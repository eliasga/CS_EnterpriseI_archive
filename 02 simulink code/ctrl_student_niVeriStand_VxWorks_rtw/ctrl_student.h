/*
 * ctrl_student.h
 *
 * Code generation for model "ctrl_student".
 *
 * Model version              : 1.57
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Dec 16 15:39:05 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_ctrl_student_h_
#define RTW_HEADER_ctrl_student_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef ctrl_student_COMMON_INCLUDES_
# define ctrl_student_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* ctrl_student_COMMON_INCLUDES_ */

#include "ctrl_student_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_zcfcn.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"

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
# define rtmGetRootDWork(rtm)          ((rtm)->ModelData.dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->ModelData.dwork = (val))
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
# define rtmGetDWork(rtm, idx)         ((rtm)->ModelData.dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->ModelData.dwork[idx] = (val))
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

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
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
#define ctrl_student_rtModel           RT_MODEL_ctrl_student_T

/* Block signals (auto storage) */
typedef struct {
  real_T x_m;                          /* '<S5>/x_m' */
  real_T y_m;                          /* '<S5>/y_m' */
  real_T psi_m;                        /* '<S5>/psi_m' */
  real_T Delay[3];                     /* '<S1>/Delay' */
  real_T Memory3[3];                   /* '<S1>/Memory3' */
  real_T Memory2[3];                   /* '<S1>/Memory2' */
  real_T Memory1[3];                   /* '<S1>/Memory1' */
  real_T reset;                        /* '<S2>/reset' */
  real_T Integrator2[3];               /* '<S2>/Integrator2' */
  real_T Integrator[3];                /* '<S2>/Integrator' */
  real_T Sum;                          /* '<S23>/Sum' */
  real_T K_4psi;                       /* '<S16>/K_4,psi' */
  real_T K_4x;                         /* '<S16>/K_4,x' */
  real_T K_4y;                         /* '<S16>/K_4,y' */
  real_T Integrator1[3];               /* '<S2>/Integrator1' */
  real_T M1[3];                        /* '<S2>/M^-1' */
  real_T K_2x;                         /* '<S14>/K_2,x' */
  real_T K_2y;                         /* '<S14>/K_2,y' */
  real_T K_2psi;                       /* '<S14>/K_2,psi' */
  real_T K_3psi;                       /* '<S15>/K_3,psi' */
  real_T K_3x;                         /* '<S15>/K_3,x' */
  real_T K_3y;                         /* '<S15>/K_3,y' */
  real_T Product1[3];                  /* '<S2>/Product1' */
  real_T Sum1[3];                      /* '<S2>/Sum1' */
  real_T u_BT;                         /* '<Root>/Thrust allocation' */
  real_T u_VSP;                        /* '<Root>/Thrust allocation' */
  real_T alpha_VSP;                    /* '<Root>/Thrust allocation' */
  real_T omega_VSP;                    /* '<Root>/Thrust allocation' */
  real_T F_x;                          /* '<S30>/VSP' */
  real_T F_y;                          /* '<S30>/VSP' */
  real_T nu[3];                        /* '<S1>/Rotation matrix' */
  real_T eta_dot_filtered[3];          /* '<S1>/Low pass filter 2' */
  real_T eta_filtered[3];              /* '<S1>/Low pass filter' */
  real_T nu_dot[3];                    /* '<S1>/Differentiate and filter1' */
  boolean_T fault;                     /* '<Root>/control limit checking' */
} B_ctrl_student_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE[3];              /* '<S1>/Delay' */
  real_T controlinputuexceedsbounds_DWOR;/* '<Root>/control input u exceeds bounds' */
  real_T alpha_VSP2_DWORK1;            /* '<S6>/alpha_VSP2' */
  real_T omega_VSP1_DWORK1;            /* '<S6>/omega_VSP1' */
  real_T omega_VSP2_DWORK1;            /* '<S6>/omega_VSP2' */
  real_T alpha_VSP1_DWORK1;            /* '<S6>/alpha_VSP1' */
  real_T u_BT_DWORK1;                  /* '<S6>/u_BT' */
  real_T u_VSP1_DWORK1;                /* '<S6>/u_VSP1' */
  real_T u_VSP2_DWORK1;                /* '<S6>/u_VSP2' */
  real_T x_m_DWORK1;                   /* '<S5>/x_m' */
  real_T y_m_DWORK1;                   /* '<S5>/y_m' */
  real_T psi_m_DWORK1;                 /* '<S5>/psi_m' */
  real_T Memory3_PreviousInput[3];     /* '<S1>/Memory3' */
  real_T Memory2_PreviousInput[3];     /* '<S1>/Memory2' */
  real_T Memory1_PreviousInput[3];     /* '<S1>/Memory1' */
  real_T reset_DWORK1;                 /* '<S2>/reset' */
  real_T b_x_hat_DWORK1;               /* '<S24>/b_x_hat' */
  real_T b_y_hat_DWORK1;               /* '<S24>/b_y_hat' */
  real_T b_psi_hat_DWORK1;             /* '<S24>/b_psi_hat' */
  real_T x_hat_DWORK1;                 /* '<S25>/x_hat' */
  real_T y_hat_DWORK1;                 /* '<S25>/y_hat' */
  real_T psi_hat_DWORK1;               /* '<S25>/psi_hat' */
  real_T K_4psi_DWORK1;                /* '<S16>/K_4,psi' */
  real_T K_4x_DWORK1;                  /* '<S16>/K_4,x' */
  real_T K_4y_DWORK1;                  /* '<S16>/K_4,y' */
  real_T u_dot_hat_DWORK1;             /* '<S26>/u_dot_hat' */
  real_T v_dot_hat_DWORK1;             /* '<S26>/v_dot_hat' */
  real_T r_dot_hat_DWORK1;             /* '<S26>/r_dot_hat' */
  real_T u_hat_DWORK1;                 /* '<S27>/u_hat' */
  real_T v_hat_DWORK1;                 /* '<S27>/v_hat' */
  real_T r_hat_DWORK1;                 /* '<S27>/r_hat' */
  real_T K_2x_DWORK1;                  /* '<S14>/K_2,x' */
  real_T K_2y_DWORK1;                  /* '<S14>/K_2,y' */
  real_T K_2psi_DWORK1;                /* '<S14>/K_2,psi' */
  real_T K_3psi_DWORK1;                /* '<S15>/K_3,psi' */
  real_T K_3x_DWORK1;                  /* '<S15>/K_3,x' */
  real_T K_3y_DWORK1;                  /* '<S15>/K_3,y' */
  int32_T NIVeriStandSignalProbe_DWORK2;/* '<Root>/NIVeriStandSignalProbe' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S2>/Integrator' */

  uint8_T controlinputuexceedsbounds_DW_j[13];/* '<Root>/control input u exceeds bounds' */
  uint8_T alpha_VSP2_DWORK2[13];       /* '<S6>/alpha_VSP2' */
  uint8_T omega_VSP1_DWORK2[13];       /* '<S6>/omega_VSP1' */
  uint8_T omega_VSP2_DWORK2[13];       /* '<S6>/omega_VSP2' */
  uint8_T alpha_VSP1_DWORK2[13];       /* '<S6>/alpha_VSP1' */
  uint8_T u_BT_DWORK2[13];             /* '<S6>/u_BT' */
  uint8_T u_VSP1_DWORK2[13];           /* '<S6>/u_VSP1' */
  uint8_T u_VSP2_DWORK2[13];           /* '<S6>/u_VSP2' */
  uint8_T x_m_DWORK2[13];              /* '<S5>/x_m' */
  uint8_T y_m_DWORK2[13];              /* '<S5>/y_m' */
  uint8_T psi_m_DWORK2[13];            /* '<S5>/psi_m' */
  uint8_T icLoad;                      /* '<S1>/Delay' */
  uint8_T reset_DWORK2[13];            /* '<S2>/reset' */
  uint8_T b_x_hat_DWORK2[13];          /* '<S24>/b_x_hat' */
  uint8_T b_y_hat_DWORK2[13];          /* '<S24>/b_y_hat' */
  uint8_T b_psi_hat_DWORK2[13];        /* '<S24>/b_psi_hat' */
  uint8_T x_hat_DWORK2[13];            /* '<S25>/x_hat' */
  uint8_T y_hat_DWORK2[13];            /* '<S25>/y_hat' */
  uint8_T psi_hat_DWORK2[13];          /* '<S25>/psi_hat' */
  uint8_T K_4psi_DWORK2[13];           /* '<S16>/K_4,psi' */
  uint8_T K_4x_DWORK2[13];             /* '<S16>/K_4,x' */
  uint8_T K_4y_DWORK2[13];             /* '<S16>/K_4,y' */
  uint8_T u_dot_hat_DWORK2[13];        /* '<S26>/u_dot_hat' */
  uint8_T v_dot_hat_DWORK2[13];        /* '<S26>/v_dot_hat' */
  uint8_T r_dot_hat_DWORK2[13];        /* '<S26>/r_dot_hat' */
  uint8_T u_hat_DWORK2[13];            /* '<S27>/u_hat' */
  uint8_T v_hat_DWORK2[13];            /* '<S27>/v_hat' */
  uint8_T r_hat_DWORK2[13];            /* '<S27>/r_hat' */
  uint8_T K_2x_DWORK2[13];             /* '<S14>/K_2,x' */
  uint8_T K_2y_DWORK2[13];             /* '<S14>/K_2,y' */
  uint8_T K_2psi_DWORK2[13];           /* '<S14>/K_2,psi' */
  uint8_T K_3psi_DWORK2[13];           /* '<S15>/K_3,psi' */
  uint8_T K_3x_DWORK2[13];             /* '<S15>/K_3,x' */
  uint8_T K_3y_DWORK2[13];             /* '<S15>/K_3,y' */
  uint8_T NIVeriStandSignalProbe_DWORK1[13];/* '<Root>/NIVeriStandSignalProbe' */
  uint8_T NIVeriStandSignalProbe_DWORK3[56];/* '<Root>/NIVeriStandSignalProbe' */
} DW_ctrl_student_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator2_CSTATE[3];        /* '<S2>/Integrator2' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
} X_ctrl_student_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator2_CSTATE[3];        /* '<S2>/Integrator2' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
} XDot_ctrl_student_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator2_CSTATE[3];     /* '<S2>/Integrator2' */
  boolean_T Integrator_CSTATE[3];      /* '<S2>/Integrator' */
  boolean_T Integrator1_CSTATE[3];     /* '<S2>/Integrator1' */
} XDis_ctrl_student_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Integrator2_Reset_ZCE;    /* '<S2>/Integrator2' */
  ZCSigState Integrator_Reset_ZCE;     /* '<S2>/Integrator' */
  ZCSigState Integrator1_Reset_ZCE;    /* '<S2>/Integrator1' */
} PrevZCX_ctrl_student_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            ctrl_student_B
#define BlockIO                        B_ctrl_student_T
#define rtX                            ctrl_student_X
#define ContinuousStates               X_ctrl_student_T
#define rtXdot                         ctrl_student_XDot
#define StateDerivatives               XDot_ctrl_student_T
#define tXdis                          ctrl_student_XDis
#define StateDisabled                  XDis_ctrl_student_T
#define rtP                            ctrl_student_P
#define Parameters                     P_ctrl_student_T
#define rtDWork                        ctrl_student_DW
#define D_Work                         DW_ctrl_student_T
#define rtPrevZCSigState               ctrl_student_PrevZCX
#define PrevZCSigStates                PrevZCX_ctrl_student_T

/* Parameters (auto storage) */
struct P_ctrl_student_T_ {
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T controlinputuexceedsbounds_P1;/* Expression: width
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P2;/* Expression: dtype
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P3;/* Expression: portnum
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P4;/* Expression: stime
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P5;/* Expression: stype
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  real_T controlinputuexceedsbounds_P6;/* Expression: btype
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  real_T alpha_VSP2_P1;                /* Expression: width
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P2;                /* Expression: dtype
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P3;                /* Expression: portnum
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P4;                /* Expression: stime
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P5;                /* Expression: stype
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  real_T alpha_VSP2_P6;                /* Expression: btype
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  real_T omega_VSP1_P1;                /* Expression: width
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  real_T omega_VSP1_P2;                /* Expression: dtype
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  real_T omega_VSP1_P3;                /* Expression: portnum
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  real_T omega_VSP1_P4;                /* Expression: stime
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  real_T omega_VSP1_P5;                /* Expression: stype
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  real_T omega_VSP1_P6;                /* Expression: btype
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  real_T omega_VSP2_P1;                /* Expression: width
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  real_T omega_VSP2_P2;                /* Expression: dtype
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  real_T omega_VSP2_P3;                /* Expression: portnum
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  real_T omega_VSP2_P4;                /* Expression: stime
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  real_T omega_VSP2_P5;                /* Expression: stype
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  real_T omega_VSP2_P6;                /* Expression: btype
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  real_T alpha_VSP1_P1;                /* Expression: width
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P2;                /* Expression: dtype
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P3;                /* Expression: portnum
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P4;                /* Expression: stime
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P5;                /* Expression: stype
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  real_T alpha_VSP1_P6;                /* Expression: btype
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  real_T u_BT_P1;                      /* Expression: width
                                        * Referenced by: '<S6>/u_BT'
                                        */
  real_T u_BT_P2;                      /* Expression: dtype
                                        * Referenced by: '<S6>/u_BT'
                                        */
  real_T u_BT_P3;                      /* Expression: portnum
                                        * Referenced by: '<S6>/u_BT'
                                        */
  real_T u_BT_P4;                      /* Expression: stime
                                        * Referenced by: '<S6>/u_BT'
                                        */
  real_T u_BT_P5;                      /* Expression: stype
                                        * Referenced by: '<S6>/u_BT'
                                        */
  real_T u_BT_P6;                      /* Expression: btype
                                        * Referenced by: '<S6>/u_BT'
                                        */
  real_T u_VSP1_P1;                    /* Expression: width
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  real_T u_VSP1_P2;                    /* Expression: dtype
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  real_T u_VSP1_P3;                    /* Expression: portnum
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  real_T u_VSP1_P4;                    /* Expression: stime
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  real_T u_VSP1_P5;                    /* Expression: stype
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  real_T u_VSP1_P6;                    /* Expression: btype
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  real_T u_VSP2_P1;                    /* Expression: width
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  real_T u_VSP2_P2;                    /* Expression: dtype
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  real_T u_VSP2_P3;                    /* Expression: portnum
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  real_T u_VSP2_P4;                    /* Expression: stime
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  real_T u_VSP2_P5;                    /* Expression: stype
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  real_T u_VSP2_P6;                    /* Expression: btype
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  real_T x_m_P1;                       /* Expression: width
                                        * Referenced by: '<S5>/x_m'
                                        */
  real_T x_m_P2;                       /* Expression: dtype
                                        * Referenced by: '<S5>/x_m'
                                        */
  real_T x_m_P3;                       /* Expression: portnum
                                        * Referenced by: '<S5>/x_m'
                                        */
  real_T x_m_P4;                       /* Expression: stime
                                        * Referenced by: '<S5>/x_m'
                                        */
  real_T x_m_P5;                       /* Expression: stype
                                        * Referenced by: '<S5>/x_m'
                                        */
  real_T x_m_P6;                       /* Expression: btype
                                        * Referenced by: '<S5>/x_m'
                                        */
  real_T y_m_P1;                       /* Expression: width
                                        * Referenced by: '<S5>/y_m'
                                        */
  real_T y_m_P2;                       /* Expression: dtype
                                        * Referenced by: '<S5>/y_m'
                                        */
  real_T y_m_P3;                       /* Expression: portnum
                                        * Referenced by: '<S5>/y_m'
                                        */
  real_T y_m_P4;                       /* Expression: stime
                                        * Referenced by: '<S5>/y_m'
                                        */
  real_T y_m_P5;                       /* Expression: stype
                                        * Referenced by: '<S5>/y_m'
                                        */
  real_T y_m_P6;                       /* Expression: btype
                                        * Referenced by: '<S5>/y_m'
                                        */
  real_T psi_m_P1;                     /* Expression: width
                                        * Referenced by: '<S5>/psi_m'
                                        */
  real_T psi_m_P2;                     /* Expression: dtype
                                        * Referenced by: '<S5>/psi_m'
                                        */
  real_T psi_m_P3;                     /* Expression: portnum
                                        * Referenced by: '<S5>/psi_m'
                                        */
  real_T psi_m_P4;                     /* Expression: stime
                                        * Referenced by: '<S5>/psi_m'
                                        */
  real_T psi_m_P5;                     /* Expression: stype
                                        * Referenced by: '<S5>/psi_m'
                                        */
  real_T psi_m_P6;                     /* Expression: btype
                                        * Referenced by: '<S5>/psi_m'
                                        */
  real_T LowpassGain2_Value;           /* Expression: 0.05
                                        * Referenced by: '<S1>/Low pass Gain 2'
                                        */
  real_T sampletime_Value;             /* Expression: 0.01
                                        * Referenced by: '<S1>/sample time'
                                        */
  real_T LowpassGain1_Value;           /* Expression: 0.05
                                        * Referenced by: '<S1>/Low pass Gain 1'
                                        */
  real_T Memory3_X0[3];                /* Expression: [0 0 0]
                                        * Referenced by: '<S1>/Memory3'
                                        */
  real_T Memory2_X0[3];                /* Expression: [0 0 0]
                                        * Referenced by: '<S1>/Memory2'
                                        */
  real_T Memory1_X0[3];                /* Expression: [0 0 0]
                                        * Referenced by: '<S1>/Memory1'
                                        */
  real_T reset_P1;                     /* Expression: width
                                        * Referenced by: '<S2>/reset'
                                        */
  real_T reset_P2;                     /* Expression: dtype
                                        * Referenced by: '<S2>/reset'
                                        */
  real_T reset_P3;                     /* Expression: portnum
                                        * Referenced by: '<S2>/reset'
                                        */
  real_T reset_P4;                     /* Expression: stime
                                        * Referenced by: '<S2>/reset'
                                        */
  real_T reset_P5;                     /* Expression: stype
                                        * Referenced by: '<S2>/reset'
                                        */
  real_T reset_P6;                     /* Expression: btype
                                        * Referenced by: '<S2>/reset'
                                        */
  real_T Integrator2_IC[3];            /* Expression: [0 0 0]'
                                        * Referenced by: '<S2>/Integrator2'
                                        */
  real_T b_x_hat_P1;                   /* Expression: width
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  real_T b_x_hat_P2;                   /* Expression: dtype
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  real_T b_x_hat_P3;                   /* Expression: portnum
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  real_T b_x_hat_P4;                   /* Expression: stime
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  real_T b_x_hat_P5;                   /* Expression: stype
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  real_T b_x_hat_P6;                   /* Expression: btype
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  real_T b_y_hat_P1;                   /* Expression: width
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  real_T b_y_hat_P2;                   /* Expression: dtype
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  real_T b_y_hat_P3;                   /* Expression: portnum
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  real_T b_y_hat_P4;                   /* Expression: stime
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  real_T b_y_hat_P5;                   /* Expression: stype
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  real_T b_y_hat_P6;                   /* Expression: btype
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  real_T b_psi_hat_P1;                 /* Expression: width
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  real_T b_psi_hat_P2;                 /* Expression: dtype
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  real_T b_psi_hat_P3;                 /* Expression: portnum
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  real_T b_psi_hat_P4;                 /* Expression: stime
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  real_T b_psi_hat_P5;                 /* Expression: stype
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  real_T b_psi_hat_P6;                 /* Expression: btype
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  real_T x_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S25>/x_hat'
                                        */
  real_T x_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S25>/x_hat'
                                        */
  real_T x_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S25>/x_hat'
                                        */
  real_T x_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S25>/x_hat'
                                        */
  real_T x_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S25>/x_hat'
                                        */
  real_T x_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S25>/x_hat'
                                        */
  real_T y_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S25>/y_hat'
                                        */
  real_T y_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S25>/y_hat'
                                        */
  real_T y_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S25>/y_hat'
                                        */
  real_T y_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S25>/y_hat'
                                        */
  real_T y_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S25>/y_hat'
                                        */
  real_T y_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S25>/y_hat'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1e10
                                        * Referenced by: '<S23>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1e10
                                        * Referenced by: '<S23>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: pi
                                        * Referenced by: '<S23>/Gain'
                                        */
  real_T Constant_Value_c;             /* Expression: 2*pi
                                        * Referenced by: '<S23>/Constant'
                                        */
  real_T psi_hat_P1;                   /* Expression: width
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  real_T psi_hat_P2;                   /* Expression: dtype
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  real_T psi_hat_P3;                   /* Expression: portnum
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  real_T psi_hat_P4;                   /* Expression: stime
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  real_T psi_hat_P5;                   /* Expression: stype
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  real_T psi_hat_P6;                   /* Expression: btype
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  real_T K_4psi_P1;                    /* Expression: width
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  real_T K_4psi_P2;                    /* Expression: dtype
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  real_T K_4psi_P3;                    /* Expression: portnum
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  real_T K_4psi_P4;                    /* Expression: stime
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  real_T K_4psi_P5;                    /* Expression: stype
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  real_T K_4psi_P6;                    /* Expression: btype
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  real_T K_4x_P1;                      /* Expression: width
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  real_T K_4x_P2;                      /* Expression: dtype
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  real_T K_4x_P3;                      /* Expression: portnum
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  real_T K_4x_P4;                      /* Expression: stime
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  real_T K_4x_P5;                      /* Expression: stype
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  real_T K_4x_P6;                      /* Expression: btype
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  real_T K_4y_P1;                      /* Expression: width
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  real_T K_4y_P2;                      /* Expression: dtype
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  real_T K_4y_P3;                      /* Expression: portnum
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  real_T K_4y_P4;                      /* Expression: stime
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  real_T K_4y_P5;                      /* Expression: stype
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  real_T K_4y_P6;                      /* Expression: btype
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  real_T Integrator1_IC[3];            /* Expression: [0 0 0]'
                                        * Referenced by: '<S2>/Integrator1'
                                        */
  real_T M1_Gain[9];                   /* Expression: M^-1
                                        * Referenced by: '<S2>/M^-1'
                                        */
  real_T u_dot_hat_P1;                 /* Expression: width
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  real_T u_dot_hat_P2;                 /* Expression: dtype
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  real_T u_dot_hat_P3;                 /* Expression: portnum
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  real_T u_dot_hat_P4;                 /* Expression: stime
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  real_T u_dot_hat_P5;                 /* Expression: stype
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  real_T u_dot_hat_P6;                 /* Expression: btype
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  real_T v_dot_hat_P1;                 /* Expression: width
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  real_T v_dot_hat_P2;                 /* Expression: dtype
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  real_T v_dot_hat_P3;                 /* Expression: portnum
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  real_T v_dot_hat_P4;                 /* Expression: stime
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  real_T v_dot_hat_P5;                 /* Expression: stype
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  real_T v_dot_hat_P6;                 /* Expression: btype
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  real_T r_dot_hat_P1;                 /* Expression: width
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  real_T r_dot_hat_P2;                 /* Expression: dtype
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  real_T r_dot_hat_P3;                 /* Expression: portnum
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  real_T r_dot_hat_P4;                 /* Expression: stime
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  real_T r_dot_hat_P5;                 /* Expression: stype
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  real_T r_dot_hat_P6;                 /* Expression: btype
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  real_T u_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S27>/u_hat'
                                        */
  real_T u_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S27>/u_hat'
                                        */
  real_T u_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S27>/u_hat'
                                        */
  real_T u_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S27>/u_hat'
                                        */
  real_T u_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S27>/u_hat'
                                        */
  real_T u_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S27>/u_hat'
                                        */
  real_T v_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S27>/v_hat'
                                        */
  real_T v_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S27>/v_hat'
                                        */
  real_T v_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S27>/v_hat'
                                        */
  real_T v_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S27>/v_hat'
                                        */
  real_T v_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S27>/v_hat'
                                        */
  real_T v_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S27>/v_hat'
                                        */
  real_T r_hat_P1;                     /* Expression: width
                                        * Referenced by: '<S27>/r_hat'
                                        */
  real_T r_hat_P2;                     /* Expression: dtype
                                        * Referenced by: '<S27>/r_hat'
                                        */
  real_T r_hat_P3;                     /* Expression: portnum
                                        * Referenced by: '<S27>/r_hat'
                                        */
  real_T r_hat_P4;                     /* Expression: stime
                                        * Referenced by: '<S27>/r_hat'
                                        */
  real_T r_hat_P5;                     /* Expression: stype
                                        * Referenced by: '<S27>/r_hat'
                                        */
  real_T r_hat_P6;                     /* Expression: btype
                                        * Referenced by: '<S27>/r_hat'
                                        */
  real_T K_2x_P1;                      /* Expression: width
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  real_T K_2x_P2;                      /* Expression: dtype
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  real_T K_2x_P3;                      /* Expression: portnum
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  real_T K_2x_P4;                      /* Expression: stime
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  real_T K_2x_P5;                      /* Expression: stype
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  real_T K_2x_P6;                      /* Expression: btype
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  real_T K_2y_P1;                      /* Expression: width
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  real_T K_2y_P2;                      /* Expression: dtype
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  real_T K_2y_P3;                      /* Expression: portnum
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  real_T K_2y_P4;                      /* Expression: stime
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  real_T K_2y_P5;                      /* Expression: stype
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  real_T K_2y_P6;                      /* Expression: btype
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  real_T K_2psi_P1;                    /* Expression: width
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  real_T K_2psi_P2;                    /* Expression: dtype
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  real_T K_2psi_P3;                    /* Expression: portnum
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  real_T K_2psi_P4;                    /* Expression: stime
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  real_T K_2psi_P5;                    /* Expression: stype
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  real_T K_2psi_P6;                    /* Expression: btype
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  real_T K_3psi_P1;                    /* Expression: width
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  real_T K_3psi_P2;                    /* Expression: dtype
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  real_T K_3psi_P3;                    /* Expression: portnum
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  real_T K_3psi_P4;                    /* Expression: stime
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  real_T K_3psi_P5;                    /* Expression: stype
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  real_T K_3psi_P6;                    /* Expression: btype
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  real_T K_3x_P1;                      /* Expression: width
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  real_T K_3x_P2;                      /* Expression: dtype
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  real_T K_3x_P3;                      /* Expression: portnum
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  real_T K_3x_P4;                      /* Expression: stime
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  real_T K_3x_P5;                      /* Expression: stype
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  real_T K_3x_P6;                      /* Expression: btype
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  real_T K_3y_P1;                      /* Expression: width
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  real_T K_3y_P2;                      /* Expression: dtype
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  real_T K_3y_P3;                      /* Expression: portnum
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  real_T K_3y_P4;                      /* Expression: stime
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  real_T K_3y_P5;                      /* Expression: stype
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  real_T K_3y_P6;                      /* Expression: btype
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  real_T Constant_Value_g;             /* Expression: 50
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 50
                                        * Referenced by: '<S2>/Constant1'
                                        */
  real_T Constant2_Value;              /* Expression: 50
                                        * Referenced by: '<S2>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/Constant3'
                                        */
  real_T Constant4_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/Constant4'
                                        */
  real_T Constant5_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/Constant5'
                                        */
  real_T Constant6_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/Constant6'
                                        */
  real_T Constant7_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/Constant7'
                                        */
  real_T Constant8_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/Constant8'
                                        */
  real_T NIVeriStandSignalProbe_P1;    /* Expression: 1
                                        * Referenced by: '<Root>/NIVeriStandSignalProbe'
                                        */
  uint32_T Delay_DelayLength;          /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S1>/Delay'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ctrl_student_T {
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
    void *defaultParam;
    ZCSigState *prevZCSigState;
    real_T *contStates;
    real_T *derivs;
    void *zcSignalValues;
    void *inputs;
    void *outputs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[9];
    real_T odeF[4][9];
    ODE4_IntgData intgData;
    void *dwork;
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
};

/* Block parameters (auto storage) */
extern P_ctrl_student_T ctrl_student_P;

/* Block signals (auto storage) */
extern B_ctrl_student_T ctrl_student_B;

/* Continuous states (auto storage) */
extern X_ctrl_student_T ctrl_student_X;

/* Block states (auto storage) */
extern DW_ctrl_student_T ctrl_student_DW;

/* Model entry point functions */
extern void ctrl_student_initialize(void);
extern void ctrl_student_output(void);
extern void ctrl_student_update(void);
extern void ctrl_student_terminate(void);

/* Real-time Model object */
extern RT_MODEL_ctrl_student_T *const ctrl_student_M;

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
 * '<Root>' : 'ctrl_student'
 * '<S1>'   : 'ctrl_student/Derivative filter'
 * '<S2>'   : 'ctrl_student/Observer'
 * '<S3>'   : 'ctrl_student/Thrust allocation'
 * '<S4>'   : 'ctrl_student/control limit checking'
 * '<S5>'   : 'ctrl_student/pose measured'
 * '<S6>'   : 'ctrl_student/u'
 * '<S7>'   : 'ctrl_student/Derivative filter/Differentiate and filter1'
 * '<S8>'   : 'ctrl_student/Derivative filter/Discrete derivative'
 * '<S9>'   : 'ctrl_student/Derivative filter/Low pass filter'
 * '<S10>'  : 'ctrl_student/Derivative filter/Low pass filter 2'
 * '<S11>'  : 'ctrl_student/Derivative filter/Rotation matrix'
 * '<S12>'  : 'ctrl_student/Observer/C(nu)*nu'
 * '<S13>'  : 'ctrl_student/Observer/D(nu)*nu'
 * '<S14>'  : 'ctrl_student/Observer/K_2'
 * '<S15>'  : 'ctrl_student/Observer/K_3'
 * '<S16>'  : 'ctrl_student/Observer/K_4'
 * '<S17>'  : 'ctrl_student/Observer/MATLAB Function'
 * '<S18>'  : 'ctrl_student/Observer/MATLAB Function1'
 * '<S19>'  : 'ctrl_student/Observer/MATLAB Function2'
 * '<S20>'  : 'ctrl_student/Observer/Rotation matrix in yaw 1'
 * '<S21>'  : 'ctrl_student/Observer/Transpose Rotation Matrix'
 * '<S22>'  : 'ctrl_student/Observer/Transpose Rotation matrix'
 * '<S23>'  : 'ctrl_student/Observer/[-inf inf] to [-pi pi]'
 * '<S24>'  : 'ctrl_student/Observer/b_hat'
 * '<S25>'  : 'ctrl_student/Observer/eta_hat'
 * '<S26>'  : 'ctrl_student/Observer/nu_dot_hat'
 * '<S27>'  : 'ctrl_student/Observer/nu_hat'
 * '<S28>'  : 'ctrl_student/Observer/u_2_tau'
 * '<S29>'  : 'ctrl_student/Observer/u_2_tau/Thruster configuration matrix'
 * '<S30>'  : 'ctrl_student/Observer/u_2_tau/Thruster mapping'
 * '<S31>'  : 'ctrl_student/Observer/u_2_tau/Thruster mapping/Bow thruster'
 * '<S32>'  : 'ctrl_student/Observer/u_2_tau/Thruster mapping/VSP'
 */
#endif                                 /* RTW_HEADER_ctrl_student_h_ */

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_ctrl_student
#ifndef NI_VERISTAND_MODELDATAFILE
#ifdef NI_VERISTAND_MAINMODELFILE

int READSIDE = 0;
int tid = 0;

#ifdef MULTITASKING

P_ctrl_student_T rtParameter[NUMST+!TID01EQ];
P_ctrl_student_T *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },

  { &rtParameter[0], &rtParameter[1] },
};

#else

P_ctrl_student_T rtParameter[2];

#endif

#else

extern int READSIDE;

#ifdef MULTITASKING

extern int tid;
extern P_ctrl_student_T* param_lookup[NUMST][2];

#else

extern P_ctrl_student_T rtParameter[];

#endif
#endif

#ifdef MULTITASKING
#define ctrl_student_P                 (*param_lookup[tid][READSIDE])
#else
#define ctrl_student_P                 rtParameter[READSIDE]
#endif
#endif
#endif
