/*
 * LgV2.h
 *
 * Real-Time Workshop code generation for Simulink model "LgV2.mdl".
 *
 * Model Version              : 1.30
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Mon Mar 17 14:01:41 2014
 *
 * Target selection: nidll_vxworks.tlc
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
#include "rt_look.h"
#include "rt_look2d_normal.h"
#include "rt_matrixlib.h"
#include "rt_pow_snf.h"
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
  real_T QTMIn[9];                     /* '<S199>/QTM In' */
  real_T QTMIn2Error;                  /* '<S199>/QTM In2 Error' */
  real_T QTMIn9Residual;               /* '<S199>/QTM In9 Residual' */
  real_T QTMIn3;                       /* '<S199>/QTM In3' */
  real_T mm2mx;                        /* '<S199>/mm2m x' */
  real_T QTMIn4;                       /* '<S199>/QTM In4' */
  real_T mm2my;                        /* '<S199>/mm2m y' */
  real_T QTMIn6;                       /* '<S199>/QTM In6' */
  real_T d2ryaw;                       /* '<S199>/d2r yaw' */
  real_T Derivative1[3];               /* '<S199>/Derivative1' */
  real_T EtadotSwitch[3];              /* '<S4>/Etadot Switch' */
  real_T etadot_surge;                 /* '<S4>/etadot_surge' */
  real_T etadot_sway;                  /* '<S4>/etadot_sway' */
  real_T etadot_yaw;                   /* '<S4>/etadot_yaw' */
  real_T EtaSwitch[3];                 /* '<S4>/Eta Switch' */
  real_T eta_surge;                    /* '<S4>/eta_surge' */
  real_T eta_sway;                     /* '<S4>/eta_sway' */
  real_T eta_yaw;                      /* '<S4>/eta_yaw' */
  real_T QTMIn8;                       /* '<S199>/QTM In8' */
  real_T d2rroll;                      /* '<S199>/d2r roll' */
  real_T QTMIn7;                       /* '<S199>/QTM In7' */
  real_T d2rpitch;                     /* '<S199>/d2r pitch' */
  real_T sintheta[3];                  /* '<S200>/sin(theta)' */
  real_T costheta[3];                  /* '<S200>/cos(theta)' */
  real_T R11;                          /* '<S200>/R11' */
  real_T R21;                          /* '<S200>/R21 ' */
  real_T R31;                          /* '<S200>/R31 ' */
  real_T R12;                          /* '<S200>/R12' */
  real_T R22;                          /* '<S200>/R22' */
  real_T R32;                          /* '<S200>/R32' */
  real_T R13;                          /* '<S200>/R13' */
  real_T R23;                          /* '<S200>/R23' */
  real_T R33;                          /* '<S200>/R33' */
  real_T Reshape9x13x3[9];             /* '<S200>/Reshape 9x1->3x3' */
  real_T MatrixConcatenate2[36];       /* '<S199>/Matrix Concatenate2' */
  real_T QTMIn5;                       /* '<S199>/QTM In5' */
  real_T mm2mz;                        /* '<S199>/mm2m z' */
  real_T Derivative[6];                /* '<S199>/Derivative' */
  real_T Product[6];                   /* '<S199>/Product' */
  real_T NuSwitch[3];                  /* '<S4>/Nu Switch' */
  real_T nu_surge;                     /* '<S4>/nu_surge' */
  real_T nu_sway;                      /* '<S4>/nu_sway' */
  real_T nu_yaw;                       /* '<S4>/nu_yaw' */
  real_T eta_dDPN;                     /* '<S113>/eta_d DP N' */
  real_T eta_dDPE;                     /* '<S113>/eta_d DP E' */
  real_T Gain1;                        /* '<S198>/Gain1' */
  real_T eta_dDPPsi;                   /* '<S113>/eta_d DP Psi' */
  real_T q_x_0;                        /* '<S95>/q_x_0' */
  real_T q_y_0;                        /* '<S95>/q_y_0' */
  real_T Integrator[2];                /* '<S52>/Integrator' */
  real_T x_2x_1;                       /* '<S187>/x_2 - x_1' */
  real_T y_2y_1;                       /* '<S187>/y_2 - y_1' */
  real_T TmpHiddenBufferAtProductInport2[2];/* 'synthesized block' */
  real_T Product_g[2];                 /* '<S182>/Product' */
  real_T s_0;                          /* '<S52>/s_0' */
  real_T Integrator1;                  /* '<S52>/Integrator1' */
  real_T Product2;                     /* '<S176>/Product2' */
  real_T sins;                         /* '<S176>/sin(s)' */
  real_T Product_m;                    /* '<S176>/Product' */
  real_T Gain;                         /* '<S176>/Gain' */
  real_T coss;                         /* '<S176>/cos(s)' */
  real_T Product1;                     /* '<S176>/Product1' */
  real_T TmpHiddenBufferAtProductInpor_d[2];/* 'synthesized block' */
  real_T Subtract;                     /* '<S182>/Subtract' */
  real_T Product1_c[2];                /* '<S182>/Product1' */
  real_T Add[2];                       /* '<S182>/Add' */
  real_T TrigonometricFunction;        /* '<S119>/Trigonometric Function' */
  real_T Gain_b;                       /* '<S124>/Gain' */
  real_T Saturation;                   /* '<S122>/Saturation' */
  real_T Sign;                         /* '<S122>/Sign' */
  real_T Gain_bx;                      /* '<S122>/Gain' */
  real_T Sum1;                         /* '<S122>/Sum1' */
  real_T MathFunction;                 /* '<S122>/Math Function' */
  real_T Sum;                          /* '<S122>/Sum' */
  real_T Gain1_f;                      /* '<S123>/Gain1' */
  real_T Gain_n;                       /* '<S157>/Gain' */
  real_T Saturation_h;                 /* '<S153>/Saturation' */
  real_T Sign_c;                       /* '<S153>/Sign' */
  real_T Gain_m;                       /* '<S153>/Gain' */
  real_T Sum1_c;                       /* '<S153>/Sum1' */
  real_T MathFunction_o;               /* '<S153>/Math Function' */
  real_T Sum_g;                        /* '<S153>/Sum' */
  real_T Gain1_c;                      /* '<S156>/Gain1' */
  real_T MathFunction_b[4];            /* '<S163>/Math Function' */
  real_T x_2x_1_m;                     /* '<S186>/x_2 - x_1' */
  real_T x_2x_1s;                      /* '<S186>/(x_2 - x_1) * s' */
  real_T x_2x_1sx_1;                   /* '<S186>/(x_2 - x_1) * s + x_1' */
  real_T y_2y_1_l;                     /* '<S186>/y_2 - y_1' */
  real_T y_2y_1s;                      /* '<S186>/(y_2 - y_1) * s' */
  real_T y_2y_1sy_1;                   /* '<S186>/(y_2 - y_1) * s + y_1' */
  real_T p_d1a[2];                     /* '<S181>/p_d1 *a' */
  real_T Product2_c;                   /* '<S175>/Product2' */
  real_T coss_d;                       /* '<S175>/cos(s)' */
  real_T Product_k;                    /* '<S175>/Product' */
  real_T Add_m;                        /* '<S175>/Add' */
  real_T sins_i;                       /* '<S175>/sin(s)' */
  real_T Product1_n;                   /* '<S175>/Product1' */
  real_T Add1;                         /* '<S175>/Add1' */
  real_T a;                            /* '<S181>/1 - a' */
  real_T p_d21a[2];                    /* '<S181>/p_d2 * (1- a )' */
  real_T Add_e[2];                     /* '<S181>/Add' */
  real_T Switch;                       /* '<S190>/Switch' */
  real_T Switch2;                      /* '<S190>/Switch2' */
  real_T Switch_m;                     /* '<S191>/Switch' */
  real_T Switch2_h;                    /* '<S191>/Switch2' */
  real_T qp_d[2];                      /* '<S130>/q - p_d' */
  real_T epsilon[2];                   /* '<S130>/epsilon' */
  real_T MultiportSelector;            /* '<S130>/Multiport Selector' */
  real_T TrigonometricFunction_f;      /* '<S147>/Trigonometric Function' */
  real_T Gain_h;                       /* '<S159>/Gain' */
  real_T Saturation_i;                 /* '<S154>/Saturation' */
  real_T Sign_i;                       /* '<S154>/Sign' */
  real_T Gain_g;                       /* '<S154>/Gain' */
  real_T Sum1_f;                       /* '<S154>/Sum1' */
  real_T MathFunction_p;               /* '<S154>/Math Function' */
  real_T Sum_p;                        /* '<S154>/Sum' */
  real_T Gain1_h;                      /* '<S158>/Gain1' */
  real_T Subtract_a;                   /* '<S147>/Subtract' */
  real_T Gain_k;                       /* '<S161>/Gain' */
  real_T Saturation_c;                 /* '<S155>/Saturation' */
  real_T Sign_d;                       /* '<S155>/Sign' */
  real_T Gain_ki;                      /* '<S155>/Gain' */
  real_T Sum1_a;                       /* '<S155>/Sum1' */
  real_T MathFunction_bn;              /* '<S155>/Math Function' */
  real_T Sum_o;                        /* '<S155>/Sum' */
  real_T Gain1_o;                      /* '<S160>/Gain1' */
  real_T VectorConcatenate[3];         /* '<S125>/Vector Concatenate' */
  real_T q_x;                          /* '<S2>/q_x' */
  real_T q_y;                          /* '<S2>/q_y' */
  real_T psi_los;                      /* '<S2>/psi_los' */
  real_T pathx_d;                      /* '<S2>/path x_d' */
  real_T pathy_d;                      /* '<S2>/path y_d' */
  real_T pathpsi_d;                    /* '<S2>/path psi_d' */
  real_T MathFunction_i[2];            /* '<S189>/Math Function' */
  real_T Product_p;                    /* '<S188>/Product' */
  real_T sqrt_p;                       /* '<S188>/sqrt' */
  real_T Product_ka;                   /* '<S185>/Product' */
  real_T MathFunction_h[2];            /* '<S180>/Math Function' */
  real_T Product_b;                    /* '<S179>/Product' */
  real_T sqrt_h;                       /* '<S179>/sqrt' */
  real_T Subtract_d;                   /* '<S185>/Subtract' */
  real_T Product1_j;                   /* '<S185>/Product1' */
  real_T Add_n;                        /* '<S185>/Add' */
  real_T Divide;                       /* '<S192>/Divide' */
  real_T ypositionofleftanalogstick11; /* '<S8>/ScalingLY' */
  real_T u_1;                          /* '<S9>/PS3 u_1' */
  real_T xpositionofleftanalogstick11; /* '<S8>/ScalingLX' */
  real_T u_2;                          /* '<S9>/PS3 u_2' */
  real_T ypositionofrightanalogstick11;/* '<S8>/ScalingRY' */
  real_T u_3;                          /* '<S9>/PS3 u_3' */
  real_T xpositionofrightanalogstick11;/* '<S8>/Scaling_RX' */
  real_T u_4;                          /* '<S9>/PS3 u_4' */
  real_T BowThrusterdirection;         /* '<S9>/Add' */
  real_T u_5;                          /* '<S9>/PS3 u_5' */
  real_T l_x1;                         /* '<S37>/-l_x1' */
  real_T l_y2;                         /* '<S37>/-l_y2' */
  real_T l_x2;                         /* '<S37>/-l_x2' */
  real_T x5[15];                       /* '<S37>/3x5' */
  real_T Pseudoinverse[15];            /* '<S16>/Pseudoinverse' */
  real_T psi;                          /* '<S10>/yaw angle' */
  real_T Saturation_ha;                /* '<S14>/Saturation' */
  real_T Sign_a;                       /* '<S14>/Sign' */
  real_T Gain_j;                       /* '<S14>/Gain' */
  real_T Sum1_i;                       /* '<S14>/Sum1' */
  real_T MathFunction_ij;              /* '<S14>/Math Function' */
  real_T Sum_b;                        /* '<S14>/Sum' */
  real_T regulationerror[3];           /* '<S10>/Sum2' */
  real_T Saturation_m;                 /* '<S13>/Saturation' */
  real_T Sign_j;                       /* '<S13>/Sign' */
  real_T Gain_a;                       /* '<S13>/Gain' */
  real_T Sum1_p;                       /* '<S13>/Sum1' */
  real_T MathFunction_d;               /* '<S13>/Math Function' */
  real_T Sum_j;                        /* '<S13>/Sum' */
  real_T Row1;                         /* '<S12>/Row1' */
  real_T Row2;                         /* '<S12>/Row2' */
  real_T Row3;                         /* '<S12>/Row3' */
  real_T TmpHiddenBufferAtKpInport1[3];/* '<S10>/Transposed rotation  matrix in yaw1' */
  real_T Kp[3];                        /* '<S10>/Kp' */
  real_T K_p_surge_scale;              /* '<S10>/K_p_surge_scale' */
  real_T K_p_sway_scale;               /* '<S10>/K_p_sway_scale' */
  real_T K_p_yaw_scale;                /* '<S10>/K_p_yaw_scale' */
  real_T Integrator_g[3];              /* '<S10>/Integrator' */
  real_T Ki[3];                        /* '<S10>/Ki' */
  real_T K_i_surge_scale;              /* '<S10>/K_i_surge_scale' */
  real_T K_i_sway_scale;               /* '<S10>/K_i_sway_scale' */
  real_T K_i_yaw_scale;                /* '<S10>/K_i_yaw_scale' */
  real_T Sum3[3];                      /* '<S10>/Sum3' */
  real_T TmpHiddenBufferAtKdInport1[3];/* 'synthesized block' */
  real_T Kd[3];                        /* '<S10>/Kd' */
  real_T K_d_surge_scale;              /* '<S10>/K_d_surge_scale' */
  real_T K_d_sway_scale;               /* '<S10>/K_d_sway_scale' */
  real_T K_d_yaw_scale;                /* '<S10>/K_d_yaw_scale' */
  real_T Sum1_j[3];                    /* '<S10>/Sum1' */
  real_T Product_o[5];                 /* '<S16>/Product' */
  real_T DeadZone;                     /* '<S17>/Dead Zone' */
  real_T f_10;                         /* '<S17>/f_1 < 0' */
  real_T f_10_l;                       /* '<S17>/f_1 > 0' */
  real_T MultiportSwitch;              /* '<S17>/Multiport Switch' */
  real_T DeadZone_j;                   /* '<S18>/Dead Zone' */
  real_T f_20;                         /* '<S18>/f_2 < 0' */
  real_T f_20_l;                       /* '<S18>/f_2 > 0' */
  real_T MultiportSwitch_h;            /* '<S18>/Multiport Switch' */
  real_T DeadZone_m;                   /* '<S19>/Dead Zone' */
  real_T f_30;                         /* '<S19>/f_3 < 0' */
  real_T f_30_o;                       /* '<S19>/f_3 > 0' */
  real_T MultiportSwitch_c;            /* '<S19>/Multiport Switch' */
  real_T DeadZone_g;                   /* '<S20>/Dead Zone' */
  real_T f_40;                         /* '<S20>/f_4 < 0' */
  real_T f_40_f;                       /* '<S20>/f_4 > 0' */
  real_T MultiportSwitch_cc;           /* '<S20>/Multiport Switch' */
  real_T DeadZone_f;                   /* '<S21>/Dead Zone' */
  real_T f_50;                         /* '<S21>/f_5 < 0' */
  real_T f_50_g;                       /* '<S21>/f_5 > 0' */
  real_T MultiportSwitch_hs;           /* '<S21>/Multiport Switch' */
  real_T Saturation_p[5];              /* '<S6>/Saturation' */
  real_T l_x1_d;                       /* '<S93>/-l_x1' */
  real_T l_y2_h;                       /* '<S93>/-l_y2' */
  real_T l_x2_m;                       /* '<S93>/-l_x2' */
  real_T x5_a[15];                     /* '<S93>/3x5' */
  real_T Pseudoinverse_j[15];          /* '<S72>/Pseudoinverse' */
  real_T R11_c;                        /* '<S47>/R11' */
  real_T R21_m;                        /* '<S47>/R21' */
  real_T R12_f;                        /* '<S47>/R12' */
  real_T u;                            /* '<S47>/-1' */
  real_T R22_p;                        /* '<S47>/R22' */
  real_T Rpsi[9];                      /* '<S47>/R(psi)' */
  real_T MathFunction_dr[9];           /* '<S48>/Math Function' */
  real_T x3[9];                        /* '<S44>/3x3' */
  real_T Integrator_k[3];              /* '<S42>/Integrator' */
  real_T Product_c[3];                 /* '<S40>/Product' */
  real_T x3_d[9];                      /* '<S43>/3x3' */
  real_T u_n;                          /* '<S40>/4' */
  real_T Divide_g;                     /* '<S40>/Divide' */
  real_T Add1_j[9];                    /* '<S40>/Add1' */
  real_T Rpsi_n[9];                    /* '<S45>/R(psi)' */
  real_T Product_bs[9];                /* '<S54>/Product' */
  real_T Subtract_dr[9];               /* '<S54>/Subtract' */
  real_T Gain_c;                       /* '<S105>/Gain' */
  real_T Saturation_cg;                /* '<S103>/Saturation' */
  real_T Sign_g;                       /* '<S103>/Sign' */
  real_T Gain_je;                      /* '<S103>/Gain' */
  real_T Sum1_e;                       /* '<S103>/Sum1' */
  real_T MathFunction_f;               /* '<S103>/Math Function' */
  real_T Sum_d;                        /* '<S103>/Sum' */
  real_T Gain1_l;                      /* '<S104>/Gain1' */
  real_T Subtract_f[3];                /* '<S58>/Subtract' */
  real_T Gain_bu;                      /* '<S108>/Gain' */
  real_T Saturation_d;                 /* '<S106>/Saturation' */
  real_T Sign_g2;                      /* '<S106>/Sign' */
  real_T Gain_ag;                      /* '<S106>/Gain' */
  real_T Sum1_h;                       /* '<S106>/Sum1' */
  real_T MathFunction_od;              /* '<S106>/Math Function' */
  real_T Sum_e;                        /* '<S106>/Sum' */
  real_T Gain1_m;                      /* '<S107>/Gain1' */
  real_T TmpHiddenBufferAtProductInpor_a[3];/* '<S58>/heading to pipi1' */
  real_T Product_i[3];                 /* '<S58>/Product' */
  real_T Product1_ce[3];               /* '<S54>/Product1' */
  real_T f_qx;                         /* '<S132>/f_qx' */
  real_T f_qy;                         /* '<S132>/f_qy' */
  real_T TmpHiddenBufferAtProductInport1[2];/* 'synthesized block' */
  real_T Product_g5[2];                /* '<S132>/Product' */
  real_T Delta2;                       /* '<S148>/Delta^2' */
  real_T epsilon_n2;                   /* '<S148>/epsilon_n^2' */
  real_T Add_o;                        /* '<S148>/Add' */
  real_T Divide_gx;                    /* '<S148>/Divide' */
  real_T MultiportSelector1[2];        /* '<S130>/Multiport Selector1' */
  real_T Product_n[2];                 /* '<S148>/Product' */
  real_T u_o[2];                       /* '<S148>/-1' */
  real_T VectorConcatenate_e[3];       /* '<S60>/Vector Concatenate' */
  real_T Product_a[2];                 /* '<S184>/Product' */
  real_T Product2_b;                   /* '<S178>/Product2' */
  real_T sins3;                        /* '<S178>/sin(s)3' */
  real_T MathFunction_l;               /* '<S178>/Math Function' */
  real_T Product_nx;                   /* '<S178>/Product' */
  real_T coss3;                        /* '<S178>/cos(s)3' */
  real_T Product1_o;                   /* '<S178>/Product1' */
  real_T Gain_d;                       /* '<S178>/Gain' */
  real_T Subtract_j;                   /* '<S184>/Subtract' */
  real_T Product1_m[2];                /* '<S184>/Product1' */
  real_T Add_mw[2];                    /* '<S184>/Add' */
  real_T x_dsy_ds2;                    /* '<S120>/x_d^s * y_d^s^2' */
  real_T x_ds2y_ds;                    /* '<S120>/x_d^s^2 * y_d^s' */
  real_T x_dsy_ds2x_ds2y_ds;           /* '<S120>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
  real_T x_ds2;                        /* '<S120>/( x_d^s )^2' */
  real_T y_ds2;                        /* '<S120>/( y_d^s )^2' */
  real_T x_ds2y_ds2;                   /* '<S120>/( x_d^s )^2 + ( y_d^s )^2' */
  real_T Divide_h;                     /* '<S120>/Divide' */
  real_T Delta2_h;                     /* '<S151>/Delta^2' */
  real_T epsilon_n2_c;                 /* '<S151>/epsilon_n^2' */
  real_T Add_no;                       /* '<S151>/Add' */
  real_T Divide_a;                     /* '<S151>/Divide' */
  real_T MathFunction_ii[4];           /* '<S167>/Math Function' */
  real_T Product_gx[2];                /* '<S169>/Product' */
  real_T Product1_p[2];                /* '<S169>/Product1' */
  real_T Subtract1[2];                 /* '<S169>/Subtract1' */
  real_T MultiportSelector2;           /* '<S130>/Multiport Selector2' */
  real_T Product_ay;                   /* '<S151>/Product' */
  real_T Subtract_h;                   /* '<S151>/Subtract' */
  real_T epsilon_n2_i;                 /* '<S136>/epsilon_n^2' */
  real_T Delta2_b;                     /* '<S136>/Delta^2' */
  real_T Add_mh;                       /* '<S136>/Add' */
  real_T sqrt_c;                       /* '<S136>/sqrt' */
  real_T Divide_f;                     /* '<S136>/Divide' */
  real_T Product_bv;                   /* '<S136>/Product' */
  real_T MathFunction_p1[2];           /* '<S143>/Math Function' */
  real_T Divide_k[2];                  /* '<S140>/Divide' */
  real_T Subtract_e[2];                /* '<S128>/Subtract' */
  real_T Product_kj;                   /* '<S140>/Product' */
  real_T Gain_c0;                      /* '<S140>/Gain' */
  real_T Subtract_l;                   /* '<S136>/Subtract' */
  real_T VectorConcatenate_eb[3];      /* '<S66>/Vector Concatenate' */
  real_T Add_c[3];                     /* '<S54>/Add' */
  real_T Product2_p[3];                /* '<S54>/Product2' */
  real_T Sum_p5[3];                    /* '<S54>/Sum' */
  real_T Subtract_di[3];               /* '<S59>/Subtract' */
  real_T Product1_a[3];                /* '<S40>/Product1' */
  real_T X_u;                          /* '<S70>/-X_u' */
  real_T Y_v;                          /* '<S70>/-Y_v' */
  real_T N_v;                          /* '<S70>/-N_v' */
  real_T Y_vr;                         /* '<S70>/-Y_vr' */
  real_T N_r;                          /* '<S70>/-N_r' */
  real_T LinearDampningmatrix[9];      /* '<S70>/Linear Dampning matrix' */
  real_T Product2_o[3];                /* '<S40>/Product2' */
  real_T M_11;                         /* '<S46>/M_11' */
  real_T M_22;                         /* '<S46>/M_22' */
  real_T mx_g;                         /* '<S46>/m x_g' */
  real_T M_32;                         /* '<S46>/M_32' */
  real_T M_23;                         /* '<S46>/M_23' */
  real_T M_33;                         /* '<S46>/M_33' */
  real_T x3_n[9];                      /* '<S46>/3x3' */
  real_T Product1_e[9];                /* '<S57>/Product1' */
  real_T Add3[9];                      /* '<S57>/Add3' */
  real_T S12;                          /* '<S49>/S12' */
  real_T Sr[9];                        /* '<S49>/S(r)' */
  real_T MathFunction_oi[9];           /* '<S50>/Math Function' */
  real_T Product_gv[3];                /* '<S57>/Product' */
  real_T Add_ot[3];                    /* '<S57>/Add' */
  real_T Product2_i[3];                /* '<S57>/Product2' */
  real_T Add1_o[3];                    /* '<S57>/Add1' */
  real_T Product3[3];                  /* '<S57>/Product3' */
  real_T TrigonometricFunction_b;      /* '<S135>/Trigonometric Function' */
  real_T TrigonometricFunction1;       /* '<S135>/Trigonometric Function1' */
  real_T Derivative_j;                 /* '<S118>/Derivative' */
  real_T Product_kt[2];                /* '<S135>/Product' */
  real_T VectorConcatenate_m[3];       /* '<S63>/Vector Concatenate' */
  real_T epsilon_n2_cp;                /* '<S139>/epsilon_n^2' */
  real_T Delta2_n;                     /* '<S139>/Delta^2' */
  real_T Add_g;                        /* '<S139>/Add' */
  real_T sqrt_n;                       /* '<S139>/sqrt' */
  real_T Divide_f1;                    /* '<S139>/Divide' */
  real_T Divide_fp;                    /* '<S194>/Divide' */
  real_T Product_l;                    /* '<S139>/Product' */
  real_T VectorConcatenate_c[3];       /* '<S69>/Vector Concatenate' */
  real_T Add2[3];                      /* '<S57>/Add2' */
  real_T Product4[3];                  /* '<S57>/Product4' */
  real_T Sum_m[3];                     /* '<S57>/Sum' */
  real_T Product4_h[3];                /* '<S40>/Product4' */
  real_T Product1_h[9];                /* '<S55>/Product1' */
  real_T Add_e3[9];                    /* '<S55>/Add' */
  real_T MatrixConcatenate[6];         /* '<S125>/Matrix Concatenate' */
  real_T Product3_j[6];                /* '<S55>/Product3' */
  real_T TrigonometricFunction1_h;     /* '<S133>/Trigonometric Function1' */
  real_T Gain_ah;                      /* '<S133>/Gain' */
  real_T Product1_aq[2];               /* '<S133>/Product1' */
  real_T TrigonometricFunction_n;      /* '<S133>/Trigonometric Function' */
  real_T Product2_c1[2];               /* '<S133>/Product2' */
  real_T MatrixConcatenate_b[4];       /* '<S133>/Matrix Concatenate' */
  real_T Product_pg[4];                /* '<S133>/Product' */
  real_T MathFunction_j[2];            /* '<S64>/Math Function' */
  real_T Product2_om;                  /* '<S149>/Product2' */
  real_T MathFunction_jw[2];           /* '<S149>/Math Function' */
  real_T Product3_k[4];                /* '<S149>/Product3' */
  real_T Product4_b[4];                /* '<S149>/Product4' */
  real_T u_c[4];                       /* '<S149>/2' */
  real_T Delta2_p;                     /* '<S149>/Delta^2' */
  real_T epsilon_n2_f;                 /* '<S149>/epsilon_n^2' */
  real_T Add_gr;                       /* '<S149>/Add' */
  real_T u_e;                          /* '<S149>/( )^2' */
  real_T Divide_o[4];                  /* '<S149>/Divide' */
  real_T Product1_ej[4];               /* '<S149>/Product1' */
  real_T Divide1[4];                   /* '<S149>/Divide1' */
  real_T Subtract_di2[4];              /* '<S149>/Subtract' */
  real_T MathFunction_g[4];            /* '<S65>/Math Function' */
  real_T Product_nz[2];                /* '<S61>/Product' */
  real_T Product1_my[2];               /* '<S61>/Product1' */
  real_T Add_mg[2];                    /* '<S61>/Add' */
  real_T MatrixConcatenate_f[6];       /* '<S61>/Matrix Concatenate' */
  real_T Product_k3[2];                /* '<S150>/Product' */
  real_T u_i[2];                       /* '<S150>/2' */
  real_T Delta2_o;                     /* '<S150>/Delta^2' */
  real_T epsilon_n2_a;                 /* '<S150>/epsilon_n^2' */
  real_T Add_e2;                       /* '<S150>/Add' */
  real_T u_l;                          /* '<S150>/( )^2' */
  real_T Divide_d[2];                  /* '<S150>/Divide' */
  real_T Product1_d[4];                /* '<S168>/Product1' */
  real_T MultiportSelector3[2];        /* '<S130>/Multiport Selector3' */
  real_T Product1_di[2];               /* '<S150>/Product1' */
  real_T Divide1_b[2];                 /* '<S150>/Divide1' */
  real_T Subtract_m[2];                /* '<S150>/Subtract' */
  real_T Product_i3[2];                /* '<S67>/Product' */
  real_T Product1_f[2];                /* '<S137>/Product1' */
  real_T epsilon_n2_l;                 /* '<S137>/epsilon_n^2' */
  real_T Delta2_g;                     /* '<S137>/Delta^2' */
  real_T Add_g3;                       /* '<S137>/Add' */
  real_T u2;                           /* '<S137>/^3//2' */
  real_T Divide_l[2];                  /* '<S137>/Divide' */
  real_T Product_ly[2];                /* '<S137>/Product' */
  real_T MathFunction_a[2];            /* '<S144>/Math Function' */
  real_T Divide_i[2];                  /* '<S141>/Divide' */
  real_T Product_az[2];                /* '<S141>/Product' */
  real_T Gain_o[2];                    /* '<S141>/Gain' */
  real_T Sum_n[2];                     /* '<S137>/Sum' */
  real_T Product1_oc[2];               /* '<S67>/Product1' */
  real_T Add_j[2];                     /* '<S67>/Add' */
  real_T MatrixConcatenate_k[6];       /* '<S67>/Matrix Concatenate' */
  real_T Add2_d[6];                    /* '<S55>/Add2' */
  real_T Product4_g[6];                /* '<S55>/Product4' */
  real_T Add3_m[6];                    /* '<S55>/Add3' */
  real_T Integrator2[2];               /* '<S52>/Integrator2' */
  real_T Add2_m[2];                    /* '<S40>/Add2' */
  real_T Product5[3];                  /* '<S40>/Product5' */
  real_T Product1_b[9];                /* '<S56>/Product1' */
  real_T Add1_o3[9];                   /* '<S56>/Add1' */
  real_T VectorConcatenate1[3];        /* '<S125>/Vector Concatenate1' */
  real_T Product3_d[3];                /* '<S56>/Product3' */
  real_T TrigonometricFunction1_i;     /* '<S134>/Trigonometric Function1' */
  real_T Gain_f;                       /* '<S134>/Gain' */
  real_T Product1_jn;                  /* '<S134>/Product1' */
  real_T TrigonometricFunction_i;      /* '<S134>/Trigonometric Function' */
  real_T Product2_n;                   /* '<S134>/Product2' */
  real_T TmpHiddenBufferAtProductInpor_i[2];/* 'synthesized block' */
  real_T Product_nxy[2];               /* '<S134>/Product' */
  real_T Product_in;                   /* '<S62>/Product' */
  real_T Product1_nf;                  /* '<S62>/Product1' */
  real_T VectorConcatenate_f[3];       /* '<S62>/Vector Concatenate' */
  real_T Product_h[2];                 /* '<S183>/Product' */
  real_T Product2_f;                   /* '<S177>/Product2' */
  real_T coss_g;                       /* '<S177>/cos(s)' */
  real_T MathFunction_b4;              /* '<S177>/Math Function' */
  real_T Product_mj;                   /* '<S177>/Product' */
  real_T Gain_hu;                      /* '<S177>/Gain' */
  real_T sins_f;                       /* '<S177>/sin(s)' */
  real_T Product1_ok;                  /* '<S177>/Product1' */
  real_T Gain1_o2;                     /* '<S177>/Gain1' */
  real_T Subtract_en;                  /* '<S183>/Subtract' */
  real_T Product1_l[2];                /* '<S183>/Product1' */
  real_T Add_b[2];                     /* '<S183>/Add' */
  real_T x_dsy_ds3;                    /* '<S121>/x_d^s * y_d^s^3 ' */
  real_T x_ds3y_ds;                    /* '<S121>/x_d^s^3 * y_d^s' */
  real_T x_dsy_ds3x_ds3y_ds;           /* '<S121>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
  real_T Product1_a3;                  /* '<S121>/Product1' */
  real_T x_dsx_ds2;                    /* '<S121>/x_d^s * x_d^s^2' */
  real_T y_dsy_ds2;                    /* '<S121>/y_d^s * y_d^s^2' */
  real_T x_dsx_ds2x_ds3y_ds;           /* '<S121>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
  real_T u_m;                          /* '<S121>/+ 2' */
  real_T Product2_i5;                  /* '<S121>/Product2' */
  real_T Subtract_n;                   /* '<S121>/Subtract' */
  real_T x_ds2y_ds22;                  /* '<S121>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
  real_T Divide_kj;                    /* '<S121>/Divide' */
  real_T epsilon_ns2;                  /* '<S152>/(epsilon_n^s)^2' */
  real_T Product_j;                    /* '<S152>/Product' */
  real_T u_d;                          /* '<S152>/2' */
  real_T Delta2_oj;                    /* '<S152>/Delta^2' */
  real_T epsilon_n2_b;                 /* '<S152>/epsilon_n^2' */
  real_T Add_k;                        /* '<S152>/Add' */
  real_T u_p;                          /* '<S152>/( )^2' */
  real_T Divide_p;                     /* '<S152>/Divide' */
  real_T MathFunction_m[4];            /* '<S166>/Math Function' */
  real_T Product_f[4];                 /* '<S170>/Product' */
  real_T Add_i[4];                     /* '<S170>/Add' */
  real_T Product1_co[2];               /* '<S170>/Product1' */
  real_T Product2_px[2];               /* '<S170>/Product2' */
  real_T u_mr[2];                      /* '<S170>/2' */
  real_T Product3_c[2];                /* '<S170>/Product3' */
  real_T Sum_pn[2];                    /* '<S170>/Sum' */
  real_T Gain_dg[2];                   /* '<S170>/Gain' */
  real_T MultiportSelector4;           /* '<S130>/Multiport Selector4' */
  real_T Product1_ns;                  /* '<S152>/Product1' */
  real_T Divide1_p;                    /* '<S152>/Divide1' */
  real_T Sum_f;                        /* '<S152>/Sum' */
  real_T Product_cc;                   /* '<S68>/Product' */
  real_T MathFunction_lq[2];           /* '<S195>/Math Function' */
  real_T Product1_jd;                  /* '<S193>/Product1' */
  real_T p_ds3;                        /* '<S193>/|p_d^s|^3' */
  real_T Divide_iy;                    /* '<S193>/Divide' */
  real_T Product_bn;                   /* '<S193>/Product' */
  real_T Gain_e;                       /* '<S193>/Gain' */
  real_T epsilon_n2_cs;                /* '<S138>/epsilon_n^2' */
  real_T Delta2_i;                     /* '<S138>/Delta^2' */
  real_T Add_es;                       /* '<S138>/Add' */
  real_T MathFunction_jo;              /* '<S138>/Math Function' */
  real_T Divide_j;                     /* '<S138>/Divide' */
  real_T Product1_es;                  /* '<S138>/Product1' */
  real_T Product2_h;                   /* '<S138>/Product2' */
  real_T u2_b;                         /* '<S138>/^3//2' */
  real_T Divide1_d;                    /* '<S138>/Divide1' */
  real_T Product3_a;                   /* '<S138>/Product3' */
  real_T Product1_en;                  /* '<S142>/Product1' */
  real_T MathFunction_c[2];            /* '<S146>/Math Function' */
  real_T Divide2[2];                   /* '<S142>/Divide2' */
  real_T MathFunction_cc[2];           /* '<S145>/Math Function' */
  real_T Product2_im[2];               /* '<S142>/Product2' */
  real_T MathFunction_ak;              /* '<S142>/Math Function' */
  real_T Divide1_be[2];                /* '<S142>/Divide1' */
  real_T Subtract1_c[2];               /* '<S142>/Subtract1' */
  real_T Product_of;                   /* '<S142>/Product' */
  real_T Subtract_nq;                  /* '<S142>/Subtract' */
  real_T Sum_oq;                       /* '<S138>/Sum' */
  real_T Product1_o2;                  /* '<S68>/Product1' */
  real_T VectorConcatenate_p[3];       /* '<S68>/Vector Concatenate' */
  real_T Add2_e[3];                    /* '<S56>/Add2' */
  real_T Product4_a[3];                /* '<S56>/Product4' */
  real_T Add3_l[3];                    /* '<S56>/Add3' */
  real_T Product6[3];                  /* '<S40>/Product6' */
  real_T Sum_gc[3];                    /* '<S40>/Sum' */
  real_T Product_cl[5];                /* '<S72>/Product' */
  real_T DeadZone_h;                   /* '<S73>/Dead Zone' */
  real_T f_10_c;                       /* '<S73>/f_1 < 0' */
  real_T f_10_i;                       /* '<S73>/f_1 > 0' */
  real_T MultiportSwitch_j;            /* '<S73>/Multiport Switch' */
  real_T DeadZone_g1;                  /* '<S74>/Dead Zone' */
  real_T f_20_o;                       /* '<S74>/f_2 < 0' */
  real_T f_20_c;                       /* '<S74>/f_2 > 0' */
  real_T MultiportSwitch_m;            /* '<S74>/Multiport Switch' */
  real_T DeadZone_f2;                  /* '<S75>/Dead Zone' */
  real_T f_30_f;                       /* '<S75>/f_3 < 0' */
  real_T f_30_e;                       /* '<S75>/f_3 > 0' */
  real_T MultiportSwitch_g;            /* '<S75>/Multiport Switch' */
  real_T DeadZone_fm;                  /* '<S76>/Dead Zone' */
  real_T f_40_l;                       /* '<S76>/f_4 < 0' */
  real_T f_40_o;                       /* '<S76>/f_4 > 0' */
  real_T MultiportSwitch_i;            /* '<S76>/Multiport Switch' */
  real_T DeadZone_jb;                  /* '<S77>/Dead Zone' */
  real_T f_50_b;                       /* '<S77>/f_5 < 0' */
  real_T f_50_k;                       /* '<S77>/f_5 > 0' */
  real_T MultiportSwitch_o;            /* '<S77>/Multiport Switch' */
  real_T ThrustersettingSwitch[7];     /* '<S1>/Thruster setting Switch' */
  real_T Saturation_e[7];              /* '<S1>/Saturation' */
  real_T l_x1_e;                       /* '<S112>/-l_x1' */
  real_T l_y2_g;                       /* '<S112>/-l_y2' */
  real_T l_x2_h;                       /* '<S112>/-l_x2' */
  real_T x5_f[15];                     /* '<S112>/3x5' */
  real_T u_1tof_1;                     /* '<S111>/u_1 to f_1' */
  real_T u_2tof_2;                     /* '<S111>/u_2 to f_2' */
  real_T u_3tof_3;                     /* '<S111>/u_3 to f_3' */
  real_T u_4tof_4;                     /* '<S111>/u_4 to f_4' */
  real_T u_5tof_5;                     /* '<S111>/u_5 to f_5' */
  real_T TmpHiddenBufferAtProductInpor_c[5];/* 'synthesized block' */
  real_T Product_cb[3];                /* '<S110>/Product' */
  real_T tauSwitch[3];                 /* '<S1>/tau Switch' */
  real_T TmpHiddenBufferAtToFileInport1[36];/* 'synthesized block' */
  real_T x2[4];                        /* '<S41>/2x2' */
  real_T Product_ff[3];                /* '<S42>/Product' */
  real_T Add_h[2];                     /* '<S52>/Add' */
  real_T MathFunction_gg[3];           /* '<S96>/Math Function' */
  real_T Product_cu[2];                /* '<S53>/Product' */
  real_T Gain_f3[2];                   /* '<S53>/Gain' */
  real_T MathFunction_g1[2];           /* '<S94>/Math Function' */
  real_T Product_if[2];                /* '<S52>/Product' */
  real_T Add1_c[2];                    /* '<S52>/Add1' */
  real_T Product1_f5[2];               /* '<S52>/Product1' */
  real_T Gain_kii[2];                  /* '<S52>/Gain' */
  real_T SITzAI0;                      /* '<S3>/SIT zAI0' */
  real_T BatteryBowThruster;           /* '<S3>/Battery Bow Thruster' */
  real_T SITzAI1;                      /* '<S3>/SIT zAI1' */
  real_T BatteryServo;                 /* '<S3>/Battery Servo' */
  real_T SITzAI2;                      /* '<S3>/SIT zAI2' */
  real_T BatteryMain;                  /* '<S3>/Battery Main' */
  real_T QTMIn1FPS;                    /* '<S199>/QTM In1 FPS' */
  real_T Saturation_dq;                /* '<S203>/Saturation' */
  real_T Saturation1;                  /* '<S203>/Saturation1' */
  real_T Saturation2;                  /* '<S203>/Saturation2' */
  real_T planttau_surge;               /* '<S203>/plant tau_surge' */
  real_T planttau_sway;                /* '<S203>/plant tau_sway' */
  real_T planttau_yaw;                 /* '<S203>/plant tau_yaw' */
  real_T plantu_1;                     /* '<S5>/plant u_1' */
  real_T plantu_2;                     /* '<S5>/plant u_2' */
  real_T plantu_3;                     /* '<S5>/plant u_3' */
  real_T plantu_4;                     /* '<S5>/plant u_4' */
  real_T plantu_5;                     /* '<S5>/plant u_5' */
  real_T plantBTpower;                 /* '<S5>/plant BT power' */
  real_T plantVSPspeed;                /* '<S5>/plant VSP speed' */
  real_T eta_psi;                      /* '<Root>/eta_psi' */
  real_T eta_psid;                     /* '<Root>/eta_psid' */
  real_T eta_x;                        /* '<Root>/eta_x' */
  real_T eta_xd;                       /* '<Root>/eta_xd' */
  real_T eta_y;                        /* '<Root>/eta_y' */
  real_T eta_yd;                       /* '<Root>/eta_yd' */
  real_T psi_los_k;                    /* '<Root>/psi_los' */
  real_T psi_plot[3];                  /* '<Root>/psi_plot' */
  real_T q_x_e;                        /* '<Root>/q_x' */
  real_T q_y_c;                        /* '<Root>/q_y' */
  real_T x_plot[3];                    /* '<Root>/x_plot' */
  real_T y_plot[3];                    /* '<Root>/y_plot' */
  real_T N_r_o;                        /* '<S210>/-N_r' */
  real_T N_v_h;                        /* '<S210>/-N_v' */
  real_T X_u_o;                        /* '<S210>/-X_u' */
  real_T Y_v_g;                        /* '<S210>/-Y_v' */
  real_T Y_vr_g;                       /* '<S210>/-Y_vr' */
  real_T LinearDampningmatrix_m[9];    /* '<S210>/Linear Dampning matrix' */
  real_T psi_0;                        /* '<S211>/psi_0' */
  real_T x_0;                          /* '<S211>/x_0' */
  real_T y_0;                          /* '<S211>/y_0' */
  real_T r_0;                          /* '<S212>/r_0' */
  real_T u_0;                          /* '<S212>/u_0' */
  real_T v_0;                          /* '<S212>/v_0' */
  real_T Integrator_p[3];              /* '<S209>/Integrator' */
  real_T Integrator1_f[3];             /* '<S209>/Integrator1' */
  real_T M_11_f;                       /* '<S213>/M_11' */
  real_T M_22_c;                       /* '<S213>/M_22' */
  real_T mx_g_e;                       /* '<S213>/m x_g' */
  real_T M_32_n;                       /* '<S213>/M_32' */
  real_T M_23_l;                       /* '<S213>/M_23' */
  real_T M_33_p;                       /* '<S213>/M_33' */
  real_T M[9];                         /* '<S213>/M' */
  real_T Inverse[9];                   /* '<S213>/Inverse' */
  real_T Product1_ob[3];               /* '<S209>/Product1' */
  real_T R11_n;                        /* '<S214>/R11' */
  real_T R21_m4;                       /* '<S214>/R21' */
  real_T R12_l;                        /* '<S214>/R12' */
  real_T R22_pu;                       /* '<S214>/R22' */
  real_T Rpsi_o[9];                    /* '<S214>/R(psi)' */
  real_T Product3_f[3];                /* '<S209>/Product3' */
  real_T eta_surge_hil;                /* '<S202>/eta_surge_hil' */
  real_T eta_sway_hil;                 /* '<S202>/eta_sway_hil' */
  real_T eta_yaw_hil;                  /* '<S202>/eta_yaw_hil' */
  real_T etadot_surge_hil;             /* '<S202>/etadot_surge_hil' */
  real_T etadot_sway_hil;              /* '<S202>/etadot_sway_hil' */
  real_T etadot_yaw_hil;               /* '<S202>/etadot_yaw_hil' */
  real_T nu_surge_hil;                 /* '<S202>/nu_surge_hil' */
  real_T nu_sway_hil;                  /* '<S202>/nu_sway_hil' */
  real_T nu_yaw_hil;                   /* '<S202>/nu_yaw_hil' */
  real_T Sum_j3[3];                    /* '<S209>/Sum' */
  real_T Product2_d[3];                /* '<S209>/Product2' */
  real_T BT_D_Gain1;                   /* '<S204>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S204>/BT_D_Gain2' */
  real_T Add_ct;                       /* '<S204>/Add' */
  real_T BT_L_Gain1;                   /* '<S204>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S204>/BT_L_Gain2' */
  real_T Neg;                          /* '<S204>/Neg' */
  real_T Sum1_k;                       /* '<S204>/Sum1' */
  real_T Sum2;                         /* '<S204>/Sum2' */
  real_T Switch_i;                     /* '<S206>/Switch' */
  real_T Switch2_d;                    /* '<S206>/Switch2' */
  real_T Switch_d;                     /* '<S207>/Switch' */
  real_T Switch2_p;                    /* '<S207>/Switch2' */
  real_T Switch_d3;                    /* '<S208>/Switch' */
  real_T Switch2_o;                    /* '<S208>/Switch2' */
  real_T Sign_o;                       /* '<S205>/Sign' */
  real_T PortVPS_X;                    /* '<S205>/Product1' */
  real_T PortVPS_X_n;                  /* '<S205>/-x' */
  real_T PortVSP_Y;                    /* '<S205>/Product2' */
  real_T PortVSP_Y_b;                  /* '<S205>/-y' */
  real_T StarboardVSP_X;               /* '<S205>/Product3' */
  real_T StarboardVSP_Y;               /* '<S205>/Product4' */
  real_T Servo1;                       /* '<S205>/Servo1' */
  real_T Servo2;                       /* '<S205>/Servo2' */
  real_T Servo3;                       /* '<S205>/Servo3' */
  real_T Servo4;                       /* '<S205>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S205>/VPS_Speed_Gain' */
  real_T Sum_d3;                       /* '<S205>/Sum' */
  real_T VSPSPort;                     /* '<S205>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S205>/VSPS Starboard' */
  real_T S12_o;                        /* '<S165>/S12' */
  real_T S_2psi_ds2[4];                /* '<S165>/S_2(psi_d^s^2)' */
  real_T S12_c;                        /* '<S164>/S12' */
  real_T S_2psi_ds[4];                 /* '<S164>/S_2(psi_d^s)' */
  real_T R11_cj;                       /* '<S162>/R11' */
  real_T R21_o;                        /* '<S162>/R21' */
  real_T R12_k;                        /* '<S162>/R12' */
  real_T R22_l;                        /* '<S162>/R22' */
  real_T R_2psi_d[4];                  /* '<S162>/R_2(psi_d)' */
  uint16_T Gain_p;                     /* '<S17>/Gain' */
  uint16_T Gain1_a;                    /* '<S17>/Gain1' */
  uint16_T Sum_i;                      /* '<S17>/Sum' */
  uint16_T Gain_nw;                    /* '<S18>/Gain' */
  uint16_T Gain1_hg;                   /* '<S18>/Gain1' */
  uint16_T Sum_a;                      /* '<S18>/Sum' */
  uint16_T Gain_br;                    /* '<S19>/Gain' */
  uint16_T Gain1_hu;                   /* '<S19>/Gain1' */
  uint16_T Sum_n5;                     /* '<S19>/Sum' */
  uint16_T Gain_c5;                    /* '<S20>/Gain' */
  uint16_T Gain1_mp;                   /* '<S20>/Gain1' */
  uint16_T Sum_k;                      /* '<S20>/Sum' */
  uint16_T Gain_j1;                    /* '<S21>/Gain' */
  uint16_T Gain1_cf;                   /* '<S21>/Gain1' */
  uint16_T Sum_fw;                     /* '<S21>/Sum' */
  uint16_T Gain_ji;                    /* '<S73>/Gain' */
  uint16_T Gain1_ld;                   /* '<S73>/Gain1' */
  uint16_T Sum_gp;                     /* '<S73>/Sum' */
  uint16_T Gain_n4;                    /* '<S74>/Gain' */
  uint16_T Gain1_aa;                   /* '<S74>/Gain1' */
  uint16_T Sum_af;                     /* '<S74>/Sum' */
  uint16_T Gain_dm;                    /* '<S75>/Gain' */
  uint16_T Gain1_hl;                   /* '<S75>/Gain1' */
  uint16_T Sum_fi;                     /* '<S75>/Sum' */
  uint16_T Gain_gr;                    /* '<S76>/Gain' */
  uint16_T Gain1_mc;                   /* '<S76>/Gain1' */
  uint16_T Sum_mq;                     /* '<S76>/Sum' */
  uint16_T Gain_cv;                    /* '<S77>/Gain' */
  uint16_T Gain1_e;                    /* '<S77>/Gain1' */
  uint16_T Sum_ih;                     /* '<S77>/Sum' */
  uint8_T Compare;                     /* '<S22>/Compare' */
  uint8_T Compare_e;                   /* '<S24>/Compare' */
  uint8_T Compare_j;                   /* '<S23>/Compare' */
  uint8_T Compare_a;                   /* '<S25>/Compare' */
  uint8_T Compare_n;                   /* '<S26>/Compare' */
  uint8_T Compare_m;                   /* '<S27>/Compare' */
  uint8_T Compare_p;                   /* '<S28>/Compare' */
  uint8_T Compare_c;                   /* '<S30>/Compare' */
  uint8_T Compare_i;                   /* '<S29>/Compare' */
  uint8_T Compare_o;                   /* '<S31>/Compare' */
  uint8_T Compare_ng;                  /* '<S33>/Compare' */
  uint8_T Compare_cx;                  /* '<S32>/Compare' */
  uint8_T Compare_l;                   /* '<S34>/Compare' */
  uint8_T Compare_b;                   /* '<S36>/Compare' */
  uint8_T Compare_d;                   /* '<S35>/Compare' */
  uint8_T Compare_en;                  /* '<S78>/Compare' */
  uint8_T Compare_p1;                  /* '<S80>/Compare' */
  uint8_T Compare_f;                   /* '<S79>/Compare' */
  uint8_T Compare_em;                  /* '<S81>/Compare' */
  uint8_T Compare_ib;                  /* '<S82>/Compare' */
  uint8_T Compare_lq;                  /* '<S83>/Compare' */
  uint8_T Compare_lu;                  /* '<S84>/Compare' */
  uint8_T Compare_p0;                  /* '<S86>/Compare' */
  uint8_T Compare_ot;                  /* '<S85>/Compare' */
  uint8_T Compare_g;                   /* '<S87>/Compare' */
  uint8_T Compare_on;                  /* '<S89>/Compare' */
  uint8_T Compare_ir;                  /* '<S88>/Compare' */
  uint8_T Compare_bz;                  /* '<S90>/Compare' */
  uint8_T Compare_cv;                  /* '<S92>/Compare' */
  uint8_T Compare_mx;                  /* '<S91>/Compare' */
  boolean_T LowerRelop1;               /* '<S190>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S190>/UpperRelop' */
  boolean_T LowerRelop1_k;             /* '<S191>/LowerRelop1' */
  boolean_T UpperRelop_e;              /* '<S191>/UpperRelop' */
  boolean_T LowerRelop1_n;             /* '<S206>/LowerRelop1' */
  boolean_T UpperRelop_m;              /* '<S206>/UpperRelop' */
  boolean_T LowerRelop1_j;             /* '<S207>/LowerRelop1' */
  boolean_T UpperRelop_b;              /* '<S207>/UpperRelop' */
  boolean_T LowerRelop1_b;             /* '<S208>/LowerRelop1' */
  boolean_T UpperRelop_h;              /* '<S208>/UpperRelop' */
} BlockIO_LgV2;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Pseudoinverse_X[15];          /* '<S16>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S16>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S16>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S16>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S16>/Pseudoinverse' */
  real_T Product_DWORK1;               /* '<S140>/Product' */
  real_T Product3_DWORK1[6];           /* '<S55>/Product3' */
  real_T Inverse_DWORK3[9];            /* '<S213>/Inverse' */
  real_T Inverse_DWORK4[9];            /* '<S213>/Inverse' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[3];
    real_T TimeStampB;
    real_T LastUAtTimeB[3];
  } Derivative1_RWORK;                 /* '<S199>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } Derivative_RWORK;                  /* '<S199>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_m;                /* '<S118>/Derivative' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<Root>/To File' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<S18>/Scope2' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_f;                    /* '<S74>/Scope2' */

  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<S102>/Scope' */

  struct {
    void *LoggedData;
  } Scope_PWORK_e;                     /* '<S136>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S136>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_h;                    /* '<S136>/Scope2' */

  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<S136>/Scope3' */

  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  int32_T Inverse_DWORK2[3];           /* '<S213>/Inverse' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S17>/Sum' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S52>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S52>/Integrator1' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<Root>/To File' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_o;                /* '<S209>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_l;               /* '<S209>/Integrator1' */

  int_T LinearSimulator_MODE;          /* '<S5>/Linear Simulator' */
  int_T CSE1_MODE;                     /* '<S5>/CSE1' */
  uint8_T SignalProbe_DWORK1[5];       /* '<Root>/SignalProbe' */
} D_Work_LgV2;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S52>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S52>/Integrator1' */
  real_T Integrator_CSTATE_k[3];       /* '<S10>/Integrator' */
  real_T Integrator_CSTATE_j[3];       /* '<S42>/Integrator' */
  real_T Integrator2_CSTATE[2];        /* '<S52>/Integrator2' */
  real_T Integrator_CSTATE_f[3];       /* '<S209>/Integrator' */
  real_T Integrator1_CSTATE_h[3];      /* '<S209>/Integrator1' */
} ContinuousStates_LgV2;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S52>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S52>/Integrator1' */
  real_T Integrator_CSTATE_k[3];       /* '<S10>/Integrator' */
  real_T Integrator_CSTATE_j[3];       /* '<S42>/Integrator' */
  real_T Integrator2_CSTATE[2];        /* '<S52>/Integrator2' */
  real_T Integrator_CSTATE_f[3];       /* '<S209>/Integrator' */
  real_T Integrator1_CSTATE_h[3];      /* '<S209>/Integrator1' */
} StateDerivatives_LgV2;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[2];      /* '<S52>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S52>/Integrator1' */
  boolean_T Integrator_CSTATE_k[3];    /* '<S10>/Integrator' */
  boolean_T Integrator_CSTATE_j[3];    /* '<S42>/Integrator' */
  boolean_T Integrator2_CSTATE[2];     /* '<S52>/Integrator2' */
  boolean_T Integrator_CSTATE_f[3];    /* '<S209>/Integrator' */
  boolean_T Integrator1_CSTATE_h[3];   /* '<S209>/Integrator1' */
} StateDisabled_LgV2;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S52>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S52>/Integrator1' */
  ZCSigState Integrator_Reset_ZCE_f;   /* '<S10>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_k;   /* '<S209>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE_g;  /* '<S209>/Integrator1' */
} PrevZCSigStates_LgV2;

#ifndef ODE5_INTG
#define ODE5_INTG

/* ODE5 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[6];                        /* derivatives */
} ODE5_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Computed Parameter: INDEX_ARRAY_FLAT
   * Referenced by blocks:
   * '<S130>/Multiport Selector'
   * '<S130>/Multiport Selector1'
   * '<S130>/Multiport Selector2'
   * '<S130>/Multiport Selector3'
   * '<S130>/Multiport Selector4'
   */
  int32_T pooled1;
} ConstParam_LgV2;

/* Backward compatible GRT Identifiers */
#define rtB                            LgV2_B
#define BlockIO                        BlockIO_LgV2
#define rtX                            LgV2_X
#define ContinuousStates               ContinuousStates_LgV2
#define rtP                            LgV2_P
#define Parameters                     Parameters_LgV2
#define rtDWork                        LgV2_DWork
#define D_Work                         D_Work_LgV2
#define ConstParam                     ConstParam_LgV2
#define rtcP                           LgV2_ConstP
#define rtPrevZCSigState               LgV2_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_LgV2

/* Parameters (auto storage) */
struct Parameters_LgV2_ {
  real_T ControllerInputSelector_Value;/* Expression: 0
                                        * '<S4>/Controller Input Selector'
                                        */
  real_T QTMIn_P1;                     /* Expression: width
                                        * '<S199>/QTM In'
                                        */
  real_T QTMIn_P2;                     /* Expression: dtype
                                        * '<S199>/QTM In'
                                        */
  real_T QTMIn_P3;                     /* Expression: portnum
                                        * '<S199>/QTM In'
                                        */
  real_T QTMIn_P4;                     /* Expression: stime
                                        * '<S199>/QTM In'
                                        */
  real_T QTMIn_P5;                     /* Expression: stype
                                        * '<S199>/QTM In'
                                        */
  real_T QTMIn_P6;                     /* Expression: btype
                                        * '<S199>/QTM In'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S199>/QTM In2 Error'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S199>/QTM In9 Residual'
                                        */
  real_T QTMIn3_Gain;                  /* Expression: 1
                                        * '<S199>/QTM In3'
                                        */
  real_T mm2mx_Gain;                   /* Expression: 0.001
                                        * '<S199>/mm2m x'
                                        */
  real_T QTMIn4_Gain;                  /* Expression: 1
                                        * '<S199>/QTM In4'
                                        */
  real_T mm2my_Gain;                   /* Expression: 0.001
                                        * '<S199>/mm2m y'
                                        */
  real_T QTMIn6_Gain;                  /* Expression: 1
                                        * '<S199>/QTM In6'
                                        */
  real_T d2ryaw_Gain;                  /* Expression: pi/180
                                        * '<S199>/d2r yaw'
                                        */
  real_T EnableLinearSimulator_Value;  /* Expression: 0
                                        * '<S5>/Enable Linear Simulator'
                                        */
  real_T etadot_surge_Gain;            /* Expression: 1
                                        * '<S4>/etadot_surge'
                                        */
  real_T etadot_sway_Gain;             /* Expression: 1
                                        * '<S4>/etadot_sway'
                                        */
  real_T etadot_yaw_Gain;              /* Expression: 1
                                        * '<S4>/etadot_yaw'
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
                                        * '<S199>/QTM In8'
                                        */
  real_T d2rroll_Gain;                 /* Expression: pi/180
                                        * '<S199>/d2r roll'
                                        */
  real_T QTMIn7_Gain;                  /* Expression: 1
                                        * '<S199>/QTM In7'
                                        */
  real_T d2rpitch_Gain;                /* Expression: pi/180
                                        * '<S199>/d2r pitch'
                                        */
  real_T Constant1_Value[9];           /* Expression: zeros(3)
                                        * '<S199>/Constant1'
                                        */
  real_T QTMIn5_Gain;                  /* Expression: 1
                                        * '<S199>/QTM In5'
                                        */
  real_T mm2mz_Gain;                   /* Expression: 0.001
                                        * '<S199>/mm2m z'
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
  real_T x_d_Value;                    /* Expression: 0
                                        * '<S196>/x_d'
                                        */
  real_T eta_dDPN_Gain;                /* Expression: 1
                                        * '<S113>/eta_d DP N'
                                        */
  real_T y_d_Value;                    /* Expression: 0
                                        * '<S196>/y_d'
                                        */
  real_T eta_dDPE_Gain;                /* Expression: 1
                                        * '<S113>/eta_d DP E'
                                        */
  real_T psi_d_Value;                  /* Expression: 0
                                        * '<S196>/psi_d'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * '<S198>/Gain1'
                                        */
  real_T eta_dDPPsi_Gain;              /* Expression: 1
                                        * '<S113>/eta_d DP Psi'
                                        */
  real_T Resetq_Value;                 /* Expression: 0
                                        * '<S52>/Reset q'
                                        */
  real_T q_x_0_Value;                  /* Expression: 0
                                        * '<S95>/q_x_0'
                                        */
  real_T q_y_0_Value;                  /* Expression: 0
                                        * '<S95>/q_y_0'
                                        */
  real_T x_2_Value;                    /* Expression: 5.5
                                        * '<S197>/x_2'
                                        */
  real_T x_1_Value;                    /* Expression: 0
                                        * '<S197>/x_1'
                                        */
  real_T y_2_Value;                    /* Expression: 2
                                        * '<S197>/y_2'
                                        */
  real_T y_1_Value;                    /* Expression: 0
                                        * '<S197>/y_1'
                                        */
  real_T PathSelector_Value;           /* Expression: 0
                                        * '<S117>/Path Selector'
                                        */
  real_T r_x_Value;                    /* Expression: 5.5
                                        * '<S197>/r_x'
                                        */
  real_T Resets_Value;                 /* Expression: 0
                                        * '<S52>/Reset s'
                                        */
  real_T s_0_Value;                    /* Expression: 0
                                        * '<S52>/s_0'
                                        */
  real_T k_Value;                      /* Expression: pi/180*2
                                        * '<S197>/k'
                                        */
  real_T Gain_Gain;                    /* Expression: -1
                                        * '<S176>/Gain'
                                        */
  real_T r_y_Value;                    /* Expression: 2
                                        * '<S197>/r_y'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * '<S182>/Constant'
                                        */
  real_T Gain_Gain_p;                  /* Expression: 180/pi
                                        * '<S124>/Gain'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * '<S122>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * '<S122>/Saturation'
                                        */
  real_T Gain_Gain_m;                  /* Expression: 180
                                        * '<S122>/Gain'
                                        */
  real_T Constant_Value_h;             /* Expression: 2*180
                                        * '<S122>/Constant'
                                        */
  real_T Gain1_Gain_g;                 /* Expression: pi/180
                                        * '<S123>/Gain1'
                                        */
  real_T Gain_Gain_n;                  /* Expression: 180/pi
                                        * '<S157>/Gain'
                                        */
  real_T Saturation_UpperSat_b;        /* Expression: 1e10
                                        * '<S153>/Saturation'
                                        */
  real_T Saturation_LowerSat_i;        /* Expression: -1e10
                                        * '<S153>/Saturation'
                                        */
  real_T Gain_Gain_g;                  /* Expression: 180
                                        * '<S153>/Gain'
                                        */
  real_T Constant_Value_p;             /* Expression: 2*180
                                        * '<S153>/Constant'
                                        */
  real_T Gain1_Gain_o;                 /* Expression: pi/180
                                        * '<S156>/Gain1'
                                        */
  real_T x_dmax_Value;                 /* Expression: 10000
                                        * '<S174>/x_dmax'
                                        */
  real_T origin_x_Value;               /* Expression: 4.5
                                        * '<S197>/origin_x'
                                        */
  real_T origo_y_Value;                /* Expression: 0
                                        * '<S197>/origo_y'
                                        */
  real_T Constant_Value_o;             /* Expression: 1
                                        * '<S181>/Constant'
                                        */
  real_T x_dmin_Value;                 /* Expression: -10000
                                        * '<S174>/x_dmin'
                                        */
  real_T y_dmax_Value;                 /* Expression: 10000
                                        * '<S174>/y_dmax'
                                        */
  real_T y_dmin_Value;                 /* Expression: -10000
                                        * '<S174>/y_dmin'
                                        */
  real_T Delta_Value;                  /* Expression: 2
                                        * '<S114>/Delta'
                                        */
  real_T Gain_Gain_pe;                 /* Expression: 180/pi
                                        * '<S159>/Gain'
                                        */
  real_T Saturation_UpperSat_k;        /* Expression: 1e10
                                        * '<S154>/Saturation'
                                        */
  real_T Saturation_LowerSat_p;        /* Expression: -1e10
                                        * '<S154>/Saturation'
                                        */
  real_T Gain_Gain_pg;                 /* Expression: 180
                                        * '<S154>/Gain'
                                        */
  real_T Constant_Value_od;            /* Expression: 2*180
                                        * '<S154>/Constant'
                                        */
  real_T Gain1_Gain_m;                 /* Expression: pi/180
                                        * '<S158>/Gain1'
                                        */
  real_T Gain_Gain_l;                  /* Expression: 180/pi
                                        * '<S161>/Gain'
                                        */
  real_T Saturation_UpperSat_i;        /* Expression: 1e10
                                        * '<S155>/Saturation'
                                        */
  real_T Saturation_LowerSat_iq;       /* Expression: -1e10
                                        * '<S155>/Saturation'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 180
                                        * '<S155>/Gain'
                                        */
  real_T Constant_Value_e;             /* Expression: 2*180
                                        * '<S155>/Constant'
                                        */
  real_T Gain1_Gain_k;                 /* Expression: pi/180
                                        * '<S160>/Gain1'
                                        */
  real_T q_x_Gain;                     /* Expression: 1
                                        * '<S2>/q_x'
                                        */
  real_T q_y_Gain;                     /* Expression: 1
                                        * '<S2>/q_y'
                                        */
  real_T psi_los_Gain;                 /* Expression: 1
                                        * '<S2>/psi_los'
                                        */
  real_T pathx_d_Gain;                 /* Expression: 1
                                        * '<S2>/path x_d'
                                        */
  real_T pathy_d_Gain;                 /* Expression: 1
                                        * '<S2>/path y_d'
                                        */
  real_T pathpsi_d_Gain;               /* Expression: 1
                                        * '<S2>/path psi_d'
                                        */
  real_T u_d_Value;                    /* Expression: 0.15
                                        * '<S197>/u_d'
                                        */
  real_T Constant_Value_oc;            /* Expression: 1
                                        * '<S185>/Constant'
                                        */
  real_T ControlMode_Value;            /* Expression: 0
                                        * '<S1>/Control Mode'
                                        */
  real_T AS_LY_Value;                  /* Expression: 0
                                        * '<S8>/AS_LY'
                                        */
  real_T ScalingLY_Gain;               /* Expression: 1/32767
                                        * '<S8>/ScalingLY'
                                        */
  real_T PS3u_1_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_1'
                                        */
  real_T AS_LX_Value;                  /* Expression: 0
                                        * '<S8>/AS_LX'
                                        */
  real_T ScalingLX_Gain;               /* Expression: 1/32767
                                        * '<S8>/ScalingLX'
                                        */
  real_T PS3u_2_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_2'
                                        */
  real_T AS_RY_Value;                  /* Expression: 0
                                        * '<S8>/AS_RY'
                                        */
  real_T ScalingRY_Gain;               /* Expression: 1/32767
                                        * '<S8>/ScalingRY'
                                        */
  real_T PS3u_3_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_3'
                                        */
  real_T AS_RX_Value;                  /* Expression: 0
                                        * '<S8>/AS_RX'
                                        */
  real_T Scaling_RX_Gain;              /* Expression: 1/32767
                                        * '<S8>/Scaling_RX'
                                        */
  real_T PS3u_4_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_4'
                                        */
  real_T L2_Value;                     /* Expression: 0
                                        * '<S8>/L2'
                                        */
  real_T R2_Value;                     /* Expression: 0
                                        * '<S8>/R2'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S9>/PS3 u_5'
                                        */
  real_T PS3_BT_Power_Value;           /* Expression: 0
                                        * '<S8>/PS3_BT_Power'
                                        */
  real_T PS3_VSP_Speed_Value;          /* Expression: 0
                                        * '<S8>/PS3_VSP_Speed'
                                        */
  real_T T_e11_Value;                  /* Expression: 1
                                        * '<S37>/T_e11'
                                        */
  real_T T_e21_Value;                  /* Expression: 0
                                        * '<S37>/T_e21'
                                        */
  real_T l_y1_Value;                   /* Expression: 0.055
                                        * '<S37>/l_y1'
                                        */
  real_T T_e12_Value;                  /* Expression: 0
                                        * '<S37>/T_e12'
                                        */
  real_T T_e22_Value;                  /* Expression: 1
                                        * '<S37>/T_e22'
                                        */
  real_T l_x1_Value;                   /* Expression: 0.45
                                        * '<S37>/l_x1'
                                        */
  real_T l_x1_Gain;                    /* Expression: -1
                                        * '<S37>/-l_x1'
                                        */
  real_T T_e13_Value;                  /* Expression: 1
                                        * '<S37>/T_e13'
                                        */
  real_T T_e23_Value;                  /* Expression: 0
                                        * '<S37>/T_e23'
                                        */
  real_T l_y2_Value;                   /* Expression: 0.055
                                        * '<S37>/l_y2'
                                        */
  real_T l_y2_Gain;                    /* Expression: -1
                                        * '<S37>/-l_y2'
                                        */
  real_T T_e14_Value;                  /* Expression: 0
                                        * '<S37>/T_e14'
                                        */
  real_T T_e24_Value;                  /* Expression: 1
                                        * '<S37>/T_e24'
                                        */
  real_T l_x2_Value;                   /* Expression: 0.45
                                        * '<S37>/l_x2'
                                        */
  real_T l_x2_Gain;                    /* Expression: -1
                                        * '<S37>/-l_x2'
                                        */
  real_T T_e15_Value;                  /* Expression: 0
                                        * '<S37>/T_e15'
                                        */
  real_T T_e25_Value;                  /* Expression: 1
                                        * '<S37>/T_e25'
                                        */
  real_T l_x3_Value;                   /* Expression: 0.385
                                        * '<S37>/l_x3'
                                        */
  real_T Saturation_UpperSat_j;        /* Expression: 1e10
                                        * '<S14>/Saturation'
                                        */
  real_T Saturation_LowerSat_j;        /* Expression: -1e10
                                        * '<S14>/Saturation'
                                        */
  real_T Gain_Gain_h;                  /* Expression: pi
                                        * '<S14>/Gain'
                                        */
  real_T Constant_Value_g;             /* Expression: 2*pi
                                        * '<S14>/Constant'
                                        */
  real_T Saturation_UpperSat_g;        /* Expression: 1e10
                                        * '<S13>/Saturation'
                                        */
  real_T Saturation_LowerSat_m;        /* Expression: -1e10
                                        * '<S13>/Saturation'
                                        */
  real_T Gain_Gain_fh;                 /* Expression: pi
                                        * '<S13>/Gain'
                                        */
  real_T Constant_Value_gt;            /* Expression: 2*pi
                                        * '<S13>/Constant'
                                        */
  real_T Kp_Gain[9];                   /* Expression: Kp
                                        * '<S10>/Kp'
                                        */
  real_T K_p_surge_scale_Gain;         /* Expression: 1
                                        * '<S10>/K_p_surge_scale'
                                        */
  real_T K_p_sway_scale_Gain;          /* Expression: 1
                                        * '<S10>/K_p_sway_scale'
                                        */
  real_T K_p_yaw_scale_Gain;           /* Expression: 1
                                        * '<S10>/K_p_yaw_scale'
                                        */
  real_T Reset_DP_integrator_Value;    /* Expression: 0
                                        * '<S10>/Reset_DP_integrator'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * '<S10>/Integrator'
                                        */
  real_T Ki_Gain[9];                   /* Expression: Ki
                                        * '<S10>/Ki'
                                        */
  real_T K_i_surge_scale_Gain;         /* Expression: 1
                                        * '<S10>/K_i_surge_scale'
                                        */
  real_T K_i_sway_scale_Gain;          /* Expression: 1
                                        * '<S10>/K_i_sway_scale'
                                        */
  real_T K_i_yaw_scale_Gain;           /* Expression: 1
                                        * '<S10>/K_i_yaw_scale'
                                        */
  real_T Kd_Gain[9];                   /* Expression: Kd
                                        * '<S10>/Kd'
                                        */
  real_T K_d_surge_scale_Gain;         /* Expression: 1
                                        * '<S10>/K_d_surge_scale'
                                        */
  real_T K_d_sway_scale_Gain;          /* Expression: 1
                                        * '<S10>/K_d_sway_scale'
                                        */
  real_T K_d_yaw_scale_Gain;           /* Expression: 1
                                        * '<S10>/K_d_yaw_scale'
                                        */
  real_T DeadZone_Start;               /* Expression: -0.001
                                        * '<S17>/Dead Zone'
                                        */
  real_T DeadZone_End;                 /* Expression: 0.001
                                        * '<S17>/Dead Zone'
                                        */
  real_T Constant_Value_c;             /* Expression: const
                                        * '<S22>/Constant'
                                        */
  real_T Constant_Value_ek;            /* Expression: const
                                        * '<S23>/Constant'
                                        */
  real_T f_10_XData[9];                /* Expression: [-1.324
                                          -1.169
                                          -0.919
                                          -0.703
                                          -0.535
                                          -0.292
                                          -0.165
                                          -0.060
                                          0]
                                        * '<S17>/f_1 < 0'
                                        */
  real_T f_10_YData[9];                /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2089]
                                        * '<S17>/f_1 < 0'
                                        */
  real_T f_10_Value;                   /* Expression: 0
                                        * '<S17>/f_1 = 0'
                                        */
  real_T f_10_XData_j[10];             /* Expression: [0
                                          0.0510
                                          0.1530
                                          0.3080
                                          0.4800
                                          0.6630
                                          0.9110
                                          1.0570
                                          1.2210
                                          1.3740]
                                        * '<S17>/f_1 > 0'
                                        */
  real_T f_10_YData_h[10];             /* Expression: [0.0500
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000]
                                        * '<S17>/f_1 > 0'
                                        */
  real_T DeadZone_Start_c;             /* Expression: -0.001
                                        * '<S18>/Dead Zone'
                                        */
  real_T DeadZone_End_e;               /* Expression: 0.001
                                        * '<S18>/Dead Zone'
                                        */
  real_T Constant_Value_d;             /* Expression: const
                                        * '<S25>/Constant'
                                        */
  real_T Constant_Value_m;             /* Expression: const
                                        * '<S26>/Constant'
                                        */
  real_T Constant_Value_go;            /* Expression: const
                                        * '<S27>/Constant'
                                        */
  real_T f_20_XData[11];               /* Expression: [-0.766
                                          -0.649
                                          -0.522
                                          -0.411
                                          -0.323
                                          -0.246
                                          -0.156
                                          -0.075
                                          -0.018
                                          -0.006
                                          0]
                                        * '<S18>/f_2 < 0'
                                        */
  real_T f_20_YData[11];               /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0466]
                                        * '<S18>/f_2 < 0'
                                        */
  real_T f_20_Value;                   /* Expression: 0
                                        * '<S18>/f_2 = 0'
                                        */
  real_T f_20_XData_b[10];             /* Expression: [0.000
                                          0.052
                                          0.207
                                          0.331
                                          0.509
                                          0.689
                                          0.829
                                          0.961
                                          1.079
                                          1.120
                                          ]
                                        * '<S18>/f_2 > 0'
                                        */
  real_T f_20_YData_g[10];             /* Expression: [0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S18>/f_2 > 0'
                                        */
  real_T DeadZone_Start_n;             /* Expression: -0.001
                                        * '<S19>/Dead Zone'
                                        */
  real_T DeadZone_End_n;               /* Expression: 0.001
                                        * '<S19>/Dead Zone'
                                        */
  real_T Constant_Value_oz;            /* Expression: const
                                        * '<S28>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: const
                                        * '<S29>/Constant'
                                        */
  real_T f_30_XData[8];                /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S19>/f_3 < 0'
                                        */
  real_T f_30_YData[8];                /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S19>/f_3 < 0'
                                        */
  real_T f_30_Value;                   /* Expression: 0
                                        * '<S19>/f_3 = 0'
                                        */
  real_T f_30_XData_k[11];             /* Expression: [0.000
                                          0.014
                                          0.040
                                          0.147
                                          0.302
                                          0.494
                                          0.680
                                          0.968
                                          1.111
                                          1.289
                                          1.339]
                                        * '<S19>/f_3 > 0'
                                        */
  real_T f_30_YData_b[11];             /* Expression: [0.0452
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000
                                          ]
                                        * '<S19>/f_3 > 0'
                                        */
  real_T DeadZone_Start_h;             /* Expression: -0.001
                                        * '<S20>/Dead Zone'
                                        */
  real_T DeadZone_End_j;               /* Expression: 0.001
                                        * '<S20>/Dead Zone'
                                        */
  real_T Constant_Value_a;             /* Expression: const
                                        * '<S31>/Constant'
                                        */
  real_T Constant_Value_b;             /* Expression: const
                                        * '<S32>/Constant'
                                        */
  real_T f_40_XData[10];               /* Expression: [-1.249
                                          -1.225
                                          -1.094
                                          -0.896
                                          -0.696
                                          -0.502
                                          -0.314
                                          -0.169
                                          -0.042
                                          0.000]
                                        * '<S20>/f_4 < 0'
                                        */
  real_T f_40_YData[10];               /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0674]
                                        * '<S20>/f_4 < 0'
                                        */
  real_T f_40_Value;                   /* Expression: 0
                                        * '<S20>/f_4 = 0'
                                        */
  real_T f_40_XData_j[7];              /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S20>/f_4 > 0'
                                        */
  real_T f_40_YData_f[7];              /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S20>/f_4 > 0'
                                        */
  real_T DeadZone_Start_l;             /* Expression: -0.001
                                        * '<S21>/Dead Zone'
                                        */
  real_T DeadZone_End_a;               /* Expression: 0.001
                                        * '<S21>/Dead Zone'
                                        */
  real_T Constant_Value_om;            /* Expression: const
                                        * '<S34>/Constant'
                                        */
  real_T Constant_Value_cn;            /* Expression: const
                                        * '<S35>/Constant'
                                        */
  real_T f_50_XData[3];                /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S21>/f_5 < 0'
                                        */
  real_T f_50_YData[3];                /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S21>/f_5 < 0'
                                        */
  real_T f_50_Value;                   /* Expression: 0
                                        * '<S21>/f_5 = 0'
                                        */
  real_T f_50_XData_c[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S21>/f_5 > 0'
                                        */
  real_T f_50_YData_m[3];              /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S21>/f_5 > 0'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 1.0
                                        * '<S6>/Saturation'
                                        */
  real_T Saturation_LowerSat_d;        /* Expression: -1.0
                                        * '<S6>/Saturation'
                                        */
  real_T BT_power_limit_Value;         /* Expression: 0.5
                                        * '<S6>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value;             /* Expression: 0.4
                                        * '<S6>/VSP_speeds'
                                        */
  real_T T_e11_Value_i;                /* Expression: 1
                                        * '<S93>/T_e11'
                                        */
  real_T T_e21_Value_m;                /* Expression: 0
                                        * '<S93>/T_e21'
                                        */
  real_T l_y1_Value_a;                 /* Expression: 0.055
                                        * '<S93>/l_y1'
                                        */
  real_T T_e12_Value_c;                /* Expression: 0
                                        * '<S93>/T_e12'
                                        */
  real_T T_e22_Value_c;                /* Expression: 1
                                        * '<S93>/T_e22'
                                        */
  real_T l_x1_Value_p;                 /* Expression: 0.45
                                        * '<S93>/l_x1'
                                        */
  real_T l_x1_Gain_h;                  /* Expression: -1
                                        * '<S93>/-l_x1'
                                        */
  real_T T_e13_Value_g;                /* Expression: 1
                                        * '<S93>/T_e13'
                                        */
  real_T T_e23_Value_h;                /* Expression: 0
                                        * '<S93>/T_e23'
                                        */
  real_T l_y2_Value_c;                 /* Expression: 0.055
                                        * '<S93>/l_y2'
                                        */
  real_T l_y2_Gain_o;                  /* Expression: -1
                                        * '<S93>/-l_y2'
                                        */
  real_T T_e14_Value_b;                /* Expression: 0
                                        * '<S93>/T_e14'
                                        */
  real_T T_e24_Value_c;                /* Expression: 1
                                        * '<S93>/T_e24'
                                        */
  real_T l_x2_Value_k;                 /* Expression: 0.45
                                        * '<S93>/l_x2'
                                        */
  real_T l_x2_Gain_e;                  /* Expression: -1
                                        * '<S93>/-l_x2'
                                        */
  real_T T_e15_Value_l;                /* Expression: 0
                                        * '<S93>/T_e15'
                                        */
  real_T T_e25_Value_o;                /* Expression: 1
                                        * '<S93>/T_e25'
                                        */
  real_T l_x3_Value_m;                 /* Expression: 0.385
                                        * '<S93>/l_x3'
                                        */
  real_T R31_Value;                    /* Expression: 0
                                        * '<S47>/R31'
                                        */
  real_T u_Gain;                       /* Expression: -1
                                        * '<S47>/-1'
                                        */
  real_T R32_Value;                    /* Expression: 0
                                        * '<S47>/R32'
                                        */
  real_T R13_Value;                    /* Expression: 0
                                        * '<S47>/R13'
                                        */
  real_T R23_Value;                    /* Expression: 0
                                        * '<S47>/R23'
                                        */
  real_T R33_Value;                    /* Expression: 1
                                        * '<S47>/R33'
                                        */
  real_T K_i_Surge_Value;              /* Expression: 0
                                        * '<S7>/K_i_Surge'
                                        */
  real_T u_Value;                      /* Expression: 0
                                        * '<S44>/21'
                                        */
  real_T u_Value_e;                    /* Expression: 0
                                        * '<S44>/31'
                                        */
  real_T u_Value_h;                    /* Expression: 0
                                        * '<S44>/12'
                                        */
  real_T K_i_Sway_Value;               /* Expression: 0
                                        * '<S7>/K_i_Sway'
                                        */
  real_T u_Value_h2;                   /* Expression: 0
                                        * '<S44>/32'
                                        */
  real_T u_Value_n;                    /* Expression: 0
                                        * '<S44>/13'
                                        */
  real_T u_Value_h3;                   /* Expression: 0
                                        * '<S44>/23'
                                        */
  real_T K_i_Yaw_Value;                /* Expression: 0
                                        * '<S7>/K_i_Yaw'
                                        */
  real_T Integrator_IC_n[3];           /* Expression: [0 0 0]'
                                        * '<S42>/Integrator'
                                        */
  real_T K_d_Surge_Value;              /* Expression: 50
                                        * '<S7>/K_d_Surge'
                                        */
  real_T u_Value_m;                    /* Expression: 0
                                        * '<S43>/21'
                                        */
  real_T u_Value_hb;                   /* Expression: 0
                                        * '<S43>/31'
                                        */
  real_T u_Value_f;                    /* Expression: 0
                                        * '<S43>/12'
                                        */
  real_T K_d_Sway_Value;               /* Expression: 30
                                        * '<S7>/K_d_Sway'
                                        */
  real_T u_Value_j;                    /* Expression: 0
                                        * '<S43>/32'
                                        */
  real_T u_Value_i;                    /* Expression: 0
                                        * '<S43>/13'
                                        */
  real_T u_Value_d;                    /* Expression: 0
                                        * '<S43>/23'
                                        */
  real_T K_d_Yaw_Value;                /* Expression: 5
                                        * '<S7>/K_d_Yaw'
                                        */
  real_T _Value;                       /* Expression: 1
                                        * '<S40>/1'
                                        */
  real_T kappa_1_Value;                /* Expression: 1
                                        * '<S7>/kappa_1'
                                        */
  real_T _Gain;                        /* Expression: 4
                                        * '<S40>/4'
                                        */
  real_T K_p_Surge_Value;              /* Expression: 2*1.5*2
                                        * '<S7>/K_p_Surge'
                                        */
  real_T u_Value_ho;                   /* Expression: 0
                                        * '<S45>/21'
                                        */
  real_T u_Value_k;                    /* Expression: 0
                                        * '<S45>/31'
                                        */
  real_T u_Value_fw;                   /* Expression: 0
                                        * '<S45>/12'
                                        */
  real_T K_p_Sway_Value;               /* Expression: 2*10*2
                                        * '<S7>/K_p_Sway'
                                        */
  real_T u_Value_hc;                   /* Expression: 0
                                        * '<S45>/32'
                                        */
  real_T u_Value_fu;                   /* Expression: 0
                                        * '<S45>/13'
                                        */
  real_T u_Value_mz;                   /* Expression: 0
                                        * '<S45>/23'
                                        */
  real_T K_p_Yaw_Value;                /* Expression: 0.5*3
                                        * '<S7>/K_p_Yaw'
                                        */
  real_T Constant_Value_bc[9];         /* Expression: a
                                        * '<S97>/Constant'
                                        */
  real_T Gain_Gain_a;                  /* Expression: 180/pi
                                        * '<S105>/Gain'
                                        */
  real_T Saturation_UpperSat_gd;       /* Expression: 1e10
                                        * '<S103>/Saturation'
                                        */
  real_T Saturation_LowerSat_id;       /* Expression: -1e10
                                        * '<S103>/Saturation'
                                        */
  real_T Gain_Gain_j;                  /* Expression: 180
                                        * '<S103>/Gain'
                                        */
  real_T Constant_Value_cj;            /* Expression: 2*180
                                        * '<S103>/Constant'
                                        */
  real_T Gain1_Gain_oh;                /* Expression: pi/180
                                        * '<S104>/Gain1'
                                        */
  real_T Gain_Gain_c;                  /* Expression: 180/pi
                                        * '<S108>/Gain'
                                        */
  real_T Saturation_UpperSat_bg;       /* Expression: 1e10
                                        * '<S106>/Saturation'
                                        */
  real_T Saturation_LowerSat_g;        /* Expression: -1e10
                                        * '<S106>/Saturation'
                                        */
  real_T Gain_Gain_c0;                 /* Expression: 180
                                        * '<S106>/Gain'
                                        */
  real_T Constant_Value_l;             /* Expression: 2*180
                                        * '<S106>/Constant'
                                        */
  real_T Gain1_Gain_d;                 /* Expression: pi/180
                                        * '<S107>/Gain1'
                                        */
  real_T u_Gain_e;                     /* Expression: -1
                                        * '<S148>/-1'
                                        */
  real_T _2x1_Value[2];                /* Expression: [0;0]
                                        * '<S66>/0_2x1'
                                        */
  real_T _2x1_Value_n;                 /* Expression: 0
                                        * '<S173>/0_2x1'
                                        */
  real_T Constant_Value_a4;            /* Expression: 3
                                        * '<S178>/Constant'
                                        */
  real_T Gain_Gain_gg;                 /* Expression: -1
                                        * '<S178>/Gain'
                                        */
  real_T Constant_Value_d3;            /* Expression: 1
                                        * '<S184>/Constant'
                                        */
  real_T my_Value;                     /* Expression: 10
                                        * '<S114>/my'
                                        */
  real_T Gain_Gain_b;                  /* Expression: -1
                                        * '<S140>/Gain'
                                        */
  real_T X_u_Value;                    /* Expression: -0.59739
                                        * '<S70>/X_u'
                                        */
  real_T X_u_Gain;                     /* Expression: -1
                                        * '<S70>/-X_u'
                                        */
  real_T D_L_21_Value;                 /* Expression: 0
                                        * '<S70>/D_L_21'
                                        */
  real_T D_L_31_Value;                 /* Expression: 0
                                        * '<S70>/D_L_31'
                                        */
  real_T D_L_12_Value;                 /* Expression: 0
                                        * '<S70>/D_L_12'
                                        */
  real_T Y_v_Value;                    /* Expression: -3.50625
                                        * '<S70>/Y_v'
                                        */
  real_T Y_v_Gain;                     /* Expression: -1
                                        * '<S70>/-Y_v'
                                        */
  real_T N_v_Value;                    /* Expression: 0.18140
                                        * '<S70>/N_v'
                                        */
  real_T N_v_Gain;                     /* Expression: -1
                                        * '<S70>/-N_v'
                                        */
  real_T D_L_13_Value;                 /* Expression: 0
                                        * '<S70>/D_L_13'
                                        */
  real_T Y_r_Value;                    /* Expression: -7.250
                                        * '<S70>/Y_r'
                                        */
  real_T Y_vr_Gain;                    /* Expression: -1
                                        * '<S70>/-Y_vr'
                                        */
  real_T N_r_Value;                    /* Expression: -1.900
                                        * '<S70>/N_r'
                                        */
  real_T N_r_Gain;                     /* Expression: -1
                                        * '<S70>/-N_r'
                                        */
  real_T m_Value;                      /* Expression: 17.6
                                        * '<S46>/m'
                                        */
  real_T X_udot_Value;                 /* Expression: -2.0
                                        * '<S46>/X_udot'
                                        */
  real_T M_21_Value;                   /* Expression: 0
                                        * '<S46>/M_21'
                                        */
  real_T M_31_Value;                   /* Expression: 0
                                        * '<S46>/M_31'
                                        */
  real_T M_12_Value;                   /* Expression: 0
                                        * '<S46>/M_12'
                                        */
  real_T Y_vdot_Value;                 /* Expression: -10.0
                                        * '<S46>/Y_vdot'
                                        */
  real_T x_g_Value;                    /* Expression: 0.03
                                        * '<S46>/x_g'
                                        */
  real_T N_vdot_Value;                 /* Expression: -0.0
                                        * '<S46>/N_vdot'
                                        */
  real_T M_13_Value;                   /* Expression: 0
                                        * '<S46>/M_13'
                                        */
  real_T Y_rdot_Value;                 /* Expression: 0.0
                                        * '<S46>/Y_rdot'
                                        */
  real_T I_z_Value;                    /* Expression: 1.760
                                        * '<S46>/I_z'
                                        */
  real_T N_rdot_Value;                 /* Expression: -1.0
                                        * '<S46>/N_rdot'
                                        */
  real_T Constant_Value_dh[9];         /* Expression: a
                                        * '<S100>/Constant'
                                        */
  real_T S11_Value;                    /* Expression: 0
                                        * '<S49>/S11'
                                        */
  real_T R31_Value_a;                  /* Expression: 0
                                        * '<S49>/R31'
                                        */
  real_T S12_Gain;                     /* Expression: 1
                                        * '<S49>/S12'
                                        */
  real_T S22_Value;                    /* Expression: 0
                                        * '<S49>/S22'
                                        */
  real_T S32_Value;                    /* Expression: 0
                                        * '<S49>/S32'
                                        */
  real_T S13_Value;                    /* Expression: 0
                                        * '<S49>/S13'
                                        */
  real_T S23_Value;                    /* Expression: 0
                                        * '<S49>/S23'
                                        */
  real_T S33_Value;                    /* Expression: 1
                                        * '<S49>/S33'
                                        */
  real_T _2x1_Value_p[2];              /* Expression: [0;0]
                                        * '<S69>/0_2x1'
                                        */
  real_T Constant_Value_cf[9];         /* Expression: a
                                        * '<S98>/Constant'
                                        */
  real_T Constant_Value_k[4];          /* Expression: a
                                        * '<S131>/Constant'
                                        */
  real_T Gain_Gain_e;                  /* Expression: -1
                                        * '<S133>/Gain'
                                        */
  real_T _Gain_l;                      /* Expression: 2
                                        * '<S149>/2'
                                        */
  real_T _2x2_Value[4];                /* Expression: [0 0;0 0]
                                        * '<S130>/0_2x2'
                                        */
  real_T _2x2_Value_n[4];              /* Expression: [0 0; 0 0]
                                        * '<S67>/0_2x2'
                                        */
  real_T _Gain_b;                      /* Expression: 2
                                        * '<S150>/2'
                                        */
  real_T u_Value_id;                   /* Expression: 3/2
                                        * '<S137>/3//2'
                                        */
  real_T Gain_Gain_d;                  /* Expression: -1
                                        * '<S141>/Gain'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * '<S52>/Integrator2'
                                        */
  real_T Constant_Value_bk[9];         /* Expression: a
                                        * '<S99>/Constant'
                                        */
  real_T _2x1_Value_j[2];              /* Expression: [0;0]
                                        * '<S125>/0_2x1'
                                        */
  real_T Gain_Gain_dz;                 /* Expression: -1
                                        * '<S134>/Gain'
                                        */
  real_T _2x1_Value_jo[2];             /* Expression: [0;0]
                                        * '<S68>/0_2x1'
                                        */
  real_T Gain_Gain_nx;                 /* Expression: -1
                                        * '<S177>/Gain'
                                        */
  real_T Gain1_Gain_p;                 /* Expression: -1
                                        * '<S177>/Gain1'
                                        */
  real_T Constant_Value_pj;            /* Expression: 1
                                        * '<S183>/Constant'
                                        */
  real_T u_Gain_m;                     /* Expression: 2
                                        * '<S121>/+ 2'
                                        */
  real_T _Gain_p;                      /* Expression: 2
                                        * '<S152>/2'
                                        */
  real_T _Gain_a;                      /* Expression: 2
                                        * '<S170>/2'
                                        */
  real_T Gain_Gain_eq;                 /* Expression: 1
                                        * '<S170>/Gain'
                                        */
  real_T Constant_Value_c5;            /* Expression: 3
                                        * '<S193>/Constant'
                                        */
  real_T Gain_Gain_af;                 /* Expression: -1
                                        * '<S193>/Gain'
                                        */
  real_T u_Value_jc;                   /* Expression: 3/2
                                        * '<S138>/3//2'
                                        */
  real_T Constant_Value_dc;            /* Expression: 3
                                        * '<S142>/Constant'
                                        */
  real_T DeadZone_Start_b;             /* Expression: -0.001
                                        * '<S73>/Dead Zone'
                                        */
  real_T DeadZone_End_jo;              /* Expression: 0.001
                                        * '<S73>/Dead Zone'
                                        */
  real_T Constant_Value_jz;            /* Expression: const
                                        * '<S78>/Constant'
                                        */
  real_T Constant_Value_gp;            /* Expression: const
                                        * '<S79>/Constant'
                                        */
  real_T f_10_XData_n[9];              /* Expression: [-1.324
                                          -1.169
                                          -0.919
                                          -0.703
                                          -0.535
                                          -0.292
                                          -0.165
                                          -0.060
                                          0]
                                        * '<S73>/f_1 < 0'
                                        */
  real_T f_10_YData_b[9];              /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2089]
                                        * '<S73>/f_1 < 0'
                                        */
  real_T f_10_Value_i;                 /* Expression: 0
                                        * '<S73>/f_1 = 0'
                                        */
  real_T f_10_XData_k[10];             /* Expression: [0
                                          0.0510
                                          0.1530
                                          0.3080
                                          0.4800
                                          0.6630
                                          0.9110
                                          1.0570
                                          1.2210
                                          1.3740]
                                        * '<S73>/f_1 > 0'
                                        */
  real_T f_10_YData_d[10];             /* Expression: [0.0500
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000]
                                        * '<S73>/f_1 > 0'
                                        */
  real_T DeadZone_Start_g;             /* Expression: -0.001
                                        * '<S74>/Dead Zone'
                                        */
  real_T DeadZone_End_p;               /* Expression: 0.001
                                        * '<S74>/Dead Zone'
                                        */
  real_T Constant_Value_cv;            /* Expression: const
                                        * '<S81>/Constant'
                                        */
  real_T Constant_Value_ow;            /* Expression: const
                                        * '<S82>/Constant'
                                        */
  real_T Constant_Value_oq;            /* Expression: const
                                        * '<S83>/Constant'
                                        */
  real_T f_20_XData_g[11];             /* Expression: [-0.766
                                          -0.649
                                          -0.522
                                          -0.411
                                          -0.323
                                          -0.246
                                          -0.156
                                          -0.075
                                          -0.018
                                          -0.006
                                          0]
                                        * '<S74>/f_2 < 0'
                                        */
  real_T f_20_YData_f[11];             /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0466]
                                        * '<S74>/f_2 < 0'
                                        */
  real_T f_20_Value_c;                 /* Expression: 0
                                        * '<S74>/f_2 = 0'
                                        */
  real_T f_20_XData_g0[10];            /* Expression: [0.000
                                          0.052
                                          0.207
                                          0.331
                                          0.509
                                          0.689
                                          0.829
                                          0.961
                                          1.079
                                          1.120
                                          ]
                                        * '<S74>/f_2 > 0'
                                        */
  real_T f_20_YData_b[10];             /* Expression: [0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S74>/f_2 > 0'
                                        */
  real_T DeadZone_Start_cu;            /* Expression: -0.001
                                        * '<S75>/Dead Zone'
                                        */
  real_T DeadZone_End_o;               /* Expression: 0.001
                                        * '<S75>/Dead Zone'
                                        */
  real_T Constant_Value_f;             /* Expression: const
                                        * '<S84>/Constant'
                                        */
  real_T Constant_Value_gc;            /* Expression: const
                                        * '<S85>/Constant'
                                        */
  real_T f_30_XData_p[8];              /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S75>/f_3 < 0'
                                        */
  real_T f_30_YData_e[8];              /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S75>/f_3 < 0'
                                        */
  real_T f_30_Value_m;                 /* Expression: 0
                                        * '<S75>/f_3 = 0'
                                        */
  real_T f_30_XData_g[11];             /* Expression: [0.000
                                          0.014
                                          0.040
                                          0.147
                                          0.302
                                          0.494
                                          0.680
                                          0.968
                                          1.111
                                          1.289
                                          1.339]
                                        * '<S75>/f_3 > 0'
                                        */
  real_T f_30_YData_p[11];             /* Expression: [0.0452
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000
                                          ]
                                        * '<S75>/f_3 > 0'
                                        */
  real_T DeadZone_Start_bq;            /* Expression: -0.001
                                        * '<S76>/Dead Zone'
                                        */
  real_T DeadZone_End_g;               /* Expression: 0.001
                                        * '<S76>/Dead Zone'
                                        */
  real_T Constant_Value_kh;            /* Expression: const
                                        * '<S87>/Constant'
                                        */
  real_T Constant_Value_n;             /* Expression: const
                                        * '<S88>/Constant'
                                        */
  real_T f_40_XData_h[10];             /* Expression: [-1.249
                                          -1.225
                                          -1.094
                                          -0.896
                                          -0.696
                                          -0.502
                                          -0.314
                                          -0.169
                                          -0.042
                                          0.000]
                                        * '<S76>/f_4 < 0'
                                        */
  real_T f_40_YData_m[10];             /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0674]
                                        * '<S76>/f_4 < 0'
                                        */
  real_T f_40_Value_j;                 /* Expression: 0
                                        * '<S76>/f_4 = 0'
                                        */
  real_T f_40_XData_j2[7];             /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S76>/f_4 > 0'
                                        */
  real_T f_40_YData_l[7];              /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S76>/f_4 > 0'
                                        */
  real_T DeadZone_Start_f;             /* Expression: -0.001
                                        * '<S77>/Dead Zone'
                                        */
  real_T DeadZone_End_k;               /* Expression: 0.001
                                        * '<S77>/Dead Zone'
                                        */
  real_T Constant_Value_a4x;           /* Expression: const
                                        * '<S90>/Constant'
                                        */
  real_T Constant_Value_hx;            /* Expression: const
                                        * '<S91>/Constant'
                                        */
  real_T f_50_XData_o[3];              /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S77>/f_5 < 0'
                                        */
  real_T f_50_YData_f[3];              /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S77>/f_5 < 0'
                                        */
  real_T f_50_Value_j;                 /* Expression: 0
                                        * '<S77>/f_5 = 0'
                                        */
  real_T f_50_XData_a[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S77>/f_5 > 0'
                                        */
  real_T f_50_YData_h[3];              /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S77>/f_5 > 0'
                                        */
  real_T BT_power_limit_Value_b;       /* Expression: 0.5
                                        * '<S7>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value_c;           /* Expression: 0.4
                                        * '<S7>/VSP_speeds'
                                        */
  real_T Saturation_UpperSat_p;        /* Expression: 1.0
                                        * '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat_g5;       /* Expression: -1.0
                                        * '<S1>/Saturation'
                                        */
  real_T T_e11_Value_j;                /* Expression: 1
                                        * '<S112>/T_e11'
                                        */
  real_T T_e21_Value_p;                /* Expression: 0
                                        * '<S112>/T_e21'
                                        */
  real_T l_y1_Value_p;                 /* Expression: 0.055
                                        * '<S112>/l_y1'
                                        */
  real_T T_e12_Value_b;                /* Expression: 0
                                        * '<S112>/T_e12'
                                        */
  real_T T_e22_Value_p;                /* Expression: 1
                                        * '<S112>/T_e22'
                                        */
  real_T l_x1_Value_ph;                /* Expression: 0.45
                                        * '<S112>/l_x1'
                                        */
  real_T l_x1_Gain_i;                  /* Expression: -1
                                        * '<S112>/-l_x1'
                                        */
  real_T T_e13_Value_d;                /* Expression: 1
                                        * '<S112>/T_e13'
                                        */
  real_T T_e23_Value_g;                /* Expression: 0
                                        * '<S112>/T_e23'
                                        */
  real_T l_y2_Value_a;                 /* Expression: 0.055
                                        * '<S112>/l_y2'
                                        */
  real_T l_y2_Gain_h;                  /* Expression: -1
                                        * '<S112>/-l_y2'
                                        */
  real_T T_e14_Value_i;                /* Expression: 0
                                        * '<S112>/T_e14'
                                        */
  real_T T_e24_Value_j;                /* Expression: 1
                                        * '<S112>/T_e24'
                                        */
  real_T l_x2_Value_l;                 /* Expression: 0.45
                                        * '<S112>/l_x2'
                                        */
  real_T l_x2_Gain_i;                  /* Expression: -1
                                        * '<S112>/-l_x2'
                                        */
  real_T T_e15_Value_f;                /* Expression: 0
                                        * '<S112>/T_e15'
                                        */
  real_T T_e25_Value_l;                /* Expression: 1
                                        * '<S112>/T_e25'
                                        */
  real_T l_x3_Value_o;                 /* Expression: 0.385
                                        * '<S112>/l_x3'
                                        */
  real_T u_1tof_1_XData[19];           /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2089
                                          0.0500
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000]
                                        * '<S111>/u_1 to f_1'
                                        */
  real_T u_1tof_1_YData[19];           /* Expression: [-1.324
                                          -1.169
                                          -0.919
                                          -0.703
                                          -0.535
                                          -0.292
                                          -0.165
                                          -0.060
                                          0.000
                                          0.000
                                          0.051
                                          0.153
                                          0.308
                                          0.480
                                          0.663
                                          0.911
                                          1.057
                                          1.221
                                          1.374]
                                        * '<S111>/u_1 to f_1'
                                        */
  real_T u_2tof_2_XData[21];           /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0466
                                          0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S111>/u_2 to f_2'
                                        */
  real_T u_2tof_2_YData[21];           /* Expression: [-0.766
                                          -0.649
                                          -0.522
                                          -0.411
                                          -0.323
                                          -0.246
                                          -0.156
                                          -0.075
                                          -0.018
                                          -0.006
                                          0
                                          0
                                          0.052
                                          0.207
                                          0.331
                                          0.509
                                          0.689
                                          0.829
                                          0.961
                                          1.079
                                          1.120]
                                        * '<S111>/u_2 to f_2'
                                        */
  real_T u_3tof_3_XData[19];           /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809
                                          0.0452
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S111>/u_3 to f_3'
                                        */
  real_T u_3tof_3_YData[19];           /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000
                                          0.000
                                          0.014
                                          0.040
                                          0.147
                                          0.302
                                          0.494
                                          0.680
                                          0.968
                                          1.111
                                          1.289
                                          1.339]
                                        * '<S111>/u_3 to f_3'
                                        */
  real_T u_4tof_4_XData[17];           /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0674
                                          0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S111>/u_4 to f_4'
                                        */
  real_T u_4tof_4_YData[17];           /* Expression: [-1.249
                                          -1.225
                                          -1.094
                                          -0.896
                                          -0.696
                                          -0.502
                                          -0.314
                                          -0.169
                                          -0.042
                                          0.000
                                          0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S111>/u_4 to f_4'
                                        */
  real_T u_5tof_5_XData[7];            /* Expression: [-.3:0.1:.3]
                                        * '<S111>/u_5 to f_5'
                                        */
  real_T u_5tof_5_YData[7];            /* Expression: [-1.2630 -1.0309 -0.3808 0 0.3480  0.8290 1.0930]
                                        * '<S111>/u_5 to f_5'
                                        */
  real_T u_Value_nw;                   /* Expression: 0
                                        * '<S41>/12'
                                        */
  real_T u_Value_io;                   /* Expression: 0
                                        * '<S41>/21'
                                        */
  real_T Gamma_q_Surge_Value;          /* Expression: 10*2
                                        * '<S7>/Gamma_q_Surge'
                                        */
  real_T Gamma_q_Sway_Value;           /* Expression: 10*10
                                        * '<S7>/Gamma_q_Sway'
                                        */
  real_T Gain_Gain_cq;                 /* Expression: -1
                                        * '<S53>/Gain'
                                        */
  real_T lambda_Value;                 /* Expression: 1
                                        * '<S7>/lambda'
                                        */
  real_T Gain_Gain_gw;                 /* Expression: -1
                                        * '<S52>/Gain'
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
  real_T BatteryMain_Gain;             /* Expression: 2
                                        * '<S3>/Battery Main'
                                        */
  real_T QTMIn1FPS_Gain;               /* Expression: 1
                                        * '<S199>/QTM In1 FPS'
                                        */
  real_T Saturation_UpperSat_a;        /* Expression: 3
                                        * '<S203>/Saturation'
                                        */
  real_T Saturation_LowerSat_k;        /* Expression: -2.6
                                        * '<S203>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 3
                                        * '<S203>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -3.5
                                        * '<S203>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.6
                                        * '<S203>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S203>/Saturation2'
                                        */
  real_T planttau_surge_Gain;          /* Expression: 1
                                        * '<S203>/plant tau_surge'
                                        */
  real_T planttau_sway_Gain;           /* Expression: 1
                                        * '<S203>/plant tau_sway'
                                        */
  real_T planttau_yaw_Gain;            /* Expression: 1
                                        * '<S203>/plant tau_yaw'
                                        */
  real_T plantu_1_Gain;                /* Expression: 1
                                        * '<S5>/plant u_1'
                                        */
  real_T plantu_2_Gain;                /* Expression: 1
                                        * '<S5>/plant u_2'
                                        */
  real_T plantu_3_Gain;                /* Expression: 1
                                        * '<S5>/plant u_3'
                                        */
  real_T plantu_4_Gain;                /* Expression: 1
                                        * '<S5>/plant u_4'
                                        */
  real_T plantu_5_Gain;                /* Expression: 1
                                        * '<S5>/plant u_5'
                                        */
  real_T plantBTpower_Gain;            /* Expression: 1
                                        * '<S5>/plant BT power'
                                        */
  real_T plantVSPspeed_Gain;           /* Expression: 1
                                        * '<S5>/plant VSP speed'
                                        */
  real_T EnableCSE1_Value;             /* Expression: 0
                                        * '<S5>/Enable CSE1'
                                        */
  real_T eta_psi_Gain;                 /* Expression: 1
                                        * '<Root>/eta_psi'
                                        */
  real_T eta_psid_Gain;                /* Expression: 1
                                        * '<Root>/eta_psid'
                                        */
  real_T eta_x_Gain;                   /* Expression: 1
                                        * '<Root>/eta_x'
                                        */
  real_T eta_xd_Gain;                  /* Expression: 1
                                        * '<Root>/eta_xd'
                                        */
  real_T eta_y_Gain;                   /* Expression: 1
                                        * '<Root>/eta_y'
                                        */
  real_T eta_yd_Gain;                  /* Expression: 1
                                        * '<Root>/eta_yd'
                                        */
  real_T psi_los_Gain_o;               /* Expression: 1
                                        * '<Root>/psi_los'
                                        */
  real_T psi_plot_Gain;                /* Expression: 1
                                        * '<Root>/psi_plot'
                                        */
  real_T q_x_Gain_o;                   /* Expression: 1
                                        * '<Root>/q_x'
                                        */
  real_T q_y_Gain_p;                   /* Expression: 1
                                        * '<Root>/q_y'
                                        */
  real_T x_plot_Gain;                  /* Expression: 1
                                        * '<Root>/x_plot'
                                        */
  real_T y_plot_Gain;                  /* Expression: 1
                                        * '<Root>/y_plot'
                                        */
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T R12_Gain;                     /* Expression: -1
                                        * '<S162>/R12'
                                        */
  real_T R22_Gain;                     /* Expression: 1
                                        * '<S162>/R22'
                                        */
  real_T _Value_i;                     /* Expression: 0
                                        * '<S164>/0'
                                        */
  real_T S12_Gain_o;                   /* Expression: -1
                                        * '<S164>/S12'
                                        */
  real_T _Value_h;                     /* Expression: 0
                                        * '<S165>/0'
                                        */
  real_T S12_Gain_f;                   /* Expression: -1
                                        * '<S165>/S12'
                                        */
  real_T SITPWM0BT_P1;                 /* Expression: width
                                        * '<S204>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S204>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S204>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S204>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S204>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S204>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S204>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S204>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S204>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S204>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S204>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S204>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S204>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_i;             /* Expression: 0
                                        * '<S204>/Constant'
                                        */
  real_T Constant1_Value_j;            /* Expression: 0
                                        * '<S204>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S204>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S205>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S205>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S205>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S205>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S205>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S205>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S205>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S205>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S205>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S205>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S205>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S205>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S205>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S205>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S205>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S205>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S205>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S205>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S205>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S205>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S205>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S205>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S205>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S205>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S205>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S205>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S205>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S205>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S205>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S205>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S205>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S205>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S205>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S205>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S205>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S205>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S205>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S205>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S205>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S205>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S205>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S205>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S205>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S205>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S205>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S205>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S205>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S205>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S205>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S205>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S205>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S205>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S205>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S205>/VSPS Starboard'
                                        */
  real_T N_r_Value_e;                  /* Expression: -1.900
                                        * '<S210>/N_r'
                                        */
  real_T N_r_Gain_f;                   /* Expression: -1
                                        * '<S210>/-N_r'
                                        */
  real_T N_v_Value_k;                  /* Expression: 0.18140
                                        * '<S210>/N_v'
                                        */
  real_T N_v_Gain_k;                   /* Expression: -1
                                        * '<S210>/-N_v'
                                        */
  real_T X_u_Value_l;                  /* Expression: -0.59739
                                        * '<S210>/X_u'
                                        */
  real_T X_u_Gain_k;                   /* Expression: -1
                                        * '<S210>/-X_u'
                                        */
  real_T Y_v_Value_n;                  /* Expression: -3.50625
                                        * '<S210>/Y_v'
                                        */
  real_T Y_v_Gain_p;                   /* Expression: -1
                                        * '<S210>/-Y_v'
                                        */
  real_T Y_r_Value_o;                  /* Expression: -7.250
                                        * '<S210>/Y_r'
                                        */
  real_T Y_vr_Gain_c;                  /* Expression: -1
                                        * '<S210>/-Y_vr'
                                        */
  real_T D_L_12_Value_k;               /* Expression: 0
                                        * '<S210>/D_L_12'
                                        */
  real_T D_L_13_Value_c;               /* Expression: 0
                                        * '<S210>/D_L_13'
                                        */
  real_T D_L_21_Value_i;               /* Expression: 0
                                        * '<S210>/D_L_21'
                                        */
  real_T D_L_31_Value_h;               /* Expression: 0
                                        * '<S210>/D_L_31'
                                        */
  real_T psi_0_Value;                  /* Expression: 0
                                        * '<S211>/psi_0'
                                        */
  real_T x_0_Value;                    /* Expression: 0
                                        * '<S211>/x_0'
                                        */
  real_T y_0_Value;                    /* Expression: 0
                                        * '<S211>/y_0'
                                        */
  real_T r_0_Value;                    /* Expression: 0
                                        * '<S212>/r_0'
                                        */
  real_T u_0_Value;                    /* Expression: 0
                                        * '<S212>/u_0'
                                        */
  real_T v_0_Value;                    /* Expression: 0
                                        * '<S212>/v_0'
                                        */
  real_T ResetLinearSimulatorintegrator_;/* Expression: 0
                                          * '<S209>/Reset Linear Simulator integrator'
                                          */
  real_T I_z_Value_e;                  /* Expression: 1.760
                                        * '<S213>/I_z'
                                        */
  real_T m_Value_f;                    /* Expression: 17.6
                                        * '<S213>/m'
                                        */
  real_T X_udot_Value_l;               /* Expression: -2.0
                                        * '<S213>/X_udot'
                                        */
  real_T M_21_Value_h;                 /* Expression: 0
                                        * '<S213>/M_21'
                                        */
  real_T M_31_Value_o;                 /* Expression: 0
                                        * '<S213>/M_31'
                                        */
  real_T M_12_Value_n;                 /* Expression: 0
                                        * '<S213>/M_12'
                                        */
  real_T Y_vdot_Value_n;               /* Expression: -10.0
                                        * '<S213>/Y_vdot'
                                        */
  real_T x_g_Value_g;                  /* Expression: 0.03
                                        * '<S213>/x_g'
                                        */
  real_T N_vdot_Value_d;               /* Expression: -0.0
                                        * '<S213>/N_vdot'
                                        */
  real_T M_13_Value_f;                 /* Expression: 0
                                        * '<S213>/M_13'
                                        */
  real_T Y_rdot_Value_e;               /* Expression: 0.0
                                        * '<S213>/Y_rdot'
                                        */
  real_T N_rdot_Value_p;               /* Expression: -1.0
                                        * '<S213>/N_rdot'
                                        */
  real_T R31_Value_m;                  /* Expression: 0
                                        * '<S214>/R31'
                                        */
  real_T R32_Value_h;                  /* Expression: 0
                                        * '<S214>/R32'
                                        */
  real_T R13_Value_b;                  /* Expression: 0
                                        * '<S214>/R13'
                                        */
  real_T R23_Value_e;                  /* Expression: 0
                                        * '<S214>/R23'
                                        */
  real_T R33_Value_c;                  /* Expression: 1
                                        * '<S214>/R33'
                                        */
  real_T eta_surge_hil_Gain;           /* Expression: 1
                                        * '<S202>/eta_surge_hil'
                                        */
  real_T eta_sway_hil_Gain;            /* Expression: 1
                                        * '<S202>/eta_sway_hil'
                                        */
  real_T eta_yaw_hil_Gain;             /* Expression: 1
                                        * '<S202>/eta_yaw_hil'
                                        */
  real_T etadot_surge_hil_Gain;        /* Expression: 1
                                        * '<S202>/etadot_surge_hil'
                                        */
  real_T etadot_sway_hil_Gain;         /* Expression: 1
                                        * '<S202>/etadot_sway_hil'
                                        */
  real_T etadot_yaw_hil_Gain;          /* Expression: 1
                                        * '<S202>/etadot_yaw_hil'
                                        */
  real_T nu_surge_hil_Gain;            /* Expression: 1
                                        * '<S202>/nu_surge_hil'
                                        */
  real_T nu_sway_hil_Gain;             /* Expression: 1
                                        * '<S202>/nu_sway_hil'
                                        */
  real_T nu_yaw_hil_Gain;              /* Expression: 1
                                        * '<S202>/nu_yaw_hil'
                                        */
  uint8_T Gain_Gain_gz;                /* Computed Parameter: Gain
                                        * '<S17>/Gain'
                                        */
  uint8_T Gain1_Gain_a;                /* Computed Parameter: Gain
                                        * '<S17>/Gain1'
                                        */
  uint8_T Gain_Gain_o;                 /* Computed Parameter: Gain
                                        * '<S18>/Gain'
                                        */
  uint8_T Gain1_Gain_b;                /* Computed Parameter: Gain
                                        * '<S18>/Gain1'
                                        */
  uint8_T Gain_Gain_o1;                /* Computed Parameter: Gain
                                        * '<S19>/Gain'
                                        */
  uint8_T Gain1_Gain_h;                /* Computed Parameter: Gain
                                        * '<S19>/Gain1'
                                        */
  uint8_T Gain_Gain_fc;                /* Computed Parameter: Gain
                                        * '<S20>/Gain'
                                        */
  uint8_T Gain1_Gain_bf;               /* Computed Parameter: Gain
                                        * '<S20>/Gain1'
                                        */
  uint8_T Gain_Gain_k;                 /* Computed Parameter: Gain
                                        * '<S21>/Gain'
                                        */
  uint8_T Gain1_Gain_n;                /* Computed Parameter: Gain
                                        * '<S21>/Gain1'
                                        */
  uint8_T Gain_Gain_i;                 /* Computed Parameter: Gain
                                        * '<S73>/Gain'
                                        */
  uint8_T Gain1_Gain_j;                /* Computed Parameter: Gain
                                        * '<S73>/Gain1'
                                        */
  uint8_T Gain_Gain_l1;                /* Computed Parameter: Gain
                                        * '<S74>/Gain'
                                        */
  uint8_T Gain1_Gain_l;                /* Computed Parameter: Gain
                                        * '<S74>/Gain1'
                                        */
  uint8_T Gain_Gain_bo;                /* Computed Parameter: Gain
                                        * '<S75>/Gain'
                                        */
  uint8_T Gain1_Gain_mu;               /* Computed Parameter: Gain
                                        * '<S75>/Gain1'
                                        */
  uint8_T Gain_Gain_mw;                /* Computed Parameter: Gain
                                        * '<S76>/Gain'
                                        */
  uint8_T Gain1_Gain_bp;               /* Computed Parameter: Gain
                                        * '<S76>/Gain1'
                                        */
  uint8_T Gain_Gain_op;                /* Computed Parameter: Gain
                                        * '<S77>/Gain'
                                        */
  uint8_T Gain1_Gain_ma;               /* Computed Parameter: Gain
                                        * '<S77>/Gain1'
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
    real_T odeY[17];
    real_T odeF[6][17];
    ODE5_IntgData intgData;
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

/* Constant parameters (auto storage) */
extern const ConstParam_LgV2 LgV2_ConstP;

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
 * '<S6>'   : LgV2/Control Systems/DP control
 * '<S7>'   : LgV2/Control Systems/LgV design 2
 * '<S8>'   : LgV2/Control Systems/PS3 input
 * '<S9>'   : LgV2/Control Systems/PS3 u input control
 * '<S10>'  : LgV2/Control Systems/DP control/DP controller
 * '<S11>'  : LgV2/Control Systems/DP control/Thruster allocation
 * '<S12>'  : LgV2/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1
 * '<S13>'  : LgV2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]
 * '<S14>'  : LgV2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1
 * '<S15>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act
 * '<S16>'  : LgV2/Control Systems/DP control/Thruster allocation/tau to f_act
 * '<S17>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S18>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S19>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S20>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S21>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S22>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S23>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S24>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S25>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S26>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1
 * '<S27>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S28>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S29>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S30>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S31>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S32>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S33>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S34>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S35>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S36>'  : LgV2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S37>'  : LgV2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e
 * '<S38>'  : LgV2/Control Systems/LgV design 2/Auxilary functions g_q
 * '<S39>'  : LgV2/Control Systems/LgV design 2/Auxiliary function g_s
 * '<S40>'  : LgV2/Control Systems/LgV design 2/Control law
 * '<S41>'  : LgV2/Control Systems/LgV design 2/Gamma_q
 * '<S42>'  : LgV2/Control Systems/LgV design 2/Integral action state
 * '<S43>'  : LgV2/Control Systems/LgV design 2/K_d
 * '<S44>'  : LgV2/Control Systems/LgV design 2/K_i
 * '<S45>'  : LgV2/Control Systems/LgV design 2/K_p
 * '<S46>'  : LgV2/Control Systems/LgV design 2/M
 * '<S47>'  : LgV2/Control Systems/LgV design 2/R(psi)
 * '<S48>'  : LgV2/Control Systems/LgV design 2/R^T
 * '<S49>'  : LgV2/Control Systems/LgV design 2/S(r)
 * '<S50>'  : LgV2/Control Systems/LgV design 2/S^T
 * '<S51>'  : LgV2/Control Systems/LgV design 2/Thruster allocation
 * '<S52>'  : LgV2/Control Systems/LgV design 2/Update laws
 * '<S53>'  : LgV2/Control Systems/LgV design 2/V_1^q
 * '<S54>'  : LgV2/Control Systems/LgV design 2/Virtual control
 * '<S55>'  : LgV2/Control Systems/LgV design 2/alpha^q
 * '<S56>'  : LgV2/Control Systems/LgV design 2/alpha^s
 * '<S57>'  : LgV2/Control Systems/LgV design 2/sigma eq
 * '<S58>'  : LgV2/Control Systems/LgV design 2/z_1 eq
 * '<S59>'  : LgV2/Control Systems/LgV design 2/z_2 eq
 * '<S60>'  : LgV2/Control Systems/LgV design 2/Auxilary functions g_q/g_q eq
 * '<S61>'  : LgV2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq
 * '<S62>'  : LgV2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^s eq
 * '<S63>'  : LgV2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^t eq
 * '<S64>'  : LgV2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/f_q^T
 * '<S65>'  : LgV2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T
 * '<S66>'  : LgV2/Control Systems/LgV design 2/Auxiliary function g_s/g_s eq
 * '<S67>'  : LgV2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq
 * '<S68>'  : LgV2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq
 * '<S69>'  : LgV2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^t eq
 * '<S70>'  : LgV2/Control Systems/LgV design 2/Control law/D_L
 * '<S71>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act
 * '<S72>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/tau to f_act
 * '<S73>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S74>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S75>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S76>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S77>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S78>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S79>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S80>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S81>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S82>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1
 * '<S83>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S84>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S85>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S86>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S87>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S88>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S89>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S90>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S91>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S92>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S93>'  : LgV2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e
 * '<S94>'  : LgV2/Control Systems/LgV design 2/Update laws/Transpose
 * '<S95>'  : LgV2/Control Systems/LgV design 2/Update laws/q_0
 * '<S96>'  : LgV2/Control Systems/LgV design 2/V_1^q/Transpose
 * '<S97>'  : LgV2/Control Systems/LgV design 2/Virtual control/I
 * '<S98>'  : LgV2/Control Systems/LgV design 2/alpha^q/I
 * '<S99>'  : LgV2/Control Systems/LgV design 2/alpha^s/I
 * '<S100>' : LgV2/Control Systems/LgV design 2/sigma eq/I
 * '<S101>' : LgV2/Control Systems/LgV design 2/z_1 eq/heading to pipi
 * '<S102>' : LgV2/Control Systems/LgV design 2/z_1 eq/heading to pipi1
 * '<S103>' : LgV2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi
 * '<S104>' : LgV2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Degrees to Radians
 * '<S105>' : LgV2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Radians to Degrees
 * '<S106>' : LgV2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi
 * '<S107>' : LgV2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Degrees to Radians
 * '<S108>' : LgV2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Radians to Degrees
 * '<S109>' : LgV2/Control Systems/PS3 u input control/Subsystem
 * '<S110>' : LgV2/Control Systems/PS3 u input control/Subsystem/f_act to tau
 * '<S111>' : LgV2/Control Systems/PS3 u input control/Subsystem/u_act to f_act
 * '<S112>' : LgV2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e
 * '<S113>' : LgV2/Guidance Systems/DP
 * '<S114>' : LgV2/Guidance Systems/Path-following
 * '<S115>' : LgV2/Guidance Systems/Path-following/Heading
 * '<S116>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight
 * '<S117>' : LgV2/Guidance Systems/Path-following/Path
 * '<S118>' : LgV2/Guidance Systems/Path-following/Speed assigment
 * '<S119>' : LgV2/Guidance Systems/Path-following/Heading/psi_d eq
 * '<S120>' : LgV2/Guidance Systems/Path-following/Heading/psi_d^s eq
 * '<S121>' : LgV2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq
 * '<S122>' : LgV2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi
 * '<S123>' : LgV2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians
 * '<S124>' : LgV2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees
 * '<S125>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector
 * '<S126>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot
 * '<S127>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot
 * '<S128>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot
 * '<S129>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading
 * '<S130>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals
 * '<S131>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I
 * '<S132>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq
 * '<S133>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq
 * '<S134>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq
 * '<S135>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq
 * '<S136>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq
 * '<S137>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq
 * '<S138>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq
 * '<S139>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq
 * '<S140>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq
 * '<S141>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq
 * '<S142>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq
 * '<S143>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose
 * '<S144>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose
 * '<S145>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1
 * '<S146>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2
 * '<S147>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq
 * '<S148>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq
 * '<S149>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq
 * '<S150>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq
 * '<S151>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq
 * '<S152>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq
 * '<S153>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1
 * '<S154>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2
 * '<S155>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3
 * '<S156>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians
 * '<S157>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees
 * '<S158>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians
 * '<S159>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees
 * '<S160>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians
 * '<S161>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees
 * '<S162>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2
 * '<S163>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2^T
 * '<S164>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2
 * '<S165>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)
 * '<S166>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T
 * '<S167>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2^T
 * '<S168>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq
 * '<S169>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq
 * '<S170>' : LgV2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq
 * '<S171>' : LgV2/Guidance Systems/Path-following/Path/Ellipse path
 * '<S172>' : LgV2/Guidance Systems/Path-following/Path/Path Switch workaround
 * '<S173>' : LgV2/Guidance Systems/Path-following/Path/Straight path
 * '<S174>' : LgV2/Guidance Systems/Path-following/Path/saturation
 * '<S175>' : LgV2/Guidance Systems/Path-following/Path/Ellipse path/p_d eq
 * '<S176>' : LgV2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq
 * '<S177>' : LgV2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq
 * '<S178>' : LgV2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq
 * '<S179>' : LgV2/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq
 * '<S180>' : LgV2/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq/Transpose
 * '<S181>' : LgV2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor
 * '<S182>' : LgV2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor
 * '<S183>' : LgV2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor
 * '<S184>' : LgV2/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor
 * '<S185>' : LgV2/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor
 * '<S186>' : LgV2/Guidance Systems/Path-following/Path/Straight path/p_d eq
 * '<S187>' : LgV2/Guidance Systems/Path-following/Path/Straight path/p_d^s eq
 * '<S188>' : LgV2/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq
 * '<S189>' : LgV2/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/p_d^s^T
 * '<S190>' : LgV2/Guidance Systems/Path-following/Path/saturation/Saturation x
 * '<S191>' : LgV2/Guidance Systems/Path-following/Path/saturation/Saturation y
 * '<S192>' : LgV2/Guidance Systems/Path-following/Speed assigment/v_s eq
 * '<S193>' : LgV2/Guidance Systems/Path-following/Speed assigment/v_s^s eq
 * '<S194>' : LgV2/Guidance Systems/Path-following/Speed assigment/v_s^t eq
 * '<S195>' : LgV2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/p_d^s^T
 * '<S196>' : LgV2/HMI/DP Input
 * '<S197>' : LgV2/HMI/Path-following input
 * '<S198>' : LgV2/HMI/DP Input/Degrees to Radians
 * '<S199>' : LgV2/Naviagation Systems/Qualisys 6 DOF
 * '<S200>' : LgV2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix
 * '<S201>' : LgV2/Plants/CSE1
 * '<S202>' : LgV2/Plants/Linear Simulator
 * '<S203>' : LgV2/Plants/saturation
 * '<S204>' : LgV2/Plants/CSE1/Bow Thruster
 * '<S205>' : LgV2/Plants/CSE1/Voith Schneider Propeller
 * '<S206>' : LgV2/Plants/CSE1/Bow Thruster/Saturation Dynamic
 * '<S207>' : LgV2/Plants/CSE1/Bow Thruster/Saturation Dynamic1
 * '<S208>' : LgV2/Plants/CSE1/Bow Thruster/Saturation Dynamic2
 * '<S209>' : LgV2/Plants/Linear Simulator/Linear Vessel Dynamics
 * '<S210>' : LgV2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L
 * '<S211>' : LgV2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta
 * '<S212>' : LgV2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu
 * '<S213>' : LgV2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv
 * '<S214>' : LgV2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)
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
