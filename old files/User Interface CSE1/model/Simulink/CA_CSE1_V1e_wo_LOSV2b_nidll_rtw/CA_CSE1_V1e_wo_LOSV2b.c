/*
 * CA_CSE1_V1e_wo_LOSV2b.c
 *
 * Real-Time Workshop code generation for Simulink model "CA_CSE1_V1e_wo_LOSV2b.mdl".
 *
 * Model Version              : 1.193
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Fri Sep 20 14:52:12 2013
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CA_CSE1_V1e_wo_LOSV2b.h"
#include "CA_CSE1_V1e_wo_LOSV2b_private.h"

/* Block signals (auto storage) */
BlockIO_CA_CSE1_V1e_wo_LOSV2b CA_CSE1_V1e_wo_LOSV2b_B;

/* Continuous states */
ContinuousStates_CA_CSE1_V1e_wo CA_CSE1_V1e_wo_LOSV2b_X;

/* Solver Matrices */

/* A and B matrices used by ODE3 fixed-step solver */
static const real_T rt_ODE3_A[3] = {
  1.0/2.0, 3.0/4.0, 1.0
};

static const real_T rt_ODE3_B[3][3] = {
  { 1.0/2.0, 0.0, 0.0 },

  { 0.0, 3.0/4.0, 0.0 },

  { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
};

/* Block states (auto storage) */
D_Work_CA_CSE1_V1e_wo_LOSV2b CA_CSE1_V1e_wo_LOSV2b_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_CA_CSE1_V1e_wo_ CA_CSE1_V1e_wo_L_PrevZCSigState;

/* Real-time model */
RT_MODEL_CA_CSE1_V1e_wo_LOSV2b CA_CSE1_V1e_wo_LOSV2b_M_;
RT_MODEL_CA_CSE1_V1e_wo_LOSV2b *CA_CSE1_V1e_wo_LOSV2b_M =
  &CA_CSE1_V1e_wo_LOSV2b_M_;

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

/* This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 27;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y,x,
                nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  CA_CSE1_V1e_wo_LOSV2b_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  CA_CSE1_V1e_wo_LOSV2b_output(0);
  CA_CSE1_V1e_wo_LOSV2b_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE3_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  CA_CSE1_V1e_wo_LOSV2b_output(0);
  CA_CSE1_V1e_wo_LOSV2b_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE3_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void CA_CSE1_V1e_wo_LOSV2b_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.t[0] = rtsiGetT
      (&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
                          ((CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTick0+1)*
      CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp;
    real_T tmp_0[5];
    int32_T i;
    real_T tmp_1[18];
    real_T tmp_2[15];
    int32_T tmp_3;
    int32_T tmp_4;
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
      /* Gain: '<S26>/Accuracy u_1' incorporates:
       *  Constant: '<S26>/u1'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_1 =
        CA_CSE1_V1e_wo_LOSV2b_P.Accuracyu_1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.u1_Value;

      /* Gain: '<S26>/Accuracy u_2' incorporates:
       *  Constant: '<S26>/u2'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_2 =
        CA_CSE1_V1e_wo_LOSV2b_P.Accuracyu_2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.u2_Value;

      /* Gain: '<S26>/Accuracy u_3' incorporates:
       *  Constant: '<S26>/u3'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_3 =
        CA_CSE1_V1e_wo_LOSV2b_P.Accuracyu_3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.u3_Value;

      /* Gain: '<S26>/Accuracy u_4' incorporates:
       *  Constant: '<S26>/u4'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_4 =
        CA_CSE1_V1e_wo_LOSV2b_P.Accuracyu_4_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.u4_Value;

      /* Gain: '<S26>/Accuracy u_5' incorporates:
       *  Constant: '<S26>/u5'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_5 =
        CA_CSE1_V1e_wo_LOSV2b_P.Accuracyu_5_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.u5_Value;

      /* Gain: '<S30>/Scaling_JS_L_Y' incorporates:
       *  Constant: '<S30>/JS_L_Y'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.u1 = CA_CSE1_V1e_wo_LOSV2b_P.Scaling_JS_L_Y_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.JS_L_Y_Value;

      /* Gain: '<S9>/PS3 u_1' */
      CA_CSE1_V1e_wo_LOSV2b_B.PS3u_1 = CA_CSE1_V1e_wo_LOSV2b_P.PS3u_1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u1;

      /* Gain: '<S30>/Scaling_JS_L_X' incorporates:
       *  Constant: '<S30>/JS_L_X'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.u1_p = CA_CSE1_V1e_wo_LOSV2b_P.Scaling_JS_L_X_Gain
        * CA_CSE1_V1e_wo_LOSV2b_P.JS_L_X_Value;

      /* Gain: '<S9>/PS3 u_2' */
      CA_CSE1_V1e_wo_LOSV2b_B.PS3u_2 = CA_CSE1_V1e_wo_LOSV2b_P.PS3u_2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u1_p;

      /* Gain: '<S30>/Scaling_JS_R_Y' incorporates:
       *  Constant: '<S30>/JS_R_Y'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.u1_a = CA_CSE1_V1e_wo_LOSV2b_P.Scaling_JS_R_Y_Gain
        * CA_CSE1_V1e_wo_LOSV2b_P.JS_R_Y_Value;

      /* Gain: '<S9>/PS3 u_3' */
      CA_CSE1_V1e_wo_LOSV2b_B.PS3u_3 = CA_CSE1_V1e_wo_LOSV2b_P.PS3u_3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u1_a;

      /* Gain: '<S30>/Scaling_JS_R_X' incorporates:
       *  Constant: '<S30>/JS_R_X'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.u1_i = CA_CSE1_V1e_wo_LOSV2b_P.Scaling_JS_R_X_Gain
        * CA_CSE1_V1e_wo_LOSV2b_P.JS_R_X_Value;

      /* Gain: '<S9>/PS3 u_4' */
      CA_CSE1_V1e_wo_LOSV2b_B.PS3u_4 = CA_CSE1_V1e_wo_LOSV2b_P.PS3u_4_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u1_i;

      /* Sum: '<S9>/Add' incorporates:
       *  Constant: '<S30>/L2'
       *  Constant: '<S30>/R2'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.BowThrusterdirection =
        CA_CSE1_V1e_wo_LOSV2b_P.L2_Value + CA_CSE1_V1e_wo_LOSV2b_P.R2_Value;

      /* Gain: '<S9>/PS3 u_5' */
      CA_CSE1_V1e_wo_LOSV2b_B.PS3u_5 = CA_CSE1_V1e_wo_LOSV2b_P.PS3u_5_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.BowThrusterdirection;

      /* Gain: '<S23>/Gain K_e1_joystick' incorporates:
       *  Constant: '<S23>/K_e1_joystick'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.GainK_e1_joystick =
        CA_CSE1_V1e_wo_LOSV2b_P.GainK_e1_joystick_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.K_e1_joystick_Value;

      /* Gain: '<S23>/Gain K_e2_joystick' incorporates:
       *  Constant: '<S23>/K_e2_joystick'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.GainK_e2_joystick =
        CA_CSE1_V1e_wo_LOSV2b_P.GainK_e2_joystick_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.K_e2_joystick_Value;

      /* Gain: '<S23>/Gain K_e3_joystick' incorporates:
       *  Constant: '<S23>/K_e3_joystick'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.GainK_e3_joystick =
        CA_CSE1_V1e_wo_LOSV2b_P.GainK_e3_joystick_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.K_e3_joystick_Value;

      /* Gain: '<S23>/Gain K_e4_joystick' incorporates:
       *  Constant: '<S23>/K_e4_joystick'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.GainK_e4_joystick =
        CA_CSE1_V1e_wo_LOSV2b_P.GainK_e4_joystick_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.K_e4_joystick_Value;

      /* Gain: '<S23>/Gain K_e5_joystick' incorporates:
       *  Constant: '<S23>/K_e5_joystick'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.GainK_e5_joystick =
        CA_CSE1_V1e_wo_LOSV2b_P.GainK_e5_joystick_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.K_e5_joystick_Value;

      /* Reshape: '<S23>/Thruster Gain matrix' incorporates:
       *  Constant: '<S23>/Constant'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e1_joystick;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[1] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[2] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[3] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[4] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[5] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[6] =
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e2_joystick;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[7] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[8] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[9] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[10] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[11] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[12] =
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e3_joystick;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[13] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[14] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[15] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[16] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[17] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[18] =
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e4_joystick;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[19] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[20] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[21] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[22] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[23] =
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix[24] =
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e5_joystick;

      /* Product Block: '<S8>/K_e^-1' */
      {
        static const int_T dims[3] = { 5, 5, 5 };

        rt_MatDivRR_Dbl(CA_CSE1_V1e_wo_LOSV2b_B.K_e1,
                        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix,
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK4[0], (real_T*)
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK1[0],
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK2[0], (real_T*)
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK3[0],
                        &dims[0]);
      }

      /* Gain: '<S24>/-l_x1' incorporates:
       *  Constant: '<S24>/l_x1'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.l_x1 = CA_CSE1_V1e_wo_LOSV2b_P.l_x1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.l_x1_Value;

      /* Gain: '<S24>/-l_y2' incorporates:
       *  Constant: '<S24>/l_y2'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.l_y2 = CA_CSE1_V1e_wo_LOSV2b_P.l_y2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.l_y2_Value;

      /* Gain: '<S24>/-l_x2' incorporates:
       *  Constant: '<S24>/l_x2'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.l_x2 = CA_CSE1_V1e_wo_LOSV2b_P.l_x2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.l_x2_Value;

      /* Reshape: '<S24>/3x5' incorporates:
       *  Constant: '<S24>/T_e11'
       *  Constant: '<S24>/T_e12'
       *  Constant: '<S24>/T_e13'
       *  Constant: '<S24>/T_e14'
       *  Constant: '<S24>/T_e15'
       *  Constant: '<S24>/T_e21'
       *  Constant: '<S24>/T_e22'
       *  Constant: '<S24>/T_e23'
       *  Constant: '<S24>/T_e24'
       *  Constant: '<S24>/T_e25'
       *  Constant: '<S24>/l_x3'
       *  Constant: '<S24>/l_y1'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.x5[0] = CA_CSE1_V1e_wo_LOSV2b_P.T_e11_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[1] = CA_CSE1_V1e_wo_LOSV2b_P.T_e21_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[2] = CA_CSE1_V1e_wo_LOSV2b_P.l_y1_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[3] = CA_CSE1_V1e_wo_LOSV2b_P.T_e12_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[4] = CA_CSE1_V1e_wo_LOSV2b_P.T_e22_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[5] = CA_CSE1_V1e_wo_LOSV2b_B.l_x1;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[6] = CA_CSE1_V1e_wo_LOSV2b_P.T_e13_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[7] = CA_CSE1_V1e_wo_LOSV2b_P.T_e23_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[8] = CA_CSE1_V1e_wo_LOSV2b_B.l_y2;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[9] = CA_CSE1_V1e_wo_LOSV2b_P.T_e14_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[10] = CA_CSE1_V1e_wo_LOSV2b_P.T_e24_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[11] = CA_CSE1_V1e_wo_LOSV2b_B.l_x2;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[12] = CA_CSE1_V1e_wo_LOSV2b_P.T_e15_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[13] = CA_CSE1_V1e_wo_LOSV2b_P.T_e25_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.x5[14] = CA_CSE1_V1e_wo_LOSV2b_P.l_x3_Value;

      /* S-Function (sdsppinv): '<S8>/T_e^+' */
      /* Copy input to temporary space */
      memcpy((void *)(&CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK1[0]), (void *)
             (&CA_CSE1_V1e_wo_LOSV2b_B.x5[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK1[0], 3, 5,
                      &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_S[0],
                      &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK3[0],
                      &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_WORK[0],
                      &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_U[0],
                      &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_S[0],
          &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_U[0],
          &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_V[0], &CA_CSE1_V1e_wo_LOSV2b_B.T_e[0],
                                (const int32_T)3, (const int32_T)5);
      }

      /* Product: '<S8>/T_e^+ K_e^-1' */
      for (i = 0; i < 5; i++) {
        for (tmp_4 = 0; tmp_4 < 3; tmp_4++) {
          CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1[i + 5 * tmp_4] = 0.0;
          for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
            CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1[i + 5 * tmp_4] =
              CA_CSE1_V1e_wo_LOSV2b_B.K_e1[5 * tmp_3 + i] *
              CA_CSE1_V1e_wo_LOSV2b_B.T_e[5 * tmp_4 + tmp_3] +
              CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1[5 * tmp_4 + i];
          }
        }
      }

      /* Sum: '<S8>/Sum1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1 = CA_CSE1_V1e_wo_LOSV2b_B.u1 +
        CA_CSE1_V1e_wo_LOSV2b_B.u1_a;

      /* Gain: '<S8>/Joystick tau_surge' */
      CA_CSE1_V1e_wo_LOSV2b_B.Joysticktau_surge =
        CA_CSE1_V1e_wo_LOSV2b_P.Joysticktau_surge_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Sum1;

      /* Saturate: '<S8>/Saturation1' */
      tmp = CA_CSE1_V1e_wo_LOSV2b_B.Joysticktau_surge;
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation1 = rt_SATURATE(tmp,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation1_LowerSat,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation1_UpperSat);

      /* Sum: '<S8>/Sum2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum2 = CA_CSE1_V1e_wo_LOSV2b_B.u1_p +
        CA_CSE1_V1e_wo_LOSV2b_B.u1_i;

      /* Gain: '<S8>/Joystick tau_sway' */
      CA_CSE1_V1e_wo_LOSV2b_B.Joysticktau_sway =
        CA_CSE1_V1e_wo_LOSV2b_P.Joysticktau_sway_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Sum2;

      /* Saturate: '<S8>/Saturation2' */
      tmp = CA_CSE1_V1e_wo_LOSV2b_B.Joysticktau_sway;
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation2 = rt_SATURATE(tmp,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation2_LowerSat,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation2_UpperSat);

      /* Sum: '<S8>/Sum' incorporates:
       *  Constant: '<S30>/L2'
       *  Constant: '<S30>/R2'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum = CA_CSE1_V1e_wo_LOSV2b_P.L2_Value +
        CA_CSE1_V1e_wo_LOSV2b_P.R2_Value;

      /* Gain: '<S8>/Joystick tau_yaw' */
      CA_CSE1_V1e_wo_LOSV2b_B.Joysticktau_yaw =
        CA_CSE1_V1e_wo_LOSV2b_P.Joysticktau_yaw_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Sum;

      /* Saturate: '<S8>/Saturation3' */
      tmp = CA_CSE1_V1e_wo_LOSV2b_B.Joysticktau_yaw;
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation3 = rt_SATURATE(tmp,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation3_LowerSat,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation3_UpperSat);

      /* SignalConversion: '<S8>/TmpHiddenBufferAtProduct1Inport2' */
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inport[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation1;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inport[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation2;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inport[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation3;

      /* Saturate: '<S8>/Saturation' */
      for (i = 0; i < 5; i++) {
        /* Product: '<S8>/Product1' */
        CA_CSE1_V1e_wo_LOSV2b_B.Product1[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Product1[i] = CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1[i]
          * CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inport[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Product1[i] = CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1[i
          + 5] * CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inport[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Product1[i] = CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1[i
          + 10] * CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inport[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1[i];
        tmp_0[i] = CA_CSE1_V1e_wo_LOSV2b_B.Product1[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation[i] = rt_SATURATE(tmp_0[i],
          CA_CSE1_V1e_wo_LOSV2b_P.Saturation_LowerSat,
          CA_CSE1_V1e_wo_LOSV2b_P.Saturation_UpperSat);
      }

      /* Gain: '<S8>/Joystick u_1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_1 =
        CA_CSE1_V1e_wo_LOSV2b_P.Joysticku_1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation[0];

      /* Gain: '<S8>/Joystick u_2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_2 =
        CA_CSE1_V1e_wo_LOSV2b_P.Joysticku_2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation[1];

      /* Gain: '<S8>/Joystick u_3' */
      CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_3 =
        CA_CSE1_V1e_wo_LOSV2b_P.Joysticku_3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation[2];

      /* Gain: '<S8>/Joystick u_4' */
      CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_4 =
        CA_CSE1_V1e_wo_LOSV2b_P.Joysticku_4_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation[3];

      /* Gain: '<S8>/Joystick u_5' */
      CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_5 =
        CA_CSE1_V1e_wo_LOSV2b_P.Joysticku_5_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation[4];

      /* Gain: '<S29>/Gain1' incorporates:
       *  Constant: '<S27>/psi_d'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Gain1 = CA_CSE1_V1e_wo_LOSV2b_P.Gain1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_P.psi_d_Value;
    }

    /* TransferFcn Block: '<S25>/Transfer Fcn' */
    CA_CSE1_V1e_wo_LOSV2b_B.TransferFcn = CA_CSE1_V1e_wo_LOSV2b_P.TransferFcn_C*
      CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn_CSTATE;

    /* TransferFcn Block: '<S25>/Transfer Fcn1' */
    CA_CSE1_V1e_wo_LOSV2b_B.TransferFcn1 =
      CA_CSE1_V1e_wo_LOSV2b_P.TransferFcn1_C*
      CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn1_CSTATE;

    /* TransferFcn Block: '<S25>/Transfer Fcn2' */
    CA_CSE1_V1e_wo_LOSV2b_B.TransferFcn2 =
      CA_CSE1_V1e_wo_LOSV2b_P.TransferFcn2_C*
      CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn2_CSTATE;

    /* MultiPortSwitch: '<S25>/Multiport Switch' incorporates:
     *  Constant: '<S25>/Enable eta_d LPF'
     *  Constant: '<S27>/x_d'
     *  Constant: '<S27>/y_d'
     */
    if ((int32_T)CA_CSE1_V1e_wo_LOSV2b_P.Enableeta_dLPF_Value == 0) {
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[0] =
        CA_CSE1_V1e_wo_LOSV2b_P.x_d_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[1] =
        CA_CSE1_V1e_wo_LOSV2b_P.y_d_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[2] = CA_CSE1_V1e_wo_LOSV2b_B.Gain1;
    } else {
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.TransferFcn;
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.TransferFcn1;
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.TransferFcn2;
    }

    /* Gain: '<S25>/eta_d DP N' */
    CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPN = CA_CSE1_V1e_wo_LOSV2b_P.eta_dDPN_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[0];

    /* Gain: '<S25>/eta_d DP E' */
    CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPE = CA_CSE1_V1e_wo_LOSV2b_P.eta_dDPE_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[1];

    /* Gain: '<S25>/eta_d DP Psi' */
    CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPPsi = CA_CSE1_V1e_wo_LOSV2b_P.eta_dDPPsi_Gain
      * CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[2];

    /* Gain: '<S31>/QTM In3' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn3 = CA_CSE1_V1e_wo_LOSV2b_P.QTMIn3_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[2];

    /* Gain: '<S31>/mm2m x' */
    CA_CSE1_V1e_wo_LOSV2b_B.mm2mx = CA_CSE1_V1e_wo_LOSV2b_P.mm2mx_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn3;

    /* Gain: '<S31>/QTM In4' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn4 = CA_CSE1_V1e_wo_LOSV2b_P.QTMIn4_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[3];

    /* Gain: '<S31>/mm2m y' */
    CA_CSE1_V1e_wo_LOSV2b_B.mm2my = CA_CSE1_V1e_wo_LOSV2b_P.mm2my_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn4;

    /* Gain: '<S31>/QTM In6' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn6 = CA_CSE1_V1e_wo_LOSV2b_P.QTMIn6_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[5];

    /* Gain: '<S31>/d2r yaw' */
    CA_CSE1_V1e_wo_LOSV2b_B.d2ryaw = CA_CSE1_V1e_wo_LOSV2b_P.d2ryaw_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn6;

    /* Outputs for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Constant: '<S5>/Enable Linear Simulator'
     *  EnablePort: '<S34>/Enable'
     */
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M) && rtmIsMajorTimeStep
        (CA_CSE1_V1e_wo_LOSV2b_M)) {
      if (CA_CSE1_V1e_wo_LOSV2b_P.EnableLinearSimulator_Value > 0.0) {
        if (CA_CSE1_V1e_wo_LOSV2b_DWork.LinearSimulator_MODE == SUBSYS_DISABLED)
        {
          /* Integrator Block: '<S46>/Integrator' */
          if (rtmIsFirstInitCond(CA_CSE1_V1e_wo_LOSV2b_M)) {
            CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[0] = 0.0;
            CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[1] = 0.0;
            CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[2] = 0.0;
          }

          CA_CSE1_V1e_wo_LOSV2b_DWork.Integrator_IWORK.IcNeedsLoading = 1;

          /* Integrator Block: '<S46>/Integrator1' */
          if (rtmIsFirstInitCond(CA_CSE1_V1e_wo_LOSV2b_M)) {
            CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[0] = 0.0;
            CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[1] = 0.0;
            CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[2] = 0.0;
          }

          CA_CSE1_V1e_wo_LOSV2b_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

          /* InitializeConditions for UnitDelay: '<S56>/Delay Input2' */
          CA_CSE1_V1e_wo_LOSV2b_DWork.DelayInput2_DSTATE =
            CA_CSE1_V1e_wo_LOSV2b_P.DelayInput2_X0;
          CA_CSE1_V1e_wo_LOSV2b_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (CA_CSE1_V1e_wo_LOSV2b_DWork.LinearSimulator_MODE == SUBSYS_ENABLED)
        {
          CA_CSE1_V1e_wo_LOSV2b_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (CA_CSE1_V1e_wo_LOSV2b_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* Gain: '<S48>/-N_r' incorporates:
         *  Constant: '<S48>/N_r'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.N_r = CA_CSE1_V1e_wo_LOSV2b_P.N_r_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.N_r_Value;

        /* Gain: '<S48>/-N_v' incorporates:
         *  Constant: '<S48>/N_v'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.N_v = CA_CSE1_V1e_wo_LOSV2b_P.N_v_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.N_v_Value;

        /* Gain: '<S48>/-X_u' incorporates:
         *  Constant: '<S48>/X_u'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.X_u = CA_CSE1_V1e_wo_LOSV2b_P.X_u_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.X_u_Value;

        /* Gain: '<S48>/-Y_v' incorporates:
         *  Constant: '<S48>/Y_v'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.Y_v = CA_CSE1_V1e_wo_LOSV2b_P.Y_v_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.Y_v_Value;

        /* Gain: '<S48>/-Y_vr' incorporates:
         *  Constant: '<S48>/Y_r'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.Y_vr = CA_CSE1_V1e_wo_LOSV2b_P.Y_vr_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.Y_r_Value;

        /* Reshape: '<S48>/Linear Dampning matrix' incorporates:
         *  Constant: '<S48>/D_L_12'
         *  Constant: '<S48>/D_L_13'
         *  Constant: '<S48>/D_L_21'
         *  Constant: '<S48>/D_L_31'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.X_u;
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[1] =
          CA_CSE1_V1e_wo_LOSV2b_P.D_L_21_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[2] =
          CA_CSE1_V1e_wo_LOSV2b_P.D_L_31_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[3] =
          CA_CSE1_V1e_wo_LOSV2b_P.D_L_12_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[4] =
          CA_CSE1_V1e_wo_LOSV2b_B.Y_v;
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[5] =
          CA_CSE1_V1e_wo_LOSV2b_B.N_v;
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[6] =
          CA_CSE1_V1e_wo_LOSV2b_P.D_L_13_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[7] =
          CA_CSE1_V1e_wo_LOSV2b_B.Y_vr;
        CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[8] =
          CA_CSE1_V1e_wo_LOSV2b_B.N_r;

        /* Constant: '<S49>/psi_0' */
        CA_CSE1_V1e_wo_LOSV2b_B.psi_0 = CA_CSE1_V1e_wo_LOSV2b_P.psi_0_Value;

        /* Constant: '<S49>/x_0' */
        CA_CSE1_V1e_wo_LOSV2b_B.x_0 = CA_CSE1_V1e_wo_LOSV2b_P.x_0_Value;

        /* Constant: '<S49>/y_0' */
        CA_CSE1_V1e_wo_LOSV2b_B.y_0 = CA_CSE1_V1e_wo_LOSV2b_P.y_0_Value;

        /* Constant: '<S50>/r_0' */
        CA_CSE1_V1e_wo_LOSV2b_B.r_0 = CA_CSE1_V1e_wo_LOSV2b_P.r_0_Value;

        /* Constant: '<S50>/u_0' */
        CA_CSE1_V1e_wo_LOSV2b_B.u_0 = CA_CSE1_V1e_wo_LOSV2b_P.u_0_Value;

        /* Constant: '<S50>/v_0' */
        CA_CSE1_V1e_wo_LOSV2b_B.v_0 = CA_CSE1_V1e_wo_LOSV2b_P.v_0_Value;
      }

      /* Integrator Block: '<S46>/Integrator'
       */
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &CA_CSE1_V1e_wo_L_PrevZCSigState.Integrator_Reset_ZCE,
                           CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_
            != 0.0 ||
            CA_CSE1_V1e_wo_LOSV2b_DWork.Integrator_IWORK.IcNeedsLoading) {
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[0] =
            CA_CSE1_V1e_wo_LOSV2b_B.u_0;
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[1] =
            CA_CSE1_V1e_wo_LOSV2b_B.v_0;
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[2] =
            CA_CSE1_V1e_wo_LOSV2b_B.r_0;
        }

        CA_CSE1_V1e_wo_LOSV2b_DWork.Integrator_IWORK.IcNeedsLoading = 0;
      }

      CA_CSE1_V1e_wo_LOSV2b_B.Integrator[0] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Integrator[1] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Integrator[2] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[2];

      /* Integrator Block: '<S46>/Integrator1'
       */
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &CA_CSE1_V1e_wo_L_PrevZCSigState.Integrator1_Reset_ZCE,
                           CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_
            != 0.0 ||
            CA_CSE1_V1e_wo_LOSV2b_DWork.Integrator1_IWORK.IcNeedsLoading) {
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[0] =
            CA_CSE1_V1e_wo_LOSV2b_B.x_0;
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[1] =
            CA_CSE1_V1e_wo_LOSV2b_B.y_0;
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[2] =
            CA_CSE1_V1e_wo_LOSV2b_B.psi_0;
        }

        CA_CSE1_V1e_wo_LOSV2b_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
      }

      CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[0] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[1] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[2] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[2];
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* Sum: '<S51>/M_11' incorporates:
         *  Constant: '<S51>/X_udot'
         *  Constant: '<S51>/m'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.M_11 = CA_CSE1_V1e_wo_LOSV2b_P.m_Value -
          CA_CSE1_V1e_wo_LOSV2b_P.X_udot_Value;

        /* Sum: '<S51>/M_22' incorporates:
         *  Constant: '<S51>/Y_vdot'
         *  Constant: '<S51>/m'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.M_22 = CA_CSE1_V1e_wo_LOSV2b_P.m_Value -
          CA_CSE1_V1e_wo_LOSV2b_P.Y_vdot_Value;

        /* Product: '<S51>/m x_g' incorporates:
         *  Constant: '<S51>/m'
         *  Constant: '<S51>/x_g'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.mx_g = CA_CSE1_V1e_wo_LOSV2b_P.m_Value *
          CA_CSE1_V1e_wo_LOSV2b_P.x_g_Value;

        /* Sum: '<S51>/M_32' incorporates:
         *  Constant: '<S51>/N_vdot'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.M_32 = CA_CSE1_V1e_wo_LOSV2b_B.mx_g -
          CA_CSE1_V1e_wo_LOSV2b_P.N_vdot_Value;

        /* Sum: '<S51>/M_23' incorporates:
         *  Constant: '<S51>/Y_rdot'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.M_23 = CA_CSE1_V1e_wo_LOSV2b_B.mx_g -
          CA_CSE1_V1e_wo_LOSV2b_P.Y_rdot_Value;

        /* Sum: '<S51>/M_33' incorporates:
         *  Constant: '<S51>/I_z'
         *  Constant: '<S51>/N_rdot'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.M_33 = CA_CSE1_V1e_wo_LOSV2b_P.I_z_Value -
          CA_CSE1_V1e_wo_LOSV2b_P.N_rdot_Value;

        /* Reshape: '<S51>/M' incorporates:
         *  Constant: '<S51>/M_12'
         *  Constant: '<S51>/M_13'
         *  Constant: '<S51>/M_21'
         *  Constant: '<S51>/M_31'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.M[0] = CA_CSE1_V1e_wo_LOSV2b_B.M_11;
        CA_CSE1_V1e_wo_LOSV2b_B.M[1] = CA_CSE1_V1e_wo_LOSV2b_P.M_21_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.M[2] = CA_CSE1_V1e_wo_LOSV2b_P.M_31_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.M[3] = CA_CSE1_V1e_wo_LOSV2b_P.M_12_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.M[4] = CA_CSE1_V1e_wo_LOSV2b_B.M_22;
        CA_CSE1_V1e_wo_LOSV2b_B.M[5] = CA_CSE1_V1e_wo_LOSV2b_B.M_32;
        CA_CSE1_V1e_wo_LOSV2b_B.M[6] = CA_CSE1_V1e_wo_LOSV2b_P.M_13_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.M[7] = CA_CSE1_V1e_wo_LOSV2b_B.M_23;
        CA_CSE1_V1e_wo_LOSV2b_B.M[8] = CA_CSE1_V1e_wo_LOSV2b_B.M_33;

        /* Product Block: '<S51>/Inverse' */
        {
          static const int_T dims[3] = { 3, 3, 3 };

          rt_MatDivRR_Dbl(CA_CSE1_V1e_wo_LOSV2b_B.Inverse,
                          CA_CSE1_V1e_wo_LOSV2b_B.M,
                          &CA_CSE1_V1e_wo_LOSV2b_DWork.Inverse_DWORK4[0],
                          (real_T*)&CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK1[0],
                          &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK2[0], (real_T*)
                          &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK3[0],
                          &dims[0]);
        }
      }

      /* Product: '<S46>/Product1' */
      for (i = 0; i < 3; i++) {
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.Integrator[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.Integrator[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.LinearDampningmatrix[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.Integrator[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[i];
      }

      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* Gain: '<S57>/-l_x1' incorporates:
         *  Constant: '<S57>/l_x1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_x1_j = CA_CSE1_V1e_wo_LOSV2b_P.l_x1_Gain_o *
          CA_CSE1_V1e_wo_LOSV2b_P.l_x1_Value_d;

        /* Gain: '<S57>/-l_y2' incorporates:
         *  Constant: '<S57>/l_y2'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_y2_p = CA_CSE1_V1e_wo_LOSV2b_P.l_y2_Gain_h *
          CA_CSE1_V1e_wo_LOSV2b_P.l_y2_Value_j;

        /* Gain: '<S57>/-l_x2' incorporates:
         *  Constant: '<S57>/l_x2'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_x2_o = CA_CSE1_V1e_wo_LOSV2b_P.l_x2_Gain_c *
          CA_CSE1_V1e_wo_LOSV2b_P.l_x2_Value_k;

        /* Reshape: '<S57>/3x5' incorporates:
         *  Constant: '<S57>/T_e11'
         *  Constant: '<S57>/T_e12'
         *  Constant: '<S57>/T_e13'
         *  Constant: '<S57>/T_e14'
         *  Constant: '<S57>/T_e15'
         *  Constant: '<S57>/T_e21'
         *  Constant: '<S57>/T_e22'
         *  Constant: '<S57>/T_e23'
         *  Constant: '<S57>/T_e24'
         *  Constant: '<S57>/T_e25'
         *  Constant: '<S57>/l_x3'
         *  Constant: '<S57>/l_y1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[0] = CA_CSE1_V1e_wo_LOSV2b_P.T_e11_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[1] = CA_CSE1_V1e_wo_LOSV2b_P.T_e21_Value_l;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[2] = CA_CSE1_V1e_wo_LOSV2b_P.l_y1_Value_n;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[3] = CA_CSE1_V1e_wo_LOSV2b_P.T_e12_Value_p;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[4] = CA_CSE1_V1e_wo_LOSV2b_P.T_e22_Value_k;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[5] = CA_CSE1_V1e_wo_LOSV2b_B.l_x1_j;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[6] = CA_CSE1_V1e_wo_LOSV2b_P.T_e13_Value_k;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[7] = CA_CSE1_V1e_wo_LOSV2b_P.T_e23_Value_e;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[8] = CA_CSE1_V1e_wo_LOSV2b_B.l_y2_p;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[9] = CA_CSE1_V1e_wo_LOSV2b_P.T_e14_Value_d;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[10] = CA_CSE1_V1e_wo_LOSV2b_P.T_e24_Value_g;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[11] = CA_CSE1_V1e_wo_LOSV2b_B.l_x2_o;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[12] = CA_CSE1_V1e_wo_LOSV2b_P.T_e15_Value_p;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[13] = CA_CSE1_V1e_wo_LOSV2b_P.T_e25_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_d[14] = CA_CSE1_V1e_wo_LOSV2b_P.l_x3_Value_b;

        /* Gain: '<S55>/Gain K_e1_hil' incorporates:
         *  Constant: '<S55>/K_e1_hil'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e1_hil =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e1_hil_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e1_hil_Value;

        /* Gain: '<S55>/Gain K_e2_hil' incorporates:
         *  Constant: '<S55>/K_e2_hil'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e2_hil =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e2_hil_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e2_hil_Value;

        /* Gain: '<S55>/Gain K_e3_hil' incorporates:
         *  Constant: '<S55>/K_e3_hil'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e3_hil =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e3_hil_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e3_hil_Value;

        /* Gain: '<S55>/Gain K_e4_hil' incorporates:
         *  Constant: '<S55>/K_e4_hil'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e4_hil =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e4_hil_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e4_hil_Value;

        /* Gain: '<S55>/Gain K_e5_hil' incorporates:
         *  Constant: '<S55>/K_e5_hil'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e5_hil =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e5_hil_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e5_hil_Value;

        /* Reshape: '<S55>/Thruster Gain matrix' incorporates:
         *  Constant: '<S55>/Constant41'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e1_hil;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[1] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[2] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[3] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[4] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[5] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[6] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e2_hil;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[7] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[8] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[9] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[10] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[11] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[12] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e3_hil;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[13] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[14] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[15] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[16] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[17] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[18] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e4_hil;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[19] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[20] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[21] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[22] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[23] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant41_Value;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[24] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e5_hil;

        /* S-Function (sfix_tsampmath) Block: '<S56>/sample time'
         */
        /* Sample Time Math Block: '<S56>/sample time'
         *
         * y = K         where     K = ( w * Ts )
         *
         * Input0  Data Type:  Floating Point real_T
         * Output0 Data Type:  Floating Point real_T
         *
         * Parameter: WtEt == Weighted Elapsed Time
         *   Data Type:  Floating Point real_T
         *
         */
        CA_CSE1_V1e_wo_LOSV2b_B.sampletime =
          CA_CSE1_V1e_wo_LOSV2b_P.sampletime_WtEt;

        /* UnitDelay: '<S56>/Delay Input2' */
        CA_CSE1_V1e_wo_LOSV2b_B.Yk1 =
          CA_CSE1_V1e_wo_LOSV2b_DWork.DelayInput2_DSTATE;
      }

      /* Fcn: '<S52>/R11' */
      CA_CSE1_V1e_wo_LOSV2b_B.R11_b = cos(CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[2]);

      /* Fcn: '<S52>/R21' */
      CA_CSE1_V1e_wo_LOSV2b_B.R21_a = sin(CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[2]);

      /* Fcn: '<S52>/R12' */
      CA_CSE1_V1e_wo_LOSV2b_B.R12_m = -1.0 * sin
        (CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[2]);

      /* Fcn: '<S52>/R22' */
      CA_CSE1_V1e_wo_LOSV2b_B.R22_h = cos(CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[2]);

      /* Reshape: '<S52>/R(psi)' incorporates:
       *  Constant: '<S52>/R13'
       *  Constant: '<S52>/R23'
       *  Constant: '<S52>/R31'
       *  Constant: '<S52>/R32'
       *  Constant: '<S52>/R33'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[0] = CA_CSE1_V1e_wo_LOSV2b_B.R11_b;
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[1] = CA_CSE1_V1e_wo_LOSV2b_B.R21_a;
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[2] = CA_CSE1_V1e_wo_LOSV2b_P.R31_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[3] = CA_CSE1_V1e_wo_LOSV2b_B.R12_m;
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[4] = CA_CSE1_V1e_wo_LOSV2b_B.R22_h;
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[5] = CA_CSE1_V1e_wo_LOSV2b_P.R32_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[6] = CA_CSE1_V1e_wo_LOSV2b_P.R13_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[7] = CA_CSE1_V1e_wo_LOSV2b_P.R23_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[8] = CA_CSE1_V1e_wo_LOSV2b_P.R33_Value;

      /* Product: '<S46>/Product3' */
      for (i = 0; i < 3; i++) {
        CA_CSE1_V1e_wo_LOSV2b_B.Product3[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Product3[i] = CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.Integrator[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product3[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Product3[i] = CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[i + 3]
          * CA_CSE1_V1e_wo_LOSV2b_B.Integrator[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product3[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Product3[i] = CA_CSE1_V1e_wo_LOSV2b_B.Rpsi[i + 6]
          * CA_CSE1_V1e_wo_LOSV2b_B.Integrator[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product3[i];
      }

      /* Gain: '<S34>/eta_surge_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.eta_surge_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.eta_surge_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[0];

      /* Gain: '<S34>/eta_sway_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.eta_sway_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.eta_sway_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[1];

      /* Gain: '<S34>/eta_yaw_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.eta_yaw_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Integrator1[2];

      /* Gain: '<S34>/etadot_surge_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.etadot_surge_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.etadot_surge_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product3[0];

      /* Gain: '<S34>/etadot_sway_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.etadot_sway_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.etadot_sway_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product3[1];

      /* Gain: '<S34>/etadot_yaw_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.etadot_yaw_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.etadot_yaw_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product3[2];

      /* Gain: '<S34>/nu_surge_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.nu_surge_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.nu_surge_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Integrator[0];

      /* Gain: '<S34>/nu_sway_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.nu_sway_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.nu_sway_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Integrator[1];

      /* Gain: '<S34>/nu_yaw_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.nu_yaw_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.nu_yaw_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Integrator[2];
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
      }
    }

    /* end of Outputs for SubSystem: '<S5>/Linear Simulator' */

    /* MultiPortSwitch: '<S4>/Eta Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)CA_CSE1_V1e_wo_LOSV2b_P.ControllerInputSelector_Value == 0) {
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[0] = CA_CSE1_V1e_wo_LOSV2b_B.mm2mx;
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[1] = CA_CSE1_V1e_wo_LOSV2b_B.mm2my;
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[2] = CA_CSE1_V1e_wo_LOSV2b_B.d2ryaw;
    } else {
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_surge_hil;
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_sway_hil;
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[2] = CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw_hil;
    }

    /* Gain: '<S4>/eta_surge' */
    CA_CSE1_V1e_wo_LOSV2b_B.eta_surge = CA_CSE1_V1e_wo_LOSV2b_P.eta_surge_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[0];

    /* Gain: '<S4>/eta_sway' */
    CA_CSE1_V1e_wo_LOSV2b_B.eta_sway = CA_CSE1_V1e_wo_LOSV2b_P.eta_sway_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[1];

    /* Gain: '<S4>/eta_yaw' */
    CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw = CA_CSE1_V1e_wo_LOSV2b_P.eta_yaw_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.EtaSwitch[2];

    /* Gain: '<S31>/QTM In8' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn8 = CA_CSE1_V1e_wo_LOSV2b_P.QTMIn8_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[7];

    /* Gain: '<S31>/d2r roll' */
    CA_CSE1_V1e_wo_LOSV2b_B.d2rroll = CA_CSE1_V1e_wo_LOSV2b_P.d2rroll_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn8;

    /* Gain: '<S31>/QTM In7' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn7 = CA_CSE1_V1e_wo_LOSV2b_P.QTMIn7_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[6];

    /* Gain: '<S31>/d2r pitch' */
    CA_CSE1_V1e_wo_LOSV2b_B.d2rpitch = CA_CSE1_V1e_wo_LOSV2b_P.d2rpitch_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn7;

    /* Trigonometry: '<S32>/sin(theta)' */
    CA_CSE1_V1e_wo_LOSV2b_B.sintheta[0] = sin(CA_CSE1_V1e_wo_LOSV2b_B.d2rroll);
    CA_CSE1_V1e_wo_LOSV2b_B.sintheta[1] = sin(CA_CSE1_V1e_wo_LOSV2b_B.d2rpitch);
    CA_CSE1_V1e_wo_LOSV2b_B.sintheta[2] = sin(CA_CSE1_V1e_wo_LOSV2b_B.d2ryaw);

    /* Trigonometry: '<S32>/cos(theta)' */
    CA_CSE1_V1e_wo_LOSV2b_B.costheta[0] = cos(CA_CSE1_V1e_wo_LOSV2b_B.d2rroll);
    CA_CSE1_V1e_wo_LOSV2b_B.costheta[1] = cos(CA_CSE1_V1e_wo_LOSV2b_B.d2rpitch);
    CA_CSE1_V1e_wo_LOSV2b_B.costheta[2] = cos(CA_CSE1_V1e_wo_LOSV2b_B.d2ryaw);

    /* Fcn: '<S32>/R11' */
    CA_CSE1_V1e_wo_LOSV2b_B.R11 = CA_CSE1_V1e_wo_LOSV2b_B.costheta[1] *
      CA_CSE1_V1e_wo_LOSV2b_B.costheta[2];

    /* Fcn: '<S32>/R21 ' */
    CA_CSE1_V1e_wo_LOSV2b_B.R21 = CA_CSE1_V1e_wo_LOSV2b_B.sintheta[0] *
      CA_CSE1_V1e_wo_LOSV2b_B.sintheta[1] * CA_CSE1_V1e_wo_LOSV2b_B.costheta[2]
      + (-CA_CSE1_V1e_wo_LOSV2b_B.costheta[0]) *
      CA_CSE1_V1e_wo_LOSV2b_B.sintheta[2];

    /* Fcn: '<S32>/R31 ' */
    CA_CSE1_V1e_wo_LOSV2b_B.R31 = CA_CSE1_V1e_wo_LOSV2b_B.costheta[0] *
      CA_CSE1_V1e_wo_LOSV2b_B.sintheta[1] * CA_CSE1_V1e_wo_LOSV2b_B.costheta[2]
      + CA_CSE1_V1e_wo_LOSV2b_B.sintheta[0] * CA_CSE1_V1e_wo_LOSV2b_B.sintheta[2];

    /* Fcn: '<S32>/R12' */
    CA_CSE1_V1e_wo_LOSV2b_B.R12 = CA_CSE1_V1e_wo_LOSV2b_B.costheta[1] *
      CA_CSE1_V1e_wo_LOSV2b_B.sintheta[2];

    /* Fcn: '<S32>/R22' */
    CA_CSE1_V1e_wo_LOSV2b_B.R22 = CA_CSE1_V1e_wo_LOSV2b_B.sintheta[0] *
      CA_CSE1_V1e_wo_LOSV2b_B.sintheta[1] * CA_CSE1_V1e_wo_LOSV2b_B.sintheta[2]
      + CA_CSE1_V1e_wo_LOSV2b_B.costheta[0] * CA_CSE1_V1e_wo_LOSV2b_B.costheta[2];

    /* Fcn: '<S32>/R32' */
    CA_CSE1_V1e_wo_LOSV2b_B.R32 = CA_CSE1_V1e_wo_LOSV2b_B.costheta[0] *
      CA_CSE1_V1e_wo_LOSV2b_B.sintheta[1] * CA_CSE1_V1e_wo_LOSV2b_B.sintheta[2]
      + (-CA_CSE1_V1e_wo_LOSV2b_B.sintheta[0]) *
      CA_CSE1_V1e_wo_LOSV2b_B.costheta[2];

    /* Fcn: '<S32>/R13' */
    CA_CSE1_V1e_wo_LOSV2b_B.R13 = -CA_CSE1_V1e_wo_LOSV2b_B.sintheta[1];

    /* Fcn: '<S32>/R23' */
    CA_CSE1_V1e_wo_LOSV2b_B.R23 = CA_CSE1_V1e_wo_LOSV2b_B.sintheta[0] *
      CA_CSE1_V1e_wo_LOSV2b_B.costheta[1];

    /* Fcn: '<S32>/R33' */
    CA_CSE1_V1e_wo_LOSV2b_B.R33 = CA_CSE1_V1e_wo_LOSV2b_B.costheta[0] *
      CA_CSE1_V1e_wo_LOSV2b_B.costheta[1];

    /* Reshape: '<S32>/Reshape 9x1->3x3' */
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[0] = CA_CSE1_V1e_wo_LOSV2b_B.R11;
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[1] = CA_CSE1_V1e_wo_LOSV2b_B.R21;
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[2] = CA_CSE1_V1e_wo_LOSV2b_B.R31;
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[3] = CA_CSE1_V1e_wo_LOSV2b_B.R12;
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[4] = CA_CSE1_V1e_wo_LOSV2b_B.R22;
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[5] = CA_CSE1_V1e_wo_LOSV2b_B.R32;
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[6] = CA_CSE1_V1e_wo_LOSV2b_B.R13;
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[7] = CA_CSE1_V1e_wo_LOSV2b_B.R23;
    CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[8] = CA_CSE1_V1e_wo_LOSV2b_B.R33;

    /* Concatenate: '<S31>/Matrix Concatenate' incorporates:
     *  Constant: '<S31>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[3 * i];
      tmp_1[1 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[3 * i + 1];
      tmp_1[2 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_P.Constant1_Value[3 * i];
      tmp_1[4 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_P.Constant1_Value[3 * i + 1];
      tmp_1[5 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&CA_CSE1_V1e_wo_LOSV2b_B.MatrixConcatenate2[0]), (void *)
           &tmp_1[0], 18U * sizeof(real_T));

    /* Concatenate: '<S31>/Matrix Concatenate1' incorporates:
     *  Constant: '<S31>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = CA_CSE1_V1e_wo_LOSV2b_P.Constant1_Value[3 * i];
      tmp_1[1 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_P.Constant1_Value[3 * i + 1];
      tmp_1[2 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[3 * i];
      tmp_1[4 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[3 * i + 1];
      tmp_1[5 + 6 * i] = CA_CSE1_V1e_wo_LOSV2b_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&CA_CSE1_V1e_wo_LOSV2b_B.MatrixConcatenate2[18]), (void *)
           &tmp_1[0], 18U * sizeof(real_T));

    /* Gain: '<S31>/QTM In5' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn5 = CA_CSE1_V1e_wo_LOSV2b_P.QTMIn5_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[4];

    /* Gain: '<S31>/mm2m z' */
    CA_CSE1_V1e_wo_LOSV2b_B.mm2mz = CA_CSE1_V1e_wo_LOSV2b_P.mm2mz_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn5;

    /* Derivative Block: '<S31>/Derivative' */
    {
      real_T t = CA_CSE1_V1e_wo_LOSV2b_M->Timing.t[0];
      real_T timeStampA =
        CA_CSE1_V1e_wo_LOSV2b_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB =
        CA_CSE1_V1e_wo_LOSV2b_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = CA_CSE1_V1e_wo_LOSV2b_B.Derivative;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank =
          &CA_CSE1_V1e_wo_LOSV2b_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        CA_CSE1_V1e_wo_LOSV2b_B.Derivative[0] = (CA_CSE1_V1e_wo_LOSV2b_B.mm2mx -
          *lastBank++) / deltaT;
        CA_CSE1_V1e_wo_LOSV2b_B.Derivative[1] = (CA_CSE1_V1e_wo_LOSV2b_B.mm2my -
          *lastBank++) / deltaT;
        CA_CSE1_V1e_wo_LOSV2b_B.Derivative[2] = (CA_CSE1_V1e_wo_LOSV2b_B.mm2mz -
          *lastBank++) / deltaT;
        CA_CSE1_V1e_wo_LOSV2b_B.Derivative[3] = (CA_CSE1_V1e_wo_LOSV2b_B.d2rroll
          - *lastBank++) / deltaT;
        CA_CSE1_V1e_wo_LOSV2b_B.Derivative[4] =
          (CA_CSE1_V1e_wo_LOSV2b_B.d2rpitch - *lastBank++) / deltaT;
        CA_CSE1_V1e_wo_LOSV2b_B.Derivative[5] = (CA_CSE1_V1e_wo_LOSV2b_B.d2ryaw
          - *lastBank++) / deltaT;
      }
    }

    /* Product: '<S31>/Product' */
    for (i = 0; i < 6; i++) {
      CA_CSE1_V1e_wo_LOSV2b_B.Product[i] = 0.0;
      for (tmp_4 = 0; tmp_4 < 6; tmp_4++) {
        CA_CSE1_V1e_wo_LOSV2b_B.Product[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.MatrixConcatenate2[6 * tmp_4 + i] *
          CA_CSE1_V1e_wo_LOSV2b_B.Derivative[tmp_4] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product[i];
      }
    }

    /* MultiPortSwitch: '<S4>/Nu Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)CA_CSE1_V1e_wo_LOSV2b_P.ControllerInputSelector_Value == 0) {
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[0] = CA_CSE1_V1e_wo_LOSV2b_B.Product[0];
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[1] = CA_CSE1_V1e_wo_LOSV2b_B.Product[1];
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[2] = CA_CSE1_V1e_wo_LOSV2b_B.Product[5];
    } else {
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[0] = CA_CSE1_V1e_wo_LOSV2b_B.nu_surge_hil;
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[1] = CA_CSE1_V1e_wo_LOSV2b_B.nu_sway_hil;
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[2] = CA_CSE1_V1e_wo_LOSV2b_B.nu_yaw_hil;
    }

    /* Gain: '<S4>/nu_surge' */
    CA_CSE1_V1e_wo_LOSV2b_B.nu_surge = CA_CSE1_V1e_wo_LOSV2b_P.nu_surge_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[0];

    /* Gain: '<S4>/nu_sway' */
    CA_CSE1_V1e_wo_LOSV2b_B.nu_sway = CA_CSE1_V1e_wo_LOSV2b_P.nu_sway_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[1];

    /* Gain: '<S4>/nu_yaw' */
    CA_CSE1_V1e_wo_LOSV2b_B.nu_yaw = CA_CSE1_V1e_wo_LOSV2b_P.nu_yaw_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.NuSwitch[2];
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
      /* RelationalOperator: '<S10>/Compare' incorporates:
       *  Constant: '<S10>/Constant'
       *  Constant: '<S1>/Control Mode'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Compare =
        (CA_CSE1_V1e_wo_LOSV2b_P.ControlMode_Value ==
         CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_c);
    }

    /* Outputs for enable SubSystem: '<S1>/DP control' incorporates:
     *  EnablePort: '<S7>/Enable'
     */
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M) && rtmIsMajorTimeStep
        (CA_CSE1_V1e_wo_LOSV2b_M)) {
      if (CA_CSE1_V1e_wo_LOSV2b_B.Compare > 0) {
        if (CA_CSE1_V1e_wo_LOSV2b_DWork.DPcontrol_MODE == SUBSYS_DISABLED) {
          /* InitializeConditions for Integrator: '<S13>/Integrator1' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[0] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator1_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[0] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator1' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[1] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator1_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[1] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator1' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[2] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator1_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[2] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC;

          /* Integrator Block: '<S11>/Integrator' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[0] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[1] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[2] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;

          /* InitializeConditions for Integrator: '<S13>/Integrator4' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[0] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator4_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator2' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator2_CSTATE[0] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator2_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator3' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator3_CSTATE[0] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator3_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator4' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[1] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator4_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator2' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator2_CSTATE[1] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator2_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator3' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator3_CSTATE[1] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator3_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator4' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[2] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator4_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator2' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator2_CSTATE[2] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator2_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator3' */
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator3_CSTATE[2] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator3_IC;
          CA_CSE1_V1e_wo_LOSV2b_DWork.DPcontrol_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (CA_CSE1_V1e_wo_LOSV2b_DWork.DPcontrol_MODE == SUBSYS_ENABLED) {
          CA_CSE1_V1e_wo_LOSV2b_DWork.DPcontrol_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (CA_CSE1_V1e_wo_LOSV2b_DWork.DPcontrol_MODE == SUBSYS_ENABLED) {
      /* Integrator: '<S13>/Integrator1' */
      CA_CSE1_V1e_wo_LOSV2b_B.eta_w[0] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[0];
      CA_CSE1_V1e_wo_LOSV2b_B.eta_w[1] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[1];
      CA_CSE1_V1e_wo_LOSV2b_B.eta_w[2] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[2];
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* ToFile Block: '<S7>/To File'
         */
        if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
          if (!(++CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_b.Decimation % 1) &&
              (CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_b.Count*4)+1 < 100000000
              ) {
            real_T u[4];
            FILE *fp = (FILE *)
              CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK_m.FilePtr;
            if (fp != (NULL)) {
              CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_b.Decimation = 0;
              u[0] = CA_CSE1_V1e_wo_LOSV2b_M->Timing.t[1];
              u[1] = CA_CSE1_V1e_wo_LOSV2b_B.eta_w[0];
              u[2] = CA_CSE1_V1e_wo_LOSV2b_B.eta_w[1];
              u[3] = CA_CSE1_V1e_wo_LOSV2b_B.eta_w[2];
              if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
                rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                                  "Error writing to MAT-file CSE1_data_eta_w.mat");
                return;
              }

              if (((++CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_b.Count)*4)+1 >=
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

        /* Constant: '<S7>/BT_power_limit' */
        CA_CSE1_V1e_wo_LOSV2b_B.BT_power_limit =
          CA_CSE1_V1e_wo_LOSV2b_P.BT_power_limit_Value;
      }

      /* Integrator: '<S13>/Integrator' */
      CA_CSE1_V1e_wo_LOSV2b_B.eta[0] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[0];
      CA_CSE1_V1e_wo_LOSV2b_B.eta[1] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[1];
      CA_CSE1_V1e_wo_LOSV2b_B.eta[2] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[2];

      /* Saturate: '<S21>/Saturation' */
      tmp = CA_CSE1_V1e_wo_LOSV2b_B.eta[2];
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_m = rt_SATURATE(tmp,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_LowerSat_l,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_UpperSat_g);

      /* Signum: '<S21>/Sign' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sign_k = rt_SIGNd_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.Saturation_m);

      /* Gain: '<S21>/Gain' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gain_k = CA_CSE1_V1e_wo_LOSV2b_P.Gain_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Sign_k;

      /* Sum: '<S21>/Sum1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_i = CA_CSE1_V1e_wo_LOSV2b_B.Saturation_m +
        CA_CSE1_V1e_wo_LOSV2b_B.Gain_k;

      /* Math: '<S21>/Math Function' incorporates:
       *  Constant: '<S21>/Constant'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.MathFunction = rt_rem_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.Sum1_i,
         CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_e);

      /* Sum: '<S21>/Sum' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_jb = CA_CSE1_V1e_wo_LOSV2b_B.MathFunction -
        CA_CSE1_V1e_wo_LOSV2b_B.Gain_k;

      /* MultiPortSwitch: '<S7>/Multiport Switch' incorporates:
       *  Constant: '<S7>/Enable Filter'
       */
      if ((int32_T)CA_CSE1_V1e_wo_LOSV2b_P.EnableFilter_Value == 0) {
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.eta_surge;
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[1] =
          CA_CSE1_V1e_wo_LOSV2b_B.eta_sway;
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[2] =
          CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.eta[0];
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[1] =
          CA_CSE1_V1e_wo_LOSV2b_B.eta[1];
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[2] =
          CA_CSE1_V1e_wo_LOSV2b_B.Sum_jb;
      }

      /* Gain: '<S11>/eta N' */
      CA_CSE1_V1e_wo_LOSV2b_B.etaN = CA_CSE1_V1e_wo_LOSV2b_P.etaN_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[0];

      /* Gain: '<S11>/eta E' */
      CA_CSE1_V1e_wo_LOSV2b_B.etaE = CA_CSE1_V1e_wo_LOSV2b_P.etaE_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[1];

      /* Gain: '<S11>/eta Psi' */
      CA_CSE1_V1e_wo_LOSV2b_B.etaPsi = CA_CSE1_V1e_wo_LOSV2b_P.etaPsi_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[2];

      /* Sum: '<S11>/Sum2' */
      CA_CSE1_V1e_wo_LOSV2b_B.regulationerror[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPN - CA_CSE1_V1e_wo_LOSV2b_B.etaN;
      CA_CSE1_V1e_wo_LOSV2b_B.regulationerror[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPE - CA_CSE1_V1e_wo_LOSV2b_B.etaE;
      CA_CSE1_V1e_wo_LOSV2b_B.regulationerror[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPPsi - CA_CSE1_V1e_wo_LOSV2b_B.etaPsi;

      /* Gain: '<S11>/Reg_e_N_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_N_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.Reg_e_N_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.regulationerror[0];

      /* Gain: '<S11>/Reg_e_E_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_E_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.Reg_e_E_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.regulationerror[1];

      /* Gain: '<S11>/Reg_e_Psi_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_Psi_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.Reg_e_Psi_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.regulationerror[2];
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* SignalConversion: '<S11>/TmpHiddenBufferAtTo FileInport1' */
        CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport_p[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_N_hil;
        CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport_p[1] =
          CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_E_hil;
        CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport_p[2] =
          CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_Psi_hil;

        /* ToFile Block: '<S11>/To File'
         */
        if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
          if (!(++CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_j.Decimation % 1) &&
              (CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_j.Count*4)+1 < 100000000
              ) {
            real_T u[4];
            FILE *fp = (FILE *)
              CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK_p.FilePtr;
            if (fp != (NULL)) {
              CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_j.Decimation = 0;
              u[0] = CA_CSE1_V1e_wo_LOSV2b_M->Timing.t[1];
              u[1] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport_p[0];
              u[2] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport_p[1];
              u[3] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport_p[2];
              if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
                rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                                  "Error writing to MAT-file CSE1_data_reg_error.mat");
                return;
              }

              if (((++CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_j.Count)*4)+1 >=
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

      /* Integrator Block: '<S11>/Integrator'
       */
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &CA_CSE1_V1e_wo_L_PrevZCSigState.Integrator_Reset_ZCE_b,
                           CA_CSE1_V1e_wo_LOSV2b_P.Reset_DP_integrator_Value);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || CA_CSE1_V1e_wo_LOSV2b_P.Reset_DP_integrator_Value != 0.0)
        {
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[0] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[1] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[2] =
            CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;
        }
      }

      CA_CSE1_V1e_wo_LOSV2b_B.Integrator_o[0] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Integrator_o[1] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Integrator_o[2] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[2];

      /* Integrator: '<S13>/Integrator4' */
      CA_CSE1_V1e_wo_LOSV2b_B.nu[0] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[0];
      CA_CSE1_V1e_wo_LOSV2b_B.nu[1] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[1];
      CA_CSE1_V1e_wo_LOSV2b_B.nu[2] =
        CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[2];

      /* MultiPortSwitch: '<S7>/Multiport Switch1' incorporates:
       *  Constant: '<S7>/Enable Filter'
       */
      if ((int32_T)CA_CSE1_V1e_wo_LOSV2b_P.EnableFilter_Value == 0) {
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.nu_surge;
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[1] =
          CA_CSE1_V1e_wo_LOSV2b_B.nu_sway;
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[2] =
          CA_CSE1_V1e_wo_LOSV2b_B.nu_yaw;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.nu[0];
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[1] =
          CA_CSE1_V1e_wo_LOSV2b_B.nu[1];
        CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[2] =
          CA_CSE1_V1e_wo_LOSV2b_B.nu[2];
      }

      /* Gain: '<S11>/K_d 1' */
      for (i = 0; i < 3; i++) {
        /* Gain: '<S11>/Kd' */
        CA_CSE1_V1e_wo_LOSV2b_B.Kd[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Kd[i] = CA_CSE1_V1e_wo_LOSV2b_P.Kd_Gain[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.Kd[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Kd[i] = CA_CSE1_V1e_wo_LOSV2b_P.Kd_Gain[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Kd[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Kd[i] = CA_CSE1_V1e_wo_LOSV2b_P.Kd_Gain[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch1[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Kd[i];

        /* Product: '<S11>/Product' incorporates:
         *  Constant: '<S11>/Kd_scale'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.Product_f[i] = CA_CSE1_V1e_wo_LOSV2b_B.Kd[i] *
          CA_CSE1_V1e_wo_LOSV2b_P.Kd_scale_Value;

        /* Gain: '<S11>/Ki' */
        CA_CSE1_V1e_wo_LOSV2b_B.Ki[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Ki[i] = CA_CSE1_V1e_wo_LOSV2b_P.Ki_Gain[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.Integrator_o[0] + CA_CSE1_V1e_wo_LOSV2b_B.Ki[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Ki[i] = CA_CSE1_V1e_wo_LOSV2b_P.Ki_Gain[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.Integrator_o[1] + CA_CSE1_V1e_wo_LOSV2b_B.Ki[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Ki[i] = CA_CSE1_V1e_wo_LOSV2b_P.Ki_Gain[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.Integrator_o[2] + CA_CSE1_V1e_wo_LOSV2b_B.Ki[i];

        /* Product: '<S11>/Product1' incorporates:
         *  Constant: '<S11>/Ki_scale'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_l[i] = CA_CSE1_V1e_wo_LOSV2b_B.Ki[i] *
          CA_CSE1_V1e_wo_LOSV2b_P.Ki_scale_Value;
      }

      CA_CSE1_V1e_wo_LOSV2b_B.K_d1 = CA_CSE1_V1e_wo_LOSV2b_P.K_d1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product_f[0];

      /* Gain: '<S11>/K_d 2' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_d2 = CA_CSE1_V1e_wo_LOSV2b_P.K_d2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product_f[1];

      /* Gain: '<S11>/K_d 3' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_d3 = CA_CSE1_V1e_wo_LOSV2b_P.K_d3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product_f[2];

      /* Gain: '<S11>/K_d 3 deg' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_d3deg = CA_CSE1_V1e_wo_LOSV2b_P.K_d3deg_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product_f[2];

      /* Gain: '<S11>/K_i 1' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_i1 = CA_CSE1_V1e_wo_LOSV2b_P.K_i1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_l[0];

      /* Gain: '<S11>/K_i 2' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_i2 = CA_CSE1_V1e_wo_LOSV2b_P.K_i2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_l[1];

      /* Gain: '<S11>/K_i 3' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_i3 = CA_CSE1_V1e_wo_LOSV2b_P.K_i3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_l[2];

      /* Gain: '<S11>/K_i 3 deg' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_i3deg = CA_CSE1_V1e_wo_LOSV2b_P.K_i3deg_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_l[2];

      /* Fcn: '<S11>/yaw angle' */
      CA_CSE1_V1e_wo_LOSV2b_B.psi = CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[2];

      /* Saturate: '<S17>/Saturation' */
      tmp = CA_CSE1_V1e_wo_LOSV2b_B.psi;
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_h = rt_SATURATE(tmp,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_LowerSat_n,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_UpperSat_o);

      /* Signum: '<S17>/Sign' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sign_i = rt_SIGNd_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.Saturation_h);

      /* Gain: '<S17>/Gain' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gain_h = CA_CSE1_V1e_wo_LOSV2b_P.Gain_Gain_d *
        CA_CSE1_V1e_wo_LOSV2b_B.Sign_i;

      /* Sum: '<S17>/Sum1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_h = CA_CSE1_V1e_wo_LOSV2b_B.Saturation_h +
        CA_CSE1_V1e_wo_LOSV2b_B.Gain_h;

      /* Math: '<S17>/Math Function' incorporates:
       *  Constant: '<S17>/Constant'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.MathFunction_a = rt_rem_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.Sum1_h,
         CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_g);

      /* Sum: '<S17>/Sum' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_k = CA_CSE1_V1e_wo_LOSV2b_B.MathFunction_a -
        CA_CSE1_V1e_wo_LOSV2b_B.Gain_h;

      /* Saturate: '<S16>/Saturation' */
      tmp = CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_Psi_hil;
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_m4 = rt_SATURATE(tmp,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_LowerSat_h,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_UpperSat_d);

      /* Signum: '<S16>/Sign' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sign_b = rt_SIGNd_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.Saturation_m4);

      /* Gain: '<S16>/Gain' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gain_ki = CA_CSE1_V1e_wo_LOSV2b_P.Gain_Gain_e *
        CA_CSE1_V1e_wo_LOSV2b_B.Sign_b;

      /* Sum: '<S16>/Sum1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_o = CA_CSE1_V1e_wo_LOSV2b_B.Saturation_m4 +
        CA_CSE1_V1e_wo_LOSV2b_B.Gain_ki;

      /* Math: '<S16>/Math Function' incorporates:
       *  Constant: '<S16>/Constant'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.MathFunction_d = rt_rem_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.Sum1_o,
         CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_i);

      /* Sum: '<S16>/Sum' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_o = CA_CSE1_V1e_wo_LOSV2b_B.MathFunction_d -
        CA_CSE1_V1e_wo_LOSV2b_B.Gain_ki;

      /* Fcn: '<S15>/Row1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Row1 = cos(CA_CSE1_V1e_wo_LOSV2b_B.Sum_k) *
        CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_N_hil + sin(CA_CSE1_V1e_wo_LOSV2b_B.Sum_k)
        * CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_E_hil;

      /* Fcn: '<S15>/Row2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Row2 = (-sin(CA_CSE1_V1e_wo_LOSV2b_B.Sum_k)) *
        CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_N_hil + cos(CA_CSE1_V1e_wo_LOSV2b_B.Sum_k)
        * CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_E_hil;

      /* Fcn: '<S15>/Row3' */
      CA_CSE1_V1e_wo_LOSV2b_B.Row3 = CA_CSE1_V1e_wo_LOSV2b_B.Sum_o;

      /* SignalConversion: '<S11>/TmpHiddenBufferAtKpInport1' */
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Row1;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Row2;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Row3;
      for (i = 0; i < 3; i++) {
        /* Gain: '<S11>/Kp' */
        CA_CSE1_V1e_wo_LOSV2b_B.Kp[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Kp[i] = CA_CSE1_V1e_wo_LOSV2b_P.Kp_Gain[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.Kp[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Kp[i] = CA_CSE1_V1e_wo_LOSV2b_P.Kp_Gain[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Kp[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Kp[i] = CA_CSE1_V1e_wo_LOSV2b_P.Kp_Gain[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Kp[i];

        /* Product: '<S11>/Product2' incorporates:
         *  Constant: '<S11>/Kp_scale'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.Product2_d[i] =
          CA_CSE1_V1e_wo_LOSV2b_P.Kp_scale_Value * CA_CSE1_V1e_wo_LOSV2b_B.Kp[i];
      }

      /* Gain: '<S11>/K_p 1' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_p1 = CA_CSE1_V1e_wo_LOSV2b_P.K_p1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product2_d[0];

      /* Gain: '<S11>/K_p 2' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_p2 = CA_CSE1_V1e_wo_LOSV2b_P.K_p2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product2_d[1];

      /* Gain: '<S11>/K_p 3' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_p3 = CA_CSE1_V1e_wo_LOSV2b_P.K_p3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product2_d[2];

      /* Gain: '<S11>/K_p 3 deg' */
      CA_CSE1_V1e_wo_LOSV2b_B.K_p3deg = CA_CSE1_V1e_wo_LOSV2b_P.K_p3deg_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product2_d[2];

      /* Gain: '<S11>/Reg_e_Psi_deg' */
      CA_CSE1_V1e_wo_LOSV2b_B.Reg_e_Psi_deg =
        CA_CSE1_V1e_wo_LOSV2b_P.Reg_e_Psi_deg_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.regulationerror[2];

      /* Sum: '<S11>/Sum3' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum3[0] = CA_CSE1_V1e_wo_LOSV2b_B.K_p1 +
        CA_CSE1_V1e_wo_LOSV2b_B.K_i1;
      CA_CSE1_V1e_wo_LOSV2b_B.Sum3[1] = CA_CSE1_V1e_wo_LOSV2b_B.K_p2 +
        CA_CSE1_V1e_wo_LOSV2b_B.K_i2;
      CA_CSE1_V1e_wo_LOSV2b_B.Sum3[2] = CA_CSE1_V1e_wo_LOSV2b_B.K_p3 +
        CA_CSE1_V1e_wo_LOSV2b_B.K_i3;

      /* Sum: '<S11>/Sum1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_g[0] = CA_CSE1_V1e_wo_LOSV2b_B.Sum3[0] -
        CA_CSE1_V1e_wo_LOSV2b_B.K_d1;
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_g[1] = CA_CSE1_V1e_wo_LOSV2b_B.Sum3[1] -
        CA_CSE1_V1e_wo_LOSV2b_B.K_d2;
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_g[2] = CA_CSE1_V1e_wo_LOSV2b_B.Sum3[2] -
        CA_CSE1_V1e_wo_LOSV2b_B.K_d3;

      /* Gain: '<S11>/eta Psi deg' */
      CA_CSE1_V1e_wo_LOSV2b_B.etaPsideg = CA_CSE1_V1e_wo_LOSV2b_P.etaPsideg_Gain
        * CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch_j[2];

      /* Gain: '<S7>/DP tau_surge' */
      CA_CSE1_V1e_wo_LOSV2b_B.DPtau_surge =
        CA_CSE1_V1e_wo_LOSV2b_P.DPtau_surge_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Sum1_g[0];

      /* Gain: '<S7>/DP tau_sway' */
      CA_CSE1_V1e_wo_LOSV2b_B.DPtau_sway =
        CA_CSE1_V1e_wo_LOSV2b_P.DPtau_sway_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Sum1_g[1];

      /* Gain: '<S7>/DP tau_yaw' */
      CA_CSE1_V1e_wo_LOSV2b_B.DPtau_yaw = CA_CSE1_V1e_wo_LOSV2b_P.DPtau_yaw_Gain
        * CA_CSE1_V1e_wo_LOSV2b_B.Sum1_g[2];
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* Gain: '<S12>/Gain K_e1_DP' incorporates:
         *  Constant: '<S12>/K_e1_DP'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e1_DP =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e1_DP_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e1_DP_Value;

        /* Gain: '<S12>/Gain K_e2_DP' incorporates:
         *  Constant: '<S12>/K_e2_DP'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e2_DP =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e2_DP_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e2_DP_Value;

        /* Gain: '<S12>/Gain K_e3_DP' incorporates:
         *  Constant: '<S12>/K_e3_DP'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e3_DP =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e3_DP_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e3_DP_Value;

        /* Gain: '<S12>/Gain K_e4_DP' incorporates:
         *  Constant: '<S12>/K_e4_DP'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e4_DP =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e4_DP_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e4_DP_Value;

        /* Gain: '<S12>/Gain K_e5_DP' incorporates:
         *  Constant: '<S12>/K_e5_DP'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e5_DP =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e5_DP_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e5_DP_Value;

        /* Reshape: '<S12>/Thruster Gain matrix' incorporates:
         *  Constant: '<S12>/Constant'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e1_DP;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[1] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[2] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[3] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[4] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[5] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[6] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e2_DP;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[7] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[8] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[9] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[10] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[11] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[12] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e3_DP;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[13] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[14] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[15] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[16] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[17] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[18] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e4_DP;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[19] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[20] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[21] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[22] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[23] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_cb;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f[24] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e5_DP;

        /* Product Block: '<S7>/K_e^-1' */
        {
          static const int_T dims[3] = { 5, 5, 5 };

          rt_MatDivRR_Dbl(CA_CSE1_V1e_wo_LOSV2b_B.K_e1_b,
                          CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_f,
                          &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK4_m[0], (real_T*)
                          &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK1[0],
                          &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK2[0], (real_T*)
                          &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK3[0],
                          &dims[0]);
        }

        /* Gain: '<S14>/-l_x1' incorporates:
         *  Constant: '<S14>/l_x1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_x1_jy = CA_CSE1_V1e_wo_LOSV2b_P.l_x1_Gain_a *
          CA_CSE1_V1e_wo_LOSV2b_P.l_x1_Value_l;

        /* Gain: '<S14>/-l_y2' incorporates:
         *  Constant: '<S14>/l_y2'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_y2_n = CA_CSE1_V1e_wo_LOSV2b_P.l_y2_Gain_j *
          CA_CSE1_V1e_wo_LOSV2b_P.l_y2_Value_o;

        /* Gain: '<S14>/-l_x2' incorporates:
         *  Constant: '<S14>/l_x2'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_x2_jn = CA_CSE1_V1e_wo_LOSV2b_P.l_x2_Gain_b *
          CA_CSE1_V1e_wo_LOSV2b_P.l_x2_Value_o;

        /* Reshape: '<S14>/3x5' incorporates:
         *  Constant: '<S14>/T_e11'
         *  Constant: '<S14>/T_e12'
         *  Constant: '<S14>/T_e13'
         *  Constant: '<S14>/T_e14'
         *  Constant: '<S14>/T_e15'
         *  Constant: '<S14>/T_e21'
         *  Constant: '<S14>/T_e22'
         *  Constant: '<S14>/T_e23'
         *  Constant: '<S14>/T_e24'
         *  Constant: '<S14>/T_e25'
         *  Constant: '<S14>/l_x3'
         *  Constant: '<S14>/l_y1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[0] = CA_CSE1_V1e_wo_LOSV2b_P.T_e11_Value_p;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[1] = CA_CSE1_V1e_wo_LOSV2b_P.T_e21_Value_c;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[2] = CA_CSE1_V1e_wo_LOSV2b_P.l_y1_Value_b;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[3] = CA_CSE1_V1e_wo_LOSV2b_P.T_e12_Value_i;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[4] = CA_CSE1_V1e_wo_LOSV2b_P.T_e22_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[5] = CA_CSE1_V1e_wo_LOSV2b_B.l_x1_jy;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[6] = CA_CSE1_V1e_wo_LOSV2b_P.T_e13_Value_d;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[7] = CA_CSE1_V1e_wo_LOSV2b_P.T_e23_Value_i;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[8] = CA_CSE1_V1e_wo_LOSV2b_B.l_y2_n;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[9] = CA_CSE1_V1e_wo_LOSV2b_P.T_e14_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[10] = CA_CSE1_V1e_wo_LOSV2b_P.T_e24_Value_h;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[11] = CA_CSE1_V1e_wo_LOSV2b_B.l_x2_jn;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[12] = CA_CSE1_V1e_wo_LOSV2b_P.T_e15_Value_g;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[13] = CA_CSE1_V1e_wo_LOSV2b_P.T_e25_Value_f;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_o[14] = CA_CSE1_V1e_wo_LOSV2b_P.l_x3_Value_h;

        /* S-Function (sdsppinv): '<S7>/T_e^+' */
        /* Copy input to temporary space */
        memcpy((void *)(&CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK1[0]), (void *)
               (&CA_CSE1_V1e_wo_LOSV2b_B.x5_o[0]), 15U * sizeof(real_T));

        /* Call SVD */
        i = MWDSP_SVD_D(&CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK1[0], 3, 5,
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_S[0],
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK3[0],
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_WORK[0],
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_U[0],
                        &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_V[0], 1);

        /* Only call 'pinv' function if SVD succeeded */
        if (i == 0) {
          MWDSPCG_Pseudoinverse_D(&CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_S[0],
            &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_U[0],
            &CA_CSE1_V1e_wo_LOSV2b_DWork.T_e_V[0],
            &CA_CSE1_V1e_wo_LOSV2b_B.T_e_a[0], (const int32_T)3, (const int32_T)
            5);
        }

        /* Product: '<S7>/Product' */
        for (i = 0; i < 5; i++) {
          for (tmp_4 = 0; tmp_4 < 3; tmp_4++) {
            CA_CSE1_V1e_wo_LOSV2b_B.Product_b[i + 5 * tmp_4] = 0.0;
            for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
              CA_CSE1_V1e_wo_LOSV2b_B.Product_b[i + 5 * tmp_4] =
                CA_CSE1_V1e_wo_LOSV2b_B.K_e1_b[5 * tmp_3 + i] *
                CA_CSE1_V1e_wo_LOSV2b_B.T_e_a[5 * tmp_4 + tmp_3] +
                CA_CSE1_V1e_wo_LOSV2b_B.Product_b[5 * tmp_4 + i];
            }
          }
        }
      }

      /* SignalConversion: '<S7>/TmpHiddenBufferAtProduct1Inport2' */
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.DPtau_surge;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.DPtau_sway;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.DPtau_yaw;

      /* Product: '<S7>/Product1' */
      for (i = 0; i < 5; i++) {
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.Product_b[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.Product_b[i + 5] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.Product_b[i + 10] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[i];
      }

      /* Gain: '<S7>/DP u_1' */
      CA_CSE1_V1e_wo_LOSV2b_B.DPu_1 = CA_CSE1_V1e_wo_LOSV2b_P.DPu_1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[0];

      /* Gain: '<S7>/DP u_2' */
      CA_CSE1_V1e_wo_LOSV2b_B.DPu_2 = CA_CSE1_V1e_wo_LOSV2b_P.DPu_2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[1];

      /* Gain: '<S7>/DP u_3' */
      CA_CSE1_V1e_wo_LOSV2b_B.DPu_3 = CA_CSE1_V1e_wo_LOSV2b_P.DPu_3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[2];

      /* Gain: '<S7>/DP u_4' */
      CA_CSE1_V1e_wo_LOSV2b_B.DPu_4 = CA_CSE1_V1e_wo_LOSV2b_P.DPu_4_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[3];

      /* Gain: '<S7>/DP u_5' */
      CA_CSE1_V1e_wo_LOSV2b_B.DPu_5 = CA_CSE1_V1e_wo_LOSV2b_P.DPu_5_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_be[4];
      for (i = 0; i < 3; i++) {
        /* Gain: '<S13>/Gain1' */
        CA_CSE1_V1e_wo_LOSV2b_B.Gain1_o[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Gain1_o[i] =
          CA_CSE1_V1e_wo_LOSV2b_P.Gain1_Gain_m[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.eta_w[0] + CA_CSE1_V1e_wo_LOSV2b_B.Gain1_o[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Gain1_o[i] =
          CA_CSE1_V1e_wo_LOSV2b_P.Gain1_Gain_m[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.eta_w[1] + CA_CSE1_V1e_wo_LOSV2b_B.Gain1_o[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Gain1_o[i] =
          CA_CSE1_V1e_wo_LOSV2b_P.Gain1_Gain_m[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.eta_w[2] + CA_CSE1_V1e_wo_LOSV2b_B.Gain1_o[i];

        /* Integrator: '<S13>/Integrator2' */
        CA_CSE1_V1e_wo_LOSV2b_B.xi_w[i] =
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator2_CSTATE[i];
      }

      /* Sum: '<S13>/Sum4' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum4[0] = CA_CSE1_V1e_wo_LOSV2b_B.eta_w[0] +
        CA_CSE1_V1e_wo_LOSV2b_B.eta[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum4[1] = CA_CSE1_V1e_wo_LOSV2b_B.eta_w[1] +
        CA_CSE1_V1e_wo_LOSV2b_B.eta[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum4[2] = CA_CSE1_V1e_wo_LOSV2b_B.eta_w[2] +
        CA_CSE1_V1e_wo_LOSV2b_B.Sum_jb;

      /* Sum: '<S13>/Sum2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum2_d[0] = CA_CSE1_V1e_wo_LOSV2b_B.eta_surge -
        CA_CSE1_V1e_wo_LOSV2b_B.Sum4[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum2_d[1] = CA_CSE1_V1e_wo_LOSV2b_B.eta_sway -
        CA_CSE1_V1e_wo_LOSV2b_B.Sum4[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum2_d[2] = CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw -
        CA_CSE1_V1e_wo_LOSV2b_B.Sum4[2];

      /* Saturate: '<S22>/Saturation' */
      tmp = CA_CSE1_V1e_wo_LOSV2b_B.Sum2_d[2];
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_n = rt_SATURATE(tmp,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_LowerSat_fw,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_UpperSat_a);

      /* Signum: '<S22>/Sign' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sign_h = rt_SIGNd_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.Saturation_n);

      /* Gain: '<S22>/Gain' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gain_f = CA_CSE1_V1e_wo_LOSV2b_P.Gain_Gain_g *
        CA_CSE1_V1e_wo_LOSV2b_B.Sign_h;

      /* Sum: '<S22>/Sum1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_c = CA_CSE1_V1e_wo_LOSV2b_B.Saturation_n +
        CA_CSE1_V1e_wo_LOSV2b_B.Gain_f;

      /* Math: '<S22>/Math Function' incorporates:
       *  Constant: '<S22>/Constant'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.MathFunction_j = rt_rem_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.Sum1_c,
         CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_h);

      /* Sum: '<S22>/Sum' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_i = CA_CSE1_V1e_wo_LOSV2b_B.MathFunction_j -
        CA_CSE1_V1e_wo_LOSV2b_B.Gain_f;

      /* SignalConversion: '<S13>/TmpHiddenBufferAtK11Inport1' */
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum2_d[0];
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum2_d[1];
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum_i;

      /* Fcn: '<S19>/Row1' */
      for (i = 0; i < 3; i++) {
        /* Gain: '<S13>/Gain2' */
        CA_CSE1_V1e_wo_LOSV2b_B.Gain2[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Gain2[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain2_Gain[i]
          * CA_CSE1_V1e_wo_LOSV2b_B.xi_w[0] + CA_CSE1_V1e_wo_LOSV2b_B.Gain2[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Gain2[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain2_Gain[i
          + 3] * CA_CSE1_V1e_wo_LOSV2b_B.xi_w[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Gain2[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Gain2[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain2_Gain[i
          + 6] * CA_CSE1_V1e_wo_LOSV2b_B.xi_w[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Gain2[i];

        /* Gain: '<S13>/K4' */
        CA_CSE1_V1e_wo_LOSV2b_B.K4[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.K4[i] = CA_CSE1_V1e_wo_LOSV2b_P.K4_Gain[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.K4[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K4[i] = CA_CSE1_V1e_wo_LOSV2b_P.K4_Gain[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.K4[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K4[i] = CA_CSE1_V1e_wo_LOSV2b_P.K4_Gain[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.K4[i];

        /* Integrator: '<S13>/Integrator3' */
        CA_CSE1_V1e_wo_LOSV2b_B.bias[i] =
          CA_CSE1_V1e_wo_LOSV2b_X.Integrator3_CSTATE[i];

        /* Gain: '<S13>/Gain6' */
        CA_CSE1_V1e_wo_LOSV2b_B.Gain6[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Gain6[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain6_Gain[i]
          * CA_CSE1_V1e_wo_LOSV2b_B.nu[0] + CA_CSE1_V1e_wo_LOSV2b_B.Gain6[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Gain6[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain6_Gain[i
          + 3] * CA_CSE1_V1e_wo_LOSV2b_B.nu[1] + CA_CSE1_V1e_wo_LOSV2b_B.Gain6[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Gain6[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain6_Gain[i
          + 6] * CA_CSE1_V1e_wo_LOSV2b_B.nu[2] + CA_CSE1_V1e_wo_LOSV2b_B.Gain6[i];
      }

      CA_CSE1_V1e_wo_LOSV2b_B.Row1_c = cos(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.K4[0] + sin(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.K4[1];

      /* Fcn: '<S19>/Row2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Row2_b = (-sin(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw)) *
        CA_CSE1_V1e_wo_LOSV2b_B.K4[0] + cos(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.K4[1];

      /* Fcn: '<S19>/Row3' */
      CA_CSE1_V1e_wo_LOSV2b_B.Row3_n = CA_CSE1_V1e_wo_LOSV2b_B.K4[2];

      /* Fcn: '<S20>/Row1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Row1_k = cos(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.bias[0] + sin(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.bias[1];

      /* Fcn: '<S20>/Row2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Row2_bv = (-sin(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw)) *
        CA_CSE1_V1e_wo_LOSV2b_B.bias[0] + cos(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.bias[1];

      /* Fcn: '<S20>/Row3' */
      CA_CSE1_V1e_wo_LOSV2b_B.Row3_l = CA_CSE1_V1e_wo_LOSV2b_B.bias[2];

      /* Sum: '<S13>/Sum1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_a[0] = CA_CSE1_V1e_wo_LOSV2b_B.Row1_k +
        CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_a[1] = CA_CSE1_V1e_wo_LOSV2b_B.Row2_bv +
        CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_a[2] = CA_CSE1_V1e_wo_LOSV2b_B.Row3_l +
        CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtProduct1Inpo_d[2];

      /* Sum: '<S13>/Sum8' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum8[0] = (CA_CSE1_V1e_wo_LOSV2b_B.Row1_c +
        CA_CSE1_V1e_wo_LOSV2b_B.Sum1_a[0]) - CA_CSE1_V1e_wo_LOSV2b_B.Gain6[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum8[1] = (CA_CSE1_V1e_wo_LOSV2b_B.Row2_b +
        CA_CSE1_V1e_wo_LOSV2b_B.Sum1_a[1]) - CA_CSE1_V1e_wo_LOSV2b_B.Gain6[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum8[2] = (CA_CSE1_V1e_wo_LOSV2b_B.Row3_n +
        CA_CSE1_V1e_wo_LOSV2b_B.Sum1_a[2]) - CA_CSE1_V1e_wo_LOSV2b_B.Gain6[2];

      /* Fcn: '<S18>/Fcn' */
      CA_CSE1_V1e_wo_LOSV2b_B.x_dot = cos(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.nu[0] - sin(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.nu[1];

      /* Fcn: '<S18>/Fcn1' */
      CA_CSE1_V1e_wo_LOSV2b_B.y_dot = sin(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.nu[0] + cos(CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw) *
        CA_CSE1_V1e_wo_LOSV2b_B.nu[1];

      /* Fcn: '<S18>/Fcn2' */
      CA_CSE1_V1e_wo_LOSV2b_B.psi_dot = CA_CSE1_V1e_wo_LOSV2b_B.nu[2];

      /* Sum: '<S13>/Sum3' */
      for (i = 0; i < 3; i++) {
        /* Gain: '<S13>/Gain3' */
        CA_CSE1_V1e_wo_LOSV2b_B.Gain3[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Gain3[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain3_Gain[i]
          * CA_CSE1_V1e_wo_LOSV2b_B.Sum8[0] + CA_CSE1_V1e_wo_LOSV2b_B.Gain3[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Gain3[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain3_Gain[i
          + 3] * CA_CSE1_V1e_wo_LOSV2b_B.Sum8[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Gain3[i];
        CA_CSE1_V1e_wo_LOSV2b_B.Gain3[i] = CA_CSE1_V1e_wo_LOSV2b_P.Gain3_Gain[i
          + 6] * CA_CSE1_V1e_wo_LOSV2b_B.Sum8[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Gain3[i];

        /* Gain: '<S13>/K11' */
        CA_CSE1_V1e_wo_LOSV2b_B.K11[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.K11[i] = CA_CSE1_V1e_wo_LOSV2b_P.K11_Gain[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.K11[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K11[i] = CA_CSE1_V1e_wo_LOSV2b_P.K11_Gain[i + 3]
          * CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.K11[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K11[i] = CA_CSE1_V1e_wo_LOSV2b_P.K11_Gain[i + 6]
          * CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.K11[i];

        /* Gain: '<S13>/K12' */
        CA_CSE1_V1e_wo_LOSV2b_B.K12[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.K12[i] = CA_CSE1_V1e_wo_LOSV2b_P.K12_Gain[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.K12[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K12[i] = CA_CSE1_V1e_wo_LOSV2b_P.K12_Gain[i + 3]
          * CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.K12[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K12[i] = CA_CSE1_V1e_wo_LOSV2b_P.K12_Gain[i + 6]
          * CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.K12[i];

        /* Gain: '<S13>/K2' */
        CA_CSE1_V1e_wo_LOSV2b_B.K2[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.K2[i] = CA_CSE1_V1e_wo_LOSV2b_P.K2_Gain[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.K2[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K2[i] = CA_CSE1_V1e_wo_LOSV2b_P.K2_Gain[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.K2[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K2[i] = CA_CSE1_V1e_wo_LOSV2b_P.K2_Gain[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.K2[i];

        /* Gain: '<S13>/K3' */
        CA_CSE1_V1e_wo_LOSV2b_B.K3[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.K3[i] = CA_CSE1_V1e_wo_LOSV2b_P.K3_Gain[i] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.K3[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K3[i] = CA_CSE1_V1e_wo_LOSV2b_P.K3_Gain[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.K3[i];
        CA_CSE1_V1e_wo_LOSV2b_B.K3[i] = CA_CSE1_V1e_wo_LOSV2b_P.K3_Gain[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtK11Inport1[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.K3[i];

        /* Sum: '<S13>/Sum5' */
        CA_CSE1_V1e_wo_LOSV2b_B.psi_WF[i] = CA_CSE1_V1e_wo_LOSV2b_B.K11[i] +
          CA_CSE1_V1e_wo_LOSV2b_B.eta_w[i];

        /* Sum: '<S13>/Sum6' */
        CA_CSE1_V1e_wo_LOSV2b_B.Sum6[i] = (CA_CSE1_V1e_wo_LOSV2b_B.K12[i] -
          CA_CSE1_V1e_wo_LOSV2b_B.Gain2[i]) - CA_CSE1_V1e_wo_LOSV2b_B.Gain1_o[i];

        /* Gain: '<S13>/inv(T_b)' */
        CA_CSE1_V1e_wo_LOSV2b_B.invT_b[i] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.invT_b[i] =
          CA_CSE1_V1e_wo_LOSV2b_P.invT_b_Gain[i] * CA_CSE1_V1e_wo_LOSV2b_B.bias
          [0] + CA_CSE1_V1e_wo_LOSV2b_B.invT_b[i];
        CA_CSE1_V1e_wo_LOSV2b_B.invT_b[i] =
          CA_CSE1_V1e_wo_LOSV2b_P.invT_b_Gain[i + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.bias[1] + CA_CSE1_V1e_wo_LOSV2b_B.invT_b[i];
        CA_CSE1_V1e_wo_LOSV2b_B.invT_b[i] =
          CA_CSE1_V1e_wo_LOSV2b_P.invT_b_Gain[i + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.bias[2] + CA_CSE1_V1e_wo_LOSV2b_B.invT_b[i];

        /* Sum: '<S13>/Sum7' */
        CA_CSE1_V1e_wo_LOSV2b_B.Sum7[i] = CA_CSE1_V1e_wo_LOSV2b_B.K3[i] -
          CA_CSE1_V1e_wo_LOSV2b_B.invT_b[i];
      }

      CA_CSE1_V1e_wo_LOSV2b_B.Sum3_k[0] = CA_CSE1_V1e_wo_LOSV2b_B.K2[0] +
        CA_CSE1_V1e_wo_LOSV2b_B.x_dot;
      CA_CSE1_V1e_wo_LOSV2b_B.Sum3_k[1] = CA_CSE1_V1e_wo_LOSV2b_B.K2[1] +
        CA_CSE1_V1e_wo_LOSV2b_B.y_dot;
      CA_CSE1_V1e_wo_LOSV2b_B.Sum3_k[2] = CA_CSE1_V1e_wo_LOSV2b_B.K2[2] +
        CA_CSE1_V1e_wo_LOSV2b_B.psi_dot;

      /* Saturate: '<S7>/Saturation' */
      tmp_0[0] = CA_CSE1_V1e_wo_LOSV2b_B.DPu_1;
      tmp_0[1] = CA_CSE1_V1e_wo_LOSV2b_B.DPu_2;
      tmp_0[2] = CA_CSE1_V1e_wo_LOSV2b_B.DPu_3;
      tmp_0[3] = CA_CSE1_V1e_wo_LOSV2b_B.DPu_4;
      tmp_0[4] = CA_CSE1_V1e_wo_LOSV2b_B.DPu_5;
      for (i = 0; i < 5; i++) {
        CA_CSE1_V1e_wo_LOSV2b_B.Saturation_f[i] = rt_SATURATE(tmp_0[i],
          CA_CSE1_V1e_wo_LOSV2b_P.Saturation_LowerSat_o,
          CA_CSE1_V1e_wo_LOSV2b_P.Saturation_UpperSat_ga);
      }

      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* Constant: '<S7>/VSP_speeds' */
        CA_CSE1_V1e_wo_LOSV2b_B.VSP_speeds =
          CA_CSE1_V1e_wo_LOSV2b_P.VSP_speeds_Value;
      }
    }

    /* end of Outputs for SubSystem: '<S1>/DP control' */

    /* MultiPortSwitch: '<S1>/Control Switch' incorporates:
     *  Constant: '<S1>/Control Mode'
     *  Constant: '<S26>/Accuracy  BT power'
     *  Constant: '<S26>/Accuracy  VSP speed'
     *  Constant: '<S28>/PS3_BT_Power'
     *  Constant: '<S28>/PS3_VSP_Speed'
     */
    switch ((int32_T)CA_CSE1_V1e_wo_LOSV2b_P.ControlMode_Value) {
     case 0:
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_1;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_2;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_3;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[3] =
        CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_4;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[4] =
        CA_CSE1_V1e_wo_LOSV2b_B.Accuracyu_5;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[5] =
        CA_CSE1_V1e_wo_LOSV2b_P.AccuracyBTpower_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[6] =
        CA_CSE1_V1e_wo_LOSV2b_P.AccuracyVSPspeed_Value;
      break;

     case 1:
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[0] = CA_CSE1_V1e_wo_LOSV2b_B.PS3u_1;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[1] = CA_CSE1_V1e_wo_LOSV2b_B.PS3u_2;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[2] = CA_CSE1_V1e_wo_LOSV2b_B.PS3u_3;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[3] = CA_CSE1_V1e_wo_LOSV2b_B.PS3u_4;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[4] = CA_CSE1_V1e_wo_LOSV2b_B.PS3u_5;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[5] =
        CA_CSE1_V1e_wo_LOSV2b_P.PS3_BT_Power_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[6] =
        CA_CSE1_V1e_wo_LOSV2b_P.PS3_VSP_Speed_Value;
      break;

     case 2:
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_1;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_2;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_3;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[3] =
        CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_4;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[4] =
        CA_CSE1_V1e_wo_LOSV2b_B.Joysticku_5;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[5] =
        CA_CSE1_V1e_wo_LOSV2b_P.PS3_BT_Power_Value;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[6] =
        CA_CSE1_V1e_wo_LOSV2b_P.PS3_VSP_Speed_Value;
      break;

     default:
      for (i = 0; i < 5; i++) {
        CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.Saturation_f[i];
      }

      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[5] =
        CA_CSE1_V1e_wo_LOSV2b_B.BT_power_limit;
      CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[6] =
        CA_CSE1_V1e_wo_LOSV2b_B.VSP_speeds;
      break;
    }

    /* Saturate: '<S1>/Saturation' */
    for (i = 0; i < 7; i++) {
      tmp = CA_CSE1_V1e_wo_LOSV2b_B.ControlSwitch[i];
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[i] = rt_SATURATE(tmp,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_LowerSat_f,
        CA_CSE1_V1e_wo_LOSV2b_P.Saturation_UpperSat_m);
    }

    /* Gain: '<S31>/QTM In9 Residual' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn9Residual =
      CA_CSE1_V1e_wo_LOSV2b_P.QTMIn9Residual_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[8];
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
      /* SignalConversion: '<Root>/TmpHiddenBufferAtTo FileInport1' */
      for (i = 0; i < 7; i++) {
        CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[i] =
          CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[i];
      }

      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[7] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_surge;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[8] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_sway;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[9] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_yaw;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[10] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPN;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[11] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPE;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[12] =
        CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPPsi;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[13] =
        CA_CSE1_V1e_wo_LOSV2b_B.QTMIn9Residual;

      /* ToFile Block: '<Root>/To File'
       */
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        if (!(++CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK.Decimation % 1) &&
            (CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK.Count*15)+1 < 100000000 )
        {
          real_T u[15];
          FILE *fp = (FILE *) CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = CA_CSE1_V1e_wo_LOSV2b_M->Timing.t[1];
            u[1] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtToFileInport1[13];
            if (fwrite(u, sizeof(real_T), 15, fp) != 15) {
              rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                                "Error writing to MAT-file CSE1_data.mat");
              return;
            }

            if (((++CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK.Count)*15)+1 >=
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

    /* Gain: '<S25>/eta_d Psi deg' */
    CA_CSE1_V1e_wo_LOSV2b_B.eta_dPsideg =
      CA_CSE1_V1e_wo_LOSV2b_P.eta_dPsideg_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.MultiportSwitch[2];

    /* Gain: '<S2>/psi_d' */
    CA_CSE1_V1e_wo_LOSV2b_B.psi_d = CA_CSE1_V1e_wo_LOSV2b_P.psi_d_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPPsi;

    /* Gain: '<S2>/x_d' */
    CA_CSE1_V1e_wo_LOSV2b_B.x_d = CA_CSE1_V1e_wo_LOSV2b_P.x_d_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPN;

    /* Gain: '<S2>/y_d' */
    CA_CSE1_V1e_wo_LOSV2b_B.y_d = CA_CSE1_V1e_wo_LOSV2b_P.y_d_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.eta_dDPE;
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
      /* Gain: '<S3>/Battery Bow Thruster' */
      CA_CSE1_V1e_wo_LOSV2b_B.BatteryBowThruster =
        CA_CSE1_V1e_wo_LOSV2b_P.BatteryBowThruster_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.SITzAI0;

      /* Gain: '<S3>/Battery Servo' */
      CA_CSE1_V1e_wo_LOSV2b_B.BatteryServo =
        CA_CSE1_V1e_wo_LOSV2b_P.BatteryServo_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.SITzAI1;

      /* Gain: '<S3>/Battery Main' */
      CA_CSE1_V1e_wo_LOSV2b_B.BatteryMain =
        CA_CSE1_V1e_wo_LOSV2b_P.BatteryMain_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.SITzAI2;
    }

    /* Gain: '<S31>/QTM In1 FPS' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn1FPS = CA_CSE1_V1e_wo_LOSV2b_P.QTMIn1FPS_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[0];

    /* Gain: '<S31>/QTM In2 Error' */
    CA_CSE1_V1e_wo_LOSV2b_B.QTMIn2Error =
      CA_CSE1_V1e_wo_LOSV2b_P.QTMIn2Error_Gain * CA_CSE1_V1e_wo_LOSV2b_B.QTMIn[1];

    /* Gain: '<S5>/u_1 plant' */
    CA_CSE1_V1e_wo_LOSV2b_B.u_1plant = CA_CSE1_V1e_wo_LOSV2b_P.u_1plant_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[0];

    /* Gain: '<S5>/u_2 plant' */
    CA_CSE1_V1e_wo_LOSV2b_B.u_2plant = CA_CSE1_V1e_wo_LOSV2b_P.u_2plant_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[1];

    /* Gain: '<S5>/u_3 plant' */
    CA_CSE1_V1e_wo_LOSV2b_B.u_3plant = CA_CSE1_V1e_wo_LOSV2b_P.u_3plant_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[2];

    /* Gain: '<S5>/u_4 plant' */
    CA_CSE1_V1e_wo_LOSV2b_B.u_4plant = CA_CSE1_V1e_wo_LOSV2b_P.u_4plant_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[3];

    /* Gain: '<S5>/u_5 plant' */
    CA_CSE1_V1e_wo_LOSV2b_B.u_5plant = CA_CSE1_V1e_wo_LOSV2b_P.u_5plant_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[4];

    /* Gain: '<S5>/BT power limit plant' */
    CA_CSE1_V1e_wo_LOSV2b_B.BTpowerlimitplant =
      CA_CSE1_V1e_wo_LOSV2b_P.BTpowerlimitplant_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[5];

    /* Gain: '<S5>/VSP speed plant' */
    CA_CSE1_V1e_wo_LOSV2b_B.VSPspeedplant =
      CA_CSE1_V1e_wo_LOSV2b_P.VSPspeedplant_Gain *
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_c[6];

    /* Outputs for enable SubSystem: '<S5>/CSE1' incorporates:
     *  Constant: '<S5>/Enable CSE1'
     *  EnablePort: '<S33>/Enable'
     */
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M) && rtmIsMajorTimeStep
        (CA_CSE1_V1e_wo_LOSV2b_M)) {
      if (CA_CSE1_V1e_wo_LOSV2b_P.EnableCSE1_Value > 0.0) {
        if (CA_CSE1_V1e_wo_LOSV2b_DWork.CSE1_MODE == SUBSYS_DISABLED) {
          CA_CSE1_V1e_wo_LOSV2b_DWork.CSE1_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (CA_CSE1_V1e_wo_LOSV2b_DWork.CSE1_MODE == SUBSYS_ENABLED) {
          CA_CSE1_V1e_wo_LOSV2b_DWork.CSE1_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (CA_CSE1_V1e_wo_LOSV2b_DWork.CSE1_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S35>/BT_D_Gain1' */
      CA_CSE1_V1e_wo_LOSV2b_B.BT_D_Gain1 =
        CA_CSE1_V1e_wo_LOSV2b_P.BT_D_Gain1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_5plant;

      /* Gain: '<S35>/BT_D_Gain2' */
      CA_CSE1_V1e_wo_LOSV2b_B.BT_D_Gain2 =
        CA_CSE1_V1e_wo_LOSV2b_P.BT_D_Gain2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_5plant;

      /* Sum: '<S35>/Add' incorporates:
       *  Constant: '<S35>/BT_Power_Offset1'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Add = (CA_CSE1_V1e_wo_LOSV2b_B.BT_D_Gain1 +
        CA_CSE1_V1e_wo_LOSV2b_P.BT_Power_Offset1_Value) +
        CA_CSE1_V1e_wo_LOSV2b_B.BT_D_Gain2;

      /* Gain: '<S35>/BT_L_Gain1' */
      CA_CSE1_V1e_wo_LOSV2b_B.BT_L_Gain1 =
        CA_CSE1_V1e_wo_LOSV2b_P.BT_L_Gain1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.BTpowerlimitplant;

      /* Gain: '<S35>/BT_L_Gain2' */
      CA_CSE1_V1e_wo_LOSV2b_B.BT_L_Gain2 =
        CA_CSE1_V1e_wo_LOSV2b_P.BT_L_Gain2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.BTpowerlimitplant;

      /* Gain: '<S35>/Neg' */
      CA_CSE1_V1e_wo_LOSV2b_B.Neg_d = CA_CSE1_V1e_wo_LOSV2b_P.Neg_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.BTpowerlimitplant;
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
      }

      /* Sum: '<S35>/Sum1' incorporates:
       *  Constant: '<S35>/BT_Power_Offset2'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum1_f = CA_CSE1_V1e_wo_LOSV2b_B.BT_L_Gain1 +
        CA_CSE1_V1e_wo_LOSV2b_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S39>/LowerRelop1' */
      CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1_n = (CA_CSE1_V1e_wo_LOSV2b_B.Add >
        CA_CSE1_V1e_wo_LOSV2b_B.Sum1_f);

      /* Sum: '<S35>/Sum2' incorporates:
       *  Constant: '<S35>/BT_Power_Offset3'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum2_m = CA_CSE1_V1e_wo_LOSV2b_B.BT_L_Gain2 +
        CA_CSE1_V1e_wo_LOSV2b_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S39>/UpperRelop' */
      CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop_d = (CA_CSE1_V1e_wo_LOSV2b_B.Add <
        CA_CSE1_V1e_wo_LOSV2b_B.Sum2_m);

      /* Switch: '<S39>/Switch' */
      if (CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop_d) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch_n = CA_CSE1_V1e_wo_LOSV2b_B.Sum2_m;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch_n = CA_CSE1_V1e_wo_LOSV2b_B.Add;
      }

      /* Switch: '<S39>/Switch2' */
      if (CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1_n) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2_l = CA_CSE1_V1e_wo_LOSV2b_B.Sum1_f;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2_l = CA_CSE1_V1e_wo_LOSV2b_B.Switch_n;
      }

      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
      }

      /* RelationalOperator: '<S40>/LowerRelop1' incorporates:
       *  Constant: '<S35>/Constant'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1_o = (CA_CSE1_V1e_wo_LOSV2b_B.u_5plant >
        CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_ef);

      /* RelationalOperator: '<S40>/UpperRelop' */
      CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop_o = (CA_CSE1_V1e_wo_LOSV2b_B.u_5plant <
        CA_CSE1_V1e_wo_LOSV2b_B.Neg_d);

      /* Switch: '<S40>/Switch' */
      if (CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop_o) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch_nw = CA_CSE1_V1e_wo_LOSV2b_B.Neg_d;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch_nw = CA_CSE1_V1e_wo_LOSV2b_B.u_5plant;
      }

      /* Switch: '<S40>/Switch2' incorporates:
       *  Constant: '<S35>/Constant'
       */
      if (CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1_o) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2_f =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_ef;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2_f = CA_CSE1_V1e_wo_LOSV2b_B.Switch_nw;
      }

      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
      }

      /* RelationalOperator: '<S41>/LowerRelop1' */
      CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1_j = (CA_CSE1_V1e_wo_LOSV2b_B.u_5plant >
        CA_CSE1_V1e_wo_LOSV2b_B.BTpowerlimitplant);

      /* RelationalOperator: '<S41>/UpperRelop' incorporates:
       *  Constant: '<S35>/Constant1'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop_h = (CA_CSE1_V1e_wo_LOSV2b_B.u_5plant <
        CA_CSE1_V1e_wo_LOSV2b_P.Constant1_Value_n);

      /* Switch: '<S41>/Switch' incorporates:
       *  Constant: '<S35>/Constant1'
       */
      if (CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop_h) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch_m =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant1_Value_n;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch_m = CA_CSE1_V1e_wo_LOSV2b_B.u_5plant;
      }

      /* Switch: '<S41>/Switch2' */
      if (CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1_j) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2_o =
          CA_CSE1_V1e_wo_LOSV2b_B.BTpowerlimitplant;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2_o = CA_CSE1_V1e_wo_LOSV2b_B.Switch_m;
      }

      /* Signum: '<S38>/Sign' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sign = rt_SIGNd_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.VSPspeedplant);

      /* Product: '<S38>/Product1' */
      CA_CSE1_V1e_wo_LOSV2b_B.PortVPS_X = CA_CSE1_V1e_wo_LOSV2b_B.u_2plant *
        CA_CSE1_V1e_wo_LOSV2b_B.Sign;

      /* Gain: '<S38>/-x' */
      CA_CSE1_V1e_wo_LOSV2b_B.PortVPS_X_a = CA_CSE1_V1e_wo_LOSV2b_P.x_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.PortVPS_X;

      /* Product: '<S38>/Product2' */
      CA_CSE1_V1e_wo_LOSV2b_B.PortVSP_Y = CA_CSE1_V1e_wo_LOSV2b_B.u_1plant *
        CA_CSE1_V1e_wo_LOSV2b_B.Sign;

      /* Gain: '<S38>/-y' */
      CA_CSE1_V1e_wo_LOSV2b_B.PortVSP_Y_a = CA_CSE1_V1e_wo_LOSV2b_P.y_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.PortVSP_Y;

      /* Fcn: '<S42>/x->r' */
      CA_CSE1_V1e_wo_LOSV2b_B.xr_l = rt_hypot_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.PortVPS_X_a,
         CA_CSE1_V1e_wo_LOSV2b_B.PortVSP_Y_a);

      /* Fcn: '<S42>/x->theta' */
      CA_CSE1_V1e_wo_LOSV2b_B.xtheta_b = rt_atan2_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.PortVSP_Y_a,
         CA_CSE1_V1e_wo_LOSV2b_B.PortVPS_X_a);

      /* Product: '<S38>/Product3' */
      CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_X = CA_CSE1_V1e_wo_LOSV2b_B.u_4plant *
        CA_CSE1_V1e_wo_LOSV2b_B.Sign;

      /* Product: '<S38>/Product4' */
      CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_Y = CA_CSE1_V1e_wo_LOSV2b_B.u_3plant *
        CA_CSE1_V1e_wo_LOSV2b_B.Sign;

      /* Fcn: '<S43>/x->r' */
      CA_CSE1_V1e_wo_LOSV2b_B.xr_a = rt_hypot_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_X,
         CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_Y);

      /* Fcn: '<S43>/x->theta' */
      CA_CSE1_V1e_wo_LOSV2b_B.xtheta_al = rt_atan2_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_Y,
         CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_X);

      /* Gain: '<S44>/Gain' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gain = CA_CSE1_V1e_wo_LOSV2b_P.Gain_Gain_k *
        CA_CSE1_V1e_wo_LOSV2b_B.xtheta_b;

      /* Gain: '<S45>/Gain' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gain_i = CA_CSE1_V1e_wo_LOSV2b_P.Gain_Gain_o *
        CA_CSE1_V1e_wo_LOSV2b_B.xtheta_al;

      /* Lookup2D: '<S38>/Servo1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo1_RowIdx[0]), 3, (const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo1_Table[0]), (const real_T)
        CA_CSE1_V1e_wo_LOSV2b_B.PortVPS_X_a, (const real_T)
        CA_CSE1_V1e_wo_LOSV2b_B.PortVSP_Y_a);

      /* Lookup2D: '<S38>/Servo2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo2_RowIdx[0]), 3, (const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo2_Table[0]), (const real_T)
        CA_CSE1_V1e_wo_LOSV2b_B.PortVPS_X_a, (const real_T)
        CA_CSE1_V1e_wo_LOSV2b_B.PortVSP_Y_a);

      /* Lookup2D: '<S38>/Servo3' */
      CA_CSE1_V1e_wo_LOSV2b_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo3_RowIdx[0]), 3, (const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo3_Table[0]), (const real_T)
        CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_X, (const real_T)
        CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_Y);

      /* Lookup2D: '<S38>/Servo4' */
      CA_CSE1_V1e_wo_LOSV2b_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo4_RowIdx[0]), 3, (const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&CA_CSE1_V1e_wo_LOSV2b_P.Servo4_Table[0]), (const real_T)
        CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_X, (const real_T)
        CA_CSE1_V1e_wo_LOSV2b_B.StarboardVSP_Y);

      /* Gain: '<S38>/VPS_Speed_Gain' */
      CA_CSE1_V1e_wo_LOSV2b_B.VPS_Speed_Gain =
        CA_CSE1_V1e_wo_LOSV2b_P.VPS_Speed_Gain_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.VSPspeedplant;

      /* Sum: '<S38>/Sum' incorporates:
       *  Constant: '<S38>/VPS_Power_Offset'
       */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_e = CA_CSE1_V1e_wo_LOSV2b_B.VPS_Speed_Gain +
        CA_CSE1_V1e_wo_LOSV2b_P.VPS_Power_Offset_Value;

      /* Gain: '<S38>/VSPS Port' */
      CA_CSE1_V1e_wo_LOSV2b_B.VSPSPort = CA_CSE1_V1e_wo_LOSV2b_P.VSPSPort_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Sum_e;

      /* Gain: '<S38>/VSPS Starboard' */
      CA_CSE1_V1e_wo_LOSV2b_B.VSPSStarboard =
        CA_CSE1_V1e_wo_LOSV2b_P.VSPSStarboard_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.Sum_e;
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* Gain: '<S37>/-l_x1' incorporates:
         *  Constant: '<S37>/l_x1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_x1_e = CA_CSE1_V1e_wo_LOSV2b_P.l_x1_Gain_f *
          CA_CSE1_V1e_wo_LOSV2b_P.l_x1_Value_j;

        /* Gain: '<S37>/-l_y2' incorporates:
         *  Constant: '<S37>/l_y2'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_y2_l = CA_CSE1_V1e_wo_LOSV2b_P.l_y2_Gain_c *
          CA_CSE1_V1e_wo_LOSV2b_P.l_y2_Value_g;

        /* Gain: '<S37>/-l_x2' incorporates:
         *  Constant: '<S37>/l_x2'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.l_x2_j = CA_CSE1_V1e_wo_LOSV2b_P.l_x2_Gain_j *
          CA_CSE1_V1e_wo_LOSV2b_P.l_x2_Value_f;

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
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[0] = CA_CSE1_V1e_wo_LOSV2b_P.T_e11_Value_i;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[1] = CA_CSE1_V1e_wo_LOSV2b_P.T_e21_Value_p;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[2] = CA_CSE1_V1e_wo_LOSV2b_P.l_y1_Value_a;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[3] = CA_CSE1_V1e_wo_LOSV2b_P.T_e12_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[4] = CA_CSE1_V1e_wo_LOSV2b_P.T_e22_Value_p;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[5] = CA_CSE1_V1e_wo_LOSV2b_B.l_x1_e;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[6] = CA_CSE1_V1e_wo_LOSV2b_P.T_e13_Value_l;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[7] = CA_CSE1_V1e_wo_LOSV2b_P.T_e23_Value_c;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[8] = CA_CSE1_V1e_wo_LOSV2b_B.l_y2_l;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[9] = CA_CSE1_V1e_wo_LOSV2b_P.T_e14_Value_g;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[10] =
          CA_CSE1_V1e_wo_LOSV2b_P.T_e24_Value_i;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[11] = CA_CSE1_V1e_wo_LOSV2b_B.l_x2_j;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[12] =
          CA_CSE1_V1e_wo_LOSV2b_P.T_e15_Value_c;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[13] =
          CA_CSE1_V1e_wo_LOSV2b_P.T_e25_Value_j;
        CA_CSE1_V1e_wo_LOSV2b_B.x5_df[14] = CA_CSE1_V1e_wo_LOSV2b_P.l_x3_Value_m;

        /* Gain: '<S36>/Gain K_e1_CSE1' incorporates:
         *  Constant: '<S36>/K_e1_CSE1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e1_CSE1 =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e1_CSE1_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e1_CSE1_Value;

        /* Gain: '<S36>/Gain K_e2_CSE1' incorporates:
         *  Constant: '<S36>/K_e2_CSE1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e2_CSE1 =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e2_CSE1_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e2_CSE1_Value;

        /* Gain: '<S36>/Gain K_e3_CSE1' incorporates:
         *  Constant: '<S36>/K_e3_CSE1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e3_CSE1 =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e3_CSE1_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e3_CSE1_Value;

        /* Gain: '<S36>/Gain K_e4_CSE1' incorporates:
         *  Constant: '<S36>/K_e4_CSE1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e4_CSE1 =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e4_CSE1_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e4_CSE1_Value;

        /* Gain: '<S36>/Gain K_e5_CSE1' incorporates:
         *  Constant: '<S36>/K_e5_CSE1'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.GainK_e5_CSE1 =
          CA_CSE1_V1e_wo_LOSV2b_P.GainK_e5_CSE1_Gain *
          CA_CSE1_V1e_wo_LOSV2b_P.K_e5_CSE1_Value;

        /* Reshape: '<S36>/Thruster Gain matrix' incorporates:
         *  Constant: '<S36>/Constant'
         */
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[0] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e1_CSE1;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[1] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[2] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[3] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[4] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[5] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[6] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e2_CSE1;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[7] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[8] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[9] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[10] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[11] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[12] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e3_CSE1;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[13] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[14] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[15] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[16] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[17] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[18] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e4_CSE1;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[19] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[20] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[21] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[22] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[23] =
          CA_CSE1_V1e_wo_LOSV2b_P.Constant_Value_o;
        CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[24] =
          CA_CSE1_V1e_wo_LOSV2b_B.GainK_e5_CSE1;
      }

      /* SignalConversion: '<S33>/TmpHiddenBufferAttau_cse1Inport3' */
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAttau_cse1Inport[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.u_1plant;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAttau_cse1Inport[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.u_2plant;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAttau_cse1Inport[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.u_3plant;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAttau_cse1Inport[3] =
        CA_CSE1_V1e_wo_LOSV2b_B.u_4plant;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAttau_cse1Inport[4] =
        CA_CSE1_V1e_wo_LOSV2b_B.u_5plant;

      /* Product: '<S33>/tau_cse1' */
      for (i = 0; i < 3; i++) {
        for (tmp_4 = 0; tmp_4 < 5; tmp_4++) {
          tmp_2[i + 3 * tmp_4] = 0.0;
          for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
            tmp_2[i + 3 * tmp_4] = CA_CSE1_V1e_wo_LOSV2b_B.x5_df[3 * tmp_3 + i] *
              CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_l[5 * tmp_4 + tmp_3] +
              tmp_2[3 * tmp_4 + i];
          }
        }
      }

      for (i = 0; i < 3; i++) {
        CA_CSE1_V1e_wo_LOSV2b_B.tau_cse1[i] = 0.0;
        for (tmp_4 = 0; tmp_4 < 5; tmp_4++) {
          CA_CSE1_V1e_wo_LOSV2b_B.tau_cse1[i] = tmp_2[3 * tmp_4 + i] *
            CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAttau_cse1Inport[tmp_4] +
            CA_CSE1_V1e_wo_LOSV2b_B.tau_cse1[i];
        }
      }

      /* Gain: '<S33>/CSE1 tau_surge' */
      CA_CSE1_V1e_wo_LOSV2b_B.CSE1tau_surge =
        CA_CSE1_V1e_wo_LOSV2b_P.CSE1tau_surge_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.tau_cse1[0];

      /* Gain: '<S33>/CSE1 tau_sway' */
      CA_CSE1_V1e_wo_LOSV2b_B.CSE1tau_sway =
        CA_CSE1_V1e_wo_LOSV2b_P.CSE1tau_sway_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.tau_cse1[1];

      /* Gain: '<S33>/CSE1 tau_yaw' */
      CA_CSE1_V1e_wo_LOSV2b_B.CSE1tau_yaw =
        CA_CSE1_V1e_wo_LOSV2b_P.CSE1tau_yaw_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.tau_cse1[2];
    }

    /* end of Outputs for SubSystem: '<S5>/CSE1' */
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void CA_CSE1_V1e_wo_LOSV2b_update(int_T tid)
{
  {
    real_T tmp[15];
    int32_T tmp_0;
    int32_T tmp_1;
    int32_T tmp_2;

    /* Update for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S34>/Enable'
     */
    if (CA_CSE1_V1e_wo_LOSV2b_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S47>/Gain u_1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_1 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_1plant;

      /* Gain: '<S47>/Gain u_2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_2 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_2plant;

      /* Gain: '<S47>/Gain u_3' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_3 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_3plant;

      /* Gain: '<S47>/Gain u_4' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_4 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_4_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_4plant;

      /* Gain: '<S47>/Gain BT power' */
      CA_CSE1_V1e_wo_LOSV2b_B.GainBTpower =
        CA_CSE1_V1e_wo_LOSV2b_P.GainBTpower_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.BTpowerlimitplant;

      /* Product: '<S56>/delta rise limit' */
      CA_CSE1_V1e_wo_LOSV2b_B.deltariselimit =
        CA_CSE1_V1e_wo_LOSV2b_B.GainBTpower * CA_CSE1_V1e_wo_LOSV2b_B.sampletime;

      /* Sum: '<S56>/Difference Inputs1' */
      CA_CSE1_V1e_wo_LOSV2b_B.UkYk1 = CA_CSE1_V1e_wo_LOSV2b_B.u_5plant -
        CA_CSE1_V1e_wo_LOSV2b_B.Yk1;

      /* RelationalOperator: '<S58>/LowerRelop1' */
      CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1 = (CA_CSE1_V1e_wo_LOSV2b_B.UkYk1 >
        CA_CSE1_V1e_wo_LOSV2b_B.deltariselimit);

      /* Gain: '<S47>/Neg' */
      CA_CSE1_V1e_wo_LOSV2b_B.Neg = CA_CSE1_V1e_wo_LOSV2b_P.Neg_Gain_o *
        CA_CSE1_V1e_wo_LOSV2b_B.GainBTpower;

      /* Product: '<S56>/delta fall limit' */
      CA_CSE1_V1e_wo_LOSV2b_B.deltafalllimit = CA_CSE1_V1e_wo_LOSV2b_B.Neg *
        CA_CSE1_V1e_wo_LOSV2b_B.sampletime;

      /* RelationalOperator: '<S58>/UpperRelop' */
      CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop = (CA_CSE1_V1e_wo_LOSV2b_B.UkYk1 <
        CA_CSE1_V1e_wo_LOSV2b_B.deltafalllimit);

      /* Switch: '<S58>/Switch' */
      if (CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch = CA_CSE1_V1e_wo_LOSV2b_B.deltafalllimit;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch = CA_CSE1_V1e_wo_LOSV2b_B.UkYk1;
      }

      /* Switch: '<S58>/Switch2' */
      if (CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2 = CA_CSE1_V1e_wo_LOSV2b_B.deltariselimit;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2 = CA_CSE1_V1e_wo_LOSV2b_B.Switch;
      }

      /* Sum: '<S56>/Difference Inputs2' */
      CA_CSE1_V1e_wo_LOSV2b_B.DifferenceInputs2 =
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2 + CA_CSE1_V1e_wo_LOSV2b_B.Yk1;

      /* Gain: '<S47>/Gain u_5' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_5 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_5_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.DifferenceInputs2;

      /* SignalConversion: '<S47>/TmpHiddenBufferAtT_e^+ K_e^-1 u_eInport3' */
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_1;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_2;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_3;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[3] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_4;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[4] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_5;

      /* Product: '<S47>/T_e^+ K_e^-1 u_e' */
      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          tmp[tmp_0 + 3 * tmp_2] = 0.0;
          for (tmp_1 = 0; tmp_1 < 5; tmp_1++) {
            tmp[tmp_0 + 3 * tmp_2] = CA_CSE1_V1e_wo_LOSV2b_B.x5_d[3 * tmp_1 +
              tmp_0] * CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[5 * tmp_2 +
              tmp_1] + tmp[3 * tmp_2 + tmp_0];
          }
        }
      }

      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[tmp_0] = 0.0;
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[tmp_0] = tmp[3 * tmp_2 + tmp_0] *
            CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[tmp_2] +
            CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[tmp_0];
        }
      }

      /* Gain: '<S47>/tau_surge_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.tau_surge_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.tau_surge_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[0];

      /* Gain: '<S47>/tau_sway_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.tau_sway_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.tau_sway_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[1];

      /* Gain: '<S47>/tau_yaw_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.tau_yaw_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.tau_yaw_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[2];

      /* Sum: '<S46>/Sum' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[0] = CA_CSE1_V1e_wo_LOSV2b_B.tau_surge_hil -
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[1] = CA_CSE1_V1e_wo_LOSV2b_B.tau_sway_hil -
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[2] = CA_CSE1_V1e_wo_LOSV2b_B.tau_yaw_hil -
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[2];

      /* Product: '<S46>/Product2' */
      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0] =
          CA_CSE1_V1e_wo_LOSV2b_B.Inverse[tmp_0] *
          CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0];
        CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0] =
          CA_CSE1_V1e_wo_LOSV2b_B.Inverse[tmp_0 + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0];
        CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0] =
          CA_CSE1_V1e_wo_LOSV2b_B.Inverse[tmp_0 + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0];
      }

      /* Fcn: '<S53>/x->r' */
      CA_CSE1_V1e_wo_LOSV2b_B.xr = rt_hypot_snf(CA_CSE1_V1e_wo_LOSV2b_B.u_2plant,
        CA_CSE1_V1e_wo_LOSV2b_B.u_1plant);

      /* Fcn: '<S53>/x->theta' */
      CA_CSE1_V1e_wo_LOSV2b_B.xtheta = rt_atan2_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.u_1plant, CA_CSE1_V1e_wo_LOSV2b_B.u_2plant);

      /* Fcn: '<S54>/x->r' */
      CA_CSE1_V1e_wo_LOSV2b_B.xr_g = rt_hypot_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.u_4plant, CA_CSE1_V1e_wo_LOSV2b_B.u_3plant);

      /* Fcn: '<S54>/x->theta' */
      CA_CSE1_V1e_wo_LOSV2b_B.xtheta_a = rt_atan2_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.u_3plant, CA_CSE1_V1e_wo_LOSV2b_B.u_4plant);

      /* Gain: '<S47>/VSP_angle_deg_port' */
      CA_CSE1_V1e_wo_LOSV2b_B.VSP_angle_deg_port =
        CA_CSE1_V1e_wo_LOSV2b_P.VSP_angle_deg_port_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.xtheta;

      /* Gain: '<S47>/VSP_angle_deg_stbd' */
      CA_CSE1_V1e_wo_LOSV2b_B.VSP_angle_deg_stbd =
        CA_CSE1_V1e_wo_LOSV2b_P.VSP_angle_deg_stbd_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.xtheta_a;
      if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
        /* Update for UnitDelay: '<S56>/Delay Input2' */
        CA_CSE1_V1e_wo_LOSV2b_DWork.DelayInput2_DSTATE =
          CA_CSE1_V1e_wo_LOSV2b_B.DifferenceInputs2;
      }
    }

    /* end of Update for SubSystem: '<S5>/Linear Simulator' */

    /* Derivative Block: '<S31>/Derivative' */
    {
      real_T timeStampA =
        CA_CSE1_V1e_wo_LOSV2b_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB =
        CA_CSE1_V1e_wo_LOSV2b_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank =
        &CA_CSE1_V1e_wo_LOSV2b_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = CA_CSE1_V1e_wo_LOSV2b_M->Timing.t[0];
      *lastBank++ = CA_CSE1_V1e_wo_LOSV2b_B.mm2mx;
      *lastBank++ = CA_CSE1_V1e_wo_LOSV2b_B.mm2my;
      *lastBank++ = CA_CSE1_V1e_wo_LOSV2b_B.mm2mz;
      *lastBank++ = CA_CSE1_V1e_wo_LOSV2b_B.d2rroll;
      *lastBank++ = CA_CSE1_V1e_wo_LOSV2b_B.d2rpitch;
      *lastBank++ = CA_CSE1_V1e_wo_LOSV2b_B.d2ryaw;
    }

    /* Update for enable SubSystem: '<S1>/DP control' incorporates:
     *  Update for EnablePort: '<S7>/Enable'
     */
    if (CA_CSE1_V1e_wo_LOSV2b_DWork.DPcontrol_MODE == SUBSYS_ENABLED) {
    }

    /* end of Update for SubSystem: '<S1>/DP control' */
    if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
    }
  }

  if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
    rt_ertODEUpdateContinuousStates(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo);
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
  if (!(++CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTick0))
    ++CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTickH0;
  CA_CSE1_V1e_wo_LOSV2b_M->Timing.t[0] =
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTick0 *
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize0 +
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTickH0 *
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(CA_CSE1_V1e_wo_LOSV2b_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTick1))
      ++CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTickH1;
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.t[1] =
      CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTick1 *
      CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize1 +
      CA_CSE1_V1e_wo_LOSV2b_M->Timing.clockTickH1 *
      CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void CA_CSE1_V1e_wo_LOSV2b_derivatives(void)
{
  {
    real_T tmp[15];
    int32_T tmp_0;
    int32_T tmp_1;
    int32_T tmp_2;

    /* TransferFcn Block: '<S25>/Transfer Fcn' */
    {
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->TransferFcn_CSTATE =
        CA_CSE1_V1e_wo_LOSV2b_P.x_d_Value;
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->TransferFcn_CSTATE +=
        (CA_CSE1_V1e_wo_LOSV2b_P.TransferFcn_A)*
        CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn_CSTATE;
    }

    /* TransferFcn Block: '<S25>/Transfer Fcn1' */
    {
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->TransferFcn1_CSTATE =
        CA_CSE1_V1e_wo_LOSV2b_P.y_d_Value;
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->TransferFcn1_CSTATE +=
        (CA_CSE1_V1e_wo_LOSV2b_P.TransferFcn1_A)*
        CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn1_CSTATE;
    }

    /* TransferFcn Block: '<S25>/Transfer Fcn2' */
    {
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->TransferFcn2_CSTATE =
        CA_CSE1_V1e_wo_LOSV2b_B.Gain1;
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->TransferFcn2_CSTATE +=
        (CA_CSE1_V1e_wo_LOSV2b_P.TransferFcn2_A)*
        CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn2_CSTATE;
    }

    /* Derivatives for enable SubSystem: '<S5>/Linear Simulator' */
    if (CA_CSE1_V1e_wo_LOSV2b_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S47>/Gain u_1' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_1 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_1_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_1plant;

      /* Gain: '<S47>/Gain u_2' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_2 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_2_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_2plant;

      /* Gain: '<S47>/Gain u_3' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_3 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_3_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_3plant;

      /* Gain: '<S47>/Gain u_4' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_4 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_4_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.u_4plant;

      /* Gain: '<S47>/Gain BT power' */
      CA_CSE1_V1e_wo_LOSV2b_B.GainBTpower =
        CA_CSE1_V1e_wo_LOSV2b_P.GainBTpower_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.BTpowerlimitplant;

      /* Product: '<S56>/delta rise limit' */
      CA_CSE1_V1e_wo_LOSV2b_B.deltariselimit =
        CA_CSE1_V1e_wo_LOSV2b_B.GainBTpower * CA_CSE1_V1e_wo_LOSV2b_B.sampletime;

      /* Sum: '<S56>/Difference Inputs1' */
      CA_CSE1_V1e_wo_LOSV2b_B.UkYk1 = CA_CSE1_V1e_wo_LOSV2b_B.u_5plant -
        CA_CSE1_V1e_wo_LOSV2b_B.Yk1;

      /* RelationalOperator: '<S58>/LowerRelop1' */
      CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1 = (CA_CSE1_V1e_wo_LOSV2b_B.UkYk1 >
        CA_CSE1_V1e_wo_LOSV2b_B.deltariselimit);

      /* Gain: '<S47>/Neg' */
      CA_CSE1_V1e_wo_LOSV2b_B.Neg = CA_CSE1_V1e_wo_LOSV2b_P.Neg_Gain_o *
        CA_CSE1_V1e_wo_LOSV2b_B.GainBTpower;

      /* Product: '<S56>/delta fall limit' */
      CA_CSE1_V1e_wo_LOSV2b_B.deltafalllimit = CA_CSE1_V1e_wo_LOSV2b_B.Neg *
        CA_CSE1_V1e_wo_LOSV2b_B.sampletime;

      /* RelationalOperator: '<S58>/UpperRelop' */
      CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop = (CA_CSE1_V1e_wo_LOSV2b_B.UkYk1 <
        CA_CSE1_V1e_wo_LOSV2b_B.deltafalllimit);

      /* Switch: '<S58>/Switch' */
      if (CA_CSE1_V1e_wo_LOSV2b_B.UpperRelop) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch = CA_CSE1_V1e_wo_LOSV2b_B.deltafalllimit;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch = CA_CSE1_V1e_wo_LOSV2b_B.UkYk1;
      }

      /* Switch: '<S58>/Switch2' */
      if (CA_CSE1_V1e_wo_LOSV2b_B.LowerRelop1) {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2 = CA_CSE1_V1e_wo_LOSV2b_B.deltariselimit;
      } else {
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2 = CA_CSE1_V1e_wo_LOSV2b_B.Switch;
      }

      /* Sum: '<S56>/Difference Inputs2' */
      CA_CSE1_V1e_wo_LOSV2b_B.DifferenceInputs2 =
        CA_CSE1_V1e_wo_LOSV2b_B.Switch2 + CA_CSE1_V1e_wo_LOSV2b_B.Yk1;

      /* Gain: '<S47>/Gain u_5' */
      CA_CSE1_V1e_wo_LOSV2b_B.Gainu_5 = CA_CSE1_V1e_wo_LOSV2b_P.Gainu_5_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.DifferenceInputs2;

      /* SignalConversion: '<S47>/TmpHiddenBufferAtT_e^+ K_e^-1 u_eInport3' */
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_1;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_2;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_3;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[3] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_4;
      CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[4] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gainu_5;

      /* Product: '<S47>/T_e^+ K_e^-1 u_e' */
      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          tmp[tmp_0 + 3 * tmp_2] = 0.0;
          for (tmp_1 = 0; tmp_1 < 5; tmp_1++) {
            tmp[tmp_0 + 3 * tmp_2] = CA_CSE1_V1e_wo_LOSV2b_B.x5_d[3 * tmp_1 +
              tmp_0] * CA_CSE1_V1e_wo_LOSV2b_B.ThrusterGainmatrix_e[5 * tmp_2 +
              tmp_1] + tmp[3 * tmp_2 + tmp_0];
          }
        }
      }

      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[tmp_0] = 0.0;
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[tmp_0] = tmp[3 * tmp_2 + tmp_0] *
            CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtT_eK_e1u_eInpo[tmp_2] +
            CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[tmp_0];
        }
      }

      /* Gain: '<S47>/tau_surge_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.tau_surge_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.tau_surge_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[0];

      /* Gain: '<S47>/tau_sway_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.tau_sway_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.tau_sway_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[1];

      /* Gain: '<S47>/tau_yaw_hil' */
      CA_CSE1_V1e_wo_LOSV2b_B.tau_yaw_hil =
        CA_CSE1_V1e_wo_LOSV2b_P.tau_yaw_hil_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.T_eK_e1u_e[2];

      /* Sum: '<S46>/Sum' */
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[0] = CA_CSE1_V1e_wo_LOSV2b_B.tau_surge_hil -
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[0];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[1] = CA_CSE1_V1e_wo_LOSV2b_B.tau_sway_hil -
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[1];
      CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[2] = CA_CSE1_V1e_wo_LOSV2b_B.tau_yaw_hil -
        CA_CSE1_V1e_wo_LOSV2b_B.Product1_b[2];

      /* Product: '<S46>/Product2' */
      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0] = 0.0;
        CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0] =
          CA_CSE1_V1e_wo_LOSV2b_B.Inverse[tmp_0] *
          CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[0] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0];
        CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0] =
          CA_CSE1_V1e_wo_LOSV2b_B.Inverse[tmp_0 + 3] *
          CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[1] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0];
        CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0] =
          CA_CSE1_V1e_wo_LOSV2b_B.Inverse[tmp_0 + 6] *
          CA_CSE1_V1e_wo_LOSV2b_B.Sum_j[2] +
          CA_CSE1_V1e_wo_LOSV2b_B.Product2[tmp_0];
      }

      /* Fcn: '<S53>/x->r' */
      CA_CSE1_V1e_wo_LOSV2b_B.xr = rt_hypot_snf(CA_CSE1_V1e_wo_LOSV2b_B.u_2plant,
        CA_CSE1_V1e_wo_LOSV2b_B.u_1plant);

      /* Fcn: '<S53>/x->theta' */
      CA_CSE1_V1e_wo_LOSV2b_B.xtheta = rt_atan2_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.u_1plant, CA_CSE1_V1e_wo_LOSV2b_B.u_2plant);

      /* Fcn: '<S54>/x->r' */
      CA_CSE1_V1e_wo_LOSV2b_B.xr_g = rt_hypot_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.u_4plant, CA_CSE1_V1e_wo_LOSV2b_B.u_3plant);

      /* Fcn: '<S54>/x->theta' */
      CA_CSE1_V1e_wo_LOSV2b_B.xtheta_a = rt_atan2_snf
        (CA_CSE1_V1e_wo_LOSV2b_B.u_3plant, CA_CSE1_V1e_wo_LOSV2b_B.u_4plant);

      /* Gain: '<S47>/VSP_angle_deg_port' */
      CA_CSE1_V1e_wo_LOSV2b_B.VSP_angle_deg_port =
        CA_CSE1_V1e_wo_LOSV2b_P.VSP_angle_deg_port_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.xtheta;

      /* Gain: '<S47>/VSP_angle_deg_stbd' */
      CA_CSE1_V1e_wo_LOSV2b_B.VSP_angle_deg_stbd =
        CA_CSE1_V1e_wo_LOSV2b_P.VSP_angle_deg_stbd_Gain *
        CA_CSE1_V1e_wo_LOSV2b_B.xtheta_a;

      /* Integrator Block: '<S46>/Integrator' */
      {
        if (CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE[0] =
            CA_CSE1_V1e_wo_LOSV2b_B.Product2[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE[0] =
            0.0;
        }

        if (CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE[1] =
            CA_CSE1_V1e_wo_LOSV2b_B.Product2[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE[1] =
            0.0;
        }

        if (CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE[2] =
            CA_CSE1_V1e_wo_LOSV2b_B.Product2[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE[2] =
            0.0;
        }
      }

      /* Integrator Block: '<S46>/Integrator1' */
      {
        if (CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE[0] =
            CA_CSE1_V1e_wo_LOSV2b_B.Product3[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE[0] =
            0.0;
        }

        if (CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE[1] =
            CA_CSE1_V1e_wo_LOSV2b_B.Product3[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE[1] =
            0.0;
        }

        if (CA_CSE1_V1e_wo_LOSV2b_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE[2] =
            CA_CSE1_V1e_wo_LOSV2b_B.Product3[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE[2] =
            0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_CA_CSE1_V1e_wo *)
                CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S5>/Linear Simulator' */

    /* Derivatives for enable SubSystem: '<S1>/DP control' */
    if (CA_CSE1_V1e_wo_LOSV2b_DWork.DPcontrol_MODE == SUBSYS_ENABLED) {
      /* Derivatives for Integrator: '<S13>/Integrator1' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE_i[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum6[0];

      /* Derivatives for Integrator: '<S13>/Integrator' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_o[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum3_k[0];

      /* Derivatives for Integrator: '<S13>/Integrator1' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE_i[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum6[1];

      /* Derivatives for Integrator: '<S13>/Integrator' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_o[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum3_k[1];

      /* Derivatives for Integrator: '<S13>/Integrator1' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator1_CSTATE_i[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum6[2];

      /* Derivatives for Integrator: '<S13>/Integrator' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_o[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum3_k[2];

      /* Integrator Block: '<S11>/Integrator' */
      {
        if (CA_CSE1_V1e_wo_LOSV2b_P.Reset_DP_integrator_Value== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_e[0] =
            CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_e[0] =
            0.0;
        }

        if (CA_CSE1_V1e_wo_LOSV2b_P.Reset_DP_integrator_Value== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_e[1] =
            CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_e[1] =
            0.0;
        }

        if (CA_CSE1_V1e_wo_LOSV2b_P.Reset_DP_integrator_Value== 0.0) {
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_e[2] =
            CA_CSE1_V1e_wo_LOSV2b_B.TmpHiddenBufferAtKpInport1[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CA_CSE1_V1e_wo *)
            CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator_CSTATE_e[2] =
            0.0;
        }
      }

      /* Derivatives for Integrator: '<S13>/Integrator4' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator4_CSTATE[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gain3[0];

      /* Derivatives for Integrator: '<S13>/Integrator2' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator2_CSTATE[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.psi_WF[0];

      /* Derivatives for Integrator: '<S13>/Integrator3' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator3_CSTATE[0] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum7[0];

      /* Derivatives for Integrator: '<S13>/Integrator4' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator4_CSTATE[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gain3[1];

      /* Derivatives for Integrator: '<S13>/Integrator2' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator2_CSTATE[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.psi_WF[1];

      /* Derivatives for Integrator: '<S13>/Integrator3' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator3_CSTATE[1] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum7[1];

      /* Derivatives for Integrator: '<S13>/Integrator4' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator4_CSTATE[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Gain3[2];

      /* Derivatives for Integrator: '<S13>/Integrator2' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator2_CSTATE[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.psi_WF[2];

      /* Derivatives for Integrator: '<S13>/Integrator3' */
      ((StateDerivatives_CA_CSE1_V1e_wo *)
        CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->Integrator3_CSTATE[2] =
        CA_CSE1_V1e_wo_LOSV2b_B.Sum7[2];
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_CA_CSE1_V1e_wo *)
                CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs)->
               Integrator1_CSTATE_i[0]);
        for (i=0; i < 18; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S1>/DP control' */
  }
}

/* Model initialize function */
void CA_CSE1_V1e_wo_LOSV2b_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)CA_CSE1_V1e_wo_LOSV2b_M,0,
                sizeof(RT_MODEL_CA_CSE1_V1e_wo_LOSV2b));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
                          &CA_CSE1_V1e_wo_LOSV2b_M->Timing.simTimeStep);
    rtsiSetTPtr(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo, &rtmGetTPtr
                (CA_CSE1_V1e_wo_LOSV2b_M));
    rtsiSetStepSizePtr(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
                       &CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize0);
    rtsiSetdXPtr(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
                 &CA_CSE1_V1e_wo_LOSV2b_M->ModelData.derivs);
    rtsiSetContStatesPtr(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
                         &CA_CSE1_V1e_wo_LOSV2b_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
      &CA_CSE1_V1e_wo_LOSV2b_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
                          (&rtmGetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M)));
    rtsiSetRTModelPtr(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
                      CA_CSE1_V1e_wo_LOSV2b_M);
  }

  rtsiSetSimTimeStep(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo, MAJOR_TIME_STEP);
  CA_CSE1_V1e_wo_LOSV2b_M->ModelData.intgData.y =
    CA_CSE1_V1e_wo_LOSV2b_M->ModelData.odeY;
  CA_CSE1_V1e_wo_LOSV2b_M->ModelData.intgData.f[0] =
    CA_CSE1_V1e_wo_LOSV2b_M->ModelData.odeF[0];
  CA_CSE1_V1e_wo_LOSV2b_M->ModelData.intgData.f[1] =
    CA_CSE1_V1e_wo_LOSV2b_M->ModelData.odeF[1];
  CA_CSE1_V1e_wo_LOSV2b_M->ModelData.intgData.f[2] =
    CA_CSE1_V1e_wo_LOSV2b_M->ModelData.odeF[2];
  CA_CSE1_V1e_wo_LOSV2b_M->ModelData.contStates = ((real_T *)
    &CA_CSE1_V1e_wo_LOSV2b_X);
  rtsiSetSolverData(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo, (void *)
                    &CA_CSE1_V1e_wo_LOSV2b_M->ModelData.intgData);
  rtsiSetSolverName(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = CA_CSE1_V1e_wo_LOSV2b_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.sampleTimes =
      (&CA_CSE1_V1e_wo_LOSV2b_M->Timing.sampleTimesArray[0]);
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.offsetTimes =
      (&CA_CSE1_V1e_wo_LOSV2b_M->Timing.offsetTimesArray[0]);

    /* task periods */
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.sampleTimes[0] = (0.0);
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.offsetTimes[0] = (0.0);
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(CA_CSE1_V1e_wo_LOSV2b_M, &CA_CSE1_V1e_wo_LOSV2b_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = CA_CSE1_V1e_wo_LOSV2b_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    CA_CSE1_V1e_wo_LOSV2b_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(CA_CSE1_V1e_wo_LOSV2b_M, -1);
  CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize0 = 0.1;
  CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(CA_CSE1_V1e_wo_LOSV2b_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, (NULL));
    rtliSetLogT(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, "");
    rtliSetLogX(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, "");
    rtliSetLogXFinal(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, "");
    rtliSetSigLog(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, 0);
    rtliSetLogDecimation(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, 1);
    rtliSetLogY(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(CA_CSE1_V1e_wo_LOSV2b_M->rtwLogInfo, (NULL));
  }

  CA_CSE1_V1e_wo_LOSV2b_M->solverInfoPtr = (&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo);
  CA_CSE1_V1e_wo_LOSV2b_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo, 0.1);
  rtsiSetSolverMode(&CA_CSE1_V1e_wo_LOSV2b_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  CA_CSE1_V1e_wo_LOSV2b_M->ModelData.blockIO = ((void *)
    &CA_CSE1_V1e_wo_LOSV2b_B);
  (void) memset(((void *) &CA_CSE1_V1e_wo_LOSV2b_B),0,
                sizeof(BlockIO_CA_CSE1_V1e_wo_LOSV2b));

  /* parameters */
  CA_CSE1_V1e_wo_LOSV2b_M->ModelData.defaultParam = ((real_T *)
    &CA_CSE1_V1e_wo_LOSV2b_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &CA_CSE1_V1e_wo_LOSV2b_X;
    CA_CSE1_V1e_wo_LOSV2b_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_CA_CSE1_V1e_wo));
  }

  /* states (dwork) */
  CA_CSE1_V1e_wo_LOSV2b_M->Work.dwork = ((void *) &CA_CSE1_V1e_wo_LOSV2b_DWork);
  (void) memset((void *)&CA_CSE1_V1e_wo_LOSV2b_DWork, 0,
                sizeof(D_Work_CA_CSE1_V1e_wo_LOSV2b));
  CA_CSE1_V1e_wo_L_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  CA_CSE1_V1e_wo_L_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  CA_CSE1_V1e_wo_L_PrevZCSigState.Integrator_Reset_ZCE_b = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void CA_CSE1_V1e_wo_LOSV2b_terminate(void)
{
  /* Terminate for enable SubSystem: '<S1>/DP control' */

  /* ToFile Block: '<S7>/To File' */
  {
    FILE *fp = (FILE *) CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK_m.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data_eta_w.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error closing MAT-file CSE1_data_eta_w.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error reopening MAT-file CSE1_data_eta_w.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4,
           CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_b.Count, "cse1_data")) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error writing header for cse1_data to MAT-file CSE1_data_eta_w.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error closing MAT-file CSE1_data_eta_w.mat");
        return;
      }

      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK_m.FilePtr = (NULL);
    }
  }

  /* ToFile Block: '<S11>/To File' */
  {
    FILE *fp = (FILE *) CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK_p.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data_reg_error.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error closing MAT-file CSE1_data_reg_error.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error reopening MAT-file CSE1_data_reg_error.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4,
           CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_j.Count,
           "cse1_data_reg_error")) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error writing header for cse1_data_reg_error to MAT-file CSE1_data_reg_error.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error closing MAT-file CSE1_data_reg_error.mat");
        return;
      }

      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK_p.FilePtr = (NULL);
    }
  }

  /* end of Terminate for SubSystem: '<S1>/DP control' */

  /* ToFile Block: '<Root>/To File' */
  {
    FILE *fp = (FILE *) CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error closing MAT-file CSE1_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error reopening MAT-file CSE1_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 15,
           CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK.Count, "cse1_data")) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error writing header for cse1_data to MAT-file CSE1_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error closing MAT-file CSE1_data.mat");
        return;
      }

      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  CA_CSE1_V1e_wo_LOSV2b_output(tid);
}

void MdlUpdate(int_T tid)
{
  CA_CSE1_V1e_wo_LOSV2b_update(tid);
}

void MdlInitializeSizes(void)
{
  CA_CSE1_V1e_wo_LOSV2b_M->Sizes.numContStates = (27);/* Number of continuous states */
  CA_CSE1_V1e_wo_LOSV2b_M->Sizes.numY = (0);/* Number of model outputs */
  CA_CSE1_V1e_wo_LOSV2b_M->Sizes.numU = (0);/* Number of model inputs */
  CA_CSE1_V1e_wo_LOSV2b_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  CA_CSE1_V1e_wo_LOSV2b_M->Sizes.numSampTimes = (2);/* Number of sample times */
  CA_CSE1_V1e_wo_LOSV2b_M->Sizes.numBlocks = (545);/* Number of blocks */
  CA_CSE1_V1e_wo_LOSV2b_M->Sizes.numBlockIO = (368);/* Number of block outputs */
  CA_CSE1_V1e_wo_LOSV2b_M->Sizes.numBlockPrms = (618);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* TransferFcn Block: '<S25>/Transfer Fcn' */
  CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn_CSTATE = 0.0;

  /* TransferFcn Block: '<S25>/Transfer Fcn1' */
  CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn1_CSTATE = 0.0;

  /* TransferFcn Block: '<S25>/Transfer Fcn2' */
  CA_CSE1_V1e_wo_LOSV2b_X.TransferFcn2_CSTATE = 0.0;

  /* Derivative Block: '<S31>/Derivative' */
  CA_CSE1_V1e_wo_LOSV2b_DWork.Derivative_RWORK.TimeStampA = rtInf;
  CA_CSE1_V1e_wo_LOSV2b_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(CA_CSE1_V1e_wo_LOSV2b_M)) {
    rtmSetFirstInitCond(CA_CSE1_V1e_wo_LOSV2b_M, 0);
  }
}

void MdlStart(void)
{
  {
    int32_T i;

    /* Create Identity Matrix for Block: '<S8>/K_e^-1' */
    {
      int_T i;
      real_T *dWork = &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK4[0];
      for (i = 0; i < 25; i++) {
        *dWork++ = 0.0;
      }

      dWork = &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK4[0];
      while (dWork < &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK4[0]+25) {
        *dWork = 1;
        dWork += 6;
      }
    }

    /* Start for enable SubSystem: '<S5>/Linear Simulator' */
    CA_CSE1_V1e_wo_LOSV2b_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

    /* Start for Constant: '<S49>/psi_0' */
    CA_CSE1_V1e_wo_LOSV2b_B.psi_0 = CA_CSE1_V1e_wo_LOSV2b_P.psi_0_Value;

    /* Start for Constant: '<S49>/x_0' */
    CA_CSE1_V1e_wo_LOSV2b_B.x_0 = CA_CSE1_V1e_wo_LOSV2b_P.x_0_Value;

    /* Start for Constant: '<S49>/y_0' */
    CA_CSE1_V1e_wo_LOSV2b_B.y_0 = CA_CSE1_V1e_wo_LOSV2b_P.y_0_Value;

    /* Start for Constant: '<S50>/r_0' */
    CA_CSE1_V1e_wo_LOSV2b_B.r_0 = CA_CSE1_V1e_wo_LOSV2b_P.r_0_Value;

    /* Start for Constant: '<S50>/u_0' */
    CA_CSE1_V1e_wo_LOSV2b_B.u_0 = CA_CSE1_V1e_wo_LOSV2b_P.u_0_Value;

    /* Start for Constant: '<S50>/v_0' */
    CA_CSE1_V1e_wo_LOSV2b_B.v_0 = CA_CSE1_V1e_wo_LOSV2b_P.v_0_Value;

    /* Create Identity Matrix for Block: '<S51>/Inverse' */
    {
      int_T i;
      real_T *dWork = &CA_CSE1_V1e_wo_LOSV2b_DWork.Inverse_DWORK4[0];
      for (i = 0; i < 9; i++) {
        *dWork++ = 0.0;
      }

      dWork = &CA_CSE1_V1e_wo_LOSV2b_DWork.Inverse_DWORK4[0];
      while (dWork < &CA_CSE1_V1e_wo_LOSV2b_DWork.Inverse_DWORK4[0]+9) {
        *dWork = 1;
        dWork += 4;
      }
    }

    /* Start for UnitDelay: '<S56>/Delay Input2' */
    CA_CSE1_V1e_wo_LOSV2b_B.Yk1 = CA_CSE1_V1e_wo_LOSV2b_P.DelayInput2_X0;

    /* Integrator Block: '<S46>/Integrator' */
    if (rtmIsFirstInitCond(CA_CSE1_V1e_wo_LOSV2b_M)) {
      CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[0] = 0.0;
      CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[1] = 0.0;
      CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE[2] = 0.0;
    }

    CA_CSE1_V1e_wo_LOSV2b_DWork.Integrator_IWORK.IcNeedsLoading = 1;

    /* Integrator Block: '<S46>/Integrator1' */
    if (rtmIsFirstInitCond(CA_CSE1_V1e_wo_LOSV2b_M)) {
      CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[0] = 0.0;
      CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[1] = 0.0;
      CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE[2] = 0.0;
    }

    CA_CSE1_V1e_wo_LOSV2b_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

    /* InitializeConditions for UnitDelay: '<S56>/Delay Input2' */
    CA_CSE1_V1e_wo_LOSV2b_DWork.DelayInput2_DSTATE =
      CA_CSE1_V1e_wo_LOSV2b_P.DelayInput2_X0;

    /* end of Start for SubSystem: '<S5>/Linear Simulator' */

    /* Start for enable SubSystem: '<S1>/DP control' */
    CA_CSE1_V1e_wo_LOSV2b_DWork.DPcontrol_MODE = SUBSYS_DISABLED;

    /* ToFile Block: '<S7>/To File' */
    {
      const char *fileName = "CSE1_data_eta_w.mat";
      FILE *fp;
      if ((fp = fopen(fileName, "wb")) == (NULL)) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error creating .mat file CSE1_data_eta_w.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp,4,0,"cse1_data")) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error writing mat file header to file CSE1_data_eta_w.mat");
        return;
      }

      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_b.Count = 0;
      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_b.Decimation = -1;
      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK_m.FilePtr = fp;
    }

    /* ToFile Block: '<S11>/To File' */
    {
      const char *fileName = "CSE1_data_reg_error.mat";
      FILE *fp;
      if ((fp = fopen(fileName, "wb")) == (NULL)) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error creating .mat file CSE1_data_reg_error.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp,4,0,"cse1_data_reg_error")) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error writing mat file header to file CSE1_data_reg_error.mat");
        return;
      }

      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_j.Count = 0;
      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK_j.Decimation = -1;
      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK_p.FilePtr = fp;
    }

    /* Create Identity Matrix for Block: '<S7>/K_e^-1' */
    {
      int_T i;
      real_T *dWork = &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK4_m[0];
      for (i = 0; i < 25; i++) {
        *dWork++ = 0.0;
      }

      dWork = &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK4_m[0];
      while (dWork < &CA_CSE1_V1e_wo_LOSV2b_DWork.K_e1_DWORK4_m[0]+25) {
        *dWork = 1;
        dWork += 6;
      }
    }

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[0] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[0] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[1] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[1] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator1_CSTATE_i[2] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_o[2] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC;

    /* Integrator Block: '<S11>/Integrator' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[0] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[1] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator_CSTATE_e[2] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator_IC_d;

    /* InitializeConditions for Integrator: '<S13>/Integrator4' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[0] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator4_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator2' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator2_CSTATE[0] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator2_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator3' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator3_CSTATE[0] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator3_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator4' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[1] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator4_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator2' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator2_CSTATE[1] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator2_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator3' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator3_CSTATE[1] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator3_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator4' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator4_CSTATE[2] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator4_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator2' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator2_CSTATE[2] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator2_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator3' */
    CA_CSE1_V1e_wo_LOSV2b_X.Integrator3_CSTATE[2] =
      CA_CSE1_V1e_wo_LOSV2b_P.Integrator3_IC;

    /* VirtualOutportStart for Outport: '<S7>/Thruster_Command_DP' */
    for (i = 0; i < 5; i++) {
      CA_CSE1_V1e_wo_LOSV2b_B.Saturation_f[i] =
        CA_CSE1_V1e_wo_LOSV2b_P.Thruster_Command_DP_Y0[i];
    }

    CA_CSE1_V1e_wo_LOSV2b_B.BT_power_limit =
      CA_CSE1_V1e_wo_LOSV2b_P.Thruster_Command_DP_Y0[5];
    CA_CSE1_V1e_wo_LOSV2b_B.VSP_speeds =
      CA_CSE1_V1e_wo_LOSV2b_P.Thruster_Command_DP_Y0[6];

    /* end of Start for SubSystem: '<S1>/DP control' */

    /* ToFile Block: '<Root>/To File' */
    {
      const char *fileName = "CSE1_data.mat";
      FILE *fp;
      if ((fp = fopen(fileName, "wb")) == (NULL)) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error creating .mat file CSE1_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp,15,0,"cse1_data")) {
        rtmSetErrorStatus(CA_CSE1_V1e_wo_LOSV2b_M,
                          "Error writing mat file header to file CSE1_data.mat");
        return;
      }

      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK.Count = 0;
      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_IWORK.Decimation = -1;
      CA_CSE1_V1e_wo_LOSV2b_DWork.ToFile_PWORK.FilePtr = fp;
    }

    /* Start for enable SubSystem: '<S5>/CSE1' */
    CA_CSE1_V1e_wo_LOSV2b_DWork.CSE1_MODE = SUBSYS_DISABLED;

    /* end of Start for SubSystem: '<S5>/CSE1' */
  }

  MdlInitialize();
}

RT_MODEL_CA_CSE1_V1e_wo_LOSV2b *CA_CSE1_V1e_wo_LOSV2b(void)
{
  CA_CSE1_V1e_wo_LOSV2b_initialize(1);
  return CA_CSE1_V1e_wo_LOSV2b_M;
}

void MdlTerminate(void)
{
  CA_CSE1_V1e_wo_LOSV2b_terminate();
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
#ifdef NI_ROOTMODEL_CA_CSE1_V1e_wo_LOSV2b
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

   case 16:
    //Type is renamed. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 17:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 18:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 19:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 20:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 21:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 41:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 42:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 50:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 51:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 52:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 53:
    //Type is matrix. Call GetValueByDataType on its contained type
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

   case 16:
    //Type is renamed. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 21:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 41:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 42:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 50:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 51:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 52:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 53:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern CA_CSE1_V1e_wo_LOSV2b_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Naviagation Systems/Qualisys 6 DOF/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(CA_CSE1_V1e_wo_LOSV2b_B.QTMIn, count, data[index++],
        34, 0);
    }
  } else {
    index += 9;
  }

  // HMI/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.SITzAI0, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.SITzAI1, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.SITzAI2, 0, data[index++],
      0, 0);
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
    ni_extout[index++] = NIRT_GetValueByDataType
      (&CA_CSE1_V1e_wo_LOSV2b_B.Switch2_l,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out1 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.Servo1,
      0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out2 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.Servo2,
      0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out3 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.Servo3,
      0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out4 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.Servo4,
      0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out6 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&CA_CSE1_V1e_wo_LOSV2b_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out7 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&CA_CSE1_V1e_wo_LOSV2b_B.VSPSStarboard,0,0,0);
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
  ni_extout[index++] = NIRT_GetValueByDataType
    (&CA_CSE1_V1e_wo_LOSV2b_B.Switch2_l,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out1 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.Servo1,0,
    0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out2 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.Servo2,0,
    0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out3 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.Servo3,0,
    0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out4 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.Servo4,0,
    0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out6 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CA_CSE1_V1e_wo_LOSV2b_B.VSPSPort,
    0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out7 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&CA_CSE1_V1e_wo_LOSV2b_B.VSPSStarboard,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "ca_cse1_v1e_wo_losv2b/Control Systems/Control Mode/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, ControlMode_Value), 31, 1, 2, 0, "", 0 },

  { 1, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u1_Value), 31, 1, 2, 2, "", 0 },

  { 2, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_1/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Accuracyu_1_Gain), 31, 1, 2, 4, "", 0 },

  { 3, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u2/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u2_Value), 31, 1, 2, 6, "", 0 },

  { 4, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_2/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Accuracyu_2_Gain), 31, 1, 2, 8, "", 0 },

  { 5, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u3/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u3_Value), 31, 1, 2, 10, "", 0 },

  { 6, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_3/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Accuracyu_3_Gain), 31, 1, 2, 12, "", 0 },

  { 7, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u4/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u4_Value), 31, 1, 2, 14, "", 0 },

  { 8, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_4/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Accuracyu_4_Gain), 31, 1, 2, 16, "", 0 },

  { 9, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u5/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u5_Value), 31, 1, 2, 18, "", 0 },

  { 10, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_5/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Accuracyu_5_Gain), 31, 1, 2, 20, "", 0 },

  { 11, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy  BT power/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, AccuracyBTpower_Value), 31, 1, 2,
    22, "", 0 },

  { 12, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy  VSP speed/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, AccuracyVSPspeed_Value), 31, 1, 2,
    24, "", 0 },

  { 13, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/JS_L_Y/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, JS_L_Y_Value), 31, 1, 2, 26, "", 0 },

  { 14, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_L_Y/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Scaling_JS_L_Y_Gain), 31, 1, 2, 28,
    "", 0 },

  { 15,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, PS3u_1_Gain), 31, 1, 2, 30, "", 0
  },

  { 16, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/JS_L_X/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, JS_L_X_Value), 31, 1, 2, 32, "", 0 },

  { 17, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_L_X/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Scaling_JS_L_X_Gain), 31, 1, 2, 34,
    "", 0 },

  { 18,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, PS3u_2_Gain), 31, 1, 2, 36, "", 0
  },

  { 19, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/JS_R_Y/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, JS_R_Y_Value), 31, 1, 2, 38, "", 0 },

  { 20, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_R_Y/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Scaling_JS_R_Y_Gain), 31, 1, 2, 40,
    "", 0 },

  { 21,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, PS3u_3_Gain), 31, 1, 2, 42, "", 0
  },

  { 22, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/JS_R_X/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, JS_R_X_Value), 31, 1, 2, 44, "", 0 },

  { 23, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_R_X/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Scaling_JS_R_X_Gain), 31, 1, 2, 46,
    "", 0 },

  { 24,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_4/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, PS3u_4_Gain), 31, 1, 2, 48, "", 0
  },

  { 25, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/L2/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, L2_Value), 31, 1, 2, 50, "", 0 },

  { 26, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/R2/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, R2_Value), 31, 1, 2, 52, "", 0 },

  { 27,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_5/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, PS3u_5_Gain), 31, 1, 2, 54, "", 0
  },

  { 28, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3_BT_Power/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, PS3_BT_Power_Value), 31, 1, 2, 56, "", 0 },

  { 29, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3_VSP_Speed/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, PS3_VSP_Speed_Value), 31, 1, 2, 58, "", 0
  },

  { 30,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e1_joystick/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e1_joystick_Value), 31, 1, 2, 60,
    "", 0 },

  { 31,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e1_joystick/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e1_joystick_Gain), 31, 1, 2,
    62, "", 0 },

  { 32,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Constant/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value), 31, 1, 2, 64, "",
    0 },

  { 33,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e2_joystick/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e2_joystick_Value), 31, 1, 2, 66,
    "", 0 },

  { 34,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e2_joystick/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e2_joystick_Gain), 31, 1, 2,
    68, "", 0 },

  { 35,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e3_joystick/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e3_joystick_Value), 31, 1, 2, 70,
    "", 0 },

  { 36,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e3_joystick/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e3_joystick_Gain), 31, 1, 2,
    72, "", 0 },

  { 37,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e4_joystick/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e4_joystick_Value), 31, 1, 2, 74,
    "", 0 },

  { 38,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e4_joystick/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e4_joystick_Gain), 31, 1, 2,
    76, "", 0 },

  { 39,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e5_joystick/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e5_joystick_Value), 31, 1, 2, 78,
    "", 0 },

  { 40,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e5_joystick/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e5_joystick_Gain), 31, 1, 2,
    80, "", 0 },

  { 41, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e11/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e11_Value), 31, 1, 2, 82, "", 0
  },

  { 42, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e21/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e21_Value), 31, 1, 2, 84, "", 0
  },

  { 43, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_y1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y1_Value), 31, 1, 2, 86, "", 0 },

  { 44, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e12/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e12_Value), 31, 1, 2, 88, "", 0
  },

  { 45, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e22/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e22_Value), 31, 1, 2, 90, "", 0
  },

  { 46, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_x1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x1_Value), 31, 1, 2, 92, "", 0 },

  { 47, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_x1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x1_Gain), 31, 1, 2, 94, "", 0 },

  { 48, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e13/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e13_Value), 31, 1, 2, 96, "", 0
  },

  { 49, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e23/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e23_Value), 31, 1, 2, 98, "", 0
  },

  { 50, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_y2/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y2_Value), 31, 1, 2, 100, "", 0
  },

  { 51, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_y2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y2_Gain), 31, 1, 2, 102, "", 0 },

  { 52, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e14/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e14_Value), 31, 1, 2, 104, "", 0
  },

  { 53, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e24/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e24_Value), 31, 1, 2, 106, "", 0
  },

  { 54, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_x2/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x2_Value), 31, 1, 2, 108, "", 0
  },

  { 55, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_x2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x2_Gain), 31, 1, 2, 110, "", 0 },

  { 56, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e15/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e15_Value), 31, 1, 2, 112, "", 0
  },

  { 57, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e25/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e25_Value), 31, 1, 2, 114, "", 0
  },

  { 58, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_x3/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x3_Value), 31, 1, 2, 116, "", 0
  },

  { 59,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_surge/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Joysticktau_surge_Gain), 31, 1, 2,
    118, "", 0 },

  { 60,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation1/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation1_UpperSat), 31, 1, 2,
    120, "", 0 },

  { 61,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation1/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation1_LowerSat), 31, 1, 2,
    122, "", 0 },

  { 62,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_sway/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Joysticktau_sway_Gain), 31, 1, 2,
    124, "", 0 },

  { 63,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation2/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation2_UpperSat), 31, 1, 2,
    126, "", 0 },

  { 64,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation2/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation2_LowerSat), 31, 1, 2,
    128, "", 0 },

  { 65,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_yaw/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Joysticktau_yaw_Gain), 31, 1, 2,
    130, "", 0 },

  { 66,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation3/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation3_UpperSat), 31, 1, 2,
    132, "", 0 },

  { 67,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation3/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation3_LowerSat), 31, 1, 2,
    134, "", 0 },

  { 68,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_UpperSat), 31, 1, 2,
    136, "", 0 },

  { 69,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_LowerSat), 31, 1, 2,
    138, "", 0 },

  { 70,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Joysticku_1_Gain), 31, 1, 2, 140,
    "", 0 },

  { 71,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Joysticku_2_Gain), 31, 1, 2, 142,
    "", 0 },

  { 72,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Joysticku_3_Gain), 31, 1, 2, 144,
    "", 0 },

  { 73,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_4/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Joysticku_4_Gain), 31, 1, 2, 146,
    "", 0 },

  { 74,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_5/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Joysticku_5_Gain), 31, 1, 2, 148,
    "", 0 },

  { 75, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Enable eta_d LPF/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Enableeta_dLPF_Value), 31, 1, 2,
    150, "", 0 },

  { 76, "ca_cse1_v1e_wo_losv2b/HMI/DP input/x_d/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, x_d_Value), 31, 1, 2, 152, "", 0 },

  { 77, "ca_cse1_v1e_wo_losv2b/HMI/DP input/y_d/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, y_d_Value), 31, 1, 2, 154, "", 0 },

  { 78, "ca_cse1_v1e_wo_losv2b/HMI/DP input/psi_d/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, psi_d_Value), 31, 1, 2, 156, "", 0 },

  { 79, "ca_cse1_v1e_wo_losv2b/HMI/DP input/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain1_Gain), 31, 1, 2, 158, "", 0
  },

  { 80, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn/A", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, TransferFcn_A), 31, 1, 2, 160, "", 0 },

  { 81, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn/C", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, TransferFcn_C), 31, 1, 2, 162, "", 0 },

  { 82, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn1/A", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, TransferFcn1_A), 31, 1, 2, 164, "", 0 },

  { 83, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn1/C", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, TransferFcn1_C), 31, 1, 2, 166, "", 0 },

  { 84, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn2/A", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, TransferFcn2_A), 31, 1, 2, 168, "", 0 },

  { 85, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn2/C", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, TransferFcn2_C), 31, 1, 2, 170, "", 0 },

  { 86, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP N/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, eta_dDPN_Gain), 31, 1, 2, 172, "", 0 },

  { 87, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP E/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, eta_dDPE_Gain), 31, 1, 2, 174, "", 0 },

  { 88, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP Psi/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, eta_dDPPsi_Gain), 31, 1, 2, 176, "", 0 },

  { 89,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Controller Input Selector/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, ControllerInputSelector_Value), 31,
    1, 2, 178, "", 0 },

  { 90, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn3_Gain), 31, 1, 2, 180, "", 0
  },

  { 91, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, mm2mx_Gain), 31, 1, 2, 182, "", 0
  },

  { 92, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn4_Gain), 31, 1, 2, 184, "", 0
  },

  { 93, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, mm2my_Gain), 31, 1, 2, 186, "", 0
  },

  { 94, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn6_Gain), 31, 1, 2, 188, "", 0
  },

  { 95, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, d2ryaw_Gain), 31, 1, 2, 190, "", 0
  },

  { 96, "ca_cse1_v1e_wo_losv2b/Plants/Enable Linear Simulator/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, EnableLinearSimulator_Value), 31, 1, 2,
    192, "", 0 },

  { 97, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_surge/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, eta_surge_Gain), 31, 1, 2, 194, "", 0 },

  { 98, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_sway/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, eta_sway_Gain), 31, 1, 2, 196, "", 0 },

  { 99, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_yaw/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, eta_yaw_Gain), 31, 1, 2, 198, "", 0 },

  { 100, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn8_Gain), 31, 1, 2, 200, "", 0
  },

  { 101,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, d2rroll_Gain), 31, 1, 2, 202, "",
    0 },

  { 102, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn7_Gain), 31, 1, 2, 204, "", 0
  },

  { 103,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, d2rpitch_Gain), 31, 1, 2, 206, "",
    0 },

  { 104,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Constant1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant1_Value), 33, 9, 2, 208,
    "", 0 },

  { 105, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn5_Gain), 31, 1, 2, 210, "", 0
  },

  { 106, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, mm2mz_Gain), 31, 1, 2, 212, "", 0
  },

  { 107, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_surge/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, nu_surge_Gain), 31, 1, 2, 214, "", 0 },

  { 108, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_sway/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, nu_sway_Gain), 31, 1, 2, 216, "", 0 },

  { 109, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_yaw/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, nu_yaw_Gain), 31, 1, 2, 218, "", 0 },

  { 110,
    "ca_cse1_v1e_wo_losv2b/Control Systems/if DP Control Mode/Constant/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value_c), 31, 1, 2, 220,
    "", 0 },

  { 111, "ca_cse1_v1e_wo_losv2b/Control Systems/Saturation/UpperLimit", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_UpperSat_m), 31, 1, 2, 222, "",
    0 },

  { 112, "ca_cse1_v1e_wo_losv2b/Control Systems/Saturation/LowerLimit", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_LowerSat_f), 31, 1, 2, 224, "",
    0 },

  { 113,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn9Residual_Gain), 31, 1, 2,
    226, "", 0 },

  { 114, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d Psi deg/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, eta_dPsideg_Gain), 31, 1, 2, 228,
    "", 0 },

  { 115, "ca_cse1_v1e_wo_losv2b/Guidance Systems/psi_d/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, psi_d_Gain), 31, 1, 2, 230, "", 0 },

  { 116, "ca_cse1_v1e_wo_losv2b/Guidance Systems/x_d/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, x_d_Gain), 31, 1, 2, 232, "", 0 },

  { 117, "ca_cse1_v1e_wo_losv2b/Guidance Systems/y_d/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, y_d_Gain), 31, 1, 2, 234, "", 0 },

  { 118, "ca_cse1_v1e_wo_losv2b/HMI/Battery Bow Thruster/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, BatteryBowThruster_Gain), 31, 1, 2, 236,
    "", 0 },

  { 119, "ca_cse1_v1e_wo_losv2b/HMI/Battery Servo/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, BatteryServo_Gain), 31, 1, 2, 238, "", 0 },

  { 120, "ca_cse1_v1e_wo_losv2b/HMI/Battery Main/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, BatteryMain_Gain), 31, 1, 2, 240, "", 0 },

  { 121,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn1FPS_Gain), 31, 1, 2, 242, "",
    0 },

  { 122,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, QTMIn2Error_Gain), 31, 1, 2, 244,
    "", 0 },

  { 123, "ca_cse1_v1e_wo_losv2b/Plants/u_1 plant/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u_1plant_Gain), 31, 1, 2, 246, "", 0 },

  { 124, "ca_cse1_v1e_wo_losv2b/Plants/u_2 plant/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u_2plant_Gain), 31, 1, 2, 248, "", 0 },

  { 125, "ca_cse1_v1e_wo_losv2b/Plants/u_3 plant/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u_3plant_Gain), 31, 1, 2, 250, "", 0 },

  { 126, "ca_cse1_v1e_wo_losv2b/Plants/u_4 plant/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u_4plant_Gain), 31, 1, 2, 252, "", 0 },

  { 127, "ca_cse1_v1e_wo_losv2b/Plants/u_5 plant/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, u_5plant_Gain), 31, 1, 2, 254, "", 0 },

  { 128, "ca_cse1_v1e_wo_losv2b/Plants/BT power limit plant/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, BTpowerlimitplant_Gain), 31, 1, 2, 256, "",
    0 },

  { 129, "ca_cse1_v1e_wo_losv2b/Plants/VSP speed plant/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, VSPspeedplant_Gain), 31, 1, 2, 258, "", 0
  },

  { 130, "ca_cse1_v1e_wo_losv2b/Plants/Enable CSE1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, EnableCSE1_Value), 31, 1, 2, 260, "", 0 },

  { 131,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Thruster_Command_DP/InitialOutput",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Thruster_Command_DP_Y0), 52, 7, 2,
    262, "", 0 },

  { 132,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator1/InitialCondition",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Integrator1_IC), 31, 1, 2, 264, "",
    0 },

  { 133, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/BT_power_limit/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, BT_power_limit_Value), 31, 1, 2,
    266, "", 0 },

  { 134, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Enable Filter/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, EnableFilter_Value), 31, 1, 2, 268,
    "", 0 },

  { 135,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator/InitialCondition",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Integrator_IC), 31, 1, 2, 270, "",
    0 },

  { 136,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_UpperSat_g), 31, 1, 2,
    272, "", 0 },

  { 137,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_LowerSat_l), 31, 1, 2,
    274, "", 0 },

  { 138,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain_Gain), 31, 1, 2, 276, "", 0 },

  { 139,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value_e), 31, 1, 2, 278,
    "", 0 },

  { 140,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta N/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, etaN_Gain), 31, 1, 2, 280, "", 0 },

  { 141,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta E/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, etaE_Gain), 31, 1, 2, 282, "", 0 },

  { 142,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta Psi/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, etaPsi_Gain), 31, 1, 2, 284, "", 0
  },

  { 143,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_N_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Reg_e_N_hil_Gain), 31, 1, 2, 286,
    "", 0 },

  { 144,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_E_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Reg_e_E_hil_Gain), 31, 1, 2, 288,
    "", 0 },

  { 145,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_Psi_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Reg_e_Psi_hil_Gain), 31, 1, 2, 290,
    "", 0 },

  { 146,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reset_DP_integrator/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Reset_DP_integrator_Value), 31, 1,
    2, 292, "", 0 },

  { 147,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Integrator/InitialCondition",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Integrator_IC_d), 31, 1, 2, 294,
    "", 0 },

  { 148,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator4/InitialCondition",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Integrator4_IC), 31, 1, 2, 296, "",
    0 },

  { 149,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kd/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Kd_Gain), 33, 9, 2, 298, "", 0 },

  { 150,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kd_scale/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Kd_scale_Value), 31, 1, 2, 300, "",
    0 },

  { 151,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_d1_Gain), 31, 1, 2, 302, "", 0 },

  { 152,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_d2_Gain), 31, 1, 2, 304, "", 0 },

  { 153,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_d3_Gain), 31, 1, 2, 306, "", 0 },

  { 154,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 3 deg/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_d3deg_Gain), 31, 1, 2, 308, "",
    0 },

  { 155,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Ki/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Ki_Gain), 33, 9, 2, 310, "", 0 },

  { 156,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Ki_scale/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Ki_scale_Value), 31, 1, 2, 312, "",
    0 },

  { 157,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_i1_Gain), 31, 1, 2, 314, "", 0 },

  { 158,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_i2_Gain), 31, 1, 2, 316, "", 0 },

  { 159,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_i3_Gain), 31, 1, 2, 318, "", 0 },

  { 160,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 3 deg/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_i3deg_Gain), 31, 1, 2, 320, "",
    0 },

  { 161,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kp_scale/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Kp_scale_Value), 31, 1, 2, 322, "",
    0 },

  { 162,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_UpperSat_o), 31, 1, 2,
    324, "", 0 },

  { 163,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_LowerSat_n), 31, 1, 2,
    326, "", 0 },

  { 164,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain_Gain_d), 31, 1, 2, 328, "", 0
  },

  { 165,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value_g), 31, 1, 2, 330,
    "", 0 },

  { 166,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_UpperSat_d), 31, 1, 2,
    332, "", 0 },

  { 167,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_LowerSat_h), 31, 1, 2,
    334, "", 0 },

  { 168,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain_Gain_e), 31, 1, 2, 336, "", 0
  },

  { 169,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value_i), 31, 1, 2, 338,
    "", 0 },

  { 170,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kp/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Kp_Gain), 33, 9, 2, 340, "", 0 },

  { 171,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_p1_Gain), 31, 1, 2, 342, "", 0 },

  { 172,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_p2_Gain), 31, 1, 2, 344, "", 0 },

  { 173,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_p3_Gain), 31, 1, 2, 346, "", 0 },

  { 174,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 3 deg/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_p3deg_Gain), 31, 1, 2, 348, "",
    0 },

  { 175,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_Psi_deg/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Reg_e_Psi_deg_Gain), 31, 1, 2, 350,
    "", 0 },

  { 176,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta Psi deg/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, etaPsideg_Gain), 31, 1, 2, 352, "",
    0 },

  { 177, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_surge/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DPtau_surge_Gain), 31, 1, 2, 354,
    "", 0 },

  { 178, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_sway/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DPtau_sway_Gain), 31, 1, 2, 356,
    "", 0 },

  { 179, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_yaw/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DPtau_yaw_Gain), 31, 1, 2, 358, "",
    0 },

  { 180, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e1_DP/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e1_DP_Value), 31, 1, 2, 360, "",
    0 },

  { 181,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e1_DP/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e1_DP_Gain), 31, 1, 2, 362,
    "", 0 },

  { 182, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Constant/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value_cb), 31, 1, 2, 364,
    "", 0 },

  { 183, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e2_DP/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e2_DP_Value), 31, 1, 2, 366, "",
    0 },

  { 184,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e2_DP/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e2_DP_Gain), 31, 1, 2, 368,
    "", 0 },

  { 185, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e3_DP/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e3_DP_Value), 31, 1, 2, 370, "",
    0 },

  { 186,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e3_DP/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e3_DP_Gain), 31, 1, 2, 372,
    "", 0 },

  { 187, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e4_DP/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e4_DP_Value), 31, 1, 2, 374, "",
    0 },

  { 188,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e4_DP/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e4_DP_Gain), 31, 1, 2, 376,
    "", 0 },

  { 189, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e5_DP/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e5_DP_Value), 31, 1, 2, 378, "",
    0 },

  { 190,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e5_DP/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e5_DP_Gain), 31, 1, 2, 380,
    "", 0 },

  { 191, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e11/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e11_Value_p), 31, 1, 2, 382, "",
    0 },

  { 192, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e21/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e21_Value_c), 31, 1, 2, 384, "",
    0 },

  { 193, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_y1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y1_Value_b), 31, 1, 2, 386, "",
    0 },

  { 194, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e12/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e12_Value_i), 31, 1, 2, 388, "",
    0 },

  { 195, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e22/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e22_Value_o), 31, 1, 2, 390, "",
    0 },

  { 196, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_x1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x1_Value_l), 31, 1, 2, 392, "",
    0 },

  { 197, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_x1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x1_Gain_a), 31, 1, 2, 394, "", 0
  },

  { 198, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e13/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e13_Value_d), 31, 1, 2, 396, "",
    0 },

  { 199, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e23/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e23_Value_i), 31, 1, 2, 398, "",
    0 },

  { 200, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_y2/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y2_Value_o), 31, 1, 2, 400, "",
    0 },

  { 201, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_y2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y2_Gain_j), 31, 1, 2, 402, "", 0
  },

  { 202, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e14/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e14_Value_o), 31, 1, 2, 404, "",
    0 },

  { 203, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e24/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e24_Value_h), 31, 1, 2, 406, "",
    0 },

  { 204, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_x2/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x2_Value_o), 31, 1, 2, 408, "",
    0 },

  { 205, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_x2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x2_Gain_b), 31, 1, 2, 410, "", 0
  },

  { 206, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e15/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e15_Value_g), 31, 1, 2, 412, "",
    0 },

  { 207, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e25/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e25_Value_f), 31, 1, 2, 414, "",
    0 },

  { 208, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_x3/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x3_Value_h), 31, 1, 2, 416, "",
    0 },

  { 209, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DPu_1_Gain), 31, 1, 2, 418, "", 0
  },

  { 210, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DPu_2_Gain), 31, 1, 2, 420, "", 0
  },

  { 211, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DPu_3_Gain), 31, 1, 2, 422, "", 0
  },

  { 212, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_4/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DPu_4_Gain), 31, 1, 2, 424, "", 0
  },

  { 213, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_5/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DPu_5_Gain), 31, 1, 2, 426, "", 0
  },

  { 214,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain1_Gain_m), 33, 9, 2, 428, "",
    0 },

  { 215,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator2/InitialCondition",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Integrator2_IC), 31, 1, 2, 430, "",
    0 },

  { 216,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain2_Gain), 33, 9, 2, 432, "", 0
  },

  { 217,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_UpperSat_a), 31, 1, 2,
    434, "", 0 },

  { 218,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_LowerSat_fw), 31, 1, 2,
    436, "", 0 },

  { 219,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain_Gain_g), 31, 1, 2, 438, "", 0
  },

  { 220,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value_h), 31, 1, 2, 440,
    "", 0 },

  { 221,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K4/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K4_Gain), 33, 9, 2, 442, "", 0 },

  { 222,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator3/InitialCondition",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Integrator3_IC), 31, 1, 2, 444, "",
    0 },

  { 223,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain6/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain6_Gain), 33, 9, 2, 446, "", 0
  },

  { 224,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain3_Gain), 33, 9, 2, 448, "", 0
  },

  { 225,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K11/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K11_Gain), 33, 9, 2, 450, "", 0 },

  { 226,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K12/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K12_Gain), 33, 9, 2, 452, "", 0 },

  { 227,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K2_Gain), 33, 9, 2, 454, "", 0 },

  { 228,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K3_Gain), 33, 9, 2, 456, "", 0 },

  { 229,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/inv(T_b)/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, invT_b_Gain), 33, 9, 2, 458, "", 0
  },

  { 230,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Saturation/UpperLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_UpperSat_ga), 31, 1, 2,
    460, "", 0 },

  { 231,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Saturation/LowerLimit",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Saturation_LowerSat_o), 31, 1, 2,
    462, "", 0 },

  { 232, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/VSP_speeds/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, VSP_speeds_Value), 31, 1, 2, 464,
    "", 0 },

  { 233, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, BT_D_Gain1_Gain), 31, 1, 2, 466,
    "", 0 },

  { 234, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, BT_Power_Offset1_Value), 31, 1, 2,
    468, "", 0 },

  { 235, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, BT_D_Gain2_Gain), 31, 1, 2, 470,
    "", 0 },

  { 236, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, BT_L_Gain1_Gain), 31, 1, 2, 472,
    "", 0 },

  { 237, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, BT_L_Gain2_Gain), 31, 1, 2, 474,
    "", 0 },

  { 238, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, BT_Power_Offset2_Value), 31, 1, 2,
    476, "", 0 },

  { 239, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, BT_Power_Offset3_Value), 31, 1, 2,
    478, "", 0 },

  { 240, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Constant/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value_ef), 31, 1, 2, 480,
    "", 0 },

  { 241, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Constant1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant1_Value_n), 31, 1, 2, 482,
    "", 0 },

  { 242, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Neg/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Neg_Gain), 31, 1, 2, 484, "", 0 },

  { 243, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /-x/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, x_Gain), 31, 1, 2, 486, "", 0 },

  { 244, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /-y/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, y_Gain), 31, 1, 2, 488, "", 0 },

  { 245,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain_Gain_k), 31, 1, 2, 490, "", 0
  },

  { 246,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gain_Gain_o), 31, 1, 2, 492, "", 0
  },

  { 247,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo1_RowIdx), 53, 3, 2, 494, "",
    0 },

  { 248,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo1_ColIdx), 53, 3, 2, 496, "",
    0 },

  { 249,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo1/Table",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo1_Table), 33, 9, 2, 498, "",
    0 },

  { 250,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo2_RowIdx), 53, 3, 2, 500, "",
    0 },

  { 251,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo2_ColIdx), 53, 3, 2, 502, "",
    0 },

  { 252,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo2/Table",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo2_Table), 33, 9, 2, 504, "",
    0 },

  { 253,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo3_RowIdx), 53, 3, 2, 506, "",
    0 },

  { 254,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo3_ColIdx), 53, 3, 2, 508, "",
    0 },

  { 255,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo3/Table",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo3_Table), 33, 9, 2, 510, "",
    0 },

  { 256,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo4_RowIdx), 53, 3, 2, 512, "",
    0 },

  { 257,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo4_ColIdx), 53, 3, 2, 514, "",
    0 },

  { 258,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo4/Table",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Servo4_Table), 33, 9, 2, 516, "",
    0 },

  { 259,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, VPS_Speed_Gain_Gain), 31, 1, 2,
    518, "", 0 },

  { 260,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, VPS_Power_Offset_Value), 31, 1, 2,
    520, "", 0 },

  { 261,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, VSPSPort_Gain), 31, 1, 2, 522, "",
    0 },

  { 262,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, VSPSStarboard_Gain), 31, 1, 2, 524,
    "", 0 },

  { 263, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e11/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e11_Value_i), 31, 1, 2, 526, "", 0 },

  { 264, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e21/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e21_Value_p), 31, 1, 2, 528, "", 0 },

  { 265, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_y1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, l_y1_Value_a), 31, 1, 2, 530, "", 0 },

  { 266, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e12/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e12_Value_o), 31, 1, 2, 532, "", 0 },

  { 267, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e22/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e22_Value_p), 31, 1, 2, 534, "", 0 },

  { 268, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_x1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, l_x1_Value_j), 31, 1, 2, 536, "", 0 },

  { 269, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_x1/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, l_x1_Gain_f), 31, 1, 2, 538, "", 0 },

  { 270, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e13/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e13_Value_l), 31, 1, 2, 540, "", 0 },

  { 271, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e23/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e23_Value_c), 31, 1, 2, 542, "", 0 },

  { 272, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_y2/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, l_y2_Value_g), 31, 1, 2, 544, "", 0 },

  { 273, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_y2/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, l_y2_Gain_c), 31, 1, 2, 546, "", 0 },

  { 274, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e14/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e14_Value_g), 31, 1, 2, 548, "", 0 },

  { 275, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e24/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e24_Value_i), 31, 1, 2, 550, "", 0 },

  { 276, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_x2/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, l_x2_Value_f), 31, 1, 2, 552, "", 0 },

  { 277, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_x2/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, l_x2_Gain_j), 31, 1, 2, 554, "", 0 },

  { 278, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e15/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e15_Value_c), 31, 1, 2, 556, "", 0 },

  { 279, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e25/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, T_e25_Value_j), 31, 1, 2, 558, "", 0 },

  { 280, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_x3/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, l_x3_Value_m), 31, 1, 2, 560, "", 0 },

  { 281, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e1_CSE1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, K_e1_CSE1_Value), 31, 1, 2, 562, "", 0 },

  { 282, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e1_CSE1/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e1_CSE1_Gain), 31, 1, 2, 564, "", 0
  },

  { 283, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Constant/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, Constant_Value_o), 31, 1, 2, 566, "", 0 },

  { 284, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e2_CSE1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, K_e2_CSE1_Value), 31, 1, 2, 568, "", 0 },

  { 285, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e2_CSE1/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e2_CSE1_Gain), 31, 1, 2, 570, "", 0
  },

  { 286, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e3_CSE1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, K_e3_CSE1_Value), 31, 1, 2, 572, "", 0 },

  { 287, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e3_CSE1/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e3_CSE1_Gain), 31, 1, 2, 574, "", 0
  },

  { 288, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e4_CSE1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, K_e4_CSE1_Value), 31, 1, 2, 576, "", 0 },

  { 289, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e4_CSE1/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e4_CSE1_Gain), 31, 1, 2, 578, "", 0
  },

  { 290, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e5_CSE1/Value", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, K_e5_CSE1_Value), 31, 1, 2, 580, "", 0 },

  { 291, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e5_CSE1/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e5_CSE1_Gain), 31, 1, 2, 582, "", 0
  },

  { 292, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_surge/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, CSE1tau_surge_Gain), 31, 1, 2, 584, "", 0
  },

  { 293, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_sway/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, CSE1tau_sway_Gain), 31, 1, 2, 586, "", 0 },

  { 294, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_yaw/Gain", offsetof
    (Parameters_CA_CSE1_V1e_wo_LOSV2, CSE1tau_yaw_Gain), 31, 1, 2, 588, "", 0 },

  { 295, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gainu_1_Gain), 31, 1, 2, 590, "",
    0 },

  { 296, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gainu_2_Gain), 31, 1, 2, 592, "",
    0 },

  { 297, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_3/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gainu_3_Gain), 31, 1, 2, 594, "",
    0 },

  { 298, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_4/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gainu_4_Gain), 31, 1, 2, 596, "",
    0 },

  { 299,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain BT power/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainBTpower_Gain), 31, 1, 2, 598,
    "", 0 },

  { 300, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Neg/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Neg_Gain_o), 31, 1, 2, 600, "", 0
  },

  { 301, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_5/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Gainu_5_Gain), 31, 1, 2, 602, "",
    0 },

  { 302,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_surge_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, tau_surge_hil_Gain), 31, 1, 2, 604,
    "", 0 },

  { 303,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_sway_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, tau_sway_hil_Gain), 31, 1, 2, 606,
    "", 0 },

  { 304,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_yaw_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, tau_yaw_hil_Gain), 31, 1, 2, 608,
    "", 0 },

  { 305,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/VSP_angle_deg_port/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, VSP_angle_deg_port_Gain), 31, 1, 2,
    610, "", 0 },

  { 306,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/VSP_angle_deg_stbd/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, VSP_angle_deg_stbd_Gain), 31, 1, 2,
    612, "", 0 },

  { 307,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/N_r/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, N_r_Value), 31, 1, 2, 614, "", 0 },

  { 308,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_r/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, N_r_Gain), 31, 1, 2, 616, "", 0 },

  { 309,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/N_v/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, N_v_Value), 31, 1, 2, 618, "", 0 },

  { 310,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_v/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, N_v_Gain), 31, 1, 2, 620, "", 0 },

  { 311,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/X_u/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, X_u_Value), 31, 1, 2, 622, "", 0 },

  { 312,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-X_u/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, X_u_Gain), 31, 1, 2, 624, "", 0 },

  { 313,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/Y_v/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Y_v_Value), 31, 1, 2, 626, "", 0 },

  { 314,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_v/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Y_v_Gain), 31, 1, 2, 628, "", 0 },

  { 315,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/Y_r/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Y_r_Value), 31, 1, 2, 630, "", 0 },

  { 316,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_vr/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Y_vr_Gain), 31, 1, 2, 632, "", 0 },

  { 317,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_12/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, D_L_12_Value), 31, 1, 2, 634, "",
    0 },

  { 318,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_13/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, D_L_13_Value), 31, 1, 2, 636, "",
    0 },

  { 319,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_21/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, D_L_21_Value), 31, 1, 2, 638, "",
    0 },

  { 320,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_31/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, D_L_31_Value), 31, 1, 2, 640, "",
    0 },

  { 321,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/psi_0/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, psi_0_Value), 31, 1, 2, 642, "", 0
  },

  { 322,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/x_0/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, x_0_Value), 31, 1, 2, 644, "", 0 },

  { 323,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/y_0/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, y_0_Value), 31, 1, 2, 646, "", 0 },

  { 324,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/r_0/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, r_0_Value), 31, 1, 2, 648, "", 0 },

  { 325,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/u_0/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, u_0_Value), 31, 1, 2, 650, "", 0 },

  { 326,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/v_0/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, v_0_Value), 31, 1, 2, 652, "", 0 },

  { 327,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, ResetLinearSimulatorintegrator_),
    31, 1, 2, 654, "", 0 },

  { 328,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/I_z/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, I_z_Value), 31, 1, 2, 656, "", 0 },

  { 329,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/m/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, m_Value), 31, 1, 2, 658, "", 0 },

  { 330,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/X_udot/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, X_udot_Value), 31, 1, 2, 660, "",
    0 },

  { 331,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_21/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, M_21_Value), 31, 1, 2, 662, "", 0
  },

  { 332,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_31/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, M_31_Value), 31, 1, 2, 664, "", 0
  },

  { 333,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_12/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, M_12_Value), 31, 1, 2, 666, "", 0
  },

  { 334,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/Y_vdot/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Y_vdot_Value), 31, 1, 2, 668, "",
    0 },

  { 335,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/x_g/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, x_g_Value), 31, 1, 2, 670, "", 0 },

  { 336,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/N_vdot/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, N_vdot_Value), 31, 1, 2, 672, "",
    0 },

  { 337,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_13/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, M_13_Value), 31, 1, 2, 674, "", 0
  },

  { 338,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/Y_rdot/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Y_rdot_Value), 31, 1, 2, 676, "",
    0 },

  { 339,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/N_rdot/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, N_rdot_Value), 31, 1, 2, 678, "",
    0 },

  { 340,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e11/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e11_Value_o), 31, 1, 2, 680, "",
    0 },

  { 341,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e21/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e21_Value_l), 31, 1, 2, 682, "",
    0 },

  { 342, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_y1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y1_Value_n), 31, 1, 2, 684, "",
    0 },

  { 343,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e12/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e12_Value_p), 31, 1, 2, 686, "",
    0 },

  { 344,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e22/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e22_Value_k), 31, 1, 2, 688, "",
    0 },

  { 345, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_x1/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x1_Value_d), 31, 1, 2, 690, "",
    0 },

  { 346, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x1_Gain_o), 31, 1, 2, 692, "", 0
  },

  { 347,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e13/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e13_Value_k), 31, 1, 2, 694, "",
    0 },

  { 348,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e23/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e23_Value_e), 31, 1, 2, 696, "",
    0 },

  { 349, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_y2/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y2_Value_j), 31, 1, 2, 698, "",
    0 },

  { 350, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_y2_Gain_h), 31, 1, 2, 700, "", 0
  },

  { 351,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e14/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e14_Value_d), 31, 1, 2, 702, "",
    0 },

  { 352,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e24/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e24_Value_g), 31, 1, 2, 704, "",
    0 },

  { 353, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_x2/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x2_Value_k), 31, 1, 2, 706, "",
    0 },

  { 354, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x2_Gain_c), 31, 1, 2, 708, "", 0
  },

  { 355,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e15/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e15_Value_p), 31, 1, 2, 710, "",
    0 },

  { 356,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e25/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, T_e25_Value_o), 31, 1, 2, 712, "",
    0 },

  { 357, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_x3/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, l_x3_Value_b), 31, 1, 2, 714, "",
    0 },

  { 358,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e1_hil/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e1_hil_Value), 31, 1, 2, 716, "",
    0 },

  { 359,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e1_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e1_hil_Gain), 31, 1, 2, 718,
    "", 0 },

  { 360,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Constant41/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, Constant41_Value), 31, 1, 2, 720,
    "", 0 },

  { 361,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e2_hil/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e2_hil_Value), 31, 1, 2, 722, "",
    0 },

  { 362,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e2_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e2_hil_Gain), 31, 1, 2, 724,
    "", 0 },

  { 363,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e3_hil/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e3_hil_Value), 31, 1, 2, 726, "",
    0 },

  { 364,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e3_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e3_hil_Gain), 31, 1, 2, 728,
    "", 0 },

  { 365,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e4_hil/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e4_hil_Value), 31, 1, 2, 730, "",
    0 },

  { 366,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e4_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e4_hil_Gain), 31, 1, 2, 732,
    "", 0 },

  { 367,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e5_hil/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, K_e5_hil_Value), 31, 1, 2, 734, "",
    0 },

  { 368,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e5_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, GainK_e5_hil_Gain), 31, 1, 2, 736,
    "", 0 },

  { 369,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/sample time/WtEt",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, sampletime_WtEt), 0, 1, 2, 738, "",
    0 },

  { 370,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Delay Input2/X0",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, DelayInput2_X0), 31, 1, 2, 740, "",
    0 },

  { 371,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, R31_Value), 31, 1, 2, 742, "", 0 },

  { 372,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, R32_Value), 31, 1, 2, 744, "", 0 },

  { 373,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, R13_Value), 31, 1, 2, 746, "", 0 },

  { 374,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, R23_Value), 31, 1, 2, 748, "", 0 },

  { 375,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, R33_Value), 31, 1, 2, 750, "", 0 },

  { 376, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_surge_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, eta_surge_hil_Gain), 31, 1, 2, 752,
    "", 0 },

  { 377, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_sway_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, eta_sway_hil_Gain), 31, 1, 2, 754,
    "", 0 },

  { 378, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_yaw_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, eta_yaw_hil_Gain), 31, 1, 2, 756,
    "", 0 },

  { 379, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_surge_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, etadot_surge_hil_Gain), 31, 1, 2,
    758, "", 0 },

  { 380, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_sway_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, etadot_sway_hil_Gain), 31, 1, 2,
    760, "", 0 },

  { 381, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_yaw_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, etadot_yaw_hil_Gain), 31, 1, 2,
    762, "", 0 },

  { 382, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_surge_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, nu_surge_hil_Gain), 31, 1, 2, 764,
    "", 0 },

  { 383, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_sway_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, nu_sway_hil_Gain), 31, 1, 2, 766,
    "", 0 },

  { 384, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_yaw_hil/Gain",
    offsetof(Parameters_CA_CSE1_V1e_wo_LOSV2, nu_yaw_hil_Gain), 31, 1, 2, 768,
    "", 0 },
};

static int NI_ParamListSize = 385;
static int NI_ParamDimList[] = {
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Control Mode/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u3/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u4/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_4/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/u5/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_5/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy  BT power/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy  VSP speed/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/JS_L_Y/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_L_Y/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/JS_L_X/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_L_X/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/JS_R_Y/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_R_Y/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/JS_R_X/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_R_X/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_4/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/L2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/R2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_5/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3_BT_Power/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3_VSP_Speed/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e1_joystick/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e1_joystick/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Constant/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e2_joystick/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e2_joystick/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e3_joystick/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e3_joystick/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e4_joystick/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e4_joystick/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/K_e5_joystick/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e5_joystick/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e11/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e21/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_y1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e12/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e22/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_x1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_x1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e13/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e23/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_y2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_y2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e14/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e24/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_x2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_x2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e15/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/T_e25/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/l_x3/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_surge/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation1/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation1/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_sway/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation2/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation2/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_yaw/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation3/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation3/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_4/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_5/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Enable eta_d LPF/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/DP input/x_d/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/DP input/y_d/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/DP input/psi_d/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/DP input/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn/A */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn/C */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn1/A */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn1/C */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn2/A */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn2/C */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP N/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP E/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP Psi/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Controller Input Selector/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Enable Linear Simulator/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_surge/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_sway/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_yaw/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Constant1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_surge/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_sway/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_yaw/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/if DP Control Mode/Constant/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Saturation/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/Saturation/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d Psi deg/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/psi_d/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/x_d/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Guidance Systems/y_d/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Battery Bow Thruster/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Battery Servo/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/HMI/Battery Main/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/u_1 plant/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/u_2 plant/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/u_3 plant/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/u_4 plant/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/u_5 plant/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/BT power limit plant/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/VSP speed plant/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Enable CSE1/Value */
  7, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Thruster_Command_DP/InitialOutput */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator1/InitialCondition */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/BT_power_limit/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Enable Filter/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator/InitialCondition */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta N/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta E/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta Psi/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_N_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_E_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_Psi_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reset_DP_integrator/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Integrator/InitialCondition */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator4/InitialCondition */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kd/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kd_scale/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 3 deg/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Ki/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Ki_scale/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 3 deg/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kp_scale/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kp/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 3 deg/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_Psi_deg/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta Psi deg/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_surge/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_sway/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_yaw/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e1_DP/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e1_DP/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Constant/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e2_DP/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e2_DP/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e3_DP/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e3_DP/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e4_DP/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e4_DP/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/K_e5_DP/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e5_DP/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e11/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e21/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_y1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e12/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e22/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_x1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_x1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e13/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e23/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_y2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_y2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e14/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e24/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_x2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_x2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e15/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/T_e25/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/l_x3/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_4/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_5/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator2/InitialCondition */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Constant/Value */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K4/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator3/InitialCondition */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain6/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain3/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K11/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K12/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K2/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K3/Gain */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/inv(T_b)/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Saturation/UpperLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Saturation/LowerLimit */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Control Systems/DP control/VSP_speeds/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Constant/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Constant1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Neg/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /-y/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain/Gain */
  1, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e11/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e21/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_y1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e12/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e22/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_x1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_x1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e13/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e23/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_y2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_y2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e14/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e24/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_x2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_x2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e15/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/T_e25/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/l_x3/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e1_CSE1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e1_CSE1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Constant/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e2_CSE1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e2_CSE1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e3_CSE1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e3_CSE1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e4_CSE1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e4_CSE1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/K_e5_CSE1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e5_CSE1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_surge/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_sway/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_yaw/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_3/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_4/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain BT power/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Neg/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_5/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_surge_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_sway_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_yaw_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/VSP_angle_deg_port/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/VSP_angle_deg_stbd/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/N_r/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_r/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/N_v/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_v/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/X_u/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-X_u/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/Y_v/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_v/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/Y_r/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_vr/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_12/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_13/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_21/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_31/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/psi_0/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/x_0/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/y_0/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/r_0/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/u_0/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/v_0/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Reset Linear Simulator integrator/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/I_z/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/m/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/X_udot/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_21/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_31/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_12/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/Y_vdot/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/x_g/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/N_vdot/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_13/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/Y_rdot/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/N_rdot/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e11/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e21/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_y1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e12/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e22/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_x1/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_x1/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e13/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e23/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_y2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_y2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e14/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e24/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_x2/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_x2/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e15/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/T_e25/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/l_x3/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e1_hil/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e1_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Constant41/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e2_hil/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e2_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e3_hil/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e3_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e4_hil/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e4_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/K_e5_hil/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e5_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/sample time/WtEt */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Delay Input2/X0 */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_surge_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_sway_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_yaw_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_surge_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_sway_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_yaw_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_surge_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_sway_hil/Gain */
  1, 1,                                /* ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_yaw_hil/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 360;
static NI_Signal NI_SigList[] = {
  { 0, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Accuracyu_1), BLOCKIO_SIG, 0, 1, 2,
    0, 0 },

  { 1, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_2", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Accuracyu_2), BLOCKIO_SIG, 0, 1, 2,
    2, 0 },

  { 2, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_3", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Accuracyu_3), BLOCKIO_SIG, 0, 1, 2,
    4, 0 },

  { 3, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_4", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Accuracyu_4), BLOCKIO_SIG, 0, 1, 2,
    6, 0 },

  { 4, "ca_cse1_v1e_wo_losv2b/HMI/Accuracy control/Accuracy u_5", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Accuracyu_5), BLOCKIO_SIG, 0, 1, 2,
    8, 0 },

  { 5, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_L_Y", 0,
    "[-1,1]", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, u1), BLOCKIO_SIG, 0, 1, 2,
    10, 0 },

  { 6, "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PS3u_1), BLOCKIO_SIG, 0, 1, 2,
    12, 0 },

  { 7, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_L_X", 0,
    "[-1,1]", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, u1_p), BLOCKIO_SIG, 0, 1,
    2, 14, 0 },

  { 8, "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PS3u_2), BLOCKIO_SIG, 0, 1, 2,
    16, 0 },

  { 9, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_R_Y", 0,
    "[-1,1]", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, u1_a), BLOCKIO_SIG, 0, 1,
    2, 18, 0 },

  { 10, "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_3", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PS3u_3), BLOCKIO_SIG, 0, 1, 2,
    20, 0 },

  { 11, "ca_cse1_v1e_wo_losv2b/HMI/PS3 input/PS3 signals/Scaling_JS_R_X", 0,
    "[-1,1]", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, u1_i), BLOCKIO_SIG, 0, 1,
    2, 22, 0 },

  { 12, "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_4", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PS3u_4), BLOCKIO_SIG, 0, 1, 2,
    24, 0 },

  { 13, "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b,
    BowThrusterdirection), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "ca_cse1_v1e_wo_losv2b/Control Systems/Manual Thrust control/PS3 u_5", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PS3u_5), BLOCKIO_SIG, 0, 1, 2,
    28, 0 },

  { 15,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e1_joystick",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e1_joystick),
    BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e2_joystick",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e2_joystick),
    BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e3_joystick",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e3_joystick),
    BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e4_joystick",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e4_joystick),
    BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Gain K_e5_joystick",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e5_joystick),
    BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e/Thruster Gain matrix",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, ThrusterGainmatrix),
    BLOCKIO_SIG, 24, 25, 2, 40, 0 },

  { 21, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/K_e^-1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_e1), BLOCKIO_SIG, 24, 25, 2, 42, 0
  },

  { 22, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_x1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_x1), BLOCKIO_SIG, 0, 1, 2, 44,
    0 },

  { 23, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_y2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_y2), BLOCKIO_SIG, 0, 1, 2, 46,
    0 },

  { 24, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/-l_x2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_x2), BLOCKIO_SIG, 0, 1, 2, 48,
    0 },

  { 25, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e/3x5", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, x5), BLOCKIO_SIG, 28, 15, 2, 50, 0 },

  { 26, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e^+", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, T_e), BLOCKIO_SIG, 27, 15, 2, 52, 0
  },

  { 27, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/T_e^+ K_e^-1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, T_eK_e1), BLOCKIO_SIG, 27, 15, 2,
    54, 0 },

  { 28, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Sum1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum1), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_surge",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Joysticktau_surge),
    BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation1), BLOCKIO_SIG, 0, 1,
    2, 60, 0 },

  { 31, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Sum2", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum2), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_sway",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Joysticktau_sway),
    BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation2), BLOCKIO_SIG, 0, 1,
    2, 66, 0 },

  { 34, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Sum", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35,
    "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick tau_yaw", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Joysticktau_yaw), BLOCKIO_SIG, 0,
    1, 2, 70, 0 },

  { 36, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation3", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation3), BLOCKIO_SIG, 0, 1,
    2, 72, 0 },

  { 37, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Product1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product1), BLOCKIO_SIG, 23, 5, 2, 74,
    0 },

  { 38, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Saturation", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation), BLOCKIO_SIG, 23, 5,
    2, 76, 0 },

  { 39, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Joysticku_1), BLOCKIO_SIG, 0, 1,
    2, 78, 0 },

  { 40, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Joysticku_2), BLOCKIO_SIG, 0, 1,
    2, 80, 0 },

  { 41, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_3", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Joysticku_3), BLOCKIO_SIG, 0, 1,
    2, 82, 0 },

  { 42, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_4", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Joysticku_4), BLOCKIO_SIG, 0, 1,
    2, 84, 0 },

  { 43, "ca_cse1_v1e_wo_losv2b/Control Systems/Joystick Control/Joystick u_5", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Joysticku_5), BLOCKIO_SIG, 0, 1,
    2, 86, 0 },

  { 44, "ca_cse1_v1e_wo_losv2b/HMI/DP input/Degrees to Radians/Gain1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain1), BLOCKIO_SIG, 0, 1, 2, 88, 0
  },

  { 45, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, TransferFcn), BLOCKIO_SIG, 0, 1, 2,
    90, 0 },

  { 46, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, TransferFcn1), BLOCKIO_SIG, 0, 1, 2,
    92, 0 },

  { 47, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Transfer Fcn2", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, TransferFcn2), BLOCKIO_SIG, 0, 1, 2,
    94, 0 },

  { 48, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/Multiport Switch", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, MultiportSwitch), BLOCKIO_SIG, 17, 3,
    2, 96, 0 },

  { 49, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP N", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_dDPN), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP E", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_dDPE), BLOCKIO_SIG, 0, 1, 2, 100, 0 },

  { 51, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d DP Psi", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_dDPPsi), BLOCKIO_SIG, 0, 1, 2,
    102, 0 },

  { 52, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn), BLOCKIO_SIG, 34, 9, 2, 104,
    0 },

  { 53, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In3", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn3), BLOCKIO_SIG, 31, 1, 2,
    106, 0 },

  { 54, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m x", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, mm2mx), BLOCKIO_SIG, 31, 1, 2, 108,
    0 },

  { 55, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In4", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn4), BLOCKIO_SIG, 31, 1, 2,
    110, 0 },

  { 56, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m y", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, mm2my), BLOCKIO_SIG, 31, 1, 2, 112,
    0 },

  { 57, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In6", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn6), BLOCKIO_SIG, 31, 1, 2,
    114, 0 },

  { 58, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r yaw", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, d2ryaw), BLOCKIO_SIG, 31, 1, 2,
    116, 0 },

  { 59, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Eta Switch", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, EtaSwitch), BLOCKIO_SIG, 17, 3, 2, 118, 0 },

  { 60, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_surge", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_surge), BLOCKIO_SIG, 0, 1, 2, 120, 0 },

  { 61, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_sway", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_sway), BLOCKIO_SIG, 0, 1, 2, 122, 0 },

  { 62, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/eta_yaw", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_yaw), BLOCKIO_SIG, 0, 1, 2, 124, 0 },

  { 63, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In8", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn8), BLOCKIO_SIG, 31, 1, 2,
    126, 0 },

  { 64, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r roll", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, d2rroll), BLOCKIO_SIG, 31, 1, 2,
    128, 0 },

  { 65, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In7", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn7), BLOCKIO_SIG, 31, 1, 2,
    130, 0 },

  { 66, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/d2r pitch", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, d2rpitch), BLOCKIO_SIG, 31, 1, 2,
    132, 0 },

  { 67,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, sintheta), BLOCKIO_SIG, 17, 3,
    2, 134, 0 },

  { 68,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, costheta), BLOCKIO_SIG, 17, 3,
    2, 136, 0 },

  { 69,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R11), BLOCKIO_SIG, 0, 1, 2,
    138, 0 },

  { 70,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R21), BLOCKIO_SIG, 0, 1, 2,
    140, 0 },

  { 71,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R31), BLOCKIO_SIG, 0, 1, 2,
    142, 0 },

  { 72,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R12), BLOCKIO_SIG, 0, 1, 2,
    144, 0 },

  { 73,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R22), BLOCKIO_SIG, 0, 1, 2,
    146, 0 },

  { 74,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R32), BLOCKIO_SIG, 0, 1, 2,
    148, 0 },

  { 75,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R13), BLOCKIO_SIG, 0, 1, 2,
    150, 0 },

  { 76,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R23), BLOCKIO_SIG, 0, 1, 2,
    152, 0 },

  { 77,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R33), BLOCKIO_SIG, 0, 1, 2,
    154, 0 },

  { 78,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Reshape9x13x3), BLOCKIO_SIG,
    33, 9, 2, 156, 0 },

  { 79,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Matrix Concatenate2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, MatrixConcatenate2),
    BLOCKIO_SIG, 36, 36, 2, 158, 0 },

  { 80, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In5", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn5), BLOCKIO_SIG, 31, 1, 2,
    160, 0 },

  { 81, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/mm2m z", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, mm2mz), BLOCKIO_SIG, 31, 1, 2, 162,
    0 },

  { 82, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Derivative", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Derivative), BLOCKIO_SIG, 19, 6,
    2, 164, 0 },

  { 83, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/Product", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product), BLOCKIO_SIG, 19, 6, 2,
    166, 0 },

  { 84, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Nu Switch", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, NuSwitch), BLOCKIO_SIG, 17, 3, 2, 168, 0 },

  { 85, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_surge", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, nu_surge), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_sway", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, nu_sway), BLOCKIO_SIG, 0, 1, 2, 172, 0 },

  { 87, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/nu_yaw", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, nu_yaw), BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88, "ca_cse1_v1e_wo_losv2b/Control Systems/Control Switch", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, ControlSwitch), BLOCKIO_SIG, 18, 7, 2, 176,
    0 },

  { 89, "ca_cse1_v1e_wo_losv2b/Control Systems/Saturation", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation_c), BLOCKIO_SIG, 18, 7, 2, 178, 0
  },

  { 90,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn9Residual), BLOCKIO_SIG,
    31, 1, 2, 180, 0 },

  { 91, "ca_cse1_v1e_wo_losv2b/Guidance Systems/DP/eta_d Psi deg", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_dPsideg), BLOCKIO_SIG, 0, 1, 2,
    182, 0 },

  { 92, "ca_cse1_v1e_wo_losv2b/Guidance Systems/psi_d", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, psi_d), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93, "ca_cse1_v1e_wo_losv2b/Guidance Systems/x_d", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, x_d), BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94, "ca_cse1_v1e_wo_losv2b/Guidance Systems/y_d", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, y_d), BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95, "ca_cse1_v1e_wo_losv2b/HMI/SIT zAI0", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, SITzAI0), BLOCKIO_SIG, 0, 1, 2, 190, 0 },

  { 96, "ca_cse1_v1e_wo_losv2b/HMI/Battery Bow Thruster", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, BatteryBowThruster), BLOCKIO_SIG, 0, 1, 2,
    192, 0 },

  { 97, "ca_cse1_v1e_wo_losv2b/HMI/SIT zAI1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, SITzAI1), BLOCKIO_SIG, 0, 1, 2, 194, 0 },

  { 98, "ca_cse1_v1e_wo_losv2b/HMI/Battery Servo", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, BatteryServo), BLOCKIO_SIG, 0, 1, 2, 196, 0
  },

  { 99, "ca_cse1_v1e_wo_losv2b/HMI/SIT zAI2", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, SITzAI2), BLOCKIO_SIG, 0, 1, 2, 198, 0 },

  { 100, "ca_cse1_v1e_wo_losv2b/HMI/Battery Main", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, BatteryMain), BLOCKIO_SIG, 0, 1, 2, 200, 0 },

  { 101, "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn1FPS), BLOCKIO_SIG, 31,
    1, 2, 202, 0 },

  { 102,
    "ca_cse1_v1e_wo_losv2b/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, QTMIn2Error), BLOCKIO_SIG, 31, 1,
    2, 204, 0 },

  { 103, "ca_cse1_v1e_wo_losv2b/Plants/u_1 plant", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, u_1plant), BLOCKIO_SIG, 0, 1, 2, 206, 0 },

  { 104, "ca_cse1_v1e_wo_losv2b/Plants/u_2 plant", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, u_2plant), BLOCKIO_SIG, 0, 1, 2, 208, 0 },

  { 105, "ca_cse1_v1e_wo_losv2b/Plants/u_3 plant", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, u_3plant), BLOCKIO_SIG, 0, 1, 2, 210, 0 },

  { 106, "ca_cse1_v1e_wo_losv2b/Plants/u_4 plant", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, u_4plant), BLOCKIO_SIG, 0, 1, 2, 212, 0 },

  { 107, "ca_cse1_v1e_wo_losv2b/Plants/u_5 plant", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, u_5plant), BLOCKIO_SIG, 0, 1, 2, 214, 0 },

  { 108, "ca_cse1_v1e_wo_losv2b/Plants/BT power limit plant", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, BTpowerlimitplant), BLOCKIO_SIG, 0, 1, 2,
    216, 0 },

  { 109, "ca_cse1_v1e_wo_losv2b/Plants/VSP speed plant", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, VSPspeedplant), BLOCKIO_SIG, 0, 1, 2, 218, 0
  },

  { 110,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_r", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, N_r), BLOCKIO_SIG, 0, 1, 2, 220,
    0 },

  { 111,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_v", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, N_v), BLOCKIO_SIG, 0, 1, 2, 222,
    0 },

  { 112,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-X_u", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, X_u), BLOCKIO_SIG, 0, 1, 2, 224,
    0 },

  { 113,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_v", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Y_v), BLOCKIO_SIG, 0, 1, 2, 226,
    0 },

  { 114,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_vr", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Y_vr), BLOCKIO_SIG, 0, 1, 2, 228,
    0 },

  { 115,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, LinearDampningmatrix),
    BLOCKIO_SIG, 33, 9, 2, 230, 0 },

  { 116,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/psi_0",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, psi_0), BLOCKIO_SIG, 0, 1, 2,
    232, 0 },

  { 117,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/x_0",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, x_0), BLOCKIO_SIG, 0, 1, 2,
    234, 0 },

  { 118,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial eta/y_0",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, y_0), BLOCKIO_SIG, 0, 1, 2,
    236, 0 },

  { 119,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/r_0",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, r_0), BLOCKIO_SIG, 0, 1, 2,
    238, 0 },

  { 120,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/u_0",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, u_0), BLOCKIO_SIG, 0, 1, 2,
    240, 0 },

  { 121,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Initial nu/v_0",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, v_0), BLOCKIO_SIG, 0, 1, 2,
    242, 0 },

  { 122,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Integrator",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Integrator), BLOCKIO_SIG, 17,
    3, 2, 244, 0 },

  { 123,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Integrator1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Integrator1), BLOCKIO_SIG, 17,
    3, 2, 246, 0 },

  { 124,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_11",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, M_11), BLOCKIO_SIG, 0, 1, 2,
    248, 0 },

  { 125,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_22",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, M_22), BLOCKIO_SIG, 0, 1, 2,
    250, 0 },

  { 126,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/m x_g",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, mx_g), BLOCKIO_SIG, 0, 1, 2,
    252, 0 },

  { 127,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_32",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, M_32), BLOCKIO_SIG, 0, 1, 2,
    254, 0 },

  { 128,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_23",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, M_23), BLOCKIO_SIG, 0, 1, 2,
    256, 0 },

  { 129,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_33",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, M_33), BLOCKIO_SIG, 0, 1, 2,
    258, 0 },

  { 130, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/M",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, M), BLOCKIO_SIG, 33, 9, 2,
    260, 0 },

  { 131,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/M_inv/Inverse",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Inverse), BLOCKIO_SIG, 33, 9,
    2, 262, 0 },

  { 132,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Product1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product1_b), BLOCKIO_SIG, 17, 3,
    2, 264, 0 },

  { 133, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_x1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_x1_j), BLOCKIO_SIG, 0, 1, 2,
    266, 0 },

  { 134, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_y2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_y2_p), BLOCKIO_SIG, 0, 1, 2,
    268, 0 },

  { 135, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/-l_x2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_x2_o), BLOCKIO_SIG, 0, 1, 2,
    270, 0 },

  { 136, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e/3x5", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, x5_d), BLOCKIO_SIG, 28, 15, 2, 272,
    0 },

  { 137,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e1_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e1_hil), BLOCKIO_SIG, 0,
    1, 2, 274, 0 },

  { 138,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e2_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e2_hil), BLOCKIO_SIG, 0,
    1, 2, 276, 0 },

  { 139,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e3_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e3_hil), BLOCKIO_SIG, 0,
    1, 2, 278, 0 },

  { 140,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e4_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e4_hil), BLOCKIO_SIG, 0,
    1, 2, 280, 0 },

  { 141,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Gain K_e5_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e5_hil), BLOCKIO_SIG, 0,
    1, 2, 282, 0 },

  { 142,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/K_e/Thruster Gain matrix",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, ThrusterGainmatrix_e),
    BLOCKIO_SIG, 24, 25, 2, 284, 0 },

  { 143,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/sample time",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, sampletime), BLOCKIO_SIG, 0,
    1, 2, 286, 0 },

  { 144,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Delay Input2",
    0, "Y(k-1)", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Yk1), BLOCKIO_SIG, 0, 1,
    2, 288, 0 },

  { 145,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R11",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R11_b), BLOCKIO_SIG, 0, 1, 2,
    290, 0 },

  { 146,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R21",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R21_a), BLOCKIO_SIG, 0, 1, 2,
    292, 0 },

  { 147,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R12",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R12_m), BLOCKIO_SIG, 0, 1, 2,
    294, 0 },

  { 148,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R22",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, R22_h), BLOCKIO_SIG, 0, 1, 2,
    296, 0 },

  { 149,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R(psi)",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Rpsi), BLOCKIO_SIG, 33, 9, 2,
    298, 0 },

  { 150,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Product3", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product3), BLOCKIO_SIG, 17, 3, 2,
    300, 0 },

  { 151, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_surge_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_surge_hil), BLOCKIO_SIG, 0, 1, 2,
    302, 0 },

  { 152, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_sway_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_sway_hil), BLOCKIO_SIG, 0, 1, 2,
    304, 0 },

  { 153, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/eta_yaw_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_yaw_hil), BLOCKIO_SIG, 0, 1, 2,
    306, 0 },

  { 154, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_surge_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, etadot_surge_hil), BLOCKIO_SIG, 0, 1,
    2, 308, 0 },

  { 155, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_sway_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, etadot_sway_hil), BLOCKIO_SIG, 0, 1,
    2, 310, 0 },

  { 156, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/etadot_yaw_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, etadot_yaw_hil), BLOCKIO_SIG, 0, 1,
    2, 312, 0 },

  { 157, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_surge_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, nu_surge_hil), BLOCKIO_SIG, 0, 1, 2,
    314, 0 },

  { 158, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_sway_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, nu_sway_hil), BLOCKIO_SIG, 0, 1, 2,
    316, 0 },

  { 159, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/nu_yaw_hil", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, nu_yaw_hil), BLOCKIO_SIG, 0, 1, 2,
    318, 0 },

  { 160, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gainu_1), BLOCKIO_SIG, 0, 1, 2,
    320, 0 },

  { 161, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gainu_2), BLOCKIO_SIG, 0, 1, 2,
    322, 0 },

  { 162, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_3", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gainu_3), BLOCKIO_SIG, 0, 1, 2,
    324, 0 },

  { 163, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_4", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gainu_4), BLOCKIO_SIG, 0, 1, 2,
    326, 0 },

  { 164, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain BT power",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainBTpower), BLOCKIO_SIG, 0,
    1, 2, 328, 0 },

  { 165,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/delta rise limit",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, deltariselimit), BLOCKIO_SIG,
    0, 1, 2, 330, 0 },

  { 166,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Difference Inputs1",
    0, "( U(k) - Y(k-1) )", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, UkYk1),
    BLOCKIO_SIG, 0, 1, 2, 332, 0 },

  { 167, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Neg", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Neg), BLOCKIO_SIG, 0, 1, 2, 334, 0 },

  { 168,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/delta fall limit",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, deltafalllimit), BLOCKIO_SIG,
    0, 1, 2, 336, 0 },

  { 169,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Switch), BLOCKIO_SIG, 0, 1, 2,
    338, 0 },

  { 170,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic/Switch2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Switch2), BLOCKIO_SIG, 0, 1,
    2, 340, 0 },

  { 171,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Difference Inputs2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DifferenceInputs2),
    BLOCKIO_SIG, 0, 1, 2, 342, 0 },

  { 172, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Gain u_5", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gainu_5), BLOCKIO_SIG, 0, 1, 2,
    344, 0 },

  { 173,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/T_e^+ K_e^-1 u_e", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, T_eK_e1u_e), BLOCKIO_SIG, 17, 3,
    2, 346, 0 },

  { 174, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_surge_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, tau_surge_hil), BLOCKIO_SIG,
    0, 1, 2, 348, 0 },

  { 175, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_sway_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, tau_sway_hil), BLOCKIO_SIG, 0,
    1, 2, 350, 0 },

  { 176, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/tau_yaw_hil", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, tau_yaw_hil), BLOCKIO_SIG, 0, 1,
    2, 352, 0 },

  { 177, "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Sum", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum_j), BLOCKIO_SIG, 17, 3, 2,
    354, 0 },

  { 178,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/Vessel Dynamics/Product2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product2), BLOCKIO_SIG, 17, 3, 2,
    356, 0 },

  { 179,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Cartesian to Polar Port/x->r",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xr), BLOCKIO_SIG, 0, 1, 2,
    358, 0 },

  { 180,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Cartesian to Polar Port/x->theta",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xtheta), BLOCKIO_SIG, 0, 1, 2,
    360, 0 },

  { 181,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Cartesian to Polar Stbd/x->r",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xr_g), BLOCKIO_SIG, 0, 1, 2,
    362, 0 },

  { 182,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Cartesian to Polar Stbd/x->theta",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xtheta_a), BLOCKIO_SIG, 0, 1,
    2, 364, 0 },

  { 183,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/VSP_angle_deg_port",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, VSP_angle_deg_port),
    BLOCKIO_SIG, 0, 1, 2, 366, 0 },

  { 184,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/VSP_angle_deg_stbd",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, VSP_angle_deg_stbd),
    BLOCKIO_SIG, 0, 1, 2, 368, 0 },

  { 185, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_D_Gain1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2,
    370, 0 },

  { 186, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_D_Gain2", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2,
    372, 0 },

  { 187, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Add", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, Add), BLOCKIO_SIG, 0, 1, 2, 374, 0 },

  { 188, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_L_Gain1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2,
    376, 0 },

  { 189, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/BT_L_Gain2", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2,
    378, 0 },

  { 190, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Neg", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, Neg_d), BLOCKIO_SIG, 0, 1, 2, 380, 0 },

  { 191, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Sum1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum1_f), BLOCKIO_SIG, 0, 1, 2, 382, 0 },

  { 192, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Sum2", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum2_m), BLOCKIO_SIG, 0, 1, 2, 384, 0 },

  { 193,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Switch_n), BLOCKIO_SIG, 0, 1,
    2, 386, 0 },

  { 194,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Switch2_l), BLOCKIO_SIG, 0, 1,
    2, 388, 0 },

  { 195,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Switch_nw), BLOCKIO_SIG, 0, 1,
    2, 390, 0 },

  { 196,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Switch2_f), BLOCKIO_SIG, 0, 1,
    2, 392, 0 },

  { 197,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Switch_m), BLOCKIO_SIG, 0, 1,
    2, 394, 0 },

  { 198,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Switch2_o), BLOCKIO_SIG, 0, 1,
    2, 396, 0 },

  { 199, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Sign", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sign), BLOCKIO_SIG, 0, 1, 2, 398,
    0 },

  { 200, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Product1",
    0, "Port VPS_X", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PortVPS_X),
    BLOCKIO_SIG, 0, 1, 2, 400, 0 },

  { 201, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /-x", 0,
    "Port VPS_X", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PortVPS_X_a),
    BLOCKIO_SIG, 0, 1, 2, 402, 0 },

  { 202, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Product2",
    0, "Port VSP_Y", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PortVSP_Y),
    BLOCKIO_SIG, 0, 1, 2, 404, 0 },

  { 203, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /-y", 0,
    "Port VSP_Y", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, PortVSP_Y_a),
    BLOCKIO_SIG, 0, 1, 2, 406, 0 },

  { 204,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Port/x->r",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xr_l), BLOCKIO_SIG, 0, 1, 2,
    408, 0 },

  { 205,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Port/x->theta",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xtheta_b), BLOCKIO_SIG, 0, 1,
    2, 410, 0 },

  { 206, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Product3",
    0, "Starboard VSP_X", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, StarboardVSP_X),
    BLOCKIO_SIG, 0, 1, 2, 412, 0 },

  { 207, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Product4",
    0, "Starboard VSP_Y", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, StarboardVSP_Y),
    BLOCKIO_SIG, 0, 1, 2, 414, 0 },

  { 208,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Starboard/x->r",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xr_a), BLOCKIO_SIG, 0, 1, 2,
    416, 0 },

  { 209,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Starboard/x->theta",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xtheta_al), BLOCKIO_SIG, 0, 1,
    2, 418, 0 },

  { 210,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain), BLOCKIO_SIG, 0, 1, 2,
    420, 0 },

  { 211,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain_i), BLOCKIO_SIG, 0, 1, 2,
    422, 0 },

  { 212, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Servo1), BLOCKIO_SIG, 0, 1, 2,
    424, 0 },

  { 213, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Servo2), BLOCKIO_SIG, 0, 1, 2,
    426, 0 },

  { 214, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Servo3), BLOCKIO_SIG, 0, 1, 2,
    428, 0 },

  { 215, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Servo4",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Servo4), BLOCKIO_SIG, 0, 1, 2,
    430, 0 },

  { 216,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, VPS_Speed_Gain), BLOCKIO_SIG,
    0, 1, 2, 432, 0 },

  { 217, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /Sum", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum_e), BLOCKIO_SIG, 0, 1, 2,
    434, 0 },

  { 218,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VSPS Port", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, VSPSPort), BLOCKIO_SIG, 0, 1, 2,
    436, 0 },

  { 219,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, VSPSStarboard), BLOCKIO_SIG,
    0, 1, 2, 438, 0 },

  { 220, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_x1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_x1_e), BLOCKIO_SIG, 0, 1, 2, 440, 0 },

  { 221, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_y2", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_y2_l), BLOCKIO_SIG, 0, 1, 2, 442, 0 },

  { 222, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/-l_x2", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_x2_j), BLOCKIO_SIG, 0, 1, 2, 444, 0 },

  { 223, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/T_e/3x5", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, x5_df), BLOCKIO_SIG, 28, 15, 2, 446, 0 },

  { 224, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e1_CSE1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e1_CSE1), BLOCKIO_SIG, 0, 1, 2, 448, 0
  },

  { 225, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e2_CSE1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e2_CSE1), BLOCKIO_SIG, 0, 1, 2, 450, 0
  },

  { 226, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e3_CSE1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e3_CSE1), BLOCKIO_SIG, 0, 1, 2, 452, 0
  },

  { 227, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e4_CSE1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e4_CSE1), BLOCKIO_SIG, 0, 1, 2, 454, 0
  },

  { 228, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Gain K_e5_CSE1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e5_CSE1), BLOCKIO_SIG, 0, 1, 2, 456, 0
  },

  { 229, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/K_e/Thruster Gain matrix", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, ThrusterGainmatrix_l), BLOCKIO_SIG,
    24, 25, 2, 458, 0 },

  { 230, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/tau_cse1", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, tau_cse1), BLOCKIO_SIG, 17, 3, 2, 460, 0 },

  { 231, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_surge", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, CSE1tau_surge), BLOCKIO_SIG, 0, 1, 2, 462, 0
  },

  { 232, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_sway", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, CSE1tau_sway), BLOCKIO_SIG, 0, 1, 2, 464, 0
  },

  { 233, "ca_cse1_v1e_wo_losv2b/Plants/CSE1/CSE1 tau_yaw", 0, "", offsetof
    (BlockIO_CA_CSE1_V1e_wo_LOSV2b, CSE1tau_yaw), BLOCKIO_SIG, 0, 1, 2, 466, 0 },

  { 234,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator1",
    0, "eta_w", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta_w), BLOCKIO_SIG, 17,
    3, 2, 468, 0 },

  { 235, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/BT_power_limit", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, BT_power_limit), BLOCKIO_SIG, 0,
    1, 2, 470, 0 },

  { 236,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator",
    0, "eta", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, eta), BLOCKIO_SIG, 17, 3,
    2, 472, 0 },

  { 237,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation_m), BLOCKIO_SIG, 0,
    1, 2, 474, 0 },

  { 238,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sign_k), BLOCKIO_SIG, 0, 1, 2,
    476, 0 },

  { 239,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain_k), BLOCKIO_SIG, 0, 1, 2,
    478, 0 },

  { 240,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum1_i), BLOCKIO_SIG, 0, 1, 2,
    480, 0 },

  { 241,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, MathFunction), BLOCKIO_SIG, 0,
    1, 2, 482, 0 },

  { 242,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum_jb), BLOCKIO_SIG, 0, 1, 2,
    484, 0 },

  { 243, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Multiport Switch", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, MultiportSwitch_j), BLOCKIO_SIG,
    17, 3, 2, 486, 0 },

  { 244, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta N",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, etaN), BLOCKIO_SIG, 0, 1, 2,
    488, 0 },

  { 245, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta E",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, etaE), BLOCKIO_SIG, 0, 1, 2,
    490, 0 },

  { 246,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta Psi", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, etaPsi), BLOCKIO_SIG, 0, 1, 2,
    492, 0 },

  { 247, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Sum2",
    0, "regulation error", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b,
    regulationerror), BLOCKIO_SIG, 17, 3, 2, 494, 0 },

  { 248,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_N_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Reg_e_N_hil), BLOCKIO_SIG, 0,
    1, 2, 496, 0 },

  { 249,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_E_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Reg_e_E_hil), BLOCKIO_SIG, 0,
    1, 2, 498, 0 },

  { 250,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_Psi_hil",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Reg_e_Psi_hil), BLOCKIO_SIG,
    0, 1, 2, 500, 0 },

  { 251,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Integrator",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Integrator_o), BLOCKIO_SIG,
    17, 3, 2, 502, 0 },

  { 252,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator4",
    0, "nu", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, nu), BLOCKIO_SIG, 17, 3, 2,
    504, 0 },

  { 253, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Multiport Switch1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, MultiportSwitch1), BLOCKIO_SIG,
    17, 3, 2, 506, 0 },

  { 254, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kd", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Kd), BLOCKIO_SIG, 17, 3, 2, 508,
    0 },

  { 255,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Product", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product_f), BLOCKIO_SIG, 17, 3,
    2, 510, 0 },

  { 256, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_d1), BLOCKIO_SIG, 0, 1, 2,
    512, 0 },

  { 257, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_d2), BLOCKIO_SIG, 0, 1, 2,
    514, 0 },

  { 258, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_d3), BLOCKIO_SIG, 0, 1, 2,
    516, 0 },

  { 259,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_d 3 deg",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_d3deg), BLOCKIO_SIG, 0, 1,
    2, 518, 0 },

  { 260, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Ki", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Ki), BLOCKIO_SIG, 17, 3, 2, 520,
    0 },

  { 261,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Product1", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product1_l), BLOCKIO_SIG, 17, 3,
    2, 522, 0 },

  { 262, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_i1), BLOCKIO_SIG, 0, 1, 2,
    524, 0 },

  { 263, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_i2), BLOCKIO_SIG, 0, 1, 2,
    526, 0 },

  { 264, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_i3), BLOCKIO_SIG, 0, 1, 2,
    528, 0 },

  { 265,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_i 3 deg",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_i3deg), BLOCKIO_SIG, 0, 1,
    2, 530, 0 },

  { 266,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/yaw angle",
    0, "psi", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, psi), BLOCKIO_SIG, 0, 1, 2,
    532, 0 },

  { 267,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation_h), BLOCKIO_SIG, 0,
    1, 2, 534, 0 },

  { 268,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sign_i), BLOCKIO_SIG, 0, 1, 2,
    536, 0 },

  { 269,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain_h), BLOCKIO_SIG, 0, 1, 2,
    538, 0 },

  { 270,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum1_h), BLOCKIO_SIG, 0, 1, 2,
    540, 0 },

  { 271,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, MathFunction_a), BLOCKIO_SIG,
    0, 1, 2, 542, 0 },

  { 272,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum_k), BLOCKIO_SIG, 0, 1, 2,
    544, 0 },

  { 273,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation_m4), BLOCKIO_SIG,
    0, 1, 2, 546, 0 },

  { 274,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sign_b), BLOCKIO_SIG, 0, 1, 2,
    548, 0 },

  { 275,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain_ki), BLOCKIO_SIG, 0, 1,
    2, 550, 0 },

  { 276,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum1_o), BLOCKIO_SIG, 0, 1, 2,
    552, 0 },

  { 277,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, MathFunction_d), BLOCKIO_SIG,
    0, 1, 2, 554, 0 },

  { 278,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum_o), BLOCKIO_SIG, 0, 1, 2,
    556, 0 },

  { 279,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row1), BLOCKIO_SIG, 0, 1, 2,
    558, 0 },

  { 280,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row2), BLOCKIO_SIG, 0, 1, 2,
    560, 0 },

  { 281,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row3), BLOCKIO_SIG, 0, 1, 2,
    562, 0 },

  { 282, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Kp", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Kp), BLOCKIO_SIG, 17, 3, 2, 564,
    0 },

  { 283,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Product2", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product2_d), BLOCKIO_SIG, 17, 3,
    2, 566, 0 },

  { 284, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_p1), BLOCKIO_SIG, 0, 1, 2,
    568, 0 },

  { 285, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_p2), BLOCKIO_SIG, 0, 1, 2,
    570, 0 },

  { 286, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_p3), BLOCKIO_SIG, 0, 1, 2,
    572, 0 },

  { 287,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/K_p 3 deg",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_p3deg), BLOCKIO_SIG, 0, 1,
    2, 574, 0 },

  { 288,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Reg_e_Psi_deg",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Reg_e_Psi_deg), BLOCKIO_SIG,
    0, 1, 2, 576, 0 },

  { 289, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Sum3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum3), BLOCKIO_SIG, 17, 3, 2,
    578, 0 },

  { 290, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/Sum1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum1_g), BLOCKIO_SIG, 17, 3,
    2, 580, 0 },

  { 291,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP controller/eta Psi deg",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, etaPsideg), BLOCKIO_SIG, 0, 1,
    2, 582, 0 },

  { 292, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_surge", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DPtau_surge), BLOCKIO_SIG, 0, 1, 2,
    584, 0 },

  { 293, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_sway", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DPtau_sway), BLOCKIO_SIG, 0, 1, 2,
    586, 0 },

  { 294, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP tau_yaw", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DPtau_yaw), BLOCKIO_SIG, 0, 1, 2,
    588, 0 },

  { 295, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e1_DP", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e1_DP), BLOCKIO_SIG, 0, 1,
    2, 590, 0 },

  { 296, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e2_DP", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e2_DP), BLOCKIO_SIG, 0, 1,
    2, 592, 0 },

  { 297, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e3_DP", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e3_DP), BLOCKIO_SIG, 0, 1,
    2, 594, 0 },

  { 298, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e4_DP", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e4_DP), BLOCKIO_SIG, 0, 1,
    2, 596, 0 },

  { 299, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Gain K_e5_DP", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, GainK_e5_DP), BLOCKIO_SIG, 0, 1,
    2, 598, 0 },

  { 300,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e/Thruster Gain matrix",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, ThrusterGainmatrix_f),
    BLOCKIO_SIG, 24, 25, 2, 600, 0 },

  { 301, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/K_e^-1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K_e1_b), BLOCKIO_SIG, 24, 25, 2, 602,
    0 },

  { 302, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_x1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_x1_jy), BLOCKIO_SIG, 0, 1, 2, 604,
    0 },

  { 303, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_y2", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_y2_n), BLOCKIO_SIG, 0, 1, 2, 606,
    0 },

  { 304, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/-l_x2", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, l_x2_jn), BLOCKIO_SIG, 0, 1, 2, 608,
    0 },

  { 305, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e/3x5", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, x5_o), BLOCKIO_SIG, 28, 15, 2, 610,
    0 },

  { 306, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/T_e^+", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, T_e_a), BLOCKIO_SIG, 27, 15, 2, 612,
    0 },

  { 307, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Product", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product_b), BLOCKIO_SIG, 27, 15, 2,
    614, 0 },

  { 308, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Product1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Product1_be), BLOCKIO_SIG, 23, 5, 2,
    616, 0 },

  { 309, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_1", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DPu_1), BLOCKIO_SIG, 0, 1, 2, 618, 0
  },

  { 310, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_2", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DPu_2), BLOCKIO_SIG, 0, 1, 2, 620, 0
  },

  { 311, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_3", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DPu_3), BLOCKIO_SIG, 0, 1, 2, 622, 0
  },

  { 312, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_4", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DPu_4), BLOCKIO_SIG, 0, 1, 2, 624, 0
  },

  { 313, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/DP u_5", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, DPu_5), BLOCKIO_SIG, 0, 1, 2, 626, 0
  },

  { 314,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain1_o), BLOCKIO_SIG, 17, 3,
    2, 628, 0 },

  { 315,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator2",
    0, "xi_w", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, xi_w), BLOCKIO_SIG, 17, 3,
    2, 630, 0 },

  { 316,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain2), BLOCKIO_SIG, 17, 3, 2,
    632, 0 },

  { 317,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Sum4",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum4), BLOCKIO_SIG, 17, 3, 2,
    634, 0 },

  { 318,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Sum2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum2_d), BLOCKIO_SIG, 17, 3,
    2, 636, 0 },

  { 319,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation_n), BLOCKIO_SIG, 0,
    1, 2, 638, 0 },

  { 320,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sign_h), BLOCKIO_SIG, 0, 1, 2,
    640, 0 },

  { 321,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain_f), BLOCKIO_SIG, 0, 1, 2,
    642, 0 },

  { 322,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum1_c), BLOCKIO_SIG, 0, 1, 2,
    644, 0 },

  { 323,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, MathFunction_j), BLOCKIO_SIG,
    0, 1, 2, 646, 0 },

  { 324,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum_i), BLOCKIO_SIG, 0, 1, 2,
    648, 0 },

  { 325,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K4",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K4), BLOCKIO_SIG, 17, 3, 2,
    650, 0 },

  { 326,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row1_c), BLOCKIO_SIG, 0, 1, 2,
    652, 0 },

  { 327,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row2_b), BLOCKIO_SIG, 0, 1, 2,
    654, 0 },

  { 328,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row3_n), BLOCKIO_SIG, 0, 1, 2,
    656, 0 },

  { 329,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Integrator3",
    0, "bias", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, bias), BLOCKIO_SIG, 17, 3,
    2, 658, 0 },

  { 330,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row1_k), BLOCKIO_SIG, 0, 1, 2,
    660, 0 },

  { 331,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row2_bv), BLOCKIO_SIG, 0, 1,
    2, 662, 0 },

  { 332,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Row3_l), BLOCKIO_SIG, 0, 1, 2,
    664, 0 },

  { 333,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Sum1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum1_a), BLOCKIO_SIG, 17, 3,
    2, 666, 0 },

  { 334,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain6",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain6), BLOCKIO_SIG, 17, 3, 2,
    668, 0 },

  { 335,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Sum8",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum8), BLOCKIO_SIG, 17, 3, 2,
    670, 0 },

  { 336,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Gain3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Gain3), BLOCKIO_SIG, 17, 3, 2,
    672, 0 },

  { 337,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K11",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K11), BLOCKIO_SIG, 17, 3, 2,
    674, 0 },

  { 338,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K12",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K12), BLOCKIO_SIG, 17, 3, 2,
    676, 0 },

  { 339,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K2",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K2), BLOCKIO_SIG, 17, 3, 2,
    678, 0 },

  { 340,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/K3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, K3), BLOCKIO_SIG, 17, 3, 2,
    680, 0 },

  { 341,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn",
    0, "x_dot", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, x_dot), BLOCKIO_SIG, 0,
    1, 2, 682, 0 },

  { 342,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn1",
    0, "y_dot", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, y_dot), BLOCKIO_SIG, 0,
    1, 2, 684, 0 },

  { 343,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn2",
    0, "psi_dot", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, psi_dot), BLOCKIO_SIG,
    0, 1, 2, 686, 0 },

  { 344,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Sum3",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum3_k), BLOCKIO_SIG, 17, 3,
    2, 688, 0 },

  { 345,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Sum5",
    0, "psi_WF", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, psi_WF), BLOCKIO_SIG,
    17, 3, 2, 690, 0 },

  { 346,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Sum6",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum6), BLOCKIO_SIG, 17, 3, 2,
    692, 0 },

  { 347,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/inv(T_b)",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, invT_b), BLOCKIO_SIG, 17, 3,
    2, 694, 0 },

  { 348,
    "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Passive DP wave filter1/Sum7",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Sum7), BLOCKIO_SIG, 17, 3, 2,
    696, 0 },

  { 349, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/Saturation", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Saturation_f), BLOCKIO_SIG, 23, 5, 2,
    698, 0 },

  { 350, "ca_cse1_v1e_wo_losv2b/Control Systems/DP control/VSP_speeds", 0, "",
    offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, VSP_speeds), BLOCKIO_SIG, 0, 1, 2,
    700, 0 },

  { 351, "ca_cse1_v1e_wo_losv2b/Control Systems/if DP Control Mode/Compare", 0,
    "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, Compare), BLOCKIO_SIG, 3, 1, 2,
    702, 0 },

  { 352,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, LowerRelop1), BLOCKIO_SIG, 8,
    1, 2, 704, 0 },

  { 353,
    "ca_cse1_v1e_wo_losv2b/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, UpperRelop), BLOCKIO_SIG, 8,
    1, 2, 706, 0 },

  { 354,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, LowerRelop1_n), BLOCKIO_SIG,
    8, 1, 2, 708, 0 },

  { 355,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, UpperRelop_d), BLOCKIO_SIG, 8,
    1, 2, 710, 0 },

  { 356,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic1/LowerRelop1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, LowerRelop1_o), BLOCKIO_SIG,
    8, 1, 2, 712, 0 },

  { 357,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic1/UpperRelop",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, UpperRelop_o), BLOCKIO_SIG, 8,
    1, 2, 714, 0 },

  { 358,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic2/LowerRelop1",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, LowerRelop1_j), BLOCKIO_SIG,
    8, 1, 2, 716, 0 },

  { 359,
    "ca_cse1_v1e_wo_losv2b/Plants/CSE1/Bow Thruster/Saturation Dynamic2/UpperRelop",
    0, "", offsetof(BlockIO_CA_CSE1_V1e_wo_LOSV2b, UpperRelop_h), BLOCKIO_SIG, 8,
    1, 2, 718, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 3, 5,
  5, 3, 5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 5,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1,
  9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  3, 3, 6, 6, 1, 1, 1, 1, 1, 6, 1, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1, 7, 1, 7, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 3, 5, 5, 3, 5, 3, 1, 5, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
  1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 5, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize = 11;
static NI_ExternalIO NI_ExtList[] = {
  { 0, "Naviagation Systems/Qualisys 6 DOF/QTM In", 0, EXT_IN, 9, 9, 1 },

  { 1, "HMI/SIT zAI0", 1, EXT_IN, 1, 1, 1 },

  { 2, "HMI/SIT zAI1", 1, EXT_IN, 1, 1, 1 },

  { 3, "HMI/SIT zAI2", 1, EXT_IN, 1, 1, 1 },

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

static char* NI_CompiledModelName = "ca_cse1_v1e_wo_losv2b";
static char* NI_CompiledModelVersion = "1.193";
static char* NI_CompiledModelDateTime = "Fri Sep 20 14:52:12 2013";

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
   The undef allows us to access the real CA_CSE1_V1e_wo_LOSV2b_P
   In the rest of the code CA_CSE1_V1e_wo_LOSV2b_P is redefine to be the read-side
   of rtParameter.
 */
#undef CA_CSE1_V1e_wo_LOSV2b_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &CA_CSE1_V1e_wo_LOSV2b_P, sizeof
         (Parameters_CA_CSE1_V1e_wo_LOSV2));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka CA_CSE1_V1e_wo_LOSV2b_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof
           (Parameters_CA_CSE1_V1e_wo_LOSV2));
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
             (Parameters_CA_CSE1_V1e_wo_LOSV2));

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
           (Parameters_CA_CSE1_V1e_wo_LOSV2));
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

#endif                                 // of NI_ROOTMODEL_CA_CSE1_V1e_wo_LOSV2b
