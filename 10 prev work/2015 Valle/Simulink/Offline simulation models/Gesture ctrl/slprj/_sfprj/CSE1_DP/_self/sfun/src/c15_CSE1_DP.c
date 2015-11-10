/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_DP_sfun.h"
#include "c15_CSE1_DP.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "CSE1_DP_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c15_debug_family_names[8] = { "u", "v", "r", "C_NL",
  "nargin", "nargout", "nu_hat", "C_nl" };

static const char * c15_b_debug_family_names[7] = { "t2", "nargin", "nargout",
  "u", "v", "r", "C" };

/* Function Declarations */
static void initialize_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance);
static void initialize_params_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct
  *chartInstance);
static void enable_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance);
static void disable_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance);
static void c15_update_debugger_state_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct
  *chartInstance);
static void set_sim_state_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_st);
static void finalize_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance);
static void sf_gateway_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance);
static void initSimStructsc15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c15_machineNumber, uint32_T
  c15_chartNumber, uint32_T c15_instanceNumber);
static const mxArray *c15_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData);
static void c15_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_C_nl, const char_T *c15_identifier, real_T c15_y[3]);
static void c15_b_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId, real_T c15_y[3]);
static void c15_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData);
static const mxArray *c15_b_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData);
static real_T c15_c_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId);
static void c15_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData);
static const mxArray *c15_c_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData);
static void c15_d_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId, real_T c15_y[9]);
static void c15_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData);
static void c15_info_helper(const mxArray **c15_info);
static const mxArray *c15_emlrt_marshallOut(const char * c15_u);
static const mxArray *c15_b_emlrt_marshallOut(const uint32_T c15_u);
static void c15_eml_scalar_eg(SFc15_CSE1_DPInstanceStruct *chartInstance);
static void c15_eml_xgemm(SFc15_CSE1_DPInstanceStruct *chartInstance, real_T
  c15_A[9], real_T c15_B[3], real_T c15_C[3], real_T c15_b_C[3]);
static const mxArray *c15_d_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData);
static int32_T c15_e_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId);
static void c15_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData);
static uint8_T c15_f_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_b_is_active_c15_CSE1_DP, const char_T *c15_identifier);
static uint8_T c15_g_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId);
static void c15_b_eml_xgemm(SFc15_CSE1_DPInstanceStruct *chartInstance, real_T
  c15_A[9], real_T c15_B[3], real_T c15_C[3]);
static void init_dsm_address_info(SFc15_CSE1_DPInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance)
{
  chartInstance->c15_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c15_is_active_c15_CSE1_DP = 0U;
}

static void initialize_params_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c15_update_debugger_state_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct
  *chartInstance)
{
  const mxArray *c15_st;
  const mxArray *c15_y = NULL;
  int32_T c15_i0;
  real_T c15_u[3];
  const mxArray *c15_b_y = NULL;
  uint8_T c15_hoistedGlobal;
  uint8_T c15_b_u;
  const mxArray *c15_c_y = NULL;
  real_T (*c15_C_nl)[3];
  c15_C_nl = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c15_st = NULL;
  c15_st = NULL;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_createcellmatrix(2, 1), false);
  for (c15_i0 = 0; c15_i0 < 3; c15_i0++) {
    c15_u[c15_i0] = (*c15_C_nl)[c15_i0];
  }

  c15_b_y = NULL;
  sf_mex_assign(&c15_b_y, sf_mex_create("y", c15_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c15_y, 0, c15_b_y);
  c15_hoistedGlobal = chartInstance->c15_is_active_c15_CSE1_DP;
  c15_b_u = c15_hoistedGlobal;
  c15_c_y = NULL;
  sf_mex_assign(&c15_c_y, sf_mex_create("y", &c15_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c15_y, 1, c15_c_y);
  sf_mex_assign(&c15_st, c15_y, false);
  return c15_st;
}

static void set_sim_state_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_st)
{
  const mxArray *c15_u;
  real_T c15_dv0[3];
  int32_T c15_i1;
  real_T (*c15_C_nl)[3];
  c15_C_nl = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c15_doneDoubleBufferReInit = true;
  c15_u = sf_mex_dup(c15_st);
  c15_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c15_u, 0)),
                       "C_nl", c15_dv0);
  for (c15_i1 = 0; c15_i1 < 3; c15_i1++) {
    (*c15_C_nl)[c15_i1] = c15_dv0[c15_i1];
  }

  chartInstance->c15_is_active_c15_CSE1_DP = c15_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c15_u, 1)),
     "is_active_c15_CSE1_DP");
  sf_mex_destroy(&c15_u);
  c15_update_debugger_state_c15_CSE1_DP(chartInstance);
  sf_mex_destroy(&c15_st);
}

static void finalize_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance)
{
  int32_T c15_i2;
  int32_T c15_i3;
  real_T c15_nu_hat[3];
  uint32_T c15_debug_family_var_map[8];
  real_T c15_u;
  real_T c15_v;
  real_T c15_r;
  real_T c15_C_NL[9];
  real_T c15_nargin = 1.0;
  real_T c15_nargout = 1.0;
  real_T c15_C_nl[3];
  real_T c15_b_u;
  real_T c15_b_v;
  real_T c15_b_r;
  uint32_T c15_b_debug_family_var_map[7];
  real_T c15_t2;
  real_T c15_b_nargin = 3.0;
  real_T c15_b_nargout = 1.0;
  real_T c15_x[9];
  int32_T c15_k;
  int32_T c15_b_k;
  int32_T c15_i4;
  real_T c15_a[9];
  int32_T c15_i5;
  real_T c15_b[3];
  int32_T c15_i6;
  int32_T c15_i7;
  int32_T c15_i8;
  real_T c15_dv1[9];
  int32_T c15_i9;
  real_T c15_dv2[3];
  int32_T c15_i10;
  real_T c15_dv3[9];
  int32_T c15_i11;
  real_T c15_dv4[3];
  int32_T c15_i12;
  int32_T c15_i13;
  real_T (*c15_b_C_nl)[3];
  real_T (*c15_b_nu_hat)[3];
  c15_b_C_nl = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c15_b_nu_hat = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 14U, chartInstance->c15_sfEvent);
  for (c15_i2 = 0; c15_i2 < 3; c15_i2++) {
    _SFD_DATA_RANGE_CHECK((*c15_b_nu_hat)[c15_i2], 0U);
  }

  chartInstance->c15_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 14U, chartInstance->c15_sfEvent);
  for (c15_i3 = 0; c15_i3 < 3; c15_i3++) {
    c15_nu_hat[c15_i3] = (*c15_b_nu_hat)[c15_i3];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c15_debug_family_names,
    c15_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_u, 0U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_v, 1U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_r, 2U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c15_C_NL, 3U, c15_c_sf_marshallOut,
    c15_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_nargin, 4U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_nargout, 5U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c15_nu_hat, 6U, c15_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c15_C_nl, 7U, c15_sf_marshallOut,
    c15_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 3);
  c15_u = c15_nu_hat[0];
  _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 4);
  c15_v = c15_nu_hat[1];
  _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 5);
  c15_r = c15_nu_hat[2];
  _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 7);
  c15_b_u = c15_u;
  c15_b_v = c15_v;
  c15_b_r = c15_r;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c15_b_debug_family_names,
    c15_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_t2, 0U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_b_nargin, 1U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_b_nargout, 2U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_b_u, 3U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_b_v, 4U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_b_r, 5U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c15_C_NL, 6U, c15_c_sf_marshallOut,
    c15_c_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c15_sfEvent, 8);
  c15_t2 = c15_b_u * 16.79;
  _SFD_SCRIPT_CALL(0U, chartInstance->c15_sfEvent, 9);
  c15_x[0] = 0.0;
  c15_x[1] = 0.0;
  c15_x[2] = c15_b_r * 0.554625 + c15_b_v * 24.79;
  c15_x[3] = 0.0;
  c15_x[4] = 0.0;
  c15_x[5] = -c15_t2;
  c15_x[6] = c15_b_r * -0.554625 - c15_b_v * 24.79;
  c15_x[7] = c15_t2;
  c15_x[8] = 0.0;
  for (c15_k = 1; c15_k < 10; c15_k++) {
    c15_b_k = c15_k;
    c15_C_NL[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c15_b_k), 1, 9, 1, 0) - 1] = c15_x[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c15_b_k), 1, 9, 1, 0) - 1];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c15_sfEvent, -9);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 9);
  for (c15_i4 = 0; c15_i4 < 9; c15_i4++) {
    c15_a[c15_i4] = c15_C_NL[c15_i4];
  }

  for (c15_i5 = 0; c15_i5 < 3; c15_i5++) {
    c15_b[c15_i5] = c15_nu_hat[c15_i5];
  }

  c15_eml_scalar_eg(chartInstance);
  c15_eml_scalar_eg(chartInstance);
  for (c15_i6 = 0; c15_i6 < 3; c15_i6++) {
    c15_C_nl[c15_i6] = 0.0;
  }

  for (c15_i7 = 0; c15_i7 < 3; c15_i7++) {
    c15_C_nl[c15_i7] = 0.0;
  }

  for (c15_i8 = 0; c15_i8 < 9; c15_i8++) {
    c15_dv1[c15_i8] = c15_a[c15_i8];
  }

  for (c15_i9 = 0; c15_i9 < 3; c15_i9++) {
    c15_dv2[c15_i9] = c15_b[c15_i9];
  }

  for (c15_i10 = 0; c15_i10 < 9; c15_i10++) {
    c15_dv3[c15_i10] = c15_dv1[c15_i10];
  }

  for (c15_i11 = 0; c15_i11 < 3; c15_i11++) {
    c15_dv4[c15_i11] = c15_dv2[c15_i11];
  }

  c15_b_eml_xgemm(chartInstance, c15_dv3, c15_dv4, c15_C_nl);
  _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, -9);
  _SFD_SYMBOL_SCOPE_POP();
  for (c15_i12 = 0; c15_i12 < 3; c15_i12++) {
    (*c15_b_C_nl)[c15_i12] = c15_C_nl[c15_i12];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c15_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_DPMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c15_i13 = 0; c15_i13 < 3; c15_i13++) {
    _SFD_DATA_RANGE_CHECK((*c15_b_C_nl)[c15_i13], 1U);
  }
}

static void initSimStructsc15_CSE1_DP(SFc15_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c15_machineNumber, uint32_T
  c15_chartNumber, uint32_T c15_instanceNumber)
{
  (void)c15_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c15_chartNumber, c15_instanceNumber, 0U,
    sf_debug_get_script_id(
    "C:\\Users\\Eirik Valle\\Dropbox\\NTNU\\Master\\Resultater\\Offline Simulation Results\\Gesture ctrl\\C.m"));
}

static const mxArray *c15_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData)
{
  const mxArray *c15_mxArrayOutData = NULL;
  int32_T c15_i14;
  real_T c15_b_inData[3];
  int32_T c15_i15;
  real_T c15_u[3];
  const mxArray *c15_y = NULL;
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c15_mxArrayOutData = NULL;
  for (c15_i14 = 0; c15_i14 < 3; c15_i14++) {
    c15_b_inData[c15_i14] = (*(real_T (*)[3])c15_inData)[c15_i14];
  }

  for (c15_i15 = 0; c15_i15 < 3; c15_i15++) {
    c15_u[c15_i15] = c15_b_inData[c15_i15];
  }

  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", c15_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c15_mxArrayOutData, c15_y, false);
  return c15_mxArrayOutData;
}

static void c15_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_C_nl, const char_T *c15_identifier, real_T c15_y[3])
{
  emlrtMsgIdentifier c15_thisId;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_C_nl), &c15_thisId, c15_y);
  sf_mex_destroy(&c15_C_nl);
}

static void c15_b_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId, real_T c15_y[3])
{
  real_T c15_dv5[3];
  int32_T c15_i16;
  (void)chartInstance;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), c15_dv5, 1, 0, 0U, 1, 0U, 1, 3);
  for (c15_i16 = 0; c15_i16 < 3; c15_i16++) {
    c15_y[c15_i16] = c15_dv5[c15_i16];
  }

  sf_mex_destroy(&c15_u);
}

static void c15_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData)
{
  const mxArray *c15_C_nl;
  const char_T *c15_identifier;
  emlrtMsgIdentifier c15_thisId;
  real_T c15_y[3];
  int32_T c15_i17;
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c15_C_nl = sf_mex_dup(c15_mxArrayInData);
  c15_identifier = c15_varName;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_C_nl), &c15_thisId, c15_y);
  sf_mex_destroy(&c15_C_nl);
  for (c15_i17 = 0; c15_i17 < 3; c15_i17++) {
    (*(real_T (*)[3])c15_outData)[c15_i17] = c15_y[c15_i17];
  }

  sf_mex_destroy(&c15_mxArrayInData);
}

static const mxArray *c15_b_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData)
{
  const mxArray *c15_mxArrayOutData = NULL;
  real_T c15_u;
  const mxArray *c15_y = NULL;
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c15_mxArrayOutData = NULL;
  c15_u = *(real_T *)c15_inData;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", &c15_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c15_mxArrayOutData, c15_y, false);
  return c15_mxArrayOutData;
}

static real_T c15_c_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId)
{
  real_T c15_y;
  real_T c15_d0;
  (void)chartInstance;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), &c15_d0, 1, 0, 0U, 0, 0U, 0);
  c15_y = c15_d0;
  sf_mex_destroy(&c15_u);
  return c15_y;
}

static void c15_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData)
{
  const mxArray *c15_nargout;
  const char_T *c15_identifier;
  emlrtMsgIdentifier c15_thisId;
  real_T c15_y;
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c15_nargout = sf_mex_dup(c15_mxArrayInData);
  c15_identifier = c15_varName;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_y = c15_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_nargout),
    &c15_thisId);
  sf_mex_destroy(&c15_nargout);
  *(real_T *)c15_outData = c15_y;
  sf_mex_destroy(&c15_mxArrayInData);
}

static const mxArray *c15_c_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData)
{
  const mxArray *c15_mxArrayOutData = NULL;
  int32_T c15_i18;
  int32_T c15_i19;
  int32_T c15_i20;
  real_T c15_b_inData[9];
  int32_T c15_i21;
  int32_T c15_i22;
  int32_T c15_i23;
  real_T c15_u[9];
  const mxArray *c15_y = NULL;
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c15_mxArrayOutData = NULL;
  c15_i18 = 0;
  for (c15_i19 = 0; c15_i19 < 3; c15_i19++) {
    for (c15_i20 = 0; c15_i20 < 3; c15_i20++) {
      c15_b_inData[c15_i20 + c15_i18] = (*(real_T (*)[9])c15_inData)[c15_i20 +
        c15_i18];
    }

    c15_i18 += 3;
  }

  c15_i21 = 0;
  for (c15_i22 = 0; c15_i22 < 3; c15_i22++) {
    for (c15_i23 = 0; c15_i23 < 3; c15_i23++) {
      c15_u[c15_i23 + c15_i21] = c15_b_inData[c15_i23 + c15_i21];
    }

    c15_i21 += 3;
  }

  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", c15_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c15_mxArrayOutData, c15_y, false);
  return c15_mxArrayOutData;
}

static void c15_d_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId, real_T c15_y[9])
{
  real_T c15_dv6[9];
  int32_T c15_i24;
  (void)chartInstance;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), c15_dv6, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c15_i24 = 0; c15_i24 < 9; c15_i24++) {
    c15_y[c15_i24] = c15_dv6[c15_i24];
  }

  sf_mex_destroy(&c15_u);
}

static void c15_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData)
{
  const mxArray *c15_C_NL;
  const char_T *c15_identifier;
  emlrtMsgIdentifier c15_thisId;
  real_T c15_y[9];
  int32_T c15_i25;
  int32_T c15_i26;
  int32_T c15_i27;
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c15_C_NL = sf_mex_dup(c15_mxArrayInData);
  c15_identifier = c15_varName;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_C_NL), &c15_thisId, c15_y);
  sf_mex_destroy(&c15_C_NL);
  c15_i25 = 0;
  for (c15_i26 = 0; c15_i26 < 3; c15_i26++) {
    for (c15_i27 = 0; c15_i27 < 3; c15_i27++) {
      (*(real_T (*)[9])c15_outData)[c15_i27 + c15_i25] = c15_y[c15_i27 + c15_i25];
    }

    c15_i25 += 3;
  }

  sf_mex_destroy(&c15_mxArrayInData);
}

const mxArray *sf_c15_CSE1_DP_get_eml_resolved_functions_info(void)
{
  const mxArray *c15_nameCaptureInfo = NULL;
  c15_nameCaptureInfo = NULL;
  sf_mex_assign(&c15_nameCaptureInfo, sf_mex_createstruct("structure", 2, 35, 1),
                false);
  c15_info_helper(&c15_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c15_nameCaptureInfo);
  return c15_nameCaptureInfo;
}

static void c15_info_helper(const mxArray **c15_info)
{
  const mxArray *c15_rhs0 = NULL;
  const mxArray *c15_lhs0 = NULL;
  const mxArray *c15_rhs1 = NULL;
  const mxArray *c15_lhs1 = NULL;
  const mxArray *c15_rhs2 = NULL;
  const mxArray *c15_lhs2 = NULL;
  const mxArray *c15_rhs3 = NULL;
  const mxArray *c15_lhs3 = NULL;
  const mxArray *c15_rhs4 = NULL;
  const mxArray *c15_lhs4 = NULL;
  const mxArray *c15_rhs5 = NULL;
  const mxArray *c15_lhs5 = NULL;
  const mxArray *c15_rhs6 = NULL;
  const mxArray *c15_lhs6 = NULL;
  const mxArray *c15_rhs7 = NULL;
  const mxArray *c15_lhs7 = NULL;
  const mxArray *c15_rhs8 = NULL;
  const mxArray *c15_lhs8 = NULL;
  const mxArray *c15_rhs9 = NULL;
  const mxArray *c15_lhs9 = NULL;
  const mxArray *c15_rhs10 = NULL;
  const mxArray *c15_lhs10 = NULL;
  const mxArray *c15_rhs11 = NULL;
  const mxArray *c15_lhs11 = NULL;
  const mxArray *c15_rhs12 = NULL;
  const mxArray *c15_lhs12 = NULL;
  const mxArray *c15_rhs13 = NULL;
  const mxArray *c15_lhs13 = NULL;
  const mxArray *c15_rhs14 = NULL;
  const mxArray *c15_lhs14 = NULL;
  const mxArray *c15_rhs15 = NULL;
  const mxArray *c15_lhs15 = NULL;
  const mxArray *c15_rhs16 = NULL;
  const mxArray *c15_lhs16 = NULL;
  const mxArray *c15_rhs17 = NULL;
  const mxArray *c15_lhs17 = NULL;
  const mxArray *c15_rhs18 = NULL;
  const mxArray *c15_lhs18 = NULL;
  const mxArray *c15_rhs19 = NULL;
  const mxArray *c15_lhs19 = NULL;
  const mxArray *c15_rhs20 = NULL;
  const mxArray *c15_lhs20 = NULL;
  const mxArray *c15_rhs21 = NULL;
  const mxArray *c15_lhs21 = NULL;
  const mxArray *c15_rhs22 = NULL;
  const mxArray *c15_lhs22 = NULL;
  const mxArray *c15_rhs23 = NULL;
  const mxArray *c15_lhs23 = NULL;
  const mxArray *c15_rhs24 = NULL;
  const mxArray *c15_lhs24 = NULL;
  const mxArray *c15_rhs25 = NULL;
  const mxArray *c15_lhs25 = NULL;
  const mxArray *c15_rhs26 = NULL;
  const mxArray *c15_lhs26 = NULL;
  const mxArray *c15_rhs27 = NULL;
  const mxArray *c15_lhs27 = NULL;
  const mxArray *c15_rhs28 = NULL;
  const mxArray *c15_lhs28 = NULL;
  const mxArray *c15_rhs29 = NULL;
  const mxArray *c15_lhs29 = NULL;
  const mxArray *c15_rhs30 = NULL;
  const mxArray *c15_lhs30 = NULL;
  const mxArray *c15_rhs31 = NULL;
  const mxArray *c15_lhs31 = NULL;
  const mxArray *c15_rhs32 = NULL;
  const mxArray *c15_lhs32 = NULL;
  const mxArray *c15_rhs33 = NULL;
  const mxArray *c15_lhs33 = NULL;
  const mxArray *c15_rhs34 = NULL;
  const mxArray *c15_lhs34 = NULL;
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("C"), "name", "name", 0);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[E]C:/Users/Eirik Valle/Dropbox/NTNU/Master/Resultater/Offline Simulation Results/Gesture ctrl/C.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1432485083U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c15_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[E]C:/Users/Eirik Valle/Dropbox/NTNU/Master/Resultater/Offline Simulation Results/Gesture ctrl/C.m"),
                  "context", "context", 1);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("reshape"), "name", "name", 1);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1378295982U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c15_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c15_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size"),
                  "context", "context", 3);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 3);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c15_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m!reshape_varargin_to_size"),
                  "context", "context", 4);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_assert_valid_size_arg"),
                  "name", "name", 4);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1368183030U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c15_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 5);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c15_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral"),
                  "context", "context", 6);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("isinf"), "name", "name", 6);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1363713856U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c15_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 7);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c15_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 8);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_is_integer_class"),
                  "name", "name", 8);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_integer_class.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1286818782U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c15_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 9);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("intmax"), "name", "name", 9);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c15_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 10);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c15_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 11);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("intmin"), "name", "name", 11);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 11);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c15_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 12);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 12);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c15_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 13);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "coder.internal.indexIntRelop"), "name", "name", 13);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1326728322U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c15_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!apply_float_relop"),
                  "context", "context", 14);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 14);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c15_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass"),
                  "context", "context", 15);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 15);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c15_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass"),
                  "context", "context", 16);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("intmin"), "name", "name", 16);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c15_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 17);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 17);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c15_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 18);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("intmax"), "name", "name", 18);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c15_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 19);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c15_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 20);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c15_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 21);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c15_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 22);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("intmax"), "name", "name", 22);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 22);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c15_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "context", "context", 23);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 23);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c15_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 24);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 24);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c15_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 25);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 25);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c15_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 26);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 26);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 26);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c15_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  27);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c15_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 28);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c15_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 29);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c15_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 30);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 30);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c15_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 31);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "coder.internal.blas.threshold"), "name", "name", 31);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c15_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 32);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 32);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c15_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 33);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 33);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c15_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 34);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "coder.internal.refblas.xgemm"), "name", "name", 34);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c15_info, c15_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c15_info, c15_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c15_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c15_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c15_info, sf_mex_duplicatearraysafe(&c15_lhs34), "lhs", "lhs",
                  34);
  sf_mex_destroy(&c15_rhs0);
  sf_mex_destroy(&c15_lhs0);
  sf_mex_destroy(&c15_rhs1);
  sf_mex_destroy(&c15_lhs1);
  sf_mex_destroy(&c15_rhs2);
  sf_mex_destroy(&c15_lhs2);
  sf_mex_destroy(&c15_rhs3);
  sf_mex_destroy(&c15_lhs3);
  sf_mex_destroy(&c15_rhs4);
  sf_mex_destroy(&c15_lhs4);
  sf_mex_destroy(&c15_rhs5);
  sf_mex_destroy(&c15_lhs5);
  sf_mex_destroy(&c15_rhs6);
  sf_mex_destroy(&c15_lhs6);
  sf_mex_destroy(&c15_rhs7);
  sf_mex_destroy(&c15_lhs7);
  sf_mex_destroy(&c15_rhs8);
  sf_mex_destroy(&c15_lhs8);
  sf_mex_destroy(&c15_rhs9);
  sf_mex_destroy(&c15_lhs9);
  sf_mex_destroy(&c15_rhs10);
  sf_mex_destroy(&c15_lhs10);
  sf_mex_destroy(&c15_rhs11);
  sf_mex_destroy(&c15_lhs11);
  sf_mex_destroy(&c15_rhs12);
  sf_mex_destroy(&c15_lhs12);
  sf_mex_destroy(&c15_rhs13);
  sf_mex_destroy(&c15_lhs13);
  sf_mex_destroy(&c15_rhs14);
  sf_mex_destroy(&c15_lhs14);
  sf_mex_destroy(&c15_rhs15);
  sf_mex_destroy(&c15_lhs15);
  sf_mex_destroy(&c15_rhs16);
  sf_mex_destroy(&c15_lhs16);
  sf_mex_destroy(&c15_rhs17);
  sf_mex_destroy(&c15_lhs17);
  sf_mex_destroy(&c15_rhs18);
  sf_mex_destroy(&c15_lhs18);
  sf_mex_destroy(&c15_rhs19);
  sf_mex_destroy(&c15_lhs19);
  sf_mex_destroy(&c15_rhs20);
  sf_mex_destroy(&c15_lhs20);
  sf_mex_destroy(&c15_rhs21);
  sf_mex_destroy(&c15_lhs21);
  sf_mex_destroy(&c15_rhs22);
  sf_mex_destroy(&c15_lhs22);
  sf_mex_destroy(&c15_rhs23);
  sf_mex_destroy(&c15_lhs23);
  sf_mex_destroy(&c15_rhs24);
  sf_mex_destroy(&c15_lhs24);
  sf_mex_destroy(&c15_rhs25);
  sf_mex_destroy(&c15_lhs25);
  sf_mex_destroy(&c15_rhs26);
  sf_mex_destroy(&c15_lhs26);
  sf_mex_destroy(&c15_rhs27);
  sf_mex_destroy(&c15_lhs27);
  sf_mex_destroy(&c15_rhs28);
  sf_mex_destroy(&c15_lhs28);
  sf_mex_destroy(&c15_rhs29);
  sf_mex_destroy(&c15_lhs29);
  sf_mex_destroy(&c15_rhs30);
  sf_mex_destroy(&c15_lhs30);
  sf_mex_destroy(&c15_rhs31);
  sf_mex_destroy(&c15_lhs31);
  sf_mex_destroy(&c15_rhs32);
  sf_mex_destroy(&c15_lhs32);
  sf_mex_destroy(&c15_rhs33);
  sf_mex_destroy(&c15_lhs33);
  sf_mex_destroy(&c15_rhs34);
  sf_mex_destroy(&c15_lhs34);
}

static const mxArray *c15_emlrt_marshallOut(const char * c15_u)
{
  const mxArray *c15_y = NULL;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", c15_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c15_u)), false);
  return c15_y;
}

static const mxArray *c15_b_emlrt_marshallOut(const uint32_T c15_u)
{
  const mxArray *c15_y = NULL;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", &c15_u, 7, 0U, 0U, 0U, 0), false);
  return c15_y;
}

static void c15_eml_scalar_eg(SFc15_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c15_eml_xgemm(SFc15_CSE1_DPInstanceStruct *chartInstance, real_T
  c15_A[9], real_T c15_B[3], real_T c15_C[3], real_T c15_b_C[3])
{
  int32_T c15_i28;
  int32_T c15_i29;
  real_T c15_b_A[9];
  int32_T c15_i30;
  real_T c15_b_B[3];
  for (c15_i28 = 0; c15_i28 < 3; c15_i28++) {
    c15_b_C[c15_i28] = c15_C[c15_i28];
  }

  for (c15_i29 = 0; c15_i29 < 9; c15_i29++) {
    c15_b_A[c15_i29] = c15_A[c15_i29];
  }

  for (c15_i30 = 0; c15_i30 < 3; c15_i30++) {
    c15_b_B[c15_i30] = c15_B[c15_i30];
  }

  c15_b_eml_xgemm(chartInstance, c15_b_A, c15_b_B, c15_b_C);
}

static const mxArray *c15_d_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData)
{
  const mxArray *c15_mxArrayOutData = NULL;
  int32_T c15_u;
  const mxArray *c15_y = NULL;
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c15_mxArrayOutData = NULL;
  c15_u = *(int32_T *)c15_inData;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", &c15_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c15_mxArrayOutData, c15_y, false);
  return c15_mxArrayOutData;
}

static int32_T c15_e_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId)
{
  int32_T c15_y;
  int32_T c15_i31;
  (void)chartInstance;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), &c15_i31, 1, 6, 0U, 0, 0U, 0);
  c15_y = c15_i31;
  sf_mex_destroy(&c15_u);
  return c15_y;
}

static void c15_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData)
{
  const mxArray *c15_b_sfEvent;
  const char_T *c15_identifier;
  emlrtMsgIdentifier c15_thisId;
  int32_T c15_y;
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c15_b_sfEvent = sf_mex_dup(c15_mxArrayInData);
  c15_identifier = c15_varName;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_y = c15_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_b_sfEvent),
    &c15_thisId);
  sf_mex_destroy(&c15_b_sfEvent);
  *(int32_T *)c15_outData = c15_y;
  sf_mex_destroy(&c15_mxArrayInData);
}

static uint8_T c15_f_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_b_is_active_c15_CSE1_DP, const char_T *c15_identifier)
{
  uint8_T c15_y;
  emlrtMsgIdentifier c15_thisId;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_y = c15_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c15_b_is_active_c15_CSE1_DP), &c15_thisId);
  sf_mex_destroy(&c15_b_is_active_c15_CSE1_DP);
  return c15_y;
}

static uint8_T c15_g_emlrt_marshallIn(SFc15_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId)
{
  uint8_T c15_y;
  uint8_T c15_u0;
  (void)chartInstance;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), &c15_u0, 1, 3, 0U, 0, 0U, 0);
  c15_y = c15_u0;
  sf_mex_destroy(&c15_u);
  return c15_y;
}

static void c15_b_eml_xgemm(SFc15_CSE1_DPInstanceStruct *chartInstance, real_T
  c15_A[9], real_T c15_B[3], real_T c15_C[3])
{
  int32_T c15_i32;
  int32_T c15_i33;
  int32_T c15_i34;
  (void)chartInstance;
  for (c15_i32 = 0; c15_i32 < 3; c15_i32++) {
    c15_C[c15_i32] = 0.0;
    c15_i33 = 0;
    for (c15_i34 = 0; c15_i34 < 3; c15_i34++) {
      c15_C[c15_i32] += c15_A[c15_i33 + c15_i32] * c15_B[c15_i34];
      c15_i33 += 3;
    }
  }
}

static void init_dsm_address_info(SFc15_CSE1_DPInstanceStruct *chartInstance)
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

void sf_c15_CSE1_DP_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4164728056U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4178643194U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3009390654U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2628411365U);
}

mxArray *sf_c15_CSE1_DP_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ZK6TE4kp1U5KyoO0l0jBP");
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

mxArray *sf_c15_CSE1_DP_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c15_CSE1_DP_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c15_CSE1_DP(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"C_nl\",},{M[8],M[0],T\"is_active_c15_CSE1_DP\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c15_CSE1_DP_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc15_CSE1_DPInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc15_CSE1_DPInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_DPMachineNumber_,
           15,
           1,
           1,
           0,
           2,
           0,
           0,
           0,
           0,
           1,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_CSE1_DPMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_CSE1_DPMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _CSE1_DPMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"nu_hat");
          _SFD_SET_DATA_PROPS(1,2,0,1,"C_nl");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,120);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"C",0,-1,266);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c15_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c15_sf_marshallOut,(MexInFcnForType)
            c15_sf_marshallIn);
        }

        {
          real_T (*c15_nu_hat)[3];
          real_T (*c15_C_nl)[3];
          c15_C_nl = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c15_nu_hat = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c15_nu_hat);
          _SFD_SET_DATA_VALUE_PTR(1U, *c15_C_nl);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _CSE1_DPMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "zDuNBMGwsGDRzRJmV9Vq7B";
}

static void sf_opaque_initialize_c15_CSE1_DP(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar);
  initialize_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c15_CSE1_DP(void *chartInstanceVar)
{
  enable_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c15_CSE1_DP(void *chartInstanceVar)
{
  disable_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c15_CSE1_DP(void *chartInstanceVar)
{
  sf_gateway_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c15_CSE1_DP(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c15_CSE1_DP();/* state var info */
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

extern void sf_internal_set_sim_state_c15_CSE1_DP(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c15_CSE1_DP();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c15_CSE1_DP(SimStruct* S)
{
  return sf_internal_get_sim_state_c15_CSE1_DP(S);
}

static void sf_opaque_set_sim_state_c15_CSE1_DP(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c15_CSE1_DP(S, st);
}

static void sf_opaque_terminate_c15_CSE1_DP(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_DP_optimization_info();
    }

    finalize_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c15_CSE1_DP(SimStruct *S)
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
    initialize_params_c15_CSE1_DP((SFc15_CSE1_DPInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c15_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_DP_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      15);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,15,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,15,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,15);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,15,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,15,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,15);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2463313165U));
  ssSetChecksum1(S,(3948850735U));
  ssSetChecksum2(S,(2175321894U));
  ssSetChecksum3(S,(915821120U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c15_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c15_CSE1_DP(SimStruct *S)
{
  SFc15_CSE1_DPInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc15_CSE1_DPInstanceStruct *)utMalloc(sizeof
    (SFc15_CSE1_DPInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc15_CSE1_DPInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c15_CSE1_DP;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c15_CSE1_DP;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c15_CSE1_DP;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c15_CSE1_DP;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c15_CSE1_DP;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c15_CSE1_DP;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c15_CSE1_DP;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c15_CSE1_DP;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c15_CSE1_DP;
  chartInstance->chartInfo.mdlStart = mdlStart_c15_CSE1_DP;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c15_CSE1_DP;
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

void c15_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c15_CSE1_DP(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c15_CSE1_DP(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c15_CSE1_DP(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c15_CSE1_DP_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
