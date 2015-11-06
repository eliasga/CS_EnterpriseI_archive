/*
 * HILmodel.h
 *
 * Code generation for model "HILmodel".
 *
 * Model version              : 1.12
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sat Jan 10 18:08:25 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_HILmodel_h_
#define RTW_HEADER_HILmodel_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef HILmodel_COMMON_INCLUDES_
# define HILmodel_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* HILmodel_COMMON_INCLUDES_ */

#include "HILmodel_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_zcfcn.h"
#include "rtGetInf.h"
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
#define HILmodel_rtModel               RT_MODEL_HILmodel_T

/* Block signals (auto storage) */
typedef struct {
  real_T reset;                        /* '<S1>/reset' */
  real_T eta_01;                       /* '<S13>/eta_01' */
  real_T eta_02;                       /* '<S13>/eta_02' */
  real_T eta_03;                       /* '<S13>/eta_03' */
  real_T p[3];                         /* '<S1>/Integrator4' */
  real_T eta_04;                       /* '<S14>/eta_04' */
  real_T eta_05;                       /* '<S14>/eta_05' */
  real_T eta_06;                       /* '<S14>/eta_06' */
  real_T theta[3];                     /* '<S1>/Integrator2' */
  real_T eta1;                         /* '<S15>/eta1' */
  real_T eta2;                         /* '<S15>/eta2' */
  real_T eta3;                         /* '<S15>/eta3' */
  real_T eta4;                         /* '<S15>/eta4' */
  real_T eta5;                         /* '<S15>/eta5' */
  real_T eta6;                         /* '<S15>/eta6' */
  real_T nu[6];                        /* '<S1>/Integrator3' */
  real_T M11[9];                       /* '<S8>/M11' */
  real_T M12[9];                       /* '<S8>/M12' */
  real_T M21M12[9];                    /* '<S8>/transpose1' */
  real_T M22[9];                       /* '<S8>/M22' */
  real_T M11_j[9];                     /* '<S9>/M11' */
  real_T nu_c1;                        /* '<S6>/nu_c1' */
  real_T nu_c2;                        /* '<S6>/nu_c2' */
  real_T nu_c_onoff;                   /* '<S6>/nu_c_onoff' */
  real_T M12_i[9];                     /* '<S9>/M12' */
  real_T M21M12_b[9];                  /* '<S9>/transpose1' */
  real_T M22_l[9];                     /* '<S9>/M22' */
  real_T M[36];                        /* '<S1>/Sum2' */
  real_T tau1;                         /* '<S7>/tau1' */
  real_T tau2;                         /* '<S7>/tau2' */
  real_T tau3;                         /* '<S7>/tau3' */
  real_T tau4;                         /* '<S7>/tau4' */
  real_T tau5;                         /* '<S7>/tau5' */
  real_T tau6;                         /* '<S7>/tau6' */
  real_T D_NL_onoff;                   /* '<S2>/D_NL_onoff' */
  real_T D_NL_onoff_g;                 /* '<S3>/D_NL_onoff' */
  real_T MatrixConcatenate1[36];       /* '<S12>/Matrix Concatenate1' */
  real_T nu_dot[6];                    /* '<S1>/Product' */
  real_T p_dot[3];                     /* '<S1>/Product1' */
  real_T theta_dot[3];                 /* '<S1>/Product2' */
} B_HILmodel_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T reset_DWORK1;                 /* '<S1>/reset' */
  real_T eta_01_DWORK1;                /* '<S13>/eta_01' */
  real_T eta_02_DWORK1;                /* '<S13>/eta_02' */
  real_T eta_03_DWORK1;                /* '<S13>/eta_03' */
  real_T eta1_DWORK1;                  /* '<S4>/eta1' */
  real_T eta2_DWORK1;                  /* '<S4>/eta2' */
  real_T eta3_DWORK1;                  /* '<S4>/eta3' */
  real_T eta_04_DWORK1;                /* '<S14>/eta_04' */
  real_T eta_05_DWORK1;                /* '<S14>/eta_05' */
  real_T eta_06_DWORK1;                /* '<S14>/eta_06' */
  real_T eta4_DWORK1;                  /* '<S4>/eta4' */
  real_T eta5_DWORK1;                  /* '<S4>/eta5' */
  real_T eta6_DWORK1;                  /* '<S4>/eta6' */
  real_T eta1_DWORK1_p;                /* '<S15>/eta1' */
  real_T eta2_DWORK1_l;                /* '<S15>/eta2' */
  real_T eta3_DWORK1_m;                /* '<S15>/eta3' */
  real_T eta4_DWORK1_g;                /* '<S15>/eta4' */
  real_T eta5_DWORK1_h;                /* '<S15>/eta5' */
  real_T eta6_DWORK1_g;                /* '<S15>/eta6' */
  real_T nu1_DWORK1;                   /* '<S5>/nu1' */
  real_T nu2_DWORK1;                   /* '<S5>/nu2' */
  real_T nu3_DWORK1;                   /* '<S5>/nu3' */
  real_T nu4_DWORK1;                   /* '<S5>/nu4' */
  real_T nu5_DWORK1;                   /* '<S5>/nu5' */
  real_T nu6_DWORK1;                   /* '<S5>/nu6' */
  real_T nu_c1_DWORK1;                 /* '<S6>/nu_c1' */
  real_T nu_c2_DWORK1;                 /* '<S6>/nu_c2' */
  real_T nu_c_onoff_DWORK1;            /* '<S6>/nu_c_onoff' */
  real_T tau1_DWORK1;                  /* '<S7>/tau1' */
  real_T tau2_DWORK1;                  /* '<S7>/tau2' */
  real_T tau3_DWORK1;                  /* '<S7>/tau3' */
  real_T tau4_DWORK1;                  /* '<S7>/tau4' */
  real_T tau5_DWORK1;                  /* '<S7>/tau5' */
  real_T tau6_DWORK1;                  /* '<S7>/tau6' */
  real_T D_NL_onoff_DWORK1;            /* '<S2>/D_NL_onoff' */
  real_T D_NL_onoff_DWORK1_l;          /* '<S3>/D_NL_onoff' */
  struct {
    int_T IcNeedsLoading;
  } Integrator4_IWORK;                 /* '<S1>/Integrator4' */

  struct {
    int_T IcNeedsLoading;
  } Integrator2_IWORK;                 /* '<S1>/Integrator2' */

  struct {
    int_T IcNeedsLoading;
  } Integrator3_IWORK;                 /* '<S1>/Integrator3' */

  uint8_T reset_DWORK2[9];             /* '<S1>/reset' */
  uint8_T eta_01_DWORK2[9];            /* '<S13>/eta_01' */
  uint8_T eta_02_DWORK2[9];            /* '<S13>/eta_02' */
  uint8_T eta_03_DWORK2[9];            /* '<S13>/eta_03' */
  uint8_T eta1_DWORK2[9];              /* '<S4>/eta1' */
  uint8_T eta2_DWORK2[9];              /* '<S4>/eta2' */
  uint8_T eta3_DWORK2[9];              /* '<S4>/eta3' */
  uint8_T eta_04_DWORK2[9];            /* '<S14>/eta_04' */
  uint8_T eta_05_DWORK2[9];            /* '<S14>/eta_05' */
  uint8_T eta_06_DWORK2[9];            /* '<S14>/eta_06' */
  uint8_T eta4_DWORK2[9];              /* '<S4>/eta4' */
  uint8_T eta5_DWORK2[9];              /* '<S4>/eta5' */
  uint8_T eta6_DWORK2[9];              /* '<S4>/eta6' */
  uint8_T eta1_DWORK2_p[9];            /* '<S15>/eta1' */
  uint8_T eta2_DWORK2_j[9];            /* '<S15>/eta2' */
  uint8_T eta3_DWORK2_p[9];            /* '<S15>/eta3' */
  uint8_T eta4_DWORK2_e[9];            /* '<S15>/eta4' */
  uint8_T eta5_DWORK2_i[9];            /* '<S15>/eta5' */
  uint8_T eta6_DWORK2_g[9];            /* '<S15>/eta6' */
  uint8_T nu1_DWORK2[9];               /* '<S5>/nu1' */
  uint8_T nu2_DWORK2[9];               /* '<S5>/nu2' */
  uint8_T nu3_DWORK2[9];               /* '<S5>/nu3' */
  uint8_T nu4_DWORK2[9];               /* '<S5>/nu4' */
  uint8_T nu5_DWORK2[9];               /* '<S5>/nu5' */
  uint8_T nu6_DWORK2[9];               /* '<S5>/nu6' */
  uint8_T nu_c1_DWORK2[9];             /* '<S6>/nu_c1' */
  uint8_T nu_c2_DWORK2[9];             /* '<S6>/nu_c2' */
  uint8_T nu_c_onoff_DWORK2[9];        /* '<S6>/nu_c_onoff' */
  uint8_T tau1_DWORK2[9];              /* '<S7>/tau1' */
  uint8_T tau2_DWORK2[9];              /* '<S7>/tau2' */
  uint8_T tau3_DWORK2[9];              /* '<S7>/tau3' */
  uint8_T tau4_DWORK2[9];              /* '<S7>/tau4' */
  uint8_T tau5_DWORK2[9];              /* '<S7>/tau5' */
  uint8_T tau6_DWORK2[9];              /* '<S7>/tau6' */
  uint8_T D_NL_onoff_DWORK2[9];        /* '<S2>/D_NL_onoff' */
  uint8_T D_NL_onoff_DWORK2_p[9];      /* '<S3>/D_NL_onoff' */
} DW_HILmodel_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator4_CSTATE[3];        /* '<S1>/Integrator4' */
  real_T Integrator2_CSTATE[3];        /* '<S1>/Integrator2' */
  real_T Integrator3_CSTATE[6];        /* '<S1>/Integrator3' */
} X_HILmodel_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator4_CSTATE[3];        /* '<S1>/Integrator4' */
  real_T Integrator2_CSTATE[3];        /* '<S1>/Integrator2' */
  real_T Integrator3_CSTATE[6];        /* '<S1>/Integrator3' */
} XDot_HILmodel_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator4_CSTATE[3];     /* '<S1>/Integrator4' */
  boolean_T Integrator2_CSTATE[3];     /* '<S1>/Integrator2' */
  boolean_T Integrator3_CSTATE[6];     /* '<S1>/Integrator3' */
} XDis_HILmodel_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator4_Reset_ZCE;    /* '<S1>/Integrator4' */
  ZCSigState Integrator2_Reset_ZCE;    /* '<S1>/Integrator2' */
  ZCSigState Integrator3_Reset_ZCE;    /* '<S1>/Integrator3' */
} PrevZCX_HILmodel_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            HILmodel_B
#define BlockIO                        B_HILmodel_T
#define rtX                            HILmodel_X
#define ContinuousStates               X_HILmodel_T
#define rtXdot                         HILmodel_XDot
#define StateDerivatives               XDot_HILmodel_T
#define tXdis                          HILmodel_XDis
#define StateDisabled                  XDis_HILmodel_T
#define rtP                            HILmodel_P
#define Parameters                     P_HILmodel_T
#define rtDWork                        HILmodel_DW
#define D_Work                         DW_HILmodel_T
#define rtPrevZCSigState               HILmodel_PrevZCX
#define PrevZCSigStates                PrevZCX_HILmodel_T

/* Parameters (auto storage) */
struct P_HILmodel_T_ {
  real_T D_L[36];                      /* Variable: D_L
                                        * Referenced by: '<Root>/D_L '
                                        */
  real_T D_NLxx[36];                   /* Variable: D_NLxx
                                        * Referenced by: '<S2>/D_NLxx '
                                        */
  real_T D_NLxy[36];                   /* Variable: D_NLxy
                                        * Referenced by: '<S3>/D_NLxy '
                                        */
  real_T M_A[36];                      /* Variable: M_A
                                        * Referenced by: '<Root>/M_A'
                                        */
  real_T M_RB[36];                     /* Variable: M_RB
                                        * Referenced by: '<Root>/M_RB'
                                        */
  real_T reset_P1;                     /* Expression: width
                                        * Referenced by: '<S1>/reset'
                                        */
  real_T reset_P2;                     /* Expression: dtype
                                        * Referenced by: '<S1>/reset'
                                        */
  real_T reset_P3;                     /* Expression: portnum
                                        * Referenced by: '<S1>/reset'
                                        */
  real_T reset_P4;                     /* Expression: stime
                                        * Referenced by: '<S1>/reset'
                                        */
  real_T reset_P5;                     /* Expression: stype
                                        * Referenced by: '<S1>/reset'
                                        */
  real_T reset_P6;                     /* Expression: btype
                                        * Referenced by: '<S1>/reset'
                                        */
  real_T eta_01_P1;                    /* Expression: width
                                        * Referenced by: '<S13>/eta_01'
                                        */
  real_T eta_01_P2;                    /* Expression: dtype
                                        * Referenced by: '<S13>/eta_01'
                                        */
  real_T eta_01_P3;                    /* Expression: portnum
                                        * Referenced by: '<S13>/eta_01'
                                        */
  real_T eta_01_P4;                    /* Expression: stime
                                        * Referenced by: '<S13>/eta_01'
                                        */
  real_T eta_01_P5;                    /* Expression: stype
                                        * Referenced by: '<S13>/eta_01'
                                        */
  real_T eta_01_P6;                    /* Expression: btype
                                        * Referenced by: '<S13>/eta_01'
                                        */
  real_T eta_02_P1;                    /* Expression: width
                                        * Referenced by: '<S13>/eta_02'
                                        */
  real_T eta_02_P2;                    /* Expression: dtype
                                        * Referenced by: '<S13>/eta_02'
                                        */
  real_T eta_02_P3;                    /* Expression: portnum
                                        * Referenced by: '<S13>/eta_02'
                                        */
  real_T eta_02_P4;                    /* Expression: stime
                                        * Referenced by: '<S13>/eta_02'
                                        */
  real_T eta_02_P5;                    /* Expression: stype
                                        * Referenced by: '<S13>/eta_02'
                                        */
  real_T eta_02_P6;                    /* Expression: btype
                                        * Referenced by: '<S13>/eta_02'
                                        */
  real_T eta_03_P1;                    /* Expression: width
                                        * Referenced by: '<S13>/eta_03'
                                        */
  real_T eta_03_P2;                    /* Expression: dtype
                                        * Referenced by: '<S13>/eta_03'
                                        */
  real_T eta_03_P3;                    /* Expression: portnum
                                        * Referenced by: '<S13>/eta_03'
                                        */
  real_T eta_03_P4;                    /* Expression: stime
                                        * Referenced by: '<S13>/eta_03'
                                        */
  real_T eta_03_P5;                    /* Expression: stype
                                        * Referenced by: '<S13>/eta_03'
                                        */
  real_T eta_03_P6;                    /* Expression: btype
                                        * Referenced by: '<S13>/eta_03'
                                        */
  real_T eta1_P1;                      /* Expression: width
                                        * Referenced by: '<S4>/eta1'
                                        */
  real_T eta1_P2;                      /* Expression: dtype
                                        * Referenced by: '<S4>/eta1'
                                        */
  real_T eta1_P3;                      /* Expression: portnum
                                        * Referenced by: '<S4>/eta1'
                                        */
  real_T eta1_P4;                      /* Expression: stime
                                        * Referenced by: '<S4>/eta1'
                                        */
  real_T eta1_P5;                      /* Expression: stype
                                        * Referenced by: '<S4>/eta1'
                                        */
  real_T eta1_P6;                      /* Expression: btype
                                        * Referenced by: '<S4>/eta1'
                                        */
  real_T eta2_P1;                      /* Expression: width
                                        * Referenced by: '<S4>/eta2'
                                        */
  real_T eta2_P2;                      /* Expression: dtype
                                        * Referenced by: '<S4>/eta2'
                                        */
  real_T eta2_P3;                      /* Expression: portnum
                                        * Referenced by: '<S4>/eta2'
                                        */
  real_T eta2_P4;                      /* Expression: stime
                                        * Referenced by: '<S4>/eta2'
                                        */
  real_T eta2_P5;                      /* Expression: stype
                                        * Referenced by: '<S4>/eta2'
                                        */
  real_T eta2_P6;                      /* Expression: btype
                                        * Referenced by: '<S4>/eta2'
                                        */
  real_T eta3_P1;                      /* Expression: width
                                        * Referenced by: '<S4>/eta3'
                                        */
  real_T eta3_P2;                      /* Expression: dtype
                                        * Referenced by: '<S4>/eta3'
                                        */
  real_T eta3_P3;                      /* Expression: portnum
                                        * Referenced by: '<S4>/eta3'
                                        */
  real_T eta3_P4;                      /* Expression: stime
                                        * Referenced by: '<S4>/eta3'
                                        */
  real_T eta3_P5;                      /* Expression: stype
                                        * Referenced by: '<S4>/eta3'
                                        */
  real_T eta3_P6;                      /* Expression: btype
                                        * Referenced by: '<S4>/eta3'
                                        */
  real_T eta_04_P1;                    /* Expression: width
                                        * Referenced by: '<S14>/eta_04'
                                        */
  real_T eta_04_P2;                    /* Expression: dtype
                                        * Referenced by: '<S14>/eta_04'
                                        */
  real_T eta_04_P3;                    /* Expression: portnum
                                        * Referenced by: '<S14>/eta_04'
                                        */
  real_T eta_04_P4;                    /* Expression: stime
                                        * Referenced by: '<S14>/eta_04'
                                        */
  real_T eta_04_P5;                    /* Expression: stype
                                        * Referenced by: '<S14>/eta_04'
                                        */
  real_T eta_04_P6;                    /* Expression: btype
                                        * Referenced by: '<S14>/eta_04'
                                        */
  real_T eta_05_P1;                    /* Expression: width
                                        * Referenced by: '<S14>/eta_05'
                                        */
  real_T eta_05_P2;                    /* Expression: dtype
                                        * Referenced by: '<S14>/eta_05'
                                        */
  real_T eta_05_P3;                    /* Expression: portnum
                                        * Referenced by: '<S14>/eta_05'
                                        */
  real_T eta_05_P4;                    /* Expression: stime
                                        * Referenced by: '<S14>/eta_05'
                                        */
  real_T eta_05_P5;                    /* Expression: stype
                                        * Referenced by: '<S14>/eta_05'
                                        */
  real_T eta_05_P6;                    /* Expression: btype
                                        * Referenced by: '<S14>/eta_05'
                                        */
  real_T eta_06_P1;                    /* Expression: width
                                        * Referenced by: '<S14>/eta_06'
                                        */
  real_T eta_06_P2;                    /* Expression: dtype
                                        * Referenced by: '<S14>/eta_06'
                                        */
  real_T eta_06_P3;                    /* Expression: portnum
                                        * Referenced by: '<S14>/eta_06'
                                        */
  real_T eta_06_P4;                    /* Expression: stime
                                        * Referenced by: '<S14>/eta_06'
                                        */
  real_T eta_06_P5;                    /* Expression: stype
                                        * Referenced by: '<S14>/eta_06'
                                        */
  real_T eta_06_P6;                    /* Expression: btype
                                        * Referenced by: '<S14>/eta_06'
                                        */
  real_T eta4_P1;                      /* Expression: width
                                        * Referenced by: '<S4>/eta4'
                                        */
  real_T eta4_P2;                      /* Expression: dtype
                                        * Referenced by: '<S4>/eta4'
                                        */
  real_T eta4_P3;                      /* Expression: portnum
                                        * Referenced by: '<S4>/eta4'
                                        */
  real_T eta4_P4;                      /* Expression: stime
                                        * Referenced by: '<S4>/eta4'
                                        */
  real_T eta4_P5;                      /* Expression: stype
                                        * Referenced by: '<S4>/eta4'
                                        */
  real_T eta4_P6;                      /* Expression: btype
                                        * Referenced by: '<S4>/eta4'
                                        */
  real_T eta5_P1;                      /* Expression: width
                                        * Referenced by: '<S4>/eta5'
                                        */
  real_T eta5_P2;                      /* Expression: dtype
                                        * Referenced by: '<S4>/eta5'
                                        */
  real_T eta5_P3;                      /* Expression: portnum
                                        * Referenced by: '<S4>/eta5'
                                        */
  real_T eta5_P4;                      /* Expression: stime
                                        * Referenced by: '<S4>/eta5'
                                        */
  real_T eta5_P5;                      /* Expression: stype
                                        * Referenced by: '<S4>/eta5'
                                        */
  real_T eta5_P6;                      /* Expression: btype
                                        * Referenced by: '<S4>/eta5'
                                        */
  real_T eta6_P1;                      /* Expression: width
                                        * Referenced by: '<S4>/eta6'
                                        */
  real_T eta6_P2;                      /* Expression: dtype
                                        * Referenced by: '<S4>/eta6'
                                        */
  real_T eta6_P3;                      /* Expression: portnum
                                        * Referenced by: '<S4>/eta6'
                                        */
  real_T eta6_P4;                      /* Expression: stime
                                        * Referenced by: '<S4>/eta6'
                                        */
  real_T eta6_P5;                      /* Expression: stype
                                        * Referenced by: '<S4>/eta6'
                                        */
  real_T eta6_P6;                      /* Expression: btype
                                        * Referenced by: '<S4>/eta6'
                                        */
  real_T eta1_P1_k;                    /* Expression: width
                                        * Referenced by: '<S15>/eta1'
                                        */
  real_T eta1_P2_k;                    /* Expression: dtype
                                        * Referenced by: '<S15>/eta1'
                                        */
  real_T eta1_P3_b;                    /* Expression: portnum
                                        * Referenced by: '<S15>/eta1'
                                        */
  real_T eta1_P4_a;                    /* Expression: stime
                                        * Referenced by: '<S15>/eta1'
                                        */
  real_T eta1_P5_j;                    /* Expression: stype
                                        * Referenced by: '<S15>/eta1'
                                        */
  real_T eta1_P6_l;                    /* Expression: btype
                                        * Referenced by: '<S15>/eta1'
                                        */
  real_T eta2_P1_h;                    /* Expression: width
                                        * Referenced by: '<S15>/eta2'
                                        */
  real_T eta2_P2_m;                    /* Expression: dtype
                                        * Referenced by: '<S15>/eta2'
                                        */
  real_T eta2_P3_c;                    /* Expression: portnum
                                        * Referenced by: '<S15>/eta2'
                                        */
  real_T eta2_P4_b;                    /* Expression: stime
                                        * Referenced by: '<S15>/eta2'
                                        */
  real_T eta2_P5_k;                    /* Expression: stype
                                        * Referenced by: '<S15>/eta2'
                                        */
  real_T eta2_P6_j;                    /* Expression: btype
                                        * Referenced by: '<S15>/eta2'
                                        */
  real_T eta3_P1_b;                    /* Expression: width
                                        * Referenced by: '<S15>/eta3'
                                        */
  real_T eta3_P2_j;                    /* Expression: dtype
                                        * Referenced by: '<S15>/eta3'
                                        */
  real_T eta3_P3_m;                    /* Expression: portnum
                                        * Referenced by: '<S15>/eta3'
                                        */
  real_T eta3_P4_f;                    /* Expression: stime
                                        * Referenced by: '<S15>/eta3'
                                        */
  real_T eta3_P5_h;                    /* Expression: stype
                                        * Referenced by: '<S15>/eta3'
                                        */
  real_T eta3_P6_b;                    /* Expression: btype
                                        * Referenced by: '<S15>/eta3'
                                        */
  real_T eta4_P1_e;                    /* Expression: width
                                        * Referenced by: '<S15>/eta4'
                                        */
  real_T eta4_P2_l;                    /* Expression: dtype
                                        * Referenced by: '<S15>/eta4'
                                        */
  real_T eta4_P3_o;                    /* Expression: portnum
                                        * Referenced by: '<S15>/eta4'
                                        */
  real_T eta4_P4_a;                    /* Expression: stime
                                        * Referenced by: '<S15>/eta4'
                                        */
  real_T eta4_P5_a;                    /* Expression: stype
                                        * Referenced by: '<S15>/eta4'
                                        */
  real_T eta4_P6_j;                    /* Expression: btype
                                        * Referenced by: '<S15>/eta4'
                                        */
  real_T eta5_P1_d;                    /* Expression: width
                                        * Referenced by: '<S15>/eta5'
                                        */
  real_T eta5_P2_b;                    /* Expression: dtype
                                        * Referenced by: '<S15>/eta5'
                                        */
  real_T eta5_P3_m;                    /* Expression: portnum
                                        * Referenced by: '<S15>/eta5'
                                        */
  real_T eta5_P4_k;                    /* Expression: stime
                                        * Referenced by: '<S15>/eta5'
                                        */
  real_T eta5_P5_i;                    /* Expression: stype
                                        * Referenced by: '<S15>/eta5'
                                        */
  real_T eta5_P6_a;                    /* Expression: btype
                                        * Referenced by: '<S15>/eta5'
                                        */
  real_T eta6_P1_g;                    /* Expression: width
                                        * Referenced by: '<S15>/eta6'
                                        */
  real_T eta6_P2_g;                    /* Expression: dtype
                                        * Referenced by: '<S15>/eta6'
                                        */
  real_T eta6_P3_c;                    /* Expression: portnum
                                        * Referenced by: '<S15>/eta6'
                                        */
  real_T eta6_P4_f;                    /* Expression: stime
                                        * Referenced by: '<S15>/eta6'
                                        */
  real_T eta6_P5_o;                    /* Expression: stype
                                        * Referenced by: '<S15>/eta6'
                                        */
  real_T eta6_P6_i;                    /* Expression: btype
                                        * Referenced by: '<S15>/eta6'
                                        */
  real_T nu1_P1;                       /* Expression: width
                                        * Referenced by: '<S5>/nu1'
                                        */
  real_T nu1_P2;                       /* Expression: dtype
                                        * Referenced by: '<S5>/nu1'
                                        */
  real_T nu1_P3;                       /* Expression: portnum
                                        * Referenced by: '<S5>/nu1'
                                        */
  real_T nu1_P4;                       /* Expression: stime
                                        * Referenced by: '<S5>/nu1'
                                        */
  real_T nu1_P5;                       /* Expression: stype
                                        * Referenced by: '<S5>/nu1'
                                        */
  real_T nu1_P6;                       /* Expression: btype
                                        * Referenced by: '<S5>/nu1'
                                        */
  real_T nu2_P1;                       /* Expression: width
                                        * Referenced by: '<S5>/nu2'
                                        */
  real_T nu2_P2;                       /* Expression: dtype
                                        * Referenced by: '<S5>/nu2'
                                        */
  real_T nu2_P3;                       /* Expression: portnum
                                        * Referenced by: '<S5>/nu2'
                                        */
  real_T nu2_P4;                       /* Expression: stime
                                        * Referenced by: '<S5>/nu2'
                                        */
  real_T nu2_P5;                       /* Expression: stype
                                        * Referenced by: '<S5>/nu2'
                                        */
  real_T nu2_P6;                       /* Expression: btype
                                        * Referenced by: '<S5>/nu2'
                                        */
  real_T nu3_P1;                       /* Expression: width
                                        * Referenced by: '<S5>/nu3'
                                        */
  real_T nu3_P2;                       /* Expression: dtype
                                        * Referenced by: '<S5>/nu3'
                                        */
  real_T nu3_P3;                       /* Expression: portnum
                                        * Referenced by: '<S5>/nu3'
                                        */
  real_T nu3_P4;                       /* Expression: stime
                                        * Referenced by: '<S5>/nu3'
                                        */
  real_T nu3_P5;                       /* Expression: stype
                                        * Referenced by: '<S5>/nu3'
                                        */
  real_T nu3_P6;                       /* Expression: btype
                                        * Referenced by: '<S5>/nu3'
                                        */
  real_T nu4_P1;                       /* Expression: width
                                        * Referenced by: '<S5>/nu4'
                                        */
  real_T nu4_P2;                       /* Expression: dtype
                                        * Referenced by: '<S5>/nu4'
                                        */
  real_T nu4_P3;                       /* Expression: portnum
                                        * Referenced by: '<S5>/nu4'
                                        */
  real_T nu4_P4;                       /* Expression: stime
                                        * Referenced by: '<S5>/nu4'
                                        */
  real_T nu4_P5;                       /* Expression: stype
                                        * Referenced by: '<S5>/nu4'
                                        */
  real_T nu4_P6;                       /* Expression: btype
                                        * Referenced by: '<S5>/nu4'
                                        */
  real_T nu5_P1;                       /* Expression: width
                                        * Referenced by: '<S5>/nu5'
                                        */
  real_T nu5_P2;                       /* Expression: dtype
                                        * Referenced by: '<S5>/nu5'
                                        */
  real_T nu5_P3;                       /* Expression: portnum
                                        * Referenced by: '<S5>/nu5'
                                        */
  real_T nu5_P4;                       /* Expression: stime
                                        * Referenced by: '<S5>/nu5'
                                        */
  real_T nu5_P5;                       /* Expression: stype
                                        * Referenced by: '<S5>/nu5'
                                        */
  real_T nu5_P6;                       /* Expression: btype
                                        * Referenced by: '<S5>/nu5'
                                        */
  real_T nu6_P1;                       /* Expression: width
                                        * Referenced by: '<S5>/nu6'
                                        */
  real_T nu6_P2;                       /* Expression: dtype
                                        * Referenced by: '<S5>/nu6'
                                        */
  real_T nu6_P3;                       /* Expression: portnum
                                        * Referenced by: '<S5>/nu6'
                                        */
  real_T nu6_P4;                       /* Expression: stime
                                        * Referenced by: '<S5>/nu6'
                                        */
  real_T nu6_P5;                       /* Expression: stype
                                        * Referenced by: '<S5>/nu6'
                                        */
  real_T nu6_P6;                       /* Expression: btype
                                        * Referenced by: '<S5>/nu6'
                                        */
  real_T Gain_Gain;                    /* Expression: 0.5
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: -1
                                        * Referenced by: '<S8>/Gain1'
                                        */
  real_T Gain2_Gain;                   /* Expression: -1
                                        * Referenced by: '<S8>/Gain2'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 0.5
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T nu_c1_P1;                     /* Expression: width
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  real_T nu_c1_P2;                     /* Expression: dtype
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  real_T nu_c1_P3;                     /* Expression: portnum
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  real_T nu_c1_P4;                     /* Expression: stime
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  real_T nu_c1_P5;                     /* Expression: stype
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  real_T nu_c1_P6;                     /* Expression: btype
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  real_T nu_c2_P1;                     /* Expression: width
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  real_T nu_c2_P2;                     /* Expression: dtype
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  real_T nu_c2_P3;                     /* Expression: portnum
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  real_T nu_c2_P4;                     /* Expression: stime
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  real_T nu_c2_P5;                     /* Expression: stype
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  real_T nu_c2_P6;                     /* Expression: btype
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  real_T nu_c_onoff_P1;                /* Expression: width
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  real_T nu_c_onoff_P2;                /* Expression: dtype
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  real_T nu_c_onoff_P3;                /* Expression: portnum
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  real_T nu_c_onoff_P4;                /* Expression: stime
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  real_T nu_c_onoff_P5;                /* Expression: stype
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  real_T nu_c_onoff_P6;                /* Expression: btype
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  real_T Constant3_Value[6];           /* Expression: zeros(6,1)
                                        * Referenced by: '<S6>/Constant3'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S6>/Constant1'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S6>/Constant2'
                                        */
  real_T Constant4_Value;              /* Expression: 0
                                        * Referenced by: '<S6>/Constant4'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: -1
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real_T Gain2_Gain_o;                 /* Expression: -1
                                        * Referenced by: '<S9>/Gain2'
                                        */
  real_T Constant_Value_c;             /* Expression: 1
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Constant_Value_e;             /* Expression: 0
                                        * Referenced by: '<S11>/Constant '
                                        */
  real_T tau1_P1;                      /* Expression: width
                                        * Referenced by: '<S7>/tau1'
                                        */
  real_T tau1_P2;                      /* Expression: dtype
                                        * Referenced by: '<S7>/tau1'
                                        */
  real_T tau1_P3;                      /* Expression: portnum
                                        * Referenced by: '<S7>/tau1'
                                        */
  real_T tau1_P4;                      /* Expression: stime
                                        * Referenced by: '<S7>/tau1'
                                        */
  real_T tau1_P5;                      /* Expression: stype
                                        * Referenced by: '<S7>/tau1'
                                        */
  real_T tau1_P6;                      /* Expression: btype
                                        * Referenced by: '<S7>/tau1'
                                        */
  real_T tau2_P1;                      /* Expression: width
                                        * Referenced by: '<S7>/tau2'
                                        */
  real_T tau2_P2;                      /* Expression: dtype
                                        * Referenced by: '<S7>/tau2'
                                        */
  real_T tau2_P3;                      /* Expression: portnum
                                        * Referenced by: '<S7>/tau2'
                                        */
  real_T tau2_P4;                      /* Expression: stime
                                        * Referenced by: '<S7>/tau2'
                                        */
  real_T tau2_P5;                      /* Expression: stype
                                        * Referenced by: '<S7>/tau2'
                                        */
  real_T tau2_P6;                      /* Expression: btype
                                        * Referenced by: '<S7>/tau2'
                                        */
  real_T tau3_P1;                      /* Expression: width
                                        * Referenced by: '<S7>/tau3'
                                        */
  real_T tau3_P2;                      /* Expression: dtype
                                        * Referenced by: '<S7>/tau3'
                                        */
  real_T tau3_P3;                      /* Expression: portnum
                                        * Referenced by: '<S7>/tau3'
                                        */
  real_T tau3_P4;                      /* Expression: stime
                                        * Referenced by: '<S7>/tau3'
                                        */
  real_T tau3_P5;                      /* Expression: stype
                                        * Referenced by: '<S7>/tau3'
                                        */
  real_T tau3_P6;                      /* Expression: btype
                                        * Referenced by: '<S7>/tau3'
                                        */
  real_T tau4_P1;                      /* Expression: width
                                        * Referenced by: '<S7>/tau4'
                                        */
  real_T tau4_P2;                      /* Expression: dtype
                                        * Referenced by: '<S7>/tau4'
                                        */
  real_T tau4_P3;                      /* Expression: portnum
                                        * Referenced by: '<S7>/tau4'
                                        */
  real_T tau4_P4;                      /* Expression: stime
                                        * Referenced by: '<S7>/tau4'
                                        */
  real_T tau4_P5;                      /* Expression: stype
                                        * Referenced by: '<S7>/tau4'
                                        */
  real_T tau4_P6;                      /* Expression: btype
                                        * Referenced by: '<S7>/tau4'
                                        */
  real_T tau5_P1;                      /* Expression: width
                                        * Referenced by: '<S7>/tau5'
                                        */
  real_T tau5_P2;                      /* Expression: dtype
                                        * Referenced by: '<S7>/tau5'
                                        */
  real_T tau5_P3;                      /* Expression: portnum
                                        * Referenced by: '<S7>/tau5'
                                        */
  real_T tau5_P4;                      /* Expression: stime
                                        * Referenced by: '<S7>/tau5'
                                        */
  real_T tau5_P5;                      /* Expression: stype
                                        * Referenced by: '<S7>/tau5'
                                        */
  real_T tau5_P6;                      /* Expression: btype
                                        * Referenced by: '<S7>/tau5'
                                        */
  real_T tau6_P1;                      /* Expression: width
                                        * Referenced by: '<S7>/tau6'
                                        */
  real_T tau6_P2;                      /* Expression: dtype
                                        * Referenced by: '<S7>/tau6'
                                        */
  real_T tau6_P3;                      /* Expression: portnum
                                        * Referenced by: '<S7>/tau6'
                                        */
  real_T tau6_P4;                      /* Expression: stime
                                        * Referenced by: '<S7>/tau6'
                                        */
  real_T tau6_P5;                      /* Expression: stype
                                        * Referenced by: '<S7>/tau6'
                                        */
  real_T tau6_P6;                      /* Expression: btype
                                        * Referenced by: '<S7>/tau6'
                                        */
  real_T D_NL_onoff_P1;                /* Expression: width
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P2;                /* Expression: dtype
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P3;                /* Expression: portnum
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P4;                /* Expression: stime
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P5;                /* Expression: stype
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P6;                /* Expression: btype
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  real_T D_NL0_Value[36];              /* Expression: zeros(6,6)
                                        * Referenced by: '<S2>/D_NL=0'
                                        */
  real_T D_NL_onoff_P1_m;              /* Expression: width
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P2_l;              /* Expression: dtype
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P3_p;              /* Expression: portnum
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P4_b;              /* Expression: stime
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P5_f;              /* Expression: stype
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  real_T D_NL_onoff_P6_n;              /* Expression: btype
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  real_T D_NL0_Value_n[36];            /* Expression: zeros(6,6)
                                        * Referenced by: '<S3>/D_NL=0'
                                        */
  real_T Constant_Value_h[6];          /* Expression: zeros(6,1)
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Constant1_Value_l[6];         /* Expression: [0 1 0 0 0 1]
                                        * Referenced by: '<S12>/Constant1'
                                        */
  real_T Constant2_Value_f[18];        /* Expression: zeros(6,3)
                                        * Referenced by: '<S12>/Constant2'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_HILmodel_T {
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
    real_T odeY[12];
    real_T odeF[4][12];
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
extern P_HILmodel_T HILmodel_P;

/* Block signals (auto storage) */
extern B_HILmodel_T HILmodel_B;

/* Continuous states (auto storage) */
extern X_HILmodel_T HILmodel_X;

/* Block states (auto storage) */
extern DW_HILmodel_T HILmodel_DW;

/* Model entry point functions */
extern void HILmodel_initialize(void);
extern void HILmodel_output(void);
extern void HILmodel_update(void);
extern void HILmodel_terminate(void);

/* Real-time Model object */
extern RT_MODEL_HILmodel_T *const HILmodel_M;

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
 * '<Root>' : 'HILmodel'
 * '<S1>'   : 'HILmodel/6 DOF Eqs. of motion (under construction)'
 * '<S2>'   : 'HILmodel/D_NLxx from LabVIEW'
 * '<S3>'   : 'HILmodel/D_NLxx from LabVIEW1'
 * '<S4>'   : 'HILmodel/eta to LabVIEW'
 * '<S5>'   : 'HILmodel/nu to LabVIEW'
 * '<S6>'   : 'HILmodel/nu_c from LabVIEW'
 * '<S7>'   : 'HILmodel/tau from LabVIEW'
 * '<S8>'   : 'HILmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces'
 * '<S9>'   : 'HILmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1'
 * '<S10>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/Euler angles to rotation matrix'
 * '<S11>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/Euler angles to attitude transformation matrix'
 * '<S12>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/Subsystem'
 * '<S13>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2'
 * '<S14>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1'
 * '<S15>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW'
 * '<S16>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/3x3 cross product'
 * '<S17>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/3x3 cross product1'
 * '<S18>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/3x3 cross product2'
 * '<S19>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/3x3 cross product'
 * '<S20>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/3x3 cross product1'
 * '<S21>'  : 'HILmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/3x3 cross product2'
 */
#endif                                 /* RTW_HEADER_HILmodel_h_ */

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_HILmodel
#ifndef NI_VERISTAND_MODELDATAFILE
#ifdef NI_VERISTAND_MAINMODELFILE

int READSIDE = 0;
int tid = 0;

#ifdef MULTITASKING

P_HILmodel_T rtParameter[NUMST+!TID01EQ];
P_HILmodel_T *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

P_HILmodel_T rtParameter[2];

#endif

#else

extern int READSIDE;

#ifdef MULTITASKING

extern int tid;
extern P_HILmodel_T* param_lookup[NUMST][2];

#else

extern P_HILmodel_T rtParameter[];

#endif
#endif

#ifdef MULTITASKING
#define HILmodel_P                     (*param_lookup[tid][READSIDE])
#else
#define HILmodel_P                     rtParameter[READSIDE]
#endif
#endif
#endif
