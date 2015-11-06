/*
 * TemplateNIPID.c
 *
 * Real-Time Workshop code generation for Simulink model "TemplateNIPID.mdl".
 *
 * Model Version              : 1.113
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 30 14:31:26 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TemplateNIPID.h"
#include "TemplateNIPID_private.h"

/* Block signals (auto storage) */
BlockIO_TemplateNIPID TemplateNIPID_B;

/* Continuous states */
ContinuousStates_TemplateNIPID TemplateNIPID_X;

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
D_Work_TemplateNIPID TemplateNIPID_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_TemplateNIPID TemplateNIPID_PrevZCSigState;

/* Real-time model */
RT_MODEL_TemplateNIPID TemplateNIPID_M_;
RT_MODEL_TemplateNIPID *TemplateNIPID_M = &TemplateNIPID_M_;

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
  int_T nXc = 23;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y,x,
                nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  TemplateNIPID_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  TemplateNIPID_output(0);
  TemplateNIPID_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE5_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  TemplateNIPID_output(0);
  TemplateNIPID_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE5_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  TemplateNIPID_output(0);
  TemplateNIPID_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++)
    hB[i] = h * rt_ODE5_B[3][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  TemplateNIPID_output(0);
  TemplateNIPID_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++)
    hB[i] = h * rt_ODE5_B[4][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  TemplateNIPID_output(0);
  TemplateNIPID_derivatives();

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
void TemplateNIPID_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(TemplateNIPID_M)) {
    TemplateNIPID_M->Timing.t[0] = rtsiGetT(&TemplateNIPID_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&TemplateNIPID_M->solverInfo,
                          ((TemplateNIPID_M->Timing.clockTick0+1)*
      TemplateNIPID_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp;
    real_T tmp_0[7];
    int32_T i;
    real_T tmp_1[9];
    real_T tmp_2[4];
    real_T tmp_3[9];
    real_T tmp_4[6];
    real_T tmp_5[18];
    int32_T tmp_6;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Constant: '<S1>/tauyawscale' */
      TemplateNIPID_B.tauyawscale = TemplateNIPID_P.tauyawscale_Value;

      /* Constant: '<S4>/Initial psi [rad]' */
      TemplateNIPID_B.Initialpsirad = TemplateNIPID_P.Initialpsirad_Value;

      /* Constant: '<S4>/Initial x [m]' */
      TemplateNIPID_B.Initialxm = TemplateNIPID_P.Initialxm_Value;

      /* Constant: '<S4>/Initial y [m]' */
      TemplateNIPID_B.Initialym = TemplateNIPID_P.Initialym_Value;

      /* Constant: '<S4>/Initial r [rad//s]' */
      TemplateNIPID_B.Initialrrads = TemplateNIPID_P.Initialrrads_Value;

      /* Constant: '<S4>/Initial u [m//s]' */
      TemplateNIPID_B.Initialums = TemplateNIPID_P.Initialums_Value;

      /* Constant: '<S4>/Initial v [m//s]' */
      TemplateNIPID_B.Initialvms = TemplateNIPID_P.Initialvms_Value;

      /* Gain: '<S6>/ScalingLX' incorporates:
       *  Constant: '<S6>/AS_LX [-] '
       */
      TemplateNIPID_B.xpositionofleftanalogstick11 =
        TemplateNIPID_P.ScalingLX_Gain * TemplateNIPID_P.AS_LX_Value;

      /* Gain: '<S6>/ScalingLY' incorporates:
       *  Constant: '<S6>/AS_LY [-]'
       */
      TemplateNIPID_B.ypositionofleftanalogstick11 =
        TemplateNIPID_P.ScalingLY_Gain * TemplateNIPID_P.AS_LY_Value;

      /* Gain: '<S6>/Scaling_RX' incorporates:
       *  Constant: '<S6>/AS_RX [-]'
       */
      TemplateNIPID_B.xpositionofrightanalogstick11 =
        TemplateNIPID_P.Scaling_RX_Gain * TemplateNIPID_P.AS_RX_Value;

      /* Gain: '<S6>/ScalingRY' incorporates:
       *  Constant: '<S6>/AS_RY [-]'
       */
      TemplateNIPID_B.ypositionofrightanalogstick11 =
        TemplateNIPID_P.ScalingRY_Gain * TemplateNIPID_P.AS_RY_Value;

      /* Gain: '<S12>/Gain1' incorporates:
       *  Constant: '<S7>/setpointpsi [deg]'
       */
      TemplateNIPID_B.Gain1 = TemplateNIPID_P.Gain1_Gain *
        TemplateNIPID_P.setpointpsideg_Value;

      /* Constant: '<S7>/setpointx [m]' */
      TemplateNIPID_B.setpointxm = TemplateNIPID_P.setpointxm_Value;

      /* Constant: '<S7>/setpointy [m]' */
      TemplateNIPID_B.setpointym = TemplateNIPID_P.setpointym_Value;

      /* Constant: '<S8>/ctrl1Kppsi' */
      TemplateNIPID_B.ctrl1Kppsi = TemplateNIPID_P.ctrl1Kppsi_Value;

      /* Constant: '<S8>/ctrl1Kipsi' */
      TemplateNIPID_B.ctrl1Kipsi = TemplateNIPID_P.ctrl1Kipsi_Value;

      /* Constant: '<S8>/ctrl1 Reset Integrator ' */
      TemplateNIPID_B.ctrl1ResetIntegrator =
        TemplateNIPID_P.ctrl1ResetIntegrator_Value;

      /* Reshape: '<S13>/[2x2]' incorporates:
       *  Constant: '<S13>/12'
       *  Constant: '<S13>/21'
       *  Constant: '<S9>/Gamma_q_Surge'
       *  Constant: '<S9>/Gamma_q_Sway'
       */
      TemplateNIPID_B.ux2[0] = TemplateNIPID_P.Gamma_q_Surge_Value;
      TemplateNIPID_B.ux2[1] = TemplateNIPID_P.u_Value_k;
      TemplateNIPID_B.ux2[2] = TemplateNIPID_P.u_Value;
      TemplateNIPID_B.ux2[3] = TemplateNIPID_P.Gamma_q_Sway_Value;

      /* Constant: '<S9>/Initial q_x' */
      TemplateNIPID_B.Initialq_x = TemplateNIPID_P.Initialq_x_Value;

      /* Constant: '<S9>/Initial q_y' */
      TemplateNIPID_B.Initialq_y = TemplateNIPID_P.Initialq_y_Value;

      /* Constant: '<S9>/Initial s' */
      TemplateNIPID_B.Initials = TemplateNIPID_P.Initials_Value;

      /* Reshape: '<S14>/[3x3]' incorporates:
       *  Constant: '<S14>/12'
       *  Constant: '<S14>/13'
       *  Constant: '<S14>/21'
       *  Constant: '<S14>/23'
       *  Constant: '<S14>/31'
       *  Constant: '<S14>/32'
       *  Constant: '<S9>/ctrl2Kdpsi'
       *  Constant: '<S9>/ctrl2Kdx'
       *  Constant: '<S9>/ctrl2Kdy'
       */
      TemplateNIPID_B.ux3[0] = TemplateNIPID_P.ctrl2Kdx_Value;
      TemplateNIPID_B.ux3[1] = TemplateNIPID_P.u_Value_c;
      TemplateNIPID_B.ux3[2] = TemplateNIPID_P.u_Value_b;
      TemplateNIPID_B.ux3[3] = TemplateNIPID_P.u_Value_l;
      TemplateNIPID_B.ux3[4] = TemplateNIPID_P.ctrl2Kdy_Value;
      TemplateNIPID_B.ux3[5] = TemplateNIPID_P.u_Value_f;
      TemplateNIPID_B.ux3[6] = TemplateNIPID_P.u_Value_a;
      TemplateNIPID_B.ux3[7] = TemplateNIPID_P.u_Value_o;
      TemplateNIPID_B.ux3[8] = TemplateNIPID_P.ctrl2Kdpsi_Value;

      /* Reshape: '<S15>/[3x3]' incorporates:
       *  Constant: '<S15>/12'
       *  Constant: '<S15>/13'
       *  Constant: '<S15>/21'
       *  Constant: '<S15>/23'
       *  Constant: '<S15>/31'
       *  Constant: '<S15>/32'
       *  Constant: '<S9>/ctrl2Kipsi'
       *  Constant: '<S9>/ctrl2Kix'
       *  Constant: '<S9>/ctrl2Kiy'
       */
      TemplateNIPID_B.ux3_c[0] = TemplateNIPID_P.ctrl2Kix_Value;
      TemplateNIPID_B.ux3_c[1] = TemplateNIPID_P.u_Value_d;
      TemplateNIPID_B.ux3_c[2] = TemplateNIPID_P.u_Value_n;
      TemplateNIPID_B.ux3_c[3] = TemplateNIPID_P.u_Value_lr;
      TemplateNIPID_B.ux3_c[4] = TemplateNIPID_P.ctrl2Kiy_Value;
      TemplateNIPID_B.ux3_c[5] = TemplateNIPID_P.u_Value_jc;
      TemplateNIPID_B.ux3_c[6] = TemplateNIPID_P.u_Value_j;
      TemplateNIPID_B.ux3_c[7] = TemplateNIPID_P.u_Value_g;
      TemplateNIPID_B.ux3_c[8] = TemplateNIPID_P.ctrl2Kipsi_Value;

      /* Reshape: '<S16>/[3x3]' incorporates:
       *  Constant: '<S16>/12'
       *  Constant: '<S16>/13'
       *  Constant: '<S16>/21'
       *  Constant: '<S16>/23'
       *  Constant: '<S16>/31'
       *  Constant: '<S16>/32'
       *  Constant: '<S9>/ctrl2Kppsi'
       *  Constant: '<S9>/ctrl2Kpx'
       *  Constant: '<S9>/ctrl2Kpy'
       */
      TemplateNIPID_B.ux3_p[0] = TemplateNIPID_P.ctrl2Kpx_Value;
      TemplateNIPID_B.ux3_p[1] = TemplateNIPID_P.u_Value_eu;
      TemplateNIPID_B.ux3_p[2] = TemplateNIPID_P.u_Value_p;
      TemplateNIPID_B.ux3_p[3] = TemplateNIPID_P.u_Value_e;
      TemplateNIPID_B.ux3_p[4] = TemplateNIPID_P.ctrl2Kpy_Value;
      TemplateNIPID_B.ux3_p[5] = TemplateNIPID_P.u_Value_bp;
      TemplateNIPID_B.ux3_p[6] = TemplateNIPID_P.u_Value_ox;
      TemplateNIPID_B.ux3_p[7] = TemplateNIPID_P.u_Value_dc;
      TemplateNIPID_B.ux3_p[8] = TemplateNIPID_P.ctrl2Kppsi_Value;

      /* Gain: '<S25>/-l_x1' incorporates:
       *  Constant: '<S25>/l_x1'
       */
      TemplateNIPID_B.l_x1 = TemplateNIPID_P.l_x1_Gain *
        TemplateNIPID_P.l_x1_Value;

      /* Gain: '<S25>/-l_x2' incorporates:
       *  Constant: '<S25>/l_x2'
       */
      TemplateNIPID_B.l_x2 = TemplateNIPID_P.l_x2_Gain *
        TemplateNIPID_P.l_x2_Value;

      /* Gain: '<S25>/-l_y2' incorporates:
       *  Constant: '<S25>/l_y2'
       */
      TemplateNIPID_B.l_y2 = TemplateNIPID_P.l_y2_Gain *
        TemplateNIPID_P.l_y2_Value;

      /* Reshape: '<S25>/3x5' incorporates:
       *  Constant: '<S25>/B_11'
       *  Constant: '<S25>/B_12'
       *  Constant: '<S25>/B_13'
       *  Constant: '<S25>/B_14'
       *  Constant: '<S25>/B_15'
       *  Constant: '<S25>/B_21'
       *  Constant: '<S25>/B_22'
       *  Constant: '<S25>/B_23'
       *  Constant: '<S25>/B_24'
       *  Constant: '<S25>/B_25'
       *  Constant: '<S25>/l_x3'
       *  Constant: '<S25>/l_y1'
       */
      TemplateNIPID_B.x5[0] = TemplateNIPID_P.B_11_Value;
      TemplateNIPID_B.x5[1] = TemplateNIPID_P.B_21_Value;
      TemplateNIPID_B.x5[2] = TemplateNIPID_P.l_y1_Value;
      TemplateNIPID_B.x5[3] = TemplateNIPID_P.B_12_Value;
      TemplateNIPID_B.x5[4] = TemplateNIPID_P.B_22_Value;
      TemplateNIPID_B.x5[5] = TemplateNIPID_B.l_x1;
      TemplateNIPID_B.x5[6] = TemplateNIPID_P.B_13_Value;
      TemplateNIPID_B.x5[7] = TemplateNIPID_P.B_23_Value;
      TemplateNIPID_B.x5[8] = TemplateNIPID_B.l_y2;
      TemplateNIPID_B.x5[9] = TemplateNIPID_P.B_14_Value;
      TemplateNIPID_B.x5[10] = TemplateNIPID_P.B_24_Value;
      TemplateNIPID_B.x5[11] = TemplateNIPID_B.l_x2;
      TemplateNIPID_B.x5[12] = TemplateNIPID_P.B_15_Value;
      TemplateNIPID_B.x5[13] = TemplateNIPID_P.B_25_Value;
      TemplateNIPID_B.x5[14] = TemplateNIPID_P.l_x3_Value;

      /* Gain: '<S24>/-N_r' incorporates:
       *  Constant: '<S24>/N_r'
       */
      TemplateNIPID_B.N_r = TemplateNIPID_P.N_r_Gain * TemplateNIPID_P.N_r_Value;

      /* Gain: '<S24>/-N_v' incorporates:
       *  Constant: '<S24>/N_v'
       */
      TemplateNIPID_B.N_v = TemplateNIPID_P.N_v_Gain * TemplateNIPID_P.N_v_Value;

      /* Gain: '<S24>/-X_u' incorporates:
       *  Constant: '<S24>/X_u'
       */
      TemplateNIPID_B.X_u = TemplateNIPID_P.X_u_Gain * TemplateNIPID_P.X_u_Value;

      /* Gain: '<S24>/-Y_v' incorporates:
       *  Constant: '<S24>/Y_v'
       */
      TemplateNIPID_B.Y_v = TemplateNIPID_P.Y_v_Gain * TemplateNIPID_P.Y_v_Value;

      /* Gain: '<S24>/-Y_vr' incorporates:
       *  Constant: '<S24>/Y_r'
       */
      TemplateNIPID_B.Y_vr = TemplateNIPID_P.Y_vr_Gain *
        TemplateNIPID_P.Y_r_Value;

      /* Reshape: '<S24>/Linear Dampning matrix' incorporates:
       *  Constant: '<S24>/D_L_12'
       *  Constant: '<S24>/D_L_13'
       *  Constant: '<S24>/D_L_21'
       *  Constant: '<S24>/D_L_31'
       */
      TemplateNIPID_B.LinearDampningmatrix[0] = TemplateNIPID_B.X_u;
      TemplateNIPID_B.LinearDampningmatrix[1] = TemplateNIPID_P.D_L_21_Value;
      TemplateNIPID_B.LinearDampningmatrix[2] = TemplateNIPID_P.D_L_31_Value;
      TemplateNIPID_B.LinearDampningmatrix[3] = TemplateNIPID_P.D_L_12_Value;
      TemplateNIPID_B.LinearDampningmatrix[4] = TemplateNIPID_B.Y_v;
      TemplateNIPID_B.LinearDampningmatrix[5] = TemplateNIPID_B.N_v;
      TemplateNIPID_B.LinearDampningmatrix[6] = TemplateNIPID_P.D_L_13_Value;
      TemplateNIPID_B.LinearDampningmatrix[7] = TemplateNIPID_B.Y_vr;
      TemplateNIPID_B.LinearDampningmatrix[8] = TemplateNIPID_B.N_r;

      /* Sum: '<S23>/M_11' incorporates:
       *  Constant: '<S23>/X_udot'
       *  Constant: '<S23>/m'
       */
      TemplateNIPID_B.M_11 = TemplateNIPID_P.m_Value -
        TemplateNIPID_P.X_udot_Value;

      /* Sum: '<S23>/M_22' incorporates:
       *  Constant: '<S23>/Y_vdot'
       *  Constant: '<S23>/m'
       */
      TemplateNIPID_B.M_22 = TemplateNIPID_P.m_Value -
        TemplateNIPID_P.Y_vdot_Value;

      /* Product: '<S23>/m x_g' incorporates:
       *  Constant: '<S23>/m'
       *  Constant: '<S23>/x_g'
       */
      TemplateNIPID_B.mx_g = TemplateNIPID_P.m_Value * TemplateNIPID_P.x_g_Value;

      /* Sum: '<S23>/M_32' incorporates:
       *  Constant: '<S23>/N_vdot'
       */
      TemplateNIPID_B.M_32 = TemplateNIPID_B.mx_g - TemplateNIPID_P.N_vdot_Value;

      /* Sum: '<S23>/M_23' incorporates:
       *  Constant: '<S23>/Y_rdot'
       */
      TemplateNIPID_B.M_23 = TemplateNIPID_B.mx_g - TemplateNIPID_P.Y_rdot_Value;

      /* Sum: '<S23>/M_33' incorporates:
       *  Constant: '<S23>/I_z'
       *  Constant: '<S23>/N_rdot'
       */
      TemplateNIPID_B.M_33 = TemplateNIPID_P.I_z_Value -
        TemplateNIPID_P.N_rdot_Value;

      /* Reshape: '<S23>/3x3' incorporates:
       *  Constant: '<S23>/M_12'
       *  Constant: '<S23>/M_13'
       *  Constant: '<S23>/M_21'
       *  Constant: '<S23>/M_31'
       */
      TemplateNIPID_B.x3[0] = TemplateNIPID_B.M_11;
      TemplateNIPID_B.x3[1] = TemplateNIPID_P.M_21_Value;
      TemplateNIPID_B.x3[2] = TemplateNIPID_P.M_31_Value;
      TemplateNIPID_B.x3[3] = TemplateNIPID_P.M_12_Value;
      TemplateNIPID_B.x3[4] = TemplateNIPID_B.M_22;
      TemplateNIPID_B.x3[5] = TemplateNIPID_B.M_32;
      TemplateNIPID_B.x3[6] = TemplateNIPID_P.M_13_Value;
      TemplateNIPID_B.x3[7] = TemplateNIPID_B.M_23;
      TemplateNIPID_B.x3[8] = TemplateNIPID_B.M_33;

      /* Gain: '<S28>/PS3 u_1' */
      TemplateNIPID_B.u_1 = TemplateNIPID_P.PS3u_1_Gain *
        TemplateNIPID_B.ypositionofleftanalogstick11;

      /* Lookup Block: '<S67>/u_1 to f_1'
       * About '<S67>/u_1 to f_1 :'
       * Lookup Block: '<S67>/u_1 to f_1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_1tof_1),
                           TemplateNIPID_P.u_1tof_1_YData, TemplateNIPID_B.u_1,
                           TemplateNIPID_P.u_1tof_1_XData, 38U);

      /* Gain: '<S28>/PS3 u_2' */
      TemplateNIPID_B.u_2 = TemplateNIPID_P.PS3u_2_Gain *
        TemplateNIPID_B.xpositionofleftanalogstick11;

      /* RelationalOperator: '<S72>/Compare' incorporates:
       *  Constant: '<S72>/Constant'
       */
      TemplateNIPID_B.Compare = (TemplateNIPID_B.u_2 <
        TemplateNIPID_P.Constant_Value);

      /* RelationalOperator: '<S74>/Compare' incorporates:
       *  Constant: '<S74>/Constant'
       */
      TemplateNIPID_B.Compare_i = (TemplateNIPID_B.u_2 >=
        TemplateNIPID_P.Constant_Value_l);

      /* RelationalOperator: '<S73>/Compare' incorporates:
       *  Constant: '<S73>/Constant'
       */
      TemplateNIPID_B.Compare_g = (TemplateNIPID_B.u_2 <
        TemplateNIPID_P.Constant_Value_m);

      /* Logic: '<S68>/Logical Operator' */
      TemplateNIPID_B.LogicalOperator = ((TemplateNIPID_B.Compare_i != 0) &&
        (TemplateNIPID_B.Compare_g != 0));

      /* Sum: '<S68>/Sum1' */
      TemplateNIPID_B.Sum1_k = (uint8_T)(TemplateNIPID_B.LogicalOperator +
        TemplateNIPID_B.LogicalOperator);

      /* RelationalOperator: '<S75>/Compare' incorporates:
       *  Constant: '<S75>/Constant'
       */
      TemplateNIPID_B.Compare_l = (TemplateNIPID_B.u_2 >=
        TemplateNIPID_P.Constant_Value_p);

      /* Gain: '<S68>/Gain1' */
      TemplateNIPID_B.Gain1_f = (uint16_T)(TemplateNIPID_P.Gain1_Gain_g *
        TemplateNIPID_B.Compare_l);

      /* Sum: '<S68>/Sum' */
      TemplateNIPID_B.Sum_ku = (uint16_T)(uint32_T)(((TemplateNIPID_B.Compare <<
        6) + (TemplateNIPID_B.Sum1_k << 6)) + TemplateNIPID_B.Gain1_f);

      /* Lookup Block: '<S68>/u_2 < -0.5'
       * About '<S68>/u_2 < -0.5 :'
       * Lookup Block: '<S68>/u_2 < -0.5'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_205),
                           TemplateNIPID_P.u_205_YData, TemplateNIPID_B.u_2,
                           TemplateNIPID_P.u_205_XData, 10U);

      /* Lookup Block: '<S68>/u_2 < -0.1 && u_2 >= -0.2'
       * About '<S68>/u_2 < -0.1 && u_2 >= -0.2 :'
       * Lookup Block: '<S68>/u_2 < -0.1 && u_2 >= -0.2'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_201u_202),
                           TemplateNIPID_P.u_201u_202_YData, TemplateNIPID_B.u_2,
                           TemplateNIPID_P.u_201u_202_XData, 2U);

      /* Lookup Block: '<S68>/u_2 => 0'
       * About '<S68>/u_2 => 0 :'
       * Lookup Block: '<S68>/u_2 => 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_20), TemplateNIPID_P.u_20_YData,
                           TemplateNIPID_B.u_2, TemplateNIPID_P.u_20_XData, 17U);

      /* MultiPortSwitch: '<S68>/Multiport Switch' */
      switch ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_ku >> 6)) {
       case 1:
        TemplateNIPID_B.MultiportSwitch = TemplateNIPID_B.u_205;
        break;

       case 2:
        TemplateNIPID_B.MultiportSwitch = TemplateNIPID_B.u_201u_202;
        break;

       default:
        TemplateNIPID_B.MultiportSwitch = TemplateNIPID_B.u_20;
        break;
      }

      /* Gain: '<S28>/PS3 u_3' */
      TemplateNIPID_B.u_3 = TemplateNIPID_P.PS3u_3_Gain *
        TemplateNIPID_B.ypositionofrightanalogstick11;

      /* Lookup Block: '<S69>/u_3 to f_3'
       * About '<S69>/u_3 to f_3 :'
       * Lookup Block: '<S69>/u_3 to f_3'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_3tof_3),
                           TemplateNIPID_P.u_3tof_3_YData, TemplateNIPID_B.u_3,
                           TemplateNIPID_P.u_3tof_3_XData, 38U);

      /* Gain: '<S28>/PS3 u_4' */
      TemplateNIPID_B.u_4 = TemplateNIPID_P.PS3u_4_Gain *
        TemplateNIPID_B.xpositionofrightanalogstick11;

      /* RelationalOperator: '<S76>/Compare' incorporates:
       *  Constant: '<S76>/Constant'
       */
      TemplateNIPID_B.Compare_la = (TemplateNIPID_B.u_4 <
        TemplateNIPID_P.Constant_Value_m0);

      /* RelationalOperator: '<S77>/Compare' incorporates:
       *  Constant: '<S77>/Constant'
       */
      TemplateNIPID_B.Compare_it = (TemplateNIPID_B.u_4 >=
        TemplateNIPID_P.Constant_Value_k);

      /* Gain: '<S70>/Gain' */
      TemplateNIPID_B.Gain_pm = (uint16_T)(TemplateNIPID_P.Gain_Gain_c0 *
        TemplateNIPID_B.Compare_it);

      /* Sum: '<S70>/Sum' */
      TemplateNIPID_B.Sum_h = (uint16_T)(uint32_T)((TemplateNIPID_B.Compare_la <<
        6) + TemplateNIPID_B.Gain_pm);

      /* Lookup Block: '<S70>/u_4 < -0.1'
       * About '<S70>/u_4 < -0.1 :'
       * Lookup Block: '<S70>/u_4 < -0.1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_401),
                           TemplateNIPID_P.u_401_YData, TemplateNIPID_B.u_4,
                           TemplateNIPID_P.u_401_XData, 14U);

      /* Lookup Block: '<S70>/u_4 >= -0.1'
       * About '<S70>/u_4 >= -0.1 :'
       * Lookup Block: '<S70>/u_4 >= -0.1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_401_o),
                           TemplateNIPID_P.u_401_YData_e, TemplateNIPID_B.u_4,
                           TemplateNIPID_P.u_401_XData_c, 12U);

      /* MultiPortSwitch: '<S70>/Multiport Switch' */
      if ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_h >> 6) == 1) {
        TemplateNIPID_B.MultiportSwitch_p = TemplateNIPID_B.u_401;
      } else {
        TemplateNIPID_B.MultiportSwitch_p = TemplateNIPID_B.u_401_o;
      }

      /* Sum: '<S28>/Add' incorporates:
       *  Constant: '<S6>/L2 [-]'
       *  Constant: '<S6>/R2 [-]'
       */
      TemplateNIPID_B.BowThrusterdirection = TemplateNIPID_P.L2_Value +
        TemplateNIPID_P.R2_Value;

      /* Gain: '<S28>/PS3 u_5' */
      TemplateNIPID_B.u_5 = TemplateNIPID_P.PS3u_5_Gain *
        TemplateNIPID_B.BowThrusterdirection;

      /* DeadZone Block: '<S71>/Dead Zone +-0.01'
       */
      if (TemplateNIPID_B.u_5 >= TemplateNIPID_P.DeadZone001_End) {
        TemplateNIPID_B.DeadZone001 = TemplateNIPID_B.u_5 -
          TemplateNIPID_P.DeadZone001_End;
      } else if (TemplateNIPID_B.u_5 > TemplateNIPID_P.DeadZone001_Start) {
        TemplateNIPID_B.DeadZone001 = 0.0;
      } else {
        TemplateNIPID_B.DeadZone001 = TemplateNIPID_B.u_5 -
          TemplateNIPID_P.DeadZone001_Start;
      }

      /* RelationalOperator: '<S78>/Compare' incorporates:
       *  Constant: '<S78>/Constant'
       */
      TemplateNIPID_B.Compare_o = (TemplateNIPID_B.DeadZone001 <
        TemplateNIPID_P.Constant_Value_f);

      /* RelationalOperator: '<S80>/Compare' */
      TemplateNIPID_B.Compare_le = (TemplateNIPID_B.DeadZone001 == 0.0);

      /* Gain: '<S71>/Gain' */
      TemplateNIPID_B.Gain_em = (uint16_T)(TemplateNIPID_P.Gain_Gain_k *
        TemplateNIPID_B.Compare_le);

      /* RelationalOperator: '<S79>/Compare' incorporates:
       *  Constant: '<S79>/Constant'
       */
      TemplateNIPID_B.Compare_k = (TemplateNIPID_B.DeadZone001 >
        TemplateNIPID_P.Constant_Value_c);

      /* Gain: '<S71>/Gain1' */
      TemplateNIPID_B.Gain1_h = (uint16_T)(TemplateNIPID_P.Gain1_Gain_o *
        TemplateNIPID_B.Compare_k);

      /* Sum: '<S71>/Sum' */
      TemplateNIPID_B.Sum_fd3 = (uint16_T)(uint32_T)(((TemplateNIPID_B.Compare_o
        << 6) + TemplateNIPID_B.Gain_em) + TemplateNIPID_B.Gain1_h);

      /* Lookup Block: '<S71>/u_5 < 0'
       * About '<S71>/u_5 < 0 :'
       * Lookup Block: '<S71>/u_5 < 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_50), TemplateNIPID_P.u_50_YData,
                           TemplateNIPID_B.u_5, TemplateNIPID_P.u_50_XData, 9U);

      /* Lookup Block: '<S71>/u_5 > 0'
       * About '<S71>/u_5 > 0 :'
       * Lookup Block: '<S71>/u_5 > 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_50_n),
                           TemplateNIPID_P.u_50_YData_g, TemplateNIPID_B.u_5,
                           TemplateNIPID_P.u_50_XData_j, 9U);

      /* MultiPortSwitch: '<S71>/Multiport Switch' incorporates:
       *  Constant: '<S71>/u_5 = 0'
       */
      switch ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_fd3 >> 6)) {
       case 1:
        TemplateNIPID_B.MultiportSwitch_i = TemplateNIPID_B.u_50;
        break;

       case 2:
        TemplateNIPID_B.MultiportSwitch_i = TemplateNIPID_P.u_50_Value;
        break;

       default:
        TemplateNIPID_B.MultiportSwitch_i = TemplateNIPID_B.u_50_n;
        break;
      }

      /* SignalConversion: '<S65>/TmpHiddenBufferAtProduct1Inport2' */
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inport[0] =
        TemplateNIPID_B.u_1tof_1;
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inport[1] =
        TemplateNIPID_B.MultiportSwitch;
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inport[2] =
        TemplateNIPID_B.u_3tof_3;
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inport[3] =
        TemplateNIPID_B.MultiportSwitch_p;
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inport[4] =
        TemplateNIPID_B.MultiportSwitch_i;

      /* Product: '<S65>/Product1' */
      for (i = 0; i < 3; i++) {
        TemplateNIPID_B.Product1[i] = 0.0;
        for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
          TemplateNIPID_B.Product1[i] = TemplateNIPID_B.x5[3 * tmp_6 + i] *
            TemplateNIPID_B.TmpHiddenBufferAtProduct1Inport[tmp_6] +
            TemplateNIPID_B.Product1[i];
        }
      }

      /* Lookup Block: '<S83>/u_1 to f_1'
       * About '<S83>/u_1 to f_1 :'
       * Lookup Block: '<S83>/u_1 to f_1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_1tof_1_p),
                           TemplateNIPID_P.u_1tof_1_YData_i,
                           TemplateNIPID_P.ctrl1Kpx_Value,
                           TemplateNIPID_P.u_1tof_1_XData_o, 38U);

      /* RelationalOperator: '<S88>/Compare' incorporates:
       *  Constant: '<S88>/Constant'
       *  Constant: '<S8>/ctrl1Kpy'
       */
      TemplateNIPID_B.Compare_f = (TemplateNIPID_P.ctrl1Kpy_Value <
        TemplateNIPID_P.Constant_Value_o);

      /* RelationalOperator: '<S90>/Compare' incorporates:
       *  Constant: '<S8>/ctrl1Kpy'
       *  Constant: '<S90>/Constant'
       */
      TemplateNIPID_B.Compare_b = (TemplateNIPID_P.ctrl1Kpy_Value >=
        TemplateNIPID_P.Constant_Value_a);

      /* RelationalOperator: '<S89>/Compare' incorporates:
       *  Constant: '<S89>/Constant'
       *  Constant: '<S8>/ctrl1Kpy'
       */
      TemplateNIPID_B.Compare_ii = (TemplateNIPID_P.ctrl1Kpy_Value <
        TemplateNIPID_P.Constant_Value_f5);

      /* Logic: '<S84>/Logical Operator' */
      TemplateNIPID_B.LogicalOperator_n = ((TemplateNIPID_B.Compare_b != 0) &&
        (TemplateNIPID_B.Compare_ii != 0));

      /* Sum: '<S84>/Sum1' */
      TemplateNIPID_B.Sum1_kv = (uint8_T)(TemplateNIPID_B.LogicalOperator_n +
        TemplateNIPID_B.LogicalOperator_n);

      /* RelationalOperator: '<S91>/Compare' incorporates:
       *  Constant: '<S8>/ctrl1Kpy'
       *  Constant: '<S91>/Constant'
       */
      TemplateNIPID_B.Compare_h = (TemplateNIPID_P.ctrl1Kpy_Value >=
        TemplateNIPID_P.Constant_Value_pu);

      /* Gain: '<S84>/Gain1' */
      TemplateNIPID_B.Gain1_ab = (uint16_T)(TemplateNIPID_P.Gain1_Gain_h *
        TemplateNIPID_B.Compare_h);

      /* Sum: '<S84>/Sum' */
      TemplateNIPID_B.Sum_hr = (uint16_T)(uint32_T)(((TemplateNIPID_B.Compare_f <<
        6) + (TemplateNIPID_B.Sum1_kv << 6)) + TemplateNIPID_B.Gain1_ab);

      /* Lookup Block: '<S84>/u_2 < -0.5'
       * About '<S84>/u_2 < -0.5 :'
       * Lookup Block: '<S84>/u_2 < -0.5'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_205_l),
                           TemplateNIPID_P.u_205_YData_e,
                           TemplateNIPID_P.ctrl1Kpy_Value,
                           TemplateNIPID_P.u_205_XData_c, 10U);

      /* Lookup Block: '<S84>/u_2 < -0.1 && u_2 >= -0.2'
       * About '<S84>/u_2 < -0.1 && u_2 >= -0.2 :'
       * Lookup Block: '<S84>/u_2 < -0.1 && u_2 >= -0.2'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_201u_202_o),
                           TemplateNIPID_P.u_201u_202_YData_f,
                           TemplateNIPID_P.ctrl1Kpy_Value,
                           TemplateNIPID_P.u_201u_202_XData_k, 2U);

      /* Lookup Block: '<S84>/u_2 => 0'
       * About '<S84>/u_2 => 0 :'
       * Lookup Block: '<S84>/u_2 => 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_20_p),
                           TemplateNIPID_P.u_20_YData_j,
                           TemplateNIPID_P.ctrl1Kpy_Value,
                           TemplateNIPID_P.u_20_XData_i, 17U);

      /* MultiPortSwitch: '<S84>/Multiport Switch' */
      switch ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_hr >> 6)) {
       case 1:
        TemplateNIPID_B.MultiportSwitch_iv = TemplateNIPID_B.u_205_l;
        break;

       case 2:
        TemplateNIPID_B.MultiportSwitch_iv = TemplateNIPID_B.u_201u_202_o;
        break;

       default:
        TemplateNIPID_B.MultiportSwitch_iv = TemplateNIPID_B.u_20_p;
        break;
      }

      /* Lookup Block: '<S85>/u_3 to f_3'
       * About '<S85>/u_3 to f_3 :'
       * Lookup Block: '<S85>/u_3 to f_3'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_3tof_3_b),
                           TemplateNIPID_P.u_3tof_3_YData_h,
                           TemplateNIPID_P.ctrl1Kix_Value,
                           TemplateNIPID_P.u_3tof_3_XData_g, 38U);

      /* RelationalOperator: '<S92>/Compare' incorporates:
       *  Constant: '<S8>/ctrl1Kiy'
       *  Constant: '<S92>/Constant'
       */
      TemplateNIPID_B.Compare_l3 = (TemplateNIPID_P.ctrl1Kiy_Value <
        TemplateNIPID_P.Constant_Value_ap);

      /* RelationalOperator: '<S93>/Compare' incorporates:
       *  Constant: '<S8>/ctrl1Kiy'
       *  Constant: '<S93>/Constant'
       */
      TemplateNIPID_B.Compare_e = (TemplateNIPID_P.ctrl1Kiy_Value >=
        TemplateNIPID_P.Constant_Value_lg);

      /* Gain: '<S86>/Gain' */
      TemplateNIPID_B.Gain_j = (uint16_T)(TemplateNIPID_P.Gain_Gain_pu *
        TemplateNIPID_B.Compare_e);

      /* Sum: '<S86>/Sum' */
      TemplateNIPID_B.Sum_o = (uint16_T)(uint32_T)((TemplateNIPID_B.Compare_l3 <<
        6) + TemplateNIPID_B.Gain_j);

      /* Lookup Block: '<S86>/u_4 < -0.1'
       * About '<S86>/u_4 < -0.1 :'
       * Lookup Block: '<S86>/u_4 < -0.1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_401_h),
                           TemplateNIPID_P.u_401_YData_d,
                           TemplateNIPID_P.ctrl1Kiy_Value,
                           TemplateNIPID_P.u_401_XData_n, 14U);

      /* Lookup Block: '<S86>/u_4 >= -0.1'
       * About '<S86>/u_4 >= -0.1 :'
       * Lookup Block: '<S86>/u_4 >= -0.1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_401_j),
                           TemplateNIPID_P.u_401_YData_b,
                           TemplateNIPID_P.ctrl1Kiy_Value,
                           TemplateNIPID_P.u_401_XData_g, 12U);

      /* MultiPortSwitch: '<S86>/Multiport Switch' */
      if ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_o >> 6) == 1) {
        TemplateNIPID_B.MultiportSwitch_pl = TemplateNIPID_B.u_401_h;
      } else {
        TemplateNIPID_B.MultiportSwitch_pl = TemplateNIPID_B.u_401_j;
      }

      /* DeadZone Block: '<S87>/Dead Zone +-0.01'
       */
      if (TemplateNIPID_P.ctrl1Kdx_Value >= TemplateNIPID_P.DeadZone001_End_k) {
        TemplateNIPID_B.DeadZone001_p = TemplateNIPID_P.ctrl1Kdx_Value -
          TemplateNIPID_P.DeadZone001_End_k;
      } else if (TemplateNIPID_P.ctrl1Kdx_Value >
                 TemplateNIPID_P.DeadZone001_Start_p) {
        TemplateNIPID_B.DeadZone001_p = 0.0;
      } else {
        TemplateNIPID_B.DeadZone001_p = TemplateNIPID_P.ctrl1Kdx_Value -
          TemplateNIPID_P.DeadZone001_Start_p;
      }

      /* RelationalOperator: '<S94>/Compare' incorporates:
       *  Constant: '<S94>/Constant'
       */
      TemplateNIPID_B.Compare_m = (TemplateNIPID_B.DeadZone001_p <
        TemplateNIPID_P.Constant_Value_b);

      /* RelationalOperator: '<S96>/Compare' */
      TemplateNIPID_B.Compare_iu = (TemplateNIPID_B.DeadZone001_p == 0.0);

      /* Gain: '<S87>/Gain' */
      TemplateNIPID_B.Gain_ca = (uint16_T)(TemplateNIPID_P.Gain_Gain_gy *
        TemplateNIPID_B.Compare_iu);

      /* RelationalOperator: '<S95>/Compare' incorporates:
       *  Constant: '<S95>/Constant'
       */
      TemplateNIPID_B.Compare_kv = (TemplateNIPID_B.DeadZone001_p >
        TemplateNIPID_P.Constant_Value_j);

      /* Gain: '<S87>/Gain1' */
      TemplateNIPID_B.Gain1_l = (uint16_T)(TemplateNIPID_P.Gain1_Gain_e *
        TemplateNIPID_B.Compare_kv);

      /* Sum: '<S87>/Sum' */
      TemplateNIPID_B.Sum_j = (uint16_T)(uint32_T)(((TemplateNIPID_B.Compare_m <<
        6) + TemplateNIPID_B.Gain_ca) + TemplateNIPID_B.Gain1_l);

      /* Lookup Block: '<S87>/u_5 < 0'
       * About '<S87>/u_5 < 0 :'
       * Lookup Block: '<S87>/u_5 < 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_50_l),
                           TemplateNIPID_P.u_50_YData_c,
                           TemplateNIPID_P.ctrl1Kdx_Value,
                           TemplateNIPID_P.u_50_XData_l, 9U);

      /* Lookup Block: '<S87>/u_5 > 0'
       * About '<S87>/u_5 > 0 :'
       * Lookup Block: '<S87>/u_5 > 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(TemplateNIPID_B.u_50_b),
                           TemplateNIPID_P.u_50_YData_j,
                           TemplateNIPID_P.ctrl1Kdx_Value,
                           TemplateNIPID_P.u_50_XData_c, 9U);

      /* MultiPortSwitch: '<S87>/Multiport Switch' incorporates:
       *  Constant: '<S87>/u_5 = 0'
       */
      switch ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_j >> 6)) {
       case 1:
        TemplateNIPID_B.MultiportSwitch_c = TemplateNIPID_B.u_50_l;
        break;

       case 2:
        TemplateNIPID_B.MultiportSwitch_c = TemplateNIPID_P.u_50_Value_n;
        break;

       default:
        TemplateNIPID_B.MultiportSwitch_c = TemplateNIPID_B.u_50_b;
        break;
      }

      /* SignalConversion: '<S81>/TmpHiddenBufferAtProduct1Inport2' */
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_h[0] =
        TemplateNIPID_B.u_1tof_1_p;
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_h[1] =
        TemplateNIPID_B.MultiportSwitch_iv;
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_h[2] =
        TemplateNIPID_B.u_3tof_3_b;
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_h[3] =
        TemplateNIPID_B.MultiportSwitch_pl;
      TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_h[4] =
        TemplateNIPID_B.MultiportSwitch_c;

      /* Product: '<S81>/Product1' */
      for (i = 0; i < 3; i++) {
        TemplateNIPID_B.Product1_b[i] = 0.0;
        for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
          TemplateNIPID_B.Product1_b[i] = TemplateNIPID_B.x5[3 * tmp_6 + i] *
            TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_h[tmp_6] +
            TemplateNIPID_B.Product1_b[i];
        }
      }
    }

    /* Gain: '<S188>/QTM In3 x-coord [mm]' */
    TemplateNIPID_B.QTMIn3xcoordmm = TemplateNIPID_P.QTMIn3xcoordmm_Gain *
      TemplateNIPID_B.QTMIn[2];

    /* Gain: '<S188>/mm2m x' */
    TemplateNIPID_B.mm2mx = TemplateNIPID_P.mm2mx_Gain *
      TemplateNIPID_B.QTMIn3xcoordmm;

    /* Gain: '<S188>/QTM In4 y-coord [mm]' */
    TemplateNIPID_B.QTMIn4ycoordmm = TemplateNIPID_P.QTMIn4ycoordmm_Gain *
      TemplateNIPID_B.QTMIn[3];

    /* Gain: '<S188>/mm2m y' */
    TemplateNIPID_B.mm2my = TemplateNIPID_P.mm2my_Gain *
      TemplateNIPID_B.QTMIn4ycoordmm;

    /* Gain: '<S188>/QTM In6 yaw [deg]' */
    TemplateNIPID_B.QTMIn6yawdeg = TemplateNIPID_P.QTMIn6yawdeg_Gain *
      TemplateNIPID_B.QTMIn[5];

    /* Gain: '<S188>/d2r yaw' */
    TemplateNIPID_B.d2ryaw = TemplateNIPID_P.d2ryaw_Gain *
      TemplateNIPID_B.QTMIn6yawdeg;

    /* Outputs for enable SubSystem: '<S22>/Linear Simulator' incorporates:
     *  Constant: '<S4>/Enable Linear Simulator'
     *  EnablePort: '<S214>/Enable'
     */
    if (rtmIsMajorTimeStep(TemplateNIPID_M) && rtmIsMajorTimeStep
        (TemplateNIPID_M)) {
      if (TemplateNIPID_P.EnableLinearSimulator_Value > 0.0) {
        if (TemplateNIPID_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S222>/Integrator' */
          if (rtmIsFirstInitCond(TemplateNIPID_M)) {
            TemplateNIPID_X.Integrator_CSTATE_m[0] = 0.0;
            TemplateNIPID_X.Integrator_CSTATE_m[1] = 0.0;
            TemplateNIPID_X.Integrator_CSTATE_m[2] = 0.0;
          }

          TemplateNIPID_DWork.Integrator_IWORK_k.IcNeedsLoading = 1;

          /* Integrator Block: '<S222>/Integrator1' */
          if (rtmIsFirstInitCond(TemplateNIPID_M)) {
            TemplateNIPID_X.Integrator1_CSTATE_m[0] = 0.0;
            TemplateNIPID_X.Integrator1_CSTATE_m[1] = 0.0;
            TemplateNIPID_X.Integrator1_CSTATE_m[2] = 0.0;
          }

          TemplateNIPID_DWork.Integrator1_IWORK_d.IcNeedsLoading = 1;
          TemplateNIPID_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (TemplateNIPID_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          TemplateNIPID_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (TemplateNIPID_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Integrator Block: '<S222>/Integrator'
       */
      if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &TemplateNIPID_PrevZCSigState.Integrator_Reset_ZCE_p,
                           TemplateNIPID_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || TemplateNIPID_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            TemplateNIPID_DWork.Integrator_IWORK_k.IcNeedsLoading) {
          TemplateNIPID_X.Integrator_CSTATE_m[0] = TemplateNIPID_B.Initialums;
          TemplateNIPID_X.Integrator_CSTATE_m[1] = TemplateNIPID_B.Initialvms;
          TemplateNIPID_X.Integrator_CSTATE_m[2] = TemplateNIPID_B.Initialrrads;
        }

        TemplateNIPID_DWork.Integrator_IWORK_k.IcNeedsLoading = 0;
      }

      TemplateNIPID_B.Integrator_e[0] = TemplateNIPID_X.Integrator_CSTATE_m[0];
      TemplateNIPID_B.Integrator_e[1] = TemplateNIPID_X.Integrator_CSTATE_m[1];
      TemplateNIPID_B.Integrator_e[2] = TemplateNIPID_X.Integrator_CSTATE_m[2];

      /* Integrator Block: '<S222>/Integrator1'
       */
      if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &TemplateNIPID_PrevZCSigState.Integrator1_Reset_ZCE_d,
                           TemplateNIPID_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || TemplateNIPID_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            TemplateNIPID_DWork.Integrator1_IWORK_d.IcNeedsLoading) {
          TemplateNIPID_X.Integrator1_CSTATE_m[0] = TemplateNIPID_B.Initialxm;
          TemplateNIPID_X.Integrator1_CSTATE_m[1] = TemplateNIPID_B.Initialym;
          TemplateNIPID_X.Integrator1_CSTATE_m[2] =
            TemplateNIPID_B.Initialpsirad;
        }

        TemplateNIPID_DWork.Integrator1_IWORK_d.IcNeedsLoading = 0;
      }

      TemplateNIPID_B.Integrator1_o[0] = TemplateNIPID_X.Integrator1_CSTATE_m[0];
      TemplateNIPID_B.Integrator1_o[1] = TemplateNIPID_X.Integrator1_CSTATE_m[1];
      TemplateNIPID_B.Integrator1_o[2] = TemplateNIPID_X.Integrator1_CSTATE_m[2];

      /* Fcn: '<S223>/R11' */
      TemplateNIPID_B.R11_c = cos(TemplateNIPID_B.Integrator1_o[2]);

      /* Fcn: '<S223>/R21' */
      TemplateNIPID_B.R21_c = sin(TemplateNIPID_B.Integrator1_o[2]);

      /* Fcn: '<S223>/R12' */
      TemplateNIPID_B.R12_j = -1.0 * sin(TemplateNIPID_B.Integrator1_o[2]);

      /* Fcn: '<S223>/R22' */
      TemplateNIPID_B.R22_f = cos(TemplateNIPID_B.Integrator1_o[2]);

      /* Reshape: '<S223>/R(psi)' incorporates:
       *  Constant: '<S223>/R13'
       *  Constant: '<S223>/R23'
       *  Constant: '<S223>/R31'
       *  Constant: '<S223>/R32'
       *  Constant: '<S223>/R33'
       */
      TemplateNIPID_B.Rpsi_o[0] = TemplateNIPID_B.R11_c;
      TemplateNIPID_B.Rpsi_o[1] = TemplateNIPID_B.R21_c;
      TemplateNIPID_B.Rpsi_o[2] = TemplateNIPID_P.R31_Value_j;
      TemplateNIPID_B.Rpsi_o[3] = TemplateNIPID_B.R12_j;
      TemplateNIPID_B.Rpsi_o[4] = TemplateNIPID_B.R22_f;
      TemplateNIPID_B.Rpsi_o[5] = TemplateNIPID_P.R32_Value_c;
      TemplateNIPID_B.Rpsi_o[6] = TemplateNIPID_P.R13_Value_g;
      TemplateNIPID_B.Rpsi_o[7] = TemplateNIPID_P.R23_Value_g;
      TemplateNIPID_B.Rpsi_o[8] = TemplateNIPID_P.R33_Value_h;
    }

    /* end of Outputs for SubSystem: '<S22>/Linear Simulator' */

    /* MultiPortSwitch: '<S189>/eta Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)TemplateNIPID_P.ControlInputSelector_Value == 0) {
      TemplateNIPID_B.etaSwitch[0] = TemplateNIPID_B.mm2mx;
      TemplateNIPID_B.etaSwitch[1] = TemplateNIPID_B.mm2my;
      TemplateNIPID_B.etaSwitch[2] = TemplateNIPID_B.d2ryaw;
    } else {
      TemplateNIPID_B.etaSwitch[0] = TemplateNIPID_B.Integrator1_o[0];
      TemplateNIPID_B.etaSwitch[1] = TemplateNIPID_B.Integrator1_o[1];
      TemplateNIPID_B.etaSwitch[2] = TemplateNIPID_B.Integrator1_o[2];
    }

    /* Trigonometry: '<S34>/R11' */
    TemplateNIPID_B.R11 = cos(TemplateNIPID_B.etaSwitch[2]);

    /* Trigonometry: '<S34>/R21' */
    TemplateNIPID_B.R21 = sin(TemplateNIPID_B.etaSwitch[2]);

    /* Trigonometry: '<S34>/R12' */
    TemplateNIPID_B.R12 = sin(TemplateNIPID_B.etaSwitch[2]);

    /* Gain: '<S34>/-1' */
    TemplateNIPID_B.u = TemplateNIPID_P.u_Gain * TemplateNIPID_B.R12;

    /* Trigonometry: '<S34>/R22' */
    TemplateNIPID_B.R22 = cos(TemplateNIPID_B.etaSwitch[2]);

    /* Reshape: '<S34>/R(psi)' incorporates:
     *  Constant: '<S34>/R13'
     *  Constant: '<S34>/R23'
     *  Constant: '<S34>/R31'
     *  Constant: '<S34>/R32'
     *  Constant: '<S34>/R33'
     */
    TemplateNIPID_B.Rpsi[0] = TemplateNIPID_B.R11;
    TemplateNIPID_B.Rpsi[1] = TemplateNIPID_B.R21;
    TemplateNIPID_B.Rpsi[2] = TemplateNIPID_P.R31_Value;
    TemplateNIPID_B.Rpsi[3] = TemplateNIPID_B.u;
    TemplateNIPID_B.Rpsi[4] = TemplateNIPID_B.R22;
    TemplateNIPID_B.Rpsi[5] = TemplateNIPID_P.R32_Value;
    TemplateNIPID_B.Rpsi[6] = TemplateNIPID_P.R13_Value;
    TemplateNIPID_B.Rpsi[7] = TemplateNIPID_P.R23_Value;
    TemplateNIPID_B.Rpsi[8] = TemplateNIPID_P.R33_Value;

    /* Math: '<S56>/Math Function' */
    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.MathFunction[3 * i] = TemplateNIPID_B.Rpsi[i];
      TemplateNIPID_B.MathFunction[1 + 3 * i] = TemplateNIPID_B.Rpsi[i + 3];
      TemplateNIPID_B.MathFunction[2 + 3 * i] = TemplateNIPID_B.Rpsi[i + 6];
    }

    /* Saturate: '<S63>/Saturation' */
    tmp = TemplateNIPID_B.etaSwitch[2];
    TemplateNIPID_B.Saturation = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat, TemplateNIPID_P.Saturation_UpperSat);

    /* Signum: '<S63>/Sign' */
    TemplateNIPID_B.Sign = rt_SIGNd_snf(TemplateNIPID_B.Saturation);

    /* Gain: '<S63>/Gain' */
    TemplateNIPID_B.Gain = TemplateNIPID_P.Gain_Gain * TemplateNIPID_B.Sign;

    /* Sum: '<S63>/Sum1' */
    TemplateNIPID_B.Sum1 = TemplateNIPID_B.Saturation + TemplateNIPID_B.Gain;

    /* Math: '<S63>/Math Function' incorporates:
     *  Constant: '<S63>/Constant'
     */
    TemplateNIPID_B.MathFunction_f = rt_rem_snf(TemplateNIPID_B.Sum1,
      TemplateNIPID_P.Constant_Value_lo);

    /* Sum: '<S63>/Sum' */
    TemplateNIPID_B.Sum = TemplateNIPID_B.MathFunction_f - TemplateNIPID_B.Gain;

    /* Integrator Block: '<S35>/Integrator'
     */
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateNIPID_PrevZCSigState.Integrator_Reset_ZCE,
                         TemplateNIPID_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateNIPID_P.ctrl2ResetIntegrator_Value != 0.0 ||
          TemplateNIPID_DWork.Integrator_IWORK.IcNeedsLoading) {
        TemplateNIPID_X.Integrator_CSTATE[0] = TemplateNIPID_B.Initialq_x;
        TemplateNIPID_X.Integrator_CSTATE[1] = TemplateNIPID_B.Initialq_y;
      }

      TemplateNIPID_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    TemplateNIPID_B.Integrator[0] = TemplateNIPID_X.Integrator_CSTATE[0];
    TemplateNIPID_B.Integrator[1] = TemplateNIPID_X.Integrator_CSTATE[1];

    /* SignalConversion: '<S128>/ConcatBufferAtVector ConcatenateIn1' */
    TemplateNIPID_B.VectorConcatenate[0] = TemplateNIPID_B.Integrator[0];
    TemplateNIPID_B.VectorConcatenate[1] = TemplateNIPID_B.Integrator[1];
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Sum: '<S181>/x_2 - x_1' incorporates:
       *  Constant: '<S11>/x_1 [m]'
       *  Constant: '<S11>/x_2 [m]'
       */
      TemplateNIPID_B.x_2x_1 = TemplateNIPID_P.x_2m_Value -
        TemplateNIPID_P.x_1m_Value;

      /* Sum: '<S181>/y_2 - y_1' incorporates:
       *  Constant: '<S11>/y_1 [m]'
       *  Constant: '<S11>/y_2 [m]'
       */
      TemplateNIPID_B.y_2y_1 = TemplateNIPID_P.y_2m_Value -
        TemplateNIPID_P.y_1m_Value;

      /* SignalConversion: '<S182>/TmpHiddenBufferAtProductInport2' */
      TemplateNIPID_B.TmpHiddenBufferAtProductInport2[0] =
        TemplateNIPID_B.x_2x_1;
      TemplateNIPID_B.TmpHiddenBufferAtProductInport2[1] =
        TemplateNIPID_B.y_2y_1;

      /* Saturate: '<S164>/Saturation' incorporates:
       *  Constant: '<S5>/Path Selector  [-]'
       */
      tmp = TemplateNIPID_P.PathSelector_Value;
      TemplateNIPID_B.Saturation_k = rt_SATURATE(tmp,
        TemplateNIPID_P.Saturation_LowerSat_b,
        TemplateNIPID_P.Saturation_UpperSat_e);

      /* Rounding: '<S164>/Rounding Function' */
      TemplateNIPID_B.RoundingFunction = floor(TemplateNIPID_B.Saturation_k);

      /* Product: '<S174>/Product' */
      TemplateNIPID_B.Product[0] =
        TemplateNIPID_B.TmpHiddenBufferAtProductInport2[0] *
        TemplateNIPID_B.RoundingFunction;
      TemplateNIPID_B.Product[1] =
        TemplateNIPID_B.TmpHiddenBufferAtProductInport2[1] *
        TemplateNIPID_B.RoundingFunction;
    }

    /* Integrator Block: '<S35>/Integrator1'
     */
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateNIPID_PrevZCSigState.Integrator1_Reset_ZCE,
                         TemplateNIPID_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateNIPID_P.ctrl2ResetIntegrator_Value != 0.0 ||
          TemplateNIPID_DWork.Integrator1_IWORK.IcNeedsLoading) {
        TemplateNIPID_X.Integrator1_CSTATE = TemplateNIPID_B.Initials;
      }

      TemplateNIPID_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    TemplateNIPID_B.Integrator1 = TemplateNIPID_X.Integrator1_CSTATE;

    /* Product: '<S167>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    TemplateNIPID_B.Product2 = TemplateNIPID_B.Integrator1 *
      TemplateNIPID_P.k_Value;

    /* Trigonometry: '<S167>/sin(s)' */
    TemplateNIPID_B.sins = sin(TemplateNIPID_B.Product2);

    /* Product: '<S167>/Product' incorporates:
     *  Constant: '<S10>/k [-]'
     *  Constant: '<S10>/r_x [m]'
     */
    TemplateNIPID_B.Product_a = TemplateNIPID_P.r_xm_Value *
      TemplateNIPID_B.sins * TemplateNIPID_P.k_Value;

    /* Gain: '<S167>/Gain' */
    TemplateNIPID_B.Gain_i = TemplateNIPID_P.Gain_Gain_l *
      TemplateNIPID_B.Product_a;

    /* Trigonometry: '<S167>/cos(s)' */
    TemplateNIPID_B.coss = cos(TemplateNIPID_B.Product2);

    /* Product: '<S167>/Product1' incorporates:
     *  Constant: '<S10>/k [-]'
     *  Constant: '<S10>/r_y [m]'
     */
    TemplateNIPID_B.Product1_a = TemplateNIPID_P.r_ym_Value *
      TemplateNIPID_B.coss * TemplateNIPID_P.k_Value;

    /* SignalConversion: '<S170>/TmpHiddenBufferAtProductInport2' */
    TemplateNIPID_B.TmpHiddenBufferAtProductInpor_k[0] = TemplateNIPID_B.Gain_i;
    TemplateNIPID_B.TmpHiddenBufferAtProductInpor_k[1] =
      TemplateNIPID_B.Product1_a;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Sum: '<S174>/Subract' incorporates:
       *  Constant: '<S174>/Constant'
       */
      TemplateNIPID_B.Subract = TemplateNIPID_P.Constant_Value_lv -
        TemplateNIPID_B.RoundingFunction;
    }

    /* Product: '<S174>/Product1' */
    TemplateNIPID_B.Product1_i[0] =
      TemplateNIPID_B.TmpHiddenBufferAtProductInpor_k[0] *
      TemplateNIPID_B.Subract;

    /* Sum: '<S174>/Add' */
    TemplateNIPID_B.Add[0] = TemplateNIPID_B.Product[0] +
      TemplateNIPID_B.Product1_i[0];

    /* Product: '<S174>/Product1' */
    TemplateNIPID_B.Product1_i[1] =
      TemplateNIPID_B.TmpHiddenBufferAtProductInpor_k[1] *
      TemplateNIPID_B.Subract;

    /* Sum: '<S174>/Add' */
    TemplateNIPID_B.Add[1] = TemplateNIPID_B.Product[1] +
      TemplateNIPID_B.Product1_i[1];

    /* Trigonometry: '<S119>/Trigonometric Function' */
    TemplateNIPID_B.TrigonometricFunction = rt_atan2_snf(TemplateNIPID_B.Add[1],
      TemplateNIPID_B.Add[0]);

    /* Saturate: '<S122>/Saturation' */
    tmp = TemplateNIPID_B.TrigonometricFunction;
    TemplateNIPID_B.Saturation_j = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat_e,
      TemplateNIPID_P.Saturation_UpperSat_d);

    /* Signum: '<S122>/Sign' */
    TemplateNIPID_B.Sign_c = rt_SIGNd_snf(TemplateNIPID_B.Saturation_j);

    /* Gain: '<S122>/Gain' */
    TemplateNIPID_B.Gain_k = TemplateNIPID_P.Gain_Gain_f *
      TemplateNIPID_B.Sign_c;

    /* Sum: '<S122>/Sum1' */
    TemplateNIPID_B.Sum1_j = TemplateNIPID_B.Saturation_j +
      TemplateNIPID_B.Gain_k;

    /* Math: '<S122>/Math Function' incorporates:
     *  Constant: '<S122>/Constant'
     */
    TemplateNIPID_B.MathFunction_h = rt_rem_snf(TemplateNIPID_B.Sum1_j,
      TemplateNIPID_P.Constant_Value_a5);

    /* Sum: '<S122>/Sum' */
    TemplateNIPID_B.Sum_k = TemplateNIPID_B.MathFunction_h -
      TemplateNIPID_B.Gain_k;

    /* Saturate: '<S150>/Saturation' */
    tmp = TemplateNIPID_B.Sum_k;
    TemplateNIPID_B.Saturation_i = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat_d,
      TemplateNIPID_P.Saturation_UpperSat_j);

    /* Signum: '<S150>/Sign' */
    TemplateNIPID_B.Sign_k = rt_SIGNd_snf(TemplateNIPID_B.Saturation_i);

    /* Gain: '<S150>/Gain' */
    TemplateNIPID_B.Gain_d = TemplateNIPID_P.Gain_Gain_p *
      TemplateNIPID_B.Sign_k;

    /* Sum: '<S150>/Sum1' */
    TemplateNIPID_B.Sum1_l = TemplateNIPID_B.Saturation_i +
      TemplateNIPID_B.Gain_d;

    /* Math: '<S150>/Math Function' incorporates:
     *  Constant: '<S150>/Constant'
     */
    TemplateNIPID_B.MathFunction_ht = rt_rem_snf(TemplateNIPID_B.Sum1_l,
      TemplateNIPID_P.Constant_Value_md);

    /* Sum: '<S150>/Sum' */
    TemplateNIPID_B.Sum_l = TemplateNIPID_B.MathFunction_ht -
      TemplateNIPID_B.Gain_d;

    /* Outputs for atomic SubSystem: '<S127>/R_2' */

    /* Trigonometry: '<S153>/R11' */
    TemplateNIPID_B.R11_jo = cos(TemplateNIPID_B.Sum_k);

    /* Trigonometry: '<S153>/R21' */
    TemplateNIPID_B.R21_m = sin(TemplateNIPID_B.Sum_k);

    /* Gain: '<S153>/R12' */
    TemplateNIPID_B.R12_ml = TemplateNIPID_P.R12_Gain * TemplateNIPID_B.R21_m;

    /* Gain: '<S153>/R22' */
    TemplateNIPID_B.R22_cv = TemplateNIPID_P.R22_Gain * TemplateNIPID_B.R11_jo;

    /* Reshape: '<S153>/R_2(psi_d)' */
    TemplateNIPID_B.R_2psi_d[0] = TemplateNIPID_B.R11_jo;
    TemplateNIPID_B.R_2psi_d[1] = TemplateNIPID_B.R21_m;
    TemplateNIPID_B.R_2psi_d[2] = TemplateNIPID_B.R12_ml;
    TemplateNIPID_B.R_2psi_d[3] = TemplateNIPID_B.R22_cv;

    /* end of Outputs for SubSystem: '<S127>/R_2' */

    /* Math: '<S154>/Math Function' */
    TemplateNIPID_B.MathFunction_n[0] = TemplateNIPID_B.R_2psi_d[0];
    TemplateNIPID_B.MathFunction_n[1] = TemplateNIPID_B.R_2psi_d[2];
    TemplateNIPID_B.MathFunction_n[2] = TemplateNIPID_B.R_2psi_d[1];
    TemplateNIPID_B.MathFunction_n[3] = TemplateNIPID_B.R_2psi_d[3];
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Sum: '<S180>/x_2 - x_1' incorporates:
       *  Constant: '<S11>/x_1 [m]'
       *  Constant: '<S11>/x_2 [m]'
       */
      TemplateNIPID_B.x_2x_1_g = TemplateNIPID_P.x_2m_Value -
        TemplateNIPID_P.x_1m_Value;
    }

    /* Product: '<S180>/(x_2 - x_1) * s' */
    TemplateNIPID_B.x_2x_1s = TemplateNIPID_B.x_2x_1_g *
      TemplateNIPID_B.Integrator1;

    /* Sum: '<S180>/(x_2 - x_1) * s + x_1' incorporates:
     *  Constant: '<S11>/x_1 [m]'
     */
    TemplateNIPID_B.x_2x_1sx_1 = TemplateNIPID_B.x_2x_1s +
      TemplateNIPID_P.x_1m_Value;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Sum: '<S180>/y_2 - y_1' incorporates:
       *  Constant: '<S11>/y_1 [m]'
       *  Constant: '<S11>/y_2 [m]'
       */
      TemplateNIPID_B.y_2y_1_m = TemplateNIPID_P.y_2m_Value -
        TemplateNIPID_P.y_1m_Value;
    }

    /* Product: '<S180>/(y_2 - y_1) * s' */
    TemplateNIPID_B.y_2y_1s = TemplateNIPID_B.y_2y_1_m *
      TemplateNIPID_B.Integrator1;

    /* Sum: '<S180>/(y_2 - y_1) * s + y_1' incorporates:
     *  Constant: '<S11>/y_1 [m]'
     */
    TemplateNIPID_B.y_2y_1sy_1 = TemplateNIPID_B.y_2y_1s +
      TemplateNIPID_P.y_1m_Value;

    /* Product: '<S173>/Product' */
    TemplateNIPID_B.Product_f[0] = TemplateNIPID_B.x_2x_1sx_1 *
      TemplateNIPID_B.RoundingFunction;
    TemplateNIPID_B.Product_f[1] = TemplateNIPID_B.y_2y_1sy_1 *
      TemplateNIPID_B.RoundingFunction;

    /* Product: '<S166>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    TemplateNIPID_B.Product2_n = TemplateNIPID_B.Integrator1 *
      TemplateNIPID_P.k_Value;

    /* Trigonometry: '<S166>/cos(s)' */
    TemplateNIPID_B.coss_o = cos(TemplateNIPID_B.Product2_n);

    /* Product: '<S166>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    TemplateNIPID_B.Product_d = TemplateNIPID_P.r_xm_Value *
      TemplateNIPID_B.coss_o;

    /* Sum: '<S166>/Add' incorporates:
     *  Constant: '<S10>/x_0 [m]'
     */
    TemplateNIPID_B.Add_c = TemplateNIPID_B.Product_d +
      TemplateNIPID_P.x_0m_Value;

    /* Trigonometry: '<S166>/sin(s)' */
    TemplateNIPID_B.sins_p = sin(TemplateNIPID_B.Product2_n);

    /* Product: '<S166>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    TemplateNIPID_B.Product1_p = TemplateNIPID_P.r_ym_Value *
      TemplateNIPID_B.sins_p;

    /* Sum: '<S166>/Add1' incorporates:
     *  Constant: '<S10>/y_0 [m]'
     */
    TemplateNIPID_B.Add1 = TemplateNIPID_B.Product1_p +
      TemplateNIPID_P.y_0m_Value;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Sum: '<S173>/Subract' incorporates:
       *  Constant: '<S173>/Constant'
       */
      TemplateNIPID_B.Subract_h = TemplateNIPID_P.Constant_Value_i -
        TemplateNIPID_B.RoundingFunction;
    }

    /* Product: '<S173>/Product1' */
    TemplateNIPID_B.Product1_h[0] = TemplateNIPID_B.Add_c *
      TemplateNIPID_B.Subract_h;
    TemplateNIPID_B.Product1_h[1] = TemplateNIPID_B.Add1 *
      TemplateNIPID_B.Subract_h;

    /* Sum: '<S173>/Add' */
    TemplateNIPID_B.Add_cx[0] = TemplateNIPID_B.Product_f[0] +
      TemplateNIPID_B.Product1_h[0];
    TemplateNIPID_B.Add_cx[1] = TemplateNIPID_B.Product_f[1] +
      TemplateNIPID_B.Product1_h[1];

    /* RelationalOperator: '<S178>/LowerRelop1' incorporates:
     *  Constant: '<S5>/x_dmax [m]'
     */
    TemplateNIPID_B.LowerRelop1 = (TemplateNIPID_B.Add_cx[0] >
      TemplateNIPID_P.x_dmaxm_Value);

    /* RelationalOperator: '<S178>/UpperRelop' incorporates:
     *  Constant: '<S5>/x_dmin [m]'
     */
    TemplateNIPID_B.UpperRelop = (TemplateNIPID_B.Add_cx[0] <
      TemplateNIPID_P.x_dminm_Value);

    /* Switch: '<S178>/Switch' incorporates:
     *  Constant: '<S5>/x_dmin [m]'
     */
    if (TemplateNIPID_B.UpperRelop) {
      TemplateNIPID_B.Switch = TemplateNIPID_P.x_dminm_Value;
    } else {
      TemplateNIPID_B.Switch = TemplateNIPID_B.Add_cx[0];
    }

    /* Switch: '<S178>/Switch2' incorporates:
     *  Constant: '<S5>/x_dmax [m]'
     */
    if (TemplateNIPID_B.LowerRelop1) {
      TemplateNIPID_B.Switch2 = TemplateNIPID_P.x_dmaxm_Value;
    } else {
      TemplateNIPID_B.Switch2 = TemplateNIPID_B.Switch;
    }

    /* RelationalOperator: '<S179>/LowerRelop1' incorporates:
     *  Constant: '<S5>/y_dmax [m]'
     */
    TemplateNIPID_B.LowerRelop1_j = (TemplateNIPID_B.Add_cx[1] >
      TemplateNIPID_P.y_dmaxm_Value);

    /* RelationalOperator: '<S179>/UpperRelop' incorporates:
     *  Constant: '<S5>/y_dmin [m]'
     */
    TemplateNIPID_B.UpperRelop_p = (TemplateNIPID_B.Add_cx[1] <
      TemplateNIPID_P.y_dminm_Value);

    /* Switch: '<S179>/Switch' incorporates:
     *  Constant: '<S5>/y_dmin [m]'
     */
    if (TemplateNIPID_B.UpperRelop_p) {
      TemplateNIPID_B.Switch_m = TemplateNIPID_P.y_dminm_Value;
    } else {
      TemplateNIPID_B.Switch_m = TemplateNIPID_B.Add_cx[1];
    }

    /* Switch: '<S179>/Switch2' incorporates:
     *  Constant: '<S5>/y_dmax [m]'
     */
    if (TemplateNIPID_B.LowerRelop1_j) {
      TemplateNIPID_B.Switch2_c = TemplateNIPID_P.y_dmaxm_Value;
    } else {
      TemplateNIPID_B.Switch2_c = TemplateNIPID_B.Switch_m;
    }

    /* Sum: '<S116>/Subtract' */
    TemplateNIPID_B.Subtract[0] = TemplateNIPID_B.Integrator[0] -
      TemplateNIPID_B.Switch2;
    TemplateNIPID_B.Subtract[1] = TemplateNIPID_B.Integrator[1] -
      TemplateNIPID_B.Switch2_c;

    /* Product: '<S127>/epsilon' */
    TemplateNIPID_B.epsilon[0] = 0.0;
    TemplateNIPID_B.epsilon[0] = TemplateNIPID_B.MathFunction_n[0] *
      TemplateNIPID_B.Subtract[0] + TemplateNIPID_B.epsilon[0];
    TemplateNIPID_B.epsilon[0] = TemplateNIPID_B.MathFunction_n[2] *
      TemplateNIPID_B.Subtract[1] + TemplateNIPID_B.epsilon[0];
    TemplateNIPID_B.epsilon[1] = 0.0;
    TemplateNIPID_B.epsilon[1] = TemplateNIPID_B.MathFunction_n[1] *
      TemplateNIPID_B.Subtract[0] + TemplateNIPID_B.epsilon[1];
    TemplateNIPID_B.epsilon[1] = TemplateNIPID_B.MathFunction_n[3] *
      TemplateNIPID_B.Subtract[1] + TemplateNIPID_B.epsilon[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector' */
    {
      const byte_T *u = (byte_T *)TemplateNIPID_B.epsilon;/* input port */
      const int32_T *index = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&TemplateNIPID_B.MultiportSelector;
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
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.TrigonometricFunction_n = rt_atan2_snf
      (TemplateNIPID_B.MultiportSelector, TemplateNIPID_P.Deltam_Value);

    /* Saturate: '<S151>/Saturation' */
    tmp = TemplateNIPID_B.TrigonometricFunction_n;
    TemplateNIPID_B.Saturation_c = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat_c,
      TemplateNIPID_P.Saturation_UpperSat_m);

    /* Signum: '<S151>/Sign' */
    TemplateNIPID_B.Sign_h = rt_SIGNd_snf(TemplateNIPID_B.Saturation_c);

    /* Gain: '<S151>/Gain' */
    TemplateNIPID_B.Gain_f = TemplateNIPID_P.Gain_Gain_o *
      TemplateNIPID_B.Sign_h;

    /* Sum: '<S151>/Sum1' */
    TemplateNIPID_B.Sum1_g = TemplateNIPID_B.Saturation_c +
      TemplateNIPID_B.Gain_f;

    /* Math: '<S151>/Math Function' incorporates:
     *  Constant: '<S151>/Constant'
     */
    TemplateNIPID_B.MathFunction_c = rt_rem_snf(TemplateNIPID_B.Sum1_g,
      TemplateNIPID_P.Constant_Value_ic);

    /* Sum: '<S151>/Sum' */
    TemplateNIPID_B.Sum_f = TemplateNIPID_B.MathFunction_c -
      TemplateNIPID_B.Gain_f;

    /* Sum: '<S144>/Subtract' */
    TemplateNIPID_B.Subtract_f = TemplateNIPID_B.Sum_l - TemplateNIPID_B.Sum_f;

    /* Saturate: '<S152>/Saturation' */
    tmp = TemplateNIPID_B.Subtract_f;
    TemplateNIPID_B.Saturation_m = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat_p,
      TemplateNIPID_P.Saturation_UpperSat_k);

    /* Signum: '<S152>/Sign' */
    TemplateNIPID_B.Sign_f = rt_SIGNd_snf(TemplateNIPID_B.Saturation_m);

    /* Gain: '<S152>/Gain' */
    TemplateNIPID_B.Gain_b = TemplateNIPID_P.Gain_Gain_b *
      TemplateNIPID_B.Sign_f;

    /* Sum: '<S152>/Sum1' */
    TemplateNIPID_B.Sum1_lj = TemplateNIPID_B.Saturation_m +
      TemplateNIPID_B.Gain_b;

    /* Math: '<S152>/Math Function' incorporates:
     *  Constant: '<S152>/Constant'
     */
    TemplateNIPID_B.MathFunction_e = rt_rem_snf(TemplateNIPID_B.Sum1_lj,
      TemplateNIPID_P.Constant_Value_l2);

    /* Sum: '<S152>/Sum' */
    TemplateNIPID_B.Sum_e = TemplateNIPID_B.MathFunction_e -
      TemplateNIPID_B.Gain_b;

    /* SignalConversion: '<S128>/ConcatBufferAtVector ConcatenateIn2' */
    TemplateNIPID_B.VectorConcatenate[2] = TemplateNIPID_B.Sum_e;

    /* Sum: '<S38>/Subtract' */
    TemplateNIPID_B.Subtract_m[0] = TemplateNIPID_B.etaSwitch[0] -
      TemplateNIPID_B.VectorConcatenate[0];
    TemplateNIPID_B.Subtract_m[1] = TemplateNIPID_B.etaSwitch[1] -
      TemplateNIPID_B.VectorConcatenate[1];
    TemplateNIPID_B.Subtract_m[2] = TemplateNIPID_B.Sum -
      TemplateNIPID_B.VectorConcatenate[2];

    /* Saturate: '<S64>/Saturation' */
    tmp = TemplateNIPID_B.Subtract_m[2];
    TemplateNIPID_B.Saturation_cu = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat_g,
      TemplateNIPID_P.Saturation_UpperSat_b);

    /* Signum: '<S64>/Sign' */
    TemplateNIPID_B.Sign_d = rt_SIGNd_snf(TemplateNIPID_B.Saturation_cu);

    /* Gain: '<S64>/Gain' */
    TemplateNIPID_B.Gain_fi = TemplateNIPID_P.Gain_Gain_ff *
      TemplateNIPID_B.Sign_d;

    /* Sum: '<S64>/Sum1' */
    TemplateNIPID_B.Sum1_e = TemplateNIPID_B.Saturation_cu +
      TemplateNIPID_B.Gain_fi;

    /* Math: '<S64>/Math Function' incorporates:
     *  Constant: '<S64>/Constant'
     */
    TemplateNIPID_B.MathFunction_k = rt_rem_snf(TemplateNIPID_B.Sum1_e,
      TemplateNIPID_P.Constant_Value_cb);

    /* Sum: '<S64>/Sum' */
    TemplateNIPID_B.Sum_d = TemplateNIPID_B.MathFunction_k -
      TemplateNIPID_B.Gain_fi;

    /* SignalConversion: '<S53>/TmpHiddenBufferAtProductInport3' */
    TemplateNIPID_B.TmpHiddenBufferAtProductInport3[0] =
      TemplateNIPID_B.Subtract_m[0];
    TemplateNIPID_B.TmpHiddenBufferAtProductInport3[1] =
      TemplateNIPID_B.Subtract_m[1];
    TemplateNIPID_B.TmpHiddenBufferAtProductInport3[2] = TemplateNIPID_B.Sum_d;

    /* Product: '<S53>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] + TemplateNIPID_B.ux3_p[3 *
          tmp_6] * TemplateNIPID_B.MathFunction[i];
        tmp_1[i + 3 * tmp_6] = TemplateNIPID_B.ux3_p[3 * tmp_6 + 1] *
          TemplateNIPID_B.MathFunction[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = TemplateNIPID_B.ux3_p[3 * tmp_6 + 2] *
          TemplateNIPID_B.MathFunction[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.Product_k[i] = 0.0;
      TemplateNIPID_B.Product_k[i] = tmp_1[i] *
        TemplateNIPID_B.TmpHiddenBufferAtProductInport3[0] +
        TemplateNIPID_B.Product_k[i];
      TemplateNIPID_B.Product_k[i] = tmp_1[i + 3] *
        TemplateNIPID_B.TmpHiddenBufferAtProductInport3[1] +
        TemplateNIPID_B.Product_k[i];
      TemplateNIPID_B.Product_k[i] = tmp_1[i + 6] *
        TemplateNIPID_B.TmpHiddenBufferAtProductInport3[2] +
        TemplateNIPID_B.Product_k[i];

      /* Gain: '<S53>/Gain' */
      TemplateNIPID_B.Gain_p[i] = TemplateNIPID_P.Gain_Gain_fj *
        TemplateNIPID_B.Product_k[i];
    }

    /* Integrator Block: '<S40>/Integrator'
     */
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateNIPID_PrevZCSigState.Integrator_Reset_ZCE_k,
                         TemplateNIPID_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateNIPID_P.ctrl2ResetIntegrator_Value != 0.0) {
        TemplateNIPID_X.Integrator_CSTATE_o[0] = TemplateNIPID_P.Integrator_IC[0];
        TemplateNIPID_X.Integrator_CSTATE_o[1] = TemplateNIPID_P.Integrator_IC[1];
        TemplateNIPID_X.Integrator_CSTATE_o[2] = TemplateNIPID_P.Integrator_IC[2];
      }
    }

    TemplateNIPID_B.Integrator_k[0] = TemplateNIPID_X.Integrator_CSTATE_o[0];
    TemplateNIPID_B.Integrator_k[1] = TemplateNIPID_X.Integrator_CSTATE_o[1];
    TemplateNIPID_B.Integrator_k[2] = TemplateNIPID_X.Integrator_CSTATE_o[2];

    /* Product: '<S53>/Product1' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] + TemplateNIPID_B.ux3_c[3 *
          tmp_6] * TemplateNIPID_B.MathFunction[i];
        tmp_1[i + 3 * tmp_6] = TemplateNIPID_B.ux3_c[3 * tmp_6 + 1] *
          TemplateNIPID_B.MathFunction[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = TemplateNIPID_B.ux3_c[3 * tmp_6 + 2] *
          TemplateNIPID_B.MathFunction[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.Product1_ao[i] = 0.0;
      TemplateNIPID_B.Product1_ao[i] = tmp_1[i] * TemplateNIPID_B.Integrator_k[0]
        + TemplateNIPID_B.Product1_ao[i];
      TemplateNIPID_B.Product1_ao[i] = tmp_1[i + 3] *
        TemplateNIPID_B.Integrator_k[1] + TemplateNIPID_B.Product1_ao[i];
      TemplateNIPID_B.Product1_ao[i] = tmp_1[i + 6] *
        TemplateNIPID_B.Integrator_k[2] + TemplateNIPID_B.Product1_ao[i];

      /* Gain: '<S53>/Gain1' */
      TemplateNIPID_B.Gain1_a[i] = TemplateNIPID_P.Gain1_Gain_c *
        TemplateNIPID_B.Product1_ao[i];
    }

    /* Integrator Block: '<S191>/Integrator4'
     */
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateNIPID_PrevZCSigState.Integrator4_Reset_ZCE,
                         TemplateNIPID_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateNIPID_P.ctrl2ResetIntegrator_Value != 0.0) {
        TemplateNIPID_X.Integrator4_CSTATE[0] = TemplateNIPID_P.Integrator4_IC;
        TemplateNIPID_X.Integrator4_CSTATE[1] = TemplateNIPID_P.Integrator4_IC;
        TemplateNIPID_X.Integrator4_CSTATE[2] = TemplateNIPID_P.Integrator4_IC;
      }
    }

    TemplateNIPID_B.nu[0] = TemplateNIPID_X.Integrator4_CSTATE[0];
    TemplateNIPID_B.nu[1] = TemplateNIPID_X.Integrator4_CSTATE[1];
    TemplateNIPID_B.nu[2] = TemplateNIPID_X.Integrator4_CSTATE[2];

    /* MultiPortSwitch: '<S189>/nu Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)TemplateNIPID_P.ControlInputSelector_Value == 0) {
      TemplateNIPID_B.nuSwitch[0] = TemplateNIPID_B.nu[0];
      TemplateNIPID_B.nuSwitch[1] = TemplateNIPID_B.nu[1];
      TemplateNIPID_B.nuSwitch[2] = TemplateNIPID_B.nu[2];
    } else {
      TemplateNIPID_B.nuSwitch[0] = TemplateNIPID_B.Integrator_e[0];
      TemplateNIPID_B.nuSwitch[1] = TemplateNIPID_B.Integrator_e[1];
      TemplateNIPID_B.nuSwitch[2] = TemplateNIPID_B.Integrator_e[2];
    }

    /* Trigonometry: '<S129>/f_qx' */
    TemplateNIPID_B.f_qx = cos(TemplateNIPID_B.Sum_e);

    /* Trigonometry: '<S129>/f_qy' */
    TemplateNIPID_B.f_qy = sin(TemplateNIPID_B.Sum_e);

    /* SignalConversion: '<S129>/TmpHiddenBufferAtProductInport1' */
    TemplateNIPID_B.TmpHiddenBufferAtProductInport1[0] = TemplateNIPID_B.f_qx;
    TemplateNIPID_B.TmpHiddenBufferAtProductInport1[1] = TemplateNIPID_B.f_qy;

    /* Product: '<S129>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateNIPID_B.Product_c[0] =
      TemplateNIPID_B.TmpHiddenBufferAtProductInport1[0] *
      TemplateNIPID_P.u_dm_Value;
    TemplateNIPID_B.Product_c[1] =
      TemplateNIPID_B.TmpHiddenBufferAtProductInport1[1] *
      TemplateNIPID_P.u_dm_Value;

    /* SignalConversion: '<S41>/ConcatBufferAtVector ConcatenateIn1' */
    TemplateNIPID_B.VectorConcatenate_k[0] = TemplateNIPID_B.Product_c[0];
    TemplateNIPID_B.VectorConcatenate_k[1] = TemplateNIPID_B.Product_c[1];
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S145>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2 = tmp * tmp;
    }

    /* Math: '<S145>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2 = tmp * tmp;

    /* Sum: '<S145>/Add' */
    TemplateNIPID_B.Add_l = TemplateNIPID_B.Delta2 + TemplateNIPID_B.epsilon_n2;

    /* Product: '<S145>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Divide = TemplateNIPID_P.Deltam_Value /
      TemplateNIPID_B.Add_l;

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector1' */
    {
      const byte_T *u = (byte_T *)TemplateNIPID_B.MathFunction_n;/* input port */
      const int32_T *index = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)TemplateNIPID_B.MultiportSelector1;
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
    TemplateNIPID_B.Product_kt[0] = TemplateNIPID_B.Divide *
      TemplateNIPID_B.MultiportSelector1[0];

    /* Gain: '<S145>/-1' */
    TemplateNIPID_B.u_m[0] = TemplateNIPID_P.u_Gain_i *
      TemplateNIPID_B.Product_kt[0];

    /* Product: '<S145>/Product' */
    TemplateNIPID_B.Product_kt[1] = TemplateNIPID_B.Divide *
      TemplateNIPID_B.MultiportSelector1[1];

    /* Gain: '<S145>/-1' */
    TemplateNIPID_B.u_m[1] = TemplateNIPID_P.u_Gain_i *
      TemplateNIPID_B.Product_kt[1];

    /* Product: '<S41>/Product' */
    tmp = TemplateNIPID_B.u_m[0] * TemplateNIPID_B.Product_c[0];
    tmp += TemplateNIPID_B.u_m[1] * TemplateNIPID_B.Product_c[1];
    TemplateNIPID_B.VectorConcatenate_k[2] = tmp;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Constant: '<S47>/0_2x1' */
      TemplateNIPID_B.VectorConcatenate_c[0] = TemplateNIPID_P._2x1_Value[0];
      TemplateNIPID_B.VectorConcatenate_c[1] = TemplateNIPID_P._2x1_Value[1];

      /* Product: '<S175>/Product' incorporates:
       *  Constant: '<S165>/0_2x1'
       */
      TemplateNIPID_B.Product_h[0] = TemplateNIPID_P._2x1_Value_a[0] *
        TemplateNIPID_B.RoundingFunction;
      TemplateNIPID_B.Product_h[1] = TemplateNIPID_P._2x1_Value_a[1] *
        TemplateNIPID_B.RoundingFunction;
    }

    /* Product: '<S168>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    TemplateNIPID_B.Product2_nb = TemplateNIPID_B.Integrator1 *
      TemplateNIPID_P.k_Value;

    /* Trigonometry: '<S168>/cos(s)' */
    TemplateNIPID_B.coss_n = cos(TemplateNIPID_B.Product2_nb);
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S168>/Math Function' incorporates:
       *  Constant: '<S10>/k [-]'
       */
      tmp = TemplateNIPID_P.k_Value;
      TemplateNIPID_B.MathFunction_kc = tmp * tmp;
    }

    /* Product: '<S168>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    TemplateNIPID_B.Product_p = TemplateNIPID_P.r_xm_Value *
      TemplateNIPID_B.coss_n * TemplateNIPID_B.MathFunction_kc;

    /* Gain: '<S168>/Gain' */
    TemplateNIPID_B.Gain_m = TemplateNIPID_P.Gain_Gain_fv *
      TemplateNIPID_B.Product_p;

    /* Trigonometry: '<S168>/sin(s)' */
    TemplateNIPID_B.sins_a = sin(TemplateNIPID_B.Product2_nb);

    /* Product: '<S168>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    TemplateNIPID_B.Product1_hr = TemplateNIPID_P.r_ym_Value *
      TemplateNIPID_B.sins_a * TemplateNIPID_B.MathFunction_kc;

    /* Gain: '<S168>/Gain1' */
    TemplateNIPID_B.Gain1_o = TemplateNIPID_P.Gain1_Gain_f *
      TemplateNIPID_B.Product1_hr;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Sum: '<S175>/Subract' incorporates:
       *  Constant: '<S175>/Constant'
       */
      TemplateNIPID_B.Subract_d = TemplateNIPID_P.Constant_Value_b0 -
        TemplateNIPID_B.RoundingFunction;
    }

    /* Product: '<S175>/Product1' */
    TemplateNIPID_B.Product1_k[0] = TemplateNIPID_B.Gain_m *
      TemplateNIPID_B.Subract_d;
    TemplateNIPID_B.Product1_k[1] = TemplateNIPID_B.Gain1_o *
      TemplateNIPID_B.Subract_d;

    /* Sum: '<S175>/Add' */
    TemplateNIPID_B.Add_a[0] = TemplateNIPID_B.Product_h[0] +
      TemplateNIPID_B.Product1_k[0];
    TemplateNIPID_B.Add_a[1] = TemplateNIPID_B.Product_h[1] +
      TemplateNIPID_B.Product1_k[1];

    /* Product: '<S120>/x_d^s * y_d^s^2' */
    TemplateNIPID_B.x_dsy_ds2 = TemplateNIPID_B.Add[0] * TemplateNIPID_B.Add_a[1];

    /* Product: '<S120>/x_d^s^2 * y_d^s' */
    TemplateNIPID_B.x_ds2y_ds = TemplateNIPID_B.Add_a[0] * TemplateNIPID_B.Add[1];

    /* Sum: '<S120>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
    TemplateNIPID_B.x_dsy_ds2x_ds2y_ds = TemplateNIPID_B.x_dsy_ds2 -
      TemplateNIPID_B.x_ds2y_ds;

    /* Math: '<S120>/( x_d^s )^2' */
    tmp = TemplateNIPID_B.Add[0];
    TemplateNIPID_B.x_ds2 = tmp * tmp;

    /* Math: '<S120>/( y_d^s )^2' */
    tmp = TemplateNIPID_B.Add[1];
    TemplateNIPID_B.y_ds2 = tmp * tmp;

    /* Sum: '<S120>/( x_d^s )^2 + ( y_d^s )^2' */
    TemplateNIPID_B.x_ds2y_ds2 = TemplateNIPID_B.x_ds2 + TemplateNIPID_B.y_ds2;

    /* Product: '<S120>/Divide' */
    TemplateNIPID_B.Divide_i = TemplateNIPID_B.x_dsy_ds2x_ds2y_ds /
      TemplateNIPID_B.x_ds2y_ds2;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S148>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2_l = tmp * tmp;
    }

    /* Math: '<S148>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2_b = tmp * tmp;

    /* Sum: '<S148>/Add' */
    TemplateNIPID_B.Add_e = TemplateNIPID_B.Delta2_l +
      TemplateNIPID_B.epsilon_n2_b;

    /* Product: '<S148>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Divide_ix = TemplateNIPID_P.Deltam_Value /
      TemplateNIPID_B.Add_e;

    /* Outputs for atomic SubSystem: '<S127>/S_2' */

    /* Gain: '<S155>/S12' */
    TemplateNIPID_B.S12_ao = TemplateNIPID_P.S12_Gain_m *
      TemplateNIPID_B.Divide_i;

    /* Reshape: '<S155>/S_2(psi_d^s)' incorporates:
     *  Constant: '<S155>/0'
     */
    TemplateNIPID_B.S_2psi_ds[0] = TemplateNIPID_P._Value;
    TemplateNIPID_B.S_2psi_ds[1] = TemplateNIPID_B.Divide_i;
    TemplateNIPID_B.S_2psi_ds[2] = TemplateNIPID_B.S12_ao;
    TemplateNIPID_B.S_2psi_ds[3] = TemplateNIPID_P._Value;

    /* end of Outputs for SubSystem: '<S127>/S_2' */

    /* Math: '<S158>/Math Function' */
    TemplateNIPID_B.MathFunction_ch[0] = TemplateNIPID_B.S_2psi_ds[0];
    TemplateNIPID_B.MathFunction_ch[1] = TemplateNIPID_B.S_2psi_ds[2];
    TemplateNIPID_B.MathFunction_ch[2] = TemplateNIPID_B.S_2psi_ds[1];
    TemplateNIPID_B.MathFunction_ch[3] = TemplateNIPID_B.S_2psi_ds[3];

    /* Product: '<S160>/Product' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += TemplateNIPID_B.MathFunction_ch[i] *
        TemplateNIPID_B.MathFunction_n[0];
      tmp_2[i] += TemplateNIPID_B.MathFunction_ch[i + 2] *
        TemplateNIPID_B.MathFunction_n[1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += TemplateNIPID_B.MathFunction_ch[i] *
        TemplateNIPID_B.MathFunction_n[2];
      tmp_2[i + 2] += TemplateNIPID_B.MathFunction_ch[i + 2] *
        TemplateNIPID_B.MathFunction_n[3];
    }

    TemplateNIPID_B.Product_ht[0] = 0.0;
    TemplateNIPID_B.Product_ht[0] = tmp_2[0] * TemplateNIPID_B.Subtract[0] +
      TemplateNIPID_B.Product_ht[0];
    TemplateNIPID_B.Product_ht[0] = tmp_2[2] * TemplateNIPID_B.Subtract[1] +
      TemplateNIPID_B.Product_ht[0];

    /* Product: '<S160>/Product1' */
    TemplateNIPID_B.Product1_m[0] = 0.0;
    TemplateNIPID_B.Product1_m[0] = TemplateNIPID_B.MathFunction_n[0] *
      TemplateNIPID_B.Add[0] + TemplateNIPID_B.Product1_m[0];
    TemplateNIPID_B.Product1_m[0] = TemplateNIPID_B.MathFunction_n[2] *
      TemplateNIPID_B.Add[1] + TemplateNIPID_B.Product1_m[0];

    /* Sum: '<S160>/Subtract1' */
    TemplateNIPID_B.Subtract1[0] = TemplateNIPID_B.Product_ht[0] -
      TemplateNIPID_B.Product1_m[0];
    TemplateNIPID_B.Product_ht[1] = 0.0;
    TemplateNIPID_B.Product_ht[1] = tmp_2[1] * TemplateNIPID_B.Subtract[0] +
      TemplateNIPID_B.Product_ht[1];
    TemplateNIPID_B.Product_ht[1] = tmp_2[3] * TemplateNIPID_B.Subtract[1] +
      TemplateNIPID_B.Product_ht[1];

    /* Product: '<S160>/Product1' */
    TemplateNIPID_B.Product1_m[1] = 0.0;
    TemplateNIPID_B.Product1_m[1] = TemplateNIPID_B.MathFunction_n[1] *
      TemplateNIPID_B.Add[0] + TemplateNIPID_B.Product1_m[1];
    TemplateNIPID_B.Product1_m[1] = TemplateNIPID_B.MathFunction_n[3] *
      TemplateNIPID_B.Add[1] + TemplateNIPID_B.Product1_m[1];

    /* Sum: '<S160>/Subtract1' */
    TemplateNIPID_B.Subtract1[1] = TemplateNIPID_B.Product_ht[1] -
      TemplateNIPID_B.Product1_m[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector2' */
    {
      const byte_T *u = (byte_T *)TemplateNIPID_B.Subtract1;/* input port */
      const int32_T *index = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&TemplateNIPID_B.MultiportSelector2;
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
    TemplateNIPID_B.Product_l = TemplateNIPID_B.Divide_ix *
      TemplateNIPID_B.MultiportSelector2;

    /* Sum: '<S148>/Subtract' */
    TemplateNIPID_B.Subtract_n = TemplateNIPID_B.Divide_i -
      TemplateNIPID_B.Product_l;

    /* Math: '<S133>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2_p = tmp * tmp;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S133>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2_b = tmp * tmp;
    }

    /* Sum: '<S133>/Add' */
    TemplateNIPID_B.Add_d = TemplateNIPID_B.epsilon_n2_p +
      TemplateNIPID_B.Delta2_b;

    /* Math: '<S133>/sqrt' */
    tmp = TemplateNIPID_B.Add_d;
    if (tmp < 0.0) {
      TemplateNIPID_B.sqrt_m = -sqrt(-tmp);
    } else {
      TemplateNIPID_B.sqrt_m = sqrt(tmp);
    }

    /* Product: '<S133>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Divide_k = TemplateNIPID_P.Deltam_Value /
      TemplateNIPID_B.sqrt_m;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S183>/Math Function' */
      TemplateNIPID_B.MathFunction_cq[0] =
        TemplateNIPID_B.TmpHiddenBufferAtProductInport2[0];
      TemplateNIPID_B.MathFunction_cq[1] =
        TemplateNIPID_B.TmpHiddenBufferAtProductInport2[1];

      /* Product: '<S182>/Product' */
      tmp = TemplateNIPID_B.MathFunction_cq[0] *
        TemplateNIPID_B.TmpHiddenBufferAtProductInport2[0];
      tmp += TemplateNIPID_B.MathFunction_cq[1] *
        TemplateNIPID_B.TmpHiddenBufferAtProductInport2[1];
      TemplateNIPID_B.Product_g = tmp;

      /* Math: '<S182>/sqrt' */
      tmp = TemplateNIPID_B.Product_g;
      if (tmp < 0.0) {
        TemplateNIPID_B.sqrt_p = -sqrt(-tmp);
      } else {
        TemplateNIPID_B.sqrt_p = sqrt(tmp);
      }

      /* Product: '<S177>/Product' */
      TemplateNIPID_B.Product_gf = TemplateNIPID_B.sqrt_p *
        TemplateNIPID_B.RoundingFunction;
    }

    /* Math: '<S171>/Math Function' */
    TemplateNIPID_B.MathFunction_ho[0] =
      TemplateNIPID_B.TmpHiddenBufferAtProductInpor_k[0];
    TemplateNIPID_B.MathFunction_ho[1] =
      TemplateNIPID_B.TmpHiddenBufferAtProductInpor_k[1];

    /* Product: '<S170>/Product' */
    tmp = TemplateNIPID_B.MathFunction_ho[0] *
      TemplateNIPID_B.TmpHiddenBufferAtProductInpor_k[0];
    tmp += TemplateNIPID_B.MathFunction_ho[1] *
      TemplateNIPID_B.TmpHiddenBufferAtProductInpor_k[1];
    TemplateNIPID_B.Product_n = tmp;

    /* Math: '<S170>/sqrt' */
    tmp = TemplateNIPID_B.Product_n;
    if (tmp < 0.0) {
      TemplateNIPID_B.sqrt_e = -sqrt(-tmp);
    } else {
      TemplateNIPID_B.sqrt_e = sqrt(tmp);
    }

    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Sum: '<S177>/Subract' incorporates:
       *  Constant: '<S177>/Constant'
       */
      TemplateNIPID_B.Subract_k = TemplateNIPID_P.Constant_Value_e -
        TemplateNIPID_B.RoundingFunction;
    }

    /* Product: '<S177>/Product1' */
    TemplateNIPID_B.Product1_bz = TemplateNIPID_B.sqrt_e *
      TemplateNIPID_B.Subract_k;

    /* Sum: '<S177>/Add' */
    TemplateNIPID_B.Add_df = TemplateNIPID_B.Product_gf +
      TemplateNIPID_B.Product1_bz;

    /* Product: '<S184>/Divide' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateNIPID_B.Divide_l = TemplateNIPID_P.u_dm_Value /
      TemplateNIPID_B.Add_df;

    /* Product: '<S133>/Product' */
    TemplateNIPID_B.Product_pe = TemplateNIPID_B.Divide_k *
      TemplateNIPID_B.Divide_l;

    /* Math: '<S140>/Math Function' */
    TemplateNIPID_B.MathFunction_m[0] = TemplateNIPID_B.Add[0];

    /* Product: '<S137>/Divide' */
    TemplateNIPID_B.Divide_m[0] = TemplateNIPID_B.MathFunction_m[0] /
      TemplateNIPID_B.Add_df;

    /* Math: '<S140>/Math Function' */
    TemplateNIPID_B.MathFunction_m[1] = TemplateNIPID_B.Add[1];

    /* Product: '<S137>/Divide' */
    TemplateNIPID_B.Divide_m[1] = TemplateNIPID_B.MathFunction_m[1] /
      TemplateNIPID_B.Add_df;

    /* Product: '<S137>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    tmp = TemplateNIPID_P.my_Value * TemplateNIPID_B.Divide_m[0] *
      TemplateNIPID_B.Subtract[0];
    tmp += TemplateNIPID_P.my_Value * TemplateNIPID_B.Divide_m[1] *
      TemplateNIPID_B.Subtract[1];
    TemplateNIPID_B.Product_ac = tmp;

    /* Gain: '<S137>/Gain' */
    TemplateNIPID_B.Gain_g = TemplateNIPID_P.Gain_Gain_h *
      TemplateNIPID_B.Product_ac;

    /* Sum: '<S133>/Subtract' */
    TemplateNIPID_B.Subtract_ni = TemplateNIPID_B.Product_pe -
      TemplateNIPID_B.Gain_g;

    /* Product: '<S47>/Product' */
    TemplateNIPID_B.VectorConcatenate_c[2] = TemplateNIPID_B.Subtract_n *
      TemplateNIPID_B.Subtract_ni;

    /* Sum: '<S39>/Add' */
    TemplateNIPID_B.Add_o[0] = TemplateNIPID_B.VectorConcatenate_k[0] +
      TemplateNIPID_B.VectorConcatenate_c[0];
    TemplateNIPID_B.Add_o[1] = TemplateNIPID_B.VectorConcatenate_k[1] +
      TemplateNIPID_B.VectorConcatenate_c[1];
    TemplateNIPID_B.Add_o[2] = TemplateNIPID_B.VectorConcatenate_k[2] +
      TemplateNIPID_B.VectorConcatenate_c[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S37>/Product' */
      TemplateNIPID_B.Product_kj[i] = 0.0;
      TemplateNIPID_B.Product_kj[i] = TemplateNIPID_B.MathFunction[i] *
        TemplateNIPID_B.Add_o[0] + TemplateNIPID_B.Product_kj[i];
      TemplateNIPID_B.Product_kj[i] = TemplateNIPID_B.MathFunction[i + 3] *
        TemplateNIPID_B.Add_o[1] + TemplateNIPID_B.Product_kj[i];
      TemplateNIPID_B.Product_kj[i] = TemplateNIPID_B.MathFunction[i + 6] *
        TemplateNIPID_B.Add_o[2] + TemplateNIPID_B.Product_kj[i];

      /* Sum: '<S37>/Subtract' */
      TemplateNIPID_B.Subtract_k[i] = TemplateNIPID_B.nuSwitch[i] -
        TemplateNIPID_B.Product_kj[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S53>/Product2' */
      TemplateNIPID_B.Product2_m[i] = 0.0;
      TemplateNIPID_B.Product2_m[i] = TemplateNIPID_B.ux3[i] *
        TemplateNIPID_B.Subtract_k[0] + TemplateNIPID_B.Product2_m[i];
      TemplateNIPID_B.Product2_m[i] = TemplateNIPID_B.ux3[i + 3] *
        TemplateNIPID_B.Subtract_k[1] + TemplateNIPID_B.Product2_m[i];
      TemplateNIPID_B.Product2_m[i] = TemplateNIPID_B.ux3[i + 6] *
        TemplateNIPID_B.Subtract_k[2] + TemplateNIPID_B.Product2_m[i];

      /* Gain: '<S53>/Gain2' */
      TemplateNIPID_B.Gain2[i] = TemplateNIPID_P.Gain2_Gain *
        TemplateNIPID_B.Product2_m[i];

      /* Sum: '<S53>/Sum' */
      TemplateNIPID_B.Sum_g[i] = (TemplateNIPID_B.Gain_p[i] +
        TemplateNIPID_B.Gain1_a[i]) + TemplateNIPID_B.Gain2[i];

      /* Product: '<S52>/Product1' */
      TemplateNIPID_B.Product1_h4[i] = 0.0;
      TemplateNIPID_B.Product1_h4[i] = TemplateNIPID_B.LinearDampningmatrix[i] *
        TemplateNIPID_B.nuSwitch[0] + TemplateNIPID_B.Product1_h4[i];
      TemplateNIPID_B.Product1_h4[i] = TemplateNIPID_B.LinearDampningmatrix[i +
        3] * TemplateNIPID_B.nuSwitch[1] + TemplateNIPID_B.Product1_h4[i];
      TemplateNIPID_B.Product1_h4[i] = TemplateNIPID_B.LinearDampningmatrix[i +
        6] * TemplateNIPID_B.nuSwitch[2] + TemplateNIPID_B.Product1_h4[i];

      /* Product: '<S33>/Product' incorporates:
       *  Constant: '<S1>/tauxscale'
       */
      TemplateNIPID_B.Product_d3[i] = TemplateNIPID_P.tauxscale_Value *
        TemplateNIPID_B.Product1_h4[i];
    }

    /* Trigonometry: '<S130>/Trigonometric Function1' */
    TemplateNIPID_B.TrigonometricFunction1 = sin(TemplateNIPID_B.Sum_e);

    /* Gain: '<S130>/Gain' */
    TemplateNIPID_B.Gain_k3 = TemplateNIPID_P.Gain_Gain_j *
      TemplateNIPID_B.TrigonometricFunction1;

    /* Trigonometry: '<S130>/Trigonometric Function' */
    TemplateNIPID_B.TrigonometricFunction_e = cos(TemplateNIPID_B.Sum_e);

    /* Product: '<S130>/Product1' */
    TemplateNIPID_B.Product1_j[0] = TemplateNIPID_B.Gain_k3 *
      TemplateNIPID_B.u_m[0];

    /* Product: '<S130>/Product2' */
    TemplateNIPID_B.Product2_l[0] = TemplateNIPID_B.TrigonometricFunction_e *
      TemplateNIPID_B.u_m[0];

    /* Product: '<S130>/Product1' */
    TemplateNIPID_B.Product1_j[1] = TemplateNIPID_B.Gain_k3 *
      TemplateNIPID_B.u_m[1];

    /* Product: '<S130>/Product2' */
    TemplateNIPID_B.Product2_l[1] = TemplateNIPID_B.TrigonometricFunction_e *
      TemplateNIPID_B.u_m[1];

    /* Concatenate: '<S130>/Matrix Concatenate' */
    TemplateNIPID_B.MatrixConcatenate[0] = TemplateNIPID_B.Product1_j[0];
    TemplateNIPID_B.MatrixConcatenate[2] = TemplateNIPID_B.Product1_j[1];
    TemplateNIPID_B.MatrixConcatenate[1] = TemplateNIPID_B.Product2_l[0];
    TemplateNIPID_B.MatrixConcatenate[3] = TemplateNIPID_B.Product2_l[1];

    /* Product: '<S130>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateNIPID_B.Product_ay[0] = TemplateNIPID_B.MatrixConcatenate[0] *
      TemplateNIPID_P.u_dm_Value;
    TemplateNIPID_B.Product_ay[1] = TemplateNIPID_B.MatrixConcatenate[1] *
      TemplateNIPID_P.u_dm_Value;
    TemplateNIPID_B.Product_ay[2] = TemplateNIPID_B.MatrixConcatenate[2] *
      TemplateNIPID_P.u_dm_Value;
    TemplateNIPID_B.Product_ay[3] = TemplateNIPID_B.MatrixConcatenate[3] *
      TemplateNIPID_P.u_dm_Value;

    /* Product: '<S146>/Product2' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product2_p = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.MultiportSelector;

    /* Math: '<S45>/Math Function' */
    TemplateNIPID_B.MathFunction_cw[0] = TemplateNIPID_B.Product_c[0];

    /* Math: '<S146>/Math Function' */
    TemplateNIPID_B.MathFunction_ct[0] = TemplateNIPID_B.MultiportSelector1[0];

    /* Math: '<S45>/Math Function' */
    TemplateNIPID_B.MathFunction_cw[1] = TemplateNIPID_B.Product_c[1];

    /* Math: '<S146>/Math Function' */
    TemplateNIPID_B.MathFunction_ct[1] = TemplateNIPID_B.MultiportSelector1[1];

    /* Product: '<S146>/Product3' */
    TemplateNIPID_B.Product3[0] = 0.0;
    TemplateNIPID_B.Product3[0] = TemplateNIPID_B.MathFunction_ct[0] *
      TemplateNIPID_B.MultiportSelector1[0] + TemplateNIPID_B.Product3[0];
    TemplateNIPID_B.Product3[2] = 0.0;
    TemplateNIPID_B.Product3[2] = TemplateNIPID_B.MathFunction_ct[0] *
      TemplateNIPID_B.MultiportSelector1[1] + TemplateNIPID_B.Product3[2];
    TemplateNIPID_B.Product3[1] = 0.0;
    TemplateNIPID_B.Product3[1] = TemplateNIPID_B.MathFunction_ct[1] *
      TemplateNIPID_B.MultiportSelector1[0] + TemplateNIPID_B.Product3[1];
    TemplateNIPID_B.Product3[3] = 0.0;
    TemplateNIPID_B.Product3[3] = TemplateNIPID_B.MathFunction_ct[1] *
      TemplateNIPID_B.MultiportSelector1[1] + TemplateNIPID_B.Product3[3];

    /* Product: '<S146>/Product4' */
    TemplateNIPID_B.Product4[0] = TemplateNIPID_B.Product2_p *
      TemplateNIPID_B.Product3[0];

    /* Gain: '<S146>/2' */
    TemplateNIPID_B.u_ma[0] = TemplateNIPID_P._Gain * TemplateNIPID_B.Product4[0];

    /* Product: '<S146>/Product4' */
    TemplateNIPID_B.Product4[1] = TemplateNIPID_B.Product2_p *
      TemplateNIPID_B.Product3[1];

    /* Gain: '<S146>/2' */
    TemplateNIPID_B.u_ma[1] = TemplateNIPID_P._Gain * TemplateNIPID_B.Product4[1];

    /* Product: '<S146>/Product4' */
    TemplateNIPID_B.Product4[2] = TemplateNIPID_B.Product2_p *
      TemplateNIPID_B.Product3[2];

    /* Gain: '<S146>/2' */
    TemplateNIPID_B.u_ma[2] = TemplateNIPID_P._Gain * TemplateNIPID_B.Product4[2];

    /* Product: '<S146>/Product4' */
    TemplateNIPID_B.Product4[3] = TemplateNIPID_B.Product2_p *
      TemplateNIPID_B.Product3[3];

    /* Gain: '<S146>/2' */
    TemplateNIPID_B.u_ma[3] = TemplateNIPID_P._Gain * TemplateNIPID_B.Product4[3];
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S146>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2_g = tmp * tmp;
    }

    /* Math: '<S146>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2_f = tmp * tmp;

    /* Sum: '<S146>/Add' */
    TemplateNIPID_B.Add_n = TemplateNIPID_B.Delta2_g +
      TemplateNIPID_B.epsilon_n2_f;

    /* Math: '<S146>/( )^2' */
    tmp = TemplateNIPID_B.Add_n;
    TemplateNIPID_B.u_j = tmp * tmp;

    /* Product: '<S146>/Divide' */
    TemplateNIPID_B.Divide_h[0] = TemplateNIPID_B.u_ma[0] / TemplateNIPID_B.u_j;
    TemplateNIPID_B.Divide_h[1] = TemplateNIPID_B.u_ma[1] / TemplateNIPID_B.u_j;
    TemplateNIPID_B.Divide_h[2] = TemplateNIPID_B.u_ma[2] / TemplateNIPID_B.u_j;
    TemplateNIPID_B.Divide_h[3] = TemplateNIPID_B.u_ma[3] / TemplateNIPID_B.u_j;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Product: '<S146>/Product1' incorporates:
       *  Constant: '<S127>/0_2x2'
       *  Constant: '<S5>/Delta [m]'
       */
      TemplateNIPID_B.Product1_kt[0] = TemplateNIPID_P.Deltam_Value *
        TemplateNIPID_P._2x2_Value[0];
      TemplateNIPID_B.Product1_kt[1] = TemplateNIPID_P.Deltam_Value *
        TemplateNIPID_P._2x2_Value[1];
      TemplateNIPID_B.Product1_kt[2] = TemplateNIPID_P.Deltam_Value *
        TemplateNIPID_P._2x2_Value[2];
      TemplateNIPID_B.Product1_kt[3] = TemplateNIPID_P.Deltam_Value *
        TemplateNIPID_P._2x2_Value[3];
    }

    /* Product: '<S146>/Divide1' */
    TemplateNIPID_B.Divide1[0] = TemplateNIPID_B.Product1_kt[0] /
      TemplateNIPID_B.Add_n;

    /* Sum: '<S146>/Subtract' */
    TemplateNIPID_B.Subtract_d[0] = TemplateNIPID_B.Divide_h[0] -
      TemplateNIPID_B.Divide1[0];

    /* Product: '<S146>/Divide1' */
    TemplateNIPID_B.Divide1[1] = TemplateNIPID_B.Product1_kt[1] /
      TemplateNIPID_B.Add_n;

    /* Sum: '<S146>/Subtract' */
    TemplateNIPID_B.Subtract_d[1] = TemplateNIPID_B.Divide_h[1] -
      TemplateNIPID_B.Divide1[1];

    /* Product: '<S146>/Divide1' */
    TemplateNIPID_B.Divide1[2] = TemplateNIPID_B.Product1_kt[2] /
      TemplateNIPID_B.Add_n;

    /* Sum: '<S146>/Subtract' */
    TemplateNIPID_B.Subtract_d[2] = TemplateNIPID_B.Divide_h[2] -
      TemplateNIPID_B.Divide1[2];

    /* Product: '<S146>/Divide1' */
    TemplateNIPID_B.Divide1[3] = TemplateNIPID_B.Product1_kt[3] /
      TemplateNIPID_B.Add_n;

    /* Sum: '<S146>/Subtract' */
    TemplateNIPID_B.Subtract_d[3] = TemplateNIPID_B.Divide_h[3] -
      TemplateNIPID_B.Divide1[3];

    /* Math: '<S46>/Math Function' */
    TemplateNIPID_B.MathFunction_l[0] = TemplateNIPID_B.Subtract_d[0];
    TemplateNIPID_B.MathFunction_l[1] = TemplateNIPID_B.Subtract_d[2];
    TemplateNIPID_B.MathFunction_l[2] = TemplateNIPID_B.Subtract_d[1];
    TemplateNIPID_B.MathFunction_l[3] = TemplateNIPID_B.Subtract_d[3];

    /* Product: '<S42>/Product' */
    TemplateNIPID_B.Product_o[0] = 0.0;
    TemplateNIPID_B.Product_o[0] = TemplateNIPID_B.MathFunction_cw[0] *
      TemplateNIPID_B.MathFunction_l[0] + TemplateNIPID_B.Product_o[0];
    TemplateNIPID_B.Product_o[0] = TemplateNIPID_B.MathFunction_cw[1] *
      TemplateNIPID_B.MathFunction_l[1] + TemplateNIPID_B.Product_o[0];

    /* Product: '<S42>/Product1' */
    TemplateNIPID_B.Product1_ay[0] = 0.0;
    TemplateNIPID_B.Product1_ay[0] = TemplateNIPID_B.u_m[0] *
      TemplateNIPID_B.Product_ay[0] + TemplateNIPID_B.Product1_ay[0];
    TemplateNIPID_B.Product1_ay[0] = TemplateNIPID_B.u_m[1] *
      TemplateNIPID_B.Product_ay[1] + TemplateNIPID_B.Product1_ay[0];

    /* Sum: '<S42>/Add' */
    TemplateNIPID_B.Add_am[0] = TemplateNIPID_B.Product_o[0] +
      TemplateNIPID_B.Product1_ay[0];

    /* Product: '<S42>/Product' */
    TemplateNIPID_B.Product_o[1] = 0.0;
    TemplateNIPID_B.Product_o[1] = TemplateNIPID_B.MathFunction_cw[0] *
      TemplateNIPID_B.MathFunction_l[2] + TemplateNIPID_B.Product_o[1];
    TemplateNIPID_B.Product_o[1] = TemplateNIPID_B.MathFunction_cw[1] *
      TemplateNIPID_B.MathFunction_l[3] + TemplateNIPID_B.Product_o[1];

    /* Product: '<S42>/Product1' */
    TemplateNIPID_B.Product1_ay[1] = 0.0;
    TemplateNIPID_B.Product1_ay[1] = TemplateNIPID_B.u_m[0] *
      TemplateNIPID_B.Product_ay[2] + TemplateNIPID_B.Product1_ay[1];
    TemplateNIPID_B.Product1_ay[1] = TemplateNIPID_B.u_m[1] *
      TemplateNIPID_B.Product_ay[3] + TemplateNIPID_B.Product1_ay[1];

    /* Sum: '<S42>/Add' */
    TemplateNIPID_B.Add_am[1] = TemplateNIPID_B.Product_o[1] +
      TemplateNIPID_B.Product1_ay[1];

    /* Concatenate: '<S42>/Matrix Concatenate' */
    TemplateNIPID_B.MatrixConcatenate_b[0] = TemplateNIPID_B.Product_ay[0];
    TemplateNIPID_B.MatrixConcatenate_b[1] = TemplateNIPID_B.Product_ay[1];
    TemplateNIPID_B.MatrixConcatenate_b[3] = TemplateNIPID_B.Product_ay[2];
    TemplateNIPID_B.MatrixConcatenate_b[4] = TemplateNIPID_B.Product_ay[3];
    TemplateNIPID_B.MatrixConcatenate_b[2] = TemplateNIPID_B.Add_am[0];
    TemplateNIPID_B.MatrixConcatenate_b[5] = TemplateNIPID_B.Add_am[1];

    /* Product: '<S147>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product_m[0] = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.MultiportSelector * TemplateNIPID_B.MultiportSelector2 *
      TemplateNIPID_B.MultiportSelector1[0];

    /* Gain: '<S147>/2' */
    TemplateNIPID_B.u_n[0] = TemplateNIPID_P._Gain_d *
      TemplateNIPID_B.Product_m[0];

    /* Product: '<S147>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product_m[1] = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.MultiportSelector * TemplateNIPID_B.MultiportSelector2 *
      TemplateNIPID_B.MultiportSelector1[1];

    /* Gain: '<S147>/2' */
    TemplateNIPID_B.u_n[1] = TemplateNIPID_P._Gain_d *
      TemplateNIPID_B.Product_m[1];
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S147>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2_p = tmp * tmp;
    }

    /* Math: '<S147>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2_a = tmp * tmp;

    /* Sum: '<S147>/Add' */
    TemplateNIPID_B.Add_j = TemplateNIPID_B.Delta2_p +
      TemplateNIPID_B.epsilon_n2_a;

    /* Math: '<S147>/( )^2' */
    tmp = TemplateNIPID_B.Add_j;
    TemplateNIPID_B.u_f = tmp * tmp;

    /* Product: '<S147>/Divide' */
    TemplateNIPID_B.Divide_b[0] = TemplateNIPID_B.u_n[0] / TemplateNIPID_B.u_f;
    TemplateNIPID_B.Divide_b[1] = TemplateNIPID_B.u_n[1] / TemplateNIPID_B.u_f;

    /* Product: '<S159>/Product1' */
    for (i = 0; i < 2; i++) {
      TemplateNIPID_B.Product1_p1[i] = 0.0;
      TemplateNIPID_B.Product1_p1[i] = TemplateNIPID_B.MathFunction_ch[i] *
        TemplateNIPID_B.MathFunction_n[0] + TemplateNIPID_B.Product1_p1[i];
      TemplateNIPID_B.Product1_p1[i] = TemplateNIPID_B.MathFunction_ch[i + 2] *
        TemplateNIPID_B.MathFunction_n[1] + TemplateNIPID_B.Product1_p1[i];
      TemplateNIPID_B.Product1_p1[i + 2] = 0.0;
      TemplateNIPID_B.Product1_p1[i + 2] = TemplateNIPID_B.Product1_p1[i + 2] +
        TemplateNIPID_B.MathFunction_ch[i] * TemplateNIPID_B.MathFunction_n[2];
      TemplateNIPID_B.Product1_p1[i + 2] = TemplateNIPID_B.MathFunction_ch[i + 2]
        * TemplateNIPID_B.MathFunction_n[3] + TemplateNIPID_B.Product1_p1[i + 2];
    }

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector3' */
    {
      const byte_T *u = (byte_T *)TemplateNIPID_B.Product1_p1;/* input port */
      const int32_T *index = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)TemplateNIPID_B.MultiportSelector3;
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
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product1_bp[0] = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.MultiportSelector3[0];

    /* Product: '<S147>/Divide1' */
    TemplateNIPID_B.Divide1_b[0] = TemplateNIPID_B.Product1_bp[0] /
      TemplateNIPID_B.Add_j;

    /* Sum: '<S147>/Subtract' */
    TemplateNIPID_B.Subtract_g[0] = TemplateNIPID_B.Divide_b[0] -
      TemplateNIPID_B.Divide1_b[0];

    /* Product: '<S48>/Product' */
    TemplateNIPID_B.Product_e[0] = TemplateNIPID_B.Subtract_g[0] *
      TemplateNIPID_B.Subtract_ni;

    /* Product: '<S134>/Product1' */
    TemplateNIPID_B.Product1_c[0] = TemplateNIPID_B.MultiportSelector *
      TemplateNIPID_B.MultiportSelector1[0];

    /* Product: '<S147>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product1_bp[1] = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.MultiportSelector3[1];

    /* Product: '<S147>/Divide1' */
    TemplateNIPID_B.Divide1_b[1] = TemplateNIPID_B.Product1_bp[1] /
      TemplateNIPID_B.Add_j;

    /* Sum: '<S147>/Subtract' */
    TemplateNIPID_B.Subtract_g[1] = TemplateNIPID_B.Divide_b[1] -
      TemplateNIPID_B.Divide1_b[1];

    /* Product: '<S48>/Product' */
    TemplateNIPID_B.Product_e[1] = TemplateNIPID_B.Subtract_g[1] *
      TemplateNIPID_B.Subtract_ni;

    /* Product: '<S134>/Product1' */
    TemplateNIPID_B.Product1_c[1] = TemplateNIPID_B.MultiportSelector *
      TemplateNIPID_B.MultiportSelector1[1];

    /* Math: '<S134>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2_at = tmp * tmp;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S134>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2_n = tmp * tmp;
    }

    /* Sum: '<S134>/Add' */
    TemplateNIPID_B.Add_ai = TemplateNIPID_B.epsilon_n2_at +
      TemplateNIPID_B.Delta2_n;

    /* Math: '<S134>/^3//2' incorporates:
     *  Constant: '<S134>/3//2'
     */
    if ((TemplateNIPID_B.Add_ai < 0.0) && (TemplateNIPID_P.u_Value_pg > floor
         (TemplateNIPID_P.u_Value_pg))) {
      TemplateNIPID_B.u2 = -rt_pow_snf(-TemplateNIPID_B.Add_ai,
        TemplateNIPID_P.u_Value_pg);
    } else {
      TemplateNIPID_B.u2 = rt_pow_snf(TemplateNIPID_B.Add_ai,
        TemplateNIPID_P.u_Value_pg);
    }

    /* Product: '<S134>/Divide' */
    TemplateNIPID_B.Divide_k1[0] = TemplateNIPID_B.Product1_c[0] /
      TemplateNIPID_B.u2;

    /* Product: '<S134>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product_c4[0] = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.Divide_k1[0] * TemplateNIPID_B.Divide_l;

    /* Math: '<S141>/Math Function' */
    TemplateNIPID_B.MathFunction_j[0] = TemplateNIPID_B.Add[0];

    /* Product: '<S138>/Divide' */
    TemplateNIPID_B.Divide_n[0] = TemplateNIPID_B.MathFunction_j[0] /
      TemplateNIPID_B.Add_df;

    /* Product: '<S138>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    TemplateNIPID_B.Product_hk[0] = TemplateNIPID_P.my_Value *
      TemplateNIPID_B.Divide_n[0];

    /* Gain: '<S138>/Gain' */
    TemplateNIPID_B.Gain_a[0] = TemplateNIPID_P.Gain_Gain_g *
      TemplateNIPID_B.Product_hk[0];

    /* Sum: '<S134>/Sum' */
    TemplateNIPID_B.Sum_f4[0] = (0.0 - TemplateNIPID_B.Product_c4[0]) -
      TemplateNIPID_B.Gain_a[0];

    /* Product: '<S48>/Product1' */
    TemplateNIPID_B.Product1_hrb[0] = TemplateNIPID_B.Subtract_n *
      TemplateNIPID_B.Sum_f4[0];

    /* Sum: '<S48>/Add' */
    TemplateNIPID_B.Add_p[0] = TemplateNIPID_B.Product_e[0] +
      TemplateNIPID_B.Product1_hrb[0];

    /* Product: '<S134>/Divide' */
    TemplateNIPID_B.Divide_k1[1] = TemplateNIPID_B.Product1_c[1] /
      TemplateNIPID_B.u2;

    /* Product: '<S134>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product_c4[1] = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.Divide_k1[1] * TemplateNIPID_B.Divide_l;

    /* Math: '<S141>/Math Function' */
    TemplateNIPID_B.MathFunction_j[1] = TemplateNIPID_B.Add[1];

    /* Product: '<S138>/Divide' */
    TemplateNIPID_B.Divide_n[1] = TemplateNIPID_B.MathFunction_j[1] /
      TemplateNIPID_B.Add_df;

    /* Product: '<S138>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    TemplateNIPID_B.Product_hk[1] = TemplateNIPID_P.my_Value *
      TemplateNIPID_B.Divide_n[1];

    /* Gain: '<S138>/Gain' */
    TemplateNIPID_B.Gain_a[1] = TemplateNIPID_P.Gain_Gain_g *
      TemplateNIPID_B.Product_hk[1];

    /* Sum: '<S134>/Sum' */
    TemplateNIPID_B.Sum_f4[1] = (0.0 - TemplateNIPID_B.Product_c4[1]) -
      TemplateNIPID_B.Gain_a[1];

    /* Product: '<S48>/Product1' */
    TemplateNIPID_B.Product1_hrb[1] = TemplateNIPID_B.Subtract_n *
      TemplateNIPID_B.Sum_f4[1];

    /* Sum: '<S48>/Add' */
    TemplateNIPID_B.Add_p[1] = TemplateNIPID_B.Product_e[1] +
      TemplateNIPID_B.Product1_hrb[1];

    /* Concatenate: '<S48>/Matrix Concatenate' incorporates:
     *  Constant: '<S48>/0_2x2'
     */
    TemplateNIPID_B.MatrixConcatenate_k[0] = TemplateNIPID_P._2x2_Value_n[0];
    TemplateNIPID_B.MatrixConcatenate_k[1] = TemplateNIPID_P._2x2_Value_n[1];
    TemplateNIPID_B.MatrixConcatenate_k[3] = TemplateNIPID_P._2x2_Value_n[2];
    TemplateNIPID_B.MatrixConcatenate_k[4] = TemplateNIPID_P._2x2_Value_n[3];
    TemplateNIPID_B.MatrixConcatenate_k[2] = TemplateNIPID_B.Add_p[0];
    TemplateNIPID_B.MatrixConcatenate_k[5] = TemplateNIPID_B.Add_p[1];

    /* Sum: '<S58>/Add' */
    for (i = 0; i < 6; i++) {
      TemplateNIPID_B.Add_jn[i] = TemplateNIPID_B.MatrixConcatenate_b[i] +
        TemplateNIPID_B.MatrixConcatenate_k[i];
    }

    /* Integrator Block: '<S35>/Integrator2'
     */
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateNIPID_PrevZCSigState.Integrator2_Reset_ZCE,
                         TemplateNIPID_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateNIPID_P.ctrl2ResetIntegrator_Value != 0.0) {
        TemplateNIPID_X.Integrator2_CSTATE[0] = TemplateNIPID_P.Integrator2_IC;
        TemplateNIPID_X.Integrator2_CSTATE[1] = TemplateNIPID_P.Integrator2_IC;
      }
    }

    TemplateNIPID_B.Integrator2[0] = TemplateNIPID_X.Integrator2_CSTATE[0];
    TemplateNIPID_B.Integrator2[1] = TemplateNIPID_X.Integrator2_CSTATE[1];

    /* Sum: '<S35>/Add1' */
    TemplateNIPID_B.Add1_g[0] = TemplateNIPID_B.Integrator2[0] +
      TemplateNIPID_B.Product_c[0];
    TemplateNIPID_B.Add1_g[1] = TemplateNIPID_B.Integrator2[1] +
      TemplateNIPID_B.Product_c[1];

    /* Product: '<S36>/Product' */
    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.Product_c3[i] = 0.0;
      TemplateNIPID_B.Product_c3[i] = TemplateNIPID_B.Add_jn[i] *
        TemplateNIPID_B.Add1_g[0] + TemplateNIPID_B.Product_c3[i];
      TemplateNIPID_B.Product_c3[i] = TemplateNIPID_B.Add_jn[i + 3] *
        TemplateNIPID_B.Add1_g[1] + TemplateNIPID_B.Product_c3[i];
    }

    /* Trigonometry: '<S131>/Trigonometric Function1' */
    TemplateNIPID_B.TrigonometricFunction1_f = sin(TemplateNIPID_B.Sum_e);

    /* Gain: '<S131>/Gain' */
    TemplateNIPID_B.Gain_e = TemplateNIPID_P.Gain_Gain_gn *
      TemplateNIPID_B.TrigonometricFunction1_f;

    /* Product: '<S131>/Product1' */
    TemplateNIPID_B.Product1_o = TemplateNIPID_B.Gain_e *
      TemplateNIPID_B.Subtract_n;

    /* Trigonometry: '<S131>/Trigonometric Function' */
    TemplateNIPID_B.TrigonometricFunction_i = cos(TemplateNIPID_B.Sum_e);

    /* Product: '<S131>/Product2' */
    TemplateNIPID_B.Product2_g = TemplateNIPID_B.TrigonometricFunction_i *
      TemplateNIPID_B.Subtract_n;

    /* SignalConversion: '<S131>/TmpHiddenBufferAtProductInport1' */
    TemplateNIPID_B.TmpHiddenBufferAtProductInpor_g[0] =
      TemplateNIPID_B.Product1_o;
    TemplateNIPID_B.TmpHiddenBufferAtProductInpor_g[1] =
      TemplateNIPID_B.Product2_g;

    /* Product: '<S131>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateNIPID_B.Product_le[0] =
      TemplateNIPID_B.TmpHiddenBufferAtProductInpor_g[0] *
      TemplateNIPID_P.u_dm_Value;
    TemplateNIPID_B.Product_le[1] =
      TemplateNIPID_B.TmpHiddenBufferAtProductInpor_g[1] *
      TemplateNIPID_P.u_dm_Value;

    /* SignalConversion: '<S43>/ConcatBufferAtVector ConcatenateIn1' */
    TemplateNIPID_B.VectorConcatenate_m[0] = TemplateNIPID_B.Product_le[0];
    TemplateNIPID_B.VectorConcatenate_m[1] = TemplateNIPID_B.Product_le[1];

    /* Product: '<S43>/Product' */
    tmp = TemplateNIPID_B.Subtract_g[0] * TemplateNIPID_B.Product_c[0];
    tmp += TemplateNIPID_B.Subtract_g[1] * TemplateNIPID_B.Product_c[1];
    TemplateNIPID_B.Product_d2 = tmp;

    /* Product: '<S43>/Product1' */
    tmp = TemplateNIPID_B.u_m[0] * TemplateNIPID_B.Product_le[0];
    tmp += TemplateNIPID_B.u_m[1] * TemplateNIPID_B.Product_le[1];
    TemplateNIPID_B.Product1_b4 = tmp;

    /* Sum: '<S43>/Add' */
    TemplateNIPID_B.VectorConcatenate_m[2] = TemplateNIPID_B.Product_d2 +
      TemplateNIPID_B.Product1_b4;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Constant: '<S49>/0_2x1' */
      TemplateNIPID_B.VectorConcatenate_a[0] = TemplateNIPID_P._2x1_Value_a2[0];
      TemplateNIPID_B.VectorConcatenate_a[1] = TemplateNIPID_P._2x1_Value_a2[1];

      /* Product: '<S176>/Product' incorporates:
       *  Constant: '<S165>/0_2x1'
       */
      TemplateNIPID_B.Product_ar[0] = TemplateNIPID_P._2x1_Value_a[0] *
        TemplateNIPID_B.RoundingFunction;
      TemplateNIPID_B.Product_ar[1] = TemplateNIPID_P._2x1_Value_a[1] *
        TemplateNIPID_B.RoundingFunction;
    }

    /* Product: '<S169>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    TemplateNIPID_B.Product2_gd = TemplateNIPID_B.Integrator1 *
      TemplateNIPID_P.k_Value;

    /* Trigonometry: '<S169>/sin(s)3' */
    TemplateNIPID_B.sins3 = sin(TemplateNIPID_B.Product2_gd);
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S169>/Math Function' incorporates:
       *  Constant: '<S10>/k [-]'
       *  Constant: '<S169>/Constant'
       */
      if ((TemplateNIPID_P.k_Value < 0.0) && (TemplateNIPID_P.Constant_Value_mz >
           floor(TemplateNIPID_P.Constant_Value_mz))) {
        TemplateNIPID_B.MathFunction_i = -rt_pow_snf(-TemplateNIPID_P.k_Value,
          TemplateNIPID_P.Constant_Value_mz);
      } else {
        TemplateNIPID_B.MathFunction_i = rt_pow_snf(TemplateNIPID_P.k_Value,
          TemplateNIPID_P.Constant_Value_mz);
      }
    }

    /* Product: '<S169>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    TemplateNIPID_B.Product_b = TemplateNIPID_P.r_xm_Value *
      TemplateNIPID_B.sins3 * TemplateNIPID_B.MathFunction_i;

    /* Trigonometry: '<S169>/cos(s)3' */
    TemplateNIPID_B.coss3 = cos(TemplateNIPID_B.Product2_gd);

    /* Product: '<S169>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    TemplateNIPID_B.Product1_ju = TemplateNIPID_P.r_ym_Value *
      TemplateNIPID_B.coss3 * TemplateNIPID_B.MathFunction_i;

    /* Gain: '<S169>/Gain' */
    TemplateNIPID_B.Gain_c = TemplateNIPID_P.Gain_Gain_e *
      TemplateNIPID_B.Product1_ju;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Sum: '<S176>/Subract' incorporates:
       *  Constant: '<S176>/Constant'
       */
      TemplateNIPID_B.Subract_c = TemplateNIPID_P.Constant_Value_h -
        TemplateNIPID_B.RoundingFunction;
    }

    /* Product: '<S176>/Product1' */
    TemplateNIPID_B.Product1_jq[0] = TemplateNIPID_B.Product_b *
      TemplateNIPID_B.Subract_c;
    TemplateNIPID_B.Product1_jq[1] = TemplateNIPID_B.Gain_c *
      TemplateNIPID_B.Subract_c;

    /* Sum: '<S176>/Add' */
    TemplateNIPID_B.Add_b[0] = TemplateNIPID_B.Product_ar[0] +
      TemplateNIPID_B.Product1_jq[0];
    TemplateNIPID_B.Add_b[1] = TemplateNIPID_B.Product_ar[1] +
      TemplateNIPID_B.Product1_jq[1];

    /* Product: '<S121>/x_d^s * y_d^s^3 ' */
    TemplateNIPID_B.x_dsy_ds3 = TemplateNIPID_B.Add[0] * TemplateNIPID_B.Add_b[1];

    /* Product: '<S121>/x_d^s^3 * y_d^s' */
    TemplateNIPID_B.x_ds3y_ds = TemplateNIPID_B.Add_b[0] * TemplateNIPID_B.Add[1];

    /* Sum: '<S121>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
    TemplateNIPID_B.x_dsy_ds3x_ds3y_ds = TemplateNIPID_B.x_dsy_ds3 -
      TemplateNIPID_B.x_ds3y_ds;

    /* Product: '<S121>/Product1' */
    TemplateNIPID_B.Product1_f = TemplateNIPID_B.x_dsy_ds3x_ds3y_ds *
      TemplateNIPID_B.x_ds2y_ds2;

    /* Product: '<S121>/x_d^s * x_d^s^2' */
    TemplateNIPID_B.x_dsx_ds2 = TemplateNIPID_B.Add[0] * TemplateNIPID_B.Add_a[0];

    /* Product: '<S121>/y_d^s * y_d^s^2' */
    TemplateNIPID_B.y_dsy_ds2 = TemplateNIPID_B.Add[1] * TemplateNIPID_B.Add_a[1];

    /* Sum: '<S121>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
    TemplateNIPID_B.x_dsx_ds2x_ds3y_ds = TemplateNIPID_B.x_dsx_ds2 +
      TemplateNIPID_B.y_dsy_ds2;

    /* Gain: '<S121>/+ 2' */
    TemplateNIPID_B.u_b = TemplateNIPID_P.u_Gain_k *
      TemplateNIPID_B.x_dsx_ds2x_ds3y_ds;

    /* Product: '<S121>/Product2' */
    TemplateNIPID_B.Product2_i = TemplateNIPID_B.x_dsy_ds2x_ds2y_ds *
      TemplateNIPID_B.u_b;

    /* Sum: '<S121>/Subtract' */
    TemplateNIPID_B.Subtract_b = TemplateNIPID_B.Product1_f -
      TemplateNIPID_B.Product2_i;

    /* Math: '<S121>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
    tmp = TemplateNIPID_B.x_ds2y_ds2;
    TemplateNIPID_B.x_ds2y_ds22 = tmp * tmp;

    /* Product: '<S121>/Divide' */
    TemplateNIPID_B.Divide_d = TemplateNIPID_B.Subtract_b /
      TemplateNIPID_B.x_ds2y_ds22;

    /* Math: '<S149>/(epsilon_n^s)^2' */
    tmp = TemplateNIPID_B.MultiportSelector2;
    TemplateNIPID_B.epsilon_ns2 = tmp * tmp;

    /* Product: '<S149>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product_bu = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.MultiportSelector * TemplateNIPID_B.epsilon_ns2;

    /* Gain: '<S149>/2' */
    TemplateNIPID_B.u_l = TemplateNIPID_P._Gain_e * TemplateNIPID_B.Product_bu;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S149>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2_e = tmp * tmp;
    }

    /* Math: '<S149>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2_k = tmp * tmp;

    /* Sum: '<S149>/Add' */
    TemplateNIPID_B.Add_nt = TemplateNIPID_B.Delta2_e +
      TemplateNIPID_B.epsilon_n2_k;

    /* Math: '<S149>/( )^2' */
    tmp = TemplateNIPID_B.Add_nt;
    TemplateNIPID_B.u_mx = tmp * tmp;

    /* Product: '<S149>/Divide' */
    TemplateNIPID_B.Divide_j = TemplateNIPID_B.u_l / TemplateNIPID_B.u_mx;

    /* Outputs for atomic SubSystem: '<S127>/S_2(psi_d^s^2)' */

    /* Gain: '<S156>/S12' */
    TemplateNIPID_B.S12_a = TemplateNIPID_P.S12_Gain_g *
      TemplateNIPID_B.Divide_d;

    /* Reshape: '<S156>/S_2(psi_d^s^2)' incorporates:
     *  Constant: '<S156>/0'
     */
    TemplateNIPID_B.S_2psi_ds2[0] = TemplateNIPID_P._Value_m;
    TemplateNIPID_B.S_2psi_ds2[1] = TemplateNIPID_B.Divide_d;
    TemplateNIPID_B.S_2psi_ds2[2] = TemplateNIPID_B.S12_a;
    TemplateNIPID_B.S_2psi_ds2[3] = TemplateNIPID_P._Value_m;

    /* end of Outputs for SubSystem: '<S127>/S_2(psi_d^s^2)' */

    /* Math: '<S157>/Math Function' */
    TemplateNIPID_B.MathFunction_b[0] = TemplateNIPID_B.S_2psi_ds2[0];
    TemplateNIPID_B.MathFunction_b[1] = TemplateNIPID_B.S_2psi_ds2[2];
    TemplateNIPID_B.MathFunction_b[2] = TemplateNIPID_B.S_2psi_ds2[1];
    TemplateNIPID_B.MathFunction_b[3] = TemplateNIPID_B.S_2psi_ds2[3];

    /* Product: '<S161>/Product' */
    for (i = 0; i < 2; i++) {
      TemplateNIPID_B.Product_dj[i] = 0.0;
      TemplateNIPID_B.Product_dj[i] = TemplateNIPID_B.MathFunction_ch[i] *
        TemplateNIPID_B.MathFunction_ch[0] + TemplateNIPID_B.Product_dj[i];
      TemplateNIPID_B.Product_dj[i] = TemplateNIPID_B.MathFunction_ch[i + 2] *
        TemplateNIPID_B.MathFunction_ch[1] + TemplateNIPID_B.Product_dj[i];
      TemplateNIPID_B.Product_dj[i + 2] = 0.0;
      TemplateNIPID_B.Product_dj[i + 2] = TemplateNIPID_B.Product_dj[i + 2] +
        TemplateNIPID_B.MathFunction_ch[i] * TemplateNIPID_B.MathFunction_ch[2];
      TemplateNIPID_B.Product_dj[i + 2] = TemplateNIPID_B.MathFunction_ch[i + 2]
        * TemplateNIPID_B.MathFunction_ch[3] + TemplateNIPID_B.Product_dj[i + 2];
    }

    /* Sum: '<S161>/Add' */
    TemplateNIPID_B.Add_k[0] = TemplateNIPID_B.MathFunction_b[0] +
      TemplateNIPID_B.Product_dj[0];
    TemplateNIPID_B.Add_k[1] = TemplateNIPID_B.MathFunction_b[1] +
      TemplateNIPID_B.Product_dj[1];
    TemplateNIPID_B.Add_k[2] = TemplateNIPID_B.MathFunction_b[2] +
      TemplateNIPID_B.Product_dj[2];
    TemplateNIPID_B.Add_k[3] = TemplateNIPID_B.MathFunction_b[3] +
      TemplateNIPID_B.Product_dj[3];

    /* Product: '<S161>/Product1' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += TemplateNIPID_B.Add_k[i] * TemplateNIPID_B.MathFunction_n[0];
      tmp_2[i] += TemplateNIPID_B.Add_k[i + 2] * TemplateNIPID_B.MathFunction_n
        [1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += TemplateNIPID_B.Add_k[i] * TemplateNIPID_B.MathFunction_n
        [2];
      tmp_2[i + 2] += TemplateNIPID_B.Add_k[i + 2] *
        TemplateNIPID_B.MathFunction_n[3];
    }

    TemplateNIPID_B.Product1_g[0] = 0.0;
    TemplateNIPID_B.Product1_g[0] = tmp_2[0] * TemplateNIPID_B.Subtract[0] +
      TemplateNIPID_B.Product1_g[0];
    TemplateNIPID_B.Product1_g[0] = tmp_2[2] * TemplateNIPID_B.Subtract[1] +
      TemplateNIPID_B.Product1_g[0];
    TemplateNIPID_B.Product1_g[1] = 0.0;
    TemplateNIPID_B.Product1_g[1] = tmp_2[1] * TemplateNIPID_B.Subtract[0] +
      TemplateNIPID_B.Product1_g[1];
    TemplateNIPID_B.Product1_g[1] = tmp_2[3] * TemplateNIPID_B.Subtract[1] +
      TemplateNIPID_B.Product1_g[1];

    /* Product: '<S161>/Product2' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += TemplateNIPID_B.MathFunction_ch[i] *
        TemplateNIPID_B.MathFunction_n[0];
      tmp_2[i] += TemplateNIPID_B.MathFunction_ch[i + 2] *
        TemplateNIPID_B.MathFunction_n[1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += TemplateNIPID_B.MathFunction_ch[i] *
        TemplateNIPID_B.MathFunction_n[2];
      tmp_2[i + 2] += TemplateNIPID_B.MathFunction_ch[i + 2] *
        TemplateNIPID_B.MathFunction_n[3];
    }

    TemplateNIPID_B.Product2_d[0] = 0.0;
    TemplateNIPID_B.Product2_d[0] = tmp_2[0] * TemplateNIPID_B.Add[0] +
      TemplateNIPID_B.Product2_d[0];
    TemplateNIPID_B.Product2_d[0] = tmp_2[2] * TemplateNIPID_B.Add[1] +
      TemplateNIPID_B.Product2_d[0];

    /* Gain: '<S161>/2' */
    TemplateNIPID_B.u_i[0] = TemplateNIPID_P._Gain_n *
      TemplateNIPID_B.Product2_d[0];

    /* Product: '<S161>/Product3' */
    TemplateNIPID_B.Product3_l[0] = 0.0;
    TemplateNIPID_B.Product3_l[0] = TemplateNIPID_B.MathFunction_n[0] *
      TemplateNIPID_B.Add_a[0] + TemplateNIPID_B.Product3_l[0];
    TemplateNIPID_B.Product3_l[0] = TemplateNIPID_B.MathFunction_n[2] *
      TemplateNIPID_B.Add_a[1] + TemplateNIPID_B.Product3_l[0];

    /* Sum: '<S161>/Sum' */
    TemplateNIPID_B.Sum_ez[0] = (TemplateNIPID_B.Product1_g[0] -
      TemplateNIPID_B.u_i[0]) - TemplateNIPID_B.Product3_l[0];

    /* Gain: '<S161>/Gain' */
    TemplateNIPID_B.Gain_o[0] = TemplateNIPID_P.Gain_Gain_gp *
      TemplateNIPID_B.Sum_ez[0];
    TemplateNIPID_B.Product2_d[1] = 0.0;
    TemplateNIPID_B.Product2_d[1] = tmp_2[1] * TemplateNIPID_B.Add[0] +
      TemplateNIPID_B.Product2_d[1];
    TemplateNIPID_B.Product2_d[1] = tmp_2[3] * TemplateNIPID_B.Add[1] +
      TemplateNIPID_B.Product2_d[1];

    /* Gain: '<S161>/2' */
    TemplateNIPID_B.u_i[1] = TemplateNIPID_P._Gain_n *
      TemplateNIPID_B.Product2_d[1];

    /* Product: '<S161>/Product3' */
    TemplateNIPID_B.Product3_l[1] = 0.0;
    TemplateNIPID_B.Product3_l[1] = TemplateNIPID_B.MathFunction_n[1] *
      TemplateNIPID_B.Add_a[0] + TemplateNIPID_B.Product3_l[1];
    TemplateNIPID_B.Product3_l[1] = TemplateNIPID_B.MathFunction_n[3] *
      TemplateNIPID_B.Add_a[1] + TemplateNIPID_B.Product3_l[1];

    /* Sum: '<S161>/Sum' */
    TemplateNIPID_B.Sum_ez[1] = (TemplateNIPID_B.Product1_g[1] -
      TemplateNIPID_B.u_i[1]) - TemplateNIPID_B.Product3_l[1];

    /* Gain: '<S161>/Gain' */
    TemplateNIPID_B.Gain_o[1] = TemplateNIPID_P.Gain_Gain_gp *
      TemplateNIPID_B.Sum_ez[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector4' */
    {
      const byte_T *u = (byte_T *)TemplateNIPID_B.Gain_o;/* input port */
      const int32_T *index = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateNIPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&TemplateNIPID_B.MultiportSelector4;
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
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product1_ma = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.MultiportSelector4;

    /* Product: '<S149>/Divide1' */
    TemplateNIPID_B.Divide1_c = TemplateNIPID_B.Product1_ma /
      TemplateNIPID_B.Add_nt;

    /* Sum: '<S149>/Sum' */
    TemplateNIPID_B.Sum_g4 = (TemplateNIPID_B.Divide_d +
      TemplateNIPID_B.Divide_j) - TemplateNIPID_B.Divide1_c;

    /* Product: '<S49>/Product' */
    TemplateNIPID_B.Product_a2 = TemplateNIPID_B.Sum_g4 *
      TemplateNIPID_B.Subtract_ni;

    /* Math: '<S187>/Math Function' */
    TemplateNIPID_B.MathFunction_d[0] = TemplateNIPID_B.Add[0];
    TemplateNIPID_B.MathFunction_d[1] = TemplateNIPID_B.Add[1];

    /* Product: '<S185>/Product1' */
    tmp = TemplateNIPID_B.MathFunction_d[0] * TemplateNIPID_B.Add_a[0];
    tmp += TemplateNIPID_B.MathFunction_d[1] * TemplateNIPID_B.Add_a[1];
    TemplateNIPID_B.Product1_gc = tmp;

    /* Math: '<S185>/|p_d^s|^3' incorporates:
     *  Constant: '<S185>/Constant'
     */
    if ((TemplateNIPID_B.Add_df < 0.0) && (TemplateNIPID_P.Constant_Value_n >
         floor(TemplateNIPID_P.Constant_Value_n))) {
      TemplateNIPID_B.p_ds3 = -rt_pow_snf(-TemplateNIPID_B.Add_df,
        TemplateNIPID_P.Constant_Value_n);
    } else {
      TemplateNIPID_B.p_ds3 = rt_pow_snf(TemplateNIPID_B.Add_df,
        TemplateNIPID_P.Constant_Value_n);
    }

    /* Product: '<S185>/Divide' */
    TemplateNIPID_B.Divide_f = TemplateNIPID_B.Product1_gc /
      TemplateNIPID_B.p_ds3;

    /* Product: '<S185>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateNIPID_B.Product_lk = TemplateNIPID_B.Divide_f *
      TemplateNIPID_P.u_dm_Value;

    /* Gain: '<S185>/Gain' */
    TemplateNIPID_B.Gain_pz = TemplateNIPID_P.Gain_Gain_jq *
      TemplateNIPID_B.Product_lk;

    /* Math: '<S135>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2_pv = tmp * tmp;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S135>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2_m = tmp * tmp;
    }

    /* Sum: '<S135>/Add' */
    TemplateNIPID_B.Add_pj = TemplateNIPID_B.epsilon_n2_pv +
      TemplateNIPID_B.Delta2_m;

    /* Math: '<S135>/Math Function' */
    tmp = TemplateNIPID_B.Add_pj;
    if (tmp < 0.0) {
      TemplateNIPID_B.MathFunction_jr = -sqrt(-tmp);
    } else {
      TemplateNIPID_B.MathFunction_jr = sqrt(tmp);
    }

    /* Product: '<S135>/Divide' */
    TemplateNIPID_B.Divide_km = TemplateNIPID_B.Gain_pz /
      TemplateNIPID_B.MathFunction_jr;

    /* Product: '<S135>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product1_it = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.Divide_km;

    /* Product: '<S135>/Product2' */
    TemplateNIPID_B.Product2_ik = TemplateNIPID_B.MultiportSelector *
      TemplateNIPID_B.MultiportSelector2;

    /* Math: '<S135>/^3//2' incorporates:
     *  Constant: '<S135>/3//2'
     */
    if ((TemplateNIPID_B.Add_pj < 0.0) && (TemplateNIPID_P.u_Value_ez > floor
         (TemplateNIPID_P.u_Value_ez))) {
      TemplateNIPID_B.u2_o = -rt_pow_snf(-TemplateNIPID_B.Add_pj,
        TemplateNIPID_P.u_Value_ez);
    } else {
      TemplateNIPID_B.u2_o = rt_pow_snf(TemplateNIPID_B.Add_pj,
        TemplateNIPID_P.u_Value_ez);
    }

    /* Product: '<S135>/Divide1' */
    TemplateNIPID_B.Divide1_j = TemplateNIPID_B.Product2_ik /
      TemplateNIPID_B.u2_o;

    /* Product: '<S135>/Product3' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Product3_o = TemplateNIPID_P.Deltam_Value *
      TemplateNIPID_B.Divide1_j * TemplateNIPID_B.Divide_l;

    /* Product: '<S139>/Product1' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    TemplateNIPID_B.Product1_at = TemplateNIPID_P.my_Value *
      TemplateNIPID_B.Add_df;

    /* Math: '<S143>/Math Function' */
    TemplateNIPID_B.MathFunction_la[0] = TemplateNIPID_B.Add_a[0];

    /* Product: '<S139>/Divide2' */
    TemplateNIPID_B.Divide2[0] = TemplateNIPID_B.MathFunction_la[0] /
      TemplateNIPID_B.Add_df;

    /* Math: '<S142>/Math Function' */
    TemplateNIPID_B.MathFunction_g[0] = TemplateNIPID_B.Add[0];

    /* Math: '<S143>/Math Function' */
    TemplateNIPID_B.MathFunction_la[1] = TemplateNIPID_B.Add_a[1];

    /* Product: '<S139>/Divide2' */
    TemplateNIPID_B.Divide2[1] = TemplateNIPID_B.MathFunction_la[1] /
      TemplateNIPID_B.Add_df;

    /* Math: '<S142>/Math Function' */
    TemplateNIPID_B.MathFunction_g[1] = TemplateNIPID_B.Add[1];

    /* Product: '<S139>/Product2' */
    tmp = TemplateNIPID_B.MathFunction_la[0] * TemplateNIPID_B.Add[0];
    tmp += TemplateNIPID_B.MathFunction_la[1] * TemplateNIPID_B.Add[1];
    TemplateNIPID_B.Product2_la[0] = tmp * TemplateNIPID_B.MathFunction_g[0];
    TemplateNIPID_B.Product2_la[1] = tmp * TemplateNIPID_B.MathFunction_g[1];

    /* Math: '<S139>/Math Function' incorporates:
     *  Constant: '<S139>/Constant'
     */
    if ((TemplateNIPID_B.Add_df < 0.0) && (TemplateNIPID_P.Constant_Value_mj >
         floor(TemplateNIPID_P.Constant_Value_mj))) {
      TemplateNIPID_B.MathFunction_p = -rt_pow_snf(-TemplateNIPID_B.Add_df,
        TemplateNIPID_P.Constant_Value_mj);
    } else {
      TemplateNIPID_B.MathFunction_p = rt_pow_snf(TemplateNIPID_B.Add_df,
        TemplateNIPID_P.Constant_Value_mj);
    }

    /* Product: '<S139>/Divide1' */
    TemplateNIPID_B.Divide1_j0[0] = TemplateNIPID_B.Product2_la[0] /
      TemplateNIPID_B.MathFunction_p;

    /* Sum: '<S139>/Subtract1' */
    TemplateNIPID_B.Subtract1_k[0] = TemplateNIPID_B.Divide2[0] -
      TemplateNIPID_B.Divide1_j0[0];

    /* Product: '<S139>/Divide1' */
    TemplateNIPID_B.Divide1_j0[1] = TemplateNIPID_B.Product2_la[1] /
      TemplateNIPID_B.MathFunction_p;

    /* Sum: '<S139>/Subtract1' */
    TemplateNIPID_B.Subtract1_k[1] = TemplateNIPID_B.Divide2[1] -
      TemplateNIPID_B.Divide1_j0[1];

    /* Product: '<S139>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    tmp = TemplateNIPID_P.my_Value * TemplateNIPID_B.Subtract1_k[0] *
      TemplateNIPID_B.Subtract[0];
    tmp += TemplateNIPID_P.my_Value * TemplateNIPID_B.Subtract1_k[1] *
      TemplateNIPID_B.Subtract[1];
    TemplateNIPID_B.Product_kg = tmp;

    /* Sum: '<S139>/Subtract' */
    TemplateNIPID_B.Subtract_c = TemplateNIPID_B.Product1_at -
      TemplateNIPID_B.Product_kg;

    /* Sum: '<S135>/Sum' */
    TemplateNIPID_B.Sum_m = (TemplateNIPID_B.Product1_it -
      TemplateNIPID_B.Product3_o) - TemplateNIPID_B.Subtract_c;

    /* Product: '<S49>/Product1' */
    TemplateNIPID_B.Product1_m1 = TemplateNIPID_B.Subtract_n *
      TemplateNIPID_B.Sum_m;

    /* Sum: '<S49>/Add' */
    TemplateNIPID_B.VectorConcatenate_a[2] = TemplateNIPID_B.Product_a2 +
      TemplateNIPID_B.Product1_m1;

    /* Sum: '<S59>/Add1' */
    TemplateNIPID_B.Add1_c[0] = TemplateNIPID_B.VectorConcatenate_m[0] +
      TemplateNIPID_B.VectorConcatenate_a[0];

    /* Product: '<S36>/Product1' */
    TemplateNIPID_B.Product1_d[0] = TemplateNIPID_B.Add1_c[0] *
      TemplateNIPID_B.Subtract_ni;

    /* Sum: '<S59>/Add1' */
    TemplateNIPID_B.Add1_c[1] = TemplateNIPID_B.VectorConcatenate_m[1] +
      TemplateNIPID_B.VectorConcatenate_a[1];

    /* Product: '<S36>/Product1' */
    TemplateNIPID_B.Product1_d[1] = TemplateNIPID_B.Add1_c[1] *
      TemplateNIPID_B.Subtract_ni;

    /* Sum: '<S59>/Add1' */
    TemplateNIPID_B.Add1_c[2] = TemplateNIPID_B.VectorConcatenate_m[2] +
      TemplateNIPID_B.VectorConcatenate_a[2];

    /* Product: '<S36>/Product1' */
    TemplateNIPID_B.Product1_d[2] = TemplateNIPID_B.Add1_c[2] *
      TemplateNIPID_B.Subtract_ni;

    /* Trigonometry: '<S132>/Trigonometric Function' */
    TemplateNIPID_B.TrigonometricFunction_o = cos(TemplateNIPID_B.Sum_e);

    /* Trigonometry: '<S132>/Trigonometric Function1' */
    TemplateNIPID_B.TrigonometricFunction1_j = sin(TemplateNIPID_B.Sum_e);

    /* Derivative Block: '<S118>/Derivative' */
    {
      real_T t = TemplateNIPID_M->Timing.t[0];
      real_T timeStampA = TemplateNIPID_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = TemplateNIPID_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        TemplateNIPID_B.Derivative = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &TemplateNIPID_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 2;
          }
        } else if (timeStampA >= t) {
          lastBank += 2;
        }

        deltaT = t - *lastBank++;
        TemplateNIPID_B.Derivative = (TemplateNIPID_P.u_dm_Value - *lastBank++) /
          deltaT;
      }
    }

    /* Product: '<S132>/Product' */
    TemplateNIPID_B.Product_pl[0] = TemplateNIPID_B.TrigonometricFunction_o *
      TemplateNIPID_B.Derivative;
    TemplateNIPID_B.Product_pl[1] = TemplateNIPID_B.TrigonometricFunction1_j *
      TemplateNIPID_B.Derivative;

    /* SignalConversion: '<S44>/ConcatBufferAtVector ConcatenateIn1' */
    TemplateNIPID_B.VectorConcatenate_b[0] = TemplateNIPID_B.Product_pl[0];
    TemplateNIPID_B.VectorConcatenate_b[1] = TemplateNIPID_B.Product_pl[1];

    /* Product: '<S44>/Product1' */
    tmp = TemplateNIPID_B.u_m[0] * TemplateNIPID_B.Product_pl[0];
    tmp += TemplateNIPID_B.u_m[1] * TemplateNIPID_B.Product_pl[1];
    TemplateNIPID_B.VectorConcatenate_b[2] = tmp;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Constant: '<S50>/0_2x1' */
      TemplateNIPID_B.VectorConcatenate_g[0] = TemplateNIPID_P._2x1_Value_c[0];
      TemplateNIPID_B.VectorConcatenate_g[1] = TemplateNIPID_P._2x1_Value_c[1];
    }

    /* Math: '<S136>/epsilon_n^2' */
    tmp = TemplateNIPID_B.MultiportSelector;
    TemplateNIPID_B.epsilon_n2_m = tmp * tmp;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Math: '<S136>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.Delta2_f = tmp * tmp;
    }

    /* Sum: '<S136>/Add' */
    TemplateNIPID_B.Add_pb = TemplateNIPID_B.epsilon_n2_m +
      TemplateNIPID_B.Delta2_f;

    /* Math: '<S136>/sqrt' */
    tmp = TemplateNIPID_B.Add_pb;
    if (tmp < 0.0) {
      TemplateNIPID_B.sqrt_d = -sqrt(-tmp);
    } else {
      TemplateNIPID_B.sqrt_d = sqrt(tmp);
    }

    /* Product: '<S136>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateNIPID_B.Divide_ht = TemplateNIPID_P.Deltam_Value /
      TemplateNIPID_B.sqrt_d;

    /* Product: '<S186>/Divide' */
    TemplateNIPID_B.Divide_a = TemplateNIPID_B.Derivative /
      TemplateNIPID_B.Add_df;

    /* Product: '<S136>/Product' */
    TemplateNIPID_B.Product_bl = TemplateNIPID_B.Divide_ht *
      TemplateNIPID_B.Divide_a;

    /* Product: '<S50>/Product1' */
    TemplateNIPID_B.VectorConcatenate_g[2] = TemplateNIPID_B.Subtract_n *
      TemplateNIPID_B.Product_bl;

    /* Sum: '<S60>/Add' */
    TemplateNIPID_B.Add_h[0] = TemplateNIPID_B.VectorConcatenate_b[0] +
      TemplateNIPID_B.VectorConcatenate_g[0];

    /* Sum: '<S36>/Sum' */
    TemplateNIPID_B.Sum_fd[0] = (TemplateNIPID_B.Product_c3[0] +
      TemplateNIPID_B.Product1_d[0]) + TemplateNIPID_B.Add_h[0];

    /* Sum: '<S60>/Add' */
    TemplateNIPID_B.Add_h[1] = TemplateNIPID_B.VectorConcatenate_b[1] +
      TemplateNIPID_B.VectorConcatenate_g[1];

    /* Sum: '<S36>/Sum' */
    TemplateNIPID_B.Sum_fd[1] = (TemplateNIPID_B.Product_c3[1] +
      TemplateNIPID_B.Product1_d[1]) + TemplateNIPID_B.Add_h[1];

    /* Sum: '<S60>/Add' */
    TemplateNIPID_B.Add_h[2] = TemplateNIPID_B.VectorConcatenate_b[2] +
      TemplateNIPID_B.VectorConcatenate_g[2];

    /* Sum: '<S36>/Sum' */
    TemplateNIPID_B.Sum_fd[2] = (TemplateNIPID_B.Product_c3[2] +
      TemplateNIPID_B.Product1_d[2]) + TemplateNIPID_B.Add_h[2];

    /* Product: '<S51>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] +
          TemplateNIPID_B.MathFunction[3 * tmp_6] * TemplateNIPID_B.x3[i];
        tmp_1[i + 3 * tmp_6] = TemplateNIPID_B.MathFunction[3 * tmp_6 + 1] *
          TemplateNIPID_B.x3[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = TemplateNIPID_B.MathFunction[3 * tmp_6 + 2] *
          TemplateNIPID_B.x3[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.Product_k3[i] = 0.0;
      TemplateNIPID_B.Product_k3[i] = tmp_1[i] * TemplateNIPID_B.Sum_fd[0] +
        TemplateNIPID_B.Product_k3[i];
      TemplateNIPID_B.Product_k3[i] = tmp_1[i + 3] * TemplateNIPID_B.Sum_fd[1] +
        TemplateNIPID_B.Product_k3[i];
      TemplateNIPID_B.Product_k3[i] = tmp_1[i + 6] * TemplateNIPID_B.Sum_fd[2] +
        TemplateNIPID_B.Product_k3[i];
    }

    /* Gain: '<S54>/S12' */
    TemplateNIPID_B.S12 = TemplateNIPID_P.S12_Gain * TemplateNIPID_B.nuSwitch[2];

    /* Reshape: '<S54>/S(r)' incorporates:
     *  Constant: '<S54>/R31'
     *  Constant: '<S54>/S11'
     *  Constant: '<S54>/S13'
     *  Constant: '<S54>/S22'
     *  Constant: '<S54>/S23'
     *  Constant: '<S54>/S32'
     *  Constant: '<S54>/S33'
     */
    TemplateNIPID_B.Sr[0] = TemplateNIPID_P.S11_Value;
    TemplateNIPID_B.Sr[1] = TemplateNIPID_B.nuSwitch[2];
    TemplateNIPID_B.Sr[2] = TemplateNIPID_P.R31_Value_e;
    TemplateNIPID_B.Sr[3] = TemplateNIPID_B.S12;
    TemplateNIPID_B.Sr[4] = TemplateNIPID_P.S22_Value;
    TemplateNIPID_B.Sr[5] = TemplateNIPID_P.S32_Value;
    TemplateNIPID_B.Sr[6] = TemplateNIPID_P.S13_Value;
    TemplateNIPID_B.Sr[7] = TemplateNIPID_P.S23_Value;
    TemplateNIPID_B.Sr[8] = TemplateNIPID_P.S33_Value;

    /* Math: '<S55>/Math Function' */
    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.MathFunction_ii[3 * i] = TemplateNIPID_B.Sr[i];
      TemplateNIPID_B.MathFunction_ii[1 + 3 * i] = TemplateNIPID_B.Sr[i + 3];
      TemplateNIPID_B.MathFunction_ii[2 + 3 * i] = TemplateNIPID_B.Sr[i + 6];
    }

    /* Product: '<S51>/Product1' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] +
          TemplateNIPID_B.MathFunction_ii[3 * tmp_6] * TemplateNIPID_B.x3[i];
        tmp_1[i + 3 * tmp_6] = TemplateNIPID_B.MathFunction_ii[3 * tmp_6 + 1] *
          TemplateNIPID_B.x3[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = TemplateNIPID_B.MathFunction_ii[3 * tmp_6 + 2] *
          TemplateNIPID_B.x3[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_3[i + 3 * tmp_6] = 0.0;
        tmp_3[i + 3 * tmp_6] = tmp_3[3 * tmp_6 + i] +
          TemplateNIPID_B.MathFunction[3 * tmp_6] * tmp_1[i];
        tmp_3[i + 3 * tmp_6] = TemplateNIPID_B.MathFunction[3 * tmp_6 + 1] *
          tmp_1[i + 3] + tmp_3[3 * tmp_6 + i];
        tmp_3[i + 3 * tmp_6] = TemplateNIPID_B.MathFunction[3 * tmp_6 + 2] *
          tmp_1[i + 6] + tmp_3[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.Product1_kl[i] = 0.0;
      TemplateNIPID_B.Product1_kl[i] = tmp_3[i] * TemplateNIPID_B.Add_o[0] +
        TemplateNIPID_B.Product1_kl[i];
      TemplateNIPID_B.Product1_kl[i] = tmp_3[i + 3] * TemplateNIPID_B.Add_o[1] +
        TemplateNIPID_B.Product1_kl[i];
      TemplateNIPID_B.Product1_kl[i] = tmp_3[i + 6] * TemplateNIPID_B.Add_o[2] +
        TemplateNIPID_B.Product1_kl[i];

      /* Gain: '<S51>/Gain' */
      TemplateNIPID_B.Gain_mj[i] = TemplateNIPID_P.Gain_Gain_h2 *
        TemplateNIPID_B.Product1_kl[i];

      /* Sum: '<S51>/Subtract' */
      TemplateNIPID_B.Subtract_dp[i] = TemplateNIPID_B.Product_k3[i] +
        TemplateNIPID_B.Gain_mj[i];

      /* Product: '<S33>/Product1' incorporates:
       *  Constant: '<S1>/tauyscale'
       */
      TemplateNIPID_B.Product1_bi[i] = TemplateNIPID_P.tauyscale_Value *
        TemplateNIPID_B.Subtract_dp[i];

      /* Sum: '<S33>/Sum' */
      TemplateNIPID_B.Sum_b[i] = (TemplateNIPID_B.Sum_g[i] +
        TemplateNIPID_B.Product_d3[i]) + TemplateNIPID_B.Product1_bi[i];
    }

    /* MultiPortSwitch: '<S26>/tau Switch' incorporates:
     *  Constant: '<S1>/Control Mode Selector'
     */
    switch ((int32_T)TemplateNIPID_P.ControlModeSelector_Value) {
     case 0:
      TemplateNIPID_B.tauSwitch[0] = TemplateNIPID_B.Product1[0];
      TemplateNIPID_B.tauSwitch[1] = TemplateNIPID_B.Product1[1];
      TemplateNIPID_B.tauSwitch[2] = TemplateNIPID_B.Product1[2];
      break;

     case 1:
      TemplateNIPID_B.tauSwitch[0] = TemplateNIPID_B.Product1_b[0];
      TemplateNIPID_B.tauSwitch[1] = TemplateNIPID_B.Product1_b[1];
      TemplateNIPID_B.tauSwitch[2] = TemplateNIPID_B.Product1_b[2];
      break;

     default:
      TemplateNIPID_B.tauSwitch[0] = TemplateNIPID_B.Sum_b[0];
      TemplateNIPID_B.tauSwitch[1] = TemplateNIPID_B.Sum_b[1];
      TemplateNIPID_B.tauSwitch[2] = TemplateNIPID_B.Sum_b[2];
      break;
    }

    /* Concatenate: '<S128>/Matrix Concatenate' incorporates:
     *  Constant: '<S162>/Constant'
     */
    TemplateNIPID_B.MatrixConcatenate_d[0] = TemplateNIPID_P.Constant_Value_pe[0];
    TemplateNIPID_B.MatrixConcatenate_d[1] = TemplateNIPID_P.Constant_Value_pe[1];
    TemplateNIPID_B.MatrixConcatenate_d[3] = TemplateNIPID_P.Constant_Value_pe[2];
    TemplateNIPID_B.MatrixConcatenate_d[4] = TemplateNIPID_P.Constant_Value_pe[3];
    TemplateNIPID_B.MatrixConcatenate_d[2] = TemplateNIPID_B.u_m[0];
    TemplateNIPID_B.MatrixConcatenate_d[5] = TemplateNIPID_B.u_m[1];

    /* Math: '<S57>/Math Function' */
    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.MathFunction_hoy[i << 1] =
        TemplateNIPID_B.MatrixConcatenate_d[i];
      TemplateNIPID_B.MathFunction_hoy[1 + (i << 1)] =
        TemplateNIPID_B.MatrixConcatenate_d[i + 3];
    }

    /* Product: '<S35>/Product2' */
    for (i = 0; i < 2; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_4[i + (tmp_6 << 1)] = 0.0;
        tmp_4[i + (tmp_6 << 1)] = tmp_4[(tmp_6 << 1) + i] +
          TemplateNIPID_B.ux3_p[3 * tmp_6] * TemplateNIPID_B.MathFunction_hoy[i];
        tmp_4[i + (tmp_6 << 1)] = TemplateNIPID_B.ux3_p[3 * tmp_6 + 1] *
          TemplateNIPID_B.MathFunction_hoy[i + 2] + tmp_4[(tmp_6 << 1) + i];
        tmp_4[i + (tmp_6 << 1)] = TemplateNIPID_B.ux3_p[3 * tmp_6 + 2] *
          TemplateNIPID_B.MathFunction_hoy[i + 4] + tmp_4[(tmp_6 << 1) + i];
      }
    }

    for (i = 0; i < 2; i++) {
      TemplateNIPID_B.Product2_c[i] = 0.0;
      TemplateNIPID_B.Product2_c[i] = tmp_4[i] *
        TemplateNIPID_B.TmpHiddenBufferAtProductInport3[0] +
        TemplateNIPID_B.Product2_c[i];
      TemplateNIPID_B.Product2_c[i] = tmp_4[i + 2] *
        TemplateNIPID_B.TmpHiddenBufferAtProductInport3[1] +
        TemplateNIPID_B.Product2_c[i];
      TemplateNIPID_B.Product2_c[i] = tmp_4[i + 4] *
        TemplateNIPID_B.TmpHiddenBufferAtProductInport3[2] +
        TemplateNIPID_B.Product2_c[i];
    }

    /* Product: '<S35>/Product3' */
    TemplateNIPID_B.Product3_e[0] = 0.0;
    TemplateNIPID_B.Product3_e[0] = TemplateNIPID_B.ux2[0] *
      TemplateNIPID_B.Product2_c[0] + TemplateNIPID_B.Product3_e[0];
    TemplateNIPID_B.Product3_e[0] = TemplateNIPID_B.ux2[2] *
      TemplateNIPID_B.Product2_c[1] + TemplateNIPID_B.Product3_e[0];

    /* Sum: '<S35>/Subtract' */
    TemplateNIPID_B.Subtract_h[0] = TemplateNIPID_B.Integrator2[0] -
      TemplateNIPID_B.Product3_e[0];

    /* Product: '<S35>/Product4' incorporates:
     *  Constant: '<S9>/lambda_q'
     */
    TemplateNIPID_B.Product4_b[0] = TemplateNIPID_P.lambda_q_Value *
      TemplateNIPID_B.Subtract_h[0];

    /* Gain: '<S35>/Gain' */
    TemplateNIPID_B.Gain_en[0] = TemplateNIPID_P.Gain_Gain_px *
      TemplateNIPID_B.Product4_b[0];

    /* Product: '<S35>/Product3' */
    TemplateNIPID_B.Product3_e[1] = 0.0;
    TemplateNIPID_B.Product3_e[1] = TemplateNIPID_B.ux2[1] *
      TemplateNIPID_B.Product2_c[0] + TemplateNIPID_B.Product3_e[1];
    TemplateNIPID_B.Product3_e[1] = TemplateNIPID_B.ux2[3] *
      TemplateNIPID_B.Product2_c[1] + TemplateNIPID_B.Product3_e[1];

    /* Sum: '<S35>/Subtract' */
    TemplateNIPID_B.Subtract_h[1] = TemplateNIPID_B.Integrator2[1] -
      TemplateNIPID_B.Product3_e[1];

    /* Product: '<S35>/Product4' incorporates:
     *  Constant: '<S9>/lambda_q'
     */
    TemplateNIPID_B.Product4_b[1] = TemplateNIPID_P.lambda_q_Value *
      TemplateNIPID_B.Subtract_h[1];

    /* Gain: '<S35>/Gain' */
    TemplateNIPID_B.Gain_en[1] = TemplateNIPID_P.Gain_Gain_px *
      TemplateNIPID_B.Product4_b[1];

    /* Product: '<S40>/Product' */
    for (i = 0; i < 3; i++) {
      TemplateNIPID_B.Product_ak[i] = 0.0;
      TemplateNIPID_B.Product_ak[i] = TemplateNIPID_B.Rpsi[i] *
        TemplateNIPID_B.Subtract_k[0] + TemplateNIPID_B.Product_ak[i];
      TemplateNIPID_B.Product_ak[i] = TemplateNIPID_B.Rpsi[i + 3] *
        TemplateNIPID_B.Subtract_k[1] + TemplateNIPID_B.Product_ak[i];
      TemplateNIPID_B.Product_ak[i] = TemplateNIPID_B.Rpsi[i + 6] *
        TemplateNIPID_B.Subtract_k[2] + TemplateNIPID_B.Product_ak[i];
    }

    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* S-Function (sdsppinv): '<S98>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&TemplateNIPID_DWork.Pseudoinverse_X[0]), (void *)
             (&TemplateNIPID_B.x5[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&TemplateNIPID_DWork.Pseudoinverse_X[0], 3, 5,
                      &TemplateNIPID_DWork.Pseudoinverse_S[0],
                      &TemplateNIPID_DWork.Inverse_DWORK3[0],
                      &TemplateNIPID_DWork.Pseudoinverse_WORK[0],
                      &TemplateNIPID_DWork.Pseudoinverse_U[0],
                      &TemplateNIPID_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&TemplateNIPID_DWork.Pseudoinverse_S[0],
          &TemplateNIPID_DWork.Pseudoinverse_U[0],
          &TemplateNIPID_DWork.Pseudoinverse_V[0],
          &TemplateNIPID_B.Pseudoinverse[0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Product: '<S98>/Product' */
    for (i = 0; i < 5; i++) {
      TemplateNIPID_B.Product_pk[i] = 0.0;
      TemplateNIPID_B.Product_pk[i] = TemplateNIPID_B.Pseudoinverse[i] *
        TemplateNIPID_B.tauSwitch[0] + TemplateNIPID_B.Product_pk[i];
      TemplateNIPID_B.Product_pk[i] = TemplateNIPID_B.Pseudoinverse[i + 5] *
        TemplateNIPID_B.tauSwitch[1] + TemplateNIPID_B.Product_pk[i];
      TemplateNIPID_B.Product_pk[i] = TemplateNIPID_B.Pseudoinverse[i + 10] *
        TemplateNIPID_B.tauSwitch[2] + TemplateNIPID_B.Product_pk[i];
    }

    /* Lookup Block: '<S100>/f_1 to u_1'
     * About '<S100>/f_1 to u_1 :'
     * Lookup Block: '<S100>/f_1 to u_1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_1tou_1),
                         TemplateNIPID_P.f_1tou_1_YData,
                         TemplateNIPID_B.Product_pk[0],
                         TemplateNIPID_P.f_1tou_1_XData, 38U);

    /* Sum: '<S99>/Sum' incorporates:
     *  Constant: '<S1>/offset u1'
     */
    TemplateNIPID_B.Sum_c = TemplateNIPID_P.offsetu1_Value +
      TemplateNIPID_B.f_1tou_1;

    /* RelationalOperator: '<S105>/Compare' incorporates:
     *  Constant: '<S105>/Constant'
     */
    TemplateNIPID_B.Compare_ku = (TemplateNIPID_B.Product_pk[1] <
      TemplateNIPID_P.Constant_Value_pj);

    /* RelationalOperator: '<S107>/Compare' incorporates:
     *  Constant: '<S107>/Constant'
     */
    TemplateNIPID_B.Compare_e2 = (TemplateNIPID_B.Product_pk[1] >=
      TemplateNIPID_P.Constant_Value_h5);

    /* RelationalOperator: '<S106>/Compare' incorporates:
     *  Constant: '<S106>/Constant'
     */
    TemplateNIPID_B.Compare_kb = (TemplateNIPID_B.Product_pk[1] <
      TemplateNIPID_P.Constant_Value_cy);

    /* Logic: '<S101>/Logical Operator' */
    TemplateNIPID_B.LogicalOperator_g = ((TemplateNIPID_B.Compare_e2 != 0) &&
      (TemplateNIPID_B.Compare_kb != 0));

    /* Sum: '<S101>/Sum1' */
    TemplateNIPID_B.Sum1_m = (uint8_T)(TemplateNIPID_B.LogicalOperator_g +
      TemplateNIPID_B.LogicalOperator_g);

    /* RelationalOperator: '<S108>/Compare' incorporates:
     *  Constant: '<S108>/Constant'
     */
    TemplateNIPID_B.Compare_ik = (TemplateNIPID_B.Product_pk[1] >=
      TemplateNIPID_P.Constant_Value_fy);

    /* Gain: '<S101>/Gain1' */
    TemplateNIPID_B.Gain1_fl = (uint16_T)(TemplateNIPID_P.Gain1_Gain_om *
      TemplateNIPID_B.Compare_ik);

    /* Sum: '<S101>/Sum' */
    TemplateNIPID_B.Sum_bs = (uint16_T)(uint32_T)(((TemplateNIPID_B.Compare_ku <<
      6) + (TemplateNIPID_B.Sum1_m << 6)) + TemplateNIPID_B.Gain1_fl);

    /* Lookup Block: '<S101>/f_2 < 0.00391'
     * About '<S101>/f_2 < 0.00391 :'
     * Lookup Block: '<S101>/f_2 < 0.00391'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_2000391),
                         TemplateNIPID_P.f_2000391_YData,
                         TemplateNIPID_B.Product_pk[1],
                         TemplateNIPID_P.f_2000391_XData, 10U);

    /* Lookup Block: '<S101>/f_2 < 0.06731 && f_2 >= 0.00391'
     * About '<S101>/f_2 < 0.06731 && f_2 >= 0.00391 :'
     * Lookup Block: '<S101>/f_2 < 0.06731 && f_2 >= 0.00391'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_2006731f_2000391),
                         TemplateNIPID_P.f_2006731f_2000391_YData,
                         TemplateNIPID_B.Product_pk[1],
                         TemplateNIPID_P.f_2006731f_2000391_XData, 2U);

    /* Lookup Block: '<S101>/f_2 => 0.06731'
     * About '<S101>/f_2 => 0.06731 :'
     * Lookup Block: '<S101>/f_2 => 0.06731'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_2006731),
                         TemplateNIPID_P.f_2006731_YData,
                         TemplateNIPID_B.Product_pk[1],
                         TemplateNIPID_P.f_2006731_XData, 17U);

    /* MultiPortSwitch: '<S101>/Multiport Switch' */
    switch ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_bs >> 6)) {
     case 1:
      TemplateNIPID_B.MultiportSwitch_iu = TemplateNIPID_B.f_2000391;
      break;

     case 2:
      TemplateNIPID_B.MultiportSwitch_iu = TemplateNIPID_B.f_2006731f_2000391;
      break;

     default:
      TemplateNIPID_B.MultiportSwitch_iu = TemplateNIPID_B.f_2006731;
      break;
    }

    /* Sum: '<S99>/Sum1' incorporates:
     *  Constant: '<S1>/offset u2'
     */
    TemplateNIPID_B.Sum1_d = TemplateNIPID_P.offsetu2_Value +
      TemplateNIPID_B.MultiportSwitch_iu;

    /* Lookup Block: '<S102>/f_3 to u_3'
     * About '<S102>/f_3 to u_3 :'
     * Lookup Block: '<S102>/f_3 to u_3'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_3tou_3),
                         TemplateNIPID_P.f_3tou_3_YData,
                         TemplateNIPID_B.Product_pk[2],
                         TemplateNIPID_P.f_3tou_3_XData, 38U);

    /* Sum: '<S99>/Sum2' incorporates:
     *  Constant: '<S1>/offset u3'
     */
    TemplateNIPID_B.Sum2 = TemplateNIPID_P.offsetu3_Value +
      TemplateNIPID_B.f_3tou_3;

    /* RelationalOperator: '<S109>/Compare' incorporates:
     *  Constant: '<S109>/Constant'
     */
    TemplateNIPID_B.Compare_e5 = (TemplateNIPID_B.Product_pk[3] <
      TemplateNIPID_P.Constant_Value_hw);

    /* RelationalOperator: '<S110>/Compare' incorporates:
     *  Constant: '<S110>/Constant'
     */
    TemplateNIPID_B.Compare_a = (TemplateNIPID_B.Product_pk[3] >=
      TemplateNIPID_P.Constant_Value_l5);

    /* Gain: '<S103>/Gain' */
    TemplateNIPID_B.Gain_bp = (uint16_T)(TemplateNIPID_P.Gain_Gain_a *
      TemplateNIPID_B.Compare_a);

    /* Sum: '<S103>/Sum' */
    TemplateNIPID_B.Sum_lm = (uint16_T)(uint32_T)((TemplateNIPID_B.Compare_e5 <<
      6) + TemplateNIPID_B.Gain_bp);

    /* Lookup Block: '<S103>/f_4 < 0.0451'
     * About '<S103>/f_4 < 0.0451 :'
     * Lookup Block: '<S103>/f_4 < 0.0451'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_400451),
                         TemplateNIPID_P.f_400451_YData,
                         TemplateNIPID_B.Product_pk[3],
                         TemplateNIPID_P.f_400451_XData, 14U);

    /* Lookup Block: '<S103>/f_4 >= 0.0451 '
     * About '<S103>/f_4 >= 0.0451  :'
     * Lookup Block: '<S103>/f_4 >= 0.0451 '
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_400451_n),
                         TemplateNIPID_P.f_400451_YData_n,
                         TemplateNIPID_B.Product_pk[3],
                         TemplateNIPID_P.f_400451_XData_m, 12U);

    /* MultiPortSwitch: '<S103>/Multiport Switch' */
    if ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_lm >> 6) == 1) {
      TemplateNIPID_B.MultiportSwitch_e = TemplateNIPID_B.f_400451;
    } else {
      TemplateNIPID_B.MultiportSwitch_e = TemplateNIPID_B.f_400451_n;
    }

    /* Sum: '<S99>/Sum3' incorporates:
     *  Constant: '<S1>/offset u4'
     */
    TemplateNIPID_B.Sum3 = TemplateNIPID_B.MultiportSwitch_e +
      TemplateNIPID_P.offsetu4_Value;

    /* DeadZone Block: '<S104>/Dead Zone +-0.01'
     */
    if (TemplateNIPID_B.Product_pk[4] >= TemplateNIPID_P.DeadZone001_End_h) {
      TemplateNIPID_B.DeadZone001_k = TemplateNIPID_B.Product_pk[4] -
        TemplateNIPID_P.DeadZone001_End_h;
    } else if (TemplateNIPID_B.Product_pk[4] >
               TemplateNIPID_P.DeadZone001_Start_i) {
      TemplateNIPID_B.DeadZone001_k = 0.0;
    } else {
      TemplateNIPID_B.DeadZone001_k = TemplateNIPID_B.Product_pk[4] -
        TemplateNIPID_P.DeadZone001_Start_i;
    }

    /* RelationalOperator: '<S111>/Compare' incorporates:
     *  Constant: '<S111>/Constant'
     */
    TemplateNIPID_B.Compare_km = (TemplateNIPID_B.DeadZone001_k <
      TemplateNIPID_P.Constant_Value_kt);

    /* RelationalOperator: '<S113>/Compare' */
    TemplateNIPID_B.Compare_l4 = (TemplateNIPID_B.DeadZone001_k == 0.0);

    /* Gain: '<S104>/Gain' */
    TemplateNIPID_B.Gain_ep = (uint16_T)(TemplateNIPID_P.Gain_Gain_n *
      TemplateNIPID_B.Compare_l4);

    /* RelationalOperator: '<S112>/Compare' incorporates:
     *  Constant: '<S112>/Constant'
     */
    TemplateNIPID_B.Compare_og = (TemplateNIPID_B.DeadZone001_k >
      TemplateNIPID_P.Constant_Value_mp);

    /* Gain: '<S104>/Gain1' */
    TemplateNIPID_B.Gain1_g = (uint16_T)(TemplateNIPID_P.Gain1_Gain_a *
      TemplateNIPID_B.Compare_og);

    /* Sum: '<S104>/Sum' */
    TemplateNIPID_B.Sum_ms = (uint16_T)(uint32_T)(((TemplateNIPID_B.Compare_km <<
      6) + TemplateNIPID_B.Gain_ep) + TemplateNIPID_B.Gain1_g);

    /* Lookup Block: '<S104>/f_5 < 0'
     * About '<S104>/f_5 < 0 :'
     * Lookup Block: '<S104>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_50), TemplateNIPID_P.f_50_YData,
                         TemplateNIPID_B.Product_pk[4],
                         TemplateNIPID_P.f_50_XData, 9U);

    /* Lookup Block: '<S104>/f_5 > 0'
     * About '<S104>/f_5 > 0 :'
     * Lookup Block: '<S104>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.f_50_f),
                         TemplateNIPID_P.f_50_YData_l,
                         TemplateNIPID_B.Product_pk[4],
                         TemplateNIPID_P.f_50_XData_i, 9U);

    /* MultiPortSwitch: '<S104>/Multiport Switch' incorporates:
     *  Constant: '<S104>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_ms >> 6)) {
     case 1:
      TemplateNIPID_B.MultiportSwitch_o = TemplateNIPID_B.f_50;
      break;

     case 2:
      TemplateNIPID_B.MultiportSwitch_o = TemplateNIPID_P.f_50_Value;
      break;

     default:
      TemplateNIPID_B.MultiportSwitch_o = TemplateNIPID_B.f_50_f;
      break;
    }

    /* Saturate: '<S30>/Saturation' incorporates:
     *  Constant: '<S97>/BT_power_limit'
     *  Constant: '<S97>/VSP_speeds'
     */
    tmp_0[0] = TemplateNIPID_B.Sum_c;
    tmp_0[1] = TemplateNIPID_B.Sum1_d;
    tmp_0[2] = TemplateNIPID_B.Sum2;
    tmp_0[3] = TemplateNIPID_B.Sum3;
    tmp_0[4] = TemplateNIPID_B.MultiportSwitch_o;
    tmp_0[5] = TemplateNIPID_P.BT_power_limit_Value;
    tmp_0[6] = TemplateNIPID_P.VSP_speeds_Value;
    for (i = 0; i < 7; i++) {
      TemplateNIPID_B.Saturation_g[i] = rt_SATURATE(tmp_0[i],
        TemplateNIPID_P.Saturation_LowerSat_i,
        TemplateNIPID_P.Saturation_UpperSat_p);
    }

    /* Gain: '<S188>/QTM In2 Error' */
    TemplateNIPID_B.QTMIn2Error = TemplateNIPID_P.QTMIn2Error_Gain *
      TemplateNIPID_B.QTMIn[1];

    /* Gain: '<S188>/QTM In9 Residual' */
    TemplateNIPID_B.QTMIn9Residual = TemplateNIPID_P.QTMIn9Residual_Gain *
      TemplateNIPID_B.QTMIn[8];

    /* MultiPortSwitch: '<S215>/tau Switch1' incorporates:
     *  Constant: '<S1>/Control Mode Selector'
     *  Constant: '<S6>/PS3_BT_Power  [-]'
     *  Constant: '<S6>/PS3_VSP_Speed  [-]'
     *  Constant: '<S8>/ctrl1Kdpsi'
     *  Constant: '<S8>/ctrl1Kdx'
     *  Constant: '<S8>/ctrl1Kdy'
     *  Constant: '<S8>/ctrl1Kix'
     *  Constant: '<S8>/ctrl1Kiy'
     *  Constant: '<S8>/ctrl1Kpx'
     *  Constant: '<S8>/ctrl1Kpy'
     */
    switch ((int32_T)TemplateNIPID_P.ControlModeSelector_Value) {
     case 0:
      TemplateNIPID_B.tauSwitch1[0] = TemplateNIPID_B.u_1;
      TemplateNIPID_B.tauSwitch1[1] = TemplateNIPID_B.u_2;
      TemplateNIPID_B.tauSwitch1[2] = TemplateNIPID_B.u_3;
      TemplateNIPID_B.tauSwitch1[3] = TemplateNIPID_B.u_4;
      TemplateNIPID_B.tauSwitch1[4] = TemplateNIPID_B.u_5;
      TemplateNIPID_B.tauSwitch1[5] = TemplateNIPID_P.PS3_BT_Power_Value;
      TemplateNIPID_B.tauSwitch1[6] = TemplateNIPID_P.PS3_VSP_Speed_Value;
      break;

     case 1:
      TemplateNIPID_B.tauSwitch1[0] = TemplateNIPID_P.ctrl1Kpx_Value;
      TemplateNIPID_B.tauSwitch1[1] = TemplateNIPID_P.ctrl1Kpy_Value;
      TemplateNIPID_B.tauSwitch1[2] = TemplateNIPID_P.ctrl1Kix_Value;
      TemplateNIPID_B.tauSwitch1[3] = TemplateNIPID_P.ctrl1Kiy_Value;
      TemplateNIPID_B.tauSwitch1[4] = TemplateNIPID_P.ctrl1Kdx_Value;
      TemplateNIPID_B.tauSwitch1[5] = TemplateNIPID_P.ctrl1Kdy_Value;
      TemplateNIPID_B.tauSwitch1[6] = TemplateNIPID_P.ctrl1Kdpsi_Value;
      break;

     default:
      for (i = 0; i < 7; i++) {
        TemplateNIPID_B.tauSwitch1[i] = TemplateNIPID_B.Saturation_g[i];
      }
      break;
    }

    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* SignalConversion: '<S19>/TmpHiddenBufferAtTo FileInport1' incorporates:
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
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[0] =
        TemplateNIPID_P.ControlModeSelector_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[1] =
        TemplateNIPID_P.ControlInputSelector_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[2] =
        TemplateNIPID_P.PathSelector_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[3] =
        TemplateNIPID_B.QTMIn2Error;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[4] =
        TemplateNIPID_B.QTMIn9Residual;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[5] =
        TemplateNIPID_B.etaSwitch[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[6] =
        TemplateNIPID_B.etaSwitch[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[7] =
        TemplateNIPID_B.etaSwitch[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[8] =
        TemplateNIPID_B.nuSwitch[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[9] =
        TemplateNIPID_B.nuSwitch[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[10] =
        TemplateNIPID_B.nuSwitch[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[11] =
        TemplateNIPID_B.VectorConcatenate[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[12] =
        TemplateNIPID_B.VectorConcatenate[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[13] =
        TemplateNIPID_B.VectorConcatenate[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[14] =
        TemplateNIPID_B.Integrator2[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[15] =
        TemplateNIPID_B.Integrator2[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[16] =
        TemplateNIPID_B.Switch2;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[17] =
        TemplateNIPID_B.Switch2_c;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[18] = TemplateNIPID_B.Sum_k;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[19] =
        TemplateNIPID_P.u_dm_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[20] =
        TemplateNIPID_B.Divide_l;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[21] =
        TemplateNIPID_B.Integrator1;
      for (i = 0; i < 7; i++) {
        TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[i + 22] =
          TemplateNIPID_B.tauSwitch1[i];
      }

      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[29] =
        TemplateNIPID_B.tauSwitch[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[30] =
        TemplateNIPID_B.tauSwitch[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[31] =
        TemplateNIPID_B.tauSwitch[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[32] =
        TemplateNIPID_B.Gain_p[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[33] =
        TemplateNIPID_B.Gain_p[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[34] =
        TemplateNIPID_B.Gain_p[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[35] =
        TemplateNIPID_B.Gain1_a[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[36] =
        TemplateNIPID_B.Gain1_a[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[37] =
        TemplateNIPID_B.Gain1_a[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[38] =
        TemplateNIPID_B.Gain2[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[39] =
        TemplateNIPID_B.Gain2[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[40] =
        TemplateNIPID_B.Gain2[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[41] =
        TemplateNIPID_B.Product1_h4[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[42] =
        TemplateNIPID_B.Product1_h4[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[43] =
        TemplateNIPID_B.Product1_h4[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[44] =
        TemplateNIPID_B.Product_k3[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[45] =
        TemplateNIPID_B.Product_k3[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[46] =
        TemplateNIPID_B.Product_k3[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[47] =
        TemplateNIPID_B.Gain_mj[0];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[48] =
        TemplateNIPID_B.Gain_mj[1];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[49] =
        TemplateNIPID_B.Gain_mj[2];
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[50] =
        TemplateNIPID_P.kappa_1_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[51] =
        TemplateNIPID_P.ctrl2Kpx_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[52] =
        TemplateNIPID_P.ctrl2Kpy_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[53] =
        TemplateNIPID_P.ctrl2Kppsi_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[54] =
        TemplateNIPID_P.ctrl2Kix_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[55] =
        TemplateNIPID_P.ctrl2Kiy_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[56] =
        TemplateNIPID_P.ctrl2Kipsi_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[57] =
        TemplateNIPID_P.ctrl2Kdx_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[58] =
        TemplateNIPID_P.ctrl2Kdy_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[59] =
        TemplateNIPID_P.ctrl2Kdpsi_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[60] =
        TemplateNIPID_P.Gamma_q_Surge_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[61] =
        TemplateNIPID_P.Gamma_q_Sway_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[62] =
        TemplateNIPID_P.lambda_q_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[63] =
        TemplateNIPID_P.Deltam_Value;
      TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[64] =
        TemplateNIPID_P.my_Value;

      /* ToFile Block: '<S19>/To File'
       */
      if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
        if (!(++TemplateNIPID_DWork.ToFile_IWORK.Decimation % 1) &&
            (TemplateNIPID_DWork.ToFile_IWORK.Count*66)+1 < 100000000 ) {
          real_T u[66];
          FILE *fp = (FILE *) TemplateNIPID_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            TemplateNIPID_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = TemplateNIPID_M->Timing.t[1];
            u[1] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[22];
            u[24] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[23];
            u[25] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[24];
            u[26] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[25];
            u[27] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[26];
            u[28] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[27];
            u[29] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[28];
            u[30] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[29];
            u[31] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[30];
            u[32] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[31];
            u[33] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[32];
            u[34] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[33];
            u[35] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[34];
            u[36] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[35];
            u[37] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[36];
            u[38] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[37];
            u[39] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[38];
            u[40] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[39];
            u[41] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[40];
            u[42] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[41];
            u[43] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[42];
            u[44] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[43];
            u[45] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[44];
            u[46] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[45];
            u[47] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[46];
            u[48] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[47];
            u[49] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[48];
            u[50] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[49];
            u[51] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[50];
            u[52] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[51];
            u[53] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[52];
            u[54] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[53];
            u[55] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[54];
            u[56] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[55];
            u[57] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[56];
            u[58] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[57];
            u[59] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[58];
            u[60] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[59];
            u[61] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[60];
            u[62] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[61];
            u[63] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[62];
            u[64] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[63];
            u[65] = TemplateNIPID_B.TmpHiddenBufferAtToFileInport1[64];
            if (fwrite(u, sizeof(real_T), 66, fp) != 66) {
              rtmSetErrorStatus(TemplateNIPID_M,
                                "Error writing to MAT-file NLPID_data.mat");
              return;
            }

            if (((++TemplateNIPID_DWork.ToFile_IWORK.Count)*66)+1 >= 100000000)
            {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file NLPID_data.mat.\n");
            }
          }
        }
      }

      /* Constant: '<S128>/0_2x1' */
      TemplateNIPID_B.VectorConcatenate1[0] = TemplateNIPID_P._2x1_Value_d[0];
      TemplateNIPID_B.VectorConcatenate1[1] = TemplateNIPID_P._2x1_Value_d[1];
    }

    /* SignalConversion: '<S128>/ConcatBufferAtVector Concatenate1In2' */
    TemplateNIPID_B.VectorConcatenate1[2] = TemplateNIPID_B.Subtract_n;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
    }

    /* Gain: '<S188>/QTM In5 z-coord [mm]' */
    TemplateNIPID_B.QTMIn5zcoordmm = TemplateNIPID_P.QTMIn5zcoordmm_Gain *
      TemplateNIPID_B.QTMIn[4];

    /* Gain: '<S188>/mm2m z' */
    TemplateNIPID_B.mm2mz = TemplateNIPID_P.mm2mz_Gain *
      TemplateNIPID_B.QTMIn5zcoordmm;

    /* Gain: '<S188>/QTM In8 roll [deg]' */
    TemplateNIPID_B.QTMIn8rolldeg = TemplateNIPID_P.QTMIn8rolldeg_Gain *
      TemplateNIPID_B.QTMIn[7];

    /* Gain: '<S188>/d2r roll' */
    TemplateNIPID_B.d2rroll = TemplateNIPID_P.d2rroll_Gain *
      TemplateNIPID_B.QTMIn8rolldeg;

    /* Gain: '<S188>/QTM In7 pitch [deg]' */
    TemplateNIPID_B.QTMIn7pitchdeg = TemplateNIPID_P.QTMIn7pitchdeg_Gain *
      TemplateNIPID_B.QTMIn[6];

    /* Gain: '<S188>/d2r pitch' */
    TemplateNIPID_B.d2rpitch = TemplateNIPID_P.d2rpitch_Gain *
      TemplateNIPID_B.QTMIn7pitchdeg;

    /* Derivative Block: '<S188>/Derivative' */
    {
      real_T t = TemplateNIPID_M->Timing.t[0];
      real_T timeStampA = TemplateNIPID_DWork.Derivative_RWORK_e.TimeStampA;
      real_T timeStampB = TemplateNIPID_DWork.Derivative_RWORK_e.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = TemplateNIPID_B.Derivative_e;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &TemplateNIPID_DWork.Derivative_RWORK_e.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        TemplateNIPID_B.Derivative_e[0] = (TemplateNIPID_B.mm2mx - *lastBank++) /
          deltaT;
        TemplateNIPID_B.Derivative_e[1] = (TemplateNIPID_B.mm2my - *lastBank++) /
          deltaT;
        TemplateNIPID_B.Derivative_e[2] = (TemplateNIPID_B.mm2mz - *lastBank++) /
          deltaT;
        TemplateNIPID_B.Derivative_e[3] = (TemplateNIPID_B.d2rroll - *lastBank++)
          / deltaT;
        TemplateNIPID_B.Derivative_e[4] = (TemplateNIPID_B.d2rpitch - *lastBank
          ++) / deltaT;
        TemplateNIPID_B.Derivative_e[5] = (TemplateNIPID_B.d2ryaw - *lastBank++)
          / deltaT;
      }
    }

    /* Trigonometry: '<S190>/sin(theta)' */
    TemplateNIPID_B.sintheta[0] = sin(TemplateNIPID_B.d2rroll);
    TemplateNIPID_B.sintheta[1] = sin(TemplateNIPID_B.d2rpitch);
    TemplateNIPID_B.sintheta[2] = sin(TemplateNIPID_B.d2ryaw);

    /* Trigonometry: '<S190>/cos(theta)' */
    TemplateNIPID_B.costheta[0] = cos(TemplateNIPID_B.d2rroll);
    TemplateNIPID_B.costheta[1] = cos(TemplateNIPID_B.d2rpitch);
    TemplateNIPID_B.costheta[2] = cos(TemplateNIPID_B.d2ryaw);

    /* Fcn: '<S190>/R11' */
    TemplateNIPID_B.R11_j = TemplateNIPID_B.costheta[1] *
      TemplateNIPID_B.costheta[2];

    /* Fcn: '<S190>/R12' */
    TemplateNIPID_B.R12_m = TemplateNIPID_B.costheta[1] *
      TemplateNIPID_B.sintheta[2];

    /* Fcn: '<S190>/R13' */
    TemplateNIPID_B.R13 = -TemplateNIPID_B.sintheta[1];

    /* Fcn: '<S190>/R21 ' */
    TemplateNIPID_B.R21_p = TemplateNIPID_B.sintheta[0] *
      TemplateNIPID_B.sintheta[1] * TemplateNIPID_B.costheta[2] +
      (-TemplateNIPID_B.costheta[0]) * TemplateNIPID_B.sintheta[2];

    /* Fcn: '<S190>/R22' */
    TemplateNIPID_B.R22_c = TemplateNIPID_B.sintheta[0] *
      TemplateNIPID_B.sintheta[1] * TemplateNIPID_B.sintheta[2] +
      TemplateNIPID_B.costheta[0] * TemplateNIPID_B.costheta[2];

    /* Fcn: '<S190>/R23' */
    TemplateNIPID_B.R23 = TemplateNIPID_B.sintheta[0] *
      TemplateNIPID_B.costheta[1];

    /* Fcn: '<S190>/R31 ' */
    TemplateNIPID_B.R31 = TemplateNIPID_B.costheta[0] *
      TemplateNIPID_B.sintheta[1] * TemplateNIPID_B.costheta[2] +
      TemplateNIPID_B.sintheta[0] * TemplateNIPID_B.sintheta[2];

    /* Fcn: '<S190>/R32' */
    TemplateNIPID_B.R32 = TemplateNIPID_B.costheta[0] *
      TemplateNIPID_B.sintheta[1] * TemplateNIPID_B.sintheta[2] +
      (-TemplateNIPID_B.sintheta[0]) * TemplateNIPID_B.costheta[2];

    /* Fcn: '<S190>/R33' */
    TemplateNIPID_B.R33 = TemplateNIPID_B.costheta[0] *
      TemplateNIPID_B.costheta[1];

    /* Reshape: '<S190>/Reshape 9x1->3x3' */
    TemplateNIPID_B.Reshape9x13x3[0] = TemplateNIPID_B.R11_j;
    TemplateNIPID_B.Reshape9x13x3[1] = TemplateNIPID_B.R21_p;
    TemplateNIPID_B.Reshape9x13x3[2] = TemplateNIPID_B.R31;
    TemplateNIPID_B.Reshape9x13x3[3] = TemplateNIPID_B.R12_m;
    TemplateNIPID_B.Reshape9x13x3[4] = TemplateNIPID_B.R22_c;
    TemplateNIPID_B.Reshape9x13x3[5] = TemplateNIPID_B.R32;
    TemplateNIPID_B.Reshape9x13x3[6] = TemplateNIPID_B.R13;
    TemplateNIPID_B.Reshape9x13x3[7] = TemplateNIPID_B.R23;
    TemplateNIPID_B.Reshape9x13x3[8] = TemplateNIPID_B.R33;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Product Block: '<S188>/Inverse' */
      {
        static const int_T dims[3] = { 3, 3, 3 };

        rt_MatDivRR_Dbl(TemplateNIPID_B.Inverse, TemplateNIPID_B.x3,
                        &TemplateNIPID_DWork.Inverse_DWORK4[0], (real_T*)
                        &TemplateNIPID_DWork.Pseudoinverse_X[0],
                        &TemplateNIPID_DWork.Inverse_DWORK2[0], (real_T*)
                        &TemplateNIPID_DWork.Inverse_DWORK3[0],
                        &dims[0]);
      }
    }

    /* Concatenate: '<S188>/Matrix Concatenate' incorporates:
     *  Constant: '<S188>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_5[6 * i] = TemplateNIPID_B.Reshape9x13x3[3 * i];
      tmp_5[1 + 6 * i] = TemplateNIPID_B.Reshape9x13x3[3 * i + 1];
      tmp_5[2 + 6 * i] = TemplateNIPID_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_5[3 + 6 * i] = TemplateNIPID_P.Constant1_Value[3 * i];
      tmp_5[4 + 6 * i] = TemplateNIPID_P.Constant1_Value[3 * i + 1];
      tmp_5[5 + 6 * i] = TemplateNIPID_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&TemplateNIPID_B.MatrixConcatenate2[0]), (void *)&tmp_5[0],
           18U * sizeof(real_T));

    /* Concatenate: '<S188>/Matrix Concatenate1' incorporates:
     *  Constant: '<S188>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_5[6 * i] = TemplateNIPID_P.Constant1_Value[3 * i];
      tmp_5[1 + 6 * i] = TemplateNIPID_P.Constant1_Value[3 * i + 1];
      tmp_5[2 + 6 * i] = TemplateNIPID_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_5[3 + 6 * i] = TemplateNIPID_B.Reshape9x13x3[3 * i];
      tmp_5[4 + 6 * i] = TemplateNIPID_B.Reshape9x13x3[3 * i + 1];
      tmp_5[5 + 6 * i] = TemplateNIPID_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&TemplateNIPID_B.MatrixConcatenate2[18]), (void *)&tmp_5[0],
           18U * sizeof(real_T));

    /* Product: '<S188>/Product' */
    for (i = 0; i < 6; i++) {
      TemplateNIPID_B.Product_l3[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 6; tmp_6++) {
        TemplateNIPID_B.Product_l3[i] = TemplateNIPID_B.MatrixConcatenate2[6 *
          tmp_6 + i] * TemplateNIPID_B.Derivative_e[tmp_6] +
          TemplateNIPID_B.Product_l3[i];
      }
    }

    /* Gain: '<S188>/QTM In1 FN' */
    TemplateNIPID_B.QTMIn1FN = TemplateNIPID_P.QTMIn1FN_Gain *
      TemplateNIPID_B.QTMIn[0];

    /* Integrator Block: '<S191>/Integrator'
     */
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateNIPID_PrevZCSigState.Integrator_Reset_ZCE_g,
                         TemplateNIPID_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateNIPID_P.ctrl2ResetIntegrator_Value != 0.0 ||
          TemplateNIPID_DWork.Integrator_IWORK_l.IcNeedsLoading) {
        TemplateNIPID_X.Integrator_CSTATE_l[0] = TemplateNIPID_B.mm2mx;
        TemplateNIPID_X.Integrator_CSTATE_l[1] = TemplateNIPID_B.mm2my;
        TemplateNIPID_X.Integrator_CSTATE_l[2] = TemplateNIPID_B.d2ryaw;
      }

      TemplateNIPID_DWork.Integrator_IWORK_l.IcNeedsLoading = 0;
    }

    TemplateNIPID_B.eta[0] = TemplateNIPID_X.Integrator_CSTATE_l[0];
    TemplateNIPID_B.eta[1] = TemplateNIPID_X.Integrator_CSTATE_l[1];
    TemplateNIPID_B.eta[2] = TemplateNIPID_X.Integrator_CSTATE_l[2];

    /* Integrator: '<S191>/Integrator3' */
    TemplateNIPID_B.bias[0] = TemplateNIPID_X.Integrator3_CSTATE[0];
    TemplateNIPID_B.bias[1] = TemplateNIPID_X.Integrator3_CSTATE[1];
    TemplateNIPID_B.bias[2] = TemplateNIPID_X.Integrator3_CSTATE[2];

    /* Saturate: '<S196>/Saturation' */
    tmp = TemplateNIPID_B.eta[2];
    TemplateNIPID_B.Saturation_b = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat_gr,
      TemplateNIPID_P.Saturation_UpperSat_dx);

    /* Signum: '<S196>/Sign' */
    TemplateNIPID_B.Sign_ds = rt_SIGNd_snf(TemplateNIPID_B.Saturation_b);

    /* Gain: '<S196>/Gain' */
    TemplateNIPID_B.Gain_h = TemplateNIPID_P.Gain_Gain_p1 *
      TemplateNIPID_B.Sign_ds;

    /* Sum: '<S196>/Sum1' */
    TemplateNIPID_B.Sum1_js = TemplateNIPID_B.Saturation_b +
      TemplateNIPID_B.Gain_h;

    /* Math: '<S196>/Math Function' incorporates:
     *  Constant: '<S196>/Constant'
     */
    TemplateNIPID_B.MathFunction_gw = rt_rem_snf(TemplateNIPID_B.Sum1_js,
      TemplateNIPID_P.Constant_Value_ol);

    /* Sum: '<S196>/Sum' */
    TemplateNIPID_B.Sum_eo = TemplateNIPID_B.MathFunction_gw -
      TemplateNIPID_B.Gain_h;

    /* Sum: '<S191>/Sum2' */
    TemplateNIPID_B.Sum2_l[0] = TemplateNIPID_B.mm2mx - TemplateNIPID_B.eta[0];
    TemplateNIPID_B.Sum2_l[1] = TemplateNIPID_B.mm2my - TemplateNIPID_B.eta[1];
    TemplateNIPID_B.Sum2_l[2] = TemplateNIPID_B.d2ryaw - TemplateNIPID_B.Sum_eo;

    /* Saturate: '<S197>/Saturation' */
    tmp = TemplateNIPID_B.Sum2_l[2];
    TemplateNIPID_B.Saturation_i1 = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat_l,
      TemplateNIPID_P.Saturation_UpperSat_eu);

    /* Signum: '<S197>/Sign' */
    TemplateNIPID_B.Sign_p = rt_SIGNd_snf(TemplateNIPID_B.Saturation_i1);

    /* Gain: '<S197>/Gain' */
    TemplateNIPID_B.Gain_p2 = TemplateNIPID_P.Gain_Gain_c *
      TemplateNIPID_B.Sign_p;

    /* Sum: '<S197>/Sum1' */
    TemplateNIPID_B.Sum1_c = TemplateNIPID_B.Saturation_i1 +
      TemplateNIPID_B.Gain_p2;

    /* Math: '<S197>/Math Function' incorporates:
     *  Constant: '<S197>/Constant'
     */
    TemplateNIPID_B.MathFunction_if = rt_rem_snf(TemplateNIPID_B.Sum1_c,
      TemplateNIPID_P.Constant_Value_g);

    /* Sum: '<S197>/Sum' */
    TemplateNIPID_B.Sum_c0 = TemplateNIPID_B.MathFunction_if -
      TemplateNIPID_B.Gain_p2;

    /* SignalConversion: '<S191>/TmpHiddenBufferAtK2Inport1' */
    TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[0] = TemplateNIPID_B.Sum2_l[0];
    TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[1] = TemplateNIPID_B.Sum2_l[1];
    TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[2] = TemplateNIPID_B.Sum_c0;
    for (i = 0; i < 3; i++) {
      /* Gain: '<S191>/K2' */
      TemplateNIPID_B.K2[i] = 0.0;
      TemplateNIPID_B.K2[i] = TemplateNIPID_P.K2_Gain[i] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[0] + TemplateNIPID_B.K2[i];
      TemplateNIPID_B.K2[i] = TemplateNIPID_P.K2_Gain[i + 3] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[1] + TemplateNIPID_B.K2[i];
      TemplateNIPID_B.K2[i] = TemplateNIPID_P.K2_Gain[i + 6] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[2] + TemplateNIPID_B.K2[i];

      /* Gain: '<S191>/K3' */
      TemplateNIPID_B.K3[i] = 0.0;
      TemplateNIPID_B.K3[i] = TemplateNIPID_P.K3_Gain[i] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[0] + TemplateNIPID_B.K3[i];
      TemplateNIPID_B.K3[i] = TemplateNIPID_P.K3_Gain[i + 3] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[1] + TemplateNIPID_B.K3[i];
      TemplateNIPID_B.K3[i] = TemplateNIPID_P.K3_Gain[i + 6] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[2] + TemplateNIPID_B.K3[i];

      /* Gain: '<S191>/K4' */
      TemplateNIPID_B.K4[i] = 0.0;
      TemplateNIPID_B.K4[i] = TemplateNIPID_P.K4_Gain[i] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[0] + TemplateNIPID_B.K4[i];
      TemplateNIPID_B.K4[i] = TemplateNIPID_P.K4_Gain[i + 3] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[1] + TemplateNIPID_B.K4[i];
      TemplateNIPID_B.K4[i] = TemplateNIPID_P.K4_Gain[i + 6] *
        TemplateNIPID_B.TmpHiddenBufferAtK2Inport1[2] + TemplateNIPID_B.K4[i];
    }

    /* Fcn: '<S194>/Row1' */
    TemplateNIPID_B.Row1 = cos(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.K4[0] +
      sin(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.K4[1];

    /* Fcn: '<S194>/Row2' */
    TemplateNIPID_B.Row2 = (-sin(TemplateNIPID_B.d2ryaw)) * TemplateNIPID_B.K4[0]
      + cos(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.K4[1];

    /* Fcn: '<S194>/Row3' */
    TemplateNIPID_B.Row3 = TemplateNIPID_B.K4[2];

    /* Fcn: '<S195>/Row1' */
    TemplateNIPID_B.Row1_j = cos(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.bias
      [0] + sin(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.bias[1];

    /* Fcn: '<S195>/Row2' */
    TemplateNIPID_B.Row2_o = (-sin(TemplateNIPID_B.d2ryaw)) *
      TemplateNIPID_B.bias[0] + cos(TemplateNIPID_B.d2ryaw) *
      TemplateNIPID_B.bias[1];

    /* Fcn: '<S195>/Row3' */
    TemplateNIPID_B.Row3_a = TemplateNIPID_B.bias[2];

    /* Lookup Block: '<S199>/u_1 to f_1'
     * About '<S199>/u_1 to f_1 :'
     * Lookup Block: '<S199>/u_1 to f_1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_1tof_1_p1),
                         TemplateNIPID_P.u_1tof_1_YData_l,
                         TemplateNIPID_B.Saturation_g[0],
                         TemplateNIPID_P.u_1tof_1_XData_b, 38U);

    /* RelationalOperator: '<S204>/Compare' incorporates:
     *  Constant: '<S204>/Constant'
     */
    TemplateNIPID_B.Compare_by = (TemplateNIPID_B.Saturation_g[1] <
      TemplateNIPID_P.Constant_Value_ex);

    /* RelationalOperator: '<S206>/Compare' incorporates:
     *  Constant: '<S206>/Constant'
     */
    TemplateNIPID_B.Compare_l2 = (TemplateNIPID_B.Saturation_g[1] >=
      TemplateNIPID_P.Constant_Value_fk);

    /* RelationalOperator: '<S205>/Compare' incorporates:
     *  Constant: '<S205>/Constant'
     */
    TemplateNIPID_B.Compare_hq = (TemplateNIPID_B.Saturation_g[1] <
      TemplateNIPID_P.Constant_Value_lt);

    /* Logic: '<S200>/Logical Operator' */
    TemplateNIPID_B.LogicalOperator_j = ((TemplateNIPID_B.Compare_l2 != 0) &&
      (TemplateNIPID_B.Compare_hq != 0));

    /* Sum: '<S200>/Sum1' */
    TemplateNIPID_B.Sum1_a = (uint8_T)(TemplateNIPID_B.LogicalOperator_j +
      TemplateNIPID_B.LogicalOperator_j);

    /* RelationalOperator: '<S207>/Compare' incorporates:
     *  Constant: '<S207>/Constant'
     */
    TemplateNIPID_B.Compare_n = (TemplateNIPID_B.Saturation_g[1] >=
      TemplateNIPID_P.Constant_Value_h2);

    /* Gain: '<S200>/Gain1' */
    TemplateNIPID_B.Gain1_n = (uint16_T)(TemplateNIPID_P.Gain1_Gain_k *
      TemplateNIPID_B.Compare_n);

    /* Sum: '<S200>/Sum' */
    TemplateNIPID_B.Sum_lo = (uint16_T)(uint32_T)(((TemplateNIPID_B.Compare_by <<
      6) + (TemplateNIPID_B.Sum1_a << 6)) + TemplateNIPID_B.Gain1_n);

    /* Lookup Block: '<S200>/u_2 < -0.5'
     * About '<S200>/u_2 < -0.5 :'
     * Lookup Block: '<S200>/u_2 < -0.5'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_205_g),
                         TemplateNIPID_P.u_205_YData_l,
                         TemplateNIPID_B.Saturation_g[1],
                         TemplateNIPID_P.u_205_XData_h, 10U);

    /* Lookup Block: '<S200>/u_2 < -0.1 && u_2 >= -0.2'
     * About '<S200>/u_2 < -0.1 && u_2 >= -0.2 :'
     * Lookup Block: '<S200>/u_2 < -0.1 && u_2 >= -0.2'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_201u_202_k),
                         TemplateNIPID_P.u_201u_202_YData_i,
                         TemplateNIPID_B.Saturation_g[1],
                         TemplateNIPID_P.u_201u_202_XData_m, 2U);

    /* Lookup Block: '<S200>/u_2 => 0'
     * About '<S200>/u_2 => 0 :'
     * Lookup Block: '<S200>/u_2 => 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_20_n),
                         TemplateNIPID_P.u_20_YData_e,
                         TemplateNIPID_B.Saturation_g[1],
                         TemplateNIPID_P.u_20_XData_b, 17U);

    /* MultiPortSwitch: '<S200>/Multiport Switch' */
    switch ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_lo >> 6)) {
     case 1:
      TemplateNIPID_B.MultiportSwitch_d = TemplateNIPID_B.u_205_g;
      break;

     case 2:
      TemplateNIPID_B.MultiportSwitch_d = TemplateNIPID_B.u_201u_202_k;
      break;

     default:
      TemplateNIPID_B.MultiportSwitch_d = TemplateNIPID_B.u_20_n;
      break;
    }

    /* Lookup Block: '<S201>/u_3 to f_3'
     * About '<S201>/u_3 to f_3 :'
     * Lookup Block: '<S201>/u_3 to f_3'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_3tof_3_d),
                         TemplateNIPID_P.u_3tof_3_YData_b,
                         TemplateNIPID_B.Saturation_g[2],
                         TemplateNIPID_P.u_3tof_3_XData_h, 38U);

    /* RelationalOperator: '<S208>/Compare' incorporates:
     *  Constant: '<S208>/Constant'
     */
    TemplateNIPID_B.Compare_lj = (TemplateNIPID_B.Saturation_g[3] <
      TemplateNIPID_P.Constant_Value_li);

    /* RelationalOperator: '<S209>/Compare' incorporates:
     *  Constant: '<S209>/Constant'
     */
    TemplateNIPID_B.Compare_p = (TemplateNIPID_B.Saturation_g[3] >=
      TemplateNIPID_P.Constant_Value_of);

    /* Gain: '<S202>/Gain' */
    TemplateNIPID_B.Gain_n = (uint16_T)(TemplateNIPID_P.Gain_Gain_p2 *
      TemplateNIPID_B.Compare_p);

    /* Sum: '<S202>/Sum' */
    TemplateNIPID_B.Sum_mo = (uint16_T)(uint32_T)((TemplateNIPID_B.Compare_lj <<
      6) + TemplateNIPID_B.Gain_n);

    /* Lookup Block: '<S202>/u_4 < -0.1'
     * About '<S202>/u_4 < -0.1 :'
     * Lookup Block: '<S202>/u_4 < -0.1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_401_d),
                         TemplateNIPID_P.u_401_YData_p,
                         TemplateNIPID_B.Saturation_g[3],
                         TemplateNIPID_P.u_401_XData_m, 14U);

    /* Lookup Block: '<S202>/u_4 >= -0.1'
     * About '<S202>/u_4 >= -0.1 :'
     * Lookup Block: '<S202>/u_4 >= -0.1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_401_hy),
                         TemplateNIPID_P.u_401_YData_ec,
                         TemplateNIPID_B.Saturation_g[3],
                         TemplateNIPID_P.u_401_XData_e, 12U);

    /* MultiPortSwitch: '<S202>/Multiport Switch' */
    if ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_mo >> 6) == 1) {
      TemplateNIPID_B.MultiportSwitch_b = TemplateNIPID_B.u_401_d;
    } else {
      TemplateNIPID_B.MultiportSwitch_b = TemplateNIPID_B.u_401_hy;
    }

    /* DeadZone Block: '<S203>/Dead Zone +-0.01'
     */
    if (TemplateNIPID_B.Saturation_g[4] >= TemplateNIPID_P.DeadZone001_End_e) {
      TemplateNIPID_B.DeadZone001_e = TemplateNIPID_B.Saturation_g[4] -
        TemplateNIPID_P.DeadZone001_End_e;
    } else if (TemplateNIPID_B.Saturation_g[4] >
               TemplateNIPID_P.DeadZone001_Start_f) {
      TemplateNIPID_B.DeadZone001_e = 0.0;
    } else {
      TemplateNIPID_B.DeadZone001_e = TemplateNIPID_B.Saturation_g[4] -
        TemplateNIPID_P.DeadZone001_Start_f;
    }

    /* RelationalOperator: '<S210>/Compare' incorporates:
     *  Constant: '<S210>/Constant'
     */
    TemplateNIPID_B.Compare_fg = (TemplateNIPID_B.DeadZone001_e <
      TemplateNIPID_P.Constant_Value_pp);

    /* RelationalOperator: '<S212>/Compare' */
    TemplateNIPID_B.Compare_c = (TemplateNIPID_B.DeadZone001_e == 0.0);

    /* Gain: '<S203>/Gain' */
    TemplateNIPID_B.Gain_ji = (uint16_T)(TemplateNIPID_P.Gain_Gain_a1 *
      TemplateNIPID_B.Compare_c);

    /* RelationalOperator: '<S211>/Compare' incorporates:
     *  Constant: '<S211>/Constant'
     */
    TemplateNIPID_B.Compare_kd = (TemplateNIPID_B.DeadZone001_e >
      TemplateNIPID_P.Constant_Value_ab);

    /* Gain: '<S203>/Gain1' */
    TemplateNIPID_B.Gain1_i = (uint16_T)(TemplateNIPID_P.Gain1_Gain_g5 *
      TemplateNIPID_B.Compare_kd);

    /* Sum: '<S203>/Sum' */
    TemplateNIPID_B.Sum_a = (uint16_T)(uint32_T)(((TemplateNIPID_B.Compare_fg <<
      6) + TemplateNIPID_B.Gain_ji) + TemplateNIPID_B.Gain1_i);

    /* Lookup Block: '<S203>/u_5 < 0'
     * About '<S203>/u_5 < 0 :'
     * Lookup Block: '<S203>/u_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_50_j),
                         TemplateNIPID_P.u_50_YData_ca,
                         TemplateNIPID_B.Saturation_g[4],
                         TemplateNIPID_P.u_50_XData_e, 9U);

    /* Lookup Block: '<S203>/u_5 > 0'
     * About '<S203>/u_5 > 0 :'
     * Lookup Block: '<S203>/u_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateNIPID_B.u_50_ns),
                         TemplateNIPID_P.u_50_YData_a,
                         TemplateNIPID_B.Saturation_g[4],
                         TemplateNIPID_P.u_50_XData_ly, 9U);

    /* MultiPortSwitch: '<S203>/Multiport Switch' incorporates:
     *  Constant: '<S203>/u_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)TemplateNIPID_B.Sum_a >> 6)) {
     case 1:
      TemplateNIPID_B.MultiportSwitch_l = TemplateNIPID_B.u_50_j;
      break;

     case 2:
      TemplateNIPID_B.MultiportSwitch_l = TemplateNIPID_P.u_50_Value_p;
      break;

     default:
      TemplateNIPID_B.MultiportSwitch_l = TemplateNIPID_B.u_50_ns;
      break;
    }

    /* SignalConversion: '<S192>/TmpHiddenBufferAtProduct1Inport2' */
    TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_f[0] =
      TemplateNIPID_B.u_1tof_1_p1;
    TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_f[1] =
      TemplateNIPID_B.MultiportSwitch_d;
    TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_f[2] =
      TemplateNIPID_B.u_3tof_3_d;
    TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_f[3] =
      TemplateNIPID_B.MultiportSwitch_b;
    TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_f[4] =
      TemplateNIPID_B.MultiportSwitch_l;

    /* Sum: '<S191>/Sum1' */
    for (i = 0; i < 3; i++) {
      /* Product: '<S192>/Product1' */
      TemplateNIPID_B.Product1_c3[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
        TemplateNIPID_B.Product1_c3[i] = TemplateNIPID_B.x5[3 * tmp_6 + i] *
          TemplateNIPID_B.TmpHiddenBufferAtProduct1Inpo_f[tmp_6] +
          TemplateNIPID_B.Product1_c3[i];
      }

      /* Product: '<S191>/Product1' */
      TemplateNIPID_B.Product1_n[i] = 0.0;
      TemplateNIPID_B.Product1_n[i] = TemplateNIPID_B.LinearDampningmatrix[i] *
        TemplateNIPID_B.nu[0] + TemplateNIPID_B.Product1_n[i];
      TemplateNIPID_B.Product1_n[i] = TemplateNIPID_B.LinearDampningmatrix[i + 3]
        * TemplateNIPID_B.nu[1] + TemplateNIPID_B.Product1_n[i];
      TemplateNIPID_B.Product1_n[i] = TemplateNIPID_B.LinearDampningmatrix[i + 6]
        * TemplateNIPID_B.nu[2] + TemplateNIPID_B.Product1_n[i];
    }

    TemplateNIPID_B.Sum1_ei[0] = TemplateNIPID_B.Row1_j +
      TemplateNIPID_B.Product1_c3[0];
    TemplateNIPID_B.Sum1_ei[1] = TemplateNIPID_B.Row2_o +
      TemplateNIPID_B.Product1_c3[1];
    TemplateNIPID_B.Sum1_ei[2] = TemplateNIPID_B.Row3_a +
      TemplateNIPID_B.Product1_c3[2];

    /* Sum: '<S191>/Sum8' */
    TemplateNIPID_B.Sum8[0] = (TemplateNIPID_B.Row1 + TemplateNIPID_B.Sum1_ei[0])
      - TemplateNIPID_B.Product1_n[0];
    TemplateNIPID_B.Sum8[1] = (TemplateNIPID_B.Row2 + TemplateNIPID_B.Sum1_ei[1])
      - TemplateNIPID_B.Product1_n[1];
    TemplateNIPID_B.Sum8[2] = (TemplateNIPID_B.Row3 + TemplateNIPID_B.Sum1_ei[2])
      - TemplateNIPID_B.Product1_n[2];

    /* Fcn: '<S193>/Fcn' */
    TemplateNIPID_B.x_dot = cos(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.nu[0]
      - sin(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.nu[1];

    /* Fcn: '<S193>/Fcn1' */
    TemplateNIPID_B.y_dot = sin(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.nu[0]
      + cos(TemplateNIPID_B.d2ryaw) * TemplateNIPID_B.nu[1];

    /* Fcn: '<S193>/Fcn2' */
    TemplateNIPID_B.psi_dot = TemplateNIPID_B.nu[2];

    /* Sum: '<S191>/Sum3' */
    TemplateNIPID_B.Sum3_b[0] = TemplateNIPID_B.K2[0] + TemplateNIPID_B.x_dot;
    TemplateNIPID_B.Sum3_b[1] = TemplateNIPID_B.K2[1] + TemplateNIPID_B.y_dot;
    TemplateNIPID_B.Sum3_b[2] = TemplateNIPID_B.K2[2] + TemplateNIPID_B.psi_dot;
    for (i = 0; i < 3; i++) {
      /* Product: '<S191>/Product' */
      TemplateNIPID_B.Product_ly[i] = 0.0;
      TemplateNIPID_B.Product_ly[i] = TemplateNIPID_B.Inverse[i] *
        TemplateNIPID_B.Sum8[0] + TemplateNIPID_B.Product_ly[i];
      TemplateNIPID_B.Product_ly[i] = TemplateNIPID_B.Inverse[i + 3] *
        TemplateNIPID_B.Sum8[1] + TemplateNIPID_B.Product_ly[i];
      TemplateNIPID_B.Product_ly[i] = TemplateNIPID_B.Inverse[i + 6] *
        TemplateNIPID_B.Sum8[2] + TemplateNIPID_B.Product_ly[i];

      /* Gain: '<S191>/inv(T_b)' */
      TemplateNIPID_B.invT_b[i] = 0.0;
      TemplateNIPID_B.invT_b[i] = TemplateNIPID_P.invT_b_Gain[i] *
        TemplateNIPID_B.bias[0] + TemplateNIPID_B.invT_b[i];
      TemplateNIPID_B.invT_b[i] = TemplateNIPID_P.invT_b_Gain[i + 3] *
        TemplateNIPID_B.bias[1] + TemplateNIPID_B.invT_b[i];
      TemplateNIPID_B.invT_b[i] = TemplateNIPID_P.invT_b_Gain[i + 6] *
        TemplateNIPID_B.bias[2] + TemplateNIPID_B.invT_b[i];

      /* Sum: '<S191>/Sum7' */
      TemplateNIPID_B.Sum7[i] = TemplateNIPID_B.K3[i] - TemplateNIPID_B.invT_b[i];
    }

    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
    }

    /* Outputs for enable SubSystem: '<S22>/CSE1 actuator' incorporates:
     *  Constant: '<S1>/Enable CSE1'
     *  EnablePort: '<S213>/Enable'
     */
    if (rtmIsMajorTimeStep(TemplateNIPID_M) && rtmIsMajorTimeStep
        (TemplateNIPID_M)) {
      if (TemplateNIPID_P.EnableCSE1_Value > 0.0) {
        if (TemplateNIPID_DWork.CSE1actuator_MODE == SUBSYS_DISABLED) {
          TemplateNIPID_DWork.CSE1actuator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (TemplateNIPID_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
          TemplateNIPID_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (TemplateNIPID_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S217>/BT_D_Gain1' */
      TemplateNIPID_B.BT_D_Gain1 = TemplateNIPID_P.BT_D_Gain1_Gain *
        TemplateNIPID_B.tauSwitch1[4];

      /* Gain: '<S217>/BT_D_Gain2' */
      TemplateNIPID_B.BT_D_Gain2 = TemplateNIPID_P.BT_D_Gain2_Gain *
        TemplateNIPID_B.tauSwitch1[4];

      /* Sum: '<S217>/Add' incorporates:
       *  Constant: '<S217>/BT_Power_Offset1'
       */
      TemplateNIPID_B.Add_ld = (TemplateNIPID_B.BT_D_Gain1 +
        TemplateNIPID_P.BT_Power_Offset1_Value) + TemplateNIPID_B.BT_D_Gain2;

      /* Gain: '<S217>/BT_L_Gain1' */
      TemplateNIPID_B.BT_L_Gain1 = TemplateNIPID_P.BT_L_Gain1_Gain *
        TemplateNIPID_B.tauSwitch1[5];

      /* Gain: '<S217>/BT_L_Gain2' */
      TemplateNIPID_B.BT_L_Gain2 = TemplateNIPID_P.BT_L_Gain2_Gain *
        TemplateNIPID_B.tauSwitch1[5];

      /* Gain: '<S217>/Neg' */
      TemplateNIPID_B.Neg = TemplateNIPID_P.Neg_Gain *
        TemplateNIPID_B.tauSwitch1[5];
      if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      }

      /* Sum: '<S217>/Sum1' incorporates:
       *  Constant: '<S217>/BT_Power_Offset2'
       */
      TemplateNIPID_B.Sum1_el = TemplateNIPID_B.BT_L_Gain1 +
        TemplateNIPID_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S219>/LowerRelop1' */
      TemplateNIPID_B.LowerRelop1_g = (TemplateNIPID_B.Add_ld >
        TemplateNIPID_B.Sum1_el);

      /* Sum: '<S217>/Sum2' incorporates:
       *  Constant: '<S217>/BT_Power_Offset3'
       */
      TemplateNIPID_B.Sum2_b = TemplateNIPID_B.BT_L_Gain2 +
        TemplateNIPID_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S219>/UpperRelop' */
      TemplateNIPID_B.UpperRelop_p1 = (TemplateNIPID_B.Add_ld <
        TemplateNIPID_B.Sum2_b);

      /* Switch: '<S219>/Switch' */
      if (TemplateNIPID_B.UpperRelop_p1) {
        TemplateNIPID_B.Switch_f = TemplateNIPID_B.Sum2_b;
      } else {
        TemplateNIPID_B.Switch_f = TemplateNIPID_B.Add_ld;
      }

      /* Switch: '<S219>/Switch2' */
      if (TemplateNIPID_B.LowerRelop1_g) {
        TemplateNIPID_B.Switch2_d = TemplateNIPID_B.Sum1_el;
      } else {
        TemplateNIPID_B.Switch2_d = TemplateNIPID_B.Switch_f;
      }

      if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      }

      /* RelationalOperator: '<S220>/LowerRelop1' incorporates:
       *  Constant: '<S217>/Constant'
       */
      TemplateNIPID_B.LowerRelop1_n = (TemplateNIPID_B.tauSwitch1[4] >
        TemplateNIPID_P.Constant_Value_j3);

      /* RelationalOperator: '<S220>/UpperRelop' */
      TemplateNIPID_B.UpperRelop_k = (TemplateNIPID_B.tauSwitch1[4] <
        TemplateNIPID_B.Neg);

      /* Switch: '<S220>/Switch' */
      if (TemplateNIPID_B.UpperRelop_k) {
        TemplateNIPID_B.Switch_g = TemplateNIPID_B.Neg;
      } else {
        TemplateNIPID_B.Switch_g = TemplateNIPID_B.tauSwitch1[4];
      }

      /* Switch: '<S220>/Switch2' incorporates:
       *  Constant: '<S217>/Constant'
       */
      if (TemplateNIPID_B.LowerRelop1_n) {
        TemplateNIPID_B.Switch2_j = TemplateNIPID_P.Constant_Value_j3;
      } else {
        TemplateNIPID_B.Switch2_j = TemplateNIPID_B.Switch_g;
      }

      if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      }

      /* RelationalOperator: '<S221>/LowerRelop1' */
      TemplateNIPID_B.LowerRelop1_b = (TemplateNIPID_B.tauSwitch1[4] >
        TemplateNIPID_B.tauSwitch1[5]);

      /* RelationalOperator: '<S221>/UpperRelop' incorporates:
       *  Constant: '<S217>/Constant1'
       */
      TemplateNIPID_B.UpperRelop_c = (TemplateNIPID_B.tauSwitch1[4] <
        TemplateNIPID_P.Constant1_Value_m);

      /* Switch: '<S221>/Switch' incorporates:
       *  Constant: '<S217>/Constant1'
       */
      if (TemplateNIPID_B.UpperRelop_c) {
        TemplateNIPID_B.Switch_a = TemplateNIPID_P.Constant1_Value_m;
      } else {
        TemplateNIPID_B.Switch_a = TemplateNIPID_B.tauSwitch1[4];
      }

      /* Switch: '<S221>/Switch2' */
      if (TemplateNIPID_B.LowerRelop1_b) {
        TemplateNIPID_B.Switch2_a = TemplateNIPID_B.tauSwitch1[5];
      } else {
        TemplateNIPID_B.Switch2_a = TemplateNIPID_B.Switch_a;
      }

      /* Signum: '<S218>/Sign' */
      TemplateNIPID_B.Sign_e = rt_SIGNd_snf(TemplateNIPID_B.tauSwitch1[6]);

      /* Product: '<S218>/Product1' */
      TemplateNIPID_B.PortVPS_X = TemplateNIPID_B.tauSwitch1[1] *
        TemplateNIPID_B.Sign_e;

      /* Gain: '<S218>/-x' */
      TemplateNIPID_B.PortVPS_X_d = TemplateNIPID_P.x_Gain *
        TemplateNIPID_B.PortVPS_X;

      /* Product: '<S218>/Product2' */
      TemplateNIPID_B.PortVSP_Y = TemplateNIPID_B.tauSwitch1[0] *
        TemplateNIPID_B.Sign_e;

      /* Gain: '<S218>/-y' */
      TemplateNIPID_B.PortVSP_Y_g = TemplateNIPID_P.y_Gain *
        TemplateNIPID_B.PortVSP_Y;

      /* Product: '<S218>/Product3' */
      TemplateNIPID_B.StarboardVSP_X = TemplateNIPID_B.tauSwitch1[3] *
        TemplateNIPID_B.Sign_e;

      /* Product: '<S218>/Product4' */
      TemplateNIPID_B.StarboardVSP_Y = TemplateNIPID_B.tauSwitch1[2] *
        TemplateNIPID_B.Sign_e;

      /* Lookup2D: '<S218>/Servo1' */
      TemplateNIPID_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&TemplateNIPID_P.Servo1_RowIdx[0]), 3, (const real_T *)
        (&TemplateNIPID_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&TemplateNIPID_P.Servo1_Table[0]), (const real_T)
        TemplateNIPID_B.PortVPS_X_d, (const real_T)TemplateNIPID_B.PortVSP_Y_g);

      /* Lookup2D: '<S218>/Servo2' */
      TemplateNIPID_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&TemplateNIPID_P.Servo2_RowIdx[0]), 3, (const real_T *)
        (&TemplateNIPID_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&TemplateNIPID_P.Servo2_Table[0]), (const real_T)
        TemplateNIPID_B.PortVPS_X_d, (const real_T)TemplateNIPID_B.PortVSP_Y_g);

      /* Lookup2D: '<S218>/Servo3' */
      TemplateNIPID_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&TemplateNIPID_P.Servo3_RowIdx[0]), 3, (const real_T *)
        (&TemplateNIPID_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&TemplateNIPID_P.Servo3_Table[0]), (const real_T)
        TemplateNIPID_B.StarboardVSP_X, (const real_T)
        TemplateNIPID_B.StarboardVSP_Y);

      /* Lookup2D: '<S218>/Servo4' */
      TemplateNIPID_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&TemplateNIPID_P.Servo4_RowIdx[0]), 3, (const real_T *)
        (&TemplateNIPID_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&TemplateNIPID_P.Servo4_Table[0]), (const real_T)
        TemplateNIPID_B.StarboardVSP_X, (const real_T)
        TemplateNIPID_B.StarboardVSP_Y);

      /* Gain: '<S218>/VPS_Speed_Gain' */
      TemplateNIPID_B.VPS_Speed_Gain = TemplateNIPID_P.VPS_Speed_Gain_Gain *
        TemplateNIPID_B.tauSwitch1[6];

      /* Sum: '<S218>/Sum' incorporates:
       *  Constant: '<S218>/VPS_Power_Offset'
       */
      TemplateNIPID_B.Sum_di = TemplateNIPID_B.VPS_Speed_Gain +
        TemplateNIPID_P.VPS_Power_Offset_Value;

      /* Gain: '<S218>/VSPS Port' */
      TemplateNIPID_B.VSPSPort = TemplateNIPID_P.VSPSPort_Gain *
        TemplateNIPID_B.Sum_di;

      /* Gain: '<S218>/VSPS Starboard' */
      TemplateNIPID_B.VSPSStarboard = TemplateNIPID_P.VSPSStarboard_Gain *
        TemplateNIPID_B.Sum_di;
    }

    /* end of Outputs for SubSystem: '<S22>/CSE1 actuator' */
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Product Block: '<S22>/Inverse' */
      {
        static const int_T dims[3] = { 3, 3, 3 };

        rt_MatDivRR_Dbl(TemplateNIPID_B.Inverse_m, TemplateNIPID_B.x3,
                        &TemplateNIPID_DWork.Inverse_DWORK4_d[0], (real_T*)
                        &TemplateNIPID_DWork.Pseudoinverse_X[0],
                        &TemplateNIPID_DWork.Inverse_DWORK2[0], (real_T*)
                        &TemplateNIPID_DWork.Inverse_DWORK3[0],
                        &dims[0]);
      }
    }

    /* Saturate: '<S216>/Saturation' */
    tmp = TemplateNIPID_B.tauSwitch[0];
    TemplateNIPID_B.Saturation_i4 = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation_LowerSat_ig,
      TemplateNIPID_P.Saturation_UpperSat_l);

    /* Saturate: '<S216>/Saturation1' */
    tmp = TemplateNIPID_B.tauSwitch[1];
    TemplateNIPID_B.Saturation1 = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation1_LowerSat, TemplateNIPID_P.Saturation1_UpperSat);

    /* Saturate: '<S216>/Saturation2' */
    tmp = TemplateNIPID_B.tauSwitch[2];
    TemplateNIPID_B.Saturation2 = rt_SATURATE(tmp,
      TemplateNIPID_P.Saturation2_LowerSat, TemplateNIPID_P.Saturation2_UpperSat);

    /* Gain: '<S216>/plant tau_surge' */
    TemplateNIPID_B.planttau_surge = TemplateNIPID_P.planttau_surge_Gain *
      TemplateNIPID_B.Saturation_i4;

    /* Gain: '<S216>/plant tau_sway' */
    TemplateNIPID_B.planttau_sway = TemplateNIPID_P.planttau_sway_Gain *
      TemplateNIPID_B.Saturation1;

    /* Gain: '<S216>/plant tau_yaw' */
    TemplateNIPID_B.planttau_yaw = TemplateNIPID_P.planttau_yaw_Gain *
      TemplateNIPID_B.Saturation2;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
      /* Gain: '<S224>/Battery Bow Thruster' */
      TemplateNIPID_B.BatteryBowThruster =
        TemplateNIPID_P.BatteryBowThruster_Gain * TemplateNIPID_B.SITzAI0;

      /* Gain: '<S224>/Battery Main' */
      TemplateNIPID_B.BatteryMain = TemplateNIPID_P.BatteryMain_Gain *
        TemplateNIPID_B.SITzAI2;

      /* Gain: '<S224>/Battery Servo' */
      TemplateNIPID_B.BatteryServo = TemplateNIPID_P.BatteryServo_Gain *
        TemplateNIPID_B.SITzAI1;
    }

    /* Gain: '<S225>/plant BT power' */
    TemplateNIPID_B.plantBTpower = TemplateNIPID_P.plantBTpower_Gain *
      TemplateNIPID_B.tauSwitch1[5];

    /* Gain: '<S225>/plant VSP speed' */
    TemplateNIPID_B.plantVSPspeed = TemplateNIPID_P.plantVSPspeed_Gain *
      TemplateNIPID_B.tauSwitch1[6];

    /* Gain: '<S225>/plant u_1' */
    TemplateNIPID_B.plantu_1 = TemplateNIPID_P.plantu_1_Gain *
      TemplateNIPID_B.tauSwitch1[0];

    /* Gain: '<S225>/plant u_2' */
    TemplateNIPID_B.plantu_2 = TemplateNIPID_P.plantu_2_Gain *
      TemplateNIPID_B.tauSwitch1[1];

    /* Gain: '<S225>/plant u_3' */
    TemplateNIPID_B.plantu_3 = TemplateNIPID_P.plantu_3_Gain *
      TemplateNIPID_B.tauSwitch1[2];

    /* Gain: '<S225>/plant u_4' */
    TemplateNIPID_B.plantu_4 = TemplateNIPID_P.plantu_4_Gain *
      TemplateNIPID_B.tauSwitch1[3];

    /* Gain: '<S225>/plant u_5' */
    TemplateNIPID_B.plantu_5 = TemplateNIPID_P.plantu_5_Gain *
      TemplateNIPID_B.tauSwitch1[4];

    /* Gain: '<S225>/fact1' */
    TemplateNIPID_B.fact1 = TemplateNIPID_P.fact1_Gain *
      TemplateNIPID_B.Product_pk[0];

    /* Gain: '<S225>/fact2' */
    TemplateNIPID_B.fact2 = TemplateNIPID_P.fact2_Gain *
      TemplateNIPID_B.Product_pk[1];

    /* Gain: '<S225>/fact3' */
    TemplateNIPID_B.fact3 = TemplateNIPID_P.fact3_Gain *
      TemplateNIPID_B.Product_pk[2];

    /* Gain: '<S225>/fact4' */
    TemplateNIPID_B.fact4 = TemplateNIPID_P.fact4_Gain *
      TemplateNIPID_B.Product_pk[3];

    /* Gain: '<S225>/fact5' */
    TemplateNIPID_B.fact5 = TemplateNIPID_P.fact5_Gain *
      TemplateNIPID_B.Product_pk[4];

    /* Gain: '<S225>/taux' */
    TemplateNIPID_B.taux = TemplateNIPID_P.taux_Gain *
      TemplateNIPID_B.tauSwitch[0];

    /* Gain: '<S225>/tauy' */
    TemplateNIPID_B.tauy = TemplateNIPID_P.tauy_Gain *
      TemplateNIPID_B.tauSwitch[1];

    /* Gain: '<S225>/tauyaw' */
    TemplateNIPID_B.tauyaw = TemplateNIPID_P.tauyaw_Gain *
      TemplateNIPID_B.tauSwitch[2];

    /* Gain: '<S225>/omega_qy' */
    TemplateNIPID_B.omega_qy = TemplateNIPID_P.omega_qy_Gain *
      TemplateNIPID_B.Integrator2[1];

    /* Gain: '<S225>/omegaqx' */
    TemplateNIPID_B.omegaqx = TemplateNIPID_P.omegaqx_Gain *
      TemplateNIPID_B.Integrator2[0];

    /* Gain: '<S226>/CSE1_r [deg//s]' */
    TemplateNIPID_B.CSE1_rdegs = TemplateNIPID_P.CSE1_rdegs_Gain *
      TemplateNIPID_B.nuSwitch[2];

    /* Gain: '<S226>/CSE1_u [m//s]' */
    TemplateNIPID_B.CSE1_ums = TemplateNIPID_P.CSE1_ums_Gain *
      TemplateNIPID_B.nuSwitch[0];

    /* Gain: '<S226>/CSE1_v [m//s]' */
    TemplateNIPID_B.CSE1_vms = TemplateNIPID_P.CSE1_vms_Gain *
      TemplateNIPID_B.nuSwitch[1];

    /* Gain: '<S226>/QS Error' */
    TemplateNIPID_B.QSError = TemplateNIPID_P.QSError_Gain *
      TemplateNIPID_B.QTMIn2Error;

    /* Gain: '<S226>/QS Frame' */
    TemplateNIPID_B.QSFrame = TemplateNIPID_P.QSFrame_Gain *
      TemplateNIPID_B.QTMIn1FN;

    /* Sum: '<S227>/Sum' */
    TemplateNIPID_B.Sum_gn[0] = TemplateNIPID_B.etaSwitch[0] -
      TemplateNIPID_B.Switch2;
    TemplateNIPID_B.Sum_gn[1] = TemplateNIPID_B.etaSwitch[1] -
      TemplateNIPID_B.Switch2_c;
    TemplateNIPID_B.Sum_gn[2] = TemplateNIPID_B.etaSwitch[2] -
      TemplateNIPID_B.Sum_k;

    /* Sum: '<S227>/Sum1' */
    TemplateNIPID_B.Sum1_i[0] = TemplateNIPID_B.VectorConcatenate[0] -
      TemplateNIPID_B.Switch2;
    TemplateNIPID_B.Sum1_i[1] = TemplateNIPID_B.VectorConcatenate[1] -
      TemplateNIPID_B.Switch2_c;
    TemplateNIPID_B.Sum1_i[2] = TemplateNIPID_B.VectorConcatenate[2] -
      TemplateNIPID_B.Sum_k;

    /* Gain: '<S225>/tau1' */
    TemplateNIPID_B.tau1[0] = TemplateNIPID_P.tau1_Gain *
      TemplateNIPID_B.Gain_p[0];

    /* Gain: '<S225>/tau2' */
    TemplateNIPID_B.tau2[0] = TemplateNIPID_P.tau2_Gain *
      TemplateNIPID_B.Gain1_a[0];

    /* Gain: '<S225>/tau3' */
    TemplateNIPID_B.tau3[0] = TemplateNIPID_P.tau3_Gain * TemplateNIPID_B.Gain2
      [0];

    /* Gain: '<S225>/tau4' */
    TemplateNIPID_B.tau4[0] = TemplateNIPID_P.tau4_Gain *
      TemplateNIPID_B.Product1_h4[0];

    /* Gain: '<S225>/tau5' */
    TemplateNIPID_B.tau5[0] = TemplateNIPID_P.tau5_Gain *
      TemplateNIPID_B.Product_k3[0];

    /* Gain: '<S225>/tau6' */
    TemplateNIPID_B.tau6[0] = TemplateNIPID_P.tau6_Gain *
      TemplateNIPID_B.Gain_mj[0];

    /* Sum: '<S227>/Sum2' */
    TemplateNIPID_B.Sum2_d[0] = TemplateNIPID_B.VectorConcatenate[0] -
      TemplateNIPID_B.etaSwitch[0];

    /* Gain: '<S225>/tau1' */
    TemplateNIPID_B.tau1[1] = TemplateNIPID_P.tau1_Gain *
      TemplateNIPID_B.Gain_p[1];

    /* Gain: '<S225>/tau2' */
    TemplateNIPID_B.tau2[1] = TemplateNIPID_P.tau2_Gain *
      TemplateNIPID_B.Gain1_a[1];

    /* Gain: '<S225>/tau3' */
    TemplateNIPID_B.tau3[1] = TemplateNIPID_P.tau3_Gain * TemplateNIPID_B.Gain2
      [1];

    /* Gain: '<S225>/tau4' */
    TemplateNIPID_B.tau4[1] = TemplateNIPID_P.tau4_Gain *
      TemplateNIPID_B.Product1_h4[1];

    /* Gain: '<S225>/tau5' */
    TemplateNIPID_B.tau5[1] = TemplateNIPID_P.tau5_Gain *
      TemplateNIPID_B.Product_k3[1];

    /* Gain: '<S225>/tau6' */
    TemplateNIPID_B.tau6[1] = TemplateNIPID_P.tau6_Gain *
      TemplateNIPID_B.Gain_mj[1];

    /* Sum: '<S227>/Sum2' */
    TemplateNIPID_B.Sum2_d[1] = TemplateNIPID_B.VectorConcatenate[1] -
      TemplateNIPID_B.etaSwitch[1];

    /* Gain: '<S225>/tau1' */
    TemplateNIPID_B.tau1[2] = TemplateNIPID_P.tau1_Gain *
      TemplateNIPID_B.Gain_p[2];

    /* Gain: '<S225>/tau2' */
    TemplateNIPID_B.tau2[2] = TemplateNIPID_P.tau2_Gain *
      TemplateNIPID_B.Gain1_a[2];

    /* Gain: '<S225>/tau3' */
    TemplateNIPID_B.tau3[2] = TemplateNIPID_P.tau3_Gain * TemplateNIPID_B.Gain2
      [2];

    /* Gain: '<S225>/tau4' */
    TemplateNIPID_B.tau4[2] = TemplateNIPID_P.tau4_Gain *
      TemplateNIPID_B.Product1_h4[2];

    /* Gain: '<S225>/tau5' */
    TemplateNIPID_B.tau5[2] = TemplateNIPID_P.tau5_Gain *
      TemplateNIPID_B.Product_k3[2];

    /* Gain: '<S225>/tau6' */
    TemplateNIPID_B.tau6[2] = TemplateNIPID_P.tau6_Gain *
      TemplateNIPID_B.Gain_mj[2];

    /* Sum: '<S227>/Sum2' */
    TemplateNIPID_B.Sum2_d[2] = TemplateNIPID_B.VectorConcatenate[2] -
      TemplateNIPID_B.etaSwitch[2];

    /* Gain: '<S227>/psi [deg]' */
    TemplateNIPID_B.psideg = TemplateNIPID_P.psideg_Gain *
      TemplateNIPID_B.etaSwitch[2];

    /* Gain: '<S227>/psi-psid [deg]' */
    TemplateNIPID_B.psipsiddeg = TemplateNIPID_P.psipsiddeg_Gain *
      TemplateNIPID_B.Sum_gn[2];

    /* Gain: '<S227>/psiLOS-psi [deg]' */
    TemplateNIPID_B.psiLOSpsideg = TemplateNIPID_P.psiLOSpsideg_Gain *
      TemplateNIPID_B.Sum2_d[2];

    /* Gain: '<S227>/psiLOS-psid [deg]' */
    TemplateNIPID_B.psiLOSpsiddeg = TemplateNIPID_P.psiLOSpsiddeg_Gain *
      TemplateNIPID_B.Sum1_i[2];

    /* Gain: '<S227>/psi_LOS [deg]' */
    TemplateNIPID_B.psi_LOSdeg = TemplateNIPID_P.psi_LOSdeg_Gain *
      TemplateNIPID_B.VectorConcatenate[2];

    /* Gain: '<S227>/psid [deg]' */
    TemplateNIPID_B.psiddeg = TemplateNIPID_P.psiddeg_Gain *
      TemplateNIPID_B.Sum_k;

    /* Gain: '<S227>/psi_plot' */
    TemplateNIPID_B.psi_plot[0] = TemplateNIPID_P.psi_plot_Gain *
      TemplateNIPID_B.psideg;
    TemplateNIPID_B.psi_plot[1] = TemplateNIPID_P.psi_plot_Gain *
      TemplateNIPID_B.psi_LOSdeg;
    TemplateNIPID_B.psi_plot[2] = TemplateNIPID_P.psi_plot_Gain *
      TemplateNIPID_B.psiddeg;

    /* Gain: '<S227>/qx [m]' */
    TemplateNIPID_B.qxm = TemplateNIPID_P.qxm_Gain *
      TemplateNIPID_B.VectorConcatenate[0];

    /* Gain: '<S227>/qx-x [m]' */
    TemplateNIPID_B.qxxm = TemplateNIPID_P.qxxm_Gain * TemplateNIPID_B.Sum2_d[0];

    /* Gain: '<S227>/qx-xd [m]1' */
    TemplateNIPID_B.qxxdm1 = TemplateNIPID_P.qxxdm1_Gain *
      TemplateNIPID_B.Sum1_i[0];

    /* Gain: '<S227>/qy [m]' */
    TemplateNIPID_B.qym = TemplateNIPID_P.qym_Gain *
      TemplateNIPID_B.VectorConcatenate[1];

    /* Gain: '<S227>/qy-y [m]' */
    TemplateNIPID_B.qyym = TemplateNIPID_P.qyym_Gain * TemplateNIPID_B.Sum2_d[1];

    /* Gain: '<S227>/qy-yd [m]1' */
    TemplateNIPID_B.qyydm1 = TemplateNIPID_P.qyydm1_Gain *
      TemplateNIPID_B.Sum1_i[1];

    /* Gain: '<S227>/x [m]' */
    TemplateNIPID_B.xm = TemplateNIPID_P.xm_Gain * TemplateNIPID_B.etaSwitch[0];

    /* Gain: '<S227>/x-xd [m]' */
    TemplateNIPID_B.xxdm = TemplateNIPID_P.xxdm_Gain * TemplateNIPID_B.Sum_gn[0];

    /* Gain: '<S227>/xd [m]' */
    TemplateNIPID_B.xdm = TemplateNIPID_P.xdm_Gain * TemplateNIPID_B.Switch2;

    /* Gain: '<S227>/x_plot' */
    TemplateNIPID_B.x_plot[0] = TemplateNIPID_P.x_plot_Gain * TemplateNIPID_B.xm;
    TemplateNIPID_B.x_plot[1] = TemplateNIPID_P.x_plot_Gain *
      TemplateNIPID_B.qxm;
    TemplateNIPID_B.x_plot[2] = TemplateNIPID_P.x_plot_Gain *
      TemplateNIPID_B.xdm;

    /* Gain: '<S227>/y [m]' */
    TemplateNIPID_B.ym = TemplateNIPID_P.ym_Gain * TemplateNIPID_B.etaSwitch[1];

    /* Gain: '<S227>/y-yd [m]' */
    TemplateNIPID_B.yydm = TemplateNIPID_P.yydm_Gain * TemplateNIPID_B.Sum_gn[1];

    /* Gain: '<S227>/yd [m]' */
    TemplateNIPID_B.ydm = TemplateNIPID_P.ydm_Gain * TemplateNIPID_B.Switch2_c;

    /* Gain: '<S227>/y_plot' */
    TemplateNIPID_B.y_plot[0] = TemplateNIPID_P.y_plot_Gain * TemplateNIPID_B.ym;
    TemplateNIPID_B.y_plot[1] = TemplateNIPID_P.y_plot_Gain *
      TemplateNIPID_B.qym;
    TemplateNIPID_B.y_plot[2] = TemplateNIPID_P.y_plot_Gain *
      TemplateNIPID_B.ydm;

    /* Gain: '<S227>/splot' */
    TemplateNIPID_B.splot = TemplateNIPID_P.splot_Gain *
      TemplateNIPID_B.Integrator1;
    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void TemplateNIPID_update(int_T tid)
{
  {
    int32_T tmp;

    /* Update for enable SubSystem: '<S22>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S214>/Enable'
     */
    if (TemplateNIPID_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S222>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        TemplateNIPID_B.Product1_bo[tmp] = 0.0;
        TemplateNIPID_B.Product1_bo[tmp] =
          TemplateNIPID_B.LinearDampningmatrix[tmp] *
          TemplateNIPID_B.Integrator_e[0] + TemplateNIPID_B.Product1_bo[tmp];
        TemplateNIPID_B.Product1_bo[tmp] =
          TemplateNIPID_B.LinearDampningmatrix[tmp + 3] *
          TemplateNIPID_B.Integrator_e[1] + TemplateNIPID_B.Product1_bo[tmp];
        TemplateNIPID_B.Product1_bo[tmp] =
          TemplateNIPID_B.LinearDampningmatrix[tmp + 6] *
          TemplateNIPID_B.Integrator_e[2] + TemplateNIPID_B.Product1_bo[tmp];
      }

      /* Sum: '<S222>/Sum' */
      TemplateNIPID_B.Sum_mk[0] = TemplateNIPID_B.planttau_surge -
        TemplateNIPID_B.Product1_bo[0];
      TemplateNIPID_B.Sum_mk[1] = TemplateNIPID_B.planttau_sway -
        TemplateNIPID_B.Product1_bo[1];
      TemplateNIPID_B.Sum_mk[2] = TemplateNIPID_B.planttau_yaw -
        TemplateNIPID_B.Product1_bo[2];
      for (tmp = 0; tmp < 3; tmp++) {
        /* Product: '<S222>/Product2' */
        TemplateNIPID_B.Product2_b[tmp] = 0.0;
        TemplateNIPID_B.Product2_b[tmp] = TemplateNIPID_B.Inverse_m[tmp] *
          TemplateNIPID_B.Sum_mk[0] + TemplateNIPID_B.Product2_b[tmp];
        TemplateNIPID_B.Product2_b[tmp] = TemplateNIPID_B.Inverse_m[tmp + 3] *
          TemplateNIPID_B.Sum_mk[1] + TemplateNIPID_B.Product2_b[tmp];
        TemplateNIPID_B.Product2_b[tmp] = TemplateNIPID_B.Inverse_m[tmp + 6] *
          TemplateNIPID_B.Sum_mk[2] + TemplateNIPID_B.Product2_b[tmp];

        /* Product: '<S222>/Product3' */
        TemplateNIPID_B.Product3_d[tmp] = 0.0;
        TemplateNIPID_B.Product3_d[tmp] = TemplateNIPID_B.Rpsi_o[tmp] *
          TemplateNIPID_B.Integrator_e[0] + TemplateNIPID_B.Product3_d[tmp];
        TemplateNIPID_B.Product3_d[tmp] = TemplateNIPID_B.Rpsi_o[tmp + 3] *
          TemplateNIPID_B.Integrator_e[1] + TemplateNIPID_B.Product3_d[tmp];
        TemplateNIPID_B.Product3_d[tmp] = TemplateNIPID_B.Rpsi_o[tmp + 6] *
          TemplateNIPID_B.Integrator_e[2] + TemplateNIPID_B.Product3_d[tmp];
      }
    }

    /* end of Update for SubSystem: '<S22>/Linear Simulator' */

    /* Derivative Block: '<S118>/Derivative' */
    {
      real_T timeStampA = TemplateNIPID_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = TemplateNIPID_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank = &TemplateNIPID_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 2;
        } else if (timeStampA >= timeStampB) {
          lastBank += 2;
        }
      }

      *lastBank++ = TemplateNIPID_M->Timing.t[0];
      *lastBank++ = TemplateNIPID_P.u_dm_Value;
    }

    /* Derivative Block: '<S188>/Derivative' */
    {
      real_T timeStampA = TemplateNIPID_DWork.Derivative_RWORK_e.TimeStampA;
      real_T timeStampB = TemplateNIPID_DWork.Derivative_RWORK_e.TimeStampB;
      real_T *lastBank = &TemplateNIPID_DWork.Derivative_RWORK_e.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = TemplateNIPID_M->Timing.t[0];
      *lastBank++ = TemplateNIPID_B.mm2mx;
      *lastBank++ = TemplateNIPID_B.mm2my;
      *lastBank++ = TemplateNIPID_B.mm2mz;
      *lastBank++ = TemplateNIPID_B.d2rroll;
      *lastBank++ = TemplateNIPID_B.d2rpitch;
      *lastBank++ = TemplateNIPID_B.d2ryaw;
    }

    if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
    }
  }

  if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
    rt_ertODEUpdateContinuousStates(&TemplateNIPID_M->solverInfo);
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
  if (!(++TemplateNIPID_M->Timing.clockTick0))
    ++TemplateNIPID_M->Timing.clockTickH0;
  TemplateNIPID_M->Timing.t[0] = TemplateNIPID_M->Timing.clockTick0 *
    TemplateNIPID_M->Timing.stepSize0 + TemplateNIPID_M->Timing.clockTickH0 *
    TemplateNIPID_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(TemplateNIPID_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++TemplateNIPID_M->Timing.clockTick1))
      ++TemplateNIPID_M->Timing.clockTickH1;
    TemplateNIPID_M->Timing.t[1] = TemplateNIPID_M->Timing.clockTick1 *
      TemplateNIPID_M->Timing.stepSize1 + TemplateNIPID_M->Timing.clockTickH1 *
      TemplateNIPID_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void TemplateNIPID_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S22>/Linear Simulator' */
    if (TemplateNIPID_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S222>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        TemplateNIPID_B.Product1_bo[tmp] = 0.0;
        TemplateNIPID_B.Product1_bo[tmp] =
          TemplateNIPID_B.LinearDampningmatrix[tmp] *
          TemplateNIPID_B.Integrator_e[0] + TemplateNIPID_B.Product1_bo[tmp];
        TemplateNIPID_B.Product1_bo[tmp] =
          TemplateNIPID_B.LinearDampningmatrix[tmp + 3] *
          TemplateNIPID_B.Integrator_e[1] + TemplateNIPID_B.Product1_bo[tmp];
        TemplateNIPID_B.Product1_bo[tmp] =
          TemplateNIPID_B.LinearDampningmatrix[tmp + 6] *
          TemplateNIPID_B.Integrator_e[2] + TemplateNIPID_B.Product1_bo[tmp];
      }

      /* Sum: '<S222>/Sum' */
      TemplateNIPID_B.Sum_mk[0] = TemplateNIPID_B.planttau_surge -
        TemplateNIPID_B.Product1_bo[0];
      TemplateNIPID_B.Sum_mk[1] = TemplateNIPID_B.planttau_sway -
        TemplateNIPID_B.Product1_bo[1];
      TemplateNIPID_B.Sum_mk[2] = TemplateNIPID_B.planttau_yaw -
        TemplateNIPID_B.Product1_bo[2];
      for (tmp = 0; tmp < 3; tmp++) {
        /* Product: '<S222>/Product2' */
        TemplateNIPID_B.Product2_b[tmp] = 0.0;
        TemplateNIPID_B.Product2_b[tmp] = TemplateNIPID_B.Inverse_m[tmp] *
          TemplateNIPID_B.Sum_mk[0] + TemplateNIPID_B.Product2_b[tmp];
        TemplateNIPID_B.Product2_b[tmp] = TemplateNIPID_B.Inverse_m[tmp + 3] *
          TemplateNIPID_B.Sum_mk[1] + TemplateNIPID_B.Product2_b[tmp];
        TemplateNIPID_B.Product2_b[tmp] = TemplateNIPID_B.Inverse_m[tmp + 6] *
          TemplateNIPID_B.Sum_mk[2] + TemplateNIPID_B.Product2_b[tmp];

        /* Product: '<S222>/Product3' */
        TemplateNIPID_B.Product3_d[tmp] = 0.0;
        TemplateNIPID_B.Product3_d[tmp] = TemplateNIPID_B.Rpsi_o[tmp] *
          TemplateNIPID_B.Integrator_e[0] + TemplateNIPID_B.Product3_d[tmp];
        TemplateNIPID_B.Product3_d[tmp] = TemplateNIPID_B.Rpsi_o[tmp + 3] *
          TemplateNIPID_B.Integrator_e[1] + TemplateNIPID_B.Product3_d[tmp];
        TemplateNIPID_B.Product3_d[tmp] = TemplateNIPID_B.Rpsi_o[tmp + 6] *
          TemplateNIPID_B.Integrator_e[2] + TemplateNIPID_B.Product3_d[tmp];
      }

      /* Integrator Block: '<S222>/Integrator' */
      {
        if (TemplateNIPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator_CSTATE_m[0] = TemplateNIPID_B.Product2_b[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator_CSTATE_m[0] = 0.0;
        }

        if (TemplateNIPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator_CSTATE_m[1] = TemplateNIPID_B.Product2_b[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator_CSTATE_m[1] = 0.0;
        }

        if (TemplateNIPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator_CSTATE_m[2] = TemplateNIPID_B.Product2_b[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator_CSTATE_m[2] = 0.0;
        }
      }

      /* Integrator Block: '<S222>/Integrator1' */
      {
        if (TemplateNIPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator1_CSTATE_m[0] = TemplateNIPID_B.Product3_d[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator1_CSTATE_m[0] = 0.0;
        }

        if (TemplateNIPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator1_CSTATE_m[1] = TemplateNIPID_B.Product3_d[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator1_CSTATE_m[1] = 0.0;
        }

        if (TemplateNIPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator1_CSTATE_m[2] = TemplateNIPID_B.Product3_d[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs
            )->Integrator1_CSTATE_m[2] = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_TemplateNIPID *)
                TemplateNIPID_M->ModelData.derivs)->Integrator_CSTATE_m[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S22>/Linear Simulator' */

    /* Integrator Block: '<S35>/Integrator' */
    {
      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = TemplateNIPID_B.Add1_g[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = 0.0;
      }

      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = TemplateNIPID_B.Add1_g[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = 0.0;
      }
    }

    /* Integrator Block: '<S35>/Integrator1' */
    {
      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator1_CSTATE = TemplateNIPID_B.Subtract_ni;
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator1_CSTATE = 0.0;
      }
    }

    /* Integrator Block: '<S40>/Integrator' */
    {
      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_o[0] = TemplateNIPID_B.Product_ak[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_o[0] = 0.0;
      }

      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_o[1] = TemplateNIPID_B.Product_ak[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_o[1] = 0.0;
      }

      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_o[2] = TemplateNIPID_B.Product_ak[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_o[2] = 0.0;
      }
    }

    /* Integrator Block: '<S191>/Integrator4' */
    {
      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator4_CSTATE[0] = TemplateNIPID_B.Product_ly[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator4_CSTATE[0] = 0.0;
      }

      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator4_CSTATE[1] = TemplateNIPID_B.Product_ly[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator4_CSTATE[1] = 0.0;
      }

      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator4_CSTATE[2] = TemplateNIPID_B.Product_ly[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator4_CSTATE[2] = 0.0;
      }
    }

    /* Integrator Block: '<S35>/Integrator2' */
    {
      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = TemplateNIPID_B.Gain_en[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = 0.0;
      }

      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = TemplateNIPID_B.Gain_en[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = 0.0;
      }
    }

    /* Integrator Block: '<S191>/Integrator' */
    {
      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_l[0] = TemplateNIPID_B.Sum3_b[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_l[0] = 0.0;
      }

      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_l[1] = TemplateNIPID_B.Sum3_b[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_l[1] = 0.0;
      }

      if (TemplateNIPID_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_l[2] = TemplateNIPID_B.Sum3_b[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
          ->Integrator_CSTATE_l[2] = 0.0;
      }
    }

    /* Derivatives for Integrator: '<S191>/Integrator3' */
    ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
      ->Integrator3_CSTATE[0] = TemplateNIPID_B.Sum7[0];
    ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
      ->Integrator3_CSTATE[1] = TemplateNIPID_B.Sum7[1];
    ((StateDerivatives_TemplateNIPID *) TemplateNIPID_M->ModelData.derivs)
      ->Integrator3_CSTATE[2] = TemplateNIPID_B.Sum7[2];
  }
}

/* Model initialize function */
void TemplateNIPID_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)TemplateNIPID_M,0,
                sizeof(RT_MODEL_TemplateNIPID));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&TemplateNIPID_M->solverInfo,
                          &TemplateNIPID_M->Timing.simTimeStep);
    rtsiSetTPtr(&TemplateNIPID_M->solverInfo, &rtmGetTPtr(TemplateNIPID_M));
    rtsiSetStepSizePtr(&TemplateNIPID_M->solverInfo,
                       &TemplateNIPID_M->Timing.stepSize0);
    rtsiSetdXPtr(&TemplateNIPID_M->solverInfo,
                 &TemplateNIPID_M->ModelData.derivs);
    rtsiSetContStatesPtr(&TemplateNIPID_M->solverInfo,
                         &TemplateNIPID_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&TemplateNIPID_M->solverInfo,
      &TemplateNIPID_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&TemplateNIPID_M->solverInfo, (&rtmGetErrorStatus
      (TemplateNIPID_M)));
    rtsiSetRTModelPtr(&TemplateNIPID_M->solverInfo, TemplateNIPID_M);
  }

  rtsiSetSimTimeStep(&TemplateNIPID_M->solverInfo, MAJOR_TIME_STEP);
  TemplateNIPID_M->ModelData.intgData.y = TemplateNIPID_M->ModelData.odeY;
  TemplateNIPID_M->ModelData.intgData.f[0] = TemplateNIPID_M->ModelData.odeF[0];
  TemplateNIPID_M->ModelData.intgData.f[1] = TemplateNIPID_M->ModelData.odeF[1];
  TemplateNIPID_M->ModelData.intgData.f[2] = TemplateNIPID_M->ModelData.odeF[2];
  TemplateNIPID_M->ModelData.intgData.f[3] = TemplateNIPID_M->ModelData.odeF[3];
  TemplateNIPID_M->ModelData.intgData.f[4] = TemplateNIPID_M->ModelData.odeF[4];
  TemplateNIPID_M->ModelData.intgData.f[5] = TemplateNIPID_M->ModelData.odeF[5];
  TemplateNIPID_M->ModelData.contStates = ((real_T *) &TemplateNIPID_X);
  rtsiSetSolverData(&TemplateNIPID_M->solverInfo, (void *)
                    &TemplateNIPID_M->ModelData.intgData);
  rtsiSetSolverName(&TemplateNIPID_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = TemplateNIPID_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    TemplateNIPID_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    TemplateNIPID_M->Timing.sampleTimes =
      (&TemplateNIPID_M->Timing.sampleTimesArray[0]);
    TemplateNIPID_M->Timing.offsetTimes =
      (&TemplateNIPID_M->Timing.offsetTimesArray[0]);

    /* task periods */
    TemplateNIPID_M->Timing.sampleTimes[0] = (0.0);
    TemplateNIPID_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    TemplateNIPID_M->Timing.offsetTimes[0] = (0.0);
    TemplateNIPID_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(TemplateNIPID_M, &TemplateNIPID_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = TemplateNIPID_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    TemplateNIPID_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(TemplateNIPID_M, -1);
  TemplateNIPID_M->Timing.stepSize0 = 0.1;
  TemplateNIPID_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(TemplateNIPID_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    TemplateNIPID_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(TemplateNIPID_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(TemplateNIPID_M->rtwLogInfo, (NULL));
    rtliSetLogT(TemplateNIPID_M->rtwLogInfo, "");
    rtliSetLogX(TemplateNIPID_M->rtwLogInfo, "");
    rtliSetLogXFinal(TemplateNIPID_M->rtwLogInfo, "");
    rtliSetSigLog(TemplateNIPID_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(TemplateNIPID_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(TemplateNIPID_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(TemplateNIPID_M->rtwLogInfo, 0);
    rtliSetLogDecimation(TemplateNIPID_M->rtwLogInfo, 1);
    rtliSetLogY(TemplateNIPID_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(TemplateNIPID_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(TemplateNIPID_M->rtwLogInfo, (NULL));
  }

  TemplateNIPID_M->solverInfoPtr = (&TemplateNIPID_M->solverInfo);
  TemplateNIPID_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&TemplateNIPID_M->solverInfo, 0.1);
  rtsiSetSolverMode(&TemplateNIPID_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  TemplateNIPID_M->ModelData.blockIO = ((void *) &TemplateNIPID_B);
  (void) memset(((void *) &TemplateNIPID_B),0,
                sizeof(BlockIO_TemplateNIPID));

  /* parameters */
  TemplateNIPID_M->ModelData.defaultParam = ((real_T *) &TemplateNIPID_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &TemplateNIPID_X;
    TemplateNIPID_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_TemplateNIPID));
  }

  /* states (dwork) */
  TemplateNIPID_M->Work.dwork = ((void *) &TemplateNIPID_DWork);
  (void) memset((void *)&TemplateNIPID_DWork, 0,
                sizeof(D_Work_TemplateNIPID));
  TemplateNIPID_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  TemplateNIPID_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  TemplateNIPID_PrevZCSigState.Integrator_Reset_ZCE_k = UNINITIALIZED_ZCSIG;
  TemplateNIPID_PrevZCSigState.Integrator4_Reset_ZCE = UNINITIALIZED_ZCSIG;
  TemplateNIPID_PrevZCSigState.Integrator2_Reset_ZCE = UNINITIALIZED_ZCSIG;
  TemplateNIPID_PrevZCSigState.Integrator_Reset_ZCE_g = UNINITIALIZED_ZCSIG;
  TemplateNIPID_PrevZCSigState.Integrator_Reset_ZCE_p = UNINITIALIZED_ZCSIG;
  TemplateNIPID_PrevZCSigState.Integrator1_Reset_ZCE_d = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void TemplateNIPID_terminate(void)
{
  /* ToFile Block: '<S19>/To File' */
  {
    FILE *fp = (FILE *) TemplateNIPID_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "NLPID_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(TemplateNIPID_M,
                          "Error closing MAT-file NLPID_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(TemplateNIPID_M,
                          "Error reopening MAT-file NLPID_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 66, TemplateNIPID_DWork.ToFile_IWORK.Count,
           "NLPID_data")) {
        rtmSetErrorStatus(TemplateNIPID_M,
                          "Error writing header for NLPID_data to MAT-file NLPID_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(TemplateNIPID_M,
                          "Error closing MAT-file NLPID_data.mat");
        return;
      }

      TemplateNIPID_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  TemplateNIPID_output(tid);
}

void MdlUpdate(int_T tid)
{
  TemplateNIPID_update(tid);
}

void MdlInitializeSizes(void)
{
  TemplateNIPID_M->Sizes.numContStates = (23);/* Number of continuous states */
  TemplateNIPID_M->Sizes.numY = (0);   /* Number of model outputs */
  TemplateNIPID_M->Sizes.numU = (0);   /* Number of model inputs */
  TemplateNIPID_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  TemplateNIPID_M->Sizes.numSampTimes = (2);/* Number of sample times */
  TemplateNIPID_M->Sizes.numBlocks = (972);/* Number of blocks */
  TemplateNIPID_M->Sizes.numBlockIO = (729);/* Number of block outputs */
  TemplateNIPID_M->Sizes.numBlockPrms = (1858);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Integrator Block: '<S35>/Integrator' */
  if (rtmIsFirstInitCond(TemplateNIPID_M)) {
    TemplateNIPID_X.Integrator_CSTATE[0] = 0.0;
    TemplateNIPID_X.Integrator_CSTATE[1] = 0.0;
  }

  TemplateNIPID_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S35>/Integrator1' */
  if (rtmIsFirstInitCond(TemplateNIPID_M)) {
    TemplateNIPID_X.Integrator1_CSTATE = 0.0;
  }

  TemplateNIPID_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S40>/Integrator' */
  TemplateNIPID_X.Integrator_CSTATE_o[0] = TemplateNIPID_P.Integrator_IC[0];
  TemplateNIPID_X.Integrator_CSTATE_o[1] = TemplateNIPID_P.Integrator_IC[1];
  TemplateNIPID_X.Integrator_CSTATE_o[2] = TemplateNIPID_P.Integrator_IC[2];

  /* Integrator Block: '<S191>/Integrator4' */
  TemplateNIPID_X.Integrator4_CSTATE[0] = TemplateNIPID_P.Integrator4_IC;
  TemplateNIPID_X.Integrator4_CSTATE[1] = TemplateNIPID_P.Integrator4_IC;
  TemplateNIPID_X.Integrator4_CSTATE[2] = TemplateNIPID_P.Integrator4_IC;

  /* Integrator Block: '<S35>/Integrator2' */
  TemplateNIPID_X.Integrator2_CSTATE[0] = TemplateNIPID_P.Integrator2_IC;
  TemplateNIPID_X.Integrator2_CSTATE[1] = TemplateNIPID_P.Integrator2_IC;

  /* Derivative Block: '<S118>/Derivative' */
  TemplateNIPID_DWork.Derivative_RWORK.TimeStampA = rtInf;
  TemplateNIPID_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* Derivative Block: '<S188>/Derivative' */
  TemplateNIPID_DWork.Derivative_RWORK_e.TimeStampA = rtInf;
  TemplateNIPID_DWork.Derivative_RWORK_e.TimeStampB = rtInf;

  /* Integrator Block: '<S191>/Integrator' */
  if (rtmIsFirstInitCond(TemplateNIPID_M)) {
    TemplateNIPID_X.Integrator_CSTATE_l[0] = 0.0;
    TemplateNIPID_X.Integrator_CSTATE_l[1] = 0.0;
    TemplateNIPID_X.Integrator_CSTATE_l[2] = 0.0;
  }

  TemplateNIPID_DWork.Integrator_IWORK_l.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<S191>/Integrator3' */
  TemplateNIPID_X.Integrator3_CSTATE[0] = TemplateNIPID_P.Integrator3_IC;
  TemplateNIPID_X.Integrator3_CSTATE[1] = TemplateNIPID_P.Integrator3_IC;
  TemplateNIPID_X.Integrator3_CSTATE[2] = TemplateNIPID_P.Integrator3_IC;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(TemplateNIPID_M)) {
    rtmSetFirstInitCond(TemplateNIPID_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for Constant: '<S4>/Initial psi [rad]' */
  TemplateNIPID_B.Initialpsirad = TemplateNIPID_P.Initialpsirad_Value;

  /* Start for Constant: '<S4>/Initial x [m]' */
  TemplateNIPID_B.Initialxm = TemplateNIPID_P.Initialxm_Value;

  /* Start for Constant: '<S4>/Initial y [m]' */
  TemplateNIPID_B.Initialym = TemplateNIPID_P.Initialym_Value;

  /* Start for Constant: '<S4>/Initial r [rad//s]' */
  TemplateNIPID_B.Initialrrads = TemplateNIPID_P.Initialrrads_Value;

  /* Start for Constant: '<S4>/Initial u [m//s]' */
  TemplateNIPID_B.Initialums = TemplateNIPID_P.Initialums_Value;

  /* Start for Constant: '<S4>/Initial v [m//s]' */
  TemplateNIPID_B.Initialvms = TemplateNIPID_P.Initialvms_Value;

  /* Start for Constant: '<S9>/Initial q_x' */
  TemplateNIPID_B.Initialq_x = TemplateNIPID_P.Initialq_x_Value;

  /* Start for Constant: '<S9>/Initial q_y' */
  TemplateNIPID_B.Initialq_y = TemplateNIPID_P.Initialq_y_Value;

  /* Start for Constant: '<S9>/Initial s' */
  TemplateNIPID_B.Initials = TemplateNIPID_P.Initials_Value;

  /* Start for enable SubSystem: '<S22>/Linear Simulator' */
  TemplateNIPID_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Integrator Block: '<S222>/Integrator' */
  if (rtmIsFirstInitCond(TemplateNIPID_M)) {
    TemplateNIPID_X.Integrator_CSTATE_m[0] = 0.0;
    TemplateNIPID_X.Integrator_CSTATE_m[1] = 0.0;
    TemplateNIPID_X.Integrator_CSTATE_m[2] = 0.0;
  }

  TemplateNIPID_DWork.Integrator_IWORK_k.IcNeedsLoading = 1;

  /* Integrator Block: '<S222>/Integrator1' */
  if (rtmIsFirstInitCond(TemplateNIPID_M)) {
    TemplateNIPID_X.Integrator1_CSTATE_m[0] = 0.0;
    TemplateNIPID_X.Integrator1_CSTATE_m[1] = 0.0;
    TemplateNIPID_X.Integrator1_CSTATE_m[2] = 0.0;
  }

  TemplateNIPID_DWork.Integrator1_IWORK_d.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S22>/Linear Simulator' */

  /* ToFile Block: '<S19>/To File' */
  {
    const char *fileName = "NLPID_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(TemplateNIPID_M,
                        "Error creating .mat file NLPID_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,66,0,"NLPID_data")) {
      rtmSetErrorStatus(TemplateNIPID_M,
                        "Error writing mat file header to file NLPID_data.mat");
      return;
    }

    TemplateNIPID_DWork.ToFile_IWORK.Count = 0;
    TemplateNIPID_DWork.ToFile_IWORK.Decimation = -1;
    TemplateNIPID_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* Create Identity Matrix for Block: '<S188>/Inverse' */
  {
    int_T i;
    real_T *dWork = &TemplateNIPID_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &TemplateNIPID_DWork.Inverse_DWORK4[0];
    while (dWork < &TemplateNIPID_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  /* Start for enable SubSystem: '<S22>/CSE1 actuator' */
  TemplateNIPID_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S22>/CSE1 actuator' */

  /* Create Identity Matrix for Block: '<S22>/Inverse' */
  {
    int_T i;
    real_T *dWork = &TemplateNIPID_DWork.Inverse_DWORK4_d[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &TemplateNIPID_DWork.Inverse_DWORK4_d[0];
    while (dWork < &TemplateNIPID_DWork.Inverse_DWORK4_d[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  MdlInitialize();
}

RT_MODEL_TemplateNIPID *TemplateNIPID(void)
{
  TemplateNIPID_initialize(1);
  return TemplateNIPID_M;
}

void MdlTerminate(void)
{
  TemplateNIPID_terminate();
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
#ifdef NI_ROOTMODEL_TemplateNIPID
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 45:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 46:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 47:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 45:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 46:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 47:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern TemplateNIPID_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Main Subsystems/Naviagation/Input from SIT/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(TemplateNIPID_B.QTMIn, count, data[index++], 48, 0);
    }
  } else {
    index += 9;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&TemplateNIPID_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&TemplateNIPID_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&TemplateNIPID_B.SITzAI2, 0, data[index++], 0, 0);
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
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Switch2_d,0,0,
      0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.VSPSStarboard,
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
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Switch2_d,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Servo1,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Servo2,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Servo3,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.Servo4,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.VSPSPort,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateNIPID_B.VSPSStarboard,0,
    0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "templatenipid/Inputs from LabVIEW/Control Input Selector/Value",
    offsetof(Parameters_TemplateNIPID, ControlInputSelector_Value), 31, 1, 2, 0,
    "", 0 },

  { 1, "templatenipid/Inputs from LabVIEW/Control Mode Selector/Value", offsetof
    (Parameters_TemplateNIPID, ControlModeSelector_Value), 31, 1, 2, 2, "", 0 },

  { 2, "templatenipid/Inputs from LabVIEW/Enable CSE1/Value", offsetof
    (Parameters_TemplateNIPID, EnableCSE1_Value), 31, 1, 2, 4, "", 0 },

  { 3, "templatenipid/Inputs from LabVIEW/tauxscale/Value", offsetof
    (Parameters_TemplateNIPID, tauxscale_Value), 31, 1, 2, 6, "", 0 },

  { 4, "templatenipid/Inputs from LabVIEW/tauyscale/Value", offsetof
    (Parameters_TemplateNIPID, tauyscale_Value), 31, 1, 2, 8, "", 0 },

  { 5, "templatenipid/Inputs from LabVIEW/tauyawscale/Value", offsetof
    (Parameters_TemplateNIPID, tauyawscale_Value), 31, 1, 2, 10, "", 0 },

  { 6, "templatenipid/Inputs from LabVIEW/offset u1/Value", offsetof
    (Parameters_TemplateNIPID, offsetu1_Value), 31, 1, 2, 12, "", 0 },

  { 7, "templatenipid/Inputs from LabVIEW/offset u2/Value", offsetof
    (Parameters_TemplateNIPID, offsetu2_Value), 31, 1, 2, 14, "", 0 },

  { 8, "templatenipid/Inputs from LabVIEW/offset u3/Value", offsetof
    (Parameters_TemplateNIPID, offsetu3_Value), 31, 1, 2, 16, "", 0 },

  { 9, "templatenipid/Inputs from LabVIEW/offset u4/Value", offsetof
    (Parameters_TemplateNIPID, offsetu4_Value), 31, 1, 2, 18, "", 0 },

  { 10,
    "templatenipid/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value",
    offsetof(Parameters_TemplateNIPID, EnableLinearSimulator_Value), 31, 1, 2,
    20, "", 0 },

  { 11,
    "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value",
    offsetof(Parameters_TemplateNIPID, Initialpsirad_Value), 31, 1, 2, 22, "", 0
  },

  { 12, "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value",
    offsetof(Parameters_TemplateNIPID, Initialxm_Value), 31, 1, 2, 24, "", 0 },

  { 13, "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value",
    offsetof(Parameters_TemplateNIPID, Initialym_Value), 31, 1, 2, 26, "", 0 },

  { 14,
    "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value",
    offsetof(Parameters_TemplateNIPID, Initialrrads_Value), 31, 1, 2, 28, "", 0
  },

  { 15,
    "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value",
    offsetof(Parameters_TemplateNIPID, Initialums_Value), 31, 1, 2, 30, "", 0 },

  { 16,
    "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value",
    offsetof(Parameters_TemplateNIPID, Initialvms_Value), 31, 1, 2, 32, "", 0 },

  { 17,
    "templatenipid/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_TemplateNIPID, ResetLinearSimulatorintegrator_), 31, 1,
    2, 34, "", 0 },

  { 18, "templatenipid/Inputs from LabVIEW/Path/Delta [m]/Value", offsetof
    (Parameters_TemplateNIPID, Deltam_Value), 31, 1, 2, 36, "", 0 },

  { 19, "templatenipid/Inputs from LabVIEW/Path/Path Selector  [-]/Value",
    offsetof(Parameters_TemplateNIPID, PathSelector_Value), 31, 1, 2, 38, "", 0
  },

  { 20, "templatenipid/Inputs from LabVIEW/Path/my [-]/Value", offsetof
    (Parameters_TemplateNIPID, my_Value), 31, 1, 2, 40, "", 0 },

  { 21, "templatenipid/Inputs from LabVIEW/Path/u_d [m]/Value", offsetof
    (Parameters_TemplateNIPID, u_dm_Value), 31, 1, 2, 42, "", 0 },

  { 22, "templatenipid/Inputs from LabVIEW/Path/x_dmax [m]/Value", offsetof
    (Parameters_TemplateNIPID, x_dmaxm_Value), 31, 1, 2, 44, "", 0 },

  { 23, "templatenipid/Inputs from LabVIEW/Path/x_dmin [m]/Value", offsetof
    (Parameters_TemplateNIPID, x_dminm_Value), 31, 1, 2, 46, "", 0 },

  { 24, "templatenipid/Inputs from LabVIEW/Path/y_dmax [m]/Value", offsetof
    (Parameters_TemplateNIPID, y_dmaxm_Value), 31, 1, 2, 48, "", 0 },

  { 25, "templatenipid/Inputs from LabVIEW/Path/y_dmin [m]/Value", offsetof
    (Parameters_TemplateNIPID, y_dminm_Value), 31, 1, 2, 50, "", 0 },

  { 26, "templatenipid/Inputs from LabVIEW/Path/Ellipse/k [-]/Value", offsetof
    (Parameters_TemplateNIPID, k_Value), 31, 1, 2, 52, "", 0 },

  { 27, "templatenipid/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value", offsetof
    (Parameters_TemplateNIPID, r_xm_Value), 31, 1, 2, 54, "", 0 },

  { 28, "templatenipid/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value", offsetof
    (Parameters_TemplateNIPID, r_ym_Value), 31, 1, 2, 56, "", 0 },

  { 29, "templatenipid/Inputs from LabVIEW/Path/Ellipse/x_0 [m]/Value", offsetof
    (Parameters_TemplateNIPID, x_0m_Value), 31, 1, 2, 58, "", 0 },

  { 30, "templatenipid/Inputs from LabVIEW/Path/Ellipse/y_0 [m]/Value", offsetof
    (Parameters_TemplateNIPID, y_0m_Value), 31, 1, 2, 60, "", 0 },

  { 31, "templatenipid/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value", offsetof
    (Parameters_TemplateNIPID, x_1m_Value), 31, 1, 2, 62, "", 0 },

  { 32, "templatenipid/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value", offsetof
    (Parameters_TemplateNIPID, x_2m_Value), 31, 1, 2, 64, "", 0 },

  { 33, "templatenipid/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value", offsetof
    (Parameters_TemplateNIPID, y_1m_Value), 31, 1, 2, 66, "", 0 },

  { 34, "templatenipid/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value", offsetof
    (Parameters_TemplateNIPID, y_2m_Value), 31, 1, 2, 68, "", 0 },

  { 35, "templatenipid/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value",
    offsetof(Parameters_TemplateNIPID, AS_LX_Value), 31, 1, 2, 70, "", 0 },

  { 36, "templatenipid/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain",
    offsetof(Parameters_TemplateNIPID, ScalingLX_Gain), 31, 1, 2, 72, "", 0 },

  { 37, "templatenipid/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value",
    offsetof(Parameters_TemplateNIPID, AS_LY_Value), 31, 1, 2, 74, "", 0 },

  { 38, "templatenipid/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain",
    offsetof(Parameters_TemplateNIPID, ScalingLY_Gain), 31, 1, 2, 76, "", 0 },

  { 39, "templatenipid/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value",
    offsetof(Parameters_TemplateNIPID, AS_RX_Value), 31, 1, 2, 78, "", 0 },

  { 40, "templatenipid/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain",
    offsetof(Parameters_TemplateNIPID, Scaling_RX_Gain), 31, 1, 2, 80, "", 0 },

  { 41, "templatenipid/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value",
    offsetof(Parameters_TemplateNIPID, AS_RY_Value), 31, 1, 2, 82, "", 0 },

  { 42, "templatenipid/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain",
    offsetof(Parameters_TemplateNIPID, ScalingRY_Gain), 31, 1, 2, 84, "", 0 },

  { 43, "templatenipid/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value",
    offsetof(Parameters_TemplateNIPID, PS3_BT_Power_Value), 31, 1, 2, 86, "", 0
  },

  { 44, "templatenipid/Inputs from LabVIEW/PlayStation3/L2 [-]/Value", offsetof
    (Parameters_TemplateNIPID, L2_Value), 31, 1, 2, 88, "", 0 },

  { 45,
    "templatenipid/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value",
    offsetof(Parameters_TemplateNIPID, PS3_VSP_Speed_Value), 31, 1, 2, 90, "", 0
  },

  { 46, "templatenipid/Inputs from LabVIEW/PlayStation3/R2 [-]/Value", offsetof
    (Parameters_TemplateNIPID, R2_Value), 31, 1, 2, 92, "", 0 },

  { 47, "templatenipid/Inputs from LabVIEW/Setpoint/setpointpsi [deg]/Value",
    offsetof(Parameters_TemplateNIPID, setpointpsideg_Value), 31, 1, 2, 94, "",
    0 },

  { 48,
    "templatenipid/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain), 31, 1, 2, 96, "", 0 },

  { 49, "templatenipid/Inputs from LabVIEW/Setpoint/setpointx [m]/Value",
    offsetof(Parameters_TemplateNIPID, setpointxm_Value), 31, 1, 2, 98, "", 0 },

  { 50, "templatenipid/Inputs from LabVIEW/Setpoint/setpointy [m]/Value",
    offsetof(Parameters_TemplateNIPID, setpointym_Value), 31, 1, 2, 100, "", 0 },

  { 51, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kppsi/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kppsi_Value), 31, 1, 2, 102, "", 0 },

  { 52, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kipsi/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kipsi_Value), 31, 1, 2, 104, "", 0 },

  { 53, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1 Reset Integrator/Value",
    offsetof(Parameters_TemplateNIPID, ctrl1ResetIntegrator_Value), 31, 1, 2,
    106, "", 0 },

  { 54, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kdpsi/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kdpsi_Value), 31, 1, 2, 108, "", 0 },

  { 55, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kdx/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kdx_Value), 31, 1, 2, 110, "", 0 },

  { 56, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kdy/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kdy_Value), 31, 1, 2, 112, "", 0 },

  { 57, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kix/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kix_Value), 31, 1, 2, 114, "", 0 },

  { 58, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kiy/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kiy_Value), 31, 1, 2, 116, "", 0 },

  { 59, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kpx/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kpx_Value), 31, 1, 2, 118, "", 0 },

  { 60, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kpy/Value", offsetof
    (Parameters_TemplateNIPID, ctrl1Kpy_Value), 31, 1, 2, 120, "", 0 },

  { 61, "templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q/12/Value", offsetof
    (Parameters_TemplateNIPID, u_Value), 31, 1, 2, 122, "", 0 },

  { 62, "templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q/21/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_k), 31, 1, 2, 124, "", 0 },

  { 63, "templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q_Surge/Value", offsetof
    (Parameters_TemplateNIPID, Gamma_q_Surge_Value), 31, 1, 2, 126, "", 0 },

  { 64, "templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q_Sway/Value", offsetof
    (Parameters_TemplateNIPID, Gamma_q_Sway_Value), 31, 1, 2, 128, "", 0 },

  { 65, "templatenipid/Inputs from LabVIEW/ctrl2/Initial q_x/Value", offsetof
    (Parameters_TemplateNIPID, Initialq_x_Value), 31, 1, 2, 130, "", 0 },

  { 66, "templatenipid/Inputs from LabVIEW/ctrl2/Initial q_y/Value", offsetof
    (Parameters_TemplateNIPID, Initialq_y_Value), 31, 1, 2, 132, "", 0 },

  { 67, "templatenipid/Inputs from LabVIEW/ctrl2/Initial s/Value", offsetof
    (Parameters_TemplateNIPID, Initials_Value), 31, 1, 2, 134, "", 0 },

  { 68, "templatenipid/Inputs from LabVIEW/ctrl2/K_d/12/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_l), 31, 1, 2, 136, "", 0 },

  { 69, "templatenipid/Inputs from LabVIEW/ctrl2/K_d/13/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_a), 31, 1, 2, 138, "", 0 },

  { 70, "templatenipid/Inputs from LabVIEW/ctrl2/K_d/21/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_c), 31, 1, 2, 140, "", 0 },

  { 71, "templatenipid/Inputs from LabVIEW/ctrl2/K_d/23/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_o), 31, 1, 2, 142, "", 0 },

  { 72, "templatenipid/Inputs from LabVIEW/ctrl2/K_d/31/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_b), 31, 1, 2, 144, "", 0 },

  { 73, "templatenipid/Inputs from LabVIEW/ctrl2/K_d/32/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_f), 31, 1, 2, 146, "", 0 },

  { 74, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kdx/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kdx_Value), 31, 1, 2, 148, "", 0 },

  { 75, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kdy/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kdy_Value), 31, 1, 2, 150, "", 0 },

  { 76, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kdpsi/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kdpsi_Value), 31, 1, 2, 152, "", 0 },

  { 77, "templatenipid/Inputs from LabVIEW/ctrl2/K_i/12/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_lr), 31, 1, 2, 154, "", 0 },

  { 78, "templatenipid/Inputs from LabVIEW/ctrl2/K_i/13/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_j), 31, 1, 2, 156, "", 0 },

  { 79, "templatenipid/Inputs from LabVIEW/ctrl2/K_i/21/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_d), 31, 1, 2, 158, "", 0 },

  { 80, "templatenipid/Inputs from LabVIEW/ctrl2/K_i/23/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_g), 31, 1, 2, 160, "", 0 },

  { 81, "templatenipid/Inputs from LabVIEW/ctrl2/K_i/31/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_n), 31, 1, 2, 162, "", 0 },

  { 82, "templatenipid/Inputs from LabVIEW/ctrl2/K_i/32/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_jc), 31, 1, 2, 164, "", 0 },

  { 83, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kix/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kix_Value), 31, 1, 2, 166, "", 0 },

  { 84, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kiy/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kiy_Value), 31, 1, 2, 168, "", 0 },

  { 85, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kipsi/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kipsi_Value), 31, 1, 2, 170, "", 0 },

  { 86, "templatenipid/Inputs from LabVIEW/ctrl2/K_p/12/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_e), 31, 1, 2, 172, "", 0 },

  { 87, "templatenipid/Inputs from LabVIEW/ctrl2/K_p/13/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_ox), 31, 1, 2, 174, "", 0 },

  { 88, "templatenipid/Inputs from LabVIEW/ctrl2/K_p/21/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_eu), 31, 1, 2, 176, "", 0 },

  { 89, "templatenipid/Inputs from LabVIEW/ctrl2/K_p/23/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_dc), 31, 1, 2, 178, "", 0 },

  { 90, "templatenipid/Inputs from LabVIEW/ctrl2/K_p/31/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_p), 31, 1, 2, 180, "", 0 },

  { 91, "templatenipid/Inputs from LabVIEW/ctrl2/K_p/32/Value", offsetof
    (Parameters_TemplateNIPID, u_Value_bp), 31, 1, 2, 182, "", 0 },

  { 92, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kpx/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kpx_Value), 31, 1, 2, 184, "", 0 },

  { 93, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kpy/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kpy_Value), 31, 1, 2, 186, "", 0 },

  { 94, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kppsi/Value", offsetof
    (Parameters_TemplateNIPID, ctrl2Kppsi_Value), 31, 1, 2, 188, "", 0 },

  { 95, "templatenipid/Inputs from LabVIEW/ctrl2/ctrl2 Reset Integrator/Value",
    offsetof(Parameters_TemplateNIPID, ctrl2ResetIntegrator_Value), 31, 1, 2,
    190, "", 0 },

  { 96, "templatenipid/Inputs from LabVIEW/ctrl2/kappa_1/Value", offsetof
    (Parameters_TemplateNIPID, kappa_1_Value), 31, 1, 2, 192, "", 0 },

  { 97, "templatenipid/Inputs from LabVIEW/ctrl2/lambda_q/Value", offsetof
    (Parameters_TemplateNIPID, lambda_q_Value), 31, 1, 2, 194, "", 0 },

  { 98,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value",
    offsetof(Parameters_TemplateNIPID, l_x1_Value), 31, 1, 2, 196, "", 0 },

  { 99,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain",
    offsetof(Parameters_TemplateNIPID, l_x1_Gain), 31, 1, 2, 198, "", 0 },

  { 100,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value",
    offsetof(Parameters_TemplateNIPID, l_x2_Value), 31, 1, 2, 200, "", 0 },

  { 101,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain",
    offsetof(Parameters_TemplateNIPID, l_x2_Gain), 31, 1, 2, 202, "", 0 },

  { 102,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value",
    offsetof(Parameters_TemplateNIPID, l_y2_Value), 31, 1, 2, 204, "", 0 },

  { 103,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain",
    offsetof(Parameters_TemplateNIPID, l_y2_Gain), 31, 1, 2, 206, "", 0 },

  { 104,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value",
    offsetof(Parameters_TemplateNIPID, B_11_Value), 31, 1, 2, 208, "", 0 },

  { 105,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value",
    offsetof(Parameters_TemplateNIPID, B_21_Value), 31, 1, 2, 210, "", 0 },

  { 106,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value",
    offsetof(Parameters_TemplateNIPID, l_y1_Value), 31, 1, 2, 212, "", 0 },

  { 107,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value",
    offsetof(Parameters_TemplateNIPID, B_12_Value), 31, 1, 2, 214, "", 0 },

  { 108,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value",
    offsetof(Parameters_TemplateNIPID, B_22_Value), 31, 1, 2, 216, "", 0 },

  { 109,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value",
    offsetof(Parameters_TemplateNIPID, B_13_Value), 31, 1, 2, 218, "", 0 },

  { 110,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value",
    offsetof(Parameters_TemplateNIPID, B_23_Value), 31, 1, 2, 220, "", 0 },

  { 111,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value",
    offsetof(Parameters_TemplateNIPID, B_14_Value), 31, 1, 2, 222, "", 0 },

  { 112,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value",
    offsetof(Parameters_TemplateNIPID, B_24_Value), 31, 1, 2, 224, "", 0 },

  { 113,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value",
    offsetof(Parameters_TemplateNIPID, B_15_Value), 31, 1, 2, 226, "", 0 },

  { 114,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value",
    offsetof(Parameters_TemplateNIPID, B_25_Value), 31, 1, 2, 228, "", 0 },

  { 115,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value",
    offsetof(Parameters_TemplateNIPID, l_x3_Value), 31, 1, 2, 230, "", 0 },

  { 116,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value",
    offsetof(Parameters_TemplateNIPID, N_r_Value), 31, 1, 2, 232, "", 0 },

  { 117,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain",
    offsetof(Parameters_TemplateNIPID, N_r_Gain), 31, 1, 2, 234, "", 0 },

  { 118,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value",
    offsetof(Parameters_TemplateNIPID, N_v_Value), 31, 1, 2, 236, "", 0 },

  { 119,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain",
    offsetof(Parameters_TemplateNIPID, N_v_Gain), 31, 1, 2, 238, "", 0 },

  { 120,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value",
    offsetof(Parameters_TemplateNIPID, X_u_Value), 31, 1, 2, 240, "", 0 },

  { 121,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain",
    offsetof(Parameters_TemplateNIPID, X_u_Gain), 31, 1, 2, 242, "", 0 },

  { 122,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value",
    offsetof(Parameters_TemplateNIPID, Y_v_Value), 31, 1, 2, 244, "", 0 },

  { 123,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain",
    offsetof(Parameters_TemplateNIPID, Y_v_Gain), 31, 1, 2, 246, "", 0 },

  { 124,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value",
    offsetof(Parameters_TemplateNIPID, Y_r_Value), 31, 1, 2, 248, "", 0 },

  { 125,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain",
    offsetof(Parameters_TemplateNIPID, Y_vr_Gain), 31, 1, 2, 250, "", 0 },

  { 126,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value",
    offsetof(Parameters_TemplateNIPID, D_L_12_Value), 31, 1, 2, 252, "", 0 },

  { 127,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value",
    offsetof(Parameters_TemplateNIPID, D_L_13_Value), 31, 1, 2, 254, "", 0 },

  { 128,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value",
    offsetof(Parameters_TemplateNIPID, D_L_21_Value), 31, 1, 2, 256, "", 0 },

  { 129,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value",
    offsetof(Parameters_TemplateNIPID, D_L_31_Value), 31, 1, 2, 258, "", 0 },

  { 130,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value",
    offsetof(Parameters_TemplateNIPID, m_Value), 31, 1, 2, 260, "", 0 },

  { 131,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value",
    offsetof(Parameters_TemplateNIPID, X_udot_Value), 31, 1, 2, 262, "", 0 },

  { 132,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value",
    offsetof(Parameters_TemplateNIPID, M_21_Value), 31, 1, 2, 264, "", 0 },

  { 133,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value",
    offsetof(Parameters_TemplateNIPID, M_31_Value), 31, 1, 2, 266, "", 0 },

  { 134,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value",
    offsetof(Parameters_TemplateNIPID, M_12_Value), 31, 1, 2, 268, "", 0 },

  { 135,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value",
    offsetof(Parameters_TemplateNIPID, Y_vdot_Value), 31, 1, 2, 270, "", 0 },

  { 136,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value",
    offsetof(Parameters_TemplateNIPID, x_g_Value), 31, 1, 2, 272, "", 0 },

  { 137,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value",
    offsetof(Parameters_TemplateNIPID, N_vdot_Value), 31, 1, 2, 274, "", 0 },

  { 138,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value",
    offsetof(Parameters_TemplateNIPID, M_13_Value), 31, 1, 2, 276, "", 0 },

  { 139,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value",
    offsetof(Parameters_TemplateNIPID, Y_rdot_Value), 31, 1, 2, 278, "", 0 },

  { 140,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value",
    offsetof(Parameters_TemplateNIPID, I_z_Value), 31, 1, 2, 280, "", 0 },

  { 141,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value",
    offsetof(Parameters_TemplateNIPID, N_rdot_Value), 31, 1, 2, 282, "", 0 },

  { 142,
    "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain",
    offsetof(Parameters_TemplateNIPID, PS3u_1_Gain), 31, 1, 2, 284, "", 0 },

  { 143,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_1tof_1_XData), 71, 39, 2, 286, "", 0 },

  { 144,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table",
    offsetof(Parameters_TemplateNIPID, u_1tof_1_YData), 71, 39, 2, 288, "", 0 },

  { 145,
    "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain",
    offsetof(Parameters_TemplateNIPID, PS3u_2_Gain), 31, 1, 2, 290, "", 0 },

  { 146,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value), 31, 1, 2, 292, "", 0 },

  { 147,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_l), 31, 1, 2, 294, "", 0 },

  { 148,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_m), 31, 1, 2, 296, "", 0 },

  { 149,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_p), 31, 1, 2, 298, "", 0 },

  { 150,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues",
    offsetof(Parameters_TemplateNIPID, u_205_XData), 72, 11, 2, 300, "", 0 },

  { 151,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table",
    offsetof(Parameters_TemplateNIPID, u_205_YData), 72, 11, 2, 302, "", 0 },

  { 152,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues",
    offsetof(Parameters_TemplateNIPID, u_201u_202_XData), 28, 3, 2, 304, "", 0 },

  { 153,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table",
    offsetof(Parameters_TemplateNIPID, u_201u_202_YData), 28, 3, 2, 306, "", 0 },

  { 154,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_20_XData), 73, 18, 2, 308, "", 0 },

  { 155,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table",
    offsetof(Parameters_TemplateNIPID, u_20_YData), 73, 18, 2, 310, "", 0 },

  { 156,
    "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain",
    offsetof(Parameters_TemplateNIPID, PS3u_3_Gain), 31, 1, 2, 312, "", 0 },

  { 157,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues",
    offsetof(Parameters_TemplateNIPID, u_3tof_3_XData), 71, 39, 2, 314, "", 0 },

  { 158,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table",
    offsetof(Parameters_TemplateNIPID, u_3tof_3_YData), 71, 39, 2, 316, "", 0 },

  { 159,
    "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain",
    offsetof(Parameters_TemplateNIPID, PS3u_4_Gain), 31, 1, 2, 318, "", 0 },

  { 160,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_m0), 31, 1, 2, 320, "", 0
  },

  { 161,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_k), 31, 1, 2, 322, "", 0 },

  { 162,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_401_XData), 74, 15, 2, 324, "", 0 },

  { 163,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table",
    offsetof(Parameters_TemplateNIPID, u_401_YData), 74, 15, 2, 326, "", 0 },

  { 164,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_401_XData_c), 75, 13, 2, 328, "", 0 },

  { 165,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table",
    offsetof(Parameters_TemplateNIPID, u_401_YData_e), 75, 13, 2, 330, "", 0 },

  { 166,
    "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain",
    offsetof(Parameters_TemplateNIPID, PS3u_5_Gain), 31, 1, 2, 332, "", 0 },

  { 167,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_TemplateNIPID, DeadZone001_Start), 31, 1, 2, 334, "", 0
  },

  { 168,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_TemplateNIPID, DeadZone001_End), 31, 1, 2, 336, "", 0 },

  { 169,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_f), 31, 1, 2, 338, "", 0 },

  { 170,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_c), 31, 1, 2, 340, "", 0 },

  { 171,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_50_XData), 76, 10, 2, 342, "", 0 },

  { 172,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table",
    offsetof(Parameters_TemplateNIPID, u_50_YData), 76, 10, 2, 344, "", 0 },

  { 173,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value",
    offsetof(Parameters_TemplateNIPID, u_50_Value), 31, 1, 2, 346, "", 0 },

  { 174,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_50_XData_j), 76, 10, 2, 348, "", 0 },

  { 175,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table",
    offsetof(Parameters_TemplateNIPID, u_50_YData_g), 76, 10, 2, 350, "", 0 },

  { 176,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_1tof_1_XData_o), 71, 39, 2, 352, "", 0
  },

  { 177,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table",
    offsetof(Parameters_TemplateNIPID, u_1tof_1_YData_i), 71, 39, 2, 354, "", 0
  },

  { 178,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_o), 31, 1, 2, 356, "", 0 },

  { 179,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_a), 31, 1, 2, 358, "", 0 },

  { 180,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_f5), 31, 1, 2, 360, "", 0
  },

  { 181,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_pu), 31, 1, 2, 362, "", 0
  },

  { 182,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues",
    offsetof(Parameters_TemplateNIPID, u_205_XData_c), 72, 11, 2, 364, "", 0 },

  { 183,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table",
    offsetof(Parameters_TemplateNIPID, u_205_YData_e), 72, 11, 2, 366, "", 0 },

  { 184,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues",
    offsetof(Parameters_TemplateNIPID, u_201u_202_XData_k), 28, 3, 2, 368, "", 0
  },

  { 185,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table",
    offsetof(Parameters_TemplateNIPID, u_201u_202_YData_f), 28, 3, 2, 370, "", 0
  },

  { 186,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_20_XData_i), 73, 18, 2, 372, "", 0 },

  { 187,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table",
    offsetof(Parameters_TemplateNIPID, u_20_YData_j), 73, 18, 2, 374, "", 0 },

  { 188,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues",
    offsetof(Parameters_TemplateNIPID, u_3tof_3_XData_g), 71, 39, 2, 376, "", 0
  },

  { 189,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table",
    offsetof(Parameters_TemplateNIPID, u_3tof_3_YData_h), 71, 39, 2, 378, "", 0
  },

  { 190,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_ap), 31, 1, 2, 380, "", 0
  },

  { 191,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_lg), 31, 1, 2, 382, "", 0
  },

  { 192,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_401_XData_n), 74, 15, 2, 384, "", 0 },

  { 193,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table",
    offsetof(Parameters_TemplateNIPID, u_401_YData_d), 74, 15, 2, 386, "", 0 },

  { 194,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_401_XData_g), 75, 13, 2, 388, "", 0 },

  { 195,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table",
    offsetof(Parameters_TemplateNIPID, u_401_YData_b), 75, 13, 2, 390, "", 0 },

  { 196,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_TemplateNIPID, DeadZone001_Start_p), 31, 1, 2, 392, "",
    0 },

  { 197,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_TemplateNIPID, DeadZone001_End_k), 31, 1, 2, 394, "", 0
  },

  { 198,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_b), 31, 1, 2, 396, "", 0 },

  { 199,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_j), 31, 1, 2, 398, "", 0 },

  { 200,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_50_XData_l), 76, 10, 2, 400, "", 0 },

  { 201,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table",
    offsetof(Parameters_TemplateNIPID, u_50_YData_c), 76, 10, 2, 402, "", 0 },

  { 202,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value",
    offsetof(Parameters_TemplateNIPID, u_50_Value_n), 31, 1, 2, 404, "", 0 },

  { 203,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_50_XData_c), 76, 10, 2, 406, "", 0 },

  { 204,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table",
    offsetof(Parameters_TemplateNIPID, u_50_YData_j), 76, 10, 2, 408, "", 0 },

  { 205,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn3xcoordmm_Gain), 31, 1, 2, 410, "",
    0 },

  { 206, "templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain",
    offsetof(Parameters_TemplateNIPID, mm2mx_Gain), 31, 1, 2, 412, "", 0 },

  { 207,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn4ycoordmm_Gain), 31, 1, 2, 414, "",
    0 },

  { 208, "templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain",
    offsetof(Parameters_TemplateNIPID, mm2my_Gain), 31, 1, 2, 416, "", 0 },

  { 209,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn6yawdeg_Gain), 31, 1, 2, 418, "", 0
  },

  { 210, "templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain",
    offsetof(Parameters_TemplateNIPID, d2ryaw_Gain), 31, 1, 2, 420, "", 0 },

  { 211, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R31/Value",
    offsetof(Parameters_TemplateNIPID, R31_Value), 31, 1, 2, 422, "", 0 },

  { 212, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/-1/Gain",
    offsetof(Parameters_TemplateNIPID, u_Gain), 31, 1, 2, 424, "", 0 },

  { 213, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R32/Value",
    offsetof(Parameters_TemplateNIPID, R32_Value), 31, 1, 2, 426, "", 0 },

  { 214, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R13/Value",
    offsetof(Parameters_TemplateNIPID, R13_Value), 31, 1, 2, 428, "", 0 },

  { 215, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R23/Value",
    offsetof(Parameters_TemplateNIPID, R23_Value), 31, 1, 2, 430, "", 0 },

  { 216, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R33/Value",
    offsetof(Parameters_TemplateNIPID, R33_Value), 31, 1, 2, 432, "", 0 },

  { 217,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat), 31, 1, 2, 434, "",
    0 },

  { 218,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat), 31, 1, 2, 436, "",
    0 },

  { 219,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain), 31, 1, 2, 438, "", 0 },

  { 220,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_lo), 31, 1, 2, 440, "", 0
  },

  { 221,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_e), 31, 1, 2, 442, "",
    0 },

  { 222,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_b), 31, 1, 2, 444, "",
    0 },

  { 223,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_l), 31, 1, 2, 446, "", 0 },

  { 224,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_lv), 31, 1, 2, 448, "", 0
  },

  { 225,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_d), 31, 1, 2, 450, "",
    0 },

  { 226,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_e), 31, 1, 2, 452, "",
    0 },

  { 227,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_f), 31, 1, 2, 454, "", 0 },

  { 228,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_a5), 31, 1, 2, 456, "", 0
  },

  { 229,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_j), 31, 1, 2, 458, "",
    0 },

  { 230,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_d), 31, 1, 2, 460, "",
    0 },

  { 231,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_p), 31, 1, 2, 462, "", 0 },

  { 232,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_md), 31, 1, 2, 464, "", 0
  },

  { 233,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_i), 31, 1, 2, 466, "", 0 },

  { 234,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_m), 31, 1, 2, 468, "",
    0 },

  { 235,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_c), 31, 1, 2, 470, "",
    0 },

  { 236,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_o), 31, 1, 2, 472, "", 0 },

  { 237,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_ic), 31, 1, 2, 474, "", 0
  },

  { 238,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_k), 31, 1, 2, 476, "",
    0 },

  { 239,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_p), 31, 1, 2, 478, "",
    0 },

  { 240,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_b), 31, 1, 2, 480, "", 0 },

  { 241,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_l2), 31, 1, 2, 482, "", 0
  },

  { 242,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_b), 31, 1, 2, 484, "",
    0 },

  { 243,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_g), 31, 1, 2, 486, "",
    0 },

  { 244,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_ff), 31, 1, 2, 488, "", 0 },

  { 245,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_cb), 31, 1, 2, 490, "", 0
  },

  { 246,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_fj), 31, 1, 2, 492, "", 0 },

  { 247,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/zeta/Integrator/InitialCondition",
    offsetof(Parameters_TemplateNIPID, Integrator_IC), 28, 3, 2, 494, "", 0 },

  { 248,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_c), 31, 1, 2, 496, "", 0 },

  { 249,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4/InitialCondition",
    offsetof(Parameters_TemplateNIPID, Integrator4_IC), 31, 1, 2, 498, "", 0 },

  { 250,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain",
    offsetof(Parameters_TemplateNIPID, u_Gain_i), 31, 1, 2, 500, "", 0 },

  { 251,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_TemplateNIPID, _2x1_Value), 32, 2, 2, 502, "", 0 },

  { 252,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value",
    offsetof(Parameters_TemplateNIPID, _2x1_Value_a), 32, 2, 2, 504, "", 0 },

  { 253,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_fv), 31, 1, 2, 506, "", 0 },

  { 254,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_f), 31, 1, 2, 508, "", 0 },

  { 255,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_b0), 31, 1, 2, 510, "", 0
  },

  { 256,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_e), 31, 1, 2, 512, "", 0 },

  { 257,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_h), 31, 1, 2, 514, "", 0 },

  { 258,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain2/Gain",
    offsetof(Parameters_TemplateNIPID, Gain2_Gain), 31, 1, 2, 516, "", 0 },

  { 259,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_j), 31, 1, 2, 518, "", 0 },

  { 260,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain",
    offsetof(Parameters_TemplateNIPID, _Gain), 31, 1, 2, 520, "", 0 },

  { 261,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value",
    offsetof(Parameters_TemplateNIPID, _2x2_Value), 22, 4, 2, 522, "", 0 },

  { 262,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_TemplateNIPID, _2x2_Value_n), 22, 4, 2, 524, "", 0 },

  { 263,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain",
    offsetof(Parameters_TemplateNIPID, _Gain_d), 31, 1, 2, 526, "", 0 },

  { 264,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value",
    offsetof(Parameters_TemplateNIPID, u_Value_pg), 31, 1, 2, 528, "", 0 },

  { 265,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_g), 31, 1, 2, 530, "", 0 },

  { 266,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator2/InitialCondition",
    offsetof(Parameters_TemplateNIPID, Integrator2_IC), 31, 1, 2, 532, "", 0 },

  { 267,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_gn), 31, 1, 2, 534, "", 0 },

  { 268,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_TemplateNIPID, _2x1_Value_a2), 32, 2, 2, 536, "", 0 },

  { 269,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_mz), 31, 1, 2, 538, "", 0
  },

  { 270,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_e), 31, 1, 2, 540, "", 0 },

  { 271,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_h), 31, 1, 2, 542, "", 0 },

  { 272,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain",
    offsetof(Parameters_TemplateNIPID, u_Gain_k), 31, 1, 2, 544, "", 0 },

  { 273,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain",
    offsetof(Parameters_TemplateNIPID, _Gain_e), 31, 1, 2, 546, "", 0 },

  { 274,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain",
    offsetof(Parameters_TemplateNIPID, _Gain_n), 31, 1, 2, 548, "", 0 },

  { 275,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_gp), 31, 1, 2, 550, "", 0 },

  { 276,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_n), 31, 1, 2, 552, "", 0 },

  { 277,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_jq), 31, 1, 2, 554, "", 0 },

  { 278,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value",
    offsetof(Parameters_TemplateNIPID, u_Value_ez), 31, 1, 2, 556, "", 0 },

  { 279,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_mj), 31, 1, 2, 558, "", 0
  },

  { 280,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_TemplateNIPID, _2x1_Value_c), 32, 2, 2, 560, "", 0 },

  { 281,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S11/Value",
    offsetof(Parameters_TemplateNIPID, S11_Value), 31, 1, 2, 562, "", 0 },

  { 282,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/R31/Value",
    offsetof(Parameters_TemplateNIPID, R31_Value_e), 31, 1, 2, 564, "", 0 },

  { 283,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S12/Gain",
    offsetof(Parameters_TemplateNIPID, S12_Gain), 31, 1, 2, 566, "", 0 },

  { 284,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S22/Value",
    offsetof(Parameters_TemplateNIPID, S22_Value), 31, 1, 2, 568, "", 0 },

  { 285,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S32/Value",
    offsetof(Parameters_TemplateNIPID, S32_Value), 31, 1, 2, 570, "", 0 },

  { 286,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S13/Value",
    offsetof(Parameters_TemplateNIPID, S13_Value), 31, 1, 2, 572, "", 0 },

  { 287,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S23/Value",
    offsetof(Parameters_TemplateNIPID, S23_Value), 31, 1, 2, 574, "", 0 },

  { 288,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S33/Value",
    offsetof(Parameters_TemplateNIPID, S33_Value), 31, 1, 2, 576, "", 0 },

  { 289,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_h2), 31, 1, 2, 578, "", 0 },

  { 290,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_pe), 22, 4, 2, 580, "", 0
  },

  { 291,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_px), 31, 1, 2, 582, "", 0 },

  { 292,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues",
    offsetof(Parameters_TemplateNIPID, f_1tou_1_XData), 71, 39, 2, 584, "", 0 },

  { 293,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table",
    offsetof(Parameters_TemplateNIPID, f_1tou_1_YData), 71, 39, 2, 586, "", 0 },

  { 294,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_pj), 31, 1, 2, 588, "", 0
  },

  { 295,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_h5), 31, 1, 2, 590, "", 0
  },

  { 296,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_cy), 31, 1, 2, 592, "", 0
  },

  { 297,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_fy), 31, 1, 2, 594, "", 0
  },

  { 298,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues",
    offsetof(Parameters_TemplateNIPID, f_2000391_XData), 72, 11, 2, 596, "", 0 },

  { 299,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table",
    offsetof(Parameters_TemplateNIPID, f_2000391_YData), 72, 11, 2, 598, "", 0 },

  { 300,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues",
    offsetof(Parameters_TemplateNIPID, f_2006731f_2000391_XData), 28, 3, 2, 600,
    "", 0 },

  { 301,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table",
    offsetof(Parameters_TemplateNIPID, f_2006731f_2000391_YData), 28, 3, 2, 602,
    "", 0 },

  { 302,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues",
    offsetof(Parameters_TemplateNIPID, f_2006731_XData), 73, 18, 2, 604, "", 0 },

  { 303,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table",
    offsetof(Parameters_TemplateNIPID, f_2006731_YData), 73, 18, 2, 606, "", 0 },

  { 304,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues",
    offsetof(Parameters_TemplateNIPID, f_3tou_3_XData), 71, 39, 2, 608, "", 0 },

  { 305,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table",
    offsetof(Parameters_TemplateNIPID, f_3tou_3_YData), 71, 39, 2, 610, "", 0 },

  { 306,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_hw), 31, 1, 2, 612, "", 0
  },

  { 307,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_l5), 31, 1, 2, 614, "", 0
  },

  { 308,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues",
    offsetof(Parameters_TemplateNIPID, f_400451_XData), 74, 15, 2, 616, "", 0 },

  { 309,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table",
    offsetof(Parameters_TemplateNIPID, f_400451_YData), 74, 15, 2, 618, "", 0 },

  { 310,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues",
    offsetof(Parameters_TemplateNIPID, f_400451_XData_m), 75, 13, 2, 620, "", 0
  },

  { 311,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table",
    offsetof(Parameters_TemplateNIPID, f_400451_YData_n), 75, 13, 2, 622, "", 0
  },

  { 312,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_TemplateNIPID, DeadZone001_Start_i), 31, 1, 2, 624, "",
    0 },

  { 313,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_TemplateNIPID, DeadZone001_End_h), 31, 1, 2, 626, "", 0
  },

  { 314,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_kt), 31, 1, 2, 628, "", 0
  },

  { 315,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_mp), 31, 1, 2, 630, "", 0
  },

  { 316,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues",
    offsetof(Parameters_TemplateNIPID, f_50_XData), 76, 10, 2, 632, "", 0 },

  { 317,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table",
    offsetof(Parameters_TemplateNIPID, f_50_YData), 76, 10, 2, 634, "", 0 },

  { 318,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value",
    offsetof(Parameters_TemplateNIPID, f_50_Value), 31, 1, 2, 636, "", 0 },

  { 319,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues",
    offsetof(Parameters_TemplateNIPID, f_50_XData_i), 76, 10, 2, 638, "", 0 },

  { 320,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table",
    offsetof(Parameters_TemplateNIPID, f_50_YData_l), 76, 10, 2, 640, "", 0 },

  { 321,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value",
    offsetof(Parameters_TemplateNIPID, BT_power_limit_Value), 31, 1, 2, 642, "",
    0 },

  { 322,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value",
    offsetof(Parameters_TemplateNIPID, VSP_speeds_Value), 31, 1, 2, 644, "", 0 },

  { 323,
    "templatenipid/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_p), 31, 1, 2, 646, "",
    0 },

  { 324,
    "templatenipid/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_i), 31, 1, 2, 648, "",
    0 },

  { 325,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn2Error_Gain), 31, 1, 2, 650, "", 0 },

  { 326,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn9Residual_Gain), 31, 1, 2, 652, "",
    0 },

  { 327,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value",
    offsetof(Parameters_TemplateNIPID, _2x1_Value_d), 32, 2, 2, 654, "", 0 },

  { 328,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Constant1/Value",
    offsetof(Parameters_TemplateNIPID, Constant1_Value), 24, 9, 2, 656, "", 0 },

  { 329,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn5zcoordmm_Gain), 31, 1, 2, 658, "",
    0 },

  { 330, "templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain",
    offsetof(Parameters_TemplateNIPID, mm2mz_Gain), 31, 1, 2, 660, "", 0 },

  { 331,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn8rolldeg_Gain), 31, 1, 2, 662, "", 0
  },

  { 332,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain",
    offsetof(Parameters_TemplateNIPID, d2rroll_Gain), 31, 1, 2, 664, "", 0 },

  { 333,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn7pitchdeg_Gain), 31, 1, 2, 666, "",
    0 },

  { 334,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain",
    offsetof(Parameters_TemplateNIPID, d2rpitch_Gain), 31, 1, 2, 668, "", 0 },

  { 335,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN/Gain",
    offsetof(Parameters_TemplateNIPID, QTMIn1FN_Gain), 31, 1, 2, 670, "", 0 },

  { 336,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3/InitialCondition",
    offsetof(Parameters_TemplateNIPID, Integrator3_IC), 31, 1, 2, 672, "", 0 },

  { 337,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_dx), 31, 1, 2, 674,
    "", 0 },

  { 338,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_gr), 31, 1, 2, 676,
    "", 0 },

  { 339,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_p1), 31, 1, 2, 678, "", 0 },

  { 340,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_ol), 31, 1, 2, 680, "", 0
  },

  { 341,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_eu), 31, 1, 2, 682,
    "", 0 },

  { 342,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_l), 31, 1, 2, 684, "",
    0 },

  { 343,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_c), 31, 1, 2, 686, "", 0 },

  { 344,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_g), 31, 1, 2, 688, "", 0 },

  { 345,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2/Gain",
    offsetof(Parameters_TemplateNIPID, K2_Gain), 24, 9, 2, 690, "", 0 },

  { 346,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3/Gain",
    offsetof(Parameters_TemplateNIPID, K3_Gain), 24, 9, 2, 692, "", 0 },

  { 347,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4/Gain",
    offsetof(Parameters_TemplateNIPID, K4_Gain), 24, 9, 2, 694, "", 0 },

  { 348,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_1tof_1_XData_b), 71, 39, 2, 696, "", 0
  },

  { 349,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table",
    offsetof(Parameters_TemplateNIPID, u_1tof_1_YData_l), 71, 39, 2, 698, "", 0
  },

  { 350,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_ex), 31, 1, 2, 700, "", 0
  },

  { 351,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_fk), 31, 1, 2, 702, "", 0
  },

  { 352,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_lt), 31, 1, 2, 704, "", 0
  },

  { 353,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_h2), 31, 1, 2, 706, "", 0
  },

  { 354,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues",
    offsetof(Parameters_TemplateNIPID, u_205_XData_h), 72, 11, 2, 708, "", 0 },

  { 355,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table",
    offsetof(Parameters_TemplateNIPID, u_205_YData_l), 72, 11, 2, 710, "", 0 },

  { 356,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues",
    offsetof(Parameters_TemplateNIPID, u_201u_202_XData_m), 28, 3, 2, 712, "", 0
  },

  { 357,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table",
    offsetof(Parameters_TemplateNIPID, u_201u_202_YData_i), 28, 3, 2, 714, "", 0
  },

  { 358,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_20_XData_b), 73, 18, 2, 716, "", 0 },

  { 359,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table",
    offsetof(Parameters_TemplateNIPID, u_20_YData_e), 73, 18, 2, 718, "", 0 },

  { 360,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues",
    offsetof(Parameters_TemplateNIPID, u_3tof_3_XData_h), 71, 39, 2, 720, "", 0
  },

  { 361,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table",
    offsetof(Parameters_TemplateNIPID, u_3tof_3_YData_b), 71, 39, 2, 722, "", 0
  },

  { 362,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_li), 31, 1, 2, 724, "", 0
  },

  { 363,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_of), 31, 1, 2, 726, "", 0
  },

  { 364,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_401_XData_m), 74, 15, 2, 728, "", 0 },

  { 365,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table",
    offsetof(Parameters_TemplateNIPID, u_401_YData_p), 74, 15, 2, 730, "", 0 },

  { 366,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues",
    offsetof(Parameters_TemplateNIPID, u_401_XData_e), 75, 13, 2, 732, "", 0 },

  { 367,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table",
    offsetof(Parameters_TemplateNIPID, u_401_YData_ec), 75, 13, 2, 734, "", 0 },

  { 368,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_TemplateNIPID, DeadZone001_Start_f), 31, 1, 2, 736, "",
    0 },

  { 369,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_TemplateNIPID, DeadZone001_End_e), 31, 1, 2, 738, "", 0
  },

  { 370,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_pp), 31, 1, 2, 740, "", 0
  },

  { 371,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_ab), 31, 1, 2, 742, "", 0
  },

  { 372,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_50_XData_e), 76, 10, 2, 744, "", 0 },

  { 373,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table",
    offsetof(Parameters_TemplateNIPID, u_50_YData_ca), 76, 10, 2, 746, "", 0 },

  { 374,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value",
    offsetof(Parameters_TemplateNIPID, u_50_Value_p), 31, 1, 2, 748, "", 0 },

  { 375,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues",
    offsetof(Parameters_TemplateNIPID, u_50_XData_ly), 76, 10, 2, 750, "", 0 },

  { 376,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table",
    offsetof(Parameters_TemplateNIPID, u_50_YData_a), 76, 10, 2, 752, "", 0 },

  { 377,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)/Gain",
    offsetof(Parameters_TemplateNIPID, invT_b_Gain), 24, 9, 2, 754, "", 0 },

  { 378, "templatenipid/Main Subsystems/Plant/saturation/Saturation/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_UpperSat_l), 31, 1, 2, 756, "",
    0 },

  { 379, "templatenipid/Main Subsystems/Plant/saturation/Saturation/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation_LowerSat_ig), 31, 1, 2, 758,
    "", 0 },

  { 380, "templatenipid/Main Subsystems/Plant/saturation/Saturation1/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation1_UpperSat), 31, 1, 2, 760, "",
    0 },

  { 381, "templatenipid/Main Subsystems/Plant/saturation/Saturation1/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation1_LowerSat), 31, 1, 2, 762, "",
    0 },

  { 382, "templatenipid/Main Subsystems/Plant/saturation/Saturation2/UpperLimit",
    offsetof(Parameters_TemplateNIPID, Saturation2_UpperSat), 31, 1, 2, 764, "",
    0 },

  { 383, "templatenipid/Main Subsystems/Plant/saturation/Saturation2/LowerLimit",
    offsetof(Parameters_TemplateNIPID, Saturation2_LowerSat), 31, 1, 2, 766, "",
    0 },

  { 384, "templatenipid/Main Subsystems/Plant/saturation/plant tau_surge/Gain",
    offsetof(Parameters_TemplateNIPID, planttau_surge_Gain), 31, 1, 2, 768, "",
    0 },

  { 385, "templatenipid/Main Subsystems/Plant/saturation/plant tau_sway/Gain",
    offsetof(Parameters_TemplateNIPID, planttau_sway_Gain), 31, 1, 2, 770, "", 0
  },

  { 386, "templatenipid/Main Subsystems/Plant/saturation/plant tau_yaw/Gain",
    offsetof(Parameters_TemplateNIPID, planttau_yaw_Gain), 31, 1, 2, 772, "", 0
  },

  { 387,
    "templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain",
    offsetof(Parameters_TemplateNIPID, BatteryBowThruster_Gain), 31, 1, 2, 774,
    "", 0 },

  { 388, "templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain",
    offsetof(Parameters_TemplateNIPID, BatteryMain_Gain), 31, 1, 2, 776, "", 0 },

  { 389, "templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain",
    offsetof(Parameters_TemplateNIPID, BatteryServo_Gain), 31, 1, 2, 778, "", 0
  },

  { 390, "templatenipid/Outputs to LabVIEW/Command/tau1/Gain", offsetof
    (Parameters_TemplateNIPID, tau1_Gain), 31, 1, 2, 780, "", 0 },

  { 391, "templatenipid/Outputs to LabVIEW/Command/tau2/Gain", offsetof
    (Parameters_TemplateNIPID, tau2_Gain), 31, 1, 2, 782, "", 0 },

  { 392, "templatenipid/Outputs to LabVIEW/Command/tau3/Gain", offsetof
    (Parameters_TemplateNIPID, tau3_Gain), 31, 1, 2, 784, "", 0 },

  { 393, "templatenipid/Outputs to LabVIEW/Command/tau4/Gain", offsetof
    (Parameters_TemplateNIPID, tau4_Gain), 31, 1, 2, 786, "", 0 },

  { 394, "templatenipid/Outputs to LabVIEW/Command/tau5/Gain", offsetof
    (Parameters_TemplateNIPID, tau5_Gain), 31, 1, 2, 788, "", 0 },

  { 395, "templatenipid/Outputs to LabVIEW/Command/tau6/Gain", offsetof
    (Parameters_TemplateNIPID, tau6_Gain), 31, 1, 2, 790, "", 0 },

  { 396, "templatenipid/Outputs to LabVIEW/Command/plant BT power/Gain",
    offsetof(Parameters_TemplateNIPID, plantBTpower_Gain), 31, 1, 2, 792, "", 0
  },

  { 397, "templatenipid/Outputs to LabVIEW/Command/plant VSP speed/Gain",
    offsetof(Parameters_TemplateNIPID, plantVSPspeed_Gain), 31, 1, 2, 794, "", 0
  },

  { 398, "templatenipid/Outputs to LabVIEW/Command/plant u_1/Gain", offsetof
    (Parameters_TemplateNIPID, plantu_1_Gain), 31, 1, 2, 796, "", 0 },

  { 399, "templatenipid/Outputs to LabVIEW/Command/plant u_2/Gain", offsetof
    (Parameters_TemplateNIPID, plantu_2_Gain), 31, 1, 2, 798, "", 0 },

  { 400, "templatenipid/Outputs to LabVIEW/Command/plant u_3/Gain", offsetof
    (Parameters_TemplateNIPID, plantu_3_Gain), 31, 1, 2, 800, "", 0 },

  { 401, "templatenipid/Outputs to LabVIEW/Command/plant u_4/Gain", offsetof
    (Parameters_TemplateNIPID, plantu_4_Gain), 31, 1, 2, 802, "", 0 },

  { 402, "templatenipid/Outputs to LabVIEW/Command/plant u_5/Gain", offsetof
    (Parameters_TemplateNIPID, plantu_5_Gain), 31, 1, 2, 804, "", 0 },

  { 403, "templatenipid/Outputs to LabVIEW/Command/fact1/Gain", offsetof
    (Parameters_TemplateNIPID, fact1_Gain), 31, 1, 2, 806, "", 0 },

  { 404, "templatenipid/Outputs to LabVIEW/Command/fact2/Gain", offsetof
    (Parameters_TemplateNIPID, fact2_Gain), 31, 1, 2, 808, "", 0 },

  { 405, "templatenipid/Outputs to LabVIEW/Command/fact3/Gain", offsetof
    (Parameters_TemplateNIPID, fact3_Gain), 31, 1, 2, 810, "", 0 },

  { 406, "templatenipid/Outputs to LabVIEW/Command/fact4/Gain", offsetof
    (Parameters_TemplateNIPID, fact4_Gain), 31, 1, 2, 812, "", 0 },

  { 407, "templatenipid/Outputs to LabVIEW/Command/fact5/Gain", offsetof
    (Parameters_TemplateNIPID, fact5_Gain), 31, 1, 2, 814, "", 0 },

  { 408, "templatenipid/Outputs to LabVIEW/Command/taux/Gain", offsetof
    (Parameters_TemplateNIPID, taux_Gain), 31, 1, 2, 816, "", 0 },

  { 409, "templatenipid/Outputs to LabVIEW/Command/tauy/Gain", offsetof
    (Parameters_TemplateNIPID, tauy_Gain), 31, 1, 2, 818, "", 0 },

  { 410, "templatenipid/Outputs to LabVIEW/Command/tauyaw/Gain", offsetof
    (Parameters_TemplateNIPID, tauyaw_Gain), 31, 1, 2, 820, "", 0 },

  { 411, "templatenipid/Outputs to LabVIEW/Command/omega_qy/Gain", offsetof
    (Parameters_TemplateNIPID, omega_qy_Gain), 31, 1, 2, 822, "", 0 },

  { 412, "templatenipid/Outputs to LabVIEW/Command/omegaqx/Gain", offsetof
    (Parameters_TemplateNIPID, omegaqx_Gain), 31, 1, 2, 824, "", 0 },

  { 413, "templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain",
    offsetof(Parameters_TemplateNIPID, CSE1_rdegs_Gain), 31, 1, 2, 826, "", 0 },

  { 414, "templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain",
    offsetof(Parameters_TemplateNIPID, CSE1_ums_Gain), 31, 1, 2, 828, "", 0 },

  { 415, "templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain",
    offsetof(Parameters_TemplateNIPID, CSE1_vms_Gain), 31, 1, 2, 830, "", 0 },

  { 416, "templatenipid/Outputs to LabVIEW/Naviagtion/QS Error/Gain", offsetof
    (Parameters_TemplateNIPID, QSError_Gain), 31, 1, 2, 832, "", 0 },

  { 417, "templatenipid/Outputs to LabVIEW/Naviagtion/QS Frame/Gain", offsetof
    (Parameters_TemplateNIPID, QSFrame_Gain), 31, 1, 2, 834, "", 0 },

  { 418, "templatenipid/Outputs to LabVIEW/Visualization/psi [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, psideg_Gain), 31, 1, 2, 836, "", 0 },

  { 419, "templatenipid/Outputs to LabVIEW/Visualization/psi-psid [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, psipsiddeg_Gain), 31, 1, 2, 838, "", 0 },

  { 420, "templatenipid/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, psiLOSpsideg_Gain), 31, 1, 2, 840, "", 0
  },

  { 421, "templatenipid/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, psiLOSpsiddeg_Gain), 31, 1, 2, 842, "", 0
  },

  { 422, "templatenipid/Outputs to LabVIEW/Visualization/psi_LOS [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, psi_LOSdeg_Gain), 31, 1, 2, 844, "", 0 },

  { 423, "templatenipid/Outputs to LabVIEW/Visualization/psid [deg]/Gain",
    offsetof(Parameters_TemplateNIPID, psiddeg_Gain), 31, 1, 2, 846, "", 0 },

  { 424, "templatenipid/Outputs to LabVIEW/Visualization/psi_plot/Gain",
    offsetof(Parameters_TemplateNIPID, psi_plot_Gain), 31, 1, 2, 848, "", 0 },

  { 425, "templatenipid/Outputs to LabVIEW/Visualization/qx [m]/Gain", offsetof
    (Parameters_TemplateNIPID, qxm_Gain), 31, 1, 2, 850, "", 0 },

  { 426, "templatenipid/Outputs to LabVIEW/Visualization/qx-x [m]/Gain",
    offsetof(Parameters_TemplateNIPID, qxxm_Gain), 31, 1, 2, 852, "", 0 },

  { 427, "templatenipid/Outputs to LabVIEW/Visualization/qx-xd [m]1/Gain",
    offsetof(Parameters_TemplateNIPID, qxxdm1_Gain), 31, 1, 2, 854, "", 0 },

  { 428, "templatenipid/Outputs to LabVIEW/Visualization/qy [m]/Gain", offsetof
    (Parameters_TemplateNIPID, qym_Gain), 31, 1, 2, 856, "", 0 },

  { 429, "templatenipid/Outputs to LabVIEW/Visualization/qy-y [m]/Gain",
    offsetof(Parameters_TemplateNIPID, qyym_Gain), 31, 1, 2, 858, "", 0 },

  { 430, "templatenipid/Outputs to LabVIEW/Visualization/qy-yd [m]1/Gain",
    offsetof(Parameters_TemplateNIPID, qyydm1_Gain), 31, 1, 2, 860, "", 0 },

  { 431, "templatenipid/Outputs to LabVIEW/Visualization/x [m]/Gain", offsetof
    (Parameters_TemplateNIPID, xm_Gain), 31, 1, 2, 862, "", 0 },

  { 432, "templatenipid/Outputs to LabVIEW/Visualization/x-xd [m]/Gain",
    offsetof(Parameters_TemplateNIPID, xxdm_Gain), 31, 1, 2, 864, "", 0 },

  { 433, "templatenipid/Outputs to LabVIEW/Visualization/xd [m]/Gain", offsetof
    (Parameters_TemplateNIPID, xdm_Gain), 31, 1, 2, 866, "", 0 },

  { 434, "templatenipid/Outputs to LabVIEW/Visualization/x_plot/Gain", offsetof
    (Parameters_TemplateNIPID, x_plot_Gain), 31, 1, 2, 868, "", 0 },

  { 435, "templatenipid/Outputs to LabVIEW/Visualization/y [m]/Gain", offsetof
    (Parameters_TemplateNIPID, ym_Gain), 31, 1, 2, 870, "", 0 },

  { 436, "templatenipid/Outputs to LabVIEW/Visualization/y-yd [m]/Gain",
    offsetof(Parameters_TemplateNIPID, yydm_Gain), 31, 1, 2, 872, "", 0 },

  { 437, "templatenipid/Outputs to LabVIEW/Visualization/yd [m]/Gain", offsetof
    (Parameters_TemplateNIPID, ydm_Gain), 31, 1, 2, 874, "", 0 },

  { 438, "templatenipid/Outputs to LabVIEW/Visualization/y_plot/Gain", offsetof
    (Parameters_TemplateNIPID, y_plot_Gain), 31, 1, 2, 876, "", 0 },

  { 439, "templatenipid/Outputs to LabVIEW/Visualization/splot/Gain", offsetof
    (Parameters_TemplateNIPID, splot_Gain), 31, 1, 2, 878, "", 0 },

  { 440,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain",
    offsetof(Parameters_TemplateNIPID, R12_Gain), 31, 1, 2, 880, "", 0 },

  { 441,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain",
    offsetof(Parameters_TemplateNIPID, R22_Gain), 31, 1, 2, 882, "", 0 },

  { 442,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value",
    offsetof(Parameters_TemplateNIPID, _Value), 31, 1, 2, 884, "", 0 },

  { 443,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain",
    offsetof(Parameters_TemplateNIPID, S12_Gain_m), 31, 1, 2, 886, "", 0 },

  { 444,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value",
    offsetof(Parameters_TemplateNIPID, _Value_m), 31, 1, 2, 888, "", 0 },

  { 445,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain",
    offsetof(Parameters_TemplateNIPID, S12_Gain_g), 31, 1, 2, 890, "", 0 },

  { 446,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, BT_D_Gain1_Gain), 31, 1, 2, 892, "", 0 },

  { 447,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value",
    offsetof(Parameters_TemplateNIPID, BT_Power_Offset1_Value), 31, 1, 2, 894,
    "", 0 },

  { 448,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain",
    offsetof(Parameters_TemplateNIPID, BT_D_Gain2_Gain), 31, 1, 2, 896, "", 0 },

  { 449,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, BT_L_Gain1_Gain), 31, 1, 2, 898, "", 0 },

  { 450,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain",
    offsetof(Parameters_TemplateNIPID, BT_L_Gain2_Gain), 31, 1, 2, 900, "", 0 },

  { 451,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value",
    offsetof(Parameters_TemplateNIPID, BT_Power_Offset2_Value), 31, 1, 2, 902,
    "", 0 },

  { 452,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value",
    offsetof(Parameters_TemplateNIPID, BT_Power_Offset3_Value), 31, 1, 2, 904,
    "", 0 },

  { 453,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value",
    offsetof(Parameters_TemplateNIPID, Constant_Value_j3), 31, 1, 2, 906, "", 0
  },

  { 454,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value",
    offsetof(Parameters_TemplateNIPID, Constant1_Value_m), 31, 1, 2, 908, "", 0
  },

  { 455,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain",
    offsetof(Parameters_TemplateNIPID, Neg_Gain), 31, 1, 2, 910, "", 0 },

  { 456,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain",
    offsetof(Parameters_TemplateNIPID, x_Gain), 31, 1, 2, 912, "", 0 },

  { 457,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain",
    offsetof(Parameters_TemplateNIPID, y_Gain), 31, 1, 2, 914, "", 0 },

  { 458,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_TemplateNIPID, Servo1_RowIdx), 77, 3, 2, 916, "", 0 },

  { 459,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_TemplateNIPID, Servo1_ColIdx), 77, 3, 2, 918, "", 0 },

  { 460,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table",
    offsetof(Parameters_TemplateNIPID, Servo1_Table), 24, 9, 2, 920, "", 0 },

  { 461,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_TemplateNIPID, Servo2_RowIdx), 77, 3, 2, 922, "", 0 },

  { 462,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_TemplateNIPID, Servo2_ColIdx), 77, 3, 2, 924, "", 0 },

  { 463,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table",
    offsetof(Parameters_TemplateNIPID, Servo2_Table), 24, 9, 2, 926, "", 0 },

  { 464,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_TemplateNIPID, Servo3_RowIdx), 77, 3, 2, 928, "", 0 },

  { 465,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_TemplateNIPID, Servo3_ColIdx), 77, 3, 2, 930, "", 0 },

  { 466,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table",
    offsetof(Parameters_TemplateNIPID, Servo3_Table), 24, 9, 2, 932, "", 0 },

  { 467,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_TemplateNIPID, Servo4_RowIdx), 77, 3, 2, 934, "", 0 },

  { 468,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_TemplateNIPID, Servo4_ColIdx), 77, 3, 2, 936, "", 0 },

  { 469,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table",
    offsetof(Parameters_TemplateNIPID, Servo4_Table), 24, 9, 2, 938, "", 0 },

  { 470,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_TemplateNIPID, VPS_Speed_Gain_Gain), 31, 1, 2, 940, "",
    0 },

  { 471,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_TemplateNIPID, VPS_Power_Offset_Value), 31, 1, 2, 942,
    "", 0 },

  { 472,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain",
    offsetof(Parameters_TemplateNIPID, VSPSPort_Gain), 31, 1, 2, 944, "", 0 },

  { 473,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_TemplateNIPID, VSPSStarboard_Gain), 31, 1, 2, 946, "", 0
  },

  { 474,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_TemplateNIPID, R31_Value_j), 31, 1, 2, 948, "", 0 },

  { 475,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_TemplateNIPID, R32_Value_c), 31, 1, 2, 950, "", 0 },

  { 476,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_TemplateNIPID, R13_Value_g), 31, 1, 2, 952, "", 0 },

  { 477,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_TemplateNIPID, R23_Value_g), 31, 1, 2, 954, "", 0 },

  { 478,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_TemplateNIPID, R33_Value_h), 31, 1, 2, 956, "", 0 },

  { 479,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_g), 37, 1, 2, 958, "", 0 },

  { 480,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_c0), 37, 1, 2, 960, "", 0 },

  { 481,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_k), 37, 1, 2, 962, "", 0 },

  { 482,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_o), 37, 1, 2, 964, "", 0 },

  { 483,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_h), 37, 1, 2, 966, "", 0 },

  { 484,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_pu), 37, 1, 2, 968, "", 0 },

  { 485,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_gy), 37, 1, 2, 970, "", 0 },

  { 486,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_e), 37, 1, 2, 972, "", 0 },

  { 487,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_om), 37, 1, 2, 974, "", 0 },

  { 488,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_a), 37, 1, 2, 976, "", 0 },

  { 489,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_n), 37, 1, 2, 978, "", 0 },

  { 490,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_a), 37, 1, 2, 980, "", 0 },

  { 491,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_k), 37, 1, 2, 982, "", 0 },

  { 492,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_p2), 37, 1, 2, 984, "", 0 },

  { 493,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_TemplateNIPID, Gain_Gain_a1), 37, 1, 2, 986, "", 0 },

  { 494,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_TemplateNIPID, Gain1_Gain_g5), 37, 1, 2, 988, "", 0 },
};

static int NI_ParamListSize = 495;
static int NI_ParamDimList[] = {
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Control Input Selector/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Control Mode Selector/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Enable CSE1/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/tauxscale/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/tauyscale/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/tauyawscale/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/offset u1/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/offset u2/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/offset u3/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/offset u4/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Delta [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Path Selector  [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/my [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/u_d [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/x_dmax [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/x_dmin [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/y_dmax [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/y_dmin [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Ellipse/k [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Ellipse/x_0 [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Ellipse/y_0 [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/L2 [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/PlayStation3/R2 [-]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Setpoint/setpointpsi [deg]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Setpoint/setpointx [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/Setpoint/setpointy [m]/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kppsi/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kipsi/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1 Reset Integrator/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kdpsi/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kdx/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kdy/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kix/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kiy/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kpx/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kpy/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q/12/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q/21/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q_Surge/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q_Sway/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/Initial q_x/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/Initial q_y/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/Initial s/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_d/12/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_d/13/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_d/21/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_d/23/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_d/31/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_d/32/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kdx/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kdy/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kdpsi/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_i/12/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_i/13/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_i/21/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_i/23/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_i/31/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_i/32/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kix/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kiy/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kipsi/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_p/12/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_p/13/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_p/21/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_p/23/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_p/31/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/K_p/32/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kpx/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kpy/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2Kppsi/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/ctrl2 Reset Integrator/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/kappa_1/Value */
  1, 1,                                /* templatenipid/Inputs from LabVIEW/ctrl2/lambda_q/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value */
  1, 1,                                /* templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain */
  1, 39,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues */
  1, 39,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues */
  11, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table */
  3, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues */
  3, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table */
  18, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues */
  18, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain */
  1, 39,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues */
  1, 39,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues */
  15, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table */
  13, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues */
  13, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues */
  10, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value */
  10, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues */
  10, 1,                               /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table */
  1, 39,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues */
  1, 39,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues */
  11, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table */
  3, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues */
  3, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table */
  18, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues */
  18, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table */
  1, 39,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues */
  1, 39,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues */
  15, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table */
  13, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues */
  13, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues */
  10, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value */
  10, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues */
  10, 1,                               /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R31/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/-1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R32/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R13/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R23/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R33/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain/Gain */
  3, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/zeta/Integrator/InitialCondition */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4/InitialCondition */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain */
  2, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s eq/0_2x1/Value */
  2, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain */
  2, 2,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value */
  2, 2,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator2/InitialCondition */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain */
  2, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value */
  2, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S11/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/R31/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S12/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S22/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S32/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S13/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S23/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S33/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Gain/Gain */
  2, 2,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Gain/Gain */
  1, 39,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues */
  1, 39,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues */
  11, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table */
  3, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues */
  3, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table */
  18, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues */
  18, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table */
  1, 39,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues */
  1, 39,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues */
  15, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table */
  13, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues */
  13, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues */
  10, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value */
  10, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues */
  10, 1,                               /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain */
  2, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value */
  3, 3,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/Constant1/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3/InitialCondition */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Constant/Value */
  3, 3,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2/Gain */
  3, 3,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3/Gain */
  3, 3,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4/Gain */
  1, 39,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues */
  1, 39,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues */
  11, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table */
  3, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues */
  3, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table */
  18, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues */
  18, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table */
  1, 39,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues */
  1, 39,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues */
  15, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table */
  13, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues */
  13, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues */
  10, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value */
  10, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues */
  10, 1,                               /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table */
  3, 3,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/Saturation/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/Saturation/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/Saturation1/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/Saturation1/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/Saturation2/UpperLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/Saturation2/LowerLimit */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/plant tau_surge/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/plant tau_sway/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/saturation/plant tau_yaw/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/tau1/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/tau2/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/tau3/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/tau4/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/tau5/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/tau6/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/plant BT power/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/plant VSP speed/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/plant u_1/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/plant u_2/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/plant u_3/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/plant u_4/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/plant u_5/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/fact1/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/fact2/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/fact3/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/fact4/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/fact5/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/taux/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/tauy/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/tauyaw/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/omega_qy/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Command/omegaqx/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Naviagtion/QS Error/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Naviagtion/QS Frame/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/psi [deg]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/psi-psid [deg]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/psi_LOS [deg]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/psid [deg]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/psi_plot/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/qx [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/qx-x [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/qx-xd [m]1/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/qy [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/qy-y [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/qy-yd [m]1/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/x [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/x-xd [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/xd [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/x_plot/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/y [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/y-yd [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/yd [m]/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/y_plot/Gain */
  1, 1,                                /* templatenipid/Outputs to LabVIEW/Visualization/splot/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 719;
static NI_Signal NI_SigList[] = {
  { 0, "templatenipid/Inputs from LabVIEW/tauyawscale", 0, "", offsetof
    (BlockIO_TemplateNIPID, tauyawscale), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]", 0,
    "", offsetof(BlockIO_TemplateNIPID, Initialpsirad), BLOCKIO_SIG, 0, 1, 2, 2,
    0 },

  { 2, "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial x [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, Initialxm), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial y [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, Initialym), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]",
    0, "", offsetof(BlockIO_TemplateNIPID, Initialrrads), BLOCKIO_SIG, 0, 1, 2,
    8, 0 },

  { 5, "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]", 0,
    "", offsetof(BlockIO_TemplateNIPID, Initialums), BLOCKIO_SIG, 0, 1, 2, 10, 0
  },

  { 6, "templatenipid/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]", 0,
    "", offsetof(BlockIO_TemplateNIPID, Initialvms), BLOCKIO_SIG, 0, 1, 2, 12, 0
  },

  { 7, "templatenipid/Inputs from LabVIEW/PlayStation3/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_TemplateNIPID,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "templatenipid/Inputs from LabVIEW/PlayStation3/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_TemplateNIPID,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "templatenipid/Inputs from LabVIEW/PlayStation3/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_TemplateNIPID,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "templatenipid/Inputs from LabVIEW/PlayStation3/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_TemplateNIPID,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "templatenipid/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1", 0,
    "", offsetof(BlockIO_TemplateNIPID, Gain1), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "templatenipid/Inputs from LabVIEW/Setpoint/setpointx [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, setpointxm), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "templatenipid/Inputs from LabVIEW/Setpoint/setpointy [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, setpointym), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kppsi", 0, "", offsetof
    (BlockIO_TemplateNIPID, ctrl1Kppsi), BLOCKIO_SIG, 0, 1, 2, 28, 0 },

  { 15, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1Kipsi", 0, "", offsetof
    (BlockIO_TemplateNIPID, ctrl1Kipsi), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "templatenipid/Inputs from LabVIEW/ctrl1/ctrl1 Reset Integrator", 0, "",
    offsetof(BlockIO_TemplateNIPID, ctrl1ResetIntegrator), BLOCKIO_SIG, 0, 1, 2,
    32, 0 },

  { 17, "templatenipid/Inputs from LabVIEW/ctrl2/Gamma_q/[2x2]", 0, "", offsetof
    (BlockIO_TemplateNIPID, ux2), BLOCKIO_SIG, 22, 4, 2, 34, 0 },

  { 18, "templatenipid/Inputs from LabVIEW/ctrl2/Initial q_x", 0, "", offsetof
    (BlockIO_TemplateNIPID, Initialq_x), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "templatenipid/Inputs from LabVIEW/ctrl2/Initial q_y", 0, "", offsetof
    (BlockIO_TemplateNIPID, Initialq_y), BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "templatenipid/Inputs from LabVIEW/ctrl2/Initial s", 0, "", offsetof
    (BlockIO_TemplateNIPID, Initials), BLOCKIO_SIG, 0, 1, 2, 40, 0 },

  { 21, "templatenipid/Inputs from LabVIEW/ctrl2/K_d/[3x3]", 0, "", offsetof
    (BlockIO_TemplateNIPID, ux3), BLOCKIO_SIG, 24, 9, 2, 42, 0 },

  { 22, "templatenipid/Inputs from LabVIEW/ctrl2/K_i/[3x3]", 0, "", offsetof
    (BlockIO_TemplateNIPID, ux3_c), BLOCKIO_SIG, 24, 9, 2, 44, 0 },

  { 23, "templatenipid/Inputs from LabVIEW/ctrl2/K_p/[3x3]", 0, "", offsetof
    (BlockIO_TemplateNIPID, ux3_p), BLOCKIO_SIG, 24, 9, 2, 46, 0 },

  { 24,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1",
    0, "", offsetof(BlockIO_TemplateNIPID, l_x1), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2",
    0, "", offsetof(BlockIO_TemplateNIPID, l_x2), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2",
    0, "", offsetof(BlockIO_TemplateNIPID, l_y2), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/3x5",
    0, "", offsetof(BlockIO_TemplateNIPID, x5), BLOCKIO_SIG, 26, 15, 2, 54, 0 },

  { 28,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r",
    0, "", offsetof(BlockIO_TemplateNIPID, N_r), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v",
    0, "", offsetof(BlockIO_TemplateNIPID, N_v), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u",
    0, "", offsetof(BlockIO_TemplateNIPID, X_u), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v",
    0, "", offsetof(BlockIO_TemplateNIPID, Y_v), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr",
    0, "", offsetof(BlockIO_TemplateNIPID, Y_vr), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Linear Dampning matrix",
    0, "", offsetof(BlockIO_TemplateNIPID, LinearDampningmatrix), BLOCKIO_SIG,
    24, 9, 2, 66, 0 },

  { 34,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_11",
    0, "", offsetof(BlockIO_TemplateNIPID, M_11), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_22",
    0, "", offsetof(BlockIO_TemplateNIPID, M_22), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m x_g",
    0, "", offsetof(BlockIO_TemplateNIPID, mx_g), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_32",
    0, "", offsetof(BlockIO_TemplateNIPID, M_32), BLOCKIO_SIG, 0, 1, 2, 74, 0 },

  { 38,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_23",
    0, "", offsetof(BlockIO_TemplateNIPID, M_23), BLOCKIO_SIG, 0, 1, 2, 76, 0 },

  { 39,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_33",
    0, "", offsetof(BlockIO_TemplateNIPID, M_33), BLOCKIO_SIG, 0, 1, 2, 78, 0 },

  { 40,
    "templatenipid/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/3x3",
    0, "", offsetof(BlockIO_TemplateNIPID, x3), BLOCKIO_SIG, 24, 9, 2, 80, 0 },

  { 41, "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_1", 0,
    "u_1", offsetof(BlockIO_TemplateNIPID, u_1), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_1tof_1), BLOCKIO_SIG, 0, 1, 2, 84,
    0 },

  { 43, "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_2", 0,
    "u_2", offsetof(BlockIO_TemplateNIPID, u_2), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5",
    0, "", offsetof(BlockIO_TemplateNIPID, u_205), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_201u_202), BLOCKIO_SIG, 0, 1, 2, 90,
    0 },

  { 46,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_20), BLOCKIO_SIG, 0, 1, 2, 92, 0 },

  { 47,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch), BLOCKIO_SIG, 0, 1,
    2, 94, 0 },

  { 48, "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_3", 0,
    "u_3", offsetof(BlockIO_TemplateNIPID, u_3), BLOCKIO_SIG, 0, 1, 2, 96, 0 },

  { 49,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3",
    0, "", offsetof(BlockIO_TemplateNIPID, u_3tof_3), BLOCKIO_SIG, 0, 1, 2, 98,
    0 },

  { 50, "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_4", 0,
    "u_4", offsetof(BlockIO_TemplateNIPID, u_4), BLOCKIO_SIG, 0, 1, 2, 100, 0 },

  { 51,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_401), BLOCKIO_SIG, 0, 1, 2, 102, 0
  },

  { 52,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_401_o), BLOCKIO_SIG, 0, 1, 2, 104,
    0 },

  { 53,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_p), BLOCKIO_SIG, 0, 1,
    2, 106, 0 },

  { 54, "templatenipid/Main Subsystems/Control/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_TemplateNIPID,
    BowThrusterdirection), BLOCKIO_SIG, 0, 1, 2, 108, 0 },

  { 55, "templatenipid/Main Subsystems/Control/PS3 u input control/PS3 u_5", 0,
    "u_5", offsetof(BlockIO_TemplateNIPID, u_5), BLOCKIO_SIG, 0, 1, 2, 110, 0 },

  { 56,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_TemplateNIPID, DeadZone001), BLOCKIO_SIG, 0, 1, 2,
    112, 0 },

  { 57,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_50), BLOCKIO_SIG, 0, 1, 2, 114, 0 },

  { 58,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_50_n), BLOCKIO_SIG, 0, 1, 2, 116, 0
  },

  { 59,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_i), BLOCKIO_SIG, 0, 1,
    2, 118, 0 },

  { 60,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1), BLOCKIO_SIG, 20, 3, 2, 120,
    0 },

  { 61,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_1tof_1_p), BLOCKIO_SIG, 0, 1, 2,
    122, 0 },

  { 62,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5",
    0, "", offsetof(BlockIO_TemplateNIPID, u_205_l), BLOCKIO_SIG, 0, 1, 2, 124,
    0 },

  { 63,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_201u_202_o), BLOCKIO_SIG, 0, 1, 2,
    126, 0 },

  { 64,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_20_p), BLOCKIO_SIG, 0, 1, 2, 128, 0
  },

  { 65,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_iv), BLOCKIO_SIG, 0,
    1, 2, 130, 0 },

  { 66,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3",
    0, "", offsetof(BlockIO_TemplateNIPID, u_3tof_3_b), BLOCKIO_SIG, 0, 1, 2,
    132, 0 },

  { 67,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_401_h), BLOCKIO_SIG, 0, 1, 2, 134,
    0 },

  { 68,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_401_j), BLOCKIO_SIG, 0, 1, 2, 136,
    0 },

  { 69,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_pl), BLOCKIO_SIG, 0,
    1, 2, 138, 0 },

  { 70,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_TemplateNIPID, DeadZone001_p), BLOCKIO_SIG, 0, 1, 2,
    140, 0 },

  { 71,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_50_l), BLOCKIO_SIG, 0, 1, 2, 142, 0
  },

  { 72,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_50_b), BLOCKIO_SIG, 0, 1, 2, 144, 0
  },

  { 73,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_c), BLOCKIO_SIG, 0, 1,
    2, 146, 0 },

  { 74,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_b), BLOCKIO_SIG, 20, 3, 2,
    148, 0 },

  { 75, "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In", 0, "",
    offsetof(BlockIO_TemplateNIPID, QTMIn), BLOCKIO_SIG, 48, 9, 2, 150, 0 },

  { 76,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]",
    0, "", offsetof(BlockIO_TemplateNIPID, QTMIn3xcoordmm), BLOCKIO_SIG, 31, 1,
    2, 152, 0 },

  { 77, "templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m x", 0, "",
    offsetof(BlockIO_TemplateNIPID, mm2mx), BLOCKIO_SIG, 31, 1, 2, 154, 0 },

  { 78,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]",
    0, "", offsetof(BlockIO_TemplateNIPID, QTMIn4ycoordmm), BLOCKIO_SIG, 31, 1,
    2, 156, 0 },

  { 79, "templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m y", 0, "",
    offsetof(BlockIO_TemplateNIPID, mm2my), BLOCKIO_SIG, 31, 1, 2, 158, 0 },

  { 80,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]",
    0, "", offsetof(BlockIO_TemplateNIPID, QTMIn6yawdeg), BLOCKIO_SIG, 31, 1, 2,
    160, 0 },

  { 81, "templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r yaw", 0,
    "", offsetof(BlockIO_TemplateNIPID, d2ryaw), BLOCKIO_SIG, 31, 1, 2, 162, 0 },

  { 82, "templatenipid/Main Subsystems/Naviagation/Navigation Switch/eta Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, etaSwitch), BLOCKIO_SIG, 20, 3, 2,
    164, 0 },

  { 83, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R11", 0, "",
    offsetof(BlockIO_TemplateNIPID, R11), BLOCKIO_SIG, 0, 1, 2, 166, 0 },

  { 84, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R21", 0, "",
    offsetof(BlockIO_TemplateNIPID, R21), BLOCKIO_SIG, 0, 1, 2, 168, 0 },

  { 85, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R12", 0, "",
    offsetof(BlockIO_TemplateNIPID, R12), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/-1", 0, "",
    offsetof(BlockIO_TemplateNIPID, u), BLOCKIO_SIG, 0, 1, 2, 172, 0 },

  { 87, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R22", 0, "",
    offsetof(BlockIO_TemplateNIPID, R22), BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88, "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R(psi)", 0,
    "", offsetof(BlockIO_TemplateNIPID, Rpsi), BLOCKIO_SIG, 24, 9, 2, 176, 0 },

  { 89,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/R(psi)/R^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction), BLOCKIO_SIG, 24, 9, 2,
    178, 0 },

  { 90,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation), BLOCKIO_SIG, 0, 1, 2,
    180, 0 },

  { 91,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1), BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_f), BLOCKIO_SIG, 0, 1, 2,
    188, 0 },

  { 95,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum), BLOCKIO_SIG, 0, 1, 2, 190, 0 },

  { 96,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator",
    0, "", offsetof(BlockIO_TemplateNIPID, Integrator), BLOCKIO_SIG, 25, 2, 2,
    192, 0 },

  { 97,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/x_2 - x_1",
    0, "", offsetof(BlockIO_TemplateNIPID, x_2x_1), BLOCKIO_SIG, 0, 1, 2, 194, 0
  },

  { 98,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/y_2 - y_1",
    0, "", offsetof(BlockIO_TemplateNIPID, y_2y_1), BLOCKIO_SIG, 0, 1, 2, 196, 0
  },

  { 99,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_k), BLOCKIO_SIG, 0, 1, 2,
    198, 0 },

  { 100,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Rounding Function",
    0, "", offsetof(BlockIO_TemplateNIPID, RoundingFunction), BLOCKIO_SIG, 0, 1,
    2, 200, 0 },

  { 101,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product), BLOCKIO_SIG, 25, 2, 2, 202,
    0 },

  { 102,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator1",
    0, "", offsetof(BlockIO_TemplateNIPID, Integrator1), BLOCKIO_SIG, 0, 1, 2,
    204, 0 },

  { 103,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2), BLOCKIO_SIG, 0, 1, 2, 206,
    0 },

  { 104,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/sin(s)",
    0, "", offsetof(BlockIO_TemplateNIPID, sins), BLOCKIO_SIG, 0, 1, 2, 208, 0 },

  { 105,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_a), BLOCKIO_SIG, 0, 1, 2, 210,
    0 },

  { 106,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_i), BLOCKIO_SIG, 0, 1, 2, 212, 0
  },

  { 107,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/cos(s)",
    0, "", offsetof(BlockIO_TemplateNIPID, coss), BLOCKIO_SIG, 0, 1, 2, 214, 0 },

  { 108,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_a), BLOCKIO_SIG, 0, 1, 2,
    216, 0 },

  { 109,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Subract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subract), BLOCKIO_SIG, 0, 1, 2, 218,
    0 },

  { 110,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_i), BLOCKIO_SIG, 25, 2, 2,
    220, 0 },

  { 111,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add), BLOCKIO_SIG, 25, 2, 2, 222, 0 },

  { 112,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateNIPID, TrigonometricFunction), BLOCKIO_SIG,
    0, 1, 2, 224, 0 },

  { 113,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_j), BLOCKIO_SIG, 0, 1, 2,
    226, 0 },

  { 114,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign_c), BLOCKIO_SIG, 0, 1, 2, 228, 0
  },

  { 115,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_k), BLOCKIO_SIG, 0, 1, 2, 230, 0
  },

  { 116,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_j), BLOCKIO_SIG, 0, 1, 2, 232, 0
  },

  { 117,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_h), BLOCKIO_SIG, 0, 1, 2,
    234, 0 },

  { 118,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_k), BLOCKIO_SIG, 0, 1, 2, 236, 0
  },

  { 119,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_i), BLOCKIO_SIG, 0, 1, 2,
    238, 0 },

  { 120,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign_k), BLOCKIO_SIG, 0, 1, 2, 240, 0
  },

  { 121,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_d), BLOCKIO_SIG, 0, 1, 2, 242, 0
  },

  { 122,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_l), BLOCKIO_SIG, 0, 1, 2, 244, 0
  },

  { 123,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_ht), BLOCKIO_SIG, 0, 1,
    2, 246, 0 },

  { 124,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_l), BLOCKIO_SIG, 0, 1, 2, 248, 0
  },

  { 125,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_n), BLOCKIO_SIG, 22, 4,
    2, 250, 0 },

  { 126,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/x_2 - x_1",
    0, "", offsetof(BlockIO_TemplateNIPID, x_2x_1_g), BLOCKIO_SIG, 0, 1, 2, 252,
    0 },

  { 127,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s",
    0, "", offsetof(BlockIO_TemplateNIPID, x_2x_1s), BLOCKIO_SIG, 0, 1, 2, 254,
    0 },

  { 128,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s + x_1",
    0, "", offsetof(BlockIO_TemplateNIPID, x_2x_1sx_1), BLOCKIO_SIG, 0, 1, 2,
    256, 0 },

  { 129,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/y_2 - y_1",
    0, "", offsetof(BlockIO_TemplateNIPID, y_2y_1_m), BLOCKIO_SIG, 0, 1, 2, 258,
    0 },

  { 130,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s",
    0, "", offsetof(BlockIO_TemplateNIPID, y_2y_1s), BLOCKIO_SIG, 0, 1, 2, 260,
    0 },

  { 131,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s + y_1",
    0, "", offsetof(BlockIO_TemplateNIPID, y_2y_1sy_1), BLOCKIO_SIG, 0, 1, 2,
    262, 0 },

  { 132,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_f), BLOCKIO_SIG, 25, 2, 2,
    264, 0 },

  { 133,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_n), BLOCKIO_SIG, 0, 1, 2,
    266, 0 },

  { 134,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/cos(s)",
    0, "", offsetof(BlockIO_TemplateNIPID, coss_o), BLOCKIO_SIG, 0, 1, 2, 268, 0
  },

  { 135,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_d), BLOCKIO_SIG, 0, 1, 2, 270,
    0 },

  { 136,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_c), BLOCKIO_SIG, 0, 1, 2, 272, 0
  },

  { 137,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/sin(s)",
    0, "", offsetof(BlockIO_TemplateNIPID, sins_p), BLOCKIO_SIG, 0, 1, 2, 274, 0
  },

  { 138,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_p), BLOCKIO_SIG, 0, 1, 2,
    276, 0 },

  { 139,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add1",
    0, "", offsetof(BlockIO_TemplateNIPID, Add1), BLOCKIO_SIG, 0, 1, 2, 278, 0 },

  { 140,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Subract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subract_h), BLOCKIO_SIG, 0, 1, 2, 280,
    0 },

  { 141,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_h), BLOCKIO_SIG, 25, 2, 2,
    282, 0 },

  { 142,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_cx), BLOCKIO_SIG, 25, 2, 2, 284,
    0 },

  { 143,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch), BLOCKIO_SIG, 0, 1, 2, 286, 0
  },

  { 144,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch2",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch2), BLOCKIO_SIG, 0, 1, 2, 288,
    0 },

  { 145,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch_m), BLOCKIO_SIG, 0, 1, 2, 290,
    0 },

  { 146,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch2",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch2_c), BLOCKIO_SIG, 0, 1, 2, 292,
    0 },

  { 147,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract), BLOCKIO_SIG, 25, 2, 2, 294,
    0 },

  { 148,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon), BLOCKIO_SIG, 25, 2, 2, 296,
    0 },

  { 149,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSelector), BLOCKIO_SIG, 31,
    1, 2, 298, 0 },

  { 150,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateNIPID, TrigonometricFunction_n), BLOCKIO_SIG,
    31, 1, 2, 300, 0 },

  { 151,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_c), BLOCKIO_SIG, 31, 1, 2,
    302, 0 },

  { 152,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign_h), BLOCKIO_SIG, 31, 1, 2, 304,
    0 },

  { 153,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_f), BLOCKIO_SIG, 31, 1, 2, 306,
    0 },

  { 154,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_g), BLOCKIO_SIG, 31, 1, 2, 308,
    0 },

  { 155,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_c), BLOCKIO_SIG, 31, 1,
    2, 310, 0 },

  { 156,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_f), BLOCKIO_SIG, 31, 1, 2, 312, 0
  },

  { 157,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_f), BLOCKIO_SIG, 0, 1, 2,
    314, 0 },

  { 158,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_m), BLOCKIO_SIG, 0, 1, 2,
    316, 0 },

  { 159,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign_f), BLOCKIO_SIG, 0, 1, 2, 318, 0
  },

  { 160,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_b), BLOCKIO_SIG, 0, 1, 2, 320, 0
  },

  { 161,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_lj), BLOCKIO_SIG, 0, 1, 2, 322,
    0 },

  { 162,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_e), BLOCKIO_SIG, 0, 1, 2,
    324, 0 },

  { 163,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_e), BLOCKIO_SIG, 0, 1, 2, 326, 0
  },

  { 164,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, VectorConcatenate), BLOCKIO_SIG, 20,
    3, 2, 328, 0 },

  { 165, "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Subtract", 0,
    "", offsetof(BlockIO_TemplateNIPID, Subtract_m), BLOCKIO_SIG, 20, 3, 2, 330,
    0 },

  { 166,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_cu), BLOCKIO_SIG, 0, 1, 2,
    332, 0 },

  { 167,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign_d), BLOCKIO_SIG, 0, 1, 2, 334, 0
  },

  { 168,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_fi), BLOCKIO_SIG, 0, 1, 2, 336,
    0 },

  { 169,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_e), BLOCKIO_SIG, 0, 1, 2, 338, 0
  },

  { 170,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_k), BLOCKIO_SIG, 0, 1, 2,
    340, 0 },

  { 171,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_d), BLOCKIO_SIG, 0, 1, 2, 342, 0
  },

  { 172,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_k), BLOCKIO_SIG, 20, 3, 2,
    344, 0 },

  { 173,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_p), BLOCKIO_SIG, 20, 3, 2, 346,
    0 },

  { 174, "templatenipid/Main Subsystems/Control/Nonlinear PID/zeta/Integrator",
    0, "", offsetof(BlockIO_TemplateNIPID, Integrator_k), BLOCKIO_SIG, 28, 3, 2,
    348, 0 },

  { 175,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_ao), BLOCKIO_SIG, 28, 3, 2,
    350, 0 },

  { 176,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_a), BLOCKIO_SIG, 28, 3, 2, 352,
    0 },

  { 177,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4",
    0, "nu", offsetof(BlockIO_TemplateNIPID, nu), BLOCKIO_SIG, 20, 3, 2, 354, 0
  },

  { 178, "templatenipid/Main Subsystems/Naviagation/Navigation Switch/nu Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, nuSwitch), BLOCKIO_SIG, 20, 3, 2, 356,
    0 },

  { 179,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qx",
    0, "", offsetof(BlockIO_TemplateNIPID, f_qx), BLOCKIO_SIG, 0, 1, 2, 358, 0 },

  { 180,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qy",
    0, "", offsetof(BlockIO_TemplateNIPID, f_qy), BLOCKIO_SIG, 0, 1, 2, 360, 0 },

  { 181,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_c), BLOCKIO_SIG, 25, 2, 2,
    362, 0 },

  { 182,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2), BLOCKIO_SIG, 0, 1, 2, 364, 0
  },

  { 183,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2), BLOCKIO_SIG, 31, 1, 2,
    366, 0 },

  { 184,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_l), BLOCKIO_SIG, 31, 1, 2, 368, 0
  },

  { 185,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide), BLOCKIO_SIG, 31, 1, 2, 370,
    0 },

  { 186,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector1",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSelector1), BLOCKIO_SIG, 29,
    2, 2, 372, 0 },

  { 187,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_kt), BLOCKIO_SIG, 29, 2, 2,
    374, 0 },

  { 188,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_m), BLOCKIO_SIG, 29, 2, 2, 376, 0 },

  { 189,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, VectorConcatenate_k), BLOCKIO_SIG, 20,
    3, 2, 378, 0 },

  { 190,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_h), BLOCKIO_SIG, 32, 2, 2,
    380, 0 },

  { 191,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_nb), BLOCKIO_SIG, 0, 1, 2,
    382, 0 },

  { 192,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/cos(s)",
    0, "", offsetof(BlockIO_TemplateNIPID, coss_n), BLOCKIO_SIG, 0, 1, 2, 384, 0
  },

  { 193,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_kc), BLOCKIO_SIG, 0, 1,
    2, 386, 0 },

  { 194,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_p), BLOCKIO_SIG, 0, 1, 2, 388,
    0 },

  { 195,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_m), BLOCKIO_SIG, 0, 1, 2, 390, 0
  },

  { 196,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/sin(s)",
    0, "", offsetof(BlockIO_TemplateNIPID, sins_a), BLOCKIO_SIG, 0, 1, 2, 392, 0
  },

  { 197,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_hr), BLOCKIO_SIG, 0, 1, 2,
    394, 0 },

  { 198,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_o), BLOCKIO_SIG, 0, 1, 2, 396,
    0 },

  { 199,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Subract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subract_d), BLOCKIO_SIG, 0, 1, 2, 398,
    0 },

  { 200,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_k), BLOCKIO_SIG, 25, 2, 2,
    400, 0 },

  { 201,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_a), BLOCKIO_SIG, 32, 2, 2, 402, 0
  },

  { 202,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_TemplateNIPID, x_dsy_ds2), BLOCKIO_SIG, 31, 1, 2,
    404, 0 },

  { 203,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s^2 + y_d^s",
    0, "", offsetof(BlockIO_TemplateNIPID, x_ds2y_ds), BLOCKIO_SIG, 31, 1, 2,
    406, 0 },

  { 204,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s + y_d^s^2 ) - ( x_d^s^2 + y_d^s )",
    0, "", offsetof(BlockIO_TemplateNIPID, x_dsy_ds2x_ds2y_ds), BLOCKIO_SIG, 31,
    1, 2, 408, 0 },

  { 205,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2",
    0, "", offsetof(BlockIO_TemplateNIPID, x_ds2), BLOCKIO_SIG, 0, 1, 2, 410, 0
  },

  { 206,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( y_d^s )^2",
    0, "", offsetof(BlockIO_TemplateNIPID, y_ds2), BLOCKIO_SIG, 0, 1, 2, 412, 0
  },

  { 207,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2 + ( y_d^s )^2",
    0, "", offsetof(BlockIO_TemplateNIPID, x_ds2y_ds2), BLOCKIO_SIG, 0, 1, 2,
    414, 0 },

  { 208,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_i), BLOCKIO_SIG, 31, 1, 2, 416,
    0 },

  { 209,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2_l), BLOCKIO_SIG, 0, 1, 2, 418,
    0 },

  { 210,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2_b), BLOCKIO_SIG, 31, 1, 2,
    420, 0 },

  { 211,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_e), BLOCKIO_SIG, 31, 1, 2, 422, 0
  },

  { 212,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_ix), BLOCKIO_SIG, 31, 1, 2,
    424, 0 },

  { 213,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_ch), BLOCKIO_SIG, 22, 4,
    2, 426, 0 },

  { 214,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_ht), BLOCKIO_SIG, 25, 2, 2,
    428, 0 },

  { 215,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_m), BLOCKIO_SIG, 25, 2, 2,
    430, 0 },

  { 216,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Subtract1",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract1), BLOCKIO_SIG, 25, 2, 2,
    432, 0 },

  { 217,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector2",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSelector2), BLOCKIO_SIG, 31,
    1, 2, 434, 0 },

  { 218,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_l), BLOCKIO_SIG, 31, 1, 2,
    436, 0 },

  { 219,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_n), BLOCKIO_SIG, 31, 1, 2,
    438, 0 },

  { 220,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2_p), BLOCKIO_SIG, 31, 1, 2,
    440, 0 },

  { 221,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2_b), BLOCKIO_SIG, 0, 1, 2, 442,
    0 },

  { 222,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_d), BLOCKIO_SIG, 31, 1, 2, 444, 0
  },

  { 223,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/sqrt",
    0, "", offsetof(BlockIO_TemplateNIPID, sqrt_m), BLOCKIO_SIG, 31, 1, 2, 446,
    0 },

  { 224,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_k), BLOCKIO_SIG, 31, 1, 2, 448,
    0 },

  { 225,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_cq), BLOCKIO_SIG, 29, 2,
    2, 450, 0 },

  { 226,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_g), BLOCKIO_SIG, 0, 1, 2, 452,
    0 },

  { 227,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_TemplateNIPID, sqrt_p), BLOCKIO_SIG, 0, 1, 2, 454, 0
  },

  { 228,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_gf), BLOCKIO_SIG, 0, 1, 2,
    456, 0 },

  { 229,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_ho), BLOCKIO_SIG, 29, 2,
    2, 458, 0 },

  { 230,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_n), BLOCKIO_SIG, 0, 1, 2, 460,
    0 },

  { 231,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_TemplateNIPID, sqrt_e), BLOCKIO_SIG, 0, 1, 2, 462, 0
  },

  { 232,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Subract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subract_k), BLOCKIO_SIG, 0, 1, 2, 464,
    0 },

  { 233,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_bz), BLOCKIO_SIG, 0, 1, 2,
    466, 0 },

  { 234,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_df), BLOCKIO_SIG, 0, 1, 2, 468, 0
  },

  { 235,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_l), BLOCKIO_SIG, 0, 1, 2, 470,
    0 },

  { 236,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_pe), BLOCKIO_SIG, 0, 1, 2,
    472, 0 },

  { 237,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_m), BLOCKIO_SIG, 29, 2,
    2, 474, 0 },

  { 238,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_m), BLOCKIO_SIG, 29, 2, 2, 476,
    0 },

  { 239,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_ac), BLOCKIO_SIG, 0, 1, 2,
    478, 0 },

  { 240,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_g), BLOCKIO_SIG, 0, 1, 2, 480, 0
  },

  { 241,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_ni), BLOCKIO_SIG, 0, 1, 2,
    482, 0 },

  { 242,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, VectorConcatenate_c), BLOCKIO_SIG, 28,
    3, 2, 484, 0 },

  { 243, "templatenipid/Main Subsystems/Control/Nonlinear PID/v_d/Add", 0, "",
    offsetof(BlockIO_TemplateNIPID, Add_o), BLOCKIO_SIG, 28, 3, 2, 486, 0 },

  { 244, "templatenipid/Main Subsystems/Control/Nonlinear PID/e2/Product", 0, "",
    offsetof(BlockIO_TemplateNIPID, Product_kj), BLOCKIO_SIG, 28, 3, 2, 488, 0 },

  { 245, "templatenipid/Main Subsystems/Control/Nonlinear PID/e2/Subtract", 0,
    "", offsetof(BlockIO_TemplateNIPID, Subtract_k), BLOCKIO_SIG, 28, 3, 2, 490,
    0 },

  { 246,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_m), BLOCKIO_SIG, 28, 3, 2,
    492, 0 },

  { 247,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Gain2",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain2), BLOCKIO_SIG, 28, 3, 2, 494, 0
  },

  { 248,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_g), BLOCKIO_SIG, 28, 3, 2, 496, 0
  },

  { 249,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FL/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_h4), BLOCKIO_SIG, 20, 3, 2,
    498, 0 },

  { 250,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/Product", 0,
    "", offsetof(BlockIO_TemplateNIPID, Product_d3), BLOCKIO_SIG, 20, 3, 2, 500,
    0 },

  { 251,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_TemplateNIPID, TrigonometricFunction1), BLOCKIO_SIG,
    0, 1, 2, 502, 0 },

  { 252,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_k3), BLOCKIO_SIG, 0, 1, 2, 504,
    0 },

  { 253,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_j), BLOCKIO_SIG, 29, 2, 2,
    506, 0 },

  { 254,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateNIPID, TrigonometricFunction_e), BLOCKIO_SIG,
    0, 1, 2, 508, 0 },

  { 255,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_l), BLOCKIO_SIG, 29, 2, 2,
    510, 0 },

  { 256,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, MatrixConcatenate), BLOCKIO_SIG, 22,
    4, 2, 512, 0 },

  { 257,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_ay), BLOCKIO_SIG, 22, 4, 2,
    514, 0 },

  { 258,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_cw), BLOCKIO_SIG, 29, 2,
    2, 516, 0 },

  { 259,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_p), BLOCKIO_SIG, 31, 1, 2,
    518, 0 },

  { 260,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_ct), BLOCKIO_SIG, 32, 2,
    2, 520, 0 },

  { 261,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product3",
    0, "", offsetof(BlockIO_TemplateNIPID, Product3), BLOCKIO_SIG, 22, 4, 2, 522,
    0 },

  { 262,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product4",
    0, "", offsetof(BlockIO_TemplateNIPID, Product4), BLOCKIO_SIG, 22, 4, 2, 524,
    0 },

  { 263,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_ma), BLOCKIO_SIG, 22, 4, 2, 526, 0
  },

  { 264,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2_g), BLOCKIO_SIG, 0, 1, 2, 528,
    0 },

  { 265,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2_f), BLOCKIO_SIG, 31, 1, 2,
    530, 0 },

  { 266,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_n), BLOCKIO_SIG, 31, 1, 2, 532, 0
  },

  { 267,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/( )^2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_j), BLOCKIO_SIG, 31, 1, 2, 534, 0 },

  { 268,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_h), BLOCKIO_SIG, 22, 4, 2, 536,
    0 },

  { 269,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_kt), BLOCKIO_SIG, 22, 4, 2,
    538, 0 },

  { 270,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide1",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide1), BLOCKIO_SIG, 22, 4, 2, 540,
    0 },

  { 271,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_d), BLOCKIO_SIG, 22, 4, 2,
    542, 0 },

  { 272,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/psi_los^q^2T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_l), BLOCKIO_SIG, 22, 4,
    2, 544, 0 },

  { 273,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_o), BLOCKIO_SIG, 29, 2, 2,
    546, 0 },

  { 274,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_ay), BLOCKIO_SIG, 29, 2, 2,
    548, 0 },

  { 275,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_am), BLOCKIO_SIG, 29, 2, 2, 550,
    0 },

  { 276,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, MatrixConcatenate_b), BLOCKIO_SIG, 30,
    6, 2, 552, 0 },

  { 277,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_m), BLOCKIO_SIG, 29, 2, 2,
    554, 0 },

  { 278,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_n), BLOCKIO_SIG, 29, 2, 2, 556, 0 },

  { 279,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2_p), BLOCKIO_SIG, 0, 1, 2, 558,
    0 },

  { 280,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2_a), BLOCKIO_SIG, 31, 1, 2,
    560, 0 },

  { 281,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_j), BLOCKIO_SIG, 31, 1, 2, 562, 0
  },

  { 282,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/( )^2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_f), BLOCKIO_SIG, 31, 1, 2, 564, 0 },

  { 283,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_b), BLOCKIO_SIG, 29, 2, 2, 566,
    0 },

  { 284,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_p1), BLOCKIO_SIG, 22, 4, 2,
    568, 0 },

  { 285,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector3",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSelector3), BLOCKIO_SIG, 29,
    2, 2, 570, 0 },

  { 286,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_bp), BLOCKIO_SIG, 29, 2, 2,
    572, 0 },

  { 287,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide1",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide1_b), BLOCKIO_SIG, 29, 2, 2,
    574, 0 },

  { 288,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_g), BLOCKIO_SIG, 29, 2, 2,
    576, 0 },

  { 289,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_e), BLOCKIO_SIG, 29, 2, 2,
    578, 0 },

  { 290,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_c), BLOCKIO_SIG, 29, 2, 2,
    580, 0 },

  { 291,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2_at), BLOCKIO_SIG, 31, 1, 2,
    582, 0 },

  { 292,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2_n), BLOCKIO_SIG, 0, 1, 2, 584,
    0 },

  { 293,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_ai), BLOCKIO_SIG, 31, 1, 2, 586,
    0 },

  { 294,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/^3//2",
    0, "", offsetof(BlockIO_TemplateNIPID, u2), BLOCKIO_SIG, 31, 1, 2, 588, 0 },

  { 295,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_k1), BLOCKIO_SIG, 29, 2, 2,
    590, 0 },

  { 296,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_c4), BLOCKIO_SIG, 29, 2, 2,
    592, 0 },

  { 297,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_j), BLOCKIO_SIG, 29, 2,
    2, 594, 0 },

  { 298,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_n), BLOCKIO_SIG, 29, 2, 2, 596,
    0 },

  { 299,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_hk), BLOCKIO_SIG, 29, 2, 2,
    598, 0 },

  { 300,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_a), BLOCKIO_SIG, 29, 2, 2, 600,
    0 },

  { 301,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_f4), BLOCKIO_SIG, 29, 2, 2, 602,
    0 },

  { 302,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_hrb), BLOCKIO_SIG, 29, 2, 2,
    604, 0 },

  { 303,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_p), BLOCKIO_SIG, 29, 2, 2, 606, 0
  },

  { 304,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, MatrixConcatenate_k), BLOCKIO_SIG, 30,
    6, 2, 608, 0 },

  { 305, "templatenipid/Main Subsystems/Control/Nonlinear PID/a_d/v_d^q/Add", 0,
    "", offsetof(BlockIO_TemplateNIPID, Add_jn), BLOCKIO_SIG, 30, 6, 2, 610, 0 },

  { 306,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator2",
    0, "", offsetof(BlockIO_TemplateNIPID, Integrator2), BLOCKIO_SIG, 25, 2, 2,
    612, 0 },

  { 307, "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Add1",
    0, "", offsetof(BlockIO_TemplateNIPID, Add1_g), BLOCKIO_SIG, 25, 2, 2, 614,
    0 },

  { 308, "templatenipid/Main Subsystems/Control/Nonlinear PID/a_d/Product", 0,
    "", offsetof(BlockIO_TemplateNIPID, Product_c3), BLOCKIO_SIG, 20, 3, 2, 616,
    0 },

  { 309,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_TemplateNIPID, TrigonometricFunction1_f),
    BLOCKIO_SIG, 0, 1, 2, 618, 0 },

  { 310,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_e), BLOCKIO_SIG, 0, 1, 2, 620, 0
  },

  { 311,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_o), BLOCKIO_SIG, 31, 1, 2,
    622, 0 },

  { 312,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateNIPID, TrigonometricFunction_i), BLOCKIO_SIG,
    0, 1, 2, 624, 0 },

  { 313,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_g), BLOCKIO_SIG, 31, 1, 2,
    626, 0 },

  { 314,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_le), BLOCKIO_SIG, 25, 2, 2,
    628, 0 },

  { 315,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_d2), BLOCKIO_SIG, 0, 1, 2,
    630, 0 },

  { 316,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_b4), BLOCKIO_SIG, 0, 1, 2,
    632, 0 },

  { 317,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, VectorConcatenate_m), BLOCKIO_SIG, 20,
    3, 2, 634, 0 },

  { 318,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_ar), BLOCKIO_SIG, 32, 2, 2,
    636, 0 },

  { 319,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_gd), BLOCKIO_SIG, 0, 1, 2,
    638, 0 },

  { 320,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/sin(s)3",
    0, "", offsetof(BlockIO_TemplateNIPID, sins3), BLOCKIO_SIG, 0, 1, 2, 640, 0
  },

  { 321,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_i), BLOCKIO_SIG, 0, 1, 2,
    642, 0 },

  { 322,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_b), BLOCKIO_SIG, 0, 1, 2, 644,
    0 },

  { 323,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/cos(s)3",
    0, "", offsetof(BlockIO_TemplateNIPID, coss3), BLOCKIO_SIG, 0, 1, 2, 646, 0
  },

  { 324,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_ju), BLOCKIO_SIG, 0, 1, 2,
    648, 0 },

  { 325,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_c), BLOCKIO_SIG, 0, 1, 2, 650, 0
  },

  { 326,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Subract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subract_c), BLOCKIO_SIG, 0, 1, 2, 652,
    0 },

  { 327,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_jq), BLOCKIO_SIG, 25, 2, 2,
    654, 0 },

  { 328,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_b), BLOCKIO_SIG, 32, 2, 2, 656, 0
  },

  { 329,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + y_d^s^3",
    0, "", offsetof(BlockIO_TemplateNIPID, x_dsy_ds3), BLOCKIO_SIG, 31, 1, 2,
    658, 0 },

  { 330,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s^3 + y_d^s",
    0, "", offsetof(BlockIO_TemplateNIPID, x_ds3y_ds), BLOCKIO_SIG, 31, 1, 2,
    660, 0 },

  { 331,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + y_d^s^3  ) - ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_TemplateNIPID, x_dsy_ds3x_ds3y_ds), BLOCKIO_SIG, 31,
    1, 2, 662, 0 },

  { 332,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_f), BLOCKIO_SIG, 31, 1, 2,
    664, 0 },

  { 333,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + x_d^s^2",
    0, "", offsetof(BlockIO_TemplateNIPID, x_dsx_ds2), BLOCKIO_SIG, 31, 1, 2,
    666, 0 },

  { 334,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/y_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_TemplateNIPID, y_dsy_ds2), BLOCKIO_SIG, 31, 1, 2,
    668, 0 },

  { 335,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + x_d^s^2 ) + ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_TemplateNIPID, x_dsx_ds2x_ds3y_ds), BLOCKIO_SIG, 31,
    1, 2, 670, 0 },

  { 336,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_b), BLOCKIO_SIG, 31, 1, 2, 672, 0 },

  { 337,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_i), BLOCKIO_SIG, 31, 1, 2,
    674, 0 },

  { 338,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_b), BLOCKIO_SIG, 31, 1, 2,
    676, 0 },

  { 339,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2",
    0, "", offsetof(BlockIO_TemplateNIPID, x_ds2y_ds22), BLOCKIO_SIG, 0, 1, 2,
    678, 0 },

  { 340,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_d), BLOCKIO_SIG, 31, 1, 2, 680,
    0 },

  { 341,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/(epsilon_n^s)^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_ns2), BLOCKIO_SIG, 31, 1, 2,
    682, 0 },

  { 342,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_bu), BLOCKIO_SIG, 31, 1, 2,
    684, 0 },

  { 343,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_l), BLOCKIO_SIG, 31, 1, 2, 686, 0 },

  { 344,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2_e), BLOCKIO_SIG, 0, 1, 2, 688,
    0 },

  { 345,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2_k), BLOCKIO_SIG, 31, 1, 2,
    690, 0 },

  { 346,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_nt), BLOCKIO_SIG, 31, 1, 2, 692,
    0 },

  { 347,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/( )^2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_mx), BLOCKIO_SIG, 31, 1, 2, 694, 0
  },

  { 348,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_j), BLOCKIO_SIG, 31, 1, 2, 696,
    0 },

  { 349,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_b), BLOCKIO_SIG, 22, 4,
    2, 698, 0 },

  { 350,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_dj), BLOCKIO_SIG, 22, 4, 2,
    700, 0 },

  { 351,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_k), BLOCKIO_SIG, 22, 4, 2, 702, 0
  },

  { 352,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_g), BLOCKIO_SIG, 25, 2, 2,
    704, 0 },

  { 353,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_d), BLOCKIO_SIG, 25, 2, 2,
    706, 0 },

  { 354,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_i), BLOCKIO_SIG, 25, 2, 2, 708, 0 },

  { 355,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product3",
    0, "", offsetof(BlockIO_TemplateNIPID, Product3_l), BLOCKIO_SIG, 32, 2, 2,
    710, 0 },

  { 356,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_ez), BLOCKIO_SIG, 32, 2, 2, 712,
    0 },

  { 357,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_o), BLOCKIO_SIG, 32, 2, 2, 714,
    0 },

  { 358,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector4",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSelector4), BLOCKIO_SIG, 31,
    1, 2, 716, 0 },

  { 359,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_ma), BLOCKIO_SIG, 31, 1, 2,
    718, 0 },

  { 360,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide1",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide1_c), BLOCKIO_SIG, 31, 1, 2,
    720, 0 },

  { 361,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_g4), BLOCKIO_SIG, 31, 1, 2, 722,
    0 },

  { 362,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_a2), BLOCKIO_SIG, 31, 1, 2,
    724, 0 },

  { 363,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_d), BLOCKIO_SIG, 29, 2,
    2, 726, 0 },

  { 364,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_gc), BLOCKIO_SIG, 31, 1, 2,
    728, 0 },

  { 365,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/|p_d^s|^3",
    0, "", offsetof(BlockIO_TemplateNIPID, p_ds3), BLOCKIO_SIG, 0, 1, 2, 730, 0
  },

  { 366,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_f), BLOCKIO_SIG, 31, 1, 2, 732,
    0 },

  { 367,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_lk), BLOCKIO_SIG, 31, 1, 2,
    734, 0 },

  { 368,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_pz), BLOCKIO_SIG, 31, 1, 2, 736,
    0 },

  { 369,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2_pv), BLOCKIO_SIG, 31, 1, 2,
    738, 0 },

  { 370,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2_m), BLOCKIO_SIG, 0, 1, 2, 740,
    0 },

  { 371,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_pj), BLOCKIO_SIG, 31, 1, 2, 742,
    0 },

  { 372,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_jr), BLOCKIO_SIG, 31, 1,
    2, 744, 0 },

  { 373,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_km), BLOCKIO_SIG, 31, 1, 2,
    746, 0 },

  { 374,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_it), BLOCKIO_SIG, 31, 1, 2,
    748, 0 },

  { 375,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_ik), BLOCKIO_SIG, 31, 1, 2,
    750, 0 },

  { 376,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/^3//2",
    0, "", offsetof(BlockIO_TemplateNIPID, u2_o), BLOCKIO_SIG, 31, 1, 2, 752, 0
  },

  { 377,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide1",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide1_j), BLOCKIO_SIG, 31, 1, 2,
    754, 0 },

  { 378,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product3",
    0, "", offsetof(BlockIO_TemplateNIPID, Product3_o), BLOCKIO_SIG, 31, 1, 2,
    756, 0 },

  { 379,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_at), BLOCKIO_SIG, 0, 1, 2,
    758, 0 },

  { 380,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_la), BLOCKIO_SIG, 29, 2,
    2, 760, 0 },

  { 381,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide2",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide2), BLOCKIO_SIG, 29, 2, 2, 762,
    0 },

  { 382,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_g), BLOCKIO_SIG, 29, 2,
    2, 764, 0 },

  { 383,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_la), BLOCKIO_SIG, 29, 2, 2,
    766, 0 },

  { 384,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_p), BLOCKIO_SIG, 0, 1, 2,
    768, 0 },

  { 385,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide1",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide1_j0), BLOCKIO_SIG, 29, 2, 2,
    770, 0 },

  { 386,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract1",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract1_k), BLOCKIO_SIG, 29, 2, 2,
    772, 0 },

  { 387,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_kg), BLOCKIO_SIG, 0, 1, 2,
    774, 0 },

  { 388,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_c), BLOCKIO_SIG, 0, 1, 2,
    776, 0 },

  { 389,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_m), BLOCKIO_SIG, 31, 1, 2, 778, 0
  },

  { 390,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_m1), BLOCKIO_SIG, 31, 1, 2,
    780, 0 },

  { 391,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, VectorConcatenate_a), BLOCKIO_SIG, 28,
    3, 2, 782, 0 },

  { 392, "templatenipid/Main Subsystems/Control/Nonlinear PID/a_d/v_d^s/Add1", 0,
    "", offsetof(BlockIO_TemplateNIPID, Add1_c), BLOCKIO_SIG, 28, 3, 2, 784, 0 },

  { 393, "templatenipid/Main Subsystems/Control/Nonlinear PID/a_d/Product1", 0,
    "", offsetof(BlockIO_TemplateNIPID, Product1_d), BLOCKIO_SIG, 20, 3, 2, 786,
    0 },

  { 394,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateNIPID, TrigonometricFunction_o), BLOCKIO_SIG,
    0, 1, 2, 788, 0 },

  { 395,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_TemplateNIPID, TrigonometricFunction1_j),
    BLOCKIO_SIG, 0, 1, 2, 790, 0 },

  { 396,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/Derivative",
    0, "", offsetof(BlockIO_TemplateNIPID, Derivative), BLOCKIO_SIG, 0, 1, 2,
    792, 0 },

  { 397,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_pl), BLOCKIO_SIG, 25, 2, 2,
    794, 0 },

  { 398,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, VectorConcatenate_b), BLOCKIO_SIG, 20,
    3, 2, 796, 0 },

  { 399,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateNIPID, epsilon_n2_m), BLOCKIO_SIG, 31, 1, 2,
    798, 0 },

  { 400,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateNIPID, Delta2_f), BLOCKIO_SIG, 0, 1, 2, 800,
    0 },

  { 401,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Add",
    0, "", offsetof(BlockIO_TemplateNIPID, Add_pb), BLOCKIO_SIG, 31, 1, 2, 802,
    0 },

  { 402,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/sqrt",
    0, "", offsetof(BlockIO_TemplateNIPID, sqrt_d), BLOCKIO_SIG, 31, 1, 2, 804,
    0 },

  { 403,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_ht), BLOCKIO_SIG, 31, 1, 2,
    806, 0 },

  { 404,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq/Divide",
    0, "", offsetof(BlockIO_TemplateNIPID, Divide_a), BLOCKIO_SIG, 0, 1, 2, 808,
    0 },

  { 405,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_bl), BLOCKIO_SIG, 31, 1, 2,
    810, 0 },

  { 406,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, VectorConcatenate_g), BLOCKIO_SIG, 28,
    3, 2, 812, 0 },

  { 407, "templatenipid/Main Subsystems/Control/Nonlinear PID/a_d/v_d^t/Add", 0,
    "", offsetof(BlockIO_TemplateNIPID, Add_h), BLOCKIO_SIG, 28, 3, 2, 814, 0 },

  { 408, "templatenipid/Main Subsystems/Control/Nonlinear PID/a_d/Sum", 0, "",
    offsetof(BlockIO_TemplateNIPID, Sum_fd), BLOCKIO_SIG, 28, 3, 2, 816, 0 },

  { 409,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_k3), BLOCKIO_SIG, 28, 3, 2,
    818, 0 },

  { 410,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S12",
    0, "", offsetof(BlockIO_TemplateNIPID, S12), BLOCKIO_SIG, 0, 1, 2, 820, 0 },

  { 411,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S(r)",
    0, "", offsetof(BlockIO_TemplateNIPID, Sr), BLOCKIO_SIG, 24, 9, 2, 822, 0 },

  { 412,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S^T/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_ii), BLOCKIO_SIG, 24, 9,
    2, 824, 0 },

  { 413,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_kl), BLOCKIO_SIG, 28, 3, 2,
    826, 0 },

  { 414,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_mj), BLOCKIO_SIG, 28, 3, 2, 828,
    0 },

  { 415,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_dp), BLOCKIO_SIG, 28, 3, 2,
    830, 0 },

  { 416,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_bi), BLOCKIO_SIG, 28, 3, 2,
    832, 0 },

  { 417, "templatenipid/Main Subsystems/Control/Nonlinear PID/Control law/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_b), BLOCKIO_SIG, 28, 3, 2, 834, 0
  },

  { 418, "templatenipid/Main Subsystems/Control/Control Switch/tau Switch", 0,
    "", offsetof(BlockIO_TemplateNIPID, tauSwitch), BLOCKIO_SIG, 28, 3, 2, 836,
    0 },

  { 419,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Matrix Concatenate",
    0, "", offsetof(BlockIO_TemplateNIPID, MatrixConcatenate_d), BLOCKIO_SIG, 30,
    6, 2, 838, 0 },

  { 420,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Transpose/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_hoy), BLOCKIO_SIG, 33, 6,
    2, 840, 0 },

  { 421,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_c), BLOCKIO_SIG, 25, 2, 2,
    842, 0 },

  { 422,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Product3",
    0, "", offsetof(BlockIO_TemplateNIPID, Product3_e), BLOCKIO_SIG, 25, 2, 2,
    844, 0 },

  { 423,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Subtract",
    0, "", offsetof(BlockIO_TemplateNIPID, Subtract_h), BLOCKIO_SIG, 25, 2, 2,
    846, 0 },

  { 424,
    "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Product4",
    0, "", offsetof(BlockIO_TemplateNIPID, Product4_b), BLOCKIO_SIG, 25, 2, 2,
    848, 0 },

  { 425, "templatenipid/Main Subsystems/Control/Nonlinear PID/Update laws/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_en), BLOCKIO_SIG, 25, 2, 2, 850,
    0 },

  { 426, "templatenipid/Main Subsystems/Control/Nonlinear PID/zeta/Product", 0,
    "", offsetof(BlockIO_TemplateNIPID, Product_ak), BLOCKIO_SIG, 28, 3, 2, 852,
    0 },

  { 427,
    "templatenipid/Main Subsystems/Control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_TemplateNIPID, Pseudoinverse), BLOCKIO_SIG, 40, 15,
    2, 854, 0 },

  { 428,
    "templatenipid/Main Subsystems/Control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_pk), BLOCKIO_SIG, 36, 5, 2,
    856, 0 },

  { 429,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1",
    0, "", offsetof(BlockIO_TemplateNIPID, f_1tou_1), BLOCKIO_SIG, 31, 1, 2, 858,
    0 },

  { 430,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_c), BLOCKIO_SIG, 31, 1, 2, 860, 0
  },

  { 431,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391",
    0, "", offsetof(BlockIO_TemplateNIPID, f_2000391), BLOCKIO_SIG, 31, 1, 2,
    862, 0 },

  { 432,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391",
    0, "", offsetof(BlockIO_TemplateNIPID, f_2006731f_2000391), BLOCKIO_SIG, 31,
    1, 2, 864, 0 },

  { 433,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731",
    0, "", offsetof(BlockIO_TemplateNIPID, f_2006731), BLOCKIO_SIG, 31, 1, 2,
    866, 0 },

  { 434,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_iu), BLOCKIO_SIG, 31,
    1, 2, 868, 0 },

  { 435,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_d), BLOCKIO_SIG, 31, 1, 2, 870,
    0 },

  { 436,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3",
    0, "", offsetof(BlockIO_TemplateNIPID, f_3tou_3), BLOCKIO_SIG, 31, 1, 2, 872,
    0 },

  { 437,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum2",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum2), BLOCKIO_SIG, 31, 1, 2, 874, 0
  },

  { 438,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451",
    0, "", offsetof(BlockIO_TemplateNIPID, f_400451), BLOCKIO_SIG, 31, 1, 2, 876,
    0 },

  { 439,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451",
    0, "", offsetof(BlockIO_TemplateNIPID, f_400451_n), BLOCKIO_SIG, 31, 1, 2,
    878, 0 },

  { 440,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_e), BLOCKIO_SIG, 31,
    1, 2, 880, 0 },

  { 441,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum3",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum3), BLOCKIO_SIG, 31, 1, 2, 882, 0
  },

  { 442,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_TemplateNIPID, DeadZone001_k), BLOCKIO_SIG, 31, 1, 2,
    884, 0 },

  { 443,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0",
    0, "", offsetof(BlockIO_TemplateNIPID, f_50), BLOCKIO_SIG, 31, 1, 2, 886, 0
  },

  { 444,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0",
    0, "", offsetof(BlockIO_TemplateNIPID, f_50_f), BLOCKIO_SIG, 31, 1, 2, 888,
    0 },

  { 445,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_o), BLOCKIO_SIG, 31,
    1, 2, 890, 0 },

  { 446, "templatenipid/Main Subsystems/Control/Thruster allocation/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_g), BLOCKIO_SIG, 34, 7, 2,
    892, 0 },

  { 447,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error", 0,
    "", offsetof(BlockIO_TemplateNIPID, QTMIn2Error), BLOCKIO_SIG, 31, 1, 2, 894,
    0 },

  { 448,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual",
    0, "", offsetof(BlockIO_TemplateNIPID, QTMIn9Residual), BLOCKIO_SIG, 31, 1,
    2, 896, 0 },

  { 449,
    "templatenipid/Main Subsystems/Plant/Thruster setting workaround/tau Switch1",
    0, "", offsetof(BlockIO_TemplateNIPID, tauSwitch1), BLOCKIO_SIG, 34, 7, 2,
    898, 0 },

  { 450,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate1",
    0, "", offsetof(BlockIO_TemplateNIPID, VectorConcatenate1), BLOCKIO_SIG, 28,
    3, 2, 900, 0 },

  { 451,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]",
    0, "", offsetof(BlockIO_TemplateNIPID, QTMIn5zcoordmm), BLOCKIO_SIG, 31, 1,
    2, 902, 0 },

  { 452, "templatenipid/Main Subsystems/Naviagation/Input from SIT/mm2m z", 0,
    "", offsetof(BlockIO_TemplateNIPID, mm2mz), BLOCKIO_SIG, 31, 1, 2, 904, 0 },

  { 453,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]",
    0, "", offsetof(BlockIO_TemplateNIPID, QTMIn8rolldeg), BLOCKIO_SIG, 31, 1, 2,
    906, 0 },

  { 454, "templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r roll", 0,
    "", offsetof(BlockIO_TemplateNIPID, d2rroll), BLOCKIO_SIG, 31, 1, 2, 908, 0
  },

  { 455,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]",
    0, "", offsetof(BlockIO_TemplateNIPID, QTMIn7pitchdeg), BLOCKIO_SIG, 31, 1,
    2, 910, 0 },

  { 456, "templatenipid/Main Subsystems/Naviagation/Input from SIT/d2r pitch", 0,
    "", offsetof(BlockIO_TemplateNIPID, d2rpitch), BLOCKIO_SIG, 31, 1, 2, 912, 0
  },

  { 457, "templatenipid/Main Subsystems/Naviagation/Input from SIT/Derivative",
    0, "", offsetof(BlockIO_TemplateNIPID, Derivative_e), BLOCKIO_SIG, 49, 6, 2,
    914, 0 },

  { 458,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_TemplateNIPID, sintheta), BLOCKIO_SIG, 20, 3, 2, 916,
    0 },

  { 459,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_TemplateNIPID, costheta), BLOCKIO_SIG, 20, 3, 2, 918,
    0 },

  { 460,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_TemplateNIPID, R11_j), BLOCKIO_SIG, 0, 1, 2, 920, 0
  },

  { 461,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_TemplateNIPID, R12_m), BLOCKIO_SIG, 0, 1, 2, 922, 0
  },

  { 462,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_TemplateNIPID, R13), BLOCKIO_SIG, 0, 1, 2, 924, 0 },

  { 463,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_TemplateNIPID, R21_p), BLOCKIO_SIG, 0, 1, 2, 926, 0
  },

  { 464,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_TemplateNIPID, R22_c), BLOCKIO_SIG, 0, 1, 2, 928, 0
  },

  { 465,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_TemplateNIPID, R23), BLOCKIO_SIG, 0, 1, 2, 930, 0 },

  { 466,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_TemplateNIPID, R31), BLOCKIO_SIG, 0, 1, 2, 932, 0 },

  { 467,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_TemplateNIPID, R32), BLOCKIO_SIG, 0, 1, 2, 934, 0 },

  { 468,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_TemplateNIPID, R33), BLOCKIO_SIG, 0, 1, 2, 936, 0 },

  { 469,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_TemplateNIPID, Reshape9x13x3), BLOCKIO_SIG, 24, 9, 2,
    938, 0 },

  { 470, "templatenipid/Main Subsystems/Naviagation/Input from SIT/Inverse", 0,
    "", offsetof(BlockIO_TemplateNIPID, Inverse), BLOCKIO_SIG, 24, 9, 2, 940, 0
  },

  { 471,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/Matrix Concatenate2",
    0, "", offsetof(BlockIO_TemplateNIPID, MatrixConcatenate2), BLOCKIO_SIG, 53,
    36, 2, 942, 0 },

  { 472, "templatenipid/Main Subsystems/Naviagation/Input from SIT/Product", 0,
    "", offsetof(BlockIO_TemplateNIPID, Product_l3), BLOCKIO_SIG, 49, 6, 2, 944,
    0 },

  { 473, "templatenipid/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN",
    0, "", offsetof(BlockIO_TemplateNIPID, QTMIn1FN), BLOCKIO_SIG, 31, 1, 2, 946,
    0 },

  { 474,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator",
    0, "eta", offsetof(BlockIO_TemplateNIPID, eta), BLOCKIO_SIG, 20, 3, 2, 948,
    0 },

  { 475,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3",
    0, "bias", offsetof(BlockIO_TemplateNIPID, bias), BLOCKIO_SIG, 20, 3, 2, 950,
    0 },

  { 476,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_b), BLOCKIO_SIG, 0, 1, 2,
    952, 0 },

  { 477,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign_ds), BLOCKIO_SIG, 0, 1, 2, 954,
    0 },

  { 478,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_h), BLOCKIO_SIG, 0, 1, 2, 956, 0
  },

  { 479,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_js), BLOCKIO_SIG, 0, 1, 2, 958,
    0 },

  { 480,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_gw), BLOCKIO_SIG, 0, 1,
    2, 960, 0 },

  { 481,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_eo), BLOCKIO_SIG, 0, 1, 2, 962, 0
  },

  { 482,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum2",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum2_l), BLOCKIO_SIG, 20, 3, 2, 964,
    0 },

  { 483,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_TemplateNIPID, Saturation_i1), BLOCKIO_SIG, 0, 1, 2,
    966, 0 },

  { 484,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign_p), BLOCKIO_SIG, 0, 1, 2, 968, 0
  },

  { 485,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_p2), BLOCKIO_SIG, 0, 1, 2, 970,
    0 },

  { 486,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_c), BLOCKIO_SIG, 0, 1, 2, 972, 0
  },

  { 487,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_TemplateNIPID, MathFunction_if), BLOCKIO_SIG, 0, 1,
    2, 974, 0 },

  { 488,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_c0), BLOCKIO_SIG, 0, 1, 2, 976, 0
  },

  { 489,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2",
    0, "", offsetof(BlockIO_TemplateNIPID, K2), BLOCKIO_SIG, 20, 3, 2, 978, 0 },

  { 490,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3",
    0, "", offsetof(BlockIO_TemplateNIPID, K3), BLOCKIO_SIG, 20, 3, 2, 980, 0 },

  { 491,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4",
    0, "", offsetof(BlockIO_TemplateNIPID, K4), BLOCKIO_SIG, 20, 3, 2, 982, 0 },

  { 492,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row1",
    0, "", offsetof(BlockIO_TemplateNIPID, Row1), BLOCKIO_SIG, 0, 1, 2, 984, 0 },

  { 493,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row2",
    0, "", offsetof(BlockIO_TemplateNIPID, Row2), BLOCKIO_SIG, 0, 1, 2, 986, 0 },

  { 494,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row3",
    0, "", offsetof(BlockIO_TemplateNIPID, Row3), BLOCKIO_SIG, 0, 1, 2, 988, 0 },

  { 495,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_TemplateNIPID, Row1_j), BLOCKIO_SIG, 0, 1, 2, 990, 0
  },

  { 496,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_TemplateNIPID, Row2_o), BLOCKIO_SIG, 0, 1, 2, 992, 0
  },

  { 497,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_TemplateNIPID, Row3_a), BLOCKIO_SIG, 0, 1, 2, 994, 0
  },

  { 498,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_1tof_1_p1), BLOCKIO_SIG, 0, 1, 2,
    996, 0 },

  { 499,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5",
    0, "", offsetof(BlockIO_TemplateNIPID, u_205_g), BLOCKIO_SIG, 0, 1, 2, 998,
    0 },

  { 500,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2",
    0, "", offsetof(BlockIO_TemplateNIPID, u_201u_202_k), BLOCKIO_SIG, 0, 1, 2,
    1000, 0 },

  { 501,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_20_n), BLOCKIO_SIG, 0, 1, 2, 1002,
    0 },

  { 502,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_d), BLOCKIO_SIG, 0, 1,
    2, 1004, 0 },

  { 503,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3",
    0, "", offsetof(BlockIO_TemplateNIPID, u_3tof_3_d), BLOCKIO_SIG, 0, 1, 2,
    1006, 0 },

  { 504,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_401_d), BLOCKIO_SIG, 0, 1, 2, 1008,
    0 },

  { 505,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1",
    0, "", offsetof(BlockIO_TemplateNIPID, u_401_hy), BLOCKIO_SIG, 0, 1, 2, 1010,
    0 },

  { 506,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_b), BLOCKIO_SIG, 0, 1,
    2, 1012, 0 },

  { 507,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_TemplateNIPID, DeadZone001_e), BLOCKIO_SIG, 0, 1, 2,
    1014, 0 },

  { 508,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_50_j), BLOCKIO_SIG, 0, 1, 2, 1016,
    0 },

  { 509,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0",
    0, "", offsetof(BlockIO_TemplateNIPID, u_50_ns), BLOCKIO_SIG, 0, 1, 2, 1018,
    0 },

  { 510,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, MultiportSwitch_l), BLOCKIO_SIG, 0, 1,
    2, 1020, 0 },

  { 511,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_c3), BLOCKIO_SIG, 20, 3, 2,
    1022, 0 },

  { 512,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_ei), BLOCKIO_SIG, 20, 3, 2, 1024,
    0 },

  { 513,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_n), BLOCKIO_SIG, 20, 3, 2,
    1026, 0 },

  { 514,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum8",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum8), BLOCKIO_SIG, 20, 3, 2, 1028, 0
  },

  { 515,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Product",
    0, "", offsetof(BlockIO_TemplateNIPID, Product_ly), BLOCKIO_SIG, 20, 3, 2,
    1030, 0 },

  { 516,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn",
    0, "x_dot", offsetof(BlockIO_TemplateNIPID, x_dot), BLOCKIO_SIG, 0, 1, 2,
    1032, 0 },

  { 517,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn1",
    0, "y_dot", offsetof(BlockIO_TemplateNIPID, y_dot), BLOCKIO_SIG, 0, 1, 2,
    1034, 0 },

  { 518,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn2",
    0, "psi_dot", offsetof(BlockIO_TemplateNIPID, psi_dot), BLOCKIO_SIG, 0, 1, 2,
    1036, 0 },

  { 519,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum3",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum3_b), BLOCKIO_SIG, 20, 3, 2, 1038,
    0 },

  { 520,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)",
    0, "", offsetof(BlockIO_TemplateNIPID, invT_b), BLOCKIO_SIG, 20, 3, 2, 1040,
    0 },

  { 521,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum7",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum7), BLOCKIO_SIG, 20, 3, 2, 1042, 0
  },

  { 522, "templatenipid/Main Subsystems/Naviagation/Input from SIT/SIT zAI0", 0,
    "", offsetof(BlockIO_TemplateNIPID, SITzAI0), BLOCKIO_SIG, 0, 1, 2, 1044, 0
  },

  { 523, "templatenipid/Main Subsystems/Naviagation/Input from SIT/SIT zAI1", 0,
    "", offsetof(BlockIO_TemplateNIPID, SITzAI1), BLOCKIO_SIG, 0, 1, 2, 1046, 0
  },

  { 524, "templatenipid/Main Subsystems/Naviagation/Input from SIT/SIT zAI2", 0,
    "", offsetof(BlockIO_TemplateNIPID, SITzAI2), BLOCKIO_SIG, 0, 1, 2, 1048, 0
  },

  { 525, "templatenipid/Main Subsystems/Plant/Inverse", 0, "", offsetof
    (BlockIO_TemplateNIPID, Inverse_m), BLOCKIO_SIG, 24, 9, 2, 1050, 0 },

  { 526, "templatenipid/Main Subsystems/Plant/saturation/Saturation", 0, "",
    offsetof(BlockIO_TemplateNIPID, Saturation_i4), BLOCKIO_SIG, 31, 1, 2, 1052,
    0 },

  { 527, "templatenipid/Main Subsystems/Plant/saturation/Saturation1", 0, "",
    offsetof(BlockIO_TemplateNIPID, Saturation1), BLOCKIO_SIG, 31, 1, 2, 1054, 0
  },

  { 528, "templatenipid/Main Subsystems/Plant/saturation/Saturation2", 0, "",
    offsetof(BlockIO_TemplateNIPID, Saturation2), BLOCKIO_SIG, 31, 1, 2, 1056, 0
  },

  { 529, "templatenipid/Main Subsystems/Plant/saturation/plant tau_surge", 0, "",
    offsetof(BlockIO_TemplateNIPID, planttau_surge), BLOCKIO_SIG, 31, 1, 2, 1058,
    0 },

  { 530, "templatenipid/Main Subsystems/Plant/saturation/plant tau_sway", 0, "",
    offsetof(BlockIO_TemplateNIPID, planttau_sway), BLOCKIO_SIG, 31, 1, 2, 1060,
    0 },

  { 531, "templatenipid/Main Subsystems/Plant/saturation/plant tau_yaw", 0, "",
    offsetof(BlockIO_TemplateNIPID, planttau_yaw), BLOCKIO_SIG, 31, 1, 2, 1062,
    0 },

  { 532, "templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster",
    0, "", offsetof(BlockIO_TemplateNIPID, BatteryBowThruster), BLOCKIO_SIG, 0,
    1, 2, 1064, 0 },

  { 533, "templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Main", 0, "",
    offsetof(BlockIO_TemplateNIPID, BatteryMain), BLOCKIO_SIG, 0, 1, 2, 1066, 0
  },

  { 534, "templatenipid/Outputs to LabVIEW/Battery Voltage/Battery Servo", 0, "",
    offsetof(BlockIO_TemplateNIPID, BatteryServo), BLOCKIO_SIG, 0, 1, 2, 1068, 0
  },

  { 535, "templatenipid/Outputs to LabVIEW/Command/tau1", 0, "", offsetof
    (BlockIO_TemplateNIPID, tau1), BLOCKIO_SIG, 20, 3, 2, 1070, 0 },

  { 536, "templatenipid/Outputs to LabVIEW/Command/tau2", 0, "", offsetof
    (BlockIO_TemplateNIPID, tau2), BLOCKIO_SIG, 28, 3, 2, 1072, 0 },

  { 537, "templatenipid/Outputs to LabVIEW/Command/tau3", 0, "", offsetof
    (BlockIO_TemplateNIPID, tau3), BLOCKIO_SIG, 28, 3, 2, 1074, 0 },

  { 538, "templatenipid/Outputs to LabVIEW/Command/tau4", 0, "", offsetof
    (BlockIO_TemplateNIPID, tau4), BLOCKIO_SIG, 20, 3, 2, 1076, 0 },

  { 539, "templatenipid/Outputs to LabVIEW/Command/tau5", 0, "", offsetof
    (BlockIO_TemplateNIPID, tau5), BLOCKIO_SIG, 28, 3, 2, 1078, 0 },

  { 540, "templatenipid/Outputs to LabVIEW/Command/tau6", 0, "", offsetof
    (BlockIO_TemplateNIPID, tau6), BLOCKIO_SIG, 28, 3, 2, 1080, 0 },

  { 541, "templatenipid/Outputs to LabVIEW/Command/plant BT power", 0, "",
    offsetof(BlockIO_TemplateNIPID, plantBTpower), BLOCKIO_SIG, 0, 1, 2, 1082, 0
  },

  { 542, "templatenipid/Outputs to LabVIEW/Command/plant VSP speed", 0, "",
    offsetof(BlockIO_TemplateNIPID, plantVSPspeed), BLOCKIO_SIG, 0, 1, 2, 1084,
    0 },

  { 543, "templatenipid/Outputs to LabVIEW/Command/plant u_1", 0, "", offsetof
    (BlockIO_TemplateNIPID, plantu_1), BLOCKIO_SIG, 0, 1, 2, 1086, 0 },

  { 544, "templatenipid/Outputs to LabVIEW/Command/plant u_2", 0, "", offsetof
    (BlockIO_TemplateNIPID, plantu_2), BLOCKIO_SIG, 0, 1, 2, 1088, 0 },

  { 545, "templatenipid/Outputs to LabVIEW/Command/plant u_3", 0, "", offsetof
    (BlockIO_TemplateNIPID, plantu_3), BLOCKIO_SIG, 0, 1, 2, 1090, 0 },

  { 546, "templatenipid/Outputs to LabVIEW/Command/plant u_4", 0, "", offsetof
    (BlockIO_TemplateNIPID, plantu_4), BLOCKIO_SIG, 0, 1, 2, 1092, 0 },

  { 547, "templatenipid/Outputs to LabVIEW/Command/plant u_5", 0, "", offsetof
    (BlockIO_TemplateNIPID, plantu_5), BLOCKIO_SIG, 0, 1, 2, 1094, 0 },

  { 548, "templatenipid/Outputs to LabVIEW/Command/fact1", 0, "", offsetof
    (BlockIO_TemplateNIPID, fact1), BLOCKIO_SIG, 31, 1, 2, 1096, 0 },

  { 549, "templatenipid/Outputs to LabVIEW/Command/fact2", 0, "", offsetof
    (BlockIO_TemplateNIPID, fact2), BLOCKIO_SIG, 31, 1, 2, 1098, 0 },

  { 550, "templatenipid/Outputs to LabVIEW/Command/fact3", 0, "", offsetof
    (BlockIO_TemplateNIPID, fact3), BLOCKIO_SIG, 31, 1, 2, 1100, 0 },

  { 551, "templatenipid/Outputs to LabVIEW/Command/fact4", 0, "", offsetof
    (BlockIO_TemplateNIPID, fact4), BLOCKIO_SIG, 31, 1, 2, 1102, 0 },

  { 552, "templatenipid/Outputs to LabVIEW/Command/fact5", 0, "", offsetof
    (BlockIO_TemplateNIPID, fact5), BLOCKIO_SIG, 31, 1, 2, 1104, 0 },

  { 553, "templatenipid/Outputs to LabVIEW/Command/taux", 0, "", offsetof
    (BlockIO_TemplateNIPID, taux), BLOCKIO_SIG, 31, 1, 2, 1106, 0 },

  { 554, "templatenipid/Outputs to LabVIEW/Command/tauy", 0, "", offsetof
    (BlockIO_TemplateNIPID, tauy), BLOCKIO_SIG, 31, 1, 2, 1108, 0 },

  { 555, "templatenipid/Outputs to LabVIEW/Command/tauyaw", 0, "", offsetof
    (BlockIO_TemplateNIPID, tauyaw), BLOCKIO_SIG, 31, 1, 2, 1110, 0 },

  { 556, "templatenipid/Outputs to LabVIEW/Command/omega_qy", 0, "", offsetof
    (BlockIO_TemplateNIPID, omega_qy), BLOCKIO_SIG, 0, 1, 2, 1112, 0 },

  { 557, "templatenipid/Outputs to LabVIEW/Command/omegaqx", 0, "", offsetof
    (BlockIO_TemplateNIPID, omegaqx), BLOCKIO_SIG, 0, 1, 2, 1114, 0 },

  { 558, "templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]", 0, "",
    offsetof(BlockIO_TemplateNIPID, CSE1_rdegs), BLOCKIO_SIG, 0, 1, 2, 1116, 0 },

  { 559, "templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]", 0, "",
    offsetof(BlockIO_TemplateNIPID, CSE1_ums), BLOCKIO_SIG, 0, 1, 2, 1118, 0 },

  { 560, "templatenipid/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]", 0, "",
    offsetof(BlockIO_TemplateNIPID, CSE1_vms), BLOCKIO_SIG, 0, 1, 2, 1120, 0 },

  { 561, "templatenipid/Outputs to LabVIEW/Naviagtion/QS Error", 0, "", offsetof
    (BlockIO_TemplateNIPID, QSError), BLOCKIO_SIG, 31, 1, 2, 1122, 0 },

  { 562, "templatenipid/Outputs to LabVIEW/Naviagtion/QS Frame", 0, "", offsetof
    (BlockIO_TemplateNIPID, QSFrame), BLOCKIO_SIG, 31, 1, 2, 1124, 0 },

  { 563, "templatenipid/Outputs to LabVIEW/Visualization/Sum", 0, "", offsetof
    (BlockIO_TemplateNIPID, Sum_gn), BLOCKIO_SIG, 20, 3, 2, 1126, 0 },

  { 564, "templatenipid/Outputs to LabVIEW/Visualization/Sum1", 0, "", offsetof
    (BlockIO_TemplateNIPID, Sum1_i), BLOCKIO_SIG, 20, 3, 2, 1128, 0 },

  { 565, "templatenipid/Outputs to LabVIEW/Visualization/Sum2", 0, "", offsetof
    (BlockIO_TemplateNIPID, Sum2_d), BLOCKIO_SIG, 20, 3, 2, 1130, 0 },

  { 566, "templatenipid/Outputs to LabVIEW/Visualization/psi [deg]", 0, "",
    offsetof(BlockIO_TemplateNIPID, psideg), BLOCKIO_SIG, 0, 1, 2, 1132, 0 },

  { 567, "templatenipid/Outputs to LabVIEW/Visualization/psi-psid [deg]", 0, "",
    offsetof(BlockIO_TemplateNIPID, psipsiddeg), BLOCKIO_SIG, 0, 1, 2, 1134, 0 },

  { 568, "templatenipid/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]", 0,
    "", offsetof(BlockIO_TemplateNIPID, psiLOSpsideg), BLOCKIO_SIG, 0, 1, 2,
    1136, 0 },

  { 569, "templatenipid/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]", 0,
    "", offsetof(BlockIO_TemplateNIPID, psiLOSpsiddeg), BLOCKIO_SIG, 0, 1, 2,
    1138, 0 },

  { 570, "templatenipid/Outputs to LabVIEW/Visualization/psi_LOS [deg]", 0, "",
    offsetof(BlockIO_TemplateNIPID, psi_LOSdeg), BLOCKIO_SIG, 0, 1, 2, 1140, 0 },

  { 571, "templatenipid/Outputs to LabVIEW/Visualization/psid [deg]", 0, "",
    offsetof(BlockIO_TemplateNIPID, psiddeg), BLOCKIO_SIG, 0, 1, 2, 1142, 0 },

  { 572, "templatenipid/Outputs to LabVIEW/Visualization/psi_plot", 0, "",
    offsetof(BlockIO_TemplateNIPID, psi_plot), BLOCKIO_SIG, 20, 3, 2, 1144, 0 },

  { 573, "templatenipid/Outputs to LabVIEW/Visualization/qx [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, qxm), BLOCKIO_SIG, 0, 1, 2, 1146, 0 },

  { 574, "templatenipid/Outputs to LabVIEW/Visualization/qx-x [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, qxxm), BLOCKIO_SIG, 0, 1, 2, 1148, 0 },

  { 575, "templatenipid/Outputs to LabVIEW/Visualization/qx-xd [m]1", 0, "",
    offsetof(BlockIO_TemplateNIPID, qxxdm1), BLOCKIO_SIG, 0, 1, 2, 1150, 0 },

  { 576, "templatenipid/Outputs to LabVIEW/Visualization/qy [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, qym), BLOCKIO_SIG, 0, 1, 2, 1152, 0 },

  { 577, "templatenipid/Outputs to LabVIEW/Visualization/qy-y [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, qyym), BLOCKIO_SIG, 0, 1, 2, 1154, 0 },

  { 578, "templatenipid/Outputs to LabVIEW/Visualization/qy-yd [m]1", 0, "",
    offsetof(BlockIO_TemplateNIPID, qyydm1), BLOCKIO_SIG, 0, 1, 2, 1156, 0 },

  { 579, "templatenipid/Outputs to LabVIEW/Visualization/x [m]", 0, "", offsetof
    (BlockIO_TemplateNIPID, xm), BLOCKIO_SIG, 0, 1, 2, 1158, 0 },

  { 580, "templatenipid/Outputs to LabVIEW/Visualization/x-xd [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, xxdm), BLOCKIO_SIG, 0, 1, 2, 1160, 0 },

  { 581, "templatenipid/Outputs to LabVIEW/Visualization/xd [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, xdm), BLOCKIO_SIG, 0, 1, 2, 1162, 0 },

  { 582, "templatenipid/Outputs to LabVIEW/Visualization/x_plot", 0, "",
    offsetof(BlockIO_TemplateNIPID, x_plot), BLOCKIO_SIG, 20, 3, 2, 1164, 0 },

  { 583, "templatenipid/Outputs to LabVIEW/Visualization/y [m]", 0, "", offsetof
    (BlockIO_TemplateNIPID, ym), BLOCKIO_SIG, 0, 1, 2, 1166, 0 },

  { 584, "templatenipid/Outputs to LabVIEW/Visualization/y-yd [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, yydm), BLOCKIO_SIG, 0, 1, 2, 1168, 0 },

  { 585, "templatenipid/Outputs to LabVIEW/Visualization/yd [m]", 0, "",
    offsetof(BlockIO_TemplateNIPID, ydm), BLOCKIO_SIG, 0, 1, 2, 1170, 0 },

  { 586, "templatenipid/Outputs to LabVIEW/Visualization/y_plot", 0, "",
    offsetof(BlockIO_TemplateNIPID, y_plot), BLOCKIO_SIG, 20, 3, 2, 1172, 0 },

  { 587, "templatenipid/Outputs to LabVIEW/Visualization/splot", 0, "", offsetof
    (BlockIO_TemplateNIPID, splot), BLOCKIO_SIG, 0, 1, 2, 1174, 0 },

  { 588,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator",
    0, "", offsetof(BlockIO_TemplateNIPID, Integrator_e), BLOCKIO_SIG, 20, 3, 2,
    1176, 0 },

  { 589,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator1",
    0, "", offsetof(BlockIO_TemplateNIPID, Integrator1_o), BLOCKIO_SIG, 20, 3, 2,
    1178, 0 },

  { 590,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11",
    0, "", offsetof(BlockIO_TemplateNIPID, R11_c), BLOCKIO_SIG, 0, 1, 2, 1180, 0
  },

  { 591,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21",
    0, "", offsetof(BlockIO_TemplateNIPID, R21_c), BLOCKIO_SIG, 0, 1, 2, 1182, 0
  },

  { 592,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12",
    0, "", offsetof(BlockIO_TemplateNIPID, R12_j), BLOCKIO_SIG, 0, 1, 2, 1184, 0
  },

  { 593,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22",
    0, "", offsetof(BlockIO_TemplateNIPID, R22_f), BLOCKIO_SIG, 0, 1, 2, 1186, 0
  },

  { 594,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)",
    0, "", offsetof(BlockIO_TemplateNIPID, Rpsi_o), BLOCKIO_SIG, 24, 9, 2, 1188,
    0 },

  { 595,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product1",
    0, "", offsetof(BlockIO_TemplateNIPID, Product1_bo), BLOCKIO_SIG, 20, 3, 2,
    1190, 0 },

  { 596,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_mk), BLOCKIO_SIG, 20, 3, 2, 1192,
    0 },

  { 597,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product2",
    0, "", offsetof(BlockIO_TemplateNIPID, Product2_b), BLOCKIO_SIG, 20, 3, 2,
    1194, 0 },

  { 598,
    "templatenipid/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product3",
    0, "", offsetof(BlockIO_TemplateNIPID, Product3_d), BLOCKIO_SIG, 20, 3, 2,
    1196, 0 },

  { 599,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1198, 0 },

  { 600,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2",
    0, "", offsetof(BlockIO_TemplateNIPID, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1200, 0 },

  { 601, "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Add", 0,
    "", offsetof(BlockIO_TemplateNIPID, Add_ld), BLOCKIO_SIG, 0, 1, 2, 1202, 0 },

  { 602,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1204, 0 },

  { 603,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2",
    0, "", offsetof(BlockIO_TemplateNIPID, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1206, 0 },

  { 604, "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg", 0,
    "", offsetof(BlockIO_TemplateNIPID, Neg), BLOCKIO_SIG, 0, 1, 2, 1208, 0 },

  { 605, "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_el), BLOCKIO_SIG, 0, 1, 2, 1210,
    0 },

  { 606, "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum2",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum2_b), BLOCKIO_SIG, 0, 1, 2, 1212,
    0 },

  { 607,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch_f), BLOCKIO_SIG, 0, 1, 2, 1214,
    0 },

  { 608,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch2",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch2_d), BLOCKIO_SIG, 0, 1, 2,
    1216, 0 },

  { 609,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch_g), BLOCKIO_SIG, 0, 1, 2, 1218,
    0 },

  { 610,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch2",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch2_j), BLOCKIO_SIG, 0, 1, 2,
    1220, 0 },

  { 611,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch_a), BLOCKIO_SIG, 0, 1, 2, 1222,
    0 },

  { 612,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch2",
    0, "", offsetof(BlockIO_TemplateNIPID, Switch2_a), BLOCKIO_SIG, 0, 1, 2,
    1224, 0 },

  { 613,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sign",
    0, "", offsetof(BlockIO_TemplateNIPID, Sign_e), BLOCKIO_SIG, 0, 1, 2, 1226,
    0 },

  { 614,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product1",
    0, "Port VPS_X", offsetof(BlockIO_TemplateNIPID, PortVPS_X), BLOCKIO_SIG, 0,
    1, 2, 1228, 0 },

  { 615,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x",
    0, "Port VPS_X", offsetof(BlockIO_TemplateNIPID, PortVPS_X_d), BLOCKIO_SIG,
    0, 1, 2, 1230, 0 },

  { 616,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product2",
    0, "Port VSP_Y", offsetof(BlockIO_TemplateNIPID, PortVSP_Y), BLOCKIO_SIG, 0,
    1, 2, 1232, 0 },

  { 617,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y",
    0, "Port VSP_Y", offsetof(BlockIO_TemplateNIPID, PortVSP_Y_g), BLOCKIO_SIG,
    0, 1, 2, 1234, 0 },

  { 618,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product3",
    0, "Starboard VSP_X", offsetof(BlockIO_TemplateNIPID, StarboardVSP_X),
    BLOCKIO_SIG, 0, 1, 2, 1236, 0 },

  { 619,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product4",
    0, "Starboard VSP_Y", offsetof(BlockIO_TemplateNIPID, StarboardVSP_Y),
    BLOCKIO_SIG, 0, 1, 2, 1238, 0 },

  { 620,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1",
    0, "", offsetof(BlockIO_TemplateNIPID, Servo1), BLOCKIO_SIG, 0, 1, 2, 1240,
    0 },

  { 621,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2",
    0, "", offsetof(BlockIO_TemplateNIPID, Servo2), BLOCKIO_SIG, 0, 1, 2, 1242,
    0 },

  { 622,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3",
    0, "", offsetof(BlockIO_TemplateNIPID, Servo3), BLOCKIO_SIG, 0, 1, 2, 1244,
    0 },

  { 623,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4",
    0, "", offsetof(BlockIO_TemplateNIPID, Servo4), BLOCKIO_SIG, 0, 1, 2, 1246,
    0 },

  { 624,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2,
    1248, 0 },

  { 625,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_di), BLOCKIO_SIG, 0, 1, 2, 1250,
    0 },

  { 626,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port",
    0, "", offsetof(BlockIO_TemplateNIPID, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 1252,
    0 },

  { 627,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard",
    0, "", offsetof(BlockIO_TemplateNIPID, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2,
    1254, 0 },

  { 628,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12",
    0, "", offsetof(BlockIO_TemplateNIPID, S12_a), BLOCKIO_SIG, 31, 1, 2, 1256,
    0 },

  { 629,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S_2(psi_d^s^2)",
    0, "", offsetof(BlockIO_TemplateNIPID, S_2psi_ds2), BLOCKIO_SIG, 22, 4, 2,
    1258, 0 },

  { 630,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12",
    0, "", offsetof(BlockIO_TemplateNIPID, S12_ao), BLOCKIO_SIG, 31, 1, 2, 1260,
    0 },

  { 631,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S_2(psi_d^s)",
    0, "", offsetof(BlockIO_TemplateNIPID, S_2psi_ds), BLOCKIO_SIG, 22, 4, 2,
    1262, 0 },

  { 632,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R11",
    0, "", offsetof(BlockIO_TemplateNIPID, R11_jo), BLOCKIO_SIG, 0, 1, 2, 1264,
    0 },

  { 633,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R21",
    0, "", offsetof(BlockIO_TemplateNIPID, R21_m), BLOCKIO_SIG, 0, 1, 2, 1266, 0
  },

  { 634,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12",
    0, "", offsetof(BlockIO_TemplateNIPID, R12_ml), BLOCKIO_SIG, 0, 1, 2, 1268,
    0 },

  { 635,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22",
    0, "", offsetof(BlockIO_TemplateNIPID, R22_cv), BLOCKIO_SIG, 0, 1, 2, 1270,
    0 },

  { 636,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R_2(psi_d)",
    0, "", offsetof(BlockIO_TemplateNIPID, R_2psi_d), BLOCKIO_SIG, 22, 4, 2,
    1272, 0 },

  { 637,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_f), BLOCKIO_SIG, 15, 1, 2, 1274,
    0 },

  { 638,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_ku), BLOCKIO_SIG, 15, 1, 2, 1276,
    0 },

  { 639,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_pm), BLOCKIO_SIG, 15, 1, 2, 1278,
    0 },

  { 640,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_h), BLOCKIO_SIG, 15, 1, 2, 1280,
    0 },

  { 641,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_em), BLOCKIO_SIG, 15, 1, 2, 1282,
    0 },

  { 642,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_h), BLOCKIO_SIG, 15, 1, 2, 1284,
    0 },

  { 643,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_fd3), BLOCKIO_SIG, 15, 1, 2, 1286,
    0 },

  { 644,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_ab), BLOCKIO_SIG, 15, 1, 2,
    1288, 0 },

  { 645,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_hr), BLOCKIO_SIG, 15, 1, 2, 1290,
    0 },

  { 646,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_j), BLOCKIO_SIG, 15, 1, 2, 1292,
    0 },

  { 647,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_o), BLOCKIO_SIG, 15, 1, 2, 1294,
    0 },

  { 648,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_ca), BLOCKIO_SIG, 15, 1, 2, 1296,
    0 },

  { 649,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_l), BLOCKIO_SIG, 15, 1, 2, 1298,
    0 },

  { 650,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_j), BLOCKIO_SIG, 15, 1, 2, 1300,
    0 },

  { 651,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_fl), BLOCKIO_SIG, 38, 1, 2,
    1302, 0 },

  { 652,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_bs), BLOCKIO_SIG, 38, 1, 2, 1304,
    0 },

  { 653,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_bp), BLOCKIO_SIG, 38, 1, 2, 1306,
    0 },

  { 654,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_lm), BLOCKIO_SIG, 38, 1, 2, 1308,
    0 },

  { 655,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_ep), BLOCKIO_SIG, 38, 1, 2, 1310,
    0 },

  { 656,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_g), BLOCKIO_SIG, 38, 1, 2, 1312,
    0 },

  { 657,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_ms), BLOCKIO_SIG, 38, 1, 2, 1314,
    0 },

  { 658,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_n), BLOCKIO_SIG, 15, 1, 2, 1316,
    0 },

  { 659,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_lo), BLOCKIO_SIG, 15, 1, 2, 1318,
    0 },

  { 660,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_n), BLOCKIO_SIG, 15, 1, 2, 1320,
    0 },

  { 661,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_mo), BLOCKIO_SIG, 15, 1, 2, 1322,
    0 },

  { 662,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain_ji), BLOCKIO_SIG, 15, 1, 2, 1324,
    0 },

  { 663,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_TemplateNIPID, Gain1_i), BLOCKIO_SIG, 15, 1, 2, 1326,
    0 },

  { 664,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum_a), BLOCKIO_SIG, 15, 1, 2, 1328,
    0 },

  { 665,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare), BLOCKIO_SIG, 3, 1, 2, 1330,
    0 },

  { 666,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_i), BLOCKIO_SIG, 3, 1, 2,
    1332, 0 },

  { 667,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_g), BLOCKIO_SIG, 3, 1, 2,
    1334, 0 },

  { 668,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_k), BLOCKIO_SIG, 3, 1, 2, 1336,
    0 },

  { 669,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_l), BLOCKIO_SIG, 3, 1, 2,
    1338, 0 },

  { 670,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_la), BLOCKIO_SIG, 3, 1, 2,
    1340, 0 },

  { 671,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_it), BLOCKIO_SIG, 3, 1, 2,
    1342, 0 },

  { 672,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_o), BLOCKIO_SIG, 3, 1, 2,
    1344, 0 },

  { 673,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_le), BLOCKIO_SIG, 3, 1, 2,
    1346, 0 },

  { 674,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_k), BLOCKIO_SIG, 3, 1, 2,
    1348, 0 },

  { 675,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_f), BLOCKIO_SIG, 3, 1, 2,
    1350, 0 },

  { 676,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_b), BLOCKIO_SIG, 3, 1, 2,
    1352, 0 },

  { 677,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_ii), BLOCKIO_SIG, 3, 1, 2,
    1354, 0 },

  { 678,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_kv), BLOCKIO_SIG, 3, 1, 2, 1356,
    0 },

  { 679,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_h), BLOCKIO_SIG, 3, 1, 2,
    1358, 0 },

  { 680,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_l3), BLOCKIO_SIG, 3, 1, 2,
    1360, 0 },

  { 681,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_e), BLOCKIO_SIG, 3, 1, 2,
    1362, 0 },

  { 682,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_m), BLOCKIO_SIG, 3, 1, 2,
    1364, 0 },

  { 683,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_iu), BLOCKIO_SIG, 3, 1, 2,
    1366, 0 },

  { 684,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_kv), BLOCKIO_SIG, 3, 1, 2,
    1368, 0 },

  { 685,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_ku), BLOCKIO_SIG, 37, 1, 2,
    1370, 0 },

  { 686,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_e2), BLOCKIO_SIG, 37, 1, 2,
    1372, 0 },

  { 687,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_kb), BLOCKIO_SIG, 37, 1, 2,
    1374, 0 },

  { 688,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_m), BLOCKIO_SIG, 37, 1, 2, 1376,
    0 },

  { 689,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_ik), BLOCKIO_SIG, 37, 1, 2,
    1378, 0 },

  { 690,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_e5), BLOCKIO_SIG, 37, 1, 2,
    1380, 0 },

  { 691,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_a), BLOCKIO_SIG, 37, 1, 2,
    1382, 0 },

  { 692,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_km), BLOCKIO_SIG, 37, 1, 2,
    1384, 0 },

  { 693,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_l4), BLOCKIO_SIG, 37, 1, 2,
    1386, 0 },

  { 694,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_og), BLOCKIO_SIG, 37, 1, 2,
    1388, 0 },

  { 695,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_by), BLOCKIO_SIG, 3, 1, 2,
    1390, 0 },

  { 696,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_l2), BLOCKIO_SIG, 3, 1, 2,
    1392, 0 },

  { 697,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_hq), BLOCKIO_SIG, 3, 1, 2,
    1394, 0 },

  { 698,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_TemplateNIPID, Sum1_a), BLOCKIO_SIG, 3, 1, 2, 1396,
    0 },

  { 699,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_n), BLOCKIO_SIG, 3, 1, 2,
    1398, 0 },

  { 700,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_lj), BLOCKIO_SIG, 3, 1, 2,
    1400, 0 },

  { 701,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_p), BLOCKIO_SIG, 3, 1, 2,
    1402, 0 },

  { 702,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_fg), BLOCKIO_SIG, 3, 1, 2,
    1404, 0 },

  { 703,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_c), BLOCKIO_SIG, 3, 1, 2,
    1406, 0 },

  { 704,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_TemplateNIPID, Compare_kd), BLOCKIO_SIG, 3, 1, 2,
    1408, 0 },

  { 705,
    "templatenipid/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_TemplateNIPID, LogicalOperator), BLOCKIO_SIG, 8, 1,
    2, 1410, 0 },

  { 706,
    "templatenipid/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_TemplateNIPID, LogicalOperator_n), BLOCKIO_SIG, 8, 1,
    2, 1412, 0 },

  { 707,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateNIPID, LowerRelop1), BLOCKIO_SIG, 8, 1, 2,
    1414, 0 },

  { 708,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/UpperRelop",
    0, "", offsetof(BlockIO_TemplateNIPID, UpperRelop), BLOCKIO_SIG, 8, 1, 2,
    1416, 0 },

  { 709,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateNIPID, LowerRelop1_j), BLOCKIO_SIG, 8, 1, 2,
    1418, 0 },

  { 710,
    "templatenipid/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/UpperRelop",
    0, "", offsetof(BlockIO_TemplateNIPID, UpperRelop_p), BLOCKIO_SIG, 8, 1, 2,
    1420, 0 },

  { 711,
    "templatenipid/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_TemplateNIPID, LogicalOperator_g), BLOCKIO_SIG, 39,
    1, 2, 1422, 0 },

  { 712,
    "templatenipid/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_TemplateNIPID, LogicalOperator_j), BLOCKIO_SIG, 8, 1,
    2, 1424, 0 },

  { 713,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateNIPID, LowerRelop1_g), BLOCKIO_SIG, 8, 1, 2,
    1426, 0 },

  { 714,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_TemplateNIPID, UpperRelop_p1), BLOCKIO_SIG, 8, 1, 2,
    1428, 0 },

  { 715,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateNIPID, LowerRelop1_n), BLOCKIO_SIG, 8, 1, 2,
    1430, 0 },

  { 716,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/UpperRelop",
    0, "", offsetof(BlockIO_TemplateNIPID, UpperRelop_k), BLOCKIO_SIG, 8, 1, 2,
    1432, 0 },

  { 717,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateNIPID, LowerRelop1_b), BLOCKIO_SIG, 8, 1, 2,
    1434, 0 },

  { 718,
    "templatenipid/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/UpperRelop",
    0, "", offsetof(BlockIO_TemplateNIPID, UpperRelop_c), BLOCKIO_SIG, 8, 1, 2,
    1436, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
  1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 9, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
  3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 1, 1,
  2, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2,
  1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
  2, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 3, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 3, 3, 3, 3, 3, 1, 3, 1, 3, 1,
  3, 1, 3, 1, 3, 1, 3, 2, 2, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 1, 5, 3, 5, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 1, 7, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 6, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 3, 3, 3, 3, 6, 6, 1, 6, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 3, 1, 3,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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

static char* NI_CompiledModelName = "templatenipid";
static char* NI_CompiledModelVersion = "1.113";
static char* NI_CompiledModelDateTime = "Sun Mar 30 14:31:24 2014";

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
   The undef allows us to access the real TemplateNIPID_P
   In the rest of the code TemplateNIPID_P is redefine to be the read-side
   of rtParameter.
 */
#undef TemplateNIPID_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &TemplateNIPID_P, sizeof(Parameters_TemplateNIPID));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka TemplateNIPID_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_TemplateNIPID));
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
             (Parameters_TemplateNIPID));

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
           (Parameters_TemplateNIPID));
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

#endif                                 // of NI_ROOTMODEL_TemplateNIPID
