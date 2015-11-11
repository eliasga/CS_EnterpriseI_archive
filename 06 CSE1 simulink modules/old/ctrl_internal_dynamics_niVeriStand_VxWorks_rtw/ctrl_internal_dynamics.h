/*
 * ctrl_internal_dynamics.h
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
#ifndef RTW_HEADER_ctrl_internal_dynamics_h_
#define RTW_HEADER_ctrl_internal_dynamics_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef ctrl_internal_dynamics_COMMON_INCLUDES_
# define ctrl_internal_dynamics_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* ctrl_internal_dynamics_COMMON_INCLUDES_ */

#include "ctrl_internal_dynamics_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->ModelData.blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->ModelData.blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->ModelData.constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->ModelData.constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ()
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ()
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->ModelData.defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->ModelData.defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ()
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ()
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ()
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ()
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
# define rtmGetNonInlinedSFcns(rtm)    ()
#endif

#ifndef rtmSetNonInlinedSFcns
# define rtmSetNonInlinedSFcns(rtm, val) ()
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ()
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ()
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ()
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ()
#endif

#ifndef rtmGetOffsetTimeArray
# define rtmGetOffsetTimeArray(rtm)    ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
# define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ()
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ()
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ()
#endif

#ifndef rtmGetPerTaskSampleHitsArray
# define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
# define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->ModelData.prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->ModelData.prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ((rtm)->rtwLogInfo = (val))
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
# define rtmGetRTWSolverInfoPtr(rtm)   ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
# define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->ModelData.dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->ModelData.dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
# define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
# define rtmGetSampleTimeArray(rtm)    ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
# define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
# define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
# define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ()
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ()
#endif

#ifndef rtmGetTaskTimeArray
# define rtmGetTaskTimeArray(rtm)      ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
# define rtmSetTaskTimeArray(rtm, val) ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->ModelData.inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->ModelData.inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->ModelData.outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->ModelData.outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->ModelData.zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->ModelData.zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->ModelData.dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->ModelData.dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) 0
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)                                       /* Do Nothing */
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)

/* Definition for use in the target main file */
#define ctrl_internal_dynamics_rtModel RT_MODEL_ctrl_internal_dynami_T

/* Block signals for system '<S1>/diag2x2' */
typedef struct {
  real_T y[4];                         /* '<S1>/diag2x2' */
} B_diag2x2_ctrl_internal_dynam_T;

/* Block signals (auto storage) */
typedef struct {
  real_T Memory10;                     /* '<Root>/Memory10' */
  real_T Ctrl_K_p_x;                   /* '<S4>/Ctrl_K_p_x' */
  real_T Ctrl_K_p_y;                   /* '<S4>/Ctrl_K_p_y' */
  real_T Ctrl_K_d_x;                   /* '<S1>/Ctrl_K_d_x' */
  real_T Ctrl_K_d_y;                   /* '<S1>/Ctrl_K_d_y' */
  real_T HIL_eta0_1_ctrl;              /* '<Root>/HIL_eta0_1_ctrl' */
  real_T HIL_eta0_2_ctrl;              /* '<Root>/HIL_eta0_2_ctrl' */
  real_T HIL_eta0_3_ctrl;              /* '<Root>/HIL_eta0_3_ctrl' */
  real_T HIL_u0;                       /* '<Root>/HIL_u0' */
  real_T HIL_l_y1;                     /* '<Root>/HIL_l_y1' */
  real_T HIL_l_y2;                     /* '<Root>/HIL_l_y2' */
  real_T HIL_reset_ctrl;               /* '<Root>/HIL_reset_ctrl' */
  real_T HIL_xc;                       /* '<Root>/HIL_xc' */
  real_T HIL_yc;                       /* '<Root>/HIL_yc' */
  real_T HIL_eta_1_ctrl;               /* '<Root>/HIL_eta_1_ctrl' */
  real_T HIL_eta_2_ctrl;               /* '<Root>/HIL_eta_2_ctrl' */
  real_T HIL_eta_3_ctrl;               /* '<Root>/HIL_eta_3_ctrl' */
  real_T HIL_nu_1_ctrl;                /* '<Root>/HIL_nu_1_ctrl' */
  real_T HIL_nu_2_ctrl;                /* '<Root>/HIL_nu_2_ctrl' */
  real_T HIL_nu_3_ctrl;                /* '<Root>/HIL_nu_3_ctrl' */
  real_T tau[3];                       /* '<Root>/PD+FL ctrl' */
  real_T e1[2];                        /* '<Root>/PD+FL ctrl' */
  real_T e2[2];                        /* '<Root>/PD+FL ctrl' */
  real_T pd[2];                        /* '<Root>/Guidance' */
  B_diag2x2_ctrl_internal_dynam_T sf_diag2x2;/* '<S4>/diag2x2' */
  B_diag2x2_ctrl_internal_dynam_T sf_diag2x2_c;/* '<S1>/diag2x2' */
} B_ctrl_internal_dynamics_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<Root>/Discrete-Time Integrator' */
  real_T Memory1_PreviousInput;        /* '<Root>/Memory1' */
  real_T Memory2_PreviousInput;        /* '<Root>/Memory2' */
  real_T Memory6_PreviousInput;        /* '<Root>/Memory6' */
  real_T Memory3_PreviousInput;        /* '<Root>/Memory3' */
  real_T Memory4_PreviousInput;        /* '<Root>/Memory4' */
  real_T Memory5_PreviousInput;        /* '<Root>/Memory5' */
  real_T Memory10_PreviousInput;       /* '<Root>/Memory10' */
  real_T Memory7_PreviousInput;        /* '<Root>/Memory7' */
  real_T Memory8_PreviousInput;        /* '<Root>/Memory8' */
  real_T Memory9_PreviousInput;        /* '<Root>/Memory9' */
  real_T Memory11_PreviousInput;       /* '<Root>/Memory11' */
  real_T Memory12_PreviousInput;       /* '<Root>/Memory12' */
  real_T Memory13_PreviousInput;       /* '<Root>/Memory13' */
  real_T Memory14_PreviousInput;       /* '<Root>/Memory14' */
  real_T Memory15_PreviousInput;       /* '<Root>/Memory15' */
  real_T Ctrl_K_p_x_DWORK1;            /* '<S4>/Ctrl_K_p_x' */
  real_T Ctrl_K_p_y_DWORK1;            /* '<S4>/Ctrl_K_p_y' */
  real_T Ctrl_K_d_x_DWORK1;            /* '<S1>/Ctrl_K_d_x' */
  real_T Ctrl_K_d_y_DWORK1;            /* '<S1>/Ctrl_K_d_y' */
  real_T HIL_e1_N_DWORK1;              /* '<Root>/HIL_e1_N' */
  real_T HIL_eta0_1_ctrl_DWORK1;       /* '<Root>/HIL_eta0_1_ctrl' */
  real_T HIL_e2_E_DWORK1;              /* '<Root>/HIL_e2_E' */
  real_T HIL_eta0_2_ctrl_DWORK1;       /* '<Root>/HIL_eta0_2_ctrl' */
  real_T HIL_e2_X_DWORK1;              /* '<Root>/HIL_e2_X' */
  real_T HIL_eta0_3_ctrl_DWORK1;       /* '<Root>/HIL_eta0_3_ctrl' */
  real_T HIL_e2_Y_DWORK1;              /* '<Root>/HIL_e2_Y' */
  real_T HIL_u0_DWORK1;                /* '<Root>/HIL_u0' */
  real_T HIL_path_d_1_DWORK1;          /* '<Root>/HIL_path_d_1' */
  real_T HIL_l_y1_DWORK1;              /* '<Root>/HIL_l_y1' */
  real_T HIL_path_d_2_DWORK1;          /* '<Root>/HIL_path_d_2' */
  real_T HIL_l_y2_DWORK1;              /* '<Root>/HIL_l_y2' */
  real_T HIL_tau_r_DWORK1;             /* '<Root>/HIL_tau_r' */
  real_T HIL_reset_ctrl_DWORK1;        /* '<Root>/HIL_reset_ctrl' */
  real_T HIL_tau_u_DWORK1;             /* '<Root>/HIL_tau_u' */
  real_T HIL_xc_DWORK1;                /* '<Root>/HIL_xc' */
  real_T HIL_tau_v_DWORK1;             /* '<Root>/HIL_tau_v' */
  real_T HIL_yc_DWORK1;                /* '<Root>/HIL_yc' */
  real_T HIL_eta_1_ctrl_DWORK1;        /* '<Root>/HIL_eta_1_ctrl' */
  real_T HIL_eta_2_ctrl_DWORK1;        /* '<Root>/HIL_eta_2_ctrl' */
  real_T HIL_eta_3_ctrl_DWORK1;        /* '<Root>/HIL_eta_3_ctrl' */
  real_T HIL_nu_1_ctrl_DWORK1;         /* '<Root>/HIL_nu_1_ctrl' */
  real_T HIL_nu_2_ctrl_DWORK1;         /* '<Root>/HIL_nu_2_ctrl' */
  real_T HIL_nu_3_ctrl_DWORK1;         /* '<Root>/HIL_nu_3_ctrl' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<Root>/Discrete-Time Integrator' */
  uint8_T Ctrl_K_p_x_DWORK2[23];       /* '<S4>/Ctrl_K_p_x' */
  uint8_T Ctrl_K_p_y_DWORK2[23];       /* '<S4>/Ctrl_K_p_y' */
  uint8_T Ctrl_K_d_x_DWORK2[23];       /* '<S1>/Ctrl_K_d_x' */
  uint8_T Ctrl_K_d_y_DWORK2[23];       /* '<S1>/Ctrl_K_d_y' */
  uint8_T HIL_e1_N_DWORK2[23];         /* '<Root>/HIL_e1_N' */
  uint8_T HIL_eta0_1_ctrl_DWORK2[23];  /* '<Root>/HIL_eta0_1_ctrl' */
  uint8_T HIL_e2_E_DWORK2[23];         /* '<Root>/HIL_e2_E' */
  uint8_T HIL_eta0_2_ctrl_DWORK2[23];  /* '<Root>/HIL_eta0_2_ctrl' */
  uint8_T HIL_e2_X_DWORK2[23];         /* '<Root>/HIL_e2_X' */
  uint8_T HIL_eta0_3_ctrl_DWORK2[23];  /* '<Root>/HIL_eta0_3_ctrl' */
  uint8_T HIL_e2_Y_DWORK2[23];         /* '<Root>/HIL_e2_Y' */
  uint8_T HIL_u0_DWORK2[23];           /* '<Root>/HIL_u0' */
  uint8_T HIL_path_d_1_DWORK2[23];     /* '<Root>/HIL_path_d_1' */
  uint8_T HIL_l_y1_DWORK2[23];         /* '<Root>/HIL_l_y1' */
  uint8_T HIL_path_d_2_DWORK2[23];     /* '<Root>/HIL_path_d_2' */
  uint8_T HIL_l_y2_DWORK2[23];         /* '<Root>/HIL_l_y2' */
  uint8_T HIL_tau_r_DWORK2[23];        /* '<Root>/HIL_tau_r' */
  uint8_T HIL_reset_ctrl_DWORK2[23];   /* '<Root>/HIL_reset_ctrl' */
  uint8_T HIL_tau_u_DWORK2[23];        /* '<Root>/HIL_tau_u' */
  uint8_T HIL_xc_DWORK2[23];           /* '<Root>/HIL_xc' */
  uint8_T HIL_tau_v_DWORK2[23];        /* '<Root>/HIL_tau_v' */
  uint8_T HIL_yc_DWORK2[23];           /* '<Root>/HIL_yc' */
  uint8_T HIL_eta_1_ctrl_DWORK2[23];   /* '<Root>/HIL_eta_1_ctrl' */
  uint8_T HIL_eta_2_ctrl_DWORK2[23];   /* '<Root>/HIL_eta_2_ctrl' */
  uint8_T HIL_eta_3_ctrl_DWORK2[23];   /* '<Root>/HIL_eta_3_ctrl' */
  uint8_T HIL_nu_1_ctrl_DWORK2[23];    /* '<Root>/HIL_nu_1_ctrl' */
  uint8_T HIL_nu_2_ctrl_DWORK2[23];    /* '<Root>/HIL_nu_2_ctrl' */
  uint8_T HIL_nu_3_ctrl_DWORK2[23];    /* '<Root>/HIL_nu_3_ctrl' */
} DW_ctrl_internal_dynamics_T;

/* Backward compatible GRT Identifiers */
#define rtB                            ctrl_internal_dynamics_B
#define BlockIO                        B_ctrl_internal_dynamics_T
#define rtP                            ctrl_internal_dynamics_P
#define Parameters                     P_ctrl_internal_dynamics_T
#define rtDWork                        ctrl_internal_dynamics_DW
#define D_Work                         DW_ctrl_internal_dynamics_T

/* Parameters (auto storage) */
struct P_ctrl_internal_dynamics_T_ {
  real_T Memory1_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory1'
                                        */
  real_T Memory2_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory2'
                                        */
  real_T Memory6_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory6'
                                        */
  real_T Memory3_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory3'
                                        */
  real_T Memory4_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory4'
                                        */
  real_T Memory5_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory5'
                                        */
  real_T Memory10_X0;                  /* Expression: 0
                                        * Referenced by: '<Root>/Memory10'
                                        */
  real_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                         * Referenced by: '<Root>/Discrete-Time Integrator'
                                         */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  real_T Memory7_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory7'
                                        */
  real_T Memory8_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory8'
                                        */
  real_T Memory9_X0;                   /* Expression: 0
                                        * Referenced by: '<Root>/Memory9'
                                        */
  real_T Memory11_X0;                  /* Expression: 0
                                        * Referenced by: '<Root>/Memory11'
                                        */
  real_T Memory12_X0;                  /* Expression: 0
                                        * Referenced by: '<Root>/Memory12'
                                        */
  real_T Memory13_X0;                  /* Expression: 0
                                        * Referenced by: '<Root>/Memory13'
                                        */
  real_T timwe1_Value;                 /* Expression: 1
                                        * Referenced by: '<Root>/timwe1'
                                        */
  real_T Memory14_X0;                  /* Expression: 0
                                        * Referenced by: '<Root>/Memory14'
                                        */
  real_T Memory15_X0;                  /* Expression: 0
                                        * Referenced by: '<Root>/Memory15'
                                        */
  real_T Ctrl_K_p_x_P1;                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P2;                /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P3;                /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P4;                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P5;                /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P6;                /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_y_P1;                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P2;                /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P3;                /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P4;                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P5;                /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P6;                /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_d_x_P1;                /* Expression: width
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  real_T Ctrl_K_d_x_P2;                /* Expression: dtype
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  real_T Ctrl_K_d_x_P3;                /* Expression: portnum
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  real_T Ctrl_K_d_x_P4;                /* Expression: stime
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  real_T Ctrl_K_d_x_P5;                /* Expression: stype
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  real_T Ctrl_K_d_x_P6;                /* Expression: btype
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  real_T Ctrl_K_d_y_P1;                /* Expression: width
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P2;                /* Expression: dtype
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P3;                /* Expression: portnum
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P4;                /* Expression: stime
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P5;                /* Expression: stype
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P6;                /* Expression: btype
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  real_T HIL_e1_N_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  real_T HIL_e1_N_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  real_T HIL_e1_N_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  real_T HIL_e1_N_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  real_T HIL_e1_N_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  real_T HIL_e1_N_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  real_T HIL_eta0_1_ctrl_P1;           /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  real_T HIL_eta0_1_ctrl_P2;           /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  real_T HIL_eta0_1_ctrl_P3;           /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  real_T HIL_eta0_1_ctrl_P4;           /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  real_T HIL_eta0_1_ctrl_P5;           /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  real_T HIL_eta0_1_ctrl_P6;           /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  real_T HIL_e2_E_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  real_T HIL_e2_E_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  real_T HIL_e2_E_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  real_T HIL_e2_E_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  real_T HIL_e2_E_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  real_T HIL_e2_E_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  real_T HIL_eta0_2_ctrl_P1;           /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  real_T HIL_eta0_2_ctrl_P2;           /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  real_T HIL_eta0_2_ctrl_P3;           /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  real_T HIL_eta0_2_ctrl_P4;           /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  real_T HIL_eta0_2_ctrl_P5;           /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  real_T HIL_eta0_2_ctrl_P6;           /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  real_T HIL_e2_X_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  real_T HIL_e2_X_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  real_T HIL_e2_X_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  real_T HIL_e2_X_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  real_T HIL_e2_X_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  real_T HIL_e2_X_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  real_T HIL_eta0_3_ctrl_P1;           /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  real_T HIL_eta0_3_ctrl_P2;           /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  real_T HIL_eta0_3_ctrl_P3;           /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  real_T HIL_eta0_3_ctrl_P4;           /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  real_T HIL_eta0_3_ctrl_P5;           /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  real_T HIL_eta0_3_ctrl_P6;           /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  real_T HIL_e2_Y_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  real_T HIL_e2_Y_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  real_T HIL_e2_Y_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  real_T HIL_e2_Y_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  real_T HIL_e2_Y_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  real_T HIL_e2_Y_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  real_T HIL_u0_P1;                    /* Expression: width
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  real_T HIL_u0_P2;                    /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  real_T HIL_u0_P3;                    /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  real_T HIL_u0_P4;                    /* Expression: stime
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  real_T HIL_u0_P5;                    /* Expression: stype
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  real_T HIL_u0_P6;                    /* Expression: btype
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  real_T HIL_path_d_1_P1;              /* Expression: width
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  real_T HIL_path_d_1_P2;              /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  real_T HIL_path_d_1_P3;              /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  real_T HIL_path_d_1_P4;              /* Expression: stime
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  real_T HIL_path_d_1_P5;              /* Expression: stype
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  real_T HIL_path_d_1_P6;              /* Expression: btype
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  real_T HIL_l_y1_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  real_T HIL_l_y1_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  real_T HIL_l_y1_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  real_T HIL_l_y1_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  real_T HIL_l_y1_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  real_T HIL_l_y1_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  real_T HIL_path_d_2_P1;              /* Expression: width
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  real_T HIL_path_d_2_P2;              /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  real_T HIL_path_d_2_P3;              /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  real_T HIL_path_d_2_P4;              /* Expression: stime
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  real_T HIL_path_d_2_P5;              /* Expression: stype
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  real_T HIL_path_d_2_P6;              /* Expression: btype
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  real_T HIL_l_y2_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  real_T HIL_l_y2_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  real_T HIL_l_y2_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  real_T HIL_l_y2_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  real_T HIL_l_y2_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  real_T HIL_l_y2_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  real_T HIL_tau_r_P1;                 /* Expression: width
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  real_T HIL_tau_r_P2;                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  real_T HIL_tau_r_P3;                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  real_T HIL_tau_r_P4;                 /* Expression: stime
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  real_T HIL_tau_r_P5;                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  real_T HIL_tau_r_P6;                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  real_T HIL_reset_ctrl_P1;            /* Expression: width
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  real_T HIL_reset_ctrl_P2;            /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  real_T HIL_reset_ctrl_P3;            /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  real_T HIL_reset_ctrl_P4;            /* Expression: stime
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  real_T HIL_reset_ctrl_P5;            /* Expression: stype
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  real_T HIL_reset_ctrl_P6;            /* Expression: btype
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  real_T HIL_tau_u_P1;                 /* Expression: width
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  real_T HIL_tau_u_P2;                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  real_T HIL_tau_u_P3;                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  real_T HIL_tau_u_P4;                 /* Expression: stime
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  real_T HIL_tau_u_P5;                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  real_T HIL_tau_u_P6;                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  real_T HIL_xc_P1;                    /* Expression: width
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  real_T HIL_xc_P2;                    /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  real_T HIL_xc_P3;                    /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  real_T HIL_xc_P4;                    /* Expression: stime
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  real_T HIL_xc_P5;                    /* Expression: stype
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  real_T HIL_xc_P6;                    /* Expression: btype
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  real_T HIL_tau_v_P1;                 /* Expression: width
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  real_T HIL_tau_v_P2;                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  real_T HIL_tau_v_P3;                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  real_T HIL_tau_v_P4;                 /* Expression: stime
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  real_T HIL_tau_v_P5;                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  real_T HIL_tau_v_P6;                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  real_T HIL_yc_P1;                    /* Expression: width
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  real_T HIL_yc_P2;                    /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  real_T HIL_yc_P3;                    /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  real_T HIL_yc_P4;                    /* Expression: stime
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  real_T HIL_yc_P5;                    /* Expression: stype
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  real_T HIL_yc_P6;                    /* Expression: btype
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  real_T HIL_eta_1_ctrl_P1;            /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  real_T HIL_eta_1_ctrl_P2;            /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  real_T HIL_eta_1_ctrl_P3;            /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  real_T HIL_eta_1_ctrl_P4;            /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  real_T HIL_eta_1_ctrl_P5;            /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  real_T HIL_eta_1_ctrl_P6;            /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  real_T HIL_eta_2_ctrl_P1;            /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  real_T HIL_eta_2_ctrl_P2;            /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  real_T HIL_eta_2_ctrl_P3;            /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  real_T HIL_eta_2_ctrl_P4;            /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  real_T HIL_eta_2_ctrl_P5;            /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  real_T HIL_eta_2_ctrl_P6;            /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  real_T HIL_eta_3_ctrl_P1;            /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  real_T HIL_eta_3_ctrl_P2;            /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  real_T HIL_eta_3_ctrl_P3;            /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  real_T HIL_eta_3_ctrl_P4;            /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  real_T HIL_eta_3_ctrl_P5;            /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  real_T HIL_eta_3_ctrl_P6;            /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  real_T HIL_nu_1_ctrl_P1;             /* Expression: width
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  real_T HIL_nu_1_ctrl_P2;             /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  real_T HIL_nu_1_ctrl_P3;             /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  real_T HIL_nu_1_ctrl_P4;             /* Expression: stime
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  real_T HIL_nu_1_ctrl_P5;             /* Expression: stype
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  real_T HIL_nu_1_ctrl_P6;             /* Expression: btype
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  real_T HIL_nu_2_ctrl_P1;             /* Expression: width
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  real_T HIL_nu_2_ctrl_P2;             /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  real_T HIL_nu_2_ctrl_P3;             /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  real_T HIL_nu_2_ctrl_P4;             /* Expression: stime
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  real_T HIL_nu_2_ctrl_P5;             /* Expression: stype
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  real_T HIL_nu_2_ctrl_P6;             /* Expression: btype
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  real_T HIL_nu_3_ctrl_P1;             /* Expression: width
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  real_T HIL_nu_3_ctrl_P2;             /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  real_T HIL_nu_3_ctrl_P3;             /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  real_T HIL_nu_3_ctrl_P4;             /* Expression: stime
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  real_T HIL_nu_3_ctrl_P5;             /* Expression: stype
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  real_T HIL_nu_3_ctrl_P6;             /* Expression: btype
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  real_T timwe_Value;                  /* Expression: 1
                                        * Referenced by: '<Root>/timwe'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ctrl_internal_dynamic_T {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWLogInfo *rtwLogInfo;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    void *blockIO;
    const void *constBlockIO;
    void *defaultParam;
    ZCSigState *prevZCSigState;
    real_T *contStates;
    real_T *derivs;
    void *zcSignalValues;
    void *inputs;
    void *outputs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    void *dwork;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[1];
    time_T offsetTimesArray[1];
    int_T sampleTimeTaskIDArray[1];
    int_T sampleHitArray[1];
    int_T perTaskSampleHitsArray[1];
    time_T tArray[1];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_ctrl_internal_dynamics_T ctrl_internal_dynamics_P;

/* Block signals (auto storage) */
extern B_ctrl_internal_dynamics_T ctrl_internal_dynamics_B;

/* Block states (auto storage) */
extern DW_ctrl_internal_dynamics_T ctrl_internal_dynamics_DW;

/* Real-time Model object */
extern RT_MODEL_ctrl_internal_dynami_T *const ctrl_internal_dynamics_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ctrl_internal_dynamics'
 * '<S1>'   : 'ctrl_internal_dynamics/Derivative_ gain'
 * '<S2>'   : 'ctrl_internal_dynamics/Guidance'
 * '<S3>'   : 'ctrl_internal_dynamics/PD+FL ctrl'
 * '<S4>'   : 'ctrl_internal_dynamics/Proportional gain'
 * '<S5>'   : 'ctrl_internal_dynamics/Derivative_ gain/diag2x2'
 * '<S6>'   : 'ctrl_internal_dynamics/Proportional gain/diag2x2'
 */
#endif                                 /* RTW_HEADER_ctrl_internal_dynamics_h_ */

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_ctrl_internal_dynamics
#ifndef NI_VERISTAND_MODELDATAFILE
#ifdef NI_VERISTAND_MAINMODELFILE

int READSIDE = 0;
int tid = 0;

#ifdef MULTITASKING

P_ctrl_internal_dynamics_T rtParameter[NUMST+!TID01EQ];
P_ctrl_internal_dynamics_T *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },
};

#else

P_ctrl_internal_dynamics_T rtParameter[2];

#endif

#else

extern int READSIDE;

#ifdef MULTITASKING

extern int tid;
extern P_ctrl_internal_dynamics_T* param_lookup[NUMST][2];

#else

extern P_ctrl_internal_dynamics_T rtParameter[];

#endif
#endif

#ifdef MULTITASKING
#define ctrl_internal_dynamics_P       (*param_lookup[tid][READSIDE])
#else
#define ctrl_internal_dynamics_P       rtParameter[READSIDE]
#endif
#endif
#endif
