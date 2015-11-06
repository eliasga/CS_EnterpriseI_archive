/*
 * TemplateNIPID.h
 *
 * Real-Time Workshop code generation for Simulink model "TemplateNIPID.mdl".
 *
 * Model Version              : 1.113
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 30 14:35:28 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_TemplateNIPID_h_
#define RTW_HEADER_TemplateNIPID_h_
#ifndef TemplateNIPID_COMMON_INCLUDES_
# define TemplateNIPID_COMMON_INCLUDES_
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
#endif                                 /* TemplateNIPID_COMMON_INCLUDES_ */

#include "TemplateNIPID_types.h"

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
#define TemplateNIPID_rtModel          RT_MODEL_TemplateNIPID

/* Block signals (auto storage) */
typedef struct {
  real_T tauyawscale;                  /* '<S1>/tauyawscale' */
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
  real_T setpointxm;                   /* '<S7>/setpointx [m]' */
  real_T setpointym;                   /* '<S7>/setpointy [m]' */
  real_T ctrl1Kppsi;                   /* '<S8>/ctrl1Kppsi' */
  real_T ctrl1Kipsi;                   /* '<S8>/ctrl1Kipsi' */
  real_T ctrl1ResetIntegrator;         /* '<S8>/ctrl1 Reset Integrator ' */
  real_T ux2[4];                       /* '<S13>/[2x2]' */
  real_T Initialq_x;                   /* '<S9>/Initial q_x' */
  real_T Initialq_y;                   /* '<S9>/Initial q_y' */
  real_T Initials;                     /* '<S9>/Initial s' */
  real_T ux3[9];                       /* '<S14>/[3x3]' */
  real_T ux3_c[9];                     /* '<S15>/[3x3]' */
  real_T ux3_p[9];                     /* '<S16>/[3x3]' */
  real_T l_x1;                         /* '<S25>/-l_x1' */
  real_T l_x2;                         /* '<S25>/-l_x2' */
  real_T l_y2;                         /* '<S25>/-l_y2' */
  real_T x5[15];                       /* '<S25>/3x5' */
  real_T N_r;                          /* '<S24>/-N_r' */
  real_T N_v;                          /* '<S24>/-N_v' */
  real_T X_u;                          /* '<S24>/-X_u' */
  real_T Y_v;                          /* '<S24>/-Y_v' */
  real_T Y_vr;                         /* '<S24>/-Y_vr' */
  real_T LinearDampningmatrix[9];      /* '<S24>/Linear Dampning matrix' */
  real_T M_11;                         /* '<S23>/M_11' */
  real_T M_22;                         /* '<S23>/M_22' */
  real_T mx_g;                         /* '<S23>/m x_g' */
  real_T M_32;                         /* '<S23>/M_32' */
  real_T M_23;                         /* '<S23>/M_23' */
  real_T M_33;                         /* '<S23>/M_33' */
  real_T x3[9];                        /* '<S23>/3x3' */
  real_T u_1;                          /* '<S28>/PS3 u_1' */
  real_T u_1tof_1;                     /* '<S67>/u_1 to f_1' */
  real_T u_2;                          /* '<S28>/PS3 u_2' */
  real_T u_205;                        /* '<S68>/u_2 < -0.5' */
  real_T u_201u_202;                   /* '<S68>/u_2 < -0.1 && u_2 >= -0.2' */
  real_T u_20;                         /* '<S68>/u_2 => 0' */
  real_T MultiportSwitch;              /* '<S68>/Multiport Switch' */
  real_T u_3;                          /* '<S28>/PS3 u_3' */
  real_T u_3tof_3;                     /* '<S69>/u_3 to f_3' */
  real_T u_4;                          /* '<S28>/PS3 u_4' */
  real_T u_401;                        /* '<S70>/u_4 < -0.1' */
  real_T u_401_o;                      /* '<S70>/u_4 >= -0.1' */
  real_T MultiportSwitch_p;            /* '<S70>/Multiport Switch' */
  real_T BowThrusterdirection;         /* '<S28>/Add' */
  real_T u_5;                          /* '<S28>/PS3 u_5' */
  real_T DeadZone001;                  /* '<S71>/Dead Zone +-0.01' */
  real_T u_50;                         /* '<S71>/u_5 < 0' */
  real_T u_50_n;                       /* '<S71>/u_5 > 0' */
  real_T MultiportSwitch_i;            /* '<S71>/Multiport Switch' */
  real_T TmpHiddenBufferAtProduct1Inport[5];/* '<S65>/u_act to f_act' */
  real_T Product1[3];                  /* '<S65>/Product1' */
  real_T u_1tof_1_p;                   /* '<S83>/u_1 to f_1' */
  real_T u_205_l;                      /* '<S84>/u_2 < -0.5' */
  real_T u_201u_202_o;                 /* '<S84>/u_2 < -0.1 && u_2 >= -0.2' */
  real_T u_20_p;                       /* '<S84>/u_2 => 0' */
  real_T MultiportSwitch_iv;           /* '<S84>/Multiport Switch' */
  real_T u_3tof_3_b;                   /* '<S85>/u_3 to f_3' */
  real_T u_401_h;                      /* '<S86>/u_4 < -0.1' */
  real_T u_401_j;                      /* '<S86>/u_4 >= -0.1' */
  real_T MultiportSwitch_pl;           /* '<S86>/Multiport Switch' */
  real_T DeadZone001_p;                /* '<S87>/Dead Zone +-0.01' */
  real_T u_50_l;                       /* '<S87>/u_5 < 0' */
  real_T u_50_b;                       /* '<S87>/u_5 > 0' */
  real_T MultiportSwitch_c;            /* '<S87>/Multiport Switch' */
  real_T TmpHiddenBufferAtProduct1Inpo_h[5];/* '<S81>/u_act to f_act' */
  real_T Product1_b[3];                /* '<S81>/Product1' */
  real_T QTMIn[9];                     /* '<S188>/QTM In' */
  real_T QTMIn3xcoordmm;               /* '<S188>/QTM In3 x-coord [mm]' */
  real_T mm2mx;                        /* '<S188>/mm2m x' */
  real_T QTMIn4ycoordmm;               /* '<S188>/QTM In4 y-coord [mm]' */
  real_T mm2my;                        /* '<S188>/mm2m y' */
  real_T QTMIn6yawdeg;                 /* '<S188>/QTM In6 yaw [deg]' */
  real_T d2ryaw;                       /* '<S188>/d2r yaw' */
  real_T etaSwitch[3];                 /* '<S189>/eta Switch' */
  real_T R11;                          /* '<S34>/R11' */
  real_T R21;                          /* '<S34>/R21' */
  real_T R12;                          /* '<S34>/R12' */
  real_T u;                            /* '<S34>/-1' */
  real_T R22;                          /* '<S34>/R22' */
  real_T Rpsi[9];                      /* '<S34>/R(psi)' */
  real_T MathFunction[9];              /* '<S56>/Math Function' */
  real_T Saturation;                   /* '<S63>/Saturation' */
  real_T Sign;                         /* '<S63>/Sign' */
  real_T Gain;                         /* '<S63>/Gain' */
  real_T Sum1;                         /* '<S63>/Sum1' */
  real_T MathFunction_f;               /* '<S63>/Math Function' */
  real_T Sum;                          /* '<S63>/Sum' */
  real_T Integrator[2];                /* '<S35>/Integrator' */
  real_T x_2x_1;                       /* '<S181>/x_2 - x_1' */
  real_T y_2y_1;                       /* '<S181>/y_2 - y_1' */
  real_T TmpHiddenBufferAtProductInport2[2];/* 'synthesized block' */
  real_T Saturation_k;                 /* '<S164>/Saturation' */
  real_T RoundingFunction;             /* '<S164>/Rounding Function' */
  real_T Product[2];                   /* '<S174>/Product' */
  real_T Integrator1;                  /* '<S35>/Integrator1' */
  real_T Product2;                     /* '<S167>/Product2' */
  real_T sins;                         /* '<S167>/sin(s)' */
  real_T Product_a;                    /* '<S167>/Product' */
  real_T Gain_i;                       /* '<S167>/Gain' */
  real_T coss;                         /* '<S167>/cos(s)' */
  real_T Product1_a;                   /* '<S167>/Product1' */
  real_T TmpHiddenBufferAtProductInpor_k[2];/* 'synthesized block' */
  real_T Subract;                      /* '<S174>/Subract' */
  real_T Product1_i[2];                /* '<S174>/Product1' */
  real_T Add[2];                       /* '<S174>/Add' */
  real_T TrigonometricFunction;        /* '<S119>/Trigonometric Function' */
  real_T Saturation_j;                 /* '<S122>/Saturation' */
  real_T Sign_c;                       /* '<S122>/Sign' */
  real_T Gain_k;                       /* '<S122>/Gain' */
  real_T Sum1_j;                       /* '<S122>/Sum1' */
  real_T MathFunction_h;               /* '<S122>/Math Function' */
  real_T Sum_k;                        /* '<S122>/Sum' */
  real_T Saturation_i;                 /* '<S150>/Saturation' */
  real_T Sign_k;                       /* '<S150>/Sign' */
  real_T Gain_d;                       /* '<S150>/Gain' */
  real_T Sum1_l;                       /* '<S150>/Sum1' */
  real_T MathFunction_ht;              /* '<S150>/Math Function' */
  real_T Sum_l;                        /* '<S150>/Sum' */
  real_T MathFunction_n[4];            /* '<S154>/Math Function' */
  real_T x_2x_1_g;                     /* '<S180>/x_2 - x_1' */
  real_T x_2x_1s;                      /* '<S180>/(x_2 - x_1) * s' */
  real_T x_2x_1sx_1;                   /* '<S180>/(x_2 - x_1) * s + x_1' */
  real_T y_2y_1_m;                     /* '<S180>/y_2 - y_1' */
  real_T y_2y_1s;                      /* '<S180>/(y_2 - y_1) * s' */
  real_T y_2y_1sy_1;                   /* '<S180>/(y_2 - y_1) * s + y_1' */
  real_T Product_f[2];                 /* '<S173>/Product' */
  real_T Product2_n;                   /* '<S166>/Product2' */
  real_T coss_o;                       /* '<S166>/cos(s)' */
  real_T Product_d;                    /* '<S166>/Product' */
  real_T Add_c;                        /* '<S166>/Add' */
  real_T sins_p;                       /* '<S166>/sin(s)' */
  real_T Product1_p;                   /* '<S166>/Product1' */
  real_T Add1;                         /* '<S166>/Add1' */
  real_T Subract_h;                    /* '<S173>/Subract' */
  real_T Product1_h[2];                /* '<S173>/Product1' */
  real_T Add_cx[2];                    /* '<S173>/Add' */
  real_T Switch;                       /* '<S178>/Switch' */
  real_T Switch2;                      /* '<S178>/Switch2' */
  real_T Switch_m;                     /* '<S179>/Switch' */
  real_T Switch2_c;                    /* '<S179>/Switch2' */
  real_T Subtract[2];                  /* '<S116>/Subtract' */
  real_T epsilon[2];                   /* '<S127>/epsilon' */
  real_T MultiportSelector;            /* '<S127>/Multiport Selector' */
  real_T TrigonometricFunction_n;      /* '<S144>/Trigonometric Function' */
  real_T Saturation_c;                 /* '<S151>/Saturation' */
  real_T Sign_h;                       /* '<S151>/Sign' */
  real_T Gain_f;                       /* '<S151>/Gain' */
  real_T Sum1_g;                       /* '<S151>/Sum1' */
  real_T MathFunction_c;               /* '<S151>/Math Function' */
  real_T Sum_f;                        /* '<S151>/Sum' */
  real_T Subtract_f;                   /* '<S144>/Subtract' */
  real_T Saturation_m;                 /* '<S152>/Saturation' */
  real_T Sign_f;                       /* '<S152>/Sign' */
  real_T Gain_b;                       /* '<S152>/Gain' */
  real_T Sum1_lj;                      /* '<S152>/Sum1' */
  real_T MathFunction_e;               /* '<S152>/Math Function' */
  real_T Sum_e;                        /* '<S152>/Sum' */
  real_T VectorConcatenate[3];         /* '<S128>/Vector Concatenate' */
  real_T Subtract_m[3];                /* '<S38>/Subtract' */
  real_T Saturation_cu;                /* '<S64>/Saturation' */
  real_T Sign_d;                       /* '<S64>/Sign' */
  real_T Gain_fi;                      /* '<S64>/Gain' */
  real_T Sum1_e;                       /* '<S64>/Sum1' */
  real_T MathFunction_k;               /* '<S64>/Math Function' */
  real_T Sum_d;                        /* '<S64>/Sum' */
  real_T TmpHiddenBufferAtProductInport3[3];/* 'synthesized block' */
  real_T Product_k[3];                 /* '<S53>/Product' */
  real_T Gain_p[3];                    /* '<S53>/Gain' */
  real_T Integrator_k[3];              /* '<S40>/Integrator' */
  real_T Product1_ao[3];               /* '<S53>/Product1' */
  real_T Gain1_a[3];                   /* '<S53>/Gain1' */
  real_T nu[3];                        /* '<S191>/Integrator4' */
  real_T nuSwitch[3];                  /* '<S189>/nu Switch' */
  real_T f_qx;                         /* '<S129>/f_qx' */
  real_T f_qy;                         /* '<S129>/f_qy' */
  real_T TmpHiddenBufferAtProductInport1[2];/* 'synthesized block' */
  real_T Product_c[2];                 /* '<S129>/Product' */
  real_T Delta2;                       /* '<S145>/Delta^2' */
  real_T epsilon_n2;                   /* '<S145>/epsilon_n^2' */
  real_T Add_l;                        /* '<S145>/Add' */
  real_T Divide;                       /* '<S145>/Divide' */
  real_T MultiportSelector1[2];        /* '<S127>/Multiport Selector1' */
  real_T Product_kt[2];                /* '<S145>/Product' */
  real_T u_m[2];                       /* '<S145>/-1' */
  real_T VectorConcatenate_k[3];       /* '<S41>/Vector Concatenate' */
  real_T Product_h[2];                 /* '<S175>/Product' */
  real_T Product2_nb;                  /* '<S168>/Product2' */
  real_T coss_n;                       /* '<S168>/cos(s)' */
  real_T MathFunction_kc;              /* '<S168>/Math Function' */
  real_T Product_p;                    /* '<S168>/Product' */
  real_T Gain_m;                       /* '<S168>/Gain' */
  real_T sins_a;                       /* '<S168>/sin(s)' */
  real_T Product1_hr;                  /* '<S168>/Product1' */
  real_T Gain1_o;                      /* '<S168>/Gain1' */
  real_T Subract_d;                    /* '<S175>/Subract' */
  real_T Product1_k[2];                /* '<S175>/Product1' */
  real_T Add_a[2];                     /* '<S175>/Add' */
  real_T x_dsy_ds2;                    /* '<S120>/x_d^s * y_d^s^2' */
  real_T x_ds2y_ds;                    /* '<S120>/x_d^s^2 * y_d^s' */
  real_T x_dsy_ds2x_ds2y_ds;           /* '<S120>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
  real_T x_ds2;                        /* '<S120>/( x_d^s )^2' */
  real_T y_ds2;                        /* '<S120>/( y_d^s )^2' */
  real_T x_ds2y_ds2;                   /* '<S120>/( x_d^s )^2 + ( y_d^s )^2' */
  real_T Divide_i;                     /* '<S120>/Divide' */
  real_T Delta2_l;                     /* '<S148>/Delta^2' */
  real_T epsilon_n2_b;                 /* '<S148>/epsilon_n^2' */
  real_T Add_e;                        /* '<S148>/Add' */
  real_T Divide_ix;                    /* '<S148>/Divide' */
  real_T MathFunction_ch[4];           /* '<S158>/Math Function' */
  real_T Product_ht[2];                /* '<S160>/Product' */
  real_T Product1_m[2];                /* '<S160>/Product1' */
  real_T Subtract1[2];                 /* '<S160>/Subtract1' */
  real_T MultiportSelector2;           /* '<S127>/Multiport Selector2' */
  real_T Product_l;                    /* '<S148>/Product' */
  real_T Subtract_n;                   /* '<S148>/Subtract' */
  real_T epsilon_n2_p;                 /* '<S133>/epsilon_n^2' */
  real_T Delta2_b;                     /* '<S133>/Delta^2' */
  real_T Add_d;                        /* '<S133>/Add' */
  real_T sqrt_m;                       /* '<S133>/sqrt' */
  real_T Divide_k;                     /* '<S133>/Divide' */
  real_T MathFunction_cq[2];           /* '<S183>/Math Function' */
  real_T Product_g;                    /* '<S182>/Product' */
  real_T sqrt_p;                       /* '<S182>/sqrt' */
  real_T Product_gf;                   /* '<S177>/Product' */
  real_T MathFunction_ho[2];           /* '<S171>/Math Function' */
  real_T Product_n;                    /* '<S170>/Product' */
  real_T sqrt_e;                       /* '<S170>/sqrt' */
  real_T Subract_k;                    /* '<S177>/Subract' */
  real_T Product1_bz;                  /* '<S177>/Product1' */
  real_T Add_df;                       /* '<S177>/Add' */
  real_T Divide_l;                     /* '<S184>/Divide' */
  real_T Product_pe;                   /* '<S133>/Product' */
  real_T MathFunction_m[2];            /* '<S140>/Math Function' */
  real_T Divide_m[2];                  /* '<S137>/Divide' */
  real_T Product_ac;                   /* '<S137>/Product' */
  real_T Gain_g;                       /* '<S137>/Gain' */
  real_T Subtract_ni;                  /* '<S133>/Subtract' */
  real_T VectorConcatenate_c[3];       /* '<S47>/Vector Concatenate' */
  real_T Add_o[3];                     /* '<S39>/Add' */
  real_T Product_kj[3];                /* '<S37>/Product' */
  real_T Subtract_k[3];                /* '<S37>/Subtract' */
  real_T Product2_m[3];                /* '<S53>/Product2' */
  real_T Gain2[3];                     /* '<S53>/Gain2' */
  real_T Sum_g[3];                     /* '<S53>/Sum' */
  real_T Product1_h4[3];               /* '<S52>/Product1' */
  real_T Product_d3[3];                /* '<S33>/Product' */
  real_T TrigonometricFunction1;       /* '<S130>/Trigonometric Function1' */
  real_T Gain_k3;                      /* '<S130>/Gain' */
  real_T Product1_j[2];                /* '<S130>/Product1' */
  real_T TrigonometricFunction_e;      /* '<S130>/Trigonometric Function' */
  real_T Product2_l[2];                /* '<S130>/Product2' */
  real_T MatrixConcatenate[4];         /* '<S130>/Matrix Concatenate' */
  real_T Product_ay[4];                /* '<S130>/Product' */
  real_T MathFunction_cw[2];           /* '<S45>/Math Function' */
  real_T Product2_p;                   /* '<S146>/Product2' */
  real_T MathFunction_ct[2];           /* '<S146>/Math Function' */
  real_T Product3[4];                  /* '<S146>/Product3' */
  real_T Product4[4];                  /* '<S146>/Product4' */
  real_T u_ma[4];                      /* '<S146>/2' */
  real_T Delta2_g;                     /* '<S146>/Delta^2' */
  real_T epsilon_n2_f;                 /* '<S146>/epsilon_n^2' */
  real_T Add_n;                        /* '<S146>/Add' */
  real_T u_j;                          /* '<S146>/( )^2' */
  real_T Divide_h[4];                  /* '<S146>/Divide' */
  real_T Product1_kt[4];               /* '<S146>/Product1' */
  real_T Divide1[4];                   /* '<S146>/Divide1' */
  real_T Subtract_d[4];                /* '<S146>/Subtract' */
  real_T MathFunction_l[4];            /* '<S46>/Math Function' */
  real_T Product_o[2];                 /* '<S42>/Product' */
  real_T Product1_ay[2];               /* '<S42>/Product1' */
  real_T Add_am[2];                    /* '<S42>/Add' */
  real_T MatrixConcatenate_b[6];       /* '<S42>/Matrix Concatenate' */
  real_T Product_m[2];                 /* '<S147>/Product' */
  real_T u_n[2];                       /* '<S147>/2' */
  real_T Delta2_p;                     /* '<S147>/Delta^2' */
  real_T epsilon_n2_a;                 /* '<S147>/epsilon_n^2' */
  real_T Add_j;                        /* '<S147>/Add' */
  real_T u_f;                          /* '<S147>/( )^2' */
  real_T Divide_b[2];                  /* '<S147>/Divide' */
  real_T Product1_p1[4];               /* '<S159>/Product1' */
  real_T MultiportSelector3[2];        /* '<S127>/Multiport Selector3' */
  real_T Product1_bp[2];               /* '<S147>/Product1' */
  real_T Divide1_b[2];                 /* '<S147>/Divide1' */
  real_T Subtract_g[2];                /* '<S147>/Subtract' */
  real_T Product_e[2];                 /* '<S48>/Product' */
  real_T Product1_c[2];                /* '<S134>/Product1' */
  real_T epsilon_n2_at;                /* '<S134>/epsilon_n^2' */
  real_T Delta2_n;                     /* '<S134>/Delta^2' */
  real_T Add_ai;                       /* '<S134>/Add' */
  real_T u2;                           /* '<S134>/^3//2' */
  real_T Divide_k1[2];                 /* '<S134>/Divide' */
  real_T Product_c4[2];                /* '<S134>/Product' */
  real_T MathFunction_j[2];            /* '<S141>/Math Function' */
  real_T Divide_n[2];                  /* '<S138>/Divide' */
  real_T Product_hk[2];                /* '<S138>/Product' */
  real_T Gain_a[2];                    /* '<S138>/Gain' */
  real_T Sum_f4[2];                    /* '<S134>/Sum' */
  real_T Product1_hrb[2];              /* '<S48>/Product1' */
  real_T Add_p[2];                     /* '<S48>/Add' */
  real_T MatrixConcatenate_k[6];       /* '<S48>/Matrix Concatenate' */
  real_T Add_jn[6];                    /* '<S58>/Add' */
  real_T Integrator2[2];               /* '<S35>/Integrator2' */
  real_T Add1_g[2];                    /* '<S35>/Add1' */
  real_T Product_c3[3];                /* '<S36>/Product' */
  real_T TrigonometricFunction1_f;     /* '<S131>/Trigonometric Function1' */
  real_T Gain_e;                       /* '<S131>/Gain' */
  real_T Product1_o;                   /* '<S131>/Product1' */
  real_T TrigonometricFunction_i;      /* '<S131>/Trigonometric Function' */
  real_T Product2_g;                   /* '<S131>/Product2' */
  real_T TmpHiddenBufferAtProductInpor_g[2];/* 'synthesized block' */
  real_T Product_le[2];                /* '<S131>/Product' */
  real_T Product_d2;                   /* '<S43>/Product' */
  real_T Product1_b4;                  /* '<S43>/Product1' */
  real_T VectorConcatenate_m[3];       /* '<S43>/Vector Concatenate' */
  real_T Product_ar[2];                /* '<S176>/Product' */
  real_T Product2_gd;                  /* '<S169>/Product2' */
  real_T sins3;                        /* '<S169>/sin(s)3' */
  real_T MathFunction_i;               /* '<S169>/Math Function' */
  real_T Product_b;                    /* '<S169>/Product' */
  real_T coss3;                        /* '<S169>/cos(s)3' */
  real_T Product1_ju;                  /* '<S169>/Product1' */
  real_T Gain_c;                       /* '<S169>/Gain' */
  real_T Subract_c;                    /* '<S176>/Subract' */
  real_T Product1_jq[2];               /* '<S176>/Product1' */
  real_T Add_b[2];                     /* '<S176>/Add' */
  real_T x_dsy_ds3;                    /* '<S121>/x_d^s * y_d^s^3 ' */
  real_T x_ds3y_ds;                    /* '<S121>/x_d^s^3 * y_d^s' */
  real_T x_dsy_ds3x_ds3y_ds;           /* '<S121>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
  real_T Product1_f;                   /* '<S121>/Product1' */
  real_T x_dsx_ds2;                    /* '<S121>/x_d^s * x_d^s^2' */
  real_T y_dsy_ds2;                    /* '<S121>/y_d^s * y_d^s^2' */
  real_T x_dsx_ds2x_ds3y_ds;           /* '<S121>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
  real_T u_b;                          /* '<S121>/+ 2' */
  real_T Product2_i;                   /* '<S121>/Product2' */
  real_T Subtract_b;                   /* '<S121>/Subtract' */
  real_T x_ds2y_ds22;                  /* '<S121>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
  real_T Divide_d;                     /* '<S121>/Divide' */
  real_T epsilon_ns2;                  /* '<S149>/(epsilon_n^s)^2' */
  real_T Product_bu;                   /* '<S149>/Product' */
  real_T u_l;                          /* '<S149>/2' */
  real_T Delta2_e;                     /* '<S149>/Delta^2' */
  real_T epsilon_n2_k;                 /* '<S149>/epsilon_n^2' */
  real_T Add_nt;                       /* '<S149>/Add' */
  real_T u_mx;                         /* '<S149>/( )^2' */
  real_T Divide_j;                     /* '<S149>/Divide' */
  real_T MathFunction_b[4];            /* '<S157>/Math Function' */
  real_T Product_dj[4];                /* '<S161>/Product' */
  real_T Add_k[4];                     /* '<S161>/Add' */
  real_T Product1_g[2];                /* '<S161>/Product1' */
  real_T Product2_d[2];                /* '<S161>/Product2' */
  real_T u_i[2];                       /* '<S161>/2' */
  real_T Product3_l[2];                /* '<S161>/Product3' */
  real_T Sum_ez[2];                    /* '<S161>/Sum' */
  real_T Gain_o[2];                    /* '<S161>/Gain' */
  real_T MultiportSelector4;           /* '<S127>/Multiport Selector4' */
  real_T Product1_ma;                  /* '<S149>/Product1' */
  real_T Divide1_c;                    /* '<S149>/Divide1' */
  real_T Sum_g4;                       /* '<S149>/Sum' */
  real_T Product_a2;                   /* '<S49>/Product' */
  real_T MathFunction_d[2];            /* '<S187>/Math Function' */
  real_T Product1_gc;                  /* '<S185>/Product1' */
  real_T p_ds3;                        /* '<S185>/|p_d^s|^3' */
  real_T Divide_f;                     /* '<S185>/Divide' */
  real_T Product_lk;                   /* '<S185>/Product' */
  real_T Gain_pz;                      /* '<S185>/Gain' */
  real_T epsilon_n2_pv;                /* '<S135>/epsilon_n^2' */
  real_T Delta2_m;                     /* '<S135>/Delta^2' */
  real_T Add_pj;                       /* '<S135>/Add' */
  real_T MathFunction_jr;              /* '<S135>/Math Function' */
  real_T Divide_km;                    /* '<S135>/Divide' */
  real_T Product1_it;                  /* '<S135>/Product1' */
  real_T Product2_ik;                  /* '<S135>/Product2' */
  real_T u2_o;                         /* '<S135>/^3//2' */
  real_T Divide1_j;                    /* '<S135>/Divide1' */
  real_T Product3_o;                   /* '<S135>/Product3' */
  real_T Product1_at;                  /* '<S139>/Product1' */
  real_T MathFunction_la[2];           /* '<S143>/Math Function' */
  real_T Divide2[2];                   /* '<S139>/Divide2' */
  real_T MathFunction_g[2];            /* '<S142>/Math Function' */
  real_T Product2_la[2];               /* '<S139>/Product2' */
  real_T MathFunction_p;               /* '<S139>/Math Function' */
  real_T Divide1_j0[2];                /* '<S139>/Divide1' */
  real_T Subtract1_k[2];               /* '<S139>/Subtract1' */
  real_T Product_kg;                   /* '<S139>/Product' */
  real_T Subtract_c;                   /* '<S139>/Subtract' */
  real_T Sum_m;                        /* '<S135>/Sum' */
  real_T Product1_m1;                  /* '<S49>/Product1' */
  real_T VectorConcatenate_a[3];       /* '<S49>/Vector Concatenate' */
  real_T Add1_c[3];                    /* '<S59>/Add1' */
  real_T Product1_d[3];                /* '<S36>/Product1' */
  real_T TrigonometricFunction_o;      /* '<S132>/Trigonometric Function' */
  real_T TrigonometricFunction1_j;     /* '<S132>/Trigonometric Function1' */
  real_T Derivative;                   /* '<S118>/Derivative' */
  real_T Product_pl[2];                /* '<S132>/Product' */
  real_T VectorConcatenate_b[3];       /* '<S44>/Vector Concatenate' */
  real_T epsilon_n2_m;                 /* '<S136>/epsilon_n^2' */
  real_T Delta2_f;                     /* '<S136>/Delta^2' */
  real_T Add_pb;                       /* '<S136>/Add' */
  real_T sqrt_d;                       /* '<S136>/sqrt' */
  real_T Divide_ht;                    /* '<S136>/Divide' */
  real_T Divide_a;                     /* '<S186>/Divide' */
  real_T Product_bl;                   /* '<S136>/Product' */
  real_T VectorConcatenate_g[3];       /* '<S50>/Vector Concatenate' */
  real_T Add_h[3];                     /* '<S60>/Add' */
  real_T Sum_fd[3];                    /* '<S36>/Sum' */
  real_T Product_k3[3];                /* '<S51>/Product' */
  real_T S12;                          /* '<S54>/S12' */
  real_T Sr[9];                        /* '<S54>/S(r)' */
  real_T MathFunction_ii[9];           /* '<S55>/Math Function' */
  real_T Product1_kl[3];               /* '<S51>/Product1' */
  real_T Gain_mj[3];                   /* '<S51>/Gain' */
  real_T Subtract_dp[3];               /* '<S51>/Subtract' */
  real_T Product1_bi[3];               /* '<S33>/Product1' */
  real_T Sum_b[3];                     /* '<S33>/Sum' */
  real_T tauSwitch[3];                 /* '<S26>/tau Switch' */
  real_T MatrixConcatenate_d[6];       /* '<S128>/Matrix Concatenate' */
  real_T MathFunction_hoy[6];          /* '<S57>/Math Function' */
  real_T Product2_c[2];                /* '<S35>/Product2' */
  real_T Product3_e[2];                /* '<S35>/Product3' */
  real_T Subtract_h[2];                /* '<S35>/Subtract' */
  real_T Product4_b[2];                /* '<S35>/Product4' */
  real_T Gain_en[2];                   /* '<S35>/Gain' */
  real_T Product_ak[3];                /* '<S40>/Product' */
  real_T Pseudoinverse[15];            /* '<S98>/Pseudoinverse' */
  real_T Product_pk[5];                /* '<S98>/Product' */
  real_T f_1tou_1;                     /* '<S100>/f_1 to u_1' */
  real_T Sum_c;                        /* '<S99>/Sum' */
  real_T f_2000391;                    /* '<S101>/f_2 < 0.00391' */
  real_T f_2006731f_2000391;           /* '<S101>/f_2 < 0.06731 && f_2 >= 0.00391' */
  real_T f_2006731;                    /* '<S101>/f_2 => 0.06731' */
  real_T MultiportSwitch_iu;           /* '<S101>/Multiport Switch' */
  real_T Sum1_d;                       /* '<S99>/Sum1' */
  real_T f_3tou_3;                     /* '<S102>/f_3 to u_3' */
  real_T Sum2;                         /* '<S99>/Sum2' */
  real_T f_400451;                     /* '<S103>/f_4 < 0.0451' */
  real_T f_400451_n;                   /* '<S103>/f_4 >= 0.0451 ' */
  real_T MultiportSwitch_e;            /* '<S103>/Multiport Switch' */
  real_T Sum3;                         /* '<S99>/Sum3' */
  real_T DeadZone001_k;                /* '<S104>/Dead Zone +-0.01' */
  real_T f_50;                         /* '<S104>/f_5 < 0' */
  real_T f_50_f;                       /* '<S104>/f_5 > 0' */
  real_T MultiportSwitch_o;            /* '<S104>/Multiport Switch' */
  real_T Saturation_g[7];              /* '<S30>/Saturation' */
  real_T QTMIn2Error;                  /* '<S188>/QTM In2 Error' */
  real_T QTMIn9Residual;               /* '<S188>/QTM In9 Residual' */
  real_T tauSwitch1[7];                /* '<S215>/tau Switch1' */
  real_T TmpHiddenBufferAtToFileInport1[65];/* 'synthesized block' */
  real_T VectorConcatenate1[3];        /* '<S128>/Vector Concatenate1' */
  real_T QTMIn5zcoordmm;               /* '<S188>/QTM In5 z-coord [mm]' */
  real_T mm2mz;                        /* '<S188>/mm2m z' */
  real_T QTMIn8rolldeg;                /* '<S188>/QTM In8 roll [deg]' */
  real_T d2rroll;                      /* '<S188>/d2r roll' */
  real_T QTMIn7pitchdeg;               /* '<S188>/QTM In7 pitch [deg]' */
  real_T d2rpitch;                     /* '<S188>/d2r pitch' */
  real_T Derivative_e[6];              /* '<S188>/Derivative' */
  real_T sintheta[3];                  /* '<S190>/sin(theta)' */
  real_T costheta[3];                  /* '<S190>/cos(theta)' */
  real_T R11_j;                        /* '<S190>/R11' */
  real_T R12_m;                        /* '<S190>/R12' */
  real_T R13;                          /* '<S190>/R13' */
  real_T R21_p;                        /* '<S190>/R21 ' */
  real_T R22_c;                        /* '<S190>/R22' */
  real_T R23;                          /* '<S190>/R23' */
  real_T R31;                          /* '<S190>/R31 ' */
  real_T R32;                          /* '<S190>/R32' */
  real_T R33;                          /* '<S190>/R33' */
  real_T Reshape9x13x3[9];             /* '<S190>/Reshape 9x1->3x3' */
  real_T Inverse[9];                   /* '<S188>/Inverse' */
  real_T MatrixConcatenate2[36];       /* '<S188>/Matrix Concatenate2' */
  real_T Product_l3[6];                /* '<S188>/Product' */
  real_T QTMIn1FN;                     /* '<S188>/QTM In1 FN' */
  real_T eta[3];                       /* '<S191>/Integrator' */
  real_T bias[3];                      /* '<S191>/Integrator3' */
  real_T Saturation_b;                 /* '<S196>/Saturation' */
  real_T Sign_ds;                      /* '<S196>/Sign' */
  real_T Gain_h;                       /* '<S196>/Gain' */
  real_T Sum1_js;                      /* '<S196>/Sum1' */
  real_T MathFunction_gw;              /* '<S196>/Math Function' */
  real_T Sum_eo;                       /* '<S196>/Sum' */
  real_T Sum2_l[3];                    /* '<S191>/Sum2' */
  real_T Saturation_i1;                /* '<S197>/Saturation' */
  real_T Sign_p;                       /* '<S197>/Sign' */
  real_T Gain_p2;                      /* '<S197>/Gain' */
  real_T Sum1_c;                       /* '<S197>/Sum1' */
  real_T MathFunction_if;              /* '<S197>/Math Function' */
  real_T Sum_c0;                       /* '<S197>/Sum' */
  real_T TmpHiddenBufferAtK2Inport1[3];/* 'synthesized block' */
  real_T K2[3];                        /* '<S191>/K2' */
  real_T K3[3];                        /* '<S191>/K3' */
  real_T K4[3];                        /* '<S191>/K4' */
  real_T Row1;                         /* '<S194>/Row1' */
  real_T Row2;                         /* '<S194>/Row2' */
  real_T Row3;                         /* '<S194>/Row3' */
  real_T Row1_j;                       /* '<S195>/Row1' */
  real_T Row2_o;                       /* '<S195>/Row2' */
  real_T Row3_a;                       /* '<S195>/Row3' */
  real_T u_1tof_1_p1;                  /* '<S199>/u_1 to f_1' */
  real_T u_205_g;                      /* '<S200>/u_2 < -0.5' */
  real_T u_201u_202_k;                 /* '<S200>/u_2 < -0.1 && u_2 >= -0.2' */
  real_T u_20_n;                       /* '<S200>/u_2 => 0' */
  real_T MultiportSwitch_d;            /* '<S200>/Multiport Switch' */
  real_T u_3tof_3_d;                   /* '<S201>/u_3 to f_3' */
  real_T u_401_d;                      /* '<S202>/u_4 < -0.1' */
  real_T u_401_hy;                     /* '<S202>/u_4 >= -0.1' */
  real_T MultiportSwitch_b;            /* '<S202>/Multiport Switch' */
  real_T DeadZone001_e;                /* '<S203>/Dead Zone +-0.01' */
  real_T u_50_j;                       /* '<S203>/u_5 < 0' */
  real_T u_50_ns;                      /* '<S203>/u_5 > 0' */
  real_T MultiportSwitch_l;            /* '<S203>/Multiport Switch' */
  real_T TmpHiddenBufferAtProduct1Inpo_f[5];/* '<S192>/u_act to f_act' */
  real_T Product1_c3[3];               /* '<S192>/Product1' */
  real_T Sum1_ei[3];                   /* '<S191>/Sum1' */
  real_T Product1_n[3];                /* '<S191>/Product1' */
  real_T Sum8[3];                      /* '<S191>/Sum8' */
  real_T Product_ly[3];                /* '<S191>/Product' */
  real_T x_dot;                        /* '<S193>/Fcn' */
  real_T y_dot;                        /* '<S193>/Fcn1' */
  real_T psi_dot;                      /* '<S193>/Fcn2' */
  real_T Sum3_b[3];                    /* '<S191>/Sum3' */
  real_T invT_b[3];                    /* '<S191>/inv(T_b)' */
  real_T Sum7[3];                      /* '<S191>/Sum7' */
  real_T SITzAI0;                      /* '<S188>/SIT zAI0' */
  real_T SITzAI1;                      /* '<S188>/SIT zAI1' */
  real_T SITzAI2;                      /* '<S188>/SIT zAI2' */
  real_T Inverse_m[9];                 /* '<S22>/Inverse' */
  real_T Saturation_i4;                /* '<S216>/Saturation' */
  real_T Saturation1;                  /* '<S216>/Saturation1' */
  real_T Saturation2;                  /* '<S216>/Saturation2' */
  real_T planttau_surge;               /* '<S216>/plant tau_surge' */
  real_T planttau_sway;                /* '<S216>/plant tau_sway' */
  real_T planttau_yaw;                 /* '<S216>/plant tau_yaw' */
  real_T BatteryBowThruster;           /* '<S224>/Battery Bow Thruster' */
  real_T BatteryMain;                  /* '<S224>/Battery Main' */
  real_T BatteryServo;                 /* '<S224>/Battery Servo' */
  real_T tau1[3];                      /* '<S225>/tau1' */
  real_T tau2[3];                      /* '<S225>/tau2' */
  real_T tau3[3];                      /* '<S225>/tau3' */
  real_T tau4[3];                      /* '<S225>/tau4' */
  real_T tau5[3];                      /* '<S225>/tau5' */
  real_T tau6[3];                      /* '<S225>/tau6' */
  real_T plantBTpower;                 /* '<S225>/plant BT power' */
  real_T plantVSPspeed;                /* '<S225>/plant VSP speed' */
  real_T plantu_1;                     /* '<S225>/plant u_1' */
  real_T plantu_2;                     /* '<S225>/plant u_2' */
  real_T plantu_3;                     /* '<S225>/plant u_3' */
  real_T plantu_4;                     /* '<S225>/plant u_4' */
  real_T plantu_5;                     /* '<S225>/plant u_5' */
  real_T fact1;                        /* '<S225>/fact1' */
  real_T fact2;                        /* '<S225>/fact2' */
  real_T fact3;                        /* '<S225>/fact3' */
  real_T fact4;                        /* '<S225>/fact4' */
  real_T fact5;                        /* '<S225>/fact5' */
  real_T taux;                         /* '<S225>/taux' */
  real_T tauy;                         /* '<S225>/tauy' */
  real_T tauyaw;                       /* '<S225>/tauyaw' */
  real_T omega_qy;                     /* '<S225>/omega_qy' */
  real_T omegaqx;                      /* '<S225>/omegaqx' */
  real_T CSE1_rdegs;                   /* '<S226>/CSE1_r [deg//s]' */
  real_T CSE1_ums;                     /* '<S226>/CSE1_u [m//s]' */
  real_T CSE1_vms;                     /* '<S226>/CSE1_v [m//s]' */
  real_T QSError;                      /* '<S226>/QS Error' */
  real_T QSFrame;                      /* '<S226>/QS Frame' */
  real_T Sum_gn[3];                    /* '<S227>/Sum' */
  real_T Sum1_i[3];                    /* '<S227>/Sum1' */
  real_T Sum2_d[3];                    /* '<S227>/Sum2' */
  real_T psideg;                       /* '<S227>/psi [deg]' */
  real_T psipsiddeg;                   /* '<S227>/psi-psid [deg]' */
  real_T psiLOSpsideg;                 /* '<S227>/psiLOS-psi [deg]' */
  real_T psiLOSpsiddeg;                /* '<S227>/psiLOS-psid [deg]' */
  real_T psi_LOSdeg;                   /* '<S227>/psi_LOS [deg]' */
  real_T psiddeg;                      /* '<S227>/psid [deg]' */
  real_T psi_plot[3];                  /* '<S227>/psi_plot' */
  real_T qxm;                          /* '<S227>/qx [m]' */
  real_T qxxm;                         /* '<S227>/qx-x [m]' */
  real_T qxxdm1;                       /* '<S227>/qx-xd [m]1' */
  real_T qym;                          /* '<S227>/qy [m]' */
  real_T qyym;                         /* '<S227>/qy-y [m]' */
  real_T qyydm1;                       /* '<S227>/qy-yd [m]1' */
  real_T xm;                           /* '<S227>/x [m]' */
  real_T xxdm;                         /* '<S227>/x-xd [m]' */
  real_T xdm;                          /* '<S227>/xd [m]' */
  real_T x_plot[3];                    /* '<S227>/x_plot' */
  real_T ym;                           /* '<S227>/y [m]' */
  real_T yydm;                         /* '<S227>/y-yd [m]' */
  real_T ydm;                          /* '<S227>/yd [m]' */
  real_T y_plot[3];                    /* '<S227>/y_plot' */
  real_T splot;                        /* '<S227>/splot' */
  real_T Integrator_e[3];              /* '<S222>/Integrator' */
  real_T Integrator1_o[3];             /* '<S222>/Integrator1' */
  real_T R11_c;                        /* '<S223>/R11' */
  real_T R21_c;                        /* '<S223>/R21' */
  real_T R12_j;                        /* '<S223>/R12' */
  real_T R22_f;                        /* '<S223>/R22' */
  real_T Rpsi_o[9];                    /* '<S223>/R(psi)' */
  real_T Product1_bo[3];               /* '<S222>/Product1' */
  real_T Sum_mk[3];                    /* '<S222>/Sum' */
  real_T Product2_b[3];                /* '<S222>/Product2' */
  real_T Product3_d[3];                /* '<S222>/Product3' */
  real_T BT_D_Gain1;                   /* '<S217>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S217>/BT_D_Gain2' */
  real_T Add_ld;                       /* '<S217>/Add' */
  real_T BT_L_Gain1;                   /* '<S217>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S217>/BT_L_Gain2' */
  real_T Neg;                          /* '<S217>/Neg' */
  real_T Sum1_el;                      /* '<S217>/Sum1' */
  real_T Sum2_b;                       /* '<S217>/Sum2' */
  real_T Switch_f;                     /* '<S219>/Switch' */
  real_T Switch2_d;                    /* '<S219>/Switch2' */
  real_T Switch_g;                     /* '<S220>/Switch' */
  real_T Switch2_j;                    /* '<S220>/Switch2' */
  real_T Switch_a;                     /* '<S221>/Switch' */
  real_T Switch2_a;                    /* '<S221>/Switch2' */
  real_T Sign_e;                       /* '<S218>/Sign' */
  real_T PortVPS_X;                    /* '<S218>/Product1' */
  real_T PortVPS_X_d;                  /* '<S218>/-x' */
  real_T PortVSP_Y;                    /* '<S218>/Product2' */
  real_T PortVSP_Y_g;                  /* '<S218>/-y' */
  real_T StarboardVSP_X;               /* '<S218>/Product3' */
  real_T StarboardVSP_Y;               /* '<S218>/Product4' */
  real_T Servo1;                       /* '<S218>/Servo1' */
  real_T Servo2;                       /* '<S218>/Servo2' */
  real_T Servo3;                       /* '<S218>/Servo3' */
  real_T Servo4;                       /* '<S218>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S218>/VPS_Speed_Gain' */
  real_T Sum_di;                       /* '<S218>/Sum' */
  real_T VSPSPort;                     /* '<S218>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S218>/VSPS Starboard' */
  real_T S12_a;                        /* '<S156>/S12' */
  real_T S_2psi_ds2[4];                /* '<S156>/S_2(psi_d^s^2)' */
  real_T S12_ao;                       /* '<S155>/S12' */
  real_T S_2psi_ds[4];                 /* '<S155>/S_2(psi_d^s)' */
  real_T R11_jo;                       /* '<S153>/R11' */
  real_T R21_m;                        /* '<S153>/R21' */
  real_T R12_ml;                       /* '<S153>/R12' */
  real_T R22_cv;                       /* '<S153>/R22' */
  real_T R_2psi_d[4];                  /* '<S153>/R_2(psi_d)' */
  uint16_T Gain1_f;                    /* '<S68>/Gain1' */
  uint16_T Sum_ku;                     /* '<S68>/Sum' */
  uint16_T Gain_pm;                    /* '<S70>/Gain' */
  uint16_T Sum_h;                      /* '<S70>/Sum' */
  uint16_T Gain_em;                    /* '<S71>/Gain' */
  uint16_T Gain1_h;                    /* '<S71>/Gain1' */
  uint16_T Sum_fd3;                    /* '<S71>/Sum' */
  uint16_T Gain1_ab;                   /* '<S84>/Gain1' */
  uint16_T Sum_hr;                     /* '<S84>/Sum' */
  uint16_T Gain_j;                     /* '<S86>/Gain' */
  uint16_T Sum_o;                      /* '<S86>/Sum' */
  uint16_T Gain_ca;                    /* '<S87>/Gain' */
  uint16_T Gain1_l;                    /* '<S87>/Gain1' */
  uint16_T Sum_j;                      /* '<S87>/Sum' */
  uint16_T Gain1_fl;                   /* '<S101>/Gain1' */
  uint16_T Sum_bs;                     /* '<S101>/Sum' */
  uint16_T Gain_bp;                    /* '<S103>/Gain' */
  uint16_T Sum_lm;                     /* '<S103>/Sum' */
  uint16_T Gain_ep;                    /* '<S104>/Gain' */
  uint16_T Gain1_g;                    /* '<S104>/Gain1' */
  uint16_T Sum_ms;                     /* '<S104>/Sum' */
  uint16_T Gain1_n;                    /* '<S200>/Gain1' */
  uint16_T Sum_lo;                     /* '<S200>/Sum' */
  uint16_T Gain_n;                     /* '<S202>/Gain' */
  uint16_T Sum_mo;                     /* '<S202>/Sum' */
  uint16_T Gain_ji;                    /* '<S203>/Gain' */
  uint16_T Gain1_i;                    /* '<S203>/Gain1' */
  uint16_T Sum_a;                      /* '<S203>/Sum' */
  uint8_T Compare;                     /* '<S72>/Compare' */
  uint8_T Compare_i;                   /* '<S74>/Compare' */
  uint8_T Compare_g;                   /* '<S73>/Compare' */
  uint8_T Sum1_k;                      /* '<S68>/Sum1' */
  uint8_T Compare_l;                   /* '<S75>/Compare' */
  uint8_T Compare_la;                  /* '<S76>/Compare' */
  uint8_T Compare_it;                  /* '<S77>/Compare' */
  uint8_T Compare_o;                   /* '<S78>/Compare' */
  uint8_T Compare_le;                  /* '<S80>/Compare' */
  uint8_T Compare_k;                   /* '<S79>/Compare' */
  uint8_T Compare_f;                   /* '<S88>/Compare' */
  uint8_T Compare_b;                   /* '<S90>/Compare' */
  uint8_T Compare_ii;                  /* '<S89>/Compare' */
  uint8_T Sum1_kv;                     /* '<S84>/Sum1' */
  uint8_T Compare_h;                   /* '<S91>/Compare' */
  uint8_T Compare_l3;                  /* '<S92>/Compare' */
  uint8_T Compare_e;                   /* '<S93>/Compare' */
  uint8_T Compare_m;                   /* '<S94>/Compare' */
  uint8_T Compare_iu;                  /* '<S96>/Compare' */
  uint8_T Compare_kv;                  /* '<S95>/Compare' */
  uint8_T Compare_ku;                  /* '<S105>/Compare' */
  uint8_T Compare_e2;                  /* '<S107>/Compare' */
  uint8_T Compare_kb;                  /* '<S106>/Compare' */
  uint8_T Sum1_m;                      /* '<S101>/Sum1' */
  uint8_T Compare_ik;                  /* '<S108>/Compare' */
  uint8_T Compare_e5;                  /* '<S109>/Compare' */
  uint8_T Compare_a;                   /* '<S110>/Compare' */
  uint8_T Compare_km;                  /* '<S111>/Compare' */
  uint8_T Compare_l4;                  /* '<S113>/Compare' */
  uint8_T Compare_og;                  /* '<S112>/Compare' */
  uint8_T Compare_by;                  /* '<S204>/Compare' */
  uint8_T Compare_l2;                  /* '<S206>/Compare' */
  uint8_T Compare_hq;                  /* '<S205>/Compare' */
  uint8_T Sum1_a;                      /* '<S200>/Sum1' */
  uint8_T Compare_n;                   /* '<S207>/Compare' */
  uint8_T Compare_lj;                  /* '<S208>/Compare' */
  uint8_T Compare_p;                   /* '<S209>/Compare' */
  uint8_T Compare_fg;                  /* '<S210>/Compare' */
  uint8_T Compare_c;                   /* '<S212>/Compare' */
  uint8_T Compare_kd;                  /* '<S211>/Compare' */
  boolean_T LogicalOperator;           /* '<S68>/Logical Operator' */
  boolean_T LogicalOperator_n;         /* '<S84>/Logical Operator' */
  boolean_T LowerRelop1;               /* '<S178>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S178>/UpperRelop' */
  boolean_T LowerRelop1_j;             /* '<S179>/LowerRelop1' */
  boolean_T UpperRelop_p;              /* '<S179>/UpperRelop' */
  boolean_T LogicalOperator_g;         /* '<S101>/Logical Operator' */
  boolean_T LogicalOperator_j;         /* '<S200>/Logical Operator' */
  boolean_T LowerRelop1_g;             /* '<S219>/LowerRelop1' */
  boolean_T UpperRelop_p1;             /* '<S219>/UpperRelop' */
  boolean_T LowerRelop1_n;             /* '<S220>/LowerRelop1' */
  boolean_T UpperRelop_k;              /* '<S220>/UpperRelop' */
  boolean_T LowerRelop1_b;             /* '<S221>/LowerRelop1' */
  boolean_T UpperRelop_c;              /* '<S221>/UpperRelop' */
} BlockIO_TemplateNIPID;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Product_DWORK1;               /* '<S137>/Product' */
  real_T Product2_DWORK1[4];           /* '<S139>/Product2' */
  real_T Pseudoinverse_X[15];          /* '<S98>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S98>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S98>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S98>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S98>/Pseudoinverse' */
  real_T Inverse_DWORK3[9];            /* '<S188>/Inverse' */
  real_T Inverse_DWORK4[9];            /* '<S188>/Inverse' */
  real_T Inverse_DWORK4_d[9];          /* '<S22>/Inverse' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK;                  /* '<S118>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } Derivative_RWORK_e;                /* '<S188>/Derivative' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<S19>/To File' */

  int32_T Inverse_DWORK2[3];           /* '<S188>/Inverse' */
  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  uint32_T Sum1_DWORK1;                /* '<S68>/Sum1' */
  uint32_T Sum1_DWORK1_d;              /* '<S101>/Sum1' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S68>/Sum' */
  uint32_T Sum_DWORK1_p;               /* '<S101>/Sum' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S35>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S35>/Integrator1' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<S19>/To File' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_l;                /* '<S191>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_k;                /* '<S222>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_d;               /* '<S222>/Integrator1' */

  int_T LinearSimulator_MODE;          /* '<S22>/Linear Simulator' */
  int_T CSE1actuator_MODE;             /* '<S22>/CSE1 actuator' */
  uint8_T SignalProbe_DWORK1[14];      /* '<Root>/SignalProbe' */
} D_Work_TemplateNIPID;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S35>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S35>/Integrator1' */
  real_T Integrator_CSTATE_o[3];       /* '<S40>/Integrator' */
  real_T Integrator4_CSTATE[3];        /* '<S191>/Integrator4' */
  real_T Integrator2_CSTATE[2];        /* '<S35>/Integrator2' */
  real_T Integrator_CSTATE_l[3];       /* '<S191>/Integrator' */
  real_T Integrator3_CSTATE[3];        /* '<S191>/Integrator3' */
  real_T Integrator_CSTATE_m[3];       /* '<S222>/Integrator' */
  real_T Integrator1_CSTATE_m[3];      /* '<S222>/Integrator1' */
} ContinuousStates_TemplateNIPID;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S35>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S35>/Integrator1' */
  real_T Integrator_CSTATE_o[3];       /* '<S40>/Integrator' */
  real_T Integrator4_CSTATE[3];        /* '<S191>/Integrator4' */
  real_T Integrator2_CSTATE[2];        /* '<S35>/Integrator2' */
  real_T Integrator_CSTATE_l[3];       /* '<S191>/Integrator' */
  real_T Integrator3_CSTATE[3];        /* '<S191>/Integrator3' */
  real_T Integrator_CSTATE_m[3];       /* '<S222>/Integrator' */
  real_T Integrator1_CSTATE_m[3];      /* '<S222>/Integrator1' */
} StateDerivatives_TemplateNIPID;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[2];      /* '<S35>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S35>/Integrator1' */
  boolean_T Integrator_CSTATE_o[3];    /* '<S40>/Integrator' */
  boolean_T Integrator4_CSTATE[3];     /* '<S191>/Integrator4' */
  boolean_T Integrator2_CSTATE[2];     /* '<S35>/Integrator2' */
  boolean_T Integrator_CSTATE_l[3];    /* '<S191>/Integrator' */
  boolean_T Integrator3_CSTATE[3];     /* '<S191>/Integrator3' */
  boolean_T Integrator_CSTATE_m[3];    /* '<S222>/Integrator' */
  boolean_T Integrator1_CSTATE_m[3];   /* '<S222>/Integrator1' */
} StateDisabled_TemplateNIPID;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S35>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S35>/Integrator1' */
  ZCSigState Integrator_Reset_ZCE_k;   /* '<S40>/Integrator' */
  ZCSigState Integrator4_Reset_ZCE;    /* '<S191>/Integrator4' */
  ZCSigState Integrator2_Reset_ZCE;    /* '<S35>/Integrator2' */
  ZCSigState Integrator_Reset_ZCE_g;   /* '<S191>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_p;   /* '<S222>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE_d;  /* '<S222>/Integrator1' */
} PrevZCSigStates_TemplateNIPID;

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
} ConstParam_TemplateNIPID;

/* Backward compatible GRT Identifiers */
#define rtB                            TemplateNIPID_B
#define BlockIO                        BlockIO_TemplateNIPID
#define rtX                            TemplateNIPID_X
#define ContinuousStates               ContinuousStates_TemplateNIPID
#define rtP                            TemplateNIPID_P
#define Parameters                     Parameters_TemplateNIPID
#define rtDWork                        TemplateNIPID_DWork
#define D_Work                         D_Work_TemplateNIPID
#define ConstParam                     ConstParam_TemplateNIPID
#define rtcP                           TemplateNIPID_ConstP
#define rtPrevZCSigState               TemplateNIPID_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_TemplateNIPID

/* Parameters (auto storage) */
struct Parameters_TemplateNIPID_ {
  real_T ControlInputSelector_Value;   /* Expression: 1
                                        * '<S1>/Control Input Selector'
                                        */
  real_T ControlModeSelector_Value;    /* Expression: 2
                                        * '<S1>/Control Mode Selector'
                                        */
  real_T EnableCSE1_Value;             /* Expression: 0
                                        * '<S1>/Enable CSE1'
                                        */
  real_T tauxscale_Value;              /* Expression: 1
                                        * '<S1>/tauxscale'
                                        */
  real_T tauyscale_Value;              /* Expression: 1
                                        * '<S1>/tauyscale'
                                        */
  real_T tauyawscale_Value;            /* Expression: 1
                                        * '<S1>/tauyawscale'
                                        */
  real_T offsetu1_Value;               /* Expression: 0
                                        * '<S1>/offset u1'
                                        */
  real_T offsetu2_Value;               /* Expression: 0
                                        * '<S1>/offset u2'
                                        */
  real_T offsetu3_Value;               /* Expression: 0
                                        * '<S1>/offset u3'
                                        */
  real_T offsetu4_Value;               /* Expression: 0
                                        * '<S1>/offset u4'
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
  real_T ctrl1Kppsi_Value;             /* Expression: 0.5*3
                                        * '<S8>/ctrl1Kppsi'
                                        */
  real_T ctrl1Kipsi_Value;             /* Expression: 0
                                        * '<S8>/ctrl1Kipsi'
                                        */
  real_T ctrl1ResetIntegrator_Value;   /* Expression: 0
                                        * '<S8>/ctrl1 Reset Integrator '
                                        */
  real_T ctrl1Kdpsi_Value;             /* Expression: 5
                                        * '<S8>/ctrl1Kdpsi'
                                        */
  real_T ctrl1Kdx_Value;               /* Expression: 50
                                        * '<S8>/ctrl1Kdx'
                                        */
  real_T ctrl1Kdy_Value;               /* Expression: 30
                                        * '<S8>/ctrl1Kdy'
                                        */
  real_T ctrl1Kix_Value;               /* Expression: 0
                                        * '<S8>/ctrl1Kix'
                                        */
  real_T ctrl1Kiy_Value;               /* Expression: 0
                                        * '<S8>/ctrl1Kiy'
                                        */
  real_T ctrl1Kpx_Value;               /* Expression: 2*1.5*2
                                        * '<S8>/ctrl1Kpx'
                                        */
  real_T ctrl1Kpy_Value;               /* Expression: 2*10*2
                                        * '<S8>/ctrl1Kpy'
                                        */
  real_T u_Value;                      /* Expression: 0
                                        * '<S13>/12'
                                        */
  real_T u_Value_k;                    /* Expression: 0
                                        * '<S13>/21'
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
                                        * '<S14>/12'
                                        */
  real_T u_Value_a;                    /* Expression: 0
                                        * '<S14>/13'
                                        */
  real_T u_Value_c;                    /* Expression: 0
                                        * '<S14>/21'
                                        */
  real_T u_Value_o;                    /* Expression: 0
                                        * '<S14>/23'
                                        */
  real_T u_Value_b;                    /* Expression: 0
                                        * '<S14>/31'
                                        */
  real_T u_Value_f;                    /* Expression: 0
                                        * '<S14>/32'
                                        */
  real_T ctrl2Kdx_Value;               /* Expression: 50*0
                                        * '<S9>/ctrl2Kdx'
                                        */
  real_T ctrl2Kdy_Value;               /* Expression: 30*0
                                        * '<S9>/ctrl2Kdy'
                                        */
  real_T ctrl2Kdpsi_Value;             /* Expression: 5*0
                                        * '<S9>/ctrl2Kdpsi'
                                        */
  real_T u_Value_lr;                   /* Expression: 0
                                        * '<S15>/12'
                                        */
  real_T u_Value_j;                    /* Expression: 0
                                        * '<S15>/13'
                                        */
  real_T u_Value_d;                    /* Expression: 0
                                        * '<S15>/21'
                                        */
  real_T u_Value_g;                    /* Expression: 0
                                        * '<S15>/23'
                                        */
  real_T u_Value_n;                    /* Expression: 0
                                        * '<S15>/31'
                                        */
  real_T u_Value_jc;                   /* Expression: 0
                                        * '<S15>/32'
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
  real_T u_Value_e;                    /* Expression: 0
                                        * '<S16>/12'
                                        */
  real_T u_Value_ox;                   /* Expression: 0
                                        * '<S16>/13'
                                        */
  real_T u_Value_eu;                   /* Expression: 0
                                        * '<S16>/21'
                                        */
  real_T u_Value_dc;                   /* Expression: 0
                                        * '<S16>/23'
                                        */
  real_T u_Value_p;                    /* Expression: 0
                                        * '<S16>/31'
                                        */
  real_T u_Value_bp;                   /* Expression: 0
                                        * '<S16>/32'
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
                                        * '<S25>/l_x1'
                                        */
  real_T l_x1_Gain;                    /* Expression: -1
                                        * '<S25>/-l_x1'
                                        */
  real_T l_x2_Value;                   /* Expression: 0.45
                                        * '<S25>/l_x2'
                                        */
  real_T l_x2_Gain;                    /* Expression: -1
                                        * '<S25>/-l_x2'
                                        */
  real_T l_y2_Value;                   /* Expression: 0.055
                                        * '<S25>/l_y2'
                                        */
  real_T l_y2_Gain;                    /* Expression: -1
                                        * '<S25>/-l_y2'
                                        */
  real_T B_11_Value;                   /* Expression: 1
                                        * '<S25>/B_11'
                                        */
  real_T B_21_Value;                   /* Expression: 0
                                        * '<S25>/B_21'
                                        */
  real_T l_y1_Value;                   /* Expression: 0.055
                                        * '<S25>/l_y1'
                                        */
  real_T B_12_Value;                   /* Expression: 0
                                        * '<S25>/B_12'
                                        */
  real_T B_22_Value;                   /* Expression: 1
                                        * '<S25>/B_22'
                                        */
  real_T B_13_Value;                   /* Expression: 1
                                        * '<S25>/B_13'
                                        */
  real_T B_23_Value;                   /* Expression: 0
                                        * '<S25>/B_23'
                                        */
  real_T B_14_Value;                   /* Expression: 0
                                        * '<S25>/B_14'
                                        */
  real_T B_24_Value;                   /* Expression: 1
                                        * '<S25>/B_24'
                                        */
  real_T B_15_Value;                   /* Expression: 0
                                        * '<S25>/B_15'
                                        */
  real_T B_25_Value;                   /* Expression: 1
                                        * '<S25>/B_25'
                                        */
  real_T l_x3_Value;                   /* Expression: 0.385
                                        * '<S25>/l_x3'
                                        */
  real_T N_r_Value;                    /* Expression: -1.900
                                        * '<S24>/N_r'
                                        */
  real_T N_r_Gain;                     /* Expression: -1
                                        * '<S24>/-N_r'
                                        */
  real_T N_v_Value;                    /* Expression: 0.18140
                                        * '<S24>/N_v'
                                        */
  real_T N_v_Gain;                     /* Expression: -1
                                        * '<S24>/-N_v'
                                        */
  real_T X_u_Value;                    /* Expression: -0.59739
                                        * '<S24>/X_u'
                                        */
  real_T X_u_Gain;                     /* Expression: -1
                                        * '<S24>/-X_u'
                                        */
  real_T Y_v_Value;                    /* Expression: -3.50625
                                        * '<S24>/Y_v'
                                        */
  real_T Y_v_Gain;                     /* Expression: -1
                                        * '<S24>/-Y_v'
                                        */
  real_T Y_r_Value;                    /* Expression: -7.250
                                        * '<S24>/Y_r'
                                        */
  real_T Y_vr_Gain;                    /* Expression: -1
                                        * '<S24>/-Y_vr'
                                        */
  real_T D_L_12_Value;                 /* Expression: 0
                                        * '<S24>/D_L_12'
                                        */
  real_T D_L_13_Value;                 /* Expression: 0
                                        * '<S24>/D_L_13'
                                        */
  real_T D_L_21_Value;                 /* Expression: 0
                                        * '<S24>/D_L_21'
                                        */
  real_T D_L_31_Value;                 /* Expression: 0
                                        * '<S24>/D_L_31'
                                        */
  real_T m_Value;                      /* Expression: 17.6
                                        * '<S23>/m'
                                        */
  real_T X_udot_Value;                 /* Expression: -2.0
                                        * '<S23>/X_udot'
                                        */
  real_T M_21_Value;                   /* Expression: 0
                                        * '<S23>/M_21'
                                        */
  real_T M_31_Value;                   /* Expression: 0
                                        * '<S23>/M_31'
                                        */
  real_T M_12_Value;                   /* Expression: 0
                                        * '<S23>/M_12'
                                        */
  real_T Y_vdot_Value;                 /* Expression: -10.0
                                        * '<S23>/Y_vdot'
                                        */
  real_T x_g_Value;                    /* Expression: 0.03
                                        * '<S23>/x_g'
                                        */
  real_T N_vdot_Value;                 /* Expression: -0.0
                                        * '<S23>/N_vdot'
                                        */
  real_T M_13_Value;                   /* Expression: 0
                                        * '<S23>/M_13'
                                        */
  real_T Y_rdot_Value;                 /* Expression: 0.0
                                        * '<S23>/Y_rdot'
                                        */
  real_T I_z_Value;                    /* Expression: 1.760
                                        * '<S23>/I_z'
                                        */
  real_T N_rdot_Value;                 /* Expression: -1.0
                                        * '<S23>/N_rdot'
                                        */
  real_T PS3u_1_Gain;                  /* Expression: 1
                                        * '<S28>/PS3 u_1'
                                        */
  real_T u_1tof_1_XData[39];           /* Expression: [-1.0000 -0.9500 -0.9000 -0.8500 -0.8000 -0.7500 -0.7000 -0.6500 -0.6000 -0.5500 -0.5000 -0.4500 -0.4000 -0.3500 -0.3000 -0.2500 -0.2000 -0.1500 -0.1000 -0.0500 0 0.0500 0.1000 0.1500 0.2000 0.2500 0.3000 0.3500 0.4000 0.4500 0.5000 0.5500 0.6000 0.6500 0.7000 0.7500 0.8000 0.8500 0.9000]
                                        * '<S67>/u_1 to f_1'
                                        */
  real_T u_1tof_1_YData[39];           /* Expression: [-0.6829 -0.6369 -0.5785 -0.5165 -0.4456 -0.3725 -0.3308 -0.2827 -0.2277 -0.1517 -0.1240 -0.0769 -0.0238 0.0039 0.0377 0.0635 0.1051 0.1196 0.1412 0.1721 0.1754 0.1774 0.2104 0.2200 0.2266 0.2673 0.3025 0.3486 0.3896 0.4252 0.4782 0.5164 0.5695 0.6195 0.6723 0.7449 0.7836 0.8414 0.8987 ]
                                        * '<S67>/u_1 to f_1'
                                        */
  real_T PS3u_2_Gain;                  /* Expression: 1
                                        * '<S28>/PS3 u_2'
                                        */
  real_T Constant_Value;               /* Expression: const
                                        * '<S72>/Constant'
                                        */
  real_T Constant_Value_l;             /* Expression: const
                                        * '<S74>/Constant'
                                        */
  real_T Constant_Value_m;             /* Expression: const
                                        * '<S73>/Constant'
                                        */
  real_T Constant_Value_p;             /* Expression: const
                                        * '<S75>/Constant'
                                        */
  real_T u_205_XData[11];              /* Expression: [-1.0000
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
                                        * '<S68>/u_2 < -0.5'
                                        */
  real_T u_205_YData[11];              /* Expression: [-0.2704
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
                                        * '<S68>/u_2 < -0.5'
                                        */
  real_T u_201u_202_XData[3];          /* Expression: [-0.2000
                                          -0.1500
                                          -0.1000]
                                        * '<S68>/u_2 < -0.1 && u_2 >= -0.2'
                                        */
  real_T u_201u_202_YData[3];          /* Expression: [-0.0105
                                          0.0226
                                          0.0673]
                                        * '<S68>/u_2 < -0.1 && u_2 >= -0.2'
                                        */
  real_T u_20_XData[18];               /* Expression: [0
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
                                        * '<S68>/u_2 => 0'
                                        */
  real_T u_20_YData[18];               /* Expression: [0.0872
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
                                        * '<S68>/u_2 => 0'
                                        */
  real_T PS3u_3_Gain;                  /* Expression: 1
                                        * '<S28>/PS3 u_3'
                                        */
  real_T u_3tof_3_XData[39];           /* Expression: [-1.0000,-0.9500,-0.9000,-0.8500,-0.8000,-0.7500,-0.7000,-0.6500,-0.6000,-0.5500,-0.5000,-0.4500,-0.4000,-0.3500,-0.3000,-0.2000,-0.1500,-0.1000,-0.0500,0,0.0500,0.1000,0.1500,0.2000,0.2500,0.3000,0.3500,0.4000,0.4500,0.5000,0.5500,0.6000,0.6500,0.7000,0.7500,0.8000,0.8500,0.9500,1.0000]
                                        * '<S69>/u_3 to f_3'
                                        */
  real_T u_3tof_3_YData[39];           /* Expression: [-0.5408,-0.5036,-0.4487,-0.3802,-0.3147,-0.2525,-0.2338,-0.1568,-0.1034,-0.0647,-0.0054,0.0221,0.0572,0.0747,0.0991,0.1258,0.1385,0.1447,0.1539,0.1625,0.1712,0.1976,0.2258,0.2443,0.3058,0.3460,0.3989,0.4342,0.4932,0.5524,0.5814,0.6394,0.6851,0.7496,0.8081,0.8382,0.8665,0.8767,0.8885]
                                        * '<S69>/u_3 to f_3'
                                        */
  real_T PS3u_4_Gain;                  /* Expression: 1
                                        * '<S28>/PS3 u_4'
                                        */
  real_T Constant_Value_m0;            /* Expression: const
                                        * '<S76>/Constant'
                                        */
  real_T Constant_Value_k;             /* Expression: const
                                        * '<S77>/Constant'
                                        */
  real_T u_401_XData[15];              /* Expression: [-0.8000
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
                                        * '<S70>/u_4 < -0.1'
                                        */
  real_T u_401_YData[15];              /* Expression: [-0.5212
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
                                        * '<S70>/u_4 < -0.1'
                                        */
  real_T u_401_XData_c[13];            /* Expression: [0.0431
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
                                        * '<S70>/u_4 >= -0.1'
                                        */
  real_T u_401_YData_e[13];            /* Expression: [0.4000
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
                                        * '<S70>/u_4 >= -0.1'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S28>/PS3 u_5'
                                        */
  real_T DeadZone001_Start;            /* Expression: -0.01
                                        * '<S71>/Dead Zone +-0.01'
                                        */
  real_T DeadZone001_End;              /* Expression: 0.01
                                        * '<S71>/Dead Zone +-0.01'
                                        */
  real_T Constant_Value_f;             /* Expression: const
                                        * '<S78>/Constant'
                                        */
  real_T Constant_Value_c;             /* Expression: const
                                        * '<S79>/Constant'
                                        */
  real_T u_50_XData[10];               /* Expression: [-0.2000
                                          -0.1900
                                          -0.1700
                                          -0.1500
                                          -0.1300
                                          -0.1100
                                          -0.0900
                                          -0.0700
                                          -0.0500
                                          -0.0300]
                                        * '<S71>/u_5 < 0'
                                        */
  real_T u_50_YData[10];               /* Expression: [-1.1653
                                          -1.1010
                                          -0.9810
                                          -0.8576
                                          -0.7363
                                          -0.5877
                                          -0.4265
                                          -0.2640
                                          -0.1099
                                          0.0031]
                                        * '<S71>/u_5 < 0'
                                        */
  real_T u_50_Value;                   /* Expression: 0
                                        * '<S71>/u_5 = 0'
                                        */
  real_T u_50_XData_j[10];             /* Expression: [0.0300
                                          0.0500
                                          0.0700
                                          0.0900
                                          0.1100
                                          0.1300
                                          0.1500
                                          0.1700
                                          0.1900
                                          0.2000]
                                        * '<S71>/u_5 > 0'
                                        */
  real_T u_50_YData_g[10];             /* Expression: [0.0103
                                          0.0743
                                          0.1937
                                          0.3232
                                          0.4342
                                          0.5862
                                          0.7291
                                          0.8697
                                          0.9681
                                          1.0229]
                                        * '<S71>/u_5 > 0'
                                        */
  real_T u_1tof_1_XData_o[39];         /* Expression: [-1.0000 -0.9500 -0.9000 -0.8500 -0.8000 -0.7500 -0.7000 -0.6500 -0.6000 -0.5500 -0.5000 -0.4500 -0.4000 -0.3500 -0.3000 -0.2500 -0.2000 -0.1500 -0.1000 -0.0500 0 0.0500 0.1000 0.1500 0.2000 0.2500 0.3000 0.3500 0.4000 0.4500 0.5000 0.5500 0.6000 0.6500 0.7000 0.7500 0.8000 0.8500 0.9000]
                                        * '<S83>/u_1 to f_1'
                                        */
  real_T u_1tof_1_YData_i[39];         /* Expression: [-0.6829 -0.6369 -0.5785 -0.5165 -0.4456 -0.3725 -0.3308 -0.2827 -0.2277 -0.1517 -0.1240 -0.0769 -0.0238 0.0039 0.0377 0.0635 0.1051 0.1196 0.1412 0.1721 0.1754 0.1774 0.2104 0.2200 0.2266 0.2673 0.3025 0.3486 0.3896 0.4252 0.4782 0.5164 0.5695 0.6195 0.6723 0.7449 0.7836 0.8414 0.8987 ]
                                        * '<S83>/u_1 to f_1'
                                        */
  real_T Constant_Value_o;             /* Expression: const
                                        * '<S88>/Constant'
                                        */
  real_T Constant_Value_a;             /* Expression: const
                                        * '<S90>/Constant'
                                        */
  real_T Constant_Value_f5;            /* Expression: const
                                        * '<S89>/Constant'
                                        */
  real_T Constant_Value_pu;            /* Expression: const
                                        * '<S91>/Constant'
                                        */
  real_T u_205_XData_c[11];            /* Expression: [-1.0000
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
                                        * '<S84>/u_2 < -0.5'
                                        */
  real_T u_205_YData_e[11];            /* Expression: [-0.2704
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
                                        * '<S84>/u_2 < -0.5'
                                        */
  real_T u_201u_202_XData_k[3];        /* Expression: [-0.2000
                                          -0.1500
                                          -0.1000]
                                        * '<S84>/u_2 < -0.1 && u_2 >= -0.2'
                                        */
  real_T u_201u_202_YData_f[3];        /* Expression: [-0.0105
                                          0.0226
                                          0.0673]
                                        * '<S84>/u_2 < -0.1 && u_2 >= -0.2'
                                        */
  real_T u_20_XData_i[18];             /* Expression: [0
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
                                        * '<S84>/u_2 => 0'
                                        */
  real_T u_20_YData_j[18];             /* Expression: [0.0872
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
                                        * '<S84>/u_2 => 0'
                                        */
  real_T u_3tof_3_XData_g[39];         /* Expression: [-1.0000,-0.9500,-0.9000,-0.8500,-0.8000,-0.7500,-0.7000,-0.6500,-0.6000,-0.5500,-0.5000,-0.4500,-0.4000,-0.3500,-0.3000,-0.2000,-0.1500,-0.1000,-0.0500,0,0.0500,0.1000,0.1500,0.2000,0.2500,0.3000,0.3500,0.4000,0.4500,0.5000,0.5500,0.6000,0.6500,0.7000,0.7500,0.8000,0.8500,0.9500,1.0000]
                                        * '<S85>/u_3 to f_3'
                                        */
  real_T u_3tof_3_YData_h[39];         /* Expression: [-0.5408,-0.5036,-0.4487,-0.3802,-0.3147,-0.2525,-0.2338,-0.1568,-0.1034,-0.0647,-0.0054,0.0221,0.0572,0.0747,0.0991,0.1258,0.1385,0.1447,0.1539,0.1625,0.1712,0.1976,0.2258,0.2443,0.3058,0.3460,0.3989,0.4342,0.4932,0.5524,0.5814,0.6394,0.6851,0.7496,0.8081,0.8382,0.8665,0.8767,0.8885]
                                        * '<S85>/u_3 to f_3'
                                        */
  real_T Constant_Value_ap;            /* Expression: const
                                        * '<S92>/Constant'
                                        */
  real_T Constant_Value_lg;            /* Expression: const
                                        * '<S93>/Constant'
                                        */
  real_T u_401_XData_n[15];            /* Expression: [-0.8000
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
                                        * '<S86>/u_4 < -0.1'
                                        */
  real_T u_401_YData_d[15];            /* Expression: [-0.5212
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
                                        * '<S86>/u_4 < -0.1'
                                        */
  real_T u_401_XData_g[13];            /* Expression: [0.0431
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
                                        * '<S86>/u_4 >= -0.1'
                                        */
  real_T u_401_YData_b[13];            /* Expression: [0.4000
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
                                        * '<S86>/u_4 >= -0.1'
                                        */
  real_T DeadZone001_Start_p;          /* Expression: -0.01
                                        * '<S87>/Dead Zone +-0.01'
                                        */
  real_T DeadZone001_End_k;            /* Expression: 0.01
                                        * '<S87>/Dead Zone +-0.01'
                                        */
  real_T Constant_Value_b;             /* Expression: const
                                        * '<S94>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: const
                                        * '<S95>/Constant'
                                        */
  real_T u_50_XData_l[10];             /* Expression: [-0.2000
                                          -0.1900
                                          -0.1700
                                          -0.1500
                                          -0.1300
                                          -0.1100
                                          -0.0900
                                          -0.0700
                                          -0.0500
                                          -0.0300]
                                        * '<S87>/u_5 < 0'
                                        */
  real_T u_50_YData_c[10];             /* Expression: [-1.1653
                                          -1.1010
                                          -0.9810
                                          -0.8576
                                          -0.7363
                                          -0.5877
                                          -0.4265
                                          -0.2640
                                          -0.1099
                                          0.0031]
                                        * '<S87>/u_5 < 0'
                                        */
  real_T u_50_Value_n;                 /* Expression: 0
                                        * '<S87>/u_5 = 0'
                                        */
  real_T u_50_XData_c[10];             /* Expression: [0.0300
                                          0.0500
                                          0.0700
                                          0.0900
                                          0.1100
                                          0.1300
                                          0.1500
                                          0.1700
                                          0.1900
                                          0.2000]
                                        * '<S87>/u_5 > 0'
                                        */
  real_T u_50_YData_j[10];             /* Expression: [0.0103
                                          0.0743
                                          0.1937
                                          0.3232
                                          0.4342
                                          0.5862
                                          0.7291
                                          0.8697
                                          0.9681
                                          1.0229]
                                        * '<S87>/u_5 > 0'
                                        */
  real_T QTMIn_P1;                     /* Expression: width
                                        * '<S188>/QTM In'
                                        */
  real_T QTMIn_P2;                     /* Expression: dtype
                                        * '<S188>/QTM In'
                                        */
  real_T QTMIn_P3;                     /* Expression: portnum
                                        * '<S188>/QTM In'
                                        */
  real_T QTMIn_P4;                     /* Expression: stime
                                        * '<S188>/QTM In'
                                        */
  real_T QTMIn_P5;                     /* Expression: stype
                                        * '<S188>/QTM In'
                                        */
  real_T QTMIn_P6;                     /* Expression: btype
                                        * '<S188>/QTM In'
                                        */
  real_T QTMIn3xcoordmm_Gain;          /* Expression: 1
                                        * '<S188>/QTM In3 x-coord [mm]'
                                        */
  real_T mm2mx_Gain;                   /* Expression: 0.001
                                        * '<S188>/mm2m x'
                                        */
  real_T QTMIn4ycoordmm_Gain;          /* Expression: 1
                                        * '<S188>/QTM In4 y-coord [mm]'
                                        */
  real_T mm2my_Gain;                   /* Expression: 0.001
                                        * '<S188>/mm2m y'
                                        */
  real_T QTMIn6yawdeg_Gain;            /* Expression: 1
                                        * '<S188>/QTM In6 yaw [deg]'
                                        */
  real_T d2ryaw_Gain;                  /* Expression: pi/180
                                        * '<S188>/d2r yaw'
                                        */
  real_T R31_Value;                    /* Expression: 0
                                        * '<S34>/R31'
                                        */
  real_T u_Gain;                       /* Expression: -1
                                        * '<S34>/-1'
                                        */
  real_T R32_Value;                    /* Expression: 0
                                        * '<S34>/R32'
                                        */
  real_T R13_Value;                    /* Expression: 0
                                        * '<S34>/R13'
                                        */
  real_T R23_Value;                    /* Expression: 0
                                        * '<S34>/R23'
                                        */
  real_T R33_Value;                    /* Expression: 1
                                        * '<S34>/R33'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * '<S63>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * '<S63>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * '<S63>/Gain'
                                        */
  real_T Constant_Value_lo;            /* Expression: 2*pi
                                        * '<S63>/Constant'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: 1
                                        * '<S164>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: 0
                                        * '<S164>/Saturation'
                                        */
  real_T Gain_Gain_l;                  /* Expression: -1
                                        * '<S167>/Gain'
                                        */
  real_T Constant_Value_lv;            /* Expression: 1
                                        * '<S174>/Constant'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 1e10
                                        * '<S122>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: -1e10
                                        * '<S122>/Saturation'
                                        */
  real_T Gain_Gain_f;                  /* Expression: pi
                                        * '<S122>/Gain'
                                        */
  real_T Constant_Value_a5;            /* Expression: 2*pi
                                        * '<S122>/Constant'
                                        */
  real_T Saturation_UpperSat_j;        /* Expression: 1e10
                                        * '<S150>/Saturation'
                                        */
  real_T Saturation_LowerSat_d;        /* Expression: -1e10
                                        * '<S150>/Saturation'
                                        */
  real_T Gain_Gain_p;                  /* Expression: pi
                                        * '<S150>/Gain'
                                        */
  real_T Constant_Value_md;            /* Expression: 2*pi
                                        * '<S150>/Constant'
                                        */
  real_T Constant_Value_i;             /* Expression: 1
                                        * '<S173>/Constant'
                                        */
  real_T Saturation_UpperSat_m;        /* Expression: 1e10
                                        * '<S151>/Saturation'
                                        */
  real_T Saturation_LowerSat_c;        /* Expression: -1e10
                                        * '<S151>/Saturation'
                                        */
  real_T Gain_Gain_o;                  /* Expression: pi
                                        * '<S151>/Gain'
                                        */
  real_T Constant_Value_ic;            /* Expression: 2*pi
                                        * '<S151>/Constant'
                                        */
  real_T Saturation_UpperSat_k;        /* Expression: 1e10
                                        * '<S152>/Saturation'
                                        */
  real_T Saturation_LowerSat_p;        /* Expression: -1e10
                                        * '<S152>/Saturation'
                                        */
  real_T Gain_Gain_b;                  /* Expression: pi
                                        * '<S152>/Gain'
                                        */
  real_T Constant_Value_l2;            /* Expression: 2*pi
                                        * '<S152>/Constant'
                                        */
  real_T Saturation_UpperSat_b;        /* Expression: 1e10
                                        * '<S64>/Saturation'
                                        */
  real_T Saturation_LowerSat_g;        /* Expression: -1e10
                                        * '<S64>/Saturation'
                                        */
  real_T Gain_Gain_ff;                 /* Expression: pi
                                        * '<S64>/Gain'
                                        */
  real_T Constant_Value_cb;            /* Expression: 2*pi
                                        * '<S64>/Constant'
                                        */
  real_T Gain_Gain_fj;                 /* Expression: -1
                                        * '<S53>/Gain'
                                        */
  real_T Integrator_IC[3];             /* Expression: [0 0 0]'
                                        * '<S40>/Integrator'
                                        */
  real_T Gain1_Gain_c;                 /* Expression: -1
                                        * '<S53>/Gain1'
                                        */
  real_T Integrator4_IC;               /* Expression: 0
                                        * '<S191>/Integrator4'
                                        */
  real_T u_Gain_i;                     /* Expression: -1
                                        * '<S145>/-1'
                                        */
  real_T _2x1_Value[2];                /* Expression: [0;0]
                                        * '<S47>/0_2x1'
                                        */
  real_T _2x1_Value_a[2];              /* Expression: [0;0]
                                        * '<S165>/0_2x1'
                                        */
  real_T Gain_Gain_fv;                 /* Expression: -1
                                        * '<S168>/Gain'
                                        */
  real_T Gain1_Gain_f;                 /* Expression: -1
                                        * '<S168>/Gain1'
                                        */
  real_T Constant_Value_b0;            /* Expression: 1
                                        * '<S175>/Constant'
                                        */
  real_T Constant_Value_e;             /* Expression: 1
                                        * '<S177>/Constant'
                                        */
  real_T Gain_Gain_h;                  /* Expression: -1
                                        * '<S137>/Gain'
                                        */
  real_T Gain2_Gain;                   /* Expression: -1
                                        * '<S53>/Gain2'
                                        */
  real_T Gain_Gain_j;                  /* Expression: -1
                                        * '<S130>/Gain'
                                        */
  real_T _Gain;                        /* Expression: 2
                                        * '<S146>/2'
                                        */
  real_T _2x2_Value[4];                /* Expression: [0 0;0 0]
                                        * '<S127>/0_2x2'
                                        */
  real_T _2x2_Value_n[4];              /* Expression: [0 0; 0 0]
                                        * '<S48>/0_2x2'
                                        */
  real_T _Gain_d;                      /* Expression: 2
                                        * '<S147>/2'
                                        */
  real_T u_Value_pg;                   /* Expression: 3/2
                                        * '<S134>/3//2'
                                        */
  real_T Gain_Gain_g;                  /* Expression: -1
                                        * '<S138>/Gain'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * '<S35>/Integrator2'
                                        */
  real_T Gain_Gain_gn;                 /* Expression: -1
                                        * '<S131>/Gain'
                                        */
  real_T _2x1_Value_a2[2];             /* Expression: [0;0]
                                        * '<S49>/0_2x1'
                                        */
  real_T Constant_Value_mz;            /* Expression: 3
                                        * '<S169>/Constant'
                                        */
  real_T Gain_Gain_e;                  /* Expression: -1
                                        * '<S169>/Gain'
                                        */
  real_T Constant_Value_h;             /* Expression: 1
                                        * '<S176>/Constant'
                                        */
  real_T u_Gain_k;                     /* Expression: 2
                                        * '<S121>/+ 2'
                                        */
  real_T _Gain_e;                      /* Expression: 2
                                        * '<S149>/2'
                                        */
  real_T _Gain_n;                      /* Expression: 2
                                        * '<S161>/2'
                                        */
  real_T Gain_Gain_gp;                 /* Expression: 1
                                        * '<S161>/Gain'
                                        */
  real_T Constant_Value_n;             /* Expression: 3
                                        * '<S185>/Constant'
                                        */
  real_T Gain_Gain_jq;                 /* Expression: -1
                                        * '<S185>/Gain'
                                        */
  real_T u_Value_ez;                   /* Expression: 3/2
                                        * '<S135>/3//2'
                                        */
  real_T Constant_Value_mj;            /* Expression: 3
                                        * '<S139>/Constant'
                                        */
  real_T _2x1_Value_c[2];              /* Expression: [0;0]
                                        * '<S50>/0_2x1'
                                        */
  real_T S11_Value;                    /* Expression: 0
                                        * '<S54>/S11'
                                        */
  real_T R31_Value_e;                  /* Expression: 0
                                        * '<S54>/R31'
                                        */
  real_T S12_Gain;                     /* Expression: 1
                                        * '<S54>/S12'
                                        */
  real_T S22_Value;                    /* Expression: 0
                                        * '<S54>/S22'
                                        */
  real_T S32_Value;                    /* Expression: 0
                                        * '<S54>/S32'
                                        */
  real_T S13_Value;                    /* Expression: 0
                                        * '<S54>/S13'
                                        */
  real_T S23_Value;                    /* Expression: 0
                                        * '<S54>/S23'
                                        */
  real_T S33_Value;                    /* Expression: 1
                                        * '<S54>/S33'
                                        */
  real_T Gain_Gain_h2;                 /* Expression: -1
                                        * '<S51>/Gain'
                                        */
  real_T Constant_Value_pe[4];         /* Expression: a
                                        * '<S162>/Constant'
                                        */
  real_T Gain_Gain_px;                 /* Expression: -1
                                        * '<S35>/Gain'
                                        */
  real_T f_1tou_1_XData[39];           /* Expression: [-0.6829 -0.6369 -0.5785 -0.5165 -0.4456 -0.3725 -0.3308 -0.2827 -0.2277 -0.1517 -0.1240 -0.0769 -0.0238 0.0039 0.0377 0.0635 0.1051 0.1196 0.1412 0.1721 0.1754 0.1774 0.2104 0.2200 0.2266 0.2673 0.3025 0.3486 0.3896 0.4252 0.4782 0.5164 0.5695 0.6195 0.6723 0.7449 0.7836 0.8414 0.8987 ]
                                        * '<S100>/f_1 to u_1'
                                        */
  real_T f_1tou_1_YData[39];           /* Expression: [-1.0000 -0.9500 -0.9000 -0.8500 -0.8000 -0.7500 -0.7000 -0.6500 -0.6000 -0.5500 -0.5000 -0.4500 -0.4000 -0.3500 -0.3000 -0.2500 -0.2000 -0.1500 -0.1000 -0.0500 0 0.0500 0.1000 0.1500 0.2000 0.2500 0.3000 0.3500 0.4000 0.4500 0.5000 0.5500 0.6000 0.6500 0.7000 0.7500 0.8000 0.8500 0.9000]
                                        * '<S100>/f_1 to u_1'
                                        */
  real_T Constant_Value_pj;            /* Expression: const
                                        * '<S105>/Constant'
                                        */
  real_T Constant_Value_h5;            /* Expression: const
                                        * '<S107>/Constant'
                                        */
  real_T Constant_Value_cy;            /* Expression: const
                                        * '<S106>/Constant'
                                        */
  real_T Constant_Value_fy;            /* Expression: const
                                        * '<S108>/Constant'
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
                                        * '<S101>/f_2 < 0.00391'
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
                                        * '<S101>/f_2 < 0.00391'
                                        */
  real_T f_2006731f_2000391_XData[3];  /* Expression: [-0.0105
                                          0.0226
                                          0.0673]
                                        * '<S101>/f_2 < 0.06731 && f_2 >= 0.00391'
                                        */
  real_T f_2006731f_2000391_YData[3];  /* Expression: [-0.2000
                                          -0.1500
                                          -0.1000]
                                        * '<S101>/f_2 < 0.06731 && f_2 >= 0.00391'
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
                                        * '<S101>/f_2 => 0.06731'
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
                                        * '<S101>/f_2 => 0.06731'
                                        */
  real_T f_3tou_3_XData[39];           /* Expression: [-0.5408,-0.5036,-0.4487,-0.3802,-0.3147,-0.2525,-0.2338,-0.1568,-0.1034,-0.0647,-0.0054,0.0221,0.0572,0.0747,0.0991,0.1258,0.1385,0.1447,0.1539,0.1625,0.1712,0.1976,0.2258,0.2443,0.3058,0.3460,0.3989,0.4342,0.4932,0.5524,0.5814,0.6394,0.6851,0.7496,0.8081,0.8382,0.8665,0.8767,0.8885]
                                        * '<S102>/f_3 to u_3'
                                        */
  real_T f_3tou_3_YData[39];           /* Expression: [-1.0000,-0.9500,-0.9000,-0.8500,-0.8000,-0.7500,-0.7000,-0.6500,-0.6000,-0.5500,-0.5000,-0.4500,-0.4000,-0.3500,-0.3000,-0.2000,-0.1500,-0.1000,-0.0500,0,0.0500,0.1000,0.1500,0.2000,0.2500,0.3000,0.3500,0.4000,0.4500,0.5000,0.5500,0.6000,0.6500,0.7000,0.7500,0.8000,0.8500,0.9500,1.0000]
                                        * '<S102>/f_3 to u_3'
                                        */
  real_T Constant_Value_hw;            /* Expression: const
                                        * '<S109>/Constant'
                                        */
  real_T Constant_Value_l5;            /* Expression: const
                                        * '<S110>/Constant'
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
                                        * '<S103>/f_4 < 0.0451'
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
                                        * '<S103>/f_4 < 0.0451'
                                        */
  real_T f_400451_XData_m[13];         /* Expression: [0.0431
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
                                        * '<S103>/f_4 >= 0.0451 '
                                        */
  real_T f_400451_YData_n[13];         /* Expression: [0.4000
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
                                        * '<S103>/f_4 >= 0.0451 '
                                        */
  real_T DeadZone001_Start_i;          /* Expression: -0.01
                                        * '<S104>/Dead Zone +-0.01'
                                        */
  real_T DeadZone001_End_h;            /* Expression: 0.01
                                        * '<S104>/Dead Zone +-0.01'
                                        */
  real_T Constant_Value_kt;            /* Expression: const
                                        * '<S111>/Constant'
                                        */
  real_T Constant_Value_mp;            /* Expression: const
                                        * '<S112>/Constant'
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
                                        * '<S104>/f_5 < 0'
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
                                        * '<S104>/f_5 < 0'
                                        */
  real_T f_50_Value;                   /* Expression: 0
                                        * '<S104>/f_5 = 0'
                                        */
  real_T f_50_XData_i[10];             /* Expression: [0.0103
                                          0.0743
                                          0.1937
                                          0.3232
                                          0.4342
                                          0.5862
                                          0.7291
                                          0.8697
                                          0.9681
                                          1.0229]
                                        * '<S104>/f_5 > 0'
                                        */
  real_T f_50_YData_l[10];             /* Expression: [0.0300
                                          0.0500
                                          0.0700
                                          0.0900
                                          0.1100
                                          0.1300
                                          0.1500
                                          0.1700
                                          0.1900
                                          0.2000]
                                        * '<S104>/f_5 > 0'
                                        */
  real_T BT_power_limit_Value;         /* Expression: 0.4
                                        * '<S97>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value;             /* Expression: 0.3
                                        * '<S97>/VSP_speeds'
                                        */
  real_T Saturation_UpperSat_p;        /* Expression: 1.0
                                        * '<S30>/Saturation'
                                        */
  real_T Saturation_LowerSat_i;        /* Expression: -1.0
                                        * '<S30>/Saturation'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S188>/QTM In2 Error'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S188>/QTM In9 Residual'
                                        */
  real_T _2x1_Value_d[2];              /* Expression: [0;0]
                                        * '<S128>/0_2x1'
                                        */
  real_T Constant1_Value[9];           /* Expression: zeros(3)
                                        * '<S188>/Constant1'
                                        */
  real_T QTMIn5zcoordmm_Gain;          /* Expression: 1
                                        * '<S188>/QTM In5 z-coord [mm]'
                                        */
  real_T mm2mz_Gain;                   /* Expression: 0.001
                                        * '<S188>/mm2m z'
                                        */
  real_T QTMIn8rolldeg_Gain;           /* Expression: 1
                                        * '<S188>/QTM In8 roll [deg]'
                                        */
  real_T d2rroll_Gain;                 /* Expression: pi/180
                                        * '<S188>/d2r roll'
                                        */
  real_T QTMIn7pitchdeg_Gain;          /* Expression: 1
                                        * '<S188>/QTM In7 pitch [deg]'
                                        */
  real_T d2rpitch_Gain;                /* Expression: pi/180
                                        * '<S188>/d2r pitch'
                                        */
  real_T QTMIn1FN_Gain;                /* Expression: 1
                                        * '<S188>/QTM In1 FN'
                                        */
  real_T Integrator3_IC;               /* Expression: 0
                                        * '<S191>/Integrator3'
                                        */
  real_T Saturation_UpperSat_dx;       /* Expression: 1e10
                                        * '<S196>/Saturation'
                                        */
  real_T Saturation_LowerSat_gr;       /* Expression: -1e10
                                        * '<S196>/Saturation'
                                        */
  real_T Gain_Gain_p1;                 /* Expression: pi
                                        * '<S196>/Gain'
                                        */
  real_T Constant_Value_ol;            /* Expression: 2*pi
                                        * '<S196>/Constant'
                                        */
  real_T Saturation_UpperSat_eu;       /* Expression: 1e10
                                        * '<S197>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: -1e10
                                        * '<S197>/Saturation'
                                        */
  real_T Gain_Gain_c;                  /* Expression: pi
                                        * '<S197>/Gain'
                                        */
  real_T Constant_Value_g;             /* Expression: 2*pi
                                        * '<S197>/Constant'
                                        */
  real_T K2_Gain[9];                   /* Expression: diag([1 1 1])*1
                                        * '<S191>/K2'
                                        */
  real_T K3_Gain[9];                   /* Expression: diag([1 1 1])*0
                                        * '<S191>/K3'
                                        */
  real_T K4_Gain[9];                   /* Expression: diag([1 1 1])*5
                                        * '<S191>/K4'
                                        */
  real_T u_1tof_1_XData_b[39];         /* Expression: [-1.0000 -0.9500 -0.9000 -0.8500 -0.8000 -0.7500 -0.7000 -0.6500 -0.6000 -0.5500 -0.5000 -0.4500 -0.4000 -0.3500 -0.3000 -0.2500 -0.2000 -0.1500 -0.1000 -0.0500 0 0.0500 0.1000 0.1500 0.2000 0.2500 0.3000 0.3500 0.4000 0.4500 0.5000 0.5500 0.6000 0.6500 0.7000 0.7500 0.8000 0.8500 0.9000]
                                        * '<S199>/u_1 to f_1'
                                        */
  real_T u_1tof_1_YData_l[39];         /* Expression: [-0.6829 -0.6369 -0.5785 -0.5165 -0.4456 -0.3725 -0.3308 -0.2827 -0.2277 -0.1517 -0.1240 -0.0769 -0.0238 0.0039 0.0377 0.0635 0.1051 0.1196 0.1412 0.1721 0.1754 0.1774 0.2104 0.2200 0.2266 0.2673 0.3025 0.3486 0.3896 0.4252 0.4782 0.5164 0.5695 0.6195 0.6723 0.7449 0.7836 0.8414 0.8987 ]
                                        * '<S199>/u_1 to f_1'
                                        */
  real_T Constant_Value_ex;            /* Expression: const
                                        * '<S204>/Constant'
                                        */
  real_T Constant_Value_fk;            /* Expression: const
                                        * '<S206>/Constant'
                                        */
  real_T Constant_Value_lt;            /* Expression: const
                                        * '<S205>/Constant'
                                        */
  real_T Constant_Value_h2;            /* Expression: const
                                        * '<S207>/Constant'
                                        */
  real_T u_205_XData_h[11];            /* Expression: [-1.0000
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
                                        * '<S200>/u_2 < -0.5'
                                        */
  real_T u_205_YData_l[11];            /* Expression: [-0.2704
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
                                        * '<S200>/u_2 < -0.5'
                                        */
  real_T u_201u_202_XData_m[3];        /* Expression: [-0.2000
                                          -0.1500
                                          -0.1000]
                                        * '<S200>/u_2 < -0.1 && u_2 >= -0.2'
                                        */
  real_T u_201u_202_YData_i[3];        /* Expression: [-0.0105
                                          0.0226
                                          0.0673]
                                        * '<S200>/u_2 < -0.1 && u_2 >= -0.2'
                                        */
  real_T u_20_XData_b[18];             /* Expression: [0
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
                                        * '<S200>/u_2 => 0'
                                        */
  real_T u_20_YData_e[18];             /* Expression: [0.0872
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
                                        * '<S200>/u_2 => 0'
                                        */
  real_T u_3tof_3_XData_h[39];         /* Expression: [-1.0000,-0.9500,-0.9000,-0.8500,-0.8000,-0.7500,-0.7000,-0.6500,-0.6000,-0.5500,-0.5000,-0.4500,-0.4000,-0.3500,-0.3000,-0.2000,-0.1500,-0.1000,-0.0500,0,0.0500,0.1000,0.1500,0.2000,0.2500,0.3000,0.3500,0.4000,0.4500,0.5000,0.5500,0.6000,0.6500,0.7000,0.7500,0.8000,0.8500,0.9500,1.0000]
                                        * '<S201>/u_3 to f_3'
                                        */
  real_T u_3tof_3_YData_b[39];         /* Expression: [-0.5408,-0.5036,-0.4487,-0.3802,-0.3147,-0.2525,-0.2338,-0.1568,-0.1034,-0.0647,-0.0054,0.0221,0.0572,0.0747,0.0991,0.1258,0.1385,0.1447,0.1539,0.1625,0.1712,0.1976,0.2258,0.2443,0.3058,0.3460,0.3989,0.4342,0.4932,0.5524,0.5814,0.6394,0.6851,0.7496,0.8081,0.8382,0.8665,0.8767,0.8885]
                                        * '<S201>/u_3 to f_3'
                                        */
  real_T Constant_Value_li;            /* Expression: const
                                        * '<S208>/Constant'
                                        */
  real_T Constant_Value_of;            /* Expression: const
                                        * '<S209>/Constant'
                                        */
  real_T u_401_XData_m[15];            /* Expression: [-0.8000
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
                                        * '<S202>/u_4 < -0.1'
                                        */
  real_T u_401_YData_p[15];            /* Expression: [-0.5212
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
                                        * '<S202>/u_4 < -0.1'
                                        */
  real_T u_401_XData_e[13];            /* Expression: [0.0431
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
                                        * '<S202>/u_4 >= -0.1'
                                        */
  real_T u_401_YData_ec[13];           /* Expression: [0.4000
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
                                        * '<S202>/u_4 >= -0.1'
                                        */
  real_T DeadZone001_Start_f;          /* Expression: -0.01
                                        * '<S203>/Dead Zone +-0.01'
                                        */
  real_T DeadZone001_End_e;            /* Expression: 0.01
                                        * '<S203>/Dead Zone +-0.01'
                                        */
  real_T Constant_Value_pp;            /* Expression: const
                                        * '<S210>/Constant'
                                        */
  real_T Constant_Value_ab;            /* Expression: const
                                        * '<S211>/Constant'
                                        */
  real_T u_50_XData_e[10];             /* Expression: [-0.2000
                                          -0.1900
                                          -0.1700
                                          -0.1500
                                          -0.1300
                                          -0.1100
                                          -0.0900
                                          -0.0700
                                          -0.0500
                                          -0.0300]
                                        * '<S203>/u_5 < 0'
                                        */
  real_T u_50_YData_ca[10];            /* Expression: [-1.1653
                                          -1.1010
                                          -0.9810
                                          -0.8576
                                          -0.7363
                                          -0.5877
                                          -0.4265
                                          -0.2640
                                          -0.1099
                                          0.0031]
                                        * '<S203>/u_5 < 0'
                                        */
  real_T u_50_Value_p;                 /* Expression: 0
                                        * '<S203>/u_5 = 0'
                                        */
  real_T u_50_XData_ly[10];            /* Expression: [0.0300
                                          0.0500
                                          0.0700
                                          0.0900
                                          0.1100
                                          0.1300
                                          0.1500
                                          0.1700
                                          0.1900
                                          0.2000]
                                        * '<S203>/u_5 > 0'
                                        */
  real_T u_50_YData_a[10];             /* Expression: [0.0103
                                          0.0743
                                          0.1937
                                          0.3232
                                          0.4342
                                          0.5862
                                          0.7291
                                          0.8697
                                          0.9681
                                          1.0229]
                                        * '<S203>/u_5 > 0'
                                        */
  real_T invT_b_Gain[9];               /* Expression: diag([1 1 1])*10
                                        * '<S191>/inv(T_b)'
                                        */
  real_T SITzAI0_P1;                   /* Expression: width
                                        * '<S188>/SIT zAI0'
                                        */
  real_T SITzAI0_P2;                   /* Expression: dtype
                                        * '<S188>/SIT zAI0'
                                        */
  real_T SITzAI0_P3;                   /* Expression: portnum
                                        * '<S188>/SIT zAI0'
                                        */
  real_T SITzAI0_P4;                   /* Expression: stime
                                        * '<S188>/SIT zAI0'
                                        */
  real_T SITzAI0_P5;                   /* Expression: stype
                                        * '<S188>/SIT zAI0'
                                        */
  real_T SITzAI0_P6;                   /* Expression: btype
                                        * '<S188>/SIT zAI0'
                                        */
  real_T SITzAI1_P1;                   /* Expression: width
                                        * '<S188>/SIT zAI1'
                                        */
  real_T SITzAI1_P2;                   /* Expression: dtype
                                        * '<S188>/SIT zAI1'
                                        */
  real_T SITzAI1_P3;                   /* Expression: portnum
                                        * '<S188>/SIT zAI1'
                                        */
  real_T SITzAI1_P4;                   /* Expression: stime
                                        * '<S188>/SIT zAI1'
                                        */
  real_T SITzAI1_P5;                   /* Expression: stype
                                        * '<S188>/SIT zAI1'
                                        */
  real_T SITzAI1_P6;                   /* Expression: btype
                                        * '<S188>/SIT zAI1'
                                        */
  real_T SITzAI2_P1;                   /* Expression: width
                                        * '<S188>/SIT zAI2'
                                        */
  real_T SITzAI2_P2;                   /* Expression: dtype
                                        * '<S188>/SIT zAI2'
                                        */
  real_T SITzAI2_P3;                   /* Expression: portnum
                                        * '<S188>/SIT zAI2'
                                        */
  real_T SITzAI2_P4;                   /* Expression: stime
                                        * '<S188>/SIT zAI2'
                                        */
  real_T SITzAI2_P5;                   /* Expression: stype
                                        * '<S188>/SIT zAI2'
                                        */
  real_T SITzAI2_P6;                   /* Expression: btype
                                        * '<S188>/SIT zAI2'
                                        */
  real_T Saturation_UpperSat_l;        /* Expression: 3
                                        * '<S216>/Saturation'
                                        */
  real_T Saturation_LowerSat_ig;       /* Expression: -2.6
                                        * '<S216>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 3
                                        * '<S216>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -3.5
                                        * '<S216>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.6
                                        * '<S216>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S216>/Saturation2'
                                        */
  real_T planttau_surge_Gain;          /* Expression: 1
                                        * '<S216>/plant tau_surge'
                                        */
  real_T planttau_sway_Gain;           /* Expression: 1
                                        * '<S216>/plant tau_sway'
                                        */
  real_T planttau_yaw_Gain;            /* Expression: 1
                                        * '<S216>/plant tau_yaw'
                                        */
  real_T BatteryBowThruster_Gain;      /* Expression: 1
                                        * '<S224>/Battery Bow Thruster'
                                        */
  real_T BatteryMain_Gain;             /* Expression: 2
                                        * '<S224>/Battery Main'
                                        */
  real_T BatteryServo_Gain;            /* Expression: 1
                                        * '<S224>/Battery Servo'
                                        */
  real_T tau1_Gain;                    /* Expression: 1
                                        * '<S225>/tau1'
                                        */
  real_T tau2_Gain;                    /* Expression: 1
                                        * '<S225>/tau2'
                                        */
  real_T tau3_Gain;                    /* Expression: 1
                                        * '<S225>/tau3'
                                        */
  real_T tau4_Gain;                    /* Expression: 1
                                        * '<S225>/tau4'
                                        */
  real_T tau5_Gain;                    /* Expression: 1
                                        * '<S225>/tau5'
                                        */
  real_T tau6_Gain;                    /* Expression: 1
                                        * '<S225>/tau6'
                                        */
  real_T plantBTpower_Gain;            /* Expression: 1
                                        * '<S225>/plant BT power'
                                        */
  real_T plantVSPspeed_Gain;           /* Expression: 1
                                        * '<S225>/plant VSP speed'
                                        */
  real_T plantu_1_Gain;                /* Expression: 1
                                        * '<S225>/plant u_1'
                                        */
  real_T plantu_2_Gain;                /* Expression: 1
                                        * '<S225>/plant u_2'
                                        */
  real_T plantu_3_Gain;                /* Expression: 1
                                        * '<S225>/plant u_3'
                                        */
  real_T plantu_4_Gain;                /* Expression: 1
                                        * '<S225>/plant u_4'
                                        */
  real_T plantu_5_Gain;                /* Expression: 1
                                        * '<S225>/plant u_5'
                                        */
  real_T fact1_Gain;                   /* Expression: 1
                                        * '<S225>/fact1'
                                        */
  real_T fact2_Gain;                   /* Expression: 1
                                        * '<S225>/fact2'
                                        */
  real_T fact3_Gain;                   /* Expression: 1
                                        * '<S225>/fact3'
                                        */
  real_T fact4_Gain;                   /* Expression: 1
                                        * '<S225>/fact4'
                                        */
  real_T fact5_Gain;                   /* Expression: 1
                                        * '<S225>/fact5'
                                        */
  real_T taux_Gain;                    /* Expression: 1
                                        * '<S225>/taux'
                                        */
  real_T tauy_Gain;                    /* Expression: 1
                                        * '<S225>/tauy'
                                        */
  real_T tauyaw_Gain;                  /* Expression: 1
                                        * '<S225>/tauyaw'
                                        */
  real_T omega_qy_Gain;                /* Expression: 1
                                        * '<S225>/omega_qy'
                                        */
  real_T omegaqx_Gain;                 /* Expression: 1
                                        * '<S225>/omegaqx'
                                        */
  real_T CSE1_rdegs_Gain;              /* Expression: 180/pi
                                        * '<S226>/CSE1_r [deg//s]'
                                        */
  real_T CSE1_ums_Gain;                /* Expression: 1
                                        * '<S226>/CSE1_u [m//s]'
                                        */
  real_T CSE1_vms_Gain;                /* Expression: 1
                                        * '<S226>/CSE1_v [m//s]'
                                        */
  real_T QSError_Gain;                 /* Expression: 1
                                        * '<S226>/QS Error'
                                        */
  real_T QSFrame_Gain;                 /* Expression: 1
                                        * '<S226>/QS Frame'
                                        */
  real_T psideg_Gain;                  /* Expression: 180/pi
                                        * '<S227>/psi [deg]'
                                        */
  real_T psipsiddeg_Gain;              /* Expression: 180/pi
                                        * '<S227>/psi-psid [deg]'
                                        */
  real_T psiLOSpsideg_Gain;            /* Expression: 180/pi
                                        * '<S227>/psiLOS-psi [deg]'
                                        */
  real_T psiLOSpsiddeg_Gain;           /* Expression: 180/pi
                                        * '<S227>/psiLOS-psid [deg]'
                                        */
  real_T psi_LOSdeg_Gain;              /* Expression: 180/pi
                                        * '<S227>/psi_LOS [deg]'
                                        */
  real_T psiddeg_Gain;                 /* Expression: 180/pi
                                        * '<S227>/psid [deg]'
                                        */
  real_T psi_plot_Gain;                /* Expression: 1
                                        * '<S227>/psi_plot'
                                        */
  real_T qxm_Gain;                     /* Expression: 1
                                        * '<S227>/qx [m]'
                                        */
  real_T qxxm_Gain;                    /* Expression: 1
                                        * '<S227>/qx-x [m]'
                                        */
  real_T qxxdm1_Gain;                  /* Expression: 1
                                        * '<S227>/qx-xd [m]1'
                                        */
  real_T qym_Gain;                     /* Expression: 1
                                        * '<S227>/qy [m]'
                                        */
  real_T qyym_Gain;                    /* Expression: 1
                                        * '<S227>/qy-y [m]'
                                        */
  real_T qyydm1_Gain;                  /* Expression: 1
                                        * '<S227>/qy-yd [m]1'
                                        */
  real_T xm_Gain;                      /* Expression: 1
                                        * '<S227>/x [m]'
                                        */
  real_T xxdm_Gain;                    /* Expression: 1
                                        * '<S227>/x-xd [m]'
                                        */
  real_T xdm_Gain;                     /* Expression: 1
                                        * '<S227>/xd [m]'
                                        */
  real_T x_plot_Gain;                  /* Expression: 1
                                        * '<S227>/x_plot'
                                        */
  real_T ym_Gain;                      /* Expression: 1
                                        * '<S227>/y [m]'
                                        */
  real_T yydm_Gain;                    /* Expression: 1
                                        * '<S227>/y-yd [m]'
                                        */
  real_T ydm_Gain;                     /* Expression: 1
                                        * '<S227>/yd [m]'
                                        */
  real_T y_plot_Gain;                  /* Expression: 1
                                        * '<S227>/y_plot'
                                        */
  real_T splot_Gain;                   /* Expression: 1
                                        * '<S227>/splot'
                                        */
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T R12_Gain;                     /* Expression: -1
                                        * '<S153>/R12'
                                        */
  real_T R22_Gain;                     /* Expression: 1
                                        * '<S153>/R22'
                                        */
  real_T _Value;                       /* Expression: 0
                                        * '<S155>/0'
                                        */
  real_T S12_Gain_m;                   /* Expression: -1
                                        * '<S155>/S12'
                                        */
  real_T _Value_m;                     /* Expression: 0
                                        * '<S156>/0'
                                        */
  real_T S12_Gain_g;                   /* Expression: -1
                                        * '<S156>/S12'
                                        */
  real_T SITPWM0BT_P1;                 /* Expression: width
                                        * '<S217>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S217>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S217>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S217>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S217>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S217>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S217>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S217>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S217>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S217>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S217>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S217>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S217>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_j3;            /* Expression: 0
                                        * '<S217>/Constant'
                                        */
  real_T Constant1_Value_m;            /* Expression: 0
                                        * '<S217>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S217>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S218>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S218>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S218>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S218>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S218>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S218>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S218>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S218>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S218>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S218>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S218>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S218>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S218>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S218>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S218>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S218>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S218>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S218>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S218>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S218>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S218>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S218>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S218>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S218>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S218>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S218>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S218>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S218>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S218>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S218>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S218>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S218>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S218>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S218>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S218>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S218>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S218>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S218>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S218>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S218>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S218>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S218>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S218>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S218>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S218>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S218>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S218>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S218>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S218>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S218>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S218>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S218>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S218>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S218>/VSPS Starboard'
                                        */
  real_T R31_Value_j;                  /* Expression: 0
                                        * '<S223>/R31'
                                        */
  real_T R32_Value_c;                  /* Expression: 0
                                        * '<S223>/R32'
                                        */
  real_T R13_Value_g;                  /* Expression: 0
                                        * '<S223>/R13'
                                        */
  real_T R23_Value_g;                  /* Expression: 0
                                        * '<S223>/R23'
                                        */
  real_T R33_Value_h;                  /* Expression: 1
                                        * '<S223>/R33'
                                        */
  uint8_T Gain1_Gain_g;                /* Computed Parameter: Gain
                                        * '<S68>/Gain1'
                                        */
  uint8_T Gain_Gain_c0;                /* Computed Parameter: Gain
                                        * '<S70>/Gain'
                                        */
  uint8_T Gain_Gain_k;                 /* Computed Parameter: Gain
                                        * '<S71>/Gain'
                                        */
  uint8_T Gain1_Gain_o;                /* Computed Parameter: Gain
                                        * '<S71>/Gain1'
                                        */
  uint8_T Gain1_Gain_h;                /* Computed Parameter: Gain
                                        * '<S84>/Gain1'
                                        */
  uint8_T Gain_Gain_pu;                /* Computed Parameter: Gain
                                        * '<S86>/Gain'
                                        */
  uint8_T Gain_Gain_gy;                /* Computed Parameter: Gain
                                        * '<S87>/Gain'
                                        */
  uint8_T Gain1_Gain_e;                /* Computed Parameter: Gain
                                        * '<S87>/Gain1'
                                        */
  uint8_T Gain1_Gain_om;               /* Computed Parameter: Gain
                                        * '<S101>/Gain1'
                                        */
  uint8_T Gain_Gain_a;                 /* Computed Parameter: Gain
                                        * '<S103>/Gain'
                                        */
  uint8_T Gain_Gain_n;                 /* Computed Parameter: Gain
                                        * '<S104>/Gain'
                                        */
  uint8_T Gain1_Gain_a;                /* Computed Parameter: Gain
                                        * '<S104>/Gain1'
                                        */
  uint8_T Gain1_Gain_k;                /* Computed Parameter: Gain
                                        * '<S200>/Gain1'
                                        */
  uint8_T Gain_Gain_p2;                /* Computed Parameter: Gain
                                        * '<S202>/Gain'
                                        */
  uint8_T Gain_Gain_a1;                /* Computed Parameter: Gain
                                        * '<S203>/Gain'
                                        */
  uint8_T Gain1_Gain_g5;               /* Computed Parameter: Gain
                                        * '<S203>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_TemplateNIPID {
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
    real_T odeY[23];
    real_T odeF[6][23];
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
extern Parameters_TemplateNIPID TemplateNIPID_P;

/* Block signals (auto storage) */
extern BlockIO_TemplateNIPID TemplateNIPID_B;

/* Continuous states (auto storage) */
extern ContinuousStates_TemplateNIPID TemplateNIPID_X;

/* Block states (auto storage) */
extern D_Work_TemplateNIPID TemplateNIPID_DWork;

/* Constant parameters (auto storage) */
extern const ConstParam_TemplateNIPID TemplateNIPID_ConstP;

/* Model entry point functions */
extern void TemplateNIPID_initialize(boolean_T firstTime);
extern void TemplateNIPID_output(int_T tid);
extern void TemplateNIPID_update(int_T tid);
extern void TemplateNIPID_terminate(void);

/* Real-time Model object */
extern RT_MODEL_TemplateNIPID *TemplateNIPID_M;

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
 * '<Root>' : TemplateNIPID
 * '<S1>'   : TemplateNIPID/Inputs from LabVIEW
 * '<S2>'   : TemplateNIPID/Main Subsystems
 * '<S3>'   : TemplateNIPID/Outputs to LabVIEW
 * '<S4>'   : TemplateNIPID/Inputs from LabVIEW/Linear Simulator
 * '<S5>'   : TemplateNIPID/Inputs from LabVIEW/Path
 * '<S6>'   : TemplateNIPID/Inputs from LabVIEW/PlayStation3
 * '<S7>'   : TemplateNIPID/Inputs from LabVIEW/Setpoint
 * '<S8>'   : TemplateNIPID/Inputs from LabVIEW/ctrl1
 * '<S9>'   : TemplateNIPID/Inputs from LabVIEW/ctrl2
 * '<S10>'  : TemplateNIPID/Inputs from LabVIEW/Path/Ellipse
 * '<S11>'  : TemplateNIPID/Inputs from LabVIEW/Path/Linear
 * '<S12>'  : TemplateNIPID/Inputs from LabVIEW/Setpoint/Degrees to Radians
 * '<S13>'  : TemplateNIPID/Inputs from LabVIEW/ctrl2/Gamma_q
 * '<S14>'  : TemplateNIPID/Inputs from LabVIEW/ctrl2/K_d
 * '<S15>'  : TemplateNIPID/Inputs from LabVIEW/ctrl2/K_i
 * '<S16>'  : TemplateNIPID/Inputs from LabVIEW/ctrl2/K_p
 * '<S17>'  : TemplateNIPID/Main Subsystems/C//S Enterprise 1 Matrices
 * '<S18>'  : TemplateNIPID/Main Subsystems/Control
 * '<S19>'  : TemplateNIPID/Main Subsystems/Data logging
 * '<S20>'  : TemplateNIPID/Main Subsystems/Guidance
 * '<S21>'  : TemplateNIPID/Main Subsystems/Naviagation
 * '<S22>'  : TemplateNIPID/Main Subsystems/Plant
 * '<S23>'  : TemplateNIPID/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix
 * '<S24>'  : TemplateNIPID/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix
 * '<S25>'  : TemplateNIPID/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix
 * '<S26>'  : TemplateNIPID/Main Subsystems/Control/Control Switch
 * '<S27>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID
 * '<S28>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control
 * '<S29>'  : TemplateNIPID/Main Subsystems/Control/Precision control
 * '<S30>'  : TemplateNIPID/Main Subsystems/Control/Thruster allocation
 * '<S31>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q
 * '<S32>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s
 * '<S33>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Control law
 * '<S34>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/R(psi)
 * '<S35>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Update laws
 * '<S36>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/a_d
 * '<S37>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/e2
 * '<S38>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/e_1
 * '<S39>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/v_d
 * '<S40>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/zeta
 * '<S41>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q eq
 * '<S42>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq
 * '<S43>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^s eq
 * '<S44>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^t eq
 * '<S45>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/f_q^T
 * '<S46>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/psi_los^q^2T
 * '<S47>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s eq
 * '<S48>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq
 * '<S49>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq
 * '<S50>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^t eq
 * '<S51>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF
 * '<S52>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Control law/tau_FL
 * '<S53>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID
 * '<S54>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T
 * '<S55>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S^T
 * '<S56>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/R(psi)/R^T
 * '<S57>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/Update laws/Transpose
 * '<S58>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/a_d/v_d^q
 * '<S59>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/a_d/v_d^s
 * '<S60>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/a_d/v_d^t
 * '<S61>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi
 * '<S62>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1
 * '<S63>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]
 * '<S64>'  : TemplateNIPID/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]
 * '<S65>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau
 * '<S66>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act
 * '<S67>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3
 * '<S68>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3
 * '<S69>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3
 * '<S70>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3
 * '<S71>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4
 * '<S72>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391
 * '<S73>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731
 * '<S74>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391
 * '<S75>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731
 * '<S76>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451
 * '<S77>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451
 * '<S78>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0
 * '<S79>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0
 * '<S80>'  : TemplateNIPID/Main Subsystems/Control/PS3 u input control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0
 * '<S81>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau
 * '<S82>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act
 * '<S83>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3
 * '<S84>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3
 * '<S85>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3
 * '<S86>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3
 * '<S87>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4
 * '<S88>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391
 * '<S89>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731
 * '<S90>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391
 * '<S91>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731
 * '<S92>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451
 * '<S93>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451
 * '<S94>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0
 * '<S95>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0
 * '<S96>'  : TemplateNIPID/Main Subsystems/Control/Precision control/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0
 * '<S97>'  : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040
 * '<S98>'  : TemplateNIPID/Main Subsystems/Control/Thruster allocation/tau to f_act
 * '<S99>'  : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act
 * '<S100>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3
 * '<S101>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3
 * '<S102>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3
 * '<S103>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3
 * '<S104>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4
 * '<S105>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391
 * '<S106>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731
 * '<S107>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391
 * '<S108>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731
 * '<S109>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451
 * '<S110>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451
 * '<S111>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0
 * '<S112>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0
 * '<S113>' : TemplateNIPID/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0
 * '<S114>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following
 * '<S115>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading
 * '<S116>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight
 * '<S117>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path
 * '<S118>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment
 * '<S119>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq
 * '<S120>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq
 * '<S121>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq
 * '<S122>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]
 * '<S123>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot
 * '<S124>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot
 * '<S125>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot
 * '<S126>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading
 * '<S127>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals
 * '<S128>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel
 * '<S129>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq
 * '<S130>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq
 * '<S131>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq
 * '<S132>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq
 * '<S133>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq
 * '<S134>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq
 * '<S135>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq
 * '<S136>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq
 * '<S137>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq
 * '<S138>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq
 * '<S139>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq
 * '<S140>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose
 * '<S141>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose
 * '<S142>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1
 * '<S143>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2
 * '<S144>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq
 * '<S145>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq
 * '<S146>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq
 * '<S147>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq
 * '<S148>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq
 * '<S149>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq
 * '<S150>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]
 * '<S151>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1
 * '<S152>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2
 * '<S153>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2
 * '<S154>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T
 * '<S155>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2
 * '<S156>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)
 * '<S157>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T
 * '<S158>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T
 * '<S159>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq
 * '<S160>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq
 * '<S161>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq
 * '<S162>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I
 * '<S163>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path
 * '<S164>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter
 * '<S165>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path
 * '<S166>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq
 * '<S167>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq
 * '<S168>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq
 * '<S169>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq
 * '<S170>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq
 * '<S171>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T
 * '<S172>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter
 * '<S173>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor
 * '<S174>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor
 * '<S175>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor
 * '<S176>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor
 * '<S177>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1
 * '<S178>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x
 * '<S179>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y
 * '<S180>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq
 * '<S181>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq
 * '<S182>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq
 * '<S183>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T
 * '<S184>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq
 * '<S185>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq
 * '<S186>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq
 * '<S187>' : TemplateNIPID/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T
 * '<S188>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT
 * '<S189>' : TemplateNIPID/Main Subsystems/Naviagation/Navigation Switch
 * '<S190>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix
 * '<S191>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/passive low speed observer
 * '<S192>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau
 * '<S193>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1
 * '<S194>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw
 * '<S195>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1
 * '<S196>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]
 * '<S197>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1
 * '<S198>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act
 * '<S199>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3
 * '<S200>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3
 * '<S201>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3
 * '<S202>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3
 * '<S203>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4
 * '<S204>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391
 * '<S205>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731
 * '<S206>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391
 * '<S207>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731
 * '<S208>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451
 * '<S209>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451
 * '<S210>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0
 * '<S211>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0
 * '<S212>' : TemplateNIPID/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0
 * '<S213>' : TemplateNIPID/Main Subsystems/Plant/CSE1 actuator
 * '<S214>' : TemplateNIPID/Main Subsystems/Plant/Linear Simulator
 * '<S215>' : TemplateNIPID/Main Subsystems/Plant/Thruster setting workaround
 * '<S216>' : TemplateNIPID/Main Subsystems/Plant/saturation
 * '<S217>' : TemplateNIPID/Main Subsystems/Plant/CSE1 actuator/Bow Thruster
 * '<S218>' : TemplateNIPID/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller
 * '<S219>' : TemplateNIPID/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic
 * '<S220>' : TemplateNIPID/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1
 * '<S221>' : TemplateNIPID/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2
 * '<S222>' : TemplateNIPID/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics
 * '<S223>' : TemplateNIPID/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)
 * '<S224>' : TemplateNIPID/Outputs to LabVIEW/Battery Voltage
 * '<S225>' : TemplateNIPID/Outputs to LabVIEW/Command
 * '<S226>' : TemplateNIPID/Outputs to LabVIEW/Naviagtion
 * '<S227>' : TemplateNIPID/Outputs to LabVIEW/Visualization
 */
#endif                                 /* RTW_HEADER_TemplateNIPID_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_TemplateNIPID
#ifdef RVE
#ifdef MULTITASKING

Parameters_TemplateNIPID rtParameter[NUMST+!TID01EQ];

#define TemplateNIPID_P                (*param_lookup[tid][READSIDE])

Parameters_TemplateNIPID *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_TemplateNIPID rtParameter[2];

#define TemplateNIPID_P                rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
