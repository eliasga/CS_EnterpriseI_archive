/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ctrl_student_sfun.h"
#include "c7_ctrl_student.h"
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
static const char * c7_debug_family_names[4] = { "nargin", "nargout", "u", "y" };

/* Function Declarations */
static void initialize_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance);
static void initialize_params_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance);
static void enable_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance);
static void disable_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance);
static void c7_update_debugger_state_c7_ctrl_student
  (SFc7_ctrl_studentInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c7_ctrl_student
  (SFc7_ctrl_studentInstanceStruct *chartInstance);
static void set_sim_state_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_st);
static void finalize_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance);
static void sf_gateway_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance);
static void initSimStructsc7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber, uint32_T c7_instanceNumber);
static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData);
static void c7_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c7_y, const char_T *c7_identifier, real_T c7_b_y[4]);
static void c7_b_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[4]);
static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static real_T c7_c_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static void c7_info_helper(const mxArray **c7_info);
static const mxArray *c7_emlrt_marshallOut(const char * c7_u);
static const mxArray *c7_b_emlrt_marshallOut(const uint32_T c7_u);
static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static int32_T c7_d_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static uint8_T c7_e_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_b_is_active_c7_ctrl_student, const char_T
  *c7_identifier);
static uint8_T c7_f_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void init_dsm_address_info(SFc7_ctrl_studentInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance)
{
  chartInstance->c7_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c7_is_active_c7_ctrl_student = 0U;
}

static void initialize_params_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c7_update_debugger_state_c7_ctrl_student
  (SFc7_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c7_ctrl_student
  (SFc7_ctrl_studentInstanceStruct *chartInstance)
{
  const mxArray *c7_st;
  const mxArray *c7_y = NULL;
  int32_T c7_i0;
  real_T c7_u[4];
  const mxArray *c7_b_y = NULL;
  uint8_T c7_hoistedGlobal;
  uint8_T c7_b_u;
  const mxArray *c7_c_y = NULL;
  real_T (*c7_d_y)[4];
  c7_d_y = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_st = NULL;
  c7_st = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_createcellmatrix(2, 1), false);
  for (c7_i0 = 0; c7_i0 < 4; c7_i0++) {
    c7_u[c7_i0] = (*c7_d_y)[c7_i0];
  }

  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 2, 2), false);
  sf_mex_setcell(c7_y, 0, c7_b_y);
  c7_hoistedGlobal = chartInstance->c7_is_active_c7_ctrl_student;
  c7_b_u = c7_hoistedGlobal;
  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c7_y, 1, c7_c_y);
  sf_mex_assign(&c7_st, c7_y, false);
  return c7_st;
}

static void set_sim_state_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_st)
{
  const mxArray *c7_u;
  real_T c7_dv0[4];
  int32_T c7_i1;
  real_T (*c7_y)[4];
  c7_y = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c7_doneDoubleBufferReInit = true;
  c7_u = sf_mex_dup(c7_st);
  c7_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 0)), "y",
                      c7_dv0);
  for (c7_i1 = 0; c7_i1 < 4; c7_i1++) {
    (*c7_y)[c7_i1] = c7_dv0[c7_i1];
  }

  chartInstance->c7_is_active_c7_ctrl_student = c7_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 1)),
     "is_active_c7_ctrl_student");
  sf_mex_destroy(&c7_u);
  c7_update_debugger_state_c7_ctrl_student(chartInstance);
  sf_mex_destroy(&c7_st);
}

static void finalize_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance)
{
  int32_T c7_i2;
  int32_T c7_i3;
  real_T c7_u[2];
  uint32_T c7_debug_family_var_map[4];
  real_T c7_nargin = 1.0;
  real_T c7_nargout = 1.0;
  real_T c7_y[4];
  real_T c7_v[2];
  int32_T c7_i4;
  int32_T c7_j;
  int32_T c7_b_j;
  int32_T c7_i5;
  int32_T c7_i6;
  real_T (*c7_b_y)[4];
  real_T (*c7_b_u)[2];
  c7_b_y = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_b_u = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c7_sfEvent);
  for (c7_i2 = 0; c7_i2 < 2; c7_i2++) {
    _SFD_DATA_RANGE_CHECK((*c7_b_u)[c7_i2], 0U);
  }

  chartInstance->c7_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c7_sfEvent);
  for (c7_i3 = 0; c7_i3 < 2; c7_i3++) {
    c7_u[c7_i3] = (*c7_b_u)[c7_i3];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c7_debug_family_names,
    c7_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargin, 0U, c7_c_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargout, 1U, c7_c_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c7_u, 2U, c7_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_y, 3U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 4);
  c7_v[0] = c7_u[0];
  c7_v[1] = c7_u[1];
  for (c7_i4 = 0; c7_i4 < 4; c7_i4++) {
    c7_y[c7_i4] = 0.0;
  }

  for (c7_j = 1; c7_j < 3; c7_j++) {
    c7_b_j = c7_j;
    c7_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c7_b_j), 1, 2, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c7_b_j), 1, 2, 2, 0) - 1) <<
           1)) - 1] = c7_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c7_b_j), 1, 2, 1, 0) - 1];
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c7_i5 = 0; c7_i5 < 4; c7_i5++) {
    (*c7_b_y)[c7_i5] = c7_y[c7_i5];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c7_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ctrl_studentMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c7_i6 = 0; c7_i6 < 4; c7_i6++) {
    _SFD_DATA_RANGE_CHECK((*c7_b_y)[c7_i6], 1U);
  }
}

static void initSimStructsc7_ctrl_student(SFc7_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber, uint32_T c7_instanceNumber)
{
  (void)c7_machineNumber;
  (void)c7_chartNumber;
  (void)c7_instanceNumber;
}

static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i7;
  int32_T c7_i8;
  int32_T c7_i9;
  real_T c7_b_inData[4];
  int32_T c7_i10;
  int32_T c7_i11;
  int32_T c7_i12;
  real_T c7_u[4];
  const mxArray *c7_y = NULL;
  SFc7_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc7_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_i7 = 0;
  for (c7_i8 = 0; c7_i8 < 2; c7_i8++) {
    for (c7_i9 = 0; c7_i9 < 2; c7_i9++) {
      c7_b_inData[c7_i9 + c7_i7] = (*(real_T (*)[4])c7_inData)[c7_i9 + c7_i7];
    }

    c7_i7 += 2;
  }

  c7_i10 = 0;
  for (c7_i11 = 0; c7_i11 < 2; c7_i11++) {
    for (c7_i12 = 0; c7_i12 < 2; c7_i12++) {
      c7_u[c7_i12 + c7_i10] = c7_b_inData[c7_i12 + c7_i10];
    }

    c7_i10 += 2;
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 2, 2), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c7_y, const char_T *c7_identifier, real_T c7_b_y[4])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_y), &c7_thisId, c7_b_y);
  sf_mex_destroy(&c7_y);
}

static void c7_b_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[4])
{
  real_T c7_dv1[4];
  int32_T c7_i13;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv1, 1, 0, 0U, 1, 0U, 2, 2, 2);
  for (c7_i13 = 0; c7_i13 < 4; c7_i13++) {
    c7_y[c7_i13] = c7_dv1[c7_i13];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_y;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_b_y[4];
  int32_T c7_i14;
  int32_T c7_i15;
  int32_T c7_i16;
  SFc7_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc7_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c7_y = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_y), &c7_thisId, c7_b_y);
  sf_mex_destroy(&c7_y);
  c7_i14 = 0;
  for (c7_i15 = 0; c7_i15 < 2; c7_i15++) {
    for (c7_i16 = 0; c7_i16 < 2; c7_i16++) {
      (*(real_T (*)[4])c7_outData)[c7_i16 + c7_i14] = c7_b_y[c7_i16 + c7_i14];
    }

    c7_i14 += 2;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i17;
  real_T c7_b_inData[2];
  int32_T c7_i18;
  real_T c7_u[2];
  const mxArray *c7_y = NULL;
  SFc7_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc7_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i17 = 0; c7_i17 < 2; c7_i17++) {
    c7_b_inData[c7_i17] = (*(real_T (*)[2])c7_inData)[c7_i17];
  }

  for (c7_i18 = 0; c7_i18 < 2; c7_i18++) {
    c7_u[c7_i18] = c7_b_inData[c7_i18];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  real_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc7_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(real_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static real_T c7_c_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  real_T c7_y;
  real_T c7_d0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_d0, 1, 0, 0U, 0, 0U, 0);
  c7_y = c7_d0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_nargout;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y;
  SFc7_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc7_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c7_nargout = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_nargout), &c7_thisId);
  sf_mex_destroy(&c7_nargout);
  *(real_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

const mxArray *sf_c7_ctrl_student_get_eml_resolved_functions_info(void)
{
  const mxArray *c7_nameCaptureInfo = NULL;
  c7_nameCaptureInfo = NULL;
  sf_mex_assign(&c7_nameCaptureInfo, sf_mex_createstruct("structure", 2, 8, 1),
                false);
  c7_info_helper(&c7_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c7_nameCaptureInfo);
  return c7_nameCaptureInfo;
}

static void c7_info_helper(const mxArray **c7_info)
{
  const mxArray *c7_rhs0 = NULL;
  const mxArray *c7_lhs0 = NULL;
  const mxArray *c7_rhs1 = NULL;
  const mxArray *c7_lhs1 = NULL;
  const mxArray *c7_rhs2 = NULL;
  const mxArray *c7_lhs2 = NULL;
  const mxArray *c7_rhs3 = NULL;
  const mxArray *c7_lhs3 = NULL;
  const mxArray *c7_rhs4 = NULL;
  const mxArray *c7_lhs4 = NULL;
  const mxArray *c7_rhs5 = NULL;
  const mxArray *c7_lhs5 = NULL;
  const mxArray *c7_rhs6 = NULL;
  const mxArray *c7_lhs6 = NULL;
  const mxArray *c7_rhs7 = NULL;
  const mxArray *c7_lhs7 = NULL;
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("diag"), "name", "name", 0);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c7_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("ismatrix"), "name", "name", 1);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c7_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c7_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c7_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c7_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 5);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c7_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 6);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("intmax"), "name", "name", 6);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c7_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 7);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c7_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs7), "lhs", "lhs", 7);
  sf_mex_destroy(&c7_rhs0);
  sf_mex_destroy(&c7_lhs0);
  sf_mex_destroy(&c7_rhs1);
  sf_mex_destroy(&c7_lhs1);
  sf_mex_destroy(&c7_rhs2);
  sf_mex_destroy(&c7_lhs2);
  sf_mex_destroy(&c7_rhs3);
  sf_mex_destroy(&c7_lhs3);
  sf_mex_destroy(&c7_rhs4);
  sf_mex_destroy(&c7_lhs4);
  sf_mex_destroy(&c7_rhs5);
  sf_mex_destroy(&c7_lhs5);
  sf_mex_destroy(&c7_rhs6);
  sf_mex_destroy(&c7_lhs6);
  sf_mex_destroy(&c7_rhs7);
  sf_mex_destroy(&c7_lhs7);
}

static const mxArray *c7_emlrt_marshallOut(const char * c7_u)
{
  const mxArray *c7_y = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c7_u)), false);
  return c7_y;
}

static const mxArray *c7_b_emlrt_marshallOut(const uint32_T c7_u)
{
  const mxArray *c7_y = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 7, 0U, 0U, 0U, 0), false);
  return c7_y;
}

static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc7_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(int32_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static int32_T c7_d_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  int32_T c7_y;
  int32_T c7_i19;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_i19, 1, 6, 0U, 0, 0U, 0);
  c7_y = c7_i19;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_sfEvent;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  int32_T c7_y;
  SFc7_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc7_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c7_b_sfEvent = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_sfEvent),
    &c7_thisId);
  sf_mex_destroy(&c7_b_sfEvent);
  *(int32_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static uint8_T c7_e_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_b_is_active_c7_ctrl_student, const char_T
  *c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_b_is_active_c7_ctrl_student), &c7_thisId);
  sf_mex_destroy(&c7_b_is_active_c7_ctrl_student);
  return c7_y;
}

static uint8_T c7_f_emlrt_marshallIn(SFc7_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  uint8_T c7_u0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u0, 1, 3, 0U, 0, 0U, 0);
  c7_y = c7_u0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void init_dsm_address_info(SFc7_ctrl_studentInstanceStruct *chartInstance)
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

void sf_c7_ctrl_student_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(110028188U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(7005270U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1165230180U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3545298124U);
}

mxArray *sf_c7_ctrl_student_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("O6RV1w2T0R81FZkT2KRJTF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
      pr[1] = (double)(2);
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

mxArray *sf_c7_ctrl_student_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c7_ctrl_student_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c7_ctrl_student(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c7_ctrl_student\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c7_ctrl_student_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc7_ctrl_studentInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc7_ctrl_studentInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ctrl_studentMachineNumber_,
           7,
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,44);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)
            c7_sf_marshallIn);
        }

        {
          real_T (*c7_u)[2];
          real_T (*c7_y)[4];
          c7_y = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
          c7_u = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c7_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c7_y);
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
  return "mke04sqomXOEz2dL9xDVwD";
}

static void sf_opaque_initialize_c7_ctrl_student(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc7_ctrl_studentInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c7_ctrl_student((SFc7_ctrl_studentInstanceStruct*)
    chartInstanceVar);
  initialize_c7_ctrl_student((SFc7_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c7_ctrl_student(void *chartInstanceVar)
{
  enable_c7_ctrl_student((SFc7_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c7_ctrl_student(void *chartInstanceVar)
{
  disable_c7_ctrl_student((SFc7_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c7_ctrl_student(void *chartInstanceVar)
{
  sf_gateway_c7_ctrl_student((SFc7_ctrl_studentInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c7_ctrl_student(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c7_ctrl_student
    ((SFc7_ctrl_studentInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_ctrl_student();/* state var info */
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

extern void sf_internal_set_sim_state_c7_ctrl_student(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c7_ctrl_student();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c7_ctrl_student((SFc7_ctrl_studentInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c7_ctrl_student(SimStruct* S)
{
  return sf_internal_get_sim_state_c7_ctrl_student(S);
}

static void sf_opaque_set_sim_state_c7_ctrl_student(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c7_ctrl_student(S, st);
}

static void sf_opaque_terminate_c7_ctrl_student(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc7_ctrl_studentInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ctrl_student_optimization_info();
    }

    finalize_c7_ctrl_student((SFc7_ctrl_studentInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc7_ctrl_student((SFc7_ctrl_studentInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c7_ctrl_student(SimStruct *S)
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
    initialize_params_c7_ctrl_student((SFc7_ctrl_studentInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c7_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ctrl_student_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,7);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,7,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,7,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,7);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,7,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,7,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,7);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(761860673U));
  ssSetChecksum1(S,(2127052078U));
  ssSetChecksum2(S,(2297064723U));
  ssSetChecksum3(S,(1714368887U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c7_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c7_ctrl_student(SimStruct *S)
{
  SFc7_ctrl_studentInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc7_ctrl_studentInstanceStruct *)utMalloc(sizeof
    (SFc7_ctrl_studentInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc7_ctrl_studentInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c7_ctrl_student;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c7_ctrl_student;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c7_ctrl_student;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c7_ctrl_student;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c7_ctrl_student;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c7_ctrl_student;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c7_ctrl_student;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c7_ctrl_student;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c7_ctrl_student;
  chartInstance->chartInfo.mdlStart = mdlStart_c7_ctrl_student;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c7_ctrl_student;
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

void c7_ctrl_student_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c7_ctrl_student(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c7_ctrl_student(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c7_ctrl_student(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c7_ctrl_student_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
