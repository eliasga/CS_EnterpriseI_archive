/*
 * CSE1_CV3_1Straight.h
 *
 * Real-Time Workshop code generation for Simulink model "CSE1_CV3_1Straight.mdl".
 *
 * Model Version              : 1.296
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Fri Feb 14 09:47:35 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_CSE1_CV3_1Straight_h_
#define RTW_HEADER_CSE1_CV3_1Straight_h_
#ifndef CSE1_CV3_1Straight_COMMON_INCLUDES_
# define CSE1_CV3_1Straight_COMMON_INCLUDES_
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
#include "rt_pow_snf.h"
#include "rt_rem_snf.h"
#include "rt_round_snf.h"
#include "rt_MAX.h"
#include "rt_MIN.h"
#endif                                 /* CSE1_CV3_1Straight_COMMON_INCLUDES_ */

#include "CSE1_CV3_1Straight_types.h"

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
#define CSE1_CV3_1Straight_rtModel     RT_MODEL_CSE1_CV3_1Straight

/* Block signals (auto storage) */
typedef struct {
  real_T QTMIn[9];                     /* '<S289>/QTM In' */
  real_T QTMIn9Residual;               /* '<S289>/QTM In9 Residual' */
  real_T QTMIn3;                       /* '<S289>/QTM In3' */
  real_T mm2mx;                        /* '<S289>/mm2m x' */
  real_T QTMIn4;                       /* '<S289>/QTM In4' */
  real_T mm2my;                        /* '<S289>/mm2m y' */
  real_T QTMIn6;                       /* '<S289>/QTM In6' */
  real_T d2ryaw;                       /* '<S289>/d2r yaw' */
  real_T EtaSwitch[3];                 /* '<S4>/Eta Switch' */
  real_T eta_surge;                    /* '<S4>/eta_surge' */
  real_T eta_sway;                     /* '<S4>/eta_sway' */
  real_T eta_yaw;                      /* '<S4>/eta_yaw' */
  real_T QTMIn8;                       /* '<S289>/QTM In8' */
  real_T d2rroll;                      /* '<S289>/d2r roll' */
  real_T QTMIn7;                       /* '<S289>/QTM In7' */
  real_T d2rpitch;                     /* '<S289>/d2r pitch' */
  real_T sintheta[3];                  /* '<S290>/sin(theta)' */
  real_T costheta[3];                  /* '<S290>/cos(theta)' */
  real_T R11;                          /* '<S290>/R11' */
  real_T R21;                          /* '<S290>/R21 ' */
  real_T R31;                          /* '<S290>/R31 ' */
  real_T R12;                          /* '<S290>/R12' */
  real_T R22;                          /* '<S290>/R22' */
  real_T R32;                          /* '<S290>/R32' */
  real_T R13;                          /* '<S290>/R13' */
  real_T R23;                          /* '<S290>/R23' */
  real_T R33;                          /* '<S290>/R33' */
  real_T Reshape9x13x3[9];             /* '<S290>/Reshape 9x1->3x3' */
  real_T MatrixConcatenate2[36];       /* '<S289>/Matrix Concatenate2' */
  real_T QTMIn5;                       /* '<S289>/QTM In5' */
  real_T mm2mz;                        /* '<S289>/mm2m z' */
  real_T nu[6];                        /* '<S289>/nu' */
  real_T Product[6];                   /* '<S289>/Product' */
  real_T NuSwitch[3];                  /* '<S4>/Nu Switch' */
  real_T nu_surge;                     /* '<S4>/nu_surge' */
  real_T nu_sway;                      /* '<S4>/nu_sway' */
  real_T nu_yaw;                       /* '<S4>/nu_yaw' */
  real_T Gain1;                        /* '<S288>/Gain1' */
  real_T TransferFcn;                  /* '<S219>/Transfer Fcn' */
  real_T TransferFcn1;                 /* '<S219>/Transfer Fcn1' */
  real_T TransferFcn2;                 /* '<S219>/Transfer Fcn2' */
  real_T MultiportSwitch[3];           /* '<S219>/Multiport Switch' */
  real_T eta_dDPN;                     /* '<S219>/eta_d DP N' */
  real_T eta_dDPE;                     /* '<S219>/eta_d DP E' */
  real_T eta_dDPPsi;                   /* '<S219>/eta_d DP Psi' */
  real_T q_x_0;                        /* '<S105>/q_x_0' */
  real_T q_y_0;                        /* '<S105>/q_y_0' */
  real_T Integrator[2];                /* '<S62>/Integrator' */
  real_T q_x_0_c;                      /* '<S187>/q_x_0' */
  real_T q_y_0_p;                      /* '<S187>/q_y_0' */
  real_T Integrator_i[2];              /* '<S135>/Integrator' */
  real_T qswitch[2];                   /* '<S1>/q switch' */
  real_T q_xgain;                      /* '<S1>/q_x gain' */
  real_T q_ygain;                      /* '<S1>/q_y gain' */
  real_T s_0;                          /* '<S62>/s_0' */
  real_T Integrator1;                  /* '<S62>/Integrator1' */
  real_T s_0_d;                        /* '<S135>/s_0' */
  real_T Integrator1_f;                /* '<S135>/Integrator1' */
  real_T sswitch;                      /* '<S1>/s switch' */
  real_T sgain;                        /* '<S1>/s gain' */
  real_T pathx_d;                      /* '<S2>/path x_d' */
  real_T pathy_d;                      /* '<S2>/path y_d' */
  real_T pathpsi_d;                    /* '<S2>/path psi_d' */
  real_T LabVIEWu_1;                   /* '<S11>/LabVIEW u_1' */
  real_T LabVIEWu_2;                   /* '<S11>/LabVIEW u_2' */
  real_T LabVIEWu_3;                   /* '<S11>/LabVIEW u_3' */
  real_T LabVIEWu_4;                   /* '<S11>/LabVIEW u_4' */
  real_T LabVIEWu_5;                   /* '<S11>/LabVIEW u_5' */
  real_T ypositionofleftanalogstick11; /* '<S10>/ScalingLY' */
  real_T u_1;                          /* '<S8>/PS3 u_1' */
  real_T xpositionofleftanalogstick11; /* '<S10>/ScalingLX' */
  real_T u_2;                          /* '<S8>/PS3 u_2' */
  real_T ypositionofrightanalogstick11;/* '<S10>/ScalingRY' */
  real_T u_3;                          /* '<S8>/PS3 u_3' */
  real_T xpositionofrightanalogstick11;/* '<S10>/Scaling_RX' */
  real_T u_4;                          /* '<S8>/PS3 u_4' */
  real_T BowThrusterdirection;         /* '<S8>/Add' */
  real_T u_5;                          /* '<S8>/PS3 u_5' */
  real_T l_x1;                         /* '<S218>/-l_x1' */
  real_T l_y2;                         /* '<S218>/-l_y2' */
  real_T l_x2;                         /* '<S218>/-l_x2' */
  real_T x5[15];                       /* '<S218>/3x5' */
  real_T Pseudoinverse[15];            /* '<S197>/Pseudoinverse' */
  real_T Sum1;                         /* '<S12>/Sum1' */
  real_T tau_surge;                    /* '<S12>/tau_surge' */
  real_T Sum2;                         /* '<S12>/Sum2' */
  real_T tau_sway;                     /* '<S12>/tau_sway' */
  real_T Sum;                          /* '<S12>/Sum' */
  real_T tau_yaw;                      /* '<S12>/tau_yaw' */
  real_T TmpHiddenBufferAtProductInport2[3];/* 'synthesized block' */
  real_T Product_c[5];                 /* '<S197>/Product' */
  real_T f_10;                         /* '<S198>/f_1 < 0' */
  real_T f_10_i;                       /* '<S198>/f_1 > 0' */
  real_T MultiportSwitch_p;            /* '<S198>/Multiport Switch' */
  real_T f_20;                         /* '<S199>/f_2 < 0' */
  real_T f_20_k;                       /* '<S199>/f_2 > 0' */
  real_T MultiportSwitch_pq;           /* '<S199>/Multiport Switch' */
  real_T f_30;                         /* '<S200>/f_3 < 0' */
  real_T f_30_i;                       /* '<S200>/f_3 > 0' */
  real_T MultiportSwitch_l;            /* '<S200>/Multiport Switch' */
  real_T f_40;                         /* '<S201>/f_4 < 0' */
  real_T f_40_n;                       /* '<S201>/f_4 > 0' */
  real_T MultiportSwitch_g;            /* '<S201>/Multiport Switch' */
  real_T f_50;                         /* '<S202>/f_5 < 0' */
  real_T f_50_g;                       /* '<S202>/f_5 > 0' */
  real_T MultiportSwitch_a;            /* '<S202>/Multiport Switch' */
  real_T Saturation[5];                /* '<S12>/Saturation' */
  real_T Joysticku_1;                  /* '<S12>/Joystick u_1' */
  real_T Joysticku_2;                  /* '<S12>/Joystick u_2' */
  real_T Joysticku_3;                  /* '<S12>/Joystick u_3' */
  real_T Joysticku_4;                  /* '<S12>/Joystick u_4' */
  real_T Joysticku_5;                  /* '<S12>/Joystick u_5' */
  real_T l_x1_k;                       /* '<S47>/-l_x1' */
  real_T l_y2_f;                       /* '<S47>/-l_y2' */
  real_T l_x2_a;                       /* '<S47>/-l_x2' */
  real_T x5_i[15];                     /* '<S47>/3x5' */
  real_T Pseudoinverse_g[15];          /* '<S26>/Pseudoinverse' */
  real_T eta[3];                       /* '<S15>/Integrator' */
  real_T Saturation_c;                 /* '<S23>/Saturation' */
  real_T Sign;                         /* '<S23>/Sign' */
  real_T Gain;                         /* '<S23>/Gain' */
  real_T Sum1_k;                       /* '<S23>/Sum1' */
  real_T MathFunction;                 /* '<S23>/Math Function' */
  real_T Sum_m;                        /* '<S23>/Sum' */
  real_T MultiportSwitch_b[3];         /* '<S6>/Multiport Switch' */
  real_T psi;                          /* '<S14>/yaw angle' */
  real_T Saturation_p;                 /* '<S19>/Saturation' */
  real_T Sign_o;                       /* '<S19>/Sign' */
  real_T Gain_c;                       /* '<S19>/Gain' */
  real_T Sum1_o;                       /* '<S19>/Sum1' */
  real_T MathFunction_j;               /* '<S19>/Math Function' */
  real_T Sum_o;                        /* '<S19>/Sum' */
  real_T etaN;                         /* '<S14>/eta N' */
  real_T etaE;                         /* '<S14>/eta E' */
  real_T etaPsi;                       /* '<S14>/eta Psi' */
  real_T regulationerror[3];           /* '<S14>/Sum2' */
  real_T Reg_e_N_hil;                  /* '<S14>/Reg_e_N_hil' */
  real_T Reg_e_E_hil;                  /* '<S14>/Reg_e_E_hil' */
  real_T Reg_e_Psi_hil;                /* '<S14>/Reg_e_Psi_hil' */
  real_T Saturation_a;                 /* '<S18>/Saturation' */
  real_T Sign_m;                       /* '<S18>/Sign' */
  real_T Gain_ce;                      /* '<S18>/Gain' */
  real_T Sum1_h;                       /* '<S18>/Sum1' */
  real_T MathFunction_e;               /* '<S18>/Math Function' */
  real_T Sum_i;                        /* '<S18>/Sum' */
  real_T Row1;                         /* '<S17>/Row1' */
  real_T Row2;                         /* '<S17>/Row2' */
  real_T Row3;                         /* '<S17>/Row3' */
  real_T TmpHiddenBufferAtKpInport1[3];/* '<S14>/Transposed rotation  matrix in yaw1' */
  real_T Kp[3];                        /* '<S14>/Kp' */
  real_T Product2[3];                  /* '<S14>/Product2' */
  real_T K_p1;                         /* '<S14>/K_p 1' */
  real_T K_p2;                         /* '<S14>/K_p 2' */
  real_T K_p3;                         /* '<S14>/K_p 3' */
  real_T Integrator_o[3];              /* '<S14>/Integrator' */
  real_T Ki[3];                        /* '<S14>/Ki' */
  real_T Product1[3];                  /* '<S14>/Product1' */
  real_T K_i1;                         /* '<S14>/K_i 1' */
  real_T K_i2;                         /* '<S14>/K_i 2' */
  real_T K_i3;                         /* '<S14>/K_i 3' */
  real_T Sum3[3];                      /* '<S14>/Sum3' */
  real_T TmpHiddenBufferAtProduct2Inport[3];/* 'synthesized block' */
  real_T nu_d[3];                      /* '<S15>/Integrator4' */
  real_T MultiportSwitch1[3];          /* '<S6>/Multiport Switch1' */
  real_T Kd[3];                        /* '<S14>/Kd' */
  real_T Product_l[3];                 /* '<S14>/Product' */
  real_T K_d1;                         /* '<S14>/K_d 1' */
  real_T K_d2;                         /* '<S14>/K_d 2' */
  real_T K_d3;                         /* '<S14>/K_d 3' */
  real_T Sum1_j[3];                    /* '<S14>/Sum1' */
  real_T DPtau_surge;                  /* '<S6>/DP tau_surge' */
  real_T DPtau_sway;                   /* '<S6>/DP tau_sway' */
  real_T DPtau_yaw;                    /* '<S6>/DP tau_yaw' */
  real_T TmpHiddenBufferAtProductInpor_k[3];/* 'synthesized block' */
  real_T Product_f[5];                 /* '<S26>/Product' */
  real_T f_10_m;                       /* '<S27>/f_1 < 0' */
  real_T f_10_l;                       /* '<S27>/f_1 > 0' */
  real_T MultiportSwitch_i;            /* '<S27>/Multiport Switch' */
  real_T DPu_1;                        /* '<S6>/DP u_1' */
  real_T f_20_d;                       /* '<S28>/f_2 < 0' */
  real_T f_20_a;                       /* '<S28>/f_2 > 0' */
  real_T MultiportSwitch_l3;           /* '<S28>/Multiport Switch' */
  real_T DPu_2;                        /* '<S6>/DP u_2' */
  real_T f_30_e;                       /* '<S29>/f_3 < 0' */
  real_T f_30_f;                       /* '<S29>/f_3 > 0' */
  real_T MultiportSwitch_j;            /* '<S29>/Multiport Switch' */
  real_T DPu_3;                        /* '<S6>/DP u_3' */
  real_T f_40_c;                       /* '<S30>/f_4 < 0' */
  real_T f_40_g;                       /* '<S30>/f_4 > 0' */
  real_T MultiportSwitch_c;            /* '<S30>/Multiport Switch' */
  real_T DPu_4;                        /* '<S6>/DP u_4' */
  real_T f_50_o;                       /* '<S31>/f_5 < 0' */
  real_T f_50_p;                       /* '<S31>/f_5 > 0' */
  real_T MultiportSwitch_m;            /* '<S31>/Multiport Switch' */
  real_T DPu_5;                        /* '<S6>/DP u_5' */
  real_T Saturation_cs[5];             /* '<S6>/Saturation' */
  real_T l_x1_a;                       /* '<S103>/-l_x1' */
  real_T l_y2_i;                       /* '<S103>/-l_y2' */
  real_T l_x2_d;                       /* '<S103>/-l_x2' */
  real_T x5_p[15];                     /* '<S103>/3x5' */
  real_T Pseudoinverse_o[15];          /* '<S82>/Pseudoinverse' */
  real_T R11_a;                        /* '<S57>/R11' */
  real_T R21_l;                        /* '<S57>/R21' */
  real_T R12_i;                        /* '<S57>/R12' */
  real_T u;                            /* '<S57>/-1' */
  real_T R22_c;                        /* '<S57>/R22' */
  real_T Rpsi[9];                      /* '<S57>/R(psi)' */
  real_T MathFunction_l[9];            /* '<S58>/Math Function' */
  real_T x3[9];                        /* '<S54>/3x3' */
  real_T Integrator_n[3];              /* '<S52>/Integrator' */
  real_T Product_p[3];                 /* '<S50>/Product' */
  real_T x3_g[9];                      /* '<S53>/3x3' */
  real_T u_i;                          /* '<S50>/4' */
  real_T Divide;                       /* '<S50>/Divide' */
  real_T Add1[9];                      /* '<S50>/Add1' */
  real_T Rpsi_n[9];                    /* '<S55>/R(psi)' */
  real_T Product_n[9];                 /* '<S64>/Product' */
  real_T Subtract[9];                  /* '<S64>/Subtract' */
  real_T Gain_j;                       /* '<S115>/Gain' */
  real_T Saturation_o;                 /* '<S113>/Saturation' */
  real_T Sign_n;                       /* '<S113>/Sign' */
  real_T Gain_d;                       /* '<S113>/Gain' */
  real_T Sum1_p;                       /* '<S113>/Sum1' */
  real_T MathFunction_g;               /* '<S113>/Math Function' */
  real_T Sum_n;                        /* '<S113>/Sum' */
  real_T Gain1_k;                      /* '<S114>/Gain1' */
  real_T q_x;                          /* '<S2>/q_x' */
  real_T q_y;                          /* '<S2>/q_y' */
  real_T psi_los;                      /* '<S2>/psi_los' */
  real_T Subtract_l[3];                /* '<S68>/Subtract' */
  real_T Gain_f;                       /* '<S118>/Gain' */
  real_T Saturation_l;                 /* '<S116>/Saturation' */
  real_T Sign_i;                       /* '<S116>/Sign' */
  real_T Gain_h;                       /* '<S116>/Gain' */
  real_T Sum1_jz;                      /* '<S116>/Sum1' */
  real_T MathFunction_a;               /* '<S116>/Math Function' */
  real_T Sum_g;                        /* '<S116>/Sum' */
  real_T Gain1_l;                      /* '<S117>/Gain1' */
  real_T TmpHiddenBufferAtProductInpor_e[3];/* '<S68>/heading to pipi1' */
  real_T Product_j[3];                 /* '<S68>/Product' */
  real_T Product1_b[3];                /* '<S64>/Product1' */
  real_T VectorConcatenate[3];         /* '<S70>/Vector Concatenate' */
  real_T VectorConcatenate_n[3];       /* '<S76>/Vector Concatenate' */
  real_T Add[3];                       /* '<S64>/Add' */
  real_T Product2_k[3];                /* '<S64>/Product2' */
  real_T Sum_og[3];                    /* '<S64>/Sum' */
  real_T Subtract_f[3];                /* '<S69>/Subtract' */
  real_T Product1_a[3];                /* '<S50>/Product1' */
  real_T X_u;                          /* '<S80>/-X_u' */
  real_T Y_v;                          /* '<S80>/-Y_v' */
  real_T N_v;                          /* '<S80>/-N_v' */
  real_T Y_vr;                         /* '<S80>/-Y_vr' */
  real_T N_r;                          /* '<S80>/-N_r' */
  real_T LinearDampningmatrix[9];      /* '<S80>/Linear Dampning matrix' */
  real_T Product2_c[3];                /* '<S50>/Product2' */
  real_T M_11;                         /* '<S56>/M_11' */
  real_T M_22;                         /* '<S56>/M_22' */
  real_T mx_g;                         /* '<S56>/m x_g' */
  real_T M_32;                         /* '<S56>/M_32' */
  real_T M_23;                         /* '<S56>/M_23' */
  real_T M_33;                         /* '<S56>/M_33' */
  real_T x3_p[9];                      /* '<S56>/3x3' */
  real_T Product1_d[9];                /* '<S67>/Product1' */
  real_T Subtract_k[9];                /* '<S67>/Subtract' */
  real_T S12;                          /* '<S59>/S12' */
  real_T Sr[9];                        /* '<S59>/S(r)' */
  real_T MathFunction_k[9];            /* '<S60>/Math Function' */
  real_T Product_fy[3];                /* '<S67>/Product' */
  real_T Add_j[3];                     /* '<S67>/Add' */
  real_T Product2_d[3];                /* '<S67>/Product2' */
  real_T Add1_o[3];                    /* '<S67>/Add1' */
  real_T Product3[3];                  /* '<S67>/Product3' */
  real_T VectorConcatenate_o[3];       /* '<S73>/Vector Concatenate' */
  real_T VectorConcatenate_d[3];       /* '<S79>/Vector Concatenate' */
  real_T Add2[3];                      /* '<S67>/Add2' */
  real_T Product4[3];                  /* '<S67>/Product4' */
  real_T Sum_ok[3];                    /* '<S67>/Sum' */
  real_T Product4_d[3];                /* '<S50>/Product4' */
  real_T Product1_m[9];                /* '<S65>/Product1' */
  real_T Subtract_j[9];                /* '<S65>/Subtract' */
  real_T Product3_e[6];                /* '<S65>/Product3' */
  real_T MathFunction_gw[2];           /* '<S74>/Math Function' */
  real_T MathFunction_n[4];            /* '<S75>/Math Function' */
  real_T Product_d[2];                 /* '<S71>/Product' */
  real_T Product1_ad[2];               /* '<S71>/Product1' */
  real_T Add_jn[2];                    /* '<S71>/Add' */
  real_T MatrixConcatenate[6];         /* '<S71>/Matrix Concatenate' */
  real_T Product_i[2];                 /* '<S77>/Product' */
  real_T Product1_h[2];                /* '<S77>/Product1' */
  real_T Add_o[2];                     /* '<S77>/Add' */
  real_T MatrixConcatenate_l[6];       /* '<S77>/Matrix Concatenate' */
  real_T Add2_c[6];                    /* '<S65>/Add2' */
  real_T Product4_l[6];                /* '<S65>/Product4' */
  real_T Add3[6];                      /* '<S65>/Add3' */
  real_T Integrator2[2];               /* '<S62>/Integrator2' */
  real_T Add2_k[2];                    /* '<S50>/Add2' */
  real_T Product5[3];                  /* '<S50>/Product5' */
  real_T Product1_l[9];                /* '<S66>/Product1' */
  real_T Subtract_fp[9];               /* '<S66>/Subtract' */
  real_T Product3_d[3];                /* '<S66>/Product3' */
  real_T Product_o;                    /* '<S72>/Product' */
  real_T Product1_i;                   /* '<S72>/Product1' */
  real_T VectorConcatenate_g[3];       /* '<S72>/Vector Concatenate' */
  real_T Product_a;                    /* '<S78>/Product' */
  real_T Product1_g;                   /* '<S78>/Product1' */
  real_T VectorConcatenate_e[3];       /* '<S78>/Vector Concatenate' */
  real_T Add2_j[3];                    /* '<S66>/Add2' */
  real_T Product4_c[3];                /* '<S66>/Product4' */
  real_T Add3_o[3];                    /* '<S66>/Add3' */
  real_T Product6[3];                  /* '<S50>/Product6' */
  real_T Sum_e[3];                     /* '<S50>/Sum' */
  real_T Product_h[5];                 /* '<S82>/Product' */
  real_T f_10_p;                       /* '<S83>/f_1 < 0' */
  real_T f_10_c;                       /* '<S83>/f_1 > 0' */
  real_T MultiportSwitch_id;           /* '<S83>/Multiport Switch' */
  real_T f_20_f;                       /* '<S84>/f_2 < 0' */
  real_T f_20_h;                       /* '<S84>/f_2 > 0' */
  real_T MultiportSwitch_f;            /* '<S84>/Multiport Switch' */
  real_T f_30_k;                       /* '<S85>/f_3 < 0' */
  real_T f_30_o;                       /* '<S85>/f_3 > 0' */
  real_T MultiportSwitch_ga;           /* '<S85>/Multiport Switch' */
  real_T f_40_f;                       /* '<S86>/f_4 < 0' */
  real_T f_40_cs;                      /* '<S86>/f_4 > 0' */
  real_T MultiportSwitch_me;           /* '<S86>/Multiport Switch' */
  real_T f_50_f;                       /* '<S87>/f_5 < 0' */
  real_T f_50_pk;                      /* '<S87>/f_5 > 0' */
  real_T MultiportSwitch_bl;           /* '<S87>/Multiport Switch' */
  real_T l_x1_d;                       /* '<S185>/-l_x1' */
  real_T l_y2_j;                       /* '<S185>/-l_y2' */
  real_T l_x2_l;                       /* '<S185>/-l_x2' */
  real_T x5_ib[15];                    /* '<S185>/3x5' */
  real_T Pseudoinverse_f[15];          /* '<S164>/Pseudoinverse' */
  real_T R11_j;                        /* '<S132>/R11' */
  real_T R21_b;                        /* '<S132>/R21' */
  real_T R12_c;                        /* '<S132>/R12' */
  real_T R22_d;                        /* '<S132>/R22' */
  real_T Rpsi_p[9];                    /* '<S132>/R(psi)' */
  real_T MathFunction_i[9];            /* '<S133>/Math Function' */
  real_T Rpsi_l[9];                    /* '<S131>/R(psi)' */
  real_T Gain_jl;                      /* '<S159>/Gain' */
  real_T Saturation_pv;                /* '<S157>/Saturation' */
  real_T Sign_mi;                      /* '<S157>/Sign' */
  real_T Gain_b;                       /* '<S157>/Gain' */
  real_T Sum1_n;                       /* '<S157>/Sum1' */
  real_T MathFunction_gi;              /* '<S157>/Math Function' */
  real_T Sum_c;                        /* '<S157>/Sum' */
  real_T Gain1_a;                      /* '<S158>/Gain1' */
  real_T Subtract_d[3];                /* '<S126>/Subtract' */
  real_T Gain_f4;                      /* '<S162>/Gain' */
  real_T Saturation_c0;                /* '<S160>/Saturation' */
  real_T Sign_i4;                      /* '<S160>/Sign' */
  real_T Gain_i;                       /* '<S160>/Gain' */
  real_T Sum1_c;                       /* '<S160>/Sum1' */
  real_T MathFunction_li;              /* '<S160>/Math Function' */
  real_T Sum_o5;                       /* '<S160>/Sum' */
  real_T Gain1_f;                      /* '<S161>/Gain1' */
  real_T TmpHiddenBufferAtProductInport3[3];/* 'synthesized block' */
  real_T Product_le[3];                /* '<S152>/Product' */
  real_T Rpsi_i[9];                    /* '<S130>/R(psi)' */
  real_T zeta[3];                      /* '<S9>/zeta' */
  real_T Product1_o[3];                /* '<S152>/Product1' */
  real_T Rpsi_k[9];                    /* '<S129>/R(psi)' */
  real_T VectorConcatenate_es[3];      /* '<S139>/Vector Concatenate' */
  real_T VectorConcatenate_oq[3];      /* '<S145>/Vector Concatenate' */
  real_T Add_p[3];                     /* '<S138>/Add' */
  real_T Product_fp[3];                /* '<S137>/Product' */
  real_T Subtract_ji[3];               /* '<S137>/Subtract' */
  real_T Product2_b[3];                /* '<S152>/Product2' */
  real_T Sum_f[3];                     /* '<S152>/Sum' */
  real_T X_u_o;                        /* '<S154>/-X_u' */
  real_T Y_v_g;                        /* '<S154>/-Y_v' */
  real_T N_v_b;                        /* '<S154>/-N_v' */
  real_T Y_vr_n;                       /* '<S154>/-Y_vr' */
  real_T N_r_k;                        /* '<S154>/-N_r' */
  real_T LinearDampningmatrix_p[9];    /* '<S154>/Linear Dampning matrix' */
  real_T Product1_hd[3];               /* '<S151>/Product1' */
  real_T M_11_p;                       /* '<S153>/M_11' */
  real_T M_22_m;                       /* '<S153>/M_22' */
  real_T mx_g_k;                       /* '<S153>/m x_g' */
  real_T M_32_a;                       /* '<S153>/M_32' */
  real_T M_23_p;                       /* '<S153>/M_23' */
  real_T M_33_m;                       /* '<S153>/M_33' */
  real_T x3_k[9];                      /* '<S153>/3x3' */
  real_T MathFunction_h[2];            /* '<S143>/Math Function' */
  real_T MathFunction_f[4];            /* '<S144>/Math Function' */
  real_T Product_py[2];                /* '<S140>/Product' */
  real_T Product1_ak[2];               /* '<S140>/Product1' */
  real_T Add_l[2];                     /* '<S140>/Add' */
  real_T MatrixConcatenate_o[6];       /* '<S140>/Matrix Concatenate' */
  real_T Product_b[2];                 /* '<S146>/Product' */
  real_T Product1_g2[2];               /* '<S146>/Product1' */
  real_T Add_d[2];                     /* '<S146>/Add' */
  real_T MatrixConcatenate_n[6];       /* '<S146>/Matrix Concatenate' */
  real_T Add_b[6];                     /* '<S188>/Add' */
  real_T omega_q[2];                   /* '<S135>/omega_q' */
  real_T Add_po[2];                    /* '<S135>/Add' */
  real_T Product_bl[3];                /* '<S136>/Product' */
  real_T Product_be;                   /* '<S141>/Product' */
  real_T Product1_m5;                  /* '<S141>/Product1' */
  real_T VectorConcatenate_ge[3];      /* '<S141>/Vector Concatenate' */
  real_T Product_o2;                   /* '<S147>/Product' */
  real_T Product1_f;                   /* '<S147>/Product1' */
  real_T VectorConcatenate_b[3];       /* '<S147>/Vector Concatenate' */
  real_T Add1_m[3];                    /* '<S189>/Add1' */
  real_T Product1_n[3];                /* '<S136>/Product1' */
  real_T VectorConcatenate_a[3];       /* '<S142>/Vector Concatenate' */
  real_T VectorConcatenate_nu[3];      /* '<S148>/Vector Concatenate' */
  real_T Add_h[3];                     /* '<S190>/Add' */
  real_T Sum_ek[3];                    /* '<S136>/Sum' */
  real_T Product_c4[3];                /* '<S150>/Product' */
  real_T S12_o;                        /* '<S149>/S12' */
  real_T Sr_j[9];                      /* '<S149>/S(r)' */
  real_T Product1_fg[3];               /* '<S150>/Product1' */
  real_T Subtract_a[3];                /* '<S150>/Subtract' */
  real_T Gain_iy[3];                   /* '<S150>/Gain' */
  real_T Sum_d[3];                     /* '<S125>/Sum' */
  real_T Product_hy[5];                /* '<S164>/Product' */
  real_T f_10_o;                       /* '<S165>/f_1 < 0' */
  real_T f_10_b;                       /* '<S165>/f_1 > 0' */
  real_T MultiportSwitch_ak;           /* '<S165>/Multiport Switch' */
  real_T f_20_p;                       /* '<S166>/f_2 < 0' */
  real_T f_20_l;                       /* '<S166>/f_2 > 0' */
  real_T MultiportSwitch_h;            /* '<S166>/Multiport Switch' */
  real_T f_30_fk;                      /* '<S167>/f_3 < 0' */
  real_T f_30_ig;                      /* '<S167>/f_3 > 0' */
  real_T MultiportSwitch_o;            /* '<S167>/Multiport Switch' */
  real_T f_40_b;                       /* '<S168>/f_4 < 0' */
  real_T f_40_l;                       /* '<S168>/f_4 > 0' */
  real_T MultiportSwitch_jj;           /* '<S168>/Multiport Switch' */
  real_T f_50_n;                       /* '<S169>/f_5 < 0' */
  real_T f_50_a;                       /* '<S169>/f_5 > 0' */
  real_T MultiportSwitch_jb;           /* '<S169>/Multiport Switch' */
  real_T ThrustersettingSwitch[7];     /* '<S1>/Thruster setting Switch' */
  real_T Saturation_ay[7];             /* '<S1>/Saturation' */
  real_T l_x1_b;                       /* '<S194>/-l_x1' */
  real_T l_y2_ia;                      /* '<S194>/-l_y2' */
  real_T l_x2_j;                       /* '<S194>/-l_x2' */
  real_T x5_h[15];                     /* '<S194>/3x5' */
  real_T u_1tof_1;                     /* '<S193>/u_1 to f_1' */
  real_T u_2tof_2;                     /* '<S193>/u_2 to f_2' */
  real_T u_3tof_3;                     /* '<S193>/u_3 to f_3' */
  real_T u_4tof_4;                     /* '<S193>/u_4 to f_4' */
  real_T u_5tof_5;                     /* '<S193>/u_5 to f_5' */
  real_T TmpHiddenBufferAtProductInpor_b[5];/* 'synthesized block' */
  real_T Product_lh[3];                /* '<S192>/Product' */
  real_T l_x1_c;                       /* '<S122>/-l_x1' */
  real_T l_y2_d;                       /* '<S122>/-l_y2' */
  real_T l_x2_h;                       /* '<S122>/-l_x2' */
  real_T x5_iw[15];                    /* '<S122>/3x5' */
  real_T u_1tof_1_p;                   /* '<S121>/u_1 to f_1' */
  real_T u_2tof_2_a;                   /* '<S121>/u_2 to f_2' */
  real_T u_3tof_3_b;                   /* '<S121>/u_3 to f_3' */
  real_T u_4tof_4_p;                   /* '<S121>/u_4 to f_4' */
  real_T u_5tof_5_k;                   /* '<S121>/u_5 to f_5' */
  real_T TmpHiddenBufferAtProductInpor_m[5];/* 'synthesized block' */
  real_T Product_m[3];                 /* '<S120>/Product' */
  real_T tauSwitch[3];                 /* '<S1>/tau  Switch' */
  real_T TmpHiddenBufferAtToFileInport1[23];/* 'synthesized block' */
  real_T eta_w[3];                     /* '<S15>/Integrator1' */
  real_T TmpHiddenBufferAtToFileInport_k[3];/* 'synthesized block' */
  real_T K_d3deg;                      /* '<S14>/K_d 3 deg' */
  real_T K_i3deg;                      /* '<S14>/K_i 3 deg' */
  real_T K_p3deg;                      /* '<S14>/K_p 3 deg' */
  real_T Reg_e_Psi_deg;                /* '<S14>/Reg_e_Psi_deg' */
  real_T etaPsideg;                    /* '<S14>/eta Psi deg' */
  real_T Gain1_j[3];                   /* '<S15>/Gain1' */
  real_T xi_w[3];                      /* '<S15>/Integrator2' */
  real_T Gain2[3];                     /* '<S15>/Gain2' */
  real_T Sum4[3];                      /* '<S15>/Sum4' */
  real_T Sum2_a[3];                    /* '<S15>/Sum2' */
  real_T Saturation_cy;                /* '<S24>/Saturation' */
  real_T Sign_d;                       /* '<S24>/Sign' */
  real_T Gain_ju;                      /* '<S24>/Gain' */
  real_T Sum1_he;                      /* '<S24>/Sum1' */
  real_T MathFunction_kv;              /* '<S24>/Math Function' */
  real_T Sum_ez;                       /* '<S24>/Sum' */
  real_T TmpHiddenBufferAtK11Inport1[3];/* 'synthesized block' */
  real_T K4[3];                        /* '<S15>/K4' */
  real_T Row1_i;                       /* '<S21>/Row1' */
  real_T Row2_p;                       /* '<S21>/Row2' */
  real_T Row3_p;                       /* '<S21>/Row3' */
  real_T bias[3];                      /* '<S15>/Integrator3' */
  real_T Row1_g;                       /* '<S22>/Row1' */
  real_T Row2_a;                       /* '<S22>/Row2' */
  real_T Row3_l;                       /* '<S22>/Row3' */
  real_T Sum1_cn[3];                   /* '<S15>/Sum1' */
  real_T Gain6[3];                     /* '<S15>/Gain6' */
  real_T Sum8[3];                      /* '<S15>/Sum8' */
  real_T Gain3[3];                     /* '<S15>/Gain3' */
  real_T K11[3];                       /* '<S15>/K11' */
  real_T K12[3];                       /* '<S15>/K12' */
  real_T K2[3];                        /* '<S15>/K2' */
  real_T K3[3];                        /* '<S15>/K3' */
  real_T x_dot;                        /* '<S20>/Fcn' */
  real_T y_dot;                        /* '<S20>/Fcn1' */
  real_T psi_dot;                      /* '<S20>/Fcn2' */
  real_T Sum3_k[3];                    /* '<S15>/Sum3' */
  real_T psi_WF[3];                    /* '<S15>/Sum5' */
  real_T Sum6[3];                      /* '<S15>/Sum6' */
  real_T invT_b[3];                    /* '<S15>/inv(T_b)' */
  real_T Sum7[3];                      /* '<S15>/Sum7' */
  real_T x2[4];                        /* '<S51>/2x2' */
  real_T Product_e[3];                 /* '<S52>/Product' */
  real_T Add_ov[2];                    /* '<S62>/Add' */
  real_T MathFunction_ew[3];           /* '<S106>/Math Function' */
  real_T Product_au[2];                /* '<S63>/Product' */
  real_T Gain_m[2];                    /* '<S63>/Gain' */
  real_T MathFunction_m[2];            /* '<S104>/Math Function' */
  real_T Product_b2[2];                /* '<S62>/Product' */
  real_T Add1_g[2];                    /* '<S62>/Add1' */
  real_T Product1_ln[2];               /* '<S62>/Product1' */
  real_T Gain_fx[2];                   /* '<S62>/Gain' */
  real_T x2_g[4];                      /* '<S127>/2x2' */
  real_T Product_k[3];                 /* '<S128>/Product' */
  real_T MathFunction_ff[6];           /* '<S186>/Math Function' */
  real_T Product2_f[2];                /* '<S135>/Product2' */
  real_T Product3_a[2];                /* '<S135>/Product3' */
  real_T Subtract_jg[2];               /* '<S135>/Subtract' */
  real_T Product1_gn[2];               /* '<S135>/Product1' */
  real_T dotomega_q[2];                /* '<S135>/dot omega_q' */
  real_T eta_dPsideg;                  /* '<S219>/eta_d Psi deg' */
  real_T QTMIn1FN;                     /* '<S289>/QTM In1 FN' */
  real_T QTMIn2Error;                  /* '<S289>/QTM In2 Error' */
  real_T SITzAI1;                      /* '<S289>/SIT zAI1' */
  real_T BatteryServo;                 /* '<S289>/Battery Servo' */
  real_T SITzAI2;                      /* '<S289>/SIT zAI2' */
  real_T BatteryMain;                  /* '<S289>/Battery Main' */
  real_T SITzAI0;                      /* '<S289>/SIT zAI0' */
  real_T BatteryBowThruster;           /* '<S289>/Battery Bow Thruster' */
  real_T Saturation_e;                 /* '<S299>/Saturation' */
  real_T Saturation1;                  /* '<S299>/Saturation1' */
  real_T Saturation2;                  /* '<S299>/Saturation2' */
  real_T planttau_surge;               /* '<S299>/plant tau_surge' */
  real_T planttau_sway;                /* '<S299>/plant tau_sway' */
  real_T planttau_yaw;                 /* '<S299>/plant tau_yaw' */
  real_T u_1plant;                     /* '<S5>/u_1 plant' */
  real_T u_2plant;                     /* '<S5>/u_2 plant' */
  real_T u_3plant;                     /* '<S5>/u_3 plant' */
  real_T u_4plant;                     /* '<S5>/u_4 plant' */
  real_T u_5plant;                     /* '<S5>/u_5 plant' */
  real_T BTpowerlimitplant;            /* '<S5>/BT power limit plant' */
  real_T VSPspeedplant;                /* '<S5>/VSP speed plant' */
  real_T trig;                         /* '<S5>/trig' */
  real_T MultiportSwitch_pqq;          /* '<S5>/Multiport Switch' */
  real_T trig1;                        /* '<S5>/trig1' */
  real_T MultiportSwitch1_g;           /* '<S5>/Multiport Switch1' */
  real_T Gain_jh;                      /* '<S297>/Gain' */
  real_T Gain_g;                       /* '<S298>/Gain' */
  real_T N_r_g;                        /* '<S310>/-N_r' */
  real_T N_v_k;                        /* '<S310>/-N_v' */
  real_T X_u_h;                        /* '<S310>/-X_u' */
  real_T Y_v_n;                        /* '<S310>/-Y_v' */
  real_T Y_vr_c;                       /* '<S310>/-Y_vr' */
  real_T LinearDampningmatrix_pr[9];   /* '<S310>/Linear Dampning matrix' */
  real_T psi_0;                        /* '<S311>/psi_0' */
  real_T x_0;                          /* '<S311>/x_0' */
  real_T y_0;                          /* '<S311>/y_0' */
  real_T r_0;                          /* '<S312>/r_0' */
  real_T u_0;                          /* '<S312>/u_0' */
  real_T v_0;                          /* '<S312>/v_0' */
  real_T Integrator_e[3];              /* '<S309>/Integrator' */
  real_T Integrator1_o[3];             /* '<S309>/Integrator1' */
  real_T M_11_a;                       /* '<S313>/M_11' */
  real_T M_22_f;                       /* '<S313>/M_22' */
  real_T mx_g_p;                       /* '<S313>/m x_g' */
  real_T M_32_l;                       /* '<S313>/M_32' */
  real_T M_23_j;                       /* '<S313>/M_23' */
  real_T M_33_a;                       /* '<S313>/M_33' */
  real_T M[9];                         /* '<S313>/M' */
  real_T Inverse[9];                   /* '<S313>/Inverse' */
  real_T Product1_ha[3];               /* '<S309>/Product1' */
  real_T R11_d;                        /* '<S314>/R11' */
  real_T R21_e;                        /* '<S314>/R21' */
  real_T R12_a;                        /* '<S314>/R12' */
  real_T R22_g;                        /* '<S314>/R22' */
  real_T Rpsi_a[9];                    /* '<S314>/R(psi)' */
  real_T Product3_j[3];                /* '<S309>/Product3' */
  real_T eta_surge_hil;                /* '<S296>/eta_surge_hil' */
  real_T eta_sway_hil;                 /* '<S296>/eta_sway_hil' */
  real_T eta_yaw_hil;                  /* '<S296>/eta_yaw_hil' */
  real_T etadot_surge_hil;             /* '<S296>/etadot_surge_hil' */
  real_T etadot_sway_hil;              /* '<S296>/etadot_sway_hil' */
  real_T etadot_yaw_hil;               /* '<S296>/etadot_yaw_hil' */
  real_T nu_surge_hil;                 /* '<S296>/nu_surge_hil' */
  real_T nu_sway_hil;                  /* '<S296>/nu_sway_hil' */
  real_T nu_yaw_hil;                   /* '<S296>/nu_yaw_hil' */
  real_T Sum_p[3];                     /* '<S309>/Sum' */
  real_T Product2_bi[3];               /* '<S309>/Product2' */
  real_T BT_D_Gain1;                   /* '<S300>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S300>/BT_D_Gain2' */
  real_T Add_c;                        /* '<S300>/Add' */
  real_T BT_L_Gain1;                   /* '<S300>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S300>/BT_L_Gain2' */
  real_T Neg;                          /* '<S300>/Neg' */
  real_T Sum1_cf;                      /* '<S300>/Sum1' */
  real_T Sum2_b;                       /* '<S300>/Sum2' */
  real_T Switch;                       /* '<S302>/Switch' */
  real_T Switch2;                      /* '<S302>/Switch2' */
  real_T Switch_n;                     /* '<S303>/Switch' */
  real_T Switch2_o;                    /* '<S303>/Switch2' */
  real_T Switch_e;                     /* '<S304>/Switch' */
  real_T Switch2_a;                    /* '<S304>/Switch2' */
  real_T Sign_mc;                      /* '<S301>/Sign' */
  real_T PortVPS_X;                    /* '<S301>/Product1' */
  real_T PortVPS_X_d;                  /* '<S301>/-x' */
  real_T PortVSP_Y;                    /* '<S301>/Product2' */
  real_T PortVSP_Y_p;                  /* '<S301>/-y' */
  real_T xr;                           /* '<S305>/x->r' */
  real_T xtheta;                       /* '<S305>/x->theta' */
  real_T StarboardVSP_X;               /* '<S301>/Product3' */
  real_T StarboardVSP_Y;               /* '<S301>/Product4' */
  real_T xr_j;                         /* '<S306>/x->r' */
  real_T xtheta_h;                     /* '<S306>/x->theta' */
  real_T Gain_e;                       /* '<S307>/Gain' */
  real_T Gain_e1;                      /* '<S308>/Gain' */
  real_T Servo1;                       /* '<S301>/Servo1' */
  real_T Servo2;                       /* '<S301>/Servo2' */
  real_T Servo3;                       /* '<S301>/Servo3' */
  real_T Servo4;                       /* '<S301>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S301>/VPS_Speed_Gain' */
  real_T Sum_ep;                       /* '<S301>/Sum' */
  real_T VSPSPort;                     /* '<S301>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S301>/VSPS Starboard' */
  real_T y_2y_1;                       /* '<S279>/y_2 - y_1' */
  real_T x_2x_1;                       /* '<S279>/x_2 - x_1' */
  real_T TrigonometricFunction;        /* '<S225>/Trigonometric Function' */
  real_T Gain_hk;                      /* '<S230>/Gain' */
  real_T Saturation_d;                 /* '<S228>/Saturation' */
  real_T Sign_h;                       /* '<S228>/Sign' */
  real_T Gain_dt;                      /* '<S228>/Gain' */
  real_T Sum1_hi;                      /* '<S228>/Sum1' */
  real_T MathFunction_lk;              /* '<S228>/Math Function' */
  real_T Sum_j;                        /* '<S228>/Sum' */
  real_T Gain1_o;                      /* '<S229>/Gain1' */
  real_T x_ds2;                        /* '<S226>/( x_d^s )^2' */
  real_T y_ds2;                        /* '<S226>/( y_d^s )^2' */
  real_T x_ds2y_ds2;                   /* '<S226>/( x_d^s )^2 + ( y_d^s )^2' */
  real_T x_dsy_ds2;                    /* '<S226>/x_d^s * y_d^s^2' */
  real_T x_ds2y_ds;                    /* '<S226>/x_d^s^2 * y_d^s' */
  real_T x_dsy_ds2x_ds2y_ds;           /* '<S226>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
  real_T Divide_g;                     /* '<S226>/Divide' */
  real_T x_dsx_ds2;                    /* '<S227>/x_d^s * x_d^s^2' */
  real_T y_dsy_ds2;                    /* '<S227>/y_d^s * y_d^s^2' */
  real_T x_dsx_ds2x_ds3y_ds;           /* '<S227>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
  real_T x_dsy_ds3;                    /* '<S227>/x_d^s * y_d^s^3 ' */
  real_T x_ds3y_ds;                    /* '<S227>/x_d^s^3 * y_d^s' */
  real_T x_dsy_ds3x_ds3y_ds;           /* '<S227>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
  real_T u_b;                          /* '<S227>/+ 2' */
  real_T Product1_j;                   /* '<S227>/Product1' */
  real_T Product2_ft;                  /* '<S227>/Product2' */
  real_T Subtract_e;                   /* '<S227>/Subtract' */
  real_T x_ds2y_ds22;                  /* '<S227>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
  real_T Divide_n;                     /* '<S227>/Divide' */
  real_T q[2];                         /* '<S220>/q' */
  real_T Gain_p;                       /* '<S263>/Gain' */
  real_T Saturation_oo;                /* '<S259>/Saturation' */
  real_T Sign_j;                       /* '<S259>/Sign' */
  real_T Gain_g3;                      /* '<S259>/Gain' */
  real_T Sum1_b;                       /* '<S259>/Sum1' */
  real_T MathFunction_lx;              /* '<S259>/Math Function' */
  real_T Sum_if;                       /* '<S259>/Sum' */
  real_T Gain1_oo;                     /* '<S262>/Gain1' */
  real_T MathFunction_id[4];           /* '<S269>/Math Function' */
  real_T x_2x_1_c;                     /* '<S278>/x_2 - x_1' */
  real_T x_2x_1s;                      /* '<S278>/(x_2 - x_1) * s' */
  real_T x_2x_1sx_1;                   /* '<S278>/(x_2 - x_1) * s + x_1' */
  real_T y_2y_1_e;                     /* '<S278>/y_2 - y_1' */
  real_T y_2y_1s;                      /* '<S278>/(y_2 - y_1) * s' */
  real_T y_2y_1sy_1;                   /* '<S278>/(y_2 - y_1) * s + y_1' */
  real_T qp_d[2];                      /* '<S236>/q - p_d' */
  real_T epsilon[2];                   /* '<S236>/epsilon' */
  real_T MultiportSelector;            /* '<S236>/Multiport Selector' */
  real_T TrigonometricFunction_a;      /* '<S253>/Trigonometric Function' */
  real_T Gain_fe;                      /* '<S265>/Gain' */
  real_T Saturation_e4;                /* '<S260>/Saturation' */
  real_T Sign_a;                       /* '<S260>/Sign' */
  real_T Gain_ih;                      /* '<S260>/Gain' */
  real_T Sum1_d;                       /* '<S260>/Sum1' */
  real_T MathFunction_nj;              /* '<S260>/Math Function' */
  real_T Sum_n4;                       /* '<S260>/Sum' */
  real_T Gain1_os;                     /* '<S264>/Gain1' */
  real_T Subtract_p;                   /* '<S253>/Subtract' */
  real_T Gain_cc;                      /* '<S267>/Gain' */
  real_T Saturation_j;                 /* '<S261>/Saturation' */
  real_T Sign_p;                       /* '<S261>/Sign' */
  real_T Gain_k;                       /* '<S261>/Gain' */
  real_T Sum1_pd;                      /* '<S261>/Sum1' */
  real_T MathFunction_ie;              /* '<S261>/Math Function' */
  real_T Sum_ne;                       /* '<S261>/Sum' */
  real_T Gain1_i;                      /* '<S266>/Gain1' */
  real_T VectorConcatenate_dn[3];      /* '<S231>/Vector Concatenate' */
  real_T MathFunction_ew1;             /* '<S254>/Math Function' */
  real_T MathFunction1;                /* '<S254>/Math Function1' */
  real_T Add_k;                        /* '<S254>/Add' */
  real_T Divide_o;                     /* '<S254>/Divide' */
  real_T MultiportSelector1[2];        /* '<S236>/Multiport Selector1' */
  real_T Product_m2[2];                /* '<S254>/Product' */
  real_T Gain_l[2];                    /* '<S254>/Gain' */
  real_T MatrixConcatenate_oj[6];      /* '<S231>/Matrix Concatenate' */
  real_T MathFunction_p;               /* '<S257>/Math Function' */
  real_T MathFunction1_i;              /* '<S257>/Math Function1' */
  real_T Add_jd;                       /* '<S257>/Add' */
  real_T Divide_g5;                    /* '<S257>/Divide' */
  real_T MathFunction_h2[4];           /* '<S273>/Math Function' */
  real_T Product_ky[2];                /* '<S275>/Product' */
  real_T TmpHiddenBufferAtMathFunctionIn[2];/* 'synthesized block' */
  real_T Product1_e[2];                /* '<S275>/Product1' */
  real_T Subtract1[2];                 /* '<S275>/Subtract1' */
  real_T MultiportSelector2;           /* '<S236>/Multiport Selector2' */
  real_T Product_l2;                   /* '<S257>/Product' */
  real_T Subtract_n;                   /* '<S257>/Subtract' */
  real_T VectorConcatenate1[3];        /* '<S231>/Vector Concatenate1' */
  real_T f_qx;                         /* '<S238>/f_qx' */
  real_T f_qy;                         /* '<S238>/f_qy' */
  real_T TmpHiddenBufferAtProductInport1[2];/* 'synthesized block' */
  real_T Product_dm[2];                /* '<S238>/Product' */
  real_T TrigonometricFunction1;       /* '<S239>/Trigonometric Function1' */
  real_T Gain_n;                       /* '<S239>/Gain' */
  real_T Product1_m4[2];               /* '<S239>/Product1' */
  real_T TrigonometricFunction_b;      /* '<S239>/Trigonometric Function' */
  real_T Product2_cb[2];               /* '<S239>/Product2' */
  real_T MatrixConcatenate_d[4];       /* '<S239>/Matrix Concatenate' */
  real_T Product_d4[4];                /* '<S239>/Product' */
  real_T TrigonometricFunction1_p;     /* '<S240>/Trigonometric Function1' */
  real_T Gain_ba;                      /* '<S240>/Gain' */
  real_T Product1_j0;                  /* '<S240>/Product1' */
  real_T TrigonometricFunction_a2;     /* '<S240>/Trigonometric Function' */
  real_T Product2_e;                   /* '<S240>/Product2' */
  real_T TmpHiddenBufferAtProductInpo_kh[2];/* 'synthesized block' */
  real_T Product_l0[2];                /* '<S240>/Product' */
  real_T TrigonometricFunction_b3;     /* '<S241>/Trigonometric Function' */
  real_T TrigonometricFunction1_l;     /* '<S241>/Trigonometric Function1' */
  real_T Derivative;                   /* '<S224>/Derivative' */
  real_T Product_of[2];                /* '<S241>/Product' */
  real_T epsilon_n2;                   /* '<S242>/epsilon_n^2' */
  real_T Delta2;                       /* '<S242>/Delta^2' */
  real_T Add_j0;                       /* '<S242>/Add' */
  real_T sqrt_m;                       /* '<S242>/sqrt' */
  real_T Divide_k;                     /* '<S242>/Divide' */
  real_T MathFunction_o[2];            /* '<S281>/Math Function' */
  real_T Product_ho;                   /* '<S280>/Product' */
  real_T sqrt_g;                       /* '<S280>/sqrt' */
  real_T Divide_j;                     /* '<S282>/Divide' */
  real_T Product_mk;                   /* '<S242>/Product' */
  real_T MathFunction_pj[2];           /* '<S249>/Math Function' */
  real_T Divide_i[2];                  /* '<S246>/Divide' */
  real_T Subtract_a1[2];               /* '<S234>/Subtract' */
  real_T Product_ct;                   /* '<S246>/Product' */
  real_T Gain_mj;                      /* '<S246>/Gain' */
  real_T Subtract_g;                   /* '<S242>/Subtract' */
  real_T epsilon_n2_a;                 /* '<S243>/epsilon_n^2' */
  real_T Delta2_a;                     /* '<S243>/Delta^2' */
  real_T Add_e;                        /* '<S243>/Add' */
  real_T Product1_c[2];                /* '<S243>/Product1' */
  real_T u2;                           /* '<S243>/^3//2' */
  real_T Divide_m[2];                  /* '<S243>/Divide' */
  real_T Product_jc[2];                /* '<S243>/Product' */
  real_T MathFunction_e0[2];           /* '<S250>/Math Function' */
  real_T Divide_d[2];                  /* '<S247>/Divide' */
  real_T Product_ff[2];                /* '<S247>/Product' */
  real_T Gain_is[2];                   /* '<S247>/Gain' */
  real_T Sum_id[2];                    /* '<S243>/Sum' */
  real_T epsilon_n2_j;                 /* '<S244>/epsilon_n^2' */
  real_T Delta2_b;                     /* '<S244>/Delta^2' */
  real_T Add_bt;                       /* '<S244>/Add' */
  real_T MathFunction_b[2];            /* '<S285>/Math Function' */
  real_T TmpHiddenBufferAtMathFunction_o[2];/* 'synthesized block' */
  real_T Product1_oy;                  /* '<S283>/Product1' */
  real_T p_ds3;                        /* '<S283>/|p_d^s|^3' */
  real_T Divide_p;                     /* '<S283>/Divide' */
  real_T Product_g;                    /* '<S283>/Product' */
  real_T Gain_a;                       /* '<S283>/Gain' */
  real_T MathFunction_ig;              /* '<S244>/Math Function' */
  real_T Divide_o4;                    /* '<S244>/Divide' */
  real_T Product2_l;                   /* '<S244>/Product2' */
  real_T u2_g;                         /* '<S244>/^3//2' */
  real_T Divide1;                      /* '<S244>/Divide1' */
  real_T Product1_p;                   /* '<S244>/Product1' */
  real_T Product3_g;                   /* '<S244>/Product3' */
  real_T Product1_bo;                  /* '<S248>/Product1' */
  real_T MathFunction_gl[2];           /* '<S252>/Math Function' */
  real_T Divide2[2];                   /* '<S248>/Divide2' */
  real_T MathFunction_bi[2];           /* '<S251>/Math Function' */
  real_T Product2_o[2];                /* '<S248>/Product2' */
  real_T MathFunction_lc;              /* '<S248>/Math Function' */
  real_T Divide1_d[2];                 /* '<S248>/Divide1' */
  real_T Subtract1_m[2];               /* '<S248>/Subtract1' */
  real_T Product_bi;                   /* '<S248>/Product' */
  real_T Subtract_nx;                  /* '<S248>/Subtract' */
  real_T Sum_oq;                       /* '<S244>/Sum' */
  real_T epsilon_n2_m;                 /* '<S245>/epsilon_n^2' */
  real_T Delta2_f;                     /* '<S245>/Delta^2' */
  real_T Add_f;                        /* '<S245>/Add' */
  real_T sqrt_c;                       /* '<S245>/sqrt' */
  real_T Divide_h;                     /* '<S245>/Divide' */
  real_T Divide_b;                     /* '<S284>/Divide' */
  real_T Product_gd;                   /* '<S245>/Product' */
  real_T MathFunction_ka;              /* '<S255>/Math Function' */
  real_T MathFunction1_c;              /* '<S255>/Math Function1' */
  real_T Add_hs;                       /* '<S255>/Add' */
  real_T Product1_pa[4];               /* '<S255>/Product1' */
  real_T Product2_j;                   /* '<S255>/Product2' */
  real_T MathFunction3[2];             /* '<S255>/Math Function3' */
  real_T Product3_k[4];                /* '<S255>/Product3' */
  real_T Product4_p[4];                /* '<S255>/Product4' */
  real_T Subtract_b[4];                /* '<S255>/Subtract' */
  real_T MathFunction2;                /* '<S255>/Math Function2' */
  real_T Divide_m4[4];                 /* '<S255>/Divide' */
  real_T Product_nq[4];                /* '<S255>/Product' */
  real_T MathFunction_igu;             /* '<S256>/Math Function' */
  real_T MathFunction1_n;              /* '<S256>/Math Function1' */
  real_T Add_bd;                       /* '<S256>/Add' */
  real_T Product1_fw[4];               /* '<S274>/Product1' */
  real_T MultiportSelector3[2];        /* '<S236>/Multiport Selector3' */
  real_T Product1_m3[2];               /* '<S256>/Product1' */
  real_T Product2_k1[2];               /* '<S256>/Product2' */
  real_T Subtract_js[2];               /* '<S256>/Subtract' */
  real_T MathFunction2_i;              /* '<S256>/Math Function2' */
  real_T Divide_b4[2];                 /* '<S256>/Divide' */
  real_T Product_gz[2];                /* '<S256>/Product' */
  real_T MathFunction_hv;              /* '<S258>/Math Function' */
  real_T MathFunction1_f;              /* '<S258>/Math Function1' */
  real_T Add_cn;                       /* '<S258>/Add' */
  real_T MathFunction_o5[4];           /* '<S272>/Math Function' */
  real_T Product_fm[2];                /* '<S276>/Product' */
  real_T Product1_cv[2];               /* '<S276>/Product1' */
  real_T Product2_cp[2];               /* '<S276>/Product2' */
  real_T u_n[2];                       /* '<S276>/2' */
  real_T Product3_f[2];                /* '<S276>/Product3' */
  real_T Sum_mf[2];                    /* '<S276>/Sum' */
  real_T Gain_il[2];                   /* '<S276>/Gain' */
  real_T MultiportSelector4;           /* '<S236>/Multiport Selector4' */
  real_T Product1_k;                   /* '<S258>/Product1' */
  real_T Product2_h;                   /* '<S258>/Product2' */
  real_T MathFunction3_n;              /* '<S258>/Math Function3' */
  real_T Product4_k;                   /* '<S258>/Product4' */
  real_T Subtract_jo;                  /* '<S258>/Subtract' */
  real_T MathFunction2_e;              /* '<S258>/Math Function2' */
  real_T Divide_m5;                    /* '<S258>/Divide' */
  real_T Product_fa;                   /* '<S258>/Product' */
  real_T Subtract1_g;                  /* '<S258>/Subtract1' */
  real_T S12_e;                        /* '<S271>/S12' */
  real_T S_2psi_ds2[4];                /* '<S271>/S_2(psi_d^s^2)' */
  real_T S12_m;                        /* '<S270>/S12' */
  real_T S_2psi_ds[4];                 /* '<S270>/S_2(psi_d^s)' */
  real_T R11_au;                       /* '<S268>/R11' */
  real_T R21_f;                        /* '<S268>/R21' */
  real_T R12_e;                        /* '<S268>/R12' */
  real_T R22_j;                        /* '<S268>/R22' */
  real_T R_2psi_d[4];                  /* '<S268>/R_2(psi_d)' */
  uint16_T Product_h0;                 /* '<S5>/Product' */
  uint16_T Product1_lw;                /* '<S5>/Product1' */
  uint16_T Gain_nh;                    /* '<S198>/Gain' */
  uint16_T Gain1_ax;                   /* '<S198>/Gain1' */
  uint16_T Sum_nj;                     /* '<S198>/Sum' */
  uint16_T Gain_jc;                    /* '<S199>/Gain' */
  uint16_T Gain1_lk;                   /* '<S199>/Gain1' */
  uint16_T Sum_a;                      /* '<S199>/Sum' */
  uint16_T Gain_m4;                    /* '<S200>/Gain' */
  uint16_T Gain1_ot;                   /* '<S200>/Gain1' */
  uint16_T Sum_h;                      /* '<S200>/Sum' */
  uint16_T Gain_mu;                    /* '<S201>/Gain' */
  uint16_T Gain1_g;                    /* '<S201>/Gain1' */
  uint16_T Sum_cr;                     /* '<S201>/Sum' */
  uint16_T Gain_j1;                    /* '<S202>/Gain' */
  uint16_T Gain1_n;                    /* '<S202>/Gain1' */
  uint16_T Sum_gp;                     /* '<S202>/Sum' */
  uint16_T Gain_hh;                    /* '<S27>/Gain' */
  uint16_T Gain1_i2;                   /* '<S27>/Gain1' */
  uint16_T Sum_i2;                     /* '<S27>/Sum' */
  uint16_T Gain_p4;                    /* '<S28>/Gain' */
  uint16_T Gain1_b;                    /* '<S28>/Gain1' */
  uint16_T Sum_nt;                     /* '<S28>/Sum' */
  uint16_T Gain_lm;                    /* '<S29>/Gain' */
  uint16_T Gain1_gb;                   /* '<S29>/Gain1' */
  uint16_T Sum_hj;                     /* '<S29>/Sum' */
  uint16_T Gain_gj;                    /* '<S30>/Gain' */
  uint16_T Gain1_ll;                   /* '<S30>/Gain1' */
  uint16_T Sum_du;                     /* '<S30>/Sum' */
  uint16_T Gain_m0;                    /* '<S31>/Gain' */
  uint16_T Gain1_d;                    /* '<S31>/Gain1' */
  uint16_T Sum_b;                      /* '<S31>/Sum' */
  uint16_T Gain_fg;                    /* '<S83>/Gain' */
  uint16_T Gain1_aq;                   /* '<S83>/Gain1' */
  uint16_T Sum_b4;                     /* '<S83>/Sum' */
  uint16_T Gain_ay;                    /* '<S84>/Gain' */
  uint16_T Gain1_kd;                   /* '<S84>/Gain1' */
  uint16_T Sum_cb;                     /* '<S84>/Sum' */
  uint16_T Gain_ma;                    /* '<S85>/Gain' */
  uint16_T Gain1_gs;                   /* '<S85>/Gain1' */
  uint16_T Sum_fv;                     /* '<S85>/Sum' */
  uint16_T Gain_ke;                    /* '<S86>/Gain' */
  uint16_T Gain1_e;                    /* '<S86>/Gain1' */
  uint16_T Sum_fx;                     /* '<S86>/Sum' */
  uint16_T Gain_fo;                    /* '<S87>/Gain' */
  uint16_T Gain1_nv;                   /* '<S87>/Gain1' */
  uint16_T Sum_ot;                     /* '<S87>/Sum' */
  uint16_T Gain_cd;                    /* '<S165>/Gain' */
  uint16_T Gain1_fi;                   /* '<S165>/Gain1' */
  uint16_T Sum_dk;                     /* '<S165>/Sum' */
  uint16_T Gain_bf;                    /* '<S166>/Gain' */
  uint16_T Gain1_ea;                   /* '<S166>/Gain1' */
  uint16_T Sum_dg;                     /* '<S166>/Sum' */
  uint16_T Gain_ls;                    /* '<S167>/Gain' */
  uint16_T Gain1_h;                    /* '<S167>/Gain1' */
  uint16_T Sum_be;                     /* '<S167>/Sum' */
  uint16_T Gain_df;                    /* '<S168>/Gain' */
  uint16_T Gain1_kx;                   /* '<S168>/Gain1' */
  uint16_T Sum_jd;                     /* '<S168>/Sum' */
  uint16_T Gain_ga;                    /* '<S169>/Gain' */
  uint16_T Gain1_c;                    /* '<S169>/Gain1' */
  uint16_T Sum_mh;                     /* '<S169>/Sum' */
  uint8_T Compare;                     /* '<S13>/Compare' */
  uint8_T Compare_b;                   /* '<S203>/Compare' */
  uint8_T Compare_a;                   /* '<S205>/Compare' */
  uint8_T Compare_l;                   /* '<S204>/Compare' */
  uint8_T Compare_c;                   /* '<S206>/Compare' */
  uint8_T Compare_o;                   /* '<S208>/Compare' */
  uint8_T Compare_e;                   /* '<S207>/Compare' */
  uint8_T Compare_d;                   /* '<S209>/Compare' */
  uint8_T Compare_h;                   /* '<S211>/Compare' */
  uint8_T Compare_i;                   /* '<S210>/Compare' */
  uint8_T Compare_g;                   /* '<S212>/Compare' */
  uint8_T Compare_ic;                  /* '<S214>/Compare' */
  uint8_T Compare_m;                   /* '<S213>/Compare' */
  uint8_T Compare_cp;                  /* '<S215>/Compare' */
  uint8_T Compare_mo;                  /* '<S217>/Compare' */
  uint8_T Compare_h2;                  /* '<S216>/Compare' */
  uint8_T Compare_gp;                  /* '<S32>/Compare' */
  uint8_T Compare_p;                   /* '<S34>/Compare' */
  uint8_T Compare_j;                   /* '<S33>/Compare' */
  uint8_T Compare_ls;                  /* '<S35>/Compare' */
  uint8_T Compare_i3;                  /* '<S37>/Compare' */
  uint8_T Compare_n;                   /* '<S36>/Compare' */
  uint8_T Compare_l5;                  /* '<S38>/Compare' */
  uint8_T Compare_ps;                  /* '<S40>/Compare' */
  uint8_T Compare_ad;                  /* '<S39>/Compare' */
  uint8_T Compare_no;                  /* '<S41>/Compare' */
  uint8_T Compare_d4;                  /* '<S43>/Compare' */
  uint8_T Compare_k;                   /* '<S42>/Compare' */
  uint8_T Compare_ba;                  /* '<S44>/Compare' */
  uint8_T Compare_mf;                  /* '<S46>/Compare' */
  uint8_T Compare_id;                  /* '<S45>/Compare' */
  uint8_T Compare_ib;                  /* '<S88>/Compare' */
  uint8_T Compare_ng;                  /* '<S90>/Compare' */
  uint8_T Compare_kb;                  /* '<S89>/Compare' */
  uint8_T Compare_o2;                  /* '<S91>/Compare' */
  uint8_T Compare_gy;                  /* '<S93>/Compare' */
  uint8_T Compare_ie;                  /* '<S92>/Compare' */
  uint8_T Compare_kt;                  /* '<S94>/Compare' */
  uint8_T Compare_nx;                  /* '<S96>/Compare' */
  uint8_T Compare_m0;                  /* '<S95>/Compare' */
  uint8_T Compare_idx;                 /* '<S97>/Compare' */
  uint8_T Compare_af;                  /* '<S99>/Compare' */
  uint8_T Compare_f;                   /* '<S98>/Compare' */
  uint8_T Compare_oe;                  /* '<S100>/Compare' */
  uint8_T Compare_en;                  /* '<S102>/Compare' */
  uint8_T Compare_lm;                  /* '<S101>/Compare' */
  uint8_T Compare_mw;                  /* '<S170>/Compare' */
  uint8_T Compare_mk;                  /* '<S172>/Compare' */
  uint8_T Compare_jd;                  /* '<S171>/Compare' */
  uint8_T Compare_ef;                  /* '<S173>/Compare' */
  uint8_T Compare_aw;                  /* '<S175>/Compare' */
  uint8_T Compare_fe;                  /* '<S174>/Compare' */
  uint8_T Compare_i3y;                 /* '<S176>/Compare' */
  uint8_T Compare_pt;                  /* '<S178>/Compare' */
  uint8_T Compare_io;                  /* '<S177>/Compare' */
  uint8_T Compare_lj;                  /* '<S179>/Compare' */
  uint8_T Compare_mz;                  /* '<S181>/Compare' */
  uint8_T Compare_gf;                  /* '<S180>/Compare' */
  uint8_T Compare_h4;                  /* '<S182>/Compare' */
  uint8_T Compare_ce;                  /* '<S184>/Compare' */
  uint8_T Compare_gt;                  /* '<S183>/Compare' */
  uint8_T Compare_oc;                  /* '<S292>/Compare' */
  uint8_T Compare_mj;                  /* '<S293>/Compare' */
  uint8_T Compare_hr;                  /* '<S294>/Compare' */
  uint8_T Compare_e0;                  /* '<S295>/Compare' */
  boolean_T LowerRelop1;               /* '<S302>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S302>/UpperRelop' */
  boolean_T LowerRelop1_p;             /* '<S303>/LowerRelop1' */
  boolean_T UpperRelop_e;              /* '<S303>/UpperRelop' */
  boolean_T LowerRelop1_n;             /* '<S304>/LowerRelop1' */
  boolean_T UpperRelop_j;              /* '<S304>/UpperRelop' */
} BlockIO_CSE1_CV3_1Straight;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Pseudoinverse_X[15];          /* '<S197>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S197>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S197>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S197>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S197>/Pseudoinverse' */
  real_T Product3_DWORK1[6];           /* '<S65>/Product3' */
  real_T Inverse_DWORK3[9];            /* '<S313>/Inverse' */
  real_T Inverse_DWORK4[9];            /* '<S313>/Inverse' */
  real_T Product_DWORK1;               /* '<S246>/Product' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } nu_RWORK;                          /* '<S289>/nu' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK;                  /* '<S224>/Derivative' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<Root>/To File' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK_a;                    /* '<S6>/To File' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK_c;                    /* '<S14>/To File' */

  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<S112>/Scope' */

  struct {
    void *LoggedData;
  } Scope_PWORK_e;                     /* '<S242>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S242>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<S242>/Scope2' */

  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<S242>/Scope3' */

  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  int32_T Inverse_DWORK2[3];           /* '<S313>/Inverse' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S198>/Sum' */
  uint32_T Sum_DWORK1_g;               /* '<S27>/Sum' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S62>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_j;                /* '<S135>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S62>/Integrator1' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_h;               /* '<S135>/Integrator1' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<Root>/To File' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK_l;                    /* '<S6>/To File' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK_e;                    /* '<S14>/To File' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_c;                /* '<S309>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_f;               /* '<S309>/Integrator1' */

  int_T LinearSimulator_MODE;          /* '<S5>/Linear Simulator' */
  int_T Pathfollowing_MODE;            /* '<S2>/Path-following' */
  int_T CSE1_MODE;                     /* '<S5>/CSE1' */
  uint8_T SignalProbe_DWORK1[19];      /* '<Root>/SignalProbe' */
} D_Work_CSE1_CV3_1Straight;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S219>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S219>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S219>/Transfer Fcn2' */
  real_T Integrator_CSTATE[2];         /* '<S62>/Integrator' */
  real_T Integrator_CSTATE_g[2];       /* '<S135>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S62>/Integrator1' */
  real_T Integrator1_CSTATE_g;         /* '<S135>/Integrator1' */
  real_T Integrator_CSTATE_p[3];       /* '<S15>/Integrator' */
  real_T Integrator_CSTATE_c[3];       /* '<S14>/Integrator' */
  real_T Integrator4_CSTATE[3];        /* '<S15>/Integrator4' */
  real_T Integrator_CSTATE_k[3];       /* '<S52>/Integrator' */
  real_T Integrator2_CSTATE[2];        /* '<S62>/Integrator2' */
  real_T zeta_CSTATE[3];               /* '<S9>/zeta' */
  real_T omega_q_CSTATE[2];            /* '<S135>/omega_q' */
  real_T Integrator1_CSTATE_d[3];      /* '<S15>/Integrator1' */
  real_T Integrator2_CSTATE_e[3];      /* '<S15>/Integrator2' */
  real_T Integrator3_CSTATE[3];        /* '<S15>/Integrator3' */
  real_T Integrator_CSTATE_cx[3];      /* '<S309>/Integrator' */
  real_T Integrator1_CSTATE_a[3];      /* '<S309>/Integrator1' */
} ContinuousStates_CSE1_CV3_1Stra;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S219>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S219>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE;          /* '<S219>/Transfer Fcn2' */
  real_T Integrator_CSTATE[2];         /* '<S62>/Integrator' */
  real_T Integrator_CSTATE_g[2];       /* '<S135>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S62>/Integrator1' */
  real_T Integrator1_CSTATE_g;         /* '<S135>/Integrator1' */
  real_T Integrator_CSTATE_p[3];       /* '<S15>/Integrator' */
  real_T Integrator_CSTATE_c[3];       /* '<S14>/Integrator' */
  real_T Integrator4_CSTATE[3];        /* '<S15>/Integrator4' */
  real_T Integrator_CSTATE_k[3];       /* '<S52>/Integrator' */
  real_T Integrator2_CSTATE[2];        /* '<S62>/Integrator2' */
  real_T zeta_CSTATE[3];               /* '<S9>/zeta' */
  real_T omega_q_CSTATE[2];            /* '<S135>/omega_q' */
  real_T Integrator1_CSTATE_d[3];      /* '<S15>/Integrator1' */
  real_T Integrator2_CSTATE_e[3];      /* '<S15>/Integrator2' */
  real_T Integrator3_CSTATE[3];        /* '<S15>/Integrator3' */
  real_T Integrator_CSTATE_cx[3];      /* '<S309>/Integrator' */
  real_T Integrator1_CSTATE_a[3];      /* '<S309>/Integrator1' */
} StateDerivatives_CSE1_CV3_1Stra;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<S219>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S219>/Transfer Fcn1' */
  boolean_T TransferFcn2_CSTATE;       /* '<S219>/Transfer Fcn2' */
  boolean_T Integrator_CSTATE[2];      /* '<S62>/Integrator' */
  boolean_T Integrator_CSTATE_g[2];    /* '<S135>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S62>/Integrator1' */
  boolean_T Integrator1_CSTATE_g;      /* '<S135>/Integrator1' */
  boolean_T Integrator_CSTATE_p[3];    /* '<S15>/Integrator' */
  boolean_T Integrator_CSTATE_c[3];    /* '<S14>/Integrator' */
  boolean_T Integrator4_CSTATE[3];     /* '<S15>/Integrator4' */
  boolean_T Integrator_CSTATE_k[3];    /* '<S52>/Integrator' */
  boolean_T Integrator2_CSTATE[2];     /* '<S62>/Integrator2' */
  boolean_T zeta_CSTATE[3];            /* '<S9>/zeta' */
  boolean_T omega_q_CSTATE[2];         /* '<S135>/omega_q' */
  boolean_T Integrator1_CSTATE_d[3];   /* '<S15>/Integrator1' */
  boolean_T Integrator2_CSTATE_e[3];   /* '<S15>/Integrator2' */
  boolean_T Integrator3_CSTATE[3];     /* '<S15>/Integrator3' */
  boolean_T Integrator_CSTATE_cx[3];   /* '<S309>/Integrator' */
  boolean_T Integrator1_CSTATE_a[3];   /* '<S309>/Integrator1' */
} StateDisabled_CSE1_CV3_1Straigh;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S62>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_o;   /* '<S135>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S62>/Integrator1' */
  ZCSigState Integrator1_Reset_ZCE_m;  /* '<S135>/Integrator1' */
  ZCSigState Integrator_Reset_ZCE_m;   /* '<S14>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_p;   /* '<S309>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE_j;  /* '<S309>/Integrator1' */
} PrevZCSigStates_CSE1_CV3_1Strai;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Computed Parameter: INDEX_ARRAY_FLAT
   * Referenced by blocks:
   * '<S236>/Multiport Selector'
   * '<S236>/Multiport Selector1'
   * '<S236>/Multiport Selector2'
   * '<S236>/Multiport Selector3'
   * '<S236>/Multiport Selector4'
   */
  int32_T pooled1;
} ConstParam_CSE1_CV3_1Straight;

/* Backward compatible GRT Identifiers */
#define rtB                            CSE1_CV3_1Straight_B
#define BlockIO                        BlockIO_CSE1_CV3_1Straight
#define rtX                            CSE1_CV3_1Straight_X
#define ContinuousStates               ContinuousStates_CSE1_CV3_1Stra
#define rtP                            CSE1_CV3_1Straight_P
#define Parameters                     Parameters_CSE1_CV3_1Straight
#define rtDWork                        CSE1_CV3_1Straight_DWork
#define D_Work                         D_Work_CSE1_CV3_1Straight
#define ConstParam                     ConstParam_CSE1_CV3_1Straight
#define rtcP                           CSE1_CV3_1Straight_ConstP
#define rtPrevZCSigState               CSE1_CV3_1Straig_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_CSE1_CV3_1Strai

/* Parameters (auto storage) */
struct Parameters_CSE1_CV3_1Straight_ {
  real_T QTMIn_P1;                     /* Expression: width
                                        * '<S289>/QTM In'
                                        */
  real_T QTMIn_P2;                     /* Expression: dtype
                                        * '<S289>/QTM In'
                                        */
  real_T QTMIn_P3;                     /* Expression: portnum
                                        * '<S289>/QTM In'
                                        */
  real_T QTMIn_P4;                     /* Expression: stime
                                        * '<S289>/QTM In'
                                        */
  real_T QTMIn_P5;                     /* Expression: stype
                                        * '<S289>/QTM In'
                                        */
  real_T QTMIn_P6;                     /* Expression: btype
                                        * '<S289>/QTM In'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S289>/QTM In9 Residual'
                                        */
  real_T ControllerInputSelector_Value;/* Expression: 0
                                        * '<S4>/Controller Input Selector'
                                        */
  real_T QTMIn3_Gain;                  /* Expression: 1
                                        * '<S289>/QTM In3'
                                        */
  real_T mm2mx_Gain;                   /* Expression: 0.001
                                        * '<S289>/mm2m x'
                                        */
  real_T QTMIn4_Gain;                  /* Expression: 1
                                        * '<S289>/QTM In4'
                                        */
  real_T mm2my_Gain;                   /* Expression: 0.001
                                        * '<S289>/mm2m y'
                                        */
  real_T QTMIn6_Gain;                  /* Expression: 1
                                        * '<S289>/QTM In6'
                                        */
  real_T d2ryaw_Gain;                  /* Expression: pi/180
                                        * '<S289>/d2r yaw'
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
                                        * '<S289>/QTM In8'
                                        */
  real_T d2rroll_Gain;                 /* Expression: pi/180
                                        * '<S289>/d2r roll'
                                        */
  real_T QTMIn7_Gain;                  /* Expression: 1
                                        * '<S289>/QTM In7'
                                        */
  real_T d2rpitch_Gain;                /* Expression: pi/180
                                        * '<S289>/d2r pitch'
                                        */
  real_T Constant1_Value[9];           /* Expression: zeros(3)
                                        * '<S289>/Constant1'
                                        */
  real_T QTMIn5_Gain;                  /* Expression: 1
                                        * '<S289>/QTM In5'
                                        */
  real_T mm2mz_Gain;                   /* Expression: 0.001
                                        * '<S289>/mm2m z'
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
  real_T Enableeta_dLPF_Value;         /* Expression: 0
                                        * '<S219>/Enable eta_d LPF'
                                        */
  real_T x_d_Value;                    /* Expression: 0
                                        * '<S286>/x_d'
                                        */
  real_T y_d_Value;                    /* Expression: 0
                                        * '<S286>/y_d'
                                        */
  real_T psi_d_Value;                  /* Expression: 0
                                        * '<S286>/psi_d'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * '<S288>/Gain1'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: A
                                        * '<S219>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: C
                                        * '<S219>/Transfer Fcn'
                                        */
  real_T TransferFcn1_A;               /* Computed Parameter: A
                                        * '<S219>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: C
                                        * '<S219>/Transfer Fcn1'
                                        */
  real_T TransferFcn2_A;               /* Computed Parameter: A
                                        * '<S219>/Transfer Fcn2'
                                        */
  real_T TransferFcn2_C;               /* Computed Parameter: C
                                        * '<S219>/Transfer Fcn2'
                                        */
  real_T eta_dDPN_Gain;                /* Expression: 1
                                        * '<S219>/eta_d DP N'
                                        */
  real_T eta_dDPE_Gain;                /* Expression: 1
                                        * '<S219>/eta_d DP E'
                                        */
  real_T eta_dDPPsi_Gain;              /* Expression: 1
                                        * '<S219>/eta_d DP Psi'
                                        */
  real_T ControlMode_Value;            /* Expression: 0
                                        * '<S1>/Control Mode'
                                        */
  real_T Constant_Value;               /* Expression: const
                                        * '<S13>/Constant'
                                        */
  real_T Resetq_Value;                 /* Expression: 0
                                        * '<S62>/Reset q'
                                        */
  real_T q_x_0_Value;                  /* Expression: 0
                                        * '<S105>/q_x_0'
                                        */
  real_T q_y_0_Value;                  /* Expression: 0
                                        * '<S105>/q_y_0'
                                        */
  real_T Resetq_Value_d;               /* Expression: 0
                                        * '<S135>/Reset q'
                                        */
  real_T q_x_0_Value_n;                /* Expression: 0
                                        * '<S187>/q_x_0'
                                        */
  real_T q_y_0_Value_n;                /* Expression: 0
                                        * '<S187>/q_y_0'
                                        */
  real_T q_xgain_Gain;                 /* Expression: 1
                                        * '<S1>/q_x gain'
                                        */
  real_T q_ygain_Gain;                 /* Expression: 1
                                        * '<S1>/q_y gain'
                                        */
  real_T Resets_Value;                 /* Expression: 0
                                        * '<S62>/Reset s'
                                        */
  real_T s_0_Value;                    /* Expression: 0
                                        * '<S62>/s_0'
                                        */
  real_T Resets_Value_c;               /* Expression: 0
                                        * '<S135>/Reset s'
                                        */
  real_T s_0_Value_c;                  /* Expression: 0
                                        * '<S135>/s_0'
                                        */
  real_T sgain_Gain;                   /* Expression: 1
                                        * '<S1>/s gain'
                                        */
  real_T u_d_Value;                    /* Expression: 0.15
                                        * '<S287>/u_d'
                                        */
  real_T x_1_Value;                    /* Expression: 0
                                        * '<S287>/x_1'
                                        */
  real_T y_1_Value;                    /* Expression: 0
                                        * '<S287>/y_1'
                                        */
  real_T x_2_Value;                    /* Expression: 5.5
                                        * '<S287>/x_2'
                                        */
  real_T y_2_Value;                    /* Expression: 2
                                        * '<S287>/y_2'
                                        */
  real_T EnablePath_Value;             /* Expression: 0
                                        * '<S2>/Enable Path'
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
  real_T u1_Value;                     /* Expression: 0
                                        * '<S11>/u1'
                                        */
  real_T LabVIEWu_1_Gain;              /* Expression: 1
                                        * '<S11>/LabVIEW u_1'
                                        */
  real_T u2_Value;                     /* Expression: 0
                                        * '<S11>/u2'
                                        */
  real_T LabVIEWu_2_Gain;              /* Expression: 1
                                        * '<S11>/LabVIEW u_2'
                                        */
  real_T u3_Value;                     /* Expression: 0
                                        * '<S11>/u3'
                                        */
  real_T LabVIEWu_3_Gain;              /* Expression: 1
                                        * '<S11>/LabVIEW u_3'
                                        */
  real_T u4_Value;                     /* Expression: 0
                                        * '<S11>/u4'
                                        */
  real_T LabVIEWu_4_Gain;              /* Expression: 1
                                        * '<S11>/LabVIEW u_4'
                                        */
  real_T u5_Value;                     /* Expression: 0
                                        * '<S11>/u5'
                                        */
  real_T LabVIEWu_5_Gain;              /* Expression: 1
                                        * '<S11>/LabVIEW u_5'
                                        */
  real_T LabVIEWBTpower_Value;         /* Expression: 0
                                        * '<S11>/LabVIEW  BT power'
                                        */
  real_T LabVIEWVSPspeed_Value;        /* Expression: 0
                                        * '<S11>/LabVIEW VSP speed'
                                        */
  real_T AS_LY_Value;                  /* Expression: 0
                                        * '<S10>/AS_LY'
                                        */
  real_T ScalingLY_Gain;               /* Expression: 1/32767
                                        * '<S10>/ScalingLY'
                                        */
  real_T PS3u_1_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_1'
                                        */
  real_T AS_LX_Value;                  /* Expression: 0
                                        * '<S10>/AS_LX'
                                        */
  real_T ScalingLX_Gain;               /* Expression: 1/32767
                                        * '<S10>/ScalingLX'
                                        */
  real_T PS3u_2_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_2'
                                        */
  real_T AS_RY_Value;                  /* Expression: 0
                                        * '<S10>/AS_RY'
                                        */
  real_T ScalingRY_Gain;               /* Expression: 1/32767
                                        * '<S10>/ScalingRY'
                                        */
  real_T PS3u_3_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_3'
                                        */
  real_T AS_RX_Value;                  /* Expression: 0
                                        * '<S10>/AS_RX'
                                        */
  real_T Scaling_RX_Gain;              /* Expression: 1/32767
                                        * '<S10>/Scaling_RX'
                                        */
  real_T PS3u_4_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_4'
                                        */
  real_T L2_Value;                     /* Expression: 0
                                        * '<S10>/L2'
                                        */
  real_T R2_Value;                     /* Expression: 0
                                        * '<S10>/R2'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_5'
                                        */
  real_T PS3_BT_Power_Value;           /* Expression: 0
                                        * '<S10>/PS3_BT_Power'
                                        */
  real_T PS3_VSP_Speed_Value;          /* Expression: 0
                                        * '<S10>/PS3_VSP_Speed'
                                        */
  real_T T_e11_Value;                  /* Expression: 1
                                        * '<S218>/T_e11'
                                        */
  real_T T_e21_Value;                  /* Expression: 0
                                        * '<S218>/T_e21'
                                        */
  real_T l_y1_Value;                   /* Expression: 0.055
                                        * '<S218>/l_y1'
                                        */
  real_T T_e12_Value;                  /* Expression: 0
                                        * '<S218>/T_e12'
                                        */
  real_T T_e22_Value;                  /* Expression: 1
                                        * '<S218>/T_e22'
                                        */
  real_T l_x1_Value;                   /* Expression: 0.45
                                        * '<S218>/l_x1'
                                        */
  real_T l_x1_Gain;                    /* Expression: -1
                                        * '<S218>/-l_x1'
                                        */
  real_T T_e13_Value;                  /* Expression: 1
                                        * '<S218>/T_e13'
                                        */
  real_T T_e23_Value;                  /* Expression: 0
                                        * '<S218>/T_e23'
                                        */
  real_T l_y2_Value;                   /* Expression: 0.055
                                        * '<S218>/l_y2'
                                        */
  real_T l_y2_Gain;                    /* Expression: -1
                                        * '<S218>/-l_y2'
                                        */
  real_T T_e14_Value;                  /* Expression: 0
                                        * '<S218>/T_e14'
                                        */
  real_T T_e24_Value;                  /* Expression: 1
                                        * '<S218>/T_e24'
                                        */
  real_T l_x2_Value;                   /* Expression: 0.45
                                        * '<S218>/l_x2'
                                        */
  real_T l_x2_Gain;                    /* Expression: -1
                                        * '<S218>/-l_x2'
                                        */
  real_T T_e15_Value;                  /* Expression: 0
                                        * '<S218>/T_e15'
                                        */
  real_T T_e25_Value;                  /* Expression: 1
                                        * '<S218>/T_e25'
                                        */
  real_T l_x3_Value;                   /* Expression: 0.385
                                        * '<S218>/l_x3'
                                        */
  real_T tau_surge_Gain;               /* Expression: 1
                                        * '<S12>/tau_surge'
                                        */
  real_T tau_sway_Gain;                /* Expression: 1
                                        * '<S12>/tau_sway'
                                        */
  real_T tau_yaw_Gain;                 /* Expression: 1
                                        * '<S12>/tau_yaw'
                                        */
  real_T Constant_Value_m;             /* Expression: const
                                        * '<S203>/Constant'
                                        */
  real_T Constant_Value_e;             /* Expression: const
                                        * '<S204>/Constant'
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
                                        * '<S198>/f_1 < 0'
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
                                        * '<S198>/f_1 < 0'
                                        */
  real_T f_10_Value;                   /* Expression: 0
                                        * '<S198>/f_1 = 0'
                                        */
  real_T f_10_XData_n[10];             /* Expression: [0
                                          0.0510
                                          0.1530
                                          0.3080
                                          0.4800
                                          0.6630
                                          0.9110
                                          1.0570
                                          1.2210
                                          1.3740]
                                        * '<S198>/f_1 > 0'
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
                                        * '<S198>/f_1 > 0'
                                        */
  real_T Constant_Value_n;             /* Expression: const
                                        * '<S206>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: const
                                        * '<S207>/Constant'
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
                                        * '<S199>/f_2 < 0'
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
                                        * '<S199>/f_2 < 0'
                                        */
  real_T f_20_Value;                   /* Expression: 0
                                        * '<S199>/f_2 = 0'
                                        */
  real_T f_20_XData_e[10];             /* Expression: [0.000
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
                                        * '<S199>/f_2 > 0'
                                        */
  real_T f_20_YData_c[10];             /* Expression: [0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S199>/f_2 > 0'
                                        */
  real_T Constant_Value_h;             /* Expression: const
                                        * '<S209>/Constant'
                                        */
  real_T Constant_Value_mx;            /* Expression: const
                                        * '<S210>/Constant'
                                        */
  real_T f_30_XData[8];                /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S200>/f_3 < 0'
                                        */
  real_T f_30_YData[8];                /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S200>/f_3 < 0'
                                        */
  real_T f_30_Value;                   /* Expression: 0
                                        * '<S200>/f_3 = 0'
                                        */
  real_T f_30_XData_n[11];             /* Expression: [0.000
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
                                        * '<S200>/f_3 > 0'
                                        */
  real_T f_30_YData_c[11];             /* Expression: [0.0452
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
                                        * '<S200>/f_3 > 0'
                                        */
  real_T Constant_Value_b;             /* Expression: const
                                        * '<S212>/Constant'
                                        */
  real_T Constant_Value_eu;            /* Expression: const
                                        * '<S213>/Constant'
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
                                        * '<S201>/f_4 < 0'
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
                                        * '<S201>/f_4 < 0'
                                        */
  real_T f_40_Value;                   /* Expression: 0
                                        * '<S201>/f_4 = 0'
                                        */
  real_T f_40_XData_a[7];              /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S201>/f_4 > 0'
                                        */
  real_T f_40_YData_o[7];              /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S201>/f_4 > 0'
                                        */
  real_T Constant_Value_f;             /* Expression: const
                                        * '<S215>/Constant'
                                        */
  real_T Constant_Value_c;             /* Expression: const
                                        * '<S216>/Constant'
                                        */
  real_T f_50_XData[3];                /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S202>/f_5 < 0'
                                        */
  real_T f_50_YData[3];                /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S202>/f_5 < 0'
                                        */
  real_T f_50_Value;                   /* Expression: 0
                                        * '<S202>/f_5 = 0'
                                        */
  real_T f_50_XData_g[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S202>/f_5 > 0'
                                        */
  real_T f_50_YData_f[3];              /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S202>/f_5 > 0'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1.0
                                        * '<S12>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1.0
                                        * '<S12>/Saturation'
                                        */
  real_T Joysticku_1_Gain;             /* Expression: 1
                                        * '<S12>/Joystick u_1'
                                        */
  real_T Joysticku_2_Gain;             /* Expression: 1
                                        * '<S12>/Joystick u_2'
                                        */
  real_T Joysticku_3_Gain;             /* Expression: 1
                                        * '<S12>/Joystick u_3'
                                        */
  real_T Joysticku_4_Gain;             /* Expression: 1
                                        * '<S12>/Joystick u_4'
                                        */
  real_T Joysticku_5_Gain;             /* Expression: 1
                                        * '<S12>/Joystick u_5'
                                        */
  real_T T_e11_Value_m;                /* Expression: 1
                                        * '<S47>/T_e11'
                                        */
  real_T T_e21_Value_l;                /* Expression: 0
                                        * '<S47>/T_e21'
                                        */
  real_T l_y1_Value_c;                 /* Expression: 0.055
                                        * '<S47>/l_y1'
                                        */
  real_T T_e12_Value_i;                /* Expression: 0
                                        * '<S47>/T_e12'
                                        */
  real_T T_e22_Value_a;                /* Expression: 1
                                        * '<S47>/T_e22'
                                        */
  real_T l_x1_Value_b;                 /* Expression: 0.45
                                        * '<S47>/l_x1'
                                        */
  real_T l_x1_Gain_g;                  /* Expression: -1
                                        * '<S47>/-l_x1'
                                        */
  real_T T_e13_Value_j;                /* Expression: 1
                                        * '<S47>/T_e13'
                                        */
  real_T T_e23_Value_o;                /* Expression: 0
                                        * '<S47>/T_e23'
                                        */
  real_T l_y2_Value_i;                 /* Expression: 0.055
                                        * '<S47>/l_y2'
                                        */
  real_T l_y2_Gain_a;                  /* Expression: -1
                                        * '<S47>/-l_y2'
                                        */
  real_T T_e14_Value_c;                /* Expression: 0
                                        * '<S47>/T_e14'
                                        */
  real_T T_e24_Value_o;                /* Expression: 1
                                        * '<S47>/T_e24'
                                        */
  real_T l_x2_Value_j;                 /* Expression: 0.45
                                        * '<S47>/l_x2'
                                        */
  real_T l_x2_Gain_l;                  /* Expression: -1
                                        * '<S47>/-l_x2'
                                        */
  real_T T_e15_Value_g;                /* Expression: 0
                                        * '<S47>/T_e15'
                                        */
  real_T T_e25_Value_d;                /* Expression: 1
                                        * '<S47>/T_e25'
                                        */
  real_T l_x3_Value_o;                 /* Expression: 0.385
                                        * '<S47>/l_x3'
                                        */
  real_T Kp_scale_Value;               /* Expression: 1
                                        * '<S14>/Kp_scale'
                                        */
  real_T EnableFilter_Value;           /* Expression: 0
                                        * '<S6>/Enable Filter'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * '<S15>/Integrator'
                                        */
  real_T Saturation_UpperSat_j;        /* Expression: 1e10
                                        * '<S23>/Saturation'
                                        */
  real_T Saturation_LowerSat_o;        /* Expression: -1e10
                                        * '<S23>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * '<S23>/Gain'
                                        */
  real_T Constant_Value_hq;            /* Expression: 2*pi
                                        * '<S23>/Constant'
                                        */
  real_T Saturation_UpperSat_o;        /* Expression: 1e10
                                        * '<S19>/Saturation'
                                        */
  real_T Saturation_LowerSat_h;        /* Expression: -1e10
                                        * '<S19>/Saturation'
                                        */
  real_T Gain_Gain_b;                  /* Expression: pi
                                        * '<S19>/Gain'
                                        */
  real_T Constant_Value_k;             /* Expression: 2*pi
                                        * '<S19>/Constant'
                                        */
  real_T etaN_Gain;                    /* Expression: 1
                                        * '<S14>/eta N'
                                        */
  real_T etaE_Gain;                    /* Expression: 1
                                        * '<S14>/eta E'
                                        */
  real_T etaPsi_Gain;                  /* Expression: 1
                                        * '<S14>/eta Psi'
                                        */
  real_T Reg_e_N_hil_Gain;             /* Expression: 1
                                        * '<S14>/Reg_e_N_hil'
                                        */
  real_T Reg_e_E_hil_Gain;             /* Expression: 1
                                        * '<S14>/Reg_e_E_hil'
                                        */
  real_T Reg_e_Psi_hil_Gain;           /* Expression: 1
                                        * '<S14>/Reg_e_Psi_hil'
                                        */
  real_T Saturation_UpperSat_p;        /* Expression: 1e10
                                        * '<S18>/Saturation'
                                        */
  real_T Saturation_LowerSat_hf;       /* Expression: -1e10
                                        * '<S18>/Saturation'
                                        */
  real_T Gain_Gain_e;                  /* Expression: pi
                                        * '<S18>/Gain'
                                        */
  real_T Constant_Value_i;             /* Expression: 2*pi
                                        * '<S18>/Constant'
                                        */
  real_T Kp_Gain[9];                   /* Expression: Kp
                                        * '<S14>/Kp'
                                        */
  real_T K_p1_Gain;                    /* Expression: 1
                                        * '<S14>/K_p 1'
                                        */
  real_T K_p2_Gain;                    /* Expression: 1
                                        * '<S14>/K_p 2'
                                        */
  real_T K_p3_Gain;                    /* Expression: 1
                                        * '<S14>/K_p 3'
                                        */
  real_T Reset_DP_integrator_Value;    /* Expression: 0
                                        * '<S14>/Reset_DP_integrator'
                                        */
  real_T Integrator_IC_g;              /* Expression: 0
                                        * '<S14>/Integrator'
                                        */
  real_T Ki_Gain[9];                   /* Expression: Ki
                                        * '<S14>/Ki'
                                        */
  real_T Ki_scale_Value;               /* Expression: 1
                                        * '<S14>/Ki_scale'
                                        */
  real_T K_i1_Gain;                    /* Expression: 1
                                        * '<S14>/K_i 1'
                                        */
  real_T K_i2_Gain;                    /* Expression: 1
                                        * '<S14>/K_i 2'
                                        */
  real_T K_i3_Gain;                    /* Expression: 1
                                        * '<S14>/K_i 3'
                                        */
  real_T Integrator4_IC;               /* Expression: 0
                                        * '<S15>/Integrator4'
                                        */
  real_T Kd_Gain[9];                   /* Expression: Kd
                                        * '<S14>/Kd'
                                        */
  real_T Kd_scale_Value;               /* Expression: 1
                                        * '<S14>/Kd_scale'
                                        */
  real_T K_d1_Gain;                    /* Expression: 1
                                        * '<S14>/K_d 1'
                                        */
  real_T K_d2_Gain;                    /* Expression: 1
                                        * '<S14>/K_d 2'
                                        */
  real_T K_d3_Gain;                    /* Expression: 1
                                        * '<S14>/K_d 3'
                                        */
  real_T DPtau_surge_Gain;             /* Expression: 1
                                        * '<S6>/DP tau_surge'
                                        */
  real_T DPtau_sway_Gain;              /* Expression: 1
                                        * '<S6>/DP tau_sway'
                                        */
  real_T DPtau_yaw_Gain;               /* Expression: 1
                                        * '<S6>/DP tau_yaw'
                                        */
  real_T Constant_Value_o;             /* Expression: const
                                        * '<S32>/Constant'
                                        */
  real_T Constant_Value_ed;            /* Expression: const
                                        * '<S33>/Constant'
                                        */
  real_T f_10_XData_o[9];              /* Expression: [-1.324
                                          -1.169
                                          -0.919
                                          -0.703
                                          -0.535
                                          -0.292
                                          -0.165
                                          -0.060
                                          0]
                                        * '<S27>/f_1 < 0'
                                        */
  real_T f_10_YData_f[9];              /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2089]
                                        * '<S27>/f_1 < 0'
                                        */
  real_T f_10_Value_c;                 /* Expression: 0
                                        * '<S27>/f_1 = 0'
                                        */
  real_T f_10_XData_h[10];             /* Expression: [0
                                          0.0510
                                          0.1530
                                          0.3080
                                          0.4800
                                          0.6630
                                          0.9110
                                          1.0570
                                          1.2210
                                          1.3740]
                                        * '<S27>/f_1 > 0'
                                        */
  real_T f_10_YData_l[10];             /* Expression: [0.0500
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000]
                                        * '<S27>/f_1 > 0'
                                        */
  real_T DPu_1_Gain;                   /* Expression: 1
                                        * '<S6>/DP u_1'
                                        */
  real_T Constant_Value_oa;            /* Expression: const
                                        * '<S35>/Constant'
                                        */
  real_T Constant_Value_cs;            /* Expression: const
                                        * '<S36>/Constant'
                                        */
  real_T f_20_XData_c[11];             /* Expression: [-0.766
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
                                        * '<S28>/f_2 < 0'
                                        */
  real_T f_20_YData_cj[11];            /* Expression: [-1.0000
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
                                        * '<S28>/f_2 < 0'
                                        */
  real_T f_20_Value_h;                 /* Expression: 0
                                        * '<S28>/f_2 = 0'
                                        */
  real_T f_20_XData_d[10];             /* Expression: [0.000
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
                                        * '<S28>/f_2 > 0'
                                        */
  real_T f_20_YData_h[10];             /* Expression: [0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S28>/f_2 > 0'
                                        */
  real_T DPu_2_Gain;                   /* Expression: 1
                                        * '<S6>/DP u_2'
                                        */
  real_T Constant_Value_jk;            /* Expression: const
                                        * '<S38>/Constant'
                                        */
  real_T Constant_Value_eq;            /* Expression: const
                                        * '<S39>/Constant'
                                        */
  real_T f_30_XData_h[8];              /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S29>/f_3 < 0'
                                        */
  real_T f_30_YData_o[8];              /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S29>/f_3 < 0'
                                        */
  real_T f_30_Value_a;                 /* Expression: 0
                                        * '<S29>/f_3 = 0'
                                        */
  real_T f_30_XData_c[11];             /* Expression: [0.000
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
                                        * '<S29>/f_3 > 0'
                                        */
  real_T f_30_YData_k[11];             /* Expression: [0.0452
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
                                        * '<S29>/f_3 > 0'
                                        */
  real_T DPu_3_Gain;                   /* Expression: 1
                                        * '<S6>/DP u_3'
                                        */
  real_T Constant_Value_nd;            /* Expression: const
                                        * '<S41>/Constant'
                                        */
  real_T Constant_Value_g;             /* Expression: const
                                        * '<S42>/Constant'
                                        */
  real_T f_40_XData_n[10];             /* Expression: [-1.249
                                          -1.225
                                          -1.094
                                          -0.896
                                          -0.696
                                          -0.502
                                          -0.314
                                          -0.169
                                          -0.042
                                          0.000]
                                        * '<S30>/f_4 < 0'
                                        */
  real_T f_40_YData_d[10];             /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0674]
                                        * '<S30>/f_4 < 0'
                                        */
  real_T f_40_Value_j;                 /* Expression: 0
                                        * '<S30>/f_4 = 0'
                                        */
  real_T f_40_XData_b[7];              /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S30>/f_4 > 0'
                                        */
  real_T f_40_YData_dx[7];             /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S30>/f_4 > 0'
                                        */
  real_T DPu_4_Gain;                   /* Expression: 1
                                        * '<S6>/DP u_4'
                                        */
  real_T Constant_Value_hu;            /* Expression: const
                                        * '<S44>/Constant'
                                        */
  real_T Constant_Value_gz;            /* Expression: const
                                        * '<S45>/Constant'
                                        */
  real_T f_50_XData_b[3];              /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S31>/f_5 < 0'
                                        */
  real_T f_50_YData_i[3];              /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S31>/f_5 < 0'
                                        */
  real_T f_50_Value_d;                 /* Expression: 0
                                        * '<S31>/f_5 = 0'
                                        */
  real_T f_50_XData_gn[3];             /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S31>/f_5 > 0'
                                        */
  real_T f_50_YData_b[3];              /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S31>/f_5 > 0'
                                        */
  real_T DPu_5_Gain;                   /* Expression: 1
                                        * '<S6>/DP u_5'
                                        */
  real_T Saturation_UpperSat_ok;       /* Expression: 1.0
                                        * '<S6>/Saturation'
                                        */
  real_T Saturation_LowerSat_k;        /* Expression: -1.0
                                        * '<S6>/Saturation'
                                        */
  real_T BT_power_limit_Value;         /* Expression: 0.5
                                        * '<S6>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value;             /* Expression: 0.4
                                        * '<S6>/VSP_speeds'
                                        */
  real_T T_e11_Value_d;                /* Expression: 1
                                        * '<S103>/T_e11'
                                        */
  real_T T_e21_Value_c;                /* Expression: 0
                                        * '<S103>/T_e21'
                                        */
  real_T l_y1_Value_b;                 /* Expression: 0.055
                                        * '<S103>/l_y1'
                                        */
  real_T T_e12_Value_c;                /* Expression: 0
                                        * '<S103>/T_e12'
                                        */
  real_T T_e22_Value_e;                /* Expression: 1
                                        * '<S103>/T_e22'
                                        */
  real_T l_x1_Value_e;                 /* Expression: 0.45
                                        * '<S103>/l_x1'
                                        */
  real_T l_x1_Gain_l;                  /* Expression: -1
                                        * '<S103>/-l_x1'
                                        */
  real_T T_e13_Value_b;                /* Expression: 1
                                        * '<S103>/T_e13'
                                        */
  real_T T_e23_Value_c;                /* Expression: 0
                                        * '<S103>/T_e23'
                                        */
  real_T l_y2_Value_h;                 /* Expression: 0.055
                                        * '<S103>/l_y2'
                                        */
  real_T l_y2_Gain_n;                  /* Expression: -1
                                        * '<S103>/-l_y2'
                                        */
  real_T T_e14_Value_p;                /* Expression: 0
                                        * '<S103>/T_e14'
                                        */
  real_T T_e24_Value_k;                /* Expression: 1
                                        * '<S103>/T_e24'
                                        */
  real_T l_x2_Value_c;                 /* Expression: 0.45
                                        * '<S103>/l_x2'
                                        */
  real_T l_x2_Gain_f;                  /* Expression: -1
                                        * '<S103>/-l_x2'
                                        */
  real_T T_e15_Value_n;                /* Expression: 0
                                        * '<S103>/T_e15'
                                        */
  real_T T_e25_Value_b;                /* Expression: 1
                                        * '<S103>/T_e25'
                                        */
  real_T l_x3_Value_a;                 /* Expression: 0.385
                                        * '<S103>/l_x3'
                                        */
  real_T R31_Value;                    /* Expression: 0
                                        * '<S57>/R31'
                                        */
  real_T u_Gain;                       /* Expression: -1
                                        * '<S57>/-1'
                                        */
  real_T R32_Value;                    /* Expression: 0
                                        * '<S57>/R32'
                                        */
  real_T R13_Value;                    /* Expression: 0
                                        * '<S57>/R13'
                                        */
  real_T R23_Value;                    /* Expression: 0
                                        * '<S57>/R23'
                                        */
  real_T R33_Value;                    /* Expression: 1
                                        * '<S57>/R33'
                                        */
  real_T K_i_Surge_Value;              /* Expression: 0
                                        * '<S7>/K_i_Surge'
                                        */
  real_T u_Value;                      /* Expression: 0
                                        * '<S54>/21'
                                        */
  real_T u_Value_m;                    /* Expression: 0
                                        * '<S54>/31'
                                        */
  real_T u_Value_c;                    /* Expression: 0
                                        * '<S54>/12'
                                        */
  real_T K_i_Sway_Value;               /* Expression: 0
                                        * '<S7>/K_i_Sway'
                                        */
  real_T u_Value_d;                    /* Expression: 0
                                        * '<S54>/32'
                                        */
  real_T u_Value_a;                    /* Expression: 0
                                        * '<S54>/13'
                                        */
  real_T u_Value_dx;                   /* Expression: 0
                                        * '<S54>/23'
                                        */
  real_T K_i_Yaw_Value;                /* Expression: 0
                                        * '<S7>/K_i_Yaw'
                                        */
  real_T Integrator_IC_b[3];           /* Expression: [0 0 0]'
                                        * '<S52>/Integrator'
                                        */
  real_T K_d_Surge_Value;              /* Expression: 50
                                        * '<S7>/K_d_Surge'
                                        */
  real_T u_Value_j;                    /* Expression: 0
                                        * '<S53>/21'
                                        */
  real_T u_Value_n;                    /* Expression: 0
                                        * '<S53>/31'
                                        */
  real_T u_Value_h;                    /* Expression: 0
                                        * '<S53>/12'
                                        */
  real_T K_d_Sway_Value;               /* Expression: 30
                                        * '<S7>/K_d_Sway'
                                        */
  real_T u_Value_dk;                   /* Expression: 0
                                        * '<S53>/32'
                                        */
  real_T u_Value_o;                    /* Expression: 0
                                        * '<S53>/13'
                                        */
  real_T u_Value_h4;                   /* Expression: 0
                                        * '<S53>/23'
                                        */
  real_T K_d_Yaw_Value;                /* Expression: 5
                                        * '<S7>/K_d_Yaw'
                                        */
  real_T _Value;                       /* Expression: 1
                                        * '<S50>/1'
                                        */
  real_T kappa_1_Value;                /* Expression: 1
                                        * '<S7>/kappa_1'
                                        */
  real_T _Gain;                        /* Expression: 4
                                        * '<S50>/4'
                                        */
  real_T K_p_Surge_Value;              /* Expression: 2*1.5*2
                                        * '<S7>/K_p_Surge'
                                        */
  real_T u_Value_hi;                   /* Expression: 0
                                        * '<S55>/21'
                                        */
  real_T u_Value_nb;                   /* Expression: 0
                                        * '<S55>/31'
                                        */
  real_T u_Value_e;                    /* Expression: 0
                                        * '<S55>/12'
                                        */
  real_T K_p_Sway_Value;               /* Expression: 2*10*2
                                        * '<S7>/K_p_Sway'
                                        */
  real_T u_Value_e1;                   /* Expression: 0
                                        * '<S55>/32'
                                        */
  real_T u_Value_jo;                   /* Expression: 0
                                        * '<S55>/13'
                                        */
  real_T u_Value_k;                    /* Expression: 0
                                        * '<S55>/23'
                                        */
  real_T K_p_Yaw_Value;                /* Expression: 0.5*3
                                        * '<S7>/K_p_Yaw'
                                        */
  real_T Constant_Value_n4[9];         /* Expression: a
                                        * '<S107>/Constant'
                                        */
  real_T Gain_Gain_o;                  /* Expression: 180/pi
                                        * '<S115>/Gain'
                                        */
  real_T Saturation_UpperSat_jx;       /* Expression: 1e10
                                        * '<S113>/Saturation'
                                        */
  real_T Saturation_LowerSat_c;        /* Expression: -1e10
                                        * '<S113>/Saturation'
                                        */
  real_T Gain_Gain_d;                  /* Expression: 180
                                        * '<S113>/Gain'
                                        */
  real_T Constant_Value_gu;            /* Expression: 2*180
                                        * '<S113>/Constant'
                                        */
  real_T Gain1_Gain_e;                 /* Expression: pi/180
                                        * '<S114>/Gain1'
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
  real_T Gain_Gain_a;                  /* Expression: 180/pi
                                        * '<S118>/Gain'
                                        */
  real_T Saturation_UpperSat_oh;       /* Expression: 1e10
                                        * '<S116>/Saturation'
                                        */
  real_T Saturation_LowerSat_p;        /* Expression: -1e10
                                        * '<S116>/Saturation'
                                        */
  real_T Gain_Gain_k;                  /* Expression: 180
                                        * '<S116>/Gain'
                                        */
  real_T Constant_Value_a;             /* Expression: 2*180
                                        * '<S116>/Constant'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: pi/180
                                        * '<S117>/Gain1'
                                        */
  real_T _2x1_Value[2];                /* Expression: [0;0]
                                        * '<S76>/0_2x1'
                                        */
  real_T X_u_Value;                    /* Expression: -0.59739
                                        * '<S80>/X_u'
                                        */
  real_T X_u_Gain;                     /* Expression: -1
                                        * '<S80>/-X_u'
                                        */
  real_T D_L_21_Value;                 /* Expression: 0
                                        * '<S80>/D_L_21'
                                        */
  real_T D_L_31_Value;                 /* Expression: 0
                                        * '<S80>/D_L_31'
                                        */
  real_T D_L_12_Value;                 /* Expression: 0
                                        * '<S80>/D_L_12'
                                        */
  real_T Y_v_Value;                    /* Expression: -3.50625
                                        * '<S80>/Y_v'
                                        */
  real_T Y_v_Gain;                     /* Expression: -1
                                        * '<S80>/-Y_v'
                                        */
  real_T N_v_Value;                    /* Expression: 0.18140
                                        * '<S80>/N_v'
                                        */
  real_T N_v_Gain;                     /* Expression: -1
                                        * '<S80>/-N_v'
                                        */
  real_T D_L_13_Value;                 /* Expression: 0
                                        * '<S80>/D_L_13'
                                        */
  real_T Y_r_Value;                    /* Expression: -7.250
                                        * '<S80>/Y_r'
                                        */
  real_T Y_vr_Gain;                    /* Expression: -1
                                        * '<S80>/-Y_vr'
                                        */
  real_T N_r_Value;                    /* Expression: -1.900
                                        * '<S80>/N_r'
                                        */
  real_T N_r_Gain;                     /* Expression: -1
                                        * '<S80>/-N_r'
                                        */
  real_T m_Value;                      /* Expression: 17.6
                                        * '<S56>/m'
                                        */
  real_T X_udot_Value;                 /* Expression: -2.0
                                        * '<S56>/X_udot'
                                        */
  real_T M_21_Value;                   /* Expression: 0
                                        * '<S56>/M_21'
                                        */
  real_T M_31_Value;                   /* Expression: 0
                                        * '<S56>/M_31'
                                        */
  real_T M_12_Value;                   /* Expression: 0
                                        * '<S56>/M_12'
                                        */
  real_T Y_vdot_Value;                 /* Expression: -10.0
                                        * '<S56>/Y_vdot'
                                        */
  real_T x_g_Value;                    /* Expression: 0.03
                                        * '<S56>/x_g'
                                        */
  real_T N_vdot_Value;                 /* Expression: -0.0
                                        * '<S56>/N_vdot'
                                        */
  real_T M_13_Value;                   /* Expression: 0
                                        * '<S56>/M_13'
                                        */
  real_T Y_rdot_Value;                 /* Expression: 0.0
                                        * '<S56>/Y_rdot'
                                        */
  real_T I_z_Value;                    /* Expression: 1.760
                                        * '<S56>/I_z'
                                        */
  real_T N_rdot_Value;                 /* Expression: -1.0
                                        * '<S56>/N_rdot'
                                        */
  real_T Constant_Value_f1[9];         /* Expression: a
                                        * '<S110>/Constant'
                                        */
  real_T S11_Value;                    /* Expression: 0
                                        * '<S59>/S11'
                                        */
  real_T R31_Value_h;                  /* Expression: 0
                                        * '<S59>/R31'
                                        */
  real_T S12_Gain;                     /* Expression: 1
                                        * '<S59>/S12'
                                        */
  real_T S22_Value;                    /* Expression: 0
                                        * '<S59>/S22'
                                        */
  real_T S32_Value;                    /* Expression: 0
                                        * '<S59>/S32'
                                        */
  real_T S13_Value;                    /* Expression: 0
                                        * '<S59>/S13'
                                        */
  real_T S23_Value;                    /* Expression: 0
                                        * '<S59>/S23'
                                        */
  real_T S33_Value;                    /* Expression: 1
                                        * '<S59>/S33'
                                        */
  real_T _2x1_Value_c[2];              /* Expression: [0;0]
                                        * '<S79>/0_2x1'
                                        */
  real_T Constant_Value_p[9];          /* Expression: a
                                        * '<S108>/Constant'
                                        */
  real_T _2x2_Value[4];                /* Expression: [0 0; 0 0]
                                        * '<S77>/0_2x2'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * '<S62>/Integrator2'
                                        */
  real_T Constant_Value_fj[9];         /* Expression: a
                                        * '<S109>/Constant'
                                        */
  real_T _2x1_Value_o[2];              /* Expression: [0;0]
                                        * '<S78>/0_2x1'
                                        */
  real_T Constant_Value_px;            /* Expression: const
                                        * '<S88>/Constant'
                                        */
  real_T Constant_Value_hh;            /* Expression: const
                                        * '<S89>/Constant'
                                        */
  real_T f_10_XData_d[9];              /* Expression: [-1.324
                                          -1.169
                                          -0.919
                                          -0.703
                                          -0.535
                                          -0.292
                                          -0.165
                                          -0.060
                                          0]
                                        * '<S83>/f_1 < 0'
                                        */
  real_T f_10_YData_d[9];              /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2089]
                                        * '<S83>/f_1 < 0'
                                        */
  real_T f_10_Value_h;                 /* Expression: 0
                                        * '<S83>/f_1 = 0'
                                        */
  real_T f_10_XData_hd[10];            /* Expression: [0
                                          0.0510
                                          0.1530
                                          0.3080
                                          0.4800
                                          0.6630
                                          0.9110
                                          1.0570
                                          1.2210
                                          1.3740]
                                        * '<S83>/f_1 > 0'
                                        */
  real_T f_10_YData_i[10];             /* Expression: [0.0500
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000]
                                        * '<S83>/f_1 > 0'
                                        */
  real_T Constant_Value_ee;            /* Expression: const
                                        * '<S91>/Constant'
                                        */
  real_T Constant_Value_l;             /* Expression: const
                                        * '<S92>/Constant'
                                        */
  real_T f_20_XData_f[11];             /* Expression: [-0.766
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
                                        * '<S84>/f_2 < 0'
                                        */
  real_T f_20_YData_k[11];             /* Expression: [-1.0000
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
                                        * '<S84>/f_2 < 0'
                                        */
  real_T f_20_Value_g;                 /* Expression: 0
                                        * '<S84>/f_2 = 0'
                                        */
  real_T f_20_XData_h[10];             /* Expression: [0.000
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
                                        * '<S84>/f_2 > 0'
                                        */
  real_T f_20_YData_j[10];             /* Expression: [0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S84>/f_2 > 0'
                                        */
  real_T Constant_Value_bu;            /* Expression: const
                                        * '<S94>/Constant'
                                        */
  real_T Constant_Value_op;            /* Expression: const
                                        * '<S95>/Constant'
                                        */
  real_T f_30_XData_f[8];              /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S85>/f_3 < 0'
                                        */
  real_T f_30_YData_e[8];              /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S85>/f_3 < 0'
                                        */
  real_T f_30_Value_c;                 /* Expression: 0
                                        * '<S85>/f_3 = 0'
                                        */
  real_T f_30_XData_b[11];             /* Expression: [0.000
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
                                        * '<S85>/f_3 > 0'
                                        */
  real_T f_30_YData_kz[11];            /* Expression: [0.0452
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
                                        * '<S85>/f_3 > 0'
                                        */
  real_T Constant_Value_fv;            /* Expression: const
                                        * '<S97>/Constant'
                                        */
  real_T Constant_Value_ju;            /* Expression: const
                                        * '<S98>/Constant'
                                        */
  real_T f_40_XData_nx[10];            /* Expression: [-1.249
                                          -1.225
                                          -1.094
                                          -0.896
                                          -0.696
                                          -0.502
                                          -0.314
                                          -0.169
                                          -0.042
                                          0.000]
                                        * '<S86>/f_4 < 0'
                                        */
  real_T f_40_YData_d2[10];            /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0674]
                                        * '<S86>/f_4 < 0'
                                        */
  real_T f_40_Value_a;                 /* Expression: 0
                                        * '<S86>/f_4 = 0'
                                        */
  real_T f_40_XData_ne[7];             /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S86>/f_4 > 0'
                                        */
  real_T f_40_YData_de[7];             /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S86>/f_4 > 0'
                                        */
  real_T Constant_Value_mf;            /* Expression: const
                                        * '<S100>/Constant'
                                        */
  real_T Constant_Value_edn;           /* Expression: const
                                        * '<S101>/Constant'
                                        */
  real_T f_50_XData_o[3];              /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S87>/f_5 < 0'
                                        */
  real_T f_50_YData_a[3];              /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S87>/f_5 < 0'
                                        */
  real_T f_50_Value_f;                 /* Expression: 0
                                        * '<S87>/f_5 = 0'
                                        */
  real_T f_50_XData_f[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S87>/f_5 > 0'
                                        */
  real_T f_50_YData_fx[3];             /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S87>/f_5 > 0'
                                        */
  real_T BT_power_limit_Value_c;       /* Expression: 0.5
                                        * '<S7>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value_m;           /* Expression: 0.4
                                        * '<S7>/VSP_speeds'
                                        */
  real_T T_e11_Value_o;                /* Expression: 1
                                        * '<S185>/T_e11'
                                        */
  real_T T_e21_Value_k;                /* Expression: 0
                                        * '<S185>/T_e21'
                                        */
  real_T l_y1_Value_j;                 /* Expression: 0.055
                                        * '<S185>/l_y1'
                                        */
  real_T T_e12_Value_a;                /* Expression: 0
                                        * '<S185>/T_e12'
                                        */
  real_T T_e22_Value_m;                /* Expression: 1
                                        * '<S185>/T_e22'
                                        */
  real_T l_x1_Value_ex;                /* Expression: 0.45
                                        * '<S185>/l_x1'
                                        */
  real_T l_x1_Gain_d;                  /* Expression: -1
                                        * '<S185>/-l_x1'
                                        */
  real_T T_e13_Value_o;                /* Expression: 1
                                        * '<S185>/T_e13'
                                        */
  real_T T_e23_Value_i;                /* Expression: 0
                                        * '<S185>/T_e23'
                                        */
  real_T l_y2_Value_l;                 /* Expression: 0.055
                                        * '<S185>/l_y2'
                                        */
  real_T l_y2_Gain_ag;                 /* Expression: -1
                                        * '<S185>/-l_y2'
                                        */
  real_T T_e14_Value_e;                /* Expression: 0
                                        * '<S185>/T_e14'
                                        */
  real_T T_e24_Value_d;                /* Expression: 1
                                        * '<S185>/T_e24'
                                        */
  real_T l_x2_Value_f;                 /* Expression: 0.45
                                        * '<S185>/l_x2'
                                        */
  real_T l_x2_Gain_i;                  /* Expression: -1
                                        * '<S185>/-l_x2'
                                        */
  real_T T_e15_Value_c;                /* Expression: 0
                                        * '<S185>/T_e15'
                                        */
  real_T T_e25_Value_bl;               /* Expression: 1
                                        * '<S185>/T_e25'
                                        */
  real_T l_x3_Value_d;                 /* Expression: 0.385
                                        * '<S185>/l_x3'
                                        */
  real_T R31_Value_e;                  /* Expression: 0
                                        * '<S132>/R31'
                                        */
  real_T R32_Value_a;                  /* Expression: 0
                                        * '<S132>/R32'
                                        */
  real_T R13_Value_h;                  /* Expression: 0
                                        * '<S132>/R13'
                                        */
  real_T R23_Value_a;                  /* Expression: 0
                                        * '<S132>/R23'
                                        */
  real_T R33_Value_e;                  /* Expression: 1
                                        * '<S132>/R33'
                                        */
  real_T K_p_Surge_Value_c;            /* Expression: 0.5*3
                                        * '<S9>/K_p_Surge'
                                        */
  real_T u_Value_ea;                   /* Expression: 0
                                        * '<S131>/21'
                                        */
  real_T u_Value_am;                   /* Expression: 0
                                        * '<S131>/31'
                                        */
  real_T u_Value_dp;                   /* Expression: 0
                                        * '<S131>/12'
                                        */
  real_T K_p_Sway_Value_o;             /* Expression: .2*4
                                        * '<S9>/K_p_Sway'
                                        */
  real_T u_Value_i;                    /* Expression: 0
                                        * '<S131>/32'
                                        */
  real_T u_Value_md;                   /* Expression: 0
                                        * '<S131>/13'
                                        */
  real_T u_Value_ib;                   /* Expression: 0
                                        * '<S131>/23'
                                        */
  real_T K_p_Yaw_Value_j;              /* Expression: 1.5*3
                                        * '<S9>/K_p_Yaw'
                                        */
  real_T Gain_Gain_j;                  /* Expression: 180/pi
                                        * '<S159>/Gain'
                                        */
  real_T Saturation_UpperSat_g;        /* Expression: 1e10
                                        * '<S157>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: -1e10
                                        * '<S157>/Saturation'
                                        */
  real_T Gain_Gain_kr;                 /* Expression: 180
                                        * '<S157>/Gain'
                                        */
  real_T Constant_Value_pw;            /* Expression: 2*180
                                        * '<S157>/Constant'
                                        */
  real_T Gain1_Gain_j;                 /* Expression: pi/180
                                        * '<S158>/Gain1'
                                        */
  real_T Gain_Gain_ou;                 /* Expression: 180/pi
                                        * '<S162>/Gain'
                                        */
  real_T Saturation_UpperSat_pu;       /* Expression: 1e10
                                        * '<S160>/Saturation'
                                        */
  real_T Saturation_LowerSat_hs;       /* Expression: -1e10
                                        * '<S160>/Saturation'
                                        */
  real_T Gain_Gain_az;                 /* Expression: 180
                                        * '<S160>/Gain'
                                        */
  real_T Constant_Value_b4;            /* Expression: 2*180
                                        * '<S160>/Constant'
                                        */
  real_T Gain1_Gain_i;                 /* Expression: pi/180
                                        * '<S161>/Gain1'
                                        */
  real_T K_i_Surge_Value_f;            /* Expression: 0
                                        * '<S9>/K_i_Surge'
                                        */
  real_T u_Value_ce;                   /* Expression: 0
                                        * '<S130>/21'
                                        */
  real_T u_Value_jf;                   /* Expression: 0
                                        * '<S130>/31'
                                        */
  real_T u_Value_g;                    /* Expression: 0
                                        * '<S130>/12'
                                        */
  real_T K_i_Sway_Value_m;             /* Expression: 0
                                        * '<S9>/K_i_Sway'
                                        */
  real_T u_Value_aa;                   /* Expression: 0
                                        * '<S130>/32'
                                        */
  real_T u_Value_mu;                   /* Expression: 0
                                        * '<S130>/13'
                                        */
  real_T u_Value_b;                    /* Expression: 0
                                        * '<S130>/23'
                                        */
  real_T K_i_Yaw_Value_c;              /* Expression: 0
                                        * '<S9>/K_i_Yaw'
                                        */
  real_T zeta_IC;                      /* Expression: 0
                                        * '<S9>/zeta'
                                        */
  real_T K_d_Surge_Value_o;            /* Expression: 8*2/4
                                        * '<S9>/K_d_Surge'
                                        */
  real_T u_Value_bk;                   /* Expression: 0
                                        * '<S129>/21'
                                        */
  real_T u_Value_bh;                   /* Expression: 0
                                        * '<S129>/31'
                                        */
  real_T u_Value_p;                    /* Expression: 0
                                        * '<S129>/12'
                                        */
  real_T K_d_Sway_Value_l;             /* Expression: 25*2
                                        * '<S9>/K_d_Sway'
                                        */
  real_T u_Value_g0;                   /* Expression: 0
                                        * '<S129>/32'
                                        */
  real_T u_Value_ew;                   /* Expression: 0
                                        * '<S129>/13'
                                        */
  real_T u_Value_bc;                   /* Expression: 0
                                        * '<S129>/23'
                                        */
  real_T K_d_Yaw_Value_f;              /* Expression: 8
                                        * '<S9>/K_d_Yaw'
                                        */
  real_T _2x1_Value_n[2];              /* Expression: [0;0]
                                        * '<S145>/0_2x1'
                                        */
  real_T X_u_Value_c;                  /* Expression: -0.59739
                                        * '<S154>/X_u'
                                        */
  real_T X_u_Gain_p;                   /* Expression: -1
                                        * '<S154>/-X_u'
                                        */
  real_T D_L_21_Value_c;               /* Expression: 0
                                        * '<S154>/D_L_21'
                                        */
  real_T D_L_31_Value_n;               /* Expression: 0
                                        * '<S154>/D_L_31'
                                        */
  real_T D_L_12_Value_i;               /* Expression: 0
                                        * '<S154>/D_L_12'
                                        */
  real_T Y_v_Value_k;                  /* Expression: -3.50625
                                        * '<S154>/Y_v'
                                        */
  real_T Y_v_Gain_d;                   /* Expression: -1
                                        * '<S154>/-Y_v'
                                        */
  real_T N_v_Value_g;                  /* Expression: 0.18140
                                        * '<S154>/N_v'
                                        */
  real_T N_v_Gain_a;                   /* Expression: -1
                                        * '<S154>/-N_v'
                                        */
  real_T D_L_13_Value_p;               /* Expression: 0
                                        * '<S154>/D_L_13'
                                        */
  real_T Y_r_Value_l;                  /* Expression: -7.250
                                        * '<S154>/Y_r'
                                        */
  real_T Y_vr_Gain_b;                  /* Expression: -1
                                        * '<S154>/-Y_vr'
                                        */
  real_T N_r_Value_o;                  /* Expression: -1.900
                                        * '<S154>/N_r'
                                        */
  real_T N_r_Gain_j;                   /* Expression: -1
                                        * '<S154>/-N_r'
                                        */
  real_T m_Value_k;                    /* Expression: 17.6
                                        * '<S153>/m'
                                        */
  real_T X_udot_Value_a;               /* Expression: -2.0
                                        * '<S153>/X_udot'
                                        */
  real_T M_21_Value_n;                 /* Expression: 0
                                        * '<S153>/M_21'
                                        */
  real_T M_31_Value_h;                 /* Expression: 0
                                        * '<S153>/M_31'
                                        */
  real_T M_12_Value_j;                 /* Expression: 0
                                        * '<S153>/M_12'
                                        */
  real_T Y_vdot_Value_j;               /* Expression: -10.0
                                        * '<S153>/Y_vdot'
                                        */
  real_T x_g_Value_f;                  /* Expression: 0.03
                                        * '<S153>/x_g'
                                        */
  real_T N_vdot_Value_g;               /* Expression: -0.0
                                        * '<S153>/N_vdot'
                                        */
  real_T M_13_Value_o;                 /* Expression: 0
                                        * '<S153>/M_13'
                                        */
  real_T Y_rdot_Value_f;               /* Expression: 0.0
                                        * '<S153>/Y_rdot'
                                        */
  real_T I_z_Value_o;                  /* Expression: 1.760
                                        * '<S153>/I_z'
                                        */
  real_T N_rdot_Value_a;               /* Expression: -1.0
                                        * '<S153>/N_rdot'
                                        */
  real_T _2x2_Value_m[4];              /* Expression: [0 0; 0 0]
                                        * '<S146>/0_2x2'
                                        */
  real_T omega_q_IC;                   /* Expression: 0
                                        * '<S135>/omega_q'
                                        */
  real_T _2x1_Value_p[2];              /* Expression: [0;0]
                                        * '<S147>/0_2x1'
                                        */
  real_T _2x1_Value_j[2];              /* Expression: [0;0]
                                        * '<S148>/0_2x1'
                                        */
  real_T S11_Value_n;                  /* Expression: 0
                                        * '<S149>/S11'
                                        */
  real_T R31_Value_j;                  /* Expression: 0
                                        * '<S149>/R31'
                                        */
  real_T S12_Gain_m;                   /* Expression: 1
                                        * '<S149>/S12'
                                        */
  real_T S22_Value_l;                  /* Expression: 0
                                        * '<S149>/S22'
                                        */
  real_T S32_Value_m;                  /* Expression: 0
                                        * '<S149>/S32'
                                        */
  real_T S13_Value_p;                  /* Expression: 0
                                        * '<S149>/S13'
                                        */
  real_T S23_Value_p;                  /* Expression: 0
                                        * '<S149>/S23'
                                        */
  real_T S33_Value_l;                  /* Expression: 1
                                        * '<S149>/S33'
                                        */
  real_T Gain_Gain_g;                  /* Expression: 1
                                        * '<S150>/Gain'
                                        */
  real_T Constant_Value_jo;            /* Expression: const
                                        * '<S170>/Constant'
                                        */
  real_T Constant_Value_bb;            /* Expression: const
                                        * '<S171>/Constant'
                                        */
  real_T f_10_XData_e[9];              /* Expression: [-1.324
                                          -1.169
                                          -0.919
                                          -0.703
                                          -0.535
                                          -0.292
                                          -0.165
                                          -0.060
                                          0]
                                        * '<S165>/f_1 < 0'
                                        */
  real_T f_10_YData_k[9];              /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2089]
                                        * '<S165>/f_1 < 0'
                                        */
  real_T f_10_Value_a;                 /* Expression: 0
                                        * '<S165>/f_1 = 0'
                                        */
  real_T f_10_XData_o2[10];            /* Expression: [0
                                          0.0510
                                          0.1530
                                          0.3080
                                          0.4800
                                          0.6630
                                          0.9110
                                          1.0570
                                          1.2210
                                          1.3740]
                                        * '<S165>/f_1 > 0'
                                        */
  real_T f_10_YData_d0[10];            /* Expression: [0.0500
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000]
                                        * '<S165>/f_1 > 0'
                                        */
  real_T Constant_Value_mh;            /* Expression: const
                                        * '<S173>/Constant'
                                        */
  real_T Constant_Value_hm;            /* Expression: const
                                        * '<S174>/Constant'
                                        */
  real_T f_20_XData_k[11];             /* Expression: [-0.766
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
                                        * '<S166>/f_2 < 0'
                                        */
  real_T f_20_YData_b[11];             /* Expression: [-1.0000
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
                                        * '<S166>/f_2 < 0'
                                        */
  real_T f_20_Value_n;                 /* Expression: 0
                                        * '<S166>/f_2 = 0'
                                        */
  real_T f_20_XData_do[10];            /* Expression: [0.000
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
                                        * '<S166>/f_2 > 0'
                                        */
  real_T f_20_YData_f[10];             /* Expression: [0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S166>/f_2 > 0'
                                        */
  real_T Constant_Value_aa;            /* Expression: const
                                        * '<S176>/Constant'
                                        */
  real_T Constant_Value_hb;            /* Expression: const
                                        * '<S177>/Constant'
                                        */
  real_T f_30_XData_hd[8];             /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S167>/f_3 < 0'
                                        */
  real_T f_30_YData_g[8];              /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S167>/f_3 < 0'
                                        */
  real_T f_30_Value_e;                 /* Expression: 0
                                        * '<S167>/f_3 = 0'
                                        */
  real_T f_30_XData_j[11];             /* Expression: [0.000
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
                                        * '<S167>/f_3 > 0'
                                        */
  real_T f_30_YData_f[11];             /* Expression: [0.0452
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
                                        * '<S167>/f_3 > 0'
                                        */
  real_T Constant_Value_iv;            /* Expression: const
                                        * '<S179>/Constant'
                                        */
  real_T Constant_Value_o5;            /* Expression: const
                                        * '<S180>/Constant'
                                        */
  real_T f_40_XData_l[10];             /* Expression: [-1.249
                                          -1.225
                                          -1.094
                                          -0.896
                                          -0.696
                                          -0.502
                                          -0.314
                                          -0.169
                                          -0.042
                                          0.000]
                                        * '<S168>/f_4 < 0'
                                        */
  real_T f_40_YData_g[10];             /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0674]
                                        * '<S168>/f_4 < 0'
                                        */
  real_T f_40_Value_c;                 /* Expression: 0
                                        * '<S168>/f_4 = 0'
                                        */
  real_T f_40_XData_b2[7];             /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S168>/f_4 > 0'
                                        */
  real_T f_40_YData_n[7];              /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S168>/f_4 > 0'
                                        */
  real_T Constant_Value_h0;            /* Expression: const
                                        * '<S182>/Constant'
                                        */
  real_T Constant_Value_gq;            /* Expression: const
                                        * '<S183>/Constant'
                                        */
  real_T f_50_XData_a[3];              /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S169>/f_5 < 0'
                                        */
  real_T f_50_YData_o[3];              /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S169>/f_5 < 0'
                                        */
  real_T f_50_Value_h;                 /* Expression: 0
                                        * '<S169>/f_5 = 0'
                                        */
  real_T f_50_XData_l[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S169>/f_5 > 0'
                                        */
  real_T f_50_YData_n[3];              /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S169>/f_5 > 0'
                                        */
  real_T BT_power_limit_Value_f;       /* Expression: 0.5
                                        * '<S9>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value_d;           /* Expression: 0.4
                                        * '<S9>/VSP_speeds'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 1.0
                                        * '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat_n;        /* Expression: -1.0
                                        * '<S1>/Saturation'
                                        */
  real_T T_e11_Value_mi;               /* Expression: 1
                                        * '<S194>/T_e11'
                                        */
  real_T T_e21_Value_kz;               /* Expression: 0
                                        * '<S194>/T_e21'
                                        */
  real_T l_y1_Value_cw;                /* Expression: 0.055
                                        * '<S194>/l_y1'
                                        */
  real_T T_e12_Value_k;                /* Expression: 0
                                        * '<S194>/T_e12'
                                        */
  real_T T_e22_Value_i;                /* Expression: 1
                                        * '<S194>/T_e22'
                                        */
  real_T l_x1_Value_k;                 /* Expression: 0.45
                                        * '<S194>/l_x1'
                                        */
  real_T l_x1_Gain_dp;                 /* Expression: -1
                                        * '<S194>/-l_x1'
                                        */
  real_T T_e13_Value_n;                /* Expression: 1
                                        * '<S194>/T_e13'
                                        */
  real_T T_e23_Value_p;                /* Expression: 0
                                        * '<S194>/T_e23'
                                        */
  real_T l_y2_Value_o;                 /* Expression: 0.055
                                        * '<S194>/l_y2'
                                        */
  real_T l_y2_Gain_d;                  /* Expression: -1
                                        * '<S194>/-l_y2'
                                        */
  real_T T_e14_Value_b;                /* Expression: 0
                                        * '<S194>/T_e14'
                                        */
  real_T T_e24_Value_a;                /* Expression: 1
                                        * '<S194>/T_e24'
                                        */
  real_T l_x2_Value_i;                 /* Expression: 0.45
                                        * '<S194>/l_x2'
                                        */
  real_T l_x2_Gain_c;                  /* Expression: -1
                                        * '<S194>/-l_x2'
                                        */
  real_T T_e15_Value_f;                /* Expression: 0
                                        * '<S194>/T_e15'
                                        */
  real_T T_e25_Value_bb;               /* Expression: 1
                                        * '<S194>/T_e25'
                                        */
  real_T l_x3_Value_i;                 /* Expression: 0.385
                                        * '<S194>/l_x3'
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
                                        * '<S193>/u_1 to f_1'
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
                                        * '<S193>/u_1 to f_1'
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
                                        * '<S193>/u_2 to f_2'
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
                                        * '<S193>/u_2 to f_2'
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
                                        * '<S193>/u_3 to f_3'
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
                                        * '<S193>/u_3 to f_3'
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
                                        * '<S193>/u_4 to f_4'
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
                                        * '<S193>/u_4 to f_4'
                                        */
  real_T u_5tof_5_XData[7];            /* Expression: [-.3:0.1:.3]
                                        * '<S193>/u_5 to f_5'
                                        */
  real_T u_5tof_5_YData[7];            /* Expression: [-1.2630 -1.0309 -0.3808 0 0.3480  0.8290 1.0930]
                                        * '<S193>/u_5 to f_5'
                                        */
  real_T T_e11_Value_b;                /* Expression: 1
                                        * '<S122>/T_e11'
                                        */
  real_T T_e21_Value_cm;               /* Expression: 0
                                        * '<S122>/T_e21'
                                        */
  real_T l_y1_Value_d;                 /* Expression: 0.055
                                        * '<S122>/l_y1'
                                        */
  real_T T_e12_Value_d;                /* Expression: 0
                                        * '<S122>/T_e12'
                                        */
  real_T T_e22_Value_iv;               /* Expression: 1
                                        * '<S122>/T_e22'
                                        */
  real_T l_x1_Value_o;                 /* Expression: 0.45
                                        * '<S122>/l_x1'
                                        */
  real_T l_x1_Gain_k;                  /* Expression: -1
                                        * '<S122>/-l_x1'
                                        */
  real_T T_e13_Value_ol;               /* Expression: 1
                                        * '<S122>/T_e13'
                                        */
  real_T T_e23_Value_m;                /* Expression: 0
                                        * '<S122>/T_e23'
                                        */
  real_T l_y2_Value_d;                 /* Expression: 0.055
                                        * '<S122>/l_y2'
                                        */
  real_T l_y2_Gain_b;                  /* Expression: -1
                                        * '<S122>/-l_y2'
                                        */
  real_T T_e14_Value_i;                /* Expression: 0
                                        * '<S122>/T_e14'
                                        */
  real_T T_e24_Value_f;                /* Expression: 1
                                        * '<S122>/T_e24'
                                        */
  real_T l_x2_Value_a;                 /* Expression: 0.45
                                        * '<S122>/l_x2'
                                        */
  real_T l_x2_Gain_ik;                 /* Expression: -1
                                        * '<S122>/-l_x2'
                                        */
  real_T T_e15_Value_d;                /* Expression: 0
                                        * '<S122>/T_e15'
                                        */
  real_T T_e25_Value_j;                /* Expression: 1
                                        * '<S122>/T_e25'
                                        */
  real_T l_x3_Value_l;                 /* Expression: 0.385
                                        * '<S122>/l_x3'
                                        */
  real_T u_1tof_1_XData_p[19];         /* Expression: [-1.0000
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
                                        * '<S121>/u_1 to f_1'
                                        */
  real_T u_1tof_1_YData_k[19];         /* Expression: [-1.324
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
                                        * '<S121>/u_1 to f_1'
                                        */
  real_T u_2tof_2_XData_o[21];         /* Expression: [-1.0000
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
                                        * '<S121>/u_2 to f_2'
                                        */
  real_T u_2tof_2_YData_o[21];         /* Expression: [-0.766
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
                                        * '<S121>/u_2 to f_2'
                                        */
  real_T u_3tof_3_XData_i[19];         /* Expression: [-0.9000
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
                                        * '<S121>/u_3 to f_3'
                                        */
  real_T u_3tof_3_YData_i[19];         /* Expression: [-1.291
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
                                        * '<S121>/u_3 to f_3'
                                        */
  real_T u_4tof_4_XData_d[17];         /* Expression: [-0.9000
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
                                        * '<S121>/u_4 to f_4'
                                        */
  real_T u_4tof_4_YData_f[17];         /* Expression: [-1.249
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
                                        * '<S121>/u_4 to f_4'
                                        */
  real_T u_5tof_5_XData_c[7];          /* Expression: [-.3:0.1:.3]
                                        * '<S121>/u_5 to f_5'
                                        */
  real_T u_5tof_5_YData_o[7];          /* Expression: [-1.2630 -1.0309 -0.3808 0 0.3480  0.8290 1.0930]
                                        * '<S121>/u_5 to f_5'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * '<S15>/Integrator1'
                                        */
  real_T K_d3deg_Gain;                 /* Expression: 180/pi
                                        * '<S14>/K_d 3 deg'
                                        */
  real_T K_i3deg_Gain;                 /* Expression: 180/pi
                                        * '<S14>/K_i 3 deg'
                                        */
  real_T K_p3deg_Gain;                 /* Expression: 180/pi
                                        * '<S14>/K_p 3 deg'
                                        */
  real_T Reg_e_Psi_deg_Gain;           /* Expression: 180/pi
                                        * '<S14>/Reg_e_Psi_deg'
                                        */
  real_T etaPsideg_Gain;               /* Expression: 180/pi
                                        * '<S14>/eta Psi deg'
                                        */
  real_T Gain1_Gain_k[9];              /* Expression: 2*lambda*w_o
                                        * '<S15>/Gain1'
                                        */
  real_T Integrator2_IC_g;             /* Expression: 0
                                        * '<S15>/Integrator2'
                                        */
  real_T Gain2_Gain[9];                /* Expression: w_o*w_o
                                        * '<S15>/Gain2'
                                        */
  real_T Saturation_UpperSat_l;        /* Expression: 1e10
                                        * '<S24>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: -1e10
                                        * '<S24>/Saturation'
                                        */
  real_T Gain_Gain_gh;                 /* Expression: pi
                                        * '<S24>/Gain'
                                        */
  real_T Constant_Value_pu;            /* Expression: 2*pi
                                        * '<S24>/Constant'
                                        */
  real_T K4_Gain[9];                   /* Expression: K4
                                        * '<S15>/K4'
                                        */
  real_T Integrator3_IC;               /* Expression: 0
                                        * '<S15>/Integrator3'
                                        */
  real_T Gain6_Gain[9];                /* Expression: D
                                        * '<S15>/Gain6'
                                        */
  real_T Gain3_Gain[9];                /* Expression: inv(M)
                                        * '<S15>/Gain3'
                                        */
  real_T K11_Gain[9];                  /* Expression: -2*(eye(3)-lambda)*diag([w_c(1,1)/w_o(1,1) w_c(2,2)/w_o(2,2) w_c(3,3)/w_o(3,3)])
                                        * '<S15>/K11'
                                        */
  real_T K12_Gain[9];                  /* Expression: 2*w_o*(eye(3)-lambda)
                                        * '<S15>/K12'
                                        */
  real_T K2_Gain[9];                   /* Expression: w_c
                                        * '<S15>/K2'
                                        */
  real_T K3_Gain[9];                   /* Expression: K3
                                        * '<S15>/K3'
                                        */
  real_T invT_b_Gain[9];               /* Expression: diag([1/T_b(1,1) 1/T_b(2,2) 1/T_b(3,3)])
                                        * '<S15>/inv(T_b)'
                                        */
  real_T u_Value_eg;                   /* Expression: 0
                                        * '<S51>/12'
                                        */
  real_T u_Value_or;                   /* Expression: 0
                                        * '<S51>/21'
                                        */
  real_T Gamma_q_Surge_Value;          /* Expression: 10*2
                                        * '<S7>/Gamma_q_Surge'
                                        */
  real_T Gamma_q_Sway_Value;           /* Expression: 10*10
                                        * '<S7>/Gamma_q_Sway'
                                        */
  real_T Gain_Gain_n;                  /* Expression: -1
                                        * '<S63>/Gain'
                                        */
  real_T lambda_Value;                 /* Expression: 1
                                        * '<S7>/lambda'
                                        */
  real_T Gain_Gain_h;                  /* Expression: -1
                                        * '<S62>/Gain'
                                        */
  real_T u_Value_cv;                   /* Expression: 0
                                        * '<S127>/12'
                                        */
  real_T u_Value_pf;                   /* Expression: 0
                                        * '<S127>/21'
                                        */
  real_T Gamma_q_Surge_Value_a;        /* Expression: 10/200
                                        * '<S9>/Gamma_q_Surge'
                                        */
  real_T Gamma_q_Sway_Value_e;         /* Expression: 0.2*4
                                        * '<S9>/Gamma_q_Sway'
                                        */
  real_T lambda_Value_l;               /* Expression: 2
                                        * '<S9>/lambda'
                                        */
  real_T dotomega_q_Gain;              /* Expression: -1
                                        * '<S135>/dot omega_q'
                                        */
  real_T eta_dPsideg_Gain;             /* Expression: 180/pi
                                        * '<S219>/eta_d Psi deg'
                                        */
  real_T QTMIn1FN_Gain;                /* Expression: 1
                                        * '<S289>/QTM In1 FN'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S289>/QTM In2 Error'
                                        */
  real_T SITzAI1_P1;                   /* Expression: width
                                        * '<S289>/SIT zAI1'
                                        */
  real_T SITzAI1_P2;                   /* Expression: dtype
                                        * '<S289>/SIT zAI1'
                                        */
  real_T SITzAI1_P3;                   /* Expression: portnum
                                        * '<S289>/SIT zAI1'
                                        */
  real_T SITzAI1_P4;                   /* Expression: stime
                                        * '<S289>/SIT zAI1'
                                        */
  real_T SITzAI1_P5;                   /* Expression: stype
                                        * '<S289>/SIT zAI1'
                                        */
  real_T SITzAI1_P6;                   /* Expression: btype
                                        * '<S289>/SIT zAI1'
                                        */
  real_T BatteryServo_Gain;            /* Expression: 1
                                        * '<S289>/Battery Servo'
                                        */
  real_T SITzAI2_P1;                   /* Expression: width
                                        * '<S289>/SIT zAI2'
                                        */
  real_T SITzAI2_P2;                   /* Expression: dtype
                                        * '<S289>/SIT zAI2'
                                        */
  real_T SITzAI2_P3;                   /* Expression: portnum
                                        * '<S289>/SIT zAI2'
                                        */
  real_T SITzAI2_P4;                   /* Expression: stime
                                        * '<S289>/SIT zAI2'
                                        */
  real_T SITzAI2_P5;                   /* Expression: stype
                                        * '<S289>/SIT zAI2'
                                        */
  real_T SITzAI2_P6;                   /* Expression: btype
                                        * '<S289>/SIT zAI2'
                                        */
  real_T BatteryMain_Gain;             /* Expression: 2
                                        * '<S289>/Battery Main'
                                        */
  real_T SITzAI0_P1;                   /* Expression: width
                                        * '<S289>/SIT zAI0'
                                        */
  real_T SITzAI0_P2;                   /* Expression: dtype
                                        * '<S289>/SIT zAI0'
                                        */
  real_T SITzAI0_P3;                   /* Expression: portnum
                                        * '<S289>/SIT zAI0'
                                        */
  real_T SITzAI0_P4;                   /* Expression: stime
                                        * '<S289>/SIT zAI0'
                                        */
  real_T SITzAI0_P5;                   /* Expression: stype
                                        * '<S289>/SIT zAI0'
                                        */
  real_T SITzAI0_P6;                   /* Expression: btype
                                        * '<S289>/SIT zAI0'
                                        */
  real_T BatteryBowThruster_Gain;      /* Expression: 1
                                        * '<S289>/Battery Bow Thruster'
                                        */
  real_T Saturation_UpperSat_d0;       /* Expression: 3
                                        * '<S299>/Saturation'
                                        */
  real_T Saturation_LowerSat_o0;       /* Expression: -2.6
                                        * '<S299>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 3
                                        * '<S299>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -3.5
                                        * '<S299>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.6
                                        * '<S299>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S299>/Saturation2'
                                        */
  real_T planttau_surge_Gain;          /* Expression: 1
                                        * '<S299>/plant tau_surge'
                                        */
  real_T planttau_sway_Gain;           /* Expression: 1
                                        * '<S299>/plant tau_sway'
                                        */
  real_T planttau_yaw_Gain;            /* Expression: 1
                                        * '<S299>/plant tau_yaw'
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
  real_T Constant_Value_n2;            /* Expression: NaN
                                        * '<S5>/Constant'
                                        */
  real_T Constant1_Value_k;            /* Expression: NaN
                                        * '<S5>/Constant1'
                                        */
  real_T Gain_Gain_c;                  /* Expression: 180/pi
                                        * '<S297>/Gain'
                                        */
  real_T Gain_Gain_ee;                 /* Expression: 180/pi
                                        * '<S298>/Gain'
                                        */
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T R12_Gain;                     /* Expression: -1
                                        * '<S268>/R12'
                                        */
  real_T R22_Gain;                     /* Expression: 1
                                        * '<S268>/R22'
                                        */
  real_T _Value_m;                     /* Expression: 0
                                        * '<S270>/0'
                                        */
  real_T S12_Gain_b;                   /* Expression: -1
                                        * '<S270>/S12'
                                        */
  real_T _Value_p;                     /* Expression: 0
                                        * '<S271>/0'
                                        */
  real_T S12_Gain_p;                   /* Expression: -1
                                        * '<S271>/S12'
                                        */
  real_T Delta_Value;                  /* Expression: 2
                                        * '<S220>/Delta'
                                        */
  real_T Constant_Value_km;            /* Expression: 2*180
                                        * '<S228>/Constant'
                                        */
  real_T Gain_Gain_i;                  /* Expression: 180/pi
                                        * '<S230>/Gain'
                                        */
  real_T Saturation_UpperSat_lj;       /* Expression: 1e10
                                        * '<S228>/Saturation'
                                        */
  real_T Saturation_LowerSat_j;        /* Expression: -1e10
                                        * '<S228>/Saturation'
                                        */
  real_T Gain_Gain_m;                  /* Expression: 180
                                        * '<S228>/Gain'
                                        */
  real_T Gain1_Gain_hm;                /* Expression: pi/180
                                        * '<S229>/Gain1'
                                        */
  real_T _2x1_Value_e;                 /* Expression: 0
                                        * '<S277>/0_2x1'
                                        */
  real_T u_Gain_k;                     /* Expression: 2
                                        * '<S227>/+ 2'
                                        */
  real_T Gain_Gain_oi;                 /* Expression: 180/pi
                                        * '<S263>/Gain'
                                        */
  real_T Saturation_UpperSat_i;        /* Expression: 1e10
                                        * '<S259>/Saturation'
                                        */
  real_T Saturation_LowerSat_hv;       /* Expression: -1e10
                                        * '<S259>/Saturation'
                                        */
  real_T Gain_Gain_ib;                 /* Expression: 180
                                        * '<S259>/Gain'
                                        */
  real_T Constant_Value_bc;            /* Expression: 2*180
                                        * '<S259>/Constant'
                                        */
  real_T Gain1_Gain_a;                 /* Expression: pi/180
                                        * '<S262>/Gain1'
                                        */
  real_T Gain_Gain_nv;                 /* Expression: 180/pi
                                        * '<S265>/Gain'
                                        */
  real_T Saturation_UpperSat_a;        /* Expression: 1e10
                                        * '<S260>/Saturation'
                                        */
  real_T Saturation_LowerSat_o4;       /* Expression: -1e10
                                        * '<S260>/Saturation'
                                        */
  real_T Gain_Gain_e1;                 /* Expression: 180
                                        * '<S260>/Gain'
                                        */
  real_T Constant_Value_ab;            /* Expression: 2*180
                                        * '<S260>/Constant'
                                        */
  real_T Gain1_Gain_jx;                /* Expression: pi/180
                                        * '<S264>/Gain1'
                                        */
  real_T Gain_Gain_dn;                 /* Expression: 180/pi
                                        * '<S267>/Gain'
                                        */
  real_T Saturation_UpperSat_b;        /* Expression: 1e10
                                        * '<S261>/Saturation'
                                        */
  real_T Saturation_LowerSat_g;        /* Expression: -1e10
                                        * '<S261>/Saturation'
                                        */
  real_T Gain_Gain_p;                  /* Expression: 180
                                        * '<S261>/Gain'
                                        */
  real_T Constant_Value_nd1;           /* Expression: 2*180
                                        * '<S261>/Constant'
                                        */
  real_T Gain1_Gain_p;                 /* Expression: pi/180
                                        * '<S266>/Gain1'
                                        */
  real_T Constant_Value_p1[4];         /* Expression: a
                                        * '<S237>/Constant'
                                        */
  real_T Gain_Gain_pi;                 /* Expression: 0
                                        * '<S254>/Gain'
                                        */
  real_T _2x1_Value_pc[2];             /* Expression: [0;0]
                                        * '<S231>/0_2x1'
                                        */
  real_T Gain_Gain_ghk;                /* Expression: -1
                                        * '<S239>/Gain'
                                        */
  real_T Gain_Gain_ma;                 /* Expression: -1
                                        * '<S240>/Gain'
                                        */
  real_T my_Value;                     /* Expression: 10
                                        * '<S220>/my'
                                        */
  real_T Gain_Gain_eo;                 /* Expression: -1
                                        * '<S246>/Gain'
                                        */
  real_T u_Value_m1;                   /* Expression: 3/2
                                        * '<S243>/3//2'
                                        */
  real_T Gain_Gain_oz;                 /* Expression: -1
                                        * '<S247>/Gain'
                                        */
  real_T u_Value_on;                   /* Expression: 3/2
                                        * '<S244>/3//2'
                                        */
  real_T Constant_Value_po;            /* Expression: 3
                                        * '<S283>/Constant'
                                        */
  real_T Gain_Gain_o2;                 /* Expression: -1
                                        * '<S283>/Gain'
                                        */
  real_T Constant_Value_nh;            /* Expression: 3
                                        * '<S248>/Constant'
                                        */
  real_T _Value_d;                     /* Expression: 2
                                        * '<S255>/2'
                                        */
  real_T _2x2_Value_b[4];              /* Expression: [0 0;0 0]
                                        * '<S236>/0_2x2'
                                        */
  real_T _Value_mn;                    /* Expression: 2
                                        * '<S256>/2'
                                        */
  real_T _Value_h;                     /* Expression: 2
                                        * '<S258>/2'
                                        */
  real_T _Gain_a;                      /* Expression: 2
                                        * '<S276>/2'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 0
                                        * '<S276>/Gain'
                                        */
  real_T SITOut5BT_P1;                 /* Expression: width
                                        * '<S300>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P2;                 /* Expression: dtype
                                        * '<S300>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P3;                 /* Expression: portnum
                                        * '<S300>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P4;                 /* Expression: stime
                                        * '<S300>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P5;                 /* Expression: stype
                                        * '<S300>/SIT Out5 BT'
                                        */
  real_T SITOut5BT_P6;                 /* Expression: btype
                                        * '<S300>/SIT Out5 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S300>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S300>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S300>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S300>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S300>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S300>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S300>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_j3;            /* Expression: 0
                                        * '<S300>/Constant'
                                        */
  real_T Constant1_Value_f;            /* Expression: 0
                                        * '<S300>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S300>/Neg'
                                        */
  real_T SITOut1Servo1_P1;             /* Expression: width
                                        * '<S301>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P2;             /* Expression: dtype
                                        * '<S301>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P3;             /* Expression: portnum
                                        * '<S301>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P4;             /* Expression: stime
                                        * '<S301>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P5;             /* Expression: stype
                                        * '<S301>/SIT Out1 Servo1'
                                        */
  real_T SITOut1Servo1_P6;             /* Expression: btype
                                        * '<S301>/SIT Out1 Servo1'
                                        */
  real_T SITOut2Servo2_P1;             /* Expression: width
                                        * '<S301>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P2;             /* Expression: dtype
                                        * '<S301>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P3;             /* Expression: portnum
                                        * '<S301>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P4;             /* Expression: stime
                                        * '<S301>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P5;             /* Expression: stype
                                        * '<S301>/SIT Out2 Servo2'
                                        */
  real_T SITOut2Servo2_P6;             /* Expression: btype
                                        * '<S301>/SIT Out2 Servo2'
                                        */
  real_T SITOut3Servo3_P1;             /* Expression: width
                                        * '<S301>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P2;             /* Expression: dtype
                                        * '<S301>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P3;             /* Expression: portnum
                                        * '<S301>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P4;             /* Expression: stime
                                        * '<S301>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P5;             /* Expression: stype
                                        * '<S301>/SIT Out3 Servo3'
                                        */
  real_T SITOut3Servo3_P6;             /* Expression: btype
                                        * '<S301>/SIT Out3 Servo3'
                                        */
  real_T SITOut4Servo4_P1;             /* Expression: width
                                        * '<S301>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P2;             /* Expression: dtype
                                        * '<S301>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P3;             /* Expression: portnum
                                        * '<S301>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P4;             /* Expression: stime
                                        * '<S301>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P5;             /* Expression: stype
                                        * '<S301>/SIT Out4 Servo4'
                                        */
  real_T SITOut4Servo4_P6;             /* Expression: btype
                                        * '<S301>/SIT Out4 Servo4'
                                        */
  real_T SITOut6VSPSPort_P1;           /* Expression: width
                                        * '<S301>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P2;           /* Expression: dtype
                                        * '<S301>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P3;           /* Expression: portnum
                                        * '<S301>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P4;           /* Expression: stime
                                        * '<S301>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P5;           /* Expression: stype
                                        * '<S301>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut6VSPSPort_P6;           /* Expression: btype
                                        * '<S301>/SIT Out6 VSPS Port'
                                        */
  real_T SITOut7VSPSStarboard_P1;      /* Expression: width
                                        * '<S301>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S301>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S301>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P4;      /* Expression: stime
                                        * '<S301>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P5;      /* Expression: stype
                                        * '<S301>/SIT Out7 VSPS Starboard'
                                        */
  real_T SITOut7VSPSStarboard_P6;      /* Expression: btype
                                        * '<S301>/SIT Out7 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S301>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S301>/-y'
                                        */
  real_T Gain_Gain_a3;                 /* Expression: 180/pi
                                        * '<S307>/Gain'
                                        */
  real_T Gain_Gain_cy;                 /* Expression: 180/pi
                                        * '<S308>/Gain'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S301>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S301>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S301>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S301>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S301>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S301>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S301>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S301>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S301>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S301>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S301>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S301>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S301>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S301>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S301>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S301>/VSPS Starboard'
                                        */
  real_T N_r_Value_j;                  /* Expression: -1.900
                                        * '<S310>/N_r'
                                        */
  real_T N_r_Gain_i;                   /* Expression: -1
                                        * '<S310>/-N_r'
                                        */
  real_T N_v_Value_c;                  /* Expression: 0.18140
                                        * '<S310>/N_v'
                                        */
  real_T N_v_Gain_l;                   /* Expression: -1
                                        * '<S310>/-N_v'
                                        */
  real_T X_u_Value_m;                  /* Expression: -0.59739
                                        * '<S310>/X_u'
                                        */
  real_T X_u_Gain_k;                   /* Expression: -1
                                        * '<S310>/-X_u'
                                        */
  real_T Y_v_Value_kr;                 /* Expression: -3.50625
                                        * '<S310>/Y_v'
                                        */
  real_T Y_v_Gain_d2;                  /* Expression: -1
                                        * '<S310>/-Y_v'
                                        */
  real_T Y_r_Value_m;                  /* Expression: -7.250
                                        * '<S310>/Y_r'
                                        */
  real_T Y_vr_Gain_j;                  /* Expression: -1
                                        * '<S310>/-Y_vr'
                                        */
  real_T D_L_12_Value_a;               /* Expression: 0
                                        * '<S310>/D_L_12'
                                        */
  real_T D_L_13_Value_k;               /* Expression: 0
                                        * '<S310>/D_L_13'
                                        */
  real_T D_L_21_Value_a;               /* Expression: 0
                                        * '<S310>/D_L_21'
                                        */
  real_T D_L_31_Value_k;               /* Expression: 0
                                        * '<S310>/D_L_31'
                                        */
  real_T psi_0_Value;                  /* Expression: 0
                                        * '<S311>/psi_0'
                                        */
  real_T x_0_Value;                    /* Expression: 0
                                        * '<S311>/x_0'
                                        */
  real_T y_0_Value;                    /* Expression: 0
                                        * '<S311>/y_0'
                                        */
  real_T r_0_Value;                    /* Expression: 0
                                        * '<S312>/r_0'
                                        */
  real_T u_0_Value;                    /* Expression: 0
                                        * '<S312>/u_0'
                                        */
  real_T v_0_Value;                    /* Expression: 0
                                        * '<S312>/v_0'
                                        */
  real_T ResetLinearSimulatorintegrator_;/* Expression: 0
                                          * '<S309>/Reset Linear Simulator integrator'
                                          */
  real_T I_z_Value_a;                  /* Expression: 1.760
                                        * '<S313>/I_z'
                                        */
  real_T m_Value_d;                    /* Expression: 17.6
                                        * '<S313>/m'
                                        */
  real_T X_udot_Value_b;               /* Expression: -2.0
                                        * '<S313>/X_udot'
                                        */
  real_T M_21_Value_c;                 /* Expression: 0
                                        * '<S313>/M_21'
                                        */
  real_T M_31_Value_j;                 /* Expression: 0
                                        * '<S313>/M_31'
                                        */
  real_T M_12_Value_h;                 /* Expression: 0
                                        * '<S313>/M_12'
                                        */
  real_T Y_vdot_Value_i;               /* Expression: -10.0
                                        * '<S313>/Y_vdot'
                                        */
  real_T x_g_Value_p;                  /* Expression: 0.03
                                        * '<S313>/x_g'
                                        */
  real_T N_vdot_Value_d;               /* Expression: -0.0
                                        * '<S313>/N_vdot'
                                        */
  real_T M_13_Value_g;                 /* Expression: 0
                                        * '<S313>/M_13'
                                        */
  real_T Y_rdot_Value_e;               /* Expression: 0.0
                                        * '<S313>/Y_rdot'
                                        */
  real_T N_rdot_Value_h;               /* Expression: -1.0
                                        * '<S313>/N_rdot'
                                        */
  real_T R31_Value_f;                  /* Expression: 0
                                        * '<S314>/R31'
                                        */
  real_T R32_Value_ag;                 /* Expression: 0
                                        * '<S314>/R32'
                                        */
  real_T R13_Value_e;                  /* Expression: 0
                                        * '<S314>/R13'
                                        */
  real_T R23_Value_p;                  /* Expression: 0
                                        * '<S314>/R23'
                                        */
  real_T R33_Value_en;                 /* Expression: 1
                                        * '<S314>/R33'
                                        */
  real_T eta_surge_hil_Gain;           /* Expression: 1
                                        * '<S296>/eta_surge_hil'
                                        */
  real_T eta_sway_hil_Gain;            /* Expression: 1
                                        * '<S296>/eta_sway_hil'
                                        */
  real_T eta_yaw_hil_Gain;             /* Expression: 1
                                        * '<S296>/eta_yaw_hil'
                                        */
  real_T etadot_surge_hil_Gain;        /* Expression: 1
                                        * '<S296>/etadot_surge_hil'
                                        */
  real_T etadot_sway_hil_Gain;         /* Expression: 1
                                        * '<S296>/etadot_sway_hil'
                                        */
  real_T etadot_yaw_hil_Gain;          /* Expression: 1
                                        * '<S296>/etadot_yaw_hil'
                                        */
  real_T nu_surge_hil_Gain;            /* Expression: 1
                                        * '<S296>/nu_surge_hil'
                                        */
  real_T nu_sway_hil_Gain;             /* Expression: 1
                                        * '<S296>/nu_sway_hil'
                                        */
  real_T nu_yaw_hil_Gain;              /* Expression: 1
                                        * '<S296>/nu_yaw_hil'
                                        */
  uint8_T Gain_Gain_fo;                /* Computed Parameter: Gain
                                        * '<S198>/Gain'
                                        */
  uint8_T Gain1_Gain_g;                /* Computed Parameter: Gain
                                        * '<S198>/Gain1'
                                        */
  uint8_T Gain_Gain_g5;                /* Computed Parameter: Gain
                                        * '<S199>/Gain'
                                        */
  uint8_T Gain1_Gain_gm;               /* Computed Parameter: Gain
                                        * '<S199>/Gain1'
                                        */
  uint8_T Gain_Gain_ga;                /* Computed Parameter: Gain
                                        * '<S200>/Gain'
                                        */
  uint8_T Gain1_Gain_af;               /* Computed Parameter: Gain
                                        * '<S200>/Gain1'
                                        */
  uint8_T Gain_Gain_l;                 /* Computed Parameter: Gain
                                        * '<S201>/Gain'
                                        */
  uint8_T Gain1_Gain_ay;               /* Computed Parameter: Gain
                                        * '<S201>/Gain1'
                                        */
  uint8_T Gain_Gain_gh3;               /* Computed Parameter: Gain
                                        * '<S202>/Gain'
                                        */
  uint8_T Gain1_Gain_l;                /* Computed Parameter: Gain
                                        * '<S202>/Gain1'
                                        */
  uint8_T Gain_Gain_ja;                /* Computed Parameter: Gain
                                        * '<S27>/Gain'
                                        */
  uint8_T Gain1_Gain_d;                /* Computed Parameter: Gain
                                        * '<S27>/Gain1'
                                        */
  uint8_T Gain_Gain_gm;                /* Computed Parameter: Gain
                                        * '<S28>/Gain'
                                        */
  uint8_T Gain1_Gain_l5;               /* Computed Parameter: Gain
                                        * '<S28>/Gain1'
                                        */
  uint8_T Gain_Gain_dx;                /* Computed Parameter: Gain
                                        * '<S29>/Gain'
                                        */
  uint8_T Gain1_Gain_ax;               /* Computed Parameter: Gain
                                        * '<S29>/Gain1'
                                        */
  uint8_T Gain_Gain_jb;                /* Computed Parameter: Gain
                                        * '<S30>/Gain'
                                        */
  uint8_T Gain1_Gain_f;                /* Computed Parameter: Gain
                                        * '<S30>/Gain1'
                                        */
  uint8_T Gain_Gain_d3;                /* Computed Parameter: Gain
                                        * '<S31>/Gain'
                                        */
  uint8_T Gain1_Gain_o;                /* Computed Parameter: Gain
                                        * '<S31>/Gain1'
                                        */
  uint8_T Gain_Gain_ps;                /* Computed Parameter: Gain
                                        * '<S83>/Gain'
                                        */
  uint8_T Gain1_Gain_id;               /* Computed Parameter: Gain
                                        * '<S83>/Gain1'
                                        */
  uint8_T Gain_Gain_pu;                /* Computed Parameter: Gain
                                        * '<S84>/Gain'
                                        */
  uint8_T Gain1_Gain_j2;               /* Computed Parameter: Gain
                                        * '<S84>/Gain1'
                                        */
  uint8_T Gain_Gain_of;                /* Computed Parameter: Gain
                                        * '<S85>/Gain'
                                        */
  uint8_T Gain1_Gain_it;               /* Computed Parameter: Gain
                                        * '<S85>/Gain1'
                                        */
  uint8_T Gain_Gain_jf;                /* Computed Parameter: Gain
                                        * '<S86>/Gain'
                                        */
  uint8_T Gain1_Gain_kr;               /* Computed Parameter: Gain
                                        * '<S86>/Gain1'
                                        */
  uint8_T Gain_Gain_eb;                /* Computed Parameter: Gain
                                        * '<S87>/Gain'
                                        */
  uint8_T Gain1_Gain_pn;               /* Computed Parameter: Gain
                                        * '<S87>/Gain1'
                                        */
  uint8_T Gain_Gain_of2;               /* Computed Parameter: Gain
                                        * '<S165>/Gain'
                                        */
  uint8_T Gain1_Gain_c;                /* Computed Parameter: Gain
                                        * '<S165>/Gain1'
                                        */
  uint8_T Gain_Gain_j0;                /* Computed Parameter: Gain
                                        * '<S166>/Gain'
                                        */
  uint8_T Gain1_Gain_li;               /* Computed Parameter: Gain
                                        * '<S166>/Gain1'
                                        */
  uint8_T Gain_Gain_ks;                /* Computed Parameter: Gain
                                        * '<S167>/Gain'
                                        */
  uint8_T Gain1_Gain_dn;               /* Computed Parameter: Gain
                                        * '<S167>/Gain1'
                                        */
  uint8_T Gain_Gain_jt;                /* Computed Parameter: Gain
                                        * '<S168>/Gain'
                                        */
  uint8_T Gain1_Gain_io;               /* Computed Parameter: Gain
                                        * '<S168>/Gain1'
                                        */
  uint8_T Gain_Gain_oz4;               /* Computed Parameter: Gain
                                        * '<S169>/Gain'
                                        */
  uint8_T Gain1_Gain_h0;               /* Computed Parameter: Gain
                                        * '<S169>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_CSE1_CV3_1Straight {
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
    real_T odeY[43];
    real_T odeF[4][43];
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
extern Parameters_CSE1_CV3_1Straight CSE1_CV3_1Straight_P;

/* Block signals (auto storage) */
extern BlockIO_CSE1_CV3_1Straight CSE1_CV3_1Straight_B;

/* Continuous states (auto storage) */
extern ContinuousStates_CSE1_CV3_1Stra CSE1_CV3_1Straight_X;

/* Block states (auto storage) */
extern D_Work_CSE1_CV3_1Straight CSE1_CV3_1Straight_DWork;

/* Constant parameters (auto storage) */
extern const ConstParam_CSE1_CV3_1Straight CSE1_CV3_1Straight_ConstP;

/* Model entry point functions */
extern void CSE1_CV3_1Straight_initialize(boolean_T firstTime);
extern void CSE1_CV3_1Straight_output(int_T tid);
extern void CSE1_CV3_1Straight_update(int_T tid);
extern void CSE1_CV3_1Straight_terminate(void);

/* Real-time Model object */
extern RT_MODEL_CSE1_CV3_1Straight *CSE1_CV3_1Straight_M;

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
 * '<Root>' : CSE1_CV3_1Straight
 * '<S1>'   : CSE1_CV3_1Straight/Control Systems
 * '<S2>'   : CSE1_CV3_1Straight/Guidance Systems
 * '<S3>'   : CSE1_CV3_1Straight/HMI
 * '<S4>'   : CSE1_CV3_1Straight/Naviagation Systems
 * '<S5>'   : CSE1_CV3_1Straight/Plants
 * '<S6>'   : CSE1_CV3_1Straight/Control Systems/DP control
 * '<S7>'   : CSE1_CV3_1Straight/Control Systems/LgV design 2
 * '<S8>'   : CSE1_CV3_1Straight/Control Systems/Manual Thruster control
 * '<S9>'   : CSE1_CV3_1Straight/Control Systems/Nonlinear PID
 * '<S10>'  : CSE1_CV3_1Straight/Control Systems/PS3 input
 * '<S11>'  : CSE1_CV3_1Straight/Control Systems/Precision control
 * '<S12>'  : CSE1_CV3_1Straight/Control Systems/Simple Control
 * '<S13>'  : CSE1_CV3_1Straight/Control Systems/if Nonlinear PID Control
 * '<S14>'  : CSE1_CV3_1Straight/Control Systems/DP control/DP controller
 * '<S15>'  : CSE1_CV3_1Straight/Control Systems/DP control/Passive DP wave filter1
 * '<S16>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation
 * '<S17>'  : CSE1_CV3_1Straight/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1
 * '<S18>'  : CSE1_CV3_1Straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]
 * '<S19>'  : CSE1_CV3_1Straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1
 * '<S20>'  : CSE1_CV3_1Straight/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1
 * '<S21>'  : CSE1_CV3_1Straight/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw
 * '<S22>'  : CSE1_CV3_1Straight/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1
 * '<S23>'  : CSE1_CV3_1Straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]
 * '<S24>'  : CSE1_CV3_1Straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1
 * '<S25>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act
 * '<S26>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/tau to f_act
 * '<S27>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S28>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S29>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S30>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S31>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S32>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S33>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S34>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S35>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S36>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S37>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/if == 0
 * '<S38>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S39>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S40>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S41>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S42>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S43>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S44>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S45>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S46>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S47>'  : CSE1_CV3_1Straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e
 * '<S48>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxilary functions g_q
 * '<S49>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxiliary function g_s
 * '<S50>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Control law
 * '<S51>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Gamma_q
 * '<S52>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Integral action state
 * '<S53>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/K_d
 * '<S54>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/K_i
 * '<S55>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/K_p
 * '<S56>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/M
 * '<S57>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/R(psi)
 * '<S58>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/R^T
 * '<S59>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/S(r)
 * '<S60>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/S^T
 * '<S61>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation
 * '<S62>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Update laws
 * '<S63>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/V_1^q
 * '<S64>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Virtual control
 * '<S65>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/alpha^q
 * '<S66>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/alpha^s
 * '<S67>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/sigma eq
 * '<S68>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq
 * '<S69>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_2 eq
 * '<S70>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q eq
 * '<S71>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq
 * '<S72>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^s eq
 * '<S73>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^t eq
 * '<S74>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/f_q^T
 * '<S75>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T
 * '<S76>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s eq
 * '<S77>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq
 * '<S78>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq
 * '<S79>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^t eq
 * '<S80>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Control law/D_L
 * '<S81>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act
 * '<S82>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act
 * '<S83>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S84>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S85>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S86>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S87>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S88>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S89>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S90>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S91>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S92>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S93>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/if == 0
 * '<S94>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S95>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S96>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S97>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S98>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S99>'  : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S100>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S101>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S102>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S103>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e
 * '<S104>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/Update laws/Transpose
 * '<S105>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/Update laws/q_0
 * '<S106>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/V_1^q/Transpose
 * '<S107>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/Virtual control/I
 * '<S108>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/alpha^q/I
 * '<S109>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/alpha^s/I
 * '<S110>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/sigma eq/I
 * '<S111>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq/heading to pipi
 * '<S112>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1
 * '<S113>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi
 * '<S114>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Degrees to Radians
 * '<S115>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Radians to Degrees
 * '<S116>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi
 * '<S117>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Degrees to Radians
 * '<S118>' : CSE1_CV3_1Straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Radians to Degrees
 * '<S119>' : CSE1_CV3_1Straight/Control Systems/Manual Thruster control/Subsystem
 * '<S120>' : CSE1_CV3_1Straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau
 * '<S121>' : CSE1_CV3_1Straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act
 * '<S122>' : CSE1_CV3_1Straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e
 * '<S123>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxilary functions g_q
 * '<S124>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxiliary function g_s
 * '<S125>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Control law
 * '<S126>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error
 * '<S127>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Gamma_q
 * '<S128>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Integral action state
 * '<S129>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/K_d
 * '<S130>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/K_i
 * '<S131>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/K_p
 * '<S132>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/R(psi)
 * '<S133>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/R^T
 * '<S134>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation
 * '<S135>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Update laws
 * '<S136>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/a_d
 * '<S137>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/nu tilde
 * '<S138>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/v_d
 * '<S139>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q eq
 * '<S140>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq
 * '<S141>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^s eq
 * '<S142>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^t eq
 * '<S143>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/f_q^T
 * '<S144>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/psi_los^q^2^T
 * '<S145>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s eq
 * '<S146>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq
 * '<S147>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq
 * '<S148>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^t eq
 * '<S149>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Control law/S(r)
 * '<S150>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Control law/tau_FF
 * '<S151>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Control law/tau_FL
 * '<S152>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Control law/tau_PID
 * '<S153>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Control law/tau_FF/M
 * '<S154>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L
 * '<S155>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error/heading to pipi
 * '<S156>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error/heading to pipi1
 * '<S157>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi
 * '<S158>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Degrees to Radians
 * '<S159>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Radians to Degrees
 * '<S160>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi
 * '<S161>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Degrees to Radians
 * '<S162>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Radians to Degrees
 * '<S163>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act
 * '<S164>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act
 * '<S165>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S166>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S167>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S168>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S169>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S170>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S171>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S172>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S173>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S174>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S175>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/if == 0
 * '<S176>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S177>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S178>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S179>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S180>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S181>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S182>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S183>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S184>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S185>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e
 * '<S186>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Update laws/Transpose
 * '<S187>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/Update laws/q_0
 * '<S188>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/a_d/v_d^q
 * '<S189>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/a_d/v_d^s
 * '<S190>' : CSE1_CV3_1Straight/Control Systems/Nonlinear PID/a_d/v_d^t
 * '<S191>' : CSE1_CV3_1Straight/Control Systems/Precision control/Subsystem
 * '<S192>' : CSE1_CV3_1Straight/Control Systems/Precision control/Subsystem/f_act to tau
 * '<S193>' : CSE1_CV3_1Straight/Control Systems/Precision control/Subsystem/u_act to f_act
 * '<S194>' : CSE1_CV3_1Straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e
 * '<S195>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation
 * '<S196>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act
 * '<S197>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/tau to f_act
 * '<S198>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S199>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S200>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S201>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S202>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S203>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S204>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S205>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S206>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S207>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S208>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/if == 0
 * '<S209>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S210>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S211>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S212>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S213>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S214>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S215>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S216>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S217>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S218>' : CSE1_CV3_1Straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e
 * '<S219>' : CSE1_CV3_1Straight/Guidance Systems/DP
 * '<S220>' : CSE1_CV3_1Straight/Guidance Systems/Path-following
 * '<S221>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Heading
 * '<S222>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight
 * '<S223>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Path
 * '<S224>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Speed assigment
 * '<S225>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Heading/psi_d eq
 * '<S226>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Heading/psi_d^s eq
 * '<S227>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq
 * '<S228>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi
 * '<S229>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians
 * '<S230>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees
 * '<S231>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector
 * '<S232>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot
 * '<S233>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot
 * '<S234>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot
 * '<S235>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading
 * '<S236>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals
 * '<S237>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I
 * '<S238>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq
 * '<S239>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq
 * '<S240>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq
 * '<S241>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq
 * '<S242>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq
 * '<S243>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq
 * '<S244>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq
 * '<S245>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq
 * '<S246>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq
 * '<S247>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq
 * '<S248>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq
 * '<S249>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose
 * '<S250>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose
 * '<S251>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1
 * '<S252>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2
 * '<S253>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq
 * '<S254>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq
 * '<S255>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq
 * '<S256>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq
 * '<S257>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq
 * '<S258>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq
 * '<S259>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1
 * '<S260>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2
 * '<S261>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3
 * '<S262>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians
 * '<S263>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees
 * '<S264>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians
 * '<S265>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees
 * '<S266>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians
 * '<S267>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees
 * '<S268>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2
 * '<S269>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2^T
 * '<S270>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2
 * '<S271>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)
 * '<S272>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T
 * '<S273>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2^T
 * '<S274>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq
 * '<S275>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq
 * '<S276>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq
 * '<S277>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Path/Straight path
 * '<S278>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Path/Straight path/p_d eq
 * '<S279>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Path/Straight path/p_d^s eq
 * '<S280>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq
 * '<S281>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/p_d^s^T
 * '<S282>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Speed assigment/v_s eq
 * '<S283>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq
 * '<S284>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Speed assigment/v_s^t eq
 * '<S285>' : CSE1_CV3_1Straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/p_d^s^T
 * '<S286>' : CSE1_CV3_1Straight/HMI/DP Input
 * '<S287>' : CSE1_CV3_1Straight/HMI/Path-following input
 * '<S288>' : CSE1_CV3_1Straight/HMI/DP Input/Degrees to Radians
 * '<S289>' : CSE1_CV3_1Straight/Naviagation Systems/Qualisys 6 DOF
 * '<S290>' : CSE1_CV3_1Straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix
 * '<S291>' : CSE1_CV3_1Straight/Plants/CSE1
 * '<S292>' : CSE1_CV3_1Straight/Plants/Compare To Zero
 * '<S293>' : CSE1_CV3_1Straight/Plants/Compare To Zero1
 * '<S294>' : CSE1_CV3_1Straight/Plants/Compare To Zero2
 * '<S295>' : CSE1_CV3_1Straight/Plants/Compare To Zero3
 * '<S296>' : CSE1_CV3_1Straight/Plants/Linear Simulator
 * '<S297>' : CSE1_CV3_1Straight/Plants/Port VSP direction
 * '<S298>' : CSE1_CV3_1Straight/Plants/Starboard VSP direction
 * '<S299>' : CSE1_CV3_1Straight/Plants/saturation
 * '<S300>' : CSE1_CV3_1Straight/Plants/CSE1/Bow Thruster
 * '<S301>' : CSE1_CV3_1Straight/Plants/CSE1/Voith Schneider Propeller
 * '<S302>' : CSE1_CV3_1Straight/Plants/CSE1/Bow Thruster/Saturation Dynamic
 * '<S303>' : CSE1_CV3_1Straight/Plants/CSE1/Bow Thruster/Saturation Dynamic1
 * '<S304>' : CSE1_CV3_1Straight/Plants/CSE1/Bow Thruster/Saturation Dynamic2
 * '<S305>' : CSE1_CV3_1Straight/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Port
 * '<S306>' : CSE1_CV3_1Straight/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Starboard
 * '<S307>' : CSE1_CV3_1Straight/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port
 * '<S308>' : CSE1_CV3_1Straight/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard
 * '<S309>' : CSE1_CV3_1Straight/Plants/Linear Simulator/Linear Vessel Dynamics
 * '<S310>' : CSE1_CV3_1Straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L
 * '<S311>' : CSE1_CV3_1Straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta
 * '<S312>' : CSE1_CV3_1Straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu
 * '<S313>' : CSE1_CV3_1Straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv
 * '<S314>' : CSE1_CV3_1Straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)
 */
#endif                                 /* RTW_HEADER_CSE1_CV3_1Straight_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_CSE1_CV3_1Straight
#ifdef RVE
#ifdef MULTITASKING

Parameters_CSE1_CV3_1Straight rtParameter[NUMST+!TID01EQ];

#define CSE1_CV3_1Straight_P           (*param_lookup[tid][READSIDE])

Parameters_CSE1_CV3_1Straight *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_CSE1_CV3_1Straight rtParameter[2];

#define CSE1_CV3_1Straight_P           rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
