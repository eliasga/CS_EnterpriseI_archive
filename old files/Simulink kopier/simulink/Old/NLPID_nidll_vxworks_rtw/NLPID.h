/*
 * NLPID.h
 *
 * Real-Time Workshop code generation for Simulink model "NLPID.mdl".
 *
 * Model Version              : 1.31
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Mon Mar 17 14:06:18 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_NLPID_h_
#define RTW_HEADER_NLPID_h_
#ifndef NLPID_COMMON_INCLUDES_
# define NLPID_COMMON_INCLUDES_
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
#endif                                 /* NLPID_COMMON_INCLUDES_ */

#include "NLPID_types.h"

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
#define NLPID_rtModel                  RT_MODEL_NLPID

/* Block signals (auto storage) */
typedef struct {
  real_T QTMIn[9];                     /* '<S196>/QTM In' */
  real_T QTMIn2Error;                  /* '<S196>/QTM In2 Error' */
  real_T QTMIn9Residual;               /* '<S196>/QTM In9 Residual' */
  real_T QTMIn3;                       /* '<S196>/QTM In3' */
  real_T mm2mx;                        /* '<S196>/mm2m x' */
  real_T QTMIn4;                       /* '<S196>/QTM In4' */
  real_T mm2my;                        /* '<S196>/mm2m y' */
  real_T QTMIn6;                       /* '<S196>/QTM In6' */
  real_T d2ryaw;                       /* '<S196>/d2r yaw' */
  real_T Derivative1[3];               /* '<S196>/Derivative1' */
  real_T EtadotSwitch[3];              /* '<S4>/Etadot Switch' */
  real_T etadot_surge;                 /* '<S4>/etadot_surge' */
  real_T etadot_sway;                  /* '<S4>/etadot_sway' */
  real_T etadot_yaw;                   /* '<S4>/etadot_yaw' */
  real_T EtaSwitch[3];                 /* '<S4>/Eta Switch' */
  real_T eta_surge;                    /* '<S4>/eta_surge' */
  real_T eta_sway;                     /* '<S4>/eta_sway' */
  real_T eta_yaw;                      /* '<S4>/eta_yaw' */
  real_T QTMIn8;                       /* '<S196>/QTM In8' */
  real_T d2rroll;                      /* '<S196>/d2r roll' */
  real_T QTMIn7;                       /* '<S196>/QTM In7' */
  real_T d2rpitch;                     /* '<S196>/d2r pitch' */
  real_T sintheta[3];                  /* '<S197>/sin(theta)' */
  real_T costheta[3];                  /* '<S197>/cos(theta)' */
  real_T R11;                          /* '<S197>/R11' */
  real_T R21;                          /* '<S197>/R21 ' */
  real_T R31;                          /* '<S197>/R31 ' */
  real_T R12;                          /* '<S197>/R12' */
  real_T R22;                          /* '<S197>/R22' */
  real_T R32;                          /* '<S197>/R32' */
  real_T R13;                          /* '<S197>/R13' */
  real_T R23;                          /* '<S197>/R23' */
  real_T R33;                          /* '<S197>/R33' */
  real_T Reshape9x13x3[9];             /* '<S197>/Reshape 9x1->3x3' */
  real_T MatrixConcatenate2[36];       /* '<S196>/Matrix Concatenate2' */
  real_T QTMIn5;                       /* '<S196>/QTM In5' */
  real_T mm2mz;                        /* '<S196>/mm2m z' */
  real_T Derivative[6];                /* '<S196>/Derivative' */
  real_T Product[6];                   /* '<S196>/Product' */
  real_T NuSwitch[3];                  /* '<S4>/Nu Switch' */
  real_T nu_surge;                     /* '<S4>/nu_surge' */
  real_T nu_sway;                      /* '<S4>/nu_sway' */
  real_T nu_yaw;                       /* '<S4>/nu_yaw' */
  real_T eta_dDPN;                     /* '<S110>/eta_d DP N' */
  real_T eta_dDPE;                     /* '<S110>/eta_d DP E' */
  real_T Gain1;                        /* '<S195>/Gain1' */
  real_T eta_dDPPsi;                   /* '<S110>/eta_d DP Psi' */
  real_T q_x_0;                        /* '<S102>/q_x_0' */
  real_T q_y_0;                        /* '<S102>/q_y_0' */
  real_T Integrator[2];                /* '<S50>/Integrator' */
  real_T x_2x_1;                       /* '<S184>/x_2 - x_1' */
  real_T y_2y_1;                       /* '<S184>/y_2 - y_1' */
  real_T TmpHiddenBufferAtProductInport2[2];/* 'synthesized block' */
  real_T Product_l[2];                 /* '<S179>/Product' */
  real_T s_0;                          /* '<S50>/s_0' */
  real_T Integrator1;                  /* '<S50>/Integrator1' */
  real_T Product2;                     /* '<S173>/Product2' */
  real_T sins;                         /* '<S173>/sin(s)' */
  real_T Product_b;                    /* '<S173>/Product' */
  real_T Gain;                         /* '<S173>/Gain' */
  real_T coss;                         /* '<S173>/cos(s)' */
  real_T Product1;                     /* '<S173>/Product1' */
  real_T TmpHiddenBufferAtProductInpor_k[2];/* 'synthesized block' */
  real_T Subtract;                     /* '<S179>/Subtract' */
  real_T Product1_k[2];                /* '<S179>/Product1' */
  real_T Add[2];                       /* '<S179>/Add' */
  real_T TrigonometricFunction;        /* '<S116>/Trigonometric Function' */
  real_T Gain_l;                       /* '<S121>/Gain' */
  real_T Saturation;                   /* '<S119>/Saturation' */
  real_T Sign;                         /* '<S119>/Sign' */
  real_T Gain_g;                       /* '<S119>/Gain' */
  real_T Sum1;                         /* '<S119>/Sum1' */
  real_T MathFunction;                 /* '<S119>/Math Function' */
  real_T Sum;                          /* '<S119>/Sum' */
  real_T Gain1_o;                      /* '<S120>/Gain1' */
  real_T Gain_i;                       /* '<S154>/Gain' */
  real_T Saturation_k;                 /* '<S150>/Saturation' */
  real_T Sign_o;                       /* '<S150>/Sign' */
  real_T Gain_h;                       /* '<S150>/Gain' */
  real_T Sum1_o;                       /* '<S150>/Sum1' */
  real_T MathFunction_g;               /* '<S150>/Math Function' */
  real_T Sum_h;                        /* '<S150>/Sum' */
  real_T Gain1_f;                      /* '<S153>/Gain1' */
  real_T MathFunction_d[4];            /* '<S160>/Math Function' */
  real_T x_2x_1_p;                     /* '<S183>/x_2 - x_1' */
  real_T x_2x_1s;                      /* '<S183>/(x_2 - x_1) * s' */
  real_T x_2x_1sx_1;                   /* '<S183>/(x_2 - x_1) * s + x_1' */
  real_T y_2y_1_g;                     /* '<S183>/y_2 - y_1' */
  real_T y_2y_1s;                      /* '<S183>/(y_2 - y_1) * s' */
  real_T y_2y_1sy_1;                   /* '<S183>/(y_2 - y_1) * s + y_1' */
  real_T p_d1a[2];                     /* '<S178>/p_d1 *a' */
  real_T Product2_j;                   /* '<S172>/Product2' */
  real_T coss_p;                       /* '<S172>/cos(s)' */
  real_T Product_la;                   /* '<S172>/Product' */
  real_T Add_i;                        /* '<S172>/Add' */
  real_T sins_f;                       /* '<S172>/sin(s)' */
  real_T Product1_f;                   /* '<S172>/Product1' */
  real_T Add1;                         /* '<S172>/Add1' */
  real_T a;                            /* '<S178>/1 - a' */
  real_T p_d21a[2];                    /* '<S178>/p_d2 * (1- a )' */
  real_T Add_m[2];                     /* '<S178>/Add' */
  real_T Switch;                       /* '<S187>/Switch' */
  real_T Switch2;                      /* '<S187>/Switch2' */
  real_T Switch_b;                     /* '<S188>/Switch' */
  real_T Switch2_b;                    /* '<S188>/Switch2' */
  real_T qp_d[2];                      /* '<S127>/q - p_d' */
  real_T epsilon[2];                   /* '<S127>/epsilon' */
  real_T MultiportSelector;            /* '<S127>/Multiport Selector' */
  real_T TrigonometricFunction_e;      /* '<S144>/Trigonometric Function' */
  real_T Gain_j;                       /* '<S156>/Gain' */
  real_T Saturation_n;                 /* '<S151>/Saturation' */
  real_T Sign_p;                       /* '<S151>/Sign' */
  real_T Gain_f;                       /* '<S151>/Gain' */
  real_T Sum1_n;                       /* '<S151>/Sum1' */
  real_T MathFunction_b;               /* '<S151>/Math Function' */
  real_T Sum_g;                        /* '<S151>/Sum' */
  real_T Gain1_o3;                     /* '<S155>/Gain1' */
  real_T Subtract_j;                   /* '<S144>/Subtract' */
  real_T Gain_c;                       /* '<S158>/Gain' */
  real_T Saturation_kb;                /* '<S152>/Saturation' */
  real_T Sign_k;                       /* '<S152>/Sign' */
  real_T Gain_fb;                      /* '<S152>/Gain' */
  real_T Sum1_i;                       /* '<S152>/Sum1' */
  real_T MathFunction_a;               /* '<S152>/Math Function' */
  real_T Sum_p;                        /* '<S152>/Sum' */
  real_T Gain1_d;                      /* '<S157>/Gain1' */
  real_T VectorConcatenate[3];         /* '<S122>/Vector Concatenate' */
  real_T q_x;                          /* '<S2>/q_x' */
  real_T q_y;                          /* '<S2>/q_y' */
  real_T psi_los;                      /* '<S2>/psi_los' */
  real_T pathx_d;                      /* '<S2>/path x_d' */
  real_T pathy_d;                      /* '<S2>/path y_d' */
  real_T pathpsi_d;                    /* '<S2>/path psi_d' */
  real_T MathFunction_i[2];            /* '<S186>/Math Function' */
  real_T Product_j;                    /* '<S185>/Product' */
  real_T sqrt_j;                       /* '<S185>/sqrt' */
  real_T Product_jd;                   /* '<S182>/Product' */
  real_T MathFunction_at[2];           /* '<S177>/Math Function' */
  real_T Product_o;                    /* '<S176>/Product' */
  real_T sqrt_f;                       /* '<S176>/sqrt' */
  real_T Subtract_h;                   /* '<S182>/Subtract' */
  real_T Product1_j;                   /* '<S182>/Product1' */
  real_T Add_p;                        /* '<S182>/Add' */
  real_T Divide;                       /* '<S189>/Divide' */
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
  real_T Saturation_b;                 /* '<S14>/Saturation' */
  real_T Sign_g;                       /* '<S14>/Sign' */
  real_T Gain_gl;                      /* '<S14>/Gain' */
  real_T Sum1_m;                       /* '<S14>/Sum1' */
  real_T MathFunction_al;              /* '<S14>/Math Function' */
  real_T Sum_a;                        /* '<S14>/Sum' */
  real_T regulationerror[3];           /* '<S10>/Sum2' */
  real_T Saturation_a;                 /* '<S13>/Saturation' */
  real_T Sign_i;                       /* '<S13>/Sign' */
  real_T Gain_m;                       /* '<S13>/Gain' */
  real_T Sum1_k;                       /* '<S13>/Sum1' */
  real_T MathFunction_gf;              /* '<S13>/Math Function' */
  real_T Sum_m;                        /* '<S13>/Sum' */
  real_T Row1;                         /* '<S12>/Row1' */
  real_T Row2;                         /* '<S12>/Row2' */
  real_T Row3;                         /* '<S12>/Row3' */
  real_T TmpHiddenBufferAtKpInport1[3];/* '<S10>/Transposed rotation  matrix in yaw1' */
  real_T Kp[3];                        /* '<S10>/Kp' */
  real_T K_p_surge_scale;              /* '<S10>/K_p_surge_scale' */
  real_T K_p_sway_scale;               /* '<S10>/K_p_sway_scale' */
  real_T K_p_yaw_scale;                /* '<S10>/K_p_yaw_scale' */
  real_T Integrator_f[3];              /* '<S10>/Integrator' */
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
  real_T Sum1_p[3];                    /* '<S10>/Sum1' */
  real_T Product_n[5];                 /* '<S16>/Product' */
  real_T DeadZone;                     /* '<S17>/Dead Zone' */
  real_T f_10;                         /* '<S17>/f_1 < 0' */
  real_T f_10_l;                       /* '<S17>/f_1 > 0' */
  real_T MultiportSwitch;              /* '<S17>/Multiport Switch' */
  real_T DeadZone_l;                   /* '<S18>/Dead Zone' */
  real_T f_20;                         /* '<S18>/f_2 < 0' */
  real_T f_20_h;                       /* '<S18>/f_2 > 0' */
  real_T MultiportSwitch_o;            /* '<S18>/Multiport Switch' */
  real_T DeadZone_i;                   /* '<S19>/Dead Zone' */
  real_T f_30;                         /* '<S19>/f_3 < 0' */
  real_T f_30_i;                       /* '<S19>/f_3 > 0' */
  real_T MultiportSwitch_n;            /* '<S19>/Multiport Switch' */
  real_T DeadZone_ly;                  /* '<S20>/Dead Zone' */
  real_T f_40;                         /* '<S20>/f_4 < 0' */
  real_T f_40_f;                       /* '<S20>/f_4 > 0' */
  real_T MultiportSwitch_o0;           /* '<S20>/Multiport Switch' */
  real_T DeadZone_g;                   /* '<S21>/Dead Zone' */
  real_T f_50;                         /* '<S21>/f_5 < 0' */
  real_T f_50_o;                       /* '<S21>/f_5 > 0' */
  real_T MultiportSwitch_ng;           /* '<S21>/Multiport Switch' */
  real_T Saturation_kt[5];             /* '<S6>/Saturation' */
  real_T l_x1_l;                       /* '<S100>/-l_x1' */
  real_T l_y2_m;                       /* '<S100>/-l_y2' */
  real_T l_x2_p;                       /* '<S100>/-l_x2' */
  real_T x5_n[15];                     /* '<S100>/3x5' */
  real_T Pseudoinverse_c[15];          /* '<S79>/Pseudoinverse' */
  real_T R11_a;                        /* '<S47>/R11' */
  real_T R21_n;                        /* '<S47>/R21' */
  real_T R12_c;                        /* '<S47>/R12' */
  real_T R22_l;                        /* '<S47>/R22' */
  real_T Rpsi[9];                      /* '<S47>/R(psi)' */
  real_T MathFunction_l[9];            /* '<S48>/Math Function' */
  real_T Rpsi_b[9];                    /* '<S46>/R(psi)' */
  real_T Gain_p;                       /* '<S74>/Gain' */
  real_T Saturation_bi;                /* '<S72>/Saturation' */
  real_T Sign_h;                       /* '<S72>/Sign' */
  real_T Gain_hl;                      /* '<S72>/Gain' */
  real_T Sum1_iw;                      /* '<S72>/Sum1' */
  real_T MathFunction_be;              /* '<S72>/Math Function' */
  real_T Sum_l;                        /* '<S72>/Sum' */
  real_T Gain1_oh;                     /* '<S73>/Gain1' */
  real_T Subtract_k[3];                /* '<S41>/Subtract' */
  real_T Gain_gi;                      /* '<S77>/Gain' */
  real_T Saturation_kg;                /* '<S75>/Saturation' */
  real_T Sign_ge;                      /* '<S75>/Sign' */
  real_T Gain_e;                       /* '<S75>/Gain' */
  real_T Sum1_a;                       /* '<S75>/Sum1' */
  real_T MathFunction_e;               /* '<S75>/Math Function' */
  real_T Sum_f;                        /* '<S75>/Sum' */
  real_T Gain1_b;                      /* '<S76>/Gain1' */
  real_T TmpHiddenBufferAtProductInport3[3];/* 'synthesized block' */
  real_T Product_bj[3];                /* '<S67>/Product' */
  real_T Rpsi_m[9];                    /* '<S45>/R(psi)' */
  real_T zeta[3];                      /* '<S7>/zeta' */
  real_T Product1_o[3];                /* '<S67>/Product1' */
  real_T Rpsi_k[9];                    /* '<S44>/R(psi)' */
  real_T f_qx;                         /* '<S129>/f_qx' */
  real_T f_qy;                         /* '<S129>/f_qy' */
  real_T TmpHiddenBufferAtProductInport1[2];/* 'synthesized block' */
  real_T Product_p[2];                 /* '<S129>/Product' */
  real_T Delta2;                       /* '<S145>/Delta^2' */
  real_T epsilon_n2;                   /* '<S145>/epsilon_n^2' */
  real_T Add_f;                        /* '<S145>/Add' */
  real_T Divide_b;                     /* '<S145>/Divide' */
  real_T MultiportSelector1[2];        /* '<S127>/Multiport Selector1' */
  real_T Product_f[2];                 /* '<S145>/Product' */
  real_T u[2];                         /* '<S145>/-1' */
  real_T VectorConcatenate_a[3];       /* '<S54>/Vector Concatenate' */
  real_T Product_m[2];                 /* '<S181>/Product' */
  real_T Product2_o;                   /* '<S175>/Product2' */
  real_T sins3;                        /* '<S175>/sin(s)3' */
  real_T MathFunction_p;               /* '<S175>/Math Function' */
  real_T Product_d;                    /* '<S175>/Product' */
  real_T coss3;                        /* '<S175>/cos(s)3' */
  real_T Product1_fw;                  /* '<S175>/Product1' */
  real_T Gain_mw;                      /* '<S175>/Gain' */
  real_T Subtract_o;                   /* '<S181>/Subtract' */
  real_T Product1_i[2];                /* '<S181>/Product1' */
  real_T Add_e[2];                     /* '<S181>/Add' */
  real_T x_dsy_ds2;                    /* '<S117>/x_d^s * y_d^s^2' */
  real_T x_ds2y_ds;                    /* '<S117>/x_d^s^2 * y_d^s' */
  real_T x_dsy_ds2x_ds2y_ds;           /* '<S117>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
  real_T x_ds2;                        /* '<S117>/( x_d^s )^2' */
  real_T y_ds2;                        /* '<S117>/( y_d^s )^2' */
  real_T x_ds2y_ds2;                   /* '<S117>/( x_d^s )^2 + ( y_d^s )^2' */
  real_T Divide_h;                     /* '<S117>/Divide' */
  real_T Delta2_b;                     /* '<S148>/Delta^2' */
  real_T epsilon_n2_j;                 /* '<S148>/epsilon_n^2' */
  real_T Add_a;                        /* '<S148>/Add' */
  real_T Divide_p;                     /* '<S148>/Divide' */
  real_T MathFunction_k[4];            /* '<S164>/Math Function' */
  real_T Product_lx[2];                /* '<S166>/Product' */
  real_T Product1_h[2];                /* '<S166>/Product1' */
  real_T Subtract1[2];                 /* '<S166>/Subtract1' */
  real_T MultiportSelector2;           /* '<S127>/Multiport Selector2' */
  real_T Product_bn;                   /* '<S148>/Product' */
  real_T Subtract_g;                   /* '<S148>/Subtract' */
  real_T epsilon_n2_f;                 /* '<S133>/epsilon_n^2' */
  real_T Delta2_d;                     /* '<S133>/Delta^2' */
  real_T Add_h;                        /* '<S133>/Add' */
  real_T sqrt_i;                       /* '<S133>/sqrt' */
  real_T Divide_c;                     /* '<S133>/Divide' */
  real_T Product_e;                    /* '<S133>/Product' */
  real_T MathFunction_pj[2];           /* '<S140>/Math Function' */
  real_T Divide_i[2];                  /* '<S137>/Divide' */
  real_T Subtract_m[2];                /* '<S125>/Subtract' */
  real_T Product_f1;                   /* '<S137>/Product' */
  real_T Gain_cx;                      /* '<S137>/Gain' */
  real_T Subtract_f;                   /* '<S133>/Subtract' */
  real_T VectorConcatenate_m[3];       /* '<S60>/Vector Concatenate' */
  real_T Add_fj[3];                    /* '<S53>/Add' */
  real_T Product_a[3];                 /* '<S52>/Product' */
  real_T Subtract_c[3];                /* '<S52>/Subtract' */
  real_T Product2_j4[3];               /* '<S67>/Product2' */
  real_T Sum_a0[3];                    /* '<S67>/Sum' */
  real_T X_u;                          /* '<S69>/-X_u' */
  real_T Y_v;                          /* '<S69>/-Y_v' */
  real_T N_v;                          /* '<S69>/-N_v' */
  real_T Y_vr;                         /* '<S69>/-Y_vr' */
  real_T N_r;                          /* '<S69>/-N_r' */
  real_T LinearDampningmatrix[9];      /* '<S69>/Linear Dampning matrix' */
  real_T Product1_kq[3];               /* '<S66>/Product1' */
  real_T M_11;                         /* '<S68>/M_11' */
  real_T M_22;                         /* '<S68>/M_22' */
  real_T mx_g;                         /* '<S68>/m x_g' */
  real_T M_32;                         /* '<S68>/M_32' */
  real_T M_23;                         /* '<S68>/M_23' */
  real_T M_33;                         /* '<S68>/M_33' */
  real_T x3[9];                        /* '<S68>/3x3' */
  real_T TrigonometricFunction1;       /* '<S130>/Trigonometric Function1' */
  real_T Gain_ga;                      /* '<S130>/Gain' */
  real_T Product1_n[2];                /* '<S130>/Product1' */
  real_T TrigonometricFunction_n;      /* '<S130>/Trigonometric Function' */
  real_T Product2_c[2];                /* '<S130>/Product2' */
  real_T MatrixConcatenate[4];         /* '<S130>/Matrix Concatenate' */
  real_T Product_i[4];                 /* '<S130>/Product' */
  real_T MathFunction_iq[2];           /* '<S58>/Math Function' */
  real_T Product2_p;                   /* '<S146>/Product2' */
  real_T MathFunction_n[2];            /* '<S146>/Math Function' */
  real_T Product3[4];                  /* '<S146>/Product3' */
  real_T Product4[4];                  /* '<S146>/Product4' */
  real_T u_g[4];                       /* '<S146>/2' */
  real_T Delta2_d4;                    /* '<S146>/Delta^2' */
  real_T epsilon_n2_o;                 /* '<S146>/epsilon_n^2' */
  real_T Add_d;                        /* '<S146>/Add' */
  real_T u_n;                          /* '<S146>/( )^2' */
  real_T Divide_hf[4];                 /* '<S146>/Divide' */
  real_T Product1_c[4];                /* '<S146>/Product1' */
  real_T Divide1[4];                   /* '<S146>/Divide1' */
  real_T Subtract_ju[4];               /* '<S146>/Subtract' */
  real_T MathFunction_o[4];            /* '<S59>/Math Function' */
  real_T Product_g[2];                 /* '<S55>/Product' */
  real_T Product1_d[2];                /* '<S55>/Product1' */
  real_T Add_ax[2];                    /* '<S55>/Add' */
  real_T MatrixConcatenate_j[6];       /* '<S55>/Matrix Concatenate' */
  real_T Product_a5[2];                /* '<S147>/Product' */
  real_T u_k[2];                       /* '<S147>/2' */
  real_T Delta2_m;                     /* '<S147>/Delta^2' */
  real_T epsilon_n2_b;                 /* '<S147>/epsilon_n^2' */
  real_T Add_dw;                       /* '<S147>/Add' */
  real_T u_b;                          /* '<S147>/( )^2' */
  real_T Divide_f[2];                  /* '<S147>/Divide' */
  real_T Product1_fo[4];               /* '<S165>/Product1' */
  real_T MultiportSelector3[2];        /* '<S127>/Multiport Selector3' */
  real_T Product1_g[2];                /* '<S147>/Product1' */
  real_T Divide1_l[2];                 /* '<S147>/Divide1' */
  real_T Subtract_fn[2];               /* '<S147>/Subtract' */
  real_T Product_ae[2];                /* '<S61>/Product' */
  real_T Product1_d4[2];               /* '<S134>/Product1' */
  real_T epsilon_n2_n;                 /* '<S134>/epsilon_n^2' */
  real_T Delta2_a;                     /* '<S134>/Delta^2' */
  real_T Add_c;                        /* '<S134>/Add' */
  real_T u2;                           /* '<S134>/^3//2' */
  real_T Divide_j[2];                  /* '<S134>/Divide' */
  real_T Product_lao[2];               /* '<S134>/Product' */
  real_T MathFunction_m[2];            /* '<S141>/Math Function' */
  real_T Divide_e[2];                  /* '<S138>/Divide' */
  real_T Product_gv[2];                /* '<S138>/Product' */
  real_T Gain_mb[2];                   /* '<S138>/Gain' */
  real_T Sum_mp[2];                    /* '<S134>/Sum' */
  real_T Product1_a[2];                /* '<S61>/Product1' */
  real_T Add_b[2];                     /* '<S61>/Add' */
  real_T MatrixConcatenate_n[6];       /* '<S61>/Matrix Concatenate' */
  real_T Add_ac[6];                    /* '<S103>/Add' */
  real_T omega_q[2];                   /* '<S50>/omega_q' */
  real_T Add_ic[2];                    /* '<S50>/Add' */
  real_T Product_gq[3];                /* '<S51>/Product' */
  real_T TrigonometricFunction1_k;     /* '<S131>/Trigonometric Function1' */
  real_T Gain_l1;                      /* '<S131>/Gain' */
  real_T Product1_i1;                  /* '<S131>/Product1' */
  real_T TrigonometricFunction_p;      /* '<S131>/Trigonometric Function' */
  real_T Product2_ok;                  /* '<S131>/Product2' */
  real_T TmpHiddenBufferAtProductInpor_n[2];/* 'synthesized block' */
  real_T Product_fr[2];                /* '<S131>/Product' */
  real_T Product_h;                    /* '<S56>/Product' */
  real_T Product1_os;                  /* '<S56>/Product1' */
  real_T VectorConcatenate_l[3];       /* '<S56>/Vector Concatenate' */
  real_T Product_jv[2];                /* '<S180>/Product' */
  real_T Product2_a;                   /* '<S174>/Product2' */
  real_T coss_pz;                      /* '<S174>/cos(s)' */
  real_T MathFunction_gs;              /* '<S174>/Math Function' */
  real_T Product_pa;                   /* '<S174>/Product' */
  real_T Gain_a;                       /* '<S174>/Gain' */
  real_T sins_p;                       /* '<S174>/sin(s)' */
  real_T Product1_jk;                  /* '<S174>/Product1' */
  real_T Gain1_c;                      /* '<S174>/Gain1' */
  real_T Subtract_fr;                  /* '<S180>/Subtract' */
  real_T Product1_if[2];               /* '<S180>/Product1' */
  real_T Add_ef[2];                    /* '<S180>/Add' */
  real_T x_dsy_ds3;                    /* '<S118>/x_d^s * y_d^s^3 ' */
  real_T x_ds3y_ds;                    /* '<S118>/x_d^s^3 * y_d^s' */
  real_T x_dsy_ds3x_ds3y_ds;           /* '<S118>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
  real_T Product1_hm;                  /* '<S118>/Product1' */
  real_T x_dsx_ds2;                    /* '<S118>/x_d^s * x_d^s^2' */
  real_T y_dsy_ds2;                    /* '<S118>/y_d^s * y_d^s^2' */
  real_T x_dsx_ds2x_ds3y_ds;           /* '<S118>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
  real_T u_d;                          /* '<S118>/+ 2' */
  real_T Product2_g;                   /* '<S118>/Product2' */
  real_T Subtract_jg;                  /* '<S118>/Subtract' */
  real_T x_ds2y_ds22;                  /* '<S118>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
  real_T Divide_ph;                    /* '<S118>/Divide' */
  real_T epsilon_ns2;                  /* '<S149>/(epsilon_n^s)^2' */
  real_T Product_nc;                   /* '<S149>/Product' */
  real_T u_f;                          /* '<S149>/2' */
  real_T Delta2_p;                     /* '<S149>/Delta^2' */
  real_T epsilon_n2_ji;                /* '<S149>/epsilon_n^2' */
  real_T Add_di;                       /* '<S149>/Add' */
  real_T u_bl;                         /* '<S149>/( )^2' */
  real_T Divide_cz;                    /* '<S149>/Divide' */
  real_T MathFunction_ox[4];           /* '<S163>/Math Function' */
  real_T Product_fb[4];                /* '<S167>/Product' */
  real_T Add_au[4];                    /* '<S167>/Add' */
  real_T Product1_l[2];                /* '<S167>/Product1' */
  real_T Product2_h[2];                /* '<S167>/Product2' */
  real_T u_j[2];                       /* '<S167>/2' */
  real_T Product3_f[2];                /* '<S167>/Product3' */
  real_T Sum_o[2];                     /* '<S167>/Sum' */
  real_T Gain_lk[2];                   /* '<S167>/Gain' */
  real_T MultiportSelector4;           /* '<S127>/Multiport Selector4' */
  real_T Product1_jb;                  /* '<S149>/Product1' */
  real_T Divide1_e;                    /* '<S149>/Divide1' */
  real_T Sum_hf;                       /* '<S149>/Sum' */
  real_T Product_av;                   /* '<S62>/Product' */
  real_T MathFunction_f[2];            /* '<S192>/Math Function' */
  real_T Product1_cs;                  /* '<S190>/Product1' */
  real_T p_ds3;                        /* '<S190>/|p_d^s|^3' */
  real_T Divide_m;                     /* '<S190>/Divide' */
  real_T Product_nw;                   /* '<S190>/Product' */
  real_T Gain_jk;                      /* '<S190>/Gain' */
  real_T epsilon_n2_bc;                /* '<S135>/epsilon_n^2' */
  real_T Delta2_c;                     /* '<S135>/Delta^2' */
  real_T Add_n;                        /* '<S135>/Add' */
  real_T MathFunction_atw;             /* '<S135>/Math Function' */
  real_T Divide_ey;                    /* '<S135>/Divide' */
  real_T Product1_hq;                  /* '<S135>/Product1' */
  real_T Product2_ha;                  /* '<S135>/Product2' */
  real_T u2_f;                         /* '<S135>/^3//2' */
  real_T Divide1_k;                    /* '<S135>/Divide1' */
  real_T Product3_n;                   /* '<S135>/Product3' */
  real_T Product1_p;                   /* '<S139>/Product1' */
  real_T MathFunction_g4[2];           /* '<S143>/Math Function' */
  real_T Divide2[2];                   /* '<S139>/Divide2' */
  real_T MathFunction_j[2];            /* '<S142>/Math Function' */
  real_T Product2_aa[2];               /* '<S139>/Product2' */
  real_T MathFunction_gc;              /* '<S139>/Math Function' */
  real_T Divide1_m[2];                 /* '<S139>/Divide1' */
  real_T Subtract1_f[2];               /* '<S139>/Subtract1' */
  real_T Product_c;                    /* '<S139>/Product' */
  real_T Subtract_gr;                  /* '<S139>/Subtract' */
  real_T Sum_ou;                       /* '<S135>/Sum' */
  real_T Product1_gt;                  /* '<S62>/Product1' */
  real_T VectorConcatenate_d[3];       /* '<S62>/Vector Concatenate' */
  real_T Add1_b[3];                    /* '<S104>/Add1' */
  real_T Product1_km[3];               /* '<S51>/Product1' */
  real_T TrigonometricFunction_m;      /* '<S132>/Trigonometric Function' */
  real_T TrigonometricFunction1_j;     /* '<S132>/Trigonometric Function1' */
  real_T Derivative_d;                 /* '<S115>/Derivative' */
  real_T Product_ji[2];                /* '<S132>/Product' */
  real_T VectorConcatenate_p[3];       /* '<S57>/Vector Concatenate' */
  real_T epsilon_n2_nl;                /* '<S136>/epsilon_n^2' */
  real_T Delta2_f;                     /* '<S136>/Delta^2' */
  real_T Add_fq;                       /* '<S136>/Add' */
  real_T sqrt_a;                       /* '<S136>/sqrt' */
  real_T Divide_d;                     /* '<S136>/Divide' */
  real_T Divide_g;                     /* '<S191>/Divide' */
  real_T Product_h4;                   /* '<S136>/Product' */
  real_T VectorConcatenate_dx[3];      /* '<S63>/Vector Concatenate' */
  real_T Add_em[3];                    /* '<S105>/Add' */
  real_T Sum_b[3];                     /* '<S51>/Sum' */
  real_T Product_l0[3];                /* '<S65>/Product' */
  real_T S12;                          /* '<S64>/S12' */
  real_T Sr[9];                        /* '<S64>/S(r)' */
  real_T Product1_m[3];                /* '<S65>/Product1' */
  real_T Subtract_p[3];                /* '<S65>/Subtract' */
  real_T Gain_mx[3];                   /* '<S65>/Gain' */
  real_T Sum_hl[3];                    /* '<S40>/Sum' */
  real_T Product_bs[5];                /* '<S79>/Product' */
  real_T DeadZone_p;                   /* '<S80>/Dead Zone' */
  real_T f_10_j;                       /* '<S80>/f_1 < 0' */
  real_T f_10_e;                       /* '<S80>/f_1 > 0' */
  real_T MultiportSwitch_f;            /* '<S80>/Multiport Switch' */
  real_T DeadZone_c;                   /* '<S81>/Dead Zone' */
  real_T f_20_p;                       /* '<S81>/f_2 < 0' */
  real_T f_20_l;                       /* '<S81>/f_2 > 0' */
  real_T MultiportSwitch_fh;           /* '<S81>/Multiport Switch' */
  real_T DeadZone_h;                   /* '<S82>/Dead Zone' */
  real_T f_30_d;                       /* '<S82>/f_3 < 0' */
  real_T f_30_h;                       /* '<S82>/f_3 > 0' */
  real_T MultiportSwitch_l;            /* '<S82>/Multiport Switch' */
  real_T DeadZone_pp;                  /* '<S83>/Dead Zone' */
  real_T f_40_fz;                      /* '<S83>/f_4 < 0' */
  real_T f_40_n;                       /* '<S83>/f_4 > 0' */
  real_T MultiportSwitch_e;            /* '<S83>/Multiport Switch' */
  real_T DeadZone_pa;                  /* '<S84>/Dead Zone' */
  real_T f_50_n;                       /* '<S84>/f_5 < 0' */
  real_T f_50_g;                       /* '<S84>/f_5 > 0' */
  real_T MultiportSwitch_lr;           /* '<S84>/Multiport Switch' */
  real_T ThrustersettingSwitch[7];     /* '<S1>/Thruster setting Switch' */
  real_T Saturation_f[7];              /* '<S1>/Saturation' */
  real_T l_x1_e;                       /* '<S109>/-l_x1' */
  real_T l_y2_g;                       /* '<S109>/-l_y2' */
  real_T l_x2_a;                       /* '<S109>/-l_x2' */
  real_T x5_a[15];                     /* '<S109>/3x5' */
  real_T u_1tof_1;                     /* '<S108>/u_1 to f_1' */
  real_T u_2tof_2;                     /* '<S108>/u_2 to f_2' */
  real_T u_3tof_3;                     /* '<S108>/u_3 to f_3' */
  real_T u_4tof_4;                     /* '<S108>/u_4 to f_4' */
  real_T u_5tof_5;                     /* '<S108>/u_5 to f_5' */
  real_T TmpHiddenBufferAtProductInpor_f[5];/* 'synthesized block' */
  real_T Product_fy[3];                /* '<S107>/Product' */
  real_T tauSwitch[3];                 /* '<S1>/tau Switch' */
  real_T TmpHiddenBufferAtToFileInport1[36];/* 'synthesized block' */
  real_T x2[4];                        /* '<S42>/2x2' */
  real_T Product_cb[3];                /* '<S43>/Product' */
  real_T MatrixConcatenate_k[6];       /* '<S122>/Matrix Concatenate' */
  real_T MathFunction_an[6];           /* '<S101>/Math Function' */
  real_T Product2_k[2];                /* '<S50>/Product2' */
  real_T Product3_g[2];                /* '<S50>/Product3' */
  real_T Subtract_o2[2];               /* '<S50>/Subtract' */
  real_T Product1_as[2];               /* '<S50>/Product1' */
  real_T dotomega_q[2];                /* '<S50>/dot omega_q' */
  real_T VectorConcatenate1[3];        /* '<S122>/Vector Concatenate1' */
  real_T SITzAI0;                      /* '<S3>/SIT zAI0' */
  real_T BatteryBowThruster;           /* '<S3>/Battery Bow Thruster' */
  real_T SITzAI1;                      /* '<S3>/SIT zAI1' */
  real_T BatteryServo;                 /* '<S3>/Battery Servo' */
  real_T SITzAI2;                      /* '<S3>/SIT zAI2' */
  real_T BatteryMain;                  /* '<S3>/Battery Main' */
  real_T QTMIn1FPS;                    /* '<S196>/QTM In1 FPS' */
  real_T Saturation_f5;                /* '<S200>/Saturation' */
  real_T Saturation1;                  /* '<S200>/Saturation1' */
  real_T Saturation2;                  /* '<S200>/Saturation2' */
  real_T planttau_surge;               /* '<S200>/plant tau_surge' */
  real_T planttau_sway;                /* '<S200>/plant tau_sway' */
  real_T planttau_yaw;                 /* '<S200>/plant tau_yaw' */
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
  real_T psi_los_l;                    /* '<Root>/psi_los' */
  real_T psi_plot[3];                  /* '<Root>/psi_plot' */
  real_T q_x_f;                        /* '<Root>/q_x' */
  real_T q_y_j;                        /* '<Root>/q_y' */
  real_T x_plot[3];                    /* '<Root>/x_plot' */
  real_T y_plot[3];                    /* '<Root>/y_plot' */
  real_T N_r_l;                        /* '<S207>/-N_r' */
  real_T N_v_g;                        /* '<S207>/-N_v' */
  real_T X_u_k;                        /* '<S207>/-X_u' */
  real_T Y_v_h;                        /* '<S207>/-Y_v' */
  real_T Y_vr_i;                       /* '<S207>/-Y_vr' */
  real_T LinearDampningmatrix_f[9];    /* '<S207>/Linear Dampning matrix' */
  real_T psi_0;                        /* '<S208>/psi_0' */
  real_T x_0;                          /* '<S208>/x_0' */
  real_T y_0;                          /* '<S208>/y_0' */
  real_T r_0;                          /* '<S209>/r_0' */
  real_T u_0;                          /* '<S209>/u_0' */
  real_T v_0;                          /* '<S209>/v_0' */
  real_T Integrator_m[3];              /* '<S206>/Integrator' */
  real_T Integrator1_m[3];             /* '<S206>/Integrator1' */
  real_T M_11_c;                       /* '<S210>/M_11' */
  real_T M_22_k;                       /* '<S210>/M_22' */
  real_T mx_g_c;                       /* '<S210>/m x_g' */
  real_T M_32_b;                       /* '<S210>/M_32' */
  real_T M_23_f;                       /* '<S210>/M_23' */
  real_T M_33_e;                       /* '<S210>/M_33' */
  real_T M[9];                         /* '<S210>/M' */
  real_T Inverse[9];                   /* '<S210>/Inverse' */
  real_T Product1_o4[3];               /* '<S206>/Product1' */
  real_T R11_m;                        /* '<S211>/R11' */
  real_T R21_h;                        /* '<S211>/R21' */
  real_T R12_d;                        /* '<S211>/R12' */
  real_T R22_le;                       /* '<S211>/R22' */
  real_T Rpsi_c[9];                    /* '<S211>/R(psi)' */
  real_T Product3_fn[3];               /* '<S206>/Product3' */
  real_T eta_surge_hil;                /* '<S199>/eta_surge_hil' */
  real_T eta_sway_hil;                 /* '<S199>/eta_sway_hil' */
  real_T eta_yaw_hil;                  /* '<S199>/eta_yaw_hil' */
  real_T etadot_surge_hil;             /* '<S199>/etadot_surge_hil' */
  real_T etadot_sway_hil;              /* '<S199>/etadot_sway_hil' */
  real_T etadot_yaw_hil;               /* '<S199>/etadot_yaw_hil' */
  real_T nu_surge_hil;                 /* '<S199>/nu_surge_hil' */
  real_T nu_sway_hil;                  /* '<S199>/nu_sway_hil' */
  real_T nu_yaw_hil;                   /* '<S199>/nu_yaw_hil' */
  real_T Sum_e[3];                     /* '<S206>/Sum' */
  real_T Product2_kw[3];               /* '<S206>/Product2' */
  real_T BT_D_Gain1;                   /* '<S201>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S201>/BT_D_Gain2' */
  real_T Add_af;                       /* '<S201>/Add' */
  real_T BT_L_Gain1;                   /* '<S201>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S201>/BT_L_Gain2' */
  real_T Neg;                          /* '<S201>/Neg' */
  real_T Sum1_nf;                      /* '<S201>/Sum1' */
  real_T Sum2;                         /* '<S201>/Sum2' */
  real_T Switch_j;                     /* '<S203>/Switch' */
  real_T Switch2_e;                    /* '<S203>/Switch2' */
  real_T Switch_i;                     /* '<S204>/Switch' */
  real_T Switch2_i;                    /* '<S204>/Switch2' */
  real_T Switch_e;                     /* '<S205>/Switch' */
  real_T Switch2_o;                    /* '<S205>/Switch2' */
  real_T Sign_c;                       /* '<S202>/Sign' */
  real_T PortVPS_X;                    /* '<S202>/Product1' */
  real_T PortVPS_X_l;                  /* '<S202>/-x' */
  real_T PortVSP_Y;                    /* '<S202>/Product2' */
  real_T PortVSP_Y_c;                  /* '<S202>/-y' */
  real_T StarboardVSP_X;               /* '<S202>/Product3' */
  real_T StarboardVSP_Y;               /* '<S202>/Product4' */
  real_T Servo1;                       /* '<S202>/Servo1' */
  real_T Servo2;                       /* '<S202>/Servo2' */
  real_T Servo3;                       /* '<S202>/Servo3' */
  real_T Servo4;                       /* '<S202>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S202>/VPS_Speed_Gain' */
  real_T Sum_bl;                       /* '<S202>/Sum' */
  real_T VSPSPort;                     /* '<S202>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S202>/VSPS Starboard' */
  real_T S12_j;                        /* '<S162>/S12' */
  real_T S_2psi_ds2[4];                /* '<S162>/S_2(psi_d^s^2)' */
  real_T S12_c;                        /* '<S161>/S12' */
  real_T S_2psi_ds[4];                 /* '<S161>/S_2(psi_d^s)' */
  real_T R11_k;                        /* '<S159>/R11' */
  real_T R21_o;                        /* '<S159>/R21' */
  real_T R12_h;                        /* '<S159>/R12' */
  real_T R22_c;                        /* '<S159>/R22' */
  real_T R_2psi_d[4];                  /* '<S159>/R_2(psi_d)' */
  uint16_T Gain_fm;                    /* '<S17>/Gain' */
  uint16_T Gain1_ce;                   /* '<S17>/Gain1' */
  uint16_T Sum_i;                      /* '<S17>/Sum' */
  uint16_T Gain_o;                     /* '<S18>/Gain' */
  uint16_T Gain1_e;                    /* '<S18>/Gain1' */
  uint16_T Sum_k;                      /* '<S18>/Sum' */
  uint16_T Gain_d;                     /* '<S19>/Gain' */
  uint16_T Gain1_fx;                   /* '<S19>/Gain1' */
  uint16_T Sum_mf;                     /* '<S19>/Sum' */
  uint16_T Gain_n;                     /* '<S20>/Gain' */
  uint16_T Gain1_i;                    /* '<S20>/Gain1' */
  uint16_T Sum_it;                     /* '<S20>/Sum' */
  uint16_T Gain_fd;                    /* '<S21>/Gain' */
  uint16_T Gain1_n;                    /* '<S21>/Gain1' */
  uint16_T Sum_e1;                     /* '<S21>/Sum' */
  uint16_T Gain_gb;                    /* '<S80>/Gain' */
  uint16_T Gain1_cn;                   /* '<S80>/Gain1' */
  uint16_T Sum_c;                      /* '<S80>/Sum' */
  uint16_T Gain_b;                     /* '<S81>/Gain' */
  uint16_T Gain1_cm;                   /* '<S81>/Gain1' */
  uint16_T Sum_m3;                     /* '<S81>/Sum' */
  uint16_T Gain_ef;                    /* '<S82>/Gain' */
  uint16_T Gain1_k;                    /* '<S82>/Gain1' */
  uint16_T Sum_d;                      /* '<S82>/Sum' */
  uint16_T Gain_nf;                    /* '<S83>/Gain' */
  uint16_T Gain1_h;                    /* '<S83>/Gain1' */
  uint16_T Sum_kv;                     /* '<S83>/Sum' */
  uint16_T Gain_nx;                    /* '<S84>/Gain' */
  uint16_T Gain1_cx;                   /* '<S84>/Gain1' */
  uint16_T Sum_hs;                     /* '<S84>/Sum' */
  uint8_T Compare;                     /* '<S22>/Compare' */
  uint8_T Compare_m;                   /* '<S24>/Compare' */
  uint8_T Compare_i;                   /* '<S23>/Compare' */
  uint8_T Compare_b;                   /* '<S25>/Compare' */
  uint8_T Compare_g;                   /* '<S26>/Compare' */
  uint8_T Compare_mz;                  /* '<S27>/Compare' */
  uint8_T Compare_gm;                  /* '<S28>/Compare' */
  uint8_T Compare_l;                   /* '<S30>/Compare' */
  uint8_T Compare_bs;                  /* '<S29>/Compare' */
  uint8_T Compare_j;                   /* '<S31>/Compare' */
  uint8_T Compare_je;                  /* '<S33>/Compare' */
  uint8_T Compare_h;                   /* '<S32>/Compare' */
  uint8_T Compare_l3;                  /* '<S34>/Compare' */
  uint8_T Compare_m1;                  /* '<S36>/Compare' */
  uint8_T Compare_d;                   /* '<S35>/Compare' */
  uint8_T Compare_p;                   /* '<S85>/Compare' */
  uint8_T Compare_ma;                  /* '<S87>/Compare' */
  uint8_T Compare_go;                  /* '<S86>/Compare' */
  uint8_T Compare_g1;                  /* '<S88>/Compare' */
  uint8_T Compare_jl;                  /* '<S89>/Compare' */
  uint8_T Compare_l1;                  /* '<S90>/Compare' */
  uint8_T Compare_jlz;                 /* '<S91>/Compare' */
  uint8_T Compare_g0;                  /* '<S93>/Compare' */
  uint8_T Compare_hr;                  /* '<S92>/Compare' */
  uint8_T Compare_a;                   /* '<S94>/Compare' */
  uint8_T Compare_gq;                  /* '<S96>/Compare' */
  uint8_T Compare_j1;                  /* '<S95>/Compare' */
  uint8_T Compare_c;                   /* '<S97>/Compare' */
  uint8_T Compare_f;                   /* '<S99>/Compare' */
  uint8_T Compare_js;                  /* '<S98>/Compare' */
  boolean_T LowerRelop1;               /* '<S187>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S187>/UpperRelop' */
  boolean_T LowerRelop1_l;             /* '<S188>/LowerRelop1' */
  boolean_T UpperRelop_e;              /* '<S188>/UpperRelop' */
  boolean_T LowerRelop1_e;             /* '<S203>/LowerRelop1' */
  boolean_T UpperRelop_p;              /* '<S203>/UpperRelop' */
  boolean_T LowerRelop1_h;             /* '<S204>/LowerRelop1' */
  boolean_T UpperRelop_o;              /* '<S204>/UpperRelop' */
  boolean_T LowerRelop1_i;             /* '<S205>/LowerRelop1' */
  boolean_T UpperRelop_l;              /* '<S205>/UpperRelop' */
} BlockIO_NLPID;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Pseudoinverse_X[15];          /* '<S16>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S16>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S16>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S16>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S16>/Pseudoinverse' */
  real_T Product_DWORK1;               /* '<S137>/Product' */
  real_T Product2_DWORK1[4];           /* '<S139>/Product2' */
  real_T Inverse_DWORK3[9];            /* '<S210>/Inverse' */
  real_T Inverse_DWORK4[9];            /* '<S210>/Inverse' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[3];
    real_T TimeStampB;
    real_T LastUAtTimeB[3];
  } Derivative1_RWORK;                 /* '<S196>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } Derivative_RWORK;                  /* '<S196>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_d;                /* '<S115>/Derivative' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<Root>/To File' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<S18>/Scope2' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_j;                    /* '<S81>/Scope2' */

  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<S133>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S133>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_c;                    /* '<S133>/Scope2' */

  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<S133>/Scope3' */

  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  int32_T Inverse_DWORK2[3];           /* '<S210>/Inverse' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S17>/Sum' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S50>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S50>/Integrator1' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<Root>/To File' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_k;                /* '<S206>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_o;               /* '<S206>/Integrator1' */

  int_T LinearSimulator_MODE;          /* '<S5>/Linear Simulator' */
  int_T CSE1_MODE;                     /* '<S5>/CSE1' */
  uint8_T SignalProbe_DWORK1[6];       /* '<Root>/SignalProbe' */
} D_Work_NLPID;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S50>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S50>/Integrator1' */
  real_T Integrator_CSTATE_m[3];       /* '<S10>/Integrator' */
  real_T zeta_CSTATE[3];               /* '<S7>/zeta' */
  real_T omega_q_CSTATE[2];            /* '<S50>/omega_q' */
  real_T Integrator_CSTATE_l[3];       /* '<S206>/Integrator' */
  real_T Integrator1_CSTATE_i[3];      /* '<S206>/Integrator1' */
} ContinuousStates_NLPID;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S50>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S50>/Integrator1' */
  real_T Integrator_CSTATE_m[3];       /* '<S10>/Integrator' */
  real_T zeta_CSTATE[3];               /* '<S7>/zeta' */
  real_T omega_q_CSTATE[2];            /* '<S50>/omega_q' */
  real_T Integrator_CSTATE_l[3];       /* '<S206>/Integrator' */
  real_T Integrator1_CSTATE_i[3];      /* '<S206>/Integrator1' */
} StateDerivatives_NLPID;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[2];      /* '<S50>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S50>/Integrator1' */
  boolean_T Integrator_CSTATE_m[3];    /* '<S10>/Integrator' */
  boolean_T zeta_CSTATE[3];            /* '<S7>/zeta' */
  boolean_T omega_q_CSTATE[2];         /* '<S50>/omega_q' */
  boolean_T Integrator_CSTATE_l[3];    /* '<S206>/Integrator' */
  boolean_T Integrator1_CSTATE_i[3];   /* '<S206>/Integrator1' */
} StateDisabled_NLPID;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S50>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S50>/Integrator1' */
  ZCSigState Integrator_Reset_ZCE_d;   /* '<S10>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_c;   /* '<S206>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE_o;  /* '<S206>/Integrator1' */
} PrevZCSigStates_NLPID;

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
   * '<S127>/Multiport Selector'
   * '<S127>/Multiport Selector1'
   * '<S127>/Multiport Selector2'
   * '<S127>/Multiport Selector3'
   * '<S127>/Multiport Selector4'
   */
  int32_T pooled1;
} ConstParam_NLPID;

/* Backward compatible GRT Identifiers */
#define rtB                            NLPID_B
#define BlockIO                        BlockIO_NLPID
#define rtX                            NLPID_X
#define ContinuousStates               ContinuousStates_NLPID
#define rtP                            NLPID_P
#define Parameters                     Parameters_NLPID
#define rtDWork                        NLPID_DWork
#define D_Work                         D_Work_NLPID
#define ConstParam                     ConstParam_NLPID
#define rtcP                           NLPID_ConstP
#define rtPrevZCSigState               NLPID_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_NLPID

/* Parameters (auto storage) */
struct Parameters_NLPID_ {
  real_T ControllerInputSelector_Value;/* Expression: 0
                                        * '<S4>/Controller Input Selector'
                                        */
  real_T QTMIn_P1;                     /* Expression: width
                                        * '<S196>/QTM In'
                                        */
  real_T QTMIn_P2;                     /* Expression: dtype
                                        * '<S196>/QTM In'
                                        */
  real_T QTMIn_P3;                     /* Expression: portnum
                                        * '<S196>/QTM In'
                                        */
  real_T QTMIn_P4;                     /* Expression: stime
                                        * '<S196>/QTM In'
                                        */
  real_T QTMIn_P5;                     /* Expression: stype
                                        * '<S196>/QTM In'
                                        */
  real_T QTMIn_P6;                     /* Expression: btype
                                        * '<S196>/QTM In'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S196>/QTM In2 Error'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S196>/QTM In9 Residual'
                                        */
  real_T QTMIn3_Gain;                  /* Expression: 1
                                        * '<S196>/QTM In3'
                                        */
  real_T mm2mx_Gain;                   /* Expression: 0.001
                                        * '<S196>/mm2m x'
                                        */
  real_T QTMIn4_Gain;                  /* Expression: 1
                                        * '<S196>/QTM In4'
                                        */
  real_T mm2my_Gain;                   /* Expression: 0.001
                                        * '<S196>/mm2m y'
                                        */
  real_T QTMIn6_Gain;                  /* Expression: 1
                                        * '<S196>/QTM In6'
                                        */
  real_T d2ryaw_Gain;                  /* Expression: pi/180
                                        * '<S196>/d2r yaw'
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
                                        * '<S196>/QTM In8'
                                        */
  real_T d2rroll_Gain;                 /* Expression: pi/180
                                        * '<S196>/d2r roll'
                                        */
  real_T QTMIn7_Gain;                  /* Expression: 1
                                        * '<S196>/QTM In7'
                                        */
  real_T d2rpitch_Gain;                /* Expression: pi/180
                                        * '<S196>/d2r pitch'
                                        */
  real_T Constant1_Value[9];           /* Expression: zeros(3)
                                        * '<S196>/Constant1'
                                        */
  real_T QTMIn5_Gain;                  /* Expression: 1
                                        * '<S196>/QTM In5'
                                        */
  real_T mm2mz_Gain;                   /* Expression: 0.001
                                        * '<S196>/mm2m z'
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
                                        * '<S193>/x_d'
                                        */
  real_T eta_dDPN_Gain;                /* Expression: 1
                                        * '<S110>/eta_d DP N'
                                        */
  real_T y_d_Value;                    /* Expression: 0
                                        * '<S193>/y_d'
                                        */
  real_T eta_dDPE_Gain;                /* Expression: 1
                                        * '<S110>/eta_d DP E'
                                        */
  real_T psi_d_Value;                  /* Expression: 0
                                        * '<S193>/psi_d'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * '<S195>/Gain1'
                                        */
  real_T eta_dDPPsi_Gain;              /* Expression: 1
                                        * '<S110>/eta_d DP Psi'
                                        */
  real_T Resetq_Value;                 /* Expression: 0
                                        * '<S50>/Reset q'
                                        */
  real_T q_x_0_Value;                  /* Expression: 0
                                        * '<S102>/q_x_0'
                                        */
  real_T q_y_0_Value;                  /* Expression: 0
                                        * '<S102>/q_y_0'
                                        */
  real_T x_2_Value;                    /* Expression: 5.5
                                        * '<S194>/x_2'
                                        */
  real_T x_1_Value;                    /* Expression: 0
                                        * '<S194>/x_1'
                                        */
  real_T y_2_Value;                    /* Expression: 2
                                        * '<S194>/y_2'
                                        */
  real_T y_1_Value;                    /* Expression: 0
                                        * '<S194>/y_1'
                                        */
  real_T PathSelector_Value;           /* Expression: 0
                                        * '<S114>/Path Selector'
                                        */
  real_T r_x_Value;                    /* Expression: 5.5
                                        * '<S194>/r_x'
                                        */
  real_T Resets_Value;                 /* Expression: 0
                                        * '<S50>/Reset s'
                                        */
  real_T s_0_Value;                    /* Expression: 0
                                        * '<S50>/s_0'
                                        */
  real_T k_Value;                      /* Expression: pi/180*2
                                        * '<S194>/k'
                                        */
  real_T Gain_Gain;                    /* Expression: -1
                                        * '<S173>/Gain'
                                        */
  real_T r_y_Value;                    /* Expression: 2
                                        * '<S194>/r_y'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * '<S179>/Constant'
                                        */
  real_T Gain_Gain_k;                  /* Expression: 180/pi
                                        * '<S121>/Gain'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * '<S119>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * '<S119>/Saturation'
                                        */
  real_T Gain_Gain_d;                  /* Expression: 180
                                        * '<S119>/Gain'
                                        */
  real_T Constant_Value_e;             /* Expression: 2*180
                                        * '<S119>/Constant'
                                        */
  real_T Gain1_Gain_g;                 /* Expression: pi/180
                                        * '<S120>/Gain1'
                                        */
  real_T Gain_Gain_h;                  /* Expression: 180/pi
                                        * '<S154>/Gain'
                                        */
  real_T Saturation_UpperSat_o;        /* Expression: 1e10
                                        * '<S150>/Saturation'
                                        */
  real_T Saturation_LowerSat_d;        /* Expression: -1e10
                                        * '<S150>/Saturation'
                                        */
  real_T Gain_Gain_j;                  /* Expression: 180
                                        * '<S150>/Gain'
                                        */
  real_T Constant_Value_c;             /* Expression: 2*180
                                        * '<S150>/Constant'
                                        */
  real_T Gain1_Gain_j;                 /* Expression: pi/180
                                        * '<S153>/Gain1'
                                        */
  real_T x_dmax_Value;                 /* Expression: 10000
                                        * '<S171>/x_dmax'
                                        */
  real_T origin_x_Value;               /* Expression: 4.5
                                        * '<S194>/origin_x'
                                        */
  real_T origo_y_Value;                /* Expression: 0
                                        * '<S194>/origo_y'
                                        */
  real_T Constant_Value_k;             /* Expression: 1
                                        * '<S178>/Constant'
                                        */
  real_T x_dmin_Value;                 /* Expression: -10000
                                        * '<S171>/x_dmin'
                                        */
  real_T y_dmax_Value;                 /* Expression: 10000
                                        * '<S171>/y_dmax'
                                        */
  real_T y_dmin_Value;                 /* Expression: -10000
                                        * '<S171>/y_dmin'
                                        */
  real_T Delta_Value;                  /* Expression: 2
                                        * '<S111>/Delta'
                                        */
  real_T Gain_Gain_p;                  /* Expression: 180/pi
                                        * '<S156>/Gain'
                                        */
  real_T Saturation_UpperSat_c;        /* Expression: 1e10
                                        * '<S151>/Saturation'
                                        */
  real_T Saturation_LowerSat_c;        /* Expression: -1e10
                                        * '<S151>/Saturation'
                                        */
  real_T Gain_Gain_m;                  /* Expression: 180
                                        * '<S151>/Gain'
                                        */
  real_T Constant_Value_n;             /* Expression: 2*180
                                        * '<S151>/Constant'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: pi/180
                                        * '<S155>/Gain1'
                                        */
  real_T Gain_Gain_jf;                 /* Expression: 180/pi
                                        * '<S158>/Gain'
                                        */
  real_T Saturation_UpperSat_og;       /* Expression: 1e10
                                        * '<S152>/Saturation'
                                        */
  real_T Saturation_LowerSat_o;        /* Expression: -1e10
                                        * '<S152>/Saturation'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 180
                                        * '<S152>/Gain'
                                        */
  real_T Constant_Value_h;             /* Expression: 2*180
                                        * '<S152>/Constant'
                                        */
  real_T Gain1_Gain_i;                 /* Expression: pi/180
                                        * '<S157>/Gain1'
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
                                        * '<S194>/u_d'
                                        */
  real_T Constant_Value_p;             /* Expression: 1
                                        * '<S182>/Constant'
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
  real_T Saturation_UpperSat_d;        /* Expression: 1e10
                                        * '<S14>/Saturation'
                                        */
  real_T Saturation_LowerSat_n;        /* Expression: -1e10
                                        * '<S14>/Saturation'
                                        */
  real_T Gain_Gain_i;                  /* Expression: pi
                                        * '<S14>/Gain'
                                        */
  real_T Constant_Value_b;             /* Expression: 2*pi
                                        * '<S14>/Constant'
                                        */
  real_T Saturation_UpperSat_j;        /* Expression: 1e10
                                        * '<S13>/Saturation'
                                        */
  real_T Saturation_LowerSat_cp;       /* Expression: -1e10
                                        * '<S13>/Saturation'
                                        */
  real_T Gain_Gain_g;                  /* Expression: pi
                                        * '<S13>/Gain'
                                        */
  real_T Constant_Value_i;             /* Expression: 2*pi
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
  real_T Constant_Value_kk;            /* Expression: const
                                        * '<S22>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: const
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
  real_T f_10_XData_f[10];             /* Expression: [0
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
  real_T f_10_YData_j[10];             /* Expression: [0.0500
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
  real_T DeadZone_Start_f;             /* Expression: -0.001
                                        * '<S18>/Dead Zone'
                                        */
  real_T DeadZone_End_o;               /* Expression: 0.001
                                        * '<S18>/Dead Zone'
                                        */
  real_T Constant_Value_l;             /* Expression: const
                                        * '<S25>/Constant'
                                        */
  real_T Constant_Value_l4;            /* Expression: const
                                        * '<S26>/Constant'
                                        */
  real_T Constant_Value_f;             /* Expression: const
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
  real_T f_20_XData_o[10];             /* Expression: [0.000
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
  real_T f_20_YData_n[10];             /* Expression: [0.1665
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
  real_T DeadZone_Start_fx;            /* Expression: -0.001
                                        * '<S19>/Dead Zone'
                                        */
  real_T DeadZone_End_c;               /* Expression: 0.001
                                        * '<S19>/Dead Zone'
                                        */
  real_T Constant_Value_cr;            /* Expression: const
                                        * '<S28>/Constant'
                                        */
  real_T Constant_Value_n2;            /* Expression: const
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
  real_T f_30_XData_d[11];             /* Expression: [0.000
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
                                        * '<S19>/f_3 > 0'
                                        */
  real_T DeadZone_Start_i;             /* Expression: -0.001
                                        * '<S20>/Dead Zone'
                                        */
  real_T DeadZone_End_e;               /* Expression: 0.001
                                        * '<S20>/Dead Zone'
                                        */
  real_T Constant_Value_fy;            /* Expression: const
                                        * '<S31>/Constant'
                                        */
  real_T Constant_Value_m;             /* Expression: const
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
  real_T f_40_XData_l[7];              /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S20>/f_4 > 0'
                                        */
  real_T f_40_YData_i[7];              /* Expression: [0.3588
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
  real_T DeadZone_End_m;               /* Expression: 0.001
                                        * '<S21>/Dead Zone'
                                        */
  real_T Constant_Value_g;             /* Expression: const
                                        * '<S34>/Constant'
                                        */
  real_T Constant_Value_d;             /* Expression: const
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
  real_T f_50_XData_d[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S21>/f_5 > 0'
                                        */
  real_T f_50_YData_a[3];              /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S21>/f_5 > 0'
                                        */
  real_T Saturation_UpperSat_l;        /* Expression: 1.0
                                        * '<S6>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: -1.0
                                        * '<S6>/Saturation'
                                        */
  real_T BT_power_limit_Value;         /* Expression: 0.5
                                        * '<S6>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value;             /* Expression: 0.4
                                        * '<S6>/VSP_speeds'
                                        */
  real_T T_e11_Value_o;                /* Expression: 1
                                        * '<S100>/T_e11'
                                        */
  real_T T_e21_Value_a;                /* Expression: 0
                                        * '<S100>/T_e21'
                                        */
  real_T l_y1_Value_b;                 /* Expression: 0.055
                                        * '<S100>/l_y1'
                                        */
  real_T T_e12_Value_h;                /* Expression: 0
                                        * '<S100>/T_e12'
                                        */
  real_T T_e22_Value_m;                /* Expression: 1
                                        * '<S100>/T_e22'
                                        */
  real_T l_x1_Value_n;                 /* Expression: 0.45
                                        * '<S100>/l_x1'
                                        */
  real_T l_x1_Gain_j;                  /* Expression: -1
                                        * '<S100>/-l_x1'
                                        */
  real_T T_e13_Value_a;                /* Expression: 1
                                        * '<S100>/T_e13'
                                        */
  real_T T_e23_Value_o;                /* Expression: 0
                                        * '<S100>/T_e23'
                                        */
  real_T l_y2_Value_n;                 /* Expression: 0.055
                                        * '<S100>/l_y2'
                                        */
  real_T l_y2_Gain_e;                  /* Expression: -1
                                        * '<S100>/-l_y2'
                                        */
  real_T T_e14_Value_m;                /* Expression: 0
                                        * '<S100>/T_e14'
                                        */
  real_T T_e24_Value_b;                /* Expression: 1
                                        * '<S100>/T_e24'
                                        */
  real_T l_x2_Value_c;                 /* Expression: 0.45
                                        * '<S100>/l_x2'
                                        */
  real_T l_x2_Gain_p;                  /* Expression: -1
                                        * '<S100>/-l_x2'
                                        */
  real_T T_e15_Value_o;                /* Expression: 0
                                        * '<S100>/T_e15'
                                        */
  real_T T_e25_Value_b;                /* Expression: 1
                                        * '<S100>/T_e25'
                                        */
  real_T l_x3_Value_i;                 /* Expression: 0.385
                                        * '<S100>/l_x3'
                                        */
  real_T R31_Value;                    /* Expression: 0
                                        * '<S47>/R31'
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
  real_T K_p_Surge_Value;              /* Expression: 0.5*3
                                        * '<S7>/K_p_Surge'
                                        */
  real_T u_Value;                      /* Expression: 0
                                        * '<S46>/21'
                                        */
  real_T u_Value_k;                    /* Expression: 0
                                        * '<S46>/31'
                                        */
  real_T u_Value_e;                    /* Expression: 0
                                        * '<S46>/12'
                                        */
  real_T K_p_Sway_Value;               /* Expression: .2*4
                                        * '<S7>/K_p_Sway'
                                        */
  real_T u_Value_a;                    /* Expression: 0
                                        * '<S46>/32'
                                        */
  real_T u_Value_c;                    /* Expression: 0
                                        * '<S46>/13'
                                        */
  real_T u_Value_eh;                   /* Expression: 0
                                        * '<S46>/23'
                                        */
  real_T K_p_Yaw_Value;                /* Expression: 1.5*3
                                        * '<S7>/K_p_Yaw'
                                        */
  real_T Gain_Gain_c;                  /* Expression: 180/pi
                                        * '<S74>/Gain'
                                        */
  real_T Saturation_UpperSat_dr;       /* Expression: 1e10
                                        * '<S72>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: -1e10
                                        * '<S72>/Saturation'
                                        */
  real_T Gain_Gain_fq;                 /* Expression: 180
                                        * '<S72>/Gain'
                                        */
  real_T Constant_Value_fc;            /* Expression: 2*180
                                        * '<S72>/Constant'
                                        */
  real_T Gain1_Gain_i5;                /* Expression: pi/180
                                        * '<S73>/Gain1'
                                        */
  real_T Gain_Gain_f0;                 /* Expression: 180/pi
                                        * '<S77>/Gain'
                                        */
  real_T Saturation_UpperSat_d1;       /* Expression: 1e10
                                        * '<S75>/Saturation'
                                        */
  real_T Saturation_LowerSat_nw;       /* Expression: -1e10
                                        * '<S75>/Saturation'
                                        */
  real_T Gain_Gain_l;                  /* Expression: 180
                                        * '<S75>/Gain'
                                        */
  real_T Constant_Value_dk;            /* Expression: 2*180
                                        * '<S75>/Constant'
                                        */
  real_T Gain1_Gain_a;                 /* Expression: pi/180
                                        * '<S76>/Gain1'
                                        */
  real_T K_i_Surge_Value;              /* Expression: 0
                                        * '<S7>/K_i_Surge'
                                        */
  real_T u_Value_n;                    /* Expression: 0
                                        * '<S45>/21'
                                        */
  real_T u_Value_l;                    /* Expression: 0
                                        * '<S45>/31'
                                        */
  real_T u_Value_i;                    /* Expression: 0
                                        * '<S45>/12'
                                        */
  real_T K_i_Sway_Value;               /* Expression: 0
                                        * '<S7>/K_i_Sway'
                                        */
  real_T u_Value_d;                    /* Expression: 0
                                        * '<S45>/32'
                                        */
  real_T u_Value_kc;                   /* Expression: 0
                                        * '<S45>/13'
                                        */
  real_T u_Value_f;                    /* Expression: 0
                                        * '<S45>/23'
                                        */
  real_T K_i_Yaw_Value;                /* Expression: 0
                                        * '<S7>/K_i_Yaw'
                                        */
  real_T zeta_IC;                      /* Expression: 0
                                        * '<S7>/zeta'
                                        */
  real_T K_d_Surge_Value;              /* Expression: 8*2/4
                                        * '<S7>/K_d_Surge'
                                        */
  real_T u_Value_j;                    /* Expression: 0
                                        * '<S44>/21'
                                        */
  real_T u_Value_aw;                   /* Expression: 0
                                        * '<S44>/31'
                                        */
  real_T u_Value_l1;                   /* Expression: 0
                                        * '<S44>/12'
                                        */
  real_T K_d_Sway_Value;               /* Expression: 25*2
                                        * '<S7>/K_d_Sway'
                                        */
  real_T u_Value_b;                    /* Expression: 0
                                        * '<S44>/32'
                                        */
  real_T u_Value_ju;                   /* Expression: 0
                                        * '<S44>/13'
                                        */
  real_T u_Value_eq;                   /* Expression: 0
                                        * '<S44>/23'
                                        */
  real_T K_d_Yaw_Value;                /* Expression: 8
                                        * '<S7>/K_d_Yaw'
                                        */
  real_T u_Gain;                       /* Expression: -1
                                        * '<S145>/-1'
                                        */
  real_T _2x1_Value[2];                /* Expression: [0;0]
                                        * '<S60>/0_2x1'
                                        */
  real_T _2x1_Value_c;                 /* Expression: 0
                                        * '<S170>/0_2x1'
                                        */
  real_T Constant_Value_fyr;           /* Expression: 3
                                        * '<S175>/Constant'
                                        */
  real_T Gain_Gain_jk;                 /* Expression: -1
                                        * '<S175>/Gain'
                                        */
  real_T Constant_Value_jt;            /* Expression: 1
                                        * '<S181>/Constant'
                                        */
  real_T my_Value;                     /* Expression: 10
                                        * '<S111>/my'
                                        */
  real_T Gain_Gain_o;                  /* Expression: -1
                                        * '<S137>/Gain'
                                        */
  real_T X_u_Value;                    /* Expression: -0.59739
                                        * '<S69>/X_u'
                                        */
  real_T X_u_Gain;                     /* Expression: -1
                                        * '<S69>/-X_u'
                                        */
  real_T D_L_21_Value;                 /* Expression: 0
                                        * '<S69>/D_L_21'
                                        */
  real_T D_L_31_Value;                 /* Expression: 0
                                        * '<S69>/D_L_31'
                                        */
  real_T D_L_12_Value;                 /* Expression: 0
                                        * '<S69>/D_L_12'
                                        */
  real_T Y_v_Value;                    /* Expression: -3.50625
                                        * '<S69>/Y_v'
                                        */
  real_T Y_v_Gain;                     /* Expression: -1
                                        * '<S69>/-Y_v'
                                        */
  real_T N_v_Value;                    /* Expression: 0.18140
                                        * '<S69>/N_v'
                                        */
  real_T N_v_Gain;                     /* Expression: -1
                                        * '<S69>/-N_v'
                                        */
  real_T D_L_13_Value;                 /* Expression: 0
                                        * '<S69>/D_L_13'
                                        */
  real_T Y_r_Value;                    /* Expression: -7.250
                                        * '<S69>/Y_r'
                                        */
  real_T Y_vr_Gain;                    /* Expression: -1
                                        * '<S69>/-Y_vr'
                                        */
  real_T N_r_Value;                    /* Expression: -1.900
                                        * '<S69>/N_r'
                                        */
  real_T N_r_Gain;                     /* Expression: -1
                                        * '<S69>/-N_r'
                                        */
  real_T m_Value;                      /* Expression: 17.6
                                        * '<S68>/m'
                                        */
  real_T X_udot_Value;                 /* Expression: -2.0
                                        * '<S68>/X_udot'
                                        */
  real_T M_21_Value;                   /* Expression: 0
                                        * '<S68>/M_21'
                                        */
  real_T M_31_Value;                   /* Expression: 0
                                        * '<S68>/M_31'
                                        */
  real_T M_12_Value;                   /* Expression: 0
                                        * '<S68>/M_12'
                                        */
  real_T Y_vdot_Value;                 /* Expression: -10.0
                                        * '<S68>/Y_vdot'
                                        */
  real_T x_g_Value;                    /* Expression: 0.03
                                        * '<S68>/x_g'
                                        */
  real_T N_vdot_Value;                 /* Expression: -0.0
                                        * '<S68>/N_vdot'
                                        */
  real_T M_13_Value;                   /* Expression: 0
                                        * '<S68>/M_13'
                                        */
  real_T Y_rdot_Value;                 /* Expression: 0.0
                                        * '<S68>/Y_rdot'
                                        */
  real_T I_z_Value;                    /* Expression: 1.760
                                        * '<S68>/I_z'
                                        */
  real_T N_rdot_Value;                 /* Expression: -1.0
                                        * '<S68>/N_rdot'
                                        */
  real_T Gain_Gain_e;                  /* Expression: -1
                                        * '<S130>/Gain'
                                        */
  real_T _Gain;                        /* Expression: 2
                                        * '<S146>/2'
                                        */
  real_T _2x2_Value[4];                /* Expression: [0 0;0 0]
                                        * '<S127>/0_2x2'
                                        */
  real_T _2x2_Value_f[4];              /* Expression: [0 0; 0 0]
                                        * '<S61>/0_2x2'
                                        */
  real_T _Gain_b;                      /* Expression: 2
                                        * '<S147>/2'
                                        */
  real_T u_Value_ip;                   /* Expression: 3/2
                                        * '<S134>/3//2'
                                        */
  real_T Gain_Gain_b;                  /* Expression: -1
                                        * '<S138>/Gain'
                                        */
  real_T omega_q_IC;                   /* Expression: 0
                                        * '<S50>/omega_q'
                                        */
  real_T Gain_Gain_lf;                 /* Expression: -1
                                        * '<S131>/Gain'
                                        */
  real_T _2x1_Value_d[2];              /* Expression: [0;0]
                                        * '<S62>/0_2x1'
                                        */
  real_T Gain_Gain_a;                  /* Expression: -1
                                        * '<S174>/Gain'
                                        */
  real_T Gain1_Gain_c;                 /* Expression: -1
                                        * '<S174>/Gain1'
                                        */
  real_T Constant_Value_pr;            /* Expression: 1
                                        * '<S180>/Constant'
                                        */
  real_T u_Gain_j;                     /* Expression: 2
                                        * '<S118>/+ 2'
                                        */
  real_T _Gain_h;                      /* Expression: 2
                                        * '<S149>/2'
                                        */
  real_T _Gain_k;                      /* Expression: 2
                                        * '<S167>/2'
                                        */
  real_T Gain_Gain_l0;                 /* Expression: 1
                                        * '<S167>/Gain'
                                        */
  real_T Constant_Value_fg;            /* Expression: 3
                                        * '<S190>/Constant'
                                        */
  real_T Gain_Gain_mo;                 /* Expression: -1
                                        * '<S190>/Gain'
                                        */
  real_T u_Value_ns;                   /* Expression: 3/2
                                        * '<S135>/3//2'
                                        */
  real_T Constant_Value_ml;            /* Expression: 3
                                        * '<S139>/Constant'
                                        */
  real_T _2x1_Value_o[2];              /* Expression: [0;0]
                                        * '<S63>/0_2x1'
                                        */
  real_T S11_Value;                    /* Expression: 0
                                        * '<S64>/S11'
                                        */
  real_T R31_Value_j;                  /* Expression: 0
                                        * '<S64>/R31'
                                        */
  real_T S12_Gain;                     /* Expression: 1
                                        * '<S64>/S12'
                                        */
  real_T S22_Value;                    /* Expression: 0
                                        * '<S64>/S22'
                                        */
  real_T S32_Value;                    /* Expression: 0
                                        * '<S64>/S32'
                                        */
  real_T S13_Value;                    /* Expression: 0
                                        * '<S64>/S13'
                                        */
  real_T S23_Value;                    /* Expression: 0
                                        * '<S64>/S23'
                                        */
  real_T S33_Value;                    /* Expression: 1
                                        * '<S64>/S33'
                                        */
  real_T Gain_Gain_g0;                 /* Expression: 1
                                        * '<S65>/Gain'
                                        */
  real_T DeadZone_Start_g;             /* Expression: -0.001
                                        * '<S80>/Dead Zone'
                                        */
  real_T DeadZone_End_d;               /* Expression: 0.001
                                        * '<S80>/Dead Zone'
                                        */
  real_T Constant_Value_ip;            /* Expression: const
                                        * '<S85>/Constant'
                                        */
  real_T Constant_Value_hk;            /* Expression: const
                                        * '<S86>/Constant'
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
                                        * '<S80>/f_1 < 0'
                                        */
  real_T f_10_YData_g[9];              /* Expression: [-1.0000
                                          -0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2089]
                                        * '<S80>/f_1 < 0'
                                        */
  real_T f_10_Value_g;                 /* Expression: 0
                                        * '<S80>/f_1 = 0'
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
                                        * '<S80>/f_1 > 0'
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
                                        * '<S80>/f_1 > 0'
                                        */
  real_T DeadZone_Start_m;             /* Expression: -0.001
                                        * '<S81>/Dead Zone'
                                        */
  real_T DeadZone_End_b;               /* Expression: 0.001
                                        * '<S81>/Dead Zone'
                                        */
  real_T Constant_Value_hl;            /* Expression: const
                                        * '<S88>/Constant'
                                        */
  real_T Constant_Value_pg;            /* Expression: const
                                        * '<S89>/Constant'
                                        */
  real_T Constant_Value_my;            /* Expression: const
                                        * '<S90>/Constant'
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
                                        * '<S81>/f_2 < 0'
                                        */
  real_T f_20_YData_nw[11];            /* Expression: [-1.0000
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
                                        * '<S81>/f_2 < 0'
                                        */
  real_T f_20_Value_k;                 /* Expression: 0
                                        * '<S81>/f_2 = 0'
                                        */
  real_T f_20_XData_a[10];             /* Expression: [0.000
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
                                        * '<S81>/f_2 > 0'
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
                                        * '<S81>/f_2 > 0'
                                        */
  real_T DeadZone_Start_d;             /* Expression: -0.001
                                        * '<S82>/Dead Zone'
                                        */
  real_T DeadZone_End_n;               /* Expression: 0.001
                                        * '<S82>/Dead Zone'
                                        */
  real_T Constant_Value_la;            /* Expression: const
                                        * '<S91>/Constant'
                                        */
  real_T Constant_Value_d2;            /* Expression: const
                                        * '<S92>/Constant'
                                        */
  real_T f_30_XData_g[8];              /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S82>/f_3 < 0'
                                        */
  real_T f_30_YData_i[8];              /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S82>/f_3 < 0'
                                        */
  real_T f_30_Value_b;                 /* Expression: 0
                                        * '<S82>/f_3 = 0'
                                        */
  real_T f_30_XData_e[11];             /* Expression: [0.000
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
                                        * '<S82>/f_3 > 0'
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
                                        * '<S82>/f_3 > 0'
                                        */
  real_T DeadZone_Start_my;            /* Expression: -0.001
                                        * '<S83>/Dead Zone'
                                        */
  real_T DeadZone_End_h;               /* Expression: 0.001
                                        * '<S83>/Dead Zone'
                                        */
  real_T Constant_Value_o;             /* Expression: const
                                        * '<S94>/Constant'
                                        */
  real_T Constant_Value_dl;            /* Expression: const
                                        * '<S95>/Constant'
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
                                        * '<S83>/f_4 < 0'
                                        */
  real_T f_40_YData_e[10];             /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2000
                                          -0.1000
                                          -0.0674]
                                        * '<S83>/f_4 < 0'
                                        */
  real_T f_40_Value_a;                 /* Expression: 0
                                        * '<S83>/f_4 = 0'
                                        */
  real_T f_40_XData_j[7];              /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S83>/f_4 > 0'
                                        */
  real_T f_40_YData_a[7];              /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S83>/f_4 > 0'
                                        */
  real_T DeadZone_Start_lo;            /* Expression: -0.001
                                        * '<S84>/Dead Zone'
                                        */
  real_T DeadZone_End_m5;              /* Expression: 0.001
                                        * '<S84>/Dead Zone'
                                        */
  real_T Constant_Value_c5;            /* Expression: const
                                        * '<S97>/Constant'
                                        */
  real_T Constant_Value_gc;            /* Expression: const
                                        * '<S98>/Constant'
                                        */
  real_T f_50_XData_e[3];              /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S84>/f_5 < 0'
                                        */
  real_T f_50_YData_p[3];              /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S84>/f_5 < 0'
                                        */
  real_T f_50_Value_b;                 /* Expression: 0
                                        * '<S84>/f_5 = 0'
                                        */
  real_T f_50_XData_p[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S84>/f_5 > 0'
                                        */
  real_T f_50_YData_pp[3];             /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S84>/f_5 > 0'
                                        */
  real_T BT_power_limit_Value_n;       /* Expression: 0.5
                                        * '<S7>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value_l;           /* Expression: 0.4
                                        * '<S7>/VSP_speeds'
                                        */
  real_T Saturation_UpperSat_j2;       /* Expression: 1.0
                                        * '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat_ll;       /* Expression: -1.0
                                        * '<S1>/Saturation'
                                        */
  real_T T_e11_Value_od;               /* Expression: 1
                                        * '<S109>/T_e11'
                                        */
  real_T T_e21_Value_k;                /* Expression: 0
                                        * '<S109>/T_e21'
                                        */
  real_T l_y1_Value_k;                 /* Expression: 0.055
                                        * '<S109>/l_y1'
                                        */
  real_T T_e12_Value_j;                /* Expression: 0
                                        * '<S109>/T_e12'
                                        */
  real_T T_e22_Value_n;                /* Expression: 1
                                        * '<S109>/T_e22'
                                        */
  real_T l_x1_Value_j;                 /* Expression: 0.45
                                        * '<S109>/l_x1'
                                        */
  real_T l_x1_Gain_n;                  /* Expression: -1
                                        * '<S109>/-l_x1'
                                        */
  real_T T_e13_Value_ai;               /* Expression: 1
                                        * '<S109>/T_e13'
                                        */
  real_T T_e23_Value_b;                /* Expression: 0
                                        * '<S109>/T_e23'
                                        */
  real_T l_y2_Value_ne;                /* Expression: 0.055
                                        * '<S109>/l_y2'
                                        */
  real_T l_y2_Gain_h;                  /* Expression: -1
                                        * '<S109>/-l_y2'
                                        */
  real_T T_e14_Value_mp;               /* Expression: 0
                                        * '<S109>/T_e14'
                                        */
  real_T T_e24_Value_c;                /* Expression: 1
                                        * '<S109>/T_e24'
                                        */
  real_T l_x2_Value_p;                 /* Expression: 0.45
                                        * '<S109>/l_x2'
                                        */
  real_T l_x2_Gain_po;                 /* Expression: -1
                                        * '<S109>/-l_x2'
                                        */
  real_T T_e15_Value_l;                /* Expression: 0
                                        * '<S109>/T_e15'
                                        */
  real_T T_e25_Value_n;                /* Expression: 1
                                        * '<S109>/T_e25'
                                        */
  real_T l_x3_Value_e;                 /* Expression: 0.385
                                        * '<S109>/l_x3'
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
                                        * '<S108>/u_1 to f_1'
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
                                        * '<S108>/u_1 to f_1'
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
                                        * '<S108>/u_2 to f_2'
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
                                        * '<S108>/u_2 to f_2'
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
                                        * '<S108>/u_3 to f_3'
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
                                        * '<S108>/u_3 to f_3'
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
                                        * '<S108>/u_4 to f_4'
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
                                        * '<S108>/u_4 to f_4'
                                        */
  real_T u_5tof_5_XData[7];            /* Expression: [-.3:0.1:.3]
                                        * '<S108>/u_5 to f_5'
                                        */
  real_T u_5tof_5_YData[7];            /* Expression: [-1.2630 -1.0309 -0.3808 0 0.3480  0.8290 1.0930]
                                        * '<S108>/u_5 to f_5'
                                        */
  real_T u_Value_fv;                   /* Expression: 0
                                        * '<S42>/12'
                                        */
  real_T u_Value_h;                    /* Expression: 0
                                        * '<S42>/21'
                                        */
  real_T Gamma_q_Surge_Value;          /* Expression: 10/200
                                        * '<S7>/Gamma_q_Surge'
                                        */
  real_T Gamma_q_Sway_Value;           /* Expression: 0.2*4
                                        * '<S7>/Gamma_q_Sway'
                                        */
  real_T lambda_Value;                 /* Expression: 2
                                        * '<S7>/lambda'
                                        */
  real_T Constant_Value_od[4];         /* Expression: a
                                        * '<S128>/Constant'
                                        */
  real_T dotomega_q_Gain;              /* Expression: -1
                                        * '<S50>/dot omega_q'
                                        */
  real_T _2x1_Value_m[2];              /* Expression: [0;0]
                                        * '<S122>/0_2x1'
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
                                        * '<S196>/QTM In1 FPS'
                                        */
  real_T Saturation_UpperSat_js;       /* Expression: 3
                                        * '<S200>/Saturation'
                                        */
  real_T Saturation_LowerSat_op;       /* Expression: -2.6
                                        * '<S200>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 3
                                        * '<S200>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -3.5
                                        * '<S200>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.6
                                        * '<S200>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S200>/Saturation2'
                                        */
  real_T planttau_surge_Gain;          /* Expression: 1
                                        * '<S200>/plant tau_surge'
                                        */
  real_T planttau_sway_Gain;           /* Expression: 1
                                        * '<S200>/plant tau_sway'
                                        */
  real_T planttau_yaw_Gain;            /* Expression: 1
                                        * '<S200>/plant tau_yaw'
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
  real_T psi_los_Gain_h;               /* Expression: 1
                                        * '<Root>/psi_los'
                                        */
  real_T psi_plot_Gain;                /* Expression: 1
                                        * '<Root>/psi_plot'
                                        */
  real_T q_x_Gain_f;                   /* Expression: 1
                                        * '<Root>/q_x'
                                        */
  real_T q_y_Gain_j;                   /* Expression: 1
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
                                        * '<S159>/R12'
                                        */
  real_T R22_Gain;                     /* Expression: 1
                                        * '<S159>/R22'
                                        */
  real_T _Value;                       /* Expression: 0
                                        * '<S161>/0'
                                        */
  real_T S12_Gain_p;                   /* Expression: -1
                                        * '<S161>/S12'
                                        */
  real_T _Value_c;                     /* Expression: 0
                                        * '<S162>/0'
                                        */
  real_T S12_Gain_k;                   /* Expression: -1
                                        * '<S162>/S12'
                                        */
  real_T SITPWM0BT_P1;                 /* Expression: width
                                        * '<S201>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S201>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S201>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S201>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S201>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S201>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S201>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S201>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S201>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S201>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S201>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S201>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S201>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_a;             /* Expression: 0
                                        * '<S201>/Constant'
                                        */
  real_T Constant1_Value_c;            /* Expression: 0
                                        * '<S201>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S201>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S202>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S202>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S202>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S202>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S202>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S202>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S202>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S202>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S202>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S202>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S202>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S202>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S202>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S202>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S202>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S202>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S202>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S202>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S202>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S202>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S202>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S202>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S202>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S202>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S202>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S202>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S202>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S202>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S202>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S202>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S202>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S202>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S202>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S202>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S202>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S202>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S202>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S202>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S202>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S202>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S202>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S202>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S202>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S202>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S202>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S202>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S202>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S202>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S202>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S202>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S202>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S202>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S202>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S202>/VSPS Starboard'
                                        */
  real_T N_r_Value_j;                  /* Expression: -1.900
                                        * '<S207>/N_r'
                                        */
  real_T N_r_Gain_p;                   /* Expression: -1
                                        * '<S207>/-N_r'
                                        */
  real_T N_v_Value_d;                  /* Expression: 0.18140
                                        * '<S207>/N_v'
                                        */
  real_T N_v_Gain_d;                   /* Expression: -1
                                        * '<S207>/-N_v'
                                        */
  real_T X_u_Value_m;                  /* Expression: -0.59739
                                        * '<S207>/X_u'
                                        */
  real_T X_u_Gain_m;                   /* Expression: -1
                                        * '<S207>/-X_u'
                                        */
  real_T Y_v_Value_p;                  /* Expression: -3.50625
                                        * '<S207>/Y_v'
                                        */
  real_T Y_v_Gain_p;                   /* Expression: -1
                                        * '<S207>/-Y_v'
                                        */
  real_T Y_r_Value_f;                  /* Expression: -7.250
                                        * '<S207>/Y_r'
                                        */
  real_T Y_vr_Gain_c;                  /* Expression: -1
                                        * '<S207>/-Y_vr'
                                        */
  real_T D_L_12_Value_g;               /* Expression: 0
                                        * '<S207>/D_L_12'
                                        */
  real_T D_L_13_Value_o;               /* Expression: 0
                                        * '<S207>/D_L_13'
                                        */
  real_T D_L_21_Value_d;               /* Expression: 0
                                        * '<S207>/D_L_21'
                                        */
  real_T D_L_31_Value_l;               /* Expression: 0
                                        * '<S207>/D_L_31'
                                        */
  real_T psi_0_Value;                  /* Expression: 0
                                        * '<S208>/psi_0'
                                        */
  real_T x_0_Value;                    /* Expression: 0
                                        * '<S208>/x_0'
                                        */
  real_T y_0_Value;                    /* Expression: 0
                                        * '<S208>/y_0'
                                        */
  real_T r_0_Value;                    /* Expression: 0
                                        * '<S209>/r_0'
                                        */
  real_T u_0_Value;                    /* Expression: 0
                                        * '<S209>/u_0'
                                        */
  real_T v_0_Value;                    /* Expression: 0
                                        * '<S209>/v_0'
                                        */
  real_T ResetLinearSimulatorintegrator_;/* Expression: 0
                                          * '<S206>/Reset Linear Simulator integrator'
                                          */
  real_T I_z_Value_k;                  /* Expression: 1.760
                                        * '<S210>/I_z'
                                        */
  real_T m_Value_k;                    /* Expression: 17.6
                                        * '<S210>/m'
                                        */
  real_T X_udot_Value_k;               /* Expression: -2.0
                                        * '<S210>/X_udot'
                                        */
  real_T M_21_Value_h;                 /* Expression: 0
                                        * '<S210>/M_21'
                                        */
  real_T M_31_Value_d;                 /* Expression: 0
                                        * '<S210>/M_31'
                                        */
  real_T M_12_Value_j;                 /* Expression: 0
                                        * '<S210>/M_12'
                                        */
  real_T Y_vdot_Value_b;               /* Expression: -10.0
                                        * '<S210>/Y_vdot'
                                        */
  real_T x_g_Value_i;                  /* Expression: 0.03
                                        * '<S210>/x_g'
                                        */
  real_T N_vdot_Value_n;               /* Expression: -0.0
                                        * '<S210>/N_vdot'
                                        */
  real_T M_13_Value_d;                 /* Expression: 0
                                        * '<S210>/M_13'
                                        */
  real_T Y_rdot_Value_f;               /* Expression: 0.0
                                        * '<S210>/Y_rdot'
                                        */
  real_T N_rdot_Value_f;               /* Expression: -1.0
                                        * '<S210>/N_rdot'
                                        */
  real_T R31_Value_n;                  /* Expression: 0
                                        * '<S211>/R31'
                                        */
  real_T R32_Value_g;                  /* Expression: 0
                                        * '<S211>/R32'
                                        */
  real_T R13_Value_i;                  /* Expression: 0
                                        * '<S211>/R13'
                                        */
  real_T R23_Value_i;                  /* Expression: 0
                                        * '<S211>/R23'
                                        */
  real_T R33_Value_k;                  /* Expression: 1
                                        * '<S211>/R33'
                                        */
  real_T eta_surge_hil_Gain;           /* Expression: 1
                                        * '<S199>/eta_surge_hil'
                                        */
  real_T eta_sway_hil_Gain;            /* Expression: 1
                                        * '<S199>/eta_sway_hil'
                                        */
  real_T eta_yaw_hil_Gain;             /* Expression: 1
                                        * '<S199>/eta_yaw_hil'
                                        */
  real_T etadot_surge_hil_Gain;        /* Expression: 1
                                        * '<S199>/etadot_surge_hil'
                                        */
  real_T etadot_sway_hil_Gain;         /* Expression: 1
                                        * '<S199>/etadot_sway_hil'
                                        */
  real_T etadot_yaw_hil_Gain;          /* Expression: 1
                                        * '<S199>/etadot_yaw_hil'
                                        */
  real_T nu_surge_hil_Gain;            /* Expression: 1
                                        * '<S199>/nu_surge_hil'
                                        */
  real_T nu_sway_hil_Gain;             /* Expression: 1
                                        * '<S199>/nu_sway_hil'
                                        */
  real_T nu_yaw_hil_Gain;              /* Expression: 1
                                        * '<S199>/nu_yaw_hil'
                                        */
  uint8_T Gain_Gain_k1;                /* Computed Parameter: Gain
                                        * '<S17>/Gain'
                                        */
  uint8_T Gain1_Gain_b;                /* Computed Parameter: Gain
                                        * '<S17>/Gain1'
                                        */
  uint8_T Gain_Gain_g0p;               /* Computed Parameter: Gain
                                        * '<S18>/Gain'
                                        */
  uint8_T Gain1_Gain_cz;               /* Computed Parameter: Gain
                                        * '<S18>/Gain1'
                                        */
  uint8_T Gain_Gain_bp;                /* Computed Parameter: Gain
                                        * '<S19>/Gain'
                                        */
  uint8_T Gain1_Gain_k;                /* Computed Parameter: Gain
                                        * '<S19>/Gain1'
                                        */
  uint8_T Gain_Gain_ef;                /* Computed Parameter: Gain
                                        * '<S20>/Gain'
                                        */
  uint8_T Gain1_Gain_o;                /* Computed Parameter: Gain
                                        * '<S20>/Gain1'
                                        */
  uint8_T Gain_Gain_g3;                /* Computed Parameter: Gain
                                        * '<S21>/Gain'
                                        */
  uint8_T Gain1_Gain_l;                /* Computed Parameter: Gain
                                        * '<S21>/Gain1'
                                        */
  uint8_T Gain_Gain_p2;                /* Computed Parameter: Gain
                                        * '<S80>/Gain'
                                        */
  uint8_T Gain1_Gain_d;                /* Computed Parameter: Gain
                                        * '<S80>/Gain1'
                                        */
  uint8_T Gain_Gain_jh;                /* Computed Parameter: Gain
                                        * '<S81>/Gain'
                                        */
  uint8_T Gain1_Gain_cy;               /* Computed Parameter: Gain
                                        * '<S81>/Gain1'
                                        */
  uint8_T Gain_Gain_ej;                /* Computed Parameter: Gain
                                        * '<S82>/Gain'
                                        */
  uint8_T Gain1_Gain_e;                /* Computed Parameter: Gain
                                        * '<S82>/Gain1'
                                        */
  uint8_T Gain_Gain_an;                /* Computed Parameter: Gain
                                        * '<S83>/Gain'
                                        */
  uint8_T Gain1_Gain_j3;               /* Computed Parameter: Gain
                                        * '<S83>/Gain1'
                                        */
  uint8_T Gain_Gain_fw;                /* Computed Parameter: Gain
                                        * '<S84>/Gain'
                                        */
  uint8_T Gain1_Gain_lh;               /* Computed Parameter: Gain
                                        * '<S84>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_NLPID {
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
extern Parameters_NLPID NLPID_P;

/* Block signals (auto storage) */
extern BlockIO_NLPID NLPID_B;

/* Continuous states (auto storage) */
extern ContinuousStates_NLPID NLPID_X;

/* Block states (auto storage) */
extern D_Work_NLPID NLPID_DWork;

/* Constant parameters (auto storage) */
extern const ConstParam_NLPID NLPID_ConstP;

/* Model entry point functions */
extern void NLPID_initialize(boolean_T firstTime);
extern void NLPID_output(int_T tid);
extern void NLPID_update(int_T tid);
extern void NLPID_terminate(void);

/* Real-time Model object */
extern RT_MODEL_NLPID *NLPID_M;

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
 * '<Root>' : NLPID
 * '<S1>'   : NLPID/Control Systems
 * '<S2>'   : NLPID/Guidance Systems
 * '<S3>'   : NLPID/HMI
 * '<S4>'   : NLPID/Naviagation Systems
 * '<S5>'   : NLPID/Plants
 * '<S6>'   : NLPID/Control Systems/DP control
 * '<S7>'   : NLPID/Control Systems/Nonlinear PID
 * '<S8>'   : NLPID/Control Systems/PS3 input
 * '<S9>'   : NLPID/Control Systems/PS3 u input control
 * '<S10>'  : NLPID/Control Systems/DP control/DP controller
 * '<S11>'  : NLPID/Control Systems/DP control/Thruster allocation
 * '<S12>'  : NLPID/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1
 * '<S13>'  : NLPID/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]
 * '<S14>'  : NLPID/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1
 * '<S15>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act
 * '<S16>'  : NLPID/Control Systems/DP control/Thruster allocation/tau to f_act
 * '<S17>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S18>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S19>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S20>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S21>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S22>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S23>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S24>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S25>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S26>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1
 * '<S27>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S28>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S29>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S30>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S31>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S32>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S33>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S34>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S35>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S36>'  : NLPID/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S37>'  : NLPID/Control Systems/DP control/Thruster allocation/tau to f_act/T_e
 * '<S38>'  : NLPID/Control Systems/Nonlinear PID/Auxilary functions g_q
 * '<S39>'  : NLPID/Control Systems/Nonlinear PID/Auxiliary function g_s
 * '<S40>'  : NLPID/Control Systems/Nonlinear PID/Control law
 * '<S41>'  : NLPID/Control Systems/Nonlinear PID/Error
 * '<S42>'  : NLPID/Control Systems/Nonlinear PID/Gamma_q
 * '<S43>'  : NLPID/Control Systems/Nonlinear PID/Integral action state
 * '<S44>'  : NLPID/Control Systems/Nonlinear PID/K_d
 * '<S45>'  : NLPID/Control Systems/Nonlinear PID/K_i
 * '<S46>'  : NLPID/Control Systems/Nonlinear PID/K_p
 * '<S47>'  : NLPID/Control Systems/Nonlinear PID/R(psi)
 * '<S48>'  : NLPID/Control Systems/Nonlinear PID/R^T
 * '<S49>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation
 * '<S50>'  : NLPID/Control Systems/Nonlinear PID/Update laws
 * '<S51>'  : NLPID/Control Systems/Nonlinear PID/a_d
 * '<S52>'  : NLPID/Control Systems/Nonlinear PID/nu tilde
 * '<S53>'  : NLPID/Control Systems/Nonlinear PID/v_d
 * '<S54>'  : NLPID/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q eq
 * '<S55>'  : NLPID/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq
 * '<S56>'  : NLPID/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^s eq
 * '<S57>'  : NLPID/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^t eq
 * '<S58>'  : NLPID/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/f_q^T
 * '<S59>'  : NLPID/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/psi_los^q^2^T
 * '<S60>'  : NLPID/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s eq
 * '<S61>'  : NLPID/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq
 * '<S62>'  : NLPID/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq
 * '<S63>'  : NLPID/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^t eq
 * '<S64>'  : NLPID/Control Systems/Nonlinear PID/Control law/S(r)
 * '<S65>'  : NLPID/Control Systems/Nonlinear PID/Control law/tau_FF
 * '<S66>'  : NLPID/Control Systems/Nonlinear PID/Control law/tau_FL
 * '<S67>'  : NLPID/Control Systems/Nonlinear PID/Control law/tau_PID
 * '<S68>'  : NLPID/Control Systems/Nonlinear PID/Control law/tau_FF/M
 * '<S69>'  : NLPID/Control Systems/Nonlinear PID/Control law/tau_FL/D_L
 * '<S70>'  : NLPID/Control Systems/Nonlinear PID/Error/heading to pipi
 * '<S71>'  : NLPID/Control Systems/Nonlinear PID/Error/heading to pipi1
 * '<S72>'  : NLPID/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi
 * '<S73>'  : NLPID/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Degrees to Radians
 * '<S74>'  : NLPID/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Radians to Degrees
 * '<S75>'  : NLPID/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi
 * '<S76>'  : NLPID/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Degrees to Radians
 * '<S77>'  : NLPID/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Radians to Degrees
 * '<S78>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act
 * '<S79>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act
 * '<S80>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S81>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S82>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S83>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S84>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S85>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S86>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S87>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S88>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S89>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1
 * '<S90>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S91>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S92>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S93>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S94>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S95>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S96>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S97>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S98>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S99>'  : NLPID/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S100>' : NLPID/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e
 * '<S101>' : NLPID/Control Systems/Nonlinear PID/Update laws/Transpose
 * '<S102>' : NLPID/Control Systems/Nonlinear PID/Update laws/q_0
 * '<S103>' : NLPID/Control Systems/Nonlinear PID/a_d/v_d^q
 * '<S104>' : NLPID/Control Systems/Nonlinear PID/a_d/v_d^s
 * '<S105>' : NLPID/Control Systems/Nonlinear PID/a_d/v_d^t
 * '<S106>' : NLPID/Control Systems/PS3 u input control/Subsystem
 * '<S107>' : NLPID/Control Systems/PS3 u input control/Subsystem/f_act to tau
 * '<S108>' : NLPID/Control Systems/PS3 u input control/Subsystem/u_act to f_act
 * '<S109>' : NLPID/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e
 * '<S110>' : NLPID/Guidance Systems/DP
 * '<S111>' : NLPID/Guidance Systems/Path-following
 * '<S112>' : NLPID/Guidance Systems/Path-following/Heading
 * '<S113>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight
 * '<S114>' : NLPID/Guidance Systems/Path-following/Path
 * '<S115>' : NLPID/Guidance Systems/Path-following/Speed assigment
 * '<S116>' : NLPID/Guidance Systems/Path-following/Heading/psi_d eq
 * '<S117>' : NLPID/Guidance Systems/Path-following/Heading/psi_d^s eq
 * '<S118>' : NLPID/Guidance Systems/Path-following/Heading/psi_d^s^2 eq
 * '<S119>' : NLPID/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi
 * '<S120>' : NLPID/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians
 * '<S121>' : NLPID/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees
 * '<S122>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector
 * '<S123>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot
 * '<S124>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot
 * '<S125>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot
 * '<S126>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading
 * '<S127>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals
 * '<S128>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I
 * '<S129>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq
 * '<S130>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq
 * '<S131>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq
 * '<S132>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq
 * '<S133>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq
 * '<S134>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq
 * '<S135>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq
 * '<S136>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq
 * '<S137>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq
 * '<S138>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq
 * '<S139>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq
 * '<S140>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose
 * '<S141>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose
 * '<S142>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1
 * '<S143>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2
 * '<S144>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq
 * '<S145>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq
 * '<S146>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq
 * '<S147>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq
 * '<S148>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq
 * '<S149>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq
 * '<S150>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1
 * '<S151>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2
 * '<S152>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3
 * '<S153>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians
 * '<S154>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees
 * '<S155>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians
 * '<S156>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees
 * '<S157>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians
 * '<S158>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees
 * '<S159>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2
 * '<S160>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2^T
 * '<S161>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2
 * '<S162>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)
 * '<S163>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T
 * '<S164>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2^T
 * '<S165>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq
 * '<S166>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq
 * '<S167>' : NLPID/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq
 * '<S168>' : NLPID/Guidance Systems/Path-following/Path/Ellipse path
 * '<S169>' : NLPID/Guidance Systems/Path-following/Path/Path Switch workaround
 * '<S170>' : NLPID/Guidance Systems/Path-following/Path/Straight path
 * '<S171>' : NLPID/Guidance Systems/Path-following/Path/saturation
 * '<S172>' : NLPID/Guidance Systems/Path-following/Path/Ellipse path/p_d eq
 * '<S173>' : NLPID/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq
 * '<S174>' : NLPID/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq
 * '<S175>' : NLPID/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq
 * '<S176>' : NLPID/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq
 * '<S177>' : NLPID/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq/Transpose
 * '<S178>' : NLPID/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor
 * '<S179>' : NLPID/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor
 * '<S180>' : NLPID/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor
 * '<S181>' : NLPID/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor
 * '<S182>' : NLPID/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor
 * '<S183>' : NLPID/Guidance Systems/Path-following/Path/Straight path/p_d eq
 * '<S184>' : NLPID/Guidance Systems/Path-following/Path/Straight path/p_d^s eq
 * '<S185>' : NLPID/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq
 * '<S186>' : NLPID/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/p_d^s^T
 * '<S187>' : NLPID/Guidance Systems/Path-following/Path/saturation/Saturation x
 * '<S188>' : NLPID/Guidance Systems/Path-following/Path/saturation/Saturation y
 * '<S189>' : NLPID/Guidance Systems/Path-following/Speed assigment/v_s eq
 * '<S190>' : NLPID/Guidance Systems/Path-following/Speed assigment/v_s^s eq
 * '<S191>' : NLPID/Guidance Systems/Path-following/Speed assigment/v_s^t eq
 * '<S192>' : NLPID/Guidance Systems/Path-following/Speed assigment/v_s^s eq/p_d^s^T
 * '<S193>' : NLPID/HMI/DP Input
 * '<S194>' : NLPID/HMI/Path-following input
 * '<S195>' : NLPID/HMI/DP Input/Degrees to Radians
 * '<S196>' : NLPID/Naviagation Systems/Qualisys 6 DOF
 * '<S197>' : NLPID/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix
 * '<S198>' : NLPID/Plants/CSE1
 * '<S199>' : NLPID/Plants/Linear Simulator
 * '<S200>' : NLPID/Plants/saturation
 * '<S201>' : NLPID/Plants/CSE1/Bow Thruster
 * '<S202>' : NLPID/Plants/CSE1/Voith Schneider Propeller
 * '<S203>' : NLPID/Plants/CSE1/Bow Thruster/Saturation Dynamic
 * '<S204>' : NLPID/Plants/CSE1/Bow Thruster/Saturation Dynamic1
 * '<S205>' : NLPID/Plants/CSE1/Bow Thruster/Saturation Dynamic2
 * '<S206>' : NLPID/Plants/Linear Simulator/Linear Vessel Dynamics
 * '<S207>' : NLPID/Plants/Linear Simulator/Linear Vessel Dynamics/D_L
 * '<S208>' : NLPID/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta
 * '<S209>' : NLPID/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu
 * '<S210>' : NLPID/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv
 * '<S211>' : NLPID/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)
 */
#endif                                 /* RTW_HEADER_NLPID_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_NLPID
#ifdef RVE
#ifdef MULTITASKING

Parameters_NLPID rtParameter[NUMST+!TID01EQ];

#define NLPID_P                        (*param_lookup[tid][READSIDE])

Parameters_NLPID *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_NLPID rtParameter[2];

#define NLPID_P                        rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
