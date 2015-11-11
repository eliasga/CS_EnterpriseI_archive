/*
 * uao2pwm.c
 *
 * Code generation for model "uao2pwm".
 *
 * Model version              : 1.21
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 25 17:24:35 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "uao2pwm.h"
#include "uao2pwm_private.h"

/* Block signals (auto storage) */
B_uao2pwm_T uao2pwm_B;

/* Block states (auto storage) */
DW_uao2pwm_T uao2pwm_DW;

/* Real-time model */
RT_MODEL_uao2pwm_T uao2pwm_M_;
RT_MODEL_uao2pwm_T *const uao2pwm_M = &uao2pwm_M_;
real_T look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const real_T bp1[],
                     const real_T table[], const uint32_T maxIndex[], uint32_T
                     stride)
{
  real_T frac;
  uint32_T bpIndices[2];
  real_T fractions[2];
  real_T yL_1d;
  uint32_T iRght;
  uint32_T bpIdx;
  uint32_T iLeft;

  /* Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  /* Interpolation 2-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_1d = (table[bpIdx + 1U] - table[bpIdx]) * fractions[0U] + table[bpIdx];
  bpIdx += stride;
  return (((table[bpIdx + 1U] - table[bpIdx]) * fractions[0U] + table[bpIdx]) -
          yL_1d) * frac + yL_1d;
}

/* Model output function */
static void uao2pwm_output(void)
{
  real_T rtb_Product5;
  real_T rtb_Gain1;
  real_T rtb_Product9;

  /* Saturate: '<Root>/Saturation1' */
  if (uao2pwm_B.omega_VSP1 > uao2pwm_P.Saturation1_UpperSat) {
    rtb_Product5 = uao2pwm_P.Saturation1_UpperSat;
  } else if (uao2pwm_B.omega_VSP1 < uao2pwm_P.Saturation1_LowerSat) {
    rtb_Product5 = uao2pwm_P.Saturation1_LowerSat;
  } else {
    rtb_Product5 = uao2pwm_B.omega_VSP1;
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/VPS_Power_Offset'
   *  Gain: '<Root>/VPS_Speed_Gain'
   *  Saturate: '<Root>/Saturation1'
   */
  uao2pwm_B.Sum1 = uao2pwm_P.VSP_u2pwm_gain * rtb_Product5 +
    uao2pwm_P.VSP_zero_pwm;

  /* Saturate: '<Root>/Saturation2' */
  if (uao2pwm_B.omega_VSP2 > uao2pwm_P.Saturation2_UpperSat) {
    rtb_Product5 = uao2pwm_P.Saturation2_UpperSat;
  } else if (uao2pwm_B.omega_VSP2 < uao2pwm_P.Saturation2_LowerSat) {
    rtb_Product5 = uao2pwm_P.Saturation2_LowerSat;
  } else {
    rtb_Product5 = uao2pwm_B.omega_VSP2;
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/VPS_Power_Offset'
   *  Gain: '<Root>/VPS_Speed_Gain2'
   *  Saturate: '<Root>/Saturation2'
   */
  uao2pwm_B.Sum = uao2pwm_P.VSP_u2pwm_gain * rtb_Product5 +
    uao2pwm_P.VSP_zero_pwm;

  /* Saturate: '<Root>/Saturation' */
  if (uao2pwm_B.u_BT > uao2pwm_P.Saturation_UpperSat) {
    rtb_Product5 = uao2pwm_P.Saturation_UpperSat;
  } else if (uao2pwm_B.u_BT < uao2pwm_P.Saturation_LowerSat) {
    rtb_Product5 = uao2pwm_P.Saturation_LowerSat;
  } else {
    rtb_Product5 = uao2pwm_B.u_BT;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/VPS_Power_Offset1'
   *  Gain: '<Root>/VPS_Speed_Gain1'
   *  Saturate: '<Root>/Saturation'
   */
  uao2pwm_B.Sum2 = uao2pwm_P.BT_u2pwm_gain * rtb_Product5 +
    uao2pwm_P.BT_zero_pwm;

  /* Saturate: '<Root>/Saturation3' */
  if (uao2pwm_B.u_VSP2 > uao2pwm_P.Saturation3_UpperSat) {
    rtb_Product5 = uao2pwm_P.Saturation3_UpperSat;
  } else if (uao2pwm_B.u_VSP2 < uao2pwm_P.Saturation3_LowerSat) {
    rtb_Product5 = uao2pwm_P.Saturation3_LowerSat;
  } else {
    rtb_Product5 = uao2pwm_B.u_VSP2;
  }

  /* End of Saturate: '<Root>/Saturation3' */

  /* Sum: '<Root>/Sum4' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  rtb_Gain1 = uao2pwm_P.Constant1_Value + uao2pwm_B.alpha_VSP2;

  /* Lookup_n-D: '<Root>/2-D Lookup Table3' incorporates:
   *  Gain: '<Root>/Gain3'
   *  Product: '<Root>/Product10'
   *  Product: '<Root>/Product11'
   *  Trigonometry: '<Root>/Trigonometric Function10'
   *  Trigonometry: '<Root>/Trigonometric Function11'
   */
  uao2pwm_B.DLookupTable3 = look2_binlxpw(rtb_Product5 * cos(rtb_Gain1) *
    uao2pwm_P.Gain3_Gain, rtb_Product5 * sin(rtb_Gain1),
    uao2pwm_P.DLookupTable3_bp01Data, uao2pwm_P.DLookupTable3_bp02Data,
    uao2pwm_P.DLookupTable3_tableData, uao2pwm_P.DLookupTable3_maxIndex, 5U);

  /* Gain: '<Root>/Gain2' incorporates:
   *  Product: '<Root>/Product7'
   *  Trigonometry: '<Root>/Trigonometric Function6'
   */
  rtb_Product9 = rtb_Product5 * cos(rtb_Gain1) * uao2pwm_P.Gain2_Gain;

  /* Product: '<Root>/Product8' incorporates:
   *  Trigonometry: '<Root>/Trigonometric Function7'
   */
  rtb_Product5 *= sin(rtb_Gain1);

  /* Lookup_n-D: '<Root>/2-D Lookup Table2' */
  uao2pwm_B.DLookupTable2 = look2_binlxpw(rtb_Product9, rtb_Product5,
    uao2pwm_P.DLookupTable2_bp01Data, uao2pwm_P.DLookupTable2_bp02Data,
    uao2pwm_P.DLookupTable2_tableData, uao2pwm_P.DLookupTable2_maxIndex, 5U);

  /* Saturate: '<Root>/Saturation4' */
  if (uao2pwm_B.u_VSP1 > uao2pwm_P.Saturation4_UpperSat) {
    rtb_Product5 = uao2pwm_P.Saturation4_UpperSat;
  } else if (uao2pwm_B.u_VSP1 < uao2pwm_P.Saturation4_LowerSat) {
    rtb_Product5 = uao2pwm_P.Saturation4_LowerSat;
  } else {
    rtb_Product5 = uao2pwm_B.u_VSP1;
  }

  /* Gain: '<Root>/Gain4' incorporates:
   *  Saturate: '<Root>/Saturation4'
   */
  rtb_Product9 = uao2pwm_P.Gain4_Gain * rtb_Product5;

  /* Sum: '<Root>/Sum3' incorporates:
   *  Constant: '<Root>/Constant'
   */
  rtb_Product5 = uao2pwm_B.alpha_VSP1 - uao2pwm_P.Constant_Value;

  /* Lookup_n-D: '<Root>/2-D Lookup Table' incorporates:
   *  Gain: '<Root>/Gain'
   *  Product: '<Root>/Product'
   *  Product: '<Root>/Product5'
   *  Trigonometry: '<Root>/Trigonometric Function4'
   *  Trigonometry: '<Root>/Trigonometric Function5'
   */
  uao2pwm_B.DLookupTable = look2_binlxpw(rtb_Product9 * cos(rtb_Product5) *
    uao2pwm_P.Gain_Gain, rtb_Product9 * sin(rtb_Product5),
    uao2pwm_P.DLookupTable_bp01Data, uao2pwm_P.DLookupTable_bp02Data,
    uao2pwm_P.DLookupTable_tableData, uao2pwm_P.DLookupTable_maxIndex, 5U);

  /* Gain: '<Root>/Gain1' incorporates:
   *  Product: '<Root>/Product6'
   *  Trigonometry: '<Root>/Trigonometric Function8'
   */
  rtb_Gain1 = rtb_Product9 * cos(rtb_Product5) * uao2pwm_P.Gain1_Gain;

  /* Product: '<Root>/Product9' incorporates:
   *  Trigonometry: '<Root>/Trigonometric Function9'
   */
  rtb_Product9 *= sin(rtb_Product5);

  /* Lookup_n-D: '<Root>/2-D Lookup Table1' */
  uao2pwm_B.DLookupTable1 = look2_binlxpw(rtb_Gain1, rtb_Product9,
    uao2pwm_P.DLookupTable1_bp01Data, uao2pwm_P.DLookupTable1_bp02Data,
    uao2pwm_P.DLookupTable1_tableData, uao2pwm_P.DLookupTable1_maxIndex, 5U);
}

/* Model update function */
static void uao2pwm_update(void)
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
  if (!(++uao2pwm_M->Timing.clockTick0)) {
    ++uao2pwm_M->Timing.clockTickH0;
  }

  uao2pwm_M->Timing.t[0] = uao2pwm_M->Timing.clockTick0 *
    uao2pwm_M->Timing.stepSize0 + uao2pwm_M->Timing.clockTickH0 *
    uao2pwm_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void uao2pwm_initialize(void)
{
}

/* Model terminate function */
void uao2pwm_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  uao2pwm_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  uao2pwm_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  uao2pwm_initialize();
}

void MdlTerminate(void)
{
  uao2pwm_terminate();
}

/* Registration function */
RT_MODEL_uao2pwm_T *uao2pwm(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)uao2pwm_M, 0,
                sizeof(RT_MODEL_uao2pwm_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = uao2pwm_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    uao2pwm_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    uao2pwm_M->Timing.sampleTimes = (&uao2pwm_M->Timing.sampleTimesArray[0]);
    uao2pwm_M->Timing.offsetTimes = (&uao2pwm_M->Timing.offsetTimesArray[0]);

    /* task periods */
    uao2pwm_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    uao2pwm_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(uao2pwm_M, &uao2pwm_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = uao2pwm_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    uao2pwm_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(uao2pwm_M, -1);
  uao2pwm_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    uao2pwm_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(uao2pwm_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(uao2pwm_M->rtwLogInfo, (NULL));
    rtliSetLogT(uao2pwm_M->rtwLogInfo, "tout");
    rtliSetLogX(uao2pwm_M->rtwLogInfo, "");
    rtliSetLogXFinal(uao2pwm_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(uao2pwm_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(uao2pwm_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(uao2pwm_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(uao2pwm_M->rtwLogInfo, 1);
    rtliSetLogY(uao2pwm_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(uao2pwm_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(uao2pwm_M->rtwLogInfo, (NULL));
  }

  uao2pwm_M->solverInfoPtr = (&uao2pwm_M->solverInfo);
  uao2pwm_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&uao2pwm_M->solverInfo, 0.01);
  rtsiSetSolverMode(&uao2pwm_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  uao2pwm_M->ModelData.blockIO = ((void *) &uao2pwm_B);
  (void) memset(((void *) &uao2pwm_B), 0,
                sizeof(B_uao2pwm_T));

  /* parameters */
  uao2pwm_M->ModelData.defaultParam = ((real_T *)&uao2pwm_P);

  /* states (dwork) */
  uao2pwm_M->ModelData.dwork = ((void *) &uao2pwm_DW);
  (void) memset((void *)&uao2pwm_DW, 0,
                sizeof(DW_uao2pwm_T));

  /* Initialize Sizes */
  uao2pwm_M->Sizes.numContStates = (0);/* Number of continuous states */
  uao2pwm_M->Sizes.numY = (0);         /* Number of model outputs */
  uao2pwm_M->Sizes.numU = (0);         /* Number of model inputs */
  uao2pwm_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  uao2pwm_M->Sizes.numSampTimes = (1); /* Number of sample times */
  uao2pwm_M->Sizes.numBlocks = (57);   /* Number of blocks */
  uao2pwm_M->Sizes.numBlockIO = (14);  /* Number of block outputs */
  uao2pwm_M->Sizes.numBlockPrms = (254);/* Sum of parameter "widths" */
  return uao2pwm_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================*
 * This file contains automatically generated code for functions
 * to update the inports and outports of a Simulink/Realtime Workshop
 * model. Calls to these functions should be made before each step is taken
 * (inports, call SetExternalInputs) and after each step is taken
 * (outports, call SetExternalOutputs.)
 */
#ifdef NI_ROOTMODEL_uao2pwm
#include "model_info.h"
#include <stddef.h>
#include <stdlib.h>
#include <float.h>

unsigned char ReadSideDirtyFlag = 0, WriteSideDirtyFlag = 0;
double NIRT_GetValueByDataType(void* ptr,int subindex, int type, int Complex)
{
  switch (type)
  {
   case 0:
    return (double)(((real_T*)ptr)[subindex]);

   case 1:
    return (double)(((real32_T*)ptr)[subindex]);

   case 2:
    return (double)(((int8_T*)ptr)[subindex]);

   case 3:
    return (double)(((uint8_T*)ptr)[subindex]);

   case 4:
    return (double)(((int16_T*)ptr)[subindex]);

   case 5:
    return (double)(((uint16_T*)ptr)[subindex]);

   case 6:
    return (double)(((int32_T*)ptr)[subindex]);

   case 7:
    return (double)(((uint32_T*)ptr)[subindex]);

   case 8:
    return (double)(((boolean_T*)ptr)[subindex]);

   case 10:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 13:
    return NIRT_GetValueByDataType(ptr,subindex,7,Complex);

   case 15:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 16:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 17:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 18:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 19:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 20:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 21:
    return NIRT_GetValueByDataType(ptr,subindex,7,Complex);

   case 22:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 26:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 27:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 28:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 29:
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

   case 15:
    //Type is enum. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 16:
    //Type is enum. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 17:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 18:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 21:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,7,Complex);

   case 22:
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
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern uao2pwm_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // alpha_VSP1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&uao2pwm_B.alpha_VSP1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // omega_VSP1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&uao2pwm_B.omega_VSP1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // u_VSP1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&uao2pwm_B.u_VSP1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // omega_VSP2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&uao2pwm_B.omega_VSP2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // alpha_VSP2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&uao2pwm_B.alpha_VSP2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // u_BT
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&uao2pwm_B.u_BT, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // u_VSP2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&uao2pwm_B.u_VSP2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 7;
}

double ni_extout[7];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // pwm_VSP1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.Sum1,0,0,0);
  } else {
    index += 1;
  }

  // pwm_VSP2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.Sum,0,0,0);
  } else {
    index += 1;
  }

  // pwm_BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.Sum2,0,0,0);
  } else {
    index += 1;
  }

  // pwm_servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.DLookupTable3,0,0,0);
  } else {
    index += 1;
  }

  // pwm_servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.DLookupTable2,0,0,0);
  } else {
    index += 1;
  }

  // pwm_servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.DLookupTable,0,0,0);
  } else {
    index += 1;
  }

  // pwm_servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.DLookupTable1,0,0,0);
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

  // pwm_VSP1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.Sum1,0,0,0);

  // pwm_VSP2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.Sum,0,0,0);

  // pwm_BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.Sum2,0,0,0);

  // pwm_servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.DLookupTable3,0,0,0);

  // pwm_servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.DLookupTable2,0,0,0);

  // pwm_servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.DLookupTable,0,0,0);

  // pwm_servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&uao2pwm_B.DLookupTable1,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "uao2pwm/VPS_Speed_Gain1/Gain", offsetof(P_uao2pwm_T, BT_u2pwm_gain), 26,
    1, 2, 0, 0 },

  { 1, "uao2pwm/VPS_Power_Offset1/Value", offsetof(P_uao2pwm_T, BT_zero_pwm), 26,
    1, 2, 2, 0 },

  { 2, "uao2pwm/VPS_Speed_Gain/Gain", offsetof(P_uao2pwm_T, VSP_u2pwm_gain), 26,
    1, 2, 4, 0 },

  { 3, "uao2pwm/VPS_Speed_Gain2/Gain", offsetof(P_uao2pwm_T, VSP_u2pwm_gain), 26,
    1, 2, 6, 0 },

  { 4, "uao2pwm/VPS_Power_Offset/Value", offsetof(P_uao2pwm_T, VSP_zero_pwm), 26,
    1, 2, 8, 0 },

  { 5, "uao2pwm/Saturation1/UpperLimit", offsetof(P_uao2pwm_T,
    Saturation1_UpperSat), 26, 1, 2, 10, 0 },

  { 6, "uao2pwm/Saturation1/LowerLimit", offsetof(P_uao2pwm_T,
    Saturation1_LowerSat), 26, 1, 2, 12, 0 },

  { 7, "uao2pwm/Saturation2/UpperLimit", offsetof(P_uao2pwm_T,
    Saturation2_UpperSat), 26, 1, 2, 14, 0 },

  { 8, "uao2pwm/Saturation2/LowerLimit", offsetof(P_uao2pwm_T,
    Saturation2_LowerSat), 26, 1, 2, 16, 0 },

  { 9, "uao2pwm/Saturation/UpperLimit", offsetof(P_uao2pwm_T,
    Saturation_UpperSat), 26, 1, 2, 18, 0 },

  { 10, "uao2pwm/Saturation/LowerLimit", offsetof(P_uao2pwm_T,
    Saturation_LowerSat), 26, 1, 2, 20, 0 },

  { 11, "uao2pwm/Saturation3/UpperLimit", offsetof(P_uao2pwm_T,
    Saturation3_UpperSat), 26, 1, 2, 22, 0 },

  { 12, "uao2pwm/Saturation3/LowerLimit", offsetof(P_uao2pwm_T,
    Saturation3_LowerSat), 26, 1, 2, 24, 0 },

  { 13, "uao2pwm/Constant1/Value", offsetof(P_uao2pwm_T, Constant1_Value), 26, 1,
    2, 26, 0 },

  { 14, "uao2pwm/Gain3/Gain", offsetof(P_uao2pwm_T, Gain3_Gain), 26, 1, 2, 28, 0
  },

  { 15, "uao2pwm/2-D Lookup Table3/Table", offsetof(P_uao2pwm_T,
    DLookupTable3_tableData), 27, 25, 2, 30, 0 },

  { 16, "uao2pwm/2-D Lookup Table3/BreakpointsForDimension1", offsetof
    (P_uao2pwm_T, DLookupTable3_bp01Data), 28, 5, 2, 32, 0 },

  { 17, "uao2pwm/2-D Lookup Table3/BreakpointsForDimension2", offsetof
    (P_uao2pwm_T, DLookupTable3_bp02Data), 28, 5, 2, 34, 0 },

  { 18, "uao2pwm/Gain2/Gain", offsetof(P_uao2pwm_T, Gain2_Gain), 26, 1, 2, 36, 0
  },

  { 19, "uao2pwm/2-D Lookup Table2/Table", offsetof(P_uao2pwm_T,
    DLookupTable2_tableData), 27, 25, 2, 38, 0 },

  { 20, "uao2pwm/2-D Lookup Table2/BreakpointsForDimension1", offsetof
    (P_uao2pwm_T, DLookupTable2_bp01Data), 28, 5, 2, 40, 0 },

  { 21, "uao2pwm/2-D Lookup Table2/BreakpointsForDimension2", offsetof
    (P_uao2pwm_T, DLookupTable2_bp02Data), 28, 5, 2, 42, 0 },

  { 22, "uao2pwm/Saturation4/UpperLimit", offsetof(P_uao2pwm_T,
    Saturation4_UpperSat), 26, 1, 2, 44, 0 },

  { 23, "uao2pwm/Saturation4/LowerLimit", offsetof(P_uao2pwm_T,
    Saturation4_LowerSat), 26, 1, 2, 46, 0 },

  { 24, "uao2pwm/Gain4/Gain", offsetof(P_uao2pwm_T, Gain4_Gain), 26, 1, 2, 48, 0
  },

  { 25, "uao2pwm/Constant/Value", offsetof(P_uao2pwm_T, Constant_Value), 26, 1,
    2, 50, 0 },

  { 26, "uao2pwm/Gain/Gain", offsetof(P_uao2pwm_T, Gain_Gain), 26, 1, 2, 52, 0 },

  { 27, "uao2pwm/2-D Lookup Table/Table", offsetof(P_uao2pwm_T,
    DLookupTable_tableData), 27, 25, 2, 54, 0 },

  { 28, "uao2pwm/2-D Lookup Table/BreakpointsForDimension1", offsetof
    (P_uao2pwm_T, DLookupTable_bp01Data), 28, 5, 2, 56, 0 },

  { 29, "uao2pwm/2-D Lookup Table/BreakpointsForDimension2", offsetof
    (P_uao2pwm_T, DLookupTable_bp02Data), 28, 5, 2, 58, 0 },

  { 30, "uao2pwm/Gain1/Gain", offsetof(P_uao2pwm_T, Gain1_Gain), 26, 1, 2, 60, 0
  },

  { 31, "uao2pwm/2-D Lookup Table1/Table", offsetof(P_uao2pwm_T,
    DLookupTable1_tableData), 27, 25, 2, 62, 0 },

  { 32, "uao2pwm/2-D Lookup Table1/BreakpointsForDimension1", offsetof
    (P_uao2pwm_T, DLookupTable1_bp01Data), 28, 5, 2, 64, 0 },

  { 33, "uao2pwm/2-D Lookup Table1/BreakpointsForDimension2", offsetof
    (P_uao2pwm_T, DLookupTable1_bp02Data), 28, 5, 2, 66, 0 },

  { 34, "uao2pwm/2-D Lookup Table3/maxIndex", offsetof(P_uao2pwm_T,
    DLookupTable3_maxIndex), 21, 2, 2, 68, 0 },

  { 35, "uao2pwm/2-D Lookup Table2/maxIndex", offsetof(P_uao2pwm_T,
    DLookupTable2_maxIndex), 21, 2, 2, 70, 0 },

  { 36, "uao2pwm/2-D Lookup Table/maxIndex", offsetof(P_uao2pwm_T,
    DLookupTable_maxIndex), 21, 2, 2, 72, 0 },

  { 37, "uao2pwm/2-D Lookup Table1/maxIndex", offsetof(P_uao2pwm_T,
    DLookupTable1_maxIndex), 21, 2, 2, 74, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 38;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 1,                                /* Parameter at index 0 */
  1, 1,                                /* Parameter at index 1 */
  1, 1,                                /* Parameter at index 2 */
  1, 1,                                /* Parameter at index 3 */
  1, 1,                                /* Parameter at index 4 */
  1, 1,                                /* Parameter at index 5 */
  1, 1,                                /* Parameter at index 6 */
  1, 1,                                /* Parameter at index 7 */
  1, 1,                                /* Parameter at index 8 */
  1, 1,                                /* Parameter at index 9 */
  1, 1,                                /* Parameter at index 10 */
  1, 1,                                /* Parameter at index 11 */
  1, 1,                                /* Parameter at index 12 */
  1, 1,                                /* Parameter at index 13 */
  1, 1,                                /* Parameter at index 14 */
  5, 5,                                /* Parameter at index 15 */
  1, 5,                                /* Parameter at index 16 */
  1, 5,                                /* Parameter at index 17 */
  1, 1,                                /* Parameter at index 18 */
  5, 5,                                /* Parameter at index 19 */
  1, 5,                                /* Parameter at index 20 */
  1, 5,                                /* Parameter at index 21 */
  1, 1,                                /* Parameter at index 22 */
  1, 1,                                /* Parameter at index 23 */
  1, 1,                                /* Parameter at index 24 */
  1, 1,                                /* Parameter at index 25 */
  1, 1,                                /* Parameter at index 26 */
  5, 5,                                /* Parameter at index 27 */
  1, 5,                                /* Parameter at index 28 */
  1, 5,                                /* Parameter at index 29 */
  1, 1,                                /* Parameter at index 30 */
  5, 5,                                /* Parameter at index 31 */
  1, 5,                                /* Parameter at index 32 */
  1, 5,                                /* Parameter at index 33 */
  2, 1,                                /* Parameter at index 34 */
  2, 1,                                /* Parameter at index 35 */
  2, 1,                                /* Parameter at index 36 */
  2, 1,                                /* Parameter at index 37 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "uao2pwm/alpha_VSP1", 0, "", offsetof(B_uao2pwm_T, alpha_VSP1)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "uao2pwm/omega_VSP1", 0, "", offsetof(B_uao2pwm_T, omega_VSP1)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "uao2pwm/Sum1", 0, "", offsetof(B_uao2pwm_T, Sum1)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "uao2pwm/u_VSP1", 0, "", offsetof(B_uao2pwm_T, u_VSP1)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "uao2pwm/omega_VSP2", 0, "", offsetof(B_uao2pwm_T, omega_VSP2)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "uao2pwm/Sum", 0, "", offsetof(B_uao2pwm_T, Sum)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "uao2pwm/alpha_VSP2", 0, "", offsetof(B_uao2pwm_T, alpha_VSP2)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "uao2pwm/u_BT", 0, "", offsetof(B_uao2pwm_T, u_BT)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "uao2pwm/Sum2", 0, "", offsetof(B_uao2pwm_T, Sum2)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "uao2pwm/u_VSP2", 0, "", offsetof(B_uao2pwm_T, u_VSP2)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "uao2pwm/2-D Lookup Table3", 0, "", offsetof(B_uao2pwm_T, DLookupTable3)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "uao2pwm/2-D Lookup Table2", 0, "", offsetof(B_uao2pwm_T, DLookupTable2)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "uao2pwm/2-D Lookup Table", 0, "", offsetof(B_uao2pwm_T, DLookupTable)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "uao2pwm/2-D Lookup Table1", 0, "", offsetof(B_uao2pwm_T, DLookupTable1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 14;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 14;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "alpha_VSP1", 0, EXT_IN, 1, 1, 1 },

  { 1, "omega_VSP1", 0, EXT_IN, 1, 1, 1 },

  { 2, "u_VSP1", 0, EXT_IN, 1, 1, 1 },

  { 3, "omega_VSP2", 0, EXT_IN, 1, 1, 1 },

  { 4, "alpha_VSP2", 0, EXT_IN, 1, 1, 1 },

  { 5, "u_BT", 0, EXT_IN, 1, 1, 1 },

  { 6, "u_VSP2", 0, EXT_IN, 1, 1, 1 },

  { 0, "pwm_VSP1", 0, EXT_OUT, 1, 1, 1 },

  { 1, "pwm_VSP2", 0, EXT_OUT, 1, 1, 1 },

  { 2, "pwm_BT", 0, EXT_OUT, 1, 1, 1 },

  { 3, "pwm_servo4", 0, EXT_OUT, 1, 1, 1 },

  { 4, "pwm_servo3", 0, EXT_OUT, 1, 1, 1 },

  { 5, "pwm_servo1", 0, EXT_OUT, 1, 1, 1 },

  { 6, "pwm_servo2", 0, EXT_OUT, 1, 1, 1 },

  { -1, "", 0, 0, 0, 0, 0 }
};

/* This Task List is generated to allow access to the task specs without
 * initializing the model.
 * 0th entry is for scheduler (base rate)
 * rest for multirate model's tasks.
 */
NI_Task NI_TaskList[] DataSection(".NIVS.tasklist") =
{
  { 0, 0.01, 0 }
};

int NI_NumTasks DataSection(".NIVS.numtasks") = 1;
static char* NI_CompiledModelName DataSection(".NIVS.compiledmodelname") =
  "uao2pwm";
static char* NI_CompiledModelVersion = "1.21";
static char* NI_CompiledModelDateTime = "Wed Feb 25 17:24:35 2015";
static char* NI_builder DataSection(".NIVS.builder") =
  "NI VeriStand 2014.0.0.82 (2014) RTW Build";
static char* NI_BuilderVersion DataSection(".NIVS.builderversion") =
  "2014.0.0.82";

/* Model Information Query fucntions for MATLAB
 */
/* dll information
 * Returns 1 for RTW DLL
 *		   2 for AutoCode DLL
 */
DLL_EXPORT long NIRT_GetBuildInfo(char* detail, long* len)
{
  // There are no console properties to set for VxWorks, because the console is simply serial output data.
  // Just do printf for VxWorks and ignore all console properties.
#if ! defined (VXWORKS) && ! defined (kNIOSLinux)

  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_BLUE |
    FOREGROUND_GREEN | FOREGROUND_RED);

#endif

  printf("\n*******************************************************************************\n");
  printf("%s\nModel Name: %s\nModel Version: %s\nCompiled On: %s",
         NI_builder, NI_CompiledModelName, NI_CompiledModelVersion,
         NI_CompiledModelDateTime);
  printf("\n*******************************************************************************\n");

#if ! defined (VXWORKS) && ! defined (kNIOSLinux)

  SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN |
    FOREGROUND_RED);

#endif

  if (*len>=(long)strlen(NI_builder))
    *len = strlen(NI_builder)+1;
  strncpy(detail,NI_builder,*len);
  return 1;
}

/*
 * Distinction between Index and ID:
 * Index is a long datatype (used to set parameter/probe signals).
 * ID on the other hand is a string (tag "2-3-2-12" for MatrixX/ Full path "f14/Gain/Gain" for Matlab).
 * If Bus support is added then signal path from the block name is added to the end of the port number (Model/subsystem1:1/X/A)
 * where X/A is the path from the block
 * NOTE: ID may not be the same as Paramname or signal name.
 */

/* signal information
   NOTE: signal ID == the blockname and port that feeds it extended with /sinalname.

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

      //ID[i] = 0;
      IDblk = ID;
      IDport = atoi(ID+i+1);

      // lookup the table for matching ID
      // Bus support
      for (i=0;i<NI_SigListSize;i++) {
        char *tempID = (char *)calloc(strlen(NI_SigList[i].blockname)+strlen
          (NI_SigList[i].signalname)+ 11, sizeof(char));

        //sprintf(tempID,"%s%s%s",NI_SigList[i].blockname,"/",NI_SigList[i].signalname);
        if (strlen(NI_SigList[i].signalname)>0)
          sprintf(tempID,"%s:%d%s%s",NI_SigList[i].blockname,NI_SigList[i].
                  portno+1,"/",NI_SigList[i].signalname);
        else
          sprintf(tempID,"%s:%d",NI_SigList[i].blockname,NI_SigList[i].portno+1);
        if (!strcmp(IDblk,tempID) && IDport==(NI_SigList[i].portno+1))
          break;
        free(tempID);
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
      // 11 to accomodate ':','/', port number and null character
      char *tempID = (char *)calloc(strlen(NI_SigList[sigidx].blockname)+strlen
        (NI_SigList[sigidx].signalname)+ 11, sizeof(char));
      if (strlen(NI_SigList[sigidx].signalname)>0)
        sprintf(tempID,"%s:%d%s%s",NI_SigList[sigidx].blockname,
                NI_SigList[sigidx].portno+1,"/",NI_SigList[sigidx].signalname);
      else
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
 * DEPRECATED.
 */
DLL_EXPORT long NIRT_GetParameterExpression(long paramidx, char* expression,
  long *exp_len)
{
  return 0;
}

/*
 * DEPRECATED.
 */
DLL_EXPORT long NIRT_GetVariableName(long varidx, char* variable_name, long
  *var_len)
{
  return 0;
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
                      S->ModelData.blockIO : S->ModelData.inputs) + (int)
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
  int i, j, idx;
  long count = 0;
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
        for (j = 0; j < 2; j++) {
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
   The undef allows us to access the real uao2pwm_P
   In the rest of the code uao2pwm_P is redefine to be the read-side
   of rtParameter.
 */
#undef uao2pwm_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &uao2pwm_P, sizeof(P_uao2pwm_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka uao2pwm_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_uao2pwm_T));
  return NI_OK;
}

static int NI_SetParamTxStatus = NI_OK;

// This function is called by the BGL to set parameters.  When a commit is requested (index < 0),
// the code enters a critical section shared with the TCL. This ensures that the flip occurs only
// when safe, and acts as a messaging scheme for us to copy back the parameters.
DLL_EXPORT long NIRT_SetParameter(long index, long subindex, double value)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (index < 0) {
    if (ReadSideDirtyFlag == 1) {
      memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
             (P_uao2pwm_T));
      ReadSideDirtyFlag = 0;
      if (WriteSideDirtyFlag == 0)
        return NI_OK;
      SetSITErrorMessage("Parameters have been set inline and from the background loop at the same time. Parameters written from the background loop since the last commit have been lost.",
                         1);
      WriteSideDirtyFlag = 0;
      return NI_ERROR;
    }

    if (NI_SetParamTxStatus==NI_ERROR) {
      // fail the transaction.
      // copy old	list of parameters to the failed TX buffer
      if (WriteSideDirtyFlag == 1)
        memcpy(&rtParameter[READSIDE], &rtParameter[1-READSIDE], sizeof
               (P_uao2pwm_T));

      // reset the status.
      NI_SetParamTxStatus = NI_OK;
      WriteSideDirtyFlag = 0;
      return NI_ERROR;
    }

    /*Do nothing if no new parameters were written after last commit*/
    if (WriteSideDirtyFlag == 0)
      return NI_OK;

    // commit changes
    S->ModelData.defaultParam = (double *)&rtParameter[1-READSIDE];
    WaitForSingleObject(SITexportglobals.flipCriticalSection, INFINITE);
    READSIDE = 1 - READSIDE;
    SITexportglobals.copyTaskBitfield = 0xFFFFFFFF;
    ReleaseSemaphore(SITexportglobals.flipCriticalSection, 1, NULL);

    // Copy back the newly set parameters to the writeside.
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof(P_uao2pwm_T));
    WriteSideDirtyFlag = 0;
    return NI_OK;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter subindex is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (ReadSideDirtyFlag == 1) {
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof(P_uao2pwm_T));
    ReadSideDirtyFlag = 0;
  }

  ptr = (char *)(&rtParameter[1-READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  WriteSideDirtyFlag = 1;
  return NIRT_SetValueByDataType(ptr,subindex,value,NI_ParamList[index].datatype,
    NI_ParamList[index].IsComplex);
}

DLL_EXPORT long NIRT_SetVectorParameter( unsigned long index, const double
  * paramvalues, unsigned long paramlength)
{
  unsigned int i = 0;
  long retval= NI_OK, temp_retval;
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  // verify that subindex is within bounds.
  if (paramlength!=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter length is incorrect.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (ReadSideDirtyFlag == 1) {
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof(P_uao2pwm_T));
    ReadSideDirtyFlag = 0;
  }

  ptr = (char *)(&rtParameter[1-READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  while (i<paramlength) {
    if (temp_retval = NIRT_SetValueByDataType(ptr, i, paramvalues[i],
         NI_ParamList[index].datatype, NI_ParamList[index].IsComplex))//assignment intended in if condition
      retval= temp_retval;
    i++;
  }

  WriteSideDirtyFlag = 1;
  return retval;
}

DLL_EXPORT long NIRT_SetScalarParameterInline( unsigned long index, unsigned
  long subindex, double paramvalue)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter subindex is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  ptr = (char *)(&rtParameter[READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  ReadSideDirtyFlag = 1;
  return NIRT_SetValueByDataType(ptr,subindex,paramvalue,NI_ParamList[index].
    datatype,NI_ParamList[index].IsComplex);
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

DLL_EXPORT long NIRT_GetVectorParameter(unsigned long index, double* paramvalues,
  unsigned long paramlength)
{
  char* ptr = NULL;
  unsigned int i = 0;
  if (index>=NI_ParamListSize || index < 0)
    return NI_ERROR;

  // verify that subindex is within bounds.
  if (paramlength!=NI_ParamList[index].width)
    return NI_ERROR;
  ptr = (char *)(&rtParameter[READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  while (i<paramlength) {
    paramvalues[i] = NIRT_GetValueByDataType(ptr, i, NI_ParamList[index].
      datatype, NI_ParamList[index].IsComplex);
    i++;
  }

  return NI_OK;
}

DLL_EXPORT long NIRT_GetSimState(long* numContStates, char* contStatesNames,
  double* contStates, long* numDiscStates, char* discStatesNames, double
  * discStates, long* numClockTicks, char* clockTicksNames, long* clockTicks)
{
  long count, idx;
  if (numContStates && numDiscStates && numClockTicks) {
    if (*numContStates < 0 || *numDiscStates < 0 || *numClockTicks < 0) {
      *numContStates = 0;
      *numDiscStates = 186;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.alpha_VSP1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.alpha_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.omega_VSP1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.omega_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_VSP1_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.u_VSP1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.u_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.omega_VSP2_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.omega_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_VSP2_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.alpha_VSP2_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.alpha_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.u_BT_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.u_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_BT_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.u_VSP2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.u_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_servo4_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_servo4_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_servo3_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_servo3_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_servo1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_servo1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_servo2_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_servo2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&uao2pwm_DW.NIVeriStandSignalProbe_DWORK2, 0, 6, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&uao2pwm_DW.NIVeriStandSignalProbe_DWORK2");
    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.alpha_VSP1_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.alpha_VSP1_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.omega_VSP1_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.omega_VSP1_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_VSP1_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_VSP1_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.u_VSP1_DWORK2, count,
        17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.u_VSP1_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.omega_VSP2_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.omega_VSP2_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_VSP2_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_VSP2_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.alpha_VSP2_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.alpha_VSP2_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.u_BT_DWORK2, count,
        17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.u_BT_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_BT_DWORK2, count,
        17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_BT_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.u_VSP2_DWORK2, count,
        17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.u_VSP2_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_servo4_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_servo4_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_servo3_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_servo3_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_servo1_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_servo1_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&uao2pwm_DW.pwm_servo2_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&uao2pwm_DW.pwm_servo2_DWORK2");
    }

    for (count = 0; count < 8; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&uao2pwm_DW.NIVeriStandSignalProbe_DWORK1, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&uao2pwm_DW.NIVeriStandSignalProbe_DWORK1");
    }

    for (count = 0; count < 51; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&uao2pwm_DW.NIVeriStandSignalProbe_DWORK3, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&uao2pwm_DW.NIVeriStandSignalProbe_DWORK3");
    }
  }

  if (clockTicks && clockTicksNames) {
    clockTicks[0] = S->Timing.clockTick0;
    strcpy(clockTicksNames, "clockTick0");
  }

  return NI_OK;
}

DLL_EXPORT long NIRT_SetSimState(double* contStates, double* discStates, long
  * clockTicks)
{
  long count, idx;
  if (discStates) {
    idx = 0;
    NIRT_SetValueByDataType(&uao2pwm_DW.alpha_VSP1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.omega_VSP1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.pwm_VSP1_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&uao2pwm_DW.u_VSP1_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&uao2pwm_DW.omega_VSP2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.pwm_VSP2_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&uao2pwm_DW.alpha_VSP2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.u_BT_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.pwm_BT_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&uao2pwm_DW.u_VSP2_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&uao2pwm_DW.pwm_servo4_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.pwm_servo3_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.pwm_servo1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.pwm_servo2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&uao2pwm_DW.NIVeriStandSignalProbe_DWORK2, 0,
      discStates[idx++], 6, 0);
    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.alpha_VSP1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.omega_VSP1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.pwm_VSP1_DWORK2, count, discStates[idx
        ++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.u_VSP1_DWORK2, count, discStates[idx++],
        17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.omega_VSP2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.pwm_VSP2_DWORK2, count, discStates[idx
        ++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.alpha_VSP2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.u_BT_DWORK2, count, discStates[idx++],
        17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.pwm_BT_DWORK2, count, discStates[idx++],
        17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.u_VSP2_DWORK2, count, discStates[idx++],
        17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.pwm_servo4_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.pwm_servo3_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.pwm_servo1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.pwm_servo2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 8; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.NIVeriStandSignalProbe_DWORK1, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 51; count++) {
      NIRT_SetValueByDataType(&uao2pwm_DW.NIVeriStandSignalProbe_DWORK3, count,
        discStates[idx++], 18, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_uao2pwm
