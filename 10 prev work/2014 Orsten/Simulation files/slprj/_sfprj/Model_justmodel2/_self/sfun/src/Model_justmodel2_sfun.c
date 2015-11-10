/* Include files */

#include "Model_justmodel2_sfun.h"
#include "Model_justmodel2_sfun_debug_macros.h"
#include "c1_Model_justmodel2.h"
#include "c2_Model_justmodel2.h"
#include "c3_Model_justmodel2.h"
#include "c8_Model_justmodel2.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _Model_justmodel2MachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void Model_justmodel2_initializer(void)
{
}

void Model_justmodel2_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_Model_justmodel2_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_Model_justmodel2_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_Model_justmodel2_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_Model_justmodel2_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==8) {
    c8_Model_justmodel2_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_Model_justmodel2_process_check_sum_call( int nlhs, mxArray *
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2969923390U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1433044363U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4180563U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2865633560U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3278277932U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2236519819U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2491568841U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3044251375U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_Model_justmodel2_get_check_sum(mxArray *plhs[]);
          sf_c1_Model_justmodel2_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_Model_justmodel2_get_check_sum(mxArray *plhs[]);
          sf_c2_Model_justmodel2_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_Model_justmodel2_get_check_sum(mxArray *plhs[]);
          sf_c3_Model_justmodel2_get_check_sum(plhs);
          break;
        }

       case 8:
        {
          extern void sf_c8_Model_justmodel2_get_check_sum(mxArray *plhs[]);
          sf_c8_Model_justmodel2_get_check_sum(plhs);
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
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4245133404U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1094971351U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1673388236U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1410553962U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_Model_justmodel2_autoinheritance_info( int nlhs, mxArray * plhs[],
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
        if (strcmp(aiChksum, "zNEwrNzfDZCAwqAfokcY1G") == 0) {
          extern mxArray *sf_c1_Model_justmodel2_get_autoinheritance_info(void);
          plhs[0] = sf_c1_Model_justmodel2_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "q2rkYF4vo2flRZ05g7L5mG") == 0) {
          extern mxArray *sf_c2_Model_justmodel2_get_autoinheritance_info(void);
          plhs[0] = sf_c2_Model_justmodel2_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "fXrmObJf0FMIZRxStXar8G") == 0) {
          extern mxArray *sf_c3_Model_justmodel2_get_autoinheritance_info(void);
          plhs[0] = sf_c3_Model_justmodel2_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 8:
      {
        if (strcmp(aiChksum, "iN2enFToX3SWwyCHGJEPiD") == 0) {
          extern mxArray *sf_c8_Model_justmodel2_get_autoinheritance_info(void);
          plhs[0] = sf_c8_Model_justmodel2_get_autoinheritance_info();
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

unsigned int sf_Model_justmodel2_get_eml_resolved_functions_info( int nlhs,
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
          *sf_c1_Model_justmodel2_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_Model_justmodel2_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_Model_justmodel2_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_Model_justmodel2_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_Model_justmodel2_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_Model_justmodel2_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 8:
      {
        extern const mxArray
          *sf_c8_Model_justmodel2_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c8_Model_justmodel2_get_eml_resolved_functions_info();
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

unsigned int sf_Model_justmodel2_third_party_uses_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
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
        if (strcmp(tpChksum, "J7s4hqktskCVdw8HzjTWZ") == 0) {
          extern mxArray *sf_c1_Model_justmodel2_third_party_uses_info(void);
          plhs[0] = sf_c1_Model_justmodel2_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "z8mkkVoYF6pMdh9e2HaAiE") == 0) {
          extern mxArray *sf_c2_Model_justmodel2_third_party_uses_info(void);
          plhs[0] = sf_c2_Model_justmodel2_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "kGNly1Tx70M0SgFxz3EIID") == 0) {
          extern mxArray *sf_c3_Model_justmodel2_third_party_uses_info(void);
          plhs[0] = sf_c3_Model_justmodel2_third_party_uses_info();
          break;
        }
      }

     case 8:
      {
        if (strcmp(tpChksum, "NIIbpNADyF6w5W3Wbnw1T") == 0) {
          extern mxArray *sf_c8_Model_justmodel2_third_party_uses_info(void);
          plhs[0] = sf_c8_Model_justmodel2_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void Model_justmodel2_debug_initialize(struct SfDebugInstanceStruct*
  debugInstance)
{
  _Model_justmodel2MachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "Model_justmodel2","sfun",0,4,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _Model_justmodel2MachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _Model_justmodel2MachineNumber_,0);
}

void Model_justmodel2_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_Model_justmodel2_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info(
      "Model_justmodel2", "Model_justmodel2");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_Model_justmodel2_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
