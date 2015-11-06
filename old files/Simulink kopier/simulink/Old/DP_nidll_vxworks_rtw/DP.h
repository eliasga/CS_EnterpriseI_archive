/*
 * DP.h
 *
 * Real-Time Workshop code generation for Simulink model "DP.mdl".
 *
 * Model Version              : 1.21
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 18:56:13 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_DP_h_
#define RTW_HEADER_DP_h_
#ifndef DP_COMMON_INCLUDES_
# define DP_COMMON_INCLUDES_
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
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_SATURATE.h"
#include "rt_SIGNd_snf.h"
#include "rt_look.h"
#include "rt_look2d_normal.h"
#include "rt_matrixlib.h"
#include "rt_rem_snf.h"
#include "rt_round_snf.h"
#include "rt_MAX.h"
#include "rt_MIN.h"
#endif                                 /* DP_COMMON_INCLUDES_ */

#include "DP_types.h"

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
#define DP_rtModel                     RT_MODEL_DP

/* Block signals (auto storage) */
typedef struct {
  real_T QTMIn[9];                     /* '<S40>/QTM In' */
  real_T QTMIn2Error;                  /* '<S40>/QTM In2 Error' */
  real_T QTMIn9Residual;               /* '<S40>/QTM In9 Residual' */
  real_T QTMIn3;                       /* '<S40>/QTM In3' */
  real_T mm2mx;                        /* '<S40>/mm2m x' */
  real_T QTMIn4;                       /* '<S40>/QTM In4' */
  real_T mm2my;                        /* '<S40>/mm2m y' */
  real_T QTMIn6;                       /* '<S40>/QTM In6' */
  real_T d2ryaw;                       /* '<S40>/d2r yaw' */
  real_T Derivative1[3];               /* '<S40>/Derivative1' */
  real_T EtadotSwitch[3];              /* '<S4>/Etadot Switch' */
  real_T etadot_surge;                 /* '<S4>/etadot_surge' */
  real_T etadot_sway;                  /* '<S4>/etadot_sway' */
  real_T etadot_yaw;                   /* '<S4>/etadot_yaw' */
  real_T EtaSwitch[3];                 /* '<S4>/Eta Switch' */
  real_T eta_surge;                    /* '<S4>/eta_surge' */
  real_T eta_sway;                     /* '<S4>/eta_sway' */
  real_T eta_yaw;                      /* '<S4>/eta_yaw' */
  real_T QTMIn8;                       /* '<S40>/QTM In8' */
  real_T d2rroll;                      /* '<S40>/d2r roll' */
  real_T QTMIn7;                       /* '<S40>/QTM In7' */
  real_T d2rpitch;                     /* '<S40>/d2r pitch' */
  real_T sintheta[3];                  /* '<S41>/sin(theta)' */
  real_T costheta[3];                  /* '<S41>/cos(theta)' */
  real_T R11;                          /* '<S41>/R11' */
  real_T R21;                          /* '<S41>/R21 ' */
  real_T R31;                          /* '<S41>/R31 ' */
  real_T R12;                          /* '<S41>/R12' */
  real_T R22;                          /* '<S41>/R22' */
  real_T R32;                          /* '<S41>/R32' */
  real_T R13;                          /* '<S41>/R13' */
  real_T R23;                          /* '<S41>/R23' */
  real_T R33;                          /* '<S41>/R33' */
  real_T Reshape9x13x3[9];             /* '<S41>/Reshape 9x1->3x3' */
  real_T MatrixConcatenate2[36];       /* '<S40>/Matrix Concatenate2' */
  real_T QTMIn5;                       /* '<S40>/QTM In5' */
  real_T mm2mz;                        /* '<S40>/mm2m z' */
  real_T Derivative[6];                /* '<S40>/Derivative' */
  real_T Product[6];                   /* '<S40>/Product' */
  real_T NuSwitch[3];                  /* '<S4>/Nu Switch' */
  real_T nu_surge;                     /* '<S4>/nu_surge' */
  real_T nu_sway;                      /* '<S4>/nu_sway' */
  real_T nu_yaw;                       /* '<S4>/nu_yaw' */
  real_T eta_dDPN;                     /* '<S37>/eta_d DP N' */
  real_T eta_dDPE;                     /* '<S37>/eta_d DP E' */
  real_T Gain1;                        /* '<S39>/Gain1' */
  real_T eta_dDPPsi;                   /* '<S37>/eta_d DP Psi' */
  real_T ypositionofleftanalogstick11; /* '<S7>/ScalingLY' */
  real_T u_1;                          /* '<S8>/PS3 u_1' */
  real_T xpositionofleftanalogstick11; /* '<S7>/ScalingLX' */
  real_T u_2;                          /* '<S8>/PS3 u_2' */
  real_T ypositionofrightanalogstick11;/* '<S7>/ScalingRY' */
  real_T u_3;                          /* '<S8>/PS3 u_3' */
  real_T xpositionofrightanalogstick11;/* '<S7>/Scaling_RX' */
  real_T u_4;                          /* '<S8>/PS3 u_4' */
  real_T BowThrusterdirection;         /* '<S8>/Add' */
  real_T u_5;                          /* '<S8>/PS3 u_5' */
  real_T l_x1;                         /* '<S36>/-l_x1' */
  real_T l_y2;                         /* '<S36>/-l_y2' */
  real_T l_x2;                         /* '<S36>/-l_x2' */
  real_T x5[15];                       /* '<S36>/3x5' */
  real_T Pseudoinverse[15];            /* '<S15>/Pseudoinverse' */
  real_T psi;                          /* '<S9>/yaw angle' */
  real_T Saturation;                   /* '<S13>/Saturation' */
  real_T Sign;                         /* '<S13>/Sign' */
  real_T Gain;                         /* '<S13>/Gain' */
  real_T Sum1;                         /* '<S13>/Sum1' */
  real_T MathFunction;                 /* '<S13>/Math Function' */
  real_T Sum;                          /* '<S13>/Sum' */
  real_T regulationerror[3];           /* '<S9>/Sum2' */
  real_T Saturation_e;                 /* '<S12>/Saturation' */
  real_T Sign_p;                       /* '<S12>/Sign' */
  real_T Gain_b;                       /* '<S12>/Gain' */
  real_T Sum1_e;                       /* '<S12>/Sum1' */
  real_T MathFunction_k;               /* '<S12>/Math Function' */
  real_T Sum_a;                        /* '<S12>/Sum' */
  real_T Row1;                         /* '<S11>/Row1' */
  real_T Row2;                         /* '<S11>/Row2' */
  real_T Row3;                         /* '<S11>/Row3' */
  real_T TmpHiddenBufferAtKpInport1[3];/* '<S9>/Transposed rotation  matrix in yaw1' */
  real_T Kp[3];                        /* '<S9>/Kp' */
  real_T K_p_surge_scale;              /* '<S9>/K_p_surge_scale' */
  real_T K_p_sway_scale;               /* '<S9>/K_p_sway_scale' */
  real_T K_p_yaw_scale;                /* '<S9>/K_p_yaw_scale' */
  real_T Integrator[3];                /* '<S9>/Integrator' */
  real_T Ki[3];                        /* '<S9>/Ki' */
  real_T K_i_surge_scale;              /* '<S9>/K_i_surge_scale' */
  real_T K_i_sway_scale;               /* '<S9>/K_i_sway_scale' */
  real_T K_i_yaw_scale;                /* '<S9>/K_i_yaw_scale' */
  real_T Sum3[3];                      /* '<S9>/Sum3' */
  real_T TmpHiddenBufferAtKdInport1[3];/* 'synthesized block' */
  real_T Kd[3];                        /* '<S9>/Kd' */
  real_T K_d_surge_scale;              /* '<S9>/K_d_surge_scale' */
  real_T K_d_sway_scale;               /* '<S9>/K_d_sway_scale' */
  real_T K_d_yaw_scale;                /* '<S9>/K_d_yaw_scale' */
  real_T Sum1_d[3];                    /* '<S9>/Sum1' */
  real_T Product_n[5];                 /* '<S15>/Product' */
  real_T DeadZone;                     /* '<S16>/Dead Zone' */
  real_T f_10;                         /* '<S16>/f_1 < 0' */
  real_T f_10_e;                       /* '<S16>/f_1 > 0' */
  real_T MultiportSwitch;              /* '<S16>/Multiport Switch' */
  real_T DeadZone_i;                   /* '<S17>/Dead Zone' */
  real_T f_20;                         /* '<S17>/f_2 < 0' */
  real_T f_20_h;                       /* '<S17>/f_2 > 0' */
  real_T MultiportSwitch_a;            /* '<S17>/Multiport Switch' */
  real_T DeadZone_o;                   /* '<S18>/Dead Zone' */
  real_T f_30;                         /* '<S18>/f_3 < 0' */
  real_T f_30_m;                       /* '<S18>/f_3 > 0' */
  real_T MultiportSwitch_m;            /* '<S18>/Multiport Switch' */
  real_T DeadZone_n;                   /* '<S19>/Dead Zone' */
  real_T f_40;                         /* '<S19>/f_4 < 0' */
  real_T f_40_l;                       /* '<S19>/f_4 > 0' */
  real_T MultiportSwitch_o;            /* '<S19>/Multiport Switch' */
  real_T DeadZone_d;                   /* '<S20>/Dead Zone' */
  real_T f_50;                         /* '<S20>/f_5 < 0' */
  real_T f_50_m;                       /* '<S20>/f_5 > 0' */
  real_T MultiportSwitch_h;            /* '<S20>/Multiport Switch' */
  real_T Saturation_a[5];              /* '<S6>/Saturation' */
  real_T ThrustersettingSwitch[7];     /* '<S1>/Thruster setting Switch' */
  real_T Saturation_j[7];              /* '<S1>/Saturation' */
  real_T TmpHiddenBufferAtToFileInport1[26];/* 'synthesized block' */
  real_T SITzAI0;                      /* '<S3>/SIT zAI0' */
  real_T BatteryBowThruster;           /* '<S3>/Battery Bow Thruster' */
  real_T SITzAI1;                      /* '<S3>/SIT zAI1' */
  real_T BatteryServo;                 /* '<S3>/Battery Servo' */
  real_T SITzAI2;                      /* '<S3>/SIT zAI2' */
  real_T BatteryMain;                  /* '<S3>/Battery Main' */
  real_T QTMIn1FPS;                    /* '<S40>/QTM In1 FPS' */
  real_T Saturation_l;                 /* '<S44>/Saturation' */
  real_T Saturation1;                  /* '<S44>/Saturation1' */
  real_T Saturation2;                  /* '<S44>/Saturation2' */
  real_T planttau_surge;               /* '<S44>/plant tau_surge' */
  real_T planttau_sway;                /* '<S44>/plant tau_sway' */
  real_T planttau_yaw;                 /* '<S44>/plant tau_yaw' */
  real_T plantu_1;                     /* '<S5>/plant u_1' */
  real_T plantu_2;                     /* '<S5>/plant u_2' */
  real_T plantu_3;                     /* '<S5>/plant u_3' */
  real_T plantu_4;                     /* '<S5>/plant u_4' */
  real_T plantu_5;                     /* '<S5>/plant u_5' */
  real_T plantBTpower;                 /* '<S5>/plant BT power' */
  real_T plantVSPspeed;                /* '<S5>/plant VSP speed' */
  real_T N_r;                          /* '<S51>/-N_r' */
  real_T N_v;                          /* '<S51>/-N_v' */
  real_T X_u;                          /* '<S51>/-X_u' */
  real_T Y_v;                          /* '<S51>/-Y_v' */
  real_T Y_vr;                         /* '<S51>/-Y_vr' */
  real_T LinearDampningmatrix[9];      /* '<S51>/Linear Dampning matrix' */
  real_T psi_0;                        /* '<S52>/psi_0' */
  real_T x_0;                          /* '<S52>/x_0' */
  real_T y_0;                          /* '<S52>/y_0' */
  real_T r_0;                          /* '<S53>/r_0' */
  real_T u_0;                          /* '<S53>/u_0' */
  real_T v_0;                          /* '<S53>/v_0' */
  real_T Integrator_d[3];              /* '<S50>/Integrator' */
  real_T Integrator1[3];               /* '<S50>/Integrator1' */
  real_T M_11;                         /* '<S54>/M_11' */
  real_T M_22;                         /* '<S54>/M_22' */
  real_T mx_g;                         /* '<S54>/m x_g' */
  real_T M_32;                         /* '<S54>/M_32' */
  real_T M_23;                         /* '<S54>/M_23' */
  real_T M_33;                         /* '<S54>/M_33' */
  real_T M[9];                         /* '<S54>/M' */
  real_T Inverse[9];                   /* '<S54>/Inverse' */
  real_T Product1[3];                  /* '<S50>/Product1' */
  real_T R11_i;                        /* '<S55>/R11' */
  real_T R21_e;                        /* '<S55>/R21' */
  real_T R12_a;                        /* '<S55>/R12' */
  real_T R22_f;                        /* '<S55>/R22' */
  real_T Rpsi[9];                      /* '<S55>/R(psi)' */
  real_T Product3[3];                  /* '<S50>/Product3' */
  real_T eta_surge_hil;                /* '<S43>/eta_surge_hil' */
  real_T eta_sway_hil;                 /* '<S43>/eta_sway_hil' */
  real_T eta_yaw_hil;                  /* '<S43>/eta_yaw_hil' */
  real_T etadot_surge_hil;             /* '<S43>/etadot_surge_hil' */
  real_T etadot_sway_hil;              /* '<S43>/etadot_sway_hil' */
  real_T etadot_yaw_hil;               /* '<S43>/etadot_yaw_hil' */
  real_T nu_surge_hil;                 /* '<S43>/nu_surge_hil' */
  real_T nu_sway_hil;                  /* '<S43>/nu_sway_hil' */
  real_T nu_yaw_hil;                   /* '<S43>/nu_yaw_hil' */
  real_T Sum_k[3];                     /* '<S50>/Sum' */
  real_T Product2[3];                  /* '<S50>/Product2' */
  real_T BT_D_Gain1;                   /* '<S45>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S45>/BT_D_Gain2' */
  real_T Add;                          /* '<S45>/Add' */
  real_T BT_L_Gain1;                   /* '<S45>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S45>/BT_L_Gain2' */
  real_T Neg;                          /* '<S45>/Neg' */
  real_T Sum1_h;                       /* '<S45>/Sum1' */
  real_T Sum2;                         /* '<S45>/Sum2' */
  real_T Switch;                       /* '<S47>/Switch' */
  real_T Switch2;                      /* '<S47>/Switch2' */
  real_T Switch_j;                     /* '<S48>/Switch' */
  real_T Switch2_m;                    /* '<S48>/Switch2' */
  real_T Switch_h;                     /* '<S49>/Switch' */
  real_T Switch2_a;                    /* '<S49>/Switch2' */
  real_T Sign_a;                       /* '<S46>/Sign' */
  real_T PortVPS_X;                    /* '<S46>/Product1' */
  real_T PortVPS_X_p;                  /* '<S46>/-x' */
  real_T PortVSP_Y;                    /* '<S46>/Product2' */
  real_T PortVSP_Y_d;                  /* '<S46>/-y' */
  real_T StarboardVSP_X;               /* '<S46>/Product3' */
  real_T StarboardVSP_Y;               /* '<S46>/Product4' */
  real_T Servo1;                       /* '<S46>/Servo1' */
  real_T Servo2;                       /* '<S46>/Servo2' */
  real_T Servo3;                       /* '<S46>/Servo3' */
  real_T Servo4;                       /* '<S46>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S46>/VPS_Speed_Gain' */
  real_T Sum_n;                        /* '<S46>/Sum' */
  real_T VSPSPort;                     /* '<S46>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S46>/VSPS Starboard' */
  uint16_T Gain_bj;                    /* '<S16>/Gain' */
  uint16_T Gain1_p;                    /* '<S16>/Gain1' */
  uint16_T Sum_h;                      /* '<S16>/Sum' */
  uint16_T Gain_m;                     /* '<S17>/Gain' */
  uint16_T Gain1_e;                    /* '<S17>/Gain1' */
  uint16_T Sum_e;                      /* '<S17>/Sum' */
  uint16_T Gain_p;                     /* '<S18>/Gain' */
  uint16_T Gain1_n;                    /* '<S18>/Gain1' */
  uint16_T Sum_ao;                     /* '<S18>/Sum' */
  uint16_T Gain_h;                     /* '<S19>/Gain' */
  uint16_T Gain1_d;                    /* '<S19>/Gain1' */
  uint16_T Sum_l;                      /* '<S19>/Sum' */
  uint16_T Gain_m3;                    /* '<S20>/Gain' */
  uint16_T Gain1_j;                    /* '<S20>/Gain1' */
  uint16_T Sum_p;                      /* '<S20>/Sum' */
  uint8_T Compare;                     /* '<S21>/Compare' */
  uint8_T Compare_c;                   /* '<S23>/Compare' */
  uint8_T Compare_o;                   /* '<S22>/Compare' */
  uint8_T Compare_p;                   /* '<S24>/Compare' */
  uint8_T Compare_cj;                  /* '<S25>/Compare' */
  uint8_T Compare_i;                   /* '<S26>/Compare' */
  uint8_T Compare_is;                  /* '<S27>/Compare' */
  uint8_T Compare_p1;                  /* '<S29>/Compare' */
  uint8_T Compare_og;                  /* '<S28>/Compare' */
  uint8_T Compare_j;                   /* '<S30>/Compare' */
  uint8_T Compare_jt;                  /* '<S32>/Compare' */
  uint8_T Compare_g;                   /* '<S31>/Compare' */
  uint8_T Compare_b;                   /* '<S33>/Compare' */
  uint8_T Compare_d;                   /* '<S35>/Compare' */
  uint8_T Compare_n;                   /* '<S34>/Compare' */
  boolean_T LowerRelop1;               /* '<S47>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S47>/UpperRelop' */
  boolean_T LowerRelop1_b;             /* '<S48>/LowerRelop1' */
  boolean_T UpperRelop_b;              /* '<S48>/UpperRelop' */
  boolean_T LowerRelop1_bd;            /* '<S49>/LowerRelop1' */
  boolean_T UpperRelop_h;              /* '<S49>/UpperRelop' */
} BlockIO_DP;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Pseudoinverse_X[15];          /* '<S15>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S15>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S15>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S15>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S15>/Pseudoinverse' */
  real_T Inverse_DWORK3[9];            /* '<S54>/Inverse' */
  real_T Inverse_DWORK4[9];            /* '<S54>/Inverse' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[3];
    real_T TimeStampB;
    real_T LastUAtTimeB[3];
  } Derivative1_RWORK;                 /* '<S40>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } Derivative_RWORK;                  /* '<S40>/Derivative' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<Root>/To File' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<S17>/Scope2' */

  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  int32_T Inverse_DWORK2[3];           /* '<S54>/Inverse' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S16>/Sum' */
  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<Root>/To File' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S50>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S50>/Integrator1' */

  int_T LinearSimulator_MODE;          /* '<S5>/Linear Simulator' */
  int_T CSE1_MODE;                     /* '<S5>/CSE1' */
  uint8_T SignalProbe_DWORK1[3];       /* '<Root>/SignalProbe' */
} D_Work_DP;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S9>/Integrator' */
  real_T Integrator_CSTATE_n[3];       /* '<S50>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S50>/Integrator1' */
} ContinuousStates_DP;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S9>/Integrator' */
  real_T Integrator_CSTATE_n[3];       /* '<S50>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S50>/Integrator1' */
} StateDerivatives_DP;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S9>/Integrator' */
  boolean_T Integrator_CSTATE_n[3];    /* '<S50>/Integrator' */
  boolean_T Integrator1_CSTATE[3];     /* '<S50>/Integrator1' */
} StateDisabled_DP;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S9>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_e;   /* '<S50>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S50>/Integrator1' */
} PrevZCSigStates_DP;

#ifndef ODE5_INTG
#define ODE5_INTG

/* ODE5 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[6];                        /* derivatives */
} ODE5_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            DP_B
#define BlockIO                        BlockIO_DP
#define rtX                            DP_X
#define ContinuousStates               ContinuousStates_DP
#define rtP                            DP_P
#define Parameters                     Parameters_DP
#define rtDWork                        DP_DWork
#define D_Work                         D_Work_DP
#define rtPrevZCSigState               DP_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_DP

/* Parameters (auto storage) */
struct Parameters_DP_ {
  real_T ControllerInputSelector_Value;/* Expression: 0
                                        * '<S4>/Controller Input Selector'
                                        */
  real_T QTMIn_P1;                     /* Expression: width
                                        * '<S40>/QTM In'
                                        */
  real_T QTMIn_P2;                     /* Expression: dtype
                                        * '<S40>/QTM In'
                                        */
  real_T QTMIn_P3;                     /* Expression: portnum
                                        * '<S40>/QTM In'
                                        */
  real_T QTMIn_P4;                     /* Expression: stime
                                        * '<S40>/QTM In'
                                        */
  real_T QTMIn_P5;                     /* Expression: stype
                                        * '<S40>/QTM In'
                                        */
  real_T QTMIn_P6;                     /* Expression: btype
                                        * '<S40>/QTM In'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S40>/QTM In2 Error'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S40>/QTM In9 Residual'
                                        */
  real_T QTMIn3_Gain;                  /* Expression: 1
                                        * '<S40>/QTM In3'
                                        */
  real_T mm2mx_Gain;                   /* Expression: 0.001
                                        * '<S40>/mm2m x'
                                        */
  real_T QTMIn4_Gain;                  /* Expression: 1
                                        * '<S40>/QTM In4'
                                        */
  real_T mm2my_Gain;                   /* Expression: 0.001
                                        * '<S40>/mm2m y'
                                        */
  real_T QTMIn6_Gain;                  /* Expression: 1
                                        * '<S40>/QTM In6'
                                        */
  real_T d2ryaw_Gain;                  /* Expression: pi/180
                                        * '<S40>/d2r yaw'
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
                                        * '<S40>/QTM In8'
                                        */
  real_T d2rroll_Gain;                 /* Expression: pi/180
                                        * '<S40>/d2r roll'
                                        */
  real_T QTMIn7_Gain;                  /* Expression: 1
                                        * '<S40>/QTM In7'
                                        */
  real_T d2rpitch_Gain;                /* Expression: pi/180
                                        * '<S40>/d2r pitch'
                                        */
  real_T Constant1_Value[9];           /* Expression: zeros(3)
                                        * '<S40>/Constant1'
                                        */
  real_T QTMIn5_Gain;                  /* Expression: 1
                                        * '<S40>/QTM In5'
                                        */
  real_T mm2mz_Gain;                   /* Expression: 0.001
                                        * '<S40>/mm2m z'
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
                                        * '<S38>/x_d'
                                        */
  real_T eta_dDPN_Gain;                /* Expression: 1
                                        * '<S37>/eta_d DP N'
                                        */
  real_T y_d_Value;                    /* Expression: 0
                                        * '<S38>/y_d'
                                        */
  real_T eta_dDPE_Gain;                /* Expression: 1
                                        * '<S37>/eta_d DP E'
                                        */
  real_T psi_d_Value;                  /* Expression: 0
                                        * '<S38>/psi_d'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * '<S39>/Gain1'
                                        */
  real_T eta_dDPPsi_Gain;              /* Expression: 1
                                        * '<S37>/eta_d DP Psi'
                                        */
  real_T ControlMode_Value;            /* Expression: 0
                                        * '<S1>/Control Mode'
                                        */
  real_T AS_LY_Value;                  /* Expression: 0
                                        * '<S7>/AS_LY'
                                        */
  real_T ScalingLY_Gain;               /* Expression: 1/32767
                                        * '<S7>/ScalingLY'
                                        */
  real_T PS3u_1_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_1'
                                        */
  real_T AS_LX_Value;                  /* Expression: 0
                                        * '<S7>/AS_LX'
                                        */
  real_T ScalingLX_Gain;               /* Expression: 1/32767
                                        * '<S7>/ScalingLX'
                                        */
  real_T PS3u_2_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_2'
                                        */
  real_T AS_RY_Value;                  /* Expression: 0
                                        * '<S7>/AS_RY'
                                        */
  real_T ScalingRY_Gain;               /* Expression: 1/32767
                                        * '<S7>/ScalingRY'
                                        */
  real_T PS3u_3_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_3'
                                        */
  real_T AS_RX_Value;                  /* Expression: 0
                                        * '<S7>/AS_RX'
                                        */
  real_T Scaling_RX_Gain;              /* Expression: 1/32767
                                        * '<S7>/Scaling_RX'
                                        */
  real_T PS3u_4_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_4'
                                        */
  real_T L2_Value;                     /* Expression: 0
                                        * '<S7>/L2'
                                        */
  real_T R2_Value;                     /* Expression: 0
                                        * '<S7>/R2'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S8>/PS3 u_5'
                                        */
  real_T PS3_BT_Power_Value;           /* Expression: 0
                                        * '<S7>/PS3_BT_Power'
                                        */
  real_T PS3_VSP_Speed_Value;          /* Expression: 0
                                        * '<S7>/PS3_VSP_Speed'
                                        */
  real_T T_e11_Value;                  /* Expression: 1
                                        * '<S36>/T_e11'
                                        */
  real_T T_e21_Value;                  /* Expression: 0
                                        * '<S36>/T_e21'
                                        */
  real_T l_y1_Value;                   /* Expression: 0.055
                                        * '<S36>/l_y1'
                                        */
  real_T T_e12_Value;                  /* Expression: 0
                                        * '<S36>/T_e12'
                                        */
  real_T T_e22_Value;                  /* Expression: 1
                                        * '<S36>/T_e22'
                                        */
  real_T l_x1_Value;                   /* Expression: 0.45
                                        * '<S36>/l_x1'
                                        */
  real_T l_x1_Gain;                    /* Expression: -1
                                        * '<S36>/-l_x1'
                                        */
  real_T T_e13_Value;                  /* Expression: 1
                                        * '<S36>/T_e13'
                                        */
  real_T T_e23_Value;                  /* Expression: 0
                                        * '<S36>/T_e23'
                                        */
  real_T l_y2_Value;                   /* Expression: 0.055
                                        * '<S36>/l_y2'
                                        */
  real_T l_y2_Gain;                    /* Expression: -1
                                        * '<S36>/-l_y2'
                                        */
  real_T T_e14_Value;                  /* Expression: 0
                                        * '<S36>/T_e14'
                                        */
  real_T T_e24_Value;                  /* Expression: 1
                                        * '<S36>/T_e24'
                                        */
  real_T l_x2_Value;                   /* Expression: 0.45
                                        * '<S36>/l_x2'
                                        */
  real_T l_x2_Gain;                    /* Expression: -1
                                        * '<S36>/-l_x2'
                                        */
  real_T T_e15_Value;                  /* Expression: 0
                                        * '<S36>/T_e15'
                                        */
  real_T T_e25_Value;                  /* Expression: 1
                                        * '<S36>/T_e25'
                                        */
  real_T l_x3_Value;                   /* Expression: 0.385
                                        * '<S36>/l_x3'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * '<S13>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * '<S13>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * '<S13>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 2*pi
                                        * '<S13>/Constant'
                                        */
  real_T Saturation_UpperSat_j;        /* Expression: 1e10
                                        * '<S12>/Saturation'
                                        */
  real_T Saturation_LowerSat_g;        /* Expression: -1e10
                                        * '<S12>/Saturation'
                                        */
  real_T Gain_Gain_i;                  /* Expression: pi
                                        * '<S12>/Gain'
                                        */
  real_T Constant_Value_i;             /* Expression: 2*pi
                                        * '<S12>/Constant'
                                        */
  real_T Kp_Gain[9];                   /* Expression: Kp
                                        * '<S9>/Kp'
                                        */
  real_T K_p_surge_scale_Gain;         /* Expression: 1
                                        * '<S9>/K_p_surge_scale'
                                        */
  real_T K_p_sway_scale_Gain;          /* Expression: 1
                                        * '<S9>/K_p_sway_scale'
                                        */
  real_T K_p_yaw_scale_Gain;           /* Expression: 1
                                        * '<S9>/K_p_yaw_scale'
                                        */
  real_T Reset_DP_integrator_Value;    /* Expression: 0
                                        * '<S9>/Reset_DP_integrator'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * '<S9>/Integrator'
                                        */
  real_T Ki_Gain[9];                   /* Expression: Ki
                                        * '<S9>/Ki'
                                        */
  real_T K_i_surge_scale_Gain;         /* Expression: 1
                                        * '<S9>/K_i_surge_scale'
                                        */
  real_T K_i_sway_scale_Gain;          /* Expression: 1
                                        * '<S9>/K_i_sway_scale'
                                        */
  real_T K_i_yaw_scale_Gain;           /* Expression: 1
                                        * '<S9>/K_i_yaw_scale'
                                        */
  real_T Kd_Gain[9];                   /* Expression: Kd
                                        * '<S9>/Kd'
                                        */
  real_T K_d_surge_scale_Gain;         /* Expression: 1
                                        * '<S9>/K_d_surge_scale'
                                        */
  real_T K_d_sway_scale_Gain;          /* Expression: 1
                                        * '<S9>/K_d_sway_scale'
                                        */
  real_T K_d_yaw_scale_Gain;           /* Expression: 1
                                        * '<S9>/K_d_yaw_scale'
                                        */
  real_T DeadZone_Start;               /* Expression: -0.001
                                        * '<S16>/Dead Zone'
                                        */
  real_T DeadZone_End;                 /* Expression: 0.001
                                        * '<S16>/Dead Zone'
                                        */
  real_T Constant_Value_b;             /* Expression: const
                                        * '<S21>/Constant'
                                        */
  real_T Constant_Value_p;             /* Expression: const
                                        * '<S22>/Constant'
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
                                        * '<S16>/f_1 < 0'
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
                                        * '<S16>/f_1 < 0'
                                        */
  real_T f_10_Value;                   /* Expression: 0
                                        * '<S16>/f_1 = 0'
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
                                        * '<S16>/f_1 > 0'
                                        */
  real_T f_10_YData_o[10];             /* Expression: [0.0500
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000]
                                        * '<S16>/f_1 > 0'
                                        */
  real_T DeadZone_Start_e;             /* Expression: -0.001
                                        * '<S17>/Dead Zone'
                                        */
  real_T DeadZone_End_p;               /* Expression: 0.001
                                        * '<S17>/Dead Zone'
                                        */
  real_T Constant_Value_l;             /* Expression: const
                                        * '<S24>/Constant'
                                        */
  real_T Constant_Value_f;             /* Expression: const
                                        * '<S25>/Constant'
                                        */
  real_T Constant_Value_a;             /* Expression: const
                                        * '<S26>/Constant'
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
                                        * '<S17>/f_2 < 0'
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
                                        * '<S17>/f_2 < 0'
                                        */
  real_T f_20_Value;                   /* Expression: 0
                                        * '<S17>/f_2 = 0'
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
                                        * '<S17>/f_2 > 0'
                                        */
  real_T f_20_YData_l[10];             /* Expression: [0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S17>/f_2 > 0'
                                        */
  real_T DeadZone_Start_o;             /* Expression: -0.001
                                        * '<S18>/Dead Zone'
                                        */
  real_T DeadZone_End_h;               /* Expression: 0.001
                                        * '<S18>/Dead Zone'
                                        */
  real_T Constant_Value_n;             /* Expression: const
                                        * '<S27>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: const
                                        * '<S28>/Constant'
                                        */
  real_T f_30_XData[8];                /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S18>/f_3 < 0'
                                        */
  real_T f_30_YData[8];                /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S18>/f_3 < 0'
                                        */
  real_T f_30_Value;                   /* Expression: 0
                                        * '<S18>/f_3 = 0'
                                        */
  real_T f_30_XData_h[11];             /* Expression: [0.000
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
                                        * '<S18>/f_3 > 0'
                                        */
  real_T f_30_YData_a[11];             /* Expression: [0.0452
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
                                        * '<S18>/f_3 > 0'
                                        */
  real_T DeadZone_Start_a;             /* Expression: -0.001
                                        * '<S19>/Dead Zone'
                                        */
  real_T DeadZone_End_k;               /* Expression: 0.001
                                        * '<S19>/Dead Zone'
                                        */
  real_T Constant_Value_h;             /* Expression: const
                                        * '<S30>/Constant'
                                        */
  real_T Constant_Value_ff;            /* Expression: const
                                        * '<S31>/Constant'
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
                                        * '<S19>/f_4 < 0'
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
                                        * '<S19>/f_4 < 0'
                                        */
  real_T f_40_Value;                   /* Expression: 0
                                        * '<S19>/f_4 = 0'
                                        */
  real_T f_40_XData_h[7];              /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S19>/f_4 > 0'
                                        */
  real_T f_40_YData_g[7];              /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S19>/f_4 > 0'
                                        */
  real_T DeadZone_Start_i;             /* Expression: -0.001
                                        * '<S20>/Dead Zone'
                                        */
  real_T DeadZone_End_pv;              /* Expression: 0.001
                                        * '<S20>/Dead Zone'
                                        */
  real_T Constant_Value_ac;            /* Expression: const
                                        * '<S33>/Constant'
                                        */
  real_T Constant_Value_k;             /* Expression: const
                                        * '<S34>/Constant'
                                        */
  real_T f_50_XData[3];                /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S20>/f_5 < 0'
                                        */
  real_T f_50_YData[3];                /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S20>/f_5 < 0'
                                        */
  real_T f_50_Value;                   /* Expression: 0
                                        * '<S20>/f_5 = 0'
                                        */
  real_T f_50_XData_k[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S20>/f_5 > 0'
                                        */
  real_T f_50_YData_h[3];              /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S20>/f_5 > 0'
                                        */
  real_T Saturation_UpperSat_c;        /* Expression: 1.0
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
  real_T Saturation_UpperSat_f;        /* Expression: 1.0
                                        * '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat_i;        /* Expression: -1.0
                                        * '<S1>/Saturation'
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
                                        * '<S40>/QTM In1 FPS'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: 3
                                        * '<S44>/Saturation'
                                        */
  real_T Saturation_LowerSat_j;        /* Expression: -2.6
                                        * '<S44>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 3
                                        * '<S44>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -3.5
                                        * '<S44>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.6
                                        * '<S44>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S44>/Saturation2'
                                        */
  real_T planttau_surge_Gain;          /* Expression: 1
                                        * '<S44>/plant tau_surge'
                                        */
  real_T planttau_sway_Gain;           /* Expression: 1
                                        * '<S44>/plant tau_sway'
                                        */
  real_T planttau_yaw_Gain;            /* Expression: 1
                                        * '<S44>/plant tau_yaw'
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
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T SITPWM0BT_P1;                 /* Expression: width
                                        * '<S45>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S45>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S45>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S45>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S45>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S45>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S45>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S45>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S45>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S45>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S45>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S45>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S45>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_m;             /* Expression: 0
                                        * '<S45>/Constant'
                                        */
  real_T Constant1_Value_j;            /* Expression: 0
                                        * '<S45>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S45>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S46>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S46>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S46>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S46>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S46>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S46>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S46>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S46>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S46>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S46>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S46>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S46>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S46>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S46>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S46>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S46>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S46>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S46>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S46>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S46>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S46>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S46>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S46>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S46>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S46>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S46>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S46>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S46>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S46>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S46>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S46>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S46>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S46>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S46>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S46>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S46>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S46>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S46>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S46>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S46>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S46>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S46>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S46>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S46>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S46>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S46>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S46>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S46>/VSPS Starboard'
                                        */
  real_T N_r_Value;                    /* Expression: -1.900
                                        * '<S51>/N_r'
                                        */
  real_T N_r_Gain;                     /* Expression: -1
                                        * '<S51>/-N_r'
                                        */
  real_T N_v_Value;                    /* Expression: 0.18140
                                        * '<S51>/N_v'
                                        */
  real_T N_v_Gain;                     /* Expression: -1
                                        * '<S51>/-N_v'
                                        */
  real_T X_u_Value;                    /* Expression: -0.59739
                                        * '<S51>/X_u'
                                        */
  real_T X_u_Gain;                     /* Expression: -1
                                        * '<S51>/-X_u'
                                        */
  real_T Y_v_Value;                    /* Expression: -3.50625
                                        * '<S51>/Y_v'
                                        */
  real_T Y_v_Gain;                     /* Expression: -1
                                        * '<S51>/-Y_v'
                                        */
  real_T Y_r_Value;                    /* Expression: -7.250
                                        * '<S51>/Y_r'
                                        */
  real_T Y_vr_Gain;                    /* Expression: -1
                                        * '<S51>/-Y_vr'
                                        */
  real_T D_L_12_Value;                 /* Expression: 0
                                        * '<S51>/D_L_12'
                                        */
  real_T D_L_13_Value;                 /* Expression: 0
                                        * '<S51>/D_L_13'
                                        */
  real_T D_L_21_Value;                 /* Expression: 0
                                        * '<S51>/D_L_21'
                                        */
  real_T D_L_31_Value;                 /* Expression: 0
                                        * '<S51>/D_L_31'
                                        */
  real_T psi_0_Value;                  /* Expression: 0
                                        * '<S52>/psi_0'
                                        */
  real_T x_0_Value;                    /* Expression: 0
                                        * '<S52>/x_0'
                                        */
  real_T y_0_Value;                    /* Expression: 0
                                        * '<S52>/y_0'
                                        */
  real_T r_0_Value;                    /* Expression: 0
                                        * '<S53>/r_0'
                                        */
  real_T u_0_Value;                    /* Expression: 0
                                        * '<S53>/u_0'
                                        */
  real_T v_0_Value;                    /* Expression: 0
                                        * '<S53>/v_0'
                                        */
  real_T ResetLinearSimulatorintegrator_;/* Expression: 0
                                          * '<S50>/Reset Linear Simulator integrator'
                                          */
  real_T I_z_Value;                    /* Expression: 1.760
                                        * '<S54>/I_z'
                                        */
  real_T m_Value;                      /* Expression: 17.6
                                        * '<S54>/m'
                                        */
  real_T X_udot_Value;                 /* Expression: -2.0
                                        * '<S54>/X_udot'
                                        */
  real_T M_21_Value;                   /* Expression: 0
                                        * '<S54>/M_21'
                                        */
  real_T M_31_Value;                   /* Expression: 0
                                        * '<S54>/M_31'
                                        */
  real_T M_12_Value;                   /* Expression: 0
                                        * '<S54>/M_12'
                                        */
  real_T Y_vdot_Value;                 /* Expression: -10.0
                                        * '<S54>/Y_vdot'
                                        */
  real_T x_g_Value;                    /* Expression: 0.03
                                        * '<S54>/x_g'
                                        */
  real_T N_vdot_Value;                 /* Expression: -0.0
                                        * '<S54>/N_vdot'
                                        */
  real_T M_13_Value;                   /* Expression: 0
                                        * '<S54>/M_13'
                                        */
  real_T Y_rdot_Value;                 /* Expression: 0.0
                                        * '<S54>/Y_rdot'
                                        */
  real_T N_rdot_Value;                 /* Expression: -1.0
                                        * '<S54>/N_rdot'
                                        */
  real_T R31_Value;                    /* Expression: 0
                                        * '<S55>/R31'
                                        */
  real_T R32_Value;                    /* Expression: 0
                                        * '<S55>/R32'
                                        */
  real_T R13_Value;                    /* Expression: 0
                                        * '<S55>/R13'
                                        */
  real_T R23_Value;                    /* Expression: 0
                                        * '<S55>/R23'
                                        */
  real_T R33_Value;                    /* Expression: 1
                                        * '<S55>/R33'
                                        */
  real_T eta_surge_hil_Gain;           /* Expression: 1
                                        * '<S43>/eta_surge_hil'
                                        */
  real_T eta_sway_hil_Gain;            /* Expression: 1
                                        * '<S43>/eta_sway_hil'
                                        */
  real_T eta_yaw_hil_Gain;             /* Expression: 1
                                        * '<S43>/eta_yaw_hil'
                                        */
  real_T etadot_surge_hil_Gain;        /* Expression: 1
                                        * '<S43>/etadot_surge_hil'
                                        */
  real_T etadot_sway_hil_Gain;         /* Expression: 1
                                        * '<S43>/etadot_sway_hil'
                                        */
  real_T etadot_yaw_hil_Gain;          /* Expression: 1
                                        * '<S43>/etadot_yaw_hil'
                                        */
  real_T nu_surge_hil_Gain;            /* Expression: 1
                                        * '<S43>/nu_surge_hil'
                                        */
  real_T nu_sway_hil_Gain;             /* Expression: 1
                                        * '<S43>/nu_sway_hil'
                                        */
  real_T nu_yaw_hil_Gain;              /* Expression: 1
                                        * '<S43>/nu_yaw_hil'
                                        */
  uint8_T Gain_Gain_e;                 /* Computed Parameter: Gain
                                        * '<S16>/Gain'
                                        */
  uint8_T Gain1_Gain_i;                /* Computed Parameter: Gain
                                        * '<S16>/Gain1'
                                        */
  uint8_T Gain_Gain_h;                 /* Computed Parameter: Gain
                                        * '<S17>/Gain'
                                        */
  uint8_T Gain1_Gain_a;                /* Computed Parameter: Gain
                                        * '<S17>/Gain1'
                                        */
  uint8_T Gain_Gain_f;                 /* Computed Parameter: Gain
                                        * '<S18>/Gain'
                                        */
  uint8_T Gain1_Gain_o;                /* Computed Parameter: Gain
                                        * '<S18>/Gain1'
                                        */
  uint8_T Gain_Gain_o;                 /* Computed Parameter: Gain
                                        * '<S19>/Gain'
                                        */
  uint8_T Gain1_Gain_it;               /* Computed Parameter: Gain
                                        * '<S19>/Gain1'
                                        */
  uint8_T Gain_Gain_k;                 /* Computed Parameter: Gain
                                        * '<S20>/Gain'
                                        */
  uint8_T Gain1_Gain_aq;               /* Computed Parameter: Gain
                                        * '<S20>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_DP {
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
    real_T odeY[9];
    real_T odeF[6][9];
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
extern Parameters_DP DP_P;

/* Block signals (auto storage) */
extern BlockIO_DP DP_B;

/* Continuous states (auto storage) */
extern ContinuousStates_DP DP_X;

/* Block states (auto storage) */
extern D_Work_DP DP_DWork;

/* Model entry point functions */
extern void DP_initialize(boolean_T firstTime);
extern void DP_output(int_T tid);
extern void DP_update(int_T tid);
extern void DP_terminate(void);

/* Real-time Model object */
extern RT_MODEL_DP *DP_M;

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
 * '<Root>' : DP
 * '<S1>'   : DP/Control Systems
 * '<S2>'   : DP/Guidance Systems
 * '<S3>'   : DP/HMI
 * '<S4>'   : DP/Naviagation Systems
 * '<S5>'   : DP/Plants
 * '<S6>'   : DP/Control Systems/DP control
 * '<S7>'   : DP/Control Systems/PS3 input
 * '<S8>'   : DP/Control Systems/PS3 u input control
 * '<S9>'   : DP/Control Systems/DP control/DP controller
 * '<S10>'  : DP/Control Systems/DP control/Thruster allocation
 * '<S11>'  : DP/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1
 * '<S12>'  : DP/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]
 * '<S13>'  : DP/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1
 * '<S14>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act
 * '<S15>'  : DP/Control Systems/DP control/Thruster allocation/tau to f_act
 * '<S16>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S17>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S18>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S19>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S20>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S21>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S22>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S23>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S24>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S25>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1
 * '<S26>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S27>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S28>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S29>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S30>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S31>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S32>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S33>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S34>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S35>'  : DP/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S36>'  : DP/Control Systems/DP control/Thruster allocation/tau to f_act/T_e
 * '<S37>'  : DP/Guidance Systems/DP
 * '<S38>'  : DP/HMI/DP Input
 * '<S39>'  : DP/HMI/DP Input/Degrees to Radians
 * '<S40>'  : DP/Naviagation Systems/Qualisys 6 DOF
 * '<S41>'  : DP/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix
 * '<S42>'  : DP/Plants/CSE1
 * '<S43>'  : DP/Plants/Linear Simulator
 * '<S44>'  : DP/Plants/saturation
 * '<S45>'  : DP/Plants/CSE1/Bow Thruster
 * '<S46>'  : DP/Plants/CSE1/Voith Schneider Propeller
 * '<S47>'  : DP/Plants/CSE1/Bow Thruster/Saturation Dynamic
 * '<S48>'  : DP/Plants/CSE1/Bow Thruster/Saturation Dynamic1
 * '<S49>'  : DP/Plants/CSE1/Bow Thruster/Saturation Dynamic2
 * '<S50>'  : DP/Plants/Linear Simulator/Linear Vessel Dynamics
 * '<S51>'  : DP/Plants/Linear Simulator/Linear Vessel Dynamics/D_L
 * '<S52>'  : DP/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta
 * '<S53>'  : DP/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu
 * '<S54>'  : DP/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv
 * '<S55>'  : DP/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)
 */
#endif                                 /* RTW_HEADER_DP_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_DP
#ifdef RVE
#ifdef MULTITASKING

Parameters_DP rtParameter[NUMST+!TID01EQ];

#define DP_P                           (*param_lookup[tid][READSIDE])

Parameters_DP *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_DP rtParameter[2];

#define DP_P                           rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
