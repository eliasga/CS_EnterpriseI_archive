/*
 * NonlinearPassiveObserver.h
 *
 * Code generation for model "NonlinearPassiveObserver".
 *
 * Model version              : 1.6
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sun Mar 15 19:19:21 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_NonlinearPassiveObserver_h_
#define RTW_HEADER_NonlinearPassiveObserver_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef NonlinearPassiveObserver_COMMON_INCLUDES_
# define NonlinearPassiveObserver_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* NonlinearPassiveObserver_COMMON_INCLUDES_ */

#include "NonlinearPassiveObserver_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_zcfcn.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

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
#define NonlinearPassiveObserver_rtModel RT_MODEL_NonlinearPassiveObse_T

/* Block signals (auto storage) */
typedef struct {
  real_T reset;                        /* '<Root>/reset' */
  real_T Integrator2[3];               /* '<S1>/Integrator2' */
  real_T x;                            /* '<S4>/x' */
  real_T y;                            /* '<S4>/y' */
  real_T psi;                          /* '<S4>/psi' */
  real_T Integrator[3];                /* '<S1>/Integrator' */
  real_T Sum;                          /* '<S15>/Sum' */
  real_T K_2_x;                        /* '<S2>/K_2_x' */
  real_T K_2_y;                        /* '<S2>/K_2_y' */
  real_T K_2_psi;                      /* '<S2>/K_2_psi' */
  real_T K_3_psi;                      /* '<S2>/K_3_psi' */
  real_T K_3_x;                        /* '<S2>/K_3_x' */
  real_T K_3_y;                        /* '<S2>/K_3_y' */
  real_T K_4_psi;                      /* '<S2>/K_4_psi' */
  real_T K_4_x;                        /* '<S2>/K_4_x' */
  real_T K_4_y;                        /* '<S2>/K_4_y' */
  real_T u_BT;                         /* '<S9>/u_BT' */
  real_T u_VSP;                        /* '<S9>/u_VSP' */
  real_T u_alpha;                      /* '<S9>/u_alpha' */
  real_T Integrator1[3];               /* '<S1>/Integrator1' */
  real_T M1[3];                        /* '<S1>/M^-1' */
  real_T MatrixMultiply1[3];           /* '<S1>/Matrix Multiply1' */
  real_T Sum1[3];                      /* '<S1>/Sum1' */
} B_NonlinearPassiveObserver_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T reset_DWORK1;                 /* '<Root>/reset' */
  real_T b_x_hat_DWORK1;               /* '<S3>/b_x_hat' */
  real_T b_y_hat_DWORK1;               /* '<S3>/b_y_hat' */
  real_T b_psi_hat_DWORK1;             /* '<S3>/b_psi_hat' */
  real_T x_DWORK1;                     /* '<S4>/x' */
  real_T y_DWORK1;                     /* '<S4>/y' */
  real_T psi_DWORK1;                   /* '<S4>/psi' */
  real_T x_hat_DWORK1;                 /* '<S5>/x_hat' */
  real_T y_hat_DWORK1;                 /* '<S5>/y_hat' */
  real_T psi_hat_DWORK1;               /* '<S5>/psi_hat' */
  real_T K_2_x_DWORK1;                 /* '<S2>/K_2_x' */
  real_T K_2_y_DWORK1;                 /* '<S2>/K_2_y' */
  real_T K_2_psi_DWORK1;               /* '<S2>/K_2_psi' */
  real_T K_3_psi_DWORK1;               /* '<S2>/K_3_psi' */
  real_T K_3_x_DWORK1;                 /* '<S2>/K_3_x' */
  real_T K_3_y_DWORK1;                 /* '<S2>/K_3_y' */
  real_T K_4_psi_DWORK1;               /* '<S2>/K_4_psi' */
  real_T K_4_x_DWORK1;                 /* '<S2>/K_4_x' */
  real_T K_4_y_DWORK1;                 /* '<S2>/K_4_y' */
  real_T u_BT_DWORK1;                  /* '<S9>/u_BT' */
  real_T u_VSP_DWORK1;                 /* '<S9>/u_VSP' */
  real_T u_alpha_DWORK1;               /* '<S9>/u_alpha' */
  real_T u_dot_hat_DWORK1;             /* '<S6>/u_dot_hat' */
  real_T v_dot_hat_DWORK1;             /* '<S6>/v_dot_hat' */
  real_T r_dot_hat_DWORK1;             /* '<S6>/r_dot_hat' */
  real_T u_hat_DWORK1;                 /* '<S7>/u_hat' */
  real_T v_hat_DWORK1;                 /* '<S7>/v_hat' */
  real_T r_hat_DWORK1;                 /* '<S7>/r_hat' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S1>/Integrator' */

  uint8_T reset_DWORK2[25];            /* '<Root>/reset' */
  uint8_T b_x_hat_DWORK2[25];          /* '<S3>/b_x_hat' */
  uint8_T b_y_hat_DWORK2[25];          /* '<S3>/b_y_hat' */
  uint8_T b_psi_hat_DWORK2[25];        /* '<S3>/b_psi_hat' */
  uint8_T x_DWORK2[25];                /* '<S4>/x' */
  uint8_T y_DWORK2[25];                /* '<S4>/y' */
  uint8_T psi_DWORK2[25];              /* '<S4>/psi' */
  uint8_T x_hat_DWORK2[25];            /* '<S5>/x_hat' */
  uint8_T y_hat_DWORK2[25];            /* '<S5>/y_hat' */
  uint8_T psi_hat_DWORK2[25];          /* '<S5>/psi_hat' */
  uint8_T K_2_x_DWORK2[25];            /* '<S2>/K_2_x' */
  uint8_T K_2_y_DWORK2[25];            /* '<S2>/K_2_y' */
  uint8_T K_2_psi_DWORK2[25];          /* '<S2>/K_2_psi' */
  uint8_T K_3_psi_DWORK2[25];          /* '<S2>/K_3_psi' */
  uint8_T K_3_x_DWORK2[25];            /* '<S2>/K_3_x' */
  uint8_T K_3_y_DWORK2[25];            /* '<S2>/K_3_y' */
  uint8_T K_4_psi_DWORK2[25];          /* '<S2>/K_4_psi' */
  uint8_T K_4_x_DWORK2[25];            /* '<S2>/K_4_x' */
  uint8_T K_4_y_DWORK2[25];            /* '<S2>/K_4_y' */
  uint8_T u_BT_DWORK2[25];             /* '<S9>/u_BT' */
  uint8_T u_VSP_DWORK2[25];            /* '<S9>/u_VSP' */
  uint8_T u_alpha_DWORK2[25];          /* '<S9>/u_alpha' */
  uint8_T u_dot_hat_DWORK2[25];        /* '<S6>/u_dot_hat' */
  uint8_T v_dot_hat_DWORK2[25];        /* '<S6>/v_dot_hat' */
  uint8_T r_dot_hat_DWORK2[25];        /* '<S6>/r_dot_hat' */
  uint8_T u_hat_DWORK2[25];            /* '<S7>/u_hat' */
  uint8_T v_hat_DWORK2[25];            /* '<S7>/v_hat' */
  uint8_T r_hat_DWORK2[25];            /* '<S7>/r_hat' */
} DW_NonlinearPassiveObserver_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator2_CSTATE[3];        /* '<S1>/Integrator2' */
  real_T Integrator_CSTATE[3];         /* '<S1>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S1>/Integrator1' */
} X_NonlinearPassiveObserver_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator2_CSTATE[3];        /* '<S1>/Integrator2' */
  real_T Integrator_CSTATE[3];         /* '<S1>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S1>/Integrator1' */
} XDot_NonlinearPassiveObserver_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator2_CSTATE[3];     /* '<S1>/Integrator2' */
  boolean_T Integrator_CSTATE[3];      /* '<S1>/Integrator' */
  boolean_T Integrator1_CSTATE[3];     /* '<S1>/Integrator1' */
} XDis_NonlinearPassiveObserver_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator2_Reset_ZCE;    /* '<S1>/Integrator2' */
  ZCSigState Integrator_Reset_ZCE;     /* '<S1>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S1>/Integrator1' */
} PrevZCX_NonlinearPassiveObser_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            NonlinearPassiveObserver_B
#define BlockIO                        B_NonlinearPassiveObserver_T
#define rtX                            NonlinearPassiveObserver_X
#define ContinuousStates               X_NonlinearPassiveObserver_T
#define rtXdot                         NonlinearPassiveObserver_XDot
#define StateDerivatives               XDot_NonlinearPassiveObserver_T
#define tXdis                          NonlinearPassiveObserver_XDis
#define StateDisabled                  XDis_NonlinearPassiveObserver_T
#define rtP                            NonlinearPassiveObserver_P
#define Parameters                     P_NonlinearPassiveObserver_T
#define rtDWork                        NonlinearPassiveObserver_DW
#define D_Work                         DW_NonlinearPassiveObserver_T
#define rtPrevZCSigState               NonlinearPassiveObserve_PrevZCX
#define PrevZCSigStates                PrevZCX_NonlinearPassiveObser_T

/* Parameters (auto storage) */
struct P_NonlinearPassiveObserver_T_ {
  real_T reset_P1;                     /* Expression: width
                                        * Referenced by: '<Root>/reset'
                                        */
  real_T reset_P2;                     /* Expression: dtype
                                        * Referenced by: '<Root>/reset'
                                        */
  real_T reset_P3;                     /* Expression: portnum
                                        * Referenced by: '<Root>/reset'
                                        */
  real_T reset_P4;                     /* Expression: stime
                                        * Referenced by: '<Root>/reset'
                                        */
  real_T reset_P5;                     /* Expression: stype
                                        * Referenced by: '<Root>/reset'
                                        */
  real_T reset_P6;                     /* Expression: btype
                                        * Referenced by: '<Root>/reset'
                                        */
  real_T Integrator2_IC[3];            /* Expression: [0 0 0]'
                                        * Referenced by: '<S1>/Integrator2'
                                        */
  real_T b_x_hat_P1;                   /* Expression: width
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  real_T b_x_hat_P2;                   /* Expression: dtype
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  real_T b_x_hat_P3;                   /* Expression: portnum
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  real_T b_x_hat_P4;                   /* Expression: stime
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  real_T b_x_hat_P5;                   /* Expression: stype
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  real_T b_x_hat_P6;                   /* Expression: btype
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  real_T b_y_hat_P1;                   /* Expression: width
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  real_T b_y_hat_P2;                   /* Expression: dtype
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  real_T b_y_hat_P3;                   /* Expression: portnum
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  real_T b_y_hat_P4;                   /* Expression: stime
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  real_T b_y_hat_P5;                   /* Expression: stype
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  real_T b_y_hat_P6;                   /* Expression: btype
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  real_T b_psi_hat_P1;                 /* Expression: width
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  real_T b_psi_hat_P2;                 /* Expression: dtype
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  real_T b_psi_hat_P3;                 /* Expression: portnum
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  real_T b_psi_hat_P4;                 /* Expression: stime
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  real_T b_psi_hat_P5;                 /* Expression: stype
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  real_T b_psi_hat_P6;                 /* Expression: btype
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  real_T x_P1;                         /* Expression: width
                                        * Referenced by: '<S4>/x'
                                        */
  real_T x_P2;                         /* Expression: dtype
                                        * Referenced by: '<S4>/x'
                                        */
  real_T x_P3;                         /* Expression: portnum
                                        * Referenced by: '<S4>/x'
                                        */
  real_T x_P4;                         /* Expression: stime
                                        * Referenced by: '<S4>/x'
                                        */
  real_T x_P5;                         /* Expression: stype
                                        * Referenced by: '<S4>/x'
                                        */
  real_T x_P6;                         /* Expression: btype
                                        * Referenced by: '<S4>/x'
                                        */
  real_T y_P1;                         /* Expression: width
                                        * Referenced by: '<S4>/y'
                                        */
  real_T y_P2;                         /* Expression: dtype
                                        * Referenced by: '<S4>/y'
                                        */
  real_T y_P3;                         /* Expression: portnum
                                        * Referenced by: '<S4>/y'
                                        */
  real_T y_P4;                         /* Expression: stime
                                        * Referenced by: '<S4>/y'
                                        */
  real_T y_P5;                         /* Expression: stype
                                        * Referenced by: '<S4>/y'
                                        */
  real_T y_P6;                         /* Expression: btype
                                        * Referenced by: '<S4>/y'
                                        */
  real_T psi_P1;                       /* Expression: width
                                        * Referenced by: '<S4>/psi'
                                        */
  real_T psi_P2;                       /* Expression: dtype
                                        * Referenced by: '<S4>/psi'
                                        */
  real_T psi_P3;                       /* Expression: portnum
                                        * Referenced by: '<S4>/psi'
                                        */
  real_T psi_P4;                       /* Expression: stime
                                        * Referenced by: '<S4>/psi'
                                        */
  real_T psi_P5;                       /* Expression: stype
                                        * Referenced by: '<S4>/psi'
                                        */
  real_T psi_P6;                       /* Expression: btype
                                        * Referenced by: '<S4>/psi'
                                        */
  real_T x_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S5>/x_hat'
                                        */
  real_T x_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S5>/x_hat'
                                        */
  real_T x_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S5>/x_hat'
                                        */
  real_T x_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S5>/x_hat'
                                        */
  real_T x_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S5>/x_hat'
                                        */
  real_T x_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S5>/x_hat'
                                        */
  real_T y_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S5>/y_hat'
                                        */
  real_T y_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S5>/y_hat'
                                        */
  real_T y_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S5>/y_hat'
                                        */
  real_T y_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S5>/y_hat'
                                        */
  real_T y_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S5>/y_hat'
                                        */
  real_T y_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S5>/y_hat'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * Referenced by: '<S15>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * Referenced by: '<S15>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * Referenced by: '<S15>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 2*pi
                                        * Referenced by: '<S15>/Constant'
                                        */
  real_T psi_hat_P1;                   /* Expression: width
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  real_T psi_hat_P2;                   /* Expression: dtype
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  real_T psi_hat_P3;                   /* Expression: portnum
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  real_T psi_hat_P4;                   /* Expression: stime
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  real_T psi_hat_P5;                   /* Expression: stype
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  real_T psi_hat_P6;                   /* Expression: btype
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  real_T Saturation_UpperSat_f;        /* Expression: 1e10
                                        * Referenced by: '<S16>/Saturation'
                                        */
  real_T Saturation_LowerSat_d;        /* Expression: -1e10
                                        * Referenced by: '<S16>/Saturation'
                                        */
  real_T Gain_Gain_h;                  /* Expression: pi
                                        * Referenced by: '<S16>/Gain'
                                        */
  real_T Constant_Value_p;             /* Expression: 2*pi
                                        * Referenced by: '<S16>/Constant'
                                        */
  real_T K_2_x_P1;                     /* Expression: width
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  real_T K_2_x_P2;                     /* Expression: dtype
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  real_T K_2_x_P3;                     /* Expression: portnum
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  real_T K_2_x_P4;                     /* Expression: stime
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  real_T K_2_x_P5;                     /* Expression: stype
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  real_T K_2_x_P6;                     /* Expression: btype
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  real_T K_2_y_P1;                     /* Expression: width
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  real_T K_2_y_P2;                     /* Expression: dtype
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  real_T K_2_y_P3;                     /* Expression: portnum
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  real_T K_2_y_P4;                     /* Expression: stime
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  real_T K_2_y_P5;                     /* Expression: stype
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  real_T K_2_y_P6;                     /* Expression: btype
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  real_T K_2_psi_P1;                   /* Expression: width
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  real_T K_2_psi_P2;                   /* Expression: dtype
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  real_T K_2_psi_P3;                   /* Expression: portnum
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  real_T K_2_psi_P4;                   /* Expression: stime
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  real_T K_2_psi_P5;                   /* Expression: stype
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  real_T K_2_psi_P6;                   /* Expression: btype
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  real_T K_3_psi_P1;                   /* Expression: width
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  real_T K_3_psi_P2;                   /* Expression: dtype
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  real_T K_3_psi_P3;                   /* Expression: portnum
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  real_T K_3_psi_P4;                   /* Expression: stime
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  real_T K_3_psi_P5;                   /* Expression: stype
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  real_T K_3_psi_P6;                   /* Expression: btype
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  real_T K_3_x_P1;                     /* Expression: width
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  real_T K_3_x_P2;                     /* Expression: dtype
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  real_T K_3_x_P3;                     /* Expression: portnum
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  real_T K_3_x_P4;                     /* Expression: stime
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  real_T K_3_x_P5;                     /* Expression: stype
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  real_T K_3_x_P6;                     /* Expression: btype
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  real_T K_3_y_P1;                     /* Expression: width
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  real_T K_3_y_P2;                     /* Expression: dtype
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  real_T K_3_y_P3;                     /* Expression: portnum
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  real_T K_3_y_P4;                     /* Expression: stime
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  real_T K_3_y_P5;                     /* Expression: stype
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  real_T K_3_y_P6;                     /* Expression: btype
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  real_T K_4_psi_P1;                   /* Expression: width
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  real_T K_4_psi_P2;                   /* Expression: dtype
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  real_T K_4_psi_P3;                   /* Expression: portnum
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  real_T K_4_psi_P4;                   /* Expression: stime
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  real_T K_4_psi_P5;                   /* Expression: stype
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  real_T K_4_psi_P6;                   /* Expression: btype
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  real_T K_4_x_P1;                     /* Expression: width
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  real_T K_4_x_P2;                     /* Expression: dtype
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  real_T K_4_x_P3;                     /* Expression: portnum
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  real_T K_4_x_P4;                     /* Expression: stime
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  real_T K_4_x_P5;                     /* Expression: stype
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  real_T K_4_x_P6;                     /* Expression: btype
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  real_T K_4_y_P1;                     /* Expression: width
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  real_T K_4_y_P2;                     /* Expression: dtype
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  real_T K_4_y_P3;                     /* Expression: portnum
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  real_T K_4_y_P4;                     /* Expression: stime
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  real_T K_4_y_P5;                     /* Expression: stype
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  real_T K_4_y_P6;                     /* Expression: btype
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  real_T u_BT_P1;                      /* Expression: width
                                        * Referenced by: '<S9>/u_BT'
                                        */
  real_T u_BT_P2;                      /* Expression: dtype
                                        * Referenced by: '<S9>/u_BT'
                                        */
  real_T u_BT_P3;                      /* Expression: portnum
                                        * Referenced by: '<S9>/u_BT'
                                        */
  real_T u_BT_P4;                      /* Expression: stime
                                        * Referenced by: '<S9>/u_BT'
                                        */
  real_T u_BT_P5;                      /* Expression: stype
                                        * Referenced by: '<S9>/u_BT'
                                        */
  real_T u_BT_P6;                      /* Expression: btype
                                        * Referenced by: '<S9>/u_BT'
                                        */
  real_T u_VSP_P1;                     /* Expression: width
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  real_T u_VSP_P2;                     /* Expression: dtype
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  real_T u_VSP_P3;                     /* Expression: portnum
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  real_T u_VSP_P4;                     /* Expression: stime
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  real_T u_VSP_P5;                     /* Expression: stype
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  real_T u_VSP_P6;                     /* Expression: btype
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  real_T u_alpha_P1;                   /* Expression: width
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  real_T u_alpha_P2;                   /* Expression: dtype
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  real_T u_alpha_P3;                   /* Expression: portnum
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  real_T u_alpha_P4;                   /* Expression: stime
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  real_T u_alpha_P5;                   /* Expression: stype
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  real_T u_alpha_P6;                   /* Expression: btype
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  real_T Integrator1_IC[3];            /* Expression: [0 0 0]'
                                        * Referenced by: '<S1>/Integrator1'
                                        */
  real_T M1_Gain[9];                   /* Expression: M^-1
                                        * Referenced by: '<S1>/M^-1'
                                        */
  real_T u_dot_hat_P1;                 /* Expression: width
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  real_T u_dot_hat_P2;                 /* Expression: dtype
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  real_T u_dot_hat_P3;                 /* Expression: portnum
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  real_T u_dot_hat_P4;                 /* Expression: stime
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  real_T u_dot_hat_P5;                 /* Expression: stype
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  real_T u_dot_hat_P6;                 /* Expression: btype
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  real_T v_dot_hat_P1;                 /* Expression: width
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  real_T v_dot_hat_P2;                 /* Expression: dtype
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  real_T v_dot_hat_P3;                 /* Expression: portnum
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  real_T v_dot_hat_P4;                 /* Expression: stime
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  real_T v_dot_hat_P5;                 /* Expression: stype
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  real_T v_dot_hat_P6;                 /* Expression: btype
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  real_T r_dot_hat_P1;                 /* Expression: width
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  real_T r_dot_hat_P2;                 /* Expression: dtype
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  real_T r_dot_hat_P3;                 /* Expression: portnum
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  real_T r_dot_hat_P4;                 /* Expression: stime
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  real_T r_dot_hat_P5;                 /* Expression: stype
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  real_T r_dot_hat_P6;                 /* Expression: btype
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  real_T u_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S7>/u_hat'
                                        */
  real_T u_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S7>/u_hat'
                                        */
  real_T u_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S7>/u_hat'
                                        */
  real_T u_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S7>/u_hat'
                                        */
  real_T u_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S7>/u_hat'
                                        */
  real_T u_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S7>/u_hat'
                                        */
  real_T v_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S7>/v_hat'
                                        */
  real_T v_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S7>/v_hat'
                                        */
  real_T v_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S7>/v_hat'
                                        */
  real_T v_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S7>/v_hat'
                                        */
  real_T v_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S7>/v_hat'
                                        */
  real_T v_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S7>/v_hat'
                                        */
  real_T r_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S7>/r_hat'
                                        */
  real_T r_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S7>/r_hat'
                                        */
  real_T r_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S7>/r_hat'
                                        */
  real_T r_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S7>/r_hat'
                                        */
  real_T r_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S7>/r_hat'
                                        */
  real_T r_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S7>/r_hat'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_NonlinearPassiveObser_T {
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
    real_T odeY[9];
    real_T odeF[4][9];
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
extern P_NonlinearPassiveObserver_T NonlinearPassiveObserver_P;

/* Block signals (auto storage) */
extern B_NonlinearPassiveObserver_T NonlinearPassiveObserver_B;

/* Continuous states (auto storage) */
extern X_NonlinearPassiveObserver_T NonlinearPassiveObserver_X;

/* Block states (auto storage) */
extern DW_NonlinearPassiveObserver_T NonlinearPassiveObserver_DW;

/* Model entry point functions */
extern void NonlinearPassiveObserver_initialize(void);
extern void NonlinearPassiveObserver_output(void);
extern void NonlinearPassiveObserver_update(void);
extern void NonlinearPassiveObserver_terminate(void);

/* Real-time Model object */
extern RT_MODEL_NonlinearPassiveObse_T *const NonlinearPassiveObserver_M;

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
 * '<Root>' : 'NonlinearPassiveObserver'
 * '<S1>'   : 'NonlinearPassiveObserver/Nonlinear Passisve Observer'
 * '<S2>'   : 'NonlinearPassiveObserver/Observer Gains'
 * '<S3>'   : 'NonlinearPassiveObserver/b_hat output'
 * '<S4>'   : 'NonlinearPassiveObserver/eta input'
 * '<S5>'   : 'NonlinearPassiveObserver/eta_hat output'
 * '<S6>'   : 'NonlinearPassiveObserver/nu_dot_hat output'
 * '<S7>'   : 'NonlinearPassiveObserver/nu_hat output'
 * '<S8>'   : 'NonlinearPassiveObserver/tau_2_tau_actual'
 * '<S9>'   : 'NonlinearPassiveObserver/u input'
 * '<S10>'  : 'NonlinearPassiveObserver/Nonlinear Passisve Observer/C(nu)*nu'
 * '<S11>'  : 'NonlinearPassiveObserver/Nonlinear Passisve Observer/D(nu)*nu'
 * '<S12>'  : 'NonlinearPassiveObserver/Nonlinear Passisve Observer/Rotation matrix in yaw 1'
 * '<S13>'  : 'NonlinearPassiveObserver/Nonlinear Passisve Observer/Transpose Rotation Matrix'
 * '<S14>'  : 'NonlinearPassiveObserver/Nonlinear Passisve Observer/Transpose Rotation matrix'
 * '<S15>'  : 'NonlinearPassiveObserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]'
 * '<S16>'  : 'NonlinearPassiveObserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]1'
 * '<S17>'  : 'NonlinearPassiveObserver/Observer Gains/MATLAB Function'
 * '<S18>'  : 'NonlinearPassiveObserver/Observer Gains/MATLAB Function1'
 * '<S19>'  : 'NonlinearPassiveObserver/Observer Gains/MATLAB Function2'
 * '<S20>'  : 'NonlinearPassiveObserver/tau_2_tau_actual/Thruster configuration matrix'
 * '<S21>'  : 'NonlinearPassiveObserver/tau_2_tau_actual/Thruster mapping'
 * '<S22>'  : 'NonlinearPassiveObserver/tau_2_tau_actual/Thruster mapping/Bow thruster'
 * '<S23>'  : 'NonlinearPassiveObserver/tau_2_tau_actual/Thruster mapping/VSP'
 */
#endif                                 /* RTW_HEADER_NonlinearPassiveObserver_h_ */

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_NonlinearPassiveObserver
#ifndef NI_VERISTAND_MODELDATAFILE
#ifdef NI_VERISTAND_MAINMODELFILE

int READSIDE = 0;
int tid = 0;

#ifdef MULTITASKING

P_NonlinearPassiveObserver_T rtParameter[NUMST+!TID01EQ];
P_NonlinearPassiveObserver_T *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

P_NonlinearPassiveObserver_T rtParameter[2];

#endif

#else

extern int READSIDE;

#ifdef MULTITASKING

extern int tid;
extern P_NonlinearPassiveObserver_T* param_lookup[NUMST][2];

#else

extern P_NonlinearPassiveObserver_T rtParameter[];

#endif
#endif

#ifdef MULTITASKING
#define NonlinearPassiveObserver_P     (*param_lookup[tid][READSIDE])
#else
#define NonlinearPassiveObserver_P     rtParameter[READSIDE]
#endif
#endif
#endif
