#ifndef __c15_HIL_model_error_h__
#define __c15_HIL_model_error_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc15_HIL_model_errorInstanceStruct
#define typedef_SFc15_HIL_model_errorInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c15_sfEvent;
  boolean_T c15_isStable;
  boolean_T c15_doneDoubleBufferReInit;
  uint8_T c15_is_active_c15_HIL_model_error;
} SFc15_HIL_model_errorInstanceStruct;

#endif                                 /*typedef_SFc15_HIL_model_errorInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c15_HIL_model_error_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c15_HIL_model_error_get_check_sum(mxArray *plhs[]);
extern void c15_HIL_model_error_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
