/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ctrl_student_sfun.h"
#include "c5_ctrl_student.h"
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
static const char * c5_debug_family_names[8] = { "h", "a", "nargin", "nargout",
  "nu", "nu_prev", "nu_dot_prev", "nu_dot" };

/* Function Declarations */
static void initialize_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance);
static void initialize_params_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance);
static void enable_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance);
static void disable_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance);
static void c5_update_debugger_state_c5_ctrl_student
  (SFc5_ctrl_studentInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_ctrl_student
  (SFc5_ctrl_studentInstanceStruct *chartInstance);
static void set_sim_state_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_st);
static void finalize_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance);
static void sf_gateway_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance);
static void initSimStructsc5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static void c5_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c5_nu_dot, const char_T *c5_identifier, real_T c5_y[3]);
static void c5_b_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[3]);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_c_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_info_helper(const mxArray **c5_info);
static const mxArray *c5_emlrt_marshallOut(const char * c5_u);
static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_d_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_e_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_ctrl_student, const char_T
  *c5_identifier);
static uint8_T c5_f_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_ctrl_studentInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance)
{
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_is_active_c5_ctrl_student = 0U;
}

static void initialize_params_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_ctrl_student
  (SFc5_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c5_ctrl_student
  (SFc5_ctrl_studentInstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  int32_T c5_i0;
  real_T c5_u[3];
  const mxArray *c5_b_y = NULL;
  uint8_T c5_hoistedGlobal;
  uint8_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  real_T (*c5_nu_dot)[3];
  c5_nu_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(2, 1), false);
  for (c5_i0 = 0; c5_i0 < 3; c5_i0++) {
    c5_u[c5_i0] = (*c5_nu_dot)[c5_i0];
  }

  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_hoistedGlobal = chartInstance->c5_is_active_c5_ctrl_student;
  c5_b_u = c5_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  real_T c5_dv0[3];
  int32_T c5_i1;
  real_T (*c5_nu_dot)[3];
  c5_nu_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 0)),
                      "nu_dot", c5_dv0);
  for (c5_i1 = 0; c5_i1 < 3; c5_i1++) {
    (*c5_nu_dot)[c5_i1] = c5_dv0[c5_i1];
  }

  chartInstance->c5_is_active_c5_ctrl_student = c5_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 1)),
     "is_active_c5_ctrl_student");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_ctrl_student(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance)
{
  int32_T c5_i2;
  int32_T c5_i3;
  real_T c5_nu[3];
  int32_T c5_i4;
  real_T c5_nu_prev[3];
  int32_T c5_i5;
  real_T c5_nu_dot_prev[3];
  uint32_T c5_debug_family_var_map[8];
  real_T c5_h;
  real_T c5_a;
  real_T c5_nargin = 3.0;
  real_T c5_nargout = 1.0;
  real_T c5_nu_dot[3];
  int32_T c5_i6;
  real_T c5_x[3];
  int32_T c5_i7;
  int32_T c5_i8;
  int32_T c5_i9;
  int32_T c5_i10;
  real_T c5_b[3];
  int32_T c5_i11;
  int32_T c5_i12;
  int32_T c5_i13;
  int32_T c5_i14;
  int32_T c5_i15;
  int32_T c5_i16;
  real_T (*c5_b_nu_dot)[3];
  real_T (*c5_b_nu_dot_prev)[3];
  real_T (*c5_b_nu_prev)[3];
  real_T (*c5_b_nu)[3];
  c5_b_nu_dot_prev = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c5_b_nu_prev = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c5_b_nu_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_b_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
  for (c5_i2 = 0; c5_i2 < 3; c5_i2++) {
    _SFD_DATA_RANGE_CHECK((*c5_b_nu)[c5_i2], 0U);
  }

  chartInstance->c5_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
  for (c5_i3 = 0; c5_i3 < 3; c5_i3++) {
    c5_nu[c5_i3] = (*c5_b_nu)[c5_i3];
  }

  for (c5_i4 = 0; c5_i4 < 3; c5_i4++) {
    c5_nu_prev[c5_i4] = (*c5_b_nu_prev)[c5_i4];
  }

  for (c5_i5 = 0; c5_i5 < 3; c5_i5++) {
    c5_nu_dot_prev[c5_i5] = (*c5_b_nu_dot_prev)[c5_i5];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_h, 0U, c5_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_a, 1U, c5_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 2U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 3U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_nu, 4U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_nu_prev, 5U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_nu_dot_prev, 6U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_nu_dot, 7U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 4);
  c5_h = 0.01;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 5);
  for (c5_i6 = 0; c5_i6 < 3; c5_i6++) {
    c5_x[c5_i6] = c5_nu[c5_i6] - c5_nu_prev[c5_i6];
  }

  for (c5_i7 = 0; c5_i7 < 3; c5_i7++) {
    c5_nu_dot[c5_i7] = c5_x[c5_i7] / 0.01;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 8);
  c5_a = 0.01;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 9);
  for (c5_i8 = 0; c5_i8 < 3; c5_i8++) {
    c5_x[c5_i8] = c5_nu_dot[c5_i8];
  }

  for (c5_i9 = 0; c5_i9 < 3; c5_i9++) {
    c5_x[c5_i9] *= 0.01;
  }

  for (c5_i10 = 0; c5_i10 < 3; c5_i10++) {
    c5_b[c5_i10] = c5_nu_dot_prev[c5_i10];
  }

  for (c5_i11 = 0; c5_i11 < 3; c5_i11++) {
    c5_b[c5_i11] *= 0.99;
  }

  for (c5_i12 = 0; c5_i12 < 3; c5_i12++) {
    c5_nu_dot[c5_i12] = c5_x[c5_i12] + c5_b[c5_i12];
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -9);
  _SFD_SYMBOL_SCOPE_POP();
  for (c5_i13 = 0; c5_i13 < 3; c5_i13++) {
    (*c5_b_nu_dot)[c5_i13] = c5_nu_dot[c5_i13];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ctrl_studentMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c5_i14 = 0; c5_i14 < 3; c5_i14++) {
    _SFD_DATA_RANGE_CHECK((*c5_b_nu_dot)[c5_i14], 1U);
  }

  for (c5_i15 = 0; c5_i15 < 3; c5_i15++) {
    _SFD_DATA_RANGE_CHECK((*c5_b_nu_prev)[c5_i15], 2U);
  }

  for (c5_i16 = 0; c5_i16 < 3; c5_i16++) {
    _SFD_DATA_RANGE_CHECK((*c5_b_nu_dot_prev)[c5_i16], 3U);
  }
}

static void initSimStructsc5_ctrl_student(SFc5_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  (void)c5_chartNumber;
  (void)c5_instanceNumber;
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i17;
  real_T c5_b_inData[3];
  int32_T c5_i18;
  real_T c5_u[3];
  const mxArray *c5_y = NULL;
  SFc5_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc5_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i17 = 0; c5_i17 < 3; c5_i17++) {
    c5_b_inData[c5_i17] = (*(real_T (*)[3])c5_inData)[c5_i17];
  }

  for (c5_i18 = 0; c5_i18 < 3; c5_i18++) {
    c5_u[c5_i18] = c5_b_inData[c5_i18];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c5_nu_dot, const char_T *c5_identifier, real_T c5_y[3])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nu_dot), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_nu_dot);
}

static void c5_b_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[3])
{
  real_T c5_dv1[3];
  int32_T c5_i19;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c5_i19 = 0; c5_i19 < 3; c5_i19++) {
    c5_y[c5_i19] = c5_dv1[c5_i19];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nu_dot;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[3];
  int32_T c5_i20;
  SFc5_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc5_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c5_nu_dot = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nu_dot), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_nu_dot);
  for (c5_i20 = 0; c5_i20 < 3; c5_i20++) {
    (*(real_T (*)[3])c5_outData)[c5_i20] = c5_y[c5_i20];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc5_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_c_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nargout;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc5_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c5_nargout = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_ctrl_student_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_createstruct("structure", 2, 7, 1),
                false);
  c5_info_helper(&c5_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c5_nameCaptureInfo);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(const mxArray **c5_info)
{
  const mxArray *c5_rhs0 = NULL;
  const mxArray *c5_lhs0 = NULL;
  const mxArray *c5_rhs1 = NULL;
  const mxArray *c5_lhs1 = NULL;
  const mxArray *c5_rhs2 = NULL;
  const mxArray *c5_lhs2 = NULL;
  const mxArray *c5_rhs3 = NULL;
  const mxArray *c5_lhs3 = NULL;
  const mxArray *c5_rhs4 = NULL;
  const mxArray *c5_lhs4 = NULL;
  const mxArray *c5_rhs5 = NULL;
  const mxArray *c5_lhs5 = NULL;
  const mxArray *c5_rhs6 = NULL;
  const mxArray *c5_lhs6 = NULL;
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("rdivide"), "name", "name", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c5_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c5_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c5_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_div"), "name", "name", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c5_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c5_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c5_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c5_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs6), "lhs", "lhs", 6);
  sf_mex_destroy(&c5_rhs0);
  sf_mex_destroy(&c5_lhs0);
  sf_mex_destroy(&c5_rhs1);
  sf_mex_destroy(&c5_lhs1);
  sf_mex_destroy(&c5_rhs2);
  sf_mex_destroy(&c5_lhs2);
  sf_mex_destroy(&c5_rhs3);
  sf_mex_destroy(&c5_lhs3);
  sf_mex_destroy(&c5_rhs4);
  sf_mex_destroy(&c5_lhs4);
  sf_mex_destroy(&c5_rhs5);
  sf_mex_destroy(&c5_lhs5);
  sf_mex_destroy(&c5_rhs6);
  sf_mex_destroy(&c5_lhs6);
}

static const mxArray *c5_emlrt_marshallOut(const char * c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c5_u)), false);
  return c5_y;
}

static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 7, 0U, 0U, 0U, 0), false);
  return c5_y;
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc5_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_d_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i21;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i21, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i21;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc5_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static uint8_T c5_e_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_ctrl_student, const char_T
  *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_is_active_c5_ctrl_student), &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_ctrl_student);
  return c5_y;
}

static uint8_T c5_f_emlrt_marshallIn(SFc5_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_ctrl_studentInstanceStruct *chartInstance)
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

void sf_c5_ctrl_student_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1166175643U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(650729457U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1529340963U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(651636980U);
}

mxArray *sf_c5_ctrl_student_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("jdGrjqJwghmegXjmyuldvF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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

mxArray *sf_c5_ctrl_student_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_ctrl_student_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c5_ctrl_student(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"nu_dot\",},{M[8],M[0],T\"is_active_c5_ctrl_student\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_ctrl_student_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_ctrl_studentInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_ctrl_studentInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ctrl_studentMachineNumber_,
           5,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"nu");
          _SFD_SET_DATA_PROPS(1,2,0,1,"nu_dot");
          _SFD_SET_DATA_PROPS(2,1,1,0,"nu_prev");
          _SFD_SET_DATA_PROPS(3,1,1,0,"nu_dot_prev");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,154);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)
            c5_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c5_nu)[3];
          real_T (*c5_nu_dot)[3];
          real_T (*c5_nu_prev)[3];
          real_T (*c5_nu_dot_prev)[3];
          c5_nu_dot_prev = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S,
            2);
          c5_nu_prev = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c5_nu_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c5_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c5_nu);
          _SFD_SET_DATA_VALUE_PTR(1U, *c5_nu_dot);
          _SFD_SET_DATA_VALUE_PTR(2U, *c5_nu_prev);
          _SFD_SET_DATA_VALUE_PTR(3U, *c5_nu_dot_prev);
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
  return "P0jPPb1SnH82d3mJNphXnG";
}

static void sf_opaque_initialize_c5_ctrl_student(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_ctrl_studentInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c5_ctrl_student((SFc5_ctrl_studentInstanceStruct*)
    chartInstanceVar);
  initialize_c5_ctrl_student((SFc5_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_ctrl_student(void *chartInstanceVar)
{
  enable_c5_ctrl_student((SFc5_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_ctrl_student(void *chartInstanceVar)
{
  disable_c5_ctrl_student((SFc5_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_ctrl_student(void *chartInstanceVar)
{
  sf_gateway_c5_ctrl_student((SFc5_ctrl_studentInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_ctrl_student(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_ctrl_student
    ((SFc5_ctrl_studentInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_ctrl_student();/* state var info */
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

extern void sf_internal_set_sim_state_c5_ctrl_student(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c5_ctrl_student();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_ctrl_student((SFc5_ctrl_studentInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_ctrl_student(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_ctrl_student(S);
}

static void sf_opaque_set_sim_state_c5_ctrl_student(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c5_ctrl_student(S, st);
}

static void sf_opaque_terminate_c5_ctrl_student(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_ctrl_studentInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ctrl_student_optimization_info();
    }

    finalize_c5_ctrl_student((SFc5_ctrl_studentInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_ctrl_student((SFc5_ctrl_studentInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_ctrl_student(SimStruct *S)
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
    initialize_params_c5_ctrl_student((SFc5_ctrl_studentInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ctrl_student_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1519212461U));
  ssSetChecksum1(S,(246536341U));
  ssSetChecksum2(S,(1880273436U));
  ssSetChecksum3(S,(2886309616U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_ctrl_student(SimStruct *S)
{
  SFc5_ctrl_studentInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc5_ctrl_studentInstanceStruct *)utMalloc(sizeof
    (SFc5_ctrl_studentInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_ctrl_studentInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_ctrl_student;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c5_ctrl_student;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_ctrl_student;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_ctrl_student;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_ctrl_student;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_ctrl_student;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_ctrl_student;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c5_ctrl_student;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_ctrl_student;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_ctrl_student;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_ctrl_student;
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

void c5_ctrl_student_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_ctrl_student(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_ctrl_student(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_ctrl_student(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_ctrl_student_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
