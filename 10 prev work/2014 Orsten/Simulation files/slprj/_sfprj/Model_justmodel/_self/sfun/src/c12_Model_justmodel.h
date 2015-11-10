#ifndef __c12_Model_justmodel_h__
#define __c12_Model_justmodel_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_c12_ResolvedFunctionInfo
#define typedef_c12_ResolvedFunctionInfo

typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c12_ResolvedFunctionInfo;

#endif                                 /*typedef_c12_ResolvedFunctionInfo*/

#ifndef typedef_SFc12_Model_justmodelInstanceStruct
#define typedef_SFc12_Model_justmodelInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c12_sfEvent;
  boolean_T c12_isStable;
  boolean_T c12_doneDoubleBufferReInit;
  uint8_T c12_is_active_c12_Model_justmodel;
  uint32_T c12_method;
  boolean_T c12_method_not_empty;
  uint32_T c12_state;
  boolean_T c12_state_not_empty;
  uint32_T c12_b_state[2];
  boolean_T c12_b_state_not_empty;
  uint32_T c12_c_state[625];
  boolean_T c12_c_state_not_empty;
} SFc12_Model_justmodelInstanceStruct;

#endif                                 /*typedef_SFc12_Model_justmodelInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c12_Model_justmodel_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c12_Model_justmodel_get_check_sum(mxArray *plhs[]);
extern void c12_Model_justmodel_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
