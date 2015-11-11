/*
 * ctrl_DP_mss.h
 *
 * Code generation for model "ctrl_DP_mss".
 *
 * Model version              : 1.10
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Jan 28 18:35:59 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_ctrl_DP_mss_h_
#define RTW_HEADER_ctrl_DP_mss_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef ctrl_DP_mss_COMMON_INCLUDES_
# define ctrl_DP_mss_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* ctrl_DP_mss_COMMON_INCLUDES_ */

#include "ctrl_DP_mss_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_zcfcn.h"
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
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
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
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
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
# define rtmIsContinuousTask(rtm, tid) ((tid) == 0)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtmIsMajorTimeStep((rtm)) && (rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]]))
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
#define ctrl_DP_mss_rtModel            RT_MODEL_ctrl_DP_mss_T

/* Block signals (auto storage) */
typedef struct {
  real_T VectorConcatenate[9];         /* '<S11>/Vector Concatenate' */
  real_T Ctrl_X;                       /* '<Root>/Ctrl_X' */
  real_T Ctrl_Y;                       /* '<Root>/Ctrl_Y' */
  real_T Ctrl_PSI;                     /* '<Root>/Ctrl_PSI' */
  real_T Ctrl_X_ref;                   /* '<Root>/Ctrl_X_ref' */
  real_T Ctrl_Y_ref;                   /* '<Root>/Ctrl_Y_ref' */
  real_T Ctrl_PSI_ref;                 /* '<Root>/Ctrl_PSI_ref' */
  real_T TmpSignalConversionAtMatrixMult[3];/* '<S1>/Transposed rotation  matrix in yaw1' */
  real_T VectorConcatenate_l[9];       /* '<S10>/Vector Concatenate' */
  real_T Reset_integrator;             /* '<S1>/Reset_integrator' */
  real_T VectorConcatenate_d[9];       /* '<S9>/Vector Concatenate' */
  real_T Ctrl_u_surge;                 /* '<Root>/Ctrl_u_surge' */
  real_T Ctrl_v_sway;                  /* '<Root>/Ctrl_v_sway' */
  real_T Ctrl_r_yawrate;               /* '<Root>/Ctrl_r_yawrate' */
  real_T Sum1[3];                      /* '<S1>/Sum1' */
  real_T Bool_VSP_omega_on_off;        /* '<S12>/Bool_VSP_omega_on_off' */
  real_T Switch;                       /* '<S12>/Switch' */
  real_T u_BT;                         /* '<S2>/Thrust allocation' */
  real_T u_VSP;                        /* '<S2>/Thrust allocation' */
  real_T alpha_VSP;                    /* '<S2>/Thrust allocation' */
} B_ctrl_DP_mss_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Ctrl_K_p_psi_DWORK1;          /* '<S5>/Ctrl_K_p_psi' */
  real_T Ctrl_K_p_x_DWORK1;            /* '<S5>/Ctrl_K_p_x' */
  real_T Ctrl_K_p_y_DWORK1;            /* '<S5>/Ctrl_K_p_y' */
  real_T Ctrl_X_DWORK1;                /* '<Root>/Ctrl_X' */
  real_T Ctrl_Y_DWORK1;                /* '<Root>/Ctrl_Y' */
  real_T Ctrl_PSI_DWORK1;              /* '<Root>/Ctrl_PSI' */
  real_T Ctrl_X_ref_DWORK1;            /* '<Root>/Ctrl_X_ref' */
  real_T Ctrl_Y_ref_DWORK1;            /* '<Root>/Ctrl_Y_ref' */
  real_T Ctrl_PSI_ref_DWORK1;          /* '<Root>/Ctrl_PSI_ref' */
  real_T Ctrl_K_i_psi_DWORK1;          /* '<S4>/Ctrl_K_i_psi' */
  real_T Ctrl_K_i_x_DWORK1;            /* '<S4>/Ctrl_K_i_x' */
  real_T Ctrl_K_i_y_DWORK1;            /* '<S4>/Ctrl_K_i_y' */
  real_T Reset_integrator_DWORK1;      /* '<S1>/Reset_integrator' */
  real_T Ctrl_K_d_X_DWORK1;            /* '<S3>/Ctrl_K_d_X' */
  real_T Ctrl_K_d_psi_DWORK1;          /* '<S3>/Ctrl_K_d_psi' */
  real_T Ctrl_K_d_y_DWORK1;            /* '<S3>/Ctrl_K_d_y' */
  real_T Ctrl_u_surge_DWORK1;          /* '<Root>/Ctrl_u_surge' */
  real_T Ctrl_v_sway_DWORK1;           /* '<Root>/Ctrl_v_sway' */
  real_T Ctrl_r_yawrate_DWORK1;        /* '<Root>/Ctrl_r_yawrate' */
  real_T Ctrl_tau_x_DWORK1;            /* '<Root>/Ctrl_tau_x' */
  real_T Ctrl_tau_y_DWORK1;            /* '<Root>/Ctrl_tau_y' */
  real_T Ctrl_tau_psi_DWORK1;          /* '<Root>/Ctrl_tau_psi' */
  real_T Ctrl_U_BT_DWORK1;             /* '<Root>/Ctrl_U_BT' */
  real_T Bool_VSP_omega_on_off_DWORK1; /* '<S12>/Bool_VSP_omega_on_off' */
  real_T Ctrl_omega_vsp1_DWORK1;       /* '<Root>/Ctrl_omega_vsp1' */
  real_T Ctrl_omega_vsp2_DWORK1;       /* '<Root>/Ctrl_omega_vsp2' */
  real_T Ctrl_U_1_DWORK1;              /* '<Root>/Ctrl_U_1' */
  real_T Ctrl_U_2_DWORK1;              /* '<Root>/Ctrl_U_2' */
  real_T Ctrl_alpha_1_DWORK1;          /* '<Root>/Ctrl_alpha_1' */
  real_T Ctrl_alpha_2_DWORK1;          /* '<Root>/Ctrl_alpha_2' */
  uint8_T Ctrl_K_p_psi_DWORK2[12];     /* '<S5>/Ctrl_K_p_psi' */
  uint8_T Ctrl_K_p_x_DWORK2[12];       /* '<S5>/Ctrl_K_p_x' */
  uint8_T Ctrl_K_p_y_DWORK2[12];       /* '<S5>/Ctrl_K_p_y' */
  uint8_T Ctrl_X_DWORK2[12];           /* '<Root>/Ctrl_X' */
  uint8_T Ctrl_Y_DWORK2[12];           /* '<Root>/Ctrl_Y' */
  uint8_T Ctrl_PSI_DWORK2[12];         /* '<Root>/Ctrl_PSI' */
  uint8_T Ctrl_X_ref_DWORK2[12];       /* '<Root>/Ctrl_X_ref' */
  uint8_T Ctrl_Y_ref_DWORK2[12];       /* '<Root>/Ctrl_Y_ref' */
  uint8_T Ctrl_PSI_ref_DWORK2[12];     /* '<Root>/Ctrl_PSI_ref' */
  uint8_T Ctrl_K_i_psi_DWORK2[12];     /* '<S4>/Ctrl_K_i_psi' */
  uint8_T Ctrl_K_i_x_DWORK2[12];       /* '<S4>/Ctrl_K_i_x' */
  uint8_T Ctrl_K_i_y_DWORK2[12];       /* '<S4>/Ctrl_K_i_y' */
  uint8_T Reset_integrator_DWORK2[12]; /* '<S1>/Reset_integrator' */
  uint8_T Ctrl_K_d_X_DWORK2[12];       /* '<S3>/Ctrl_K_d_X' */
  uint8_T Ctrl_K_d_psi_DWORK2[12];     /* '<S3>/Ctrl_K_d_psi' */
  uint8_T Ctrl_K_d_y_DWORK2[12];       /* '<S3>/Ctrl_K_d_y' */
  uint8_T Ctrl_u_surge_DWORK2[12];     /* '<Root>/Ctrl_u_surge' */
  uint8_T Ctrl_v_sway_DWORK2[12];      /* '<Root>/Ctrl_v_sway' */
  uint8_T Ctrl_r_yawrate_DWORK2[12];   /* '<Root>/Ctrl_r_yawrate' */
  uint8_T Ctrl_tau_x_DWORK2[12];       /* '<Root>/Ctrl_tau_x' */
  uint8_T Ctrl_tau_y_DWORK2[12];       /* '<Root>/Ctrl_tau_y' */
  uint8_T Ctrl_tau_psi_DWORK2[12];     /* '<Root>/Ctrl_tau_psi' */
  uint8_T Ctrl_U_BT_DWORK2[12];        /* '<Root>/Ctrl_U_BT' */
  uint8_T Bool_VSP_omega_on_off_DWORK2[12];/* '<S12>/Bool_VSP_omega_on_off' */
  uint8_T Ctrl_omega_vsp1_DWORK2[12];  /* '<Root>/Ctrl_omega_vsp1' */
  uint8_T Ctrl_omega_vsp2_DWORK2[12];  /* '<Root>/Ctrl_omega_vsp2' */
  uint8_T Ctrl_U_1_DWORK2[12];         /* '<Root>/Ctrl_U_1' */
  uint8_T Ctrl_U_2_DWORK2[12];         /* '<Root>/Ctrl_U_2' */
  uint8_T Ctrl_alpha_1_DWORK2[12];     /* '<Root>/Ctrl_alpha_1' */
  uint8_T Ctrl_alpha_2_DWORK2[12];     /* '<Root>/Ctrl_alpha_2' */
} DW_ctrl_DP_mss_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S1>/Integrator' */
} X_ctrl_DP_mss_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S1>/Integrator' */
} XDot_ctrl_DP_mss_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S1>/Integrator' */
} XDis_ctrl_DP_mss_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S1>/Integrator' */
} PrevZCX_ctrl_DP_mss_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            ctrl_DP_mss_B
#define BlockIO                        B_ctrl_DP_mss_T
#define rtX                            ctrl_DP_mss_X
#define ContinuousStates               X_ctrl_DP_mss_T
#define rtXdot                         ctrl_DP_mss_XDot
#define StateDerivatives               XDot_ctrl_DP_mss_T
#define tXdis                          ctrl_DP_mss_XDis
#define StateDisabled                  XDis_ctrl_DP_mss_T
#define rtP                            ctrl_DP_mss_P
#define Parameters                     P_ctrl_DP_mss_T
#define rtDWork                        ctrl_DP_mss_DW
#define D_Work                         DW_ctrl_DP_mss_T
#define rtPrevZCSigState               ctrl_DP_mss_PrevZCX
#define PrevZCSigStates                PrevZCX_ctrl_DP_mss_T

/* Parameters (auto storage) */
struct P_ctrl_DP_mss_T_ {
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0.3
                                        * Referenced by: '<S12>/Constant1'
                                        */
  real_T Ctrl_K_p_psi_P1;              /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  real_T Ctrl_K_p_psi_P2;              /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  real_T Ctrl_K_p_psi_P3;              /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  real_T Ctrl_K_p_psi_P4;              /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  real_T Ctrl_K_p_psi_P5;              /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  real_T Ctrl_K_p_psi_P6;              /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  real_T Ctrl_K_p_x_P1;                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P2;                /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P3;                /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P4;                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P5;                /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_x_P6;                /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  real_T Ctrl_K_p_y_P1;                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P2;                /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P3;                /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P4;                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P5;                /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  real_T Ctrl_K_p_y_P6;                /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  real_T Constant8_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant8'
                                        */
  real_T Constant10_Value;             /* Expression: 0
                                        * Referenced by: '<S5>/Constant10'
                                        */
  real_T Constant6_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant6'
                                        */
  real_T Constant11_Value;             /* Expression: 0
                                        * Referenced by: '<S5>/Constant11'
                                        */
  real_T Constant7_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant7'
                                        */
  real_T Constant9_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant9'
                                        */
  real_T Ctrl_X_P1;                    /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  real_T Ctrl_X_P2;                    /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  real_T Ctrl_X_P3;                    /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  real_T Ctrl_X_P4;                    /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  real_T Ctrl_X_P5;                    /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  real_T Ctrl_X_P6;                    /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  real_T Ctrl_Y_P1;                    /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  real_T Ctrl_Y_P2;                    /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  real_T Ctrl_Y_P3;                    /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  real_T Ctrl_Y_P4;                    /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  real_T Ctrl_Y_P5;                    /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  real_T Ctrl_Y_P6;                    /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  real_T Ctrl_PSI_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  real_T Ctrl_PSI_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  real_T Ctrl_PSI_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  real_T Ctrl_PSI_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  real_T Ctrl_PSI_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  real_T Ctrl_PSI_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T Constant_Value_l;             /* Expression: 2*pi
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Ctrl_X_ref_P1;                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  real_T Ctrl_X_ref_P2;                /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  real_T Ctrl_X_ref_P3;                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  real_T Ctrl_X_ref_P4;                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  real_T Ctrl_X_ref_P5;                /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  real_T Ctrl_X_ref_P6;                /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  real_T Ctrl_Y_ref_P1;                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  real_T Ctrl_Y_ref_P2;                /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  real_T Ctrl_Y_ref_P3;                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  real_T Ctrl_Y_ref_P4;                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  real_T Ctrl_Y_ref_P5;                /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  real_T Ctrl_Y_ref_P6;                /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  real_T Ctrl_PSI_ref_P1;              /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  real_T Ctrl_PSI_ref_P2;              /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  real_T Ctrl_PSI_ref_P3;              /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  real_T Ctrl_PSI_ref_P4;              /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  real_T Ctrl_PSI_ref_P5;              /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  real_T Ctrl_PSI_ref_P6;              /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  real_T Saturation_UpperSat_p;        /* Expression: 1e10
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Saturation_LowerSat_i;        /* Expression: -1e10
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Gain_Gain_l;                  /* Expression: pi
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T Constant_Value_g;             /* Expression: 2*pi
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Ctrl_K_i_psi_P1;              /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  real_T Ctrl_K_i_psi_P2;              /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  real_T Ctrl_K_i_psi_P3;              /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  real_T Ctrl_K_i_psi_P4;              /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  real_T Ctrl_K_i_psi_P5;              /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  real_T Ctrl_K_i_psi_P6;              /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  real_T Ctrl_K_i_x_P1;                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  real_T Ctrl_K_i_x_P2;                /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  real_T Ctrl_K_i_x_P3;                /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  real_T Ctrl_K_i_x_P4;                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  real_T Ctrl_K_i_x_P5;                /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  real_T Ctrl_K_i_x_P6;                /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  real_T Ctrl_K_i_y_P1;                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  real_T Ctrl_K_i_y_P2;                /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  real_T Ctrl_K_i_y_P3;                /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  real_T Ctrl_K_i_y_P4;                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  real_T Ctrl_K_i_y_P5;                /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  real_T Ctrl_K_i_y_P6;                /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  real_T Constant14_Value;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant14'
                                        */
  real_T Constant16_Value;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant16'
                                        */
  real_T Constant12_Value;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant12'
                                        */
  real_T Constant17_Value;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant17'
                                        */
  real_T Constant13_Value;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant13'
                                        */
  real_T Constant15_Value;             /* Expression: 0
                                        * Referenced by: '<S4>/Constant15'
                                        */
  real_T Reset_integrator_P1;          /* Expression: width
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  real_T Reset_integrator_P2;          /* Expression: dtype
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  real_T Reset_integrator_P3;          /* Expression: portnum
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  real_T Reset_integrator_P4;          /* Expression: stime
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  real_T Reset_integrator_P5;          /* Expression: stype
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  real_T Reset_integrator_P6;          /* Expression: btype
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Ctrl_K_d_X_P1;                /* Expression: width
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  real_T Ctrl_K_d_X_P2;                /* Expression: dtype
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  real_T Ctrl_K_d_X_P3;                /* Expression: portnum
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  real_T Ctrl_K_d_X_P4;                /* Expression: stime
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  real_T Ctrl_K_d_X_P5;                /* Expression: stype
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  real_T Ctrl_K_d_X_P6;                /* Expression: btype
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  real_T Ctrl_K_d_psi_P1;              /* Expression: width
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  real_T Ctrl_K_d_psi_P2;              /* Expression: dtype
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  real_T Ctrl_K_d_psi_P3;              /* Expression: portnum
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  real_T Ctrl_K_d_psi_P4;              /* Expression: stime
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  real_T Ctrl_K_d_psi_P5;              /* Expression: stype
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  real_T Ctrl_K_d_psi_P6;              /* Expression: btype
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  real_T Ctrl_K_d_y_P1;                /* Expression: width
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P2;                /* Expression: dtype
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P3;                /* Expression: portnum
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P4;                /* Expression: stime
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P5;                /* Expression: stype
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  real_T Ctrl_K_d_y_P6;                /* Expression: btype
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S3>/Constant2'
                                        */
  real_T Constant4_Value;              /* Expression: 0
                                        * Referenced by: '<S3>/Constant4'
                                        */
  real_T Constant_Value_m;             /* Expression: 0
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T Constant5_Value;              /* Expression: 0
                                        * Referenced by: '<S3>/Constant5'
                                        */
  real_T Constant1_Value_b;            /* Expression: 0
                                        * Referenced by: '<S3>/Constant1'
                                        */
  real_T Constant3_Value;              /* Expression: 0
                                        * Referenced by: '<S3>/Constant3'
                                        */
  real_T Ctrl_u_surge_P1;              /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  real_T Ctrl_u_surge_P2;              /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  real_T Ctrl_u_surge_P3;              /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  real_T Ctrl_u_surge_P4;              /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  real_T Ctrl_u_surge_P5;              /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  real_T Ctrl_u_surge_P6;              /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  real_T Ctrl_v_sway_P1;               /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  real_T Ctrl_v_sway_P2;               /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  real_T Ctrl_v_sway_P3;               /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  real_T Ctrl_v_sway_P4;               /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  real_T Ctrl_v_sway_P5;               /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  real_T Ctrl_v_sway_P6;               /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  real_T Ctrl_r_yawrate_P1;            /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  real_T Ctrl_r_yawrate_P2;            /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  real_T Ctrl_r_yawrate_P3;            /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  real_T Ctrl_r_yawrate_P4;            /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  real_T Ctrl_r_yawrate_P5;            /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  real_T Ctrl_r_yawrate_P6;            /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  real_T Ctrl_tau_x_P1;                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  real_T Ctrl_tau_x_P2;                /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  real_T Ctrl_tau_x_P3;                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  real_T Ctrl_tau_x_P4;                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  real_T Ctrl_tau_x_P5;                /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  real_T Ctrl_tau_x_P6;                /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  real_T Ctrl_tau_y_P1;                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  real_T Ctrl_tau_y_P2;                /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  real_T Ctrl_tau_y_P3;                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  real_T Ctrl_tau_y_P4;                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  real_T Ctrl_tau_y_P5;                /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  real_T Ctrl_tau_y_P6;                /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  real_T Ctrl_tau_psi_P1;              /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  real_T Ctrl_tau_psi_P2;              /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  real_T Ctrl_tau_psi_P3;              /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  real_T Ctrl_tau_psi_P4;              /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  real_T Ctrl_tau_psi_P5;              /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  real_T Ctrl_tau_psi_P6;              /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  real_T Constant_Value_k;             /* Expression: 0.42
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Ctrl_U_BT_P1;                 /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  real_T Ctrl_U_BT_P2;                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  real_T Ctrl_U_BT_P3;                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  real_T Ctrl_U_BT_P4;                 /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  real_T Ctrl_U_BT_P5;                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  real_T Ctrl_U_BT_P6;                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  real_T Bool_VSP_omega_on_off_P1;     /* Expression: width
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  real_T Bool_VSP_omega_on_off_P2;     /* Expression: dtype
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  real_T Bool_VSP_omega_on_off_P3;     /* Expression: portnum
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  real_T Bool_VSP_omega_on_off_P4;     /* Expression: stime
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  real_T Bool_VSP_omega_on_off_P5;     /* Expression: stype
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  real_T Bool_VSP_omega_on_off_P6;     /* Expression: btype
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  real_T Ctrl_omega_vsp1_P1;           /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  real_T Ctrl_omega_vsp1_P2;           /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  real_T Ctrl_omega_vsp1_P3;           /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  real_T Ctrl_omega_vsp1_P4;           /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  real_T Ctrl_omega_vsp1_P5;           /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  real_T Ctrl_omega_vsp1_P6;           /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  real_T Ctrl_omega_vsp2_P1;           /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  real_T Ctrl_omega_vsp2_P2;           /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  real_T Ctrl_omega_vsp2_P3;           /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  real_T Ctrl_omega_vsp2_P4;           /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  real_T Ctrl_omega_vsp2_P5;           /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  real_T Ctrl_omega_vsp2_P6;           /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  real_T Ctrl_U_1_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  real_T Ctrl_U_1_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  real_T Ctrl_U_1_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  real_T Ctrl_U_1_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  real_T Ctrl_U_1_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  real_T Ctrl_U_1_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  real_T Ctrl_U_2_P1;                  /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  real_T Ctrl_U_2_P2;                  /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  real_T Ctrl_U_2_P3;                  /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  real_T Ctrl_U_2_P4;                  /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  real_T Ctrl_U_2_P5;                  /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  real_T Ctrl_U_2_P6;                  /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  real_T Ctrl_alpha_1_P1;              /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  real_T Ctrl_alpha_1_P2;              /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  real_T Ctrl_alpha_1_P3;              /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  real_T Ctrl_alpha_1_P4;              /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  real_T Ctrl_alpha_1_P5;              /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  real_T Ctrl_alpha_1_P6;              /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  real_T Ctrl_alpha_2_P1;              /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  real_T Ctrl_alpha_2_P2;              /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  real_T Ctrl_alpha_2_P3;              /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  real_T Ctrl_alpha_2_P4;              /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  real_T Ctrl_alpha_2_P5;              /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  real_T Ctrl_alpha_2_P6;              /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ctrl_DP_mss_T {
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
    real_T odeY[3];
    real_T odeF[4][3];
    ODE4_IntgData intgData;
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
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T stepSize1;
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
    time_T sampleTimesArray[2];
    time_T offsetTimesArray[2];
    int_T sampleTimeTaskIDArray[2];
    int_T sampleHitArray[2];
    int_T perTaskSampleHitsArray[4];
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_ctrl_DP_mss_T ctrl_DP_mss_P;

/* Block signals (auto storage) */
extern B_ctrl_DP_mss_T ctrl_DP_mss_B;

/* Continuous states (auto storage) */
extern X_ctrl_DP_mss_T ctrl_DP_mss_X;

/* Block states (auto storage) */
extern DW_ctrl_DP_mss_T ctrl_DP_mss_DW;

/* Model entry point functions */
extern void ctrl_DP_mss_initialize(void);
extern void ctrl_DP_mss_output(void);
extern void ctrl_DP_mss_update(void);
extern void ctrl_DP_mss_terminate(void);

/* Real-time Model object */
extern RT_MODEL_ctrl_DP_mss_T *const ctrl_DP_mss_M;

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
 * '<Root>' : 'ctrl_DP_mss'
 * '<S1>'   : 'ctrl_DP_mss/DP controller'
 * '<S2>'   : 'ctrl_DP_mss/Thruster allocation'
 * '<S3>'   : 'ctrl_DP_mss/DP controller/Derivative gain'
 * '<S4>'   : 'ctrl_DP_mss/DP controller/Integral  gain'
 * '<S5>'   : 'ctrl_DP_mss/DP controller/Proportional gain'
 * '<S6>'   : 'ctrl_DP_mss/DP controller/Transposed rotation  matrix in yaw1'
 * '<S7>'   : 'ctrl_DP_mss/DP controller/[-inf inf] to [-pi pi]'
 * '<S8>'   : 'ctrl_DP_mss/DP controller/[-inf inf] to [-pi pi]1'
 * '<S9>'   : 'ctrl_DP_mss/DP controller/Derivative gain/Create 3x3 Matrix'
 * '<S10>'  : 'ctrl_DP_mss/DP controller/Integral  gain/Create 3x3 Matrix2'
 * '<S11>'  : 'ctrl_DP_mss/DP controller/Proportional gain/Create 3x3 Matrix1'
 * '<S12>'  : 'ctrl_DP_mss/Thruster allocation/Set_omega_VSP'
 * '<S13>'  : 'ctrl_DP_mss/Thruster allocation/Thrust allocation'
 */
#endif                                 /* RTW_HEADER_ctrl_DP_mss_h_ */

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_ctrl_DP_mss
#ifndef NI_VERISTAND_MODELDATAFILE
#ifdef NI_VERISTAND_MAINMODELFILE

int READSIDE = 0;
int tid = 0;

#ifdef MULTITASKING

P_ctrl_DP_mss_T rtParameter[NUMST+!TID01EQ];
P_ctrl_DP_mss_T *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

P_ctrl_DP_mss_T rtParameter[2];

#endif

#else

extern int READSIDE;

#ifdef MULTITASKING

extern int tid;
extern P_ctrl_DP_mss_T* param_lookup[NUMST][2];

#else

extern P_ctrl_DP_mss_T rtParameter[];

#endif
#endif

#ifdef MULTITASKING
#define ctrl_DP_mss_P                  (*param_lookup[tid][READSIDE])
#else
#define ctrl_DP_mss_P                  rtParameter[READSIDE]
#endif
#endif
#endif
