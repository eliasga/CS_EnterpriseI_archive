/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ctrl_student_sfun.h"
#include "c34_ctrl_student.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ctrl_student_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c34_debug_family_names[6] = { "nargin", "nargout", "a",
  "eta_dot", "eta_dot_filtered_prev", "eta_dot_filtered" };

/* Function Declarations */
static void initialize_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance);
static void initialize_params_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct *
  chartInstance);
static void enable_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance);
static void disable_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance);
static void c34_update_debugger_state_c34_ctrl_student
  (SFc34_ctrl_studentInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c34_ctrl_student
  (SFc34_ctrl_studentInstanceStruct *chartInstance);
static void set_sim_state_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_st);
static void finalize_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance);
static void sf_gateway_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance);
static void initSimStructsc34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c34_machineNumber, uint32_T
  c34_chartNumber, uint32_T c34_instanceNumber);
static const mxArray *c34_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData);
static void c34_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c34_eta_dot_filtered, const char_T *c34_identifier, real_T
  c34_y[3]);
static void c34_b_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId,
  real_T c34_y[3]);
static void c34_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData);
static const mxArray *c34_b_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData);
static real_T c34_c_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId);
static void c34_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData);
static void c34_info_helper(const mxArray **c34_info);
static const mxArray *c34_emlrt_marshallOut(const char * c34_u);
static const mxArray *c34_b_emlrt_marshallOut(const uint32_T c34_u);
static const mxArray *c34_c_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData);
static int32_T c34_d_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId);
static void c34_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData);
static uint8_T c34_e_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_b_is_active_c34_ctrl_student, const char_T *
  c34_identifier);
static uint8_T c34_f_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId);
static void init_dsm_address_info(SFc34_ctrl_studentInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance)
{
  chartInstance->c34_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c34_is_active_c34_ctrl_student = 0U;
}

static void initialize_params_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void enable_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c34_update_debugger_state_c34_ctrl_student
  (SFc34_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c34_ctrl_student
  (SFc34_ctrl_studentInstanceStruct *chartInstance)
{
  const mxArray *c34_st;
  const mxArray *c34_y = NULL;
  int32_T c34_i0;
  real_T c34_u[3];
  const mxArray *c34_b_y = NULL;
  uint8_T c34_hoistedGlobal;
  uint8_T c34_b_u;
  const mxArray *c34_c_y = NULL;
  real_T (*c34_eta_dot_filtered)[3];
  c34_eta_dot_filtered = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
    1);
  c34_st = NULL;
  c34_st = NULL;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_createcellmatrix(2, 1), false);
  for (c34_i0 = 0; c34_i0 < 3; c34_i0++) {
    c34_u[c34_i0] = (*c34_eta_dot_filtered)[c34_i0];
  }

  c34_b_y = NULL;
  sf_mex_assign(&c34_b_y, sf_mex_create("y", c34_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c34_y, 0, c34_b_y);
  c34_hoistedGlobal = chartInstance->c34_is_active_c34_ctrl_student;
  c34_b_u = c34_hoistedGlobal;
  c34_c_y = NULL;
  sf_mex_assign(&c34_c_y, sf_mex_create("y", &c34_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c34_y, 1, c34_c_y);
  sf_mex_assign(&c34_st, c34_y, false);
  return c34_st;
}

static void set_sim_state_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_st)
{
  const mxArray *c34_u;
  real_T c34_dv0[3];
  int32_T c34_i1;
  real_T (*c34_eta_dot_filtered)[3];
  c34_eta_dot_filtered = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
    1);
  chartInstance->c34_doneDoubleBufferReInit = true;
  c34_u = sf_mex_dup(c34_st);
  c34_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c34_u, 0)),
                       "eta_dot_filtered", c34_dv0);
  for (c34_i1 = 0; c34_i1 < 3; c34_i1++) {
    (*c34_eta_dot_filtered)[c34_i1] = c34_dv0[c34_i1];
  }

  chartInstance->c34_is_active_c34_ctrl_student = c34_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c34_u, 1)),
     "is_active_c34_ctrl_student");
  sf_mex_destroy(&c34_u);
  c34_update_debugger_state_c34_ctrl_student(chartInstance);
  sf_mex_destroy(&c34_st);
}

static void finalize_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance)
{
  real_T c34_hoistedGlobal;
  real_T c34_a;
  int32_T c34_i2;
  real_T c34_eta_dot[3];
  int32_T c34_i3;
  real_T c34_eta_dot_filtered_prev[3];
  uint32_T c34_debug_family_var_map[6];
  real_T c34_nargin = 3.0;
  real_T c34_nargout = 1.0;
  real_T c34_eta_dot_filtered[3];
  real_T c34_b_a;
  int32_T c34_i4;
  real_T c34_b[3];
  int32_T c34_i5;
  real_T c34_c_a;
  int32_T c34_i6;
  real_T c34_b_b[3];
  int32_T c34_i7;
  int32_T c34_i8;
  int32_T c34_i9;
  int32_T c34_i10;
  int32_T c34_i11;
  int32_T c34_i12;
  real_T *c34_d_a;
  real_T (*c34_b_eta_dot_filtered)[3];
  real_T (*c34_b_eta_dot_filtered_prev)[3];
  real_T (*c34_b_eta_dot)[3];
  c34_b_eta_dot_filtered_prev = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 2);
  c34_b_eta_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c34_b_eta_dot_filtered = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
    1);
  c34_d_a = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 5U, chartInstance->c34_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c34_d_a, 0U);
  chartInstance->c34_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c34_sfEvent);
  c34_hoistedGlobal = *c34_d_a;
  c34_a = c34_hoistedGlobal;
  for (c34_i2 = 0; c34_i2 < 3; c34_i2++) {
    c34_eta_dot[c34_i2] = (*c34_b_eta_dot)[c34_i2];
  }

  for (c34_i3 = 0; c34_i3 < 3; c34_i3++) {
    c34_eta_dot_filtered_prev[c34_i3] = (*c34_b_eta_dot_filtered_prev)[c34_i3];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c34_debug_family_names,
    c34_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c34_nargin, 0U, c34_b_sf_marshallOut,
    c34_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c34_nargout, 1U, c34_b_sf_marshallOut,
    c34_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c34_a, 2U, c34_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c34_eta_dot, 3U, c34_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c34_eta_dot_filtered_prev, 4U, c34_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c34_eta_dot_filtered, 5U,
    c34_sf_marshallOut, c34_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c34_sfEvent, 3);
  c34_b_a = c34_a;
  for (c34_i4 = 0; c34_i4 < 3; c34_i4++) {
    c34_b[c34_i4] = c34_eta_dot[c34_i4];
  }

  for (c34_i5 = 0; c34_i5 < 3; c34_i5++) {
    c34_b[c34_i5] *= c34_b_a;
  }

  c34_c_a = 1.0 - c34_a;
  for (c34_i6 = 0; c34_i6 < 3; c34_i6++) {
    c34_b_b[c34_i6] = c34_eta_dot_filtered_prev[c34_i6];
  }

  for (c34_i7 = 0; c34_i7 < 3; c34_i7++) {
    c34_b_b[c34_i7] *= c34_c_a;
  }

  for (c34_i8 = 0; c34_i8 < 3; c34_i8++) {
    c34_eta_dot_filtered[c34_i8] = c34_b[c34_i8] + c34_b_b[c34_i8];
  }

  _SFD_EML_CALL(0U, chartInstance->c34_sfEvent, -3);
  _SFD_SYMBOL_SCOPE_POP();
  for (c34_i9 = 0; c34_i9 < 3; c34_i9++) {
    (*c34_b_eta_dot_filtered)[c34_i9] = c34_eta_dot_filtered[c34_i9];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c34_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ctrl_studentMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c34_i10 = 0; c34_i10 < 3; c34_i10++) {
    _SFD_DATA_RANGE_CHECK((*c34_b_eta_dot_filtered)[c34_i10], 1U);
  }

  for (c34_i11 = 0; c34_i11 < 3; c34_i11++) {
    _SFD_DATA_RANGE_CHECK((*c34_b_eta_dot)[c34_i11], 2U);
  }

  for (c34_i12 = 0; c34_i12 < 3; c34_i12++) {
    _SFD_DATA_RANGE_CHECK((*c34_b_eta_dot_filtered_prev)[c34_i12], 3U);
  }
}

static void initSimStructsc34_ctrl_student(SFc34_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c34_machineNumber, uint32_T
  c34_chartNumber, uint32_T c34_instanceNumber)
{
  (void)c34_machineNumber;
  (void)c34_chartNumber;
  (void)c34_instanceNumber;
}

static const mxArray *c34_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData)
{
  const mxArray *c34_mxArrayOutData = NULL;
  int32_T c34_i13;
  real_T c34_b_inData[3];
  int32_T c34_i14;
  real_T c34_u[3];
  const mxArray *c34_y = NULL;
  SFc34_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc34_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c34_mxArrayOutData = NULL;
  for (c34_i13 = 0; c34_i13 < 3; c34_i13++) {
    c34_b_inData[c34_i13] = (*(real_T (*)[3])c34_inData)[c34_i13];
  }

  for (c34_i14 = 0; c34_i14 < 3; c34_i14++) {
    c34_u[c34_i14] = c34_b_inData[c34_i14];
  }

  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", c34_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c34_mxArrayOutData, c34_y, false);
  return c34_mxArrayOutData;
}

static void c34_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c34_eta_dot_filtered, const char_T *c34_identifier, real_T
  c34_y[3])
{
  emlrtMsgIdentifier c34_thisId;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c34_eta_dot_filtered),
    &c34_thisId, c34_y);
  sf_mex_destroy(&c34_eta_dot_filtered);
}

static void c34_b_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId,
  real_T c34_y[3])
{
  real_T c34_dv1[3];
  int32_T c34_i15;
  (void)chartInstance;
  sf_mex_import(c34_parentId, sf_mex_dup(c34_u), c34_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c34_i15 = 0; c34_i15 < 3; c34_i15++) {
    c34_y[c34_i15] = c34_dv1[c34_i15];
  }

  sf_mex_destroy(&c34_u);
}

static void c34_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData)
{
  const mxArray *c34_eta_dot_filtered;
  const char_T *c34_identifier;
  emlrtMsgIdentifier c34_thisId;
  real_T c34_y[3];
  int32_T c34_i16;
  SFc34_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc34_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c34_eta_dot_filtered = sf_mex_dup(c34_mxArrayInData);
  c34_identifier = c34_varName;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c34_eta_dot_filtered),
    &c34_thisId, c34_y);
  sf_mex_destroy(&c34_eta_dot_filtered);
  for (c34_i16 = 0; c34_i16 < 3; c34_i16++) {
    (*(real_T (*)[3])c34_outData)[c34_i16] = c34_y[c34_i16];
  }

  sf_mex_destroy(&c34_mxArrayInData);
}

static const mxArray *c34_b_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData)
{
  const mxArray *c34_mxArrayOutData = NULL;
  real_T c34_u;
  const mxArray *c34_y = NULL;
  SFc34_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc34_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c34_mxArrayOutData = NULL;
  c34_u = *(real_T *)c34_inData;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", &c34_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c34_mxArrayOutData, c34_y, false);
  return c34_mxArrayOutData;
}

static real_T c34_c_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId)
{
  real_T c34_y;
  real_T c34_d0;
  (void)chartInstance;
  sf_mex_import(c34_parentId, sf_mex_dup(c34_u), &c34_d0, 1, 0, 0U, 0, 0U, 0);
  c34_y = c34_d0;
  sf_mex_destroy(&c34_u);
  return c34_y;
}

static void c34_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData)
{
  const mxArray *c34_nargout;
  const char_T *c34_identifier;
  emlrtMsgIdentifier c34_thisId;
  real_T c34_y;
  SFc34_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc34_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c34_nargout = sf_mex_dup(c34_mxArrayInData);
  c34_identifier = c34_varName;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_y = c34_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c34_nargout),
    &c34_thisId);
  sf_mex_destroy(&c34_nargout);
  *(real_T *)c34_outData = c34_y;
  sf_mex_destroy(&c34_mxArrayInData);
}

const mxArray *sf_c34_ctrl_student_get_eml_resolved_functions_info(void)
{
  const mxArray *c34_nameCaptureInfo = NULL;
  c34_nameCaptureInfo = NULL;
  sf_mex_assign(&c34_nameCaptureInfo, sf_mex_createstruct("structure", 2, 2, 1),
                false);
  c34_info_helper(&c34_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c34_nameCaptureInfo);
  return c34_nameCaptureInfo;
}

static void c34_info_helper(const mxArray **c34_info)
{
  const mxArray *c34_rhs0 = NULL;
  const mxArray *c34_lhs0 = NULL;
  const mxArray *c34_rhs1 = NULL;
  const mxArray *c34_lhs1 = NULL;
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c34_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c34_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs1), "lhs", "lhs",
                  1);
  sf_mex_destroy(&c34_rhs0);
  sf_mex_destroy(&c34_lhs0);
  sf_mex_destroy(&c34_rhs1);
  sf_mex_destroy(&c34_lhs1);
}

static const mxArray *c34_emlrt_marshallOut(const char * c34_u)
{
  const mxArray *c34_y = NULL;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", c34_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c34_u)), false);
  return c34_y;
}

static const mxArray *c34_b_emlrt_marshallOut(const uint32_T c34_u)
{
  const mxArray *c34_y = NULL;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", &c34_u, 7, 0U, 0U, 0U, 0), false);
  return c34_y;
}

static const mxArray *c34_c_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData)
{
  const mxArray *c34_mxArrayOutData = NULL;
  int32_T c34_u;
  const mxArray *c34_y = NULL;
  SFc34_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc34_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c34_mxArrayOutData = NULL;
  c34_u = *(int32_T *)c34_inData;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", &c34_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c34_mxArrayOutData, c34_y, false);
  return c34_mxArrayOutData;
}

static int32_T c34_d_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId)
{
  int32_T c34_y;
  int32_T c34_i17;
  (void)chartInstance;
  sf_mex_import(c34_parentId, sf_mex_dup(c34_u), &c34_i17, 1, 6, 0U, 0, 0U, 0);
  c34_y = c34_i17;
  sf_mex_destroy(&c34_u);
  return c34_y;
}

static void c34_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData)
{
  const mxArray *c34_b_sfEvent;
  const char_T *c34_identifier;
  emlrtMsgIdentifier c34_thisId;
  int32_T c34_y;
  SFc34_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc34_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c34_b_sfEvent = sf_mex_dup(c34_mxArrayInData);
  c34_identifier = c34_varName;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_y = c34_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c34_b_sfEvent),
    &c34_thisId);
  sf_mex_destroy(&c34_b_sfEvent);
  *(int32_T *)c34_outData = c34_y;
  sf_mex_destroy(&c34_mxArrayInData);
}

static uint8_T c34_e_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_b_is_active_c34_ctrl_student, const char_T *
  c34_identifier)
{
  uint8_T c34_y;
  emlrtMsgIdentifier c34_thisId;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_y = c34_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c34_b_is_active_c34_ctrl_student), &c34_thisId);
  sf_mex_destroy(&c34_b_is_active_c34_ctrl_student);
  return c34_y;
}

static uint8_T c34_f_emlrt_marshallIn(SFc34_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId)
{
  uint8_T c34_y;
  uint8_T c34_u0;
  (void)chartInstance;
  sf_mex_import(c34_parentId, sf_mex_dup(c34_u), &c34_u0, 1, 3, 0U, 0, 0U, 0);
  c34_y = c34_u0;
  sf_mex_destroy(&c34_u);
  return c34_y;
}

static void init_dsm_address_info(SFc34_ctrl_studentInstanceStruct
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

void sf_c34_ctrl_student_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3749738760U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2002152498U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(635480812U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2209361810U);
}

mxArray *sf_c34_ctrl_student_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("WrXO8sSmra0b642F8IO1yG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
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

mxArray *sf_c34_ctrl_student_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c34_ctrl_student_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c34_ctrl_student(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"eta_dot_filtered\",},{M[8],M[0],T\"is_active_c34_ctrl_student\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c34_ctrl_student_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc34_ctrl_studentInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc34_ctrl_studentInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ctrl_studentMachineNumber_,
           34,
           1,
           1,
           0,
           4,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_ctrl_studentMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ctrl_studentMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ctrl_studentMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"a");
          _SFD_SET_DATA_PROPS(1,2,0,1,"eta_dot_filtered");
          _SFD_SET_DATA_PROPS(2,1,1,0,"eta_dot");
          _SFD_SET_DATA_PROPS(3,1,1,0,"eta_dot_filtered_prev");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,125);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c34_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c34_sf_marshallOut,(MexInFcnForType)
            c34_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c34_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c34_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T *c34_a;
          real_T (*c34_eta_dot_filtered)[3];
          real_T (*c34_eta_dot)[3];
          real_T (*c34_eta_dot_filtered_prev)[3];
          c34_eta_dot_filtered_prev = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 2);
          c34_eta_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c34_eta_dot_filtered = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c34_a = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c34_a);
          _SFD_SET_DATA_VALUE_PTR(1U, *c34_eta_dot_filtered);
          _SFD_SET_DATA_VALUE_PTR(2U, *c34_eta_dot);
          _SFD_SET_DATA_VALUE_PTR(3U, *c34_eta_dot_filtered_prev);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ctrl_studentMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "piVJe9Rzy8Nt0gZdvFZjEH";
}

static void sf_opaque_initialize_c34_ctrl_student(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc34_ctrl_studentInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c34_ctrl_student((SFc34_ctrl_studentInstanceStruct*)
    chartInstanceVar);
  initialize_c34_ctrl_student((SFc34_ctrl_studentInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c34_ctrl_student(void *chartInstanceVar)
{
  enable_c34_ctrl_student((SFc34_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c34_ctrl_student(void *chartInstanceVar)
{
  disable_c34_ctrl_student((SFc34_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c34_ctrl_student(void *chartInstanceVar)
{
  sf_gateway_c34_ctrl_student((SFc34_ctrl_studentInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c34_ctrl_student(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c34_ctrl_student
    ((SFc34_ctrl_studentInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c34_ctrl_student();/* state var info */
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

extern void sf_internal_set_sim_state_c34_ctrl_student(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c34_ctrl_student();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c34_ctrl_student((SFc34_ctrl_studentInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c34_ctrl_student(SimStruct* S)
{
  return sf_internal_get_sim_state_c34_ctrl_student(S);
}

static void sf_opaque_set_sim_state_c34_ctrl_student(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c34_ctrl_student(S, st);
}

static void sf_opaque_terminate_c34_ctrl_student(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc34_ctrl_studentInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ctrl_student_optimization_info();
    }

    finalize_c34_ctrl_student((SFc34_ctrl_studentInstanceStruct*)
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
  initSimStructsc34_ctrl_student((SFc34_ctrl_studentInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c34_ctrl_student(SimStruct *S)
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
    initialize_params_c34_ctrl_student((SFc34_ctrl_studentInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c34_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ctrl_student_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      34);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,34,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,34,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,34);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,34,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,34,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,34);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2735226233U));
  ssSetChecksum1(S,(3209203606U));
  ssSetChecksum2(S,(3261867363U));
  ssSetChecksum3(S,(4025730065U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c34_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c34_ctrl_student(SimStruct *S)
{
  SFc34_ctrl_studentInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc34_ctrl_studentInstanceStruct *)utMalloc(sizeof
    (SFc34_ctrl_studentInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc34_ctrl_studentInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c34_ctrl_student;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c34_ctrl_student;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c34_ctrl_student;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c34_ctrl_student;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c34_ctrl_student;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c34_ctrl_student;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c34_ctrl_student;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c34_ctrl_student;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c34_ctrl_student;
  chartInstance->chartInfo.mdlStart = mdlStart_c34_ctrl_student;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c34_ctrl_student;
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

void c34_ctrl_student_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c34_ctrl_student(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c34_ctrl_student(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c34_ctrl_student(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c34_ctrl_student_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
