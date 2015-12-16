/* Include files */

#include "ctrl_student_sfun.h"
#include "ctrl_student_sfun_debug_macros.h"
#include "c1_ctrl_student.h"
#include "c2_ctrl_student.h"
#include "c5_ctrl_student.h"
#include "c12_ctrl_student.h"
#include "c13_ctrl_student.h"
#include "c14_ctrl_student.h"
#include "c15_ctrl_student.h"
#include "c19_ctrl_student.h"
#include "c29_ctrl_student.h"
#include "c30_ctrl_student.h"
#include "c31_ctrl_student.h"
#include "c32_ctrl_student.h"
#include "c33_ctrl_student.h"
#include "c34_ctrl_student.h"
#include "c35_ctrl_student.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _ctrl_studentMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void ctrl_student_initializer(void)
{
}

void ctrl_student_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_ctrl_student_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==12) {
    c12_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==13) {
    c13_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==14) {
    c14_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==15) {
    c15_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==19) {
    c19_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==29) {
    c29_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==30) {
    c30_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==31) {
    c31_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==32) {
    c32_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==33) {
    c33_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==34) {
    c34_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==35) {
    c35_ctrl_student_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_ctrl_student_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3640938945U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3064787207U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(393088274U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2879323004U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2899623873U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4292373778U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1767616009U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2436088827U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c1_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c2_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c5_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 12:
        {
          extern void sf_c12_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c12_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 13:
        {
          extern void sf_c13_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c13_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 14:
        {
          extern void sf_c14_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c14_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 15:
        {
          extern void sf_c15_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c15_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 19:
        {
          extern void sf_c19_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c19_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 29:
        {
          extern void sf_c29_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c29_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 30:
        {
          extern void sf_c30_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c30_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 31:
        {
          extern void sf_c31_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c31_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 32:
        {
          extern void sf_c32_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c32_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 33:
        {
          extern void sf_c33_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c33_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 34:
        {
          extern void sf_c34_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c34_ctrl_student_get_check_sum(plhs);
          break;
        }

       case 35:
        {
          extern void sf_c35_ctrl_student_get_check_sum(mxArray *plhs[]);
          sf_c35_ctrl_student_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3031367619U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4001028638U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3978939492U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(838979348U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1580962530U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1069624385U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3001012515U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(689729755U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_ctrl_student_autoinheritance_info( int nlhs, mxArray * plhs[],
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
        if (strcmp(aiChksum, "atRTyUbczfYroxA2sX2uHE") == 0) {
          extern mxArray *sf_c1_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c1_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "twZ9xU73SDq5w5lBAf9Bv") == 0) {
          extern mxArray *sf_c2_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c2_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "jdGrjqJwghmegXjmyuldvF") == 0) {
          extern mxArray *sf_c5_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c5_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 12:
      {
        if (strcmp(aiChksum, "K4XK4stm5HItb464S4fdKE") == 0) {
          extern mxArray *sf_c12_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c12_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 13:
      {
        if (strcmp(aiChksum, "HcHb7KfjZDcI8Ssh66im5") == 0) {
          extern mxArray *sf_c13_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c13_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 14:
      {
        if (strcmp(aiChksum, "dQ120WfwDXKCgTNXf5nvoH") == 0) {
          extern mxArray *sf_c14_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c14_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 15:
      {
        if (strcmp(aiChksum, "Xq3QrWc2oXaP0PqytUUyDG") == 0) {
          extern mxArray *sf_c15_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c15_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 19:
      {
        if (strcmp(aiChksum, "ZxJonMXo0lEr8kq3DUBNmC") == 0) {
          extern mxArray *sf_c19_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c19_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 29:
      {
        if (strcmp(aiChksum, "O10M0c60XMpoxHQIK1PIeD") == 0) {
          extern mxArray *sf_c29_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c29_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 30:
      {
        if (strcmp(aiChksum, "Mj7CHw0385bxYKt1BP0rlF") == 0) {
          extern mxArray *sf_c30_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c30_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 31:
      {
        if (strcmp(aiChksum, "L58HAWj85A5HxbKK3DXH8G") == 0) {
          extern mxArray *sf_c31_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c31_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 32:
      {
        if (strcmp(aiChksum, "IjnQftEpmhxGdlGAAuBHSF") == 0) {
          extern mxArray *sf_c32_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c32_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 33:
      {
        if (strcmp(aiChksum, "hUUU8EuiWWXxsdTY3uHGvD") == 0) {
          extern mxArray *sf_c33_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c33_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 34:
      {
        if (strcmp(aiChksum, "WrXO8sSmra0b642F8IO1yG") == 0) {
          extern mxArray *sf_c34_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c34_ctrl_student_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 35:
      {
        if (strcmp(aiChksum, "UmKAF1GE7xoIxSLZalYVt") == 0) {
          extern mxArray *sf_c35_ctrl_student_get_autoinheritance_info(void);
          plhs[0] = sf_c35_ctrl_student_get_autoinheritance_info();
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

unsigned int sf_ctrl_student_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
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
        extern const mxArray *sf_c1_ctrl_student_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_ctrl_student_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_ctrl_student_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 12:
      {
        extern const mxArray
          *sf_c12_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c12_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 13:
      {
        extern const mxArray
          *sf_c13_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c13_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 14:
      {
        extern const mxArray
          *sf_c14_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c14_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 15:
      {
        extern const mxArray
          *sf_c15_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c15_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 19:
      {
        extern const mxArray
          *sf_c19_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c19_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 29:
      {
        extern const mxArray
          *sf_c29_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c29_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 30:
      {
        extern const mxArray
          *sf_c30_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c30_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 31:
      {
        extern const mxArray
          *sf_c31_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c31_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 32:
      {
        extern const mxArray
          *sf_c32_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c32_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 33:
      {
        extern const mxArray
          *sf_c33_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c33_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 34:
      {
        extern const mxArray
          *sf_c34_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c34_ctrl_student_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 35:
      {
        extern const mxArray
          *sf_c35_ctrl_student_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c35_ctrl_student_get_eml_resolved_functions_info();
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

unsigned int sf_ctrl_student_third_party_uses_info( int nlhs, mxArray * plhs[],
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
        if (strcmp(tpChksum, "WLfuUcp3GrB4bo00fWAiID") == 0) {
          extern mxArray *sf_c1_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c1_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "q1j9ZtAb7K8XPjJwWLG9qG") == 0) {
          extern mxArray *sf_c2_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c2_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "P0jPPb1SnH82d3mJNphXnG") == 0) {
          extern mxArray *sf_c5_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c5_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 12:
      {
        if (strcmp(tpChksum, "hhO60cW3dFdG8jxKxZ0McE") == 0) {
          extern mxArray *sf_c12_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c12_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 13:
      {
        if (strcmp(tpChksum, "TFjENdXaDE0vhjgNr3hyEF") == 0) {
          extern mxArray *sf_c13_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c13_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 14:
      {
        if (strcmp(tpChksum, "jiyW8ppNpEd0ro5iNe9yF") == 0) {
          extern mxArray *sf_c14_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c14_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 15:
      {
        if (strcmp(tpChksum, "1p2JWRIdTHsdd8tDJSAE8E") == 0) {
          extern mxArray *sf_c15_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c15_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 19:
      {
        if (strcmp(tpChksum, "NHJ7r9elp6jyZ6hMsRm63F") == 0) {
          extern mxArray *sf_c19_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c19_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 29:
      {
        if (strcmp(tpChksum, "oR4pF6vc63ECTOb3l0SIAE") == 0) {
          extern mxArray *sf_c29_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c29_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 30:
      {
        if (strcmp(tpChksum, "26DfMYsRDbVTvZQ2QugyyF") == 0) {
          extern mxArray *sf_c30_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c30_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 31:
      {
        if (strcmp(tpChksum, "00mOJNzb73k8cqQBzVT2a") == 0) {
          extern mxArray *sf_c31_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c31_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 32:
      {
        if (strcmp(tpChksum, "U80EMSOKQPEDDHn8Kd4xcD") == 0) {
          extern mxArray *sf_c32_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c32_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 33:
      {
        if (strcmp(tpChksum, "wULOMuSiYgXO10AFcWXfzF") == 0) {
          extern mxArray *sf_c33_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c33_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 34:
      {
        if (strcmp(tpChksum, "piVJe9Rzy8Nt0gZdvFZjEH") == 0) {
          extern mxArray *sf_c34_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c34_ctrl_student_third_party_uses_info();
          break;
        }
      }

     case 35:
      {
        if (strcmp(tpChksum, "2WHkTcLHLrAwNcDo2iYm") == 0) {
          extern mxArray *sf_c35_ctrl_student_third_party_uses_info(void);
          plhs[0] = sf_c35_ctrl_student_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_ctrl_student_updateBuildInfo_args_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "WLfuUcp3GrB4bo00fWAiID") == 0) {
          extern mxArray *sf_c1_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "q1j9ZtAb7K8XPjJwWLG9qG") == 0) {
          extern mxArray *sf_c2_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "P0jPPb1SnH82d3mJNphXnG") == 0) {
          extern mxArray *sf_c5_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 12:
      {
        if (strcmp(tpChksum, "hhO60cW3dFdG8jxKxZ0McE") == 0) {
          extern mxArray *sf_c12_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c12_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 13:
      {
        if (strcmp(tpChksum, "TFjENdXaDE0vhjgNr3hyEF") == 0) {
          extern mxArray *sf_c13_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c13_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 14:
      {
        if (strcmp(tpChksum, "jiyW8ppNpEd0ro5iNe9yF") == 0) {
          extern mxArray *sf_c14_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c14_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 15:
      {
        if (strcmp(tpChksum, "1p2JWRIdTHsdd8tDJSAE8E") == 0) {
          extern mxArray *sf_c15_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c15_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 19:
      {
        if (strcmp(tpChksum, "NHJ7r9elp6jyZ6hMsRm63F") == 0) {
          extern mxArray *sf_c19_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c19_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 29:
      {
        if (strcmp(tpChksum, "oR4pF6vc63ECTOb3l0SIAE") == 0) {
          extern mxArray *sf_c29_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c29_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 30:
      {
        if (strcmp(tpChksum, "26DfMYsRDbVTvZQ2QugyyF") == 0) {
          extern mxArray *sf_c30_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c30_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 31:
      {
        if (strcmp(tpChksum, "00mOJNzb73k8cqQBzVT2a") == 0) {
          extern mxArray *sf_c31_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c31_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 32:
      {
        if (strcmp(tpChksum, "U80EMSOKQPEDDHn8Kd4xcD") == 0) {
          extern mxArray *sf_c32_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c32_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 33:
      {
        if (strcmp(tpChksum, "wULOMuSiYgXO10AFcWXfzF") == 0) {
          extern mxArray *sf_c33_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c33_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 34:
      {
        if (strcmp(tpChksum, "piVJe9Rzy8Nt0gZdvFZjEH") == 0) {
          extern mxArray *sf_c34_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c34_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     case 35:
      {
        if (strcmp(tpChksum, "2WHkTcLHLrAwNcDo2iYm") == 0) {
          extern mxArray *sf_c35_ctrl_student_updateBuildInfo_args_info(void);
          plhs[0] = sf_c35_ctrl_student_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void ctrl_student_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _ctrl_studentMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "ctrl_student","sfun",0,15,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _ctrl_studentMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_ctrl_studentMachineNumber_,
    0);
}

void ctrl_student_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_ctrl_student_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("ctrl_student",
      "ctrl_student");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_ctrl_student_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
