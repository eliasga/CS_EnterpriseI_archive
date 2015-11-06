/*
 * NLPIDVersion2.h
 *
 * Real-Time Workshop code generation for Simulink model "NLPIDVersion2.mdl".
 *
 * Model Version              : 1.89
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Mon Mar 24 18:43:48 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_NLPIDVersion2_h_
#define RTW_HEADER_NLPIDVersion2_h_
#ifndef NLPIDVersion2_COMMON_INCLUDES_
# define NLPIDVersion2_COMMON_INCLUDES_
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
#endif                                 /* NLPIDVersion2_COMMON_INCLUDES_ */

#include "NLPIDVersion2_types.h"

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
#define NLPIDVersion2_rtModel          RT_MODEL_NLPIDVersion2

/* Block signals (auto storage) */
typedef struct {
  real_T Initialpsirad;                /* '<S4>/Initial psi [rad]' */
  real_T Initialxm;                    /* '<S4>/Initial x [m]' */
  real_T Initialym;                    /* '<S4>/Initial y [m]' */
  real_T Initialrrads;                 /* '<S4>/Initial r [rad//s]' */
  real_T Initialums;                   /* '<S4>/Initial u [m//s]' */
  real_T Initialvms;                   /* '<S4>/Initial v [m//s]' */
  real_T xpositionofleftanalogstick11; /* '<S6>/ScalingLX' */
  real_T ypositionofleftanalogstick11; /* '<S6>/ScalingLY' */
  real_T xpositionofrightanalogstick11;/* '<S6>/Scaling_RX' */
  real_T ypositionofrightanalogstick11;/* '<S6>/ScalingRY' */
  real_T Gain1;                        /* '<S12>/Gain1' */
  real_T ux3[9];                       /* '<S13>/[3x3]' */
  real_T ux3_a[9];                     /* '<S14>/[3x3]' */
  real_T ux3_i[9];                     /* '<S15>/[3x3]' */
  real_T ux2[4];                       /* '<S16>/[2x2]' */
  real_T Initialq_x;                   /* '<S9>/Initial q_x' */
  real_T Initialq_y;                   /* '<S9>/Initial q_y' */
  real_T Initials;                     /* '<S9>/Initial s' */
  real_T ux3_ip[9];                    /* '<S17>/[3x3]' */
  real_T ux3_p[9];                     /* '<S18>/[3x3]' */
  real_T ux3_g[9];                     /* '<S19>/[3x3]' */
  real_T kappa_1;                      /* '<S9>/kappa_1' */
  real_T l_x1;                         /* '<S28>/-l_x1' */
  real_T l_x2;                         /* '<S28>/-l_x2' */
  real_T l_y2;                         /* '<S28>/-l_y2' */
  real_T x5[15];                       /* '<S28>/3x5' */
  real_T N_r;                          /* '<S27>/-N_r' */
  real_T N_v;                          /* '<S27>/-N_v' */
  real_T X_u;                          /* '<S27>/-X_u' */
  real_T Y_v;                          /* '<S27>/-Y_v' */
  real_T Y_vr;                         /* '<S27>/-Y_vr' */
  real_T LinearDampningmatrix[9];      /* '<S27>/Linear Dampning matrix' */
  real_T M_11;                         /* '<S26>/M_11' */
  real_T M_22;                         /* '<S26>/M_22' */
  real_T mx_g;                         /* '<S26>/m x_g' */
  real_T M_32;                         /* '<S26>/M_32' */
  real_T M_23;                         /* '<S26>/M_23' */
  real_T M_33;                         /* '<S26>/M_33' */
  real_T x3[9];                        /* '<S26>/3x3' */
  real_T l_x1_f;                       /* '<S74>/-l_x1' */
  real_T l_y2_d;                       /* '<S74>/-l_y2' */
  real_T l_x2_d;                       /* '<S74>/-l_x2' */
  real_T x5_p[15];                     /* '<S74>/3x5' */
  real_T u_1;                          /* '<S32>/PS3 u_1' */
  real_T u_1tof_1;                     /* '<S73>/u_1 to f_1' */
  real_T u_2;                          /* '<S32>/PS3 u_2' */
  real_T u_2tof_2;                     /* '<S73>/u_2 to f_2' */
  real_T u_3;                          /* '<S32>/PS3 u_3' */
  real_T u_3tof_3;                     /* '<S73>/u_3 to f_3' */
  real_T u_4;                          /* '<S32>/PS3 u_4' */
  real_T u_4tof_4;                     /* '<S73>/u_4 to f_4' */
  real_T BowThrusterdirection;         /* '<S32>/Add' */
  real_T u_5;                          /* '<S32>/PS3 u_5' */
  real_T u_5tof_5;                     /* '<S73>/u_5 to f_5' */
  real_T TmpHiddenBufferAtProductInport2[5];/* 'synthesized block' */
  real_T Product[3];                   /* '<S72>/Product' */
  real_T QTMIn[9];                     /* '<S166>/QTM In' */
  real_T QTMIn3xcoordmm;               /* '<S166>/QTM In3 x-coord [mm]' */
  real_T mm2mx;                        /* '<S166>/mm2m x' */
  real_T QTMIn4ycoordmm;               /* '<S166>/QTM In4 y-coord [mm]' */
  real_T mm2my;                        /* '<S166>/mm2m y' */
  real_T QTMIn6yawdeg;                 /* '<S166>/QTM In6 yaw [deg]' */
  real_T d2ryaw;                       /* '<S166>/d2r yaw' */
  real_T etaSwitch[3];                 /* '<S167>/eta Switch' */
  real_T psi;                          /* '<S30>/yaw angle' */
  real_T Saturation;                   /* '<S36>/Saturation' */
  real_T Sign;                         /* '<S36>/Sign' */
  real_T Gain;                         /* '<S36>/Gain' */
  real_T Sum1;                         /* '<S36>/Sum1' */
  real_T MathFunction;                 /* '<S36>/Math Function' */
  real_T Sum;                          /* '<S36>/Sum' */
  real_T Sum2[3];                      /* '<S30>/Sum2' */
  real_T Saturation_d;                 /* '<S35>/Saturation' */
  real_T Sign_h;                       /* '<S35>/Sign' */
  real_T Gain_g;                       /* '<S35>/Gain' */
  real_T Sum1_j;                       /* '<S35>/Sum1' */
  real_T MathFunction_a;               /* '<S35>/Math Function' */
  real_T Sum_l;                        /* '<S35>/Sum' */
  real_T Row1;                         /* '<S34>/Row1' */
  real_T Row2;                         /* '<S34>/Row2' */
  real_T Row3;                         /* '<S34>/Row3' */
  real_T TmpHiddenBufferAtProductInpor_e[3];/* '<S30>/Transposed rotation  matrix in yaw1' */
  real_T Product_i[3];                 /* '<S30>/Product' */
  real_T Integrator[3];                /* '<S30>/Integrator' */
  real_T Product1[3];                  /* '<S30>/Product1' */
  real_T Sum3[3];                      /* '<S30>/Sum3' */
  real_T QTMIn8rolldeg;                /* '<S166>/QTM In8 roll [deg]' */
  real_T d2rroll;                      /* '<S166>/d2r roll' */
  real_T QTMIn7pitchdeg;               /* '<S166>/QTM In7 pitch [deg]' */
  real_T d2rpitch;                     /* '<S166>/d2r pitch' */
  real_T sintheta[3];                  /* '<S168>/sin(theta)' */
  real_T costheta[3];                  /* '<S168>/cos(theta)' */
  real_T R11;                          /* '<S168>/R11' */
  real_T R21;                          /* '<S168>/R21 ' */
  real_T R31;                          /* '<S168>/R31 ' */
  real_T R12;                          /* '<S168>/R12' */
  real_T R22;                          /* '<S168>/R22' */
  real_T R32;                          /* '<S168>/R32' */
  real_T R13;                          /* '<S168>/R13' */
  real_T R23;                          /* '<S168>/R23' */
  real_T R33;                          /* '<S168>/R33' */
  real_T Reshape9x13x3[9];             /* '<S168>/Reshape 9x1->3x3' */
  real_T MatrixConcatenate2[36];       /* '<S166>/Matrix Concatenate2' */
  real_T QTMIn5zcoordmm;               /* '<S166>/QTM In5 z-coord [mm]' */
  real_T mm2mz;                        /* '<S166>/mm2m z' */
  real_T Derivative[6];                /* '<S166>/Derivative' */
  real_T Product_l[6];                 /* '<S166>/Product' */
  real_T nuSwitch[3];                  /* '<S167>/nu Switch' */
  real_T Product2[3];                  /* '<S30>/Product2' */
  real_T Sum1_f[3];                    /* '<S30>/Sum1' */
  real_T R11_h;                        /* '<S40>/R11' */
  real_T R21_c;                        /* '<S40>/R21' */
  real_T R12_p;                        /* '<S40>/R12' */
  real_T u;                            /* '<S40>/-1' */
  real_T R22_p;                        /* '<S40>/R22' */
  real_T Rpsi[9];                      /* '<S40>/R(psi)' */
  real_T MathFunction_m[9];            /* '<S62>/Math Function' */
  real_T Saturation_p;                 /* '<S69>/Saturation' */
  real_T Sign_f;                       /* '<S69>/Sign' */
  real_T Gain_f;                       /* '<S69>/Gain' */
  real_T Sum1_b;                       /* '<S69>/Sum1' */
  real_T MathFunction_p;               /* '<S69>/Math Function' */
  real_T Sum_p;                        /* '<S69>/Sum' */
  real_T Integrator_k[2];              /* '<S41>/Integrator' */
  real_T x_2x_1;                       /* '<S159>/x_2 - x_1' */
  real_T y_2y_1;                       /* '<S159>/y_2 - y_1' */
  real_T TmpHiddenBufferAtProductInpor_b[2];/* 'synthesized block' */
  real_T Saturation_i;                 /* '<S142>/Saturation' */
  real_T RoundingFunction;             /* '<S142>/Rounding Function' */
  real_T Product_c[2];                 /* '<S152>/Product' */
  real_T Integrator1;                  /* '<S41>/Integrator1' */
  real_T Product2_i;                   /* '<S145>/Product2' */
  real_T sins;                         /* '<S145>/sin(s)' */
  real_T Product_id;                   /* '<S145>/Product' */
  real_T Gain_k;                       /* '<S145>/Gain' */
  real_T coss;                         /* '<S145>/cos(s)' */
  real_T Product1_p;                   /* '<S145>/Product1' */
  real_T TmpHiddenBufferAtProductInpor_n[2];/* 'synthesized block' */
  real_T Subract;                      /* '<S152>/Subract' */
  real_T Product1_d[2];                /* '<S152>/Product1' */
  real_T Add[2];                       /* '<S152>/Add' */
  real_T TrigonometricFunction;        /* '<S97>/Trigonometric Function' */
  real_T Saturation_o;                 /* '<S100>/Saturation' */
  real_T Sign_c;                       /* '<S100>/Sign' */
  real_T Gain_a;                       /* '<S100>/Gain' */
  real_T Sum1_fu;                      /* '<S100>/Sum1' */
  real_T MathFunction_c;               /* '<S100>/Math Function' */
  real_T Sum_pi;                       /* '<S100>/Sum' */
  real_T Saturation_n;                 /* '<S128>/Saturation' */
  real_T Sign_hb;                      /* '<S128>/Sign' */
  real_T Gain_l;                       /* '<S128>/Gain' */
  real_T Sum1_n;                       /* '<S128>/Sum1' */
  real_T MathFunction_me;              /* '<S128>/Math Function' */
  real_T Sum_e;                        /* '<S128>/Sum' */
  real_T MathFunction_o[4];            /* '<S132>/Math Function' */
  real_T x_2x_1_j;                     /* '<S158>/x_2 - x_1' */
  real_T x_2x_1s;                      /* '<S158>/(x_2 - x_1) * s' */
  real_T x_2x_1sx_1;                   /* '<S158>/(x_2 - x_1) * s + x_1' */
  real_T y_2y_1_j;                     /* '<S158>/y_2 - y_1' */
  real_T y_2y_1s;                      /* '<S158>/(y_2 - y_1) * s' */
  real_T y_2y_1sy_1;                   /* '<S158>/(y_2 - y_1) * s + y_1' */
  real_T Product_b[2];                 /* '<S151>/Product' */
  real_T Product2_n;                   /* '<S144>/Product2' */
  real_T coss_p;                       /* '<S144>/cos(s)' */
  real_T Product_bm;                   /* '<S144>/Product' */
  real_T Add_p;                        /* '<S144>/Add' */
  real_T sins_k;                       /* '<S144>/sin(s)' */
  real_T Product1_e;                   /* '<S144>/Product1' */
  real_T Add1;                         /* '<S144>/Add1' */
  real_T Subract_c;                    /* '<S151>/Subract' */
  real_T Product1_m[2];                /* '<S151>/Product1' */
  real_T Add_n[2];                     /* '<S151>/Add' */
  real_T Switch;                       /* '<S156>/Switch' */
  real_T Switch2;                      /* '<S156>/Switch2' */
  real_T Switch_e;                     /* '<S157>/Switch' */
  real_T Switch2_b;                    /* '<S157>/Switch2' */
  real_T Subtract[2];                  /* '<S94>/Subtract' */
  real_T epsilon[2];                   /* '<S105>/epsilon' */
  real_T MultiportSelector;            /* '<S105>/Multiport Selector' */
  real_T TrigonometricFunction_m;      /* '<S122>/Trigonometric Function' */
  real_T Saturation_ns;                /* '<S129>/Saturation' */
  real_T Sign_cn;                      /* '<S129>/Sign' */
  real_T Gain_h;                       /* '<S129>/Gain' */
  real_T Sum1_n1;                      /* '<S129>/Sum1' */
  real_T MathFunction_c5;              /* '<S129>/Math Function' */
  real_T Sum_o;                        /* '<S129>/Sum' */
  real_T Subtract_h;                   /* '<S122>/Subtract' */
  real_T Saturation_a;                 /* '<S130>/Saturation' */
  real_T Sign_n;                       /* '<S130>/Sign' */
  real_T Gain_ai;                      /* '<S130>/Gain' */
  real_T Sum1_c;                       /* '<S130>/Sum1' */
  real_T MathFunction_g;               /* '<S130>/Math Function' */
  real_T Sum_d;                        /* '<S130>/Sum' */
  real_T VectorConcatenate[3];         /* '<S106>/Vector Concatenate' */
  real_T Subtract_f[3];                /* '<S44>/Subtract' */
  real_T Saturation_o4;                /* '<S70>/Saturation' */
  real_T Sign_j;                       /* '<S70>/Sign' */
  real_T Gain_ag;                      /* '<S70>/Gain' */
  real_T Sum1_d;                       /* '<S70>/Sum1' */
  real_T MathFunction_j;               /* '<S70>/Math Function' */
  real_T Sum_a;                        /* '<S70>/Sum' */
  real_T TmpHiddenBufferAtProductInport3[3];/* 'synthesized block' */
  real_T Product_k[3];                 /* '<S59>/Product' */
  real_T Integrator_kk[3];             /* '<S46>/Integrator' */
  real_T Product1_k[3];                /* '<S59>/Product1' */
  real_T f_qx;                         /* '<S107>/f_qx' */
  real_T f_qy;                         /* '<S107>/f_qy' */
  real_T TmpHiddenBufferAtProductInport1[2];/* 'synthesized block' */
  real_T Product_kv[2];                /* '<S107>/Product' */
  real_T Delta2;                       /* '<S123>/Delta^2' */
  real_T epsilon_n2;                   /* '<S123>/epsilon_n^2' */
  real_T Add_o;                        /* '<S123>/Add' */
  real_T Divide;                       /* '<S123>/Divide' */
  real_T MultiportSelector1[2];        /* '<S105>/Multiport Selector1' */
  real_T Product_ch[2];                /* '<S123>/Product' */
  real_T u_o[2];                       /* '<S123>/-1' */
  real_T VectorConcatenate_p[3];       /* '<S47>/Vector Concatenate' */
  real_T Product_ca[2];                /* '<S153>/Product' */
  real_T Product2_b;                   /* '<S146>/Product2' */
  real_T coss_f;                       /* '<S146>/cos(s)' */
  real_T MathFunction_mn;              /* '<S146>/Math Function' */
  real_T Product_a;                    /* '<S146>/Product' */
  real_T Gain_i;                       /* '<S146>/Gain' */
  real_T sins_m;                       /* '<S146>/sin(s)' */
  real_T Product1_o;                   /* '<S146>/Product1' */
  real_T Gain1_h;                      /* '<S146>/Gain1' */
  real_T Subract_j;                    /* '<S153>/Subract' */
  real_T Product1_kh[2];               /* '<S153>/Product1' */
  real_T Add_l[2];                     /* '<S153>/Add' */
  real_T x_dsy_ds2;                    /* '<S98>/x_d^s * y_d^s^2' */
  real_T x_ds2y_ds;                    /* '<S98>/x_d^s^2 * y_d^s' */
  real_T x_dsy_ds2x_ds2y_ds;           /* '<S98>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
  real_T x_ds2;                        /* '<S98>/( x_d^s )^2' */
  real_T y_ds2;                        /* '<S98>/( y_d^s )^2' */
  real_T x_ds2y_ds2;                   /* '<S98>/( x_d^s )^2 + ( y_d^s )^2' */
  real_T Divide_l;                     /* '<S98>/Divide' */
  real_T Delta2_n;                     /* '<S126>/Delta^2' */
  real_T epsilon_n2_c;                 /* '<S126>/epsilon_n^2' */
  real_T Add_m;                        /* '<S126>/Add' */
  real_T Divide_i;                     /* '<S126>/Divide' */
  real_T MathFunction_d[4];            /* '<S136>/Math Function' */
  real_T Product_d[2];                 /* '<S138>/Product' */
  real_T Product1_h[2];                /* '<S138>/Product1' */
  real_T Subtract1[2];                 /* '<S138>/Subtract1' */
  real_T MultiportSelector2;           /* '<S105>/Multiport Selector2' */
  real_T Product_le;                   /* '<S126>/Product' */
  real_T Subtract_b;                   /* '<S126>/Subtract' */
  real_T epsilon_n2_e;                 /* '<S111>/epsilon_n^2' */
  real_T Delta2_b;                     /* '<S111>/Delta^2' */
  real_T Add_ma;                       /* '<S111>/Add' */
  real_T sqrt_c;                       /* '<S111>/sqrt' */
  real_T Divide_m;                     /* '<S111>/Divide' */
  real_T MathFunction_my[2];           /* '<S161>/Math Function' */
  real_T Product_o;                    /* '<S160>/Product' */
  real_T sqrt_d;                       /* '<S160>/sqrt' */
  real_T Product_j;                    /* '<S155>/Product' */
  real_T MathFunction_e[2];            /* '<S149>/Math Function' */
  real_T Product_j0;                   /* '<S148>/Product' */
  real_T sqrt_b;                       /* '<S148>/sqrt' */
  real_T Subract_m;                    /* '<S155>/Subract' */
  real_T Product1_a;                   /* '<S155>/Product1' */
  real_T Add_pj;                       /* '<S155>/Add' */
  real_T Divide_n;                     /* '<S162>/Divide' */
  real_T Product_h;                    /* '<S111>/Product' */
  real_T MathFunction_pb[2];           /* '<S118>/Math Function' */
  real_T Divide_f[2];                  /* '<S115>/Divide' */
  real_T Product_ar;                   /* '<S115>/Product' */
  real_T Gain_hz;                      /* '<S115>/Gain' */
  real_T Subtract_a;                   /* '<S111>/Subtract' */
  real_T VectorConcatenate_d[3];       /* '<S53>/Vector Concatenate' */
  real_T Add_lh[3];                    /* '<S45>/Add' */
  real_T Product_dv[3];                /* '<S43>/Product' */
  real_T Subtract_e[3];                /* '<S43>/Subtract' */
  real_T Product2_ie[3];               /* '<S59>/Product2' */
  real_T Sum_j[3];                     /* '<S59>/Sum' */
  real_T Product1_al[3];               /* '<S58>/Product1' */
  real_T TrigonometricFunction1;       /* '<S108>/Trigonometric Function1' */
  real_T Gain_e;                       /* '<S108>/Gain' */
  real_T Product1_du[2];               /* '<S108>/Product1' */
  real_T TrigonometricFunction_l;      /* '<S108>/Trigonometric Function' */
  real_T Product2_j[2];                /* '<S108>/Product2' */
  real_T MatrixConcatenate[4];         /* '<S108>/Matrix Concatenate' */
  real_T Product_aw[4];                /* '<S108>/Product' */
  real_T MathFunction_k[2];            /* '<S51>/Math Function' */
  real_T Product2_l;                   /* '<S124>/Product2' */
  real_T MathFunction_h[2];            /* '<S124>/Math Function' */
  real_T Product3[4];                  /* '<S124>/Product3' */
  real_T Product4[4];                  /* '<S124>/Product4' */
  real_T u_m[4];                       /* '<S124>/2' */
  real_T Delta2_g;                     /* '<S124>/Delta^2' */
  real_T epsilon_n2_i;                 /* '<S124>/epsilon_n^2' */
  real_T Add_i;                        /* '<S124>/Add' */
  real_T u_n;                          /* '<S124>/( )^2' */
  real_T Divide_k[4];                  /* '<S124>/Divide' */
  real_T Product1_i[4];                /* '<S124>/Product1' */
  real_T Divide1[4];                   /* '<S124>/Divide1' */
  real_T Subtract_m[4];                /* '<S124>/Subtract' */
  real_T MathFunction_av[4];           /* '<S52>/Math Function' */
  real_T Product_hb[2];                /* '<S48>/Product' */
  real_T Product1_mc[2];               /* '<S48>/Product1' */
  real_T Add_d[2];                     /* '<S48>/Add' */
  real_T MatrixConcatenate_j[6];       /* '<S48>/Matrix Concatenate' */
  real_T Product_f[2];                 /* '<S125>/Product' */
  real_T u_e[2];                       /* '<S125>/2' */
  real_T Delta2_o;                     /* '<S125>/Delta^2' */
  real_T epsilon_n2_ia;                /* '<S125>/epsilon_n^2' */
  real_T Add_ox;                       /* '<S125>/Add' */
  real_T u_og;                         /* '<S125>/( )^2' */
  real_T Divide_e[2];                  /* '<S125>/Divide' */
  real_T Product1_ez[4];               /* '<S137>/Product1' */
  real_T MultiportSelector3[2];        /* '<S105>/Multiport Selector3' */
  real_T Product1_ka[2];               /* '<S125>/Product1' */
  real_T Divide1_a[2];                 /* '<S125>/Divide1' */
  real_T Subtract_n[2];                /* '<S125>/Subtract' */
  real_T Product_b4[2];                /* '<S54>/Product' */
  real_T Product1_ex[2];               /* '<S112>/Product1' */
  real_T epsilon_n2_iw;                /* '<S112>/epsilon_n^2' */
  real_T Delta2_nh;                    /* '<S112>/Delta^2' */
  real_T Add_li;                       /* '<S112>/Add' */
  real_T u2;                           /* '<S112>/^3//2' */
  real_T Divide_b[2];                  /* '<S112>/Divide' */
  real_T Product_cm[2];                /* '<S112>/Product' */
  real_T MathFunction_pj[2];           /* '<S119>/Math Function' */
  real_T Divide_a[2];                  /* '<S116>/Divide' */
  real_T Product_la[2];                /* '<S116>/Product' */
  real_T Gain_p[2];                    /* '<S116>/Gain' */
  real_T Sum_f[2];                     /* '<S112>/Sum' */
  real_T Product1_b[2];                /* '<S54>/Product1' */
  real_T Add_mt[2];                    /* '<S54>/Add' */
  real_T MatrixConcatenate_k[6];       /* '<S54>/Matrix Concatenate' */
  real_T Add_g[6];                     /* '<S64>/Add' */
  real_T Integrator2[2];               /* '<S41>/Integrator2' */
  real_T Add1_f[2];                    /* '<S41>/Add1' */
  real_T Product_ju[3];                /* '<S42>/Product' */
  real_T TrigonometricFunction1_j;     /* '<S109>/Trigonometric Function1' */
  real_T Gain_j;                       /* '<S109>/Gain' */
  real_T Product1_ak;                  /* '<S109>/Product1' */
  real_T TrigonometricFunction_n;      /* '<S109>/Trigonometric Function' */
  real_T Product2_bn;                  /* '<S109>/Product2' */
  real_T TmpHiddenBufferAtProductInpo_ep[2];/* 'synthesized block' */
  real_T Product_an[2];                /* '<S109>/Product' */
  real_T Product_jb;                   /* '<S49>/Product' */
  real_T Product1_aj;                  /* '<S49>/Product1' */
  real_T VectorConcatenate_c[3];       /* '<S49>/Vector Concatenate' */
  real_T Product_bf[2];                /* '<S154>/Product' */
  real_T Product2_e;                   /* '<S147>/Product2' */
  real_T sins3;                        /* '<S147>/sin(s)3' */
  real_T MathFunction_i;               /* '<S147>/Math Function' */
  real_T Product_m;                    /* '<S147>/Product' */
  real_T coss3;                        /* '<S147>/cos(s)3' */
  real_T Product1_ou;                  /* '<S147>/Product1' */
  real_T Gain_n;                       /* '<S147>/Gain' */
  real_T Subract_k;                    /* '<S154>/Subract' */
  real_T Product1_ic[2];               /* '<S154>/Product1' */
  real_T Add_of[2];                    /* '<S154>/Add' */
  real_T x_dsy_ds3;                    /* '<S99>/x_d^s * y_d^s^3 ' */
  real_T x_ds3y_ds;                    /* '<S99>/x_d^s^3 * y_d^s' */
  real_T x_dsy_ds3x_ds3y_ds;           /* '<S99>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
  real_T Product1_dg;                  /* '<S99>/Product1' */
  real_T x_dsx_ds2;                    /* '<S99>/x_d^s * x_d^s^2' */
  real_T y_dsy_ds2;                    /* '<S99>/y_d^s * y_d^s^2' */
  real_T x_dsx_ds2x_ds3y_ds;           /* '<S99>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
  real_T u_k;                          /* '<S99>/+ 2' */
  real_T Product2_ey;                  /* '<S99>/Product2' */
  real_T Subtract_ar;                  /* '<S99>/Subtract' */
  real_T x_ds2y_ds22;                  /* '<S99>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
  real_T Divide_li;                    /* '<S99>/Divide' */
  real_T epsilon_ns2;                  /* '<S127>/(epsilon_n^s)^2' */
  real_T Product_lo;                   /* '<S127>/Product' */
  real_T u_p;                          /* '<S127>/2' */
  real_T Delta2_nhl;                   /* '<S127>/Delta^2' */
  real_T epsilon_n2_n;                 /* '<S127>/epsilon_n^2' */
  real_T Add_dv;                       /* '<S127>/Add' */
  real_T u_d;                          /* '<S127>/( )^2' */
  real_T Divide_ng;                    /* '<S127>/Divide' */
  real_T MathFunction_ce[4];           /* '<S135>/Math Function' */
  real_T Product_mi[4];                /* '<S139>/Product' */
  real_T Add_gb[4];                    /* '<S139>/Add' */
  real_T Product1_ph[2];               /* '<S139>/Product1' */
  real_T Product2_c[2];                /* '<S139>/Product2' */
  real_T u_a[2];                       /* '<S139>/2' */
  real_T Product3_b[2];                /* '<S139>/Product3' */
  real_T Sum_m[2];                     /* '<S139>/Sum' */
  real_T Gain_b[2];                    /* '<S139>/Gain' */
  real_T MultiportSelector4;           /* '<S105>/Multiport Selector4' */
  real_T Product1_mi;                  /* '<S127>/Product1' */
  real_T Divide1_n;                    /* '<S127>/Divide1' */
  real_T Sum_k;                        /* '<S127>/Sum' */
  real_T Product_fu;                   /* '<S55>/Product' */
  real_T MathFunction_pg[2];           /* '<S165>/Math Function' */
  real_T Product1_j;                   /* '<S163>/Product1' */
  real_T p_ds3;                        /* '<S163>/|p_d^s|^3' */
  real_T Divide_lp;                    /* '<S163>/Divide' */
  real_T Product_p;                    /* '<S163>/Product' */
  real_T Gain_o;                       /* '<S163>/Gain' */
  real_T epsilon_n2_p;                 /* '<S113>/epsilon_n^2' */
  real_T Delta2_j;                     /* '<S113>/Delta^2' */
  real_T Add_b;                        /* '<S113>/Add' */
  real_T MathFunction_ds;              /* '<S113>/Math Function' */
  real_T Divide_lpt;                   /* '<S113>/Divide' */
  real_T Product1_ap;                  /* '<S113>/Product1' */
  real_T Product2_e1;                  /* '<S113>/Product2' */
  real_T u2_d;                         /* '<S113>/^3//2' */
  real_T Divide1_no;                   /* '<S113>/Divide1' */
  real_T Product3_m;                   /* '<S113>/Product3' */
  real_T Product1_n;                   /* '<S117>/Product1' */
  real_T MathFunction_il[2];           /* '<S121>/Math Function' */
  real_T Divide2[2];                   /* '<S117>/Divide2' */
  real_T MathFunction_ht[2];           /* '<S120>/Math Function' */
  real_T Product2_e1e[2];              /* '<S117>/Product2' */
  real_T MathFunction_c4;              /* '<S117>/Math Function' */
  real_T Divide1_o[2];                 /* '<S117>/Divide1' */
  real_T Subtract1_j[2];               /* '<S117>/Subtract1' */
  real_T Product_hd;                   /* '<S117>/Product' */
  real_T Subtract_ny;                  /* '<S117>/Subtract' */
  real_T Sum_ax;                       /* '<S113>/Sum' */
  real_T Product1_pf;                  /* '<S55>/Product1' */
  real_T VectorConcatenate_j[3];       /* '<S55>/Vector Concatenate' */
  real_T Add1_d[3];                    /* '<S65>/Add1' */
  real_T Product1_c[3];                /* '<S42>/Product1' */
  real_T TrigonometricFunction_h;      /* '<S110>/Trigonometric Function' */
  real_T TrigonometricFunction1_g;     /* '<S110>/Trigonometric Function1' */
  real_T Derivative_h;                 /* '<S96>/Derivative' */
  real_T Product_ae[2];                /* '<S110>/Product' */
  real_T VectorConcatenate_g[3];       /* '<S50>/Vector Concatenate' */
  real_T epsilon_n2_nb;                /* '<S114>/epsilon_n^2' */
  real_T Delta2_gb;                    /* '<S114>/Delta^2' */
  real_T Add_gm;                       /* '<S114>/Add' */
  real_T sqrt_p;                       /* '<S114>/sqrt' */
  real_T Divide_mc;                    /* '<S114>/Divide' */
  real_T Divide_d;                     /* '<S164>/Divide' */
  real_T Product_e;                    /* '<S114>/Product' */
  real_T VectorConcatenate_o[3];       /* '<S56>/Vector Concatenate' */
  real_T Add_nb[3];                    /* '<S66>/Add' */
  real_T Sum_e2[3];                    /* '<S42>/Sum' */
  real_T Product_d4[3];                /* '<S57>/Product' */
  real_T S12;                          /* '<S60>/S12' */
  real_T Sr[9];                        /* '<S60>/S(r)' */
  real_T MathFunction_n[9];            /* '<S61>/Math Function' */
  real_T Product1_l[3];                /* '<S57>/Product1' */
  real_T Subtract_j[3];                /* '<S57>/Subtract' */
  real_T Sum_fj[3];                    /* '<S39>/Sum' */
  real_T tauSwitch[3];                 /* '<S29>/tau Switch' */
  real_T MatrixConcatenate_b[6];       /* '<S106>/Matrix Concatenate' */
  real_T MathFunction_k1[6];           /* '<S63>/Math Function' */
  real_T Product2_g[2];                /* '<S41>/Product2' */
  real_T Product3_mf[2];               /* '<S41>/Product3' */
  real_T Subtract_as[2];               /* '<S41>/Subtract' */
  real_T Product4_m[2];                /* '<S41>/Product4' */
  real_T Gain_pp[2];                   /* '<S41>/Gain' */
  real_T Product_og[3];                /* '<S46>/Product' */
  real_T Pseudoinverse[15];            /* '<S76>/Pseudoinverse' */
  real_T Product_m2[5];                /* '<S76>/Product' */
  real_T f_1tou_1;                     /* '<S78>/f_1 to u_1' */
  real_T f_2000391;                    /* '<S79>/f_2 < 0.00391' */
  real_T f_2006731f_2000391;           /* '<S79>/f_2 < 0.06731 && f_2 >= 0.00391' */
  real_T f_2006731;                    /* '<S79>/f_2 => 0.06731' */
  real_T MultiportSwitch;              /* '<S79>/Multiport Switch' */
  real_T f_3tou_3;                     /* '<S80>/f_3 to u_3' */
  real_T f_400451;                     /* '<S81>/f_4 < 0.0451' */
  real_T f_400451_o;                   /* '<S81>/f_4 >= 0.0451 ' */
  real_T MultiportSwitch_m;            /* '<S81>/Multiport Switch' */
  real_T DeadZone001;                  /* '<S82>/Dead Zone +-0.01' */
  real_T f_50;                         /* '<S82>/f_5 < 0' */
  real_T f_50_j;                       /* '<S82>/f_5 > 0' */
  real_T MultiportSwitch_d;            /* '<S82>/Multiport Switch' */
  real_T Saturation_j[7];              /* '<S33>/Saturation' */
  real_T QTMIn2Error;                  /* '<S166>/QTM In2 Error' */
  real_T QTMIn9Residual;               /* '<S166>/QTM In9 Residual' */
  real_T Derivative1[3];               /* '<S166>/Derivative1' */
  real_T etadotSwitch[3];              /* '<S167>/etadot Switch' */
  real_T Saturation_ja;                /* '<S171>/Saturation' */
  real_T tauSwitch_m[7];               /* '<S171>/tau Switch' */
  real_T TmpHiddenBufferAtToFileInport1[37];/* 'synthesized block' */
  real_T VectorConcatenate1[3];        /* '<S106>/Vector Concatenate1' */
  real_T QTMIn1FPS;                    /* '<S166>/QTM In1 FPS' */
  real_T SITzAI0;                      /* '<S166>/SIT zAI0' */
  real_T SITzAI1;                      /* '<S166>/SIT zAI1' */
  real_T SITzAI2;                      /* '<S166>/SIT zAI2' */
  real_T Inverse[9];                   /* '<S25>/Inverse' */
  real_T Saturation_ay;                /* '<S172>/Saturation' */
  real_T Saturation1;                  /* '<S172>/Saturation1' */
  real_T Saturation2;                  /* '<S172>/Saturation2' */
  real_T planttau_surge;               /* '<S172>/plant tau_surge' */
  real_T planttau_sway;                /* '<S172>/plant tau_sway' */
  real_T planttau_yaw;                 /* '<S172>/plant tau_yaw' */
  real_T BatteryBowThruster;           /* '<S180>/Battery Bow Thruster' */
  real_T BatteryMain;                  /* '<S180>/Battery Main' */
  real_T BatteryServo;                 /* '<S180>/Battery Servo' */
  real_T omega_qy;                     /* '<S181>/omega_qy' */
  real_T omegaqx;                      /* '<S181>/omegaqx' */
  real_T plantBTpower;                 /* '<S181>/plant BT power' */
  real_T plantVSPspeed;                /* '<S181>/plant VSP speed' */
  real_T plantu_1;                     /* '<S181>/plant u_1' */
  real_T plantu_2;                     /* '<S181>/plant u_2' */
  real_T plantu_3;                     /* '<S181>/plant u_3' */
  real_T plantu_4;                     /* '<S181>/plant u_4' */
  real_T plantu_5;                     /* '<S181>/plant u_5' */
  real_T fact1;                        /* '<S181>/fact1' */
  real_T fact2;                        /* '<S181>/fact2' */
  real_T fact3;                        /* '<S181>/fact3' */
  real_T fact4;                        /* '<S181>/fact4' */
  real_T fact5;                        /* '<S181>/fact5' */
  real_T taux;                         /* '<S181>/taux' */
  real_T tauy;                         /* '<S181>/tauy' */
  real_T tauyaw;                       /* '<S181>/tauyaw' */
  real_T CSE1_rdegs;                   /* '<S182>/CSE1_r [deg//s]' */
  real_T CSE1_ums;                     /* '<S182>/CSE1_u [m//s]' */
  real_T CSE1_vms;                     /* '<S182>/CSE1_v [m//s]' */
  real_T Sum_fc[3];                    /* '<S183>/Sum' */
  real_T Sum1_nv[3];                   /* '<S183>/Sum1' */
  real_T Sum2_o[3];                    /* '<S183>/Sum2' */
  real_T psideg;                       /* '<S183>/psi [deg]' */
  real_T psipsiddeg;                   /* '<S183>/psi-psid [deg]' */
  real_T psiLOSpsideg;                 /* '<S183>/psiLOS-psi [deg]' */
  real_T psiLOSpsiddeg;                /* '<S183>/psiLOS-psid [deg]' */
  real_T psi_LOSdeg;                   /* '<S183>/psi_LOS [deg]' */
  real_T psiddeg;                      /* '<S183>/psid [deg]' */
  real_T psi_plot[3];                  /* '<S183>/psi_plot' */
  real_T qxm;                          /* '<S183>/qx [m]' */
  real_T qxxm;                         /* '<S183>/qx-x [m]' */
  real_T qxxdm1;                       /* '<S183>/qx-xd [m]1' */
  real_T qym;                          /* '<S183>/qy [m]' */
  real_T qyym;                         /* '<S183>/qy-y [m]' */
  real_T qyydm1;                       /* '<S183>/qy-yd [m]1' */
  real_T xm;                           /* '<S183>/x [m]' */
  real_T xxdm;                         /* '<S183>/x-xd [m]' */
  real_T xdm;                          /* '<S183>/xd [m]' */
  real_T x_plot[3];                    /* '<S183>/x_plot' */
  real_T ym;                           /* '<S183>/y [m]' */
  real_T yydm;                         /* '<S183>/y-yd [m]' */
  real_T ydm;                          /* '<S183>/yd [m]' */
  real_T y_plot[3];                    /* '<S183>/y_plot' */
  real_T Integrator_d[3];              /* '<S178>/Integrator' */
  real_T Integrator1_n[3];             /* '<S178>/Integrator1' */
  real_T R11_p;                        /* '<S179>/R11' */
  real_T R21_b;                        /* '<S179>/R21' */
  real_T R12_o;                        /* '<S179>/R12' */
  real_T R22_px;                       /* '<S179>/R22' */
  real_T Rpsi_b[9];                    /* '<S179>/R(psi)' */
  real_T Product3_mm[3];               /* '<S178>/Product3' */
  real_T Product1_dk[3];               /* '<S178>/Product1' */
  real_T Sum_lb[3];                    /* '<S178>/Sum' */
  real_T Product2_ca[3];               /* '<S178>/Product2' */
  real_T BT_D_Gain1;                   /* '<S173>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S173>/BT_D_Gain2' */
  real_T Add_e;                        /* '<S173>/Add' */
  real_T BT_L_Gain1;                   /* '<S173>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S173>/BT_L_Gain2' */
  real_T Neg;                          /* '<S173>/Neg' */
  real_T Sum1_cw;                      /* '<S173>/Sum1' */
  real_T Sum2_d;                       /* '<S173>/Sum2' */
  real_T Switch_k;                     /* '<S175>/Switch' */
  real_T Switch2_o;                    /* '<S175>/Switch2' */
  real_T Switch_g;                     /* '<S176>/Switch' */
  real_T Switch2_n;                    /* '<S176>/Switch2' */
  real_T Switch_b;                     /* '<S177>/Switch' */
  real_T Switch2_g;                    /* '<S177>/Switch2' */
  real_T Sign_i;                       /* '<S174>/Sign' */
  real_T PortVPS_X;                    /* '<S174>/Product1' */
  real_T PortVPS_X_e;                  /* '<S174>/-x' */
  real_T PortVSP_Y;                    /* '<S174>/Product2' */
  real_T PortVSP_Y_m;                  /* '<S174>/-y' */
  real_T StarboardVSP_X;               /* '<S174>/Product3' */
  real_T StarboardVSP_Y;               /* '<S174>/Product4' */
  real_T Servo1;                       /* '<S174>/Servo1' */
  real_T Servo2;                       /* '<S174>/Servo2' */
  real_T Servo3;                       /* '<S174>/Servo3' */
  real_T Servo4;                       /* '<S174>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S174>/VPS_Speed_Gain' */
  real_T Sum_c;                        /* '<S174>/Sum' */
  real_T VSPSPort;                     /* '<S174>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S174>/VSPS Starboard' */
  real_T S12_c;                        /* '<S134>/S12' */
  real_T S_2psi_ds2[4];                /* '<S134>/S_2(psi_d^s^2)' */
  real_T S12_b;                        /* '<S133>/S12' */
  real_T S_2psi_ds[4];                 /* '<S133>/S_2(psi_d^s)' */
  real_T R11_j;                        /* '<S131>/R11' */
  real_T R21_f;                        /* '<S131>/R21' */
  real_T R12_d;                        /* '<S131>/R12' */
  real_T R22_j;                        /* '<S131>/R22' */
  real_T R_2psi_d[4];                  /* '<S131>/R_2(psi_d)' */
  uint16_T Gain1_g;                    /* '<S79>/Gain1' */
  uint16_T Sum_cg;                     /* '<S79>/Sum' */
  uint16_T Gain_m;                     /* '<S81>/Gain' */
  uint16_T Sum_e5;                     /* '<S81>/Sum' */
  uint16_T Gain_bl;                    /* '<S82>/Gain' */
  uint16_T Gain1_c;                    /* '<S82>/Gain1' */
  uint16_T Sum_lj;                     /* '<S82>/Sum' */
  uint8_T Compare;                     /* '<S83>/Compare' */
  uint8_T Compare_o;                   /* '<S85>/Compare' */
  uint8_T Compare_c;                   /* '<S84>/Compare' */
  uint8_T Sum1_l;                      /* '<S79>/Sum1' */
  uint8_T Compare_f;                   /* '<S86>/Compare' */
  uint8_T Compare_b;                   /* '<S87>/Compare' */
  uint8_T Compare_m;                   /* '<S88>/Compare' */
  uint8_T Compare_p;                   /* '<S89>/Compare' */
  uint8_T Compare_oc;                  /* '<S91>/Compare' */
  uint8_T Compare_a;                   /* '<S90>/Compare' */
  boolean_T LowerRelop1;               /* '<S156>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S156>/UpperRelop' */
  boolean_T LowerRelop1_a;             /* '<S157>/LowerRelop1' */
  boolean_T UpperRelop_e;              /* '<S157>/UpperRelop' */
  boolean_T LogicalOperator;           /* '<S79>/Logical Operator' */
  boolean_T LowerRelop1_j;             /* '<S175>/LowerRelop1' */
  boolean_T UpperRelop_f;              /* '<S175>/UpperRelop' */
  boolean_T LowerRelop1_l;             /* '<S176>/LowerRelop1' */
  boolean_T UpperRelop_b;              /* '<S176>/UpperRelop' */
  boolean_T LowerRelop1_n;             /* '<S177>/LowerRelop1' */
  boolean_T UpperRelop_m;              /* '<S177>/UpperRelop' */
} BlockIO_NLPIDVersion2;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Product_DWORK1;               /* '<S115>/Product' */
  real_T Product2_DWORK1[4];           /* '<S117>/Product2' */
  real_T Pseudoinverse_X[15];          /* '<S76>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S76>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S76>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S76>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S76>/Pseudoinverse' */
  real_T Inverse_DWORK3[9];            /* '<S25>/Inverse' */
  real_T Inverse_DWORK4[9];            /* '<S25>/Inverse' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } Derivative_RWORK;                  /* '<S166>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_g;                /* '<S96>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[3];
    real_T TimeStampB;
    real_T LastUAtTimeB[3];
  } Derivative1_RWORK;                 /* '<S166>/Derivative1' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<S22>/To File' */

  int32_T Inverse_DWORK2[3];           /* '<S25>/Inverse' */
  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  uint32_T Sum1_DWORK1;                /* '<S79>/Sum1' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S79>/Sum' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S41>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S41>/Integrator1' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<S22>/To File' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_c;                /* '<S178>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_b;               /* '<S178>/Integrator1' */

  int_T LinearSimulator_MODE;          /* '<S25>/Linear Simulator' */
  int_T CSE1actuator_MODE;             /* '<S25>/CSE1 actuator' */
  uint8_T SignalProbe_DWORK1[14];      /* '<Root>/SignalProbe' */
} D_Work_NLPIDVersion2;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S30>/Integrator' */
  real_T Integrator_CSTATE_p[2];       /* '<S41>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S41>/Integrator1' */
  real_T Integrator_CSTATE_c[3];       /* '<S46>/Integrator' */
  real_T Integrator2_CSTATE[2];        /* '<S41>/Integrator2' */
  real_T Integrator_CSTATE_d[3];       /* '<S178>/Integrator' */
  real_T Integrator1_CSTATE_h[3];      /* '<S178>/Integrator1' */
} ContinuousStates_NLPIDVersion2;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S30>/Integrator' */
  real_T Integrator_CSTATE_p[2];       /* '<S41>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S41>/Integrator1' */
  real_T Integrator_CSTATE_c[3];       /* '<S46>/Integrator' */
  real_T Integrator2_CSTATE[2];        /* '<S41>/Integrator2' */
  real_T Integrator_CSTATE_d[3];       /* '<S178>/Integrator' */
  real_T Integrator1_CSTATE_h[3];      /* '<S178>/Integrator1' */
} StateDerivatives_NLPIDVersion2;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S30>/Integrator' */
  boolean_T Integrator_CSTATE_p[2];    /* '<S41>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S41>/Integrator1' */
  boolean_T Integrator_CSTATE_c[3];    /* '<S46>/Integrator' */
  boolean_T Integrator2_CSTATE[2];     /* '<S41>/Integrator2' */
  boolean_T Integrator_CSTATE_d[3];    /* '<S178>/Integrator' */
  boolean_T Integrator1_CSTATE_h[3];   /* '<S178>/Integrator1' */
} StateDisabled_NLPIDVersion2;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S30>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_j;   /* '<S41>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S41>/Integrator1' */
  ZCSigState Integrator_Reset_ZCE_l;   /* '<S46>/Integrator' */
  ZCSigState Integrator2_Reset_ZCE;    /* '<S41>/Integrator2' */
  ZCSigState Integrator_Reset_ZCE_f;   /* '<S178>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE_j;  /* '<S178>/Integrator1' */
} PrevZCSigStates_NLPIDVersion2;

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
   * '<S105>/Multiport Selector'
   * '<S105>/Multiport Selector1'
   * '<S105>/Multiport Selector2'
   * '<S105>/Multiport Selector3'
   * '<S105>/Multiport Selector4'
   */
  int32_T pooled1;
} ConstParam_NLPIDVersion2;

/* Backward compatible GRT Identifiers */
#define rtB                            NLPIDVersion2_B
#define BlockIO                        BlockIO_NLPIDVersion2
#define rtX                            NLPIDVersion2_X
#define ContinuousStates               ContinuousStates_NLPIDVersion2
#define rtP                            NLPIDVersion2_P
#define Parameters                     Parameters_NLPIDVersion2
#define rtDWork                        NLPIDVersion2_DWork
#define D_Work                         D_Work_NLPIDVersion2
#define ConstParam                     ConstParam_NLPIDVersion2
#define rtcP                           NLPIDVersion2_ConstP
#define rtPrevZCSigState               NLPIDVersion2_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_NLPIDVersion2

/* Parameters (auto storage) */
struct Parameters_NLPIDVersion2_ {
  real_T ControlInputSelector_Value;   /* Expression: 0
                                        * '<S1>/Control Input Selector'
                                        */
  real_T ControlModeSelector_Value;    /* Expression: 0
                                        * '<S1>/Control Mode Selector'
                                        */
  real_T EnableCSE1_Value;             /* Expression: 0
                                        * '<S1>/Enable CSE1'
                                        */
  real_T EnableLinearSimulator_Value;  /* Expression: 0
                                        * '<S4>/Enable Linear Simulator'
                                        */
  real_T Initialpsirad_Value;          /* Expression: 0
                                        * '<S4>/Initial psi [rad]'
                                        */
  real_T Initialxm_Value;              /* Expression: 0
                                        * '<S4>/Initial x [m]'
                                        */
  real_T Initialym_Value;              /* Expression: 0
                                        * '<S4>/Initial y [m]'
                                        */
  real_T Initialrrads_Value;           /* Expression: 0
                                        * '<S4>/Initial r [rad//s]'
                                        */
  real_T Initialums_Value;             /* Expression: 0
                                        * '<S4>/Initial u [m//s]'
                                        */
  real_T Initialvms_Value;             /* Expression: 0
                                        * '<S4>/Initial v [m//s]'
                                        */
  real_T ResetLinearSimulatorintegrator_;/* Expression: 0
                                          * '<S4>/Reset Linear Simulator integrator'
                                          */
  real_T Deltam_Value;                 /* Expression: 2
                                        * '<S5>/Delta [m]'
                                        */
  real_T PathSelector_Value;           /* Expression: 0
                                        * '<S5>/Path Selector  [-]'
                                        */
  real_T my_Value;                     /* Expression: 10
                                        * '<S5>/my [-]'
                                        */
  real_T u_dm_Value;                   /* Expression: 0.15
                                        * '<S5>/u_d [m]'
                                        */
  real_T x_dmaxm_Value;                /* Expression: 40
                                        * '<S5>/x_dmax [m]'
                                        */
  real_T x_dminm_Value;                /* Expression: -40
                                        * '<S5>/x_dmin [m]'
                                        */
  real_T y_dmaxm_Value;                /* Expression: 7
                                        * '<S5>/y_dmax [m]'
                                        */
  real_T y_dminm_Value;                /* Expression: -7
                                        * '<S5>/y_dmin [m]'
                                        */
  real_T k_Value;                      /* Expression: pi/180*2
                                        * '<S10>/k [-]'
                                        */
  real_T r_xm_Value;                   /* Expression: 5.5
                                        * '<S10>/r_x [m]'
                                        */
  real_T r_ym_Value;                   /* Expression: 2
                                        * '<S10>/r_y [m]'
                                        */
  real_T x_0m_Value;                   /* Expression: 4.5
                                        * '<S10>/x_0 [m]'
                                        */
  real_T y_0m_Value;                   /* Expression: 0
                                        * '<S10>/y_0 [m]'
                                        */
  real_T x_1m_Value;                   /* Expression: 0
                                        * '<S11>/x_1 [m]'
                                        */
  real_T x_2m_Value;                   /* Expression: 5.5
                                        * '<S11>/x_2 [m]'
                                        */
  real_T y_1m_Value;                   /* Expression: 0
                                        * '<S11>/y_1 [m]'
                                        */
  real_T y_2m_Value;                   /* Expression: 2
                                        * '<S11>/y_2 [m]'
                                        */
  real_T AS_LX_Value;                  /* Expression: 0
                                        * '<S6>/AS_LX [-] '
                                        */
  real_T ScalingLX_Gain;               /* Expression: 1/32767
                                        * '<S6>/ScalingLX'
                                        */
  real_T AS_LY_Value;                  /* Expression: 0
                                        * '<S6>/AS_LY [-]'
                                        */
  real_T ScalingLY_Gain;               /* Expression: 1/32767
                                        * '<S6>/ScalingLY'
                                        */
  real_T AS_RX_Value;                  /* Expression: 0
                                        * '<S6>/AS_RX [-]'
                                        */
  real_T Scaling_RX_Gain;              /* Expression: 1/32767
                                        * '<S6>/Scaling_RX'
                                        */
  real_T AS_RY_Value;                  /* Expression: 0
                                        * '<S6>/AS_RY [-]'
                                        */
  real_T ScalingRY_Gain;               /* Expression: 1/32767
                                        * '<S6>/ScalingRY'
                                        */
  real_T PS3_BT_Power_Value;           /* Expression: 0
                                        * '<S6>/PS3_BT_Power  [-]'
                                        */
  real_T L2_Value;                     /* Expression: 0
                                        * '<S6>/L2 [-]'
                                        */
  real_T PS3_VSP_Speed_Value;          /* Expression: 0
                                        * '<S6>/PS3_VSP_Speed  [-]'
                                        */
  real_T R2_Value;                     /* Expression: 0
                                        * '<S6>/R2 [-]'
                                        */
  real_T setpointpsideg_Value;         /* Expression: 0
                                        * '<S7>/setpointpsi [deg]'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * '<S12>/Gain1'
                                        */
  real_T setpointxm_Value;             /* Expression: 0
                                        * '<S7>/setpointx [m]'
                                        */
  real_T setpointym_Value;             /* Expression: 0
                                        * '<S7>/setpointy [m]'
                                        */
  real_T u_Value;                      /* Expression: 0
                                        * '<S13>/12'
                                        */
  real_T u_Value_k;                    /* Expression: 0
                                        * '<S13>/13'
                                        */
  real_T u_Value_k0;                   /* Expression: 0
                                        * '<S13>/21'
                                        */
  real_T u_Value_j;                    /* Expression: 0
                                        * '<S13>/23'
                                        */
  real_T u_Value_o;                    /* Expression: 0
                                        * '<S13>/31'
                                        */
  real_T u_Value_oz;                   /* Expression: 0
                                        * '<S13>/32'
                                        */
  real_T ctrl1Kdx_Value;               /* Expression: 50
                                        * '<S8>/ctrl1Kdx'
                                        */
  real_T ctrl1Kdy_Value;               /* Expression: 30
                                        * '<S8>/ctrl1Kdy'
                                        */
  real_T ctrl1Kdpsi_Value;             /* Expression: 5
                                        * '<S8>/ctrl1Kdpsi'
                                        */
  real_T u_Value_a;                    /* Expression: 0
                                        * '<S14>/12'
                                        */
  real_T u_Value_e;                    /* Expression: 0
                                        * '<S14>/13'
                                        */
  real_T u_Value_b;                    /* Expression: 0
                                        * '<S14>/21'
                                        */
  real_T u_Value_f;                    /* Expression: 0
                                        * '<S14>/23'
                                        */
  real_T u_Value_m;                    /* Expression: 0
                                        * '<S14>/31'
                                        */
  real_T u_Value_ea;                   /* Expression: 0
                                        * '<S14>/32'
                                        */
  real_T ctrl1Kix_Value;               /* Expression: 0
                                        * '<S8>/ctrl1Kix'
                                        */
  real_T ctrl1Kiy_Value;               /* Expression: 0
                                        * '<S8>/ctrl1Kiy'
                                        */
  real_T ctrl1Kipsi_Value;             /* Expression: 0
                                        * '<S8>/ctrl1Kipsi'
                                        */
  real_T u_Value_et;                   /* Expression: 0
                                        * '<S15>/12'
                                        */
  real_T u_Value_c;                    /* Expression: 0
                                        * '<S15>/13'
                                        */
  real_T u_Value_b4;                   /* Expression: 0
                                        * '<S15>/21'
                                        */
  real_T u_Value_n;                    /* Expression: 0
                                        * '<S15>/23'
                                        */
  real_T u_Value_i;                    /* Expression: 0
                                        * '<S15>/31'
                                        */
  real_T u_Value_aw;                   /* Expression: 0
                                        * '<S15>/32'
                                        */
  real_T ctrl1Kpx_Value;               /* Expression: 2*1.5*2
                                        * '<S8>/ctrl1Kpx'
                                        */
  real_T ctrl1Kpy_Value;               /* Expression: 2*10*2
                                        * '<S8>/ctrl1Kpy'
                                        */
  real_T ctrl1Kppsi_Value;             /* Expression: 0.5*3
                                        * '<S8>/ctrl1Kppsi'
                                        */
  real_T ctrl1ResetIntegrator_Value;   /* Expression: 0
                                        * '<S8>/ctrl1 Reset Integrator '
                                        */
  real_T u_Value_p;                    /* Expression: 0
                                        * '<S16>/12'
                                        */
  real_T u_Value_kp;                   /* Expression: 0
                                        * '<S16>/21'
                                        */
  real_T Gamma_q_Surge_Value;          /* Expression: 10*2
                                        * '<S9>/Gamma_q_Surge'
                                        */
  real_T Gamma_q_Sway_Value;           /* Expression: 10*10
                                        * '<S9>/Gamma_q_Sway'
                                        */
  real_T Initialq_x_Value;             /* Expression: 0
                                        * '<S9>/Initial q_x'
                                        */
  real_T Initialq_y_Value;             /* Expression: 0
                                        * '<S9>/Initial q_y'
                                        */
  real_T Initials_Value;               /* Expression: 0
                                        * '<S9>/Initial s'
                                        */
  real_T u_Value_l;                    /* Expression: 0
                                        * '<S17>/12'
                                        */
  real_T u_Value_h;                    /* Expression: 0
                                        * '<S17>/13'
                                        */
  real_T u_Value_fr;                   /* Expression: 0
                                        * '<S17>/21'
                                        */
  real_T u_Value_hr;                   /* Expression: 0
                                        * '<S17>/23'
                                        */
  real_T u_Value_ka;                   /* Expression: 0
                                        * '<S17>/31'
                                        */
  real_T u_Value_hp;                   /* Expression: 0
                                        * '<S17>/32'
                                        */
  real_T ctrl2Kdx_Value;               /* Expression: 50
                                        * '<S9>/ctrl2Kdx'
                                        */
  real_T ctrl2Kdy_Value;               /* Expression: 30
                                        * '<S9>/ctrl2Kdy'
                                        */
  real_T ctrl2Kdpsi_Value;             /* Expression: 5
                                        * '<S9>/ctrl2Kdpsi'
                                        */
  real_T u_Value_bm;                   /* Expression: 0
                                        * '<S18>/12'
                                        */
  real_T u_Value_li;                   /* Expression: 0
                                        * '<S18>/13'
                                        */
  real_T u_Value_nj;                   /* Expression: 0
                                        * '<S18>/21'
                                        */
  real_T u_Value_fn;                   /* Expression: 0
                                        * '<S18>/23'
                                        */
  real_T u_Value_ho;                   /* Expression: 0
                                        * '<S18>/31'
                                        */
  real_T u_Value_cj;                   /* Expression: 0
                                        * '<S18>/32'
                                        */
  real_T ctrl2Kix_Value;               /* Expression: 0
                                        * '<S9>/ctrl2Kix'
                                        */
  real_T ctrl2Kiy_Value;               /* Expression: 0
                                        * '<S9>/ctrl2Kiy'
                                        */
  real_T ctrl2Kipsi_Value;             /* Expression: 0
                                        * '<S9>/ctrl2Kipsi'
                                        */
  real_T u_Value_pl;                   /* Expression: 0
                                        * '<S19>/12'
                                        */
  real_T u_Value_jh;                   /* Expression: 0
                                        * '<S19>/13'
                                        */
  real_T u_Value_aq;                   /* Expression: 0
                                        * '<S19>/21'
                                        */
  real_T u_Value_fe;                   /* Expression: 0
                                        * '<S19>/23'
                                        */
  real_T u_Value_fv;                   /* Expression: 0
                                        * '<S19>/31'
                                        */
  real_T u_Value_h3;                   /* Expression: 0
                                        * '<S19>/32'
                                        */
  real_T ctrl2Kpx_Value;               /* Expression: 2*1.5*2
                                        * '<S9>/ctrl2Kpx'
                                        */
  real_T ctrl2Kpy_Value;               /* Expression: 2*10*2
                                        * '<S9>/ctrl2Kpy'
                                        */
  real_T ctrl2Kppsi_Value;             /* Expression: 0.5*3
                                        * '<S9>/ctrl2Kppsi'
                                        */
  real_T ctrl2ResetIntegrator_Value;   /* Expression: 0
                                        * '<S9>/ctrl2 Reset Integrator '
                                        */
  real_T kappa_1_Value;                /* Expression: 1
                                        * '<S9>/kappa_1'
                                        */
  real_T lambda_q_Value;               /* Expression: 1
                                        * '<S9>/lambda_q'
                                        */
  real_T l_x1_Value;                   /* Expression: 0.45
                                        * '<S28>/l_x1'
                                        */
  real_T l_x1_Gain;                    /* Expression: -1
                                        * '<S28>/-l_x1'
                                        */
  real_T l_x2_Value;                   /* Expression: 0.45
                                        * '<S28>/l_x2'
                                        */
  real_T l_x2_Gain;                    /* Expression: -1
                                        * '<S28>/-l_x2'
                                        */
  real_T l_y2_Value;                   /* Expression: 0.055
                                        * '<S28>/l_y2'
                                        */
  real_T l_y2_Gain;                    /* Expression: -1
                                        * '<S28>/-l_y2'
                                        */
  real_T B_11_Value;                   /* Expression: 1
                                        * '<S28>/B_11'
                                        */
  real_T B_21_Value;                   /* Expression: 0
                                        * '<S28>/B_21'
                                        */
  real_T l_y1_Value;                   /* Expression: 0.055
                                        * '<S28>/l_y1'
                                        */
  real_T B_12_Value;                   /* Expression: 0
                                        * '<S28>/B_12'
                                        */
  real_T B_22_Value;                   /* Expression: 1
                                        * '<S28>/B_22'
                                        */
  real_T B_13_Value;                   /* Expression: 1
                                        * '<S28>/B_13'
                                        */
  real_T B_23_Value;                   /* Expression: 0
                                        * '<S28>/B_23'
                                        */
  real_T B_14_Value;                   /* Expression: 0
                                        * '<S28>/B_14'
                                        */
  real_T B_24_Value;                   /* Expression: 1
                                        * '<S28>/B_24'
                                        */
  real_T B_15_Value;                   /* Expression: 0
                                        * '<S28>/B_15'
                                        */
  real_T B_25_Value;                   /* Expression: 1
                                        * '<S28>/B_25'
                                        */
  real_T l_x3_Value;                   /* Expression: 0.385
                                        * '<S28>/l_x3'
                                        */
  real_T N_r_Value;                    /* Expression: -1.900
                                        * '<S27>/N_r'
                                        */
  real_T N_r_Gain;                     /* Expression: -1
                                        * '<S27>/-N_r'
                                        */
  real_T N_v_Value;                    /* Expression: 0.18140
                                        * '<S27>/N_v'
                                        */
  real_T N_v_Gain;                     /* Expression: -1
                                        * '<S27>/-N_v'
                                        */
  real_T X_u_Value;                    /* Expression: -0.59739
                                        * '<S27>/X_u'
                                        */
  real_T X_u_Gain;                     /* Expression: -1
                                        * '<S27>/-X_u'
                                        */
  real_T Y_v_Value;                    /* Expression: -3.50625
                                        * '<S27>/Y_v'
                                        */
  real_T Y_v_Gain;                     /* Expression: -1
                                        * '<S27>/-Y_v'
                                        */
  real_T Y_r_Value;                    /* Expression: -7.250
                                        * '<S27>/Y_r'
                                        */
  real_T Y_vr_Gain;                    /* Expression: -1
                                        * '<S27>/-Y_vr'
                                        */
  real_T D_L_12_Value;                 /* Expression: 0
                                        * '<S27>/D_L_12'
                                        */
  real_T D_L_13_Value;                 /* Expression: 0
                                        * '<S27>/D_L_13'
                                        */
  real_T D_L_21_Value;                 /* Expression: 0
                                        * '<S27>/D_L_21'
                                        */
  real_T D_L_31_Value;                 /* Expression: 0
                                        * '<S27>/D_L_31'
                                        */
  real_T m_Value;                      /* Expression: 17.6
                                        * '<S26>/m'
                                        */
  real_T X_udot_Value;                 /* Expression: -2.0
                                        * '<S26>/X_udot'
                                        */
  real_T M_21_Value;                   /* Expression: 0
                                        * '<S26>/M_21'
                                        */
  real_T M_31_Value;                   /* Expression: 0
                                        * '<S26>/M_31'
                                        */
  real_T M_12_Value;                   /* Expression: 0
                                        * '<S26>/M_12'
                                        */
  real_T Y_vdot_Value;                 /* Expression: -10.0
                                        * '<S26>/Y_vdot'
                                        */
  real_T x_g_Value;                    /* Expression: 0.03
                                        * '<S26>/x_g'
                                        */
  real_T N_vdot_Value;                 /* Expression: -0.0
                                        * '<S26>/N_vdot'
                                        */
  real_T M_13_Value;                   /* Expression: 0
                                        * '<S26>/M_13'
                                        */
  real_T Y_rdot_Value;                 /* Expression: 0.0
                                        * '<S26>/Y_rdot'
                                        */
  real_T I_z_Value;                    /* Expression: 1.760
                                        * '<S26>/I_z'
                                        */
  real_T N_rdot_Value;                 /* Expression: -1.0
                                        * '<S26>/N_rdot'
                                        */
  real_T T_e11_Value;                  /* Expression: 1
                                        * '<S74>/T_e11'
                                        */
  real_T T_e21_Value;                  /* Expression: 0
                                        * '<S74>/T_e21'
                                        */
  real_T l_y1_Value_o;                 /* Expression: 0.055
                                        * '<S74>/l_y1'
                                        */
  real_T T_e12_Value;                  /* Expression: 0
                                        * '<S74>/T_e12'
                                        */
  real_T T_e22_Value;                  /* Expression: 1
                                        * '<S74>/T_e22'
                                        */
  real_T l_x1_Value_n;                 /* Expression: 0.45
                                        * '<S74>/l_x1'
                                        */
  real_T l_x1_Gain_h;                  /* Expression: -1
                                        * '<S74>/-l_x1'
                                        */
  real_T T_e13_Value;                  /* Expression: 1
                                        * '<S74>/T_e13'
                                        */
  real_T T_e23_Value;                  /* Expression: 0
                                        * '<S74>/T_e23'
                                        */
  real_T l_y2_Value_n;                 /* Expression: 0.055
                                        * '<S74>/l_y2'
                                        */
  real_T l_y2_Gain_g;                  /* Expression: -1
                                        * '<S74>/-l_y2'
                                        */
  real_T T_e14_Value;                  /* Expression: 0
                                        * '<S74>/T_e14'
                                        */
  real_T T_e24_Value;                  /* Expression: 1
                                        * '<S74>/T_e24'
                                        */
  real_T l_x2_Value_e;                 /* Expression: 0.45
                                        * '<S74>/l_x2'
                                        */
  real_T l_x2_Gain_c;                  /* Expression: -1
                                        * '<S74>/-l_x2'
                                        */
  real_T T_e15_Value;                  /* Expression: 0
                                        * '<S74>/T_e15'
                                        */
  real_T T_e25_Value;                  /* Expression: 1
                                        * '<S74>/T_e25'
                                        */
  real_T l_x3_Value_o;                 /* Expression: 0.385
                                        * '<S74>/l_x3'
                                        */
  real_T PS3u_1_Gain;                  /* Expression: 1
                                        * '<S32>/PS3 u_1'
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
                                        * '<S73>/u_1 to f_1'
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
                                        * '<S73>/u_1 to f_1'
                                        */
  real_T PS3u_2_Gain;                  /* Expression: 1
                                        * '<S32>/PS3 u_2'
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
                                        * '<S73>/u_2 to f_2'
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
                                        * '<S73>/u_2 to f_2'
                                        */
  real_T PS3u_3_Gain;                  /* Expression: 1
                                        * '<S32>/PS3 u_3'
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
                                        * '<S73>/u_3 to f_3'
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
                                        * '<S73>/u_3 to f_3'
                                        */
  real_T PS3u_4_Gain;                  /* Expression: 1
                                        * '<S32>/PS3 u_4'
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
                                        * '<S73>/u_4 to f_4'
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
                                        * '<S73>/u_4 to f_4'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S32>/PS3 u_5'
                                        */
  real_T u_5tof_5_XData[7];            /* Expression: [-.3:0.1:.3]
                                        * '<S73>/u_5 to f_5'
                                        */
  real_T u_5tof_5_YData[7];            /* Expression: [-1.2630 -1.0309 -0.3808 0 0.3480  0.8290 1.0930]
                                        * '<S73>/u_5 to f_5'
                                        */
  real_T QTMIn_P1;                     /* Expression: width
                                        * '<S166>/QTM In'
                                        */
  real_T QTMIn_P2;                     /* Expression: dtype
                                        * '<S166>/QTM In'
                                        */
  real_T QTMIn_P3;                     /* Expression: portnum
                                        * '<S166>/QTM In'
                                        */
  real_T QTMIn_P4;                     /* Expression: stime
                                        * '<S166>/QTM In'
                                        */
  real_T QTMIn_P5;                     /* Expression: stype
                                        * '<S166>/QTM In'
                                        */
  real_T QTMIn_P6;                     /* Expression: btype
                                        * '<S166>/QTM In'
                                        */
  real_T QTMIn3xcoordmm_Gain;          /* Expression: 1
                                        * '<S166>/QTM In3 x-coord [mm]'
                                        */
  real_T mm2mx_Gain;                   /* Expression: 0.001
                                        * '<S166>/mm2m x'
                                        */
  real_T QTMIn4ycoordmm_Gain;          /* Expression: 1
                                        * '<S166>/QTM In4 y-coord [mm]'
                                        */
  real_T mm2my_Gain;                   /* Expression: 0.001
                                        * '<S166>/mm2m y'
                                        */
  real_T QTMIn6yawdeg_Gain;            /* Expression: 1
                                        * '<S166>/QTM In6 yaw [deg]'
                                        */
  real_T d2ryaw_Gain;                  /* Expression: pi/180
                                        * '<S166>/d2r yaw'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * '<S36>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * '<S36>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * '<S36>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 2*pi
                                        * '<S36>/Constant'
                                        */
  real_T Saturation_UpperSat_i;        /* Expression: 1e10
                                        * '<S35>/Saturation'
                                        */
  real_T Saturation_LowerSat_f;        /* Expression: -1e10
                                        * '<S35>/Saturation'
                                        */
  real_T Gain_Gain_n;                  /* Expression: pi
                                        * '<S35>/Gain'
                                        */
  real_T Constant_Value_o;             /* Expression: 2*pi
                                        * '<S35>/Constant'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * '<S30>/Integrator'
                                        */
  real_T QTMIn8rolldeg_Gain;           /* Expression: 1
                                        * '<S166>/QTM In8 roll [deg]'
                                        */
  real_T d2rroll_Gain;                 /* Expression: pi/180
                                        * '<S166>/d2r roll'
                                        */
  real_T QTMIn7pitchdeg_Gain;          /* Expression: 1
                                        * '<S166>/QTM In7 pitch [deg]'
                                        */
  real_T d2rpitch_Gain;                /* Expression: pi/180
                                        * '<S166>/d2r pitch'
                                        */
  real_T Constant1_Value[9];           /* Expression: zeros(3)
                                        * '<S166>/Constant1'
                                        */
  real_T QTMIn5zcoordmm_Gain;          /* Expression: 1
                                        * '<S166>/QTM In5 z-coord [mm]'
                                        */
  real_T mm2mz_Gain;                   /* Expression: 0.001
                                        * '<S166>/mm2m z'
                                        */
  real_T R31_Value;                    /* Expression: 0
                                        * '<S40>/R31'
                                        */
  real_T u_Gain;                       /* Expression: -1
                                        * '<S40>/-1'
                                        */
  real_T R32_Value;                    /* Expression: 0
                                        * '<S40>/R32'
                                        */
  real_T R13_Value;                    /* Expression: 0
                                        * '<S40>/R13'
                                        */
  real_T R23_Value;                    /* Expression: 0
                                        * '<S40>/R23'
                                        */
  real_T R33_Value;                    /* Expression: 1
                                        * '<S40>/R33'
                                        */
  real_T Saturation_UpperSat_f;        /* Expression: 1e10
                                        * '<S69>/Saturation'
                                        */
  real_T Saturation_LowerSat_m;        /* Expression: -1e10
                                        * '<S69>/Saturation'
                                        */
  real_T Gain_Gain_k;                  /* Expression: pi
                                        * '<S69>/Gain'
                                        */
  real_T Constant_Value_l;             /* Expression: 2*pi
                                        * '<S69>/Constant'
                                        */
  real_T Saturation_UpperSat_j;        /* Expression: 1
                                        * '<S142>/Saturation'
                                        */
  real_T Saturation_LowerSat_k;        /* Expression: 0
                                        * '<S142>/Saturation'
                                        */
  real_T Gain_Gain_o;                  /* Expression: -1
                                        * '<S145>/Gain'
                                        */
  real_T Constant_Value_g;             /* Expression: 1
                                        * '<S152>/Constant'
                                        */
  real_T Saturation_UpperSat_m;        /* Expression: 1e10
                                        * '<S100>/Saturation'
                                        */
  real_T Saturation_LowerSat_o;        /* Expression: -1e10
                                        * '<S100>/Saturation'
                                        */
  real_T Gain_Gain_p;                  /* Expression: pi
                                        * '<S100>/Gain'
                                        */
  real_T Constant_Value_p;             /* Expression: 2*pi
                                        * '<S100>/Constant'
                                        */
  real_T Saturation_UpperSat_h;        /* Expression: 1e10
                                        * '<S128>/Saturation'
                                        */
  real_T Saturation_LowerSat_p;        /* Expression: -1e10
                                        * '<S128>/Saturation'
                                        */
  real_T Gain_Gain_b;                  /* Expression: pi
                                        * '<S128>/Gain'
                                        */
  real_T Constant_Value_a;             /* Expression: 2*pi
                                        * '<S128>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: 1
                                        * '<S151>/Constant'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 1e10
                                        * '<S129>/Saturation'
                                        */
  real_T Saturation_LowerSat_mg;       /* Expression: -1e10
                                        * '<S129>/Saturation'
                                        */
  real_T Gain_Gain_j;                  /* Expression: pi
                                        * '<S129>/Gain'
                                        */
  real_T Constant_Value_lh;            /* Expression: 2*pi
                                        * '<S129>/Constant'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: 1e10
                                        * '<S130>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: -1e10
                                        * '<S130>/Saturation'
                                        */
  real_T Gain_Gain_d;                  /* Expression: pi
                                        * '<S130>/Gain'
                                        */
  real_T Constant_Value_ac;            /* Expression: 2*pi
                                        * '<S130>/Constant'
                                        */
  real_T Saturation_UpperSat_n;        /* Expression: 1e10
                                        * '<S70>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: -1e10
                                        * '<S70>/Saturation'
                                        */
  real_T Gain_Gain_g;                  /* Expression: pi
                                        * '<S70>/Gain'
                                        */
  real_T Constant_Value_f;             /* Expression: 2*pi
                                        * '<S70>/Constant'
                                        */
  real_T Integrator_IC_g[3];           /* Expression: [0 0 0]'
                                        * '<S46>/Integrator'
                                        */
  real_T u_Gain_m;                     /* Expression: -1
                                        * '<S123>/-1'
                                        */
  real_T _2x1_Value[2];                /* Expression: [0;0]
                                        * '<S53>/0_2x1'
                                        */
  real_T _2x1_Value_i[2];              /* Expression: [0;0]
                                        * '<S143>/0_2x1'
                                        */
  real_T Gain_Gain_pn;                 /* Expression: -1
                                        * '<S146>/Gain'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: -1
                                        * '<S146>/Gain1'
                                        */
  real_T Constant_Value_i;             /* Expression: 1
                                        * '<S153>/Constant'
                                        */
  real_T Constant_Value_d;             /* Expression: 1
                                        * '<S155>/Constant'
                                        */
  real_T Gain_Gain_e;                  /* Expression: -1
                                        * '<S115>/Gain'
                                        */
  real_T Gain_Gain_f;                  /* Expression: -1
                                        * '<S108>/Gain'
                                        */
  real_T _Gain;                        /* Expression: 2
                                        * '<S124>/2'
                                        */
  real_T _2x2_Value[4];                /* Expression: [0 0;0 0]
                                        * '<S105>/0_2x2'
                                        */
  real_T _2x2_Value_m[4];              /* Expression: [0 0; 0 0]
                                        * '<S54>/0_2x2'
                                        */
  real_T _Gain_m;                      /* Expression: 2
                                        * '<S125>/2'
                                        */
  real_T u_Value_h4;                   /* Expression: 3/2
                                        * '<S112>/3//2'
                                        */
  real_T Gain_Gain_c;                  /* Expression: -1
                                        * '<S116>/Gain'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * '<S41>/Integrator2'
                                        */
  real_T Gain_Gain_c4;                 /* Expression: -1
                                        * '<S109>/Gain'
                                        */
  real_T _2x1_Value_ig[2];             /* Expression: [0;0]
                                        * '<S55>/0_2x1'
                                        */
  real_T Constant_Value_ji;            /* Expression: 3
                                        * '<S147>/Constant'
                                        */
  real_T Gain_Gain_gz;                 /* Expression: -1
                                        * '<S147>/Gain'
                                        */
  real_T Constant_Value_n;             /* Expression: 1
                                        * '<S154>/Constant'
                                        */
  real_T u_Gain_k;                     /* Expression: 2
                                        * '<S99>/+ 2'
                                        */
  real_T _Gain_j;                      /* Expression: 2
                                        * '<S127>/2'
                                        */
  real_T _Gain_f;                      /* Expression: 2
                                        * '<S139>/2'
                                        */
  real_T Gain_Gain_cv;                 /* Expression: 1
                                        * '<S139>/Gain'
                                        */
  real_T Constant_Value_m;             /* Expression: 3
                                        * '<S163>/Constant'
                                        */
  real_T Gain_Gain_eu;                 /* Expression: -1
                                        * '<S163>/Gain'
                                        */
  real_T u_Value_jk;                   /* Expression: 3/2
                                        * '<S113>/3//2'
                                        */
  real_T Constant_Value_gy;            /* Expression: 3
                                        * '<S117>/Constant'
                                        */
  real_T _2x1_Value_h[2];              /* Expression: [0;0]
                                        * '<S56>/0_2x1'
                                        */
  real_T S11_Value;                    /* Expression: 0
                                        * '<S60>/S11'
                                        */
  real_T R31_Value_l;                  /* Expression: 0
                                        * '<S60>/R31'
                                        */
  real_T S12_Gain;                     /* Expression: 1
                                        * '<S60>/S12'
                                        */
  real_T S22_Value;                    /* Expression: 0
                                        * '<S60>/S22'
                                        */
  real_T S32_Value;                    /* Expression: 0
                                        * '<S60>/S32'
                                        */
  real_T S13_Value;                    /* Expression: 0
                                        * '<S60>/S13'
                                        */
  real_T S23_Value;                    /* Expression: 0
                                        * '<S60>/S23'
                                        */
  real_T S33_Value;                    /* Expression: 1
                                        * '<S60>/S33'
                                        */
  real_T Constant_Value_jd[4];         /* Expression: a
                                        * '<S140>/Constant'
                                        */
  real_T Gain_Gain_i;                  /* Expression: -1
                                        * '<S41>/Gain'
                                        */
  real_T f_1tou_1_XData[39];           /* Expression: [-0.6829 -0.6369 -0.5785 -0.5165 -0.4456 -0.3725 -0.3308 -0.2827 -0.2277 -0.1517 -0.1240 -0.0769 -0.0238 0.0039 0.0377 0.0635 0.1051 0.1196 0.1412 0.1721 0.1754 0.1774 0.2104 0.2200 0.2266 0.2673 0.3025 0.3486 0.3896 0.4252 0.4782 0.5164 0.5695 0.6195 0.6723 0.7449 0.7836 0.8414 0.8987 ]
                                        * '<S78>/f_1 to u_1'
                                        */
  real_T f_1tou_1_YData[39];           /* Expression: [-1.0000 -0.9500 -0.9000 -0.8500 -0.8000 -0.7500 -0.7000 -0.6500 -0.6000 -0.5500 -0.5000 -0.4500 -0.4000 -0.3500 -0.3000 -0.2500 -0.2000 -0.1500 -0.1000 -0.0500 0 0.0500 0.1000 0.1500 0.2000 0.2500 0.3000 0.3500 0.4000 0.4500 0.5000 0.5500 0.6000 0.6500 0.7000 0.7500 0.8000 0.8500 0.9000]
                                        * '<S78>/f_1 to u_1'
                                        */
  real_T Constant_Value_c;             /* Expression: const
                                        * '<S83>/Constant'
                                        */
  real_T Constant_Value_go;            /* Expression: const
                                        * '<S85>/Constant'
                                        */
  real_T Constant_Value_l1;            /* Expression: const
                                        * '<S84>/Constant'
                                        */
  real_T Constant_Value_k;             /* Expression: const
                                        * '<S86>/Constant'
                                        */
  real_T f_2000391_XData[11];          /* Expression: [-0.2704
                                          -0.2259
                                          -0.1903
                                          -0.1697
                                          -0.1518
                                          -0.1234
                                          -0.0994
                                          -0.0817
                                          -0.0612
                                          -0.0123
                                          0.0039]
                                        * '<S79>/f_2 < 0.00391'
                                        */
  real_T f_2000391_YData[11];          /* Expression: [-1.0000
                                          -0.9500
                                          -0.9000
                                          -0.8500
                                          -0.8000
                                          -0.7500
                                          -0.7000
                                          -0.6500
                                          -0.6000
                                          -0.5500
                                          -0.5000]
                                        * '<S79>/f_2 < 0.00391'
                                        */
  real_T f_2006731f_2000391_XData[3];  /* Expression: [-0.0105
                                          0.0226
                                          0.0673]
                                        * '<S79>/f_2 < 0.06731 && f_2 >= 0.00391'
                                        */
  real_T f_2006731f_2000391_YData[3];  /* Expression: [-0.2000
                                          -0.1500
                                          -0.1000]
                                        * '<S79>/f_2 < 0.06731 && f_2 >= 0.00391'
                                        */
  real_T f_2006731_XData[18];          /* Expression: [0.0872
                                          0.0930
                                          0.1182
                                          0.1412
                                          0.1892
                                          0.2146
                                          0.2678
                                          0.3096
                                          0.3551
                                          0.4013
                                          0.4566
                                          0.5051
                                          0.5477
                                          0.6060
                                          0.6703
                                          0.7437
                                          0.7604
                                          0.7634]
                                        * '<S79>/f_2 => 0.06731'
                                        */
  real_T f_2006731_YData[18];          /* Expression: [0
                                          0.0500
                                          0.1000
                                          0.1500
                                          0.2000
                                          0.2500
                                          0.3000
                                          0.3500
                                          0.4000
                                          0.4500
                                          0.5000
                                          0.5500
                                          0.6000
                                          0.6500
                                          0.7000
                                          0.7500
                                          0.8000
                                          0.8500]
                                        * '<S79>/f_2 => 0.06731'
                                        */
  real_T f_3tou_3_XData[39];           /* Expression: [-0.5408,-0.5036,-0.4487,-0.3802,-0.3147,-0.2525,-0.2338,-0.1568,-0.1034,-0.0647,-0.0054,0.0221,0.0572,0.0747,0.0991,0.1258,0.1385,0.1447,0.1539,0.1625,0.1712,0.1976,0.2258,0.2443,0.3058,0.3460,0.3989,0.4342,0.4932,0.5524,0.5814,0.6394,0.6851,0.7496,0.8081,0.8382,0.8665,0.8767,0.8885]
                                        * '<S80>/f_3 to u_3'
                                        */
  real_T f_3tou_3_YData[39];           /* Expression: [-1.0000,-0.9500,-0.9000,-0.8500,-0.8000,-0.7500,-0.7000,-0.6500,-0.6000,-0.5500,-0.5000,-0.4500,-0.4000,-0.3500,-0.3000,-0.2000,-0.1500,-0.1000,-0.0500,0,0.0500,0.1000,0.1500,0.2000,0.2500,0.3000,0.3500,0.4000,0.4500,0.5000,0.5500,0.6000,0.6500,0.7000,0.7500,0.8000,0.8500,0.9500,1.0000]
                                        * '<S80>/f_3 to u_3'
                                        */
  real_T Constant_Value_al;            /* Expression: const
                                        * '<S87>/Constant'
                                        */
  real_T Constant_Value_nq;            /* Expression: const
                                        * '<S88>/Constant'
                                        */
  real_T f_400451_XData[15];           /* Expression: [-0.5212
                                          -0.5163
                                          -0.4943
                                          -0.4390
                                          -0.3803
                                          -0.3603
                                          -0.3132
                                          -0.2567
                                          -0.2102
                                          -0.1609
                                          -0.1267
                                          -0.0819
                                          -0.0554
                                          0.0099
                                          0.0450]
                                        * '<S81>/f_4 < 0.0451'
                                        */
  real_T f_400451_YData[15];           /* Expression: [-0.8000
                                          -0.7500
                                          -0.7000
                                          -0.6500
                                          -0.6000
                                          -0.5500
                                          -0.5000
                                          -0.4500
                                          -0.4000
                                          -0.3500
                                          -0.3000
                                          -0.2500
                                          -0.2000
                                          -0.1500
                                          -0.1000]
                                        * '<S81>/f_4 < 0.0451'
                                        */
  real_T f_400451_XData_e[13];         /* Expression: [0.0431
                                          0.0808
                                          0.0867
                                          0.1337
                                          0.1726
                                          0.1963
                                          0.2088
                                          0.2323
                                          0.2969
                                          0.3134
                                          0.3376
                                          0.3743
                                          0.4276]
                                        * '<S81>/f_4 >= 0.0451 '
                                        */
  real_T f_400451_YData_p[13];         /* Expression: [0.4000
                                          0.4500
                                          0.5000
                                          0.5500
                                          0.6000
                                          0.6500
                                          0.7000
                                          0.7500
                                          0.8000
                                          0.8500
                                          0.9000
                                          0.9500
                                          1.0000]
                                        * '<S81>/f_4 >= 0.0451 '
                                        */
  real_T DeadZone001_Start;            /* Expression: -0.01
                                        * '<S82>/Dead Zone +-0.01'
                                        */
  real_T DeadZone001_End;              /* Expression: 0.01
                                        * '<S82>/Dead Zone +-0.01'
                                        */
  real_T Constant_Value_b;             /* Expression: const
                                        * '<S89>/Constant'
                                        */
  real_T Constant_Value_fz;            /* Expression: const
                                        * '<S90>/Constant'
                                        */
  real_T f_50_XData[10];               /* Expression: [-1.1653
                                          -1.1010
                                          -0.9810
                                          -0.8576
                                          -0.7363
                                          -0.5877
                                          -0.4265
                                          -0.2640
                                          -0.1099
                                          0.0031]
                                        * '<S82>/f_5 < 0'
                                        */
  real_T f_50_YData[10];               /* Expression: [-0.2000
                                          -0.1900
                                          -0.1700
                                          -0.1500
                                          -0.1300
                                          -0.1100
                                          -0.0900
                                          -0.0700
                                          -0.0500
                                          -0.0300]
                                        * '<S82>/f_5 < 0'
                                        */
  real_T f_50_Value;                   /* Expression: 0
                                        * '<S82>/f_5 = 0'
                                        */
  real_T f_50_XData_k[10];             /* Expression: [0.0103
                                          0.0743
                                          0.1937
                                          0.3232
                                          0.4342
                                          0.5862
                                          0.7291
                                          0.8697
                                          0.9681
                                          1.0229]
                                        * '<S82>/f_5 > 0'
                                        */
  real_T f_50_YData_c[10];             /* Expression: [0.0300
                                          0.0500
                                          0.0700
                                          0.0900
                                          0.1100
                                          0.1300
                                          0.1500
                                          0.1700
                                          0.1900
                                          0.2000]
                                        * '<S82>/f_5 > 0'
                                        */
  real_T BT_power_limit_Value;         /* Expression: 0.4
                                        * '<S75>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value;             /* Expression: 0.3
                                        * '<S75>/VSP_speeds'
                                        */
  real_T Saturation_UpperSat_il;       /* Expression: 1.0
                                        * '<S33>/Saturation'
                                        */
  real_T Saturation_LowerSat_j;        /* Expression: -1.0
                                        * '<S33>/Saturation'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S166>/QTM In2 Error'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S166>/QTM In9 Residual'
                                        */
  real_T Saturation_UpperSat_k;        /* Expression: 1
                                        * '<S171>/Saturation'
                                        */
  real_T Saturation_LowerSat_b2;       /* Expression: 0
                                        * '<S171>/Saturation'
                                        */
  real_T _2x1_Value_l[2];              /* Expression: [0;0]
                                        * '<S106>/0_2x1'
                                        */
  real_T QTMIn1FPS_Gain;               /* Expression: 1
                                        * '<S166>/QTM In1 FPS'
                                        */
  real_T SITzAI0_P1;                   /* Expression: width
                                        * '<S166>/SIT zAI0'
                                        */
  real_T SITzAI0_P2;                   /* Expression: dtype
                                        * '<S166>/SIT zAI0'
                                        */
  real_T SITzAI0_P3;                   /* Expression: portnum
                                        * '<S166>/SIT zAI0'
                                        */
  real_T SITzAI0_P4;                   /* Expression: stime
                                        * '<S166>/SIT zAI0'
                                        */
  real_T SITzAI0_P5;                   /* Expression: stype
                                        * '<S166>/SIT zAI0'
                                        */
  real_T SITzAI0_P6;                   /* Expression: btype
                                        * '<S166>/SIT zAI0'
                                        */
  real_T SITzAI1_P1;                   /* Expression: width
                                        * '<S166>/SIT zAI1'
                                        */
  real_T SITzAI1_P2;                   /* Expression: dtype
                                        * '<S166>/SIT zAI1'
                                        */
  real_T SITzAI1_P3;                   /* Expression: portnum
                                        * '<S166>/SIT zAI1'
                                        */
  real_T SITzAI1_P4;                   /* Expression: stime
                                        * '<S166>/SIT zAI1'
                                        */
  real_T SITzAI1_P5;                   /* Expression: stype
                                        * '<S166>/SIT zAI1'
                                        */
  real_T SITzAI1_P6;                   /* Expression: btype
                                        * '<S166>/SIT zAI1'
                                        */
  real_T SITzAI2_P1;                   /* Expression: width
                                        * '<S166>/SIT zAI2'
                                        */
  real_T SITzAI2_P2;                   /* Expression: dtype
                                        * '<S166>/SIT zAI2'
                                        */
  real_T SITzAI2_P3;                   /* Expression: portnum
                                        * '<S166>/SIT zAI2'
                                        */
  real_T SITzAI2_P4;                   /* Expression: stime
                                        * '<S166>/SIT zAI2'
                                        */
  real_T SITzAI2_P5;                   /* Expression: stype
                                        * '<S166>/SIT zAI2'
                                        */
  real_T SITzAI2_P6;                   /* Expression: btype
                                        * '<S166>/SIT zAI2'
                                        */
  real_T Saturation_UpperSat_ez;       /* Expression: 3
                                        * '<S172>/Saturation'
                                        */
  real_T Saturation_LowerSat_pr;       /* Expression: -2.6
                                        * '<S172>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 3
                                        * '<S172>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -3.5
                                        * '<S172>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.6
                                        * '<S172>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S172>/Saturation2'
                                        */
  real_T planttau_surge_Gain;          /* Expression: 1
                                        * '<S172>/plant tau_surge'
                                        */
  real_T planttau_sway_Gain;           /* Expression: 1
                                        * '<S172>/plant tau_sway'
                                        */
  real_T planttau_yaw_Gain;            /* Expression: 1
                                        * '<S172>/plant tau_yaw'
                                        */
  real_T BatteryBowThruster_Gain;      /* Expression: 1
                                        * '<S180>/Battery Bow Thruster'
                                        */
  real_T BatteryMain_Gain;             /* Expression: 2
                                        * '<S180>/Battery Main'
                                        */
  real_T BatteryServo_Gain;            /* Expression: 1
                                        * '<S180>/Battery Servo'
                                        */
  real_T omega_qy_Gain;                /* Expression: 1
                                        * '<S181>/omega_qy'
                                        */
  real_T omegaqx_Gain;                 /* Expression: 1
                                        * '<S181>/omegaqx'
                                        */
  real_T plantBTpower_Gain;            /* Expression: 1
                                        * '<S181>/plant BT power'
                                        */
  real_T plantVSPspeed_Gain;           /* Expression: 1
                                        * '<S181>/plant VSP speed'
                                        */
  real_T plantu_1_Gain;                /* Expression: 1
                                        * '<S181>/plant u_1'
                                        */
  real_T plantu_2_Gain;                /* Expression: 1
                                        * '<S181>/plant u_2'
                                        */
  real_T plantu_3_Gain;                /* Expression: 1
                                        * '<S181>/plant u_3'
                                        */
  real_T plantu_4_Gain;                /* Expression: 1
                                        * '<S181>/plant u_4'
                                        */
  real_T plantu_5_Gain;                /* Expression: 1
                                        * '<S181>/plant u_5'
                                        */
  real_T fact1_Gain;                   /* Expression: 1
                                        * '<S181>/fact1'
                                        */
  real_T fact2_Gain;                   /* Expression: 1
                                        * '<S181>/fact2'
                                        */
  real_T fact3_Gain;                   /* Expression: 1
                                        * '<S181>/fact3'
                                        */
  real_T fact4_Gain;                   /* Expression: 1
                                        * '<S181>/fact4'
                                        */
  real_T fact5_Gain;                   /* Expression: 1
                                        * '<S181>/fact5'
                                        */
  real_T taux_Gain;                    /* Expression: 1
                                        * '<S181>/taux'
                                        */
  real_T tauy_Gain;                    /* Expression: 1
                                        * '<S181>/tauy'
                                        */
  real_T tauyaw_Gain;                  /* Expression: 1
                                        * '<S181>/tauyaw'
                                        */
  real_T CSE1_rdegs_Gain;              /* Expression: 180/pi
                                        * '<S182>/CSE1_r [deg//s]'
                                        */
  real_T CSE1_ums_Gain;                /* Expression: 1
                                        * '<S182>/CSE1_u [m//s]'
                                        */
  real_T CSE1_vms_Gain;                /* Expression: 1
                                        * '<S182>/CSE1_v [m//s]'
                                        */
  real_T psideg_Gain;                  /* Expression: 180/pi
                                        * '<S183>/psi [deg]'
                                        */
  real_T psipsiddeg_Gain;              /* Expression: 180/pi
                                        * '<S183>/psi-psid [deg]'
                                        */
  real_T psiLOSpsideg_Gain;            /* Expression: 180/pi
                                        * '<S183>/psiLOS-psi [deg]'
                                        */
  real_T psiLOSpsiddeg_Gain;           /* Expression: 180/pi
                                        * '<S183>/psiLOS-psid [deg]'
                                        */
  real_T psi_LOSdeg_Gain;              /* Expression: 180/pi
                                        * '<S183>/psi_LOS [deg]'
                                        */
  real_T psiddeg_Gain;                 /* Expression: 180/pi
                                        * '<S183>/psid [deg]'
                                        */
  real_T psi_plot_Gain;                /* Expression: 1
                                        * '<S183>/psi_plot'
                                        */
  real_T qxm_Gain;                     /* Expression: 1
                                        * '<S183>/qx [m]'
                                        */
  real_T qxxm_Gain;                    /* Expression: 1
                                        * '<S183>/qx-x [m]'
                                        */
  real_T qxxdm1_Gain;                  /* Expression: 1
                                        * '<S183>/qx-xd [m]1'
                                        */
  real_T qym_Gain;                     /* Expression: 1
                                        * '<S183>/qy [m]'
                                        */
  real_T qyym_Gain;                    /* Expression: 1
                                        * '<S183>/qy-y [m]'
                                        */
  real_T qyydm1_Gain;                  /* Expression: 1
                                        * '<S183>/qy-yd [m]1'
                                        */
  real_T xm_Gain;                      /* Expression: 1
                                        * '<S183>/x [m]'
                                        */
  real_T xxdm_Gain;                    /* Expression: 1
                                        * '<S183>/x-xd [m]'
                                        */
  real_T xdm_Gain;                     /* Expression: 1
                                        * '<S183>/xd [m]'
                                        */
  real_T x_plot_Gain;                  /* Expression: 1
                                        * '<S183>/x_plot'
                                        */
  real_T ym_Gain;                      /* Expression: 1
                                        * '<S183>/y [m]'
                                        */
  real_T yydm_Gain;                    /* Expression: 1
                                        * '<S183>/y-yd [m]'
                                        */
  real_T ydm_Gain;                     /* Expression: 1
                                        * '<S183>/yd [m]'
                                        */
  real_T y_plot_Gain;                  /* Expression: 1
                                        * '<S183>/y_plot'
                                        */
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T R12_Gain;                     /* Expression: -1
                                        * '<S131>/R12'
                                        */
  real_T R22_Gain;                     /* Expression: 1
                                        * '<S131>/R22'
                                        */
  real_T _Value;                       /* Expression: 0
                                        * '<S133>/0'
                                        */
  real_T S12_Gain_c;                   /* Expression: -1
                                        * '<S133>/S12'
                                        */
  real_T _Value_m;                     /* Expression: 0
                                        * '<S134>/0'
                                        */
  real_T S12_Gain_g;                   /* Expression: -1
                                        * '<S134>/S12'
                                        */
  real_T SITPWM0BT_P1;                 /* Expression: width
                                        * '<S173>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S173>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S173>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S173>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S173>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S173>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S173>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S173>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S173>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S173>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S173>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S173>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S173>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_h;             /* Expression: 0
                                        * '<S173>/Constant'
                                        */
  real_T Constant1_Value_i;            /* Expression: 0
                                        * '<S173>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S173>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S174>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S174>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S174>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S174>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S174>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S174>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S174>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S174>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S174>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S174>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S174>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S174>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S174>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S174>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S174>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S174>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S174>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S174>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S174>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S174>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S174>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S174>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S174>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S174>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S174>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S174>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S174>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S174>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S174>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S174>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S174>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S174>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S174>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S174>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S174>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S174>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S174>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S174>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S174>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S174>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S174>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S174>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S174>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S174>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S174>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S174>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S174>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S174>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S174>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S174>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S174>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S174>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S174>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S174>/VSPS Starboard'
                                        */
  real_T R31_Value_m;                  /* Expression: 0
                                        * '<S179>/R31'
                                        */
  real_T R32_Value_d;                  /* Expression: 0
                                        * '<S179>/R32'
                                        */
  real_T R13_Value_l;                  /* Expression: 0
                                        * '<S179>/R13'
                                        */
  real_T R23_Value_c;                  /* Expression: 0
                                        * '<S179>/R23'
                                        */
  real_T R33_Value_b;                  /* Expression: 1
                                        * '<S179>/R33'
                                        */
  uint8_T Gain1_Gain_n;                /* Computed Parameter: Gain
                                        * '<S79>/Gain1'
                                        */
  uint8_T Gain_Gain_l;                 /* Computed Parameter: Gain
                                        * '<S81>/Gain'
                                        */
  uint8_T Gain_Gain_fd;                /* Computed Parameter: Gain
                                        * '<S82>/Gain'
                                        */
  uint8_T Gain1_Gain_i;                /* Computed Parameter: Gain
                                        * '<S82>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_NLPIDVersion2 {
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
extern Parameters_NLPIDVersion2 NLPIDVersion2_P;

/* Block signals (auto storage) */
extern BlockIO_NLPIDVersion2 NLPIDVersion2_B;

/* Continuous states (auto storage) */
extern ContinuousStates_NLPIDVersion2 NLPIDVersion2_X;

/* Block states (auto storage) */
extern D_Work_NLPIDVersion2 NLPIDVersion2_DWork;

/* Constant parameters (auto storage) */
extern const ConstParam_NLPIDVersion2 NLPIDVersion2_ConstP;

/* Model entry point functions */
extern void NLPIDVersion2_initialize(boolean_T firstTime);
extern void NLPIDVersion2_output(int_T tid);
extern void NLPIDVersion2_update(int_T tid);
extern void NLPIDVersion2_terminate(void);

/* Real-time Model object */
extern RT_MODEL_NLPIDVersion2 *NLPIDVersion2_M;

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
 * '<Root>' : NLPIDVersion2
 * '<S1>'   : NLPIDVersion2/Inputs from LabVIEW
 * '<S2>'   : NLPIDVersion2/Main Subsystems
 * '<S3>'   : NLPIDVersion2/Outputs to LabVIEW
 * '<S4>'   : NLPIDVersion2/Inputs from LabVIEW/Linear Simulator
 * '<S5>'   : NLPIDVersion2/Inputs from LabVIEW/Path
 * '<S6>'   : NLPIDVersion2/Inputs from LabVIEW/PlayStation3
 * '<S7>'   : NLPIDVersion2/Inputs from LabVIEW/Setpoint
 * '<S8>'   : NLPIDVersion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning
 * '<S9>'   : NLPIDVersion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II
 * '<S10>'  : NLPIDVersion2/Inputs from LabVIEW/Path/Ellipse
 * '<S11>'  : NLPIDVersion2/Inputs from LabVIEW/Path/Linear
 * '<S12>'  : NLPIDVersion2/Inputs from LabVIEW/Setpoint/Degrees to Radians
 * '<S13>'  : NLPIDVersion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd
 * '<S14>'  : NLPIDVersion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki
 * '<S15>'  : NLPIDVersion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp
 * '<S16>'  : NLPIDVersion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q
 * '<S17>'  : NLPIDVersion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d
 * '<S18>'  : NLPIDVersion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i
 * '<S19>'  : NLPIDVersion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p
 * '<S20>'  : NLPIDVersion2/Main Subsystems/C//S Enterprise 1 Matrices
 * '<S21>'  : NLPIDVersion2/Main Subsystems/Control
 * '<S22>'  : NLPIDVersion2/Main Subsystems/Data logging
 * '<S23>'  : NLPIDVersion2/Main Subsystems/Guidance
 * '<S24>'  : NLPIDVersion2/Main Subsystems/Naviagation
 * '<S25>'  : NLPIDVersion2/Main Subsystems/Plant
 * '<S26>'  : NLPIDVersion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix
 * '<S27>'  : NLPIDVersion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix
 * '<S28>'  : NLPIDVersion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix
 * '<S29>'  : NLPIDVersion2/Main Subsystems/Control/Control Switch
 * '<S30>'  : NLPIDVersion2/Main Subsystems/Control/DP control
 * '<S31>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID
 * '<S32>'  : NLPIDVersion2/Main Subsystems/Control/PS3 u input control
 * '<S33>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation
 * '<S34>'  : NLPIDVersion2/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1
 * '<S35>'  : NLPIDVersion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]
 * '<S36>'  : NLPIDVersion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1
 * '<S37>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q
 * '<S38>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s
 * '<S39>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Control law
 * '<S40>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/R(psi)
 * '<S41>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Update laws
 * '<S42>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/a_d
 * '<S43>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/e2
 * '<S44>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/e_1
 * '<S45>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/v_d
 * '<S46>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/zeta
 * '<S47>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q eq
 * '<S48>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq
 * '<S49>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^s eq
 * '<S50>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^t eq
 * '<S51>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/f_q^T
 * '<S52>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/psi_los^q^2T
 * '<S53>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s eq
 * '<S54>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq
 * '<S55>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq
 * '<S56>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^t eq
 * '<S57>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF
 * '<S58>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FL
 * '<S59>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID
 * '<S60>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T
 * '<S61>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S^T
 * '<S62>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R^T
 * '<S63>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/Update laws/Transpose
 * '<S64>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/a_d/v_d^q
 * '<S65>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/a_d/v_d^s
 * '<S66>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/a_d/v_d^t
 * '<S67>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi
 * '<S68>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1
 * '<S69>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]
 * '<S70>'  : NLPIDVersion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]
 * '<S71>'  : NLPIDVersion2/Main Subsystems/Control/PS3 u input control/Subsystem
 * '<S72>'  : NLPIDVersion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau
 * '<S73>'  : NLPIDVersion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act
 * '<S74>'  : NLPIDVersion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e
 * '<S75>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040
 * '<S76>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/tau to f_act
 * '<S77>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act
 * '<S78>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3
 * '<S79>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3
 * '<S80>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3
 * '<S81>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3
 * '<S82>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4
 * '<S83>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391
 * '<S84>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731
 * '<S85>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391
 * '<S86>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731
 * '<S87>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451
 * '<S88>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451
 * '<S89>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0
 * '<S90>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0
 * '<S91>'  : NLPIDVersion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0
 * '<S92>'  : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following
 * '<S93>'  : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading
 * '<S94>'  : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight
 * '<S95>'  : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path
 * '<S96>'  : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment
 * '<S97>'  : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq
 * '<S98>'  : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq
 * '<S99>'  : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq
 * '<S100>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]
 * '<S101>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot
 * '<S102>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot
 * '<S103>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot
 * '<S104>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading
 * '<S105>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals
 * '<S106>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel
 * '<S107>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq
 * '<S108>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq
 * '<S109>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq
 * '<S110>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq
 * '<S111>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq
 * '<S112>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq
 * '<S113>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq
 * '<S114>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq
 * '<S115>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq
 * '<S116>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq
 * '<S117>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq
 * '<S118>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose
 * '<S119>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose
 * '<S120>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1
 * '<S121>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2
 * '<S122>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq
 * '<S123>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq
 * '<S124>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq
 * '<S125>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq
 * '<S126>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq
 * '<S127>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq
 * '<S128>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]
 * '<S129>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1
 * '<S130>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2
 * '<S131>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2
 * '<S132>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T
 * '<S133>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2
 * '<S134>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)
 * '<S135>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T
 * '<S136>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T
 * '<S137>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq
 * '<S138>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq
 * '<S139>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq
 * '<S140>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I
 * '<S141>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path
 * '<S142>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter
 * '<S143>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path
 * '<S144>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq
 * '<S145>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq
 * '<S146>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq
 * '<S147>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq
 * '<S148>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq
 * '<S149>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T
 * '<S150>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter
 * '<S151>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor
 * '<S152>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor
 * '<S153>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor
 * '<S154>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor
 * '<S155>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1
 * '<S156>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x
 * '<S157>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y
 * '<S158>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq
 * '<S159>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq
 * '<S160>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq
 * '<S161>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T
 * '<S162>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq
 * '<S163>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq
 * '<S164>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq
 * '<S165>' : NLPIDVersion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T
 * '<S166>' : NLPIDVersion2/Main Subsystems/Naviagation/Input from SIT
 * '<S167>' : NLPIDVersion2/Main Subsystems/Naviagation/Navigation Switch
 * '<S168>' : NLPIDVersion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix
 * '<S169>' : NLPIDVersion2/Main Subsystems/Plant/CSE1 actuator
 * '<S170>' : NLPIDVersion2/Main Subsystems/Plant/Linear Simulator
 * '<S171>' : NLPIDVersion2/Main Subsystems/Plant/Thruster setting workaround
 * '<S172>' : NLPIDVersion2/Main Subsystems/Plant/saturation
 * '<S173>' : NLPIDVersion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster
 * '<S174>' : NLPIDVersion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller
 * '<S175>' : NLPIDVersion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic
 * '<S176>' : NLPIDVersion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1
 * '<S177>' : NLPIDVersion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2
 * '<S178>' : NLPIDVersion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics
 * '<S179>' : NLPIDVersion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)
 * '<S180>' : NLPIDVersion2/Outputs to LabVIEW/Battery Voltage
 * '<S181>' : NLPIDVersion2/Outputs to LabVIEW/Command
 * '<S182>' : NLPIDVersion2/Outputs to LabVIEW/Naviagtion
 * '<S183>' : NLPIDVersion2/Outputs to LabVIEW/Visualization
 */
#endif                                 /* RTW_HEADER_NLPIDVersion2_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_NLPIDVersion2
#ifdef RVE
#ifdef MULTITASKING

Parameters_NLPIDVersion2 rtParameter[NUMST+!TID01EQ];

#define NLPIDVersion2_P                (*param_lookup[tid][READSIDE])

Parameters_NLPIDVersion2 *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_NLPIDVersion2 rtParameter[2];

#define NLPIDVersion2_P                rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
