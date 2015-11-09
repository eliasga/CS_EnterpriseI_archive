/*
 * CSE1_Oculus_gesture.h
 *
 * Code generation for model "CSE1_Oculus_gesture".
 *
 * Model version              : 1.30
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Thu Apr 23 10:29:55 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_CSE1_Oculus_gesture_h_
#define RTW_HEADER_CSE1_Oculus_gesture_h_
#include <stddef.h>
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef CSE1_Oculus_gesture_COMMON_INCLUDES_
# define CSE1_Oculus_gesture_COMMON_INCLUDES_
#include <stdio.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* CSE1_Oculus_gesture_COMMON_INCLUDES_ */

#include "CSE1_Oculus_gesture_types.h"

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
# define rtmGetFirstInitCondFlag(rtm)  ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ((rtm)->Timing.firstInitCondFlag = (val))
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

#ifndef rtmSetFirstInitCond
# define rtmSetFirstInitCond(rtm, val) ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmIsFirstInitCond
# define rtmIsFirstInitCond(rtm)       ((rtm)->Timing.firstInitCondFlag)
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
#define CSE1_Oculus_gesture_rtModel    RT_MODEL_CSE1_Oculus_gesture_T

/* Block signals for system '<S14>/w_d*w_d' */
typedef struct {
  real_T y[9];                         /* '<S14>/w_d*w_d' */
} B_w_dw_d_CSE1_Oculus_gesture_T;

/* Block signals for system '<S14>/w_d*w_d1' */
typedef struct {
  real_T y[9];                         /* '<S14>/w_d*w_d1' */
} B_w_dw_d1_CSE1_Oculus_gesture_T;

/* Block signals for system '<S14>/w_d^-2' */
typedef struct {
  real_T y[9];                         /* '<S14>/w_d^-2' */
} B_w_d2_CSE1_Oculus_gesture_T;

/* Block signals for system '<S14>/w_d^3' */
typedef struct {
  real_T y[9];                         /* '<S14>/w_d^3' */
} B_w_d3_CSE1_Oculus_gesture_T;

/* Block signals for system '<S29>/MATLAB Function' */
typedef struct {
  real_T K_p[9];                       /* '<S29>/MATLAB Function' */
} B_MATLABFunction_CSE1_Oculus__T;

/* Block signals for system '<S40>/diag' */
typedef struct {
  real_T w_d[9];                       /* '<S40>/diag' */
} B_diag_CSE1_Oculus_gesture_T;

/* Block signals for system '<S40>/diag1' */
typedef struct {
  real_T Zeta[9];                      /* '<S40>/diag1' */
} B_diag1_CSE1_Oculus_gesture_T;

/* Block signals for system '<S5>/diag2vector' */
typedef struct {
  real_T y[3];                         /* '<S5>/diag2vector' */
} B_diag2vector_CSE1_Oculus_ges_T;

/* Block signals (auto storage) */
typedef struct {
  real_T Triangle;                     /* '<S68>/Triangle' */
  real_T Circle;                       /* '<S68>/Circle' */
  real_T Cross;                        /* '<S68>/Cross' */
  real_T Square;                       /* '<S68>/Square' */
  real_T Memory;                       /* '<S62>/Memory' */
  real_T K_p_x;                        /* '<S29>/K_p_x' */
  real_T K_p_y;                        /* '<S29>/K_p_y' */
  real_T K_p_psi;                      /* '<S29>/K_p_psi' */
  real_T K_i_psi;                      /* '<S29>/K_i_psi' */
  real_T K_i_x;                        /* '<S29>/K_i_x' */
  real_T K_i_y;                        /* '<S29>/K_i_y' */
  real_T K_d_psi;                      /* '<S29>/K_d_psi' */
  real_T K_d_x;                        /* '<S29>/K_d_x' */
  real_T K_d_y;                        /* '<S29>/K_d_y' */
  real_T psi;                          /* '<S3>/psi' */
  real_T Sum;                          /* '<S34>/Sum' */
  real_T reset;                        /* '<S3>/reset' */
  real_T Filter1;                      /* '<S32>/Filter 1' */
  real_T Filter2;                      /* '<S32>/Filter 2' */
  real_T Filter3;                      /* '<S32>/Filter 3' */
  real_T VSP_on;                       /* '<S3>/VSP_on' */
  real_T zeta_y;                       /* '<S40>/zeta_y' */
  real_T w_d_psi;                      /* '<S40>/w_d_psi' */
  real_T w_d_x;                        /* '<S40>/w_d_x' */
  real_T w_d_y;                        /* '<S40>/w_d_y' */
  real_T zeta_psi;                     /* '<S40>/zeta_psi' */
  real_T zeta_x;                       /* '<S40>/zeta_x' */
  real_T Oculus_ref_on_off;            /* '<S3>/Oculus_ref_on_off' */
  real_T psi_ref;                      /* '<S3>/psi_ref' */
  real_T Oculus_yaw;                   /* '<S3>/Oculus_yaw' */
  real_T x_ref;                        /* '<S3>/x_ref' */
  real_T y_ref;                        /* '<S3>/y_ref' */
  real_T x;                            /* '<S3>/x' */
  real_T y;                            /* '<S3>/y' */
  real_T Gesture_off;                  /* '<S3>/Gesture_off' */
  real_T Gain3;                        /* '<S33>/Gain3' */
  real_T zeta_y_k;                     /* '<S41>/zeta_y' */
  real_T w_d_psi_d;                    /* '<S41>/w_d_psi' */
  real_T w_d_x_l;                      /* '<S41>/w_d_x' */
  real_T w_d_y_c;                      /* '<S41>/w_d_y' */
  real_T zeta_psi_i;                   /* '<S41>/zeta_psi' */
  real_T zeta_x_m;                     /* '<S41>/zeta_x' */
  real_T K_u;                          /* '<S30>/K_u' */
  real_T K_v;                          /* '<S30>/K_v' */
  real_T K_r;                          /* '<S30>/K_r' */
  real_T Oculus_roll;                  /* '<S3>/Oculus_roll' */
  real_T Gain1;                        /* '<S33>/Gain1' */
  real_T Oculus_pitch;                 /* '<S3>/Oculus_pitch' */
  real_T Row1;                         /* '<S17>/Row1' */
  real_T Row2;                         /* '<S17>/Row2' */
  real_T Row3;                         /* '<S17>/Row3' */
  real_T Integrator1[3];               /* '<S18>/Integrator1' */
  real_T Integrator3[3];               /* '<S14>/Integrator3' */
  real_T MultiportSwitch[6];           /* '<S2>/Multiport Switch' */
  real_T Sum_p;                        /* '<S20>/Sum' */
  real_T TmpSignalConversionAtMatrixMult[3];/* '<S8>/Transposed rotation  matrix in yaw1' */
  real_T Delay[3];                     /* '<S46>/Delay' */
  real_T Memory3[3];                   /* '<S46>/Memory3' */
  real_T Sum1[3];                      /* '<S8>/Sum1' */
  real_T u_BT;                         /* '<S65>/u_BT' */
  real_T u_VSP2;                       /* '<S65>/u_VSP2' */
  real_T omega_VSP1;                   /* '<S65>/omega_VSP1' */
  real_T omega_VSP2;                   /* '<S65>/omega_VSP2' */
  real_T u_VSP1;                       /* '<S65>/u_VSP1' */
  real_T alpha_VSP1;                   /* '<S65>/alpha_VSP1' */
  real_T alpha_VSP2;                   /* '<S65>/alpha_VSP2' */
  real_T u_BT_c;                       /* '<S64>/u_BT' */
  real_T u_VSP2_c;                     /* '<S64>/u_VSP2' */
  real_T omega_VSP1_a;                 /* '<S64>/omega_VSP1' */
  real_T omega_VSP2_f;                 /* '<S64>/omega_VSP2' */
  real_T u_VSP1_d;                     /* '<S64>/u_VSP1' */
  real_T alpha_VSP1_i;                 /* '<S64>/alpha_VSP1' */
  real_T alpha_VSP2_f;                 /* '<S64>/alpha_VSP2' */
  real_T u_BT_f;                       /* '<S66>/u_BT' */
  real_T u_VSP2_o;                     /* '<S66>/u_VSP2' */
  real_T omega_VSP1_k;                 /* '<S66>/omega_VSP1' */
  real_T omega_VSP2_b;                 /* '<S66>/omega_VSP2' */
  real_T u_VSP1_g;                     /* '<S66>/u_VSP1' */
  real_T alpha_VSP1_o;                 /* '<S66>/alpha_VSP1' */
  real_T alpha_VSP2_f2;                /* '<S66>/alpha_VSP2' */
  real_T Saturation4;                  /* '<S7>/Saturation4' */
  real_T Saturation;                   /* '<S7>/Saturation' */
  real_T Saturation1;                  /* '<S7>/Saturation1' */
  real_T Saturation2;                  /* '<S7>/Saturation2' */
  real_T Saturation3;                  /* '<S7>/Saturation3' */
  real_T Saturation5;                  /* '<S7>/Saturation5' */
  real_T Saturation6;                  /* '<S7>/Saturation6' */
  real_T MultiportSwitch_o;            /* '<S3>/Multiport Switch' */
  real_T MatrixMultiply[3];            /* '<S14>/Matrix Multiply' */
  real_T Sum5[3];                      /* '<S14>/Sum5' */
  real_T Integrator3_o[3];             /* '<S18>/Integrator3' */
  real_T Gain2;                        /* '<S33>/Gain2' */
  real_T MatrixMultiply_k[3];          /* '<S30>/Matrix Multiply' */
  real_T MatrixMultiply_n[3];          /* '<S18>/Matrix Multiply' */
  real_T Sum5_o[3];                    /* '<S18>/Sum5' */
  real_T Sum_a;                        /* '<S60>/Sum' */
  real_T switch_signal;                /* '<S62>/Switch_function' */
  real_T u_BT_j;                       /* '<S6>/Thrust allocation' */
  real_T u_VSP;                        /* '<S6>/Thrust allocation' */
  real_T alpha_VSP;                    /* '<S6>/Thrust allocation' */
  real_T nu[3];                        /* '<S46>/MATLAB Function3' */
  real_T eta_dot_filtered[3];          /* '<S46>/MATLAB Function2' */
  real_T eta_filtered[3];              /* '<S46>/MATLAB Function' */
  boolean_T ctrl_student;              /* '<S67>/C' */
  boolean_T ctrl_DP_basic;             /* '<S67>/C' */
  boolean_T ctrl_sixaxis2force;        /* '<S67>/C' */
  boolean_T ctrl_sixaxis2thruster;     /* '<S67>/C' */
  boolean_T fault;                     /* '<S7>/control limit checking' */
  B_diag2vector_CSE1_Oculus_ges_T sf_diag2vector4;/* '<S5>/diag2vector4' */
  B_diag2vector_CSE1_Oculus_ges_T sf_diag2vector3;/* '<S5>/diag2vector3' */
  B_diag2vector_CSE1_Oculus_ges_T sf_diag2vector2;/* '<S5>/diag2vector2' */
  B_diag2vector_CSE1_Oculus_ges_T sf_diag2vector1;/* '<S5>/diag2vector1' */
  B_diag2vector_CSE1_Oculus_ges_T sf_diag2vector;/* '<S5>/diag2vector' */
  B_diag1_CSE1_Oculus_gesture_T sf_diag1_j;/* '<S41>/diag1' */
  B_diag_CSE1_Oculus_gesture_T sf_diag_j;/* '<S41>/diag' */
  B_diag1_CSE1_Oculus_gesture_T sf_diag1;/* '<S40>/diag1' */
  B_diag_CSE1_Oculus_gesture_T sf_diag;/* '<S40>/diag' */
  B_MATLABFunction_CSE1_Oculus__T sf_MATLABFunction4;/* '<S30>/MATLAB Function4' */
  B_MATLABFunction_CSE1_Oculus__T sf_MATLABFunction;/* '<S29>/MATLAB Function' */
  B_w_d3_CSE1_Oculus_gesture_T sf_w_d3_f;/* '<S18>/w_d^3' */
  B_w_d2_CSE1_Oculus_gesture_T sf_w_d2_d;/* '<S18>/w_d^-2' */
  B_w_dw_d1_CSE1_Oculus_gesture_T sf_w_dw_d1_f;/* '<S18>/w_d*w_d1' */
  B_w_dw_d_CSE1_Oculus_gesture_T sf_w_dw_d_f;/* '<S18>/w_d*w_d' */
  B_w_d3_CSE1_Oculus_gesture_T sf_w_d3;/* '<S14>/w_d^3' */
  B_w_d2_CSE1_Oculus_gesture_T sf_w_d2;/* '<S14>/w_d^-2' */
  B_w_dw_d1_CSE1_Oculus_gesture_T sf_w_dw_d1;/* '<S14>/w_d*w_d1' */
  B_w_dw_d_CSE1_Oculus_gesture_T sf_w_dw_d;/* '<S14>/w_d*w_d' */
} B_CSE1_Oculus_gesture_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE[3];              /* '<S46>/Delay' */
  real_T Triangle_DWORK1;              /* '<S68>/Triangle' */
  real_T Circle_DWORK1;                /* '<S68>/Circle' */
  real_T Cross_DWORK1;                 /* '<S68>/Cross' */
  real_T Square_DWORK1;                /* '<S68>/Square' */
  real_T Memory_PreviousInput;         /* '<S62>/Memory' */
  real_T K_p_x_DWORK1;                 /* '<S29>/K_p_x' */
  real_T K_p_y_DWORK1;                 /* '<S29>/K_p_y' */
  real_T K_p_psi_DWORK1;               /* '<S29>/K_p_psi' */
  real_T K_i_psi_DWORK1;               /* '<S29>/K_i_psi' */
  real_T K_i_x_DWORK1;                 /* '<S29>/K_i_x' */
  real_T K_i_y_DWORK1;                 /* '<S29>/K_i_y' */
  real_T K_d_psi_DWORK1;               /* '<S29>/K_d_psi' */
  real_T K_d_x_DWORK1;                 /* '<S29>/K_d_x' */
  real_T K_d_y_DWORK1;                 /* '<S29>/K_d_y' */
  real_T psi_DWORK1;                   /* '<S3>/psi' */
  real_T reset_DWORK1;                 /* '<S3>/reset' */
  real_T Filter1_DWORK1;               /* '<S32>/Filter 1' */
  real_T Filter2_DWORK1;               /* '<S32>/Filter 2' */
  real_T Filter3_DWORK1;               /* '<S32>/Filter 3' */
  real_T VSP_on_DWORK1;                /* '<S3>/VSP_on' */
  real_T zeta_y_DWORK1;                /* '<S40>/zeta_y' */
  real_T w_d_psi_DWORK1;               /* '<S40>/w_d_psi' */
  real_T w_d_x_DWORK1;                 /* '<S40>/w_d_x' */
  real_T w_d_y_DWORK1;                 /* '<S40>/w_d_y' */
  real_T zeta_psi_DWORK1;              /* '<S40>/zeta_psi' */
  real_T zeta_x_DWORK1;                /* '<S40>/zeta_x' */
  real_T Oculus_ref_on_off_DWORK1;     /* '<S3>/Oculus_ref_on_off' */
  real_T psi_ref_DWORK1;               /* '<S3>/psi_ref' */
  real_T Oculus_yaw_DWORK1;            /* '<S3>/Oculus_yaw' */
  real_T x_ref_DWORK1;                 /* '<S3>/x_ref' */
  real_T y_ref_DWORK1;                 /* '<S3>/y_ref' */
  real_T x_DWORK1;                     /* '<S3>/x' */
  real_T y_DWORK1;                     /* '<S3>/y' */
  real_T Gesture_off_DWORK1;           /* '<S3>/Gesture_off' */
  real_T zeta_y_DWORK1_a;              /* '<S41>/zeta_y' */
  real_T w_d_psi_DWORK1_h;             /* '<S41>/w_d_psi' */
  real_T w_d_x_DWORK1_p;               /* '<S41>/w_d_x' */
  real_T w_d_y_DWORK1_g;               /* '<S41>/w_d_y' */
  real_T zeta_psi_DWORK1_b;            /* '<S41>/zeta_psi' */
  real_T zeta_x_DWORK1_p;              /* '<S41>/zeta_x' */
  real_T K_u_DWORK1;                   /* '<S30>/K_u' */
  real_T K_v_DWORK1;                   /* '<S30>/K_v' */
  real_T K_r_DWORK1;                   /* '<S30>/K_r' */
  real_T Oculus_roll_DWORK1;           /* '<S3>/Oculus_roll' */
  real_T Oculus_pitch_DWORK1;          /* '<S3>/Oculus_pitch' */
  real_T Memory3_PreviousInput[3];     /* '<S46>/Memory3' */
  real_T u_BT_DWORK1;                  /* '<S65>/u_BT' */
  real_T u_VSP2_DWORK1;                /* '<S65>/u_VSP2' */
  real_T omega_VSP1_DWORK1;            /* '<S65>/omega_VSP1' */
  real_T omega_VSP2_DWORK1;            /* '<S65>/omega_VSP2' */
  real_T u_VSP1_DWORK1;                /* '<S65>/u_VSP1' */
  real_T alpha_VSP1_DWORK1;            /* '<S65>/alpha_VSP1' */
  real_T alpha_VSP2_DWORK1;            /* '<S65>/alpha_VSP2' */
  real_T u_BT_DWORK1_j;                /* '<S64>/u_BT' */
  real_T u_VSP2_DWORK1_b;              /* '<S64>/u_VSP2' */
  real_T omega_VSP1_DWORK1_b;          /* '<S64>/omega_VSP1' */
  real_T omega_VSP2_DWORK1_k;          /* '<S64>/omega_VSP2' */
  real_T u_VSP1_DWORK1_e;              /* '<S64>/u_VSP1' */
  real_T alpha_VSP1_DWORK1_b;          /* '<S64>/alpha_VSP1' */
  real_T alpha_VSP2_DWORK1_i;          /* '<S64>/alpha_VSP2' */
  real_T u_BT_DWORK1_l;                /* '<S66>/u_BT' */
  real_T u_VSP2_DWORK1_m;              /* '<S66>/u_VSP2' */
  real_T omega_VSP1_DWORK1_h;          /* '<S66>/omega_VSP1' */
  real_T omega_VSP2_DWORK1_o;          /* '<S66>/omega_VSP2' */
  real_T u_VSP1_DWORK1_h;              /* '<S66>/u_VSP1' */
  real_T alpha_VSP1_DWORK1_p;          /* '<S66>/alpha_VSP1' */
  real_T alpha_VSP2_DWORK1_n;          /* '<S66>/alpha_VSP2' */
  real_T alpha_VSP2_DWORK1_l;          /* '<S7>/alpha_VSP2' */
  real_T u_BT_DWORK1_f;                /* '<S7>/u_BT' */
  real_T u_VSP1_DWORK1_hn;             /* '<S7>/u_VSP1' */
  real_T u_VSP2_DWORK1_o;              /* '<S7>/u_VSP2' */
  real_T alpha_VSP1_DWORK1_f;          /* '<S7>/alpha_VSP1' */
  real_T omega_VSP1_DWORK1_l;          /* '<S7>/omega_VSP1' */
  real_T omega_VSP2_DWORK1_d;          /* '<S7>/omega_VSP2' */
  real_T controlinputuexceedsbounds_DWOR;/* '<S7>/control input u exceeds bounds' */
  real_T ctrl_DP_basic_DWORK1;         /* '<S67>/ctrl_DP_basic' */
  real_T ctrl_sixaxis2force_DWORK1;    /* '<S67>/ctrl_sixaxis2force' */
  real_T ctrl_sixaxis2thruster_DWORK1; /* '<S67>/ctrl_sixaxis2thruster' */
  real_T ctrl_student_DWORK1;          /* '<S67>/ctrl_student' */
  real_T tau_N_DWORK1;                 /* '<S51>/tau_N' */
  real_T tau_X_DWORK1;                 /* '<S51>/tau_X' */
  real_T tau_Y_DWORK1;                 /* '<S51>/tau_Y' */
  real_T x_d_DWORK1;                   /* '<S52>/x_d' */
  real_T y_d_DWORK1;                   /* '<S52>/y_d' */
  real_T psi_d_DWORK1;                 /* '<S52>/psi_d' */
  real_T r_d_DWORK1;                   /* '<S52>/r_d' */
  real_T u_d_DWORK1;                   /* '<S52>/u_d' */
  real_T v_d_DWORK1;                   /* '<S52>/v_d' */
  real_T r_oculus_DWORK1;              /* '<S52>/r_oculus' */
  real_T u_oculus_DWORK1;              /* '<S52>/u_oculus' */
  real_T v_oculus_DWORK1;              /* '<S52>/v_oculus' */
  real_T r_hat_DWORK1;                 /* '<S53>/r_hat' */
  real_T u_hat_DWORK1;                 /* '<S53>/u_hat' */
  real_T v_hat_DWORK1;                 /* '<S53>/v_hat' */
  real_T x_DWORK1_m;                   /* '<S54>/x' */
  real_T y_DWORK1_c;                   /* '<S54>/y' */
  real_T psi_DWORK1_o;                 /* '<S54>/psi' */
  struct {
    void *FilePtr;
  } ToFile_PWORK;                      /* '<S5>/To File' */

  struct {
    void *FilePtr;
  } tau_PWORK;                         /* '<S51>/tau' */

  struct {
    void *FilePtr;
  } eta3_PWORK;                        /* '<S51>/eta3' */

  struct {
    void *FilePtr;
  } eta1_PWORK;                        /* '<S52>/eta1' */

  struct {
    void *FilePtr;
  } eta3_PWORK_p;                      /* '<S52>/eta3' */

  struct {
    void *FilePtr;
  } eta5_PWORK;                        /* '<S52>/eta5' */

  struct {
    void *FilePtr;
  } eta4_PWORK;                        /* '<S52>/eta4' */

  struct {
    void *FilePtr;
  } eta2_PWORK;                        /* '<S52>/eta2' */

  struct {
    void *FilePtr;
  } nu1_PWORK;                         /* '<S52>/nu 1' */

  struct {
    void *FilePtr;
  } nu_dot1_PWORK;                     /* '<S52>/nu_dot1' */

  struct {
    void *FilePtr;
  } nu_hat_PWORK;                      /* '<S53>/nu_hat ' */

  struct {
    void *FilePtr;
  } eta_PWORK;                         /* '<S54>/eta' */

  int32_T NIVeriStandSignalProbe_DWORK2;/* '<Root>/NIVeriStandSignalProbe' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S2>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S14>/Integrator1' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<S5>/To File' */

  struct {
    int_T Count;
    int_T Decimation;
  } tau_IWORK;                         /* '<S51>/tau' */

  struct {
    int_T Count;
    int_T Decimation;
  } eta3_IWORK;                        /* '<S51>/eta3' */

  struct {
    int_T Count;
    int_T Decimation;
  } eta1_IWORK;                        /* '<S52>/eta1' */

  struct {
    int_T Count;
    int_T Decimation;
  } eta3_IWORK_a;                      /* '<S52>/eta3' */

  struct {
    int_T Count;
    int_T Decimation;
  } eta5_IWORK;                        /* '<S52>/eta5' */

  struct {
    int_T Count;
    int_T Decimation;
  } eta4_IWORK;                        /* '<S52>/eta4' */

  struct {
    int_T Count;
    int_T Decimation;
  } eta2_IWORK;                        /* '<S52>/eta2' */

  struct {
    int_T Count;
    int_T Decimation;
  } nu1_IWORK;                         /* '<S52>/nu 1' */

  struct {
    int_T Count;
    int_T Decimation;
  } nu_dot1_IWORK;                     /* '<S52>/nu_dot1' */

  struct {
    int_T Count;
    int_T Decimation;
  } nu_hat_IWORK;                      /* '<S53>/nu_hat ' */

  struct {
    int_T Count;
    int_T Decimation;
  } eta_IWORK;                         /* '<S54>/eta' */

  uint8_T Triangle_DWORK2[20];         /* '<S68>/Triangle' */
  uint8_T Circle_DWORK2[20];           /* '<S68>/Circle' */
  uint8_T Cross_DWORK2[20];            /* '<S68>/Cross' */
  uint8_T Square_DWORK2[20];           /* '<S68>/Square' */
  uint8_T K_p_x_DWORK2[20];            /* '<S29>/K_p_x' */
  uint8_T K_p_y_DWORK2[20];            /* '<S29>/K_p_y' */
  uint8_T K_p_psi_DWORK2[20];          /* '<S29>/K_p_psi' */
  uint8_T K_i_psi_DWORK2[20];          /* '<S29>/K_i_psi' */
  uint8_T K_i_x_DWORK2[20];            /* '<S29>/K_i_x' */
  uint8_T K_i_y_DWORK2[20];            /* '<S29>/K_i_y' */
  uint8_T K_d_psi_DWORK2[20];          /* '<S29>/K_d_psi' */
  uint8_T K_d_x_DWORK2[20];            /* '<S29>/K_d_x' */
  uint8_T K_d_y_DWORK2[20];            /* '<S29>/K_d_y' */
  uint8_T psi_DWORK2[20];              /* '<S3>/psi' */
  uint8_T reset_DWORK2[20];            /* '<S3>/reset' */
  uint8_T Filter1_DWORK2[20];          /* '<S32>/Filter 1' */
  uint8_T Filter2_DWORK2[20];          /* '<S32>/Filter 2' */
  uint8_T Filter3_DWORK2[20];          /* '<S32>/Filter 3' */
  uint8_T VSP_on_DWORK2[20];           /* '<S3>/VSP_on' */
  uint8_T zeta_y_DWORK2[20];           /* '<S40>/zeta_y' */
  uint8_T w_d_psi_DWORK2[20];          /* '<S40>/w_d_psi' */
  uint8_T w_d_x_DWORK2[20];            /* '<S40>/w_d_x' */
  uint8_T w_d_y_DWORK2[20];            /* '<S40>/w_d_y' */
  uint8_T zeta_psi_DWORK2[20];         /* '<S40>/zeta_psi' */
  uint8_T zeta_x_DWORK2[20];           /* '<S40>/zeta_x' */
  uint8_T Oculus_ref_on_off_DWORK2[20];/* '<S3>/Oculus_ref_on_off' */
  uint8_T psi_ref_DWORK2[20];          /* '<S3>/psi_ref' */
  uint8_T Oculus_yaw_DWORK2[20];       /* '<S3>/Oculus_yaw' */
  uint8_T x_ref_DWORK2[20];            /* '<S3>/x_ref' */
  uint8_T y_ref_DWORK2[20];            /* '<S3>/y_ref' */
  uint8_T x_DWORK2[20];                /* '<S3>/x' */
  uint8_T y_DWORK2[20];                /* '<S3>/y' */
  uint8_T Gesture_off_DWORK2[20];      /* '<S3>/Gesture_off' */
  uint8_T zeta_y_DWORK2_c[20];         /* '<S41>/zeta_y' */
  uint8_T w_d_psi_DWORK2_h[20];        /* '<S41>/w_d_psi' */
  uint8_T w_d_x_DWORK2_b[20];          /* '<S41>/w_d_x' */
  uint8_T w_d_y_DWORK2_b[20];          /* '<S41>/w_d_y' */
  uint8_T zeta_psi_DWORK2_e[20];       /* '<S41>/zeta_psi' */
  uint8_T zeta_x_DWORK2_g[20];         /* '<S41>/zeta_x' */
  uint8_T K_u_DWORK2[20];              /* '<S30>/K_u' */
  uint8_T K_v_DWORK2[20];              /* '<S30>/K_v' */
  uint8_T K_r_DWORK2[20];              /* '<S30>/K_r' */
  uint8_T Oculus_roll_DWORK2[20];      /* '<S3>/Oculus_roll' */
  uint8_T Oculus_pitch_DWORK2[20];     /* '<S3>/Oculus_pitch' */
  uint8_T icLoad;                      /* '<S46>/Delay' */
  uint8_T u_BT_DWORK2[20];             /* '<S65>/u_BT' */
  uint8_T u_VSP2_DWORK2[20];           /* '<S65>/u_VSP2' */
  uint8_T omega_VSP1_DWORK2[20];       /* '<S65>/omega_VSP1' */
  uint8_T omega_VSP2_DWORK2[20];       /* '<S65>/omega_VSP2' */
  uint8_T u_VSP1_DWORK2[20];           /* '<S65>/u_VSP1' */
  uint8_T alpha_VSP1_DWORK2[20];       /* '<S65>/alpha_VSP1' */
  uint8_T alpha_VSP2_DWORK2[20];       /* '<S65>/alpha_VSP2' */
  uint8_T u_BT_DWORK2_k[20];           /* '<S64>/u_BT' */
  uint8_T u_VSP2_DWORK2_c[20];         /* '<S64>/u_VSP2' */
  uint8_T omega_VSP1_DWORK2_c[20];     /* '<S64>/omega_VSP1' */
  uint8_T omega_VSP2_DWORK2_p[20];     /* '<S64>/omega_VSP2' */
  uint8_T u_VSP1_DWORK2_k[20];         /* '<S64>/u_VSP1' */
  uint8_T alpha_VSP1_DWORK2_a[20];     /* '<S64>/alpha_VSP1' */
  uint8_T alpha_VSP2_DWORK2_n[20];     /* '<S64>/alpha_VSP2' */
  uint8_T u_BT_DWORK2_b[20];           /* '<S66>/u_BT' */
  uint8_T u_VSP2_DWORK2_o[20];         /* '<S66>/u_VSP2' */
  uint8_T omega_VSP1_DWORK2_a[20];     /* '<S66>/omega_VSP1' */
  uint8_T omega_VSP2_DWORK2_k[20];     /* '<S66>/omega_VSP2' */
  uint8_T u_VSP1_DWORK2_f[20];         /* '<S66>/u_VSP1' */
  uint8_T alpha_VSP1_DWORK2_b[20];     /* '<S66>/alpha_VSP1' */
  uint8_T alpha_VSP2_DWORK2_c[20];     /* '<S66>/alpha_VSP2' */
  uint8_T alpha_VSP2_DWORK2_n5[20];    /* '<S7>/alpha_VSP2' */
  uint8_T u_BT_DWORK2_l[20];           /* '<S7>/u_BT' */
  uint8_T u_VSP1_DWORK2_h[20];         /* '<S7>/u_VSP1' */
  uint8_T u_VSP2_DWORK2_cb[20];        /* '<S7>/u_VSP2' */
  uint8_T alpha_VSP1_DWORK2_f[20];     /* '<S7>/alpha_VSP1' */
  uint8_T omega_VSP1_DWORK2_f[20];     /* '<S7>/omega_VSP1' */
  uint8_T omega_VSP2_DWORK2_d[20];     /* '<S7>/omega_VSP2' */
  uint8_T controlinputuexceedsbounds_DW_f[20];/* '<S7>/control input u exceeds bounds' */
  uint8_T ctrl_DP_basic_DWORK2[20];    /* '<S67>/ctrl_DP_basic' */
  uint8_T ctrl_sixaxis2force_DWORK2[20];/* '<S67>/ctrl_sixaxis2force' */
  uint8_T ctrl_sixaxis2thruster_DWORK2[20];/* '<S67>/ctrl_sixaxis2thruster' */
  uint8_T ctrl_student_DWORK2[20];     /* '<S67>/ctrl_student' */
  uint8_T tau_N_DWORK2[20];            /* '<S51>/tau_N' */
  uint8_T tau_X_DWORK2[20];            /* '<S51>/tau_X' */
  uint8_T tau_Y_DWORK2[20];            /* '<S51>/tau_Y' */
  uint8_T x_d_DWORK2[20];              /* '<S52>/x_d' */
  uint8_T y_d_DWORK2[20];              /* '<S52>/y_d' */
  uint8_T psi_d_DWORK2[20];            /* '<S52>/psi_d' */
  uint8_T r_d_DWORK2[20];              /* '<S52>/r_d' */
  uint8_T u_d_DWORK2[20];              /* '<S52>/u_d' */
  uint8_T v_d_DWORK2[20];              /* '<S52>/v_d' */
  uint8_T r_oculus_DWORK2[20];         /* '<S52>/r_oculus' */
  uint8_T u_oculus_DWORK2[20];         /* '<S52>/u_oculus' */
  uint8_T v_oculus_DWORK2[20];         /* '<S52>/v_oculus' */
  uint8_T r_hat_DWORK2[20];            /* '<S53>/r_hat' */
  uint8_T u_hat_DWORK2[20];            /* '<S53>/u_hat' */
  uint8_T v_hat_DWORK2[20];            /* '<S53>/v_hat' */
  uint8_T x_DWORK2_f[20];              /* '<S54>/x' */
  uint8_T y_DWORK2_i[20];              /* '<S54>/y' */
  uint8_T psi_DWORK2_o[20];            /* '<S54>/psi' */
  uint8_T NIVeriStandSignalProbe_DWORK1[20];/* '<Root>/NIVeriStandSignalProbe' */
  uint8_T NIVeriStandSignalProbe_DWORK3[63];/* '<Root>/NIVeriStandSignalProbe' */
} DW_CSE1_Oculus_gesture_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S18>/Integrator1' */
  real_T Integrator1_CSTATE_j[3];      /* '<S14>/Integrator1' */
  real_T Integrator3_CSTATE[3];        /* '<S14>/Integrator3' */
  real_T Integrator_CSTATE_i[3];       /* '<S8>/Integrator' */
  real_T Integrator2_CSTATE[3];        /* '<S14>/Integrator2' */
  real_T Integrator2_CSTATE_b[3];      /* '<S18>/Integrator2' */
  real_T Integrator3_CSTATE_f[3];      /* '<S18>/Integrator3' */
} X_CSE1_Oculus_gesture_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S18>/Integrator1' */
  real_T Integrator1_CSTATE_j[3];      /* '<S14>/Integrator1' */
  real_T Integrator3_CSTATE[3];        /* '<S14>/Integrator3' */
  real_T Integrator_CSTATE_i[3];       /* '<S8>/Integrator' */
  real_T Integrator2_CSTATE[3];        /* '<S14>/Integrator2' */
  real_T Integrator2_CSTATE_b[3];      /* '<S18>/Integrator2' */
  real_T Integrator3_CSTATE_f[3];      /* '<S18>/Integrator3' */
} XDot_CSE1_Oculus_gesture_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S2>/Integrator' */
  boolean_T Integrator1_CSTATE[3];     /* '<S18>/Integrator1' */
  boolean_T Integrator1_CSTATE_j[3];   /* '<S14>/Integrator1' */
  boolean_T Integrator3_CSTATE[3];     /* '<S14>/Integrator3' */
  boolean_T Integrator_CSTATE_i[3];    /* '<S8>/Integrator' */
  boolean_T Integrator2_CSTATE[3];     /* '<S14>/Integrator2' */
  boolean_T Integrator2_CSTATE_b[3];   /* '<S18>/Integrator2' */
  boolean_T Integrator3_CSTATE_f[3];   /* '<S18>/Integrator3' */
} XDis_CSE1_Oculus_gesture_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S2>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S18>/Integrator1' */
  ZCSigState Integrator1_Reset_ZCE_g;  /* '<S14>/Integrator1' */
  ZCSigState Integrator3_Reset_ZCE;    /* '<S14>/Integrator3' */
  ZCSigState Integrator_Reset_ZCE_h;   /* '<S8>/Integrator' */
  ZCSigState Integrator2_Reset_ZCE;    /* '<S14>/Integrator2' */
  ZCSigState Integrator2_Reset_ZCE_p;  /* '<S18>/Integrator2' */
  ZCSigState Integrator3_Reset_ZCE_h;  /* '<S18>/Integrator3' */
} PrevZCX_CSE1_Oculus_gesture_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            CSE1_Oculus_gesture_B
#define BlockIO                        B_CSE1_Oculus_gesture_T
#define rtX                            CSE1_Oculus_gesture_X
#define ContinuousStates               X_CSE1_Oculus_gesture_T
#define rtXdot                         CSE1_Oculus_gesture_XDot
#define StateDerivatives               XDot_CSE1_Oculus_gesture_T
#define tXdis                          CSE1_Oculus_gesture_XDis
#define StateDisabled                  XDis_CSE1_Oculus_gesture_T
#define rtP                            CSE1_Oculus_gesture_P
#define Parameters                     P_CSE1_Oculus_gesture_T
#define rtDWork                        CSE1_Oculus_gesture_DW
#define D_Work                         DW_CSE1_Oculus_gesture_T
#define rtPrevZCSigState               CSE1_Oculus_gesture_PrevZCX
#define PrevZCSigStates                PrevZCX_CSE1_Oculus_gesture_T

/* Parameters (auto storage) */
struct P_CSE1_Oculus_gesture_T_ {
  real_T Triangle_P1;                  /* Expression: width
                                        * Referenced by: '<S68>/Triangle'
                                        */
  real_T Triangle_P2;                  /* Expression: dtype
                                        * Referenced by: '<S68>/Triangle'
                                        */
  real_T Triangle_P3;                  /* Expression: portnum
                                        * Referenced by: '<S68>/Triangle'
                                        */
  real_T Triangle_P4;                  /* Expression: stime
                                        * Referenced by: '<S68>/Triangle'
                                        */
  real_T Triangle_P5;                  /* Expression: stype
                                        * Referenced by: '<S68>/Triangle'
                                        */
  real_T Triangle_P6;                  /* Expression: btype
                                        * Referenced by: '<S68>/Triangle'
                                        */
  real_T Circle_P1;                    /* Expression: width
                                        * Referenced by: '<S68>/Circle'
                                        */
  real_T Circle_P2;                    /* Expression: dtype
                                        * Referenced by: '<S68>/Circle'
                                        */
  real_T Circle_P3;                    /* Expression: portnum
                                        * Referenced by: '<S68>/Circle'
                                        */
  real_T Circle_P4;                    /* Expression: stime
                                        * Referenced by: '<S68>/Circle'
                                        */
  real_T Circle_P5;                    /* Expression: stype
                                        * Referenced by: '<S68>/Circle'
                                        */
  real_T Circle_P6;                    /* Expression: btype
                                        * Referenced by: '<S68>/Circle'
                                        */
  real_T Cross_P1;                     /* Expression: width
                                        * Referenced by: '<S68>/Cross'
                                        */
  real_T Cross_P2;                     /* Expression: dtype
                                        * Referenced by: '<S68>/Cross'
                                        */
  real_T Cross_P3;                     /* Expression: portnum
                                        * Referenced by: '<S68>/Cross'
                                        */
  real_T Cross_P4;                     /* Expression: stime
                                        * Referenced by: '<S68>/Cross'
                                        */
  real_T Cross_P5;                     /* Expression: stype
                                        * Referenced by: '<S68>/Cross'
                                        */
  real_T Cross_P6;                     /* Expression: btype
                                        * Referenced by: '<S68>/Cross'
                                        */
  real_T Square_P1;                    /* Expression: width
                                        * Referenced by: '<S68>/Square'
                                        */
  real_T Square_P2;                    /* Expression: dtype
                                        * Referenced by: '<S68>/Square'
                                        */
  real_T Square_P3;                    /* Expression: portnum
                                        * Referenced by: '<S68>/Square'
                                        */
  real_T Square_P4;                    /* Expression: stime
                                        * Referenced by: '<S68>/Square'
                                        */
  real_T Square_P5;                    /* Expression: stype
                                        * Referenced by: '<S68>/Square'
                                        */
  real_T Square_P6;                    /* Expression: btype
                                        * Referenced by: '<S68>/Square'
                                        */
  real_T Memory_X0;                    /* Expression: 4
                                        * Referenced by: '<S62>/Memory'
                                        */
  real_T K_p_x_P1;                     /* Expression: width
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  real_T K_p_x_P2;                     /* Expression: dtype
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  real_T K_p_x_P3;                     /* Expression: portnum
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  real_T K_p_x_P4;                     /* Expression: stime
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  real_T K_p_x_P5;                     /* Expression: stype
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  real_T K_p_x_P6;                     /* Expression: btype
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  real_T K_p_y_P1;                     /* Expression: width
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  real_T K_p_y_P2;                     /* Expression: dtype
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  real_T K_p_y_P3;                     /* Expression: portnum
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  real_T K_p_y_P4;                     /* Expression: stime
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  real_T K_p_y_P5;                     /* Expression: stype
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  real_T K_p_y_P6;                     /* Expression: btype
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  real_T K_p_psi_P1;                   /* Expression: width
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  real_T K_p_psi_P2;                   /* Expression: dtype
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  real_T K_p_psi_P3;                   /* Expression: portnum
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  real_T K_p_psi_P4;                   /* Expression: stime
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  real_T K_p_psi_P5;                   /* Expression: stype
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  real_T K_p_psi_P6;                   /* Expression: btype
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  real_T K_i_psi_P1;                   /* Expression: width
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  real_T K_i_psi_P2;                   /* Expression: dtype
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  real_T K_i_psi_P3;                   /* Expression: portnum
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  real_T K_i_psi_P4;                   /* Expression: stime
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  real_T K_i_psi_P5;                   /* Expression: stype
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  real_T K_i_psi_P6;                   /* Expression: btype
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  real_T K_i_x_P1;                     /* Expression: width
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  real_T K_i_x_P2;                     /* Expression: dtype
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  real_T K_i_x_P3;                     /* Expression: portnum
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  real_T K_i_x_P4;                     /* Expression: stime
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  real_T K_i_x_P5;                     /* Expression: stype
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  real_T K_i_x_P6;                     /* Expression: btype
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  real_T K_i_y_P1;                     /* Expression: width
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  real_T K_i_y_P2;                     /* Expression: dtype
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  real_T K_i_y_P3;                     /* Expression: portnum
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  real_T K_i_y_P4;                     /* Expression: stime
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  real_T K_i_y_P5;                     /* Expression: stype
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  real_T K_i_y_P6;                     /* Expression: btype
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  real_T K_d_psi_P1;                   /* Expression: width
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  real_T K_d_psi_P2;                   /* Expression: dtype
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  real_T K_d_psi_P3;                   /* Expression: portnum
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  real_T K_d_psi_P4;                   /* Expression: stime
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  real_T K_d_psi_P5;                   /* Expression: stype
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  real_T K_d_psi_P6;                   /* Expression: btype
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  real_T K_d_x_P1;                     /* Expression: width
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  real_T K_d_x_P2;                     /* Expression: dtype
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  real_T K_d_x_P3;                     /* Expression: portnum
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  real_T K_d_x_P4;                     /* Expression: stime
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  real_T K_d_x_P5;                     /* Expression: stype
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  real_T K_d_x_P6;                     /* Expression: btype
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  real_T K_d_y_P1;                     /* Expression: width
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  real_T K_d_y_P2;                     /* Expression: dtype
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  real_T K_d_y_P3;                     /* Expression: portnum
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  real_T K_d_y_P4;                     /* Expression: stime
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  real_T K_d_y_P5;                     /* Expression: stype
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  real_T K_d_y_P6;                     /* Expression: btype
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  real_T psi_P1;                       /* Expression: width
                                        * Referenced by: '<S3>/psi'
                                        */
  real_T psi_P2;                       /* Expression: dtype
                                        * Referenced by: '<S3>/psi'
                                        */
  real_T psi_P3;                       /* Expression: portnum
                                        * Referenced by: '<S3>/psi'
                                        */
  real_T psi_P4;                       /* Expression: stime
                                        * Referenced by: '<S3>/psi'
                                        */
  real_T psi_P5;                       /* Expression: stype
                                        * Referenced by: '<S3>/psi'
                                        */
  real_T psi_P6;                       /* Expression: btype
                                        * Referenced by: '<S3>/psi'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * Referenced by: '<S34>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * Referenced by: '<S34>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * Referenced by: '<S34>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 2*pi
                                        * Referenced by: '<S34>/Constant'
                                        */
  real_T reset_P1;                     /* Expression: width
                                        * Referenced by: '<S3>/reset'
                                        */
  real_T reset_P2;                     /* Expression: dtype
                                        * Referenced by: '<S3>/reset'
                                        */
  real_T reset_P3;                     /* Expression: portnum
                                        * Referenced by: '<S3>/reset'
                                        */
  real_T reset_P4;                     /* Expression: stime
                                        * Referenced by: '<S3>/reset'
                                        */
  real_T reset_P5;                     /* Expression: stype
                                        * Referenced by: '<S3>/reset'
                                        */
  real_T reset_P6;                     /* Expression: btype
                                        * Referenced by: '<S3>/reset'
                                        */
  real_T Filter1_P1;                   /* Expression: width
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  real_T Filter1_P2;                   /* Expression: dtype
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  real_T Filter1_P3;                   /* Expression: portnum
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  real_T Filter1_P4;                   /* Expression: stime
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  real_T Filter1_P5;                   /* Expression: stype
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  real_T Filter1_P6;                   /* Expression: btype
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  real_T Filter2_P1;                   /* Expression: width
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  real_T Filter2_P2;                   /* Expression: dtype
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  real_T Filter2_P3;                   /* Expression: portnum
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  real_T Filter2_P4;                   /* Expression: stime
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  real_T Filter2_P5;                   /* Expression: stype
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  real_T Filter2_P6;                   /* Expression: btype
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  real_T Filter3_P1;                   /* Expression: width
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  real_T Filter3_P2;                   /* Expression: dtype
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  real_T Filter3_P3;                   /* Expression: portnum
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  real_T Filter3_P4;                   /* Expression: stime
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  real_T Filter3_P5;                   /* Expression: stype
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  real_T Filter3_P6;                   /* Expression: btype
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  real_T VSP_on_P1;                    /* Expression: width
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  real_T VSP_on_P2;                    /* Expression: dtype
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  real_T VSP_on_P3;                    /* Expression: portnum
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  real_T VSP_on_P4;                    /* Expression: stime
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  real_T VSP_on_P5;                    /* Expression: stype
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  real_T VSP_on_P6;                    /* Expression: btype
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  real_T zeta_y_P1;                    /* Expression: width
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  real_T zeta_y_P2;                    /* Expression: dtype
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  real_T zeta_y_P3;                    /* Expression: portnum
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  real_T zeta_y_P4;                    /* Expression: stime
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  real_T zeta_y_P5;                    /* Expression: stype
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  real_T zeta_y_P6;                    /* Expression: btype
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  real_T w_d_psi_P1;                   /* Expression: width
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  real_T w_d_psi_P2;                   /* Expression: dtype
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  real_T w_d_psi_P3;                   /* Expression: portnum
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  real_T w_d_psi_P4;                   /* Expression: stime
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  real_T w_d_psi_P5;                   /* Expression: stype
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  real_T w_d_psi_P6;                   /* Expression: btype
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  real_T w_d_x_P1;                     /* Expression: width
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  real_T w_d_x_P2;                     /* Expression: dtype
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  real_T w_d_x_P3;                     /* Expression: portnum
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  real_T w_d_x_P4;                     /* Expression: stime
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  real_T w_d_x_P5;                     /* Expression: stype
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  real_T w_d_x_P6;                     /* Expression: btype
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  real_T w_d_y_P1;                     /* Expression: width
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  real_T w_d_y_P2;                     /* Expression: dtype
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  real_T w_d_y_P3;                     /* Expression: portnum
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  real_T w_d_y_P4;                     /* Expression: stime
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  real_T w_d_y_P5;                     /* Expression: stype
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  real_T w_d_y_P6;                     /* Expression: btype
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  real_T zeta_psi_P1;                  /* Expression: width
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  real_T zeta_psi_P2;                  /* Expression: dtype
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  real_T zeta_psi_P3;                  /* Expression: portnum
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  real_T zeta_psi_P4;                  /* Expression: stime
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  real_T zeta_psi_P5;                  /* Expression: stype
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  real_T zeta_psi_P6;                  /* Expression: btype
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  real_T zeta_x_P1;                    /* Expression: width
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  real_T zeta_x_P2;                    /* Expression: dtype
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  real_T zeta_x_P3;                    /* Expression: portnum
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  real_T zeta_x_P4;                    /* Expression: stime
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  real_T zeta_x_P5;                    /* Expression: stype
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  real_T zeta_x_P6;                    /* Expression: btype
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  real_T Oculus_ref_on_off_P1;         /* Expression: width
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  real_T Oculus_ref_on_off_P2;         /* Expression: dtype
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  real_T Oculus_ref_on_off_P3;         /* Expression: portnum
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  real_T Oculus_ref_on_off_P4;         /* Expression: stime
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  real_T Oculus_ref_on_off_P5;         /* Expression: stype
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  real_T Oculus_ref_on_off_P6;         /* Expression: btype
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  real_T psi_ref_P1;                   /* Expression: width
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  real_T psi_ref_P2;                   /* Expression: dtype
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  real_T psi_ref_P3;                   /* Expression: portnum
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  real_T psi_ref_P4;                   /* Expression: stime
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  real_T psi_ref_P5;                   /* Expression: stype
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  real_T psi_ref_P6;                   /* Expression: btype
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  real_T Oculus_yaw_P1;                /* Expression: width
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  real_T Oculus_yaw_P2;                /* Expression: dtype
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  real_T Oculus_yaw_P3;                /* Expression: portnum
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  real_T Oculus_yaw_P4;                /* Expression: stime
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  real_T Oculus_yaw_P5;                /* Expression: stype
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  real_T Oculus_yaw_P6;                /* Expression: btype
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  real_T x_ref_P1;                     /* Expression: width
                                        * Referenced by: '<S3>/x_ref'
                                        */
  real_T x_ref_P2;                     /* Expression: dtype
                                        * Referenced by: '<S3>/x_ref'
                                        */
  real_T x_ref_P3;                     /* Expression: portnum
                                        * Referenced by: '<S3>/x_ref'
                                        */
  real_T x_ref_P4;                     /* Expression: stime
                                        * Referenced by: '<S3>/x_ref'
                                        */
  real_T x_ref_P5;                     /* Expression: stype
                                        * Referenced by: '<S3>/x_ref'
                                        */
  real_T x_ref_P6;                     /* Expression: btype
                                        * Referenced by: '<S3>/x_ref'
                                        */
  real_T y_ref_P1;                     /* Expression: width
                                        * Referenced by: '<S3>/y_ref'
                                        */
  real_T y_ref_P2;                     /* Expression: dtype
                                        * Referenced by: '<S3>/y_ref'
                                        */
  real_T y_ref_P3;                     /* Expression: portnum
                                        * Referenced by: '<S3>/y_ref'
                                        */
  real_T y_ref_P4;                     /* Expression: stime
                                        * Referenced by: '<S3>/y_ref'
                                        */
  real_T y_ref_P5;                     /* Expression: stype
                                        * Referenced by: '<S3>/y_ref'
                                        */
  real_T y_ref_P6;                     /* Expression: btype
                                        * Referenced by: '<S3>/y_ref'
                                        */
  real_T x_P1;                         /* Expression: width
                                        * Referenced by: '<S3>/x'
                                        */
  real_T x_P2;                         /* Expression: dtype
                                        * Referenced by: '<S3>/x'
                                        */
  real_T x_P3;                         /* Expression: portnum
                                        * Referenced by: '<S3>/x'
                                        */
  real_T x_P4;                         /* Expression: stime
                                        * Referenced by: '<S3>/x'
                                        */
  real_T x_P5;                         /* Expression: stype
                                        * Referenced by: '<S3>/x'
                                        */
  real_T x_P6;                         /* Expression: btype
                                        * Referenced by: '<S3>/x'
                                        */
  real_T y_P1;                         /* Expression: width
                                        * Referenced by: '<S3>/y'
                                        */
  real_T y_P2;                         /* Expression: dtype
                                        * Referenced by: '<S3>/y'
                                        */
  real_T y_P3;                         /* Expression: portnum
                                        * Referenced by: '<S3>/y'
                                        */
  real_T y_P4;                         /* Expression: stime
                                        * Referenced by: '<S3>/y'
                                        */
  real_T y_P5;                         /* Expression: stype
                                        * Referenced by: '<S3>/y'
                                        */
  real_T y_P6;                         /* Expression: btype
                                        * Referenced by: '<S3>/y'
                                        */
  real_T Gesture_off_P1;               /* Expression: width
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  real_T Gesture_off_P2;               /* Expression: dtype
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  real_T Gesture_off_P3;               /* Expression: portnum
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  real_T Gesture_off_P4;               /* Expression: stime
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  real_T Gesture_off_P5;               /* Expression: stype
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  real_T Gesture_off_P6;               /* Expression: btype
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  real_T Gain3_Gain;                   /* Expression: -32767/10000
                                        * Referenced by: '<S33>/Gain3'
                                        */
  real_T zeta_y_P1_p;                  /* Expression: width
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  real_T zeta_y_P2_n;                  /* Expression: dtype
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  real_T zeta_y_P3_c;                  /* Expression: portnum
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  real_T zeta_y_P4_i;                  /* Expression: stime
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  real_T zeta_y_P5_m;                  /* Expression: stype
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  real_T zeta_y_P6_j;                  /* Expression: btype
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  real_T w_d_psi_P1_n;                 /* Expression: width
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  real_T w_d_psi_P2_i;                 /* Expression: dtype
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  real_T w_d_psi_P3_j;                 /* Expression: portnum
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  real_T w_d_psi_P4_j;                 /* Expression: stime
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  real_T w_d_psi_P5_i;                 /* Expression: stype
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  real_T w_d_psi_P6_d;                 /* Expression: btype
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  real_T w_d_x_P1_i;                   /* Expression: width
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  real_T w_d_x_P2_i;                   /* Expression: dtype
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  real_T w_d_x_P3_n;                   /* Expression: portnum
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  real_T w_d_x_P4_e;                   /* Expression: stime
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  real_T w_d_x_P5_c;                   /* Expression: stype
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  real_T w_d_x_P6_j;                   /* Expression: btype
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  real_T w_d_y_P1_a;                   /* Expression: width
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  real_T w_d_y_P2_c;                   /* Expression: dtype
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  real_T w_d_y_P3_i;                   /* Expression: portnum
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  real_T w_d_y_P4_c;                   /* Expression: stime
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  real_T w_d_y_P5_i;                   /* Expression: stype
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  real_T w_d_y_P6_g;                   /* Expression: btype
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  real_T zeta_psi_P1_k;                /* Expression: width
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  real_T zeta_psi_P2_m;                /* Expression: dtype
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  real_T zeta_psi_P3_k;                /* Expression: portnum
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  real_T zeta_psi_P4_g;                /* Expression: stime
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  real_T zeta_psi_P5_n;                /* Expression: stype
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  real_T zeta_psi_P6_g;                /* Expression: btype
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  real_T zeta_x_P1_l;                  /* Expression: width
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  real_T zeta_x_P2_a;                  /* Expression: dtype
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  real_T zeta_x_P3_h;                  /* Expression: portnum
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  real_T zeta_x_P4_i;                  /* Expression: stime
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  real_T zeta_x_P5_d;                  /* Expression: stype
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  real_T zeta_x_P6_j;                  /* Expression: btype
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  real_T K_u_P1;                       /* Expression: width
                                        * Referenced by: '<S30>/K_u'
                                        */
  real_T K_u_P2;                       /* Expression: dtype
                                        * Referenced by: '<S30>/K_u'
                                        */
  real_T K_u_P3;                       /* Expression: portnum
                                        * Referenced by: '<S30>/K_u'
                                        */
  real_T K_u_P4;                       /* Expression: stime
                                        * Referenced by: '<S30>/K_u'
                                        */
  real_T K_u_P5;                       /* Expression: stype
                                        * Referenced by: '<S30>/K_u'
                                        */
  real_T K_u_P6;                       /* Expression: btype
                                        * Referenced by: '<S30>/K_u'
                                        */
  real_T K_v_P1;                       /* Expression: width
                                        * Referenced by: '<S30>/K_v'
                                        */
  real_T K_v_P2;                       /* Expression: dtype
                                        * Referenced by: '<S30>/K_v'
                                        */
  real_T K_v_P3;                       /* Expression: portnum
                                        * Referenced by: '<S30>/K_v'
                                        */
  real_T K_v_P4;                       /* Expression: stime
                                        * Referenced by: '<S30>/K_v'
                                        */
  real_T K_v_P5;                       /* Expression: stype
                                        * Referenced by: '<S30>/K_v'
                                        */
  real_T K_v_P6;                       /* Expression: btype
                                        * Referenced by: '<S30>/K_v'
                                        */
  real_T K_r_P1;                       /* Expression: width
                                        * Referenced by: '<S30>/K_r'
                                        */
  real_T K_r_P2;                       /* Expression: dtype
                                        * Referenced by: '<S30>/K_r'
                                        */
  real_T K_r_P3;                       /* Expression: portnum
                                        * Referenced by: '<S30>/K_r'
                                        */
  real_T K_r_P4;                       /* Expression: stime
                                        * Referenced by: '<S30>/K_r'
                                        */
  real_T K_r_P5;                       /* Expression: stype
                                        * Referenced by: '<S30>/K_r'
                                        */
  real_T K_r_P6;                       /* Expression: btype
                                        * Referenced by: '<S30>/K_r'
                                        */
  real_T Oculus_roll_P1;               /* Expression: width
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  real_T Oculus_roll_P2;               /* Expression: dtype
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  real_T Oculus_roll_P3;               /* Expression: portnum
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  real_T Oculus_roll_P4;               /* Expression: stime
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  real_T Oculus_roll_P5;               /* Expression: stype
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  real_T Oculus_roll_P6;               /* Expression: btype
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  real_T Gain1_Gain;                   /* Expression: -32767/10000
                                        * Referenced by: '<S33>/Gain1'
                                        */
  real_T Oculus_pitch_P1;              /* Expression: width
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  real_T Oculus_pitch_P2;              /* Expression: dtype
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  real_T Oculus_pitch_P3;              /* Expression: portnum
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  real_T Oculus_pitch_P4;              /* Expression: stime
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  real_T Oculus_pitch_P5;              /* Expression: stype
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  real_T Oculus_pitch_P6;              /* Expression: btype
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 1e10
                                        * Referenced by: '<S12>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: -1e10
                                        * Referenced by: '<S12>/Saturation'
                                        */
  real_T Gain_Gain_n;                  /* Expression: pi
                                        * Referenced by: '<S12>/Gain'
                                        */
  real_T Constant_Value_d;             /* Expression: 2*pi
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Saturation_UpperSat_dc;       /* Expression: 1e10
                                        * Referenced by: '<S19>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: -1e10
                                        * Referenced by: '<S19>/Saturation'
                                        */
  real_T Gain_Gain_e;                  /* Expression: pi
                                        * Referenced by: '<S19>/Gain'
                                        */
  real_T Constant_Value_j;             /* Expression: 2*pi
                                        * Referenced by: '<S19>/Constant'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<S18>/Integrator1'
                                        */
  real_T Integrator3_IC;               /* Expression: 0
                                        * Referenced by: '<S14>/Integrator3'
                                        */
  real_T Saturation_UpperSat_c;        /* Expression: 1e10
                                        * Referenced by: '<S20>/Saturation'
                                        */
  real_T Saturation_LowerSat_n;        /* Expression: -1e10
                                        * Referenced by: '<S20>/Saturation'
                                        */
  real_T Gain_Gain_l;                  /* Expression: pi
                                        * Referenced by: '<S20>/Gain'
                                        */
  real_T Constant_Value_e;             /* Expression: 2*pi
                                        * Referenced by: '<S20>/Constant'
                                        */
  real_T Saturation_UpperSat_g;        /* Expression: 1e10
                                        * Referenced by: '<S11>/Saturation'
                                        */
  real_T Saturation_LowerSat_et;       /* Expression: -1e10
                                        * Referenced by: '<S11>/Saturation'
                                        */
  real_T Gain_Gain_p;                  /* Expression: pi
                                        * Referenced by: '<S11>/Gain'
                                        */
  real_T Constant_Value_c;             /* Expression: 2*pi
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S8>/Integrator'
                                        */
  real_T Constant1_Value;              /* Expression: 0.01
                                        * Referenced by: '<S46>/Constant1'
                                        */
  real_T Memory3_X0[3];                /* Expression: [0 0 0]
                                        * Referenced by: '<S46>/Memory3'
                                        */
  real_T u_BT_P1;                      /* Expression: width
                                        * Referenced by: '<S65>/u_BT'
                                        */
  real_T u_BT_P2;                      /* Expression: dtype
                                        * Referenced by: '<S65>/u_BT'
                                        */
  real_T u_BT_P3;                      /* Expression: portnum
                                        * Referenced by: '<S65>/u_BT'
                                        */
  real_T u_BT_P4;                      /* Expression: stime
                                        * Referenced by: '<S65>/u_BT'
                                        */
  real_T u_BT_P5;                      /* Expression: stype
                                        * Referenced by: '<S65>/u_BT'
                                        */
  real_T u_BT_P6;                      /* Expression: btype
                                        * Referenced by: '<S65>/u_BT'
                                        */
  real_T u_VSP2_P1;                    /* Expression: width
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  real_T u_VSP2_P2;                    /* Expression: dtype
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  real_T u_VSP2_P3;                    /* Expression: portnum
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  real_T u_VSP2_P4;                    /* Expression: stime
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  real_T u_VSP2_P5;                    /* Expression: stype
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  real_T u_VSP2_P6;                    /* Expression: btype
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  real_T omega_VSP1_P1;                /* Expression: width
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  real_T omega_VSP1_P2;                /* Expression: dtype
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  real_T omega_VSP1_P3;                /* Expression: portnum
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  real_T omega_VSP1_P4;                /* Expression: stime
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  real_T omega_VSP1_P5;                /* Expression: stype
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  real_T omega_VSP1_P6;                /* Expression: btype
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  real_T omega_VSP2_P1;                /* Expression: width
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  real_T omega_VSP2_P2;                /* Expression: dtype
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  real_T omega_VSP2_P3;                /* Expression: portnum
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  real_T omega_VSP2_P4;                /* Expression: stime
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  real_T omega_VSP2_P5;                /* Expression: stype
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  real_T omega_VSP2_P6;                /* Expression: btype
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  real_T u_VSP1_P1;                    /* Expression: width
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  real_T u_VSP1_P2;                    /* Expression: dtype
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  real_T u_VSP1_P3;                    /* Expression: portnum
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  real_T u_VSP1_P4;                    /* Expression: stime
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  real_T u_VSP1_P5;                    /* Expression: stype
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  real_T u_VSP1_P6;                    /* Expression: btype
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  real_T alpha_VSP1_P1;                /* Expression: width
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P2;                /* Expression: dtype
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P3;                /* Expression: portnum
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P4;                /* Expression: stime
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P5;                /* Expression: stype
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P6;                /* Expression: btype
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  real_T alpha_VSP2_P1;                /* Expression: width
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P2;                /* Expression: dtype
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P3;                /* Expression: portnum
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P4;                /* Expression: stime
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P5;                /* Expression: stype
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P6;                /* Expression: btype
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  real_T u_BT_P1_b;                    /* Expression: width
                                        * Referenced by: '<S64>/u_BT'
                                        */
  real_T u_BT_P2_p;                    /* Expression: dtype
                                        * Referenced by: '<S64>/u_BT'
                                        */
  real_T u_BT_P3_c;                    /* Expression: portnum
                                        * Referenced by: '<S64>/u_BT'
                                        */
  real_T u_BT_P4_b;                    /* Expression: stime
                                        * Referenced by: '<S64>/u_BT'
                                        */
  real_T u_BT_P5_l;                    /* Expression: stype
                                        * Referenced by: '<S64>/u_BT'
                                        */
  real_T u_BT_P6_h;                    /* Expression: btype
                                        * Referenced by: '<S64>/u_BT'
                                        */
  real_T u_VSP2_P1_h;                  /* Expression: width
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  real_T u_VSP2_P2_m;                  /* Expression: dtype
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  real_T u_VSP2_P3_j;                  /* Expression: portnum
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  real_T u_VSP2_P4_o;                  /* Expression: stime
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  real_T u_VSP2_P5_g;                  /* Expression: stype
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  real_T u_VSP2_P6_h;                  /* Expression: btype
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  real_T omega_VSP1_P1_j;              /* Expression: width
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  real_T omega_VSP1_P2_b;              /* Expression: dtype
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  real_T omega_VSP1_P3_e;              /* Expression: portnum
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  real_T omega_VSP1_P4_a;              /* Expression: stime
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  real_T omega_VSP1_P5_n;              /* Expression: stype
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  real_T omega_VSP1_P6_j;              /* Expression: btype
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  real_T omega_VSP2_P1_e;              /* Expression: width
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  real_T omega_VSP2_P2_b;              /* Expression: dtype
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  real_T omega_VSP2_P3_p;              /* Expression: portnum
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  real_T omega_VSP2_P4_i;              /* Expression: stime
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  real_T omega_VSP2_P5_o;              /* Expression: stype
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  real_T omega_VSP2_P6_l;              /* Expression: btype
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  real_T u_VSP1_P1_e;                  /* Expression: width
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  real_T u_VSP1_P2_k;                  /* Expression: dtype
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  real_T u_VSP1_P3_e;                  /* Expression: portnum
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  real_T u_VSP1_P4_k;                  /* Expression: stime
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  real_T u_VSP1_P5_o;                  /* Expression: stype
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  real_T u_VSP1_P6_m;                  /* Expression: btype
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  real_T alpha_VSP1_P1_l;              /* Expression: width
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P2_l;              /* Expression: dtype
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P3_m;              /* Expression: portnum
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P4_d;              /* Expression: stime
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P5_f;              /* Expression: stype
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P6_c;              /* Expression: btype
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  real_T alpha_VSP2_P1_k;              /* Expression: width
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P2_d;              /* Expression: dtype
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P3_l;              /* Expression: portnum
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P4_m;              /* Expression: stime
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P5_i;              /* Expression: stype
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P6_b;              /* Expression: btype
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  real_T u_BT_P1_m;                    /* Expression: width
                                        * Referenced by: '<S66>/u_BT'
                                        */
  real_T u_BT_P2_j;                    /* Expression: dtype
                                        * Referenced by: '<S66>/u_BT'
                                        */
  real_T u_BT_P3_i;                    /* Expression: portnum
                                        * Referenced by: '<S66>/u_BT'
                                        */
  real_T u_BT_P4_h;                    /* Expression: stime
                                        * Referenced by: '<S66>/u_BT'
                                        */
  real_T u_BT_P5_a;                    /* Expression: stype
                                        * Referenced by: '<S66>/u_BT'
                                        */
  real_T u_BT_P6_l;                    /* Expression: btype
                                        * Referenced by: '<S66>/u_BT'
                                        */
  real_T u_VSP2_P1_k;                  /* Expression: width
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  real_T u_VSP2_P2_e;                  /* Expression: dtype
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  real_T u_VSP2_P3_l;                  /* Expression: portnum
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  real_T u_VSP2_P4_j;                  /* Expression: stime
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  real_T u_VSP2_P5_p;                  /* Expression: stype
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  real_T u_VSP2_P6_h0;                 /* Expression: btype
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  real_T omega_VSP1_P1_m;              /* Expression: width
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  real_T omega_VSP1_P2_o;              /* Expression: dtype
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  real_T omega_VSP1_P3_c;              /* Expression: portnum
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  real_T omega_VSP1_P4_d;              /* Expression: stime
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  real_T omega_VSP1_P5_i;              /* Expression: stype
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  real_T omega_VSP1_P6_d;              /* Expression: btype
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  real_T omega_VSP2_P1_n;              /* Expression: width
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  real_T omega_VSP2_P2_g;              /* Expression: dtype
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  real_T omega_VSP2_P3_n;              /* Expression: portnum
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  real_T omega_VSP2_P4_m;              /* Expression: stime
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  real_T omega_VSP2_P5_k;              /* Expression: stype
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  real_T omega_VSP2_P6_e;              /* Expression: btype
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  real_T u_VSP1_P1_n;                  /* Expression: width
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  real_T u_VSP1_P2_l;                  /* Expression: dtype
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  real_T u_VSP1_P3_p;                  /* Expression: portnum
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  real_T u_VSP1_P4_g;                  /* Expression: stime
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  real_T u_VSP1_P5_g;                  /* Expression: stype
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  real_T u_VSP1_P6_c;                  /* Expression: btype
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  real_T alpha_VSP1_P1_m;              /* Expression: width
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P2_i;              /* Expression: dtype
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P3_e;              /* Expression: portnum
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P4_d2;             /* Expression: stime
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P5_h;              /* Expression: stype
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P6_i;              /* Expression: btype
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  real_T alpha_VSP2_P1_a;              /* Expression: width
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P2_f;              /* Expression: dtype
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P3_o;              /* Expression: portnum
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P4_h;              /* Expression: stime
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P5_ii;             /* Expression: stype
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P6_o;              /* Expression: btype
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  real_T Saturation4_UpperSat;         /* Expression: pi
                                        * Referenced by: '<S7>/Saturation4'
                                        */
  real_T Saturation4_LowerSat;         /* Expression: -pi
                                        * Referenced by: '<S7>/Saturation4'
                                        */
  real_T alpha_VSP2_P1_f;              /* Expression: width
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P2_b;              /* Expression: dtype
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P3_b;              /* Expression: portnum
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P4_hg;             /* Expression: stime
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P5_j;              /* Expression: stype
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P6_c;              /* Expression: btype
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  real_T Saturation_UpperSat_b;        /* Expression: 1
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Saturation_LowerSat_nv;       /* Expression: -1
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T u_BT_P1_h;                    /* Expression: width
                                        * Referenced by: '<S7>/u_BT'
                                        */
  real_T u_BT_P2_e;                    /* Expression: dtype
                                        * Referenced by: '<S7>/u_BT'
                                        */
  real_T u_BT_P3_j;                    /* Expression: portnum
                                        * Referenced by: '<S7>/u_BT'
                                        */
  real_T u_BT_P4_o;                    /* Expression: stime
                                        * Referenced by: '<S7>/u_BT'
                                        */
  real_T u_BT_P5_p;                    /* Expression: stype
                                        * Referenced by: '<S7>/u_BT'
                                        */
  real_T u_BT_P6_a;                    /* Expression: btype
                                        * Referenced by: '<S7>/u_BT'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 1
                                        * Referenced by: '<S7>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: 0
                                        * Referenced by: '<S7>/Saturation1'
                                        */
  real_T u_VSP1_P1_g;                  /* Expression: width
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  real_T u_VSP1_P2_m;                  /* Expression: dtype
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  real_T u_VSP1_P3_ee;                 /* Expression: portnum
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  real_T u_VSP1_P4_i;                  /* Expression: stime
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  real_T u_VSP1_P5_n;                  /* Expression: stype
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  real_T u_VSP1_P6_k;                  /* Expression: btype
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1
                                        * Referenced by: '<S7>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: 0
                                        * Referenced by: '<S7>/Saturation2'
                                        */
  real_T u_VSP2_P1_c;                  /* Expression: width
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  real_T u_VSP2_P2_p;                  /* Expression: dtype
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  real_T u_VSP2_P3_g;                  /* Expression: portnum
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  real_T u_VSP2_P4_m;                  /* Expression: stime
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  real_T u_VSP2_P5_k;                  /* Expression: stype
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  real_T u_VSP2_P6_a;                  /* Expression: btype
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  real_T Saturation3_UpperSat;         /* Expression: pi
                                        * Referenced by: '<S7>/Saturation3'
                                        */
  real_T Saturation3_LowerSat;         /* Expression: -pi
                                        * Referenced by: '<S7>/Saturation3'
                                        */
  real_T alpha_VSP1_P1_h;              /* Expression: width
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P2_d;              /* Expression: dtype
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P3_b;              /* Expression: portnum
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P4_m;              /* Expression: stime
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P5_a;              /* Expression: stype
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P6_a;              /* Expression: btype
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  real_T Saturation5_UpperSat;         /* Expression: 1
                                        * Referenced by: '<S7>/Saturation5'
                                        */
  real_T Saturation5_LowerSat;         /* Expression: -1
                                        * Referenced by: '<S7>/Saturation5'
                                        */
  real_T omega_VSP1_P1_p;              /* Expression: width
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  real_T omega_VSP1_P2_j;              /* Expression: dtype
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  real_T omega_VSP1_P3_h;              /* Expression: portnum
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  real_T omega_VSP1_P4_m;              /* Expression: stime
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  real_T omega_VSP1_P5_o;              /* Expression: stype
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  real_T omega_VSP1_P6_l;              /* Expression: btype
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  real_T Saturation6_UpperSat;         /* Expression: 1
                                        * Referenced by: '<S7>/Saturation6'
                                        */
  real_T Saturation6_LowerSat;         /* Expression: -1
                                        * Referenced by: '<S7>/Saturation6'
                                        */
  real_T omega_VSP2_P1_f;              /* Expression: width
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  real_T omega_VSP2_P2_e;              /* Expression: dtype
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  real_T omega_VSP2_P3_d;              /* Expression: portnum
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  real_T omega_VSP2_P4_k;              /* Expression: stime
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  real_T omega_VSP2_P5_c;              /* Expression: stype
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  real_T omega_VSP2_P6_h;              /* Expression: btype
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  real_T controlinputuexceedsbounds_P1;/* Expression: width
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P2;/* Expression: dtype
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P3;/* Expression: portnum
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P4;/* Expression: stime
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P5;/* Expression: stype
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P6;/* Expression: btype
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  real_T ctrl_DP_basic_P1;             /* Expression: width
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  real_T ctrl_DP_basic_P2;             /* Expression: dtype
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  real_T ctrl_DP_basic_P3;             /* Expression: portnum
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  real_T ctrl_DP_basic_P4;             /* Expression: stime
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  real_T ctrl_DP_basic_P5;             /* Expression: stype
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  real_T ctrl_DP_basic_P6;             /* Expression: btype
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  real_T ctrl_sixaxis2force_P1;        /* Expression: width
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  real_T ctrl_sixaxis2force_P2;        /* Expression: dtype
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  real_T ctrl_sixaxis2force_P3;        /* Expression: portnum
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  real_T ctrl_sixaxis2force_P4;        /* Expression: stime
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  real_T ctrl_sixaxis2force_P5;        /* Expression: stype
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  real_T ctrl_sixaxis2force_P6;        /* Expression: btype
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  real_T ctrl_sixaxis2thruster_P1;     /* Expression: width
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  real_T ctrl_sixaxis2thruster_P2;     /* Expression: dtype
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  real_T ctrl_sixaxis2thruster_P3;     /* Expression: portnum
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  real_T ctrl_sixaxis2thruster_P4;     /* Expression: stime
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  real_T ctrl_sixaxis2thruster_P5;     /* Expression: stype
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  real_T ctrl_sixaxis2thruster_P6;     /* Expression: btype
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  real_T ctrl_student_P1;              /* Expression: width
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  real_T ctrl_student_P2;              /* Expression: dtype
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  real_T ctrl_student_P3;              /* Expression: portnum
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  real_T ctrl_student_P4;              /* Expression: stime
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  real_T ctrl_student_P5;              /* Expression: stype
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  real_T ctrl_student_P6;              /* Expression: btype
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * Referenced by: '<S14>/Integrator2'
                                        */
  real_T Integrator2_IC_n;             /* Expression: 0
                                        * Referenced by: '<S18>/Integrator2'
                                        */
  real_T Integrator3_IC_i;             /* Expression: 0
                                        * Referenced by: '<S18>/Integrator3'
                                        */
  real_T Gain2_Gain;                   /* Expression: -32767/10000
                                        * Referenced by: '<S33>/Gain2'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 2/pi
                                        * Referenced by: '<S30>/Gain'
                                        */
  real_T T_b_Gain[9];                  /* Expression: [0 1 0; 1 0 0; 0 0 1];
                                        * Referenced by: '<S30>/T_b'
                                        */
  real_T tau_N_P1;                     /* Expression: width
                                        * Referenced by: '<S51>/tau_N'
                                        */
  real_T tau_N_P2;                     /* Expression: dtype
                                        * Referenced by: '<S51>/tau_N'
                                        */
  real_T tau_N_P3;                     /* Expression: portnum
                                        * Referenced by: '<S51>/tau_N'
                                        */
  real_T tau_N_P4;                     /* Expression: stime
                                        * Referenced by: '<S51>/tau_N'
                                        */
  real_T tau_N_P5;                     /* Expression: stype
                                        * Referenced by: '<S51>/tau_N'
                                        */
  real_T tau_N_P6;                     /* Expression: btype
                                        * Referenced by: '<S51>/tau_N'
                                        */
  real_T tau_X_P1;                     /* Expression: width
                                        * Referenced by: '<S51>/tau_X'
                                        */
  real_T tau_X_P2;                     /* Expression: dtype
                                        * Referenced by: '<S51>/tau_X'
                                        */
  real_T tau_X_P3;                     /* Expression: portnum
                                        * Referenced by: '<S51>/tau_X'
                                        */
  real_T tau_X_P4;                     /* Expression: stime
                                        * Referenced by: '<S51>/tau_X'
                                        */
  real_T tau_X_P5;                     /* Expression: stype
                                        * Referenced by: '<S51>/tau_X'
                                        */
  real_T tau_X_P6;                     /* Expression: btype
                                        * Referenced by: '<S51>/tau_X'
                                        */
  real_T tau_Y_P1;                     /* Expression: width
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  real_T tau_Y_P2;                     /* Expression: dtype
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  real_T tau_Y_P3;                     /* Expression: portnum
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  real_T tau_Y_P4;                     /* Expression: stime
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  real_T tau_Y_P5;                     /* Expression: stype
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  real_T tau_Y_P6;                     /* Expression: btype
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  real_T x_d_P1;                       /* Expression: width
                                        * Referenced by: '<S52>/x_d'
                                        */
  real_T x_d_P2;                       /* Expression: dtype
                                        * Referenced by: '<S52>/x_d'
                                        */
  real_T x_d_P3;                       /* Expression: portnum
                                        * Referenced by: '<S52>/x_d'
                                        */
  real_T x_d_P4;                       /* Expression: stime
                                        * Referenced by: '<S52>/x_d'
                                        */
  real_T x_d_P5;                       /* Expression: stype
                                        * Referenced by: '<S52>/x_d'
                                        */
  real_T x_d_P6;                       /* Expression: btype
                                        * Referenced by: '<S52>/x_d'
                                        */
  real_T y_d_P1;                       /* Expression: width
                                        * Referenced by: '<S52>/y_d'
                                        */
  real_T y_d_P2;                       /* Expression: dtype
                                        * Referenced by: '<S52>/y_d'
                                        */
  real_T y_d_P3;                       /* Expression: portnum
                                        * Referenced by: '<S52>/y_d'
                                        */
  real_T y_d_P4;                       /* Expression: stime
                                        * Referenced by: '<S52>/y_d'
                                        */
  real_T y_d_P5;                       /* Expression: stype
                                        * Referenced by: '<S52>/y_d'
                                        */
  real_T y_d_P6;                       /* Expression: btype
                                        * Referenced by: '<S52>/y_d'
                                        */
  real_T psi_d_P1;                     /* Expression: width
                                        * Referenced by: '<S52>/psi_d'
                                        */
  real_T psi_d_P2;                     /* Expression: dtype
                                        * Referenced by: '<S52>/psi_d'
                                        */
  real_T psi_d_P3;                     /* Expression: portnum
                                        * Referenced by: '<S52>/psi_d'
                                        */
  real_T psi_d_P4;                     /* Expression: stime
                                        * Referenced by: '<S52>/psi_d'
                                        */
  real_T psi_d_P5;                     /* Expression: stype
                                        * Referenced by: '<S52>/psi_d'
                                        */
  real_T psi_d_P6;                     /* Expression: btype
                                        * Referenced by: '<S52>/psi_d'
                                        */
  real_T r_d_P1;                       /* Expression: width
                                        * Referenced by: '<S52>/r_d'
                                        */
  real_T r_d_P2;                       /* Expression: dtype
                                        * Referenced by: '<S52>/r_d'
                                        */
  real_T r_d_P3;                       /* Expression: portnum
                                        * Referenced by: '<S52>/r_d'
                                        */
  real_T r_d_P4;                       /* Expression: stime
                                        * Referenced by: '<S52>/r_d'
                                        */
  real_T r_d_P5;                       /* Expression: stype
                                        * Referenced by: '<S52>/r_d'
                                        */
  real_T r_d_P6;                       /* Expression: btype
                                        * Referenced by: '<S52>/r_d'
                                        */
  real_T u_d_P1;                       /* Expression: width
                                        * Referenced by: '<S52>/u_d'
                                        */
  real_T u_d_P2;                       /* Expression: dtype
                                        * Referenced by: '<S52>/u_d'
                                        */
  real_T u_d_P3;                       /* Expression: portnum
                                        * Referenced by: '<S52>/u_d'
                                        */
  real_T u_d_P4;                       /* Expression: stime
                                        * Referenced by: '<S52>/u_d'
                                        */
  real_T u_d_P5;                       /* Expression: stype
                                        * Referenced by: '<S52>/u_d'
                                        */
  real_T u_d_P6;                       /* Expression: btype
                                        * Referenced by: '<S52>/u_d'
                                        */
  real_T v_d_P1;                       /* Expression: width
                                        * Referenced by: '<S52>/v_d'
                                        */
  real_T v_d_P2;                       /* Expression: dtype
                                        * Referenced by: '<S52>/v_d'
                                        */
  real_T v_d_P3;                       /* Expression: portnum
                                        * Referenced by: '<S52>/v_d'
                                        */
  real_T v_d_P4;                       /* Expression: stime
                                        * Referenced by: '<S52>/v_d'
                                        */
  real_T v_d_P5;                       /* Expression: stype
                                        * Referenced by: '<S52>/v_d'
                                        */
  real_T v_d_P6;                       /* Expression: btype
                                        * Referenced by: '<S52>/v_d'
                                        */
  real_T r_oculus_P1;                  /* Expression: width
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  real_T r_oculus_P2;                  /* Expression: dtype
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  real_T r_oculus_P3;                  /* Expression: portnum
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  real_T r_oculus_P4;                  /* Expression: stime
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  real_T r_oculus_P5;                  /* Expression: stype
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  real_T r_oculus_P6;                  /* Expression: btype
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  real_T u_oculus_P1;                  /* Expression: width
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  real_T u_oculus_P2;                  /* Expression: dtype
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  real_T u_oculus_P3;                  /* Expression: portnum
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  real_T u_oculus_P4;                  /* Expression: stime
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  real_T u_oculus_P5;                  /* Expression: stype
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  real_T u_oculus_P6;                  /* Expression: btype
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  real_T v_oculus_P1;                  /* Expression: width
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  real_T v_oculus_P2;                  /* Expression: dtype
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  real_T v_oculus_P3;                  /* Expression: portnum
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  real_T v_oculus_P4;                  /* Expression: stime
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  real_T v_oculus_P5;                  /* Expression: stype
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  real_T v_oculus_P6;                  /* Expression: btype
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  real_T r_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S53>/r_hat'
                                        */
  real_T r_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S53>/r_hat'
                                        */
  real_T r_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S53>/r_hat'
                                        */
  real_T r_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S53>/r_hat'
                                        */
  real_T r_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S53>/r_hat'
                                        */
  real_T r_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S53>/r_hat'
                                        */
  real_T u_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S53>/u_hat'
                                        */
  real_T u_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S53>/u_hat'
                                        */
  real_T u_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S53>/u_hat'
                                        */
  real_T u_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S53>/u_hat'
                                        */
  real_T u_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S53>/u_hat'
                                        */
  real_T u_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S53>/u_hat'
                                        */
  real_T v_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S53>/v_hat'
                                        */
  real_T v_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S53>/v_hat'
                                        */
  real_T v_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S53>/v_hat'
                                        */
  real_T v_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S53>/v_hat'
                                        */
  real_T v_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S53>/v_hat'
                                        */
  real_T v_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S53>/v_hat'
                                        */
  real_T x_P1_a;                       /* Expression: width
                                        * Referenced by: '<S54>/x'
                                        */
  real_T x_P2_i;                       /* Expression: dtype
                                        * Referenced by: '<S54>/x'
                                        */
  real_T x_P3_k;                       /* Expression: portnum
                                        * Referenced by: '<S54>/x'
                                        */
  real_T x_P4_o;                       /* Expression: stime
                                        * Referenced by: '<S54>/x'
                                        */
  real_T x_P5_l;                       /* Expression: stype
                                        * Referenced by: '<S54>/x'
                                        */
  real_T x_P6_n;                       /* Expression: btype
                                        * Referenced by: '<S54>/x'
                                        */
  real_T y_P1_e;                       /* Expression: width
                                        * Referenced by: '<S54>/y'
                                        */
  real_T y_P2_f;                       /* Expression: dtype
                                        * Referenced by: '<S54>/y'
                                        */
  real_T y_P3_b;                       /* Expression: portnum
                                        * Referenced by: '<S54>/y'
                                        */
  real_T y_P4_d;                       /* Expression: stime
                                        * Referenced by: '<S54>/y'
                                        */
  real_T y_P5_i;                       /* Expression: stype
                                        * Referenced by: '<S54>/y'
                                        */
  real_T y_P6_e;                       /* Expression: btype
                                        * Referenced by: '<S54>/y'
                                        */
  real_T Saturation_UpperSat_o;        /* Expression: 1e10
                                        * Referenced by: '<S60>/Saturation'
                                        */
  real_T Saturation_LowerSat_l5;       /* Expression: -1e10
                                        * Referenced by: '<S60>/Saturation'
                                        */
  real_T Gain_Gain_pb;                 /* Expression: pi
                                        * Referenced by: '<S60>/Gain'
                                        */
  real_T Constant_Value_f;             /* Expression: 2*pi
                                        * Referenced by: '<S60>/Constant'
                                        */
  real_T psi_P1_c;                     /* Expression: width
                                        * Referenced by: '<S54>/psi'
                                        */
  real_T psi_P2_g;                     /* Expression: dtype
                                        * Referenced by: '<S54>/psi'
                                        */
  real_T psi_P3_l;                     /* Expression: portnum
                                        * Referenced by: '<S54>/psi'
                                        */
  real_T psi_P4_e;                     /* Expression: stime
                                        * Referenced by: '<S54>/psi'
                                        */
  real_T psi_P5_i;                     /* Expression: stype
                                        * Referenced by: '<S54>/psi'
                                        */
  real_T psi_P6_p;                     /* Expression: btype
                                        * Referenced by: '<S54>/psi'
                                        */
  real_T NIVeriStandSignalProbe_P1;    /* Expression: 1
                                        * Referenced by: '<Root>/NIVeriStandSignalProbe'
                                        */
  uint32_T Delay_DelayLength;          /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S46>/Delay'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_CSE1_Oculus_gesture_T {
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
    real_T odeY[24];
    real_T odeF[4][24];
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
    boolean_T firstInitCondFlag;
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
extern P_CSE1_Oculus_gesture_T CSE1_Oculus_gesture_P;

/* Block signals (auto storage) */
extern B_CSE1_Oculus_gesture_T CSE1_Oculus_gesture_B;

/* Continuous states (auto storage) */
extern X_CSE1_Oculus_gesture_T CSE1_Oculus_gesture_X;

/* Block states (auto storage) */
extern DW_CSE1_Oculus_gesture_T CSE1_Oculus_gesture_DW;

/* Model entry point functions */
extern void CSE1_Oculus_gesture_initialize(void);
extern void CSE1_Oculus_gesture_output(void);
extern void CSE1_Oculus_gesture_update(void);
extern void CSE1_Oculus_gesture_terminate(void);

/* Real-time Model object */
extern RT_MODEL_CSE1_Oculus_gesture_T *const CSE1_Oculus_gesture_M;

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
 * '<Root>' : 'CSE1_Oculus_gesture'
 * '<S1>'   : 'CSE1_Oculus_gesture/Control'
 * '<S2>'   : 'CSE1_Oculus_gesture/Guidance'
 * '<S3>'   : 'CSE1_Oculus_gesture/Input'
 * '<S4>'   : 'CSE1_Oculus_gesture/Navigation '
 * '<S5>'   : 'CSE1_Oculus_gesture/Output'
 * '<S6>'   : 'CSE1_Oculus_gesture/Thrust allocation'
 * '<S7>'   : 'CSE1_Oculus_gesture/ctrl_out'
 * '<S8>'   : 'CSE1_Oculus_gesture/Control/DP Controller'
 * '<S9>'   : 'CSE1_Oculus_gesture/Control/DP Controller/Transposed rotation  matrix in yaw1'
 * '<S10>'  : 'CSE1_Oculus_gesture/Control/DP Controller/Transposed rotation  matrix in yaw2'
 * '<S11>'  : 'CSE1_Oculus_gesture/Control/DP Controller/[-inf inf] to [-pi pi]'
 * '<S12>'  : 'CSE1_Oculus_gesture/Control/DP Controller/[-inf inf] to [-pi pi]1'
 * '<S13>'  : 'CSE1_Oculus_gesture/Guidance/Inf,inf tto pi,pi'
 * '<S14>'  : 'CSE1_Oculus_gesture/Guidance/Reference model'
 * '<S15>'  : 'CSE1_Oculus_gesture/Guidance/Rotation matrix in yaw 1'
 * '<S16>'  : 'CSE1_Oculus_gesture/Guidance/Rotation matrix in yaw 2'
 * '<S17>'  : 'CSE1_Oculus_gesture/Guidance/Transposed rotation  matrix in yaw1'
 * '<S18>'  : 'CSE1_Oculus_gesture/Guidance/Vel Reference model1'
 * '<S19>'  : 'CSE1_Oculus_gesture/Guidance/[-inf inf] to [-pi pi]1'
 * '<S20>'  : 'CSE1_Oculus_gesture/Guidance/Inf,inf tto pi,pi/[-inf inf] to [-pi pi]'
 * '<S21>'  : 'CSE1_Oculus_gesture/Guidance/Reference model/w_d*w_d'
 * '<S22>'  : 'CSE1_Oculus_gesture/Guidance/Reference model/w_d*w_d1'
 * '<S23>'  : 'CSE1_Oculus_gesture/Guidance/Reference model/w_d^-2'
 * '<S24>'  : 'CSE1_Oculus_gesture/Guidance/Reference model/w_d^3'
 * '<S25>'  : 'CSE1_Oculus_gesture/Guidance/Vel Reference model1/w_d*w_d'
 * '<S26>'  : 'CSE1_Oculus_gesture/Guidance/Vel Reference model1/w_d*w_d1'
 * '<S27>'  : 'CSE1_Oculus_gesture/Guidance/Vel Reference model1/w_d^-2'
 * '<S28>'  : 'CSE1_Oculus_gesture/Guidance/Vel Reference model1/w_d^3'
 * '<S29>'  : 'CSE1_Oculus_gesture/Input/Control Gains'
 * '<S30>'  : 'CSE1_Oculus_gesture/Input/Gesture based ctrl'
 * '<S31>'  : 'CSE1_Oculus_gesture/Input/Guidance gains'
 * '<S32>'  : 'CSE1_Oculus_gesture/Input/Observer Gains'
 * '<S33>'  : 'CSE1_Oculus_gesture/Input/Subsystem1'
 * '<S34>'  : 'CSE1_Oculus_gesture/Input/[-inf inf] to [-pi pi]'
 * '<S35>'  : 'CSE1_Oculus_gesture/Input/Control Gains/MATLAB Function'
 * '<S36>'  : 'CSE1_Oculus_gesture/Input/Control Gains/MATLAB Function1'
 * '<S37>'  : 'CSE1_Oculus_gesture/Input/Control Gains/MATLAB Function2'
 * '<S38>'  : 'CSE1_Oculus_gesture/Input/Gesture based ctrl/MATLAB Function'
 * '<S39>'  : 'CSE1_Oculus_gesture/Input/Gesture based ctrl/MATLAB Function4'
 * '<S40>'  : 'CSE1_Oculus_gesture/Input/Guidance gains/DP guidance'
 * '<S41>'  : 'CSE1_Oculus_gesture/Input/Guidance gains/Gesture guidance'
 * '<S42>'  : 'CSE1_Oculus_gesture/Input/Guidance gains/DP guidance/diag'
 * '<S43>'  : 'CSE1_Oculus_gesture/Input/Guidance gains/DP guidance/diag1'
 * '<S44>'  : 'CSE1_Oculus_gesture/Input/Guidance gains/Gesture guidance/diag'
 * '<S45>'  : 'CSE1_Oculus_gesture/Input/Guidance gains/Gesture guidance/diag1'
 * '<S46>'  : 'CSE1_Oculus_gesture/Navigation /Derivative filter'
 * '<S47>'  : 'CSE1_Oculus_gesture/Navigation /Derivative filter/MATLAB Function'
 * '<S48>'  : 'CSE1_Oculus_gesture/Navigation /Derivative filter/MATLAB Function1'
 * '<S49>'  : 'CSE1_Oculus_gesture/Navigation /Derivative filter/MATLAB Function2'
 * '<S50>'  : 'CSE1_Oculus_gesture/Navigation /Derivative filter/MATLAB Function3'
 * '<S51>'  : 'CSE1_Oculus_gesture/Output/Control output'
 * '<S52>'  : 'CSE1_Oculus_gesture/Output/Guidance output'
 * '<S53>'  : 'CSE1_Oculus_gesture/Output/Navigation output'
 * '<S54>'  : 'CSE1_Oculus_gesture/Output/Plant output'
 * '<S55>'  : 'CSE1_Oculus_gesture/Output/diag2vector'
 * '<S56>'  : 'CSE1_Oculus_gesture/Output/diag2vector1'
 * '<S57>'  : 'CSE1_Oculus_gesture/Output/diag2vector2'
 * '<S58>'  : 'CSE1_Oculus_gesture/Output/diag2vector3'
 * '<S59>'  : 'CSE1_Oculus_gesture/Output/diag2vector4'
 * '<S60>'  : 'CSE1_Oculus_gesture/Output/Plant output/[-inf inf] to [-pi pi]'
 * '<S61>'  : 'CSE1_Oculus_gesture/Thrust allocation/Thrust allocation'
 * '<S62>'  : 'CSE1_Oculus_gesture/ctrl_out/Switch_subsystem'
 * '<S63>'  : 'CSE1_Oculus_gesture/ctrl_out/control limit checking'
 * '<S64>'  : 'CSE1_Oculus_gesture/ctrl_out/ctrl_DP_basic'
 * '<S65>'  : 'CSE1_Oculus_gesture/ctrl_out/ctrl_sixaxis2force'
 * '<S66>'  : 'CSE1_Oculus_gesture/ctrl_out/ctrl_sixaxis2thruster'
 * '<S67>'  : 'CSE1_Oculus_gesture/ctrl_out/indicator'
 * '<S68>'  : 'CSE1_Oculus_gesture/ctrl_out/sixaxis'
 * '<S69>'  : 'CSE1_Oculus_gesture/ctrl_out/Switch_subsystem/Switch_function'
 * '<S70>'  : 'CSE1_Oculus_gesture/ctrl_out/indicator/C'
 */
#endif                                 /* RTW_HEADER_CSE1_Oculus_gesture_h_ */

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_CSE1_Oculus_gesture
#ifndef NI_VERISTAND_MODELDATAFILE
#ifdef NI_VERISTAND_MAINMODELFILE

int READSIDE = 0;
int tid = 0;

#ifdef MULTITASKING

P_CSE1_Oculus_gesture_T rtParameter[NUMST+!TID01EQ];
P_CSE1_Oculus_gesture_T *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

P_CSE1_Oculus_gesture_T rtParameter[2];

#endif

#else

extern int READSIDE;

#ifdef MULTITASKING

extern int tid;
extern P_CSE1_Oculus_gesture_T* param_lookup[NUMST][2];

#else

extern P_CSE1_Oculus_gesture_T rtParameter[];

#endif
#endif

#ifdef MULTITASKING
#define CSE1_Oculus_gesture_P          (*param_lookup[tid][READSIDE])
#else
#define CSE1_Oculus_gesture_P          rtParameter[READSIDE]
#endif
#endif
#endif
