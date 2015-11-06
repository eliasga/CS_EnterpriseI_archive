/*
 * LgV2.h
 *
 * Real-Time Workshop code generation for Simulink model "LgV2.mdl".
 *
 * Model Version              : 1.198
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Wed Nov 27 14:51:19 2013
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_LgV2_h_
#define RTW_HEADER_LgV2_h_
#ifndef LgV2_COMMON_INCLUDES_
# define LgV2_COMMON_INCLUDES_
#include <stdio.h>
#include <stddef.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#include "dspsvd_rt.h"
#include "rt_zcfcn.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_SATURATE.h"
#include "rt_SIGNd_snf.h"
#include "rt_atan2_snf.h"
#include "rt_hypot_snf.h"
#include "rt_look.h"
#include "rt_look2d_normal.h"
#include "rt_matrixlib.h"
#include "rt_rem_snf.h"
#include "rt_round_snf.h"
#include "rt_MAX.h"
#include "rt_MIN.h"
#endif                                 /* LgV2_COMMON_INCLUDES_ */

#include "LgV2_types.h"

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
#define LgV2_rtModel                   RT_MODEL_LgV2

/* Block signals (auto storage) */
typedef struct {
  real_T Accuracyu_1;                  /* '<S26>/Accuracy u_1' */
  real_T Accuracyu_2;                  /* '<S26>/Accuracy u_2' */
  real_T Accuracyu_3;                  /* '<S26>/Accuracy u_3' */
  real_T Accuracyu_4;                  /* '<S26>/Accuracy u_4' */
  real_T Accuracyu_5;                  /* '<S26>/Accuracy u_5' */
  real_T u1;                           /* '<S30>/Scaling_JS_L_Y' */
  real_T PS3u_1;                       /* '<S9>/PS3 u_1' */
  real_T u1_b;                         /* '<S30>/Scaling_JS_L_X' */
  real_T PS3u_2;                       /* '<S9>/PS3 u_2' */
  real_T u1_l;                         /* '<S30>/Scaling_JS_R_Y' */
  real_T PS3u_3;                       /* '<S9>/PS3 u_3' */
  real_T u1_c;                         /* '<S30>/Scaling_JS_R_X' */
  real_T PS3u_4;                       /* '<S9>/PS3 u_4' */
  real_T BowThrusterdirection;         /* '<S9>/Add' */
  real_T PS3u_5;                       /* '<S9>/PS3 u_5' */
  real_T GainK_e1_joystick;            /* '<S23>/Gain K_e1_joystick' */
  real_T GainK_e2_joystick;            /* '<S23>/Gain K_e2_joystick' */
  real_T GainK_e3_joystick;            /* '<S23>/Gain K_e3_joystick' */
  real_T GainK_e4_joystick;            /* '<S23>/Gain K_e4_joystick' */
  real_T GainK_e5_joystick;            /* '<S23>/Gain K_e5_joystick' */
  real_T ThrusterGainmatrix[25];       /* '<S23>/Thruster Gain matrix' */
  real_T K_e1[25];                     /* '<S8>/K_e^-1' */
  real_T l_x1;                         /* '<S24>/-l_x1' */
  real_T l_y2;                         /* '<S24>/-l_y2' */
  real_T l_x2;                         /* '<S24>/-l_x2' */
  real_T x5[15];                       /* '<S24>/3x5' */
  real_T T_e[15];                      /* '<S8>/T_e^+' */
  real_T T_eK_e1[15];                  /* '<S8>/T_e^+ K_e^-1' */
  real_T Sum1;                         /* '<S8>/Sum1' */
  real_T Joysticktau_surge;            /* '<S8>/Joystick tau_surge' */
  real_T Saturation1;                  /* '<S8>/Saturation1' */
  real_T Sum2;                         /* '<S8>/Sum2' */
  real_T Joysticktau_sway;             /* '<S8>/Joystick tau_sway' */
  real_T Saturation2;                  /* '<S8>/Saturation2' */
  real_T Sum;                          /* '<S8>/Sum' */
  real_T Joysticktau_yaw;              /* '<S8>/Joystick tau_yaw' */
  real_T Saturation3;                  /* '<S8>/Saturation3' */
  real_T TmpHiddenBufferAtProduct1Inport[3];/* 'synthesized block' */
  real_T Product1[5];                  /* '<S8>/Product1' */
  real_T Saturation[5];                /* '<S8>/Saturation' */
  real_T Joysticku_1;                  /* '<S8>/Joystick u_1' */
  real_T Joysticku_2;                  /* '<S8>/Joystick u_2' */
  real_T Joysticku_3;                  /* '<S8>/Joystick u_3' */
  real_T Joysticku_4;                  /* '<S8>/Joystick u_4' */
  real_T Joysticku_5;                  /* '<S8>/Joystick u_5' */
  real_T Gain1;                        /* '<S29>/Gain1' */
  real_T TransferFcn;                  /* '<S25>/Transfer Fcn' */
  real_T TransferFcn1;                 /* '<S25>/Transfer Fcn1' */
  real_T TransferFcn2;                 /* '<S25>/Transfer Fcn2' */
  real_T MultiportSwitch[3];           /* '<S25>/Multiport Switch' */
  real_T eta_dDPN;                     /* '<S25>/eta_d DP N' */
  real_T eta_dDPE;                     /* '<S25>/eta_d DP E' */
  real_T eta_dDPPsi;                   /* '<S25>/eta_d DP Psi' */
  real_T QTMIn[9];                     /* '<S31>/QTM In' */
  real_T QTMIn3;                       /* '<S31>/QTM In3' */
  real_T mm2mx;                        /* '<S31>/mm2m x' */
  real_T QTMIn4;                       /* '<S31>/QTM In4' */
  real_T mm2my;                        /* '<S31>/mm2m y' */
  real_T QTMIn6;                       /* '<S31>/QTM In6' */
  real_T d2ryaw;                       /* '<S31>/d2r yaw' */
  real_T EtaSwitch[3];                 /* '<S4>/Eta Switch' */
  real_T eta_surge;                    /* '<S4>/eta_surge' */
  real_T eta_sway;                     /* '<S4>/eta_sway' */
  real_T eta_yaw;                      /* '<S4>/eta_yaw' */
  real_T QTMIn8;                       /* '<S31>/QTM In8' */
  real_T d2rroll;                      /* '<S31>/d2r roll' */
  real_T QTMIn7;                       /* '<S31>/QTM In7' */
  real_T d2rpitch;                     /* '<S31>/d2r pitch' */
  real_T sintheta[3];                  /* '<S32>/sin(theta)' */
  real_T costheta[3];                  /* '<S32>/cos(theta)' */
  real_T R11;                          /* '<S32>/R11' */
  real_T R21;                          /* '<S32>/R21 ' */
  real_T R31;                          /* '<S32>/R31 ' */
  real_T R12;                          /* '<S32>/R12' */
  real_T R22;                          /* '<S32>/R22' */
  real_T R32;                          /* '<S32>/R32' */
  real_T R13;                          /* '<S32>/R13' */
  real_T R23;                          /* '<S32>/R23' */
  real_T R33;                          /* '<S32>/R33' */
  real_T Reshape9x13x3[9];             /* '<S32>/Reshape 9x1->3x3' */
  real_T MatrixConcatenate2[36];       /* '<S31>/Matrix Concatenate2' */
  real_T QTMIn5;                       /* '<S31>/QTM In5' */
  real_T mm2mz;                        /* '<S31>/mm2m z' */
  real_T Derivative[6];                /* '<S31>/Derivative' */
  real_T Product[6];                   /* '<S31>/Product' */
  real_T NuSwitch[3];                  /* '<S4>/Nu Switch' */
  real_T nu_surge;                     /* '<S4>/nu_surge' */
  real_T nu_sway;                      /* '<S4>/nu_sway' */
  real_T nu_yaw;                       /* '<S4>/nu_yaw' */
  real_T ControlSwitch[7];             /* '<S1>/Control Switch' */
  real_T Saturation_e[7];              /* '<S1>/Saturation' */
  real_T QTMIn2Error;                  /* '<S31>/QTM In2 Error' */
  real_T TmpHiddenBufferAtToFileInport1[14];/* 'synthesized block' */
  real_T eta_dPsideg;                  /* '<S25>/eta_d Psi deg' */
  real_T psi_d;                        /* '<S2>/psi_d' */
  real_T x_d;                          /* '<S2>/x_d' */
  real_T y_d;                          /* '<S2>/y_d' */
  real_T SITzAI0;                      /* '<S3>/SIT zAI0' */
  real_T BatteryBowThruster;           /* '<S3>/Battery Bow Thruster' */
  real_T SITzAI1;                      /* '<S3>/SIT zAI1' */
  real_T BatteryServo;                 /* '<S3>/Battery Servo' */
  real_T SITzAI2;                      /* '<S3>/SIT zAI2' */
  real_T BatteryMain;                  /* '<S3>/Battery Main' */
  real_T QTMIn1FPS;                    /* '<S31>/QTM In1 FPS' */
  real_T QTMIn9Residual;               /* '<S31>/QTM In9 Residual' */
  real_T u_1plant;                     /* '<S5>/u_1 plant' */
  real_T u_2plant;                     /* '<S5>/u_2 plant' */
  real_T u_3plant;                     /* '<S5>/u_3 plant' */
  real_T u_4plant;                     /* '<S5>/u_4 plant' */
  real_T u_5plant;                     /* '<S5>/u_5 plant' */
  real_T BTpowerlimitplant;            /* '<S5>/BT power limit plant' */
  real_T VSPspeedplant;                /* '<S5>/VSP speed plant' */
  real_T N_r;                          /* '<S48>/-N_r' */
  real_T N_v;                          /* '<S48>/-N_v' */
  real_T X_u;                          /* '<S48>/-X_u' */
  real_T Y_v;                          /* '<S48>/-Y_v' */
  real_T Y_vr;                         /* '<S48>/-Y_vr' */
  real_T LinearDampningmatrix[9];      /* '<S48>/Linear Dampning matrix' */
  real_T psi_0;                        /* '<S49>/psi_0' */
  real_T x_0;                          /* '<S49>/x_0' */
  real_T y_0;                          /* '<S49>/y_0' */
  real_T r_0;                          /* '<S50>/r_0' */
  real_T u_0;                          /* '<S50>/u_0' */
  real_T v_0;                          /* '<S50>/v_0' */
  real_T Integrator[3];                /* '<S46>/Integrator' */
  real_T Integrator1[3];               /* '<S46>/Integrator1' */
  real_T M_11;                         /* '<S51>/M_11' */
  real_T M_22;                         /* '<S51>/M_22' */
  real_T mx_g;                         /* '<S51>/m x_g' */
  real_T M_32;                         /* '<S51>/M_32' */
  real_T M_23;                         /* '<S51>/M_23' */
  real_T M_33;                         /* '<S51>/M_33' */
  real_T M[9];                         /* '<S51>/M' */
  real_T Inverse[9];                   /* '<S51>/Inverse' */
  real_T Product1_h[3];                /* '<S46>/Product1' */
  real_T l_x1_k;                       /* '<S57>/-l_x1' */
  real_T l_y2_g;                       /* '<S57>/-l_y2' */
  real_T l_x2_h;                       /* '<S57>/-l_x2' */
  real_T x5_m[15];                     /* '<S57>/3x5' */
  real_T GainK_e1_hil;                 /* '<S55>/Gain K_e1_hil' */
  real_T GainK_e2_hil;                 /* '<S55>/Gain K_e2_hil' */
  real_T GainK_e3_hil;                 /* '<S55>/Gain K_e3_hil' */
  real_T GainK_e4_hil;                 /* '<S55>/Gain K_e4_hil' */
  real_T GainK_e5_hil;                 /* '<S55>/Gain K_e5_hil' */
  real_T ThrusterGainmatrix_m[25];     /* '<S55>/Thruster Gain matrix' */
  real_T sampletime;                   /* '<S56>/sample time' */
  real_T Yk1;                          /* '<S56>/Delay Input2' */
  real_T R11_i;                        /* '<S52>/R11' */
  real_T R21_l;                        /* '<S52>/R21' */
  real_T R12_g;                        /* '<S52>/R12' */
  real_T R22_i;                        /* '<S52>/R22' */
  real_T Rpsi[9];                      /* '<S52>/R(psi)' */
  real_T Product3[3];                  /* '<S46>/Product3' */
  real_T eta_surge_hil;                /* '<S34>/eta_surge_hil' */
  real_T eta_sway_hil;                 /* '<S34>/eta_sway_hil' */
  real_T eta_yaw_hil;                  /* '<S34>/eta_yaw_hil' */
  real_T etadot_surge_hil;             /* '<S34>/etadot_surge_hil' */
  real_T etadot_sway_hil;              /* '<S34>/etadot_sway_hil' */
  real_T etadot_yaw_hil;               /* '<S34>/etadot_yaw_hil' */
  real_T nu_surge_hil;                 /* '<S34>/nu_surge_hil' */
  real_T nu_sway_hil;                  /* '<S34>/nu_sway_hil' */
  real_T nu_yaw_hil;                   /* '<S34>/nu_yaw_hil' */
  real_T Gainu_1;                      /* '<S47>/Gain u_1' */
  real_T Gainu_2;                      /* '<S47>/Gain u_2' */
  real_T Gainu_3;                      /* '<S47>/Gain u_3' */
  real_T Gainu_4;                      /* '<S47>/Gain u_4' */
  real_T GainBTpower;                  /* '<S47>/Gain BT power' */
  real_T deltariselimit;               /* '<S56>/delta rise limit' */
  real_T UkYk1;                        /* '<S56>/Difference Inputs1' */
  real_T Neg;                          /* '<S47>/Neg' */
  real_T deltafalllimit;               /* '<S56>/delta fall limit' */
  real_T Switch;                       /* '<S58>/Switch' */
  real_T Switch2;                      /* '<S58>/Switch2' */
  real_T DifferenceInputs2;            /* '<S56>/Difference Inputs2' */
  real_T Gainu_5;                      /* '<S47>/Gain u_5' */
  real_T TmpHiddenBufferAtT_eK_e1u_eInpo[5];/* 'synthesized block' */
  real_T T_eK_e1u_e[3];                /* '<S47>/T_e^+ K_e^-1 u_e' */
  real_T tau_surge_hil;                /* '<S47>/tau_surge_hil' */
  real_T tau_sway_hil;                 /* '<S47>/tau_sway_hil' */
  real_T tau_yaw_hil;                  /* '<S47>/tau_yaw_hil' */
  real_T Sum_h[3];                     /* '<S46>/Sum' */
  real_T Product2[3];                  /* '<S46>/Product2' */
  real_T xr;                           /* '<S53>/x->r' */
  real_T xtheta;                       /* '<S53>/x->theta' */
  real_T xr_l;                         /* '<S54>/x->r' */
  real_T xtheta_j;                     /* '<S54>/x->theta' */
  real_T VSP_angle_deg_port;           /* '<S47>/VSP_angle_deg_port' */
  real_T VSP_angle_deg_stbd;           /* '<S47>/VSP_angle_deg_stbd' */
  real_T BT_D_Gain1;                   /* '<S35>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S35>/BT_D_Gain2' */
  real_T Add;                          /* '<S35>/Add' */
  real_T BT_L_Gain1;                   /* '<S35>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S35>/BT_L_Gain2' */
  real_T Neg_b;                        /* '<S35>/Neg' */
  real_T Sum1_k;                       /* '<S35>/Sum1' */
  real_T Sum2_m;                       /* '<S35>/Sum2' */
  real_T Switch_i;                     /* '<S39>/Switch' */
  real_T Switch2_d;                    /* '<S39>/Switch2' */
  real_T Switch_d;                     /* '<S40>/Switch' */
  real_T Switch2_p;                    /* '<S40>/Switch2' */
  real_T Switch_d3;                    /* '<S41>/Switch' */
  real_T Switch2_o;                    /* '<S41>/Switch2' */
  real_T Sign;                         /* '<S38>/Sign' */
  real_T PortVPS_X;                    /* '<S38>/Product1' */
  real_T PortVPS_X_n;                  /* '<S38>/-x' */
  real_T PortVSP_Y;                    /* '<S38>/Product2' */
  real_T PortVSP_Y_b;                  /* '<S38>/-y' */
  real_T xr_n;                         /* '<S42>/x->r' */
  real_T xtheta_i;                     /* '<S42>/x->theta' */
  real_T StarboardVSP_X;               /* '<S38>/Product3' */
  real_T StarboardVSP_Y;               /* '<S38>/Product4' */
  real_T xr_h;                         /* '<S43>/x->r' */
  real_T xtheta_n;                     /* '<S43>/x->theta' */
  real_T Gain;                         /* '<S44>/Gain' */
  real_T Gain_i;                       /* '<S45>/Gain' */
  real_T Servo1;                       /* '<S38>/Servo1' */
  real_T Servo2;                       /* '<S38>/Servo2' */
  real_T Servo3;                       /* '<S38>/Servo3' */
  real_T Servo4;                       /* '<S38>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S38>/VPS_Speed_Gain' */
  real_T Sum_d;                        /* '<S38>/Sum' */
  real_T VSPSPort;                     /* '<S38>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S38>/VSPS Starboard' */
  real_T l_x1_b;                       /* '<S37>/-l_x1' */
  real_T l_y2_h;                       /* '<S37>/-l_y2' */
  real_T l_x2_p;                       /* '<S37>/-l_x2' */
  real_T x5_n[15];                     /* '<S37>/3x5' */
  real_T GainK_e1_CSE1;                /* '<S36>/Gain K_e1_CSE1' */
  real_T GainK_e2_CSE1;                /* '<S36>/Gain K_e2_CSE1' */
  real_T GainK_e3_CSE1;                /* '<S36>/Gain K_e3_CSE1' */
  real_T GainK_e4_CSE1;                /* '<S36>/Gain K_e4_CSE1' */
  real_T GainK_e5_CSE1;                /* '<S36>/Gain K_e5_CSE1' */
  real_T ThrusterGainmatrix_mz[25];    /* '<S36>/Thruster Gain matrix' */
  real_T TmpHiddenBufferAttau_cse1Inport[5];/* 'synthesized block' */
  real_T tau_cse1[3];                  /* '<S33>/tau_cse1' */
  real_T CSE1tau_surge;                /* '<S33>/CSE1 tau_surge' */
  real_T CSE1tau_sway;                 /* '<S33>/CSE1 tau_sway' */
  real_T CSE1tau_yaw;                  /* '<S33>/CSE1 tau_yaw' */
  real_T eta_w[3];                     /* '<S13>/Integrator1' */
  real_T BT_power_limit;               /* '<S7>/BT_power_limit' */
  real_T eta[3];                       /* '<S13>/Integrator' */
  real_T Saturation_j;                 /* '<S21>/Saturation' */
  real_T Sign_l;                       /* '<S21>/Sign' */
  real_T Gain_d;                       /* '<S21>/Gain' */
  real_T Sum1_e;                       /* '<S21>/Sum1' */
  real_T MathFunction;                 /* '<S21>/Math Function' */
  real_T Sum_n;                        /* '<S21>/Sum' */
  real_T MultiportSwitch_p[3];         /* '<S7>/Multiport Switch' */
  real_T etaN;                         /* '<S11>/eta N' */
  real_T etaE;                         /* '<S11>/eta E' */
  real_T etaPsi;                       /* '<S11>/eta Psi' */
  real_T regulationerror[3];           /* '<S11>/Sum2' */
  real_T Reg_e_N_hil;                  /* '<S11>/Reg_e_N_hil' */
  real_T Reg_e_E_hil;                  /* '<S11>/Reg_e_E_hil' */
  real_T Reg_e_Psi_hil;                /* '<S11>/Reg_e_Psi_hil' */
  real_T TmpHiddenBufferAtToFileInport_g[3];/* 'synthesized block' */
  real_T Integrator_g[3];              /* '<S11>/Integrator' */
  real_T nu[3];                        /* '<S13>/Integrator4' */
  real_T MultiportSwitch1[3];          /* '<S7>/Multiport Switch1' */
  real_T Kd[3];                        /* '<S11>/Kd' */
  real_T Product_d[3];                 /* '<S11>/Product' */
  real_T K_d1;                         /* '<S11>/K_d 1' */
  real_T K_d2;                         /* '<S11>/K_d 2' */
  real_T K_d3;                         /* '<S11>/K_d 3' */
  real_T K_d3deg;                      /* '<S11>/K_d 3 deg' */
  real_T Ki[3];                        /* '<S11>/Ki' */
  real_T Product1_c[3];                /* '<S11>/Product1' */
  real_T K_i1;                         /* '<S11>/K_i 1' */
  real_T K_i2;                         /* '<S11>/K_i 2' */
  real_T K_i3;                         /* '<S11>/K_i 3' */
  real_T K_i3deg;                      /* '<S11>/K_i 3 deg' */
  real_T psi;                          /* '<S11>/yaw angle' */
  real_T Saturation_h;                 /* '<S17>/Saturation' */
  real_T Sign_a;                       /* '<S17>/Sign' */
  real_T Gain_j;                       /* '<S17>/Gain' */
  real_T Sum1_i;                       /* '<S17>/Sum1' */
  real_T MathFunction_i;               /* '<S17>/Math Function' */
  real_T Sum_b;                        /* '<S17>/Sum' */
  real_T Saturation_m;                 /* '<S16>/Saturation' */
  real_T Sign_j;                       /* '<S16>/Sign' */
  real_T Gain_a;                       /* '<S16>/Gain' */
  real_T Sum1_p;                       /* '<S16>/Sum1' */
  real_T MathFunction_d;               /* '<S16>/Math Function' */
  real_T Sum_j;                        /* '<S16>/Sum' */
  real_T Row1;                         /* '<S15>/Row1' */
  real_T Row2;                         /* '<S15>/Row2' */
  real_T Row3;                         /* '<S15>/Row3' */
  real_T TmpHiddenBufferAtKpInport1[3];/* '<S11>/Transposed rotation  matrix in yaw1' */
  real_T Kp[3];                        /* '<S11>/Kp' */
  real_T Product2_m[3];                /* '<S11>/Product2' */
  real_T K_p1;                         /* '<S11>/K_p 1' */
  real_T K_p2;                         /* '<S11>/K_p 2' */
  real_T K_p3;                         /* '<S11>/K_p 3' */
  real_T K_p3deg;                      /* '<S11>/K_p 3 deg' */
  real_T Reg_e_Psi_deg;                /* '<S11>/Reg_e_Psi_deg' */
  real_T Sum3[3];                      /* '<S11>/Sum3' */
  real_T Sum1_j[3];                    /* '<S11>/Sum1' */
  real_T etaPsideg;                    /* '<S11>/eta Psi deg' */
  real_T DPtau_surge;                  /* '<S7>/DP tau_surge' */
  real_T DPtau_sway;                   /* '<S7>/DP tau_sway' */
  real_T DPtau_yaw;                    /* '<S7>/DP tau_yaw' */
  real_T GainK_e1_DP;                  /* '<S12>/Gain K_e1_DP' */
  real_T GainK_e2_DP;                  /* '<S12>/Gain K_e2_DP' */
  real_T GainK_e3_DP;                  /* '<S12>/Gain K_e3_DP' */
  real_T GainK_e4_DP;                  /* '<S12>/Gain K_e4_DP' */
  real_T GainK_e5_DP;                  /* '<S12>/Gain K_e5_DP' */
  real_T ThrusterGainmatrix_o[25];     /* '<S12>/Thruster Gain matrix' */
  real_T K_e1_g[25];                   /* '<S7>/K_e^-1' */
  real_T l_x1_m;                       /* '<S14>/-l_x1' */
  real_T l_y2_f;                       /* '<S14>/-l_y2' */
  real_T l_x2_k;                       /* '<S14>/-l_x2' */
  real_T x5_j[15];                     /* '<S14>/3x5' */
  real_T T_e_d[15];                    /* '<S7>/T_e^+' */
  real_T Product_c[15];                /* '<S7>/Product' */
  real_T TmpHiddenBufferAtProduct1Inpo_e[3];/* 'synthesized block' */
  real_T Product1_i[5];                /* '<S7>/Product1' */
  real_T DPu_1;                        /* '<S7>/DP u_1' */
  real_T DPu_2;                        /* '<S7>/DP u_2' */
  real_T DPu_3;                        /* '<S7>/DP u_3' */
  real_T DPu_4;                        /* '<S7>/DP u_4' */
  real_T DPu_5;                        /* '<S7>/DP u_5' */
  real_T Gain1_g[3];                   /* '<S13>/Gain1' */
  real_T xi_w[3];                      /* '<S13>/Integrator2' */
  real_T Gain2[3];                     /* '<S13>/Gain2' */
  real_T Sum4[3];                      /* '<S13>/Sum4' */
  real_T Sum2_d[3];                    /* '<S13>/Sum2' */
  real_T Saturation_ho;                /* '<S22>/Saturation' */
  real_T Sign_jh;                      /* '<S22>/Sign' */
  real_T Gain_it;                      /* '<S22>/Gain' */
  real_T Sum1_pt;                      /* '<S22>/Sum1' */
  real_T MathFunction_c;               /* '<S22>/Math Function' */
  real_T Sum_hw;                       /* '<S22>/Sum' */
  real_T TmpHiddenBufferAtK11Inport1[3];/* 'synthesized block' */
  real_T K4[3];                        /* '<S13>/K4' */
  real_T Row1_b;                       /* '<S19>/Row1' */
  real_T Row2_d;                       /* '<S19>/Row2' */
  real_T Row3_h;                       /* '<S19>/Row3' */
  real_T bias[3];                      /* '<S13>/Integrator3' */
  real_T Row1_g;                       /* '<S20>/Row1' */
  real_T Row2_b;                       /* '<S20>/Row2' */
  real_T Row3_p;                       /* '<S20>/Row3' */
  real_T Sum1_g[3];                    /* '<S13>/Sum1' */
  real_T Gain6[3];                     /* '<S13>/Gain6' */
  real_T Sum8[3];                      /* '<S13>/Sum8' */
  real_T Gain3[3];                     /* '<S13>/Gain3' */
  real_T K11[3];                       /* '<S13>/K11' */
  real_T K12[3];                       /* '<S13>/K12' */
  real_T K2[3];                        /* '<S13>/K2' */
  real_T K3[3];                        /* '<S13>/K3' */
  real_T x_dot;                        /* '<S18>/Fcn' */
  real_T y_dot;                        /* '<S18>/Fcn1' */
  real_T psi_dot;                      /* '<S18>/Fcn2' */
  real_T Sum3_h[3];                    /* '<S13>/Sum3' */
  real_T psi_WF[3];                    /* '<S13>/Sum5' */
  real_T Sum6[3];                      /* '<S13>/Sum6' */
  real_T invT_b[3];                    /* '<S13>/inv(T_b)' */
  real_T Sum7[3];                      /* '<S13>/Sum7' */
  real_T Saturation_p[5];              /* '<S7>/Saturation' */
  real_T VSP_speeds;                   /* '<S7>/VSP_speeds' */
  uint8_T Compare;                     /* '<S10>/Compare' */
  boolean_T LowerRelop1;               /* '<S58>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S58>/UpperRelop' */
  boolean_T LowerRelop1_n;             /* '<S39>/LowerRelop1' */
  boolean_T UpperRelop_m;              /* '<S39>/UpperRelop' */
  boolean_T LowerRelop1_j;             /* '<S40>/LowerRelop1' */
  boolean_T UpperRelop_b;              /* '<S40>/UpperRelop' */
  boolean_T LowerRelop1_b;             /* '<S41>/LowerRelop1' */
  boolean_T UpperRelop_h;              /* '<S41>/UpperRelop' */
} BlockIO_LgV2;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T DelayInput2_DSTATE;           /* '<S56>/Delay Input2' */
  real_T K_e1_DWORK1[25];              /* '<S8>/K_e^-1' */
  real_T K_e1_DWORK3[25];              /* '<S8>/K_e^-1' */
  real_T K_e1_DWORK4[25];              /* '<S8>/K_e^-1' */
  real_T T_e_WORK[3];                  /* '<S8>/T_e^+' */
  real_T T_e_S[4];                     /* '<S8>/T_e^+' */
  real_T T_e_U[9];                     /* '<S8>/T_e^+' */
  real_T T_e_V[25];                    /* '<S8>/T_e^+' */
  real_T Inverse_DWORK4[9];            /* '<S51>/Inverse' */
  real_T T_eK_e1u_e_DWORK1[5];         /* '<S47>/T_e^+ K_e^-1 u_e' */
  real_T K_e1_DWORK4_d[25];            /* '<S7>/K_e^-1' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } Derivative_RWORK;                  /* '<S31>/Derivative' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<Root>/To File' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK_b;                    /* '<S7>/To File' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK_e;                    /* '<S11>/To File' */

  int32_T K_e1_DWORK2[5];              /* '<S8>/K_e^-1' */
  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<Root>/To File' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S46>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S46>/Integrator1' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK_h;                    /* '<S7>/To File' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK_k;                    /* '<S11>/To File' */

  int_T LinearSimulator_MODE;          /* '<S5>/Linear Simulator' */
  int_T DPcontrol_MODE;                /* '<S1>/DP control' */
  int_T CSE1_MODE;                     /* '<S5>/CSE1' */
  uint8_T SignalProbe_DWORK1[5];       /* '<Root>/SignalProbe' */
} D_Work_LgV2;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S25>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S25>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S25>/Transfer Fcn2' */
  real_T Integrator_CSTATE[3];         /* '<S46>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S46>/Integrator1' */
  real_T Integrator1_CSTATE_m[3];      /* '<S13>/Integrator1' */
  real_T Integrator_CSTATE_h[3];       /* '<S13>/Integrator' */
  real_T Integrator_CSTATE_k[3];       /* '<S11>/Integrator' */
  real_T Integrator4_CSTATE[3];        /* '<S13>/Integrator4' */
  real_T Integrator2_CSTATE[3];        /* '<S13>/Integrator2' */
  real_T Integrator3_CSTATE[3];        /* '<S13>/Integrator3' */
} ContinuousStates_LgV2;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S25>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S25>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S25>/Transfer Fcn2' */
  real_T Integrator_CSTATE[3];         /* '<S46>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S46>/Integrator1' */
  real_T Integrator1_CSTATE_m[3];      /* '<S13>/Integrator1' */
  real_T Integrator_CSTATE_h[3];       /* '<S13>/Integrator' */
  real_T Integrator_CSTATE_k[3];       /* '<S11>/Integrator' */
  real_T Integrator4_CSTATE[3];        /* '<S13>/Integrator4' */
  real_T Integrator2_CSTATE[3];        /* '<S13>/Integrator2' */
  real_T Integrator3_CSTATE[3];        /* '<S13>/Integrator3' */
} StateDerivatives_LgV2;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<S25>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S25>/Transfer Fcn1' */
  boolean_T TransferFcn2_CSTATE;       /* '<S25>/Transfer Fcn2' */
  boolean_T Integrator_CSTATE[3];      /* '<S46>/Integrator' */
  boolean_T Integrator1_CSTATE[3];     /* '<S46>/Integrator1' */
  boolean_T Integrator1_CSTATE_m[3];   /* '<S13>/Integrator1' */
  boolean_T Integrator_CSTATE_h[3];    /* '<S13>/Integrator' */
  boolean_T Integrator_CSTATE_k[3];    /* '<S11>/Integrator' */
  boolean_T Integrator4_CSTATE[3];     /* '<S13>/Integrator4' */
  boolean_T Integrator2_CSTATE[3];     /* '<S13>/Integrator2' */
  boolean_T Integrator3_CSTATE[3];     /* '<S13>/Integrator3' */
} StateDisabled_LgV2;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S46>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S46>/Integrator1' */
  ZCSigState Integrator_Reset_ZCE_f;   /* '<S11>/Integrator' */
} PrevZCSigStates_LgV2;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            LgV2_B
#define BlockIO                        BlockIO_LgV2
#define rtX                            LgV2_X
#define ContinuousStates               ContinuousStates_LgV2
#define rtP                            LgV2_P
#define Parameters                     Parameters_LgV2
#define rtDWork                        LgV2_DWork
#define D_Work                         D_Work_LgV2
#define rtPrevZCSigState               LgV2_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_LgV2

/* Parameters (auto storage) */
struct Parameters_LgV2_ {
  real_T ControlMode_Value;            /* Expression: 0
                                        * '<S1>/Control Mode'
                                        */
  real_T u1_Value;                     /* Expression: 0
                                        * '<S26>/u1'
                                        */
  real_T Accuracyu_1_Gain;             /* Expression: 1
                                        * '<S26>/Accuracy u_1'
                                        */
  real_T u2_Value;                     /* Expression: 0
                                        * '<S26>/u2'
                                        */
  real_T Accuracyu_2_Gain;             /* Expression: 1
                                        * '<S26>/Accuracy u_2'
                                        */
  real_T u3_Value;                     /* Expression: 0
                                        * '<S26>/u3'
                                        */
  real_T Accuracyu_3_Gain;             /* Expression: 1
                                        * '<S26>/Accuracy u_3'
                                        */
  real_T u4_Value;                     /* Expression: 0
                                        * '<S26>/u4'
                                        */
  real_T Accuracyu_4_Gain;             /* Expression: 1
                                        * '<S26>/Accuracy u_4'
                                        */
  real_T u5_Value;                     /* Expression: 0
                                        * '<S26>/u5'
                                        */
  real_T Accuracyu_5_Gain;             /* Expression: 1
                                        * '<S26>/Accuracy u_5'
                                        */
  real_T AccuracyBTpower_Value;        /* Expression: 0
                                        * '<S26>/Accuracy  BT power'
                                        */
  real_T AccuracyVSPspeed_Value;       /* Expression: 0
                                        * '<S26>/Accuracy  VSP speed'
                                        */
  real_T JS_L_Y_Value;                 /* Expression: 0
                                        * '<S30>/JS_L_Y'
                                        */
  real_T Scaling_JS_L_Y_Gain;          /* Expression: 1/32767
                                        * '<S30>/Scaling_JS_L_Y'
                                        */
  real_T PS3u_1_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_1'
                                        */
  real_T JS_L_X_Value;                 /* Expression: 0
                                        * '<S30>/JS_L_X'
                                        */
  real_T Scaling_JS_L_X_Gain;          /* Expression: 1/32767
                                        * '<S30>/Scaling_JS_L_X'
                                        */
  real_T PS3u_2_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_2'
                                        */
  real_T JS_R_Y_Value;                 /* Expression: 0
                                        * '<S30>/JS_R_Y'
                                        */
  real_T Scaling_JS_R_Y_Gain;          /* Expression: 1/32767
                                        * '<S30>/Scaling_JS_R_Y'
                                        */
  real_T PS3u_3_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_3'
                                        */
  real_T JS_R_X_Value;                 /* Expression: 0
                                        * '<S30>/JS_R_X'
                                        */
  real_T Scaling_JS_R_X_Gain;          /* Expression: 1/32767
                                        * '<S30>/Scaling_JS_R_X'
                                        */
  real_T PS3u_4_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_4'
                                        */
  real_T L2_Value;                     /* Expression: 0
                                        * '<S30>/L2'
                                        */
  real_T R2_Value;                     /* Expression: 0
                                        * '<S30>/R2'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_5'
                                        */
  real_T PS3_BT_Power_Value;           /* Expression: 0
                                        * '<S28>/PS3_BT_Power'
                                        */
  real_T PS3_VSP_Speed_Value;          /* Expression: 0
                                        * '<S28>/PS3_VSP_Speed'
                                        */
  real_T K_e1_joystick_Value;          /* Expression: 1
                                        * '<S23>/K_e1_joystick'
                                        */
  real_T GainK_e1_joystick_Gain;       /* Expression: 1
                                        * '<S23>/Gain K_e1_joystick'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * '<S23>/Constant'
                                        */
  real_T K_e2_joystick_Value;          /* Expression: 1
                                        * '<S23>/K_e2_joystick'
                                        */
  real_T GainK_e2_joystick_Gain;       /* Expression: 1
                                        * '<S23>/Gain K_e2_joystick'
                                        */
  real_T K_e3_joystick_Value;          /* Expression: 1
                                        * '<S23>/K_e3_joystick'
                                        */
  real_T GainK_e3_joystick_Gain;       /* Expression: 1
                                        * '<S23>/Gain K_e3_joystick'
                                        */
  real_T K_e4_joystick_Value;          /* Expression: 1
                                        * '<S23>/K_e4_joystick'
                                        */
  real_T GainK_e4_joystick_Gain;       /* Expression: 1
                                        * '<S23>/Gain K_e4_joystick'
                                        */
  real_T K_e5_joystick_Value;          /* Expression: 1
                                        * '<S23>/K_e5_joystick'
                                        */
  real_T GainK_e5_joystick_Gain;       /* Expression: 1
                                        * '<S23>/Gain K_e5_joystick'
                                        */
  real_T T_e11_Value;                  /* Expression: 1
                                        * '<S24>/T_e11'
                                        */
  real_T T_e21_Value;                  /* Expression: 0
                                        * '<S24>/T_e21'
                                        */
  real_T l_y1_Value;                   /* Expression: 0.055
                                        * '<S24>/l_y1'
                                        */
  real_T T_e12_Value;                  /* Expression: 0
                                        * '<S24>/T_e12'
                                        */
  real_T T_e22_Value;                  /* Expression: 1
                                        * '<S24>/T_e22'
                                        */
  real_T l_x1_Value;                   /* Expression: 0.425
                                        * '<S24>/l_x1'
                                        */
  real_T l_x1_Gain;                    /* Expression: -1
                                        * '<S24>/-l_x1'
                                        */
  real_T T_e13_Value;                  /* Expression: 1
                                        * '<S24>/T_e13'
                                        */
  real_T T_e23_Value;                  /* Expression: 0
                                        * '<S24>/T_e23'
                                        */
  real_T l_y2_Value;                   /* Expression: 0.055
                                        * '<S24>/l_y2'
                                        */
  real_T l_y2_Gain;                    /* Expression: -1
                                        * '<S24>/-l_y2'
                                        */
  real_T T_e14_Value;                  /* Expression: 0
                                        * '<S24>/T_e14'
                                        */
  real_T T_e24_Value;                  /* Expression: 1
                                        * '<S24>/T_e24'
                                        */
  real_T l_x2_Value;                   /* Expression: 0.425
                                        * '<S24>/l_x2'
                                        */
  real_T l_x2_Gain;                    /* Expression: -1
                                        * '<S24>/-l_x2'
                                        */
  real_T T_e15_Value;                  /* Expression: 0
                                        * '<S24>/T_e15'
                                        */
  real_T T_e25_Value;                  /* Expression: 1
                                        * '<S24>/T_e25'
                                        */
  real_T l_x3_Value;                   /* Expression: 0.425
                                        * '<S24>/l_x3'
                                        */
  real_T Joysticktau_surge_Gain;       /* Expression: 1
                                        * '<S8>/Joystick tau_surge'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 1.0
                                        * '<S8>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -1.0
                                        * '<S8>/Saturation1'
                                        */
  real_T Joysticktau_sway_Gain;        /* Expression: 1
                                        * '<S8>/Joystick tau_sway'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.0
                                        * '<S8>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.0
                                        * '<S8>/Saturation2'
                                        */
  real_T Joysticktau_yaw_Gain;         /* Expression: 1
                                        * '<S8>/Joystick tau_yaw'
                                        */
  real_T Saturation3_UpperSat;         /* Expression: 1.0
                                        * '<S8>/Saturation3'
                                        */
  real_T Saturation3_LowerSat;         /* Expression: -1.0
                                        * '<S8>/Saturation3'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1.0
                                        * '<S8>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1.0
                                        * '<S8>/Saturation'
                                        */
  real_T Joysticku_1_Gain;             /* Expression: 1
                                        * '<S8>/Joystick u_1'
                                        */
  real_T Joysticku_2_Gain;             /* Expression: 1
                                        * '<S8>/Joystick u_2'
                                        */
  real_T Joysticku_3_Gain;             /* Expression: 1
                                        * '<S8>/Joystick u_3'
                                        */
  real_T Joysticku_4_Gain;             /* Expression: 1
                                        * '<S8>/Joystick u_4'
                                        */
  real_T Joysticku_5_Gain;             /* Expression: 1
                                        * '<S8>/Joystick u_5'
                                        */
  real_T Enableeta_dLPF_Value;         /* Expression: 0
                                        * '<S25>/Enable eta_d LPF'
                                        */
  real_T x_d_Value;                    /* Expression: 0
                                        * '<S27>/x_d'
                                        */
  real_T y_d_Value;                    /* Expression: 0
                                        * '<S27>/y_d'
                                        */
  real_T psi_d_Value;                  /* Expression: 0
                                        * '<S27>/psi_d'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * '<S29>/Gain1'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: A
                                        * '<S25>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: C
                                        * '<S25>/Transfer Fcn'
                                        */
  real_T TransferFcn1_A;               /* Computed Parameter: A
                                        * '<S25>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: C
                                        * '<S25>/Transfer Fcn1'
                                        */
  real_T TransferFcn2_A;               /* Computed Parameter: A
                                        * '<S25>/Transfer Fcn2'
                                        */
  real_T TransferFcn2_C;               /* Computed Parameter: C
                                        * '<S25>/Transfer Fcn2'
                                        */
  real_T eta_dDPN_Gain;                /* Expression: 1
                                        * '<S25>/eta_d DP N'
                                        */
  real_T eta_dDPE_Gain;                /* Expression: 1
                                        * '<S25>/eta_d DP E'
                                        */
  real_T eta_dDPPsi_Gain;              /* Expression: 1
                                        * '<S25>/eta_d DP Psi'
                                        */
  real_T ControllerInputSelector_Value;/* Expression: 0
                                        * '<S4>/Controller Input Selector'
                                        */
  real_T QTMIn_P1;                     /* Expression: width
                                        * '<S31>/QTM In'
                                        */
  real_T QTMIn_P2;                     /* Expression: dtype
                                        * '<S31>/QTM In'
                                        */
  real_T QTMIn_P3;                     /* Expression: portnum
                                        * '<S31>/QTM In'
                                        */
  real_T QTMIn_P4;                     /* Expression: stime
                                        * '<S31>/QTM In'
                                        */
  real_T QTMIn_P5;                     /* Expression: stype
                                        * '<S31>/QTM In'
                                        */
  real_T QTMIn_P6;                     /* Expression: btype
                                        * '<S31>/QTM In'
                                        */
  real_T QTMIn3_Gain;                  /* Expression: 1
                                        * '<S31>/QTM In3'
                                        */
  real_T mm2mx_Gain;                   /* Expression: 0.001
                                        * '<S31>/mm2m x'
                                        */
  real_T QTMIn4_Gain;                  /* Expression: 1
                                        * '<S31>/QTM In4'
                                        */
  real_T mm2my_Gain;                   /* Expression: 0.001
                                        * '<S31>/mm2m y'
                                        */
  real_T QTMIn6_Gain;                  /* Expression: 1
                                        * '<S31>/QTM In6'
                                        */
  real_T d2ryaw_Gain;                  /* Expression: pi/180
                                        * '<S31>/d2r yaw'
                                        */
  real_T EnableLinearSimulator_Value;  /* Expression: 0
                                        * '<S5>/Enable Linear Simulator'
                                        */
  real_T eta_surge_Gain;               /* Expression: 1
                                        * '<S4>/eta_surge'
                                        */
  real_T eta_sway_Gain;                /* Expression: 1
                                        * '<S4>/eta_sway'
                                        */
  real_T eta_yaw_Gain;                 /* Expression: 1
                                        * '<S4>/eta_yaw'
                                        */
  real_T QTMIn8_Gain;                  /* Expression: 1
                                        * '<S31>/QTM In8'
                                        */
  real_T d2rroll_Gain;                 /* Expression: pi/180
                                        * '<S31>/d2r roll'
                                        */
  real_T QTMIn7_Gain;                  /* Expression: 1
                                        * '<S31>/QTM In7'
                                        */
  real_T d2rpitch_Gain;                /* Expression: pi/180
                                        * '<S31>/d2r pitch'
                                        */
  real_T Constant1_Value[9];           /* Expression: zeros(3)
                                        * '<S31>/Constant1'
                                        */
  real_T QTMIn5_Gain;                  /* Expression: 1
                                        * '<S31>/QTM In5'
                                        */
  real_T mm2mz_Gain;                   /* Expression: 0.001
                                        * '<S31>/mm2m z'
                                        */
  real_T nu_surge_Gain;                /* Expression: 1
                                        * '<S4>/nu_surge'
                                        */
  real_T nu_sway_Gain;                 /* Expression: 1
                                        * '<S4>/nu_sway'
                                        */
  real_T nu_yaw_Gain;                  /* Expression: 1
                                        * '<S4>/nu_yaw'
                                        */
  real_T Constant_Value_j;             /* Expression: const
                                        * '<S10>/Constant'
                                        */
  real_T Saturation_UpperSat_p;        /* Expression: 1.0
                                        * '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat_g;        /* Expression: -1.0
                                        * '<S1>/Saturation'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S31>/QTM In2 Error'
                                        */
  real_T eta_dPsideg_Gain;             /* Expression: 180/pi
                                        * '<S25>/eta_d Psi deg'
                                        */
  real_T psi_d_Gain;                   /* Expression: 1
                                        * '<S2>/psi_d'
                                        */
  real_T x_d_Gain;                     /* Expression: 1
                                        * '<S2>/x_d'
                                        */
  real_T y_d_Gain;                     /* Expression: 1
                                        * '<S2>/y_d'
                                        */
  real_T SITzAI0_P1;                   /* Expression: width
                                        * '<S3>/SIT zAI0'
                                        */
  real_T SITzAI0_P2;                   /* Expression: dtype
                                        * '<S3>/SIT zAI0'
                                        */
  real_T SITzAI0_P3;                   /* Expression: portnum
                                        * '<S3>/SIT zAI0'
                                        */
  real_T SITzAI0_P4;                   /* Expression: stime
                                        * '<S3>/SIT zAI0'
                                        */
  real_T SITzAI0_P5;                   /* Expression: stype
                                        * '<S3>/SIT zAI0'
                                        */
  real_T SITzAI0_P6;                   /* Expression: btype
                                        * '<S3>/SIT zAI0'
                                        */
  real_T BatteryBowThruster_Gain;      /* Expression: 1
                                        * '<S3>/Battery Bow Thruster'
                                        */
  real_T SITzAI1_P1;                   /* Expression: width
                                        * '<S3>/SIT zAI1'
                                        */
  real_T SITzAI1_P2;                   /* Expression: dtype
                                        * '<S3>/SIT zAI1'
                                        */
  real_T SITzAI1_P3;                   /* Expression: portnum
                                        * '<S3>/SIT zAI1'
                                        */
  real_T SITzAI1_P4;                   /* Expression: stime
                                        * '<S3>/SIT zAI1'
                                        */
  real_T SITzAI1_P5;                   /* Expression: stype
                                        * '<S3>/SIT zAI1'
                                        */
  real_T SITzAI1_P6;                   /* Expression: btype
                                        * '<S3>/SIT zAI1'
                                        */
  real_T BatteryServo_Gain;            /* Expression: 1
                                        * '<S3>/Battery Servo'
                                        */
  real_T SITzAI2_P1;                   /* Expression: width
                                        * '<S3>/SIT zAI2'
                                        */
  real_T SITzAI2_P2;                   /* Expression: dtype
                                        * '<S3>/SIT zAI2'
                                        */
  real_T SITzAI2_P3;                   /* Expression: portnum
                                        * '<S3>/SIT zAI2'
                                        */
  real_T SITzAI2_P4;                   /* Expression: stime
                                        * '<S3>/SIT zAI2'
                                        */
  real_T SITzAI2_P5;                   /* Expression: stype
                                        * '<S3>/SIT zAI2'
                                        */
  real_T SITzAI2_P6;                   /* Expression: btype
                                        * '<S3>/SIT zAI2'
                                        */
  real_T BatteryMain_Gain;             /* Expression: 1
                                        * '<S3>/Battery Main'
                                        */
  real_T QTMIn1FPS_Gain;               /* Expression: 1
                                        * '<S31>/QTM In1 FPS'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S31>/QTM In9 Residual'
                                        */
  real_T u_1plant_Gain;                /* Expression: 1
                                        * '<S5>/u_1 plant'
                                        */
  real_T u_2plant_Gain;                /* Expression: 1
                                        * '<S5>/u_2 plant'
                                        */
  real_T u_3plant_Gain;                /* Expression: 1
                                        * '<S5>/u_3 plant'
                                        */
  real_T u_4plant_Gain;                /* Expression: 1
                                        * '<S5>/u_4 plant'
                                        */
  real_T u_5plant_Gain;                /* Expression: 1
                                        * '<S5>/u_5 plant'
                                        */
  real_T BTpowerlimitplant_Gain;       /* Expression: 1
                                        * '<S5>/BT power limit plant'
                                        */
  real_T VSPspeedplant_Gain;           /* Expression: 1
                                        * '<S5>/VSP speed plant'
                                        */
  real_T EnableCSE1_Value;             /* Expression: 0
                                        * '<S5>/Enable CSE1'
                                        */
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T Thruster_Command_DP_Y0[7];    /* Expression: [0;0;0;0;0;0;0]
                                        * '<S7>/Thruster_Command_DP'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * '<S13>/Integrator1'
                                        */
  real_T BT_power_limit_Value;         /* Expression: 0.5
                                        * '<S7>/BT_power_limit'
                                        */
  real_T EnableFilter_Value;           /* Expression: 0
                                        * '<S7>/Enable Filter'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * '<S13>/Integrator'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 1e10
                                        * '<S21>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: -1e10
                                        * '<S21>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * '<S21>/Gain'
                                        */
  real_T Constant_Value_jr;            /* Expression: 2*pi
                                        * '<S21>/Constant'
                                        */
  real_T etaN_Gain;                    /* Expression: 1
                                        * '<S11>/eta N'
                                        */
  real_T etaE_Gain;                    /* Expression: 1
                                        * '<S11>/eta E'
                                        */
  real_T etaPsi_Gain;                  /* Expression: 1
                                        * '<S11>/eta Psi'
                                        */
  real_T Reg_e_N_hil_Gain;             /* Expression: 1
                                        * '<S11>/Reg_e_N_hil'
                                        */
  real_T Reg_e_E_hil_Gain;             /* Expression: 1
                                        * '<S11>/Reg_e_E_hil'
                                        */
  real_T Reg_e_Psi_hil_Gain;           /* Expression: 1
                                        * '<S11>/Reg_e_Psi_hil'
                                        */
  real_T Reset_DP_integrator_Value;    /* Expression: 0
                                        * '<S11>/Reset_DP_integrator'
                                        */
  real_T Integrator_IC_f;              /* Expression: 0
                                        * '<S11>/Integrator'
                                        */
  real_T Integrator4_IC;               /* Expression: 0
                                        * '<S13>/Integrator4'
                                        */
  real_T Kd_Gain[9];                   /* Expression: Kd
                                        * '<S11>/Kd'
                                        */
  real_T Kd_scale_Value;               /* Expression: 1
                                        * '<S11>/Kd_scale'
                                        */
  real_T K_d1_Gain;                    /* Expression: 1
                                        * '<S11>/K_d 1'
                                        */
  real_T K_d2_Gain;                    /* Expression: 1
                                        * '<S11>/K_d 2'
                                        */
  real_T K_d3_Gain;                    /* Expression: 1
                                        * '<S11>/K_d 3'
                                        */
  real_T K_d3deg_Gain;                 /* Expression: 180/pi
                                        * '<S11>/K_d 3 deg'
                                        */
  real_T Ki_Gain[9];                   /* Expression: Ki
                                        * '<S11>/Ki'
                                        */
  real_T Ki_scale_Value;               /* Expression: 1
                                        * '<S11>/Ki_scale'
                                        */
  real_T K_i1_Gain;                    /* Expression: 1
                                        * '<S11>/K_i 1'
                                        */
  real_T K_i2_Gain;                    /* Expression: 1
                                        * '<S11>/K_i 2'
                                        */
  real_T K_i3_Gain;                    /* Expression: 1
                                        * '<S11>/K_i 3'
                                        */
  real_T K_i3deg_Gain;                 /* Expression: 180/pi
                                        * '<S11>/K_i 3 deg'
                                        */
  real_T Kp_scale_Value;               /* Expression: 1
                                        * '<S11>/Kp_scale'
                                        */
  real_T Saturation_UpperSat_j;        /* Expression: 1e10
                                        * '<S17>/Saturation'
                                        */
  real_T Saturation_LowerSat_j;        /* Expression: -1e10
                                        * '<S17>/Saturation'
                                        */
  real_T Gain_Gain_h;                  /* Expression: pi
                                        * '<S17>/Gain'
                                        */
  real_T Constant_Value_g;             /* Expression: 2*pi
                                        * '<S17>/Constant'
                                        */
  real_T Saturation_UpperSat_g;        /* Expression: 1e10
                                        * '<S16>/Saturation'
                                        */
  real_T Saturation_LowerSat_m;        /* Expression: -1e10
                                        * '<S16>/Saturation'
                                        */
  real_T Gain_Gain_f;                  /* Expression: pi
                                        * '<S16>/Gain'
                                        */
  real_T Constant_Value_gt;            /* Expression: 2*pi
                                        * '<S16>/Constant'
                                        */
  real_T Kp_Gain[9];                   /* Expression: Kp
                                        * '<S11>/Kp'
                                        */
  real_T K_p1_Gain;                    /* Expression: 1
                                        * '<S11>/K_p 1'
                                        */
  real_T K_p2_Gain;                    /* Expression: 1
                                        * '<S11>/K_p 2'
                                        */
  real_T K_p3_Gain;                    /* Expression: 1
                                        * '<S11>/K_p 3'
                                        */
  real_T K_p3deg_Gain;                 /* Expression: 180/pi
                                        * '<S11>/K_p 3 deg'
                                        */
  real_T Reg_e_Psi_deg_Gain;           /* Expression: 180/pi
                                        * '<S11>/Reg_e_Psi_deg'
                                        */
  real_T etaPsideg_Gain;               /* Expression: 180/pi
                                        * '<S11>/eta Psi deg'
                                        */
  real_T DPtau_surge_Gain;             /* Expression: 1
                                        * '<S7>/DP tau_surge'
                                        */
  real_T DPtau_sway_Gain;              /* Expression: 1
                                        * '<S7>/DP tau_sway'
                                        */
  real_T DPtau_yaw_Gain;               /* Expression: 1
                                        * '<S7>/DP tau_yaw'
                                        */
  real_T K_e1_DP_Value;                /* Expression: 1
                                        * '<S12>/K_e1_DP'
                                        */
  real_T GainK_e1_DP_Gain;             /* Expression: 1
                                        * '<S12>/Gain K_e1_DP'
                                        */
  real_T Constant_Value_c;             /* Expression: 0
                                        * '<S12>/Constant'
                                        */
  real_T K_e2_DP_Value;                /* Expression: 1
                                        * '<S12>/K_e2_DP'
                                        */
  real_T GainK_e2_DP_Gain;             /* Expression: 1
                                        * '<S12>/Gain K_e2_DP'
                                        */
  real_T K_e3_DP_Value;                /* Expression: 1
                                        * '<S12>/K_e3_DP'
                                        */
  real_T GainK_e3_DP_Gain;             /* Expression: 1
                                        * '<S12>/Gain K_e3_DP'
                                        */
  real_T K_e4_DP_Value;                /* Expression: 1
                                        * '<S12>/K_e4_DP'
                                        */
  real_T GainK_e4_DP_Gain;             /* Expression: 1
                                        * '<S12>/Gain K_e4_DP'
                                        */
  real_T K_e5_DP_Value;                /* Expression: 1
                                        * '<S12>/K_e5_DP'
                                        */
  real_T GainK_e5_DP_Gain;             /* Expression: 1
                                        * '<S12>/Gain K_e5_DP'
                                        */
  real_T T_e11_Value_o;                /* Expression: 1
                                        * '<S14>/T_e11'
                                        */
  real_T T_e21_Value_d;                /* Expression: 0
                                        * '<S14>/T_e21'
                                        */
  real_T l_y1_Value_p;                 /* Expression: 0.055
                                        * '<S14>/l_y1'
                                        */
  real_T T_e12_Value_i;                /* Expression: 0
                                        * '<S14>/T_e12'
                                        */
  real_T T_e22_Value_o;                /* Expression: 1
                                        * '<S14>/T_e22'
                                        */
  real_T l_x1_Value_e;                 /* Expression: 0.425
                                        * '<S14>/l_x1'
                                        */
  real_T l_x1_Gain_j;                  /* Expression: -1
                                        * '<S14>/-l_x1'
                                        */
  real_T T_e13_Value_g;                /* Expression: 1
                                        * '<S14>/T_e13'
                                        */
  real_T T_e23_Value_o;                /* Expression: 0
                                        * '<S14>/T_e23'
                                        */
  real_T l_y2_Value_e;                 /* Expression: 0.055
                                        * '<S14>/l_y2'
                                        */
  real_T l_y2_Gain_l;                  /* Expression: -1
                                        * '<S14>/-l_y2'
                                        */
  real_T T_e14_Value_e;                /* Expression: 0
                                        * '<S14>/T_e14'
                                        */
  real_T T_e24_Value_c;                /* Expression: 1
                                        * '<S14>/T_e24'
                                        */
  real_T l_x2_Value_d;                 /* Expression: 0.425
                                        * '<S14>/l_x2'
                                        */
  real_T l_x2_Gain_b;                  /* Expression: -1
                                        * '<S14>/-l_x2'
                                        */
  real_T T_e15_Value_h;                /* Expression: 0
                                        * '<S14>/T_e15'
                                        */
  real_T T_e25_Value_c;                /* Expression: 1
                                        * '<S14>/T_e25'
                                        */
  real_T l_x3_Value_d;                 /* Expression: 0.425
                                        * '<S14>/l_x3'
                                        */
  real_T DPu_1_Gain;                   /* Expression: 1
                                        * '<S7>/DP u_1'
                                        */
  real_T DPu_2_Gain;                   /* Expression: 1
                                        * '<S7>/DP u_2'
                                        */
  real_T DPu_3_Gain;                   /* Expression: 1
                                        * '<S7>/DP u_3'
                                        */
  real_T DPu_4_Gain;                   /* Expression: 1
                                        * '<S7>/DP u_4'
                                        */
  real_T DPu_5_Gain;                   /* Expression: 1
                                        * '<S7>/DP u_5'
                                        */
  real_T Gain1_Gain_b[9];              /* Expression: 2*lambda*w_o
                                        * '<S13>/Gain1'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * '<S13>/Integrator2'
                                        */
  real_T Gain2_Gain[9];                /* Expression: w_o*w_o
                                        * '<S13>/Gain2'
                                        */
  real_T Saturation_UpperSat_n;        /* Expression: 1e10
                                        * '<S22>/Saturation'
                                        */
  real_T Saturation_LowerSat_c;        /* Expression: -1e10
                                        * '<S22>/Saturation'
                                        */
  real_T Gain_Gain_e;                  /* Expression: pi
                                        * '<S22>/Gain'
                                        */
  real_T Constant_Value_a;             /* Expression: 2*pi
                                        * '<S22>/Constant'
                                        */
  real_T K4_Gain[9];                   /* Expression: K4
                                        * '<S13>/K4'
                                        */
  real_T Integrator3_IC;               /* Expression: 0
                                        * '<S13>/Integrator3'
                                        */
  real_T Gain6_Gain[9];                /* Expression: D
                                        * '<S13>/Gain6'
                                        */
  real_T Gain3_Gain[9];                /* Expression: inv(M)
                                        * '<S13>/Gain3'
                                        */
  real_T K11_Gain[9];                  /* Expression: -2*(eye(3)-lambda)*diag([w_c(1,1)/w_o(1,1) w_c(2,2)/w_o(2,2) w_c(3,3)/w_o(3,3)])
                                        * '<S13>/K11'
                                        */
  real_T K12_Gain[9];                  /* Expression: 2*w_o*(eye(3)-lambda)
                                        * '<S13>/K12'
                                        */
  real_T K2_Gain[9];                   /* Expression: w_c
                                        * '<S13>/K2'
                                        */
  real_T K3_Gain[9];                   /* Expression: K3
                                        * '<S13>/K3'
                                        */
  real_T invT_b_Gain[9];               /* Expression: diag([1/T_b(1,1) 1/T_b(2,2) 1/T_b(3,3)])
                                        * '<S13>/inv(T_b)'
                                        */
  real_T Saturation_UpperSat_do;       /* Expression: 1.0
                                        * '<S7>/Saturation'
                                        */
  real_T Saturation_LowerSat_d;        /* Expression: -1.0
                                        * '<S7>/Saturation'
                                        */
  real_T VSP_speeds_Value;             /* Expression: 0.4
                                        * '<S7>/VSP_speeds'
                                        */
  real_T SITOut5BT_P1;                 /* Expression: width
                                        * '<S35>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P2;                 /* Expression: dtype
                                        * '<S35>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P3;                 /* Expression: portnum
                                        * '<S35>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P4;                 /* Expression: stime
                                        * '<S35>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P5;                 /* Expression: stype
                                        * '<S35>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P6;                 /* Expression: btype
                                        * '<S35>/SIT Out5 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S35>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S35>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S35>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S35>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S35>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S35>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S35>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_i;             /* Expression: 0
                                        * '<S35>/Constant'
                                        */
  real_T Constant1_Value_j;            /* Expression: 0
                                        * '<S35>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S35>/Neg'
                                        */
  real_T SITOut1Servo1_P1;             /* Expression: width
                                        * '<S38>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P2;             /* Expression: dtype
                                        * '<S38>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P3;             /* Expression: portnum
                                        * '<S38>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P4;             /* Expression: stime
                                        * '<S38>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P5;             /* Expression: stype
                                        * '<S38>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P6;             /* Expression: btype
                                        * '<S38>/SIT Out1 Servo1'
                                        */
  real_T SITOut2Servo2_P1;             /* Expression: width
                                        * '<S38>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P2;             /* Expression: dtype
                                        * '<S38>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P3;             /* Expression: portnum
                                        * '<S38>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P4;             /* Expression: stime
                                        * '<S38>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P5;             /* Expression: stype
                                        * '<S38>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P6;             /* Expression: btype
                                        * '<S38>/SIT Out2 Servo2'
                                        */
  real_T SITOut3Servo3_P1;             /* Expression: width
                                        * '<S38>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P2;             /* Expression: dtype
                                        * '<S38>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P3;             /* Expression: portnum
                                        * '<S38>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P4;             /* Expression: stime
                                        * '<S38>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P5;             /* Expression: stype
                                        * '<S38>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P6;             /* Expression: btype
                                        * '<S38>/SIT Out3 Servo3'
                                        */
  real_T SITOut4Servo4_P1;             /* Expression: width
                                        * '<S38>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P2;             /* Expression: dtype
                                        * '<S38>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P3;             /* Expression: portnum
                                        * '<S38>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P4;             /* Expression: stime
                                        * '<S38>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P5;             /* Expression: stype
                                        * '<S38>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P6;             /* Expression: btype
                                        * '<S38>/SIT Out4 Servo4'
                                        */
  real_T SITOut6VSPSPort_P1;           /* Expression: width
                                        * '<S38>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P2;           /* Expression: dtype
                                        * '<S38>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P3;           /* Expression: portnum
                                        * '<S38>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P4;           /* Expression: stime
                                        * '<S38>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P5;           /* Expression: stype
                                        * '<S38>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P6;           /* Expression: btype
                                        * '<S38>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut7VSPSStarboard_P1;      /* Expression: width
                                        * '<S38>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S38>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S38>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P4;      /* Expression: stime
                                        * '<S38>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P5;      /* Expression: stype
                                        * '<S38>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P6;      /* Expression: btype
                                        * '<S38>/SIT Out7 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S38>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S38>/-y'
                                        */
  real_T Gain_Gain_l;                  /* Expression: 180/pi
                                        * '<S44>/Gain'
                                        */
  real_T Gain_Gain_o;                  /* Expression: 180/pi
                                        * '<S45>/Gain'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S38>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S38>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S38>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S38>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S38>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S38>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S38>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S38>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S38>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S38>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S38>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S38>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S38>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S38>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S38>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S38>/VSPS Starboard'
                                        */
  real_T T_e11_Value_c;                /* Expression: 1
                                        * '<S37>/T_e11'
                                        */
  real_T T_e21_Value_l;                /* Expression: 0
                                        * '<S37>/T_e21'
                                        */
  real_T l_y1_Value_e;                 /* Expression: 0.055
                                        * '<S37>/l_y1'
                                        */
  real_T T_e12_Value_k;                /* Expression: 0
                                        * '<S37>/T_e12'
                                        */
  real_T T_e22_Value_i;                /* Expression: 1
                                        * '<S37>/T_e22'
                                        */
  real_T l_x1_Value_o;                 /* Expression: 0.425
                                        * '<S37>/l_x1'
                                        */
  real_T l_x1_Gain_jm;                 /* Expression: -1
                                        * '<S37>/-l_x1'
                                        */
  real_T T_e13_Value_p;                /* Expression: 1
                                        * '<S37>/T_e13'
                                        */
  real_T T_e23_Value_l;                /* Expression: 0
                                        * '<S37>/T_e23'
                                        */
  real_T l_y2_Value_f;                 /* Expression: 0.055
                                        * '<S37>/l_y2'
                                        */
  real_T l_y2_Gain_f;                  /* Expression: -1
                                        * '<S37>/-l_y2'
                                        */
  real_T T_e14_Value_b;                /* Expression: 0
                                        * '<S37>/T_e14'
                                        */
  real_T T_e24_Value_e;                /* Expression: 1
                                        * '<S37>/T_e24'
                                        */
  real_T l_x2_Value_j;                 /* Expression: 0.425
                                        * '<S37>/l_x2'
                                        */
  real_T l_x2_Gain_bv;                 /* Expression: -1
                                        * '<S37>/-l_x2'
                                        */
  real_T T_e15_Value_c;                /* Expression: 0
                                        * '<S37>/T_e15'
                                        */
  real_T T_e25_Value_o;                /* Expression: 1
                                        * '<S37>/T_e25'
                                        */
  real_T l_x3_Value_g;                 /* Expression: 0.425
                                        * '<S37>/l_x3'
                                        */
  real_T K_e1_CSE1_Value;              /* Expression: 1
                                        * '<S36>/K_e1_CSE1'
                                        */
  real_T GainK_e1_CSE1_Gain;           /* Expression: 1
                                        * '<S36>/Gain K_e1_CSE1'
                                        */
  real_T Constant_Value_p;             /* Expression: 0
                                        * '<S36>/Constant'
                                        */
  real_T K_e2_CSE1_Value;              /* Expression: 1
                                        * '<S36>/K_e2_CSE1'
                                        */
  real_T GainK_e2_CSE1_Gain;           /* Expression: 1
                                        * '<S36>/Gain K_e2_CSE1'
                                        */
  real_T K_e3_CSE1_Value;              /* Expression: 1
                                        * '<S36>/K_e3_CSE1'
                                        */
  real_T GainK_e3_CSE1_Gain;           /* Expression: 1
                                        * '<S36>/Gain K_e3_CSE1'
                                        */
  real_T K_e4_CSE1_Value;              /* Expression: 1
                                        * '<S36>/K_e4_CSE1'
                                        */
  real_T GainK_e4_CSE1_Gain;           /* Expression: 1
                                        * '<S36>/Gain K_e4_CSE1'
                                        */
  real_T K_e5_CSE1_Value;              /* Expression: 1
                                        * '<S36>/K_e5_CSE1'
                                        */
  real_T GainK_e5_CSE1_Gain;           /* Expression: 1
                                        * '<S36>/Gain K_e5_CSE1'
                                        */
  real_T CSE1tau_surge_Gain;           /* Expression: 1
                                        * '<S33>/CSE1 tau_surge'
                                        */
  real_T CSE1tau_sway_Gain;            /* Expression: 1
                                        * '<S33>/CSE1 tau_sway'
                                        */
  real_T CSE1tau_yaw_Gain;             /* Expression: 1
                                        * '<S33>/CSE1 tau_yaw'
                                        */
  real_T Gainu_1_Gain;                 /* Expression: 1
                                        * '<S47>/Gain u_1'
                                        */
  real_T Gainu_2_Gain;                 /* Expression: 1
                                        * '<S47>/Gain u_2'
                                        */
  real_T Gainu_3_Gain;                 /* Expression: 1
                                        * '<S47>/Gain u_3'
                                        */
  real_T Gainu_4_Gain;                 /* Expression: 1
                                        * '<S47>/Gain u_4'
                                        */
  real_T GainBTpower_Gain;             /* Expression: 1
                                        * '<S47>/Gain BT power'
                                        */
  real_T Neg_Gain_f;                   /* Expression: -1
                                        * '<S47>/Neg'
                                        */
  real_T Gainu_5_Gain;                 /* Expression: 1
                                        * '<S47>/Gain u_5'
                                        */
  real_T tau_surge_hil_Gain;           /* Expression: 1
                                        * '<S47>/tau_surge_hil'
                                        */
  real_T tau_sway_hil_Gain;            /* Expression: 1
                                        * '<S47>/tau_sway_hil'
                                        */
  real_T tau_yaw_hil_Gain;             /* Expression: 1
                                        * '<S47>/tau_yaw_hil'
                                        */
  real_T VSP_angle_deg_port_Gain;      /* Expression: 180/pi
                                        * '<S47>/VSP_angle_deg_port'
                                        */
  real_T VSP_angle_deg_stbd_Gain;      /* Expression: 180/pi
                                        * '<S47>/VSP_angle_deg_stbd'
                                        */
  real_T N_r_Value;                    /* Expression: -1.900
                                        * '<S48>/N_r'
                                        */
  real_T N_r_Gain;                     /* Expression: -1
                                        * '<S48>/-N_r'
                                        */
  real_T N_v_Value;                    /* Expression: 0.03130
                                        * '<S48>/N_v'
                                        */
  real_T N_v_Gain;                     /* Expression: -1
                                        * '<S48>/-N_v'
                                        */
  real_T X_u_Value;                    /* Expression: -0.72253
                                        * '<S48>/X_u'
                                        */
  real_T X_u_Gain;                     /* Expression: -1
                                        * '<S48>/-X_u'
                                        */
  real_T Y_v_Value;                    /* Expression: -0.889656
                                        * '<S48>/Y_v'
                                        */
  real_T Y_v_Gain;                     /* Expression: -1
                                        * '<S48>/-Y_v'
                                        */
  real_T Y_r_Value;                    /* Expression: -7.250
                                        * '<S48>/Y_r'
                                        */
  real_T Y_vr_Gain;                    /* Expression: -1
                                        * '<S48>/-Y_vr'
                                        */
  real_T D_L_12_Value;                 /* Expression: 0
                                        * '<S48>/D_L_12'
                                        */
  real_T D_L_13_Value;                 /* Expression: 0
                                        * '<S48>/D_L_13'
                                        */
  real_T D_L_21_Value;                 /* Expression: 0
                                        * '<S48>/D_L_21'
                                        */
  real_T D_L_31_Value;                 /* Expression: 0
                                        * '<S48>/D_L_31'
                                        */
  real_T psi_0_Value;                  /* Expression: 0
                                        * '<S49>/psi_0'
                                        */
  real_T x_0_Value;                    /* Expression: 0
                                        * '<S49>/x_0'
                                        */
  real_T y_0_Value;                    /* Expression: 0
                                        * '<S49>/y_0'
                                        */
  real_T r_0_Value;                    /* Expression: 0
                                        * '<S50>/r_0'
                                        */
  real_T u_0_Value;                    /* Expression: 0
                                        * '<S50>/u_0'
                                        */
  real_T v_0_Value;                    /* Expression: 0
                                        * '<S50>/v_0'
                                        */
  real_T ResetLinearSimulatorintegrator_;/* Expression: 0
                                          * '<S46>/Reset Linear Simulator integrator'
                                          */
  real_T I_z_Value;                    /* Expression: 1.760
                                        * '<S51>/I_z'
                                        */
  real_T m_Value;                      /* Expression: 14.1
                                        * '<S51>/m'
                                        */
  real_T X_udot_Value;                 /* Expression: -2.0
                                        * '<S51>/X_udot'
                                        */
  real_T M_21_Value;                   /* Expression: 0
                                        * '<S51>/M_21'
                                        */
  real_T M_31_Value;                   /* Expression: 0
                                        * '<S51>/M_31'
                                        */
  real_T M_12_Value;                   /* Expression: 0
                                        * '<S51>/M_12'
                                        */
  real_T Y_vdot_Value;                 /* Expression: -10.0
                                        * '<S51>/Y_vdot'
                                        */
  real_T x_g_Value;                    /* Expression: 0.03
                                        * '<S51>/x_g'
                                        */
  real_T N_vdot_Value;                 /* Expression: -0.0
                                        * '<S51>/N_vdot'
                                        */
  real_T M_13_Value;                   /* Expression: 0
                                        * '<S51>/M_13'
                                        */
  real_T Y_rdot_Value;                 /* Expression: 0.0
                                        * '<S51>/Y_rdot'
                                        */
  real_T N_rdot_Value;                 /* Expression: -1.0
                                        * '<S51>/N_rdot'
                                        */
  real_T T_e11_Value_c1;               /* Expression: 1
                                        * '<S57>/T_e11'
                                        */
  real_T T_e21_Value_a;                /* Expression: 0
                                        * '<S57>/T_e21'
                                        */
  real_T l_y1_Value_j;                 /* Expression: 0.055
                                        * '<S57>/l_y1'
                                        */
  real_T T_e12_Value_iv;               /* Expression: 0
                                        * '<S57>/T_e12'
                                        */
  real_T T_e22_Value_on;               /* Expression: 1
                                        * '<S57>/T_e22'
                                        */
  real_T l_x1_Value_f;                 /* Expression: 0.425
                                        * '<S57>/l_x1'
                                        */
  real_T l_x1_Gain_o;                  /* Expression: -1
                                        * '<S57>/-l_x1'
                                        */
  real_T T_e13_Value_i;                /* Expression: 1
                                        * '<S57>/T_e13'
                                        */
  real_T T_e23_Value_k;                /* Expression: 0
                                        * '<S57>/T_e23'
                                        */
  real_T l_y2_Value_j;                 /* Expression: 0.055
                                        * '<S57>/l_y2'
                                        */
  real_T l_y2_Gain_p;                  /* Expression: -1
                                        * '<S57>/-l_y2'
                                        */
  real_T T_e14_Value_g;                /* Expression: 0
                                        * '<S57>/T_e14'
                                        */
  real_T T_e24_Value_b;                /* Expression: 1
                                        * '<S57>/T_e24'
                                        */
  real_T l_x2_Value_p;                 /* Expression: 0.425
                                        * '<S57>/l_x2'
                                        */
  real_T l_x2_Gain_d;                  /* Expression: -1
                                        * '<S57>/-l_x2'
                                        */
  real_T T_e15_Value_j;                /* Expression: 0
                                        * '<S57>/T_e15'
                                        */
  real_T T_e25_Value_n;                /* Expression: 1
                                        * '<S57>/T_e25'
                                        */
  real_T l_x3_Value_n;                 /* Expression: 0.425
                                        * '<S57>/l_x3'
                                        */
  real_T K_e1_hil_Value;               /* Expression: 1
                                        * '<S55>/K_e1_hil'
                                        */
  real_T GainK_e1_hil_Gain;            /* Expression: 1
                                        * '<S55>/Gain K_e1_hil'
                                        */
  real_T Constant41_Value;             /* Expression: 0
                                        * '<S55>/Constant41'
                                        */
  real_T K_e2_hil_Value;               /* Expression: 1
                                        * '<S55>/K_e2_hil'
                                        */
  real_T GainK_e2_hil_Gain;            /* Expression: 1
                                        * '<S55>/Gain K_e2_hil'
                                        */
  real_T K_e3_hil_Value;               /* Expression: 1
                                        * '<S55>/K_e3_hil'
                                        */
  real_T GainK_e3_hil_Gain;            /* Expression: 1
                                        * '<S55>/Gain K_e3_hil'
                                        */
  real_T K_e4_hil_Value;               /* Expression: 1
                                        * '<S55>/K_e4_hil'
                                        */
  real_T GainK_e4_hil_Gain;            /* Expression: 1
                                        * '<S55>/Gain K_e4_hil'
                                        */
  real_T K_e5_hil_Value;               /* Expression: 1
                                        * '<S55>/K_e5_hil'
                                        */
  real_T GainK_e5_hil_Gain;            /* Expression: 1
                                        * '<S55>/Gain K_e5_hil'
                                        */
  real_T sampletime_WtEt;              /* Computed Parameter: WtEt
                                        * '<S56>/sample time'
                                        */
  real_T DelayInput2_X0;               /* Expression: 0
                                        * '<S56>/Delay Input2'
                                        */
  real_T R31_Value;                    /* Expression: 0
                                        * '<S52>/R31'
                                        */
  real_T R32_Value;                    /* Expression: 0
                                        * '<S52>/R32'
                                        */
  real_T R13_Value;                    /* Expression: 0
                                        * '<S52>/R13'
                                        */
  real_T R23_Value;                    /* Expression: 0
                                        * '<S52>/R23'
                                        */
  real_T R33_Value;                    /* Expression: 1
                                        * '<S52>/R33'
                                        */
  real_T eta_surge_hil_Gain;           /* Expression: 1
                                        * '<S34>/eta_surge_hil'
                                        */
  real_T eta_sway_hil_Gain;            /* Expression: 1
                                        * '<S34>/eta_sway_hil'
                                        */
  real_T eta_yaw_hil_Gain;             /* Expression: 1
                                        * '<S34>/eta_yaw_hil'
                                        */
  real_T etadot_surge_hil_Gain;        /* Expression: 1
                                        * '<S34>/etadot_surge_hil'
                                        */
  real_T etadot_sway_hil_Gain;         /* Expression: 1
                                        * '<S34>/etadot_sway_hil'
                                        */
  real_T etadot_yaw_hil_Gain;          /* Expression: 1
                                        * '<S34>/etadot_yaw_hil'
                                        */
  real_T nu_surge_hil_Gain;            /* Expression: 1
                                        * '<S34>/nu_surge_hil'
                                        */
  real_T nu_sway_hil_Gain;             /* Expression: 1
                                        * '<S34>/nu_sway_hil'
                                        */
  real_T nu_yaw_hil_Gain;              /* Expression: 1
                                        * '<S34>/nu_yaw_hil'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_LgV2 {
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
    real_T odeY[27];
    real_T odeF[3][27];
    ODE3_IntgData intgData;
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
extern Parameters_LgV2 LgV2_P;

/* Block signals (auto storage) */
extern BlockIO_LgV2 LgV2_B;

/* Continuous states (auto storage) */
extern ContinuousStates_LgV2 LgV2_X;

/* Block states (auto storage) */
extern D_Work_LgV2 LgV2_DWork;

/* Model entry point functions */
extern void LgV2_initialize(boolean_T firstTime);
extern void LgV2_output(int_T tid);
extern void LgV2_update(int_T tid);
extern void LgV2_terminate(void);

/* Real-time Model object */
extern RT_MODEL_LgV2 *LgV2_M;

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
 * '<Root>' : LgV2
 * '<S1>'   : LgV2/Control Systems
 * '<S2>'   : LgV2/Guidance Systems
 * '<S3>'   : LgV2/HMI
 * '<S4>'   : LgV2/Naviagation Systems
 * '<S5>'   : LgV2/Plants
 * '<S6>'   : LgV2/Control Systems/Accuracy Control
 * '<S7>'   : LgV2/Control Systems/DP control
 * '<S8>'   : LgV2/Control Systems/Joystick Control
 * '<S9>'   : LgV2/Control Systems/Manual Thrust control
 * '<S10>'  : LgV2/Control Systems/if DP Control Mode
 * '<S11>'  : LgV2/Control Systems/DP control/DP controller
 * '<S12>'  : LgV2/Control Systems/DP control/K_e
 * '<S13>'  : LgV2/Control Systems/DP control/Passive DP wave filter1
 * '<S14>'  : LgV2/Control Systems/DP control/T_e
 * '<S15>'  : LgV2/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1
 * '<S16>'  : LgV2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]
 * '<S17>'  : LgV2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1
 * '<S18>'  : LgV2/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1
 * '<S19>'  : LgV2/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw
 * '<S20>'  : LgV2/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1
 * '<S21>'  : LgV2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]
 * '<S22>'  : LgV2/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1
 * '<S23>'  : LgV2/Control Systems/Joystick Control/K_e
 * '<S24>'  : LgV2/Control Systems/Joystick Control/T_e
 * '<S25>'  : LgV2/Guidance Systems/DP
 * '<S26>'  : LgV2/HMI/Accuracy control
 * '<S27>'  : LgV2/HMI/DP input
 * '<S28>'  : LgV2/HMI/PS3 input
 * '<S29>'  : LgV2/HMI/DP input/Degrees to Radians
 * '<S30>'  : LgV2/HMI/PS3 input/PS3 signals
 * '<S31>'  : LgV2/Naviagation Systems/Qualisys 6 DOF
 * '<S32>'  : LgV2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix
 * '<S33>'  : LgV2/Plants/CSE1
 * '<S34>'  : LgV2/Plants/Linear Simulator
 * '<S35>'  : LgV2/Plants/CSE1/Bow Thruster
 * '<S36>'  : LgV2/Plants/CSE1/K_e
 * '<S37>'  : LgV2/Plants/CSE1/T_e
 * '<S38>'  : LgV2/Plants/CSE1/Voith Schneider Propeller
 * '<S39>'  : LgV2/Plants/CSE1/Bow Thruster/Saturation Dynamic
 * '<S40>'  : LgV2/Plants/CSE1/Bow Thruster/Saturation Dynamic1
 * '<S41>'  : LgV2/Plants/CSE1/Bow Thruster/Saturation Dynamic2
 * '<S42>'  : LgV2/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Port
 * '<S43>'  : LgV2/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Starboard
 * '<S44>'  : LgV2/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port
 * '<S45>'  : LgV2/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard
 * '<S46>'  : LgV2/Plants/Linear Simulator/Vessel Dynamics
 * '<S47>'  : LgV2/Plants/Linear Simulator/u to tau
 * '<S48>'  : LgV2/Plants/Linear Simulator/Vessel Dynamics/D_L
 * '<S49>'  : LgV2/Plants/Linear Simulator/Vessel Dynamics/Initial eta
 * '<S50>'  : LgV2/Plants/Linear Simulator/Vessel Dynamics/Initial nu
 * '<S51>'  : LgV2/Plants/Linear Simulator/Vessel Dynamics/M_inv
 * '<S52>'  : LgV2/Plants/Linear Simulator/Vessel Dynamics/R(psi)
 * '<S53>'  : LgV2/Plants/Linear Simulator/u to tau/Cartesian to Polar Port
 * '<S54>'  : LgV2/Plants/Linear Simulator/u to tau/Cartesian to Polar Stbd
 * '<S55>'  : LgV2/Plants/Linear Simulator/u to tau/K_e
 * '<S56>'  : LgV2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic
 * '<S57>'  : LgV2/Plants/Linear Simulator/u to tau/T_e
 * '<S58>'  : LgV2/Plants/Linear Simulator/u to tau/Rate Limiter Dynamic/Saturation Dynamic
 */
#endif                                 /* RTW_HEADER_LgV2_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_LgV2
#ifdef RVE
#ifdef MULTITASKING

Parameters_LgV2 rtParameter[NUMST+!TID01EQ];

#define LgV2_P                         (*param_lookup[tid][READSIDE])

Parameters_LgV2 *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_LgV2 rtParameter[2];

#define LgV2_P                         rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
