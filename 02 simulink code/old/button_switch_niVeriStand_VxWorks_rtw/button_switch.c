/*
 * button_switch.c
 *
 * Code generation for model "button_switch".
 *
 * Model version              : 1.11
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Feb 03 14:35:05 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "button_switch.h"
#include "button_switch_private.h"

/* Block signals (auto storage) */
B_button_switch_T button_switch_B;

/* Block states (auto storage) */
DW_button_switch_T button_switch_DW;

/* Real-time model */
RT_MODEL_button_switch_T button_switch_M_;
RT_MODEL_button_switch_T *const button_switch_M = &button_switch_M_;

/* Model output function */
static void button_switch_output(void)
{
  real_T signal;

  /* MATLAB Function: '<S4>/Switch_function' incorporates:
   *  Memory: '<S4>/Memory'
   */
  /* MATLAB Function 'Switch_subsystem/Switch_function': '<S6>:1' */
  /* % Function that takes in impulse button sigals [0,1] and sends out a  */
  /*  different signal depentent pn which button has been pressed */
  /* '<S6>:1:8' */
  signal = button_switch_DW.Memory_PreviousInput;
  if (button_switch_B.Switch_Cross != 0.0) {
    /* '<S6>:1:10' */
    /* '<S6>:1:11' */
    signal = 1.0;
  }

  if (button_switch_B.Switch_Square != 0.0) {
    /* '<S6>:1:14' */
    /* '<S6>:1:15' */
    signal = 2.0;
  }

  if (button_switch_B.Switch_Circle != 0.0) {
    /* '<S6>:1:18' */
    /* '<S6>:1:19' */
    signal = 3.0;
  }

  if (button_switch_B.Switch_Triangle != 0.0) {
    /* '<S6>:1:22' */
    /* '<S6>:1:23' */
    signal = 4.0;
  }

  /* '<S6>:1:28' */
  button_switch_B.switch_signal = signal;

  /* End of MATLAB Function: '<S4>/Switch_function' */

  /* MultiPortSwitch: '<Root>/Multiport Switch' */
  switch ((int32_T)button_switch_B.switch_signal) {
   case 1:
    button_switch_B.MultiportSwitch[0] = button_switch_B.Student_Ctrl_alpha_1;
    button_switch_B.MultiportSwitch[1] = button_switch_B.Student_Ctrl_u_1;
    button_switch_B.MultiportSwitch[2] = button_switch_B.Student_Ctrl_alpha_2;
    button_switch_B.MultiportSwitch[3] = button_switch_B.Student_Ctrl_u_2;
    button_switch_B.MultiportSwitch[4] = button_switch_B.Student_Ctrl_u_BT2;
    button_switch_B.MultiportSwitch[5] = button_switch_B.Student_Ctrl_omega_VSP1;
    button_switch_B.MultiportSwitch[6] = button_switch_B.Student_Ctrl_omega_VSP2;
    break;

   case 2:
    button_switch_B.MultiportSwitch[0] =
      button_switch_B.Sixaxis_force_Ctrl_alpha_1;
    button_switch_B.MultiportSwitch[1] = button_switch_B.Sixaxis_force_Ctrl_u_1;
    button_switch_B.MultiportSwitch[2] =
      button_switch_B.Sixaxis_force_Ctrl_alpha_2;
    button_switch_B.MultiportSwitch[3] = button_switch_B.Sixaxis_force_Ctrl_u_2;
    button_switch_B.MultiportSwitch[4] =
      button_switch_B.Sixaxis_force_Ctrl_u_BT2;
    button_switch_B.MultiportSwitch[5] =
      button_switch_B.Sixaxis_force_Ctrl_omega_VSP1;
    button_switch_B.MultiportSwitch[6] =
      button_switch_B.Sixaxis_force_Ctrl_omega_VSP2;
    break;

   case 3:
    button_switch_B.MultiportSwitch[0] = button_switch_B.Ctrl_alpha_1;
    button_switch_B.MultiportSwitch[1] = button_switch_B.Ctrl_u_1;
    button_switch_B.MultiportSwitch[2] = button_switch_B.Ctrl_alpha_2;
    button_switch_B.MultiportSwitch[3] = button_switch_B.Ctrl_u_2;
    button_switch_B.MultiportSwitch[4] = button_switch_B.Ctrl_u_BT2;
    button_switch_B.MultiportSwitch[5] = button_switch_B.Ctrl_omega_VSP1;
    button_switch_B.MultiportSwitch[6] = button_switch_B.Ctrl_omega_VSP2;
    break;

   default:
    button_switch_B.MultiportSwitch[0] = button_switch_B.Sixaxis_alpha_1;
    button_switch_B.MultiportSwitch[1] = button_switch_B.Sixaxis_u_1;
    button_switch_B.MultiportSwitch[2] = button_switch_B.Sixaxis_alpha_2;
    button_switch_B.MultiportSwitch[3] = button_switch_B.Sixaxis_u_2;
    button_switch_B.MultiportSwitch[4] = button_switch_B.Sixaxis_u_BT;
    button_switch_B.MultiportSwitch[5] = button_switch_B.Sixaxis_omega_VSP;
    button_switch_B.MultiportSwitch[6] = button_switch_B.Sixaxis_omega_VSP;
    break;
  }

  /* End of MultiPortSwitch: '<Root>/Multiport Switch' */
}

/* Model update function */
static void button_switch_update(void)
{
  /* Update for Memory: '<S4>/Memory' */
  button_switch_DW.Memory_PreviousInput = button_switch_B.switch_signal;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++button_switch_M->Timing.clockTick0)) {
    ++button_switch_M->Timing.clockTickH0;
  }

  button_switch_M->Timing.t[0] = button_switch_M->Timing.clockTick0 *
    button_switch_M->Timing.stepSize0 + button_switch_M->Timing.clockTickH0 *
    button_switch_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void button_switch_initialize(void)
{
  /* InitializeConditions for Memory: '<S4>/Memory' */
  button_switch_DW.Memory_PreviousInput = button_switch_P.Memory_X0;
}

/* Model terminate function */
void button_switch_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  button_switch_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  button_switch_update();
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
  button_switch_initialize();
}

void MdlTerminate(void)
{
  button_switch_terminate();
}

/* Registration function */
RT_MODEL_button_switch_T *button_switch(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)button_switch_M, 0,
                sizeof(RT_MODEL_button_switch_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = button_switch_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    button_switch_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    button_switch_M->Timing.sampleTimes =
      (&button_switch_M->Timing.sampleTimesArray[0]);
    button_switch_M->Timing.offsetTimes =
      (&button_switch_M->Timing.offsetTimesArray[0]);

    /* task periods */
    button_switch_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    button_switch_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(button_switch_M, &button_switch_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = button_switch_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    button_switch_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(button_switch_M, -1);
  button_switch_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    button_switch_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(button_switch_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(button_switch_M->rtwLogInfo, (NULL));
    rtliSetLogT(button_switch_M->rtwLogInfo, "tout");
    rtliSetLogX(button_switch_M->rtwLogInfo, "");
    rtliSetLogXFinal(button_switch_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(button_switch_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(button_switch_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(button_switch_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(button_switch_M->rtwLogInfo, 1);
    rtliSetLogY(button_switch_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(button_switch_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(button_switch_M->rtwLogInfo, (NULL));
  }

  button_switch_M->solverInfoPtr = (&button_switch_M->solverInfo);
  button_switch_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&button_switch_M->solverInfo, 0.01);
  rtsiSetSolverMode(&button_switch_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  button_switch_M->ModelData.blockIO = ((void *) &button_switch_B);
  (void) memset(((void *) &button_switch_B), 0,
                sizeof(B_button_switch_T));

  /* parameters */
  button_switch_M->ModelData.defaultParam = ((real_T *)&button_switch_P);

  /* states (dwork) */
  button_switch_M->ModelData.dwork = ((void *) &button_switch_DW);
  (void) memset((void *)&button_switch_DW, 0,
                sizeof(DW_button_switch_T));

  /* Initialize Sizes */
  button_switch_M->Sizes.numContStates = (0);/* Number of continuous states */
  button_switch_M->Sizes.numY = (0);   /* Number of model outputs */
  button_switch_M->Sizes.numU = (0);   /* Number of model inputs */
  button_switch_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  button_switch_M->Sizes.numSampTimes = (1);/* Number of sample times */
  button_switch_M->Sizes.numBlocks = (43);/* Number of blocks */
  button_switch_M->Sizes.numBlockIO = (33);/* Number of block outputs */
  button_switch_M->Sizes.numBlockPrms = (235);/* Sum of parameter "widths" */
  return button_switch_M;
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
#ifdef NI_ROOTMODEL_button_switch
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
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 22:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 23:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 22:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 23:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern button_switch_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Switch_Cross
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Switch_Cross, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Switch_Square
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Switch_Square, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Switch_Circle
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Switch_Circle, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Switch_Triangle
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Switch_Triangle, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Student_CTRL/Student_Ctrl_alpha_1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Student_Ctrl_alpha_1, 0, data[index
      ++], 0, 0);
  } else {
    index += 1;
  }

  // Student_CTRL/Student_Ctrl_alpha_2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Student_Ctrl_alpha_2, 0, data[index
      ++], 0, 0);
  } else {
    index += 1;
  }

  // Student_CTRL/Student_Ctrl_omega_VSP1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Student_Ctrl_omega_VSP1, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Student_CTRL/Student_Ctrl_omega_VSP2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Student_Ctrl_omega_VSP2, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Student_CTRL/Student_Ctrl_u_1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Student_Ctrl_u_1, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Student_CTRL/Student_Ctrl_u_2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Student_Ctrl_u_2, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Student_CTRL/Student_Ctrl_u_BT2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Student_Ctrl_u_BT2, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_force_ctrl/Sixaxis_force_Ctrl_alpha_1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_force_Ctrl_alpha_1, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_force_ctrl/Sixaxis_force_Ctrl_alpha_2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_force_Ctrl_alpha_2, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_force_ctrl/Sixaxis_force_Ctrl_omega_VSP1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_force_Ctrl_omega_VSP1, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_force_ctrl/Sixaxis_force_Ctrl_omega_VSP2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_force_Ctrl_omega_VSP2, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_force_Ctrl_u_1, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_force_Ctrl_u_2, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_BT2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_force_Ctrl_u_BT2, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Template_DP_ctrl/Ctrl_alpha_1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Ctrl_alpha_1, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Template_DP_ctrl/Ctrl_alpha_2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Ctrl_alpha_2, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Template_DP_ctrl/Ctrl_omega_VSP1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Ctrl_omega_VSP1, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Template_DP_ctrl/Ctrl_omega_VSP2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Ctrl_omega_VSP2, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Template_DP_ctrl/Ctrl_u_1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Ctrl_u_1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Template_DP_ctrl/Ctrl_u_2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Ctrl_u_2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Template_DP_ctrl/Ctrl_u_BT2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Ctrl_u_BT2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_manual_thruster_ctlr/Sixaxis_alpha_1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_alpha_1, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_manual_thruster_ctlr/Sixaxis_alpha_2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_alpha_2, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_manual_thruster_ctlr/Sixaxis_omega_VSP
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_omega_VSP, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_manual_thruster_ctlr/Sixaxis_u_1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_u_1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_manual_thruster_ctlr/Sixaxis_u_2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_u_2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Sixaxis_manual_thruster_ctlr/Sixaxis_u_BT
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&button_switch_B.Sixaxis_u_BT, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 31;
}

double ni_extout[8];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // U_BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&button_switch_B.MultiportSwitch,4,17,0);
  } else {
    index += 1;
  }

  // alpha_1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&button_switch_B.MultiportSwitch,0,17,0);
  } else {
    index += 1;
  }

  // u_1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&button_switch_B.MultiportSwitch,1,17,0);
  } else {
    index += 1;
  }

  // alpha_2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&button_switch_B.MultiportSwitch,2,17,0);
  } else {
    index += 1;
  }

  // u_2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&button_switch_B.MultiportSwitch,3,17,0);
  } else {
    index += 1;
  }

  // omega_VSP_1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&button_switch_B.MultiportSwitch,5,17,0);
  } else {
    index += 1;
  }

  // omega_VSP_2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&button_switch_B.MultiportSwitch,6,17,0);
  } else {
    index += 1;
  }

  // Switch_indicator: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.switch_signal,
      0,0,0);
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

  // U_BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.MultiportSwitch,
    4,17,0);

  // alpha_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.MultiportSwitch,
    0,17,0);

  // u_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.MultiportSwitch,
    1,17,0);

  // alpha_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.MultiportSwitch,
    2,17,0);

  // u_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.MultiportSwitch,
    3,17,0);

  // omega_VSP_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.MultiportSwitch,
    5,17,0);

  // omega_VSP_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.MultiportSwitch,
    6,17,0);

  // Switch_indicator: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&button_switch_B.switch_signal,0,
    0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "button_switch/Switch_subsystem/Memory/X0", offsetof(P_button_switch_T,
    Memory_X0), 22, 1, 2, 0, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 1;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 1,                                /* Parameter at index 0 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "button_switch/Switch_Cross", 0, "", offsetof(B_button_switch_T,
    Switch_Cross)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "button_switch/Switch_Square", 0, "", offsetof(B_button_switch_T,
    Switch_Square)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "button_switch/Switch_Circle", 0, "", offsetof(B_button_switch_T,
    Switch_Circle)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "button_switch/Switch_Triangle", 0, "", offsetof(B_button_switch_T,
    Switch_Triangle)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "button_switch/Student_CTRL/Student_Ctrl_alpha_1", 0, "", offsetof
    (B_button_switch_T, Student_Ctrl_alpha_1)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 8, 0 },

  { 5, "button_switch/Student_CTRL/Student_Ctrl_alpha_2", 0, "", offsetof
    (B_button_switch_T, Student_Ctrl_alpha_2)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 10, 0 },

  { 6, "button_switch/Student_CTRL/Student_Ctrl_omega_VSP1", 0, "", offsetof
    (B_button_switch_T, Student_Ctrl_omega_VSP1)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 12, 0 },

  { 7, "button_switch/Student_CTRL/Student_Ctrl_omega_VSP2", 0, "", offsetof
    (B_button_switch_T, Student_Ctrl_omega_VSP2)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 14, 0 },

  { 8, "button_switch/Student_CTRL/Student_Ctrl_u_1", 0, "", offsetof
    (B_button_switch_T, Student_Ctrl_u_1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    16, 0 },

  { 9, "button_switch/Student_CTRL/Student_Ctrl_u_2", 0, "", offsetof
    (B_button_switch_T, Student_Ctrl_u_2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    18, 0 },

  { 10, "button_switch/Student_CTRL/Student_Ctrl_u_BT2", 0, "", offsetof
    (B_button_switch_T, Student_Ctrl_u_BT2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 20, 0 },

  { 11, "button_switch/Sixaxis_force_ctrl/Sixaxis_force_Ctrl_alpha_1", 0, "",
    offsetof(B_button_switch_T, Sixaxis_force_Ctrl_alpha_1)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "button_switch/Sixaxis_force_ctrl/Sixaxis_force_Ctrl_alpha_2", 0, "",
    offsetof(B_button_switch_T, Sixaxis_force_Ctrl_alpha_2)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "button_switch/Sixaxis_force_ctrl/Sixaxis_force_Ctrl_omega_VSP1", 0, "",
    offsetof(B_button_switch_T, Sixaxis_force_Ctrl_omega_VSP1)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "button_switch/Sixaxis_force_ctrl/Sixaxis_force_Ctrl_omega_VSP2", 0, "",
    offsetof(B_button_switch_T, Sixaxis_force_Ctrl_omega_VSP2)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 28, 0 },

  { 15, "button_switch/Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_1", 0, "",
    offsetof(B_button_switch_T, Sixaxis_force_Ctrl_u_1)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "button_switch/Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_2", 0, "",
    offsetof(B_button_switch_T, Sixaxis_force_Ctrl_u_2)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "button_switch/Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_BT2", 0, "",
    offsetof(B_button_switch_T, Sixaxis_force_Ctrl_u_BT2)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "button_switch/Template_DP_ctrl/Ctrl_alpha_1", 0, "", offsetof
    (B_button_switch_T, Ctrl_alpha_1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 36,
    0 },

  { 19, "button_switch/Template_DP_ctrl/Ctrl_alpha_2", 0, "", offsetof
    (B_button_switch_T, Ctrl_alpha_2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 38,
    0 },

  { 20, "button_switch/Template_DP_ctrl/Ctrl_omega_VSP1", 0, "", offsetof
    (B_button_switch_T, Ctrl_omega_VSP1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    40, 0 },

  { 21, "button_switch/Template_DP_ctrl/Ctrl_omega_VSP2", 0, "", offsetof
    (B_button_switch_T, Ctrl_omega_VSP2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    42, 0 },

  { 22, "button_switch/Template_DP_ctrl/Ctrl_u_1", 0, "", offsetof
    (B_button_switch_T, Ctrl_u_1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 44, 0
  },

  { 23, "button_switch/Template_DP_ctrl/Ctrl_u_2", 0, "", offsetof
    (B_button_switch_T, Ctrl_u_2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 46, 0
  },

  { 24, "button_switch/Template_DP_ctrl/Ctrl_u_BT2", 0, "", offsetof
    (B_button_switch_T, Ctrl_u_BT2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 48,
    0 },

  { 25, "button_switch/Sixaxis_manual_thruster_ctlr/Sixaxis_alpha_1", 0, "",
    offsetof(B_button_switch_T, Sixaxis_alpha_1)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 50, 0 },

  { 26, "button_switch/Sixaxis_manual_thruster_ctlr/Sixaxis_alpha_2", 0, "",
    offsetof(B_button_switch_T, Sixaxis_alpha_2)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 52, 0 },

  { 27, "button_switch/Sixaxis_manual_thruster_ctlr/Sixaxis_omega_VSP", 0, "",
    offsetof(B_button_switch_T, Sixaxis_omega_VSP)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 54, 0 },

  { 28, "button_switch/Sixaxis_manual_thruster_ctlr/Sixaxis_u_1", 0, "",
    offsetof(B_button_switch_T, Sixaxis_u_1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 56, 0 },

  { 29, "button_switch/Sixaxis_manual_thruster_ctlr/Sixaxis_u_2", 0, "",
    offsetof(B_button_switch_T, Sixaxis_u_2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 58, 0 },

  { 30, "button_switch/Sixaxis_manual_thruster_ctlr/Sixaxis_u_BT", 0, "",
    offsetof(B_button_switch_T, Sixaxis_u_BT)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 60, 0 },

  { 31, "button_switch/Multiport Switch", 0, "(1,1)", offsetof(B_button_switch_T,
    MultiportSwitch)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 62, 0 },

  { 32, "button_switch/Multiport Switch", 0, "(1,2)", offsetof(B_button_switch_T,
    MultiportSwitch)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 64, 0 },

  { 33, "button_switch/Multiport Switch", 0, "(1,3)", offsetof(B_button_switch_T,
    MultiportSwitch)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 66, 0 },

  { 34, "button_switch/Multiport Switch", 0, "(1,4)", offsetof(B_button_switch_T,
    MultiportSwitch)+3*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 68, 0 },

  { 35, "button_switch/Multiport Switch", 0, "(1,5)", offsetof(B_button_switch_T,
    MultiportSwitch)+4*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 70, 0 },

  { 36, "button_switch/Multiport Switch", 0, "(1,6)", offsetof(B_button_switch_T,
    MultiportSwitch)+5*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 72, 0 },

  { 37, "button_switch/Multiport Switch", 0, "(1,7)", offsetof(B_button_switch_T,
    MultiportSwitch)+6*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 74, 0 },

  { 38, "button_switch/Switch_subsystem/Switch_function", 0, "switch_signal",
    offsetof(B_button_switch_T, switch_signal)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 76, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 39;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 39;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "Switch_Cross", 0, EXT_IN, 1, 1, 1 },

  { 1, "Switch_Square", 0, EXT_IN, 1, 1, 1 },

  { 2, "Switch_Circle", 0, EXT_IN, 1, 1, 1 },

  { 3, "Switch_Triangle", 0, EXT_IN, 1, 1, 1 },

  { 4, "Student_CTRL/Student_Ctrl_alpha_1", 0, EXT_IN, 1, 1, 1 },

  { 5, "Student_CTRL/Student_Ctrl_alpha_2", 0, EXT_IN, 1, 1, 1 },

  { 6, "Student_CTRL/Student_Ctrl_omega_VSP1", 0, EXT_IN, 1, 1, 1 },

  { 7, "Student_CTRL/Student_Ctrl_omega_VSP2", 0, EXT_IN, 1, 1, 1 },

  { 8, "Student_CTRL/Student_Ctrl_u_1", 0, EXT_IN, 1, 1, 1 },

  { 9, "Student_CTRL/Student_Ctrl_u_2", 0, EXT_IN, 1, 1, 1 },

  { 10, "Student_CTRL/Student_Ctrl_u_BT2", 0, EXT_IN, 1, 1, 1 },

  { 11, "Sixaxis_force_ctrl/Sixaxis_force_Ctrl_alpha_1", 0, EXT_IN, 1, 1, 1 },

  { 12, "Sixaxis_force_ctrl/Sixaxis_force_Ctrl_alpha_2", 0, EXT_IN, 1, 1, 1 },

  { 13, "Sixaxis_force_ctrl/Sixaxis_force_Ctrl_omega_VSP1", 0, EXT_IN, 1, 1, 1 },

  { 14, "Sixaxis_force_ctrl/Sixaxis_force_Ctrl_omega_VSP2", 0, EXT_IN, 1, 1, 1 },

  { 15, "Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_1", 0, EXT_IN, 1, 1, 1 },

  { 16, "Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_2", 0, EXT_IN, 1, 1, 1 },

  { 17, "Sixaxis_force_ctrl/Sixaxis_force_Ctrl_u_BT2", 0, EXT_IN, 1, 1, 1 },

  { 18, "Template_DP_ctrl/Ctrl_alpha_1", 0, EXT_IN, 1, 1, 1 },

  { 19, "Template_DP_ctrl/Ctrl_alpha_2", 0, EXT_IN, 1, 1, 1 },

  { 20, "Template_DP_ctrl/Ctrl_omega_VSP1", 0, EXT_IN, 1, 1, 1 },

  { 21, "Template_DP_ctrl/Ctrl_omega_VSP2", 0, EXT_IN, 1, 1, 1 },

  { 22, "Template_DP_ctrl/Ctrl_u_1", 0, EXT_IN, 1, 1, 1 },

  { 23, "Template_DP_ctrl/Ctrl_u_2", 0, EXT_IN, 1, 1, 1 },

  { 24, "Template_DP_ctrl/Ctrl_u_BT2", 0, EXT_IN, 1, 1, 1 },

  { 25, "Sixaxis_manual_thruster_ctlr/Sixaxis_alpha_1", 0, EXT_IN, 1, 1, 1 },

  { 26, "Sixaxis_manual_thruster_ctlr/Sixaxis_alpha_2", 0, EXT_IN, 1, 1, 1 },

  { 27, "Sixaxis_manual_thruster_ctlr/Sixaxis_omega_VSP", 0, EXT_IN, 1, 1, 1 },

  { 28, "Sixaxis_manual_thruster_ctlr/Sixaxis_u_1", 0, EXT_IN, 1, 1, 1 },

  { 29, "Sixaxis_manual_thruster_ctlr/Sixaxis_u_2", 0, EXT_IN, 1, 1, 1 },

  { 30, "Sixaxis_manual_thruster_ctlr/Sixaxis_u_BT", 0, EXT_IN, 1, 1, 1 },

  { 0, "U_BT", 0, EXT_OUT, 1, 1, 1 },

  { 1, "alpha_1", 0, EXT_OUT, 1, 1, 1 },

  { 2, "u_1", 0, EXT_OUT, 1, 1, 1 },

  { 3, "alpha_2", 0, EXT_OUT, 1, 1, 1 },

  { 4, "u_2", 0, EXT_OUT, 1, 1, 1 },

  { 5, "omega_VSP_1", 0, EXT_OUT, 1, 1, 1 },

  { 6, "omega_VSP_2", 0, EXT_OUT, 1, 1, 1 },

  { 7, "Switch_indicator", 0, EXT_OUT, 1, 1, 1 },

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
  "button_switch";
static char* NI_CompiledModelVersion = "1.11";
static char* NI_CompiledModelDateTime = "Tue Feb 03 14:35:05 2015";
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
   The undef allows us to access the real button_switch_P
   In the rest of the code button_switch_P is redefine to be the read-side
   of rtParameter.
 */
#undef button_switch_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &button_switch_P, sizeof(P_button_switch_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka button_switch_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_button_switch_T));
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
             (P_button_switch_T));
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
               (P_button_switch_T));

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
           (P_button_switch_T));
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
           (P_button_switch_T));
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
           (P_button_switch_T));
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
      *numDiscStates = 586;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Switch_Cross_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Switch_Cross_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Memory_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Memory_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Switch_Square_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Switch_Square_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Switch_Circle_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Switch_Circle_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Switch_Triangle_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Switch_Triangle_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Student_Ctrl_alpha_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Student_Ctrl_alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Student_Ctrl_alpha_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Student_Ctrl_alpha_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Student_Ctrl_omega_VSP1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Student_Ctrl_omega_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Student_Ctrl_omega_VSP2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Student_Ctrl_omega_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Student_Ctrl_u_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Student_Ctrl_u_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Student_Ctrl_u_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Student_Ctrl_u_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Student_Ctrl_u_BT2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Student_Ctrl_u_BT2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_force_Ctrl_alpha_1_DWOR, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_force_Ctrl_alpha_1_DWOR");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_force_Ctrl_alpha_2_DWOR, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_force_Ctrl_alpha_2_DWOR");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP1_D, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP1_D");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP2_D, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP2_D");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_force_Ctrl_u_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_force_Ctrl_u_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_force_Ctrl_u_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_force_Ctrl_u_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_force_Ctrl_u_BT2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_force_Ctrl_u_BT2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Ctrl_alpha_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Ctrl_alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Ctrl_alpha_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Ctrl_alpha_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Ctrl_omega_VSP1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Ctrl_omega_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Ctrl_omega_VSP2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Ctrl_omega_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.Ctrl_u_1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.Ctrl_u_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.Ctrl_u_2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.Ctrl_u_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Ctrl_u_BT2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Ctrl_u_BT2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_alpha_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_alpha_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_alpha_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_omega_VSP_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_omega_VSP_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_u_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_u_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_u_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_u_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Sixaxis_u_BT_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Sixaxis_u_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.U_BT_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.U_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.alpha_1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.u_1_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.u_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.alpha_2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.alpha_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.u_2_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.u_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.omega_VSP_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.omega_VSP_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.omega_VSP_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.omega_VSP_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&button_switch_DW.Switch_indicator_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&button_switch_DW.Switch_indicator_DWORK1");
    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Switch_Cross_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Switch_Cross_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Switch_Square_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Switch_Square_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Switch_Circle_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Switch_Circle_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Switch_Triangle_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Switch_Triangle_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Student_Ctrl_alpha_1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Student_Ctrl_alpha_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Student_Ctrl_alpha_2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Student_Ctrl_alpha_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Student_Ctrl_omega_VSP1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Student_Ctrl_omega_VSP1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Student_Ctrl_omega_VSP2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Student_Ctrl_omega_VSP2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Student_Ctrl_u_1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Student_Ctrl_u_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Student_Ctrl_u_2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Student_Ctrl_u_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Student_Ctrl_u_BT2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Student_Ctrl_u_BT2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_force_Ctrl_alpha_1_DW_e, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_force_Ctrl_alpha_1_DW_e");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_force_Ctrl_alpha_2_DW_l, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_force_Ctrl_alpha_2_DW_l");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP1_o, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP1_o");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP2_l, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP2_l");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_force_Ctrl_u_1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_force_Ctrl_u_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_force_Ctrl_u_2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_force_Ctrl_u_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_force_Ctrl_u_BT2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_force_Ctrl_u_BT2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Ctrl_alpha_1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Ctrl_alpha_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Ctrl_alpha_2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Ctrl_alpha_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Ctrl_omega_VSP1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Ctrl_omega_VSP1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Ctrl_omega_VSP2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Ctrl_omega_VSP2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Ctrl_u_1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Ctrl_u_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Ctrl_u_2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Ctrl_u_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Ctrl_u_BT2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Ctrl_u_BT2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_alpha_1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_alpha_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_alpha_2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_alpha_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_omega_VSP_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_omega_VSP_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_u_1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_u_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_u_2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_u_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Sixaxis_u_BT_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Sixaxis_u_BT_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.U_BT_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.U_BT_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.alpha_1_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.alpha_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.u_1_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.u_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.alpha_2_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.alpha_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&button_switch_DW.u_2_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&button_switch_DW.u_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.omega_VSP_1_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.omega_VSP_1_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.omega_VSP_2_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.omega_VSP_2_DWORK2");
    }

    for (count = 0; count < 14; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&button_switch_DW.Switch_indicator_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&button_switch_DW.Switch_indicator_DWORK2");
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
    NIRT_SetValueByDataType(&button_switch_DW.Switch_Cross_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Memory_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Switch_Square_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Switch_Circle_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Switch_Triangle_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_alpha_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_alpha_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_omega_VSP1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_omega_VSP2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_u_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_u_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_u_BT2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_alpha_1_DWOR, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_alpha_2_DWOR, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP1_D, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP2_D, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_u_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_u_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_u_BT2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Ctrl_alpha_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Ctrl_alpha_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Ctrl_omega_VSP1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Ctrl_omega_VSP2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Ctrl_u_1_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Ctrl_u_2_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Ctrl_u_BT2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_alpha_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_alpha_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_omega_VSP_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_u_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_u_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_u_BT_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.U_BT_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.alpha_1_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.u_1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.alpha_2_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.u_2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.omega_VSP_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.omega_VSP_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&button_switch_DW.Switch_indicator_DWORK1, 0,
      discStates[idx++], 0, 0);
    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Switch_Cross_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Switch_Square_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Switch_Circle_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Switch_Triangle_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_alpha_1_DWORK2,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_alpha_2_DWORK2,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_omega_VSP1_DWORK2,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_omega_VSP2_DWORK2,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_u_1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_u_2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Student_Ctrl_u_BT2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_alpha_1_DW_e,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_alpha_2_DW_l,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP1_o,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_omega_VSP2_l,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_u_1_DWORK2,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_u_2_DWORK2,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_force_Ctrl_u_BT2_DWORK2,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Ctrl_alpha_1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Ctrl_alpha_2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Ctrl_omega_VSP1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Ctrl_omega_VSP2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Ctrl_u_1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Ctrl_u_2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Ctrl_u_BT2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_alpha_1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_alpha_2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_omega_VSP_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_u_1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_u_2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Sixaxis_u_BT_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.U_BT_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.alpha_1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.u_1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.alpha_2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.u_2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.omega_VSP_1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.omega_VSP_2_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 14; count++) {
      NIRT_SetValueByDataType(&button_switch_DW.Switch_indicator_DWORK2, count,
        discStates[idx++], 18, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_button_switch
