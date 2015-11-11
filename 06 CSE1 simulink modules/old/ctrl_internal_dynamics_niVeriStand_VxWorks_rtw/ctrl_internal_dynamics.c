/*
 * ctrl_internal_dynamics.c
 *
 * Code generation for model "ctrl_internal_dynamics".
 *
 * Model version              : 1.148
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 25 09:52:00 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ctrl_internal_dynamics.h"
#include "ctrl_internal_dynamics_private.h"

/* Block signals (auto storage) */
B_ctrl_internal_dynamics_T ctrl_internal_dynamics_B;

/* Block states (auto storage) */
DW_ctrl_internal_dynamics_T ctrl_internal_dynamics_DW;

/* Real-time model */
RT_MODEL_ctrl_internal_dynami_T ctrl_internal_dynamics_M_;
RT_MODEL_ctrl_internal_dynami_T *const ctrl_internal_dynamics_M =
  &ctrl_internal_dynamics_M_;

/*
 * Output and update for atomic system:
 *    '<S1>/diag2x2'
 *    '<S4>/diag2x2'
 */
void ctrl_internal_dynamics_diag2x2(real_T rtu_u, real_T rtu_u_j,
  B_diag2x2_ctrl_internal_dynam_T *localB)
{
  /* MATLAB Function 'Derivative_ gain/diag2x2': '<S5>:1' */
  /* '<S5>:1:4' */
  localB->y[0] = 0.0;
  localB->y[1] = 0.0;
  localB->y[2] = 0.0;
  localB->y[3] = 0.0;

  /* SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport1' */
  localB->y[0] = rtu_u;
  localB->y[3] = rtu_u_j;
}

/* Model output function */
static void ctrl_internal_dynamics_output(void)
{
  real_T a1;
  real_T a2;
  real_T s;
  real_T s_dot;
  real_T R2[4];
  real_T rtb_Memory1;
  real_T rtb_Memory2;
  real_T rtb_Memory6;
  real_T rtb_Memory3;
  real_T rtb_Memory4;
  real_T rtb_Memory5;
  real_T rtb_Memory15;
  real_T R2_0[4];
  int32_T i;
  real_T R2_1[4];

  /* Memory: '<Root>/Memory1' */
  rtb_Memory1 = ctrl_internal_dynamics_DW.Memory1_PreviousInput;

  /* Memory: '<Root>/Memory2' */
  rtb_Memory2 = ctrl_internal_dynamics_DW.Memory2_PreviousInput;

  /* Memory: '<Root>/Memory6' */
  rtb_Memory6 = ctrl_internal_dynamics_DW.Memory6_PreviousInput;

  /* Memory: '<Root>/Memory3' */
  rtb_Memory3 = ctrl_internal_dynamics_DW.Memory3_PreviousInput;

  /* Memory: '<Root>/Memory4' */
  rtb_Memory4 = ctrl_internal_dynamics_DW.Memory4_PreviousInput;

  /* Memory: '<Root>/Memory5' */
  rtb_Memory5 = ctrl_internal_dynamics_DW.Memory5_PreviousInput;

  /* Memory: '<Root>/Memory10' */
  ctrl_internal_dynamics_B.Memory10 =
    ctrl_internal_dynamics_DW.Memory10_PreviousInput;

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  if ((ctrl_internal_dynamics_B.Memory10 > 0.0) &&
      (ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_DSTATE =
      ctrl_internal_dynamics_P.DiscreteTimeIntegrator_IC;
  }

  /* MATLAB Function: '<Root>/Guidance' incorporates:
   *  Constant: '<Root>/timwe1'
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   *  Memory: '<Root>/Memory11'
   *  Memory: '<Root>/Memory12'
   *  Memory: '<Root>/Memory13'
   *  Memory: '<Root>/Memory7'
   *  Memory: '<Root>/Memory8'
   *  Sum: '<Root>/Sum'
   */
  /* MATLAB Function 'Guidance': '<S2>:1' */
  /* % Path parameters */
  /*  End corner */
  /* xc = 100; */
  /* yc = 10; */
  /*  Path coefficients */
  /* '<S2>:1:9' */
  /* '<S2>:1:10' */
  /* '<S2>:1:11' */
  a1 = ctrl_internal_dynamics_DW.Memory12_PreviousInput -
    ctrl_internal_dynamics_DW.Memory7_PreviousInput;

  /* '<S2>:1:12' */
  a2 = (ctrl_internal_dynamics_DW.Memory13_PreviousInput +
        ctrl_internal_dynamics_P.timwe1_Value) -
    ctrl_internal_dynamics_DW.Memory8_PreviousInput;

  /*  Path variable  */
  /* '<S2>:1:15' */
  s = ctrl_internal_dynamics_DW.Memory11_PreviousInput *
    ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_DSTATE / sqrt(a1 * a1 + a2 *
    a2);

  /* '<S2>:1:16' */
  s_dot = ctrl_internal_dynamics_DW.Memory11_PreviousInput / sqrt(a1 * a1 + a2 *
    a2);

  /* % Path signals */
  /* '<S2>:1:21' */
  ctrl_internal_dynamics_B.pd[0] = a1 * s +
    ctrl_internal_dynamics_DW.Memory7_PreviousInput;
  ctrl_internal_dynamics_B.pd[1] = a2 * s +
    ctrl_internal_dynamics_DW.Memory8_PreviousInput;

  /* Memory: '<Root>/Memory14' */
  /* '<S2>:1:23' */
  /* '<S2>:1:25' */
  s = ctrl_internal_dynamics_DW.Memory14_PreviousInput;

  /* Memory: '<Root>/Memory15' */
  rtb_Memory15 = ctrl_internal_dynamics_DW.Memory15_PreviousInput;

  /* MATLAB Function: '<S4>/diag2x2' */
  ctrl_internal_dynamics_diag2x2(ctrl_internal_dynamics_B.Ctrl_K_p_x,
    ctrl_internal_dynamics_B.Ctrl_K_p_y, &ctrl_internal_dynamics_B.sf_diag2x2);

  /* MATLAB Function: '<S1>/diag2x2' */
  ctrl_internal_dynamics_diag2x2(ctrl_internal_dynamics_B.Ctrl_K_d_x,
    ctrl_internal_dynamics_B.Ctrl_K_d_y, &ctrl_internal_dynamics_B.sf_diag2x2_c);

  /* MATLAB Function: '<Root>/PD+FL ctrl' incorporates:
   *  SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport2'
   *  SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport6'
   */
  /* MATLAB Function 'PD+FL ctrl': '<S3>:1' */
  /* % CS2 model parameters */
  /*  x_g  =  0.0460; % Table B.1 */
  /* % Added mass */
  /*  Table B.1 */
  /* % Total mass matrix */
  /* % Damping coefficients */
  /*  Comments at the end of the lines indicate the old values used. */
  /*  Y_r */
  /*  Y_rr */
  /*  Y_rv, Y_vr */
  /*  N_r */
  /*  N_rr */
  /*  N_rv, N_vr */
  /* % Correolis matrix */
  /* % Assembly of the damping matrix */
  /*  using abs(r) */
  /* % Assembly of the damping matrix */
  /*  using abs(r) */
  /* % Control law */
  /*  Signals and parameters */
  /* '<S3>:1:81' */
  /* '<S3>:1:82' */
  /* '<S3>:1:83' */
  /* '<S3>:1:84' */
  /* '<S3>:1:85' */
  /* p   = eta(1:2); */
  /* '<S3>:1:87' */
  /* '<S3>:1:88' */
  /* '<S3>:1:89' */
  /* ups = nu(1:2); */
  /* '<S3>:1:92' */
  R2[0] = cos(rtb_Memory5);
  R2[2] = -sin(rtb_Memory5);
  R2[1] = sin(rtb_Memory5);
  R2[3] = cos(rtb_Memory5);

  /* '<S3>:1:94' */
  /* '<S3>:1:97' */
  /* '<S3>:1:99' */
  rtb_Memory3 = ((R2[0] * s + R2[1] * rtb_Memory15) + rtb_Memory3) -
    ctrl_internal_dynamics_B.pd[0];
  rtb_Memory5 = ((R2[2] * s + R2[3] * rtb_Memory15) + rtb_Memory4) -
    ctrl_internal_dynamics_B.pd[1];
  ctrl_internal_dynamics_B.e1[0] = 0.0;
  ctrl_internal_dynamics_B.e1[0] += R2[0] * rtb_Memory3;
  ctrl_internal_dynamics_B.e1[0] += R2[1] * rtb_Memory5;
  ctrl_internal_dynamics_B.e1[1] = 0.0;
  ctrl_internal_dynamics_B.e1[1] += R2[2] * rtb_Memory3;
  ctrl_internal_dynamics_B.e1[1] += R2[3] * rtb_Memory5;

  /* MATLAB Function: '<Root>/Guidance' */
  /* '<S3>:1:100' */
  rtb_Memory3 = a1 * s_dot;
  rtb_Memory5 = a2 * s_dot;

  /* MATLAB Function: '<Root>/PD+FL ctrl' incorporates:
   *  SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport6'
   */
  for (i = 0; i < 2; i++) {
    R2_0[i] = 0.0;
    R2_0[i] += R2[i << 1] * 0.0;
    R2_0[i] += R2[(i << 1) + 1] * rtb_Memory6;
    R2_0[i + 2] = 0.0;
    R2_0[i + 2] += R2[i << 1] * -rtb_Memory6;
    R2_0[i + 2] += R2[(i << 1) + 1] * 0.0;
  }

  for (i = 0; i < 2; i++) {
    R2_1[i] = 0.0;
    R2_1[i] += R2_0[i] * R2[0];
    R2_1[i] += R2_0[i + 2] * R2[2];
    R2_1[i + 2] = 0.0;
    R2_1[i + 2] += R2_0[i] * R2[1];
    R2_1[i + 2] += R2_0[i + 2] * R2[3];
  }

  ctrl_internal_dynamics_B.e2[0] = (rtb_Memory1 - (R2[0] * rtb_Memory3 + R2[1] *
    rtb_Memory5)) - (R2_1[0] * s + R2_1[2] * rtb_Memory15);
  ctrl_internal_dynamics_B.e2[1] = (rtb_Memory2 - (R2[2] * rtb_Memory3 + R2[3] *
    rtb_Memory5)) - (R2_1[1] * s + R2_1[3] * rtb_Memory15);

  /*  A   = [zeros(2,2), eye(2); zeros(2,2) Av]; */
  /*  B   = [zeros(2,2); Bv]; */
  /*  Co = ctrb(A,B); */
  /*  rank(Co); */
  /*  Control gains */
  /* Kp  = 0.1*diag([1 1]); */
  /* Kd  = 0.05*diag([1 1]); */
  /*  Kpd = [Kp, Kd]; */
  /*  eig((A-B*Kpd)); */
  /*  P = lyap((A-B*Kpd)',eye(4)); */
  /*  Control law   */
  /*  tau_ups = -Kp*e1 - Kd*e2 - Bv\(Av*R2'*(pd_dot + S2*R2'*ly) - R2'*pd_ddot);  */
  /*  tau_ups = -Kp*e1-Kd*e2+Bv\(-Av*R2'*pd_dot-h*r-S2*R2'*pd_dot+R2'*pd_ddot); */
  /*  tau_ups = -Kp*e1-Kd*e2-Bv\(Av*R2'*pd_dot+R2'*pd_ddot); */
  /* '<S3>:1:131' */
  /* '<S3>:1:132' */
  ctrl_internal_dynamics_B.tau[0] = (-ctrl_internal_dynamics_B.sf_diag2x2.y[0] *
    ctrl_internal_dynamics_B.e1[0] + -ctrl_internal_dynamics_B.sf_diag2x2.y[2] *
    ctrl_internal_dynamics_B.e1[1]) - (ctrl_internal_dynamics_B.sf_diag2x2_c.y[0]
    * ctrl_internal_dynamics_B.e2[0] + ctrl_internal_dynamics_B.sf_diag2x2_c.y[2]
    * ctrl_internal_dynamics_B.e2[1]);
  ctrl_internal_dynamics_B.tau[1] = (-ctrl_internal_dynamics_B.sf_diag2x2.y[1] *
    ctrl_internal_dynamics_B.e1[0] + -ctrl_internal_dynamics_B.sf_diag2x2.y[3] *
    ctrl_internal_dynamics_B.e1[1]) - (ctrl_internal_dynamics_B.sf_diag2x2_c.y[1]
    * ctrl_internal_dynamics_B.e2[0] + ctrl_internal_dynamics_B.sf_diag2x2_c.y[3]
    * ctrl_internal_dynamics_B.e2[1]);
  ctrl_internal_dynamics_B.tau[2] = 0.0;
}

/* Model update function */
static void ctrl_internal_dynamics_update(void)
{
  /* Update for Memory: '<Root>/Memory1' */
  ctrl_internal_dynamics_DW.Memory1_PreviousInput =
    ctrl_internal_dynamics_B.HIL_nu_1_ctrl;

  /* Update for Memory: '<Root>/Memory2' */
  ctrl_internal_dynamics_DW.Memory2_PreviousInput =
    ctrl_internal_dynamics_B.HIL_nu_2_ctrl;

  /* Update for Memory: '<Root>/Memory6' */
  ctrl_internal_dynamics_DW.Memory6_PreviousInput =
    ctrl_internal_dynamics_B.HIL_nu_3_ctrl;

  /* Update for Memory: '<Root>/Memory3' */
  ctrl_internal_dynamics_DW.Memory3_PreviousInput =
    ctrl_internal_dynamics_B.HIL_eta_1_ctrl;

  /* Update for Memory: '<Root>/Memory4' */
  ctrl_internal_dynamics_DW.Memory4_PreviousInput =
    ctrl_internal_dynamics_B.HIL_eta_2_ctrl;

  /* Update for Memory: '<Root>/Memory5' */
  ctrl_internal_dynamics_DW.Memory5_PreviousInput =
    ctrl_internal_dynamics_B.HIL_eta_3_ctrl;

  /* Update for Memory: '<Root>/Memory10' */
  ctrl_internal_dynamics_DW.Memory10_PreviousInput =
    ctrl_internal_dynamics_B.HIL_reset_ctrl;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
   *  Constant: '<Root>/timwe'
   */
  ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_DSTATE +=
    ctrl_internal_dynamics_P.DiscreteTimeIntegrator_gainval *
    ctrl_internal_dynamics_P.timwe_Value;
  if (ctrl_internal_dynamics_B.Memory10 > 0.0) {
    ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese = 1;
  } else if (ctrl_internal_dynamics_B.Memory10 < 0.0) {
    ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese = -1;
  } else if (ctrl_internal_dynamics_B.Memory10 == 0.0) {
    ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese = 0;
  } else {
    ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese = 2;
  }

  /* End of Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */

  /* Update for Memory: '<Root>/Memory7' */
  ctrl_internal_dynamics_DW.Memory7_PreviousInput =
    ctrl_internal_dynamics_B.HIL_eta0_1_ctrl;

  /* Update for Memory: '<Root>/Memory8' */
  ctrl_internal_dynamics_DW.Memory8_PreviousInput =
    ctrl_internal_dynamics_B.HIL_eta0_2_ctrl;

  /* Update for Memory: '<Root>/Memory9' */
  ctrl_internal_dynamics_DW.Memory9_PreviousInput =
    ctrl_internal_dynamics_B.HIL_eta0_3_ctrl;

  /* Update for Memory: '<Root>/Memory11' */
  ctrl_internal_dynamics_DW.Memory11_PreviousInput =
    ctrl_internal_dynamics_B.HIL_u0;

  /* Update for Memory: '<Root>/Memory12' */
  ctrl_internal_dynamics_DW.Memory12_PreviousInput =
    ctrl_internal_dynamics_B.HIL_xc;

  /* Update for Memory: '<Root>/Memory13' */
  ctrl_internal_dynamics_DW.Memory13_PreviousInput =
    ctrl_internal_dynamics_B.HIL_yc;

  /* Update for Memory: '<Root>/Memory14' */
  ctrl_internal_dynamics_DW.Memory14_PreviousInput =
    ctrl_internal_dynamics_B.HIL_l_y1;

  /* Update for Memory: '<Root>/Memory15' */
  ctrl_internal_dynamics_DW.Memory15_PreviousInput =
    ctrl_internal_dynamics_B.HIL_l_y2;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ctrl_internal_dynamics_M->Timing.clockTick0)) {
    ++ctrl_internal_dynamics_M->Timing.clockTickH0;
  }

  ctrl_internal_dynamics_M->Timing.t[0] =
    ctrl_internal_dynamics_M->Timing.clockTick0 *
    ctrl_internal_dynamics_M->Timing.stepSize0 +
    ctrl_internal_dynamics_M->Timing.clockTickH0 *
    ctrl_internal_dynamics_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void ctrl_internal_dynamics_initialize(void)
{
  /* InitializeConditions for Memory: '<Root>/Memory1' */
  ctrl_internal_dynamics_DW.Memory1_PreviousInput =
    ctrl_internal_dynamics_P.Memory1_X0;

  /* InitializeConditions for Memory: '<Root>/Memory2' */
  ctrl_internal_dynamics_DW.Memory2_PreviousInput =
    ctrl_internal_dynamics_P.Memory2_X0;

  /* InitializeConditions for Memory: '<Root>/Memory6' */
  ctrl_internal_dynamics_DW.Memory6_PreviousInput =
    ctrl_internal_dynamics_P.Memory6_X0;

  /* InitializeConditions for Memory: '<Root>/Memory3' */
  ctrl_internal_dynamics_DW.Memory3_PreviousInput =
    ctrl_internal_dynamics_P.Memory3_X0;

  /* InitializeConditions for Memory: '<Root>/Memory4' */
  ctrl_internal_dynamics_DW.Memory4_PreviousInput =
    ctrl_internal_dynamics_P.Memory4_X0;

  /* InitializeConditions for Memory: '<Root>/Memory5' */
  ctrl_internal_dynamics_DW.Memory5_PreviousInput =
    ctrl_internal_dynamics_P.Memory5_X0;

  /* InitializeConditions for Memory: '<Root>/Memory10' */
  ctrl_internal_dynamics_DW.Memory10_PreviousInput =
    ctrl_internal_dynamics_P.Memory10_X0;

  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_DSTATE =
    ctrl_internal_dynamics_P.DiscreteTimeIntegrator_IC;
  ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese = 2;

  /* InitializeConditions for Memory: '<Root>/Memory7' */
  ctrl_internal_dynamics_DW.Memory7_PreviousInput =
    ctrl_internal_dynamics_P.Memory7_X0;

  /* InitializeConditions for Memory: '<Root>/Memory8' */
  ctrl_internal_dynamics_DW.Memory8_PreviousInput =
    ctrl_internal_dynamics_P.Memory8_X0;

  /* InitializeConditions for Memory: '<Root>/Memory9' */
  ctrl_internal_dynamics_DW.Memory9_PreviousInput =
    ctrl_internal_dynamics_P.Memory9_X0;

  /* InitializeConditions for Memory: '<Root>/Memory11' */
  ctrl_internal_dynamics_DW.Memory11_PreviousInput =
    ctrl_internal_dynamics_P.Memory11_X0;

  /* InitializeConditions for Memory: '<Root>/Memory12' */
  ctrl_internal_dynamics_DW.Memory12_PreviousInput =
    ctrl_internal_dynamics_P.Memory12_X0;

  /* InitializeConditions for Memory: '<Root>/Memory13' */
  ctrl_internal_dynamics_DW.Memory13_PreviousInput =
    ctrl_internal_dynamics_P.Memory13_X0;

  /* InitializeConditions for Memory: '<Root>/Memory14' */
  ctrl_internal_dynamics_DW.Memory14_PreviousInput =
    ctrl_internal_dynamics_P.Memory14_X0;

  /* InitializeConditions for Memory: '<Root>/Memory15' */
  ctrl_internal_dynamics_DW.Memory15_PreviousInput =
    ctrl_internal_dynamics_P.Memory15_X0;
}

/* Model terminate function */
void ctrl_internal_dynamics_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  ctrl_internal_dynamics_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  ctrl_internal_dynamics_update();
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
  ctrl_internal_dynamics_initialize();
}

void MdlTerminate(void)
{
  ctrl_internal_dynamics_terminate();
}

/* Registration function */
RT_MODEL_ctrl_internal_dynami_T *ctrl_internal_dynamics(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ctrl_internal_dynamics_M, 0,
                sizeof(RT_MODEL_ctrl_internal_dynami_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ctrl_internal_dynamics_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    ctrl_internal_dynamics_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ctrl_internal_dynamics_M->Timing.sampleTimes =
      (&ctrl_internal_dynamics_M->Timing.sampleTimesArray[0]);
    ctrl_internal_dynamics_M->Timing.offsetTimes =
      (&ctrl_internal_dynamics_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ctrl_internal_dynamics_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    ctrl_internal_dynamics_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(ctrl_internal_dynamics_M, &ctrl_internal_dynamics_M->Timing.tArray
             [0]);

  {
    int_T *mdlSampleHits = ctrl_internal_dynamics_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    ctrl_internal_dynamics_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ctrl_internal_dynamics_M, -1);
  ctrl_internal_dynamics_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    ctrl_internal_dynamics_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ctrl_internal_dynamics_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ctrl_internal_dynamics_M->rtwLogInfo, (NULL));
    rtliSetLogT(ctrl_internal_dynamics_M->rtwLogInfo, "tout");
    rtliSetLogX(ctrl_internal_dynamics_M->rtwLogInfo, "");
    rtliSetLogXFinal(ctrl_internal_dynamics_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ctrl_internal_dynamics_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ctrl_internal_dynamics_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(ctrl_internal_dynamics_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(ctrl_internal_dynamics_M->rtwLogInfo, 1);
    rtliSetLogY(ctrl_internal_dynamics_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(ctrl_internal_dynamics_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(ctrl_internal_dynamics_M->rtwLogInfo, (NULL));
  }

  ctrl_internal_dynamics_M->solverInfoPtr =
    (&ctrl_internal_dynamics_M->solverInfo);
  ctrl_internal_dynamics_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&ctrl_internal_dynamics_M->solverInfo, 0.01);
  rtsiSetSolverMode(&ctrl_internal_dynamics_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  ctrl_internal_dynamics_M->ModelData.blockIO = ((void *)
    &ctrl_internal_dynamics_B);
  (void) memset(((void *) &ctrl_internal_dynamics_B), 0,
                sizeof(B_ctrl_internal_dynamics_T));

  /* parameters */
  ctrl_internal_dynamics_M->ModelData.defaultParam = ((real_T *)
    &ctrl_internal_dynamics_P);

  /* states (dwork) */
  ctrl_internal_dynamics_M->ModelData.dwork = ((void *)
    &ctrl_internal_dynamics_DW);
  (void) memset((void *)&ctrl_internal_dynamics_DW, 0,
                sizeof(DW_ctrl_internal_dynamics_T));

  /* Initialize Sizes */
  ctrl_internal_dynamics_M->Sizes.numContStates = (0);/* Number of continuous states */
  ctrl_internal_dynamics_M->Sizes.numY = (0);/* Number of model outputs */
  ctrl_internal_dynamics_M->Sizes.numU = (0);/* Number of model inputs */
  ctrl_internal_dynamics_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  ctrl_internal_dynamics_M->Sizes.numSampTimes = (1);/* Number of sample times */
  ctrl_internal_dynamics_M->Sizes.numBlocks = (59);/* Number of blocks */
  ctrl_internal_dynamics_M->Sizes.numBlockIO = (26);/* Number of block outputs */
  ctrl_internal_dynamics_M->Sizes.numBlockPrms = (187);/* Sum of parameter "widths" */
  return ctrl_internal_dynamics_M;
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
#ifdef NI_ROOTMODEL_ctrl_internal_dynamics
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 20:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 23:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 18:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 23:
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

extern ctrl_internal_dynamics_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Proportional gain/Ctrl_K_p_x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.Ctrl_K_p_x, 0, data[index
      ++], 0, 0);
  } else {
    index += 1;
  }

  // Proportional gain/Ctrl_K_p_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.Ctrl_K_p_y, 0, data[index
      ++], 0, 0);
  } else {
    index += 1;
  }

  // Derivative_ gain/Ctrl_K_d_x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.Ctrl_K_d_x, 0, data[index
      ++], 0, 0);
  } else {
    index += 1;
  }

  // Derivative_ gain/Ctrl_K_d_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.Ctrl_K_d_y, 0, data[index
      ++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_eta0_1_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_eta0_1_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_eta0_2_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_eta0_2_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_eta0_3_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_eta0_3_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_u0
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_u0, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // HIL_l_y1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_l_y1, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // HIL_l_y2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_l_y2, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // HIL_reset_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_reset_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_xc
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_xc, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // HIL_yc
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_yc, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // HIL_eta_1_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_eta_1_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_eta_2_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_eta_2_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_eta_3_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_eta_3_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_nu_1_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_nu_1_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_nu_2_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_nu_2_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HIL_nu_3_ctrl
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_B.HIL_nu_3_ctrl, 0,
      data[index++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 19;
}

double ni_extout[9];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // HIL_e1_N: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.e1,0,
      17,0);
  } else {
    index += 1;
  }

  // HIL_e2_E: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.e1,1,
      17,0);
  } else {
    index += 1;
  }

  // HIL_e2_X: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.e2,0,
      17,0);
  } else {
    index += 1;
  }

  // HIL_e2_Y: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.e2,1,
      17,0);
  } else {
    index += 1;
  }

  // HIL_path_d_1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.pd,0,
      17,0);
  } else {
    index += 1;
  }

  // HIL_path_d_2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.pd,1,
      17,0);
  } else {
    index += 1;
  }

  // HIL_tau_r: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.tau,2,
      18,0);
  } else {
    index += 1;
  }

  // HIL_tau_u: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.tau,0,
      18,0);
  } else {
    index += 1;
  }

  // HIL_tau_v: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.tau,1,
      18,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 9;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // HIL_e1_N: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.e1,0,17,
    0);

  // HIL_e2_E: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.e1,1,17,
    0);

  // HIL_e2_X: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.e2,0,17,
    0);

  // HIL_e2_Y: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.e2,1,17,
    0);

  // HIL_path_d_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.pd,0,17,
    0);

  // HIL_path_d_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.pd,1,17,
    0);

  // HIL_tau_r: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.tau,2,
    18,0);

  // HIL_tau_u: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.tau,0,
    18,0);

  // HIL_tau_v: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_internal_dynamics_B.tau,1,
    18,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "ctrl_internal_dynamics/Memory1/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory1_X0), 28, 1, 2, 0, 0 },

  { 1, "ctrl_internal_dynamics/Memory2/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory2_X0), 28, 1, 2, 2, 0 },

  { 2, "ctrl_internal_dynamics/Memory6/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory6_X0), 28, 1, 2, 4, 0 },

  { 3, "ctrl_internal_dynamics/Memory3/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory3_X0), 28, 1, 2, 6, 0 },

  { 4, "ctrl_internal_dynamics/Memory4/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory4_X0), 28, 1, 2, 8, 0 },

  { 5, "ctrl_internal_dynamics/Memory5/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory5_X0), 28, 1, 2, 10, 0 },

  { 6, "ctrl_internal_dynamics/Memory10/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory10_X0), 28, 1, 2, 12, 0 },

  { 7, "ctrl_internal_dynamics/Discrete-Time Integrator/gainval", offsetof
    (P_ctrl_internal_dynamics_T, DiscreteTimeIntegrator_gainval), 0, 1, 2, 14, 0
  },

  { 8, "ctrl_internal_dynamics/Discrete-Time Integrator/InitialCondition",
    offsetof(P_ctrl_internal_dynamics_T, DiscreteTimeIntegrator_IC), 28, 1, 2,
    16, 0 },

  { 9, "ctrl_internal_dynamics/Memory7/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory7_X0), 28, 1, 2, 18, 0 },

  { 10, "ctrl_internal_dynamics/Memory8/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory8_X0), 28, 1, 2, 20, 0 },

  { 11, "ctrl_internal_dynamics/Memory9/X0", offsetof(P_ctrl_internal_dynamics_T,
    Memory9_X0), 28, 1, 2, 22, 0 },

  { 12, "ctrl_internal_dynamics/Memory11/X0", offsetof
    (P_ctrl_internal_dynamics_T, Memory11_X0), 28, 1, 2, 24, 0 },

  { 13, "ctrl_internal_dynamics/Memory12/X0", offsetof
    (P_ctrl_internal_dynamics_T, Memory12_X0), 28, 1, 2, 26, 0 },

  { 14, "ctrl_internal_dynamics/Memory13/X0", offsetof
    (P_ctrl_internal_dynamics_T, Memory13_X0), 28, 1, 2, 28, 0 },

  { 15, "ctrl_internal_dynamics/timwe1/Value", offsetof
    (P_ctrl_internal_dynamics_T, timwe1_Value), 28, 1, 2, 30, 0 },

  { 16, "ctrl_internal_dynamics/Memory14/X0", offsetof
    (P_ctrl_internal_dynamics_T, Memory14_X0), 28, 1, 2, 32, 0 },

  { 17, "ctrl_internal_dynamics/Memory15/X0", offsetof
    (P_ctrl_internal_dynamics_T, Memory15_X0), 28, 1, 2, 34, 0 },

  { 18, "ctrl_internal_dynamics/timwe/Value", offsetof
    (P_ctrl_internal_dynamics_T, timwe_Value), 28, 1, 2, 36, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 19;
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
  1, 1,                                /* Parameter at index 15 */
  1, 1,                                /* Parameter at index 16 */
  1, 1,                                /* Parameter at index 17 */
  1, 1,                                /* Parameter at index 18 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "ctrl_internal_dynamics/Memory10", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, Memory10)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 0, 0 },

  { 1, "ctrl_internal_dynamics/Proportional gain/Ctrl_K_p_x", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, Ctrl_K_p_x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 2, 0 },

  { 2, "ctrl_internal_dynamics/Proportional gain/Ctrl_K_p_y", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, Ctrl_K_p_y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 4, 0 },

  { 3, "ctrl_internal_dynamics/Derivative_ gain/Ctrl_K_d_x", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, Ctrl_K_d_x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 6, 0 },

  { 4, "ctrl_internal_dynamics/Derivative_ gain/Ctrl_K_d_y", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, Ctrl_K_d_y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 8, 0 },

  { 5, "ctrl_internal_dynamics/HIL_eta0_1_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_eta0_1_ctrl)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 10, 0 },

  { 6, "ctrl_internal_dynamics/HIL_eta0_2_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_eta0_2_ctrl)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 12, 0 },

  { 7, "ctrl_internal_dynamics/HIL_eta0_3_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_eta0_3_ctrl)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 14, 0 },

  { 8, "ctrl_internal_dynamics/HIL_u0", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_u0)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    16, 0 },

  { 9, "ctrl_internal_dynamics/HIL_l_y1", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_l_y1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 18, 0 },

  { 10, "ctrl_internal_dynamics/HIL_l_y2", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_l_y2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 20, 0 },

  { 11, "ctrl_internal_dynamics/HIL_reset_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_reset_ctrl)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 22, 0 },

  { 12, "ctrl_internal_dynamics/HIL_xc", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_xc)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    24, 0 },

  { 13, "ctrl_internal_dynamics/HIL_yc", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_yc)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    26, 0 },

  { 14, "ctrl_internal_dynamics/HIL_eta_1_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_eta_1_ctrl)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 28, 0 },

  { 15, "ctrl_internal_dynamics/HIL_eta_2_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_eta_2_ctrl)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 30, 0 },

  { 16, "ctrl_internal_dynamics/HIL_eta_3_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_eta_3_ctrl)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 32, 0 },

  { 17, "ctrl_internal_dynamics/HIL_nu_1_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_nu_1_ctrl)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 34, 0 },

  { 18, "ctrl_internal_dynamics/HIL_nu_2_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_nu_2_ctrl)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 36, 0 },

  { 19, "ctrl_internal_dynamics/HIL_nu_3_ctrl", 0, "", offsetof
    (B_ctrl_internal_dynamics_T, HIL_nu_3_ctrl)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 38, 0 },

  { 20, "ctrl_internal_dynamics/PD+FL ctrl", 0, "tau(1,1)", offsetof
    (B_ctrl_internal_dynamics_T, tau)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2,
    40, 0 },

  { 21, "ctrl_internal_dynamics/PD+FL ctrl", 0, "tau(1,2)", offsetof
    (B_ctrl_internal_dynamics_T, tau)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2,
    42, 0 },

  { 22, "ctrl_internal_dynamics/PD+FL ctrl", 0, "tau(1,3)", offsetof
    (B_ctrl_internal_dynamics_T, tau)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2,
    44, 0 },

  { 23, "ctrl_internal_dynamics/PD+FL ctrl", 1, "e1(1,1)", offsetof
    (B_ctrl_internal_dynamics_T, e1)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 46,
    0 },

  { 24, "ctrl_internal_dynamics/PD+FL ctrl", 1, "e1(1,2)", offsetof
    (B_ctrl_internal_dynamics_T, e1)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 48,
    0 },

  { 25, "ctrl_internal_dynamics/PD+FL ctrl", 2, "e2(1,1)", offsetof
    (B_ctrl_internal_dynamics_T, e2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 50,
    0 },

  { 26, "ctrl_internal_dynamics/PD+FL ctrl", 2, "e2(1,2)", offsetof
    (B_ctrl_internal_dynamics_T, e2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 52,
    0 },

  { 27, "ctrl_internal_dynamics/Guidance", 0, "pd(1,1)", offsetof
    (B_ctrl_internal_dynamics_T, pd)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 54,
    0 },

  { 28, "ctrl_internal_dynamics/Guidance", 0, "pd(1,2)", offsetof
    (B_ctrl_internal_dynamics_T, pd)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 56,
    0 },

  { 29, "ctrl_internal_dynamics/Proportional gain/diag2x2", 0, "y(1,1)",
    offsetof(B_ctrl_internal_dynamics_T, sf_diag2x2.y)+0*sizeof(real_T),
    BLOCKIO_SIG, 19, 1, 2, 58, 0 },

  { 30, "ctrl_internal_dynamics/Proportional gain/diag2x2", 0, "y(2,1)",
    offsetof(B_ctrl_internal_dynamics_T, sf_diag2x2.y)+1*sizeof(real_T),
    BLOCKIO_SIG, 19, 1, 2, 60, 0 },

  { 31, "ctrl_internal_dynamics/Proportional gain/diag2x2", 0, "y(1,2)",
    offsetof(B_ctrl_internal_dynamics_T, sf_diag2x2.y)+2*sizeof(real_T),
    BLOCKIO_SIG, 19, 1, 2, 62, 0 },

  { 32, "ctrl_internal_dynamics/Proportional gain/diag2x2", 0, "y(2,2)",
    offsetof(B_ctrl_internal_dynamics_T, sf_diag2x2.y)+3*sizeof(real_T),
    BLOCKIO_SIG, 19, 1, 2, 64, 0 },

  { 33, "ctrl_internal_dynamics/Derivative_ gain/diag2x2", 0, "y(1,1)", offsetof
    (B_ctrl_internal_dynamics_T, sf_diag2x2_c.y)+0*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 66, 0 },

  { 34, "ctrl_internal_dynamics/Derivative_ gain/diag2x2", 0, "y(2,1)", offsetof
    (B_ctrl_internal_dynamics_T, sf_diag2x2_c.y)+1*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 68, 0 },

  { 35, "ctrl_internal_dynamics/Derivative_ gain/diag2x2", 0, "y(1,2)", offsetof
    (B_ctrl_internal_dynamics_T, sf_diag2x2_c.y)+2*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 70, 0 },

  { 36, "ctrl_internal_dynamics/Derivative_ gain/diag2x2", 0, "y(2,2)", offsetof
    (B_ctrl_internal_dynamics_T, sf_diag2x2_c.y)+3*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 72, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 37;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 28;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "Proportional gain/Ctrl_K_p_x", 0, EXT_IN, 1, 1, 1 },

  { 1, "Proportional gain/Ctrl_K_p_y", 0, EXT_IN, 1, 1, 1 },

  { 2, "Derivative_ gain/Ctrl_K_d_x", 0, EXT_IN, 1, 1, 1 },

  { 3, "Derivative_ gain/Ctrl_K_d_y", 0, EXT_IN, 1, 1, 1 },

  { 4, "HIL_eta0_1_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 5, "HIL_eta0_2_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 6, "HIL_eta0_3_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 7, "HIL_u0", 0, EXT_IN, 1, 1, 1 },

  { 8, "HIL_l_y1", 0, EXT_IN, 1, 1, 1 },

  { 9, "HIL_l_y2", 0, EXT_IN, 1, 1, 1 },

  { 10, "HIL_reset_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 11, "HIL_xc", 0, EXT_IN, 1, 1, 1 },

  { 12, "HIL_yc", 0, EXT_IN, 1, 1, 1 },

  { 13, "HIL_eta_1_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 14, "HIL_eta_2_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 15, "HIL_eta_3_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 16, "HIL_nu_1_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 17, "HIL_nu_2_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 18, "HIL_nu_3_ctrl", 0, EXT_IN, 1, 1, 1 },

  { 0, "HIL_e1_N", 0, EXT_OUT, 1, 1, 1 },

  { 1, "HIL_e2_E", 0, EXT_OUT, 1, 1, 1 },

  { 2, "HIL_e2_X", 0, EXT_OUT, 1, 1, 1 },

  { 3, "HIL_e2_Y", 0, EXT_OUT, 1, 1, 1 },

  { 4, "HIL_path_d_1", 0, EXT_OUT, 1, 1, 1 },

  { 5, "HIL_path_d_2", 0, EXT_OUT, 1, 1, 1 },

  { 6, "HIL_tau_r", 0, EXT_OUT, 1, 1, 1 },

  { 7, "HIL_tau_u", 0, EXT_OUT, 1, 1, 1 },

  { 8, "HIL_tau_v", 0, EXT_OUT, 1, 1, 1 },

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
  "ctrl_internal_dynamics";
static char* NI_CompiledModelVersion = "1.148";
static char* NI_CompiledModelDateTime = "Wed Feb 25 09:52:00 2015";
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
   The undef allows us to access the real ctrl_internal_dynamics_P
   In the rest of the code ctrl_internal_dynamics_P is redefine to be the read-side
   of rtParameter.
 */
#undef ctrl_internal_dynamics_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &ctrl_internal_dynamics_P, sizeof
         (P_ctrl_internal_dynamics_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka ctrl_internal_dynamics_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_ctrl_internal_dynamics_T));
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
             (P_ctrl_internal_dynamics_T));
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
               (P_ctrl_internal_dynamics_T));

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
           (P_ctrl_internal_dynamics_T));
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
           (P_ctrl_internal_dynamics_T));
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
           (P_ctrl_internal_dynamics_T));
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
      *numDiscStates = 689;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_DSTATE, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_DSTATE");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory1_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory1_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory2_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory6_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory6_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory3_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory4_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory4_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory5_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory5_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory10_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory10_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory7_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory7_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory8_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory8_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory9_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory9_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory11_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory11_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory12_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory12_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory13_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory13_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory14_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory14_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Memory15_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Memory15_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Ctrl_K_p_x_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Ctrl_K_p_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Ctrl_K_p_y_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Ctrl_K_p_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Ctrl_K_d_x_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Ctrl_K_d_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.Ctrl_K_d_y_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.Ctrl_K_d_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_e1_N_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_e1_N_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_eta0_1_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_eta0_1_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_e2_E_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_e2_E_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_eta0_2_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_eta0_2_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_e2_X_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_e2_X_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_eta0_3_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_eta0_3_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_e2_Y_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_e2_Y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_u0_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_u0_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_path_d_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_path_d_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_l_y1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_l_y1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_path_d_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_path_d_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_l_y2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_l_y2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_tau_r_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_tau_r_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_reset_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_reset_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_tau_u_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_tau_u_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_xc_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_xc_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_tau_v_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_tau_v_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_yc_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_yc_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_eta_1_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_eta_1_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_eta_2_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_eta_2_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_eta_3_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_eta_3_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_nu_1_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_nu_1_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_nu_2_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_nu_2_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.HIL_nu_3_ctrl_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.HIL_nu_3_ctrl_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese, 0, 2, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese");
    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.Ctrl_K_p_x_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.Ctrl_K_p_x_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.Ctrl_K_p_y_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.Ctrl_K_p_y_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.Ctrl_K_d_x_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.Ctrl_K_d_x_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.Ctrl_K_d_y_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.Ctrl_K_d_y_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_e1_N_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_e1_N_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_eta0_1_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_eta0_1_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_e2_E_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_e2_E_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_eta0_2_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_eta0_2_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_e2_X_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_e2_X_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_eta0_3_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_eta0_3_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_e2_Y_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_e2_Y_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_u0_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_u0_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_path_d_1_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_path_d_1_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_l_y1_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_l_y1_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_path_d_2_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_path_d_2_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_l_y2_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_l_y2_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_tau_r_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_tau_r_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_reset_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_reset_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_tau_u_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_tau_u_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_xc_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_xc_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_tau_v_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_tau_v_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_yc_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_yc_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_eta_1_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_eta_1_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_eta_2_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_eta_2_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_eta_3_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_eta_3_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_nu_1_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_nu_1_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_nu_2_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_nu_2_ctrl_DWORK2");
    }

    for (count = 0; count < 23; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_internal_dynamics_DW.HIL_nu_3_ctrl_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_internal_dynamics_DW.HIL_nu_3_ctrl_DWORK2");
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
    NIRT_SetValueByDataType
      (&ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_DSTATE, 0,
       discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory1_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory2_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory6_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory3_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory4_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory5_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory10_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory7_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory8_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory9_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory11_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory12_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory13_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory14_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Memory15_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Ctrl_K_p_x_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Ctrl_K_p_y_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Ctrl_K_d_x_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Ctrl_K_d_y_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_e1_N_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta0_1_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_e2_E_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta0_2_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_e2_X_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta0_3_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_e2_Y_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_u0_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_path_d_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_l_y1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_path_d_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_l_y2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_tau_r_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_reset_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_tau_u_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_xc_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_tau_v_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_yc_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta_1_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta_2_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta_3_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_nu_1_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_nu_2_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_nu_3_ctrl_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType
      (&ctrl_internal_dynamics_DW.DiscreteTimeIntegrator_PrevRese, 0,
       discStates[idx++], 2, 0);
    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Ctrl_K_p_x_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Ctrl_K_p_y_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Ctrl_K_d_x_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.Ctrl_K_d_y_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_e1_N_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta0_1_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_e2_E_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta0_2_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_e2_X_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta0_3_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_e2_Y_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_u0_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_path_d_1_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_l_y1_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_path_d_2_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_l_y2_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_tau_r_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_reset_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_tau_u_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_xc_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_tau_v_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_yc_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta_1_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta_2_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_eta_3_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_nu_1_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_nu_2_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 23; count++) {
      NIRT_SetValueByDataType(&ctrl_internal_dynamics_DW.HIL_nu_3_ctrl_DWORK2,
        count, discStates[idx++], 20, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_ctrl_internal_dynamics
