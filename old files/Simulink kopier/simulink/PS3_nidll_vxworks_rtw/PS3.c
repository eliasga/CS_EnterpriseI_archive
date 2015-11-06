/*
 * PS3.c
 *
 * Real-Time Workshop code generation for Simulink model "PS3.mdl".
 *
 * Model Version              : 1.6
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 16:15:49 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PS3.h"
#include "PS3_private.h"

/* Block signals (auto storage) */
BlockIO_PS3 PS3_B;

/* Block states (auto storage) */
D_Work_PS3 PS3_DWork;

/* Real-time model */
RT_MODEL_PS3 PS3_M_;
RT_MODEL_PS3 *PS3_M = &PS3_M_;

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

/* Model output function */
static void PS3_output(int_T tid)
{
  {
    real_T tmp[5];
    int32_T i;
    real_T tmp_0;

    /* Gain: '<S4>/ScalingLY' incorporates:
     *  Constant: '<S4>/AS_LY'
     */
    PS3_B.ypositionofleftanalogstick11 = PS3_P.ScalingLY_Gain *
      PS3_P.AS_LY_Value;

    /* Gain: '<S6>/PS3 u_1' */
    PS3_B.u_1 = PS3_P.PS3u_1_Gain * PS3_B.ypositionofleftanalogstick11;

    /* Gain: '<S4>/ScalingLX' incorporates:
     *  Constant: '<S4>/AS_LX'
     */
    PS3_B.xpositionofleftanalogstick11 = PS3_P.ScalingLX_Gain *
      PS3_P.AS_LX_Value;

    /* Gain: '<S6>/PS3 u_2' */
    PS3_B.u_2 = PS3_P.PS3u_2_Gain * PS3_B.xpositionofleftanalogstick11;

    /* Gain: '<S4>/ScalingRY' incorporates:
     *  Constant: '<S4>/AS_RY'
     */
    PS3_B.ypositionofrightanalogstick11 = PS3_P.ScalingRY_Gain *
      PS3_P.AS_RY_Value;

    /* Gain: '<S6>/PS3 u_3' */
    PS3_B.u_3 = PS3_P.PS3u_3_Gain * PS3_B.ypositionofrightanalogstick11;

    /* Gain: '<S4>/Scaling_RX' incorporates:
     *  Constant: '<S4>/AS_RX'
     */
    PS3_B.xpositionofrightanalogstick11 = PS3_P.Scaling_RX_Gain *
      PS3_P.AS_RX_Value;

    /* Gain: '<S6>/PS3 u_4' */
    PS3_B.u_4 = PS3_P.PS3u_4_Gain * PS3_B.xpositionofrightanalogstick11;

    /* Sum: '<S6>/Add' incorporates:
     *  Constant: '<S4>/L2'
     *  Constant: '<S4>/R2'
     */
    PS3_B.BowThrusterdirection = PS3_P.L2_Value + PS3_P.R2_Value;

    /* Gain: '<S6>/PS3 u_5' */
    PS3_B.u_5 = PS3_P.PS3u_5_Gain * PS3_B.BowThrusterdirection;

    /* Gain: '<S30>/-l_x1' incorporates:
     *  Constant: '<S30>/l_x1'
     */
    PS3_B.l_x1 = PS3_P.l_x1_Gain * PS3_P.l_x1_Value;

    /* Gain: '<S30>/-l_y2' incorporates:
     *  Constant: '<S30>/l_y2'
     */
    PS3_B.l_y2 = PS3_P.l_y2_Gain * PS3_P.l_y2_Value;

    /* Gain: '<S30>/-l_x2' incorporates:
     *  Constant: '<S30>/l_x2'
     */
    PS3_B.l_x2 = PS3_P.l_x2_Gain * PS3_P.l_x2_Value;

    /* Reshape: '<S30>/3x5' incorporates:
     *  Constant: '<S30>/T_e11'
     *  Constant: '<S30>/T_e12'
     *  Constant: '<S30>/T_e13'
     *  Constant: '<S30>/T_e14'
     *  Constant: '<S30>/T_e15'
     *  Constant: '<S30>/T_e21'
     *  Constant: '<S30>/T_e22'
     *  Constant: '<S30>/T_e23'
     *  Constant: '<S30>/T_e24'
     *  Constant: '<S30>/T_e25'
     *  Constant: '<S30>/l_x3'
     *  Constant: '<S30>/l_y1'
     */
    PS3_B.x5[0] = PS3_P.T_e11_Value;
    PS3_B.x5[1] = PS3_P.T_e21_Value;
    PS3_B.x5[2] = PS3_P.l_y1_Value;
    PS3_B.x5[3] = PS3_P.T_e12_Value;
    PS3_B.x5[4] = PS3_P.T_e22_Value;
    PS3_B.x5[5] = PS3_B.l_x1;
    PS3_B.x5[6] = PS3_P.T_e13_Value;
    PS3_B.x5[7] = PS3_P.T_e23_Value;
    PS3_B.x5[8] = PS3_B.l_y2;
    PS3_B.x5[9] = PS3_P.T_e14_Value;
    PS3_B.x5[10] = PS3_P.T_e24_Value;
    PS3_B.x5[11] = PS3_B.l_x2;
    PS3_B.x5[12] = PS3_P.T_e15_Value;
    PS3_B.x5[13] = PS3_P.T_e25_Value;
    PS3_B.x5[14] = PS3_P.l_x3_Value;

    /* S-Function (sdsppinv): '<S9>/Pseudoinverse' */
    /* Copy input to temporary space */
    memcpy((void *)(&PS3_DWork.Pseudoinverse_X[0]), (void *)(&PS3_B.x5[0]), 15U *
           sizeof(real_T));

    /* Call SVD */
    i = MWDSP_SVD_D(&PS3_DWork.Pseudoinverse_X[0], 3, 5,
                    &PS3_DWork.Pseudoinverse_S[0], &PS3_DWork.Pseudoinverse_E[0],
                    &PS3_DWork.Pseudoinverse_WORK[0],
                    &PS3_DWork.Pseudoinverse_U[0], &PS3_DWork.Pseudoinverse_V[0],
                    1);

    /* Only call 'pinv' function if SVD succeeded */
    if (i == 0) {
      MWDSPCG_Pseudoinverse_D(&PS3_DWork.Pseudoinverse_S[0],
        &PS3_DWork.Pseudoinverse_U[0], &PS3_DWork.Pseudoinverse_V[0],
        &PS3_B.Pseudoinverse[0], (const int32_T)3, (const int32_T)5);
    }

    /* Sum: '<S5>/Sum1' */
    PS3_B.Sum1 = PS3_B.ypositionofleftanalogstick11 +
      PS3_B.ypositionofrightanalogstick11;

    /* Gain: '<S5>/tau_surge' */
    PS3_B.tau_surge = PS3_P.tau_surge_Gain * PS3_B.Sum1;

    /* Sum: '<S5>/Sum2' */
    PS3_B.Sum2 = PS3_B.xpositionofleftanalogstick11 +
      PS3_B.xpositionofrightanalogstick11;

    /* Gain: '<S5>/tau_sway' */
    PS3_B.tau_sway = PS3_P.tau_sway_Gain * PS3_B.Sum2;

    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S4>/L2'
     *  Constant: '<S4>/R2'
     */
    PS3_B.Sum = PS3_P.L2_Value + PS3_P.R2_Value;

    /* Gain: '<S5>/tau_yaw' */
    PS3_B.tau_yaw = PS3_P.tau_yaw_Gain * PS3_B.Sum;

    /* SignalConversion: '<S9>/TmpHiddenBufferAtProductInport2' */
    PS3_B.TmpHiddenBufferAtProductInport2[0] = PS3_B.tau_surge;
    PS3_B.TmpHiddenBufferAtProductInport2[1] = PS3_B.tau_sway;
    PS3_B.TmpHiddenBufferAtProductInport2[2] = PS3_B.tau_yaw;

    /* Product: '<S9>/Product' */
    for (i = 0; i < 5; i++) {
      PS3_B.Product[i] = 0.0;
      PS3_B.Product[i] = PS3_B.Pseudoinverse[i] *
        PS3_B.TmpHiddenBufferAtProductInport2[0] + PS3_B.Product[i];
      PS3_B.Product[i] = PS3_B.Pseudoinverse[i + 5] *
        PS3_B.TmpHiddenBufferAtProductInport2[1] + PS3_B.Product[i];
      PS3_B.Product[i] = PS3_B.Pseudoinverse[i + 10] *
        PS3_B.TmpHiddenBufferAtProductInport2[2] + PS3_B.Product[i];
    }

    /* DeadZone Block: '<S10>/Dead Zone'
     */
    if (PS3_B.Product[0] >= PS3_P.DeadZone_End) {
      PS3_B.DeadZone = PS3_B.Product[0] - PS3_P.DeadZone_End;
    } else if (PS3_B.Product[0] > PS3_P.DeadZone_Start) {
      PS3_B.DeadZone = 0.0;
    } else {
      PS3_B.DeadZone = PS3_B.Product[0] - PS3_P.DeadZone_Start;
    }

    /* RelationalOperator: '<S15>/Compare' incorporates:
     *  Constant: '<S15>/Constant'
     */
    PS3_B.Compare = (PS3_B.DeadZone < PS3_P.Constant_Value);

    /* RelationalOperator: '<S17>/Compare' */
    PS3_B.Compare_a = (PS3_B.DeadZone == 0.0);

    /* Gain: '<S10>/Gain' */
    PS3_B.Gain = (uint16_T)(PS3_P.Gain_Gain * PS3_B.Compare_a);

    /* RelationalOperator: '<S16>/Compare' incorporates:
     *  Constant: '<S16>/Constant'
     */
    PS3_B.Compare_d = (PS3_B.DeadZone > PS3_P.Constant_Value_h);

    /* Gain: '<S10>/Gain1' */
    PS3_B.Gain1 = (uint16_T)(PS3_P.Gain1_Gain * PS3_B.Compare_d);

    /* Sum: '<S10>/Sum' */
    PS3_B.Sum_ow = (uint16_T)(uint32_T)(((PS3_B.Compare << 6) + PS3_B.Gain) +
      PS3_B.Gain1);

    /* Lookup Block: '<S10>/f_1 < 0'
     * About '<S10>/f_1 < 0 :'
     * Lookup Block: '<S10>/f_1 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_10), PS3_P.f_10_YData, PS3_B.Product[0],
                         PS3_P.f_10_XData, 8U);

    /* Lookup Block: '<S10>/f_1 > 0'
     * About '<S10>/f_1 > 0 :'
     * Lookup Block: '<S10>/f_1 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_10_m), PS3_P.f_10_YData_p, PS3_B.Product[0],
                         PS3_P.f_10_XData_h, 9U);

    /* MultiPortSwitch: '<S10>/Multiport Switch' incorporates:
     *  Constant: '<S10>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)PS3_B.Sum_ow >> 6)) {
     case 1:
      PS3_B.MultiportSwitch = PS3_B.f_10;
      break;

     case 2:
      PS3_B.MultiportSwitch = PS3_P.f_10_Value;
      break;

     default:
      PS3_B.MultiportSwitch = PS3_B.f_10_m;
      break;
    }

    /* DeadZone Block: '<S11>/Dead Zone'
     */
    if (PS3_B.Product[1] >= PS3_P.DeadZone_End_b) {
      PS3_B.DeadZone_h = PS3_B.Product[1] - PS3_P.DeadZone_End_b;
    } else if (PS3_B.Product[1] > PS3_P.DeadZone_Start_p) {
      PS3_B.DeadZone_h = 0.0;
    } else {
      PS3_B.DeadZone_h = PS3_B.Product[1] - PS3_P.DeadZone_Start_p;
    }

    /* RelationalOperator: '<S18>/Compare' incorporates:
     *  Constant: '<S18>/Constant'
     */
    PS3_B.Compare_i = (PS3_B.DeadZone_h < PS3_P.Constant_Value_l);

    /* RelationalOperator: '<S19>/Compare' incorporates:
     *  Constant: '<S19>/Constant'
     */
    PS3_B.Compare_ab = (PS3_B.DeadZone_h == PS3_P.Constant_Value_n);

    /* Gain: '<S11>/Gain' */
    PS3_B.Gain_k = (uint16_T)(PS3_P.Gain_Gain_h * PS3_B.Compare_ab);

    /* RelationalOperator: '<S20>/Compare' incorporates:
     *  Constant: '<S20>/Constant'
     */
    PS3_B.Compare_h = (PS3_B.DeadZone_h > PS3_P.Constant_Value_b);

    /* Gain: '<S11>/Gain1' */
    PS3_B.Gain1_l = (uint16_T)(PS3_P.Gain1_Gain_p * PS3_B.Compare_h);

    /* Sum: '<S11>/Sum' */
    PS3_B.Sum_i = (uint16_T)(uint32_T)(((PS3_B.Compare_i << 6) + PS3_B.Gain_k) +
      PS3_B.Gain1_l);

    /* Lookup Block: '<S11>/f_2 < 0'
     * About '<S11>/f_2 < 0 :'
     * Lookup Block: '<S11>/f_2 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_20), PS3_P.f_20_YData, PS3_B.Product[1],
                         PS3_P.f_20_XData, 10U);

    /* Lookup Block: '<S11>/f_2 > 0'
     * About '<S11>/f_2 > 0 :'
     * Lookup Block: '<S11>/f_2 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_20_i), PS3_P.f_20_YData_p, PS3_B.Product[1],
                         PS3_P.f_20_XData_n, 9U);

    /* MultiPortSwitch: '<S11>/Multiport Switch' incorporates:
     *  Constant: '<S11>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)PS3_B.Sum_i >> 6)) {
     case 1:
      PS3_B.MultiportSwitch_e = PS3_B.f_20;
      break;

     case 2:
      PS3_B.MultiportSwitch_e = PS3_P.f_20_Value;
      break;

     default:
      PS3_B.MultiportSwitch_e = PS3_B.f_20_i;
      break;
    }

    /* DeadZone Block: '<S12>/Dead Zone'
     */
    if (PS3_B.Product[2] >= PS3_P.DeadZone_End_a) {
      PS3_B.DeadZone_b = PS3_B.Product[2] - PS3_P.DeadZone_End_a;
    } else if (PS3_B.Product[2] > PS3_P.DeadZone_Start_d) {
      PS3_B.DeadZone_b = 0.0;
    } else {
      PS3_B.DeadZone_b = PS3_B.Product[2] - PS3_P.DeadZone_Start_d;
    }

    /* RelationalOperator: '<S21>/Compare' incorporates:
     *  Constant: '<S21>/Constant'
     */
    PS3_B.Compare_dd = (PS3_B.DeadZone_b < PS3_P.Constant_Value_a);

    /* RelationalOperator: '<S23>/Compare' */
    PS3_B.Compare_c = (PS3_B.DeadZone_b == 0.0);

    /* Gain: '<S12>/Gain' */
    PS3_B.Gain_f = (uint16_T)(PS3_P.Gain_Gain_f * PS3_B.Compare_c);

    /* RelationalOperator: '<S22>/Compare' incorporates:
     *  Constant: '<S22>/Constant'
     */
    PS3_B.Compare_af = (PS3_B.DeadZone_b > PS3_P.Constant_Value_o);

    /* Gain: '<S12>/Gain1' */
    PS3_B.Gain1_i = (uint16_T)(PS3_P.Gain1_Gain_o * PS3_B.Compare_af);

    /* Sum: '<S12>/Sum' */
    PS3_B.Sum_f = (uint16_T)(uint32_T)(((PS3_B.Compare_dd << 6) + PS3_B.Gain_f)
      + PS3_B.Gain1_i);

    /* Lookup Block: '<S12>/f_3 < 0'
     * About '<S12>/f_3 < 0 :'
     * Lookup Block: '<S12>/f_3 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_30), PS3_P.f_30_YData, PS3_B.Product[2],
                         PS3_P.f_30_XData, 7U);

    /* Lookup Block: '<S12>/f_3 > 0'
     * About '<S12>/f_3 > 0 :'
     * Lookup Block: '<S12>/f_3 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_30_b), PS3_P.f_30_YData_j, PS3_B.Product[2],
                         PS3_P.f_30_XData_k, 10U);

    /* MultiPortSwitch: '<S12>/Multiport Switch' incorporates:
     *  Constant: '<S12>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)PS3_B.Sum_f >> 6)) {
     case 1:
      PS3_B.MultiportSwitch_f = PS3_B.f_30;
      break;

     case 2:
      PS3_B.MultiportSwitch_f = PS3_P.f_30_Value;
      break;

     default:
      PS3_B.MultiportSwitch_f = PS3_B.f_30_b;
      break;
    }

    /* DeadZone Block: '<S13>/Dead Zone'
     */
    if (PS3_B.Product[3] >= PS3_P.DeadZone_End_p) {
      PS3_B.DeadZone_f = PS3_B.Product[3] - PS3_P.DeadZone_End_p;
    } else if (PS3_B.Product[3] > PS3_P.DeadZone_Start_a) {
      PS3_B.DeadZone_f = 0.0;
    } else {
      PS3_B.DeadZone_f = PS3_B.Product[3] - PS3_P.DeadZone_Start_a;
    }

    /* RelationalOperator: '<S24>/Compare' incorporates:
     *  Constant: '<S24>/Constant'
     */
    PS3_B.Compare_ak = (PS3_B.DeadZone_f < PS3_P.Constant_Value_bv);

    /* RelationalOperator: '<S26>/Compare' */
    PS3_B.Compare_av = (PS3_B.DeadZone_f == 0.0);

    /* Gain: '<S13>/Gain' */
    PS3_B.Gain_m = (uint16_T)(PS3_P.Gain_Gain_b * PS3_B.Compare_av);

    /* RelationalOperator: '<S25>/Compare' incorporates:
     *  Constant: '<S25>/Constant'
     */
    PS3_B.Compare_p = (PS3_B.DeadZone_f > PS3_P.Constant_Value_bb);

    /* Gain: '<S13>/Gain1' */
    PS3_B.Gain1_g = (uint16_T)(PS3_P.Gain1_Gain_l * PS3_B.Compare_p);

    /* Sum: '<S13>/Sum' */
    PS3_B.Sum_l = (uint16_T)(uint32_T)(((PS3_B.Compare_ak << 6) + PS3_B.Gain_m)
      + PS3_B.Gain1_g);

    /* Lookup Block: '<S13>/f_4 < 0'
     * About '<S13>/f_4 < 0 :'
     * Lookup Block: '<S13>/f_4 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_40), PS3_P.f_40_YData, PS3_B.Product[3],
                         PS3_P.f_40_XData, 9U);

    /* Lookup Block: '<S13>/f_4 > 0'
     * About '<S13>/f_4 > 0 :'
     * Lookup Block: '<S13>/f_4 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_40_k), PS3_P.f_40_YData_l, PS3_B.Product[3],
                         PS3_P.f_40_XData_e, 6U);

    /* MultiPortSwitch: '<S13>/Multiport Switch' incorporates:
     *  Constant: '<S13>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)PS3_B.Sum_l >> 6)) {
     case 1:
      PS3_B.MultiportSwitch_h = PS3_B.f_40;
      break;

     case 2:
      PS3_B.MultiportSwitch_h = PS3_P.f_40_Value;
      break;

     default:
      PS3_B.MultiportSwitch_h = PS3_B.f_40_k;
      break;
    }

    /* DeadZone Block: '<S14>/Dead Zone'
     */
    if (PS3_B.Product[4] >= PS3_P.DeadZone_End_d) {
      PS3_B.DeadZone_l = PS3_B.Product[4] - PS3_P.DeadZone_End_d;
    } else if (PS3_B.Product[4] > PS3_P.DeadZone_Start_dk) {
      PS3_B.DeadZone_l = 0.0;
    } else {
      PS3_B.DeadZone_l = PS3_B.Product[4] - PS3_P.DeadZone_Start_dk;
    }

    /* RelationalOperator: '<S27>/Compare' incorporates:
     *  Constant: '<S27>/Constant'
     */
    PS3_B.Compare_p5 = (PS3_B.DeadZone_l < PS3_P.Constant_Value_g);

    /* RelationalOperator: '<S29>/Compare' */
    PS3_B.Compare_l = (PS3_B.DeadZone_l == 0.0);

    /* Gain: '<S14>/Gain' */
    PS3_B.Gain_o = (uint16_T)(PS3_P.Gain_Gain_g * PS3_B.Compare_l);

    /* RelationalOperator: '<S28>/Compare' incorporates:
     *  Constant: '<S28>/Constant'
     */
    PS3_B.Compare_c4 = (PS3_B.DeadZone_l > PS3_P.Constant_Value_ny);

    /* Gain: '<S14>/Gain1' */
    PS3_B.Gain1_p = (uint16_T)(PS3_P.Gain1_Gain_k * PS3_B.Compare_c4);

    /* Sum: '<S14>/Sum' */
    PS3_B.Sum_g = (uint16_T)(uint32_T)(((PS3_B.Compare_p5 << 6) + PS3_B.Gain_o)
      + PS3_B.Gain1_p);

    /* Lookup Block: '<S14>/f_5 < 0'
     * About '<S14>/f_5 < 0 :'
     * Lookup Block: '<S14>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_50), PS3_P.f_50_YData, PS3_B.Product[4],
                         PS3_P.f_50_XData, 2U);

    /* Lookup Block: '<S14>/f_5 > 0'
     * About '<S14>/f_5 > 0 :'
     * Lookup Block: '<S14>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(PS3_B.f_50_c), PS3_P.f_50_YData_d, PS3_B.Product[4],
                         PS3_P.f_50_XData_p, 2U);

    /* MultiPortSwitch: '<S14>/Multiport Switch' incorporates:
     *  Constant: '<S14>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)PS3_B.Sum_g >> 6)) {
     case 1:
      PS3_B.MultiportSwitch_p = PS3_B.f_50;
      break;

     case 2:
      PS3_B.MultiportSwitch_p = PS3_P.f_50_Value;
      break;

     default:
      PS3_B.MultiportSwitch_p = PS3_B.f_50_c;
      break;
    }

    /* Saturate: '<S5>/Saturation' */
    tmp[0] = PS3_B.MultiportSwitch;
    tmp[1] = PS3_B.MultiportSwitch_e;
    tmp[2] = PS3_B.MultiportSwitch_f;
    tmp[3] = PS3_B.MultiportSwitch_h;
    tmp[4] = PS3_B.MultiportSwitch_p;
    for (i = 0; i < 5; i++) {
      PS3_B.Saturation[i] = rt_SATURATE(tmp[i], PS3_P.Saturation_LowerSat,
        PS3_P.Saturation_UpperSat);
    }

    /* Gain: '<S5>/Joystick u_1' */
    PS3_B.Joysticku_1 = PS3_P.Joysticku_1_Gain * PS3_B.Saturation[0];

    /* Gain: '<S5>/Joystick u_2' */
    PS3_B.Joysticku_2 = PS3_P.Joysticku_2_Gain * PS3_B.Saturation[1];

    /* Gain: '<S5>/Joystick u_3' */
    PS3_B.Joysticku_3 = PS3_P.Joysticku_3_Gain * PS3_B.Saturation[2];

    /* Gain: '<S5>/Joystick u_4' */
    PS3_B.Joysticku_4 = PS3_P.Joysticku_4_Gain * PS3_B.Saturation[3];

    /* Gain: '<S5>/Joystick u_5' */
    PS3_B.Joysticku_5 = PS3_P.Joysticku_5_Gain * PS3_B.Saturation[4];

    /* MultiPortSwitch: '<S1>/Thruster setting Switch' incorporates:
     *  Constant: '<S1>/Control Mode'
     *  Constant: '<S4>/PS3_BT_Power'
     *  Constant: '<S4>/PS3_VSP_Speed'
     */
    if ((int32_T)PS3_P.ControlMode_Value == 0) {
      PS3_B.ThrustersettingSwitch[0] = PS3_B.u_1;
      PS3_B.ThrustersettingSwitch[1] = PS3_B.u_2;
      PS3_B.ThrustersettingSwitch[2] = PS3_B.u_3;
      PS3_B.ThrustersettingSwitch[3] = PS3_B.u_4;
      PS3_B.ThrustersettingSwitch[4] = PS3_B.u_5;
      PS3_B.ThrustersettingSwitch[5] = PS3_P.PS3_BT_Power_Value;
      PS3_B.ThrustersettingSwitch[6] = PS3_P.PS3_VSP_Speed_Value;
    } else {
      PS3_B.ThrustersettingSwitch[0] = PS3_B.Joysticku_1;
      PS3_B.ThrustersettingSwitch[1] = PS3_B.Joysticku_2;
      PS3_B.ThrustersettingSwitch[2] = PS3_B.Joysticku_3;
      PS3_B.ThrustersettingSwitch[3] = PS3_B.Joysticku_4;
      PS3_B.ThrustersettingSwitch[4] = PS3_B.Joysticku_5;
      PS3_B.ThrustersettingSwitch[5] = PS3_P.PS3_BT_Power_Value;
      PS3_B.ThrustersettingSwitch[6] = PS3_P.PS3_VSP_Speed_Value;
    }

    /* Saturate: '<S1>/Saturation' */
    for (i = 0; i < 7; i++) {
      tmp_0 = PS3_B.ThrustersettingSwitch[i];
      PS3_B.Saturation_f[i] = rt_SATURATE(tmp_0, PS3_P.Saturation_LowerSat_b,
        PS3_P.Saturation_UpperSat_l);
    }

    /* Gain: '<S3>/plant u_1' */
    PS3_B.plantu_1 = PS3_P.plantu_1_Gain * PS3_B.Saturation_f[0];

    /* Gain: '<S3>/plant u_2' */
    PS3_B.plantu_2 = PS3_P.plantu_2_Gain * PS3_B.Saturation_f[1];

    /* Gain: '<S3>/plant u_3' */
    PS3_B.plantu_3 = PS3_P.plantu_3_Gain * PS3_B.Saturation_f[2];

    /* Gain: '<S3>/plant u_4' */
    PS3_B.plantu_4 = PS3_P.plantu_4_Gain * PS3_B.Saturation_f[3];

    /* Gain: '<S3>/plant u_5' */
    PS3_B.plantu_5 = PS3_P.plantu_5_Gain * PS3_B.Saturation_f[4];

    /* Gain: '<S3>/plant BT power' */
    PS3_B.plantBTpower = PS3_P.plantBTpower_Gain * PS3_B.Saturation_f[5];

    /* Gain: '<S3>/plant VSP speed' */
    PS3_B.plantVSPspeed = PS3_P.plantVSPspeed_Gain * PS3_B.Saturation_f[6];

    /* Outputs for enable SubSystem: '<S3>/CSE1' incorporates:
     *  Constant: '<S3>/Enable CSE1'
     *  EnablePort: '<S31>/Enable'
     */
    if (PS3_P.EnableCSE1_Value > 0.0) {
      /* Gain: '<S32>/BT_D_Gain1' */
      PS3_B.BT_D_Gain1 = PS3_P.BT_D_Gain1_Gain * PS3_B.plantu_5;

      /* Gain: '<S32>/BT_D_Gain2' */
      PS3_B.BT_D_Gain2 = PS3_P.BT_D_Gain2_Gain * PS3_B.plantu_5;

      /* Sum: '<S32>/Add' incorporates:
       *  Constant: '<S32>/BT_Power_Offset1'
       */
      PS3_B.Add = (PS3_B.BT_D_Gain1 + PS3_P.BT_Power_Offset1_Value) +
        PS3_B.BT_D_Gain2;

      /* Gain: '<S32>/BT_L_Gain1' */
      PS3_B.BT_L_Gain1 = PS3_P.BT_L_Gain1_Gain * PS3_B.plantBTpower;

      /* Gain: '<S32>/BT_L_Gain2' */
      PS3_B.BT_L_Gain2 = PS3_P.BT_L_Gain2_Gain * PS3_B.plantBTpower;

      /* Gain: '<S32>/Neg' */
      PS3_B.Neg = PS3_P.Neg_Gain * PS3_B.plantBTpower;

      /* Sum: '<S32>/Sum1' incorporates:
       *  Constant: '<S32>/BT_Power_Offset2'
       */
      PS3_B.Sum1_d = PS3_B.BT_L_Gain1 + PS3_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S34>/LowerRelop1' */
      PS3_B.LowerRelop1 = (PS3_B.Add > PS3_B.Sum1_d);

      /* Sum: '<S32>/Sum2' incorporates:
       *  Constant: '<S32>/BT_Power_Offset3'
       */
      PS3_B.Sum2_o = PS3_B.BT_L_Gain2 + PS3_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S34>/UpperRelop' */
      PS3_B.UpperRelop = (PS3_B.Add < PS3_B.Sum2_o);

      /* Switch: '<S34>/Switch' */
      if (PS3_B.UpperRelop) {
        PS3_B.Switch = PS3_B.Sum2_o;
      } else {
        PS3_B.Switch = PS3_B.Add;
      }

      /* Switch: '<S34>/Switch2' */
      if (PS3_B.LowerRelop1) {
        PS3_B.Switch2 = PS3_B.Sum1_d;
      } else {
        PS3_B.Switch2 = PS3_B.Switch;
      }

      /* RelationalOperator: '<S35>/LowerRelop1' incorporates:
       *  Constant: '<S32>/Constant'
       */
      PS3_B.LowerRelop1_c = (PS3_B.plantu_5 > PS3_P.Constant_Value_al);

      /* RelationalOperator: '<S35>/UpperRelop' */
      PS3_B.UpperRelop_o = (PS3_B.plantu_5 < PS3_B.Neg);

      /* Switch: '<S35>/Switch' */
      if (PS3_B.UpperRelop_o) {
        PS3_B.Switch_e = PS3_B.Neg;
      } else {
        PS3_B.Switch_e = PS3_B.plantu_5;
      }

      /* Switch: '<S35>/Switch2' incorporates:
       *  Constant: '<S32>/Constant'
       */
      if (PS3_B.LowerRelop1_c) {
        PS3_B.Switch2_i = PS3_P.Constant_Value_al;
      } else {
        PS3_B.Switch2_i = PS3_B.Switch_e;
      }

      /* RelationalOperator: '<S36>/LowerRelop1' */
      PS3_B.LowerRelop1_g = (PS3_B.plantu_5 > PS3_B.plantBTpower);

      /* RelationalOperator: '<S36>/UpperRelop' incorporates:
       *  Constant: '<S32>/Constant1'
       */
      PS3_B.UpperRelop_g = (PS3_B.plantu_5 < PS3_P.Constant1_Value);

      /* Switch: '<S36>/Switch' incorporates:
       *  Constant: '<S32>/Constant1'
       */
      if (PS3_B.UpperRelop_g) {
        PS3_B.Switch_o = PS3_P.Constant1_Value;
      } else {
        PS3_B.Switch_o = PS3_B.plantu_5;
      }

      /* Switch: '<S36>/Switch2' */
      if (PS3_B.LowerRelop1_g) {
        PS3_B.Switch2_c = PS3_B.plantBTpower;
      } else {
        PS3_B.Switch2_c = PS3_B.Switch_o;
      }

      /* Signum: '<S33>/Sign' */
      PS3_B.Sign = rt_SIGNd_snf(PS3_B.plantVSPspeed);

      /* Product: '<S33>/Product1' */
      PS3_B.PortVPS_X = PS3_B.plantu_2 * PS3_B.Sign;

      /* Gain: '<S33>/-x' */
      PS3_B.PortVPS_X_o = PS3_P.x_Gain * PS3_B.PortVPS_X;

      /* Product: '<S33>/Product2' */
      PS3_B.PortVSP_Y = PS3_B.plantu_1 * PS3_B.Sign;

      /* Gain: '<S33>/-y' */
      PS3_B.PortVSP_Y_b = PS3_P.y_Gain * PS3_B.PortVSP_Y;

      /* Product: '<S33>/Product3' */
      PS3_B.StarboardVSP_X = PS3_B.plantu_4 * PS3_B.Sign;

      /* Product: '<S33>/Product4' */
      PS3_B.StarboardVSP_Y = PS3_B.plantu_3 * PS3_B.Sign;

      /* Lookup2D: '<S33>/Servo1' */
      PS3_B.Servo1 = rt_Lookup2D_Normal((const real_T *)(&PS3_P.Servo1_RowIdx[0]),
        3, (const real_T *)(&PS3_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&PS3_P.Servo1_Table[0]), (const real_T)PS3_B.PortVPS_X_o, (const real_T)
        PS3_B.PortVSP_Y_b);

      /* Lookup2D: '<S33>/Servo2' */
      PS3_B.Servo2 = rt_Lookup2D_Normal((const real_T *)(&PS3_P.Servo2_RowIdx[0]),
        3, (const real_T *)(&PS3_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&PS3_P.Servo2_Table[0]), (const real_T)PS3_B.PortVPS_X_o, (const real_T)
        PS3_B.PortVSP_Y_b);

      /* Lookup2D: '<S33>/Servo3' */
      PS3_B.Servo3 = rt_Lookup2D_Normal((const real_T *)(&PS3_P.Servo3_RowIdx[0]),
        3, (const real_T *)(&PS3_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&PS3_P.Servo3_Table[0]), (const real_T)PS3_B.StarboardVSP_X, (const
        real_T)PS3_B.StarboardVSP_Y);

      /* Lookup2D: '<S33>/Servo4' */
      PS3_B.Servo4 = rt_Lookup2D_Normal((const real_T *)(&PS3_P.Servo4_RowIdx[0]),
        3, (const real_T *)(&PS3_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&PS3_P.Servo4_Table[0]), (const real_T)PS3_B.StarboardVSP_X, (const
        real_T)PS3_B.StarboardVSP_Y);

      /* Gain: '<S33>/VPS_Speed_Gain' */
      PS3_B.VPS_Speed_Gain = PS3_P.VPS_Speed_Gain_Gain * PS3_B.plantVSPspeed;

      /* Sum: '<S33>/Sum' incorporates:
       *  Constant: '<S33>/VPS_Power_Offset'
       */
      PS3_B.Sum_o = PS3_B.VPS_Speed_Gain + PS3_P.VPS_Power_Offset_Value;

      /* Gain: '<S33>/VSPS Port' */
      PS3_B.VSPSPort = PS3_P.VSPSPort_Gain * PS3_B.Sum_o;

      /* Gain: '<S33>/VSPS Starboard' */
      PS3_B.VSPSStarboard = PS3_P.VSPSStarboard_Gain * PS3_B.Sum_o;
    }

    /* end of Outputs for SubSystem: '<S3>/CSE1' */

    /* Gain: '<S2>/Battery Bow Thruster' */
    PS3_B.BatteryBowThruster = PS3_P.BatteryBowThruster_Gain * PS3_B.SITzAI0;

    /* Gain: '<S2>/Battery Servo' */
    PS3_B.BatteryServo = PS3_P.BatteryServo_Gain * PS3_B.SITzAI1;

    /* Gain: '<S2>/Battery Main' */
    PS3_B.BatteryMain = PS3_P.BatteryMain_Gain * PS3_B.SITzAI2;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
static void PS3_update(int_T tid)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++PS3_M->Timing.clockTick0))
    ++PS3_M->Timing.clockTickH0;
  PS3_M->Timing.t[0] = PS3_M->Timing.clockTick0 * PS3_M->Timing.stepSize0 +
    PS3_M->Timing.clockTickH0 * PS3_M->Timing.stepSize0 * 4294967296.0;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void PS3_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PS3_M,0,
                sizeof(RT_MODEL_PS3));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = PS3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    PS3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    PS3_M->Timing.sampleTimes = (&PS3_M->Timing.sampleTimesArray[0]);
    PS3_M->Timing.offsetTimes = (&PS3_M->Timing.offsetTimesArray[0]);

    /* task periods */
    PS3_M->Timing.sampleTimes[0] = (0.1);

    /* task offsets */
    PS3_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(PS3_M, &PS3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = PS3_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    PS3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(PS3_M, -1);
  PS3_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    PS3_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(PS3_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(PS3_M->rtwLogInfo, (NULL));
    rtliSetLogT(PS3_M->rtwLogInfo, "");
    rtliSetLogX(PS3_M->rtwLogInfo, "");
    rtliSetLogXFinal(PS3_M->rtwLogInfo, "");
    rtliSetSigLog(PS3_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(PS3_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(PS3_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(PS3_M->rtwLogInfo, 0);
    rtliSetLogDecimation(PS3_M->rtwLogInfo, 1);
    rtliSetLogY(PS3_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(PS3_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(PS3_M->rtwLogInfo, (NULL));
  }

  PS3_M->solverInfoPtr = (&PS3_M->solverInfo);
  PS3_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&PS3_M->solverInfo, 0.1);
  rtsiSetSolverMode(&PS3_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  PS3_M->ModelData.blockIO = ((void *) &PS3_B);
  (void) memset(((void *) &PS3_B),0,
                sizeof(BlockIO_PS3));

  /* parameters */
  PS3_M->ModelData.defaultParam = ((real_T *) &PS3_P);

  /* states (dwork) */
  PS3_M->Work.dwork = ((void *) &PS3_DWork);
  (void) memset((void *)&PS3_DWork, 0,
                sizeof(D_Work_PS3));
}

/* Model terminate function */
void PS3_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  PS3_output(tid);
}

void MdlUpdate(int_T tid)
{
  PS3_update(tid);
}

void MdlInitializeSizes(void)
{
  PS3_M->Sizes.numContStates = (0);    /* Number of continuous states */
  PS3_M->Sizes.numY = (0);             /* Number of model outputs */
  PS3_M->Sizes.numU = (0);             /* Number of model inputs */
  PS3_M->Sizes.sysDirFeedThru = (0);   /* The model is not direct feedthrough */
  PS3_M->Sizes.numSampTimes = (1);     /* Number of sample times */
  PS3_M->Sizes.numBlocks = (192);      /* Number of blocks */
  PS3_M->Sizes.numBlockIO = (129);     /* Number of block outputs */
  PS3_M->Sizes.numBlockPrms = (396);   /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  MdlInitialize();
}

RT_MODEL_PS3 *PS3(void)
{
  PS3_initialize(1);
  return PS3_M;
}

void MdlTerminate(void)
{
  PS3_terminate();
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
#ifdef NI_ROOTMODEL_PS3
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
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 31:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 32:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 33:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 31:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 32:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 33:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern PS3_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // HMI/SIT zAI0
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&PS3_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&PS3_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&PS3_B.SITzAI2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 3;
}

double ni_extout[7];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Plants/CSE1/Bow Thruster/SIT PWM0 BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Switch2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.VSPSStarboard,0,0,0);
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
  ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Switch2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Servo1,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Servo2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Servo3,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.Servo4,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.VSPSPort,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&PS3_B.VSPSStarboard,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "ps3/Control Systems/Control Mode/Value", offsetof(Parameters_PS3,
    ControlMode_Value), 37, 1, 2, 0, "", 0 },

  { 1, "ps3/Control Systems/PS3 input/AS_LY/Value", offsetof(Parameters_PS3,
    AS_LY_Value), 37, 1, 2, 2, "", 0 },

  { 2, "ps3/Control Systems/PS3 input/ScalingLY/Gain", offsetof(Parameters_PS3,
    ScalingLY_Gain), 37, 1, 2, 4, "", 0 },

  { 3, "ps3/Control Systems/PS3 u input control/PS3 u_1/Gain", offsetof
    (Parameters_PS3, PS3u_1_Gain), 37, 1, 2, 6, "", 0 },

  { 4, "ps3/Control Systems/PS3 input/AS_LX/Value", offsetof(Parameters_PS3,
    AS_LX_Value), 37, 1, 2, 8, "", 0 },

  { 5, "ps3/Control Systems/PS3 input/ScalingLX/Gain", offsetof(Parameters_PS3,
    ScalingLX_Gain), 37, 1, 2, 10, "", 0 },

  { 6, "ps3/Control Systems/PS3 u input control/PS3 u_2/Gain", offsetof
    (Parameters_PS3, PS3u_2_Gain), 37, 1, 2, 12, "", 0 },

  { 7, "ps3/Control Systems/PS3 input/AS_RY/Value", offsetof(Parameters_PS3,
    AS_RY_Value), 37, 1, 2, 14, "", 0 },

  { 8, "ps3/Control Systems/PS3 input/ScalingRY/Gain", offsetof(Parameters_PS3,
    ScalingRY_Gain), 37, 1, 2, 16, "", 0 },

  { 9, "ps3/Control Systems/PS3 u input control/PS3 u_3/Gain", offsetof
    (Parameters_PS3, PS3u_3_Gain), 37, 1, 2, 18, "", 0 },

  { 10, "ps3/Control Systems/PS3 input/AS_RX/Value", offsetof(Parameters_PS3,
    AS_RX_Value), 37, 1, 2, 20, "", 0 },

  { 11, "ps3/Control Systems/PS3 input/Scaling_RX/Gain", offsetof(Parameters_PS3,
    Scaling_RX_Gain), 37, 1, 2, 22, "", 0 },

  { 12, "ps3/Control Systems/PS3 u input control/PS3 u_4/Gain", offsetof
    (Parameters_PS3, PS3u_4_Gain), 37, 1, 2, 24, "", 0 },

  { 13, "ps3/Control Systems/PS3 input/L2/Value", offsetof(Parameters_PS3,
    L2_Value), 37, 1, 2, 26, "", 0 },

  { 14, "ps3/Control Systems/PS3 input/R2/Value", offsetof(Parameters_PS3,
    R2_Value), 37, 1, 2, 28, "", 0 },

  { 15, "ps3/Control Systems/PS3 u input control/PS3 u_5/Gain", offsetof
    (Parameters_PS3, PS3u_5_Gain), 37, 1, 2, 30, "", 0 },

  { 16, "ps3/Control Systems/PS3 input/PS3_BT_Power/Value", offsetof
    (Parameters_PS3, PS3_BT_Power_Value), 37, 1, 2, 32, "", 0 },

  { 17, "ps3/Control Systems/PS3 input/PS3_VSP_Speed/Value", offsetof
    (Parameters_PS3, PS3_VSP_Speed_Value), 37, 1, 2, 34, "", 0 },

  { 18,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_PS3, T_e11_Value), 37, 1, 2, 36, "", 0 },

  { 19,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_PS3, T_e21_Value), 37, 1, 2, 38, "", 0 },

  { 20,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_PS3, l_y1_Value), 37, 1, 2, 40, "", 0 },

  { 21,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_PS3, T_e12_Value), 37, 1, 2, 42, "", 0 },

  { 22,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_PS3, T_e22_Value), 37, 1, 2, 44, "", 0 },

  { 23,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_PS3, l_x1_Value), 37, 1, 2, 46, "", 0 },

  { 24,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_PS3, l_x1_Gain), 37, 1, 2, 48, "", 0 },

  { 25,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_PS3, T_e13_Value), 37, 1, 2, 50, "", 0 },

  { 26,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_PS3, T_e23_Value), 37, 1, 2, 52, "", 0 },

  { 27,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_PS3, l_y2_Value), 37, 1, 2, 54, "", 0 },

  { 28,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_PS3, l_y2_Gain), 37, 1, 2, 56, "", 0 },

  { 29,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_PS3, T_e14_Value), 37, 1, 2, 58, "", 0 },

  { 30,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_PS3, T_e24_Value), 37, 1, 2, 60, "", 0 },

  { 31,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_PS3, l_x2_Value), 37, 1, 2, 62, "", 0 },

  { 32,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_PS3, l_x2_Gain), 37, 1, 2, 64, "", 0 },

  { 33,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_PS3, T_e15_Value), 37, 1, 2, 66, "", 0 },

  { 34,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_PS3, T_e25_Value), 37, 1, 2, 68, "", 0 },

  { 35,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_PS3, l_x3_Value), 37, 1, 2, 70, "", 0 },

  { 36, "ps3/Control Systems/PS3 tau input control/tau_surge/Gain", offsetof
    (Parameters_PS3, tau_surge_Gain), 37, 1, 2, 72, "", 0 },

  { 37, "ps3/Control Systems/PS3 tau input control/tau_sway/Gain", offsetof
    (Parameters_PS3, tau_sway_Gain), 37, 1, 2, 74, "", 0 },

  { 38, "ps3/Control Systems/PS3 tau input control/tau_yaw/Gain", offsetof
    (Parameters_PS3, tau_yaw_Gain), 37, 1, 2, 76, "", 0 },

  { 39,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue",
    offsetof(Parameters_PS3, DeadZone_Start), 37, 1, 2, 78, "", 0 },

  { 40,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue",
    offsetof(Parameters_PS3, DeadZone_End), 37, 1, 2, 80, "", 0 },

  { 41,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value), 37, 1, 2, 82, "", 0 },

  { 42,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_h), 37, 1, 2, 84, "", 0 },

  { 43,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_PS3, f_10_XData), 38, 9, 2, 86, "", 0 },

  { 44,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_PS3, f_10_YData), 38, 9, 2, 88, "", 0 },

  { 45,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_PS3, f_10_Value), 37, 1, 2, 90, "", 0 },

  { 46,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_PS3, f_10_XData_h), 39, 10, 2, 92, "", 0 },

  { 47,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_PS3, f_10_YData_p), 39, 10, 2, 94, "", 0 },

  { 48,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue",
    offsetof(Parameters_PS3, DeadZone_Start_p), 37, 1, 2, 96, "", 0 },

  { 49,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue",
    offsetof(Parameters_PS3, DeadZone_End_b), 37, 1, 2, 98, "", 0 },

  { 50,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_l), 37, 1, 2, 100, "", 0 },

  { 51,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_n), 37, 1, 2, 102, "", 0 },

  { 52,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_b), 37, 1, 2, 104, "", 0 },

  { 53,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_PS3, f_20_XData), 40, 11, 2, 106, "", 0 },

  { 54,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_PS3, f_20_YData), 40, 11, 2, 108, "", 0 },

  { 55,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_PS3, f_20_Value), 37, 1, 2, 110, "", 0 },

  { 56,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_PS3, f_20_XData_n), 39, 10, 2, 112, "", 0 },

  { 57,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_PS3, f_20_YData_p), 39, 10, 2, 114, "", 0 },

  { 58,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue",
    offsetof(Parameters_PS3, DeadZone_Start_d), 37, 1, 2, 116, "", 0 },

  { 59,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue",
    offsetof(Parameters_PS3, DeadZone_End_a), 37, 1, 2, 118, "", 0 },

  { 60,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_a), 37, 1, 2, 120, "", 0 },

  { 61,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_o), 37, 1, 2, 122, "", 0 },

  { 62,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_PS3, f_30_XData), 41, 8, 2, 124, "", 0 },

  { 63,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_PS3, f_30_YData), 41, 8, 2, 126, "", 0 },

  { 64,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_PS3, f_30_Value), 37, 1, 2, 128, "", 0 },

  { 65,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_PS3, f_30_XData_k), 40, 11, 2, 130, "", 0 },

  { 66,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_PS3, f_30_YData_j), 40, 11, 2, 132, "", 0 },

  { 67,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue",
    offsetof(Parameters_PS3, DeadZone_Start_a), 37, 1, 2, 134, "", 0 },

  { 68,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue",
    offsetof(Parameters_PS3, DeadZone_End_p), 37, 1, 2, 136, "", 0 },

  { 69,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_bv), 37, 1, 2, 138, "", 0 },

  { 70,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_bb), 37, 1, 2, 140, "", 0 },

  { 71,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_PS3, f_40_XData), 39, 10, 2, 142, "", 0 },

  { 72,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_PS3, f_40_YData), 39, 10, 2, 144, "", 0 },

  { 73,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_PS3, f_40_Value), 37, 1, 2, 146, "", 0 },

  { 74,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_PS3, f_40_XData_e), 42, 7, 2, 148, "", 0 },

  { 75,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_PS3, f_40_YData_l), 42, 7, 2, 150, "", 0 },

  { 76,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue",
    offsetof(Parameters_PS3, DeadZone_Start_dk), 37, 1, 2, 152, "", 0 },

  { 77,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue",
    offsetof(Parameters_PS3, DeadZone_End_d), 37, 1, 2, 154, "", 0 },

  { 78,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_g), 37, 1, 2, 156, "", 0 },

  { 79,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_PS3, Constant_Value_ny), 37, 1, 2, 158, "", 0 },

  { 80,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_PS3, f_50_XData), 43, 3, 2, 160, "", 0 },

  { 81,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_PS3, f_50_YData), 43, 3, 2, 162, "", 0 },

  { 82,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_PS3, f_50_Value), 37, 1, 2, 164, "", 0 },

  { 83,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_PS3, f_50_XData_p), 43, 3, 2, 166, "", 0 },

  { 84,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_PS3, f_50_YData_d), 43, 3, 2, 168, "", 0 },

  { 85, "ps3/Control Systems/PS3 tau input control/Saturation/UpperLimit",
    offsetof(Parameters_PS3, Saturation_UpperSat), 37, 1, 2, 170, "", 0 },

  { 86, "ps3/Control Systems/PS3 tau input control/Saturation/LowerLimit",
    offsetof(Parameters_PS3, Saturation_LowerSat), 37, 1, 2, 172, "", 0 },

  { 87, "ps3/Control Systems/PS3 tau input control/Joystick u_1/Gain", offsetof
    (Parameters_PS3, Joysticku_1_Gain), 37, 1, 2, 174, "", 0 },

  { 88, "ps3/Control Systems/PS3 tau input control/Joystick u_2/Gain", offsetof
    (Parameters_PS3, Joysticku_2_Gain), 37, 1, 2, 176, "", 0 },

  { 89, "ps3/Control Systems/PS3 tau input control/Joystick u_3/Gain", offsetof
    (Parameters_PS3, Joysticku_3_Gain), 37, 1, 2, 178, "", 0 },

  { 90, "ps3/Control Systems/PS3 tau input control/Joystick u_4/Gain", offsetof
    (Parameters_PS3, Joysticku_4_Gain), 37, 1, 2, 180, "", 0 },

  { 91, "ps3/Control Systems/PS3 tau input control/Joystick u_5/Gain", offsetof
    (Parameters_PS3, Joysticku_5_Gain), 37, 1, 2, 182, "", 0 },

  { 92, "ps3/Control Systems/Saturation/UpperLimit", offsetof(Parameters_PS3,
    Saturation_UpperSat_l), 37, 1, 2, 184, "", 0 },

  { 93, "ps3/Control Systems/Saturation/LowerLimit", offsetof(Parameters_PS3,
    Saturation_LowerSat_b), 37, 1, 2, 186, "", 0 },

  { 94, "ps3/Plants/plant u_1/Gain", offsetof(Parameters_PS3, plantu_1_Gain), 37,
    1, 2, 188, "", 0 },

  { 95, "ps3/Plants/plant u_2/Gain", offsetof(Parameters_PS3, plantu_2_Gain), 37,
    1, 2, 190, "", 0 },

  { 96, "ps3/Plants/plant u_3/Gain", offsetof(Parameters_PS3, plantu_3_Gain), 37,
    1, 2, 192, "", 0 },

  { 97, "ps3/Plants/plant u_4/Gain", offsetof(Parameters_PS3, plantu_4_Gain), 37,
    1, 2, 194, "", 0 },

  { 98, "ps3/Plants/plant u_5/Gain", offsetof(Parameters_PS3, plantu_5_Gain), 37,
    1, 2, 196, "", 0 },

  { 99, "ps3/Plants/plant BT power/Gain", offsetof(Parameters_PS3,
    plantBTpower_Gain), 37, 1, 2, 198, "", 0 },

  { 100, "ps3/Plants/plant VSP speed/Gain", offsetof(Parameters_PS3,
    plantVSPspeed_Gain), 37, 1, 2, 200, "", 0 },

  { 101, "ps3/Plants/Enable CSE1/Value", offsetof(Parameters_PS3,
    EnableCSE1_Value), 37, 1, 2, 202, "", 0 },

  { 102, "ps3/HMI/Battery Bow Thruster/Gain", offsetof(Parameters_PS3,
    BatteryBowThruster_Gain), 37, 1, 2, 204, "", 0 },

  { 103, "ps3/HMI/Battery Servo/Gain", offsetof(Parameters_PS3,
    BatteryServo_Gain), 37, 1, 2, 206, "", 0 },

  { 104, "ps3/HMI/Battery Main/Gain", offsetof(Parameters_PS3, BatteryMain_Gain),
    37, 1, 2, 208, "", 0 },

  { 105, "ps3/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain", offsetof(Parameters_PS3,
    BT_D_Gain1_Gain), 37, 1, 2, 210, "", 0 },

  { 106, "ps3/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value", offsetof
    (Parameters_PS3, BT_Power_Offset1_Value), 37, 1, 2, 212, "", 0 },

  { 107, "ps3/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain", offsetof(Parameters_PS3,
    BT_D_Gain2_Gain), 37, 1, 2, 214, "", 0 },

  { 108, "ps3/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain", offsetof(Parameters_PS3,
    BT_L_Gain1_Gain), 37, 1, 2, 216, "", 0 },

  { 109, "ps3/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain", offsetof(Parameters_PS3,
    BT_L_Gain2_Gain), 37, 1, 2, 218, "", 0 },

  { 110, "ps3/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value", offsetof
    (Parameters_PS3, BT_Power_Offset2_Value), 37, 1, 2, 220, "", 0 },

  { 111, "ps3/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value", offsetof
    (Parameters_PS3, BT_Power_Offset3_Value), 37, 1, 2, 222, "", 0 },

  { 112, "ps3/Plants/CSE1/Bow Thruster/Constant/Value", offsetof(Parameters_PS3,
    Constant_Value_al), 37, 1, 2, 224, "", 0 },

  { 113, "ps3/Plants/CSE1/Bow Thruster/Constant1/Value", offsetof(Parameters_PS3,
    Constant1_Value), 37, 1, 2, 226, "", 0 },

  { 114, "ps3/Plants/CSE1/Bow Thruster/Neg/Gain", offsetof(Parameters_PS3,
    Neg_Gain), 37, 1, 2, 228, "", 0 },

  { 115, "ps3/Plants/CSE1/Voith Schneider Propeller /-x/Gain", offsetof
    (Parameters_PS3, x_Gain), 37, 1, 2, 230, "", 0 },

  { 116, "ps3/Plants/CSE1/Voith Schneider Propeller /-y/Gain", offsetof
    (Parameters_PS3, y_Gain), 37, 1, 2, 232, "", 0 },

  { 117, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex", offsetof
    (Parameters_PS3, Servo1_RowIdx), 44, 3, 2, 234, "", 0 },

  { 118, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_PS3, Servo1_ColIdx), 44, 3, 2, 236, "", 0 },

  { 119, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo1/Table", offsetof
    (Parameters_PS3, Servo1_Table), 45, 9, 2, 238, "", 0 },

  { 120, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex", offsetof
    (Parameters_PS3, Servo2_RowIdx), 44, 3, 2, 240, "", 0 },

  { 121, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_PS3, Servo2_ColIdx), 44, 3, 2, 242, "", 0 },

  { 122, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo2/Table", offsetof
    (Parameters_PS3, Servo2_Table), 45, 9, 2, 244, "", 0 },

  { 123, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex", offsetof
    (Parameters_PS3, Servo3_RowIdx), 44, 3, 2, 246, "", 0 },

  { 124, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_PS3, Servo3_ColIdx), 44, 3, 2, 248, "", 0 },

  { 125, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo3/Table", offsetof
    (Parameters_PS3, Servo3_Table), 45, 9, 2, 250, "", 0 },

  { 126, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex", offsetof
    (Parameters_PS3, Servo4_RowIdx), 44, 3, 2, 252, "", 0 },

  { 127, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_PS3, Servo4_ColIdx), 44, 3, 2, 254, "", 0 },

  { 128, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo4/Table", offsetof
    (Parameters_PS3, Servo4_Table), 45, 9, 2, 256, "", 0 },

  { 129, "ps3/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_PS3, VPS_Speed_Gain_Gain), 37, 1, 2, 258, "", 0 },

  { 130, "ps3/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_PS3, VPS_Power_Offset_Value), 37, 1, 2, 260, "", 0 },

  { 131, "ps3/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain", offsetof
    (Parameters_PS3, VSPSPort_Gain), 37, 1, 2, 262, "", 0 },

  { 132, "ps3/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_PS3, VSPSStarboard_Gain), 37, 1, 2, 264, "", 0 },

  { 133,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_PS3, Gain_Gain), 46, 1, 2, 266, "", 0 },

  { 134,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_PS3, Gain1_Gain), 46, 1, 2, 268, "", 0 },

  { 135,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_PS3, Gain_Gain_h), 46, 1, 2, 270, "", 0 },

  { 136,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_PS3, Gain1_Gain_p), 46, 1, 2, 272, "", 0 },

  { 137,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_PS3, Gain_Gain_f), 46, 1, 2, 274, "", 0 },

  { 138,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_PS3, Gain1_Gain_o), 46, 1, 2, 276, "", 0 },

  { 139,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_PS3, Gain_Gain_b), 46, 1, 2, 278, "", 0 },

  { 140,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_PS3, Gain1_Gain_l), 46, 1, 2, 280, "", 0 },

  { 141,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_PS3, Gain_Gain_g), 46, 1, 2, 282, "", 0 },

  { 142,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_PS3, Gain1_Gain_k), 46, 1, 2, 284, "", 0 },
};

static int NI_ParamListSize = 143;
static int NI_ParamDimList[] = {
  1, 1,                                /* ps3/Control Systems/Control Mode/Value */
  1, 1,                                /* ps3/Control Systems/PS3 input/AS_LY/Value */
  1, 1,                                /* ps3/Control Systems/PS3 input/ScalingLY/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 u input control/PS3 u_1/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 input/AS_LX/Value */
  1, 1,                                /* ps3/Control Systems/PS3 input/ScalingLX/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 u input control/PS3 u_2/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 input/AS_RY/Value */
  1, 1,                                /* ps3/Control Systems/PS3 input/ScalingRY/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 u input control/PS3 u_3/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 input/AS_RX/Value */
  1, 1,                                /* ps3/Control Systems/PS3 input/Scaling_RX/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 u input control/PS3 u_4/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 input/L2/Value */
  1, 1,                                /* ps3/Control Systems/PS3 input/R2/Value */
  1, 1,                                /* ps3/Control Systems/PS3 u input control/PS3 u_5/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 input/PS3_BT_Power/Value */
  1, 1,                                /* ps3/Control Systems/PS3 input/PS3_VSP_Speed/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/tau_surge/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/tau_sway/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/tau_yaw/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Saturation/UpperLimit */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Saturation/LowerLimit */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Joystick u_1/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Joystick u_2/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Joystick u_3/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Joystick u_4/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Joystick u_5/Gain */
  1, 1,                                /* ps3/Control Systems/Saturation/UpperLimit */
  1, 1,                                /* ps3/Control Systems/Saturation/LowerLimit */
  1, 1,                                /* ps3/Plants/plant u_1/Gain */
  1, 1,                                /* ps3/Plants/plant u_2/Gain */
  1, 1,                                /* ps3/Plants/plant u_3/Gain */
  1, 1,                                /* ps3/Plants/plant u_4/Gain */
  1, 1,                                /* ps3/Plants/plant u_5/Gain */
  1, 1,                                /* ps3/Plants/plant BT power/Gain */
  1, 1,                                /* ps3/Plants/plant VSP speed/Gain */
  1, 1,                                /* ps3/Plants/Enable CSE1/Value */
  1, 1,                                /* ps3/HMI/Battery Bow Thruster/Gain */
  1, 1,                                /* ps3/HMI/Battery Servo/Gain */
  1, 1,                                /* ps3/HMI/Battery Main/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/Constant/Value */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/Constant1/Value */
  1, 1,                                /* ps3/Plants/CSE1/Bow Thruster/Neg/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* ps3/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 128;
static NI_Signal NI_SigList[] = {
  { 0, "ps3/Control Systems/PS3 input/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_PS3,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "ps3/Control Systems/PS3 u input control/PS3 u_1", 0, "u_1", offsetof
    (BlockIO_PS3, u_1), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "ps3/Control Systems/PS3 input/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_PS3,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "ps3/Control Systems/PS3 u input control/PS3 u_2", 0, "u_2", offsetof
    (BlockIO_PS3, u_2), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "ps3/Control Systems/PS3 input/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_PS3,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "ps3/Control Systems/PS3 u input control/PS3 u_3", 0, "u_3", offsetof
    (BlockIO_PS3, u_3), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "ps3/Control Systems/PS3 input/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_PS3,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "ps3/Control Systems/PS3 u input control/PS3 u_4", 0, "u_4", offsetof
    (BlockIO_PS3, u_4), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "ps3/Control Systems/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_PS3, BowThrusterdirection),
    BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "ps3/Control Systems/PS3 u input control/PS3 u_5", 0, "u_5", offsetof
    (BlockIO_PS3, u_5), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_PS3, l_x1), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_PS3, l_y2), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_PS3, l_x2), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_PS3, x5), BLOCKIO_SIG, 25, 15, 2, 26, 0 },

  { 14,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_PS3, Pseudoinverse), BLOCKIO_SIG, 24, 15, 2, 28, 0 },

  { 15, "ps3/Control Systems/PS3 tau input control/Sum1", 0, "", offsetof
    (BlockIO_PS3, Sum1), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "ps3/Control Systems/PS3 tau input control/tau_surge", 0, "", offsetof
    (BlockIO_PS3, tau_surge), BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "ps3/Control Systems/PS3 tau input control/Sum2", 0, "", offsetof
    (BlockIO_PS3, Sum2), BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "ps3/Control Systems/PS3 tau input control/tau_sway", 0, "", offsetof
    (BlockIO_PS3, tau_sway), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "ps3/Control Systems/PS3 tau input control/Sum", 0, "", offsetof
    (BlockIO_PS3, Sum), BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "ps3/Control Systems/PS3 tau input control/tau_yaw", 0, "", offsetof
    (BlockIO_PS3, tau_yaw), BLOCKIO_SIG, 0, 1, 2, 40, 0 },

  { 21,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_PS3, Product), BLOCKIO_SIG, 22, 5, 2, 42, 0 },

  { 22,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone",
    0, "", offsetof(BlockIO_PS3, DeadZone), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { 23,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_PS3, f_10), BLOCKIO_SIG, 0, 1, 2, 46, 0 },

  { 24,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_PS3, f_10_m), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_PS3, MultiportSwitch), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone",
    0, "", offsetof(BlockIO_PS3, DeadZone_h), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_PS3, f_20), BLOCKIO_SIG, 0, 1, 2, 54, 0 },

  { 28,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_PS3, f_20_i), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_PS3, MultiportSwitch_e), BLOCKIO_SIG, 0, 1, 2, 58, 0
  },

  { 30,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone",
    0, "", offsetof(BlockIO_PS3, DeadZone_b), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_PS3, f_30), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_PS3, f_30_b), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_PS3, MultiportSwitch_f), BLOCKIO_SIG, 0, 1, 2, 66, 0
  },

  { 34,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone",
    0, "", offsetof(BlockIO_PS3, DeadZone_f), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_PS3, f_40), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_PS3, f_40_k), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_PS3, MultiportSwitch_h), BLOCKIO_SIG, 0, 1, 2, 74, 0
  },

  { 38,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone",
    0, "", offsetof(BlockIO_PS3, DeadZone_l), BLOCKIO_SIG, 0, 1, 2, 76, 0 },

  { 39,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_PS3, f_50), BLOCKIO_SIG, 0, 1, 2, 78, 0 },

  { 40,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_PS3, f_50_c), BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_PS3, MultiportSwitch_p), BLOCKIO_SIG, 0, 1, 2, 82, 0
  },

  { 42, "ps3/Control Systems/PS3 tau input control/Saturation", 0, "", offsetof
    (BlockIO_PS3, Saturation), BLOCKIO_SIG, 22, 5, 2, 84, 0 },

  { 43, "ps3/Control Systems/PS3 tau input control/Joystick u_1", 0, "",
    offsetof(BlockIO_PS3, Joysticku_1), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44, "ps3/Control Systems/PS3 tau input control/Joystick u_2", 0, "",
    offsetof(BlockIO_PS3, Joysticku_2), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "ps3/Control Systems/PS3 tau input control/Joystick u_3", 0, "",
    offsetof(BlockIO_PS3, Joysticku_3), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46, "ps3/Control Systems/PS3 tau input control/Joystick u_4", 0, "",
    offsetof(BlockIO_PS3, Joysticku_4), BLOCKIO_SIG, 0, 1, 2, 92, 0 },

  { 47, "ps3/Control Systems/PS3 tau input control/Joystick u_5", 0, "",
    offsetof(BlockIO_PS3, Joysticku_5), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48, "ps3/Control Systems/Thruster setting Switch", 0, "", offsetof
    (BlockIO_PS3, ThrustersettingSwitch), BLOCKIO_SIG, 20, 7, 2, 96, 0 },

  { 49, "ps3/Control Systems/Saturation", 0, "", offsetof(BlockIO_PS3,
    Saturation_f), BLOCKIO_SIG, 20, 7, 2, 98, 0 },

  { 50, "ps3/Plants/plant u_1", 0, "", offsetof(BlockIO_PS3, plantu_1),
    BLOCKIO_SIG, 0, 1, 2, 100, 0 },

  { 51, "ps3/Plants/plant u_2", 0, "", offsetof(BlockIO_PS3, plantu_2),
    BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52, "ps3/Plants/plant u_3", 0, "", offsetof(BlockIO_PS3, plantu_3),
    BLOCKIO_SIG, 0, 1, 2, 104, 0 },

  { 53, "ps3/Plants/plant u_4", 0, "", offsetof(BlockIO_PS3, plantu_4),
    BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "ps3/Plants/plant u_5", 0, "", offsetof(BlockIO_PS3, plantu_5),
    BLOCKIO_SIG, 0, 1, 2, 108, 0 },

  { 55, "ps3/Plants/plant BT power", 0, "", offsetof(BlockIO_PS3, plantBTpower),
    BLOCKIO_SIG, 0, 1, 2, 110, 0 },

  { 56, "ps3/Plants/plant VSP speed", 0, "", offsetof(BlockIO_PS3, plantVSPspeed),
    BLOCKIO_SIG, 0, 1, 2, 112, 0 },

  { 57, "ps3/HMI/SIT zAI0", 0, "", offsetof(BlockIO_PS3, SITzAI0), BLOCKIO_SIG,
    0, 1, 2, 114, 0 },

  { 58, "ps3/HMI/Battery Bow Thruster", 0, "", offsetof(BlockIO_PS3,
    BatteryBowThruster), BLOCKIO_SIG, 0, 1, 2, 116, 0 },

  { 59, "ps3/HMI/SIT zAI1", 0, "", offsetof(BlockIO_PS3, SITzAI1), BLOCKIO_SIG,
    0, 1, 2, 118, 0 },

  { 60, "ps3/HMI/Battery Servo", 0, "", offsetof(BlockIO_PS3, BatteryServo),
    BLOCKIO_SIG, 0, 1, 2, 120, 0 },

  { 61, "ps3/HMI/SIT zAI2", 0, "", offsetof(BlockIO_PS3, SITzAI2), BLOCKIO_SIG,
    0, 1, 2, 122, 0 },

  { 62, "ps3/HMI/Battery Main", 0, "", offsetof(BlockIO_PS3, BatteryMain),
    BLOCKIO_SIG, 0, 1, 2, 124, 0 },

  { 63, "ps3/Plants/CSE1/Bow Thruster/BT_D_Gain1", 0, "", offsetof(BlockIO_PS3,
    BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2, 126, 0 },

  { 64, "ps3/Plants/CSE1/Bow Thruster/BT_D_Gain2", 0, "", offsetof(BlockIO_PS3,
    BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2, 128, 0 },

  { 65, "ps3/Plants/CSE1/Bow Thruster/Add", 0, "", offsetof(BlockIO_PS3, Add),
    BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66, "ps3/Plants/CSE1/Bow Thruster/BT_L_Gain1", 0, "", offsetof(BlockIO_PS3,
    BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2, 132, 0 },

  { 67, "ps3/Plants/CSE1/Bow Thruster/BT_L_Gain2", 0, "", offsetof(BlockIO_PS3,
    BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2, 134, 0 },

  { 68, "ps3/Plants/CSE1/Bow Thruster/Neg", 0, "", offsetof(BlockIO_PS3, Neg),
    BLOCKIO_SIG, 0, 1, 2, 136, 0 },

  { 69, "ps3/Plants/CSE1/Bow Thruster/Sum1", 0, "", offsetof(BlockIO_PS3, Sum1_d),
    BLOCKIO_SIG, 0, 1, 2, 138, 0 },

  { 70, "ps3/Plants/CSE1/Bow Thruster/Sum2", 0, "", offsetof(BlockIO_PS3, Sum2_o),
    BLOCKIO_SIG, 0, 1, 2, 140, 0 },

  { 71, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch", 0, "",
    offsetof(BlockIO_PS3, Switch), BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch2", 0, "",
    offsetof(BlockIO_PS3, Switch2), BLOCKIO_SIG, 0, 1, 2, 144, 0 },

  { 73, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch", 0, "",
    offsetof(BlockIO_PS3, Switch_e), BLOCKIO_SIG, 0, 1, 2, 146, 0 },

  { 74, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch2", 0, "",
    offsetof(BlockIO_PS3, Switch2_i), BLOCKIO_SIG, 0, 1, 2, 148, 0 },

  { 75, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch", 0, "",
    offsetof(BlockIO_PS3, Switch_o), BLOCKIO_SIG, 0, 1, 2, 150, 0 },

  { 76, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch2", 0, "",
    offsetof(BlockIO_PS3, Switch2_c), BLOCKIO_SIG, 0, 1, 2, 152, 0 },

  { 77, "ps3/Plants/CSE1/Voith Schneider Propeller /Sign", 0, "", offsetof
    (BlockIO_PS3, Sign), BLOCKIO_SIG, 0, 1, 2, 154, 0 },

  { 78, "ps3/Plants/CSE1/Voith Schneider Propeller /Product1", 0, "Port VPS_X",
    offsetof(BlockIO_PS3, PortVPS_X), BLOCKIO_SIG, 0, 1, 2, 156, 0 },

  { 79, "ps3/Plants/CSE1/Voith Schneider Propeller /-x", 0, "Port VPS_X",
    offsetof(BlockIO_PS3, PortVPS_X_o), BLOCKIO_SIG, 0, 1, 2, 158, 0 },

  { 80, "ps3/Plants/CSE1/Voith Schneider Propeller /Product2", 0, "Port VSP_Y",
    offsetof(BlockIO_PS3, PortVSP_Y), BLOCKIO_SIG, 0, 1, 2, 160, 0 },

  { 81, "ps3/Plants/CSE1/Voith Schneider Propeller /-y", 0, "Port VSP_Y",
    offsetof(BlockIO_PS3, PortVSP_Y_b), BLOCKIO_SIG, 0, 1, 2, 162, 0 },

  { 82, "ps3/Plants/CSE1/Voith Schneider Propeller /Product3", 0,
    "Starboard VSP_X", offsetof(BlockIO_PS3, StarboardVSP_X), BLOCKIO_SIG, 0, 1,
    2, 164, 0 },

  { 83, "ps3/Plants/CSE1/Voith Schneider Propeller /Product4", 0,
    "Starboard VSP_Y", offsetof(BlockIO_PS3, StarboardVSP_Y), BLOCKIO_SIG, 0, 1,
    2, 166, 0 },

  { 84, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo1", 0, "", offsetof
    (BlockIO_PS3, Servo1), BLOCKIO_SIG, 0, 1, 2, 168, 0 },

  { 85, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo2", 0, "", offsetof
    (BlockIO_PS3, Servo2), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo3", 0, "", offsetof
    (BlockIO_PS3, Servo3), BLOCKIO_SIG, 0, 1, 2, 172, 0 },

  { 87, "ps3/Plants/CSE1/Voith Schneider Propeller /Servo4", 0, "", offsetof
    (BlockIO_PS3, Servo4), BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88, "ps3/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain", 0, "",
    offsetof(BlockIO_PS3, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2, 176, 0 },

  { 89, "ps3/Plants/CSE1/Voith Schneider Propeller /Sum", 0, "", offsetof
    (BlockIO_PS3, Sum_o), BLOCKIO_SIG, 0, 1, 2, 178, 0 },

  { 90, "ps3/Plants/CSE1/Voith Schneider Propeller /VSPS Port", 0, "", offsetof
    (BlockIO_PS3, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91, "ps3/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard", 0, "",
    offsetof(BlockIO_PS3, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_PS3, Gain), BLOCKIO_SIG, 15, 1, 2, 184, 0 },

  { 93,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_PS3, Gain1), BLOCKIO_SIG, 15, 1, 2, 186, 0 },

  { 94,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_PS3, Sum_ow), BLOCKIO_SIG, 15, 1, 2, 188, 0 },

  { 95,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_PS3, Gain_k), BLOCKIO_SIG, 15, 1, 2, 190, 0 },

  { 96,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_PS3, Gain1_l), BLOCKIO_SIG, 15, 1, 2, 192, 0 },

  { 97,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_PS3, Sum_i), BLOCKIO_SIG, 15, 1, 2, 194, 0 },

  { 98,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_PS3, Gain_f), BLOCKIO_SIG, 15, 1, 2, 196, 0 },

  { 99,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_PS3, Gain1_i), BLOCKIO_SIG, 15, 1, 2, 198, 0 },

  { 100,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_PS3, Sum_f), BLOCKIO_SIG, 15, 1, 2, 200, 0 },

  { 101,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_PS3, Gain_m), BLOCKIO_SIG, 15, 1, 2, 202, 0 },

  { 102,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_PS3, Gain1_g), BLOCKIO_SIG, 15, 1, 2, 204, 0 },

  { 103,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_PS3, Sum_l), BLOCKIO_SIG, 15, 1, 2, 206, 0 },

  { 104,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_PS3, Gain_o), BLOCKIO_SIG, 15, 1, 2, 208, 0 },

  { 105,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_PS3, Gain1_p), BLOCKIO_SIG, 15, 1, 2, 210, 0 },

  { 106,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_PS3, Sum_g), BLOCKIO_SIG, 15, 1, 2, 212, 0 },

  { 107,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare), BLOCKIO_SIG, 3, 1, 2, 214, 0 },

  { 108,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_a), BLOCKIO_SIG, 3, 1, 2, 216, 0 },

  { 109,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_d), BLOCKIO_SIG, 3, 1, 2, 218, 0 },

  { 110,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_i), BLOCKIO_SIG, 3, 1, 2, 220, 0 },

  { 111,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_ab), BLOCKIO_SIG, 3, 1, 2, 222, 0 },

  { 112,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_h), BLOCKIO_SIG, 3, 1, 2, 224, 0 },

  { 113,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_dd), BLOCKIO_SIG, 3, 1, 2, 226, 0 },

  { 114,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_c), BLOCKIO_SIG, 3, 1, 2, 228, 0 },

  { 115,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_af), BLOCKIO_SIG, 3, 1, 2, 230, 0 },

  { 116,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_ak), BLOCKIO_SIG, 3, 1, 2, 232, 0 },

  { 117,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_av), BLOCKIO_SIG, 3, 1, 2, 234, 0 },

  { 118,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_p), BLOCKIO_SIG, 3, 1, 2, 236, 0 },

  { 119,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_p5), BLOCKIO_SIG, 3, 1, 2, 238, 0 },

  { 120,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_l), BLOCKIO_SIG, 3, 1, 2, 240, 0 },

  { 121,
    "ps3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_PS3, Compare_c4), BLOCKIO_SIG, 3, 1, 2, 242, 0 },

  { 122, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic/LowerRelop1", 0, "",
    offsetof(BlockIO_PS3, LowerRelop1), BLOCKIO_SIG, 8, 1, 2, 244, 0 },

  { 123, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic/UpperRelop", 0, "",
    offsetof(BlockIO_PS3, UpperRelop), BLOCKIO_SIG, 8, 1, 2, 246, 0 },

  { 124, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic1/LowerRelop1", 0, "",
    offsetof(BlockIO_PS3, LowerRelop1_c), BLOCKIO_SIG, 8, 1, 2, 248, 0 },

  { 125, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic1/UpperRelop", 0, "",
    offsetof(BlockIO_PS3, UpperRelop_o), BLOCKIO_SIG, 8, 1, 2, 250, 0 },

  { 126, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic2/LowerRelop1", 0, "",
    offsetof(BlockIO_PS3, LowerRelop1_g), BLOCKIO_SIG, 8, 1, 2, 252, 0 },

  { 127, "ps3/Plants/CSE1/Bow Thruster/Saturation Dynamic2/UpperRelop", 0, "",
    offsetof(BlockIO_PS3, UpperRelop_g), BLOCKIO_SIG, 8, 1, 2, 254, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  3, 5, 5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 7, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize = 10;
static NI_ExternalIO NI_ExtList[] = {
  { 0, "HMI/SIT zAI0", 0, EXT_IN, 1, 1, 1 },

  { 1, "HMI/SIT zAI1", 0, EXT_IN, 1, 1, 1 },

  { 2, "HMI/SIT zAI2", 0, EXT_IN, 1, 1, 1 },

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

static char* NI_CompiledModelName = "ps3";
static char* NI_CompiledModelVersion = "1.6";
static char* NI_CompiledModelDateTime = "Sun Mar 16 16:15:48 2014";

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
   The undef allows us to access the real PS3_P
   In the rest of the code PS3_P is redefine to be the read-side
   of rtParameter.
 */
#undef PS3_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &PS3_P, sizeof(Parameters_PS3));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka PS3_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_PS3));
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
             (Parameters_PS3));

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
           (Parameters_PS3));
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

#endif                                 // of NI_ROOTMODEL_PS3
