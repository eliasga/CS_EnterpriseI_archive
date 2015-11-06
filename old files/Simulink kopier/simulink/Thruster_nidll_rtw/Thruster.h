/*
 * Thruster.h
 *
 * Real-Time Workshop code generation for Simulink model "Thruster.mdl".
 *
 * Model Version              : 1.8
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 15:31:34 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Thruster_h_
#define RTW_HEADER_Thruster_h_
#ifndef Thruster_COMMON_INCLUDES_
# define Thruster_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "rt_SATURATE.h"
#include "rt_SIGNd_snf.h"
#include "rt_look.h"
#include "rt_look2d_normal.h"
#endif                                 /* Thruster_COMMON_INCLUDES_ */

#include "Thruster_types.h"

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
#define Thruster_rtModel               RT_MODEL_Thruster

/* Block signals (auto storage) */
typedef struct {
  real_T ypositionofleftanalogstick11; /* '<S4>/ScalingLY' */
  real_T u_1;                          /* '<S5>/PS3 u_1' */
  real_T xpositionofleftanalogstick11; /* '<S4>/ScalingLX' */
  real_T u_2;                          /* '<S5>/PS3 u_2' */
  real_T ypositionofrightanalogstick11;/* '<S4>/ScalingRY' */
  real_T u_3;                          /* '<S5>/PS3 u_3' */
  real_T xpositionofrightanalogstick11;/* '<S4>/Scaling_RX' */
  real_T u_4;                          /* '<S5>/PS3 u_4' */
  real_T BowThrusterdirection;         /* '<S5>/Add' */
  real_T u_5;                          /* '<S5>/PS3 u_5' */
  real_T LabVIEWu_1;                   /* '<S6>/LabVIEW u_1' */
  real_T LabVIEWu_2;                   /* '<S6>/LabVIEW u_2' */
  real_T LabVIEWu_3;                   /* '<S6>/LabVIEW u_3' */
  real_T LabVIEWu_4;                   /* '<S6>/LabVIEW u_4' */
  real_T LabVIEWu_5;                   /* '<S6>/LabVIEW u_5' */
  real_T ThrustersettingSwitch[7];     /* '<S1>/Thruster setting Switch' */
  real_T Saturation[7];                /* '<S1>/Saturation' */
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
  real_T BT_D_Gain1;                   /* '<S8>/BT_D_Gain1' */
  real_T BT_D_Gain2;                   /* '<S8>/BT_D_Gain2' */
  real_T Add;                          /* '<S8>/Add' */
  real_T BT_L_Gain1;                   /* '<S8>/BT_L_Gain1' */
  real_T BT_L_Gain2;                   /* '<S8>/BT_L_Gain2' */
  real_T Neg;                          /* '<S8>/Neg' */
  real_T Sum1;                         /* '<S8>/Sum1' */
  real_T Sum2;                         /* '<S8>/Sum2' */
  real_T Switch;                       /* '<S10>/Switch' */
  real_T Switch2;                      /* '<S10>/Switch2' */
  real_T Switch_g;                     /* '<S11>/Switch' */
  real_T Switch2_b;                    /* '<S11>/Switch2' */
  real_T Switch_k;                     /* '<S12>/Switch' */
  real_T Switch2_p;                    /* '<S12>/Switch2' */
  real_T Sign;                         /* '<S9>/Sign' */
  real_T PortVPS_X;                    /* '<S9>/Product1' */
  real_T PortVPS_X_g;                  /* '<S9>/-x' */
  real_T PortVSP_Y;                    /* '<S9>/Product2' */
  real_T PortVSP_Y_l;                  /* '<S9>/-y' */
  real_T StarboardVSP_X;               /* '<S9>/Product3' */
  real_T StarboardVSP_Y;               /* '<S9>/Product4' */
  real_T Servo1;                       /* '<S9>/Servo1' */
  real_T Servo2;                       /* '<S9>/Servo2' */
  real_T Servo3;                       /* '<S9>/Servo3' */
  real_T Servo4;                       /* '<S9>/Servo4' */
  real_T VPS_Speed_Gain;               /* '<S9>/VPS_Speed_Gain' */
  real_T Sum;                          /* '<S9>/Sum' */
  real_T VSPSPort;                     /* '<S9>/VSPS Port' */
  real_T VSPSStarboard;                /* '<S9>/VSPS Starboard' */
  boolean_T LowerRelop1;               /* '<S10>/LowerRelop1' */
  boolean_T UpperRelop;                /* '<S10>/UpperRelop' */
  boolean_T LowerRelop1_j;             /* '<S11>/LowerRelop1' */
  boolean_T UpperRelop_a;              /* '<S11>/UpperRelop' */
  boolean_T LowerRelop1_c;             /* '<S12>/LowerRelop1' */
  boolean_T UpperRelop_h;              /* '<S12>/UpperRelop' */
} BlockIO_Thruster;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  int32_T SignalProbe_DWORK2;          /* '<Root>/SignalProbe' */
  uint32_T SignalProbe_DWORK3;         /* '<Root>/SignalProbe' */
  uint8_T SignalProbe_DWORK1[9];       /* '<Root>/SignalProbe' */
} D_Work_Thruster;

/* Backward compatible GRT Identifiers */
#define rtB                            Thruster_B
#define BlockIO                        BlockIO_Thruster
#define rtXdot                         Thruster_Xdot
#define StateDerivatives               StateDerivatives_Thruster
#define tXdis                          Thruster_Xdis
#define StateDisabled                  StateDisabled_Thruster
#define rtP                            Thruster_P
#define Parameters                     Parameters_Thruster
#define rtDWork                        Thruster_DWork
#define D_Work                         D_Work_Thruster

/* Parameters (auto storage) */
struct Parameters_Thruster_ {
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
                                        * '<S5>/PS3 u_1'
                                        */
  real_T AS_LX_Value;                  /* Expression: 0
                                        * '<S4>/AS_LX'
                                        */
  real_T ScalingLX_Gain;               /* Expression: 1/32767
                                        * '<S4>/ScalingLX'
                                        */
  real_T PS3u_2_Gain;                  /* Expression: 1
                                        * '<S5>/PS3 u_2'
                                        */
  real_T AS_RY_Value;                  /* Expression: 0
                                        * '<S4>/AS_RY'
                                        */
  real_T ScalingRY_Gain;               /* Expression: 1/32767
                                        * '<S4>/ScalingRY'
                                        */
  real_T PS3u_3_Gain;                  /* Expression: 1
                                        * '<S5>/PS3 u_3'
                                        */
  real_T AS_RX_Value;                  /* Expression: 0
                                        * '<S4>/AS_RX'
                                        */
  real_T Scaling_RX_Gain;              /* Expression: 1/32767
                                        * '<S4>/Scaling_RX'
                                        */
  real_T PS3u_4_Gain;                  /* Expression: 1
                                        * '<S5>/PS3 u_4'
                                        */
  real_T L2_Value;                     /* Expression: 0
                                        * '<S4>/L2'
                                        */
  real_T R2_Value;                     /* Expression: 0
                                        * '<S4>/R2'
                                        */
  real_T PS3u_5_Gain;                  /* Expression: 1
                                        * '<S5>/PS3 u_5'
                                        */
  real_T PS3_BT_Power_Value;           /* Expression: 0
                                        * '<S4>/PS3_BT_Power'
                                        */
  real_T PS3_VSP_Speed_Value;          /* Expression: 0
                                        * '<S4>/PS3_VSP_Speed'
                                        */
  real_T u1_Value;                     /* Expression: 0
                                        * '<S6>/u1'
                                        */
  real_T LabVIEWu_1_Gain;              /* Expression: 1
                                        * '<S6>/LabVIEW u_1'
                                        */
  real_T u2_Value;                     /* Expression: 0
                                        * '<S6>/u2'
                                        */
  real_T LabVIEWu_2_Gain;              /* Expression: 1
                                        * '<S6>/LabVIEW u_2'
                                        */
  real_T u3_Value;                     /* Expression: 0
                                        * '<S6>/u3'
                                        */
  real_T LabVIEWu_3_Gain;              /* Expression: 1
                                        * '<S6>/LabVIEW u_3'
                                        */
  real_T u4_Value;                     /* Expression: 0
                                        * '<S6>/u4'
                                        */
  real_T LabVIEWu_4_Gain;              /* Expression: 1
                                        * '<S6>/LabVIEW u_4'
                                        */
  real_T u5_Value;                     /* Expression: 0
                                        * '<S6>/u5'
                                        */
  real_T LabVIEWu_5_Gain;              /* Expression: 1
                                        * '<S6>/LabVIEW u_5'
                                        */
  real_T BTpower_Value;                /* Expression: 0
                                        * '<S6>/BT power'
                                        */
  real_T VSPspeed_Value;               /* Expression: 0
                                        * '<S6>/VSP speed'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1.0
                                        * '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1.0
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
                                        * '<S8>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P2;                 /* Expression: dtype
                                        * '<S8>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P3;                 /* Expression: portnum
                                        * '<S8>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P4;                 /* Expression: stime
                                        * '<S8>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P5;                 /* Expression: stype
                                        * '<S8>/SIT PWM0 BT'
                                        */
  real_T SITPWM0BT_P6;                 /* Expression: btype
                                        * '<S8>/SIT PWM0 BT'
                                        */
  real_T BT_D_Gain1_Gain;              /* Expression: 0.02
                                        * '<S8>/BT_D_Gain1'
                                        */
  real_T BT_Power_Offset1_Value;       /* Expression: 0.05
                                        * '<S8>/BT_Power_Offset1'
                                        */
  real_T BT_D_Gain2_Gain;              /* Expression: 0.02
                                        * '<S8>/BT_D_Gain2'
                                        */
  real_T BT_L_Gain1_Gain;              /* Expression: 0.02
                                        * '<S8>/BT_L_Gain1'
                                        */
  real_T BT_L_Gain2_Gain;              /* Expression: -0.02
                                        * '<S8>/BT_L_Gain2'
                                        */
  real_T BT_Power_Offset2_Value;       /* Expression: 0.05
                                        * '<S8>/BT_Power_Offset2'
                                        */
  real_T BT_Power_Offset3_Value;       /* Expression: 0.05
                                        * '<S8>/BT_Power_Offset3'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * '<S8>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * '<S8>/Constant1'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S8>/Neg'
                                        */
  real_T SITPWM4Servo1_P1;             /* Expression: width
                                        * '<S9>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P2;             /* Expression: dtype
                                        * '<S9>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P3;             /* Expression: portnum
                                        * '<S9>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P4;             /* Expression: stime
                                        * '<S9>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P5;             /* Expression: stype
                                        * '<S9>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM4Servo1_P6;             /* Expression: btype
                                        * '<S9>/SIT PWM4 Servo1'
                                        */
  real_T SITPWM5Servo2_P1;             /* Expression: width
                                        * '<S9>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P2;             /* Expression: dtype
                                        * '<S9>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P3;             /* Expression: portnum
                                        * '<S9>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P4;             /* Expression: stime
                                        * '<S9>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P5;             /* Expression: stype
                                        * '<S9>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM5Servo2_P6;             /* Expression: btype
                                        * '<S9>/SIT PWM5 Servo2'
                                        */
  real_T SITPWM6Servo3_P1;             /* Expression: width
                                        * '<S9>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P2;             /* Expression: dtype
                                        * '<S9>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P3;             /* Expression: portnum
                                        * '<S9>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P4;             /* Expression: stime
                                        * '<S9>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P5;             /* Expression: stype
                                        * '<S9>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM6Servo3_P6;             /* Expression: btype
                                        * '<S9>/SIT PWM6 Servo3'
                                        */
  real_T SITPWM7Servo4_P1;             /* Expression: width
                                        * '<S9>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P2;             /* Expression: dtype
                                        * '<S9>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P3;             /* Expression: portnum
                                        * '<S9>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P4;             /* Expression: stime
                                        * '<S9>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P5;             /* Expression: stype
                                        * '<S9>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM7Servo4_P6;             /* Expression: btype
                                        * '<S9>/SIT PWM7 Servo4'
                                        */
  real_T SITPWM1VSPSPort_P1;           /* Expression: width
                                        * '<S9>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P2;           /* Expression: dtype
                                        * '<S9>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P3;           /* Expression: portnum
                                        * '<S9>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P4;           /* Expression: stime
                                        * '<S9>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P5;           /* Expression: stype
                                        * '<S9>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM1VSPSPort_P6;           /* Expression: btype
                                        * '<S9>/SIT PWM1 VSPS Port'
                                        */
  real_T SITPWM2VSPSStarboard_P1;      /* Expression: width
                                        * '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P2;      /* Expression: dtype
                                        * '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P3;      /* Expression: portnum
                                        * '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P4;      /* Expression: stime
                                        * '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P5;      /* Expression: stype
                                        * '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  real_T SITPWM2VSPSStarboard_P6;      /* Expression: btype
                                        * '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  real_T x_Gain;                       /* Expression: -1
                                        * '<S9>/-x'
                                        */
  real_T y_Gain;                       /* Expression: -1
                                        * '<S9>/-y'
                                        */
  real_T Servo1_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S9>/Servo1'
                                        */
  real_T Servo1_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S9>/Servo1'
                                        */
  real_T Servo1_Table[9];              /* Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
                                        * '<S9>/Servo1'
                                        */
  real_T Servo2_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S9>/Servo2'
                                        */
  real_T Servo2_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S9>/Servo2'
                                        */
  real_T Servo2_Table[9];              /* Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
                                        * '<S9>/Servo2'
                                        */
  real_T Servo3_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S9>/Servo3'
                                        */
  real_T Servo3_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S9>/Servo3'
                                        */
  real_T Servo3_Table[9];              /* Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
                                        * '<S9>/Servo3'
                                        */
  real_T Servo4_RowIdx[3];             /* Expression: [-1,0,1]
                                        * '<S9>/Servo4'
                                        */
  real_T Servo4_ColIdx[3];             /* Expression: [-1,0,1]
                                        * '<S9>/Servo4'
                                        */
  real_T Servo4_Table[9];              /* Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
                                        * '<S9>/Servo4'
                                        */
  real_T VPS_Speed_Gain_Gain;          /* Expression: -0.02
                                        * '<S9>/VPS_Speed_Gain'
                                        */
  real_T VPS_Power_Offset_Value;       /* Expression: 0.05
                                        * '<S9>/VPS_Power_Offset'
                                        */
  real_T VSPSPort_Gain;                /* Expression: 1
                                        * '<S9>/VSPS Port'
                                        */
  real_T VSPSStarboard_Gain;           /* Expression: 1
                                        * '<S9>/VSPS Starboard'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_Thruster {
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
extern Parameters_Thruster Thruster_P;

/* Block signals (auto storage) */
extern BlockIO_Thruster Thruster_B;

/* Block states (auto storage) */
extern D_Work_Thruster Thruster_DWork;

/* Real-time Model object */
extern RT_MODEL_Thruster *Thruster_M;

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
 * '<Root>' : Thruster
 * '<S1>'   : Thruster/Control Systems
 * '<S2>'   : Thruster/HMI
 * '<S3>'   : Thruster/Plants
 * '<S4>'   : Thruster/Control Systems/PS3 input
 * '<S5>'   : Thruster/Control Systems/PS3 u input control
 * '<S6>'   : Thruster/Control Systems/Precision control
 * '<S7>'   : Thruster/Plants/CSE1
 * '<S8>'   : Thruster/Plants/CSE1/Bow Thruster
 * '<S9>'   : Thruster/Plants/CSE1/Voith Schneider Propeller
 * '<S10>'  : Thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic
 * '<S11>'  : Thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic1
 * '<S12>'  : Thruster/Plants/CSE1/Bow Thruster/Saturation Dynamic2
 */
#endif                                 /* RTW_HEADER_Thruster_h_ */

#define NI_SIT_PARAMS
#ifdef NI_ROOTMODEL_Thruster
#ifdef RVE
#ifdef MULTITASKING

Parameters_Thruster rtParameter[NUMST+!TID01EQ];

#define Thruster_P                     (*param_lookup[tid][READSIDE])

Parameters_Thruster *param_lookup[NUMST][2] = {
  { &rtParameter[0], &rtParameter[1] },
};

#else

Parameters_Thruster rtParameter[2];

#define Thruster_P                     rtParameter[READSIDE]
#endif

int READSIDE = 0;
int tid = 0;

#endif
#endif
