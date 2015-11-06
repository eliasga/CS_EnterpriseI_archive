/*
 * Copyright 1994-2004 The MathWorks, Inc.
 *
 * Abstract:
 *      A NI "Real-Time (single tasking or pseudo-multitasking,
 *      statically allocated data)" main that runs under most
 *      operating systems.
 *
 *      This file may be a useful starting point when targeting a new
 *      processor or microcontroller.
 *
 *
 * Compiler specified defines:
 *	RT              - Required.
 *      MODEL=modelname - Required.
 *	NUMST=#         - Required. Number of sample times.
 *	NCSTATES=#      - Required. Number of continuous states.
 *      TID01EQ=1 or 0  - Optional. Only define to 1 if sample time task
 *                        id's 0 and 1 have equal rates.
 *      MULTITASKING    - Optional. (use MT for a synonym).
 *	SAVEFILE        - Optional (non-quoted) name of .mat file to create.
 *			  Default is <MODEL>.mat
 *      BORLAND         - Required if using Borland C/C++
 */



#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tmwtypes.h"
#include "rtmodel.h"
#include "rt_sim.h"
#include "rt_logging.h"
#ifdef UseMMIDataLogging
# include "rt_logging_mmi.h"
#endif
#include "rt_nonfinite.h"

#include "model_info.h"
#include "SIT_API.h"

/*=========*
 * Defines *
 *=========*/

#ifndef TRUE
# define FALSE (0)
# define TRUE  (1)
#endif

#ifndef EXIT_FAILURE
# define EXIT_FAILURE  1
#endif
#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS  0
#endif

#define QUOTE1(name) #name
#define QUOTE(name) QUOTE1(name)    /* need to expand name    */

#ifndef RT
# error "must define RT"
#endif

#ifndef MODEL
# error "must define MODEL"
#endif

#ifndef NUMST
# error "must define number of sample times, NUMST"
#endif

#ifndef NCSTATES
# error "must define NCSTATES"
#endif

#ifndef SAVEFILE
# define MATFILE2(file) #file ".mat"
# define MATFILE1(file) MATFILE2(file)
# define MATFILE MATFILE1(MODEL)
#else
# define MATFILE QUOTE(SAVEFILE)
#endif

#define RUN_FOREVER -1.0

#define EXPAND_CONCAT(name1,name2) name1 ## name2
#define CONCAT(name1,name2) EXPAND_CONCAT(name1,name2)
#define RT_MODEL            CONCAT(MODEL,_rtModel)

#ifdef VXWORKS


void InitializeCriticalSection(CRITICAL_SECTION *CriticalSection) {
	*CriticalSection = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
	return;
}
HANDLE CreateSemaphore(long lpSemaphoreAttributes, long lInitialCount, long lMaximumCount, char* lpName) {
	return semBCreate(SEM_Q_PRIORITY, SEM_FULL);
}


void EnterCriticalSection(CRITICAL_SECTION *CriticalSection){
	semTake(*CriticalSection, WAIT_FOREVER);
	return;
}
void WaitForSingleObject(HANDLE hHandle, long dwMilliseconds) {
	semTake(hHandle, dwMilliseconds);
	return;
}


void LeaveCriticalSection(CRITICAL_SECTION *CriticalSection){
	semGive(*CriticalSection);
	return;
}
void ReleaseSemaphore(HANDLE hSemaphore, long lReleaseCount, long lpPreviousCount) {
	semGive(hSemaphore);
	return;
}


void DeleteCriticalSection(CRITICAL_SECTION *CriticalSection){
	semFlush(*CriticalSection);
	semDelete(*CriticalSection);
	return;
}
void CloseHandle(HANDLE hObject) {
	semFlush(hObject);
	semDelete(hObject);
	return;
}


boolean_T _isnan(real_T value) {
	return isNan(value);
}
#endif

#ifdef MULTITASKING
# ifdef NI_SIT_PARAMS
extern Parameters *param_lookup[NUMST+!TID01EQ][2];
# endif
#endif
extern int READSIDE;

/*====================*
 * External functions *
 *====================*/
extern RT_MODEL *MODEL(void);

extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);

#if NCSTATES > 0
  extern void rt_ODECreateIntegrationData(RTWSolverInfo *si);
  extern void rt_ODEUpdateContinuousStates(RTWSolverInfo *si);

# define rt_CreateIntegrationData(S) \
    rt_ODECreateIntegrationData(rtmGetRTWSolverInfo(S));
# define rt_UpdateContinuousStates(S) \
    rt_ODEUpdateContinuousStates(rtmGetRTWSolverInfo(S));
#else
# define rt_CreateIntegrationData(S)  \
      rtsiSetSolverName(rtmGetRTWSolverInfo(S),"FixedStepDiscrete");
# define rt_UpdateContinuousStates(S) \
      rtmSetT(S, rtsiGetSolverStopTime(rtmGetRTWSolverInfo(S)));
#endif

void SetExternalInputs( double *data, int* sampleHit);
void SetExternalOutputs( double *data, int* sampleHit);

/*==================================*
 * Global data local to this module *
 *==================================*/

static struct {
	int_T				stopExecutionFlag;
	int_T				isrOverrun;
	int_T				overrunFlags[NUMST];
	int_T				overrunCount[NUMST];
	int_T				haltonOverrun;
	int_T				completedTaskBitfield;
	int_T				scheduledTaskBitfield;
	CRITICAL_SECTION	taskCriticalSection;
	const char_T		*errmsg;
} SITglobals;

_SITexportglobals SITexportglobals;
long NumInputPorts(void);  /* defined in <model name>.c */
long NumOutputPorts(void); /* defined in <model name>.c */
long NI_InitParamDoubleBuf(void); /* defined in <model name>.c */
long NI_InitializeParamStruct(void); /* defined in <model name>.c */
long NI_InitExternalOutputs(void); /* defined in <model name>.c */

RT_MODEL *S = NULL;

void SetSITErrorMessage(char *ErrMsg, int Error)
{
	//Stop execution if it was an error, otherwise assume it is warning
	if (Error) 
		SITglobals.stopExecutionFlag = 1;
	//Only set the error message text if it hasn't been set before.
	if (!SITglobals.errmsg)
		SITglobals.errmsg = ErrMsg;	
}
/**
	Code to handle the task bitfields. Only used in the multithreaded case.

	Each task is assigned a bit location, with the i_th
	task occupying (1 << i). There are two bitfields,
	completedTaskBitfield and scheduledTaskBitfield.
	Since these are currently stored in 32-bit values, 
	SIT multirate is limited to 32 tasks.

	The function 

		int NIRT_ComputeNextCycleSampleHits(void) 

	is called at the beginning of each cycle (in SCHEDULER)
	after the sample hit pointers are updated, and its return
	value is assigned to scheduledTaskBitfield. This function
	deduces which tasks will be scheduled NEXT cycle, and 
	sets to 1 each of the corresponding bits. This function is 
	included into <model_name>.c by nidll_codegen.tlc.

	As each task completes (in the function rt_oneStepTask,) it 
	calls the function NIRT_ScheduleComplete, and returns its return value. This
	function returns a boolean specifying whether this task is the
	last task to finish this cycle, and has the side effect of 
	updating completedTaskBitfield (bit i = 1 means i_th task is finished,
	bit i = 0, not.)

	The return value of rt_oneStepTask is used in the G code to determine
	when to post the outputs. It is returned to two different VIs,
	depending on whether it is the base rate task or not. For base rate,
	it is returned to "SIT ScheduleTasks" (which is a wrapper for
	the function NIRT_ScheduleTasks) and for other tasks it is 
	returned to "SIT ExecuteTask" (which is a wrapper for the function
	NIRT_TaskTakeOneStep.) In each case, a non-zero return value causes
	the HW outputs to be posted.

	There is a critical section to protect access to the bitfields. It is
	entered in NIRT_ScheduleComplete and SCHEDULER. It is allocated in NIRT_InitializeModel
	and deallocated in NIRT_FinalizeModel.
*/
int NIRT_ComputeNextCycleSampleHits(void); /* defined in <model_name>.c */

/*	Determines if taskID is the last to complete of the tasks scheduled this cycle.
	Has the side effect of updating SITglobals.completedTaskBitfield.
	This function is thread-safe, protecting access to SITglobals.completedTaskBitfield
	and SITglobals.scheduledTaskBitfield with a critical section.
	*/
long NIRT_ScheduleComplete( int taskID)
{
	long scheduleComplete = 0;

	EnterCriticalSection(&SITglobals.taskCriticalSection);

	/* indicate this task is finished */
	SITglobals.completedTaskBitfield |= (1 << taskID);

	/* if all tasks that are scheduled this cycle are complete */
	if ((SITglobals.completedTaskBitfield & SITglobals.scheduledTaskBitfield) == SITglobals.scheduledTaskBitfield) {
		scheduleComplete = 1;
		/* only clear the tasks that are scheduled to complete this cycle, the
		   other tasks may have completed early */
		/* NOTE: probably should manage this in the scheduler so we can use it to detect task overflow */
		SITglobals.completedTaskBitfield &= (~SITglobals.scheduledTaskBitfield);
	} else
		scheduleComplete = 0;

	LeaveCriticalSection(&SITglobals.taskCriticalSection);

	return scheduleComplete;
}


#if !defined(MULTITASKING)  /* SINGLETASKING */

#define FIRST_TID 0

/* Function: rtOneStep ========================================================
 *
 * Abstract:
 *      Perform one step of the model. This function is modeled such that
 *      it could be called from an interrupt service routine (ISR) with minor
 *      modifications.
 */
static int rt_OneStep(RT_MODEL *S, double *inData)
{
    real_T tnext;
	int_T  *sampleHit = rtmGetSampleHitPtr(S);

    /***********************************************
     * Check and see if base step time is too fast *
     ***********************************************/

    if (SITglobals.isrOverrun++) {
        SITglobals.stopExecutionFlag = 1;
        return -1;
    }

    /***********************************************
     * Check and see if error status has been set  *
     ***********************************************/

    if (rtmGetErrorStatus(S) != NULL) {
        SITglobals.stopExecutionFlag = 1;
        return -1;
    }

    /* enable interrupts here */


	SetExternalInputs(inData, sampleHit);

	tnext = rt_SimGetNextSampleHit();
    rtsiSetSolverStopTime(rtmGetRTWSolverInfo(S),tnext);

    MdlOutputs(0);

	SITglobals.isrOverrun--;

	return 0;
} /* end rtOneStep */

#else /* MULTITASKING */

# if TID01EQ == 1
#  define FIRST_TID 1
# else
#  define FIRST_TID 0
# endif




/* Function: SCHEDULER ========================================================
 *
 * Abstract:
 *		Computes SampleHits for tasks in the model.
 *
 */

static int SCHEDULER(RT_MODEL *S) 
{
    int_T  i;
    real_T tnext;
    int_T  *sampleHit = rtmGetSampleHitPtr(S);

    /***********************************************
     * Check and see if base step time is too fast *
     ***********************************************/

    if (SITglobals.isrOverrun++) {
        SITglobals.stopExecutionFlag = 1;
        return -1;
    }

    /***********************************************
     * Check and see if error status has been set  *
     ***********************************************/

    if (rtmGetErrorStatus(S) != NULL) {
        SITglobals.stopExecutionFlag = 1;
        return -1;
    }
    /* enable interrupts here */

	/* compute next cycle hits and update niScheduledTaskBitfield */
	EnterCriticalSection( &SITglobals.taskCriticalSection);

	SITglobals.scheduledTaskBitfield = NIRT_ComputeNextCycleSampleHits();
	
	LeaveCriticalSection(&SITglobals.taskCriticalSection);

    tnext = rt_SimUpdateDiscreteEvents(rtmGetNumSampleTimes(S),
                                       rtmGetTimingData(S),
                                       rtmGetSampleHitPtr(S),
                                       rtmGetPerTaskSampleHitsPtr(S));
    rtsiSetSolverStopTime(rtmGetRTWSolverInfo(S),tnext);

	/*********************************************
     * Step the model for any other sample times *
     *********************************************/
	for (i=1+FIRST_TID; i<NUMST; i++) {
        if (sampleHit[i]) {
		/*	if sampleHit, mark the overrunFlag : if the flag is already marked, 
			the task has not finished its run from last sampleHit.
			Marking the flag in scheduler instead of in the task:
			To detect the case of overrun when the task cannot even start 
			execution even though it is scheduled 
		*/
			if (SITglobals.overrunFlags[i] > 0)  {// check for overrun
				printf("overrun in task %d: %d\n", i, SITglobals.overrunFlags[i]);
                SITglobals.overrunCount[i]++;  // update counter
				if (SITglobals.haltonOverrun) {
					SetSITErrorMessage("Task Overran", 1);
				}
			} else {
				SITglobals.overrunFlags[i] = 1;
			}
		}
	}

    SITglobals.isrOverrun--;

	return 0;

} /* end SCHEDULER */

/* rt_OneStepTask
	Takes one step for the task specified by tid
	RT_MODEL *S: Pointer to model information
	int tid: Task ID to step
	double *inData: Pointer to inport data.  Ignored unless it is the FIRST_TID (aka base rate).
	returns:
		1 if this is the last task to execute for a time step
		0 if other tasks still need to execute
		-1 if an error occured
		
*/
static int rt_OneStepTask(RT_MODEL *S, int tid, double *inData)
{
	int retVal = 0;

	if (tid == FIRST_TID) {
	//Return if there has been a previous error
		if (SITglobals.stopExecutionFlag) 
			return -1;

	// As FIRST_TID executes in same loop as scheduler, Overruns are detected by the tloop.

    /*******************************************
     * Step the model for the base sample time *
     *******************************************/
	if (!inData && (NumInputPorts() > 0)) {
		// For baserate (FIRST_TID) we need inData, but only set error message if it hasn't been set yet
		SetSITErrorMessage("External Input data array is NULL for base rate task",1);
		return -1;
	}
 
	//MdlUpdate is not executed on the first iteration.

	SetExternalInputs(inData, rtmGetSampleHitPtr(S)); // pull inport data in from LabVIEW
    MdlOutputs(FIRST_TID);
	retVal = NIRT_ScheduleComplete( tid);


  } else { // of if tid==FIRST_TID 
    /*********************************************
     * Step the model for any other sample times *
     *********************************************/
    if (tid<FIRST_TID+1 || tid >= NUMST) 
    	return -1;
	
    MdlOutputs(tid);
	MdlUpdate(tid);

	rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S),tid);

	/* Indicate task complete */
    SITglobals.overrunFlags[tid]--;

	retVal = NIRT_ScheduleComplete( tid);

  } // of tid==FIRST_TID

  return retVal;

} /* end rtOneStep */

#endif /* MULTITASKING */



    /************************
     * Initialize the model *
     ************************/

DLL_EXPORT long NIRT_InitializeModel (double finaltime, double *outTimeStep, long *outNumInports, long *outNumOutports, long *numTasks) {
    const char *status = NULL;
    
	//Make sure SITglobals is reinitialized even if DLL is not reloaded
    (void)memset(&SITglobals, 0, sizeof(SITglobals));
    (void)memset(&SITexportglobals, 0, sizeof(SITexportglobals));

    rt_InitInfAndNaN(sizeof(real_T));

	NI_InitializeParamStruct();

    S = MODEL();
    if (rtmGetErrorStatus(S) != NULL) {
        (void)fprintf(stderr,"Error during model registration: %s\n",
                      rtmGetErrorStatus(S));
        return 5;
    }
    if (finaltime >= 0.0 || finaltime == RUN_FOREVER) rtmSetTFinal(S,finaltime);

    MdlInitializeSizes();
    MdlInitializeSampleTimes();
    
    status = rt_SimInitTimingEngine(rtmGetNumSampleTimes(S),
                                    rtmGetStepSize(S),
                                    rtmGetSampleTimePtr(S),
                                    rtmGetOffsetTimePtr(S),
                                    rtmGetSampleHitPtr(S),
                                    rtmGetSampleTimeTaskIDPtr(S),
                                    rtmGetTStart(S),
                                    &rtmGetSimTimeStep(S),
                                    &rtmGetTimingData(S));

    if (status != NULL) {
        (void)fprintf(stderr,
                "Failed to initialize sample time engine: %s\n", status);
        exit(EXIT_FAILURE);
    }
    rt_CreateIntegrationData(S);

    SITglobals.errmsg = rt_StartDataLogging(rtmGetRTWLogInfo(S),
                                        rtmGetTFinal(S),
                                        rtmGetStepSize(S),
                                        &rtmGetErrorStatus(S));
										
    if (SITglobals.errmsg != NULL) {
        (void)fprintf(stderr,"Error starting data logging: %s\n",SITglobals.errmsg);
        return(3);
    }

	NI_InitParamDoubleBuf();
    MdlStart();

	
    if (rtmGetErrorStatus(S) != NULL) SITglobals.stopExecutionFlag = 1;
	
	NIRT_GetModelSpec(NULL, 0, outTimeStep, outNumInports, outNumOutports, numTasks);


	InitializeCriticalSection(&SITglobals.taskCriticalSection);
	SITexportglobals.flipCriticalSection = CreateSemaphore(NULL, 1, 1, NULL);
	
	if (SITexportglobals.flipCriticalSection == NULL) 
		SetSITErrorMessage("Failed to create semaphore.", 1);

	NI_InitExternalOutputs();

#if defined(MULTITASKING)  /* MULTITASKING */
	{
		int_T  *sampleHit = rtmGetSampleHitPtr(S);
		int_T tid;
		// Make sure SampleHits is uptodate
		rt_SimUpdateDiscreteEvents(rtmGetNumSampleTimes(S),
                                       rtmGetTimingData(S),
                                       rtmGetSampleHitPtr(S),
                                       rtmGetPerTaskSampleHitsPtr(S));
	
		for (tid=FIRST_TID+1; tid<NUMST; tid++) {
			//if a task is not scheduled to run first iteration, mark it as already complete
			//so we don't wait for it to finish the first time it is scheduled to run
			SITglobals.completedTaskBitfield |= ((sampleHit[tid]!=0) << tid);
		}
	}
#endif // defined(MULTITASKING)

	return(0);

} // end of InitializeModel()

DLL_EXPORT long NIRT_PostOutputs(double *outData) 
{
	SetExternalOutputs(outData, rtmGetSampleHitPtr(S)); // push outport data out to LabVIEW
	
	return 0;	
}

// Decrement our count for entries into the critical section, signalling the it is no longer safe to probe
// Update states. Leave critical section.
DLL_EXPORT long NIRT_ModelUpdate() 
{
	if (SITexportglobals.inCriticalSection) {
		SITexportglobals.inCriticalSection--;
		MdlUpdate(FIRST_TID);
#if defined(MULTITASKING)
		if (rtmGetSampleTime(S,0) == CONTINUOUS_SAMPLE_TIME) {
			rt_UpdateContinuousStates(S); 
		} else {
			rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S), 0);
		}
# if FIRST_TID == 1
	 	rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S),1);
# endif
#else
		rt_SimUpdateDiscreteTaskSampleHits(rtmGetNumSampleTimes(S), rtmGetTimingData(S), rtmGetSampleHitPtr(S), rtmGetTPtr(S));

		if (rtmGetSampleTime(S,0) == CONTINUOUS_SAMPLE_TIME)
			rt_UpdateContinuousStates(S);
#endif
		ReleaseSemaphore(SITexportglobals.flipCriticalSection,1,NULL);
	}
	return SITexportglobals.inCriticalSection;
}

/*  
	Schedule Tasks 
	used to run the base rate and figure out which other tasks to run for 
	multi-rate simulations.  We do not run the other tasks here, they are
	executed seperately through NIRT_TaskTakeOneStep)
	double *inData: Points to an array of elements sent to the model inports
    double *outData: Points to an array of elements sent to the model outports
	double *outTime: Used to return the current model time.  Ignored if it is NULL
	long *dispatchtasks: Array size of NUMST.  dispatchtaks[i] is set to 1 for task
		that need to be executed.  
		dispatch[0] is 1 for scheduleComplete, 0 for tasks remaining, and -1 for error
*/
DLL_EXPORT long NIRT_ScheduleTasks(double *inData, double *outTime, long *dispatchtasks) 
{	
#ifndef MULTITASKING
	SetSITErrorMessage("Called ScheduleTasks() for a single-rate model.  Use Schedule() instead.",1);
	return 1;
#else
	int i, lastStep = 1, scheduleComplete = 0;
	// donot increment the time..

	if (outTime)
		*outTime = rtmGetT(S);

	for (i=0; i<NUMST; i++)
		dispatchtasks[i] = rtmGetSampleHitPtr(S)[i + TID01EQ];
	
	/* Critical section is used to prevent the background loop from switching parameters
	sets while the baserate is running.  On a single core system this can not happen, but
	on a multi-core system the baserate and background can be executing at the same time. */
	WaitForSingleObject(SITexportglobals.flipCriticalSection, INFINITE);
	if (SITexportglobals.inCriticalSection > 0) {
		SetSITErrorMessage("Each call to ScheduleTasks() MUST be followed by a call to ModelUpdate() before ScheduleTasks() is called again.",1);
		ReleaseSemaphore(SITexportglobals.flipCriticalSection, 1, NULL);
		return 1;
	}

	/* For each task other than the base rate copy parameters if there are new ones.
	Since the task is about the be scheduled it should not be executing at the moment
	so copying the parameters will be safe.
	*/
# ifdef NI_SIT_PARAMS
    for (i = 1; i < NUMST - TID01EQ; i++) {
		if (dispatchtasks[i] && (SITexportglobals.copyTaskBitfield & (1 << i))) {
			memcpy(param_lookup[i+TID01EQ][1-READSIDE], param_lookup[0][READSIDE], sizeof(Parameters));
			SITexportglobals.copyTaskBitfield &= ~(1 << i);
		}
    }
# endif
	if(!SITglobals.stopExecutionFlag) {  //If stopExecutionFlag is true we have had an error
		if (rtmGetTFinal(S) == RUN_FOREVER ||rtmGetTFinal(S)-rtmGetT(S) > rtmGetT(S)*DBL_EPSILON) {
			SCHEDULER(S);
			scheduleComplete = rt_OneStepTask(S,FIRST_TID, inData);
			lastStep = rtmGetStopRequested(S);
		} else if (!rtmGetStopRequested(S)) { // take last step
			SCHEDULER(S);
			scheduleComplete = rt_OneStepTask(S,FIRST_TID, inData);
		}
	} else {
		scheduleComplete = -1;
	}

	SITexportglobals.inCriticalSection++;
	dispatchtasks[0] = scheduleComplete;  //First element of dispatch list tells us if schedule is done 
	
	return SITglobals.stopExecutionFlag | lastStep;
#endif
}

/*  
	Scheduler behaves traditionally for singletasking (Get Inputs, Take Step, Post Outputs).
	For multitasking, the outputs are delayed by one time step. 
	
	This scheduler ignores dispatchtasks input as all tasks are dispatched based on their sample
	rate information alone. This is done externally by timed loops. 
	
*/
DLL_EXPORT long NIRT_Schedule(double *inData, double *outData, double *outTime, long *dispatchtasks) 
{
#ifdef MULTITASKING
	SetSITErrorMessage("Called Schedule() for a multi-rate model.  Use ScheduleTasks() instead.",1);
	return 1;
#else
	int lastStep = 1;
	
	if (outTime)
		*outTime = rtmGetT(S);

	WaitForSingleObject(SITexportglobals.flipCriticalSection, INFINITE);
	if (SITexportglobals.inCriticalSection > 0) {
		SetSITErrorMessage("Each call to Schedule() MUST be followed by a call to ModelUpdate() before Schedule() is called again.",1);
		ReleaseSemaphore(SITexportglobals.flipCriticalSection, 1, NULL);
		return 1;
	}
	
	if (!SITglobals.stopExecutionFlag && 
		(rtmGetTFinal(S) == RUN_FOREVER || rtmGetTFinal(S)-rtmGetT(S) > rtmGetT(S)*DBL_EPSILON)) {
		rt_OneStep(S, inData);		
		lastStep = rtmGetStopRequested(S);
	} else if (!SITglobals.stopExecutionFlag && !rtmGetStopRequested(S)){ // take last step
		rt_OneStep(S, inData);
	}
	SetExternalOutputs(outData, rtmGetSampleHitPtr(S)); // push outport data out to LabVIEW	
	SITexportglobals.inCriticalSection++;

	return lastStep;	
#endif
}


/* Use for SINGLETASKING mode ONLY*/

DLL_EXPORT long NIRT_TakeOneStep(double *inData, double *outData, double *outTime)
{
    return NIRT_Schedule(inData, outData, outTime, NULL);
}

/* Use for MULTITASKING mode only */


DLL_EXPORT long NIRT_TaskTakeOneStep(long tid)
{
#if defined(MULTITASKING)  
  	return rt_OneStepTask(S,tid, NULL);
#else
	return 0;
#endif
}


DLL_EXPORT long NIRT_FinalizeModel(void)
{
    rt_StopDataLogging(MATFILE,rtmGetRTWLogInfo(S));

    if (SITglobals.errmsg) {
        (void)fprintf(stderr,"%s\n",SITglobals.errmsg);
        return 1;
		}

    if (rtmGetErrorStatus(S) != NULL) {
        (void)fprintf(stderr,"%s\n", rtmGetErrorStatus(S));
        return 1;
	    }

    MdlTerminate();

	DeleteCriticalSection(&SITglobals.taskCriticalSection);
	CloseHandle(SITexportglobals.flipCriticalSection);

    return(0);

} /* end FinalizeModel */

// pass error to labview.
DLL_EXPORT long NIRT_ModelError(char* errmsg, long *msglen) 
{
	if (!SITglobals.errmsg && !rtmGetErrorStatus(S))
		return *msglen = 0; // No error
	if (*msglen > 0) {
		if(SITglobals.errmsg){
			if (*msglen > (long)strlen(SITglobals.errmsg)) 
				*msglen = strlen(SITglobals.errmsg);
			strncpy(errmsg, SITglobals.errmsg, *msglen);
		} else {
			if (*msglen > (long)strlen(rtmGetErrorStatus(S))) 
				*msglen = strlen(rtmGetErrorStatus(S));
			strncpy(errmsg, rtmGetErrorStatus(S), *msglen);
		}
	}
	return 1;
}

extern const NI_Task NI_TaskList[];
extern const long NI_NumTasks;


DLL_EXPORT long NIRT_TaskRunTimeInfo(long halt, long* overruns, long *numtasks) 
{
	int TaskOverrun = 0, i=0;
	
	if (halt) 
		SITglobals.haltonOverrun = halt-1;
	for (i=0; i<NUMST-TID01EQ; i++) {
		TaskOverrun+= overruns[i] = SITglobals.overrunCount[i+FIRST_TID];
    }

	*numtasks = NUMST;
	return TaskOverrun;
}


/* task information 
 * as the NiTaskList also contains the baserate as a 0th task, filter it out 
 */
DLL_EXPORT long NIRT_GetTaskSpec(long index, long *tID, double *tstep, double *offset) 
{
   if (index<0 || index>=NI_NumTasks) 
	return NI_NumTasks;

   if (tID) *tID = NI_TaskList[index].tid;
   if (tstep) *tstep = NI_TaskList[index].tstep;
   if (offset) *offset = NI_TaskList[index].offset;
   return 0;
}

/*************************************************
* Access Model Information without Initializing *
* return -1 if some info is not available	 * 
*************************************************/
DLL_EXPORT long NIRT_GetModelSpec(char* name, long *namelen, double *baseTimeStep, 
											long *outNumInports, long *outNumOutports, long *numTasks)
{
	// fill name buffer to min of namelen or namelen
	if (namelen) {
		long i, length;
		length = (long)strlen(QUOTE(MODEL));
		if (*namelen > length)
			*namelen = length;

		strncpy(name, QUOTE(MODEL), *namelen);

		for(i=0; i<*namelen; i++)
			name[i] = (char) tolower(name[i]);
	}
	if (baseTimeStep)
		*baseTimeStep = NI_TaskList[0].tstep;
	
	if (outNumInports)
		*outNumInports = NumInputPorts();
	
	if (outNumOutports)
		*outNumOutports = NumOutputPorts();
	
	if (numTasks) 
#if !defined(MULTITASKING)  /* SINGLETASKING */
	*numTasks = 1; 
#else
	*numTasks = NI_NumTasks;
#endif
	
	return NI_OK;
}
 
