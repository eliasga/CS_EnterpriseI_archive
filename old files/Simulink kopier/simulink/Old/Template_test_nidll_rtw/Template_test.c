/*
 * Template_test.c
 *
 * Real-Time Workshop code generation for Simulink model "Template_test.mdl".
 *
 * Model Version              : 1.13
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Thu Mar 20 15:07:33 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Template_test.h"
#include "Template_test_private.h"

/* Block signals (auto storage) */
BlockIO_Template_test Template_test_B;

/* Continuous states */
ContinuousStates_Template_test Template_test_X;

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
D_Work_Template_test Template_test_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_Template_test Template_test_PrevZCSigState;

/* Real-time model */
RT_MODEL_Template_test Template_test_M_;
RT_MODEL_Template_test *Template_test_M = &Template_test_M_;

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
  Template_test_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  Template_test_output(0);
  Template_test_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE5_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  Template_test_output(0);
  Template_test_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE5_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  Template_test_output(0);
  Template_test_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++)
    hB[i] = h * rt_ODE5_B[3][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  Template_test_output(0);
  Template_test_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++)
    hB[i] = h * rt_ODE5_B[4][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  Template_test_output(0);
  Template_test_derivatives();

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
void Template_test_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Template_test_M)) {
    Template_test_M->Timing.t[0] = rtsiGetT(&Template_test_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Template_test_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&Template_test_M->solverInfo,
                          ((Template_test_M->Timing.clockTick0+1)*
      Template_test_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp;
    real_T tmp_0[7];
    int32_T i;
    real_T tmp_1[18];
    real_T tmp_2[9];
    real_T tmp_3[4];
    real_T tmp_4[6];
    int32_T tmp_5;
    real_T tmp_6[3];
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Reshape: '<S9>/[3x3]' incorporates:
       *  Constant: '<S4>/K_d_Surge'
       *  Constant: '<S4>/K_d_Sway'
       *  Constant: '<S4>/K_d_Yaw'
       *  Constant: '<S9>/12'
       *  Constant: '<S9>/13'
       *  Constant: '<S9>/21'
       *  Constant: '<S9>/23'
       *  Constant: '<S9>/31'
       *  Constant: '<S9>/32'
       */
      Template_test_B.ux3[0] = Template_test_P.K_d_Surge_Value;
      Template_test_B.ux3[1] = Template_test_P.u_Value_g;
      Template_test_B.ux3[2] = Template_test_P.u_Value_a;
      Template_test_B.ux3[3] = Template_test_P.u_Value;
      Template_test_B.ux3[4] = Template_test_P.K_d_Sway_Value;
      Template_test_B.ux3[5] = Template_test_P.u_Value_mz;
      Template_test_B.ux3[6] = Template_test_P.u_Value_m;
      Template_test_B.ux3[7] = Template_test_P.u_Value_e;
      Template_test_B.ux3[8] = Template_test_P.K_d_Yaw_Value;

      /* Reshape: '<S10>/[3x3]' incorporates:
       *  Constant: '<S10>/12'
       *  Constant: '<S10>/13'
       *  Constant: '<S10>/21'
       *  Constant: '<S10>/23'
       *  Constant: '<S10>/31'
       *  Constant: '<S10>/32'
       *  Constant: '<S4>/K_i_Surge'
       *  Constant: '<S4>/K_i_Sway'
       *  Constant: '<S4>/K_i_Yaw'
       */
      Template_test_B.ux3_g[0] = Template_test_P.K_i_Surge_Value;
      Template_test_B.ux3_g[1] = Template_test_P.u_Value_n2;
      Template_test_B.ux3_g[2] = Template_test_P.u_Value_gv;
      Template_test_B.ux3_g[3] = Template_test_P.u_Value_f;
      Template_test_B.ux3_g[4] = Template_test_P.K_i_Sway_Value;
      Template_test_B.ux3_g[5] = Template_test_P.u_Value_k;
      Template_test_B.ux3_g[6] = Template_test_P.u_Value_n;
      Template_test_B.ux3_g[7] = Template_test_P.u_Value_j;
      Template_test_B.ux3_g[8] = Template_test_P.K_i_Yaw_Value;

      /* Reshape: '<S11>/[3x3]' incorporates:
       *  Constant: '<S11>/12'
       *  Constant: '<S11>/13'
       *  Constant: '<S11>/21'
       *  Constant: '<S11>/23'
       *  Constant: '<S11>/31'
       *  Constant: '<S11>/32'
       *  Constant: '<S4>/K_p_Surge'
       *  Constant: '<S4>/K_p_Sway'
       *  Constant: '<S4>/K_p_Yaw'
       */
      Template_test_B.ux3_f[0] = Template_test_P.K_p_Surge_Value;
      Template_test_B.ux3_f[1] = Template_test_P.u_Value_el;
      Template_test_B.ux3_f[2] = Template_test_P.u_Value_jw;
      Template_test_B.ux3_f[3] = Template_test_P.u_Value_i;
      Template_test_B.ux3_f[4] = Template_test_P.K_p_Sway_Value;
      Template_test_B.ux3_f[5] = Template_test_P.u_Value_n4;
      Template_test_B.ux3_f[6] = Template_test_P.u_Value_l;
      Template_test_B.ux3_f[7] = Template_test_P.u_Value_d;
      Template_test_B.ux3_f[8] = Template_test_P.K_p_Yaw_Value;

      /* Constant: '<S4>/Reset integrator' */
      Template_test_B.Resetintegrator = Template_test_P.Resetintegrator_Value;

      /* Gain: '<S13>/Gain1' incorporates:
       *  Constant: '<S12>/psi_d [deg]'
       */
      Template_test_B.Gain1 = Template_test_P.Gain1_Gain *
        Template_test_P.psi_ddeg_Value;

      /* Reshape: '<S14>/[2x2]' incorporates:
       *  Constant: '<S14>/12'
       *  Constant: '<S14>/21'
       *  Constant: '<S5>/Gamma_q_Surge'
       *  Constant: '<S5>/Gamma_q_Sway'
       */
      Template_test_B.ux2[0] = Template_test_P.Gamma_q_Surge_Value;
      Template_test_B.ux2[1] = Template_test_P.u_Value_ab;
      Template_test_B.ux2[2] = Template_test_P.u_Value_p;
      Template_test_B.ux2[3] = Template_test_P.Gamma_q_Sway_Value;

      /* Constant: '<S5>/Initial q_x' */
      Template_test_B.Initialq_x = Template_test_P.Initialq_x_Value;

      /* Constant: '<S5>/Initial q_y' */
      Template_test_B.Initialq_y = Template_test_P.Initialq_y_Value;

      /* Constant: '<S5>/Initial s' */
      Template_test_B.Initials = Template_test_P.Initials_Value;

      /* Reshape: '<S15>/[3x3]' incorporates:
       *  Constant: '<S15>/12'
       *  Constant: '<S15>/13'
       *  Constant: '<S15>/21'
       *  Constant: '<S15>/23'
       *  Constant: '<S15>/31'
       *  Constant: '<S15>/32'
       *  Constant: '<S5>/K_d_Surge'
       *  Constant: '<S5>/K_d_Sway'
       *  Constant: '<S5>/K_d_Yaw'
       */
      Template_test_B.ux3_n[0] = Template_test_P.K_d_Surge_Value_j;
      Template_test_B.ux3_n[1] = Template_test_P.u_Value_ni;
      Template_test_B.ux3_n[2] = Template_test_P.u_Value_jr;
      Template_test_B.ux3_n[3] = Template_test_P.u_Value_pk;
      Template_test_B.ux3_n[4] = Template_test_P.K_d_Sway_Value_a;
      Template_test_B.ux3_n[5] = Template_test_P.u_Value_gl;
      Template_test_B.ux3_n[6] = Template_test_P.u_Value_n21;
      Template_test_B.ux3_n[7] = Template_test_P.u_Value_pe;
      Template_test_B.ux3_n[8] = Template_test_P.K_d_Yaw_Value_i;

      /* Reshape: '<S16>/[3x3]' incorporates:
       *  Constant: '<S16>/12'
       *  Constant: '<S16>/13'
       *  Constant: '<S16>/21'
       *  Constant: '<S16>/23'
       *  Constant: '<S16>/31'
       *  Constant: '<S16>/32'
       *  Constant: '<S5>/K_i_Surge'
       *  Constant: '<S5>/K_i_Sway'
       *  Constant: '<S5>/K_i_Yaw'
       */
      Template_test_B.ux3_d[0] = Template_test_P.K_i_Surge_Value_o;
      Template_test_B.ux3_d[1] = Template_test_P.u_Value_mv;
      Template_test_B.ux3_d[2] = Template_test_P.u_Value_in;
      Template_test_B.ux3_d[3] = Template_test_P.u_Value_c;
      Template_test_B.ux3_d[4] = Template_test_P.K_i_Sway_Value_o;
      Template_test_B.ux3_d[5] = Template_test_P.u_Value_la;
      Template_test_B.ux3_d[6] = Template_test_P.u_Value_kr;
      Template_test_B.ux3_d[7] = Template_test_P.u_Value_f2;
      Template_test_B.ux3_d[8] = Template_test_P.K_i_Yaw_Value_o;

      /* Reshape: '<S17>/[3x3]' incorporates:
       *  Constant: '<S17>/12'
       *  Constant: '<S17>/13'
       *  Constant: '<S17>/21'
       *  Constant: '<S17>/23'
       *  Constant: '<S17>/31'
       *  Constant: '<S17>/32'
       *  Constant: '<S5>/K_p_Surge'
       *  Constant: '<S5>/K_p_Sway'
       *  Constant: '<S5>/K_p_Yaw'
       */
      Template_test_B.ux3_b[0] = Template_test_P.K_p_Surge_Value_g;
      Template_test_B.ux3_b[1] = Template_test_P.u_Value_lf;
      Template_test_B.ux3_b[2] = Template_test_P.u_Value_ft;
      Template_test_B.ux3_b[3] = Template_test_P.u_Value_ex;
      Template_test_B.ux3_b[4] = Template_test_P.K_p_Sway_Value_e;
      Template_test_B.ux3_b[5] = Template_test_P.u_Value_db;
      Template_test_B.ux3_b[6] = Template_test_P.u_Value_ph;
      Template_test_B.ux3_b[7] = Template_test_P.u_Value_exm;
      Template_test_B.ux3_b[8] = Template_test_P.K_p_Yaw_Value_c;

      /* Constant: '<S6>/Initial psi [rad]' */
      Template_test_B.Initialpsirad = Template_test_P.Initialpsirad_Value;

      /* Constant: '<S6>/Initial x [m]' */
      Template_test_B.Initialxm = Template_test_P.Initialxm_Value;

      /* Constant: '<S6>/Initial y [m]' */
      Template_test_B.Initialym = Template_test_P.Initialym_Value;

      /* Constant: '<S6>/Initial r [rad//s]' */
      Template_test_B.Initialrrads = Template_test_P.Initialrrads_Value;

      /* Constant: '<S6>/Initial u [m//s]' */
      Template_test_B.Initialums = Template_test_P.Initialums_Value;

      /* Constant: '<S6>/Initial v [m//s]' */
      Template_test_B.Initialvms = Template_test_P.Initialvms_Value;

      /* Gain: '<S8>/ScalingLX' incorporates:
       *  Constant: '<S8>/AS_LX [-] '
       */
      Template_test_B.xpositionofleftanalogstick11 =
        Template_test_P.ScalingLX_Gain * Template_test_P.AS_LX_Value;

      /* Gain: '<S8>/ScalingLY' incorporates:
       *  Constant: '<S8>/AS_LY [-]'
       */
      Template_test_B.ypositionofleftanalogstick11 =
        Template_test_P.ScalingLY_Gain * Template_test_P.AS_LY_Value;

      /* Gain: '<S8>/Scaling_RX' incorporates:
       *  Constant: '<S8>/AS_RX [-]'
       */
      Template_test_B.xpositionofrightanalogstick11 =
        Template_test_P.Scaling_RX_Gain * Template_test_P.AS_RX_Value;

      /* Gain: '<S8>/ScalingRY' incorporates:
       *  Constant: '<S8>/AS_RY [-]'
       */
      Template_test_B.ypositionofrightanalogstick11 =
        Template_test_P.ScalingRY_Gain * Template_test_P.AS_RY_Value;

      /* Gain: '<S28>/-l_x1' incorporates:
       *  Constant: '<S28>/l_x1'
       */
      Template_test_B.l_x1 = Template_test_P.l_x1_Gain *
        Template_test_P.l_x1_Value;

      /* Gain: '<S28>/-l_x2' incorporates:
       *  Constant: '<S28>/l_x2'
       */
      Template_test_B.l_x2 = Template_test_P.l_x2_Gain *
        Template_test_P.l_x2_Value;

      /* Gain: '<S28>/-l_y2' incorporates:
       *  Constant: '<S28>/l_y2'
       */
      Template_test_B.l_y2 = Template_test_P.l_y2_Gain *
        Template_test_P.l_y2_Value;

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
      Template_test_B.x5[0] = Template_test_P.B_11_Value;
      Template_test_B.x5[1] = Template_test_P.B_21_Value;
      Template_test_B.x5[2] = Template_test_P.l_y1_Value;
      Template_test_B.x5[3] = Template_test_P.B_12_Value;
      Template_test_B.x5[4] = Template_test_P.B_22_Value;
      Template_test_B.x5[5] = Template_test_B.l_x1;
      Template_test_B.x5[6] = Template_test_P.B_13_Value;
      Template_test_B.x5[7] = Template_test_P.B_23_Value;
      Template_test_B.x5[8] = Template_test_B.l_y2;
      Template_test_B.x5[9] = Template_test_P.B_14_Value;
      Template_test_B.x5[10] = Template_test_P.B_24_Value;
      Template_test_B.x5[11] = Template_test_B.l_x2;
      Template_test_B.x5[12] = Template_test_P.B_15_Value;
      Template_test_B.x5[13] = Template_test_P.B_25_Value;
      Template_test_B.x5[14] = Template_test_P.l_x3_Value;

      /* Gain: '<S27>/-N_r' incorporates:
       *  Constant: '<S27>/N_r'
       */
      Template_test_B.N_r = Template_test_P.N_r_Gain * Template_test_P.N_r_Value;

      /* Gain: '<S27>/-N_v' incorporates:
       *  Constant: '<S27>/N_v'
       */
      Template_test_B.N_v = Template_test_P.N_v_Gain * Template_test_P.N_v_Value;

      /* Gain: '<S27>/-X_u' incorporates:
       *  Constant: '<S27>/X_u'
       */
      Template_test_B.X_u = Template_test_P.X_u_Gain * Template_test_P.X_u_Value;

      /* Gain: '<S27>/-Y_v' incorporates:
       *  Constant: '<S27>/Y_v'
       */
      Template_test_B.Y_v = Template_test_P.Y_v_Gain * Template_test_P.Y_v_Value;

      /* Gain: '<S27>/-Y_vr' incorporates:
       *  Constant: '<S27>/Y_r'
       */
      Template_test_B.Y_vr = Template_test_P.Y_vr_Gain *
        Template_test_P.Y_r_Value;

      /* Reshape: '<S27>/Linear Dampning matrix' incorporates:
       *  Constant: '<S27>/D_L_12'
       *  Constant: '<S27>/D_L_13'
       *  Constant: '<S27>/D_L_21'
       *  Constant: '<S27>/D_L_31'
       */
      Template_test_B.LinearDampningmatrix[0] = Template_test_B.X_u;
      Template_test_B.LinearDampningmatrix[1] = Template_test_P.D_L_21_Value;
      Template_test_B.LinearDampningmatrix[2] = Template_test_P.D_L_31_Value;
      Template_test_B.LinearDampningmatrix[3] = Template_test_P.D_L_12_Value;
      Template_test_B.LinearDampningmatrix[4] = Template_test_B.Y_v;
      Template_test_B.LinearDampningmatrix[5] = Template_test_B.N_v;
      Template_test_B.LinearDampningmatrix[6] = Template_test_P.D_L_13_Value;
      Template_test_B.LinearDampningmatrix[7] = Template_test_B.Y_vr;
      Template_test_B.LinearDampningmatrix[8] = Template_test_B.N_r;

      /* Sum: '<S26>/M_11' incorporates:
       *  Constant: '<S26>/X_udot'
       *  Constant: '<S26>/m'
       */
      Template_test_B.M_11 = Template_test_P.m_Value -
        Template_test_P.X_udot_Value;

      /* Sum: '<S26>/M_22' incorporates:
       *  Constant: '<S26>/Y_vdot'
       *  Constant: '<S26>/m'
       */
      Template_test_B.M_22 = Template_test_P.m_Value -
        Template_test_P.Y_vdot_Value;

      /* Product: '<S26>/m x_g' incorporates:
       *  Constant: '<S26>/m'
       *  Constant: '<S26>/x_g'
       */
      Template_test_B.mx_g = Template_test_P.m_Value * Template_test_P.x_g_Value;

      /* Sum: '<S26>/M_32' incorporates:
       *  Constant: '<S26>/N_vdot'
       */
      Template_test_B.M_32 = Template_test_B.mx_g - Template_test_P.N_vdot_Value;

      /* Sum: '<S26>/M_23' incorporates:
       *  Constant: '<S26>/Y_rdot'
       */
      Template_test_B.M_23 = Template_test_B.mx_g - Template_test_P.Y_rdot_Value;

      /* Sum: '<S26>/M_33' incorporates:
       *  Constant: '<S26>/I_z'
       *  Constant: '<S26>/N_rdot'
       */
      Template_test_B.M_33 = Template_test_P.I_z_Value -
        Template_test_P.N_rdot_Value;

      /* Reshape: '<S26>/3x3' incorporates:
       *  Constant: '<S26>/M_12'
       *  Constant: '<S26>/M_13'
       *  Constant: '<S26>/M_21'
       *  Constant: '<S26>/M_31'
       */
      Template_test_B.x3[0] = Template_test_B.M_11;
      Template_test_B.x3[1] = Template_test_P.M_21_Value;
      Template_test_B.x3[2] = Template_test_P.M_31_Value;
      Template_test_B.x3[3] = Template_test_P.M_12_Value;
      Template_test_B.x3[4] = Template_test_B.M_22;
      Template_test_B.x3[5] = Template_test_B.M_32;
      Template_test_B.x3[6] = Template_test_P.M_13_Value;
      Template_test_B.x3[7] = Template_test_B.M_23;
      Template_test_B.x3[8] = Template_test_B.M_33;

      /* Gain: '<S77>/-l_x1' incorporates:
       *  Constant: '<S77>/l_x1'
       */
      Template_test_B.l_x1_i = Template_test_P.l_x1_Gain_j *
        Template_test_P.l_x1_Value_e;

      /* Gain: '<S77>/-l_y2' incorporates:
       *  Constant: '<S77>/l_y2'
       */
      Template_test_B.l_y2_f = Template_test_P.l_y2_Gain_p *
        Template_test_P.l_y2_Value_g;

      /* Gain: '<S77>/-l_x2' incorporates:
       *  Constant: '<S77>/l_x2'
       */
      Template_test_B.l_x2_o = Template_test_P.l_x2_Gain_m *
        Template_test_P.l_x2_Value_n;

      /* Reshape: '<S77>/3x5' incorporates:
       *  Constant: '<S77>/T_e11'
       *  Constant: '<S77>/T_e12'
       *  Constant: '<S77>/T_e13'
       *  Constant: '<S77>/T_e14'
       *  Constant: '<S77>/T_e15'
       *  Constant: '<S77>/T_e21'
       *  Constant: '<S77>/T_e22'
       *  Constant: '<S77>/T_e23'
       *  Constant: '<S77>/T_e24'
       *  Constant: '<S77>/T_e25'
       *  Constant: '<S77>/l_x3'
       *  Constant: '<S77>/l_y1'
       */
      Template_test_B.x5_b[0] = Template_test_P.T_e11_Value;
      Template_test_B.x5_b[1] = Template_test_P.T_e21_Value;
      Template_test_B.x5_b[2] = Template_test_P.l_y1_Value_d;
      Template_test_B.x5_b[3] = Template_test_P.T_e12_Value;
      Template_test_B.x5_b[4] = Template_test_P.T_e22_Value;
      Template_test_B.x5_b[5] = Template_test_B.l_x1_i;
      Template_test_B.x5_b[6] = Template_test_P.T_e13_Value;
      Template_test_B.x5_b[7] = Template_test_P.T_e23_Value;
      Template_test_B.x5_b[8] = Template_test_B.l_y2_f;
      Template_test_B.x5_b[9] = Template_test_P.T_e14_Value;
      Template_test_B.x5_b[10] = Template_test_P.T_e24_Value;
      Template_test_B.x5_b[11] = Template_test_B.l_x2_o;
      Template_test_B.x5_b[12] = Template_test_P.T_e15_Value;
      Template_test_B.x5_b[13] = Template_test_P.T_e25_Value;
      Template_test_B.x5_b[14] = Template_test_P.l_x3_Value_h;

      /* Gain: '<S32>/PS3 u_1' */
      Template_test_B.u_1 = Template_test_P.PS3u_1_Gain *
        Template_test_B.ypositionofleftanalogstick11;

      /* Lookup Block: '<S76>/u_1 to f_1'
       * About '<S76>/u_1 to f_1 :'
       * Lookup Block: '<S76>/u_1 to f_1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(Template_test_B.u_1tof_1),
                           Template_test_P.u_1tof_1_YData, Template_test_B.u_1,
                           Template_test_P.u_1tof_1_XData, 18U);

      /* Gain: '<S32>/PS3 u_2' */
      Template_test_B.u_2 = Template_test_P.PS3u_2_Gain *
        Template_test_B.xpositionofleftanalogstick11;

      /* Lookup Block: '<S76>/u_2 to f_2'
       * About '<S76>/u_2 to f_2 :'
       * Lookup Block: '<S76>/u_2 to f_2'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(Template_test_B.u_2tof_2),
                           Template_test_P.u_2tof_2_YData, Template_test_B.u_2,
                           Template_test_P.u_2tof_2_XData, 20U);

      /* Gain: '<S32>/PS3 u_3' */
      Template_test_B.u_3 = Template_test_P.PS3u_3_Gain *
        Template_test_B.ypositionofrightanalogstick11;

      /* Lookup Block: '<S76>/u_3 to f_3'
       * About '<S76>/u_3 to f_3 :'
       * Lookup Block: '<S76>/u_3 to f_3'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(Template_test_B.u_3tof_3),
                           Template_test_P.u_3tof_3_YData, Template_test_B.u_3,
                           Template_test_P.u_3tof_3_XData, 18U);

      /* Gain: '<S32>/PS3 u_4' */
      Template_test_B.u_4 = Template_test_P.PS3u_4_Gain *
        Template_test_B.xpositionofrightanalogstick11;

      /* Lookup Block: '<S76>/u_4 to f_4'
       * About '<S76>/u_4 to f_4 :'
       * Lookup Block: '<S76>/u_4 to f_4'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(Template_test_B.u_4tof_4),
                           Template_test_P.u_4tof_4_YData, Template_test_B.u_4,
                           Template_test_P.u_4tof_4_XData, 16U);

      /* Sum: '<S32>/Add' incorporates:
       *  Constant: '<S8>/L2 [-]'
       *  Constant: '<S8>/R2 [-]'
       */
      Template_test_B.BowThrusterdirection = Template_test_P.L2_Value +
        Template_test_P.R2_Value;

      /* Gain: '<S32>/PS3 u_5' */
      Template_test_B.u_5 = Template_test_P.PS3u_5_Gain *
        Template_test_B.BowThrusterdirection;

      /* Lookup Block: '<S76>/u_5 to f_5'
       * About '<S76>/u_5 to f_5 :'
       * Lookup Block: '<S76>/u_5 to f_5'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(Template_test_B.u_5tof_5),
                           Template_test_P.u_5tof_5_YData, Template_test_B.u_5,
                           Template_test_P.u_5tof_5_XData, 6U);

      /* SignalConversion: '<S75>/TmpHiddenBufferAtProductInport2' */
      Template_test_B.TmpHiddenBufferAtProductInport2[0] =
        Template_test_B.u_1tof_1;
      Template_test_B.TmpHiddenBufferAtProductInport2[1] =
        Template_test_B.u_2tof_2;
      Template_test_B.TmpHiddenBufferAtProductInport2[2] =
        Template_test_B.u_3tof_3;
      Template_test_B.TmpHiddenBufferAtProductInport2[3] =
        Template_test_B.u_4tof_4;
      Template_test_B.TmpHiddenBufferAtProductInport2[4] =
        Template_test_B.u_5tof_5;

      /* Product: '<S75>/Product' */
      for (i = 0; i < 3; i++) {
        Template_test_B.Product[i] = 0.0;
        for (tmp_5 = 0; tmp_5 < 5; tmp_5++) {
          Template_test_B.Product[i] = Template_test_B.x5_b[3 * tmp_5 + i] *
            Template_test_B.TmpHiddenBufferAtProductInport2[tmp_5] +
            Template_test_B.Product[i];
        }
      }
    }

    /* Gain: '<S169>/QTM In3 x-coord [mm]' */
    Template_test_B.QTMIn3xcoordmm = Template_test_P.QTMIn3xcoordmm_Gain *
      Template_test_B.QTMIn[2];

    /* Gain: '<S169>/mm2m x' */
    Template_test_B.mm2mx = Template_test_P.mm2mx_Gain *
      Template_test_B.QTMIn3xcoordmm;

    /* Gain: '<S169>/QTM In4 y-coord [mm]' */
    Template_test_B.QTMIn4ycoordmm = Template_test_P.QTMIn4ycoordmm_Gain *
      Template_test_B.QTMIn[3];

    /* Gain: '<S169>/mm2m y' */
    Template_test_B.mm2my = Template_test_P.mm2my_Gain *
      Template_test_B.QTMIn4ycoordmm;

    /* Gain: '<S169>/QTM In6 yaw [deg]' */
    Template_test_B.QTMIn6yawdeg = Template_test_P.QTMIn6yawdeg_Gain *
      Template_test_B.QTMIn[5];

    /* Gain: '<S169>/d2r yaw' */
    Template_test_B.d2ryaw = Template_test_P.d2ryaw_Gain *
      Template_test_B.QTMIn6yawdeg;

    /* Outputs for enable SubSystem: '<S25>/Linear Simulator' incorporates:
     *  Constant: '<S6>/Enable Linear Simulator'
     *  EnablePort: '<S173>/Enable'
     */
    if (rtmIsMajorTimeStep(Template_test_M) && rtmIsMajorTimeStep
        (Template_test_M)) {
      if (Template_test_P.EnableLinearSimulator_Value > 0.0) {
        if (Template_test_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S181>/Integrator' */
          if (rtmIsFirstInitCond(Template_test_M)) {
            Template_test_X.Integrator_CSTATE_p[0] = 0.0;
            Template_test_X.Integrator_CSTATE_p[1] = 0.0;
            Template_test_X.Integrator_CSTATE_p[2] = 0.0;
          }

          Template_test_DWork.Integrator_IWORK_f.IcNeedsLoading = 1;

          /* Integrator Block: '<S181>/Integrator1' */
          if (rtmIsFirstInitCond(Template_test_M)) {
            Template_test_X.Integrator1_CSTATE_d[0] = 0.0;
            Template_test_X.Integrator1_CSTATE_d[1] = 0.0;
            Template_test_X.Integrator1_CSTATE_d[2] = 0.0;
          }

          Template_test_DWork.Integrator1_IWORK_o.IcNeedsLoading = 1;
          Template_test_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (Template_test_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          Template_test_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (Template_test_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Integrator Block: '<S181>/Integrator'
       */
      if (rtmIsMajorTimeStep(Template_test_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &Template_test_PrevZCSigState.Integrator_Reset_ZCE_h,
                           Template_test_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || Template_test_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            Template_test_DWork.Integrator_IWORK_f.IcNeedsLoading) {
          Template_test_X.Integrator_CSTATE_p[0] = Template_test_B.Initialums;
          Template_test_X.Integrator_CSTATE_p[1] = Template_test_B.Initialvms;
          Template_test_X.Integrator_CSTATE_p[2] = Template_test_B.Initialrrads;
        }

        Template_test_DWork.Integrator_IWORK_f.IcNeedsLoading = 0;
      }

      Template_test_B.Integrator_j[0] = Template_test_X.Integrator_CSTATE_p[0];
      Template_test_B.Integrator_j[1] = Template_test_X.Integrator_CSTATE_p[1];
      Template_test_B.Integrator_j[2] = Template_test_X.Integrator_CSTATE_p[2];

      /* Integrator Block: '<S181>/Integrator1'
       */
      if (rtmIsMajorTimeStep(Template_test_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &Template_test_PrevZCSigState.Integrator1_Reset_ZCE_o,
                           Template_test_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || Template_test_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            Template_test_DWork.Integrator1_IWORK_o.IcNeedsLoading) {
          Template_test_X.Integrator1_CSTATE_d[0] = Template_test_B.Initialxm;
          Template_test_X.Integrator1_CSTATE_d[1] = Template_test_B.Initialym;
          Template_test_X.Integrator1_CSTATE_d[2] =
            Template_test_B.Initialpsirad;
        }

        Template_test_DWork.Integrator1_IWORK_o.IcNeedsLoading = 0;
      }

      Template_test_B.Integrator1_o[0] = Template_test_X.Integrator1_CSTATE_d[0];
      Template_test_B.Integrator1_o[1] = Template_test_X.Integrator1_CSTATE_d[1];
      Template_test_B.Integrator1_o[2] = Template_test_X.Integrator1_CSTATE_d[2];

      /* Fcn: '<S182>/R11' */
      Template_test_B.R11_k = cos(Template_test_B.Integrator1_o[2]);

      /* Fcn: '<S182>/R21' */
      Template_test_B.R21_n = sin(Template_test_B.Integrator1_o[2]);

      /* Fcn: '<S182>/R12' */
      Template_test_B.R12_fw = -1.0 * sin(Template_test_B.Integrator1_o[2]);

      /* Fcn: '<S182>/R22' */
      Template_test_B.R22_e = cos(Template_test_B.Integrator1_o[2]);

      /* Reshape: '<S182>/R(psi)' incorporates:
       *  Constant: '<S182>/R13'
       *  Constant: '<S182>/R23'
       *  Constant: '<S182>/R31'
       *  Constant: '<S182>/R32'
       *  Constant: '<S182>/R33'
       */
      Template_test_B.Rpsi_c[0] = Template_test_B.R11_k;
      Template_test_B.Rpsi_c[1] = Template_test_B.R21_n;
      Template_test_B.Rpsi_c[2] = Template_test_P.R31_Value_a;
      Template_test_B.Rpsi_c[3] = Template_test_B.R12_fw;
      Template_test_B.Rpsi_c[4] = Template_test_B.R22_e;
      Template_test_B.Rpsi_c[5] = Template_test_P.R32_Value_h;
      Template_test_B.Rpsi_c[6] = Template_test_P.R13_Value_f;
      Template_test_B.Rpsi_c[7] = Template_test_P.R23_Value_b;
      Template_test_B.Rpsi_c[8] = Template_test_P.R33_Value_l;

      /* Product: '<S181>/Product3' */
      for (i = 0; i < 3; i++) {
        Template_test_B.Product3_n[i] = 0.0;
        Template_test_B.Product3_n[i] = Template_test_B.Rpsi_c[i] *
          Template_test_B.Integrator_j[0] + Template_test_B.Product3_n[i];
        Template_test_B.Product3_n[i] = Template_test_B.Rpsi_c[i + 3] *
          Template_test_B.Integrator_j[1] + Template_test_B.Product3_n[i];
        Template_test_B.Product3_n[i] = Template_test_B.Rpsi_c[i + 6] *
          Template_test_B.Integrator_j[2] + Template_test_B.Product3_n[i];
      }
    }

    /* end of Outputs for SubSystem: '<S25>/Linear Simulator' */

    /* MultiPortSwitch: '<S170>/eta Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)Template_test_P.ControlInputSelector_Value == 0) {
      Template_test_B.etaSwitch[0] = Template_test_B.mm2mx;
      Template_test_B.etaSwitch[1] = Template_test_B.mm2my;
      Template_test_B.etaSwitch[2] = Template_test_B.d2ryaw;
    } else {
      Template_test_B.etaSwitch[0] = Template_test_B.Integrator1_o[0];
      Template_test_B.etaSwitch[1] = Template_test_B.Integrator1_o[1];
      Template_test_B.etaSwitch[2] = Template_test_B.Integrator1_o[2];
    }

    /* Fcn: '<S30>/yaw angle' */
    Template_test_B.psi = Template_test_B.etaSwitch[2];

    /* Saturate: '<S36>/Saturation' */
    tmp = Template_test_B.psi;
    Template_test_B.Saturation = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat, Template_test_P.Saturation_UpperSat);

    /* Signum: '<S36>/Sign' */
    Template_test_B.Sign = rt_SIGNd_snf(Template_test_B.Saturation);

    /* Gain: '<S36>/Gain' */
    Template_test_B.Gain = Template_test_P.Gain_Gain * Template_test_B.Sign;

    /* Sum: '<S36>/Sum1' */
    Template_test_B.Sum1 = Template_test_B.Saturation + Template_test_B.Gain;

    /* Math: '<S36>/Math Function' incorporates:
     *  Constant: '<S36>/Constant'
     */
    Template_test_B.MathFunction = rt_rem_snf(Template_test_B.Sum1,
      Template_test_P.Constant_Value);

    /* Sum: '<S36>/Sum' */
    Template_test_B.Sum = Template_test_B.MathFunction - Template_test_B.Gain;

    /* Sum: '<S30>/Sum2' incorporates:
     *  Constant: '<S12>/ y_d [m]'
     *  Constant: '<S12>/x_d [m]'
     */
    Template_test_B.Sum2[0] = Template_test_P.x_dm_Value -
      Template_test_B.etaSwitch[0];
    Template_test_B.Sum2[1] = Template_test_P.y_dm_Value -
      Template_test_B.etaSwitch[1];
    Template_test_B.Sum2[2] = Template_test_B.Gain1 - Template_test_B.etaSwitch
      [2];

    /* Saturate: '<S35>/Saturation' */
    tmp = Template_test_B.Sum2[2];
    Template_test_B.Saturation_k = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat_o,
      Template_test_P.Saturation_UpperSat_d);

    /* Signum: '<S35>/Sign' */
    Template_test_B.Sign_f = rt_SIGNd_snf(Template_test_B.Saturation_k);

    /* Gain: '<S35>/Gain' */
    Template_test_B.Gain_k = Template_test_P.Gain_Gain_f *
      Template_test_B.Sign_f;

    /* Sum: '<S35>/Sum1' */
    Template_test_B.Sum1_j = Template_test_B.Saturation_k +
      Template_test_B.Gain_k;

    /* Math: '<S35>/Math Function' incorporates:
     *  Constant: '<S35>/Constant'
     */
    Template_test_B.MathFunction_a = rt_rem_snf(Template_test_B.Sum1_j,
      Template_test_P.Constant_Value_a);

    /* Sum: '<S35>/Sum' */
    Template_test_B.Sum_p = Template_test_B.MathFunction_a -
      Template_test_B.Gain_k;

    /* Fcn: '<S34>/Row1' */
    Template_test_B.Row1 = cos(Template_test_B.Sum) * Template_test_B.Sum2[0] +
      sin(Template_test_B.Sum) * Template_test_B.Sum2[1];

    /* Fcn: '<S34>/Row2' */
    Template_test_B.Row2 = (-sin(Template_test_B.Sum)) * Template_test_B.Sum2[0]
      + cos(Template_test_B.Sum) * Template_test_B.Sum2[1];

    /* Fcn: '<S34>/Row3' */
    Template_test_B.Row3 = Template_test_B.Sum_p;

    /* SignalConversion: '<S30>/TmpHiddenBufferAtProductInport2' */
    Template_test_B.TmpHiddenBufferAtProductInpor_d[0] = Template_test_B.Row1;
    Template_test_B.TmpHiddenBufferAtProductInpor_d[1] = Template_test_B.Row2;
    Template_test_B.TmpHiddenBufferAtProductInpor_d[2] = Template_test_B.Row3;

    /* Product: '<S30>/Product' */
    for (i = 0; i < 3; i++) {
      Template_test_B.Product_e[i] = 0.0;
      Template_test_B.Product_e[i] = Template_test_B.ux3_f[i] *
        Template_test_B.TmpHiddenBufferAtProductInpor_d[0] +
        Template_test_B.Product_e[i];
      Template_test_B.Product_e[i] = Template_test_B.ux3_f[i + 3] *
        Template_test_B.TmpHiddenBufferAtProductInpor_d[1] +
        Template_test_B.Product_e[i];
      Template_test_B.Product_e[i] = Template_test_B.ux3_f[i + 6] *
        Template_test_B.TmpHiddenBufferAtProductInpor_d[2] +
        Template_test_B.Product_e[i];
    }

    /* Integrator Block: '<S30>/Integrator'
     */
    if (rtmIsMajorTimeStep(Template_test_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &Template_test_PrevZCSigState.Integrator_Reset_ZCE,
                         0.0);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || 0.0 != 0.0) {
        Template_test_X.Integrator_CSTATE[0] = Template_test_P.Integrator_IC;
        Template_test_X.Integrator_CSTATE[1] = Template_test_P.Integrator_IC;
        Template_test_X.Integrator_CSTATE[2] = Template_test_P.Integrator_IC;
      }
    }

    Template_test_B.Integrator[0] = Template_test_X.Integrator_CSTATE[0];
    Template_test_B.Integrator[1] = Template_test_X.Integrator_CSTATE[1];
    Template_test_B.Integrator[2] = Template_test_X.Integrator_CSTATE[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S30>/Product1' */
      Template_test_B.Product1[i] = 0.0;
      Template_test_B.Product1[i] = Template_test_B.ux3_g[i] *
        Template_test_B.Integrator[0] + Template_test_B.Product1[i];
      Template_test_B.Product1[i] = Template_test_B.ux3_g[i + 3] *
        Template_test_B.Integrator[1] + Template_test_B.Product1[i];
      Template_test_B.Product1[i] = Template_test_B.ux3_g[i + 6] *
        Template_test_B.Integrator[2] + Template_test_B.Product1[i];

      /* Sum: '<S30>/Sum3' */
      Template_test_B.Sum3[i] = Template_test_B.Product_e[i] +
        Template_test_B.Product1[i];
    }

    /* Gain: '<S169>/QTM In8 roll [deg]' */
    Template_test_B.QTMIn8rolldeg = Template_test_P.QTMIn8rolldeg_Gain *
      Template_test_B.QTMIn[7];

    /* Gain: '<S169>/d2r roll' */
    Template_test_B.d2rroll = Template_test_P.d2rroll_Gain *
      Template_test_B.QTMIn8rolldeg;

    /* Gain: '<S169>/QTM In7 pitch [deg]' */
    Template_test_B.QTMIn7pitchdeg = Template_test_P.QTMIn7pitchdeg_Gain *
      Template_test_B.QTMIn[6];

    /* Gain: '<S169>/d2r pitch' */
    Template_test_B.d2rpitch = Template_test_P.d2rpitch_Gain *
      Template_test_B.QTMIn7pitchdeg;

    /* Trigonometry: '<S171>/sin(theta)' */
    Template_test_B.sintheta[0] = sin(Template_test_B.d2rroll);
    Template_test_B.sintheta[1] = sin(Template_test_B.d2rpitch);
    Template_test_B.sintheta[2] = sin(Template_test_B.d2ryaw);

    /* Trigonometry: '<S171>/cos(theta)' */
    Template_test_B.costheta[0] = cos(Template_test_B.d2rroll);
    Template_test_B.costheta[1] = cos(Template_test_B.d2rpitch);
    Template_test_B.costheta[2] = cos(Template_test_B.d2ryaw);

    /* Fcn: '<S171>/R11' */
    Template_test_B.R11 = Template_test_B.costheta[1] *
      Template_test_B.costheta[2];

    /* Fcn: '<S171>/R21 ' */
    Template_test_B.R21 = Template_test_B.sintheta[0] *
      Template_test_B.sintheta[1] * Template_test_B.costheta[2] +
      (-Template_test_B.costheta[0]) * Template_test_B.sintheta[2];

    /* Fcn: '<S171>/R31 ' */
    Template_test_B.R31 = Template_test_B.costheta[0] *
      Template_test_B.sintheta[1] * Template_test_B.costheta[2] +
      Template_test_B.sintheta[0] * Template_test_B.sintheta[2];

    /* Fcn: '<S171>/R12' */
    Template_test_B.R12 = Template_test_B.costheta[1] *
      Template_test_B.sintheta[2];

    /* Fcn: '<S171>/R22' */
    Template_test_B.R22 = Template_test_B.sintheta[0] *
      Template_test_B.sintheta[1] * Template_test_B.sintheta[2] +
      Template_test_B.costheta[0] * Template_test_B.costheta[2];

    /* Fcn: '<S171>/R32' */
    Template_test_B.R32 = Template_test_B.costheta[0] *
      Template_test_B.sintheta[1] * Template_test_B.sintheta[2] +
      (-Template_test_B.sintheta[0]) * Template_test_B.costheta[2];

    /* Fcn: '<S171>/R13' */
    Template_test_B.R13 = -Template_test_B.sintheta[1];

    /* Fcn: '<S171>/R23' */
    Template_test_B.R23 = Template_test_B.sintheta[0] *
      Template_test_B.costheta[1];

    /* Fcn: '<S171>/R33' */
    Template_test_B.R33 = Template_test_B.costheta[0] *
      Template_test_B.costheta[1];

    /* Reshape: '<S171>/Reshape 9x1->3x3' */
    Template_test_B.Reshape9x13x3[0] = Template_test_B.R11;
    Template_test_B.Reshape9x13x3[1] = Template_test_B.R21;
    Template_test_B.Reshape9x13x3[2] = Template_test_B.R31;
    Template_test_B.Reshape9x13x3[3] = Template_test_B.R12;
    Template_test_B.Reshape9x13x3[4] = Template_test_B.R22;
    Template_test_B.Reshape9x13x3[5] = Template_test_B.R32;
    Template_test_B.Reshape9x13x3[6] = Template_test_B.R13;
    Template_test_B.Reshape9x13x3[7] = Template_test_B.R23;
    Template_test_B.Reshape9x13x3[8] = Template_test_B.R33;

    /* Concatenate: '<S169>/Matrix Concatenate' incorporates:
     *  Constant: '<S169>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = Template_test_B.Reshape9x13x3[3 * i];
      tmp_1[1 + 6 * i] = Template_test_B.Reshape9x13x3[3 * i + 1];
      tmp_1[2 + 6 * i] = Template_test_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = Template_test_P.Constant1_Value[3 * i];
      tmp_1[4 + 6 * i] = Template_test_P.Constant1_Value[3 * i + 1];
      tmp_1[5 + 6 * i] = Template_test_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&Template_test_B.MatrixConcatenate2[0]), (void *)&tmp_1[0],
           18U * sizeof(real_T));

    /* Concatenate: '<S169>/Matrix Concatenate1' incorporates:
     *  Constant: '<S169>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = Template_test_P.Constant1_Value[3 * i];
      tmp_1[1 + 6 * i] = Template_test_P.Constant1_Value[3 * i + 1];
      tmp_1[2 + 6 * i] = Template_test_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = Template_test_B.Reshape9x13x3[3 * i];
      tmp_1[4 + 6 * i] = Template_test_B.Reshape9x13x3[3 * i + 1];
      tmp_1[5 + 6 * i] = Template_test_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&Template_test_B.MatrixConcatenate2[18]), (void *)&tmp_1[0],
           18U * sizeof(real_T));

    /* Gain: '<S169>/QTM In5 z-coord [mm]' */
    Template_test_B.QTMIn5zcoordmm = Template_test_P.QTMIn5zcoordmm_Gain *
      Template_test_B.QTMIn[4];

    /* Gain: '<S169>/mm2m z' */
    Template_test_B.mm2mz = Template_test_P.mm2mz_Gain *
      Template_test_B.QTMIn5zcoordmm;

    /* Derivative Block: '<S169>/Derivative' */
    {
      real_T t = Template_test_M->Timing.t[0];
      real_T timeStampA = Template_test_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = Template_test_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = Template_test_B.Derivative;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &Template_test_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        Template_test_B.Derivative[0] = (Template_test_B.mm2mx - *lastBank++) /
          deltaT;
        Template_test_B.Derivative[1] = (Template_test_B.mm2my - *lastBank++) /
          deltaT;
        Template_test_B.Derivative[2] = (Template_test_B.mm2mz - *lastBank++) /
          deltaT;
        Template_test_B.Derivative[3] = (Template_test_B.d2rroll - *lastBank++) /
          deltaT;
        Template_test_B.Derivative[4] = (Template_test_B.d2rpitch - *lastBank++)
          / deltaT;
        Template_test_B.Derivative[5] = (Template_test_B.d2ryaw - *lastBank++) /
          deltaT;
      }
    }

    /* Product: '<S169>/Product' */
    for (i = 0; i < 6; i++) {
      Template_test_B.Product_a[i] = 0.0;
      for (tmp_5 = 0; tmp_5 < 6; tmp_5++) {
        Template_test_B.Product_a[i] = Template_test_B.MatrixConcatenate2[6 *
          tmp_5 + i] * Template_test_B.Derivative[tmp_5] +
          Template_test_B.Product_a[i];
      }
    }

    /* MultiPortSwitch: '<S170>/nu Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)Template_test_P.ControlInputSelector_Value == 0) {
      Template_test_B.nuSwitch[0] = Template_test_B.Product_a[0];
      Template_test_B.nuSwitch[1] = Template_test_B.Product_a[1];
      Template_test_B.nuSwitch[2] = Template_test_B.Product_a[5];
    } else {
      Template_test_B.nuSwitch[0] = Template_test_B.Integrator_j[0];
      Template_test_B.nuSwitch[1] = Template_test_B.Integrator_j[1];
      Template_test_B.nuSwitch[2] = Template_test_B.Integrator_j[2];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S30>/Product2' */
      Template_test_B.Product2[i] = 0.0;
      Template_test_B.Product2[i] = Template_test_B.ux3[i] *
        Template_test_B.nuSwitch[0] + Template_test_B.Product2[i];
      Template_test_B.Product2[i] = Template_test_B.ux3[i + 3] *
        Template_test_B.nuSwitch[1] + Template_test_B.Product2[i];
      Template_test_B.Product2[i] = Template_test_B.ux3[i + 6] *
        Template_test_B.nuSwitch[2] + Template_test_B.Product2[i];

      /* Sum: '<S30>/Sum1' */
      Template_test_B.Sum1_b[i] = Template_test_B.Sum3[i] -
        Template_test_B.Product2[i];
    }

    /* Trigonometry: '<S40>/R11' */
    Template_test_B.R11_e = cos(Template_test_B.etaSwitch[2]);

    /* Trigonometry: '<S40>/R21' */
    Template_test_B.R21_a = sin(Template_test_B.etaSwitch[2]);

    /* Trigonometry: '<S40>/R12' */
    Template_test_B.R12_f = sin(Template_test_B.etaSwitch[2]);

    /* Gain: '<S40>/-1' */
    Template_test_B.u = Template_test_P.u_Gain * Template_test_B.R12_f;

    /* Trigonometry: '<S40>/R22' */
    Template_test_B.R22_i = cos(Template_test_B.etaSwitch[2]);

    /* Reshape: '<S40>/R(psi)' incorporates:
     *  Constant: '<S40>/R13'
     *  Constant: '<S40>/R23'
     *  Constant: '<S40>/R31'
     *  Constant: '<S40>/R32'
     *  Constant: '<S40>/R33'
     */
    Template_test_B.Rpsi[0] = Template_test_B.R11_e;
    Template_test_B.Rpsi[1] = Template_test_B.R21_a;
    Template_test_B.Rpsi[2] = Template_test_P.R31_Value;
    Template_test_B.Rpsi[3] = Template_test_B.u;
    Template_test_B.Rpsi[4] = Template_test_B.R22_i;
    Template_test_B.Rpsi[5] = Template_test_P.R32_Value;
    Template_test_B.Rpsi[6] = Template_test_P.R13_Value;
    Template_test_B.Rpsi[7] = Template_test_P.R23_Value;
    Template_test_B.Rpsi[8] = Template_test_P.R33_Value;

    /* Math: '<S41>/Math Function' */
    for (i = 0; i < 3; i++) {
      Template_test_B.MathFunction_n[3 * i] = Template_test_B.Rpsi[i];
      Template_test_B.MathFunction_n[1 + 3 * i] = Template_test_B.Rpsi[i + 3];
      Template_test_B.MathFunction_n[2 + 3 * i] = Template_test_B.Rpsi[i + 6];
    }

    /* Integrator: '<S50>/Integrator' */
    Template_test_B.Integrator_b[0] = Template_test_X.Integrator_CSTATE_m[0];
    Template_test_B.Integrator_b[1] = Template_test_X.Integrator_CSTATE_m[1];
    Template_test_B.Integrator_b[2] = Template_test_X.Integrator_CSTATE_m[2];

    /* Product: '<S39>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_5 = 0; tmp_5 < 3; tmp_5++) {
        tmp_2[i + 3 * tmp_5] = 0.0;
        tmp_2[i + 3 * tmp_5] = tmp_2[3 * tmp_5 + i] + Template_test_B.ux3_d[3 *
          tmp_5] * Template_test_B.MathFunction_n[i];
        tmp_2[i + 3 * tmp_5] = Template_test_B.ux3_d[3 * tmp_5 + 1] *
          Template_test_B.MathFunction_n[i + 3] + tmp_2[3 * tmp_5 + i];
        tmp_2[i + 3 * tmp_5] = Template_test_B.ux3_d[3 * tmp_5 + 2] *
          Template_test_B.MathFunction_n[i + 6] + tmp_2[3 * tmp_5 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      Template_test_B.Product_l[i] = 0.0;
      Template_test_B.Product_l[i] = tmp_2[i] * Template_test_B.Integrator_b[0]
        + Template_test_B.Product_l[i];
      Template_test_B.Product_l[i] = tmp_2[i + 3] *
        Template_test_B.Integrator_b[1] + Template_test_B.Product_l[i];
      Template_test_B.Product_l[i] = tmp_2[i + 6] *
        Template_test_B.Integrator_b[2] + Template_test_B.Product_l[i];
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Gain: '<S39>/4' incorporates:
       *  Constant: '<S5>/kappa_1'
       */
      Template_test_B.u_a = Template_test_P._Gain *
        Template_test_P.kappa_1_Value;

      /* Product: '<S39>/Divide' incorporates:
       *  Constant: '<S39>/1'
       */
      Template_test_B.Divide = Template_test_P._Value / Template_test_B.u_a;
      for (i = 0; i < 9; i++) {
        /* Sum: '<S39>/Add1' */
        Template_test_B.Add1[i] = Template_test_B.ux3_n[i] +
          Template_test_B.Divide;

        /* Product: '<S44>/Product' incorporates:
         *  Constant: '<S5>/kappa_1'
         *  Constant: '<S63>/Constant'
         */
        Template_test_B.Product_k[i] = Template_test_P.kappa_1_Value *
          Template_test_P.Constant_Value_i[i];

        /* Sum: '<S44>/Subtract' */
        Template_test_B.Subtract[i] = Template_test_B.ux3_b[i] -
          Template_test_B.Product_k[i];
      }
    }

    /* Saturate: '<S72>/Saturation' */
    tmp = Template_test_B.etaSwitch[2];
    Template_test_B.Saturation_o = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat_f,
      Template_test_P.Saturation_UpperSat_m);

    /* Signum: '<S72>/Sign' */
    Template_test_B.Sign_a = rt_SIGNd_snf(Template_test_B.Saturation_o);

    /* Gain: '<S72>/Gain' */
    Template_test_B.Gain_c = Template_test_P.Gain_Gain_o *
      Template_test_B.Sign_a;

    /* Sum: '<S72>/Sum1' */
    Template_test_B.Sum1_j5 = Template_test_B.Saturation_o +
      Template_test_B.Gain_c;

    /* Math: '<S72>/Math Function' incorporates:
     *  Constant: '<S72>/Constant'
     */
    Template_test_B.MathFunction_m = rt_rem_snf(Template_test_B.Sum1_j5,
      Template_test_P.Constant_Value_ah);

    /* Sum: '<S72>/Sum' */
    Template_test_B.Sum_d = Template_test_B.MathFunction_m -
      Template_test_B.Gain_c;

    /* Integrator Block: '<S42>/Integrator'
     */
    if (rtmIsMajorTimeStep(Template_test_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &Template_test_PrevZCSigState.Integrator_Reset_ZCE_e,
                         Template_test_P.Resetq_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || Template_test_P.Resetq_Value != 0.0 ||
          Template_test_DWork.Integrator_IWORK.IcNeedsLoading) {
        Template_test_X.Integrator_CSTATE_f[0] = Template_test_B.Initialq_x;
        Template_test_X.Integrator_CSTATE_f[1] = Template_test_B.Initialq_y;
      }

      Template_test_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    Template_test_B.Integrator_n[0] = Template_test_X.Integrator_CSTATE_f[0];
    Template_test_B.Integrator_n[1] = Template_test_X.Integrator_CSTATE_f[1];

    /* SignalConversion: '<S109>/ConcatBufferAtVector ConcatenateIn1' */
    Template_test_B.VectorConcatenate[0] = Template_test_B.Integrator_n[0];
    Template_test_B.VectorConcatenate[1] = Template_test_B.Integrator_n[1];
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Sum: '<S162>/x_2 - x_1' incorporates:
       *  Constant: '<S19>/x_1 [m]'
       *  Constant: '<S19>/x_2 [m]'
       */
      Template_test_B.x_2x_1 = Template_test_P.x_2m_Value -
        Template_test_P.x_1m_Value;

      /* Sum: '<S162>/y_2 - y_1' incorporates:
       *  Constant: '<S19>/y_1 [m]'
       *  Constant: '<S19>/y_2 [m]'
       */
      Template_test_B.y_2y_1 = Template_test_P.y_2m_Value -
        Template_test_P.y_1m_Value;

      /* SignalConversion: '<S163>/TmpHiddenBufferAtProductInport2' */
      Template_test_B.TmpHiddenBufferAtProductInpo_dn[0] =
        Template_test_B.x_2x_1;
      Template_test_B.TmpHiddenBufferAtProductInpo_dn[1] =
        Template_test_B.y_2y_1;

      /* Product: '<S155>/Product' incorporates:
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Product_h[0] =
        Template_test_B.TmpHiddenBufferAtProductInpo_dn[0] *
        Template_test_P.PathSelector_Value;
      Template_test_B.Product_h[1] =
        Template_test_B.TmpHiddenBufferAtProductInpo_dn[1] *
        Template_test_P.PathSelector_Value;
    }

    /* Integrator Block: '<S42>/Integrator1'
     */
    if (rtmIsMajorTimeStep(Template_test_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &Template_test_PrevZCSigState.Integrator1_Reset_ZCE,
                         Template_test_P.Resets_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || Template_test_P.Resets_Value != 0.0 ||
          Template_test_DWork.Integrator1_IWORK.IcNeedsLoading) {
        Template_test_X.Integrator1_CSTATE = Template_test_B.Initials;
      }

      Template_test_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    Template_test_B.Integrator1 = Template_test_X.Integrator1_CSTATE;

    /* Product: '<S148>/Product2' incorporates:
     *  Constant: '<S18>/k [-]'
     */
    Template_test_B.Product2_i = Template_test_B.Integrator1 *
      Template_test_P.k_Value;

    /* Trigonometry: '<S148>/sin(s)' */
    Template_test_B.sins = sin(Template_test_B.Product2_i);

    /* Product: '<S148>/Product' incorporates:
     *  Constant: '<S18>/k [-]'
     *  Constant: '<S18>/r_x [m]'
     */
    Template_test_B.Product_eb = Template_test_P.r_xm_Value *
      Template_test_B.sins * Template_test_P.k_Value;

    /* Gain: '<S148>/Gain' */
    Template_test_B.Gain_b = Template_test_P.Gain_Gain_d *
      Template_test_B.Product_eb;

    /* Trigonometry: '<S148>/cos(s)' */
    Template_test_B.coss = cos(Template_test_B.Product2_i);

    /* Product: '<S148>/Product1' incorporates:
     *  Constant: '<S18>/k [-]'
     *  Constant: '<S18>/r_y [m]'
     */
    Template_test_B.Product1_n = Template_test_P.r_ym_Value *
      Template_test_B.coss * Template_test_P.k_Value;

    /* SignalConversion: '<S151>/TmpHiddenBufferAtProductInport2' */
    Template_test_B.TmpHiddenBufferAtProductInpor_l[0] = Template_test_B.Gain_b;
    Template_test_B.TmpHiddenBufferAtProductInpor_l[1] =
      Template_test_B.Product1_n;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Sum: '<S155>/Subract' incorporates:
       *  Constant: '<S155>/Constant'
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Subract = Template_test_P.Constant_Value_d -
        Template_test_P.PathSelector_Value;
    }

    /* Product: '<S155>/Product1' */
    Template_test_B.Product1_m[0] =
      Template_test_B.TmpHiddenBufferAtProductInpor_l[0] *
      Template_test_B.Subract;

    /* Sum: '<S155>/Add' */
    Template_test_B.Add[0] = Template_test_B.Product_h[0] +
      Template_test_B.Product1_m[0];

    /* Product: '<S155>/Product1' */
    Template_test_B.Product1_m[1] =
      Template_test_B.TmpHiddenBufferAtProductInpor_l[1] *
      Template_test_B.Subract;

    /* Sum: '<S155>/Add' */
    Template_test_B.Add[1] = Template_test_B.Product_h[1] +
      Template_test_B.Product1_m[1];

    /* Trigonometry: '<S100>/Trigonometric Function' */
    Template_test_B.TrigonometricFunction = rt_atan2_snf(Template_test_B.Add[1],
      Template_test_B.Add[0]);

    /* Saturate: '<S103>/Saturation' */
    tmp = Template_test_B.TrigonometricFunction;
    Template_test_B.Saturation_g = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat_k,
      Template_test_P.Saturation_UpperSat_j);

    /* Signum: '<S103>/Sign' */
    Template_test_B.Sign_i = rt_SIGNd_snf(Template_test_B.Saturation_g);

    /* Gain: '<S103>/Gain' */
    Template_test_B.Gain_d = Template_test_P.Gain_Gain_a *
      Template_test_B.Sign_i;

    /* Sum: '<S103>/Sum1' */
    Template_test_B.Sum1_i = Template_test_B.Saturation_g +
      Template_test_B.Gain_d;

    /* Math: '<S103>/Math Function' incorporates:
     *  Constant: '<S103>/Constant'
     */
    Template_test_B.MathFunction_j = rt_rem_snf(Template_test_B.Sum1_i,
      Template_test_P.Constant_Value_g);

    /* Sum: '<S103>/Sum' */
    Template_test_B.Sum_dn = Template_test_B.MathFunction_j -
      Template_test_B.Gain_d;

    /* Saturate: '<S131>/Saturation' */
    tmp = Template_test_B.Sum_dn;
    Template_test_B.Saturation_l = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat_d,
      Template_test_P.Saturation_UpperSat_k);

    /* Signum: '<S131>/Sign' */
    Template_test_B.Sign_ik = rt_SIGNd_snf(Template_test_B.Saturation_l);

    /* Gain: '<S131>/Gain' */
    Template_test_B.Gain_h = Template_test_P.Gain_Gain_l *
      Template_test_B.Sign_ik;

    /* Sum: '<S131>/Sum1' */
    Template_test_B.Sum1_c = Template_test_B.Saturation_l +
      Template_test_B.Gain_h;

    /* Math: '<S131>/Math Function' incorporates:
     *  Constant: '<S131>/Constant'
     */
    Template_test_B.MathFunction_d = rt_rem_snf(Template_test_B.Sum1_c,
      Template_test_P.Constant_Value_k);

    /* Sum: '<S131>/Sum' */
    Template_test_B.Sum_f = Template_test_B.MathFunction_d -
      Template_test_B.Gain_h;

    /* Outputs for atomic SubSystem: '<S108>/R_2' */

    /* Trigonometry: '<S134>/R11' */
    Template_test_B.R11_b = cos(Template_test_B.Sum_dn);

    /* Trigonometry: '<S134>/R21' */
    Template_test_B.R21_k = sin(Template_test_B.Sum_dn);

    /* Gain: '<S134>/R12' */
    Template_test_B.R12_i = Template_test_P.R12_Gain * Template_test_B.R21_k;

    /* Gain: '<S134>/R22' */
    Template_test_B.R22_m = Template_test_P.R22_Gain * Template_test_B.R11_b;

    /* Reshape: '<S134>/R_2(psi_d)' */
    Template_test_B.R_2psi_d[0] = Template_test_B.R11_b;
    Template_test_B.R_2psi_d[1] = Template_test_B.R21_k;
    Template_test_B.R_2psi_d[2] = Template_test_B.R12_i;
    Template_test_B.R_2psi_d[3] = Template_test_B.R22_m;

    /* end of Outputs for SubSystem: '<S108>/R_2' */

    /* Math: '<S135>/Math Function' */
    Template_test_B.MathFunction_g[0] = Template_test_B.R_2psi_d[0];
    Template_test_B.MathFunction_g[1] = Template_test_B.R_2psi_d[2];
    Template_test_B.MathFunction_g[2] = Template_test_B.R_2psi_d[1];
    Template_test_B.MathFunction_g[3] = Template_test_B.R_2psi_d[3];
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Sum: '<S161>/x_2 - x_1' incorporates:
       *  Constant: '<S19>/x_1 [m]'
       *  Constant: '<S19>/x_2 [m]'
       */
      Template_test_B.x_2x_1_k = Template_test_P.x_2m_Value -
        Template_test_P.x_1m_Value;
    }

    /* Product: '<S161>/(x_2 - x_1) * s' */
    Template_test_B.x_2x_1s = Template_test_B.x_2x_1_k *
      Template_test_B.Integrator1;

    /* Sum: '<S161>/(x_2 - x_1) * s + x_1' incorporates:
     *  Constant: '<S19>/x_1 [m]'
     */
    Template_test_B.x_2x_1sx_1 = Template_test_B.x_2x_1s +
      Template_test_P.x_1m_Value;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Sum: '<S161>/y_2 - y_1' incorporates:
       *  Constant: '<S19>/y_1 [m]'
       *  Constant: '<S19>/y_2 [m]'
       */
      Template_test_B.y_2y_1_b = Template_test_P.y_2m_Value -
        Template_test_P.y_1m_Value;
    }

    /* Product: '<S161>/(y_2 - y_1) * s' */
    Template_test_B.y_2y_1s = Template_test_B.y_2y_1_b *
      Template_test_B.Integrator1;

    /* Sum: '<S161>/(y_2 - y_1) * s + y_1' incorporates:
     *  Constant: '<S19>/y_1 [m]'
     */
    Template_test_B.y_2y_1sy_1 = Template_test_B.y_2y_1s +
      Template_test_P.y_1m_Value;

    /* Product: '<S154>/Product' incorporates:
     *  Constant: '<S7>/Path Selector  [-]'
     */
    Template_test_B.Product_ei[0] = Template_test_B.x_2x_1sx_1 *
      Template_test_P.PathSelector_Value;
    Template_test_B.Product_ei[1] = Template_test_B.y_2y_1sy_1 *
      Template_test_P.PathSelector_Value;

    /* Product: '<S147>/Product2' incorporates:
     *  Constant: '<S18>/k [-]'
     */
    Template_test_B.Product2_g = Template_test_B.Integrator1 *
      Template_test_P.k_Value;

    /* Trigonometry: '<S147>/cos(s)' */
    Template_test_B.coss_h = cos(Template_test_B.Product2_g);

    /* Product: '<S147>/Product' incorporates:
     *  Constant: '<S18>/r_x [m]'
     */
    Template_test_B.Product_p = Template_test_P.r_xm_Value *
      Template_test_B.coss_h;

    /* Sum: '<S147>/Add' incorporates:
     *  Constant: '<S18>/origin_x [m]'
     */
    Template_test_B.Add_b = Template_test_B.Product_p +
      Template_test_P.origin_xm_Value;

    /* Trigonometry: '<S147>/sin(s)' */
    Template_test_B.sins_l = sin(Template_test_B.Product2_g);

    /* Product: '<S147>/Product1' incorporates:
     *  Constant: '<S18>/r_y [m]'
     */
    Template_test_B.Product1_a = Template_test_P.r_ym_Value *
      Template_test_B.sins_l;

    /* Sum: '<S147>/Add1' incorporates:
     *  Constant: '<S18>/origo_y [m]'
     */
    Template_test_B.Add1_k = Template_test_B.Product1_a +
      Template_test_P.origo_ym_Value;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Sum: '<S154>/Subract' incorporates:
       *  Constant: '<S154>/Constant'
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Subract_o = Template_test_P.Constant_Value_p -
        Template_test_P.PathSelector_Value;
    }

    /* Product: '<S154>/Product1' */
    Template_test_B.Product1_h[0] = Template_test_B.Add_b *
      Template_test_B.Subract_o;
    Template_test_B.Product1_h[1] = Template_test_B.Add1_k *
      Template_test_B.Subract_o;

    /* Sum: '<S154>/Add' */
    Template_test_B.Add_n[0] = Template_test_B.Product_ei[0] +
      Template_test_B.Product1_h[0];
    Template_test_B.Add_n[1] = Template_test_B.Product_ei[1] +
      Template_test_B.Product1_h[1];

    /* RelationalOperator: '<S159>/LowerRelop1' incorporates:
     *  Constant: '<S7>/x_dmax [m]'
     */
    Template_test_B.LowerRelop1 = (Template_test_B.Add_n[0] >
      Template_test_P.x_dmaxm_Value);

    /* RelationalOperator: '<S159>/UpperRelop' incorporates:
     *  Constant: '<S7>/x_dmin [m]'
     */
    Template_test_B.UpperRelop = (Template_test_B.Add_n[0] <
      Template_test_P.x_dminm_Value);

    /* Switch: '<S159>/Switch' incorporates:
     *  Constant: '<S7>/x_dmin [m]'
     */
    if (Template_test_B.UpperRelop) {
      Template_test_B.Switch = Template_test_P.x_dminm_Value;
    } else {
      Template_test_B.Switch = Template_test_B.Add_n[0];
    }

    /* Switch: '<S159>/Switch2' incorporates:
     *  Constant: '<S7>/x_dmax [m]'
     */
    if (Template_test_B.LowerRelop1) {
      Template_test_B.Switch2 = Template_test_P.x_dmaxm_Value;
    } else {
      Template_test_B.Switch2 = Template_test_B.Switch;
    }

    /* RelationalOperator: '<S160>/LowerRelop1' incorporates:
     *  Constant: '<S7>/y_dmax [m]'
     */
    Template_test_B.LowerRelop1_g = (Template_test_B.Add_n[1] >
      Template_test_P.y_dmaxm_Value);

    /* RelationalOperator: '<S160>/UpperRelop' incorporates:
     *  Constant: '<S7>/y_dmin [m]'
     */
    Template_test_B.UpperRelop_d = (Template_test_B.Add_n[1] <
      Template_test_P.y_dminm_Value);

    /* Switch: '<S160>/Switch' incorporates:
     *  Constant: '<S7>/y_dmin [m]'
     */
    if (Template_test_B.UpperRelop_d) {
      Template_test_B.Switch_d = Template_test_P.y_dminm_Value;
    } else {
      Template_test_B.Switch_d = Template_test_B.Add_n[1];
    }

    /* Switch: '<S160>/Switch2' incorporates:
     *  Constant: '<S7>/y_dmax [m]'
     */
    if (Template_test_B.LowerRelop1_g) {
      Template_test_B.Switch2_c = Template_test_P.y_dmaxm_Value;
    } else {
      Template_test_B.Switch2_c = Template_test_B.Switch_d;
    }

    /* Sum: '<S97>/Subtract' */
    Template_test_B.Subtract_i[0] = Template_test_B.Integrator_n[0] -
      Template_test_B.Switch2;
    Template_test_B.Subtract_i[1] = Template_test_B.Integrator_n[1] -
      Template_test_B.Switch2_c;

    /* Product: '<S108>/epsilon' */
    Template_test_B.epsilon[0] = 0.0;
    Template_test_B.epsilon[0] = Template_test_B.MathFunction_g[0] *
      Template_test_B.Subtract_i[0] + Template_test_B.epsilon[0];
    Template_test_B.epsilon[0] = Template_test_B.MathFunction_g[2] *
      Template_test_B.Subtract_i[1] + Template_test_B.epsilon[0];
    Template_test_B.epsilon[1] = 0.0;
    Template_test_B.epsilon[1] = Template_test_B.MathFunction_g[1] *
      Template_test_B.Subtract_i[0] + Template_test_B.epsilon[1];
    Template_test_B.epsilon[1] = Template_test_B.MathFunction_g[3] *
      Template_test_B.Subtract_i[1] + Template_test_B.epsilon[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S108>/Multiport Selector' */
    {
      const byte_T *u = (byte_T *)Template_test_B.epsilon;/* input port */
      const int32_T *index = (const int32_T *)&Template_test_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&Template_test_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&Template_test_B.MultiportSelector;
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
    }                                  /* end <S108>/Multiport Selector */

    /* Trigonometry: '<S125>/Trigonometric Function' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.TrigonometricFunction_i = rt_atan2_snf
      (Template_test_B.MultiportSelector, Template_test_P.Deltam_Value);

    /* Saturate: '<S132>/Saturation' */
    tmp = Template_test_B.TrigonometricFunction_i;
    Template_test_B.Saturation_m = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat_e,
      Template_test_P.Saturation_UpperSat_p);

    /* Signum: '<S132>/Sign' */
    Template_test_B.Sign_m = rt_SIGNd_snf(Template_test_B.Saturation_m);

    /* Gain: '<S132>/Gain' */
    Template_test_B.Gain_f = Template_test_P.Gain_Gain_i *
      Template_test_B.Sign_m;

    /* Sum: '<S132>/Sum1' */
    Template_test_B.Sum1_n = Template_test_B.Saturation_m +
      Template_test_B.Gain_f;

    /* Math: '<S132>/Math Function' incorporates:
     *  Constant: '<S132>/Constant'
     */
    Template_test_B.MathFunction_o = rt_rem_snf(Template_test_B.Sum1_n,
      Template_test_P.Constant_Value_f);

    /* Sum: '<S132>/Sum' */
    Template_test_B.Sum_d3 = Template_test_B.MathFunction_o -
      Template_test_B.Gain_f;

    /* Sum: '<S125>/Subtract' */
    Template_test_B.Subtract_l = Template_test_B.Sum_f - Template_test_B.Sum_d3;

    /* Saturate: '<S133>/Saturation' */
    tmp = Template_test_B.Subtract_l;
    Template_test_B.Saturation_oa = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat_ku,
      Template_test_P.Saturation_UpperSat_kl);

    /* Signum: '<S133>/Sign' */
    Template_test_B.Sign_j = rt_SIGNd_snf(Template_test_B.Saturation_oa);

    /* Gain: '<S133>/Gain' */
    Template_test_B.Gain_n = Template_test_P.Gain_Gain_e *
      Template_test_B.Sign_j;

    /* Sum: '<S133>/Sum1' */
    Template_test_B.Sum1_a = Template_test_B.Saturation_oa +
      Template_test_B.Gain_n;

    /* Math: '<S133>/Math Function' incorporates:
     *  Constant: '<S133>/Constant'
     */
    Template_test_B.MathFunction_p = rt_rem_snf(Template_test_B.Sum1_a,
      Template_test_P.Constant_Value_d1);

    /* Sum: '<S133>/Sum' */
    Template_test_B.Sum_pn = Template_test_B.MathFunction_p -
      Template_test_B.Gain_n;

    /* SignalConversion: '<S109>/ConcatBufferAtVector ConcatenateIn2' */
    Template_test_B.VectorConcatenate[2] = Template_test_B.Sum_pn;

    /* Sum: '<S48>/Subtract' */
    Template_test_B.Subtract_n[0] = Template_test_B.etaSwitch[0] -
      Template_test_B.VectorConcatenate[0];
    Template_test_B.Subtract_n[1] = Template_test_B.etaSwitch[1] -
      Template_test_B.VectorConcatenate[1];
    Template_test_B.Subtract_n[2] = Template_test_B.Sum_d -
      Template_test_B.VectorConcatenate[2];

    /* Saturate: '<S73>/Saturation' */
    tmp = Template_test_B.Subtract_n[2];
    Template_test_B.Saturation_h = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat_l,
      Template_test_P.Saturation_UpperSat_f);

    /* Signum: '<S73>/Sign' */
    Template_test_B.Sign_k = rt_SIGNd_snf(Template_test_B.Saturation_h);

    /* Gain: '<S73>/Gain' */
    Template_test_B.Gain_p = Template_test_P.Gain_Gain_eb *
      Template_test_B.Sign_k;

    /* Sum: '<S73>/Sum1' */
    Template_test_B.Sum1_g = Template_test_B.Saturation_h +
      Template_test_B.Gain_p;

    /* Math: '<S73>/Math Function' incorporates:
     *  Constant: '<S73>/Constant'
     */
    Template_test_B.MathFunction_pi = rt_rem_snf(Template_test_B.Sum1_g,
      Template_test_P.Constant_Value_gp);

    /* Sum: '<S73>/Sum' */
    Template_test_B.Sum_i = Template_test_B.MathFunction_pi -
      Template_test_B.Gain_p;

    /* SignalConversion: '<S48>/TmpHiddenBufferAtProductInport2' */
    Template_test_B.TmpHiddenBufferAtProductInpo_lr[0] =
      Template_test_B.Subtract_n[0];
    Template_test_B.TmpHiddenBufferAtProductInpo_lr[1] =
      Template_test_B.Subtract_n[1];
    Template_test_B.TmpHiddenBufferAtProductInpo_lr[2] = Template_test_B.Sum_i;

    /* Product: '<S48>/Product' */
    for (i = 0; i < 3; i++) {
      Template_test_B.Product_d[i] = 0.0;
      Template_test_B.Product_d[i] = Template_test_B.MathFunction_n[i] *
        Template_test_B.TmpHiddenBufferAtProductInpo_lr[0] +
        Template_test_B.Product_d[i];
      Template_test_B.Product_d[i] = Template_test_B.MathFunction_n[i + 3] *
        Template_test_B.TmpHiddenBufferAtProductInpo_lr[1] +
        Template_test_B.Product_d[i];
      Template_test_B.Product_d[i] = Template_test_B.MathFunction_n[i + 6] *
        Template_test_B.TmpHiddenBufferAtProductInpo_lr[2] +
        Template_test_B.Product_d[i];
    }

    /* Product: '<S44>/Product1' */
    for (i = 0; i < 3; i++) {
      Template_test_B.Product1_d[i] = 0.0;
      Template_test_B.Product1_d[i] = Template_test_B.Subtract[i] *
        Template_test_B.Product_d[0] + Template_test_B.Product1_d[i];
      Template_test_B.Product1_d[i] = Template_test_B.Subtract[i + 3] *
        Template_test_B.Product_d[1] + Template_test_B.Product1_d[i];
      Template_test_B.Product1_d[i] = Template_test_B.Subtract[i + 6] *
        Template_test_B.Product_d[2] + Template_test_B.Product1_d[i];
    }

    /* Trigonometry: '<S110>/f_qx' */
    Template_test_B.f_qx = cos(Template_test_B.Sum_pn);

    /* Trigonometry: '<S110>/f_qy' */
    Template_test_B.f_qy = sin(Template_test_B.Sum_pn);

    /* SignalConversion: '<S110>/TmpHiddenBufferAtProductInport1' */
    Template_test_B.TmpHiddenBufferAtProductInport1[0] = Template_test_B.f_qx;
    Template_test_B.TmpHiddenBufferAtProductInport1[1] = Template_test_B.f_qy;

    /* Product: '<S110>/Product' incorporates:
     *  Constant: '<S7>/u_d [m]'
     */
    Template_test_B.Product_o[0] =
      Template_test_B.TmpHiddenBufferAtProductInport1[0] *
      Template_test_P.u_dm_Value;
    Template_test_B.Product_o[1] =
      Template_test_B.TmpHiddenBufferAtProductInport1[1] *
      Template_test_P.u_dm_Value;

    /* SignalConversion: '<S51>/ConcatBufferAtVector ConcatenateIn1' */
    Template_test_B.VectorConcatenate_p[0] = Template_test_B.Product_o[0];
    Template_test_B.VectorConcatenate_p[1] = Template_test_B.Product_o[1];
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S126>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2 = tmp * tmp;
    }

    /* Math: '<S126>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2 = tmp * tmp;

    /* Sum: '<S126>/Add' */
    Template_test_B.Add_g = Template_test_B.Delta2 + Template_test_B.epsilon_n2;

    /* Product: '<S126>/Divide' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Divide_p = Template_test_P.Deltam_Value /
      Template_test_B.Add_g;

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S108>/Multiport Selector1' */
    {
      const byte_T *u = (byte_T *)Template_test_B.MathFunction_g;/* input port */
      const int32_T *index = (const int32_T *)&Template_test_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&Template_test_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)Template_test_B.MultiportSelector1;
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
    }                                  /* end <S108>/Multiport Selector1 */

    /* Product: '<S126>/Product' */
    Template_test_B.Product_i[0] = Template_test_B.Divide_p *
      Template_test_B.MultiportSelector1[0];

    /* Gain: '<S126>/-1' */
    Template_test_B.u_b[0] = Template_test_P.u_Gain_d *
      Template_test_B.Product_i[0];

    /* Product: '<S126>/Product' */
    Template_test_B.Product_i[1] = Template_test_B.Divide_p *
      Template_test_B.MultiportSelector1[1];

    /* Gain: '<S126>/-1' */
    Template_test_B.u_b[1] = Template_test_P.u_Gain_d *
      Template_test_B.Product_i[1];

    /* Product: '<S51>/Product' */
    tmp = Template_test_B.u_b[0] * Template_test_B.Product_o[0];
    tmp += Template_test_B.u_b[1] * Template_test_B.Product_o[1];
    Template_test_B.VectorConcatenate_p[2] = tmp;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Constant: '<S57>/0_2x1' */
      Template_test_B.VectorConcatenate_n[0] = Template_test_P._2x1_Value[0];
      Template_test_B.VectorConcatenate_n[1] = Template_test_P._2x1_Value[1];

      /* Product: '<S156>/Product' incorporates:
       *  Constant: '<S146>/0_2x1'
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Product_m[0] = Template_test_P._2x1_Value_m[0] *
        Template_test_P.PathSelector_Value;
      Template_test_B.Product_m[1] = Template_test_P._2x1_Value_m[1] *
        Template_test_P.PathSelector_Value;
    }

    /* Product: '<S149>/Product2' incorporates:
     *  Constant: '<S18>/k [-]'
     */
    Template_test_B.Product2_h = Template_test_B.Integrator1 *
      Template_test_P.k_Value;

    /* Trigonometry: '<S149>/cos(s)' */
    Template_test_B.coss_c = cos(Template_test_B.Product2_h);
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S149>/Math Function' incorporates:
       *  Constant: '<S18>/k [-]'
       */
      tmp = Template_test_P.k_Value;
      Template_test_B.MathFunction_i = tmp * tmp;
    }

    /* Product: '<S149>/Product' incorporates:
     *  Constant: '<S18>/r_x [m]'
     */
    Template_test_B.Product_ih = Template_test_P.r_xm_Value *
      Template_test_B.coss_c * Template_test_B.MathFunction_i;

    /* Gain: '<S149>/Gain' */
    Template_test_B.Gain_nq = Template_test_P.Gain_Gain_ot *
      Template_test_B.Product_ih;

    /* Trigonometry: '<S149>/sin(s)' */
    Template_test_B.sins_n = sin(Template_test_B.Product2_h);

    /* Product: '<S149>/Product1' incorporates:
     *  Constant: '<S18>/r_y [m]'
     */
    Template_test_B.Product1_di = Template_test_P.r_ym_Value *
      Template_test_B.sins_n * Template_test_B.MathFunction_i;

    /* Gain: '<S149>/Gain1' */
    Template_test_B.Gain1_b = Template_test_P.Gain1_Gain_n *
      Template_test_B.Product1_di;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Sum: '<S156>/Subract' incorporates:
       *  Constant: '<S156>/Constant'
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Subract_e = Template_test_P.Constant_Value_ie -
        Template_test_P.PathSelector_Value;
    }

    /* Product: '<S156>/Product1' */
    Template_test_B.Product1_nf[0] = Template_test_B.Gain_nq *
      Template_test_B.Subract_e;
    Template_test_B.Product1_nf[1] = Template_test_B.Gain1_b *
      Template_test_B.Subract_e;

    /* Sum: '<S156>/Add' */
    Template_test_B.Add_f[0] = Template_test_B.Product_m[0] +
      Template_test_B.Product1_nf[0];
    Template_test_B.Add_f[1] = Template_test_B.Product_m[1] +
      Template_test_B.Product1_nf[1];

    /* Product: '<S101>/x_d^s * y_d^s^2' */
    Template_test_B.x_dsy_ds2 = Template_test_B.Add[0] * Template_test_B.Add_f[1];

    /* Product: '<S101>/x_d^s^2 * y_d^s' */
    Template_test_B.x_ds2y_ds = Template_test_B.Add_f[0] * Template_test_B.Add[1];

    /* Sum: '<S101>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
    Template_test_B.x_dsy_ds2x_ds2y_ds = Template_test_B.x_dsy_ds2 -
      Template_test_B.x_ds2y_ds;

    /* Math: '<S101>/( x_d^s )^2' */
    tmp = Template_test_B.Add[0];
    Template_test_B.x_ds2 = tmp * tmp;

    /* Math: '<S101>/( y_d^s )^2' */
    tmp = Template_test_B.Add[1];
    Template_test_B.y_ds2 = tmp * tmp;

    /* Sum: '<S101>/( x_d^s )^2 + ( y_d^s )^2' */
    Template_test_B.x_ds2y_ds2 = Template_test_B.x_ds2 + Template_test_B.y_ds2;

    /* Product: '<S101>/Divide' */
    Template_test_B.Divide_k = Template_test_B.x_dsy_ds2x_ds2y_ds /
      Template_test_B.x_ds2y_ds2;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S129>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2_p = tmp * tmp;
    }

    /* Math: '<S129>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2_b = tmp * tmp;

    /* Sum: '<S129>/Add' */
    Template_test_B.Add_p = Template_test_B.Delta2_p +
      Template_test_B.epsilon_n2_b;

    /* Product: '<S129>/Divide' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Divide_d = Template_test_P.Deltam_Value /
      Template_test_B.Add_p;

    /* Outputs for atomic SubSystem: '<S108>/S_2' */

    /* Gain: '<S136>/S12' */
    Template_test_B.S12_l = Template_test_P.S12_Gain_i *
      Template_test_B.Divide_k;

    /* Reshape: '<S136>/S_2(psi_d^s)' incorporates:
     *  Constant: '<S136>/0'
     */
    Template_test_B.S_2psi_ds[0] = Template_test_P._Value_f;
    Template_test_B.S_2psi_ds[1] = Template_test_B.Divide_k;
    Template_test_B.S_2psi_ds[2] = Template_test_B.S12_l;
    Template_test_B.S_2psi_ds[3] = Template_test_P._Value_f;

    /* end of Outputs for SubSystem: '<S108>/S_2' */

    /* Math: '<S139>/Math Function' */
    Template_test_B.MathFunction_e[0] = Template_test_B.S_2psi_ds[0];
    Template_test_B.MathFunction_e[1] = Template_test_B.S_2psi_ds[2];
    Template_test_B.MathFunction_e[2] = Template_test_B.S_2psi_ds[1];
    Template_test_B.MathFunction_e[3] = Template_test_B.S_2psi_ds[3];

    /* Product: '<S141>/Product' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += Template_test_B.MathFunction_e[i] *
        Template_test_B.MathFunction_g[0];
      tmp_3[i] += Template_test_B.MathFunction_e[i + 2] *
        Template_test_B.MathFunction_g[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += Template_test_B.MathFunction_e[i] *
        Template_test_B.MathFunction_g[2];
      tmp_3[i + 2] += Template_test_B.MathFunction_e[i + 2] *
        Template_test_B.MathFunction_g[3];
    }

    Template_test_B.Product_aj[0] = 0.0;
    Template_test_B.Product_aj[0] = tmp_3[0] * Template_test_B.Subtract_i[0] +
      Template_test_B.Product_aj[0];
    Template_test_B.Product_aj[0] = tmp_3[2] * Template_test_B.Subtract_i[1] +
      Template_test_B.Product_aj[0];

    /* Product: '<S141>/Product1' */
    Template_test_B.Product1_i[0] = 0.0;
    Template_test_B.Product1_i[0] = Template_test_B.MathFunction_g[0] *
      Template_test_B.Add[0] + Template_test_B.Product1_i[0];
    Template_test_B.Product1_i[0] = Template_test_B.MathFunction_g[2] *
      Template_test_B.Add[1] + Template_test_B.Product1_i[0];

    /* Sum: '<S141>/Subtract1' */
    Template_test_B.Subtract1[0] = Template_test_B.Product_aj[0] -
      Template_test_B.Product1_i[0];
    Template_test_B.Product_aj[1] = 0.0;
    Template_test_B.Product_aj[1] = tmp_3[1] * Template_test_B.Subtract_i[0] +
      Template_test_B.Product_aj[1];
    Template_test_B.Product_aj[1] = tmp_3[3] * Template_test_B.Subtract_i[1] +
      Template_test_B.Product_aj[1];

    /* Product: '<S141>/Product1' */
    Template_test_B.Product1_i[1] = 0.0;
    Template_test_B.Product1_i[1] = Template_test_B.MathFunction_g[1] *
      Template_test_B.Add[0] + Template_test_B.Product1_i[1];
    Template_test_B.Product1_i[1] = Template_test_B.MathFunction_g[3] *
      Template_test_B.Add[1] + Template_test_B.Product1_i[1];

    /* Sum: '<S141>/Subtract1' */
    Template_test_B.Subtract1[1] = Template_test_B.Product_aj[1] -
      Template_test_B.Product1_i[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S108>/Multiport Selector2' */
    {
      const byte_T *u = (byte_T *)Template_test_B.Subtract1;/* input port */
      const int32_T *index = (const int32_T *)&Template_test_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&Template_test_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&Template_test_B.MultiportSelector2;
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
    }                                  /* end <S108>/Multiport Selector2 */

    /* Product: '<S129>/Product' */
    Template_test_B.Product_f = Template_test_B.Divide_d *
      Template_test_B.MultiportSelector2;

    /* Sum: '<S129>/Subtract' */
    Template_test_B.Subtract_h = Template_test_B.Divide_k -
      Template_test_B.Product_f;

    /* Math: '<S114>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2_j = tmp * tmp;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S114>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2_n = tmp * tmp;
    }

    /* Sum: '<S114>/Add' */
    Template_test_B.Add_i = Template_test_B.epsilon_n2_j +
      Template_test_B.Delta2_n;

    /* Math: '<S114>/sqrt' */
    tmp = Template_test_B.Add_i;
    if (tmp < 0.0) {
      Template_test_B.sqrt_g = -sqrt(-tmp);
    } else {
      Template_test_B.sqrt_g = sqrt(tmp);
    }

    /* Product: '<S114>/Divide' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Divide_dt = Template_test_P.Deltam_Value /
      Template_test_B.sqrt_g;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Product: '<S158>/Product' incorporates:
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Product_b = 0.0 * Template_test_P.PathSelector_Value;

      /* Sum: '<S158>/Subract' incorporates:
       *  Constant: '<S158>/Constant'
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Subract_eq = Template_test_P.Constant_Value_j -
        Template_test_P.PathSelector_Value;

      /* Product: '<S158>/Product1' */
      Template_test_B.Product1_e = 0.0 * Template_test_B.Subract_eq;

      /* Sum: '<S158>/Add' */
      Template_test_B.Add_e = Template_test_B.Product_b +
        Template_test_B.Product1_e;

      /* Product: '<S165>/Divide' incorporates:
       *  Constant: '<S7>/u_d [m]'
       */
      Template_test_B.Divide_o = Template_test_P.u_dm_Value /
        Template_test_B.Add_e;
    }

    /* Product: '<S114>/Product' */
    Template_test_B.Product_ey = Template_test_B.Divide_dt *
      Template_test_B.Divide_o;

    /* Math: '<S121>/Math Function' */
    Template_test_B.MathFunction_b[0] = Template_test_B.Add[0];

    /* Product: '<S118>/Divide' */
    Template_test_B.Divide_e[0] = Template_test_B.MathFunction_b[0] /
      Template_test_B.Add_e;

    /* Math: '<S121>/Math Function' */
    Template_test_B.MathFunction_b[1] = Template_test_B.Add[1];

    /* Product: '<S118>/Divide' */
    Template_test_B.Divide_e[1] = Template_test_B.MathFunction_b[1] /
      Template_test_B.Add_e;

    /* Product: '<S118>/Product' incorporates:
     *  Constant: '<S7>/my [-]'
     */
    tmp = Template_test_P.my_Value * Template_test_B.Divide_e[0] *
      Template_test_B.Subtract_i[0];
    tmp += Template_test_P.my_Value * Template_test_B.Divide_e[1] *
      Template_test_B.Subtract_i[1];
    Template_test_B.Product_bd = tmp;

    /* Gain: '<S118>/Gain' */
    Template_test_B.Gain_a = Template_test_P.Gain_Gain_p *
      Template_test_B.Product_bd;

    /* Sum: '<S114>/Subtract' */
    Template_test_B.Subtract_d = Template_test_B.Product_ey -
      Template_test_B.Gain_a;

    /* Product: '<S57>/Product' */
    Template_test_B.VectorConcatenate_n[2] = Template_test_B.Subtract_h *
      Template_test_B.Subtract_d;

    /* Sum: '<S44>/Add' */
    Template_test_B.Add_l[0] = Template_test_B.VectorConcatenate_p[0] +
      Template_test_B.VectorConcatenate_n[0];
    Template_test_B.Add_l[1] = Template_test_B.VectorConcatenate_p[1] +
      Template_test_B.VectorConcatenate_n[1];
    Template_test_B.Add_l[2] = Template_test_B.VectorConcatenate_p[2] +
      Template_test_B.VectorConcatenate_n[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S44>/Product2' */
      Template_test_B.Product2_d[i] = 0.0;
      Template_test_B.Product2_d[i] = Template_test_B.MathFunction_n[i] *
        Template_test_B.Add_l[0] + Template_test_B.Product2_d[i];
      Template_test_B.Product2_d[i] = Template_test_B.MathFunction_n[i + 3] *
        Template_test_B.Add_l[1] + Template_test_B.Product2_d[i];
      Template_test_B.Product2_d[i] = Template_test_B.MathFunction_n[i + 6] *
        Template_test_B.Add_l[2] + Template_test_B.Product2_d[i];

      /* Sum: '<S44>/Sum' */
      Template_test_B.Sum_e[i] = Template_test_B.Product2_d[i] -
        Template_test_B.Product1_d[i];

      /* Sum: '<S49>/Subtract' */
      Template_test_B.Subtract_o[i] = Template_test_B.nuSwitch[i] -
        Template_test_B.Sum_e[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S39>/Product1' */
      Template_test_B.Product1_k[i] = 0.0;
      Template_test_B.Product1_k[i] = Template_test_B.Add1[i] *
        Template_test_B.Subtract_o[0] + Template_test_B.Product1_k[i];
      Template_test_B.Product1_k[i] = Template_test_B.Add1[i + 3] *
        Template_test_B.Subtract_o[1] + Template_test_B.Product1_k[i];
      Template_test_B.Product1_k[i] = Template_test_B.Add1[i + 6] *
        Template_test_B.Subtract_o[2] + Template_test_B.Product1_k[i];

      /* Product: '<S39>/Product2' */
      Template_test_B.Product2_i4[i] = 0.0;
      Template_test_B.Product2_i4[i] = Template_test_B.LinearDampningmatrix[i] *
        Template_test_B.nuSwitch[0] + Template_test_B.Product2_i4[i];
      Template_test_B.Product2_i4[i] = Template_test_B.LinearDampningmatrix[i +
        3] * Template_test_B.nuSwitch[1] + Template_test_B.Product2_i4[i];
      Template_test_B.Product2_i4[i] = Template_test_B.LinearDampningmatrix[i +
        6] * Template_test_B.nuSwitch[2] + Template_test_B.Product2_i4[i];
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
      for (i = 0; i < 9; i++) {
        /* Product: '<S47>/Product1' incorporates:
         *  Constant: '<S5>/kappa_1'
         *  Constant: '<S66>/Constant'
         */
        Template_test_B.Product1_j[i] = Template_test_P.kappa_1_Value *
          Template_test_P.Constant_Value_aj[i];

        /* Sum: '<S47>/Add3' */
        Template_test_B.Add3[i] = Template_test_B.ux3_b[i] +
          Template_test_B.Product1_j[i];
      }
    }

    /* Gain: '<S68>/S12' */
    Template_test_B.S12 = Template_test_P.S12_Gain * Template_test_B.nuSwitch[2];

    /* Reshape: '<S68>/S(r)' incorporates:
     *  Constant: '<S68>/R31'
     *  Constant: '<S68>/S11'
     *  Constant: '<S68>/S13'
     *  Constant: '<S68>/S22'
     *  Constant: '<S68>/S23'
     *  Constant: '<S68>/S32'
     *  Constant: '<S68>/S33'
     */
    Template_test_B.Sr[0] = Template_test_P.S11_Value;
    Template_test_B.Sr[1] = Template_test_B.nuSwitch[2];
    Template_test_B.Sr[2] = Template_test_P.R31_Value_d;
    Template_test_B.Sr[3] = Template_test_B.S12;
    Template_test_B.Sr[4] = Template_test_P.S22_Value;
    Template_test_B.Sr[5] = Template_test_P.S32_Value;
    Template_test_B.Sr[6] = Template_test_P.S13_Value;
    Template_test_B.Sr[7] = Template_test_P.S23_Value;
    Template_test_B.Sr[8] = Template_test_P.S33_Value;

    /* Math: '<S69>/Math Function' */
    for (i = 0; i < 3; i++) {
      Template_test_B.MathFunction_k[3 * i] = Template_test_B.Sr[i];
      Template_test_B.MathFunction_k[1 + 3 * i] = Template_test_B.Sr[i + 3];
      Template_test_B.MathFunction_k[2 + 3 * i] = Template_test_B.Sr[i + 6];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product' */
      Template_test_B.Product_c[i] = 0.0;
      Template_test_B.Product_c[i] = Template_test_B.MathFunction_k[i] *
        Template_test_B.Product_d[0] + Template_test_B.Product_c[i];
      Template_test_B.Product_c[i] = Template_test_B.MathFunction_k[i + 3] *
        Template_test_B.Product_d[1] + Template_test_B.Product_c[i];
      Template_test_B.Product_c[i] = Template_test_B.MathFunction_k[i + 6] *
        Template_test_B.Product_d[2] + Template_test_B.Product_c[i];

      /* Sum: '<S47>/Add' */
      Template_test_B.Add_a[i] = Template_test_B.Product_c[i] +
        Template_test_B.nuSwitch[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product2' */
      Template_test_B.Product2_n[i] = 0.0;
      Template_test_B.Product2_n[i] = Template_test_B.Add3[i] *
        Template_test_B.Add_a[0] + Template_test_B.Product2_n[i];
      Template_test_B.Product2_n[i] = Template_test_B.Add3[i + 3] *
        Template_test_B.Add_a[1] + Template_test_B.Product2_n[i];
      Template_test_B.Product2_n[i] = Template_test_B.Add3[i + 6] *
        Template_test_B.Add_a[2] + Template_test_B.Product2_n[i];

      /* Sum: '<S47>/Add1' */
      Template_test_B.Add1_a[i] = Template_test_B.VectorConcatenate_p[i] +
        Template_test_B.VectorConcatenate_n[i];
    }

    /* Product: '<S47>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_5 = 0; tmp_5 < 3; tmp_5++) {
        tmp_2[i + 3 * tmp_5] = 0.0;
        tmp_2[i + 3 * tmp_5] = tmp_2[3 * tmp_5 + i] +
          Template_test_B.MathFunction_n[3 * tmp_5] *
          Template_test_B.MathFunction_k[i];
        tmp_2[i + 3 * tmp_5] = Template_test_B.MathFunction_n[3 * tmp_5 + 1] *
          Template_test_B.MathFunction_k[i + 3] + tmp_2[3 * tmp_5 + i];
        tmp_2[i + 3 * tmp_5] = Template_test_B.MathFunction_n[3 * tmp_5 + 2] *
          Template_test_B.MathFunction_k[i + 6] + tmp_2[3 * tmp_5 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      Template_test_B.Product3[i] = 0.0;
      Template_test_B.Product3[i] = tmp_2[i] * Template_test_B.Add1_a[0] +
        Template_test_B.Product3[i];
      Template_test_B.Product3[i] = tmp_2[i + 3] * Template_test_B.Add1_a[1] +
        Template_test_B.Product3[i];
      Template_test_B.Product3[i] = tmp_2[i + 6] * Template_test_B.Add1_a[2] +
        Template_test_B.Product3[i];
    }

    /* Trigonometry: '<S113>/Trigonometric Function' */
    Template_test_B.TrigonometricFunction_m = cos(Template_test_B.Sum_pn);

    /* Trigonometry: '<S113>/Trigonometric Function1' */
    Template_test_B.TrigonometricFunction1 = sin(Template_test_B.Sum_pn);

    /* Derivative Block: '<S99>/Derivative' */
    {
      real_T t = Template_test_M->Timing.t[0];
      real_T timeStampA = Template_test_DWork.Derivative_RWORK_o.TimeStampA;
      real_T timeStampB = Template_test_DWork.Derivative_RWORK_o.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        Template_test_B.Derivative_g = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &Template_test_DWork.Derivative_RWORK_o.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 2;
          }
        } else if (timeStampA >= t) {
          lastBank += 2;
        }

        deltaT = t - *lastBank++;
        Template_test_B.Derivative_g = (Template_test_P.u_dm_Value - *lastBank++)
          / deltaT;
      }
    }

    /* Product: '<S113>/Product' */
    Template_test_B.Product_kh[0] = Template_test_B.TrigonometricFunction_m *
      Template_test_B.Derivative_g;
    Template_test_B.Product_kh[1] = Template_test_B.TrigonometricFunction1 *
      Template_test_B.Derivative_g;

    /* SignalConversion: '<S54>/ConcatBufferAtVector ConcatenateIn1' */
    Template_test_B.VectorConcatenate_nq[0] = Template_test_B.Product_kh[0];
    Template_test_B.VectorConcatenate_nq[1] = Template_test_B.Product_kh[1];

    /* Product: '<S54>/Product1' */
    tmp = Template_test_B.u_b[0] * Template_test_B.Product_kh[0];
    tmp += Template_test_B.u_b[1] * Template_test_B.Product_kh[1];
    Template_test_B.VectorConcatenate_nq[2] = tmp;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Constant: '<S60>/0_2x1' */
      Template_test_B.VectorConcatenate_b[0] = Template_test_P._2x1_Value_i[0];
      Template_test_B.VectorConcatenate_b[1] = Template_test_P._2x1_Value_i[1];
    }

    /* Math: '<S117>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2_m = tmp * tmp;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S117>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2_a = tmp * tmp;
    }

    /* Sum: '<S117>/Add' */
    Template_test_B.Add_pz = Template_test_B.epsilon_n2_m +
      Template_test_B.Delta2_a;

    /* Math: '<S117>/sqrt' */
    tmp = Template_test_B.Add_pz;
    if (tmp < 0.0) {
      Template_test_B.sqrt_ge = -sqrt(-tmp);
    } else {
      Template_test_B.sqrt_ge = sqrt(tmp);
    }

    /* Product: '<S117>/Divide' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Divide_a = Template_test_P.Deltam_Value /
      Template_test_B.sqrt_ge;

    /* Product: '<S167>/Divide' */
    Template_test_B.Divide_j = Template_test_B.Derivative_g /
      Template_test_B.Add_e;

    /* Product: '<S117>/Product' */
    Template_test_B.Product_kl = Template_test_B.Divide_a *
      Template_test_B.Divide_j;

    /* Product: '<S60>/Product1' */
    Template_test_B.VectorConcatenate_b[2] = Template_test_B.Subtract_h *
      Template_test_B.Product_kl;

    /* Sum: '<S47>/Add2' */
    Template_test_B.Add2[0] = Template_test_B.VectorConcatenate_nq[0] +
      Template_test_B.VectorConcatenate_b[0];
    Template_test_B.Add2[1] = Template_test_B.VectorConcatenate_nq[1] +
      Template_test_B.VectorConcatenate_b[1];
    Template_test_B.Add2[2] = Template_test_B.VectorConcatenate_nq[2] +
      Template_test_B.VectorConcatenate_b[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product4' */
      Template_test_B.Product4[i] = 0.0;
      Template_test_B.Product4[i] = Template_test_B.MathFunction_n[i] *
        Template_test_B.Add2[0] + Template_test_B.Product4[i];
      Template_test_B.Product4[i] = Template_test_B.MathFunction_n[i + 3] *
        Template_test_B.Add2[1] + Template_test_B.Product4[i];
      Template_test_B.Product4[i] = Template_test_B.MathFunction_n[i + 6] *
        Template_test_B.Add2[2] + Template_test_B.Product4[i];

      /* Sum: '<S47>/Sum' */
      Template_test_B.Sum_l[i] = (Template_test_B.Product3[i] -
        Template_test_B.Product2_n[i]) + Template_test_B.Product4[i];
    }

    /* Product: '<S39>/Product4' */
    for (i = 0; i < 3; i++) {
      Template_test_B.Product4_p[i] = 0.0;
      Template_test_B.Product4_p[i] = Template_test_B.x3[i] *
        Template_test_B.Sum_l[0] + Template_test_B.Product4_p[i];
      Template_test_B.Product4_p[i] = Template_test_B.x3[i + 3] *
        Template_test_B.Sum_l[1] + Template_test_B.Product4_p[i];
      Template_test_B.Product4_p[i] = Template_test_B.x3[i + 6] *
        Template_test_B.Sum_l[2] + Template_test_B.Product4_p[i];
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
      for (i = 0; i < 9; i++) {
        /* Product: '<S45>/Product1' incorporates:
         *  Constant: '<S5>/kappa_1'
         *  Constant: '<S64>/Constant'
         */
        Template_test_B.Product1_mo[i] = Template_test_P.kappa_1_Value *
          Template_test_P.Constant_Value_ks[i];

        /* Sum: '<S45>/Add' */
        Template_test_B.Add_e5[i] = Template_test_B.ux3_b[i] +
          Template_test_B.Product1_mo[i];
      }
    }

    /* Concatenate: '<S109>/Matrix Concatenate' incorporates:
     *  Constant: '<S143>/Constant'
     */
    Template_test_B.MatrixConcatenate[0] = Template_test_P.Constant_Value_m[0];
    Template_test_B.MatrixConcatenate[1] = Template_test_P.Constant_Value_m[1];
    Template_test_B.MatrixConcatenate[3] = Template_test_P.Constant_Value_m[2];
    Template_test_B.MatrixConcatenate[4] = Template_test_P.Constant_Value_m[3];
    Template_test_B.MatrixConcatenate[2] = Template_test_B.u_b[0];
    Template_test_B.MatrixConcatenate[5] = Template_test_B.u_b[1];

    /* Product: '<S45>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_5 = 0; tmp_5 < 3; tmp_5++) {
        tmp_2[i + 3 * tmp_5] = 0.0;
        tmp_2[i + 3 * tmp_5] = tmp_2[3 * tmp_5 + i] +
          Template_test_B.MathFunction_n[3 * tmp_5] * Template_test_B.Add_e5[i];
        tmp_2[i + 3 * tmp_5] = Template_test_B.MathFunction_n[3 * tmp_5 + 1] *
          Template_test_B.Add_e5[i + 3] + tmp_2[3 * tmp_5 + i];
        tmp_2[i + 3 * tmp_5] = Template_test_B.MathFunction_n[3 * tmp_5 + 2] *
          Template_test_B.Add_e5[i + 6] + tmp_2[3 * tmp_5 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_5 = 0; tmp_5 < 2; tmp_5++) {
        Template_test_B.Product3_i[i + 3 * tmp_5] = 0.0;
        Template_test_B.Product3_i[i + 3 * tmp_5] = Template_test_B.Product3_i[3
          * tmp_5 + i] + Template_test_B.MatrixConcatenate[3 * tmp_5] * tmp_2[i];
        Template_test_B.Product3_i[i + 3 * tmp_5] =
          Template_test_B.MatrixConcatenate[3 * tmp_5 + 1] * tmp_2[i + 3] +
          Template_test_B.Product3_i[3 * tmp_5 + i];
        Template_test_B.Product3_i[i + 3 * tmp_5] =
          Template_test_B.MatrixConcatenate[3 * tmp_5 + 2] * tmp_2[i + 6] +
          Template_test_B.Product3_i[3 * tmp_5 + i];
      }
    }

    /* Trigonometry: '<S111>/Trigonometric Function1' */
    Template_test_B.TrigonometricFunction1_c = sin(Template_test_B.Sum_pn);

    /* Gain: '<S111>/Gain' */
    Template_test_B.Gain_pg = Template_test_P.Gain_Gain_p5 *
      Template_test_B.TrigonometricFunction1_c;

    /* Trigonometry: '<S111>/Trigonometric Function' */
    Template_test_B.TrigonometricFunction_k = cos(Template_test_B.Sum_pn);

    /* Product: '<S111>/Product1' */
    Template_test_B.Product1_dm[0] = Template_test_B.Gain_pg *
      Template_test_B.u_b[0];

    /* Product: '<S111>/Product2' */
    Template_test_B.Product2_a[0] = Template_test_B.TrigonometricFunction_k *
      Template_test_B.u_b[0];

    /* Product: '<S111>/Product1' */
    Template_test_B.Product1_dm[1] = Template_test_B.Gain_pg *
      Template_test_B.u_b[1];

    /* Product: '<S111>/Product2' */
    Template_test_B.Product2_a[1] = Template_test_B.TrigonometricFunction_k *
      Template_test_B.u_b[1];

    /* Concatenate: '<S111>/Matrix Concatenate' */
    Template_test_B.MatrixConcatenate_o[0] = Template_test_B.Product1_dm[0];
    Template_test_B.MatrixConcatenate_o[2] = Template_test_B.Product1_dm[1];
    Template_test_B.MatrixConcatenate_o[1] = Template_test_B.Product2_a[0];
    Template_test_B.MatrixConcatenate_o[3] = Template_test_B.Product2_a[1];

    /* Product: '<S111>/Product' incorporates:
     *  Constant: '<S7>/u_d [m]'
     */
    Template_test_B.Product_me[0] = Template_test_B.MatrixConcatenate_o[0] *
      Template_test_P.u_dm_Value;
    Template_test_B.Product_me[1] = Template_test_B.MatrixConcatenate_o[1] *
      Template_test_P.u_dm_Value;
    Template_test_B.Product_me[2] = Template_test_B.MatrixConcatenate_o[2] *
      Template_test_P.u_dm_Value;
    Template_test_B.Product_me[3] = Template_test_B.MatrixConcatenate_o[3] *
      Template_test_P.u_dm_Value;

    /* Product: '<S127>/Product2' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product2_ho = Template_test_P.Deltam_Value *
      Template_test_B.MultiportSelector;

    /* Math: '<S55>/Math Function' */
    Template_test_B.MathFunction_m5[0] = Template_test_B.Product_o[0];

    /* Math: '<S127>/Math Function' */
    Template_test_B.MathFunction_js[0] = Template_test_B.MultiportSelector1[0];

    /* Math: '<S55>/Math Function' */
    Template_test_B.MathFunction_m5[1] = Template_test_B.Product_o[1];

    /* Math: '<S127>/Math Function' */
    Template_test_B.MathFunction_js[1] = Template_test_B.MultiportSelector1[1];

    /* Product: '<S127>/Product3' */
    Template_test_B.Product3_o[0] = 0.0;
    Template_test_B.Product3_o[0] = Template_test_B.MathFunction_js[0] *
      Template_test_B.MultiportSelector1[0] + Template_test_B.Product3_o[0];
    Template_test_B.Product3_o[2] = 0.0;
    Template_test_B.Product3_o[2] = Template_test_B.MathFunction_js[0] *
      Template_test_B.MultiportSelector1[1] + Template_test_B.Product3_o[2];
    Template_test_B.Product3_o[1] = 0.0;
    Template_test_B.Product3_o[1] = Template_test_B.MathFunction_js[1] *
      Template_test_B.MultiportSelector1[0] + Template_test_B.Product3_o[1];
    Template_test_B.Product3_o[3] = 0.0;
    Template_test_B.Product3_o[3] = Template_test_B.MathFunction_js[1] *
      Template_test_B.MultiportSelector1[1] + Template_test_B.Product3_o[3];

    /* Product: '<S127>/Product4' */
    Template_test_B.Product4_e[0] = Template_test_B.Product2_ho *
      Template_test_B.Product3_o[0];

    /* Gain: '<S127>/2' */
    Template_test_B.u_g[0] = Template_test_P._Gain_e *
      Template_test_B.Product4_e[0];

    /* Product: '<S127>/Product4' */
    Template_test_B.Product4_e[1] = Template_test_B.Product2_ho *
      Template_test_B.Product3_o[1];

    /* Gain: '<S127>/2' */
    Template_test_B.u_g[1] = Template_test_P._Gain_e *
      Template_test_B.Product4_e[1];

    /* Product: '<S127>/Product4' */
    Template_test_B.Product4_e[2] = Template_test_B.Product2_ho *
      Template_test_B.Product3_o[2];

    /* Gain: '<S127>/2' */
    Template_test_B.u_g[2] = Template_test_P._Gain_e *
      Template_test_B.Product4_e[2];

    /* Product: '<S127>/Product4' */
    Template_test_B.Product4_e[3] = Template_test_B.Product2_ho *
      Template_test_B.Product3_o[3];

    /* Gain: '<S127>/2' */
    Template_test_B.u_g[3] = Template_test_P._Gain_e *
      Template_test_B.Product4_e[3];
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S127>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2_e = tmp * tmp;
    }

    /* Math: '<S127>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2_bp = tmp * tmp;

    /* Sum: '<S127>/Add' */
    Template_test_B.Add_c = Template_test_B.Delta2_e +
      Template_test_B.epsilon_n2_bp;

    /* Math: '<S127>/( )^2' */
    tmp = Template_test_B.Add_c;
    Template_test_B.u_h = tmp * tmp;

    /* Product: '<S127>/Divide' */
    Template_test_B.Divide_et[0] = Template_test_B.u_g[0] / Template_test_B.u_h;
    Template_test_B.Divide_et[1] = Template_test_B.u_g[1] / Template_test_B.u_h;
    Template_test_B.Divide_et[2] = Template_test_B.u_g[2] / Template_test_B.u_h;
    Template_test_B.Divide_et[3] = Template_test_B.u_g[3] / Template_test_B.u_h;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Product: '<S127>/Product1' incorporates:
       *  Constant: '<S108>/0_2x2'
       *  Constant: '<S7>/Delta [m]'
       */
      Template_test_B.Product1_dz[0] = Template_test_P.Deltam_Value *
        Template_test_P._2x2_Value[0];
      Template_test_B.Product1_dz[1] = Template_test_P.Deltam_Value *
        Template_test_P._2x2_Value[1];
      Template_test_B.Product1_dz[2] = Template_test_P.Deltam_Value *
        Template_test_P._2x2_Value[2];
      Template_test_B.Product1_dz[3] = Template_test_P.Deltam_Value *
        Template_test_P._2x2_Value[3];
    }

    /* Product: '<S127>/Divide1' */
    Template_test_B.Divide1[0] = Template_test_B.Product1_dz[0] /
      Template_test_B.Add_c;

    /* Sum: '<S127>/Subtract' */
    Template_test_B.Subtract_d1[0] = Template_test_B.Divide_et[0] -
      Template_test_B.Divide1[0];

    /* Product: '<S127>/Divide1' */
    Template_test_B.Divide1[1] = Template_test_B.Product1_dz[1] /
      Template_test_B.Add_c;

    /* Sum: '<S127>/Subtract' */
    Template_test_B.Subtract_d1[1] = Template_test_B.Divide_et[1] -
      Template_test_B.Divide1[1];

    /* Product: '<S127>/Divide1' */
    Template_test_B.Divide1[2] = Template_test_B.Product1_dz[2] /
      Template_test_B.Add_c;

    /* Sum: '<S127>/Subtract' */
    Template_test_B.Subtract_d1[2] = Template_test_B.Divide_et[2] -
      Template_test_B.Divide1[2];

    /* Product: '<S127>/Divide1' */
    Template_test_B.Divide1[3] = Template_test_B.Product1_dz[3] /
      Template_test_B.Add_c;

    /* Sum: '<S127>/Subtract' */
    Template_test_B.Subtract_d1[3] = Template_test_B.Divide_et[3] -
      Template_test_B.Divide1[3];

    /* Math: '<S56>/Math Function' */
    Template_test_B.MathFunction_ke[0] = Template_test_B.Subtract_d1[0];
    Template_test_B.MathFunction_ke[1] = Template_test_B.Subtract_d1[2];
    Template_test_B.MathFunction_ke[2] = Template_test_B.Subtract_d1[1];
    Template_test_B.MathFunction_ke[3] = Template_test_B.Subtract_d1[3];

    /* Product: '<S52>/Product' */
    Template_test_B.Product_oe[0] = 0.0;
    Template_test_B.Product_oe[0] = Template_test_B.MathFunction_m5[0] *
      Template_test_B.MathFunction_ke[0] + Template_test_B.Product_oe[0];
    Template_test_B.Product_oe[0] = Template_test_B.MathFunction_m5[1] *
      Template_test_B.MathFunction_ke[1] + Template_test_B.Product_oe[0];

    /* Product: '<S52>/Product1' */
    Template_test_B.Product1_b[0] = 0.0;
    Template_test_B.Product1_b[0] = Template_test_B.u_b[0] *
      Template_test_B.Product_me[0] + Template_test_B.Product1_b[0];
    Template_test_B.Product1_b[0] = Template_test_B.u_b[1] *
      Template_test_B.Product_me[1] + Template_test_B.Product1_b[0];

    /* Sum: '<S52>/Add' */
    Template_test_B.Add_pv[0] = Template_test_B.Product_oe[0] +
      Template_test_B.Product1_b[0];

    /* Product: '<S52>/Product' */
    Template_test_B.Product_oe[1] = 0.0;
    Template_test_B.Product_oe[1] = Template_test_B.MathFunction_m5[0] *
      Template_test_B.MathFunction_ke[2] + Template_test_B.Product_oe[1];
    Template_test_B.Product_oe[1] = Template_test_B.MathFunction_m5[1] *
      Template_test_B.MathFunction_ke[3] + Template_test_B.Product_oe[1];

    /* Product: '<S52>/Product1' */
    Template_test_B.Product1_b[1] = 0.0;
    Template_test_B.Product1_b[1] = Template_test_B.u_b[0] *
      Template_test_B.Product_me[2] + Template_test_B.Product1_b[1];
    Template_test_B.Product1_b[1] = Template_test_B.u_b[1] *
      Template_test_B.Product_me[3] + Template_test_B.Product1_b[1];

    /* Sum: '<S52>/Add' */
    Template_test_B.Add_pv[1] = Template_test_B.Product_oe[1] +
      Template_test_B.Product1_b[1];

    /* Concatenate: '<S52>/Matrix Concatenate' */
    Template_test_B.MatrixConcatenate_l[0] = Template_test_B.Product_me[0];
    Template_test_B.MatrixConcatenate_l[1] = Template_test_B.Product_me[1];
    Template_test_B.MatrixConcatenate_l[3] = Template_test_B.Product_me[2];
    Template_test_B.MatrixConcatenate_l[4] = Template_test_B.Product_me[3];
    Template_test_B.MatrixConcatenate_l[2] = Template_test_B.Add_pv[0];
    Template_test_B.MatrixConcatenate_l[5] = Template_test_B.Add_pv[1];

    /* Product: '<S128>/Product' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product_a4[0] = Template_test_P.Deltam_Value *
      Template_test_B.MultiportSelector * Template_test_B.MultiportSelector2 *
      Template_test_B.MultiportSelector1[0];

    /* Gain: '<S128>/2' */
    Template_test_B.u_bz[0] = Template_test_P._Gain_c *
      Template_test_B.Product_a4[0];

    /* Product: '<S128>/Product' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product_a4[1] = Template_test_P.Deltam_Value *
      Template_test_B.MultiportSelector * Template_test_B.MultiportSelector2 *
      Template_test_B.MultiportSelector1[1];

    /* Gain: '<S128>/2' */
    Template_test_B.u_bz[1] = Template_test_P._Gain_c *
      Template_test_B.Product_a4[1];
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S128>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2_g = tmp * tmp;
    }

    /* Math: '<S128>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2_mi = tmp * tmp;

    /* Sum: '<S128>/Add' */
    Template_test_B.Add_g5 = Template_test_B.Delta2_g +
      Template_test_B.epsilon_n2_mi;

    /* Math: '<S128>/( )^2' */
    tmp = Template_test_B.Add_g5;
    Template_test_B.u_n = tmp * tmp;

    /* Product: '<S128>/Divide' */
    Template_test_B.Divide_m[0] = Template_test_B.u_bz[0] / Template_test_B.u_n;
    Template_test_B.Divide_m[1] = Template_test_B.u_bz[1] / Template_test_B.u_n;

    /* Product: '<S140>/Product1' */
    for (i = 0; i < 2; i++) {
      Template_test_B.Product1_ha[i] = 0.0;
      Template_test_B.Product1_ha[i] = Template_test_B.MathFunction_e[i] *
        Template_test_B.MathFunction_g[0] + Template_test_B.Product1_ha[i];
      Template_test_B.Product1_ha[i] = Template_test_B.MathFunction_e[i + 2] *
        Template_test_B.MathFunction_g[1] + Template_test_B.Product1_ha[i];
      Template_test_B.Product1_ha[i + 2] = 0.0;
      Template_test_B.Product1_ha[i + 2] = Template_test_B.Product1_ha[i + 2] +
        Template_test_B.MathFunction_e[i] * Template_test_B.MathFunction_g[2];
      Template_test_B.Product1_ha[i + 2] = Template_test_B.MathFunction_e[i + 2]
        * Template_test_B.MathFunction_g[3] + Template_test_B.Product1_ha[i + 2];
    }

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S108>/Multiport Selector3' */
    {
      const byte_T *u = (byte_T *)Template_test_B.Product1_ha;/* input port */
      const int32_T *index = (const int32_T *)&Template_test_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&Template_test_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)Template_test_B.MultiportSelector3;
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
    }                                  /* end <S108>/Multiport Selector3 */

    /* Product: '<S128>/Product1' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product1_g[0] = Template_test_P.Deltam_Value *
      Template_test_B.MultiportSelector3[0];

    /* Product: '<S128>/Divide1' */
    Template_test_B.Divide1_a[0] = Template_test_B.Product1_g[0] /
      Template_test_B.Add_g5;

    /* Sum: '<S128>/Subtract' */
    Template_test_B.Subtract_l1[0] = Template_test_B.Divide_m[0] -
      Template_test_B.Divide1_a[0];

    /* Product: '<S58>/Product' */
    Template_test_B.Product_c5[0] = Template_test_B.Subtract_l1[0] *
      Template_test_B.Subtract_d;

    /* Product: '<S115>/Product1' */
    Template_test_B.Product1_nn[0] = Template_test_B.MultiportSelector *
      Template_test_B.MultiportSelector1[0];

    /* Product: '<S128>/Product1' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product1_g[1] = Template_test_P.Deltam_Value *
      Template_test_B.MultiportSelector3[1];

    /* Product: '<S128>/Divide1' */
    Template_test_B.Divide1_a[1] = Template_test_B.Product1_g[1] /
      Template_test_B.Add_g5;

    /* Sum: '<S128>/Subtract' */
    Template_test_B.Subtract_l1[1] = Template_test_B.Divide_m[1] -
      Template_test_B.Divide1_a[1];

    /* Product: '<S58>/Product' */
    Template_test_B.Product_c5[1] = Template_test_B.Subtract_l1[1] *
      Template_test_B.Subtract_d;

    /* Product: '<S115>/Product1' */
    Template_test_B.Product1_nn[1] = Template_test_B.MultiportSelector *
      Template_test_B.MultiportSelector1[1];

    /* Math: '<S115>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2_h = tmp * tmp;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S115>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2_k = tmp * tmp;
    }

    /* Sum: '<S115>/Add' */
    Template_test_B.Add_k = Template_test_B.epsilon_n2_h +
      Template_test_B.Delta2_k;

    /* Math: '<S115>/^3//2' incorporates:
     *  Constant: '<S115>/3//2'
     */
    if ((Template_test_B.Add_k < 0.0) && (Template_test_P.u_Value_pq > floor
         (Template_test_P.u_Value_pq))) {
      Template_test_B.u2 = -rt_pow_snf(-Template_test_B.Add_k,
        Template_test_P.u_Value_pq);
    } else {
      Template_test_B.u2 = rt_pow_snf(Template_test_B.Add_k,
        Template_test_P.u_Value_pq);
    }

    /* Product: '<S115>/Divide' */
    Template_test_B.Divide_n[0] = Template_test_B.Product1_nn[0] /
      Template_test_B.u2;

    /* Product: '<S115>/Product' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product_d0[0] = Template_test_P.Deltam_Value *
      Template_test_B.Divide_n[0] * Template_test_B.Divide_o;

    /* Math: '<S122>/Math Function' */
    Template_test_B.MathFunction_e5[0] = Template_test_B.Add[0];

    /* Product: '<S119>/Divide' */
    Template_test_B.Divide_ef[0] = Template_test_B.MathFunction_e5[0] /
      Template_test_B.Add_e;

    /* Product: '<S119>/Product' incorporates:
     *  Constant: '<S7>/my [-]'
     */
    Template_test_B.Product_g[0] = Template_test_P.my_Value *
      Template_test_B.Divide_ef[0];

    /* Gain: '<S119>/Gain' */
    Template_test_B.Gain_cj[0] = Template_test_P.Gain_Gain_g *
      Template_test_B.Product_g[0];

    /* Sum: '<S115>/Sum' */
    Template_test_B.Sum_la[0] = (0.0 - Template_test_B.Product_d0[0]) -
      Template_test_B.Gain_cj[0];

    /* Product: '<S58>/Product1' */
    Template_test_B.Product1_az[0] = Template_test_B.Subtract_h *
      Template_test_B.Sum_la[0];

    /* Sum: '<S58>/Add' */
    Template_test_B.Add_av[0] = Template_test_B.Product_c5[0] +
      Template_test_B.Product1_az[0];

    /* Product: '<S115>/Divide' */
    Template_test_B.Divide_n[1] = Template_test_B.Product1_nn[1] /
      Template_test_B.u2;

    /* Product: '<S115>/Product' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product_d0[1] = Template_test_P.Deltam_Value *
      Template_test_B.Divide_n[1] * Template_test_B.Divide_o;

    /* Math: '<S122>/Math Function' */
    Template_test_B.MathFunction_e5[1] = Template_test_B.Add[1];

    /* Product: '<S119>/Divide' */
    Template_test_B.Divide_ef[1] = Template_test_B.MathFunction_e5[1] /
      Template_test_B.Add_e;

    /* Product: '<S119>/Product' incorporates:
     *  Constant: '<S7>/my [-]'
     */
    Template_test_B.Product_g[1] = Template_test_P.my_Value *
      Template_test_B.Divide_ef[1];

    /* Gain: '<S119>/Gain' */
    Template_test_B.Gain_cj[1] = Template_test_P.Gain_Gain_g *
      Template_test_B.Product_g[1];

    /* Sum: '<S115>/Sum' */
    Template_test_B.Sum_la[1] = (0.0 - Template_test_B.Product_d0[1]) -
      Template_test_B.Gain_cj[1];

    /* Product: '<S58>/Product1' */
    Template_test_B.Product1_az[1] = Template_test_B.Subtract_h *
      Template_test_B.Sum_la[1];

    /* Sum: '<S58>/Add' */
    Template_test_B.Add_av[1] = Template_test_B.Product_c5[1] +
      Template_test_B.Product1_az[1];

    /* Concatenate: '<S58>/Matrix Concatenate' incorporates:
     *  Constant: '<S58>/0_2x2'
     */
    Template_test_B.MatrixConcatenate_b[0] = Template_test_P._2x2_Value_j[0];
    Template_test_B.MatrixConcatenate_b[1] = Template_test_P._2x2_Value_j[1];
    Template_test_B.MatrixConcatenate_b[3] = Template_test_P._2x2_Value_j[2];
    Template_test_B.MatrixConcatenate_b[4] = Template_test_P._2x2_Value_j[3];
    Template_test_B.MatrixConcatenate_b[2] = Template_test_B.Add_av[0];
    Template_test_B.MatrixConcatenate_b[5] = Template_test_B.Add_av[1];

    /* Sum: '<S45>/Add2' */
    for (i = 0; i < 6; i++) {
      Template_test_B.Add2_d[i] = Template_test_B.MatrixConcatenate_l[i] +
        Template_test_B.MatrixConcatenate_b[i];
    }

    /* Product: '<S45>/Product4' */
    for (i = 0; i < 3; i++) {
      for (tmp_5 = 0; tmp_5 < 2; tmp_5++) {
        Template_test_B.Product4_d[i + 3 * tmp_5] = 0.0;
        Template_test_B.Product4_d[i + 3 * tmp_5] = Template_test_B.Product4_d[3
          * tmp_5 + i] + Template_test_B.Add2_d[3 * tmp_5] *
          Template_test_B.MathFunction_n[i];
        Template_test_B.Product4_d[i + 3 * tmp_5] = Template_test_B.Add2_d[3 *
          tmp_5 + 1] * Template_test_B.MathFunction_n[i + 3] +
          Template_test_B.Product4_d[3 * tmp_5 + i];
        Template_test_B.Product4_d[i + 3 * tmp_5] = Template_test_B.Add2_d[3 *
          tmp_5 + 2] * Template_test_B.MathFunction_n[i + 6] +
          Template_test_B.Product4_d[3 * tmp_5 + i];
      }
    }

    /* Sum: '<S45>/Add3' */
    for (i = 0; i < 6; i++) {
      Template_test_B.Add3_a[i] = Template_test_B.Product3_i[i] +
        Template_test_B.Product4_d[i];
    }

    /* Integrator Block: '<S42>/Integrator2'
     */
    if (rtmIsMajorTimeStep(Template_test_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &Template_test_PrevZCSigState.Integrator2_Reset_ZCE,
                         Template_test_P.Resetomega_q_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || Template_test_P.Resetomega_q_Value != 0.0) {
        Template_test_X.Integrator2_CSTATE[0] = Template_test_P.Integrator2_IC;
        Template_test_X.Integrator2_CSTATE[1] = Template_test_P.Integrator2_IC;
      }
    }

    Template_test_B.Integrator2[0] = Template_test_X.Integrator2_CSTATE[0];
    Template_test_B.Integrator2[1] = Template_test_X.Integrator2_CSTATE[1];

    /* Sum: '<S39>/Add2' */
    Template_test_B.Add2_a[0] = Template_test_B.Integrator2[0] +
      Template_test_B.Product_o[0];
    Template_test_B.Add2_a[1] = Template_test_B.Integrator2[1] +
      Template_test_B.Product_o[1];

    /* Product: '<S39>/Product5' */
    for (i = 0; i < 3; i++) {
      for (tmp_5 = 0; tmp_5 < 2; tmp_5++) {
        tmp_4[i + 3 * tmp_5] = 0.0;
        tmp_4[i + 3 * tmp_5] = tmp_4[3 * tmp_5 + i] + Template_test_B.Add3_a[3 *
          tmp_5] * Template_test_B.x3[i];
        tmp_4[i + 3 * tmp_5] = Template_test_B.Add3_a[3 * tmp_5 + 1] *
          Template_test_B.x3[i + 3] + tmp_4[3 * tmp_5 + i];
        tmp_4[i + 3 * tmp_5] = Template_test_B.Add3_a[3 * tmp_5 + 2] *
          Template_test_B.x3[i + 6] + tmp_4[3 * tmp_5 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      Template_test_B.Product5[i] = 0.0;
      Template_test_B.Product5[i] = tmp_4[i] * Template_test_B.Add2_a[0] +
        Template_test_B.Product5[i];
      Template_test_B.Product5[i] = tmp_4[i + 3] * Template_test_B.Add2_a[1] +
        Template_test_B.Product5[i];
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
      for (i = 0; i < 9; i++) {
        /* Product: '<S46>/Product1' incorporates:
         *  Constant: '<S5>/kappa_1'
         *  Constant: '<S65>/Constant'
         */
        Template_test_B.Product1_l[i] = Template_test_P.kappa_1_Value *
          Template_test_P.Constant_Value_l[i];

        /* Sum: '<S46>/Add1' */
        Template_test_B.Add1_g[i] = Template_test_B.ux3_b[i] +
          Template_test_B.Product1_l[i];
      }

      /* Constant: '<S109>/0_2x1' */
      Template_test_B.VectorConcatenate1[0] = Template_test_P._2x1_Value_l[0];
      Template_test_B.VectorConcatenate1[1] = Template_test_P._2x1_Value_l[1];
    }

    /* SignalConversion: '<S109>/ConcatBufferAtVector Concatenate1In2' */
    Template_test_B.VectorConcatenate1[2] = Template_test_B.Subtract_h;

    /* Product: '<S46>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_5 = 0; tmp_5 < 3; tmp_5++) {
        tmp_2[i + 3 * tmp_5] = 0.0;
        tmp_2[i + 3 * tmp_5] = tmp_2[3 * tmp_5 + i] +
          Template_test_B.MathFunction_n[3 * tmp_5] * Template_test_B.Add1_g[i];
        tmp_2[i + 3 * tmp_5] = Template_test_B.MathFunction_n[3 * tmp_5 + 1] *
          Template_test_B.Add1_g[i + 3] + tmp_2[3 * tmp_5 + i];
        tmp_2[i + 3 * tmp_5] = Template_test_B.MathFunction_n[3 * tmp_5 + 2] *
          Template_test_B.Add1_g[i + 6] + tmp_2[3 * tmp_5 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      Template_test_B.Product3_f[i] = 0.0;
      Template_test_B.Product3_f[i] = tmp_2[i] *
        Template_test_B.VectorConcatenate1[0] + Template_test_B.Product3_f[i];
      Template_test_B.Product3_f[i] = tmp_2[i + 3] *
        Template_test_B.VectorConcatenate1[1] + Template_test_B.Product3_f[i];
      Template_test_B.Product3_f[i] = tmp_2[i + 6] *
        Template_test_B.VectorConcatenate1[2] + Template_test_B.Product3_f[i];
    }

    /* Trigonometry: '<S112>/Trigonometric Function1' */
    Template_test_B.TrigonometricFunction1_b = sin(Template_test_B.Sum_pn);

    /* Gain: '<S112>/Gain' */
    Template_test_B.Gain_dr = Template_test_P.Gain_Gain_o0 *
      Template_test_B.TrigonometricFunction1_b;

    /* Product: '<S112>/Product1' */
    Template_test_B.Product1_c = Template_test_B.Gain_dr *
      Template_test_B.Subtract_h;

    /* Trigonometry: '<S112>/Trigonometric Function' */
    Template_test_B.TrigonometricFunction_o = cos(Template_test_B.Sum_pn);

    /* Product: '<S112>/Product2' */
    Template_test_B.Product2_hd = Template_test_B.TrigonometricFunction_o *
      Template_test_B.Subtract_h;

    /* SignalConversion: '<S112>/TmpHiddenBufferAtProductInport1' */
    Template_test_B.TmpHiddenBufferAtProductInpor_o[0] =
      Template_test_B.Product1_c;
    Template_test_B.TmpHiddenBufferAtProductInpor_o[1] =
      Template_test_B.Product2_hd;

    /* Product: '<S112>/Product' incorporates:
     *  Constant: '<S7>/u_d [m]'
     */
    Template_test_B.Product_hn[0] =
      Template_test_B.TmpHiddenBufferAtProductInpor_o[0] *
      Template_test_P.u_dm_Value;
    Template_test_B.Product_hn[1] =
      Template_test_B.TmpHiddenBufferAtProductInpor_o[1] *
      Template_test_P.u_dm_Value;

    /* SignalConversion: '<S53>/ConcatBufferAtVector ConcatenateIn1' */
    Template_test_B.VectorConcatenate_g[0] = Template_test_B.Product_hn[0];
    Template_test_B.VectorConcatenate_g[1] = Template_test_B.Product_hn[1];

    /* Product: '<S53>/Product' */
    tmp = Template_test_B.Subtract_l1[0] * Template_test_B.Product_o[0];
    tmp += Template_test_B.Subtract_l1[1] * Template_test_B.Product_o[1];
    Template_test_B.Product_lz = tmp;

    /* Product: '<S53>/Product1' */
    tmp = Template_test_B.u_b[0] * Template_test_B.Product_hn[0];
    tmp += Template_test_B.u_b[1] * Template_test_B.Product_hn[1];
    Template_test_B.Product1_cf = tmp;

    /* Sum: '<S53>/Add' */
    Template_test_B.VectorConcatenate_g[2] = Template_test_B.Product_lz +
      Template_test_B.Product1_cf;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Constant: '<S59>/0_2x1' */
      Template_test_B.VectorConcatenate_e[0] = Template_test_P._2x1_Value_b[0];
      Template_test_B.VectorConcatenate_e[1] = Template_test_P._2x1_Value_b[1];

      /* Product: '<S157>/Product' incorporates:
       *  Constant: '<S146>/0_2x1'
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Product_pb[0] = Template_test_P._2x1_Value_m[0] *
        Template_test_P.PathSelector_Value;
      Template_test_B.Product_pb[1] = Template_test_P._2x1_Value_m[1] *
        Template_test_P.PathSelector_Value;
    }

    /* Product: '<S150>/Product2' incorporates:
     *  Constant: '<S18>/k [-]'
     */
    Template_test_B.Product2_dr = Template_test_B.Integrator1 *
      Template_test_P.k_Value;

    /* Trigonometry: '<S150>/sin(s)3' */
    Template_test_B.sins3 = sin(Template_test_B.Product2_dr);
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S150>/Math Function' incorporates:
       *  Constant: '<S150>/Constant'
       *  Constant: '<S18>/k [-]'
       */
      if ((Template_test_P.k_Value < 0.0) && (Template_test_P.Constant_Value_n >
           floor(Template_test_P.Constant_Value_n))) {
        Template_test_B.MathFunction_dq = -rt_pow_snf(-Template_test_P.k_Value,
          Template_test_P.Constant_Value_n);
      } else {
        Template_test_B.MathFunction_dq = rt_pow_snf(Template_test_P.k_Value,
          Template_test_P.Constant_Value_n);
      }
    }

    /* Product: '<S150>/Product' incorporates:
     *  Constant: '<S18>/r_x [m]'
     */
    Template_test_B.Product_ch = Template_test_P.r_xm_Value *
      Template_test_B.sins3 * Template_test_B.MathFunction_dq;

    /* Trigonometry: '<S150>/cos(s)3' */
    Template_test_B.coss3 = cos(Template_test_B.Product2_dr);

    /* Product: '<S150>/Product1' incorporates:
     *  Constant: '<S18>/r_y [m]'
     */
    Template_test_B.Product1_en = Template_test_P.r_ym_Value *
      Template_test_B.coss3 * Template_test_B.MathFunction_dq;

    /* Gain: '<S150>/Gain' */
    Template_test_B.Gain_o = Template_test_P.Gain_Gain_ap *
      Template_test_B.Product1_en;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Sum: '<S157>/Subract' incorporates:
       *  Constant: '<S157>/Constant'
       *  Constant: '<S7>/Path Selector  [-]'
       */
      Template_test_B.Subract_e3 = Template_test_P.Constant_Value_a1 -
        Template_test_P.PathSelector_Value;
    }

    /* Product: '<S157>/Product1' */
    Template_test_B.Product1_kt[0] = Template_test_B.Product_ch *
      Template_test_B.Subract_e3;
    Template_test_B.Product1_kt[1] = Template_test_B.Gain_o *
      Template_test_B.Subract_e3;

    /* Sum: '<S157>/Add' */
    Template_test_B.Add_ej[0] = Template_test_B.Product_pb[0] +
      Template_test_B.Product1_kt[0];
    Template_test_B.Add_ej[1] = Template_test_B.Product_pb[1] +
      Template_test_B.Product1_kt[1];

    /* Product: '<S102>/x_d^s * y_d^s^3 ' */
    Template_test_B.x_dsy_ds3 = Template_test_B.Add[0] * Template_test_B.Add_ej
      [1];

    /* Product: '<S102>/x_d^s^3 * y_d^s' */
    Template_test_B.x_ds3y_ds = Template_test_B.Add_ej[0] * Template_test_B.Add
      [1];

    /* Sum: '<S102>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
    Template_test_B.x_dsy_ds3x_ds3y_ds = Template_test_B.x_dsy_ds3 -
      Template_test_B.x_ds3y_ds;

    /* Product: '<S102>/Product1' */
    Template_test_B.Product1_g2 = Template_test_B.x_dsy_ds3x_ds3y_ds *
      Template_test_B.x_ds2y_ds2;

    /* Product: '<S102>/x_d^s * x_d^s^2' */
    Template_test_B.x_dsx_ds2 = Template_test_B.Add[0] * Template_test_B.Add_f[0];

    /* Product: '<S102>/y_d^s * y_d^s^2' */
    Template_test_B.y_dsy_ds2 = Template_test_B.Add[1] * Template_test_B.Add_f[1];

    /* Sum: '<S102>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
    Template_test_B.x_dsx_ds2x_ds3y_ds = Template_test_B.x_dsx_ds2 +
      Template_test_B.y_dsy_ds2;

    /* Gain: '<S102>/+ 2' */
    Template_test_B.u_ab = Template_test_P.u_Gain_m *
      Template_test_B.x_dsx_ds2x_ds3y_ds;

    /* Product: '<S102>/Product2' */
    Template_test_B.Product2_d2 = Template_test_B.x_dsy_ds2x_ds2y_ds *
      Template_test_B.u_ab;

    /* Sum: '<S102>/Subtract' */
    Template_test_B.Subtract_n5 = Template_test_B.Product1_g2 -
      Template_test_B.Product2_d2;

    /* Math: '<S102>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
    tmp = Template_test_B.x_ds2y_ds2;
    Template_test_B.x_ds2y_ds22 = tmp * tmp;

    /* Product: '<S102>/Divide' */
    Template_test_B.Divide_d3 = Template_test_B.Subtract_n5 /
      Template_test_B.x_ds2y_ds22;

    /* Math: '<S130>/(epsilon_n^s)^2' */
    tmp = Template_test_B.MultiportSelector2;
    Template_test_B.epsilon_ns2 = tmp * tmp;

    /* Product: '<S130>/Product' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product_ol = Template_test_P.Deltam_Value *
      Template_test_B.MultiportSelector * Template_test_B.epsilon_ns2;

    /* Gain: '<S130>/2' */
    Template_test_B.u_j = Template_test_P._Gain_g * Template_test_B.Product_ol;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S130>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2_p4 = tmp * tmp;
    }

    /* Math: '<S130>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2_n = tmp * tmp;

    /* Sum: '<S130>/Add' */
    Template_test_B.Add_nw = Template_test_B.Delta2_p4 +
      Template_test_B.epsilon_n2_n;

    /* Math: '<S130>/( )^2' */
    tmp = Template_test_B.Add_nw;
    Template_test_B.u_o = tmp * tmp;

    /* Product: '<S130>/Divide' */
    Template_test_B.Divide_pq = Template_test_B.u_j / Template_test_B.u_o;

    /* Outputs for atomic SubSystem: '<S108>/S_2(psi_d^s^2)' */

    /* Gain: '<S137>/S12' */
    Template_test_B.S12_j = Template_test_P.S12_Gain_f *
      Template_test_B.Divide_d3;

    /* Reshape: '<S137>/S_2(psi_d^s^2)' incorporates:
     *  Constant: '<S137>/0'
     */
    Template_test_B.S_2psi_ds2[0] = Template_test_P._Value_o;
    Template_test_B.S_2psi_ds2[1] = Template_test_B.Divide_d3;
    Template_test_B.S_2psi_ds2[2] = Template_test_B.S12_j;
    Template_test_B.S_2psi_ds2[3] = Template_test_P._Value_o;

    /* end of Outputs for SubSystem: '<S108>/S_2(psi_d^s^2)' */

    /* Math: '<S138>/Math Function' */
    Template_test_B.MathFunction_l[0] = Template_test_B.S_2psi_ds2[0];
    Template_test_B.MathFunction_l[1] = Template_test_B.S_2psi_ds2[2];
    Template_test_B.MathFunction_l[2] = Template_test_B.S_2psi_ds2[1];
    Template_test_B.MathFunction_l[3] = Template_test_B.S_2psi_ds2[3];

    /* Product: '<S142>/Product' */
    for (i = 0; i < 2; i++) {
      Template_test_B.Product_k4[i] = 0.0;
      Template_test_B.Product_k4[i] = Template_test_B.MathFunction_e[i] *
        Template_test_B.MathFunction_e[0] + Template_test_B.Product_k4[i];
      Template_test_B.Product_k4[i] = Template_test_B.MathFunction_e[i + 2] *
        Template_test_B.MathFunction_e[1] + Template_test_B.Product_k4[i];
      Template_test_B.Product_k4[i + 2] = 0.0;
      Template_test_B.Product_k4[i + 2] = Template_test_B.Product_k4[i + 2] +
        Template_test_B.MathFunction_e[i] * Template_test_B.MathFunction_e[2];
      Template_test_B.Product_k4[i + 2] = Template_test_B.MathFunction_e[i + 2] *
        Template_test_B.MathFunction_e[3] + Template_test_B.Product_k4[i + 2];
    }

    /* Sum: '<S142>/Add' */
    Template_test_B.Add_an[0] = Template_test_B.MathFunction_l[0] +
      Template_test_B.Product_k4[0];
    Template_test_B.Add_an[1] = Template_test_B.MathFunction_l[1] +
      Template_test_B.Product_k4[1];
    Template_test_B.Add_an[2] = Template_test_B.MathFunction_l[2] +
      Template_test_B.Product_k4[2];
    Template_test_B.Add_an[3] = Template_test_B.MathFunction_l[3] +
      Template_test_B.Product_k4[3];

    /* Product: '<S142>/Product1' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += Template_test_B.Add_an[i] * Template_test_B.MathFunction_g[0];
      tmp_3[i] += Template_test_B.Add_an[i + 2] *
        Template_test_B.MathFunction_g[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += Template_test_B.Add_an[i] *
        Template_test_B.MathFunction_g[2];
      tmp_3[i + 2] += Template_test_B.Add_an[i + 2] *
        Template_test_B.MathFunction_g[3];
    }

    Template_test_B.Product1_hn[0] = 0.0;
    Template_test_B.Product1_hn[0] = tmp_3[0] * Template_test_B.Subtract_i[0] +
      Template_test_B.Product1_hn[0];
    Template_test_B.Product1_hn[0] = tmp_3[2] * Template_test_B.Subtract_i[1] +
      Template_test_B.Product1_hn[0];
    Template_test_B.Product1_hn[1] = 0.0;
    Template_test_B.Product1_hn[1] = tmp_3[1] * Template_test_B.Subtract_i[0] +
      Template_test_B.Product1_hn[1];
    Template_test_B.Product1_hn[1] = tmp_3[3] * Template_test_B.Subtract_i[1] +
      Template_test_B.Product1_hn[1];

    /* Product: '<S142>/Product2' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += Template_test_B.MathFunction_e[i] *
        Template_test_B.MathFunction_g[0];
      tmp_3[i] += Template_test_B.MathFunction_e[i + 2] *
        Template_test_B.MathFunction_g[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += Template_test_B.MathFunction_e[i] *
        Template_test_B.MathFunction_g[2];
      tmp_3[i + 2] += Template_test_B.MathFunction_e[i + 2] *
        Template_test_B.MathFunction_g[3];
    }

    Template_test_B.Product2_o[0] = 0.0;
    Template_test_B.Product2_o[0] = tmp_3[0] * Template_test_B.Add[0] +
      Template_test_B.Product2_o[0];
    Template_test_B.Product2_o[0] = tmp_3[2] * Template_test_B.Add[1] +
      Template_test_B.Product2_o[0];

    /* Gain: '<S142>/2' */
    Template_test_B.u_p[0] = Template_test_P._Gain_o *
      Template_test_B.Product2_o[0];

    /* Product: '<S142>/Product3' */
    Template_test_B.Product3_m[0] = 0.0;
    Template_test_B.Product3_m[0] = Template_test_B.MathFunction_g[0] *
      Template_test_B.Add_f[0] + Template_test_B.Product3_m[0];
    Template_test_B.Product3_m[0] = Template_test_B.MathFunction_g[2] *
      Template_test_B.Add_f[1] + Template_test_B.Product3_m[0];

    /* Sum: '<S142>/Sum' */
    Template_test_B.Sum_m[0] = (Template_test_B.Product1_hn[0] -
      Template_test_B.u_p[0]) - Template_test_B.Product3_m[0];

    /* Gain: '<S142>/Gain' */
    Template_test_B.Gain_e[0] = Template_test_P.Gain_Gain_n *
      Template_test_B.Sum_m[0];
    Template_test_B.Product2_o[1] = 0.0;
    Template_test_B.Product2_o[1] = tmp_3[1] * Template_test_B.Add[0] +
      Template_test_B.Product2_o[1];
    Template_test_B.Product2_o[1] = tmp_3[3] * Template_test_B.Add[1] +
      Template_test_B.Product2_o[1];

    /* Gain: '<S142>/2' */
    Template_test_B.u_p[1] = Template_test_P._Gain_o *
      Template_test_B.Product2_o[1];

    /* Product: '<S142>/Product3' */
    Template_test_B.Product3_m[1] = 0.0;
    Template_test_B.Product3_m[1] = Template_test_B.MathFunction_g[1] *
      Template_test_B.Add_f[0] + Template_test_B.Product3_m[1];
    Template_test_B.Product3_m[1] = Template_test_B.MathFunction_g[3] *
      Template_test_B.Add_f[1] + Template_test_B.Product3_m[1];

    /* Sum: '<S142>/Sum' */
    Template_test_B.Sum_m[1] = (Template_test_B.Product1_hn[1] -
      Template_test_B.u_p[1]) - Template_test_B.Product3_m[1];

    /* Gain: '<S142>/Gain' */
    Template_test_B.Gain_e[1] = Template_test_P.Gain_Gain_n *
      Template_test_B.Sum_m[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S108>/Multiport Selector4' */
    {
      const byte_T *u = (byte_T *)Template_test_B.Gain_e;/* input port */
      const int32_T *index = (const int32_T *)&Template_test_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&Template_test_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&Template_test_B.MultiportSelector4;
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
    }                                  /* end <S108>/Multiport Selector4 */

    /* Product: '<S130>/Product1' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product1_je = Template_test_P.Deltam_Value *
      Template_test_B.MultiportSelector4;

    /* Product: '<S130>/Divide1' */
    Template_test_B.Divide1_j = Template_test_B.Product1_je /
      Template_test_B.Add_nw;

    /* Sum: '<S130>/Sum' */
    Template_test_B.Sum_iy = (Template_test_B.Divide_d3 +
      Template_test_B.Divide_pq) - Template_test_B.Divide1_j;

    /* Product: '<S59>/Product' */
    Template_test_B.Product_m2 = Template_test_B.Sum_iy *
      Template_test_B.Subtract_d;

    /* Math: '<S168>/Math Function' */
    Template_test_B.MathFunction_jy[0] = Template_test_B.Add[0];
    Template_test_B.MathFunction_jy[1] = Template_test_B.Add[1];

    /* Product: '<S166>/Product1' */
    tmp = Template_test_B.MathFunction_jy[0] * Template_test_B.Add_f[0];
    tmp += Template_test_B.MathFunction_jy[1] * Template_test_B.Add_f[1];
    Template_test_B.Product1_lg = tmp;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S166>/|p_d^s|^3' incorporates:
       *  Constant: '<S166>/Constant'
       */
      if ((Template_test_B.Add_e < 0.0) && (Template_test_P.Constant_Value_da >
           floor(Template_test_P.Constant_Value_da))) {
        Template_test_B.p_ds3 = -rt_pow_snf(-Template_test_B.Add_e,
          Template_test_P.Constant_Value_da);
      } else {
        Template_test_B.p_ds3 = rt_pow_snf(Template_test_B.Add_e,
          Template_test_P.Constant_Value_da);
      }
    }

    /* Product: '<S166>/Divide' */
    Template_test_B.Divide_jj = Template_test_B.Product1_lg /
      Template_test_B.p_ds3;

    /* Product: '<S166>/Product' incorporates:
     *  Constant: '<S7>/u_d [m]'
     */
    Template_test_B.Product_j = Template_test_B.Divide_jj *
      Template_test_P.u_dm_Value;

    /* Gain: '<S166>/Gain' */
    Template_test_B.Gain_ds = Template_test_P.Gain_Gain_k *
      Template_test_B.Product_j;

    /* Math: '<S116>/epsilon_n^2' */
    tmp = Template_test_B.MultiportSelector;
    Template_test_B.epsilon_n2_jy = tmp * tmp;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S116>/Delta^2' incorporates:
       *  Constant: '<S7>/Delta [m]'
       */
      tmp = Template_test_P.Deltam_Value;
      Template_test_B.Delta2_gi = tmp * tmp;
    }

    /* Sum: '<S116>/Add' */
    Template_test_B.Add_if = Template_test_B.epsilon_n2_jy +
      Template_test_B.Delta2_gi;

    /* Math: '<S116>/Math Function' */
    tmp = Template_test_B.Add_if;
    if (tmp < 0.0) {
      Template_test_B.MathFunction_pl = -sqrt(-tmp);
    } else {
      Template_test_B.MathFunction_pl = sqrt(tmp);
    }

    /* Product: '<S116>/Divide' */
    Template_test_B.Divide_ep = Template_test_B.Gain_ds /
      Template_test_B.MathFunction_pl;

    /* Product: '<S116>/Product1' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product1_cj = Template_test_P.Deltam_Value *
      Template_test_B.Divide_ep;

    /* Product: '<S116>/Product2' */
    Template_test_B.Product2_ak = Template_test_B.MultiportSelector *
      Template_test_B.MultiportSelector2;

    /* Math: '<S116>/^3//2' incorporates:
     *  Constant: '<S116>/3//2'
     */
    if ((Template_test_B.Add_if < 0.0) && (Template_test_P.u_Value_dh > floor
         (Template_test_P.u_Value_dh))) {
      Template_test_B.u2_h = -rt_pow_snf(-Template_test_B.Add_if,
        Template_test_P.u_Value_dh);
    } else {
      Template_test_B.u2_h = rt_pow_snf(Template_test_B.Add_if,
        Template_test_P.u_Value_dh);
    }

    /* Product: '<S116>/Divide1' */
    Template_test_B.Divide1_d = Template_test_B.Product2_ak /
      Template_test_B.u2_h;

    /* Product: '<S116>/Product3' incorporates:
     *  Constant: '<S7>/Delta [m]'
     */
    Template_test_B.Product3_mg = Template_test_P.Deltam_Value *
      Template_test_B.Divide1_d * Template_test_B.Divide_o;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Product: '<S120>/Product1' incorporates:
       *  Constant: '<S7>/my [-]'
       */
      Template_test_B.Product1_p = Template_test_P.my_Value *
        Template_test_B.Add_e;
    }

    /* Math: '<S124>/Math Function' */
    Template_test_B.MathFunction_eo[0] = Template_test_B.Add_f[0];

    /* Product: '<S120>/Divide2' */
    Template_test_B.Divide2[0] = Template_test_B.MathFunction_eo[0] /
      Template_test_B.Add_e;

    /* Math: '<S123>/Math Function' */
    Template_test_B.MathFunction_i2[0] = Template_test_B.Add[0];

    /* Math: '<S124>/Math Function' */
    Template_test_B.MathFunction_eo[1] = Template_test_B.Add_f[1];

    /* Product: '<S120>/Divide2' */
    Template_test_B.Divide2[1] = Template_test_B.MathFunction_eo[1] /
      Template_test_B.Add_e;

    /* Math: '<S123>/Math Function' */
    Template_test_B.MathFunction_i2[1] = Template_test_B.Add[1];

    /* Product: '<S120>/Product2' */
    tmp = Template_test_B.MathFunction_eo[0] * Template_test_B.Add[0];
    tmp += Template_test_B.MathFunction_eo[1] * Template_test_B.Add[1];
    Template_test_B.Product2_nd[0] = tmp * Template_test_B.MathFunction_i2[0];
    Template_test_B.Product2_nd[1] = tmp * Template_test_B.MathFunction_i2[1];
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S120>/Math Function' incorporates:
       *  Constant: '<S120>/Constant'
       */
      if ((Template_test_B.Add_e < 0.0) && (Template_test_P.Constant_Value_gt >
           floor(Template_test_P.Constant_Value_gt))) {
        Template_test_B.MathFunction_py = -rt_pow_snf(-Template_test_B.Add_e,
          Template_test_P.Constant_Value_gt);
      } else {
        Template_test_B.MathFunction_py = rt_pow_snf(Template_test_B.Add_e,
          Template_test_P.Constant_Value_gt);
      }
    }

    /* Product: '<S120>/Divide1' */
    Template_test_B.Divide1_jw[0] = Template_test_B.Product2_nd[0] /
      Template_test_B.MathFunction_py;

    /* Sum: '<S120>/Subtract1' */
    Template_test_B.Subtract1_k[0] = Template_test_B.Divide2[0] -
      Template_test_B.Divide1_jw[0];

    /* Product: '<S120>/Divide1' */
    Template_test_B.Divide1_jw[1] = Template_test_B.Product2_nd[1] /
      Template_test_B.MathFunction_py;

    /* Sum: '<S120>/Subtract1' */
    Template_test_B.Subtract1_k[1] = Template_test_B.Divide2[1] -
      Template_test_B.Divide1_jw[1];

    /* Product: '<S120>/Product' incorporates:
     *  Constant: '<S7>/my [-]'
     */
    tmp = Template_test_P.my_Value * Template_test_B.Subtract1_k[0] *
      Template_test_B.Subtract_i[0];
    tmp += Template_test_P.my_Value * Template_test_B.Subtract1_k[1] *
      Template_test_B.Subtract_i[1];
    Template_test_B.Product_o1 = tmp;

    /* Sum: '<S120>/Subtract' */
    Template_test_B.Subtract_i2 = Template_test_B.Product1_p -
      Template_test_B.Product_o1;

    /* Sum: '<S116>/Sum' */
    Template_test_B.Sum_fp = (Template_test_B.Product1_cj -
      Template_test_B.Product3_mg) - Template_test_B.Subtract_i2;

    /* Product: '<S59>/Product1' */
    Template_test_B.Product1_a3 = Template_test_B.Subtract_h *
      Template_test_B.Sum_fp;

    /* Sum: '<S59>/Add' */
    Template_test_B.VectorConcatenate_e[2] = Template_test_B.Product_m2 +
      Template_test_B.Product1_a3;

    /* Sum: '<S46>/Add2' */
    Template_test_B.Add2_l[0] = Template_test_B.VectorConcatenate_g[0] +
      Template_test_B.VectorConcatenate_e[0];
    Template_test_B.Add2_l[1] = Template_test_B.VectorConcatenate_g[1] +
      Template_test_B.VectorConcatenate_e[1];
    Template_test_B.Add2_l[2] = Template_test_B.VectorConcatenate_g[2] +
      Template_test_B.VectorConcatenate_e[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S46>/Product4' */
      Template_test_B.Product4_g[i] = 0.0;
      Template_test_B.Product4_g[i] = Template_test_B.MathFunction_n[i] *
        Template_test_B.Add2_l[0] + Template_test_B.Product4_g[i];
      Template_test_B.Product4_g[i] = Template_test_B.MathFunction_n[i + 3] *
        Template_test_B.Add2_l[1] + Template_test_B.Product4_g[i];
      Template_test_B.Product4_g[i] = Template_test_B.MathFunction_n[i + 6] *
        Template_test_B.Add2_l[2] + Template_test_B.Product4_g[i];

      /* Sum: '<S46>/Add3' */
      Template_test_B.Add3_j[i] = Template_test_B.Product3_f[i] +
        Template_test_B.Product4_g[i];
    }

    for (i = 0; i < 3; i++) {
      tmp_6[i] = 0.0;
      tmp = tmp_6[i];
      tmp += Template_test_B.x3[i] * Template_test_B.Add3_j[0];
      tmp_6[i] = tmp;
      tmp = tmp_6[i];
      tmp += Template_test_B.x3[i + 3] * Template_test_B.Add3_j[1];
      tmp_6[i] = tmp;
      tmp = tmp_6[i];
      tmp += Template_test_B.x3[i + 6] * Template_test_B.Add3_j[2];
      tmp_6[i] = tmp;
      Template_test_B.Product6[i] = tmp_6[i] * Template_test_B.Subtract_d;

      /* Sum: '<S39>/Sum' */
      Template_test_B.Sum_po[i] = ((((Template_test_B.Product2_i4[i] -
        Template_test_B.Product_l[i]) - Template_test_B.Product1_k[i]) +
        Template_test_B.Product4_p[i]) + Template_test_B.Product5[i]) +
        Template_test_B.Product6[i];
    }

    /* MultiPortSwitch: '<S29>/tau Switch' incorporates:
     *  Constant: '<S1>/Control Mode Selector'
     */
    switch ((int32_T)Template_test_P.ControlModeSelector_Value) {
     case 0:
      Template_test_B.tauSwitch[0] = Template_test_B.Product[0];
      Template_test_B.tauSwitch[1] = Template_test_B.Product[1];
      Template_test_B.tauSwitch[2] = Template_test_B.Product[2];
      break;

     case 1:
      Template_test_B.tauSwitch[0] = Template_test_B.Sum1_b[0];
      Template_test_B.tauSwitch[1] = Template_test_B.Sum1_b[1];
      Template_test_B.tauSwitch[2] = Template_test_B.Sum1_b[2];
      break;

     default:
      Template_test_B.tauSwitch[0] = Template_test_B.Sum_po[0];
      Template_test_B.tauSwitch[1] = Template_test_B.Sum_po[1];
      Template_test_B.tauSwitch[2] = Template_test_B.Sum_po[2];
      break;
    }

    /* Sum: '<S42>/Add' */
    Template_test_B.Add_lp[0] = Template_test_B.Integrator2[0] +
      Template_test_B.Product_o[0];
    Template_test_B.Add_lp[1] = Template_test_B.Integrator2[1] +
      Template_test_B.Product_o[1];

    /* Math: '<S62>/Math Function' */
    Template_test_B.MathFunction_kw[0] = Template_test_B.Product_d[0];
    Template_test_B.MathFunction_kw[1] = Template_test_B.Product_d[1];
    Template_test_B.MathFunction_kw[2] = Template_test_B.Product_d[2];

    /* Product: '<S43>/Product' */
    for (i = 0; i < 3; i++) {
      tmp_6[i] = 0.0;
      tmp = tmp_6[i];
      tmp += Template_test_B.MathFunction_n[3 * i] *
        Template_test_B.MathFunction_kw[0];
      tmp_6[i] = tmp;
      tmp = tmp_6[i];
      tmp += Template_test_B.MathFunction_n[3 * i + 1] *
        Template_test_B.MathFunction_kw[1];
      tmp_6[i] = tmp;
      tmp = tmp_6[i];
      tmp += Template_test_B.MathFunction_n[3 * i + 2] *
        Template_test_B.MathFunction_kw[2];
      tmp_6[i] = tmp;
    }

    for (i = 0; i < 2; i++) {
      Template_test_B.Product_py[i] = 0.0;
      Template_test_B.Product_py[i] = Template_test_B.MatrixConcatenate[3 * i] *
        tmp_6[0] + Template_test_B.Product_py[i];
      Template_test_B.Product_py[i] = Template_test_B.MatrixConcatenate[3 * i +
        1] * tmp_6[1] + Template_test_B.Product_py[i];
      Template_test_B.Product_py[i] = Template_test_B.MatrixConcatenate[3 * i +
        2] * tmp_6[2] + Template_test_B.Product_py[i];

      /* Gain: '<S43>/Gain' */
      Template_test_B.Gain_i[i] = Template_test_P.Gain_Gain_p1 *
        Template_test_B.Product_py[i];

      /* Math: '<S61>/Math Function' */
      Template_test_B.MathFunction_ln[i] = Template_test_B.Gain_i[i];
    }

    /* Product: '<S42>/Product' */
    Template_test_B.Product_ce[0] = 0.0;
    Template_test_B.Product_ce[0] = Template_test_B.ux2[0] *
      Template_test_B.MathFunction_ln[0] + Template_test_B.Product_ce[0];
    Template_test_B.Product_ce[0] = Template_test_B.ux2[2] *
      Template_test_B.MathFunction_ln[1] + Template_test_B.Product_ce[0];

    /* Sum: '<S42>/Add1' */
    Template_test_B.Add1_f[0] = Template_test_B.Integrator2[0] +
      Template_test_B.Product_ce[0];

    /* Product: '<S42>/Product1' incorporates:
     *  Constant: '<S5>/lambda_q'
     */
    Template_test_B.Product1_kn[0] = Template_test_P.lambda_q_Value *
      Template_test_B.Add1_f[0];

    /* Gain: '<S42>/Gain' */
    Template_test_B.Gain_kq[0] = Template_test_P.Gain_Gain_os *
      Template_test_B.Product1_kn[0];

    /* Product: '<S42>/Product' */
    Template_test_B.Product_ce[1] = 0.0;
    Template_test_B.Product_ce[1] = Template_test_B.ux2[1] *
      Template_test_B.MathFunction_ln[0] + Template_test_B.Product_ce[1];
    Template_test_B.Product_ce[1] = Template_test_B.ux2[3] *
      Template_test_B.MathFunction_ln[1] + Template_test_B.Product_ce[1];

    /* Sum: '<S42>/Add1' */
    Template_test_B.Add1_f[1] = Template_test_B.Integrator2[1] +
      Template_test_B.Product_ce[1];

    /* Product: '<S42>/Product1' incorporates:
     *  Constant: '<S5>/lambda_q'
     */
    Template_test_B.Product1_kn[1] = Template_test_P.lambda_q_Value *
      Template_test_B.Add1_f[1];

    /* Gain: '<S42>/Gain' */
    Template_test_B.Gain_kq[1] = Template_test_P.Gain_Gain_os *
      Template_test_B.Product1_kn[1];

    /* Product: '<S50>/Product' */
    for (i = 0; i < 3; i++) {
      Template_test_B.Product_n[i] = 0.0;
      Template_test_B.Product_n[i] = Template_test_B.Rpsi[i] *
        Template_test_B.Subtract_o[0] + Template_test_B.Product_n[i];
      Template_test_B.Product_n[i] = Template_test_B.Rpsi[i + 3] *
        Template_test_B.Subtract_o[1] + Template_test_B.Product_n[i];
      Template_test_B.Product_n[i] = Template_test_B.Rpsi[i + 6] *
        Template_test_B.Subtract_o[2] + Template_test_B.Product_n[i];
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* S-Function (sdsppinv): '<S79>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&Template_test_DWork.Pseudoinverse_X[0]), (void *)
             (&Template_test_B.x5[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&Template_test_DWork.Pseudoinverse_X[0], 3, 5,
                      &Template_test_DWork.Pseudoinverse_S[0],
                      &Template_test_DWork.Inverse_DWORK3[0],
                      &Template_test_DWork.Pseudoinverse_WORK[0],
                      &Template_test_DWork.Pseudoinverse_U[0],
                      &Template_test_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&Template_test_DWork.Pseudoinverse_S[0],
          &Template_test_DWork.Pseudoinverse_U[0],
          &Template_test_DWork.Pseudoinverse_V[0],
          &Template_test_B.Pseudoinverse[0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Product: '<S79>/Product' */
    for (i = 0; i < 5; i++) {
      Template_test_B.Product_jq[i] = 0.0;
      Template_test_B.Product_jq[i] = Template_test_B.Pseudoinverse[i] *
        Template_test_B.tauSwitch[0] + Template_test_B.Product_jq[i];
      Template_test_B.Product_jq[i] = Template_test_B.Pseudoinverse[i + 5] *
        Template_test_B.tauSwitch[1] + Template_test_B.Product_jq[i];
      Template_test_B.Product_jq[i] = Template_test_B.Pseudoinverse[i + 10] *
        Template_test_B.tauSwitch[2] + Template_test_B.Product_jq[i];
    }

    /* Lookup Block: '<S81>/f_1 to u_1'
     * About '<S81>/f_1 to u_1 :'
     * Lookup Block: '<S81>/f_1 to u_1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_1tou_1),
                         Template_test_P.f_1tou_1_YData,
                         Template_test_B.Product_jq[0],
                         Template_test_P.f_1tou_1_XData, 38U);

    /* RelationalOperator: '<S86>/Compare' incorporates:
     *  Constant: '<S86>/Constant'
     */
    Template_test_B.Compare = (Template_test_B.Product_jq[1] <
      Template_test_P.Constant_Value_e);

    /* RelationalOperator: '<S88>/Compare' incorporates:
     *  Constant: '<S88>/Constant'
     */
    Template_test_B.Compare_m = (Template_test_B.Product_jq[1] >=
      Template_test_P.Constant_Value_fg);

    /* RelationalOperator: '<S87>/Compare' incorporates:
     *  Constant: '<S87>/Constant'
     */
    Template_test_B.Compare_l = (Template_test_B.Product_jq[1] <
      Template_test_P.Constant_Value_h);

    /* Logic: '<S82>/Logical Operator' */
    Template_test_B.LogicalOperator = ((Template_test_B.Compare_m != 0) &&
      (Template_test_B.Compare_l != 0));

    /* Sum: '<S82>/Sum1' */
    Template_test_B.Sum1_iu = (uint8_T)(Template_test_B.LogicalOperator +
      Template_test_B.LogicalOperator);

    /* RelationalOperator: '<S89>/Compare' incorporates:
     *  Constant: '<S89>/Constant'
     */
    Template_test_B.Compare_e = (Template_test_B.Product_jq[1] >=
      Template_test_P.Constant_Value_l5);

    /* Gain: '<S82>/Gain1' */
    Template_test_B.Gain1_k = (uint16_T)(Template_test_P.Gain1_Gain_nz *
      Template_test_B.Compare_e);

    /* Sum: '<S82>/Sum' */
    Template_test_B.Sum_e0 = (uint16_T)(uint32_T)(((Template_test_B.Compare << 6)
      + (Template_test_B.Sum1_iu << 6)) + Template_test_B.Gain1_k);

    /* Lookup Block: '<S82>/f_2 < 0.00391'
     * About '<S82>/f_2 < 0.00391 :'
     * Lookup Block: '<S82>/f_2 < 0.00391'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_2000391),
                         Template_test_P.f_2000391_YData,
                         Template_test_B.Product_jq[1],
                         Template_test_P.f_2000391_XData, 10U);

    /* Lookup Block: '<S82>/f_2 < 0.06731 && f_2 >= 0.00391'
     * About '<S82>/f_2 < 0.06731 && f_2 >= 0.00391 :'
     * Lookup Block: '<S82>/f_2 < 0.06731 && f_2 >= 0.00391'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_2006731f_2000391),
                         Template_test_P.f_2006731f_2000391_YData,
                         Template_test_B.Product_jq[1],
                         Template_test_P.f_2006731f_2000391_XData, 2U);

    /* Lookup Block: '<S82>/f_2 => 0.06731'
     * About '<S82>/f_2 => 0.06731 :'
     * Lookup Block: '<S82>/f_2 => 0.06731'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_2006731),
                         Template_test_P.f_2006731_YData,
                         Template_test_B.Product_jq[1],
                         Template_test_P.f_2006731_XData, 17U);

    /* MultiPortSwitch: '<S82>/Multiport Switch' */
    switch ((int32_T)((uint32_T)(int32_T)Template_test_B.Sum_e0 >> 6)) {
     case 1:
      Template_test_B.MultiportSwitch = Template_test_B.f_2000391;
      break;

     case 2:
      Template_test_B.MultiportSwitch = Template_test_B.f_2006731f_2000391;
      break;

     default:
      Template_test_B.MultiportSwitch = Template_test_B.f_2006731;
      break;
    }

    /* Lookup Block: '<S83>/f_3 to u_3'
     * About '<S83>/f_3 to u_3 :'
     * Lookup Block: '<S83>/f_3 to u_3'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_3tou_3),
                         Template_test_P.f_3tou_3_YData,
                         Template_test_B.Product_jq[2],
                         Template_test_P.f_3tou_3_XData, 38U);

    /* RelationalOperator: '<S90>/Compare' incorporates:
     *  Constant: '<S90>/Constant'
     */
    Template_test_B.Compare_d = (Template_test_B.Product_jq[3] <
      Template_test_P.Constant_Value_dd);

    /* RelationalOperator: '<S91>/Compare' incorporates:
     *  Constant: '<S91>/Constant'
     */
    Template_test_B.Compare_g = (Template_test_B.Product_jq[3] >=
      Template_test_P.Constant_Value_kj);

    /* Gain: '<S84>/Gain' */
    Template_test_B.Gain_j = (uint16_T)(Template_test_P.Gain_Gain_b *
      Template_test_B.Compare_g);

    /* Sum: '<S84>/Sum' */
    Template_test_B.Sum_n = (uint16_T)(uint32_T)((Template_test_B.Compare_d << 6)
      + Template_test_B.Gain_j);

    /* Lookup Block: '<S84>/f_4 < 0.0451'
     * About '<S84>/f_4 < 0.0451 :'
     * Lookup Block: '<S84>/f_4 < 0.0451'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_400451),
                         Template_test_P.f_400451_YData,
                         Template_test_B.Product_jq[3],
                         Template_test_P.f_400451_XData, 14U);

    /* Lookup Block: '<S84>/f_4 >= 0.0451 '
     * About '<S84>/f_4 >= 0.0451  :'
     * Lookup Block: '<S84>/f_4 >= 0.0451 '
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_400451_p),
                         Template_test_P.f_400451_YData_b,
                         Template_test_B.Product_jq[3],
                         Template_test_P.f_400451_XData_h, 12U);

    /* MultiPortSwitch: '<S84>/Multiport Switch' */
    if ((int32_T)((uint32_T)(int32_T)Template_test_B.Sum_n >> 6) == 1) {
      Template_test_B.MultiportSwitch_m = Template_test_B.f_400451;
    } else {
      Template_test_B.MultiportSwitch_m = Template_test_B.f_400451_p;
    }

    /* DeadZone Block: '<S85>/Dead Zone +-0.01'
     */
    if (Template_test_B.Product_jq[4] >= Template_test_P.DeadZone001_End) {
      Template_test_B.DeadZone001 = Template_test_B.Product_jq[4] -
        Template_test_P.DeadZone001_End;
    } else if (Template_test_B.Product_jq[4] > Template_test_P.DeadZone001_Start)
    {
      Template_test_B.DeadZone001 = 0.0;
    } else {
      Template_test_B.DeadZone001 = Template_test_B.Product_jq[4] -
        Template_test_P.DeadZone001_Start;
    }

    /* RelationalOperator: '<S92>/Compare' incorporates:
     *  Constant: '<S92>/Constant'
     */
    Template_test_B.Compare_a = (Template_test_B.DeadZone001 <
      Template_test_P.Constant_Value_dz);

    /* RelationalOperator: '<S94>/Compare' */
    Template_test_B.Compare_b = (Template_test_B.DeadZone001 == 0.0);

    /* Gain: '<S85>/Gain' */
    Template_test_B.Gain_jt = (uint16_T)(Template_test_P.Gain_Gain_ea *
      Template_test_B.Compare_b);

    /* RelationalOperator: '<S93>/Compare' incorporates:
     *  Constant: '<S93>/Constant'
     */
    Template_test_B.Compare_aa = (Template_test_B.DeadZone001 >
      Template_test_P.Constant_Value_i4);

    /* Gain: '<S85>/Gain1' */
    Template_test_B.Gain1_m = (uint16_T)(Template_test_P.Gain1_Gain_f *
      Template_test_B.Compare_aa);

    /* Sum: '<S85>/Sum' */
    Template_test_B.Sum_g = (uint16_T)(uint32_T)(((Template_test_B.Compare_a <<
      6) + Template_test_B.Gain_jt) + Template_test_B.Gain1_m);

    /* Lookup Block: '<S85>/f_5 < 0'
     * About '<S85>/f_5 < 0 :'
     * Lookup Block: '<S85>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_50), Template_test_P.f_50_YData,
                         Template_test_B.Product_jq[4],
                         Template_test_P.f_50_XData, 9U);

    /* Lookup Block: '<S85>/f_5 > 0'
     * About '<S85>/f_5 > 0 :'
     * Lookup Block: '<S85>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(Template_test_B.f_50_g),
                         Template_test_P.f_50_YData_m,
                         Template_test_B.Product_jq[4],
                         Template_test_P.f_50_XData_h, 9U);

    /* MultiPortSwitch: '<S85>/Multiport Switch' incorporates:
     *  Constant: '<S85>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)Template_test_B.Sum_g >> 6)) {
     case 1:
      Template_test_B.MultiportSwitch_c = Template_test_B.f_50;
      break;

     case 2:
      Template_test_B.MultiportSwitch_c = Template_test_P.f_50_Value;
      break;

     default:
      Template_test_B.MultiportSwitch_c = Template_test_B.f_50_g;
      break;
    }

    /* Saturate: '<S33>/Saturation' incorporates:
     *  Constant: '<S78>/BT_power_limit'
     *  Constant: '<S78>/VSP_speeds'
     */
    tmp_0[0] = Template_test_B.f_1tou_1;
    tmp_0[1] = Template_test_B.MultiportSwitch;
    tmp_0[2] = Template_test_B.f_3tou_3;
    tmp_0[3] = Template_test_B.MultiportSwitch_m;
    tmp_0[4] = Template_test_B.MultiportSwitch_c;
    tmp_0[5] = Template_test_P.BT_power_limit_Value;
    tmp_0[6] = Template_test_P.VSP_speeds_Value;
    for (i = 0; i < 7; i++) {
      Template_test_B.Saturation_he[i] = rt_SATURATE(tmp_0[i],
        Template_test_P.Saturation_LowerSat_h,
        Template_test_P.Saturation_UpperSat_e);
    }

    /* Gain: '<S169>/QTM In2 Error' */
    Template_test_B.QTMIn2Error = Template_test_P.QTMIn2Error_Gain *
      Template_test_B.QTMIn[1];

    /* Gain: '<S169>/QTM In9 Residual' */
    Template_test_B.QTMIn9Residual = Template_test_P.QTMIn9Residual_Gain *
      Template_test_B.QTMIn[8];

    /* Derivative Block: '<S169>/Derivative1' */
    {
      real_T t = Template_test_M->Timing.t[0];
      real_T timeStampA = Template_test_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = Template_test_DWork.Derivative1_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        Template_test_B.Derivative1[0] = 0.0;
        Template_test_B.Derivative1[1] = 0.0;
        Template_test_B.Derivative1[2] = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &Template_test_DWork.Derivative1_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 4;
          }
        } else if (timeStampA >= t) {
          lastBank += 4;
        }

        deltaT = t - *lastBank++;
        Template_test_B.Derivative1[0] = (Template_test_B.mm2mx - *lastBank++) /
          deltaT;
        Template_test_B.Derivative1[1] = (Template_test_B.mm2my - *lastBank++) /
          deltaT;
        Template_test_B.Derivative1[2] = (Template_test_B.d2ryaw - *lastBank++) /
          deltaT;
      }
    }

    /* MultiPortSwitch: '<S170>/etadot Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)Template_test_P.ControlInputSelector_Value == 0) {
      Template_test_B.etadotSwitch[0] = Template_test_B.Derivative1[0];
      Template_test_B.etadotSwitch[1] = Template_test_B.Derivative1[1];
      Template_test_B.etadotSwitch[2] = Template_test_B.Derivative1[2];
    } else {
      Template_test_B.etadotSwitch[0] = Template_test_B.Product3_n[0];
      Template_test_B.etadotSwitch[1] = Template_test_B.Product3_n[1];
      Template_test_B.etadotSwitch[2] = Template_test_B.Product3_n[2];
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Saturate: '<S174>/Saturation' incorporates:
       *  Constant: '<S1>/Control Mode Selector'
       */
      tmp = Template_test_P.ControlModeSelector_Value;
      Template_test_B.Saturation_d = rt_SATURATE(tmp,
        Template_test_P.Saturation_LowerSat_c,
        Template_test_P.Saturation_UpperSat_g);
    }

    /* MultiPortSwitch: '<S174>/tau Switch' incorporates:
     *  Constant: '<S8>/PS3_BT_Power  [-]'
     *  Constant: '<S8>/PS3_VSP_Speed  [-]'
     */
    if ((int32_T)Template_test_B.Saturation_d == 0) {
      Template_test_B.tauSwitch_k[0] = Template_test_B.u_1;
      Template_test_B.tauSwitch_k[1] = Template_test_B.u_2;
      Template_test_B.tauSwitch_k[2] = Template_test_B.u_3;
      Template_test_B.tauSwitch_k[3] = Template_test_B.u_4;
      Template_test_B.tauSwitch_k[4] = Template_test_B.u_5;
      Template_test_B.tauSwitch_k[5] = Template_test_P.PS3_BT_Power_Value;
      Template_test_B.tauSwitch_k[6] = Template_test_P.PS3_VSP_Speed_Value;
    } else {
      for (i = 0; i < 7; i++) {
        Template_test_B.tauSwitch_k[i] = Template_test_B.Saturation_he[i];
      }
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* SignalConversion: '<S22>/TmpHiddenBufferAtTo FileInport1' incorporates:
       *  Constant: '<S12>/ y_d [m]'
       *  Constant: '<S12>/x_d [m]'
       *  Constant: '<S1>/Control Input Selector'
       *  Constant: '<S1>/Control Mode Selector'
       *  Constant: '<S7>/Path Selector  [-]'
       *  Constant: '<S7>/u_d [m]'
       */
      Template_test_B.TmpHiddenBufferAtToFileInport1[0] =
        Template_test_P.ControlInputSelector_Value;
      Template_test_B.TmpHiddenBufferAtToFileInport1[1] =
        Template_test_B.QTMIn2Error;
      Template_test_B.TmpHiddenBufferAtToFileInport1[2] =
        Template_test_B.QTMIn9Residual;
      Template_test_B.TmpHiddenBufferAtToFileInport1[3] =
        Template_test_B.etadotSwitch[0];
      Template_test_B.TmpHiddenBufferAtToFileInport1[4] =
        Template_test_B.etadotSwitch[1];
      Template_test_B.TmpHiddenBufferAtToFileInport1[5] =
        Template_test_B.etadotSwitch[2];
      Template_test_B.TmpHiddenBufferAtToFileInport1[6] =
        Template_test_B.etaSwitch[0];
      Template_test_B.TmpHiddenBufferAtToFileInport1[7] =
        Template_test_B.etaSwitch[1];
      Template_test_B.TmpHiddenBufferAtToFileInport1[8] =
        Template_test_B.etaSwitch[2];
      Template_test_B.TmpHiddenBufferAtToFileInport1[9] =
        Template_test_B.nuSwitch[0];
      Template_test_B.TmpHiddenBufferAtToFileInport1[10] =
        Template_test_B.nuSwitch[1];
      Template_test_B.TmpHiddenBufferAtToFileInport1[11] =
        Template_test_B.nuSwitch[2];
      Template_test_B.TmpHiddenBufferAtToFileInport1[12] =
        Template_test_P.x_dm_Value;
      Template_test_B.TmpHiddenBufferAtToFileInport1[13] =
        Template_test_P.y_dm_Value;
      Template_test_B.TmpHiddenBufferAtToFileInport1[14] = Template_test_B.Gain1;
      Template_test_B.TmpHiddenBufferAtToFileInport1[15] =
        Template_test_B.VectorConcatenate[0];
      Template_test_B.TmpHiddenBufferAtToFileInport1[16] =
        Template_test_B.VectorConcatenate[1];
      Template_test_B.TmpHiddenBufferAtToFileInport1[17] =
        Template_test_B.VectorConcatenate[2];
      Template_test_B.TmpHiddenBufferAtToFileInport1[18] =
        Template_test_P.PathSelector_Value;
      Template_test_B.TmpHiddenBufferAtToFileInport1[19] =
        Template_test_B.Switch2;
      Template_test_B.TmpHiddenBufferAtToFileInport1[20] =
        Template_test_B.Switch2_c;
      Template_test_B.TmpHiddenBufferAtToFileInport1[21] =
        Template_test_B.Sum_dn;
      Template_test_B.TmpHiddenBufferAtToFileInport1[22] =
        Template_test_P.u_dm_Value;
      Template_test_B.TmpHiddenBufferAtToFileInport1[23] =
        Template_test_B.Divide_o;
      Template_test_B.TmpHiddenBufferAtToFileInport1[24] =
        Template_test_B.Integrator1;
      Template_test_B.TmpHiddenBufferAtToFileInport1[25] =
        Template_test_P.ControlModeSelector_Value;
      for (i = 0; i < 7; i++) {
        Template_test_B.TmpHiddenBufferAtToFileInport1[i + 26] =
          Template_test_B.tauSwitch_k[i];
      }

      Template_test_B.TmpHiddenBufferAtToFileInport1[33] =
        Template_test_B.tauSwitch[0];
      Template_test_B.TmpHiddenBufferAtToFileInport1[34] =
        Template_test_B.tauSwitch[1];
      Template_test_B.TmpHiddenBufferAtToFileInport1[35] =
        Template_test_B.tauSwitch[2];
      Template_test_B.TmpHiddenBufferAtToFileInport1[36] =
        Template_test_B.Integrator2[0];
      Template_test_B.TmpHiddenBufferAtToFileInport1[37] =
        Template_test_B.Integrator2[1];

      /* ToFile Block: '<S22>/To File'
       */
      if (rtmIsMajorTimeStep(Template_test_M)) {
        if (!(++Template_test_DWork.ToFile_IWORK.Decimation % 1) &&
            (Template_test_DWork.ToFile_IWORK.Count*39)+1 < 100000000 ) {
          real_T u[39];
          FILE *fp = (FILE *) Template_test_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            Template_test_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = Template_test_M->Timing.t[1];
            u[1] = Template_test_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = Template_test_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = Template_test_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = Template_test_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = Template_test_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = Template_test_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = Template_test_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = Template_test_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = Template_test_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = Template_test_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = Template_test_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = Template_test_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = Template_test_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = Template_test_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = Template_test_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = Template_test_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = Template_test_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = Template_test_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = Template_test_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = Template_test_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = Template_test_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = Template_test_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = Template_test_B.TmpHiddenBufferAtToFileInport1[22];
            u[24] = Template_test_B.TmpHiddenBufferAtToFileInport1[23];
            u[25] = Template_test_B.TmpHiddenBufferAtToFileInport1[24];
            u[26] = Template_test_B.TmpHiddenBufferAtToFileInport1[25];
            u[27] = Template_test_B.TmpHiddenBufferAtToFileInport1[26];
            u[28] = Template_test_B.TmpHiddenBufferAtToFileInport1[27];
            u[29] = Template_test_B.TmpHiddenBufferAtToFileInport1[28];
            u[30] = Template_test_B.TmpHiddenBufferAtToFileInport1[29];
            u[31] = Template_test_B.TmpHiddenBufferAtToFileInport1[30];
            u[32] = Template_test_B.TmpHiddenBufferAtToFileInport1[31];
            u[33] = Template_test_B.TmpHiddenBufferAtToFileInport1[32];
            u[34] = Template_test_B.TmpHiddenBufferAtToFileInport1[33];
            u[35] = Template_test_B.TmpHiddenBufferAtToFileInport1[34];
            u[36] = Template_test_B.TmpHiddenBufferAtToFileInport1[35];
            u[37] = Template_test_B.TmpHiddenBufferAtToFileInport1[36];
            u[38] = Template_test_B.TmpHiddenBufferAtToFileInport1[37];
            if (fwrite(u, sizeof(real_T), 39, fp) != 39) {
              rtmSetErrorStatus(Template_test_M,
                                "Error writing to MAT-file Template_data.mat");
              return;
            }

            if (((++Template_test_DWork.ToFile_IWORK.Count)*39)+1 >= 100000000)
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
    }

    /* Math: '<S152>/Math Function' */
    Template_test_B.MathFunction_gc[0] =
      Template_test_B.TmpHiddenBufferAtProductInpor_l[0];
    Template_test_B.MathFunction_gc[1] =
      Template_test_B.TmpHiddenBufferAtProductInpor_l[1];

    /* Product: '<S151>/Product' */
    tmp = Template_test_B.MathFunction_gc[0] *
      Template_test_B.TmpHiddenBufferAtProductInpor_l[0];
    tmp += Template_test_B.MathFunction_gc[1] *
      Template_test_B.TmpHiddenBufferAtProductInpor_l[1];
    Template_test_B.Product_dc = tmp;

    /* Math: '<S151>/sqrt' */
    tmp = Template_test_B.Product_dc;
    if (tmp < 0.0) {
      Template_test_B.sqrt_h = -sqrt(-tmp);
    } else {
      Template_test_B.sqrt_h = sqrt(tmp);
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Math: '<S164>/Math Function' */
      Template_test_B.MathFunction_jd[0] =
        Template_test_B.TmpHiddenBufferAtProductInpo_dn[0];
      Template_test_B.MathFunction_jd[1] =
        Template_test_B.TmpHiddenBufferAtProductInpo_dn[1];

      /* Product: '<S163>/Product' */
      tmp = Template_test_B.MathFunction_jd[0] *
        Template_test_B.TmpHiddenBufferAtProductInpo_dn[0];
      tmp += Template_test_B.MathFunction_jd[1] *
        Template_test_B.TmpHiddenBufferAtProductInpo_dn[1];
      Template_test_B.Product_ha = tmp;

      /* Math: '<S163>/sqrt' */
      tmp = Template_test_B.Product_ha;
      if (tmp < 0.0) {
        Template_test_B.sqrt_hn = -sqrt(-tmp);
      } else {
        Template_test_B.sqrt_hn = sqrt(tmp);
      }
    }

    /* Gain: '<S169>/QTM In1 FPS' */
    Template_test_B.QTMIn1FPS = Template_test_P.QTMIn1FPS_Gain *
      Template_test_B.QTMIn[0];
    if (rtmIsMajorTimeStep(Template_test_M)) {
    }

    /* Outputs for enable SubSystem: '<S25>/CSE1 actuator' incorporates:
     *  Constant: '<S1>/Enable CSE1'
     *  EnablePort: '<S172>/Enable'
     */
    if (rtmIsMajorTimeStep(Template_test_M) && rtmIsMajorTimeStep
        (Template_test_M)) {
      if (Template_test_P.EnableCSE1_Value > 0.0) {
        if (Template_test_DWork.CSE1actuator_MODE == SUBSYS_DISABLED) {
          Template_test_DWork.CSE1actuator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (Template_test_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
          Template_test_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (Template_test_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S176>/BT_D_Gain1' */
      Template_test_B.BT_D_Gain1 = Template_test_P.BT_D_Gain1_Gain *
        Template_test_B.tauSwitch_k[4];

      /* Gain: '<S176>/BT_D_Gain2' */
      Template_test_B.BT_D_Gain2 = Template_test_P.BT_D_Gain2_Gain *
        Template_test_B.tauSwitch_k[4];

      /* Sum: '<S176>/Add' incorporates:
       *  Constant: '<S176>/BT_Power_Offset1'
       */
      Template_test_B.Add_h = (Template_test_B.BT_D_Gain1 +
        Template_test_P.BT_Power_Offset1_Value) + Template_test_B.BT_D_Gain2;

      /* Gain: '<S176>/BT_L_Gain1' */
      Template_test_B.BT_L_Gain1 = Template_test_P.BT_L_Gain1_Gain *
        Template_test_B.tauSwitch_k[5];

      /* Gain: '<S176>/BT_L_Gain2' */
      Template_test_B.BT_L_Gain2 = Template_test_P.BT_L_Gain2_Gain *
        Template_test_B.tauSwitch_k[5];

      /* Gain: '<S176>/Neg' */
      Template_test_B.Neg = Template_test_P.Neg_Gain *
        Template_test_B.tauSwitch_k[5];
      if (rtmIsMajorTimeStep(Template_test_M)) {
      }

      /* Sum: '<S176>/Sum1' incorporates:
       *  Constant: '<S176>/BT_Power_Offset2'
       */
      Template_test_B.Sum1_ac = Template_test_B.BT_L_Gain1 +
        Template_test_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S178>/LowerRelop1' */
      Template_test_B.LowerRelop1_c = (Template_test_B.Add_h >
        Template_test_B.Sum1_ac);

      /* Sum: '<S176>/Sum2' incorporates:
       *  Constant: '<S176>/BT_Power_Offset3'
       */
      Template_test_B.Sum2_m = Template_test_B.BT_L_Gain2 +
        Template_test_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S178>/UpperRelop' */
      Template_test_B.UpperRelop_k = (Template_test_B.Add_h <
        Template_test_B.Sum2_m);

      /* Switch: '<S178>/Switch' */
      if (Template_test_B.UpperRelop_k) {
        Template_test_B.Switch_h = Template_test_B.Sum2_m;
      } else {
        Template_test_B.Switch_h = Template_test_B.Add_h;
      }

      /* Switch: '<S178>/Switch2' */
      if (Template_test_B.LowerRelop1_c) {
        Template_test_B.Switch2_e = Template_test_B.Sum1_ac;
      } else {
        Template_test_B.Switch2_e = Template_test_B.Switch_h;
      }

      if (rtmIsMajorTimeStep(Template_test_M)) {
      }

      /* RelationalOperator: '<S179>/LowerRelop1' incorporates:
       *  Constant: '<S176>/Constant'
       */
      Template_test_B.LowerRelop1_o = (Template_test_B.tauSwitch_k[4] >
        Template_test_P.Constant_Value_ahu);

      /* RelationalOperator: '<S179>/UpperRelop' */
      Template_test_B.UpperRelop_g = (Template_test_B.tauSwitch_k[4] <
        Template_test_B.Neg);

      /* Switch: '<S179>/Switch' */
      if (Template_test_B.UpperRelop_g) {
        Template_test_B.Switch_p = Template_test_B.Neg;
      } else {
        Template_test_B.Switch_p = Template_test_B.tauSwitch_k[4];
      }

      /* Switch: '<S179>/Switch2' incorporates:
       *  Constant: '<S176>/Constant'
       */
      if (Template_test_B.LowerRelop1_o) {
        Template_test_B.Switch2_j = Template_test_P.Constant_Value_ahu;
      } else {
        Template_test_B.Switch2_j = Template_test_B.Switch_p;
      }

      if (rtmIsMajorTimeStep(Template_test_M)) {
      }

      /* RelationalOperator: '<S180>/LowerRelop1' */
      Template_test_B.LowerRelop1_on = (Template_test_B.tauSwitch_k[4] >
        Template_test_B.tauSwitch_k[5]);

      /* RelationalOperator: '<S180>/UpperRelop' incorporates:
       *  Constant: '<S176>/Constant1'
       */
      Template_test_B.UpperRelop_d5 = (Template_test_B.tauSwitch_k[4] <
        Template_test_P.Constant1_Value_j);

      /* Switch: '<S180>/Switch' incorporates:
       *  Constant: '<S176>/Constant1'
       */
      if (Template_test_B.UpperRelop_d5) {
        Template_test_B.Switch_m = Template_test_P.Constant1_Value_j;
      } else {
        Template_test_B.Switch_m = Template_test_B.tauSwitch_k[4];
      }

      /* Switch: '<S180>/Switch2' */
      if (Template_test_B.LowerRelop1_on) {
        Template_test_B.Switch2_f = Template_test_B.tauSwitch_k[5];
      } else {
        Template_test_B.Switch2_f = Template_test_B.Switch_m;
      }

      /* Signum: '<S177>/Sign' */
      Template_test_B.Sign_e = rt_SIGNd_snf(Template_test_B.tauSwitch_k[6]);

      /* Product: '<S177>/Product1' */
      Template_test_B.PortVPS_X = Template_test_B.tauSwitch_k[1] *
        Template_test_B.Sign_e;

      /* Gain: '<S177>/-x' */
      Template_test_B.PortVPS_X_d = Template_test_P.x_Gain *
        Template_test_B.PortVPS_X;

      /* Product: '<S177>/Product2' */
      Template_test_B.PortVSP_Y = Template_test_B.tauSwitch_k[0] *
        Template_test_B.Sign_e;

      /* Gain: '<S177>/-y' */
      Template_test_B.PortVSP_Y_g = Template_test_P.y_Gain *
        Template_test_B.PortVSP_Y;

      /* Product: '<S177>/Product3' */
      Template_test_B.StarboardVSP_X = Template_test_B.tauSwitch_k[3] *
        Template_test_B.Sign_e;

      /* Product: '<S177>/Product4' */
      Template_test_B.StarboardVSP_Y = Template_test_B.tauSwitch_k[2] *
        Template_test_B.Sign_e;

      /* Lookup2D: '<S177>/Servo1' */
      Template_test_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&Template_test_P.Servo1_RowIdx[0]), 3, (const real_T *)
        (&Template_test_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&Template_test_P.Servo1_Table[0]), (const real_T)
        Template_test_B.PortVPS_X_d, (const real_T)Template_test_B.PortVSP_Y_g);

      /* Lookup2D: '<S177>/Servo2' */
      Template_test_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&Template_test_P.Servo2_RowIdx[0]), 3, (const real_T *)
        (&Template_test_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&Template_test_P.Servo2_Table[0]), (const real_T)
        Template_test_B.PortVPS_X_d, (const real_T)Template_test_B.PortVSP_Y_g);

      /* Lookup2D: '<S177>/Servo3' */
      Template_test_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&Template_test_P.Servo3_RowIdx[0]), 3, (const real_T *)
        (&Template_test_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&Template_test_P.Servo3_Table[0]), (const real_T)
        Template_test_B.StarboardVSP_X, (const real_T)
        Template_test_B.StarboardVSP_Y);

      /* Lookup2D: '<S177>/Servo4' */
      Template_test_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&Template_test_P.Servo4_RowIdx[0]), 3, (const real_T *)
        (&Template_test_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&Template_test_P.Servo4_Table[0]), (const real_T)
        Template_test_B.StarboardVSP_X, (const real_T)
        Template_test_B.StarboardVSP_Y);

      /* Gain: '<S177>/VPS_Speed_Gain' */
      Template_test_B.VPS_Speed_Gain = Template_test_P.VPS_Speed_Gain_Gain *
        Template_test_B.tauSwitch_k[6];

      /* Sum: '<S177>/Sum' incorporates:
       *  Constant: '<S177>/VPS_Power_Offset'
       */
      Template_test_B.Sum_dnw = Template_test_B.VPS_Speed_Gain +
        Template_test_P.VPS_Power_Offset_Value;

      /* Gain: '<S177>/VSPS Port' */
      Template_test_B.VSPSPort = Template_test_P.VSPSPort_Gain *
        Template_test_B.Sum_dnw;

      /* Gain: '<S177>/VSPS Starboard' */
      Template_test_B.VSPSStarboard = Template_test_P.VSPSStarboard_Gain *
        Template_test_B.Sum_dnw;
    }

    /* end of Outputs for SubSystem: '<S25>/CSE1 actuator' */
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Product Block: '<S25>/Inverse' */
      {
        static const int_T dims[3] = { 3, 3, 3 };

        rt_MatDivRR_Dbl(Template_test_B.Inverse, Template_test_B.x3,
                        &Template_test_DWork.Inverse_DWORK4[0], (real_T*)
                        &Template_test_DWork.Pseudoinverse_X[0],
                        &Template_test_DWork.Inverse_DWORK2[0], (real_T*)
                        &Template_test_DWork.Inverse_DWORK3[0],
                        &dims[0]);
      }
    }

    /* Saturate: '<S175>/Saturation' */
    tmp = Template_test_B.tauSwitch[0];
    Template_test_B.Saturation_kh = rt_SATURATE(tmp,
      Template_test_P.Saturation_LowerSat_n,
      Template_test_P.Saturation_UpperSat_i);

    /* Saturate: '<S175>/Saturation1' */
    tmp = Template_test_B.tauSwitch[1];
    Template_test_B.Saturation1 = rt_SATURATE(tmp,
      Template_test_P.Saturation1_LowerSat, Template_test_P.Saturation1_UpperSat);

    /* Saturate: '<S175>/Saturation2' */
    tmp = Template_test_B.tauSwitch[2];
    Template_test_B.Saturation2 = rt_SATURATE(tmp,
      Template_test_P.Saturation2_LowerSat, Template_test_P.Saturation2_UpperSat);

    /* Gain: '<S175>/plant tau_surge' */
    Template_test_B.planttau_surge = Template_test_P.planttau_surge_Gain *
      Template_test_B.Saturation_kh;

    /* Gain: '<S175>/plant tau_sway' */
    Template_test_B.planttau_sway = Template_test_P.planttau_sway_Gain *
      Template_test_B.Saturation1;

    /* Gain: '<S175>/plant tau_yaw' */
    Template_test_B.planttau_yaw = Template_test_P.planttau_yaw_Gain *
      Template_test_B.Saturation2;
    if (rtmIsMajorTimeStep(Template_test_M)) {
      /* Gain: '<S183>/Battery Bow Thruster' */
      Template_test_B.BatteryBowThruster =
        Template_test_P.BatteryBowThruster_Gain * Template_test_B.SITzAI0;

      /* Gain: '<S183>/Battery Main' */
      Template_test_B.BatteryMain = Template_test_P.BatteryMain_Gain *
        Template_test_B.SITzAI2;

      /* Gain: '<S183>/Battery Servo' */
      Template_test_B.BatteryServo = Template_test_P.BatteryServo_Gain *
        Template_test_B.SITzAI1;
    }

    /* Gain: '<S184>/CSE1_Yaw [deg]' */
    Template_test_B.CSE1_Yawdeg = Template_test_P.CSE1_Yawdeg_Gain *
      Template_test_B.etaSwitch[2];

    /* Gain: '<S184>/CSE1_x [m]' */
    Template_test_B.CSE1_xm = Template_test_P.CSE1_xm_Gain *
      Template_test_B.etaSwitch[0];

    /* Gain: '<S184>/CSE1_y [m]' */
    Template_test_B.CSE1_ym = Template_test_P.CSE1_ym_Gain *
      Template_test_B.etaSwitch[1];

    /* Gain: '<S184>/CSE1_r [deg//s]' */
    Template_test_B.CSE1_rdegs = Template_test_P.CSE1_rdegs_Gain *
      Template_test_B.nuSwitch[2];

    /* Gain: '<S184>/CSE1_u [m//s]' */
    Template_test_B.CSE1_ums = Template_test_P.CSE1_ums_Gain *
      Template_test_B.nuSwitch[0];

    /* Gain: '<S184>/CSE1_v [m//s]' */
    Template_test_B.CSE1_vms = Template_test_P.CSE1_vms_Gain *
      Template_test_B.nuSwitch[1];

    /* Gain: '<S184>/QS_Yaw [deg]' */
    Template_test_B.QS_Yawdeg = Template_test_P.QS_Yawdeg_Gain *
      Template_test_B.d2ryaw;

    /* Gain: '<S184>/QS_x [m]' */
    Template_test_B.QS_xm = Template_test_P.QS_xm_Gain * Template_test_B.mm2mx;

    /* Gain: '<S184>/QS_y [m]' */
    Template_test_B.QS_ym = Template_test_P.QS_ym_Gain * Template_test_B.mm2my;

    /* Gain: '<S184>/LS_Yaw [deg]' */
    Template_test_B.LS_Yawdeg = Template_test_P.LS_Yawdeg_Gain *
      Template_test_B.Integrator1_o[2];

    /* Gain: '<S184>/LS_x [m]' */
    Template_test_B.LS_xm = Template_test_P.LS_xm_Gain *
      Template_test_B.Integrator1_o[0];

    /* Gain: '<S184>/LS_y [m]' */
    Template_test_B.LS_ym = Template_test_P.LS_ym_Gain *
      Template_test_B.Integrator1_o[1];

    /* Gain: '<S185>/plant BT power' */
    Template_test_B.plantBTpower = Template_test_P.plantBTpower_Gain *
      Template_test_B.tauSwitch_k[5];

    /* Gain: '<S185>/plant VSP speed' */
    Template_test_B.plantVSPspeed = Template_test_P.plantVSPspeed_Gain *
      Template_test_B.tauSwitch_k[6];

    /* Gain: '<S185>/plant u_1' */
    Template_test_B.plantu_1 = Template_test_P.plantu_1_Gain *
      Template_test_B.tauSwitch_k[0];

    /* Gain: '<S185>/plant u_2' */
    Template_test_B.plantu_2 = Template_test_P.plantu_2_Gain *
      Template_test_B.tauSwitch_k[1];

    /* Gain: '<S185>/plant u_3' */
    Template_test_B.plantu_3 = Template_test_P.plantu_3_Gain *
      Template_test_B.tauSwitch_k[2];

    /* Gain: '<S185>/plant u_4' */
    Template_test_B.plantu_4 = Template_test_P.plantu_4_Gain *
      Template_test_B.tauSwitch_k[3];

    /* Gain: '<S185>/plant u_5' */
    Template_test_B.plantu_5 = Template_test_P.plantu_5_Gain *
      Template_test_B.tauSwitch_k[4];

    /* Gain: '<S186>/eta_psi [rad]' */
    Template_test_B.eta_psirad = Template_test_P.eta_psirad_Gain *
      Template_test_B.etaSwitch[2];

    /* Gain: '<S186>/eta_psid [rad]' */
    Template_test_B.eta_psidrad = Template_test_P.eta_psidrad_Gain *
      Template_test_B.Sum_dn;

    /* Gain: '<S186>/eta_x [m]' */
    Template_test_B.eta_xm = Template_test_P.eta_xm_Gain *
      Template_test_B.etaSwitch[0];

    /* Gain: '<S186>/eta_xd [m]' */
    Template_test_B.eta_xdm = Template_test_P.eta_xdm_Gain *
      Template_test_B.Switch2;

    /* Gain: '<S186>/eta_y [m]' */
    Template_test_B.eta_ym = Template_test_P.eta_ym_Gain *
      Template_test_B.etaSwitch[1];

    /* Gain: '<S186>/eta_yd [m]' */
    Template_test_B.eta_ydm = Template_test_P.eta_ydm_Gain *
      Template_test_B.Switch2_c;

    /* Gain: '<S186>/psi_los [rad]' */
    Template_test_B.psi_losrad = Template_test_P.psi_losrad_Gain *
      Template_test_B.VectorConcatenate[2];

    /* Gain: '<S186>/psi_plot' */
    Template_test_B.psi_plot[0] = Template_test_P.psi_plot_Gain *
      Template_test_B.eta_psirad;
    Template_test_B.psi_plot[1] = Template_test_P.psi_plot_Gain *
      Template_test_B.psi_losrad;
    Template_test_B.psi_plot[2] = Template_test_P.psi_plot_Gain *
      Template_test_B.eta_psidrad;

    /* Gain: '<S186>/q_x [m]' */
    Template_test_B.q_xm = Template_test_P.q_xm_Gain *
      Template_test_B.VectorConcatenate[0];

    /* Gain: '<S186>/q_y [m]' */
    Template_test_B.q_ym = Template_test_P.q_ym_Gain *
      Template_test_B.VectorConcatenate[1];

    /* Gain: '<S186>/x_plot' */
    Template_test_B.x_plot[0] = Template_test_P.x_plot_Gain *
      Template_test_B.eta_xm;
    Template_test_B.x_plot[1] = Template_test_P.x_plot_Gain *
      Template_test_B.q_xm;
    Template_test_B.x_plot[2] = Template_test_P.x_plot_Gain *
      Template_test_B.eta_xdm;

    /* Gain: '<S186>/y_plot' */
    Template_test_B.y_plot[0] = Template_test_P.y_plot_Gain *
      Template_test_B.eta_ym;
    Template_test_B.y_plot[1] = Template_test_P.y_plot_Gain *
      Template_test_B.q_ym;
    Template_test_B.y_plot[2] = Template_test_P.y_plot_Gain *
      Template_test_B.eta_ydm;
    if (rtmIsMajorTimeStep(Template_test_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void Template_test_update(int_T tid)
{
  {
    int32_T tmp;

    /* Update for enable SubSystem: '<S25>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S173>/Enable'
     */
    if (Template_test_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S181>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        Template_test_B.Product1_gl[tmp] = 0.0;
        Template_test_B.Product1_gl[tmp] =
          Template_test_B.LinearDampningmatrix[tmp] *
          Template_test_B.Integrator_j[0] + Template_test_B.Product1_gl[tmp];
        Template_test_B.Product1_gl[tmp] =
          Template_test_B.LinearDampningmatrix[tmp + 3] *
          Template_test_B.Integrator_j[1] + Template_test_B.Product1_gl[tmp];
        Template_test_B.Product1_gl[tmp] =
          Template_test_B.LinearDampningmatrix[tmp + 6] *
          Template_test_B.Integrator_j[2] + Template_test_B.Product1_gl[tmp];
      }

      /* Sum: '<S181>/Sum' */
      Template_test_B.Sum_ib[0] = Template_test_B.planttau_surge -
        Template_test_B.Product1_gl[0];
      Template_test_B.Sum_ib[1] = Template_test_B.planttau_sway -
        Template_test_B.Product1_gl[1];
      Template_test_B.Sum_ib[2] = Template_test_B.planttau_yaw -
        Template_test_B.Product1_gl[2];

      /* Product: '<S181>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        Template_test_B.Product2_i1[tmp] = 0.0;
        Template_test_B.Product2_i1[tmp] = Template_test_B.Inverse[tmp] *
          Template_test_B.Sum_ib[0] + Template_test_B.Product2_i1[tmp];
        Template_test_B.Product2_i1[tmp] = Template_test_B.Inverse[tmp + 3] *
          Template_test_B.Sum_ib[1] + Template_test_B.Product2_i1[tmp];
        Template_test_B.Product2_i1[tmp] = Template_test_B.Inverse[tmp + 6] *
          Template_test_B.Sum_ib[2] + Template_test_B.Product2_i1[tmp];
      }
    }

    /* end of Update for SubSystem: '<S25>/Linear Simulator' */

    /* Derivative Block: '<S169>/Derivative' */
    {
      real_T timeStampA = Template_test_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = Template_test_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank = &Template_test_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = Template_test_M->Timing.t[0];
      *lastBank++ = Template_test_B.mm2mx;
      *lastBank++ = Template_test_B.mm2my;
      *lastBank++ = Template_test_B.mm2mz;
      *lastBank++ = Template_test_B.d2rroll;
      *lastBank++ = Template_test_B.d2rpitch;
      *lastBank++ = Template_test_B.d2ryaw;
    }

    /* Derivative Block: '<S99>/Derivative' */
    {
      real_T timeStampA = Template_test_DWork.Derivative_RWORK_o.TimeStampA;
      real_T timeStampB = Template_test_DWork.Derivative_RWORK_o.TimeStampB;
      real_T *lastBank = &Template_test_DWork.Derivative_RWORK_o.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 2;
        } else if (timeStampA >= timeStampB) {
          lastBank += 2;
        }
      }

      *lastBank++ = Template_test_M->Timing.t[0];
      *lastBank++ = Template_test_P.u_dm_Value;
    }

    /* Derivative Block: '<S169>/Derivative1' */
    {
      real_T timeStampA = Template_test_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = Template_test_DWork.Derivative1_RWORK.TimeStampB;
      real_T *lastBank = &Template_test_DWork.Derivative1_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 4;
        } else if (timeStampA >= timeStampB) {
          lastBank += 4;
        }
      }

      *lastBank++ = Template_test_M->Timing.t[0];
      *lastBank++ = Template_test_B.mm2mx;
      *lastBank++ = Template_test_B.mm2my;
      *lastBank++ = Template_test_B.d2ryaw;
    }

    if (rtmIsMajorTimeStep(Template_test_M)) {
    }
  }

  if (rtmIsMajorTimeStep(Template_test_M)) {
    rt_ertODEUpdateContinuousStates(&Template_test_M->solverInfo);
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
  if (!(++Template_test_M->Timing.clockTick0))
    ++Template_test_M->Timing.clockTickH0;
  Template_test_M->Timing.t[0] = Template_test_M->Timing.clockTick0 *
    Template_test_M->Timing.stepSize0 + Template_test_M->Timing.clockTickH0 *
    Template_test_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(Template_test_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Template_test_M->Timing.clockTick1))
      ++Template_test_M->Timing.clockTickH1;
    Template_test_M->Timing.t[1] = Template_test_M->Timing.clockTick1 *
      Template_test_M->Timing.stepSize1 + Template_test_M->Timing.clockTickH1 *
      Template_test_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void Template_test_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S25>/Linear Simulator' */
    if (Template_test_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S181>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        Template_test_B.Product1_gl[tmp] = 0.0;
        Template_test_B.Product1_gl[tmp] =
          Template_test_B.LinearDampningmatrix[tmp] *
          Template_test_B.Integrator_j[0] + Template_test_B.Product1_gl[tmp];
        Template_test_B.Product1_gl[tmp] =
          Template_test_B.LinearDampningmatrix[tmp + 3] *
          Template_test_B.Integrator_j[1] + Template_test_B.Product1_gl[tmp];
        Template_test_B.Product1_gl[tmp] =
          Template_test_B.LinearDampningmatrix[tmp + 6] *
          Template_test_B.Integrator_j[2] + Template_test_B.Product1_gl[tmp];
      }

      /* Sum: '<S181>/Sum' */
      Template_test_B.Sum_ib[0] = Template_test_B.planttau_surge -
        Template_test_B.Product1_gl[0];
      Template_test_B.Sum_ib[1] = Template_test_B.planttau_sway -
        Template_test_B.Product1_gl[1];
      Template_test_B.Sum_ib[2] = Template_test_B.planttau_yaw -
        Template_test_B.Product1_gl[2];

      /* Product: '<S181>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        Template_test_B.Product2_i1[tmp] = 0.0;
        Template_test_B.Product2_i1[tmp] = Template_test_B.Inverse[tmp] *
          Template_test_B.Sum_ib[0] + Template_test_B.Product2_i1[tmp];
        Template_test_B.Product2_i1[tmp] = Template_test_B.Inverse[tmp + 3] *
          Template_test_B.Sum_ib[1] + Template_test_B.Product2_i1[tmp];
        Template_test_B.Product2_i1[tmp] = Template_test_B.Inverse[tmp + 6] *
          Template_test_B.Sum_ib[2] + Template_test_B.Product2_i1[tmp];
      }

      /* Integrator Block: '<S181>/Integrator' */
      {
        if (Template_test_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator_CSTATE_p[0] = Template_test_B.Product2_i1[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator_CSTATE_p[0] = 0.0;
        }

        if (Template_test_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator_CSTATE_p[1] = Template_test_B.Product2_i1[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator_CSTATE_p[1] = 0.0;
        }

        if (Template_test_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator_CSTATE_p[2] = Template_test_B.Product2_i1[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator_CSTATE_p[2] = 0.0;
        }
      }

      /* Integrator Block: '<S181>/Integrator1' */
      {
        if (Template_test_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator1_CSTATE_d[0] = Template_test_B.Product3_n[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator1_CSTATE_d[0] = 0.0;
        }

        if (Template_test_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator1_CSTATE_d[1] = Template_test_B.Product3_n[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator1_CSTATE_d[1] = 0.0;
        }

        if (Template_test_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator1_CSTATE_d[2] = Template_test_B.Product3_n[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs
            )->Integrator1_CSTATE_d[2] = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_Template_test *)
                Template_test_M->ModelData.derivs)->Integrator_CSTATE_p[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S25>/Linear Simulator' */

    /* Integrator Block: '<S30>/Integrator' */
    {
      if (0.0== 0.0) {
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE[0] =
          Template_test_B.TmpHiddenBufferAtProductInpor_d[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = 0.0;
      }

      if (0.0== 0.0) {
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE[1] =
          Template_test_B.TmpHiddenBufferAtProductInpor_d[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = 0.0;
      }

      if (0.0== 0.0) {
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE[2] =
          Template_test_B.TmpHiddenBufferAtProductInpor_d[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE[2] = 0.0;
      }
    }

    /* Derivatives for Integrator: '<S50>/Integrator' */
    ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
      ->Integrator_CSTATE_m[0] = Template_test_B.Product_n[0];
    ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
      ->Integrator_CSTATE_m[1] = Template_test_B.Product_n[1];
    ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
      ->Integrator_CSTATE_m[2] = Template_test_B.Product_n[2];

    /* Integrator Block: '<S42>/Integrator' */
    {
      if (Template_test_P.Resetq_Value== 0.0) {
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE_f[0] = Template_test_B.Add_lp[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE_f[0] = 0.0;
      }

      if (Template_test_P.Resetq_Value== 0.0) {
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE_f[1] = Template_test_B.Add_lp[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator_CSTATE_f[1] = 0.0;
      }
    }

    /* Integrator Block: '<S42>/Integrator1' */
    {
      if (Template_test_P.Resets_Value== 0.0) {
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator1_CSTATE = Template_test_B.Subtract_d;
      } else {
        /* level reset is active*/
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator1_CSTATE = 0.0;
      }
    }

    /* Integrator Block: '<S42>/Integrator2' */
    {
      if (Template_test_P.Resetomega_q_Value== 0.0) {
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = Template_test_B.Gain_kq[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = 0.0;
      }

      if (Template_test_P.Resetomega_q_Value== 0.0) {
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = Template_test_B.Gain_kq[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_Template_test *) Template_test_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = 0.0;
      }
    }
  }
}

/* Model initialize function */
void Template_test_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Template_test_M,0,
                sizeof(RT_MODEL_Template_test));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Template_test_M->solverInfo,
                          &Template_test_M->Timing.simTimeStep);
    rtsiSetTPtr(&Template_test_M->solverInfo, &rtmGetTPtr(Template_test_M));
    rtsiSetStepSizePtr(&Template_test_M->solverInfo,
                       &Template_test_M->Timing.stepSize0);
    rtsiSetdXPtr(&Template_test_M->solverInfo,
                 &Template_test_M->ModelData.derivs);
    rtsiSetContStatesPtr(&Template_test_M->solverInfo,
                         &Template_test_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&Template_test_M->solverInfo,
      &Template_test_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&Template_test_M->solverInfo, (&rtmGetErrorStatus
      (Template_test_M)));
    rtsiSetRTModelPtr(&Template_test_M->solverInfo, Template_test_M);
  }

  rtsiSetSimTimeStep(&Template_test_M->solverInfo, MAJOR_TIME_STEP);
  Template_test_M->ModelData.intgData.y = Template_test_M->ModelData.odeY;
  Template_test_M->ModelData.intgData.f[0] = Template_test_M->ModelData.odeF[0];
  Template_test_M->ModelData.intgData.f[1] = Template_test_M->ModelData.odeF[1];
  Template_test_M->ModelData.intgData.f[2] = Template_test_M->ModelData.odeF[2];
  Template_test_M->ModelData.intgData.f[3] = Template_test_M->ModelData.odeF[3];
  Template_test_M->ModelData.intgData.f[4] = Template_test_M->ModelData.odeF[4];
  Template_test_M->ModelData.intgData.f[5] = Template_test_M->ModelData.odeF[5];
  Template_test_M->ModelData.contStates = ((real_T *) &Template_test_X);
  rtsiSetSolverData(&Template_test_M->solverInfo, (void *)
                    &Template_test_M->ModelData.intgData);
  rtsiSetSolverName(&Template_test_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Template_test_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    Template_test_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Template_test_M->Timing.sampleTimes =
      (&Template_test_M->Timing.sampleTimesArray[0]);
    Template_test_M->Timing.offsetTimes =
      (&Template_test_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Template_test_M->Timing.sampleTimes[0] = (0.0);
    Template_test_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    Template_test_M->Timing.offsetTimes[0] = (0.0);
    Template_test_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(Template_test_M, &Template_test_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Template_test_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    Template_test_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Template_test_M, -1);
  Template_test_M->Timing.stepSize0 = 0.1;
  Template_test_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(Template_test_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    Template_test_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(Template_test_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Template_test_M->rtwLogInfo, (NULL));
    rtliSetLogT(Template_test_M->rtwLogInfo, "");
    rtliSetLogX(Template_test_M->rtwLogInfo, "");
    rtliSetLogXFinal(Template_test_M->rtwLogInfo, "");
    rtliSetSigLog(Template_test_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Template_test_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Template_test_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Template_test_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Template_test_M->rtwLogInfo, 1);
    rtliSetLogY(Template_test_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Template_test_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Template_test_M->rtwLogInfo, (NULL));
  }

  Template_test_M->solverInfoPtr = (&Template_test_M->solverInfo);
  Template_test_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&Template_test_M->solverInfo, 0.1);
  rtsiSetSolverMode(&Template_test_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Template_test_M->ModelData.blockIO = ((void *) &Template_test_B);
  (void) memset(((void *) &Template_test_B),0,
                sizeof(BlockIO_Template_test));

  /* parameters */
  Template_test_M->ModelData.defaultParam = ((real_T *) &Template_test_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Template_test_X;
    Template_test_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_Template_test));
  }

  /* states (dwork) */
  Template_test_M->Work.dwork = ((void *) &Template_test_DWork);
  (void) memset((void *)&Template_test_DWork, 0,
                sizeof(D_Work_Template_test));
  Template_test_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Template_test_PrevZCSigState.Integrator_Reset_ZCE_e = UNINITIALIZED_ZCSIG;
  Template_test_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Template_test_PrevZCSigState.Integrator2_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Template_test_PrevZCSigState.Integrator_Reset_ZCE_h = UNINITIALIZED_ZCSIG;
  Template_test_PrevZCSigState.Integrator1_Reset_ZCE_o = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void Template_test_terminate(void)
{
  /* ToFile Block: '<S22>/To File' */
  {
    FILE *fp = (FILE *) Template_test_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "Template_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Template_test_M,
                          "Error closing MAT-file Template_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Template_test_M,
                          "Error reopening MAT-file Template_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 39, Template_test_DWork.ToFile_IWORK.Count,
           "Template_data")) {
        rtmSetErrorStatus(Template_test_M,
                          "Error writing header for Template_data to MAT-file Template_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Template_test_M,
                          "Error closing MAT-file Template_data.mat");
        return;
      }

      Template_test_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Template_test_output(tid);
}

void MdlUpdate(int_T tid)
{
  Template_test_update(tid);
}

void MdlInitializeSizes(void)
{
  Template_test_M->Sizes.numContStates = (17);/* Number of continuous states */
  Template_test_M->Sizes.numY = (0);   /* Number of model outputs */
  Template_test_M->Sizes.numU = (0);   /* Number of model inputs */
  Template_test_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Template_test_M->Sizes.numSampTimes = (2);/* Number of sample times */
  Template_test_M->Sizes.numBlocks = (874);/* Number of blocks */
  Template_test_M->Sizes.numBlockIO = (620);/* Number of block outputs */
  Template_test_M->Sizes.numBlockPrms = (1041);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Integrator Block: '<S30>/Integrator' */
  Template_test_X.Integrator_CSTATE[0] = Template_test_P.Integrator_IC;
  Template_test_X.Integrator_CSTATE[1] = Template_test_P.Integrator_IC;
  Template_test_X.Integrator_CSTATE[2] = Template_test_P.Integrator_IC;

  /* Derivative Block: '<S169>/Derivative' */
  Template_test_DWork.Derivative_RWORK.TimeStampA = rtInf;
  Template_test_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Integrator: '<S50>/Integrator' */
  Template_test_X.Integrator_CSTATE_m[0] = Template_test_P.Integrator_IC_f[0];
  Template_test_X.Integrator_CSTATE_m[1] = Template_test_P.Integrator_IC_f[1];
  Template_test_X.Integrator_CSTATE_m[2] = Template_test_P.Integrator_IC_f[2];

  /* Integrator Block: '<S42>/Integrator' */
  if (rtmIsFirstInitCond(Template_test_M)) {
    Template_test_X.Integrator_CSTATE_f[0] = 0.0;
    Template_test_X.Integrator_CSTATE_f[1] = 0.0;
  }

  Template_test_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S42>/Integrator1' */
  if (rtmIsFirstInitCond(Template_test_M)) {
    Template_test_X.Integrator1_CSTATE = 0.0;
  }

  Template_test_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* Derivative Block: '<S99>/Derivative' */
  Template_test_DWork.Derivative_RWORK_o.TimeStampA = rtInf;
  Template_test_DWork.Derivative_RWORK_o.TimeStampB = rtInf;

  /* Integrator Block: '<S42>/Integrator2' */
  Template_test_X.Integrator2_CSTATE[0] = Template_test_P.Integrator2_IC;
  Template_test_X.Integrator2_CSTATE[1] = Template_test_P.Integrator2_IC;

  /* Derivative Block: '<S169>/Derivative1' */
  Template_test_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  Template_test_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(Template_test_M)) {
    rtmSetFirstInitCond(Template_test_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for Constant: '<S5>/Initial q_x' */
  Template_test_B.Initialq_x = Template_test_P.Initialq_x_Value;

  /* Start for Constant: '<S5>/Initial q_y' */
  Template_test_B.Initialq_y = Template_test_P.Initialq_y_Value;

  /* Start for Constant: '<S5>/Initial s' */
  Template_test_B.Initials = Template_test_P.Initials_Value;

  /* Start for Constant: '<S6>/Initial psi [rad]' */
  Template_test_B.Initialpsirad = Template_test_P.Initialpsirad_Value;

  /* Start for Constant: '<S6>/Initial x [m]' */
  Template_test_B.Initialxm = Template_test_P.Initialxm_Value;

  /* Start for Constant: '<S6>/Initial y [m]' */
  Template_test_B.Initialym = Template_test_P.Initialym_Value;

  /* Start for Constant: '<S6>/Initial r [rad//s]' */
  Template_test_B.Initialrrads = Template_test_P.Initialrrads_Value;

  /* Start for Constant: '<S6>/Initial u [m//s]' */
  Template_test_B.Initialums = Template_test_P.Initialums_Value;

  /* Start for Constant: '<S6>/Initial v [m//s]' */
  Template_test_B.Initialvms = Template_test_P.Initialvms_Value;

  /* Start for enable SubSystem: '<S25>/Linear Simulator' */
  Template_test_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Integrator Block: '<S181>/Integrator' */
  if (rtmIsFirstInitCond(Template_test_M)) {
    Template_test_X.Integrator_CSTATE_p[0] = 0.0;
    Template_test_X.Integrator_CSTATE_p[1] = 0.0;
    Template_test_X.Integrator_CSTATE_p[2] = 0.0;
  }

  Template_test_DWork.Integrator_IWORK_f.IcNeedsLoading = 1;

  /* Integrator Block: '<S181>/Integrator1' */
  if (rtmIsFirstInitCond(Template_test_M)) {
    Template_test_X.Integrator1_CSTATE_d[0] = 0.0;
    Template_test_X.Integrator1_CSTATE_d[1] = 0.0;
    Template_test_X.Integrator1_CSTATE_d[2] = 0.0;
  }

  Template_test_DWork.Integrator1_IWORK_o.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S25>/Linear Simulator' */

  /* ToFile Block: '<S22>/To File' */
  {
    const char *fileName = "Template_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Template_test_M,
                        "Error creating .mat file Template_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,39,0,"Template_data")) {
      rtmSetErrorStatus(Template_test_M,
                        "Error writing mat file header to file Template_data.mat");
      return;
    }

    Template_test_DWork.ToFile_IWORK.Count = 0;
    Template_test_DWork.ToFile_IWORK.Decimation = -1;
    Template_test_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for enable SubSystem: '<S25>/CSE1 actuator' */
  Template_test_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S25>/CSE1 actuator' */

  /* Create Identity Matrix for Block: '<S25>/Inverse' */
  {
    int_T i;
    real_T *dWork = &Template_test_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &Template_test_DWork.Inverse_DWORK4[0];
    while (dWork < &Template_test_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  MdlInitialize();
}

RT_MODEL_Template_test *Template_test(void)
{
  Template_test_initialize(1);
  return Template_test_M;
}

void MdlTerminate(void)
{
  Template_test_terminate();
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
#ifdef NI_ROOTMODEL_Template_test
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
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 46:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 46:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern Template_test_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Main Subsystems/Naviagation/Input from SIT/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(Template_test_B.QTMIn, count, data[index++], 47, 0);
    }
  } else {
    index += 9;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Template_test_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Template_test_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Template_test_B.SITzAI2, 0, data[index++], 0, 0);
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
    ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Switch2_e,0,0,
      0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.VSPSStarboard,
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
  ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Switch2_e,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Servo1,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Servo2,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Servo3,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.Servo4,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.VSPSPort,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Template_test_B.VSPSStarboard,0,
    0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "template_test/Inputs from LabVIEW/Control Input Selector/Value",
    offsetof(Parameters_Template_test, ControlInputSelector_Value), 31, 1, 2, 0,
    "", 0 },

  { 1, "template_test/Inputs from LabVIEW/Control Mode Selector/Value", offsetof
    (Parameters_Template_test, ControlModeSelector_Value), 31, 1, 2, 2, "", 0 },

  { 2, "template_test/Inputs from LabVIEW/Enable CSE1/Value", offsetof
    (Parameters_Template_test, EnableCSE1_Value), 31, 1, 2, 4, "", 0 },

  { 3, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/12/Value",
    offsetof(Parameters_Template_test, u_Value), 31, 1, 2, 6, "", 0 },

  { 4, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/13/Value",
    offsetof(Parameters_Template_test, u_Value_m), 31, 1, 2, 8, "", 0 },

  { 5, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/21/Value",
    offsetof(Parameters_Template_test, u_Value_g), 31, 1, 2, 10, "", 0 },

  { 6, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/23/Value",
    offsetof(Parameters_Template_test, u_Value_e), 31, 1, 2, 12, "", 0 },

  { 7, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/31/Value",
    offsetof(Parameters_Template_test, u_Value_a), 31, 1, 2, 14, "", 0 },

  { 8, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/32/Value",
    offsetof(Parameters_Template_test, u_Value_mz), 31, 1, 2, 16, "", 0 },

  { 9, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d_Surge/Value",
    offsetof(Parameters_Template_test, K_d_Surge_Value), 31, 1, 2, 18, "", 0 },

  { 10, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d_Sway/Value",
    offsetof(Parameters_Template_test, K_d_Sway_Value), 31, 1, 2, 20, "", 0 },

  { 11, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d_Yaw/Value",
    offsetof(Parameters_Template_test, K_d_Yaw_Value), 31, 1, 2, 22, "", 0 },

  { 12, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/12/Value",
    offsetof(Parameters_Template_test, u_Value_f), 31, 1, 2, 24, "", 0 },

  { 13, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/13/Value",
    offsetof(Parameters_Template_test, u_Value_n), 31, 1, 2, 26, "", 0 },

  { 14, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/21/Value",
    offsetof(Parameters_Template_test, u_Value_n2), 31, 1, 2, 28, "", 0 },

  { 15, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/23/Value",
    offsetof(Parameters_Template_test, u_Value_j), 31, 1, 2, 30, "", 0 },

  { 16, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/31/Value",
    offsetof(Parameters_Template_test, u_Value_gv), 31, 1, 2, 32, "", 0 },

  { 17, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/32/Value",
    offsetof(Parameters_Template_test, u_Value_k), 31, 1, 2, 34, "", 0 },

  { 18, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i_Surge/Value",
    offsetof(Parameters_Template_test, K_i_Surge_Value), 31, 1, 2, 36, "", 0 },

  { 19, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i_Sway/Value",
    offsetof(Parameters_Template_test, K_i_Sway_Value), 31, 1, 2, 38, "", 0 },

  { 20, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i_Yaw/Value",
    offsetof(Parameters_Template_test, K_i_Yaw_Value), 31, 1, 2, 40, "", 0 },

  { 21, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/12/Value",
    offsetof(Parameters_Template_test, u_Value_i), 31, 1, 2, 42, "", 0 },

  { 22, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/13/Value",
    offsetof(Parameters_Template_test, u_Value_l), 31, 1, 2, 44, "", 0 },

  { 23, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/21/Value",
    offsetof(Parameters_Template_test, u_Value_el), 31, 1, 2, 46, "", 0 },

  { 24, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/23/Value",
    offsetof(Parameters_Template_test, u_Value_d), 31, 1, 2, 48, "", 0 },

  { 25, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/31/Value",
    offsetof(Parameters_Template_test, u_Value_jw), 31, 1, 2, 50, "", 0 },

  { 26, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/32/Value",
    offsetof(Parameters_Template_test, u_Value_n4), 31, 1, 2, 52, "", 0 },

  { 27, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p_Surge/Value",
    offsetof(Parameters_Template_test, K_p_Surge_Value), 31, 1, 2, 54, "", 0 },

  { 28, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p_Sway/Value",
    offsetof(Parameters_Template_test, K_p_Sway_Value), 31, 1, 2, 56, "", 0 },

  { 29, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p_Yaw/Value",
    offsetof(Parameters_Template_test, K_p_Yaw_Value), 31, 1, 2, 58, "", 0 },

  { 30,
    "template_test/Inputs from LabVIEW/Dynamic Positioning/Reset integrator/Value",
    offsetof(Parameters_Template_test, Resetintegrator_Value), 31, 1, 2, 60, "",
    0 },

  { 31,
    "template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/ y_d [m]/Value",
    offsetof(Parameters_Template_test, y_dm_Value), 31, 1, 2, 62, "", 0 },

  { 32,
    "template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/psi_d [deg]/Value",
    offsetof(Parameters_Template_test, psi_ddeg_Value), 31, 1, 2, 64, "", 0 },

  { 33,
    "template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_Template_test, Gain1_Gain), 31, 1, 2, 66, "", 0 },

  { 34,
    "template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/x_d [m]/Value",
    offsetof(Parameters_Template_test, x_dm_Value), 31, 1, 2, 68, "", 0 },

  { 35,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q/12/Value",
    offsetof(Parameters_Template_test, u_Value_p), 31, 1, 2, 70, "", 0 },

  { 36,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q/21/Value",
    offsetof(Parameters_Template_test, u_Value_ab), 31, 1, 2, 72, "", 0 },

  { 37,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q_Surge/Value",
    offsetof(Parameters_Template_test, Gamma_q_Surge_Value), 31, 1, 2, 74, "", 0
  },

  { 38,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q_Sway/Value",
    offsetof(Parameters_Template_test, Gamma_q_Sway_Value), 31, 1, 2, 76, "", 0
  },

  { 39,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial q_x/Value",
    offsetof(Parameters_Template_test, Initialq_x_Value), 31, 1, 2, 78, "", 0 },

  { 40,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial q_y/Value",
    offsetof(Parameters_Template_test, Initialq_y_Value), 31, 1, 2, 80, "", 0 },

  { 41,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial s/Value",
    offsetof(Parameters_Template_test, Initials_Value), 31, 1, 2, 82, "", 0 },

  { 42, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/12/Value",
    offsetof(Parameters_Template_test, u_Value_pk), 31, 1, 2, 84, "", 0 },

  { 43, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/13/Value",
    offsetof(Parameters_Template_test, u_Value_n21), 31, 1, 2, 86, "", 0 },

  { 44, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/21/Value",
    offsetof(Parameters_Template_test, u_Value_ni), 31, 1, 2, 88, "", 0 },

  { 45, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/23/Value",
    offsetof(Parameters_Template_test, u_Value_pe), 31, 1, 2, 90, "", 0 },

  { 46, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/31/Value",
    offsetof(Parameters_Template_test, u_Value_jr), 31, 1, 2, 92, "", 0 },

  { 47, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/32/Value",
    offsetof(Parameters_Template_test, u_Value_gl), 31, 1, 2, 94, "", 0 },

  { 48,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d_Surge/Value",
    offsetof(Parameters_Template_test, K_d_Surge_Value_j), 31, 1, 2, 96, "", 0 },

  { 49,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d_Sway/Value",
    offsetof(Parameters_Template_test, K_d_Sway_Value_a), 31, 1, 2, 98, "", 0 },

  { 50,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d_Yaw/Value",
    offsetof(Parameters_Template_test, K_d_Yaw_Value_i), 31, 1, 2, 100, "", 0 },

  { 51, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/12/Value",
    offsetof(Parameters_Template_test, u_Value_c), 31, 1, 2, 102, "", 0 },

  { 52, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/13/Value",
    offsetof(Parameters_Template_test, u_Value_kr), 31, 1, 2, 104, "", 0 },

  { 53, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/21/Value",
    offsetof(Parameters_Template_test, u_Value_mv), 31, 1, 2, 106, "", 0 },

  { 54, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/23/Value",
    offsetof(Parameters_Template_test, u_Value_f2), 31, 1, 2, 108, "", 0 },

  { 55, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/31/Value",
    offsetof(Parameters_Template_test, u_Value_in), 31, 1, 2, 110, "", 0 },

  { 56, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/32/Value",
    offsetof(Parameters_Template_test, u_Value_la), 31, 1, 2, 112, "", 0 },

  { 57,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i_Surge/Value",
    offsetof(Parameters_Template_test, K_i_Surge_Value_o), 31, 1, 2, 114, "", 0
  },

  { 58,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i_Sway/Value",
    offsetof(Parameters_Template_test, K_i_Sway_Value_o), 31, 1, 2, 116, "", 0 },

  { 59,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i_Yaw/Value",
    offsetof(Parameters_Template_test, K_i_Yaw_Value_o), 31, 1, 2, 118, "", 0 },

  { 60, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/12/Value",
    offsetof(Parameters_Template_test, u_Value_ex), 31, 1, 2, 120, "", 0 },

  { 61, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/13/Value",
    offsetof(Parameters_Template_test, u_Value_ph), 31, 1, 2, 122, "", 0 },

  { 62, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/21/Value",
    offsetof(Parameters_Template_test, u_Value_lf), 31, 1, 2, 124, "", 0 },

  { 63, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/23/Value",
    offsetof(Parameters_Template_test, u_Value_exm), 31, 1, 2, 126, "", 0 },

  { 64, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/31/Value",
    offsetof(Parameters_Template_test, u_Value_ft), 31, 1, 2, 128, "", 0 },

  { 65, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/32/Value",
    offsetof(Parameters_Template_test, u_Value_db), 31, 1, 2, 130, "", 0 },

  { 66,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p_Surge/Value",
    offsetof(Parameters_Template_test, K_p_Surge_Value_g), 31, 1, 2, 132, "", 0
  },

  { 67,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p_Sway/Value",
    offsetof(Parameters_Template_test, K_p_Sway_Value_e), 31, 1, 2, 134, "", 0 },

  { 68,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p_Yaw/Value",
    offsetof(Parameters_Template_test, K_p_Yaw_Value_c), 31, 1, 2, 136, "", 0 },

  { 69,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/kappa_1/Value",
    offsetof(Parameters_Template_test, kappa_1_Value), 31, 1, 2, 138, "", 0 },

  { 70,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/lambda_q/Value",
    offsetof(Parameters_Template_test, lambda_q_Value), 31, 1, 2, 140, "", 0 },

  { 71,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Reset omega_q/Value",
    offsetof(Parameters_Template_test, Resetomega_q_Value), 31, 1, 2, 142, "", 0
  },

  { 72,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Reset q/Value",
    offsetof(Parameters_Template_test, Resetq_Value), 31, 1, 2, 144, "", 0 },

  { 73,
    "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Reset s/Value",
    offsetof(Parameters_Template_test, Resets_Value), 31, 1, 2, 146, "", 0 },

  { 74,
    "template_test/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value",
    offsetof(Parameters_Template_test, EnableLinearSimulator_Value), 31, 1, 2,
    148, "", 0 },

  { 75,
    "template_test/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value",
    offsetof(Parameters_Template_test, Initialpsirad_Value), 31, 1, 2, 150, "",
    0 },

  { 76, "template_test/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value",
    offsetof(Parameters_Template_test, Initialxm_Value), 31, 1, 2, 152, "", 0 },

  { 77, "template_test/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value",
    offsetof(Parameters_Template_test, Initialym_Value), 31, 1, 2, 154, "", 0 },

  { 78,
    "template_test/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value",
    offsetof(Parameters_Template_test, Initialrrads_Value), 31, 1, 2, 156, "", 0
  },

  { 79,
    "template_test/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value",
    offsetof(Parameters_Template_test, Initialums_Value), 31, 1, 2, 158, "", 0 },

  { 80,
    "template_test/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value",
    offsetof(Parameters_Template_test, Initialvms_Value), 31, 1, 2, 160, "", 0 },

  { 81,
    "template_test/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_Template_test, ResetLinearSimulatorintegrator_), 31, 1,
    2, 162, "", 0 },

  { 82, "template_test/Inputs from LabVIEW/Path/Delta [m]/Value", offsetof
    (Parameters_Template_test, Deltam_Value), 31, 1, 2, 164, "", 0 },

  { 83, "template_test/Inputs from LabVIEW/Path/Path Selector  [-]/Value",
    offsetof(Parameters_Template_test, PathSelector_Value), 31, 1, 2, 166, "", 0
  },

  { 84, "template_test/Inputs from LabVIEW/Path/my [-]/Value", offsetof
    (Parameters_Template_test, my_Value), 31, 1, 2, 168, "", 0 },

  { 85, "template_test/Inputs from LabVIEW/Path/u_d [m]/Value", offsetof
    (Parameters_Template_test, u_dm_Value), 31, 1, 2, 170, "", 0 },

  { 86, "template_test/Inputs from LabVIEW/Path/x_dmax [m]/Value", offsetof
    (Parameters_Template_test, x_dmaxm_Value), 31, 1, 2, 172, "", 0 },

  { 87, "template_test/Inputs from LabVIEW/Path/x_dmin [m]/Value", offsetof
    (Parameters_Template_test, x_dminm_Value), 31, 1, 2, 174, "", 0 },

  { 88, "template_test/Inputs from LabVIEW/Path/y_dmax [m]/Value", offsetof
    (Parameters_Template_test, y_dmaxm_Value), 31, 1, 2, 176, "", 0 },

  { 89, "template_test/Inputs from LabVIEW/Path/y_dmin [m]/Value", offsetof
    (Parameters_Template_test, y_dminm_Value), 31, 1, 2, 178, "", 0 },

  { 90, "template_test/Inputs from LabVIEW/Path/Ellipse/k [-]/Value", offsetof
    (Parameters_Template_test, k_Value), 31, 1, 2, 180, "", 0 },

  { 91, "template_test/Inputs from LabVIEW/Path/Ellipse/origin_x [m]/Value",
    offsetof(Parameters_Template_test, origin_xm_Value), 31, 1, 2, 182, "", 0 },

  { 92, "template_test/Inputs from LabVIEW/Path/Ellipse/origo_y [m]/Value",
    offsetof(Parameters_Template_test, origo_ym_Value), 31, 1, 2, 184, "", 0 },

  { 93, "template_test/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value", offsetof
    (Parameters_Template_test, r_xm_Value), 31, 1, 2, 186, "", 0 },

  { 94, "template_test/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value", offsetof
    (Parameters_Template_test, r_ym_Value), 31, 1, 2, 188, "", 0 },

  { 95, "template_test/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value", offsetof
    (Parameters_Template_test, x_1m_Value), 31, 1, 2, 190, "", 0 },

  { 96, "template_test/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value", offsetof
    (Parameters_Template_test, x_2m_Value), 31, 1, 2, 192, "", 0 },

  { 97, "template_test/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value", offsetof
    (Parameters_Template_test, y_1m_Value), 31, 1, 2, 194, "", 0 },

  { 98, "template_test/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value", offsetof
    (Parameters_Template_test, y_2m_Value), 31, 1, 2, 196, "", 0 },

  { 99, "template_test/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value",
    offsetof(Parameters_Template_test, AS_LX_Value), 31, 1, 2, 198, "", 0 },

  { 100, "template_test/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain",
    offsetof(Parameters_Template_test, ScalingLX_Gain), 31, 1, 2, 200, "", 0 },

  { 101, "template_test/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value",
    offsetof(Parameters_Template_test, AS_LY_Value), 31, 1, 2, 202, "", 0 },

  { 102, "template_test/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain",
    offsetof(Parameters_Template_test, ScalingLY_Gain), 31, 1, 2, 204, "", 0 },

  { 103, "template_test/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value",
    offsetof(Parameters_Template_test, AS_RX_Value), 31, 1, 2, 206, "", 0 },

  { 104, "template_test/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain",
    offsetof(Parameters_Template_test, Scaling_RX_Gain), 31, 1, 2, 208, "", 0 },

  { 105, "template_test/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value",
    offsetof(Parameters_Template_test, AS_RY_Value), 31, 1, 2, 210, "", 0 },

  { 106, "template_test/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain",
    offsetof(Parameters_Template_test, ScalingRY_Gain), 31, 1, 2, 212, "", 0 },

  { 107,
    "template_test/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value",
    offsetof(Parameters_Template_test, PS3_BT_Power_Value), 31, 1, 2, 214, "", 0
  },

  { 108, "template_test/Inputs from LabVIEW/PlayStation3/L2 [-]/Value", offsetof
    (Parameters_Template_test, L2_Value), 31, 1, 2, 216, "", 0 },

  { 109,
    "template_test/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value",
    offsetof(Parameters_Template_test, PS3_VSP_Speed_Value), 31, 1, 2, 218, "",
    0 },

  { 110, "template_test/Inputs from LabVIEW/PlayStation3/R2 [-]/Value", offsetof
    (Parameters_Template_test, R2_Value), 31, 1, 2, 220, "", 0 },

  { 111,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value",
    offsetof(Parameters_Template_test, l_x1_Value), 31, 1, 2, 222, "", 0 },

  { 112,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain",
    offsetof(Parameters_Template_test, l_x1_Gain), 31, 1, 2, 224, "", 0 },

  { 113,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value",
    offsetof(Parameters_Template_test, l_x2_Value), 31, 1, 2, 226, "", 0 },

  { 114,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain",
    offsetof(Parameters_Template_test, l_x2_Gain), 31, 1, 2, 228, "", 0 },

  { 115,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value",
    offsetof(Parameters_Template_test, l_y2_Value), 31, 1, 2, 230, "", 0 },

  { 116,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain",
    offsetof(Parameters_Template_test, l_y2_Gain), 31, 1, 2, 232, "", 0 },

  { 117,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value",
    offsetof(Parameters_Template_test, B_11_Value), 31, 1, 2, 234, "", 0 },

  { 118,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value",
    offsetof(Parameters_Template_test, B_21_Value), 31, 1, 2, 236, "", 0 },

  { 119,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value",
    offsetof(Parameters_Template_test, l_y1_Value), 31, 1, 2, 238, "", 0 },

  { 120,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value",
    offsetof(Parameters_Template_test, B_12_Value), 31, 1, 2, 240, "", 0 },

  { 121,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value",
    offsetof(Parameters_Template_test, B_22_Value), 31, 1, 2, 242, "", 0 },

  { 122,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value",
    offsetof(Parameters_Template_test, B_13_Value), 31, 1, 2, 244, "", 0 },

  { 123,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value",
    offsetof(Parameters_Template_test, B_23_Value), 31, 1, 2, 246, "", 0 },

  { 124,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value",
    offsetof(Parameters_Template_test, B_14_Value), 31, 1, 2, 248, "", 0 },

  { 125,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value",
    offsetof(Parameters_Template_test, B_24_Value), 31, 1, 2, 250, "", 0 },

  { 126,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value",
    offsetof(Parameters_Template_test, B_15_Value), 31, 1, 2, 252, "", 0 },

  { 127,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value",
    offsetof(Parameters_Template_test, B_25_Value), 31, 1, 2, 254, "", 0 },

  { 128,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value",
    offsetof(Parameters_Template_test, l_x3_Value), 31, 1, 2, 256, "", 0 },

  { 129,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value",
    offsetof(Parameters_Template_test, N_r_Value), 31, 1, 2, 258, "", 0 },

  { 130,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain",
    offsetof(Parameters_Template_test, N_r_Gain), 31, 1, 2, 260, "", 0 },

  { 131,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value",
    offsetof(Parameters_Template_test, N_v_Value), 31, 1, 2, 262, "", 0 },

  { 132,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain",
    offsetof(Parameters_Template_test, N_v_Gain), 31, 1, 2, 264, "", 0 },

  { 133,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value",
    offsetof(Parameters_Template_test, X_u_Value), 31, 1, 2, 266, "", 0 },

  { 134,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain",
    offsetof(Parameters_Template_test, X_u_Gain), 31, 1, 2, 268, "", 0 },

  { 135,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value",
    offsetof(Parameters_Template_test, Y_v_Value), 31, 1, 2, 270, "", 0 },

  { 136,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain",
    offsetof(Parameters_Template_test, Y_v_Gain), 31, 1, 2, 272, "", 0 },

  { 137,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value",
    offsetof(Parameters_Template_test, Y_r_Value), 31, 1, 2, 274, "", 0 },

  { 138,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain",
    offsetof(Parameters_Template_test, Y_vr_Gain), 31, 1, 2, 276, "", 0 },

  { 139,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value",
    offsetof(Parameters_Template_test, D_L_12_Value), 31, 1, 2, 278, "", 0 },

  { 140,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value",
    offsetof(Parameters_Template_test, D_L_13_Value), 31, 1, 2, 280, "", 0 },

  { 141,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value",
    offsetof(Parameters_Template_test, D_L_21_Value), 31, 1, 2, 282, "", 0 },

  { 142,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value",
    offsetof(Parameters_Template_test, D_L_31_Value), 31, 1, 2, 284, "", 0 },

  { 143,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value",
    offsetof(Parameters_Template_test, m_Value), 31, 1, 2, 286, "", 0 },

  { 144,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value",
    offsetof(Parameters_Template_test, X_udot_Value), 31, 1, 2, 288, "", 0 },

  { 145,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value",
    offsetof(Parameters_Template_test, M_21_Value), 31, 1, 2, 290, "", 0 },

  { 146,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value",
    offsetof(Parameters_Template_test, M_31_Value), 31, 1, 2, 292, "", 0 },

  { 147,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value",
    offsetof(Parameters_Template_test, M_12_Value), 31, 1, 2, 294, "", 0 },

  { 148,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value",
    offsetof(Parameters_Template_test, Y_vdot_Value), 31, 1, 2, 296, "", 0 },

  { 149,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value",
    offsetof(Parameters_Template_test, x_g_Value), 31, 1, 2, 298, "", 0 },

  { 150,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value",
    offsetof(Parameters_Template_test, N_vdot_Value), 31, 1, 2, 300, "", 0 },

  { 151,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value",
    offsetof(Parameters_Template_test, M_13_Value), 31, 1, 2, 302, "", 0 },

  { 152,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value",
    offsetof(Parameters_Template_test, Y_rdot_Value), 31, 1, 2, 304, "", 0 },

  { 153,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value",
    offsetof(Parameters_Template_test, I_z_Value), 31, 1, 2, 306, "", 0 },

  { 154,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value",
    offsetof(Parameters_Template_test, N_rdot_Value), 31, 1, 2, 308, "", 0 },

  { 155,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value",
    offsetof(Parameters_Template_test, T_e11_Value), 31, 1, 2, 310, "", 0 },

  { 156,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value",
    offsetof(Parameters_Template_test, T_e21_Value), 31, 1, 2, 312, "", 0 },

  { 157,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value",
    offsetof(Parameters_Template_test, l_y1_Value_d), 31, 1, 2, 314, "", 0 },

  { 158,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value",
    offsetof(Parameters_Template_test, T_e12_Value), 31, 1, 2, 316, "", 0 },

  { 159,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value",
    offsetof(Parameters_Template_test, T_e22_Value), 31, 1, 2, 318, "", 0 },

  { 160,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value",
    offsetof(Parameters_Template_test, l_x1_Value_e), 31, 1, 2, 320, "", 0 },

  { 161,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_Template_test, l_x1_Gain_j), 31, 1, 2, 322, "", 0 },

  { 162,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value",
    offsetof(Parameters_Template_test, T_e13_Value), 31, 1, 2, 324, "", 0 },

  { 163,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value",
    offsetof(Parameters_Template_test, T_e23_Value), 31, 1, 2, 326, "", 0 },

  { 164,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value",
    offsetof(Parameters_Template_test, l_y2_Value_g), 31, 1, 2, 328, "", 0 },

  { 165,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_Template_test, l_y2_Gain_p), 31, 1, 2, 330, "", 0 },

  { 166,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value",
    offsetof(Parameters_Template_test, T_e14_Value), 31, 1, 2, 332, "", 0 },

  { 167,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value",
    offsetof(Parameters_Template_test, T_e24_Value), 31, 1, 2, 334, "", 0 },

  { 168,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value",
    offsetof(Parameters_Template_test, l_x2_Value_n), 31, 1, 2, 336, "", 0 },

  { 169,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_Template_test, l_x2_Gain_m), 31, 1, 2, 338, "", 0 },

  { 170,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value",
    offsetof(Parameters_Template_test, T_e15_Value), 31, 1, 2, 340, "", 0 },

  { 171,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value",
    offsetof(Parameters_Template_test, T_e25_Value), 31, 1, 2, 342, "", 0 },

  { 172,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value",
    offsetof(Parameters_Template_test, l_x3_Value_h), 31, 1, 2, 344, "", 0 },

  { 173,
    "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain",
    offsetof(Parameters_Template_test, PS3u_1_Gain), 31, 1, 2, 346, "", 0 },

  { 174,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues",
    offsetof(Parameters_Template_test, u_1tof_1_XData), 73, 19, 2, 348, "", 0 },

  { 175,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table",
    offsetof(Parameters_Template_test, u_1tof_1_YData), 73, 19, 2, 350, "", 0 },

  { 176,
    "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain",
    offsetof(Parameters_Template_test, PS3u_2_Gain), 31, 1, 2, 352, "", 0 },

  { 177,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues",
    offsetof(Parameters_Template_test, u_2tof_2_XData), 74, 21, 2, 354, "", 0 },

  { 178,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table",
    offsetof(Parameters_Template_test, u_2tof_2_YData), 74, 21, 2, 356, "", 0 },

  { 179,
    "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain",
    offsetof(Parameters_Template_test, PS3u_3_Gain), 31, 1, 2, 358, "", 0 },

  { 180,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues",
    offsetof(Parameters_Template_test, u_3tof_3_XData), 73, 19, 2, 360, "", 0 },

  { 181,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table",
    offsetof(Parameters_Template_test, u_3tof_3_YData), 73, 19, 2, 362, "", 0 },

  { 182,
    "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain",
    offsetof(Parameters_Template_test, PS3u_4_Gain), 31, 1, 2, 364, "", 0 },

  { 183,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues",
    offsetof(Parameters_Template_test, u_4tof_4_XData), 75, 17, 2, 366, "", 0 },

  { 184,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table",
    offsetof(Parameters_Template_test, u_4tof_4_YData), 75, 17, 2, 368, "", 0 },

  { 185,
    "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain",
    offsetof(Parameters_Template_test, PS3u_5_Gain), 31, 1, 2, 370, "", 0 },

  { 186,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues",
    offsetof(Parameters_Template_test, u_5tof_5_XData), 76, 7, 2, 372, "", 0 },

  { 187,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table",
    offsetof(Parameters_Template_test, u_5tof_5_YData), 76, 7, 2, 374, "", 0 },

  { 188,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain",
    offsetof(Parameters_Template_test, QTMIn3xcoordmm_Gain), 31, 1, 2, 376, "",
    0 },

  { 189, "template_test/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain",
    offsetof(Parameters_Template_test, mm2mx_Gain), 31, 1, 2, 378, "", 0 },

  { 190,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain",
    offsetof(Parameters_Template_test, QTMIn4ycoordmm_Gain), 31, 1, 2, 380, "",
    0 },

  { 191, "template_test/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain",
    offsetof(Parameters_Template_test, mm2my_Gain), 31, 1, 2, 382, "", 0 },

  { 192,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain",
    offsetof(Parameters_Template_test, QTMIn6yawdeg_Gain), 31, 1, 2, 384, "", 0
  },

  { 193, "template_test/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain",
    offsetof(Parameters_Template_test, d2ryaw_Gain), 31, 1, 2, 386, "", 0 },

  { 194,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat), 31, 1, 2, 388, "",
    0 },

  { 195,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat), 31, 1, 2, 390, "",
    0 },

  { 196,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain), 31, 1, 2, 392, "", 0 },

  { 197,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value), 31, 1, 2, 394, "", 0 },

  { 198,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_d), 31, 1, 2, 396, "",
    0 },

  { 199,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_o), 31, 1, 2, 398, "",
    0 },

  { 200,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_f), 31, 1, 2, 400, "", 0 },

  { 201,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_a), 31, 1, 2, 402, "", 0 },

  { 202,
    "template_test/Main Subsystems/Control/DP control/Integrator/InitialCondition",
    offsetof(Parameters_Template_test, Integrator_IC), 31, 1, 2, 404, "", 0 },

  { 203,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain",
    offsetof(Parameters_Template_test, QTMIn8rolldeg_Gain), 31, 1, 2, 406, "", 0
  },

  { 204,
    "template_test/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain",
    offsetof(Parameters_Template_test, d2rroll_Gain), 31, 1, 2, 408, "", 0 },

  { 205,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain",
    offsetof(Parameters_Template_test, QTMIn7pitchdeg_Gain), 31, 1, 2, 410, "",
    0 },

  { 206,
    "template_test/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain",
    offsetof(Parameters_Template_test, d2rpitch_Gain), 31, 1, 2, 412, "", 0 },

  { 207,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Constant1/Value",
    offsetof(Parameters_Template_test, Constant1_Value), 20, 9, 2, 414, "", 0 },

  { 208,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain",
    offsetof(Parameters_Template_test, QTMIn5zcoordmm_Gain), 31, 1, 2, 416, "",
    0 },

  { 209, "template_test/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain",
    offsetof(Parameters_Template_test, mm2mz_Gain), 31, 1, 2, 418, "", 0 },

  { 210, "template_test/Main Subsystems/Control/LgV2/R(psi)/R31/Value", offsetof
    (Parameters_Template_test, R31_Value), 31, 1, 2, 420, "", 0 },

  { 211, "template_test/Main Subsystems/Control/LgV2/R(psi)/-1/Gain", offsetof
    (Parameters_Template_test, u_Gain), 31, 1, 2, 422, "", 0 },

  { 212, "template_test/Main Subsystems/Control/LgV2/R(psi)/R32/Value", offsetof
    (Parameters_Template_test, R32_Value), 31, 1, 2, 424, "", 0 },

  { 213, "template_test/Main Subsystems/Control/LgV2/R(psi)/R13/Value", offsetof
    (Parameters_Template_test, R13_Value), 31, 1, 2, 426, "", 0 },

  { 214, "template_test/Main Subsystems/Control/LgV2/R(psi)/R23/Value", offsetof
    (Parameters_Template_test, R23_Value), 31, 1, 2, 428, "", 0 },

  { 215, "template_test/Main Subsystems/Control/LgV2/R(psi)/R33/Value", offsetof
    (Parameters_Template_test, R33_Value), 31, 1, 2, 430, "", 0 },

  { 216,
    "template_test/Main Subsystems/Control/LgV2/zeta/Integrator/InitialCondition",
    offsetof(Parameters_Template_test, Integrator_IC_f), 28, 3, 2, 432, "", 0 },

  { 217, "template_test/Main Subsystems/Control/LgV2/Control law/1/Value",
    offsetof(Parameters_Template_test, _Value), 31, 1, 2, 434, "", 0 },

  { 218, "template_test/Main Subsystems/Control/LgV2/Control law/4/Gain",
    offsetof(Parameters_Template_test, _Gain), 31, 1, 2, 436, "", 0 },

  { 219, "template_test/Main Subsystems/Control/LgV2/alpha/I/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_i), 20, 9, 2, 438, "", 0 },

  { 220,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_m), 31, 1, 2, 440, "",
    0 },

  { 221,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_f), 31, 1, 2, 442, "",
    0 },

  { 222,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_o), 31, 1, 2, 444, "", 0 },

  { 223,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_ah), 31, 1, 2, 446, "", 0
  },

  { 224,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_d), 31, 1, 2, 448, "", 0 },

  { 225,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_d), 31, 1, 2, 450, "", 0 },

  { 226,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_j), 31, 1, 2, 452, "",
    0 },

  { 227,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_k), 31, 1, 2, 454, "",
    0 },

  { 228,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_a), 31, 1, 2, 456, "", 0 },

  { 229,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_g), 31, 1, 2, 458, "", 0 },

  { 230,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_k), 31, 1, 2, 460, "",
    0 },

  { 231,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_d), 31, 1, 2, 462, "",
    0 },

  { 232,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_l), 31, 1, 2, 464, "", 0 },

  { 233,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_k), 31, 1, 2, 466, "", 0 },

  { 234,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_p), 31, 1, 2, 468, "", 0 },

  { 235,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_p), 31, 1, 2, 470, "",
    0 },

  { 236,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_e), 31, 1, 2, 472, "",
    0 },

  { 237,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_i), 31, 1, 2, 474, "", 0 },

  { 238,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_f), 31, 1, 2, 476, "", 0 },

  { 239,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_kl), 31, 1, 2, 478,
    "", 0 },

  { 240,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_ku), 31, 1, 2, 480,
    "", 0 },

  { 241,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_e), 31, 1, 2, 482, "", 0 },

  { 242,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_d1), 31, 1, 2, 484, "", 0
  },

  { 243,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_f), 31, 1, 2, 486, "",
    0 },

  { 244,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_l), 31, 1, 2, 488, "",
    0 },

  { 245,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_eb), 31, 1, 2, 490, "", 0 },

  { 246,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_gp), 31, 1, 2, 492, "", 0
  },

  { 247,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain",
    offsetof(Parameters_Template_test, u_Gain_d), 31, 1, 2, 494, "", 0 },

  { 248,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_Template_test, _2x1_Value), 32, 2, 2, 496, "", 0 },

  { 249,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value",
    offsetof(Parameters_Template_test, _2x1_Value_m), 32, 2, 2, 498, "", 0 },

  { 250,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_ot), 31, 1, 2, 500, "", 0 },

  { 251,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain",
    offsetof(Parameters_Template_test, Gain1_Gain_n), 31, 1, 2, 502, "", 0 },

  { 252,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_ie), 31, 1, 2, 504, "", 0
  },

  { 253,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_j), 31, 1, 2, 506, "", 0 },

  { 254,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_p), 31, 1, 2, 508, "", 0 },

  { 255, "template_test/Main Subsystems/Control/LgV2/sigma/I/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_aj), 20, 9, 2, 510, "", 0
  },

  { 256, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S11/Value",
    offsetof(Parameters_Template_test, S11_Value), 31, 1, 2, 512, "", 0 },

  { 257, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/R31/Value",
    offsetof(Parameters_Template_test, R31_Value_d), 31, 1, 2, 514, "", 0 },

  { 258, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12/Gain",
    offsetof(Parameters_Template_test, S12_Gain), 31, 1, 2, 516, "", 0 },

  { 259, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S22/Value",
    offsetof(Parameters_Template_test, S22_Value), 31, 1, 2, 518, "", 0 },

  { 260, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S32/Value",
    offsetof(Parameters_Template_test, S32_Value), 31, 1, 2, 520, "", 0 },

  { 261, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S13/Value",
    offsetof(Parameters_Template_test, S13_Value), 31, 1, 2, 522, "", 0 },

  { 262, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S23/Value",
    offsetof(Parameters_Template_test, S23_Value), 31, 1, 2, 524, "", 0 },

  { 263, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S33/Value",
    offsetof(Parameters_Template_test, S33_Value), 31, 1, 2, 526, "", 0 },

  { 264,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_Template_test, _2x1_Value_i), 32, 2, 2, 528, "", 0 },

  { 265, "template_test/Main Subsystems/Control/LgV2/alpha^q/I/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_ks), 20, 9, 2, 530, "", 0
  },

  { 266,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_m), 23, 4, 2, 532, "", 0 },

  { 267,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_p5), 31, 1, 2, 534, "", 0 },

  { 268,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain",
    offsetof(Parameters_Template_test, _Gain_e), 31, 1, 2, 536, "", 0 },

  { 269,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value",
    offsetof(Parameters_Template_test, _2x2_Value), 23, 4, 2, 538, "", 0 },

  { 270,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_Template_test, _2x2_Value_j), 23, 4, 2, 540, "", 0 },

  { 271,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain",
    offsetof(Parameters_Template_test, _Gain_c), 31, 1, 2, 542, "", 0 },

  { 272,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value",
    offsetof(Parameters_Template_test, u_Value_pq), 31, 1, 2, 544, "", 0 },

  { 273,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_g), 31, 1, 2, 546, "", 0 },

  { 274,
    "template_test/Main Subsystems/Control/LgV2/Update laws/Integrator2/InitialCondition",
    offsetof(Parameters_Template_test, Integrator2_IC), 31, 1, 2, 548, "", 0 },

  { 275, "template_test/Main Subsystems/Control/LgV2/alpha^s/I/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_l), 20, 9, 2, 550, "", 0 },

  { 276,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value",
    offsetof(Parameters_Template_test, _2x1_Value_l), 32, 2, 2, 552, "", 0 },

  { 277,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_o0), 31, 1, 2, 554, "", 0 },

  { 278,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_Template_test, _2x1_Value_b), 32, 2, 2, 556, "", 0 },

  { 279,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_n), 31, 1, 2, 558, "", 0 },

  { 280,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_ap), 31, 1, 2, 560, "", 0 },

  { 281,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_a1), 31, 1, 2, 562, "", 0
  },

  { 282,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain",
    offsetof(Parameters_Template_test, u_Gain_m), 31, 1, 2, 564, "", 0 },

  { 283,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain",
    offsetof(Parameters_Template_test, _Gain_g), 31, 1, 2, 566, "", 0 },

  { 284,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain",
    offsetof(Parameters_Template_test, _Gain_o), 31, 1, 2, 568, "", 0 },

  { 285,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_n), 31, 1, 2, 570, "", 0 },

  { 286,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_da), 31, 1, 2, 572, "", 0
  },

  { 287,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_k), 31, 1, 2, 574, "", 0 },

  { 288,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value",
    offsetof(Parameters_Template_test, u_Value_dh), 31, 1, 2, 576, "", 0 },

  { 289,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_gt), 31, 1, 2, 578, "", 0
  },

  { 290, "template_test/Main Subsystems/Control/LgV2/V_1^q/Gain/Gain", offsetof
    (Parameters_Template_test, Gain_Gain_p1), 31, 1, 2, 580, "", 0 },

  { 291, "template_test/Main Subsystems/Control/LgV2/Update laws/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_os), 31, 1, 2, 582, "", 0 },

  { 292,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues",
    offsetof(Parameters_Template_test, f_1tou_1_XData), 77, 39, 2, 584, "", 0 },

  { 293,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table",
    offsetof(Parameters_Template_test, f_1tou_1_YData), 77, 39, 2, 586, "", 0 },

  { 294,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_e), 31, 1, 2, 588, "", 0 },

  { 295,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_fg), 31, 1, 2, 590, "", 0
  },

  { 296,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_h), 31, 1, 2, 592, "", 0 },

  { 297,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_l5), 31, 1, 2, 594, "", 0
  },

  { 298,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues",
    offsetof(Parameters_Template_test, f_2000391_XData), 78, 11, 2, 596, "", 0 },

  { 299,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table",
    offsetof(Parameters_Template_test, f_2000391_YData), 78, 11, 2, 598, "", 0 },

  { 300,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues",
    offsetof(Parameters_Template_test, f_2006731f_2000391_XData), 28, 3, 2, 600,
    "", 0 },

  { 301,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table",
    offsetof(Parameters_Template_test, f_2006731f_2000391_YData), 28, 3, 2, 602,
    "", 0 },

  { 302,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues",
    offsetof(Parameters_Template_test, f_2006731_XData), 79, 18, 2, 604, "", 0 },

  { 303,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table",
    offsetof(Parameters_Template_test, f_2006731_YData), 79, 18, 2, 606, "", 0 },

  { 304,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues",
    offsetof(Parameters_Template_test, f_3tou_3_XData), 77, 39, 2, 608, "", 0 },

  { 305,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table",
    offsetof(Parameters_Template_test, f_3tou_3_YData), 77, 39, 2, 610, "", 0 },

  { 306,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_dd), 31, 1, 2, 612, "", 0
  },

  { 307,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_kj), 31, 1, 2, 614, "", 0
  },

  { 308,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues",
    offsetof(Parameters_Template_test, f_400451_XData), 80, 15, 2, 616, "", 0 },

  { 309,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table",
    offsetof(Parameters_Template_test, f_400451_YData), 80, 15, 2, 618, "", 0 },

  { 310,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues",
    offsetof(Parameters_Template_test, f_400451_XData_h), 81, 13, 2, 620, "", 0
  },

  { 311,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table",
    offsetof(Parameters_Template_test, f_400451_YData_b), 81, 13, 2, 622, "", 0
  },

  { 312,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_Template_test, DeadZone001_Start), 31, 1, 2, 624, "", 0
  },

  { 313,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_Template_test, DeadZone001_End), 31, 1, 2, 626, "", 0 },

  { 314,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_dz), 31, 1, 2, 628, "", 0
  },

  { 315,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_i4), 31, 1, 2, 630, "", 0
  },

  { 316,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues",
    offsetof(Parameters_Template_test, f_50_XData), 82, 10, 2, 632, "", 0 },

  { 317,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table",
    offsetof(Parameters_Template_test, f_50_YData), 82, 10, 2, 634, "", 0 },

  { 318,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value",
    offsetof(Parameters_Template_test, f_50_Value), 31, 1, 2, 636, "", 0 },

  { 319,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues",
    offsetof(Parameters_Template_test, f_50_XData_h), 82, 10, 2, 638, "", 0 },

  { 320,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table",
    offsetof(Parameters_Template_test, f_50_YData_m), 82, 10, 2, 640, "", 0 },

  { 321,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value",
    offsetof(Parameters_Template_test, BT_power_limit_Value), 31, 1, 2, 642, "",
    0 },

  { 322,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value",
    offsetof(Parameters_Template_test, VSP_speeds_Value), 31, 1, 2, 644, "", 0 },

  { 323,
    "template_test/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_e), 31, 1, 2, 646, "",
    0 },

  { 324,
    "template_test/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_h), 31, 1, 2, 648, "",
    0 },

  { 325,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain",
    offsetof(Parameters_Template_test, QTMIn2Error_Gain), 31, 1, 2, 650, "", 0 },

  { 326,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain",
    offsetof(Parameters_Template_test, QTMIn9Residual_Gain), 31, 1, 2, 652, "",
    0 },

  { 327,
    "template_test/Main Subsystems/Plant/Thruster setting workaround/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_g), 31, 1, 2, 654, "",
    0 },

  { 328,
    "template_test/Main Subsystems/Plant/Thruster setting workaround/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_c), 31, 1, 2, 656, "",
    0 },

  { 329,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In1 FPS/Gain",
    offsetof(Parameters_Template_test, QTMIn1FPS_Gain), 31, 1, 2, 658, "", 0 },

  { 330, "template_test/Main Subsystems/Plant/saturation/Saturation/UpperLimit",
    offsetof(Parameters_Template_test, Saturation_UpperSat_i), 31, 1, 2, 660, "",
    0 },

  { 331, "template_test/Main Subsystems/Plant/saturation/Saturation/LowerLimit",
    offsetof(Parameters_Template_test, Saturation_LowerSat_n), 31, 1, 2, 662, "",
    0 },

  { 332, "template_test/Main Subsystems/Plant/saturation/Saturation1/UpperLimit",
    offsetof(Parameters_Template_test, Saturation1_UpperSat), 31, 1, 2, 664, "",
    0 },

  { 333, "template_test/Main Subsystems/Plant/saturation/Saturation1/LowerLimit",
    offsetof(Parameters_Template_test, Saturation1_LowerSat), 31, 1, 2, 666, "",
    0 },

  { 334, "template_test/Main Subsystems/Plant/saturation/Saturation2/UpperLimit",
    offsetof(Parameters_Template_test, Saturation2_UpperSat), 31, 1, 2, 668, "",
    0 },

  { 335, "template_test/Main Subsystems/Plant/saturation/Saturation2/LowerLimit",
    offsetof(Parameters_Template_test, Saturation2_LowerSat), 31, 1, 2, 670, "",
    0 },

  { 336, "template_test/Main Subsystems/Plant/saturation/plant tau_surge/Gain",
    offsetof(Parameters_Template_test, planttau_surge_Gain), 31, 1, 2, 672, "",
    0 },

  { 337, "template_test/Main Subsystems/Plant/saturation/plant tau_sway/Gain",
    offsetof(Parameters_Template_test, planttau_sway_Gain), 31, 1, 2, 674, "", 0
  },

  { 338, "template_test/Main Subsystems/Plant/saturation/plant tau_yaw/Gain",
    offsetof(Parameters_Template_test, planttau_yaw_Gain), 31, 1, 2, 676, "", 0
  },

  { 339,
    "template_test/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain",
    offsetof(Parameters_Template_test, BatteryBowThruster_Gain), 31, 1, 2, 678,
    "", 0 },

  { 340, "template_test/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain",
    offsetof(Parameters_Template_test, BatteryMain_Gain), 31, 1, 2, 680, "", 0 },

  { 341, "template_test/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain",
    offsetof(Parameters_Template_test, BatteryServo_Gain), 31, 1, 2, 682, "", 0
  },

  { 342, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_Yaw [deg]/Gain",
    offsetof(Parameters_Template_test, CSE1_Yawdeg_Gain), 31, 1, 2, 684, "", 0 },

  { 343, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_x [m]/Gain", offsetof
    (Parameters_Template_test, CSE1_xm_Gain), 31, 1, 2, 686, "", 0 },

  { 344, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_y [m]/Gain", offsetof
    (Parameters_Template_test, CSE1_ym_Gain), 31, 1, 2, 688, "", 0 },

  { 345, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain",
    offsetof(Parameters_Template_test, CSE1_rdegs_Gain), 31, 1, 2, 690, "", 0 },

  { 346, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain",
    offsetof(Parameters_Template_test, CSE1_ums_Gain), 31, 1, 2, 692, "", 0 },

  { 347, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain",
    offsetof(Parameters_Template_test, CSE1_vms_Gain), 31, 1, 2, 694, "", 0 },

  { 348, "template_test/Outputs to LabVIEW/Naviagtion/QS_Yaw [deg]/Gain",
    offsetof(Parameters_Template_test, QS_Yawdeg_Gain), 31, 1, 2, 696, "", 0 },

  { 349, "template_test/Outputs to LabVIEW/Naviagtion/QS_x [m]/Gain", offsetof
    (Parameters_Template_test, QS_xm_Gain), 31, 1, 2, 698, "", 0 },

  { 350, "template_test/Outputs to LabVIEW/Naviagtion/QS_y [m]/Gain", offsetof
    (Parameters_Template_test, QS_ym_Gain), 31, 1, 2, 700, "", 0 },

  { 351, "template_test/Outputs to LabVIEW/Naviagtion/LS_Yaw [deg]/Gain",
    offsetof(Parameters_Template_test, LS_Yawdeg_Gain), 31, 1, 2, 702, "", 0 },

  { 352, "template_test/Outputs to LabVIEW/Naviagtion/LS_x [m]/Gain", offsetof
    (Parameters_Template_test, LS_xm_Gain), 31, 1, 2, 704, "", 0 },

  { 353, "template_test/Outputs to LabVIEW/Naviagtion/LS_y [m]/Gain", offsetof
    (Parameters_Template_test, LS_ym_Gain), 31, 1, 2, 706, "", 0 },

  { 354, "template_test/Outputs to LabVIEW/Plant/plant BT power/Gain", offsetof
    (Parameters_Template_test, plantBTpower_Gain), 31, 1, 2, 708, "", 0 },

  { 355, "template_test/Outputs to LabVIEW/Plant/plant VSP speed/Gain", offsetof
    (Parameters_Template_test, plantVSPspeed_Gain), 31, 1, 2, 710, "", 0 },

  { 356, "template_test/Outputs to LabVIEW/Plant/plant u_1/Gain", offsetof
    (Parameters_Template_test, plantu_1_Gain), 31, 1, 2, 712, "", 0 },

  { 357, "template_test/Outputs to LabVIEW/Plant/plant u_2/Gain", offsetof
    (Parameters_Template_test, plantu_2_Gain), 31, 1, 2, 714, "", 0 },

  { 358, "template_test/Outputs to LabVIEW/Plant/plant u_3/Gain", offsetof
    (Parameters_Template_test, plantu_3_Gain), 31, 1, 2, 716, "", 0 },

  { 359, "template_test/Outputs to LabVIEW/Plant/plant u_4/Gain", offsetof
    (Parameters_Template_test, plantu_4_Gain), 31, 1, 2, 718, "", 0 },

  { 360, "template_test/Outputs to LabVIEW/Plant/plant u_5/Gain", offsetof
    (Parameters_Template_test, plantu_5_Gain), 31, 1, 2, 720, "", 0 },

  { 361, "template_test/Outputs to LabVIEW/Visualization/eta_psi [rad]/Gain",
    offsetof(Parameters_Template_test, eta_psirad_Gain), 31, 1, 2, 722, "", 0 },

  { 362, "template_test/Outputs to LabVIEW/Visualization/eta_psid [rad]/Gain",
    offsetof(Parameters_Template_test, eta_psidrad_Gain), 31, 1, 2, 724, "", 0 },

  { 363, "template_test/Outputs to LabVIEW/Visualization/eta_x [m]/Gain",
    offsetof(Parameters_Template_test, eta_xm_Gain), 31, 1, 2, 726, "", 0 },

  { 364, "template_test/Outputs to LabVIEW/Visualization/eta_xd [m]/Gain",
    offsetof(Parameters_Template_test, eta_xdm_Gain), 31, 1, 2, 728, "", 0 },

  { 365, "template_test/Outputs to LabVIEW/Visualization/eta_y [m]/Gain",
    offsetof(Parameters_Template_test, eta_ym_Gain), 31, 1, 2, 730, "", 0 },

  { 366, "template_test/Outputs to LabVIEW/Visualization/eta_yd [m]/Gain",
    offsetof(Parameters_Template_test, eta_ydm_Gain), 31, 1, 2, 732, "", 0 },

  { 367, "template_test/Outputs to LabVIEW/Visualization/psi_los [rad]/Gain",
    offsetof(Parameters_Template_test, psi_losrad_Gain), 31, 1, 2, 734, "", 0 },

  { 368, "template_test/Outputs to LabVIEW/Visualization/psi_plot/Gain",
    offsetof(Parameters_Template_test, psi_plot_Gain), 31, 1, 2, 736, "", 0 },

  { 369, "template_test/Outputs to LabVIEW/Visualization/q_x [m]/Gain", offsetof
    (Parameters_Template_test, q_xm_Gain), 31, 1, 2, 738, "", 0 },

  { 370, "template_test/Outputs to LabVIEW/Visualization/q_y [m]/Gain", offsetof
    (Parameters_Template_test, q_ym_Gain), 31, 1, 2, 740, "", 0 },

  { 371, "template_test/Outputs to LabVIEW/Visualization/x_plot/Gain", offsetof
    (Parameters_Template_test, x_plot_Gain), 31, 1, 2, 742, "", 0 },

  { 372, "template_test/Outputs to LabVIEW/Visualization/y_plot/Gain", offsetof
    (Parameters_Template_test, y_plot_Gain), 31, 1, 2, 744, "", 0 },

  { 373,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain",
    offsetof(Parameters_Template_test, R12_Gain), 31, 1, 2, 746, "", 0 },

  { 374,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain",
    offsetof(Parameters_Template_test, R22_Gain), 31, 1, 2, 748, "", 0 },

  { 375,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value",
    offsetof(Parameters_Template_test, _Value_f), 31, 1, 2, 750, "", 0 },

  { 376,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain",
    offsetof(Parameters_Template_test, S12_Gain_i), 31, 1, 2, 752, "", 0 },

  { 377,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value",
    offsetof(Parameters_Template_test, _Value_o), 31, 1, 2, 754, "", 0 },

  { 378,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain",
    offsetof(Parameters_Template_test, S12_Gain_f), 31, 1, 2, 756, "", 0 },

  { 379,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain",
    offsetof(Parameters_Template_test, BT_D_Gain1_Gain), 31, 1, 2, 758, "", 0 },

  { 380,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value",
    offsetof(Parameters_Template_test, BT_Power_Offset1_Value), 31, 1, 2, 760,
    "", 0 },

  { 381,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain",
    offsetof(Parameters_Template_test, BT_D_Gain2_Gain), 31, 1, 2, 762, "", 0 },

  { 382,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain",
    offsetof(Parameters_Template_test, BT_L_Gain1_Gain), 31, 1, 2, 764, "", 0 },

  { 383,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain",
    offsetof(Parameters_Template_test, BT_L_Gain2_Gain), 31, 1, 2, 766, "", 0 },

  { 384,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value",
    offsetof(Parameters_Template_test, BT_Power_Offset2_Value), 31, 1, 2, 768,
    "", 0 },

  { 385,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value",
    offsetof(Parameters_Template_test, BT_Power_Offset3_Value), 31, 1, 2, 770,
    "", 0 },

  { 386,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value",
    offsetof(Parameters_Template_test, Constant_Value_ahu), 31, 1, 2, 772, "", 0
  },

  { 387,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value",
    offsetof(Parameters_Template_test, Constant1_Value_j), 31, 1, 2, 774, "", 0
  },

  { 388,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain",
    offsetof(Parameters_Template_test, Neg_Gain), 31, 1, 2, 776, "", 0 },

  { 389,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain",
    offsetof(Parameters_Template_test, x_Gain), 31, 1, 2, 778, "", 0 },

  { 390,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain",
    offsetof(Parameters_Template_test, y_Gain), 31, 1, 2, 780, "", 0 },

  { 391,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_Template_test, Servo1_RowIdx), 33, 3, 2, 782, "", 0 },

  { 392,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_Template_test, Servo1_ColIdx), 33, 3, 2, 784, "", 0 },

  { 393,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table",
    offsetof(Parameters_Template_test, Servo1_Table), 20, 9, 2, 786, "", 0 },

  { 394,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_Template_test, Servo2_RowIdx), 33, 3, 2, 788, "", 0 },

  { 395,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_Template_test, Servo2_ColIdx), 33, 3, 2, 790, "", 0 },

  { 396,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table",
    offsetof(Parameters_Template_test, Servo2_Table), 20, 9, 2, 792, "", 0 },

  { 397,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_Template_test, Servo3_RowIdx), 33, 3, 2, 794, "", 0 },

  { 398,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_Template_test, Servo3_ColIdx), 33, 3, 2, 796, "", 0 },

  { 399,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table",
    offsetof(Parameters_Template_test, Servo3_Table), 20, 9, 2, 798, "", 0 },

  { 400,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_Template_test, Servo4_RowIdx), 33, 3, 2, 800, "", 0 },

  { 401,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_Template_test, Servo4_ColIdx), 33, 3, 2, 802, "", 0 },

  { 402,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table",
    offsetof(Parameters_Template_test, Servo4_Table), 20, 9, 2, 804, "", 0 },

  { 403,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_Template_test, VPS_Speed_Gain_Gain), 31, 1, 2, 806, "",
    0 },

  { 404,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_Template_test, VPS_Power_Offset_Value), 31, 1, 2, 808,
    "", 0 },

  { 405,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain",
    offsetof(Parameters_Template_test, VSPSPort_Gain), 31, 1, 2, 810, "", 0 },

  { 406,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_Template_test, VSPSStarboard_Gain), 31, 1, 2, 812, "", 0
  },

  { 407,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_Template_test, R31_Value_a), 31, 1, 2, 814, "", 0 },

  { 408,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_Template_test, R32_Value_h), 31, 1, 2, 816, "", 0 },

  { 409,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_Template_test, R13_Value_f), 31, 1, 2, 818, "", 0 },

  { 410,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_Template_test, R23_Value_b), 31, 1, 2, 820, "", 0 },

  { 411,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_Template_test, R33_Value_l), 31, 1, 2, 822, "", 0 },

  { 412,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_Template_test, Gain1_Gain_nz), 38, 1, 2, 824, "", 0 },

  { 413,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_b), 38, 1, 2, 826, "", 0 },

  { 414,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_Template_test, Gain_Gain_ea), 38, 1, 2, 828, "", 0 },

  { 415,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_Template_test, Gain1_Gain_f), 38, 1, 2, 830, "", 0 },
};

static int NI_ParamListSize = 416;
static int NI_ParamDimList[] = {
  1, 1,                                /* template_test/Inputs from LabVIEW/Control Input Selector/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Control Mode Selector/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Enable CSE1/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/12/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/13/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/21/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/23/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/31/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/32/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d_Surge/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d_Sway/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_d_Yaw/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/12/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/13/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/21/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/23/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/31/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/32/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i_Surge/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i_Sway/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_i_Yaw/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/12/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/13/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/21/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/23/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/31/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/32/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p_Surge/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p_Sway/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/K_p_Yaw/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/Reset integrator/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/ y_d [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/psi_d [deg]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/x_d [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q/12/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q/21/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q_Surge/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q_Sway/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial q_x/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial q_y/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial s/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/12/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/13/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/21/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/23/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/31/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/32/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d_Surge/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d_Sway/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d_Yaw/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/12/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/13/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/21/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/23/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/31/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/32/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i_Surge/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i_Sway/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i_Yaw/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/12/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/13/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/21/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/23/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/31/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/32/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p_Surge/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p_Sway/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p_Yaw/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/kappa_1/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/lambda_q/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Reset omega_q/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Reset q/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/LOS LgV backstepping II/Reset s/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Delta [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Path Selector  [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/my [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/u_d [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/x_dmax [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/x_dmin [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/y_dmax [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/y_dmin [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Ellipse/k [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Ellipse/origin_x [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Ellipse/origo_y [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/L2 [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value */
  1, 1,                                /* template_test/Inputs from LabVIEW/PlayStation3/R2 [-]/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value */
  1, 1,                                /* template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain */
  19, 1,                               /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues */
  19, 1,                               /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain */
  21, 1,                               /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues */
  21, 1,                               /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain */
  19, 1,                               /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues */
  19, 1,                               /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain */
  17, 1,                               /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues */
  17, 1,                               /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain */
  1, 7,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues */
  1, 7,                                /* template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/DP control/Integrator/InitialCondition */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain */
  3, 3,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/Constant1/Value */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/R(psi)/R31/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/R(psi)/-1/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/R(psi)/R32/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/R(psi)/R13/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/R(psi)/R23/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/R(psi)/R33/Value */
  3, 1,                                /* template_test/Main Subsystems/Control/LgV2/zeta/Integrator/InitialCondition */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/Control law/1/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/Control law/4/Gain */
  3, 3,                                /* template_test/Main Subsystems/Control/LgV2/alpha/I/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain */
  2, 1,                                /* template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/0_2x1/Value */
  2, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain */
  3, 3,                                /* template_test/Main Subsystems/Control/LgV2/sigma/I/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S11/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/R31/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S22/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S32/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S13/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S23/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S33/Value */
  2, 1,                                /* template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  3, 3,                                /* template_test/Main Subsystems/Control/LgV2/alpha^q/I/Constant/Value */
  2, 2,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain */
  2, 2,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value */
  2, 2,                                /* template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/Update laws/Integrator2/InitialCondition */
  3, 3,                                /* template_test/Main Subsystems/Control/LgV2/alpha^s/I/Constant/Value */
  2, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain */
  2, 1,                                /* template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/V_1^q/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/LgV2/Update laws/Gain/Gain */
  1, 39,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues */
  1, 39,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues */
  11, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table */
  3, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues */
  3, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table */
  18, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues */
  18, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table */
  1, 39,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues */
  1, 39,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues */
  15, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table */
  13, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues */
  13, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues */
  10, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value */
  10, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues */
  10, 1,                               /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/Thruster setting workaround/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Plant/Thruster setting workaround/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Naviagation/Input from SIT/QTM In1 FPS/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/Saturation/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/Saturation/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/Saturation1/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/Saturation1/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/Saturation2/UpperLimit */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/Saturation2/LowerLimit */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/plant tau_surge/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/plant tau_sway/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/saturation/plant tau_yaw/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/CSE1_Yaw [deg]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/CSE1_x [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/CSE1_y [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/QS_Yaw [deg]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/QS_x [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/QS_y [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/LS_Yaw [deg]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/LS_x [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Naviagtion/LS_y [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Plant/plant BT power/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Plant/plant VSP speed/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Plant/plant u_1/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Plant/plant u_2/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Plant/plant u_3/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Plant/plant u_4/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Plant/plant u_5/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/eta_psi [rad]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/eta_psid [rad]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/eta_x [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/eta_xd [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/eta_y [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/eta_yd [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/psi_los [rad]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/psi_plot/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/q_x [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/q_y [m]/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/x_plot/Gain */
  1, 1,                                /* template_test/Outputs to LabVIEW/Visualization/y_plot/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value */
  1, 1,                                /* template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 612;
static NI_Signal NI_SigList[] = {
  { 0, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_d/[3x3]", 0, "",
    offsetof(BlockIO_Template_test, ux3), BLOCKIO_SIG, 20, 9, 2, 0, 0 },

  { 1, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_i/[3x3]", 0, "",
    offsetof(BlockIO_Template_test, ux3_g), BLOCKIO_SIG, 20, 9, 2, 2, 0 },

  { 2, "template_test/Inputs from LabVIEW/Dynamic Positioning/K_p/[3x3]", 0, "",
    offsetof(BlockIO_Template_test, ux3_f), BLOCKIO_SIG, 20, 9, 2, 4, 0 },

  { 3, "template_test/Inputs from LabVIEW/Dynamic Positioning/Reset integrator",
    0, "", offsetof(BlockIO_Template_test, Resetintegrator), BLOCKIO_SIG, 0, 1,
    2, 6, 0 },

  { 4,
    "template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_Template_test, Gain1), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q/[2x2]",
    0, "", offsetof(BlockIO_Template_test, ux2), BLOCKIO_SIG, 23, 4, 2, 10, 0 },

  { 6, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial q_x",
    0, "", offsetof(BlockIO_Template_test, Initialq_x), BLOCKIO_SIG, 0, 1, 2, 12,
    0 },

  { 7, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial q_y",
    0, "", offsetof(BlockIO_Template_test, Initialq_y), BLOCKIO_SIG, 0, 1, 2, 14,
    0 },

  { 8, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/Initial s", 0,
    "", offsetof(BlockIO_Template_test, Initials), BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d/[3x3]", 0,
    "", offsetof(BlockIO_Template_test, ux3_n), BLOCKIO_SIG, 20, 9, 2, 18, 0 },

  { 10, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i/[3x3]", 0,
    "", offsetof(BlockIO_Template_test, ux3_d), BLOCKIO_SIG, 20, 9, 2, 20, 0 },

  { 11, "template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p/[3x3]", 0,
    "", offsetof(BlockIO_Template_test, ux3_b), BLOCKIO_SIG, 20, 9, 2, 22, 0 },

  { 12, "template_test/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]",
    0, "", offsetof(BlockIO_Template_test, Initialpsirad), BLOCKIO_SIG, 0, 1, 2,
    24, 0 },

  { 13, "template_test/Inputs from LabVIEW/Linear Simulator/Initial x [m]", 0,
    "", offsetof(BlockIO_Template_test, Initialxm), BLOCKIO_SIG, 0, 1, 2, 26, 0
  },

  { 14, "template_test/Inputs from LabVIEW/Linear Simulator/Initial y [m]", 0,
    "", offsetof(BlockIO_Template_test, Initialym), BLOCKIO_SIG, 0, 1, 2, 28, 0
  },

  { 15, "template_test/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]",
    0, "", offsetof(BlockIO_Template_test, Initialrrads), BLOCKIO_SIG, 0, 1, 2,
    30, 0 },

  { 16, "template_test/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]", 0,
    "", offsetof(BlockIO_Template_test, Initialums), BLOCKIO_SIG, 0, 1, 2, 32, 0
  },

  { 17, "template_test/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]", 0,
    "", offsetof(BlockIO_Template_test, Initialvms), BLOCKIO_SIG, 0, 1, 2, 34, 0
  },

  { 18, "template_test/Inputs from LabVIEW/PlayStation3/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_Template_test,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "template_test/Inputs from LabVIEW/PlayStation3/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_Template_test,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "template_test/Inputs from LabVIEW/PlayStation3/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_Template_test,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 40, 0 },

  { 21, "template_test/Inputs from LabVIEW/PlayStation3/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_Template_test,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 42, 0 },

  { 22,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1",
    0, "", offsetof(BlockIO_Template_test, l_x1), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { 23,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2",
    0, "", offsetof(BlockIO_Template_test, l_x2), BLOCKIO_SIG, 0, 1, 2, 46, 0 },

  { 24,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2",
    0, "", offsetof(BlockIO_Template_test, l_y2), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/3x5",
    0, "", offsetof(BlockIO_Template_test, x5), BLOCKIO_SIG, 26, 15, 2, 50, 0 },

  { 26,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r",
    0, "", offsetof(BlockIO_Template_test, N_r), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v",
    0, "", offsetof(BlockIO_Template_test, N_v), BLOCKIO_SIG, 0, 1, 2, 54, 0 },

  { 28,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u",
    0, "", offsetof(BlockIO_Template_test, X_u), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v",
    0, "", offsetof(BlockIO_Template_test, Y_v), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr",
    0, "", offsetof(BlockIO_Template_test, Y_vr), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Linear Dampning matrix",
    0, "", offsetof(BlockIO_Template_test, LinearDampningmatrix), BLOCKIO_SIG,
    20, 9, 2, 62, 0 },

  { 32,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_11",
    0, "", offsetof(BlockIO_Template_test, M_11), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_22",
    0, "", offsetof(BlockIO_Template_test, M_22), BLOCKIO_SIG, 0, 1, 2, 66, 0 },

  { 34,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m x_g",
    0, "", offsetof(BlockIO_Template_test, mx_g), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_32",
    0, "", offsetof(BlockIO_Template_test, M_32), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_23",
    0, "", offsetof(BlockIO_Template_test, M_23), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_33",
    0, "", offsetof(BlockIO_Template_test, M_33), BLOCKIO_SIG, 0, 1, 2, 74, 0 },

  { 38,
    "template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/3x3",
    0, "", offsetof(BlockIO_Template_test, x3), BLOCKIO_SIG, 20, 9, 2, 76, 0 },

  { 39,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1",
    0, "", offsetof(BlockIO_Template_test, l_x1_i), BLOCKIO_SIG, 0, 1, 2, 78, 0
  },

  { 40,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2",
    0, "", offsetof(BlockIO_Template_test, l_y2_f), BLOCKIO_SIG, 0, 1, 2, 80, 0
  },

  { 41,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2",
    0, "", offsetof(BlockIO_Template_test, l_x2_o), BLOCKIO_SIG, 0, 1, 2, 82, 0
  },

  { 42,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/3x5",
    0, "", offsetof(BlockIO_Template_test, x5_b), BLOCKIO_SIG, 26, 15, 2, 84, 0
  },

  { 43, "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_1", 0,
    "u_1", offsetof(BlockIO_Template_test, u_1), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1",
    0, "", offsetof(BlockIO_Template_test, u_1tof_1), BLOCKIO_SIG, 0, 1, 2, 88,
    0 },

  { 45, "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_2", 0,
    "u_2", offsetof(BlockIO_Template_test, u_2), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2",
    0, "", offsetof(BlockIO_Template_test, u_2tof_2), BLOCKIO_SIG, 0, 1, 2, 92,
    0 },

  { 47, "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_3", 0,
    "u_3", offsetof(BlockIO_Template_test, u_3), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3",
    0, "", offsetof(BlockIO_Template_test, u_3tof_3), BLOCKIO_SIG, 0, 1, 2, 96,
    0 },

  { 49, "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_4", 0,
    "u_4", offsetof(BlockIO_Template_test, u_4), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4",
    0, "", offsetof(BlockIO_Template_test, u_4tof_4), BLOCKIO_SIG, 0, 1, 2, 100,
    0 },

  { 51, "template_test/Main Subsystems/Control/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_Template_test,
    BowThrusterdirection), BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52, "template_test/Main Subsystems/Control/PS3 u input control/PS3 u_5", 0,
    "u_5", offsetof(BlockIO_Template_test, u_5), BLOCKIO_SIG, 0, 1, 2, 104, 0 },

  { 53,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5",
    0, "", offsetof(BlockIO_Template_test, u_5tof_5), BLOCKIO_SIG, 0, 1, 2, 106,
    0 },

  { 54,
    "template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/Product",
    0, "", offsetof(BlockIO_Template_test, Product), BLOCKIO_SIG, 22, 3, 2, 108,
    0 },

  { 55, "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In", 0, "",
    offsetof(BlockIO_Template_test, QTMIn), BLOCKIO_SIG, 47, 9, 2, 110, 0 },

  { 56,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]",
    0, "", offsetof(BlockIO_Template_test, QTMIn3xcoordmm), BLOCKIO_SIG, 31, 1,
    2, 112, 0 },

  { 57, "template_test/Main Subsystems/Naviagation/Input from SIT/mm2m x", 0, "",
    offsetof(BlockIO_Template_test, mm2mx), BLOCKIO_SIG, 31, 1, 2, 114, 0 },

  { 58,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]",
    0, "", offsetof(BlockIO_Template_test, QTMIn4ycoordmm), BLOCKIO_SIG, 31, 1,
    2, 116, 0 },

  { 59, "template_test/Main Subsystems/Naviagation/Input from SIT/mm2m y", 0, "",
    offsetof(BlockIO_Template_test, mm2my), BLOCKIO_SIG, 31, 1, 2, 118, 0 },

  { 60,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]",
    0, "", offsetof(BlockIO_Template_test, QTMIn6yawdeg), BLOCKIO_SIG, 31, 1, 2,
    120, 0 },

  { 61, "template_test/Main Subsystems/Naviagation/Input from SIT/d2r yaw", 0,
    "", offsetof(BlockIO_Template_test, d2ryaw), BLOCKIO_SIG, 31, 1, 2, 122, 0 },

  { 62, "template_test/Main Subsystems/Naviagation/Navigation Switch/eta Switch",
    0, "", offsetof(BlockIO_Template_test, etaSwitch), BLOCKIO_SIG, 22, 3, 2,
    124, 0 },

  { 63, "template_test/Main Subsystems/Control/DP control/yaw angle", 0, "psi",
    offsetof(BlockIO_Template_test, psi), BLOCKIO_SIG, 0, 1, 2, 126, 0 },

  { 64,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation), BLOCKIO_SIG, 0, 1, 2,
    128, 0 },

  { 65,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_Template_test, Sign), BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain), BLOCKIO_SIG, 0, 1, 2, 132, 0 },

  { 67,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1), BLOCKIO_SIG, 0, 1, 2, 134, 0 },

  { 68,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction), BLOCKIO_SIG, 0, 1, 2,
    136, 0 },

  { 69,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum), BLOCKIO_SIG, 0, 1, 2, 138, 0 },

  { 70, "template_test/Main Subsystems/Control/DP control/Sum2", 0, "", offsetof
    (BlockIO_Template_test, Sum2), BLOCKIO_SIG, 22, 3, 2, 140, 0 },

  { 71,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_k), BLOCKIO_SIG, 0, 1, 2,
    142, 0 },

  { 72,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_Template_test, Sign_f), BLOCKIO_SIG, 0, 1, 2, 144, 0
  },

  { 73,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_k), BLOCKIO_SIG, 0, 1, 2, 146, 0
  },

  { 74,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_j), BLOCKIO_SIG, 0, 1, 2, 148, 0
  },

  { 75,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_a), BLOCKIO_SIG, 0, 1, 2,
    150, 0 },

  { 76,
    "template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_p), BLOCKIO_SIG, 0, 1, 2, 152, 0
  },

  { 77,
    "template_test/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_Template_test, Row1), BLOCKIO_SIG, 0, 1, 2, 154, 0 },

  { 78,
    "template_test/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_Template_test, Row2), BLOCKIO_SIG, 0, 1, 2, 156, 0 },

  { 79,
    "template_test/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_Template_test, Row3), BLOCKIO_SIG, 0, 1, 2, 158, 0 },

  { 80, "template_test/Main Subsystems/Control/DP control/Product", 0, "",
    offsetof(BlockIO_Template_test, Product_e), BLOCKIO_SIG, 22, 3, 2, 160, 0 },

  { 81, "template_test/Main Subsystems/Control/DP control/Integrator", 0, "",
    offsetof(BlockIO_Template_test, Integrator), BLOCKIO_SIG, 22, 3, 2, 162, 0 },

  { 82, "template_test/Main Subsystems/Control/DP control/Product1", 0, "",
    offsetof(BlockIO_Template_test, Product1), BLOCKIO_SIG, 22, 3, 2, 164, 0 },

  { 83, "template_test/Main Subsystems/Control/DP control/Sum3", 0, "", offsetof
    (BlockIO_Template_test, Sum3), BLOCKIO_SIG, 22, 3, 2, 166, 0 },

  { 84,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]",
    0, "", offsetof(BlockIO_Template_test, QTMIn8rolldeg), BLOCKIO_SIG, 31, 1, 2,
    168, 0 },

  { 85, "template_test/Main Subsystems/Naviagation/Input from SIT/d2r roll", 0,
    "", offsetof(BlockIO_Template_test, d2rroll), BLOCKIO_SIG, 31, 1, 2, 170, 0
  },

  { 86,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]",
    0, "", offsetof(BlockIO_Template_test, QTMIn7pitchdeg), BLOCKIO_SIG, 31, 1,
    2, 172, 0 },

  { 87, "template_test/Main Subsystems/Naviagation/Input from SIT/d2r pitch", 0,
    "", offsetof(BlockIO_Template_test, d2rpitch), BLOCKIO_SIG, 31, 1, 2, 174, 0
  },

  { 88,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_Template_test, sintheta), BLOCKIO_SIG, 22, 3, 2, 176,
    0 },

  { 89,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_Template_test, costheta), BLOCKIO_SIG, 22, 3, 2, 178,
    0 },

  { 90,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_Template_test, R11), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_Template_test, R21), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_Template_test, R31), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_Template_test, R12), BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_Template_test, R22), BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_Template_test, R32), BLOCKIO_SIG, 0, 1, 2, 190, 0 },

  { 96,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_Template_test, R13), BLOCKIO_SIG, 0, 1, 2, 192, 0 },

  { 97,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_Template_test, R23), BLOCKIO_SIG, 0, 1, 2, 194, 0 },

  { 98,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_Template_test, R33), BLOCKIO_SIG, 0, 1, 2, 196, 0 },

  { 99,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_Template_test, Reshape9x13x3), BLOCKIO_SIG, 20, 9, 2,
    198, 0 },

  { 100,
    "template_test/Main Subsystems/Naviagation/Input from SIT/Matrix Concatenate2",
    0, "", offsetof(BlockIO_Template_test, MatrixConcatenate2), BLOCKIO_SIG, 51,
    36, 2, 200, 0 },

  { 101,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]",
    0, "", offsetof(BlockIO_Template_test, QTMIn5zcoordmm), BLOCKIO_SIG, 31, 1,
    2, 202, 0 },

  { 102, "template_test/Main Subsystems/Naviagation/Input from SIT/mm2m z", 0,
    "", offsetof(BlockIO_Template_test, mm2mz), BLOCKIO_SIG, 31, 1, 2, 204, 0 },

  { 103, "template_test/Main Subsystems/Naviagation/Input from SIT/Derivative",
    0, "", offsetof(BlockIO_Template_test, Derivative), BLOCKIO_SIG, 34, 6, 2,
    206, 0 },

  { 104, "template_test/Main Subsystems/Naviagation/Input from SIT/Product", 0,
    "", offsetof(BlockIO_Template_test, Product_a), BLOCKIO_SIG, 34, 6, 2, 208,
    0 },

  { 105, "template_test/Main Subsystems/Naviagation/Navigation Switch/nu Switch",
    0, "", offsetof(BlockIO_Template_test, nuSwitch), BLOCKIO_SIG, 22, 3, 2, 210,
    0 },

  { 106, "template_test/Main Subsystems/Control/DP control/Product2", 0, "",
    offsetof(BlockIO_Template_test, Product2), BLOCKIO_SIG, 22, 3, 2, 212, 0 },

  { 107, "template_test/Main Subsystems/Control/DP control/Sum1", 0, "",
    offsetof(BlockIO_Template_test, Sum1_b), BLOCKIO_SIG, 22, 3, 2, 214, 0 },

  { 108, "template_test/Main Subsystems/Control/LgV2/R(psi)/R11", 0, "",
    offsetof(BlockIO_Template_test, R11_e), BLOCKIO_SIG, 0, 1, 2, 216, 0 },

  { 109, "template_test/Main Subsystems/Control/LgV2/R(psi)/R21", 0, "",
    offsetof(BlockIO_Template_test, R21_a), BLOCKIO_SIG, 0, 1, 2, 218, 0 },

  { 110, "template_test/Main Subsystems/Control/LgV2/R(psi)/R12", 0, "",
    offsetof(BlockIO_Template_test, R12_f), BLOCKIO_SIG, 0, 1, 2, 220, 0 },

  { 111, "template_test/Main Subsystems/Control/LgV2/R(psi)/-1", 0, "", offsetof
    (BlockIO_Template_test, u), BLOCKIO_SIG, 0, 1, 2, 222, 0 },

  { 112, "template_test/Main Subsystems/Control/LgV2/R(psi)/R22", 0, "",
    offsetof(BlockIO_Template_test, R22_i), BLOCKIO_SIG, 0, 1, 2, 224, 0 },

  { 113, "template_test/Main Subsystems/Control/LgV2/R(psi)/R(psi)", 0, "",
    offsetof(BlockIO_Template_test, Rpsi), BLOCKIO_SIG, 20, 9, 2, 226, 0 },

  { 114, "template_test/Main Subsystems/Control/LgV2/R^T/Math Function", 0, "",
    offsetof(BlockIO_Template_test, MathFunction_n), BLOCKIO_SIG, 20, 9, 2, 228,
    0 },

  { 115, "template_test/Main Subsystems/Control/LgV2/zeta/Integrator", 0, "",
    offsetof(BlockIO_Template_test, Integrator_b), BLOCKIO_SIG, 28, 3, 2, 230, 0
  },

  { 116, "template_test/Main Subsystems/Control/LgV2/Control law/Product", 0, "",
    offsetof(BlockIO_Template_test, Product_l), BLOCKIO_SIG, 28, 3, 2, 232, 0 },

  { 117, "template_test/Main Subsystems/Control/LgV2/Control law/4", 0, "",
    offsetof(BlockIO_Template_test, u_a), BLOCKIO_SIG, 0, 1, 2, 234, 0 },

  { 118, "template_test/Main Subsystems/Control/LgV2/Control law/Divide", 0, "",
    offsetof(BlockIO_Template_test, Divide), BLOCKIO_SIG, 0, 1, 2, 236, 0 },

  { 119, "template_test/Main Subsystems/Control/LgV2/Control law/Add1", 0, "",
    offsetof(BlockIO_Template_test, Add1), BLOCKIO_SIG, 20, 9, 2, 238, 0 },

  { 120, "template_test/Main Subsystems/Control/LgV2/alpha/Product", 0, "",
    offsetof(BlockIO_Template_test, Product_k), BLOCKIO_SIG, 20, 9, 2, 240, 0 },

  { 121, "template_test/Main Subsystems/Control/LgV2/alpha/Subtract", 0, "",
    offsetof(BlockIO_Template_test, Subtract), BLOCKIO_SIG, 20, 9, 2, 242, 0 },

  { 122,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_o), BLOCKIO_SIG, 0, 1, 2,
    244, 0 },

  { 123,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_Template_test, Sign_a), BLOCKIO_SIG, 0, 1, 2, 246, 0
  },

  { 124,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_c), BLOCKIO_SIG, 0, 1, 2, 248, 0
  },

  { 125,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_j5), BLOCKIO_SIG, 0, 1, 2, 250,
    0 },

  { 126,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_m), BLOCKIO_SIG, 0, 1, 2,
    252, 0 },

  { 127,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_d), BLOCKIO_SIG, 0, 1, 2, 254, 0
  },

  { 128, "template_test/Main Subsystems/Control/LgV2/Update laws/Integrator", 0,
    "", offsetof(BlockIO_Template_test, Integrator_n), BLOCKIO_SIG, 25, 2, 2,
    256, 0 },

  { 129,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/x_2 - x_1",
    0, "", offsetof(BlockIO_Template_test, x_2x_1), BLOCKIO_SIG, 0, 1, 2, 258, 0
  },

  { 130,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/y_2 - y_1",
    0, "", offsetof(BlockIO_Template_test, y_2y_1), BLOCKIO_SIG, 0, 1, 2, 260, 0
  },

  { 131,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product",
    0, "", offsetof(BlockIO_Template_test, Product_h), BLOCKIO_SIG, 25, 2, 2,
    262, 0 },

  { 132, "template_test/Main Subsystems/Control/LgV2/Update laws/Integrator1", 0,
    "", offsetof(BlockIO_Template_test, Integrator1), BLOCKIO_SIG, 0, 1, 2, 264,
    0 },

  { 133,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_i), BLOCKIO_SIG, 0, 1, 2,
    266, 0 },

  { 134,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/sin(s)",
    0, "", offsetof(BlockIO_Template_test, sins), BLOCKIO_SIG, 0, 1, 2, 268, 0 },

  { 135,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_eb), BLOCKIO_SIG, 0, 1, 2,
    270, 0 },

  { 136,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_b), BLOCKIO_SIG, 0, 1, 2, 272, 0
  },

  { 137,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/cos(s)",
    0, "", offsetof(BlockIO_Template_test, coss), BLOCKIO_SIG, 0, 1, 2, 274, 0 },

  { 138,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_n), BLOCKIO_SIG, 0, 1, 2,
    276, 0 },

  { 139,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Subract",
    0, "", offsetof(BlockIO_Template_test, Subract), BLOCKIO_SIG, 0, 1, 2, 278,
    0 },

  { 140,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_m), BLOCKIO_SIG, 25, 2, 2,
    280, 0 },

  { 141,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Add",
    0, "", offsetof(BlockIO_Template_test, Add), BLOCKIO_SIG, 25, 2, 2, 282, 0 },

  { 142,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/Trigonometric Function",
    0, "", offsetof(BlockIO_Template_test, TrigonometricFunction), BLOCKIO_SIG,
    0, 1, 2, 284, 0 },

  { 143,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_g), BLOCKIO_SIG, 0, 1, 2,
    286, 0 },

  { 144,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_Template_test, Sign_i), BLOCKIO_SIG, 0, 1, 2, 288, 0
  },

  { 145,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_d), BLOCKIO_SIG, 0, 1, 2, 290, 0
  },

  { 146,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_i), BLOCKIO_SIG, 0, 1, 2, 292, 0
  },

  { 147,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_j), BLOCKIO_SIG, 0, 1, 2,
    294, 0 },

  { 148,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_dn), BLOCKIO_SIG, 0, 1, 2, 296, 0
  },

  { 149,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_l), BLOCKIO_SIG, 0, 1, 2,
    298, 0 },

  { 150,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_Template_test, Sign_ik), BLOCKIO_SIG, 0, 1, 2, 300,
    0 },

  { 151,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_h), BLOCKIO_SIG, 0, 1, 2, 302, 0
  },

  { 152,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_c), BLOCKIO_SIG, 0, 1, 2, 304, 0
  },

  { 153,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_d), BLOCKIO_SIG, 0, 1, 2,
    306, 0 },

  { 154,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_f), BLOCKIO_SIG, 0, 1, 2, 308, 0
  },

  { 155,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_g), BLOCKIO_SIG, 23, 4,
    2, 310, 0 },

  { 156,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/x_2 - x_1",
    0, "", offsetof(BlockIO_Template_test, x_2x_1_k), BLOCKIO_SIG, 0, 1, 2, 312,
    0 },

  { 157,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s",
    0, "", offsetof(BlockIO_Template_test, x_2x_1s), BLOCKIO_SIG, 0, 1, 2, 314,
    0 },

  { 158,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s + x_1",
    0, "", offsetof(BlockIO_Template_test, x_2x_1sx_1), BLOCKIO_SIG, 0, 1, 2,
    316, 0 },

  { 159,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/y_2 - y_1",
    0, "", offsetof(BlockIO_Template_test, y_2y_1_b), BLOCKIO_SIG, 0, 1, 2, 318,
    0 },

  { 160,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s",
    0, "", offsetof(BlockIO_Template_test, y_2y_1s), BLOCKIO_SIG, 0, 1, 2, 320,
    0 },

  { 161,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s + y_1",
    0, "", offsetof(BlockIO_Template_test, y_2y_1sy_1), BLOCKIO_SIG, 0, 1, 2,
    322, 0 },

  { 162,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product",
    0, "", offsetof(BlockIO_Template_test, Product_ei), BLOCKIO_SIG, 25, 2, 2,
    324, 0 },

  { 163,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_g), BLOCKIO_SIG, 0, 1, 2,
    326, 0 },

  { 164,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/cos(s)",
    0, "", offsetof(BlockIO_Template_test, coss_h), BLOCKIO_SIG, 0, 1, 2, 328, 0
  },

  { 165,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_p), BLOCKIO_SIG, 0, 1, 2, 330,
    0 },

  { 166,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_b), BLOCKIO_SIG, 0, 1, 2, 332, 0
  },

  { 167,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/sin(s)",
    0, "", offsetof(BlockIO_Template_test, sins_l), BLOCKIO_SIG, 0, 1, 2, 334, 0
  },

  { 168,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_a), BLOCKIO_SIG, 0, 1, 2,
    336, 0 },

  { 169,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add1",
    0, "", offsetof(BlockIO_Template_test, Add1_k), BLOCKIO_SIG, 0, 1, 2, 338, 0
  },

  { 170,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Subract",
    0, "", offsetof(BlockIO_Template_test, Subract_o), BLOCKIO_SIG, 0, 1, 2, 340,
    0 },

  { 171,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_h), BLOCKIO_SIG, 25, 2, 2,
    342, 0 },

  { 172,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Add",
    0, "", offsetof(BlockIO_Template_test, Add_n), BLOCKIO_SIG, 25, 2, 2, 344, 0
  },

  { 173,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch",
    0, "", offsetof(BlockIO_Template_test, Switch), BLOCKIO_SIG, 0, 1, 2, 346, 0
  },

  { 174,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch2",
    0, "", offsetof(BlockIO_Template_test, Switch2), BLOCKIO_SIG, 0, 1, 2, 348,
    0 },

  { 175,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch",
    0, "", offsetof(BlockIO_Template_test, Switch_d), BLOCKIO_SIG, 0, 1, 2, 350,
    0 },

  { 176,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch2",
    0, "", offsetof(BlockIO_Template_test, Switch2_c), BLOCKIO_SIG, 0, 1, 2, 352,
    0 },

  { 177,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Subtract",
    0, "", offsetof(BlockIO_Template_test, Subtract_i), BLOCKIO_SIG, 25, 2, 2,
    354, 0 },

  { 178,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon",
    0, "", offsetof(BlockIO_Template_test, epsilon), BLOCKIO_SIG, 25, 2, 2, 356,
    0 },

  { 179,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector",
    0, "", offsetof(BlockIO_Template_test, MultiportSelector), BLOCKIO_SIG, 31,
    1, 2, 358, 0 },

  { 180,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Trigonometric Function",
    0, "", offsetof(BlockIO_Template_test, TrigonometricFunction_i), BLOCKIO_SIG,
    31, 1, 2, 360, 0 },

  { 181,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_m), BLOCKIO_SIG, 31, 1, 2,
    362, 0 },

  { 182,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_Template_test, Sign_m), BLOCKIO_SIG, 31, 1, 2, 364,
    0 },

  { 183,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_f), BLOCKIO_SIG, 31, 1, 2, 366,
    0 },

  { 184,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_n), BLOCKIO_SIG, 31, 1, 2, 368,
    0 },

  { 185,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_o), BLOCKIO_SIG, 31, 1,
    2, 370, 0 },

  { 186,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_d3), BLOCKIO_SIG, 31, 1, 2, 372,
    0 },

  { 187,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Subtract",
    0, "", offsetof(BlockIO_Template_test, Subtract_l), BLOCKIO_SIG, 0, 1, 2,
    374, 0 },

  { 188,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_oa), BLOCKIO_SIG, 0, 1, 2,
    376, 0 },

  { 189,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sign",
    0, "", offsetof(BlockIO_Template_test, Sign_j), BLOCKIO_SIG, 0, 1, 2, 378, 0
  },

  { 190,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_n), BLOCKIO_SIG, 0, 1, 2, 380, 0
  },

  { 191,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_a), BLOCKIO_SIG, 0, 1, 2, 382, 0
  },

  { 192,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_p), BLOCKIO_SIG, 0, 1, 2,
    384, 0 },

  { 193,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_pn), BLOCKIO_SIG, 0, 1, 2, 386, 0
  },

  { 194,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate",
    0, "", offsetof(BlockIO_Template_test, VectorConcatenate), BLOCKIO_SIG, 22,
    3, 2, 388, 0 },

  { 195, "template_test/Main Subsystems/Control/LgV2/z_1/Subtract", 0, "",
    offsetof(BlockIO_Template_test, Subtract_n), BLOCKIO_SIG, 22, 3, 2, 390, 0 },

  { 196,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_h), BLOCKIO_SIG, 0, 1, 2,
    392, 0 },

  { 197,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_Template_test, Sign_k), BLOCKIO_SIG, 0, 1, 2, 394, 0
  },

  { 198,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_p), BLOCKIO_SIG, 0, 1, 2, 396, 0
  },

  { 199,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_g), BLOCKIO_SIG, 0, 1, 2, 398, 0
  },

  { 200,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_pi), BLOCKIO_SIG, 0, 1,
    2, 400, 0 },

  { 201,
    "template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_i), BLOCKIO_SIG, 0, 1, 2, 402, 0
  },

  { 202, "template_test/Main Subsystems/Control/LgV2/z_1/Product", 0, "",
    offsetof(BlockIO_Template_test, Product_d), BLOCKIO_SIG, 22, 3, 2, 404, 0 },

  { 203, "template_test/Main Subsystems/Control/LgV2/alpha/Product1", 0, "",
    offsetof(BlockIO_Template_test, Product1_d), BLOCKIO_SIG, 22, 3, 2, 406, 0 },

  { 204,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qx",
    0, "", offsetof(BlockIO_Template_test, f_qx), BLOCKIO_SIG, 0, 1, 2, 408, 0 },

  { 205,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qy",
    0, "", offsetof(BlockIO_Template_test, f_qy), BLOCKIO_SIG, 0, 1, 2, 410, 0 },

  { 206,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_o), BLOCKIO_SIG, 25, 2, 2,
    412, 0 },

  { 207,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2), BLOCKIO_SIG, 0, 1, 2, 414, 0
  },

  { 208,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2), BLOCKIO_SIG, 31, 1, 2,
    416, 0 },

  { 209,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_g), BLOCKIO_SIG, 31, 1, 2, 418, 0
  },

  { 210,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_p), BLOCKIO_SIG, 31, 1, 2, 420,
    0 },

  { 211,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector1",
    0, "", offsetof(BlockIO_Template_test, MultiportSelector1), BLOCKIO_SIG, 29,
    2, 2, 422, 0 },

  { 212,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_i), BLOCKIO_SIG, 29, 2, 2,
    424, 0 },

  { 213,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1",
    0, "", offsetof(BlockIO_Template_test, u_b), BLOCKIO_SIG, 29, 2, 2, 426, 0 },

  { 214,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_Template_test, VectorConcatenate_p), BLOCKIO_SIG, 22,
    3, 2, 428, 0 },

  { 215,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product",
    0, "", offsetof(BlockIO_Template_test, Product_m), BLOCKIO_SIG, 32, 2, 2,
    430, 0 },

  { 216,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_h), BLOCKIO_SIG, 0, 1, 2,
    432, 0 },

  { 217,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/cos(s)",
    0, "", offsetof(BlockIO_Template_test, coss_c), BLOCKIO_SIG, 0, 1, 2, 434, 0
  },

  { 218,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_i), BLOCKIO_SIG, 0, 1, 2,
    436, 0 },

  { 219,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_ih), BLOCKIO_SIG, 0, 1, 2,
    438, 0 },

  { 220,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_nq), BLOCKIO_SIG, 0, 1, 2, 440,
    0 },

  { 221,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/sin(s)",
    0, "", offsetof(BlockIO_Template_test, sins_n), BLOCKIO_SIG, 0, 1, 2, 442, 0
  },

  { 222,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_di), BLOCKIO_SIG, 0, 1, 2,
    444, 0 },

  { 223,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1",
    0, "", offsetof(BlockIO_Template_test, Gain1_b), BLOCKIO_SIG, 0, 1, 2, 446,
    0 },

  { 224,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Subract",
    0, "", offsetof(BlockIO_Template_test, Subract_e), BLOCKIO_SIG, 0, 1, 2, 448,
    0 },

  { 225,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_nf), BLOCKIO_SIG, 25, 2, 2,
    450, 0 },

  { 226,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Add",
    0, "", offsetof(BlockIO_Template_test, Add_f), BLOCKIO_SIG, 32, 2, 2, 452, 0
  },

  { 227,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_Template_test, x_dsy_ds2), BLOCKIO_SIG, 31, 1, 2,
    454, 0 },

  { 228,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s^2 + y_d^s",
    0, "", offsetof(BlockIO_Template_test, x_ds2y_ds), BLOCKIO_SIG, 31, 1, 2,
    456, 0 },

  { 229,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s + y_d^s^2 ) - ( x_d^s^2 + y_d^s )",
    0, "", offsetof(BlockIO_Template_test, x_dsy_ds2x_ds2y_ds), BLOCKIO_SIG, 31,
    1, 2, 458, 0 },

  { 230,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2",
    0, "", offsetof(BlockIO_Template_test, x_ds2), BLOCKIO_SIG, 0, 1, 2, 460, 0
  },

  { 231,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( y_d^s )^2",
    0, "", offsetof(BlockIO_Template_test, y_ds2), BLOCKIO_SIG, 0, 1, 2, 462, 0
  },

  { 232,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2 + ( y_d^s )^2",
    0, "", offsetof(BlockIO_Template_test, x_ds2y_ds2), BLOCKIO_SIG, 0, 1, 2,
    464, 0 },

  { 233,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_k), BLOCKIO_SIG, 31, 1, 2, 466,
    0 },

  { 234,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2_p), BLOCKIO_SIG, 0, 1, 2, 468,
    0 },

  { 235,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2_b), BLOCKIO_SIG, 31, 1, 2,
    470, 0 },

  { 236,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_p), BLOCKIO_SIG, 31, 1, 2, 472, 0
  },

  { 237,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_d), BLOCKIO_SIG, 31, 1, 2, 474,
    0 },

  { 238,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_e), BLOCKIO_SIG, 23, 4,
    2, 476, 0 },

  { 239,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_aj), BLOCKIO_SIG, 25, 2, 2,
    478, 0 },

  { 240,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_i), BLOCKIO_SIG, 25, 2, 2,
    480, 0 },

  { 241,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Subtract1",
    0, "", offsetof(BlockIO_Template_test, Subtract1), BLOCKIO_SIG, 25, 2, 2,
    482, 0 },

  { 242,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector2",
    0, "", offsetof(BlockIO_Template_test, MultiportSelector2), BLOCKIO_SIG, 31,
    1, 2, 484, 0 },

  { 243,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_f), BLOCKIO_SIG, 31, 1, 2,
    486, 0 },

  { 244,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Subtract",
    0, "", offsetof(BlockIO_Template_test, Subtract_h), BLOCKIO_SIG, 31, 1, 2,
    488, 0 },

  { 245,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2_j), BLOCKIO_SIG, 31, 1, 2,
    490, 0 },

  { 246,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2_n), BLOCKIO_SIG, 0, 1, 2, 492,
    0 },

  { 247,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_i), BLOCKIO_SIG, 31, 1, 2, 494, 0
  },

  { 248,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/sqrt",
    0, "", offsetof(BlockIO_Template_test, sqrt_g), BLOCKIO_SIG, 31, 1, 2, 496,
    0 },

  { 249,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_dt), BLOCKIO_SIG, 31, 1, 2,
    498, 0 },

  { 250,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product",
    0, "", offsetof(BlockIO_Template_test, Product_b), BLOCKIO_SIG, 0, 1, 2, 500,
    0 },

  { 251,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Subract",
    0, "", offsetof(BlockIO_Template_test, Subract_eq), BLOCKIO_SIG, 0, 1, 2,
    502, 0 },

  { 252,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_e), BLOCKIO_SIG, 0, 1, 2,
    504, 0 },

  { 253,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Add",
    0, "", offsetof(BlockIO_Template_test, Add_e), BLOCKIO_SIG, 0, 1, 2, 506, 0
  },

  { 254,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_o), BLOCKIO_SIG, 0, 1, 2, 508,
    0 },

  { 255,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_ey), BLOCKIO_SIG, 0, 1, 2,
    510, 0 },

  { 256,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_b), BLOCKIO_SIG, 29, 2,
    2, 512, 0 },

  { 257,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_e), BLOCKIO_SIG, 29, 2, 2, 514,
    0 },

  { 258,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_bd), BLOCKIO_SIG, 0, 1, 2,
    516, 0 },

  { 259,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_a), BLOCKIO_SIG, 0, 1, 2, 518, 0
  },

  { 260,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Subtract",
    0, "", offsetof(BlockIO_Template_test, Subtract_d), BLOCKIO_SIG, 0, 1, 2,
    520, 0 },

  { 261,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_Template_test, VectorConcatenate_n), BLOCKIO_SIG, 28,
    3, 2, 522, 0 },

  { 262, "template_test/Main Subsystems/Control/LgV2/alpha/Add", 0, "", offsetof
    (BlockIO_Template_test, Add_l), BLOCKIO_SIG, 28, 3, 2, 524, 0 },

  { 263, "template_test/Main Subsystems/Control/LgV2/alpha/Product2", 0, "",
    offsetof(BlockIO_Template_test, Product2_d), BLOCKIO_SIG, 28, 3, 2, 526, 0 },

  { 264, "template_test/Main Subsystems/Control/LgV2/alpha/Sum", 0, "", offsetof
    (BlockIO_Template_test, Sum_e), BLOCKIO_SIG, 28, 3, 2, 528, 0 },

  { 265, "template_test/Main Subsystems/Control/LgV2/z_2/Subtract", 0, "",
    offsetof(BlockIO_Template_test, Subtract_o), BLOCKIO_SIG, 28, 3, 2, 530, 0 },

  { 266, "template_test/Main Subsystems/Control/LgV2/Control law/Product1", 0,
    "", offsetof(BlockIO_Template_test, Product1_k), BLOCKIO_SIG, 28, 3, 2, 532,
    0 },

  { 267, "template_test/Main Subsystems/Control/LgV2/Control law/Product2", 0,
    "", offsetof(BlockIO_Template_test, Product2_i4), BLOCKIO_SIG, 22, 3, 2, 534,
    0 },

  { 268, "template_test/Main Subsystems/Control/LgV2/sigma/Product1", 0, "",
    offsetof(BlockIO_Template_test, Product1_j), BLOCKIO_SIG, 20, 9, 2, 536, 0 },

  { 269, "template_test/Main Subsystems/Control/LgV2/sigma/Add3", 0, "",
    offsetof(BlockIO_Template_test, Add3), BLOCKIO_SIG, 20, 9, 2, 538, 0 },

  { 270, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12", 0, "",
    offsetof(BlockIO_Template_test, S12), BLOCKIO_SIG, 0, 1, 2, 540, 0 },

  { 271, "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S(r)", 0, "",
    offsetof(BlockIO_Template_test, Sr), BLOCKIO_SIG, 20, 9, 2, 542, 0 },

  { 272,
    "template_test/Main Subsystems/Control/LgV2/sigma/S^T/S^T/Math Function", 0,
    "", offsetof(BlockIO_Template_test, MathFunction_k), BLOCKIO_SIG, 20, 9, 2,
    544, 0 },

  { 273, "template_test/Main Subsystems/Control/LgV2/sigma/Product", 0, "",
    offsetof(BlockIO_Template_test, Product_c), BLOCKIO_SIG, 22, 3, 2, 546, 0 },

  { 274, "template_test/Main Subsystems/Control/LgV2/sigma/Add", 0, "", offsetof
    (BlockIO_Template_test, Add_a), BLOCKIO_SIG, 22, 3, 2, 548, 0 },

  { 275, "template_test/Main Subsystems/Control/LgV2/sigma/Product2", 0, "",
    offsetof(BlockIO_Template_test, Product2_n), BLOCKIO_SIG, 22, 3, 2, 550, 0 },

  { 276, "template_test/Main Subsystems/Control/LgV2/sigma/Add1", 0, "",
    offsetof(BlockIO_Template_test, Add1_a), BLOCKIO_SIG, 28, 3, 2, 552, 0 },

  { 277, "template_test/Main Subsystems/Control/LgV2/sigma/Product3", 0, "",
    offsetof(BlockIO_Template_test, Product3), BLOCKIO_SIG, 28, 3, 2, 554, 0 },

  { 278,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function",
    0, "", offsetof(BlockIO_Template_test, TrigonometricFunction_m), BLOCKIO_SIG,
    0, 1, 2, 556, 0 },

  { 279,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_Template_test, TrigonometricFunction1), BLOCKIO_SIG,
    0, 1, 2, 558, 0 },

  { 280,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/Derivative",
    0, "", offsetof(BlockIO_Template_test, Derivative_g), BLOCKIO_SIG, 0, 1, 2,
    560, 0 },

  { 281,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_kh), BLOCKIO_SIG, 25, 2, 2,
    562, 0 },

  { 282,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_Template_test, VectorConcatenate_nq), BLOCKIO_SIG,
    22, 3, 2, 564, 0 },

  { 283,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2_m), BLOCKIO_SIG, 31, 1, 2,
    566, 0 },

  { 284,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2_a), BLOCKIO_SIG, 0, 1, 2, 568,
    0 },

  { 285,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_pz), BLOCKIO_SIG, 31, 1, 2, 570,
    0 },

  { 286,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/sqrt",
    0, "", offsetof(BlockIO_Template_test, sqrt_ge), BLOCKIO_SIG, 31, 1, 2, 572,
    0 },

  { 287,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_a), BLOCKIO_SIG, 31, 1, 2, 574,
    0 },

  { 288,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_j), BLOCKIO_SIG, 0, 1, 2, 576,
    0 },

  { 289,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_kl), BLOCKIO_SIG, 31, 1, 2,
    578, 0 },

  { 290,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_Template_test, VectorConcatenate_b), BLOCKIO_SIG, 28,
    3, 2, 580, 0 },

  { 291, "template_test/Main Subsystems/Control/LgV2/sigma/Add2", 0, "",
    offsetof(BlockIO_Template_test, Add2), BLOCKIO_SIG, 28, 3, 2, 582, 0 },

  { 292, "template_test/Main Subsystems/Control/LgV2/sigma/Product4", 0, "",
    offsetof(BlockIO_Template_test, Product4), BLOCKIO_SIG, 28, 3, 2, 584, 0 },

  { 293, "template_test/Main Subsystems/Control/LgV2/sigma/Sum", 0, "", offsetof
    (BlockIO_Template_test, Sum_l), BLOCKIO_SIG, 28, 3, 2, 586, 0 },

  { 294, "template_test/Main Subsystems/Control/LgV2/Control law/Product4", 0,
    "", offsetof(BlockIO_Template_test, Product4_p), BLOCKIO_SIG, 28, 3, 2, 588,
    0 },

  { 295, "template_test/Main Subsystems/Control/LgV2/alpha^q/Product1", 0, "",
    offsetof(BlockIO_Template_test, Product1_mo), BLOCKIO_SIG, 20, 9, 2, 590, 0
  },

  { 296, "template_test/Main Subsystems/Control/LgV2/alpha^q/Add", 0, "",
    offsetof(BlockIO_Template_test, Add_e5), BLOCKIO_SIG, 20, 9, 2, 592, 0 },

  { 297,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Matrix Concatenate",
    0, "", offsetof(BlockIO_Template_test, MatrixConcatenate), BLOCKIO_SIG, 30,
    6, 2, 594, 0 },

  { 298, "template_test/Main Subsystems/Control/LgV2/alpha^q/Product3", 0, "",
    offsetof(BlockIO_Template_test, Product3_i), BLOCKIO_SIG, 30, 6, 2, 596, 0 },

  { 299,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_Template_test, TrigonometricFunction1_c),
    BLOCKIO_SIG, 0, 1, 2, 598, 0 },

  { 300,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_pg), BLOCKIO_SIG, 0, 1, 2, 600,
    0 },

  { 301,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_dm), BLOCKIO_SIG, 29, 2, 2,
    602, 0 },

  { 302,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function",
    0, "", offsetof(BlockIO_Template_test, TrigonometricFunction_k), BLOCKIO_SIG,
    0, 1, 2, 604, 0 },

  { 303,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_a), BLOCKIO_SIG, 29, 2, 2,
    606, 0 },

  { 304,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_Template_test, MatrixConcatenate_o), BLOCKIO_SIG, 23,
    4, 2, 608, 0 },

  { 305,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_me), BLOCKIO_SIG, 23, 4, 2,
    610, 0 },

  { 306,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_m5), BLOCKIO_SIG, 29, 2,
    2, 612, 0 },

  { 307,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_ho), BLOCKIO_SIG, 31, 1, 2,
    614, 0 },

  { 308,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_js), BLOCKIO_SIG, 32, 2,
    2, 616, 0 },

  { 309,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product3",
    0, "", offsetof(BlockIO_Template_test, Product3_o), BLOCKIO_SIG, 23, 4, 2,
    618, 0 },

  { 310,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product4",
    0, "", offsetof(BlockIO_Template_test, Product4_e), BLOCKIO_SIG, 23, 4, 2,
    620, 0 },

  { 311,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2",
    0, "", offsetof(BlockIO_Template_test, u_g), BLOCKIO_SIG, 23, 4, 2, 622, 0 },

  { 312,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2_e), BLOCKIO_SIG, 0, 1, 2, 624,
    0 },

  { 313,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2_bp), BLOCKIO_SIG, 31, 1, 2,
    626, 0 },

  { 314,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_c), BLOCKIO_SIG, 31, 1, 2, 628, 0
  },

  { 315,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/( )^2",
    0, "", offsetof(BlockIO_Template_test, u_h), BLOCKIO_SIG, 31, 1, 2, 630, 0 },

  { 316,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_et), BLOCKIO_SIG, 23, 4, 2,
    632, 0 },

  { 317,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_dz), BLOCKIO_SIG, 23, 4, 2,
    634, 0 },

  { 318,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide1",
    0, "", offsetof(BlockIO_Template_test, Divide1), BLOCKIO_SIG, 23, 4, 2, 636,
    0 },

  { 319,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Subtract",
    0, "", offsetof(BlockIO_Template_test, Subtract_d1), BLOCKIO_SIG, 23, 4, 2,
    638, 0 },

  { 320,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_ke), BLOCKIO_SIG, 23, 4,
    2, 640, 0 },

  { 321,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_oe), BLOCKIO_SIG, 29, 2, 2,
    642, 0 },

  { 322,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_b), BLOCKIO_SIG, 29, 2, 2,
    644, 0 },

  { 323,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_pv), BLOCKIO_SIG, 29, 2, 2, 646,
    0 },

  { 324,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_Template_test, MatrixConcatenate_l), BLOCKIO_SIG, 30,
    6, 2, 648, 0 },

  { 325,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_a4), BLOCKIO_SIG, 29, 2, 2,
    650, 0 },

  { 326,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2",
    0, "", offsetof(BlockIO_Template_test, u_bz), BLOCKIO_SIG, 29, 2, 2, 652, 0
  },

  { 327,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2_g), BLOCKIO_SIG, 0, 1, 2, 654,
    0 },

  { 328,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2_mi), BLOCKIO_SIG, 31, 1, 2,
    656, 0 },

  { 329,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_g5), BLOCKIO_SIG, 31, 1, 2, 658,
    0 },

  { 330,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/( )^2",
    0, "", offsetof(BlockIO_Template_test, u_n), BLOCKIO_SIG, 31, 1, 2, 660, 0 },

  { 331,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_m), BLOCKIO_SIG, 29, 2, 2, 662,
    0 },

  { 332,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_ha), BLOCKIO_SIG, 23, 4, 2,
    664, 0 },

  { 333,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector3",
    0, "", offsetof(BlockIO_Template_test, MultiportSelector3), BLOCKIO_SIG, 29,
    2, 2, 666, 0 },

  { 334,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_g), BLOCKIO_SIG, 29, 2, 2,
    668, 0 },

  { 335,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide1",
    0, "", offsetof(BlockIO_Template_test, Divide1_a), BLOCKIO_SIG, 29, 2, 2,
    670, 0 },

  { 336,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Subtract",
    0, "", offsetof(BlockIO_Template_test, Subtract_l1), BLOCKIO_SIG, 29, 2, 2,
    672, 0 },

  { 337,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_c5), BLOCKIO_SIG, 29, 2, 2,
    674, 0 },

  { 338,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_nn), BLOCKIO_SIG, 29, 2, 2,
    676, 0 },

  { 339,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2_h), BLOCKIO_SIG, 31, 1, 2,
    678, 0 },

  { 340,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2_k), BLOCKIO_SIG, 0, 1, 2, 680,
    0 },

  { 341,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_k), BLOCKIO_SIG, 31, 1, 2, 682, 0
  },

  { 342,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/^3//2",
    0, "", offsetof(BlockIO_Template_test, u2), BLOCKIO_SIG, 31, 1, 2, 684, 0 },

  { 343,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_n), BLOCKIO_SIG, 29, 2, 2, 686,
    0 },

  { 344,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_d0), BLOCKIO_SIG, 29, 2, 2,
    688, 0 },

  { 345,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_e5), BLOCKIO_SIG, 29, 2,
    2, 690, 0 },

  { 346,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_ef), BLOCKIO_SIG, 29, 2, 2,
    692, 0 },

  { 347,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_g), BLOCKIO_SIG, 29, 2, 2,
    694, 0 },

  { 348,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_cj), BLOCKIO_SIG, 29, 2, 2, 696,
    0 },

  { 349,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_la), BLOCKIO_SIG, 29, 2, 2, 698,
    0 },

  { 350,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_az), BLOCKIO_SIG, 29, 2, 2,
    700, 0 },

  { 351,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_av), BLOCKIO_SIG, 29, 2, 2, 702,
    0 },

  { 352,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_Template_test, MatrixConcatenate_b), BLOCKIO_SIG, 30,
    6, 2, 704, 0 },

  { 353, "template_test/Main Subsystems/Control/LgV2/alpha^q/Add2", 0, "",
    offsetof(BlockIO_Template_test, Add2_d), BLOCKIO_SIG, 30, 6, 2, 706, 0 },

  { 354, "template_test/Main Subsystems/Control/LgV2/alpha^q/Product4", 0, "",
    offsetof(BlockIO_Template_test, Product4_d), BLOCKIO_SIG, 30, 6, 2, 708, 0 },

  { 355, "template_test/Main Subsystems/Control/LgV2/alpha^q/Add3", 0, "",
    offsetof(BlockIO_Template_test, Add3_a), BLOCKIO_SIG, 30, 6, 2, 710, 0 },

  { 356, "template_test/Main Subsystems/Control/LgV2/Update laws/Integrator2", 0,
    "", offsetof(BlockIO_Template_test, Integrator2), BLOCKIO_SIG, 32, 2, 2, 712,
    0 },

  { 357, "template_test/Main Subsystems/Control/LgV2/Control law/Add2", 0, "",
    offsetof(BlockIO_Template_test, Add2_a), BLOCKIO_SIG, 32, 2, 2, 714, 0 },

  { 358, "template_test/Main Subsystems/Control/LgV2/Control law/Product5", 0,
    "", offsetof(BlockIO_Template_test, Product5), BLOCKIO_SIG, 28, 3, 2, 716, 0
  },

  { 359, "template_test/Main Subsystems/Control/LgV2/alpha^s/Product1", 0, "",
    offsetof(BlockIO_Template_test, Product1_l), BLOCKIO_SIG, 20, 9, 2, 718, 0 },

  { 360, "template_test/Main Subsystems/Control/LgV2/alpha^s/Add1", 0, "",
    offsetof(BlockIO_Template_test, Add1_g), BLOCKIO_SIG, 20, 9, 2, 720, 0 },

  { 361,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate1",
    0, "", offsetof(BlockIO_Template_test, VectorConcatenate1), BLOCKIO_SIG, 28,
    3, 2, 722, 0 },

  { 362, "template_test/Main Subsystems/Control/LgV2/alpha^s/Product3", 0, "",
    offsetof(BlockIO_Template_test, Product3_f), BLOCKIO_SIG, 28, 3, 2, 724, 0 },

  { 363,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_Template_test, TrigonometricFunction1_b),
    BLOCKIO_SIG, 0, 1, 2, 726, 0 },

  { 364,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_dr), BLOCKIO_SIG, 0, 1, 2, 728,
    0 },

  { 365,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_c), BLOCKIO_SIG, 31, 1, 2,
    730, 0 },

  { 366,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function",
    0, "", offsetof(BlockIO_Template_test, TrigonometricFunction_o), BLOCKIO_SIG,
    0, 1, 2, 732, 0 },

  { 367,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_hd), BLOCKIO_SIG, 31, 1, 2,
    734, 0 },

  { 368,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_hn), BLOCKIO_SIG, 25, 2, 2,
    736, 0 },

  { 369,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_lz), BLOCKIO_SIG, 0, 1, 2,
    738, 0 },

  { 370,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_cf), BLOCKIO_SIG, 0, 1, 2,
    740, 0 },

  { 371,
    "template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_Template_test, VectorConcatenate_g), BLOCKIO_SIG, 22,
    3, 2, 742, 0 },

  { 372,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product",
    0, "", offsetof(BlockIO_Template_test, Product_pb), BLOCKIO_SIG, 32, 2, 2,
    744, 0 },

  { 373,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_dr), BLOCKIO_SIG, 0, 1, 2,
    746, 0 },

  { 374,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/sin(s)3",
    0, "", offsetof(BlockIO_Template_test, sins3), BLOCKIO_SIG, 0, 1, 2, 748, 0
  },

  { 375,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_dq), BLOCKIO_SIG, 0, 1,
    2, 750, 0 },

  { 376,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_ch), BLOCKIO_SIG, 0, 1, 2,
    752, 0 },

  { 377,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/cos(s)3",
    0, "", offsetof(BlockIO_Template_test, coss3), BLOCKIO_SIG, 0, 1, 2, 754, 0
  },

  { 378,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_en), BLOCKIO_SIG, 0, 1, 2,
    756, 0 },

  { 379,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_o), BLOCKIO_SIG, 0, 1, 2, 758, 0
  },

  { 380,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Subract",
    0, "", offsetof(BlockIO_Template_test, Subract_e3), BLOCKIO_SIG, 0, 1, 2,
    760, 0 },

  { 381,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_kt), BLOCKIO_SIG, 25, 2, 2,
    762, 0 },

  { 382,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Add",
    0, "", offsetof(BlockIO_Template_test, Add_ej), BLOCKIO_SIG, 32, 2, 2, 764,
    0 },

  { 383,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + y_d^s^3",
    0, "", offsetof(BlockIO_Template_test, x_dsy_ds3), BLOCKIO_SIG, 31, 1, 2,
    766, 0 },

  { 384,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s^3 + y_d^s",
    0, "", offsetof(BlockIO_Template_test, x_ds3y_ds), BLOCKIO_SIG, 31, 1, 2,
    768, 0 },

  { 385,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + y_d^s^3  ) - ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_Template_test, x_dsy_ds3x_ds3y_ds), BLOCKIO_SIG, 31,
    1, 2, 770, 0 },

  { 386,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_g2), BLOCKIO_SIG, 31, 1, 2,
    772, 0 },

  { 387,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + x_d^s^2",
    0, "", offsetof(BlockIO_Template_test, x_dsx_ds2), BLOCKIO_SIG, 31, 1, 2,
    774, 0 },

  { 388,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/y_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_Template_test, y_dsy_ds2), BLOCKIO_SIG, 31, 1, 2,
    776, 0 },

  { 389,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + x_d^s^2 ) + ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_Template_test, x_dsx_ds2x_ds3y_ds), BLOCKIO_SIG, 31,
    1, 2, 778, 0 },

  { 390,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2",
    0, "", offsetof(BlockIO_Template_test, u_ab), BLOCKIO_SIG, 31, 1, 2, 780, 0
  },

  { 391,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_d2), BLOCKIO_SIG, 31, 1, 2,
    782, 0 },

  { 392,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Subtract",
    0, "", offsetof(BlockIO_Template_test, Subtract_n5), BLOCKIO_SIG, 31, 1, 2,
    784, 0 },

  { 393,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2",
    0, "", offsetof(BlockIO_Template_test, x_ds2y_ds22), BLOCKIO_SIG, 0, 1, 2,
    786, 0 },

  { 394,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_d3), BLOCKIO_SIG, 31, 1, 2,
    788, 0 },

  { 395,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/(epsilon_n^s)^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_ns2), BLOCKIO_SIG, 31, 1, 2,
    790, 0 },

  { 396,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_ol), BLOCKIO_SIG, 31, 1, 2,
    792, 0 },

  { 397,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2",
    0, "", offsetof(BlockIO_Template_test, u_j), BLOCKIO_SIG, 31, 1, 2, 794, 0 },

  { 398,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2_p4), BLOCKIO_SIG, 0, 1, 2, 796,
    0 },

  { 399,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2_n), BLOCKIO_SIG, 31, 1, 2,
    798, 0 },

  { 400,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_nw), BLOCKIO_SIG, 31, 1, 2, 800,
    0 },

  { 401,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/( )^2",
    0, "", offsetof(BlockIO_Template_test, u_o), BLOCKIO_SIG, 31, 1, 2, 802, 0 },

  { 402,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_pq), BLOCKIO_SIG, 31, 1, 2,
    804, 0 },

  { 403,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_l), BLOCKIO_SIG, 23, 4,
    2, 806, 0 },

  { 404,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_k4), BLOCKIO_SIG, 23, 4, 2,
    808, 0 },

  { 405,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_an), BLOCKIO_SIG, 23, 4, 2, 810,
    0 },

  { 406,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_hn), BLOCKIO_SIG, 25, 2, 2,
    812, 0 },

  { 407,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_o), BLOCKIO_SIG, 25, 2, 2,
    814, 0 },

  { 408,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2",
    0, "", offsetof(BlockIO_Template_test, u_p), BLOCKIO_SIG, 25, 2, 2, 816, 0 },

  { 409,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product3",
    0, "", offsetof(BlockIO_Template_test, Product3_m), BLOCKIO_SIG, 32, 2, 2,
    818, 0 },

  { 410,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_m), BLOCKIO_SIG, 32, 2, 2, 820, 0
  },

  { 411,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_e), BLOCKIO_SIG, 32, 2, 2, 822,
    0 },

  { 412,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector4",
    0, "", offsetof(BlockIO_Template_test, MultiportSelector4), BLOCKIO_SIG, 31,
    1, 2, 824, 0 },

  { 413,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_je), BLOCKIO_SIG, 31, 1, 2,
    826, 0 },

  { 414,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide1",
    0, "", offsetof(BlockIO_Template_test, Divide1_j), BLOCKIO_SIG, 31, 1, 2,
    828, 0 },

  { 415,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_iy), BLOCKIO_SIG, 31, 1, 2, 830,
    0 },

  { 416,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_m2), BLOCKIO_SIG, 31, 1, 2,
    832, 0 },

  { 417,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_jy), BLOCKIO_SIG, 29, 2,
    2, 834, 0 },

  { 418,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_lg), BLOCKIO_SIG, 31, 1, 2,
    836, 0 },

  { 419,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/|p_d^s|^3",
    0, "", offsetof(BlockIO_Template_test, p_ds3), BLOCKIO_SIG, 0, 1, 2, 838, 0
  },

  { 420,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_jj), BLOCKIO_SIG, 31, 1, 2,
    840, 0 },

  { 421,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_j), BLOCKIO_SIG, 31, 1, 2,
    842, 0 },

  { 422,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_ds), BLOCKIO_SIG, 31, 1, 2, 844,
    0 },

  { 423,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_Template_test, epsilon_n2_jy), BLOCKIO_SIG, 31, 1, 2,
    846, 0 },

  { 424,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Delta^2",
    0, "", offsetof(BlockIO_Template_test, Delta2_gi), BLOCKIO_SIG, 0, 1, 2, 848,
    0 },

  { 425,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Add",
    0, "", offsetof(BlockIO_Template_test, Add_if), BLOCKIO_SIG, 31, 1, 2, 850,
    0 },

  { 426,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_pl), BLOCKIO_SIG, 31, 1,
    2, 852, 0 },

  { 427,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide",
    0, "", offsetof(BlockIO_Template_test, Divide_ep), BLOCKIO_SIG, 31, 1, 2,
    854, 0 },

  { 428,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_cj), BLOCKIO_SIG, 31, 1, 2,
    856, 0 },

  { 429,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_ak), BLOCKIO_SIG, 31, 1, 2,
    858, 0 },

  { 430,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/^3//2",
    0, "", offsetof(BlockIO_Template_test, u2_h), BLOCKIO_SIG, 31, 1, 2, 860, 0
  },

  { 431,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide1",
    0, "", offsetof(BlockIO_Template_test, Divide1_d), BLOCKIO_SIG, 31, 1, 2,
    862, 0 },

  { 432,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product3",
    0, "", offsetof(BlockIO_Template_test, Product3_mg), BLOCKIO_SIG, 31, 1, 2,
    864, 0 },

  { 433,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_p), BLOCKIO_SIG, 0, 1, 2,
    866, 0 },

  { 434,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_eo), BLOCKIO_SIG, 29, 2,
    2, 868, 0 },

  { 435,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide2",
    0, "", offsetof(BlockIO_Template_test, Divide2), BLOCKIO_SIG, 29, 2, 2, 870,
    0 },

  { 436,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_i2), BLOCKIO_SIG, 29, 2,
    2, 872, 0 },

  { 437,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_nd), BLOCKIO_SIG, 29, 2, 2,
    874, 0 },

  { 438,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_py), BLOCKIO_SIG, 0, 1,
    2, 876, 0 },

  { 439,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide1",
    0, "", offsetof(BlockIO_Template_test, Divide1_jw), BLOCKIO_SIG, 29, 2, 2,
    878, 0 },

  { 440,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract1",
    0, "", offsetof(BlockIO_Template_test, Subtract1_k), BLOCKIO_SIG, 29, 2, 2,
    880, 0 },

  { 441,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_o1), BLOCKIO_SIG, 0, 1, 2,
    882, 0 },

  { 442,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract",
    0, "", offsetof(BlockIO_Template_test, Subtract_i2), BLOCKIO_SIG, 0, 1, 2,
    884, 0 },

  { 443,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_fp), BLOCKIO_SIG, 31, 1, 2, 886,
    0 },

  { 444,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_a3), BLOCKIO_SIG, 31, 1, 2,
    888, 0 },

  { 445,
    "template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_Template_test, VectorConcatenate_e), BLOCKIO_SIG, 28,
    3, 2, 890, 0 },

  { 446, "template_test/Main Subsystems/Control/LgV2/alpha^s/Add2", 0, "",
    offsetof(BlockIO_Template_test, Add2_l), BLOCKIO_SIG, 28, 3, 2, 892, 0 },

  { 447, "template_test/Main Subsystems/Control/LgV2/alpha^s/Product4", 0, "",
    offsetof(BlockIO_Template_test, Product4_g), BLOCKIO_SIG, 28, 3, 2, 894, 0 },

  { 448, "template_test/Main Subsystems/Control/LgV2/alpha^s/Add3", 0, "",
    offsetof(BlockIO_Template_test, Add3_j), BLOCKIO_SIG, 28, 3, 2, 896, 0 },

  { 449, "template_test/Main Subsystems/Control/LgV2/Control law/Product6", 0,
    "", offsetof(BlockIO_Template_test, Product6), BLOCKIO_SIG, 28, 3, 2, 898, 0
  },

  { 450, "template_test/Main Subsystems/Control/LgV2/Control law/Sum", 0, "",
    offsetof(BlockIO_Template_test, Sum_po), BLOCKIO_SIG, 28, 3, 2, 900, 0 },

  { 451, "template_test/Main Subsystems/Control/Control Switch/tau Switch", 0,
    "", offsetof(BlockIO_Template_test, tauSwitch), BLOCKIO_SIG, 28, 3, 2, 902,
    0 },

  { 452, "template_test/Main Subsystems/Control/LgV2/Update laws/Add", 0, "",
    offsetof(BlockIO_Template_test, Add_lp), BLOCKIO_SIG, 32, 2, 2, 904, 0 },

  { 453,
    "template_test/Main Subsystems/Control/LgV2/V_1^q/Transpose/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_kw), BLOCKIO_SIG, 33, 3,
    2, 906, 0 },

  { 454, "template_test/Main Subsystems/Control/LgV2/V_1^q/Product", 0, "",
    offsetof(BlockIO_Template_test, Product_py), BLOCKIO_SIG, 29, 2, 2, 908, 0 },

  { 455, "template_test/Main Subsystems/Control/LgV2/V_1^q/Gain", 0, "",
    offsetof(BlockIO_Template_test, Gain_i), BLOCKIO_SIG, 29, 2, 2, 910, 0 },

  { 456,
    "template_test/Main Subsystems/Control/LgV2/Update laws/Transpose/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_ln), BLOCKIO_SIG, 32, 2,
    2, 912, 0 },

  { 457, "template_test/Main Subsystems/Control/LgV2/Update laws/Product", 0, "",
    offsetof(BlockIO_Template_test, Product_ce), BLOCKIO_SIG, 32, 2, 2, 914, 0 },

  { 458, "template_test/Main Subsystems/Control/LgV2/Update laws/Add1", 0, "",
    offsetof(BlockIO_Template_test, Add1_f), BLOCKIO_SIG, 32, 2, 2, 916, 0 },

  { 459, "template_test/Main Subsystems/Control/LgV2/Update laws/Product1", 0,
    "", offsetof(BlockIO_Template_test, Product1_kn), BLOCKIO_SIG, 32, 2, 2, 918,
    0 },

  { 460, "template_test/Main Subsystems/Control/LgV2/Update laws/Gain", 0, "",
    offsetof(BlockIO_Template_test, Gain_kq), BLOCKIO_SIG, 32, 2, 2, 920, 0 },

  { 461, "template_test/Main Subsystems/Control/LgV2/zeta/Product", 0, "",
    offsetof(BlockIO_Template_test, Product_n), BLOCKIO_SIG, 28, 3, 2, 922, 0 },

  { 462,
    "template_test/Main Subsystems/Control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_Template_test, Pseudoinverse), BLOCKIO_SIG, 41, 15,
    2, 924, 0 },

  { 463,
    "template_test/Main Subsystems/Control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_Template_test, Product_jq), BLOCKIO_SIG, 37, 5, 2,
    926, 0 },

  { 464,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1",
    0, "", offsetof(BlockIO_Template_test, f_1tou_1), BLOCKIO_SIG, 31, 1, 2, 928,
    0 },

  { 465,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391",
    0, "", offsetof(BlockIO_Template_test, f_2000391), BLOCKIO_SIG, 31, 1, 2,
    930, 0 },

  { 466,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391",
    0, "", offsetof(BlockIO_Template_test, f_2006731f_2000391), BLOCKIO_SIG, 31,
    1, 2, 932, 0 },

  { 467,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731",
    0, "", offsetof(BlockIO_Template_test, f_2006731), BLOCKIO_SIG, 31, 1, 2,
    934, 0 },

  { 468,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_Template_test, MultiportSwitch), BLOCKIO_SIG, 31, 1,
    2, 936, 0 },

  { 469,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3",
    0, "", offsetof(BlockIO_Template_test, f_3tou_3), BLOCKIO_SIG, 31, 1, 2, 938,
    0 },

  { 470,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451",
    0, "", offsetof(BlockIO_Template_test, f_400451), BLOCKIO_SIG, 31, 1, 2, 940,
    0 },

  { 471,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451",
    0, "", offsetof(BlockIO_Template_test, f_400451_p), BLOCKIO_SIG, 31, 1, 2,
    942, 0 },

  { 472,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_Template_test, MultiportSwitch_m), BLOCKIO_SIG, 31,
    1, 2, 944, 0 },

  { 473,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_Template_test, DeadZone001), BLOCKIO_SIG, 31, 1, 2,
    946, 0 },

  { 474,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0",
    0, "", offsetof(BlockIO_Template_test, f_50), BLOCKIO_SIG, 31, 1, 2, 948, 0
  },

  { 475,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0",
    0, "", offsetof(BlockIO_Template_test, f_50_g), BLOCKIO_SIG, 31, 1, 2, 950,
    0 },

  { 476,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_Template_test, MultiportSwitch_c), BLOCKIO_SIG, 31,
    1, 2, 952, 0 },

  { 477, "template_test/Main Subsystems/Control/Thruster allocation/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_he), BLOCKIO_SIG, 35, 7, 2,
    954, 0 },

  { 478,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error", 0,
    "", offsetof(BlockIO_Template_test, QTMIn2Error), BLOCKIO_SIG, 31, 1, 2, 956,
    0 },

  { 479,
    "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual",
    0, "", offsetof(BlockIO_Template_test, QTMIn9Residual), BLOCKIO_SIG, 31, 1,
    2, 958, 0 },

  { 480, "template_test/Main Subsystems/Naviagation/Input from SIT/Derivative1",
    0, "", offsetof(BlockIO_Template_test, Derivative1), BLOCKIO_SIG, 22, 3, 2,
    960, 0 },

  { 481,
    "template_test/Main Subsystems/Naviagation/Navigation Switch/etadot Switch",
    0, "", offsetof(BlockIO_Template_test, etadotSwitch), BLOCKIO_SIG, 22, 3, 2,
    962, 0 },

  { 482,
    "template_test/Main Subsystems/Plant/Thruster setting workaround/Saturation",
    0, "", offsetof(BlockIO_Template_test, Saturation_d), BLOCKIO_SIG, 0, 1, 2,
    964, 0 },

  { 483,
    "template_test/Main Subsystems/Plant/Thruster setting workaround/tau Switch",
    0, "", offsetof(BlockIO_Template_test, tauSwitch_k), BLOCKIO_SIG, 35, 7, 2,
    966, 0 },

  { 484,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_gc), BLOCKIO_SIG, 29, 2,
    2, 968, 0 },

  { 485,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_dc), BLOCKIO_SIG, 0, 1, 2,
    970, 0 },

  { 486,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_Template_test, sqrt_h), BLOCKIO_SIG, 0, 1, 2, 972, 0
  },

  { 487,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_Template_test, MathFunction_jd), BLOCKIO_SIG, 29, 2,
    2, 974, 0 },

  { 488,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_Template_test, Product_ha), BLOCKIO_SIG, 0, 1, 2,
    976, 0 },

  { 489,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_Template_test, sqrt_hn), BLOCKIO_SIG, 0, 1, 2, 978,
    0 },

  { 490, "template_test/Main Subsystems/Naviagation/Input from SIT/QTM In1 FPS",
    0, "", offsetof(BlockIO_Template_test, QTMIn1FPS), BLOCKIO_SIG, 31, 1, 2,
    980, 0 },

  { 491, "template_test/Main Subsystems/Naviagation/Input from SIT/SIT zAI0", 0,
    "", offsetof(BlockIO_Template_test, SITzAI0), BLOCKIO_SIG, 0, 1, 2, 982, 0 },

  { 492, "template_test/Main Subsystems/Naviagation/Input from SIT/SIT zAI1", 0,
    "", offsetof(BlockIO_Template_test, SITzAI1), BLOCKIO_SIG, 0, 1, 2, 984, 0 },

  { 493, "template_test/Main Subsystems/Naviagation/Input from SIT/SIT zAI2", 0,
    "", offsetof(BlockIO_Template_test, SITzAI2), BLOCKIO_SIG, 0, 1, 2, 986, 0 },

  { 494, "template_test/Main Subsystems/Plant/Inverse", 0, "", offsetof
    (BlockIO_Template_test, Inverse), BLOCKIO_SIG, 20, 9, 2, 988, 0 },

  { 495, "template_test/Main Subsystems/Plant/saturation/Saturation", 0, "",
    offsetof(BlockIO_Template_test, Saturation_kh), BLOCKIO_SIG, 31, 1, 2, 990,
    0 },

  { 496, "template_test/Main Subsystems/Plant/saturation/Saturation1", 0, "",
    offsetof(BlockIO_Template_test, Saturation1), BLOCKIO_SIG, 31, 1, 2, 992, 0
  },

  { 497, "template_test/Main Subsystems/Plant/saturation/Saturation2", 0, "",
    offsetof(BlockIO_Template_test, Saturation2), BLOCKIO_SIG, 31, 1, 2, 994, 0
  },

  { 498, "template_test/Main Subsystems/Plant/saturation/plant tau_surge", 0, "",
    offsetof(BlockIO_Template_test, planttau_surge), BLOCKIO_SIG, 31, 1, 2, 996,
    0 },

  { 499, "template_test/Main Subsystems/Plant/saturation/plant tau_sway", 0, "",
    offsetof(BlockIO_Template_test, planttau_sway), BLOCKIO_SIG, 31, 1, 2, 998,
    0 },

  { 500, "template_test/Main Subsystems/Plant/saturation/plant tau_yaw", 0, "",
    offsetof(BlockIO_Template_test, planttau_yaw), BLOCKIO_SIG, 31, 1, 2, 1000,
    0 },

  { 501, "template_test/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster",
    0, "", offsetof(BlockIO_Template_test, BatteryBowThruster), BLOCKIO_SIG, 0,
    1, 2, 1002, 0 },

  { 502, "template_test/Outputs to LabVIEW/Battery Voltage/Battery Main", 0, "",
    offsetof(BlockIO_Template_test, BatteryMain), BLOCKIO_SIG, 0, 1, 2, 1004, 0
  },

  { 503, "template_test/Outputs to LabVIEW/Battery Voltage/Battery Servo", 0, "",
    offsetof(BlockIO_Template_test, BatteryServo), BLOCKIO_SIG, 0, 1, 2, 1006, 0
  },

  { 504, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_Yaw [deg]", 0, "",
    offsetof(BlockIO_Template_test, CSE1_Yawdeg), BLOCKIO_SIG, 0, 1, 2, 1008, 0
  },

  { 505, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_x [m]", 0, "",
    offsetof(BlockIO_Template_test, CSE1_xm), BLOCKIO_SIG, 0, 1, 2, 1010, 0 },

  { 506, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_y [m]", 0, "",
    offsetof(BlockIO_Template_test, CSE1_ym), BLOCKIO_SIG, 0, 1, 2, 1012, 0 },

  { 507, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]", 0, "",
    offsetof(BlockIO_Template_test, CSE1_rdegs), BLOCKIO_SIG, 0, 1, 2, 1014, 0 },

  { 508, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]", 0, "",
    offsetof(BlockIO_Template_test, CSE1_ums), BLOCKIO_SIG, 0, 1, 2, 1016, 0 },

  { 509, "template_test/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]", 0, "",
    offsetof(BlockIO_Template_test, CSE1_vms), BLOCKIO_SIG, 0, 1, 2, 1018, 0 },

  { 510, "template_test/Outputs to LabVIEW/Naviagtion/QS_Yaw [deg]", 0, "",
    offsetof(BlockIO_Template_test, QS_Yawdeg), BLOCKIO_SIG, 0, 1, 2, 1020, 0 },

  { 511, "template_test/Outputs to LabVIEW/Naviagtion/QS_x [m]", 0, "", offsetof
    (BlockIO_Template_test, QS_xm), BLOCKIO_SIG, 0, 1, 2, 1022, 0 },

  { 512, "template_test/Outputs to LabVIEW/Naviagtion/QS_y [m]", 0, "", offsetof
    (BlockIO_Template_test, QS_ym), BLOCKIO_SIG, 0, 1, 2, 1024, 0 },

  { 513, "template_test/Outputs to LabVIEW/Naviagtion/LS_Yaw [deg]", 0, "",
    offsetof(BlockIO_Template_test, LS_Yawdeg), BLOCKIO_SIG, 0, 1, 2, 1026, 0 },

  { 514, "template_test/Outputs to LabVIEW/Naviagtion/LS_x [m]", 0, "", offsetof
    (BlockIO_Template_test, LS_xm), BLOCKIO_SIG, 0, 1, 2, 1028, 0 },

  { 515, "template_test/Outputs to LabVIEW/Naviagtion/LS_y [m]", 0, "", offsetof
    (BlockIO_Template_test, LS_ym), BLOCKIO_SIG, 0, 1, 2, 1030, 0 },

  { 516, "template_test/Outputs to LabVIEW/Plant/plant BT power", 0, "",
    offsetof(BlockIO_Template_test, plantBTpower), BLOCKIO_SIG, 0, 1, 2, 1032, 0
  },

  { 517, "template_test/Outputs to LabVIEW/Plant/plant VSP speed", 0, "",
    offsetof(BlockIO_Template_test, plantVSPspeed), BLOCKIO_SIG, 0, 1, 2, 1034,
    0 },

  { 518, "template_test/Outputs to LabVIEW/Plant/plant u_1", 0, "", offsetof
    (BlockIO_Template_test, plantu_1), BLOCKIO_SIG, 0, 1, 2, 1036, 0 },

  { 519, "template_test/Outputs to LabVIEW/Plant/plant u_2", 0, "", offsetof
    (BlockIO_Template_test, plantu_2), BLOCKIO_SIG, 0, 1, 2, 1038, 0 },

  { 520, "template_test/Outputs to LabVIEW/Plant/plant u_3", 0, "", offsetof
    (BlockIO_Template_test, plantu_3), BLOCKIO_SIG, 0, 1, 2, 1040, 0 },

  { 521, "template_test/Outputs to LabVIEW/Plant/plant u_4", 0, "", offsetof
    (BlockIO_Template_test, plantu_4), BLOCKIO_SIG, 0, 1, 2, 1042, 0 },

  { 522, "template_test/Outputs to LabVIEW/Plant/plant u_5", 0, "", offsetof
    (BlockIO_Template_test, plantu_5), BLOCKIO_SIG, 0, 1, 2, 1044, 0 },

  { 523, "template_test/Outputs to LabVIEW/Visualization/eta_psi [rad]", 0, "",
    offsetof(BlockIO_Template_test, eta_psirad), BLOCKIO_SIG, 0, 1, 2, 1046, 0 },

  { 524, "template_test/Outputs to LabVIEW/Visualization/eta_psid [rad]", 0, "",
    offsetof(BlockIO_Template_test, eta_psidrad), BLOCKIO_SIG, 0, 1, 2, 1048, 0
  },

  { 525, "template_test/Outputs to LabVIEW/Visualization/eta_x [m]", 0, "",
    offsetof(BlockIO_Template_test, eta_xm), BLOCKIO_SIG, 0, 1, 2, 1050, 0 },

  { 526, "template_test/Outputs to LabVIEW/Visualization/eta_xd [m]", 0, "",
    offsetof(BlockIO_Template_test, eta_xdm), BLOCKIO_SIG, 0, 1, 2, 1052, 0 },

  { 527, "template_test/Outputs to LabVIEW/Visualization/eta_y [m]", 0, "",
    offsetof(BlockIO_Template_test, eta_ym), BLOCKIO_SIG, 0, 1, 2, 1054, 0 },

  { 528, "template_test/Outputs to LabVIEW/Visualization/eta_yd [m]", 0, "",
    offsetof(BlockIO_Template_test, eta_ydm), BLOCKIO_SIG, 0, 1, 2, 1056, 0 },

  { 529, "template_test/Outputs to LabVIEW/Visualization/psi_los [rad]", 0, "",
    offsetof(BlockIO_Template_test, psi_losrad), BLOCKIO_SIG, 0, 1, 2, 1058, 0 },

  { 530, "template_test/Outputs to LabVIEW/Visualization/psi_plot", 0, "",
    offsetof(BlockIO_Template_test, psi_plot), BLOCKIO_SIG, 22, 3, 2, 1060, 0 },

  { 531, "template_test/Outputs to LabVIEW/Visualization/q_x [m]", 0, "",
    offsetof(BlockIO_Template_test, q_xm), BLOCKIO_SIG, 0, 1, 2, 1062, 0 },

  { 532, "template_test/Outputs to LabVIEW/Visualization/q_y [m]", 0, "",
    offsetof(BlockIO_Template_test, q_ym), BLOCKIO_SIG, 0, 1, 2, 1064, 0 },

  { 533, "template_test/Outputs to LabVIEW/Visualization/x_plot", 0, "",
    offsetof(BlockIO_Template_test, x_plot), BLOCKIO_SIG, 22, 3, 2, 1066, 0 },

  { 534, "template_test/Outputs to LabVIEW/Visualization/y_plot", 0, "",
    offsetof(BlockIO_Template_test, y_plot), BLOCKIO_SIG, 22, 3, 2, 1068, 0 },

  { 535,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator",
    0, "", offsetof(BlockIO_Template_test, Integrator_j), BLOCKIO_SIG, 22, 3, 2,
    1070, 0 },

  { 536,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator1",
    0, "", offsetof(BlockIO_Template_test, Integrator1_o), BLOCKIO_SIG, 22, 3, 2,
    1072, 0 },

  { 537,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11",
    0, "", offsetof(BlockIO_Template_test, R11_k), BLOCKIO_SIG, 0, 1, 2, 1074, 0
  },

  { 538,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21",
    0, "", offsetof(BlockIO_Template_test, R21_n), BLOCKIO_SIG, 0, 1, 2, 1076, 0
  },

  { 539,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12",
    0, "", offsetof(BlockIO_Template_test, R12_fw), BLOCKIO_SIG, 0, 1, 2, 1078,
    0 },

  { 540,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22",
    0, "", offsetof(BlockIO_Template_test, R22_e), BLOCKIO_SIG, 0, 1, 2, 1080, 0
  },

  { 541,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)",
    0, "", offsetof(BlockIO_Template_test, Rpsi_c), BLOCKIO_SIG, 20, 9, 2, 1082,
    0 },

  { 542,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product3",
    0, "", offsetof(BlockIO_Template_test, Product3_n), BLOCKIO_SIG, 22, 3, 2,
    1084, 0 },

  { 543,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product1",
    0, "", offsetof(BlockIO_Template_test, Product1_gl), BLOCKIO_SIG, 22, 3, 2,
    1086, 0 },

  { 544,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_ib), BLOCKIO_SIG, 22, 3, 2, 1088,
    0 },

  { 545,
    "template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product2",
    0, "", offsetof(BlockIO_Template_test, Product2_i1), BLOCKIO_SIG, 22, 3, 2,
    1090, 0 },

  { 546,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1",
    0, "", offsetof(BlockIO_Template_test, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1092, 0 },

  { 547,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2",
    0, "", offsetof(BlockIO_Template_test, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1094, 0 },

  { 548, "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Add", 0,
    "", offsetof(BlockIO_Template_test, Add_h), BLOCKIO_SIG, 0, 1, 2, 1096, 0 },

  { 549,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1",
    0, "", offsetof(BlockIO_Template_test, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1098, 0 },

  { 550,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2",
    0, "", offsetof(BlockIO_Template_test, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1100, 0 },

  { 551, "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg", 0,
    "", offsetof(BlockIO_Template_test, Neg), BLOCKIO_SIG, 0, 1, 2, 1102, 0 },

  { 552, "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_ac), BLOCKIO_SIG, 0, 1, 2, 1104,
    0 },

  { 553, "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum2",
    0, "", offsetof(BlockIO_Template_test, Sum2_m), BLOCKIO_SIG, 0, 1, 2, 1106,
    0 },

  { 554,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_Template_test, Switch_h), BLOCKIO_SIG, 0, 1, 2, 1108,
    0 },

  { 555,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch2",
    0, "", offsetof(BlockIO_Template_test, Switch2_e), BLOCKIO_SIG, 0, 1, 2,
    1110, 0 },

  { 556,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch",
    0, "", offsetof(BlockIO_Template_test, Switch_p), BLOCKIO_SIG, 0, 1, 2, 1112,
    0 },

  { 557,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch2",
    0, "", offsetof(BlockIO_Template_test, Switch2_j), BLOCKIO_SIG, 0, 1, 2,
    1114, 0 },

  { 558,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch",
    0, "", offsetof(BlockIO_Template_test, Switch_m), BLOCKIO_SIG, 0, 1, 2, 1116,
    0 },

  { 559,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch2",
    0, "", offsetof(BlockIO_Template_test, Switch2_f), BLOCKIO_SIG, 0, 1, 2,
    1118, 0 },

  { 560,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sign",
    0, "", offsetof(BlockIO_Template_test, Sign_e), BLOCKIO_SIG, 0, 1, 2, 1120,
    0 },

  { 561,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product1",
    0, "Port VPS_X", offsetof(BlockIO_Template_test, PortVPS_X), BLOCKIO_SIG, 0,
    1, 2, 1122, 0 },

  { 562,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x",
    0, "Port VPS_X", offsetof(BlockIO_Template_test, PortVPS_X_d), BLOCKIO_SIG,
    0, 1, 2, 1124, 0 },

  { 563,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product2",
    0, "Port VSP_Y", offsetof(BlockIO_Template_test, PortVSP_Y), BLOCKIO_SIG, 0,
    1, 2, 1126, 0 },

  { 564,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y",
    0, "Port VSP_Y", offsetof(BlockIO_Template_test, PortVSP_Y_g), BLOCKIO_SIG,
    0, 1, 2, 1128, 0 },

  { 565,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product3",
    0, "Starboard VSP_X", offsetof(BlockIO_Template_test, StarboardVSP_X),
    BLOCKIO_SIG, 0, 1, 2, 1130, 0 },

  { 566,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product4",
    0, "Starboard VSP_Y", offsetof(BlockIO_Template_test, StarboardVSP_Y),
    BLOCKIO_SIG, 0, 1, 2, 1132, 0 },

  { 567,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1",
    0, "", offsetof(BlockIO_Template_test, Servo1), BLOCKIO_SIG, 0, 1, 2, 1134,
    0 },

  { 568,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2",
    0, "", offsetof(BlockIO_Template_test, Servo2), BLOCKIO_SIG, 0, 1, 2, 1136,
    0 },

  { 569,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3",
    0, "", offsetof(BlockIO_Template_test, Servo3), BLOCKIO_SIG, 0, 1, 2, 1138,
    0 },

  { 570,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4",
    0, "", offsetof(BlockIO_Template_test, Servo4), BLOCKIO_SIG, 0, 1, 2, 1140,
    0 },

  { 571,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain",
    0, "", offsetof(BlockIO_Template_test, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2,
    1142, 0 },

  { 572,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_dnw), BLOCKIO_SIG, 0, 1, 2, 1144,
    0 },

  { 573,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port",
    0, "", offsetof(BlockIO_Template_test, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 1146,
    0 },

  { 574,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard",
    0, "", offsetof(BlockIO_Template_test, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2,
    1148, 0 },

  { 575,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12",
    0, "", offsetof(BlockIO_Template_test, S12_j), BLOCKIO_SIG, 31, 1, 2, 1150,
    0 },

  { 576,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S_2(psi_d^s^2)",
    0, "", offsetof(BlockIO_Template_test, S_2psi_ds2), BLOCKIO_SIG, 23, 4, 2,
    1152, 0 },

  { 577,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12",
    0, "", offsetof(BlockIO_Template_test, S12_l), BLOCKIO_SIG, 31, 1, 2, 1154,
    0 },

  { 578,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S_2(psi_d^s)",
    0, "", offsetof(BlockIO_Template_test, S_2psi_ds), BLOCKIO_SIG, 23, 4, 2,
    1156, 0 },

  { 579,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R11",
    0, "", offsetof(BlockIO_Template_test, R11_b), BLOCKIO_SIG, 0, 1, 2, 1158, 0
  },

  { 580,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R21",
    0, "", offsetof(BlockIO_Template_test, R21_k), BLOCKIO_SIG, 0, 1, 2, 1160, 0
  },

  { 581,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12",
    0, "", offsetof(BlockIO_Template_test, R12_i), BLOCKIO_SIG, 0, 1, 2, 1162, 0
  },

  { 582,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22",
    0, "", offsetof(BlockIO_Template_test, R22_m), BLOCKIO_SIG, 0, 1, 2, 1164, 0
  },

  { 583,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R_2(psi_d)",
    0, "", offsetof(BlockIO_Template_test, R_2psi_d), BLOCKIO_SIG, 23, 4, 2,
    1166, 0 },

  { 584,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_Template_test, Gain1_k), BLOCKIO_SIG, 39, 1, 2, 1168,
    0 },

  { 585,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_e0), BLOCKIO_SIG, 39, 1, 2, 1170,
    0 },

  { 586,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_j), BLOCKIO_SIG, 39, 1, 2, 1172,
    0 },

  { 587,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_n), BLOCKIO_SIG, 39, 1, 2, 1174,
    0 },

  { 588,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_Template_test, Gain_jt), BLOCKIO_SIG, 39, 1, 2, 1176,
    0 },

  { 589,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_Template_test, Gain1_m), BLOCKIO_SIG, 39, 1, 2, 1178,
    0 },

  { 590,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_Template_test, Sum_g), BLOCKIO_SIG, 39, 1, 2, 1180,
    0 },

  { 591,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare), BLOCKIO_SIG, 38, 1, 2, 1182,
    0 },

  { 592,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare_m), BLOCKIO_SIG, 38, 1, 2,
    1184, 0 },

  { 593,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare_l), BLOCKIO_SIG, 38, 1, 2,
    1186, 0 },

  { 594,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_Template_test, Sum1_iu), BLOCKIO_SIG, 38, 1, 2, 1188,
    0 },

  { 595,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare_e), BLOCKIO_SIG, 38, 1, 2,
    1190, 0 },

  { 596,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare_d), BLOCKIO_SIG, 38, 1, 2,
    1192, 0 },

  { 597,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare_g), BLOCKIO_SIG, 38, 1, 2,
    1194, 0 },

  { 598,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare_a), BLOCKIO_SIG, 38, 1, 2,
    1196, 0 },

  { 599,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare_b), BLOCKIO_SIG, 38, 1, 2,
    1198, 0 },

  { 600,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_Template_test, Compare_aa), BLOCKIO_SIG, 38, 1, 2,
    1200, 0 },

  { 601,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/LowerRelop1",
    0, "", offsetof(BlockIO_Template_test, LowerRelop1), BLOCKIO_SIG, 8, 1, 2,
    1202, 0 },

  { 602,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/UpperRelop",
    0, "", offsetof(BlockIO_Template_test, UpperRelop), BLOCKIO_SIG, 8, 1, 2,
    1204, 0 },

  { 603,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/LowerRelop1",
    0, "", offsetof(BlockIO_Template_test, LowerRelop1_g), BLOCKIO_SIG, 8, 1, 2,
    1206, 0 },

  { 604,
    "template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/UpperRelop",
    0, "", offsetof(BlockIO_Template_test, UpperRelop_d), BLOCKIO_SIG, 8, 1, 2,
    1208, 0 },

  { 605,
    "template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_Template_test, LogicalOperator), BLOCKIO_SIG, 40, 1,
    2, 1210, 0 },

  { 606,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_Template_test, LowerRelop1_c), BLOCKIO_SIG, 8, 1, 2,
    1212, 0 },

  { 607,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_Template_test, UpperRelop_k), BLOCKIO_SIG, 8, 1, 2,
    1214, 0 },

  { 608,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/LowerRelop1",
    0, "", offsetof(BlockIO_Template_test, LowerRelop1_o), BLOCKIO_SIG, 8, 1, 2,
    1216, 0 },

  { 609,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/UpperRelop",
    0, "", offsetof(BlockIO_Template_test, UpperRelop_g), BLOCKIO_SIG, 8, 1, 2,
    1218, 0 },

  { 610,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/LowerRelop1",
    0, "", offsetof(BlockIO_Template_test, LowerRelop1_on), BLOCKIO_SIG, 8, 1, 2,
    1220, 0 },

  { 611,
    "template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/UpperRelop",
    0, "", offsetof(BlockIO_Template_test, UpperRelop_d5), BLOCKIO_SIG, 8, 1, 2,
    1222, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3,
  1, 1, 1, 1, 1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 6, 6, 1, 1, 1, 1, 1, 6,
  1, 6, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 3, 1,
  1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1,
  1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1,
  1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3,
  1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 3, 3, 3, 2, 3, 2,
  1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 3, 2,
  1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 1, 2, 1, 3, 1, 3, 3, 3, 3, 3, 1, 3, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 2, 1, 1, 3, 1, 2,
  1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1, 5, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 1, 1, 7, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
  1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, };

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

static char* NI_CompiledModelName = "template_test";
static char* NI_CompiledModelVersion = "1.13";
static char* NI_CompiledModelDateTime = "Thu Mar 20 15:07:33 2014";

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
   The undef allows us to access the real Template_test_P
   In the rest of the code Template_test_P is redefine to be the read-side
   of rtParameter.
 */
#undef Template_test_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &Template_test_P, sizeof(Parameters_Template_test));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka Template_test_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_Template_test));
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
             (Parameters_Template_test));

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
           (Parameters_Template_test));
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

#endif                                 // of NI_ROOTMODEL_Template_test
