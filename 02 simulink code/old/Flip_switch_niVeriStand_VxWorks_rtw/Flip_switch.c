/*
 * Flip_switch.c
 *
 * Code generation for model "Flip_switch".
 *
 * Model version              : 1.15
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Mon Feb 02 16:58:03 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Flip_switch.h"
#include "Flip_switch_private.h"

/* Block signals (auto storage) */
B_Flip_switch_T Flip_switch_B;

/* Block states (auto storage) */
DW_Flip_switch_T Flip_switch_DW;

/* Real-time model */
RT_MODEL_Flip_switch_T Flip_switch_M_;
RT_MODEL_Flip_switch_T *const Flip_switch_M = &Flip_switch_M_;
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(Flip_switch_M, 1);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Flip_switch_M->Timing.TaskCounters.TID[1])++;
  if ((Flip_switch_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.05s, 0.0s] */
    Flip_switch_M->Timing.TaskCounters.TID[1] = 0;
  }
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model output function for TID0 */
static void Flip_switch_output0(void)  /* Sample time: [0.01s, 0.0s] */
{
  {                                    /* Sample time: [0.01s, 0.0s] */
    rate_monotonic_scheduler();
  }
}

/* Model update function for TID0 */
static void Flip_switch_update0(void)  /* Sample time: [0.01s, 0.0s] */
{
  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Flip_switch_M->Timing.clockTick0)) {
    ++Flip_switch_M->Timing.clockTickH0;
  }

  Flip_switch_M->Timing.t[0] = Flip_switch_M->Timing.clockTick0 *
    Flip_switch_M->Timing.stepSize0 + Flip_switch_M->Timing.clockTickH0 *
    Flip_switch_M->Timing.stepSize0 * 4294967296.0;
}

/* Model output function for TID1 */
static void Flip_switch_output1(void)  /* Sample time: [0.05s, 0.0s] */
{
  real_T x;

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  if ((Flip_switch_B.Ctrl_Switchsignal1 > 0.0) &&
      (Flip_switch_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    Flip_switch_DW.DiscreteTimeIntegrator_DSTATE =
      Flip_switch_P.DiscreteTimeIntegrator_IC;
  }

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   */
  /* MATLAB Function 'MATLAB Function': '<S1>:1' */
  /* '<S1>:1:4' */
  x = rt_roundd_snf(Flip_switch_DW.DiscreteTimeIntegrator_DSTATE);
  Flip_switch_B.y = x - floor(x / 2.0) * 2.0;

  /* Switch: '<Root>/Switch1' */
  if (Flip_switch_B.y != 0.0) {
    Flip_switch_B.Switch1[0] = Flip_switch_B.Ctrl_alpha_1;
  } else {
    Flip_switch_B.Switch1[0] = Flip_switch_B.Sixaxis_alpha_1;
  }

  if (Flip_switch_B.y != 0.0) {
    Flip_switch_B.Switch1[1] = Flip_switch_B.Ctrl_u_1;
  } else {
    Flip_switch_B.Switch1[1] = Flip_switch_B.Sixaxis_u_1;
  }

  if (Flip_switch_B.y != 0.0) {
    Flip_switch_B.Switch1[2] = Flip_switch_B.Ctrl_alpha_2;
  } else {
    Flip_switch_B.Switch1[2] = Flip_switch_B.Sixaxis_alpha_2;
  }

  if (Flip_switch_B.y != 0.0) {
    Flip_switch_B.Switch1[3] = Flip_switch_B.Ctrl_u_2;
  } else {
    Flip_switch_B.Switch1[3] = Flip_switch_B.Sixaxis_u_2;
  }

  if (Flip_switch_B.y != 0.0) {
    Flip_switch_B.Switch1[4] = Flip_switch_B.Ctrl_u_BT2;
  } else {
    Flip_switch_B.Switch1[4] = Flip_switch_B.Sixaxis_u_BT;
  }

  if (Flip_switch_B.y != 0.0) {
    Flip_switch_B.Switch1[5] = Flip_switch_B.Ctrl_omega_VSP1;
  } else {
    Flip_switch_B.Switch1[5] = Flip_switch_B.Sixaxis_omega_VSP;
  }

  if (Flip_switch_B.y != 0.0) {
    Flip_switch_B.Switch1[6] = Flip_switch_B.Ctrl_omega_VSP2;
  } else {
    Flip_switch_B.Switch1[6] = Flip_switch_B.Sixaxis_omega_VSP;
  }

  /* End of Switch: '<Root>/Switch1' */
}

/* Model update function for TID1 */
static void Flip_switch_update1(void)  /* Sample time: [0.05s, 0.0s] */
{
  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  Flip_switch_DW.DiscreteTimeIntegrator_DSTATE +=
    Flip_switch_P.DiscreteTimeIntegrator_gainval *
    Flip_switch_B.Sixaxis_Switchsignal;
  if (Flip_switch_B.Ctrl_Switchsignal1 > 0.0) {
    Flip_switch_DW.DiscreteTimeIntegrator_PrevRese = 1;
  } else if (Flip_switch_B.Ctrl_Switchsignal1 < 0.0) {
    Flip_switch_DW.DiscreteTimeIntegrator_PrevRese = -1;
  } else if (Flip_switch_B.Ctrl_Switchsignal1 == 0.0) {
    Flip_switch_DW.DiscreteTimeIntegrator_PrevRese = 0;
  } else {
    Flip_switch_DW.DiscreteTimeIntegrator_PrevRese = 2;
  }

  /* End of Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Flip_switch_M->Timing.clockTick1)) {
    ++Flip_switch_M->Timing.clockTickH1;
  }

  Flip_switch_M->Timing.t[1] = Flip_switch_M->Timing.clockTick1 *
    Flip_switch_M->Timing.stepSize1 + Flip_switch_M->Timing.clockTickH1 *
    Flip_switch_M->Timing.stepSize1 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
static void Flip_switch_output(int_T tid)
{
  switch (tid) {
   case 0 :
    Flip_switch_output0();
    break;

   case 1 :
    Flip_switch_output1();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
static void Flip_switch_update(int_T tid)
{
  switch (tid) {
   case 0 :
    Flip_switch_update0();
    break;

   case 1 :
    Flip_switch_update1();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void Flip_switch_initialize(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  Flip_switch_DW.DiscreteTimeIntegrator_DSTATE =
    Flip_switch_P.DiscreteTimeIntegrator_IC;
  Flip_switch_DW.DiscreteTimeIntegrator_PrevRese = 2;
}

/* Model terminate function */
void Flip_switch_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Flip_switch_output(tid);
}

void MdlUpdate(int_T tid)
{
  Flip_switch_update(tid);
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
  Flip_switch_initialize();
}

void MdlTerminate(void)
{
  Flip_switch_terminate();
}

/* Registration function */
RT_MODEL_Flip_switch_T *Flip_switch(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Flip_switch_M, 0,
                sizeof(RT_MODEL_Flip_switch_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Flip_switch_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    Flip_switch_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Flip_switch_M->Timing.sampleTimes = (&Flip_switch_M->
      Timing.sampleTimesArray[0]);
    Flip_switch_M->Timing.offsetTimes = (&Flip_switch_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    Flip_switch_M->Timing.sampleTimes[0] = (0.01);
    Flip_switch_M->Timing.sampleTimes[1] = (0.05);

    /* task offsets */
    Flip_switch_M->Timing.offsetTimes[0] = (0.0);
    Flip_switch_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(Flip_switch_M, &Flip_switch_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Flip_switch_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = Flip_switch_M->Timing.perTaskSampleHitsArray;
    Flip_switch_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    Flip_switch_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Flip_switch_M, -1);
  Flip_switch_M->Timing.stepSize0 = 0.01;
  Flip_switch_M->Timing.stepSize1 = 0.05;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    Flip_switch_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Flip_switch_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Flip_switch_M->rtwLogInfo, (NULL));
    rtliSetLogT(Flip_switch_M->rtwLogInfo, "tout");
    rtliSetLogX(Flip_switch_M->rtwLogInfo, "");
    rtliSetLogXFinal(Flip_switch_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Flip_switch_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Flip_switch_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Flip_switch_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(Flip_switch_M->rtwLogInfo, 1);
    rtliSetLogY(Flip_switch_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Flip_switch_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Flip_switch_M->rtwLogInfo, (NULL));
  }

  Flip_switch_M->solverInfoPtr = (&Flip_switch_M->solverInfo);
  Flip_switch_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&Flip_switch_M->solverInfo, 0.01);
  rtsiSetSolverMode(&Flip_switch_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  Flip_switch_M->ModelData.blockIO = ((void *) &Flip_switch_B);
  (void) memset(((void *) &Flip_switch_B), 0,
                sizeof(B_Flip_switch_T));

  /* parameters */
  Flip_switch_M->ModelData.defaultParam = ((real_T *)&Flip_switch_P);

  /* states (dwork) */
  Flip_switch_M->ModelData.dwork = ((void *) &Flip_switch_DW);
  (void) memset((void *)&Flip_switch_DW, 0,
                sizeof(DW_Flip_switch_T));

  /* Initialize Sizes */
  Flip_switch_M->Sizes.numContStates = (0);/* Number of continuous states */
  Flip_switch_M->Sizes.numY = (0);     /* Number of model outputs */
  Flip_switch_M->Sizes.numU = (0);     /* Number of model inputs */
  Flip_switch_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Flip_switch_M->Sizes.numSampTimes = (2);/* Number of sample times */
  Flip_switch_M->Sizes.numBlocks = (28);/* Number of blocks */
  Flip_switch_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  Flip_switch_M->Sizes.numBlockPrms = (141);/* Sum of parameter "widths" */
  return Flip_switch_M;
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
#ifdef NI_ROOTMODEL_Flip_switch
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
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 23:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 24:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 23:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 24:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern Flip_switch_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Ctrl_Switch signal1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Ctrl_Switchsignal1, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_Switch signal
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Sixaxis_Switchsignal, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_alpha_1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Sixaxis_alpha_1, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Ctrl_alpha_1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Ctrl_alpha_1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_u_1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Ctrl_u_1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_alpha_2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Ctrl_alpha_2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_u_2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Ctrl_u_2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_u_BT2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Ctrl_u_BT2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_omega_VSP1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Ctrl_omega_VSP1, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Ctrl_omega_VSP2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Ctrl_omega_VSP2, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Sixaxis_u_1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Sixaxis_u_1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_alpha_2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Sixaxis_alpha_2, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Sixaxis_u_2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Sixaxis_u_2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_u_BT
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Sixaxis_u_BT, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_omega_VSP
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&Flip_switch_B.Sixaxis_omega_VSP, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 15;
}

double ni_extout[8];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Indicator: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.y,0,0,0);
  } else {
    index += 1;
  }

  // alpha_1: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,0,18,0);
  } else {
    index += 1;
  }

  // u_1: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,1,18,0);
  } else {
    index += 1;
  }

  // alpha_2: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,2,18,0);
  } else {
    index += 1;
  }

  // u_2: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,3,18,0);
  } else {
    index += 1;
  }

  // U_BT: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,4,18,0);
  } else {
    index += 1;
  }

  // omega_VSP_1: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,5,18,0);
  } else {
    index += 1;
  }

  // omega_VSP_2: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,6,18,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 8;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // Indicator: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.y,0,0,0);

  // alpha_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,0,18,0);

  // u_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,1,18,0);

  // alpha_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,2,18,0);

  // u_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,3,18,0);

  // U_BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,4,18,0);

  // omega_VSP_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,5,18,0);

  // omega_VSP_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Flip_switch_B.Switch1,6,18,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "flip_switch/Discrete-Time Integrator/gainval", offsetof(P_Flip_switch_T,
    DiscreteTimeIntegrator_gainval), 0, 1, 2, 0, 0 },

  { 1, "flip_switch/Discrete-Time Integrator/InitialCondition", offsetof
    (P_Flip_switch_T, DiscreteTimeIntegrator_IC), 23, 1, 2, 2, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 2;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 1,                                /* Parameter at index 0 */
  1, 1,                                /* Parameter at index 1 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "flip_switch/Ctrl_Switch signal1", 0, "", offsetof(B_Flip_switch_T,
    Ctrl_Switchsignal1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "flip_switch/Sixaxis_Switch signal", 0, "", offsetof(B_Flip_switch_T,
    Sixaxis_Switchsignal)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "flip_switch/Sixaxis_alpha_1", 0, "", offsetof(B_Flip_switch_T,
    Sixaxis_alpha_1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "flip_switch/Ctrl_alpha_1", 0, "", offsetof(B_Flip_switch_T, Ctrl_alpha_1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "flip_switch/Ctrl_u_1", 0, "", offsetof(B_Flip_switch_T, Ctrl_u_1)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "flip_switch/Ctrl_alpha_2", 0, "", offsetof(B_Flip_switch_T, Ctrl_alpha_2)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "flip_switch/Ctrl_u_2", 0, "", offsetof(B_Flip_switch_T, Ctrl_u_2)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "flip_switch/Ctrl_u_BT2", 0, "", offsetof(B_Flip_switch_T, Ctrl_u_BT2)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "flip_switch/Ctrl_omega_VSP1", 0, "", offsetof(B_Flip_switch_T,
    Ctrl_omega_VSP1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "flip_switch/Ctrl_omega_VSP2", 0, "", offsetof(B_Flip_switch_T,
    Ctrl_omega_VSP2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "flip_switch/Sixaxis_u_1", 0, "", offsetof(B_Flip_switch_T, Sixaxis_u_1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "flip_switch/Sixaxis_alpha_2", 0, "", offsetof(B_Flip_switch_T,
    Sixaxis_alpha_2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "flip_switch/Sixaxis_u_2", 0, "", offsetof(B_Flip_switch_T, Sixaxis_u_2)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "flip_switch/Sixaxis_u_BT", 0, "", offsetof(B_Flip_switch_T,
    Sixaxis_u_BT)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "flip_switch/Sixaxis_omega_VSP", 0, "", offsetof(B_Flip_switch_T,
    Sixaxis_omega_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 28, 0 },

  { 15, "flip_switch/Switch1", 0, "(1,1)", offsetof(B_Flip_switch_T, Switch1)+0*
    sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 30, 0 },

  { 16, "flip_switch/Switch1", 0, "(1,2)", offsetof(B_Flip_switch_T, Switch1)+1*
    sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 32, 0 },

  { 17, "flip_switch/Switch1", 0, "(1,3)", offsetof(B_Flip_switch_T, Switch1)+2*
    sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 34, 0 },

  { 18, "flip_switch/Switch1", 0, "(1,4)", offsetof(B_Flip_switch_T, Switch1)+3*
    sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 36, 0 },

  { 19, "flip_switch/Switch1", 0, "(1,5)", offsetof(B_Flip_switch_T, Switch1)+4*
    sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 38, 0 },

  { 20, "flip_switch/Switch1", 0, "(1,6)", offsetof(B_Flip_switch_T, Switch1)+5*
    sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 40, 0 },

  { 21, "flip_switch/Switch1", 0, "(1,7)", offsetof(B_Flip_switch_T, Switch1)+6*
    sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 42, 0 },

  { 22, "flip_switch/MATLAB Function", 0, "y", offsetof(B_Flip_switch_T, y)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 23;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 23;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "Ctrl_Switch signal1", 1, EXT_IN, 1, 1, 1 },

  { 1, "Sixaxis_Switch signal", 1, EXT_IN, 1, 1, 1 },

  { 2, "Sixaxis_alpha_1", 1, EXT_IN, 1, 1, 1 },

  { 3, "Ctrl_alpha_1", 1, EXT_IN, 1, 1, 1 },

  { 4, "Ctrl_u_1", 1, EXT_IN, 1, 1, 1 },

  { 5, "Ctrl_alpha_2", 1, EXT_IN, 1, 1, 1 },

  { 6, "Ctrl_u_2", 1, EXT_IN, 1, 1, 1 },

  { 7, "Ctrl_u_BT2", 1, EXT_IN, 1, 1, 1 },

  { 8, "Ctrl_omega_VSP1", 1, EXT_IN, 1, 1, 1 },

  { 9, "Ctrl_omega_VSP2", 1, EXT_IN, 1, 1, 1 },

  { 10, "Sixaxis_u_1", 1, EXT_IN, 1, 1, 1 },

  { 11, "Sixaxis_alpha_2", 1, EXT_IN, 1, 1, 1 },

  { 12, "Sixaxis_u_2", 1, EXT_IN, 1, 1, 1 },

  { 13, "Sixaxis_u_BT", 1, EXT_IN, 1, 1, 1 },

  { 14, "Sixaxis_omega_VSP", 1, EXT_IN, 1, 1, 1 },

  { 0, "Indicator", 1, EXT_OUT, 1, 1, 1 },

  { 1, "alpha_1", 1, EXT_OUT, 1, 1, 1 },

  { 2, "u_1", 1, EXT_OUT, 1, 1, 1 },

  { 3, "alpha_2", 1, EXT_OUT, 1, 1, 1 },

  { 4, "u_2", 1, EXT_OUT, 1, 1, 1 },

  { 5, "U_BT", 1, EXT_OUT, 1, 1, 1 },

  { 6, "omega_VSP_1", 1, EXT_OUT, 1, 1, 1 },

  { 7, "omega_VSP_2", 1, EXT_OUT, 1, 1, 1 },

  { -1, "", 0, 0, 0, 0, 0 }
};

/* This Task List is generated to allow access to the task specs without
 * initializing the model.
 * 0th entry is for scheduler (base rate)
 * rest for multirate model's tasks.
 */
NI_Task NI_TaskList[] DataSection(".NIVS.tasklist") =
{
  { 0, 0.01, 0.0 },

  { 1, 0.05, 0.0 },
};

int NI_NumTasks DataSection(".NIVS.numtasks") = 2;
static char* NI_CompiledModelName DataSection(".NIVS.compiledmodelname") =
  "flip_switch";
static char* NI_CompiledModelVersion = "1.15";
static char* NI_CompiledModelDateTime = "Mon Feb 02 16:58:02 2015";
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
   The undef allows us to access the real Flip_switch_P
   In the rest of the code Flip_switch_P is redefine to be the read-side
   of rtParameter.
 */
#undef Flip_switch_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &Flip_switch_P, sizeof(P_Flip_switch_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka Flip_switch_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_Flip_switch_T));
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
             (P_Flip_switch_T));
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
               (P_Flip_switch_T));

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
           (P_Flip_switch_T));
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
           (P_Flip_switch_T));
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
           (P_Flip_switch_T));
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
      *numDiscStates = 369;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.DiscreteTimeIntegrator_DSTATE, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.DiscreteTimeIntegrator_DSTATE");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Ctrl_Switchsignal1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Ctrl_Switchsignal1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Indicator_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Indicator_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Sixaxis_Switchsignal_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Sixaxis_Switchsignal_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Sixaxis_alpha_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Sixaxis_alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Ctrl_alpha_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Ctrl_alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Ctrl_u_1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Ctrl_u_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Ctrl_alpha_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Ctrl_alpha_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Ctrl_u_2_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Ctrl_u_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Ctrl_u_BT2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Ctrl_u_BT2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Ctrl_omega_VSP1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Ctrl_omega_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Ctrl_omega_VSP2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Ctrl_omega_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Sixaxis_u_1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Sixaxis_u_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Sixaxis_alpha_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Sixaxis_alpha_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Sixaxis_u_2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Sixaxis_u_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Sixaxis_u_BT_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Sixaxis_u_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.Sixaxis_omega_VSP_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.Sixaxis_omega_VSP_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.alpha_1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.u_1_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.u_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.alpha_2_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.alpha_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.u_2_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.u_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.U_BT_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.U_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.omega_VSP_1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.omega_VSP_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.omega_VSP_2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.omega_VSP_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.NIVeriStandSignalProbe_DWORK2, 0, 6, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.NIVeriStandSignalProbe_DWORK2");
    discStates[idx] = NIRT_GetValueByDataType
      (&Flip_switch_DW.DiscreteTimeIntegrator_PrevRese, 0, 2, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&Flip_switch_DW.DiscreteTimeIntegrator_PrevRese");
    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Ctrl_Switchsignal1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Ctrl_Switchsignal1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Indicator_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Indicator_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Sixaxis_Switchsignal_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Sixaxis_Switchsignal_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Sixaxis_alpha_1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Sixaxis_alpha_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Ctrl_alpha_1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Ctrl_alpha_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Ctrl_u_1_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Ctrl_u_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Ctrl_alpha_2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Ctrl_alpha_2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.Ctrl_u_2_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.Ctrl_u_2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Ctrl_u_BT2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Ctrl_u_BT2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Ctrl_omega_VSP1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Ctrl_omega_VSP1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Ctrl_omega_VSP2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Ctrl_omega_VSP2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Sixaxis_u_1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Sixaxis_u_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Sixaxis_alpha_2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Sixaxis_alpha_2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Sixaxis_u_2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Sixaxis_u_2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Sixaxis_u_BT_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Sixaxis_u_BT_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.Sixaxis_omega_VSP_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.Sixaxis_omega_VSP_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.alpha_1_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.alpha_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.u_1_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.u_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.alpha_2_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.alpha_2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.u_2_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.u_2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&Flip_switch_DW.U_BT_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&Flip_switch_DW.U_BT_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.omega_VSP_1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.omega_VSP_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.omega_VSP_2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.omega_VSP_2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.NIVeriStandSignalProbe_DWORK1, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.NIVeriStandSignalProbe_DWORK1");
    }

    for (count = 0; count < 55; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&Flip_switch_DW.NIVeriStandSignalProbe_DWORK3, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&Flip_switch_DW.NIVeriStandSignalProbe_DWORK3");
    }
  }

  if (clockTicks && clockTicksNames) {
    clockTicks[0] = S->Timing.clockTick0;
    strcpy(clockTicksNames, "clockTick0");
    clockTicks[0] = S->Timing.clockTick1;
    strcpy(clockTicksNames + (0 * 100), "clockTick1");
  }

  return NI_OK;
}

DLL_EXPORT long NIRT_SetSimState(double* contStates, double* discStates, long
  * clockTicks)
{
  long count, idx;
  if (discStates) {
    idx = 0;
    NIRT_SetValueByDataType(&Flip_switch_DW.DiscreteTimeIntegrator_DSTATE, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_Switchsignal1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Indicator_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_Switchsignal_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_alpha_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_alpha_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_u_1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_alpha_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_u_2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_u_BT2_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_omega_VSP1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_omega_VSP2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_u_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_alpha_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_u_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_u_BT_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_omega_VSP_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.alpha_1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.u_1_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&Flip_switch_DW.alpha_2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.u_2_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&Flip_switch_DW.U_BT_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&Flip_switch_DW.omega_VSP_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.omega_VSP_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.NIVeriStandSignalProbe_DWORK2, 0,
      discStates[idx++], 6, 0);
    NIRT_SetValueByDataType(&Flip_switch_DW.DiscreteTimeIntegrator_PrevRese, 0,
      discStates[idx++], 2, 0);
    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_Switchsignal1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Indicator_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_Switchsignal_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_alpha_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_alpha_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_u_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_alpha_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_u_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_u_BT2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_omega_VSP1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Ctrl_omega_VSP2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_u_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_alpha_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_u_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_u_BT_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.Sixaxis_omega_VSP_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.alpha_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.u_1_DWORK2, count, discStates[idx
        ++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.alpha_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.u_2_DWORK2, count, discStates[idx
        ++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.U_BT_DWORK2, count, discStates[idx
        ++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.omega_VSP_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.omega_VSP_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.NIVeriStandSignalProbe_DWORK1,
        count, discStates[idx++], 17, 0);
    }

    for (count = 0; count < 55; count++) {
      NIRT_SetValueByDataType(&Flip_switch_DW.NIVeriStandSignalProbe_DWORK3,
        count, discStates[idx++], 19, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
    S->Timing.clockTick1 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_Flip_switch
