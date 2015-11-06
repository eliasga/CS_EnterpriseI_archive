/*
 * PS3.h
 *
 * Real-Time Workshop code generation for Simulink model "PS3.mdl".
 *
 * Model Version              : 1.6
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 16:16:32 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_PS3_h_
#define RTW_HEADER_PS3_h_
#ifndef PS3_COMMON_INCLUDES_
# define PS3_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#include "dspsvd_rt.h"
#include "rt_nonfinite.h"
#include "rt_SATURATE.h"
#include "rt_SIGNd_snf.h"
#include "rt_look.h"
#include "rt_look2d_normal.h"
#include "rt_MAX.h"
#include "rt_MIN.h"
#endif                                 /* PS3_COMMON_INCLUDES_ */

#include "PS3_types.h"

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
# define rtmGetFirstInitCondFlag(rtm)  ()
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ()
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ()
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
# define rtmGetOdeF(rtm)               ()
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ()
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ()
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ()
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
# define rtmIsContinuousTask(rtm, tid) 0
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
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
#define PS3_rtModel                    RT_MODEL_PS3

/* Block signals (auto storage) */
typedef struct {
  real_T ypositionofleftanalogstick11; /* '<S4>/ScalingLY' */
  real_T u_1;                          /* '<S6>/PS3 u_1' */
  real_T xpositionofleftanalogstick11; /* '<S4>/ScalingLX' */
  real_T u_2;                          /* '<S6>/PS3 u_2' */
  real_T ypositionofrightanalogstick11;/* '<S4>/ScalingRY' */
  real_T u_3;                          /* '<S6>/PS3 u_3' */
  real_T xpositionofrightanalogstick11;/* '<S4>/Scaling_RX' */
  real_T u_4;                          /* '<S6>/PS3 u_4' */
  real_T BowThrusterdirection;         /* '<S6>/Add' */
  real_T u_5;                          /* '<S6>/PS3 u_5' */
  real_T l_x1;                         /* '<S30>/-l_x1' */
  real_T l_y2;                         /* '<S30>/-l_y2' */
  real_T l_x2;                         /* '<S30>/-l_x2' */
  real_T x5[15];                       /* '<S30>/3x5' */
  real_T Pseudoinverse[15];            /* '<S9>/Pseudoinverse' */
  real_T Sum1;                         /* '<S5>/Sum1' */
  real_T tau_surge;                    /* '<S5>/tau_surge' */
  real_T Sum2;                         /* '<S5>/Sum2' */
  real_T tau_sway;                     /* '<S5>/tau_sway' */
  real_T Sum;                          /* '<S5>/Sum' */
  real_T tau_yaw;                      /* '<S5>/tau_yaw' */
  real_T TmpHiddenBufferAtProductInport2[3];/* 'synthesized block' */
  real_T Product[5];                   /* '<S9>/Product' */
  real_T DeadZone;                     /* '<S10>/Dead Zone' */
  real_T f_10;                         /* '<S10>/f_1 < 0' */
  real_T f_10_m;                       /* '<S10>/f_1 > 0' */
  real_T MultiportSwitch;              /* '<S10>/Multiport Switch' */
  real_T DeadZone_h;                   /* '<S11>/Dead Zone' */
  real_T f_20;                         /* '<S11>/f_2 < 0' */
  real_T f_20_i;                       /* '<S11>/f_2 > 0' */
  real_T MultiportSwitch_e;            /* '<S11>/Multiport Switch' */
  real_T DeadZone_b;                   /* '<S12>/Dead Zone' */
  real_T f_30;                         /* '<S12>/f_3 < 0' */
  real_T f_30_b;                       /* '<S12>/f_3 > 0' */
  real_T MultiportSwitch_f;            /* '<S12>/Multiport Switch' */
  real_T DeadZone_f;                   /* '<S13>/Dead Zone' */
  real_T f_40;                         /* '<S13>/f_4 < 0' */
  real_T f_40_k;                       /* '<S13>/f_4 > 0' */
  real_T MultiportSwitch_h;            /* '<S13>/Multiport Switch' */
  real_T DeadZone_l;                   /* '<S14>/Dead Zone' */
  real_T f_50;                         /* '<S14>/f_5 < 0' */
  real_T f_50_c;                       /* '<S14>/f_5 > 0' */
  real_T MultiportSwitch_p;            /* '<S14>/Multiport Switch' */
  real_T Saturation[5];                /* '<S5>/Saturation' */
  real_T Joysticku_1;                  /* '<S5>/Joystick u_1' */
  real_T Joysticku_2;                  /* '<S5>/Joystick u_2' */
  real_T Joysticku_3;                  /* '<S5>/Joystick u_3' */
  real_T Joysticku_4;                  /* '<S5>/Joystick u_4' */
  real_T Joysticku_5;                  /* '<S5>/Joystick u_5' */
  real_T ThrustersettingSwitch[7];     /* '<S1>/Thruster setting Switch' */
  real_T Saturation_f[7];              /* '<S1>/Saturation' */
  real_T plantu_1;                     /* '<S3>/plant u_1' */
  real_T plantu_2;                     /* '<S3>/plant u_2' */
  real_T plantu_3;                     /* '<S3>/plant u_3' */
  real_T plantu_4;                     /* '<S3>/plant u_4' */
  real_T plantu_5;                     /* '<S3>/plant u_5' */
  real_T plantBTpower;                 /* '<S3>/plant BT power' */
  real_T plantVSPspeed;                /* '<S3>/plant VSP speed' */
  real_T SITzAI0;                      /* '<S2>/SIT zAI0' */
  real_T BatteryBowThruster;           /* '<S2>/Battery Bow Thruster' */
  real_T SITzAI1;                      /* '<S2>/SIT zAI1' */
  real_T BatteryServo;                 /* '<S2>/Battery Servo' */
  real_T SITzAI2;                      /* '<S2>/SIT zAI2' */
  real_T BatteryMain;                  /* '<S2>/Battery Main' */
  real_T BT_D_Gain1;                   /* '<S32>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S32>/BT_D_Gain2' */
  real_T Add;                          /* '<S32>/Add' */
  real_T BT_L_Gain1;                   /* '<S32>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S32>/BT_L_Gain2' */
  real_T Neg;                          /* '<S32>/Neg' */
  real_T Sum1_d;                       /* '<S32>/Sum1' */
  real_T Sum2_o;                       /* '<S32>/Sum2' */
  real_T Switch;                       /* '<S34>/Switch' */
  real_T Switch2;                      /* '<S34>/Switch2' */
  real_T Switch_e;                     /* '<S35>/Switch' */
  real_T Switch2_i;                    /* '<S35>/Switch2' */
  real_T Switch_o;                     /* '<S36>/Switch' */
  real_T Switch2_c;                    /* '<S36>/Switch2' */
  real_T Sign;                         /* '<S33>/Sign' */
  real_T PortVPS_X;                    /* '<S33>/Product1' */
  real_T PortVPS_X_o;                  /* '<S33>/-x' */
  real_T PortVSP_Y;                    /* '<S33>/Product2' */
  real_T PortVSP_Y_b;                  /* '<S33>/-y' */
  real_T StarboardVSP_X;               /* '<S33>/Product3' */
  real_T StarboardVSP_Y;               /* '<S33>/Product4' */
  real_T Servo1;                       /* '<S33>/Servo1' */
  real_T Servo2;                       /* '<S33>/Servo2' */
  real_T Servo3;                       /* '<S33>/Servo3' */
  real_T Servo4;                       /* '<S33>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S33>/VPS_Speed_Gain' */
  real_T Sum_o;                        /* '<S33>/Sum' */
  real_T VSPSPort;                     /* '<S33>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S33>/VSPS Starboard' */
  uint16_T Gain;                       /* '<S10>/Gain' */
  uint16_T Gain1;                      /* '<S10>/Gain1' */
  uint16_T Sum_ow;                     /* '<S10>/Sum' */
  uint16_T Gain_k;                     /* '<S11>/Gain' */
  uint16_T Gain1_l;                    /* '<S11>/Gain1' */
  uint16_T Sum_i;                      /* '<S11>/Sum' */
  uint16_T Gain_f;                     /* '<S12>/Gain' */
  uint16_T Gain1_i;                    /* '<S12>/Gain1' */
  uint16_T Sum_f;                      /* '<S12>/Sum' */
  uint16_T Gain_m;                     /* '<S13>/Gain' */
  uint16_T Gain1_g;                    /* '<S13>/Gain1' */
  uint16_T Sum_l;                      /* '<S13>/Sum' */
  uint16_T Gain_o;                     /* '<S14>/Gain' */
  uint16_T Gain1_p;                    /* '<S14>/Gain1' */
  uint16_T Sum_g;                      /* '<S14>/Sum' */
  uint8_T Compare;                     /* '<S15>/Compare' */
  uint8_T Compare_a;                   /* '<S17>/Compare' */
  uint8_T Compare_d;                   /* '<S16>/Compare' */
  uint8_T Compare_i;                   /* '<S18>/Compare' */
  uint8_T Compare_ab;                  /* '<S19>/Compare' */
  uint8_T Compare_h;                   /* '<S20>/Compare' */
  uint8_T Compare_dd;                  /* '<S21>/Compare' */
  uint8_T Compare_c;                   /* '<S23>/Compare' */
  uint8_T Compare_af;                  /* '<S22>/Compare' */
  uint8_T Compare_ak;                  /* '<S24>/Compare' */
  uint8_T Compare_av;                  /* '<S26>/Compare' */
  uint8_T Compare_p;                   /* '<S25>/Compare' */
  uint8_T Compare_p5;                  /* '<S27>/Compare' */
  uint8_T Compare_l;                   /* '<S29>/Compare' */
  uint8_T Compare_c4;                  /* '<S28>/Compare' */
  boolean_T LowerRelop1;               /* '<S34>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S34>/UpperRelop' */
  boolean_T LowerRelop1_c;             /* '<S35>/LowerRelop1' */
  boolean_T UpperRelop_o;              /* '<S35>/UpperRelop' */
  boolean_T LowerRelop1_g;             /* '<S36>/LowerRelop1' */
  boolean_T UpperRelop_g;              /* '<S36>/UpperRelop' */
} BlockIO_PS3;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Pseudoinverse_X[15];          /* '<S9>/Pseudoinverse' */
  real_T Pseudoinverse_E[5];           /* '<S9>/Pseudoinverse' */
  real_T Pseudoinverse_WORK[3];        /* '<S9>/Pseudoinverse' */
  real_T Pseudoinverse_S[4];           /* '<S9>/Pseudoinverse' */
  real_T Pseudoinverse_U[9];           /* '<S9>/Pseudoinverse' */
  real_T Pseudoinverse_V[25];          /* '<S9>/Pseudoinverse' */
  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<S11>/Scope2' */

  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint32_T Sum_DWORK1;                 /* '<S10>/Sum' */
  uint8_T SignalProbe_DWORK1[4];       /* '<Root>/SignalProbe' */
} D_Work_PS3;

/* Backward compatible GRT Identifiers */
#define rtB                            PS3_B
#define BlockIO                        BlockIO_PS3
#define rtXdot                         PS3_Xdot
#define StateDerivatives               StateDerivatives_PS3
#define tXdis                          PS3_Xdis
#define StateDisabled                  StateDisabled_PS3
#define rtP                            PS3_P
#define Parameters                     Parameters_PS3
#define rtDWork                        PS3_DWork
#define D_Work                         D_Work_PS3

/* Parameters (auto storage) */
struct Parameters_PS3_ {
  real_T ControlMode_Value;            /* Expression: 0
                                        * '<S1>/Control Mode'
                                        */
  real_T AS_LY_Value;                  /* Expression: 0
                                        * '<S4>/AS_LY'
                                        */
  real_T ScalingLY_Gain;               /* Expression: 1/32767
                                        * '<S4>/ScalingLY'
                                        */
  real_T PS3u_1_Gain;                  /* Expression: 1
                                        * '<S6>/PS3 u_1'
                                        */
  real_T AS_LX_Value;                  /* Expression: 0
                                        * '<S4>/AS_LX'
                                        */
  real_T ScalingLX_Gain;               /* Expression: 1/32767
                                        * '<S4>/ScalingLX'
                                        */
  real_T PS3u_2_Gain;                  /* Expression: 1
                                        * '<S6>/PS3 u_2'
                                        */
  real_T AS_RY_Value;                  /* Expression: 0
                                        * '<S4>/AS_RY'
                                        */
  real_T ScalingRY_Gain;               /* Expression: 1/32767
                                        * '<S4>/ScalingRY'
                                        */
  real_T PS3u_3_Gain;                  /* Expression: 1
                                        * '<S6>/PS3 u_3'
                                        */
  real_T AS_RX_Value;                  /* Expression: 0
                                        * '<S4>/AS_RX'
                                        */
  real_T Scaling_RX_Gain;              /* Expression: 1/32767
                                        * '<S4>/Scaling_RX'
                                        */
  real_T PS3u_4_Gain;                  /* Expression: 1
                                        * '<S6>/PS3 u_4'
                                        */
  real_T L2_Value;                     /* Expression: 0
                                        * '<S4>/L2'
                                        */
  real_T R2_Value;                     /* Expression: 0
                                        * '<S4>/R2'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S6>/PS3 u_5'
                                        */
  real_T PS3_BT_Power_Value;           /* Expression: 0
                                        * '<S4>/PS3_BT_Power'
                                        */
  real_T PS3_VSP_Speed_Value;          /* Expression: 0
                                        * '<S4>/PS3_VSP_Speed'
                                        */
  real_T T_e11_Value;                  /* Expression: 1
                                        * '<S30>/T_e11'
                                        */
  real_T T_e21_Value;                  /* Expression: 0
                                        * '<S30>/T_e21'
                                        */
  real_T l_y1_Value;                   /* Expression: 0.055
                                        * '<S30>/l_y1'
                                        */
  real_T T_e12_Value;                  /* Expression: 0
                                        * '<S30>/T_e12'
                                        */
  real_T T_e22_Value;                  /* Expression: 1
                                        * '<S30>/T_e22'
                                        */
  real_T l_x1_Value;                   /* Expression: 0.45
                                        * '<S30>/l_x1'
                                        */
  real_T l_x1_Gain;                    /* Expression: -1
                                        * '<S30>/-l_x1'
                                        */
  real_T T_e13_Value;                  /* Expression: 1
                                        * '<S30>/T_e13'
                                        */
  real_T T_e23_Value;                  /* Expression: 0
                                        * '<S30>/T_e23'
                                        */
  real_T l_y2_Value;                   /* Expression: 0.055
                                        * '<S30>/l_y2'
                                        */
  real_T l_y2_Gain;                    /* Expression: -1
                                        * '<S30>/-l_y2'
                                        */
  real_T T_e14_Value;                  /* Expression: 0
                                        * '<S30>/T_e14'
                                        */
  real_T T_e24_Value;                  /* Expression: 1
                                        * '<S30>/T_e24'
                                        */
  real_T l_x2_Value;                   /* Expression: 0.45
                                        * '<S30>/l_x2'
                                        */
  real_T l_x2_Gain;                    /* Expression: -1
                                        * '<S30>/-l_x2'
                                        */
  real_T T_e15_Value;                  /* Expression: 0
                                        * '<S30>/T_e15'
                                        */
  real_T T_e25_Value;                  /* Expression: 1
                                        * '<S30>/T_e25'
                                        */
  real_T l_x3_Value;                   /* Expression: 0.385
                                        * '<S30>/l_x3'
                                        */
  real_T tau_surge_Gain;               /* Expression: 1
                                        * '<S5>/tau_surge'
                                        */
  real_T tau_sway_Gain;                /* Expression: 1
                                        * '<S5>/tau_sway'
                                        */
  real_T tau_yaw_Gain;                 /* Expression: 1
                                        * '<S5>/tau_yaw'
                                        */
  real_T DeadZone_Start;               /* Expression: -0.001
                                        * '<S10>/Dead Zone'
                                        */
  real_T DeadZone_End;                 /* Expression: 0.001
                                        * '<S10>/Dead Zone'
                                        */
  real_T Constant_Value;               /* Expression: const
                                        * '<S15>/Constant'
                                        */
  real_T Constant_Value_h;             /* Expression: const
                                        * '<S16>/Constant'
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
                                        * '<S10>/f_1 < 0'
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
                                        * '<S10>/f_1 < 0'
                                        */
  real_T f_10_Value;                   /* Expression: 0
                                        * '<S10>/f_1 = 0'
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
                                        * '<S10>/f_1 > 0'
                                        */
  real_T f_10_YData_p[10];             /* Expression: [0.0500
                                          0.1000
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000]
                                        * '<S10>/f_1 > 0'
                                        */
  real_T DeadZone_Start_p;             /* Expression: -0.001
                                        * '<S11>/Dead Zone'
                                        */
  real_T DeadZone_End_b;               /* Expression: 0.001
                                        * '<S11>/Dead Zone'
                                        */
  real_T Constant_Value_l;             /* Expression: const
                                        * '<S18>/Constant'
                                        */
  real_T Constant_Value_n;             /* Expression: const
                                        * '<S19>/Constant'
                                        */
  real_T Constant_Value_b;             /* Expression: const
                                        * '<S20>/Constant'
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
                                        * '<S11>/f_2 < 0'
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
                                        * '<S11>/f_2 < 0'
                                        */
  real_T f_20_Value;                   /* Expression: 0
                                        * '<S11>/f_2 = 0'
                                        */
  real_T f_20_XData_n[10];             /* Expression: [0.000
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
                                        * '<S11>/f_2 > 0'
                                        */
  real_T f_20_YData_p[10];             /* Expression: [0.1665
                                          0.2000
                                          0.3000
                                          0.4000
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S11>/f_2 > 0'
                                        */
  real_T DeadZone_Start_d;             /* Expression: -0.001
                                        * '<S12>/Dead Zone'
                                        */
  real_T DeadZone_End_a;               /* Expression: 0.001
                                        * '<S12>/Dead Zone'
                                        */
  real_T Constant_Value_a;             /* Expression: const
                                        * '<S21>/Constant'
                                        */
  real_T Constant_Value_o;             /* Expression: const
                                        * '<S22>/Constant'
                                        */
  real_T f_30_XData[8];                /* Expression: [-1.291
                                          -1.088
                                          -0.885
                                          -0.618
                                          -0.403
                                          -0.211
                                          -0.034
                                          0.000]
                                        * '<S12>/f_3 < 0'
                                        */
  real_T f_30_YData[8];                /* Expression: [-0.9000
                                          -0.8000
                                          -0.7000
                                          -0.6000
                                          -0.5000
                                          -0.4000
                                          -0.3000
                                          -0.2809]
                                        * '<S12>/f_3 < 0'
                                        */
  real_T f_30_Value;                   /* Expression: 0
                                        * '<S12>/f_3 = 0'
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
                                        * '<S12>/f_3 > 0'
                                        */
  real_T f_30_YData_j[11];             /* Expression: [0.0452
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
                                        * '<S12>/f_3 > 0'
                                        */
  real_T DeadZone_Start_a;             /* Expression: -0.001
                                        * '<S13>/Dead Zone'
                                        */
  real_T DeadZone_End_p;               /* Expression: 0.001
                                        * '<S13>/Dead Zone'
                                        */
  real_T Constant_Value_bv;            /* Expression: const
                                        * '<S24>/Constant'
                                        */
  real_T Constant_Value_bb;            /* Expression: const
                                        * '<S25>/Constant'
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
                                        * '<S13>/f_4 < 0'
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
                                        * '<S13>/f_4 < 0'
                                        */
  real_T f_40_Value;                   /* Expression: 0
                                        * '<S13>/f_4 = 0'
                                        */
  real_T f_40_XData_e[7];              /* Expression: [0.000
                                          0.063
                                          0.107
                                          0.274
                                          0.441
                                          0.599
                                          0.731]
                                        * '<S13>/f_4 > 0'
                                        */
  real_T f_40_YData_l[7];              /* Expression: [0.3588
                                          0.5000
                                          0.6000
                                          0.7000
                                          0.8000
                                          0.9000
                                          1.0000]
                                        * '<S13>/f_4 > 0'
                                        */
  real_T DeadZone_Start_dk;            /* Expression: -0.001
                                        * '<S14>/Dead Zone'
                                        */
  real_T DeadZone_End_d;               /* Expression: 0.001
                                        * '<S14>/Dead Zone'
                                        */
  real_T Constant_Value_g;             /* Expression: const
                                        * '<S27>/Constant'
                                        */
  real_T Constant_Value_ny;            /* Expression: const
                                        * '<S28>/Constant'
                                        */
  real_T f_50_XData[3];                /* Expression: [-1.2630
                                          -1.0309
                                          -0.3808]
                                        * '<S14>/f_5 < 0'
                                        */
  real_T f_50_YData[3];                /* Expression: [-0.3000
                                          -0.2000
                                          -0.1000]
                                        * '<S14>/f_5 < 0'
                                        */
  real_T f_50_Value;                   /* Expression: 0
                                        * '<S14>/f_5 = 0'
                                        */
  real_T f_50_XData_p[3];              /* Expression: [0.3480
                                          0.8290
                                          1.0930]
                                        * '<S14>/f_5 > 0'
                                        */
  real_T f_50_YData_d[3];              /* Expression: [0.1000
                                          0.2000
                                          0.3000]
                                        * '<S14>/f_5 > 0'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1.0
                                        * '<S5>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1.0
                                        * '<S5>/Saturation'
                                        */
  real_T Joysticku_1_Gain;             /* Expression: 1
                                        * '<S5>/Joystick u_1'
                                        */
  real_T Joysticku_2_Gain;             /* Expression: 1
                                        * '<S5>/Joystick u_2'
                                        */
  real_T Joysticku_3_Gain;             /* Expression: 1
                                        * '<S5>/Joystick u_3'
                                        */
  real_T Joysticku_4_Gain;             /* Expression: 1
                                        * '<S5>/Joystick u_4'
                                        */
  real_T Joysticku_5_Gain;             /* Expression: 1
                                        * '<S5>/Joystick u_5'
                                        */
  real_T Saturation_UpperSat_l;        /* Expression: 1.0
                                        * '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: -1.0
                                        * '<S1>/Saturation'
                                        */
  real_T plantu_1_Gain;                /* Expression: 1
                                        * '<S3>/plant u_1'
                                        */
  real_T plantu_2_Gain;                /* Expression: 1
                                        * '<S3>/plant u_2'
                                        */
  real_T plantu_3_Gain;                /* Expression: 1
                                        * '<S3>/plant u_3'
                                        */
  real_T plantu_4_Gain;                /* Expression: 1
                                        * '<S3>/plant u_4'
                                        */
  real_T plantu_5_Gain;                /* Expression: 1
                                        * '<S3>/plant u_5'
                                        */
  real_T plantBTpower_Gain;            /* Expression: 1
                                        * '<S3>/plant BT power'
                                        */
  real_T plantVSPspeed_Gain;           /* Expression: 1
                                        * '<S3>/plant VSP speed'
                                        */
  real_T EnableCSE1_Value;             /* Expression: 0
                                        * '<S3>/Enable CSE1'
                                        */
  real_T SITzAI0_P1;                   /* Expression: width
                                        * '<S2>/SIT zAI0'
                                        */
  real_T SITzAI0_P2;                   /* Expression: dtype
                                        * '<S2>/SIT zAI0'
                                        */
  real_T SITzAI0_P3;                   /* Expression: portnum
                                        * '<S2>/SIT zAI0'
                                        */
  real_T SITzAI0_P4;                   /* Expression: stime
                                        * '<S2>/SIT zAI0'
                                        */
  real_T SITzAI0_P5;                   /* Expression: stype
                                        * '<S2>/SIT zAI0'
                                        */
  real_T SITzAI0_P6;                   /* Expression: btype
                                        * '<S2>/SIT zAI0'
                                        */
  real_T BatteryBowThruster_Gain;      /* Expression: 1
                                        * '<S2>/Battery Bow Thruster'
                                        */
  real_T SITzAI1_P1;                   /* Expression: width
                                        * '<S2>/SIT zAI1'
                                        */
  real_T SITzAI1_P2;                   /* Expression: dtype
                                        * '<S2>/SIT zAI1'
                                        */
  real_T SITzAI1_P3;                   /* Expression: portnum
                                        * '<S2>/SIT zAI1'
                                        */
  real_T SITzAI1_P4;                   /* Expression: stime
                                        * '<S2>/SIT zAI1'
                                        */
  real_T SITzAI1_P5;                   /* Expression: stype
                                        * '<S2>/SIT zAI1'
                                        */
  real_T SITzAI1_P6;                   /* Expression: btype
                                        * '<S2>/SIT zAI1'
                                        */
  real_T BatteryServo_Gain;            /* Expression: 1
                                        * '<S2>/Battery Servo'
                                        */
  real_T SITzAI2_P1;                   /* Expression: width
                                        * '<S2>/SIT zAI2'
                                        */
  real_T SITzAI2_P2;                   /* Expression: dtype
                                        * '<S2>/SIT zAI2'
                                        */
  real_T SITzAI2_P3;                   /* Expression: portnum
                                        * '<S2>/SIT zAI2'
                                        */
  real_T SITzAI2_P4;                   /* Expression: stime
                                        * '<S2>/SIT zAI2'
                                        */
  real_T SITzAI2_P5;                   /* Expression: stype
                                        * '<S2>/SIT zAI2'
                                        */
  real_T SITzAI2_P6;                   /* Expression: btype
                                        * '<S2>/SIT zAI2'
                                        */
  real_T BatteryMain_Gain;             /* Expression: 2
                                        * '<S2>/Battery Main'
                                        */
  real_T SignalProbe_P1;               /* Expression: 1
                                        * '<Root>/SignalProbe'
                                        */
  real_T SITPWM0BT_P1;                 /* Expression: width
                                        * '<S32>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S32>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S32>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S32>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S32>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S32>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S32>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S32>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S32>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S32>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S32>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S32>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S32>/BT_Power_Offset3'
                                        */
  real_T Constant_Value_al;            /* Expression: 0
                                        * '<S32>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * '<S32>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S32>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S33>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S33>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S33>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S33>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S33>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S33>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S33>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S33>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S33>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S33>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S33>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S33>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S33>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S33>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S33>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S33>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S33>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S33>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S33>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S33>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S33>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S33>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S33>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S33>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S33>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S33>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S33>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S33>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S33>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S33>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S33>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S33>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S33>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S33>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S33>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S33>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S33>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S33>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S33>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S33>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S33>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S33>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S33>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S33>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S33>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S33>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S33>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S33>/VSPS Starboard'
                                        */
  uint8_T Gain_Gain;                   /* Computed Parameter: Gain
                                        * '<S10>/Gain'
                                        */
  uint8_T Gain1_Gain;                  /* Computed Parameter: Gain
                                        * '<S10>/Gain1'
                                        */
  uint8_T Gain_Gain_h;                 /* Computed Parameter: Gain
                                        * '<S11>/Gain'
                                        */
  uint8_T Gain1_Gain_p;                /* Computed Parameter: Gain
                                        * '<S11>/Gain1'
                                        */
  uint8_T Gain_Gain_f;                 /* Computed Parameter: Gain
                                        * '<S12>/Gain'
                                        */
  uint8_T Gain1_Gain_o;                /* Computed Parameter: Gain
                                        * '<S12>/Gain1'
                                        */
  uint8_T Gain_Gain_b;                 /* Computed Parameter: Gain
                                        * '<S13>/Gain'
                                        */
  uint8_T Gain1_Gain_l;                /* Computed Parameter: Gain
                                        * '<S13>/Gain1'
                                        */
  uint8_T Gain_Gain_g;                 /* Computed Parameter: Gain
                                        * '<S14>/Gain'
                                        */
  uint8_T Gain1_Gain_k;                /* Computed Parameter: Gain
                                        * '<S14>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_PS3 {
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
    time_T sampleTimesArray[1];
    time_T offsetTimesArray[1];
    int_T sampleTimeTaskIDArray[1];
    int_T sampleHitArray[1];
    int_T perTaskSampleHitsArray[1];
    time_T tArray[1];
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
extern Parameters_PS3 PS3_P;

/* Block signals (auto storage) */
extern BlockIO_PS3 PS3_B;

/* Block states (auto storage) */
extern D_Work_PS3 PS3_DWork;

/* Real-time Model object */
extern RT_MODEL_PS3 *PS3_M;

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
 * '<Root>' : PS3
 * '<S1>'   : PS3/Control Systems
 * '<S2>'   : PS3/HMI
 * '<S3>'   : PS3/Plants
 * '<S4>'   : PS3/Control Systems/PS3 input
 * '<S5>'   : PS3/Control Systems/PS3 tau input control
 * '<S6>'   : PS3/Control Systems/PS3 u input control
 * '<S7>'   : PS3/Control Systems/PS3 tau input control/Thruster allocation
 * '<S8>'   : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act
 * '<S9>'   : PS3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act
 * '<S10>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1
 * '<S11>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2
 * '<S12>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3
 * '<S13>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4
 * '<S14>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5
 * '<S15>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0
 * '<S16>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0
 * '<S17>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0
 * '<S18>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0
 * '<S19>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1
 * '<S20>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0
 * '<S21>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0
 * '<S22>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0
 * '<S23>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0
 * '<S24>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0
 * '<S25>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0
 * '<S26>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0
 * '<S27>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0
 * '<S28>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0
 * '<S29>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0
 * '<S30>'  : PS3/Control Systems/PS3 tau input control/Thruster allocation/tau to f_act/T_e
 * '<S31>'  : PS3/Plants/CSE1
 * '<S32>'  : PS3/Plants/CSE1/Bow Thruster
 * '<S33>'  : PS3/Plants/CSE1/Voith Schneider Propeller
 * '<S34>'  : PS3/Plants/CSE1/Bow Thruster/Saturation Dynamic
 * '<S35>'  : PS3/Plants/CSE1/Bow Thruster/Saturation Dynamic1
 * '<S36>'  : PS3/Plants/CSE1/Bow Thruster/Saturation Dynamic2
 */
#endif                                 /* RTW_HEADER_PS3_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_PS3
#ifdef RVE
#ifdef MULTITASKING

Parameters_PS3 rtParameter[NUMST+!TID01EQ];

#define PS3_P                          (*param_lookup[tid][READSIDE])

Parameters_PS3 *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_PS3 rtParameter[2];

#define PS3_P                          rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
