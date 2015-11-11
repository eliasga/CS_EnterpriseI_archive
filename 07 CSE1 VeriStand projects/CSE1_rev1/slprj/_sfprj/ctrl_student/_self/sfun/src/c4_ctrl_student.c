/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ctrl_student_sfun.h"
#include "c4_ctrl_student.h"
#include "mwmathutil.h"
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
static const char * c4_debug_family_names[17] = { "b1", "b2", "a1", "a2", "s",
  "s_dot", "s_ddot", "nargin", "nargout", "t", "eta0", "u0", "xc", "yc", "pd",
  "pd_dot", "pd_ddot" };

/* Function Declarations */
static void initialize_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance);
static void initialize_params_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance);
static void enable_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance);
static void disable_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance);
static void c4_update_debugger_state_c4_ctrl_student
  (SFc4_ctrl_studentInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c4_ctrl_student
  (SFc4_ctrl_studentInstanceStruct *chartInstance);
static void set_sim_state_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_st);
static void finalize_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance);
static void sf_gateway_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance);
static void initSimStructsc4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static void c4_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c4_pd_ddot, const char_T *c4_identifier, real_T c4_y[2]);
static void c4_b_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2]);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_c_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(const mxArray **c4_info);
static const mxArray *c4_emlrt_marshallOut(const char * c4_u);
static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u);
static real_T c4_mpower(SFc4_ctrl_studentInstanceStruct *chartInstance, real_T
  c4_a);
static void c4_eml_scalar_eg(SFc4_ctrl_studentInstanceStruct *chartInstance);
static void c4_eml_error(SFc4_ctrl_studentInstanceStruct *chartInstance);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_d_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_e_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_ctrl_student, const char_T
  *c4_identifier);
static uint8_T c4_f_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_ctrl_studentInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_is_active_c4_ctrl_student = 0U;
}

static void initialize_params_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c4_update_debugger_state_c4_ctrl_student
  (SFc4_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c4_ctrl_student
  (SFc4_ctrl_studentInstanceStruct *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int32_T c4_i0;
  real_T c4_u[2];
  const mxArray *c4_b_y = NULL;
  int32_T c4_i1;
  real_T c4_b_u[2];
  const mxArray *c4_c_y = NULL;
  int32_T c4_i2;
  real_T c4_c_u[2];
  const mxArray *c4_d_y = NULL;
  uint8_T c4_hoistedGlobal;
  uint8_T c4_d_u;
  const mxArray *c4_e_y = NULL;
  real_T (*c4_pd_dot)[2];
  real_T (*c4_pd_ddot)[2];
  real_T (*c4_pd)[2];
  c4_pd_ddot = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c4_pd_dot = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_pd = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(4, 1), false);
  for (c4_i0 = 0; c4_i0 < 2; c4_i0++) {
    c4_u[c4_i0] = (*c4_pd)[c4_i0];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  for (c4_i1 = 0; c4_i1 < 2; c4_i1++) {
    c4_b_u[c4_i1] = (*c4_pd_ddot)[c4_i1];
  }

  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  for (c4_i2 = 0; c4_i2 < 2; c4_i2++) {
    c4_c_u[c4_i2] = (*c4_pd_dot)[c4_i2];
  }

  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", c4_c_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  c4_hoistedGlobal = chartInstance->c4_is_active_c4_ctrl_student;
  c4_d_u = c4_hoistedGlobal;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 3, c4_e_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv0[2];
  int32_T c4_i3;
  real_T c4_dv1[2];
  int32_T c4_i4;
  real_T c4_dv2[2];
  int32_T c4_i5;
  real_T (*c4_pd)[2];
  real_T (*c4_pd_ddot)[2];
  real_T (*c4_pd_dot)[2];
  c4_pd_ddot = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c4_pd_dot = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_pd = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = true;
  c4_u = sf_mex_dup(c4_st);
  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)), "pd",
                      c4_dv0);
  for (c4_i3 = 0; c4_i3 < 2; c4_i3++) {
    (*c4_pd)[c4_i3] = c4_dv0[c4_i3];
  }

  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
                      "pd_ddot", c4_dv1);
  for (c4_i4 = 0; c4_i4 < 2; c4_i4++) {
    (*c4_pd_ddot)[c4_i4] = c4_dv1[c4_i4];
  }

  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 2)),
                      "pd_dot", c4_dv2);
  for (c4_i5 = 0; c4_i5 < 2; c4_i5++) {
    (*c4_pd_dot)[c4_i5] = c4_dv2[c4_i5];
  }

  chartInstance->c4_is_active_c4_ctrl_student = c4_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 3)),
     "is_active_c4_ctrl_student");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_ctrl_student(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance)
{
  int32_T c4_i6;
  real_T c4_hoistedGlobal;
  real_T c4_b_hoistedGlobal;
  real_T c4_c_hoistedGlobal;
  real_T c4_d_hoistedGlobal;
  real_T c4_t;
  int32_T c4_i7;
  real_T c4_eta0[3];
  real_T c4_u0;
  real_T c4_xc;
  real_T c4_yc;
  uint32_T c4_debug_family_var_map[17];
  real_T c4_b1;
  real_T c4_b2;
  real_T c4_a1;
  real_T c4_a2;
  real_T c4_s;
  real_T c4_s_dot;
  real_T c4_s_ddot;
  real_T c4_nargin = 5.0;
  real_T c4_nargout = 3.0;
  real_T c4_pd[2];
  real_T c4_pd_dot[2];
  real_T c4_pd_ddot[2];
  real_T c4_x;
  real_T c4_b_x;
  real_T c4_A;
  real_T c4_B;
  real_T c4_c_x;
  real_T c4_y;
  real_T c4_d_x;
  real_T c4_b_y;
  real_T c4_e_x;
  real_T c4_c_y;
  real_T c4_f_x;
  real_T c4_g_x;
  real_T c4_b_A;
  real_T c4_b_B;
  real_T c4_h_x;
  real_T c4_d_y;
  real_T c4_i_x;
  real_T c4_e_y;
  real_T c4_j_x;
  real_T c4_f_y;
  int32_T c4_i8;
  int32_T c4_i9;
  int32_T c4_i10;
  int32_T c4_i11;
  int32_T c4_i12;
  int32_T c4_i13;
  real_T *c4_b_yc;
  real_T *c4_b_xc;
  real_T *c4_b_u0;
  real_T *c4_b_t;
  real_T (*c4_b_pd)[2];
  real_T (*c4_b_pd_dot)[2];
  real_T (*c4_b_pd_ddot)[2];
  real_T (*c4_b_eta0)[3];
  c4_b_yc = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c4_b_xc = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c4_b_pd_ddot = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c4_b_pd_dot = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_b_pd = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_u0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c4_b_eta0 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c4_b_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c4_b_t, 0U);
  for (c4_i6 = 0; c4_i6 < 3; c4_i6++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_eta0)[c4_i6], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c4_b_u0, 2U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *c4_b_t;
  c4_b_hoistedGlobal = *c4_b_u0;
  c4_c_hoistedGlobal = *c4_b_xc;
  c4_d_hoistedGlobal = *c4_b_yc;
  c4_t = c4_hoistedGlobal;
  for (c4_i7 = 0; c4_i7 < 3; c4_i7++) {
    c4_eta0[c4_i7] = (*c4_b_eta0)[c4_i7];
  }

  c4_u0 = c4_b_hoistedGlobal;
  c4_xc = c4_c_hoistedGlobal;
  c4_yc = c4_d_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 17U, 17U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b1, 0U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b2, 1U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_a1, 2U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_a2, 3U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_s, 4U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_s_dot, 5U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_s_ddot, 6U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 7U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 8U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_t, 9U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_eta0, 10U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_u0, 11U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_xc, 12U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_yc, 13U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_pd, 14U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_pd_dot, 15U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_pd_ddot, 16U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 9);
  c4_b1 = c4_eta0[0];
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 10);
  c4_b2 = c4_eta0[1];
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 11);
  c4_a1 = c4_xc - c4_b1;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 12);
  c4_a2 = c4_yc - c4_b2;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 15);
  c4_x = c4_mpower(chartInstance, c4_a1) + c4_mpower(chartInstance, c4_a2);
  c4_b_x = c4_x;
  if (c4_b_x < 0.0) {
    c4_eml_error(chartInstance);
  }

  c4_b_x = muDoubleScalarSqrt(c4_b_x);
  c4_A = c4_u0 * c4_t;
  c4_B = c4_b_x;
  c4_c_x = c4_A;
  c4_y = c4_B;
  c4_d_x = c4_c_x;
  c4_b_y = c4_y;
  c4_e_x = c4_d_x;
  c4_c_y = c4_b_y;
  c4_s = c4_e_x / c4_c_y;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 16);
  c4_f_x = c4_mpower(chartInstance, c4_a1) + c4_mpower(chartInstance, c4_a2);
  c4_g_x = c4_f_x;
  if (c4_g_x < 0.0) {
    c4_eml_error(chartInstance);
  }

  c4_g_x = muDoubleScalarSqrt(c4_g_x);
  c4_b_A = c4_u0;
  c4_b_B = c4_g_x;
  c4_h_x = c4_b_A;
  c4_d_y = c4_b_B;
  c4_i_x = c4_h_x;
  c4_e_y = c4_d_y;
  c4_j_x = c4_i_x;
  c4_f_y = c4_e_y;
  c4_s_dot = c4_j_x / c4_f_y;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 17);
  c4_s_ddot = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 21);
  c4_pd[0] = c4_a1 * c4_s + c4_b1;
  c4_pd[1] = c4_a2 * c4_s + c4_b2;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 23);
  c4_pd_dot[0] = c4_a1 * c4_s_dot;
  c4_pd_dot[1] = c4_a2 * c4_s_dot;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 25);
  c4_pd_ddot[0] = c4_a1 * 0.0;
  c4_pd_ddot[1] = c4_a2 * 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -25);
  _SFD_SYMBOL_SCOPE_POP();
  for (c4_i8 = 0; c4_i8 < 2; c4_i8++) {
    (*c4_b_pd)[c4_i8] = c4_pd[c4_i8];
  }

  for (c4_i9 = 0; c4_i9 < 2; c4_i9++) {
    (*c4_b_pd_dot)[c4_i9] = c4_pd_dot[c4_i9];
  }

  for (c4_i10 = 0; c4_i10 < 2; c4_i10++) {
    (*c4_b_pd_ddot)[c4_i10] = c4_pd_ddot[c4_i10];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ctrl_studentMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c4_i11 = 0; c4_i11 < 2; c4_i11++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_pd)[c4_i11], 3U);
  }

  for (c4_i12 = 0; c4_i12 < 2; c4_i12++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_pd_dot)[c4_i12], 4U);
  }

  for (c4_i13 = 0; c4_i13 < 2; c4_i13++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_pd_ddot)[c4_i13], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c4_b_xc, 6U);
  _SFD_DATA_RANGE_CHECK(*c4_b_yc, 7U);
}

static void initSimStructsc4_ctrl_student(SFc4_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)c4_machineNumber;
  (void)c4_chartNumber;
  (void)c4_instanceNumber;
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i14;
  real_T c4_b_inData[2];
  int32_T c4_i15;
  real_T c4_u[2];
  const mxArray *c4_y = NULL;
  SFc4_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc4_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i14 = 0; c4_i14 < 2; c4_i14++) {
    c4_b_inData[c4_i14] = (*(real_T (*)[2])c4_inData)[c4_i14];
  }

  for (c4_i15 = 0; c4_i15 < 2; c4_i15++) {
    c4_u[c4_i15] = c4_b_inData[c4_i15];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c4_pd_ddot, const char_T *c4_identifier, real_T c4_y[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_pd_ddot), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_pd_ddot);
}

static void c4_b_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2])
{
  real_T c4_dv3[2];
  int32_T c4_i16;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv3, 1, 0, 0U, 1, 0U, 1, 2);
  for (c4_i16 = 0; c4_i16 < 2; c4_i16++) {
    c4_y[c4_i16] = c4_dv3[c4_i16];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_pd_ddot;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[2];
  int32_T c4_i17;
  SFc4_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc4_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c4_pd_ddot = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_pd_ddot), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_pd_ddot);
  for (c4_i17 = 0; c4_i17 < 2; c4_i17++) {
    (*(real_T (*)[2])c4_outData)[c4_i17] = c4_y[c4_i17];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc4_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i18;
  real_T c4_b_inData[3];
  int32_T c4_i19;
  real_T c4_u[3];
  const mxArray *c4_y = NULL;
  SFc4_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc4_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i18 = 0; c4_i18 < 3; c4_i18++) {
    c4_b_inData[c4_i18] = (*(real_T (*)[3])c4_inData)[c4_i18];
  }

  for (c4_i19 = 0; c4_i19 < 3; c4_i19++) {
    c4_u[c4_i19] = c4_b_inData[c4_i19];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_c_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_nargout;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc4_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c4_nargout = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nargout), &c4_thisId);
  sf_mex_destroy(&c4_nargout);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_ctrl_student_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_createstruct("structure", 2, 23, 1),
                false);
  c4_info_helper(&c4_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs0 = NULL;
  const mxArray *c4_lhs0 = NULL;
  const mxArray *c4_rhs1 = NULL;
  const mxArray *c4_lhs1 = NULL;
  const mxArray *c4_rhs2 = NULL;
  const mxArray *c4_lhs2 = NULL;
  const mxArray *c4_rhs3 = NULL;
  const mxArray *c4_lhs3 = NULL;
  const mxArray *c4_rhs4 = NULL;
  const mxArray *c4_lhs4 = NULL;
  const mxArray *c4_rhs5 = NULL;
  const mxArray *c4_lhs5 = NULL;
  const mxArray *c4_rhs6 = NULL;
  const mxArray *c4_lhs6 = NULL;
  const mxArray *c4_rhs7 = NULL;
  const mxArray *c4_lhs7 = NULL;
  const mxArray *c4_rhs8 = NULL;
  const mxArray *c4_lhs8 = NULL;
  const mxArray *c4_rhs9 = NULL;
  const mxArray *c4_lhs9 = NULL;
  const mxArray *c4_rhs10 = NULL;
  const mxArray *c4_lhs10 = NULL;
  const mxArray *c4_rhs11 = NULL;
  const mxArray *c4_lhs11 = NULL;
  const mxArray *c4_rhs12 = NULL;
  const mxArray *c4_lhs12 = NULL;
  const mxArray *c4_rhs13 = NULL;
  const mxArray *c4_lhs13 = NULL;
  const mxArray *c4_rhs14 = NULL;
  const mxArray *c4_lhs14 = NULL;
  const mxArray *c4_rhs15 = NULL;
  const mxArray *c4_lhs15 = NULL;
  const mxArray *c4_rhs16 = NULL;
  const mxArray *c4_lhs16 = NULL;
  const mxArray *c4_rhs17 = NULL;
  const mxArray *c4_lhs17 = NULL;
  const mxArray *c4_rhs18 = NULL;
  const mxArray *c4_lhs18 = NULL;
  const mxArray *c4_rhs19 = NULL;
  const mxArray *c4_lhs19 = NULL;
  const mxArray *c4_rhs20 = NULL;
  const mxArray *c4_lhs20 = NULL;
  const mxArray *c4_rhs21 = NULL;
  const mxArray *c4_lhs21 = NULL;
  const mxArray *c4_rhs22 = NULL;
  const mxArray *c4_lhs22 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("mpower"), "name", "name", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c4_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c4_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("ismatrix"), "name", "name", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c4_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("power"), "name", "name", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c4_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c4_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c4_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c4_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c4_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c4_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("floor"), "name", "name", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c4_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c4_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c4_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c4_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("sqrt"), "name", "name", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c4_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_error"), "name", "name",
                  14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c4_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_sqrt"), "name",
                  "name", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286818738U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c4_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("mrdivide"), "name", "name", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c4_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c4_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("rdivide"), "name", "name", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c4_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c4_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c4_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_div"), "name", "name", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c4_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c4_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs22), "lhs", "lhs",
                  22);
  sf_mex_destroy(&c4_rhs0);
  sf_mex_destroy(&c4_lhs0);
  sf_mex_destroy(&c4_rhs1);
  sf_mex_destroy(&c4_lhs1);
  sf_mex_destroy(&c4_rhs2);
  sf_mex_destroy(&c4_lhs2);
  sf_mex_destroy(&c4_rhs3);
  sf_mex_destroy(&c4_lhs3);
  sf_mex_destroy(&c4_rhs4);
  sf_mex_destroy(&c4_lhs4);
  sf_mex_destroy(&c4_rhs5);
  sf_mex_destroy(&c4_lhs5);
  sf_mex_destroy(&c4_rhs6);
  sf_mex_destroy(&c4_lhs6);
  sf_mex_destroy(&c4_rhs7);
  sf_mex_destroy(&c4_lhs7);
  sf_mex_destroy(&c4_rhs8);
  sf_mex_destroy(&c4_lhs8);
  sf_mex_destroy(&c4_rhs9);
  sf_mex_destroy(&c4_lhs9);
  sf_mex_destroy(&c4_rhs10);
  sf_mex_destroy(&c4_lhs10);
  sf_mex_destroy(&c4_rhs11);
  sf_mex_destroy(&c4_lhs11);
  sf_mex_destroy(&c4_rhs12);
  sf_mex_destroy(&c4_lhs12);
  sf_mex_destroy(&c4_rhs13);
  sf_mex_destroy(&c4_lhs13);
  sf_mex_destroy(&c4_rhs14);
  sf_mex_destroy(&c4_lhs14);
  sf_mex_destroy(&c4_rhs15);
  sf_mex_destroy(&c4_lhs15);
  sf_mex_destroy(&c4_rhs16);
  sf_mex_destroy(&c4_lhs16);
  sf_mex_destroy(&c4_rhs17);
  sf_mex_destroy(&c4_lhs17);
  sf_mex_destroy(&c4_rhs18);
  sf_mex_destroy(&c4_lhs18);
  sf_mex_destroy(&c4_rhs19);
  sf_mex_destroy(&c4_lhs19);
  sf_mex_destroy(&c4_rhs20);
  sf_mex_destroy(&c4_lhs20);
  sf_mex_destroy(&c4_rhs21);
  sf_mex_destroy(&c4_lhs21);
  sf_mex_destroy(&c4_rhs22);
  sf_mex_destroy(&c4_lhs22);
}

static const mxArray *c4_emlrt_marshallOut(const char * c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c4_u)), false);
  return c4_y;
}

static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 7, 0U, 0U, 0U, 0), false);
  return c4_y;
}

static real_T c4_mpower(SFc4_ctrl_studentInstanceStruct *chartInstance, real_T
  c4_a)
{
  real_T c4_b_a;
  real_T c4_c_a;
  real_T c4_ak;
  real_T c4_d_a;
  c4_b_a = c4_a;
  c4_c_a = c4_b_a;
  c4_eml_scalar_eg(chartInstance);
  c4_ak = c4_c_a;
  c4_d_a = c4_ak;
  c4_eml_scalar_eg(chartInstance);
  return c4_d_a * c4_d_a;
}

static void c4_eml_scalar_eg(SFc4_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_eml_error(SFc4_ctrl_studentInstanceStruct *chartInstance)
{
  int32_T c4_i20;
  static char_T c4_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c4_u[30];
  const mxArray *c4_y = NULL;
  int32_T c4_i21;
  static char_T c4_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c4_b_u[4];
  const mxArray *c4_b_y = NULL;
  (void)chartInstance;
  for (c4_i20 = 0; c4_i20 < 30; c4_i20++) {
    c4_u[c4_i20] = c4_cv0[c4_i20];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  for (c4_i21 = 0; c4_i21 < 4; c4_i21++) {
    c4_b_u[c4_i21] = c4_cv1[c4_i21];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c4_y, 14, c4_b_y));
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc4_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_d_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i22;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i22, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i22;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc4_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_e_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_ctrl_student, const char_T
  *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_ctrl_student), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_ctrl_student);
  return c4_y;
}

static uint8_T c4_f_emlrt_marshallIn(SFc4_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_ctrl_studentInstanceStruct *chartInstance)
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

void sf_c4_ctrl_student_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(129389077U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2214895743U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2853148004U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1104941638U);
}

mxArray *sf_c4_ctrl_student_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("XFyKBGL7ahiub0AmbdbAkG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

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
      pr[0] = (double)(1);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_ctrl_student_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_ctrl_student_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c4_ctrl_student(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[7],T\"pd\",},{M[1],M[10],T\"pd_ddot\",},{M[1],M[9],T\"pd_dot\",},{M[8],M[0],T\"is_active_c4_ctrl_student\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_ctrl_student_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_ctrl_studentInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc4_ctrl_studentInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ctrl_studentMachineNumber_,
           4,
           1,
           1,
           0,
           8,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"t");
          _SFD_SET_DATA_PROPS(1,1,1,0,"eta0");
          _SFD_SET_DATA_PROPS(2,1,1,0,"u0");
          _SFD_SET_DATA_PROPS(3,2,0,1,"pd");
          _SFD_SET_DATA_PROPS(4,2,0,1,"pd_dot");
          _SFD_SET_DATA_PROPS(5,2,0,1,"pd_ddot");
          _SFD_SET_DATA_PROPS(6,1,1,0,"xc");
          _SFD_SET_DATA_PROPS(7,1,1,0,"yc");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,431);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)
            c4_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)
            c4_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)
            c4_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c4_t;
          real_T *c4_u0;
          real_T *c4_xc;
          real_T *c4_yc;
          real_T (*c4_eta0)[3];
          real_T (*c4_pd)[2];
          real_T (*c4_pd_dot)[2];
          real_T (*c4_pd_ddot)[2];
          c4_yc = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c4_xc = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c4_pd_ddot = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
          c4_pd_dot = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
          c4_pd = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
          c4_u0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c4_eta0 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c4_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c4_t);
          _SFD_SET_DATA_VALUE_PTR(1U, *c4_eta0);
          _SFD_SET_DATA_VALUE_PTR(2U, c4_u0);
          _SFD_SET_DATA_VALUE_PTR(3U, *c4_pd);
          _SFD_SET_DATA_VALUE_PTR(4U, *c4_pd_dot);
          _SFD_SET_DATA_VALUE_PTR(5U, *c4_pd_ddot);
          _SFD_SET_DATA_VALUE_PTR(6U, c4_xc);
          _SFD_SET_DATA_VALUE_PTR(7U, c4_yc);
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
  return "9Mrk5M32038NYyt2uLa10E";
}

static void sf_opaque_initialize_c4_ctrl_student(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_ctrl_studentInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c4_ctrl_student((SFc4_ctrl_studentInstanceStruct*)
    chartInstanceVar);
  initialize_c4_ctrl_student((SFc4_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_ctrl_student(void *chartInstanceVar)
{
  enable_c4_ctrl_student((SFc4_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_ctrl_student(void *chartInstanceVar)
{
  disable_c4_ctrl_student((SFc4_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_ctrl_student(void *chartInstanceVar)
{
  sf_gateway_c4_ctrl_student((SFc4_ctrl_studentInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_ctrl_student(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_ctrl_student
    ((SFc4_ctrl_studentInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_ctrl_student();/* state var info */
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

extern void sf_internal_set_sim_state_c4_ctrl_student(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c4_ctrl_student();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_ctrl_student((SFc4_ctrl_studentInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_ctrl_student(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_ctrl_student(S);
}

static void sf_opaque_set_sim_state_c4_ctrl_student(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c4_ctrl_student(S, st);
}

static void sf_opaque_terminate_c4_ctrl_student(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_ctrl_studentInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ctrl_student_optimization_info();
    }

    finalize_c4_ctrl_student((SFc4_ctrl_studentInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_ctrl_student((SFc4_ctrl_studentInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_ctrl_student(SimStruct *S)
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
    initialize_params_c4_ctrl_student((SFc4_ctrl_studentInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ctrl_student_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2973180294U));
  ssSetChecksum1(S,(1190893594U));
  ssSetChecksum2(S,(3780874628U));
  ssSetChecksum3(S,(4168803194U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_ctrl_student(SimStruct *S)
{
  SFc4_ctrl_studentInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc4_ctrl_studentInstanceStruct *)utMalloc(sizeof
    (SFc4_ctrl_studentInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_ctrl_studentInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_ctrl_student;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_ctrl_student;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_ctrl_student;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_ctrl_student;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_ctrl_student;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_ctrl_student;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_ctrl_student;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_ctrl_student;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_ctrl_student;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_ctrl_student;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_ctrl_student;
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

void c4_ctrl_student_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_ctrl_student(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_ctrl_student(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_ctrl_student(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_ctrl_student_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
