/*
 * Template_test.h
 *
 * Real-Time Workshop code generation for Simulink model "Template_test.mdl".
 *
 * Model Version              : 1.13
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Thu Mar 20 15:08:38 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Template_test_h_
#define RTW_HEADER_Template_test_h_
#ifndef Template_test_COMMON_INCLUDES_
# define Template_test_COMMON_INCLUDES_
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
#endif                                 /* Template_test_COMMON_INCLUDES_ */

#include "Template_test_types.h"

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
#define Template_test_rtModel          RT_MODEL_Template_test

/* Block signals (auto storage) */
typedef struct {
  real_T ux3[9];                       /* '<S9>/[3x3]' */
  real_T ux3_g[9];                     /* '<S10>/[3x3]' */
  real_T ux3_f[9];                     /* '<S11>/[3x3]' */
  real_T Resetintegrator;              /* '<S4>/Reset integrator' */
  real_T Gain1;                        /* '<S13>/Gain1' */
  real_T ux2[4];                       /* '<S14>/[2x2]' */
  real_T Initialq_x;                   /* '<S5>/Initial q_x' */
  real_T Initialq_y;                   /* '<S5>/Initial q_y' */
  real_T Initials;                     /* '<S5>/Initial s' */
  real_T ux3_n[9];                     /* '<S15>/[3x3]' */
  real_T ux3_d[9];                     /* '<S16>/[3x3]' */
  real_T ux3_b[9];                     /* '<S17>/[3x3]' */
  real_T Initialpsirad;                /* '<S6>/Initial psi [rad]' */
  real_T Initialxm;                    /* '<S6>/Initial x [m]' */
  real_T Initialym;                    /* '<S6>/Initial y [m]' */
  real_T Initialrrads;                 /* '<S6>/Initial r [rad//s]' */
  real_T Initialums;                   /* '<S6>/Initial u [m//s]' */
  real_T Initialvms;                   /* '<S6>/Initial v [m//s]' */
  real_T xpositionofleftanalogstick11; /* '<S8>/ScalingLX' */
  real_T ypositionofleftanalogstick11; /* '<S8>/ScalingLY' */
  real_T xpositionofrightanalogstick11;/* '<S8>/Scaling_RX' */
  real_T ypositionofrightanalogstick11;/* '<S8>/ScalingRY' */
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
  real_T l_x1_i;                       /* '<S77>/-l_x1' */
  real_T l_y2_f;                       /* '<S77>/-l_y2' */
  real_T l_x2_o;                       /* '<S77>/-l_x2' */
  real_T x5_b[15];                     /* '<S77>/3x5' */
  real_T u_1;                          /* '<S32>/PS3 u_1' */
  real_T u_1tof_1;                     /* '<S76>/u_1 to f_1' */
  real_T u_2;                          /* '<S32>/PS3 u_2' */
  real_T u_2tof_2;                     /* '<S76>/u_2 to f_2' */
  real_T u_3;                          /* '<S32>/PS3 u_3' */
  real_T u_3tof_3;                     /* '<S76>/u_3 to f_3' */
  real_T u_4;                          /* '<S32>/PS3 u_4' */
  real_T u_4tof_4;                     /* '<S76>/u_4 to f_4' */
  real_T BowThrusterdirection;         /* '<S32>/Add' */
  real_T u_5;                          /* '<S32>/PS3 u_5' */
  real_T u_5tof_5;                     /* '<S76>/u_5 to f_5' */
  real_T TmpHiddenBufferAtProductInport2[5];/* 'synthesized block' */
  real_T Product[3];                   /* '<S75>/Product' */
  real_T QTMIn[9];                     /* '<S169>/QTM In' */
  real_T QTMIn3xcoordmm;               /* '<S169>/QTM In3 x-coord [mm]' */
  real_T mm2mx;                        /* '<S169>/mm2m x' */
  real_T QTMIn4ycoordmm;               /* '<S169>/QTM In4 y-coord [mm]' */
  real_T mm2my;                        /* '<S169>/mm2m y' */
  real_T QTMIn6yawdeg;                 /* '<S169>/QTM In6 yaw [deg]' */
  real_T d2ryaw;                       /* '<S169>/d2r yaw' */
  real_T etaSwitch[3];                 /* '<S170>/eta Switch' */
  real_T psi;                          /* '<S30>/yaw angle' */
  real_T Saturation;                   /* '<S36>/Saturation' */
  real_T Sign;                         /* '<S36>/Sign' */
  real_T Gain;                         /* '<S36>/Gain' */
  real_T Sum1;                         /* '<S36>/Sum1' */
  real_T MathFunction;                 /* '<S36>/Math Function' */
  real_T Sum;                          /* '<S36>/Sum' */
  real_T Sum2[3];                      /* '<S30>/Sum2' */
  real_T Saturation_k;                 /* '<S35>/Saturation' */
  real_T Sign_f;                       /* '<S35>/Sign' */
  real_T Gain_k;                       /* '<S35>/Gain' */
  real_T Sum1_j;                       /* '<S35>/Sum1' */
  real_T MathFunction_a;               /* '<S35>/Math Function' */
  real_T Sum_p;                        /* '<S35>/Sum' */
  real_T Row1;                         /* '<S34>/Row1' */
  real_T Row2;                         /* '<S34>/Row2' */
  real_T Row3;                         /* '<S34>/Row3' */
  real_T TmpHiddenBufferAtProductInpor_d[3];/* '<S30>/Transposed rotation  matrix in yaw1' */
  real_T Product_e[3];                 /* '<S30>/Product' */
  real_T Integrator[3];                /* '<S30>/Integrator' */
  real_T Product1[3];                  /* '<S30>/Product1' */
  real_T Sum3[3];                      /* '<S30>/Sum3' */
  real_T QTMIn8rolldeg;                /* '<S169>/QTM In8 roll [deg]' */
  real_T d2rroll;                      /* '<S169>/d2r roll' */
  real_T QTMIn7pitchdeg;               /* '<S169>/QTM In7 pitch [deg]' */
  real_T d2rpitch;                     /* '<S169>/d2r pitch' */
  real_T sintheta[3];                  /* '<S171>/sin(theta)' */
  real_T costheta[3];                  /* '<S171>/cos(theta)' */
  real_T R11;                          /* '<S171>/R11' */
  real_T R21;                          /* '<S171>/R21 ' */
  real_T R31;                          /* '<S171>/R31 ' */
  real_T R12;                          /* '<S171>/R12' */
  real_T R22;                          /* '<S171>/R22' */
  real_T R32;                          /* '<S171>/R32' */
  real_T R13;                          /* '<S171>/R13' */
  real_T R23;                          /* '<S171>/R23' */
  real_T R33;                          /* '<S171>/R33' */
  real_T Reshape9x13x3[9];             /* '<S171>/Reshape 9x1->3x3' */
  real_T MatrixConcatenate2[36];       /* '<S169>/Matrix Concatenate2' */
  real_T QTMIn5zcoordmm;               /* '<S169>/QTM In5 z-coord [mm]' */
  real_T mm2mz;                        /* '<S169>/mm2m z' */
  real_T Derivative[6];                /* '<S169>/Derivative' */
  real_T Product_a[6];                 /* '<S169>/Product' */
  real_T nuSwitch[3];                  /* '<S170>/nu Switch' */
  real_T Product2[3];                  /* '<S30>/Product2' */
  real_T Sum1_b[3];                    /* '<S30>/Sum1' */
  real_T R11_e;                        /* '<S40>/R11' */
  real_T R21_a;                        /* '<S40>/R21' */
  real_T R12_f;                        /* '<S40>/R12' */
  real_T u;                            /* '<S40>/-1' */
  real_T R22_i;                        /* '<S40>/R22' */
  real_T Rpsi[9];                      /* '<S40>/R(psi)' */
  real_T MathFunction_n[9];            /* '<S41>/Math Function' */
  real_T Integrator_b[3];              /* '<S50>/Integrator' */
  real_T Product_l[3];                 /* '<S39>/Product' */
  real_T u_a;                          /* '<S39>/4' */
  real_T Divide;                       /* '<S39>/Divide' */
  real_T Add1[9];                      /* '<S39>/Add1' */
  real_T Product_k[9];                 /* '<S44>/Product' */
  real_T Subtract[9];                  /* '<S44>/Subtract' */
  real_T Saturation_o;                 /* '<S72>/Saturation' */
  real_T Sign_a;                       /* '<S72>/Sign' */
  real_T Gain_c;                       /* '<S72>/Gain' */
  real_T Sum1_j5;                      /* '<S72>/Sum1' */
  real_T MathFunction_m;               /* '<S72>/Math Function' */
  real_T Sum_d;                        /* '<S72>/Sum' */
  real_T Integrator_n[2];              /* '<S42>/Integrator' */
  real_T x_2x_1;                       /* '<S162>/x_2 - x_1' */
  real_T y_2y_1;                       /* '<S162>/y_2 - y_1' */
  real_T TmpHiddenBufferAtProductInpo_dn[2];/* 'synthesized block' */
  real_T Product_h[2];                 /* '<S155>/Product' */
  real_T Integrator1;                  /* '<S42>/Integrator1' */
  real_T Product2_i;                   /* '<S148>/Product2' */
  real_T sins;                         /* '<S148>/sin(s)' */
  real_T Product_eb;                   /* '<S148>/Product' */
  real_T Gain_b;                       /* '<S148>/Gain' */
  real_T coss;                         /* '<S148>/cos(s)' */
  real_T Product1_n;                   /* '<S148>/Product1' */
  real_T TmpHiddenBufferAtProductInpor_l[2];/* 'synthesized block' */
  real_T Subract;                      /* '<S155>/Subract' */
  real_T Product1_m[2];                /* '<S155>/Product1' */
  real_T Add[2];                       /* '<S155>/Add' */
  real_T TrigonometricFunction;        /* '<S100>/Trigonometric Function' */
  real_T Saturation_g;                 /* '<S103>/Saturation' */
  real_T Sign_i;                       /* '<S103>/Sign' */
  real_T Gain_d;                       /* '<S103>/Gain' */
  real_T Sum1_i;                       /* '<S103>/Sum1' */
  real_T MathFunction_j;               /* '<S103>/Math Function' */
  real_T Sum_dn;                       /* '<S103>/Sum' */
  real_T Saturation_l;                 /* '<S131>/Saturation' */
  real_T Sign_ik;                      /* '<S131>/Sign' */
  real_T Gain_h;                       /* '<S131>/Gain' */
  real_T Sum1_c;                       /* '<S131>/Sum1' */
  real_T MathFunction_d;               /* '<S131>/Math Function' */
  real_T Sum_f;                        /* '<S131>/Sum' */
  real_T MathFunction_g[4];            /* '<S135>/Math Function' */
  real_T x_2x_1_k;                     /* '<S161>/x_2 - x_1' */
  real_T x_2x_1s;                      /* '<S161>/(x_2 - x_1) * s' */
  real_T x_2x_1sx_1;                   /* '<S161>/(x_2 - x_1) * s + x_1' */
  real_T y_2y_1_b;                     /* '<S161>/y_2 - y_1' */
  real_T y_2y_1s;                      /* '<S161>/(y_2 - y_1) * s' */
  real_T y_2y_1sy_1;                   /* '<S161>/(y_2 - y_1) * s + y_1' */
  real_T Product_ei[2];                /* '<S154>/Product' */
  real_T Product2_g;                   /* '<S147>/Product2' */
  real_T coss_h;                       /* '<S147>/cos(s)' */
  real_T Product_p;                    /* '<S147>/Product' */
  real_T Add_b;                        /* '<S147>/Add' */
  real_T sins_l;                       /* '<S147>/sin(s)' */
  real_T Product1_a;                   /* '<S147>/Product1' */
  real_T Add1_k;                       /* '<S147>/Add1' */
  real_T Subract_o;                    /* '<S154>/Subract' */
  real_T Product1_h[2];                /* '<S154>/Product1' */
  real_T Add_n[2];                     /* '<S154>/Add' */
  real_T Switch;                       /* '<S159>/Switch' */
  real_T Switch2;                      /* '<S159>/Switch2' */
  real_T Switch_d;                     /* '<S160>/Switch' */
  real_T Switch2_c;                    /* '<S160>/Switch2' */
  real_T Subtract_i[2];                /* '<S97>/Subtract' */
  real_T epsilon[2];                   /* '<S108>/epsilon' */
  real_T MultiportSelector;            /* '<S108>/Multiport Selector' */
  real_T TrigonometricFunction_i;      /* '<S125>/Trigonometric Function' */
  real_T Saturation_m;                 /* '<S132>/Saturation' */
  real_T Sign_m;                       /* '<S132>/Sign' */
  real_T Gain_f;                       /* '<S132>/Gain' */
  real_T Sum1_n;                       /* '<S132>/Sum1' */
  real_T MathFunction_o;               /* '<S132>/Math Function' */
  real_T Sum_d3;                       /* '<S132>/Sum' */
  real_T Subtract_l;                   /* '<S125>/Subtract' */
  real_T Saturation_oa;                /* '<S133>/Saturation' */
  real_T Sign_j;                       /* '<S133>/Sign' */
  real_T Gain_n;                       /* '<S133>/Gain' */
  real_T Sum1_a;                       /* '<S133>/Sum1' */
  real_T MathFunction_p;               /* '<S133>/Math Function' */
  real_T Sum_pn;                       /* '<S133>/Sum' */
  real_T VectorConcatenate[3];         /* '<S109>/Vector Concatenate' */
  real_T Subtract_n[3];                /* '<S48>/Subtract' */
  real_T Saturation_h;                 /* '<S73>/Saturation' */
  real_T Sign_k;                       /* '<S73>/Sign' */
  real_T Gain_p;                       /* '<S73>/Gain' */
  real_T Sum1_g;                       /* '<S73>/Sum1' */
  real_T MathFunction_pi;              /* '<S73>/Math Function' */
  real_T Sum_i;                        /* '<S73>/Sum' */
  real_T TmpHiddenBufferAtProductInpo_lr[3];/* '<S48>/Heading to -pi//pi1' */
  real_T Product_d[3];                 /* '<S48>/Product' */
  real_T Product1_d[3];                /* '<S44>/Product1' */
  real_T f_qx;                         /* '<S110>/f_qx' */
  real_T f_qy;                         /* '<S110>/f_qy' */
  real_T TmpHiddenBufferAtProductInport1[2];/* 'synthesized block' */
  real_T Product_o[2];                 /* '<S110>/Product' */
  real_T Delta2;                       /* '<S126>/Delta^2' */
  real_T epsilon_n2;                   /* '<S126>/epsilon_n^2' */
  real_T Add_g;                        /* '<S126>/Add' */
  real_T Divide_p;                     /* '<S126>/Divide' */
  real_T MultiportSelector1[2];        /* '<S108>/Multiport Selector1' */
  real_T Product_i[2];                 /* '<S126>/Product' */
  real_T u_b[2];                       /* '<S126>/-1' */
  real_T VectorConcatenate_p[3];       /* '<S51>/Vector Concatenate' */
  real_T Product_m[2];                 /* '<S156>/Product' */
  real_T Product2_h;                   /* '<S149>/Product2' */
  real_T coss_c;                       /* '<S149>/cos(s)' */
  real_T MathFunction_i;               /* '<S149>/Math Function' */
  real_T Product_ih;                   /* '<S149>/Product' */
  real_T Gain_nq;                      /* '<S149>/Gain' */
  real_T sins_n;                       /* '<S149>/sin(s)' */
  real_T Product1_di;                  /* '<S149>/Product1' */
  real_T Gain1_b;                      /* '<S149>/Gain1' */
  real_T Subract_e;                    /* '<S156>/Subract' */
  real_T Product1_nf[2];               /* '<S156>/Product1' */
  real_T Add_f[2];                     /* '<S156>/Add' */
  real_T x_dsy_ds2;                    /* '<S101>/x_d^s * y_d^s^2' */
  real_T x_ds2y_ds;                    /* '<S101>/x_d^s^2 * y_d^s' */
  real_T x_dsy_ds2x_ds2y_ds;           /* '<S101>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
  real_T x_ds2;                        /* '<S101>/( x_d^s )^2' */
  real_T y_ds2;                        /* '<S101>/( y_d^s )^2' */
  real_T x_ds2y_ds2;                   /* '<S101>/( x_d^s )^2 + ( y_d^s )^2' */
  real_T Divide_k;                     /* '<S101>/Divide' */
  real_T Delta2_p;                     /* '<S129>/Delta^2' */
  real_T epsilon_n2_b;                 /* '<S129>/epsilon_n^2' */
  real_T Add_p;                        /* '<S129>/Add' */
  real_T Divide_d;                     /* '<S129>/Divide' */
  real_T MathFunction_e[4];            /* '<S139>/Math Function' */
  real_T Product_aj[2];                /* '<S141>/Product' */
  real_T Product1_i[2];                /* '<S141>/Product1' */
  real_T Subtract1[2];                 /* '<S141>/Subtract1' */
  real_T MultiportSelector2;           /* '<S108>/Multiport Selector2' */
  real_T Product_f;                    /* '<S129>/Product' */
  real_T Subtract_h;                   /* '<S129>/Subtract' */
  real_T epsilon_n2_j;                 /* '<S114>/epsilon_n^2' */
  real_T Delta2_n;                     /* '<S114>/Delta^2' */
  real_T Add_i;                        /* '<S114>/Add' */
  real_T sqrt_g;                       /* '<S114>/sqrt' */
  real_T Divide_dt;                    /* '<S114>/Divide' */
  real_T Product_b;                    /* '<S158>/Product' */
  real_T Subract_eq;                   /* '<S158>/Subract' */
  real_T Product1_e;                   /* '<S158>/Product1' */
  real_T Add_e;                        /* '<S158>/Add' */
  real_T Divide_o;                     /* '<S165>/Divide' */
  real_T Product_ey;                   /* '<S114>/Product' */
  real_T MathFunction_b[2];            /* '<S121>/Math Function' */
  real_T Divide_e[2];                  /* '<S118>/Divide' */
  real_T Product_bd;                   /* '<S118>/Product' */
  real_T Gain_a;                       /* '<S118>/Gain' */
  real_T Subtract_d;                   /* '<S114>/Subtract' */
  real_T VectorConcatenate_n[3];       /* '<S57>/Vector Concatenate' */
  real_T Add_l[3];                     /* '<S44>/Add' */
  real_T Product2_d[3];                /* '<S44>/Product2' */
  real_T Sum_e[3];                     /* '<S44>/Sum' */
  real_T Subtract_o[3];                /* '<S49>/Subtract' */
  real_T Product1_k[3];                /* '<S39>/Product1' */
  real_T Product2_i4[3];               /* '<S39>/Product2' */
  real_T Product1_j[9];                /* '<S47>/Product1' */
  real_T Add3[9];                      /* '<S47>/Add3' */
  real_T S12;                          /* '<S68>/S12' */
  real_T Sr[9];                        /* '<S68>/S(r)' */
  real_T MathFunction_k[9];            /* '<S69>/Math Function' */
  real_T Product_c[3];                 /* '<S47>/Product' */
  real_T Add_a[3];                     /* '<S47>/Add' */
  real_T Product2_n[3];                /* '<S47>/Product2' */
  real_T Add1_a[3];                    /* '<S47>/Add1' */
  real_T Product3[3];                  /* '<S47>/Product3' */
  real_T TrigonometricFunction_m;      /* '<S113>/Trigonometric Function' */
  real_T TrigonometricFunction1;       /* '<S113>/Trigonometric Function1' */
  real_T Derivative_g;                 /* '<S99>/Derivative' */
  real_T Product_kh[2];                /* '<S113>/Product' */
  real_T VectorConcatenate_nq[3];      /* '<S54>/Vector Concatenate' */
  real_T epsilon_n2_m;                 /* '<S117>/epsilon_n^2' */
  real_T Delta2_a;                     /* '<S117>/Delta^2' */
  real_T Add_pz;                       /* '<S117>/Add' */
  real_T sqrt_ge;                      /* '<S117>/sqrt' */
  real_T Divide_a;                     /* '<S117>/Divide' */
  real_T Divide_j;                     /* '<S167>/Divide' */
  real_T Product_kl;                   /* '<S117>/Product' */
  real_T VectorConcatenate_b[3];       /* '<S60>/Vector Concatenate' */
  real_T Add2[3];                      /* '<S47>/Add2' */
  real_T Product4[3];                  /* '<S47>/Product4' */
  real_T Sum_l[3];                     /* '<S47>/Sum' */
  real_T Product4_p[3];                /* '<S39>/Product4' */
  real_T Product1_mo[9];               /* '<S45>/Product1' */
  real_T Add_e5[9];                    /* '<S45>/Add' */
  real_T MatrixConcatenate[6];         /* '<S109>/Matrix Concatenate' */
  real_T Product3_i[6];                /* '<S45>/Product3' */
  real_T TrigonometricFunction1_c;     /* '<S111>/Trigonometric Function1' */
  real_T Gain_pg;                      /* '<S111>/Gain' */
  real_T Product1_dm[2];               /* '<S111>/Product1' */
  real_T TrigonometricFunction_k;      /* '<S111>/Trigonometric Function' */
  real_T Product2_a[2];                /* '<S111>/Product2' */
  real_T MatrixConcatenate_o[4];       /* '<S111>/Matrix Concatenate' */
  real_T Product_me[4];                /* '<S111>/Product' */
  real_T MathFunction_m5[2];           /* '<S55>/Math Function' */
  real_T Product2_ho;                  /* '<S127>/Product2' */
  real_T MathFunction_js[2];           /* '<S127>/Math Function' */
  real_T Product3_o[4];                /* '<S127>/Product3' */
  real_T Product4_e[4];                /* '<S127>/Product4' */
  real_T u_g[4];                       /* '<S127>/2' */
  real_T Delta2_e;                     /* '<S127>/Delta^2' */
  real_T epsilon_n2_bp;                /* '<S127>/epsilon_n^2' */
  real_T Add_c;                        /* '<S127>/Add' */
  real_T u_h;                          /* '<S127>/( )^2' */
  real_T Divide_et[4];                 /* '<S127>/Divide' */
  real_T Product1_dz[4];               /* '<S127>/Product1' */
  real_T Divide1[4];                   /* '<S127>/Divide1' */
  real_T Subtract_d1[4];               /* '<S127>/Subtract' */
  real_T MathFunction_ke[4];           /* '<S56>/Math Function' */
  real_T Product_oe[2];                /* '<S52>/Product' */
  real_T Product1_b[2];                /* '<S52>/Product1' */
  real_T Add_pv[2];                    /* '<S52>/Add' */
  real_T MatrixConcatenate_l[6];       /* '<S52>/Matrix Concatenate' */
  real_T Product_a4[2];                /* '<S128>/Product' */
  real_T u_bz[2];                      /* '<S128>/2' */
  real_T Delta2_g;                     /* '<S128>/Delta^2' */
  real_T epsilon_n2_mi;                /* '<S128>/epsilon_n^2' */
  real_T Add_g5;                       /* '<S128>/Add' */
  real_T u_n;                          /* '<S128>/( )^2' */
  real_T Divide_m[2];                  /* '<S128>/Divide' */
  real_T Product1_ha[4];               /* '<S140>/Product1' */
  real_T MultiportSelector3[2];        /* '<S108>/Multiport Selector3' */
  real_T Product1_g[2];                /* '<S128>/Product1' */
  real_T Divide1_a[2];                 /* '<S128>/Divide1' */
  real_T Subtract_l1[2];               /* '<S128>/Subtract' */
  real_T Product_c5[2];                /* '<S58>/Product' */
  real_T Product1_nn[2];               /* '<S115>/Product1' */
  real_T epsilon_n2_h;                 /* '<S115>/epsilon_n^2' */
  real_T Delta2_k;                     /* '<S115>/Delta^2' */
  real_T Add_k;                        /* '<S115>/Add' */
  real_T u2;                           /* '<S115>/^3//2' */
  real_T Divide_n[2];                  /* '<S115>/Divide' */
  real_T Product_d0[2];                /* '<S115>/Product' */
  real_T MathFunction_e5[2];           /* '<S122>/Math Function' */
  real_T Divide_ef[2];                 /* '<S119>/Divide' */
  real_T Product_g[2];                 /* '<S119>/Product' */
  real_T Gain_cj[2];                   /* '<S119>/Gain' */
  real_T Sum_la[2];                    /* '<S115>/Sum' */
  real_T Product1_az[2];               /* '<S58>/Product1' */
  real_T Add_av[2];                    /* '<S58>/Add' */
  real_T MatrixConcatenate_b[6];       /* '<S58>/Matrix Concatenate' */
  real_T Add2_d[6];                    /* '<S45>/Add2' */
  real_T Product4_d[6];                /* '<S45>/Product4' */
  real_T Add3_a[6];                    /* '<S45>/Add3' */
  real_T Integrator2[2];               /* '<S42>/Integrator2' */
  real_T Add2_a[2];                    /* '<S39>/Add2' */
  real_T Product5[3];                  /* '<S39>/Product5' */
  real_T Product1_l[9];                /* '<S46>/Product1' */
  real_T Add1_g[9];                    /* '<S46>/Add1' */
  real_T VectorConcatenate1[3];        /* '<S109>/Vector Concatenate1' */
  real_T Product3_f[3];                /* '<S46>/Product3' */
  real_T TrigonometricFunction1_b;     /* '<S112>/Trigonometric Function1' */
  real_T Gain_dr;                      /* '<S112>/Gain' */
  real_T Product1_c;                   /* '<S112>/Product1' */
  real_T TrigonometricFunction_o;      /* '<S112>/Trigonometric Function' */
  real_T Product2_hd;                  /* '<S112>/Product2' */
  real_T TmpHiddenBufferAtProductInpor_o[2];/* 'synthesized block' */
  real_T Product_hn[2];                /* '<S112>/Product' */
  real_T Product_lz;                   /* '<S53>/Product' */
  real_T Product1_cf;                  /* '<S53>/Product1' */
  real_T VectorConcatenate_g[3];       /* '<S53>/Vector Concatenate' */
  real_T Product_pb[2];                /* '<S157>/Product' */
  real_T Product2_dr;                  /* '<S150>/Product2' */
  real_T sins3;                        /* '<S150>/sin(s)3' */
  real_T MathFunction_dq;              /* '<S150>/Math Function' */
  real_T Product_ch;                   /* '<S150>/Product' */
  real_T coss3;                        /* '<S150>/cos(s)3' */
  real_T Product1_en;                  /* '<S150>/Product1' */
  real_T Gain_o;                       /* '<S150>/Gain' */
  real_T Subract_e3;                   /* '<S157>/Subract' */
  real_T Product1_kt[2];               /* '<S157>/Product1' */
  real_T Add_ej[2];                    /* '<S157>/Add' */
  real_T x_dsy_ds3;                    /* '<S102>/x_d^s * y_d^s^3 ' */
  real_T x_ds3y_ds;                    /* '<S102>/x_d^s^3 * y_d^s' */
  real_T x_dsy_ds3x_ds3y_ds;           /* '<S102>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
  real_T Product1_g2;                  /* '<S102>/Product1' */
  real_T x_dsx_ds2;                    /* '<S102>/x_d^s * x_d^s^2' */
  real_T y_dsy_ds2;                    /* '<S102>/y_d^s * y_d^s^2' */
  real_T x_dsx_ds2x_ds3y_ds;           /* '<S102>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
  real_T u_ab;                         /* '<S102>/+ 2' */
  real_T Product2_d2;                  /* '<S102>/Product2' */
  real_T Subtract_n5;                  /* '<S102>/Subtract' */
  real_T x_ds2y_ds22;                  /* '<S102>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
  real_T Divide_d3;                    /* '<S102>/Divide' */
  real_T epsilon_ns2;                  /* '<S130>/(epsilon_n^s)^2' */
  real_T Product_ol;                   /* '<S130>/Product' */
  real_T u_j;                          /* '<S130>/2' */
  real_T Delta2_p4;                    /* '<S130>/Delta^2' */
  real_T epsilon_n2_n;                 /* '<S130>/epsilon_n^2' */
  real_T Add_nw;                       /* '<S130>/Add' */
  real_T u_o;                          /* '<S130>/( )^2' */
  real_T Divide_pq;                    /* '<S130>/Divide' */
  real_T MathFunction_l[4];            /* '<S138>/Math Function' */
  real_T Product_k4[4];                /* '<S142>/Product' */
  real_T Add_an[4];                    /* '<S142>/Add' */
  real_T Product1_hn[2];               /* '<S142>/Product1' */
  real_T Product2_o[2];                /* '<S142>/Product2' */
  real_T u_p[2];                       /* '<S142>/2' */
  real_T Product3_m[2];                /* '<S142>/Product3' */
  real_T Sum_m[2];                     /* '<S142>/Sum' */
  real_T Gain_e[2];                    /* '<S142>/Gain' */
  real_T MultiportSelector4;           /* '<S108>/Multiport Selector4' */
  real_T Product1_je;                  /* '<S130>/Product1' */
  real_T Divide1_j;                    /* '<S130>/Divide1' */
  real_T Sum_iy;                       /* '<S130>/Sum' */
  real_T Product_m2;                   /* '<S59>/Product' */
  real_T MathFunction_jy[2];           /* '<S168>/Math Function' */
  real_T Product1_lg;                  /* '<S166>/Product1' */
  real_T p_ds3;                        /* '<S166>/|p_d^s|^3' */
  real_T Divide_jj;                    /* '<S166>/Divide' */
  real_T Product_j;                    /* '<S166>/Product' */
  real_T Gain_ds;                      /* '<S166>/Gain' */
  real_T epsilon_n2_jy;                /* '<S116>/epsilon_n^2' */
  real_T Delta2_gi;                    /* '<S116>/Delta^2' */
  real_T Add_if;                       /* '<S116>/Add' */
  real_T MathFunction_pl;              /* '<S116>/Math Function' */
  real_T Divide_ep;                    /* '<S116>/Divide' */
  real_T Product1_cj;                  /* '<S116>/Product1' */
  real_T Product2_ak;                  /* '<S116>/Product2' */
  real_T u2_h;                         /* '<S116>/^3//2' */
  real_T Divide1_d;                    /* '<S116>/Divide1' */
  real_T Product3_mg;                  /* '<S116>/Product3' */
  real_T Product1_p;                   /* '<S120>/Product1' */
  real_T MathFunction_eo[2];           /* '<S124>/Math Function' */
  real_T Divide2[2];                   /* '<S120>/Divide2' */
  real_T MathFunction_i2[2];           /* '<S123>/Math Function' */
  real_T Product2_nd[2];               /* '<S120>/Product2' */
  real_T MathFunction_py;              /* '<S120>/Math Function' */
  real_T Divide1_jw[2];                /* '<S120>/Divide1' */
  real_T Subtract1_k[2];               /* '<S120>/Subtract1' */
  real_T Product_o1;                   /* '<S120>/Product' */
  real_T Subtract_i2;                  /* '<S120>/Subtract' */
  real_T Sum_fp;                       /* '<S116>/Sum' */
  real_T Product1_a3;                  /* '<S59>/Product1' */
  real_T VectorConcatenate_e[3];       /* '<S59>/Vector Concatenate' */
  real_T Add2_l[3];                    /* '<S46>/Add2' */
  real_T Product4_g[3];                /* '<S46>/Product4' */
  real_T Add3_j[3];                    /* '<S46>/Add3' */
  real_T Product6[3];                  /* '<S39>/Product6' */
  real_T Sum_po[3];                    /* '<S39>/Sum' */
  real_T tauSwitch[3];                 /* '<S29>/tau Switch' */
  real_T Add_lp[2];                    /* '<S42>/Add' */
  real_T MathFunction_kw[3];           /* '<S62>/Math Function' */
  real_T Product_py[2];                /* '<S43>/Product' */
  real_T Gain_i[2];                    /* '<S43>/Gain' */
  real_T MathFunction_ln[2];           /* '<S61>/Math Function' */
  real_T Product_ce[2];                /* '<S42>/Product' */
  real_T Add1_f[2];                    /* '<S42>/Add1' */
  real_T Product1_kn[2];               /* '<S42>/Product1' */
  real_T Gain_kq[2];                   /* '<S42>/Gain' */
  real_T Product_n[3];                 /* '<S50>/Product' */
  real_T Pseudoinverse[15];            /* '<S79>/Pseudoinverse' */
  real_T Product_jq[5];                /* '<S79>/Product' */
  real_T f_1tou_1;                     /* '<S81>/f_1 to u_1' */
  real_T f_2000391;                    /* '<S82>/f_2 < 0.00391' */
  real_T f_2006731f_2000391;           /* '<S82>/f_2 < 0.06731 && f_2 >= 0.00391' */
  real_T f_2006731;                    /* '<S82>/f_2 => 0.06731' */
  real_T MultiportSwitch;              /* '<S82>/Multiport Switch' */
  real_T f_3tou_3;                     /* '<S83>/f_3 to u_3' */
  real_T f_400451;                     /* '<S84>/f_4 < 0.0451' */
  real_T f_400451_p;                   /* '<S84>/f_4 >= 0.0451 ' */
  real_T MultiportSwitch_m;            /* '<S84>/Multiport Switch' */
  real_T DeadZone001;                  /* '<S85>/Dead Zone +-0.01' */
  real_T f_50;                         /* '<S85>/f_5 < 0' */
  real_T f_50_g;                       /* '<S85>/f_5 > 0' */
  real_T MultiportSwitch_c;            /* '<S85>/Multiport Switch' */
  real_T Saturation_he[7];             /* '<S33>/Saturation' */
  real_T QTMIn2Error;                  /* '<S169>/QTM In2 Error' */
  real_T QTMIn9Residual;               /* '<S169>/QTM In9 Residual' */
  real_T Derivative1[3];               /* '<S169>/Derivative1' */
  real_T etadotSwitch[3];              /* '<S170>/etadot Switch' */
  real_T Saturation_d;                 /* '<S174>/Saturation' */
  real_T tauSwitch_k[7];               /* '<S174>/tau Switch' */
  real_T TmpHiddenBufferAtToFileInport1[38];/* 'synthesized block' */
  real_T MathFunction_gc[2];           /* '<S152>/Math Function' */
  real_T Product_dc;                   /* '<S151>/Product' */
  real_T sqrt_h;                       /* '<S151>/sqrt' */
  real_T MathFunction_jd[2];           /* '<S164>/Math Function' */
  real_T Product_ha;                   /* '<S163>/Product' */
  real_T sqrt_hn;                      /* '<S163>/sqrt' */
  real_T QTMIn1FPS;                    /* '<S169>/QTM In1 FPS' */
  real_T SITzAI0;                      /* '<S169>/SIT zAI0' */
  real_T SITzAI1;                      /* '<S169>/SIT zAI1' */
  real_T SITzAI2;                      /* '<S169>/SIT zAI2' */
  real_T Inverse[9];                   /* '<S25>/Inverse' */
  real_T Saturation_kh;                /* '<S175>/Saturation' */
  real_T Saturation1;                  /* '<S175>/Saturation1' */
  real_T Saturation2;                  /* '<S175>/Saturation2' */
  real_T planttau_surge;               /* '<S175>/plant tau_surge' */
  real_T planttau_sway;                /* '<S175>/plant tau_sway' */
  real_T planttau_yaw;                 /* '<S175>/plant tau_yaw' */
  real_T BatteryBowThruster;           /* '<S183>/Battery Bow Thruster' */
  real_T BatteryMain;                  /* '<S183>/Battery Main' */
  real_T BatteryServo;                 /* '<S183>/Battery Servo' */
  real_T CSE1_Yawdeg;                  /* '<S184>/CSE1_Yaw [deg]' */
  real_T CSE1_xm;                      /* '<S184>/CSE1_x [m]' */
  real_T CSE1_ym;                      /* '<S184>/CSE1_y [m]' */
  real_T CSE1_rdegs;                   /* '<S184>/CSE1_r [deg//s]' */
  real_T CSE1_ums;                     /* '<S184>/CSE1_u [m//s]' */
  real_T CSE1_vms;                     /* '<S184>/CSE1_v [m//s]' */
  real_T QS_Yawdeg;                    /* '<S184>/QS_Yaw [deg]' */
  real_T QS_xm;                        /* '<S184>/QS_x [m]' */
  real_T QS_ym;                        /* '<S184>/QS_y [m]' */
  real_T LS_Yawdeg;                    /* '<S184>/LS_Yaw [deg]' */
  real_T LS_xm;                        /* '<S184>/LS_x [m]' */
  real_T LS_ym;                        /* '<S184>/LS_y [m]' */
  real_T plantBTpower;                 /* '<S185>/plant BT power' */
  real_T plantVSPspeed;                /* '<S185>/plant VSP speed' */
  real_T plantu_1;                     /* '<S185>/plant u_1' */
  real_T plantu_2;                     /* '<S185>/plant u_2' */
  real_T plantu_3;                     /* '<S185>/plant u_3' */
  real_T plantu_4;                     /* '<S185>/plant u_4' */
  real_T plantu_5;                     /* '<S185>/plant u_5' */
  real_T eta_psirad;                   /* '<S186>/eta_psi [rad]' */
  real_T eta_psidrad;                  /* '<S186>/eta_psid [rad]' */
  real_T eta_xm;                       /* '<S186>/eta_x [m]' */
  real_T eta_xdm;                      /* '<S186>/eta_xd [m]' */
  real_T eta_ym;                       /* '<S186>/eta_y [m]' */
  real_T eta_ydm;                      /* '<S186>/eta_yd [m]' */
  real_T psi_losrad;                   /* '<S186>/psi_los [rad]' */
  real_T psi_plot[3];                  /* '<S186>/psi_plot' */
  real_T q_xm;                         /* '<S186>/q_x [m]' */
  real_T q_ym;                         /* '<S186>/q_y [m]' */
  real_T x_plot[3];                    /* '<S186>/x_plot' */
  real_T y_plot[3];                    /* '<S186>/y_plot' */
  real_T Integrator_j[3];              /* '<S181>/Integrator' */
  real_T Integrator1_o[3];             /* '<S181>/Integrator1' */
  real_T R11_k;                        /* '<S182>/R11' */
  real_T R21_n;                        /* '<S182>/R21' */
  real_T R12_fw;                       /* '<S182>/R12' */
  real_T R22_e;                        /* '<S182>/R22' */
  real_T Rpsi_c[9];                    /* '<S182>/R(psi)' */
  real_T Product3_n[3];                /* '<S181>/Product3' */
  real_T Product1_gl[3];               /* '<S181>/Product1' */
  real_T Sum_ib[3];                    /* '<S181>/Sum' */
  real_T Product2_i1[3];               /* '<S181>/Product2' */
  real_T BT_D_Gain1;                   /* '<S176>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S176>/BT_D_Gain2' */
  real_T Add_h;                        /* '<S176>/Add' */
  real_T BT_L_Gain1;                   /* '<S176>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S176>/BT_L_Gain2' */
  real_T Neg;                          /* '<S176>/Neg' */
  real_T Sum1_ac;                      /* '<S176>/Sum1' */
  real_T Sum2_m;                       /* '<S176>/Sum2' */
  real_T Switch_h;                     /* '<S178>/Switch' */
  real_T Switch2_e;                    /* '<S178>/Switch2' */
  real_T Switch_p;                     /* '<S179>/Switch' */
  real_T Switch2_j;                    /* '<S179>/Switch2' */
  real_T Switch_m;                     /* '<S180>/Switch' */
  real_T Switch2_f;                    /* '<S180>/Switch2' */
  real_T Sign_e;                       /* '<S177>/Sign' */
  real_T PortVPS_X;                    /* '<S177>/Product1' */
  real_T PortVPS_X_d;                  /* '<S177>/-x' */
  real_T PortVSP_Y;                    /* '<S177>/Product2' */
  real_T PortVSP_Y_g;                  /* '<S177>/-y' */
  real_T StarboardVSP_X;               /* '<S177>/Product3' */
  real_T StarboardVSP_Y;               /* '<S177>/Product4' */
  real_T Servo1;                       /* '<S177>/Servo1' */
  real_T Servo2;                       /* '<S177>/Servo2' */
  real_T Servo3;                       /* '<S177>/Servo3' */
  real_T Servo4;                       /* '<S177>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S177>/VPS_Speed_Gain' */
  real_T Sum_dnw;                      /* '<S177>/Sum' */
  real_T VSPSPort;                     /* '<S177>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S177>/VSPS Starboard' */
  real_T S12_j;                        /* '<S137>/S12' */
  real_T S_2psi_ds2[4];                /* '<S137>/S_2(psi_d^s^2)' */
  real_T S12_l;                        /* '<S136>/S12' */
  real_T S_2psi_ds[4];                 /* '<S136>/S_2(psi_d^s)' */
  real_T R11_b;                        /* '<S134>/R11' */
  real_T R21_k;                        /* '<S134>/R21' */
  real_T R12_i;                        /* '<S134>/R12' */
  real_T R22_m;                        /* '<S134>/R22' */
  real_T R_2psi_d[4];                  /* '<S134>/R_2(psi_d)' */
  uint16_T Gain1_k;                    /* '<S82>/Gain1' */
  uint16_T Sum_e0;                     /* '<S82>/Sum' */
  uint16_T Gain_j;                     /* '<S84>/Gain' */
  uint16_T Sum_n;                      /* '<S84>/Sum' */
  uint16_T Gain_jt;                    /* '<S85>/Gain' */
  uint16_T Gain1_m;                    /* '<S85>/Gain1' */
  uint16_T Sum_g;                      /* '<S85>/Sum' */
  uint8_T Compare;                     /* '<S86>/Compare' */
  uint8_T Compare_m;                   /* '<S88>/Compare' */
  uint8_T Compare_l;                   /* '<S87>/Compare' */
  uint8_T Sum1_iu;                     /* '<S82>/Sum1' */
  uint8_T Compare_e;                   /* '<S89>/Compare' */
  uint8_T Compare_d;                   /* '<S90>/Compare' */
  uint8_T Compare_g;                   /* '<S91>/Compare' */
  uint8_T Compare_a;                   /* '<S92>/Compare' */
  uint8_T Compare_b;                   /* '<S94>/Compare' */
  uint8_T Compare_aa;                  /* '<S93>/Compare' */
  boolean_T LowerRelop1;               /* '<S159>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S159>/UpperRelop' */
  boolean_T LowerRelop1_g;             /* '<S160>/LowerRelop1' */
  boolean_T UpperRelop_d;              /* '<S160>/UpperRelop' */
  boolean_T LogicalOperator;           /* '<S82>/Logical Operator' */
  boolean_T LowerRelop1_c;             /* '<S178>/LowerRelop1' */
  boolean_T UpperRelop_k;              /* '<S178>/UpperRelop' */
  boolean_T LowerRelop1_o;             /* '<S179>/LowerRelop1' */
  boolean_T UpperRelop_g;              /* '<S179>/UpperRelop' */
  boolean_T LowerRelop1_on;            /* '<S180>/LowerRelop1' */
  boolean_T UpperRelop_d5;             /* '<S180>/UpperRelop' */
} BlockIO_Template_test;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Product_DWORK1;               /* '<S118>/Product' */
  real_T Product3_DWORK1[6];           /* '<S45>/Product3' */
  real_T Pseudoinverse_X[15];          /* '<S79>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S79>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S79>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S79>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S79>/Pseudoinverse' */
  real_T Inverse_DWORK3[9];            /* '<S25>/Inverse' */
  real_T Inverse_DWORK4[9];            /* '<S25>/Inverse' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[6];
    real_T TimeStampB;
    real_T LastUAtTimeB[6];
  } Derivative_RWORK;                  /* '<S169>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_o;                /* '<S99>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[3];
    real_T TimeStampB;
    real_T LastUAtTimeB[3];
  } Derivative1_RWORK;                 /* '<S169>/Derivative1' */

  struct {
    void *FilePtr;
    void *LogFilePtr;
  } ToFile_PWORK;                      /* '<S22>/To File' */

  int32_T Inverse_DWORK2[3];           /* '<S25>/Inverse' */
  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  uint32_T Sum1_DWORK1;                /* '<S82>/Sum1' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S82>/Sum' */
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
  } Integrator_IWORK_f;                /* '<S181>/Integrator' */

  struct {
    int_T IcNeedsLoading;
  } Integrator1_IWORK_o;               /* '<S181>/Integrator1' */

  int_T LinearSimulator_MODE;          /* '<S25>/Linear Simulator' */
  int_T CSE1actuator_MODE;             /* '<S25>/CSE1 actuator' */
  uint8_T SignalProbe_DWORK1[14];      /* '<Root>/SignalProbe' */
} D_Work_Template_test;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S30>/Integrator' */
  real_T Integrator_CSTATE_m[3];       /* '<S50>/Integrator' */
  real_T Integrator_CSTATE_f[2];       /* '<S42>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S42>/Integrator1' */
  real_T Integrator2_CSTATE[2];        /* '<S42>/Integrator2' */
  real_T Integrator_CSTATE_p[3];       /* '<S181>/Integrator' */
  real_T Integrator1_CSTATE_d[3];      /* '<S181>/Integrator1' */
} ContinuousStates_Template_test;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S30>/Integrator' */
  real_T Integrator_CSTATE_m[3];       /* '<S50>/Integrator' */
  real_T Integrator_CSTATE_f[2];       /* '<S42>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S42>/Integrator1' */
  real_T Integrator2_CSTATE[2];        /* '<S42>/Integrator2' */
  real_T Integrator_CSTATE_p[3];       /* '<S181>/Integrator' */
  real_T Integrator1_CSTATE_d[3];      /* '<S181>/Integrator1' */
} StateDerivatives_Template_test;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S30>/Integrator' */
  boolean_T Integrator_CSTATE_m[3];    /* '<S50>/Integrator' */
  boolean_T Integrator_CSTATE_f[2];    /* '<S42>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S42>/Integrator1' */
  boolean_T Integrator2_CSTATE[2];     /* '<S42>/Integrator2' */
  boolean_T Integrator_CSTATE_p[3];    /* '<S181>/Integrator' */
  boolean_T Integrator1_CSTATE_d[3];   /* '<S181>/Integrator1' */
} StateDisabled_Template_test;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     /* '<S30>/Integrator' */
  ZCSigState Integrator_Reset_ZCE_e;   /* '<S42>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S42>/Integrator1' */
  ZCSigState Integrator2_Reset_ZCE;    /* '<S42>/Integrator2' */
  ZCSigState Integrator_Reset_ZCE_h;   /* '<S181>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE_o;  /* '<S181>/Integrator1' */
} PrevZCSigStates_Template_test;

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
   * '<S108>/Multiport Selector'
   * '<S108>/Multiport Selector1'
   * '<S108>/Multiport Selector2'
   * '<S108>/Multiport Selector3'
   * '<S108>/Multiport Selector4'
   */
  int32_T pooled1;
} ConstParam_Template_test;

/* Backward compatible GRT Identifiers */
#define rtB                            Template_test_B
#define BlockIO                        BlockIO_Template_test
#define rtX                            Template_test_X
#define ContinuousStates               ContinuousStates_Template_test
#define rtP                            Template_test_P
#define Parameters                     Parameters_Template_test
#define rtDWork                        Template_test_DWork
#define D_Work                         D_Work_Template_test
#define ConstParam                     ConstParam_Template_test
#define rtcP                           Template_test_ConstP
#define rtPrevZCSigState               Template_test_PrevZCSigState
#define PrevZCSigStates                PrevZCSigStates_Template_test

/* Parameters (auto storage) */
struct Parameters_Template_test_ {
  real_T ControlInputSelector_Value;   /* Expression: 0
                                        * '<S1>/Control Input Selector'
                                        */
  real_T ControlModeSelector_Value;    /* Expression: 0
                                        * '<S1>/Control Mode Selector'
                                        */
  real_T EnableCSE1_Value;             /* Expression: 0
                                        * '<S1>/Enable CSE1'
                                        */
  real_T u_Value;                      /* Expression: 0
                                        * '<S9>/12'
                                        */
  real_T u_Value_m;                    /* Expression: 0
                                        * '<S9>/13'
                                        */
  real_T u_Value_g;                    /* Expression: 0
                                        * '<S9>/21'
                                        */
  real_T u_Value_e;                    /* Expression: 0
                                        * '<S9>/23'
                                        */
  real_T u_Value_a;                    /* Expression: 0
                                        * '<S9>/31'
                                        */
  real_T u_Value_mz;                   /* Expression: 0
                                        * '<S9>/32'
                                        */
  real_T K_d_Surge_Value;              /* Expression: 50
                                        * '<S4>/K_d_Surge'
                                        */
  real_T K_d_Sway_Value;               /* Expression: 30
                                        * '<S4>/K_d_Sway'
                                        */
  real_T K_d_Yaw_Value;                /* Expression: 5
                                        * '<S4>/K_d_Yaw'
                                        */
  real_T u_Value_f;                    /* Expression: 0
                                        * '<S10>/12'
                                        */
  real_T u_Value_n;                    /* Expression: 0
                                        * '<S10>/13'
                                        */
  real_T u_Value_n2;                   /* Expression: 0
                                        * '<S10>/21'
                                        */
  real_T u_Value_j;                    /* Expression: 0
                                        * '<S10>/23'
                                        */
  real_T u_Value_gv;                   /* Expression: 0
                                        * '<S10>/31'
                                        */
  real_T u_Value_k;                    /* Expression: 0
                                        * '<S10>/32'
                                        */
  real_T K_i_Surge_Value;              /* Expression: 0
                                        * '<S4>/K_i_Surge'
                                        */
  real_T K_i_Sway_Value;               /* Expression: 0
                                        * '<S4>/K_i_Sway'
                                        */
  real_T K_i_Yaw_Value;                /* Expression: 0
                                        * '<S4>/K_i_Yaw'
                                        */
  real_T u_Value_i;                    /* Expression: 0
                                        * '<S11>/12'
                                        */
  real_T u_Value_l;                    /* Expression: 0
                                        * '<S11>/13'
                                        */
  real_T u_Value_el;                   /* Expression: 0
                                        * '<S11>/21'
                                        */
  real_T u_Value_d;                    /* Expression: 0
                                        * '<S11>/23'
                                        */
  real_T u_Value_jw;                   /* Expression: 0
                                        * '<S11>/31'
                                        */
  real_T u_Value_n4;                   /* Expression: 0
                                        * '<S11>/32'
                                        */
  real_T K_p_Surge_Value;              /* Expression: 2*1.5*2
                                        * '<S4>/K_p_Surge'
                                        */
  real_T K_p_Sway_Value;               /* Expression: 2*10*2
                                        * '<S4>/K_p_Sway'
                                        */
  real_T K_p_Yaw_Value;                /* Expression: 0.5*3
                                        * '<S4>/K_p_Yaw'
                                        */
  real_T Resetintegrator_Value;        /* Expression: 0
                                        * '<S4>/Reset integrator'
                                        */
  real_T y_dm_Value;                   /* Expression: 0
                                        * '<S12>/ y_d [m]'
                                        */
  real_T psi_ddeg_Value;               /* Expression: 0
                                        * '<S12>/psi_d [deg]'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * '<S13>/Gain1'
                                        */
  real_T x_dm_Value;                   /* Expression: 0
                                        * '<S12>/x_d [m]'
                                        */
  real_T u_Value_p;                    /* Expression: 0
                                        * '<S14>/12'
                                        */
  real_T u_Value_ab;                   /* Expression: 0
                                        * '<S14>/21'
                                        */
  real_T Gamma_q_Surge_Value;          /* Expression: 10*2
                                        * '<S5>/Gamma_q_Surge'
                                        */
  real_T Gamma_q_Sway_Value;           /* Expression: 10*10
                                        * '<S5>/Gamma_q_Sway'
                                        */
  real_T Initialq_x_Value;             /* Expression: 0
                                        * '<S5>/Initial q_x'
                                        */
  real_T Initialq_y_Value;             /* Expression: 0
                                        * '<S5>/Initial q_y'
                                        */
  real_T Initials_Value;               /* Expression: 0
                                        * '<S5>/Initial s'
                                        */
  real_T u_Value_pk;                   /* Expression: 0
                                        * '<S15>/12'
                                        */
  real_T u_Value_n21;                  /* Expression: 0
                                        * '<S15>/13'
                                        */
  real_T u_Value_ni;                   /* Expression: 0
                                        * '<S15>/21'
                                        */
  real_T u_Value_pe;                   /* Expression: 0
                                        * '<S15>/23'
                                        */
  real_T u_Value_jr;                   /* Expression: 0
                                        * '<S15>/31'
                                        */
  real_T u_Value_gl;                   /* Expression: 0
                                        * '<S15>/32'
                                        */
  real_T K_d_Surge_Value_j;            /* Expression: 50
                                        * '<S5>/K_d_Surge'
                                        */
  real_T K_d_Sway_Value_a;             /* Expression: 30
                                        * '<S5>/K_d_Sway'
                                        */
  real_T K_d_Yaw_Value_i;              /* Expression: 5
                                        * '<S5>/K_d_Yaw'
                                        */
  real_T u_Value_c;                    /* Expression: 0
                                        * '<S16>/12'
                                        */
  real_T u_Value_kr;                   /* Expression: 0
                                        * '<S16>/13'
                                        */
  real_T u_Value_mv;                   /* Expression: 0
                                        * '<S16>/21'
                                        */
  real_T u_Value_f2;                   /* Expression: 0
                                        * '<S16>/23'
                                        */
  real_T u_Value_in;                   /* Expression: 0
                                        * '<S16>/31'
                                        */
  real_T u_Value_la;                   /* Expression: 0
                                        * '<S16>/32'
                                        */
  real_T K_i_Surge_Value_o;            /* Expression: 0
                                        * '<S5>/K_i_Surge'
                                        */
  real_T K_i_Sway_Value_o;             /* Expression: 0
                                        * '<S5>/K_i_Sway'
                                        */
  real_T K_i_Yaw_Value_o;              /* Expression: 0
                                        * '<S5>/K_i_Yaw'
                                        */
  real_T u_Value_ex;                   /* Expression: 0
                                        * '<S17>/12'
                                        */
  real_T u_Value_ph;                   /* Expression: 0
                                        * '<S17>/13'
                                        */
  real_T u_Value_lf;                   /* Expression: 0
                                        * '<S17>/21'
                                        */
  real_T u_Value_exm;                  /* Expression: 0
                                        * '<S17>/23'
                                        */
  real_T u_Value_ft;                   /* Expression: 0
                                        * '<S17>/31'
                                        */
  real_T u_Value_db;                   /* Expression: 0
                                        * '<S17>/32'
                                        */
  real_T K_p_Surge_Value_g;            /* Expression: 2*1.5*2
                                        * '<S5>/K_p_Surge'
                                        */
  real_T K_p_Sway_Value_e;             /* Expression: 2*10*2
                                        * '<S5>/K_p_Sway'
                                        */
  real_T K_p_Yaw_Value_c;              /* Expression: 0.5*3
                                        * '<S5>/K_p_Yaw'
                                        */
  real_T kappa_1_Value;                /* Expression: 1
                                        * '<S5>/kappa_1'
                                        */
  real_T lambda_q_Value;               /* Expression: 1
                                        * '<S5>/lambda_q'
                                        */
  real_T Resetomega_q_Value;           /* Expression: 0
                                        * '<S5>/Reset omega_q'
                                        */
  real_T Resetq_Value;                 /* Expression: 0
                                        * '<S5>/Reset q'
                                        */
  real_T Resets_Value;                 /* Expression: 0
                                        * '<S5>/Reset s'
                                        */
  real_T EnableLinearSimulator_Value;  /* Expression: 0
                                        * '<S6>/Enable Linear Simulator'
                                        */
  real_T Initialpsirad_Value;          /* Expression: 0
                                        * '<S6>/Initial psi [rad]'
                                        */
  real_T Initialxm_Value;              /* Expression: 0
                                        * '<S6>/Initial x [m]'
                                        */
  real_T Initialym_Value;              /* Expression: 0
                                        * '<S6>/Initial y [m]'
                                        */
  real_T Initialrrads_Value;           /* Expression: 0
                                        * '<S6>/Initial r [rad//s]'
                                        */
  real_T Initialums_Value;             /* Expression: 0
                                        * '<S6>/Initial u [m//s]'
                                        */
  real_T Initialvms_Value;             /* Expression: 0
                                        * '<S6>/Initial v [m//s]'
                                        */
  real_T ResetLinearSimulatorintegrator_;/* Expression: 0
                                          * '<S6>/Reset Linear Simulator integrator'
                                          */
  real_T Deltam_Value;                 /* Expression: 2
                                        * '<S7>/Delta [m]'
                                        */
  real_T PathSelector_Value;           /* Expression: 0
                                        * '<S7>/Path Selector  [-]'
                                        */
  real_T my_Value;                     /* Expression: 10
                                        * '<S7>/my [-]'
                                        */
  real_T u_dm_Value;                   /* Expression: 0.15
                                        * '<S7>/u_d [m]'
                                        */
  real_T x_dmaxm_Value;                /* Expression: 40
                                        * '<S7>/x_dmax [m]'
                                        */
  real_T x_dminm_Value;                /* Expression: -40
                                        * '<S7>/x_dmin [m]'
                                        */
  real_T y_dmaxm_Value;                /* Expression: 7
                                        * '<S7>/y_dmax [m]'
                                        */
  real_T y_dminm_Value;                /* Expression: -7
                                        * '<S7>/y_dmin [m]'
                                        */
  real_T k_Value;                      /* Expression: pi/180*2
                                        * '<S18>/k [-]'
                                        */
  real_T origin_xm_Value;              /* Expression: 4.5
                                        * '<S18>/origin_x [m]'
                                        */
  real_T origo_ym_Value;               /* Expression: 0
                                        * '<S18>/origo_y [m]'
                                        */
  real_T r_xm_Value;                   /* Expression: 5.5
                                        * '<S18>/r_x [m]'
                                        */
  real_T r_ym_Value;                   /* Expression: 2
                                        * '<S18>/r_y [m]'
                                        */
  real_T x_1m_Value;                   /* Expression: 0
                                        * '<S19>/x_1 [m]'
                                        */
  real_T x_2m_Value;                   /* Expression: 5.5
                                        * '<S19>/x_2 [m]'
                                        */
  real_T y_1m_Value;                   /* Expression: 0
                                        * '<S19>/y_1 [m]'
                                        */
  real_T y_2m_Value;                   /* Expression: 2
                                        * '<S19>/y_2 [m]'
                                        */
  real_T AS_LX_Value;                  /* Expression: 0
                                        * '<S8>/AS_LX [-] '
                                        */
  real_T ScalingLX_Gain;               /* Expression: 1/32767
                                        * '<S8>/ScalingLX'
                                        */
  real_T AS_LY_Value;                  /* Expression: 0
                                        * '<S8>/AS_LY [-]'
                                        */
  real_T ScalingLY_Gain;               /* Expression: 1/32767
                                        * '<S8>/ScalingLY'
                                        */
  real_T AS_RX_Value;                  /* Expression: 0
                                        * '<S8>/AS_RX [-]'
                                        */
  real_T Scaling_RX_Gain;              /* Expression: 1/32767
                                        * '<S8>/Scaling_RX'
                                        */
  real_T AS_RY_Value;                  /* Expression: 0
                                        * '<S8>/AS_RY [-]'
                                        */
  real_T ScalingRY_Gain;               /* Expression: 1/32767
                                        * '<S8>/ScalingRY'
                                        */
  real_T PS3_BT_Power_Value;           /* Expression: 0
                                        * '<S8>/PS3_BT_Power  [-]'
                                        */
  real_T L2_Value;                     /* Expression: 0
                                        * '<S8>/L2 [-]'
                                        */
  real_T PS3_VSP_Speed_Value;          /* Expression: 0
                                        * '<S8>/PS3_VSP_Speed  [-]'
                                        */
  real_T R2_Value;                     /* Expression: 0
                                        * '<S8>/R2 [-]'
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
                                        * '<S77>/T_e11'
                                        */
  real_T T_e21_Value;                  /* Expression: 0
                                        * '<S77>/T_e21'
                                        */
  real_T l_y1_Value_d;                 /* Expression: 0.055
                                        * '<S77>/l_y1'
                                        */
  real_T T_e12_Value;                  /* Expression: 0
                                        * '<S77>/T_e12'
                                        */
  real_T T_e22_Value;                  /* Expression: 1
                                        * '<S77>/T_e22'
                                        */
  real_T l_x1_Value_e;                 /* Expression: 0.45
                                        * '<S77>/l_x1'
                                        */
  real_T l_x1_Gain_j;                  /* Expression: -1
                                        * '<S77>/-l_x1'
                                        */
  real_T T_e13_Value;                  /* Expression: 1
                                        * '<S77>/T_e13'
                                        */
  real_T T_e23_Value;                  /* Expression: 0
                                        * '<S77>/T_e23'
                                        */
  real_T l_y2_Value_g;                 /* Expression: 0.055
                                        * '<S77>/l_y2'
                                        */
  real_T l_y2_Gain_p;                  /* Expression: -1
                                        * '<S77>/-l_y2'
                                        */
  real_T T_e14_Value;                  /* Expression: 0
                                        * '<S77>/T_e14'
                                        */
  real_T T_e24_Value;                  /* Expression: 1
                                        * '<S77>/T_e24'
                                        */
  real_T l_x2_Value_n;                 /* Expression: 0.45
                                        * '<S77>/l_x2'
                                        */
  real_T l_x2_Gain_m;                  /* Expression: -1
                                        * '<S77>/-l_x2'
                                        */
  real_T T_e15_Value;                  /* Expression: 0
                                        * '<S77>/T_e15'
                                        */
  real_T T_e25_Value;                  /* Expression: 1
                                        * '<S77>/T_e25'
                                        */
  real_T l_x3_Value_h;                 /* Expression: 0.385
                                        * '<S77>/l_x3'
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
                                        * '<S76>/u_1 to f_1'
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
                                        * '<S76>/u_1 to f_1'
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
                                        * '<S76>/u_2 to f_2'
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
                                        * '<S76>/u_2 to f_2'
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
                                        * '<S76>/u_3 to f_3'
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
                                        * '<S76>/u_3 to f_3'
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
                                        * '<S76>/u_4 to f_4'
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
                                        * '<S76>/u_4 to f_4'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S32>/PS3 u_5'
                                        */
  real_T u_5tof_5_XData[7];            /* Expression: [-.3:0.1:.3]
                                        * '<S76>/u_5 to f_5'
                                        */
  real_T u_5tof_5_YData[7];            /* Expression: [-1.2630 -1.0309 -0.3808 0 0.3480  0.8290 1.0930]
                                        * '<S76>/u_5 to f_5'
                                        */
  real_T QTMIn_P1;                     /* Expression: width
                                        * '<S169>/QTM In'
                                        */
  real_T QTMIn_P2;                     /* Expression: dtype
                                        * '<S169>/QTM In'
                                        */
  real_T QTMIn_P3;                     /* Expression: portnum
                                        * '<S169>/QTM In'
                                        */
  real_T QTMIn_P4;                     /* Expression: stime
                                        * '<S169>/QTM In'
                                        */
  real_T QTMIn_P5;                     /* Expression: stype
                                        * '<S169>/QTM In'
                                        */
  real_T QTMIn_P6;                     /* Expression: btype
                                        * '<S169>/QTM In'
                                        */
  real_T QTMIn3xcoordmm_Gain;          /* Expression: 1
                                        * '<S169>/QTM In3 x-coord [mm]'
                                        */
  real_T mm2mx_Gain;                   /* Expression: 0.001
                                        * '<S169>/mm2m x'
                                        */
  real_T QTMIn4ycoordmm_Gain;          /* Expression: 1
                                        * '<S169>/QTM In4 y-coord [mm]'
                                        */
  real_T mm2my_Gain;                   /* Expression: 0.001
                                        * '<S169>/mm2m y'
                                        */
  real_T QTMIn6yawdeg_Gain;            /* Expression: 1
                                        * '<S169>/QTM In6 yaw [deg]'
                                        */
  real_T d2ryaw_Gain;                  /* Expression: pi/180
                                        * '<S169>/d2r yaw'
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
  real_T Saturation_UpperSat_d;        /* Expression: 1e10
                                        * '<S35>/Saturation'
                                        */
  real_T Saturation_LowerSat_o;        /* Expression: -1e10
                                        * '<S35>/Saturation'
                                        */
  real_T Gain_Gain_f;                  /* Expression: pi
                                        * '<S35>/Gain'
                                        */
  real_T Constant_Value_a;             /* Expression: 2*pi
                                        * '<S35>/Constant'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * '<S30>/Integrator'
                                        */
  real_T QTMIn8rolldeg_Gain;           /* Expression: 1
                                        * '<S169>/QTM In8 roll [deg]'
                                        */
  real_T d2rroll_Gain;                 /* Expression: pi/180
                                        * '<S169>/d2r roll'
                                        */
  real_T QTMIn7pitchdeg_Gain;          /* Expression: 1
                                        * '<S169>/QTM In7 pitch [deg]'
                                        */
  real_T d2rpitch_Gain;                /* Expression: pi/180
                                        * '<S169>/d2r pitch'
                                        */
  real_T Constant1_Value[9];           /* Expression: zeros(3)
                                        * '<S169>/Constant1'
                                        */
  real_T QTMIn5zcoordmm_Gain;          /* Expression: 1
                                        * '<S169>/QTM In5 z-coord [mm]'
                                        */
  real_T mm2mz_Gain;                   /* Expression: 0.001
                                        * '<S169>/mm2m z'
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
  real_T Integrator_IC_f[3];           /* Expression: [0 0 0]'
                                        * '<S50>/Integrator'
                                        */
  real_T _Value;                       /* Expression: 1
                                        * '<S39>/1'
                                        */
  real_T _Gain;                        /* Expression: 4
                                        * '<S39>/4'
                                        */
  real_T Constant_Value_i[9];          /* Expression: a
                                        * '<S63>/Constant'
                                        */
  real_T Saturation_UpperSat_m;        /* Expression: 1e10
                                        * '<S72>/Saturation'
                                        */
  real_T Saturation_LowerSat_f;        /* Expression: -1e10
                                        * '<S72>/Saturation'
                                        */
  real_T Gain_Gain_o;                  /* Expression: pi
                                        * '<S72>/Gain'
                                        */
  real_T Constant_Value_ah;            /* Expression: 2*pi
                                        * '<S72>/Constant'
                                        */
  real_T Gain_Gain_d;                  /* Expression: -1
                                        * '<S148>/Gain'
                                        */
  real_T Constant_Value_d;             /* Expression: 1
                                        * '<S155>/Constant'
                                        */
  real_T Saturation_UpperSat_j;        /* Expression: 1e10
                                        * '<S103>/Saturation'
                                        */
  real_T Saturation_LowerSat_k;        /* Expression: -1e10
                                        * '<S103>/Saturation'
                                        */
  real_T Gain_Gain_a;                  /* Expression: pi
                                        * '<S103>/Gain'
                                        */
  real_T Constant_Value_g;             /* Expression: 2*pi
                                        * '<S103>/Constant'
                                        */
  real_T Saturation_UpperSat_k;        /* Expression: 1e10
                                        * '<S131>/Saturation'
                                        */
  real_T Saturation_LowerSat_d;        /* Expression: -1e10
                                        * '<S131>/Saturation'
                                        */
  real_T Gain_Gain_l;                  /* Expression: pi
                                        * '<S131>/Gain'
                                        */
  real_T Constant_Value_k;             /* Expression: 2*pi
                                        * '<S131>/Constant'
                                        */
  real_T Constant_Value_p;             /* Expression: 1
                                        * '<S154>/Constant'
                                        */
  real_T Saturation_UpperSat_p;        /* Expression: 1e10
                                        * '<S132>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: -1e10
                                        * '<S132>/Saturation'
                                        */
  real_T Gain_Gain_i;                  /* Expression: pi
                                        * '<S132>/Gain'
                                        */
  real_T Constant_Value_f;             /* Expression: 2*pi
                                        * '<S132>/Constant'
                                        */
  real_T Saturation_UpperSat_kl;       /* Expression: 1e10
                                        * '<S133>/Saturation'
                                        */
  real_T Saturation_LowerSat_ku;       /* Expression: -1e10
                                        * '<S133>/Saturation'
                                        */
  real_T Gain_Gain_e;                  /* Expression: pi
                                        * '<S133>/Gain'
                                        */
  real_T Constant_Value_d1;            /* Expression: 2*pi
                                        * '<S133>/Constant'
                                        */
  real_T Saturation_UpperSat_f;        /* Expression: 1e10
                                        * '<S73>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: -1e10
                                        * '<S73>/Saturation'
                                        */
  real_T Gain_Gain_eb;                 /* Expression: pi
                                        * '<S73>/Gain'
                                        */
  real_T Constant_Value_gp;            /* Expression: 2*pi
                                        * '<S73>/Constant'
                                        */
  real_T u_Gain_d;                     /* Expression: -1
                                        * '<S126>/-1'
                                        */
  real_T _2x1_Value[2];                /* Expression: [0;0]
                                        * '<S57>/0_2x1'
                                        */
  real_T _2x1_Value_m[2];              /* Expression: [0;0]
                                        * '<S146>/0_2x1'
                                        */
  real_T Gain_Gain_ot;                 /* Expression: -1
                                        * '<S149>/Gain'
                                        */
  real_T Gain1_Gain_n;                 /* Expression: -1
                                        * '<S149>/Gain1'
                                        */
  real_T Constant_Value_ie;            /* Expression: 1
                                        * '<S156>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: 1
                                        * '<S158>/Constant'
                                        */
  real_T Gain_Gain_p;                  /* Expression: -1
                                        * '<S118>/Gain'
                                        */
  real_T Constant_Value_aj[9];         /* Expression: a
                                        * '<S66>/Constant'
                                        */
  real_T S11_Value;                    /* Expression: 0
                                        * '<S68>/S11'
                                        */
  real_T R31_Value_d;                  /* Expression: 0
                                        * '<S68>/R31'
                                        */
  real_T S12_Gain;                     /* Expression: 1
                                        * '<S68>/S12'
                                        */
  real_T S22_Value;                    /* Expression: 0
                                        * '<S68>/S22'
                                        */
  real_T S32_Value;                    /* Expression: 0
                                        * '<S68>/S32'
                                        */
  real_T S13_Value;                    /* Expression: 0
                                        * '<S68>/S13'
                                        */
  real_T S23_Value;                    /* Expression: 0
                                        * '<S68>/S23'
                                        */
  real_T S33_Value;                    /* Expression: 1
                                        * '<S68>/S33'
                                        */
  real_T _2x1_Value_i[2];              /* Expression: [0;0]
                                        * '<S60>/0_2x1'
                                        */
  real_T Constant_Value_ks[9];         /* Expression: a
                                        * '<S64>/Constant'
                                        */
  real_T Constant_Value_m[4];          /* Expression: a
                                        * '<S143>/Constant'
                                        */
  real_T Gain_Gain_p5;                 /* Expression: -1
                                        * '<S111>/Gain'
                                        */
  real_T _Gain_e;                      /* Expression: 2
                                        * '<S127>/2'
                                        */
  real_T _2x2_Value[4];                /* Expression: [0 0;0 0]
                                        * '<S108>/0_2x2'
                                        */
  real_T _2x2_Value_j[4];              /* Expression: [0 0; 0 0]
                                        * '<S58>/0_2x2'
                                        */
  real_T _Gain_c;                      /* Expression: 2
                                        * '<S128>/2'
                                        */
  real_T u_Value_pq;                   /* Expression: 3/2
                                        * '<S115>/3//2'
                                        */
  real_T Gain_Gain_g;                  /* Expression: -1
                                        * '<S119>/Gain'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * '<S42>/Integrator2'
                                        */
  real_T Constant_Value_l[9];          /* Expression: a
                                        * '<S65>/Constant'
                                        */
  real_T _2x1_Value_l[2];              /* Expression: [0;0]
                                        * '<S109>/0_2x1'
                                        */
  real_T Gain_Gain_o0;                 /* Expression: -1
                                        * '<S112>/Gain'
                                        */
  real_T _2x1_Value_b[2];              /* Expression: [0;0]
                                        * '<S59>/0_2x1'
                                        */
  real_T Constant_Value_n;             /* Expression: 3
                                        * '<S150>/Constant'
                                        */
  real_T Gain_Gain_ap;                 /* Expression: -1
                                        * '<S150>/Gain'
                                        */
  real_T Constant_Value_a1;            /* Expression: 1
                                        * '<S157>/Constant'
                                        */
  real_T u_Gain_m;                     /* Expression: 2
                                        * '<S102>/+ 2'
                                        */
  real_T _Gain_g;                      /* Expression: 2
                                        * '<S130>/2'
                                        */
  real_T _Gain_o;                      /* Expression: 2
                                        * '<S142>/2'
                                        */
  real_T Gain_Gain_n;                  /* Expression: 1
                                        * '<S142>/Gain'
                                        */
  real_T Constant_Value_da;            /* Expression: 3
                                        * '<S166>/Constant'
                                        */
  real_T Gain_Gain_k;                  /* Expression: -1
                                        * '<S166>/Gain'
                                        */
  real_T u_Value_dh;                   /* Expression: 3/2
                                        * '<S116>/3//2'
                                        */
  real_T Constant_Value_gt;            /* Expression: 3
                                        * '<S120>/Constant'
                                        */
  real_T Gain_Gain_p1;                 /* Expression: -1
                                        * '<S43>/Gain'
                                        */
  real_T Gain_Gain_os;                 /* Expression: -1
                                        * '<S42>/Gain'
                                        */
  real_T f_1tou_1_XData[39];           /* Expression: [-0.6829 -0.6369 -0.5785 -0.5165 -0.4456 -0.3725 -0.3308 -0.2827 -0.2277 -0.1517 -0.1240 -0.0769 -0.0238 0.0039 0.0377 0.0635 0.1051 0.1196 0.1412 0.1721 0.1754 0.1774 0.2104 0.2200 0.2266 0.2673 0.3025 0.3486 0.3896 0.4252 0.4782 0.5164 0.5695 0.6195 0.6723 0.7449 0.7836 0.8414 0.8987 ]
                                        * '<S81>/f_1 to u_1'
                                        */
  real_T f_1tou_1_YData[39];           /* Expression: [-1.0000 -0.9500 -0.9000 -0.8500 -0.8000 -0.7500 -0.7000 -0.6500 -0.6000 -0.5500 -0.5000 -0.4500 -0.4000 -0.3500 -0.3000 -0.2500 -0.2000 -0.1500 -0.1000 -0.0500 0 0.0500 0.1000 0.1500 0.2000 0.2500 0.3000 0.3500 0.4000 0.4500 0.5000 0.5500 0.6000 0.6500 0.7000 0.7500 0.8000 0.8500 0.9000]
                                        * '<S81>/f_1 to u_1'
                                        */
  real_T Constant_Value_e;             /* Expression: const
                                        * '<S86>/Constant'
                                        */
  real_T Constant_Value_fg;            /* Expression: const
                                        * '<S88>/Constant'
                                        */
  real_T Constant_Value_h;             /* Expression: const
                                        * '<S87>/Constant'
                                        */
  real_T Constant_Value_l5;            /* Expression: const
                                        * '<S89>/Constant'
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
                                        * '<S82>/f_2 < 0.00391'
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
                                        * '<S82>/f_2 < 0.00391'
                                        */
  real_T f_2006731f_2000391_XData[3];  /* Expression: [-0.0105
                                          0.0226
                                          0.0673]
                                        * '<S82>/f_2 < 0.06731 && f_2 >= 0.00391'
                                        */
  real_T f_2006731f_2000391_YData[3];  /* Expression: [-0.2000
                                          -0.1500
                                          -0.1000]
                                        * '<S82>/f_2 < 0.06731 && f_2 >= 0.00391'
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
                                        * '<S82>/f_2 => 0.06731'
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
                                        * '<S82>/f_2 => 0.06731'
                                        */
  real_T f_3tou_3_XData[39];           /* Expression: [-0.5408,-0.5036,-0.4487,-0.3802,-0.3147,-0.2525,-0.2338,-0.1568,-0.1034,-0.0647,-0.0054,0.0221,0.0572,0.0747,0.0991,0.1258,0.1385,0.1447,0.1539,0.1625,0.1712,0.1976,0.2258,0.2443,0.3058,0.3460,0.3989,0.4342,0.4932,0.5524,0.5814,0.6394,0.6851,0.7496,0.8081,0.8382,0.8665,0.8767,0.8885]
                                        * '<S83>/f_3 to u_3'
                                        */
  real_T f_3tou_3_YData[39];           /* Expression: [-1.0000,-0.9500,-0.9000,-0.8500,-0.8000,-0.7500,-0.7000,-0.6500,-0.6000,-0.5500,-0.5000,-0.4500,-0.4000,-0.3500,-0.3000,-0.2000,-0.1500,-0.1000,-0.0500,0,0.0500,0.1000,0.1500,0.2000,0.2500,0.3000,0.3500,0.4000,0.4500,0.5000,0.5500,0.6000,0.6500,0.7000,0.7500,0.8000,0.8500,0.9500,1.0000]
                                        * '<S83>/f_3 to u_3'
                                        */
  real_T Constant_Value_dd;            /* Expression: const
                                        * '<S90>/Constant'
                                        */
  real_T Constant_Value_kj;            /* Expression: const
                                        * '<S91>/Constant'
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
                                        * '<S84>/f_4 < 0.0451'
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
                                        * '<S84>/f_4 < 0.0451'
                                        */
  real_T f_400451_XData_h[13];         /* Expression: [0.0431
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
                                        * '<S84>/f_4 >= 0.0451 '
                                        */
  real_T f_400451_YData_b[13];         /* Expression: [0.4000
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
                                        * '<S84>/f_4 >= 0.0451 '
                                        */
  real_T DeadZone001_Start;            /* Expression: -0.01
                                        * '<S85>/Dead Zone +-0.01'
                                        */
  real_T DeadZone001_End;              /* Expression: 0.01
                                        * '<S85>/Dead Zone +-0.01'
                                        */
  real_T Constant_Value_dz;            /* Expression: const
                                        * '<S92>/Constant'
                                        */
  real_T Constant_Value_i4;            /* Expression: const
                                        * '<S93>/Constant'
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
                                        * '<S85>/f_5 < 0'
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
                                        * '<S85>/f_5 < 0'
                                        */
  real_T f_50_Value;                   /* Expression: 0
                                        * '<S85>/f_5 = 0'
                                        */
  real_T f_50_XData_h[10];             /* Expression: [0.0103
                                          0.0743
                                          0.1937
                                          0.3232
                                          0.4342
                                          0.5862
                                          0.7291
                                          0.8697
                                          0.9681
                                          1.0229]
                                        * '<S85>/f_5 > 0'
                                        */
  real_T f_50_YData_m[10];             /* Expression: [0.0300
                                          0.0500
                                          0.0700
                                          0.0900
                                          0.1100
                                          0.1300
                                          0.1500
                                          0.1700
                                          0.1900
                                          0.2000]
                                        * '<S85>/f_5 > 0'
                                        */
  real_T BT_power_limit_Value;         /* Expression: 0.4
                                        * '<S78>/BT_power_limit'
                                        */
  real_T VSP_speeds_Value;             /* Expression: 0.3
                                        * '<S78>/VSP_speeds'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: 1.0
                                        * '<S33>/Saturation'
                                        */
  real_T Saturation_LowerSat_h;        /* Expression: -1.0
                                        * '<S33>/Saturation'
                                        */
  real_T QTMIn2Error_Gain;             /* Expression: 1
                                        * '<S169>/QTM In2 Error'
                                        */
  real_T QTMIn9Residual_Gain;          /* Expression: 1
                                        * '<S169>/QTM In9 Residual'
                                        */
  real_T Saturation_UpperSat_g;        /* Expression: 1
                                        * '<S174>/Saturation'
                                        */
  real_T Saturation_LowerSat_c;        /* Expression: 0
                                        * '<S174>/Saturation'
                                        */
  real_T QTMIn1FPS_Gain;               /* Expression: 1
                                        * '<S169>/QTM In1 FPS'
                                        */
  real_T SITzAI0_P1;                   /* Expression: width
                                        * '<S169>/SIT zAI0'
                                        */
  real_T SITzAI0_P2;                   /* Expression: dtype
                                        * '<S169>/SIT zAI0'
                                        */
  real_T SITzAI0_P3;                   /* Expression: portnum
                                        * '<S169>/SIT zAI0'
                                        */
  real_T SITzAI0_P4;                   /* Expression: stime
                                        * '<S169>/SIT zAI0'
                                        */
  real_T SITzAI0_P5;                   /* Expression: stype
                                        * '<S169>/SIT zAI0'
                                        */
  real_T SITzAI0_P6;                   /* Expression: btype
                                        * '<S169>/SIT zAI0'
                                        */
  real_T SITzAI1_P1;                   /* Expression: width
                                        * '<S169>/SIT zAI1'
                                        */
  real_T SITzAI1_P2;                   /* Expression: dtype
                                        * '<S169>/SIT zAI1'
                                        */
  real_T SITzAI1_P3;                   /* Expression: portnum
                                        * '<S169>/SIT zAI1'
                                        */
  real_T SITzAI1_P4;                   /* Expression: stime
                                        * '<S169>/SIT zAI1'
                                        */
  real_T SITzAI1_P5;                   /* Expression: stype
                                        * '<S169>/SIT zAI1'
                                        */
  real_T SITzAI1_P6;                   /* Expression: btype
                                        * '<S169>/SIT zAI1'
                                        */
  real_T SITzAI2_P1;                   /* Expression: width
                                        * '<S169>/SIT zAI2'
                                        */
  real_T SITzAI2_P2;                   /* Expression: dtype
                                        * '<S169>/SIT zAI2'
                                        */
  real_T SITzAI2_P3;                   /* Expression: portnum
                                        * '<S169>/SIT zAI2'
                                        */
  real_T SITzAI2_P4;                   /* Expression: stime
                                        * '<S169>/SIT zAI2'
                                        */
  real_T SITzAI2_P5;                   /* Expression: stype
                                        * '<S169>/SIT zAI2'
                                        */
  real_T SITzAI2_P6;                   /* Expression: btype
                                        * '<S169>/SIT zAI2'
                                        */
  real_T Saturation_UpperSat_i;        /* Expression: 3
                                        * '<S175>/Saturation'
                                        */
  real_T Saturation_LowerSat_n;        /* Expression: -2.6
                                        * '<S175>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 3
                                        * '<S175>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -3.5
                                        * '<S175>/Saturation1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1.6
                                        * '<S175>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1.5
                                        * '<S175>/Saturation2'
                                        */
  real_T planttau_surge_Gain;          /* Expression: 1
                                        * '<S175>/plant tau_surge'
                                        */
  real_T planttau_sway_Gain;           /* Expression: 1
                                        * '<S175>/plant tau_sway'
                                        */
  real_T planttau_yaw_Gain;            /* Expression: 1
                                        * '<S175>/plant tau_yaw'
                                        */
  real_T BatteryBowThruster_Gain;      /* Expression: 1
                                        * '<S183>/Battery Bow Thruster'
                                        */
  real_T BatteryMain_Gain;             /* Expression: 2
                                        * '<S183>/Battery Main'
                                        */
  real_T BatteryServo_Gain;            /* Expression: 1
                                        * '<S183>/Battery Servo'
                                        */
  real_T CSE1_Yawdeg_Gain;             /* Expression: 180/pi
                                        * '<S184>/CSE1_Yaw [deg]'
                                        */
  real_T CSE1_xm_Gain;                 /* Expression: 1
                                        * '<S184>/CSE1_x [m]'
                                        */
  real_T CSE1_ym_Gain;                 /* Expression: 1
                                        * '<S184>/CSE1_y [m]'
                                        */
  real_T CSE1_rdegs_Gain;              /* Expression: 180/pi
                                        * '<S184>/CSE1_r [deg//s]'
                                        */
  real_T CSE1_ums_Gain;                /* Expression: 1
                                        * '<S184>/CSE1_u [m//s]'
                                        */
  real_T CSE1_vms_Gain;                /* Expression: 1
                                        * '<S184>/CSE1_v [m//s]'
                                        */
  real_T QS_Yawdeg_Gain;               /* Expression: 180/pi
                                        * '<S184>/QS_Yaw [deg]'
                                        */
  real_T QS_xm_Gain;                   /* Expression: 1
                                        * '<S184>/QS_x [m]'
                                        */
  real_T QS_ym_Gain;                   /* Expression: 1
                                        * '<S184>/QS_y [m]'
                                        */
  real_T LS_Yawdeg_Gain;               /* Expression: 180/pi
                                        * '<S184>/LS_Yaw [deg]'
                                        */
  real_T LS_xm_Gain;                   /* Expression: 1
                                        * '<S184>/LS_x [m]'
                                        */
  real_T LS_ym_Gain;                   /* Expression: 1
                                        * '<S184>/LS_y [m]'
                                        */
  real_T plantBTpower_Gain;            /* Expression: 1
                                        * '<S185>/plant BT power'
                                        */
  real_T plantVSPspeed_Gain;           /* Expression: 1
                                        * '<S185>/plant VSP speed'
                                        */
  real_T plantu_1_Gain;                /* Expression: 1
                                        * '<S185>/plant u_1'
                                        */
  real_T plantu_2_Gain;                /* Expression: 1
                                        * '<S185>/plant u_2'
                                        */
  real_T plantu_3_Gain;                /* Expression: 1
                                        * '<S185>/plant u_3'
                                        */
  real_T plantu_4_Gain;                /* Expression: 1
                                        * '<S185>/plant u_4'
                                        */
  real_T plantu_5_Gain;                /* Expression: 1
                                        * '<S185>/plant u_5'
                                        */
  real_T eta_psirad_Gain;              /* Expression: 1
                                        * '<S186>/eta_psi [rad]'
                                        */
  real_T eta_psidrad_Gain;             /* Expression: 1
                                        * '<S186>/eta_psid [rad]'
                                        */
  real_T eta_xm_Gain;                  /* Expression: 1
                                        * '<S186>/eta_x [m]'
                                        */
  real_T eta_xdm_Gain;                 /* Expression: 1
                                        * '<S186>/eta_xd [m]'
                                        */
  real_T eta_ym_Gain;                  /* Expression: 1
                                        * '<S186>/eta_y [m]'
                                        */
  real_T eta_ydm_Gain;                 /* Expression: 1
                                        * '<S186>/eta_yd [m]'
                                        */
  real_T psi_losrad_Gain;              /* Expression: 1
                                        * '<S186>/psi_los [rad]'
                                        */
  real_T psi_plot_Gain;                /* Expression: 1
                                        * '<S186>/psi_plot'
                                        */
  real_T q_xm_Gain;                    /* Expression: 1
                                        * '<S186>/q_x [m]'
                                        */
  real_T q_ym_Gain;                    /* Expression: 1
                                        * '<S186>/q_y [m]'
                                        */
  real_T x_plot_Gain;                  /* Expression: 1
                                        * '<S186>/x_plot'
                                        */
  real_T y_plot_Gain;                  /* Expression: 1
                                        * '<S186>/y_plot'
                                        */
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T R12_Gain;                     /* Expression: -1
                                        * '<S134>/R12'
                                        */
  real_T R22_Gain;                     /* Expression: 1
                                        * '<S134>/R22'
                                        */
  real_T _Value_f;                     /* Expression: 0
                                        * '<S136>/0'
                                        */
  real_T S12_Gain_i;                   /* Expression: -1
                                        * '<S136>/S12'
                                        */
  real_T _Value_o;                     /* Expression: 0
                                        * '<S137>/0'
                                        */
  real_T S12_Gain_f;                   /* Expression: -1
                                        * '<S137>/S12'
                                        */
  real_T SITPWM0BT_P1;                 /* Expression: width
                                        * '<S176>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S176>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S176>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S176>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S176>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S176>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S176>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S176>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S176>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S176>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S176>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S176>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S176>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_ahu;           /* Expression: 0
                                        * '<S176>/Constant'
                                        */
  real_T Constant1_Value_j;            /* Expression: 0
                                        * '<S176>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S176>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S177>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S177>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S177>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S177>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S177>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S177>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S177>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S177>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S177>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S177>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S177>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S177>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S177>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S177>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S177>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S177>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S177>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S177>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S177>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S177>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S177>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S177>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S177>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S177>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S177>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S177>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S177>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S177>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S177>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S177>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S177>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S177>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S177>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S177>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S177>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S177>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S177>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S177>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S177>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S177>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S177>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S177>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S177>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S177>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S177>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S177>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S177>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S177>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S177>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S177>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S177>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S177>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S177>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S177>/VSPS Starboard'
                                        */
  real_T R31_Value_a;                  /* Expression: 0
                                        * '<S182>/R31'
                                        */
  real_T R32_Value_h;                  /* Expression: 0
                                        * '<S182>/R32'
                                        */
  real_T R13_Value_f;                  /* Expression: 0
                                        * '<S182>/R13'
                                        */
  real_T R23_Value_b;                  /* Expression: 0
                                        * '<S182>/R23'
                                        */
  real_T R33_Value_l;                  /* Expression: 1
                                        * '<S182>/R33'
                                        */
  uint8_T Gain1_Gain_nz;               /* Computed Parameter: Gain
                                        * '<S82>/Gain1'
                                        */
  uint8_T Gain_Gain_b;                 /* Computed Parameter: Gain
                                        * '<S84>/Gain'
                                        */
  uint8_T Gain_Gain_ea;                /* Computed Parameter: Gain
                                        * '<S85>/Gain'
                                        */
  uint8_T Gain1_Gain_f;                /* Computed Parameter: Gain
                                        * '<S85>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_Template_test {
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
extern Parameters_Template_test Template_test_P;

/* Block signals (auto storage) */
extern BlockIO_Template_test Template_test_B;

/* Continuous states (auto storage) */
extern ContinuousStates_Template_test Template_test_X;

/* Block states (auto storage) */
extern D_Work_Template_test Template_test_DWork;

/* Constant parameters (auto storage) */
extern const ConstParam_Template_test Template_test_ConstP;

/* Model entry point functions */
extern void Template_test_initialize(boolean_T firstTime);
extern void Template_test_output(int_T tid);
extern void Template_test_update(int_T tid);
extern void Template_test_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Template_test *Template_test_M;

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
 * '<Root>' : Template_test
 * '<S1>'   : Template_test/Inputs from LabVIEW
 * '<S2>'   : Template_test/Main Subsystems
 * '<S3>'   : Template_test/Outputs to LabVIEW
 * '<S4>'   : Template_test/Inputs from LabVIEW/Dynamic Positioning
 * '<S5>'   : Template_test/Inputs from LabVIEW/LOS LgV backstepping II
 * '<S6>'   : Template_test/Inputs from LabVIEW/Linear Simulator
 * '<S7>'   : Template_test/Inputs from LabVIEW/Path
 * '<S8>'   : Template_test/Inputs from LabVIEW/PlayStation3
 * '<S9>'   : Template_test/Inputs from LabVIEW/Dynamic Positioning/K_d
 * '<S10>'  : Template_test/Inputs from LabVIEW/Dynamic Positioning/K_i
 * '<S11>'  : Template_test/Inputs from LabVIEW/Dynamic Positioning/K_p
 * '<S12>'  : Template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint
 * '<S13>'  : Template_test/Inputs from LabVIEW/Dynamic Positioning/Setpoint/Degrees to Radians
 * '<S14>'  : Template_test/Inputs from LabVIEW/LOS LgV backstepping II/Gamma_q
 * '<S15>'  : Template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_d
 * '<S16>'  : Template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_i
 * '<S17>'  : Template_test/Inputs from LabVIEW/LOS LgV backstepping II/K_p
 * '<S18>'  : Template_test/Inputs from LabVIEW/Path/Ellipse
 * '<S19>'  : Template_test/Inputs from LabVIEW/Path/Linear
 * '<S20>'  : Template_test/Main Subsystems/C//S Enterprise 1 Matrices
 * '<S21>'  : Template_test/Main Subsystems/Control
 * '<S22>'  : Template_test/Main Subsystems/Data logging
 * '<S23>'  : Template_test/Main Subsystems/Guidance
 * '<S24>'  : Template_test/Main Subsystems/Naviagation
 * '<S25>'  : Template_test/Main Subsystems/Plant
 * '<S26>'  : Template_test/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix
 * '<S27>'  : Template_test/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix
 * '<S28>'  : Template_test/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix
 * '<S29>'  : Template_test/Main Subsystems/Control/Control Switch
 * '<S30>'  : Template_test/Main Subsystems/Control/DP control
 * '<S31>'  : Template_test/Main Subsystems/Control/LgV2
 * '<S32>'  : Template_test/Main Subsystems/Control/PS3 u input control
 * '<S33>'  : Template_test/Main Subsystems/Control/Thruster allocation
 * '<S34>'  : Template_test/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1
 * '<S35>'  : Template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]
 * '<S36>'  : Template_test/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1
 * '<S37>'  : Template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q
 * '<S38>'  : Template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s
 * '<S39>'  : Template_test/Main Subsystems/Control/LgV2/Control law
 * '<S40>'  : Template_test/Main Subsystems/Control/LgV2/R(psi)
 * '<S41>'  : Template_test/Main Subsystems/Control/LgV2/R^T
 * '<S42>'  : Template_test/Main Subsystems/Control/LgV2/Update laws
 * '<S43>'  : Template_test/Main Subsystems/Control/LgV2/V_1^q
 * '<S44>'  : Template_test/Main Subsystems/Control/LgV2/alpha
 * '<S45>'  : Template_test/Main Subsystems/Control/LgV2/alpha^q
 * '<S46>'  : Template_test/Main Subsystems/Control/LgV2/alpha^s
 * '<S47>'  : Template_test/Main Subsystems/Control/LgV2/sigma
 * '<S48>'  : Template_test/Main Subsystems/Control/LgV2/z_1
 * '<S49>'  : Template_test/Main Subsystems/Control/LgV2/z_2
 * '<S50>'  : Template_test/Main Subsystems/Control/LgV2/zeta
 * '<S51>'  : Template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q eq
 * '<S52>'  : Template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq
 * '<S53>'  : Template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq
 * '<S54>'  : Template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^t eq
 * '<S55>'  : Template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/f_q^T
 * '<S56>'  : Template_test/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T
 * '<S57>'  : Template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq
 * '<S58>'  : Template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq
 * '<S59>'  : Template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq
 * '<S60>'  : Template_test/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq
 * '<S61>'  : Template_test/Main Subsystems/Control/LgV2/Update laws/Transpose
 * '<S62>'  : Template_test/Main Subsystems/Control/LgV2/V_1^q/Transpose
 * '<S63>'  : Template_test/Main Subsystems/Control/LgV2/alpha/I
 * '<S64>'  : Template_test/Main Subsystems/Control/LgV2/alpha^q/I
 * '<S65>'  : Template_test/Main Subsystems/Control/LgV2/alpha^s/I
 * '<S66>'  : Template_test/Main Subsystems/Control/LgV2/sigma/I
 * '<S67>'  : Template_test/Main Subsystems/Control/LgV2/sigma/S^T
 * '<S68>'  : Template_test/Main Subsystems/Control/LgV2/sigma/S^T/S(r)
 * '<S69>'  : Template_test/Main Subsystems/Control/LgV2/sigma/S^T/S^T
 * '<S70>'  : Template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi
 * '<S71>'  : Template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1
 * '<S72>'  : Template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]
 * '<S73>'  : Template_test/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]
 * '<S74>'  : Template_test/Main Subsystems/Control/PS3 u input control/Subsystem
 * '<S75>'  : Template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau
 * '<S76>'  : Template_test/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act
 * '<S77>'  : Template_test/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e
 * '<S78>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040
 * '<S79>'  : Template_test/Main Subsystems/Control/Thruster allocation/tau to f_act
 * '<S80>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act
 * '<S81>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3
 * '<S82>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3
 * '<S83>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3
 * '<S84>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3
 * '<S85>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4
 * '<S86>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391
 * '<S87>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731
 * '<S88>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391
 * '<S89>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731
 * '<S90>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451
 * '<S91>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451
 * '<S92>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0
 * '<S93>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0
 * '<S94>'  : Template_test/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0
 * '<S95>'  : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following
 * '<S96>'  : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading
 * '<S97>'  : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight
 * '<S98>'  : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path
 * '<S99>'  : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment
 * '<S100>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq
 * '<S101>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq
 * '<S102>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq
 * '<S103>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]
 * '<S104>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot
 * '<S105>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot
 * '<S106>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot
 * '<S107>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading
 * '<S108>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals
 * '<S109>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel
 * '<S110>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq
 * '<S111>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq
 * '<S112>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq
 * '<S113>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq
 * '<S114>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq
 * '<S115>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq
 * '<S116>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq
 * '<S117>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq
 * '<S118>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq
 * '<S119>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq
 * '<S120>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq
 * '<S121>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose
 * '<S122>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose
 * '<S123>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1
 * '<S124>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2
 * '<S125>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq
 * '<S126>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq
 * '<S127>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq
 * '<S128>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq
 * '<S129>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq
 * '<S130>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq
 * '<S131>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]
 * '<S132>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1
 * '<S133>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2
 * '<S134>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2
 * '<S135>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T
 * '<S136>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2
 * '<S137>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)
 * '<S138>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T
 * '<S139>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T
 * '<S140>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq
 * '<S141>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq
 * '<S142>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq
 * '<S143>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I
 * '<S144>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path
 * '<S145>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter
 * '<S146>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path
 * '<S147>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq
 * '<S148>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq
 * '<S149>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq
 * '<S150>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq
 * '<S151>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq
 * '<S152>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T
 * '<S153>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter
 * '<S154>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor
 * '<S155>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor
 * '<S156>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor
 * '<S157>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor
 * '<S158>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1
 * '<S159>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x
 * '<S160>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y
 * '<S161>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq
 * '<S162>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq
 * '<S163>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq
 * '<S164>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T
 * '<S165>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq
 * '<S166>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq
 * '<S167>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq
 * '<S168>' : Template_test/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T
 * '<S169>' : Template_test/Main Subsystems/Naviagation/Input from SIT
 * '<S170>' : Template_test/Main Subsystems/Naviagation/Navigation Switch
 * '<S171>' : Template_test/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix
 * '<S172>' : Template_test/Main Subsystems/Plant/CSE1 actuator
 * '<S173>' : Template_test/Main Subsystems/Plant/Linear Simulator
 * '<S174>' : Template_test/Main Subsystems/Plant/Thruster setting workaround
 * '<S175>' : Template_test/Main Subsystems/Plant/saturation
 * '<S176>' : Template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster
 * '<S177>' : Template_test/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller
 * '<S178>' : Template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic
 * '<S179>' : Template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1
 * '<S180>' : Template_test/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2
 * '<S181>' : Template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics
 * '<S182>' : Template_test/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)
 * '<S183>' : Template_test/Outputs to LabVIEW/Battery Voltage
 * '<S184>' : Template_test/Outputs to LabVIEW/Naviagtion
 * '<S185>' : Template_test/Outputs to LabVIEW/Plant
 * '<S186>' : Template_test/Outputs to LabVIEW/Visualization
 */
#endif                                 /* RTW_HEADER_Template_test_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_Template_test
#ifdef RVE
#ifdef MULTITASKING

Parameters_Template_test rtParameter[NUMST+!TID01EQ];

#define Template_test_P                (*param_lookup[tid][READSIDE])

Parameters_Template_test *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_Template_test rtParameter[2];

#define Template_test_P                rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
