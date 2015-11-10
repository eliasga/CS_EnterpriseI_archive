/* Include files */

#include "HIL_model_experiments1_sfun.h"
#include "HIL_model_experiments1_sfun_debug_macros.h"
#include "c1_HIL_model_experiments1.h"
#include "c2_HIL_model_experiments1.h"
#include "c3_HIL_model_experiments1.h"
#include "c4_HIL_model_experiments1.h"
#include "c5_HIL_model_experiments1.h"
#include "c6_HIL_model_experiments1.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _HIL_model_experiments1MachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void HIL_model_experiments1_initializer(void)
{
}

void HIL_model_experiments1_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_HIL_model_experiments1_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_HIL_model_experiments1_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_HIL_model_experiments1_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_HIL_model_experiments1_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_HIL_model_experiments1_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_HIL_model_experiments1_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_HIL_model_experiments1_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_HIL_model_experiments1_process_check_sum_call( int nlhs, mxArray
  * plhs[], int nrhs, const mxArray * prhs[] )
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(170915212U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(601903572U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4011554710U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1119868014U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1188377669U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1025168642U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2837815657U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1536637523U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_HIL_model_experiments1_get_check_sum(mxArray *plhs[]);
          sf_c1_HIL_model_experiments1_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_HIL_model_experiments1_get_check_sum(mxArray *plhs[]);
          sf_c2_HIL_model_experiments1_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_HIL_model_experiments1_get_check_sum(mxArray *plhs[]);
          sf_c3_HIL_model_experiments1_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_HIL_model_experiments1_get_check_sum(mxArray *plhs[]);
          sf_c4_HIL_model_experiments1_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_HIL_model_experiments1_get_check_sum(mxArray *plhs[]);
          sf_c5_HIL_model_experiments1_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_HIL_model_experiments1_get_check_sum(mxArray *plhs[]);
          sf_c6_HIL_model_experiments1_get_check_sum(plhs);
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
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1904238285U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3133953068U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4275152630U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2367375247U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_HIL_model_experiments1_autoinheritance_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
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
        if (strcmp(aiChksum, "26QjjNalRMX5fmoznzLGrB") == 0) {
          extern mxArray *sf_c1_HIL_model_experiments1_get_autoinheritance_info
            (void);
          plhs[0] = sf_c1_HIL_model_experiments1_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "q2rkYF4vo2flRZ05g7L5mG") == 0) {
          extern mxArray *sf_c2_HIL_model_experiments1_get_autoinheritance_info
            (void);
          plhs[0] = sf_c2_HIL_model_experiments1_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "iN2enFToX3SWwyCHGJEPiD") == 0) {
          extern mxArray *sf_c3_HIL_model_experiments1_get_autoinheritance_info
            (void);
          plhs[0] = sf_c3_HIL_model_experiments1_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "u8DodBcfg6Fycr1oCgSynD") == 0) {
          extern mxArray *sf_c4_HIL_model_experiments1_get_autoinheritance_info
            (void);
          plhs[0] = sf_c4_HIL_model_experiments1_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "mLUCAsKQO1Jrkerz4va37C") == 0) {
          extern mxArray *sf_c5_HIL_model_experiments1_get_autoinheritance_info
            (void);
          plhs[0] = sf_c5_HIL_model_experiments1_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "THnJ6GB5zocqsODhF5NAdG") == 0) {
          extern mxArray *sf_c6_HIL_model_experiments1_get_autoinheritance_info
            (void);
          plhs[0] = sf_c6_HIL_model_experiments1_get_autoinheritance_info();
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

unsigned int sf_HIL_model_experiments1_get_eml_resolved_functions_info( int nlhs,
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
          *sf_c1_HIL_model_experiments1_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_HIL_model_experiments1_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_HIL_model_experiments1_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_HIL_model_experiments1_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_HIL_model_experiments1_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_HIL_model_experiments1_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray
          *sf_c4_HIL_model_experiments1_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_HIL_model_experiments1_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray
          *sf_c5_HIL_model_experiments1_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_HIL_model_experiments1_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray
          *sf_c6_HIL_model_experiments1_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_HIL_model_experiments1_get_eml_resolved_functions_info();
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

unsigned int sf_HIL_model_experiments1_third_party_uses_info( int nlhs, mxArray *
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
        if (strcmp(tpChksum, "5d1d5sSeMbUSSINPhhruBG") == 0) {
          extern mxArray *sf_c1_HIL_model_experiments1_third_party_uses_info
            (void);
          plhs[0] = sf_c1_HIL_model_experiments1_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "z8mkkVoYF6pMdh9e2HaAiE") == 0) {
          extern mxArray *sf_c2_HIL_model_experiments1_third_party_uses_info
            (void);
          plhs[0] = sf_c2_HIL_model_experiments1_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "NIIbpNADyF6w5W3Wbnw1T") == 0) {
          extern mxArray *sf_c3_HIL_model_experiments1_third_party_uses_info
            (void);
          plhs[0] = sf_c3_HIL_model_experiments1_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "Yx149Zt7ofzbrArignrUN") == 0) {
          extern mxArray *sf_c4_HIL_model_experiments1_third_party_uses_info
            (void);
          plhs[0] = sf_c4_HIL_model_experiments1_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "2mWZCGJzRtXjkDmrv5cJOB") == 0) {
          extern mxArray *sf_c5_HIL_model_experiments1_third_party_uses_info
            (void);
          plhs[0] = sf_c5_HIL_model_experiments1_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "AOgk8sFoV9BDzxotdW6qaG") == 0) {
          extern mxArray *sf_c6_HIL_model_experiments1_third_party_uses_info
            (void);
          plhs[0] = sf_c6_HIL_model_experiments1_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void HIL_model_experiments1_debug_initialize(struct SfDebugInstanceStruct*
  debugInstance)
{
  _HIL_model_experiments1MachineNumber_ = sf_debug_initialize_machine
    (debugInstance,"HIL_model_experiments1","sfun",0,6,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _HIL_model_experiments1MachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _HIL_model_experiments1MachineNumber_,0);
}

void HIL_model_experiments1_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_HIL_model_experiments1_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info(
      "HIL_model_experiments1", "HIL_model_experiments1");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_HIL_model_experiments1_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
