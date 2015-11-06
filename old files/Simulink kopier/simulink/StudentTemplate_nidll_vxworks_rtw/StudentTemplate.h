/*
 * StudentTemplate.h
 *
 * Real-Time Workshop code generation for Simulink model "StudentTemplate.mdl".
 *
 * Model Version              : 1.119
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Wed Apr 02 20:33:15 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_StudentTemplate_h_
#define RTW_HEADER_StudentTemplate_h_
#ifndef StudentTemplate_COMMON_INCLUDES_
# define StudentTemplate_COMMON_INCLUDES_
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
#endif                                 /* StudentTemplate_COMMON_INCLUDES_ */

#include "StudentTemplate_types.h"

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
#define StudentTemplate_rtModel        RT_MODEL_StudentTemplate

/* Block signals (auto storage) */
typedef struct {
  real_T tauxscale;                    /* '<S1>/tauxscale' */
  real_T tauyscale;                    /* '<S1>/tauyscale' */
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
  real_T ux3[9];                       /* '<S13>/[3x3]' */
  real_T ux3_g[9];                     /* '<S14>/[3x3]' */
  real_T ux3_h[9];                     /* '<S15>/[3x3]' */
  real_T ux2[4];                       /* '<S16>/[2x2]' */
  real_T Initialq_x;                   /* '<S9>/Initial q_x' */
  real_T Initialq_y;                   /* '<S9>/Initial q_y' */
  real_T Initials;                     /* '<S9>/Initial s' */
  real_T ux3_e[9];                     /* '<S17>/[3x3]' */
  real_T ux3_b[9];                     /* '<S18>/[3x3]' */
  real_T ux3_he[9];                    /* '<S19>/[3x3]' */
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
  real_T l_x1_m;                       /* '<S74>/-l_x1' */
  real_T l_y2_a;                       /* '<S74>/-l_y2' */
  real_T l_x2_l;                       /* '<S74>/-l_x2' */
  real_T x5_i[15];                     /* '<S74>/3x5' */
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
  real_T Saturation_l;                 /* '<S35>/Saturation' */
  real_T Sign_b;                       /* '<S35>/Sign' */
  real_T Gain_n;                       /* '<S35>/Gain' */
  real_T Sum1_c;                       /* '<S35>/Sum1' */
  real_T MathFunction_e;               /* '<S35>/Math Function' */
  real_T Sum_m;                        /* '<S35>/Sum' */
  real_T Row1;                         /* '<S34>/Row1' */
  real_T Row2;                         /* '<S34>/Row2' */
  real_T Row3;                         /* '<S34>/Row3' */
  real_T TmpHiddenBufferAtProductInpor_d[3];/* '<S30>/Transposed rotation  matrix in yaw1' */
  real_T Product_m[3];                 /* '<S30>/Product' */
  real_T Integrator[3];                /* '<S30>/Integrator' */
  real_T Product1[3];                  /* '<S30>/Product1' */
  real_T Sum3[3];                      /* '<S30>/Sum3' */
  real_T nu[3];                        /* '<S169>/Integrator4' */
  real_T nuSwitch[3];                  /* '<S167>/nu Switch' */
  real_T Product2[3];                  /* '<S30>/Product2' */
  real_T Sum1_j[3];                    /* '<S30>/Sum1' */
  real_T R11;                          /* '<S41>/R11' */
  real_T R21;                          /* '<S41>/R21' */
  real_T R12;                          /* '<S41>/R12' */
  real_T u;                            /* '<S41>/-1' */
  real_T R22;                          /* '<S41>/R22' */
  real_T Rpsi[9];                      /* '<S41>/R(psi)' */
  real_T MathFunction_a[9];            /* '<S61>/Math Function' */
  real_T Integrator_h[3];              /* '<S50>/Integrator' */
  real_T Product_e[3];                 /* '<S39>/Product' */
  real_T Gain_a[3];                    /* '<S39>/Gain' */
  real_T u_h;                          /* '<S39>/4' */
  real_T Divide;                       /* '<S39>/Divide' */
  real_T Add1[9];                      /* '<S39>/Add1' */
  real_T Product1_d[9];                /* '<S31>/Product1' */
  real_T Add3[9];                      /* '<S31>/Add3' */
  real_T Saturation_o;                 /* '<S69>/Saturation' */
  real_T Sign_p;                       /* '<S69>/Sign' */
  real_T Gain_m;                       /* '<S69>/Gain' */
  real_T Sum1_k;                       /* '<S69>/Sum1' */
  real_T MathFunction_d;               /* '<S69>/Math Function' */
  real_T Sum_n;                        /* '<S69>/Sum' */
  real_T Integrator_b[2];              /* '<S42>/Integrator' */
  real_T x_2x_1;                       /* '<S159>/x_2 - x_1' */
  real_T y_2y_1;                       /* '<S159>/y_2 - y_1' */
  real_T TmpHiddenBufferAtProductInpor_e[2];/* 'synthesized block' */
  real_T Saturation_d;                 /* '<S142>/Saturation' */
  real_T RoundingFunction;             /* '<S142>/Rounding Function' */
  real_T Product_n[2];                 /* '<S152>/Product' */
  real_T Integrator1;                  /* '<S42>/Integrator1' */
  real_T Product2_j;                   /* '<S145>/Product2' */
  real_T sins;                         /* '<S145>/sin(s)' */
  real_T Product_b;                    /* '<S145>/Product' */
  real_T Gain_mx;                      /* '<S145>/Gain' */
  real_T coss;                         /* '<S145>/cos(s)' */
  real_T Product1_a;                   /* '<S145>/Product1' */
  real_T TmpHiddenBufferAtProductInpo_ds[2];/* 'synthesized block' */
  real_T Subract;                      /* '<S152>/Subract' */
  real_T Product1_m[2];                /* '<S152>/Product1' */
  real_T Add[2];                       /* '<S152>/Add' */
  real_T TrigonometricFunction;        /* '<S97>/Trigonometric Function' */
  real_T Saturation_c;                 /* '<S100>/Saturation' */
  real_T Sign_m;                       /* '<S100>/Sign' */
  real_T Gain_c;                       /* '<S100>/Gain' */
  real_T Sum1_l;                       /* '<S100>/Sum1' */
  real_T MathFunction_dh;              /* '<S100>/Math Function' */
  real_T Sum_b;                        /* '<S100>/Sum' */
  real_T Saturation_n;                 /* '<S128>/Saturation' */
  real_T Sign_g;                       /* '<S128>/Sign' */
  real_T Gain_k;                       /* '<S128>/Gain' */
  real_T Sum1_j4;                      /* '<S128>/Sum1' */
  real_T MathFunction_j;               /* '<S128>/Math Function' */
  real_T Sum_i;                        /* '<S128>/Sum' */
  real_T MathFunction_h[4];            /* '<S132>/Math Function' */
  real_T x_2x_1_e;                     /* '<S158>/x_2 - x_1' */
  real_T x_2x_1s;                      /* '<S158>/(x_2 - x_1) * s' */
  real_T x_2x_1sx_1;                   /* '<S158>/(x_2 - x_1) * s + x_1' */
  real_T y_2y_1_j;                     /* '<S158>/y_2 - y_1' */
  real_T y_2y_1s;                      /* '<S158>/(y_2 - y_1) * s' */
  real_T y_2y_1sy_1;                   /* '<S158>/(y_2 - y_1) * s + y_1' */
  real_T Product_mq[2];                /* '<S151>/Product' */
  real_T Product2_l;                   /* '<S144>/Product2' */
  real_T coss_n;                       /* '<S144>/cos(s)' */
  real_T Product_c;                    /* '<S144>/Product' */
  real_T Add_i;                        /* '<S144>/Add' */
  real_T sins_o;                       /* '<S144>/sin(s)' */
  real_T Product1_h;                   /* '<S144>/Product1' */
  real_T Add1_i;                       /* '<S144>/Add1' */
  real_T Subract_a;                    /* '<S151>/Subract' */
  real_T Product1_f[2];                /* '<S151>/Product1' */
  real_T Add_n[2];                     /* '<S151>/Add' */
  real_T Switch;                       /* '<S156>/Switch' */
  real_T Switch2;                      /* '<S156>/Switch2' */
  real_T Switch_e;                     /* '<S157>/Switch' */
  real_T Switch2_j;                    /* '<S157>/Switch2' */
  real_T Subtract[2];                  /* '<S94>/Subtract' */
  real_T epsilon[2];                   /* '<S105>/epsilon' */
  real_T MultiportSelector;            /* '<S105>/Multiport Selector' */
  real_T TrigonometricFunction_i;      /* '<S122>/Trigonometric Function' */
  real_T Saturation_i;                 /* '<S129>/Saturation' */
  real_T Sign_k;                       /* '<S129>/Sign' */
  real_T Gain_g;                       /* '<S129>/Gain' */
  real_T Sum1_h;                       /* '<S129>/Sum1' */
  real_T MathFunction_e4;              /* '<S129>/Math Function' */
  real_T Sum_e;                        /* '<S129>/Sum' */
  real_T Subtract_h;                   /* '<S122>/Subtract' */
  real_T Saturation_e;                 /* '<S130>/Saturation' */
  real_T Sign_f;                       /* '<S130>/Sign' */
  real_T Gain_d;                       /* '<S130>/Gain' */
  real_T Sum1_g;                       /* '<S130>/Sum1' */
  real_T MathFunction_eb;              /* '<S130>/Math Function' */
  real_T Sum_ip;                       /* '<S130>/Sum' */
  real_T VectorConcatenate[3];         /* '<S106>/Vector Concatenate' */
  real_T Subtract_e[3];                /* '<S48>/Subtract' */
  real_T Saturation_g;                 /* '<S70>/Saturation' */
  real_T Sign_a;                       /* '<S70>/Sign' */
  real_T Gain_j;                       /* '<S70>/Gain' */
  real_T Sum1_cz;                      /* '<S70>/Sum1' */
  real_T MathFunction_f;               /* '<S70>/Math Function' */
  real_T Sum_g;                        /* '<S70>/Sum' */
  real_T TmpHiddenBufferAtProductInpor_c[3];/* '<S48>/Heading to -pi//pi1' */
  real_T Product_bx[3];                /* '<S48>/Product' */
  real_T Product1_l[3];                /* '<S44>/Product1' */
  real_T f_qx;                         /* '<S107>/f_qx' */
  real_T f_qy;                         /* '<S107>/f_qy' */
  real_T TmpHiddenBufferAtProductInport1[2];/* 'synthesized block' */
  real_T Product_i[2];                 /* '<S107>/Product' */
  real_T Delta2;                       /* '<S123>/Delta^2' */
  real_T epsilon_n2;                   /* '<S123>/epsilon_n^2' */
  real_T Add_g;                        /* '<S123>/Add' */
  real_T Divide_b;                     /* '<S123>/Divide' */
  real_T MultiportSelector1[2];        /* '<S105>/Multiport Selector1' */
  real_T Product_a[2];                 /* '<S123>/Product' */
  real_T u_m[2];                       /* '<S123>/-1' */
  real_T VectorConcatenate_e[3];       /* '<S51>/Vector Concatenate' */
  real_T Product_g[2];                 /* '<S153>/Product' */
  real_T Product2_ld;                  /* '<S146>/Product2' */
  real_T coss_l;                       /* '<S146>/cos(s)' */
  real_T MathFunction_o;               /* '<S146>/Math Function' */
  real_T Product_p;                    /* '<S146>/Product' */
  real_T Gain_m4;                      /* '<S146>/Gain' */
  real_T sins_h;                       /* '<S146>/sin(s)' */
  real_T Product1_l1;                  /* '<S146>/Product1' */
  real_T Gain1_e;                      /* '<S146>/Gain1' */
  real_T Subract_c;                    /* '<S153>/Subract' */
  real_T Product1_l4[2];               /* '<S153>/Product1' */
  real_T Add_nm[2];                    /* '<S153>/Add' */
  real_T x_dsy_ds2;                    /* '<S98>/x_d^s * y_d^s^2' */
  real_T x_ds2y_ds;                    /* '<S98>/x_d^s^2 * y_d^s' */
  real_T x_dsy_ds2x_ds2y_ds;           /* '<S98>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
  real_T x_ds2;                        /* '<S98>/( x_d^s )^2' */
  real_T y_ds2;                        /* '<S98>/( y_d^s )^2' */
  real_T x_ds2y_ds2;                   /* '<S98>/( x_d^s )^2 + ( y_d^s )^2' */
  real_T Divide_j;                     /* '<S98>/Divide' */
  real_T Delta2_p;                     /* '<S126>/Delta^2' */
  real_T epsilon_n2_p;                 /* '<S126>/epsilon_n^2' */
  real_T Add_nu;                       /* '<S126>/Add' */
  real_T Divide_p;                     /* '<S126>/Divide' */
  real_T MathFunction_c[4];            /* '<S136>/Math Function' */
  real_T Product_j[2];                 /* '<S138>/Product' */
  real_T Product1_j[2];                /* '<S138>/Product1' */
  real_T Subtract1[2];                 /* '<S138>/Subtract1' */
  real_T MultiportSelector2;           /* '<S105>/Multiport Selector2' */
  real_T Product_i5;                   /* '<S126>/Product' */
  real_T Subtract_n;                   /* '<S126>/Subtract' */
  real_T epsilon_n2_o;                 /* '<S111>/epsilon_n^2' */
  real_T Delta2_l;                     /* '<S111>/Delta^2' */
  real_T Add_o;                        /* '<S111>/Add' */
  real_T sqrt_i;                       /* '<S111>/sqrt' */
  real_T Divide_l;                     /* '<S111>/Divide' */
  real_T MathFunction_l[2];            /* '<S161>/Math Function' */
  real_T Product_nk;                   /* '<S160>/Product' */
  real_T sqrt_d;                       /* '<S160>/sqrt' */
  real_T Product_n4;                   /* '<S155>/Product' */
  real_T MathFunction_p[2];            /* '<S149>/Math Function' */
  real_T Product_jp;                   /* '<S148>/Product' */
  real_T sqrt_e;                       /* '<S148>/sqrt' */
  real_T Subract_ab;                   /* '<S155>/Subract' */
  real_T Product1_p;                   /* '<S155>/Product1' */
  real_T Add_b;                        /* '<S155>/Add' */
  real_T Divide_bz;                    /* '<S162>/Divide' */
  real_T Product_l;                    /* '<S111>/Product' */
  real_T MathFunction_jv[2];           /* '<S118>/Math Function' */
  real_T Divide_lw[2];                 /* '<S115>/Divide' */
  real_T Product_cl;                   /* '<S115>/Product' */
  real_T Gain_h;                       /* '<S115>/Gain' */
  real_T Subtract_f;                   /* '<S111>/Subtract' */
  real_T VectorConcatenate_f[3];       /* '<S57>/Vector Concatenate' */
  real_T Add_iy[3];                    /* '<S44>/Add' */
  real_T Product2_o[3];                /* '<S44>/Product2' */
  real_T Sum_o[3];                     /* '<S44>/Sum' */
  real_T Subtract_n5[3];               /* '<S49>/Subtract' */
  real_T Product1_i[3];                /* '<S39>/Product1' */
  real_T Gain1_j[3];                   /* '<S39>/Gain1' */
  real_T Product2_g[3];                /* '<S39>/Product2' */
  real_T S12;                          /* '<S65>/S12' */
  real_T Sr[9];                        /* '<S65>/S(r)' */
  real_T MathFunction_jw[9];           /* '<S66>/Math Function' */
  real_T Product_f[3];                 /* '<S47>/Product' */
  real_T Add_k[3];                     /* '<S47>/Add' */
  real_T Product2_f[3];                /* '<S47>/Product2' */
  real_T Add1_k[3];                    /* '<S47>/Add1' */
  real_T Product3[3];                  /* '<S47>/Product3' */
  real_T TrigonometricFunction_p;      /* '<S110>/Trigonometric Function' */
  real_T TrigonometricFunction1;       /* '<S110>/Trigonometric Function1' */
  real_T Derivative;                   /* '<S96>/Derivative' */
  real_T Product_ir[2];                /* '<S110>/Product' */
  real_T VectorConcatenate_c[3];       /* '<S54>/Vector Concatenate' */
  real_T epsilon_n2_n;                 /* '<S114>/epsilon_n^2' */
  real_T Delta2_e;                     /* '<S114>/Delta^2' */
  real_T Add_m;                        /* '<S114>/Add' */
  real_T sqrt_f;                       /* '<S114>/sqrt' */
  real_T Divide_be;                    /* '<S114>/Divide' */
  real_T Divide_i;                     /* '<S164>/Divide' */
  real_T Product_f5;                   /* '<S114>/Product' */
  real_T VectorConcatenate_o[3];       /* '<S60>/Vector Concatenate' */
  real_T Add2[3];                      /* '<S47>/Add2' */
  real_T Product4[3];                  /* '<S47>/Product4' */
  real_T Sum_io[3];                    /* '<S47>/Sum' */
  real_T Product4_p[3];                /* '<S39>/Product4' */
  real_T MatrixConcatenate[6];         /* '<S106>/Matrix Concatenate' */
  real_T Product3_b[6];                /* '<S45>/Product3' */
  real_T TrigonometricFunction1_h;     /* '<S108>/Trigonometric Function1' */
  real_T Gain_o;                       /* '<S108>/Gain' */
  real_T Product1_b[2];                /* '<S108>/Product1' */
  real_T TrigonometricFunction_k;      /* '<S108>/Trigonometric Function' */
  real_T Product2_d[2];                /* '<S108>/Product2' */
  real_T MatrixConcatenate_d[4];       /* '<S108>/Matrix Concatenate' */
  real_T Product_f4[4];                /* '<S108>/Product' */
  real_T MathFunction_b[2];            /* '<S55>/Math Function' */
  real_T Product2_h;                   /* '<S124>/Product2' */
  real_T MathFunction_es[2];           /* '<S124>/Math Function' */
  real_T Product3_e[4];                /* '<S124>/Product3' */
  real_T Product4_pk[4];               /* '<S124>/Product4' */
  real_T u_e[4];                       /* '<S124>/2' */
  real_T Delta2_h;                     /* '<S124>/Delta^2' */
  real_T epsilon_n2_m;                 /* '<S124>/epsilon_n^2' */
  real_T Add_l;                        /* '<S124>/Add' */
  real_T u_g;                          /* '<S124>/( )^2' */
  real_T Divide_d[4];                  /* '<S124>/Divide' */
  real_T Product1_li[4];               /* '<S124>/Product1' */
  real_T Divide1[4];                   /* '<S124>/Divide1' */
  real_T Subtract_o[4];                /* '<S124>/Subtract' */
  real_T MathFunction_cd[4];           /* '<S56>/Math Function' */
  real_T Product_ga[2];                /* '<S52>/Product' */
  real_T Product1_ii[2];               /* '<S52>/Product1' */
  real_T Add_h[2];                     /* '<S52>/Add' */
  real_T MatrixConcatenate_k[6];       /* '<S52>/Matrix Concatenate' */
  real_T Product_iz[2];                /* '<S125>/Product' */
  real_T u_f[2];                       /* '<S125>/2' */
  real_T Delta2_g;                     /* '<S125>/Delta^2' */
  real_T epsilon_n2_o1;                /* '<S125>/epsilon_n^2' */
  real_T Add_nf;                       /* '<S125>/Add' */
  real_T u_ey;                         /* '<S125>/( )^2' */
  real_T Divide_o[2];                  /* '<S125>/Divide' */
  real_T Product1_mv[4];               /* '<S137>/Product1' */
  real_T MultiportSelector3[2];        /* '<S105>/Multiport Selector3' */
  real_T Product1_bq[2];               /* '<S125>/Product1' */
  real_T Divide1_p[2];                 /* '<S125>/Divide1' */
  real_T Subtract_b[2];                /* '<S125>/Subtract' */
  real_T Product_l2[2];                /* '<S58>/Product' */
  real_T Product1_k[2];                /* '<S112>/Product1' */
  real_T epsilon_n2_m5;                /* '<S112>/epsilon_n^2' */
  real_T Delta2_o;                     /* '<S112>/Delta^2' */
  real_T Add_ba;                       /* '<S112>/Add' */
  real_T u2;                           /* '<S112>/^3//2' */
  real_T Divide_j0[2];                 /* '<S112>/Divide' */
  real_T Product_jh[2];                /* '<S112>/Product' */
  real_T MathFunction_cy[2];           /* '<S119>/Math Function' */
  real_T Divide_a[2];                  /* '<S116>/Divide' */
  real_T Product_mp[2];                /* '<S116>/Product' */
  real_T Gain_b[2];                    /* '<S116>/Gain' */
  real_T Sum_ow[2];                    /* '<S112>/Sum' */
  real_T Product1_o[2];                /* '<S58>/Product1' */
  real_T Add_g3[2];                    /* '<S58>/Add' */
  real_T MatrixConcatenate_p[6];       /* '<S58>/Matrix Concatenate' */
  real_T Add2_d[6];                    /* '<S45>/Add2' */
  real_T Product4_k[6];                /* '<S45>/Product4' */
  real_T Add3_p[6];                    /* '<S45>/Add3' */
  real_T Integrator2[2];               /* '<S42>/Integrator2' */
  real_T Add2_f[2];                    /* '<S39>/Add2' */
  real_T Product5[3];                  /* '<S39>/Product5' */
  real_T VectorConcatenate1[3];        /* '<S106>/Vector Concatenate1' */
  real_T Product3_h[3];                /* '<S46>/Product3' */
  real_T TrigonometricFunction1_f;     /* '<S109>/Trigonometric Function1' */
  real_T Gain_l;                       /* '<S109>/Gain' */
  real_T Product1_hg;                  /* '<S109>/Product1' */
  real_T TrigonometricFunction_p5;     /* '<S109>/Trigonometric Function' */
  real_T Product2_n;                   /* '<S109>/Product2' */
  real_T TmpHiddenBufferAtProductInpor_f[2];/* 'synthesized block' */
  real_T Product_la[2];                /* '<S109>/Product' */
  real_T Product_eg;                   /* '<S53>/Product' */
  real_T Product1_lb;                  /* '<S53>/Product1' */
  real_T VectorConcatenate_em[3];      /* '<S53>/Vector Concatenate' */
  real_T Product_fb[2];                /* '<S154>/Product' */
  real_T Product2_fz;                  /* '<S147>/Product2' */
  real_T sins3;                        /* '<S147>/sin(s)3' */
  real_T MathFunction_eq;              /* '<S147>/Math Function' */
  real_T Product_lr;                   /* '<S147>/Product' */
  real_T coss3;                        /* '<S147>/cos(s)3' */
  real_T Product1_fg;                  /* '<S147>/Product1' */
  real_T Gain_ca;                      /* '<S147>/Gain' */
  real_T Subract_l;                    /* '<S154>/Subract' */
  real_T Product1_mt[2];               /* '<S154>/Product1' */
  real_T Add_bs[2];                    /* '<S154>/Add' */
  real_T x_dsy_ds3;                    /* '<S99>/x_d^s * y_d^s^3 ' */
  real_T x_ds3y_ds;                    /* '<S99>/x_d^s^3 * y_d^s' */
  real_T x_dsy_ds3x_ds3y_ds;           /* '<S99>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
  real_T Product1_op;                  /* '<S99>/Product1' */
  real_T x_dsx_ds2;                    /* '<S99>/x_d^s * x_d^s^2' */
  real_T y_dsy_ds2;                    /* '<S99>/y_d^s * y_d^s^2' */
  real_T x_dsx_ds2x_ds3y_ds;           /* '<S99>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
  real_T u_k;                          /* '<S99>/+ 2' */
  real_T Product2_i;                   /* '<S99>/Product2' */
  real_T Subtract_m;                   /* '<S99>/Subtract' */
  real_T x_ds2y_ds22;                  /* '<S99>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
  real_T Divide_ob;                    /* '<S99>/Divide' */
  real_T epsilon_ns2;                  /* '<S127>/(epsilon_n^s)^2' */
  real_T Product_lu;                   /* '<S127>/Product' */
  real_T u_o;                          /* '<S127>/2' */
  real_T Delta2_d;                     /* '<S127>/Delta^2' */
  real_T epsilon_n2_nk;                /* '<S127>/epsilon_n^2' */
  real_T Add_c;                        /* '<S127>/Add' */
  real_T u_e2;                         /* '<S127>/( )^2' */
  real_T Divide_h;                     /* '<S127>/Divide' */
  real_T MathFunction_bo[4];           /* '<S135>/Math Function' */
  real_T Product_o[4];                 /* '<S139>/Product' */
  real_T Add_ii[4];                    /* '<S139>/Add' */
  real_T Product1_pg[2];               /* '<S139>/Product1' */
  real_T Product2_hq[2];               /* '<S139>/Product2' */
  real_T u_j[2];                       /* '<S139>/2' */
  real_T Product3_e5[2];               /* '<S139>/Product3' */
  real_T Sum_og[2];                    /* '<S139>/Sum' */
  real_T Gain_f[2];                    /* '<S139>/Gain' */
  real_T MultiportSelector4;           /* '<S105>/Multiport Selector4' */
  real_T Product1_a1;                  /* '<S127>/Product1' */
  real_T Divide1_pj;                   /* '<S127>/Divide1' */
  real_T Sum_l;                        /* '<S127>/Sum' */
  real_T Product_k;                    /* '<S59>/Product' */
  real_T MathFunction_lp[2];           /* '<S165>/Math Function' */
  real_T Product1_ke;                  /* '<S163>/Product1' */
  real_T p_ds3;                        /* '<S163>/|p_d^s|^3' */
  real_T Divide_it;                    /* '<S163>/Divide' */
  real_T Product_h;                    /* '<S163>/Product' */
  real_T Gain_nv;                      /* '<S163>/Gain' */
  real_T epsilon_n2_d;                 /* '<S113>/epsilon_n^2' */
  real_T Delta2_k;                     /* '<S113>/Delta^2' */
  real_T Add_l4;                       /* '<S113>/Add' */
  real_T MathFunction_ju;              /* '<S113>/Math Function' */
  real_T Divide_da;                    /* '<S113>/Divide' */
  real_T Product1_c;                   /* '<S113>/Product1' */
  real_T Product2_m;                   /* '<S113>/Product2' */
  real_T u2_p;                         /* '<S113>/^3//2' */
  real_T Divide1_f;                    /* '<S113>/Divide1' */
  real_T Product3_m;                   /* '<S113>/Product3' */
  real_T Product1_e;                   /* '<S117>/Product1' */
  real_T MathFunction_fs[2];           /* '<S121>/Math Function' */
  real_T Divide2[2];                   /* '<S117>/Divide2' */
  real_T MathFunction_ps[2];           /* '<S120>/Math Function' */
  real_T Product2_k[2];                /* '<S117>/Product2' */
  real_T MathFunction_fa;              /* '<S117>/Math Function' */
  real_T Divide1_b[2];                 /* '<S117>/Divide1' */
  real_T Subtract1_b[2];               /* '<S117>/Subtract1' */
  real_T Product_ca;                   /* '<S117>/Product' */
  real_T Subtract_ea;                  /* '<S117>/Subtract' */
  real_T Sum_mk;                       /* '<S113>/Sum' */
  real_T Product1_kz;                  /* '<S59>/Product1' */
  real_T VectorConcatenate_c5[3];      /* '<S59>/Vector Concatenate' */
  real_T Add2_a[3];                    /* '<S46>/Add2' */
  real_T Product4_f[3];                /* '<S46>/Product4' */
  real_T Add3_l[3];                    /* '<S46>/Add3' */
  real_T Product6[3];                  /* '<S39>/Product6' */
  real_T Sum_lt[3];                    /* '<S39>/Sum' */
  real_T tauSwitch[3];                 /* '<S29>/tau Switch' */
  real_T Add_gg[2];                    /* '<S42>/Add' */
  real_T MathFunction_la[3];           /* '<S63>/Math Function' */
  real_T Product_g4[2];                /* '<S43>/Product' */
  real_T Gain_i[2];                    /* '<S43>/Gain' */
  real_T MathFunction_h2[2];           /* '<S62>/Math Function' */
  real_T Product_a5[2];                /* '<S42>/Product' */
  real_T Add1_l[2];                    /* '<S42>/Add1' */
  real_T Product1_cx[2];               /* '<S42>/Product1' */
  real_T Gain_mv[2];                   /* '<S42>/Gain' */
  real_T Product_ar[3];                /* '<S50>/Product' */
  real_T Pseudoinverse[15];            /* '<S76>/Pseudoinverse' */
  real_T Product_hu[5];                /* '<S76>/Product' */
  real_T f_1tou_1;                     /* '<S78>/f_1 to u_1' */
  real_T Sum_j;                        /* '<S77>/Sum' */
  real_T f_2000391;                    /* '<S79>/f_2 < 0.00391' */
  real_T f_2006731f_2000391;           /* '<S79>/f_2 < 0.06731 && f_2 >= 0.00391' */
  real_T f_2006731;                    /* '<S79>/f_2 => 0.06731' */
  real_T MultiportSwitch;              /* '<S79>/Multiport Switch' */
  real_T Sum1_o;                       /* '<S77>/Sum1' */
  real_T f_3tou_3;                     /* '<S80>/f_3 to u_3' */
  real_T Sum2_p;                       /* '<S77>/Sum2' */
  real_T f_400451;                     /* '<S81>/f_4 < 0.0451' */
  real_T f_400451_o;                   /* '<S81>/f_4 >= 0.0451 ' */
  real_T MultiportSwitch_e;            /* '<S81>/Multiport Switch' */
  real_T Sum3_k;                       /* '<S77>/Sum3' */
  real_T DeadZone001;                  /* '<S82>/Dead Zone +-0.01' */
  real_T f_50;                         /* '<S82>/f_5 < 0' */
  real_T f_50_b;                       /* '<S82>/f_5 > 0' */
  real_T MultiportSwitch_j;            /* '<S82>/Multiport Switch' */
  real_T Saturation_j[7];              /* '<S33>/Saturation' */
  real_T QTMIn2Error;                  /* '<S166>/QTM In2 Error' */
  real_T QTMIn9Residual;               /* '<S166>/QTM In9 Residual' */
  real_T Saturation_iv;                /* '<S193>/Saturation' */
  real_T tauSwitch_o[7];               /* '<S193>/tau Switch' */
  real_T TmpHiddenBufferAtToFileInport1[86];/* 'synthesized block' */
  real_T QTMIn5zcoordmm;               /* '<S166>/QTM In5 z-coord [mm]' */
  real_T mm2mz;                        /* '<S166>/mm2m z' */
  real_T QTMIn8rolldeg;                /* '<S166>/QTM In8 roll [deg]' */
  real_T d2rroll;                      /* '<S166>/d2r roll' */
  real_T QTMIn7pitchdeg;               /* '<S166>/QTM In7 pitch [deg]' */
  real_T d2rpitch;                     /* '<S166>/d2r pitch' */
  real_T Derivative_o[6];              /* '<S166>/Derivative' */
  real_T sintheta[3];                  /* '<S168>/sin(theta)' */
  real_T costheta[3];                  /* '<S168>/cos(theta)' */
  real_T R11_d;                        /* '<S168>/R11' */
  real_T R12_o;                        /* '<S168>/R12' */
  real_T R13;                          /* '<S168>/R13' */
  real_T R21_j;                        /* '<S168>/R21 ' */
  real_T R22_g;                        /* '<S168>/R22' */
  real_T R23;                          /* '<S168>/R23' */
  real_T R31;                          /* '<S168>/R31 ' */
  real_T R32;                          /* '<S168>/R32' */
  real_T R33;                          /* '<S168>/R33' */
  real_T Reshape9x13x3[9];             /* '<S168>/Reshape 9x1->3x3' */
  real_T Inverse[9];                   /* '<S166>/Inverse' */
  real_T MatrixConcatenate2[36];       /* '<S166>/Matrix Concatenate2' */
  real_T Product_go[6];                /* '<S166>/Product' */
  real_T QTMIn1FN;                     /* '<S166>/QTM In1 FN' */
  real_T eta[3];                       /* '<S169>/Integrator' */
  real_T bias[3];                      /* '<S169>/Integrator3' */
  real_T Saturation_lr;                /* '<S174>/Saturation' */
  real_T Sign_ab;                      /* '<S174>/Sign' */
  real_T Gain_cy;                      /* '<S174>/Gain' */
  real_T Sum1_e;                       /* '<S174>/Sum1' */
  real_T MathFunction_hz;              /* '<S174>/Math Function' */
  real_T Sum_bk;                       /* '<S174>/Sum' */
  real_T Sum2_b[3];                    /* '<S169>/Sum2' */
  real_T Saturation_b;                 /* '<S175>/Saturation' */
  real_T Sign_j;                       /* '<S175>/Sign' */
  real_T Gain_cb;                      /* '<S175>/Gain' */
  real_T Sum1_ll;                      /* '<S175>/Sum1' */
  real_T MathFunction_fr;              /* '<S175>/Math Function' */
  real_T Sum_ez;                       /* '<S175>/Sum' */
  real_T TmpHiddenBufferAtK2Inport1[3];/* 'synthesized block' */
  real_T K2[3];                        /* '<S169>/K2' */
  real_T K3[3];                        /* '<S169>/K3' */
  real_T K4[3];                        /* '<S169>/K4' */
  real_T Row1_k;                       /* '<S172>/Row1' */
  real_T Row2_o;                       /* '<S172>/Row2' */
  real_T Row3_g;                       /* '<S172>/Row3' */
  real_T Row1_g;                       /* '<S173>/Row1' */
  real_T Row2_i;                       /* '<S173>/Row2' */
  real_T Row3_d;                       /* '<S173>/Row3' */
  real_T u_1tof_1_o;                   /* '<S177>/u_1 to f_1' */
  real_T u_205;                        /* '<S178>/u_2 < -0.5' */
  real_T u_201u_202;                   /* '<S178>/u_2 < -0.1 && u_2 >= -0.2' */
  real_T u_20;                         /* '<S178>/u_2 => 0' */
  real_T MultiportSwitch_k;            /* '<S178>/Multiport Switch' */
  real_T u_3tof_3_g;                   /* '<S179>/u_3 to f_3' */
  real_T u_401;                        /* '<S180>/u_4 < -0.1' */
  real_T u_401_b;                      /* '<S180>/u_4 >= -0.1' */
  real_T MultiportSwitch_i;            /* '<S180>/Multiport Switch' */
  real_T DeadZone001_c;                /* '<S181>/Dead Zone +-0.01' */
  real_T u_50;                         /* '<S181>/u_5 < 0' */
  real_T u_50_d;                       /* '<S181>/u_5 > 0' */
  real_T MultiportSwitch_m;            /* '<S181>/Multiport Switch' */
  real_T TmpHiddenBufferAtProduct1Inport[5];/* '<S170>/u_act to f_act' */
  real_T Product1_dl[3];               /* '<S170>/Product1' */
  real_T Sum1_eh[3];                   /* '<S169>/Sum1' */
  real_T Product1_k0[3];               /* '<S169>/Product1' */
  real_T Sum8[3];                      /* '<S169>/Sum8' */
  real_T Product_ay[3];                /* '<S169>/Product' */
  real_T x_dot;                        /* '<S171>/Fcn' */
  real_T y_dot;                        /* '<S171>/Fcn1' */
  real_T psi_dot;                      /* '<S171>/Fcn2' */
  real_T Sum3_h[3];                    /* '<S169>/Sum3' */
  real_T invT_b[3];                    /* '<S169>/inv(T_b)' */
  real_T Sum7[3];                      /* '<S169>/Sum7' */
  real_T SITzAI0;                      /* '<S166>/SIT zAI0' */
  real_T SITzAI1;                      /* '<S166>/SIT zAI1' */
  real_T SITzAI2;                      /* '<S166>/SIT zAI2' */
  real_T Inverse_c[9];                 /* '<S25>/Inverse' */
  real_T Saturation_a;                 /* '<S194>/Saturation' */
  real_T Saturation1;                  /* '<S194>/Saturation1' */
  real_T Saturation2;                  /* '<S194>/Saturation2' */
  real_T planttau_surge;               /* '<S194>/plant tau_surge' */
  real_T planttau_sway;                /* '<S194>/plant tau_sway' */
  real_T planttau_yaw;                 /* '<S194>/plant tau_yaw' */
  real_T BatteryBowThruster;           /* '<S202>/Battery Bow Thruster' */
  real_T BatteryMain;                  /* '<S202>/Battery Main' */
  real_T BatteryServo;                 /* '<S202>/Battery Servo' */
  real_T tau1[3];                      /* '<S203>/tau1' */
  real_T tau2[3];                      /* '<S203>/tau2' */
  real_T tau3[3];                      /* '<S203>/tau3' */
  real_T tau4[3];                      /* '<S203>/tau4' */
  real_T tau5[3];                      /* '<S203>/tau5' */
  real_T tau6[3];                      /* '<S203>/tau6' */
  real_T plantBTpower;                 /* '<S203>/plant BT power' */
  real_T plantVSPspeed;                /* '<S203>/plant VSP speed' */
  real_T plantu_1;                     /* '<S203>/plant u_1' */
  real_T plantu_2;                     /* '<S203>/plant u_2' */
  real_T plantu_3;                     /* '<S203>/plant u_3' */
  real_T plantu_4;                     /* '<S203>/plant u_4' */
  real_T plantu_5;                     /* '<S203>/plant u_5' */
  real_T fact1;                        /* '<S203>/fact1' */
  real_T fact2;                        /* '<S203>/fact2' */
  real_T fact3;                        /* '<S203>/fact3' */
  real_T fact4;                        /* '<S203>/fact4' */
  real_T fact5;                        /* '<S203>/fact5' */
  real_T taux;                         /* '<S203>/taux' */
  real_T tauy;                         /* '<S203>/tauy' */
  real_T tauyaw;                       /* '<S203>/tauyaw' */
  real_T omega_qy;                     /* '<S203>/omega_qy' */
  real_T omegaqx;                      /* '<S203>/omegaqx' */
  real_T CSE1_rdegs;                   /* '<S204>/CSE1_r [deg//s]' */
  real_T CSE1_ums;                     /* '<S204>/CSE1_u [m//s]' */
  real_T CSE1_vms;                     /* '<S204>/CSE1_v [m//s]' */
  real_T QSError;                      /* '<S204>/QS Error' */
  real_T QSFrame;                      /* '<S204>/QS Frame' */
  real_T Sum_f[3];                     /* '<S205>/Sum' */
  real_T Sum1_hm[3];                   /* '<S205>/Sum1' */
  real_T Sum2_j[3];                    /* '<S205>/Sum2' */
  real_T psideg;                       /* '<S205>/psi [deg]' */
  real_T psipsiddeg;                   /* '<S205>/psi-psid [deg]' */
  real_T psiLOSpsideg;                 /* '<S205>/psiLOS-psi [deg]' */
  real_T psiLOSpsiddeg;                /* '<S205>/psiLOS-psid [deg]' */
  real_T psi_LOSdeg;                   /* '<S205>/psi_LOS [deg]' */
  real_T psiddeg;                      /* '<S205>/psid [deg]' */
  real_T psi_plot[3];                  /* '<S205>/psi_plot' */
  real_T qxm;                          /* '<S205>/qx [m]' */
  real_T qxxm;                         /* '<S205>/qx-x [m]' */
  real_T qxxdm1;                       /* '<S205>/qx-xd [m]1' */
  real_T qym;                          /* '<S205>/qy [m]' */
  real_T qyym;                         /* '<S205>/qy-y [m]' */
  real_T qyydm1;                       /* '<S205>/qy-yd [m]1' */
  real_T xm;                           /* '<S205>/x [m]' */
  real_T xxdm;                         /* '<S205>/x-xd [m]' */
  real_T xdm;                          /* '<S205>/xd [m]' */
  real_T x_plot[3];                    /* '<S205>/x_plot' */
  real_T ym;                           /* '<S205>/y [m]' */
  real_T yydm;                         /* '<S205>/y-yd [m]' */
  real_T ydm;                          /* '<S205>/yd [m]' */
  real_T y_plot[3];                    /* '<S205>/y_plot' */
  real_T splot;                        /* '<S205>/splot' */
  real_T Integrator_p[3];              /* '<S200>/Integrator' */
  real_T Integrator1_n[3];             /* '<S200>/Integrator1' */
  real_T R11_e;                        /* '<S201>/R11' */
  real_T R21_a;                        /* '<S201>/R21' */
  real_T R12_h;                        /* '<S201>/R12' */
  real_T R22_e;                        /* '<S201>/R22' */
  real_T Rpsi_h[9];                    /* '<S201>/R(psi)' */
  real_T Product1_ku[3];               /* '<S200>/Product1' */
  real_T Sum_jz[3];                    /* '<S200>/Sum' */
  real_T Product2_fu[3];               /* '<S200>/Product2' */
  real_T Product3_l[3];                /* '<S200>/Product3' */
  real_T BT_D_Gain1;                   /* '<S195>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S195>/BT_D_Gain2' */
  real_T Add_j;                        /* '<S195>/Add' */
  real_T BT_L_Gain1;                   /* '<S195>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S195>/BT_L_Gain2' */
  real_T Neg;                          /* '<S195>/Neg' */
  real_T Sum1_f;                       /* '<S195>/Sum1' */
  real_T Sum2_i;                       /* '<S195>/Sum2' */
  real_T Switch_j;                     /* '<S197>/Switch' */
  real_T Switch2_o;                    /* '<S197>/Switch2' */
  real_T Switch_ei;                    /* '<S198>/Switch' */
  real_T Switch2_g;                    /* '<S198>/Switch2' */
  real_T Switch_a;                     /* '<S199>/Switch' */
  real_T Switch2_i;                    /* '<S199>/Switch2' */
  real_T Sign_gy;                      /* '<S196>/Sign' */
  real_T PortVPS_X;                    /* '<S196>/Product1' */
  real_T PortVPS_X_e;                  /* '<S196>/-x' */
  real_T PortVSP_Y;                    /* '<S196>/Product2' */
  real_T PortVSP_Y_h;                  /* '<S196>/-y' */
  real_T StarboardVSP_X;               /* '<S196>/Product3' */
  real_T StarboardVSP_Y;               /* '<S196>/Product4' */
  real_T Servo1;                       /* '<S196>/Servo1' */
  real_T Servo2;                       /* '<S196>/Servo2' */
  real_T Servo3;                       /* '<S196>/Servo3' */
  real_T Servo4;                       /* '<S196>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S196>/VPS_Speed_Gain' */
  real_T Sum_c;                        /* '<S196>/Sum' */
  real_T VSPSPort;                     /* '<S196>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S196>/VSPS Starboard' */
  real_T S12_p;                        /* '<S134>/S12' */
  real_T S_2psi_ds2[4];                /* '<S134>/S_2(psi_d^s^2)' */
  real_T S12_e;                        /* '<S133>/S12' */
  real_T S_2psi_ds[4];                 /* '<S133>/S_2(psi_d^s)' */
  real_T R11_j;                        /* '<S131>/R11' */
  real_T R21_n;                        /* '<S131>/R21' */
  real_T R12_k;                        /* '<S131>/R12' */
  real_T R22_j;                        /* '<S131>/R22' */
  real_T R_2psi_d[4];                  /* '<S131>/R_2(psi_d)' */
  uint16_T Gain1_m;                    /* '<S79>/Gain1' */
  uint16_T Sum_p;                      /* '<S79>/Sum' */
  uint16_T Gain_mc;                    /* '<S81>/Gain' */
  uint16_T Sum_nx;                     /* '<S81>/Sum' */
  uint16_T Gain_o2;                    /* '<S82>/Gain' */
  uint16_T Gain1_a;                    /* '<S82>/Gain1' */
  uint16_T Sum_li;                     /* '<S82>/Sum' */
  uint16_T Gain1_c;                    /* '<S178>/Gain1' */
  uint16_T Sum_ol;                     /* '<S178>/Sum' */
  uint16_T Gain_f0;                    /* '<S180>/Gain' */
  uint16_T Sum_ld;                     /* '<S180>/Sum' */
  uint16_T Gain_lg;                    /* '<S181>/Gain' */
  uint16_T Gain1_h;                    /* '<S181>/Gain1' */
  uint16_T Sum_k;                      /* '<S181>/Sum' */
  uint8_T Compare;                     /* '<S83>/Compare' */
  uint8_T Compare_c;                   /* '<S85>/Compare' */
  uint8_T Compare_g;                   /* '<S84>/Compare' */
  uint8_T Sum1_a;                      /* '<S79>/Sum1' */
  uint8_T Compare_e;                   /* '<S86>/Compare' */
  uint8_T Compare_j;                   /* '<S87>/Compare' */
  uint8_T Compare_l;                   /* '<S88>/Compare' */
  uint8_T Compare_b;                   /* '<S89>/Compare' */
  uint8_T Compare_gl;                  /* '<S91>/Compare' */
  uint8_T Compare_gl1;                 /* '<S90>/Compare' */
  uint8_T Compare_cv;                  /* '<S182>/Compare' */
  uint8_T Compare_ev;                  /* '<S184>/Compare' */
  uint8_T Compare_i;                   /* '<S183>/Compare' */
  uint8_T Sum1_kz;                     /* '<S178>/Sum1' */
  uint8_T Compare_o;                   /* '<S185>/Compare' */
  uint8_T Compare_i4;                  /* '<S186>/Compare' */
  uint8_T Compare_p;                   /* '<S187>/Compare' */
  uint8_T Compare_n;                   /* '<S188>/Compare' */
  uint8_T Compare_a;                   /* '<S190>/Compare' */
  uint8_T Compare_ln;                  /* '<S189>/Compare' */
  boolean_T LowerRelop1;               /* '<S156>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S156>/UpperRelop' */
  boolean_T LowerRelop1_e;             /* '<S157>/LowerRelop1' */
  boolean_T UpperRelop_c;              /* '<S157>/UpperRelop' */
  boolean_T LogicalOperator;           /* '<S79>/Logical Operator' */
  boolean_T LogicalOperator_o;         /* '<S178>/Logical Operator' */
  boolean_T LowerRelop1_p;             /* '<S197>/LowerRelop1' */
  boolean_T UpperRelop_h;              /* '<S197>/UpperRelop' */
  boolean_T LowerRelop1_o;             /* '<S198>/LowerRelop1' */
  boolean_T UpperRelop_n;              /* '<S198>/UpperRelop' */
  boolean_T LowerRelop1_j;             /* '<S199>/LowerRelop1' */
  boolean_T UpperRelop_nc;             /* '<S199>/UpperRelop' */
} BlockIO_StudentTemplate;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Product_DWORK1;               /* '<S115>/Product' */
  real_T Product3_DWORK1[6];           /* '<S45>/Product3' */
  real_T Pseudoinverse_X[15];          /* '<S76>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S76>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S76>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S76>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S76>/Pseudoinverse' */
  real_T Inverse_DWORK3[9];            /* '<S166>/Inverse' */
  real_T Inverse_DWORK4[9];            /* '<S166>/Inverse' */
  real_T Inverse_DWORK4_f[9];          /* '<S25>/Inverse' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK;                  /* '<S96>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } Derivative_RWORK_d;                /* '<S166>/Derivative' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<S22>/To File' */

  int32_T Inverse_DWORK2[3];           /* '<S166>/Inverse' */
  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  uint32_T Sum1_DWORK1;                /* '<S79>/Sum1' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S79>/Sum' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S42>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK;                 /* '<S42>/Integrator1' */

  struct {
    int_T Count;
    int_T Decimation;
  } ToFile_IWORK;                      /* '<S22>/To File' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_j;                /* '<S169>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK_jt;               /* '<S200>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_h;               /* '<S200>/Integrator1' */

  int_T LinearSimulator_MODE;          /* '<S25>/Linear Simulator' */
  int_T CSE1actuator_MODE;             /* '<S25>/CSE1 actuator' */
  uint8_T SignalProbe_DWORK1[16];      /* '<Root>/SignalProbe' */
} D_Work_StudentTemplate;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S30>/Integrator' */
  real_T Integrator4_CSTATE[3];        /* '<S169>/Integrator4' */
  real_T Integrator_CSTATE_c[3];       /* '<S50>/Integrator' */
  real_T Integrator_CSTATE_j[2];       /* '<S42>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S42>/Integrator1' */
  real_T Integrator2_CSTATE[2];        /* '<S42>/Integrator2' */
  real_T Integrator_CSTATE_e[3];       /* '<S169>/Integrator' */
  real_T Integrator3_CSTATE[3];        /* '<S169>/Integrator3' */
  real_T Integrator_CSTATE_en[3];      /* '<S200>/Integrator' */
  real_T Integrator1_CSTATE_l[3];      /* '<S200>/Integrator1' */
} ContinuousStates_StudentTemplat;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S30>/Integrator' */
  real_T Integrator4_CSTATE[3];        /* '<S169>/Integrator4' */
  real_T Integrator_CSTATE_c[3];       /* '<S50>/Integrator' */
  real_T Integrator_CSTATE_j[2];       /* '<S42>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S42>/Integrator1' */
  real_T Integrator2_CSTATE[2];        /* '<S42>/Integrator2' */
  real_T Integrator_CSTATE_e[3];       /* '<S169>/Integrator' */
  real_T Integrator3_CSTATE[3];        /* '<S169>/Integrator3' */
  real_T Integrator_CSTATE_en[3];      /* '<S200>/Integrator' */
  real_T Integrator1_CSTATE_l[3];      /* '<S200>/Integrator1' */
} StateDerivatives_StudentTemplat;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S30>/Integrator' */
  boolean_T Integrator4_CSTATE[3];     /* '<S169>/Integrator4' */
  boolean_T Integrator_CSTATE_c[3];    /* '<S50>/Integrator' */
  boolean_T Integrator_CSTATE_j[2];    /* '<S42>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S42>/Integrator1' */
  boolean_T Integrator2_CSTATE[2];     /* '<S42>/Integrator2' */
  boolean_T Integrator_CSTATE_e[3];    /* '<S169>/Integrator' */
  boolean_T Integrator3_CSTATE[3];     /* '<S169>/Integrator3' */
  boolean_T Integrator_CSTATE_en[3];   /* '<S200>/Integrator' */
  boolean_T Integrator1_CSTATE_l[3];   /* '<S200>/Integrator1' */
} StateDisabled_StudentTemplate;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S30>/Integrator' */
  ZCSigState Integrator4_Reset_ZCE;    /* '<S169>/Integrator4' */
  ZCSigState Integrator_Reset_ZCE_c;   /* '<S50>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_p;   /* '<S42>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S42>/Integrator1' */
  ZCSigState Integrator2_Reset_ZCE;    /* '<S42>/Integrator2' */
  ZCSigState Integrator_Reset_ZCE_l;   /* '<S169>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_j;   /* '<S200>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE_e;  /* '<S200>/Integrator1' */
} PrevZCSigStates_StudentTemplate;

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
} ConstParam_StudentTemplate;

/* Backward compatible GRT Identifiers */
#define rtB                            StudentTemplate_B
#define BlockIO                        BlockIO_StudentTemplate
#define rtX                            StudentTemplate_X
#define ContinuousStates               ContinuousStates_StudentTemplat
#define rtP                            StudentTemplate_P
#define Parameters                     Parameters_StudentTemplate
#define rtDWork                        StudentTemplate_DWork
#define D_Work                         D_Work_StudentTemplate
#define ConstParam                     ConstParam_StudentTemplate
#define rtcP                           StudentTemplate_ConstP
#define rtPrevZCSigState               StudentTemplate_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_StudentTemplate

/* Parameters (auto storage) */
struct Parameters_StudentTemplate_ {
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
  real_T u_Value;                      /* Expression: 0
                                        * '<S13>/12'
                                        */
  real_T u_Value_n;                    /* Expression: 0
                                        * '<S13>/13'
                                        */
  real_T u_Value_ns;                   /* Expression: 0
                                        * '<S13>/21'
                                        */
  real_T u_Value_f;                    /* Expression: 0
                                        * '<S13>/23'
                                        */
  real_T u_Value_p;                    /* Expression: 0
                                        * '<S13>/31'
                                        */
  real_T u_Value_e;                    /* Expression: 0
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
  real_T u_Value_fm;                   /* Expression: 0
                                        * '<S14>/12'
                                        */
  real_T u_Value_h;                    /* Expression: 0
                                        * '<S14>/13'
                                        */
  real_T u_Value_k;                    /* Expression: 0
                                        * '<S14>/21'
                                        */
  real_T u_Value_fx;                   /* Expression: 0
                                        * '<S14>/23'
                                        */
  real_T u_Value_hu;                   /* Expression: 0
                                        * '<S14>/31'
                                        */
  real_T u_Value_a;                    /* Expression: 0
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
  real_T u_Value_b;                    /* Expression: 0
                                        * '<S15>/12'
                                        */
  real_T u_Value_np;                   /* Expression: 0
                                        * '<S15>/13'
                                        */
  real_T u_Value_km;                   /* Expression: 0
                                        * '<S15>/21'
                                        */
  real_T u_Value_g;                    /* Expression: 0
                                        * '<S15>/23'
                                        */
  real_T u_Value_f3;                   /* Expression: 0
                                        * '<S15>/31'
                                        */
  real_T u_Value_m;                    /* Expression: 0
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
  real_T u_Value_d;                    /* Expression: 0
                                        * '<S16>/12'
                                        */
  real_T u_Value_mb;                   /* Expression: 0
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
  real_T u_Value_hw;                   /* Expression: 0
                                        * '<S17>/12'
                                        */
  real_T u_Value_kh;                   /* Expression: 0
                                        * '<S17>/13'
                                        */
  real_T u_Value_l;                    /* Expression: 0
                                        * '<S17>/21'
                                        */
  real_T u_Value_kz;                   /* Expression: 0
                                        * '<S17>/23'
                                        */
  real_T u_Value_m2;                   /* Expression: 0
                                        * '<S17>/31'
                                        */
  real_T u_Value_ey;                   /* Expression: 0
                                        * '<S17>/32'
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
  real_T u_Value_ay;                   /* Expression: 0
                                        * '<S18>/12'
                                        */
  real_T u_Value_o;                    /* Expression: 0
                                        * '<S18>/13'
                                        */
  real_T u_Value_kr;                   /* Expression: 0
                                        * '<S18>/21'
                                        */
  real_T u_Value_bn;                   /* Expression: 0
                                        * '<S18>/23'
                                        */
  real_T u_Value_mi;                   /* Expression: 0
                                        * '<S18>/31'
                                        */
  real_T u_Value_pa;                   /* Expression: 0
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
  real_T u_Value_j;                    /* Expression: 0
                                        * '<S19>/12'
                                        */
  real_T u_Value_lw;                   /* Expression: 0
                                        * '<S19>/13'
                                        */
  real_T u_Value_eq;                   /* Expression: 0
                                        * '<S19>/21'
                                        */
  real_T u_Value_l0;                   /* Expression: 0
                                        * '<S19>/23'
                                        */
  real_T u_Value_pr;                   /* Expression: 0
                                        * '<S19>/31'
                                        */
  real_T u_Value_dj;                   /* Expression: 0
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
  real_T l_y1_Value_e;                 /* Expression: 0.055
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
  real_T l_x1_Gain_n;                  /* Expression: -1
                                        * '<S74>/-l_x1'
                                        */
  real_T T_e13_Value;                  /* Expression: 1
                                        * '<S74>/T_e13'
                                        */
  real_T T_e23_Value;                  /* Expression: 0
                                        * '<S74>/T_e23'
                                        */
  real_T l_y2_Value_o;                 /* Expression: 0.055
                                        * '<S74>/l_y2'
                                        */
  real_T l_y2_Gain_f;                  /* Expression: -1
                                        * '<S74>/-l_y2'
                                        */
  real_T T_e14_Value;                  /* Expression: 0
                                        * '<S74>/T_e14'
                                        */
  real_T T_e24_Value;                  /* Expression: 1
                                        * '<S74>/T_e24'
                                        */
  real_T l_x2_Value_l;                 /* Expression: 0.45
                                        * '<S74>/l_x2'
                                        */
  real_T l_x2_Gain_b;                  /* Expression: -1
                                        * '<S74>/-l_x2'
                                        */
  real_T T_e15_Value;                  /* Expression: 0
                                        * '<S74>/T_e15'
                                        */
  real_T T_e25_Value;                  /* Expression: 1
                                        * '<S74>/T_e25'
                                        */
  real_T l_x3_Value_j;                 /* Expression: 0.385
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
  real_T Saturation_UpperSat_f;        /* Expression: 1e10
                                        * '<S35>/Saturation'
                                        */
  real_T Saturation_LowerSat_p;        /* Expression: -1e10
                                        * '<S35>/Saturation'
                                        */
  real_T Gain_Gain_j;                  /* Expression: pi
                                        * '<S35>/Gain'
                                        */
  real_T Constant_Value_k;             /* Expression: 2*pi
                                        * '<S35>/Constant'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * '<S30>/Integrator'
                                        */
  real_T Integrator4_IC;               /* Expression: 0
                                        * '<S169>/Integrator4'
                                        */
  real_T R31_Value;                    /* Expression: 0
                                        * '<S41>/R31'
                                        */
  real_T u_Gain;                       /* Expression: -1
                                        * '<S41>/-1'
                                        */
  real_T R32_Value;                    /* Expression: 0
                                        * '<S41>/R32'
                                        */
  real_T R13_Value;                    /* Expression: 0
                                        * '<S41>/R13'
                                        */
  real_T R23_Value;                    /* Expression: 0
                                        * '<S41>/R23'
                                        */
  real_T R33_Value;                    /* Expression: 1
                                        * '<S41>/R33'
                                        */
  real_T Integrator_IC_f[3];           /* Expression: [0 0 0]'
                                        * '<S50>/Integrator'
                                        */
  real_T Gain_Gain_c;                  /* Expression: -1
                                        * '<S39>/Gain'
                                        */
  real_T _Value;                       /* Expression: 1
                                        * '<S39>/1'
                                        */
  real_T _Gain;                        /* Expression: 4
                                        * '<S39>/4'
                                        */
  real_T Constant_Value_e[9];          /* Expression: a
                                        * '<S40>/Constant'
                                        */
  real_T Saturation_UpperSat_n;        /* Expression: 1e10
                                        * '<S69>/Saturation'
                                        */
  real_T Saturation_LowerSat_f;        /* Expression: -1e10
                                        * '<S69>/Saturation'
                                        */
  real_T Gain_Gain_h;                  /* Expression: pi
                                        * '<S69>/Gain'
                                        */
  real_T Constant_Value_f;             /* Expression: 2*pi
                                        * '<S69>/Constant'
                                        */
  real_T Saturation_UpperSat_c;        /* Expression: 1
                                        * '<S142>/Saturation'
                                        */
  real_T Saturation_LowerSat_o;        /* Expression: 0
                                        * '<S142>/Saturation'
                                        */
  real_T Gain_Gain_n;                  /* Expression: -1
                                        * '<S145>/Gain'
                                        */
  real_T Constant_Value_m;             /* Expression: 1
                                        * '<S152>/Constant'
                                        */
  real_T Saturation_UpperSat_b;        /* Expression: 1e10
                                        * '<S100>/Saturation'
                                        */
  real_T Saturation_LowerSat_h;        /* Expression: -1e10
                                        * '<S100>/Saturation'
                                        */
  real_T Gain_Gain_g;                  /* Expression: pi
                                        * '<S100>/Gain'
                                        */
  real_T Constant_Value_i;             /* Expression: 2*pi
                                        * '<S100>/Constant'
                                        */
  real_T Saturation_UpperSat_cq;       /* Expression: 1e10
                                        * '<S128>/Saturation'
                                        */
  real_T Saturation_LowerSat_a;        /* Expression: -1e10
                                        * '<S128>/Saturation'
                                        */
  real_T Gain_Gain_h4;                 /* Expression: pi
                                        * '<S128>/Gain'
                                        */
  real_T Constant_Value_n;             /* Expression: 2*pi
                                        * '<S128>/Constant'
                                        */
  real_T Constant_Value_p;             /* Expression: 1
                                        * '<S151>/Constant'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: 1e10
                                        * '<S129>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: -1e10
                                        * '<S129>/Saturation'
                                        */
  real_T Gain_Gain_p;                  /* Expression: pi
                                        * '<S129>/Gain'
                                        */
  real_T Constant_Value_g;             /* Expression: 2*pi
                                        * '<S129>/Constant'
                                        */
  real_T Saturation_UpperSat_d;        /* Expression: 1e10
                                        * '<S130>/Saturation'
                                        */
  real_T Saturation_LowerSat_g;        /* Expression: -1e10
                                        * '<S130>/Saturation'
                                        */
  real_T Gain_Gain_i;                  /* Expression: pi
                                        * '<S130>/Gain'
                                        */
  real_T Constant_Value_j;             /* Expression: 2*pi
                                        * '<S130>/Constant'
                                        */
  real_T Saturation_UpperSat_dd;       /* Expression: 1e10
                                        * '<S70>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: -1e10
                                        * '<S70>/Saturation'
                                        */
  real_T Gain_Gain_nr;                 /* Expression: pi
                                        * '<S70>/Gain'
                                        */
  real_T Constant_Value_ig;            /* Expression: 2*pi
                                        * '<S70>/Constant'
                                        */
  real_T u_Gain_c;                     /* Expression: -1
                                        * '<S123>/-1'
                                        */
  real_T _2x1_Value[2];                /* Expression: [0;0]
                                        * '<S57>/0_2x1'
                                        */
  real_T _2x1_Value_b[2];              /* Expression: [0;0]
                                        * '<S143>/0_2x1'
                                        */
  real_T Gain_Gain_o;                  /* Expression: -1
                                        * '<S146>/Gain'
                                        */
  real_T Gain1_Gain_l;                 /* Expression: -1
                                        * '<S146>/Gain1'
                                        */
  real_T Constant_Value_f2;            /* Expression: 1
                                        * '<S153>/Constant'
                                        */
  real_T Constant_Value_a;             /* Expression: 1
                                        * '<S155>/Constant'
                                        */
  real_T Gain_Gain_e;                  /* Expression: -1
                                        * '<S115>/Gain'
                                        */
  real_T Gain1_Gain_n;                 /* Expression: -1
                                        * '<S39>/Gain1'
                                        */
  real_T S11_Value;                    /* Expression: 0
                                        * '<S65>/S11'
                                        */
  real_T R31_Value_g;                  /* Expression: 0
                                        * '<S65>/R31'
                                        */
  real_T S12_Gain;                     /* Expression: 1
                                        * '<S65>/S12'
                                        */
  real_T S22_Value;                    /* Expression: 0
                                        * '<S65>/S22'
                                        */
  real_T S32_Value;                    /* Expression: 0
                                        * '<S65>/S32'
                                        */
  real_T S13_Value;                    /* Expression: 0
                                        * '<S65>/S13'
                                        */
  real_T S23_Value;                    /* Expression: 0
                                        * '<S65>/S23'
                                        */
  real_T S33_Value;                    /* Expression: 1
                                        * '<S65>/S33'
                                        */
  real_T _2x1_Value_a[2];              /* Expression: [0;0]
                                        * '<S60>/0_2x1'
                                        */
  real_T Constant_Value_mk[4];         /* Expression: a
                                        * '<S140>/Constant'
                                        */
  real_T Gain_Gain_i4;                 /* Expression: -1
                                        * '<S108>/Gain'
                                        */
  real_T _Gain_i;                      /* Expression: 2
                                        * '<S124>/2'
                                        */
  real_T _2x2_Value[4];                /* Expression: [0 0;0 0]
                                        * '<S105>/0_2x2'
                                        */
  real_T _2x2_Value_l[4];              /* Expression: [0 0; 0 0]
                                        * '<S58>/0_2x2'
                                        */
  real_T _Gain_p;                      /* Expression: 2
                                        * '<S125>/2'
                                        */
  real_T u_Value_b2;                   /* Expression: 3/2
                                        * '<S112>/3//2'
                                        */
  real_T Gain_Gain_k;                  /* Expression: -1
                                        * '<S116>/Gain'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * '<S42>/Integrator2'
                                        */
  real_T _2x1_Value_d[2];              /* Expression: [0;0]
                                        * '<S106>/0_2x1'
                                        */
  real_T Gain_Gain_a;                  /* Expression: -1
                                        * '<S109>/Gain'
                                        */
  real_T _2x1_Value_j[2];              /* Expression: [0;0]
                                        * '<S59>/0_2x1'
                                        */
  real_T Constant_Value_j0;            /* Expression: 3
                                        * '<S147>/Constant'
                                        */
  real_T Gain_Gain_p2;                 /* Expression: -1
                                        * '<S147>/Gain'
                                        */
  real_T Constant_Value_d;             /* Expression: 1
                                        * '<S154>/Constant'
                                        */
  real_T u_Gain_h;                     /* Expression: 2
                                        * '<S99>/+ 2'
                                        */
  real_T _Gain_h;                      /* Expression: 2
                                        * '<S127>/2'
                                        */
  real_T _Gain_n;                      /* Expression: 2
                                        * '<S139>/2'
                                        */
  real_T Gain_Gain_gx;                 /* Expression: 1
                                        * '<S139>/Gain'
                                        */
  real_T Constant_Value_kd;            /* Expression: 3
                                        * '<S163>/Constant'
                                        */
  real_T Gain_Gain_kp;                 /* Expression: -1
                                        * '<S163>/Gain'
                                        */
  real_T u_Value_gk;                   /* Expression: 3/2
                                        * '<S113>/3//2'
                                        */
  real_T Constant_Value_h;             /* Expression: 3
                                        * '<S117>/Constant'
                                        */
  real_T Gain_Gain_k3;                 /* Expression: -1
                                        * '<S43>/Gain'
                                        */
  real_T Gain_Gain_ni;                 /* Expression: -1
                                        * '<S42>/Gain'
                                        */
  real_T f_1tou_1_XData[39];           /* Expression: [-0.6829 -0.6369 -0.5785 -0.5165 -0.4456 -0.3725 -0.3308 -0.2827 -0.2277 -0.1517 -0.1240 -0.0769 -0.0238 0.0039 0.0377 0.0635 0.1051 0.1196 0.1412 0.1721 0.1754 0.1774 0.2104 0.2200 0.2266 0.2673 0.3025 0.3486 0.3896 0.4252 0.4782 0.5164 0.5695 0.6195 0.6723 0.7449 0.7836 0.8414 0.8987 ]
                                        * '<S78>/f_1 to u_1'
                                        */
  real_T f_1tou_1_YData[39];           /* Expression: [-1.0000 -0.9500 -0.9000 -0.8500 -0.8000 -0.7500 -0.7000 -0.6500 -0.6000 -0.5500 -0.5000 -0.4500 -0.4000 -0.3500 -0.3000 -0.2500 -0.2000 -0.1500 -0.1000 -0.0500 0 0.0500 0.1000 0.1500 0.2000 0.2500 0.3000 0.3500 0.4000 0.4500 0.5000 0.5500 0.6000 0.6500 0.7000 0.7500 0.8000 0.8500 0.9000]
                                        * '<S78>/f_1 to u_1'
                                        */
  real_T Constant_Value_h4;            /* Expression: const
                                        * '<S83>/Constant'
                                        */
  real_T Constant_Value_b;             /* Expression: const
                                        * '<S85>/Constant'
                                        */
  real_T Constant_Value_c;             /* Expression: const
                                        * '<S84>/Constant'
                                        */
  real_T Constant_Value_gx;            /* Expression: const
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
  real_T Constant_Value_ke;            /* Expression: const
                                        * '<S87>/Constant'
                                        */
  real_T Constant_Value_h3;            /* Expression: const
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
  real_T f_400451_XData_n[13];         /* Expression: [0.0431
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
  real_T Constant_Value_ek;            /* Expression: const
                                        * '<S89>/Constant'
                                        */
  real_T Constant_Value_o;             /* Expression: const
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
  real_T f_50_XData_a[10];             /* Expression: [0.0103
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
  real_T f_50_YData_f[10];             /* Expression: [0.0300
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
  real_T Saturation_UpperSat_k;        /* Expression: 1.0
                                        * '<S33>/Saturation'
                                        */
  real_T Saturation_LowerSat_ak;       /* Expression: -1.0
                                        * '<S33>/Saturation'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S166>/QTM In2 Error'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S166>/QTM In9 Residual'
                                        */
  real_T Saturation_UpperSat_a;        /* Expression: 1
                                        * '<S193>/Saturation'
                                        */
  real_T Saturation_LowerSat_m;        /* Expression: 0
                                        * '<S193>/Saturation'
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
  real_T QTMIn1FN_Gain;                /* Expression: 1
                                        * '<S166>/QTM In1 FN'
                                        */
  real_T Integrator3_IC;               /* Expression: 0
                                        * '<S169>/Integrator3'
                                        */
  real_T Saturation_UpperSat_kw;       /* Expression: 1e10
                                        * '<S174>/Saturation'
                                        */
  real_T Saturation_LowerSat_fg;       /* Expression: -1e10
                                        * '<S174>/Saturation'
                                        */
  real_T Gain_Gain_p0;                 /* Expression: pi
                                        * '<S174>/Gain'
                                        */
  real_T Constant_Value_f3;            /* Expression: 2*pi
                                        * '<S174>/Constant'
                                        */
  real_T Saturation_UpperSat_ft;       /* Expression: 1e10
                                        * '<S175>/Saturation'
                                        */
  real_T Saturation_LowerSat_k;        /* Expression: -1e10
                                        * '<S175>/Saturation'
                                        */
  real_T Gain_Gain_b;                  /* Expression: pi
                                        * '<S175>/Gain'
                                        */
  real_T Constant_Value_cz;            /* Expression: 2*pi
                                        * '<S175>/Constant'
                                        */
  real_T K2_Gain[9];                   /* Expression: diag([1 1 1])*1
                                        * '<S169>/K2'
                                        */
  real_T K3_Gain[9];                   /* Expression: diag([1 1 1])*0
                                        * '<S169>/K3'
                                        */
  real_T K4_Gain[9];                   /* Expression: diag([1 1 1])*5
                                        * '<S169>/K4'
                                        */
  real_T u_1tof_1_XData_p[39];         /* Expression: [-1.0000 -0.9500 -0.9000 -0.8500 -0.8000 -0.7500 -0.7000 -0.6500 -0.6000 -0.5500 -0.5000 -0.4500 -0.4000 -0.3500 -0.3000 -0.2500 -0.2000 -0.1500 -0.1000 -0.0500 0 0.0500 0.1000 0.1500 0.2000 0.2500 0.3000 0.3500 0.4000 0.4500 0.5000 0.5500 0.6000 0.6500 0.7000 0.7500 0.8000 0.8500 0.9000]
                                        * '<S177>/u_1 to f_1'
                                        */
  real_T u_1tof_1_YData_i[39];         /* Expression: [-0.6829 -0.6369 -0.5785 -0.5165 -0.4456 -0.3725 -0.3308 -0.2827 -0.2277 -0.1517 -0.1240 -0.0769 -0.0238 0.0039 0.0377 0.0635 0.1051 0.1196 0.1412 0.1721 0.1754 0.1774 0.2104 0.2200 0.2266 0.2673 0.3025 0.3486 0.3896 0.4252 0.4782 0.5164 0.5695 0.6195 0.6723 0.7449 0.7836 0.8414 0.8987 ]
                                        * '<S177>/u_1 to f_1'
                                        */
  real_T Constant_Value_it;            /* Expression: const
                                        * '<S182>/Constant'
                                        */
  real_T Constant_Value_pt;            /* Expression: const
                                        * '<S184>/Constant'
                                        */
  real_T Constant_Value_fy;            /* Expression: const
                                        * '<S183>/Constant'
                                        */
  real_T Constant_Value_jd;            /* Expression: const
                                        * '<S185>/Constant'
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
                                        * '<S178>/u_2 < -0.5'
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
                                        * '<S178>/u_2 < -0.5'
                                        */
  real_T u_201u_202_XData[3];          /* Expression: [-0.2000
                                          -0.1500
                                          -0.1000]
                                        * '<S178>/u_2 < -0.1 && u_2 >= -0.2'
                                        */
  real_T u_201u_202_YData[3];          /* Expression: [-0.0105
                                          0.0226
                                          0.0673]
                                        * '<S178>/u_2 < -0.1 && u_2 >= -0.2'
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
                                        * '<S178>/u_2 => 0'
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
                                        * '<S178>/u_2 => 0'
                                        */
  real_T u_3tof_3_XData_e[39];         /* Expression: [-1.0000,-0.9500,-0.9000,-0.8500,-0.8000,-0.7500,-0.7000,-0.6500,-0.6000,-0.5500,-0.5000,-0.4500,-0.4000,-0.3500,-0.3000,-0.2000,-0.1500,-0.1000,-0.0500,0,0.0500,0.1000,0.1500,0.2000,0.2500,0.3000,0.3500,0.4000,0.4500,0.5000,0.5500,0.6000,0.6500,0.7000,0.7500,0.8000,0.8500,0.9500,1.0000]
                                        * '<S179>/u_3 to f_3'
                                        */
  real_T u_3tof_3_YData_a[39];         /* Expression: [-0.5408,-0.5036,-0.4487,-0.3802,-0.3147,-0.2525,-0.2338,-0.1568,-0.1034,-0.0647,-0.0054,0.0221,0.0572,0.0747,0.0991,0.1258,0.1385,0.1447,0.1539,0.1625,0.1712,0.1976,0.2258,0.2443,0.3058,0.3460,0.3989,0.4342,0.4932,0.5524,0.5814,0.6394,0.6851,0.7496,0.8081,0.8382,0.8665,0.8767,0.8885]
                                        * '<S179>/u_3 to f_3'
                                        */
  real_T Constant_Value_bh;            /* Expression: const
                                        * '<S186>/Constant'
                                        */
  real_T Constant_Value_cy;            /* Expression: const
                                        * '<S187>/Constant'
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
                                        * '<S180>/u_4 < -0.1'
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
                                        * '<S180>/u_4 < -0.1'
                                        */
  real_T u_401_XData_m[13];            /* Expression: [0.0431
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
                                        * '<S180>/u_4 >= -0.1'
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
                                        * '<S180>/u_4 >= -0.1'
                                        */
  real_T DeadZone001_Start_e;          /* Expression: -0.01
                                        * '<S181>/Dead Zone +-0.01'
                                        */
  real_T DeadZone001_End_k;            /* Expression: 0.01
                                        * '<S181>/Dead Zone +-0.01'
                                        */
  real_T Constant_Value_dp;            /* Expression: const
                                        * '<S188>/Constant'
                                        */
  real_T Constant_Value_hu;            /* Expression: const
                                        * '<S189>/Constant'
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
                                        * '<S181>/u_5 < 0'
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
                                        * '<S181>/u_5 < 0'
                                        */
  real_T u_50_Value;                   /* Expression: 0
                                        * '<S181>/u_5 = 0'
                                        */
  real_T u_50_XData_d[10];             /* Expression: [0.0300
                                          0.0500
                                          0.0700
                                          0.0900
                                          0.1100
                                          0.1300
                                          0.1500
                                          0.1700
                                          0.1900
                                          0.2000]
                                        * '<S181>/u_5 > 0'
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
                                        * '<S181>/u_5 > 0'
                                        */
  real_T invT_b_Gain[9];               /* Expression: diag([1 1 1])*10
                                        * '<S169>/inv(T_b)'
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
  real_T Saturation_UpperSat_p;        /* Expression: 3
                                        * '<S194>/Saturation'
                                        */
  real_T Saturation_LowerSat_oc;       /* Expression: -2.6
                                        * '<S194>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 3
                                        * '<S194>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -3.5
                                        * '<S194>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.6
                                        * '<S194>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S194>/Saturation2'
                                        */
  real_T planttau_surge_Gain;          /* Expression: 1
                                        * '<S194>/plant tau_surge'
                                        */
  real_T planttau_sway_Gain;           /* Expression: 1
                                        * '<S194>/plant tau_sway'
                                        */
  real_T planttau_yaw_Gain;            /* Expression: 1
                                        * '<S194>/plant tau_yaw'
                                        */
  real_T BatteryBowThruster_Gain;      /* Expression: 1
                                        * '<S202>/Battery Bow Thruster'
                                        */
  real_T BatteryMain_Gain;             /* Expression: 2
                                        * '<S202>/Battery Main'
                                        */
  real_T BatteryServo_Gain;            /* Expression: 1
                                        * '<S202>/Battery Servo'
                                        */
  real_T tau1_Gain;                    /* Expression: 1
                                        * '<S203>/tau1'
                                        */
  real_T tau2_Gain;                    /* Expression: 1
                                        * '<S203>/tau2'
                                        */
  real_T tau3_Gain;                    /* Expression: 1
                                        * '<S203>/tau3'
                                        */
  real_T tau4_Gain;                    /* Expression: 1
                                        * '<S203>/tau4'
                                        */
  real_T tau5_Gain;                    /* Expression: 1
                                        * '<S203>/tau5'
                                        */
  real_T tau6_Gain;                    /* Expression: 1
                                        * '<S203>/tau6'
                                        */
  real_T plantBTpower_Gain;            /* Expression: 1
                                        * '<S203>/plant BT power'
                                        */
  real_T plantVSPspeed_Gain;           /* Expression: 1
                                        * '<S203>/plant VSP speed'
                                        */
  real_T plantu_1_Gain;                /* Expression: 1
                                        * '<S203>/plant u_1'
                                        */
  real_T plantu_2_Gain;                /* Expression: 1
                                        * '<S203>/plant u_2'
                                        */
  real_T plantu_3_Gain;                /* Expression: 1
                                        * '<S203>/plant u_3'
                                        */
  real_T plantu_4_Gain;                /* Expression: 1
                                        * '<S203>/plant u_4'
                                        */
  real_T plantu_5_Gain;                /* Expression: 1
                                        * '<S203>/plant u_5'
                                        */
  real_T fact1_Gain;                   /* Expression: 1
                                        * '<S203>/fact1'
                                        */
  real_T fact2_Gain;                   /* Expression: 1
                                        * '<S203>/fact2'
                                        */
  real_T fact3_Gain;                   /* Expression: 1
                                        * '<S203>/fact3'
                                        */
  real_T fact4_Gain;                   /* Expression: 1
                                        * '<S203>/fact4'
                                        */
  real_T fact5_Gain;                   /* Expression: 1
                                        * '<S203>/fact5'
                                        */
  real_T taux_Gain;                    /* Expression: 1
                                        * '<S203>/taux'
                                        */
  real_T tauy_Gain;                    /* Expression: 1
                                        * '<S203>/tauy'
                                        */
  real_T tauyaw_Gain;                  /* Expression: 1
                                        * '<S203>/tauyaw'
                                        */
  real_T omega_qy_Gain;                /* Expression: 1
                                        * '<S203>/omega_qy'
                                        */
  real_T omegaqx_Gain;                 /* Expression: 1
                                        * '<S203>/omegaqx'
                                        */
  real_T CSE1_rdegs_Gain;              /* Expression: 180/pi
                                        * '<S204>/CSE1_r [deg//s]'
                                        */
  real_T CSE1_ums_Gain;                /* Expression: 1
                                        * '<S204>/CSE1_u [m//s]'
                                        */
  real_T CSE1_vms_Gain;                /* Expression: 1
                                        * '<S204>/CSE1_v [m//s]'
                                        */
  real_T QSError_Gain;                 /* Expression: 1
                                        * '<S204>/QS Error'
                                        */
  real_T QSFrame_Gain;                 /* Expression: 1
                                        * '<S204>/QS Frame'
                                        */
  real_T psideg_Gain;                  /* Expression: 180/pi
                                        * '<S205>/psi [deg]'
                                        */
  real_T psipsiddeg_Gain;              /* Expression: 180/pi
                                        * '<S205>/psi-psid [deg]'
                                        */
  real_T psiLOSpsideg_Gain;            /* Expression: 180/pi
                                        * '<S205>/psiLOS-psi [deg]'
                                        */
  real_T psiLOSpsiddeg_Gain;           /* Expression: 180/pi
                                        * '<S205>/psiLOS-psid [deg]'
                                        */
  real_T psi_LOSdeg_Gain;              /* Expression: 180/pi
                                        * '<S205>/psi_LOS [deg]'
                                        */
  real_T psiddeg_Gain;                 /* Expression: 180/pi
                                        * '<S205>/psid [deg]'
                                        */
  real_T psi_plot_Gain;                /* Expression: 1
                                        * '<S205>/psi_plot'
                                        */
  real_T qxm_Gain;                     /* Expression: 1
                                        * '<S205>/qx [m]'
                                        */
  real_T qxxm_Gain;                    /* Expression: 1
                                        * '<S205>/qx-x [m]'
                                        */
  real_T qxxdm1_Gain;                  /* Expression: 1
                                        * '<S205>/qx-xd [m]1'
                                        */
  real_T qym_Gain;                     /* Expression: 1
                                        * '<S205>/qy [m]'
                                        */
  real_T qyym_Gain;                    /* Expression: 1
                                        * '<S205>/qy-y [m]'
                                        */
  real_T qyydm1_Gain;                  /* Expression: 1
                                        * '<S205>/qy-yd [m]1'
                                        */
  real_T xm_Gain;                      /* Expression: 1
                                        * '<S205>/x [m]'
                                        */
  real_T xxdm_Gain;                    /* Expression: 1
                                        * '<S205>/x-xd [m]'
                                        */
  real_T xdm_Gain;                     /* Expression: 1
                                        * '<S205>/xd [m]'
                                        */
  real_T x_plot_Gain;                  /* Expression: 1
                                        * '<S205>/x_plot'
                                        */
  real_T ym_Gain;                      /* Expression: 1
                                        * '<S205>/y [m]'
                                        */
  real_T yydm_Gain;                    /* Expression: 1
                                        * '<S205>/y-yd [m]'
                                        */
  real_T ydm_Gain;                     /* Expression: 1
                                        * '<S205>/yd [m]'
                                        */
  real_T y_plot_Gain;                  /* Expression: 1
                                        * '<S205>/y_plot'
                                        */
  real_T splot_Gain;                   /* Expression: 1
                                        * '<S205>/splot'
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
  real_T _Value_m;                     /* Expression: 0
                                        * '<S133>/0'
                                        */
  real_T S12_Gain_h;                   /* Expression: -1
                                        * '<S133>/S12'
                                        */
  real_T _Value_f;                     /* Expression: 0
                                        * '<S134>/0'
                                        */
  real_T S12_Gain_e;                   /* Expression: -1
                                        * '<S134>/S12'
                                        */
  real_T SITPWM0BT_P1;                 /* Expression: width
                                        * '<S195>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S195>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S195>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S195>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S195>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S195>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S195>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S195>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S195>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S195>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S195>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S195>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S195>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_l;             /* Expression: 0
                                        * '<S195>/Constant'
                                        */
  real_T Constant1_Value_k;            /* Expression: 0
                                        * '<S195>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S195>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S196>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S196>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S196>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S196>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S196>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S196>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S196>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S196>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S196>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S196>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S196>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S196>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S196>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S196>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S196>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S196>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S196>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S196>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S196>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S196>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S196>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S196>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S196>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S196>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S196>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S196>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S196>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S196>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S196>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S196>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S196>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S196>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S196>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S196>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S196>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S196>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S196>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S196>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S196>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S196>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S196>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S196>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S196>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S196>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S196>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S196>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S196>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S196>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S196>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S196>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S196>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S196>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S196>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S196>/VSPS Starboard'
                                        */
  real_T R31_Value_j;                  /* Expression: 0
                                        * '<S201>/R31'
                                        */
  real_T R32_Value_h;                  /* Expression: 0
                                        * '<S201>/R32'
                                        */
  real_T R13_Value_p;                  /* Expression: 0
                                        * '<S201>/R13'
                                        */
  real_T R23_Value_f;                  /* Expression: 0
                                        * '<S201>/R23'
                                        */
  real_T R33_Value_h;                  /* Expression: 1
                                        * '<S201>/R33'
                                        */
  uint8_T Gain1_Gain_n2;               /* Computed Parameter: Gain
                                        * '<S79>/Gain1'
                                        */
  uint8_T Gain_Gain_gq;                /* Computed Parameter: Gain
                                        * '<S81>/Gain'
                                        */
  uint8_T Gain_Gain_en;                /* Computed Parameter: Gain
                                        * '<S82>/Gain'
                                        */
  uint8_T Gain1_Gain_c;                /* Computed Parameter: Gain
                                        * '<S82>/Gain1'
                                        */
  uint8_T Gain1_Gain_g;                /* Computed Parameter: Gain
                                        * '<S178>/Gain1'
                                        */
  uint8_T Gain_Gain_as;                /* Computed Parameter: Gain
                                        * '<S180>/Gain'
                                        */
  uint8_T Gain_Gain_hc;                /* Computed Parameter: Gain
                                        * '<S181>/Gain'
                                        */
  uint8_T Gain1_Gain_h;                /* Computed Parameter: Gain
                                        * '<S181>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_StudentTemplate {
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
    real_T odeY[26];
    real_T odeF[6][26];
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
extern Parameters_StudentTemplate StudentTemplate_P;

/* Block signals (auto storage) */
extern BlockIO_StudentTemplate StudentTemplate_B;

/* Continuous states (auto storage) */
extern ContinuousStates_StudentTemplat StudentTemplate_X;

/* Block states (auto storage) */
extern D_Work_StudentTemplate StudentTemplate_DWork;

/* Constant parameters (auto storage) */
extern const ConstParam_StudentTemplate StudentTemplate_ConstP;

/* Model entry point functions */
extern void StudentTemplate_initialize(boolean_T firstTime);
extern void StudentTemplate_output(int_T tid);
extern void StudentTemplate_update(int_T tid);
extern void StudentTemplate_terminate(void);

/* Real-time Model object */
extern RT_MODEL_StudentTemplate *StudentTemplate_M;

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
 * '<Root>' : StudentTemplate
 * '<S1>'   : StudentTemplate/Inputs from LabVIEW
 * '<S2>'   : StudentTemplate/Main Subsystems
 * '<S3>'   : StudentTemplate/Outputs to LabVIEW
 * '<S4>'   : StudentTemplate/Inputs from LabVIEW/Linear Simulator
 * '<S5>'   : StudentTemplate/Inputs from LabVIEW/Path
 * '<S6>'   : StudentTemplate/Inputs from LabVIEW/PlayStation3
 * '<S7>'   : StudentTemplate/Inputs from LabVIEW/Setpoint
 * '<S8>'   : StudentTemplate/Inputs from LabVIEW/ctrl1
 * '<S9>'   : StudentTemplate/Inputs from LabVIEW/ctrl2
 * '<S10>'  : StudentTemplate/Inputs from LabVIEW/Path/Ellipse
 * '<S11>'  : StudentTemplate/Inputs from LabVIEW/Path/Linear
 * '<S12>'  : StudentTemplate/Inputs from LabVIEW/Setpoint/Degrees to Radians
 * '<S13>'  : StudentTemplate/Inputs from LabVIEW/ctrl1/Kd
 * '<S14>'  : StudentTemplate/Inputs from LabVIEW/ctrl1/Ki
 * '<S15>'  : StudentTemplate/Inputs from LabVIEW/ctrl1/Kp
 * '<S16>'  : StudentTemplate/Inputs from LabVIEW/ctrl2/Gamma_q
 * '<S17>'  : StudentTemplate/Inputs from LabVIEW/ctrl2/K_d
 * '<S18>'  : StudentTemplate/Inputs from LabVIEW/ctrl2/K_i
 * '<S19>'  : StudentTemplate/Inputs from LabVIEW/ctrl2/K_p
 * '<S20>'  : StudentTemplate/Main Subsystems/C//S Enterprise 1 Matrices
 * '<S21>'  : StudentTemplate/Main Subsystems/Control
 * '<S22>'  : StudentTemplate/Main Subsystems/Data logging
 * '<S23>'  : StudentTemplate/Main Subsystems/Guidance
 * '<S24>'  : StudentTemplate/Main Subsystems/Naviagation
 * '<S25>'  : StudentTemplate/Main Subsystems/Plant
 * '<S26>'  : StudentTemplate/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix
 * '<S27>'  : StudentTemplate/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix
 * '<S28>'  : StudentTemplate/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix
 * '<S29>'  : StudentTemplate/Main Subsystems/Control/Control Switch
 * '<S30>'  : StudentTemplate/Main Subsystems/Control/DP control
 * '<S31>'  : StudentTemplate/Main Subsystems/Control/LgV2
 * '<S32>'  : StudentTemplate/Main Subsystems/Control/PS3 u input control
 * '<S33>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation
 * '<S34>'  : StudentTemplate/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1
 * '<S35>'  : StudentTemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]
 * '<S36>'  : StudentTemplate/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1
 * '<S37>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q
 * '<S38>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s
 * '<S39>'  : StudentTemplate/Main Subsystems/Control/LgV2/Control law
 * '<S40>'  : StudentTemplate/Main Subsystems/Control/LgV2/I
 * '<S41>'  : StudentTemplate/Main Subsystems/Control/LgV2/R(psi)
 * '<S42>'  : StudentTemplate/Main Subsystems/Control/LgV2/Update laws
 * '<S43>'  : StudentTemplate/Main Subsystems/Control/LgV2/V_1^q
 * '<S44>'  : StudentTemplate/Main Subsystems/Control/LgV2/alpha
 * '<S45>'  : StudentTemplate/Main Subsystems/Control/LgV2/alpha^q
 * '<S46>'  : StudentTemplate/Main Subsystems/Control/LgV2/alpha^s
 * '<S47>'  : StudentTemplate/Main Subsystems/Control/LgV2/sigma
 * '<S48>'  : StudentTemplate/Main Subsystems/Control/LgV2/z_1
 * '<S49>'  : StudentTemplate/Main Subsystems/Control/LgV2/z_2
 * '<S50>'  : StudentTemplate/Main Subsystems/Control/LgV2/zeta
 * '<S51>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q eq
 * '<S52>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq
 * '<S53>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq
 * '<S54>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^t eq
 * '<S55>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/f_q^T
 * '<S56>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T
 * '<S57>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq
 * '<S58>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq
 * '<S59>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq
 * '<S60>'  : StudentTemplate/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq
 * '<S61>'  : StudentTemplate/Main Subsystems/Control/LgV2/R(psi)/R^T
 * '<S62>'  : StudentTemplate/Main Subsystems/Control/LgV2/Update laws/Transpose
 * '<S63>'  : StudentTemplate/Main Subsystems/Control/LgV2/V_1^q/Transpose
 * '<S64>'  : StudentTemplate/Main Subsystems/Control/LgV2/sigma/S^T
 * '<S65>'  : StudentTemplate/Main Subsystems/Control/LgV2/sigma/S^T/S(r)
 * '<S66>'  : StudentTemplate/Main Subsystems/Control/LgV2/sigma/S^T/S^T
 * '<S67>'  : StudentTemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi
 * '<S68>'  : StudentTemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1
 * '<S69>'  : StudentTemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]
 * '<S70>'  : StudentTemplate/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]
 * '<S71>'  : StudentTemplate/Main Subsystems/Control/PS3 u input control/Subsystem
 * '<S72>'  : StudentTemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau
 * '<S73>'  : StudentTemplate/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act
 * '<S74>'  : StudentTemplate/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e
 * '<S75>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040
 * '<S76>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/tau to f_act
 * '<S77>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act
 * '<S78>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3
 * '<S79>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3
 * '<S80>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3
 * '<S81>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3
 * '<S82>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4
 * '<S83>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391
 * '<S84>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731
 * '<S85>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391
 * '<S86>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731
 * '<S87>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451
 * '<S88>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451
 * '<S89>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0
 * '<S90>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0
 * '<S91>'  : StudentTemplate/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0
 * '<S92>'  : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following
 * '<S93>'  : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading
 * '<S94>'  : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight
 * '<S95>'  : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path
 * '<S96>'  : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment
 * '<S97>'  : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq
 * '<S98>'  : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq
 * '<S99>'  : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq
 * '<S100>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]
 * '<S101>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot
 * '<S102>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot
 * '<S103>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot
 * '<S104>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading
 * '<S105>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals
 * '<S106>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel
 * '<S107>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq
 * '<S108>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq
 * '<S109>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq
 * '<S110>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq
 * '<S111>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq
 * '<S112>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq
 * '<S113>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq
 * '<S114>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq
 * '<S115>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq
 * '<S116>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq
 * '<S117>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq
 * '<S118>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose
 * '<S119>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose
 * '<S120>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1
 * '<S121>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2
 * '<S122>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq
 * '<S123>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq
 * '<S124>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq
 * '<S125>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq
 * '<S126>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq
 * '<S127>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq
 * '<S128>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]
 * '<S129>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1
 * '<S130>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2
 * '<S131>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2
 * '<S132>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T
 * '<S133>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2
 * '<S134>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)
 * '<S135>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T
 * '<S136>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T
 * '<S137>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq
 * '<S138>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq
 * '<S139>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq
 * '<S140>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I
 * '<S141>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path
 * '<S142>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter
 * '<S143>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path
 * '<S144>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq
 * '<S145>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq
 * '<S146>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq
 * '<S147>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq
 * '<S148>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq
 * '<S149>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T
 * '<S150>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter
 * '<S151>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor
 * '<S152>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor
 * '<S153>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor
 * '<S154>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor
 * '<S155>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1
 * '<S156>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x
 * '<S157>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y
 * '<S158>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq
 * '<S159>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq
 * '<S160>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq
 * '<S161>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T
 * '<S162>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq
 * '<S163>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq
 * '<S164>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq
 * '<S165>' : StudentTemplate/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T
 * '<S166>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT
 * '<S167>' : StudentTemplate/Main Subsystems/Naviagation/Navigation Switch
 * '<S168>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix
 * '<S169>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer
 * '<S170>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau
 * '<S171>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1
 * '<S172>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw
 * '<S173>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1
 * '<S174>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]
 * '<S175>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1
 * '<S176>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act
 * '<S177>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3
 * '<S178>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3
 * '<S179>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3
 * '<S180>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3
 * '<S181>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4
 * '<S182>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391
 * '<S183>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731
 * '<S184>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391
 * '<S185>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731
 * '<S186>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451
 * '<S187>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451
 * '<S188>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0
 * '<S189>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0
 * '<S190>' : StudentTemplate/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0
 * '<S191>' : StudentTemplate/Main Subsystems/Plant/CSE1 actuator
 * '<S192>' : StudentTemplate/Main Subsystems/Plant/Linear Simulator
 * '<S193>' : StudentTemplate/Main Subsystems/Plant/Thruster setting workaround
 * '<S194>' : StudentTemplate/Main Subsystems/Plant/saturation
 * '<S195>' : StudentTemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster
 * '<S196>' : StudentTemplate/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller
 * '<S197>' : StudentTemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic
 * '<S198>' : StudentTemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1
 * '<S199>' : StudentTemplate/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2
 * '<S200>' : StudentTemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics
 * '<S201>' : StudentTemplate/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)
 * '<S202>' : StudentTemplate/Outputs to LabVIEW/Battery Voltage
 * '<S203>' : StudentTemplate/Outputs to LabVIEW/Command
 * '<S204>' : StudentTemplate/Outputs to LabVIEW/Naviagtion
 * '<S205>' : StudentTemplate/Outputs to LabVIEW/Visualization
 */
#endif                                 /* RTW_HEADER_StudentTemplate_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_StudentTemplate
#ifdef RVE
#ifdef MULTITASKING

Parameters_StudentTemplate rtParameter[NUMST+!TID01EQ];

#define StudentTemplate_P              (*param_lookup[tid][READSIDE])

Parameters_StudentTemplate *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_StudentTemplate rtParameter[2];

#define StudentTemplate_P              rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
