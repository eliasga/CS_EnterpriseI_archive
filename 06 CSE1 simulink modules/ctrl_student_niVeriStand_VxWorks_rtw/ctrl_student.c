/*
 * ctrl_student.c
 *
 * Code generation for model "ctrl_student".
 *
 * Model version              : 1.44
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Thu Mar 19 13:51:16 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ctrl_student.h"
#include "ctrl_student_private.h"

/* Block signals (auto storage) */
B_ctrl_student_T ctrl_student_B;

/* Block states (auto storage) */
DW_ctrl_student_T ctrl_student_DW;

/* Real-time model */
RT_MODEL_ctrl_student_T ctrl_student_M_;
RT_MODEL_ctrl_student_T *const ctrl_student_M = &ctrl_student_M_;
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
static void ctrl_student_output(void)
{
  real_T u_VSP_x;
  real_T z;
  real_T tmp[9];
  int32_T i;
  real_T u_idx_1;
  real_T u_idx_2;

  /* MATLAB Function: '<S1>/Differentiate and filter' incorporates:
   *  Memory: '<S1>/Memory'
   *  Memory: '<S1>/Memory1'
   *  SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'Differentiate and rotate/Differentiate and filter': '<S6>:1' */
  /*  derivative */
  /* '<S6>:1:5' */
  ctrl_student_B.eta_dot[0] = (ctrl_student_B.x -
    ctrl_student_DW.Memory_PreviousInput[0]) / 0.01;
  ctrl_student_B.eta_dot[1] = (ctrl_student_B.y -
    ctrl_student_DW.Memory_PreviousInput[1]) / 0.01;
  ctrl_student_B.eta_dot[2] = (ctrl_student_B.psi -
    ctrl_student_DW.Memory_PreviousInput[2]) / 0.01;

  /*  filter */
  /* '<S6>:1:9' */
  ctrl_student_B.eta_dot[0] = 0.01 * ctrl_student_B.eta_dot[0] + 0.99 *
    ctrl_student_DW.Memory1_PreviousInput[0];
  ctrl_student_B.eta_dot[1] = 0.01 * ctrl_student_B.eta_dot[1] + 0.99 *
    ctrl_student_DW.Memory1_PreviousInput[1];
  ctrl_student_B.eta_dot[2] = 0.01 * ctrl_student_B.eta_dot[2] + 0.99 *
    ctrl_student_DW.Memory1_PreviousInput[2];

  /* MATLAB Function: '<S1>/Rotate' */
  /* MATLAB Function 'Differentiate and rotate/Rotate': '<S8>:1' */
  /* '<S8>:1:3' */
  /* '<S8>:1:6' */
  tmp[0] = cos(ctrl_student_B.psi);
  tmp[3] = sin(ctrl_student_B.psi);
  tmp[6] = 0.0;
  tmp[1] = -sin(ctrl_student_B.psi);
  tmp[4] = cos(ctrl_student_B.psi);
  tmp[7] = 0.0;
  tmp[2] = 0.0;
  tmp[5] = 0.0;
  tmp[8] = 1.0;
  for (i = 0; i < 3; i++) {
    ctrl_student_B.nu[i] = 0.0;
    ctrl_student_B.nu[i] += tmp[i] * ctrl_student_B.eta_dot[0];
    ctrl_student_B.nu[i] += tmp[i + 3] * ctrl_student_B.eta_dot[1];
    ctrl_student_B.nu[i] += tmp[i + 6] * ctrl_student_B.eta_dot[2];
  }

  /* End of MATLAB Function: '<S1>/Rotate' */

  /* MATLAB Function: '<S1>/Differentiate and filter1' incorporates:
   *  Memory: '<S1>/Memory2'
   *  Memory: '<S1>/Memory3'
   */
  /* MATLAB Function 'Differentiate and rotate/Differentiate and filter1': '<S7>:1' */
  /*  derivative */
  /* '<S7>:1:5' */
  ctrl_student_B.nu_dot[0] = (ctrl_student_B.nu[0] -
    ctrl_student_DW.Memory2_PreviousInput[0]) / 0.01;
  ctrl_student_B.nu_dot[1] = (ctrl_student_B.nu[1] -
    ctrl_student_DW.Memory2_PreviousInput[1]) / 0.01;
  ctrl_student_B.nu_dot[2] = (ctrl_student_B.nu[2] -
    ctrl_student_DW.Memory2_PreviousInput[2]) / 0.01;

  /*  filter */
  /* '<S7>:1:9' */
  ctrl_student_B.nu_dot[0] = 0.01 * ctrl_student_B.nu_dot[0] + 0.99 *
    ctrl_student_DW.Memory3_PreviousInput[0];
  ctrl_student_B.nu_dot[1] = 0.01 * ctrl_student_B.nu_dot[1] + 0.99 *
    ctrl_student_DW.Memory3_PreviousInput[1];
  ctrl_student_B.nu_dot[2] = 0.01 * ctrl_student_B.nu_dot[2] + 0.99 *
    ctrl_student_DW.Memory3_PreviousInput[2];

  /* MATLAB Function: '<Root>/Thrust allocation' incorporates:
   *  Constant: '<Root>/Constant'
   */
  /* MATLAB Function 'Thrust allocation': '<S3>:1' */
  /*  Forces and moments vector */
  /* '<S3>:1:4' */
  /*  Extended thrust configuration matrix */
  /*  Extended thrust coefficient matrix */
  /*  tau = T*K*u inverse */
  /* '<S3>:1:23' */
  u_idx_1 = 0.0 - 0.0 * 0.0;
  u_idx_2 = ((0.0 - 0.0 * 0.0) - u_idx_1 * -0.4575) / 2.221505;
  u_idx_1 -= u_idx_2 * 2.629;
  z = u_idx_1 / 1.165;
  u_idx_1 /= 1.165;
  u_idx_1 = (0.0 - u_idx_2 * 0.0) - u_idx_1 * 0.0;

  /* '<S3>:1:25' */
  /* '<S3>:1:27' */
  u_VSP_x = u_idx_1 / 1.165;

  /* '<S3>:1:28' */
  /* '<S3>:1:29' */
  /* '<S3>:1:30' */
  if (ctrl_student_P.Constant_Value != 0.0) {
    /* '<S3>:1:33' */
    ctrl_student_B.omega_VSP = 0.3;
  } else {
    /* '<S3>:1:35' */
    ctrl_student_B.omega_VSP = 0.0;
  }

  ctrl_student_B.u_BT = u_idx_2;
  ctrl_student_B.u_VSP = sqrt(u_VSP_x * u_VSP_x + z * z);
  ctrl_student_B.alpha_VSP = rt_atan2d_snf(z, u_idx_1 / 1.165);

  /* End of MATLAB Function: '<Root>/Thrust allocation' */

  /* MATLAB Function: '<Root>/control limit checking' incorporates:
   *  SignalConversion: '<S4>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'control limit checking': '<S4>:1' */
  /* '<S4>:1:2' */
  /* '<S4>:1:3' */
  /* '<S4>:1:5' */
  /* '<S4>:1:6' */
  /* '<S4>:1:7' */
  /* '<S4>:1:8' */
  /* '<S4>:1:10' */
  /* '<S4>:1:18' */
  ctrl_student_B.fault = !((-1.0 <= ctrl_student_B.u_BT) && (ctrl_student_B.u_BT
    <= 1.0) && (0.0 <= ctrl_student_B.u_VSP) && (ctrl_student_B.u_VSP <= 1.0) &&
                           (0.0 <= ctrl_student_B.u_VSP) &&
    (ctrl_student_B.u_VSP <= 2.0) && (-3.1415926535897931 <=
    ctrl_student_B.alpha_VSP) && (ctrl_student_B.alpha_VSP <= 3.1415926535897931)
    && (-3.1415926535897931 <= ctrl_student_B.alpha_VSP) &&
    (ctrl_student_B.alpha_VSP <= 3.1415926535897931) && (-1.0 <=
    ctrl_student_B.omega_VSP) && (ctrl_student_B.omega_VSP <= 1.0) && (-1.0 <=
    ctrl_student_B.omega_VSP) && (ctrl_student_B.omega_VSP <= 1.0));
}

/* Model update function */
static void ctrl_student_update(void)
{
  /* Update for Memory: '<S1>/Memory' */
  ctrl_student_DW.Memory_PreviousInput[0] = ctrl_student_B.x;
  ctrl_student_DW.Memory_PreviousInput[1] = ctrl_student_B.y;
  ctrl_student_DW.Memory_PreviousInput[2] = ctrl_student_B.psi;

  /* Update for Memory: '<S1>/Memory1' */
  ctrl_student_DW.Memory1_PreviousInput[0] = ctrl_student_B.eta_dot[0];
  ctrl_student_DW.Memory1_PreviousInput[1] = ctrl_student_B.eta_dot[1];
  ctrl_student_DW.Memory1_PreviousInput[2] = ctrl_student_B.eta_dot[2];

  /* Update for Memory: '<S1>/Memory2' */
  ctrl_student_DW.Memory2_PreviousInput[0] = ctrl_student_B.nu[0];
  ctrl_student_DW.Memory2_PreviousInput[1] = ctrl_student_B.nu[1];
  ctrl_student_DW.Memory2_PreviousInput[2] = ctrl_student_B.nu[2];

  /* Update for Memory: '<S1>/Memory3' */
  ctrl_student_DW.Memory3_PreviousInput[0] = ctrl_student_B.nu_dot[0];
  ctrl_student_DW.Memory3_PreviousInput[1] = ctrl_student_B.nu_dot[1];
  ctrl_student_DW.Memory3_PreviousInput[2] = ctrl_student_B.nu_dot[2];

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ctrl_student_M->Timing.clockTick0)) {
    ++ctrl_student_M->Timing.clockTickH0;
  }

  ctrl_student_M->Timing.t[0] = ctrl_student_M->Timing.clockTick0 *
    ctrl_student_M->Timing.stepSize0 + ctrl_student_M->Timing.clockTickH0 *
    ctrl_student_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void ctrl_student_initialize(void)
{
  /* InitializeConditions for Memory: '<S1>/Memory' */
  ctrl_student_DW.Memory_PreviousInput[0] = ctrl_student_P.Memory_X0[0];
  ctrl_student_DW.Memory_PreviousInput[1] = ctrl_student_P.Memory_X0[1];
  ctrl_student_DW.Memory_PreviousInput[2] = ctrl_student_P.Memory_X0[2];

  /* InitializeConditions for Memory: '<S1>/Memory1' */
  ctrl_student_DW.Memory1_PreviousInput[0] = ctrl_student_P.Memory1_X0[0];
  ctrl_student_DW.Memory1_PreviousInput[1] = ctrl_student_P.Memory1_X0[1];
  ctrl_student_DW.Memory1_PreviousInput[2] = ctrl_student_P.Memory1_X0[2];

  /* InitializeConditions for Memory: '<S1>/Memory2' */
  ctrl_student_DW.Memory2_PreviousInput[0] = ctrl_student_P.Memory2_X0[0];
  ctrl_student_DW.Memory2_PreviousInput[1] = ctrl_student_P.Memory2_X0[1];
  ctrl_student_DW.Memory2_PreviousInput[2] = ctrl_student_P.Memory2_X0[2];

  /* InitializeConditions for Memory: '<S1>/Memory3' */
  ctrl_student_DW.Memory3_PreviousInput[0] = ctrl_student_P.Memory3_X0[0];
  ctrl_student_DW.Memory3_PreviousInput[1] = ctrl_student_P.Memory3_X0[1];
  ctrl_student_DW.Memory3_PreviousInput[2] = ctrl_student_P.Memory3_X0[2];
}

/* Model terminate function */
void ctrl_student_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  ctrl_student_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  ctrl_student_update();
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
  ctrl_student_initialize();
}

void MdlTerminate(void)
{
  ctrl_student_terminate();
}

/* Registration function */
RT_MODEL_ctrl_student_T *ctrl_student(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ctrl_student_M, 0,
                sizeof(RT_MODEL_ctrl_student_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ctrl_student_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    ctrl_student_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ctrl_student_M->Timing.sampleTimes =
      (&ctrl_student_M->Timing.sampleTimesArray[0]);
    ctrl_student_M->Timing.offsetTimes =
      (&ctrl_student_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ctrl_student_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    ctrl_student_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(ctrl_student_M, &ctrl_student_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ctrl_student_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    ctrl_student_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ctrl_student_M, -1);
  ctrl_student_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    ctrl_student_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ctrl_student_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ctrl_student_M->rtwLogInfo, (NULL));
    rtliSetLogT(ctrl_student_M->rtwLogInfo, "tout");
    rtliSetLogX(ctrl_student_M->rtwLogInfo, "");
    rtliSetLogXFinal(ctrl_student_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ctrl_student_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ctrl_student_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(ctrl_student_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(ctrl_student_M->rtwLogInfo, 1);
    rtliSetLogY(ctrl_student_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(ctrl_student_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(ctrl_student_M->rtwLogInfo, (NULL));
  }

  ctrl_student_M->solverInfoPtr = (&ctrl_student_M->solverInfo);
  ctrl_student_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&ctrl_student_M->solverInfo, 0.01);
  rtsiSetSolverMode(&ctrl_student_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  ctrl_student_M->ModelData.blockIO = ((void *) &ctrl_student_B);
  (void) memset(((void *) &ctrl_student_B), 0,
                sizeof(B_ctrl_student_T));

  /* parameters */
  ctrl_student_M->ModelData.defaultParam = ((real_T *)&ctrl_student_P);

  /* states (dwork) */
  ctrl_student_M->ModelData.dwork = ((void *) &ctrl_student_DW);
  (void) memset((void *)&ctrl_student_DW, 0,
                sizeof(DW_ctrl_student_T));

  /* Initialize Sizes */
  ctrl_student_M->Sizes.numContStates = (0);/* Number of continuous states */
  ctrl_student_M->Sizes.numY = (0);    /* Number of model outputs */
  ctrl_student_M->Sizes.numU = (0);    /* Number of model inputs */
  ctrl_student_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  ctrl_student_M->Sizes.numSampTimes = (1);/* Number of sample times */
  ctrl_student_M->Sizes.numBlocks = (29);/* Number of blocks */
  ctrl_student_M->Sizes.numBlockIO = (11);/* Number of block outputs */
  ctrl_student_M->Sizes.numBlockPrms = (80);/* Sum of parameter "widths" */
  return ctrl_student_M;
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
#ifdef NI_ROOTMODEL_ctrl_student
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 18:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 19:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 20:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 24:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 18:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 24:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

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

extern ctrl_student_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.x, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.y, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.psi, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 3;
}

double ni_extout[8];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // control input u exceeds bounds: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.fault,0,8,0);
  } else {
    index += 1;
  }

  // u/alpha_VSP2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.alpha_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/omega_VSP1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.omega_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/omega_VSP2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.omega_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/alpha_VSP1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.alpha_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/u_BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_BT,0,0,0);
  } else {
    index += 1;
  }

  // u/u_VSP1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/u_VSP2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_VSP,0,0,0);
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

  // control input u exceeds bounds: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.fault,0,8,0);

  // u/alpha_VSP2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.alpha_VSP,0,0,0);

  // u/omega_VSP1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.omega_VSP,0,0,0);

  // u/omega_VSP2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.omega_VSP,0,0,0);

  // u/alpha_VSP1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.alpha_VSP,0,0,0);

  // u/u_BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_BT,0,0,0);

  // u/u_VSP1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_VSP,0,0,0);

  // u/u_VSP2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_VSP,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "ctrl_student/Differentiate and rotate/Memory/X0", offsetof
    (P_ctrl_student_T, Memory_X0), 25, 3, 2, 0, 0 },

  { 1, "ctrl_student/Differentiate and rotate/Memory1/X0", offsetof
    (P_ctrl_student_T, Memory1_X0), 25, 3, 2, 2, 0 },

  { 2, "ctrl_student/Differentiate and rotate/Memory2/X0", offsetof
    (P_ctrl_student_T, Memory2_X0), 25, 3, 2, 4, 0 },

  { 3, "ctrl_student/Differentiate and rotate/Memory3/X0", offsetof
    (P_ctrl_student_T, Memory3_X0), 25, 3, 2, 6, 0 },

  { 4, "ctrl_student/Constant/Value", offsetof(P_ctrl_student_T, Constant_Value),
    24, 1, 2, 8, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 5;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 3,                                /* Parameter at index 0 */
  1, 3,                                /* Parameter at index 1 */
  1, 3,                                /* Parameter at index 2 */
  1, 3,                                /* Parameter at index 3 */
  1, 1,                                /* Parameter at index 4 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "ctrl_student/x", 0, "", offsetof(B_ctrl_student_T, x)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "ctrl_student/y", 0, "", offsetof(B_ctrl_student_T, y)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "ctrl_student/psi", 0, "", offsetof(B_ctrl_student_T, psi)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "ctrl_student/Thrust allocation", 0, "u_BT", offsetof(B_ctrl_student_T,
    u_BT)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "ctrl_student/Thrust allocation", 1, "u_VSP", offsetof(B_ctrl_student_T,
    u_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "ctrl_student/Thrust allocation", 2, "alpha_VSP", offsetof
    (B_ctrl_student_T, alpha_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 10, 0
  },

  { 6, "ctrl_student/Thrust allocation", 3, "omega_VSP", offsetof
    (B_ctrl_student_T, omega_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 12, 0
  },

  { 7, "ctrl_student/Differentiate and rotate/Rotate", 0, "nu(1,1)", offsetof
    (B_ctrl_student_T, nu)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 14, 0 },

  { 8, "ctrl_student/Differentiate and rotate/Rotate", 0, "nu(1,2)", offsetof
    (B_ctrl_student_T, nu)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 16, 0 },

  { 9, "ctrl_student/Differentiate and rotate/Rotate", 0, "nu(1,3)", offsetof
    (B_ctrl_student_T, nu)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 18, 0 },

  { 10, "ctrl_student/Differentiate and rotate/Differentiate and filter1", 0,
    "nu_dot(1,1)", offsetof(B_ctrl_student_T, nu_dot)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 20, 0 },

  { 11, "ctrl_student/Differentiate and rotate/Differentiate and filter1", 0,
    "nu_dot(1,2)", offsetof(B_ctrl_student_T, nu_dot)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 22, 0 },

  { 12, "ctrl_student/Differentiate and rotate/Differentiate and filter1", 0,
    "nu_dot(1,3)", offsetof(B_ctrl_student_T, nu_dot)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 24, 0 },

  { 13, "ctrl_student/Differentiate and rotate/Differentiate and filter", 0,
    "eta_dot(1,1)", offsetof(B_ctrl_student_T, eta_dot)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 26, 0 },

  { 14, "ctrl_student/Differentiate and rotate/Differentiate and filter", 0,
    "eta_dot(1,2)", offsetof(B_ctrl_student_T, eta_dot)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 28, 0 },

  { 15, "ctrl_student/Differentiate and rotate/Differentiate and filter", 0,
    "eta_dot(1,3)", offsetof(B_ctrl_student_T, eta_dot)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 30, 0 },

  { 16, "ctrl_student/control limit checking", 0, "fault", offsetof
    (B_ctrl_student_T, fault)+0*sizeof(boolean_T), BLOCKIO_SIG, 8, 1, 2, 32, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 17;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 11;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "x", 0, EXT_IN, 1, 1, 1 },

  { 1, "y", 0, EXT_IN, 1, 1, 1 },

  { 2, "psi", 0, EXT_IN, 1, 1, 1 },

  { 0, "control input u exceeds bounds", 0, EXT_OUT, 1, 1, 1 },

  { 1, "u/alpha_VSP2", 0, EXT_OUT, 1, 1, 1 },

  { 2, "u/omega_VSP1", 0, EXT_OUT, 1, 1, 1 },

  { 3, "u/omega_VSP2", 0, EXT_OUT, 1, 1, 1 },

  { 4, "u/alpha_VSP1", 0, EXT_OUT, 1, 1, 1 },

  { 5, "u/u_BT", 0, EXT_OUT, 1, 1, 1 },

  { 6, "u/u_VSP1", 0, EXT_OUT, 1, 1, 1 },

  { 7, "u/u_VSP2", 0, EXT_OUT, 1, 1, 1 },

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
  "ctrl_student";
static char* NI_CompiledModelVersion = "1.44";
static char* NI_CompiledModelDateTime = "Thu Mar 19 13:51:15 2015";
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
   The undef allows us to access the real ctrl_student_P
   In the rest of the code ctrl_student_P is redefine to be the read-side
   of rtParameter.
 */
#undef ctrl_student_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &ctrl_student_P, sizeof(P_ctrl_student_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka ctrl_student_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_ctrl_student_T));
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
             (P_ctrl_student_T));
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
               (P_ctrl_student_T));

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
           (P_ctrl_student_T));
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
           (P_ctrl_student_T));
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
           (P_ctrl_student_T));
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
      *numDiscStates = 236;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.x_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.y_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.psi_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory1_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory1_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory1_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory1_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory1_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory1_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory2_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory2_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory2_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory3_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory3_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory3_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.controlinputuexceedsbounds_DWOR, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.controlinputuexceedsbounds_DWOR");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.alpha_VSP2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.alpha_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.omega_VSP1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.omega_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.omega_VSP2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.omega_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.alpha_VSP1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.alpha_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_BT_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_VSP1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_VSP2_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.NIVeriStandSignalProbe_DWORK2, 0, 6, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.NIVeriStandSignalProbe_DWORK2");
    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.x_DWORK2, count,
        19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.x_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.y_DWORK2, count,
        19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.y_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.psi_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.psi_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.controlinputuexceedsbounds_DW_j, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.controlinputuexceedsbounds_DW_j");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.alpha_VSP2_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.alpha_VSP2_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.omega_VSP1_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.omega_VSP1_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.omega_VSP2_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.omega_VSP2_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.alpha_VSP1_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.alpha_VSP1_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_BT_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_BT_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_VSP1_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_VSP1_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_VSP2_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_VSP2_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.NIVeriStandSignalProbe_DWORK1, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.NIVeriStandSignalProbe_DWORK1");
    }

    for (count = 0; count < 56; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.NIVeriStandSignalProbe_DWORK3, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.NIVeriStandSignalProbe_DWORK3");
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
    NIRT_SetValueByDataType(&ctrl_student_DW.x_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&ctrl_student_DW.y_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&ctrl_student_DW.psi_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory1_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory1_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory1_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory2_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory2_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory2_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory3_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory3_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory3_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.controlinputuexceedsbounds_DWOR, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.alpha_VSP2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.omega_VSP1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.omega_VSP2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.alpha_VSP1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.u_BT_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.u_VSP1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.u_VSP2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.NIVeriStandSignalProbe_DWORK2, 0,
      discStates[idx++], 6, 0);
    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.x_DWORK2, count, discStates[idx++],
        19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.y_DWORK2, count, discStates[idx++],
        19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.psi_DWORK2, count, discStates[idx
        ++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.controlinputuexceedsbounds_DW_j,
        count, discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.alpha_VSP2_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.omega_VSP1_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.omega_VSP2_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.alpha_VSP1_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.u_BT_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.u_VSP1_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.u_VSP2_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.NIVeriStandSignalProbe_DWORK1,
        count, discStates[idx++], 19, 0);
    }

    for (count = 0; count < 56; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.NIVeriStandSignalProbe_DWORK3,
        count, discStates[idx++], 20, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_ctrl_student
