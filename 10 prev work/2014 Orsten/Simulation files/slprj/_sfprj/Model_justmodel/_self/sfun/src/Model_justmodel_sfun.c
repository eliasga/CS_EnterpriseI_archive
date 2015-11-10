/* Include files */

#include "Model_justmodel_sfun.h"
#include "Model_justmodel_sfun_debug_macros.h"
#include "c1_Model_justmodel.h"
#include "c2_Model_justmodel.h"
#include "c3_Model_justmodel.h"
#include "c4_Model_justmodel.h"
#include "c5_Model_justmodel.h"
#include "c6_Model_justmodel.h"
#include "c7_Model_justmodel.h"
#include "c8_Model_justmodel.h"
#include "c9_Model_justmodel.h"
#include "c10_Model_justmodel.h"
#include "c11_Model_justmodel.h"
#include "c12_Model_justmodel.h"
#include "c13_Model_justmodel.h"
#include "c14_Model_justmodel.h"
#include "c15_Model_justmodel.h"
#include "c25_Model_justmodel.h"
#include "c26_Model_justmodel.h"
#include "c27_Model_justmodel.h"
#include "c28_Model_justmodel.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _Model_justmodelMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void Model_justmodel_initializer(void)
{
}

void Model_justmodel_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_Model_justmodel_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==8) {
    c8_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==9) {
    c9_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==10) {
    c10_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==11) {
    c11_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==12) {
    c12_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==13) {
    c13_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==14) {
    c14_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==15) {
    c15_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==25) {
    c25_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==26) {
    c26_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==27) {
    c27_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==28) {
    c28_Model_justmodel_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_Model_justmodel_process_check_sum_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1974508652U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1575841360U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3725562772U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(781497288U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1033341586U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2798499483U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(268059366U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(950091890U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c1_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c2_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c3_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c4_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c5_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c6_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 7:
        {
          extern void sf_c7_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c7_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 8:
        {
          extern void sf_c8_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c8_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 9:
        {
          extern void sf_c9_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c9_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 10:
        {
          extern void sf_c10_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c10_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 11:
        {
          extern void sf_c11_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c11_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 12:
        {
          extern void sf_c12_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c12_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 13:
        {
          extern void sf_c13_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c13_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 14:
        {
          extern void sf_c14_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c14_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 15:
        {
          extern void sf_c15_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c15_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 25:
        {
          extern void sf_c25_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c25_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 26:
        {
          extern void sf_c26_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c26_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 27:
        {
          extern void sf_c27_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c27_Model_justmodel_get_check_sum(plhs);
          break;
        }

       case 28:
        {
          extern void sf_c28_Model_justmodel_get_check_sum(mxArray *plhs[]);
          sf_c28_Model_justmodel_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3564696471U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(678668628U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1090454852U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3896867807U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1863942934U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(974936334U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3520068432U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(960075490U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_Model_justmodel_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "t88tWvHfccsSlIYyLDrSIF") == 0) {
          extern mxArray *sf_c1_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c1_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "pEoBLkO5VnHf2a36B3DZQF") == 0) {
          extern mxArray *sf_c2_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c2_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "fXrmObJf0FMIZRxStXar8G") == 0) {
          extern mxArray *sf_c3_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c3_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "ASu1O1s8cmc6pjtKKrL18F") == 0) {
          extern mxArray *sf_c4_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c4_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "JaH9rLY29wusECyBipCU1B") == 0) {
          extern mxArray *sf_c5_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c5_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "VRXtcKU3IwjgHa6GKW3ipE") == 0) {
          extern mxArray *sf_c6_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c6_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "s3Z21eWbdMKukxXIrWcsq") == 0) {
          extern mxArray *sf_c7_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c7_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 8:
      {
        if (strcmp(aiChksum, "qNiRYuDEYVYKaSj5LEmwtC") == 0) {
          extern mxArray *sf_c8_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c8_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 9:
      {
        if (strcmp(aiChksum, "PScgNGCMFVfnekBdZR2I7C") == 0) {
          extern mxArray *sf_c9_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c9_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 10:
      {
        if (strcmp(aiChksum, "G64yU3zmbafFuwxSzxbspC") == 0) {
          extern mxArray *sf_c10_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c10_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 11:
      {
        if (strcmp(aiChksum, "q2rkYF4vo2flRZ05g7L5mG") == 0) {
          extern mxArray *sf_c11_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c11_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 12:
      {
        if (strcmp(aiChksum, "xfSnGuNZBLRs5sdk0BCC1") == 0) {
          extern mxArray *sf_c12_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c12_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 13:
      {
        if (strcmp(aiChksum, "VXZlspe2d7KKElQK7f33OD") == 0) {
          extern mxArray *sf_c13_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c13_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 14:
      {
        if (strcmp(aiChksum, "H08gUXOQ4cGie6wRMFqGLH") == 0) {
          extern mxArray *sf_c14_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c14_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 15:
      {
        if (strcmp(aiChksum, "W1zcanKW732uWktz1OxkBC") == 0) {
          extern mxArray *sf_c15_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c15_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 25:
      {
        if (strcmp(aiChksum, "uV0TFr6ZhSiO1vejw3TNqH") == 0) {
          extern mxArray *sf_c25_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c25_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 26:
      {
        if (strcmp(aiChksum, "0ctf0Y5i7MK8fbaYTDLzOF") == 0) {
          extern mxArray *sf_c26_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c26_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 27:
      {
        if (strcmp(aiChksum, "22Y6r9N2L5gPKVN7ifxNPH") == 0) {
          extern mxArray *sf_c27_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c27_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 28:
      {
        if (strcmp(aiChksum, "SSTmexydsysmTRJLoEOgJG") == 0) {
          extern mxArray *sf_c28_Model_justmodel_get_autoinheritance_info(void);
          plhs[0] = sf_c28_Model_justmodel_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_Model_justmodel_get_eml_resolved_functions_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray
          *sf_c1_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray
          *sf_c4_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray
          *sf_c5_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray
          *sf_c6_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray
          *sf_c7_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 8:
      {
        extern const mxArray
          *sf_c8_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c8_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 9:
      {
        extern const mxArray
          *sf_c9_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c9_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 10:
      {
        extern const mxArray
          *sf_c10_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c10_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 11:
      {
        extern const mxArray
          *sf_c11_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c11_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 12:
      {
        extern const mxArray
          *sf_c12_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c12_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 13:
      {
        extern const mxArray
          *sf_c13_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c13_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 14:
      {
        extern const mxArray
          *sf_c14_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c14_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 15:
      {
        extern const mxArray
          *sf_c15_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c15_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 25:
      {
        extern const mxArray
          *sf_c25_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c25_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 26:
      {
        extern const mxArray
          *sf_c26_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c26_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 27:
      {
        extern const mxArray
          *sf_c27_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c27_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 28:
      {
        extern const mxArray
          *sf_c28_Model_justmodel_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c28_Model_justmodel_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_Model_justmodel_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "vz6u7ezXroZWt3jjRgunP") == 0) {
          extern mxArray *sf_c1_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c1_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "WZR3HGy77jnGmWyD2kcflF") == 0) {
          extern mxArray *sf_c2_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c2_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "kGNly1Tx70M0SgFxz3EIID") == 0) {
          extern mxArray *sf_c3_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c3_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "8FMnQhU6Uzl3cGuIyQtDkH") == 0) {
          extern mxArray *sf_c4_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c4_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "Iaa4DHsWrE0ZGmOc9BvrfG") == 0) {
          extern mxArray *sf_c5_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c5_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "YiYKYViaUpsTRqcXREms9F") == 0) {
          extern mxArray *sf_c6_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c6_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "wLIU1FNcGVbOKxcd4UcwXB") == 0) {
          extern mxArray *sf_c7_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c7_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 8:
      {
        if (strcmp(tpChksum, "maaAR6gSKSqM87jJ4EXSBC") == 0) {
          extern mxArray *sf_c8_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c8_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 9:
      {
        if (strcmp(tpChksum, "c10O9G8JXfEj3YBB8w0Yn") == 0) {
          extern mxArray *sf_c9_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c9_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 10:
      {
        if (strcmp(tpChksum, "SLGExYOQbgHwOhnjPAxnnH") == 0) {
          extern mxArray *sf_c10_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c10_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 11:
      {
        if (strcmp(tpChksum, "z8mkkVoYF6pMdh9e2HaAiE") == 0) {
          extern mxArray *sf_c11_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c11_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 12:
      {
        if (strcmp(tpChksum, "fTlsYWM82OaAJSaTSEpkwF") == 0) {
          extern mxArray *sf_c12_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c12_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 13:
      {
        if (strcmp(tpChksum, "Ihgg7JyJ6LU2bxA358za1G") == 0) {
          extern mxArray *sf_c13_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c13_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 14:
      {
        if (strcmp(tpChksum, "aE4uNmGkbqfeM8ew8jZHyB") == 0) {
          extern mxArray *sf_c14_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c14_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 15:
      {
        if (strcmp(tpChksum, "o3yVXKn1Vks8genuOh7YJE") == 0) {
          extern mxArray *sf_c15_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c15_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 25:
      {
        if (strcmp(tpChksum, "0zMw5LFa0bWy2VJ2QgwK1E") == 0) {
          extern mxArray *sf_c25_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c25_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 26:
      {
        if (strcmp(tpChksum, "UALrpIdQJ4OdOD8IeOcDnD") == 0) {
          extern mxArray *sf_c26_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c26_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 27:
      {
        if (strcmp(tpChksum, "EADHIkZDZp84G7FG02hUSF") == 0) {
          extern mxArray *sf_c27_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c27_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     case 28:
      {
        if (strcmp(tpChksum, "je2Gmq1bf80hBBypf9zjpB") == 0) {
          extern mxArray *sf_c28_Model_justmodel_third_party_uses_info(void);
          plhs[0] = sf_c28_Model_justmodel_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void Model_justmodel_debug_initialize(struct SfDebugInstanceStruct*
  debugInstance)
{
  _Model_justmodelMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "Model_justmodel","sfun",0,19,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _Model_justmodelMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _Model_justmodelMachineNumber_,0);
}

void Model_justmodel_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_Model_justmodel_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("Model_justmodel",
      "Model_justmodel");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_Model_justmodel_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
