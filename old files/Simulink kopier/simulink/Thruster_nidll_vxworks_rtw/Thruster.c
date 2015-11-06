/*
 * Thruster.c
 *
 * Real-Time Workshop code generation for Simulink model "Thruster.mdl".
 *
 * Model Version              : 1.8
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 15:31:19 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Thruster.h"
#include "Thruster_private.h"

/* Block signals (auto storage) */
BlockIO_Thruster Thruster_B;

/* Block states (auto storage) */
D_Work_Thruster Thruster_DWork;

/* Real-time model */
RT_MODEL_Thruster Thruster_M_;
RT_MODEL_Thruster *Thruster_M = &Thruster_M_;

/* Model output function */
static void Thruster_output(int_T tid)
{
  {
    int32_T i;
    real_T tmp;

    /* Gain: '<S4>/ScalingLY' incorporates:
     *  Constant: '<S4>/AS_LY'
     */
    Thruster_B.ypositionofleftanalogstick11 = Thruster_P.ScalingLY_Gain *
      Thruster_P.AS_LY_Value;

    /* Gain: '<S5>/PS3 u_1' */
    Thruster_B.u_1 = Thruster_P.PS3u_1_Gain *
      Thruster_B.ypositionofleftanalogstick11;

    /* Gain: '<S4>/ScalingLX' incorporates:
     *  Constant: '<S4>/AS_LX'
     */
    Thruster_B.xpositionofleftanalogstick11 = Thruster_P.ScalingLX_Gain *
      Thruster_P.AS_LX_Value;

    /* Gain: '<S5>/PS3 u_2' */
    Thruster_B.u_2 = Thruster_P.PS3u_2_Gain *
      Thruster_B.xpositionofleftanalogstick11;

    /* Gain: '<S4>/ScalingRY' incorporates:
     *  Constant: '<S4>/AS_RY'
     */
    Thruster_B.ypositionofrightanalogstick11 = Thruster_P.ScalingRY_Gain *
      Thruster_P.AS_RY_Value;

    /* Gain: '<S5>/PS3 u_3' */
    Thruster_B.u_3 = Thruster_P.PS3u_3_Gain *
      Thruster_B.ypositionofrightanalogstick11;

    /* Gain: '<S4>/Scaling_RX' incorporates:
     *  Constant: '<S4>/AS_RX'
     */
    Thruster_B.xpositionofrightanalogstick11 = Thruster_P.Scaling_RX_Gain *
      Thruster_P.AS_RX_Value;

    /* Gain: '<S5>/PS3 u_4' */
    Thruster_B.u_4 = Thruster_P.PS3u_4_Gain *
      Thruster_B.xpositionofrightanalogstick11;

    /* Sum: '<S5>/Add' incorporates:
     *  Constant: '<S4>/L2'
     *  Constant: '<S4>/R2'
     */
    Thruster_B.BowThrusterdirection = Thruster_P.L2_Value + Thruster_P.R2_Value;

    /* Gain: '<S5>/PS3 u_5' */
    Thruster_B.u_5 = Thruster_P.PS3u_5_Gain * Thruster_B.BowThrusterdirection;

    /* Gain: '<S6>/LabVIEW u_1' incorporates:
     *  Constant: '<S6>/u1'
     */
    Thruster_B.LabVIEWu_1 = Thruster_P.LabVIEWu_1_Gain * Thruster_P.u1_Value;

    /* Gain: '<S6>/LabVIEW u_2' incorporates:
     *  Constant: '<S6>/u2'
     */
    Thruster_B.LabVIEWu_2 = Thruster_P.LabVIEWu_2_Gain * Thruster_P.u2_Value;

    /* Gain: '<S6>/LabVIEW u_3' incorporates:
     *  Constant: '<S6>/u3'
     */
    Thruster_B.LabVIEWu_3 = Thruster_P.LabVIEWu_3_Gain * Thruster_P.u3_Value;

    /* Gain: '<S6>/LabVIEW u_4' incorporates:
     *  Constant: '<S6>/u4'
     */
    Thruster_B.LabVIEWu_4 = Thruster_P.LabVIEWu_4_Gain * Thruster_P.u4_Value;

    /* Gain: '<S6>/LabVIEW u_5' incorporates:
     *  Constant: '<S6>/u5'
     */
    Thruster_B.LabVIEWu_5 = Thruster_P.LabVIEWu_5_Gain * Thruster_P.u5_Value;

    /* MultiPortSwitch: '<S1>/Thruster setting Switch' incorporates:
     *  Constant: '<S1>/Control Mode'
     *  Constant: '<S4>/PS3_BT_Power'
     *  Constant: '<S4>/PS3_VSP_Speed'
     *  Constant: '<S6>/BT power'
     *  Constant: '<S6>/VSP speed'
     */
    if ((int32_T)Thruster_P.ControlMode_Value == 0) {
      Thruster_B.ThrustersettingSwitch[0] = Thruster_B.u_1;
      Thruster_B.ThrustersettingSwitch[1] = Thruster_B.u_2;
      Thruster_B.ThrustersettingSwitch[2] = Thruster_B.u_3;
      Thruster_B.ThrustersettingSwitch[3] = Thruster_B.u_4;
      Thruster_B.ThrustersettingSwitch[4] = Thruster_B.u_5;
      Thruster_B.ThrustersettingSwitch[5] = Thruster_P.PS3_BT_Power_Value;
      Thruster_B.ThrustersettingSwitch[6] = Thruster_P.PS3_VSP_Speed_Value;
    } else {
      Thruster_B.ThrustersettingSwitch[0] = Thruster_B.LabVIEWu_1;
      Thruster_B.ThrustersettingSwitch[1] = Thruster_B.LabVIEWu_2;
      Thruster_B.ThrustersettingSwitch[2] = Thruster_B.LabVIEWu_3;
      Thruster_B.ThrustersettingSwitch[3] = Thruster_B.LabVIEWu_4;
      Thruster_B.ThrustersettingSwitch[4] = Thruster_B.LabVIEWu_5;
      Thruster_B.ThrustersettingSwitch[5] = Thruster_P.BTpower_Value;
      Thruster_B.ThrustersettingSwitch[6] = Thruster_P.VSPspeed_Value;
    }

    /* Saturate: '<S1>/Saturation' */
    for (i = 0; i < 7; i++) {
      tmp = Thruster_B.ThrustersettingSwitch[i];
      Thruster_B.Saturation[i] = rt_SATURATE(tmp, Thruster_P.Saturation_LowerSat,
        Thruster_P.Saturation_UpperSat);
    }

    /* Gain: '<S3>/plant u_1' */
    Thruster_B.plantu_1 = Thruster_P.plantu_1_Gain * Thruster_B.Saturation[0];

    /* Gain: '<S3>/plant u_2' */
    Thruster_B.plantu_2 = Thruster_P.plantu_2_Gain * Thruster_B.Saturation[1];

    /* Gain: '<S3>/plant u_3' */
    Thruster_B.plantu_3 = Thruster_P.plantu_3_Gain * Thruster_B.Saturation[2];

    /* Gain: '<S3>/plant u_4' */
    Thruster_B.plantu_4 = Thruster_P.plantu_4_Gain * Thruster_B.Saturation[3];

    /* Gain: '<S3>/plant u_5' */
    Thruster_B.plantu_5 = Thruster_P.plantu_5_Gain * Thruster_B.Saturation[4];

    /* Gain: '<S3>/plant BT power' */
    Thruster_B.plantBTpower = Thruster_P.plantBTpower_Gain *
      Thruster_B.Saturation[5];

    /* Gain: '<S3>/plant VSP speed' */
    Thruster_B.plantVSPspeed = Thruster_P.plantVSPspeed_Gain *
      Thruster_B.Saturation[6];

    /* Outputs for enable SubSystem: '<S3>/CSE1' incorporates:
     *  Constant: '<S3>/Enable CSE1'
     *  EnablePort: '<S7>/Enable'
     */
    if (Thruster_P.EnableCSE1_Value > 0.0) {
      /* Gain: '<S8>/BT_D_Gain1' */
      Thruster_B.BT_D_Gain1 = Thruster_P.BT_D_Gain1_Gain * Thruster_B.plantu_5;

      /* Gain: '<S8>/BT_D_Gain2' */
      Thruster_B.BT_D_Gain2 = Thruster_P.BT_D_Gain2_Gain * Thruster_B.plantu_5;

      /* Sum: '<S8>/Add' incorporates:
       *  Constant: '<S8>/BT_Power_Offset1'
       */
      Thruster_B.Add = (Thruster_B.BT_D_Gain1 +
                        Thruster_P.BT_Power_Offset1_Value) +
        Thruster_B.BT_D_Gain2;

      /* Gain: '<S8>/BT_L_Gain1' */
      Thruster_B.BT_L_Gain1 = Thruster_P.BT_L_Gain1_Gain *
        Thruster_B.plantBTpower;

      /* Gain: '<S8>/BT_L_Gain2' */
      Thruster_B.BT_L_Gain2 = Thruster_P.BT_L_Gain2_Gain *
        Thruster_B.plantBTpower;

      /* Gain: '<S8>/Neg' */
      Thruster_B.Neg = Thruster_P.Neg_Gain * Thruster_B.plantBTpower;

      /* Sum: '<S8>/Sum1' incorporates:
       *  Constant: '<S8>/BT_Power_Offset2'
       */
      Thruster_B.Sum1 = Thruster_B.BT_L_Gain1 +
        Thruster_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S10>/LowerRelop1' */
      Thruster_B.LowerRelop1 = (Thruster_B.Add > Thruster_B.Sum1);

      /* Sum: '<S8>/Sum2' incorporates:
       *  Constant: '<S8>/BT_Power_Offset3'
       */
      Thruster_B.Sum2 = Thruster_B.BT_L_Gain2 +
        Thruster_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S10>/UpperRelop' */
      Thruster_B.UpperRelop = (Thruster_B.Add < Thruster_B.Sum2);

      /* Switch: '<S10>/Switch' */
      if (Thruster_B.UpperRelop) {
        Thruster_B.Switch = Thruster_B.Sum2;
      } else {
        Thruster_B.Switch = Thruster_B.Add;
      }

      /* Switch: '<S10>/Switch2' */
      if (Thruster_B.LowerRelop1) {
        Thruster_B.Switch2 = Thruster_B.Sum1;
      } else {
        Thruster_B.Switch2 = Thruster_B.Switch;
      }

      /* RelationalOperator: '<S11>/LowerRelop1' incorporates:
       *  Constant: '<S8>/Constant'
       */
      Thruster_B.LowerRelop1_j = (Thruster_B.plantu_5 >
        Thruster_P.Constant_Value);

      /* RelationalOperator: '<S11>/UpperRelop' */
      Thruster_B.UpperRelop_a = (Thruster_B.plantu_5 < Thruster_B.Neg);

      /* Switch: '<S11>/Switch' */
      if (Thruster_B.UpperRelop_a) {
        Thruster_B.Switch_g = Thruster_B.Neg;
      } else {
        Thruster_B.Switch_g = Thruster_B.plantu_5;
      }

      /* Switch: '<S11>/Switch2' incorporates:
       *  Constant: '<S8>/Constant'
       */
      if (Thruster_B.LowerRelop1_j) {
        Thruster_B.Switch2_b = Thruster_P.Constant_Value;
      } else {
        Thruster_B.Switch2_b = Thruster_B.Switch_g;
      }

      /* RelationalOperator: '<S12>/LowerRelop1' */
      Thruster_B.LowerRelop1_c = (Thruster_B.plantu_5 > Thruster_B.plantBTpower);

      /* RelationalOperator: '<S12>/UpperRelop' incorporates:
       *  Constant: '<S8>/Constant1'
       */
      Thruster_B.UpperRelop_h = (Thruster_B.plantu_5 <
        Thruster_P.Constant1_Value);

      /* Switch: '<S12>/Switch' incorporates:
       *  Constant: '<S8>/Constant1'
       */
      if (Thruster_B.UpperRelop_h) {
        Thruster_B.Switch_k = Thruster_P.Constant1_Value;
      } else {
        Thruster_B.Switch_k = Thruster_B.plantu_5;
      }

      /* Switch: '<S12>/Switch2' */
      if (Thruster_B.LowerRelop1_c) {
        Thruster_B.Switch2_p = Thruster_B.plantBTpower;
      } else {
        Thruster_B.Switch2_p = Thruster_B.Switch_k;
      }

      /* Signum: '<S9>/Sign' */
      Thruster_B.Sign = rt_SIGNd_snf(Thruster_B.plantVSPspeed);

      /* Product: '<S9>/Product1' */
      Thruster_B.PortVPS_X = Thruster_B.plantu_2 * Thruster_B.Sign;

      /* Gain: '<S9>/-x' */
      Thruster_B.PortVPS_X_g = Thruster_P.x_Gain * Thruster_B.PortVPS_X;

      /* Product: '<S9>/Product2' */
      Thruster_B.PortVSP_Y = Thruster_B.plantu_1 * Thruster_B.Sign;

      /* Gain: '<S9>/-y' */
      Thruster_B.PortVSP_Y_l = Thruster_P.y_Gain * Thruster_B.PortVSP_Y;

      /* Product: '<S9>/Product3' */
      Thruster_B.StarboardVSP_X = Thruster_B.plantu_4 * Thruster_B.Sign;

      /* Product: '<S9>/Product4' */
      Thruster_B.StarboardVSP_Y = Thruster_B.plantu_3 * Thruster_B.Sign;

      /* Lookup2D: '<S9>/Servo1' */
      Thruster_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&Thruster_P.Servo1_RowIdx[0]), 3, (const real_T *)
        (&Thruster_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&Thruster_P.Servo1_Table[0]), (const real_T)Thruster_B.PortVPS_X_g, (
        const real_T)Thruster_B.PortVSP_Y_l);

      /* Lookup2D: '<S9>/Servo2' */
      Thruster_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&Thruster_P.Servo2_RowIdx[0]), 3, (const real_T *)
        (&Thruster_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&Thruster_P.Servo2_Table[0]), (const real_T)Thruster_B.PortVPS_X_g, (
        const real_T)Thruster_B.PortVSP_Y_l);

      /* Lookup2D: '<S9>/Servo3' */
      Thruster_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&Thruster_P.Servo3_RowIdx[0]), 3, (const real_T *)
        (&Thruster_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&Thruster_P.Servo3_Table[0]), (const real_T)Thruster_B.StarboardVSP_X,
        (const real_T)Thruster_B.StarboardVSP_Y);

      /* Lookup2D: '<S9>/Servo4' */
      Thruster_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&Thruster_P.Servo4_RowIdx[0]), 3, (const real_T *)
        (&Thruster_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&Thruster_P.Servo4_Table[0]), (const real_T)Thruster_B.StarboardVSP_X,
        (const real_T)Thruster_B.StarboardVSP_Y);

      /* Gain: '<S9>/VPS_Speed_Gain' */
      Thruster_B.VPS_Speed_Gain = Thruster_P.VPS_Speed_Gain_Gain *
        Thruster_B.plantVSPspeed;

      /* Sum: '<S9>/Sum' incorporates:
       *  Constant: '<S9>/VPS_Power_Offset'
       */
      Thruster_B.Sum = Thruster_B.VPS_Speed_Gain +
        Thruster_P.VPS_Power_Offset_Value;

      /* Gain: '<S9>/VSPS Port' */
      Thruster_B.VSPSPort = Thruster_P.VSPSPort_Gain * Thruster_B.Sum;

      /* Gain: '<S9>/VSPS Starboard' */
      Thruster_B.VSPSStarboard = Thruster_P.VSPSStarboard_Gain * Thruster_B.Sum;
    }

    /* end of Outputs for SubSystem: '<S3>/CSE1' */

    /* Gain: '<S2>/Battery Bow Thruster' */
    Thruster_B.BatteryBowThruster = Thruster_P.BatteryBowThruster_Gain *
      Thruster_B.SITzAI0;

    /* Gain: '<S2>/Battery Servo' */
    Thruster_B.BatteryServo = Thruster_P.BatteryServo_Gain * Thruster_B.SITzAI1;

    /* Gain: '<S2>/Battery Main' */
    Thruster_B.BatteryMain = Thruster_P.BatteryMain_Gain * Thruster_B.SITzAI2;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
static void Thruster_update(int_T tid)
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
  if (!(++Thruster_M->Timing.clockTick0))
    ++Thruster_M->Timing.clockTickH0;
  Thruster_M->Timing.t[0] = Thruster_M->Timing.clockTick0 *
    Thruster_M->Timing.stepSize0 + Thruster_M->Timing.clockTickH0 *
    Thruster_M->Timing.stepSize0 * 4294967296.0;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void Thruster_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Thruster_M,0,
                sizeof(RT_MODEL_Thruster));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Thruster_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Thruster_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Thruster_M->Timing.sampleTimes = (&Thruster_M->Timing.sampleTimesArray[0]);
    Thruster_M->Timing.offsetTimes = (&Thruster_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Thruster_M->Timing.sampleTimes[0] = (0.1);

    /* task offsets */
    Thruster_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Thruster_M, &Thruster_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Thruster_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Thruster_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Thruster_M, -1);
  Thruster_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    Thruster_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(Thruster_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Thruster_M->rtwLogInfo, (NULL));
    rtliSetLogT(Thruster_M->rtwLogInfo, "");
    rtliSetLogX(Thruster_M->rtwLogInfo, "");
    rtliSetLogXFinal(Thruster_M->rtwLogInfo, "");
    rtliSetSigLog(Thruster_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Thruster_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Thruster_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Thruster_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Thruster_M->rtwLogInfo, 1);
    rtliSetLogY(Thruster_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Thruster_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Thruster_M->rtwLogInfo, (NULL));
  }

  Thruster_M->solverInfoPtr = (&Thruster_M->solverInfo);
  Thruster_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&Thruster_M->solverInfo, 0.1);
  rtsiSetSolverMode(&Thruster_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Thruster_M->ModelData.blockIO = ((void *) &Thruster_B);
  (void) memset(((void *) &Thruster_B),0,
                sizeof(BlockIO_Thruster));

  /* parameters */
  Thruster_M->ModelData.defaultParam = ((real_T *) &Thruster_P);

  /* states (dwork) */
  Thruster_M->Work.dwork = ((void *) &Thruster_DWork);
  (void) memset((void *)&Thruster_DWork, 0,
                sizeof(D_Work_Thruster));
}

/* Model terminate function */
void Thruster_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Thruster_output(tid);
}

void MdlUpdate(int_T tid)
{
  Thruster_update(tid);
}

void MdlInitializeSizes(void)
{
  Thruster_M->Sizes.numContStates = (0);/* Number of continuous states */
  Thruster_M->Sizes.numY = (0);        /* Number of model outputs */
  Thruster_M->Sizes.numU = (0);        /* Number of model inputs */
  Thruster_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Thruster_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Thruster_M->Sizes.numBlocks = (103); /* Number of blocks */
  Thruster_M->Sizes.numBlockIO = (65); /* Number of block outputs */
  Thruster_M->Sizes.numBlockPrms = (180);/* Sum of parameter "widths" */
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

RT_MODEL_Thruster *Thruster(void)
{
  Thruster_initialize(1);
  return Thruster_M;
}

void MdlTerminate(void)
{
  Thruster_terminate();
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
#ifdef NI_ROOTMODEL_Thruster
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
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 20:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 21:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 21:
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
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern Thruster_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // HMI/SIT zAI0
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Thruster_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Thruster_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&Thruster_B.SITzAI2, 0, data[index++], 0, 0);
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
    ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Switch2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.VSPSStarboard,0,0,0);
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
  ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Switch2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Servo1,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Servo2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Servo3,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.Servo4,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.VSPSPort,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&Thruster_B.VSPSStarboard,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "thruster/Control Systems/Control Mode/Value", offsetof
    (Parameters_Thruster, ControlMode_Value), 25, 1, 2, 0, "", 0 },

  { 1, "thruster/Control Systems/PS3 input/AS_LY/Value", offsetof
    (Parameters_Thruster, AS_LY_Value), 25, 1, 2, 2, "", 0 },

  { 2, "thruster/Control Systems/PS3 input/ScalingLY/Gain", offsetof
    (Parameters_Thruster, ScalingLY_Gain), 25, 1, 2, 4, "", 0 },

  { 3, "thruster/Control Systems/PS3 u input control/PS3 u_1/Gain", offsetof
    (Parameters_Thruster, PS3u_1_Gain), 25, 1, 2, 6, "", 0 },

  { 4, "thruster/Control Systems/PS3 input/AS_LX/Value", offsetof
    (Parameters_Thruster, AS_LX_Value), 25, 1, 2, 8, "", 0 },

  { 5, "thruster/Control Systems/PS3 input/ScalingLX/Gain", offsetof
    (Parameters_Thruster, ScalingLX_Gain), 25, 1, 2, 10, "", 0 },

  { 6, "thruster/Control Systems/PS3 u input control/PS3 u_2/Gain", offsetof
    (Parameters_Thruster, PS3u_2_Gain), 25, 1, 2, 12, "", 0 },

  { 7, "thruster/Control Systems/PS3 input/AS_RY/Value", offsetof
    (Parameters_Thruster, AS_RY_Value), 25, 1, 2, 14, "", 0 },

  { 8, "thruster/Control Systems/PS3 input/ScalingRY/Gain", offsetof
    (Parameters_Thruster, ScalingRY_Gain), 25, 1, 2, 16, "", 0 },

  { 9, "thruster/Control Systems/PS3 u input control/PS3 u_3/Gain", offsetof
    (Parameters_Thruster, PS3u_3_Gain), 25, 1, 2, 18, "", 0 },

  { 10, "thruster/Control Systems/PS3 input/AS_RX/Value", offsetof
    (Parameters_Thruster, AS_RX_Value), 25, 1, 2, 20, "", 0 },

  { 11, "thruster/Control Systems/PS3 input/Scaling_RX/Gain", offsetof
    (Parameters_Thruster, Scaling_RX_Gain), 25, 1, 2, 22, "", 0 },

  { 12, "thruster/Control Systems/PS3 u input control/PS3 u_4/Gain", offsetof
    (Parameters_Thruster, PS3u_4_Gain), 25, 1, 2, 24, "", 0 },

  { 13, "thruster/Control Systems/PS3 input/L2/Value", offsetof
    (Parameters_Thruster, L2_Value), 25, 1, 2, 26, "", 0 },

  { 14, "thruster/Control Systems/PS3 input/R2/Value", offsetof
    (Parameters_Thruster, R2_Value), 25, 1, 2, 28, "", 0 },

  { 15, "thruster/Control Systems/PS3 u input control/PS3 u_5/Gain", offsetof
    (Parameters_Thruster, PS3u_5_Gain), 25, 1, 2, 30, "", 0 },

  { 16, "thruster/Control Systems/PS3 input/PS3_BT_Power/Value", offsetof
    (Parameters_Thruster, PS3_BT_Power_Value), 25, 1, 2, 32, "", 0 },

  { 17, "thruster/Control Systems/PS3 input/PS3_VSP_Speed/Value", offsetof
    (Parameters_Thruster, PS3_VSP_Speed_Value), 25, 1, 2, 34, "", 0 },

  { 18, "thruster/Control Systems/Precision control/u1/Value", offsetof
    (Parameters_Thruster, u1_Value), 25, 1, 2, 36, "", 0 },

  { 19, "thruster/Control Systems/Precision control/LabVIEW u_1/Gain", offsetof
    (Parameters_Thruster, LabVIEWu_1_Gain), 25, 1, 2, 38, "", 0 },

  { 20, "thruster/Control Systems/Precision control/u2/Value", offsetof
    (Parameters_Thruster, u2_Value), 25, 1, 2, 40, "", 0 },

  { 21, "thruster/Control Systems/Precision control/LabVIEW u_2/Gain", offsetof
    (Parameters_Thruster, LabVIEWu_2_Gain), 25, 1, 2, 42, "", 0 },

  { 22, "thruster/Control Systems/Precision control/u3/Value", offsetof
    (Parameters_Thruster, u3_Value), 25, 1, 2, 44, "", 0 },

  { 23, "thruster/Control Systems/Precision control/LabVIEW u_3/Gain", offsetof
    (Parameters_Thruster, LabVIEWu_3_Gain), 25, 1, 2, 46, "", 0 },

  { 24, "thruster/Control Systems/Precision control/u4/Value", offsetof
    (Parameters_Thruster, u4_Value), 25, 1, 2, 48, "", 0 },

  { 25, "thruster/Control Systems/Precision control/LabVIEW u_4/Gain", offsetof
    (Parameters_Thruster, LabVIEWu_4_Gain), 25, 1, 2, 50, "", 0 },

  { 26, "thruster/Control Systems/Precision control/u5/Value", offsetof
    (Parameters_Thruster, u5_Value), 25, 1, 2, 52, "", 0 },

  { 27, "thruster/Control Systems/Precision control/LabVIEW u_5/Gain", offsetof
    (Parameters_Thruster, LabVIEWu_5_Gain), 25, 1, 2, 54, "", 0 },

  { 28, "thruster/Control Systems/Precision control/BT power/Value", offsetof
    (Parameters_Thruster, BTpower_Value), 25, 1, 2, 56, "", 0 },

  { 29, "thruster/Control Systems/Precision control/VSP speed/Value", offsetof
    (Parameters_Thruster, VSPspeed_Value), 25, 1, 2, 58, "", 0 },

  { 30, "thruster/Control Systems/Saturation/UpperLimit", offsetof
    (Parameters_Thruster, Saturation_UpperSat), 25, 1, 2, 60, "", 0 },

  { 31, "thruster/Control Systems/Saturation/LowerLimit", offsetof
    (Parameters_Thruster, Saturation_LowerSat), 25, 1, 2, 62, "", 0 },

  { 32, "thruster/Plants/plant u_1/Gain", offsetof(Parameters_Thruster,
    plantu_1_Gain), 25, 1, 2, 64, "", 0 },

  { 33, "thruster/Plants/plant u_2/Gain", offsetof(Parameters_Thruster,
    plantu_2_Gain), 25, 1, 2, 66, "", 0 },

  { 34, "thruster/Plants/plant u_3/Gain", offsetof(Parameters_Thruster,
    plantu_3_Gain), 25, 1, 2, 68, "", 0 },

  { 35, "thruster/Plants/plant u_4/Gain", offsetof(Parameters_Thruster,
    plantu_4_Gain), 25, 1, 2, 70, "", 0 },

  { 36, "thruster/Plants/plant u_5/Gain", offsetof(Parameters_Thruster,
    plantu_5_Gain), 25, 1, 2, 72, "", 0 },

  { 37, "thruster/Plants/plant BT power/Gain", offsetof(Parameters_Thruster,
    plantBTpower_Gain), 25, 1, 2, 74, "", 0 },

  { 38, "thruster/Plants/plant VSP speed/Gain", offsetof(Parameters_Thruster,
    plantVSPspeed_Gain), 25, 1, 2, 76, "", 0 },

  { 39, "thruster/Plants/Enable CSE1/Value", offsetof(Parameters_Thruster,
    EnableCSE1_Value), 25, 1, 2, 78, "", 0 },

  { 40, "thruster/HMI/Battery Bow Thruster/Gain", offsetof(Parameters_Thruster,
    BatteryBowThruster_Gain), 25, 1, 2, 80, "", 0 },

  { 41, "thruster/HMI/Battery Servo/Gain", offsetof(Parameters_Thruster,
    BatteryServo_Gain), 25, 1, 2, 82, "", 0 },

  { 42, "thruster/HMI/Battery Main/Gain", offsetof(Parameters_Thruster,
    BatteryMain_Gain), 25, 1, 2, 84, "", 0 },

  { 43, "thruster/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain", offsetof
    (Parameters_Thruster, BT_D_Gain1_Gain), 25, 1, 2, 86, "", 0 },

  { 44, "thruster/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value", offsetof
    (Parameters_Thruster, BT_Power_Offset1_Value), 25, 1, 2, 88, "", 0 },

  { 45, "thruster/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain", offsetof
    (Parameters_Thruster, BT_D_Gain2_Gain), 25, 1, 2, 90, "", 0 },

  { 46, "thruster/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain", offsetof
    (Parameters_Thruster, BT_L_Gain1_Gain), 25, 1, 2, 92, "", 0 },

  { 47, "thruster/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain", offsetof
    (Parameters_Thruster, BT_L_Gain2_Gain), 25, 1, 2, 94, "", 0 },

  { 48, "thruster/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value", offsetof
    (Parameters_Thruster, BT_Power_Offset2_Value), 25, 1, 2, 96, "", 0 },

  { 49, "thruster/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value", offsetof
    (Parameters_Thruster, BT_Power_Offset3_Value), 25, 1, 2, 98, "", 0 },

  { 50, "thruster/Plants/CSE1/Bow Thruster/Constant/Value", offsetof
    (Parameters_Thruster, Constant_Value), 25, 1, 2, 100, "", 0 },

  { 51, "thruster/Plants/CSE1/Bow Thruster/Constant1/Value", offsetof
    (Parameters_Thruster, Constant1_Value), 25, 1, 2, 102, "", 0 },

  { 52, "thruster/Plants/CSE1/Bow Thruster/Neg/Gain", offsetof
    (Parameters_Thruster, Neg_Gain), 25, 1, 2, 104, "", 0 },

  { 53, "thruster/Plants/CSE1/Voith Schneider Propeller /-x/Gain", offsetof
    (Parameters_Thruster, x_Gain), 25, 1, 2, 106, "", 0 },

  { 54, "thruster/Plants/CSE1/Voith Schneider Propeller /-y/Gain", offsetof
    (Parameters_Thruster, y_Gain), 25, 1, 2, 108, "", 0 },

  { 55, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_Thruster, Servo1_RowIdx), 26, 3, 2, 110, "", 0 },

  { 56, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_Thruster, Servo1_ColIdx), 26, 3, 2, 112, "", 0 },

  { 57, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo1/Table", offsetof
    (Parameters_Thruster, Servo1_Table), 27, 9, 2, 114, "", 0 },

  { 58, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_Thruster, Servo2_RowIdx), 26, 3, 2, 116, "", 0 },

  { 59, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_Thruster, Servo2_ColIdx), 26, 3, 2, 118, "", 0 },

  { 60, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo2/Table", offsetof
    (Parameters_Thruster, Servo2_Table), 27, 9, 2, 120, "", 0 },

  { 61, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_Thruster, Servo3_RowIdx), 26, 3, 2, 122, "", 0 },

  { 62, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_Thruster, Servo3_ColIdx), 26, 3, 2, 124, "", 0 },

  { 63, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo3/Table", offsetof
    (Parameters_Thruster, Servo3_Table), 27, 9, 2, 126, "", 0 },

  { 64, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_Thruster, Servo4_RowIdx), 26, 3, 2, 128, "", 0 },

  { 65, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_Thruster, Servo4_ColIdx), 26, 3, 2, 130, "", 0 },

  { 66, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo4/Table", offsetof
    (Parameters_Thruster, Servo4_Table), 27, 9, 2, 132, "", 0 },

  { 67, "thruster/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_Thruster, VPS_Speed_Gain_Gain), 25, 1, 2, 134, "", 0 },

  { 68, "thruster/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_Thruster, VPS_Power_Offset_Value), 25, 1, 2, 136, "", 0
  },

  { 69, "thruster/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain",
    offsetof(Parameters_Thruster, VSPSPort_Gain), 25, 1, 2, 138, "", 0 },

  { 70, "thruster/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_Thruster, VSPSStarboard_Gain), 25, 1, 2, 140, "", 0 },
};

static int NI_ParamListSize = 71;
static int NI_ParamDimList[] = {
  1, 1,                                /* thruster/Control Systems/Control Mode/Value */
  1, 1,                                /* thruster/Control Systems/PS3 input/AS_LY/Value */
  1, 1,                                /* thruster/Control Systems/PS3 input/ScalingLY/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 u input control/PS3 u_1/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 input/AS_LX/Value */
  1, 1,                                /* thruster/Control Systems/PS3 input/ScalingLX/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 u input control/PS3 u_2/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 input/AS_RY/Value */
  1, 1,                                /* thruster/Control Systems/PS3 input/ScalingRY/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 u input control/PS3 u_3/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 input/AS_RX/Value */
  1, 1,                                /* thruster/Control Systems/PS3 input/Scaling_RX/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 u input control/PS3 u_4/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 input/L2/Value */
  1, 1,                                /* thruster/Control Systems/PS3 input/R2/Value */
  1, 1,                                /* thruster/Control Systems/PS3 u input control/PS3 u_5/Gain */
  1, 1,                                /* thruster/Control Systems/PS3 input/PS3_BT_Power/Value */
  1, 1,                                /* thruster/Control Systems/PS3 input/PS3_VSP_Speed/Value */
  1, 1,                                /* thruster/Control Systems/Precision control/u1/Value */
  1, 1,                                /* thruster/Control Systems/Precision control/LabVIEW u_1/Gain */
  1, 1,                                /* thruster/Control Systems/Precision control/u2/Value */
  1, 1,                                /* thruster/Control Systems/Precision control/LabVIEW u_2/Gain */
  1, 1,                                /* thruster/Control Systems/Precision control/u3/Value */
  1, 1,                                /* thruster/Control Systems/Precision control/LabVIEW u_3/Gain */
  1, 1,                                /* thruster/Control Systems/Precision control/u4/Value */
  1, 1,                                /* thruster/Control Systems/Precision control/LabVIEW u_4/Gain */
  1, 1,                                /* thruster/Control Systems/Precision control/u5/Value */
  1, 1,                                /* thruster/Control Systems/Precision control/LabVIEW u_5/Gain */
  1, 1,                                /* thruster/Control Systems/Precision control/BT power/Value */
  1, 1,                                /* thruster/Control Systems/Precision control/VSP speed/Value */
  1, 1,                                /* thruster/Control Systems/Saturation/UpperLimit */
  1, 1,                                /* thruster/Control Systems/Saturation/LowerLimit */
  1, 1,                                /* thruster/Plants/plant u_1/Gain */
  1, 1,                                /* thruster/Plants/plant u_2/Gain */
  1, 1,                                /* thruster/Plants/plant u_3/Gain */
  1, 1,                                /* thruster/Plants/plant u_4/Gain */
  1, 1,                                /* thruster/Plants/plant u_5/Gain */
  1, 1,                                /* thruster/Plants/plant BT power/Gain */
  1, 1,                                /* thruster/Plants/plant VSP speed/Gain */
  1, 1,                                /* thruster/Plants/Enable CSE1/Value */
  1, 1,                                /* thruster/HMI/Battery Bow Thruster/Gain */
  1, 1,                                /* thruster/HMI/Battery Servo/Gain */
  1, 1,                                /* thruster/HMI/Battery Main/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/Constant/Value */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/Constant1/Value */
  1, 1,                                /* thruster/Plants/CSE1/Bow Thruster/Neg/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* thruster/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 65;
static NI_Signal NI_SigList[] = {
  { 0, "thruster/Control Systems/PS3 input/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_Thruster,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "thruster/Control Systems/PS3 u input control/PS3 u_1", 0, "u_1",
    offsetof(BlockIO_Thruster, u_1), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "thruster/Control Systems/PS3 input/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_Thruster,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "thruster/Control Systems/PS3 u input control/PS3 u_2", 0, "u_2",
    offsetof(BlockIO_Thruster, u_2), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "thruster/Control Systems/PS3 input/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_Thruster,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "thruster/Control Systems/PS3 u input control/PS3 u_3", 0, "u_3",
    offsetof(BlockIO_Thruster, u_3), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "thruster/Control Systems/PS3 input/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_Thruster,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "thruster/Control Systems/PS3 u input control/PS3 u_4", 0, "u_4",
    offsetof(BlockIO_Thruster, u_4), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "thruster/Control Systems/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_Thruster, BowThrusterdirection),
    BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "thruster/Control Systems/PS3 u input control/PS3 u_5", 0, "u_5",
    offsetof(BlockIO_Thruster, u_5), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "thruster/Control Systems/Precision control/LabVIEW u_1", 0, "",
    offsetof(BlockIO_Thruster, LabVIEWu_1), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "thruster/Control Systems/Precision control/LabVIEW u_2", 0, "",
    offsetof(BlockIO_Thruster, LabVIEWu_2), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "thruster/Control Systems/Precision control/LabVIEW u_3", 0, "",
    offsetof(BlockIO_Thruster, LabVIEWu_3), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "thruster/Control Systems/Precision control/LabVIEW u_4", 0, "",
    offsetof(BlockIO_Thruster, LabVIEWu_4), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "thruster/Control Systems/Precision control/LabVIEW u_5", 0, "",
    offsetof(BlockIO_Thruster, LabVIEWu_5), BLOCKIO_SIG, 0, 1, 2, 28, 0 },

  { 15, "thruster/Control Systems/Thruster setting Switch", 0, "", offsetof
    (BlockIO_Thruster, ThrustersettingSwitch), BLOCKIO_SIG, 17, 7, 2, 30, 0 },

  { 16, "thruster/Control Systems/Saturation", 0, "", offsetof(BlockIO_Thruster,
    Saturation), BLOCKIO_SIG, 17, 7, 2, 32, 0 },

  { 17, "thruster/Plants/plant u_1", 0, "", offsetof(BlockIO_Thruster, plantu_1),
    BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "thruster/Plants/plant u_2", 0, "", offsetof(BlockIO_Thruster, plantu_2),
    BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "thruster/Plants/plant u_3", 0, "", offsetof(BlockIO_Thruster, plantu_3),
    BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "thruster/Plants/plant u_4", 0, "", offsetof(BlockIO_Thruster, plantu_4),
    BLOCKIO_SIG, 0, 1, 2, 40, 0 },

  { 21, "thruster/Plants/plant u_5", 0, "", offsetof(BlockIO_Thruster, plantu_5),
    BLOCKIO_SIG, 0, 1, 2, 42, 0 },

  { 22, "thruster/Plants/plant BT power", 0, "", offsetof(BlockIO_Thruster,
    plantBTpower), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { 23, "thruster/Plants/plant VSP speed", 0, "", offsetof(BlockIO_Thruster,
    plantVSPspeed), BLOCKIO_SIG, 0, 1, 2, 46, 0 },

  { 24, "thruster/HMI/SIT zAI0", 0, "", offsetof(BlockIO_Thruster, SITzAI0),
    BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25, "thruster/HMI/Battery Bow Thruster", 0, "", offsetof(BlockIO_Thruster,
    BatteryBowThruster), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26, "thruster/HMI/SIT zAI1", 0, "", offsetof(BlockIO_Thruster, SITzAI1),
    BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27, "thruster/HMI/Battery Servo", 0, "", offsetof(BlockIO_Thruster,
    BatteryServo), BLOCKIO_SIG, 0, 1, 2, 54, 0 },

  { 28, "thruster/HMI/SIT zAI2", 0, "", offsetof(BlockIO_Thruster, SITzAI2),
    BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29, "thruster/HMI/Battery Main", 0, "", offsetof(BlockIO_Thruster,
    BatteryMain), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30, "thruster/Plants/CSE1/Bow Thruster/BT_D_Gain1", 0, "", offsetof
    (BlockIO_Thruster, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31, "thruster/Plants/CSE1/Bow Thruster/BT_D_Gain2", 0, "", offsetof
    (BlockIO_Thruster, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32, "thruster/Plants/CSE1/Bow Thruster/Add", 0, "", offsetof
    (BlockIO_Thruster, Add), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33, "thruster/Plants/CSE1/Bow Thruster/BT_L_Gain1", 0, "", offsetof
    (BlockIO_Thruster, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2, 66, 0 },

  { 34, "thruster/Plants/CSE1/Bow Thruster/BT_L_Gain2", 0, "", offsetof
    (BlockIO_Thruster, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35, "thruster/Plants/CSE1/Bow Thruster/Neg", 0, "", offsetof
    (BlockIO_Thruster, Neg), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36, "thruster/Plants/CSE1/Bow Thruster/Sum1", 0, "", offsetof
    (BlockIO_Thruster, Sum1), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37, "thruster/Plants/CSE1/Bow Thruster/Sum2", 0, "", offsetof
    (BlockIO_Thruster, Sum2), BLOCKIO_SIG, 0, 1, 2, 74, 0 },

  { 38, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch", 0, "",
    offsetof(BlockIO_Thruster, Switch), BLOCKIO_SIG, 0, 1, 2, 76, 0 },

  { 39, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch2", 0, "",
    offsetof(BlockIO_Thruster, Switch2), BLOCKIO_SIG, 0, 1, 2, 78, 0 },

  { 40, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch", 0, "",
    offsetof(BlockIO_Thruster, Switch_g), BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch2", 0, "",
    offsetof(BlockIO_Thruster, Switch2_b), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch", 0, "",
    offsetof(BlockIO_Thruster, Switch_k), BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch2", 0, "",
    offsetof(BlockIO_Thruster, Switch2_p), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44, "thruster/Plants/CSE1/Voith Schneider Propeller /Sign", 0, "", offsetof
    (BlockIO_Thruster, Sign), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "thruster/Plants/CSE1/Voith Schneider Propeller /Product1", 0,
    "Port VPS_X", offsetof(BlockIO_Thruster, PortVPS_X), BLOCKIO_SIG, 0, 1, 2,
    90, 0 },

  { 46, "thruster/Plants/CSE1/Voith Schneider Propeller /-x", 0, "Port VPS_X",
    offsetof(BlockIO_Thruster, PortVPS_X_g), BLOCKIO_SIG, 0, 1, 2, 92, 0 },

  { 47, "thruster/Plants/CSE1/Voith Schneider Propeller /Product2", 0,
    "Port VSP_Y", offsetof(BlockIO_Thruster, PortVSP_Y), BLOCKIO_SIG, 0, 1, 2,
    94, 0 },

  { 48, "thruster/Plants/CSE1/Voith Schneider Propeller /-y", 0, "Port VSP_Y",
    offsetof(BlockIO_Thruster, PortVSP_Y_l), BLOCKIO_SIG, 0, 1, 2, 96, 0 },

  { 49, "thruster/Plants/CSE1/Voith Schneider Propeller /Product3", 0,
    "Starboard VSP_X", offsetof(BlockIO_Thruster, StarboardVSP_X), BLOCKIO_SIG,
    0, 1, 2, 98, 0 },

  { 50, "thruster/Plants/CSE1/Voith Schneider Propeller /Product4", 0,
    "Starboard VSP_Y", offsetof(BlockIO_Thruster, StarboardVSP_Y), BLOCKIO_SIG,
    0, 1, 2, 100, 0 },

  { 51, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo1", 0, "",
    offsetof(BlockIO_Thruster, Servo1), BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo2", 0, "",
    offsetof(BlockIO_Thruster, Servo2), BLOCKIO_SIG, 0, 1, 2, 104, 0 },

  { 53, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo3", 0, "",
    offsetof(BlockIO_Thruster, Servo3), BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "thruster/Plants/CSE1/Voith Schneider Propeller /Servo4", 0, "",
    offsetof(BlockIO_Thruster, Servo4), BLOCKIO_SIG, 0, 1, 2, 108, 0 },

  { 55, "thruster/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain", 0, "",
    offsetof(BlockIO_Thruster, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2, 110, 0 },

  { 56, "thruster/Plants/CSE1/Voith Schneider Propeller /Sum", 0, "", offsetof
    (BlockIO_Thruster, Sum), BLOCKIO_SIG, 0, 1, 2, 112, 0 },

  { 57, "thruster/Plants/CSE1/Voith Schneider Propeller /VSPS Port", 0, "",
    offsetof(BlockIO_Thruster, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 114, 0 },

  { 58, "thruster/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard", 0, "",
    offsetof(BlockIO_Thruster, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2, 116, 0 },

  { 59, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic/LowerRelop1", 0,
    "", offsetof(BlockIO_Thruster, LowerRelop1), BLOCKIO_SIG, 8, 1, 2, 118, 0 },

  { 60, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic/UpperRelop", 0, "",
    offsetof(BlockIO_Thruster, UpperRelop), BLOCKIO_SIG, 8, 1, 2, 120, 0 },

  { 61, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic1/LowerRelop1", 0,
    "", offsetof(BlockIO_Thruster, LowerRelop1_j), BLOCKIO_SIG, 8, 1, 2, 122, 0
  },

  { 62, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic1/UpperRelop", 0,
    "", offsetof(BlockIO_Thruster, UpperRelop_a), BLOCKIO_SIG, 8, 1, 2, 124, 0 },

  { 63, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic2/LowerRelop1", 0,
    "", offsetof(BlockIO_Thruster, LowerRelop1_c), BLOCKIO_SIG, 8, 1, 2, 126, 0
  },

  { 64, "thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic2/UpperRelop", 0,
    "", offsetof(BlockIO_Thruster, UpperRelop_h), BLOCKIO_SIG, 8, 1, 2, 128, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 7, 1, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

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

static char* NI_CompiledModelName = "thruster";
static char* NI_CompiledModelVersion = "1.8";
static char* NI_CompiledModelDateTime = "Sun Mar 16 15:31:19 2014";

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
   The undef allows us to access the real Thruster_P
   In the rest of the code Thruster_P is redefine to be the read-side
   of rtParameter.
 */
#undef Thruster_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &Thruster_P, sizeof(Parameters_Thruster));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka Thruster_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_Thruster));
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
             (Parameters_Thruster));

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
           (Parameters_Thruster));
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

#endif                                 // of NI_ROOTMODEL_Thruster
