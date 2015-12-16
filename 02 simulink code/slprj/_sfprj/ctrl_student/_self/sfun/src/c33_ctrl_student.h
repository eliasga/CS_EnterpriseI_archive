#ifndef __c33_ctrl_student_h__
#define __c33_ctrl_student_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc33_ctrl_studentInstanceStruct
#define typedef_SFc33_ctrl_studentInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c33_sfEvent;
  boolean_T c33_isStable;
  boolean_T c33_doneDoubleBufferReInit;
  uint8_T c33_is_active_c33_ctrl_student;
} SFc33_ctrl_studentInstanceStruct;

#endif                                 /*typedef_SFc33_ctrl_studentInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c33_ctrl_student_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c33_ctrl_student_get_check_sum(mxArray *plhs[]);
extern void c33_ctrl_student_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
