/*
 * modell.h
 *
 * Real-Time Workshop code generation for Simulink model "modell.mdl".
 *
 * Model Version              : 1.149
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Tue Mar 12 15:06:30 2013
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_modell_h_
#define RTW_HEADER_modell_h_
#ifndef modell_COMMON_INCLUDES_
# define modell_COMMON_INCLUDES_
#include <stddef.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "rt_zcfcn.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_SATURATE.h"
#include "rt_SIGNd_snf.h"
#include "rt_atan2_snf.h"
#include "rt_hypot_snf.h"
#include "rt_rand.h"
#include "rt_rem_snf.h"
#include "rt_round_snf.h"
#endif                                 /* modell_COMMON_INCLUDES_ */

#include "modell_types.h"

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
# define rtmGetRootDWork(rtm)          ((rtm)->Work.dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->Work.dwork = (val))
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
# define rtmGetDWork(rtm, idx)         ((rtm)->Work.dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->Work.dwork[idx] = (val))
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

#ifndef rtmGetVarNextHitTime
# define rtmGetVarNextHitTime(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTime
# define rtmSetVarNextHitTime(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
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
#define modell_rtModel                 RT_MODEL_modell

/* Block signals for system '<S32>/if' */
typedef struct {
  real_T In1;                          /* '<S37>/In1' */
} rtB_if_modell;

/* Block signals for system '<S44>/slack' */
typedef struct {
  real_T In1[3];                       /* '<S49>/In1' */
} rtB_slack_modell;

/* Block signals (auto storage) */
typedef struct {
  real_T Constant;                     /* '<Root>/Constant' */
  real_T Integrator1[3];               /* '<S2>/Integrator1' */
  real_T initial_nu_hil[3];            /* '<S2>/initial_nu_hil' */
  real_T Integrator[3];                /* '<S2>/Integrator' */
  real_T nu_surge_hil;                 /* '<S2>/nu_surge_hil' */
  real_T nu_sway_hil;                  /* '<S2>/nu_sway_hil' */
  real_T nu_yaw_hil;                   /* '<S2>/nu_yaw_hil' */
  real_T TransferFcn;                  /* '<S5>/Transfer Fcn' */
  real_T TransferFcn1;                 /* '<S5>/Transfer Fcn1' */
  real_T TransferFcn2;                 /* '<S5>/Transfer Fcn2' */
  real_T initialposition[3];           /* '<S3>/initial position' */
  real_T Integrator1_e[3];             /* '<S3>/Integrator1' */
  real_T Integrator2[3];               /* '<S3>/Integrator2' */
  real_T pos_diff[3];                  /* '<S12>/pos_diff' */
  real_T Integrator_l[3];              /* '<S12>/Integrator' */
  real_T mf1;                          /* '<S46>/mf1' */
  real_T mf2;                          /* '<S46>/mf2' */
  real_T Sum;                          /* '<S46>/Sum' */
  real_T mf3;                          /* '<S46>/mf3' */
  real_T T_temp[3];                    /* '<S44>/T_temp' */
  real_T mf1_j;                        /* '<S47>/mf1' */
  real_T mf2_m;                        /* '<S47>/mf2' */
  real_T Sum_p;                        /* '<S47>/Sum' */
  real_T mf3_f;                        /* '<S47>/mf3' */
  real_T Sum2[3];                      /* '<S44>/Sum2' */
  real_T IC[3];                        /* '<S12>/IC' */
  real_T Integrator_n[3];              /* '<S13>/Integrator' */
  real_T SwitchControl[3];             /* '<S52>/SwitchControl' */
  real_T wavehat[6];                   /* '<S8>/wave hat' */
  real_T C_w[3];                       /* '<S8>/C_w' */
  real_T eta_hat[3];                   /* '<S8>/eta_hat' */
  real_T Sum6[3];                      /* '<S8>/Sum6' */
  real_T nu_hat[3];                    /* '<S8>/nu_hat' */
  real_T wavehat_n[6];                 /* '<S7>/wave hat' */
  real_T C_w_d[3];                     /* '<S7>/C_w' */
  real_T eta_hat_m[3];                 /* '<S7>/eta_hat' */
  real_T Sum6_a[3];                    /* '<S7>/Sum6' */
  real_T nu_hat_n[3];                  /* '<S7>/nu_hat' */
  real_T Abs;                          /* '<S33>/Abs' */
  real_T Gain1;                        /* '<S9>/Gain1' */
  real_T Sum_b;                        /* '<S33>/Sum' */
  real_T Abs_n;                        /* '<S32>/Abs' */
  real_T Gain;                         /* '<S9>/Gain' */
  real_T Sum_i;                        /* '<S32>/Sum' */
  real_T Abs_o;                        /* '<S35>/Abs' */
  real_T Gain3;                        /* '<S9>/Gain3' */
  real_T Sum_e;                        /* '<S35>/Sum' */
  real_T Abs_d;                        /* '<S34>/Abs' */
  real_T Gain2;                        /* '<S9>/Gain2' */
  real_T Sum_d;                        /* '<S34>/Sum' */
  real_T Sum3;                         /* '<S9>/Sum3' */
  real_T g1;                           /* '<S9>/g1' */
  real_T Sum4;                         /* '<S9>/Sum4' */
  real_T g2;                           /* '<S9>/g2' */
  real_T Product[15];                  /* '<S4>/Product' */
  real_T joystick_gain_surge;          /* '<S4>/joystick_gain_surge' */
  real_T joystick_gain_sway;           /* '<S4>/joystick_gain_sway' */
  real_T Sum_c;                        /* '<S4>/Sum' */
  real_T joystick_gain_yaw;            /* '<S4>/joystick_gain_yaw' */
  real_T TmpHiddenBufferAtProduct1Inport[3];/* 'synthesized block' */
  real_T Product1[5];                  /* '<S4>/Product1' */
  real_T Saturation[5];                /* '<S4>/Saturation' */
  real_T Product_c[15];                /* '<S11>/Product' */
  real_T Sum_pv[3];                    /* '<S11>/Sum' */
  real_T MultiportSwitch[7];           /* '<Root>/Multiport Switch' */
  real_T BT_power;                     /* '<S2>/BT_power' */
  real_T xr;                           /* '<S19>/x->r' */
  real_T xtheta;                       /* '<S19>/x->theta' */
  real_T xr_i;                         /* '<S20>/x->r' */
  real_T xtheta_d;                     /* '<S20>/x->theta' */
  real_T D[3];                         /* '<S2>/D' */
  real_T u1_hil;                       /* '<S2>/u1_hil' */
  real_T u2_hil;                       /* '<S2>/u2_hil' */
  real_T u3_hil;                       /* '<S2>/u3_hil' */
  real_T u4_hil;                       /* '<S2>/u4_hil' */
  real_T sampletime;                   /* '<S21>/sample time' */
  real_T deltariselimit;               /* '<S21>/delta rise limit' */
  real_T Yk1;                          /* '<S21>/Delay Input2' */
  real_T UkYk1;                        /* '<S21>/Difference Inputs1' */
  real_T neg;                          /* '<S2>/neg' */
  real_T deltafalllimit;               /* '<S21>/delta fall limit' */
  real_T Switch;                       /* '<S23>/Switch' */
  real_T Switch2;                      /* '<S23>/Switch2' */
  real_T DifferenceInputs2;            /* '<S21>/Difference Inputs2' */
  real_T u5_hil;                       /* '<S2>/u5_hil' */
  real_T TmpHiddenBufferAtProductInport3[5];/* 'synthesized block' */
  real_T Product_o[3];                 /* '<S2>/Product' */
  real_T x_dot;                        /* '<S22>/Fcn' */
  real_T y_dot;                        /* '<S22>/Fcn1' */
  real_T psi_dot;                      /* '<S22>/Fcn2' */
  real_T tau_surge_hil;                /* '<S2>/tau_surge_hil' */
  real_T tau_sway_hil;                 /* '<S2>/tau_sway_hil' */
  real_T tau_yaw_hil;                  /* '<S2>/tau_yaw_hil' */
  real_T Sum3_o[3];                    /* '<S2>/Sum3' */
  real_T VIS_HIL_E;                    /* '<S2>/VIS_HIL_E' */
  real_T VIS_HIL_N;                    /* '<S2>/VIS_HIL_N' */
  real_T VIS_HIL_PIS;                  /* '<S2>/VIS_HIL_PIS' */
  real_T VSP_angle_deg_port;           /* '<S2>/VSP_angle_deg_port' */
  real_T VSP_angle_deg_stbd;           /* '<S2>/VSP_angle_deg_stbd' */
  real_T invM[3];                      /* '<S2>/inv(M)' */
  real_T D_f[3];                       /* '<S3>/D' */
  real_T x_dot_a;                      /* '<S24>/Fcn' */
  real_T y_dot_g;                      /* '<S24>/Fcn1' */
  real_T psi_dot_p;                    /* '<S24>/Fcn2' */
  real_T Saturation_l;                 /* '<S25>/Saturation' */
  real_T Saturation1;                  /* '<S25>/Saturation1' */
  real_T Saturation2;                  /* '<S25>/Saturation2' */
  real_T Integrator1_n[3];             /* '<S13>/Integrator1' */
  real_T SwitchControl_o[3];           /* '<S53>/SwitchControl' */
  real_T Sum3_f[3];                    /* '<S3>/Sum3' */
  real_T invM_g[3];                    /* '<S3>/inv(M)' */
  real_T A_w[6];                       /* '<S7>/A_w' */
  real_T D_fe[3];                      /* '<S7>/D' */
  real_T Sum_n[3];                     /* '<S7>/Sum' */
  real_T K_1[6];                       /* '<S7>/K_1' */
  real_T K_2[3];                       /* '<S7>/K_2' */
  real_T K_3[3];                       /* '<S7>/K_3' */
  real_T K_4[3];                       /* '<S7>/K_4' */
  real_T bias_hat_integrator[3];       /* '<S7>/bias_hat_integrator' */
  real_T Row1;                         /* '<S27>/Row1' */
  real_T Row2;                         /* '<S27>/Row2' */
  real_T Row3;                         /* '<S27>/Row3' */
  real_T Row1_d;                       /* '<S26>/Row1' */
  real_T Row2_p;                       /* '<S26>/Row2' */
  real_T Row3_j;                       /* '<S26>/Row3' */
  real_T Sum1[3];                      /* '<S7>/Sum1' */
  real_T Sum4_o[3];                    /* '<S7>/Sum4' */
  real_T M_inv[3];                     /* '<S7>/M_inv' */
  real_T x_dot_f;                      /* '<S28>/Fcn' */
  real_T y_dot_m;                      /* '<S28>/Fcn1' */
  real_T psi_dot_g;                    /* '<S28>/Fcn2' */
  real_T T_inv[3];                     /* '<S7>/T_inv' */
  real_T Sum2_b[3];                    /* '<S7>/Sum2' */
  real_T Sum3_g[3];                    /* '<S7>/Sum3' */
  real_T Sum5[6];                      /* '<S7>/Sum5' */
  real_T A_w_l[6];                     /* '<S8>/A_w' */
  real_T D_n[3];                       /* '<S8>/D' */
  real_T Sum_h[3];                     /* '<S8>/Sum' */
  real_T K_1_d[6];                     /* '<S8>/K_1' */
  real_T K_2_n[3];                     /* '<S8>/K_2' */
  real_T K_3_j[3];                     /* '<S8>/K_3' */
  real_T K_4_j[3];                     /* '<S8>/K_4' */
  real_T bias_hat_integrator_a[3];     /* '<S8>/bias_hat_integrator' */
  real_T Row1_m;                       /* '<S30>/Row1' */
  real_T Row2_c;                       /* '<S30>/Row2' */
  real_T Row3_i;                       /* '<S30>/Row3' */
  real_T Row1_a;                       /* '<S29>/Row1' */
  real_T Row2_g;                       /* '<S29>/Row2' */
  real_T Row3_n;                       /* '<S29>/Row3' */
  real_T Sum1_g[3];                    /* '<S8>/Sum1' */
  real_T Sum4_l[3];                    /* '<S8>/Sum4' */
  real_T M_inv_d[3];                   /* '<S8>/M_inv' */
  real_T x_dot_l;                      /* '<S31>/Fcn' */
  real_T y_dot_i;                      /* '<S31>/Fcn1' */
  real_T psi_dot_j;                    /* '<S31>/Fcn2' */
  real_T T_inv_i[3];                   /* '<S8>/T_inv' */
  real_T Sum2_k[3];                    /* '<S8>/Sum2' */
  real_T Sum3_i[3];                    /* '<S8>/Sum3' */
  real_T Sum5_a[6];                    /* '<S8>/Sum5' */
  real_T Sum_d0[3];                    /* '<S12>/Sum' */
  real_T mf1_js;                       /* '<S45>/mf1' */
  real_T mf2_d;                        /* '<S45>/mf2' */
  real_T Sum_pn;                       /* '<S45>/Sum' */
  real_T mf3_l;                        /* '<S45>/mf3' */
  real_T WhiteNoise;                   /* '<S51>/White Noise' */
  real_T Output[3];                    /* '<S51>/Output' */
  real_T E_b_i[3];                     /* '<S13>/E_b_i' */
  real_T E_b_s[3];                     /* '<S13>/E_b_s' */
  real_T T_s_inv[3];                   /* '<S13>/T_s_inv' */
  real_T Sum_iz[3];                    /* '<S13>/Sum' */
  real_T T_i_inv[3];                   /* '<S13>/T_i_inv' */
  real_T Sum1_i[3];                    /* '<S13>/Sum1' */
  real_T Row1_k;                       /* '<S55>/Row1' */
  real_T Row2_g1;                      /* '<S55>/Row2' */
  real_T Row3_d;                       /* '<S55>/Row3' */
  real_T Row1_av;                      /* '<S54>/Row1' */
  real_T Row2_e;                       /* '<S54>/Row2' */
  real_T Row3_it;                      /* '<S54>/Row3' */
  real_T Integrator_ln[3];             /* '<S15>/Integrator' */
  real_T TmpHiddenBufferAtKdInport1[3];/* 'synthesized block' */
  real_T Kd[3];                        /* '<S15>/Kd' */
  real_T Ki[3];                        /* '<S15>/Ki' */
  real_T psi;                          /* '<S15>/yaw angle' */
  real_T Saturation_o;                 /* '<S18>/Saturation' */
  real_T Sign;                         /* '<S18>/Sign' */
  real_T Gain_a;                       /* '<S18>/Gain' */
  real_T Sum1_f;                       /* '<S18>/Sum1' */
  real_T MathFunction;                 /* '<S18>/Math Function' */
  real_T Sum_l;                        /* '<S18>/Sum' */
  real_T regulationerror[3];           /* '<S15>/Sum2' */
  real_T Reg_e_N_hil;                  /* '<S15>/Reg_e_N_hil' */
  real_T Reg_e_E_hil;                  /* '<S15>/Reg_e_E_hil' */
  real_T Reg_e_Psi_hil;                /* '<S15>/Reg_e_Psi_hil' */
  real_T Saturation_f;                 /* '<S17>/Saturation' */
  real_T Sign_l;                       /* '<S17>/Sign' */
  real_T Gain_h;                       /* '<S17>/Gain' */
  real_T Sum1_h;                       /* '<S17>/Sum1' */
  real_T MathFunction_i;               /* '<S17>/Math Function' */
  real_T Sum_nl;                       /* '<S17>/Sum' */
  real_T Row1_e;                       /* '<S16>/Row1' */
  real_T Row2_o;                       /* '<S16>/Row2' */
  real_T Row3_g;                       /* '<S16>/Row3' */
  real_T TmpHiddenBufferAtKpInport1[3];/* '<S15>/Transposed rotation  matrix in yaw1' */
  real_T Kp[3];                        /* '<S15>/Kp' */
  real_T Product_l[3];                 /* '<S15>/Product' */
  real_T Product1_j[3];                /* '<S15>/Product1' */
  real_T Product2[3];                  /* '<S15>/Product2' */
  real_T Sum3_d[3];                    /* '<S15>/Sum3' */
  real_T Sum1_hw[3];                   /* '<S15>/Sum1' */
  real_T U1;                           /* '<S6>/U1' */
  real_T U2;                           /* '<S6>/U2' */
  real_T U3;                           /* '<S6>/U3' */
  real_T U4;                           /* '<S6>/U4' */
  real_T Sum_ej;                       /* '<S6>/Sum' */
  real_T U5;                           /* '<S6>/U5' */
  real_T Product1_o[5];                /* '<S11>/Product1' */
  real_T Saturation_a[5];              /* '<S11>/Saturation' */
  uint8_T Compare;                     /* '<S14>/Compare' */
  boolean_T LowerRelop1;               /* '<S23>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S23>/UpperRelop' */
  rtB_slack_modell towing;             /* '<S44>/towing' */
  rtB_slack_modell rupture;            /* '<S44>/rupture' */
  rtB_slack_modell slack;              /* '<S44>/slack' */
  rtB_if_modell else_aj;               /* '<S35>/else' */
  rtB_if_modell if_k;                  /* '<S35>/if' */
  rtB_if_modell else_d;                /* '<S34>/else' */
  rtB_if_modell if_i;                  /* '<S34>/if' */
  rtB_if_modell else_a;                /* '<S33>/else' */
  rtB_if_modell if_f;                  /* '<S33>/if' */
  rtB_if_modell else_j;                /* '<S32>/else' */
  rtB_if_modell if_j;                  /* '<S32>/if' */
} BlockIO_modell;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T DelayInput2_DSTATE;           /* '<S21>/Delay Input2' */
  real_T IC_FirstOutputTime;           /* '<S12>/IC' */
  real_T Product_DWORK1[5];            /* '<S2>/Product' */
  real_T NextOutput;                   /* '<S51>/White Noise' */
  struct {
    void *LoggedData;
  } ToWorkspace_PWORK;                 /* '<S10>/To Workspace' */

  struct {
    void *LoggedData;
  } eta_sscope_PWORK;                  /* '<S10>/eta_s scope' */

  struct {
    void *LoggedData;
  } ToWorkspace1_PWORK;                /* '<S10>/To Workspace1' */

  struct {
    void *LoggedData;
  } nu_sscope_PWORK;                   /* '<S10>/nu_s scope' */

  struct {
    void *LoggedData;
  } ToWorkspace4_PWORK;                /* '<S10>/To Workspace4' */

  struct {
    void *LoggedData;
  } eta_dscope_PWORK;                  /* '<S10>/eta_d scope' */

  struct {
    void *LoggedData;
  } ToWorkspace2_PWORK;                /* '<S10>/To Workspace2' */

  struct {
    void *LoggedData;
  } eta_iscope_PWORK;                  /* '<S10>/eta_i scope' */

  struct {
    void *LoggedData;
  } ToWorkspace3_PWORK;                /* '<S10>/To Workspace3' */

  struct {
    void *LoggedData;
  } nu_iscope_PWORK;                   /* '<S10>/nu_i scope' */

  struct {
    void *LoggedData;
  } ToWorkspace5_PWORK;                /* '<S10>/To Workspace5' */

  struct {
    void *LoggedData;
  } towforcescope_PWORK;               /* '<S10>/towforce scope' */

  struct {
    void *LoggedData;
  } ToWorkspace6_PWORK;                /* '<S10>/To Workspace6' */

  struct {
    void *LoggedData;
  } Xscope_PWORK;                      /* '<S10>/X scope' */

  struct {
    void *LoggedData;
  } ToWorkspace7_PWORK;                /* '<S10>/To Workspace7' */

  struct {
    void *LoggedData;
  } bias_sscope_PWORK;                 /* '<S10>/bias_s scope' */

  struct {
    void *LoggedData;
  } ToWorkspace8_PWORK;                /* '<S10>/To Workspace8' */

  struct {
    void *LoggedData;
  } eta_s_hatscope_PWORK;              /* '<S10>/eta_s_hat scope' */

  struct {
    void *LoggedData;
  } ToWorkspace9_PWORK;                /* '<S10>/To Workspace9' */

  struct {
    void *LoggedData;
  } nu_s_hatscope_PWORK;               /* '<S10>/nu_s_hat scope' */

  struct {
    void *LoggedData;
  } ToWorkspace10_PWORK;               /* '<S10>/To Workspace10' */

  struct {
    void *LoggedData;
  } eta_i_hatscope_PWORK;              /* '<S10>/eta_i_hat scope' */

  struct {
    void *LoggedData;
  } ToWorkspace11_PWORK;               /* '<S10>/To Workspace11' */

  struct {
    void *LoggedData;
  } nu_i_hatscope_PWORK;               /* '<S10>/nu_i_hat scope' */

  struct {
    void *LoggedData;
  } debugjoystickcontrolIN_PWORK;      /* '<S4>/debug joystick control IN' */

  struct {
    void *LoggedData;
  } debugjoystickcontrolOUT_PWORK;     /* '<S4>/debug joystick control OUT' */

  struct {
    void *LoggedData;
  } debug_PWORK;                       /* '<S9>/debug' */

  struct {
    void *LoggedData;
  } debug1_PWORK;                      /* '<S9>/debug1' */

  struct {
    void *LoggedData;
  } Xscope_PWORK_a;                    /* '<S12>/X scope' */

  struct {
    void *LoggedData;
  } lengthT_PWORK;                     /* '<S12>/length+T' */

  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  uint32_T RandSeed;                   /* '<S51>/White Noise' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S2>/Integrator1' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S2>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_j;               /* '<S3>/Integrator1' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_o;                /* '<S12>/Integrator' */

  int_T DPcontroller_MODE;             /* '<Root>/DP controller' */
  int8_T If_ActiveSubsystem;           /* '<S44>/If' */
  int8_T If_ActiveSubsystem_p;         /* '<S33>/If' */
  int8_T If_ActiveSubsystem_j;         /* '<S32>/If' */
  int8_T If_ActiveSubsystem_jx;        /* '<S35>/If' */
  int8_T If_ActiveSubsystem_m;         /* '<S34>/If' */
  uint8_T SignalProbe_DWORK1[7];       /* '<Root>/SignalProbe' */
} D_Work_modell;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T TransferFcn_CSTATE;           /* '<S5>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S5>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S5>/Transfer Fcn2' */
  real_T Integrator1_CSTATE_e[3];      /* '<S3>/Integrator1' */
  real_T Integrator2_CSTATE[3];        /* '<S3>/Integrator2' */
  real_T Integrator_CSTATE_e[3];       /* '<S12>/Integrator' */
  real_T Integrator_CSTATE_m[3];       /* '<S13>/Integrator' */
  real_T wavehat_CSTATE[6];            /* '<S8>/wave hat' */
  real_T eta_hat_CSTATE[3];            /* '<S8>/eta_hat' */
  real_T nu_hat_CSTATE[3];             /* '<S8>/nu_hat' */
  real_T wavehat_CSTATE_g[6];          /* '<S7>/wave hat' */
  real_T eta_hat_CSTATE_b[3];          /* '<S7>/eta_hat' */
  real_T nu_hat_CSTATE_g[3];           /* '<S7>/nu_hat' */
  real_T Integrator1_CSTATE_p[3];      /* '<S13>/Integrator1' */
  real_T bias_hat_integrator_CSTATE[3];/* '<S7>/bias_hat_integrator' */
  real_T bias_hat_integrator_CSTATE_l[3];/* '<S8>/bias_hat_integrator' */
  real_T Integrator_CSTATE_p[3];       /* '<S15>/Integrator' */
} ContinuousStates_modell;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T TransferFcn_CSTATE;           /* '<S5>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S5>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S5>/Transfer Fcn2' */
  real_T Integrator1_CSTATE_e[3];      /* '<S3>/Integrator1' */
  real_T Integrator2_CSTATE[3];        /* '<S3>/Integrator2' */
  real_T Integrator_CSTATE_e[3];       /* '<S12>/Integrator' */
  real_T Integrator_CSTATE_m[3];       /* '<S13>/Integrator' */
  real_T wavehat_CSTATE[6];            /* '<S8>/wave hat' */
  real_T eta_hat_CSTATE[3];            /* '<S8>/eta_hat' */
  real_T nu_hat_CSTATE[3];             /* '<S8>/nu_hat' */
  real_T wavehat_CSTATE_g[6];          /* '<S7>/wave hat' */
  real_T eta_hat_CSTATE_b[3];          /* '<S7>/eta_hat' */
  real_T nu_hat_CSTATE_g[3];           /* '<S7>/nu_hat' */
  real_T Integrator1_CSTATE_p[3];      /* '<S13>/Integrator1' */
  real_T bias_hat_integrator_CSTATE[3];/* '<S7>/bias_hat_integrator' */
  real_T bias_hat_integrator_CSTATE_l[3];/* '<S8>/bias_hat_integrator' */
  real_T Integrator_CSTATE_p[3];       /* '<S15>/Integrator' */
} StateDerivatives_modell;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE[3];     /* '<S2>/Integrator1' */
  boolean_T Integrator_CSTATE[3];      /* '<S2>/Integrator' */
  boolean_T TransferFcn_CSTATE;        /* '<S5>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S5>/Transfer Fcn1' */
  boolean_T TransferFcn2_CSTATE;       /* '<S5>/Transfer Fcn2' */
  boolean_T Integrator1_CSTATE_e[3];   /* '<S3>/Integrator1' */
  boolean_T Integrator2_CSTATE[3];     /* '<S3>/Integrator2' */
  boolean_T Integrator_CSTATE_e[3];    /* '<S12>/Integrator' */
  boolean_T Integrator_CSTATE_m[3];    /* '<S13>/Integrator' */
  boolean_T wavehat_CSTATE[6];         /* '<S8>/wave hat' */
  boolean_T eta_hat_CSTATE[3];         /* '<S8>/eta_hat' */
  boolean_T nu_hat_CSTATE[3];          /* '<S8>/nu_hat' */
  boolean_T wavehat_CSTATE_g[6];       /* '<S7>/wave hat' */
  boolean_T eta_hat_CSTATE_b[3];       /* '<S7>/eta_hat' */
  boolean_T nu_hat_CSTATE_g[3];        /* '<S7>/nu_hat' */
  boolean_T Integrator1_CSTATE_p[3];   /* '<S13>/Integrator1' */
  boolean_T bias_hat_integrator_CSTATE[3];/* '<S7>/bias_hat_integrator' */
  boolean_T bias_hat_integrator_CSTATE_l[3];/* '<S8>/bias_hat_integrator' */
  boolean_T Integrator_CSTATE_p[3];    /* '<S15>/Integrator' */
} StateDisabled_modell;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator1_Reset_ZCE;    /* '<S2>/Integrator1' */
  ZCSigState Integrator_Reset_ZCE;     /* '<S2>/Integrator' */
} PrevZCSigStates_modell;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            modell_B
#define BlockIO                        BlockIO_modell
#define rtX                            modell_X
#define ContinuousStates               ContinuousStates_modell
#define rtP                            modell_P
#define Parameters                     Parameters_modell
#define rtDWork                        modell_DWork
#define D_Work                         D_Work_modell
#define rtPrevZCSigState               modell_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_modell

/* Parameters (auto storage) */
struct Parameters_modell_ {
  real_T reset_eta_hil_Value;          /* Expression: 0.000000000000000
                                        * '<S2>/reset_eta_hil'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * '<Root>/Constant'
                                        */
  real_T initial_nu_hil_Value[3];      /* Expression: [0; 0; 0]
                                        * '<S2>/initial_nu_hil'
                                        */
  real_T nu_surge_hil_Gain;            /* Expression: 1
                                        * '<S2>/nu_surge_hil'
                                        */
  real_T nu_sway_hil_Gain;             /* Expression: 1
                                        * '<S2>/nu_sway_hil'
                                        */
  real_T nu_yaw_hil_Gain;              /* Expression: 1
                                        * '<S2>/nu_yaw_hil'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: A
                                        * '<S5>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: C
                                        * '<S5>/Transfer Fcn'
                                        */
  real_T TransferFcn1_A;               /* Computed Parameter: A
                                        * '<S5>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: C
                                        * '<S5>/Transfer Fcn1'
                                        */
  real_T TransferFcn2_A;               /* Computed Parameter: A
                                        * '<S5>/Transfer Fcn2'
                                        */
  real_T TransferFcn2_C;               /* Computed Parameter: C
                                        * '<S5>/Transfer Fcn2'
                                        */
  real_T initialposition_Value[3];     /* Expression: pos_0_i
                                        * '<S3>/initial position'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * '<S3>/Integrator2'
                                        */
  real_T T_zero_Value[3];              /* Expression: [0 0 0]'
                                        * '<S44>/T_zero'
                                        */
  real_T Towlinelength_Value;          /* Expression: 0
                                        * '<S44>/Towline length'
                                        */
  real_T pos_diff_Value[3];            /* Expression: pos_diff
                                        * '<S12>/pos_diff'
                                        */
  real_T K_tow_Value[9];               /* Expression: [1 0 0; 0 1 0; 0 0 0]
                                        * '<S44>/K_tow'
                                        */
  real_T T_cr_Value;                   /* Expression: 14000
                                        * '<S44>/T_cr'
                                        */
  real_T IC_Value[3];                  /* Expression: [0 0 0]'
                                        * '<S12>/IC'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * '<S13>/Integrator'
                                        */
  real_T zero_Value;                   /* Expression: 0
                                        * '<S13>/zero'
                                        */
  real_T wavehat_IC;                   /* Expression: 0
                                        * '<S8>/wave hat'
                                        */
  real_T C_w_Gain[18];                 /* Expression: C_w
                                        * '<S8>/C_w'
                                        */
  real_T eta_hat_IC;                   /* Expression: 0
                                        * '<S8>/eta_hat'
                                        */
  real_T nu_hat_IC;                    /* Expression: 0
                                        * '<S8>/nu_hat'
                                        */
  real_T wavehat_IC_l;                 /* Expression: 0
                                        * '<S7>/wave hat'
                                        */
  real_T C_w_Gain_d[18];               /* Expression: C_w
                                        * '<S7>/C_w'
                                        */
  real_T eta_hat_IC_g;                 /* Expression: 0
                                        * '<S7>/eta_hat'
                                        */
  real_T nu_hat_IC_c;                  /* Expression: 0
                                        * '<S7>/nu_hat'
                                        */
  real_T MODE_Value;                   /* Expression: 2.000000000000000
                                        * '<Root>/MODE'
                                        */
  real_T Constant_Value_j;             /* Expression: const
                                        * '<S14>/Constant'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * '<S33>/Constant2'
                                        */
  real_T PS3_L_JS_Y_Value;             /* Expression: -3229.000000000000000
                                        * '<S9>/PS3_L_JS_Y'
                                        */
  real_T limit_L_JS_Y_Value;           /* Expression: 10000
                                        * '<S9>/limit_L_JS_Y'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/32676
                                        * '<S9>/Gain1'
                                        */
  real_T Constant2_Value_j;            /* Expression: 0
                                        * '<S32>/Constant2'
                                        */
  real_T PS3_L_JS_X_Value;             /* Expression: 3229.000000000000000
                                        * '<S9>/PS3_L_JS_X'
                                        */
  real_T limit_L_JS_X_Value;           /* Expression: 10000
                                        * '<S9>/limit_L_JS_X'
                                        */
  real_T Gain_Gain;                    /* Expression: 1/32676
                                        * '<S9>/Gain'
                                        */
  real_T Constant2_Value_f;            /* Expression: 0
                                        * '<S35>/Constant2'
                                        */
  real_T PS3_R_JS_Y_Value;             /* Expression: -3229.000000000000000
                                        * '<S9>/PS3_R_JS_Y'
                                        */
  real_T limit_R_JS_Y_Value;           /* Expression: 10000
                                        * '<S9>/limit_R_JS_Y'
                                        */
  real_T Gain3_Gain;                   /* Expression: 1/32676
                                        * '<S9>/Gain3'
                                        */
  real_T Constant2_Value_o;            /* Expression: 0
                                        * '<S34>/Constant2'
                                        */
  real_T PS3_R_JS_X_Value;             /* Expression: 3229.000000000000000
                                        * '<S9>/PS3_R_JS_X'
                                        */
  real_T limit_R_JS_X_Value;           /* Expression: 10000
                                        * '<S9>/limit_R_JS_X'
                                        */
  real_T Gain2_Gain;                   /* Expression: 1/32676
                                        * '<S9>/Gain2'
                                        */
  real_T PS3_L2_Value;                 /* Expression: -1.000000000000000
                                        * '<S9>/PS3_L2'
                                        */
  real_T Constant_Value_o;             /* Expression: -179
                                        * '<S9>/Constant'
                                        */
  real_T g1_Gain;                      /* Expression: 1/179
                                        * '<S9>/g1'
                                        */
  real_T PS3_R2_Value;                 /* Expression: 179.000000000000000
                                        * '<S9>/PS3_R2'
                                        */
  real_T Constant1_Value;              /* Expression: -179
                                        * '<S9>/Constant1'
                                        */
  real_T g2_Gain;                      /* Expression: -1/179
                                        * '<S9>/g2'
                                        */
  real_T BT_saturation_Value;          /* Expression: 0.000000000000000
                                        * '<S5>/BT_saturation'
                                        */
  real_T VSP_speeds_Value;             /* Expression: 0.000000000000000
                                        * '<S5>/VSP_speeds'
                                        */
  real_T Ke1_Value[25];                /* Expression: inv(Ke)
                                        * '<S4>/Ke^-1'
                                        */
  real_T Te_Value[15];                 /* Expression: pinv(Te)
                                        * '<S4>/Te^+'
                                        */
  real_T joystick_gain_surge_Gain;     /* Expression: 1
                                        * '<S4>/joystick_gain_surge'
                                        */
  real_T joystick_gain_sway_Gain;      /* Expression: 1
                                        * '<S4>/joystick_gain_sway'
                                        */
  real_T joystick_gain_yaw_Gain;       /* Expression: 1
                                        * '<S4>/joystick_gain_yaw'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1.0
                                        * '<S4>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1.0
                                        * '<S4>/Saturation'
                                        */
  real_T VSP_speeds_Value_n;           /* Expression: 0.4
                                        * '<S4>/VSP_speeds'
                                        */
  real_T BT_power_limit_Value;         /* Expression: 0.5
                                        * '<S4>/BT_power_limit'
                                        */
  real_T Ke1_Value_c[25];              /* Expression: inv(Ke)
                                        * '<S11>/Ke^-1'
                                        */
  real_T Te_Value_h[15];               /* Expression: pinv(Te)
                                        * '<S11>/Te^+'
                                        */
  real_T VSP_speeds_Value_k;           /* Expression: 0.4
                                        * '<S11>/VSP_speeds'
                                        */
  real_T BT_power_limit_Value_f;       /* Expression: 0.5
                                        * '<S11>/BT_power_limit'
                                        */
  real_T BT_power_Gain;                /* Expression: 1
                                        * '<S2>/BT_power'
                                        */
  real_T Constant_Value_e[15];         /* Expression: Te
                                        * '<S2>/Constant'
                                        */
  real_T Constant1_Value_o[25];        /* Expression: diag([1 1 1 1 1])
                                        * '<S2>/Constant1'
                                        */
  real_T D_Gain[9];                    /* Expression: D
                                        * '<S2>/D'
                                        */
  real_T u1_hil_Gain;                  /* Expression: 1
                                        * '<S2>/u1_hil'
                                        */
  real_T u2_hil_Gain;                  /* Expression: 1
                                        * '<S2>/u2_hil'
                                        */
  real_T u3_hil_Gain;                  /* Expression: 1
                                        * '<S2>/u3_hil'
                                        */
  real_T u4_hil_Gain;                  /* Expression: 1
                                        * '<S2>/u4_hil'
                                        */
  real_T sampletime_WtEt;              /* Computed Parameter: WtEt
                                        * '<S21>/sample time'
                                        */
  real_T DelayInput2_X0;               /* Expression: 0
                                        * '<S21>/Delay Input2'
                                        */
  real_T neg_Gain;                     /* Expression: -1
                                        * '<S2>/neg'
                                        */
  real_T u5_hil_Gain;                  /* Expression: 1
                                        * '<S2>/u5_hil'
                                        */
  real_T tau_surge_hil_Gain;           /* Expression: 1
                                        * '<S2>/tau_surge_hil'
                                        */
  real_T tau_sway_hil_Gain;            /* Expression: 1
                                        * '<S2>/tau_sway_hil'
                                        */
  real_T tau_yaw_hil_Gain;             /* Expression: 1
                                        * '<S2>/tau_yaw_hil'
                                        */
  real_T VIS_HIL_E_Gain;               /* Expression: 1
                                        * '<S2>/VIS_HIL_E'
                                        */
  real_T VIS_HIL_N_Gain;               /* Expression: 1
                                        * '<S2>/VIS_HIL_N'
                                        */
  real_T VIS_HIL_PIS_Gain;             /* Expression: 1
                                        * '<S2>/VIS_HIL_PIS'
                                        */
  real_T VSP_angle_deg_port_Gain;      /* Expression: 180/pi
                                        * '<S2>/VSP_angle_deg_port'
                                        */
  real_T VSP_angle_deg_stbd_Gain;      /* Expression: 180/pi
                                        * '<S2>/VSP_angle_deg_stbd'
                                        */
  real_T invM_Gain[9];                 /* Expression: inv(M)
                                        * '<S2>/inv(M)'
                                        */
  real_T D_Gain_d[9];                  /* Expression: D_i
                                        * '<S3>/D'
                                        */
  real_T Saturation_UpperSat_n;        /* Expression: 2
                                        * '<S25>/Saturation'
                                        */
  real_T Saturation_LowerSat_j;        /* Expression: -2
                                        * '<S25>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 1.5
                                        * '<S25>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -1.5
                                        * '<S25>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.5
                                        * '<S25>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S25>/Saturation2'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * '<S13>/Integrator1'
                                        */
  real_T invM_Gain_d[9];               /* Expression: inv(M_i)
                                        * '<S3>/inv(M)'
                                        */
  real_T eta_d_E_Value;                /* Expression: -1.000000000000000
                                        * '<S5>/eta_d_E'
                                        */
  real_T eta_d_N_Value;                /* Expression: 2.000000000000000
                                        * '<S5>/eta_d_N'
                                        */
  real_T eta_d_Psi_Value;              /* Expression: 0.000000000000000
                                        * '<S5>/eta_d_Psi'
                                        */
  real_T A_w_Gain[36];                 /* Expression: A_w
                                        * '<S7>/A_w'
                                        */
  real_T D_Gain_h[9];                  /* Expression: D_i
                                        * '<S7>/D'
                                        */
  real_T K_1_Gain[18];                 /* Expression: K_1
                                        * '<S7>/K_1'
                                        */
  real_T K_2_Gain[9];                  /* Expression: K_2
                                        * '<S7>/K_2'
                                        */
  real_T K_3_Gain[9];                  /* Expression: K_3
                                        * '<S7>/K_3'
                                        */
  real_T K_4_Gain[9];                  /* Expression: K_4
                                        * '<S7>/K_4'
                                        */
  real_T bias_hat_integrator_IC;       /* Expression: 0
                                        * '<S7>/bias_hat_integrator'
                                        */
  real_T M_inv_Gain[9];                /* Expression: inv(M_i)
                                        * '<S7>/M_inv'
                                        */
  real_T T_inv_Gain[9];                /* Expression: T_s_inv
                                        * '<S7>/T_inv'
                                        */
  real_T A_w_Gain_p[36];               /* Expression: A_w
                                        * '<S8>/A_w'
                                        */
  real_T D_Gain_e[9];                  /* Expression: D
                                        * '<S8>/D'
                                        */
  real_T K_1_Gain_k[18];               /* Expression: K_1
                                        * '<S8>/K_1'
                                        */
  real_T K_2_Gain_m[9];                /* Expression: K_2
                                        * '<S8>/K_2'
                                        */
  real_T K_3_Gain_f[9];                /* Expression: K_3
                                        * '<S8>/K_3'
                                        */
  real_T K_4_Gain_m[9];                /* Expression: K_4
                                        * '<S8>/K_4'
                                        */
  real_T bias_hat_integrator_IC_f;     /* Expression: 0
                                        * '<S8>/bias_hat_integrator'
                                        */
  real_T M_inv_Gain_h[9];              /* Expression: inv(M)
                                        * '<S8>/M_inv'
                                        */
  real_T T_inv_Gain_d[9];              /* Expression: T_s_inv
                                        * '<S8>/T_inv'
                                        */
  real_T WhiteNoise_Mean;              /* Expression: 0
                                        * '<S51>/White Noise'
                                        */
  real_T WhiteNoise_StdDev;            /* Computed Parameter: StdDev
                                        * '<S51>/White Noise'
                                        */
  real_T WhiteNoise_Seed;              /* Expression: seed
                                        * '<S51>/White Noise'
                                        */
  real_T Output_Gain[3];               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * '<S51>/Output'
                                        */
  real_T E_b_i_Gain[9];                /* Expression: E_b_i
                                        * '<S13>/E_b_i'
                                        */
  real_T E_b_s_Gain[9];                /* Expression: E_b_s
                                        * '<S13>/E_b_s'
                                        */
  real_T T_s_inv_Gain[9];              /* Expression: inv(T_s)
                                        * '<S13>/T_s_inv'
                                        */
  real_T T_i_inv_Gain[9];              /* Expression: inv(T_i)
                                        * '<S13>/T_i_inv'
                                        */
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T Saturation_UpperSat_c;        /* Expression: 1.0
                                        * '<S11>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: -1.0
                                        * '<S11>/Saturation'
                                        */
  real_T U1_Gain;                      /* Expression: 1
                                        * '<S6>/U1'
                                        */
  real_T U2_Gain;                      /* Expression: 1
                                        * '<S6>/U2'
                                        */
  real_T U3_Gain;                      /* Expression: 1
                                        * '<S6>/U3'
                                        */
  real_T U4_Gain;                      /* Expression: 1
                                        * '<S6>/U4'
                                        */
  real_T U5_Gain;                      /* Expression: 1
                                        * '<S6>/U5'
                                        */
  real_T Integrator_IC_l;              /* Expression: 0
                                        * '<S15>/Integrator'
                                        */
  real_T Kd_Gain[9];                   /* Expression: Kd
                                        * '<S15>/Kd'
                                        */
  real_T Kd_scale_Value;               /* Expression: 0.909090909090909
                                        * '<S15>/Kd_scale'
                                        */
  real_T Ki_Gain[9];                   /* Expression: Ki
                                        * '<S15>/Ki'
                                        */
  real_T Ki_scale_Value;               /* Expression: 0.000000000000000
                                        * '<S15>/Ki_scale'
                                        */
  real_T Saturation_UpperSat_i;        /* Expression: 1e10
                                        * '<S18>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: -1e10
                                        * '<S18>/Saturation'
                                        */
  real_T Gain_Gain_i;                  /* Expression: pi
                                        * '<S18>/Gain'
                                        */
  real_T Constant_Value_jb;            /* Expression: 2*pi
                                        * '<S18>/Constant'
                                        */
  real_T Reg_e_N_hil_Gain;             /* Expression: 1
                                        * '<S15>/Reg_e_N_hil'
                                        */
  real_T Reg_e_E_hil_Gain;             /* Expression: 1
                                        * '<S15>/Reg_e_E_hil'
                                        */
  real_T Reg_e_Psi_hil_Gain;           /* Expression: 1
                                        * '<S15>/Reg_e_Psi_hil'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: 1e10
                                        * '<S17>/Saturation'
                                        */
  real_T Saturation_LowerSat_n;        /* Expression: -1e10
                                        * '<S17>/Saturation'
                                        */
  real_T Gain_Gain_k;                  /* Expression: pi
                                        * '<S17>/Gain'
                                        */
  real_T Constant_Value_f;             /* Expression: 2*pi
                                        * '<S17>/Constant'
                                        */
  real_T Kp_Gain[9];                   /* Expression: Kp
                                        * '<S15>/Kp'
                                        */
  real_T Kp_scale_Value;               /* Expression: 0.519480519480519
                                        * '<S15>/Kp_scale'
                                        */
  uint8_T Constant_Value_ow;           /* Expression: uint8(1)
                                        * '<S52>/Constant'
                                        */
  uint8_T SwitchControl_Threshold;     /* Expression: uint8(1)
                                        * '<S52>/SwitchControl'
                                        */
  uint8_T Constant_Value_b;            /* Expression: uint8(1)
                                        * '<S53>/Constant'
                                        */
  uint8_T SwitchControl_Threshold_a;   /* Expression: uint8(0)
                                        * '<S53>/SwitchControl'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_modell {
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
    real_T *defaultParam;
    ZCSigState *prevZCSigState;
    real_T *contStates;
    real_T *derivs;
    real_T *zcSignalValues;
    void *inputs;
    void *outputs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[57];
    real_T odeF[4][57];
    ODE4_IntgData intgData;
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

  /*
   * Work:
   * The following substructure contains information regarding
   * the work vectors in the model.
   */
  struct {
    void *dwork;
  } Work;
};

/* Block parameters (auto storage) */
extern Parameters_modell modell_P;

/* Block signals (auto storage) */
extern BlockIO_modell modell_B;

/* Continuous states (auto storage) */
extern ContinuousStates_modell modell_X;

/* Block states (auto storage) */
extern D_Work_modell modell_DWork;

/* Model entry point functions */
extern void modell_initialize(boolean_T firstTime);
extern void modell_output(int_T tid);
extern void modell_update(int_T tid);
extern void modell_terminate(void);

/* Real-time Model object */
extern RT_MODEL_modell *modell_M;

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
 * '<Root>' : modell
 * '<S1>'   : modell/DP controller
 * '<S2>'   : modell/HIL model
 * '<S3>'   : modell/Iceberg
 * '<S4>'   : modell/Joystick Control
 * '<S5>'   : modell/LabView Out
 * '<S6>'   : modell/Manual Thruster Control
 * '<S7>'   : modell/Observer (iceberg)
 * '<S8>'   : modell/Observer (ship)
 * '<S9>'   : modell/PS3 Sixaxis
 * '<S10>'  : modell/Plotter
 * '<S11>'  : modell/Thruster Control
 * '<S12>'  : modell/Towline
 * '<S13>'  : modell/bias
 * '<S14>'  : modell/ctc
 * '<S15>'  : modell/DP controller/DP controller
 * '<S16>'  : modell/DP controller/DP controller/Transposed rotation  matrix in yaw1
 * '<S17>'  : modell/DP controller/DP controller/[-inf inf] to [-pi pi]
 * '<S18>'  : modell/DP controller/DP controller/[-inf inf] to [-pi pi]1
 * '<S19>'  : modell/HIL model/Cartesian to Polar Port
 * '<S20>'  : modell/HIL model/Cartesian to Polar Stbd
 * '<S21>'  : modell/HIL model/Rate Limiter Dynamic
 * '<S22>'  : modell/HIL model/Rotation matrix in yaw 1
 * '<S23>'  : modell/HIL model/Rate Limiter Dynamic/Saturation Dynamic
 * '<S24>'  : modell/Iceberg/Rotation matrix in yaw 1
 * '<S25>'  : modell/Iceberg/saturation
 * '<S26>'  : modell/Observer (iceberg)/R_T1
 * '<S27>'  : modell/Observer (iceberg)/R_T2
 * '<S28>'  : modell/Observer (iceberg)/Rotation matrix in yaw
 * '<S29>'  : modell/Observer (ship)/R_T1
 * '<S30>'  : modell/Observer (ship)/R_T2
 * '<S31>'  : modell/Observer (ship)/Rotation matrix in yaw
 * '<S32>'  : modell/PS3 Sixaxis/threshold block
 * '<S33>'  : modell/PS3 Sixaxis/threshold block1
 * '<S34>'  : modell/PS3 Sixaxis/threshold block2
 * '<S35>'  : modell/PS3 Sixaxis/threshold block3
 * '<S36>'  : modell/PS3 Sixaxis/threshold block/else
 * '<S37>'  : modell/PS3 Sixaxis/threshold block/if
 * '<S38>'  : modell/PS3 Sixaxis/threshold block1/else
 * '<S39>'  : modell/PS3 Sixaxis/threshold block1/if
 * '<S40>'  : modell/PS3 Sixaxis/threshold block2/else
 * '<S41>'  : modell/PS3 Sixaxis/threshold block2/if
 * '<S42>'  : modell/PS3 Sixaxis/threshold block3/else
 * '<S43>'  : modell/PS3 Sixaxis/threshold block3/if
 * '<S44>'  : modell/Towline/Towline dynamics
 * '<S45>'  : modell/Towline/cartesian length
 * '<S46>'  : modell/Towline/Towline dynamics/cartesian length
 * '<S47>'  : modell/Towline/Towline dynamics/cartesian length1
 * '<S48>'  : modell/Towline/Towline dynamics/rupture
 * '<S49>'  : modell/Towline/Towline dynamics/slack
 * '<S50>'  : modell/Towline/Towline dynamics/towing
 * '<S51>'  : modell/bias/Band-Limited White Noise
 * '<S52>'  : modell/bias/Manual Switch
 * '<S53>'  : modell/bias/Manual Switch1
 * '<S54>'  : modell/bias/Transposed rotation  matrix in yaw
 * '<S55>'  : modell/bias/Transposed rotation  matrix in yaw1
 */
#endif                                 /* RTW_HEADER_modell_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_modell
#ifdef RVE
#ifdef MULTITASKING

Parameters_modell rtParameter[NUMST+!TID01EQ];

#define modell_P                       (*param_lookup[tid][READSIDE])

Parameters_modell *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_modell rtParameter[2];

#define modell_P                       rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
