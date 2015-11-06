/*
 * LgV2.c
 *
 * Real-Time Workshop code generation for Simulink model "LgV2.mdl".
 *
 * Model Version              : 1.198
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Wed Nov 27 14:51:19 2013
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
  LgV2_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  LgV2_output(0);
  LgV2_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE3_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  LgV2_output(0);
  LgV2_derivatives();

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
    real_T tmp_2[15];
    int32_T tmp_3;
    int32_T tmp_4;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Gain: '<S26>/Accuracy u_1' incorporates:
       *  Constant: '<S26>/u1'
       */
      LgV2_B.Accuracyu_1 = LgV2_P.Accuracyu_1_Gain * LgV2_P.u1_Value;

      /* Gain: '<S26>/Accuracy u_2' incorporates:
       *  Constant: '<S26>/u2'
       */
      LgV2_B.Accuracyu_2 = LgV2_P.Accuracyu_2_Gain * LgV2_P.u2_Value;

      /* Gain: '<S26>/Accuracy u_3' incorporates:
       *  Constant: '<S26>/u3'
       */
      LgV2_B.Accuracyu_3 = LgV2_P.Accuracyu_3_Gain * LgV2_P.u3_Value;

      /* Gain: '<S26>/Accuracy u_4' incorporates:
       *  Constant: '<S26>/u4'
       */
      LgV2_B.Accuracyu_4 = LgV2_P.Accuracyu_4_Gain * LgV2_P.u4_Value;

      /* Gain: '<S26>/Accuracy u_5' incorporates:
       *  Constant: '<S26>/u5'
       */
      LgV2_B.Accuracyu_5 = LgV2_P.Accuracyu_5_Gain * LgV2_P.u5_Value;

      /* Gain: '<S30>/Scaling_JS_L_Y' incorporates:
       *  Constant: '<S30>/JS_L_Y'
       */
      LgV2_B.u1 = LgV2_P.Scaling_JS_L_Y_Gain * LgV2_P.JS_L_Y_Value;

      /* Gain: '<S9>/PS3 u_1' */
      LgV2_B.PS3u_1 = LgV2_P.PS3u_1_Gain * LgV2_B.u1;

      /* Gain: '<S30>/Scaling_JS_L_X' incorporates:
       *  Constant: '<S30>/JS_L_X'
       */
      LgV2_B.u1_b = LgV2_P.Scaling_JS_L_X_Gain * LgV2_P.JS_L_X_Value;

      /* Gain: '<S9>/PS3 u_2' */
      LgV2_B.PS3u_2 = LgV2_P.PS3u_2_Gain * LgV2_B.u1_b;

      /* Gain: '<S30>/Scaling_JS_R_Y' incorporates:
       *  Constant: '<S30>/JS_R_Y'
       */
      LgV2_B.u1_l = LgV2_P.Scaling_JS_R_Y_Gain * LgV2_P.JS_R_Y_Value;

      /* Gain: '<S9>/PS3 u_3' */
      LgV2_B.PS3u_3 = LgV2_P.PS3u_3_Gain * LgV2_B.u1_l;

      /* Gain: '<S30>/Scaling_JS_R_X' incorporates:
       *  Constant: '<S30>/JS_R_X'
       */
      LgV2_B.u1_c = LgV2_P.Scaling_JS_R_X_Gain * LgV2_P.JS_R_X_Value;

      /* Gain: '<S9>/PS3 u_4' */
      LgV2_B.PS3u_4 = LgV2_P.PS3u_4_Gain * LgV2_B.u1_c;

      /* Sum: '<S9>/Add' incorporates:
       *  Constant: '<S30>/L2'
       *  Constant: '<S30>/R2'
       */
      LgV2_B.BowThrusterdirection = LgV2_P.L2_Value + LgV2_P.R2_Value;

      /* Gain: '<S9>/PS3 u_5' */
      LgV2_B.PS3u_5 = LgV2_P.PS3u_5_Gain * LgV2_B.BowThrusterdirection;

      /* Gain: '<S23>/Gain K_e1_joystick' incorporates:
       *  Constant: '<S23>/K_e1_joystick'
       */
      LgV2_B.GainK_e1_joystick = LgV2_P.GainK_e1_joystick_Gain *
        LgV2_P.K_e1_joystick_Value;

      /* Gain: '<S23>/Gain K_e2_joystick' incorporates:
       *  Constant: '<S23>/K_e2_joystick'
       */
      LgV2_B.GainK_e2_joystick = LgV2_P.GainK_e2_joystick_Gain *
        LgV2_P.K_e2_joystick_Value;

      /* Gain: '<S23>/Gain K_e3_joystick' incorporates:
       *  Constant: '<S23>/K_e3_joystick'
       */
      LgV2_B.GainK_e3_joystick = LgV2_P.GainK_e3_joystick_Gain *
        LgV2_P.K_e3_joystick_Value;

      /* Gain: '<S23>/Gain K_e4_joystick' incorporates:
       *  Constant: '<S23>/K_e4_joystick'
       */
      LgV2_B.GainK_e4_joystick = LgV2_P.GainK_e4_joystick_Gain *
        LgV2_P.K_e4_joystick_Value;

      /* Gain: '<S23>/Gain K_e5_joystick' incorporates:
       *  Constant: '<S23>/K_e5_joystick'
       */
      LgV2_B.GainK_e5_joystick = LgV2_P.GainK_e5_joystick_Gain *
        LgV2_P.K_e5_joystick_Value;

      /* Reshape: '<S23>/Thruster Gain matrix' incorporates:
       *  Constant: '<S23>/Constant'
       */
      LgV2_B.ThrusterGainmatrix[0] = LgV2_B.GainK_e1_joystick;
      LgV2_B.ThrusterGainmatrix[1] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[2] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[3] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[4] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[5] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[6] = LgV2_B.GainK_e2_joystick;
      LgV2_B.ThrusterGainmatrix[7] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[8] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[9] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[10] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[11] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[12] = LgV2_B.GainK_e3_joystick;
      LgV2_B.ThrusterGainmatrix[13] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[14] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[15] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[16] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[17] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[18] = LgV2_B.GainK_e4_joystick;
      LgV2_B.ThrusterGainmatrix[19] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[20] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[21] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[22] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[23] = LgV2_P.Constant_Value;
      LgV2_B.ThrusterGainmatrix[24] = LgV2_B.GainK_e5_joystick;

      /* Product Block: '<S8>/K_e^-1' */
      {
        static const int_T dims[3] = { 5, 5, 5 };

        rt_MatDivRR_Dbl(LgV2_B.K_e1, LgV2_B.ThrusterGainmatrix,
                        &LgV2_DWork.K_e1_DWORK4[0], (real_T*)
                        &LgV2_DWork.K_e1_DWORK1[0],
                        &LgV2_DWork.K_e1_DWORK2[0], (real_T*)
                        &LgV2_DWork.K_e1_DWORK3[0],
                        &dims[0]);
      }

      /* Gain: '<S24>/-l_x1' incorporates:
       *  Constant: '<S24>/l_x1'
       */
      LgV2_B.l_x1 = LgV2_P.l_x1_Gain * LgV2_P.l_x1_Value;

      /* Gain: '<S24>/-l_y2' incorporates:
       *  Constant: '<S24>/l_y2'
       */
      LgV2_B.l_y2 = LgV2_P.l_y2_Gain * LgV2_P.l_y2_Value;

      /* Gain: '<S24>/-l_x2' incorporates:
       *  Constant: '<S24>/l_x2'
       */
      LgV2_B.l_x2 = LgV2_P.l_x2_Gain * LgV2_P.l_x2_Value;

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

      /* S-Function (sdsppinv): '<S8>/T_e^+' */
      /* Copy input to temporary space */
      memcpy((void *)(&LgV2_DWork.K_e1_DWORK1[0]), (void *)(&LgV2_B.x5[0]), 15U *
             sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&LgV2_DWork.K_e1_DWORK1[0], 3, 5, &LgV2_DWork.T_e_S[0],
                      &LgV2_DWork.K_e1_DWORK3[0], &LgV2_DWork.T_e_WORK[0],
                      &LgV2_DWork.T_e_U[0], &LgV2_DWork.T_e_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&LgV2_DWork.T_e_S[0], &LgV2_DWork.T_e_U[0],
          &LgV2_DWork.T_e_V[0], &LgV2_B.T_e[0], (const int32_T)3, (const int32_T)
          5);
      }

      /* Product: '<S8>/T_e^+ K_e^-1' */
      for (i = 0; i < 5; i++) {
        for (tmp_4 = 0; tmp_4 < 3; tmp_4++) {
          LgV2_B.T_eK_e1[i + 5 * tmp_4] = 0.0;
          for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
            LgV2_B.T_eK_e1[i + 5 * tmp_4] = LgV2_B.K_e1[5 * tmp_3 + i] *
              LgV2_B.T_e[5 * tmp_4 + tmp_3] + LgV2_B.T_eK_e1[5 * tmp_4 + i];
          }
        }
      }

      /* Sum: '<S8>/Sum1' */
      LgV2_B.Sum1 = LgV2_B.u1 + LgV2_B.u1_l;

      /* Gain: '<S8>/Joystick tau_surge' */
      LgV2_B.Joysticktau_surge = LgV2_P.Joysticktau_surge_Gain * LgV2_B.Sum1;

      /* Saturate: '<S8>/Saturation1' */
      tmp = LgV2_B.Joysticktau_surge;
      LgV2_B.Saturation1 = rt_SATURATE(tmp, LgV2_P.Saturation1_LowerSat,
        LgV2_P.Saturation1_UpperSat);

      /* Sum: '<S8>/Sum2' */
      LgV2_B.Sum2 = LgV2_B.u1_b + LgV2_B.u1_c;

      /* Gain: '<S8>/Joystick tau_sway' */
      LgV2_B.Joysticktau_sway = LgV2_P.Joysticktau_sway_Gain * LgV2_B.Sum2;

      /* Saturate: '<S8>/Saturation2' */
      tmp = LgV2_B.Joysticktau_sway;
      LgV2_B.Saturation2 = rt_SATURATE(tmp, LgV2_P.Saturation2_LowerSat,
        LgV2_P.Saturation2_UpperSat);

      /* Sum: '<S8>/Sum' incorporates:
       *  Constant: '<S30>/L2'
       *  Constant: '<S30>/R2'
       */
      LgV2_B.Sum = LgV2_P.L2_Value + LgV2_P.R2_Value;

      /* Gain: '<S8>/Joystick tau_yaw' */
      LgV2_B.Joysticktau_yaw = LgV2_P.Joysticktau_yaw_Gain * LgV2_B.Sum;

      /* Saturate: '<S8>/Saturation3' */
      tmp = LgV2_B.Joysticktau_yaw;
      LgV2_B.Saturation3 = rt_SATURATE(tmp, LgV2_P.Saturation3_LowerSat,
        LgV2_P.Saturation3_UpperSat);

      /* SignalConversion: '<S8>/TmpHiddenBufferAtProduct1Inport2' */
      LgV2_B.TmpHiddenBufferAtProduct1Inport[0] = LgV2_B.Saturation1;
      LgV2_B.TmpHiddenBufferAtProduct1Inport[1] = LgV2_B.Saturation2;
      LgV2_B.TmpHiddenBufferAtProduct1Inport[2] = LgV2_B.Saturation3;

      /* Saturate: '<S8>/Saturation' */
      for (i = 0; i < 5; i++) {
        /* Product: '<S8>/Product1' */
        LgV2_B.Product1[i] = 0.0;
        LgV2_B.Product1[i] = LgV2_B.T_eK_e1[i] *
          LgV2_B.TmpHiddenBufferAtProduct1Inport[0] + LgV2_B.Product1[i];
        LgV2_B.Product1[i] = LgV2_B.T_eK_e1[i + 5] *
          LgV2_B.TmpHiddenBufferAtProduct1Inport[1] + LgV2_B.Product1[i];
        LgV2_B.Product1[i] = LgV2_B.T_eK_e1[i + 10] *
          LgV2_B.TmpHiddenBufferAtProduct1Inport[2] + LgV2_B.Product1[i];
        tmp_0[i] = LgV2_B.Product1[i];
        LgV2_B.Saturation[i] = rt_SATURATE(tmp_0[i], LgV2_P.Saturation_LowerSat,
          LgV2_P.Saturation_UpperSat);
      }

      /* Gain: '<S8>/Joystick u_1' */
      LgV2_B.Joysticku_1 = LgV2_P.Joysticku_1_Gain * LgV2_B.Saturation[0];

      /* Gain: '<S8>/Joystick u_2' */
      LgV2_B.Joysticku_2 = LgV2_P.Joysticku_2_Gain * LgV2_B.Saturation[1];

      /* Gain: '<S8>/Joystick u_3' */
      LgV2_B.Joysticku_3 = LgV2_P.Joysticku_3_Gain * LgV2_B.Saturation[2];

      /* Gain: '<S8>/Joystick u_4' */
      LgV2_B.Joysticku_4 = LgV2_P.Joysticku_4_Gain * LgV2_B.Saturation[3];

      /* Gain: '<S8>/Joystick u_5' */
      LgV2_B.Joysticku_5 = LgV2_P.Joysticku_5_Gain * LgV2_B.Saturation[4];

      /* Gain: '<S29>/Gain1' incorporates:
       *  Constant: '<S27>/psi_d'
       */
      LgV2_B.Gain1 = LgV2_P.Gain1_Gain * LgV2_P.psi_d_Value;
    }

    /* TransferFcn Block: '<S25>/Transfer Fcn' */
    LgV2_B.TransferFcn = LgV2_P.TransferFcn_C*LgV2_X.TransferFcn_CSTATE;

    /* TransferFcn Block: '<S25>/Transfer Fcn1' */
    LgV2_B.TransferFcn1 = LgV2_P.TransferFcn1_C*LgV2_X.TransferFcn1_CSTATE;

    /* TransferFcn Block: '<S25>/Transfer Fcn2' */
    LgV2_B.TransferFcn2 = LgV2_P.TransferFcn2_C*LgV2_X.TransferFcn2_CSTATE;

    /* MultiPortSwitch: '<S25>/Multiport Switch' incorporates:
     *  Constant: '<S25>/Enable eta_d LPF'
     *  Constant: '<S27>/x_d'
     *  Constant: '<S27>/y_d'
     */
    if ((int32_T)LgV2_P.Enableeta_dLPF_Value == 0) {
      LgV2_B.MultiportSwitch[0] = LgV2_P.x_d_Value;
      LgV2_B.MultiportSwitch[1] = LgV2_P.y_d_Value;
      LgV2_B.MultiportSwitch[2] = LgV2_B.Gain1;
    } else {
      LgV2_B.MultiportSwitch[0] = LgV2_B.TransferFcn;
      LgV2_B.MultiportSwitch[1] = LgV2_B.TransferFcn1;
      LgV2_B.MultiportSwitch[2] = LgV2_B.TransferFcn2;
    }

    /* Gain: '<S25>/eta_d DP N' */
    LgV2_B.eta_dDPN = LgV2_P.eta_dDPN_Gain * LgV2_B.MultiportSwitch[0];

    /* Gain: '<S25>/eta_d DP E' */
    LgV2_B.eta_dDPE = LgV2_P.eta_dDPE_Gain * LgV2_B.MultiportSwitch[1];

    /* Gain: '<S25>/eta_d DP Psi' */
    LgV2_B.eta_dDPPsi = LgV2_P.eta_dDPPsi_Gain * LgV2_B.MultiportSwitch[2];

    /* Gain: '<S31>/QTM In3' */
    LgV2_B.QTMIn3 = LgV2_P.QTMIn3_Gain * LgV2_B.QTMIn[2];

    /* Gain: '<S31>/mm2m x' */
    LgV2_B.mm2mx = LgV2_P.mm2mx_Gain * LgV2_B.QTMIn3;

    /* Gain: '<S31>/QTM In4' */
    LgV2_B.QTMIn4 = LgV2_P.QTMIn4_Gain * LgV2_B.QTMIn[3];

    /* Gain: '<S31>/mm2m y' */
    LgV2_B.mm2my = LgV2_P.mm2my_Gain * LgV2_B.QTMIn4;

    /* Gain: '<S31>/QTM In6' */
    LgV2_B.QTMIn6 = LgV2_P.QTMIn6_Gain * LgV2_B.QTMIn[5];

    /* Gain: '<S31>/d2r yaw' */
    LgV2_B.d2ryaw = LgV2_P.d2ryaw_Gain * LgV2_B.QTMIn6;

    /* Outputs for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Constant: '<S5>/Enable Linear Simulator'
     *  EnablePort: '<S34>/Enable'
     */
    if (rtmIsMajorTimeStep(LgV2_M) && rtmIsMajorTimeStep(LgV2_M)) {
      if (LgV2_P.EnableLinearSimulator_Value > 0.0) {
        if (LgV2_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S46>/Integrator' */
          if (rtmIsFirstInitCond(LgV2_M)) {
            LgV2_X.Integrator_CSTATE[0] = 0.0;
            LgV2_X.Integrator_CSTATE[1] = 0.0;
            LgV2_X.Integrator_CSTATE[2] = 0.0;
          }

          LgV2_DWork.Integrator_IWORK.IcNeedsLoading = 1;

          /* Integrator Block: '<S46>/Integrator1' */
          if (rtmIsFirstInitCond(LgV2_M)) {
            LgV2_X.Integrator1_CSTATE[0] = 0.0;
            LgV2_X.Integrator1_CSTATE[1] = 0.0;
            LgV2_X.Integrator1_CSTATE[2] = 0.0;
          }

          LgV2_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

          /* InitializeConditions for UnitDelay: '<S56>/Delay Input2' */
          LgV2_DWork.DelayInput2_DSTATE = LgV2_P.DelayInput2_X0;
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
        /* Gain: '<S48>/-N_r' incorporates:
         *  Constant: '<S48>/N_r'
         */
        LgV2_B.N_r = LgV2_P.N_r_Gain * LgV2_P.N_r_Value;

        /* Gain: '<S48>/-N_v' incorporates:
         *  Constant: '<S48>/N_v'
         */
        LgV2_B.N_v = LgV2_P.N_v_Gain * LgV2_P.N_v_Value;

        /* Gain: '<S48>/-X_u' incorporates:
         *  Constant: '<S48>/X_u'
         */
        LgV2_B.X_u = LgV2_P.X_u_Gain * LgV2_P.X_u_Value;

        /* Gain: '<S48>/-Y_v' incorporates:
         *  Constant: '<S48>/Y_v'
         */
        LgV2_B.Y_v = LgV2_P.Y_v_Gain * LgV2_P.Y_v_Value;

        /* Gain: '<S48>/-Y_vr' incorporates:
         *  Constant: '<S48>/Y_r'
         */
        LgV2_B.Y_vr = LgV2_P.Y_vr_Gain * LgV2_P.Y_r_Value;

        /* Reshape: '<S48>/Linear Dampning matrix' incorporates:
         *  Constant: '<S48>/D_L_12'
         *  Constant: '<S48>/D_L_13'
         *  Constant: '<S48>/D_L_21'
         *  Constant: '<S48>/D_L_31'
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

        /* Constant: '<S49>/psi_0' */
        LgV2_B.psi_0 = LgV2_P.psi_0_Value;

        /* Constant: '<S49>/x_0' */
        LgV2_B.x_0 = LgV2_P.x_0_Value;

        /* Constant: '<S49>/y_0' */
        LgV2_B.y_0 = LgV2_P.y_0_Value;

        /* Constant: '<S50>/r_0' */
        LgV2_B.r_0 = LgV2_P.r_0_Value;

        /* Constant: '<S50>/u_0' */
        LgV2_B.u_0 = LgV2_P.u_0_Value;

        /* Constant: '<S50>/v_0' */
        LgV2_B.v_0 = LgV2_P.v_0_Value;
      }

      /* Integrator Block: '<S46>/Integrator'
       */
      if (rtmIsMajorTimeStep(LgV2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &LgV2_PrevZCSigState.Integrator_Reset_ZCE,
                           LgV2_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || LgV2_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            LgV2_DWork.Integrator_IWORK.IcNeedsLoading) {
          LgV2_X.Integrator_CSTATE[0] = LgV2_B.u_0;
          LgV2_X.Integrator_CSTATE[1] = LgV2_B.v_0;
          LgV2_X.Integrator_CSTATE[2] = LgV2_B.r_0;
        }

        LgV2_DWork.Integrator_IWORK.IcNeedsLoading = 0;
      }

      LgV2_B.Integrator[0] = LgV2_X.Integrator_CSTATE[0];
      LgV2_B.Integrator[1] = LgV2_X.Integrator_CSTATE[1];
      LgV2_B.Integrator[2] = LgV2_X.Integrator_CSTATE[2];

      /* Integrator Block: '<S46>/Integrator1'
       */
      if (rtmIsMajorTimeStep(LgV2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &LgV2_PrevZCSigState.Integrator1_Reset_ZCE,
                           LgV2_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || LgV2_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            LgV2_DWork.Integrator1_IWORK.IcNeedsLoading) {
          LgV2_X.Integrator1_CSTATE[0] = LgV2_B.x_0;
          LgV2_X.Integrator1_CSTATE[1] = LgV2_B.y_0;
          LgV2_X.Integrator1_CSTATE[2] = LgV2_B.psi_0;
        }

        LgV2_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
      }

      LgV2_B.Integrator1[0] = LgV2_X.Integrator1_CSTATE[0];
      LgV2_B.Integrator1[1] = LgV2_X.Integrator1_CSTATE[1];
      LgV2_B.Integrator1[2] = LgV2_X.Integrator1_CSTATE[2];
      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* Sum: '<S51>/M_11' incorporates:
         *  Constant: '<S51>/X_udot'
         *  Constant: '<S51>/m'
         */
        LgV2_B.M_11 = LgV2_P.m_Value - LgV2_P.X_udot_Value;

        /* Sum: '<S51>/M_22' incorporates:
         *  Constant: '<S51>/Y_vdot'
         *  Constant: '<S51>/m'
         */
        LgV2_B.M_22 = LgV2_P.m_Value - LgV2_P.Y_vdot_Value;

        /* Product: '<S51>/m x_g' incorporates:
         *  Constant: '<S51>/m'
         *  Constant: '<S51>/x_g'
         */
        LgV2_B.mx_g = LgV2_P.m_Value * LgV2_P.x_g_Value;

        /* Sum: '<S51>/M_32' incorporates:
         *  Constant: '<S51>/N_vdot'
         */
        LgV2_B.M_32 = LgV2_B.mx_g - LgV2_P.N_vdot_Value;

        /* Sum: '<S51>/M_23' incorporates:
         *  Constant: '<S51>/Y_rdot'
         */
        LgV2_B.M_23 = LgV2_B.mx_g - LgV2_P.Y_rdot_Value;

        /* Sum: '<S51>/M_33' incorporates:
         *  Constant: '<S51>/I_z'
         *  Constant: '<S51>/N_rdot'
         */
        LgV2_B.M_33 = LgV2_P.I_z_Value - LgV2_P.N_rdot_Value;

        /* Reshape: '<S51>/M' incorporates:
         *  Constant: '<S51>/M_12'
         *  Constant: '<S51>/M_13'
         *  Constant: '<S51>/M_21'
         *  Constant: '<S51>/M_31'
         */
        LgV2_B.M[0] = LgV2_B.M_11;
        LgV2_B.M[1] = LgV2_P.M_21_Value;
        LgV2_B.M[2] = LgV2_P.M_31_Value;
        LgV2_B.M[3] = LgV2_P.M_12_Value;
        LgV2_B.M[4] = LgV2_B.M_22;
        LgV2_B.M[5] = LgV2_B.M_32;
        LgV2_B.M[6] = LgV2_P.M_13_Value;
        LgV2_B.M[7] = LgV2_B.M_23;
        LgV2_B.M[8] = LgV2_B.M_33;

        /* Product Block: '<S51>/Inverse' */
        {
          static const int_T dims[3] = { 3, 3, 3 };

          rt_MatDivRR_Dbl(LgV2_B.Inverse, LgV2_B.M,
                          &LgV2_DWork.Inverse_DWORK4[0], (real_T*)
                          &LgV2_DWork.K_e1_DWORK1[0],
                          &LgV2_DWork.K_e1_DWORK2[0], (real_T*)
                          &LgV2_DWork.K_e1_DWORK3[0],
                          &dims[0]);
        }
      }

      /* Product: '<S46>/Product1' */
      for (i = 0; i < 3; i++) {
        LgV2_B.Product1_h[i] = 0.0;
        LgV2_B.Product1_h[i] = LgV2_B.LinearDampningmatrix[i] *
          LgV2_B.Integrator[0] + LgV2_B.Product1_h[i];
        LgV2_B.Product1_h[i] = LgV2_B.LinearDampningmatrix[i + 3] *
          LgV2_B.Integrator[1] + LgV2_B.Product1_h[i];
        LgV2_B.Product1_h[i] = LgV2_B.LinearDampningmatrix[i + 6] *
          LgV2_B.Integrator[2] + LgV2_B.Product1_h[i];
      }

      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* Gain: '<S57>/-l_x1' incorporates:
         *  Constant: '<S57>/l_x1'
         */
        LgV2_B.l_x1_k = LgV2_P.l_x1_Gain_o * LgV2_P.l_x1_Value_f;

        /* Gain: '<S57>/-l_y2' incorporates:
         *  Constant: '<S57>/l_y2'
         */
        LgV2_B.l_y2_g = LgV2_P.l_y2_Gain_p * LgV2_P.l_y2_Value_j;

        /* Gain: '<S57>/-l_x2' incorporates:
         *  Constant: '<S57>/l_x2'
         */
        LgV2_B.l_x2_h = LgV2_P.l_x2_Gain_d * LgV2_P.l_x2_Value_p;

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
        LgV2_B.x5_m[0] = LgV2_P.T_e11_Value_c1;
        LgV2_B.x5_m[1] = LgV2_P.T_e21_Value_a;
        LgV2_B.x5_m[2] = LgV2_P.l_y1_Value_j;
        LgV2_B.x5_m[3] = LgV2_P.T_e12_Value_iv;
        LgV2_B.x5_m[4] = LgV2_P.T_e22_Value_on;
        LgV2_B.x5_m[5] = LgV2_B.l_x1_k;
        LgV2_B.x5_m[6] = LgV2_P.T_e13_Value_i;
        LgV2_B.x5_m[7] = LgV2_P.T_e23_Value_k;
        LgV2_B.x5_m[8] = LgV2_B.l_y2_g;
        LgV2_B.x5_m[9] = LgV2_P.T_e14_Value_g;
        LgV2_B.x5_m[10] = LgV2_P.T_e24_Value_b;
        LgV2_B.x5_m[11] = LgV2_B.l_x2_h;
        LgV2_B.x5_m[12] = LgV2_P.T_e15_Value_j;
        LgV2_B.x5_m[13] = LgV2_P.T_e25_Value_n;
        LgV2_B.x5_m[14] = LgV2_P.l_x3_Value_n;

        /* Gain: '<S55>/Gain K_e1_hil' incorporates:
         *  Constant: '<S55>/K_e1_hil'
         */
        LgV2_B.GainK_e1_hil = LgV2_P.GainK_e1_hil_Gain * LgV2_P.K_e1_hil_Value;

        /* Gain: '<S55>/Gain K_e2_hil' incorporates:
         *  Constant: '<S55>/K_e2_hil'
         */
        LgV2_B.GainK_e2_hil = LgV2_P.GainK_e2_hil_Gain * LgV2_P.K_e2_hil_Value;

        /* Gain: '<S55>/Gain K_e3_hil' incorporates:
         *  Constant: '<S55>/K_e3_hil'
         */
        LgV2_B.GainK_e3_hil = LgV2_P.GainK_e3_hil_Gain * LgV2_P.K_e3_hil_Value;

        /* Gain: '<S55>/Gain K_e4_hil' incorporates:
         *  Constant: '<S55>/K_e4_hil'
         */
        LgV2_B.GainK_e4_hil = LgV2_P.GainK_e4_hil_Gain * LgV2_P.K_e4_hil_Value;

        /* Gain: '<S55>/Gain K_e5_hil' incorporates:
         *  Constant: '<S55>/K_e5_hil'
         */
        LgV2_B.GainK_e5_hil = LgV2_P.GainK_e5_hil_Gain * LgV2_P.K_e5_hil_Value;

        /* Reshape: '<S55>/Thruster Gain matrix' incorporates:
         *  Constant: '<S55>/Constant41'
         */
        LgV2_B.ThrusterGainmatrix_m[0] = LgV2_B.GainK_e1_hil;
        LgV2_B.ThrusterGainmatrix_m[1] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[2] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[3] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[4] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[5] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[6] = LgV2_B.GainK_e2_hil;
        LgV2_B.ThrusterGainmatrix_m[7] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[8] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[9] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[10] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[11] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[12] = LgV2_B.GainK_e3_hil;
        LgV2_B.ThrusterGainmatrix_m[13] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[14] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[15] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[16] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[17] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[18] = LgV2_B.GainK_e4_hil;
        LgV2_B.ThrusterGainmatrix_m[19] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[20] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[21] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[22] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[23] = LgV2_P.Constant41_Value;
        LgV2_B.ThrusterGainmatrix_m[24] = LgV2_B.GainK_e5_hil;

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
        LgV2_B.sampletime = LgV2_P.sampletime_WtEt;

        /* UnitDelay: '<S56>/Delay Input2' */
        LgV2_B.Yk1 = LgV2_DWork.DelayInput2_DSTATE;
      }

      /* Fcn: '<S52>/R11' */
      LgV2_B.R11_i = cos(LgV2_B.Integrator1[2]);

      /* Fcn: '<S52>/R21' */
      LgV2_B.R21_l = sin(LgV2_B.Integrator1[2]);

      /* Fcn: '<S52>/R12' */
      LgV2_B.R12_g = -1.0 * sin(LgV2_B.Integrator1[2]);

      /* Fcn: '<S52>/R22' */
      LgV2_B.R22_i = cos(LgV2_B.Integrator1[2]);

      /* Reshape: '<S52>/R(psi)' incorporates:
       *  Constant: '<S52>/R13'
       *  Constant: '<S52>/R23'
       *  Constant: '<S52>/R31'
       *  Constant: '<S52>/R32'
       *  Constant: '<S52>/R33'
       */
      LgV2_B.Rpsi[0] = LgV2_B.R11_i;
      LgV2_B.Rpsi[1] = LgV2_B.R21_l;
      LgV2_B.Rpsi[2] = LgV2_P.R31_Value;
      LgV2_B.Rpsi[3] = LgV2_B.R12_g;
      LgV2_B.Rpsi[4] = LgV2_B.R22_i;
      LgV2_B.Rpsi[5] = LgV2_P.R32_Value;
      LgV2_B.Rpsi[6] = LgV2_P.R13_Value;
      LgV2_B.Rpsi[7] = LgV2_P.R23_Value;
      LgV2_B.Rpsi[8] = LgV2_P.R33_Value;

      /* Product: '<S46>/Product3' */
      for (i = 0; i < 3; i++) {
        LgV2_B.Product3[i] = 0.0;
        LgV2_B.Product3[i] = LgV2_B.Rpsi[i] * LgV2_B.Integrator[0] +
          LgV2_B.Product3[i];
        LgV2_B.Product3[i] = LgV2_B.Rpsi[i + 3] * LgV2_B.Integrator[1] +
          LgV2_B.Product3[i];
        LgV2_B.Product3[i] = LgV2_B.Rpsi[i + 6] * LgV2_B.Integrator[2] +
          LgV2_B.Product3[i];
      }

      /* Gain: '<S34>/eta_surge_hil' */
      LgV2_B.eta_surge_hil = LgV2_P.eta_surge_hil_Gain * LgV2_B.Integrator1[0];

      /* Gain: '<S34>/eta_sway_hil' */
      LgV2_B.eta_sway_hil = LgV2_P.eta_sway_hil_Gain * LgV2_B.Integrator1[1];

      /* Gain: '<S34>/eta_yaw_hil' */
      LgV2_B.eta_yaw_hil = LgV2_P.eta_yaw_hil_Gain * LgV2_B.Integrator1[2];

      /* Gain: '<S34>/etadot_surge_hil' */
      LgV2_B.etadot_surge_hil = LgV2_P.etadot_surge_hil_Gain * LgV2_B.Product3[0];

      /* Gain: '<S34>/etadot_sway_hil' */
      LgV2_B.etadot_sway_hil = LgV2_P.etadot_sway_hil_Gain * LgV2_B.Product3[1];

      /* Gain: '<S34>/etadot_yaw_hil' */
      LgV2_B.etadot_yaw_hil = LgV2_P.etadot_yaw_hil_Gain * LgV2_B.Product3[2];

      /* Gain: '<S34>/nu_surge_hil' */
      LgV2_B.nu_surge_hil = LgV2_P.nu_surge_hil_Gain * LgV2_B.Integrator[0];

      /* Gain: '<S34>/nu_sway_hil' */
      LgV2_B.nu_sway_hil = LgV2_P.nu_sway_hil_Gain * LgV2_B.Integrator[1];

      /* Gain: '<S34>/nu_yaw_hil' */
      LgV2_B.nu_yaw_hil = LgV2_P.nu_yaw_hil_Gain * LgV2_B.Integrator[2];
      if (rtmIsMajorTimeStep(LgV2_M)) {
      }
    }

    /* end of Outputs for SubSystem: '<S5>/Linear Simulator' */

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

    /* Gain: '<S31>/QTM In8' */
    LgV2_B.QTMIn8 = LgV2_P.QTMIn8_Gain * LgV2_B.QTMIn[7];

    /* Gain: '<S31>/d2r roll' */
    LgV2_B.d2rroll = LgV2_P.d2rroll_Gain * LgV2_B.QTMIn8;

    /* Gain: '<S31>/QTM In7' */
    LgV2_B.QTMIn7 = LgV2_P.QTMIn7_Gain * LgV2_B.QTMIn[6];

    /* Gain: '<S31>/d2r pitch' */
    LgV2_B.d2rpitch = LgV2_P.d2rpitch_Gain * LgV2_B.QTMIn7;

    /* Trigonometry: '<S32>/sin(theta)' */
    LgV2_B.sintheta[0] = sin(LgV2_B.d2rroll);
    LgV2_B.sintheta[1] = sin(LgV2_B.d2rpitch);
    LgV2_B.sintheta[2] = sin(LgV2_B.d2ryaw);

    /* Trigonometry: '<S32>/cos(theta)' */
    LgV2_B.costheta[0] = cos(LgV2_B.d2rroll);
    LgV2_B.costheta[1] = cos(LgV2_B.d2rpitch);
    LgV2_B.costheta[2] = cos(LgV2_B.d2ryaw);

    /* Fcn: '<S32>/R11' */
    LgV2_B.R11 = LgV2_B.costheta[1] * LgV2_B.costheta[2];

    /* Fcn: '<S32>/R21 ' */
    LgV2_B.R21 = LgV2_B.sintheta[0] * LgV2_B.sintheta[1] * LgV2_B.costheta[2] +
      (-LgV2_B.costheta[0]) * LgV2_B.sintheta[2];

    /* Fcn: '<S32>/R31 ' */
    LgV2_B.R31 = LgV2_B.costheta[0] * LgV2_B.sintheta[1] * LgV2_B.costheta[2] +
      LgV2_B.sintheta[0] * LgV2_B.sintheta[2];

    /* Fcn: '<S32>/R12' */
    LgV2_B.R12 = LgV2_B.costheta[1] * LgV2_B.sintheta[2];

    /* Fcn: '<S32>/R22' */
    LgV2_B.R22 = LgV2_B.sintheta[0] * LgV2_B.sintheta[1] * LgV2_B.sintheta[2] +
      LgV2_B.costheta[0] * LgV2_B.costheta[2];

    /* Fcn: '<S32>/R32' */
    LgV2_B.R32 = LgV2_B.costheta[0] * LgV2_B.sintheta[1] * LgV2_B.sintheta[2] +
      (-LgV2_B.sintheta[0]) * LgV2_B.costheta[2];

    /* Fcn: '<S32>/R13' */
    LgV2_B.R13 = -LgV2_B.sintheta[1];

    /* Fcn: '<S32>/R23' */
    LgV2_B.R23 = LgV2_B.sintheta[0] * LgV2_B.costheta[1];

    /* Fcn: '<S32>/R33' */
    LgV2_B.R33 = LgV2_B.costheta[0] * LgV2_B.costheta[1];

    /* Reshape: '<S32>/Reshape 9x1->3x3' */
    LgV2_B.Reshape9x13x3[0] = LgV2_B.R11;
    LgV2_B.Reshape9x13x3[1] = LgV2_B.R21;
    LgV2_B.Reshape9x13x3[2] = LgV2_B.R31;
    LgV2_B.Reshape9x13x3[3] = LgV2_B.R12;
    LgV2_B.Reshape9x13x3[4] = LgV2_B.R22;
    LgV2_B.Reshape9x13x3[5] = LgV2_B.R32;
    LgV2_B.Reshape9x13x3[6] = LgV2_B.R13;
    LgV2_B.Reshape9x13x3[7] = LgV2_B.R23;
    LgV2_B.Reshape9x13x3[8] = LgV2_B.R33;

    /* Concatenate: '<S31>/Matrix Concatenate' incorporates:
     *  Constant: '<S31>/Constant1'
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

    /* Concatenate: '<S31>/Matrix Concatenate1' incorporates:
     *  Constant: '<S31>/Constant1'
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

    /* Gain: '<S31>/QTM In5' */
    LgV2_B.QTMIn5 = LgV2_P.QTMIn5_Gain * LgV2_B.QTMIn[4];

    /* Gain: '<S31>/mm2m z' */
    LgV2_B.mm2mz = LgV2_P.mm2mz_Gain * LgV2_B.QTMIn5;

    /* Derivative Block: '<S31>/Derivative' */
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

    /* Product: '<S31>/Product' */
    for (i = 0; i < 6; i++) {
      LgV2_B.Product[i] = 0.0;
      for (tmp_4 = 0; tmp_4 < 6; tmp_4++) {
        LgV2_B.Product[i] = LgV2_B.MatrixConcatenate2[6 * tmp_4 + i] *
          LgV2_B.Derivative[tmp_4] + LgV2_B.Product[i];
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
      /* RelationalOperator: '<S10>/Compare' incorporates:
       *  Constant: '<S10>/Constant'
       *  Constant: '<S1>/Control Mode'
       */
      LgV2_B.Compare = (LgV2_P.ControlMode_Value == LgV2_P.Constant_Value_j);
    }

    /* Outputs for enable SubSystem: '<S1>/DP control' incorporates:
     *  EnablePort: '<S7>/Enable'
     */
    if (rtmIsMajorTimeStep(LgV2_M) && rtmIsMajorTimeStep(LgV2_M)) {
      if (LgV2_B.Compare > 0) {
        if (LgV2_DWork.DPcontrol_MODE == SUBSYS_DISABLED) {
          /* InitializeConditions for Integrator: '<S13>/Integrator1' */
          LgV2_X.Integrator1_CSTATE_m[0] = LgV2_P.Integrator1_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator' */
          LgV2_X.Integrator_CSTATE_h[0] = LgV2_P.Integrator_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator1' */
          LgV2_X.Integrator1_CSTATE_m[1] = LgV2_P.Integrator1_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator' */
          LgV2_X.Integrator_CSTATE_h[1] = LgV2_P.Integrator_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator1' */
          LgV2_X.Integrator1_CSTATE_m[2] = LgV2_P.Integrator1_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator' */
          LgV2_X.Integrator_CSTATE_h[2] = LgV2_P.Integrator_IC;

          /* Integrator Block: '<S11>/Integrator' */
          LgV2_X.Integrator_CSTATE_k[0] = LgV2_P.Integrator_IC_f;
          LgV2_X.Integrator_CSTATE_k[1] = LgV2_P.Integrator_IC_f;
          LgV2_X.Integrator_CSTATE_k[2] = LgV2_P.Integrator_IC_f;

          /* InitializeConditions for Integrator: '<S13>/Integrator4' */
          LgV2_X.Integrator4_CSTATE[0] = LgV2_P.Integrator4_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator2' */
          LgV2_X.Integrator2_CSTATE[0] = LgV2_P.Integrator2_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator3' */
          LgV2_X.Integrator3_CSTATE[0] = LgV2_P.Integrator3_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator4' */
          LgV2_X.Integrator4_CSTATE[1] = LgV2_P.Integrator4_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator2' */
          LgV2_X.Integrator2_CSTATE[1] = LgV2_P.Integrator2_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator3' */
          LgV2_X.Integrator3_CSTATE[1] = LgV2_P.Integrator3_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator4' */
          LgV2_X.Integrator4_CSTATE[2] = LgV2_P.Integrator4_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator2' */
          LgV2_X.Integrator2_CSTATE[2] = LgV2_P.Integrator2_IC;

          /* InitializeConditions for Integrator: '<S13>/Integrator3' */
          LgV2_X.Integrator3_CSTATE[2] = LgV2_P.Integrator3_IC;
          LgV2_DWork.DPcontrol_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (LgV2_DWork.DPcontrol_MODE == SUBSYS_ENABLED) {
          LgV2_DWork.DPcontrol_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (LgV2_DWork.DPcontrol_MODE == SUBSYS_ENABLED) {
      /* Integrator: '<S13>/Integrator1' */
      LgV2_B.eta_w[0] = LgV2_X.Integrator1_CSTATE_m[0];
      LgV2_B.eta_w[1] = LgV2_X.Integrator1_CSTATE_m[1];
      LgV2_B.eta_w[2] = LgV2_X.Integrator1_CSTATE_m[2];
      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* ToFile Block: '<S7>/To File'
         */
        if (rtmIsMajorTimeStep(LgV2_M)) {
          if (!(++LgV2_DWork.ToFile_IWORK_h.Decimation % 1) &&
              (LgV2_DWork.ToFile_IWORK_h.Count*4)+1 < 100000000 ) {
            real_T u[4];
            FILE *fp = (FILE *) LgV2_DWork.ToFile_PWORK_b.FilePtr;
            if (fp != (NULL)) {
              LgV2_DWork.ToFile_IWORK_h.Decimation = 0;
              u[0] = LgV2_M->Timing.t[1];
              u[1] = LgV2_B.eta_w[0];
              u[2] = LgV2_B.eta_w[1];
              u[3] = LgV2_B.eta_w[2];
              if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
                rtmSetErrorStatus(LgV2_M,
                                  "Error writing to MAT-file CSE1_data_eta_w.mat");
                return;
              }

              if (((++LgV2_DWork.ToFile_IWORK_h.Count)*4)+1 >= 100000000) {
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
        LgV2_B.BT_power_limit = LgV2_P.BT_power_limit_Value;
      }

      /* Integrator: '<S13>/Integrator' */
      LgV2_B.eta[0] = LgV2_X.Integrator_CSTATE_h[0];
      LgV2_B.eta[1] = LgV2_X.Integrator_CSTATE_h[1];
      LgV2_B.eta[2] = LgV2_X.Integrator_CSTATE_h[2];

      /* Saturate: '<S21>/Saturation' */
      tmp = LgV2_B.eta[2];
      LgV2_B.Saturation_j = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_b,
        LgV2_P.Saturation_UpperSat_d);

      /* Signum: '<S21>/Sign' */
      LgV2_B.Sign_l = rt_SIGNd_snf(LgV2_B.Saturation_j);

      /* Gain: '<S21>/Gain' */
      LgV2_B.Gain_d = LgV2_P.Gain_Gain * LgV2_B.Sign_l;

      /* Sum: '<S21>/Sum1' */
      LgV2_B.Sum1_e = LgV2_B.Saturation_j + LgV2_B.Gain_d;

      /* Math: '<S21>/Math Function' incorporates:
       *  Constant: '<S21>/Constant'
       */
      LgV2_B.MathFunction = rt_rem_snf(LgV2_B.Sum1_e, LgV2_P.Constant_Value_jr);

      /* Sum: '<S21>/Sum' */
      LgV2_B.Sum_n = LgV2_B.MathFunction - LgV2_B.Gain_d;

      /* MultiPortSwitch: '<S7>/Multiport Switch' incorporates:
       *  Constant: '<S7>/Enable Filter'
       */
      if ((int32_T)LgV2_P.EnableFilter_Value == 0) {
        LgV2_B.MultiportSwitch_p[0] = LgV2_B.eta_surge;
        LgV2_B.MultiportSwitch_p[1] = LgV2_B.eta_sway;
        LgV2_B.MultiportSwitch_p[2] = LgV2_B.eta_yaw;
      } else {
        LgV2_B.MultiportSwitch_p[0] = LgV2_B.eta[0];
        LgV2_B.MultiportSwitch_p[1] = LgV2_B.eta[1];
        LgV2_B.MultiportSwitch_p[2] = LgV2_B.Sum_n;
      }

      /* Gain: '<S11>/eta N' */
      LgV2_B.etaN = LgV2_P.etaN_Gain * LgV2_B.MultiportSwitch_p[0];

      /* Gain: '<S11>/eta E' */
      LgV2_B.etaE = LgV2_P.etaE_Gain * LgV2_B.MultiportSwitch_p[1];

      /* Gain: '<S11>/eta Psi' */
      LgV2_B.etaPsi = LgV2_P.etaPsi_Gain * LgV2_B.MultiportSwitch_p[2];

      /* Sum: '<S11>/Sum2' */
      LgV2_B.regulationerror[0] = LgV2_B.eta_dDPN - LgV2_B.etaN;
      LgV2_B.regulationerror[1] = LgV2_B.eta_dDPE - LgV2_B.etaE;
      LgV2_B.regulationerror[2] = LgV2_B.eta_dDPPsi - LgV2_B.etaPsi;

      /* Gain: '<S11>/Reg_e_N_hil' */
      LgV2_B.Reg_e_N_hil = LgV2_P.Reg_e_N_hil_Gain * LgV2_B.regulationerror[0];

      /* Gain: '<S11>/Reg_e_E_hil' */
      LgV2_B.Reg_e_E_hil = LgV2_P.Reg_e_E_hil_Gain * LgV2_B.regulationerror[1];

      /* Gain: '<S11>/Reg_e_Psi_hil' */
      LgV2_B.Reg_e_Psi_hil = LgV2_P.Reg_e_Psi_hil_Gain * LgV2_B.regulationerror
        [2];
      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* SignalConversion: '<S11>/TmpHiddenBufferAtTo FileInport1' */
        LgV2_B.TmpHiddenBufferAtToFileInport_g[0] = LgV2_B.Reg_e_N_hil;
        LgV2_B.TmpHiddenBufferAtToFileInport_g[1] = LgV2_B.Reg_e_E_hil;
        LgV2_B.TmpHiddenBufferAtToFileInport_g[2] = LgV2_B.Reg_e_Psi_hil;

        /* ToFile Block: '<S11>/To File'
         */
        if (rtmIsMajorTimeStep(LgV2_M)) {
          if (!(++LgV2_DWork.ToFile_IWORK_k.Decimation % 1) &&
              (LgV2_DWork.ToFile_IWORK_k.Count*4)+1 < 100000000 ) {
            real_T u[4];
            FILE *fp = (FILE *) LgV2_DWork.ToFile_PWORK_e.FilePtr;
            if (fp != (NULL)) {
              LgV2_DWork.ToFile_IWORK_k.Decimation = 0;
              u[0] = LgV2_M->Timing.t[1];
              u[1] = LgV2_B.TmpHiddenBufferAtToFileInport_g[0];
              u[2] = LgV2_B.TmpHiddenBufferAtToFileInport_g[1];
              u[3] = LgV2_B.TmpHiddenBufferAtToFileInport_g[2];
              if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
                rtmSetErrorStatus(LgV2_M,
                                  "Error writing to MAT-file CSE1_data_reg_error.mat");
                return;
              }

              if (((++LgV2_DWork.ToFile_IWORK_k.Count)*4)+1 >= 100000000) {
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
      if (rtmIsMajorTimeStep(LgV2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &LgV2_PrevZCSigState.Integrator_Reset_ZCE_f,
                           LgV2_P.Reset_DP_integrator_Value);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || LgV2_P.Reset_DP_integrator_Value != 0.0) {
          LgV2_X.Integrator_CSTATE_k[0] = LgV2_P.Integrator_IC_f;
          LgV2_X.Integrator_CSTATE_k[1] = LgV2_P.Integrator_IC_f;
          LgV2_X.Integrator_CSTATE_k[2] = LgV2_P.Integrator_IC_f;
        }
      }

      LgV2_B.Integrator_g[0] = LgV2_X.Integrator_CSTATE_k[0];
      LgV2_B.Integrator_g[1] = LgV2_X.Integrator_CSTATE_k[1];
      LgV2_B.Integrator_g[2] = LgV2_X.Integrator_CSTATE_k[2];

      /* Integrator: '<S13>/Integrator4' */
      LgV2_B.nu[0] = LgV2_X.Integrator4_CSTATE[0];
      LgV2_B.nu[1] = LgV2_X.Integrator4_CSTATE[1];
      LgV2_B.nu[2] = LgV2_X.Integrator4_CSTATE[2];

      /* MultiPortSwitch: '<S7>/Multiport Switch1' incorporates:
       *  Constant: '<S7>/Enable Filter'
       */
      if ((int32_T)LgV2_P.EnableFilter_Value == 0) {
        LgV2_B.MultiportSwitch1[0] = LgV2_B.nu_surge;
        LgV2_B.MultiportSwitch1[1] = LgV2_B.nu_sway;
        LgV2_B.MultiportSwitch1[2] = LgV2_B.nu_yaw;
      } else {
        LgV2_B.MultiportSwitch1[0] = LgV2_B.nu[0];
        LgV2_B.MultiportSwitch1[1] = LgV2_B.nu[1];
        LgV2_B.MultiportSwitch1[2] = LgV2_B.nu[2];
      }

      /* Gain: '<S11>/K_d 1' */
      for (i = 0; i < 3; i++) {
        /* Gain: '<S11>/Kd' */
        LgV2_B.Kd[i] = 0.0;
        LgV2_B.Kd[i] = LgV2_P.Kd_Gain[i] * LgV2_B.MultiportSwitch1[0] +
          LgV2_B.Kd[i];
        LgV2_B.Kd[i] = LgV2_P.Kd_Gain[i + 3] * LgV2_B.MultiportSwitch1[1] +
          LgV2_B.Kd[i];
        LgV2_B.Kd[i] = LgV2_P.Kd_Gain[i + 6] * LgV2_B.MultiportSwitch1[2] +
          LgV2_B.Kd[i];

        /* Product: '<S11>/Product' incorporates:
         *  Constant: '<S11>/Kd_scale'
         */
        LgV2_B.Product_d[i] = LgV2_B.Kd[i] * LgV2_P.Kd_scale_Value;

        /* Gain: '<S11>/Ki' */
        LgV2_B.Ki[i] = 0.0;
        LgV2_B.Ki[i] = LgV2_P.Ki_Gain[i] * LgV2_B.Integrator_g[0] + LgV2_B.Ki[i];
        LgV2_B.Ki[i] = LgV2_P.Ki_Gain[i + 3] * LgV2_B.Integrator_g[1] +
          LgV2_B.Ki[i];
        LgV2_B.Ki[i] = LgV2_P.Ki_Gain[i + 6] * LgV2_B.Integrator_g[2] +
          LgV2_B.Ki[i];

        /* Product: '<S11>/Product1' incorporates:
         *  Constant: '<S11>/Ki_scale'
         */
        LgV2_B.Product1_c[i] = LgV2_B.Ki[i] * LgV2_P.Ki_scale_Value;
      }

      LgV2_B.K_d1 = LgV2_P.K_d1_Gain * LgV2_B.Product_d[0];

      /* Gain: '<S11>/K_d 2' */
      LgV2_B.K_d2 = LgV2_P.K_d2_Gain * LgV2_B.Product_d[1];

      /* Gain: '<S11>/K_d 3' */
      LgV2_B.K_d3 = LgV2_P.K_d3_Gain * LgV2_B.Product_d[2];

      /* Gain: '<S11>/K_d 3 deg' */
      LgV2_B.K_d3deg = LgV2_P.K_d3deg_Gain * LgV2_B.Product_d[2];

      /* Gain: '<S11>/K_i 1' */
      LgV2_B.K_i1 = LgV2_P.K_i1_Gain * LgV2_B.Product1_c[0];

      /* Gain: '<S11>/K_i 2' */
      LgV2_B.K_i2 = LgV2_P.K_i2_Gain * LgV2_B.Product1_c[1];

      /* Gain: '<S11>/K_i 3' */
      LgV2_B.K_i3 = LgV2_P.K_i3_Gain * LgV2_B.Product1_c[2];

      /* Gain: '<S11>/K_i 3 deg' */
      LgV2_B.K_i3deg = LgV2_P.K_i3deg_Gain * LgV2_B.Product1_c[2];

      /* Fcn: '<S11>/yaw angle' */
      LgV2_B.psi = LgV2_B.MultiportSwitch_p[2];

      /* Saturate: '<S17>/Saturation' */
      tmp = LgV2_B.psi;
      LgV2_B.Saturation_h = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_j,
        LgV2_P.Saturation_UpperSat_j);

      /* Signum: '<S17>/Sign' */
      LgV2_B.Sign_a = rt_SIGNd_snf(LgV2_B.Saturation_h);

      /* Gain: '<S17>/Gain' */
      LgV2_B.Gain_j = LgV2_P.Gain_Gain_h * LgV2_B.Sign_a;

      /* Sum: '<S17>/Sum1' */
      LgV2_B.Sum1_i = LgV2_B.Saturation_h + LgV2_B.Gain_j;

      /* Math: '<S17>/Math Function' incorporates:
       *  Constant: '<S17>/Constant'
       */
      LgV2_B.MathFunction_i = rt_rem_snf(LgV2_B.Sum1_i, LgV2_P.Constant_Value_g);

      /* Sum: '<S17>/Sum' */
      LgV2_B.Sum_b = LgV2_B.MathFunction_i - LgV2_B.Gain_j;

      /* Saturate: '<S16>/Saturation' */
      tmp = LgV2_B.Reg_e_Psi_hil;
      LgV2_B.Saturation_m = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_m,
        LgV2_P.Saturation_UpperSat_g);

      /* Signum: '<S16>/Sign' */
      LgV2_B.Sign_j = rt_SIGNd_snf(LgV2_B.Saturation_m);

      /* Gain: '<S16>/Gain' */
      LgV2_B.Gain_a = LgV2_P.Gain_Gain_f * LgV2_B.Sign_j;

      /* Sum: '<S16>/Sum1' */
      LgV2_B.Sum1_p = LgV2_B.Saturation_m + LgV2_B.Gain_a;

      /* Math: '<S16>/Math Function' incorporates:
       *  Constant: '<S16>/Constant'
       */
      LgV2_B.MathFunction_d = rt_rem_snf(LgV2_B.Sum1_p, LgV2_P.Constant_Value_gt);

      /* Sum: '<S16>/Sum' */
      LgV2_B.Sum_j = LgV2_B.MathFunction_d - LgV2_B.Gain_a;

      /* Fcn: '<S15>/Row1' */
      LgV2_B.Row1 = cos(LgV2_B.Sum_b) * LgV2_B.Reg_e_N_hil + sin(LgV2_B.Sum_b) *
        LgV2_B.Reg_e_E_hil;

      /* Fcn: '<S15>/Row2' */
      LgV2_B.Row2 = (-sin(LgV2_B.Sum_b)) * LgV2_B.Reg_e_N_hil + cos(LgV2_B.Sum_b)
        * LgV2_B.Reg_e_E_hil;

      /* Fcn: '<S15>/Row3' */
      LgV2_B.Row3 = LgV2_B.Sum_j;

      /* SignalConversion: '<S11>/TmpHiddenBufferAtKpInport1' */
      LgV2_B.TmpHiddenBufferAtKpInport1[0] = LgV2_B.Row1;
      LgV2_B.TmpHiddenBufferAtKpInport1[1] = LgV2_B.Row2;
      LgV2_B.TmpHiddenBufferAtKpInport1[2] = LgV2_B.Row3;
      for (i = 0; i < 3; i++) {
        /* Gain: '<S11>/Kp' */
        LgV2_B.Kp[i] = 0.0;
        LgV2_B.Kp[i] = LgV2_P.Kp_Gain[i] * LgV2_B.TmpHiddenBufferAtKpInport1[0]
          + LgV2_B.Kp[i];
        LgV2_B.Kp[i] = LgV2_P.Kp_Gain[i + 3] *
          LgV2_B.TmpHiddenBufferAtKpInport1[1] + LgV2_B.Kp[i];
        LgV2_B.Kp[i] = LgV2_P.Kp_Gain[i + 6] *
          LgV2_B.TmpHiddenBufferAtKpInport1[2] + LgV2_B.Kp[i];

        /* Product: '<S11>/Product2' incorporates:
         *  Constant: '<S11>/Kp_scale'
         */
        LgV2_B.Product2_m[i] = LgV2_P.Kp_scale_Value * LgV2_B.Kp[i];
      }

      /* Gain: '<S11>/K_p 1' */
      LgV2_B.K_p1 = LgV2_P.K_p1_Gain * LgV2_B.Product2_m[0];

      /* Gain: '<S11>/K_p 2' */
      LgV2_B.K_p2 = LgV2_P.K_p2_Gain * LgV2_B.Product2_m[1];

      /* Gain: '<S11>/K_p 3' */
      LgV2_B.K_p3 = LgV2_P.K_p3_Gain * LgV2_B.Product2_m[2];

      /* Gain: '<S11>/K_p 3 deg' */
      LgV2_B.K_p3deg = LgV2_P.K_p3deg_Gain * LgV2_B.Product2_m[2];

      /* Gain: '<S11>/Reg_e_Psi_deg' */
      LgV2_B.Reg_e_Psi_deg = LgV2_P.Reg_e_Psi_deg_Gain * LgV2_B.regulationerror
        [2];

      /* Sum: '<S11>/Sum3' */
      LgV2_B.Sum3[0] = LgV2_B.K_p1 + LgV2_B.K_i1;
      LgV2_B.Sum3[1] = LgV2_B.K_p2 + LgV2_B.K_i2;
      LgV2_B.Sum3[2] = LgV2_B.K_p3 + LgV2_B.K_i3;

      /* Sum: '<S11>/Sum1' */
      LgV2_B.Sum1_j[0] = LgV2_B.Sum3[0] - LgV2_B.K_d1;
      LgV2_B.Sum1_j[1] = LgV2_B.Sum3[1] - LgV2_B.K_d2;
      LgV2_B.Sum1_j[2] = LgV2_B.Sum3[2] - LgV2_B.K_d3;

      /* Gain: '<S11>/eta Psi deg' */
      LgV2_B.etaPsideg = LgV2_P.etaPsideg_Gain * LgV2_B.MultiportSwitch_p[2];

      /* Gain: '<S7>/DP tau_surge' */
      LgV2_B.DPtau_surge = LgV2_P.DPtau_surge_Gain * LgV2_B.Sum1_j[0];

      /* Gain: '<S7>/DP tau_sway' */
      LgV2_B.DPtau_sway = LgV2_P.DPtau_sway_Gain * LgV2_B.Sum1_j[1];

      /* Gain: '<S7>/DP tau_yaw' */
      LgV2_B.DPtau_yaw = LgV2_P.DPtau_yaw_Gain * LgV2_B.Sum1_j[2];
      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* Gain: '<S12>/Gain K_e1_DP' incorporates:
         *  Constant: '<S12>/K_e1_DP'
         */
        LgV2_B.GainK_e1_DP = LgV2_P.GainK_e1_DP_Gain * LgV2_P.K_e1_DP_Value;

        /* Gain: '<S12>/Gain K_e2_DP' incorporates:
         *  Constant: '<S12>/K_e2_DP'
         */
        LgV2_B.GainK_e2_DP = LgV2_P.GainK_e2_DP_Gain * LgV2_P.K_e2_DP_Value;

        /* Gain: '<S12>/Gain K_e3_DP' incorporates:
         *  Constant: '<S12>/K_e3_DP'
         */
        LgV2_B.GainK_e3_DP = LgV2_P.GainK_e3_DP_Gain * LgV2_P.K_e3_DP_Value;

        /* Gain: '<S12>/Gain K_e4_DP' incorporates:
         *  Constant: '<S12>/K_e4_DP'
         */
        LgV2_B.GainK_e4_DP = LgV2_P.GainK_e4_DP_Gain * LgV2_P.K_e4_DP_Value;

        /* Gain: '<S12>/Gain K_e5_DP' incorporates:
         *  Constant: '<S12>/K_e5_DP'
         */
        LgV2_B.GainK_e5_DP = LgV2_P.GainK_e5_DP_Gain * LgV2_P.K_e5_DP_Value;

        /* Reshape: '<S12>/Thruster Gain matrix' incorporates:
         *  Constant: '<S12>/Constant'
         */
        LgV2_B.ThrusterGainmatrix_o[0] = LgV2_B.GainK_e1_DP;
        LgV2_B.ThrusterGainmatrix_o[1] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[2] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[3] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[4] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[5] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[6] = LgV2_B.GainK_e2_DP;
        LgV2_B.ThrusterGainmatrix_o[7] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[8] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[9] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[10] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[11] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[12] = LgV2_B.GainK_e3_DP;
        LgV2_B.ThrusterGainmatrix_o[13] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[14] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[15] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[16] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[17] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[18] = LgV2_B.GainK_e4_DP;
        LgV2_B.ThrusterGainmatrix_o[19] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[20] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[21] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[22] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[23] = LgV2_P.Constant_Value_c;
        LgV2_B.ThrusterGainmatrix_o[24] = LgV2_B.GainK_e5_DP;

        /* Product Block: '<S7>/K_e^-1' */
        {
          static const int_T dims[3] = { 5, 5, 5 };

          rt_MatDivRR_Dbl(LgV2_B.K_e1_g, LgV2_B.ThrusterGainmatrix_o,
                          &LgV2_DWork.K_e1_DWORK4_d[0], (real_T*)
                          &LgV2_DWork.K_e1_DWORK1[0],
                          &LgV2_DWork.K_e1_DWORK2[0], (real_T*)
                          &LgV2_DWork.K_e1_DWORK3[0],
                          &dims[0]);
        }

        /* Gain: '<S14>/-l_x1' incorporates:
         *  Constant: '<S14>/l_x1'
         */
        LgV2_B.l_x1_m = LgV2_P.l_x1_Gain_j * LgV2_P.l_x1_Value_e;

        /* Gain: '<S14>/-l_y2' incorporates:
         *  Constant: '<S14>/l_y2'
         */
        LgV2_B.l_y2_f = LgV2_P.l_y2_Gain_l * LgV2_P.l_y2_Value_e;

        /* Gain: '<S14>/-l_x2' incorporates:
         *  Constant: '<S14>/l_x2'
         */
        LgV2_B.l_x2_k = LgV2_P.l_x2_Gain_b * LgV2_P.l_x2_Value_d;

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
        LgV2_B.x5_j[0] = LgV2_P.T_e11_Value_o;
        LgV2_B.x5_j[1] = LgV2_P.T_e21_Value_d;
        LgV2_B.x5_j[2] = LgV2_P.l_y1_Value_p;
        LgV2_B.x5_j[3] = LgV2_P.T_e12_Value_i;
        LgV2_B.x5_j[4] = LgV2_P.T_e22_Value_o;
        LgV2_B.x5_j[5] = LgV2_B.l_x1_m;
        LgV2_B.x5_j[6] = LgV2_P.T_e13_Value_g;
        LgV2_B.x5_j[7] = LgV2_P.T_e23_Value_o;
        LgV2_B.x5_j[8] = LgV2_B.l_y2_f;
        LgV2_B.x5_j[9] = LgV2_P.T_e14_Value_e;
        LgV2_B.x5_j[10] = LgV2_P.T_e24_Value_c;
        LgV2_B.x5_j[11] = LgV2_B.l_x2_k;
        LgV2_B.x5_j[12] = LgV2_P.T_e15_Value_h;
        LgV2_B.x5_j[13] = LgV2_P.T_e25_Value_c;
        LgV2_B.x5_j[14] = LgV2_P.l_x3_Value_d;

        /* S-Function (sdsppinv): '<S7>/T_e^+' */
        /* Copy input to temporary space */
        memcpy((void *)(&LgV2_DWork.K_e1_DWORK1[0]), (void *)(&LgV2_B.x5_j[0]),
               15U * sizeof(real_T));

        /* Call SVD */
        i = MWDSP_SVD_D(&LgV2_DWork.K_e1_DWORK1[0], 3, 5, &LgV2_DWork.T_e_S[0],
                        &LgV2_DWork.K_e1_DWORK3[0], &LgV2_DWork.T_e_WORK[0],
                        &LgV2_DWork.T_e_U[0], &LgV2_DWork.T_e_V[0], 1);

        /* Only call 'pinv' function if SVD succeeded */
        if (i == 0) {
          MWDSPCG_Pseudoinverse_D(&LgV2_DWork.T_e_S[0], &LgV2_DWork.T_e_U[0],
            &LgV2_DWork.T_e_V[0], &LgV2_B.T_e_d[0], (const int32_T)3, (const
            int32_T)5);
        }

        /* Product: '<S7>/Product' */
        for (i = 0; i < 5; i++) {
          for (tmp_4 = 0; tmp_4 < 3; tmp_4++) {
            LgV2_B.Product_c[i + 5 * tmp_4] = 0.0;
            for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
              LgV2_B.Product_c[i + 5 * tmp_4] = LgV2_B.K_e1_g[5 * tmp_3 + i] *
                LgV2_B.T_e_d[5 * tmp_4 + tmp_3] + LgV2_B.Product_c[5 * tmp_4 + i];
            }
          }
        }
      }

      /* SignalConversion: '<S7>/TmpHiddenBufferAtProduct1Inport2' */
      LgV2_B.TmpHiddenBufferAtProduct1Inpo_e[0] = LgV2_B.DPtau_surge;
      LgV2_B.TmpHiddenBufferAtProduct1Inpo_e[1] = LgV2_B.DPtau_sway;
      LgV2_B.TmpHiddenBufferAtProduct1Inpo_e[2] = LgV2_B.DPtau_yaw;

      /* Product: '<S7>/Product1' */
      for (i = 0; i < 5; i++) {
        LgV2_B.Product1_i[i] = 0.0;
        LgV2_B.Product1_i[i] = LgV2_B.Product_c[i] *
          LgV2_B.TmpHiddenBufferAtProduct1Inpo_e[0] + LgV2_B.Product1_i[i];
        LgV2_B.Product1_i[i] = LgV2_B.Product_c[i + 5] *
          LgV2_B.TmpHiddenBufferAtProduct1Inpo_e[1] + LgV2_B.Product1_i[i];
        LgV2_B.Product1_i[i] = LgV2_B.Product_c[i + 10] *
          LgV2_B.TmpHiddenBufferAtProduct1Inpo_e[2] + LgV2_B.Product1_i[i];
      }

      /* Gain: '<S7>/DP u_1' */
      LgV2_B.DPu_1 = LgV2_P.DPu_1_Gain * LgV2_B.Product1_i[0];

      /* Gain: '<S7>/DP u_2' */
      LgV2_B.DPu_2 = LgV2_P.DPu_2_Gain * LgV2_B.Product1_i[1];

      /* Gain: '<S7>/DP u_3' */
      LgV2_B.DPu_3 = LgV2_P.DPu_3_Gain * LgV2_B.Product1_i[2];

      /* Gain: '<S7>/DP u_4' */
      LgV2_B.DPu_4 = LgV2_P.DPu_4_Gain * LgV2_B.Product1_i[3];

      /* Gain: '<S7>/DP u_5' */
      LgV2_B.DPu_5 = LgV2_P.DPu_5_Gain * LgV2_B.Product1_i[4];
      for (i = 0; i < 3; i++) {
        /* Gain: '<S13>/Gain1' */
        LgV2_B.Gain1_g[i] = 0.0;
        LgV2_B.Gain1_g[i] = LgV2_P.Gain1_Gain_b[i] * LgV2_B.eta_w[0] +
          LgV2_B.Gain1_g[i];
        LgV2_B.Gain1_g[i] = LgV2_P.Gain1_Gain_b[i + 3] * LgV2_B.eta_w[1] +
          LgV2_B.Gain1_g[i];
        LgV2_B.Gain1_g[i] = LgV2_P.Gain1_Gain_b[i + 6] * LgV2_B.eta_w[2] +
          LgV2_B.Gain1_g[i];

        /* Integrator: '<S13>/Integrator2' */
        LgV2_B.xi_w[i] = LgV2_X.Integrator2_CSTATE[i];
      }

      /* Sum: '<S13>/Sum4' */
      LgV2_B.Sum4[0] = LgV2_B.eta_w[0] + LgV2_B.eta[0];
      LgV2_B.Sum4[1] = LgV2_B.eta_w[1] + LgV2_B.eta[1];
      LgV2_B.Sum4[2] = LgV2_B.eta_w[2] + LgV2_B.Sum_n;

      /* Sum: '<S13>/Sum2' */
      LgV2_B.Sum2_d[0] = LgV2_B.eta_surge - LgV2_B.Sum4[0];
      LgV2_B.Sum2_d[1] = LgV2_B.eta_sway - LgV2_B.Sum4[1];
      LgV2_B.Sum2_d[2] = LgV2_B.eta_yaw - LgV2_B.Sum4[2];

      /* Saturate: '<S22>/Saturation' */
      tmp = LgV2_B.Sum2_d[2];
      LgV2_B.Saturation_ho = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_c,
        LgV2_P.Saturation_UpperSat_n);

      /* Signum: '<S22>/Sign' */
      LgV2_B.Sign_jh = rt_SIGNd_snf(LgV2_B.Saturation_ho);

      /* Gain: '<S22>/Gain' */
      LgV2_B.Gain_it = LgV2_P.Gain_Gain_e * LgV2_B.Sign_jh;

      /* Sum: '<S22>/Sum1' */
      LgV2_B.Sum1_pt = LgV2_B.Saturation_ho + LgV2_B.Gain_it;

      /* Math: '<S22>/Math Function' incorporates:
       *  Constant: '<S22>/Constant'
       */
      LgV2_B.MathFunction_c = rt_rem_snf(LgV2_B.Sum1_pt, LgV2_P.Constant_Value_a);

      /* Sum: '<S22>/Sum' */
      LgV2_B.Sum_hw = LgV2_B.MathFunction_c - LgV2_B.Gain_it;

      /* SignalConversion: '<S13>/TmpHiddenBufferAtK11Inport1' */
      LgV2_B.TmpHiddenBufferAtK11Inport1[0] = LgV2_B.Sum2_d[0];
      LgV2_B.TmpHiddenBufferAtK11Inport1[1] = LgV2_B.Sum2_d[1];
      LgV2_B.TmpHiddenBufferAtK11Inport1[2] = LgV2_B.Sum_hw;

      /* Fcn: '<S19>/Row1' */
      for (i = 0; i < 3; i++) {
        /* Gain: '<S13>/Gain2' */
        LgV2_B.Gain2[i] = 0.0;
        LgV2_B.Gain2[i] = LgV2_P.Gain2_Gain[i] * LgV2_B.xi_w[0] + LgV2_B.Gain2[i];
        LgV2_B.Gain2[i] = LgV2_P.Gain2_Gain[i + 3] * LgV2_B.xi_w[1] +
          LgV2_B.Gain2[i];
        LgV2_B.Gain2[i] = LgV2_P.Gain2_Gain[i + 6] * LgV2_B.xi_w[2] +
          LgV2_B.Gain2[i];

        /* Gain: '<S13>/K4' */
        LgV2_B.K4[i] = 0.0;
        LgV2_B.K4[i] = LgV2_P.K4_Gain[i] * LgV2_B.TmpHiddenBufferAtK11Inport1[0]
          + LgV2_B.K4[i];
        LgV2_B.K4[i] = LgV2_P.K4_Gain[i + 3] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[1] + LgV2_B.K4[i];
        LgV2_B.K4[i] = LgV2_P.K4_Gain[i + 6] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[2] + LgV2_B.K4[i];

        /* Integrator: '<S13>/Integrator3' */
        LgV2_B.bias[i] = LgV2_X.Integrator3_CSTATE[i];

        /* Gain: '<S13>/Gain6' */
        LgV2_B.Gain6[i] = 0.0;
        LgV2_B.Gain6[i] = LgV2_P.Gain6_Gain[i] * LgV2_B.nu[0] + LgV2_B.Gain6[i];
        LgV2_B.Gain6[i] = LgV2_P.Gain6_Gain[i + 3] * LgV2_B.nu[1] +
          LgV2_B.Gain6[i];
        LgV2_B.Gain6[i] = LgV2_P.Gain6_Gain[i + 6] * LgV2_B.nu[2] +
          LgV2_B.Gain6[i];
      }

      LgV2_B.Row1_b = cos(LgV2_B.eta_yaw) * LgV2_B.K4[0] + sin(LgV2_B.eta_yaw) *
        LgV2_B.K4[1];

      /* Fcn: '<S19>/Row2' */
      LgV2_B.Row2_d = (-sin(LgV2_B.eta_yaw)) * LgV2_B.K4[0] + cos(LgV2_B.eta_yaw)
        * LgV2_B.K4[1];

      /* Fcn: '<S19>/Row3' */
      LgV2_B.Row3_h = LgV2_B.K4[2];

      /* Fcn: '<S20>/Row1' */
      LgV2_B.Row1_g = cos(LgV2_B.eta_yaw) * LgV2_B.bias[0] + sin(LgV2_B.eta_yaw)
        * LgV2_B.bias[1];

      /* Fcn: '<S20>/Row2' */
      LgV2_B.Row2_b = (-sin(LgV2_B.eta_yaw)) * LgV2_B.bias[0] + cos
        (LgV2_B.eta_yaw) * LgV2_B.bias[1];

      /* Fcn: '<S20>/Row3' */
      LgV2_B.Row3_p = LgV2_B.bias[2];

      /* Sum: '<S13>/Sum1' */
      LgV2_B.Sum1_g[0] = LgV2_B.Row1_g + LgV2_B.TmpHiddenBufferAtProduct1Inpo_e
        [0];
      LgV2_B.Sum1_g[1] = LgV2_B.Row2_b + LgV2_B.TmpHiddenBufferAtProduct1Inpo_e
        [1];
      LgV2_B.Sum1_g[2] = LgV2_B.Row3_p + LgV2_B.TmpHiddenBufferAtProduct1Inpo_e
        [2];

      /* Sum: '<S13>/Sum8' */
      LgV2_B.Sum8[0] = (LgV2_B.Row1_b + LgV2_B.Sum1_g[0]) - LgV2_B.Gain6[0];
      LgV2_B.Sum8[1] = (LgV2_B.Row2_d + LgV2_B.Sum1_g[1]) - LgV2_B.Gain6[1];
      LgV2_B.Sum8[2] = (LgV2_B.Row3_h + LgV2_B.Sum1_g[2]) - LgV2_B.Gain6[2];

      /* Fcn: '<S18>/Fcn' */
      LgV2_B.x_dot = cos(LgV2_B.eta_yaw) * LgV2_B.nu[0] - sin(LgV2_B.eta_yaw) *
        LgV2_B.nu[1];

      /* Fcn: '<S18>/Fcn1' */
      LgV2_B.y_dot = sin(LgV2_B.eta_yaw) * LgV2_B.nu[0] + cos(LgV2_B.eta_yaw) *
        LgV2_B.nu[1];

      /* Fcn: '<S18>/Fcn2' */
      LgV2_B.psi_dot = LgV2_B.nu[2];

      /* Sum: '<S13>/Sum3' */
      for (i = 0; i < 3; i++) {
        /* Gain: '<S13>/Gain3' */
        LgV2_B.Gain3[i] = 0.0;
        LgV2_B.Gain3[i] = LgV2_P.Gain3_Gain[i] * LgV2_B.Sum8[0] + LgV2_B.Gain3[i];
        LgV2_B.Gain3[i] = LgV2_P.Gain3_Gain[i + 3] * LgV2_B.Sum8[1] +
          LgV2_B.Gain3[i];
        LgV2_B.Gain3[i] = LgV2_P.Gain3_Gain[i + 6] * LgV2_B.Sum8[2] +
          LgV2_B.Gain3[i];

        /* Gain: '<S13>/K11' */
        LgV2_B.K11[i] = 0.0;
        LgV2_B.K11[i] = LgV2_P.K11_Gain[i] * LgV2_B.TmpHiddenBufferAtK11Inport1
          [0] + LgV2_B.K11[i];
        LgV2_B.K11[i] = LgV2_P.K11_Gain[i + 3] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[1] + LgV2_B.K11[i];
        LgV2_B.K11[i] = LgV2_P.K11_Gain[i + 6] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[2] + LgV2_B.K11[i];

        /* Gain: '<S13>/K12' */
        LgV2_B.K12[i] = 0.0;
        LgV2_B.K12[i] = LgV2_P.K12_Gain[i] * LgV2_B.TmpHiddenBufferAtK11Inport1
          [0] + LgV2_B.K12[i];
        LgV2_B.K12[i] = LgV2_P.K12_Gain[i + 3] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[1] + LgV2_B.K12[i];
        LgV2_B.K12[i] = LgV2_P.K12_Gain[i + 6] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[2] + LgV2_B.K12[i];

        /* Gain: '<S13>/K2' */
        LgV2_B.K2[i] = 0.0;
        LgV2_B.K2[i] = LgV2_P.K2_Gain[i] * LgV2_B.TmpHiddenBufferAtK11Inport1[0]
          + LgV2_B.K2[i];
        LgV2_B.K2[i] = LgV2_P.K2_Gain[i + 3] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[1] + LgV2_B.K2[i];
        LgV2_B.K2[i] = LgV2_P.K2_Gain[i + 6] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[2] + LgV2_B.K2[i];

        /* Gain: '<S13>/K3' */
        LgV2_B.K3[i] = 0.0;
        LgV2_B.K3[i] = LgV2_P.K3_Gain[i] * LgV2_B.TmpHiddenBufferAtK11Inport1[0]
          + LgV2_B.K3[i];
        LgV2_B.K3[i] = LgV2_P.K3_Gain[i + 3] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[1] + LgV2_B.K3[i];
        LgV2_B.K3[i] = LgV2_P.K3_Gain[i + 6] *
          LgV2_B.TmpHiddenBufferAtK11Inport1[2] + LgV2_B.K3[i];

        /* Sum: '<S13>/Sum5' */
        LgV2_B.psi_WF[i] = LgV2_B.K11[i] + LgV2_B.eta_w[i];

        /* Sum: '<S13>/Sum6' */
        LgV2_B.Sum6[i] = (LgV2_B.K12[i] - LgV2_B.Gain2[i]) - LgV2_B.Gain1_g[i];

        /* Gain: '<S13>/inv(T_b)' */
        LgV2_B.invT_b[i] = 0.0;
        LgV2_B.invT_b[i] = LgV2_P.invT_b_Gain[i] * LgV2_B.bias[0] +
          LgV2_B.invT_b[i];
        LgV2_B.invT_b[i] = LgV2_P.invT_b_Gain[i + 3] * LgV2_B.bias[1] +
          LgV2_B.invT_b[i];
        LgV2_B.invT_b[i] = LgV2_P.invT_b_Gain[i + 6] * LgV2_B.bias[2] +
          LgV2_B.invT_b[i];

        /* Sum: '<S13>/Sum7' */
        LgV2_B.Sum7[i] = LgV2_B.K3[i] - LgV2_B.invT_b[i];
      }

      LgV2_B.Sum3_h[0] = LgV2_B.K2[0] + LgV2_B.x_dot;
      LgV2_B.Sum3_h[1] = LgV2_B.K2[1] + LgV2_B.y_dot;
      LgV2_B.Sum3_h[2] = LgV2_B.K2[2] + LgV2_B.psi_dot;

      /* Saturate: '<S7>/Saturation' */
      tmp_0[0] = LgV2_B.DPu_1;
      tmp_0[1] = LgV2_B.DPu_2;
      tmp_0[2] = LgV2_B.DPu_3;
      tmp_0[3] = LgV2_B.DPu_4;
      tmp_0[4] = LgV2_B.DPu_5;
      for (i = 0; i < 5; i++) {
        LgV2_B.Saturation_p[i] = rt_SATURATE(tmp_0[i],
          LgV2_P.Saturation_LowerSat_d, LgV2_P.Saturation_UpperSat_do);
      }

      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* Constant: '<S7>/VSP_speeds' */
        LgV2_B.VSP_speeds = LgV2_P.VSP_speeds_Value;
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
    switch ((int32_T)LgV2_P.ControlMode_Value) {
     case 0:
      LgV2_B.ControlSwitch[0] = LgV2_B.Accuracyu_1;
      LgV2_B.ControlSwitch[1] = LgV2_B.Accuracyu_2;
      LgV2_B.ControlSwitch[2] = LgV2_B.Accuracyu_3;
      LgV2_B.ControlSwitch[3] = LgV2_B.Accuracyu_4;
      LgV2_B.ControlSwitch[4] = LgV2_B.Accuracyu_5;
      LgV2_B.ControlSwitch[5] = LgV2_P.AccuracyBTpower_Value;
      LgV2_B.ControlSwitch[6] = LgV2_P.AccuracyVSPspeed_Value;
      break;

     case 1:
      LgV2_B.ControlSwitch[0] = LgV2_B.PS3u_1;
      LgV2_B.ControlSwitch[1] = LgV2_B.PS3u_2;
      LgV2_B.ControlSwitch[2] = LgV2_B.PS3u_3;
      LgV2_B.ControlSwitch[3] = LgV2_B.PS3u_4;
      LgV2_B.ControlSwitch[4] = LgV2_B.PS3u_5;
      LgV2_B.ControlSwitch[5] = LgV2_P.PS3_BT_Power_Value;
      LgV2_B.ControlSwitch[6] = LgV2_P.PS3_VSP_Speed_Value;
      break;

     case 2:
      LgV2_B.ControlSwitch[0] = LgV2_B.Joysticku_1;
      LgV2_B.ControlSwitch[1] = LgV2_B.Joysticku_2;
      LgV2_B.ControlSwitch[2] = LgV2_B.Joysticku_3;
      LgV2_B.ControlSwitch[3] = LgV2_B.Joysticku_4;
      LgV2_B.ControlSwitch[4] = LgV2_B.Joysticku_5;
      LgV2_B.ControlSwitch[5] = LgV2_P.PS3_BT_Power_Value;
      LgV2_B.ControlSwitch[6] = LgV2_P.PS3_VSP_Speed_Value;
      break;

     default:
      for (i = 0; i < 5; i++) {
        LgV2_B.ControlSwitch[i] = LgV2_B.Saturation_p[i];
      }

      LgV2_B.ControlSwitch[5] = LgV2_B.BT_power_limit;
      LgV2_B.ControlSwitch[6] = LgV2_B.VSP_speeds;
      break;
    }

    /* Saturate: '<S1>/Saturation' */
    for (i = 0; i < 7; i++) {
      tmp = LgV2_B.ControlSwitch[i];
      LgV2_B.Saturation_e[i] = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_g,
        LgV2_P.Saturation_UpperSat_p);
    }

    /* Gain: '<S31>/QTM In2 Error' */
    LgV2_B.QTMIn2Error = LgV2_P.QTMIn2Error_Gain * LgV2_B.QTMIn[1];
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* SignalConversion: '<Root>/TmpHiddenBufferAtTo FileInport1' */
      for (i = 0; i < 7; i++) {
        LgV2_B.TmpHiddenBufferAtToFileInport1[i] = LgV2_B.Saturation_e[i];
      }

      LgV2_B.TmpHiddenBufferAtToFileInport1[7] = LgV2_B.eta_surge;
      LgV2_B.TmpHiddenBufferAtToFileInport1[8] = LgV2_B.eta_sway;
      LgV2_B.TmpHiddenBufferAtToFileInport1[9] = LgV2_B.eta_yaw;
      LgV2_B.TmpHiddenBufferAtToFileInport1[10] = LgV2_B.eta_dDPN;
      LgV2_B.TmpHiddenBufferAtToFileInport1[11] = LgV2_B.eta_dDPE;
      LgV2_B.TmpHiddenBufferAtToFileInport1[12] = LgV2_B.eta_dDPPsi;
      LgV2_B.TmpHiddenBufferAtToFileInport1[13] = LgV2_B.QTMIn2Error;

      /* ToFile Block: '<Root>/To File'
       */
      if (rtmIsMajorTimeStep(LgV2_M)) {
        if (!(++LgV2_DWork.ToFile_IWORK.Decimation % 1) &&
            (LgV2_DWork.ToFile_IWORK.Count*15)+1 < 100000000 ) {
          real_T u[15];
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
            if (fwrite(u, sizeof(real_T), 15, fp) != 15) {
              rtmSetErrorStatus(LgV2_M,
                                "Error writing to MAT-file CSE1_data.mat");
              return;
            }

            if (((++LgV2_DWork.ToFile_IWORK.Count)*15)+1 >= 100000000) {
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
    LgV2_B.eta_dPsideg = LgV2_P.eta_dPsideg_Gain * LgV2_B.MultiportSwitch[2];

    /* Gain: '<S2>/psi_d' */
    LgV2_B.psi_d = LgV2_P.psi_d_Gain * LgV2_B.eta_dDPPsi;

    /* Gain: '<S2>/x_d' */
    LgV2_B.x_d = LgV2_P.x_d_Gain * LgV2_B.eta_dDPN;

    /* Gain: '<S2>/y_d' */
    LgV2_B.y_d = LgV2_P.y_d_Gain * LgV2_B.eta_dDPE;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Gain: '<S3>/Battery Bow Thruster' */
      LgV2_B.BatteryBowThruster = LgV2_P.BatteryBowThruster_Gain *
        LgV2_B.SITzAI0;

      /* Gain: '<S3>/Battery Servo' */
      LgV2_B.BatteryServo = LgV2_P.BatteryServo_Gain * LgV2_B.SITzAI1;

      /* Gain: '<S3>/Battery Main' */
      LgV2_B.BatteryMain = LgV2_P.BatteryMain_Gain * LgV2_B.SITzAI2;
    }

    /* Gain: '<S31>/QTM In1 FPS' */
    LgV2_B.QTMIn1FPS = LgV2_P.QTMIn1FPS_Gain * LgV2_B.QTMIn[0];

    /* Gain: '<S31>/QTM In9 Residual' */
    LgV2_B.QTMIn9Residual = LgV2_P.QTMIn9Residual_Gain * LgV2_B.QTMIn[8];

    /* Gain: '<S5>/u_1 plant' */
    LgV2_B.u_1plant = LgV2_P.u_1plant_Gain * LgV2_B.Saturation_e[0];

    /* Gain: '<S5>/u_2 plant' */
    LgV2_B.u_2plant = LgV2_P.u_2plant_Gain * LgV2_B.Saturation_e[1];

    /* Gain: '<S5>/u_3 plant' */
    LgV2_B.u_3plant = LgV2_P.u_3plant_Gain * LgV2_B.Saturation_e[2];

    /* Gain: '<S5>/u_4 plant' */
    LgV2_B.u_4plant = LgV2_P.u_4plant_Gain * LgV2_B.Saturation_e[3];

    /* Gain: '<S5>/u_5 plant' */
    LgV2_B.u_5plant = LgV2_P.u_5plant_Gain * LgV2_B.Saturation_e[4];

    /* Gain: '<S5>/BT power limit plant' */
    LgV2_B.BTpowerlimitplant = LgV2_P.BTpowerlimitplant_Gain *
      LgV2_B.Saturation_e[5];

    /* Gain: '<S5>/VSP speed plant' */
    LgV2_B.VSPspeedplant = LgV2_P.VSPspeedplant_Gain * LgV2_B.Saturation_e[6];

    /* Outputs for enable SubSystem: '<S5>/CSE1' incorporates:
     *  Constant: '<S5>/Enable CSE1'
     *  EnablePort: '<S33>/Enable'
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
      /* Gain: '<S35>/BT_D_Gain1' */
      LgV2_B.BT_D_Gain1 = LgV2_P.BT_D_Gain1_Gain * LgV2_B.u_5plant;

      /* Gain: '<S35>/BT_D_Gain2' */
      LgV2_B.BT_D_Gain2 = LgV2_P.BT_D_Gain2_Gain * LgV2_B.u_5plant;

      /* Sum: '<S35>/Add' incorporates:
       *  Constant: '<S35>/BT_Power_Offset1'
       */
      LgV2_B.Add = (LgV2_B.BT_D_Gain1 + LgV2_P.BT_Power_Offset1_Value) +
        LgV2_B.BT_D_Gain2;

      /* Gain: '<S35>/BT_L_Gain1' */
      LgV2_B.BT_L_Gain1 = LgV2_P.BT_L_Gain1_Gain * LgV2_B.BTpowerlimitplant;

      /* Gain: '<S35>/BT_L_Gain2' */
      LgV2_B.BT_L_Gain2 = LgV2_P.BT_L_Gain2_Gain * LgV2_B.BTpowerlimitplant;

      /* Gain: '<S35>/Neg' */
      LgV2_B.Neg_b = LgV2_P.Neg_Gain * LgV2_B.BTpowerlimitplant;
      if (rtmIsMajorTimeStep(LgV2_M)) {
      }

      /* Sum: '<S35>/Sum1' incorporates:
       *  Constant: '<S35>/BT_Power_Offset2'
       */
      LgV2_B.Sum1_k = LgV2_B.BT_L_Gain1 + LgV2_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S39>/LowerRelop1' */
      LgV2_B.LowerRelop1_n = (LgV2_B.Add > LgV2_B.Sum1_k);

      /* Sum: '<S35>/Sum2' incorporates:
       *  Constant: '<S35>/BT_Power_Offset3'
       */
      LgV2_B.Sum2_m = LgV2_B.BT_L_Gain2 + LgV2_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S39>/UpperRelop' */
      LgV2_B.UpperRelop_m = (LgV2_B.Add < LgV2_B.Sum2_m);

      /* Switch: '<S39>/Switch' */
      if (LgV2_B.UpperRelop_m) {
        LgV2_B.Switch_i = LgV2_B.Sum2_m;
      } else {
        LgV2_B.Switch_i = LgV2_B.Add;
      }

      /* Switch: '<S39>/Switch2' */
      if (LgV2_B.LowerRelop1_n) {
        LgV2_B.Switch2_d = LgV2_B.Sum1_k;
      } else {
        LgV2_B.Switch2_d = LgV2_B.Switch_i;
      }

      if (rtmIsMajorTimeStep(LgV2_M)) {
      }

      /* RelationalOperator: '<S40>/LowerRelop1' incorporates:
       *  Constant: '<S35>/Constant'
       */
      LgV2_B.LowerRelop1_j = (LgV2_B.u_5plant > LgV2_P.Constant_Value_i);

      /* RelationalOperator: '<S40>/UpperRelop' */
      LgV2_B.UpperRelop_b = (LgV2_B.u_5plant < LgV2_B.Neg_b);

      /* Switch: '<S40>/Switch' */
      if (LgV2_B.UpperRelop_b) {
        LgV2_B.Switch_d = LgV2_B.Neg_b;
      } else {
        LgV2_B.Switch_d = LgV2_B.u_5plant;
      }

      /* Switch: '<S40>/Switch2' incorporates:
       *  Constant: '<S35>/Constant'
       */
      if (LgV2_B.LowerRelop1_j) {
        LgV2_B.Switch2_p = LgV2_P.Constant_Value_i;
      } else {
        LgV2_B.Switch2_p = LgV2_B.Switch_d;
      }

      if (rtmIsMajorTimeStep(LgV2_M)) {
      }

      /* RelationalOperator: '<S41>/LowerRelop1' */
      LgV2_B.LowerRelop1_b = (LgV2_B.u_5plant > LgV2_B.BTpowerlimitplant);

      /* RelationalOperator: '<S41>/UpperRelop' incorporates:
       *  Constant: '<S35>/Constant1'
       */
      LgV2_B.UpperRelop_h = (LgV2_B.u_5plant < LgV2_P.Constant1_Value_j);

      /* Switch: '<S41>/Switch' incorporates:
       *  Constant: '<S35>/Constant1'
       */
      if (LgV2_B.UpperRelop_h) {
        LgV2_B.Switch_d3 = LgV2_P.Constant1_Value_j;
      } else {
        LgV2_B.Switch_d3 = LgV2_B.u_5plant;
      }

      /* Switch: '<S41>/Switch2' */
      if (LgV2_B.LowerRelop1_b) {
        LgV2_B.Switch2_o = LgV2_B.BTpowerlimitplant;
      } else {
        LgV2_B.Switch2_o = LgV2_B.Switch_d3;
      }

      /* Signum: '<S38>/Sign' */
      LgV2_B.Sign = rt_SIGNd_snf(LgV2_B.VSPspeedplant);

      /* Product: '<S38>/Product1' */
      LgV2_B.PortVPS_X = LgV2_B.u_2plant * LgV2_B.Sign;

      /* Gain: '<S38>/-x' */
      LgV2_B.PortVPS_X_n = LgV2_P.x_Gain * LgV2_B.PortVPS_X;

      /* Product: '<S38>/Product2' */
      LgV2_B.PortVSP_Y = LgV2_B.u_1plant * LgV2_B.Sign;

      /* Gain: '<S38>/-y' */
      LgV2_B.PortVSP_Y_b = LgV2_P.y_Gain * LgV2_B.PortVSP_Y;

      /* Fcn: '<S42>/x->r' */
      LgV2_B.xr_n = rt_hypot_snf(LgV2_B.PortVPS_X_n, LgV2_B.PortVSP_Y_b);

      /* Fcn: '<S42>/x->theta' */
      LgV2_B.xtheta_i = rt_atan2_snf(LgV2_B.PortVSP_Y_b, LgV2_B.PortVPS_X_n);

      /* Product: '<S38>/Product3' */
      LgV2_B.StarboardVSP_X = LgV2_B.u_4plant * LgV2_B.Sign;

      /* Product: '<S38>/Product4' */
      LgV2_B.StarboardVSP_Y = LgV2_B.u_3plant * LgV2_B.Sign;

      /* Fcn: '<S43>/x->r' */
      LgV2_B.xr_h = rt_hypot_snf(LgV2_B.StarboardVSP_X, LgV2_B.StarboardVSP_Y);

      /* Fcn: '<S43>/x->theta' */
      LgV2_B.xtheta_n = rt_atan2_snf(LgV2_B.StarboardVSP_Y,
        LgV2_B.StarboardVSP_X);

      /* Gain: '<S44>/Gain' */
      LgV2_B.Gain = LgV2_P.Gain_Gain_l * LgV2_B.xtheta_i;

      /* Gain: '<S45>/Gain' */
      LgV2_B.Gain_i = LgV2_P.Gain_Gain_o * LgV2_B.xtheta_n;

      /* Lookup2D: '<S38>/Servo1' */
      LgV2_B.Servo1 = rt_Lookup2D_Normal((const real_T *)(&LgV2_P.Servo1_RowIdx
        [0]), 3, (const real_T *)(&LgV2_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&LgV2_P.Servo1_Table[0]), (const real_T)LgV2_B.PortVPS_X_n, (const
        real_T)LgV2_B.PortVSP_Y_b);

      /* Lookup2D: '<S38>/Servo2' */
      LgV2_B.Servo2 = rt_Lookup2D_Normal((const real_T *)(&LgV2_P.Servo2_RowIdx
        [0]), 3, (const real_T *)(&LgV2_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&LgV2_P.Servo2_Table[0]), (const real_T)LgV2_B.PortVPS_X_n, (const
        real_T)LgV2_B.PortVSP_Y_b);

      /* Lookup2D: '<S38>/Servo3' */
      LgV2_B.Servo3 = rt_Lookup2D_Normal((const real_T *)(&LgV2_P.Servo3_RowIdx
        [0]), 3, (const real_T *)(&LgV2_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&LgV2_P.Servo3_Table[0]), (const real_T)LgV2_B.StarboardVSP_X, (const
        real_T)LgV2_B.StarboardVSP_Y);

      /* Lookup2D: '<S38>/Servo4' */
      LgV2_B.Servo4 = rt_Lookup2D_Normal((const real_T *)(&LgV2_P.Servo4_RowIdx
        [0]), 3, (const real_T *)(&LgV2_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&LgV2_P.Servo4_Table[0]), (const real_T)LgV2_B.StarboardVSP_X, (const
        real_T)LgV2_B.StarboardVSP_Y);

      /* Gain: '<S38>/VPS_Speed_Gain' */
      LgV2_B.VPS_Speed_Gain = LgV2_P.VPS_Speed_Gain_Gain * LgV2_B.VSPspeedplant;

      /* Sum: '<S38>/Sum' incorporates:
       *  Constant: '<S38>/VPS_Power_Offset'
       */
      LgV2_B.Sum_d = LgV2_B.VPS_Speed_Gain + LgV2_P.VPS_Power_Offset_Value;

      /* Gain: '<S38>/VSPS Port' */
      LgV2_B.VSPSPort = LgV2_P.VSPSPort_Gain * LgV2_B.Sum_d;

      /* Gain: '<S38>/VSPS Starboard' */
      LgV2_B.VSPSStarboard = LgV2_P.VSPSStarboard_Gain * LgV2_B.Sum_d;
      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* Gain: '<S37>/-l_x1' incorporates:
         *  Constant: '<S37>/l_x1'
         */
        LgV2_B.l_x1_b = LgV2_P.l_x1_Gain_jm * LgV2_P.l_x1_Value_o;

        /* Gain: '<S37>/-l_y2' incorporates:
         *  Constant: '<S37>/l_y2'
         */
        LgV2_B.l_y2_h = LgV2_P.l_y2_Gain_f * LgV2_P.l_y2_Value_f;

        /* Gain: '<S37>/-l_x2' incorporates:
         *  Constant: '<S37>/l_x2'
         */
        LgV2_B.l_x2_p = LgV2_P.l_x2_Gain_bv * LgV2_P.l_x2_Value_j;

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
        LgV2_B.x5_n[0] = LgV2_P.T_e11_Value_c;
        LgV2_B.x5_n[1] = LgV2_P.T_e21_Value_l;
        LgV2_B.x5_n[2] = LgV2_P.l_y1_Value_e;
        LgV2_B.x5_n[3] = LgV2_P.T_e12_Value_k;
        LgV2_B.x5_n[4] = LgV2_P.T_e22_Value_i;
        LgV2_B.x5_n[5] = LgV2_B.l_x1_b;
        LgV2_B.x5_n[6] = LgV2_P.T_e13_Value_p;
        LgV2_B.x5_n[7] = LgV2_P.T_e23_Value_l;
        LgV2_B.x5_n[8] = LgV2_B.l_y2_h;
        LgV2_B.x5_n[9] = LgV2_P.T_e14_Value_b;
        LgV2_B.x5_n[10] = LgV2_P.T_e24_Value_e;
        LgV2_B.x5_n[11] = LgV2_B.l_x2_p;
        LgV2_B.x5_n[12] = LgV2_P.T_e15_Value_c;
        LgV2_B.x5_n[13] = LgV2_P.T_e25_Value_o;
        LgV2_B.x5_n[14] = LgV2_P.l_x3_Value_g;

        /* Gain: '<S36>/Gain K_e1_CSE1' incorporates:
         *  Constant: '<S36>/K_e1_CSE1'
         */
        LgV2_B.GainK_e1_CSE1 = LgV2_P.GainK_e1_CSE1_Gain *
          LgV2_P.K_e1_CSE1_Value;

        /* Gain: '<S36>/Gain K_e2_CSE1' incorporates:
         *  Constant: '<S36>/K_e2_CSE1'
         */
        LgV2_B.GainK_e2_CSE1 = LgV2_P.GainK_e2_CSE1_Gain *
          LgV2_P.K_e2_CSE1_Value;

        /* Gain: '<S36>/Gain K_e3_CSE1' incorporates:
         *  Constant: '<S36>/K_e3_CSE1'
         */
        LgV2_B.GainK_e3_CSE1 = LgV2_P.GainK_e3_CSE1_Gain *
          LgV2_P.K_e3_CSE1_Value;

        /* Gain: '<S36>/Gain K_e4_CSE1' incorporates:
         *  Constant: '<S36>/K_e4_CSE1'
         */
        LgV2_B.GainK_e4_CSE1 = LgV2_P.GainK_e4_CSE1_Gain *
          LgV2_P.K_e4_CSE1_Value;

        /* Gain: '<S36>/Gain K_e5_CSE1' incorporates:
         *  Constant: '<S36>/K_e5_CSE1'
         */
        LgV2_B.GainK_e5_CSE1 = LgV2_P.GainK_e5_CSE1_Gain *
          LgV2_P.K_e5_CSE1_Value;

        /* Reshape: '<S36>/Thruster Gain matrix' incorporates:
         *  Constant: '<S36>/Constant'
         */
        LgV2_B.ThrusterGainmatrix_mz[0] = LgV2_B.GainK_e1_CSE1;
        LgV2_B.ThrusterGainmatrix_mz[1] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[2] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[3] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[4] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[5] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[6] = LgV2_B.GainK_e2_CSE1;
        LgV2_B.ThrusterGainmatrix_mz[7] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[8] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[9] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[10] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[11] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[12] = LgV2_B.GainK_e3_CSE1;
        LgV2_B.ThrusterGainmatrix_mz[13] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[14] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[15] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[16] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[17] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[18] = LgV2_B.GainK_e4_CSE1;
        LgV2_B.ThrusterGainmatrix_mz[19] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[20] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[21] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[22] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[23] = LgV2_P.Constant_Value_p;
        LgV2_B.ThrusterGainmatrix_mz[24] = LgV2_B.GainK_e5_CSE1;
      }

      /* SignalConversion: '<S33>/TmpHiddenBufferAttau_cse1Inport3' */
      LgV2_B.TmpHiddenBufferAttau_cse1Inport[0] = LgV2_B.u_1plant;
      LgV2_B.TmpHiddenBufferAttau_cse1Inport[1] = LgV2_B.u_2plant;
      LgV2_B.TmpHiddenBufferAttau_cse1Inport[2] = LgV2_B.u_3plant;
      LgV2_B.TmpHiddenBufferAttau_cse1Inport[3] = LgV2_B.u_4plant;
      LgV2_B.TmpHiddenBufferAttau_cse1Inport[4] = LgV2_B.u_5plant;

      /* Product: '<S33>/tau_cse1' */
      for (i = 0; i < 3; i++) {
        for (tmp_4 = 0; tmp_4 < 5; tmp_4++) {
          tmp_2[i + 3 * tmp_4] = 0.0;
          for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
            tmp_2[i + 3 * tmp_4] = LgV2_B.x5_n[3 * tmp_3 + i] *
              LgV2_B.ThrusterGainmatrix_mz[5 * tmp_4 + tmp_3] + tmp_2[3 * tmp_4
              + i];
          }
        }
      }

      for (i = 0; i < 3; i++) {
        LgV2_B.tau_cse1[i] = 0.0;
        for (tmp_4 = 0; tmp_4 < 5; tmp_4++) {
          LgV2_B.tau_cse1[i] = tmp_2[3 * tmp_4 + i] *
            LgV2_B.TmpHiddenBufferAttau_cse1Inport[tmp_4] + LgV2_B.tau_cse1[i];
        }
      }

      /* Gain: '<S33>/CSE1 tau_surge' */
      LgV2_B.CSE1tau_surge = LgV2_P.CSE1tau_surge_Gain * LgV2_B.tau_cse1[0];

      /* Gain: '<S33>/CSE1 tau_sway' */
      LgV2_B.CSE1tau_sway = LgV2_P.CSE1tau_sway_Gain * LgV2_B.tau_cse1[1];

      /* Gain: '<S33>/CSE1 tau_yaw' */
      LgV2_B.CSE1tau_yaw = LgV2_P.CSE1tau_yaw_Gain * LgV2_B.tau_cse1[2];
    }

    /* end of Outputs for SubSystem: '<S5>/CSE1' */
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
    real_T tmp[15];
    int32_T tmp_0;
    int32_T tmp_1;
    int32_T tmp_2;

    /* Update for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S34>/Enable'
     */
    if (LgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S47>/Gain u_1' */
      LgV2_B.Gainu_1 = LgV2_P.Gainu_1_Gain * LgV2_B.u_1plant;

      /* Gain: '<S47>/Gain u_2' */
      LgV2_B.Gainu_2 = LgV2_P.Gainu_2_Gain * LgV2_B.u_2plant;

      /* Gain: '<S47>/Gain u_3' */
      LgV2_B.Gainu_3 = LgV2_P.Gainu_3_Gain * LgV2_B.u_3plant;

      /* Gain: '<S47>/Gain u_4' */
      LgV2_B.Gainu_4 = LgV2_P.Gainu_4_Gain * LgV2_B.u_4plant;

      /* Gain: '<S47>/Gain BT power' */
      LgV2_B.GainBTpower = LgV2_P.GainBTpower_Gain * LgV2_B.BTpowerlimitplant;

      /* Product: '<S56>/delta rise limit' */
      LgV2_B.deltariselimit = LgV2_B.GainBTpower * LgV2_B.sampletime;

      /* Sum: '<S56>/Difference Inputs1' */
      LgV2_B.UkYk1 = LgV2_B.u_5plant - LgV2_B.Yk1;

      /* RelationalOperator: '<S58>/LowerRelop1' */
      LgV2_B.LowerRelop1 = (LgV2_B.UkYk1 > LgV2_B.deltariselimit);

      /* Gain: '<S47>/Neg' */
      LgV2_B.Neg = LgV2_P.Neg_Gain_f * LgV2_B.GainBTpower;

      /* Product: '<S56>/delta fall limit' */
      LgV2_B.deltafalllimit = LgV2_B.Neg * LgV2_B.sampletime;

      /* RelationalOperator: '<S58>/UpperRelop' */
      LgV2_B.UpperRelop = (LgV2_B.UkYk1 < LgV2_B.deltafalllimit);

      /* Switch: '<S58>/Switch' */
      if (LgV2_B.UpperRelop) {
        LgV2_B.Switch = LgV2_B.deltafalllimit;
      } else {
        LgV2_B.Switch = LgV2_B.UkYk1;
      }

      /* Switch: '<S58>/Switch2' */
      if (LgV2_B.LowerRelop1) {
        LgV2_B.Switch2 = LgV2_B.deltariselimit;
      } else {
        LgV2_B.Switch2 = LgV2_B.Switch;
      }

      /* Sum: '<S56>/Difference Inputs2' */
      LgV2_B.DifferenceInputs2 = LgV2_B.Switch2 + LgV2_B.Yk1;

      /* Gain: '<S47>/Gain u_5' */
      LgV2_B.Gainu_5 = LgV2_P.Gainu_5_Gain * LgV2_B.DifferenceInputs2;

      /* SignalConversion: '<S47>/TmpHiddenBufferAtT_e^+ K_e^-1 u_eInport3' */
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[0] = LgV2_B.Gainu_1;
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[1] = LgV2_B.Gainu_2;
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[2] = LgV2_B.Gainu_3;
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[3] = LgV2_B.Gainu_4;
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[4] = LgV2_B.Gainu_5;

      /* Product: '<S47>/T_e^+ K_e^-1 u_e' */
      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          tmp[tmp_0 + 3 * tmp_2] = 0.0;
          for (tmp_1 = 0; tmp_1 < 5; tmp_1++) {
            tmp[tmp_0 + 3 * tmp_2] = LgV2_B.x5_m[3 * tmp_1 + tmp_0] *
              LgV2_B.ThrusterGainmatrix_m[5 * tmp_2 + tmp_1] + tmp[3 * tmp_2 +
              tmp_0];
          }
        }
      }

      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        LgV2_B.T_eK_e1u_e[tmp_0] = 0.0;
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          LgV2_B.T_eK_e1u_e[tmp_0] = tmp[3 * tmp_2 + tmp_0] *
            LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[tmp_2] +
            LgV2_B.T_eK_e1u_e[tmp_0];
        }
      }

      /* Gain: '<S47>/tau_surge_hil' */
      LgV2_B.tau_surge_hil = LgV2_P.tau_surge_hil_Gain * LgV2_B.T_eK_e1u_e[0];

      /* Gain: '<S47>/tau_sway_hil' */
      LgV2_B.tau_sway_hil = LgV2_P.tau_sway_hil_Gain * LgV2_B.T_eK_e1u_e[1];

      /* Gain: '<S47>/tau_yaw_hil' */
      LgV2_B.tau_yaw_hil = LgV2_P.tau_yaw_hil_Gain * LgV2_B.T_eK_e1u_e[2];

      /* Sum: '<S46>/Sum' */
      LgV2_B.Sum_h[0] = LgV2_B.tau_surge_hil - LgV2_B.Product1_h[0];
      LgV2_B.Sum_h[1] = LgV2_B.tau_sway_hil - LgV2_B.Product1_h[1];
      LgV2_B.Sum_h[2] = LgV2_B.tau_yaw_hil - LgV2_B.Product1_h[2];

      /* Product: '<S46>/Product2' */
      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        LgV2_B.Product2[tmp_0] = 0.0;
        LgV2_B.Product2[tmp_0] = LgV2_B.Inverse[tmp_0] * LgV2_B.Sum_h[0] +
          LgV2_B.Product2[tmp_0];
        LgV2_B.Product2[tmp_0] = LgV2_B.Inverse[tmp_0 + 3] * LgV2_B.Sum_h[1] +
          LgV2_B.Product2[tmp_0];
        LgV2_B.Product2[tmp_0] = LgV2_B.Inverse[tmp_0 + 6] * LgV2_B.Sum_h[2] +
          LgV2_B.Product2[tmp_0];
      }

      /* Fcn: '<S53>/x->r' */
      LgV2_B.xr = rt_hypot_snf(LgV2_B.u_2plant, LgV2_B.u_1plant);

      /* Fcn: '<S53>/x->theta' */
      LgV2_B.xtheta = rt_atan2_snf(LgV2_B.u_1plant, LgV2_B.u_2plant);

      /* Fcn: '<S54>/x->r' */
      LgV2_B.xr_l = rt_hypot_snf(LgV2_B.u_4plant, LgV2_B.u_3plant);

      /* Fcn: '<S54>/x->theta' */
      LgV2_B.xtheta_j = rt_atan2_snf(LgV2_B.u_3plant, LgV2_B.u_4plant);

      /* Gain: '<S47>/VSP_angle_deg_port' */
      LgV2_B.VSP_angle_deg_port = LgV2_P.VSP_angle_deg_port_Gain * LgV2_B.xtheta;

      /* Gain: '<S47>/VSP_angle_deg_stbd' */
      LgV2_B.VSP_angle_deg_stbd = LgV2_P.VSP_angle_deg_stbd_Gain *
        LgV2_B.xtheta_j;
      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* Update for UnitDelay: '<S56>/Delay Input2' */
        LgV2_DWork.DelayInput2_DSTATE = LgV2_B.DifferenceInputs2;
      }
    }

    /* end of Update for SubSystem: '<S5>/Linear Simulator' */

    /* Derivative Block: '<S31>/Derivative' */
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

    /* Update for enable SubSystem: '<S1>/DP control' incorporates:
     *  Update for EnablePort: '<S7>/Enable'
     */
    if (LgV2_DWork.DPcontrol_MODE == SUBSYS_ENABLED) {
    }

    /* end of Update for SubSystem: '<S1>/DP control' */
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
    real_T tmp[15];
    int32_T tmp_0;
    int32_T tmp_1;
    int32_T tmp_2;

    /* TransferFcn Block: '<S25>/Transfer Fcn' */
    {
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->TransferFcn_CSTATE =
        LgV2_P.x_d_Value;
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->TransferFcn_CSTATE +=
        (LgV2_P.TransferFcn_A)*LgV2_X.TransferFcn_CSTATE;
    }

    /* TransferFcn Block: '<S25>/Transfer Fcn1' */
    {
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->TransferFcn1_CSTATE =
        LgV2_P.y_d_Value;
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->TransferFcn1_CSTATE +=
        (LgV2_P.TransferFcn1_A)*LgV2_X.TransferFcn1_CSTATE;
    }

    /* TransferFcn Block: '<S25>/Transfer Fcn2' */
    {
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->TransferFcn2_CSTATE =
        LgV2_B.Gain1;
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->TransferFcn2_CSTATE +=
        (LgV2_P.TransferFcn2_A)*LgV2_X.TransferFcn2_CSTATE;
    }

    /* Derivatives for enable SubSystem: '<S5>/Linear Simulator' */
    if (LgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S47>/Gain u_1' */
      LgV2_B.Gainu_1 = LgV2_P.Gainu_1_Gain * LgV2_B.u_1plant;

      /* Gain: '<S47>/Gain u_2' */
      LgV2_B.Gainu_2 = LgV2_P.Gainu_2_Gain * LgV2_B.u_2plant;

      /* Gain: '<S47>/Gain u_3' */
      LgV2_B.Gainu_3 = LgV2_P.Gainu_3_Gain * LgV2_B.u_3plant;

      /* Gain: '<S47>/Gain u_4' */
      LgV2_B.Gainu_4 = LgV2_P.Gainu_4_Gain * LgV2_B.u_4plant;

      /* Gain: '<S47>/Gain BT power' */
      LgV2_B.GainBTpower = LgV2_P.GainBTpower_Gain * LgV2_B.BTpowerlimitplant;

      /* Product: '<S56>/delta rise limit' */
      LgV2_B.deltariselimit = LgV2_B.GainBTpower * LgV2_B.sampletime;

      /* Sum: '<S56>/Difference Inputs1' */
      LgV2_B.UkYk1 = LgV2_B.u_5plant - LgV2_B.Yk1;

      /* RelationalOperator: '<S58>/LowerRelop1' */
      LgV2_B.LowerRelop1 = (LgV2_B.UkYk1 > LgV2_B.deltariselimit);

      /* Gain: '<S47>/Neg' */
      LgV2_B.Neg = LgV2_P.Neg_Gain_f * LgV2_B.GainBTpower;

      /* Product: '<S56>/delta fall limit' */
      LgV2_B.deltafalllimit = LgV2_B.Neg * LgV2_B.sampletime;

      /* RelationalOperator: '<S58>/UpperRelop' */
      LgV2_B.UpperRelop = (LgV2_B.UkYk1 < LgV2_B.deltafalllimit);

      /* Switch: '<S58>/Switch' */
      if (LgV2_B.UpperRelop) {
        LgV2_B.Switch = LgV2_B.deltafalllimit;
      } else {
        LgV2_B.Switch = LgV2_B.UkYk1;
      }

      /* Switch: '<S58>/Switch2' */
      if (LgV2_B.LowerRelop1) {
        LgV2_B.Switch2 = LgV2_B.deltariselimit;
      } else {
        LgV2_B.Switch2 = LgV2_B.Switch;
      }

      /* Sum: '<S56>/Difference Inputs2' */
      LgV2_B.DifferenceInputs2 = LgV2_B.Switch2 + LgV2_B.Yk1;

      /* Gain: '<S47>/Gain u_5' */
      LgV2_B.Gainu_5 = LgV2_P.Gainu_5_Gain * LgV2_B.DifferenceInputs2;

      /* SignalConversion: '<S47>/TmpHiddenBufferAtT_e^+ K_e^-1 u_eInport3' */
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[0] = LgV2_B.Gainu_1;
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[1] = LgV2_B.Gainu_2;
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[2] = LgV2_B.Gainu_3;
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[3] = LgV2_B.Gainu_4;
      LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[4] = LgV2_B.Gainu_5;

      /* Product: '<S47>/T_e^+ K_e^-1 u_e' */
      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          tmp[tmp_0 + 3 * tmp_2] = 0.0;
          for (tmp_1 = 0; tmp_1 < 5; tmp_1++) {
            tmp[tmp_0 + 3 * tmp_2] = LgV2_B.x5_m[3 * tmp_1 + tmp_0] *
              LgV2_B.ThrusterGainmatrix_m[5 * tmp_2 + tmp_1] + tmp[3 * tmp_2 +
              tmp_0];
          }
        }
      }

      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        LgV2_B.T_eK_e1u_e[tmp_0] = 0.0;
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          LgV2_B.T_eK_e1u_e[tmp_0] = tmp[3 * tmp_2 + tmp_0] *
            LgV2_B.TmpHiddenBufferAtT_eK_e1u_eInpo[tmp_2] +
            LgV2_B.T_eK_e1u_e[tmp_0];
        }
      }

      /* Gain: '<S47>/tau_surge_hil' */
      LgV2_B.tau_surge_hil = LgV2_P.tau_surge_hil_Gain * LgV2_B.T_eK_e1u_e[0];

      /* Gain: '<S47>/tau_sway_hil' */
      LgV2_B.tau_sway_hil = LgV2_P.tau_sway_hil_Gain * LgV2_B.T_eK_e1u_e[1];

      /* Gain: '<S47>/tau_yaw_hil' */
      LgV2_B.tau_yaw_hil = LgV2_P.tau_yaw_hil_Gain * LgV2_B.T_eK_e1u_e[2];

      /* Sum: '<S46>/Sum' */
      LgV2_B.Sum_h[0] = LgV2_B.tau_surge_hil - LgV2_B.Product1_h[0];
      LgV2_B.Sum_h[1] = LgV2_B.tau_sway_hil - LgV2_B.Product1_h[1];
      LgV2_B.Sum_h[2] = LgV2_B.tau_yaw_hil - LgV2_B.Product1_h[2];

      /* Product: '<S46>/Product2' */
      for (tmp_0 = 0; tmp_0 < 3; tmp_0++) {
        LgV2_B.Product2[tmp_0] = 0.0;
        LgV2_B.Product2[tmp_0] = LgV2_B.Inverse[tmp_0] * LgV2_B.Sum_h[0] +
          LgV2_B.Product2[tmp_0];
        LgV2_B.Product2[tmp_0] = LgV2_B.Inverse[tmp_0 + 3] * LgV2_B.Sum_h[1] +
          LgV2_B.Product2[tmp_0];
        LgV2_B.Product2[tmp_0] = LgV2_B.Inverse[tmp_0 + 6] * LgV2_B.Sum_h[2] +
          LgV2_B.Product2[tmp_0];
      }

      /* Fcn: '<S53>/x->r' */
      LgV2_B.xr = rt_hypot_snf(LgV2_B.u_2plant, LgV2_B.u_1plant);

      /* Fcn: '<S53>/x->theta' */
      LgV2_B.xtheta = rt_atan2_snf(LgV2_B.u_1plant, LgV2_B.u_2plant);

      /* Fcn: '<S54>/x->r' */
      LgV2_B.xr_l = rt_hypot_snf(LgV2_B.u_4plant, LgV2_B.u_3plant);

      /* Fcn: '<S54>/x->theta' */
      LgV2_B.xtheta_j = rt_atan2_snf(LgV2_B.u_3plant, LgV2_B.u_4plant);

      /* Gain: '<S47>/VSP_angle_deg_port' */
      LgV2_B.VSP_angle_deg_port = LgV2_P.VSP_angle_deg_port_Gain * LgV2_B.xtheta;

      /* Gain: '<S47>/VSP_angle_deg_stbd' */
      LgV2_B.VSP_angle_deg_stbd = LgV2_P.VSP_angle_deg_stbd_Gain *
        LgV2_B.xtheta_j;

      /* Integrator Block: '<S46>/Integrator' */
      {
        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE[0] = LgV2_B.Product2[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE[0] = 0.0;
        }

        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE[1] = LgV2_B.Product2[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE[1] = 0.0;
        }

        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE[2] = LgV2_B.Product2[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE[2] = 0.0;
        }
      }

      /* Integrator Block: '<S46>/Integrator1' */
      {
        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE[0] = LgV2_B.Product3[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE[0] = 0.0;
        }

        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE[1] = LgV2_B.Product3[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE[1] = 0.0;
        }

        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE[2] = LgV2_B.Product3[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE[2] = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
               ->Integrator_CSTATE[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S5>/Linear Simulator' */

    /* Derivatives for enable SubSystem: '<S1>/DP control' */
    if (LgV2_DWork.DPcontrol_MODE == SUBSYS_ENABLED) {
      /* Derivatives for Integrator: '<S13>/Integrator1' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->
        Integrator1_CSTATE_m[0] = LgV2_B.Sum6[0];

      /* Derivatives for Integrator: '<S13>/Integrator' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE_h
        [0] = LgV2_B.Sum3_h[0];

      /* Derivatives for Integrator: '<S13>/Integrator1' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->
        Integrator1_CSTATE_m[1] = LgV2_B.Sum6[1];

      /* Derivatives for Integrator: '<S13>/Integrator' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE_h
        [1] = LgV2_B.Sum3_h[1];

      /* Derivatives for Integrator: '<S13>/Integrator1' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->
        Integrator1_CSTATE_m[2] = LgV2_B.Sum6[2];

      /* Derivatives for Integrator: '<S13>/Integrator' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE_h
        [2] = LgV2_B.Sum3_h[2];

      /* Integrator Block: '<S11>/Integrator' */
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

      /* Derivatives for Integrator: '<S13>/Integrator4' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator4_CSTATE[0]
        = LgV2_B.Gain3[0];

      /* Derivatives for Integrator: '<S13>/Integrator2' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator2_CSTATE[0]
        = LgV2_B.psi_WF[0];

      /* Derivatives for Integrator: '<S13>/Integrator3' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator3_CSTATE[0]
        = LgV2_B.Sum7[0];

      /* Derivatives for Integrator: '<S13>/Integrator4' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator4_CSTATE[1]
        = LgV2_B.Gain3[1];

      /* Derivatives for Integrator: '<S13>/Integrator2' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator2_CSTATE[1]
        = LgV2_B.psi_WF[1];

      /* Derivatives for Integrator: '<S13>/Integrator3' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator3_CSTATE[1]
        = LgV2_B.Sum7[1];

      /* Derivatives for Integrator: '<S13>/Integrator4' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator4_CSTATE[2]
        = LgV2_B.Gain3[2];

      /* Derivatives for Integrator: '<S13>/Integrator2' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator2_CSTATE[2]
        = LgV2_B.psi_WF[2];

      /* Derivatives for Integrator: '<S13>/Integrator3' */
      ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator3_CSTATE[2]
        = LgV2_B.Sum7[2];
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
               ->Integrator1_CSTATE_m[0]);
        for (i=0; i < 18; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S1>/DP control' */
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
  LgV2_M->ModelData.contStates = ((real_T *) &LgV2_X);
  rtsiSetSolverData(&LgV2_M->solverInfo, (void *)&LgV2_M->ModelData.intgData);
  rtsiSetSolverName(&LgV2_M->solverInfo,"ode3");

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
}

/* Model terminate function */
void LgV2_terminate(void)
{
  /* Terminate for enable SubSystem: '<S1>/DP control' */

  /* ToFile Block: '<S7>/To File' */
  {
    FILE *fp = (FILE *) LgV2_DWork.ToFile_PWORK_b.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data_eta_w.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(LgV2_M, "Error closing MAT-file CSE1_data_eta_w.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(LgV2_M, "Error reopening MAT-file CSE1_data_eta_w.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4, LgV2_DWork.ToFile_IWORK_h.Count,
           "cse1_data")) {
        rtmSetErrorStatus(LgV2_M,
                          "Error writing header for cse1_data to MAT-file CSE1_data_eta_w.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(LgV2_M, "Error closing MAT-file CSE1_data_eta_w.mat");
        return;
      }

      LgV2_DWork.ToFile_PWORK_b.FilePtr = (NULL);
    }
  }

  /* ToFile Block: '<S11>/To File' */
  {
    FILE *fp = (FILE *) LgV2_DWork.ToFile_PWORK_e.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data_reg_error.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(LgV2_M,
                          "Error closing MAT-file CSE1_data_reg_error.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(LgV2_M,
                          "Error reopening MAT-file CSE1_data_reg_error.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4, LgV2_DWork.ToFile_IWORK_k.Count,
           "cse1_data_reg_error")) {
        rtmSetErrorStatus(LgV2_M,
                          "Error writing header for cse1_data_reg_error to MAT-file CSE1_data_reg_error.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(LgV2_M,
                          "Error closing MAT-file CSE1_data_reg_error.mat");
        return;
      }

      LgV2_DWork.ToFile_PWORK_e.FilePtr = (NULL);
    }
  }

  /* end of Terminate for SubSystem: '<S1>/DP control' */

  /* ToFile Block: '<Root>/To File' */
  {
    FILE *fp = (FILE *) LgV2_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(LgV2_M, "Error closing MAT-file CSE1_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(LgV2_M, "Error reopening MAT-file CSE1_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 15, LgV2_DWork.ToFile_IWORK.Count,
           "cse1_data")) {
        rtmSetErrorStatus(LgV2_M,
                          "Error writing header for cse1_data to MAT-file CSE1_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(LgV2_M, "Error closing MAT-file CSE1_data.mat");
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
  LgV2_M->Sizes.numContStates = (27);  /* Number of continuous states */
  LgV2_M->Sizes.numY = (0);            /* Number of model outputs */
  LgV2_M->Sizes.numU = (0);            /* Number of model inputs */
  LgV2_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  LgV2_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  LgV2_M->Sizes.numBlocks = (545);     /* Number of blocks */
  LgV2_M->Sizes.numBlockIO = (368);    /* Number of block outputs */
  LgV2_M->Sizes.numBlockPrms = (618);  /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* TransferFcn Block: '<S25>/Transfer Fcn' */
  LgV2_X.TransferFcn_CSTATE = 0.0;

  /* TransferFcn Block: '<S25>/Transfer Fcn1' */
  LgV2_X.TransferFcn1_CSTATE = 0.0;

  /* TransferFcn Block: '<S25>/Transfer Fcn2' */
  LgV2_X.TransferFcn2_CSTATE = 0.0;

  /* Derivative Block: '<S31>/Derivative' */
  LgV2_DWork.Derivative_RWORK.TimeStampA = rtInf;
  LgV2_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(LgV2_M)) {
    rtmSetFirstInitCond(LgV2_M, 0);
  }
}

void MdlStart(void)
{
  {
    int32_T i;

    /* Create Identity Matrix for Block: '<S8>/K_e^-1' */
    {
      int_T i;
      real_T *dWork = &LgV2_DWork.K_e1_DWORK4[0];
      for (i = 0; i < 25; i++) {
        *dWork++ = 0.0;
      }

      dWork = &LgV2_DWork.K_e1_DWORK4[0];
      while (dWork < &LgV2_DWork.K_e1_DWORK4[0]+25) {
        *dWork = 1;
        dWork += 6;
      }
    }

    /* Start for enable SubSystem: '<S5>/Linear Simulator' */
    LgV2_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

    /* Start for Constant: '<S49>/psi_0' */
    LgV2_B.psi_0 = LgV2_P.psi_0_Value;

    /* Start for Constant: '<S49>/x_0' */
    LgV2_B.x_0 = LgV2_P.x_0_Value;

    /* Start for Constant: '<S49>/y_0' */
    LgV2_B.y_0 = LgV2_P.y_0_Value;

    /* Start for Constant: '<S50>/r_0' */
    LgV2_B.r_0 = LgV2_P.r_0_Value;

    /* Start for Constant: '<S50>/u_0' */
    LgV2_B.u_0 = LgV2_P.u_0_Value;

    /* Start for Constant: '<S50>/v_0' */
    LgV2_B.v_0 = LgV2_P.v_0_Value;

    /* Create Identity Matrix for Block: '<S51>/Inverse' */
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

    /* Start for UnitDelay: '<S56>/Delay Input2' */
    LgV2_B.Yk1 = LgV2_P.DelayInput2_X0;

    /* Integrator Block: '<S46>/Integrator' */
    if (rtmIsFirstInitCond(LgV2_M)) {
      LgV2_X.Integrator_CSTATE[0] = 0.0;
      LgV2_X.Integrator_CSTATE[1] = 0.0;
      LgV2_X.Integrator_CSTATE[2] = 0.0;
    }

    LgV2_DWork.Integrator_IWORK.IcNeedsLoading = 1;

    /* Integrator Block: '<S46>/Integrator1' */
    if (rtmIsFirstInitCond(LgV2_M)) {
      LgV2_X.Integrator1_CSTATE[0] = 0.0;
      LgV2_X.Integrator1_CSTATE[1] = 0.0;
      LgV2_X.Integrator1_CSTATE[2] = 0.0;
    }

    LgV2_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

    /* InitializeConditions for UnitDelay: '<S56>/Delay Input2' */
    LgV2_DWork.DelayInput2_DSTATE = LgV2_P.DelayInput2_X0;

    /* end of Start for SubSystem: '<S5>/Linear Simulator' */

    /* Start for enable SubSystem: '<S1>/DP control' */
    LgV2_DWork.DPcontrol_MODE = SUBSYS_DISABLED;

    /* ToFile Block: '<S7>/To File' */
    {
      const char *fileName = "CSE1_data_eta_w.mat";
      FILE *fp;
      if ((fp = fopen(fileName, "wb")) == (NULL)) {
        rtmSetErrorStatus(LgV2_M, "Error creating .mat file CSE1_data_eta_w.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp,4,0,"cse1_data")) {
        rtmSetErrorStatus(LgV2_M,
                          "Error writing mat file header to file CSE1_data_eta_w.mat");
        return;
      }

      LgV2_DWork.ToFile_IWORK_h.Count = 0;
      LgV2_DWork.ToFile_IWORK_h.Decimation = -1;
      LgV2_DWork.ToFile_PWORK_b.FilePtr = fp;
    }

    /* ToFile Block: '<S11>/To File' */
    {
      const char *fileName = "CSE1_data_reg_error.mat";
      FILE *fp;
      if ((fp = fopen(fileName, "wb")) == (NULL)) {
        rtmSetErrorStatus(LgV2_M,
                          "Error creating .mat file CSE1_data_reg_error.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp,4,0,"cse1_data_reg_error")) {
        rtmSetErrorStatus(LgV2_M,
                          "Error writing mat file header to file CSE1_data_reg_error.mat");
        return;
      }

      LgV2_DWork.ToFile_IWORK_k.Count = 0;
      LgV2_DWork.ToFile_IWORK_k.Decimation = -1;
      LgV2_DWork.ToFile_PWORK_e.FilePtr = fp;
    }

    /* Create Identity Matrix for Block: '<S7>/K_e^-1' */
    {
      int_T i;
      real_T *dWork = &LgV2_DWork.K_e1_DWORK4_d[0];
      for (i = 0; i < 25; i++) {
        *dWork++ = 0.0;
      }

      dWork = &LgV2_DWork.K_e1_DWORK4_d[0];
      while (dWork < &LgV2_DWork.K_e1_DWORK4_d[0]+25) {
        *dWork = 1;
        dWork += 6;
      }
    }

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    LgV2_X.Integrator1_CSTATE_m[0] = LgV2_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator' */
    LgV2_X.Integrator_CSTATE_h[0] = LgV2_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    LgV2_X.Integrator1_CSTATE_m[1] = LgV2_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator' */
    LgV2_X.Integrator_CSTATE_h[1] = LgV2_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    LgV2_X.Integrator1_CSTATE_m[2] = LgV2_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator' */
    LgV2_X.Integrator_CSTATE_h[2] = LgV2_P.Integrator_IC;

    /* Integrator Block: '<S11>/Integrator' */
    LgV2_X.Integrator_CSTATE_k[0] = LgV2_P.Integrator_IC_f;
    LgV2_X.Integrator_CSTATE_k[1] = LgV2_P.Integrator_IC_f;
    LgV2_X.Integrator_CSTATE_k[2] = LgV2_P.Integrator_IC_f;

    /* InitializeConditions for Integrator: '<S13>/Integrator4' */
    LgV2_X.Integrator4_CSTATE[0] = LgV2_P.Integrator4_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator2' */
    LgV2_X.Integrator2_CSTATE[0] = LgV2_P.Integrator2_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator3' */
    LgV2_X.Integrator3_CSTATE[0] = LgV2_P.Integrator3_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator4' */
    LgV2_X.Integrator4_CSTATE[1] = LgV2_P.Integrator4_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator2' */
    LgV2_X.Integrator2_CSTATE[1] = LgV2_P.Integrator2_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator3' */
    LgV2_X.Integrator3_CSTATE[1] = LgV2_P.Integrator3_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator4' */
    LgV2_X.Integrator4_CSTATE[2] = LgV2_P.Integrator4_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator2' */
    LgV2_X.Integrator2_CSTATE[2] = LgV2_P.Integrator2_IC;

    /* InitializeConditions for Integrator: '<S13>/Integrator3' */
    LgV2_X.Integrator3_CSTATE[2] = LgV2_P.Integrator3_IC;

    /* VirtualOutportStart for Outport: '<S7>/Thruster_Command_DP' */
    for (i = 0; i < 5; i++) {
      LgV2_B.Saturation_p[i] = LgV2_P.Thruster_Command_DP_Y0[i];
    }

    LgV2_B.BT_power_limit = LgV2_P.Thruster_Command_DP_Y0[5];
    LgV2_B.VSP_speeds = LgV2_P.Thruster_Command_DP_Y0[6];

    /* end of Start for SubSystem: '<S1>/DP control' */

    /* ToFile Block: '<Root>/To File' */
    {
      const char *fileName = "CSE1_data.mat";
      FILE *fp;
      if ((fp = fopen(fileName, "wb")) == (NULL)) {
        rtmSetErrorStatus(LgV2_M, "Error creating .mat file CSE1_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp,15,0,"cse1_data")) {
        rtmSetErrorStatus(LgV2_M,
                          "Error writing mat file header to file CSE1_data.mat");
        return;
      }

      LgV2_DWork.ToFile_IWORK.Count = 0;
      LgV2_DWork.ToFile_IWORK.Decimation = -1;
      LgV2_DWork.ToFile_PWORK.FilePtr = fp;
    }

    /* Start for enable SubSystem: '<S5>/CSE1' */
    LgV2_DWork.CSE1_MODE = SUBSYS_DISABLED;

    /* end of Start for SubSystem: '<S5>/CSE1' */
  }

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

extern LgV2_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Naviagation Systems/Qualisys 6 DOF/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(LgV2_B.QTMIn, count, data[index++], 34, 0);
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

  // Plants/CSE1/Bow Thruster/SIT Out5 BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Switch2_d,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out1 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out2 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out3 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out4 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out6 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out7 VSPS Starboard: Virtual Signal # 0
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

  // Plants/CSE1/Bow Thruster/SIT Out5 BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Switch2_d,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out1 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo1,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out2 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out3 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo3,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out4 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo4,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out6 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.VSPSPort,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out7 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.VSPSStarboard,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "lgv2/Control Systems/Control Mode/Value", offsetof(Parameters_LgV2,
    ControlMode_Value), 31, 1, 2, 0, "", 0 },

  { 1, "lgv2/HMI/Accuracy control/u1/Value", offsetof(Parameters_LgV2, u1_Value),
    31, 1, 2, 2, "", 0 },

  { 2, "lgv2/HMI/Accuracy control/Accuracy u_1/Gain", offsetof(Parameters_LgV2,
    Accuracyu_1_Gain), 31, 1, 2, 4, "", 0 },

  { 3, "lgv2/HMI/Accuracy control/u2/Value", offsetof(Parameters_LgV2, u2_Value),
    31, 1, 2, 6, "", 0 },

  { 4, "lgv2/HMI/Accuracy control/Accuracy u_2/Gain", offsetof(Parameters_LgV2,
    Accuracyu_2_Gain), 31, 1, 2, 8, "", 0 },

  { 5, "lgv2/HMI/Accuracy control/u3/Value", offsetof(Parameters_LgV2, u3_Value),
    31, 1, 2, 10, "", 0 },

  { 6, "lgv2/HMI/Accuracy control/Accuracy u_3/Gain", offsetof(Parameters_LgV2,
    Accuracyu_3_Gain), 31, 1, 2, 12, "", 0 },

  { 7, "lgv2/HMI/Accuracy control/u4/Value", offsetof(Parameters_LgV2, u4_Value),
    31, 1, 2, 14, "", 0 },

  { 8, "lgv2/HMI/Accuracy control/Accuracy u_4/Gain", offsetof(Parameters_LgV2,
    Accuracyu_4_Gain), 31, 1, 2, 16, "", 0 },

  { 9, "lgv2/HMI/Accuracy control/u5/Value", offsetof(Parameters_LgV2, u5_Value),
    31, 1, 2, 18, "", 0 },

  { 10, "lgv2/HMI/Accuracy control/Accuracy u_5/Gain", offsetof(Parameters_LgV2,
    Accuracyu_5_Gain), 31, 1, 2, 20, "", 0 },

  { 11, "lgv2/HMI/Accuracy control/Accuracy  BT power/Value", offsetof
    (Parameters_LgV2, AccuracyBTpower_Value), 31, 1, 2, 22, "", 0 },

  { 12, "lgv2/HMI/Accuracy control/Accuracy  VSP speed/Value", offsetof
    (Parameters_LgV2, AccuracyVSPspeed_Value), 31, 1, 2, 24, "", 0 },

  { 13, "lgv2/HMI/PS3 input/PS3 signals/JS_L_Y/Value", offsetof(Parameters_LgV2,
    JS_L_Y_Value), 31, 1, 2, 26, "", 0 },

  { 14, "lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_L_Y/Gain", offsetof
    (Parameters_LgV2, Scaling_JS_L_Y_Gain), 31, 1, 2, 28, "", 0 },

  { 15, "lgv2/Control Systems/Manual Thrust control/PS3 u_1/Gain", offsetof
    (Parameters_LgV2, PS3u_1_Gain), 31, 1, 2, 30, "", 0 },

  { 16, "lgv2/HMI/PS3 input/PS3 signals/JS_L_X/Value", offsetof(Parameters_LgV2,
    JS_L_X_Value), 31, 1, 2, 32, "", 0 },

  { 17, "lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_L_X/Gain", offsetof
    (Parameters_LgV2, Scaling_JS_L_X_Gain), 31, 1, 2, 34, "", 0 },

  { 18, "lgv2/Control Systems/Manual Thrust control/PS3 u_2/Gain", offsetof
    (Parameters_LgV2, PS3u_2_Gain), 31, 1, 2, 36, "", 0 },

  { 19, "lgv2/HMI/PS3 input/PS3 signals/JS_R_Y/Value", offsetof(Parameters_LgV2,
    JS_R_Y_Value), 31, 1, 2, 38, "", 0 },

  { 20, "lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_R_Y/Gain", offsetof
    (Parameters_LgV2, Scaling_JS_R_Y_Gain), 31, 1, 2, 40, "", 0 },

  { 21, "lgv2/Control Systems/Manual Thrust control/PS3 u_3/Gain", offsetof
    (Parameters_LgV2, PS3u_3_Gain), 31, 1, 2, 42, "", 0 },

  { 22, "lgv2/HMI/PS3 input/PS3 signals/JS_R_X/Value", offsetof(Parameters_LgV2,
    JS_R_X_Value), 31, 1, 2, 44, "", 0 },

  { 23, "lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_R_X/Gain", offsetof
    (Parameters_LgV2, Scaling_JS_R_X_Gain), 31, 1, 2, 46, "", 0 },

  { 24, "lgv2/Control Systems/Manual Thrust control/PS3 u_4/Gain", offsetof
    (Parameters_LgV2, PS3u_4_Gain), 31, 1, 2, 48, "", 0 },

  { 25, "lgv2/HMI/PS3 input/PS3 signals/L2/Value", offsetof(Parameters_LgV2,
    L2_Value), 31, 1, 2, 50, "", 0 },

  { 26, "lgv2/HMI/PS3 input/PS3 signals/R2/Value", offsetof(Parameters_LgV2,
    R2_Value), 31, 1, 2, 52, "", 0 },

  { 27, "lgv2/Control Systems/Manual Thrust control/PS3 u_5/Gain", offsetof
    (Parameters_LgV2, PS3u_5_Gain), 31, 1, 2, 54, "", 0 },

  { 28, "lgv2/HMI/PS3 input/PS3_BT_Power/Value", offsetof(Parameters_LgV2,
    PS3_BT_Power_Value), 31, 1, 2, 56, "", 0 },

  { 29, "lgv2/HMI/PS3 input/PS3_VSP_Speed/Value", offsetof(Parameters_LgV2,
    PS3_VSP_Speed_Value), 31, 1, 2, 58, "", 0 },

  { 30, "lgv2/Control Systems/Joystick Control/K_e/K_e1_joystick/Value",
    offsetof(Parameters_LgV2, K_e1_joystick_Value), 31, 1, 2, 60, "", 0 },

  { 31, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e1_joystick/Gain",
    offsetof(Parameters_LgV2, GainK_e1_joystick_Gain), 31, 1, 2, 62, "", 0 },

  { 32, "lgv2/Control Systems/Joystick Control/K_e/Constant/Value", offsetof
    (Parameters_LgV2, Constant_Value), 31, 1, 2, 64, "", 0 },

  { 33, "lgv2/Control Systems/Joystick Control/K_e/K_e2_joystick/Value",
    offsetof(Parameters_LgV2, K_e2_joystick_Value), 31, 1, 2, 66, "", 0 },

  { 34, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e2_joystick/Gain",
    offsetof(Parameters_LgV2, GainK_e2_joystick_Gain), 31, 1, 2, 68, "", 0 },

  { 35, "lgv2/Control Systems/Joystick Control/K_e/K_e3_joystick/Value",
    offsetof(Parameters_LgV2, K_e3_joystick_Value), 31, 1, 2, 70, "", 0 },

  { 36, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e3_joystick/Gain",
    offsetof(Parameters_LgV2, GainK_e3_joystick_Gain), 31, 1, 2, 72, "", 0 },

  { 37, "lgv2/Control Systems/Joystick Control/K_e/K_e4_joystick/Value",
    offsetof(Parameters_LgV2, K_e4_joystick_Value), 31, 1, 2, 74, "", 0 },

  { 38, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e4_joystick/Gain",
    offsetof(Parameters_LgV2, GainK_e4_joystick_Gain), 31, 1, 2, 76, "", 0 },

  { 39, "lgv2/Control Systems/Joystick Control/K_e/K_e5_joystick/Value",
    offsetof(Parameters_LgV2, K_e5_joystick_Value), 31, 1, 2, 78, "", 0 },

  { 40, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e5_joystick/Gain",
    offsetof(Parameters_LgV2, GainK_e5_joystick_Gain), 31, 1, 2, 80, "", 0 },

  { 41, "lgv2/Control Systems/Joystick Control/T_e/T_e11/Value", offsetof
    (Parameters_LgV2, T_e11_Value), 31, 1, 2, 82, "", 0 },

  { 42, "lgv2/Control Systems/Joystick Control/T_e/T_e21/Value", offsetof
    (Parameters_LgV2, T_e21_Value), 31, 1, 2, 84, "", 0 },

  { 43, "lgv2/Control Systems/Joystick Control/T_e/l_y1/Value", offsetof
    (Parameters_LgV2, l_y1_Value), 31, 1, 2, 86, "", 0 },

  { 44, "lgv2/Control Systems/Joystick Control/T_e/T_e12/Value", offsetof
    (Parameters_LgV2, T_e12_Value), 31, 1, 2, 88, "", 0 },

  { 45, "lgv2/Control Systems/Joystick Control/T_e/T_e22/Value", offsetof
    (Parameters_LgV2, T_e22_Value), 31, 1, 2, 90, "", 0 },

  { 46, "lgv2/Control Systems/Joystick Control/T_e/l_x1/Value", offsetof
    (Parameters_LgV2, l_x1_Value), 31, 1, 2, 92, "", 0 },

  { 47, "lgv2/Control Systems/Joystick Control/T_e/-l_x1/Gain", offsetof
    (Parameters_LgV2, l_x1_Gain), 31, 1, 2, 94, "", 0 },

  { 48, "lgv2/Control Systems/Joystick Control/T_e/T_e13/Value", offsetof
    (Parameters_LgV2, T_e13_Value), 31, 1, 2, 96, "", 0 },

  { 49, "lgv2/Control Systems/Joystick Control/T_e/T_e23/Value", offsetof
    (Parameters_LgV2, T_e23_Value), 31, 1, 2, 98, "", 0 },

  { 50, "lgv2/Control Systems/Joystick Control/T_e/l_y2/Value", offsetof
    (Parameters_LgV2, l_y2_Value), 31, 1, 2, 100, "", 0 },

  { 51, "lgv2/Control Systems/Joystick Control/T_e/-l_y2/Gain", offsetof
    (Parameters_LgV2, l_y2_Gain), 31, 1, 2, 102, "", 0 },

  { 52, "lgv2/Control Systems/Joystick Control/T_e/T_e14/Value", offsetof
    (Parameters_LgV2, T_e14_Value), 31, 1, 2, 104, "", 0 },

  { 53, "lgv2/Control Systems/Joystick Control/T_e/T_e24/Value", offsetof
    (Parameters_LgV2, T_e24_Value), 31, 1, 2, 106, "", 0 },

  { 54, "lgv2/Control Systems/Joystick Control/T_e/l_x2/Value", offsetof
    (Parameters_LgV2, l_x2_Value), 31, 1, 2, 108, "", 0 },

  { 55, "lgv2/Control Systems/Joystick Control/T_e/-l_x2/Gain", offsetof
    (Parameters_LgV2, l_x2_Gain), 31, 1, 2, 110, "", 0 },

  { 56, "lgv2/Control Systems/Joystick Control/T_e/T_e15/Value", offsetof
    (Parameters_LgV2, T_e15_Value), 31, 1, 2, 112, "", 0 },

  { 57, "lgv2/Control Systems/Joystick Control/T_e/T_e25/Value", offsetof
    (Parameters_LgV2, T_e25_Value), 31, 1, 2, 114, "", 0 },

  { 58, "lgv2/Control Systems/Joystick Control/T_e/l_x3/Value", offsetof
    (Parameters_LgV2, l_x3_Value), 31, 1, 2, 116, "", 0 },

  { 59, "lgv2/Control Systems/Joystick Control/Joystick tau_surge/Gain",
    offsetof(Parameters_LgV2, Joysticktau_surge_Gain), 31, 1, 2, 118, "", 0 },

  { 60, "lgv2/Control Systems/Joystick Control/Saturation1/UpperLimit", offsetof
    (Parameters_LgV2, Saturation1_UpperSat), 31, 1, 2, 120, "", 0 },

  { 61, "lgv2/Control Systems/Joystick Control/Saturation1/LowerLimit", offsetof
    (Parameters_LgV2, Saturation1_LowerSat), 31, 1, 2, 122, "", 0 },

  { 62, "lgv2/Control Systems/Joystick Control/Joystick tau_sway/Gain", offsetof
    (Parameters_LgV2, Joysticktau_sway_Gain), 31, 1, 2, 124, "", 0 },

  { 63, "lgv2/Control Systems/Joystick Control/Saturation2/UpperLimit", offsetof
    (Parameters_LgV2, Saturation2_UpperSat), 31, 1, 2, 126, "", 0 },

  { 64, "lgv2/Control Systems/Joystick Control/Saturation2/LowerLimit", offsetof
    (Parameters_LgV2, Saturation2_LowerSat), 31, 1, 2, 128, "", 0 },

  { 65, "lgv2/Control Systems/Joystick Control/Joystick tau_yaw/Gain", offsetof
    (Parameters_LgV2, Joysticktau_yaw_Gain), 31, 1, 2, 130, "", 0 },

  { 66, "lgv2/Control Systems/Joystick Control/Saturation3/UpperLimit", offsetof
    (Parameters_LgV2, Saturation3_UpperSat), 31, 1, 2, 132, "", 0 },

  { 67, "lgv2/Control Systems/Joystick Control/Saturation3/LowerLimit", offsetof
    (Parameters_LgV2, Saturation3_LowerSat), 31, 1, 2, 134, "", 0 },

  { 68, "lgv2/Control Systems/Joystick Control/Saturation/UpperLimit", offsetof
    (Parameters_LgV2, Saturation_UpperSat), 31, 1, 2, 136, "", 0 },

  { 69, "lgv2/Control Systems/Joystick Control/Saturation/LowerLimit", offsetof
    (Parameters_LgV2, Saturation_LowerSat), 31, 1, 2, 138, "", 0 },

  { 70, "lgv2/Control Systems/Joystick Control/Joystick u_1/Gain", offsetof
    (Parameters_LgV2, Joysticku_1_Gain), 31, 1, 2, 140, "", 0 },

  { 71, "lgv2/Control Systems/Joystick Control/Joystick u_2/Gain", offsetof
    (Parameters_LgV2, Joysticku_2_Gain), 31, 1, 2, 142, "", 0 },

  { 72, "lgv2/Control Systems/Joystick Control/Joystick u_3/Gain", offsetof
    (Parameters_LgV2, Joysticku_3_Gain), 31, 1, 2, 144, "", 0 },

  { 73, "lgv2/Control Systems/Joystick Control/Joystick u_4/Gain", offsetof
    (Parameters_LgV2, Joysticku_4_Gain), 31, 1, 2, 146, "", 0 },

  { 74, "lgv2/Control Systems/Joystick Control/Joystick u_5/Gain", offsetof
    (Parameters_LgV2, Joysticku_5_Gain), 31, 1, 2, 148, "", 0 },

  { 75, "lgv2/Guidance Systems/DP/Enable eta_d LPF/Value", offsetof
    (Parameters_LgV2, Enableeta_dLPF_Value), 31, 1, 2, 150, "", 0 },

  { 76, "lgv2/HMI/DP input/x_d/Value", offsetof(Parameters_LgV2, x_d_Value), 31,
    1, 2, 152, "", 0 },

  { 77, "lgv2/HMI/DP input/y_d/Value", offsetof(Parameters_LgV2, y_d_Value), 31,
    1, 2, 154, "", 0 },

  { 78, "lgv2/HMI/DP input/psi_d/Value", offsetof(Parameters_LgV2, psi_d_Value),
    31, 1, 2, 156, "", 0 },

  { 79, "lgv2/HMI/DP input/Degrees to Radians/Gain1/Gain", offsetof
    (Parameters_LgV2, Gain1_Gain), 31, 1, 2, 158, "", 0 },

  { 80, "lgv2/Guidance Systems/DP/Transfer Fcn/A", offsetof(Parameters_LgV2,
    TransferFcn_A), 31, 1, 2, 160, "", 0 },

  { 81, "lgv2/Guidance Systems/DP/Transfer Fcn/C", offsetof(Parameters_LgV2,
    TransferFcn_C), 31, 1, 2, 162, "", 0 },

  { 82, "lgv2/Guidance Systems/DP/Transfer Fcn1/A", offsetof(Parameters_LgV2,
    TransferFcn1_A), 31, 1, 2, 164, "", 0 },

  { 83, "lgv2/Guidance Systems/DP/Transfer Fcn1/C", offsetof(Parameters_LgV2,
    TransferFcn1_C), 31, 1, 2, 166, "", 0 },

  { 84, "lgv2/Guidance Systems/DP/Transfer Fcn2/A", offsetof(Parameters_LgV2,
    TransferFcn2_A), 31, 1, 2, 168, "", 0 },

  { 85, "lgv2/Guidance Systems/DP/Transfer Fcn2/C", offsetof(Parameters_LgV2,
    TransferFcn2_C), 31, 1, 2, 170, "", 0 },

  { 86, "lgv2/Guidance Systems/DP/eta_d DP N/Gain", offsetof(Parameters_LgV2,
    eta_dDPN_Gain), 31, 1, 2, 172, "", 0 },

  { 87, "lgv2/Guidance Systems/DP/eta_d DP E/Gain", offsetof(Parameters_LgV2,
    eta_dDPE_Gain), 31, 1, 2, 174, "", 0 },

  { 88, "lgv2/Guidance Systems/DP/eta_d DP Psi/Gain", offsetof(Parameters_LgV2,
    eta_dDPPsi_Gain), 31, 1, 2, 176, "", 0 },

  { 89, "lgv2/Naviagation Systems/Controller Input Selector/Value", offsetof
    (Parameters_LgV2, ControllerInputSelector_Value), 31, 1, 2, 178, "", 0 },

  { 90, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain", offsetof
    (Parameters_LgV2, QTMIn3_Gain), 31, 1, 2, 180, "", 0 },

  { 91, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain", offsetof
    (Parameters_LgV2, mm2mx_Gain), 31, 1, 2, 182, "", 0 },

  { 92, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain", offsetof
    (Parameters_LgV2, QTMIn4_Gain), 31, 1, 2, 184, "", 0 },

  { 93, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain", offsetof
    (Parameters_LgV2, mm2my_Gain), 31, 1, 2, 186, "", 0 },

  { 94, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain", offsetof
    (Parameters_LgV2, QTMIn6_Gain), 31, 1, 2, 188, "", 0 },

  { 95, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain", offsetof
    (Parameters_LgV2, d2ryaw_Gain), 31, 1, 2, 190, "", 0 },

  { 96, "lgv2/Plants/Enable Linear Simulator/Value", offsetof(Parameters_LgV2,
    EnableLinearSimulator_Value), 31, 1, 2, 192, "", 0 },

  { 97, "lgv2/Naviagation Systems/eta_surge/Gain", offsetof(Parameters_LgV2,
    eta_surge_Gain), 31, 1, 2, 194, "", 0 },

  { 98, "lgv2/Naviagation Systems/eta_sway/Gain", offsetof(Parameters_LgV2,
    eta_sway_Gain), 31, 1, 2, 196, "", 0 },

  { 99, "lgv2/Naviagation Systems/eta_yaw/Gain", offsetof(Parameters_LgV2,
    eta_yaw_Gain), 31, 1, 2, 198, "", 0 },

  { 100, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain", offsetof
    (Parameters_LgV2, QTMIn8_Gain), 31, 1, 2, 200, "", 0 },

  { 101, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain", offsetof
    (Parameters_LgV2, d2rroll_Gain), 31, 1, 2, 202, "", 0 },

  { 102, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain", offsetof
    (Parameters_LgV2, QTMIn7_Gain), 31, 1, 2, 204, "", 0 },

  { 103, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain", offsetof
    (Parameters_LgV2, d2rpitch_Gain), 31, 1, 2, 206, "", 0 },

  { 104, "lgv2/Naviagation Systems/Qualisys 6 DOF/Constant1/Value", offsetof
    (Parameters_LgV2, Constant1_Value), 33, 9, 2, 208, "", 0 },

  { 105, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain", offsetof
    (Parameters_LgV2, QTMIn5_Gain), 31, 1, 2, 210, "", 0 },

  { 106, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain", offsetof
    (Parameters_LgV2, mm2mz_Gain), 31, 1, 2, 212, "", 0 },

  { 107, "lgv2/Naviagation Systems/nu_surge/Gain", offsetof(Parameters_LgV2,
    nu_surge_Gain), 31, 1, 2, 214, "", 0 },

  { 108, "lgv2/Naviagation Systems/nu_sway/Gain", offsetof(Parameters_LgV2,
    nu_sway_Gain), 31, 1, 2, 216, "", 0 },

  { 109, "lgv2/Naviagation Systems/nu_yaw/Gain", offsetof(Parameters_LgV2,
    nu_yaw_Gain), 31, 1, 2, 218, "", 0 },

  { 110, "lgv2/Control Systems/if DP Control Mode/Constant/Value", offsetof
    (Parameters_LgV2, Constant_Value_j), 31, 1, 2, 220, "", 0 },

  { 111, "lgv2/Control Systems/Saturation/UpperLimit", offsetof(Parameters_LgV2,
    Saturation_UpperSat_p), 31, 1, 2, 222, "", 0 },

  { 112, "lgv2/Control Systems/Saturation/LowerLimit", offsetof(Parameters_LgV2,
    Saturation_LowerSat_g), 31, 1, 2, 224, "", 0 },

  { 113, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain", offsetof
    (Parameters_LgV2, QTMIn2Error_Gain), 31, 1, 2, 226, "", 0 },

  { 114, "lgv2/Guidance Systems/DP/eta_d Psi deg/Gain", offsetof(Parameters_LgV2,
    eta_dPsideg_Gain), 31, 1, 2, 228, "", 0 },

  { 115, "lgv2/Guidance Systems/psi_d/Gain", offsetof(Parameters_LgV2,
    psi_d_Gain), 31, 1, 2, 230, "", 0 },

  { 116, "lgv2/Guidance Systems/x_d/Gain", offsetof(Parameters_LgV2, x_d_Gain),
    31, 1, 2, 232, "", 0 },

  { 117, "lgv2/Guidance Systems/y_d/Gain", offsetof(Parameters_LgV2, y_d_Gain),
    31, 1, 2, 234, "", 0 },

  { 118, "lgv2/HMI/Battery Bow Thruster/Gain", offsetof(Parameters_LgV2,
    BatteryBowThruster_Gain), 31, 1, 2, 236, "", 0 },

  { 119, "lgv2/HMI/Battery Servo/Gain", offsetof(Parameters_LgV2,
    BatteryServo_Gain), 31, 1, 2, 238, "", 0 },

  { 120, "lgv2/HMI/Battery Main/Gain", offsetof(Parameters_LgV2,
    BatteryMain_Gain), 31, 1, 2, 240, "", 0 },

  { 121, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain", offsetof
    (Parameters_LgV2, QTMIn1FPS_Gain), 31, 1, 2, 242, "", 0 },

  { 122, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain",
    offsetof(Parameters_LgV2, QTMIn9Residual_Gain), 31, 1, 2, 244, "", 0 },

  { 123, "lgv2/Plants/u_1 plant/Gain", offsetof(Parameters_LgV2, u_1plant_Gain),
    31, 1, 2, 246, "", 0 },

  { 124, "lgv2/Plants/u_2 plant/Gain", offsetof(Parameters_LgV2, u_2plant_Gain),
    31, 1, 2, 248, "", 0 },

  { 125, "lgv2/Plants/u_3 plant/Gain", offsetof(Parameters_LgV2, u_3plant_Gain),
    31, 1, 2, 250, "", 0 },

  { 126, "lgv2/Plants/u_4 plant/Gain", offsetof(Parameters_LgV2, u_4plant_Gain),
    31, 1, 2, 252, "", 0 },

  { 127, "lgv2/Plants/u_5 plant/Gain", offsetof(Parameters_LgV2, u_5plant_Gain),
    31, 1, 2, 254, "", 0 },

  { 128, "lgv2/Plants/BT power limit plant/Gain", offsetof(Parameters_LgV2,
    BTpowerlimitplant_Gain), 31, 1, 2, 256, "", 0 },

  { 129, "lgv2/Plants/VSP speed plant/Gain", offsetof(Parameters_LgV2,
    VSPspeedplant_Gain), 31, 1, 2, 258, "", 0 },

  { 130, "lgv2/Plants/Enable CSE1/Value", offsetof(Parameters_LgV2,
    EnableCSE1_Value), 31, 1, 2, 260, "", 0 },

  { 131, "lgv2/Control Systems/DP control/Thruster_Command_DP/InitialOutput",
    offsetof(Parameters_LgV2, Thruster_Command_DP_Y0), 52, 7, 2, 262, "", 0 },

  { 132,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator1/InitialCondition",
    offsetof(Parameters_LgV2, Integrator1_IC), 31, 1, 2, 264, "", 0 },

  { 133, "lgv2/Control Systems/DP control/BT_power_limit/Value", offsetof
    (Parameters_LgV2, BT_power_limit_Value), 31, 1, 2, 266, "", 0 },

  { 134, "lgv2/Control Systems/DP control/Enable Filter/Value", offsetof
    (Parameters_LgV2, EnableFilter_Value), 31, 1, 2, 268, "", 0 },

  { 135,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator/InitialCondition",
    offsetof(Parameters_LgV2, Integrator_IC), 31, 1, 2, 270, "", 0 },

  { 136,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_d), 31, 1, 2, 272, "", 0 },

  { 137,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_b), 31, 1, 2, 274, "", 0 },

  { 138,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain), 31, 1, 2, 276, "", 0 },

  { 139,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_jr), 31, 1, 2, 278, "", 0 },

  { 140, "lgv2/Control Systems/DP control/DP controller/eta N/Gain", offsetof
    (Parameters_LgV2, etaN_Gain), 31, 1, 2, 280, "", 0 },

  { 141, "lgv2/Control Systems/DP control/DP controller/eta E/Gain", offsetof
    (Parameters_LgV2, etaE_Gain), 31, 1, 2, 282, "", 0 },

  { 142, "lgv2/Control Systems/DP control/DP controller/eta Psi/Gain", offsetof
    (Parameters_LgV2, etaPsi_Gain), 31, 1, 2, 284, "", 0 },

  { 143, "lgv2/Control Systems/DP control/DP controller/Reg_e_N_hil/Gain",
    offsetof(Parameters_LgV2, Reg_e_N_hil_Gain), 31, 1, 2, 286, "", 0 },

  { 144, "lgv2/Control Systems/DP control/DP controller/Reg_e_E_hil/Gain",
    offsetof(Parameters_LgV2, Reg_e_E_hil_Gain), 31, 1, 2, 288, "", 0 },

  { 145, "lgv2/Control Systems/DP control/DP controller/Reg_e_Psi_hil/Gain",
    offsetof(Parameters_LgV2, Reg_e_Psi_hil_Gain), 31, 1, 2, 290, "", 0 },

  { 146,
    "lgv2/Control Systems/DP control/DP controller/Reset_DP_integrator/Value",
    offsetof(Parameters_LgV2, Reset_DP_integrator_Value), 31, 1, 2, 292, "", 0 },

  { 147,
    "lgv2/Control Systems/DP control/DP controller/Integrator/InitialCondition",
    offsetof(Parameters_LgV2, Integrator_IC_f), 31, 1, 2, 294, "", 0 },

  { 148,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator4/InitialCondition",
    offsetof(Parameters_LgV2, Integrator4_IC), 31, 1, 2, 296, "", 0 },

  { 149, "lgv2/Control Systems/DP control/DP controller/Kd/Gain", offsetof
    (Parameters_LgV2, Kd_Gain), 33, 9, 2, 298, "", 0 },

  { 150, "lgv2/Control Systems/DP control/DP controller/Kd_scale/Value",
    offsetof(Parameters_LgV2, Kd_scale_Value), 31, 1, 2, 300, "", 0 },

  { 151, "lgv2/Control Systems/DP control/DP controller/K_d 1/Gain", offsetof
    (Parameters_LgV2, K_d1_Gain), 31, 1, 2, 302, "", 0 },

  { 152, "lgv2/Control Systems/DP control/DP controller/K_d 2/Gain", offsetof
    (Parameters_LgV2, K_d2_Gain), 31, 1, 2, 304, "", 0 },

  { 153, "lgv2/Control Systems/DP control/DP controller/K_d 3/Gain", offsetof
    (Parameters_LgV2, K_d3_Gain), 31, 1, 2, 306, "", 0 },

  { 154, "lgv2/Control Systems/DP control/DP controller/K_d 3 deg/Gain",
    offsetof(Parameters_LgV2, K_d3deg_Gain), 31, 1, 2, 308, "", 0 },

  { 155, "lgv2/Control Systems/DP control/DP controller/Ki/Gain", offsetof
    (Parameters_LgV2, Ki_Gain), 33, 9, 2, 310, "", 0 },

  { 156, "lgv2/Control Systems/DP control/DP controller/Ki_scale/Value",
    offsetof(Parameters_LgV2, Ki_scale_Value), 31, 1, 2, 312, "", 0 },

  { 157, "lgv2/Control Systems/DP control/DP controller/K_i 1/Gain", offsetof
    (Parameters_LgV2, K_i1_Gain), 31, 1, 2, 314, "", 0 },

  { 158, "lgv2/Control Systems/DP control/DP controller/K_i 2/Gain", offsetof
    (Parameters_LgV2, K_i2_Gain), 31, 1, 2, 316, "", 0 },

  { 159, "lgv2/Control Systems/DP control/DP controller/K_i 3/Gain", offsetof
    (Parameters_LgV2, K_i3_Gain), 31, 1, 2, 318, "", 0 },

  { 160, "lgv2/Control Systems/DP control/DP controller/K_i 3 deg/Gain",
    offsetof(Parameters_LgV2, K_i3deg_Gain), 31, 1, 2, 320, "", 0 },

  { 161, "lgv2/Control Systems/DP control/DP controller/Kp_scale/Value",
    offsetof(Parameters_LgV2, Kp_scale_Value), 31, 1, 2, 322, "", 0 },

  { 162,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_j), 31, 1, 2, 324, "", 0 },

  { 163,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_j), 31, 1, 2, 326, "", 0 },

  { 164,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_h), 31, 1, 2, 328, "", 0 },

  { 165,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_g), 31, 1, 2, 330, "", 0 },

  { 166,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_g), 31, 1, 2, 332, "", 0 },

  { 167,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_m), 31, 1, 2, 334, "", 0 },

  { 168,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_f), 31, 1, 2, 336, "", 0 },

  { 169,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_gt), 31, 1, 2, 338, "", 0 },

  { 170, "lgv2/Control Systems/DP control/DP controller/Kp/Gain", offsetof
    (Parameters_LgV2, Kp_Gain), 33, 9, 2, 340, "", 0 },

  { 171, "lgv2/Control Systems/DP control/DP controller/K_p 1/Gain", offsetof
    (Parameters_LgV2, K_p1_Gain), 31, 1, 2, 342, "", 0 },

  { 172, "lgv2/Control Systems/DP control/DP controller/K_p 2/Gain", offsetof
    (Parameters_LgV2, K_p2_Gain), 31, 1, 2, 344, "", 0 },

  { 173, "lgv2/Control Systems/DP control/DP controller/K_p 3/Gain", offsetof
    (Parameters_LgV2, K_p3_Gain), 31, 1, 2, 346, "", 0 },

  { 174, "lgv2/Control Systems/DP control/DP controller/K_p 3 deg/Gain",
    offsetof(Parameters_LgV2, K_p3deg_Gain), 31, 1, 2, 348, "", 0 },

  { 175, "lgv2/Control Systems/DP control/DP controller/Reg_e_Psi_deg/Gain",
    offsetof(Parameters_LgV2, Reg_e_Psi_deg_Gain), 31, 1, 2, 350, "", 0 },

  { 176, "lgv2/Control Systems/DP control/DP controller/eta Psi deg/Gain",
    offsetof(Parameters_LgV2, etaPsideg_Gain), 31, 1, 2, 352, "", 0 },

  { 177, "lgv2/Control Systems/DP control/DP tau_surge/Gain", offsetof
    (Parameters_LgV2, DPtau_surge_Gain), 31, 1, 2, 354, "", 0 },

  { 178, "lgv2/Control Systems/DP control/DP tau_sway/Gain", offsetof
    (Parameters_LgV2, DPtau_sway_Gain), 31, 1, 2, 356, "", 0 },

  { 179, "lgv2/Control Systems/DP control/DP tau_yaw/Gain", offsetof
    (Parameters_LgV2, DPtau_yaw_Gain), 31, 1, 2, 358, "", 0 },

  { 180, "lgv2/Control Systems/DP control/K_e/K_e1_DP/Value", offsetof
    (Parameters_LgV2, K_e1_DP_Value), 31, 1, 2, 360, "", 0 },

  { 181, "lgv2/Control Systems/DP control/K_e/Gain K_e1_DP/Gain", offsetof
    (Parameters_LgV2, GainK_e1_DP_Gain), 31, 1, 2, 362, "", 0 },

  { 182, "lgv2/Control Systems/DP control/K_e/Constant/Value", offsetof
    (Parameters_LgV2, Constant_Value_c), 31, 1, 2, 364, "", 0 },

  { 183, "lgv2/Control Systems/DP control/K_e/K_e2_DP/Value", offsetof
    (Parameters_LgV2, K_e2_DP_Value), 31, 1, 2, 366, "", 0 },

  { 184, "lgv2/Control Systems/DP control/K_e/Gain K_e2_DP/Gain", offsetof
    (Parameters_LgV2, GainK_e2_DP_Gain), 31, 1, 2, 368, "", 0 },

  { 185, "lgv2/Control Systems/DP control/K_e/K_e3_DP/Value", offsetof
    (Parameters_LgV2, K_e3_DP_Value), 31, 1, 2, 370, "", 0 },

  { 186, "lgv2/Control Systems/DP control/K_e/Gain K_e3_DP/Gain", offsetof
    (Parameters_LgV2, GainK_e3_DP_Gain), 31, 1, 2, 372, "", 0 },

  { 187, "lgv2/Control Systems/DP control/K_e/K_e4_DP/Value", offsetof
    (Parameters_LgV2, K_e4_DP_Value), 31, 1, 2, 374, "", 0 },

  { 188, "lgv2/Control Systems/DP control/K_e/Gain K_e4_DP/Gain", offsetof
    (Parameters_LgV2, GainK_e4_DP_Gain), 31, 1, 2, 376, "", 0 },

  { 189, "lgv2/Control Systems/DP control/K_e/K_e5_DP/Value", offsetof
    (Parameters_LgV2, K_e5_DP_Value), 31, 1, 2, 378, "", 0 },

  { 190, "lgv2/Control Systems/DP control/K_e/Gain K_e5_DP/Gain", offsetof
    (Parameters_LgV2, GainK_e5_DP_Gain), 31, 1, 2, 380, "", 0 },

  { 191, "lgv2/Control Systems/DP control/T_e/T_e11/Value", offsetof
    (Parameters_LgV2, T_e11_Value_o), 31, 1, 2, 382, "", 0 },

  { 192, "lgv2/Control Systems/DP control/T_e/T_e21/Value", offsetof
    (Parameters_LgV2, T_e21_Value_d), 31, 1, 2, 384, "", 0 },

  { 193, "lgv2/Control Systems/DP control/T_e/l_y1/Value", offsetof
    (Parameters_LgV2, l_y1_Value_p), 31, 1, 2, 386, "", 0 },

  { 194, "lgv2/Control Systems/DP control/T_e/T_e12/Value", offsetof
    (Parameters_LgV2, T_e12_Value_i), 31, 1, 2, 388, "", 0 },

  { 195, "lgv2/Control Systems/DP control/T_e/T_e22/Value", offsetof
    (Parameters_LgV2, T_e22_Value_o), 31, 1, 2, 390, "", 0 },

  { 196, "lgv2/Control Systems/DP control/T_e/l_x1/Value", offsetof
    (Parameters_LgV2, l_x1_Value_e), 31, 1, 2, 392, "", 0 },

  { 197, "lgv2/Control Systems/DP control/T_e/-l_x1/Gain", offsetof
    (Parameters_LgV2, l_x1_Gain_j), 31, 1, 2, 394, "", 0 },

  { 198, "lgv2/Control Systems/DP control/T_e/T_e13/Value", offsetof
    (Parameters_LgV2, T_e13_Value_g), 31, 1, 2, 396, "", 0 },

  { 199, "lgv2/Control Systems/DP control/T_e/T_e23/Value", offsetof
    (Parameters_LgV2, T_e23_Value_o), 31, 1, 2, 398, "", 0 },

  { 200, "lgv2/Control Systems/DP control/T_e/l_y2/Value", offsetof
    (Parameters_LgV2, l_y2_Value_e), 31, 1, 2, 400, "", 0 },

  { 201, "lgv2/Control Systems/DP control/T_e/-l_y2/Gain", offsetof
    (Parameters_LgV2, l_y2_Gain_l), 31, 1, 2, 402, "", 0 },

  { 202, "lgv2/Control Systems/DP control/T_e/T_e14/Value", offsetof
    (Parameters_LgV2, T_e14_Value_e), 31, 1, 2, 404, "", 0 },

  { 203, "lgv2/Control Systems/DP control/T_e/T_e24/Value", offsetof
    (Parameters_LgV2, T_e24_Value_c), 31, 1, 2, 406, "", 0 },

  { 204, "lgv2/Control Systems/DP control/T_e/l_x2/Value", offsetof
    (Parameters_LgV2, l_x2_Value_d), 31, 1, 2, 408, "", 0 },

  { 205, "lgv2/Control Systems/DP control/T_e/-l_x2/Gain", offsetof
    (Parameters_LgV2, l_x2_Gain_b), 31, 1, 2, 410, "", 0 },

  { 206, "lgv2/Control Systems/DP control/T_e/T_e15/Value", offsetof
    (Parameters_LgV2, T_e15_Value_h), 31, 1, 2, 412, "", 0 },

  { 207, "lgv2/Control Systems/DP control/T_e/T_e25/Value", offsetof
    (Parameters_LgV2, T_e25_Value_c), 31, 1, 2, 414, "", 0 },

  { 208, "lgv2/Control Systems/DP control/T_e/l_x3/Value", offsetof
    (Parameters_LgV2, l_x3_Value_d), 31, 1, 2, 416, "", 0 },

  { 209, "lgv2/Control Systems/DP control/DP u_1/Gain", offsetof(Parameters_LgV2,
    DPu_1_Gain), 31, 1, 2, 418, "", 0 },

  { 210, "lgv2/Control Systems/DP control/DP u_2/Gain", offsetof(Parameters_LgV2,
    DPu_2_Gain), 31, 1, 2, 420, "", 0 },

  { 211, "lgv2/Control Systems/DP control/DP u_3/Gain", offsetof(Parameters_LgV2,
    DPu_3_Gain), 31, 1, 2, 422, "", 0 },

  { 212, "lgv2/Control Systems/DP control/DP u_4/Gain", offsetof(Parameters_LgV2,
    DPu_4_Gain), 31, 1, 2, 424, "", 0 },

  { 213, "lgv2/Control Systems/DP control/DP u_5/Gain", offsetof(Parameters_LgV2,
    DPu_5_Gain), 31, 1, 2, 426, "", 0 },

  { 214, "lgv2/Control Systems/DP control/Passive DP wave filter1/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_b), 33, 9, 2, 428, "", 0 },

  { 215,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator2/InitialCondition",
    offsetof(Parameters_LgV2, Integrator2_IC), 31, 1, 2, 430, "", 0 },

  { 216, "lgv2/Control Systems/DP control/Passive DP wave filter1/Gain2/Gain",
    offsetof(Parameters_LgV2, Gain2_Gain), 33, 9, 2, 432, "", 0 },

  { 217,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_n), 31, 1, 2, 434, "", 0 },

  { 218,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_c), 31, 1, 2, 436, "", 0 },

  { 219,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_e), 31, 1, 2, 438, "", 0 },

  { 220,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_a), 31, 1, 2, 440, "", 0 },

  { 221, "lgv2/Control Systems/DP control/Passive DP wave filter1/K4/Gain",
    offsetof(Parameters_LgV2, K4_Gain), 33, 9, 2, 442, "", 0 },

  { 222,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator3/InitialCondition",
    offsetof(Parameters_LgV2, Integrator3_IC), 31, 1, 2, 444, "", 0 },

  { 223, "lgv2/Control Systems/DP control/Passive DP wave filter1/Gain6/Gain",
    offsetof(Parameters_LgV2, Gain6_Gain), 33, 9, 2, 446, "", 0 },

  { 224, "lgv2/Control Systems/DP control/Passive DP wave filter1/Gain3/Gain",
    offsetof(Parameters_LgV2, Gain3_Gain), 33, 9, 2, 448, "", 0 },

  { 225, "lgv2/Control Systems/DP control/Passive DP wave filter1/K11/Gain",
    offsetof(Parameters_LgV2, K11_Gain), 33, 9, 2, 450, "", 0 },

  { 226, "lgv2/Control Systems/DP control/Passive DP wave filter1/K12/Gain",
    offsetof(Parameters_LgV2, K12_Gain), 33, 9, 2, 452, "", 0 },

  { 227, "lgv2/Control Systems/DP control/Passive DP wave filter1/K2/Gain",
    offsetof(Parameters_LgV2, K2_Gain), 33, 9, 2, 454, "", 0 },

  { 228, "lgv2/Control Systems/DP control/Passive DP wave filter1/K3/Gain",
    offsetof(Parameters_LgV2, K3_Gain), 33, 9, 2, 456, "", 0 },

  { 229, "lgv2/Control Systems/DP control/Passive DP wave filter1/inv(T_b)/Gain",
    offsetof(Parameters_LgV2, invT_b_Gain), 33, 9, 2, 458, "", 0 },

  { 230, "lgv2/Control Systems/DP control/Saturation/UpperLimit", offsetof
    (Parameters_LgV2, Saturation_UpperSat_do), 31, 1, 2, 460, "", 0 },

  { 231, "lgv2/Control Systems/DP control/Saturation/LowerLimit", offsetof
    (Parameters_LgV2, Saturation_LowerSat_d), 31, 1, 2, 462, "", 0 },

  { 232, "lgv2/Control Systems/DP control/VSP_speeds/Value", offsetof
    (Parameters_LgV2, VSP_speeds_Value), 31, 1, 2, 464, "", 0 },

  { 233, "lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain", offsetof
    (Parameters_LgV2, BT_D_Gain1_Gain), 31, 1, 2, 466, "", 0 },

  { 234, "lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value", offsetof
    (Parameters_LgV2, BT_Power_Offset1_Value), 31, 1, 2, 468, "", 0 },

  { 235, "lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain", offsetof
    (Parameters_LgV2, BT_D_Gain2_Gain), 31, 1, 2, 470, "", 0 },

  { 236, "lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain", offsetof
    (Parameters_LgV2, BT_L_Gain1_Gain), 31, 1, 2, 472, "", 0 },

  { 237, "lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain", offsetof
    (Parameters_LgV2, BT_L_Gain2_Gain), 31, 1, 2, 474, "", 0 },

  { 238, "lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value", offsetof
    (Parameters_LgV2, BT_Power_Offset2_Value), 31, 1, 2, 476, "", 0 },

  { 239, "lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value", offsetof
    (Parameters_LgV2, BT_Power_Offset3_Value), 31, 1, 2, 478, "", 0 },

  { 240, "lgv2/Plants/CSE1/Bow Thruster/Constant/Value", offsetof
    (Parameters_LgV2, Constant_Value_i), 31, 1, 2, 480, "", 0 },

  { 241, "lgv2/Plants/CSE1/Bow Thruster/Constant1/Value", offsetof
    (Parameters_LgV2, Constant1_Value_j), 31, 1, 2, 482, "", 0 },

  { 242, "lgv2/Plants/CSE1/Bow Thruster/Neg/Gain", offsetof(Parameters_LgV2,
    Neg_Gain), 31, 1, 2, 484, "", 0 },

  { 243, "lgv2/Plants/CSE1/Voith Schneider Propeller /-x/Gain", offsetof
    (Parameters_LgV2, x_Gain), 31, 1, 2, 486, "", 0 },

  { 244, "lgv2/Plants/CSE1/Voith Schneider Propeller /-y/Gain", offsetof
    (Parameters_LgV2, y_Gain), 31, 1, 2, 488, "", 0 },

  { 245,
    "lgv2/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_l), 31, 1, 2, 490, "", 0 },

  { 246,
    "lgv2/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_o), 31, 1, 2, 492, "", 0 },

  { 247, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex", offsetof
    (Parameters_LgV2, Servo1_RowIdx), 53, 3, 2, 494, "", 0 },

  { 248, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_LgV2, Servo1_ColIdx), 53, 3, 2, 496, "", 0 },

  { 249, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/Table", offsetof
    (Parameters_LgV2, Servo1_Table), 33, 9, 2, 498, "", 0 },

  { 250, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex", offsetof
    (Parameters_LgV2, Servo2_RowIdx), 53, 3, 2, 500, "", 0 },

  { 251, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_LgV2, Servo2_ColIdx), 53, 3, 2, 502, "", 0 },

  { 252, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/Table", offsetof
    (Parameters_LgV2, Servo2_Table), 33, 9, 2, 504, "", 0 },

  { 253, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex", offsetof
    (Parameters_LgV2, Servo3_RowIdx), 53, 3, 2, 506, "", 0 },

  { 254, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_LgV2, Servo3_ColIdx), 53, 3, 2, 508, "", 0 },

  { 255, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/Table", offsetof
    (Parameters_LgV2, Servo3_Table), 33, 9, 2, 510, "", 0 },

  { 256, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex", offsetof
    (Parameters_LgV2, Servo4_RowIdx), 53, 3, 2, 512, "", 0 },

  { 257, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_LgV2, Servo4_ColIdx), 53, 3, 2, 514, "", 0 },

  { 258, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/Table", offsetof
    (Parameters_LgV2, Servo4_Table), 33, 9, 2, 516, "", 0 },

  { 259, "lgv2/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_LgV2, VPS_Speed_Gain_Gain), 31, 1, 2, 518, "", 0 },

  { 260, "lgv2/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_LgV2, VPS_Power_Offset_Value), 31, 1, 2, 520, "", 0 },

  { 261, "lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain", offsetof
    (Parameters_LgV2, VSPSPort_Gain), 31, 1, 2, 522, "", 0 },

  { 262, "lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_LgV2, VSPSStarboard_Gain), 31, 1, 2, 524, "", 0 },

  { 263, "lgv2/Plants/CSE1/T_e/T_e11/Value", offsetof(Parameters_LgV2,
    T_e11_Value_c), 31, 1, 2, 526, "", 0 },

  { 264, "lgv2/Plants/CSE1/T_e/T_e21/Value", offsetof(Parameters_LgV2,
    T_e21_Value_l), 31, 1, 2, 528, "", 0 },

  { 265, "lgv2/Plants/CSE1/T_e/l_y1/Value", offsetof(Parameters_LgV2,
    l_y1_Value_e), 31, 1, 2, 530, "", 0 },

  { 266, "lgv2/Plants/CSE1/T_e/T_e12/Value", offsetof(Parameters_LgV2,
    T_e12_Value_k), 31, 1, 2, 532, "", 0 },

  { 267, "lgv2/Plants/CSE1/T_e/T_e22/Value", offsetof(Parameters_LgV2,
    T_e22_Value_i), 31, 1, 2, 534, "", 0 },

  { 268, "lgv2/Plants/CSE1/T_e/l_x1/Value", offsetof(Parameters_LgV2,
    l_x1_Value_o), 31, 1, 2, 536, "", 0 },

  { 269, "lgv2/Plants/CSE1/T_e/-l_x1/Gain", offsetof(Parameters_LgV2,
    l_x1_Gain_jm), 31, 1, 2, 538, "", 0 },

  { 270, "lgv2/Plants/CSE1/T_e/T_e13/Value", offsetof(Parameters_LgV2,
    T_e13_Value_p), 31, 1, 2, 540, "", 0 },

  { 271, "lgv2/Plants/CSE1/T_e/T_e23/Value", offsetof(Parameters_LgV2,
    T_e23_Value_l), 31, 1, 2, 542, "", 0 },

  { 272, "lgv2/Plants/CSE1/T_e/l_y2/Value", offsetof(Parameters_LgV2,
    l_y2_Value_f), 31, 1, 2, 544, "", 0 },

  { 273, "lgv2/Plants/CSE1/T_e/-l_y2/Gain", offsetof(Parameters_LgV2,
    l_y2_Gain_f), 31, 1, 2, 546, "", 0 },

  { 274, "lgv2/Plants/CSE1/T_e/T_e14/Value", offsetof(Parameters_LgV2,
    T_e14_Value_b), 31, 1, 2, 548, "", 0 },

  { 275, "lgv2/Plants/CSE1/T_e/T_e24/Value", offsetof(Parameters_LgV2,
    T_e24_Value_e), 31, 1, 2, 550, "", 0 },

  { 276, "lgv2/Plants/CSE1/T_e/l_x2/Value", offsetof(Parameters_LgV2,
    l_x2_Value_j), 31, 1, 2, 552, "", 0 },

  { 277, "lgv2/Plants/CSE1/T_e/-l_x2/Gain", offsetof(Parameters_LgV2,
    l_x2_Gain_bv), 31, 1, 2, 554, "", 0 },

  { 278, "lgv2/Plants/CSE1/T_e/T_e15/Value", offsetof(Parameters_LgV2,
    T_e15_Value_c), 31, 1, 2, 556, "", 0 },

  { 279, "lgv2/Plants/CSE1/T_e/T_e25/Value", offsetof(Parameters_LgV2,
    T_e25_Value_o), 31, 1, 2, 558, "", 0 },

  { 280, "lgv2/Plants/CSE1/T_e/l_x3/Value", offsetof(Parameters_LgV2,
    l_x3_Value_g), 31, 1, 2, 560, "", 0 },

  { 281, "lgv2/Plants/CSE1/K_e/K_e1_CSE1/Value", offsetof(Parameters_LgV2,
    K_e1_CSE1_Value), 31, 1, 2, 562, "", 0 },

  { 282, "lgv2/Plants/CSE1/K_e/Gain K_e1_CSE1/Gain", offsetof(Parameters_LgV2,
    GainK_e1_CSE1_Gain), 31, 1, 2, 564, "", 0 },

  { 283, "lgv2/Plants/CSE1/K_e/Constant/Value", offsetof(Parameters_LgV2,
    Constant_Value_p), 31, 1, 2, 566, "", 0 },

  { 284, "lgv2/Plants/CSE1/K_e/K_e2_CSE1/Value", offsetof(Parameters_LgV2,
    K_e2_CSE1_Value), 31, 1, 2, 568, "", 0 },

  { 285, "lgv2/Plants/CSE1/K_e/Gain K_e2_CSE1/Gain", offsetof(Parameters_LgV2,
    GainK_e2_CSE1_Gain), 31, 1, 2, 570, "", 0 },

  { 286, "lgv2/Plants/CSE1/K_e/K_e3_CSE1/Value", offsetof(Parameters_LgV2,
    K_e3_CSE1_Value), 31, 1, 2, 572, "", 0 },

  { 287, "lgv2/Plants/CSE1/K_e/Gain K_e3_CSE1/Gain", offsetof(Parameters_LgV2,
    GainK_e3_CSE1_Gain), 31, 1, 2, 574, "", 0 },

  { 288, "lgv2/Plants/CSE1/K_e/K_e4_CSE1/Value", offsetof(Parameters_LgV2,
    K_e4_CSE1_Value), 31, 1, 2, 576, "", 0 },

  { 289, "lgv2/Plants/CSE1/K_e/Gain K_e4_CSE1/Gain", offsetof(Parameters_LgV2,
    GainK_e4_CSE1_Gain), 31, 1, 2, 578, "", 0 },

  { 290, "lgv2/Plants/CSE1/K_e/K_e5_CSE1/Value", offsetof(Parameters_LgV2,
    K_e5_CSE1_Value), 31, 1, 2, 580, "", 0 },

  { 291, "lgv2/Plants/CSE1/K_e/Gain K_e5_CSE1/Gain", offsetof(Parameters_LgV2,
    GainK_e5_CSE1_Gain), 31, 1, 2, 582, "", 0 },

  { 292, "lgv2/Plants/CSE1/CSE1 tau_surge/Gain", offsetof(Parameters_LgV2,
    CSE1tau_surge_Gain), 31, 1, 2, 584, "", 0 },

  { 293, "lgv2/Plants/CSE1/CSE1 tau_sway/Gain", offsetof(Parameters_LgV2,
    CSE1tau_sway_Gain), 31, 1, 2, 586, "", 0 },

  { 294, "lgv2/Plants/CSE1/CSE1 tau_yaw/Gain", offsetof(Parameters_LgV2,
    CSE1tau_yaw_Gain), 31, 1, 2, 588, "", 0 },

  { 295, "lgv2/Plants/Linear Simulator/u to tau/Gain u_1/Gain", offsetof
    (Parameters_LgV2, Gainu_1_Gain), 31, 1, 2, 590, "", 0 },

  { 296, "lgv2/Plants/Linear Simulator/u to tau/Gain u_2/Gain", offsetof
    (Parameters_LgV2, Gainu_2_Gain), 31, 1, 2, 592, "", 0 },

  { 297, "lgv2/Plants/Linear Simulator/u to tau/Gain u_3/Gain", offsetof
    (Parameters_LgV2, Gainu_3_Gain), 31, 1, 2, 594, "", 0 },

  { 298, "lgv2/Plants/Linear Simulator/u to tau/Gain u_4/Gain", offsetof
    (Parameters_LgV2, Gainu_4_Gain), 31, 1, 2, 596, "", 0 },

  { 299, "lgv2/Plants/Linear Simulator/u to tau/Gain BT power/Gain", offsetof
    (Parameters_LgV2, GainBTpower_Gain), 31, 1, 2, 598, "", 0 },

  { 300, "lgv2/Plants/Linear Simulator/u to tau/Neg/Gain", offsetof
    (Parameters_LgV2, Neg_Gain_f), 31, 1, 2, 600, "", 0 },

  { 301, "lgv2/Plants/Linear Simulator/u to tau/Gain u_5/Gain", offsetof
    (Parameters_LgV2, Gainu_5_Gain), 31, 1, 2, 602, "", 0 },

  { 302, "lgv2/Plants/Linear Simulator/u to tau/tau_surge_hil/Gain", offsetof
    (Parameters_LgV2, tau_surge_hil_Gain), 31, 1, 2, 604, "", 0 },

  { 303, "lgv2/Plants/Linear Simulator/u to tau/tau_sway_hil/Gain", offsetof
    (Parameters_LgV2, tau_sway_hil_Gain), 31, 1, 2, 606, "", 0 },

  { 304, "lgv2/Plants/Linear Simulator/u to tau/tau_yaw_hil/Gain", offsetof
    (Parameters_LgV2, tau_yaw_hil_Gain), 31, 1, 2, 608, "", 0 },

  { 305, "lgv2/Plants/Linear Simulator/u to tau/VSP_angle_deg_port/Gain",
    offsetof(Parameters_LgV2, VSP_angle_deg_port_Gain), 31, 1, 2, 610, "", 0 },

  { 306, "lgv2/Plants/Linear Simulator/u to tau/VSP_angle_deg_stbd/Gain",
    offsetof(Parameters_LgV2, VSP_angle_deg_stbd_Gain), 31, 1, 2, 612, "", 0 },

  { 307, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/N_r/Value", offsetof
    (Parameters_LgV2, N_r_Value), 31, 1, 2, 614, "", 0 },

  { 308, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_r/Gain", offsetof
    (Parameters_LgV2, N_r_Gain), 31, 1, 2, 616, "", 0 },

  { 309, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/N_v/Value", offsetof
    (Parameters_LgV2, N_v_Value), 31, 1, 2, 618, "", 0 },

  { 310, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_v/Gain", offsetof
    (Parameters_LgV2, N_v_Gain), 31, 1, 2, 620, "", 0 },

  { 311, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/X_u/Value", offsetof
    (Parameters_LgV2, X_u_Value), 31, 1, 2, 622, "", 0 },

  { 312, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-X_u/Gain", offsetof
    (Parameters_LgV2, X_u_Gain), 31, 1, 2, 624, "", 0 },

  { 313, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/Y_v/Value", offsetof
    (Parameters_LgV2, Y_v_Value), 31, 1, 2, 626, "", 0 },

  { 314, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_v/Gain", offsetof
    (Parameters_LgV2, Y_v_Gain), 31, 1, 2, 628, "", 0 },

  { 315, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/Y_r/Value", offsetof
    (Parameters_LgV2, Y_r_Value), 31, 1, 2, 630, "", 0 },

  { 316, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_vr/Gain", offsetof
    (Parameters_LgV2, Y_vr_Gain), 31, 1, 2, 632, "", 0 },

  { 317, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_12/Value",
    offsetof(Parameters_LgV2, D_L_12_Value), 31, 1, 2, 634, "", 0 },

  { 318, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_13/Value",
    offsetof(Parameters_LgV2, D_L_13_Value), 31, 1, 2, 636, "", 0 },

  { 319, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_21/Value",
    offsetof(Parameters_LgV2, D_L_21_Value), 31, 1, 2, 638, "", 0 },

  { 320, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_31/Value",
    offsetof(Parameters_LgV2, D_L_31_Value), 31, 1, 2, 640, "", 0 },

  { 321, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/psi_0/Value",
    offsetof(Parameters_LgV2, psi_0_Value), 31, 1, 2, 642, "", 0 },

  { 322, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/x_0/Value",
    offsetof(Parameters_LgV2, x_0_Value), 31, 1, 2, 644, "", 0 },

  { 323, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/y_0/Value",
    offsetof(Parameters_LgV2, y_0_Value), 31, 1, 2, 646, "", 0 },

  { 324, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/r_0/Value",
    offsetof(Parameters_LgV2, r_0_Value), 31, 1, 2, 648, "", 0 },

  { 325, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/u_0/Value",
    offsetof(Parameters_LgV2, u_0_Value), 31, 1, 2, 650, "", 0 },

  { 326, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/v_0/Value",
    offsetof(Parameters_LgV2, v_0_Value), 31, 1, 2, 652, "", 0 },

  { 327,
    "lgv2/Plants/Linear Simulator/Vessel Dynamics/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_LgV2, ResetLinearSimulatorintegrator_), 31, 1, 2, 654,
    "", 0 },

  { 328, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/I_z/Value",
    offsetof(Parameters_LgV2, I_z_Value), 31, 1, 2, 656, "", 0 },

  { 329, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/m/Value", offsetof
    (Parameters_LgV2, m_Value), 31, 1, 2, 658, "", 0 },

  { 330, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/X_udot/Value",
    offsetof(Parameters_LgV2, X_udot_Value), 31, 1, 2, 660, "", 0 },

  { 331, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_21/Value",
    offsetof(Parameters_LgV2, M_21_Value), 31, 1, 2, 662, "", 0 },

  { 332, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_31/Value",
    offsetof(Parameters_LgV2, M_31_Value), 31, 1, 2, 664, "", 0 },

  { 333, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_12/Value",
    offsetof(Parameters_LgV2, M_12_Value), 31, 1, 2, 666, "", 0 },

  { 334, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/Y_vdot/Value",
    offsetof(Parameters_LgV2, Y_vdot_Value), 31, 1, 2, 668, "", 0 },

  { 335, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/x_g/Value",
    offsetof(Parameters_LgV2, x_g_Value), 31, 1, 2, 670, "", 0 },

  { 336, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/N_vdot/Value",
    offsetof(Parameters_LgV2, N_vdot_Value), 31, 1, 2, 672, "", 0 },

  { 337, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_13/Value",
    offsetof(Parameters_LgV2, M_13_Value), 31, 1, 2, 674, "", 0 },

  { 338, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/Y_rdot/Value",
    offsetof(Parameters_LgV2, Y_rdot_Value), 31, 1, 2, 676, "", 0 },

  { 339, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/N_rdot/Value",
    offsetof(Parameters_LgV2, N_rdot_Value), 31, 1, 2, 678, "", 0 },

  { 340, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e11/Value", offsetof
    (Parameters_LgV2, T_e11_Value_c1), 31, 1, 2, 680, "", 0 },

  { 341, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e21/Value", offsetof
    (Parameters_LgV2, T_e21_Value_a), 31, 1, 2, 682, "", 0 },

  { 342, "lgv2/Plants/Linear Simulator/u to tau/T_e/l_y1/Value", offsetof
    (Parameters_LgV2, l_y1_Value_j), 31, 1, 2, 684, "", 0 },

  { 343, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e12/Value", offsetof
    (Parameters_LgV2, T_e12_Value_iv), 31, 1, 2, 686, "", 0 },

  { 344, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e22/Value", offsetof
    (Parameters_LgV2, T_e22_Value_on), 31, 1, 2, 688, "", 0 },

  { 345, "lgv2/Plants/Linear Simulator/u to tau/T_e/l_x1/Value", offsetof
    (Parameters_LgV2, l_x1_Value_f), 31, 1, 2, 690, "", 0 },

  { 346, "lgv2/Plants/Linear Simulator/u to tau/T_e/-l_x1/Gain", offsetof
    (Parameters_LgV2, l_x1_Gain_o), 31, 1, 2, 692, "", 0 },

  { 347, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e13/Value", offsetof
    (Parameters_LgV2, T_e13_Value_i), 31, 1, 2, 694, "", 0 },

  { 348, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e23/Value", offsetof
    (Parameters_LgV2, T_e23_Value_k), 31, 1, 2, 696, "", 0 },

  { 349, "lgv2/Plants/Linear Simulator/u to tau/T_e/l_y2/Value", offsetof
    (Parameters_LgV2, l_y2_Value_j), 31, 1, 2, 698, "", 0 },

  { 350, "lgv2/Plants/Linear Simulator/u to tau/T_e/-l_y2/Gain", offsetof
    (Parameters_LgV2, l_y2_Gain_p), 31, 1, 2, 700, "", 0 },

  { 351, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e14/Value", offsetof
    (Parameters_LgV2, T_e14_Value_g), 31, 1, 2, 702, "", 0 },

  { 352, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e24/Value", offsetof
    (Parameters_LgV2, T_e24_Value_b), 31, 1, 2, 704, "", 0 },

  { 353, "lgv2/Plants/Linear Simulator/u to tau/T_e/l_x2/Value", offsetof
    (Parameters_LgV2, l_x2_Value_p), 31, 1, 2, 706, "", 0 },

  { 354, "lgv2/Plants/Linear Simulator/u to tau/T_e/-l_x2/Gain", offsetof
    (Parameters_LgV2, l_x2_Gain_d), 31, 1, 2, 708, "", 0 },

  { 355, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e15/Value", offsetof
    (Parameters_LgV2, T_e15_Value_j), 31, 1, 2, 710, "", 0 },

  { 356, "lgv2/Plants/Linear Simulator/u to tau/T_e/T_e25/Value", offsetof
    (Parameters_LgV2, T_e25_Value_n), 31, 1, 2, 712, "", 0 },

  { 357, "lgv2/Plants/Linear Simulator/u to tau/T_e/l_x3/Value", offsetof
    (Parameters_LgV2, l_x3_Value_n), 31, 1, 2, 714, "", 0 },

  { 358, "lgv2/Plants/Linear Simulator/u to tau/K_e/K_e1_hil/Value", offsetof
    (Parameters_LgV2, K_e1_hil_Value), 31, 1, 2, 716, "", 0 },

  { 359, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e1_hil/Gain",
    offsetof(Parameters_LgV2, GainK_e1_hil_Gain), 31, 1, 2, 718, "", 0 },

  { 360, "lgv2/Plants/Linear Simulator/u to tau/K_e/Constant41/Value", offsetof
    (Parameters_LgV2, Constant41_Value), 31, 1, 2, 720, "", 0 },

  { 361, "lgv2/Plants/Linear Simulator/u to tau/K_e/K_e2_hil/Value", offsetof
    (Parameters_LgV2, K_e2_hil_Value), 31, 1, 2, 722, "", 0 },

  { 362, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e2_hil/Gain",
    offsetof(Parameters_LgV2, GainK_e2_hil_Gain), 31, 1, 2, 724, "", 0 },

  { 363, "lgv2/Plants/Linear Simulator/u to tau/K_e/K_e3_hil/Value", offsetof
    (Parameters_LgV2, K_e3_hil_Value), 31, 1, 2, 726, "", 0 },

  { 364, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e3_hil/Gain",
    offsetof(Parameters_LgV2, GainK_e3_hil_Gain), 31, 1, 2, 728, "", 0 },

  { 365, "lgv2/Plants/Linear Simulator/u to tau/K_e/K_e4_hil/Value", offsetof
    (Parameters_LgV2, K_e4_hil_Value), 31, 1, 2, 730, "", 0 },

  { 366, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e4_hil/Gain",
    offsetof(Parameters_LgV2, GainK_e4_hil_Gain), 31, 1, 2, 732, "", 0 },

  { 367, "lgv2/Plants/Linear Simulator/u to tau/K_e/K_e5_hil/Value", offsetof
    (Parameters_LgV2, K_e5_hil_Value), 31, 1, 2, 734, "", 0 },

  { 368, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e5_hil/Gain",
    offsetof(Parameters_LgV2, GainK_e5_hil_Gain), 31, 1, 2, 736, "", 0 },

  { 369,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/sample time/WtEt",
    offsetof(Parameters_LgV2, sampletime_WtEt), 0, 1, 2, 738, "", 0 },

  { 370,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Delay Input2/X0",
    offsetof(Parameters_LgV2, DelayInput2_X0), 31, 1, 2, 740, "", 0 },

  { 371, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_LgV2, R31_Value), 31, 1, 2, 742, "", 0 },

  { 372, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_LgV2, R32_Value), 31, 1, 2, 744, "", 0 },

  { 373, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_LgV2, R13_Value), 31, 1, 2, 746, "", 0 },

  { 374, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_LgV2, R23_Value), 31, 1, 2, 748, "", 0 },

  { 375, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_LgV2, R33_Value), 31, 1, 2, 750, "", 0 },

  { 376, "lgv2/Plants/Linear Simulator/eta_surge_hil/Gain", offsetof
    (Parameters_LgV2, eta_surge_hil_Gain), 31, 1, 2, 752, "", 0 },

  { 377, "lgv2/Plants/Linear Simulator/eta_sway_hil/Gain", offsetof
    (Parameters_LgV2, eta_sway_hil_Gain), 31, 1, 2, 754, "", 0 },

  { 378, "lgv2/Plants/Linear Simulator/eta_yaw_hil/Gain", offsetof
    (Parameters_LgV2, eta_yaw_hil_Gain), 31, 1, 2, 756, "", 0 },

  { 379, "lgv2/Plants/Linear Simulator/etadot_surge_hil/Gain", offsetof
    (Parameters_LgV2, etadot_surge_hil_Gain), 31, 1, 2, 758, "", 0 },

  { 380, "lgv2/Plants/Linear Simulator/etadot_sway_hil/Gain", offsetof
    (Parameters_LgV2, etadot_sway_hil_Gain), 31, 1, 2, 760, "", 0 },

  { 381, "lgv2/Plants/Linear Simulator/etadot_yaw_hil/Gain", offsetof
    (Parameters_LgV2, etadot_yaw_hil_Gain), 31, 1, 2, 762, "", 0 },

  { 382, "lgv2/Plants/Linear Simulator/nu_surge_hil/Gain", offsetof
    (Parameters_LgV2, nu_surge_hil_Gain), 31, 1, 2, 764, "", 0 },

  { 383, "lgv2/Plants/Linear Simulator/nu_sway_hil/Gain", offsetof
    (Parameters_LgV2, nu_sway_hil_Gain), 31, 1, 2, 766, "", 0 },

  { 384, "lgv2/Plants/Linear Simulator/nu_yaw_hil/Gain", offsetof
    (Parameters_LgV2, nu_yaw_hil_Gain), 31, 1, 2, 768, "", 0 },
};

static int NI_ParamListSize = 385;
static int NI_ParamDimList[] = {
  1, 1,                                /* lgv2/Control Systems/Control Mode/Value */
  1, 1,                                /* lgv2/HMI/Accuracy control/u1/Value */
  1, 1,                                /* lgv2/HMI/Accuracy control/Accuracy u_1/Gain */
  1, 1,                                /* lgv2/HMI/Accuracy control/u2/Value */
  1, 1,                                /* lgv2/HMI/Accuracy control/Accuracy u_2/Gain */
  1, 1,                                /* lgv2/HMI/Accuracy control/u3/Value */
  1, 1,                                /* lgv2/HMI/Accuracy control/Accuracy u_3/Gain */
  1, 1,                                /* lgv2/HMI/Accuracy control/u4/Value */
  1, 1,                                /* lgv2/HMI/Accuracy control/Accuracy u_4/Gain */
  1, 1,                                /* lgv2/HMI/Accuracy control/u5/Value */
  1, 1,                                /* lgv2/HMI/Accuracy control/Accuracy u_5/Gain */
  1, 1,                                /* lgv2/HMI/Accuracy control/Accuracy  BT power/Value */
  1, 1,                                /* lgv2/HMI/Accuracy control/Accuracy  VSP speed/Value */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/JS_L_Y/Value */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_L_Y/Gain */
  1, 1,                                /* lgv2/Control Systems/Manual Thrust control/PS3 u_1/Gain */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/JS_L_X/Value */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_L_X/Gain */
  1, 1,                                /* lgv2/Control Systems/Manual Thrust control/PS3 u_2/Gain */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/JS_R_Y/Value */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_R_Y/Gain */
  1, 1,                                /* lgv2/Control Systems/Manual Thrust control/PS3 u_3/Gain */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/JS_R_X/Value */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_R_X/Gain */
  1, 1,                                /* lgv2/Control Systems/Manual Thrust control/PS3 u_4/Gain */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/L2/Value */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3 signals/R2/Value */
  1, 1,                                /* lgv2/Control Systems/Manual Thrust control/PS3 u_5/Gain */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3_BT_Power/Value */
  1, 1,                                /* lgv2/HMI/PS3 input/PS3_VSP_Speed/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/K_e1_joystick/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/Gain K_e1_joystick/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/K_e2_joystick/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/Gain K_e2_joystick/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/K_e3_joystick/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/Gain K_e3_joystick/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/K_e4_joystick/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/Gain K_e4_joystick/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/K_e5_joystick/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/K_e/Gain K_e5_joystick/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e11/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e21/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/l_y1/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e12/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e22/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/l_x1/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/-l_x1/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e13/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e23/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/l_y2/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/-l_y2/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e14/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e24/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/l_x2/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/-l_x2/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e15/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/T_e25/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/T_e/l_x3/Value */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Joystick tau_surge/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Saturation1/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Saturation1/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Joystick tau_sway/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Saturation2/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Saturation2/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Joystick tau_yaw/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Saturation3/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Saturation3/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Joystick u_1/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Joystick u_2/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Joystick u_3/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Joystick u_4/Gain */
  1, 1,                                /* lgv2/Control Systems/Joystick Control/Joystick u_5/Gain */
  1, 1,                                /* lgv2/Guidance Systems/DP/Enable eta_d LPF/Value */
  1, 1,                                /* lgv2/HMI/DP input/x_d/Value */
  1, 1,                                /* lgv2/HMI/DP input/y_d/Value */
  1, 1,                                /* lgv2/HMI/DP input/psi_d/Value */
  1, 1,                                /* lgv2/HMI/DP input/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* lgv2/Guidance Systems/DP/Transfer Fcn/A */
  1, 1,                                /* lgv2/Guidance Systems/DP/Transfer Fcn/C */
  1, 1,                                /* lgv2/Guidance Systems/DP/Transfer Fcn1/A */
  1, 1,                                /* lgv2/Guidance Systems/DP/Transfer Fcn1/C */
  1, 1,                                /* lgv2/Guidance Systems/DP/Transfer Fcn2/A */
  1, 1,                                /* lgv2/Guidance Systems/DP/Transfer Fcn2/C */
  1, 1,                                /* lgv2/Guidance Systems/DP/eta_d DP N/Gain */
  1, 1,                                /* lgv2/Guidance Systems/DP/eta_d DP E/Gain */
  1, 1,                                /* lgv2/Guidance Systems/DP/eta_d DP Psi/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Controller Input Selector/Value */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain */
  1, 1,                                /* lgv2/Plants/Enable Linear Simulator/Value */
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
  1, 1,                                /* lgv2/Control Systems/if DP Control Mode/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain */
  1, 1,                                /* lgv2/Guidance Systems/DP/eta_d Psi deg/Gain */
  1, 1,                                /* lgv2/Guidance Systems/psi_d/Gain */
  1, 1,                                /* lgv2/Guidance Systems/x_d/Gain */
  1, 1,                                /* lgv2/Guidance Systems/y_d/Gain */
  1, 1,                                /* lgv2/HMI/Battery Bow Thruster/Gain */
  1, 1,                                /* lgv2/HMI/Battery Servo/Gain */
  1, 1,                                /* lgv2/HMI/Battery Main/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain */
  1, 1,                                /* lgv2/Plants/u_1 plant/Gain */
  1, 1,                                /* lgv2/Plants/u_2 plant/Gain */
  1, 1,                                /* lgv2/Plants/u_3 plant/Gain */
  1, 1,                                /* lgv2/Plants/u_4 plant/Gain */
  1, 1,                                /* lgv2/Plants/u_5 plant/Gain */
  1, 1,                                /* lgv2/Plants/BT power limit plant/Gain */
  1, 1,                                /* lgv2/Plants/VSP speed plant/Gain */
  1, 1,                                /* lgv2/Plants/Enable CSE1/Value */
  7, 1,                                /* lgv2/Control Systems/DP control/Thruster_Command_DP/InitialOutput */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator1/InitialCondition */
  1, 1,                                /* lgv2/Control Systems/DP control/BT_power_limit/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Enable Filter/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator/InitialCondition */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/eta N/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/eta E/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/eta Psi/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Reg_e_N_hil/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Reg_e_E_hil/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Reg_e_Psi_hil/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Reset_DP_integrator/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Integrator/InitialCondition */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator4/InitialCondition */
  3, 3,                                /* lgv2/Control Systems/DP control/DP controller/Kd/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Kd_scale/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_d 1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_d 2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_d 3/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_d 3 deg/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/DP controller/Ki/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Ki_scale/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_i 1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_i 2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_i 3/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_i 3 deg/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Kp_scale/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value */
  3, 3,                                /* lgv2/Control Systems/DP control/DP controller/Kp/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_p 1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_p 2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_p 3/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_p 3 deg/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Reg_e_Psi_deg/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/eta Psi deg/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP tau_surge/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP tau_sway/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP tau_yaw/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/K_e1_DP/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/Gain K_e1_DP/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/K_e2_DP/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/Gain K_e2_DP/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/K_e3_DP/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/Gain K_e3_DP/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/K_e4_DP/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/Gain K_e4_DP/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/K_e5_DP/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/K_e/Gain K_e5_DP/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e11/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e21/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/l_y1/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e12/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e22/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/l_x1/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/-l_x1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e13/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e23/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/l_y2/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/-l_y2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e14/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e24/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/l_x2/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/-l_x2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e15/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/T_e25/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/T_e/l_x3/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP u_1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP u_2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP u_3/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP u_4/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP u_5/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator2/InitialCondition */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Gain2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Constant/Value */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/K4/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator3/InitialCondition */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Gain6/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/Gain3/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/K11/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/K12/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/K2/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/K3/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/Passive DP wave filter1/inv(T_b)/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/VSP_speeds/Value */
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
  1, 1,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain/Gain */
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
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e11/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e21/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/l_y1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e12/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e22/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/l_x1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/-l_x1/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e13/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e23/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/l_y2/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/-l_y2/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e14/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e24/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/l_x2/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/-l_x2/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e15/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/T_e25/Value */
  1, 1,                                /* lgv2/Plants/CSE1/T_e/l_x3/Value */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/K_e1_CSE1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/Gain K_e1_CSE1/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/Constant/Value */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/K_e2_CSE1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/Gain K_e2_CSE1/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/K_e3_CSE1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/Gain K_e3_CSE1/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/K_e4_CSE1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/Gain K_e4_CSE1/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/K_e5_CSE1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/K_e/Gain K_e5_CSE1/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/CSE1 tau_surge/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/CSE1 tau_sway/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/CSE1 tau_yaw/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Gain u_1/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Gain u_2/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Gain u_3/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Gain u_4/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Gain BT power/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Neg/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Gain u_5/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/tau_surge_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/tau_sway_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/tau_yaw_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/VSP_angle_deg_port/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/VSP_angle_deg_stbd/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/N_r/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_r/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/N_v/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_v/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/X_u/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-X_u/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/Y_v/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_v/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/Y_r/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_vr/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_12/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_13/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_21/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/D_L_31/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/psi_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/x_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/y_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/r_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/u_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/v_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/Reset Linear Simulator integrator/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/I_z/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/m/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/X_udot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_21/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_31/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_12/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/Y_vdot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/x_g/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/N_vdot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_13/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/Y_rdot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/N_rdot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e11/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e21/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/l_y1/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e12/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e22/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/l_x1/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/-l_x1/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e13/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e23/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/l_y2/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/-l_y2/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e14/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e24/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/l_x2/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/-l_x2/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e15/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/T_e25/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/T_e/l_x3/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/K_e1_hil/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e1_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/Constant41/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/K_e2_hil/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e2_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/K_e3_hil/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e3_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/K_e4_hil/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e4_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/K_e5_hil/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e5_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/sample time/WtEt */
  1, 1,                                /* lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Delay Input2/X0 */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/eta_surge_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/eta_sway_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/eta_yaw_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/etadot_surge_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/etadot_sway_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/etadot_yaw_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/nu_surge_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/nu_sway_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/nu_yaw_hil/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 360;
static NI_Signal NI_SigList[] = {
  { 0, "lgv2/HMI/Accuracy control/Accuracy u_1", 0, "", offsetof(BlockIO_LgV2,
    Accuracyu_1), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "lgv2/HMI/Accuracy control/Accuracy u_2", 0, "", offsetof(BlockIO_LgV2,
    Accuracyu_2), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "lgv2/HMI/Accuracy control/Accuracy u_3", 0, "", offsetof(BlockIO_LgV2,
    Accuracyu_3), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "lgv2/HMI/Accuracy control/Accuracy u_4", 0, "", offsetof(BlockIO_LgV2,
    Accuracyu_4), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "lgv2/HMI/Accuracy control/Accuracy u_5", 0, "", offsetof(BlockIO_LgV2,
    Accuracyu_5), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_L_Y", 0, "[-1,1]", offsetof
    (BlockIO_LgV2, u1), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "lgv2/Control Systems/Manual Thrust control/PS3 u_1", 0, "", offsetof
    (BlockIO_LgV2, PS3u_1), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_L_X", 0, "[-1,1]", offsetof
    (BlockIO_LgV2, u1_b), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "lgv2/Control Systems/Manual Thrust control/PS3 u_2", 0, "", offsetof
    (BlockIO_LgV2, PS3u_2), BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_R_Y", 0, "[-1,1]", offsetof
    (BlockIO_LgV2, u1_l), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "lgv2/Control Systems/Manual Thrust control/PS3 u_3", 0, "", offsetof
    (BlockIO_LgV2, PS3u_3), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "lgv2/HMI/PS3 input/PS3 signals/Scaling_JS_R_X", 0, "[-1,1]", offsetof
    (BlockIO_LgV2, u1_c), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "lgv2/Control Systems/Manual Thrust control/PS3 u_4", 0, "", offsetof
    (BlockIO_LgV2, PS3u_4), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "lgv2/Control Systems/Manual Thrust control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_LgV2, BowThrusterdirection),
    BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "lgv2/Control Systems/Manual Thrust control/PS3 u_5", 0, "", offsetof
    (BlockIO_LgV2, PS3u_5), BLOCKIO_SIG, 0, 1, 2, 28, 0 },

  { 15, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e1_joystick", 0, "",
    offsetof(BlockIO_LgV2, GainK_e1_joystick), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e2_joystick", 0, "",
    offsetof(BlockIO_LgV2, GainK_e2_joystick), BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e3_joystick", 0, "",
    offsetof(BlockIO_LgV2, GainK_e3_joystick), BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e4_joystick", 0, "",
    offsetof(BlockIO_LgV2, GainK_e4_joystick), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "lgv2/Control Systems/Joystick Control/K_e/Gain K_e5_joystick", 0, "",
    offsetof(BlockIO_LgV2, GainK_e5_joystick), BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "lgv2/Control Systems/Joystick Control/K_e/Thruster Gain matrix", 0, "",
    offsetof(BlockIO_LgV2, ThrusterGainmatrix), BLOCKIO_SIG, 24, 25, 2, 40, 0 },

  { 21, "lgv2/Control Systems/Joystick Control/K_e^-1", 0, "", offsetof
    (BlockIO_LgV2, K_e1), BLOCKIO_SIG, 24, 25, 2, 42, 0 },

  { 22, "lgv2/Control Systems/Joystick Control/T_e/-l_x1", 0, "", offsetof
    (BlockIO_LgV2, l_x1), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { 23, "lgv2/Control Systems/Joystick Control/T_e/-l_y2", 0, "", offsetof
    (BlockIO_LgV2, l_y2), BLOCKIO_SIG, 0, 1, 2, 46, 0 },

  { 24, "lgv2/Control Systems/Joystick Control/T_e/-l_x2", 0, "", offsetof
    (BlockIO_LgV2, l_x2), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25, "lgv2/Control Systems/Joystick Control/T_e/3x5", 0, "", offsetof
    (BlockIO_LgV2, x5), BLOCKIO_SIG, 28, 15, 2, 50, 0 },

  { 26, "lgv2/Control Systems/Joystick Control/T_e^+", 0, "", offsetof
    (BlockIO_LgV2, T_e), BLOCKIO_SIG, 27, 15, 2, 52, 0 },

  { 27, "lgv2/Control Systems/Joystick Control/T_e^+ K_e^-1", 0, "", offsetof
    (BlockIO_LgV2, T_eK_e1), BLOCKIO_SIG, 27, 15, 2, 54, 0 },

  { 28, "lgv2/Control Systems/Joystick Control/Sum1", 0, "", offsetof
    (BlockIO_LgV2, Sum1), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29, "lgv2/Control Systems/Joystick Control/Joystick tau_surge", 0, "",
    offsetof(BlockIO_LgV2, Joysticktau_surge), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30, "lgv2/Control Systems/Joystick Control/Saturation1", 0, "", offsetof
    (BlockIO_LgV2, Saturation1), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31, "lgv2/Control Systems/Joystick Control/Sum2", 0, "", offsetof
    (BlockIO_LgV2, Sum2), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32, "lgv2/Control Systems/Joystick Control/Joystick tau_sway", 0, "",
    offsetof(BlockIO_LgV2, Joysticktau_sway), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33, "lgv2/Control Systems/Joystick Control/Saturation2", 0, "", offsetof
    (BlockIO_LgV2, Saturation2), BLOCKIO_SIG, 0, 1, 2, 66, 0 },

  { 34, "lgv2/Control Systems/Joystick Control/Sum", 0, "", offsetof
    (BlockIO_LgV2, Sum), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35, "lgv2/Control Systems/Joystick Control/Joystick tau_yaw", 0, "",
    offsetof(BlockIO_LgV2, Joysticktau_yaw), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36, "lgv2/Control Systems/Joystick Control/Saturation3", 0, "", offsetof
    (BlockIO_LgV2, Saturation3), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37, "lgv2/Control Systems/Joystick Control/Product1", 0, "", offsetof
    (BlockIO_LgV2, Product1), BLOCKIO_SIG, 23, 5, 2, 74, 0 },

  { 38, "lgv2/Control Systems/Joystick Control/Saturation", 0, "", offsetof
    (BlockIO_LgV2, Saturation), BLOCKIO_SIG, 23, 5, 2, 76, 0 },

  { 39, "lgv2/Control Systems/Joystick Control/Joystick u_1", 0, "", offsetof
    (BlockIO_LgV2, Joysticku_1), BLOCKIO_SIG, 0, 1, 2, 78, 0 },

  { 40, "lgv2/Control Systems/Joystick Control/Joystick u_2", 0, "", offsetof
    (BlockIO_LgV2, Joysticku_2), BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41, "lgv2/Control Systems/Joystick Control/Joystick u_3", 0, "", offsetof
    (BlockIO_LgV2, Joysticku_3), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42, "lgv2/Control Systems/Joystick Control/Joystick u_4", 0, "", offsetof
    (BlockIO_LgV2, Joysticku_4), BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "lgv2/Control Systems/Joystick Control/Joystick u_5", 0, "", offsetof
    (BlockIO_LgV2, Joysticku_5), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44, "lgv2/HMI/DP input/Degrees to Radians/Gain1", 0, "", offsetof
    (BlockIO_LgV2, Gain1), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "lgv2/Guidance Systems/DP/Transfer Fcn", 0, "", offsetof(BlockIO_LgV2,
    TransferFcn), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46, "lgv2/Guidance Systems/DP/Transfer Fcn1", 0, "", offsetof(BlockIO_LgV2,
    TransferFcn1), BLOCKIO_SIG, 0, 1, 2, 92, 0 },

  { 47, "lgv2/Guidance Systems/DP/Transfer Fcn2", 0, "", offsetof(BlockIO_LgV2,
    TransferFcn2), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48, "lgv2/Guidance Systems/DP/Multiport Switch", 0, "", offsetof
    (BlockIO_LgV2, MultiportSwitch), BLOCKIO_SIG, 17, 3, 2, 96, 0 },

  { 49, "lgv2/Guidance Systems/DP/eta_d DP N", 0, "", offsetof(BlockIO_LgV2,
    eta_dDPN), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50, "lgv2/Guidance Systems/DP/eta_d DP E", 0, "", offsetof(BlockIO_LgV2,
    eta_dDPE), BLOCKIO_SIG, 0, 1, 2, 100, 0 },

  { 51, "lgv2/Guidance Systems/DP/eta_d DP Psi", 0, "", offsetof(BlockIO_LgV2,
    eta_dDPPsi), BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In", 0, "", offsetof
    (BlockIO_LgV2, QTMIn), BLOCKIO_SIG, 34, 9, 2, 104, 0 },

  { 53, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In3", 0, "", offsetof
    (BlockIO_LgV2, QTMIn3), BLOCKIO_SIG, 31, 1, 2, 106, 0 },

  { 54, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m x", 0, "", offsetof
    (BlockIO_LgV2, mm2mx), BLOCKIO_SIG, 31, 1, 2, 108, 0 },

  { 55, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In4", 0, "", offsetof
    (BlockIO_LgV2, QTMIn4), BLOCKIO_SIG, 31, 1, 2, 110, 0 },

  { 56, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m y", 0, "", offsetof
    (BlockIO_LgV2, mm2my), BLOCKIO_SIG, 31, 1, 2, 112, 0 },

  { 57, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In6", 0, "", offsetof
    (BlockIO_LgV2, QTMIn6), BLOCKIO_SIG, 31, 1, 2, 114, 0 },

  { 58, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r yaw", 0, "", offsetof
    (BlockIO_LgV2, d2ryaw), BLOCKIO_SIG, 31, 1, 2, 116, 0 },

  { 59, "lgv2/Naviagation Systems/Eta Switch", 0, "", offsetof(BlockIO_LgV2,
    EtaSwitch), BLOCKIO_SIG, 17, 3, 2, 118, 0 },

  { 60, "lgv2/Naviagation Systems/eta_surge", 0, "", offsetof(BlockIO_LgV2,
    eta_surge), BLOCKIO_SIG, 0, 1, 2, 120, 0 },

  { 61, "lgv2/Naviagation Systems/eta_sway", 0, "", offsetof(BlockIO_LgV2,
    eta_sway), BLOCKIO_SIG, 0, 1, 2, 122, 0 },

  { 62, "lgv2/Naviagation Systems/eta_yaw", 0, "", offsetof(BlockIO_LgV2,
    eta_yaw), BLOCKIO_SIG, 0, 1, 2, 124, 0 },

  { 63, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In8", 0, "", offsetof
    (BlockIO_LgV2, QTMIn8), BLOCKIO_SIG, 31, 1, 2, 126, 0 },

  { 64, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r roll", 0, "", offsetof
    (BlockIO_LgV2, d2rroll), BLOCKIO_SIG, 31, 1, 2, 128, 0 },

  { 65, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In7", 0, "", offsetof
    (BlockIO_LgV2, QTMIn7), BLOCKIO_SIG, 31, 1, 2, 130, 0 },

  { 66, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r pitch", 0, "", offsetof
    (BlockIO_LgV2, d2rpitch), BLOCKIO_SIG, 31, 1, 2, 132, 0 },

  { 67,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_LgV2, sintheta), BLOCKIO_SIG, 17, 3, 2, 134, 0 },

  { 68,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_LgV2, costheta), BLOCKIO_SIG, 17, 3, 2, 136, 0 },

  { 69,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_LgV2, R11), BLOCKIO_SIG, 0, 1, 2, 138, 0 },

  { 70,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_LgV2, R21), BLOCKIO_SIG, 0, 1, 2, 140, 0 },

  { 71,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_LgV2, R31), BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_LgV2, R12), BLOCKIO_SIG, 0, 1, 2, 144, 0 },

  { 73,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_LgV2, R22), BLOCKIO_SIG, 0, 1, 2, 146, 0 },

  { 74,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_LgV2, R32), BLOCKIO_SIG, 0, 1, 2, 148, 0 },

  { 75,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_LgV2, R13), BLOCKIO_SIG, 0, 1, 2, 150, 0 },

  { 76,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_LgV2, R23), BLOCKIO_SIG, 0, 1, 2, 152, 0 },

  { 77,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_LgV2, R33), BLOCKIO_SIG, 0, 1, 2, 154, 0 },

  { 78,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_LgV2, Reshape9x13x3), BLOCKIO_SIG, 33, 9, 2, 156, 0
  },

  { 79, "lgv2/Naviagation Systems/Qualisys 6 DOF/Matrix Concatenate2", 0, "",
    offsetof(BlockIO_LgV2, MatrixConcatenate2), BLOCKIO_SIG, 36, 36, 2, 158, 0 },

  { 80, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In5", 0, "", offsetof
    (BlockIO_LgV2, QTMIn5), BLOCKIO_SIG, 31, 1, 2, 160, 0 },

  { 81, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m z", 0, "", offsetof
    (BlockIO_LgV2, mm2mz), BLOCKIO_SIG, 31, 1, 2, 162, 0 },

  { 82, "lgv2/Naviagation Systems/Qualisys 6 DOF/Derivative", 0, "", offsetof
    (BlockIO_LgV2, Derivative), BLOCKIO_SIG, 19, 6, 2, 164, 0 },

  { 83, "lgv2/Naviagation Systems/Qualisys 6 DOF/Product", 0, "", offsetof
    (BlockIO_LgV2, Product), BLOCKIO_SIG, 19, 6, 2, 166, 0 },

  { 84, "lgv2/Naviagation Systems/Nu Switch", 0, "", offsetof(BlockIO_LgV2,
    NuSwitch), BLOCKIO_SIG, 17, 3, 2, 168, 0 },

  { 85, "lgv2/Naviagation Systems/nu_surge", 0, "", offsetof(BlockIO_LgV2,
    nu_surge), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86, "lgv2/Naviagation Systems/nu_sway", 0, "", offsetof(BlockIO_LgV2,
    nu_sway), BLOCKIO_SIG, 0, 1, 2, 172, 0 },

  { 87, "lgv2/Naviagation Systems/nu_yaw", 0, "", offsetof(BlockIO_LgV2, nu_yaw),
    BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88, "lgv2/Control Systems/Control Switch", 0, "", offsetof(BlockIO_LgV2,
    ControlSwitch), BLOCKIO_SIG, 18, 7, 2, 176, 0 },

  { 89, "lgv2/Control Systems/Saturation", 0, "", offsetof(BlockIO_LgV2,
    Saturation_e), BLOCKIO_SIG, 18, 7, 2, 178, 0 },

  { 90, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error", 0, "", offsetof
    (BlockIO_LgV2, QTMIn2Error), BLOCKIO_SIG, 31, 1, 2, 180, 0 },

  { 91, "lgv2/Guidance Systems/DP/eta_d Psi deg", 0, "", offsetof(BlockIO_LgV2,
    eta_dPsideg), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92, "lgv2/Guidance Systems/psi_d", 0, "", offsetof(BlockIO_LgV2, psi_d),
    BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93, "lgv2/Guidance Systems/x_d", 0, "", offsetof(BlockIO_LgV2, x_d),
    BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94, "lgv2/Guidance Systems/y_d", 0, "", offsetof(BlockIO_LgV2, y_d),
    BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95, "lgv2/HMI/SIT zAI0", 0, "", offsetof(BlockIO_LgV2, SITzAI0), BLOCKIO_SIG,
    0, 1, 2, 190, 0 },

  { 96, "lgv2/HMI/Battery Bow Thruster", 0, "", offsetof(BlockIO_LgV2,
    BatteryBowThruster), BLOCKIO_SIG, 0, 1, 2, 192, 0 },

  { 97, "lgv2/HMI/SIT zAI1", 0, "", offsetof(BlockIO_LgV2, SITzAI1), BLOCKIO_SIG,
    0, 1, 2, 194, 0 },

  { 98, "lgv2/HMI/Battery Servo", 0, "", offsetof(BlockIO_LgV2, BatteryServo),
    BLOCKIO_SIG, 0, 1, 2, 196, 0 },

  { 99, "lgv2/HMI/SIT zAI2", 0, "", offsetof(BlockIO_LgV2, SITzAI2), BLOCKIO_SIG,
    0, 1, 2, 198, 0 },

  { 100, "lgv2/HMI/Battery Main", 0, "", offsetof(BlockIO_LgV2, BatteryMain),
    BLOCKIO_SIG, 0, 1, 2, 200, 0 },

  { 101, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS", 0, "", offsetof
    (BlockIO_LgV2, QTMIn1FPS), BLOCKIO_SIG, 31, 1, 2, 202, 0 },

  { 102, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual", 0, "",
    offsetof(BlockIO_LgV2, QTMIn9Residual), BLOCKIO_SIG, 31, 1, 2, 204, 0 },

  { 103, "lgv2/Plants/u_1 plant", 0, "", offsetof(BlockIO_LgV2, u_1plant),
    BLOCKIO_SIG, 0, 1, 2, 206, 0 },

  { 104, "lgv2/Plants/u_2 plant", 0, "", offsetof(BlockIO_LgV2, u_2plant),
    BLOCKIO_SIG, 0, 1, 2, 208, 0 },

  { 105, "lgv2/Plants/u_3 plant", 0, "", offsetof(BlockIO_LgV2, u_3plant),
    BLOCKIO_SIG, 0, 1, 2, 210, 0 },

  { 106, "lgv2/Plants/u_4 plant", 0, "", offsetof(BlockIO_LgV2, u_4plant),
    BLOCKIO_SIG, 0, 1, 2, 212, 0 },

  { 107, "lgv2/Plants/u_5 plant", 0, "", offsetof(BlockIO_LgV2, u_5plant),
    BLOCKIO_SIG, 0, 1, 2, 214, 0 },

  { 108, "lgv2/Plants/BT power limit plant", 0, "", offsetof(BlockIO_LgV2,
    BTpowerlimitplant), BLOCKIO_SIG, 0, 1, 2, 216, 0 },

  { 109, "lgv2/Plants/VSP speed plant", 0, "", offsetof(BlockIO_LgV2,
    VSPspeedplant), BLOCKIO_SIG, 0, 1, 2, 218, 0 },

  { 110, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_r", 0, "",
    offsetof(BlockIO_LgV2, N_r), BLOCKIO_SIG, 0, 1, 2, 220, 0 },

  { 111, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-N_v", 0, "",
    offsetof(BlockIO_LgV2, N_v), BLOCKIO_SIG, 0, 1, 2, 222, 0 },

  { 112, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-X_u", 0, "",
    offsetof(BlockIO_LgV2, X_u), BLOCKIO_SIG, 0, 1, 2, 224, 0 },

  { 113, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_v", 0, "",
    offsetof(BlockIO_LgV2, Y_v), BLOCKIO_SIG, 0, 1, 2, 226, 0 },

  { 114, "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/-Y_vr", 0, "",
    offsetof(BlockIO_LgV2, Y_vr), BLOCKIO_SIG, 0, 1, 2, 228, 0 },

  { 115,
    "lgv2/Plants/Linear Simulator/Vessel Dynamics/D_L/Linear Dampning matrix", 0,
    "", offsetof(BlockIO_LgV2, LinearDampningmatrix), BLOCKIO_SIG, 33, 9, 2, 230,
    0 },

  { 116, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/psi_0", 0, "",
    offsetof(BlockIO_LgV2, psi_0), BLOCKIO_SIG, 0, 1, 2, 232, 0 },

  { 117, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/x_0", 0, "",
    offsetof(BlockIO_LgV2, x_0), BLOCKIO_SIG, 0, 1, 2, 234, 0 },

  { 118, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial eta/y_0", 0, "",
    offsetof(BlockIO_LgV2, y_0), BLOCKIO_SIG, 0, 1, 2, 236, 0 },

  { 119, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/r_0", 0, "",
    offsetof(BlockIO_LgV2, r_0), BLOCKIO_SIG, 0, 1, 2, 238, 0 },

  { 120, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/u_0", 0, "",
    offsetof(BlockIO_LgV2, u_0), BLOCKIO_SIG, 0, 1, 2, 240, 0 },

  { 121, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Initial nu/v_0", 0, "",
    offsetof(BlockIO_LgV2, v_0), BLOCKIO_SIG, 0, 1, 2, 242, 0 },

  { 122, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Integrator", 0, "",
    offsetof(BlockIO_LgV2, Integrator), BLOCKIO_SIG, 17, 3, 2, 244, 0 },

  { 123, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Integrator1", 0, "",
    offsetof(BlockIO_LgV2, Integrator1), BLOCKIO_SIG, 17, 3, 2, 246, 0 },

  { 124, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_11", 0, "",
    offsetof(BlockIO_LgV2, M_11), BLOCKIO_SIG, 0, 1, 2, 248, 0 },

  { 125, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_22", 0, "",
    offsetof(BlockIO_LgV2, M_22), BLOCKIO_SIG, 0, 1, 2, 250, 0 },

  { 126, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/m x_g", 0, "",
    offsetof(BlockIO_LgV2, mx_g), BLOCKIO_SIG, 0, 1, 2, 252, 0 },

  { 127, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_32", 0, "",
    offsetof(BlockIO_LgV2, M_32), BLOCKIO_SIG, 0, 1, 2, 254, 0 },

  { 128, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_23", 0, "",
    offsetof(BlockIO_LgV2, M_23), BLOCKIO_SIG, 0, 1, 2, 256, 0 },

  { 129, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M_33", 0, "",
    offsetof(BlockIO_LgV2, M_33), BLOCKIO_SIG, 0, 1, 2, 258, 0 },

  { 130, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/M", 0, "", offsetof
    (BlockIO_LgV2, M), BLOCKIO_SIG, 33, 9, 2, 260, 0 },

  { 131, "lgv2/Plants/Linear Simulator/Vessel Dynamics/M_inv/Inverse", 0, "",
    offsetof(BlockIO_LgV2, Inverse), BLOCKIO_SIG, 33, 9, 2, 262, 0 },

  { 132, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Product1", 0, "",
    offsetof(BlockIO_LgV2, Product1_h), BLOCKIO_SIG, 17, 3, 2, 264, 0 },

  { 133, "lgv2/Plants/Linear Simulator/u to tau/T_e/-l_x1", 0, "", offsetof
    (BlockIO_LgV2, l_x1_k), BLOCKIO_SIG, 0, 1, 2, 266, 0 },

  { 134, "lgv2/Plants/Linear Simulator/u to tau/T_e/-l_y2", 0, "", offsetof
    (BlockIO_LgV2, l_y2_g), BLOCKIO_SIG, 0, 1, 2, 268, 0 },

  { 135, "lgv2/Plants/Linear Simulator/u to tau/T_e/-l_x2", 0, "", offsetof
    (BlockIO_LgV2, l_x2_h), BLOCKIO_SIG, 0, 1, 2, 270, 0 },

  { 136, "lgv2/Plants/Linear Simulator/u to tau/T_e/3x5", 0, "", offsetof
    (BlockIO_LgV2, x5_m), BLOCKIO_SIG, 28, 15, 2, 272, 0 },

  { 137, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e1_hil", 0, "",
    offsetof(BlockIO_LgV2, GainK_e1_hil), BLOCKIO_SIG, 0, 1, 2, 274, 0 },

  { 138, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e2_hil", 0, "",
    offsetof(BlockIO_LgV2, GainK_e2_hil), BLOCKIO_SIG, 0, 1, 2, 276, 0 },

  { 139, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e3_hil", 0, "",
    offsetof(BlockIO_LgV2, GainK_e3_hil), BLOCKIO_SIG, 0, 1, 2, 278, 0 },

  { 140, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e4_hil", 0, "",
    offsetof(BlockIO_LgV2, GainK_e4_hil), BLOCKIO_SIG, 0, 1, 2, 280, 0 },

  { 141, "lgv2/Plants/Linear Simulator/u to tau/K_e/Gain K_e5_hil", 0, "",
    offsetof(BlockIO_LgV2, GainK_e5_hil), BLOCKIO_SIG, 0, 1, 2, 282, 0 },

  { 142, "lgv2/Plants/Linear Simulator/u to tau/K_e/Thruster Gain matrix", 0, "",
    offsetof(BlockIO_LgV2, ThrusterGainmatrix_m), BLOCKIO_SIG, 24, 25, 2, 284, 0
  },

  { 143,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/sample time", 0,
    "", offsetof(BlockIO_LgV2, sampletime), BLOCKIO_SIG, 0, 1, 2, 286, 0 },

  { 144,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Delay Input2", 0,
    "Y(k-1)", offsetof(BlockIO_LgV2, Yk1), BLOCKIO_SIG, 0, 1, 2, 288, 0 },

  { 145, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R11", 0, "",
    offsetof(BlockIO_LgV2, R11_i), BLOCKIO_SIG, 0, 1, 2, 290, 0 },

  { 146, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R21", 0, "",
    offsetof(BlockIO_LgV2, R21_l), BLOCKIO_SIG, 0, 1, 2, 292, 0 },

  { 147, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R12", 0, "",
    offsetof(BlockIO_LgV2, R12_g), BLOCKIO_SIG, 0, 1, 2, 294, 0 },

  { 148, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R22", 0, "",
    offsetof(BlockIO_LgV2, R22_i), BLOCKIO_SIG, 0, 1, 2, 296, 0 },

  { 149, "lgv2/Plants/Linear Simulator/Vessel Dynamics/R(psi)/R(psi)", 0, "",
    offsetof(BlockIO_LgV2, Rpsi), BLOCKIO_SIG, 33, 9, 2, 298, 0 },

  { 150, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Product3", 0, "",
    offsetof(BlockIO_LgV2, Product3), BLOCKIO_SIG, 17, 3, 2, 300, 0 },

  { 151, "lgv2/Plants/Linear Simulator/eta_surge_hil", 0, "", offsetof
    (BlockIO_LgV2, eta_surge_hil), BLOCKIO_SIG, 0, 1, 2, 302, 0 },

  { 152, "lgv2/Plants/Linear Simulator/eta_sway_hil", 0, "", offsetof
    (BlockIO_LgV2, eta_sway_hil), BLOCKIO_SIG, 0, 1, 2, 304, 0 },

  { 153, "lgv2/Plants/Linear Simulator/eta_yaw_hil", 0, "", offsetof
    (BlockIO_LgV2, eta_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 306, 0 },

  { 154, "lgv2/Plants/Linear Simulator/etadot_surge_hil", 0, "", offsetof
    (BlockIO_LgV2, etadot_surge_hil), BLOCKIO_SIG, 0, 1, 2, 308, 0 },

  { 155, "lgv2/Plants/Linear Simulator/etadot_sway_hil", 0, "", offsetof
    (BlockIO_LgV2, etadot_sway_hil), BLOCKIO_SIG, 0, 1, 2, 310, 0 },

  { 156, "lgv2/Plants/Linear Simulator/etadot_yaw_hil", 0, "", offsetof
    (BlockIO_LgV2, etadot_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 312, 0 },

  { 157, "lgv2/Plants/Linear Simulator/nu_surge_hil", 0, "", offsetof
    (BlockIO_LgV2, nu_surge_hil), BLOCKIO_SIG, 0, 1, 2, 314, 0 },

  { 158, "lgv2/Plants/Linear Simulator/nu_sway_hil", 0, "", offsetof
    (BlockIO_LgV2, nu_sway_hil), BLOCKIO_SIG, 0, 1, 2, 316, 0 },

  { 159, "lgv2/Plants/Linear Simulator/nu_yaw_hil", 0, "", offsetof(BlockIO_LgV2,
    nu_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 318, 0 },

  { 160, "lgv2/Plants/Linear Simulator/u to tau/Gain u_1", 0, "", offsetof
    (BlockIO_LgV2, Gainu_1), BLOCKIO_SIG, 0, 1, 2, 320, 0 },

  { 161, "lgv2/Plants/Linear Simulator/u to tau/Gain u_2", 0, "", offsetof
    (BlockIO_LgV2, Gainu_2), BLOCKIO_SIG, 0, 1, 2, 322, 0 },

  { 162, "lgv2/Plants/Linear Simulator/u to tau/Gain u_3", 0, "", offsetof
    (BlockIO_LgV2, Gainu_3), BLOCKIO_SIG, 0, 1, 2, 324, 0 },

  { 163, "lgv2/Plants/Linear Simulator/u to tau/Gain u_4", 0, "", offsetof
    (BlockIO_LgV2, Gainu_4), BLOCKIO_SIG, 0, 1, 2, 326, 0 },

  { 164, "lgv2/Plants/Linear Simulator/u to tau/Gain BT power", 0, "", offsetof
    (BlockIO_LgV2, GainBTpower), BLOCKIO_SIG, 0, 1, 2, 328, 0 },

  { 165,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/delta rise limit",
    0, "", offsetof(BlockIO_LgV2, deltariselimit), BLOCKIO_SIG, 0, 1, 2, 330, 0
  },

  { 166,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Difference Inputs1",
    0, "( U(k) - Y(k-1) )", offsetof(BlockIO_LgV2, UkYk1), BLOCKIO_SIG, 0, 1, 2,
    332, 0 },

  { 167, "lgv2/Plants/Linear Simulator/u to tau/Neg", 0, "", offsetof
    (BlockIO_LgV2, Neg), BLOCKIO_SIG, 0, 1, 2, 334, 0 },

  { 168,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/delta fall limit",
    0, "", offsetof(BlockIO_LgV2, deltafalllimit), BLOCKIO_SIG, 0, 1, 2, 336, 0
  },

  { 169,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_LgV2, Switch), BLOCKIO_SIG, 0, 1, 2, 338, 0 },

  { 170,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic/Switch2",
    0, "", offsetof(BlockIO_LgV2, Switch2), BLOCKIO_SIG, 0, 1, 2, 340, 0 },

  { 171,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Difference Inputs2",
    0, "", offsetof(BlockIO_LgV2, DifferenceInputs2), BLOCKIO_SIG, 0, 1, 2, 342,
    0 },

  { 172, "lgv2/Plants/Linear Simulator/u to tau/Gain u_5", 0, "", offsetof
    (BlockIO_LgV2, Gainu_5), BLOCKIO_SIG, 0, 1, 2, 344, 0 },

  { 173, "lgv2/Plants/Linear Simulator/u to tau/T_e^+ K_e^-1 u_e", 0, "",
    offsetof(BlockIO_LgV2, T_eK_e1u_e), BLOCKIO_SIG, 17, 3, 2, 346, 0 },

  { 174, "lgv2/Plants/Linear Simulator/u to tau/tau_surge_hil", 0, "", offsetof
    (BlockIO_LgV2, tau_surge_hil), BLOCKIO_SIG, 0, 1, 2, 348, 0 },

  { 175, "lgv2/Plants/Linear Simulator/u to tau/tau_sway_hil", 0, "", offsetof
    (BlockIO_LgV2, tau_sway_hil), BLOCKIO_SIG, 0, 1, 2, 350, 0 },

  { 176, "lgv2/Plants/Linear Simulator/u to tau/tau_yaw_hil", 0, "", offsetof
    (BlockIO_LgV2, tau_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 352, 0 },

  { 177, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Sum", 0, "", offsetof
    (BlockIO_LgV2, Sum_h), BLOCKIO_SIG, 17, 3, 2, 354, 0 },

  { 178, "lgv2/Plants/Linear Simulator/Vessel Dynamics/Product2", 0, "",
    offsetof(BlockIO_LgV2, Product2), BLOCKIO_SIG, 17, 3, 2, 356, 0 },

  { 179, "lgv2/Plants/Linear Simulator/u to tau/Cartesian to Polar Port/x->r", 0,
    "", offsetof(BlockIO_LgV2, xr), BLOCKIO_SIG, 0, 1, 2, 358, 0 },

  { 180,
    "lgv2/Plants/Linear Simulator/u to tau/Cartesian to Polar Port/x->theta", 0,
    "", offsetof(BlockIO_LgV2, xtheta), BLOCKIO_SIG, 0, 1, 2, 360, 0 },

  { 181, "lgv2/Plants/Linear Simulator/u to tau/Cartesian to Polar Stbd/x->r", 0,
    "", offsetof(BlockIO_LgV2, xr_l), BLOCKIO_SIG, 0, 1, 2, 362, 0 },

  { 182,
    "lgv2/Plants/Linear Simulator/u to tau/Cartesian to Polar Stbd/x->theta", 0,
    "", offsetof(BlockIO_LgV2, xtheta_j), BLOCKIO_SIG, 0, 1, 2, 364, 0 },

  { 183, "lgv2/Plants/Linear Simulator/u to tau/VSP_angle_deg_port", 0, "",
    offsetof(BlockIO_LgV2, VSP_angle_deg_port), BLOCKIO_SIG, 0, 1, 2, 366, 0 },

  { 184, "lgv2/Plants/Linear Simulator/u to tau/VSP_angle_deg_stbd", 0, "",
    offsetof(BlockIO_LgV2, VSP_angle_deg_stbd), BLOCKIO_SIG, 0, 1, 2, 368, 0 },

  { 185, "lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain1", 0, "", offsetof
    (BlockIO_LgV2, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2, 370, 0 },

  { 186, "lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain2", 0, "", offsetof
    (BlockIO_LgV2, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2, 372, 0 },

  { 187, "lgv2/Plants/CSE1/Bow Thruster/Add", 0, "", offsetof(BlockIO_LgV2, Add),
    BLOCKIO_SIG, 0, 1, 2, 374, 0 },

  { 188, "lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain1", 0, "", offsetof
    (BlockIO_LgV2, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2, 376, 0 },

  { 189, "lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain2", 0, "", offsetof
    (BlockIO_LgV2, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2, 378, 0 },

  { 190, "lgv2/Plants/CSE1/Bow Thruster/Neg", 0, "", offsetof(BlockIO_LgV2,
    Neg_b), BLOCKIO_SIG, 0, 1, 2, 380, 0 },

  { 191, "lgv2/Plants/CSE1/Bow Thruster/Sum1", 0, "", offsetof(BlockIO_LgV2,
    Sum1_k), BLOCKIO_SIG, 0, 1, 2, 382, 0 },

  { 192, "lgv2/Plants/CSE1/Bow Thruster/Sum2", 0, "", offsetof(BlockIO_LgV2,
    Sum2_m), BLOCKIO_SIG, 0, 1, 2, 384, 0 },

  { 193, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch", 0, "",
    offsetof(BlockIO_LgV2, Switch_i), BLOCKIO_SIG, 0, 1, 2, 386, 0 },

  { 194, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch2", 0, "",
    offsetof(BlockIO_LgV2, Switch2_d), BLOCKIO_SIG, 0, 1, 2, 388, 0 },

  { 195, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch", 0, "",
    offsetof(BlockIO_LgV2, Switch_d), BLOCKIO_SIG, 0, 1, 2, 390, 0 },

  { 196, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch2", 0, "",
    offsetof(BlockIO_LgV2, Switch2_p), BLOCKIO_SIG, 0, 1, 2, 392, 0 },

  { 197, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch", 0, "",
    offsetof(BlockIO_LgV2, Switch_d3), BLOCKIO_SIG, 0, 1, 2, 394, 0 },

  { 198, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch2", 0, "",
    offsetof(BlockIO_LgV2, Switch2_o), BLOCKIO_SIG, 0, 1, 2, 396, 0 },

  { 199, "lgv2/Plants/CSE1/Voith Schneider Propeller /Sign", 0, "", offsetof
    (BlockIO_LgV2, Sign), BLOCKIO_SIG, 0, 1, 2, 398, 0 },

  { 200, "lgv2/Plants/CSE1/Voith Schneider Propeller /Product1", 0, "Port VPS_X",
    offsetof(BlockIO_LgV2, PortVPS_X), BLOCKIO_SIG, 0, 1, 2, 400, 0 },

  { 201, "lgv2/Plants/CSE1/Voith Schneider Propeller /-x", 0, "Port VPS_X",
    offsetof(BlockIO_LgV2, PortVPS_X_n), BLOCKIO_SIG, 0, 1, 2, 402, 0 },

  { 202, "lgv2/Plants/CSE1/Voith Schneider Propeller /Product2", 0, "Port VSP_Y",
    offsetof(BlockIO_LgV2, PortVSP_Y), BLOCKIO_SIG, 0, 1, 2, 404, 0 },

  { 203, "lgv2/Plants/CSE1/Voith Schneider Propeller /-y", 0, "Port VSP_Y",
    offsetof(BlockIO_LgV2, PortVSP_Y_b), BLOCKIO_SIG, 0, 1, 2, 406, 0 },

  { 204,
    "lgv2/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Port/x->r",
    0, "", offsetof(BlockIO_LgV2, xr_n), BLOCKIO_SIG, 0, 1, 2, 408, 0 },

  { 205,
    "lgv2/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Port/x->theta",
    0, "", offsetof(BlockIO_LgV2, xtheta_i), BLOCKIO_SIG, 0, 1, 2, 410, 0 },

  { 206, "lgv2/Plants/CSE1/Voith Schneider Propeller /Product3", 0,
    "Starboard VSP_X", offsetof(BlockIO_LgV2, StarboardVSP_X), BLOCKIO_SIG, 0, 1,
    2, 412, 0 },

  { 207, "lgv2/Plants/CSE1/Voith Schneider Propeller /Product4", 0,
    "Starboard VSP_Y", offsetof(BlockIO_LgV2, StarboardVSP_Y), BLOCKIO_SIG, 0, 1,
    2, 414, 0 },

  { 208,
    "lgv2/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Starboard/x->r",
    0, "", offsetof(BlockIO_LgV2, xr_h), BLOCKIO_SIG, 0, 1, 2, 416, 0 },

  { 209,
    "lgv2/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Starboard/x->theta",
    0, "", offsetof(BlockIO_LgV2, xtheta_n), BLOCKIO_SIG, 0, 1, 2, 418, 0 },

  { 210,
    "lgv2/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain), BLOCKIO_SIG, 0, 1, 2, 420, 0 },

  { 211,
    "lgv2/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_i), BLOCKIO_SIG, 0, 1, 2, 422, 0 },

  { 212, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1", 0, "", offsetof
    (BlockIO_LgV2, Servo1), BLOCKIO_SIG, 0, 1, 2, 424, 0 },

  { 213, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2", 0, "", offsetof
    (BlockIO_LgV2, Servo2), BLOCKIO_SIG, 0, 1, 2, 426, 0 },

  { 214, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3", 0, "", offsetof
    (BlockIO_LgV2, Servo3), BLOCKIO_SIG, 0, 1, 2, 428, 0 },

  { 215, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4", 0, "", offsetof
    (BlockIO_LgV2, Servo4), BLOCKIO_SIG, 0, 1, 2, 430, 0 },

  { 216, "lgv2/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain", 0, "",
    offsetof(BlockIO_LgV2, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2, 432, 0 },

  { 217, "lgv2/Plants/CSE1/Voith Schneider Propeller /Sum", 0, "", offsetof
    (BlockIO_LgV2, Sum_d), BLOCKIO_SIG, 0, 1, 2, 434, 0 },

  { 218, "lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Port", 0, "",
    offsetof(BlockIO_LgV2, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 436, 0 },

  { 219, "lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard", 0, "",
    offsetof(BlockIO_LgV2, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2, 438, 0 },

  { 220, "lgv2/Plants/CSE1/T_e/-l_x1", 0, "", offsetof(BlockIO_LgV2, l_x1_b),
    BLOCKIO_SIG, 0, 1, 2, 440, 0 },

  { 221, "lgv2/Plants/CSE1/T_e/-l_y2", 0, "", offsetof(BlockIO_LgV2, l_y2_h),
    BLOCKIO_SIG, 0, 1, 2, 442, 0 },

  { 222, "lgv2/Plants/CSE1/T_e/-l_x2", 0, "", offsetof(BlockIO_LgV2, l_x2_p),
    BLOCKIO_SIG, 0, 1, 2, 444, 0 },

  { 223, "lgv2/Plants/CSE1/T_e/3x5", 0, "", offsetof(BlockIO_LgV2, x5_n),
    BLOCKIO_SIG, 28, 15, 2, 446, 0 },

  { 224, "lgv2/Plants/CSE1/K_e/Gain K_e1_CSE1", 0, "", offsetof(BlockIO_LgV2,
    GainK_e1_CSE1), BLOCKIO_SIG, 0, 1, 2, 448, 0 },

  { 225, "lgv2/Plants/CSE1/K_e/Gain K_e2_CSE1", 0, "", offsetof(BlockIO_LgV2,
    GainK_e2_CSE1), BLOCKIO_SIG, 0, 1, 2, 450, 0 },

  { 226, "lgv2/Plants/CSE1/K_e/Gain K_e3_CSE1", 0, "", offsetof(BlockIO_LgV2,
    GainK_e3_CSE1), BLOCKIO_SIG, 0, 1, 2, 452, 0 },

  { 227, "lgv2/Plants/CSE1/K_e/Gain K_e4_CSE1", 0, "", offsetof(BlockIO_LgV2,
    GainK_e4_CSE1), BLOCKIO_SIG, 0, 1, 2, 454, 0 },

  { 228, "lgv2/Plants/CSE1/K_e/Gain K_e5_CSE1", 0, "", offsetof(BlockIO_LgV2,
    GainK_e5_CSE1), BLOCKIO_SIG, 0, 1, 2, 456, 0 },

  { 229, "lgv2/Plants/CSE1/K_e/Thruster Gain matrix", 0, "", offsetof
    (BlockIO_LgV2, ThrusterGainmatrix_mz), BLOCKIO_SIG, 24, 25, 2, 458, 0 },

  { 230, "lgv2/Plants/CSE1/tau_cse1", 0, "", offsetof(BlockIO_LgV2, tau_cse1),
    BLOCKIO_SIG, 17, 3, 2, 460, 0 },

  { 231, "lgv2/Plants/CSE1/CSE1 tau_surge", 0, "", offsetof(BlockIO_LgV2,
    CSE1tau_surge), BLOCKIO_SIG, 0, 1, 2, 462, 0 },

  { 232, "lgv2/Plants/CSE1/CSE1 tau_sway", 0, "", offsetof(BlockIO_LgV2,
    CSE1tau_sway), BLOCKIO_SIG, 0, 1, 2, 464, 0 },

  { 233, "lgv2/Plants/CSE1/CSE1 tau_yaw", 0, "", offsetof(BlockIO_LgV2,
    CSE1tau_yaw), BLOCKIO_SIG, 0, 1, 2, 466, 0 },

  { 234, "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator1",
    0, "eta_w", offsetof(BlockIO_LgV2, eta_w), BLOCKIO_SIG, 17, 3, 2, 468, 0 },

  { 235, "lgv2/Control Systems/DP control/BT_power_limit", 0, "", offsetof
    (BlockIO_LgV2, BT_power_limit), BLOCKIO_SIG, 0, 1, 2, 470, 0 },

  { 236, "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator", 0,
    "eta", offsetof(BlockIO_LgV2, eta), BLOCKIO_SIG, 17, 3, 2, 472, 0 },

  { 237,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_j), BLOCKIO_SIG, 0, 1, 2, 474, 0 },

  { 238,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_l), BLOCKIO_SIG, 0, 1, 2, 476, 0 },

  { 239,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_d), BLOCKIO_SIG, 0, 1, 2, 478, 0 },

  { 240,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_e), BLOCKIO_SIG, 0, 1, 2, 480, 0 },

  { 241,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction), BLOCKIO_SIG, 0, 1, 2, 482, 0 },

  { 242,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_n), BLOCKIO_SIG, 0, 1, 2, 484, 0 },

  { 243, "lgv2/Control Systems/DP control/Multiport Switch", 0, "", offsetof
    (BlockIO_LgV2, MultiportSwitch_p), BLOCKIO_SIG, 17, 3, 2, 486, 0 },

  { 244, "lgv2/Control Systems/DP control/DP controller/eta N", 0, "", offsetof
    (BlockIO_LgV2, etaN), BLOCKIO_SIG, 0, 1, 2, 488, 0 },

  { 245, "lgv2/Control Systems/DP control/DP controller/eta E", 0, "", offsetof
    (BlockIO_LgV2, etaE), BLOCKIO_SIG, 0, 1, 2, 490, 0 },

  { 246, "lgv2/Control Systems/DP control/DP controller/eta Psi", 0, "",
    offsetof(BlockIO_LgV2, etaPsi), BLOCKIO_SIG, 0, 1, 2, 492, 0 },

  { 247, "lgv2/Control Systems/DP control/DP controller/Sum2", 0,
    "regulation error", offsetof(BlockIO_LgV2, regulationerror), BLOCKIO_SIG, 17,
    3, 2, 494, 0 },

  { 248, "lgv2/Control Systems/DP control/DP controller/Reg_e_N_hil", 0, "",
    offsetof(BlockIO_LgV2, Reg_e_N_hil), BLOCKIO_SIG, 0, 1, 2, 496, 0 },

  { 249, "lgv2/Control Systems/DP control/DP controller/Reg_e_E_hil", 0, "",
    offsetof(BlockIO_LgV2, Reg_e_E_hil), BLOCKIO_SIG, 0, 1, 2, 498, 0 },

  { 250, "lgv2/Control Systems/DP control/DP controller/Reg_e_Psi_hil", 0, "",
    offsetof(BlockIO_LgV2, Reg_e_Psi_hil), BLOCKIO_SIG, 0, 1, 2, 500, 0 },

  { 251, "lgv2/Control Systems/DP control/DP controller/Integrator", 0, "",
    offsetof(BlockIO_LgV2, Integrator_g), BLOCKIO_SIG, 17, 3, 2, 502, 0 },

  { 252, "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator4",
    0, "nu", offsetof(BlockIO_LgV2, nu), BLOCKIO_SIG, 17, 3, 2, 504, 0 },

  { 253, "lgv2/Control Systems/DP control/Multiport Switch1", 0, "", offsetof
    (BlockIO_LgV2, MultiportSwitch1), BLOCKIO_SIG, 17, 3, 2, 506, 0 },

  { 254, "lgv2/Control Systems/DP control/DP controller/Kd", 0, "", offsetof
    (BlockIO_LgV2, Kd), BLOCKIO_SIG, 17, 3, 2, 508, 0 },

  { 255, "lgv2/Control Systems/DP control/DP controller/Product", 0, "",
    offsetof(BlockIO_LgV2, Product_d), BLOCKIO_SIG, 17, 3, 2, 510, 0 },

  { 256, "lgv2/Control Systems/DP control/DP controller/K_d 1", 0, "", offsetof
    (BlockIO_LgV2, K_d1), BLOCKIO_SIG, 0, 1, 2, 512, 0 },

  { 257, "lgv2/Control Systems/DP control/DP controller/K_d 2", 0, "", offsetof
    (BlockIO_LgV2, K_d2), BLOCKIO_SIG, 0, 1, 2, 514, 0 },

  { 258, "lgv2/Control Systems/DP control/DP controller/K_d 3", 0, "", offsetof
    (BlockIO_LgV2, K_d3), BLOCKIO_SIG, 0, 1, 2, 516, 0 },

  { 259, "lgv2/Control Systems/DP control/DP controller/K_d 3 deg", 0, "",
    offsetof(BlockIO_LgV2, K_d3deg), BLOCKIO_SIG, 0, 1, 2, 518, 0 },

  { 260, "lgv2/Control Systems/DP control/DP controller/Ki", 0, "", offsetof
    (BlockIO_LgV2, Ki), BLOCKIO_SIG, 17, 3, 2, 520, 0 },

  { 261, "lgv2/Control Systems/DP control/DP controller/Product1", 0, "",
    offsetof(BlockIO_LgV2, Product1_c), BLOCKIO_SIG, 17, 3, 2, 522, 0 },

  { 262, "lgv2/Control Systems/DP control/DP controller/K_i 1", 0, "", offsetof
    (BlockIO_LgV2, K_i1), BLOCKIO_SIG, 0, 1, 2, 524, 0 },

  { 263, "lgv2/Control Systems/DP control/DP controller/K_i 2", 0, "", offsetof
    (BlockIO_LgV2, K_i2), BLOCKIO_SIG, 0, 1, 2, 526, 0 },

  { 264, "lgv2/Control Systems/DP control/DP controller/K_i 3", 0, "", offsetof
    (BlockIO_LgV2, K_i3), BLOCKIO_SIG, 0, 1, 2, 528, 0 },

  { 265, "lgv2/Control Systems/DP control/DP controller/K_i 3 deg", 0, "",
    offsetof(BlockIO_LgV2, K_i3deg), BLOCKIO_SIG, 0, 1, 2, 530, 0 },

  { 266, "lgv2/Control Systems/DP control/DP controller/yaw angle", 0, "psi",
    offsetof(BlockIO_LgV2, psi), BLOCKIO_SIG, 0, 1, 2, 532, 0 },

  { 267,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_h), BLOCKIO_SIG, 0, 1, 2, 534, 0 },

  { 268,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_a), BLOCKIO_SIG, 0, 1, 2, 536, 0 },

  { 269,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_j), BLOCKIO_SIG, 0, 1, 2, 538, 0 },

  { 270,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_i), BLOCKIO_SIG, 0, 1, 2, 540, 0 },

  { 271,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_i), BLOCKIO_SIG, 0, 1, 2, 542, 0
  },

  { 272,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_b), BLOCKIO_SIG, 0, 1, 2, 544, 0 },

  { 273,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_m), BLOCKIO_SIG, 0, 1, 2, 546, 0 },

  { 274,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_j), BLOCKIO_SIG, 0, 1, 2, 548, 0 },

  { 275,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_a), BLOCKIO_SIG, 0, 1, 2, 550, 0 },

  { 276,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_p), BLOCKIO_SIG, 0, 1, 2, 552, 0 },

  { 277,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_d), BLOCKIO_SIG, 0, 1, 2, 554, 0
  },

  { 278,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_j), BLOCKIO_SIG, 0, 1, 2, 556, 0 },

  { 279,
    "lgv2/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_LgV2, Row1), BLOCKIO_SIG, 0, 1, 2, 558, 0 },

  { 280,
    "lgv2/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_LgV2, Row2), BLOCKIO_SIG, 0, 1, 2, 560, 0 },

  { 281,
    "lgv2/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_LgV2, Row3), BLOCKIO_SIG, 0, 1, 2, 562, 0 },

  { 282, "lgv2/Control Systems/DP control/DP controller/Kp", 0, "", offsetof
    (BlockIO_LgV2, Kp), BLOCKIO_SIG, 17, 3, 2, 564, 0 },

  { 283, "lgv2/Control Systems/DP control/DP controller/Product2", 0, "",
    offsetof(BlockIO_LgV2, Product2_m), BLOCKIO_SIG, 17, 3, 2, 566, 0 },

  { 284, "lgv2/Control Systems/DP control/DP controller/K_p 1", 0, "", offsetof
    (BlockIO_LgV2, K_p1), BLOCKIO_SIG, 0, 1, 2, 568, 0 },

  { 285, "lgv2/Control Systems/DP control/DP controller/K_p 2", 0, "", offsetof
    (BlockIO_LgV2, K_p2), BLOCKIO_SIG, 0, 1, 2, 570, 0 },

  { 286, "lgv2/Control Systems/DP control/DP controller/K_p 3", 0, "", offsetof
    (BlockIO_LgV2, K_p3), BLOCKIO_SIG, 0, 1, 2, 572, 0 },

  { 287, "lgv2/Control Systems/DP control/DP controller/K_p 3 deg", 0, "",
    offsetof(BlockIO_LgV2, K_p3deg), BLOCKIO_SIG, 0, 1, 2, 574, 0 },

  { 288, "lgv2/Control Systems/DP control/DP controller/Reg_e_Psi_deg", 0, "",
    offsetof(BlockIO_LgV2, Reg_e_Psi_deg), BLOCKIO_SIG, 0, 1, 2, 576, 0 },

  { 289, "lgv2/Control Systems/DP control/DP controller/Sum3", 0, "", offsetof
    (BlockIO_LgV2, Sum3), BLOCKIO_SIG, 17, 3, 2, 578, 0 },

  { 290, "lgv2/Control Systems/DP control/DP controller/Sum1", 0, "", offsetof
    (BlockIO_LgV2, Sum1_j), BLOCKIO_SIG, 17, 3, 2, 580, 0 },

  { 291, "lgv2/Control Systems/DP control/DP controller/eta Psi deg", 0, "",
    offsetof(BlockIO_LgV2, etaPsideg), BLOCKIO_SIG, 0, 1, 2, 582, 0 },

  { 292, "lgv2/Control Systems/DP control/DP tau_surge", 0, "", offsetof
    (BlockIO_LgV2, DPtau_surge), BLOCKIO_SIG, 0, 1, 2, 584, 0 },

  { 293, "lgv2/Control Systems/DP control/DP tau_sway", 0, "", offsetof
    (BlockIO_LgV2, DPtau_sway), BLOCKIO_SIG, 0, 1, 2, 586, 0 },

  { 294, "lgv2/Control Systems/DP control/DP tau_yaw", 0, "", offsetof
    (BlockIO_LgV2, DPtau_yaw), BLOCKIO_SIG, 0, 1, 2, 588, 0 },

  { 295, "lgv2/Control Systems/DP control/K_e/Gain K_e1_DP", 0, "", offsetof
    (BlockIO_LgV2, GainK_e1_DP), BLOCKIO_SIG, 0, 1, 2, 590, 0 },

  { 296, "lgv2/Control Systems/DP control/K_e/Gain K_e2_DP", 0, "", offsetof
    (BlockIO_LgV2, GainK_e2_DP), BLOCKIO_SIG, 0, 1, 2, 592, 0 },

  { 297, "lgv2/Control Systems/DP control/K_e/Gain K_e3_DP", 0, "", offsetof
    (BlockIO_LgV2, GainK_e3_DP), BLOCKIO_SIG, 0, 1, 2, 594, 0 },

  { 298, "lgv2/Control Systems/DP control/K_e/Gain K_e4_DP", 0, "", offsetof
    (BlockIO_LgV2, GainK_e4_DP), BLOCKIO_SIG, 0, 1, 2, 596, 0 },

  { 299, "lgv2/Control Systems/DP control/K_e/Gain K_e5_DP", 0, "", offsetof
    (BlockIO_LgV2, GainK_e5_DP), BLOCKIO_SIG, 0, 1, 2, 598, 0 },

  { 300, "lgv2/Control Systems/DP control/K_e/Thruster Gain matrix", 0, "",
    offsetof(BlockIO_LgV2, ThrusterGainmatrix_o), BLOCKIO_SIG, 24, 25, 2, 600, 0
  },

  { 301, "lgv2/Control Systems/DP control/K_e^-1", 0, "", offsetof(BlockIO_LgV2,
    K_e1_g), BLOCKIO_SIG, 24, 25, 2, 602, 0 },

  { 302, "lgv2/Control Systems/DP control/T_e/-l_x1", 0, "", offsetof
    (BlockIO_LgV2, l_x1_m), BLOCKIO_SIG, 0, 1, 2, 604, 0 },

  { 303, "lgv2/Control Systems/DP control/T_e/-l_y2", 0, "", offsetof
    (BlockIO_LgV2, l_y2_f), BLOCKIO_SIG, 0, 1, 2, 606, 0 },

  { 304, "lgv2/Control Systems/DP control/T_e/-l_x2", 0, "", offsetof
    (BlockIO_LgV2, l_x2_k), BLOCKIO_SIG, 0, 1, 2, 608, 0 },

  { 305, "lgv2/Control Systems/DP control/T_e/3x5", 0, "", offsetof(BlockIO_LgV2,
    x5_j), BLOCKIO_SIG, 28, 15, 2, 610, 0 },

  { 306, "lgv2/Control Systems/DP control/T_e^+", 0, "", offsetof(BlockIO_LgV2,
    T_e_d), BLOCKIO_SIG, 27, 15, 2, 612, 0 },

  { 307, "lgv2/Control Systems/DP control/Product", 0, "", offsetof(BlockIO_LgV2,
    Product_c), BLOCKIO_SIG, 27, 15, 2, 614, 0 },

  { 308, "lgv2/Control Systems/DP control/Product1", 0, "", offsetof
    (BlockIO_LgV2, Product1_i), BLOCKIO_SIG, 23, 5, 2, 616, 0 },

  { 309, "lgv2/Control Systems/DP control/DP u_1", 0, "", offsetof(BlockIO_LgV2,
    DPu_1), BLOCKIO_SIG, 0, 1, 2, 618, 0 },

  { 310, "lgv2/Control Systems/DP control/DP u_2", 0, "", offsetof(BlockIO_LgV2,
    DPu_2), BLOCKIO_SIG, 0, 1, 2, 620, 0 },

  { 311, "lgv2/Control Systems/DP control/DP u_3", 0, "", offsetof(BlockIO_LgV2,
    DPu_3), BLOCKIO_SIG, 0, 1, 2, 622, 0 },

  { 312, "lgv2/Control Systems/DP control/DP u_4", 0, "", offsetof(BlockIO_LgV2,
    DPu_4), BLOCKIO_SIG, 0, 1, 2, 624, 0 },

  { 313, "lgv2/Control Systems/DP control/DP u_5", 0, "", offsetof(BlockIO_LgV2,
    DPu_5), BLOCKIO_SIG, 0, 1, 2, 626, 0 },

  { 314, "lgv2/Control Systems/DP control/Passive DP wave filter1/Gain1", 0, "",
    offsetof(BlockIO_LgV2, Gain1_g), BLOCKIO_SIG, 17, 3, 2, 628, 0 },

  { 315, "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator2",
    0, "xi_w", offsetof(BlockIO_LgV2, xi_w), BLOCKIO_SIG, 17, 3, 2, 630, 0 },

  { 316, "lgv2/Control Systems/DP control/Passive DP wave filter1/Gain2", 0, "",
    offsetof(BlockIO_LgV2, Gain2), BLOCKIO_SIG, 17, 3, 2, 632, 0 },

  { 317, "lgv2/Control Systems/DP control/Passive DP wave filter1/Sum4", 0, "",
    offsetof(BlockIO_LgV2, Sum4), BLOCKIO_SIG, 17, 3, 2, 634, 0 },

  { 318, "lgv2/Control Systems/DP control/Passive DP wave filter1/Sum2", 0, "",
    offsetof(BlockIO_LgV2, Sum2_d), BLOCKIO_SIG, 17, 3, 2, 636, 0 },

  { 319,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_ho), BLOCKIO_SIG, 0, 1, 2, 638, 0 },

  { 320,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_jh), BLOCKIO_SIG, 0, 1, 2, 640, 0 },

  { 321,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_it), BLOCKIO_SIG, 0, 1, 2, 642, 0 },

  { 322,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_pt), BLOCKIO_SIG, 0, 1, 2, 644, 0 },

  { 323,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_c), BLOCKIO_SIG, 0, 1, 2, 646, 0
  },

  { 324,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_hw), BLOCKIO_SIG, 0, 1, 2, 648, 0 },

  { 325, "lgv2/Control Systems/DP control/Passive DP wave filter1/K4", 0, "",
    offsetof(BlockIO_LgV2, K4), BLOCKIO_SIG, 17, 3, 2, 650, 0 },

  { 326,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row1",
    0, "", offsetof(BlockIO_LgV2, Row1_b), BLOCKIO_SIG, 0, 1, 2, 652, 0 },

  { 327,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row2",
    0, "", offsetof(BlockIO_LgV2, Row2_d), BLOCKIO_SIG, 0, 1, 2, 654, 0 },

  { 328,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row3",
    0, "", offsetof(BlockIO_LgV2, Row3_h), BLOCKIO_SIG, 0, 1, 2, 656, 0 },

  { 329, "lgv2/Control Systems/DP control/Passive DP wave filter1/Integrator3",
    0, "bias", offsetof(BlockIO_LgV2, bias), BLOCKIO_SIG, 17, 3, 2, 658, 0 },

  { 330,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_LgV2, Row1_g), BLOCKIO_SIG, 0, 1, 2, 660, 0 },

  { 331,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_LgV2, Row2_b), BLOCKIO_SIG, 0, 1, 2, 662, 0 },

  { 332,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_LgV2, Row3_p), BLOCKIO_SIG, 0, 1, 2, 664, 0 },

  { 333, "lgv2/Control Systems/DP control/Passive DP wave filter1/Sum1", 0, "",
    offsetof(BlockIO_LgV2, Sum1_g), BLOCKIO_SIG, 17, 3, 2, 666, 0 },

  { 334, "lgv2/Control Systems/DP control/Passive DP wave filter1/Gain6", 0, "",
    offsetof(BlockIO_LgV2, Gain6), BLOCKIO_SIG, 17, 3, 2, 668, 0 },

  { 335, "lgv2/Control Systems/DP control/Passive DP wave filter1/Sum8", 0, "",
    offsetof(BlockIO_LgV2, Sum8), BLOCKIO_SIG, 17, 3, 2, 670, 0 },

  { 336, "lgv2/Control Systems/DP control/Passive DP wave filter1/Gain3", 0, "",
    offsetof(BlockIO_LgV2, Gain3), BLOCKIO_SIG, 17, 3, 2, 672, 0 },

  { 337, "lgv2/Control Systems/DP control/Passive DP wave filter1/K11", 0, "",
    offsetof(BlockIO_LgV2, K11), BLOCKIO_SIG, 17, 3, 2, 674, 0 },

  { 338, "lgv2/Control Systems/DP control/Passive DP wave filter1/K12", 0, "",
    offsetof(BlockIO_LgV2, K12), BLOCKIO_SIG, 17, 3, 2, 676, 0 },

  { 339, "lgv2/Control Systems/DP control/Passive DP wave filter1/K2", 0, "",
    offsetof(BlockIO_LgV2, K2), BLOCKIO_SIG, 17, 3, 2, 678, 0 },

  { 340, "lgv2/Control Systems/DP control/Passive DP wave filter1/K3", 0, "",
    offsetof(BlockIO_LgV2, K3), BLOCKIO_SIG, 17, 3, 2, 680, 0 },

  { 341,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn",
    0, "x_dot", offsetof(BlockIO_LgV2, x_dot), BLOCKIO_SIG, 0, 1, 2, 682, 0 },

  { 342,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn1",
    0, "y_dot", offsetof(BlockIO_LgV2, y_dot), BLOCKIO_SIG, 0, 1, 2, 684, 0 },

  { 343,
    "lgv2/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn2",
    0, "psi_dot", offsetof(BlockIO_LgV2, psi_dot), BLOCKIO_SIG, 0, 1, 2, 686, 0
  },

  { 344, "lgv2/Control Systems/DP control/Passive DP wave filter1/Sum3", 0, "",
    offsetof(BlockIO_LgV2, Sum3_h), BLOCKIO_SIG, 17, 3, 2, 688, 0 },

  { 345, "lgv2/Control Systems/DP control/Passive DP wave filter1/Sum5", 0,
    "psi_WF", offsetof(BlockIO_LgV2, psi_WF), BLOCKIO_SIG, 17, 3, 2, 690, 0 },

  { 346, "lgv2/Control Systems/DP control/Passive DP wave filter1/Sum6", 0, "",
    offsetof(BlockIO_LgV2, Sum6), BLOCKIO_SIG, 17, 3, 2, 692, 0 },

  { 347, "lgv2/Control Systems/DP control/Passive DP wave filter1/inv(T_b)", 0,
    "", offsetof(BlockIO_LgV2, invT_b), BLOCKIO_SIG, 17, 3, 2, 694, 0 },

  { 348, "lgv2/Control Systems/DP control/Passive DP wave filter1/Sum7", 0, "",
    offsetof(BlockIO_LgV2, Sum7), BLOCKIO_SIG, 17, 3, 2, 696, 0 },

  { 349, "lgv2/Control Systems/DP control/Saturation", 0, "", offsetof
    (BlockIO_LgV2, Saturation_p), BLOCKIO_SIG, 23, 5, 2, 698, 0 },

  { 350, "lgv2/Control Systems/DP control/VSP_speeds", 0, "", offsetof
    (BlockIO_LgV2, VSP_speeds), BLOCKIO_SIG, 0, 1, 2, 700, 0 },

  { 351, "lgv2/Control Systems/if DP Control Mode/Compare", 0, "", offsetof
    (BlockIO_LgV2, Compare), BLOCKIO_SIG, 3, 1, 2, 702, 0 },

  { 352,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_LgV2, LowerRelop1), BLOCKIO_SIG, 8, 1, 2, 704, 0 },

  { 353,
    "lgv2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_LgV2, UpperRelop), BLOCKIO_SIG, 8, 1, 2, 706, 0 },

  { 354, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic/LowerRelop1", 0, "",
    offsetof(BlockIO_LgV2, LowerRelop1_n), BLOCKIO_SIG, 8, 1, 2, 708, 0 },

  { 355, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic/UpperRelop", 0, "",
    offsetof(BlockIO_LgV2, UpperRelop_m), BLOCKIO_SIG, 8, 1, 2, 710, 0 },

  { 356, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic1/LowerRelop1", 0, "",
    offsetof(BlockIO_LgV2, LowerRelop1_j), BLOCKIO_SIG, 8, 1, 2, 712, 0 },

  { 357, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic1/UpperRelop", 0, "",
    offsetof(BlockIO_LgV2, UpperRelop_b), BLOCKIO_SIG, 8, 1, 2, 714, 0 },

  { 358, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic2/LowerRelop1", 0, "",
    offsetof(BlockIO_LgV2, LowerRelop1_b), BLOCKIO_SIG, 8, 1, 2, 716, 0 },

  { 359, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic2/UpperRelop", 0, "",
    offsetof(BlockIO_LgV2, UpperRelop_h), BLOCKIO_SIG, 8, 1, 2, 718, 0 },

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

static char* NI_CompiledModelName = "lgv2";
static char* NI_CompiledModelVersion = "1.198";
static char* NI_CompiledModelDateTime = "Wed Nov 27 14:51:19 2013";

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
