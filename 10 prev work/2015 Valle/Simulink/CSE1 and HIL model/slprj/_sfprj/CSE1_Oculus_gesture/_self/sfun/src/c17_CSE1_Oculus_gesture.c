/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_Oculus_gesture_sfun.h"
#include "c17_CSE1_Oculus_gesture.h"
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
static const char * c17_debug_family_names[4] = { "nargin", "nargout", "K_i1",
  "K_i" };

/* Function Declarations */
static void initialize_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void initialize_params_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void enable_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void disable_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void c17_update_debugger_state_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void set_sim_state_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance, const mxArray *c17_st);
static void finalize_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void sf_gateway_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void initSimStructsc17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c17_machineNumber, uint32_T
  c17_chartNumber, uint32_T c17_instanceNumber);
static const mxArray *c17_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static void c17_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_K_i, const char_T *c17_identifier, real_T
  c17_y[9]);
static void c17_b_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId,
  real_T c17_y[9]);
static void c17_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData);
static const mxArray *c17_b_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static const mxArray *c17_c_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static real_T c17_c_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId);
static void c17_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData);
static void c17_info_helper(const mxArray **c17_info);
static const mxArray *c17_emlrt_marshallOut(const char * c17_u);
static const mxArray *c17_b_emlrt_marshallOut(const uint32_T c17_u);
static const mxArray *c17_d_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static int32_T c17_d_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId);
static void c17_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData);
static uint8_T c17_e_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_b_is_active_c17_CSE1_Oculus_gesture, const
  char_T *c17_identifier);
static uint8_T c17_f_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId);
static void init_dsm_address_info(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  chartInstance->c17_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c17_is_active_c17_CSE1_Oculus_gesture = 0U;
}

static void initialize_params_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c17_update_debugger_state_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  const mxArray *c17_st;
  const mxArray *c17_y = NULL;
  int32_T c17_i0;
  real_T c17_u[9];
  const mxArray *c17_b_y = NULL;
  uint8_T c17_hoistedGlobal;
  uint8_T c17_b_u;
  const mxArray *c17_c_y = NULL;
  real_T (*c17_K_i)[9];
  c17_K_i = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c17_st = NULL;
  c17_st = NULL;
  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_createcellmatrix(2, 1), false);
  for (c17_i0 = 0; c17_i0 < 9; c17_i0++) {
    c17_u[c17_i0] = (*c17_K_i)[c17_i0];
  }

  c17_b_y = NULL;
  sf_mex_assign(&c17_b_y, sf_mex_create("y", c17_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_setcell(c17_y, 0, c17_b_y);
  c17_hoistedGlobal = chartInstance->c17_is_active_c17_CSE1_Oculus_gesture;
  c17_b_u = c17_hoistedGlobal;
  c17_c_y = NULL;
  sf_mex_assign(&c17_c_y, sf_mex_create("y", &c17_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c17_y, 1, c17_c_y);
  sf_mex_assign(&c17_st, c17_y, false);
  return c17_st;
}

static void set_sim_state_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance, const mxArray *c17_st)
{
  const mxArray *c17_u;
  real_T c17_dv0[9];
  int32_T c17_i1;
  real_T (*c17_K_i)[9];
  c17_K_i = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c17_doneDoubleBufferReInit = true;
  c17_u = sf_mex_dup(c17_st);
  c17_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c17_u, 0)),
                       "K_i", c17_dv0);
  for (c17_i1 = 0; c17_i1 < 9; c17_i1++) {
    (*c17_K_i)[c17_i1] = c17_dv0[c17_i1];
  }

  chartInstance->c17_is_active_c17_CSE1_Oculus_gesture = c17_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c17_u, 1)),
     "is_active_c17_CSE1_Oculus_gesture");
  sf_mex_destroy(&c17_u);
  c17_update_debugger_state_c17_CSE1_Oculus_gesture(chartInstance);
  sf_mex_destroy(&c17_st);
}

static void finalize_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  int32_T c17_i2;
  real_T c17_K_i1[3];
  uint32_T c17_debug_family_var_map[4];
  real_T c17_nargin = 1.0;
  real_T c17_nargout = 1.0;
  real_T c17_K_i[9];
  int32_T c17_i3;
  real_T c17_v[3];
  int32_T c17_i4;
  int32_T c17_j;
  int32_T c17_b_j;
  int32_T c17_i5;
  int32_T c17_i6;
  int32_T c17_i7;
  real_T (*c17_b_K_i)[9];
  real_T (*c17_b_K_i1)[3];
  c17_b_K_i1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  c17_b_K_i = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 11U, chartInstance->c17_sfEvent);
  chartInstance->c17_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c17_sfEvent);
  for (c17_i2 = 0; c17_i2 < 3; c17_i2++) {
    c17_K_i1[c17_i2] = (*c17_b_K_i1)[c17_i2];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c17_debug_family_names,
    c17_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_nargin, 0U, c17_c_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_nargout, 1U, c17_c_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c17_K_i1, 2U, c17_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_K_i, 3U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 4);
  for (c17_i3 = 0; c17_i3 < 3; c17_i3++) {
    c17_v[c17_i3] = c17_K_i1[c17_i3];
  }

  for (c17_i4 = 0; c17_i4 < 9; c17_i4++) {
    c17_K_i[c17_i4] = 0.0;
  }

  for (c17_j = 1; c17_j < 4; c17_j++) {
    c17_b_j = c17_j;
    c17_K_i[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
               (real_T)c17_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
               "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c17_b_j), 1, 3, 2, 0)
              - 1)) - 1] = c17_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c17_b_j), 1, 3, 1, 0) - 1];
  }

  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c17_i5 = 0; c17_i5 < 9; c17_i5++) {
    (*c17_b_K_i)[c17_i5] = c17_K_i[c17_i5];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c17_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_Oculus_gestureMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c17_i6 = 0; c17_i6 < 9; c17_i6++) {
    _SFD_DATA_RANGE_CHECK((*c17_b_K_i)[c17_i6], 0U);
  }

  for (c17_i7 = 0; c17_i7 < 3; c17_i7++) {
    _SFD_DATA_RANGE_CHECK((*c17_b_K_i1)[c17_i7], 1U);
  }
}

static void initSimStructsc17_CSE1_Oculus_gesture
  (SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c17_machineNumber, uint32_T
  c17_chartNumber, uint32_T c17_instanceNumber)
{
  (void)c17_machineNumber;
  (void)c17_chartNumber;
  (void)c17_instanceNumber;
}

static const mxArray *c17_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  int32_T c17_i8;
  int32_T c17_i9;
  int32_T c17_i10;
  real_T c17_b_inData[9];
  int32_T c17_i11;
  int32_T c17_i12;
  int32_T c17_i13;
  real_T c17_u[9];
  const mxArray *c17_y = NULL;
  SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  c17_i8 = 0;
  for (c17_i9 = 0; c17_i9 < 3; c17_i9++) {
    for (c17_i10 = 0; c17_i10 < 3; c17_i10++) {
      c17_b_inData[c17_i10 + c17_i8] = (*(real_T (*)[9])c17_inData)[c17_i10 +
        c17_i8];
    }

    c17_i8 += 3;
  }

  c17_i11 = 0;
  for (c17_i12 = 0; c17_i12 < 3; c17_i12++) {
    for (c17_i13 = 0; c17_i13 < 3; c17_i13++) {
      c17_u[c17_i13 + c17_i11] = c17_b_inData[c17_i13 + c17_i11];
    }

    c17_i11 += 3;
  }

  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", c17_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, false);
  return c17_mxArrayOutData;
}

static void c17_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_K_i, const char_T *c17_identifier, real_T
  c17_y[9])
{
  emlrtMsgIdentifier c17_thisId;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_K_i), &c17_thisId, c17_y);
  sf_mex_destroy(&c17_K_i);
}

static void c17_b_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId,
  real_T c17_y[9])
{
  real_T c17_dv1[9];
  int32_T c17_i14;
  (void)chartInstance;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), c17_dv1, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c17_i14 = 0; c17_i14 < 9; c17_i14++) {
    c17_y[c17_i14] = c17_dv1[c17_i14];
  }

  sf_mex_destroy(&c17_u);
}

static void c17_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData)
{
  const mxArray *c17_K_i;
  const char_T *c17_identifier;
  emlrtMsgIdentifier c17_thisId;
  real_T c17_y[9];
  int32_T c17_i15;
  int32_T c17_i16;
  int32_T c17_i17;
  SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c17_K_i = sf_mex_dup(c17_mxArrayInData);
  c17_identifier = c17_varName;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_K_i), &c17_thisId, c17_y);
  sf_mex_destroy(&c17_K_i);
  c17_i15 = 0;
  for (c17_i16 = 0; c17_i16 < 3; c17_i16++) {
    for (c17_i17 = 0; c17_i17 < 3; c17_i17++) {
      (*(real_T (*)[9])c17_outData)[c17_i17 + c17_i15] = c17_y[c17_i17 + c17_i15];
    }

    c17_i15 += 3;
  }

  sf_mex_destroy(&c17_mxArrayInData);
}

static const mxArray *c17_b_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  int32_T c17_i18;
  real_T c17_b_inData[3];
  int32_T c17_i19;
  real_T c17_u[3];
  const mxArray *c17_y = NULL;
  SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  for (c17_i18 = 0; c17_i18 < 3; c17_i18++) {
    c17_b_inData[c17_i18] = (*(real_T (*)[3])c17_inData)[c17_i18];
  }

  for (c17_i19 = 0; c17_i19 < 3; c17_i19++) {
    c17_u[c17_i19] = c17_b_inData[c17_i19];
  }

  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", c17_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, false);
  return c17_mxArrayOutData;
}

static const mxArray *c17_c_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  real_T c17_u;
  const mxArray *c17_y = NULL;
  SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  c17_u = *(real_T *)c17_inData;
  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", &c17_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, false);
  return c17_mxArrayOutData;
}

static real_T c17_c_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId)
{
  real_T c17_y;
  real_T c17_d0;
  (void)chartInstance;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), &c17_d0, 1, 0, 0U, 0, 0U, 0);
  c17_y = c17_d0;
  sf_mex_destroy(&c17_u);
  return c17_y;
}

static void c17_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData)
{
  const mxArray *c17_nargout;
  const char_T *c17_identifier;
  emlrtMsgIdentifier c17_thisId;
  real_T c17_y;
  SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c17_nargout = sf_mex_dup(c17_mxArrayInData);
  c17_identifier = c17_varName;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_y = c17_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_nargout),
    &c17_thisId);
  sf_mex_destroy(&c17_nargout);
  *(real_T *)c17_outData = c17_y;
  sf_mex_destroy(&c17_mxArrayInData);
}

const mxArray *sf_c17_CSE1_Oculus_gesture_get_eml_resolved_functions_info(void)
{
  const mxArray *c17_nameCaptureInfo = NULL;
  c17_nameCaptureInfo = NULL;
  sf_mex_assign(&c17_nameCaptureInfo, sf_mex_createstruct("structure", 2, 8, 1),
                false);
  c17_info_helper(&c17_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c17_nameCaptureInfo);
  return c17_nameCaptureInfo;
}

static void c17_info_helper(const mxArray **c17_info)
{
  const mxArray *c17_rhs0 = NULL;
  const mxArray *c17_lhs0 = NULL;
  const mxArray *c17_rhs1 = NULL;
  const mxArray *c17_lhs1 = NULL;
  const mxArray *c17_rhs2 = NULL;
  const mxArray *c17_lhs2 = NULL;
  const mxArray *c17_rhs3 = NULL;
  const mxArray *c17_lhs3 = NULL;
  const mxArray *c17_rhs4 = NULL;
  const mxArray *c17_lhs4 = NULL;
  const mxArray *c17_rhs5 = NULL;
  const mxArray *c17_lhs5 = NULL;
  const mxArray *c17_rhs6 = NULL;
  const mxArray *c17_lhs6 = NULL;
  const mxArray *c17_rhs7 = NULL;
  const mxArray *c17_lhs7 = NULL;
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("diag"), "name", "name", 0);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c17_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c17_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("ismatrix"), "name", "name",
                  1);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c17_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c17_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c17_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c17_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c17_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c17_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c17_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c17_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 5);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c17_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c17_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 6);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("intmax"), "name", "name", 6);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c17_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c17_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 7);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c17_info, c17_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c17_info, c17_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c17_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c17_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c17_info, sf_mex_duplicatearraysafe(&c17_lhs7), "lhs", "lhs",
                  7);
  sf_mex_destroy(&c17_rhs0);
  sf_mex_destroy(&c17_lhs0);
  sf_mex_destroy(&c17_rhs1);
  sf_mex_destroy(&c17_lhs1);
  sf_mex_destroy(&c17_rhs2);
  sf_mex_destroy(&c17_lhs2);
  sf_mex_destroy(&c17_rhs3);
  sf_mex_destroy(&c17_lhs3);
  sf_mex_destroy(&c17_rhs4);
  sf_mex_destroy(&c17_lhs4);
  sf_mex_destroy(&c17_rhs5);
  sf_mex_destroy(&c17_lhs5);
  sf_mex_destroy(&c17_rhs6);
  sf_mex_destroy(&c17_lhs6);
  sf_mex_destroy(&c17_rhs7);
  sf_mex_destroy(&c17_lhs7);
}

static const mxArray *c17_emlrt_marshallOut(const char * c17_u)
{
  const mxArray *c17_y = NULL;
  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", c17_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c17_u)), false);
  return c17_y;
}

static const mxArray *c17_b_emlrt_marshallOut(const uint32_T c17_u)
{
  const mxArray *c17_y = NULL;
  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", &c17_u, 7, 0U, 0U, 0U, 0), false);
  return c17_y;
}

static const mxArray *c17_d_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  int32_T c17_u;
  const mxArray *c17_y = NULL;
  SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  c17_u = *(int32_T *)c17_inData;
  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", &c17_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, false);
  return c17_mxArrayOutData;
}

static int32_T c17_d_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId)
{
  int32_T c17_y;
  int32_T c17_i20;
  (void)chartInstance;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), &c17_i20, 1, 6, 0U, 0, 0U, 0);
  c17_y = c17_i20;
  sf_mex_destroy(&c17_u);
  return c17_y;
}

static void c17_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData)
{
  const mxArray *c17_b_sfEvent;
  const char_T *c17_identifier;
  emlrtMsgIdentifier c17_thisId;
  int32_T c17_y;
  SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c17_b_sfEvent = sf_mex_dup(c17_mxArrayInData);
  c17_identifier = c17_varName;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_y = c17_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_b_sfEvent),
    &c17_thisId);
  sf_mex_destroy(&c17_b_sfEvent);
  *(int32_T *)c17_outData = c17_y;
  sf_mex_destroy(&c17_mxArrayInData);
}

static uint8_T c17_e_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_b_is_active_c17_CSE1_Oculus_gesture, const
  char_T *c17_identifier)
{
  uint8_T c17_y;
  emlrtMsgIdentifier c17_thisId;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_y = c17_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c17_b_is_active_c17_CSE1_Oculus_gesture), &c17_thisId);
  sf_mex_destroy(&c17_b_is_active_c17_CSE1_Oculus_gesture);
  return c17_y;
}

static uint8_T c17_f_emlrt_marshallIn(SFc17_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId)
{
  uint8_T c17_y;
  uint8_T c17_u0;
  (void)chartInstance;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), &c17_u0, 1, 3, 0U, 0, 0U, 0);
  c17_y = c17_u0;
  sf_mex_destroy(&c17_u);
  return c17_y;
}

static void init_dsm_address_info(SFc17_CSE1_Oculus_gestureInstanceStruct
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

void sf_c17_CSE1_Oculus_gesture_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2992751722U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2935330347U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1840364655U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3630695603U);
}

mxArray *sf_c17_CSE1_Oculus_gesture_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("Mj7CHw0385bxYKt1BP0rlF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c17_CSE1_Oculus_gesture_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c17_CSE1_Oculus_gesture_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c17_CSE1_Oculus_gesture(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[4],T\"K_i\",},{M[8],M[0],T\"is_active_c17_CSE1_Oculus_gesture\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c17_CSE1_Oculus_gesture_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_Oculus_gestureMachineNumber_,
           17,
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
          _SFD_SET_DATA_PROPS(0,2,0,1,"K_i");
          _SFD_SET_DATA_PROPS(1,1,1,0,"K_i1");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,53);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c17_sf_marshallOut,(MexInFcnForType)
            c17_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c17_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c17_K_i)[9];
          real_T (*c17_K_i1)[3];
          c17_K_i1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          c17_K_i = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, *c17_K_i);
          _SFD_SET_DATA_VALUE_PTR(1U, *c17_K_i1);
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
  return "26DfMYsRDbVTvZQ2QugyyF";
}

static void sf_opaque_initialize_c17_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc17_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c17_CSE1_Oculus_gesture
    ((SFc17_CSE1_Oculus_gestureInstanceStruct*) chartInstanceVar);
  initialize_c17_CSE1_Oculus_gesture((SFc17_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c17_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  enable_c17_CSE1_Oculus_gesture((SFc17_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c17_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  disable_c17_CSE1_Oculus_gesture((SFc17_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c17_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  sf_gateway_c17_CSE1_Oculus_gesture((SFc17_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c17_CSE1_Oculus_gesture
  (SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c17_CSE1_Oculus_gesture
    ((SFc17_CSE1_Oculus_gestureInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c17_CSE1_Oculus_gesture();/* state var info */
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

extern void sf_internal_set_sim_state_c17_CSE1_Oculus_gesture(SimStruct* S,
  const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c17_CSE1_Oculus_gesture();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c17_CSE1_Oculus_gesture((SFc17_CSE1_Oculus_gestureInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c17_CSE1_Oculus_gesture(SimStruct*
  S)
{
  return sf_internal_get_sim_state_c17_CSE1_Oculus_gesture(S);
}

static void sf_opaque_set_sim_state_c17_CSE1_Oculus_gesture(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c17_CSE1_Oculus_gesture(S, st);
}

static void sf_opaque_terminate_c17_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc17_CSE1_Oculus_gestureInstanceStruct*) chartInstanceVar
      )->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_Oculus_gesture_optimization_info();
    }

    finalize_c17_CSE1_Oculus_gesture((SFc17_CSE1_Oculus_gestureInstanceStruct*)
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
  initSimStructsc17_CSE1_Oculus_gesture((SFc17_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c17_CSE1_Oculus_gesture(SimStruct *S)
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
    initialize_params_c17_CSE1_Oculus_gesture
      ((SFc17_CSE1_Oculus_gestureInstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c17_CSE1_Oculus_gesture(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_Oculus_gesture_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      17);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,17,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,17,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,17);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,17,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,17,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,17);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3421545711U));
  ssSetChecksum1(S,(761754172U));
  ssSetChecksum2(S,(314961839U));
  ssSetChecksum3(S,(607936801U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c17_CSE1_Oculus_gesture(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c17_CSE1_Oculus_gesture(SimStruct *S)
{
  SFc17_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc17_CSE1_Oculus_gestureInstanceStruct *)utMalloc(sizeof
    (SFc17_CSE1_Oculus_gestureInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc17_CSE1_Oculus_gestureInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.mdlStart = mdlStart_c17_CSE1_Oculus_gesture;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c17_CSE1_Oculus_gesture;
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

void c17_CSE1_Oculus_gesture_method_dispatcher(SimStruct *S, int_T method, void *
  data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c17_CSE1_Oculus_gesture(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c17_CSE1_Oculus_gesture(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c17_CSE1_Oculus_gesture(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c17_CSE1_Oculus_gesture_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
