/*
 * Ctrl_Dahl_DP_1.c
 *
 * Code generation for model "Ctrl_Dahl_DP_1".
 *
 * Model version              : 1.27
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 04 17:19:35 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Ctrl_Dahl_DP_1.h"
#include "Ctrl_Dahl_DP_1_private.h"

/* Block signals (auto storage) */
B_Ctrl_Dahl_DP_1_T Ctrl_Dahl_DP_1_B;

/* Block states (auto storage) */
DW_Ctrl_Dahl_DP_1_T Ctrl_Dahl_DP_1_DW;

/* Real-time model */
RT_MODEL_Ctrl_Dahl_DP_1_T Ctrl_Dahl_DP_1_M_;
RT_MODEL_Ctrl_Dahl_DP_1_T *const Ctrl_Dahl_DP_1_M = &Ctrl_Dahl_DP_1_M_;
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model output function */
static void Ctrl_Dahl_DP_1_output(void)
{
  real_T tau_trans;
  real_T rtb_X;
  real_T rtb_Y;
  real_T rtb_Psi;
  real_T rtb_TmpSignalConversionAtSFun_0;

  /* Gain: '<Root>/Gain' */
  Ctrl_Dahl_DP_1_B.Gain = Ctrl_Dahl_DP_1_P.Gain_Gain * Ctrl_Dahl_DP_1_B.Ctrl_PSI;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAt SFunction Inport1'
   *  SignalConversion: '<S1>/TmpSignal ConversionAt SFunction Inport2'
   */
  /* MATLAB Function 'MATLAB Function': '<S1>:1' */
  /* '<S1>:1:4' */
  /* '<S1>:1:5' */
  /* '<S1>:1:6' */
  /* '<S1>:1:7' */
  /* '<S1>:1:8' */
  /* '<S1>:1:9' */
  /* '<S1>:1:11' */
  /* '<S1>:1:12' */
  Ctrl_Dahl_DP_1_B.error_psi = Ctrl_Dahl_DP_1_B.Gain -
    Ctrl_Dahl_DP_1_B.Ctrl_PSI_d;

  /* '<S1>:1:14' */
  /* '<S1>:1:19' */
  rtb_Y = Ctrl_Dahl_DP_1_B.Ctrl_X - Ctrl_Dahl_DP_1_B.Ctrl_X_d;
  rtb_TmpSignalConversionAtSFun_0 = Ctrl_Dahl_DP_1_B.Ctrl_Y -
    Ctrl_Dahl_DP_1_B.Ctrl_Y_d;
  Ctrl_Dahl_DP_1_B.epsilon[0] = 0.0;
  Ctrl_Dahl_DP_1_B.epsilon[0] += cos(Ctrl_Dahl_DP_1_B.Gain) * rtb_Y;
  Ctrl_Dahl_DP_1_B.epsilon[0] += sin(Ctrl_Dahl_DP_1_B.Gain) *
    rtb_TmpSignalConversionAtSFun_0;
  Ctrl_Dahl_DP_1_B.epsilon[1] = 0.0;
  Ctrl_Dahl_DP_1_B.epsilon[1] += -sin(Ctrl_Dahl_DP_1_B.Gain) * rtb_Y;
  Ctrl_Dahl_DP_1_B.epsilon[1] += cos(Ctrl_Dahl_DP_1_B.Gain) *
    rtb_TmpSignalConversionAtSFun_0;

  /* Product: '<Root>/X' */
  rtb_X = Ctrl_Dahl_DP_1_B.epsilon[0] * Ctrl_Dahl_DP_1_B.P_x;

  /* Product: '<Root>/Y' */
  rtb_Y = Ctrl_Dahl_DP_1_B.epsilon[1] * Ctrl_Dahl_DP_1_B.P_y;

  /* Product: '<Root>/Psi' */
  rtb_Psi = Ctrl_Dahl_DP_1_B.error_psi * Ctrl_Dahl_DP_1_B.P_psi;

  /* MATLAB Function: '<S2>/Thrust allocation' incorporates:
   *  Constant: '<S2>/Constant'
   */
  /* MATLAB Function 'Thruster allocation/Thrust allocation': '<S4>:1' */
  /* '<S4>:1:3' */
  tau_trans = fabs(rtb_X) + fabs(rtb_Y);

  /* '<S4>:1:6' */
  rtb_X = rt_atan2d_snf(rtb_Y, rtb_X);

  /* '<S4>:1:7' */
  /* '<S4>:1:9' */
  /* '<S4>:1:10' */
  /* '<S4>:1:11' */
  /* '<S4>:1:13' */
  Ctrl_Dahl_DP_1_B.u_VSP = fabs(rtb_Psi) / Ctrl_Dahl_DP_1_P.Constant_Value_l +
    tau_trans;

  /* '<S4>:1:14' */
  if (-rtb_Psi < 0.0) {
    rtb_TmpSignalConversionAtSFun_0 = -1.0;
  } else if (-rtb_Psi > 0.0) {
    rtb_TmpSignalConversionAtSFun_0 = 1.0;
  } else if (-rtb_Psi == 0.0) {
    rtb_TmpSignalConversionAtSFun_0 = 0.0;
  } else {
    rtb_TmpSignalConversionAtSFun_0 = -rtb_Psi;
  }

  Ctrl_Dahl_DP_1_B.alpha_VSP = rtb_TmpSignalConversionAtSFun_0 *
    3.1415926535897931 / 2.0 + rtb_X;

  /* '<S4>:1:15' */
  Ctrl_Dahl_DP_1_B.u_BT = tau_trans * sin(rtb_X) *
    Ctrl_Dahl_DP_1_P.Constant_Value_l / Ctrl_Dahl_DP_1_P.Constant_Value_l +
    rtb_Psi / Ctrl_Dahl_DP_1_P.Constant_Value_l;

  /* End of MATLAB Function: '<S2>/Thrust allocation' */

  /* Switch: '<S3>/Switch' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   */
  if (Ctrl_Dahl_DP_1_B.Bool_VSP_omega_on_off != 0.0) {
    Ctrl_Dahl_DP_1_B.Switch = Ctrl_Dahl_DP_1_P.Constant1_Value;
  } else {
    Ctrl_Dahl_DP_1_B.Switch = Ctrl_Dahl_DP_1_P.Constant_Value;
  }

  /* End of Switch: '<S3>/Switch' */
}

/* Model update function */
static void Ctrl_Dahl_DP_1_update(void)
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
  if (!(++Ctrl_Dahl_DP_1_M->Timing.clockTick0)) {
    ++Ctrl_Dahl_DP_1_M->Timing.clockTickH0;
  }

  Ctrl_Dahl_DP_1_M->Timing.t[0] = Ctrl_Dahl_DP_1_M->Timing.clockTick0 *
    Ctrl_Dahl_DP_1_M->Timing.stepSize0 + Ctrl_Dahl_DP_1_M->Timing.clockTickH0 *
    Ctrl_Dahl_DP_1_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Ctrl_Dahl_DP_1_initialize(void)
{
}

/* Model terminate function */
void Ctrl_Dahl_DP_1_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Ctrl_Dahl_DP_1_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Ctrl_Dahl_DP_1_update();
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
  Ctrl_Dahl_DP_1_initialize();
}

void MdlTerminate(void)
{
  Ctrl_Dahl_DP_1_terminate();
}

/* Registration function */
RT_MODEL_Ctrl_Dahl_DP_1_T *Ctrl_Dahl_DP_1(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Ctrl_Dahl_DP_1_M, 0,
                sizeof(RT_MODEL_Ctrl_Dahl_DP_1_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Ctrl_Dahl_DP_1_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Ctrl_Dahl_DP_1_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Ctrl_Dahl_DP_1_M->Timing.sampleTimes =
      (&Ctrl_Dahl_DP_1_M->Timing.sampleTimesArray[0]);
    Ctrl_Dahl_DP_1_M->Timing.offsetTimes =
      (&Ctrl_Dahl_DP_1_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Ctrl_Dahl_DP_1_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    Ctrl_Dahl_DP_1_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Ctrl_Dahl_DP_1_M, &Ctrl_Dahl_DP_1_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Ctrl_Dahl_DP_1_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Ctrl_Dahl_DP_1_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Ctrl_Dahl_DP_1_M, -1);
  Ctrl_Dahl_DP_1_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    Ctrl_Dahl_DP_1_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Ctrl_Dahl_DP_1_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Ctrl_Dahl_DP_1_M->rtwLogInfo, (NULL));
    rtliSetLogT(Ctrl_Dahl_DP_1_M->rtwLogInfo, "tout");
    rtliSetLogX(Ctrl_Dahl_DP_1_M->rtwLogInfo, "");
    rtliSetLogXFinal(Ctrl_Dahl_DP_1_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Ctrl_Dahl_DP_1_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Ctrl_Dahl_DP_1_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Ctrl_Dahl_DP_1_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(Ctrl_Dahl_DP_1_M->rtwLogInfo, 1);
    rtliSetLogY(Ctrl_Dahl_DP_1_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Ctrl_Dahl_DP_1_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Ctrl_Dahl_DP_1_M->rtwLogInfo, (NULL));
  }

  Ctrl_Dahl_DP_1_M->solverInfoPtr = (&Ctrl_Dahl_DP_1_M->solverInfo);
  Ctrl_Dahl_DP_1_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&Ctrl_Dahl_DP_1_M->solverInfo, 0.01);
  rtsiSetSolverMode(&Ctrl_Dahl_DP_1_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Ctrl_Dahl_DP_1_M->ModelData.blockIO = ((void *) &Ctrl_Dahl_DP_1_B);
  (void) memset(((void *) &Ctrl_Dahl_DP_1_B), 0,
                sizeof(B_Ctrl_Dahl_DP_1_T));

  /* parameters */
  Ctrl_Dahl_DP_1_M->ModelData.defaultParam = ((real_T *)&Ctrl_Dahl_DP_1_P);

  /* states (dwork) */
  Ctrl_Dahl_DP_1_M->ModelData.dwork = ((void *) &Ctrl_Dahl_DP_1_DW);
  (void) memset((void *)&Ctrl_Dahl_DP_1_DW, 0,
                sizeof(DW_Ctrl_Dahl_DP_1_T));

  /* Initialize Sizes */
  Ctrl_Dahl_DP_1_M->Sizes.numContStates = (0);/* Number of continuous states */
  Ctrl_Dahl_DP_1_M->Sizes.numY = (0);  /* Number of model outputs */
  Ctrl_Dahl_DP_1_M->Sizes.numU = (0);  /* Number of model inputs */
  Ctrl_Dahl_DP_1_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Ctrl_Dahl_DP_1_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Ctrl_Dahl_DP_1_M->Sizes.numBlocks = (38);/* Number of blocks */
  Ctrl_Dahl_DP_1_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  Ctrl_Dahl_DP_1_M->Sizes.numBlockPrms = (131);/* Sum of parameter "widths" */
  return Ctrl_Dahl_DP_1_M;
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
#ifdef NI_ROOTMODEL_Ctrl_Dahl_DP_1
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 19:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 20:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 21:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 25:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 26:
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

   case 25:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 26:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern Ctrl_Dahl_DP_1_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Ctrl_X
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.Ctrl_X, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_X_d
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.Ctrl_X_d, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_Y_d
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.Ctrl_Y_d, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_PSI_d
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.Ctrl_PSI_d, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_Y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.Ctrl_Y, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_PSI
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.Ctrl_PSI, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // P_x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.P_x, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // P_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.P_y, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // P_psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.P_psi, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Thruster allocation/Set_omega_VSP/Bool_VSP_omega_on_off
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_B.Bool_VSP_omega_on_off, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 10;
}

double ni_extout[11];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Ctrl_U_1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.u_VSP,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_U_2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.u_VSP,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_alpha_1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.alpha_VSP,0,0,
      0);
  } else {
    index += 1;
  }

  // Ctrl_alpha_2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.alpha_VSP,0,0,
      0);
  } else {
    index += 1;
  }

  // Ctrl_U_BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.u_BT,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_omega_vsp1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.Switch,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_omega_vsp2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.Switch,0,0,0);
  } else {
    index += 1;
  }

  // epsilon_s: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.epsilon,0,19,
      0);
  } else {
    index += 1;
  }

  // epsilon_e: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.epsilon,1,19,
      0);
  } else {
    index += 1;
  }

  // epsilon_psi: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.error_psi,0,0,
      0);
  } else {
    index += 1;
  }

  // NIVeriStand Out1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.Gain,0,0,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 11;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // Ctrl_U_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.u_VSP,0,0,0);

  // Ctrl_U_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.u_VSP,0,0,0);

  // Ctrl_alpha_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.alpha_VSP,0,0,0);

  // Ctrl_alpha_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.alpha_VSP,0,0,0);

  // Ctrl_U_BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.u_BT,0,0,0);

  // Ctrl_omega_vsp1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.Switch,0,0,0);

  // Ctrl_omega_vsp2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.Switch,0,0,0);

  // epsilon_s: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.epsilon,0,19,0);

  // epsilon_e: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.epsilon,1,19,0);

  // epsilon_psi: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.error_psi,0,0,0);

  // NIVeriStand Out1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_B.Gain,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "ctrl_dahl_dp_1/Thruster allocation/Set_omega_VSP/Constant/Value",
    offsetof(P_Ctrl_Dahl_DP_1_T, Constant_Value), 25, 1, 2, 0, 0 },

  { 1, "ctrl_dahl_dp_1/Thruster allocation/Set_omega_VSP/Constant1/Value",
    offsetof(P_Ctrl_Dahl_DP_1_T, Constant1_Value), 25, 1, 2, 2, 0 },

  { 2, "ctrl_dahl_dp_1/Thruster allocation/Constant/Value", offsetof
    (P_Ctrl_Dahl_DP_1_T, Constant_Value_l), 25, 1, 2, 4, 0 },

  { 3, "ctrl_dahl_dp_1/Gain/Gain", offsetof(P_Ctrl_Dahl_DP_1_T, Gain_Gain), 25,
    1, 2, 6, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 4;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 1,                                /* Parameter at index 0 */
  1, 1,                                /* Parameter at index 1 */
  1, 1,                                /* Parameter at index 2 */
  1, 1,                                /* Parameter at index 3 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "ctrl_dahl_dp_1/Ctrl_X", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, Ctrl_X)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "ctrl_dahl_dp_1/Ctrl_X_d", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, Ctrl_X_d)+
    0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "ctrl_dahl_dp_1/Ctrl_Y_d", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, Ctrl_Y_d)+
    0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "ctrl_dahl_dp_1/Ctrl_PSI_d", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T,
    Ctrl_PSI_d)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "ctrl_dahl_dp_1/Ctrl_Y", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, Ctrl_Y)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "ctrl_dahl_dp_1/Ctrl_PSI", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, Ctrl_PSI)+
    0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "ctrl_dahl_dp_1/Gain", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, Gain)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "ctrl_dahl_dp_1/P_x", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, P_x)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "ctrl_dahl_dp_1/P_y", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, P_y)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "ctrl_dahl_dp_1/P_psi", 0, "", offsetof(B_Ctrl_Dahl_DP_1_T, P_psi)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "ctrl_dahl_dp_1/Thruster allocation/Set_omega_VSP/Bool_VSP_omega_on_off",
    0, "", offsetof(B_Ctrl_Dahl_DP_1_T, Bool_VSP_omega_on_off)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "ctrl_dahl_dp_1/Thruster allocation/Set_omega_VSP/Switch", 0, "",
    offsetof(B_Ctrl_Dahl_DP_1_T, Switch)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    22, 0 },

  { 12, "ctrl_dahl_dp_1/Thruster allocation/Thrust allocation", 0, "u_BT",
    offsetof(B_Ctrl_Dahl_DP_1_T, u_BT)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    24, 0 },

  { 13, "ctrl_dahl_dp_1/Thruster allocation/Thrust allocation", 1, "u_VSP",
    offsetof(B_Ctrl_Dahl_DP_1_T, u_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    26, 0 },

  { 14, "ctrl_dahl_dp_1/Thruster allocation/Thrust allocation", 2, "alpha_VSP",
    offsetof(B_Ctrl_Dahl_DP_1_T, alpha_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 28, 0 },

  { 15, "ctrl_dahl_dp_1/MATLAB Function", 0, "epsilon(1,1)", offsetof
    (B_Ctrl_Dahl_DP_1_T, epsilon)+0*sizeof(real_T), BLOCKIO_SIG, 19, 1, 2, 30, 0
  },

  { 16, "ctrl_dahl_dp_1/MATLAB Function", 0, "epsilon(1,2)", offsetof
    (B_Ctrl_Dahl_DP_1_T, epsilon)+1*sizeof(real_T), BLOCKIO_SIG, 19, 1, 2, 32, 0
  },

  { 17, "ctrl_dahl_dp_1/MATLAB Function", 1, "error_psi", offsetof
    (B_Ctrl_Dahl_DP_1_T, error_psi)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 34,
    0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 18;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 21;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "Ctrl_X", 0, EXT_IN, 1, 1, 1 },

  { 1, "Ctrl_X_d", 0, EXT_IN, 1, 1, 1 },

  { 2, "Ctrl_Y_d", 0, EXT_IN, 1, 1, 1 },

  { 3, "Ctrl_PSI_d", 0, EXT_IN, 1, 1, 1 },

  { 4, "Ctrl_Y", 0, EXT_IN, 1, 1, 1 },

  { 5, "Ctrl_PSI", 0, EXT_IN, 1, 1, 1 },

  { 6, "P_x", 0, EXT_IN, 1, 1, 1 },

  { 7, "P_y", 0, EXT_IN, 1, 1, 1 },

  { 8, "P_psi", 0, EXT_IN, 1, 1, 1 },

  { 9, "Thruster allocation/Set_omega_VSP/Bool_VSP_omega_on_off", 0, EXT_IN, 1,
    1, 1 },

  { 0, "Ctrl_U_1", 0, EXT_OUT, 1, 1, 1 },

  { 1, "Ctrl_U_2", 0, EXT_OUT, 1, 1, 1 },

  { 2, "Ctrl_alpha_1", 0, EXT_OUT, 1, 1, 1 },

  { 3, "Ctrl_alpha_2", 0, EXT_OUT, 1, 1, 1 },

  { 4, "Ctrl_U_BT", 0, EXT_OUT, 1, 1, 1 },

  { 5, "Ctrl_omega_vsp1", 0, EXT_OUT, 1, 1, 1 },

  { 6, "Ctrl_omega_vsp2", 0, EXT_OUT, 1, 1, 1 },

  { 7, "epsilon_s", 0, EXT_OUT, 1, 1, 1 },

  { 8, "epsilon_e", 0, EXT_OUT, 1, 1, 1 },

  { 9, "epsilon_psi", 0, EXT_OUT, 1, 1, 1 },

  { 10, "NIVeriStand Out1", 0, EXT_OUT, 1, 1, 1 },

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
  "ctrl_dahl_dp_1";
static char* NI_CompiledModelVersion = "1.27";
static char* NI_CompiledModelDateTime = "Wed Feb 04 17:19:35 2015";
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
   The undef allows us to access the real Ctrl_Dahl_DP_1_P
   In the rest of the code Ctrl_Dahl_DP_1_P is redefine to be the read-side
   of rtParameter.
 */
#undef Ctrl_Dahl_DP_1_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &Ctrl_Dahl_DP_1_P, sizeof(P_Ctrl_Dahl_DP_1_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka Ctrl_Dahl_DP_1_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_Ctrl_Dahl_DP_1_T));
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
             (P_Ctrl_Dahl_DP_1_T));
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
               (P_Ctrl_Dahl_DP_1_T));

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
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_Ctrl_Dahl_DP_1_T));
    WriteSideDirtyFlag = 0;
    return NI_OK;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter subindex is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (ReadSideDirtyFlag == 1) {
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_Ctrl_Dahl_DP_1_T));
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
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_Ctrl_Dahl_DP_1_T));
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
      *numDiscStates = 410;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_X_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_X_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_X_d_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_X_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_Y_d_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_Y_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_d_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_Y_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_Y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_x_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.P_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_y_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.P_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_psi_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.P_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_U_1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_U_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_U_2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_U_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.Ctrl_U_BT_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.Ctrl_U_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.Bool_VSP_omega_on_off_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.Bool_VSP_omega_on_off_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.epsilon_s_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.epsilon_s_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.epsilon_e_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.epsilon_e_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.epsilon_psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.epsilon_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.NIVeriStandOut1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.NIVeriStandOut1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK2, 0, 6, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK2");
    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_X_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_X_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_X_d_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_X_d_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_Y_d_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_Y_d_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_d_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_d_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_Y_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.Ctrl_Y_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_x_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.P_x_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_y_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.P_y_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_psi_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Ctrl_Dahl_DP_1_DW.P_psi_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_U_1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_U_1_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_U_2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_U_2_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_1_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_2_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_U_BT_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_U_BT_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Bool_VSP_omega_on_off_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Bool_VSP_omega_on_off_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp1_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp2_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.epsilon_s_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.epsilon_s_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.epsilon_e_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.epsilon_e_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.epsilon_psi_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.epsilon_psi_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.NIVeriStandOut1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.NIVeriStandOut1_DWORK2");
    }

    for (count = 0; count < 15; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK1, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK1");
    }

    for (count = 0; count < 58; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK3, count, 21, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK3");
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
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_X_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_X_d_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_Y_d_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_d_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_Y_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_x_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_y_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_psi_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_U_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_U_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_U_BT_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Bool_VSP_omega_on_off_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.epsilon_s_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.epsilon_e_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.epsilon_psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.NIVeriStandOut1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK2, 0,
      discStates[idx++], 6, 0);
    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_X_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_X_d_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_Y_d_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_d_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_Y_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_PSI_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_x_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_y_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.P_psi_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_U_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_U_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_alpha_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_U_BT_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Bool_VSP_omega_on_off_DWORK2,
        count, discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.Ctrl_omega_vsp2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.epsilon_s_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.epsilon_e_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.epsilon_psi_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.NIVeriStandOut1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 15; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK1,
        count, discStates[idx++], 17, 0);
    }

    for (count = 0; count < 58; count++) {
      NIRT_SetValueByDataType(&Ctrl_Dahl_DP_1_DW.NIVeriStandSignalProbe_DWORK3,
        count, discStates[idx++], 21, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_Ctrl_Dahl_DP_1
