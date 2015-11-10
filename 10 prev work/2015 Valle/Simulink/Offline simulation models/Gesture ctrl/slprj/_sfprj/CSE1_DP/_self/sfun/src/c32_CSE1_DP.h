#ifndef __c32_CSE1_DP_h__
#define __c32_CSE1_DP_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc32_CSE1_DPInstanceStruct
#define typedef_SFc32_CSE1_DPInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c32_sfEvent;
  boolean_T c32_isStable;
  boolean_T c32_doneDoubleBufferReInit;
  uint8_T c32_is_active_c32_CSE1_DP;
} SFc32_CSE1_DPInstanceStruct;

#endif                                 /*typedef_SFc32_CSE1_DPInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c32_CSE1_DP_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c32_CSE1_DP_get_check_sum(mxArray *plhs[]);
extern void c32_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
