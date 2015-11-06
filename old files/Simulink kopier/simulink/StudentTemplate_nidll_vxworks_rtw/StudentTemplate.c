/*
 * StudentTemplate.c
 *
 * Real-Time Workshop code generation for Simulink model "StudentTemplate.mdl".
 *
 * Model Version              : 1.119
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Wed Apr 02 20:33:15 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "StudentTemplate.h"
#include "StudentTemplate_private.h"

/* Block signals (auto storage) */
BlockIO_StudentTemplate StudentTemplate_B;

/* Continuous states */
ContinuousStates_StudentTemplat StudentTemplate_X;

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
D_Work_StudentTemplate StudentTemplate_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_StudentTemplate StudentTemplate_PrevZCSigState;

/* Real-time model */
RT_MODEL_StudentTemplate StudentTemplate_M_;
RT_MODEL_StudentTemplate *StudentTemplate_M = &StudentTemplate_M_;

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
  StudentTemplate_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  StudentTemplate_output(0);
  StudentTemplate_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE5_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  StudentTemplate_output(0);
  StudentTemplate_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE5_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  StudentTemplate_output(0);
  StudentTemplate_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++)
    hB[i] = h * rt_ODE5_B[3][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  StudentTemplate_output(0);
  StudentTemplate_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++)
    hB[i] = h * rt_ODE5_B[4][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  StudentTemplate_output(0);
  StudentTemplate_derivatives();

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
void StudentTemplate_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(StudentTemplate_M)) {
    StudentTemplate_M->Timing.t[0] = rtsiGetT(&StudentTemplate_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(StudentTemplate_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&StudentTemplate_M->solverInfo,
                          ((StudentTemplate_M->Timing.clockTick0+1)*
      StudentTemplate_M->Timing.stepSize0));
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
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Constant: '<S1>/tauxscale' */
      StudentTemplate_B.tauxscale = StudentTemplate_P.tauxscale_Value;

      /* Constant: '<S1>/tauyscale' */
      StudentTemplate_B.tauyscale = StudentTemplate_P.tauyscale_Value;

      /* Constant: '<S1>/tauyawscale' */
      StudentTemplate_B.tauyawscale = StudentTemplate_P.tauyawscale_Value;

      /* Constant: '<S4>/Initial psi [rad]' */
      StudentTemplate_B.Initialpsirad = StudentTemplate_P.Initialpsirad_Value;

      /* Constant: '<S4>/Initial x [m]' */
      StudentTemplate_B.Initialxm = StudentTemplate_P.Initialxm_Value;

      /* Constant: '<S4>/Initial y [m]' */
      StudentTemplate_B.Initialym = StudentTemplate_P.Initialym_Value;

      /* Constant: '<S4>/Initial r [rad//s]' */
      StudentTemplate_B.Initialrrads = StudentTemplate_P.Initialrrads_Value;

      /* Constant: '<S4>/Initial u [m//s]' */
      StudentTemplate_B.Initialums = StudentTemplate_P.Initialums_Value;

      /* Constant: '<S4>/Initial v [m//s]' */
      StudentTemplate_B.Initialvms = StudentTemplate_P.Initialvms_Value;

      /* Gain: '<S6>/ScalingLX' incorporates:
       *  Constant: '<S6>/AS_LX [-] '
       */
      StudentTemplate_B.xpositionofleftanalogstick11 =
        StudentTemplate_P.ScalingLX_Gain * StudentTemplate_P.AS_LX_Value;

      /* Gain: '<S6>/ScalingLY' incorporates:
       *  Constant: '<S6>/AS_LY [-]'
       */
      StudentTemplate_B.ypositionofleftanalogstick11 =
        StudentTemplate_P.ScalingLY_Gain * StudentTemplate_P.AS_LY_Value;

      /* Gain: '<S6>/Scaling_RX' incorporates:
       *  Constant: '<S6>/AS_RX [-]'
       */
      StudentTemplate_B.xpositionofrightanalogstick11 =
        StudentTemplate_P.Scaling_RX_Gain * StudentTemplate_P.AS_RX_Value;

      /* Gain: '<S6>/ScalingRY' incorporates:
       *  Constant: '<S6>/AS_RY [-]'
       */
      StudentTemplate_B.ypositionofrightanalogstick11 =
        StudentTemplate_P.ScalingRY_Gain * StudentTemplate_P.AS_RY_Value;

      /* Gain: '<S12>/Gain1' incorporates:
       *  Constant: '<S7>/setpointpsi [deg]'
       */
      StudentTemplate_B.Gain1 = StudentTemplate_P.Gain1_Gain *
        StudentTemplate_P.setpointpsideg_Value;

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
      StudentTemplate_B.ux3[0] = StudentTemplate_P.ctrl1Kdx_Value;
      StudentTemplate_B.ux3[1] = StudentTemplate_P.u_Value_ns;
      StudentTemplate_B.ux3[2] = StudentTemplate_P.u_Value_p;
      StudentTemplate_B.ux3[3] = StudentTemplate_P.u_Value;
      StudentTemplate_B.ux3[4] = StudentTemplate_P.ctrl1Kdy_Value;
      StudentTemplate_B.ux3[5] = StudentTemplate_P.u_Value_e;
      StudentTemplate_B.ux3[6] = StudentTemplate_P.u_Value_n;
      StudentTemplate_B.ux3[7] = StudentTemplate_P.u_Value_f;
      StudentTemplate_B.ux3[8] = StudentTemplate_P.ctrl1Kdpsi_Value;

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
      StudentTemplate_B.ux3_g[0] = StudentTemplate_P.ctrl1Kix_Value;
      StudentTemplate_B.ux3_g[1] = StudentTemplate_P.u_Value_k;
      StudentTemplate_B.ux3_g[2] = StudentTemplate_P.u_Value_hu;
      StudentTemplate_B.ux3_g[3] = StudentTemplate_P.u_Value_fm;
      StudentTemplate_B.ux3_g[4] = StudentTemplate_P.ctrl1Kiy_Value;
      StudentTemplate_B.ux3_g[5] = StudentTemplate_P.u_Value_a;
      StudentTemplate_B.ux3_g[6] = StudentTemplate_P.u_Value_h;
      StudentTemplate_B.ux3_g[7] = StudentTemplate_P.u_Value_fx;
      StudentTemplate_B.ux3_g[8] = StudentTemplate_P.ctrl1Kipsi_Value;

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
      StudentTemplate_B.ux3_h[0] = StudentTemplate_P.ctrl1Kpx_Value;
      StudentTemplate_B.ux3_h[1] = StudentTemplate_P.u_Value_km;
      StudentTemplate_B.ux3_h[2] = StudentTemplate_P.u_Value_f3;
      StudentTemplate_B.ux3_h[3] = StudentTemplate_P.u_Value_b;
      StudentTemplate_B.ux3_h[4] = StudentTemplate_P.ctrl1Kpy_Value;
      StudentTemplate_B.ux3_h[5] = StudentTemplate_P.u_Value_m;
      StudentTemplate_B.ux3_h[6] = StudentTemplate_P.u_Value_np;
      StudentTemplate_B.ux3_h[7] = StudentTemplate_P.u_Value_g;
      StudentTemplate_B.ux3_h[8] = StudentTemplate_P.ctrl1Kppsi_Value;

      /* Reshape: '<S16>/[2x2]' incorporates:
       *  Constant: '<S16>/12'
       *  Constant: '<S16>/21'
       *  Constant: '<S9>/Gamma_q_Surge'
       *  Constant: '<S9>/Gamma_q_Sway'
       */
      StudentTemplate_B.ux2[0] = StudentTemplate_P.Gamma_q_Surge_Value;
      StudentTemplate_B.ux2[1] = StudentTemplate_P.u_Value_mb;
      StudentTemplate_B.ux2[2] = StudentTemplate_P.u_Value_d;
      StudentTemplate_B.ux2[3] = StudentTemplate_P.Gamma_q_Sway_Value;

      /* Constant: '<S9>/Initial q_x' */
      StudentTemplate_B.Initialq_x = StudentTemplate_P.Initialq_x_Value;

      /* Constant: '<S9>/Initial q_y' */
      StudentTemplate_B.Initialq_y = StudentTemplate_P.Initialq_y_Value;

      /* Constant: '<S9>/Initial s' */
      StudentTemplate_B.Initials = StudentTemplate_P.Initials_Value;

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
      StudentTemplate_B.ux3_e[0] = StudentTemplate_P.ctrl2Kdx_Value;
      StudentTemplate_B.ux3_e[1] = StudentTemplate_P.u_Value_l;
      StudentTemplate_B.ux3_e[2] = StudentTemplate_P.u_Value_m2;
      StudentTemplate_B.ux3_e[3] = StudentTemplate_P.u_Value_hw;
      StudentTemplate_B.ux3_e[4] = StudentTemplate_P.ctrl2Kdy_Value;
      StudentTemplate_B.ux3_e[5] = StudentTemplate_P.u_Value_ey;
      StudentTemplate_B.ux3_e[6] = StudentTemplate_P.u_Value_kh;
      StudentTemplate_B.ux3_e[7] = StudentTemplate_P.u_Value_kz;
      StudentTemplate_B.ux3_e[8] = StudentTemplate_P.ctrl2Kdpsi_Value;

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
      StudentTemplate_B.ux3_b[0] = StudentTemplate_P.ctrl2Kix_Value;
      StudentTemplate_B.ux3_b[1] = StudentTemplate_P.u_Value_kr;
      StudentTemplate_B.ux3_b[2] = StudentTemplate_P.u_Value_mi;
      StudentTemplate_B.ux3_b[3] = StudentTemplate_P.u_Value_ay;
      StudentTemplate_B.ux3_b[4] = StudentTemplate_P.ctrl2Kiy_Value;
      StudentTemplate_B.ux3_b[5] = StudentTemplate_P.u_Value_pa;
      StudentTemplate_B.ux3_b[6] = StudentTemplate_P.u_Value_o;
      StudentTemplate_B.ux3_b[7] = StudentTemplate_P.u_Value_bn;
      StudentTemplate_B.ux3_b[8] = StudentTemplate_P.ctrl2Kipsi_Value;

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
      StudentTemplate_B.ux3_he[0] = StudentTemplate_P.ctrl2Kpx_Value;
      StudentTemplate_B.ux3_he[1] = StudentTemplate_P.u_Value_eq;
      StudentTemplate_B.ux3_he[2] = StudentTemplate_P.u_Value_pr;
      StudentTemplate_B.ux3_he[3] = StudentTemplate_P.u_Value_j;
      StudentTemplate_B.ux3_he[4] = StudentTemplate_P.ctrl2Kpy_Value;
      StudentTemplate_B.ux3_he[5] = StudentTemplate_P.u_Value_dj;
      StudentTemplate_B.ux3_he[6] = StudentTemplate_P.u_Value_lw;
      StudentTemplate_B.ux3_he[7] = StudentTemplate_P.u_Value_l0;
      StudentTemplate_B.ux3_he[8] = StudentTemplate_P.ctrl2Kppsi_Value;

      /* Gain: '<S28>/-l_x1' incorporates:
       *  Constant: '<S28>/l_x1'
       */
      StudentTemplate_B.l_x1 = StudentTemplate_P.l_x1_Gain *
        StudentTemplate_P.l_x1_Value;

      /* Gain: '<S28>/-l_x2' incorporates:
       *  Constant: '<S28>/l_x2'
       */
      StudentTemplate_B.l_x2 = StudentTemplate_P.l_x2_Gain *
        StudentTemplate_P.l_x2_Value;

      /* Gain: '<S28>/-l_y2' incorporates:
       *  Constant: '<S28>/l_y2'
       */
      StudentTemplate_B.l_y2 = StudentTemplate_P.l_y2_Gain *
        StudentTemplate_P.l_y2_Value;

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
      StudentTemplate_B.x5[0] = StudentTemplate_P.B_11_Value;
      StudentTemplate_B.x5[1] = StudentTemplate_P.B_21_Value;
      StudentTemplate_B.x5[2] = StudentTemplate_P.l_y1_Value;
      StudentTemplate_B.x5[3] = StudentTemplate_P.B_12_Value;
      StudentTemplate_B.x5[4] = StudentTemplate_P.B_22_Value;
      StudentTemplate_B.x5[5] = StudentTemplate_B.l_x1;
      StudentTemplate_B.x5[6] = StudentTemplate_P.B_13_Value;
      StudentTemplate_B.x5[7] = StudentTemplate_P.B_23_Value;
      StudentTemplate_B.x5[8] = StudentTemplate_B.l_y2;
      StudentTemplate_B.x5[9] = StudentTemplate_P.B_14_Value;
      StudentTemplate_B.x5[10] = StudentTemplate_P.B_24_Value;
      StudentTemplate_B.x5[11] = StudentTemplate_B.l_x2;
      StudentTemplate_B.x5[12] = StudentTemplate_P.B_15_Value;
      StudentTemplate_B.x5[13] = StudentTemplate_P.B_25_Value;
      StudentTemplate_B.x5[14] = StudentTemplate_P.l_x3_Value;

      /* Gain: '<S27>/-N_r' incorporates:
       *  Constant: '<S27>/N_r'
       */
      StudentTemplate_B.N_r = StudentTemplate_P.N_r_Gain *
        StudentTemplate_P.N_r_Value;

      /* Gain: '<S27>/-N_v' incorporates:
       *  Constant: '<S27>/N_v'
       */
      StudentTemplate_B.N_v = StudentTemplate_P.N_v_Gain *
        StudentTemplate_P.N_v_Value;

      /* Gain: '<S27>/-X_u' incorporates:
       *  Constant: '<S27>/X_u'
       */
      StudentTemplate_B.X_u = StudentTemplate_P.X_u_Gain *
        StudentTemplate_P.X_u_Value;

      /* Gain: '<S27>/-Y_v' incorporates:
       *  Constant: '<S27>/Y_v'
       */
      StudentTemplate_B.Y_v = StudentTemplate_P.Y_v_Gain *
        StudentTemplate_P.Y_v_Value;

      /* Gain: '<S27>/-Y_vr' incorporates:
       *  Constant: '<S27>/Y_r'
       */
      StudentTemplate_B.Y_vr = StudentTemplate_P.Y_vr_Gain *
        StudentTemplate_P.Y_r_Value;

      /* Reshape: '<S27>/Linear Dampning matrix' incorporates:
       *  Constant: '<S27>/D_L_12'
       *  Constant: '<S27>/D_L_13'
       *  Constant: '<S27>/D_L_21'
       *  Constant: '<S27>/D_L_31'
       */
      StudentTemplate_B.LinearDampningmatrix[0] = StudentTemplate_B.X_u;
      StudentTemplate_B.LinearDampningmatrix[1] = StudentTemplate_P.D_L_21_Value;
      StudentTemplate_B.LinearDampningmatrix[2] = StudentTemplate_P.D_L_31_Value;
      StudentTemplate_B.LinearDampningmatrix[3] = StudentTemplate_P.D_L_12_Value;
      StudentTemplate_B.LinearDampningmatrix[4] = StudentTemplate_B.Y_v;
      StudentTemplate_B.LinearDampningmatrix[5] = StudentTemplate_B.N_v;
      StudentTemplate_B.LinearDampningmatrix[6] = StudentTemplate_P.D_L_13_Value;
      StudentTemplate_B.LinearDampningmatrix[7] = StudentTemplate_B.Y_vr;
      StudentTemplate_B.LinearDampningmatrix[8] = StudentTemplate_B.N_r;

      /* Sum: '<S26>/M_11' incorporates:
       *  Constant: '<S26>/X_udot'
       *  Constant: '<S26>/m'
       */
      StudentTemplate_B.M_11 = StudentTemplate_P.m_Value -
        StudentTemplate_P.X_udot_Value;

      /* Sum: '<S26>/M_22' incorporates:
       *  Constant: '<S26>/Y_vdot'
       *  Constant: '<S26>/m'
       */
      StudentTemplate_B.M_22 = StudentTemplate_P.m_Value -
        StudentTemplate_P.Y_vdot_Value;

      /* Product: '<S26>/m x_g' incorporates:
       *  Constant: '<S26>/m'
       *  Constant: '<S26>/x_g'
       */
      StudentTemplate_B.mx_g = StudentTemplate_P.m_Value *
        StudentTemplate_P.x_g_Value;

      /* Sum: '<S26>/M_32' incorporates:
       *  Constant: '<S26>/N_vdot'
       */
      StudentTemplate_B.M_32 = StudentTemplate_B.mx_g -
        StudentTemplate_P.N_vdot_Value;

      /* Sum: '<S26>/M_23' incorporates:
       *  Constant: '<S26>/Y_rdot'
       */
      StudentTemplate_B.M_23 = StudentTemplate_B.mx_g -
        StudentTemplate_P.Y_rdot_Value;

      /* Sum: '<S26>/M_33' incorporates:
       *  Constant: '<S26>/I_z'
       *  Constant: '<S26>/N_rdot'
       */
      StudentTemplate_B.M_33 = StudentTemplate_P.I_z_Value -
        StudentTemplate_P.N_rdot_Value;

      /* Reshape: '<S26>/3x3' incorporates:
       *  Constant: '<S26>/M_12'
       *  Constant: '<S26>/M_13'
       *  Constant: '<S26>/M_21'
       *  Constant: '<S26>/M_31'
       */
      StudentTemplate_B.x3[0] = StudentTemplate_B.M_11;
      StudentTemplate_B.x3[1] = StudentTemplate_P.M_21_Value;
      StudentTemplate_B.x3[2] = StudentTemplate_P.M_31_Value;
      StudentTemplate_B.x3[3] = StudentTemplate_P.M_12_Value;
      StudentTemplate_B.x3[4] = StudentTemplate_B.M_22;
      StudentTemplate_B.x3[5] = StudentTemplate_B.M_32;
      StudentTemplate_B.x3[6] = StudentTemplate_P.M_13_Value;
      StudentTemplate_B.x3[7] = StudentTemplate_B.M_23;
      StudentTemplate_B.x3[8] = StudentTemplate_B.M_33;

      /* Gain: '<S74>/-l_x1' incorporates:
       *  Constant: '<S74>/l_x1'
       */
      StudentTemplate_B.l_x1_m = StudentTemplate_P.l_x1_Gain_n *
        StudentTemplate_P.l_x1_Value_n;

      /* Gain: '<S74>/-l_y2' incorporates:
       *  Constant: '<S74>/l_y2'
       */
      StudentTemplate_B.l_y2_a = StudentTemplate_P.l_y2_Gain_f *
        StudentTemplate_P.l_y2_Value_o;

      /* Gain: '<S74>/-l_x2' incorporates:
       *  Constant: '<S74>/l_x2'
       */
      StudentTemplate_B.l_x2_l = StudentTemplate_P.l_x2_Gain_b *
        StudentTemplate_P.l_x2_Value_l;

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
      StudentTemplate_B.x5_i[0] = StudentTemplate_P.T_e11_Value;
      StudentTemplate_B.x5_i[1] = StudentTemplate_P.T_e21_Value;
      StudentTemplate_B.x5_i[2] = StudentTemplate_P.l_y1_Value_e;
      StudentTemplate_B.x5_i[3] = StudentTemplate_P.T_e12_Value;
      StudentTemplate_B.x5_i[4] = StudentTemplate_P.T_e22_Value;
      StudentTemplate_B.x5_i[5] = StudentTemplate_B.l_x1_m;
      StudentTemplate_B.x5_i[6] = StudentTemplate_P.T_e13_Value;
      StudentTemplate_B.x5_i[7] = StudentTemplate_P.T_e23_Value;
      StudentTemplate_B.x5_i[8] = StudentTemplate_B.l_y2_a;
      StudentTemplate_B.x5_i[9] = StudentTemplate_P.T_e14_Value;
      StudentTemplate_B.x5_i[10] = StudentTemplate_P.T_e24_Value;
      StudentTemplate_B.x5_i[11] = StudentTemplate_B.l_x2_l;
      StudentTemplate_B.x5_i[12] = StudentTemplate_P.T_e15_Value;
      StudentTemplate_B.x5_i[13] = StudentTemplate_P.T_e25_Value;
      StudentTemplate_B.x5_i[14] = StudentTemplate_P.l_x3_Value_j;

      /* Gain: '<S32>/PS3 u_1' */
      StudentTemplate_B.u_1 = StudentTemplate_P.PS3u_1_Gain *
        StudentTemplate_B.ypositionofleftanalogstick11;

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
      LookUp_real_T_real_T( &(StudentTemplate_B.u_1tof_1),
                           StudentTemplate_P.u_1tof_1_YData,
                           StudentTemplate_B.u_1,
                           StudentTemplate_P.u_1tof_1_XData, 18U);

      /* Gain: '<S32>/PS3 u_2' */
      StudentTemplate_B.u_2 = StudentTemplate_P.PS3u_2_Gain *
        StudentTemplate_B.xpositionofleftanalogstick11;

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
      LookUp_real_T_real_T( &(StudentTemplate_B.u_2tof_2),
                           StudentTemplate_P.u_2tof_2_YData,
                           StudentTemplate_B.u_2,
                           StudentTemplate_P.u_2tof_2_XData, 20U);

      /* Gain: '<S32>/PS3 u_3' */
      StudentTemplate_B.u_3 = StudentTemplate_P.PS3u_3_Gain *
        StudentTemplate_B.ypositionofrightanalogstick11;

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
      LookUp_real_T_real_T( &(StudentTemplate_B.u_3tof_3),
                           StudentTemplate_P.u_3tof_3_YData,
                           StudentTemplate_B.u_3,
                           StudentTemplate_P.u_3tof_3_XData, 18U);

      /* Gain: '<S32>/PS3 u_4' */
      StudentTemplate_B.u_4 = StudentTemplate_P.PS3u_4_Gain *
        StudentTemplate_B.xpositionofrightanalogstick11;

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
      LookUp_real_T_real_T( &(StudentTemplate_B.u_4tof_4),
                           StudentTemplate_P.u_4tof_4_YData,
                           StudentTemplate_B.u_4,
                           StudentTemplate_P.u_4tof_4_XData, 16U);

      /* Sum: '<S32>/Add' incorporates:
       *  Constant: '<S6>/L2 [-]'
       *  Constant: '<S6>/R2 [-]'
       */
      StudentTemplate_B.BowThrusterdirection = StudentTemplate_P.L2_Value +
        StudentTemplate_P.R2_Value;

      /* Gain: '<S32>/PS3 u_5' */
      StudentTemplate_B.u_5 = StudentTemplate_P.PS3u_5_Gain *
        StudentTemplate_B.BowThrusterdirection;

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
      LookUp_real_T_real_T( &(StudentTemplate_B.u_5tof_5),
                           StudentTemplate_P.u_5tof_5_YData,
                           StudentTemplate_B.u_5,
                           StudentTemplate_P.u_5tof_5_XData, 6U);

      /* SignalConversion: '<S72>/TmpHiddenBufferAtProductInport2' */
      StudentTemplate_B.TmpHiddenBufferAtProductInport2[0] =
        StudentTemplate_B.u_1tof_1;
      StudentTemplate_B.TmpHiddenBufferAtProductInport2[1] =
        StudentTemplate_B.u_2tof_2;
      StudentTemplate_B.TmpHiddenBufferAtProductInport2[2] =
        StudentTemplate_B.u_3tof_3;
      StudentTemplate_B.TmpHiddenBufferAtProductInport2[3] =
        StudentTemplate_B.u_4tof_4;
      StudentTemplate_B.TmpHiddenBufferAtProductInport2[4] =
        StudentTemplate_B.u_5tof_5;

      /* Product: '<S72>/Product' */
      for (i = 0; i < 3; i++) {
        StudentTemplate_B.Product[i] = 0.0;
        for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
          StudentTemplate_B.Product[i] = StudentTemplate_B.x5_i[3 * tmp_6 + i] *
            StudentTemplate_B.TmpHiddenBufferAtProductInport2[tmp_6] +
            StudentTemplate_B.Product[i];
        }
      }
    }

    /* Gain: '<S166>/QTM In3 x-coord [mm]' */
    StudentTemplate_B.QTMIn3xcoordmm = StudentTemplate_P.QTMIn3xcoordmm_Gain *
      StudentTemplate_B.QTMIn[2];

    /* Gain: '<S166>/mm2m x' */
    StudentTemplate_B.mm2mx = StudentTemplate_P.mm2mx_Gain *
      StudentTemplate_B.QTMIn3xcoordmm;

    /* Gain: '<S166>/QTM In4 y-coord [mm]' */
    StudentTemplate_B.QTMIn4ycoordmm = StudentTemplate_P.QTMIn4ycoordmm_Gain *
      StudentTemplate_B.QTMIn[3];

    /* Gain: '<S166>/mm2m y' */
    StudentTemplate_B.mm2my = StudentTemplate_P.mm2my_Gain *
      StudentTemplate_B.QTMIn4ycoordmm;

    /* Gain: '<S166>/QTM In6 yaw [deg]' */
    StudentTemplate_B.QTMIn6yawdeg = StudentTemplate_P.QTMIn6yawdeg_Gain *
      StudentTemplate_B.QTMIn[5];

    /* Gain: '<S166>/d2r yaw' */
    StudentTemplate_B.d2ryaw = StudentTemplate_P.d2ryaw_Gain *
      StudentTemplate_B.QTMIn6yawdeg;

    /* Outputs for enable SubSystem: '<S25>/Linear Simulator' incorporates:
     *  Constant: '<S4>/Enable Linear Simulator'
     *  EnablePort: '<S192>/Enable'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M) && rtmIsMajorTimeStep
        (StudentTemplate_M)) {
      if (StudentTemplate_P.EnableLinearSimulator_Value > 0.0) {
        if (StudentTemplate_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S200>/Integrator' */
          if (rtmIsFirstInitCond(StudentTemplate_M)) {
            StudentTemplate_X.Integrator_CSTATE_en[0] = 0.0;
            StudentTemplate_X.Integrator_CSTATE_en[1] = 0.0;
            StudentTemplate_X.Integrator_CSTATE_en[2] = 0.0;
          }

          StudentTemplate_DWork.Integrator_IWORK_jt.IcNeedsLoading = 1;

          /* Integrator Block: '<S200>/Integrator1' */
          if (rtmIsFirstInitCond(StudentTemplate_M)) {
            StudentTemplate_X.Integrator1_CSTATE_l[0] = 0.0;
            StudentTemplate_X.Integrator1_CSTATE_l[1] = 0.0;
            StudentTemplate_X.Integrator1_CSTATE_l[2] = 0.0;
          }

          StudentTemplate_DWork.Integrator1_IWORK_h.IcNeedsLoading = 1;
          StudentTemplate_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (StudentTemplate_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          StudentTemplate_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (StudentTemplate_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Integrator Block: '<S200>/Integrator'
       */
      if (rtmIsMajorTimeStep(StudentTemplate_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE_j,
                           StudentTemplate_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || StudentTemplate_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            StudentTemplate_DWork.Integrator_IWORK_jt.IcNeedsLoading) {
          StudentTemplate_X.Integrator_CSTATE_en[0] =
            StudentTemplate_B.Initialums;
          StudentTemplate_X.Integrator_CSTATE_en[1] =
            StudentTemplate_B.Initialvms;
          StudentTemplate_X.Integrator_CSTATE_en[2] =
            StudentTemplate_B.Initialrrads;
        }

        StudentTemplate_DWork.Integrator_IWORK_jt.IcNeedsLoading = 0;
      }

      StudentTemplate_B.Integrator_p[0] =
        StudentTemplate_X.Integrator_CSTATE_en[0];
      StudentTemplate_B.Integrator_p[1] =
        StudentTemplate_X.Integrator_CSTATE_en[1];
      StudentTemplate_B.Integrator_p[2] =
        StudentTemplate_X.Integrator_CSTATE_en[2];

      /* Integrator Block: '<S200>/Integrator1'
       */
      if (rtmIsMajorTimeStep(StudentTemplate_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &StudentTemplate_PrevZCSigState.Integrator1_Reset_ZCE_e,
                           StudentTemplate_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || StudentTemplate_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            StudentTemplate_DWork.Integrator1_IWORK_h.IcNeedsLoading) {
          StudentTemplate_X.Integrator1_CSTATE_l[0] =
            StudentTemplate_B.Initialxm;
          StudentTemplate_X.Integrator1_CSTATE_l[1] =
            StudentTemplate_B.Initialym;
          StudentTemplate_X.Integrator1_CSTATE_l[2] =
            StudentTemplate_B.Initialpsirad;
        }

        StudentTemplate_DWork.Integrator1_IWORK_h.IcNeedsLoading = 0;
      }

      StudentTemplate_B.Integrator1_n[0] =
        StudentTemplate_X.Integrator1_CSTATE_l[0];
      StudentTemplate_B.Integrator1_n[1] =
        StudentTemplate_X.Integrator1_CSTATE_l[1];
      StudentTemplate_B.Integrator1_n[2] =
        StudentTemplate_X.Integrator1_CSTATE_l[2];

      /* Fcn: '<S201>/R11' */
      StudentTemplate_B.R11_e = cos(StudentTemplate_B.Integrator1_n[2]);

      /* Fcn: '<S201>/R21' */
      StudentTemplate_B.R21_a = sin(StudentTemplate_B.Integrator1_n[2]);

      /* Fcn: '<S201>/R12' */
      StudentTemplate_B.R12_h = -1.0 * sin(StudentTemplate_B.Integrator1_n[2]);

      /* Fcn: '<S201>/R22' */
      StudentTemplate_B.R22_e = cos(StudentTemplate_B.Integrator1_n[2]);

      /* Reshape: '<S201>/R(psi)' incorporates:
       *  Constant: '<S201>/R13'
       *  Constant: '<S201>/R23'
       *  Constant: '<S201>/R31'
       *  Constant: '<S201>/R32'
       *  Constant: '<S201>/R33'
       */
      StudentTemplate_B.Rpsi_h[0] = StudentTemplate_B.R11_e;
      StudentTemplate_B.Rpsi_h[1] = StudentTemplate_B.R21_a;
      StudentTemplate_B.Rpsi_h[2] = StudentTemplate_P.R31_Value_j;
      StudentTemplate_B.Rpsi_h[3] = StudentTemplate_B.R12_h;
      StudentTemplate_B.Rpsi_h[4] = StudentTemplate_B.R22_e;
      StudentTemplate_B.Rpsi_h[5] = StudentTemplate_P.R32_Value_h;
      StudentTemplate_B.Rpsi_h[6] = StudentTemplate_P.R13_Value_p;
      StudentTemplate_B.Rpsi_h[7] = StudentTemplate_P.R23_Value_f;
      StudentTemplate_B.Rpsi_h[8] = StudentTemplate_P.R33_Value_h;
    }

    /* end of Outputs for SubSystem: '<S25>/Linear Simulator' */

    /* MultiPortSwitch: '<S167>/eta Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)StudentTemplate_P.ControlInputSelector_Value == 0) {
      StudentTemplate_B.etaSwitch[0] = StudentTemplate_B.mm2mx;
      StudentTemplate_B.etaSwitch[1] = StudentTemplate_B.mm2my;
      StudentTemplate_B.etaSwitch[2] = StudentTemplate_B.d2ryaw;
    } else {
      StudentTemplate_B.etaSwitch[0] = StudentTemplate_B.Integrator1_n[0];
      StudentTemplate_B.etaSwitch[1] = StudentTemplate_B.Integrator1_n[1];
      StudentTemplate_B.etaSwitch[2] = StudentTemplate_B.Integrator1_n[2];
    }

    /* Fcn: '<S30>/yaw angle' */
    StudentTemplate_B.psi = StudentTemplate_B.etaSwitch[2];

    /* Saturate: '<S36>/Saturation' */
    tmp = StudentTemplate_B.psi;
    StudentTemplate_B.Saturation = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat,
      StudentTemplate_P.Saturation_UpperSat);

    /* Signum: '<S36>/Sign' */
    StudentTemplate_B.Sign = rt_SIGNd_snf(StudentTemplate_B.Saturation);

    /* Gain: '<S36>/Gain' */
    StudentTemplate_B.Gain = StudentTemplate_P.Gain_Gain *
      StudentTemplate_B.Sign;

    /* Sum: '<S36>/Sum1' */
    StudentTemplate_B.Sum1 = StudentTemplate_B.Saturation +
      StudentTemplate_B.Gain;

    /* Math: '<S36>/Math Function' incorporates:
     *  Constant: '<S36>/Constant'
     */
    StudentTemplate_B.MathFunction = rt_rem_snf(StudentTemplate_B.Sum1,
      StudentTemplate_P.Constant_Value);

    /* Sum: '<S36>/Sum' */
    StudentTemplate_B.Sum = StudentTemplate_B.MathFunction -
      StudentTemplate_B.Gain;

    /* Sum: '<S30>/Sum2' incorporates:
     *  Constant: '<S7>/setpointx [m]'
     *  Constant: '<S7>/setpointy [m]'
     */
    StudentTemplate_B.Sum2[0] = StudentTemplate_P.setpointxm_Value -
      StudentTemplate_B.etaSwitch[0];
    StudentTemplate_B.Sum2[1] = StudentTemplate_P.setpointym_Value -
      StudentTemplate_B.etaSwitch[1];
    StudentTemplate_B.Sum2[2] = StudentTemplate_B.Gain1 -
      StudentTemplate_B.etaSwitch[2];

    /* Saturate: '<S35>/Saturation' */
    tmp = StudentTemplate_B.Sum2[2];
    StudentTemplate_B.Saturation_l = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_p,
      StudentTemplate_P.Saturation_UpperSat_f);

    /* Signum: '<S35>/Sign' */
    StudentTemplate_B.Sign_b = rt_SIGNd_snf(StudentTemplate_B.Saturation_l);

    /* Gain: '<S35>/Gain' */
    StudentTemplate_B.Gain_n = StudentTemplate_P.Gain_Gain_j *
      StudentTemplate_B.Sign_b;

    /* Sum: '<S35>/Sum1' */
    StudentTemplate_B.Sum1_c = StudentTemplate_B.Saturation_l +
      StudentTemplate_B.Gain_n;

    /* Math: '<S35>/Math Function' incorporates:
     *  Constant: '<S35>/Constant'
     */
    StudentTemplate_B.MathFunction_e = rt_rem_snf(StudentTemplate_B.Sum1_c,
      StudentTemplate_P.Constant_Value_k);

    /* Sum: '<S35>/Sum' */
    StudentTemplate_B.Sum_m = StudentTemplate_B.MathFunction_e -
      StudentTemplate_B.Gain_n;

    /* Fcn: '<S34>/Row1' */
    StudentTemplate_B.Row1 = cos(StudentTemplate_B.Sum) *
      StudentTemplate_B.Sum2[0] + sin(StudentTemplate_B.Sum) *
      StudentTemplate_B.Sum2[1];

    /* Fcn: '<S34>/Row2' */
    StudentTemplate_B.Row2 = (-sin(StudentTemplate_B.Sum)) *
      StudentTemplate_B.Sum2[0] + cos(StudentTemplate_B.Sum) *
      StudentTemplate_B.Sum2[1];

    /* Fcn: '<S34>/Row3' */
    StudentTemplate_B.Row3 = StudentTemplate_B.Sum_m;

    /* SignalConversion: '<S30>/TmpHiddenBufferAtProductInport2' */
    StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[0] =
      StudentTemplate_B.Row1;
    StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[1] =
      StudentTemplate_B.Row2;
    StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[2] =
      StudentTemplate_B.Row3;

    /* Product: '<S30>/Product' */
    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product_m[i] = 0.0;
      StudentTemplate_B.Product_m[i] = StudentTemplate_B.ux3_h[i] *
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[0] +
        StudentTemplate_B.Product_m[i];
      StudentTemplate_B.Product_m[i] = StudentTemplate_B.ux3_h[i + 3] *
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[1] +
        StudentTemplate_B.Product_m[i];
      StudentTemplate_B.Product_m[i] = StudentTemplate_B.ux3_h[i + 6] *
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[2] +
        StudentTemplate_B.Product_m[i];
    }

    /* Integrator Block: '<S30>/Integrator'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE,
                         StudentTemplate_P.ctrl1ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || StudentTemplate_P.ctrl1ResetIntegrator_Value != 0.0) {
        StudentTemplate_X.Integrator_CSTATE[0] = StudentTemplate_P.Integrator_IC;
        StudentTemplate_X.Integrator_CSTATE[1] = StudentTemplate_P.Integrator_IC;
        StudentTemplate_X.Integrator_CSTATE[2] = StudentTemplate_P.Integrator_IC;
      }
    }

    StudentTemplate_B.Integrator[0] = StudentTemplate_X.Integrator_CSTATE[0];
    StudentTemplate_B.Integrator[1] = StudentTemplate_X.Integrator_CSTATE[1];
    StudentTemplate_B.Integrator[2] = StudentTemplate_X.Integrator_CSTATE[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S30>/Product1' */
      StudentTemplate_B.Product1[i] = 0.0;
      StudentTemplate_B.Product1[i] = StudentTemplate_B.ux3_g[i] *
        StudentTemplate_B.Integrator[0] + StudentTemplate_B.Product1[i];
      StudentTemplate_B.Product1[i] = StudentTemplate_B.ux3_g[i + 3] *
        StudentTemplate_B.Integrator[1] + StudentTemplate_B.Product1[i];
      StudentTemplate_B.Product1[i] = StudentTemplate_B.ux3_g[i + 6] *
        StudentTemplate_B.Integrator[2] + StudentTemplate_B.Product1[i];

      /* Sum: '<S30>/Sum3' */
      StudentTemplate_B.Sum3[i] = StudentTemplate_B.Product_m[i] +
        StudentTemplate_B.Product1[i];
    }

    /* Integrator Block: '<S169>/Integrator4'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &StudentTemplate_PrevZCSigState.Integrator4_Reset_ZCE,
                         StudentTemplate_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || StudentTemplate_P.ctrl2ResetIntegrator_Value != 0.0) {
        StudentTemplate_X.Integrator4_CSTATE[0] =
          StudentTemplate_P.Integrator4_IC;
        StudentTemplate_X.Integrator4_CSTATE[1] =
          StudentTemplate_P.Integrator4_IC;
        StudentTemplate_X.Integrator4_CSTATE[2] =
          StudentTemplate_P.Integrator4_IC;
      }
    }

    StudentTemplate_B.nu[0] = StudentTemplate_X.Integrator4_CSTATE[0];
    StudentTemplate_B.nu[1] = StudentTemplate_X.Integrator4_CSTATE[1];
    StudentTemplate_B.nu[2] = StudentTemplate_X.Integrator4_CSTATE[2];

    /* MultiPortSwitch: '<S167>/nu Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)StudentTemplate_P.ControlInputSelector_Value == 0) {
      StudentTemplate_B.nuSwitch[0] = StudentTemplate_B.nu[0];
      StudentTemplate_B.nuSwitch[1] = StudentTemplate_B.nu[1];
      StudentTemplate_B.nuSwitch[2] = StudentTemplate_B.nu[2];
    } else {
      StudentTemplate_B.nuSwitch[0] = StudentTemplate_B.Integrator_p[0];
      StudentTemplate_B.nuSwitch[1] = StudentTemplate_B.Integrator_p[1];
      StudentTemplate_B.nuSwitch[2] = StudentTemplate_B.Integrator_p[2];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S30>/Product2' */
      StudentTemplate_B.Product2[i] = 0.0;
      StudentTemplate_B.Product2[i] = StudentTemplate_B.ux3[i] *
        StudentTemplate_B.nuSwitch[0] + StudentTemplate_B.Product2[i];
      StudentTemplate_B.Product2[i] = StudentTemplate_B.ux3[i + 3] *
        StudentTemplate_B.nuSwitch[1] + StudentTemplate_B.Product2[i];
      StudentTemplate_B.Product2[i] = StudentTemplate_B.ux3[i + 6] *
        StudentTemplate_B.nuSwitch[2] + StudentTemplate_B.Product2[i];

      /* Sum: '<S30>/Sum1' */
      StudentTemplate_B.Sum1_j[i] = StudentTemplate_B.Sum3[i] -
        StudentTemplate_B.Product2[i];
    }

    /* Trigonometry: '<S41>/R11' */
    StudentTemplate_B.R11 = cos(StudentTemplate_B.etaSwitch[2]);

    /* Trigonometry: '<S41>/R21' */
    StudentTemplate_B.R21 = sin(StudentTemplate_B.etaSwitch[2]);

    /* Trigonometry: '<S41>/R12' */
    StudentTemplate_B.R12 = sin(StudentTemplate_B.etaSwitch[2]);

    /* Gain: '<S41>/-1' */
    StudentTemplate_B.u = StudentTemplate_P.u_Gain * StudentTemplate_B.R12;

    /* Trigonometry: '<S41>/R22' */
    StudentTemplate_B.R22 = cos(StudentTemplate_B.etaSwitch[2]);

    /* Reshape: '<S41>/R(psi)' incorporates:
     *  Constant: '<S41>/R13'
     *  Constant: '<S41>/R23'
     *  Constant: '<S41>/R31'
     *  Constant: '<S41>/R32'
     *  Constant: '<S41>/R33'
     */
    StudentTemplate_B.Rpsi[0] = StudentTemplate_B.R11;
    StudentTemplate_B.Rpsi[1] = StudentTemplate_B.R21;
    StudentTemplate_B.Rpsi[2] = StudentTemplate_P.R31_Value;
    StudentTemplate_B.Rpsi[3] = StudentTemplate_B.u;
    StudentTemplate_B.Rpsi[4] = StudentTemplate_B.R22;
    StudentTemplate_B.Rpsi[5] = StudentTemplate_P.R32_Value;
    StudentTemplate_B.Rpsi[6] = StudentTemplate_P.R13_Value;
    StudentTemplate_B.Rpsi[7] = StudentTemplate_P.R23_Value;
    StudentTemplate_B.Rpsi[8] = StudentTemplate_P.R33_Value;

    /* Math: '<S61>/Math Function' */
    for (i = 0; i < 3; i++) {
      StudentTemplate_B.MathFunction_a[3 * i] = StudentTemplate_B.Rpsi[i];
      StudentTemplate_B.MathFunction_a[1 + 3 * i] = StudentTemplate_B.Rpsi[i + 3];
      StudentTemplate_B.MathFunction_a[2 + 3 * i] = StudentTemplate_B.Rpsi[i + 6];
    }

    /* Integrator Block: '<S50>/Integrator'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE_c,
                         StudentTemplate_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || StudentTemplate_P.ctrl2ResetIntegrator_Value != 0.0) {
        StudentTemplate_X.Integrator_CSTATE_c[0] =
          StudentTemplate_P.Integrator_IC_f[0];
        StudentTemplate_X.Integrator_CSTATE_c[1] =
          StudentTemplate_P.Integrator_IC_f[1];
        StudentTemplate_X.Integrator_CSTATE_c[2] =
          StudentTemplate_P.Integrator_IC_f[2];
      }
    }

    StudentTemplate_B.Integrator_h[0] = StudentTemplate_X.Integrator_CSTATE_c[0];
    StudentTemplate_B.Integrator_h[1] = StudentTemplate_X.Integrator_CSTATE_c[1];
    StudentTemplate_B.Integrator_h[2] = StudentTemplate_X.Integrator_CSTATE_c[2];

    /* Product: '<S39>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] + StudentTemplate_B.ux3_b[3 *
          tmp_6] * StudentTemplate_B.MathFunction_a[i];
        tmp_1[i + 3 * tmp_6] = StudentTemplate_B.ux3_b[3 * tmp_6 + 1] *
          StudentTemplate_B.MathFunction_a[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = StudentTemplate_B.ux3_b[3 * tmp_6 + 2] *
          StudentTemplate_B.MathFunction_a[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product_e[i] = 0.0;
      StudentTemplate_B.Product_e[i] = tmp_1[i] *
        StudentTemplate_B.Integrator_h[0] + StudentTemplate_B.Product_e[i];
      StudentTemplate_B.Product_e[i] = tmp_1[i + 3] *
        StudentTemplate_B.Integrator_h[1] + StudentTemplate_B.Product_e[i];
      StudentTemplate_B.Product_e[i] = tmp_1[i + 6] *
        StudentTemplate_B.Integrator_h[2] + StudentTemplate_B.Product_e[i];

      /* Gain: '<S39>/Gain' */
      StudentTemplate_B.Gain_a[i] = StudentTemplate_P.Gain_Gain_c *
        StudentTemplate_B.Product_e[i];
    }

    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Gain: '<S39>/4' incorporates:
       *  Constant: '<S9>/kappa_1'
       */
      StudentTemplate_B.u_h = StudentTemplate_P._Gain *
        StudentTemplate_P.kappa_1_Value;

      /* Product: '<S39>/Divide' incorporates:
       *  Constant: '<S39>/1'
       */
      StudentTemplate_B.Divide = StudentTemplate_P._Value /
        StudentTemplate_B.u_h;
      for (i = 0; i < 9; i++) {
        /* Sum: '<S39>/Add1' */
        StudentTemplate_B.Add1[i] = StudentTemplate_B.ux3_e[i] +
          StudentTemplate_B.Divide;

        /* Product: '<S31>/Product1' incorporates:
         *  Constant: '<S40>/Constant'
         *  Constant: '<S9>/kappa_1'
         */
        StudentTemplate_B.Product1_d[i] = StudentTemplate_P.kappa_1_Value *
          StudentTemplate_P.Constant_Value_e[i];

        /* Sum: '<S31>/Add3' */
        StudentTemplate_B.Add3[i] = StudentTemplate_B.ux3_he[i] +
          StudentTemplate_B.Product1_d[i];
      }
    }

    /* Saturate: '<S69>/Saturation' */
    tmp = StudentTemplate_B.etaSwitch[2];
    StudentTemplate_B.Saturation_o = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_f,
      StudentTemplate_P.Saturation_UpperSat_n);

    /* Signum: '<S69>/Sign' */
    StudentTemplate_B.Sign_p = rt_SIGNd_snf(StudentTemplate_B.Saturation_o);

    /* Gain: '<S69>/Gain' */
    StudentTemplate_B.Gain_m = StudentTemplate_P.Gain_Gain_h *
      StudentTemplate_B.Sign_p;

    /* Sum: '<S69>/Sum1' */
    StudentTemplate_B.Sum1_k = StudentTemplate_B.Saturation_o +
      StudentTemplate_B.Gain_m;

    /* Math: '<S69>/Math Function' incorporates:
     *  Constant: '<S69>/Constant'
     */
    StudentTemplate_B.MathFunction_d = rt_rem_snf(StudentTemplate_B.Sum1_k,
      StudentTemplate_P.Constant_Value_f);

    /* Sum: '<S69>/Sum' */
    StudentTemplate_B.Sum_n = StudentTemplate_B.MathFunction_d -
      StudentTemplate_B.Gain_m;

    /* Integrator Block: '<S42>/Integrator'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE_p,
                         StudentTemplate_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || StudentTemplate_P.ctrl2ResetIntegrator_Value != 0.0 ||
          StudentTemplate_DWork.Integrator_IWORK.IcNeedsLoading) {
        StudentTemplate_X.Integrator_CSTATE_j[0] = StudentTemplate_B.Initialq_x;
        StudentTemplate_X.Integrator_CSTATE_j[1] = StudentTemplate_B.Initialq_y;
      }

      StudentTemplate_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    StudentTemplate_B.Integrator_b[0] = StudentTemplate_X.Integrator_CSTATE_j[0];
    StudentTemplate_B.Integrator_b[1] = StudentTemplate_X.Integrator_CSTATE_j[1];

    /* SignalConversion: '<S106>/ConcatBufferAtVector ConcatenateIn1' */
    StudentTemplate_B.VectorConcatenate[0] = StudentTemplate_B.Integrator_b[0];
    StudentTemplate_B.VectorConcatenate[1] = StudentTemplate_B.Integrator_b[1];
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Sum: '<S159>/x_2 - x_1' incorporates:
       *  Constant: '<S11>/x_1 [m]'
       *  Constant: '<S11>/x_2 [m]'
       */
      StudentTemplate_B.x_2x_1 = StudentTemplate_P.x_2m_Value -
        StudentTemplate_P.x_1m_Value;

      /* Sum: '<S159>/y_2 - y_1' incorporates:
       *  Constant: '<S11>/y_1 [m]'
       *  Constant: '<S11>/y_2 [m]'
       */
      StudentTemplate_B.y_2y_1 = StudentTemplate_P.y_2m_Value -
        StudentTemplate_P.y_1m_Value;

      /* SignalConversion: '<S160>/TmpHiddenBufferAtProductInport2' */
      StudentTemplate_B.TmpHiddenBufferAtProductInpor_e[0] =
        StudentTemplate_B.x_2x_1;
      StudentTemplate_B.TmpHiddenBufferAtProductInpor_e[1] =
        StudentTemplate_B.y_2y_1;

      /* Saturate: '<S142>/Saturation' incorporates:
       *  Constant: '<S5>/Path Selector  [-]'
       */
      tmp = StudentTemplate_P.PathSelector_Value;
      StudentTemplate_B.Saturation_d = rt_SATURATE(tmp,
        StudentTemplate_P.Saturation_LowerSat_o,
        StudentTemplate_P.Saturation_UpperSat_c);

      /* Rounding: '<S142>/Rounding Function' */
      StudentTemplate_B.RoundingFunction = floor(StudentTemplate_B.Saturation_d);

      /* Product: '<S152>/Product' */
      StudentTemplate_B.Product_n[0] =
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_e[0] *
        StudentTemplate_B.RoundingFunction;
      StudentTemplate_B.Product_n[1] =
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_e[1] *
        StudentTemplate_B.RoundingFunction;
    }

    /* Integrator Block: '<S42>/Integrator1'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &StudentTemplate_PrevZCSigState.Integrator1_Reset_ZCE,
                         StudentTemplate_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || StudentTemplate_P.ctrl2ResetIntegrator_Value != 0.0 ||
          StudentTemplate_DWork.Integrator1_IWORK.IcNeedsLoading) {
        StudentTemplate_X.Integrator1_CSTATE = StudentTemplate_B.Initials;
      }

      StudentTemplate_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    StudentTemplate_B.Integrator1 = StudentTemplate_X.Integrator1_CSTATE;

    /* Product: '<S145>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    StudentTemplate_B.Product2_j = StudentTemplate_B.Integrator1 *
      StudentTemplate_P.k_Value;

    /* Trigonometry: '<S145>/sin(s)' */
    StudentTemplate_B.sins = sin(StudentTemplate_B.Product2_j);

    /* Product: '<S145>/Product' incorporates:
     *  Constant: '<S10>/k [-]'
     *  Constant: '<S10>/r_x [m]'
     */
    StudentTemplate_B.Product_b = StudentTemplate_P.r_xm_Value *
      StudentTemplate_B.sins * StudentTemplate_P.k_Value;

    /* Gain: '<S145>/Gain' */
    StudentTemplate_B.Gain_mx = StudentTemplate_P.Gain_Gain_n *
      StudentTemplate_B.Product_b;

    /* Trigonometry: '<S145>/cos(s)' */
    StudentTemplate_B.coss = cos(StudentTemplate_B.Product2_j);

    /* Product: '<S145>/Product1' incorporates:
     *  Constant: '<S10>/k [-]'
     *  Constant: '<S10>/r_y [m]'
     */
    StudentTemplate_B.Product1_a = StudentTemplate_P.r_ym_Value *
      StudentTemplate_B.coss * StudentTemplate_P.k_Value;

    /* SignalConversion: '<S148>/TmpHiddenBufferAtProductInport2' */
    StudentTemplate_B.TmpHiddenBufferAtProductInpo_ds[0] =
      StudentTemplate_B.Gain_mx;
    StudentTemplate_B.TmpHiddenBufferAtProductInpo_ds[1] =
      StudentTemplate_B.Product1_a;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Sum: '<S152>/Subract' incorporates:
       *  Constant: '<S152>/Constant'
       */
      StudentTemplate_B.Subract = StudentTemplate_P.Constant_Value_m -
        StudentTemplate_B.RoundingFunction;
    }

    /* Product: '<S152>/Product1' */
    StudentTemplate_B.Product1_m[0] =
      StudentTemplate_B.TmpHiddenBufferAtProductInpo_ds[0] *
      StudentTemplate_B.Subract;

    /* Sum: '<S152>/Add' */
    StudentTemplate_B.Add[0] = StudentTemplate_B.Product_n[0] +
      StudentTemplate_B.Product1_m[0];

    /* Product: '<S152>/Product1' */
    StudentTemplate_B.Product1_m[1] =
      StudentTemplate_B.TmpHiddenBufferAtProductInpo_ds[1] *
      StudentTemplate_B.Subract;

    /* Sum: '<S152>/Add' */
    StudentTemplate_B.Add[1] = StudentTemplate_B.Product_n[1] +
      StudentTemplate_B.Product1_m[1];

    /* Trigonometry: '<S97>/Trigonometric Function' */
    StudentTemplate_B.TrigonometricFunction = rt_atan2_snf
      (StudentTemplate_B.Add[1], StudentTemplate_B.Add[0]);

    /* Saturate: '<S100>/Saturation' */
    tmp = StudentTemplate_B.TrigonometricFunction;
    StudentTemplate_B.Saturation_c = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_h,
      StudentTemplate_P.Saturation_UpperSat_b);

    /* Signum: '<S100>/Sign' */
    StudentTemplate_B.Sign_m = rt_SIGNd_snf(StudentTemplate_B.Saturation_c);

    /* Gain: '<S100>/Gain' */
    StudentTemplate_B.Gain_c = StudentTemplate_P.Gain_Gain_g *
      StudentTemplate_B.Sign_m;

    /* Sum: '<S100>/Sum1' */
    StudentTemplate_B.Sum1_l = StudentTemplate_B.Saturation_c +
      StudentTemplate_B.Gain_c;

    /* Math: '<S100>/Math Function' incorporates:
     *  Constant: '<S100>/Constant'
     */
    StudentTemplate_B.MathFunction_dh = rt_rem_snf(StudentTemplate_B.Sum1_l,
      StudentTemplate_P.Constant_Value_i);

    /* Sum: '<S100>/Sum' */
    StudentTemplate_B.Sum_b = StudentTemplate_B.MathFunction_dh -
      StudentTemplate_B.Gain_c;

    /* Saturate: '<S128>/Saturation' */
    tmp = StudentTemplate_B.Sum_b;
    StudentTemplate_B.Saturation_n = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_a,
      StudentTemplate_P.Saturation_UpperSat_cq);

    /* Signum: '<S128>/Sign' */
    StudentTemplate_B.Sign_g = rt_SIGNd_snf(StudentTemplate_B.Saturation_n);

    /* Gain: '<S128>/Gain' */
    StudentTemplate_B.Gain_k = StudentTemplate_P.Gain_Gain_h4 *
      StudentTemplate_B.Sign_g;

    /* Sum: '<S128>/Sum1' */
    StudentTemplate_B.Sum1_j4 = StudentTemplate_B.Saturation_n +
      StudentTemplate_B.Gain_k;

    /* Math: '<S128>/Math Function' incorporates:
     *  Constant: '<S128>/Constant'
     */
    StudentTemplate_B.MathFunction_j = rt_rem_snf(StudentTemplate_B.Sum1_j4,
      StudentTemplate_P.Constant_Value_n);

    /* Sum: '<S128>/Sum' */
    StudentTemplate_B.Sum_i = StudentTemplate_B.MathFunction_j -
      StudentTemplate_B.Gain_k;

    /* Outputs for atomic SubSystem: '<S105>/R_2' */

    /* Trigonometry: '<S131>/R11' */
    StudentTemplate_B.R11_j = cos(StudentTemplate_B.Sum_b);

    /* Trigonometry: '<S131>/R21' */
    StudentTemplate_B.R21_n = sin(StudentTemplate_B.Sum_b);

    /* Gain: '<S131>/R12' */
    StudentTemplate_B.R12_k = StudentTemplate_P.R12_Gain *
      StudentTemplate_B.R21_n;

    /* Gain: '<S131>/R22' */
    StudentTemplate_B.R22_j = StudentTemplate_P.R22_Gain *
      StudentTemplate_B.R11_j;

    /* Reshape: '<S131>/R_2(psi_d)' */
    StudentTemplate_B.R_2psi_d[0] = StudentTemplate_B.R11_j;
    StudentTemplate_B.R_2psi_d[1] = StudentTemplate_B.R21_n;
    StudentTemplate_B.R_2psi_d[2] = StudentTemplate_B.R12_k;
    StudentTemplate_B.R_2psi_d[3] = StudentTemplate_B.R22_j;

    /* end of Outputs for SubSystem: '<S105>/R_2' */

    /* Math: '<S132>/Math Function' */
    StudentTemplate_B.MathFunction_h[0] = StudentTemplate_B.R_2psi_d[0];
    StudentTemplate_B.MathFunction_h[1] = StudentTemplate_B.R_2psi_d[2];
    StudentTemplate_B.MathFunction_h[2] = StudentTemplate_B.R_2psi_d[1];
    StudentTemplate_B.MathFunction_h[3] = StudentTemplate_B.R_2psi_d[3];
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Sum: '<S158>/x_2 - x_1' incorporates:
       *  Constant: '<S11>/x_1 [m]'
       *  Constant: '<S11>/x_2 [m]'
       */
      StudentTemplate_B.x_2x_1_e = StudentTemplate_P.x_2m_Value -
        StudentTemplate_P.x_1m_Value;
    }

    /* Product: '<S158>/(x_2 - x_1) * s' */
    StudentTemplate_B.x_2x_1s = StudentTemplate_B.x_2x_1_e *
      StudentTemplate_B.Integrator1;

    /* Sum: '<S158>/(x_2 - x_1) * s + x_1' incorporates:
     *  Constant: '<S11>/x_1 [m]'
     */
    StudentTemplate_B.x_2x_1sx_1 = StudentTemplate_B.x_2x_1s +
      StudentTemplate_P.x_1m_Value;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Sum: '<S158>/y_2 - y_1' incorporates:
       *  Constant: '<S11>/y_1 [m]'
       *  Constant: '<S11>/y_2 [m]'
       */
      StudentTemplate_B.y_2y_1_j = StudentTemplate_P.y_2m_Value -
        StudentTemplate_P.y_1m_Value;
    }

    /* Product: '<S158>/(y_2 - y_1) * s' */
    StudentTemplate_B.y_2y_1s = StudentTemplate_B.y_2y_1_j *
      StudentTemplate_B.Integrator1;

    /* Sum: '<S158>/(y_2 - y_1) * s + y_1' incorporates:
     *  Constant: '<S11>/y_1 [m]'
     */
    StudentTemplate_B.y_2y_1sy_1 = StudentTemplate_B.y_2y_1s +
      StudentTemplate_P.y_1m_Value;

    /* Product: '<S151>/Product' */
    StudentTemplate_B.Product_mq[0] = StudentTemplate_B.x_2x_1sx_1 *
      StudentTemplate_B.RoundingFunction;
    StudentTemplate_B.Product_mq[1] = StudentTemplate_B.y_2y_1sy_1 *
      StudentTemplate_B.RoundingFunction;

    /* Product: '<S144>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    StudentTemplate_B.Product2_l = StudentTemplate_B.Integrator1 *
      StudentTemplate_P.k_Value;

    /* Trigonometry: '<S144>/cos(s)' */
    StudentTemplate_B.coss_n = cos(StudentTemplate_B.Product2_l);

    /* Product: '<S144>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    StudentTemplate_B.Product_c = StudentTemplate_P.r_xm_Value *
      StudentTemplate_B.coss_n;

    /* Sum: '<S144>/Add' incorporates:
     *  Constant: '<S10>/x_0 [m]'
     */
    StudentTemplate_B.Add_i = StudentTemplate_B.Product_c +
      StudentTemplate_P.x_0m_Value;

    /* Trigonometry: '<S144>/sin(s)' */
    StudentTemplate_B.sins_o = sin(StudentTemplate_B.Product2_l);

    /* Product: '<S144>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    StudentTemplate_B.Product1_h = StudentTemplate_P.r_ym_Value *
      StudentTemplate_B.sins_o;

    /* Sum: '<S144>/Add1' incorporates:
     *  Constant: '<S10>/y_0 [m]'
     */
    StudentTemplate_B.Add1_i = StudentTemplate_B.Product1_h +
      StudentTemplate_P.y_0m_Value;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Sum: '<S151>/Subract' incorporates:
       *  Constant: '<S151>/Constant'
       */
      StudentTemplate_B.Subract_a = StudentTemplate_P.Constant_Value_p -
        StudentTemplate_B.RoundingFunction;
    }

    /* Product: '<S151>/Product1' */
    StudentTemplate_B.Product1_f[0] = StudentTemplate_B.Add_i *
      StudentTemplate_B.Subract_a;
    StudentTemplate_B.Product1_f[1] = StudentTemplate_B.Add1_i *
      StudentTemplate_B.Subract_a;

    /* Sum: '<S151>/Add' */
    StudentTemplate_B.Add_n[0] = StudentTemplate_B.Product_mq[0] +
      StudentTemplate_B.Product1_f[0];
    StudentTemplate_B.Add_n[1] = StudentTemplate_B.Product_mq[1] +
      StudentTemplate_B.Product1_f[1];

    /* RelationalOperator: '<S156>/LowerRelop1' incorporates:
     *  Constant: '<S5>/x_dmax [m]'
     */
    StudentTemplate_B.LowerRelop1 = (StudentTemplate_B.Add_n[0] >
      StudentTemplate_P.x_dmaxm_Value);

    /* RelationalOperator: '<S156>/UpperRelop' incorporates:
     *  Constant: '<S5>/x_dmin [m]'
     */
    StudentTemplate_B.UpperRelop = (StudentTemplate_B.Add_n[0] <
      StudentTemplate_P.x_dminm_Value);

    /* Switch: '<S156>/Switch' incorporates:
     *  Constant: '<S5>/x_dmin [m]'
     */
    if (StudentTemplate_B.UpperRelop) {
      StudentTemplate_B.Switch = StudentTemplate_P.x_dminm_Value;
    } else {
      StudentTemplate_B.Switch = StudentTemplate_B.Add_n[0];
    }

    /* Switch: '<S156>/Switch2' incorporates:
     *  Constant: '<S5>/x_dmax [m]'
     */
    if (StudentTemplate_B.LowerRelop1) {
      StudentTemplate_B.Switch2 = StudentTemplate_P.x_dmaxm_Value;
    } else {
      StudentTemplate_B.Switch2 = StudentTemplate_B.Switch;
    }

    /* RelationalOperator: '<S157>/LowerRelop1' incorporates:
     *  Constant: '<S5>/y_dmax [m]'
     */
    StudentTemplate_B.LowerRelop1_e = (StudentTemplate_B.Add_n[1] >
      StudentTemplate_P.y_dmaxm_Value);

    /* RelationalOperator: '<S157>/UpperRelop' incorporates:
     *  Constant: '<S5>/y_dmin [m]'
     */
    StudentTemplate_B.UpperRelop_c = (StudentTemplate_B.Add_n[1] <
      StudentTemplate_P.y_dminm_Value);

    /* Switch: '<S157>/Switch' incorporates:
     *  Constant: '<S5>/y_dmin [m]'
     */
    if (StudentTemplate_B.UpperRelop_c) {
      StudentTemplate_B.Switch_e = StudentTemplate_P.y_dminm_Value;
    } else {
      StudentTemplate_B.Switch_e = StudentTemplate_B.Add_n[1];
    }

    /* Switch: '<S157>/Switch2' incorporates:
     *  Constant: '<S5>/y_dmax [m]'
     */
    if (StudentTemplate_B.LowerRelop1_e) {
      StudentTemplate_B.Switch2_j = StudentTemplate_P.y_dmaxm_Value;
    } else {
      StudentTemplate_B.Switch2_j = StudentTemplate_B.Switch_e;
    }

    /* Sum: '<S94>/Subtract' */
    StudentTemplate_B.Subtract[0] = StudentTemplate_B.Integrator_b[0] -
      StudentTemplate_B.Switch2;
    StudentTemplate_B.Subtract[1] = StudentTemplate_B.Integrator_b[1] -
      StudentTemplate_B.Switch2_j;

    /* Product: '<S105>/epsilon' */
    StudentTemplate_B.epsilon[0] = 0.0;
    StudentTemplate_B.epsilon[0] = StudentTemplate_B.MathFunction_h[0] *
      StudentTemplate_B.Subtract[0] + StudentTemplate_B.epsilon[0];
    StudentTemplate_B.epsilon[0] = StudentTemplate_B.MathFunction_h[2] *
      StudentTemplate_B.Subtract[1] + StudentTemplate_B.epsilon[0];
    StudentTemplate_B.epsilon[1] = 0.0;
    StudentTemplate_B.epsilon[1] = StudentTemplate_B.MathFunction_h[1] *
      StudentTemplate_B.Subtract[0] + StudentTemplate_B.epsilon[1];
    StudentTemplate_B.epsilon[1] = StudentTemplate_B.MathFunction_h[3] *
      StudentTemplate_B.Subtract[1] + StudentTemplate_B.epsilon[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector' */
    {
      const byte_T *u = (byte_T *)StudentTemplate_B.epsilon;/* input port */
      const int32_T *index = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&StudentTemplate_B.MultiportSelector;
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
    StudentTemplate_B.TrigonometricFunction_i = rt_atan2_snf
      (StudentTemplate_B.MultiportSelector, StudentTemplate_P.Deltam_Value);

    /* Saturate: '<S129>/Saturation' */
    tmp = StudentTemplate_B.TrigonometricFunction_i;
    StudentTemplate_B.Saturation_i = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_b,
      StudentTemplate_P.Saturation_UpperSat_e);

    /* Signum: '<S129>/Sign' */
    StudentTemplate_B.Sign_k = rt_SIGNd_snf(StudentTemplate_B.Saturation_i);

    /* Gain: '<S129>/Gain' */
    StudentTemplate_B.Gain_g = StudentTemplate_P.Gain_Gain_p *
      StudentTemplate_B.Sign_k;

    /* Sum: '<S129>/Sum1' */
    StudentTemplate_B.Sum1_h = StudentTemplate_B.Saturation_i +
      StudentTemplate_B.Gain_g;

    /* Math: '<S129>/Math Function' incorporates:
     *  Constant: '<S129>/Constant'
     */
    StudentTemplate_B.MathFunction_e4 = rt_rem_snf(StudentTemplate_B.Sum1_h,
      StudentTemplate_P.Constant_Value_g);

    /* Sum: '<S129>/Sum' */
    StudentTemplate_B.Sum_e = StudentTemplate_B.MathFunction_e4 -
      StudentTemplate_B.Gain_g;

    /* Sum: '<S122>/Subtract' */
    StudentTemplate_B.Subtract_h = StudentTemplate_B.Sum_i -
      StudentTemplate_B.Sum_e;

    /* Saturate: '<S130>/Saturation' */
    tmp = StudentTemplate_B.Subtract_h;
    StudentTemplate_B.Saturation_e = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_g,
      StudentTemplate_P.Saturation_UpperSat_d);

    /* Signum: '<S130>/Sign' */
    StudentTemplate_B.Sign_f = rt_SIGNd_snf(StudentTemplate_B.Saturation_e);

    /* Gain: '<S130>/Gain' */
    StudentTemplate_B.Gain_d = StudentTemplate_P.Gain_Gain_i *
      StudentTemplate_B.Sign_f;

    /* Sum: '<S130>/Sum1' */
    StudentTemplate_B.Sum1_g = StudentTemplate_B.Saturation_e +
      StudentTemplate_B.Gain_d;

    /* Math: '<S130>/Math Function' incorporates:
     *  Constant: '<S130>/Constant'
     */
    StudentTemplate_B.MathFunction_eb = rt_rem_snf(StudentTemplate_B.Sum1_g,
      StudentTemplate_P.Constant_Value_j);

    /* Sum: '<S130>/Sum' */
    StudentTemplate_B.Sum_ip = StudentTemplate_B.MathFunction_eb -
      StudentTemplate_B.Gain_d;

    /* SignalConversion: '<S106>/ConcatBufferAtVector ConcatenateIn2' */
    StudentTemplate_B.VectorConcatenate[2] = StudentTemplate_B.Sum_ip;

    /* Sum: '<S48>/Subtract' */
    StudentTemplate_B.Subtract_e[0] = StudentTemplate_B.etaSwitch[0] -
      StudentTemplate_B.VectorConcatenate[0];
    StudentTemplate_B.Subtract_e[1] = StudentTemplate_B.etaSwitch[1] -
      StudentTemplate_B.VectorConcatenate[1];
    StudentTemplate_B.Subtract_e[2] = StudentTemplate_B.Sum_n -
      StudentTemplate_B.VectorConcatenate[2];

    /* Saturate: '<S70>/Saturation' */
    tmp = StudentTemplate_B.Subtract_e[2];
    StudentTemplate_B.Saturation_g = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_e,
      StudentTemplate_P.Saturation_UpperSat_dd);

    /* Signum: '<S70>/Sign' */
    StudentTemplate_B.Sign_a = rt_SIGNd_snf(StudentTemplate_B.Saturation_g);

    /* Gain: '<S70>/Gain' */
    StudentTemplate_B.Gain_j = StudentTemplate_P.Gain_Gain_nr *
      StudentTemplate_B.Sign_a;

    /* Sum: '<S70>/Sum1' */
    StudentTemplate_B.Sum1_cz = StudentTemplate_B.Saturation_g +
      StudentTemplate_B.Gain_j;

    /* Math: '<S70>/Math Function' incorporates:
     *  Constant: '<S70>/Constant'
     */
    StudentTemplate_B.MathFunction_f = rt_rem_snf(StudentTemplate_B.Sum1_cz,
      StudentTemplate_P.Constant_Value_ig);

    /* Sum: '<S70>/Sum' */
    StudentTemplate_B.Sum_g = StudentTemplate_B.MathFunction_f -
      StudentTemplate_B.Gain_j;

    /* SignalConversion: '<S48>/TmpHiddenBufferAtProductInport2' */
    StudentTemplate_B.TmpHiddenBufferAtProductInpor_c[0] =
      StudentTemplate_B.Subtract_e[0];
    StudentTemplate_B.TmpHiddenBufferAtProductInpor_c[1] =
      StudentTemplate_B.Subtract_e[1];
    StudentTemplate_B.TmpHiddenBufferAtProductInpor_c[2] =
      StudentTemplate_B.Sum_g;

    /* Product: '<S48>/Product' */
    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product_bx[i] = 0.0;
      StudentTemplate_B.Product_bx[i] = StudentTemplate_B.MathFunction_a[i] *
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_c[0] +
        StudentTemplate_B.Product_bx[i];
      StudentTemplate_B.Product_bx[i] = StudentTemplate_B.MathFunction_a[i + 3] *
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_c[1] +
        StudentTemplate_B.Product_bx[i];
      StudentTemplate_B.Product_bx[i] = StudentTemplate_B.MathFunction_a[i + 6] *
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_c[2] +
        StudentTemplate_B.Product_bx[i];
    }

    /* Product: '<S44>/Product1' */
    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product1_l[i] = 0.0;
      StudentTemplate_B.Product1_l[i] = StudentTemplate_B.Add3[i] *
        StudentTemplate_B.Product_bx[0] + StudentTemplate_B.Product1_l[i];
      StudentTemplate_B.Product1_l[i] = StudentTemplate_B.Add3[i + 3] *
        StudentTemplate_B.Product_bx[1] + StudentTemplate_B.Product1_l[i];
      StudentTemplate_B.Product1_l[i] = StudentTemplate_B.Add3[i + 6] *
        StudentTemplate_B.Product_bx[2] + StudentTemplate_B.Product1_l[i];
    }

    /* Trigonometry: '<S107>/f_qx' */
    StudentTemplate_B.f_qx = cos(StudentTemplate_B.Sum_ip);

    /* Trigonometry: '<S107>/f_qy' */
    StudentTemplate_B.f_qy = sin(StudentTemplate_B.Sum_ip);

    /* SignalConversion: '<S107>/TmpHiddenBufferAtProductInport1' */
    StudentTemplate_B.TmpHiddenBufferAtProductInport1[0] =
      StudentTemplate_B.f_qx;
    StudentTemplate_B.TmpHiddenBufferAtProductInport1[1] =
      StudentTemplate_B.f_qy;

    /* Product: '<S107>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    StudentTemplate_B.Product_i[0] =
      StudentTemplate_B.TmpHiddenBufferAtProductInport1[0] *
      StudentTemplate_P.u_dm_Value;
    StudentTemplate_B.Product_i[1] =
      StudentTemplate_B.TmpHiddenBufferAtProductInport1[1] *
      StudentTemplate_P.u_dm_Value;

    /* SignalConversion: '<S51>/ConcatBufferAtVector ConcatenateIn1' */
    StudentTemplate_B.VectorConcatenate_e[0] = StudentTemplate_B.Product_i[0];
    StudentTemplate_B.VectorConcatenate_e[1] = StudentTemplate_B.Product_i[1];
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S123>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2 = tmp * tmp;
    }

    /* Math: '<S123>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2 = tmp * tmp;

    /* Sum: '<S123>/Add' */
    StudentTemplate_B.Add_g = StudentTemplate_B.Delta2 +
      StudentTemplate_B.epsilon_n2;

    /* Product: '<S123>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Divide_b = StudentTemplate_P.Deltam_Value /
      StudentTemplate_B.Add_g;

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector1' */
    {
      const byte_T *u = (byte_T *)StudentTemplate_B.MathFunction_h;/* input port */
      const int32_T *index = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)StudentTemplate_B.MultiportSelector1;
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
    StudentTemplate_B.Product_a[0] = StudentTemplate_B.Divide_b *
      StudentTemplate_B.MultiportSelector1[0];

    /* Gain: '<S123>/-1' */
    StudentTemplate_B.u_m[0] = StudentTemplate_P.u_Gain_c *
      StudentTemplate_B.Product_a[0];

    /* Product: '<S123>/Product' */
    StudentTemplate_B.Product_a[1] = StudentTemplate_B.Divide_b *
      StudentTemplate_B.MultiportSelector1[1];

    /* Gain: '<S123>/-1' */
    StudentTemplate_B.u_m[1] = StudentTemplate_P.u_Gain_c *
      StudentTemplate_B.Product_a[1];

    /* Product: '<S51>/Product' */
    tmp = StudentTemplate_B.u_m[0] * StudentTemplate_B.Product_i[0];
    tmp += StudentTemplate_B.u_m[1] * StudentTemplate_B.Product_i[1];
    StudentTemplate_B.VectorConcatenate_e[2] = tmp;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Constant: '<S57>/0_2x1' */
      StudentTemplate_B.VectorConcatenate_f[0] = StudentTemplate_P._2x1_Value[0];
      StudentTemplate_B.VectorConcatenate_f[1] = StudentTemplate_P._2x1_Value[1];

      /* Product: '<S153>/Product' incorporates:
       *  Constant: '<S143>/0_2x1'
       */
      StudentTemplate_B.Product_g[0] = StudentTemplate_P._2x1_Value_b[0] *
        StudentTemplate_B.RoundingFunction;
      StudentTemplate_B.Product_g[1] = StudentTemplate_P._2x1_Value_b[1] *
        StudentTemplate_B.RoundingFunction;
    }

    /* Product: '<S146>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    StudentTemplate_B.Product2_ld = StudentTemplate_B.Integrator1 *
      StudentTemplate_P.k_Value;

    /* Trigonometry: '<S146>/cos(s)' */
    StudentTemplate_B.coss_l = cos(StudentTemplate_B.Product2_ld);
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S146>/Math Function' incorporates:
       *  Constant: '<S10>/k [-]'
       */
      tmp = StudentTemplate_P.k_Value;
      StudentTemplate_B.MathFunction_o = tmp * tmp;
    }

    /* Product: '<S146>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    StudentTemplate_B.Product_p = StudentTemplate_P.r_xm_Value *
      StudentTemplate_B.coss_l * StudentTemplate_B.MathFunction_o;

    /* Gain: '<S146>/Gain' */
    StudentTemplate_B.Gain_m4 = StudentTemplate_P.Gain_Gain_o *
      StudentTemplate_B.Product_p;

    /* Trigonometry: '<S146>/sin(s)' */
    StudentTemplate_B.sins_h = sin(StudentTemplate_B.Product2_ld);

    /* Product: '<S146>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    StudentTemplate_B.Product1_l1 = StudentTemplate_P.r_ym_Value *
      StudentTemplate_B.sins_h * StudentTemplate_B.MathFunction_o;

    /* Gain: '<S146>/Gain1' */
    StudentTemplate_B.Gain1_e = StudentTemplate_P.Gain1_Gain_l *
      StudentTemplate_B.Product1_l1;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Sum: '<S153>/Subract' incorporates:
       *  Constant: '<S153>/Constant'
       */
      StudentTemplate_B.Subract_c = StudentTemplate_P.Constant_Value_f2 -
        StudentTemplate_B.RoundingFunction;
    }

    /* Product: '<S153>/Product1' */
    StudentTemplate_B.Product1_l4[0] = StudentTemplate_B.Gain_m4 *
      StudentTemplate_B.Subract_c;
    StudentTemplate_B.Product1_l4[1] = StudentTemplate_B.Gain1_e *
      StudentTemplate_B.Subract_c;

    /* Sum: '<S153>/Add' */
    StudentTemplate_B.Add_nm[0] = StudentTemplate_B.Product_g[0] +
      StudentTemplate_B.Product1_l4[0];
    StudentTemplate_B.Add_nm[1] = StudentTemplate_B.Product_g[1] +
      StudentTemplate_B.Product1_l4[1];

    /* Product: '<S98>/x_d^s * y_d^s^2' */
    StudentTemplate_B.x_dsy_ds2 = StudentTemplate_B.Add[0] *
      StudentTemplate_B.Add_nm[1];

    /* Product: '<S98>/x_d^s^2 * y_d^s' */
    StudentTemplate_B.x_ds2y_ds = StudentTemplate_B.Add_nm[0] *
      StudentTemplate_B.Add[1];

    /* Sum: '<S98>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
    StudentTemplate_B.x_dsy_ds2x_ds2y_ds = StudentTemplate_B.x_dsy_ds2 -
      StudentTemplate_B.x_ds2y_ds;

    /* Math: '<S98>/( x_d^s )^2' */
    tmp = StudentTemplate_B.Add[0];
    StudentTemplate_B.x_ds2 = tmp * tmp;

    /* Math: '<S98>/( y_d^s )^2' */
    tmp = StudentTemplate_B.Add[1];
    StudentTemplate_B.y_ds2 = tmp * tmp;

    /* Sum: '<S98>/( x_d^s )^2 + ( y_d^s )^2' */
    StudentTemplate_B.x_ds2y_ds2 = StudentTemplate_B.x_ds2 +
      StudentTemplate_B.y_ds2;

    /* Product: '<S98>/Divide' */
    StudentTemplate_B.Divide_j = StudentTemplate_B.x_dsy_ds2x_ds2y_ds /
      StudentTemplate_B.x_ds2y_ds2;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S126>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2_p = tmp * tmp;
    }

    /* Math: '<S126>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2_p = tmp * tmp;

    /* Sum: '<S126>/Add' */
    StudentTemplate_B.Add_nu = StudentTemplate_B.Delta2_p +
      StudentTemplate_B.epsilon_n2_p;

    /* Product: '<S126>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Divide_p = StudentTemplate_P.Deltam_Value /
      StudentTemplate_B.Add_nu;

    /* Outputs for atomic SubSystem: '<S105>/S_2' */

    /* Gain: '<S133>/S12' */
    StudentTemplate_B.S12_e = StudentTemplate_P.S12_Gain_h *
      StudentTemplate_B.Divide_j;

    /* Reshape: '<S133>/S_2(psi_d^s)' incorporates:
     *  Constant: '<S133>/0'
     */
    StudentTemplate_B.S_2psi_ds[0] = StudentTemplate_P._Value_m;
    StudentTemplate_B.S_2psi_ds[1] = StudentTemplate_B.Divide_j;
    StudentTemplate_B.S_2psi_ds[2] = StudentTemplate_B.S12_e;
    StudentTemplate_B.S_2psi_ds[3] = StudentTemplate_P._Value_m;

    /* end of Outputs for SubSystem: '<S105>/S_2' */

    /* Math: '<S136>/Math Function' */
    StudentTemplate_B.MathFunction_c[0] = StudentTemplate_B.S_2psi_ds[0];
    StudentTemplate_B.MathFunction_c[1] = StudentTemplate_B.S_2psi_ds[2];
    StudentTemplate_B.MathFunction_c[2] = StudentTemplate_B.S_2psi_ds[1];
    StudentTemplate_B.MathFunction_c[3] = StudentTemplate_B.S_2psi_ds[3];

    /* Product: '<S138>/Product' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += StudentTemplate_B.MathFunction_c[i] *
        StudentTemplate_B.MathFunction_h[0];
      tmp_2[i] += StudentTemplate_B.MathFunction_c[i + 2] *
        StudentTemplate_B.MathFunction_h[1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += StudentTemplate_B.MathFunction_c[i] *
        StudentTemplate_B.MathFunction_h[2];
      tmp_2[i + 2] += StudentTemplate_B.MathFunction_c[i + 2] *
        StudentTemplate_B.MathFunction_h[3];
    }

    StudentTemplate_B.Product_j[0] = 0.0;
    StudentTemplate_B.Product_j[0] = tmp_2[0] * StudentTemplate_B.Subtract[0] +
      StudentTemplate_B.Product_j[0];
    StudentTemplate_B.Product_j[0] = tmp_2[2] * StudentTemplate_B.Subtract[1] +
      StudentTemplate_B.Product_j[0];

    /* Product: '<S138>/Product1' */
    StudentTemplate_B.Product1_j[0] = 0.0;
    StudentTemplate_B.Product1_j[0] = StudentTemplate_B.MathFunction_h[0] *
      StudentTemplate_B.Add[0] + StudentTemplate_B.Product1_j[0];
    StudentTemplate_B.Product1_j[0] = StudentTemplate_B.MathFunction_h[2] *
      StudentTemplate_B.Add[1] + StudentTemplate_B.Product1_j[0];

    /* Sum: '<S138>/Subtract1' */
    StudentTemplate_B.Subtract1[0] = StudentTemplate_B.Product_j[0] -
      StudentTemplate_B.Product1_j[0];
    StudentTemplate_B.Product_j[1] = 0.0;
    StudentTemplate_B.Product_j[1] = tmp_2[1] * StudentTemplate_B.Subtract[0] +
      StudentTemplate_B.Product_j[1];
    StudentTemplate_B.Product_j[1] = tmp_2[3] * StudentTemplate_B.Subtract[1] +
      StudentTemplate_B.Product_j[1];

    /* Product: '<S138>/Product1' */
    StudentTemplate_B.Product1_j[1] = 0.0;
    StudentTemplate_B.Product1_j[1] = StudentTemplate_B.MathFunction_h[1] *
      StudentTemplate_B.Add[0] + StudentTemplate_B.Product1_j[1];
    StudentTemplate_B.Product1_j[1] = StudentTemplate_B.MathFunction_h[3] *
      StudentTemplate_B.Add[1] + StudentTemplate_B.Product1_j[1];

    /* Sum: '<S138>/Subtract1' */
    StudentTemplate_B.Subtract1[1] = StudentTemplate_B.Product_j[1] -
      StudentTemplate_B.Product1_j[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector2' */
    {
      const byte_T *u = (byte_T *)StudentTemplate_B.Subtract1;/* input port */
      const int32_T *index = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&StudentTemplate_B.MultiportSelector2;
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
    StudentTemplate_B.Product_i5 = StudentTemplate_B.Divide_p *
      StudentTemplate_B.MultiportSelector2;

    /* Sum: '<S126>/Subtract' */
    StudentTemplate_B.Subtract_n = StudentTemplate_B.Divide_j -
      StudentTemplate_B.Product_i5;

    /* Math: '<S111>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2_o = tmp * tmp;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S111>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2_l = tmp * tmp;
    }

    /* Sum: '<S111>/Add' */
    StudentTemplate_B.Add_o = StudentTemplate_B.epsilon_n2_o +
      StudentTemplate_B.Delta2_l;

    /* Math: '<S111>/sqrt' */
    tmp = StudentTemplate_B.Add_o;
    if (tmp < 0.0) {
      StudentTemplate_B.sqrt_i = -sqrt(-tmp);
    } else {
      StudentTemplate_B.sqrt_i = sqrt(tmp);
    }

    /* Product: '<S111>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Divide_l = StudentTemplate_P.Deltam_Value /
      StudentTemplate_B.sqrt_i;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S161>/Math Function' */
      StudentTemplate_B.MathFunction_l[0] =
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_e[0];
      StudentTemplate_B.MathFunction_l[1] =
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_e[1];

      /* Product: '<S160>/Product' */
      tmp = StudentTemplate_B.MathFunction_l[0] *
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_e[0];
      tmp += StudentTemplate_B.MathFunction_l[1] *
        StudentTemplate_B.TmpHiddenBufferAtProductInpor_e[1];
      StudentTemplate_B.Product_nk = tmp;

      /* Math: '<S160>/sqrt' */
      tmp = StudentTemplate_B.Product_nk;
      if (tmp < 0.0) {
        StudentTemplate_B.sqrt_d = -sqrt(-tmp);
      } else {
        StudentTemplate_B.sqrt_d = sqrt(tmp);
      }

      /* Product: '<S155>/Product' */
      StudentTemplate_B.Product_n4 = StudentTemplate_B.sqrt_d *
        StudentTemplate_B.RoundingFunction;
    }

    /* Math: '<S149>/Math Function' */
    StudentTemplate_B.MathFunction_p[0] =
      StudentTemplate_B.TmpHiddenBufferAtProductInpo_ds[0];
    StudentTemplate_B.MathFunction_p[1] =
      StudentTemplate_B.TmpHiddenBufferAtProductInpo_ds[1];

    /* Product: '<S148>/Product' */
    tmp = StudentTemplate_B.MathFunction_p[0] *
      StudentTemplate_B.TmpHiddenBufferAtProductInpo_ds[0];
    tmp += StudentTemplate_B.MathFunction_p[1] *
      StudentTemplate_B.TmpHiddenBufferAtProductInpo_ds[1];
    StudentTemplate_B.Product_jp = tmp;

    /* Math: '<S148>/sqrt' */
    tmp = StudentTemplate_B.Product_jp;
    if (tmp < 0.0) {
      StudentTemplate_B.sqrt_e = -sqrt(-tmp);
    } else {
      StudentTemplate_B.sqrt_e = sqrt(tmp);
    }

    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Sum: '<S155>/Subract' incorporates:
       *  Constant: '<S155>/Constant'
       */
      StudentTemplate_B.Subract_ab = StudentTemplate_P.Constant_Value_a -
        StudentTemplate_B.RoundingFunction;
    }

    /* Product: '<S155>/Product1' */
    StudentTemplate_B.Product1_p = StudentTemplate_B.sqrt_e *
      StudentTemplate_B.Subract_ab;

    /* Sum: '<S155>/Add' */
    StudentTemplate_B.Add_b = StudentTemplate_B.Product_n4 +
      StudentTemplate_B.Product1_p;

    /* Product: '<S162>/Divide' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    StudentTemplate_B.Divide_bz = StudentTemplate_P.u_dm_Value /
      StudentTemplate_B.Add_b;

    /* Product: '<S111>/Product' */
    StudentTemplate_B.Product_l = StudentTemplate_B.Divide_l *
      StudentTemplate_B.Divide_bz;

    /* Math: '<S118>/Math Function' */
    StudentTemplate_B.MathFunction_jv[0] = StudentTemplate_B.Add[0];

    /* Product: '<S115>/Divide' */
    StudentTemplate_B.Divide_lw[0] = StudentTemplate_B.MathFunction_jv[0] /
      StudentTemplate_B.Add_b;

    /* Math: '<S118>/Math Function' */
    StudentTemplate_B.MathFunction_jv[1] = StudentTemplate_B.Add[1];

    /* Product: '<S115>/Divide' */
    StudentTemplate_B.Divide_lw[1] = StudentTemplate_B.MathFunction_jv[1] /
      StudentTemplate_B.Add_b;

    /* Product: '<S115>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    tmp = StudentTemplate_P.my_Value * StudentTemplate_B.Divide_lw[0] *
      StudentTemplate_B.Subtract[0];
    tmp += StudentTemplate_P.my_Value * StudentTemplate_B.Divide_lw[1] *
      StudentTemplate_B.Subtract[1];
    StudentTemplate_B.Product_cl = tmp;

    /* Gain: '<S115>/Gain' */
    StudentTemplate_B.Gain_h = StudentTemplate_P.Gain_Gain_e *
      StudentTemplate_B.Product_cl;

    /* Sum: '<S111>/Subtract' */
    StudentTemplate_B.Subtract_f = StudentTemplate_B.Product_l -
      StudentTemplate_B.Gain_h;

    /* Product: '<S57>/Product' */
    StudentTemplate_B.VectorConcatenate_f[2] = StudentTemplate_B.Subtract_n *
      StudentTemplate_B.Subtract_f;

    /* Sum: '<S44>/Add' */
    StudentTemplate_B.Add_iy[0] = StudentTemplate_B.VectorConcatenate_e[0] +
      StudentTemplate_B.VectorConcatenate_f[0];
    StudentTemplate_B.Add_iy[1] = StudentTemplate_B.VectorConcatenate_e[1] +
      StudentTemplate_B.VectorConcatenate_f[1];
    StudentTemplate_B.Add_iy[2] = StudentTemplate_B.VectorConcatenate_e[2] +
      StudentTemplate_B.VectorConcatenate_f[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S44>/Product2' */
      StudentTemplate_B.Product2_o[i] = 0.0;
      StudentTemplate_B.Product2_o[i] = StudentTemplate_B.MathFunction_a[i] *
        StudentTemplate_B.Add_iy[0] + StudentTemplate_B.Product2_o[i];
      StudentTemplate_B.Product2_o[i] = StudentTemplate_B.MathFunction_a[i + 3] *
        StudentTemplate_B.Add_iy[1] + StudentTemplate_B.Product2_o[i];
      StudentTemplate_B.Product2_o[i] = StudentTemplate_B.MathFunction_a[i + 6] *
        StudentTemplate_B.Add_iy[2] + StudentTemplate_B.Product2_o[i];

      /* Sum: '<S44>/Sum' */
      StudentTemplate_B.Sum_o[i] = StudentTemplate_B.Product2_o[i] -
        StudentTemplate_B.Product1_l[i];

      /* Sum: '<S49>/Subtract' */
      StudentTemplate_B.Subtract_n5[i] = StudentTemplate_B.nuSwitch[i] -
        StudentTemplate_B.Sum_o[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S39>/Product1' */
      StudentTemplate_B.Product1_i[i] = 0.0;
      StudentTemplate_B.Product1_i[i] = StudentTemplate_B.Add1[i] *
        StudentTemplate_B.Subtract_n5[0] + StudentTemplate_B.Product1_i[i];
      StudentTemplate_B.Product1_i[i] = StudentTemplate_B.Add1[i + 3] *
        StudentTemplate_B.Subtract_n5[1] + StudentTemplate_B.Product1_i[i];
      StudentTemplate_B.Product1_i[i] = StudentTemplate_B.Add1[i + 6] *
        StudentTemplate_B.Subtract_n5[2] + StudentTemplate_B.Product1_i[i];

      /* Gain: '<S39>/Gain1' */
      StudentTemplate_B.Gain1_j[i] = StudentTemplate_P.Gain1_Gain_n *
        StudentTemplate_B.Product1_i[i];

      /* Product: '<S39>/Product2' */
      StudentTemplate_B.Product2_g[i] = 0.0;
      StudentTemplate_B.Product2_g[i] = StudentTemplate_B.LinearDampningmatrix[i]
        * StudentTemplate_B.nuSwitch[0] + StudentTemplate_B.Product2_g[i];
      StudentTemplate_B.Product2_g[i] = StudentTemplate_B.LinearDampningmatrix[i
        + 3] * StudentTemplate_B.nuSwitch[1] + StudentTemplate_B.Product2_g[i];
      StudentTemplate_B.Product2_g[i] = StudentTemplate_B.LinearDampningmatrix[i
        + 6] * StudentTemplate_B.nuSwitch[2] + StudentTemplate_B.Product2_g[i];
    }

    /* Gain: '<S65>/S12' */
    StudentTemplate_B.S12 = StudentTemplate_P.S12_Gain *
      StudentTemplate_B.nuSwitch[2];

    /* Reshape: '<S65>/S(r)' incorporates:
     *  Constant: '<S65>/R31'
     *  Constant: '<S65>/S11'
     *  Constant: '<S65>/S13'
     *  Constant: '<S65>/S22'
     *  Constant: '<S65>/S23'
     *  Constant: '<S65>/S32'
     *  Constant: '<S65>/S33'
     */
    StudentTemplate_B.Sr[0] = StudentTemplate_P.S11_Value;
    StudentTemplate_B.Sr[1] = StudentTemplate_B.nuSwitch[2];
    StudentTemplate_B.Sr[2] = StudentTemplate_P.R31_Value_g;
    StudentTemplate_B.Sr[3] = StudentTemplate_B.S12;
    StudentTemplate_B.Sr[4] = StudentTemplate_P.S22_Value;
    StudentTemplate_B.Sr[5] = StudentTemplate_P.S32_Value;
    StudentTemplate_B.Sr[6] = StudentTemplate_P.S13_Value;
    StudentTemplate_B.Sr[7] = StudentTemplate_P.S23_Value;
    StudentTemplate_B.Sr[8] = StudentTemplate_P.S33_Value;

    /* Math: '<S66>/Math Function' */
    for (i = 0; i < 3; i++) {
      StudentTemplate_B.MathFunction_jw[3 * i] = StudentTemplate_B.Sr[i];
      StudentTemplate_B.MathFunction_jw[1 + 3 * i] = StudentTemplate_B.Sr[i + 3];
      StudentTemplate_B.MathFunction_jw[2 + 3 * i] = StudentTemplate_B.Sr[i + 6];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product' */
      StudentTemplate_B.Product_f[i] = 0.0;
      StudentTemplate_B.Product_f[i] = StudentTemplate_B.MathFunction_jw[i] *
        StudentTemplate_B.Product_bx[0] + StudentTemplate_B.Product_f[i];
      StudentTemplate_B.Product_f[i] = StudentTemplate_B.MathFunction_jw[i + 3] *
        StudentTemplate_B.Product_bx[1] + StudentTemplate_B.Product_f[i];
      StudentTemplate_B.Product_f[i] = StudentTemplate_B.MathFunction_jw[i + 6] *
        StudentTemplate_B.Product_bx[2] + StudentTemplate_B.Product_f[i];

      /* Sum: '<S47>/Add' */
      StudentTemplate_B.Add_k[i] = StudentTemplate_B.Product_f[i] +
        StudentTemplate_B.nuSwitch[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product2' */
      StudentTemplate_B.Product2_f[i] = 0.0;
      StudentTemplate_B.Product2_f[i] = StudentTemplate_B.Add3[i] *
        StudentTemplate_B.Add_k[0] + StudentTemplate_B.Product2_f[i];
      StudentTemplate_B.Product2_f[i] = StudentTemplate_B.Add3[i + 3] *
        StudentTemplate_B.Add_k[1] + StudentTemplate_B.Product2_f[i];
      StudentTemplate_B.Product2_f[i] = StudentTemplate_B.Add3[i + 6] *
        StudentTemplate_B.Add_k[2] + StudentTemplate_B.Product2_f[i];

      /* Sum: '<S47>/Add1' */
      StudentTemplate_B.Add1_k[i] = StudentTemplate_B.VectorConcatenate_e[i] +
        StudentTemplate_B.VectorConcatenate_f[i];
    }

    /* Product: '<S47>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] +
          StudentTemplate_B.MathFunction_a[3 * tmp_6] *
          StudentTemplate_B.MathFunction_jw[i];
        tmp_1[i + 3 * tmp_6] = StudentTemplate_B.MathFunction_a[3 * tmp_6 + 1] *
          StudentTemplate_B.MathFunction_jw[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = StudentTemplate_B.MathFunction_a[3 * tmp_6 + 2] *
          StudentTemplate_B.MathFunction_jw[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product3[i] = 0.0;
      StudentTemplate_B.Product3[i] = tmp_1[i] * StudentTemplate_B.Add1_k[0] +
        StudentTemplate_B.Product3[i];
      StudentTemplate_B.Product3[i] = tmp_1[i + 3] * StudentTemplate_B.Add1_k[1]
        + StudentTemplate_B.Product3[i];
      StudentTemplate_B.Product3[i] = tmp_1[i + 6] * StudentTemplate_B.Add1_k[2]
        + StudentTemplate_B.Product3[i];
    }

    /* Trigonometry: '<S110>/Trigonometric Function' */
    StudentTemplate_B.TrigonometricFunction_p = cos(StudentTemplate_B.Sum_ip);

    /* Trigonometry: '<S110>/Trigonometric Function1' */
    StudentTemplate_B.TrigonometricFunction1 = sin(StudentTemplate_B.Sum_ip);

    /* Derivative Block: '<S96>/Derivative' */
    {
      real_T t = StudentTemplate_M->Timing.t[0];
      real_T timeStampA = StudentTemplate_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = StudentTemplate_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        StudentTemplate_B.Derivative = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &StudentTemplate_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 2;
          }
        } else if (timeStampA >= t) {
          lastBank += 2;
        }

        deltaT = t - *lastBank++;
        StudentTemplate_B.Derivative = (StudentTemplate_P.u_dm_Value - *lastBank
          ++) / deltaT;
      }
    }

    /* Product: '<S110>/Product' */
    StudentTemplate_B.Product_ir[0] = StudentTemplate_B.TrigonometricFunction_p *
      StudentTemplate_B.Derivative;
    StudentTemplate_B.Product_ir[1] = StudentTemplate_B.TrigonometricFunction1 *
      StudentTemplate_B.Derivative;

    /* SignalConversion: '<S54>/ConcatBufferAtVector ConcatenateIn1' */
    StudentTemplate_B.VectorConcatenate_c[0] = StudentTemplate_B.Product_ir[0];
    StudentTemplate_B.VectorConcatenate_c[1] = StudentTemplate_B.Product_ir[1];

    /* Product: '<S54>/Product1' */
    tmp = StudentTemplate_B.u_m[0] * StudentTemplate_B.Product_ir[0];
    tmp += StudentTemplate_B.u_m[1] * StudentTemplate_B.Product_ir[1];
    StudentTemplate_B.VectorConcatenate_c[2] = tmp;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Constant: '<S60>/0_2x1' */
      StudentTemplate_B.VectorConcatenate_o[0] = StudentTemplate_P._2x1_Value_a
        [0];
      StudentTemplate_B.VectorConcatenate_o[1] = StudentTemplate_P._2x1_Value_a
        [1];
    }

    /* Math: '<S114>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2_n = tmp * tmp;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S114>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2_e = tmp * tmp;
    }

    /* Sum: '<S114>/Add' */
    StudentTemplate_B.Add_m = StudentTemplate_B.epsilon_n2_n +
      StudentTemplate_B.Delta2_e;

    /* Math: '<S114>/sqrt' */
    tmp = StudentTemplate_B.Add_m;
    if (tmp < 0.0) {
      StudentTemplate_B.sqrt_f = -sqrt(-tmp);
    } else {
      StudentTemplate_B.sqrt_f = sqrt(tmp);
    }

    /* Product: '<S114>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Divide_be = StudentTemplate_P.Deltam_Value /
      StudentTemplate_B.sqrt_f;

    /* Product: '<S164>/Divide' */
    StudentTemplate_B.Divide_i = StudentTemplate_B.Derivative /
      StudentTemplate_B.Add_b;

    /* Product: '<S114>/Product' */
    StudentTemplate_B.Product_f5 = StudentTemplate_B.Divide_be *
      StudentTemplate_B.Divide_i;

    /* Product: '<S60>/Product1' */
    StudentTemplate_B.VectorConcatenate_o[2] = StudentTemplate_B.Subtract_n *
      StudentTemplate_B.Product_f5;

    /* Sum: '<S47>/Add2' */
    StudentTemplate_B.Add2[0] = StudentTemplate_B.VectorConcatenate_c[0] +
      StudentTemplate_B.VectorConcatenate_o[0];
    StudentTemplate_B.Add2[1] = StudentTemplate_B.VectorConcatenate_c[1] +
      StudentTemplate_B.VectorConcatenate_o[1];
    StudentTemplate_B.Add2[2] = StudentTemplate_B.VectorConcatenate_c[2] +
      StudentTemplate_B.VectorConcatenate_o[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product4' */
      StudentTemplate_B.Product4[i] = 0.0;
      StudentTemplate_B.Product4[i] = StudentTemplate_B.MathFunction_a[i] *
        StudentTemplate_B.Add2[0] + StudentTemplate_B.Product4[i];
      StudentTemplate_B.Product4[i] = StudentTemplate_B.MathFunction_a[i + 3] *
        StudentTemplate_B.Add2[1] + StudentTemplate_B.Product4[i];
      StudentTemplate_B.Product4[i] = StudentTemplate_B.MathFunction_a[i + 6] *
        StudentTemplate_B.Add2[2] + StudentTemplate_B.Product4[i];

      /* Sum: '<S47>/Sum' */
      StudentTemplate_B.Sum_io[i] = (StudentTemplate_B.Product3[i] -
        StudentTemplate_B.Product2_f[i]) + StudentTemplate_B.Product4[i];
    }

    /* Product: '<S39>/Product4' */
    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product4_p[i] = 0.0;
      StudentTemplate_B.Product4_p[i] = StudentTemplate_B.x3[i] *
        StudentTemplate_B.Sum_io[0] + StudentTemplate_B.Product4_p[i];
      StudentTemplate_B.Product4_p[i] = StudentTemplate_B.x3[i + 3] *
        StudentTemplate_B.Sum_io[1] + StudentTemplate_B.Product4_p[i];
      StudentTemplate_B.Product4_p[i] = StudentTemplate_B.x3[i + 6] *
        StudentTemplate_B.Sum_io[2] + StudentTemplate_B.Product4_p[i];
    }

    /* Concatenate: '<S106>/Matrix Concatenate' incorporates:
     *  Constant: '<S140>/Constant'
     */
    StudentTemplate_B.MatrixConcatenate[0] =
      StudentTemplate_P.Constant_Value_mk[0];
    StudentTemplate_B.MatrixConcatenate[1] =
      StudentTemplate_P.Constant_Value_mk[1];
    StudentTemplate_B.MatrixConcatenate[3] =
      StudentTemplate_P.Constant_Value_mk[2];
    StudentTemplate_B.MatrixConcatenate[4] =
      StudentTemplate_P.Constant_Value_mk[3];
    StudentTemplate_B.MatrixConcatenate[2] = StudentTemplate_B.u_m[0];
    StudentTemplate_B.MatrixConcatenate[5] = StudentTemplate_B.u_m[1];

    /* Product: '<S45>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] +
          StudentTemplate_B.MathFunction_a[3 * tmp_6] * StudentTemplate_B.Add3[i];
        tmp_1[i + 3 * tmp_6] = StudentTemplate_B.MathFunction_a[3 * tmp_6 + 1] *
          StudentTemplate_B.Add3[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = StudentTemplate_B.MathFunction_a[3 * tmp_6 + 2] *
          StudentTemplate_B.Add3[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        StudentTemplate_B.Product3_b[i + 3 * tmp_6] = 0.0;
        StudentTemplate_B.Product3_b[i + 3 * tmp_6] =
          StudentTemplate_B.Product3_b[3 * tmp_6 + i] +
          StudentTemplate_B.MatrixConcatenate[3 * tmp_6] * tmp_1[i];
        StudentTemplate_B.Product3_b[i + 3 * tmp_6] =
          StudentTemplate_B.MatrixConcatenate[3 * tmp_6 + 1] * tmp_1[i + 3] +
          StudentTemplate_B.Product3_b[3 * tmp_6 + i];
        StudentTemplate_B.Product3_b[i + 3 * tmp_6] =
          StudentTemplate_B.MatrixConcatenate[3 * tmp_6 + 2] * tmp_1[i + 6] +
          StudentTemplate_B.Product3_b[3 * tmp_6 + i];
      }
    }

    /* Trigonometry: '<S108>/Trigonometric Function1' */
    StudentTemplate_B.TrigonometricFunction1_h = sin(StudentTemplate_B.Sum_ip);

    /* Gain: '<S108>/Gain' */
    StudentTemplate_B.Gain_o = StudentTemplate_P.Gain_Gain_i4 *
      StudentTemplate_B.TrigonometricFunction1_h;

    /* Trigonometry: '<S108>/Trigonometric Function' */
    StudentTemplate_B.TrigonometricFunction_k = cos(StudentTemplate_B.Sum_ip);

    /* Product: '<S108>/Product1' */
    StudentTemplate_B.Product1_b[0] = StudentTemplate_B.Gain_o *
      StudentTemplate_B.u_m[0];

    /* Product: '<S108>/Product2' */
    StudentTemplate_B.Product2_d[0] = StudentTemplate_B.TrigonometricFunction_k *
      StudentTemplate_B.u_m[0];

    /* Product: '<S108>/Product1' */
    StudentTemplate_B.Product1_b[1] = StudentTemplate_B.Gain_o *
      StudentTemplate_B.u_m[1];

    /* Product: '<S108>/Product2' */
    StudentTemplate_B.Product2_d[1] = StudentTemplate_B.TrigonometricFunction_k *
      StudentTemplate_B.u_m[1];

    /* Concatenate: '<S108>/Matrix Concatenate' */
    StudentTemplate_B.MatrixConcatenate_d[0] = StudentTemplate_B.Product1_b[0];
    StudentTemplate_B.MatrixConcatenate_d[2] = StudentTemplate_B.Product1_b[1];
    StudentTemplate_B.MatrixConcatenate_d[1] = StudentTemplate_B.Product2_d[0];
    StudentTemplate_B.MatrixConcatenate_d[3] = StudentTemplate_B.Product2_d[1];

    /* Product: '<S108>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    StudentTemplate_B.Product_f4[0] = StudentTemplate_B.MatrixConcatenate_d[0] *
      StudentTemplate_P.u_dm_Value;
    StudentTemplate_B.Product_f4[1] = StudentTemplate_B.MatrixConcatenate_d[1] *
      StudentTemplate_P.u_dm_Value;
    StudentTemplate_B.Product_f4[2] = StudentTemplate_B.MatrixConcatenate_d[2] *
      StudentTemplate_P.u_dm_Value;
    StudentTemplate_B.Product_f4[3] = StudentTemplate_B.MatrixConcatenate_d[3] *
      StudentTemplate_P.u_dm_Value;

    /* Product: '<S124>/Product2' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product2_h = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.MultiportSelector;

    /* Math: '<S55>/Math Function' */
    StudentTemplate_B.MathFunction_b[0] = StudentTemplate_B.Product_i[0];

    /* Math: '<S124>/Math Function' */
    StudentTemplate_B.MathFunction_es[0] = StudentTemplate_B.MultiportSelector1
      [0];

    /* Math: '<S55>/Math Function' */
    StudentTemplate_B.MathFunction_b[1] = StudentTemplate_B.Product_i[1];

    /* Math: '<S124>/Math Function' */
    StudentTemplate_B.MathFunction_es[1] = StudentTemplate_B.MultiportSelector1
      [1];

    /* Product: '<S124>/Product3' */
    StudentTemplate_B.Product3_e[0] = 0.0;
    StudentTemplate_B.Product3_e[0] = StudentTemplate_B.MathFunction_es[0] *
      StudentTemplate_B.MultiportSelector1[0] + StudentTemplate_B.Product3_e[0];
    StudentTemplate_B.Product3_e[2] = 0.0;
    StudentTemplate_B.Product3_e[2] = StudentTemplate_B.MathFunction_es[0] *
      StudentTemplate_B.MultiportSelector1[1] + StudentTemplate_B.Product3_e[2];
    StudentTemplate_B.Product3_e[1] = 0.0;
    StudentTemplate_B.Product3_e[1] = StudentTemplate_B.MathFunction_es[1] *
      StudentTemplate_B.MultiportSelector1[0] + StudentTemplate_B.Product3_e[1];
    StudentTemplate_B.Product3_e[3] = 0.0;
    StudentTemplate_B.Product3_e[3] = StudentTemplate_B.MathFunction_es[1] *
      StudentTemplate_B.MultiportSelector1[1] + StudentTemplate_B.Product3_e[3];

    /* Product: '<S124>/Product4' */
    StudentTemplate_B.Product4_pk[0] = StudentTemplate_B.Product2_h *
      StudentTemplate_B.Product3_e[0];

    /* Gain: '<S124>/2' */
    StudentTemplate_B.u_e[0] = StudentTemplate_P._Gain_i *
      StudentTemplate_B.Product4_pk[0];

    /* Product: '<S124>/Product4' */
    StudentTemplate_B.Product4_pk[1] = StudentTemplate_B.Product2_h *
      StudentTemplate_B.Product3_e[1];

    /* Gain: '<S124>/2' */
    StudentTemplate_B.u_e[1] = StudentTemplate_P._Gain_i *
      StudentTemplate_B.Product4_pk[1];

    /* Product: '<S124>/Product4' */
    StudentTemplate_B.Product4_pk[2] = StudentTemplate_B.Product2_h *
      StudentTemplate_B.Product3_e[2];

    /* Gain: '<S124>/2' */
    StudentTemplate_B.u_e[2] = StudentTemplate_P._Gain_i *
      StudentTemplate_B.Product4_pk[2];

    /* Product: '<S124>/Product4' */
    StudentTemplate_B.Product4_pk[3] = StudentTemplate_B.Product2_h *
      StudentTemplate_B.Product3_e[3];

    /* Gain: '<S124>/2' */
    StudentTemplate_B.u_e[3] = StudentTemplate_P._Gain_i *
      StudentTemplate_B.Product4_pk[3];
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S124>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2_h = tmp * tmp;
    }

    /* Math: '<S124>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2_m = tmp * tmp;

    /* Sum: '<S124>/Add' */
    StudentTemplate_B.Add_l = StudentTemplate_B.Delta2_h +
      StudentTemplate_B.epsilon_n2_m;

    /* Math: '<S124>/( )^2' */
    tmp = StudentTemplate_B.Add_l;
    StudentTemplate_B.u_g = tmp * tmp;

    /* Product: '<S124>/Divide' */
    StudentTemplate_B.Divide_d[0] = StudentTemplate_B.u_e[0] /
      StudentTemplate_B.u_g;
    StudentTemplate_B.Divide_d[1] = StudentTemplate_B.u_e[1] /
      StudentTemplate_B.u_g;
    StudentTemplate_B.Divide_d[2] = StudentTemplate_B.u_e[2] /
      StudentTemplate_B.u_g;
    StudentTemplate_B.Divide_d[3] = StudentTemplate_B.u_e[3] /
      StudentTemplate_B.u_g;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Product: '<S124>/Product1' incorporates:
       *  Constant: '<S105>/0_2x2'
       *  Constant: '<S5>/Delta [m]'
       */
      StudentTemplate_B.Product1_li[0] = StudentTemplate_P.Deltam_Value *
        StudentTemplate_P._2x2_Value[0];
      StudentTemplate_B.Product1_li[1] = StudentTemplate_P.Deltam_Value *
        StudentTemplate_P._2x2_Value[1];
      StudentTemplate_B.Product1_li[2] = StudentTemplate_P.Deltam_Value *
        StudentTemplate_P._2x2_Value[2];
      StudentTemplate_B.Product1_li[3] = StudentTemplate_P.Deltam_Value *
        StudentTemplate_P._2x2_Value[3];
    }

    /* Product: '<S124>/Divide1' */
    StudentTemplate_B.Divide1[0] = StudentTemplate_B.Product1_li[0] /
      StudentTemplate_B.Add_l;

    /* Sum: '<S124>/Subtract' */
    StudentTemplate_B.Subtract_o[0] = StudentTemplate_B.Divide_d[0] -
      StudentTemplate_B.Divide1[0];

    /* Product: '<S124>/Divide1' */
    StudentTemplate_B.Divide1[1] = StudentTemplate_B.Product1_li[1] /
      StudentTemplate_B.Add_l;

    /* Sum: '<S124>/Subtract' */
    StudentTemplate_B.Subtract_o[1] = StudentTemplate_B.Divide_d[1] -
      StudentTemplate_B.Divide1[1];

    /* Product: '<S124>/Divide1' */
    StudentTemplate_B.Divide1[2] = StudentTemplate_B.Product1_li[2] /
      StudentTemplate_B.Add_l;

    /* Sum: '<S124>/Subtract' */
    StudentTemplate_B.Subtract_o[2] = StudentTemplate_B.Divide_d[2] -
      StudentTemplate_B.Divide1[2];

    /* Product: '<S124>/Divide1' */
    StudentTemplate_B.Divide1[3] = StudentTemplate_B.Product1_li[3] /
      StudentTemplate_B.Add_l;

    /* Sum: '<S124>/Subtract' */
    StudentTemplate_B.Subtract_o[3] = StudentTemplate_B.Divide_d[3] -
      StudentTemplate_B.Divide1[3];

    /* Math: '<S56>/Math Function' */
    StudentTemplate_B.MathFunction_cd[0] = StudentTemplate_B.Subtract_o[0];
    StudentTemplate_B.MathFunction_cd[1] = StudentTemplate_B.Subtract_o[2];
    StudentTemplate_B.MathFunction_cd[2] = StudentTemplate_B.Subtract_o[1];
    StudentTemplate_B.MathFunction_cd[3] = StudentTemplate_B.Subtract_o[3];

    /* Product: '<S52>/Product' */
    StudentTemplate_B.Product_ga[0] = 0.0;
    StudentTemplate_B.Product_ga[0] = StudentTemplate_B.MathFunction_b[0] *
      StudentTemplate_B.MathFunction_cd[0] + StudentTemplate_B.Product_ga[0];
    StudentTemplate_B.Product_ga[0] = StudentTemplate_B.MathFunction_b[1] *
      StudentTemplate_B.MathFunction_cd[1] + StudentTemplate_B.Product_ga[0];

    /* Product: '<S52>/Product1' */
    StudentTemplate_B.Product1_ii[0] = 0.0;
    StudentTemplate_B.Product1_ii[0] = StudentTemplate_B.u_m[0] *
      StudentTemplate_B.Product_f4[0] + StudentTemplate_B.Product1_ii[0];
    StudentTemplate_B.Product1_ii[0] = StudentTemplate_B.u_m[1] *
      StudentTemplate_B.Product_f4[1] + StudentTemplate_B.Product1_ii[0];

    /* Sum: '<S52>/Add' */
    StudentTemplate_B.Add_h[0] = StudentTemplate_B.Product_ga[0] +
      StudentTemplate_B.Product1_ii[0];

    /* Product: '<S52>/Product' */
    StudentTemplate_B.Product_ga[1] = 0.0;
    StudentTemplate_B.Product_ga[1] = StudentTemplate_B.MathFunction_b[0] *
      StudentTemplate_B.MathFunction_cd[2] + StudentTemplate_B.Product_ga[1];
    StudentTemplate_B.Product_ga[1] = StudentTemplate_B.MathFunction_b[1] *
      StudentTemplate_B.MathFunction_cd[3] + StudentTemplate_B.Product_ga[1];

    /* Product: '<S52>/Product1' */
    StudentTemplate_B.Product1_ii[1] = 0.0;
    StudentTemplate_B.Product1_ii[1] = StudentTemplate_B.u_m[0] *
      StudentTemplate_B.Product_f4[2] + StudentTemplate_B.Product1_ii[1];
    StudentTemplate_B.Product1_ii[1] = StudentTemplate_B.u_m[1] *
      StudentTemplate_B.Product_f4[3] + StudentTemplate_B.Product1_ii[1];

    /* Sum: '<S52>/Add' */
    StudentTemplate_B.Add_h[1] = StudentTemplate_B.Product_ga[1] +
      StudentTemplate_B.Product1_ii[1];

    /* Concatenate: '<S52>/Matrix Concatenate' */
    StudentTemplate_B.MatrixConcatenate_k[0] = StudentTemplate_B.Product_f4[0];
    StudentTemplate_B.MatrixConcatenate_k[1] = StudentTemplate_B.Product_f4[1];
    StudentTemplate_B.MatrixConcatenate_k[3] = StudentTemplate_B.Product_f4[2];
    StudentTemplate_B.MatrixConcatenate_k[4] = StudentTemplate_B.Product_f4[3];
    StudentTemplate_B.MatrixConcatenate_k[2] = StudentTemplate_B.Add_h[0];
    StudentTemplate_B.MatrixConcatenate_k[5] = StudentTemplate_B.Add_h[1];

    /* Product: '<S125>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product_iz[0] = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.MultiportSelector * StudentTemplate_B.MultiportSelector2
      * StudentTemplate_B.MultiportSelector1[0];

    /* Gain: '<S125>/2' */
    StudentTemplate_B.u_f[0] = StudentTemplate_P._Gain_p *
      StudentTemplate_B.Product_iz[0];

    /* Product: '<S125>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product_iz[1] = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.MultiportSelector * StudentTemplate_B.MultiportSelector2
      * StudentTemplate_B.MultiportSelector1[1];

    /* Gain: '<S125>/2' */
    StudentTemplate_B.u_f[1] = StudentTemplate_P._Gain_p *
      StudentTemplate_B.Product_iz[1];
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S125>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2_g = tmp * tmp;
    }

    /* Math: '<S125>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2_o1 = tmp * tmp;

    /* Sum: '<S125>/Add' */
    StudentTemplate_B.Add_nf = StudentTemplate_B.Delta2_g +
      StudentTemplate_B.epsilon_n2_o1;

    /* Math: '<S125>/( )^2' */
    tmp = StudentTemplate_B.Add_nf;
    StudentTemplate_B.u_ey = tmp * tmp;

    /* Product: '<S125>/Divide' */
    StudentTemplate_B.Divide_o[0] = StudentTemplate_B.u_f[0] /
      StudentTemplate_B.u_ey;
    StudentTemplate_B.Divide_o[1] = StudentTemplate_B.u_f[1] /
      StudentTemplate_B.u_ey;

    /* Product: '<S137>/Product1' */
    for (i = 0; i < 2; i++) {
      StudentTemplate_B.Product1_mv[i] = 0.0;
      StudentTemplate_B.Product1_mv[i] = StudentTemplate_B.MathFunction_c[i] *
        StudentTemplate_B.MathFunction_h[0] + StudentTemplate_B.Product1_mv[i];
      StudentTemplate_B.Product1_mv[i] = StudentTemplate_B.MathFunction_c[i + 2]
        * StudentTemplate_B.MathFunction_h[1] + StudentTemplate_B.Product1_mv[i];
      StudentTemplate_B.Product1_mv[i + 2] = 0.0;
      StudentTemplate_B.Product1_mv[i + 2] = StudentTemplate_B.Product1_mv[i + 2]
        + StudentTemplate_B.MathFunction_c[i] *
        StudentTemplate_B.MathFunction_h[2];
      StudentTemplate_B.Product1_mv[i + 2] = StudentTemplate_B.MathFunction_c[i
        + 2] * StudentTemplate_B.MathFunction_h[3] +
        StudentTemplate_B.Product1_mv[i + 2];
    }

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector3' */
    {
      const byte_T *u = (byte_T *)StudentTemplate_B.Product1_mv;/* input port */
      const int32_T *index = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)StudentTemplate_B.MultiportSelector3;
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
    StudentTemplate_B.Product1_bq[0] = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.MultiportSelector3[0];

    /* Product: '<S125>/Divide1' */
    StudentTemplate_B.Divide1_p[0] = StudentTemplate_B.Product1_bq[0] /
      StudentTemplate_B.Add_nf;

    /* Sum: '<S125>/Subtract' */
    StudentTemplate_B.Subtract_b[0] = StudentTemplate_B.Divide_o[0] -
      StudentTemplate_B.Divide1_p[0];

    /* Product: '<S58>/Product' */
    StudentTemplate_B.Product_l2[0] = StudentTemplate_B.Subtract_b[0] *
      StudentTemplate_B.Subtract_f;

    /* Product: '<S112>/Product1' */
    StudentTemplate_B.Product1_k[0] = StudentTemplate_B.MultiportSelector *
      StudentTemplate_B.MultiportSelector1[0];

    /* Product: '<S125>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product1_bq[1] = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.MultiportSelector3[1];

    /* Product: '<S125>/Divide1' */
    StudentTemplate_B.Divide1_p[1] = StudentTemplate_B.Product1_bq[1] /
      StudentTemplate_B.Add_nf;

    /* Sum: '<S125>/Subtract' */
    StudentTemplate_B.Subtract_b[1] = StudentTemplate_B.Divide_o[1] -
      StudentTemplate_B.Divide1_p[1];

    /* Product: '<S58>/Product' */
    StudentTemplate_B.Product_l2[1] = StudentTemplate_B.Subtract_b[1] *
      StudentTemplate_B.Subtract_f;

    /* Product: '<S112>/Product1' */
    StudentTemplate_B.Product1_k[1] = StudentTemplate_B.MultiportSelector *
      StudentTemplate_B.MultiportSelector1[1];

    /* Math: '<S112>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2_m5 = tmp * tmp;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S112>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2_o = tmp * tmp;
    }

    /* Sum: '<S112>/Add' */
    StudentTemplate_B.Add_ba = StudentTemplate_B.epsilon_n2_m5 +
      StudentTemplate_B.Delta2_o;

    /* Math: '<S112>/^3//2' incorporates:
     *  Constant: '<S112>/3//2'
     */
    if ((StudentTemplate_B.Add_ba < 0.0) && (StudentTemplate_P.u_Value_b2 >
         floor(StudentTemplate_P.u_Value_b2))) {
      StudentTemplate_B.u2 = -rt_pow_snf(-StudentTemplate_B.Add_ba,
        StudentTemplate_P.u_Value_b2);
    } else {
      StudentTemplate_B.u2 = rt_pow_snf(StudentTemplate_B.Add_ba,
        StudentTemplate_P.u_Value_b2);
    }

    /* Product: '<S112>/Divide' */
    StudentTemplate_B.Divide_j0[0] = StudentTemplate_B.Product1_k[0] /
      StudentTemplate_B.u2;

    /* Product: '<S112>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product_jh[0] = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.Divide_j0[0] * StudentTemplate_B.Divide_bz;

    /* Math: '<S119>/Math Function' */
    StudentTemplate_B.MathFunction_cy[0] = StudentTemplate_B.Add[0];

    /* Product: '<S116>/Divide' */
    StudentTemplate_B.Divide_a[0] = StudentTemplate_B.MathFunction_cy[0] /
      StudentTemplate_B.Add_b;

    /* Product: '<S116>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    StudentTemplate_B.Product_mp[0] = StudentTemplate_P.my_Value *
      StudentTemplate_B.Divide_a[0];

    /* Gain: '<S116>/Gain' */
    StudentTemplate_B.Gain_b[0] = StudentTemplate_P.Gain_Gain_k *
      StudentTemplate_B.Product_mp[0];

    /* Sum: '<S112>/Sum' */
    StudentTemplate_B.Sum_ow[0] = (0.0 - StudentTemplate_B.Product_jh[0]) -
      StudentTemplate_B.Gain_b[0];

    /* Product: '<S58>/Product1' */
    StudentTemplate_B.Product1_o[0] = StudentTemplate_B.Subtract_n *
      StudentTemplate_B.Sum_ow[0];

    /* Sum: '<S58>/Add' */
    StudentTemplate_B.Add_g3[0] = StudentTemplate_B.Product_l2[0] +
      StudentTemplate_B.Product1_o[0];

    /* Product: '<S112>/Divide' */
    StudentTemplate_B.Divide_j0[1] = StudentTemplate_B.Product1_k[1] /
      StudentTemplate_B.u2;

    /* Product: '<S112>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product_jh[1] = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.Divide_j0[1] * StudentTemplate_B.Divide_bz;

    /* Math: '<S119>/Math Function' */
    StudentTemplate_B.MathFunction_cy[1] = StudentTemplate_B.Add[1];

    /* Product: '<S116>/Divide' */
    StudentTemplate_B.Divide_a[1] = StudentTemplate_B.MathFunction_cy[1] /
      StudentTemplate_B.Add_b;

    /* Product: '<S116>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    StudentTemplate_B.Product_mp[1] = StudentTemplate_P.my_Value *
      StudentTemplate_B.Divide_a[1];

    /* Gain: '<S116>/Gain' */
    StudentTemplate_B.Gain_b[1] = StudentTemplate_P.Gain_Gain_k *
      StudentTemplate_B.Product_mp[1];

    /* Sum: '<S112>/Sum' */
    StudentTemplate_B.Sum_ow[1] = (0.0 - StudentTemplate_B.Product_jh[1]) -
      StudentTemplate_B.Gain_b[1];

    /* Product: '<S58>/Product1' */
    StudentTemplate_B.Product1_o[1] = StudentTemplate_B.Subtract_n *
      StudentTemplate_B.Sum_ow[1];

    /* Sum: '<S58>/Add' */
    StudentTemplate_B.Add_g3[1] = StudentTemplate_B.Product_l2[1] +
      StudentTemplate_B.Product1_o[1];

    /* Concatenate: '<S58>/Matrix Concatenate' incorporates:
     *  Constant: '<S58>/0_2x2'
     */
    StudentTemplate_B.MatrixConcatenate_p[0] = StudentTemplate_P._2x2_Value_l[0];
    StudentTemplate_B.MatrixConcatenate_p[1] = StudentTemplate_P._2x2_Value_l[1];
    StudentTemplate_B.MatrixConcatenate_p[3] = StudentTemplate_P._2x2_Value_l[2];
    StudentTemplate_B.MatrixConcatenate_p[4] = StudentTemplate_P._2x2_Value_l[3];
    StudentTemplate_B.MatrixConcatenate_p[2] = StudentTemplate_B.Add_g3[0];
    StudentTemplate_B.MatrixConcatenate_p[5] = StudentTemplate_B.Add_g3[1];

    /* Sum: '<S45>/Add2' */
    for (i = 0; i < 6; i++) {
      StudentTemplate_B.Add2_d[i] = StudentTemplate_B.MatrixConcatenate_k[i] +
        StudentTemplate_B.MatrixConcatenate_p[i];
    }

    /* Product: '<S45>/Product4' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        StudentTemplate_B.Product4_k[i + 3 * tmp_6] = 0.0;
        StudentTemplate_B.Product4_k[i + 3 * tmp_6] =
          StudentTemplate_B.Product4_k[3 * tmp_6 + i] +
          StudentTemplate_B.Add2_d[3 * tmp_6] *
          StudentTemplate_B.MathFunction_a[i];
        StudentTemplate_B.Product4_k[i + 3 * tmp_6] = StudentTemplate_B.Add2_d[3
          * tmp_6 + 1] * StudentTemplate_B.MathFunction_a[i + 3] +
          StudentTemplate_B.Product4_k[3 * tmp_6 + i];
        StudentTemplate_B.Product4_k[i + 3 * tmp_6] = StudentTemplate_B.Add2_d[3
          * tmp_6 + 2] * StudentTemplate_B.MathFunction_a[i + 6] +
          StudentTemplate_B.Product4_k[3 * tmp_6 + i];
      }
    }

    /* Sum: '<S45>/Add3' */
    for (i = 0; i < 6; i++) {
      StudentTemplate_B.Add3_p[i] = StudentTemplate_B.Product3_b[i] +
        StudentTemplate_B.Product4_k[i];
    }

    /* Integrator Block: '<S42>/Integrator2'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &StudentTemplate_PrevZCSigState.Integrator2_Reset_ZCE,
                         StudentTemplate_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || StudentTemplate_P.ctrl2ResetIntegrator_Value != 0.0) {
        StudentTemplate_X.Integrator2_CSTATE[0] =
          StudentTemplate_P.Integrator2_IC;
        StudentTemplate_X.Integrator2_CSTATE[1] =
          StudentTemplate_P.Integrator2_IC;
      }
    }

    StudentTemplate_B.Integrator2[0] = StudentTemplate_X.Integrator2_CSTATE[0];
    StudentTemplate_B.Integrator2[1] = StudentTemplate_X.Integrator2_CSTATE[1];

    /* Sum: '<S39>/Add2' */
    StudentTemplate_B.Add2_f[0] = StudentTemplate_B.Integrator2[0] +
      StudentTemplate_B.Product_i[0];
    StudentTemplate_B.Add2_f[1] = StudentTemplate_B.Integrator2[1] +
      StudentTemplate_B.Product_i[1];

    /* Product: '<S39>/Product5' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        tmp_3[i + 3 * tmp_6] = 0.0;
        tmp_3[i + 3 * tmp_6] = tmp_3[3 * tmp_6 + i] + StudentTemplate_B.Add3_p[3
          * tmp_6] * StudentTemplate_B.x3[i];
        tmp_3[i + 3 * tmp_6] = StudentTemplate_B.Add3_p[3 * tmp_6 + 1] *
          StudentTemplate_B.x3[i + 3] + tmp_3[3 * tmp_6 + i];
        tmp_3[i + 3 * tmp_6] = StudentTemplate_B.Add3_p[3 * tmp_6 + 2] *
          StudentTemplate_B.x3[i + 6] + tmp_3[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product5[i] = 0.0;
      StudentTemplate_B.Product5[i] = tmp_3[i] * StudentTemplate_B.Add2_f[0] +
        StudentTemplate_B.Product5[i];
      StudentTemplate_B.Product5[i] = tmp_3[i + 3] * StudentTemplate_B.Add2_f[1]
        + StudentTemplate_B.Product5[i];
    }

    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Constant: '<S106>/0_2x1' */
      StudentTemplate_B.VectorConcatenate1[0] = StudentTemplate_P._2x1_Value_d[0];
      StudentTemplate_B.VectorConcatenate1[1] = StudentTemplate_P._2x1_Value_d[1];
    }

    /* SignalConversion: '<S106>/ConcatBufferAtVector Concatenate1In2' */
    StudentTemplate_B.VectorConcatenate1[2] = StudentTemplate_B.Subtract_n;

    /* Product: '<S46>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] +
          StudentTemplate_B.MathFunction_a[3 * tmp_6] * StudentTemplate_B.Add3[i];
        tmp_1[i + 3 * tmp_6] = StudentTemplate_B.MathFunction_a[3 * tmp_6 + 1] *
          StudentTemplate_B.Add3[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = StudentTemplate_B.MathFunction_a[3 * tmp_6 + 2] *
          StudentTemplate_B.Add3[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product3_h[i] = 0.0;
      StudentTemplate_B.Product3_h[i] = tmp_1[i] *
        StudentTemplate_B.VectorConcatenate1[0] + StudentTemplate_B.Product3_h[i];
      StudentTemplate_B.Product3_h[i] = tmp_1[i + 3] *
        StudentTemplate_B.VectorConcatenate1[1] + StudentTemplate_B.Product3_h[i];
      StudentTemplate_B.Product3_h[i] = tmp_1[i + 6] *
        StudentTemplate_B.VectorConcatenate1[2] + StudentTemplate_B.Product3_h[i];
    }

    /* Trigonometry: '<S109>/Trigonometric Function1' */
    StudentTemplate_B.TrigonometricFunction1_f = sin(StudentTemplate_B.Sum_ip);

    /* Gain: '<S109>/Gain' */
    StudentTemplate_B.Gain_l = StudentTemplate_P.Gain_Gain_a *
      StudentTemplate_B.TrigonometricFunction1_f;

    /* Product: '<S109>/Product1' */
    StudentTemplate_B.Product1_hg = StudentTemplate_B.Gain_l *
      StudentTemplate_B.Subtract_n;

    /* Trigonometry: '<S109>/Trigonometric Function' */
    StudentTemplate_B.TrigonometricFunction_p5 = cos(StudentTemplate_B.Sum_ip);

    /* Product: '<S109>/Product2' */
    StudentTemplate_B.Product2_n = StudentTemplate_B.TrigonometricFunction_p5 *
      StudentTemplate_B.Subtract_n;

    /* SignalConversion: '<S109>/TmpHiddenBufferAtProductInport1' */
    StudentTemplate_B.TmpHiddenBufferAtProductInpor_f[0] =
      StudentTemplate_B.Product1_hg;
    StudentTemplate_B.TmpHiddenBufferAtProductInpor_f[1] =
      StudentTemplate_B.Product2_n;

    /* Product: '<S109>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    StudentTemplate_B.Product_la[0] =
      StudentTemplate_B.TmpHiddenBufferAtProductInpor_f[0] *
      StudentTemplate_P.u_dm_Value;
    StudentTemplate_B.Product_la[1] =
      StudentTemplate_B.TmpHiddenBufferAtProductInpor_f[1] *
      StudentTemplate_P.u_dm_Value;

    /* SignalConversion: '<S53>/ConcatBufferAtVector ConcatenateIn1' */
    StudentTemplate_B.VectorConcatenate_em[0] = StudentTemplate_B.Product_la[0];
    StudentTemplate_B.VectorConcatenate_em[1] = StudentTemplate_B.Product_la[1];

    /* Product: '<S53>/Product' */
    tmp = StudentTemplate_B.Subtract_b[0] * StudentTemplate_B.Product_i[0];
    tmp += StudentTemplate_B.Subtract_b[1] * StudentTemplate_B.Product_i[1];
    StudentTemplate_B.Product_eg = tmp;

    /* Product: '<S53>/Product1' */
    tmp = StudentTemplate_B.u_m[0] * StudentTemplate_B.Product_la[0];
    tmp += StudentTemplate_B.u_m[1] * StudentTemplate_B.Product_la[1];
    StudentTemplate_B.Product1_lb = tmp;

    /* Sum: '<S53>/Add' */
    StudentTemplate_B.VectorConcatenate_em[2] = StudentTemplate_B.Product_eg +
      StudentTemplate_B.Product1_lb;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Constant: '<S59>/0_2x1' */
      StudentTemplate_B.VectorConcatenate_c5[0] =
        StudentTemplate_P._2x1_Value_j[0];
      StudentTemplate_B.VectorConcatenate_c5[1] =
        StudentTemplate_P._2x1_Value_j[1];

      /* Product: '<S154>/Product' incorporates:
       *  Constant: '<S143>/0_2x1'
       */
      StudentTemplate_B.Product_fb[0] = StudentTemplate_P._2x1_Value_b[0] *
        StudentTemplate_B.RoundingFunction;
      StudentTemplate_B.Product_fb[1] = StudentTemplate_P._2x1_Value_b[1] *
        StudentTemplate_B.RoundingFunction;
    }

    /* Product: '<S147>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    StudentTemplate_B.Product2_fz = StudentTemplate_B.Integrator1 *
      StudentTemplate_P.k_Value;

    /* Trigonometry: '<S147>/sin(s)3' */
    StudentTemplate_B.sins3 = sin(StudentTemplate_B.Product2_fz);
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S147>/Math Function' incorporates:
       *  Constant: '<S10>/k [-]'
       *  Constant: '<S147>/Constant'
       */
      if ((StudentTemplate_P.k_Value < 0.0) &&
          (StudentTemplate_P.Constant_Value_j0 > floor
           (StudentTemplate_P.Constant_Value_j0))) {
        StudentTemplate_B.MathFunction_eq = -rt_pow_snf
          (-StudentTemplate_P.k_Value, StudentTemplate_P.Constant_Value_j0);
      } else {
        StudentTemplate_B.MathFunction_eq = rt_pow_snf(StudentTemplate_P.k_Value,
          StudentTemplate_P.Constant_Value_j0);
      }
    }

    /* Product: '<S147>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    StudentTemplate_B.Product_lr = StudentTemplate_P.r_xm_Value *
      StudentTemplate_B.sins3 * StudentTemplate_B.MathFunction_eq;

    /* Trigonometry: '<S147>/cos(s)3' */
    StudentTemplate_B.coss3 = cos(StudentTemplate_B.Product2_fz);

    /* Product: '<S147>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    StudentTemplate_B.Product1_fg = StudentTemplate_P.r_ym_Value *
      StudentTemplate_B.coss3 * StudentTemplate_B.MathFunction_eq;

    /* Gain: '<S147>/Gain' */
    StudentTemplate_B.Gain_ca = StudentTemplate_P.Gain_Gain_p2 *
      StudentTemplate_B.Product1_fg;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Sum: '<S154>/Subract' incorporates:
       *  Constant: '<S154>/Constant'
       */
      StudentTemplate_B.Subract_l = StudentTemplate_P.Constant_Value_d -
        StudentTemplate_B.RoundingFunction;
    }

    /* Product: '<S154>/Product1' */
    StudentTemplate_B.Product1_mt[0] = StudentTemplate_B.Product_lr *
      StudentTemplate_B.Subract_l;
    StudentTemplate_B.Product1_mt[1] = StudentTemplate_B.Gain_ca *
      StudentTemplate_B.Subract_l;

    /* Sum: '<S154>/Add' */
    StudentTemplate_B.Add_bs[0] = StudentTemplate_B.Product_fb[0] +
      StudentTemplate_B.Product1_mt[0];
    StudentTemplate_B.Add_bs[1] = StudentTemplate_B.Product_fb[1] +
      StudentTemplate_B.Product1_mt[1];

    /* Product: '<S99>/x_d^s * y_d^s^3 ' */
    StudentTemplate_B.x_dsy_ds3 = StudentTemplate_B.Add[0] *
      StudentTemplate_B.Add_bs[1];

    /* Product: '<S99>/x_d^s^3 * y_d^s' */
    StudentTemplate_B.x_ds3y_ds = StudentTemplate_B.Add_bs[0] *
      StudentTemplate_B.Add[1];

    /* Sum: '<S99>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
    StudentTemplate_B.x_dsy_ds3x_ds3y_ds = StudentTemplate_B.x_dsy_ds3 -
      StudentTemplate_B.x_ds3y_ds;

    /* Product: '<S99>/Product1' */
    StudentTemplate_B.Product1_op = StudentTemplate_B.x_dsy_ds3x_ds3y_ds *
      StudentTemplate_B.x_ds2y_ds2;

    /* Product: '<S99>/x_d^s * x_d^s^2' */
    StudentTemplate_B.x_dsx_ds2 = StudentTemplate_B.Add[0] *
      StudentTemplate_B.Add_nm[0];

    /* Product: '<S99>/y_d^s * y_d^s^2' */
    StudentTemplate_B.y_dsy_ds2 = StudentTemplate_B.Add[1] *
      StudentTemplate_B.Add_nm[1];

    /* Sum: '<S99>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
    StudentTemplate_B.x_dsx_ds2x_ds3y_ds = StudentTemplate_B.x_dsx_ds2 +
      StudentTemplate_B.y_dsy_ds2;

    /* Gain: '<S99>/+ 2' */
    StudentTemplate_B.u_k = StudentTemplate_P.u_Gain_h *
      StudentTemplate_B.x_dsx_ds2x_ds3y_ds;

    /* Product: '<S99>/Product2' */
    StudentTemplate_B.Product2_i = StudentTemplate_B.x_dsy_ds2x_ds2y_ds *
      StudentTemplate_B.u_k;

    /* Sum: '<S99>/Subtract' */
    StudentTemplate_B.Subtract_m = StudentTemplate_B.Product1_op -
      StudentTemplate_B.Product2_i;

    /* Math: '<S99>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
    tmp = StudentTemplate_B.x_ds2y_ds2;
    StudentTemplate_B.x_ds2y_ds22 = tmp * tmp;

    /* Product: '<S99>/Divide' */
    StudentTemplate_B.Divide_ob = StudentTemplate_B.Subtract_m /
      StudentTemplate_B.x_ds2y_ds22;

    /* Math: '<S127>/(epsilon_n^s)^2' */
    tmp = StudentTemplate_B.MultiportSelector2;
    StudentTemplate_B.epsilon_ns2 = tmp * tmp;

    /* Product: '<S127>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product_lu = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.MultiportSelector * StudentTemplate_B.epsilon_ns2;

    /* Gain: '<S127>/2' */
    StudentTemplate_B.u_o = StudentTemplate_P._Gain_h *
      StudentTemplate_B.Product_lu;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S127>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2_d = tmp * tmp;
    }

    /* Math: '<S127>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2_nk = tmp * tmp;

    /* Sum: '<S127>/Add' */
    StudentTemplate_B.Add_c = StudentTemplate_B.Delta2_d +
      StudentTemplate_B.epsilon_n2_nk;

    /* Math: '<S127>/( )^2' */
    tmp = StudentTemplate_B.Add_c;
    StudentTemplate_B.u_e2 = tmp * tmp;

    /* Product: '<S127>/Divide' */
    StudentTemplate_B.Divide_h = StudentTemplate_B.u_o / StudentTemplate_B.u_e2;

    /* Outputs for atomic SubSystem: '<S105>/S_2(psi_d^s^2)' */

    /* Gain: '<S134>/S12' */
    StudentTemplate_B.S12_p = StudentTemplate_P.S12_Gain_e *
      StudentTemplate_B.Divide_ob;

    /* Reshape: '<S134>/S_2(psi_d^s^2)' incorporates:
     *  Constant: '<S134>/0'
     */
    StudentTemplate_B.S_2psi_ds2[0] = StudentTemplate_P._Value_f;
    StudentTemplate_B.S_2psi_ds2[1] = StudentTemplate_B.Divide_ob;
    StudentTemplate_B.S_2psi_ds2[2] = StudentTemplate_B.S12_p;
    StudentTemplate_B.S_2psi_ds2[3] = StudentTemplate_P._Value_f;

    /* end of Outputs for SubSystem: '<S105>/S_2(psi_d^s^2)' */

    /* Math: '<S135>/Math Function' */
    StudentTemplate_B.MathFunction_bo[0] = StudentTemplate_B.S_2psi_ds2[0];
    StudentTemplate_B.MathFunction_bo[1] = StudentTemplate_B.S_2psi_ds2[2];
    StudentTemplate_B.MathFunction_bo[2] = StudentTemplate_B.S_2psi_ds2[1];
    StudentTemplate_B.MathFunction_bo[3] = StudentTemplate_B.S_2psi_ds2[3];

    /* Product: '<S139>/Product' */
    for (i = 0; i < 2; i++) {
      StudentTemplate_B.Product_o[i] = 0.0;
      StudentTemplate_B.Product_o[i] = StudentTemplate_B.MathFunction_c[i] *
        StudentTemplate_B.MathFunction_c[0] + StudentTemplate_B.Product_o[i];
      StudentTemplate_B.Product_o[i] = StudentTemplate_B.MathFunction_c[i + 2] *
        StudentTemplate_B.MathFunction_c[1] + StudentTemplate_B.Product_o[i];
      StudentTemplate_B.Product_o[i + 2] = 0.0;
      StudentTemplate_B.Product_o[i + 2] = StudentTemplate_B.Product_o[i + 2] +
        StudentTemplate_B.MathFunction_c[i] * StudentTemplate_B.MathFunction_c[2];
      StudentTemplate_B.Product_o[i + 2] = StudentTemplate_B.MathFunction_c[i +
        2] * StudentTemplate_B.MathFunction_c[3] + StudentTemplate_B.Product_o[i
        + 2];
    }

    /* Sum: '<S139>/Add' */
    StudentTemplate_B.Add_ii[0] = StudentTemplate_B.MathFunction_bo[0] +
      StudentTemplate_B.Product_o[0];
    StudentTemplate_B.Add_ii[1] = StudentTemplate_B.MathFunction_bo[1] +
      StudentTemplate_B.Product_o[1];
    StudentTemplate_B.Add_ii[2] = StudentTemplate_B.MathFunction_bo[2] +
      StudentTemplate_B.Product_o[2];
    StudentTemplate_B.Add_ii[3] = StudentTemplate_B.MathFunction_bo[3] +
      StudentTemplate_B.Product_o[3];

    /* Product: '<S139>/Product1' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += StudentTemplate_B.Add_ii[i] *
        StudentTemplate_B.MathFunction_h[0];
      tmp_2[i] += StudentTemplate_B.Add_ii[i + 2] *
        StudentTemplate_B.MathFunction_h[1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += StudentTemplate_B.Add_ii[i] *
        StudentTemplate_B.MathFunction_h[2];
      tmp_2[i + 2] += StudentTemplate_B.Add_ii[i + 2] *
        StudentTemplate_B.MathFunction_h[3];
    }

    StudentTemplate_B.Product1_pg[0] = 0.0;
    StudentTemplate_B.Product1_pg[0] = tmp_2[0] * StudentTemplate_B.Subtract[0]
      + StudentTemplate_B.Product1_pg[0];
    StudentTemplate_B.Product1_pg[0] = tmp_2[2] * StudentTemplate_B.Subtract[1]
      + StudentTemplate_B.Product1_pg[0];
    StudentTemplate_B.Product1_pg[1] = 0.0;
    StudentTemplate_B.Product1_pg[1] = tmp_2[1] * StudentTemplate_B.Subtract[0]
      + StudentTemplate_B.Product1_pg[1];
    StudentTemplate_B.Product1_pg[1] = tmp_2[3] * StudentTemplate_B.Subtract[1]
      + StudentTemplate_B.Product1_pg[1];

    /* Product: '<S139>/Product2' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += StudentTemplate_B.MathFunction_c[i] *
        StudentTemplate_B.MathFunction_h[0];
      tmp_2[i] += StudentTemplate_B.MathFunction_c[i + 2] *
        StudentTemplate_B.MathFunction_h[1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += StudentTemplate_B.MathFunction_c[i] *
        StudentTemplate_B.MathFunction_h[2];
      tmp_2[i + 2] += StudentTemplate_B.MathFunction_c[i + 2] *
        StudentTemplate_B.MathFunction_h[3];
    }

    StudentTemplate_B.Product2_hq[0] = 0.0;
    StudentTemplate_B.Product2_hq[0] = tmp_2[0] * StudentTemplate_B.Add[0] +
      StudentTemplate_B.Product2_hq[0];
    StudentTemplate_B.Product2_hq[0] = tmp_2[2] * StudentTemplate_B.Add[1] +
      StudentTemplate_B.Product2_hq[0];

    /* Gain: '<S139>/2' */
    StudentTemplate_B.u_j[0] = StudentTemplate_P._Gain_n *
      StudentTemplate_B.Product2_hq[0];

    /* Product: '<S139>/Product3' */
    StudentTemplate_B.Product3_e5[0] = 0.0;
    StudentTemplate_B.Product3_e5[0] = StudentTemplate_B.MathFunction_h[0] *
      StudentTemplate_B.Add_nm[0] + StudentTemplate_B.Product3_e5[0];
    StudentTemplate_B.Product3_e5[0] = StudentTemplate_B.MathFunction_h[2] *
      StudentTemplate_B.Add_nm[1] + StudentTemplate_B.Product3_e5[0];

    /* Sum: '<S139>/Sum' */
    StudentTemplate_B.Sum_og[0] = (StudentTemplate_B.Product1_pg[0] -
      StudentTemplate_B.u_j[0]) - StudentTemplate_B.Product3_e5[0];

    /* Gain: '<S139>/Gain' */
    StudentTemplate_B.Gain_f[0] = StudentTemplate_P.Gain_Gain_gx *
      StudentTemplate_B.Sum_og[0];
    StudentTemplate_B.Product2_hq[1] = 0.0;
    StudentTemplate_B.Product2_hq[1] = tmp_2[1] * StudentTemplate_B.Add[0] +
      StudentTemplate_B.Product2_hq[1];
    StudentTemplate_B.Product2_hq[1] = tmp_2[3] * StudentTemplate_B.Add[1] +
      StudentTemplate_B.Product2_hq[1];

    /* Gain: '<S139>/2' */
    StudentTemplate_B.u_j[1] = StudentTemplate_P._Gain_n *
      StudentTemplate_B.Product2_hq[1];

    /* Product: '<S139>/Product3' */
    StudentTemplate_B.Product3_e5[1] = 0.0;
    StudentTemplate_B.Product3_e5[1] = StudentTemplate_B.MathFunction_h[1] *
      StudentTemplate_B.Add_nm[0] + StudentTemplate_B.Product3_e5[1];
    StudentTemplate_B.Product3_e5[1] = StudentTemplate_B.MathFunction_h[3] *
      StudentTemplate_B.Add_nm[1] + StudentTemplate_B.Product3_e5[1];

    /* Sum: '<S139>/Sum' */
    StudentTemplate_B.Sum_og[1] = (StudentTemplate_B.Product1_pg[1] -
      StudentTemplate_B.u_j[1]) - StudentTemplate_B.Product3_e5[1];

    /* Gain: '<S139>/Gain' */
    StudentTemplate_B.Gain_f[1] = StudentTemplate_P.Gain_Gain_gx *
      StudentTemplate_B.Sum_og[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector4' */
    {
      const byte_T *u = (byte_T *)StudentTemplate_B.Gain_f;/* input port */
      const int32_T *index = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&StudentTemplate_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&StudentTemplate_B.MultiportSelector4;
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
    StudentTemplate_B.Product1_a1 = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.MultiportSelector4;

    /* Product: '<S127>/Divide1' */
    StudentTemplate_B.Divide1_pj = StudentTemplate_B.Product1_a1 /
      StudentTemplate_B.Add_c;

    /* Sum: '<S127>/Sum' */
    StudentTemplate_B.Sum_l = (StudentTemplate_B.Divide_ob +
      StudentTemplate_B.Divide_h) - StudentTemplate_B.Divide1_pj;

    /* Product: '<S59>/Product' */
    StudentTemplate_B.Product_k = StudentTemplate_B.Sum_l *
      StudentTemplate_B.Subtract_f;

    /* Math: '<S165>/Math Function' */
    StudentTemplate_B.MathFunction_lp[0] = StudentTemplate_B.Add[0];
    StudentTemplate_B.MathFunction_lp[1] = StudentTemplate_B.Add[1];

    /* Product: '<S163>/Product1' */
    tmp = StudentTemplate_B.MathFunction_lp[0] * StudentTemplate_B.Add_nm[0];
    tmp += StudentTemplate_B.MathFunction_lp[1] * StudentTemplate_B.Add_nm[1];
    StudentTemplate_B.Product1_ke = tmp;

    /* Math: '<S163>/|p_d^s|^3' incorporates:
     *  Constant: '<S163>/Constant'
     */
    if ((StudentTemplate_B.Add_b < 0.0) && (StudentTemplate_P.Constant_Value_kd >
         floor(StudentTemplate_P.Constant_Value_kd))) {
      StudentTemplate_B.p_ds3 = -rt_pow_snf(-StudentTemplate_B.Add_b,
        StudentTemplate_P.Constant_Value_kd);
    } else {
      StudentTemplate_B.p_ds3 = rt_pow_snf(StudentTemplate_B.Add_b,
        StudentTemplate_P.Constant_Value_kd);
    }

    /* Product: '<S163>/Divide' */
    StudentTemplate_B.Divide_it = StudentTemplate_B.Product1_ke /
      StudentTemplate_B.p_ds3;

    /* Product: '<S163>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    StudentTemplate_B.Product_h = StudentTemplate_B.Divide_it *
      StudentTemplate_P.u_dm_Value;

    /* Gain: '<S163>/Gain' */
    StudentTemplate_B.Gain_nv = StudentTemplate_P.Gain_Gain_kp *
      StudentTemplate_B.Product_h;

    /* Math: '<S113>/epsilon_n^2' */
    tmp = StudentTemplate_B.MultiportSelector;
    StudentTemplate_B.epsilon_n2_d = tmp * tmp;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Math: '<S113>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.Delta2_k = tmp * tmp;
    }

    /* Sum: '<S113>/Add' */
    StudentTemplate_B.Add_l4 = StudentTemplate_B.epsilon_n2_d +
      StudentTemplate_B.Delta2_k;

    /* Math: '<S113>/Math Function' */
    tmp = StudentTemplate_B.Add_l4;
    if (tmp < 0.0) {
      StudentTemplate_B.MathFunction_ju = -sqrt(-tmp);
    } else {
      StudentTemplate_B.MathFunction_ju = sqrt(tmp);
    }

    /* Product: '<S113>/Divide' */
    StudentTemplate_B.Divide_da = StudentTemplate_B.Gain_nv /
      StudentTemplate_B.MathFunction_ju;

    /* Product: '<S113>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product1_c = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.Divide_da;

    /* Product: '<S113>/Product2' */
    StudentTemplate_B.Product2_m = StudentTemplate_B.MultiportSelector *
      StudentTemplate_B.MultiportSelector2;

    /* Math: '<S113>/^3//2' incorporates:
     *  Constant: '<S113>/3//2'
     */
    if ((StudentTemplate_B.Add_l4 < 0.0) && (StudentTemplate_P.u_Value_gk >
         floor(StudentTemplate_P.u_Value_gk))) {
      StudentTemplate_B.u2_p = -rt_pow_snf(-StudentTemplate_B.Add_l4,
        StudentTemplate_P.u_Value_gk);
    } else {
      StudentTemplate_B.u2_p = rt_pow_snf(StudentTemplate_B.Add_l4,
        StudentTemplate_P.u_Value_gk);
    }

    /* Product: '<S113>/Divide1' */
    StudentTemplate_B.Divide1_f = StudentTemplate_B.Product2_m /
      StudentTemplate_B.u2_p;

    /* Product: '<S113>/Product3' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    StudentTemplate_B.Product3_m = StudentTemplate_P.Deltam_Value *
      StudentTemplate_B.Divide1_f * StudentTemplate_B.Divide_bz;

    /* Product: '<S117>/Product1' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    StudentTemplate_B.Product1_e = StudentTemplate_P.my_Value *
      StudentTemplate_B.Add_b;

    /* Math: '<S121>/Math Function' */
    StudentTemplate_B.MathFunction_fs[0] = StudentTemplate_B.Add_nm[0];

    /* Product: '<S117>/Divide2' */
    StudentTemplate_B.Divide2[0] = StudentTemplate_B.MathFunction_fs[0] /
      StudentTemplate_B.Add_b;

    /* Math: '<S120>/Math Function' */
    StudentTemplate_B.MathFunction_ps[0] = StudentTemplate_B.Add[0];

    /* Math: '<S121>/Math Function' */
    StudentTemplate_B.MathFunction_fs[1] = StudentTemplate_B.Add_nm[1];

    /* Product: '<S117>/Divide2' */
    StudentTemplate_B.Divide2[1] = StudentTemplate_B.MathFunction_fs[1] /
      StudentTemplate_B.Add_b;

    /* Math: '<S120>/Math Function' */
    StudentTemplate_B.MathFunction_ps[1] = StudentTemplate_B.Add[1];

    /* Product: '<S117>/Product2' */
    tmp = StudentTemplate_B.MathFunction_fs[0] * StudentTemplate_B.Add[0];
    tmp += StudentTemplate_B.MathFunction_fs[1] * StudentTemplate_B.Add[1];
    StudentTemplate_B.Product2_k[0] = tmp * StudentTemplate_B.MathFunction_ps[0];
    StudentTemplate_B.Product2_k[1] = tmp * StudentTemplate_B.MathFunction_ps[1];

    /* Math: '<S117>/Math Function' incorporates:
     *  Constant: '<S117>/Constant'
     */
    if ((StudentTemplate_B.Add_b < 0.0) && (StudentTemplate_P.Constant_Value_h >
         floor(StudentTemplate_P.Constant_Value_h))) {
      StudentTemplate_B.MathFunction_fa = -rt_pow_snf(-StudentTemplate_B.Add_b,
        StudentTemplate_P.Constant_Value_h);
    } else {
      StudentTemplate_B.MathFunction_fa = rt_pow_snf(StudentTemplate_B.Add_b,
        StudentTemplate_P.Constant_Value_h);
    }

    /* Product: '<S117>/Divide1' */
    StudentTemplate_B.Divide1_b[0] = StudentTemplate_B.Product2_k[0] /
      StudentTemplate_B.MathFunction_fa;

    /* Sum: '<S117>/Subtract1' */
    StudentTemplate_B.Subtract1_b[0] = StudentTemplate_B.Divide2[0] -
      StudentTemplate_B.Divide1_b[0];

    /* Product: '<S117>/Divide1' */
    StudentTemplate_B.Divide1_b[1] = StudentTemplate_B.Product2_k[1] /
      StudentTemplate_B.MathFunction_fa;

    /* Sum: '<S117>/Subtract1' */
    StudentTemplate_B.Subtract1_b[1] = StudentTemplate_B.Divide2[1] -
      StudentTemplate_B.Divide1_b[1];

    /* Product: '<S117>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    tmp = StudentTemplate_P.my_Value * StudentTemplate_B.Subtract1_b[0] *
      StudentTemplate_B.Subtract[0];
    tmp += StudentTemplate_P.my_Value * StudentTemplate_B.Subtract1_b[1] *
      StudentTemplate_B.Subtract[1];
    StudentTemplate_B.Product_ca = tmp;

    /* Sum: '<S117>/Subtract' */
    StudentTemplate_B.Subtract_ea = StudentTemplate_B.Product1_e -
      StudentTemplate_B.Product_ca;

    /* Sum: '<S113>/Sum' */
    StudentTemplate_B.Sum_mk = (StudentTemplate_B.Product1_c -
      StudentTemplate_B.Product3_m) - StudentTemplate_B.Subtract_ea;

    /* Product: '<S59>/Product1' */
    StudentTemplate_B.Product1_kz = StudentTemplate_B.Subtract_n *
      StudentTemplate_B.Sum_mk;

    /* Sum: '<S59>/Add' */
    StudentTemplate_B.VectorConcatenate_c5[2] = StudentTemplate_B.Product_k +
      StudentTemplate_B.Product1_kz;

    /* Sum: '<S46>/Add2' */
    StudentTemplate_B.Add2_a[0] = StudentTemplate_B.VectorConcatenate_em[0] +
      StudentTemplate_B.VectorConcatenate_c5[0];
    StudentTemplate_B.Add2_a[1] = StudentTemplate_B.VectorConcatenate_em[1] +
      StudentTemplate_B.VectorConcatenate_c5[1];
    StudentTemplate_B.Add2_a[2] = StudentTemplate_B.VectorConcatenate_em[2] +
      StudentTemplate_B.VectorConcatenate_c5[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S46>/Product4' */
      StudentTemplate_B.Product4_f[i] = 0.0;
      StudentTemplate_B.Product4_f[i] = StudentTemplate_B.MathFunction_a[i] *
        StudentTemplate_B.Add2_a[0] + StudentTemplate_B.Product4_f[i];
      StudentTemplate_B.Product4_f[i] = StudentTemplate_B.MathFunction_a[i + 3] *
        StudentTemplate_B.Add2_a[1] + StudentTemplate_B.Product4_f[i];
      StudentTemplate_B.Product4_f[i] = StudentTemplate_B.MathFunction_a[i + 6] *
        StudentTemplate_B.Add2_a[2] + StudentTemplate_B.Product4_f[i];

      /* Sum: '<S46>/Add3' */
      StudentTemplate_B.Add3_l[i] = StudentTemplate_B.Product3_h[i] +
        StudentTemplate_B.Product4_f[i];
    }

    for (i = 0; i < 3; i++) {
      tmp_4[i] = 0.0;
      tmp = tmp_4[i];
      tmp += StudentTemplate_B.x3[i] * StudentTemplate_B.Add3_l[0];
      tmp_4[i] = tmp;
      tmp = tmp_4[i];
      tmp += StudentTemplate_B.x3[i + 3] * StudentTemplate_B.Add3_l[1];
      tmp_4[i] = tmp;
      tmp = tmp_4[i];
      tmp += StudentTemplate_B.x3[i + 6] * StudentTemplate_B.Add3_l[2];
      tmp_4[i] = tmp;
      StudentTemplate_B.Product6[i] = tmp_4[i] * StudentTemplate_B.Subtract_f;

      /* Sum: '<S39>/Sum' */
      StudentTemplate_B.Sum_lt[i] = ((((StudentTemplate_B.Gain_a[i] +
        StudentTemplate_B.Gain1_j[i]) + StudentTemplate_B.Product2_g[i]) +
        StudentTemplate_B.Product4_p[i]) + StudentTemplate_B.Product5[i]) +
        StudentTemplate_B.Product6[i];
    }

    /* MultiPortSwitch: '<S29>/tau Switch' incorporates:
     *  Constant: '<S1>/Control Mode Selector'
     */
    switch ((int32_T)StudentTemplate_P.ControlModeSelector_Value) {
     case 0:
      StudentTemplate_B.tauSwitch[0] = StudentTemplate_B.Product[0];
      StudentTemplate_B.tauSwitch[1] = StudentTemplate_B.Product[1];
      StudentTemplate_B.tauSwitch[2] = StudentTemplate_B.Product[2];
      break;

     case 1:
      StudentTemplate_B.tauSwitch[0] = StudentTemplate_B.Sum1_j[0];
      StudentTemplate_B.tauSwitch[1] = StudentTemplate_B.Sum1_j[1];
      StudentTemplate_B.tauSwitch[2] = StudentTemplate_B.Sum1_j[2];
      break;

     default:
      StudentTemplate_B.tauSwitch[0] = StudentTemplate_B.Sum_lt[0];
      StudentTemplate_B.tauSwitch[1] = StudentTemplate_B.Sum_lt[1];
      StudentTemplate_B.tauSwitch[2] = StudentTemplate_B.Sum_lt[2];
      break;
    }

    /* Sum: '<S42>/Add' */
    StudentTemplate_B.Add_gg[0] = StudentTemplate_B.Integrator2[0] +
      StudentTemplate_B.Product_i[0];
    StudentTemplate_B.Add_gg[1] = StudentTemplate_B.Integrator2[1] +
      StudentTemplate_B.Product_i[1];

    /* Math: '<S63>/Math Function' */
    StudentTemplate_B.MathFunction_la[0] = StudentTemplate_B.Product_bx[0];
    StudentTemplate_B.MathFunction_la[1] = StudentTemplate_B.Product_bx[1];
    StudentTemplate_B.MathFunction_la[2] = StudentTemplate_B.Product_bx[2];

    /* Product: '<S43>/Product' */
    for (i = 0; i < 3; i++) {
      tmp_4[i] = 0.0;
      tmp = tmp_4[i];
      tmp += StudentTemplate_B.MathFunction_a[3 * i] *
        StudentTemplate_B.MathFunction_la[0];
      tmp_4[i] = tmp;
      tmp = tmp_4[i];
      tmp += StudentTemplate_B.MathFunction_a[3 * i + 1] *
        StudentTemplate_B.MathFunction_la[1];
      tmp_4[i] = tmp;
      tmp = tmp_4[i];
      tmp += StudentTemplate_B.MathFunction_a[3 * i + 2] *
        StudentTemplate_B.MathFunction_la[2];
      tmp_4[i] = tmp;
    }

    for (i = 0; i < 2; i++) {
      StudentTemplate_B.Product_g4[i] = 0.0;
      StudentTemplate_B.Product_g4[i] = StudentTemplate_B.MatrixConcatenate[3 *
        i] * tmp_4[0] + StudentTemplate_B.Product_g4[i];
      StudentTemplate_B.Product_g4[i] = StudentTemplate_B.MatrixConcatenate[3 *
        i + 1] * tmp_4[1] + StudentTemplate_B.Product_g4[i];
      StudentTemplate_B.Product_g4[i] = StudentTemplate_B.MatrixConcatenate[3 *
        i + 2] * tmp_4[2] + StudentTemplate_B.Product_g4[i];

      /* Gain: '<S43>/Gain' */
      StudentTemplate_B.Gain_i[i] = StudentTemplate_P.Gain_Gain_k3 *
        StudentTemplate_B.Product_g4[i];

      /* Math: '<S62>/Math Function' */
      StudentTemplate_B.MathFunction_h2[i] = StudentTemplate_B.Gain_i[i];
    }

    /* Product: '<S42>/Product' */
    StudentTemplate_B.Product_a5[0] = 0.0;
    StudentTemplate_B.Product_a5[0] = StudentTemplate_B.ux2[0] *
      StudentTemplate_B.MathFunction_h2[0] + StudentTemplate_B.Product_a5[0];
    StudentTemplate_B.Product_a5[0] = StudentTemplate_B.ux2[2] *
      StudentTemplate_B.MathFunction_h2[1] + StudentTemplate_B.Product_a5[0];

    /* Sum: '<S42>/Add1' */
    StudentTemplate_B.Add1_l[0] = StudentTemplate_B.Integrator2[0] +
      StudentTemplate_B.Product_a5[0];

    /* Product: '<S42>/Product1' incorporates:
     *  Constant: '<S9>/lambda_q'
     */
    StudentTemplate_B.Product1_cx[0] = StudentTemplate_P.lambda_q_Value *
      StudentTemplate_B.Add1_l[0];

    /* Gain: '<S42>/Gain' */
    StudentTemplate_B.Gain_mv[0] = StudentTemplate_P.Gain_Gain_ni *
      StudentTemplate_B.Product1_cx[0];

    /* Product: '<S42>/Product' */
    StudentTemplate_B.Product_a5[1] = 0.0;
    StudentTemplate_B.Product_a5[1] = StudentTemplate_B.ux2[1] *
      StudentTemplate_B.MathFunction_h2[0] + StudentTemplate_B.Product_a5[1];
    StudentTemplate_B.Product_a5[1] = StudentTemplate_B.ux2[3] *
      StudentTemplate_B.MathFunction_h2[1] + StudentTemplate_B.Product_a5[1];

    /* Sum: '<S42>/Add1' */
    StudentTemplate_B.Add1_l[1] = StudentTemplate_B.Integrator2[1] +
      StudentTemplate_B.Product_a5[1];

    /* Product: '<S42>/Product1' incorporates:
     *  Constant: '<S9>/lambda_q'
     */
    StudentTemplate_B.Product1_cx[1] = StudentTemplate_P.lambda_q_Value *
      StudentTemplate_B.Add1_l[1];

    /* Gain: '<S42>/Gain' */
    StudentTemplate_B.Gain_mv[1] = StudentTemplate_P.Gain_Gain_ni *
      StudentTemplate_B.Product1_cx[1];

    /* Product: '<S50>/Product' */
    for (i = 0; i < 3; i++) {
      StudentTemplate_B.Product_ar[i] = 0.0;
      StudentTemplate_B.Product_ar[i] = StudentTemplate_B.Rpsi[i] *
        StudentTemplate_B.Subtract_n5[0] + StudentTemplate_B.Product_ar[i];
      StudentTemplate_B.Product_ar[i] = StudentTemplate_B.Rpsi[i + 3] *
        StudentTemplate_B.Subtract_n5[1] + StudentTemplate_B.Product_ar[i];
      StudentTemplate_B.Product_ar[i] = StudentTemplate_B.Rpsi[i + 6] *
        StudentTemplate_B.Subtract_n5[2] + StudentTemplate_B.Product_ar[i];
    }

    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* S-Function (sdsppinv): '<S76>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&StudentTemplate_DWork.Pseudoinverse_X[0]), (void *)
             (&StudentTemplate_B.x5[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&StudentTemplate_DWork.Pseudoinverse_X[0], 3, 5,
                      &StudentTemplate_DWork.Pseudoinverse_S[0],
                      &StudentTemplate_DWork.Inverse_DWORK3[0],
                      &StudentTemplate_DWork.Pseudoinverse_WORK[0],
                      &StudentTemplate_DWork.Pseudoinverse_U[0],
                      &StudentTemplate_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&StudentTemplate_DWork.Pseudoinverse_S[0],
          &StudentTemplate_DWork.Pseudoinverse_U[0],
          &StudentTemplate_DWork.Pseudoinverse_V[0],
          &StudentTemplate_B.Pseudoinverse[0], (const int32_T)3, (const int32_T)
          5);
      }
    }

    /* Product: '<S76>/Product' */
    for (i = 0; i < 5; i++) {
      StudentTemplate_B.Product_hu[i] = 0.0;
      StudentTemplate_B.Product_hu[i] = StudentTemplate_B.Pseudoinverse[i] *
        StudentTemplate_B.tauSwitch[0] + StudentTemplate_B.Product_hu[i];
      StudentTemplate_B.Product_hu[i] = StudentTemplate_B.Pseudoinverse[i + 5] *
        StudentTemplate_B.tauSwitch[1] + StudentTemplate_B.Product_hu[i];
      StudentTemplate_B.Product_hu[i] = StudentTemplate_B.Pseudoinverse[i + 10] *
        StudentTemplate_B.tauSwitch[2] + StudentTemplate_B.Product_hu[i];
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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_1tou_1),
                         StudentTemplate_P.f_1tou_1_YData,
                         StudentTemplate_B.Product_hu[0],
                         StudentTemplate_P.f_1tou_1_XData, 38U);

    /* Sum: '<S77>/Sum' incorporates:
     *  Constant: '<S1>/offset u1'
     */
    StudentTemplate_B.Sum_j = StudentTemplate_P.offsetu1_Value +
      StudentTemplate_B.f_1tou_1;

    /* RelationalOperator: '<S83>/Compare' incorporates:
     *  Constant: '<S83>/Constant'
     */
    StudentTemplate_B.Compare = (StudentTemplate_B.Product_hu[1] <
      StudentTemplate_P.Constant_Value_h4);

    /* RelationalOperator: '<S85>/Compare' incorporates:
     *  Constant: '<S85>/Constant'
     */
    StudentTemplate_B.Compare_c = (StudentTemplate_B.Product_hu[1] >=
      StudentTemplate_P.Constant_Value_b);

    /* RelationalOperator: '<S84>/Compare' incorporates:
     *  Constant: '<S84>/Constant'
     */
    StudentTemplate_B.Compare_g = (StudentTemplate_B.Product_hu[1] <
      StudentTemplate_P.Constant_Value_c);

    /* Logic: '<S79>/Logical Operator' */
    StudentTemplate_B.LogicalOperator = ((StudentTemplate_B.Compare_c != 0) &&
      (StudentTemplate_B.Compare_g != 0));

    /* Sum: '<S79>/Sum1' */
    StudentTemplate_B.Sum1_a = (uint8_T)(StudentTemplate_B.LogicalOperator +
      StudentTemplate_B.LogicalOperator);

    /* RelationalOperator: '<S86>/Compare' incorporates:
     *  Constant: '<S86>/Constant'
     */
    StudentTemplate_B.Compare_e = (StudentTemplate_B.Product_hu[1] >=
      StudentTemplate_P.Constant_Value_gx);

    /* Gain: '<S79>/Gain1' */
    StudentTemplate_B.Gain1_m = (uint16_T)(StudentTemplate_P.Gain1_Gain_n2 *
      StudentTemplate_B.Compare_e);

    /* Sum: '<S79>/Sum' */
    StudentTemplate_B.Sum_p = (uint16_T)(uint32_T)(((StudentTemplate_B.Compare <<
      6) + (StudentTemplate_B.Sum1_a << 6)) + StudentTemplate_B.Gain1_m);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_2000391),
                         StudentTemplate_P.f_2000391_YData,
                         StudentTemplate_B.Product_hu[1],
                         StudentTemplate_P.f_2000391_XData, 10U);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_2006731f_2000391),
                         StudentTemplate_P.f_2006731f_2000391_YData,
                         StudentTemplate_B.Product_hu[1],
                         StudentTemplate_P.f_2006731f_2000391_XData, 2U);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_2006731),
                         StudentTemplate_P.f_2006731_YData,
                         StudentTemplate_B.Product_hu[1],
                         StudentTemplate_P.f_2006731_XData, 17U);

    /* MultiPortSwitch: '<S79>/Multiport Switch' */
    switch ((int32_T)((uint32_T)(int32_T)StudentTemplate_B.Sum_p >> 6)) {
     case 1:
      StudentTemplate_B.MultiportSwitch = StudentTemplate_B.f_2000391;
      break;

     case 2:
      StudentTemplate_B.MultiportSwitch = StudentTemplate_B.f_2006731f_2000391;
      break;

     default:
      StudentTemplate_B.MultiportSwitch = StudentTemplate_B.f_2006731;
      break;
    }

    /* Sum: '<S77>/Sum1' incorporates:
     *  Constant: '<S1>/offset u2'
     */
    StudentTemplate_B.Sum1_o = StudentTemplate_P.offsetu2_Value +
      StudentTemplate_B.MultiportSwitch;

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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_3tou_3),
                         StudentTemplate_P.f_3tou_3_YData,
                         StudentTemplate_B.Product_hu[2],
                         StudentTemplate_P.f_3tou_3_XData, 38U);

    /* Sum: '<S77>/Sum2' incorporates:
     *  Constant: '<S1>/offset u3'
     */
    StudentTemplate_B.Sum2_p = StudentTemplate_P.offsetu3_Value +
      StudentTemplate_B.f_3tou_3;

    /* RelationalOperator: '<S87>/Compare' incorporates:
     *  Constant: '<S87>/Constant'
     */
    StudentTemplate_B.Compare_j = (StudentTemplate_B.Product_hu[3] <
      StudentTemplate_P.Constant_Value_ke);

    /* RelationalOperator: '<S88>/Compare' incorporates:
     *  Constant: '<S88>/Constant'
     */
    StudentTemplate_B.Compare_l = (StudentTemplate_B.Product_hu[3] >=
      StudentTemplate_P.Constant_Value_h3);

    /* Gain: '<S81>/Gain' */
    StudentTemplate_B.Gain_mc = (uint16_T)(StudentTemplate_P.Gain_Gain_gq *
      StudentTemplate_B.Compare_l);

    /* Sum: '<S81>/Sum' */
    StudentTemplate_B.Sum_nx = (uint16_T)(uint32_T)((StudentTemplate_B.Compare_j
      << 6) + StudentTemplate_B.Gain_mc);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_400451),
                         StudentTemplate_P.f_400451_YData,
                         StudentTemplate_B.Product_hu[3],
                         StudentTemplate_P.f_400451_XData, 14U);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_400451_o),
                         StudentTemplate_P.f_400451_YData_p,
                         StudentTemplate_B.Product_hu[3],
                         StudentTemplate_P.f_400451_XData_n, 12U);

    /* MultiPortSwitch: '<S81>/Multiport Switch' */
    if ((int32_T)((uint32_T)(int32_T)StudentTemplate_B.Sum_nx >> 6) == 1) {
      StudentTemplate_B.MultiportSwitch_e = StudentTemplate_B.f_400451;
    } else {
      StudentTemplate_B.MultiportSwitch_e = StudentTemplate_B.f_400451_o;
    }

    /* Sum: '<S77>/Sum3' incorporates:
     *  Constant: '<S1>/offset u4'
     */
    StudentTemplate_B.Sum3_k = StudentTemplate_B.MultiportSwitch_e +
      StudentTemplate_P.offsetu4_Value;

    /* DeadZone Block: '<S82>/Dead Zone +-0.01'
     */
    if (StudentTemplate_B.Product_hu[4] >= StudentTemplate_P.DeadZone001_End) {
      StudentTemplate_B.DeadZone001 = StudentTemplate_B.Product_hu[4] -
        StudentTemplate_P.DeadZone001_End;
    } else if (StudentTemplate_B.Product_hu[4] >
               StudentTemplate_P.DeadZone001_Start) {
      StudentTemplate_B.DeadZone001 = 0.0;
    } else {
      StudentTemplate_B.DeadZone001 = StudentTemplate_B.Product_hu[4] -
        StudentTemplate_P.DeadZone001_Start;
    }

    /* RelationalOperator: '<S89>/Compare' incorporates:
     *  Constant: '<S89>/Constant'
     */
    StudentTemplate_B.Compare_b = (StudentTemplate_B.DeadZone001 <
      StudentTemplate_P.Constant_Value_ek);

    /* RelationalOperator: '<S91>/Compare' */
    StudentTemplate_B.Compare_gl = (StudentTemplate_B.DeadZone001 == 0.0);

    /* Gain: '<S82>/Gain' */
    StudentTemplate_B.Gain_o2 = (uint16_T)(StudentTemplate_P.Gain_Gain_en *
      StudentTemplate_B.Compare_gl);

    /* RelationalOperator: '<S90>/Compare' incorporates:
     *  Constant: '<S90>/Constant'
     */
    StudentTemplate_B.Compare_gl1 = (StudentTemplate_B.DeadZone001 >
      StudentTemplate_P.Constant_Value_o);

    /* Gain: '<S82>/Gain1' */
    StudentTemplate_B.Gain1_a = (uint16_T)(StudentTemplate_P.Gain1_Gain_c *
      StudentTemplate_B.Compare_gl1);

    /* Sum: '<S82>/Sum' */
    StudentTemplate_B.Sum_li = (uint16_T)(uint32_T)
      (((StudentTemplate_B.Compare_b << 6) + StudentTemplate_B.Gain_o2) +
       StudentTemplate_B.Gain1_a);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_50),
                         StudentTemplate_P.f_50_YData,
                         StudentTemplate_B.Product_hu[4],
                         StudentTemplate_P.f_50_XData, 9U);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.f_50_b),
                         StudentTemplate_P.f_50_YData_f,
                         StudentTemplate_B.Product_hu[4],
                         StudentTemplate_P.f_50_XData_a, 9U);

    /* MultiPortSwitch: '<S82>/Multiport Switch' incorporates:
     *  Constant: '<S82>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)StudentTemplate_B.Sum_li >> 6)) {
     case 1:
      StudentTemplate_B.MultiportSwitch_j = StudentTemplate_B.f_50;
      break;

     case 2:
      StudentTemplate_B.MultiportSwitch_j = StudentTemplate_P.f_50_Value;
      break;

     default:
      StudentTemplate_B.MultiportSwitch_j = StudentTemplate_B.f_50_b;
      break;
    }

    /* Saturate: '<S33>/Saturation' incorporates:
     *  Constant: '<S75>/BT_power_limit'
     *  Constant: '<S75>/VSP_speeds'
     */
    tmp_0[0] = StudentTemplate_B.Sum_j;
    tmp_0[1] = StudentTemplate_B.Sum1_o;
    tmp_0[2] = StudentTemplate_B.Sum2_p;
    tmp_0[3] = StudentTemplate_B.Sum3_k;
    tmp_0[4] = StudentTemplate_B.MultiportSwitch_j;
    tmp_0[5] = StudentTemplate_P.BT_power_limit_Value;
    tmp_0[6] = StudentTemplate_P.VSP_speeds_Value;
    for (i = 0; i < 7; i++) {
      StudentTemplate_B.Saturation_j[i] = rt_SATURATE(tmp_0[i],
        StudentTemplate_P.Saturation_LowerSat_ak,
        StudentTemplate_P.Saturation_UpperSat_k);
    }

    /* Gain: '<S166>/QTM In2 Error' */
    StudentTemplate_B.QTMIn2Error = StudentTemplate_P.QTMIn2Error_Gain *
      StudentTemplate_B.QTMIn[1];

    /* Gain: '<S166>/QTM In9 Residual' */
    StudentTemplate_B.QTMIn9Residual = StudentTemplate_P.QTMIn9Residual_Gain *
      StudentTemplate_B.QTMIn[8];
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Saturate: '<S193>/Saturation' incorporates:
       *  Constant: '<S1>/Control Mode Selector'
       */
      tmp = StudentTemplate_P.ControlModeSelector_Value;
      StudentTemplate_B.Saturation_iv = rt_SATURATE(tmp,
        StudentTemplate_P.Saturation_LowerSat_m,
        StudentTemplate_P.Saturation_UpperSat_a);
    }

    /* MultiPortSwitch: '<S193>/tau Switch' incorporates:
     *  Constant: '<S6>/PS3_BT_Power  [-]'
     *  Constant: '<S6>/PS3_VSP_Speed  [-]'
     */
    if ((int32_T)StudentTemplate_B.Saturation_iv == 0) {
      StudentTemplate_B.tauSwitch_o[0] = StudentTemplate_B.u_1;
      StudentTemplate_B.tauSwitch_o[1] = StudentTemplate_B.u_2;
      StudentTemplate_B.tauSwitch_o[2] = StudentTemplate_B.u_3;
      StudentTemplate_B.tauSwitch_o[3] = StudentTemplate_B.u_4;
      StudentTemplate_B.tauSwitch_o[4] = StudentTemplate_B.u_5;
      StudentTemplate_B.tauSwitch_o[5] = StudentTemplate_P.PS3_BT_Power_Value;
      StudentTemplate_B.tauSwitch_o[6] = StudentTemplate_P.PS3_VSP_Speed_Value;
    } else {
      for (i = 0; i < 7; i++) {
        StudentTemplate_B.tauSwitch_o[i] = StudentTemplate_B.Saturation_j[i];
      }
    }

    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* SignalConversion: '<S22>/TmpHiddenBufferAtTo FileInport1' incorporates:
       *  Constant: '<S1>/Control Input Selector'
       *  Constant: '<S1>/Control Mode Selector'
       *  Constant: '<S5>/Delta [m]'
       *  Constant: '<S5>/Path Selector  [-]'
       *  Constant: '<S5>/my [-]'
       *  Constant: '<S5>/u_d [m]'
       *  Constant: '<S7>/setpointx [m]'
       *  Constant: '<S7>/setpointy [m]'
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
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[0] =
        StudentTemplate_P.ControlModeSelector_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[1] =
        StudentTemplate_P.ControlInputSelector_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[2] =
        StudentTemplate_P.PathSelector_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[3] =
        StudentTemplate_B.QTMIn2Error;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[4] =
        StudentTemplate_B.QTMIn9Residual;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[5] =
        StudentTemplate_B.etaSwitch[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[6] =
        StudentTemplate_B.etaSwitch[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[7] =
        StudentTemplate_B.etaSwitch[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[8] =
        StudentTemplate_B.nuSwitch[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[9] =
        StudentTemplate_B.nuSwitch[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[10] =
        StudentTemplate_B.nuSwitch[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[11] =
        StudentTemplate_B.VectorConcatenate[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[12] =
        StudentTemplate_B.VectorConcatenate[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[13] =
        StudentTemplate_B.VectorConcatenate[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[14] =
        StudentTemplate_B.Integrator2[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[15] =
        StudentTemplate_B.Integrator2[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[16] =
        StudentTemplate_P.setpointxm_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[17] =
        StudentTemplate_P.setpointym_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[18] =
        StudentTemplate_B.Gain1;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[19] =
        StudentTemplate_B.Switch2;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[20] =
        StudentTemplate_B.Switch2_j;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[21] =
        StudentTemplate_B.Sum_b;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[22] =
        StudentTemplate_P.u_dm_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[23] =
        StudentTemplate_B.Divide_bz;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[24] =
        StudentTemplate_B.Integrator1;
      for (i = 0; i < 7; i++) {
        StudentTemplate_B.TmpHiddenBufferAtToFileInport1[i + 25] =
          StudentTemplate_B.tauSwitch_o[i];
      }

      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[32] =
        StudentTemplate_B.tauSwitch[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[33] =
        StudentTemplate_B.tauSwitch[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[34] =
        StudentTemplate_B.tauSwitch[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[35] =
        StudentTemplate_B.Product_m[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[36] =
        StudentTemplate_B.Product_m[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[37] =
        StudentTemplate_B.Product_m[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[38] =
        StudentTemplate_B.Product1[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[39] =
        StudentTemplate_B.Product1[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[40] =
        StudentTemplate_B.Product1[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[41] =
        StudentTemplate_B.Product2[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[42] =
        StudentTemplate_B.Product2[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[43] =
        StudentTemplate_B.Product2[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[44] =
        StudentTemplate_B.Gain_a[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[45] =
        StudentTemplate_B.Gain_a[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[46] =
        StudentTemplate_B.Gain_a[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[47] =
        StudentTemplate_B.Gain1_j[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[48] =
        StudentTemplate_B.Gain1_j[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[49] =
        StudentTemplate_B.Gain1_j[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[50] =
        StudentTemplate_B.Product2_g[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[51] =
        StudentTemplate_B.Product2_g[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[52] =
        StudentTemplate_B.Product2_g[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[53] =
        StudentTemplate_B.Product4_p[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[54] =
        StudentTemplate_B.Product4_p[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[55] =
        StudentTemplate_B.Product4_p[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[56] =
        StudentTemplate_B.Product5[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[57] =
        StudentTemplate_B.Product5[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[58] =
        StudentTemplate_B.Product5[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[59] =
        StudentTemplate_B.Product6[0];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[60] =
        StudentTemplate_B.Product6[1];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[61] =
        StudentTemplate_B.Product6[2];
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[62] =
        StudentTemplate_P.ctrl2Kpx_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[63] =
        StudentTemplate_P.ctrl2Kpy_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[64] =
        StudentTemplate_P.ctrl2Kppsi_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[65] =
        StudentTemplate_P.ctrl2Kix_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[66] =
        StudentTemplate_P.ctrl2Kiy_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[67] =
        StudentTemplate_P.ctrl2Kipsi_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[68] =
        StudentTemplate_P.ctrl2Kdx_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[69] =
        StudentTemplate_P.ctrl2Kdy_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[70] =
        StudentTemplate_P.ctrl2Kdpsi_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[71] =
        StudentTemplate_P.kappa_1_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[72] =
        StudentTemplate_P.ctrl2Kpx_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[73] =
        StudentTemplate_P.ctrl2Kpy_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[74] =
        StudentTemplate_P.ctrl2Kppsi_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[75] =
        StudentTemplate_P.ctrl2Kix_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[76] =
        StudentTemplate_P.ctrl2Kiy_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[77] =
        StudentTemplate_P.ctrl2Kipsi_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[78] =
        StudentTemplate_P.ctrl2Kdx_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[79] =
        StudentTemplate_P.ctrl2Kdy_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[80] =
        StudentTemplate_P.ctrl2Kdpsi_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[81] =
        StudentTemplate_P.Gamma_q_Surge_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[82] =
        StudentTemplate_P.Gamma_q_Sway_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[83] =
        StudentTemplate_P.lambda_q_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[84] =
        StudentTemplate_P.Deltam_Value;
      StudentTemplate_B.TmpHiddenBufferAtToFileInport1[85] =
        StudentTemplate_P.my_Value;

      /* ToFile Block: '<S22>/To File'
       */
      if (rtmIsMajorTimeStep(StudentTemplate_M)) {
        if (!(++StudentTemplate_DWork.ToFile_IWORK.Decimation % 1) &&
            (StudentTemplate_DWork.ToFile_IWORK.Count*87)+1 < 100000000 ) {
          real_T u[87];
          FILE *fp = (FILE *) StudentTemplate_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            StudentTemplate_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = StudentTemplate_M->Timing.t[1];
            u[1] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[22];
            u[24] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[23];
            u[25] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[24];
            u[26] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[25];
            u[27] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[26];
            u[28] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[27];
            u[29] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[28];
            u[30] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[29];
            u[31] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[30];
            u[32] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[31];
            u[33] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[32];
            u[34] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[33];
            u[35] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[34];
            u[36] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[35];
            u[37] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[36];
            u[38] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[37];
            u[39] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[38];
            u[40] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[39];
            u[41] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[40];
            u[42] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[41];
            u[43] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[42];
            u[44] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[43];
            u[45] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[44];
            u[46] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[45];
            u[47] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[46];
            u[48] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[47];
            u[49] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[48];
            u[50] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[49];
            u[51] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[50];
            u[52] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[51];
            u[53] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[52];
            u[54] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[53];
            u[55] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[54];
            u[56] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[55];
            u[57] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[56];
            u[58] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[57];
            u[59] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[58];
            u[60] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[59];
            u[61] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[60];
            u[62] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[61];
            u[63] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[62];
            u[64] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[63];
            u[65] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[64];
            u[66] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[65];
            u[67] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[66];
            u[68] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[67];
            u[69] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[68];
            u[70] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[69];
            u[71] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[70];
            u[72] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[71];
            u[73] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[72];
            u[74] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[73];
            u[75] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[74];
            u[76] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[75];
            u[77] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[76];
            u[78] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[77];
            u[79] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[78];
            u[80] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[79];
            u[81] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[80];
            u[82] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[81];
            u[83] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[82];
            u[84] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[83];
            u[85] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[84];
            u[86] = StudentTemplate_B.TmpHiddenBufferAtToFileInport1[85];
            if (fwrite(u, sizeof(real_T), 87, fp) != 87) {
              rtmSetErrorStatus(StudentTemplate_M,
                                "Error writing to MAT-file Student_data.mat");
              return;
            }

            if (((++StudentTemplate_DWork.ToFile_IWORK.Count)*87)+1 >= 100000000)
            {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file Student_data.mat.\n");
            }
          }
        }
      }
    }

    /* Gain: '<S166>/QTM In5 z-coord [mm]' */
    StudentTemplate_B.QTMIn5zcoordmm = StudentTemplate_P.QTMIn5zcoordmm_Gain *
      StudentTemplate_B.QTMIn[4];

    /* Gain: '<S166>/mm2m z' */
    StudentTemplate_B.mm2mz = StudentTemplate_P.mm2mz_Gain *
      StudentTemplate_B.QTMIn5zcoordmm;

    /* Gain: '<S166>/QTM In8 roll [deg]' */
    StudentTemplate_B.QTMIn8rolldeg = StudentTemplate_P.QTMIn8rolldeg_Gain *
      StudentTemplate_B.QTMIn[7];

    /* Gain: '<S166>/d2r roll' */
    StudentTemplate_B.d2rroll = StudentTemplate_P.d2rroll_Gain *
      StudentTemplate_B.QTMIn8rolldeg;

    /* Gain: '<S166>/QTM In7 pitch [deg]' */
    StudentTemplate_B.QTMIn7pitchdeg = StudentTemplate_P.QTMIn7pitchdeg_Gain *
      StudentTemplate_B.QTMIn[6];

    /* Gain: '<S166>/d2r pitch' */
    StudentTemplate_B.d2rpitch = StudentTemplate_P.d2rpitch_Gain *
      StudentTemplate_B.QTMIn7pitchdeg;

    /* Derivative Block: '<S166>/Derivative' */
    {
      real_T t = StudentTemplate_M->Timing.t[0];
      real_T timeStampA = StudentTemplate_DWork.Derivative_RWORK_d.TimeStampA;
      real_T timeStampB = StudentTemplate_DWork.Derivative_RWORK_d.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = StudentTemplate_B.Derivative_o;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &StudentTemplate_DWork.Derivative_RWORK_d.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        StudentTemplate_B.Derivative_o[0] = (StudentTemplate_B.mm2mx - *lastBank
          ++) / deltaT;
        StudentTemplate_B.Derivative_o[1] = (StudentTemplate_B.mm2my - *lastBank
          ++) / deltaT;
        StudentTemplate_B.Derivative_o[2] = (StudentTemplate_B.mm2mz - *lastBank
          ++) / deltaT;
        StudentTemplate_B.Derivative_o[3] = (StudentTemplate_B.d2rroll -
          *lastBank++) / deltaT;
        StudentTemplate_B.Derivative_o[4] = (StudentTemplate_B.d2rpitch -
          *lastBank++) / deltaT;
        StudentTemplate_B.Derivative_o[5] = (StudentTemplate_B.d2ryaw -
          *lastBank++) / deltaT;
      }
    }

    /* Trigonometry: '<S168>/sin(theta)' */
    StudentTemplate_B.sintheta[0] = sin(StudentTemplate_B.d2rroll);
    StudentTemplate_B.sintheta[1] = sin(StudentTemplate_B.d2rpitch);
    StudentTemplate_B.sintheta[2] = sin(StudentTemplate_B.d2ryaw);

    /* Trigonometry: '<S168>/cos(theta)' */
    StudentTemplate_B.costheta[0] = cos(StudentTemplate_B.d2rroll);
    StudentTemplate_B.costheta[1] = cos(StudentTemplate_B.d2rpitch);
    StudentTemplate_B.costheta[2] = cos(StudentTemplate_B.d2ryaw);

    /* Fcn: '<S168>/R11' */
    StudentTemplate_B.R11_d = StudentTemplate_B.costheta[1] *
      StudentTemplate_B.costheta[2];

    /* Fcn: '<S168>/R12' */
    StudentTemplate_B.R12_o = StudentTemplate_B.costheta[1] *
      StudentTemplate_B.sintheta[2];

    /* Fcn: '<S168>/R13' */
    StudentTemplate_B.R13 = -StudentTemplate_B.sintheta[1];

    /* Fcn: '<S168>/R21 ' */
    StudentTemplate_B.R21_j = StudentTemplate_B.sintheta[0] *
      StudentTemplate_B.sintheta[1] * StudentTemplate_B.costheta[2] +
      (-StudentTemplate_B.costheta[0]) * StudentTemplate_B.sintheta[2];

    /* Fcn: '<S168>/R22' */
    StudentTemplate_B.R22_g = StudentTemplate_B.sintheta[0] *
      StudentTemplate_B.sintheta[1] * StudentTemplate_B.sintheta[2] +
      StudentTemplate_B.costheta[0] * StudentTemplate_B.costheta[2];

    /* Fcn: '<S168>/R23' */
    StudentTemplate_B.R23 = StudentTemplate_B.sintheta[0] *
      StudentTemplate_B.costheta[1];

    /* Fcn: '<S168>/R31 ' */
    StudentTemplate_B.R31 = StudentTemplate_B.costheta[0] *
      StudentTemplate_B.sintheta[1] * StudentTemplate_B.costheta[2] +
      StudentTemplate_B.sintheta[0] * StudentTemplate_B.sintheta[2];

    /* Fcn: '<S168>/R32' */
    StudentTemplate_B.R32 = StudentTemplate_B.costheta[0] *
      StudentTemplate_B.sintheta[1] * StudentTemplate_B.sintheta[2] +
      (-StudentTemplate_B.sintheta[0]) * StudentTemplate_B.costheta[2];

    /* Fcn: '<S168>/R33' */
    StudentTemplate_B.R33 = StudentTemplate_B.costheta[0] *
      StudentTemplate_B.costheta[1];

    /* Reshape: '<S168>/Reshape 9x1->3x3' */
    StudentTemplate_B.Reshape9x13x3[0] = StudentTemplate_B.R11_d;
    StudentTemplate_B.Reshape9x13x3[1] = StudentTemplate_B.R21_j;
    StudentTemplate_B.Reshape9x13x3[2] = StudentTemplate_B.R31;
    StudentTemplate_B.Reshape9x13x3[3] = StudentTemplate_B.R12_o;
    StudentTemplate_B.Reshape9x13x3[4] = StudentTemplate_B.R22_g;
    StudentTemplate_B.Reshape9x13x3[5] = StudentTemplate_B.R32;
    StudentTemplate_B.Reshape9x13x3[6] = StudentTemplate_B.R13;
    StudentTemplate_B.Reshape9x13x3[7] = StudentTemplate_B.R23;
    StudentTemplate_B.Reshape9x13x3[8] = StudentTemplate_B.R33;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Product Block: '<S166>/Inverse' */
      {
        static const int_T dims[3] = { 3, 3, 3 };

        rt_MatDivRR_Dbl(StudentTemplate_B.Inverse, StudentTemplate_B.x3,
                        &StudentTemplate_DWork.Inverse_DWORK4[0], (real_T*)
                        &StudentTemplate_DWork.Pseudoinverse_X[0],
                        &StudentTemplate_DWork.Inverse_DWORK2[0], (real_T*)
                        &StudentTemplate_DWork.Inverse_DWORK3[0],
                        &dims[0]);
      }
    }

    /* Concatenate: '<S166>/Matrix Concatenate' incorporates:
     *  Constant: '<S166>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_5[6 * i] = StudentTemplate_B.Reshape9x13x3[3 * i];
      tmp_5[1 + 6 * i] = StudentTemplate_B.Reshape9x13x3[3 * i + 1];
      tmp_5[2 + 6 * i] = StudentTemplate_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_5[3 + 6 * i] = StudentTemplate_P.Constant1_Value[3 * i];
      tmp_5[4 + 6 * i] = StudentTemplate_P.Constant1_Value[3 * i + 1];
      tmp_5[5 + 6 * i] = StudentTemplate_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&StudentTemplate_B.MatrixConcatenate2[0]), (void *)&tmp_5[0],
           18U * sizeof(real_T));

    /* Concatenate: '<S166>/Matrix Concatenate1' incorporates:
     *  Constant: '<S166>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_5[6 * i] = StudentTemplate_P.Constant1_Value[3 * i];
      tmp_5[1 + 6 * i] = StudentTemplate_P.Constant1_Value[3 * i + 1];
      tmp_5[2 + 6 * i] = StudentTemplate_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_5[3 + 6 * i] = StudentTemplate_B.Reshape9x13x3[3 * i];
      tmp_5[4 + 6 * i] = StudentTemplate_B.Reshape9x13x3[3 * i + 1];
      tmp_5[5 + 6 * i] = StudentTemplate_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&StudentTemplate_B.MatrixConcatenate2[18]), (void *)&tmp_5[0],
           18U * sizeof(real_T));

    /* Product: '<S166>/Product' */
    for (i = 0; i < 6; i++) {
      StudentTemplate_B.Product_go[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 6; tmp_6++) {
        StudentTemplate_B.Product_go[i] = StudentTemplate_B.MatrixConcatenate2[6
          * tmp_6 + i] * StudentTemplate_B.Derivative_o[tmp_6] +
          StudentTemplate_B.Product_go[i];
      }
    }

    /* Gain: '<S166>/QTM In1 FN' */
    StudentTemplate_B.QTMIn1FN = StudentTemplate_P.QTMIn1FN_Gain *
      StudentTemplate_B.QTMIn[0];

    /* Integrator Block: '<S169>/Integrator'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE_l,
                         StudentTemplate_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || StudentTemplate_P.ctrl2ResetIntegrator_Value != 0.0 ||
          StudentTemplate_DWork.Integrator_IWORK_j.IcNeedsLoading) {
        StudentTemplate_X.Integrator_CSTATE_e[0] = StudentTemplate_B.mm2mx;
        StudentTemplate_X.Integrator_CSTATE_e[1] = StudentTemplate_B.mm2my;
        StudentTemplate_X.Integrator_CSTATE_e[2] = StudentTemplate_B.d2ryaw;
      }

      StudentTemplate_DWork.Integrator_IWORK_j.IcNeedsLoading = 0;
    }

    StudentTemplate_B.eta[0] = StudentTemplate_X.Integrator_CSTATE_e[0];
    StudentTemplate_B.eta[1] = StudentTemplate_X.Integrator_CSTATE_e[1];
    StudentTemplate_B.eta[2] = StudentTemplate_X.Integrator_CSTATE_e[2];

    /* Integrator: '<S169>/Integrator3' */
    StudentTemplate_B.bias[0] = StudentTemplate_X.Integrator3_CSTATE[0];
    StudentTemplate_B.bias[1] = StudentTemplate_X.Integrator3_CSTATE[1];
    StudentTemplate_B.bias[2] = StudentTemplate_X.Integrator3_CSTATE[2];

    /* Saturate: '<S174>/Saturation' */
    tmp = StudentTemplate_B.eta[2];
    StudentTemplate_B.Saturation_lr = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_fg,
      StudentTemplate_P.Saturation_UpperSat_kw);

    /* Signum: '<S174>/Sign' */
    StudentTemplate_B.Sign_ab = rt_SIGNd_snf(StudentTemplate_B.Saturation_lr);

    /* Gain: '<S174>/Gain' */
    StudentTemplate_B.Gain_cy = StudentTemplate_P.Gain_Gain_p0 *
      StudentTemplate_B.Sign_ab;

    /* Sum: '<S174>/Sum1' */
    StudentTemplate_B.Sum1_e = StudentTemplate_B.Saturation_lr +
      StudentTemplate_B.Gain_cy;

    /* Math: '<S174>/Math Function' incorporates:
     *  Constant: '<S174>/Constant'
     */
    StudentTemplate_B.MathFunction_hz = rt_rem_snf(StudentTemplate_B.Sum1_e,
      StudentTemplate_P.Constant_Value_f3);

    /* Sum: '<S174>/Sum' */
    StudentTemplate_B.Sum_bk = StudentTemplate_B.MathFunction_hz -
      StudentTemplate_B.Gain_cy;

    /* Sum: '<S169>/Sum2' */
    StudentTemplate_B.Sum2_b[0] = StudentTemplate_B.mm2mx -
      StudentTemplate_B.eta[0];
    StudentTemplate_B.Sum2_b[1] = StudentTemplate_B.mm2my -
      StudentTemplate_B.eta[1];
    StudentTemplate_B.Sum2_b[2] = StudentTemplate_B.d2ryaw -
      StudentTemplate_B.Sum_bk;

    /* Saturate: '<S175>/Saturation' */
    tmp = StudentTemplate_B.Sum2_b[2];
    StudentTemplate_B.Saturation_b = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_k,
      StudentTemplate_P.Saturation_UpperSat_ft);

    /* Signum: '<S175>/Sign' */
    StudentTemplate_B.Sign_j = rt_SIGNd_snf(StudentTemplate_B.Saturation_b);

    /* Gain: '<S175>/Gain' */
    StudentTemplate_B.Gain_cb = StudentTemplate_P.Gain_Gain_b *
      StudentTemplate_B.Sign_j;

    /* Sum: '<S175>/Sum1' */
    StudentTemplate_B.Sum1_ll = StudentTemplate_B.Saturation_b +
      StudentTemplate_B.Gain_cb;

    /* Math: '<S175>/Math Function' incorporates:
     *  Constant: '<S175>/Constant'
     */
    StudentTemplate_B.MathFunction_fr = rt_rem_snf(StudentTemplate_B.Sum1_ll,
      StudentTemplate_P.Constant_Value_cz);

    /* Sum: '<S175>/Sum' */
    StudentTemplate_B.Sum_ez = StudentTemplate_B.MathFunction_fr -
      StudentTemplate_B.Gain_cb;

    /* SignalConversion: '<S169>/TmpHiddenBufferAtK2Inport1' */
    StudentTemplate_B.TmpHiddenBufferAtK2Inport1[0] = StudentTemplate_B.Sum2_b[0];
    StudentTemplate_B.TmpHiddenBufferAtK2Inport1[1] = StudentTemplate_B.Sum2_b[1];
    StudentTemplate_B.TmpHiddenBufferAtK2Inport1[2] = StudentTemplate_B.Sum_ez;
    for (i = 0; i < 3; i++) {
      /* Gain: '<S169>/K2' */
      StudentTemplate_B.K2[i] = 0.0;
      StudentTemplate_B.K2[i] = StudentTemplate_P.K2_Gain[i] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[0] + StudentTemplate_B.K2[i];
      StudentTemplate_B.K2[i] = StudentTemplate_P.K2_Gain[i + 3] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[1] + StudentTemplate_B.K2[i];
      StudentTemplate_B.K2[i] = StudentTemplate_P.K2_Gain[i + 6] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[2] + StudentTemplate_B.K2[i];

      /* Gain: '<S169>/K3' */
      StudentTemplate_B.K3[i] = 0.0;
      StudentTemplate_B.K3[i] = StudentTemplate_P.K3_Gain[i] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[0] + StudentTemplate_B.K3[i];
      StudentTemplate_B.K3[i] = StudentTemplate_P.K3_Gain[i + 3] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[1] + StudentTemplate_B.K3[i];
      StudentTemplate_B.K3[i] = StudentTemplate_P.K3_Gain[i + 6] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[2] + StudentTemplate_B.K3[i];

      /* Gain: '<S169>/K4' */
      StudentTemplate_B.K4[i] = 0.0;
      StudentTemplate_B.K4[i] = StudentTemplate_P.K4_Gain[i] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[0] + StudentTemplate_B.K4[i];
      StudentTemplate_B.K4[i] = StudentTemplate_P.K4_Gain[i + 3] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[1] + StudentTemplate_B.K4[i];
      StudentTemplate_B.K4[i] = StudentTemplate_P.K4_Gain[i + 6] *
        StudentTemplate_B.TmpHiddenBufferAtK2Inport1[2] + StudentTemplate_B.K4[i];
    }

    /* Fcn: '<S172>/Row1' */
    StudentTemplate_B.Row1_k = cos(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.K4[0] + sin(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.K4[1];

    /* Fcn: '<S172>/Row2' */
    StudentTemplate_B.Row2_o = (-sin(StudentTemplate_B.d2ryaw)) *
      StudentTemplate_B.K4[0] + cos(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.K4[1];

    /* Fcn: '<S172>/Row3' */
    StudentTemplate_B.Row3_g = StudentTemplate_B.K4[2];

    /* Fcn: '<S173>/Row1' */
    StudentTemplate_B.Row1_g = cos(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.bias[0] + sin(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.bias[1];

    /* Fcn: '<S173>/Row2' */
    StudentTemplate_B.Row2_i = (-sin(StudentTemplate_B.d2ryaw)) *
      StudentTemplate_B.bias[0] + cos(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.bias[1];

    /* Fcn: '<S173>/Row3' */
    StudentTemplate_B.Row3_d = StudentTemplate_B.bias[2];

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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_1tof_1_o),
                         StudentTemplate_P.u_1tof_1_YData_i,
                         StudentTemplate_B.Saturation_j[0],
                         StudentTemplate_P.u_1tof_1_XData_p, 38U);

    /* RelationalOperator: '<S182>/Compare' incorporates:
     *  Constant: '<S182>/Constant'
     */
    StudentTemplate_B.Compare_cv = (StudentTemplate_B.Saturation_j[1] <
      StudentTemplate_P.Constant_Value_it);

    /* RelationalOperator: '<S184>/Compare' incorporates:
     *  Constant: '<S184>/Constant'
     */
    StudentTemplate_B.Compare_ev = (StudentTemplate_B.Saturation_j[1] >=
      StudentTemplate_P.Constant_Value_pt);

    /* RelationalOperator: '<S183>/Compare' incorporates:
     *  Constant: '<S183>/Constant'
     */
    StudentTemplate_B.Compare_i = (StudentTemplate_B.Saturation_j[1] <
      StudentTemplate_P.Constant_Value_fy);

    /* Logic: '<S178>/Logical Operator' */
    StudentTemplate_B.LogicalOperator_o = ((StudentTemplate_B.Compare_ev != 0) &&
      (StudentTemplate_B.Compare_i != 0));

    /* Sum: '<S178>/Sum1' */
    StudentTemplate_B.Sum1_kz = (uint8_T)(StudentTemplate_B.LogicalOperator_o +
      StudentTemplate_B.LogicalOperator_o);

    /* RelationalOperator: '<S185>/Compare' incorporates:
     *  Constant: '<S185>/Constant'
     */
    StudentTemplate_B.Compare_o = (StudentTemplate_B.Saturation_j[1] >=
      StudentTemplate_P.Constant_Value_jd);

    /* Gain: '<S178>/Gain1' */
    StudentTemplate_B.Gain1_c = (uint16_T)(StudentTemplate_P.Gain1_Gain_g *
      StudentTemplate_B.Compare_o);

    /* Sum: '<S178>/Sum' */
    StudentTemplate_B.Sum_ol = (uint16_T)(uint32_T)
      (((StudentTemplate_B.Compare_cv << 6) + (StudentTemplate_B.Sum1_kz << 6))
       + StudentTemplate_B.Gain1_c);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_205),
                         StudentTemplate_P.u_205_YData,
                         StudentTemplate_B.Saturation_j[1],
                         StudentTemplate_P.u_205_XData, 10U);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_201u_202),
                         StudentTemplate_P.u_201u_202_YData,
                         StudentTemplate_B.Saturation_j[1],
                         StudentTemplate_P.u_201u_202_XData, 2U);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_20),
                         StudentTemplate_P.u_20_YData,
                         StudentTemplate_B.Saturation_j[1],
                         StudentTemplate_P.u_20_XData, 17U);

    /* MultiPortSwitch: '<S178>/Multiport Switch' */
    switch ((int32_T)((uint32_T)(int32_T)StudentTemplate_B.Sum_ol >> 6)) {
     case 1:
      StudentTemplate_B.MultiportSwitch_k = StudentTemplate_B.u_205;
      break;

     case 2:
      StudentTemplate_B.MultiportSwitch_k = StudentTemplate_B.u_201u_202;
      break;

     default:
      StudentTemplate_B.MultiportSwitch_k = StudentTemplate_B.u_20;
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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_3tof_3_g),
                         StudentTemplate_P.u_3tof_3_YData_a,
                         StudentTemplate_B.Saturation_j[2],
                         StudentTemplate_P.u_3tof_3_XData_e, 38U);

    /* RelationalOperator: '<S186>/Compare' incorporates:
     *  Constant: '<S186>/Constant'
     */
    StudentTemplate_B.Compare_i4 = (StudentTemplate_B.Saturation_j[3] <
      StudentTemplate_P.Constant_Value_bh);

    /* RelationalOperator: '<S187>/Compare' incorporates:
     *  Constant: '<S187>/Constant'
     */
    StudentTemplate_B.Compare_p = (StudentTemplate_B.Saturation_j[3] >=
      StudentTemplate_P.Constant_Value_cy);

    /* Gain: '<S180>/Gain' */
    StudentTemplate_B.Gain_f0 = (uint16_T)(StudentTemplate_P.Gain_Gain_as *
      StudentTemplate_B.Compare_p);

    /* Sum: '<S180>/Sum' */
    StudentTemplate_B.Sum_ld = (uint16_T)(uint32_T)
      ((StudentTemplate_B.Compare_i4 << 6) + StudentTemplate_B.Gain_f0);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_401),
                         StudentTemplate_P.u_401_YData,
                         StudentTemplate_B.Saturation_j[3],
                         StudentTemplate_P.u_401_XData, 14U);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_401_b),
                         StudentTemplate_P.u_401_YData_e,
                         StudentTemplate_B.Saturation_j[3],
                         StudentTemplate_P.u_401_XData_m, 12U);

    /* MultiPortSwitch: '<S180>/Multiport Switch' */
    if ((int32_T)((uint32_T)(int32_T)StudentTemplate_B.Sum_ld >> 6) == 1) {
      StudentTemplate_B.MultiportSwitch_i = StudentTemplate_B.u_401;
    } else {
      StudentTemplate_B.MultiportSwitch_i = StudentTemplate_B.u_401_b;
    }

    /* DeadZone Block: '<S181>/Dead Zone +-0.01'
     */
    if (StudentTemplate_B.Saturation_j[4] >= StudentTemplate_P.DeadZone001_End_k)
    {
      StudentTemplate_B.DeadZone001_c = StudentTemplate_B.Saturation_j[4] -
        StudentTemplate_P.DeadZone001_End_k;
    } else if (StudentTemplate_B.Saturation_j[4] >
               StudentTemplate_P.DeadZone001_Start_e) {
      StudentTemplate_B.DeadZone001_c = 0.0;
    } else {
      StudentTemplate_B.DeadZone001_c = StudentTemplate_B.Saturation_j[4] -
        StudentTemplate_P.DeadZone001_Start_e;
    }

    /* RelationalOperator: '<S188>/Compare' incorporates:
     *  Constant: '<S188>/Constant'
     */
    StudentTemplate_B.Compare_n = (StudentTemplate_B.DeadZone001_c <
      StudentTemplate_P.Constant_Value_dp);

    /* RelationalOperator: '<S190>/Compare' */
    StudentTemplate_B.Compare_a = (StudentTemplate_B.DeadZone001_c == 0.0);

    /* Gain: '<S181>/Gain' */
    StudentTemplate_B.Gain_lg = (uint16_T)(StudentTemplate_P.Gain_Gain_hc *
      StudentTemplate_B.Compare_a);

    /* RelationalOperator: '<S189>/Compare' incorporates:
     *  Constant: '<S189>/Constant'
     */
    StudentTemplate_B.Compare_ln = (StudentTemplate_B.DeadZone001_c >
      StudentTemplate_P.Constant_Value_hu);

    /* Gain: '<S181>/Gain1' */
    StudentTemplate_B.Gain1_h = (uint16_T)(StudentTemplate_P.Gain1_Gain_h *
      StudentTemplate_B.Compare_ln);

    /* Sum: '<S181>/Sum' */
    StudentTemplate_B.Sum_k = (uint16_T)(uint32_T)(((StudentTemplate_B.Compare_n
      << 6) + StudentTemplate_B.Gain_lg) + StudentTemplate_B.Gain1_h);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_50),
                         StudentTemplate_P.u_50_YData,
                         StudentTemplate_B.Saturation_j[4],
                         StudentTemplate_P.u_50_XData, 9U);

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
    LookUp_real_T_real_T( &(StudentTemplate_B.u_50_d),
                         StudentTemplate_P.u_50_YData_g,
                         StudentTemplate_B.Saturation_j[4],
                         StudentTemplate_P.u_50_XData_d, 9U);

    /* MultiPortSwitch: '<S181>/Multiport Switch' incorporates:
     *  Constant: '<S181>/u_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)StudentTemplate_B.Sum_k >> 6)) {
     case 1:
      StudentTemplate_B.MultiportSwitch_m = StudentTemplate_B.u_50;
      break;

     case 2:
      StudentTemplate_B.MultiportSwitch_m = StudentTemplate_P.u_50_Value;
      break;

     default:
      StudentTemplate_B.MultiportSwitch_m = StudentTemplate_B.u_50_d;
      break;
    }

    /* SignalConversion: '<S170>/TmpHiddenBufferAtProduct1Inport2' */
    StudentTemplate_B.TmpHiddenBufferAtProduct1Inport[0] =
      StudentTemplate_B.u_1tof_1_o;
    StudentTemplate_B.TmpHiddenBufferAtProduct1Inport[1] =
      StudentTemplate_B.MultiportSwitch_k;
    StudentTemplate_B.TmpHiddenBufferAtProduct1Inport[2] =
      StudentTemplate_B.u_3tof_3_g;
    StudentTemplate_B.TmpHiddenBufferAtProduct1Inport[3] =
      StudentTemplate_B.MultiportSwitch_i;
    StudentTemplate_B.TmpHiddenBufferAtProduct1Inport[4] =
      StudentTemplate_B.MultiportSwitch_m;

    /* Sum: '<S169>/Sum1' */
    for (i = 0; i < 3; i++) {
      /* Product: '<S170>/Product1' */
      StudentTemplate_B.Product1_dl[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
        StudentTemplate_B.Product1_dl[i] = StudentTemplate_B.x5[3 * tmp_6 + i] *
          StudentTemplate_B.TmpHiddenBufferAtProduct1Inport[tmp_6] +
          StudentTemplate_B.Product1_dl[i];
      }

      /* Product: '<S169>/Product1' */
      StudentTemplate_B.Product1_k0[i] = 0.0;
      StudentTemplate_B.Product1_k0[i] =
        StudentTemplate_B.LinearDampningmatrix[i] * StudentTemplate_B.nu[0] +
        StudentTemplate_B.Product1_k0[i];
      StudentTemplate_B.Product1_k0[i] =
        StudentTemplate_B.LinearDampningmatrix[i + 3] * StudentTemplate_B.nu[1]
        + StudentTemplate_B.Product1_k0[i];
      StudentTemplate_B.Product1_k0[i] =
        StudentTemplate_B.LinearDampningmatrix[i + 6] * StudentTemplate_B.nu[2]
        + StudentTemplate_B.Product1_k0[i];
    }

    StudentTemplate_B.Sum1_eh[0] = StudentTemplate_B.Row1_g +
      StudentTemplate_B.Product1_dl[0];
    StudentTemplate_B.Sum1_eh[1] = StudentTemplate_B.Row2_i +
      StudentTemplate_B.Product1_dl[1];
    StudentTemplate_B.Sum1_eh[2] = StudentTemplate_B.Row3_d +
      StudentTemplate_B.Product1_dl[2];

    /* Sum: '<S169>/Sum8' */
    StudentTemplate_B.Sum8[0] = (StudentTemplate_B.Row1_k +
      StudentTemplate_B.Sum1_eh[0]) - StudentTemplate_B.Product1_k0[0];
    StudentTemplate_B.Sum8[1] = (StudentTemplate_B.Row2_o +
      StudentTemplate_B.Sum1_eh[1]) - StudentTemplate_B.Product1_k0[1];
    StudentTemplate_B.Sum8[2] = (StudentTemplate_B.Row3_g +
      StudentTemplate_B.Sum1_eh[2]) - StudentTemplate_B.Product1_k0[2];

    /* Fcn: '<S171>/Fcn' */
    StudentTemplate_B.x_dot = cos(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.nu[0] - sin(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.nu[1];

    /* Fcn: '<S171>/Fcn1' */
    StudentTemplate_B.y_dot = sin(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.nu[0] + cos(StudentTemplate_B.d2ryaw) *
      StudentTemplate_B.nu[1];

    /* Fcn: '<S171>/Fcn2' */
    StudentTemplate_B.psi_dot = StudentTemplate_B.nu[2];

    /* Sum: '<S169>/Sum3' */
    StudentTemplate_B.Sum3_h[0] = StudentTemplate_B.K2[0] +
      StudentTemplate_B.x_dot;
    StudentTemplate_B.Sum3_h[1] = StudentTemplate_B.K2[1] +
      StudentTemplate_B.y_dot;
    StudentTemplate_B.Sum3_h[2] = StudentTemplate_B.K2[2] +
      StudentTemplate_B.psi_dot;
    for (i = 0; i < 3; i++) {
      /* Product: '<S169>/Product' */
      StudentTemplate_B.Product_ay[i] = 0.0;
      StudentTemplate_B.Product_ay[i] = StudentTemplate_B.Inverse[i] *
        StudentTemplate_B.Sum8[0] + StudentTemplate_B.Product_ay[i];
      StudentTemplate_B.Product_ay[i] = StudentTemplate_B.Inverse[i + 3] *
        StudentTemplate_B.Sum8[1] + StudentTemplate_B.Product_ay[i];
      StudentTemplate_B.Product_ay[i] = StudentTemplate_B.Inverse[i + 6] *
        StudentTemplate_B.Sum8[2] + StudentTemplate_B.Product_ay[i];

      /* Gain: '<S169>/inv(T_b)' */
      StudentTemplate_B.invT_b[i] = 0.0;
      StudentTemplate_B.invT_b[i] = StudentTemplate_P.invT_b_Gain[i] *
        StudentTemplate_B.bias[0] + StudentTemplate_B.invT_b[i];
      StudentTemplate_B.invT_b[i] = StudentTemplate_P.invT_b_Gain[i + 3] *
        StudentTemplate_B.bias[1] + StudentTemplate_B.invT_b[i];
      StudentTemplate_B.invT_b[i] = StudentTemplate_P.invT_b_Gain[i + 6] *
        StudentTemplate_B.bias[2] + StudentTemplate_B.invT_b[i];

      /* Sum: '<S169>/Sum7' */
      StudentTemplate_B.Sum7[i] = StudentTemplate_B.K3[i] -
        StudentTemplate_B.invT_b[i];
    }

    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
    }

    /* Outputs for enable SubSystem: '<S25>/CSE1 actuator' incorporates:
     *  Constant: '<S1>/Enable CSE1'
     *  EnablePort: '<S191>/Enable'
     */
    if (rtmIsMajorTimeStep(StudentTemplate_M) && rtmIsMajorTimeStep
        (StudentTemplate_M)) {
      if (StudentTemplate_P.EnableCSE1_Value > 0.0) {
        if (StudentTemplate_DWork.CSE1actuator_MODE == SUBSYS_DISABLED) {
          StudentTemplate_DWork.CSE1actuator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (StudentTemplate_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
          StudentTemplate_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (StudentTemplate_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S195>/BT_D_Gain1' */
      StudentTemplate_B.BT_D_Gain1 = StudentTemplate_P.BT_D_Gain1_Gain *
        StudentTemplate_B.tauSwitch_o[4];

      /* Gain: '<S195>/BT_D_Gain2' */
      StudentTemplate_B.BT_D_Gain2 = StudentTemplate_P.BT_D_Gain2_Gain *
        StudentTemplate_B.tauSwitch_o[4];

      /* Sum: '<S195>/Add' incorporates:
       *  Constant: '<S195>/BT_Power_Offset1'
       */
      StudentTemplate_B.Add_j = (StudentTemplate_B.BT_D_Gain1 +
        StudentTemplate_P.BT_Power_Offset1_Value) + StudentTemplate_B.BT_D_Gain2;

      /* Gain: '<S195>/BT_L_Gain1' */
      StudentTemplate_B.BT_L_Gain1 = StudentTemplate_P.BT_L_Gain1_Gain *
        StudentTemplate_B.tauSwitch_o[5];

      /* Gain: '<S195>/BT_L_Gain2' */
      StudentTemplate_B.BT_L_Gain2 = StudentTemplate_P.BT_L_Gain2_Gain *
        StudentTemplate_B.tauSwitch_o[5];

      /* Gain: '<S195>/Neg' */
      StudentTemplate_B.Neg = StudentTemplate_P.Neg_Gain *
        StudentTemplate_B.tauSwitch_o[5];
      if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      }

      /* Sum: '<S195>/Sum1' incorporates:
       *  Constant: '<S195>/BT_Power_Offset2'
       */
      StudentTemplate_B.Sum1_f = StudentTemplate_B.BT_L_Gain1 +
        StudentTemplate_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S197>/LowerRelop1' */
      StudentTemplate_B.LowerRelop1_p = (StudentTemplate_B.Add_j >
        StudentTemplate_B.Sum1_f);

      /* Sum: '<S195>/Sum2' incorporates:
       *  Constant: '<S195>/BT_Power_Offset3'
       */
      StudentTemplate_B.Sum2_i = StudentTemplate_B.BT_L_Gain2 +
        StudentTemplate_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S197>/UpperRelop' */
      StudentTemplate_B.UpperRelop_h = (StudentTemplate_B.Add_j <
        StudentTemplate_B.Sum2_i);

      /* Switch: '<S197>/Switch' */
      if (StudentTemplate_B.UpperRelop_h) {
        StudentTemplate_B.Switch_j = StudentTemplate_B.Sum2_i;
      } else {
        StudentTemplate_B.Switch_j = StudentTemplate_B.Add_j;
      }

      /* Switch: '<S197>/Switch2' */
      if (StudentTemplate_B.LowerRelop1_p) {
        StudentTemplate_B.Switch2_o = StudentTemplate_B.Sum1_f;
      } else {
        StudentTemplate_B.Switch2_o = StudentTemplate_B.Switch_j;
      }

      if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      }

      /* RelationalOperator: '<S198>/LowerRelop1' incorporates:
       *  Constant: '<S195>/Constant'
       */
      StudentTemplate_B.LowerRelop1_o = (StudentTemplate_B.tauSwitch_o[4] >
        StudentTemplate_P.Constant_Value_l);

      /* RelationalOperator: '<S198>/UpperRelop' */
      StudentTemplate_B.UpperRelop_n = (StudentTemplate_B.tauSwitch_o[4] <
        StudentTemplate_B.Neg);

      /* Switch: '<S198>/Switch' */
      if (StudentTemplate_B.UpperRelop_n) {
        StudentTemplate_B.Switch_ei = StudentTemplate_B.Neg;
      } else {
        StudentTemplate_B.Switch_ei = StudentTemplate_B.tauSwitch_o[4];
      }

      /* Switch: '<S198>/Switch2' incorporates:
       *  Constant: '<S195>/Constant'
       */
      if (StudentTemplate_B.LowerRelop1_o) {
        StudentTemplate_B.Switch2_g = StudentTemplate_P.Constant_Value_l;
      } else {
        StudentTemplate_B.Switch2_g = StudentTemplate_B.Switch_ei;
      }

      if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      }

      /* RelationalOperator: '<S199>/LowerRelop1' */
      StudentTemplate_B.LowerRelop1_j = (StudentTemplate_B.tauSwitch_o[4] >
        StudentTemplate_B.tauSwitch_o[5]);

      /* RelationalOperator: '<S199>/UpperRelop' incorporates:
       *  Constant: '<S195>/Constant1'
       */
      StudentTemplate_B.UpperRelop_nc = (StudentTemplate_B.tauSwitch_o[4] <
        StudentTemplate_P.Constant1_Value_k);

      /* Switch: '<S199>/Switch' incorporates:
       *  Constant: '<S195>/Constant1'
       */
      if (StudentTemplate_B.UpperRelop_nc) {
        StudentTemplate_B.Switch_a = StudentTemplate_P.Constant1_Value_k;
      } else {
        StudentTemplate_B.Switch_a = StudentTemplate_B.tauSwitch_o[4];
      }

      /* Switch: '<S199>/Switch2' */
      if (StudentTemplate_B.LowerRelop1_j) {
        StudentTemplate_B.Switch2_i = StudentTemplate_B.tauSwitch_o[5];
      } else {
        StudentTemplate_B.Switch2_i = StudentTemplate_B.Switch_a;
      }

      /* Signum: '<S196>/Sign' */
      StudentTemplate_B.Sign_gy = rt_SIGNd_snf(StudentTemplate_B.tauSwitch_o[6]);

      /* Product: '<S196>/Product1' */
      StudentTemplate_B.PortVPS_X = StudentTemplate_B.tauSwitch_o[1] *
        StudentTemplate_B.Sign_gy;

      /* Gain: '<S196>/-x' */
      StudentTemplate_B.PortVPS_X_e = StudentTemplate_P.x_Gain *
        StudentTemplate_B.PortVPS_X;

      /* Product: '<S196>/Product2' */
      StudentTemplate_B.PortVSP_Y = StudentTemplate_B.tauSwitch_o[0] *
        StudentTemplate_B.Sign_gy;

      /* Gain: '<S196>/-y' */
      StudentTemplate_B.PortVSP_Y_h = StudentTemplate_P.y_Gain *
        StudentTemplate_B.PortVSP_Y;

      /* Product: '<S196>/Product3' */
      StudentTemplate_B.StarboardVSP_X = StudentTemplate_B.tauSwitch_o[3] *
        StudentTemplate_B.Sign_gy;

      /* Product: '<S196>/Product4' */
      StudentTemplate_B.StarboardVSP_Y = StudentTemplate_B.tauSwitch_o[2] *
        StudentTemplate_B.Sign_gy;

      /* Lookup2D: '<S196>/Servo1' */
      StudentTemplate_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&StudentTemplate_P.Servo1_RowIdx[0]), 3, (const real_T *)
        (&StudentTemplate_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&StudentTemplate_P.Servo1_Table[0]), (const real_T)
        StudentTemplate_B.PortVPS_X_e, (const real_T)
        StudentTemplate_B.PortVSP_Y_h);

      /* Lookup2D: '<S196>/Servo2' */
      StudentTemplate_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&StudentTemplate_P.Servo2_RowIdx[0]), 3, (const real_T *)
        (&StudentTemplate_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&StudentTemplate_P.Servo2_Table[0]), (const real_T)
        StudentTemplate_B.PortVPS_X_e, (const real_T)
        StudentTemplate_B.PortVSP_Y_h);

      /* Lookup2D: '<S196>/Servo3' */
      StudentTemplate_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&StudentTemplate_P.Servo3_RowIdx[0]), 3, (const real_T *)
        (&StudentTemplate_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&StudentTemplate_P.Servo3_Table[0]), (const real_T)
        StudentTemplate_B.StarboardVSP_X, (const real_T)
        StudentTemplate_B.StarboardVSP_Y);

      /* Lookup2D: '<S196>/Servo4' */
      StudentTemplate_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&StudentTemplate_P.Servo4_RowIdx[0]), 3, (const real_T *)
        (&StudentTemplate_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&StudentTemplate_P.Servo4_Table[0]), (const real_T)
        StudentTemplate_B.StarboardVSP_X, (const real_T)
        StudentTemplate_B.StarboardVSP_Y);

      /* Gain: '<S196>/VPS_Speed_Gain' */
      StudentTemplate_B.VPS_Speed_Gain = StudentTemplate_P.VPS_Speed_Gain_Gain *
        StudentTemplate_B.tauSwitch_o[6];

      /* Sum: '<S196>/Sum' incorporates:
       *  Constant: '<S196>/VPS_Power_Offset'
       */
      StudentTemplate_B.Sum_c = StudentTemplate_B.VPS_Speed_Gain +
        StudentTemplate_P.VPS_Power_Offset_Value;

      /* Gain: '<S196>/VSPS Port' */
      StudentTemplate_B.VSPSPort = StudentTemplate_P.VSPSPort_Gain *
        StudentTemplate_B.Sum_c;

      /* Gain: '<S196>/VSPS Starboard' */
      StudentTemplate_B.VSPSStarboard = StudentTemplate_P.VSPSStarboard_Gain *
        StudentTemplate_B.Sum_c;
    }

    /* end of Outputs for SubSystem: '<S25>/CSE1 actuator' */
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Product Block: '<S25>/Inverse' */
      {
        static const int_T dims[3] = { 3, 3, 3 };

        rt_MatDivRR_Dbl(StudentTemplate_B.Inverse_c, StudentTemplate_B.x3,
                        &StudentTemplate_DWork.Inverse_DWORK4_f[0], (real_T*)
                        &StudentTemplate_DWork.Pseudoinverse_X[0],
                        &StudentTemplate_DWork.Inverse_DWORK2[0], (real_T*)
                        &StudentTemplate_DWork.Inverse_DWORK3[0],
                        &dims[0]);
      }
    }

    /* Saturate: '<S194>/Saturation' */
    tmp = StudentTemplate_B.tauSwitch[0];
    StudentTemplate_B.Saturation_a = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation_LowerSat_oc,
      StudentTemplate_P.Saturation_UpperSat_p);

    /* Saturate: '<S194>/Saturation1' */
    tmp = StudentTemplate_B.tauSwitch[1];
    StudentTemplate_B.Saturation1 = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation1_LowerSat,
      StudentTemplate_P.Saturation1_UpperSat);

    /* Saturate: '<S194>/Saturation2' */
    tmp = StudentTemplate_B.tauSwitch[2];
    StudentTemplate_B.Saturation2 = rt_SATURATE(tmp,
      StudentTemplate_P.Saturation2_LowerSat,
      StudentTemplate_P.Saturation2_UpperSat);

    /* Gain: '<S194>/plant tau_surge' */
    StudentTemplate_B.planttau_surge = StudentTemplate_P.planttau_surge_Gain *
      StudentTemplate_B.Saturation_a;

    /* Gain: '<S194>/plant tau_sway' */
    StudentTemplate_B.planttau_sway = StudentTemplate_P.planttau_sway_Gain *
      StudentTemplate_B.Saturation1;

    /* Gain: '<S194>/plant tau_yaw' */
    StudentTemplate_B.planttau_yaw = StudentTemplate_P.planttau_yaw_Gain *
      StudentTemplate_B.Saturation2;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
      /* Gain: '<S202>/Battery Bow Thruster' */
      StudentTemplate_B.BatteryBowThruster =
        StudentTemplate_P.BatteryBowThruster_Gain * StudentTemplate_B.SITzAI0;

      /* Gain: '<S202>/Battery Main' */
      StudentTemplate_B.BatteryMain = StudentTemplate_P.BatteryMain_Gain *
        StudentTemplate_B.SITzAI2;

      /* Gain: '<S202>/Battery Servo' */
      StudentTemplate_B.BatteryServo = StudentTemplate_P.BatteryServo_Gain *
        StudentTemplate_B.SITzAI1;
    }

    /* Gain: '<S203>/plant BT power' */
    StudentTemplate_B.plantBTpower = StudentTemplate_P.plantBTpower_Gain *
      StudentTemplate_B.tauSwitch_o[5];

    /* Gain: '<S203>/plant VSP speed' */
    StudentTemplate_B.plantVSPspeed = StudentTemplate_P.plantVSPspeed_Gain *
      StudentTemplate_B.tauSwitch_o[6];

    /* Gain: '<S203>/plant u_1' */
    StudentTemplate_B.plantu_1 = StudentTemplate_P.plantu_1_Gain *
      StudentTemplate_B.tauSwitch_o[0];

    /* Gain: '<S203>/plant u_2' */
    StudentTemplate_B.plantu_2 = StudentTemplate_P.plantu_2_Gain *
      StudentTemplate_B.tauSwitch_o[1];

    /* Gain: '<S203>/plant u_3' */
    StudentTemplate_B.plantu_3 = StudentTemplate_P.plantu_3_Gain *
      StudentTemplate_B.tauSwitch_o[2];

    /* Gain: '<S203>/plant u_4' */
    StudentTemplate_B.plantu_4 = StudentTemplate_P.plantu_4_Gain *
      StudentTemplate_B.tauSwitch_o[3];

    /* Gain: '<S203>/plant u_5' */
    StudentTemplate_B.plantu_5 = StudentTemplate_P.plantu_5_Gain *
      StudentTemplate_B.tauSwitch_o[4];

    /* Gain: '<S203>/fact1' */
    StudentTemplate_B.fact1 = StudentTemplate_P.fact1_Gain *
      StudentTemplate_B.Product_hu[0];

    /* Gain: '<S203>/fact2' */
    StudentTemplate_B.fact2 = StudentTemplate_P.fact2_Gain *
      StudentTemplate_B.Product_hu[1];

    /* Gain: '<S203>/fact3' */
    StudentTemplate_B.fact3 = StudentTemplate_P.fact3_Gain *
      StudentTemplate_B.Product_hu[2];

    /* Gain: '<S203>/fact4' */
    StudentTemplate_B.fact4 = StudentTemplate_P.fact4_Gain *
      StudentTemplate_B.Product_hu[3];

    /* Gain: '<S203>/fact5' */
    StudentTemplate_B.fact5 = StudentTemplate_P.fact5_Gain *
      StudentTemplate_B.Product_hu[4];

    /* Gain: '<S203>/taux' */
    StudentTemplate_B.taux = StudentTemplate_P.taux_Gain *
      StudentTemplate_B.tauSwitch[0];

    /* Gain: '<S203>/tauy' */
    StudentTemplate_B.tauy = StudentTemplate_P.tauy_Gain *
      StudentTemplate_B.tauSwitch[1];

    /* Gain: '<S203>/tauyaw' */
    StudentTemplate_B.tauyaw = StudentTemplate_P.tauyaw_Gain *
      StudentTemplate_B.tauSwitch[2];

    /* Gain: '<S203>/omega_qy' */
    StudentTemplate_B.omega_qy = StudentTemplate_P.omega_qy_Gain *
      StudentTemplate_B.Integrator2[1];

    /* Gain: '<S203>/omegaqx' */
    StudentTemplate_B.omegaqx = StudentTemplate_P.omegaqx_Gain *
      StudentTemplate_B.Integrator2[0];

    /* Gain: '<S204>/CSE1_r [deg//s]' */
    StudentTemplate_B.CSE1_rdegs = StudentTemplate_P.CSE1_rdegs_Gain *
      StudentTemplate_B.nuSwitch[2];

    /* Gain: '<S204>/CSE1_u [m//s]' */
    StudentTemplate_B.CSE1_ums = StudentTemplate_P.CSE1_ums_Gain *
      StudentTemplate_B.nuSwitch[0];

    /* Gain: '<S204>/CSE1_v [m//s]' */
    StudentTemplate_B.CSE1_vms = StudentTemplate_P.CSE1_vms_Gain *
      StudentTemplate_B.nuSwitch[1];

    /* Gain: '<S204>/QS Error' */
    StudentTemplate_B.QSError = StudentTemplate_P.QSError_Gain *
      StudentTemplate_B.QTMIn2Error;

    /* Gain: '<S204>/QS Frame' */
    StudentTemplate_B.QSFrame = StudentTemplate_P.QSFrame_Gain *
      StudentTemplate_B.QTMIn1FN;

    /* Sum: '<S205>/Sum' */
    StudentTemplate_B.Sum_f[0] = StudentTemplate_B.etaSwitch[0] -
      StudentTemplate_B.Switch2;
    StudentTemplate_B.Sum_f[1] = StudentTemplate_B.etaSwitch[1] -
      StudentTemplate_B.Switch2_j;
    StudentTemplate_B.Sum_f[2] = StudentTemplate_B.etaSwitch[2] -
      StudentTemplate_B.Sum_b;

    /* Sum: '<S205>/Sum1' */
    StudentTemplate_B.Sum1_hm[0] = StudentTemplate_B.VectorConcatenate[0] -
      StudentTemplate_B.Switch2;
    StudentTemplate_B.Sum1_hm[1] = StudentTemplate_B.VectorConcatenate[1] -
      StudentTemplate_B.Switch2_j;
    StudentTemplate_B.Sum1_hm[2] = StudentTemplate_B.VectorConcatenate[2] -
      StudentTemplate_B.Sum_b;

    /* Gain: '<S203>/tau1' */
    StudentTemplate_B.tau1[0] = StudentTemplate_P.tau1_Gain *
      StudentTemplate_B.Gain_a[0];

    /* Gain: '<S203>/tau2' */
    StudentTemplate_B.tau2[0] = StudentTemplate_P.tau2_Gain *
      StudentTemplate_B.Gain1_j[0];

    /* Gain: '<S203>/tau3' */
    StudentTemplate_B.tau3[0] = StudentTemplate_P.tau3_Gain *
      StudentTemplate_B.Product2_g[0];

    /* Gain: '<S203>/tau4' */
    StudentTemplate_B.tau4[0] = StudentTemplate_P.tau4_Gain *
      StudentTemplate_B.Product4_p[0];

    /* Gain: '<S203>/tau5' */
    StudentTemplate_B.tau5[0] = StudentTemplate_P.tau5_Gain *
      StudentTemplate_B.Product5[0];

    /* Gain: '<S203>/tau6' */
    StudentTemplate_B.tau6[0] = StudentTemplate_P.tau6_Gain *
      StudentTemplate_B.Product6[0];

    /* Sum: '<S205>/Sum2' */
    StudentTemplate_B.Sum2_j[0] = StudentTemplate_B.VectorConcatenate[0] -
      StudentTemplate_B.etaSwitch[0];

    /* Gain: '<S203>/tau1' */
    StudentTemplate_B.tau1[1] = StudentTemplate_P.tau1_Gain *
      StudentTemplate_B.Gain_a[1];

    /* Gain: '<S203>/tau2' */
    StudentTemplate_B.tau2[1] = StudentTemplate_P.tau2_Gain *
      StudentTemplate_B.Gain1_j[1];

    /* Gain: '<S203>/tau3' */
    StudentTemplate_B.tau3[1] = StudentTemplate_P.tau3_Gain *
      StudentTemplate_B.Product2_g[1];

    /* Gain: '<S203>/tau4' */
    StudentTemplate_B.tau4[1] = StudentTemplate_P.tau4_Gain *
      StudentTemplate_B.Product4_p[1];

    /* Gain: '<S203>/tau5' */
    StudentTemplate_B.tau5[1] = StudentTemplate_P.tau5_Gain *
      StudentTemplate_B.Product5[1];

    /* Gain: '<S203>/tau6' */
    StudentTemplate_B.tau6[1] = StudentTemplate_P.tau6_Gain *
      StudentTemplate_B.Product6[1];

    /* Sum: '<S205>/Sum2' */
    StudentTemplate_B.Sum2_j[1] = StudentTemplate_B.VectorConcatenate[1] -
      StudentTemplate_B.etaSwitch[1];

    /* Gain: '<S203>/tau1' */
    StudentTemplate_B.tau1[2] = StudentTemplate_P.tau1_Gain *
      StudentTemplate_B.Gain_a[2];

    /* Gain: '<S203>/tau2' */
    StudentTemplate_B.tau2[2] = StudentTemplate_P.tau2_Gain *
      StudentTemplate_B.Gain1_j[2];

    /* Gain: '<S203>/tau3' */
    StudentTemplate_B.tau3[2] = StudentTemplate_P.tau3_Gain *
      StudentTemplate_B.Product2_g[2];

    /* Gain: '<S203>/tau4' */
    StudentTemplate_B.tau4[2] = StudentTemplate_P.tau4_Gain *
      StudentTemplate_B.Product4_p[2];

    /* Gain: '<S203>/tau5' */
    StudentTemplate_B.tau5[2] = StudentTemplate_P.tau5_Gain *
      StudentTemplate_B.Product5[2];

    /* Gain: '<S203>/tau6' */
    StudentTemplate_B.tau6[2] = StudentTemplate_P.tau6_Gain *
      StudentTemplate_B.Product6[2];

    /* Sum: '<S205>/Sum2' */
    StudentTemplate_B.Sum2_j[2] = StudentTemplate_B.VectorConcatenate[2] -
      StudentTemplate_B.etaSwitch[2];

    /* Gain: '<S205>/psi [deg]' */
    StudentTemplate_B.psideg = StudentTemplate_P.psideg_Gain *
      StudentTemplate_B.etaSwitch[2];

    /* Gain: '<S205>/psi-psid [deg]' */
    StudentTemplate_B.psipsiddeg = StudentTemplate_P.psipsiddeg_Gain *
      StudentTemplate_B.Sum_f[2];

    /* Gain: '<S205>/psiLOS-psi [deg]' */
    StudentTemplate_B.psiLOSpsideg = StudentTemplate_P.psiLOSpsideg_Gain *
      StudentTemplate_B.Sum2_j[2];

    /* Gain: '<S205>/psiLOS-psid [deg]' */
    StudentTemplate_B.psiLOSpsiddeg = StudentTemplate_P.psiLOSpsiddeg_Gain *
      StudentTemplate_B.Sum1_hm[2];

    /* Gain: '<S205>/psi_LOS [deg]' */
    StudentTemplate_B.psi_LOSdeg = StudentTemplate_P.psi_LOSdeg_Gain *
      StudentTemplate_B.VectorConcatenate[2];

    /* Gain: '<S205>/psid [deg]' */
    StudentTemplate_B.psiddeg = StudentTemplate_P.psiddeg_Gain *
      StudentTemplate_B.Sum_b;

    /* Gain: '<S205>/psi_plot' */
    StudentTemplate_B.psi_plot[0] = StudentTemplate_P.psi_plot_Gain *
      StudentTemplate_B.psideg;
    StudentTemplate_B.psi_plot[1] = StudentTemplate_P.psi_plot_Gain *
      StudentTemplate_B.psi_LOSdeg;
    StudentTemplate_B.psi_plot[2] = StudentTemplate_P.psi_plot_Gain *
      StudentTemplate_B.psiddeg;

    /* Gain: '<S205>/qx [m]' */
    StudentTemplate_B.qxm = StudentTemplate_P.qxm_Gain *
      StudentTemplate_B.VectorConcatenate[0];

    /* Gain: '<S205>/qx-x [m]' */
    StudentTemplate_B.qxxm = StudentTemplate_P.qxxm_Gain *
      StudentTemplate_B.Sum2_j[0];

    /* Gain: '<S205>/qx-xd [m]1' */
    StudentTemplate_B.qxxdm1 = StudentTemplate_P.qxxdm1_Gain *
      StudentTemplate_B.Sum1_hm[0];

    /* Gain: '<S205>/qy [m]' */
    StudentTemplate_B.qym = StudentTemplate_P.qym_Gain *
      StudentTemplate_B.VectorConcatenate[1];

    /* Gain: '<S205>/qy-y [m]' */
    StudentTemplate_B.qyym = StudentTemplate_P.qyym_Gain *
      StudentTemplate_B.Sum2_j[1];

    /* Gain: '<S205>/qy-yd [m]1' */
    StudentTemplate_B.qyydm1 = StudentTemplate_P.qyydm1_Gain *
      StudentTemplate_B.Sum1_hm[1];

    /* Gain: '<S205>/x [m]' */
    StudentTemplate_B.xm = StudentTemplate_P.xm_Gain *
      StudentTemplate_B.etaSwitch[0];

    /* Gain: '<S205>/x-xd [m]' */
    StudentTemplate_B.xxdm = StudentTemplate_P.xxdm_Gain *
      StudentTemplate_B.Sum_f[0];

    /* Gain: '<S205>/xd [m]' */
    StudentTemplate_B.xdm = StudentTemplate_P.xdm_Gain *
      StudentTemplate_B.Switch2;

    /* Gain: '<S205>/x_plot' */
    StudentTemplate_B.x_plot[0] = StudentTemplate_P.x_plot_Gain *
      StudentTemplate_B.xm;
    StudentTemplate_B.x_plot[1] = StudentTemplate_P.x_plot_Gain *
      StudentTemplate_B.qxm;
    StudentTemplate_B.x_plot[2] = StudentTemplate_P.x_plot_Gain *
      StudentTemplate_B.xdm;

    /* Gain: '<S205>/y [m]' */
    StudentTemplate_B.ym = StudentTemplate_P.ym_Gain *
      StudentTemplate_B.etaSwitch[1];

    /* Gain: '<S205>/y-yd [m]' */
    StudentTemplate_B.yydm = StudentTemplate_P.yydm_Gain *
      StudentTemplate_B.Sum_f[1];

    /* Gain: '<S205>/yd [m]' */
    StudentTemplate_B.ydm = StudentTemplate_P.ydm_Gain *
      StudentTemplate_B.Switch2_j;

    /* Gain: '<S205>/y_plot' */
    StudentTemplate_B.y_plot[0] = StudentTemplate_P.y_plot_Gain *
      StudentTemplate_B.ym;
    StudentTemplate_B.y_plot[1] = StudentTemplate_P.y_plot_Gain *
      StudentTemplate_B.qym;
    StudentTemplate_B.y_plot[2] = StudentTemplate_P.y_plot_Gain *
      StudentTemplate_B.ydm;

    /* Gain: '<S205>/splot' */
    StudentTemplate_B.splot = StudentTemplate_P.splot_Gain *
      StudentTemplate_B.Integrator1;
    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void StudentTemplate_update(int_T tid)
{
  {
    int32_T tmp;

    /* Update for enable SubSystem: '<S25>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S192>/Enable'
     */
    if (StudentTemplate_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S200>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        StudentTemplate_B.Product1_ku[tmp] = 0.0;
        StudentTemplate_B.Product1_ku[tmp] =
          StudentTemplate_B.LinearDampningmatrix[tmp] *
          StudentTemplate_B.Integrator_p[0] + StudentTemplate_B.Product1_ku[tmp];
        StudentTemplate_B.Product1_ku[tmp] =
          StudentTemplate_B.LinearDampningmatrix[tmp + 3] *
          StudentTemplate_B.Integrator_p[1] + StudentTemplate_B.Product1_ku[tmp];
        StudentTemplate_B.Product1_ku[tmp] =
          StudentTemplate_B.LinearDampningmatrix[tmp + 6] *
          StudentTemplate_B.Integrator_p[2] + StudentTemplate_B.Product1_ku[tmp];
      }

      /* Sum: '<S200>/Sum' */
      StudentTemplate_B.Sum_jz[0] = StudentTemplate_B.planttau_surge -
        StudentTemplate_B.Product1_ku[0];
      StudentTemplate_B.Sum_jz[1] = StudentTemplate_B.planttau_sway -
        StudentTemplate_B.Product1_ku[1];
      StudentTemplate_B.Sum_jz[2] = StudentTemplate_B.planttau_yaw -
        StudentTemplate_B.Product1_ku[2];
      for (tmp = 0; tmp < 3; tmp++) {
        /* Product: '<S200>/Product2' */
        StudentTemplate_B.Product2_fu[tmp] = 0.0;
        StudentTemplate_B.Product2_fu[tmp] = StudentTemplate_B.Inverse_c[tmp] *
          StudentTemplate_B.Sum_jz[0] + StudentTemplate_B.Product2_fu[tmp];
        StudentTemplate_B.Product2_fu[tmp] = StudentTemplate_B.Inverse_c[tmp + 3]
          * StudentTemplate_B.Sum_jz[1] + StudentTemplate_B.Product2_fu[tmp];
        StudentTemplate_B.Product2_fu[tmp] = StudentTemplate_B.Inverse_c[tmp + 6]
          * StudentTemplate_B.Sum_jz[2] + StudentTemplate_B.Product2_fu[tmp];

        /* Product: '<S200>/Product3' */
        StudentTemplate_B.Product3_l[tmp] = 0.0;
        StudentTemplate_B.Product3_l[tmp] = StudentTemplate_B.Rpsi_h[tmp] *
          StudentTemplate_B.Integrator_p[0] + StudentTemplate_B.Product3_l[tmp];
        StudentTemplate_B.Product3_l[tmp] = StudentTemplate_B.Rpsi_h[tmp + 3] *
          StudentTemplate_B.Integrator_p[1] + StudentTemplate_B.Product3_l[tmp];
        StudentTemplate_B.Product3_l[tmp] = StudentTemplate_B.Rpsi_h[tmp + 6] *
          StudentTemplate_B.Integrator_p[2] + StudentTemplate_B.Product3_l[tmp];
      }
    }

    /* end of Update for SubSystem: '<S25>/Linear Simulator' */

    /* Derivative Block: '<S96>/Derivative' */
    {
      real_T timeStampA = StudentTemplate_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = StudentTemplate_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank = &StudentTemplate_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 2;
        } else if (timeStampA >= timeStampB) {
          lastBank += 2;
        }
      }

      *lastBank++ = StudentTemplate_M->Timing.t[0];
      *lastBank++ = StudentTemplate_P.u_dm_Value;
    }

    /* Derivative Block: '<S166>/Derivative' */
    {
      real_T timeStampA = StudentTemplate_DWork.Derivative_RWORK_d.TimeStampA;
      real_T timeStampB = StudentTemplate_DWork.Derivative_RWORK_d.TimeStampB;
      real_T *lastBank = &StudentTemplate_DWork.Derivative_RWORK_d.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = StudentTemplate_M->Timing.t[0];
      *lastBank++ = StudentTemplate_B.mm2mx;
      *lastBank++ = StudentTemplate_B.mm2my;
      *lastBank++ = StudentTemplate_B.mm2mz;
      *lastBank++ = StudentTemplate_B.d2rroll;
      *lastBank++ = StudentTemplate_B.d2rpitch;
      *lastBank++ = StudentTemplate_B.d2ryaw;
    }

    if (rtmIsMajorTimeStep(StudentTemplate_M)) {
    }
  }

  if (rtmIsMajorTimeStep(StudentTemplate_M)) {
    rt_ertODEUpdateContinuousStates(&StudentTemplate_M->solverInfo);
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
  if (!(++StudentTemplate_M->Timing.clockTick0))
    ++StudentTemplate_M->Timing.clockTickH0;
  StudentTemplate_M->Timing.t[0] = StudentTemplate_M->Timing.clockTick0 *
    StudentTemplate_M->Timing.stepSize0 + StudentTemplate_M->Timing.clockTickH0 *
    StudentTemplate_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(StudentTemplate_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++StudentTemplate_M->Timing.clockTick1))
      ++StudentTemplate_M->Timing.clockTickH1;
    StudentTemplate_M->Timing.t[1] = StudentTemplate_M->Timing.clockTick1 *
      StudentTemplate_M->Timing.stepSize1 +
      StudentTemplate_M->Timing.clockTickH1 *
      StudentTemplate_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void StudentTemplate_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S25>/Linear Simulator' */
    if (StudentTemplate_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S200>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        StudentTemplate_B.Product1_ku[tmp] = 0.0;
        StudentTemplate_B.Product1_ku[tmp] =
          StudentTemplate_B.LinearDampningmatrix[tmp] *
          StudentTemplate_B.Integrator_p[0] + StudentTemplate_B.Product1_ku[tmp];
        StudentTemplate_B.Product1_ku[tmp] =
          StudentTemplate_B.LinearDampningmatrix[tmp + 3] *
          StudentTemplate_B.Integrator_p[1] + StudentTemplate_B.Product1_ku[tmp];
        StudentTemplate_B.Product1_ku[tmp] =
          StudentTemplate_B.LinearDampningmatrix[tmp + 6] *
          StudentTemplate_B.Integrator_p[2] + StudentTemplate_B.Product1_ku[tmp];
      }

      /* Sum: '<S200>/Sum' */
      StudentTemplate_B.Sum_jz[0] = StudentTemplate_B.planttau_surge -
        StudentTemplate_B.Product1_ku[0];
      StudentTemplate_B.Sum_jz[1] = StudentTemplate_B.planttau_sway -
        StudentTemplate_B.Product1_ku[1];
      StudentTemplate_B.Sum_jz[2] = StudentTemplate_B.planttau_yaw -
        StudentTemplate_B.Product1_ku[2];
      for (tmp = 0; tmp < 3; tmp++) {
        /* Product: '<S200>/Product2' */
        StudentTemplate_B.Product2_fu[tmp] = 0.0;
        StudentTemplate_B.Product2_fu[tmp] = StudentTemplate_B.Inverse_c[tmp] *
          StudentTemplate_B.Sum_jz[0] + StudentTemplate_B.Product2_fu[tmp];
        StudentTemplate_B.Product2_fu[tmp] = StudentTemplate_B.Inverse_c[tmp + 3]
          * StudentTemplate_B.Sum_jz[1] + StudentTemplate_B.Product2_fu[tmp];
        StudentTemplate_B.Product2_fu[tmp] = StudentTemplate_B.Inverse_c[tmp + 6]
          * StudentTemplate_B.Sum_jz[2] + StudentTemplate_B.Product2_fu[tmp];

        /* Product: '<S200>/Product3' */
        StudentTemplate_B.Product3_l[tmp] = 0.0;
        StudentTemplate_B.Product3_l[tmp] = StudentTemplate_B.Rpsi_h[tmp] *
          StudentTemplate_B.Integrator_p[0] + StudentTemplate_B.Product3_l[tmp];
        StudentTemplate_B.Product3_l[tmp] = StudentTemplate_B.Rpsi_h[tmp + 3] *
          StudentTemplate_B.Integrator_p[1] + StudentTemplate_B.Product3_l[tmp];
        StudentTemplate_B.Product3_l[tmp] = StudentTemplate_B.Rpsi_h[tmp + 6] *
          StudentTemplate_B.Integrator_p[2] + StudentTemplate_B.Product3_l[tmp];
      }

      /* Integrator Block: '<S200>/Integrator' */
      {
        if (StudentTemplate_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator_CSTATE_en[0] =
            StudentTemplate_B.Product2_fu[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator_CSTATE_en[0] = 0.0;
        }

        if (StudentTemplate_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator_CSTATE_en[1] =
            StudentTemplate_B.Product2_fu[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator_CSTATE_en[1] = 0.0;
        }

        if (StudentTemplate_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator_CSTATE_en[2] =
            StudentTemplate_B.Product2_fu[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator_CSTATE_en[2] = 0.0;
        }
      }

      /* Integrator Block: '<S200>/Integrator1' */
      {
        if (StudentTemplate_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator1_CSTATE_l[0] =
            StudentTemplate_B.Product3_l[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator1_CSTATE_l[0] = 0.0;
        }

        if (StudentTemplate_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator1_CSTATE_l[1] =
            StudentTemplate_B.Product3_l[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator1_CSTATE_l[1] = 0.0;
        }

        if (StudentTemplate_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator1_CSTATE_l[2] =
            StudentTemplate_B.Product3_l[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_StudentTemplat *)
            StudentTemplate_M->ModelData.derivs)->Integrator1_CSTATE_l[2] = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_StudentTemplat *)
                StudentTemplate_M->ModelData.derivs)->Integrator_CSTATE_en[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S25>/Linear Simulator' */

    /* Integrator Block: '<S30>/Integrator' */
    {
      if (StudentTemplate_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE[0] =
          StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = 0.0;
      }

      if (StudentTemplate_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE[1] =
          StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = 0.0;
      }

      if (StudentTemplate_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE[2] =
          StudentTemplate_B.TmpHiddenBufferAtProductInpor_d[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE[2] = 0.0;
      }
    }

    /* Integrator Block: '<S169>/Integrator4' */
    {
      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator4_CSTATE[0] = StudentTemplate_B.Product_ay[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator4_CSTATE[0] = 0.0;
      }

      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator4_CSTATE[1] = StudentTemplate_B.Product_ay[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator4_CSTATE[1] = 0.0;
      }

      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator4_CSTATE[2] = StudentTemplate_B.Product_ay[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator4_CSTATE[2] = 0.0;
      }
    }

    /* Integrator Block: '<S50>/Integrator' */
    {
      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_c[0] = StudentTemplate_B.Product_ar[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_c[0] = 0.0;
      }

      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_c[1] = StudentTemplate_B.Product_ar[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_c[1] = 0.0;
      }

      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_c[2] = StudentTemplate_B.Product_ar[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_c[2] = 0.0;
      }
    }

    /* Integrator Block: '<S42>/Integrator' */
    {
      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_j[0] = StudentTemplate_B.Add_gg[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_j[0] = 0.0;
      }

      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_j[1] = StudentTemplate_B.Add_gg[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_j[1] = 0.0;
      }
    }

    /* Integrator Block: '<S42>/Integrator1' */
    {
      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator1_CSTATE = StudentTemplate_B.Subtract_f;
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator1_CSTATE = 0.0;
      }
    }

    /* Integrator Block: '<S42>/Integrator2' */
    {
      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = StudentTemplate_B.Gain_mv[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = 0.0;
      }

      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = StudentTemplate_B.Gain_mv[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = 0.0;
      }
    }

    /* Integrator Block: '<S169>/Integrator' */
    {
      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_e[0] = StudentTemplate_B.Sum3_h[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_e[0] = 0.0;
      }

      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_e[1] = StudentTemplate_B.Sum3_h[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_e[1] = 0.0;
      }

      if (StudentTemplate_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_e[2] = StudentTemplate_B.Sum3_h[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
          ->Integrator_CSTATE_e[2] = 0.0;
      }
    }

    /* Derivatives for Integrator: '<S169>/Integrator3' */
    ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
      ->Integrator3_CSTATE[0] = StudentTemplate_B.Sum7[0];
    ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
      ->Integrator3_CSTATE[1] = StudentTemplate_B.Sum7[1];
    ((StateDerivatives_StudentTemplat *) StudentTemplate_M->ModelData.derivs)
      ->Integrator3_CSTATE[2] = StudentTemplate_B.Sum7[2];
  }
}

/* Model initialize function */
void StudentTemplate_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)StudentTemplate_M,0,
                sizeof(RT_MODEL_StudentTemplate));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&StudentTemplate_M->solverInfo,
                          &StudentTemplate_M->Timing.simTimeStep);
    rtsiSetTPtr(&StudentTemplate_M->solverInfo, &rtmGetTPtr(StudentTemplate_M));
    rtsiSetStepSizePtr(&StudentTemplate_M->solverInfo,
                       &StudentTemplate_M->Timing.stepSize0);
    rtsiSetdXPtr(&StudentTemplate_M->solverInfo,
                 &StudentTemplate_M->ModelData.derivs);
    rtsiSetContStatesPtr(&StudentTemplate_M->solverInfo,
                         &StudentTemplate_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&StudentTemplate_M->solverInfo,
      &StudentTemplate_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&StudentTemplate_M->solverInfo, (&rtmGetErrorStatus
      (StudentTemplate_M)));
    rtsiSetRTModelPtr(&StudentTemplate_M->solverInfo, StudentTemplate_M);
  }

  rtsiSetSimTimeStep(&StudentTemplate_M->solverInfo, MAJOR_TIME_STEP);
  StudentTemplate_M->ModelData.intgData.y = StudentTemplate_M->ModelData.odeY;
  StudentTemplate_M->ModelData.intgData.f[0] = StudentTemplate_M->
    ModelData.odeF[0];
  StudentTemplate_M->ModelData.intgData.f[1] = StudentTemplate_M->
    ModelData.odeF[1];
  StudentTemplate_M->ModelData.intgData.f[2] = StudentTemplate_M->
    ModelData.odeF[2];
  StudentTemplate_M->ModelData.intgData.f[3] = StudentTemplate_M->
    ModelData.odeF[3];
  StudentTemplate_M->ModelData.intgData.f[4] = StudentTemplate_M->
    ModelData.odeF[4];
  StudentTemplate_M->ModelData.intgData.f[5] = StudentTemplate_M->
    ModelData.odeF[5];
  StudentTemplate_M->ModelData.contStates = ((real_T *) &StudentTemplate_X);
  rtsiSetSolverData(&StudentTemplate_M->solverInfo, (void *)
                    &StudentTemplate_M->ModelData.intgData);
  rtsiSetSolverName(&StudentTemplate_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = StudentTemplate_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    StudentTemplate_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    StudentTemplate_M->Timing.sampleTimes =
      (&StudentTemplate_M->Timing.sampleTimesArray[0]);
    StudentTemplate_M->Timing.offsetTimes =
      (&StudentTemplate_M->Timing.offsetTimesArray[0]);

    /* task periods */
    StudentTemplate_M->Timing.sampleTimes[0] = (0.0);
    StudentTemplate_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    StudentTemplate_M->Timing.offsetTimes[0] = (0.0);
    StudentTemplate_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(StudentTemplate_M, &StudentTemplate_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = StudentTemplate_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    StudentTemplate_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(StudentTemplate_M, -1);
  StudentTemplate_M->Timing.stepSize0 = 0.1;
  StudentTemplate_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(StudentTemplate_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    StudentTemplate_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(StudentTemplate_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(StudentTemplate_M->rtwLogInfo, (NULL));
    rtliSetLogT(StudentTemplate_M->rtwLogInfo, "");
    rtliSetLogX(StudentTemplate_M->rtwLogInfo, "");
    rtliSetLogXFinal(StudentTemplate_M->rtwLogInfo, "");
    rtliSetSigLog(StudentTemplate_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(StudentTemplate_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(StudentTemplate_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(StudentTemplate_M->rtwLogInfo, 0);
    rtliSetLogDecimation(StudentTemplate_M->rtwLogInfo, 1);
    rtliSetLogY(StudentTemplate_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(StudentTemplate_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(StudentTemplate_M->rtwLogInfo, (NULL));
  }

  StudentTemplate_M->solverInfoPtr = (&StudentTemplate_M->solverInfo);
  StudentTemplate_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&StudentTemplate_M->solverInfo, 0.1);
  rtsiSetSolverMode(&StudentTemplate_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  StudentTemplate_M->ModelData.blockIO = ((void *) &StudentTemplate_B);
  (void) memset(((void *) &StudentTemplate_B),0,
                sizeof(BlockIO_StudentTemplate));

  /* parameters */
  StudentTemplate_M->ModelData.defaultParam = ((real_T *) &StudentTemplate_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &StudentTemplate_X;
    StudentTemplate_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_StudentTemplat));
  }

  /* states (dwork) */
  StudentTemplate_M->Work.dwork = ((void *) &StudentTemplate_DWork);
  (void) memset((void *)&StudentTemplate_DWork, 0,
                sizeof(D_Work_StudentTemplate));
  StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  StudentTemplate_PrevZCSigState.Integrator4_Reset_ZCE = UNINITIALIZED_ZCSIG;
  StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE_c = UNINITIALIZED_ZCSIG;
  StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE_p = UNINITIALIZED_ZCSIG;
  StudentTemplate_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  StudentTemplate_PrevZCSigState.Integrator2_Reset_ZCE = UNINITIALIZED_ZCSIG;
  StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE_l = UNINITIALIZED_ZCSIG;
  StudentTemplate_PrevZCSigState.Integrator_Reset_ZCE_j = UNINITIALIZED_ZCSIG;
  StudentTemplate_PrevZCSigState.Integrator1_Reset_ZCE_e = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void StudentTemplate_terminate(void)
{
  /* ToFile Block: '<S22>/To File' */
  {
    FILE *fp = (FILE *) StudentTemplate_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "Student_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(StudentTemplate_M,
                          "Error closing MAT-file Student_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(StudentTemplate_M,
                          "Error reopening MAT-file Student_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 87,
           StudentTemplate_DWork.ToFile_IWORK.Count, "Student_data")) {
        rtmSetErrorStatus(StudentTemplate_M,
                          "Error writing header for Student_data to MAT-file Student_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(StudentTemplate_M,
                          "Error closing MAT-file Student_data.mat");
        return;
      }

      StudentTemplate_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  StudentTemplate_output(tid);
}

void MdlUpdate(int_T tid)
{
  StudentTemplate_update(tid);
}

void MdlInitializeSizes(void)
{
  StudentTemplate_M->Sizes.numContStates = (26);/* Number of continuous states */
  StudentTemplate_M->Sizes.numY = (0); /* Number of model outputs */
  StudentTemplate_M->Sizes.numU = (0); /* Number of model inputs */
  StudentTemplate_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  StudentTemplate_M->Sizes.numSampTimes = (2);/* Number of sample times */
  StudentTemplate_M->Sizes.numBlocks = (979);/* Number of blocks */
  StudentTemplate_M->Sizes.numBlockIO = (714);/* Number of block outputs */
  StudentTemplate_M->Sizes.numBlockPrms = (1419);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Integrator Block: '<S30>/Integrator' */
  StudentTemplate_X.Integrator_CSTATE[0] = StudentTemplate_P.Integrator_IC;
  StudentTemplate_X.Integrator_CSTATE[1] = StudentTemplate_P.Integrator_IC;
  StudentTemplate_X.Integrator_CSTATE[2] = StudentTemplate_P.Integrator_IC;

  /* Integrator Block: '<S169>/Integrator4' */
  StudentTemplate_X.Integrator4_CSTATE[0] = StudentTemplate_P.Integrator4_IC;
  StudentTemplate_X.Integrator4_CSTATE[1] = StudentTemplate_P.Integrator4_IC;
  StudentTemplate_X.Integrator4_CSTATE[2] = StudentTemplate_P.Integrator4_IC;

  /* Integrator Block: '<S50>/Integrator' */
  StudentTemplate_X.Integrator_CSTATE_c[0] = StudentTemplate_P.Integrator_IC_f[0];
  StudentTemplate_X.Integrator_CSTATE_c[1] = StudentTemplate_P.Integrator_IC_f[1];
  StudentTemplate_X.Integrator_CSTATE_c[2] = StudentTemplate_P.Integrator_IC_f[2];

  /* Integrator Block: '<S42>/Integrator' */
  if (rtmIsFirstInitCond(StudentTemplate_M)) {
    StudentTemplate_X.Integrator_CSTATE_j[0] = 0.0;
    StudentTemplate_X.Integrator_CSTATE_j[1] = 0.0;
  }

  StudentTemplate_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S42>/Integrator1' */
  if (rtmIsFirstInitCond(StudentTemplate_M)) {
    StudentTemplate_X.Integrator1_CSTATE = 0.0;
  }

  StudentTemplate_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* Derivative Block: '<S96>/Derivative' */
  StudentTemplate_DWork.Derivative_RWORK.TimeStampA = rtInf;
  StudentTemplate_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* Integrator Block: '<S42>/Integrator2' */
  StudentTemplate_X.Integrator2_CSTATE[0] = StudentTemplate_P.Integrator2_IC;
  StudentTemplate_X.Integrator2_CSTATE[1] = StudentTemplate_P.Integrator2_IC;

  /* Derivative Block: '<S166>/Derivative' */
  StudentTemplate_DWork.Derivative_RWORK_d.TimeStampA = rtInf;
  StudentTemplate_DWork.Derivative_RWORK_d.TimeStampB = rtInf;

  /* Integrator Block: '<S169>/Integrator' */
  if (rtmIsFirstInitCond(StudentTemplate_M)) {
    StudentTemplate_X.Integrator_CSTATE_e[0] = 0.0;
    StudentTemplate_X.Integrator_CSTATE_e[1] = 0.0;
    StudentTemplate_X.Integrator_CSTATE_e[2] = 0.0;
  }

  StudentTemplate_DWork.Integrator_IWORK_j.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<S169>/Integrator3' */
  StudentTemplate_X.Integrator3_CSTATE[0] = StudentTemplate_P.Integrator3_IC;
  StudentTemplate_X.Integrator3_CSTATE[1] = StudentTemplate_P.Integrator3_IC;
  StudentTemplate_X.Integrator3_CSTATE[2] = StudentTemplate_P.Integrator3_IC;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(StudentTemplate_M)) {
    rtmSetFirstInitCond(StudentTemplate_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for Constant: '<S4>/Initial psi [rad]' */
  StudentTemplate_B.Initialpsirad = StudentTemplate_P.Initialpsirad_Value;

  /* Start for Constant: '<S4>/Initial x [m]' */
  StudentTemplate_B.Initialxm = StudentTemplate_P.Initialxm_Value;

  /* Start for Constant: '<S4>/Initial y [m]' */
  StudentTemplate_B.Initialym = StudentTemplate_P.Initialym_Value;

  /* Start for Constant: '<S4>/Initial r [rad//s]' */
  StudentTemplate_B.Initialrrads = StudentTemplate_P.Initialrrads_Value;

  /* Start for Constant: '<S4>/Initial u [m//s]' */
  StudentTemplate_B.Initialums = StudentTemplate_P.Initialums_Value;

  /* Start for Constant: '<S4>/Initial v [m//s]' */
  StudentTemplate_B.Initialvms = StudentTemplate_P.Initialvms_Value;

  /* Start for Constant: '<S9>/Initial q_x' */
  StudentTemplate_B.Initialq_x = StudentTemplate_P.Initialq_x_Value;

  /* Start for Constant: '<S9>/Initial q_y' */
  StudentTemplate_B.Initialq_y = StudentTemplate_P.Initialq_y_Value;

  /* Start for Constant: '<S9>/Initial s' */
  StudentTemplate_B.Initials = StudentTemplate_P.Initials_Value;

  /* Start for enable SubSystem: '<S25>/Linear Simulator' */
  StudentTemplate_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Integrator Block: '<S200>/Integrator' */
  if (rtmIsFirstInitCond(StudentTemplate_M)) {
    StudentTemplate_X.Integrator_CSTATE_en[0] = 0.0;
    StudentTemplate_X.Integrator_CSTATE_en[1] = 0.0;
    StudentTemplate_X.Integrator_CSTATE_en[2] = 0.0;
  }

  StudentTemplate_DWork.Integrator_IWORK_jt.IcNeedsLoading = 1;

  /* Integrator Block: '<S200>/Integrator1' */
  if (rtmIsFirstInitCond(StudentTemplate_M)) {
    StudentTemplate_X.Integrator1_CSTATE_l[0] = 0.0;
    StudentTemplate_X.Integrator1_CSTATE_l[1] = 0.0;
    StudentTemplate_X.Integrator1_CSTATE_l[2] = 0.0;
  }

  StudentTemplate_DWork.Integrator1_IWORK_h.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S25>/Linear Simulator' */

  /* ToFile Block: '<S22>/To File' */
  {
    const char *fileName = "Student_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(StudentTemplate_M,
                        "Error creating .mat file Student_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,87,0,"Student_data")) {
      rtmSetErrorStatus(StudentTemplate_M,
                        "Error writing mat file header to file Student_data.mat");
      return;
    }

    StudentTemplate_DWork.ToFile_IWORK.Count = 0;
    StudentTemplate_DWork.ToFile_IWORK.Decimation = -1;
    StudentTemplate_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* Create Identity Matrix for Block: '<S166>/Inverse' */
  {
    int_T i;
    real_T *dWork = &StudentTemplate_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &StudentTemplate_DWork.Inverse_DWORK4[0];
    while (dWork < &StudentTemplate_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  /* Start for enable SubSystem: '<S25>/CSE1 actuator' */
  StudentTemplate_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S25>/CSE1 actuator' */

  /* Create Identity Matrix for Block: '<S25>/Inverse' */
  {
    int_T i;
    real_T *dWork = &StudentTemplate_DWork.Inverse_DWORK4_f[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &StudentTemplate_DWork.Inverse_DWORK4_f[0];
    while (dWork < &StudentTemplate_DWork.Inverse_DWORK4_f[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  MdlInitialize();
}

RT_MODEL_StudentTemplate *StudentTemplate(void)
{
  StudentTemplate_initialize(1);
  return StudentTemplate_M;
}

void MdlTerminate(void)
{
  StudentTemplate_terminate();
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
#ifdef NI_ROOTMODEL_StudentTemplate
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 48:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 49:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 54:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 55:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 56:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 64:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 65:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 48:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 49:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 54:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 55:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 56:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 64:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 65:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

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

extern StudentTemplate_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Main Subsystems/Naviagation/Input from SIT/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(StudentTemplate_B.QTMIn, count, data[index++], 50,
        0);
    }
  } else {
    index += 9;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&StudentTemplate_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&StudentTemplate_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&StudentTemplate_B.SITzAI2, 0, data[index++], 0, 0);
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
    ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Switch2_o,0,
      0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.VSPSPort,0,0,
      0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&StudentTemplate_B.VSPSStarboard,0,0,0);
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
  ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Switch2_o,0,0,
    0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Servo1,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Servo2,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Servo3,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.Servo4,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.VSPSPort,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&StudentTemplate_B.VSPSStarboard,
    0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "studenttemplate/Inputs from LabVIEW/Control Input Selector/Value",
    offsetof(Parameters_StudentTemplate, ControlInputSelector_Value), 31, 1, 2,
    0, "", 0 },

  { 1, "studenttemplate/Inputs from LabVIEW/Control Mode Selector/Value",
    offsetof(Parameters_StudentTemplate, ControlModeSelector_Value), 31, 1, 2, 2,
    "", 0 },

  { 2, "studenttemplate/Inputs from LabVIEW/Enable CSE1/Value", offsetof
    (Parameters_StudentTemplate, EnableCSE1_Value), 31, 1, 2, 4, "", 0 },

  { 3, "studenttemplate/Inputs from LabVIEW/tauxscale/Value", offsetof
    (Parameters_StudentTemplate, tauxscale_Value), 31, 1, 2, 6, "", 0 },

  { 4, "studenttemplate/Inputs from LabVIEW/tauyscale/Value", offsetof
    (Parameters_StudentTemplate, tauyscale_Value), 31, 1, 2, 8, "", 0 },

  { 5, "studenttemplate/Inputs from LabVIEW/tauyawscale/Value", offsetof
    (Parameters_StudentTemplate, tauyawscale_Value), 31, 1, 2, 10, "", 0 },

  { 6, "studenttemplate/Inputs from LabVIEW/offset u1/Value", offsetof
    (Parameters_StudentTemplate, offsetu1_Value), 31, 1, 2, 12, "", 0 },

  { 7, "studenttemplate/Inputs from LabVIEW/offset u2/Value", offsetof
    (Parameters_StudentTemplate, offsetu2_Value), 31, 1, 2, 14, "", 0 },

  { 8, "studenttemplate/Inputs from LabVIEW/offset u3/Value", offsetof
    (Parameters_StudentTemplate, offsetu3_Value), 31, 1, 2, 16, "", 0 },

  { 9, "studenttemplate/Inputs from LabVIEW/offset u4/Value", offsetof
    (Parameters_StudentTemplate, offsetu4_Value), 31, 1, 2, 18, "", 0 },

  { 10,
    "studenttemplate/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value",
    offsetof(Parameters_StudentTemplate, EnableLinearSimulator_Value), 31, 1, 2,
    20, "", 0 },

  { 11,
    "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value",
    offsetof(Parameters_StudentTemplate, Initialpsirad_Value), 31, 1, 2, 22, "",
    0 },

  { 12,
    "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value",
    offsetof(Parameters_StudentTemplate, Initialxm_Value), 31, 1, 2, 24, "", 0 },

  { 13,
    "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value",
    offsetof(Parameters_StudentTemplate, Initialym_Value), 31, 1, 2, 26, "", 0 },

  { 14,
    "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value",
    offsetof(Parameters_StudentTemplate, Initialrrads_Value), 31, 1, 2, 28, "",
    0 },

  { 15,
    "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value",
    offsetof(Parameters_StudentTemplate, Initialums_Value), 31, 1, 2, 30, "", 0
  },

  { 16,
    "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value",
    offsetof(Parameters_StudentTemplate, Initialvms_Value), 31, 1, 2, 32, "", 0
  },

  { 17,
    "studenttemplate/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_StudentTemplate, ResetLinearSimulatorintegrator_), 31, 1,
    2, 34, "", 0 },

  { 18, "studenttemplate/Inputs from LabVIEW/Path/Delta [m]/Value", offsetof
    (Parameters_StudentTemplate, Deltam_Value), 31, 1, 2, 36, "", 0 },

  { 19, "studenttemplate/Inputs from LabVIEW/Path/Path Selector  [-]/Value",
    offsetof(Parameters_StudentTemplate, PathSelector_Value), 31, 1, 2, 38, "",
    0 },

  { 20, "studenttemplate/Inputs from LabVIEW/Path/my [-]/Value", offsetof
    (Parameters_StudentTemplate, my_Value), 31, 1, 2, 40, "", 0 },

  { 21, "studenttemplate/Inputs from LabVIEW/Path/u_d [m]/Value", offsetof
    (Parameters_StudentTemplate, u_dm_Value), 31, 1, 2, 42, "", 0 },

  { 22, "studenttemplate/Inputs from LabVIEW/Path/x_dmax [m]/Value", offsetof
    (Parameters_StudentTemplate, x_dmaxm_Value), 31, 1, 2, 44, "", 0 },

  { 23, "studenttemplate/Inputs from LabVIEW/Path/x_dmin [m]/Value", offsetof
    (Parameters_StudentTemplate, x_dminm_Value), 31, 1, 2, 46, "", 0 },

  { 24, "studenttemplate/Inputs from LabVIEW/Path/y_dmax [m]/Value", offsetof
    (Parameters_StudentTemplate, y_dmaxm_Value), 31, 1, 2, 48, "", 0 },

  { 25, "studenttemplate/Inputs from LabVIEW/Path/y_dmin [m]/Value", offsetof
    (Parameters_StudentTemplate, y_dminm_Value), 31, 1, 2, 50, "", 0 },

  { 26, "studenttemplate/Inputs from LabVIEW/Path/Ellipse/k [-]/Value", offsetof
    (Parameters_StudentTemplate, k_Value), 31, 1, 2, 52, "", 0 },

  { 27, "studenttemplate/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value",
    offsetof(Parameters_StudentTemplate, r_xm_Value), 31, 1, 2, 54, "", 0 },

  { 28, "studenttemplate/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value",
    offsetof(Parameters_StudentTemplate, r_ym_Value), 31, 1, 2, 56, "", 0 },

  { 29, "studenttemplate/Inputs from LabVIEW/Path/Ellipse/x_0 [m]/Value",
    offsetof(Parameters_StudentTemplate, x_0m_Value), 31, 1, 2, 58, "", 0 },

  { 30, "studenttemplate/Inputs from LabVIEW/Path/Ellipse/y_0 [m]/Value",
    offsetof(Parameters_StudentTemplate, y_0m_Value), 31, 1, 2, 60, "", 0 },

  { 31, "studenttemplate/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value",
    offsetof(Parameters_StudentTemplate, x_1m_Value), 31, 1, 2, 62, "", 0 },

  { 32, "studenttemplate/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value",
    offsetof(Parameters_StudentTemplate, x_2m_Value), 31, 1, 2, 64, "", 0 },

  { 33, "studenttemplate/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value",
    offsetof(Parameters_StudentTemplate, y_1m_Value), 31, 1, 2, 66, "", 0 },

  { 34, "studenttemplate/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value",
    offsetof(Parameters_StudentTemplate, y_2m_Value), 31, 1, 2, 68, "", 0 },

  { 35, "studenttemplate/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value",
    offsetof(Parameters_StudentTemplate, AS_LX_Value), 31, 1, 2, 70, "", 0 },

  { 36, "studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain",
    offsetof(Parameters_StudentTemplate, ScalingLX_Gain), 31, 1, 2, 72, "", 0 },

  { 37, "studenttemplate/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value",
    offsetof(Parameters_StudentTemplate, AS_LY_Value), 31, 1, 2, 74, "", 0 },

  { 38, "studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain",
    offsetof(Parameters_StudentTemplate, ScalingLY_Gain), 31, 1, 2, 76, "", 0 },

  { 39, "studenttemplate/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value",
    offsetof(Parameters_StudentTemplate, AS_RX_Value), 31, 1, 2, 78, "", 0 },

  { 40, "studenttemplate/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain",
    offsetof(Parameters_StudentTemplate, Scaling_RX_Gain), 31, 1, 2, 80, "", 0 },

  { 41, "studenttemplate/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value",
    offsetof(Parameters_StudentTemplate, AS_RY_Value), 31, 1, 2, 82, "", 0 },

  { 42, "studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain",
    offsetof(Parameters_StudentTemplate, ScalingRY_Gain), 31, 1, 2, 84, "", 0 },

  { 43,
    "studenttemplate/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value",
    offsetof(Parameters_StudentTemplate, PS3_BT_Power_Value), 31, 1, 2, 86, "",
    0 },

  { 44, "studenttemplate/Inputs from LabVIEW/PlayStation3/L2 [-]/Value",
    offsetof(Parameters_StudentTemplate, L2_Value), 31, 1, 2, 88, "", 0 },

  { 45,
    "studenttemplate/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value",
    offsetof(Parameters_StudentTemplate, PS3_VSP_Speed_Value), 31, 1, 2, 90, "",
    0 },

  { 46, "studenttemplate/Inputs from LabVIEW/PlayStation3/R2 [-]/Value",
    offsetof(Parameters_StudentTemplate, R2_Value), 31, 1, 2, 92, "", 0 },

  { 47, "studenttemplate/Inputs from LabVIEW/Setpoint/setpointpsi [deg]/Value",
    offsetof(Parameters_StudentTemplate, setpointpsideg_Value), 31, 1, 2, 94, "",
    0 },

  { 48,
    "studenttemplate/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_StudentTemplate, Gain1_Gain), 31, 1, 2, 96, "", 0 },

  { 49, "studenttemplate/Inputs from LabVIEW/Setpoint/setpointx [m]/Value",
    offsetof(Parameters_StudentTemplate, setpointxm_Value), 31, 1, 2, 98, "", 0
  },

  { 50, "studenttemplate/Inputs from LabVIEW/Setpoint/setpointy [m]/Value",
    offsetof(Parameters_StudentTemplate, setpointym_Value), 31, 1, 2, 100, "", 0
  },

  { 51, "studenttemplate/Inputs from LabVIEW/ctrl1/Kd/12/Value", offsetof
    (Parameters_StudentTemplate, u_Value), 31, 1, 2, 102, "", 0 },

  { 52, "studenttemplate/Inputs from LabVIEW/ctrl1/Kd/13/Value", offsetof
    (Parameters_StudentTemplate, u_Value_n), 31, 1, 2, 104, "", 0 },

  { 53, "studenttemplate/Inputs from LabVIEW/ctrl1/Kd/21/Value", offsetof
    (Parameters_StudentTemplate, u_Value_ns), 31, 1, 2, 106, "", 0 },

  { 54, "studenttemplate/Inputs from LabVIEW/ctrl1/Kd/23/Value", offsetof
    (Parameters_StudentTemplate, u_Value_f), 31, 1, 2, 108, "", 0 },

  { 55, "studenttemplate/Inputs from LabVIEW/ctrl1/Kd/31/Value", offsetof
    (Parameters_StudentTemplate, u_Value_p), 31, 1, 2, 110, "", 0 },

  { 56, "studenttemplate/Inputs from LabVIEW/ctrl1/Kd/32/Value", offsetof
    (Parameters_StudentTemplate, u_Value_e), 31, 1, 2, 112, "", 0 },

  { 57, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kdx/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kdx_Value), 31, 1, 2, 114, "", 0 },

  { 58, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kdy/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kdy_Value), 31, 1, 2, 116, "", 0 },

  { 59, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kdpsi/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kdpsi_Value), 31, 1, 2, 118, "", 0 },

  { 60, "studenttemplate/Inputs from LabVIEW/ctrl1/Ki/12/Value", offsetof
    (Parameters_StudentTemplate, u_Value_fm), 31, 1, 2, 120, "", 0 },

  { 61, "studenttemplate/Inputs from LabVIEW/ctrl1/Ki/13/Value", offsetof
    (Parameters_StudentTemplate, u_Value_h), 31, 1, 2, 122, "", 0 },

  { 62, "studenttemplate/Inputs from LabVIEW/ctrl1/Ki/21/Value", offsetof
    (Parameters_StudentTemplate, u_Value_k), 31, 1, 2, 124, "", 0 },

  { 63, "studenttemplate/Inputs from LabVIEW/ctrl1/Ki/23/Value", offsetof
    (Parameters_StudentTemplate, u_Value_fx), 31, 1, 2, 126, "", 0 },

  { 64, "studenttemplate/Inputs from LabVIEW/ctrl1/Ki/31/Value", offsetof
    (Parameters_StudentTemplate, u_Value_hu), 31, 1, 2, 128, "", 0 },

  { 65, "studenttemplate/Inputs from LabVIEW/ctrl1/Ki/32/Value", offsetof
    (Parameters_StudentTemplate, u_Value_a), 31, 1, 2, 130, "", 0 },

  { 66, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kix/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kix_Value), 31, 1, 2, 132, "", 0 },

  { 67, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kiy/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kiy_Value), 31, 1, 2, 134, "", 0 },

  { 68, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kipsi/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kipsi_Value), 31, 1, 2, 136, "", 0 },

  { 69, "studenttemplate/Inputs from LabVIEW/ctrl1/Kp/12/Value", offsetof
    (Parameters_StudentTemplate, u_Value_b), 31, 1, 2, 138, "", 0 },

  { 70, "studenttemplate/Inputs from LabVIEW/ctrl1/Kp/13/Value", offsetof
    (Parameters_StudentTemplate, u_Value_np), 31, 1, 2, 140, "", 0 },

  { 71, "studenttemplate/Inputs from LabVIEW/ctrl1/Kp/21/Value", offsetof
    (Parameters_StudentTemplate, u_Value_km), 31, 1, 2, 142, "", 0 },

  { 72, "studenttemplate/Inputs from LabVIEW/ctrl1/Kp/23/Value", offsetof
    (Parameters_StudentTemplate, u_Value_g), 31, 1, 2, 144, "", 0 },

  { 73, "studenttemplate/Inputs from LabVIEW/ctrl1/Kp/31/Value", offsetof
    (Parameters_StudentTemplate, u_Value_f3), 31, 1, 2, 146, "", 0 },

  { 74, "studenttemplate/Inputs from LabVIEW/ctrl1/Kp/32/Value", offsetof
    (Parameters_StudentTemplate, u_Value_m), 31, 1, 2, 148, "", 0 },

  { 75, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kpx/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kpx_Value), 31, 1, 2, 150, "", 0 },

  { 76, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kpy/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kpy_Value), 31, 1, 2, 152, "", 0 },

  { 77, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kppsi/Value", offsetof
    (Parameters_StudentTemplate, ctrl1Kppsi_Value), 31, 1, 2, 154, "", 0 },

  { 78, "studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1 Reset Integrator/Value",
    offsetof(Parameters_StudentTemplate, ctrl1ResetIntegrator_Value), 31, 1, 2,
    156, "", 0 },

  { 79, "studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q/12/Value", offsetof
    (Parameters_StudentTemplate, u_Value_d), 31, 1, 2, 158, "", 0 },

  { 80, "studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q/21/Value", offsetof
    (Parameters_StudentTemplate, u_Value_mb), 31, 1, 2, 160, "", 0 },

  { 81, "studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q_Surge/Value",
    offsetof(Parameters_StudentTemplate, Gamma_q_Surge_Value), 31, 1, 2, 162, "",
    0 },

  { 82, "studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q_Sway/Value", offsetof
    (Parameters_StudentTemplate, Gamma_q_Sway_Value), 31, 1, 2, 164, "", 0 },

  { 83, "studenttemplate/Inputs from LabVIEW/ctrl2/Initial q_x/Value", offsetof
    (Parameters_StudentTemplate, Initialq_x_Value), 31, 1, 2, 166, "", 0 },

  { 84, "studenttemplate/Inputs from LabVIEW/ctrl2/Initial q_y/Value", offsetof
    (Parameters_StudentTemplate, Initialq_y_Value), 31, 1, 2, 168, "", 0 },

  { 85, "studenttemplate/Inputs from LabVIEW/ctrl2/Initial s/Value", offsetof
    (Parameters_StudentTemplate, Initials_Value), 31, 1, 2, 170, "", 0 },

  { 86, "studenttemplate/Inputs from LabVIEW/ctrl2/K_d/12/Value", offsetof
    (Parameters_StudentTemplate, u_Value_hw), 31, 1, 2, 172, "", 0 },

  { 87, "studenttemplate/Inputs from LabVIEW/ctrl2/K_d/13/Value", offsetof
    (Parameters_StudentTemplate, u_Value_kh), 31, 1, 2, 174, "", 0 },

  { 88, "studenttemplate/Inputs from LabVIEW/ctrl2/K_d/21/Value", offsetof
    (Parameters_StudentTemplate, u_Value_l), 31, 1, 2, 176, "", 0 },

  { 89, "studenttemplate/Inputs from LabVIEW/ctrl2/K_d/23/Value", offsetof
    (Parameters_StudentTemplate, u_Value_kz), 31, 1, 2, 178, "", 0 },

  { 90, "studenttemplate/Inputs from LabVIEW/ctrl2/K_d/31/Value", offsetof
    (Parameters_StudentTemplate, u_Value_m2), 31, 1, 2, 180, "", 0 },

  { 91, "studenttemplate/Inputs from LabVIEW/ctrl2/K_d/32/Value", offsetof
    (Parameters_StudentTemplate, u_Value_ey), 31, 1, 2, 182, "", 0 },

  { 92, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kdx/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kdx_Value), 31, 1, 2, 184, "", 0 },

  { 93, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kdy/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kdy_Value), 31, 1, 2, 186, "", 0 },

  { 94, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kdpsi/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kdpsi_Value), 31, 1, 2, 188, "", 0 },

  { 95, "studenttemplate/Inputs from LabVIEW/ctrl2/K_i/12/Value", offsetof
    (Parameters_StudentTemplate, u_Value_ay), 31, 1, 2, 190, "", 0 },

  { 96, "studenttemplate/Inputs from LabVIEW/ctrl2/K_i/13/Value", offsetof
    (Parameters_StudentTemplate, u_Value_o), 31, 1, 2, 192, "", 0 },

  { 97, "studenttemplate/Inputs from LabVIEW/ctrl2/K_i/21/Value", offsetof
    (Parameters_StudentTemplate, u_Value_kr), 31, 1, 2, 194, "", 0 },

  { 98, "studenttemplate/Inputs from LabVIEW/ctrl2/K_i/23/Value", offsetof
    (Parameters_StudentTemplate, u_Value_bn), 31, 1, 2, 196, "", 0 },

  { 99, "studenttemplate/Inputs from LabVIEW/ctrl2/K_i/31/Value", offsetof
    (Parameters_StudentTemplate, u_Value_mi), 31, 1, 2, 198, "", 0 },

  { 100, "studenttemplate/Inputs from LabVIEW/ctrl2/K_i/32/Value", offsetof
    (Parameters_StudentTemplate, u_Value_pa), 31, 1, 2, 200, "", 0 },

  { 101, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kix/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kix_Value), 31, 1, 2, 202, "", 0 },

  { 102, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kiy/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kiy_Value), 31, 1, 2, 204, "", 0 },

  { 103, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kipsi/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kipsi_Value), 31, 1, 2, 206, "", 0 },

  { 104, "studenttemplate/Inputs from LabVIEW/ctrl2/K_p/12/Value", offsetof
    (Parameters_StudentTemplate, u_Value_j), 31, 1, 2, 208, "", 0 },

  { 105, "studenttemplate/Inputs from LabVIEW/ctrl2/K_p/13/Value", offsetof
    (Parameters_StudentTemplate, u_Value_lw), 31, 1, 2, 210, "", 0 },

  { 106, "studenttemplate/Inputs from LabVIEW/ctrl2/K_p/21/Value", offsetof
    (Parameters_StudentTemplate, u_Value_eq), 31, 1, 2, 212, "", 0 },

  { 107, "studenttemplate/Inputs from LabVIEW/ctrl2/K_p/23/Value", offsetof
    (Parameters_StudentTemplate, u_Value_l0), 31, 1, 2, 214, "", 0 },

  { 108, "studenttemplate/Inputs from LabVIEW/ctrl2/K_p/31/Value", offsetof
    (Parameters_StudentTemplate, u_Value_pr), 31, 1, 2, 216, "", 0 },

  { 109, "studenttemplate/Inputs from LabVIEW/ctrl2/K_p/32/Value", offsetof
    (Parameters_StudentTemplate, u_Value_dj), 31, 1, 2, 218, "", 0 },

  { 110, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kpx/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kpx_Value), 31, 1, 2, 220, "", 0 },

  { 111, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kpy/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kpy_Value), 31, 1, 2, 222, "", 0 },

  { 112, "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kppsi/Value", offsetof
    (Parameters_StudentTemplate, ctrl2Kppsi_Value), 31, 1, 2, 224, "", 0 },

  { 113,
    "studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2 Reset Integrator/Value",
    offsetof(Parameters_StudentTemplate, ctrl2ResetIntegrator_Value), 31, 1, 2,
    226, "", 0 },

  { 114, "studenttemplate/Inputs from LabVIEW/ctrl2/kappa_1/Value", offsetof
    (Parameters_StudentTemplate, kappa_1_Value), 31, 1, 2, 228, "", 0 },

  { 115, "studenttemplate/Inputs from LabVIEW/ctrl2/lambda_q/Value", offsetof
    (Parameters_StudentTemplate, lambda_q_Value), 31, 1, 2, 230, "", 0 },

  { 116,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value",
    offsetof(Parameters_StudentTemplate, l_x1_Value), 31, 1, 2, 232, "", 0 },

  { 117,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain",
    offsetof(Parameters_StudentTemplate, l_x1_Gain), 31, 1, 2, 234, "", 0 },

  { 118,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value",
    offsetof(Parameters_StudentTemplate, l_x2_Value), 31, 1, 2, 236, "", 0 },

  { 119,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain",
    offsetof(Parameters_StudentTemplate, l_x2_Gain), 31, 1, 2, 238, "", 0 },

  { 120,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value",
    offsetof(Parameters_StudentTemplate, l_y2_Value), 31, 1, 2, 240, "", 0 },

  { 121,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain",
    offsetof(Parameters_StudentTemplate, l_y2_Gain), 31, 1, 2, 242, "", 0 },

  { 122,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value",
    offsetof(Parameters_StudentTemplate, B_11_Value), 31, 1, 2, 244, "", 0 },

  { 123,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value",
    offsetof(Parameters_StudentTemplate, B_21_Value), 31, 1, 2, 246, "", 0 },

  { 124,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value",
    offsetof(Parameters_StudentTemplate, l_y1_Value), 31, 1, 2, 248, "", 0 },

  { 125,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value",
    offsetof(Parameters_StudentTemplate, B_12_Value), 31, 1, 2, 250, "", 0 },

  { 126,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value",
    offsetof(Parameters_StudentTemplate, B_22_Value), 31, 1, 2, 252, "", 0 },

  { 127,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value",
    offsetof(Parameters_StudentTemplate, B_13_Value), 31, 1, 2, 254, "", 0 },

  { 128,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value",
    offsetof(Parameters_StudentTemplate, B_23_Value), 31, 1, 2, 256, "", 0 },

  { 129,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value",
    offsetof(Parameters_StudentTemplate, B_14_Value), 31, 1, 2, 258, "", 0 },

  { 130,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value",
    offsetof(Parameters_StudentTemplate, B_24_Value), 31, 1, 2, 260, "", 0 },

  { 131,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value",
    offsetof(Parameters_StudentTemplate, B_15_Value), 31, 1, 2, 262, "", 0 },

  { 132,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value",
    offsetof(Parameters_StudentTemplate, B_25_Value), 31, 1, 2, 264, "", 0 },

  { 133,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value",
    offsetof(Parameters_StudentTemplate, l_x3_Value), 31, 1, 2, 266, "", 0 },

  { 134,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value",
    offsetof(Parameters_StudentTemplate, N_r_Value), 31, 1, 2, 268, "", 0 },

  { 135,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain",
    offsetof(Parameters_StudentTemplate, N_r_Gain), 31, 1, 2, 270, "", 0 },

  { 136,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value",
    offsetof(Parameters_StudentTemplate, N_v_Value), 31, 1, 2, 272, "", 0 },

  { 137,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain",
    offsetof(Parameters_StudentTemplate, N_v_Gain), 31, 1, 2, 274, "", 0 },

  { 138,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value",
    offsetof(Parameters_StudentTemplate, X_u_Value), 31, 1, 2, 276, "", 0 },

  { 139,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain",
    offsetof(Parameters_StudentTemplate, X_u_Gain), 31, 1, 2, 278, "", 0 },

  { 140,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value",
    offsetof(Parameters_StudentTemplate, Y_v_Value), 31, 1, 2, 280, "", 0 },

  { 141,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain",
    offsetof(Parameters_StudentTemplate, Y_v_Gain), 31, 1, 2, 282, "", 0 },

  { 142,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value",
    offsetof(Parameters_StudentTemplate, Y_r_Value), 31, 1, 2, 284, "", 0 },

  { 143,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain",
    offsetof(Parameters_StudentTemplate, Y_vr_Gain), 31, 1, 2, 286, "", 0 },

  { 144,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value",
    offsetof(Parameters_StudentTemplate, D_L_12_Value), 31, 1, 2, 288, "", 0 },

  { 145,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value",
    offsetof(Parameters_StudentTemplate, D_L_13_Value), 31, 1, 2, 290, "", 0 },

  { 146,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value",
    offsetof(Parameters_StudentTemplate, D_L_21_Value), 31, 1, 2, 292, "", 0 },

  { 147,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value",
    offsetof(Parameters_StudentTemplate, D_L_31_Value), 31, 1, 2, 294, "", 0 },

  { 148,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value",
    offsetof(Parameters_StudentTemplate, m_Value), 31, 1, 2, 296, "", 0 },

  { 149,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value",
    offsetof(Parameters_StudentTemplate, X_udot_Value), 31, 1, 2, 298, "", 0 },

  { 150,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value",
    offsetof(Parameters_StudentTemplate, M_21_Value), 31, 1, 2, 300, "", 0 },

  { 151,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value",
    offsetof(Parameters_StudentTemplate, M_31_Value), 31, 1, 2, 302, "", 0 },

  { 152,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value",
    offsetof(Parameters_StudentTemplate, M_12_Value), 31, 1, 2, 304, "", 0 },

  { 153,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value",
    offsetof(Parameters_StudentTemplate, Y_vdot_Value), 31, 1, 2, 306, "", 0 },

  { 154,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value",
    offsetof(Parameters_StudentTemplate, x_g_Value), 31, 1, 2, 308, "", 0 },

  { 155,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value",
    offsetof(Parameters_StudentTemplate, N_vdot_Value), 31, 1, 2, 310, "", 0 },

  { 156,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value",
    offsetof(Parameters_StudentTemplate, M_13_Value), 31, 1, 2, 312, "", 0 },

  { 157,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value",
    offsetof(Parameters_StudentTemplate, Y_rdot_Value), 31, 1, 2, 314, "", 0 },

  { 158,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value",
    offsetof(Parameters_StudentTemplate, I_z_Value), 31, 1, 2, 316, "", 0 },

  { 159,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value",
    offsetof(Parameters_StudentTemplate, N_rdot_Value), 31, 1, 2, 318, "", 0 },

  { 160,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value",
    offsetof(Parameters_StudentTemplate, T_e11_Value), 31, 1, 2, 320, "", 0 },

  { 161,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value",
    offsetof(Parameters_StudentTemplate, T_e21_Value), 31, 1, 2, 322, "", 0 },

  { 162,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value",
    offsetof(Parameters_StudentTemplate, l_y1_Value_e), 31, 1, 2, 324, "", 0 },

  { 163,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value",
    offsetof(Parameters_StudentTemplate, T_e12_Value), 31, 1, 2, 326, "", 0 },

  { 164,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value",
    offsetof(Parameters_StudentTemplate, T_e22_Value), 31, 1, 2, 328, "", 0 },

  { 165,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value",
    offsetof(Parameters_StudentTemplate, l_x1_Value_n), 31, 1, 2, 330, "", 0 },

  { 166,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_StudentTemplate, l_x1_Gain_n), 31, 1, 2, 332, "", 0 },

  { 167,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value",
    offsetof(Parameters_StudentTemplate, T_e13_Value), 31, 1, 2, 334, "", 0 },

  { 168,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value",
    offsetof(Parameters_StudentTemplate, T_e23_Value), 31, 1, 2, 336, "", 0 },

  { 169,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value",
    offsetof(Parameters_StudentTemplate, l_y2_Value_o), 31, 1, 2, 338, "", 0 },

  { 170,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_StudentTemplate, l_y2_Gain_f), 31, 1, 2, 340, "", 0 },

  { 171,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value",
    offsetof(Parameters_StudentTemplate, T_e14_Value), 31, 1, 2, 342, "", 0 },

  { 172,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value",
    offsetof(Parameters_StudentTemplate, T_e24_Value), 31, 1, 2, 344, "", 0 },

  { 173,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value",
    offsetof(Parameters_StudentTemplate, l_x2_Value_l), 31, 1, 2, 346, "", 0 },

  { 174,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_StudentTemplate, l_x2_Gain_b), 31, 1, 2, 348, "", 0 },

  { 175,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value",
    offsetof(Parameters_StudentTemplate, T_e15_Value), 31, 1, 2, 350, "", 0 },

  { 176,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value",
    offsetof(Parameters_StudentTemplate, T_e25_Value), 31, 1, 2, 352, "", 0 },

  { 177,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value",
    offsetof(Parameters_StudentTemplate, l_x3_Value_j), 31, 1, 2, 354, "", 0 },

  { 178,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain",
    offsetof(Parameters_StudentTemplate, PS3u_1_Gain), 31, 1, 2, 356, "", 0 },

  { 179,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues",
    offsetof(Parameters_StudentTemplate, u_1tof_1_XData), 74, 19, 2, 358, "", 0
  },

  { 180,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table",
    offsetof(Parameters_StudentTemplate, u_1tof_1_YData), 74, 19, 2, 360, "", 0
  },

  { 181,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain",
    offsetof(Parameters_StudentTemplate, PS3u_2_Gain), 31, 1, 2, 362, "", 0 },

  { 182,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues",
    offsetof(Parameters_StudentTemplate, u_2tof_2_XData), 75, 21, 2, 364, "", 0
  },

  { 183,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table",
    offsetof(Parameters_StudentTemplate, u_2tof_2_YData), 75, 21, 2, 366, "", 0
  },

  { 184,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain",
    offsetof(Parameters_StudentTemplate, PS3u_3_Gain), 31, 1, 2, 368, "", 0 },

  { 185,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues",
    offsetof(Parameters_StudentTemplate, u_3tof_3_XData), 74, 19, 2, 370, "", 0
  },

  { 186,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table",
    offsetof(Parameters_StudentTemplate, u_3tof_3_YData), 74, 19, 2, 372, "", 0
  },

  { 187,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain",
    offsetof(Parameters_StudentTemplate, PS3u_4_Gain), 31, 1, 2, 374, "", 0 },

  { 188,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues",
    offsetof(Parameters_StudentTemplate, u_4tof_4_XData), 76, 17, 2, 376, "", 0
  },

  { 189,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table",
    offsetof(Parameters_StudentTemplate, u_4tof_4_YData), 76, 17, 2, 378, "", 0
  },

  { 190,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain",
    offsetof(Parameters_StudentTemplate, PS3u_5_Gain), 31, 1, 2, 380, "", 0 },

  { 191,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues",
    offsetof(Parameters_StudentTemplate, u_5tof_5_XData), 77, 7, 2, 382, "", 0 },

  { 192,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table",
    offsetof(Parameters_StudentTemplate, u_5tof_5_YData), 77, 7, 2, 384, "", 0 },

  { 193,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn3xcoordmm_Gain), 31, 1, 2, 386, "",
    0 },

  { 194,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain",
    offsetof(Parameters_StudentTemplate, mm2mx_Gain), 31, 1, 2, 388, "", 0 },

  { 195,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn4ycoordmm_Gain), 31, 1, 2, 390, "",
    0 },

  { 196,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain",
    offsetof(Parameters_StudentTemplate, mm2my_Gain), 31, 1, 2, 392, "", 0 },

  { 197,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn6yawdeg_Gain), 31, 1, 2, 394, "",
    0 },

  { 198,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain",
    offsetof(Parameters_StudentTemplate, d2ryaw_Gain), 31, 1, 2, 396, "", 0 },

  { 199,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat), 31, 1, 2, 398, "",
    0 },

  { 200,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat), 31, 1, 2, 400, "",
    0 },

  { 201,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain), 31, 1, 2, 402, "", 0 },

  { 202,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value), 31, 1, 2, 404, "", 0 },

  { 203,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_f), 31, 1, 2, 406,
    "", 0 },

  { 204,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_p), 31, 1, 2, 408,
    "", 0 },

  { 205,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_j), 31, 1, 2, 410, "", 0 },

  { 206,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_k), 31, 1, 2, 412, "", 0
  },

  { 207,
    "studenttemplate/Main Subsystems/Control/DP control/Integrator/InitialCondition",
    offsetof(Parameters_StudentTemplate, Integrator_IC), 31, 1, 2, 414, "", 0 },

  { 208,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4/InitialCondition",
    offsetof(Parameters_StudentTemplate, Integrator4_IC), 31, 1, 2, 416, "", 0 },

  { 209, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R31/Value",
    offsetof(Parameters_StudentTemplate, R31_Value), 31, 1, 2, 418, "", 0 },

  { 210, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/-1/Gain", offsetof
    (Parameters_StudentTemplate, u_Gain), 31, 1, 2, 420, "", 0 },

  { 211, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R32/Value",
    offsetof(Parameters_StudentTemplate, R32_Value), 31, 1, 2, 422, "", 0 },

  { 212, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R13/Value",
    offsetof(Parameters_StudentTemplate, R13_Value), 31, 1, 2, 424, "", 0 },

  { 213, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R23/Value",
    offsetof(Parameters_StudentTemplate, R23_Value), 31, 1, 2, 426, "", 0 },

  { 214, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R33/Value",
    offsetof(Parameters_StudentTemplate, R33_Value), 31, 1, 2, 428, "", 0 },

  { 215,
    "studenttemplate/Main Subsystems/Control/LgV2/zeta/Integrator/InitialCondition",
    offsetof(Parameters_StudentTemplate, Integrator_IC_f), 28, 3, 2, 430, "", 0
  },

  { 216, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_c), 31, 1, 2, 432, "", 0 },

  { 217, "studenttemplate/Main Subsystems/Control/LgV2/Control law/1/Value",
    offsetof(Parameters_StudentTemplate, _Value), 31, 1, 2, 434, "", 0 },

  { 218, "studenttemplate/Main Subsystems/Control/LgV2/Control law/4/Gain",
    offsetof(Parameters_StudentTemplate, _Gain), 31, 1, 2, 436, "", 0 },

  { 219, "studenttemplate/Main Subsystems/Control/LgV2/I/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_e), 22, 9, 2, 438, "", 0
  },

  { 220,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_n), 31, 1, 2, 440,
    "", 0 },

  { 221,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_f), 31, 1, 2, 442,
    "", 0 },

  { 222,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_h), 31, 1, 2, 444, "", 0 },

  { 223,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_f), 31, 1, 2, 446, "", 0
  },

  { 224,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_c), 31, 1, 2, 448,
    "", 0 },

  { 225,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_o), 31, 1, 2, 450,
    "", 0 },

  { 226,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_n), 31, 1, 2, 452, "", 0 },

  { 227,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_m), 31, 1, 2, 454, "", 0
  },

  { 228,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_b), 31, 1, 2, 456,
    "", 0 },

  { 229,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_h), 31, 1, 2, 458,
    "", 0 },

  { 230,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_g), 31, 1, 2, 460, "", 0 },

  { 231,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_i), 31, 1, 2, 462, "", 0
  },

  { 232,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_cq), 31, 1, 2, 464,
    "", 0 },

  { 233,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_a), 31, 1, 2, 466,
    "", 0 },

  { 234,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_h4), 31, 1, 2, 468, "", 0 },

  { 235,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_n), 31, 1, 2, 470, "", 0
  },

  { 236,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_p), 31, 1, 2, 472, "", 0
  },

  { 237,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_e), 31, 1, 2, 474,
    "", 0 },

  { 238,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_b), 31, 1, 2, 476,
    "", 0 },

  { 239,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_p), 31, 1, 2, 478, "", 0 },

  { 240,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_g), 31, 1, 2, 480, "", 0
  },

  { 241,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_d), 31, 1, 2, 482,
    "", 0 },

  { 242,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_g), 31, 1, 2, 484,
    "", 0 },

  { 243,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_i), 31, 1, 2, 486, "", 0 },

  { 244,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_j), 31, 1, 2, 488, "", 0
  },

  { 245,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_dd), 31, 1, 2, 490,
    "", 0 },

  { 246,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_e), 31, 1, 2, 492,
    "", 0 },

  { 247,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_nr), 31, 1, 2, 494, "", 0 },

  { 248,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_ig), 31, 1, 2, 496, "",
    0 },

  { 249,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain",
    offsetof(Parameters_StudentTemplate, u_Gain_c), 31, 1, 2, 498, "", 0 },

  { 250,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_StudentTemplate, _2x1_Value), 32, 2, 2, 500, "", 0 },

  { 251,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value",
    offsetof(Parameters_StudentTemplate, _2x1_Value_b), 32, 2, 2, 502, "", 0 },

  { 252,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_o), 31, 1, 2, 504, "", 0 },

  { 253,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain",
    offsetof(Parameters_StudentTemplate, Gain1_Gain_l), 31, 1, 2, 506, "", 0 },

  { 254,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_f2), 31, 1, 2, 508, "",
    0 },

  { 255,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_a), 31, 1, 2, 510, "", 0
  },

  { 256,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_e), 31, 1, 2, 512, "", 0 },

  { 257, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Gain1/Gain",
    offsetof(Parameters_StudentTemplate, Gain1_Gain_n), 31, 1, 2, 514, "", 0 },

  { 258, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S11/Value",
    offsetof(Parameters_StudentTemplate, S11_Value), 31, 1, 2, 516, "", 0 },

  { 259, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/R31/Value",
    offsetof(Parameters_StudentTemplate, R31_Value_g), 31, 1, 2, 518, "", 0 },

  { 260, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12/Gain",
    offsetof(Parameters_StudentTemplate, S12_Gain), 31, 1, 2, 520, "", 0 },

  { 261, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S22/Value",
    offsetof(Parameters_StudentTemplate, S22_Value), 31, 1, 2, 522, "", 0 },

  { 262, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S32/Value",
    offsetof(Parameters_StudentTemplate, S32_Value), 31, 1, 2, 524, "", 0 },

  { 263, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S13/Value",
    offsetof(Parameters_StudentTemplate, S13_Value), 31, 1, 2, 526, "", 0 },

  { 264, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S23/Value",
    offsetof(Parameters_StudentTemplate, S23_Value), 31, 1, 2, 528, "", 0 },

  { 265, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S33/Value",
    offsetof(Parameters_StudentTemplate, S33_Value), 31, 1, 2, 530, "", 0 },

  { 266,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_StudentTemplate, _2x1_Value_a), 32, 2, 2, 532, "", 0 },

  { 267,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_mk), 24, 4, 2, 534, "",
    0 },

  { 268,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_i4), 31, 1, 2, 536, "", 0 },

  { 269,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain",
    offsetof(Parameters_StudentTemplate, _Gain_i), 31, 1, 2, 538, "", 0 },

  { 270,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value",
    offsetof(Parameters_StudentTemplate, _2x2_Value), 24, 4, 2, 540, "", 0 },

  { 271,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_StudentTemplate, _2x2_Value_l), 24, 4, 2, 542, "", 0 },

  { 272,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain",
    offsetof(Parameters_StudentTemplate, _Gain_p), 31, 1, 2, 544, "", 0 },

  { 273,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value",
    offsetof(Parameters_StudentTemplate, u_Value_b2), 31, 1, 2, 546, "", 0 },

  { 274,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_k), 31, 1, 2, 548, "", 0 },

  { 275,
    "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Integrator2/InitialCondition",
    offsetof(Parameters_StudentTemplate, Integrator2_IC), 31, 1, 2, 550, "", 0 },

  { 276,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value",
    offsetof(Parameters_StudentTemplate, _2x1_Value_d), 32, 2, 2, 552, "", 0 },

  { 277,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_a), 31, 1, 2, 554, "", 0 },

  { 278,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_StudentTemplate, _2x1_Value_j), 32, 2, 2, 556, "", 0 },

  { 279,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_j0), 31, 1, 2, 558, "",
    0 },

  { 280,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_p2), 31, 1, 2, 560, "", 0 },

  { 281,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_d), 31, 1, 2, 562, "", 0
  },

  { 282,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain",
    offsetof(Parameters_StudentTemplate, u_Gain_h), 31, 1, 2, 564, "", 0 },

  { 283,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain",
    offsetof(Parameters_StudentTemplate, _Gain_h), 31, 1, 2, 566, "", 0 },

  { 284,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain",
    offsetof(Parameters_StudentTemplate, _Gain_n), 31, 1, 2, 568, "", 0 },

  { 285,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_gx), 31, 1, 2, 570, "", 0 },

  { 286,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_kd), 31, 1, 2, 572, "",
    0 },

  { 287,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_kp), 31, 1, 2, 574, "", 0 },

  { 288,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value",
    offsetof(Parameters_StudentTemplate, u_Value_gk), 31, 1, 2, 576, "", 0 },

  { 289,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_h), 31, 1, 2, 578, "", 0
  },

  { 290, "studenttemplate/Main Subsystems/Control/LgV2/V_1^q/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_k3), 31, 1, 2, 580, "", 0 },

  { 291, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_ni), 31, 1, 2, 582, "", 0 },

  { 292,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues",
    offsetof(Parameters_StudentTemplate, f_1tou_1_XData), 78, 39, 2, 584, "", 0
  },

  { 293,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table",
    offsetof(Parameters_StudentTemplate, f_1tou_1_YData), 78, 39, 2, 586, "", 0
  },

  { 294,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_h4), 31, 1, 2, 588, "",
    0 },

  { 295,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_b), 31, 1, 2, 590, "", 0
  },

  { 296,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_c), 31, 1, 2, 592, "", 0
  },

  { 297,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_gx), 31, 1, 2, 594, "",
    0 },

  { 298,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues",
    offsetof(Parameters_StudentTemplate, f_2000391_XData), 79, 11, 2, 596, "", 0
  },

  { 299,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table",
    offsetof(Parameters_StudentTemplate, f_2000391_YData), 79, 11, 2, 598, "", 0
  },

  { 300,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues",
    offsetof(Parameters_StudentTemplate, f_2006731f_2000391_XData), 28, 3, 2,
    600, "", 0 },

  { 301,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table",
    offsetof(Parameters_StudentTemplate, f_2006731f_2000391_YData), 28, 3, 2,
    602, "", 0 },

  { 302,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues",
    offsetof(Parameters_StudentTemplate, f_2006731_XData), 80, 18, 2, 604, "", 0
  },

  { 303,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table",
    offsetof(Parameters_StudentTemplate, f_2006731_YData), 80, 18, 2, 606, "", 0
  },

  { 304,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues",
    offsetof(Parameters_StudentTemplate, f_3tou_3_XData), 78, 39, 2, 608, "", 0
  },

  { 305,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table",
    offsetof(Parameters_StudentTemplate, f_3tou_3_YData), 78, 39, 2, 610, "", 0
  },

  { 306,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_ke), 31, 1, 2, 612, "",
    0 },

  { 307,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_h3), 31, 1, 2, 614, "",
    0 },

  { 308,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues",
    offsetof(Parameters_StudentTemplate, f_400451_XData), 81, 15, 2, 616, "", 0
  },

  { 309,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table",
    offsetof(Parameters_StudentTemplate, f_400451_YData), 81, 15, 2, 618, "", 0
  },

  { 310,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues",
    offsetof(Parameters_StudentTemplate, f_400451_XData_n), 82, 13, 2, 620, "",
    0 },

  { 311,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table",
    offsetof(Parameters_StudentTemplate, f_400451_YData_p), 82, 13, 2, 622, "",
    0 },

  { 312,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_StudentTemplate, DeadZone001_Start), 31, 1, 2, 624, "",
    0 },

  { 313,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_StudentTemplate, DeadZone001_End), 31, 1, 2, 626, "", 0
  },

  { 314,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_ek), 31, 1, 2, 628, "",
    0 },

  { 315,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_o), 31, 1, 2, 630, "", 0
  },

  { 316,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues",
    offsetof(Parameters_StudentTemplate, f_50_XData), 83, 10, 2, 632, "", 0 },

  { 317,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table",
    offsetof(Parameters_StudentTemplate, f_50_YData), 83, 10, 2, 634, "", 0 },

  { 318,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value",
    offsetof(Parameters_StudentTemplate, f_50_Value), 31, 1, 2, 636, "", 0 },

  { 319,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues",
    offsetof(Parameters_StudentTemplate, f_50_XData_a), 83, 10, 2, 638, "", 0 },

  { 320,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table",
    offsetof(Parameters_StudentTemplate, f_50_YData_f), 83, 10, 2, 640, "", 0 },

  { 321,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value",
    offsetof(Parameters_StudentTemplate, BT_power_limit_Value), 31, 1, 2, 642,
    "", 0 },

  { 322,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value",
    offsetof(Parameters_StudentTemplate, VSP_speeds_Value), 31, 1, 2, 644, "", 0
  },

  { 323,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_k), 31, 1, 2, 646,
    "", 0 },

  { 324,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_ak), 31, 1, 2, 648,
    "", 0 },

  { 325,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn2Error_Gain), 31, 1, 2, 650, "", 0
  },

  { 326,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn9Residual_Gain), 31, 1, 2, 652, "",
    0 },

  { 327,
    "studenttemplate/Main Subsystems/Plant/Thruster setting workaround/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_a), 31, 1, 2, 654,
    "", 0 },

  { 328,
    "studenttemplate/Main Subsystems/Plant/Thruster setting workaround/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_m), 31, 1, 2, 656,
    "", 0 },

  { 329,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Constant1/Value",
    offsetof(Parameters_StudentTemplate, Constant1_Value), 22, 9, 2, 658, "", 0
  },

  { 330,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn5zcoordmm_Gain), 31, 1, 2, 660, "",
    0 },

  { 331,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain",
    offsetof(Parameters_StudentTemplate, mm2mz_Gain), 31, 1, 2, 662, "", 0 },

  { 332,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn8rolldeg_Gain), 31, 1, 2, 664, "",
    0 },

  { 333,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain",
    offsetof(Parameters_StudentTemplate, d2rroll_Gain), 31, 1, 2, 666, "", 0 },

  { 334,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn7pitchdeg_Gain), 31, 1, 2, 668, "",
    0 },

  { 335,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain",
    offsetof(Parameters_StudentTemplate, d2rpitch_Gain), 31, 1, 2, 670, "", 0 },

  { 336,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN/Gain",
    offsetof(Parameters_StudentTemplate, QTMIn1FN_Gain), 31, 1, 2, 672, "", 0 },

  { 337,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3/InitialCondition",
    offsetof(Parameters_StudentTemplate, Integrator3_IC), 31, 1, 2, 674, "", 0 },

  { 338,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_kw), 31, 1, 2, 676,
    "", 0 },

  { 339,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_fg), 31, 1, 2, 678,
    "", 0 },

  { 340,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_p0), 31, 1, 2, 680, "", 0 },

  { 341,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_f3), 31, 1, 2, 682, "",
    0 },

  { 342,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_ft), 31, 1, 2, 684,
    "", 0 },

  { 343,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_k), 31, 1, 2, 686,
    "", 0 },

  { 344,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_b), 31, 1, 2, 688, "", 0 },

  { 345,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_cz), 31, 1, 2, 690, "",
    0 },

  { 346,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2/Gain",
    offsetof(Parameters_StudentTemplate, K2_Gain), 22, 9, 2, 692, "", 0 },

  { 347,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3/Gain",
    offsetof(Parameters_StudentTemplate, K3_Gain), 22, 9, 2, 694, "", 0 },

  { 348,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4/Gain",
    offsetof(Parameters_StudentTemplate, K4_Gain), 22, 9, 2, 696, "", 0 },

  { 349,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues",
    offsetof(Parameters_StudentTemplate, u_1tof_1_XData_p), 78, 39, 2, 698, "",
    0 },

  { 350,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table",
    offsetof(Parameters_StudentTemplate, u_1tof_1_YData_i), 78, 39, 2, 700, "",
    0 },

  { 351,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_it), 31, 1, 2, 702, "",
    0 },

  { 352,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_pt), 31, 1, 2, 704, "",
    0 },

  { 353,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_fy), 31, 1, 2, 706, "",
    0 },

  { 354,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_jd), 31, 1, 2, 708, "",
    0 },

  { 355,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues",
    offsetof(Parameters_StudentTemplate, u_205_XData), 79, 11, 2, 710, "", 0 },

  { 356,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table",
    offsetof(Parameters_StudentTemplate, u_205_YData), 79, 11, 2, 712, "", 0 },

  { 357,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues",
    offsetof(Parameters_StudentTemplate, u_201u_202_XData), 28, 3, 2, 714, "", 0
  },

  { 358,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table",
    offsetof(Parameters_StudentTemplate, u_201u_202_YData), 28, 3, 2, 716, "", 0
  },

  { 359,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues",
    offsetof(Parameters_StudentTemplate, u_20_XData), 80, 18, 2, 718, "", 0 },

  { 360,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table",
    offsetof(Parameters_StudentTemplate, u_20_YData), 80, 18, 2, 720, "", 0 },

  { 361,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues",
    offsetof(Parameters_StudentTemplate, u_3tof_3_XData_e), 78, 39, 2, 722, "",
    0 },

  { 362,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table",
    offsetof(Parameters_StudentTemplate, u_3tof_3_YData_a), 78, 39, 2, 724, "",
    0 },

  { 363,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_bh), 31, 1, 2, 726, "",
    0 },

  { 364,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_cy), 31, 1, 2, 728, "",
    0 },

  { 365,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues",
    offsetof(Parameters_StudentTemplate, u_401_XData), 81, 15, 2, 730, "", 0 },

  { 366,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table",
    offsetof(Parameters_StudentTemplate, u_401_YData), 81, 15, 2, 732, "", 0 },

  { 367,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues",
    offsetof(Parameters_StudentTemplate, u_401_XData_m), 82, 13, 2, 734, "", 0 },

  { 368,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table",
    offsetof(Parameters_StudentTemplate, u_401_YData_e), 82, 13, 2, 736, "", 0 },

  { 369,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_StudentTemplate, DeadZone001_Start_e), 31, 1, 2, 738, "",
    0 },

  { 370,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_StudentTemplate, DeadZone001_End_k), 31, 1, 2, 740, "",
    0 },

  { 371,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_dp), 31, 1, 2, 742, "",
    0 },

  { 372,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_hu), 31, 1, 2, 744, "",
    0 },

  { 373,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues",
    offsetof(Parameters_StudentTemplate, u_50_XData), 83, 10, 2, 746, "", 0 },

  { 374,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table",
    offsetof(Parameters_StudentTemplate, u_50_YData), 83, 10, 2, 748, "", 0 },

  { 375,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value",
    offsetof(Parameters_StudentTemplate, u_50_Value), 31, 1, 2, 750, "", 0 },

  { 376,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues",
    offsetof(Parameters_StudentTemplate, u_50_XData_d), 83, 10, 2, 752, "", 0 },

  { 377,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table",
    offsetof(Parameters_StudentTemplate, u_50_YData_g), 83, 10, 2, 754, "", 0 },

  { 378,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)/Gain",
    offsetof(Parameters_StudentTemplate, invT_b_Gain), 22, 9, 2, 756, "", 0 },

  { 379,
    "studenttemplate/Main Subsystems/Plant/saturation/Saturation/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation_UpperSat_p), 31, 1, 2, 758,
    "", 0 },

  { 380,
    "studenttemplate/Main Subsystems/Plant/saturation/Saturation/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation_LowerSat_oc), 31, 1, 2, 760,
    "", 0 },

  { 381,
    "studenttemplate/Main Subsystems/Plant/saturation/Saturation1/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation1_UpperSat), 31, 1, 2, 762,
    "", 0 },

  { 382,
    "studenttemplate/Main Subsystems/Plant/saturation/Saturation1/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation1_LowerSat), 31, 1, 2, 764,
    "", 0 },

  { 383,
    "studenttemplate/Main Subsystems/Plant/saturation/Saturation2/UpperLimit",
    offsetof(Parameters_StudentTemplate, Saturation2_UpperSat), 31, 1, 2, 766,
    "", 0 },

  { 384,
    "studenttemplate/Main Subsystems/Plant/saturation/Saturation2/LowerLimit",
    offsetof(Parameters_StudentTemplate, Saturation2_LowerSat), 31, 1, 2, 768,
    "", 0 },

  { 385, "studenttemplate/Main Subsystems/Plant/saturation/plant tau_surge/Gain",
    offsetof(Parameters_StudentTemplate, planttau_surge_Gain), 31, 1, 2, 770, "",
    0 },

  { 386, "studenttemplate/Main Subsystems/Plant/saturation/plant tau_sway/Gain",
    offsetof(Parameters_StudentTemplate, planttau_sway_Gain), 31, 1, 2, 772, "",
    0 },

  { 387, "studenttemplate/Main Subsystems/Plant/saturation/plant tau_yaw/Gain",
    offsetof(Parameters_StudentTemplate, planttau_yaw_Gain), 31, 1, 2, 774, "",
    0 },

  { 388,
    "studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain",
    offsetof(Parameters_StudentTemplate, BatteryBowThruster_Gain), 31, 1, 2, 776,
    "", 0 },

  { 389, "studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain",
    offsetof(Parameters_StudentTemplate, BatteryMain_Gain), 31, 1, 2, 778, "", 0
  },

  { 390, "studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain",
    offsetof(Parameters_StudentTemplate, BatteryServo_Gain), 31, 1, 2, 780, "",
    0 },

  { 391, "studenttemplate/Outputs to LabVIEW/Command/tau1/Gain", offsetof
    (Parameters_StudentTemplate, tau1_Gain), 31, 1, 2, 782, "", 0 },

  { 392, "studenttemplate/Outputs to LabVIEW/Command/tau2/Gain", offsetof
    (Parameters_StudentTemplate, tau2_Gain), 31, 1, 2, 784, "", 0 },

  { 393, "studenttemplate/Outputs to LabVIEW/Command/tau3/Gain", offsetof
    (Parameters_StudentTemplate, tau3_Gain), 31, 1, 2, 786, "", 0 },

  { 394, "studenttemplate/Outputs to LabVIEW/Command/tau4/Gain", offsetof
    (Parameters_StudentTemplate, tau4_Gain), 31, 1, 2, 788, "", 0 },

  { 395, "studenttemplate/Outputs to LabVIEW/Command/tau5/Gain", offsetof
    (Parameters_StudentTemplate, tau5_Gain), 31, 1, 2, 790, "", 0 },

  { 396, "studenttemplate/Outputs to LabVIEW/Command/tau6/Gain", offsetof
    (Parameters_StudentTemplate, tau6_Gain), 31, 1, 2, 792, "", 0 },

  { 397, "studenttemplate/Outputs to LabVIEW/Command/plant BT power/Gain",
    offsetof(Parameters_StudentTemplate, plantBTpower_Gain), 31, 1, 2, 794, "",
    0 },

  { 398, "studenttemplate/Outputs to LabVIEW/Command/plant VSP speed/Gain",
    offsetof(Parameters_StudentTemplate, plantVSPspeed_Gain), 31, 1, 2, 796, "",
    0 },

  { 399, "studenttemplate/Outputs to LabVIEW/Command/plant u_1/Gain", offsetof
    (Parameters_StudentTemplate, plantu_1_Gain), 31, 1, 2, 798, "", 0 },

  { 400, "studenttemplate/Outputs to LabVIEW/Command/plant u_2/Gain", offsetof
    (Parameters_StudentTemplate, plantu_2_Gain), 31, 1, 2, 800, "", 0 },

  { 401, "studenttemplate/Outputs to LabVIEW/Command/plant u_3/Gain", offsetof
    (Parameters_StudentTemplate, plantu_3_Gain), 31, 1, 2, 802, "", 0 },

  { 402, "studenttemplate/Outputs to LabVIEW/Command/plant u_4/Gain", offsetof
    (Parameters_StudentTemplate, plantu_4_Gain), 31, 1, 2, 804, "", 0 },

  { 403, "studenttemplate/Outputs to LabVIEW/Command/plant u_5/Gain", offsetof
    (Parameters_StudentTemplate, plantu_5_Gain), 31, 1, 2, 806, "", 0 },

  { 404, "studenttemplate/Outputs to LabVIEW/Command/fact1/Gain", offsetof
    (Parameters_StudentTemplate, fact1_Gain), 31, 1, 2, 808, "", 0 },

  { 405, "studenttemplate/Outputs to LabVIEW/Command/fact2/Gain", offsetof
    (Parameters_StudentTemplate, fact2_Gain), 31, 1, 2, 810, "", 0 },

  { 406, "studenttemplate/Outputs to LabVIEW/Command/fact3/Gain", offsetof
    (Parameters_StudentTemplate, fact3_Gain), 31, 1, 2, 812, "", 0 },

  { 407, "studenttemplate/Outputs to LabVIEW/Command/fact4/Gain", offsetof
    (Parameters_StudentTemplate, fact4_Gain), 31, 1, 2, 814, "", 0 },

  { 408, "studenttemplate/Outputs to LabVIEW/Command/fact5/Gain", offsetof
    (Parameters_StudentTemplate, fact5_Gain), 31, 1, 2, 816, "", 0 },

  { 409, "studenttemplate/Outputs to LabVIEW/Command/taux/Gain", offsetof
    (Parameters_StudentTemplate, taux_Gain), 31, 1, 2, 818, "", 0 },

  { 410, "studenttemplate/Outputs to LabVIEW/Command/tauy/Gain", offsetof
    (Parameters_StudentTemplate, tauy_Gain), 31, 1, 2, 820, "", 0 },

  { 411, "studenttemplate/Outputs to LabVIEW/Command/tauyaw/Gain", offsetof
    (Parameters_StudentTemplate, tauyaw_Gain), 31, 1, 2, 822, "", 0 },

  { 412, "studenttemplate/Outputs to LabVIEW/Command/omega_qy/Gain", offsetof
    (Parameters_StudentTemplate, omega_qy_Gain), 31, 1, 2, 824, "", 0 },

  { 413, "studenttemplate/Outputs to LabVIEW/Command/omegaqx/Gain", offsetof
    (Parameters_StudentTemplate, omegaqx_Gain), 31, 1, 2, 826, "", 0 },

  { 414, "studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain",
    offsetof(Parameters_StudentTemplate, CSE1_rdegs_Gain), 31, 1, 2, 828, "", 0
  },

  { 415, "studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain",
    offsetof(Parameters_StudentTemplate, CSE1_ums_Gain), 31, 1, 2, 830, "", 0 },

  { 416, "studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain",
    offsetof(Parameters_StudentTemplate, CSE1_vms_Gain), 31, 1, 2, 832, "", 0 },

  { 417, "studenttemplate/Outputs to LabVIEW/Naviagtion/QS Error/Gain", offsetof
    (Parameters_StudentTemplate, QSError_Gain), 31, 1, 2, 834, "", 0 },

  { 418, "studenttemplate/Outputs to LabVIEW/Naviagtion/QS Frame/Gain", offsetof
    (Parameters_StudentTemplate, QSFrame_Gain), 31, 1, 2, 836, "", 0 },

  { 419, "studenttemplate/Outputs to LabVIEW/Visualization/psi [deg]/Gain",
    offsetof(Parameters_StudentTemplate, psideg_Gain), 31, 1, 2, 838, "", 0 },

  { 420, "studenttemplate/Outputs to LabVIEW/Visualization/psi-psid [deg]/Gain",
    offsetof(Parameters_StudentTemplate, psipsiddeg_Gain), 31, 1, 2, 840, "", 0
  },

  { 421,
    "studenttemplate/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]/Gain",
    offsetof(Parameters_StudentTemplate, psiLOSpsideg_Gain), 31, 1, 2, 842, "",
    0 },

  { 422,
    "studenttemplate/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]/Gain",
    offsetof(Parameters_StudentTemplate, psiLOSpsiddeg_Gain), 31, 1, 2, 844, "",
    0 },

  { 423, "studenttemplate/Outputs to LabVIEW/Visualization/psi_LOS [deg]/Gain",
    offsetof(Parameters_StudentTemplate, psi_LOSdeg_Gain), 31, 1, 2, 846, "", 0
  },

  { 424, "studenttemplate/Outputs to LabVIEW/Visualization/psid [deg]/Gain",
    offsetof(Parameters_StudentTemplate, psiddeg_Gain), 31, 1, 2, 848, "", 0 },

  { 425, "studenttemplate/Outputs to LabVIEW/Visualization/psi_plot/Gain",
    offsetof(Parameters_StudentTemplate, psi_plot_Gain), 31, 1, 2, 850, "", 0 },

  { 426, "studenttemplate/Outputs to LabVIEW/Visualization/qx [m]/Gain",
    offsetof(Parameters_StudentTemplate, qxm_Gain), 31, 1, 2, 852, "", 0 },

  { 427, "studenttemplate/Outputs to LabVIEW/Visualization/qx-x [m]/Gain",
    offsetof(Parameters_StudentTemplate, qxxm_Gain), 31, 1, 2, 854, "", 0 },

  { 428, "studenttemplate/Outputs to LabVIEW/Visualization/qx-xd [m]1/Gain",
    offsetof(Parameters_StudentTemplate, qxxdm1_Gain), 31, 1, 2, 856, "", 0 },

  { 429, "studenttemplate/Outputs to LabVIEW/Visualization/qy [m]/Gain",
    offsetof(Parameters_StudentTemplate, qym_Gain), 31, 1, 2, 858, "", 0 },

  { 430, "studenttemplate/Outputs to LabVIEW/Visualization/qy-y [m]/Gain",
    offsetof(Parameters_StudentTemplate, qyym_Gain), 31, 1, 2, 860, "", 0 },

  { 431, "studenttemplate/Outputs to LabVIEW/Visualization/qy-yd [m]1/Gain",
    offsetof(Parameters_StudentTemplate, qyydm1_Gain), 31, 1, 2, 862, "", 0 },

  { 432, "studenttemplate/Outputs to LabVIEW/Visualization/x [m]/Gain", offsetof
    (Parameters_StudentTemplate, xm_Gain), 31, 1, 2, 864, "", 0 },

  { 433, "studenttemplate/Outputs to LabVIEW/Visualization/x-xd [m]/Gain",
    offsetof(Parameters_StudentTemplate, xxdm_Gain), 31, 1, 2, 866, "", 0 },

  { 434, "studenttemplate/Outputs to LabVIEW/Visualization/xd [m]/Gain",
    offsetof(Parameters_StudentTemplate, xdm_Gain), 31, 1, 2, 868, "", 0 },

  { 435, "studenttemplate/Outputs to LabVIEW/Visualization/x_plot/Gain",
    offsetof(Parameters_StudentTemplate, x_plot_Gain), 31, 1, 2, 870, "", 0 },

  { 436, "studenttemplate/Outputs to LabVIEW/Visualization/y [m]/Gain", offsetof
    (Parameters_StudentTemplate, ym_Gain), 31, 1, 2, 872, "", 0 },

  { 437, "studenttemplate/Outputs to LabVIEW/Visualization/y-yd [m]/Gain",
    offsetof(Parameters_StudentTemplate, yydm_Gain), 31, 1, 2, 874, "", 0 },

  { 438, "studenttemplate/Outputs to LabVIEW/Visualization/yd [m]/Gain",
    offsetof(Parameters_StudentTemplate, ydm_Gain), 31, 1, 2, 876, "", 0 },

  { 439, "studenttemplate/Outputs to LabVIEW/Visualization/y_plot/Gain",
    offsetof(Parameters_StudentTemplate, y_plot_Gain), 31, 1, 2, 878, "", 0 },

  { 440, "studenttemplate/Outputs to LabVIEW/Visualization/splot/Gain", offsetof
    (Parameters_StudentTemplate, splot_Gain), 31, 1, 2, 880, "", 0 },

  { 441,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain",
    offsetof(Parameters_StudentTemplate, R12_Gain), 31, 1, 2, 882, "", 0 },

  { 442,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain",
    offsetof(Parameters_StudentTemplate, R22_Gain), 31, 1, 2, 884, "", 0 },

  { 443,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value",
    offsetof(Parameters_StudentTemplate, _Value_m), 31, 1, 2, 886, "", 0 },

  { 444,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain",
    offsetof(Parameters_StudentTemplate, S12_Gain_h), 31, 1, 2, 888, "", 0 },

  { 445,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value",
    offsetof(Parameters_StudentTemplate, _Value_f), 31, 1, 2, 890, "", 0 },

  { 446,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain",
    offsetof(Parameters_StudentTemplate, S12_Gain_e), 31, 1, 2, 892, "", 0 },

  { 447,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain",
    offsetof(Parameters_StudentTemplate, BT_D_Gain1_Gain), 31, 1, 2, 894, "", 0
  },

  { 448,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value",
    offsetof(Parameters_StudentTemplate, BT_Power_Offset1_Value), 31, 1, 2, 896,
    "", 0 },

  { 449,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain",
    offsetof(Parameters_StudentTemplate, BT_D_Gain2_Gain), 31, 1, 2, 898, "", 0
  },

  { 450,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain",
    offsetof(Parameters_StudentTemplate, BT_L_Gain1_Gain), 31, 1, 2, 900, "", 0
  },

  { 451,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain",
    offsetof(Parameters_StudentTemplate, BT_L_Gain2_Gain), 31, 1, 2, 902, "", 0
  },

  { 452,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value",
    offsetof(Parameters_StudentTemplate, BT_Power_Offset2_Value), 31, 1, 2, 904,
    "", 0 },

  { 453,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value",
    offsetof(Parameters_StudentTemplate, BT_Power_Offset3_Value), 31, 1, 2, 906,
    "", 0 },

  { 454,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value",
    offsetof(Parameters_StudentTemplate, Constant_Value_l), 31, 1, 2, 908, "", 0
  },

  { 455,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value",
    offsetof(Parameters_StudentTemplate, Constant1_Value_k), 31, 1, 2, 910, "",
    0 },

  { 456,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain",
    offsetof(Parameters_StudentTemplate, Neg_Gain), 31, 1, 2, 912, "", 0 },

  { 457,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain",
    offsetof(Parameters_StudentTemplate, x_Gain), 31, 1, 2, 914, "", 0 },

  { 458,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain",
    offsetof(Parameters_StudentTemplate, y_Gain), 31, 1, 2, 916, "", 0 },

  { 459,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_StudentTemplate, Servo1_RowIdx), 33, 3, 2, 918, "", 0 },

  { 460,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_StudentTemplate, Servo1_ColIdx), 33, 3, 2, 920, "", 0 },

  { 461,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table",
    offsetof(Parameters_StudentTemplate, Servo1_Table), 22, 9, 2, 922, "", 0 },

  { 462,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_StudentTemplate, Servo2_RowIdx), 33, 3, 2, 924, "", 0 },

  { 463,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_StudentTemplate, Servo2_ColIdx), 33, 3, 2, 926, "", 0 },

  { 464,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table",
    offsetof(Parameters_StudentTemplate, Servo2_Table), 22, 9, 2, 928, "", 0 },

  { 465,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_StudentTemplate, Servo3_RowIdx), 33, 3, 2, 930, "", 0 },

  { 466,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_StudentTemplate, Servo3_ColIdx), 33, 3, 2, 932, "", 0 },

  { 467,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table",
    offsetof(Parameters_StudentTemplate, Servo3_Table), 22, 9, 2, 934, "", 0 },

  { 468,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_StudentTemplate, Servo4_RowIdx), 33, 3, 2, 936, "", 0 },

  { 469,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_StudentTemplate, Servo4_ColIdx), 33, 3, 2, 938, "", 0 },

  { 470,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table",
    offsetof(Parameters_StudentTemplate, Servo4_Table), 22, 9, 2, 940, "", 0 },

  { 471,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_StudentTemplate, VPS_Speed_Gain_Gain), 31, 1, 2, 942, "",
    0 },

  { 472,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_StudentTemplate, VPS_Power_Offset_Value), 31, 1, 2, 944,
    "", 0 },

  { 473,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain",
    offsetof(Parameters_StudentTemplate, VSPSPort_Gain), 31, 1, 2, 946, "", 0 },

  { 474,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_StudentTemplate, VSPSStarboard_Gain), 31, 1, 2, 948, "",
    0 },

  { 475,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_StudentTemplate, R31_Value_j), 31, 1, 2, 950, "", 0 },

  { 476,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_StudentTemplate, R32_Value_h), 31, 1, 2, 952, "", 0 },

  { 477,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_StudentTemplate, R13_Value_p), 31, 1, 2, 954, "", 0 },

  { 478,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_StudentTemplate, R23_Value_f), 31, 1, 2, 956, "", 0 },

  { 479,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_StudentTemplate, R33_Value_h), 31, 1, 2, 958, "", 0 },

  { 480,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_StudentTemplate, Gain1_Gain_n2), 38, 1, 2, 960, "", 0 },

  { 481,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_gq), 38, 1, 2, 962, "", 0 },

  { 482,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_en), 38, 1, 2, 964, "", 0 },

  { 483,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_StudentTemplate, Gain1_Gain_c), 38, 1, 2, 966, "", 0 },

  { 484,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_StudentTemplate, Gain1_Gain_g), 38, 1, 2, 968, "", 0 },

  { 485,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_as), 38, 1, 2, 970, "", 0 },

  { 486,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_StudentTemplate, Gain_Gain_hc), 38, 1, 2, 972, "", 0 },

  { 487,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_StudentTemplate, Gain1_Gain_h), 38, 1, 2, 974, "", 0 },
};

static int NI_ParamListSize = 488;
static int NI_ParamDimList[] = {
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Control Input Selector/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Control Mode Selector/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Enable CSE1/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/tauxscale/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/tauyscale/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/tauyawscale/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/offset u1/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/offset u2/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/offset u3/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/offset u4/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Delta [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Path Selector  [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/my [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/u_d [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/x_dmax [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/x_dmin [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/y_dmax [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/y_dmin [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Ellipse/k [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Ellipse/x_0 [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Ellipse/y_0 [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/L2 [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/PlayStation3/R2 [-]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Setpoint/setpointpsi [deg]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Setpoint/setpointx [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/Setpoint/setpointy [m]/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kd/12/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kd/13/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kd/21/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kd/23/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kd/31/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kd/32/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kdx/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kdy/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kdpsi/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Ki/12/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Ki/13/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Ki/21/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Ki/23/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Ki/31/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Ki/32/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kix/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kiy/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kipsi/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kp/12/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kp/13/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kp/21/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kp/23/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kp/31/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/Kp/32/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kpx/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kpy/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1Kppsi/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl1/ctrl1 Reset Integrator/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q/12/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q/21/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q_Surge/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q_Sway/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/Initial q_x/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/Initial q_y/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/Initial s/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_d/12/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_d/13/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_d/21/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_d/23/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_d/31/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_d/32/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kdx/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kdy/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kdpsi/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_i/12/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_i/13/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_i/21/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_i/23/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_i/31/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_i/32/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kix/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kiy/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kipsi/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_p/12/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_p/13/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_p/21/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_p/23/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_p/31/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/K_p/32/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kpx/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kpy/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2Kppsi/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/ctrl2 Reset Integrator/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/kappa_1/Value */
  1, 1,                                /* studenttemplate/Inputs from LabVIEW/ctrl2/lambda_q/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain */
  19, 1,                               /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues */
  19, 1,                               /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain */
  21, 1,                               /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues */
  21, 1,                               /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain */
  19, 1,                               /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues */
  19, 1,                               /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain */
  17, 1,                               /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues */
  17, 1,                               /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain */
  1, 7,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues */
  1, 7,                                /* studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/DP control/Integrator/InitialCondition */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4/InitialCondition */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R31/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/R(psi)/-1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R32/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R13/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R23/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R33/Value */
  3, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/zeta/Integrator/InitialCondition */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Control law/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Control law/1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Control law/4/Gain */
  3, 3,                                /* studenttemplate/Main Subsystems/Control/LgV2/I/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain */
  2, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/0_2x1/Value */
  2, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Control law/Gain1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S11/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/R31/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S22/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S32/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S13/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S23/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S33/Value */
  2, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  2, 2,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain */
  2, 2,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value */
  2, 2,                                /* studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Update laws/Integrator2/InitialCondition */
  2, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain */
  2, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/V_1^q/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/LgV2/Update laws/Gain/Gain */
  1, 39,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues */
  1, 39,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues */
  11, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table */
  3, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues */
  3, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table */
  18, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues */
  18, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table */
  1, 39,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues */
  1, 39,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues */
  15, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table */
  13, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues */
  13, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues */
  10, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value */
  10, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues */
  10, 1,                               /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/Thruster setting workaround/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/Thruster setting workaround/Saturation/LowerLimit */
  3, 3,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/Constant1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3/InitialCondition */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Constant/Value */
  3, 3,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2/Gain */
  3, 3,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3/Gain */
  3, 3,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4/Gain */
  1, 39,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues */
  1, 39,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues */
  11, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table */
  3, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues */
  3, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table */
  18, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues */
  18, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table */
  1, 39,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues */
  1, 39,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues */
  15, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table */
  13, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues */
  13, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues */
  10, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value */
  10, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues */
  10, 1,                               /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table */
  3, 3,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/Saturation/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/Saturation/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/Saturation1/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/Saturation1/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/Saturation2/UpperLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/Saturation2/LowerLimit */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/plant tau_surge/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/plant tau_sway/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/saturation/plant tau_yaw/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/tau1/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/tau2/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/tau3/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/tau4/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/tau5/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/tau6/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/plant BT power/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/plant VSP speed/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/plant u_1/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/plant u_2/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/plant u_3/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/plant u_4/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/plant u_5/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/fact1/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/fact2/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/fact3/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/fact4/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/fact5/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/taux/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/tauy/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/tauyaw/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/omega_qy/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Command/omegaqx/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Naviagtion/QS Error/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Naviagtion/QS Frame/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/psi [deg]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/psi-psid [deg]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/psi_LOS [deg]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/psid [deg]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/psi_plot/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/qx [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/qx-x [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/qx-xd [m]1/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/qy [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/qy-y [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/qy-yd [m]1/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/x [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/x-xd [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/xd [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/x_plot/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/y [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/y-yd [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/yd [m]/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/y_plot/Gain */
  1, 1,                                /* studenttemplate/Outputs to LabVIEW/Visualization/splot/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 704;
static NI_Signal NI_SigList[] = {
  { 0, "studenttemplate/Inputs from LabVIEW/tauxscale", 0, "", offsetof
    (BlockIO_StudentTemplate, tauxscale), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "studenttemplate/Inputs from LabVIEW/tauyscale", 0, "", offsetof
    (BlockIO_StudentTemplate, tauyscale), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "studenttemplate/Inputs from LabVIEW/tauyawscale", 0, "", offsetof
    (BlockIO_StudentTemplate, tauyawscale), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]",
    0, "", offsetof(BlockIO_StudentTemplate, Initialpsirad), BLOCKIO_SIG, 0, 1,
    2, 6, 0 },

  { 4, "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial x [m]", 0,
    "", offsetof(BlockIO_StudentTemplate, Initialxm), BLOCKIO_SIG, 0, 1, 2, 8, 0
  },

  { 5, "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial y [m]", 0,
    "", offsetof(BlockIO_StudentTemplate, Initialym), BLOCKIO_SIG, 0, 1, 2, 10,
    0 },

  { 6, "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]",
    0, "", offsetof(BlockIO_StudentTemplate, Initialrrads), BLOCKIO_SIG, 0, 1, 2,
    12, 0 },

  { 7, "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]",
    0, "", offsetof(BlockIO_StudentTemplate, Initialums), BLOCKIO_SIG, 0, 1, 2,
    14, 0 },

  { 8, "studenttemplate/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]",
    0, "", offsetof(BlockIO_StudentTemplate, Initialvms), BLOCKIO_SIG, 0, 1, 2,
    16, 0 },

  { 9, "studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_StudentTemplate,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_StudentTemplate,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "studenttemplate/Inputs from LabVIEW/PlayStation3/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_StudentTemplate,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "studenttemplate/Inputs from LabVIEW/PlayStation3/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_StudentTemplate,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "studenttemplate/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_StudentTemplate, Gain1), BLOCKIO_SIG, 0, 1, 2, 26, 0
  },

  { 14, "studenttemplate/Inputs from LabVIEW/ctrl1/Kd/[3x3]", 0, "", offsetof
    (BlockIO_StudentTemplate, ux3), BLOCKIO_SIG, 22, 9, 2, 28, 0 },

  { 15, "studenttemplate/Inputs from LabVIEW/ctrl1/Ki/[3x3]", 0, "", offsetof
    (BlockIO_StudentTemplate, ux3_g), BLOCKIO_SIG, 22, 9, 2, 30, 0 },

  { 16, "studenttemplate/Inputs from LabVIEW/ctrl1/Kp/[3x3]", 0, "", offsetof
    (BlockIO_StudentTemplate, ux3_h), BLOCKIO_SIG, 22, 9, 2, 32, 0 },

  { 17, "studenttemplate/Inputs from LabVIEW/ctrl2/Gamma_q/[2x2]", 0, "",
    offsetof(BlockIO_StudentTemplate, ux2), BLOCKIO_SIG, 24, 4, 2, 34, 0 },

  { 18, "studenttemplate/Inputs from LabVIEW/ctrl2/Initial q_x", 0, "", offsetof
    (BlockIO_StudentTemplate, Initialq_x), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "studenttemplate/Inputs from LabVIEW/ctrl2/Initial q_y", 0, "", offsetof
    (BlockIO_StudentTemplate, Initialq_y), BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "studenttemplate/Inputs from LabVIEW/ctrl2/Initial s", 0, "", offsetof
    (BlockIO_StudentTemplate, Initials), BLOCKIO_SIG, 0, 1, 2, 40, 0 },

  { 21, "studenttemplate/Inputs from LabVIEW/ctrl2/K_d/[3x3]", 0, "", offsetof
    (BlockIO_StudentTemplate, ux3_e), BLOCKIO_SIG, 22, 9, 2, 42, 0 },

  { 22, "studenttemplate/Inputs from LabVIEW/ctrl2/K_i/[3x3]", 0, "", offsetof
    (BlockIO_StudentTemplate, ux3_b), BLOCKIO_SIG, 22, 9, 2, 44, 0 },

  { 23, "studenttemplate/Inputs from LabVIEW/ctrl2/K_p/[3x3]", 0, "", offsetof
    (BlockIO_StudentTemplate, ux3_he), BLOCKIO_SIG, 22, 9, 2, 46, 0 },

  { 24,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1",
    0, "", offsetof(BlockIO_StudentTemplate, l_x1), BLOCKIO_SIG, 0, 1, 2, 48, 0
  },

  { 25,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2",
    0, "", offsetof(BlockIO_StudentTemplate, l_x2), BLOCKIO_SIG, 0, 1, 2, 50, 0
  },

  { 26,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2",
    0, "", offsetof(BlockIO_StudentTemplate, l_y2), BLOCKIO_SIG, 0, 1, 2, 52, 0
  },

  { 27,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/3x5",
    0, "", offsetof(BlockIO_StudentTemplate, x5), BLOCKIO_SIG, 26, 15, 2, 54, 0
  },

  { 28,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r",
    0, "", offsetof(BlockIO_StudentTemplate, N_r), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v",
    0, "", offsetof(BlockIO_StudentTemplate, N_v), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u",
    0, "", offsetof(BlockIO_StudentTemplate, X_u), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v",
    0, "", offsetof(BlockIO_StudentTemplate, Y_v), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr",
    0, "", offsetof(BlockIO_StudentTemplate, Y_vr), BLOCKIO_SIG, 0, 1, 2, 64, 0
  },

  { 33,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Linear Dampning matrix",
    0, "", offsetof(BlockIO_StudentTemplate, LinearDampningmatrix), BLOCKIO_SIG,
    22, 9, 2, 66, 0 },

  { 34,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_11",
    0, "", offsetof(BlockIO_StudentTemplate, M_11), BLOCKIO_SIG, 0, 1, 2, 68, 0
  },

  { 35,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_22",
    0, "", offsetof(BlockIO_StudentTemplate, M_22), BLOCKIO_SIG, 0, 1, 2, 70, 0
  },

  { 36,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m x_g",
    0, "", offsetof(BlockIO_StudentTemplate, mx_g), BLOCKIO_SIG, 0, 1, 2, 72, 0
  },

  { 37,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_32",
    0, "", offsetof(BlockIO_StudentTemplate, M_32), BLOCKIO_SIG, 0, 1, 2, 74, 0
  },

  { 38,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_23",
    0, "", offsetof(BlockIO_StudentTemplate, M_23), BLOCKIO_SIG, 0, 1, 2, 76, 0
  },

  { 39,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_33",
    0, "", offsetof(BlockIO_StudentTemplate, M_33), BLOCKIO_SIG, 0, 1, 2, 78, 0
  },

  { 40,
    "studenttemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/3x3",
    0, "", offsetof(BlockIO_StudentTemplate, x3), BLOCKIO_SIG, 22, 9, 2, 80, 0 },

  { 41,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1",
    0, "", offsetof(BlockIO_StudentTemplate, l_x1_m), BLOCKIO_SIG, 0, 1, 2, 82,
    0 },

  { 42,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2",
    0, "", offsetof(BlockIO_StudentTemplate, l_y2_a), BLOCKIO_SIG, 0, 1, 2, 84,
    0 },

  { 43,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2",
    0, "", offsetof(BlockIO_StudentTemplate, l_x2_l), BLOCKIO_SIG, 0, 1, 2, 86,
    0 },

  { 44,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/3x5",
    0, "", offsetof(BlockIO_StudentTemplate, x5_i), BLOCKIO_SIG, 26, 15, 2, 88,
    0 },

  { 45, "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_1", 0,
    "u_1", offsetof(BlockIO_StudentTemplate, u_1), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1",
    0, "", offsetof(BlockIO_StudentTemplate, u_1tof_1), BLOCKIO_SIG, 0, 1, 2, 92,
    0 },

  { 47, "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_2", 0,
    "u_2", offsetof(BlockIO_StudentTemplate, u_2), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2",
    0, "", offsetof(BlockIO_StudentTemplate, u_2tof_2), BLOCKIO_SIG, 0, 1, 2, 96,
    0 },

  { 49, "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_3", 0,
    "u_3", offsetof(BlockIO_StudentTemplate, u_3), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3",
    0, "", offsetof(BlockIO_StudentTemplate, u_3tof_3), BLOCKIO_SIG, 0, 1, 2,
    100, 0 },

  { 51, "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_4", 0,
    "u_4", offsetof(BlockIO_StudentTemplate, u_4), BLOCKIO_SIG, 0, 1, 2, 102, 0
  },

  { 52,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4",
    0, "", offsetof(BlockIO_StudentTemplate, u_4tof_4), BLOCKIO_SIG, 0, 1, 2,
    104, 0 },

  { 53, "studenttemplate/Main Subsystems/Control/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_StudentTemplate,
    BowThrusterdirection), BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "studenttemplate/Main Subsystems/Control/PS3 u input control/PS3 u_5", 0,
    "u_5", offsetof(BlockIO_StudentTemplate, u_5), BLOCKIO_SIG, 0, 1, 2, 108, 0
  },

  { 55,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5",
    0, "", offsetof(BlockIO_StudentTemplate, u_5tof_5), BLOCKIO_SIG, 0, 1, 2,
    110, 0 },

  { 56,
    "studenttemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product), BLOCKIO_SIG, 20, 3, 2,
    112, 0 },

  { 57, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In", 0,
    "", offsetof(BlockIO_StudentTemplate, QTMIn), BLOCKIO_SIG, 50, 9, 2, 114, 0
  },

  { 58,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn3xcoordmm), BLOCKIO_SIG, 31, 1,
    2, 116, 0 },

  { 59, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m x", 0,
    "", offsetof(BlockIO_StudentTemplate, mm2mx), BLOCKIO_SIG, 31, 1, 2, 118, 0
  },

  { 60,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn4ycoordmm), BLOCKIO_SIG, 31, 1,
    2, 120, 0 },

  { 61, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m y", 0,
    "", offsetof(BlockIO_StudentTemplate, mm2my), BLOCKIO_SIG, 31, 1, 2, 122, 0
  },

  { 62,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn6yawdeg), BLOCKIO_SIG, 31, 1,
    2, 124, 0 },

  { 63, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r yaw", 0,
    "", offsetof(BlockIO_StudentTemplate, d2ryaw), BLOCKIO_SIG, 31, 1, 2, 126, 0
  },

  { 64,
    "studenttemplate/Main Subsystems/Naviagation/Navigation Switch/eta Switch",
    0, "", offsetof(BlockIO_StudentTemplate, etaSwitch), BLOCKIO_SIG, 20, 3, 2,
    128, 0 },

  { 65, "studenttemplate/Main Subsystems/Control/DP control/yaw angle", 0, "psi",
    offsetof(BlockIO_StudentTemplate, psi), BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation), BLOCKIO_SIG, 0, 1, 2,
    132, 0 },

  { 67,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign), BLOCKIO_SIG, 0, 1, 2, 134, 0
  },

  { 68,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain), BLOCKIO_SIG, 0, 1, 2, 136, 0
  },

  { 69,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1), BLOCKIO_SIG, 0, 1, 2, 138, 0
  },

  { 70,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction), BLOCKIO_SIG, 0, 1, 2,
    140, 0 },

  { 71,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum), BLOCKIO_SIG, 0, 1, 2, 142, 0
  },

  { 72, "studenttemplate/Main Subsystems/Control/DP control/Sum2", 0, "",
    offsetof(BlockIO_StudentTemplate, Sum2), BLOCKIO_SIG, 20, 3, 2, 144, 0 },

  { 73,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_l), BLOCKIO_SIG, 0, 1, 2,
    146, 0 },

  { 74,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_b), BLOCKIO_SIG, 0, 1, 2, 148,
    0 },

  { 75,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_n), BLOCKIO_SIG, 0, 1, 2, 150,
    0 },

  { 76,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_c), BLOCKIO_SIG, 0, 1, 2, 152,
    0 },

  { 77,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_e), BLOCKIO_SIG, 0, 1,
    2, 154, 0 },

  { 78,
    "studenttemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_m), BLOCKIO_SIG, 0, 1, 2, 156,
    0 },

  { 79,
    "studenttemplate/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_StudentTemplate, Row1), BLOCKIO_SIG, 0, 1, 2, 158, 0
  },

  { 80,
    "studenttemplate/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_StudentTemplate, Row2), BLOCKIO_SIG, 0, 1, 2, 160, 0
  },

  { 81,
    "studenttemplate/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_StudentTemplate, Row3), BLOCKIO_SIG, 0, 1, 2, 162, 0
  },

  { 82, "studenttemplate/Main Subsystems/Control/DP control/Product", 0, "",
    offsetof(BlockIO_StudentTemplate, Product_m), BLOCKIO_SIG, 20, 3, 2, 164, 0
  },

  { 83, "studenttemplate/Main Subsystems/Control/DP control/Integrator", 0, "",
    offsetof(BlockIO_StudentTemplate, Integrator), BLOCKIO_SIG, 20, 3, 2, 166, 0
  },

  { 84, "studenttemplate/Main Subsystems/Control/DP control/Product1", 0, "",
    offsetof(BlockIO_StudentTemplate, Product1), BLOCKIO_SIG, 20, 3, 2, 168, 0 },

  { 85, "studenttemplate/Main Subsystems/Control/DP control/Sum3", 0, "",
    offsetof(BlockIO_StudentTemplate, Sum3), BLOCKIO_SIG, 20, 3, 2, 170, 0 },

  { 86,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4",
    0, "nu", offsetof(BlockIO_StudentTemplate, nu), BLOCKIO_SIG, 20, 3, 2, 172,
    0 },

  { 87,
    "studenttemplate/Main Subsystems/Naviagation/Navigation Switch/nu Switch", 0,
    "", offsetof(BlockIO_StudentTemplate, nuSwitch), BLOCKIO_SIG, 20, 3, 2, 174,
    0 },

  { 88, "studenttemplate/Main Subsystems/Control/DP control/Product2", 0, "",
    offsetof(BlockIO_StudentTemplate, Product2), BLOCKIO_SIG, 20, 3, 2, 176, 0 },

  { 89, "studenttemplate/Main Subsystems/Control/DP control/Sum1", 0, "",
    offsetof(BlockIO_StudentTemplate, Sum1_j), BLOCKIO_SIG, 20, 3, 2, 178, 0 },

  { 90, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R11", 0, "",
    offsetof(BlockIO_StudentTemplate, R11), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R21", 0, "",
    offsetof(BlockIO_StudentTemplate, R21), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R12", 0, "",
    offsetof(BlockIO_StudentTemplate, R12), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/-1", 0, "",
    offsetof(BlockIO_StudentTemplate, u), BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R22", 0, "",
    offsetof(BlockIO_StudentTemplate, R22), BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R(psi)", 0, "",
    offsetof(BlockIO_StudentTemplate, Rpsi), BLOCKIO_SIG, 22, 9, 2, 190, 0 },

  { 96, "studenttemplate/Main Subsystems/Control/LgV2/R(psi)/R^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_a), BLOCKIO_SIG, 22, 9,
    2, 192, 0 },

  { 97, "studenttemplate/Main Subsystems/Control/LgV2/zeta/Integrator", 0, "",
    offsetof(BlockIO_StudentTemplate, Integrator_h), BLOCKIO_SIG, 28, 3, 2, 194,
    0 },

  { 98, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Product", 0,
    "", offsetof(BlockIO_StudentTemplate, Product_e), BLOCKIO_SIG, 28, 3, 2, 196,
    0 },

  { 99, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Gain", 0, "",
    offsetof(BlockIO_StudentTemplate, Gain_a), BLOCKIO_SIG, 28, 3, 2, 198, 0 },

  { 100, "studenttemplate/Main Subsystems/Control/LgV2/Control law/4", 0, "",
    offsetof(BlockIO_StudentTemplate, u_h), BLOCKIO_SIG, 0, 1, 2, 200, 0 },

  { 101, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Divide", 0,
    "", offsetof(BlockIO_StudentTemplate, Divide), BLOCKIO_SIG, 0, 1, 2, 202, 0
  },

  { 102, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Add1", 0, "",
    offsetof(BlockIO_StudentTemplate, Add1), BLOCKIO_SIG, 22, 9, 2, 204, 0 },

  { 103, "studenttemplate/Main Subsystems/Control/LgV2/Product1", 0, "",
    offsetof(BlockIO_StudentTemplate, Product1_d), BLOCKIO_SIG, 22, 9, 2, 206, 0
  },

  { 104, "studenttemplate/Main Subsystems/Control/LgV2/Add3", 0, "", offsetof
    (BlockIO_StudentTemplate, Add3), BLOCKIO_SIG, 22, 9, 2, 208, 0 },

  { 105,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_o), BLOCKIO_SIG, 0, 1, 2,
    210, 0 },

  { 106,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_p), BLOCKIO_SIG, 0, 1, 2, 212,
    0 },

  { 107,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_m), BLOCKIO_SIG, 0, 1, 2, 214,
    0 },

  { 108,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_k), BLOCKIO_SIG, 0, 1, 2, 216,
    0 },

  { 109,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_d), BLOCKIO_SIG, 0, 1,
    2, 218, 0 },

  { 110,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_n), BLOCKIO_SIG, 0, 1, 2, 220,
    0 },

  { 111, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Integrator",
    0, "", offsetof(BlockIO_StudentTemplate, Integrator_b), BLOCKIO_SIG, 25, 2,
    2, 222, 0 },

  { 112,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/x_2 - x_1",
    0, "", offsetof(BlockIO_StudentTemplate, x_2x_1), BLOCKIO_SIG, 0, 1, 2, 224,
    0 },

  { 113,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/y_2 - y_1",
    0, "", offsetof(BlockIO_StudentTemplate, y_2y_1), BLOCKIO_SIG, 0, 1, 2, 226,
    0 },

  { 114,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_d), BLOCKIO_SIG, 0, 1, 2,
    228, 0 },

  { 115,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Rounding Function",
    0, "", offsetof(BlockIO_StudentTemplate, RoundingFunction), BLOCKIO_SIG, 0,
    1, 2, 230, 0 },

  { 116,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_n), BLOCKIO_SIG, 25, 2, 2,
    232, 0 },

  { 117, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Integrator1",
    0, "", offsetof(BlockIO_StudentTemplate, Integrator1), BLOCKIO_SIG, 0, 1, 2,
    234, 0 },

  { 118,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_j), BLOCKIO_SIG, 0, 1, 2,
    236, 0 },

  { 119,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/sin(s)",
    0, "", offsetof(BlockIO_StudentTemplate, sins), BLOCKIO_SIG, 0, 1, 2, 238, 0
  },

  { 120,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_b), BLOCKIO_SIG, 0, 1, 2,
    240, 0 },

  { 121,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_mx), BLOCKIO_SIG, 0, 1, 2, 242,
    0 },

  { 122,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/cos(s)",
    0, "", offsetof(BlockIO_StudentTemplate, coss), BLOCKIO_SIG, 0, 1, 2, 244, 0
  },

  { 123,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_a), BLOCKIO_SIG, 0, 1, 2,
    246, 0 },

  { 124,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Subract",
    0, "", offsetof(BlockIO_StudentTemplate, Subract), BLOCKIO_SIG, 0, 1, 2, 248,
    0 },

  { 125,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_m), BLOCKIO_SIG, 25, 2, 2,
    250, 0 },

  { 126,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add), BLOCKIO_SIG, 25, 2, 2, 252, 0
  },

  { 127,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/Trigonometric Function",
    0, "", offsetof(BlockIO_StudentTemplate, TrigonometricFunction), BLOCKIO_SIG,
    0, 1, 2, 254, 0 },

  { 128,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_c), BLOCKIO_SIG, 0, 1, 2,
    256, 0 },

  { 129,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_m), BLOCKIO_SIG, 0, 1, 2, 258,
    0 },

  { 130,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_c), BLOCKIO_SIG, 0, 1, 2, 260,
    0 },

  { 131,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_l), BLOCKIO_SIG, 0, 1, 2, 262,
    0 },

  { 132,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_dh), BLOCKIO_SIG, 0, 1,
    2, 264, 0 },

  { 133,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_b), BLOCKIO_SIG, 0, 1, 2, 266,
    0 },

  { 134,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_n), BLOCKIO_SIG, 0, 1, 2,
    268, 0 },

  { 135,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_g), BLOCKIO_SIG, 0, 1, 2, 270,
    0 },

  { 136,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_k), BLOCKIO_SIG, 0, 1, 2, 272,
    0 },

  { 137,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_j4), BLOCKIO_SIG, 0, 1, 2, 274,
    0 },

  { 138,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_j), BLOCKIO_SIG, 0, 1,
    2, 276, 0 },

  { 139,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_i), BLOCKIO_SIG, 0, 1, 2, 278,
    0 },

  { 140,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_h), BLOCKIO_SIG, 24, 4,
    2, 280, 0 },

  { 141,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/x_2 - x_1",
    0, "", offsetof(BlockIO_StudentTemplate, x_2x_1_e), BLOCKIO_SIG, 0, 1, 2,
    282, 0 },

  { 142,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s",
    0, "", offsetof(BlockIO_StudentTemplate, x_2x_1s), BLOCKIO_SIG, 0, 1, 2, 284,
    0 },

  { 143,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s + x_1",
    0, "", offsetof(BlockIO_StudentTemplate, x_2x_1sx_1), BLOCKIO_SIG, 0, 1, 2,
    286, 0 },

  { 144,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/y_2 - y_1",
    0, "", offsetof(BlockIO_StudentTemplate, y_2y_1_j), BLOCKIO_SIG, 0, 1, 2,
    288, 0 },

  { 145,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s",
    0, "", offsetof(BlockIO_StudentTemplate, y_2y_1s), BLOCKIO_SIG, 0, 1, 2, 290,
    0 },

  { 146,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s + y_1",
    0, "", offsetof(BlockIO_StudentTemplate, y_2y_1sy_1), BLOCKIO_SIG, 0, 1, 2,
    292, 0 },

  { 147,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_mq), BLOCKIO_SIG, 25, 2, 2,
    294, 0 },

  { 148,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_l), BLOCKIO_SIG, 0, 1, 2,
    296, 0 },

  { 149,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/cos(s)",
    0, "", offsetof(BlockIO_StudentTemplate, coss_n), BLOCKIO_SIG, 0, 1, 2, 298,
    0 },

  { 150,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_c), BLOCKIO_SIG, 0, 1, 2,
    300, 0 },

  { 151,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_i), BLOCKIO_SIG, 0, 1, 2, 302,
    0 },

  { 152,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/sin(s)",
    0, "", offsetof(BlockIO_StudentTemplate, sins_o), BLOCKIO_SIG, 0, 1, 2, 304,
    0 },

  { 153,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_h), BLOCKIO_SIG, 0, 1, 2,
    306, 0 },

  { 154,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add1",
    0, "", offsetof(BlockIO_StudentTemplate, Add1_i), BLOCKIO_SIG, 0, 1, 2, 308,
    0 },

  { 155,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Subract",
    0, "", offsetof(BlockIO_StudentTemplate, Subract_a), BLOCKIO_SIG, 0, 1, 2,
    310, 0 },

  { 156,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_f), BLOCKIO_SIG, 25, 2, 2,
    312, 0 },

  { 157,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_n), BLOCKIO_SIG, 25, 2, 2, 314,
    0 },

  { 158,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch",
    0, "", offsetof(BlockIO_StudentTemplate, Switch), BLOCKIO_SIG, 0, 1, 2, 316,
    0 },

  { 159,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch2",
    0, "", offsetof(BlockIO_StudentTemplate, Switch2), BLOCKIO_SIG, 0, 1, 2, 318,
    0 },

  { 160,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch",
    0, "", offsetof(BlockIO_StudentTemplate, Switch_e), BLOCKIO_SIG, 0, 1, 2,
    320, 0 },

  { 161,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch2",
    0, "", offsetof(BlockIO_StudentTemplate, Switch2_j), BLOCKIO_SIG, 0, 1, 2,
    322, 0 },

  { 162,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Subtract",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract), BLOCKIO_SIG, 25, 2, 2,
    324, 0 },

  { 163,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon), BLOCKIO_SIG, 25, 2, 2,
    326, 0 },

  { 164,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSelector), BLOCKIO_SIG, 31,
    1, 2, 328, 0 },

  { 165,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Trigonometric Function",
    0, "", offsetof(BlockIO_StudentTemplate, TrigonometricFunction_i),
    BLOCKIO_SIG, 31, 1, 2, 330, 0 },

  { 166,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_i), BLOCKIO_SIG, 31, 1,
    2, 332, 0 },

  { 167,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_k), BLOCKIO_SIG, 31, 1, 2, 334,
    0 },

  { 168,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_g), BLOCKIO_SIG, 31, 1, 2, 336,
    0 },

  { 169,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_h), BLOCKIO_SIG, 31, 1, 2, 338,
    0 },

  { 170,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_e4), BLOCKIO_SIG, 31,
    1, 2, 340, 0 },

  { 171,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_e), BLOCKIO_SIG, 31, 1, 2, 342,
    0 },

  { 172,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Subtract",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract_h), BLOCKIO_SIG, 0, 1, 2,
    344, 0 },

  { 173,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_e), BLOCKIO_SIG, 0, 1, 2,
    346, 0 },

  { 174,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_f), BLOCKIO_SIG, 0, 1, 2, 348,
    0 },

  { 175,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_d), BLOCKIO_SIG, 0, 1, 2, 350,
    0 },

  { 176,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_g), BLOCKIO_SIG, 0, 1, 2, 352,
    0 },

  { 177,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_eb), BLOCKIO_SIG, 0, 1,
    2, 354, 0 },

  { 178,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_ip), BLOCKIO_SIG, 0, 1, 2, 356,
    0 },

  { 179,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, VectorConcatenate), BLOCKIO_SIG, 20,
    3, 2, 358, 0 },

  { 180, "studenttemplate/Main Subsystems/Control/LgV2/z_1/Subtract", 0, "",
    offsetof(BlockIO_StudentTemplate, Subtract_e), BLOCKIO_SIG, 20, 3, 2, 360, 0
  },

  { 181,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_g), BLOCKIO_SIG, 0, 1, 2,
    362, 0 },

  { 182,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_a), BLOCKIO_SIG, 0, 1, 2, 364,
    0 },

  { 183,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_j), BLOCKIO_SIG, 0, 1, 2, 366,
    0 },

  { 184,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_cz), BLOCKIO_SIG, 0, 1, 2, 368,
    0 },

  { 185,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_f), BLOCKIO_SIG, 0, 1,
    2, 370, 0 },

  { 186,
    "studenttemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_g), BLOCKIO_SIG, 0, 1, 2, 372,
    0 },

  { 187, "studenttemplate/Main Subsystems/Control/LgV2/z_1/Product", 0, "",
    offsetof(BlockIO_StudentTemplate, Product_bx), BLOCKIO_SIG, 20, 3, 2, 374, 0
  },

  { 188, "studenttemplate/Main Subsystems/Control/LgV2/alpha/Product1", 0, "",
    offsetof(BlockIO_StudentTemplate, Product1_l), BLOCKIO_SIG, 20, 3, 2, 376, 0
  },

  { 189,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qx",
    0, "", offsetof(BlockIO_StudentTemplate, f_qx), BLOCKIO_SIG, 0, 1, 2, 378, 0
  },

  { 190,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qy",
    0, "", offsetof(BlockIO_StudentTemplate, f_qy), BLOCKIO_SIG, 0, 1, 2, 380, 0
  },

  { 191,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_i), BLOCKIO_SIG, 25, 2, 2,
    382, 0 },

  { 192,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2), BLOCKIO_SIG, 0, 1, 2, 384,
    0 },

  { 193,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2), BLOCKIO_SIG, 31, 1, 2,
    386, 0 },

  { 194,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_g), BLOCKIO_SIG, 31, 1, 2, 388,
    0 },

  { 195,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_b), BLOCKIO_SIG, 31, 1, 2,
    390, 0 },

  { 196,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector1",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSelector1), BLOCKIO_SIG,
    29, 2, 2, 392, 0 },

  { 197,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_a), BLOCKIO_SIG, 29, 2, 2,
    394, 0 },

  { 198,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1",
    0, "", offsetof(BlockIO_StudentTemplate, u_m), BLOCKIO_SIG, 29, 2, 2, 396, 0
  },

  { 199,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, VectorConcatenate_e), BLOCKIO_SIG,
    20, 3, 2, 398, 0 },

  { 200,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_g), BLOCKIO_SIG, 32, 2, 2,
    400, 0 },

  { 201,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_ld), BLOCKIO_SIG, 0, 1, 2,
    402, 0 },

  { 202,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/cos(s)",
    0, "", offsetof(BlockIO_StudentTemplate, coss_l), BLOCKIO_SIG, 0, 1, 2, 404,
    0 },

  { 203,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_o), BLOCKIO_SIG, 0, 1,
    2, 406, 0 },

  { 204,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_p), BLOCKIO_SIG, 0, 1, 2,
    408, 0 },

  { 205,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_m4), BLOCKIO_SIG, 0, 1, 2, 410,
    0 },

  { 206,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/sin(s)",
    0, "", offsetof(BlockIO_StudentTemplate, sins_h), BLOCKIO_SIG, 0, 1, 2, 412,
    0 },

  { 207,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_l1), BLOCKIO_SIG, 0, 1, 2,
    414, 0 },

  { 208,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1",
    0, "", offsetof(BlockIO_StudentTemplate, Gain1_e), BLOCKIO_SIG, 0, 1, 2, 416,
    0 },

  { 209,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Subract",
    0, "", offsetof(BlockIO_StudentTemplate, Subract_c), BLOCKIO_SIG, 0, 1, 2,
    418, 0 },

  { 210,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_l4), BLOCKIO_SIG, 25, 2, 2,
    420, 0 },

  { 211,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_nm), BLOCKIO_SIG, 32, 2, 2, 422,
    0 },

  { 212,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_StudentTemplate, x_dsy_ds2), BLOCKIO_SIG, 31, 1, 2,
    424, 0 },

  { 213,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s^2 + y_d^s",
    0, "", offsetof(BlockIO_StudentTemplate, x_ds2y_ds), BLOCKIO_SIG, 31, 1, 2,
    426, 0 },

  { 214,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s + y_d^s^2 ) - ( x_d^s^2 + y_d^s )",
    0, "", offsetof(BlockIO_StudentTemplate, x_dsy_ds2x_ds2y_ds), BLOCKIO_SIG,
    31, 1, 2, 428, 0 },

  { 215,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2",
    0, "", offsetof(BlockIO_StudentTemplate, x_ds2), BLOCKIO_SIG, 0, 1, 2, 430,
    0 },

  { 216,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( y_d^s )^2",
    0, "", offsetof(BlockIO_StudentTemplate, y_ds2), BLOCKIO_SIG, 0, 1, 2, 432,
    0 },

  { 217,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2 + ( y_d^s )^2",
    0, "", offsetof(BlockIO_StudentTemplate, x_ds2y_ds2), BLOCKIO_SIG, 0, 1, 2,
    434, 0 },

  { 218,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_j), BLOCKIO_SIG, 31, 1, 2,
    436, 0 },

  { 219,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2_p), BLOCKIO_SIG, 0, 1, 2,
    438, 0 },

  { 220,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2_p), BLOCKIO_SIG, 31, 1,
    2, 440, 0 },

  { 221,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_nu), BLOCKIO_SIG, 31, 1, 2, 442,
    0 },

  { 222,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_p), BLOCKIO_SIG, 31, 1, 2,
    444, 0 },

  { 223,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_c), BLOCKIO_SIG, 24, 4,
    2, 446, 0 },

  { 224,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_j), BLOCKIO_SIG, 25, 2, 2,
    448, 0 },

  { 225,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_j), BLOCKIO_SIG, 25, 2, 2,
    450, 0 },

  { 226,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Subtract1",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract1), BLOCKIO_SIG, 25, 2, 2,
    452, 0 },

  { 227,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector2",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSelector2), BLOCKIO_SIG,
    31, 1, 2, 454, 0 },

  { 228,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_i5), BLOCKIO_SIG, 31, 1, 2,
    456, 0 },

  { 229,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Subtract",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract_n), BLOCKIO_SIG, 31, 1, 2,
    458, 0 },

  { 230,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2_o), BLOCKIO_SIG, 31, 1,
    2, 460, 0 },

  { 231,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2_l), BLOCKIO_SIG, 0, 1, 2,
    462, 0 },

  { 232,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_o), BLOCKIO_SIG, 31, 1, 2, 464,
    0 },

  { 233,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/sqrt",
    0, "", offsetof(BlockIO_StudentTemplate, sqrt_i), BLOCKIO_SIG, 31, 1, 2, 466,
    0 },

  { 234,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_l), BLOCKIO_SIG, 31, 1, 2,
    468, 0 },

  { 235,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_l), BLOCKIO_SIG, 29, 2,
    2, 470, 0 },

  { 236,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_nk), BLOCKIO_SIG, 0, 1, 2,
    472, 0 },

  { 237,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_StudentTemplate, sqrt_d), BLOCKIO_SIG, 0, 1, 2, 474,
    0 },

  { 238,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_n4), BLOCKIO_SIG, 0, 1, 2,
    476, 0 },

  { 239,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_p), BLOCKIO_SIG, 29, 2,
    2, 478, 0 },

  { 240,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_jp), BLOCKIO_SIG, 0, 1, 2,
    480, 0 },

  { 241,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_StudentTemplate, sqrt_e), BLOCKIO_SIG, 0, 1, 2, 482,
    0 },

  { 242,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Subract",
    0, "", offsetof(BlockIO_StudentTemplate, Subract_ab), BLOCKIO_SIG, 0, 1, 2,
    484, 0 },

  { 243,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_p), BLOCKIO_SIG, 0, 1, 2,
    486, 0 },

  { 244,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_b), BLOCKIO_SIG, 0, 1, 2, 488,
    0 },

  { 245,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_bz), BLOCKIO_SIG, 0, 1, 2,
    490, 0 },

  { 246,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_l), BLOCKIO_SIG, 0, 1, 2,
    492, 0 },

  { 247,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_jv), BLOCKIO_SIG, 29,
    2, 2, 494, 0 },

  { 248,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_lw), BLOCKIO_SIG, 29, 2, 2,
    496, 0 },

  { 249,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_cl), BLOCKIO_SIG, 0, 1, 2,
    498, 0 },

  { 250,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_h), BLOCKIO_SIG, 0, 1, 2, 500,
    0 },

  { 251,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Subtract",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract_f), BLOCKIO_SIG, 0, 1, 2,
    502, 0 },

  { 252,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, VectorConcatenate_f), BLOCKIO_SIG,
    28, 3, 2, 504, 0 },

  { 253, "studenttemplate/Main Subsystems/Control/LgV2/alpha/Add", 0, "",
    offsetof(BlockIO_StudentTemplate, Add_iy), BLOCKIO_SIG, 28, 3, 2, 506, 0 },

  { 254, "studenttemplate/Main Subsystems/Control/LgV2/alpha/Product2", 0, "",
    offsetof(BlockIO_StudentTemplate, Product2_o), BLOCKIO_SIG, 28, 3, 2, 508, 0
  },

  { 255, "studenttemplate/Main Subsystems/Control/LgV2/alpha/Sum", 0, "",
    offsetof(BlockIO_StudentTemplate, Sum_o), BLOCKIO_SIG, 28, 3, 2, 510, 0 },

  { 256, "studenttemplate/Main Subsystems/Control/LgV2/z_2/Subtract", 0, "",
    offsetof(BlockIO_StudentTemplate, Subtract_n5), BLOCKIO_SIG, 28, 3, 2, 512,
    0 },

  { 257, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Product1", 0,
    "", offsetof(BlockIO_StudentTemplate, Product1_i), BLOCKIO_SIG, 28, 3, 2,
    514, 0 },

  { 258, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Gain1", 0, "",
    offsetof(BlockIO_StudentTemplate, Gain1_j), BLOCKIO_SIG, 28, 3, 2, 516, 0 },

  { 259, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Product2", 0,
    "", offsetof(BlockIO_StudentTemplate, Product2_g), BLOCKIO_SIG, 20, 3, 2,
    518, 0 },

  { 260, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12", 0,
    "", offsetof(BlockIO_StudentTemplate, S12), BLOCKIO_SIG, 0, 1, 2, 520, 0 },

  { 261, "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S(r)", 0,
    "", offsetof(BlockIO_StudentTemplate, Sr), BLOCKIO_SIG, 22, 9, 2, 522, 0 },

  { 262,
    "studenttemplate/Main Subsystems/Control/LgV2/sigma/S^T/S^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_jw), BLOCKIO_SIG, 22,
    9, 2, 524, 0 },

  { 263, "studenttemplate/Main Subsystems/Control/LgV2/sigma/Product", 0, "",
    offsetof(BlockIO_StudentTemplate, Product_f), BLOCKIO_SIG, 20, 3, 2, 526, 0
  },

  { 264, "studenttemplate/Main Subsystems/Control/LgV2/sigma/Add", 0, "",
    offsetof(BlockIO_StudentTemplate, Add_k), BLOCKIO_SIG, 20, 3, 2, 528, 0 },

  { 265, "studenttemplate/Main Subsystems/Control/LgV2/sigma/Product2", 0, "",
    offsetof(BlockIO_StudentTemplate, Product2_f), BLOCKIO_SIG, 20, 3, 2, 530, 0
  },

  { 266, "studenttemplate/Main Subsystems/Control/LgV2/sigma/Add1", 0, "",
    offsetof(BlockIO_StudentTemplate, Add1_k), BLOCKIO_SIG, 28, 3, 2, 532, 0 },

  { 267, "studenttemplate/Main Subsystems/Control/LgV2/sigma/Product3", 0, "",
    offsetof(BlockIO_StudentTemplate, Product3), BLOCKIO_SIG, 28, 3, 2, 534, 0 },

  { 268,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function",
    0, "", offsetof(BlockIO_StudentTemplate, TrigonometricFunction_p),
    BLOCKIO_SIG, 0, 1, 2, 536, 0 },

  { 269,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_StudentTemplate, TrigonometricFunction1),
    BLOCKIO_SIG, 0, 1, 2, 538, 0 },

  { 270,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/Derivative",
    0, "", offsetof(BlockIO_StudentTemplate, Derivative), BLOCKIO_SIG, 0, 1, 2,
    540, 0 },

  { 271,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_ir), BLOCKIO_SIG, 25, 2, 2,
    542, 0 },

  { 272,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, VectorConcatenate_c), BLOCKIO_SIG,
    20, 3, 2, 544, 0 },

  { 273,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2_n), BLOCKIO_SIG, 31, 1,
    2, 546, 0 },

  { 274,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2_e), BLOCKIO_SIG, 0, 1, 2,
    548, 0 },

  { 275,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_m), BLOCKIO_SIG, 31, 1, 2, 550,
    0 },

  { 276,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/sqrt",
    0, "", offsetof(BlockIO_StudentTemplate, sqrt_f), BLOCKIO_SIG, 31, 1, 2, 552,
    0 },

  { 277,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_be), BLOCKIO_SIG, 31, 1, 2,
    554, 0 },

  { 278,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_i), BLOCKIO_SIG, 0, 1, 2,
    556, 0 },

  { 279,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_f5), BLOCKIO_SIG, 0, 1, 2,
    558, 0 },

  { 280,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, VectorConcatenate_o), BLOCKIO_SIG,
    28, 3, 2, 560, 0 },

  { 281, "studenttemplate/Main Subsystems/Control/LgV2/sigma/Add2", 0, "",
    offsetof(BlockIO_StudentTemplate, Add2), BLOCKIO_SIG, 28, 3, 2, 562, 0 },

  { 282, "studenttemplate/Main Subsystems/Control/LgV2/sigma/Product4", 0, "",
    offsetof(BlockIO_StudentTemplate, Product4), BLOCKIO_SIG, 28, 3, 2, 564, 0 },

  { 283, "studenttemplate/Main Subsystems/Control/LgV2/sigma/Sum", 0, "",
    offsetof(BlockIO_StudentTemplate, Sum_io), BLOCKIO_SIG, 28, 3, 2, 566, 0 },

  { 284, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Product4", 0,
    "", offsetof(BlockIO_StudentTemplate, Product4_p), BLOCKIO_SIG, 28, 3, 2,
    568, 0 },

  { 285,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Matrix Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, MatrixConcatenate), BLOCKIO_SIG, 30,
    6, 2, 570, 0 },

  { 286, "studenttemplate/Main Subsystems/Control/LgV2/alpha^q/Product3", 0, "",
    offsetof(BlockIO_StudentTemplate, Product3_b), BLOCKIO_SIG, 30, 6, 2, 572, 0
  },

  { 287,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_StudentTemplate, TrigonometricFunction1_h),
    BLOCKIO_SIG, 0, 1, 2, 574, 0 },

  { 288,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_o), BLOCKIO_SIG, 0, 1, 2, 576,
    0 },

  { 289,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_b), BLOCKIO_SIG, 29, 2, 2,
    578, 0 },

  { 290,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function",
    0, "", offsetof(BlockIO_StudentTemplate, TrigonometricFunction_k),
    BLOCKIO_SIG, 0, 1, 2, 580, 0 },

  { 291,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_d), BLOCKIO_SIG, 29, 2, 2,
    582, 0 },

  { 292,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, MatrixConcatenate_d), BLOCKIO_SIG,
    24, 4, 2, 584, 0 },

  { 293,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_f4), BLOCKIO_SIG, 24, 4, 2,
    586, 0 },

  { 294,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_b), BLOCKIO_SIG, 29, 2,
    2, 588, 0 },

  { 295,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_h), BLOCKIO_SIG, 31, 1, 2,
    590, 0 },

  { 296,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_es), BLOCKIO_SIG, 32,
    2, 2, 592, 0 },

  { 297,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product3",
    0, "", offsetof(BlockIO_StudentTemplate, Product3_e), BLOCKIO_SIG, 24, 4, 2,
    594, 0 },

  { 298,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product4",
    0, "", offsetof(BlockIO_StudentTemplate, Product4_pk), BLOCKIO_SIG, 24, 4, 2,
    596, 0 },

  { 299,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2",
    0, "", offsetof(BlockIO_StudentTemplate, u_e), BLOCKIO_SIG, 24, 4, 2, 598, 0
  },

  { 300,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2_h), BLOCKIO_SIG, 0, 1, 2,
    600, 0 },

  { 301,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2_m), BLOCKIO_SIG, 31, 1,
    2, 602, 0 },

  { 302,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_l), BLOCKIO_SIG, 31, 1, 2, 604,
    0 },

  { 303,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/( )^2",
    0, "", offsetof(BlockIO_StudentTemplate, u_g), BLOCKIO_SIG, 31, 1, 2, 606, 0
  },

  { 304,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_d), BLOCKIO_SIG, 24, 4, 2,
    608, 0 },

  { 305,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_li), BLOCKIO_SIG, 24, 4, 2,
    610, 0 },

  { 306,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide1",
    0, "", offsetof(BlockIO_StudentTemplate, Divide1), BLOCKIO_SIG, 24, 4, 2,
    612, 0 },

  { 307,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Subtract",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract_o), BLOCKIO_SIG, 24, 4, 2,
    614, 0 },

  { 308,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_cd), BLOCKIO_SIG, 24,
    4, 2, 616, 0 },

  { 309,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_ga), BLOCKIO_SIG, 29, 2, 2,
    618, 0 },

  { 310,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_ii), BLOCKIO_SIG, 29, 2, 2,
    620, 0 },

  { 311,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_h), BLOCKIO_SIG, 29, 2, 2, 622,
    0 },

  { 312,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, MatrixConcatenate_k), BLOCKIO_SIG,
    30, 6, 2, 624, 0 },

  { 313,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_iz), BLOCKIO_SIG, 29, 2, 2,
    626, 0 },

  { 314,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2",
    0, "", offsetof(BlockIO_StudentTemplate, u_f), BLOCKIO_SIG, 29, 2, 2, 628, 0
  },

  { 315,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2_g), BLOCKIO_SIG, 0, 1, 2,
    630, 0 },

  { 316,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2_o1), BLOCKIO_SIG, 31, 1,
    2, 632, 0 },

  { 317,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_nf), BLOCKIO_SIG, 31, 1, 2, 634,
    0 },

  { 318,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/( )^2",
    0, "", offsetof(BlockIO_StudentTemplate, u_ey), BLOCKIO_SIG, 31, 1, 2, 636,
    0 },

  { 319,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_o), BLOCKIO_SIG, 29, 2, 2,
    638, 0 },

  { 320,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_mv), BLOCKIO_SIG, 24, 4, 2,
    640, 0 },

  { 321,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector3",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSelector3), BLOCKIO_SIG,
    29, 2, 2, 642, 0 },

  { 322,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_bq), BLOCKIO_SIG, 29, 2, 2,
    644, 0 },

  { 323,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide1",
    0, "", offsetof(BlockIO_StudentTemplate, Divide1_p), BLOCKIO_SIG, 29, 2, 2,
    646, 0 },

  { 324,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Subtract",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract_b), BLOCKIO_SIG, 29, 2, 2,
    648, 0 },

  { 325,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_l2), BLOCKIO_SIG, 29, 2, 2,
    650, 0 },

  { 326,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_k), BLOCKIO_SIG, 29, 2, 2,
    652, 0 },

  { 327,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2_m5), BLOCKIO_SIG, 31, 1,
    2, 654, 0 },

  { 328,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2_o), BLOCKIO_SIG, 0, 1, 2,
    656, 0 },

  { 329,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_ba), BLOCKIO_SIG, 31, 1, 2, 658,
    0 },

  { 330,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/^3//2",
    0, "", offsetof(BlockIO_StudentTemplate, u2), BLOCKIO_SIG, 31, 1, 2, 660, 0
  },

  { 331,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_j0), BLOCKIO_SIG, 29, 2, 2,
    662, 0 },

  { 332,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_jh), BLOCKIO_SIG, 29, 2, 2,
    664, 0 },

  { 333,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_cy), BLOCKIO_SIG, 29,
    2, 2, 666, 0 },

  { 334,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_a), BLOCKIO_SIG, 29, 2, 2,
    668, 0 },

  { 335,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_mp), BLOCKIO_SIG, 29, 2, 2,
    670, 0 },

  { 336,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_b), BLOCKIO_SIG, 29, 2, 2, 672,
    0 },

  { 337,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_ow), BLOCKIO_SIG, 29, 2, 2, 674,
    0 },

  { 338,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_o), BLOCKIO_SIG, 29, 2, 2,
    676, 0 },

  { 339,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_g3), BLOCKIO_SIG, 29, 2, 2, 678,
    0 },

  { 340,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, MatrixConcatenate_p), BLOCKIO_SIG,
    30, 6, 2, 680, 0 },

  { 341, "studenttemplate/Main Subsystems/Control/LgV2/alpha^q/Add2", 0, "",
    offsetof(BlockIO_StudentTemplate, Add2_d), BLOCKIO_SIG, 30, 6, 2, 682, 0 },

  { 342, "studenttemplate/Main Subsystems/Control/LgV2/alpha^q/Product4", 0, "",
    offsetof(BlockIO_StudentTemplate, Product4_k), BLOCKIO_SIG, 30, 6, 2, 684, 0
  },

  { 343, "studenttemplate/Main Subsystems/Control/LgV2/alpha^q/Add3", 0, "",
    offsetof(BlockIO_StudentTemplate, Add3_p), BLOCKIO_SIG, 30, 6, 2, 686, 0 },

  { 344, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Integrator2",
    0, "", offsetof(BlockIO_StudentTemplate, Integrator2), BLOCKIO_SIG, 32, 2, 2,
    688, 0 },

  { 345, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Add2", 0, "",
    offsetof(BlockIO_StudentTemplate, Add2_f), BLOCKIO_SIG, 32, 2, 2, 690, 0 },

  { 346, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Product5", 0,
    "", offsetof(BlockIO_StudentTemplate, Product5), BLOCKIO_SIG, 28, 3, 2, 692,
    0 },

  { 347,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate1",
    0, "", offsetof(BlockIO_StudentTemplate, VectorConcatenate1), BLOCKIO_SIG,
    28, 3, 2, 694, 0 },

  { 348, "studenttemplate/Main Subsystems/Control/LgV2/alpha^s/Product3", 0, "",
    offsetof(BlockIO_StudentTemplate, Product3_h), BLOCKIO_SIG, 28, 3, 2, 696, 0
  },

  { 349,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_StudentTemplate, TrigonometricFunction1_f),
    BLOCKIO_SIG, 0, 1, 2, 698, 0 },

  { 350,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_l), BLOCKIO_SIG, 0, 1, 2, 700,
    0 },

  { 351,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_hg), BLOCKIO_SIG, 31, 1, 2,
    702, 0 },

  { 352,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function",
    0, "", offsetof(BlockIO_StudentTemplate, TrigonometricFunction_p5),
    BLOCKIO_SIG, 0, 1, 2, 704, 0 },

  { 353,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_n), BLOCKIO_SIG, 31, 1, 2,
    706, 0 },

  { 354,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_la), BLOCKIO_SIG, 25, 2, 2,
    708, 0 },

  { 355,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_eg), BLOCKIO_SIG, 0, 1, 2,
    710, 0 },

  { 356,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_lb), BLOCKIO_SIG, 0, 1, 2,
    712, 0 },

  { 357,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, VectorConcatenate_em), BLOCKIO_SIG,
    20, 3, 2, 714, 0 },

  { 358,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_fb), BLOCKIO_SIG, 32, 2, 2,
    716, 0 },

  { 359,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_fz), BLOCKIO_SIG, 0, 1, 2,
    718, 0 },

  { 360,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/sin(s)3",
    0, "", offsetof(BlockIO_StudentTemplate, sins3), BLOCKIO_SIG, 0, 1, 2, 720,
    0 },

  { 361,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_eq), BLOCKIO_SIG, 0, 1,
    2, 722, 0 },

  { 362,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_lr), BLOCKIO_SIG, 0, 1, 2,
    724, 0 },

  { 363,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/cos(s)3",
    0, "", offsetof(BlockIO_StudentTemplate, coss3), BLOCKIO_SIG, 0, 1, 2, 726,
    0 },

  { 364,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_fg), BLOCKIO_SIG, 0, 1, 2,
    728, 0 },

  { 365,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_ca), BLOCKIO_SIG, 0, 1, 2, 730,
    0 },

  { 366,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Subract",
    0, "", offsetof(BlockIO_StudentTemplate, Subract_l), BLOCKIO_SIG, 0, 1, 2,
    732, 0 },

  { 367,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_mt), BLOCKIO_SIG, 25, 2, 2,
    734, 0 },

  { 368,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_bs), BLOCKIO_SIG, 32, 2, 2, 736,
    0 },

  { 369,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + y_d^s^3",
    0, "", offsetof(BlockIO_StudentTemplate, x_dsy_ds3), BLOCKIO_SIG, 31, 1, 2,
    738, 0 },

  { 370,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s^3 + y_d^s",
    0, "", offsetof(BlockIO_StudentTemplate, x_ds3y_ds), BLOCKIO_SIG, 31, 1, 2,
    740, 0 },

  { 371,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + y_d^s^3  ) - ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_StudentTemplate, x_dsy_ds3x_ds3y_ds), BLOCKIO_SIG,
    31, 1, 2, 742, 0 },

  { 372,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_op), BLOCKIO_SIG, 31, 1, 2,
    744, 0 },

  { 373,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + x_d^s^2",
    0, "", offsetof(BlockIO_StudentTemplate, x_dsx_ds2), BLOCKIO_SIG, 31, 1, 2,
    746, 0 },

  { 374,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/y_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_StudentTemplate, y_dsy_ds2), BLOCKIO_SIG, 31, 1, 2,
    748, 0 },

  { 375,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + x_d^s^2 ) + ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_StudentTemplate, x_dsx_ds2x_ds3y_ds), BLOCKIO_SIG,
    31, 1, 2, 750, 0 },

  { 376,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2",
    0, "", offsetof(BlockIO_StudentTemplate, u_k), BLOCKIO_SIG, 31, 1, 2, 752, 0
  },

  { 377,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_i), BLOCKIO_SIG, 31, 1, 2,
    754, 0 },

  { 378,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Subtract",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract_m), BLOCKIO_SIG, 31, 1, 2,
    756, 0 },

  { 379,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2",
    0, "", offsetof(BlockIO_StudentTemplate, x_ds2y_ds22), BLOCKIO_SIG, 0, 1, 2,
    758, 0 },

  { 380,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_ob), BLOCKIO_SIG, 31, 1, 2,
    760, 0 },

  { 381,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/(epsilon_n^s)^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_ns2), BLOCKIO_SIG, 31, 1, 2,
    762, 0 },

  { 382,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_lu), BLOCKIO_SIG, 31, 1, 2,
    764, 0 },

  { 383,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2",
    0, "", offsetof(BlockIO_StudentTemplate, u_o), BLOCKIO_SIG, 31, 1, 2, 766, 0
  },

  { 384,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2_d), BLOCKIO_SIG, 0, 1, 2,
    768, 0 },

  { 385,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2_nk), BLOCKIO_SIG, 31, 1,
    2, 770, 0 },

  { 386,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_c), BLOCKIO_SIG, 31, 1, 2, 772,
    0 },

  { 387,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/( )^2",
    0, "", offsetof(BlockIO_StudentTemplate, u_e2), BLOCKIO_SIG, 31, 1, 2, 774,
    0 },

  { 388,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_h), BLOCKIO_SIG, 31, 1, 2,
    776, 0 },

  { 389,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_bo), BLOCKIO_SIG, 24,
    4, 2, 778, 0 },

  { 390,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_o), BLOCKIO_SIG, 24, 4, 2,
    780, 0 },

  { 391,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_ii), BLOCKIO_SIG, 24, 4, 2, 782,
    0 },

  { 392,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_pg), BLOCKIO_SIG, 25, 2, 2,
    784, 0 },

  { 393,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_hq), BLOCKIO_SIG, 25, 2, 2,
    786, 0 },

  { 394,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2",
    0, "", offsetof(BlockIO_StudentTemplate, u_j), BLOCKIO_SIG, 25, 2, 2, 788, 0
  },

  { 395,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product3",
    0, "", offsetof(BlockIO_StudentTemplate, Product3_e5), BLOCKIO_SIG, 32, 2, 2,
    790, 0 },

  { 396,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_og), BLOCKIO_SIG, 32, 2, 2, 792,
    0 },

  { 397,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_f), BLOCKIO_SIG, 32, 2, 2, 794,
    0 },

  { 398,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector4",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSelector4), BLOCKIO_SIG,
    31, 1, 2, 796, 0 },

  { 399,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_a1), BLOCKIO_SIG, 31, 1, 2,
    798, 0 },

  { 400,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide1",
    0, "", offsetof(BlockIO_StudentTemplate, Divide1_pj), BLOCKIO_SIG, 31, 1, 2,
    800, 0 },

  { 401,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_l), BLOCKIO_SIG, 31, 1, 2, 802,
    0 },

  { 402,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_k), BLOCKIO_SIG, 0, 1, 2,
    804, 0 },

  { 403,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_lp), BLOCKIO_SIG, 29,
    2, 2, 806, 0 },

  { 404,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_ke), BLOCKIO_SIG, 31, 1, 2,
    808, 0 },

  { 405,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/|p_d^s|^3",
    0, "", offsetof(BlockIO_StudentTemplate, p_ds3), BLOCKIO_SIG, 0, 1, 2, 810,
    0 },

  { 406,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_it), BLOCKIO_SIG, 0, 1, 2,
    812, 0 },

  { 407,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_h), BLOCKIO_SIG, 0, 1, 2,
    814, 0 },

  { 408,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_nv), BLOCKIO_SIG, 0, 1, 2, 816,
    0 },

  { 409,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_StudentTemplate, epsilon_n2_d), BLOCKIO_SIG, 31, 1,
    2, 818, 0 },

  { 410,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Delta^2",
    0, "", offsetof(BlockIO_StudentTemplate, Delta2_k), BLOCKIO_SIG, 0, 1, 2,
    820, 0 },

  { 411,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_l4), BLOCKIO_SIG, 31, 1, 2, 822,
    0 },

  { 412,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_ju), BLOCKIO_SIG, 31,
    1, 2, 824, 0 },

  { 413,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide",
    0, "", offsetof(BlockIO_StudentTemplate, Divide_da), BLOCKIO_SIG, 0, 1, 2,
    826, 0 },

  { 414,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_c), BLOCKIO_SIG, 0, 1, 2,
    828, 0 },

  { 415,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_m), BLOCKIO_SIG, 31, 1, 2,
    830, 0 },

  { 416,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/^3//2",
    0, "", offsetof(BlockIO_StudentTemplate, u2_p), BLOCKIO_SIG, 31, 1, 2, 832,
    0 },

  { 417,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide1",
    0, "", offsetof(BlockIO_StudentTemplate, Divide1_f), BLOCKIO_SIG, 31, 1, 2,
    834, 0 },

  { 418,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product3",
    0, "", offsetof(BlockIO_StudentTemplate, Product3_m), BLOCKIO_SIG, 0, 1, 2,
    836, 0 },

  { 419,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_e), BLOCKIO_SIG, 0, 1, 2,
    838, 0 },

  { 420,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_fs), BLOCKIO_SIG, 29,
    2, 2, 840, 0 },

  { 421,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide2",
    0, "", offsetof(BlockIO_StudentTemplate, Divide2), BLOCKIO_SIG, 29, 2, 2,
    842, 0 },

  { 422,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_ps), BLOCKIO_SIG, 29,
    2, 2, 844, 0 },

  { 423,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_k), BLOCKIO_SIG, 29, 2, 2,
    846, 0 },

  { 424,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_fa), BLOCKIO_SIG, 0, 1,
    2, 848, 0 },

  { 425,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide1",
    0, "", offsetof(BlockIO_StudentTemplate, Divide1_b), BLOCKIO_SIG, 29, 2, 2,
    850, 0 },

  { 426,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract1",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract1_b), BLOCKIO_SIG, 29, 2, 2,
    852, 0 },

  { 427,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_ca), BLOCKIO_SIG, 0, 1, 2,
    854, 0 },

  { 428,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract",
    0, "", offsetof(BlockIO_StudentTemplate, Subtract_ea), BLOCKIO_SIG, 0, 1, 2,
    856, 0 },

  { 429,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_mk), BLOCKIO_SIG, 0, 1, 2, 858,
    0 },

  { 430,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_kz), BLOCKIO_SIG, 0, 1, 2,
    860, 0 },

  { 431,
    "studenttemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_StudentTemplate, VectorConcatenate_c5), BLOCKIO_SIG,
    28, 3, 2, 862, 0 },

  { 432, "studenttemplate/Main Subsystems/Control/LgV2/alpha^s/Add2", 0, "",
    offsetof(BlockIO_StudentTemplate, Add2_a), BLOCKIO_SIG, 28, 3, 2, 864, 0 },

  { 433, "studenttemplate/Main Subsystems/Control/LgV2/alpha^s/Product4", 0, "",
    offsetof(BlockIO_StudentTemplate, Product4_f), BLOCKIO_SIG, 28, 3, 2, 866, 0
  },

  { 434, "studenttemplate/Main Subsystems/Control/LgV2/alpha^s/Add3", 0, "",
    offsetof(BlockIO_StudentTemplate, Add3_l), BLOCKIO_SIG, 28, 3, 2, 868, 0 },

  { 435, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Product6", 0,
    "", offsetof(BlockIO_StudentTemplate, Product6), BLOCKIO_SIG, 20, 3, 2, 870,
    0 },

  { 436, "studenttemplate/Main Subsystems/Control/LgV2/Control law/Sum", 0, "",
    offsetof(BlockIO_StudentTemplate, Sum_lt), BLOCKIO_SIG, 28, 3, 2, 872, 0 },

  { 437, "studenttemplate/Main Subsystems/Control/Control Switch/tau Switch", 0,
    "", offsetof(BlockIO_StudentTemplate, tauSwitch), BLOCKIO_SIG, 28, 3, 2, 874,
    0 },

  { 438, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Add", 0, "",
    offsetof(BlockIO_StudentTemplate, Add_gg), BLOCKIO_SIG, 32, 2, 2, 876, 0 },

  { 439,
    "studenttemplate/Main Subsystems/Control/LgV2/V_1^q/Transpose/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_la), BLOCKIO_SIG, 33,
    3, 2, 878, 0 },

  { 440, "studenttemplate/Main Subsystems/Control/LgV2/V_1^q/Product", 0, "",
    offsetof(BlockIO_StudentTemplate, Product_g4), BLOCKIO_SIG, 29, 2, 2, 880, 0
  },

  { 441, "studenttemplate/Main Subsystems/Control/LgV2/V_1^q/Gain", 0, "",
    offsetof(BlockIO_StudentTemplate, Gain_i), BLOCKIO_SIG, 29, 2, 2, 882, 0 },

  { 442,
    "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Transpose/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_h2), BLOCKIO_SIG, 32,
    2, 2, 884, 0 },

  { 443, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Product", 0,
    "", offsetof(BlockIO_StudentTemplate, Product_a5), BLOCKIO_SIG, 32, 2, 2,
    886, 0 },

  { 444, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Add1", 0, "",
    offsetof(BlockIO_StudentTemplate, Add1_l), BLOCKIO_SIG, 32, 2, 2, 888, 0 },

  { 445, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Product1", 0,
    "", offsetof(BlockIO_StudentTemplate, Product1_cx), BLOCKIO_SIG, 32, 2, 2,
    890, 0 },

  { 446, "studenttemplate/Main Subsystems/Control/LgV2/Update laws/Gain", 0, "",
    offsetof(BlockIO_StudentTemplate, Gain_mv), BLOCKIO_SIG, 32, 2, 2, 892, 0 },

  { 447, "studenttemplate/Main Subsystems/Control/LgV2/zeta/Product", 0, "",
    offsetof(BlockIO_StudentTemplate, Product_ar), BLOCKIO_SIG, 28, 3, 2, 894, 0
  },

  { 448,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_StudentTemplate, Pseudoinverse), BLOCKIO_SIG, 41, 15,
    2, 896, 0 },

  { 449,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_hu), BLOCKIO_SIG, 37, 5, 2,
    898, 0 },

  { 450,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1",
    0, "", offsetof(BlockIO_StudentTemplate, f_1tou_1), BLOCKIO_SIG, 31, 1, 2,
    900, 0 },

  { 451,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_j), BLOCKIO_SIG, 31, 1, 2, 902,
    0 },

  { 452,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391",
    0, "", offsetof(BlockIO_StudentTemplate, f_2000391), BLOCKIO_SIG, 31, 1, 2,
    904, 0 },

  { 453,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391",
    0, "", offsetof(BlockIO_StudentTemplate, f_2006731f_2000391), BLOCKIO_SIG,
    31, 1, 2, 906, 0 },

  { 454,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731",
    0, "", offsetof(BlockIO_StudentTemplate, f_2006731), BLOCKIO_SIG, 31, 1, 2,
    908, 0 },

  { 455,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSwitch), BLOCKIO_SIG, 31,
    1, 2, 910, 0 },

  { 456,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_o), BLOCKIO_SIG, 31, 1, 2, 912,
    0 },

  { 457,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3",
    0, "", offsetof(BlockIO_StudentTemplate, f_3tou_3), BLOCKIO_SIG, 31, 1, 2,
    914, 0 },

  { 458,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum2",
    0, "", offsetof(BlockIO_StudentTemplate, Sum2_p), BLOCKIO_SIG, 31, 1, 2, 916,
    0 },

  { 459,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451",
    0, "", offsetof(BlockIO_StudentTemplate, f_400451), BLOCKIO_SIG, 31, 1, 2,
    918, 0 },

  { 460,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451",
    0, "", offsetof(BlockIO_StudentTemplate, f_400451_o), BLOCKIO_SIG, 31, 1, 2,
    920, 0 },

  { 461,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSwitch_e), BLOCKIO_SIG, 31,
    1, 2, 922, 0 },

  { 462,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum3",
    0, "", offsetof(BlockIO_StudentTemplate, Sum3_k), BLOCKIO_SIG, 31, 1, 2, 924,
    0 },

  { 463,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_StudentTemplate, DeadZone001), BLOCKIO_SIG, 31, 1, 2,
    926, 0 },

  { 464,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0",
    0, "", offsetof(BlockIO_StudentTemplate, f_50), BLOCKIO_SIG, 31, 1, 2, 928,
    0 },

  { 465,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0",
    0, "", offsetof(BlockIO_StudentTemplate, f_50_b), BLOCKIO_SIG, 31, 1, 2, 930,
    0 },

  { 466,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSwitch_j), BLOCKIO_SIG, 31,
    1, 2, 932, 0 },

  { 467,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/Saturation", 0,
    "", offsetof(BlockIO_StudentTemplate, Saturation_j), BLOCKIO_SIG, 35, 7, 2,
    934, 0 },

  { 468,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn2Error), BLOCKIO_SIG, 31, 1, 2,
    936, 0 },

  { 469,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn9Residual), BLOCKIO_SIG, 31, 1,
    2, 938, 0 },

  { 470,
    "studenttemplate/Main Subsystems/Plant/Thruster setting workaround/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_iv), BLOCKIO_SIG, 0, 1,
    2, 940, 0 },

  { 471,
    "studenttemplate/Main Subsystems/Plant/Thruster setting workaround/tau Switch",
    0, "", offsetof(BlockIO_StudentTemplate, tauSwitch_o), BLOCKIO_SIG, 35, 7, 2,
    942, 0 },

  { 472,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn5zcoordmm), BLOCKIO_SIG, 31, 1,
    2, 944, 0 },

  { 473, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/mm2m z", 0,
    "", offsetof(BlockIO_StudentTemplate, mm2mz), BLOCKIO_SIG, 31, 1, 2, 946, 0
  },

  { 474,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn8rolldeg), BLOCKIO_SIG, 31, 1,
    2, 948, 0 },

  { 475, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r roll",
    0, "", offsetof(BlockIO_StudentTemplate, d2rroll), BLOCKIO_SIG, 31, 1, 2,
    950, 0 },

  { 476,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn7pitchdeg), BLOCKIO_SIG, 31, 1,
    2, 952, 0 },

  { 477, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/d2r pitch",
    0, "", offsetof(BlockIO_StudentTemplate, d2rpitch), BLOCKIO_SIG, 31, 1, 2,
    954, 0 },

  { 478, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Derivative",
    0, "", offsetof(BlockIO_StudentTemplate, Derivative_o), BLOCKIO_SIG, 34, 6,
    2, 956, 0 },

  { 479,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_StudentTemplate, sintheta), BLOCKIO_SIG, 20, 3, 2,
    958, 0 },

  { 480,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_StudentTemplate, costheta), BLOCKIO_SIG, 20, 3, 2,
    960, 0 },

  { 481,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_StudentTemplate, R11_d), BLOCKIO_SIG, 0, 1, 2, 962,
    0 },

  { 482,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_StudentTemplate, R12_o), BLOCKIO_SIG, 0, 1, 2, 964,
    0 },

  { 483,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_StudentTemplate, R13), BLOCKIO_SIG, 0, 1, 2, 966, 0
  },

  { 484,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_StudentTemplate, R21_j), BLOCKIO_SIG, 0, 1, 2, 968,
    0 },

  { 485,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_StudentTemplate, R22_g), BLOCKIO_SIG, 0, 1, 2, 970,
    0 },

  { 486,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_StudentTemplate, R23), BLOCKIO_SIG, 0, 1, 2, 972, 0
  },

  { 487,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_StudentTemplate, R31), BLOCKIO_SIG, 0, 1, 2, 974, 0
  },

  { 488,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_StudentTemplate, R32), BLOCKIO_SIG, 0, 1, 2, 976, 0
  },

  { 489,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_StudentTemplate, R33), BLOCKIO_SIG, 0, 1, 2, 978, 0
  },

  { 490,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_StudentTemplate, Reshape9x13x3), BLOCKIO_SIG, 22, 9,
    2, 980, 0 },

  { 491, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Inverse", 0,
    "", offsetof(BlockIO_StudentTemplate, Inverse), BLOCKIO_SIG, 22, 9, 2, 982,
    0 },

  { 492,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Matrix Concatenate2",
    0, "", offsetof(BlockIO_StudentTemplate, MatrixConcatenate2), BLOCKIO_SIG,
    54, 36, 2, 984, 0 },

  { 493, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/Product", 0,
    "", offsetof(BlockIO_StudentTemplate, Product_go), BLOCKIO_SIG, 34, 6, 2,
    986, 0 },

  { 494, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN",
    0, "", offsetof(BlockIO_StudentTemplate, QTMIn1FN), BLOCKIO_SIG, 31, 1, 2,
    988, 0 },

  { 495,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator",
    0, "eta", offsetof(BlockIO_StudentTemplate, eta), BLOCKIO_SIG, 20, 3, 2, 990,
    0 },

  { 496,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3",
    0, "bias", offsetof(BlockIO_StudentTemplate, bias), BLOCKIO_SIG, 20, 3, 2,
    992, 0 },

  { 497,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_lr), BLOCKIO_SIG, 0, 1,
    2, 994, 0 },

  { 498,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_ab), BLOCKIO_SIG, 0, 1, 2, 996,
    0 },

  { 499,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_cy), BLOCKIO_SIG, 0, 1, 2, 998,
    0 },

  { 500,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_e), BLOCKIO_SIG, 0, 1, 2, 1000,
    0 },

  { 501,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_hz), BLOCKIO_SIG, 0, 1,
    2, 1002, 0 },

  { 502,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_bk), BLOCKIO_SIG, 0, 1, 2, 1004,
    0 },

  { 503,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum2",
    0, "", offsetof(BlockIO_StudentTemplate, Sum2_b), BLOCKIO_SIG, 20, 3, 2,
    1006, 0 },

  { 504,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_StudentTemplate, Saturation_b), BLOCKIO_SIG, 0, 1, 2,
    1008, 0 },

  { 505,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_j), BLOCKIO_SIG, 0, 1, 2, 1010,
    0 },

  { 506,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_cb), BLOCKIO_SIG, 0, 1, 2,
    1012, 0 },

  { 507,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_ll), BLOCKIO_SIG, 0, 1, 2,
    1014, 0 },

  { 508,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_StudentTemplate, MathFunction_fr), BLOCKIO_SIG, 0, 1,
    2, 1016, 0 },

  { 509,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_ez), BLOCKIO_SIG, 0, 1, 2, 1018,
    0 },

  { 510,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2",
    0, "", offsetof(BlockIO_StudentTemplate, K2), BLOCKIO_SIG, 20, 3, 2, 1020, 0
  },

  { 511,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3",
    0, "", offsetof(BlockIO_StudentTemplate, K3), BLOCKIO_SIG, 20, 3, 2, 1022, 0
  },

  { 512,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4",
    0, "", offsetof(BlockIO_StudentTemplate, K4), BLOCKIO_SIG, 20, 3, 2, 1024, 0
  },

  { 513,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row1",
    0, "", offsetof(BlockIO_StudentTemplate, Row1_k), BLOCKIO_SIG, 0, 1, 2, 1026,
    0 },

  { 514,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row2",
    0, "", offsetof(BlockIO_StudentTemplate, Row2_o), BLOCKIO_SIG, 0, 1, 2, 1028,
    0 },

  { 515,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row3",
    0, "", offsetof(BlockIO_StudentTemplate, Row3_g), BLOCKIO_SIG, 0, 1, 2, 1030,
    0 },

  { 516,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_StudentTemplate, Row1_g), BLOCKIO_SIG, 0, 1, 2, 1032,
    0 },

  { 517,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_StudentTemplate, Row2_i), BLOCKIO_SIG, 0, 1, 2, 1034,
    0 },

  { 518,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_StudentTemplate, Row3_d), BLOCKIO_SIG, 0, 1, 2, 1036,
    0 },

  { 519,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1",
    0, "", offsetof(BlockIO_StudentTemplate, u_1tof_1_o), BLOCKIO_SIG, 0, 1, 2,
    1038, 0 },

  { 520,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5",
    0, "", offsetof(BlockIO_StudentTemplate, u_205), BLOCKIO_SIG, 0, 1, 2, 1040,
    0 },

  { 521,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2",
    0, "", offsetof(BlockIO_StudentTemplate, u_201u_202), BLOCKIO_SIG, 0, 1, 2,
    1042, 0 },

  { 522,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0",
    0, "", offsetof(BlockIO_StudentTemplate, u_20), BLOCKIO_SIG, 0, 1, 2, 1044,
    0 },

  { 523,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSwitch_k), BLOCKIO_SIG, 0,
    1, 2, 1046, 0 },

  { 524,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3",
    0, "", offsetof(BlockIO_StudentTemplate, u_3tof_3_g), BLOCKIO_SIG, 0, 1, 2,
    1048, 0 },

  { 525,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1",
    0, "", offsetof(BlockIO_StudentTemplate, u_401), BLOCKIO_SIG, 0, 1, 2, 1050,
    0 },

  { 526,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1",
    0, "", offsetof(BlockIO_StudentTemplate, u_401_b), BLOCKIO_SIG, 0, 1, 2,
    1052, 0 },

  { 527,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSwitch_i), BLOCKIO_SIG, 0,
    1, 2, 1054, 0 },

  { 528,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_StudentTemplate, DeadZone001_c), BLOCKIO_SIG, 0, 1,
    2, 1056, 0 },

  { 529,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0",
    0, "", offsetof(BlockIO_StudentTemplate, u_50), BLOCKIO_SIG, 0, 1, 2, 1058,
    0 },

  { 530,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0",
    0, "", offsetof(BlockIO_StudentTemplate, u_50_d), BLOCKIO_SIG, 0, 1, 2, 1060,
    0 },

  { 531,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_StudentTemplate, MultiportSwitch_m), BLOCKIO_SIG, 0,
    1, 2, 1062, 0 },

  { 532,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_dl), BLOCKIO_SIG, 20, 3, 2,
    1064, 0 },

  { 533,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_eh), BLOCKIO_SIG, 20, 3, 2,
    1066, 0 },

  { 534,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_k0), BLOCKIO_SIG, 20, 3, 2,
    1068, 0 },

  { 535,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum8",
    0, "", offsetof(BlockIO_StudentTemplate, Sum8), BLOCKIO_SIG, 20, 3, 2, 1070,
    0 },

  { 536,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Product",
    0, "", offsetof(BlockIO_StudentTemplate, Product_ay), BLOCKIO_SIG, 20, 3, 2,
    1072, 0 },

  { 537,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn",
    0, "x_dot", offsetof(BlockIO_StudentTemplate, x_dot), BLOCKIO_SIG, 0, 1, 2,
    1074, 0 },

  { 538,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn1",
    0, "y_dot", offsetof(BlockIO_StudentTemplate, y_dot), BLOCKIO_SIG, 0, 1, 2,
    1076, 0 },

  { 539,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn2",
    0, "psi_dot", offsetof(BlockIO_StudentTemplate, psi_dot), BLOCKIO_SIG, 0, 1,
    2, 1078, 0 },

  { 540,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum3",
    0, "", offsetof(BlockIO_StudentTemplate, Sum3_h), BLOCKIO_SIG, 20, 3, 2,
    1080, 0 },

  { 541,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)",
    0, "", offsetof(BlockIO_StudentTemplate, invT_b), BLOCKIO_SIG, 20, 3, 2,
    1082, 0 },

  { 542,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum7",
    0, "", offsetof(BlockIO_StudentTemplate, Sum7), BLOCKIO_SIG, 20, 3, 2, 1084,
    0 },

  { 543, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/SIT zAI0",
    0, "", offsetof(BlockIO_StudentTemplate, SITzAI0), BLOCKIO_SIG, 0, 1, 2,
    1086, 0 },

  { 544, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/SIT zAI1",
    0, "", offsetof(BlockIO_StudentTemplate, SITzAI1), BLOCKIO_SIG, 0, 1, 2,
    1088, 0 },

  { 545, "studenttemplate/Main Subsystems/Naviagation/Input from SIT/SIT zAI2",
    0, "", offsetof(BlockIO_StudentTemplate, SITzAI2), BLOCKIO_SIG, 0, 1, 2,
    1090, 0 },

  { 546, "studenttemplate/Main Subsystems/Plant/Inverse", 0, "", offsetof
    (BlockIO_StudentTemplate, Inverse_c), BLOCKIO_SIG, 22, 9, 2, 1092, 0 },

  { 547, "studenttemplate/Main Subsystems/Plant/saturation/Saturation", 0, "",
    offsetof(BlockIO_StudentTemplate, Saturation_a), BLOCKIO_SIG, 31, 1, 2, 1094,
    0 },

  { 548, "studenttemplate/Main Subsystems/Plant/saturation/Saturation1", 0, "",
    offsetof(BlockIO_StudentTemplate, Saturation1), BLOCKIO_SIG, 31, 1, 2, 1096,
    0 },

  { 549, "studenttemplate/Main Subsystems/Plant/saturation/Saturation2", 0, "",
    offsetof(BlockIO_StudentTemplate, Saturation2), BLOCKIO_SIG, 31, 1, 2, 1098,
    0 },

  { 550, "studenttemplate/Main Subsystems/Plant/saturation/plant tau_surge", 0,
    "", offsetof(BlockIO_StudentTemplate, planttau_surge), BLOCKIO_SIG, 31, 1, 2,
    1100, 0 },

  { 551, "studenttemplate/Main Subsystems/Plant/saturation/plant tau_sway", 0,
    "", offsetof(BlockIO_StudentTemplate, planttau_sway), BLOCKIO_SIG, 31, 1, 2,
    1102, 0 },

  { 552, "studenttemplate/Main Subsystems/Plant/saturation/plant tau_yaw", 0, "",
    offsetof(BlockIO_StudentTemplate, planttau_yaw), BLOCKIO_SIG, 31, 1, 2, 1104,
    0 },

  { 553,
    "studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster", 0,
    "", offsetof(BlockIO_StudentTemplate, BatteryBowThruster), BLOCKIO_SIG, 0, 1,
    2, 1106, 0 },

  { 554, "studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Main", 0,
    "", offsetof(BlockIO_StudentTemplate, BatteryMain), BLOCKIO_SIG, 0, 1, 2,
    1108, 0 },

  { 555, "studenttemplate/Outputs to LabVIEW/Battery Voltage/Battery Servo", 0,
    "", offsetof(BlockIO_StudentTemplate, BatteryServo), BLOCKIO_SIG, 0, 1, 2,
    1110, 0 },

  { 556, "studenttemplate/Outputs to LabVIEW/Command/tau1", 0, "", offsetof
    (BlockIO_StudentTemplate, tau1), BLOCKIO_SIG, 28, 3, 2, 1112, 0 },

  { 557, "studenttemplate/Outputs to LabVIEW/Command/tau2", 0, "", offsetof
    (BlockIO_StudentTemplate, tau2), BLOCKIO_SIG, 28, 3, 2, 1114, 0 },

  { 558, "studenttemplate/Outputs to LabVIEW/Command/tau3", 0, "", offsetof
    (BlockIO_StudentTemplate, tau3), BLOCKIO_SIG, 20, 3, 2, 1116, 0 },

  { 559, "studenttemplate/Outputs to LabVIEW/Command/tau4", 0, "", offsetof
    (BlockIO_StudentTemplate, tau4), BLOCKIO_SIG, 28, 3, 2, 1118, 0 },

  { 560, "studenttemplate/Outputs to LabVIEW/Command/tau5", 0, "", offsetof
    (BlockIO_StudentTemplate, tau5), BLOCKIO_SIG, 28, 3, 2, 1120, 0 },

  { 561, "studenttemplate/Outputs to LabVIEW/Command/tau6", 0, "", offsetof
    (BlockIO_StudentTemplate, tau6), BLOCKIO_SIG, 20, 3, 2, 1122, 0 },

  { 562, "studenttemplate/Outputs to LabVIEW/Command/plant BT power", 0, "",
    offsetof(BlockIO_StudentTemplate, plantBTpower), BLOCKIO_SIG, 0, 1, 2, 1124,
    0 },

  { 563, "studenttemplate/Outputs to LabVIEW/Command/plant VSP speed", 0, "",
    offsetof(BlockIO_StudentTemplate, plantVSPspeed), BLOCKIO_SIG, 0, 1, 2, 1126,
    0 },

  { 564, "studenttemplate/Outputs to LabVIEW/Command/plant u_1", 0, "", offsetof
    (BlockIO_StudentTemplate, plantu_1), BLOCKIO_SIG, 0, 1, 2, 1128, 0 },

  { 565, "studenttemplate/Outputs to LabVIEW/Command/plant u_2", 0, "", offsetof
    (BlockIO_StudentTemplate, plantu_2), BLOCKIO_SIG, 0, 1, 2, 1130, 0 },

  { 566, "studenttemplate/Outputs to LabVIEW/Command/plant u_3", 0, "", offsetof
    (BlockIO_StudentTemplate, plantu_3), BLOCKIO_SIG, 0, 1, 2, 1132, 0 },

  { 567, "studenttemplate/Outputs to LabVIEW/Command/plant u_4", 0, "", offsetof
    (BlockIO_StudentTemplate, plantu_4), BLOCKIO_SIG, 0, 1, 2, 1134, 0 },

  { 568, "studenttemplate/Outputs to LabVIEW/Command/plant u_5", 0, "", offsetof
    (BlockIO_StudentTemplate, plantu_5), BLOCKIO_SIG, 0, 1, 2, 1136, 0 },

  { 569, "studenttemplate/Outputs to LabVIEW/Command/fact1", 0, "", offsetof
    (BlockIO_StudentTemplate, fact1), BLOCKIO_SIG, 31, 1, 2, 1138, 0 },

  { 570, "studenttemplate/Outputs to LabVIEW/Command/fact2", 0, "", offsetof
    (BlockIO_StudentTemplate, fact2), BLOCKIO_SIG, 31, 1, 2, 1140, 0 },

  { 571, "studenttemplate/Outputs to LabVIEW/Command/fact3", 0, "", offsetof
    (BlockIO_StudentTemplate, fact3), BLOCKIO_SIG, 31, 1, 2, 1142, 0 },

  { 572, "studenttemplate/Outputs to LabVIEW/Command/fact4", 0, "", offsetof
    (BlockIO_StudentTemplate, fact4), BLOCKIO_SIG, 31, 1, 2, 1144, 0 },

  { 573, "studenttemplate/Outputs to LabVIEW/Command/fact5", 0, "", offsetof
    (BlockIO_StudentTemplate, fact5), BLOCKIO_SIG, 31, 1, 2, 1146, 0 },

  { 574, "studenttemplate/Outputs to LabVIEW/Command/taux", 0, "", offsetof
    (BlockIO_StudentTemplate, taux), BLOCKIO_SIG, 31, 1, 2, 1148, 0 },

  { 575, "studenttemplate/Outputs to LabVIEW/Command/tauy", 0, "", offsetof
    (BlockIO_StudentTemplate, tauy), BLOCKIO_SIG, 31, 1, 2, 1150, 0 },

  { 576, "studenttemplate/Outputs to LabVIEW/Command/tauyaw", 0, "", offsetof
    (BlockIO_StudentTemplate, tauyaw), BLOCKIO_SIG, 31, 1, 2, 1152, 0 },

  { 577, "studenttemplate/Outputs to LabVIEW/Command/omega_qy", 0, "", offsetof
    (BlockIO_StudentTemplate, omega_qy), BLOCKIO_SIG, 31, 1, 2, 1154, 0 },

  { 578, "studenttemplate/Outputs to LabVIEW/Command/omegaqx", 0, "", offsetof
    (BlockIO_StudentTemplate, omegaqx), BLOCKIO_SIG, 31, 1, 2, 1156, 0 },

  { 579, "studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]", 0, "",
    offsetof(BlockIO_StudentTemplate, CSE1_rdegs), BLOCKIO_SIG, 0, 1, 2, 1158, 0
  },

  { 580, "studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]", 0, "",
    offsetof(BlockIO_StudentTemplate, CSE1_ums), BLOCKIO_SIG, 0, 1, 2, 1160, 0 },

  { 581, "studenttemplate/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]", 0, "",
    offsetof(BlockIO_StudentTemplate, CSE1_vms), BLOCKIO_SIG, 0, 1, 2, 1162, 0 },

  { 582, "studenttemplate/Outputs to LabVIEW/Naviagtion/QS Error", 0, "",
    offsetof(BlockIO_StudentTemplate, QSError), BLOCKIO_SIG, 31, 1, 2, 1164, 0 },

  { 583, "studenttemplate/Outputs to LabVIEW/Naviagtion/QS Frame", 0, "",
    offsetof(BlockIO_StudentTemplate, QSFrame), BLOCKIO_SIG, 31, 1, 2, 1166, 0 },

  { 584, "studenttemplate/Outputs to LabVIEW/Visualization/Sum", 0, "", offsetof
    (BlockIO_StudentTemplate, Sum_f), BLOCKIO_SIG, 20, 3, 2, 1168, 0 },

  { 585, "studenttemplate/Outputs to LabVIEW/Visualization/Sum1", 0, "",
    offsetof(BlockIO_StudentTemplate, Sum1_hm), BLOCKIO_SIG, 20, 3, 2, 1170, 0 },

  { 586, "studenttemplate/Outputs to LabVIEW/Visualization/Sum2", 0, "",
    offsetof(BlockIO_StudentTemplate, Sum2_j), BLOCKIO_SIG, 20, 3, 2, 1172, 0 },

  { 587, "studenttemplate/Outputs to LabVIEW/Visualization/psi [deg]", 0, "",
    offsetof(BlockIO_StudentTemplate, psideg), BLOCKIO_SIG, 0, 1, 2, 1174, 0 },

  { 588, "studenttemplate/Outputs to LabVIEW/Visualization/psi-psid [deg]", 0,
    "", offsetof(BlockIO_StudentTemplate, psipsiddeg), BLOCKIO_SIG, 0, 1, 2,
    1176, 0 },

  { 589, "studenttemplate/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]", 0,
    "", offsetof(BlockIO_StudentTemplate, psiLOSpsideg), BLOCKIO_SIG, 0, 1, 2,
    1178, 0 },

  { 590, "studenttemplate/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]", 0,
    "", offsetof(BlockIO_StudentTemplate, psiLOSpsiddeg), BLOCKIO_SIG, 0, 1, 2,
    1180, 0 },

  { 591, "studenttemplate/Outputs to LabVIEW/Visualization/psi_LOS [deg]", 0, "",
    offsetof(BlockIO_StudentTemplate, psi_LOSdeg), BLOCKIO_SIG, 0, 1, 2, 1182, 0
  },

  { 592, "studenttemplate/Outputs to LabVIEW/Visualization/psid [deg]", 0, "",
    offsetof(BlockIO_StudentTemplate, psiddeg), BLOCKIO_SIG, 0, 1, 2, 1184, 0 },

  { 593, "studenttemplate/Outputs to LabVIEW/Visualization/psi_plot", 0, "",
    offsetof(BlockIO_StudentTemplate, psi_plot), BLOCKIO_SIG, 20, 3, 2, 1186, 0
  },

  { 594, "studenttemplate/Outputs to LabVIEW/Visualization/qx [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, qxm), BLOCKIO_SIG, 0, 1, 2, 1188, 0 },

  { 595, "studenttemplate/Outputs to LabVIEW/Visualization/qx-x [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, qxxm), BLOCKIO_SIG, 0, 1, 2, 1190, 0 },

  { 596, "studenttemplate/Outputs to LabVIEW/Visualization/qx-xd [m]1", 0, "",
    offsetof(BlockIO_StudentTemplate, qxxdm1), BLOCKIO_SIG, 0, 1, 2, 1192, 0 },

  { 597, "studenttemplate/Outputs to LabVIEW/Visualization/qy [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, qym), BLOCKIO_SIG, 0, 1, 2, 1194, 0 },

  { 598, "studenttemplate/Outputs to LabVIEW/Visualization/qy-y [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, qyym), BLOCKIO_SIG, 0, 1, 2, 1196, 0 },

  { 599, "studenttemplate/Outputs to LabVIEW/Visualization/qy-yd [m]1", 0, "",
    offsetof(BlockIO_StudentTemplate, qyydm1), BLOCKIO_SIG, 0, 1, 2, 1198, 0 },

  { 600, "studenttemplate/Outputs to LabVIEW/Visualization/x [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, xm), BLOCKIO_SIG, 0, 1, 2, 1200, 0 },

  { 601, "studenttemplate/Outputs to LabVIEW/Visualization/x-xd [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, xxdm), BLOCKIO_SIG, 0, 1, 2, 1202, 0 },

  { 602, "studenttemplate/Outputs to LabVIEW/Visualization/xd [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, xdm), BLOCKIO_SIG, 0, 1, 2, 1204, 0 },

  { 603, "studenttemplate/Outputs to LabVIEW/Visualization/x_plot", 0, "",
    offsetof(BlockIO_StudentTemplate, x_plot), BLOCKIO_SIG, 20, 3, 2, 1206, 0 },

  { 604, "studenttemplate/Outputs to LabVIEW/Visualization/y [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, ym), BLOCKIO_SIG, 0, 1, 2, 1208, 0 },

  { 605, "studenttemplate/Outputs to LabVIEW/Visualization/y-yd [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, yydm), BLOCKIO_SIG, 0, 1, 2, 1210, 0 },

  { 606, "studenttemplate/Outputs to LabVIEW/Visualization/yd [m]", 0, "",
    offsetof(BlockIO_StudentTemplate, ydm), BLOCKIO_SIG, 0, 1, 2, 1212, 0 },

  { 607, "studenttemplate/Outputs to LabVIEW/Visualization/y_plot", 0, "",
    offsetof(BlockIO_StudentTemplate, y_plot), BLOCKIO_SIG, 20, 3, 2, 1214, 0 },

  { 608, "studenttemplate/Outputs to LabVIEW/Visualization/splot", 0, "",
    offsetof(BlockIO_StudentTemplate, splot), BLOCKIO_SIG, 0, 1, 2, 1216, 0 },

  { 609,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator",
    0, "", offsetof(BlockIO_StudentTemplate, Integrator_p), BLOCKIO_SIG, 20, 3,
    2, 1218, 0 },

  { 610,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator1",
    0, "", offsetof(BlockIO_StudentTemplate, Integrator1_n), BLOCKIO_SIG, 20, 3,
    2, 1220, 0 },

  { 611,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11",
    0, "", offsetof(BlockIO_StudentTemplate, R11_e), BLOCKIO_SIG, 0, 1, 2, 1222,
    0 },

  { 612,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21",
    0, "", offsetof(BlockIO_StudentTemplate, R21_a), BLOCKIO_SIG, 0, 1, 2, 1224,
    0 },

  { 613,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12",
    0, "", offsetof(BlockIO_StudentTemplate, R12_h), BLOCKIO_SIG, 0, 1, 2, 1226,
    0 },

  { 614,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22",
    0, "", offsetof(BlockIO_StudentTemplate, R22_e), BLOCKIO_SIG, 0, 1, 2, 1228,
    0 },

  { 615,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)",
    0, "", offsetof(BlockIO_StudentTemplate, Rpsi_h), BLOCKIO_SIG, 22, 9, 2,
    1230, 0 },

  { 616,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product1",
    0, "", offsetof(BlockIO_StudentTemplate, Product1_ku), BLOCKIO_SIG, 20, 3, 2,
    1232, 0 },

  { 617,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_jz), BLOCKIO_SIG, 20, 3, 2,
    1234, 0 },

  { 618,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product2",
    0, "", offsetof(BlockIO_StudentTemplate, Product2_fu), BLOCKIO_SIG, 20, 3, 2,
    1236, 0 },

  { 619,
    "studenttemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product3",
    0, "", offsetof(BlockIO_StudentTemplate, Product3_l), BLOCKIO_SIG, 20, 3, 2,
    1238, 0 },

  { 620,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1",
    0, "", offsetof(BlockIO_StudentTemplate, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1240, 0 },

  { 621,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2",
    0, "", offsetof(BlockIO_StudentTemplate, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1242, 0 },

  { 622, "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Add",
    0, "", offsetof(BlockIO_StudentTemplate, Add_j), BLOCKIO_SIG, 0, 1, 2, 1244,
    0 },

  { 623,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1",
    0, "", offsetof(BlockIO_StudentTemplate, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1246, 0 },

  { 624,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2",
    0, "", offsetof(BlockIO_StudentTemplate, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1248, 0 },

  { 625, "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg",
    0, "", offsetof(BlockIO_StudentTemplate, Neg), BLOCKIO_SIG, 0, 1, 2, 1250, 0
  },

  { 626, "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_f), BLOCKIO_SIG, 0, 1, 2, 1252,
    0 },

  { 627, "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum2",
    0, "", offsetof(BlockIO_StudentTemplate, Sum2_i), BLOCKIO_SIG, 0, 1, 2, 1254,
    0 },

  { 628,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_StudentTemplate, Switch_j), BLOCKIO_SIG, 0, 1, 2,
    1256, 0 },

  { 629,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch2",
    0, "", offsetof(BlockIO_StudentTemplate, Switch2_o), BLOCKIO_SIG, 0, 1, 2,
    1258, 0 },

  { 630,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch",
    0, "", offsetof(BlockIO_StudentTemplate, Switch_ei), BLOCKIO_SIG, 0, 1, 2,
    1260, 0 },

  { 631,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch2",
    0, "", offsetof(BlockIO_StudentTemplate, Switch2_g), BLOCKIO_SIG, 0, 1, 2,
    1262, 0 },

  { 632,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch",
    0, "", offsetof(BlockIO_StudentTemplate, Switch_a), BLOCKIO_SIG, 0, 1, 2,
    1264, 0 },

  { 633,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch2",
    0, "", offsetof(BlockIO_StudentTemplate, Switch2_i), BLOCKIO_SIG, 0, 1, 2,
    1266, 0 },

  { 634,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sign",
    0, "", offsetof(BlockIO_StudentTemplate, Sign_gy), BLOCKIO_SIG, 0, 1, 2,
    1268, 0 },

  { 635,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product1",
    0, "Port VPS_X", offsetof(BlockIO_StudentTemplate, PortVPS_X), BLOCKIO_SIG,
    0, 1, 2, 1270, 0 },

  { 636,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x",
    0, "Port VPS_X", offsetof(BlockIO_StudentTemplate, PortVPS_X_e), BLOCKIO_SIG,
    0, 1, 2, 1272, 0 },

  { 637,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product2",
    0, "Port VSP_Y", offsetof(BlockIO_StudentTemplate, PortVSP_Y), BLOCKIO_SIG,
    0, 1, 2, 1274, 0 },

  { 638,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y",
    0, "Port VSP_Y", offsetof(BlockIO_StudentTemplate, PortVSP_Y_h), BLOCKIO_SIG,
    0, 1, 2, 1276, 0 },

  { 639,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product3",
    0, "Starboard VSP_X", offsetof(BlockIO_StudentTemplate, StarboardVSP_X),
    BLOCKIO_SIG, 0, 1, 2, 1278, 0 },

  { 640,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product4",
    0, "Starboard VSP_Y", offsetof(BlockIO_StudentTemplate, StarboardVSP_Y),
    BLOCKIO_SIG, 0, 1, 2, 1280, 0 },

  { 641,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1",
    0, "", offsetof(BlockIO_StudentTemplate, Servo1), BLOCKIO_SIG, 0, 1, 2, 1282,
    0 },

  { 642,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2",
    0, "", offsetof(BlockIO_StudentTemplate, Servo2), BLOCKIO_SIG, 0, 1, 2, 1284,
    0 },

  { 643,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3",
    0, "", offsetof(BlockIO_StudentTemplate, Servo3), BLOCKIO_SIG, 0, 1, 2, 1286,
    0 },

  { 644,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4",
    0, "", offsetof(BlockIO_StudentTemplate, Servo4), BLOCKIO_SIG, 0, 1, 2, 1288,
    0 },

  { 645,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain",
    0, "", offsetof(BlockIO_StudentTemplate, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1,
    2, 1290, 0 },

  { 646,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_c), BLOCKIO_SIG, 0, 1, 2, 1292,
    0 },

  { 647,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port",
    0, "", offsetof(BlockIO_StudentTemplate, VSPSPort), BLOCKIO_SIG, 0, 1, 2,
    1294, 0 },

  { 648,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard",
    0, "", offsetof(BlockIO_StudentTemplate, VSPSStarboard), BLOCKIO_SIG, 0, 1,
    2, 1296, 0 },

  { 649,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12",
    0, "", offsetof(BlockIO_StudentTemplate, S12_p), BLOCKIO_SIG, 31, 1, 2, 1298,
    0 },

  { 650,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S_2(psi_d^s^2)",
    0, "", offsetof(BlockIO_StudentTemplate, S_2psi_ds2), BLOCKIO_SIG, 24, 4, 2,
    1300, 0 },

  { 651,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12",
    0, "", offsetof(BlockIO_StudentTemplate, S12_e), BLOCKIO_SIG, 31, 1, 2, 1302,
    0 },

  { 652,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S_2(psi_d^s)",
    0, "", offsetof(BlockIO_StudentTemplate, S_2psi_ds), BLOCKIO_SIG, 24, 4, 2,
    1304, 0 },

  { 653,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R11",
    0, "", offsetof(BlockIO_StudentTemplate, R11_j), BLOCKIO_SIG, 0, 1, 2, 1306,
    0 },

  { 654,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R21",
    0, "", offsetof(BlockIO_StudentTemplate, R21_n), BLOCKIO_SIG, 0, 1, 2, 1308,
    0 },

  { 655,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12",
    0, "", offsetof(BlockIO_StudentTemplate, R12_k), BLOCKIO_SIG, 0, 1, 2, 1310,
    0 },

  { 656,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22",
    0, "", offsetof(BlockIO_StudentTemplate, R22_j), BLOCKIO_SIG, 0, 1, 2, 1312,
    0 },

  { 657,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R_2(psi_d)",
    0, "", offsetof(BlockIO_StudentTemplate, R_2psi_d), BLOCKIO_SIG, 24, 4, 2,
    1314, 0 },

  { 658,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_StudentTemplate, Gain1_m), BLOCKIO_SIG, 39, 1, 2,
    1316, 0 },

  { 659,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_p), BLOCKIO_SIG, 39, 1, 2, 1318,
    0 },

  { 660,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_mc), BLOCKIO_SIG, 39, 1, 2,
    1320, 0 },

  { 661,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_nx), BLOCKIO_SIG, 39, 1, 2,
    1322, 0 },

  { 662,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_o2), BLOCKIO_SIG, 39, 1, 2,
    1324, 0 },

  { 663,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_StudentTemplate, Gain1_a), BLOCKIO_SIG, 39, 1, 2,
    1326, 0 },

  { 664,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_li), BLOCKIO_SIG, 39, 1, 2,
    1328, 0 },

  { 665,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_StudentTemplate, Gain1_c), BLOCKIO_SIG, 15, 1, 2,
    1330, 0 },

  { 666,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_ol), BLOCKIO_SIG, 15, 1, 2,
    1332, 0 },

  { 667,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_f0), BLOCKIO_SIG, 15, 1, 2,
    1334, 0 },

  { 668,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_ld), BLOCKIO_SIG, 15, 1, 2,
    1336, 0 },

  { 669,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_StudentTemplate, Gain_lg), BLOCKIO_SIG, 15, 1, 2,
    1338, 0 },

  { 670,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_StudentTemplate, Gain1_h), BLOCKIO_SIG, 15, 1, 2,
    1340, 0 },

  { 671,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_StudentTemplate, Sum_k), BLOCKIO_SIG, 15, 1, 2, 1342,
    0 },

  { 672,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare), BLOCKIO_SIG, 38, 1, 2,
    1344, 0 },

  { 673,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_c), BLOCKIO_SIG, 38, 1, 2,
    1346, 0 },

  { 674,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_g), BLOCKIO_SIG, 38, 1, 2,
    1348, 0 },

  { 675,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_a), BLOCKIO_SIG, 38, 1, 2,
    1350, 0 },

  { 676,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_e), BLOCKIO_SIG, 38, 1, 2,
    1352, 0 },

  { 677,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_j), BLOCKIO_SIG, 38, 1, 2,
    1354, 0 },

  { 678,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_l), BLOCKIO_SIG, 38, 1, 2,
    1356, 0 },

  { 679,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_b), BLOCKIO_SIG, 38, 1, 2,
    1358, 0 },

  { 680,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_gl), BLOCKIO_SIG, 38, 1, 2,
    1360, 0 },

  { 681,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_gl1), BLOCKIO_SIG, 38, 1, 2,
    1362, 0 },

  { 682,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_cv), BLOCKIO_SIG, 3, 1, 2,
    1364, 0 },

  { 683,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_ev), BLOCKIO_SIG, 3, 1, 2,
    1366, 0 },

  { 684,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_i), BLOCKIO_SIG, 3, 1, 2,
    1368, 0 },

  { 685,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_StudentTemplate, Sum1_kz), BLOCKIO_SIG, 3, 1, 2,
    1370, 0 },

  { 686,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_o), BLOCKIO_SIG, 3, 1, 2,
    1372, 0 },

  { 687,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_i4), BLOCKIO_SIG, 3, 1, 2,
    1374, 0 },

  { 688,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_p), BLOCKIO_SIG, 3, 1, 2,
    1376, 0 },

  { 689,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_n), BLOCKIO_SIG, 3, 1, 2,
    1378, 0 },

  { 690,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_a), BLOCKIO_SIG, 3, 1, 2,
    1380, 0 },

  { 691,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_StudentTemplate, Compare_ln), BLOCKIO_SIG, 3, 1, 2,
    1382, 0 },

  { 692,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/LowerRelop1",
    0, "", offsetof(BlockIO_StudentTemplate, LowerRelop1), BLOCKIO_SIG, 8, 1, 2,
    1384, 0 },

  { 693,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/UpperRelop",
    0, "", offsetof(BlockIO_StudentTemplate, UpperRelop), BLOCKIO_SIG, 8, 1, 2,
    1386, 0 },

  { 694,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/LowerRelop1",
    0, "", offsetof(BlockIO_StudentTemplate, LowerRelop1_e), BLOCKIO_SIG, 8, 1,
    2, 1388, 0 },

  { 695,
    "studenttemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/UpperRelop",
    0, "", offsetof(BlockIO_StudentTemplate, UpperRelop_c), BLOCKIO_SIG, 8, 1, 2,
    1390, 0 },

  { 696,
    "studenttemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_StudentTemplate, LogicalOperator), BLOCKIO_SIG, 40,
    1, 2, 1392, 0 },

  { 697,
    "studenttemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_StudentTemplate, LogicalOperator_o), BLOCKIO_SIG, 8,
    1, 2, 1394, 0 },

  { 698,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_StudentTemplate, LowerRelop1_p), BLOCKIO_SIG, 8, 1,
    2, 1396, 0 },

  { 699,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_StudentTemplate, UpperRelop_h), BLOCKIO_SIG, 8, 1, 2,
    1398, 0 },

  { 700,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/LowerRelop1",
    0, "", offsetof(BlockIO_StudentTemplate, LowerRelop1_o), BLOCKIO_SIG, 8, 1,
    2, 1400, 0 },

  { 701,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/UpperRelop",
    0, "", offsetof(BlockIO_StudentTemplate, UpperRelop_n), BLOCKIO_SIG, 8, 1, 2,
    1402, 0 },

  { 702,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/LowerRelop1",
    0, "", offsetof(BlockIO_StudentTemplate, LowerRelop1_j), BLOCKIO_SIG, 8, 1,
    2, 1404, 0 },

  { 703,
    "studenttemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/UpperRelop",
    0, "", offsetof(BlockIO_StudentTemplate, UpperRelop_nc), BLOCKIO_SIG, 8, 1,
    2, 1406, 0 },

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

static char* NI_CompiledModelName = "studenttemplate";
static char* NI_CompiledModelVersion = "1.119";
static char* NI_CompiledModelDateTime = "Wed Apr 02 20:33:14 2014";

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
   The undef allows us to access the real StudentTemplate_P
   In the rest of the code StudentTemplate_P is redefine to be the read-side
   of rtParameter.
 */
#undef StudentTemplate_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &StudentTemplate_P, sizeof(Parameters_StudentTemplate));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka StudentTemplate_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_StudentTemplate));
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
             (Parameters_StudentTemplate));

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
           (Parameters_StudentTemplate));
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

#endif                                 // of NI_ROOTMODEL_StudentTemplate
