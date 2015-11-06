
#ifndef NIRT_MODEL_INFO_H
#define NIRT_MODEL_INFO_H

#ifdef VXWORKS
# include <private/mathP.h>
# include <private/semLibP.h>
# define CRITICAL_SECTION SEM_ID
# define HANDLE SEM_ID
# define INFINITE WAIT_FOREVER

void InitializeCriticalSection(CRITICAL_SECTION *CriticalSection);
HANDLE CreateSemaphore(long lpSemaphoreAttributes, long lInitialCount, long lMaximumCount, char* lpName);

void EnterCriticalSection(CRITICAL_SECTION *CriticalSection);
void WaitForSingleObject(HANDLE hHandle, long dwMilliseconds);

void LeaveCriticalSection(CRITICAL_SECTION *CriticalSection);
void ReleaseSemaphore(HANDLE hSemaphore, long lReleaseCount, long lpPreviousCount);

void DeleteCriticalSection(CRITICAL_SECTION *CriticalSection);
void CloseHandle(HANDLE hObject);

#else
# include <windows.h>
#endif

typedef struct {
	HANDLE	flipCriticalSection;
	uint_T				copyTaskBitfield;
	// inCriticalSection keeps track of how many entries the TCL has into the critical section
	// presumably, it should only have <= 1, and if it ever goes above that, we will error out.
	// the critical section is acquired BEFORE the call to MdlOutputs, inCriticalSection is incremented AFTER.
	// the critical section is released AFTER the call to MdlUpdate, inCriticalSection is decremented BEFORE.
	// this allows us to use the flag to know when it is valid to probe.
	uint_T				inCriticalSection;
} _SITexportglobals;

typedef struct {
  int    tid;
  double tstep;
  double offset;
  int priority;
} NI_Task;


typedef struct {
  int idx;
  char* paramname;
  unsigned int addr;
  int datatype;
  int width;
  int numofdims; // number of dimensions
  int dimListOffset;	 // dimensions array
  char* expression;
  int IsComplex;
} NI_Parameter;

#define BLOCKIO_SIG		0
#define EXTIO_SIG		1

// for virtual signals, addr is offset into virtualmap array that contains indices in NI_Signal
// array corresponding to the non-virtual signals that compose the virtual signal.
// currently unused 
#define VIRTUAL_SIG		2

typedef struct {
  int    idx;
  char*  blockname;
  int    portno;
  char* signalname;
  unsigned int addr;
  int baseaddr;
  int	 datatype;
  int width;
  int numofdims; // number of dimensions
  int dimListOffset;	 // dimensions array
  int IsComplex;
} NI_Signal;

#define EXT_IN		0
#define EXT_OUT		1

typedef struct {
  int	idx;
  char*	name;
  int	TID;
  int   type; // Ext Input: 0, Ext Output: 1
  int  width; // = dimX*dimY
  int	dimX;
  int	dimY; // support only 2-D 
} NI_ExternalIO;
		
// defined in nidll_main.c
void SetSITErrorMessage(char *ErrMsg, int Error);

#endif
