/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_Oculus_gesture_sfun.h"
#include "c28_CSE1_Oculus_gesture.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "CSE1_Oculus_gesture_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c28_debug_family_names[4] = { "nargin", "nargout", "u", "y"
};

/* Function Declarations */
static void initialize_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void initialize_params_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void enable_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void disable_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void c28_update_debugger_state_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void set_sim_state_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance, const mxArray *c28_st);
static void finalize_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void sf_gateway_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void initSimStructsc28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c28_machineNumber, uint32_T
  c28_chartNumber, uint32_T c28_instanceNumber);
static const mxArray *c28_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData);
static void c28_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_y, const char_T *c28_identifier, real_T
  c28_b_y[3]);
static void c28_b_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId,
  real_T c28_y[3]);
static void c28_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData);
static const mxArray *c28_b_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData);
static const mxArray *c28_c_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData);
static real_T c28_c_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId);
static void c28_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData);
static const mxArray *c28_d_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData);
static int32_T c28_d_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId);
static void c28_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData);
static uint8_T c28_e_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_b_is_active_c28_CSE1_Oculus_gesture, const
  char_T *c28_identifier);
static uint8_T c28_f_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId);
static void init_dsm_address_info(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  chartInstance->c28_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c28_is_active_c28_CSE1_Oculus_gesture = 0U;
}

static void initialize_params_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c28_update_debugger_state_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  const mxArray *c28_st;
  const mxArray *c28_y = NULL;
  int32_T c28_i0;
  real_T c28_u[3];
  const mxArray *c28_b_y = NULL;
  uint8_T c28_hoistedGlobal;
  uint8_T c28_b_u;
  const mxArray *c28_c_y = NULL;
  real_T (*c28_d_y)[3];
  c28_d_y = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c28_st = NULL;
  c28_st = NULL;
  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_createcellmatrix(2, 1), false);
  for (c28_i0 = 0; c28_i0 < 3; c28_i0++) {
    c28_u[c28_i0] = (*c28_d_y)[c28_i0];
  }

  c28_b_y = NULL;
  sf_mex_assign(&c28_b_y, sf_mex_create("y", c28_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c28_y, 0, c28_b_y);
  c28_hoistedGlobal = chartInstance->c28_is_active_c28_CSE1_Oculus_gesture;
  c28_b_u = c28_hoistedGlobal;
  c28_c_y = NULL;
  sf_mex_assign(&c28_c_y, sf_mex_create("y", &c28_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c28_y, 1, c28_c_y);
  sf_mex_assign(&c28_st, c28_y, false);
  return c28_st;
}

static void set_sim_state_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance, const mxArray *c28_st)
{
  const mxArray *c28_u;
  real_T c28_dv0[3];
  int32_T c28_i1;
  real_T (*c28_y)[3];
  c28_y = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c28_doneDoubleBufferReInit = true;
  c28_u = sf_mex_dup(c28_st);
  c28_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c28_u, 0)), "y",
                       c28_dv0);
  for (c28_i1 = 0; c28_i1 < 3; c28_i1++) {
    (*c28_y)[c28_i1] = c28_dv0[c28_i1];
  }

  chartInstance->c28_is_active_c28_CSE1_Oculus_gesture = c28_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c28_u, 1)),
     "is_active_c28_CSE1_Oculus_gesture");
  sf_mex_destroy(&c28_u);
  c28_update_debugger_state_c28_CSE1_Oculus_gesture(chartInstance);
  sf_mex_destroy(&c28_st);
}

static void finalize_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  int32_T c28_i2;
  int32_T c28_i3;
  real_T c28_u[9];
  uint32_T c28_debug_family_var_map[4];
  real_T c28_nargin = 1.0;
  real_T c28_nargout = 1.0;
  real_T c28_y[3];
  real_T c28_b_u[3];
  int32_T c28_i4;
  int32_T c28_i5;
  int32_T c28_i6;
  real_T (*c28_b_y)[3];
  real_T (*c28_c_u)[9];
  c28_b_y = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c28_c_u = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 19U, chartInstance->c28_sfEvent);
  for (c28_i2 = 0; c28_i2 < 9; c28_i2++) {
    _SFD_DATA_RANGE_CHECK((*c28_c_u)[c28_i2], 0U);
  }

  chartInstance->c28_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 19U, chartInstance->c28_sfEvent);
  for (c28_i3 = 0; c28_i3 < 9; c28_i3++) {
    c28_u[c28_i3] = (*c28_c_u)[c28_i3];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c28_debug_family_names,
    c28_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c28_nargin, 0U, c28_c_sf_marshallOut,
    c28_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c28_nargout, 1U, c28_c_sf_marshallOut,
    c28_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c28_u, 2U, c28_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c28_y, 3U, c28_sf_marshallOut,
    c28_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 4);
  c28_b_u[0] = c28_u[0];
  c28_b_u[1] = c28_u[4];
  c28_b_u[2] = c28_u[8];
  for (c28_i4 = 0; c28_i4 < 3; c28_i4++) {
    c28_y[c28_i4] = c28_b_u[c28_i4];
  }

  _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c28_i5 = 0; c28_i5 < 3; c28_i5++) {
    (*c28_b_y)[c28_i5] = c28_y[c28_i5];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c28_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_Oculus_gestureMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c28_i6 = 0; c28_i6 < 3; c28_i6++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_y)[c28_i6], 1U);
  }
}

static void initSimStructsc28_CSE1_Oculus_gesture
  (SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c28_machineNumber, uint32_T
  c28_chartNumber, uint32_T c28_instanceNumber)
{
  (void)c28_machineNumber;
  (void)c28_chartNumber;
  (void)c28_instanceNumber;
}

static const mxArray *c28_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData)
{
  const mxArray *c28_mxArrayOutData = NULL;
  int32_T c28_i7;
  real_T c28_b_inData[3];
  int32_T c28_i8;
  real_T c28_u[3];
  const mxArray *c28_y = NULL;
  SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c28_mxArrayOutData = NULL;
  for (c28_i7 = 0; c28_i7 < 3; c28_i7++) {
    c28_b_inData[c28_i7] = (*(real_T (*)[3])c28_inData)[c28_i7];
  }

  for (c28_i8 = 0; c28_i8 < 3; c28_i8++) {
    c28_u[c28_i8] = c28_b_inData[c28_i8];
  }

  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_create("y", c28_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c28_mxArrayOutData, c28_y, false);
  return c28_mxArrayOutData;
}

static void c28_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_y, const char_T *c28_identifier, real_T
  c28_b_y[3])
{
  emlrtMsgIdentifier c28_thisId;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c28_y), &c28_thisId, c28_b_y);
  sf_mex_destroy(&c28_y);
}

static void c28_b_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId,
  real_T c28_y[3])
{
  real_T c28_dv1[3];
  int32_T c28_i9;
  (void)chartInstance;
  sf_mex_import(c28_parentId, sf_mex_dup(c28_u), c28_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c28_i9 = 0; c28_i9 < 3; c28_i9++) {
    c28_y[c28_i9] = c28_dv1[c28_i9];
  }

  sf_mex_destroy(&c28_u);
}

static void c28_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData)
{
  const mxArray *c28_y;
  const char_T *c28_identifier;
  emlrtMsgIdentifier c28_thisId;
  real_T c28_b_y[3];
  int32_T c28_i10;
  SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c28_y = sf_mex_dup(c28_mxArrayInData);
  c28_identifier = c28_varName;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c28_y), &c28_thisId, c28_b_y);
  sf_mex_destroy(&c28_y);
  for (c28_i10 = 0; c28_i10 < 3; c28_i10++) {
    (*(real_T (*)[3])c28_outData)[c28_i10] = c28_b_y[c28_i10];
  }

  sf_mex_destroy(&c28_mxArrayInData);
}

static const mxArray *c28_b_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData)
{
  const mxArray *c28_mxArrayOutData = NULL;
  int32_T c28_i11;
  int32_T c28_i12;
  int32_T c28_i13;
  real_T c28_b_inData[9];
  int32_T c28_i14;
  int32_T c28_i15;
  int32_T c28_i16;
  real_T c28_u[9];
  const mxArray *c28_y = NULL;
  SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c28_mxArrayOutData = NULL;
  c28_i11 = 0;
  for (c28_i12 = 0; c28_i12 < 3; c28_i12++) {
    for (c28_i13 = 0; c28_i13 < 3; c28_i13++) {
      c28_b_inData[c28_i13 + c28_i11] = (*(real_T (*)[9])c28_inData)[c28_i13 +
        c28_i11];
    }

    c28_i11 += 3;
  }

  c28_i14 = 0;
  for (c28_i15 = 0; c28_i15 < 3; c28_i15++) {
    for (c28_i16 = 0; c28_i16 < 3; c28_i16++) {
      c28_u[c28_i16 + c28_i14] = c28_b_inData[c28_i16 + c28_i14];
    }

    c28_i14 += 3;
  }

  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_create("y", c28_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c28_mxArrayOutData, c28_y, false);
  return c28_mxArrayOutData;
}

static const mxArray *c28_c_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData)
{
  const mxArray *c28_mxArrayOutData = NULL;
  real_T c28_u;
  const mxArray *c28_y = NULL;
  SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c28_mxArrayOutData = NULL;
  c28_u = *(real_T *)c28_inData;
  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_create("y", &c28_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c28_mxArrayOutData, c28_y, false);
  return c28_mxArrayOutData;
}

static real_T c28_c_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId)
{
  real_T c28_y;
  real_T c28_d0;
  (void)chartInstance;
  sf_mex_import(c28_parentId, sf_mex_dup(c28_u), &c28_d0, 1, 0, 0U, 0, 0U, 0);
  c28_y = c28_d0;
  sf_mex_destroy(&c28_u);
  return c28_y;
}

static void c28_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData)
{
  const mxArray *c28_nargout;
  const char_T *c28_identifier;
  emlrtMsgIdentifier c28_thisId;
  real_T c28_y;
  SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c28_nargout = sf_mex_dup(c28_mxArrayInData);
  c28_identifier = c28_varName;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_y = c28_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c28_nargout),
    &c28_thisId);
  sf_mex_destroy(&c28_nargout);
  *(real_T *)c28_outData = c28_y;
  sf_mex_destroy(&c28_mxArrayInData);
}

const mxArray *sf_c28_CSE1_Oculus_gesture_get_eml_resolved_functions_info(void)
{
  const mxArray *c28_nameCaptureInfo = NULL;
  c28_nameCaptureInfo = NULL;
  sf_mex_assign(&c28_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c28_nameCaptureInfo;
}

static const mxArray *c28_d_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData)
{
  const mxArray *c28_mxArrayOutData = NULL;
  int32_T c28_u;
  const mxArray *c28_y = NULL;
  SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c28_mxArrayOutData = NULL;
  c28_u = *(int32_T *)c28_inData;
  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_create("y", &c28_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c28_mxArrayOutData, c28_y, false);
  return c28_mxArrayOutData;
}

static int32_T c28_d_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId)
{
  int32_T c28_y;
  int32_T c28_i17;
  (void)chartInstance;
  sf_mex_import(c28_parentId, sf_mex_dup(c28_u), &c28_i17, 1, 6, 0U, 0, 0U, 0);
  c28_y = c28_i17;
  sf_mex_destroy(&c28_u);
  return c28_y;
}

static void c28_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData)
{
  const mxArray *c28_b_sfEvent;
  const char_T *c28_identifier;
  emlrtMsgIdentifier c28_thisId;
  int32_T c28_y;
  SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c28_b_sfEvent = sf_mex_dup(c28_mxArrayInData);
  c28_identifier = c28_varName;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_y = c28_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c28_b_sfEvent),
    &c28_thisId);
  sf_mex_destroy(&c28_b_sfEvent);
  *(int32_T *)c28_outData = c28_y;
  sf_mex_destroy(&c28_mxArrayInData);
}

static uint8_T c28_e_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_b_is_active_c28_CSE1_Oculus_gesture, const
  char_T *c28_identifier)
{
  uint8_T c28_y;
  emlrtMsgIdentifier c28_thisId;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_y = c28_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c28_b_is_active_c28_CSE1_Oculus_gesture), &c28_thisId);
  sf_mex_destroy(&c28_b_is_active_c28_CSE1_Oculus_gesture);
  return c28_y;
}

static uint8_T c28_f_emlrt_marshallIn(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId)
{
  uint8_T c28_y;
  uint8_T c28_u0;
  (void)chartInstance;
  sf_mex_import(c28_parentId, sf_mex_dup(c28_u), &c28_u0, 1, 3, 0U, 0, 0U, 0);
  c28_y = c28_u0;
  sf_mex_destroy(&c28_u);
  return c28_y;
}

static void init_dsm_address_info(SFc28_CSE1_Oculus_gestureInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c28_CSE1_Oculus_gesture_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1015263013U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3205539371U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1790276243U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3434160899U);
}

mxArray *sf_c28_CSE1_Oculus_gesture_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("wGDWcrDPoP6upYHC6H790F");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c28_CSE1_Oculus_gesture_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c28_CSE1_Oculus_gesture_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c28_CSE1_Oculus_gesture(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c28_CSE1_Oculus_gesture\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c28_CSE1_Oculus_gesture_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_Oculus_gestureMachineNumber_,
           28,
           1,
           1,
           0,
           2,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_CSE1_Oculus_gestureMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_CSE1_Oculus_gestureMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _CSE1_Oculus_gestureMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,59);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)
            c28_sf_marshallIn);
        }

        {
          real_T (*c28_u)[9];
          real_T (*c28_y)[3];
          c28_y = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c28_u = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c28_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c28_y);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _CSE1_Oculus_gestureMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "gTLrfa3gzmKOIRVgKqxP3E";
}

static void sf_opaque_initialize_c28_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc28_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c28_CSE1_Oculus_gesture
    ((SFc28_CSE1_Oculus_gestureInstanceStruct*) chartInstanceVar);
  initialize_c28_CSE1_Oculus_gesture((SFc28_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c28_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  enable_c28_CSE1_Oculus_gesture((SFc28_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c28_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  disable_c28_CSE1_Oculus_gesture((SFc28_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c28_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  sf_gateway_c28_CSE1_Oculus_gesture((SFc28_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c28_CSE1_Oculus_gesture
  (SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c28_CSE1_Oculus_gesture
    ((SFc28_CSE1_Oculus_gestureInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c28_CSE1_Oculus_gesture();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c28_CSE1_Oculus_gesture(SimStruct* S,
  const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c28_CSE1_Oculus_gesture();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c28_CSE1_Oculus_gesture((SFc28_CSE1_Oculus_gestureInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c28_CSE1_Oculus_gesture(SimStruct*
  S)
{
  return sf_internal_get_sim_state_c28_CSE1_Oculus_gesture(S);
}

static void sf_opaque_set_sim_state_c28_CSE1_Oculus_gesture(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c28_CSE1_Oculus_gesture(S, st);
}

static void sf_opaque_terminate_c28_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc28_CSE1_Oculus_gestureInstanceStruct*) chartInstanceVar
      )->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_Oculus_gesture_optimization_info();
    }

    finalize_c28_CSE1_Oculus_gesture((SFc28_CSE1_Oculus_gestureInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc28_CSE1_Oculus_gesture((SFc28_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c28_CSE1_Oculus_gesture(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c28_CSE1_Oculus_gesture
      ((SFc28_CSE1_Oculus_gestureInstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c28_CSE1_Oculus_gesture(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_Oculus_gesture_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      28);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,28,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,28,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,28);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,28,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,28,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,28);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(299400708U));
  ssSetChecksum1(S,(3858039242U));
  ssSetChecksum2(S,(231537238U));
  ssSetChecksum3(S,(1109977696U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c28_CSE1_Oculus_gesture(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c28_CSE1_Oculus_gesture(SimStruct *S)
{
  SFc28_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc28_CSE1_Oculus_gestureInstanceStruct *)utMalloc(sizeof
    (SFc28_CSE1_Oculus_gestureInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc28_CSE1_Oculus_gestureInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.mdlStart = mdlStart_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c28_CSE1_Oculus_gesture;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c28_CSE1_Oculus_gesture_method_dispatcher(SimStruct *S, int_T method, void *
  data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c28_CSE1_Oculus_gesture(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c28_CSE1_Oculus_gesture(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c28_CSE1_Oculus_gesture(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c28_CSE1_Oculus_gesture_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
