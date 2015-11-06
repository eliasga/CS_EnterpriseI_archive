/*
 * BP_MC1.c
 *
 * Real-Time Workshop code generation for Simulink model "BP_MC1.mdl".
 *
 * Model Version              : 1.49
 * Real-Time Workshop version : 7.4  (R2009b)  29-Jun-2009
 * C source code generated on : Wed Sep 19 12:19:00 2012
 *
 * Target selection: nidll.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "BP_MC1.h"
#include "BP_MC1_private.h"

/* Block signals (auto storage) */
BlockIO_BP_MC1 BP_MC1_B;

/* Block states (auto storage) */
D_Work_BP_MC1 BP_MC1_DWork;

/* Real-time model */
RT_MODEL_BP_MC1 BP_MC1_M_;
RT_MODEL_BP_MC1 *BP_MC1_M = &BP_MC1_M_;

/* Model output function */
static void BP_MC1_output(int_T tid)
{
  /* Gain: '<S3>/Scaling_JS_L_X' incorporates:
   *  Constant: '<S3>/JS_L_X'
   */
  BP_MC1_B.u1 = BP_MC1_P.Scaling_JS_L_X_Gain * BP_MC1_P.JS_L_X_Value;

  /* Signum: '<S4>/Sign' incorporates:
   *  Constant: '<S1>/LabVIEW_VSPS'
   */
  BP_MC1_B.Sign = rt_SIGNd_snf(BP_MC1_P.LabVIEW_VSPS_Value);

  /* Product: '<S4>/Product1' */
  BP_MC1_B.PortVPS_X = BP_MC1_B.u1 * BP_MC1_B.Sign;

  /* Gain: '<S4>/Neg1' */
  BP_MC1_B.PortVPS_X_g = BP_MC1_P.Neg1_Gain * BP_MC1_B.PortVPS_X;

  /* Gain: '<S3>/Scaling_JS_L_Y' incorporates:
   *  Constant: '<S3>/JS_L_Y'
   */
  BP_MC1_B.u1_p = BP_MC1_P.Scaling_JS_L_Y_Gain * BP_MC1_P.JS_L_Y_Value;

  /* Product: '<S4>/Product2' */
  BP_MC1_B.PortVSP_Y = BP_MC1_B.u1_p * BP_MC1_B.Sign;

  /* Gain: '<S4>/Neg2' */
  BP_MC1_B.PortVSP_Y_i = BP_MC1_P.Neg2_Gain * BP_MC1_B.PortVSP_Y;

  /* Gain: '<S3>/Scaling_JS_R_X' incorporates:
   *  Constant: '<S3>/JS_R_X'
   */
  BP_MC1_B.u1_g = BP_MC1_P.Scaling_JS_R_X_Gain * BP_MC1_P.JS_R_X_Value;

  /* Product: '<S4>/Product3' */
  BP_MC1_B.StarboardVSP_X = BP_MC1_B.u1_g * BP_MC1_B.Sign;

  /* Gain: '<S3>/Scaling_JS_R_Y' incorporates:
   *  Constant: '<S3>/JS_R_Y'
   */
  BP_MC1_B.u1_pj = BP_MC1_P.Scaling_JS_R_Y_Gain * BP_MC1_P.JS_R_Y_Value;

  /* Product: '<S4>/Product4' */
  BP_MC1_B.StarboardVSP_Y = BP_MC1_B.u1_pj * BP_MC1_B.Sign;

  /* Lookup2D: '<S4>/Servo1' */
  BP_MC1_B.Servo1 = rt_Lookup2D_Normal((const real_T *)(&BP_MC1_P.Servo1_RowIdx
    [0]), 3, (const real_T *)(&BP_MC1_P.Servo1_ColIdx[0]), 3, (const real_T *)
    (&BP_MC1_P.Servo1_Table[0]), (const real_T)BP_MC1_B.PortVPS_X_g, (const
    real_T)BP_MC1_B.PortVSP_Y_i);

  /* Lookup2D: '<S4>/Servo2' */
  BP_MC1_B.Servo2 = rt_Lookup2D_Normal((const real_T *)(&BP_MC1_P.Servo2_RowIdx
    [0]), 3, (const real_T *)(&BP_MC1_P.Servo2_ColIdx[0]), 3, (const real_T *)
    (&BP_MC1_P.Servo2_Table[0]), (const real_T)BP_MC1_B.PortVPS_X_g, (const
    real_T)BP_MC1_B.PortVSP_Y_i);

  /* Lookup2D: '<S4>/Servo3' */
  BP_MC1_B.Servo3 = rt_Lookup2D_Normal((const real_T *)(&BP_MC1_P.Servo3_RowIdx
    [0]), 3, (const real_T *)(&BP_MC1_P.Servo3_ColIdx[0]), 3, (const real_T *)
    (&BP_MC1_P.Servo3_Table[0]), (const real_T)BP_MC1_B.StarboardVSP_X, (const
    real_T)BP_MC1_B.StarboardVSP_Y);

  /* Lookup2D: '<S4>/Servo4' */
  BP_MC1_B.Servo4 = rt_Lookup2D_Normal((const real_T *)(&BP_MC1_P.Servo4_RowIdx
    [0]), 3, (const real_T *)(&BP_MC1_P.Servo4_ColIdx[0]), 3, (const real_T *)
    (&BP_MC1_P.Servo4_Table[0]), (const real_T)BP_MC1_B.StarboardVSP_X, (const
    real_T)BP_MC1_B.StarboardVSP_Y);

  /* Gain: '<S4>/VPS_Speed_Gain' incorporates:
   *  Constant: '<S1>/LabVIEW_VSPS'
   */
  BP_MC1_B.VPS_Speed_Gain = BP_MC1_P.VPS_Speed_Gain_Gain *
    BP_MC1_P.LabVIEW_VSPS_Value;

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/VPS_Power_Offset'
   */
  BP_MC1_B.Sum = BP_MC1_B.VPS_Speed_Gain + BP_MC1_P.VPS_Power_Offset_Value;

  /* Sum: '<S2>/Add' incorporates:
   *  Constant: '<S3>/L2'
   *  Constant: '<S3>/R2'
   */
  BP_MC1_B.BowThrusterdirection = BP_MC1_P.L2_Value + BP_MC1_P.R2_Value;

  /* Gain: '<S4>/BT_D_Gain1' */
  BP_MC1_B.BT_D_Gain1 = BP_MC1_P.BT_D_Gain1_Gain * BP_MC1_B.BowThrusterdirection;

  /* Gain: '<S4>/BT_D_Gain2' */
  BP_MC1_B.BT_D_Gain2 = BP_MC1_P.BT_D_Gain2_Gain * BP_MC1_B.BowThrusterdirection;

  /* Sum: '<S4>/Add' incorporates:
   *  Constant: '<S4>/BT_Power_Offset1'
   */
  BP_MC1_B.Add = (BP_MC1_B.BT_D_Gain1 + BP_MC1_P.BT_Power_Offset1_Value) +
    BP_MC1_B.BT_D_Gain2;

  /* Gain: '<S4>/BT_L_Gain1' incorporates:
   *  Constant: '<S1>/LabVIEW_BT_Limit'
   */
  BP_MC1_B.BT_L_Gain1 = BP_MC1_P.BT_L_Gain1_Gain *
    BP_MC1_P.LabVIEW_BT_Limit_Value;

  /* Gain: '<S4>/BT_L_Gain2' incorporates:
   *  Constant: '<S1>/LabVIEW_BT_Limit'
   */
  BP_MC1_B.BT_L_Gain2 = BP_MC1_P.BT_L_Gain2_Gain *
    BP_MC1_P.LabVIEW_BT_Limit_Value;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Constant: '<S4>/BT_Power_Offset2'
   */
  BP_MC1_B.Sum1 = BP_MC1_B.BT_L_Gain1 + BP_MC1_P.BT_Power_Offset2_Value;

  /* RelationalOperator: '<S5>/LowerRelop1' */
  BP_MC1_B.LowerRelop1 = (BP_MC1_B.Add > BP_MC1_B.Sum1);

  /* Sum: '<S4>/Sum2' incorporates:
   *  Constant: '<S4>/BT_Power_Offset3'
   */
  BP_MC1_B.Sum2 = BP_MC1_B.BT_L_Gain2 + BP_MC1_P.BT_Power_Offset3_Value;

  /* RelationalOperator: '<S5>/UpperRelop' */
  BP_MC1_B.UpperRelop = (BP_MC1_B.Add < BP_MC1_B.Sum2);

  /* Switch: '<S5>/Switch' */
  if (BP_MC1_B.UpperRelop) {
    BP_MC1_B.Switch = BP_MC1_B.Sum2;
  } else {
    BP_MC1_B.Switch = BP_MC1_B.Add;
  }

  /* Switch: '<S5>/Switch2' */
  if (BP_MC1_B.LowerRelop1) {
    BP_MC1_B.Switch2 = BP_MC1_B.Sum1;
  } else {
    BP_MC1_B.Switch2 = BP_MC1_B.Switch;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
static void BP_MC1_update(int_T tid)
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
  if (!(++BP_MC1_M->Timing.clockTick0))
    ++BP_MC1_M->Timing.clockTickH0;
  BP_MC1_M->Timing.t[0] = BP_MC1_M->Timing.clockTick0 *
    BP_MC1_M->Timing.stepSize0 + BP_MC1_M->Timing.clockTickH0 *
    BP_MC1_M->Timing.stepSize0 * 4294967296.0;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void BP_MC1_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)BP_MC1_M,0,
                sizeof(RT_MODEL_BP_MC1));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = BP_MC1_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    BP_MC1_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    BP_MC1_M->Timing.sampleTimes = (&BP_MC1_M->Timing.sampleTimesArray[0]);
    BP_MC1_M->Timing.offsetTimes = (&BP_MC1_M->Timing.offsetTimesArray[0]);

    /* task periods */
    BP_MC1_M->Timing.sampleTimes[0] = (0.05);

    /* task offsets */
    BP_MC1_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(BP_MC1_M, &BP_MC1_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = BP_MC1_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    BP_MC1_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(BP_MC1_M, -1);
  BP_MC1_M->Timing.stepSize0 = 0.05;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    BP_MC1_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(BP_MC1_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(BP_MC1_M->rtwLogInfo, (NULL));
    rtliSetLogT(BP_MC1_M->rtwLogInfo, "");
    rtliSetLogX(BP_MC1_M->rtwLogInfo, "");
    rtliSetLogXFinal(BP_MC1_M->rtwLogInfo, "");
    rtliSetSigLog(BP_MC1_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(BP_MC1_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(BP_MC1_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(BP_MC1_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(BP_MC1_M->rtwLogInfo, 1);
    rtliSetLogY(BP_MC1_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(BP_MC1_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(BP_MC1_M->rtwLogInfo, (NULL));
  }

  BP_MC1_M->solverInfoPtr = (&BP_MC1_M->solverInfo);
  BP_MC1_M->Timing.stepSize = (0.05);
  rtsiSetFixedStepSize(&BP_MC1_M->solverInfo, 0.05);
  rtsiSetSolverMode(&BP_MC1_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  BP_MC1_M->ModelData.blockIO = ((void *) &BP_MC1_B);
  (void) memset(((void *) &BP_MC1_B),0,
                sizeof(BlockIO_BP_MC1));

  {
    BP_MC1_B.u1 = 0.0;
    BP_MC1_B.Sign = 0.0;
    BP_MC1_B.PortVPS_X = 0.0;
    BP_MC1_B.PortVPS_X_g = 0.0;
    BP_MC1_B.u1_p = 0.0;
    BP_MC1_B.PortVSP_Y = 0.0;
    BP_MC1_B.PortVSP_Y_i = 0.0;
    BP_MC1_B.u1_g = 0.0;
    BP_MC1_B.StarboardVSP_X = 0.0;
    BP_MC1_B.u1_pj = 0.0;
    BP_MC1_B.StarboardVSP_Y = 0.0;
    BP_MC1_B.Servo1 = 0.0;
    BP_MC1_B.Servo2 = 0.0;
    BP_MC1_B.Servo3 = 0.0;
    BP_MC1_B.Servo4 = 0.0;
    BP_MC1_B.VPS_Speed_Gain = 0.0;
    BP_MC1_B.Sum = 0.0;
    BP_MC1_B.BowThrusterdirection = 0.0;
    BP_MC1_B.BT_D_Gain1 = 0.0;
    BP_MC1_B.BT_D_Gain2 = 0.0;
    BP_MC1_B.Add = 0.0;
    BP_MC1_B.BT_L_Gain1 = 0.0;
    BP_MC1_B.BT_L_Gain2 = 0.0;
    BP_MC1_B.Sum1 = 0.0;
    BP_MC1_B.Sum2 = 0.0;
    BP_MC1_B.Switch = 0.0;
    BP_MC1_B.Switch2 = 0.0;
  }

  /* parameters */
  BP_MC1_M->ModelData.defaultParam = ((real_T *) &BP_MC1_P);

  /* states (dwork) */
  BP_MC1_M->Work.dwork = ((void *) &BP_MC1_DWork);
  (void) memset((void *)&BP_MC1_DWork, 0,
                sizeof(D_Work_BP_MC1));
}

/* Model terminate function */
void BP_MC1_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  BP_MC1_output(tid);
}

void MdlUpdate(int_T tid)
{
  BP_MC1_update(tid);
}

void MdlInitializeSizes(void)
{
  BP_MC1_M->Sizes.numContStates = (0); /* Number of continuous states */
  BP_MC1_M->Sizes.numY = (0);          /* Number of model outputs */
  BP_MC1_M->Sizes.numU = (0);          /* Number of model inputs */
  BP_MC1_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  BP_MC1_M->Sizes.numSampTimes = (1);  /* Number of sample times */
  BP_MC1_M->Sizes.numBlocks = (51);    /* Number of blocks */
  BP_MC1_M->Sizes.numBlockIO = (29);   /* Number of block outputs */
  BP_MC1_M->Sizes.numBlockPrms = (126);/* Sum of parameter "widths" */
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

void MdlTerminate(void)
{
  BP_MC1_terminate();
}

RT_MODEL_BP_MC1 *BP_MC1(void)
{
  BP_MC1_initialize(1);
  return BP_MC1_M;
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
#ifdef NI_ROOTMODEL_BP_MC1
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

   case 17:
    //Type is renamed. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 18:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 19:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 20:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 21:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 22:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 23:
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

   case 17:
    //Type is renamed. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 18:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 21:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 22:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 23:
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

extern BP_MC1_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 0;
}

double ni_extout[7];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Thurster Allocation/SIT Out1 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Thurster Allocation/SIT Out2 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Thurster Allocation/SIT Out3 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Thurster Allocation/SIT Out4 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Thurster Allocation/SIT Out5 VSPS Port : Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Sum,0,0,0);
  } else {
    index += 1;
  }

  // Thurster Allocation/SIT Out6 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Sum,0,0,0);
  } else {
    index += 1;
  }

  // Thurster Allocation/SIT Out7 BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Switch2,0,0,0);
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

  // Thurster Allocation/SIT Out1 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Servo1,0,0,0);

  // Thurster Allocation/SIT Out2 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Servo2,0,0,0);

  // Thurster Allocation/SIT Out3 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Servo3,0,0,0);

  // Thurster Allocation/SIT Out4 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Servo4,0,0,0);

  // Thurster Allocation/SIT Out5 VSPS Port : Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Sum,0,0,0);

  // Thurster Allocation/SIT Out6 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Sum,0,0,0);

  // Thurster Allocation/SIT Out7 BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&BP_MC1_B.Switch2,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "bp_mc1/PS3 Controller Output/JS_L_X/Value", offsetof(Parameters_BP_MC1,
    JS_L_X_Value), 27, 1, 2, 0, "", 0 },

  { 1, "bp_mc1/PS3 Controller Output/Scaling_JS_L_X/Gain", offsetof
    (Parameters_BP_MC1, Scaling_JS_L_X_Gain), 27, 1, 2, 2, "", 0 },

  { 2, "bp_mc1/Labview Output/LabVIEW_VSPS/Value", offsetof(Parameters_BP_MC1,
    LabVIEW_VSPS_Value), 27, 1, 2, 4, "", 0 },

  { 3, "bp_mc1/Thurster Allocation/Neg1/Gain", offsetof(Parameters_BP_MC1,
    Neg1_Gain), 27, 1, 2, 6, "", 0 },

  { 4, "bp_mc1/PS3 Controller Output/JS_L_Y/Value", offsetof(Parameters_BP_MC1,
    JS_L_Y_Value), 27, 1, 2, 8, "", 0 },

  { 5, "bp_mc1/PS3 Controller Output/Scaling_JS_L_Y/Gain", offsetof
    (Parameters_BP_MC1, Scaling_JS_L_Y_Gain), 27, 1, 2, 10, "", 0 },

  { 6, "bp_mc1/Thurster Allocation/Neg2/Gain", offsetof(Parameters_BP_MC1,
    Neg2_Gain), 27, 1, 2, 12, "", 0 },

  { 7, "bp_mc1/PS3 Controller Output/JS_R_X/Value", offsetof(Parameters_BP_MC1,
    JS_R_X_Value), 27, 1, 2, 14, "", 0 },

  { 8, "bp_mc1/PS3 Controller Output/Scaling_JS_R_X/Gain", offsetof
    (Parameters_BP_MC1, Scaling_JS_R_X_Gain), 27, 1, 2, 16, "", 0 },

  { 9, "bp_mc1/PS3 Controller Output/JS_R_Y/Value", offsetof(Parameters_BP_MC1,
    JS_R_Y_Value), 27, 1, 2, 18, "", 0 },

  { 10, "bp_mc1/PS3 Controller Output/Scaling_JS_R_Y/Gain", offsetof
    (Parameters_BP_MC1, Scaling_JS_R_Y_Gain), 27, 1, 2, 20, "", 0 },

  { 11, "bp_mc1/Thurster Allocation/Servo1/RowIndex", offsetof(Parameters_BP_MC1,
    Servo1_RowIdx), 28, 3, 2, 22, "", 0 },

  { 12, "bp_mc1/Thurster Allocation/Servo1/ColumnIndex", offsetof
    (Parameters_BP_MC1, Servo1_ColIdx), 28, 3, 2, 24, "", 0 },

  { 13, "bp_mc1/Thurster Allocation/Servo1/Table", offsetof(Parameters_BP_MC1,
    Servo1_Table), 29, 9, 2, 26, "", 0 },

  { 14, "bp_mc1/Thurster Allocation/Servo2/RowIndex", offsetof(Parameters_BP_MC1,
    Servo2_RowIdx), 28, 3, 2, 28, "", 0 },

  { 15, "bp_mc1/Thurster Allocation/Servo2/ColumnIndex", offsetof
    (Parameters_BP_MC1, Servo2_ColIdx), 28, 3, 2, 30, "", 0 },

  { 16, "bp_mc1/Thurster Allocation/Servo2/Table", offsetof(Parameters_BP_MC1,
    Servo2_Table), 29, 9, 2, 32, "", 0 },

  { 17, "bp_mc1/Thurster Allocation/Servo3/RowIndex", offsetof(Parameters_BP_MC1,
    Servo3_RowIdx), 28, 3, 2, 34, "", 0 },

  { 18, "bp_mc1/Thurster Allocation/Servo3/ColumnIndex", offsetof
    (Parameters_BP_MC1, Servo3_ColIdx), 28, 3, 2, 36, "", 0 },

  { 19, "bp_mc1/Thurster Allocation/Servo3/Table", offsetof(Parameters_BP_MC1,
    Servo3_Table), 29, 9, 2, 38, "", 0 },

  { 20, "bp_mc1/Thurster Allocation/Servo4/RowIndex", offsetof(Parameters_BP_MC1,
    Servo4_RowIdx), 28, 3, 2, 40, "", 0 },

  { 21, "bp_mc1/Thurster Allocation/Servo4/ColumnIndex", offsetof
    (Parameters_BP_MC1, Servo4_ColIdx), 28, 3, 2, 42, "", 0 },

  { 22, "bp_mc1/Thurster Allocation/Servo4/Table", offsetof(Parameters_BP_MC1,
    Servo4_Table), 29, 9, 2, 44, "", 0 },

  { 23, "bp_mc1/Thurster Allocation/VPS_Speed_Gain/Gain", offsetof
    (Parameters_BP_MC1, VPS_Speed_Gain_Gain), 27, 1, 2, 46, "", 0 },

  { 24, "bp_mc1/Thurster Allocation/VPS_Power_Offset/Value", offsetof
    (Parameters_BP_MC1, VPS_Power_Offset_Value), 27, 1, 2, 48, "", 0 },

  { 25, "bp_mc1/PS3 Controller Output/L2/Value", offsetof(Parameters_BP_MC1,
    L2_Value), 27, 1, 2, 50, "", 0 },

  { 26, "bp_mc1/PS3 Controller Output/R2/Value", offsetof(Parameters_BP_MC1,
    R2_Value), 27, 1, 2, 52, "", 0 },

  { 27, "bp_mc1/Thurster Allocation/BT_D_Gain1/Gain", offsetof(Parameters_BP_MC1,
    BT_D_Gain1_Gain), 27, 1, 2, 54, "", 0 },

  { 28, "bp_mc1/Thurster Allocation/BT_Power_Offset1/Value", offsetof
    (Parameters_BP_MC1, BT_Power_Offset1_Value), 27, 1, 2, 56, "", 0 },

  { 29, "bp_mc1/Thurster Allocation/BT_D_Gain2/Gain", offsetof(Parameters_BP_MC1,
    BT_D_Gain2_Gain), 27, 1, 2, 58, "", 0 },

  { 30, "bp_mc1/Labview Output/LabVIEW_BT_Limit/Value", offsetof
    (Parameters_BP_MC1, LabVIEW_BT_Limit_Value), 27, 1, 2, 60, "", 0 },

  { 31, "bp_mc1/Thurster Allocation/BT_L_Gain1/Gain", offsetof(Parameters_BP_MC1,
    BT_L_Gain1_Gain), 27, 1, 2, 62, "", 0 },

  { 32, "bp_mc1/Thurster Allocation/BT_L_Gain2/Gain", offsetof(Parameters_BP_MC1,
    BT_L_Gain2_Gain), 27, 1, 2, 64, "", 0 },

  { 33, "bp_mc1/Thurster Allocation/BT_Power_Offset2/Value", offsetof
    (Parameters_BP_MC1, BT_Power_Offset2_Value), 27, 1, 2, 66, "", 0 },

  { 34, "bp_mc1/Thurster Allocation/BT_Power_Offset3/Value", offsetof
    (Parameters_BP_MC1, BT_Power_Offset3_Value), 27, 1, 2, 68, "", 0 },
};

static int NI_ParamListSize = 35;
static int NI_ParamDimList[] = {
  1, 1,                                /* bp_mc1/PS3 Controller Output/JS_L_X/Value */
  1, 1,                                /* bp_mc1/PS3 Controller Output/Scaling_JS_L_X/Gain */
  1, 1,                                /* bp_mc1/Labview Output/LabVIEW_VSPS/Value */
  1, 1,                                /* bp_mc1/Thurster Allocation/Neg1/Gain */
  1, 1,                                /* bp_mc1/PS3 Controller Output/JS_L_Y/Value */
  1, 1,                                /* bp_mc1/PS3 Controller Output/Scaling_JS_L_Y/Gain */
  1, 1,                                /* bp_mc1/Thurster Allocation/Neg2/Gain */
  1, 1,                                /* bp_mc1/PS3 Controller Output/JS_R_X/Value */
  1, 1,                                /* bp_mc1/PS3 Controller Output/Scaling_JS_R_X/Gain */
  1, 1,                                /* bp_mc1/PS3 Controller Output/JS_R_Y/Value */
  1, 1,                                /* bp_mc1/PS3 Controller Output/Scaling_JS_R_Y/Gain */
  1, 3,                                /* bp_mc1/Thurster Allocation/Servo1/RowIndex */
  1, 3,                                /* bp_mc1/Thurster Allocation/Servo1/ColumnIndex */
  3, 3,                                /* bp_mc1/Thurster Allocation/Servo1/Table */
  1, 3,                                /* bp_mc1/Thurster Allocation/Servo2/RowIndex */
  1, 3,                                /* bp_mc1/Thurster Allocation/Servo2/ColumnIndex */
  3, 3,                                /* bp_mc1/Thurster Allocation/Servo2/Table */
  1, 3,                                /* bp_mc1/Thurster Allocation/Servo3/RowIndex */
  1, 3,                                /* bp_mc1/Thurster Allocation/Servo3/ColumnIndex */
  3, 3,                                /* bp_mc1/Thurster Allocation/Servo3/Table */
  1, 3,                                /* bp_mc1/Thurster Allocation/Servo4/RowIndex */
  1, 3,                                /* bp_mc1/Thurster Allocation/Servo4/ColumnIndex */
  3, 3,                                /* bp_mc1/Thurster Allocation/Servo4/Table */
  1, 1,                                /* bp_mc1/Thurster Allocation/VPS_Speed_Gain/Gain */
  1, 1,                                /* bp_mc1/Thurster Allocation/VPS_Power_Offset/Value */
  1, 1,                                /* bp_mc1/PS3 Controller Output/L2/Value */
  1, 1,                                /* bp_mc1/PS3 Controller Output/R2/Value */
  1, 1,                                /* bp_mc1/Thurster Allocation/BT_D_Gain1/Gain */
  1, 1,                                /* bp_mc1/Thurster Allocation/BT_Power_Offset1/Value */
  1, 1,                                /* bp_mc1/Thurster Allocation/BT_D_Gain2/Gain */
  1, 1,                                /* bp_mc1/Labview Output/LabVIEW_BT_Limit/Value */
  1, 1,                                /* bp_mc1/Thurster Allocation/BT_L_Gain1/Gain */
  1, 1,                                /* bp_mc1/Thurster Allocation/BT_L_Gain2/Gain */
  1, 1,                                /* bp_mc1/Thurster Allocation/BT_Power_Offset2/Value */
  1, 1,                                /* bp_mc1/Thurster Allocation/BT_Power_Offset3/Value */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 29;
static NI_Signal NI_SigList[] = {
  { 0, "bp_mc1/PS3 Controller Output/Scaling_JS_L_X", 0, "[-1,1]", offsetof
    (BlockIO_BP_MC1, u1), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "bp_mc1/Thurster Allocation/Sign", 0, "", offsetof(BlockIO_BP_MC1, Sign),
    BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "bp_mc1/Thurster Allocation/Product1", 0, "Port VPS_X", offsetof
    (BlockIO_BP_MC1, PortVPS_X), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "bp_mc1/Thurster Allocation/Neg1", 0, "Port VPS_X", offsetof
    (BlockIO_BP_MC1, PortVPS_X_g), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "bp_mc1/PS3 Controller Output/Scaling_JS_L_Y", 0, "[-1,1]", offsetof
    (BlockIO_BP_MC1, u1_p), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "bp_mc1/Thurster Allocation/Product2", 0, "Port VSP_Y", offsetof
    (BlockIO_BP_MC1, PortVSP_Y), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "bp_mc1/Thurster Allocation/Neg2", 0, "Port VSP_Y", offsetof
    (BlockIO_BP_MC1, PortVSP_Y_i), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "bp_mc1/PS3 Controller Output/Scaling_JS_R_X", 0, "[-1,1]", offsetof
    (BlockIO_BP_MC1, u1_g), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "bp_mc1/Thurster Allocation/Product3", 0, "Starboard VSP_X", offsetof
    (BlockIO_BP_MC1, StarboardVSP_X), BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "bp_mc1/PS3 Controller Output/Scaling_JS_R_Y", 0, "[-1,1]", offsetof
    (BlockIO_BP_MC1, u1_pj), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "bp_mc1/Thurster Allocation/Product4", 0, "Starboard VSP_Y", offsetof
    (BlockIO_BP_MC1, StarboardVSP_Y), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "bp_mc1/Thurster Allocation/Servo1", 0, "", offsetof(BlockIO_BP_MC1,
    Servo1), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "bp_mc1/Thurster Allocation/Servo2", 0, "", offsetof(BlockIO_BP_MC1,
    Servo2), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "bp_mc1/Thurster Allocation/Servo3", 0, "", offsetof(BlockIO_BP_MC1,
    Servo3), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "bp_mc1/Thurster Allocation/Servo4", 0, "", offsetof(BlockIO_BP_MC1,
    Servo4), BLOCKIO_SIG, 0, 1, 2, 28, 0 },

  { 15, "bp_mc1/Thurster Allocation/VPS_Speed_Gain", 0, "", offsetof
    (BlockIO_BP_MC1, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "bp_mc1/Thurster Allocation/Sum", 0, "", offsetof(BlockIO_BP_MC1, Sum),
    BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "bp_mc1/Manual Thrust controll/Add", 0, "Bow Thruster direction",
    offsetof(BlockIO_BP_MC1, BowThrusterdirection), BLOCKIO_SIG, 0, 1, 2, 34, 0
  },

  { 18, "bp_mc1/Thurster Allocation/BT_D_Gain1", 0, "", offsetof(BlockIO_BP_MC1,
    BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "bp_mc1/Thurster Allocation/BT_D_Gain2", 0, "", offsetof(BlockIO_BP_MC1,
    BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "bp_mc1/Thurster Allocation/Add", 0, "", offsetof(BlockIO_BP_MC1, Add),
    BLOCKIO_SIG, 0, 1, 2, 40, 0 },

  { 21, "bp_mc1/Thurster Allocation/BT_L_Gain1", 0, "", offsetof(BlockIO_BP_MC1,
    BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2, 42, 0 },

  { 22, "bp_mc1/Thurster Allocation/BT_L_Gain2", 0, "", offsetof(BlockIO_BP_MC1,
    BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { 23, "bp_mc1/Thurster Allocation/Sum1", 0, "", offsetof(BlockIO_BP_MC1, Sum1),
    BLOCKIO_SIG, 0, 1, 2, 46, 0 },

  { 24, "bp_mc1/Thurster Allocation/Sum2", 0, "", offsetof(BlockIO_BP_MC1, Sum2),
    BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25, "bp_mc1/Thurster Allocation/Saturation Dynamic/Switch", 0, "", offsetof
    (BlockIO_BP_MC1, Switch), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26, "bp_mc1/Thurster Allocation/Saturation Dynamic/Switch2", 0, "", offsetof
    (BlockIO_BP_MC1, Switch2), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27, "bp_mc1/Thurster Allocation/Saturation Dynamic/LowerRelop1", 0, "",
    offsetof(BlockIO_BP_MC1, LowerRelop1), BLOCKIO_SIG, 8, 1, 2, 54, 0 },

  { 28, "bp_mc1/Thurster Allocation/Saturation Dynamic/UpperRelop", 0, "",
    offsetof(BlockIO_BP_MC1, UpperRelop), BLOCKIO_SIG, 8, 1, 2, 56, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize = 7;
static NI_ExternalIO NI_ExtList[] = {
  { 0, "Thurster Allocation/SIT Out1 Servo1", 0, EXT_OUT, 1, 1, 1 },

  { 1, "Thurster Allocation/SIT Out2 Servo2", 0, EXT_OUT, 1, 1, 1 },

  { 2, "Thurster Allocation/SIT Out3 Servo3", 0, EXT_OUT, 1, 1, 1 },

  { 3, "Thurster Allocation/SIT Out4 Servo4", 0, EXT_OUT, 1, 1, 1 },

  { 4, "Thurster Allocation/SIT Out5 VSPS Port ", 0, EXT_OUT, 1, 1, 1 },

  { 5, "Thurster Allocation/SIT Out6 VSPS Starboard", 0, EXT_OUT, 1, 1, 1 },

  { 6, "Thurster Allocation/SIT Out7 BT", 0, EXT_OUT, 1, 1, 1 },

  { -1, "", 0, 0, 0, 0, 0 }
};

/* This Task List is generated to allow access to the task specs without
 * initializing the model.
 * 0th entry is for scheduler (base rate)
 * rest for multirate model's tasks.
 */
NI_Task NI_TaskList[] = {
  { 0, 0.05, 0 }
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

static char* NI_CompiledModelName = "bp_mc1";
static char* NI_CompiledModelVersion = "1.49";
static char* NI_CompiledModelDateTime = "Wed Sep 19 12:18:59 2012";

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
   The undef allows us to access the real BP_MC1_P
   In the rest of the code BP_MC1_P is redefine to be the read-side
   of rtParameter.
 */
#undef BP_MC1_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &BP_MC1_P, sizeof(Parameters_BP_MC1));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka BP_MC1_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_BP_MC1));
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
             (Parameters_BP_MC1));

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
           (Parameters_BP_MC1));
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

#endif                                 // of NI_ROOTMODEL_BP_MC1
