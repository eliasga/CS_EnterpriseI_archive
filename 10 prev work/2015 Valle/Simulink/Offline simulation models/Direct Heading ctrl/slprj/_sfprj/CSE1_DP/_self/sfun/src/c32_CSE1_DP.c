/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_DP_sfun.h"
#include "c32_CSE1_DP.h"
#include "mwmathutil.h"
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
static const char * c32_debug_family_names[6] = { "R_inv", "nargin", "nargout",
  "eta_dot", "psi", "nu" };

/* Function Declarations */
static void initialize_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance);
static void initialize_params_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct
  *chartInstance);
static void enable_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance);
static void disable_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance);
static void c32_update_debugger_state_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct
  *chartInstance);
static void set_sim_state_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_st);
static void finalize_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance);
static void sf_gateway_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance);
static void initSimStructsc32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c32_machineNumber, uint32_T
  c32_chartNumber, uint32_T c32_instanceNumber);
static const mxArray *c32_sf_marshallOut(void *chartInstanceVoid, void
  *c32_inData);
static void c32_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_nu, const char_T *c32_identifier, real_T c32_y[3]);
static void c32_b_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId, real_T c32_y[3]);
static void c32_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c32_mxArrayInData, const char_T *c32_varName, void *c32_outData);
static const mxArray *c32_b_sf_marshallOut(void *chartInstanceVoid, void
  *c32_inData);
static real_T c32_c_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId);
static void c32_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c32_mxArrayInData, const char_T *c32_varName, void *c32_outData);
static const mxArray *c32_c_sf_marshallOut(void *chartInstanceVoid, void
  *c32_inData);
static void c32_d_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId, real_T c32_y[9]);
static void c32_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c32_mxArrayInData, const char_T *c32_varName, void *c32_outData);
static void c32_info_helper(const mxArray **c32_info);
static const mxArray *c32_emlrt_marshallOut(const char * c32_u);
static const mxArray *c32_b_emlrt_marshallOut(const uint32_T c32_u);
static void c32_eml_scalar_eg(SFc32_CSE1_DPInstanceStruct *chartInstance);
static void c32_eml_xgemm(SFc32_CSE1_DPInstanceStruct *chartInstance, real_T
  c32_A[9], real_T c32_B[3], real_T c32_C[3], real_T c32_b_C[3]);
static const mxArray *c32_d_sf_marshallOut(void *chartInstanceVoid, void
  *c32_inData);
static int32_T c32_e_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId);
static void c32_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c32_mxArrayInData, const char_T *c32_varName, void *c32_outData);
static uint8_T c32_f_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_b_is_active_c32_CSE1_DP, const char_T *c32_identifier);
static uint8_T c32_g_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId);
static void c32_b_eml_xgemm(SFc32_CSE1_DPInstanceStruct *chartInstance, real_T
  c32_A[9], real_T c32_B[3], real_T c32_C[3]);
static void init_dsm_address_info(SFc32_CSE1_DPInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance)
{
  chartInstance->c32_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c32_is_active_c32_CSE1_DP = 0U;
}

static void initialize_params_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c32_update_debugger_state_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct
  *chartInstance)
{
  const mxArray *c32_st;
  const mxArray *c32_y = NULL;
  int32_T c32_i0;
  real_T c32_u[3];
  const mxArray *c32_b_y = NULL;
  uint8_T c32_hoistedGlobal;
  uint8_T c32_b_u;
  const mxArray *c32_c_y = NULL;
  real_T (*c32_nu)[3];
  c32_nu = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c32_st = NULL;
  c32_st = NULL;
  c32_y = NULL;
  sf_mex_assign(&c32_y, sf_mex_createcellmatrix(2, 1), false);
  for (c32_i0 = 0; c32_i0 < 3; c32_i0++) {
    c32_u[c32_i0] = (*c32_nu)[c32_i0];
  }

  c32_b_y = NULL;
  sf_mex_assign(&c32_b_y, sf_mex_create("y", c32_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c32_y, 0, c32_b_y);
  c32_hoistedGlobal = chartInstance->c32_is_active_c32_CSE1_DP;
  c32_b_u = c32_hoistedGlobal;
  c32_c_y = NULL;
  sf_mex_assign(&c32_c_y, sf_mex_create("y", &c32_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c32_y, 1, c32_c_y);
  sf_mex_assign(&c32_st, c32_y, false);
  return c32_st;
}

static void set_sim_state_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_st)
{
  const mxArray *c32_u;
  real_T c32_dv0[3];
  int32_T c32_i1;
  real_T (*c32_nu)[3];
  c32_nu = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c32_doneDoubleBufferReInit = true;
  c32_u = sf_mex_dup(c32_st);
  c32_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c32_u, 0)), "nu",
                       c32_dv0);
  for (c32_i1 = 0; c32_i1 < 3; c32_i1++) {
    (*c32_nu)[c32_i1] = c32_dv0[c32_i1];
  }

  chartInstance->c32_is_active_c32_CSE1_DP = c32_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c32_u, 1)),
     "is_active_c32_CSE1_DP");
  sf_mex_destroy(&c32_u);
  c32_update_debugger_state_c32_CSE1_DP(chartInstance);
  sf_mex_destroy(&c32_st);
}

static void finalize_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance)
{
  int32_T c32_i2;
  real_T c32_hoistedGlobal;
  int32_T c32_i3;
  real_T c32_eta_dot[3];
  real_T c32_psi;
  uint32_T c32_debug_family_var_map[6];
  real_T c32_R_inv[9];
  real_T c32_nargin = 2.0;
  real_T c32_nargout = 1.0;
  real_T c32_nu[3];
  real_T c32_x;
  real_T c32_b_x;
  real_T c32_c_x;
  real_T c32_d_x;
  real_T c32_e_x;
  real_T c32_f_x;
  real_T c32_g_x;
  real_T c32_h_x;
  int32_T c32_i4;
  int32_T c32_i5;
  static real_T c32_dv1[3] = { 0.0, 0.0, 1.0 };

  int32_T c32_i6;
  real_T c32_a[9];
  int32_T c32_i7;
  real_T c32_b[3];
  int32_T c32_i8;
  int32_T c32_i9;
  int32_T c32_i10;
  real_T c32_dv2[9];
  int32_T c32_i11;
  real_T c32_dv3[3];
  int32_T c32_i12;
  real_T c32_dv4[9];
  int32_T c32_i13;
  real_T c32_dv5[3];
  int32_T c32_i14;
  int32_T c32_i15;
  real_T *c32_b_psi;
  real_T (*c32_b_nu)[3];
  real_T (*c32_b_eta_dot)[3];
  c32_b_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c32_b_nu = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c32_b_eta_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 28U, chartInstance->c32_sfEvent);
  for (c32_i2 = 0; c32_i2 < 3; c32_i2++) {
    _SFD_DATA_RANGE_CHECK((*c32_b_eta_dot)[c32_i2], 0U);
  }

  chartInstance->c32_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 28U, chartInstance->c32_sfEvent);
  c32_hoistedGlobal = *c32_b_psi;
  for (c32_i3 = 0; c32_i3 < 3; c32_i3++) {
    c32_eta_dot[c32_i3] = (*c32_b_eta_dot)[c32_i3];
  }

  c32_psi = c32_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c32_debug_family_names,
    c32_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c32_R_inv, 0U, c32_c_sf_marshallOut,
    c32_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c32_nargin, 1U, c32_b_sf_marshallOut,
    c32_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c32_nargout, 2U, c32_b_sf_marshallOut,
    c32_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c32_eta_dot, 3U, c32_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c32_psi, 4U, c32_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c32_nu, 5U, c32_sf_marshallOut,
    c32_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c32_sfEvent, 3);
  c32_x = c32_psi;
  c32_b_x = c32_x;
  c32_b_x = muDoubleScalarCos(c32_b_x);
  c32_c_x = c32_psi;
  c32_d_x = c32_c_x;
  c32_d_x = muDoubleScalarSin(c32_d_x);
  c32_e_x = c32_psi;
  c32_f_x = c32_e_x;
  c32_f_x = muDoubleScalarSin(c32_f_x);
  c32_g_x = c32_psi;
  c32_h_x = c32_g_x;
  c32_h_x = muDoubleScalarCos(c32_h_x);
  c32_R_inv[0] = c32_b_x;
  c32_R_inv[3] = c32_d_x;
  c32_R_inv[6] = 0.0;
  c32_R_inv[1] = -c32_f_x;
  c32_R_inv[4] = c32_h_x;
  c32_R_inv[7] = 0.0;
  c32_i4 = 0;
  for (c32_i5 = 0; c32_i5 < 3; c32_i5++) {
    c32_R_inv[c32_i4 + 2] = c32_dv1[c32_i5];
    c32_i4 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c32_sfEvent, 6);
  for (c32_i6 = 0; c32_i6 < 9; c32_i6++) {
    c32_a[c32_i6] = c32_R_inv[c32_i6];
  }

  for (c32_i7 = 0; c32_i7 < 3; c32_i7++) {
    c32_b[c32_i7] = c32_eta_dot[c32_i7];
  }

  c32_eml_scalar_eg(chartInstance);
  c32_eml_scalar_eg(chartInstance);
  for (c32_i8 = 0; c32_i8 < 3; c32_i8++) {
    c32_nu[c32_i8] = 0.0;
  }

  for (c32_i9 = 0; c32_i9 < 3; c32_i9++) {
    c32_nu[c32_i9] = 0.0;
  }

  for (c32_i10 = 0; c32_i10 < 9; c32_i10++) {
    c32_dv2[c32_i10] = c32_a[c32_i10];
  }

  for (c32_i11 = 0; c32_i11 < 3; c32_i11++) {
    c32_dv3[c32_i11] = c32_b[c32_i11];
  }

  for (c32_i12 = 0; c32_i12 < 9; c32_i12++) {
    c32_dv4[c32_i12] = c32_dv2[c32_i12];
  }

  for (c32_i13 = 0; c32_i13 < 3; c32_i13++) {
    c32_dv5[c32_i13] = c32_dv3[c32_i13];
  }

  c32_b_eml_xgemm(chartInstance, c32_dv4, c32_dv5, c32_nu);
  _SFD_EML_CALL(0U, chartInstance->c32_sfEvent, -6);
  _SFD_SYMBOL_SCOPE_POP();
  for (c32_i14 = 0; c32_i14 < 3; c32_i14++) {
    (*c32_b_nu)[c32_i14] = c32_nu[c32_i14];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 28U, chartInstance->c32_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_DPMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c32_i15 = 0; c32_i15 < 3; c32_i15++) {
    _SFD_DATA_RANGE_CHECK((*c32_b_nu)[c32_i15], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c32_b_psi, 2U);
}

static void initSimStructsc32_CSE1_DP(SFc32_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c32_machineNumber, uint32_T
  c32_chartNumber, uint32_T c32_instanceNumber)
{
  (void)c32_machineNumber;
  (void)c32_chartNumber;
  (void)c32_instanceNumber;
}

static const mxArray *c32_sf_marshallOut(void *chartInstanceVoid, void
  *c32_inData)
{
  const mxArray *c32_mxArrayOutData = NULL;
  int32_T c32_i16;
  real_T c32_b_inData[3];
  int32_T c32_i17;
  real_T c32_u[3];
  const mxArray *c32_y = NULL;
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c32_mxArrayOutData = NULL;
  for (c32_i16 = 0; c32_i16 < 3; c32_i16++) {
    c32_b_inData[c32_i16] = (*(real_T (*)[3])c32_inData)[c32_i16];
  }

  for (c32_i17 = 0; c32_i17 < 3; c32_i17++) {
    c32_u[c32_i17] = c32_b_inData[c32_i17];
  }

  c32_y = NULL;
  sf_mex_assign(&c32_y, sf_mex_create("y", c32_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c32_mxArrayOutData, c32_y, false);
  return c32_mxArrayOutData;
}

static void c32_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_nu, const char_T *c32_identifier, real_T c32_y[3])
{
  emlrtMsgIdentifier c32_thisId;
  c32_thisId.fIdentifier = c32_identifier;
  c32_thisId.fParent = NULL;
  c32_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c32_nu), &c32_thisId, c32_y);
  sf_mex_destroy(&c32_nu);
}

static void c32_b_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId, real_T c32_y[3])
{
  real_T c32_dv6[3];
  int32_T c32_i18;
  (void)chartInstance;
  sf_mex_import(c32_parentId, sf_mex_dup(c32_u), c32_dv6, 1, 0, 0U, 1, 0U, 1, 3);
  for (c32_i18 = 0; c32_i18 < 3; c32_i18++) {
    c32_y[c32_i18] = c32_dv6[c32_i18];
  }

  sf_mex_destroy(&c32_u);
}

static void c32_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c32_mxArrayInData, const char_T *c32_varName, void *c32_outData)
{
  const mxArray *c32_nu;
  const char_T *c32_identifier;
  emlrtMsgIdentifier c32_thisId;
  real_T c32_y[3];
  int32_T c32_i19;
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c32_nu = sf_mex_dup(c32_mxArrayInData);
  c32_identifier = c32_varName;
  c32_thisId.fIdentifier = c32_identifier;
  c32_thisId.fParent = NULL;
  c32_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c32_nu), &c32_thisId, c32_y);
  sf_mex_destroy(&c32_nu);
  for (c32_i19 = 0; c32_i19 < 3; c32_i19++) {
    (*(real_T (*)[3])c32_outData)[c32_i19] = c32_y[c32_i19];
  }

  sf_mex_destroy(&c32_mxArrayInData);
}

static const mxArray *c32_b_sf_marshallOut(void *chartInstanceVoid, void
  *c32_inData)
{
  const mxArray *c32_mxArrayOutData = NULL;
  real_T c32_u;
  const mxArray *c32_y = NULL;
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c32_mxArrayOutData = NULL;
  c32_u = *(real_T *)c32_inData;
  c32_y = NULL;
  sf_mex_assign(&c32_y, sf_mex_create("y", &c32_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c32_mxArrayOutData, c32_y, false);
  return c32_mxArrayOutData;
}

static real_T c32_c_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId)
{
  real_T c32_y;
  real_T c32_d0;
  (void)chartInstance;
  sf_mex_import(c32_parentId, sf_mex_dup(c32_u), &c32_d0, 1, 0, 0U, 0, 0U, 0);
  c32_y = c32_d0;
  sf_mex_destroy(&c32_u);
  return c32_y;
}

static void c32_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c32_mxArrayInData, const char_T *c32_varName, void *c32_outData)
{
  const mxArray *c32_nargout;
  const char_T *c32_identifier;
  emlrtMsgIdentifier c32_thisId;
  real_T c32_y;
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c32_nargout = sf_mex_dup(c32_mxArrayInData);
  c32_identifier = c32_varName;
  c32_thisId.fIdentifier = c32_identifier;
  c32_thisId.fParent = NULL;
  c32_y = c32_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c32_nargout),
    &c32_thisId);
  sf_mex_destroy(&c32_nargout);
  *(real_T *)c32_outData = c32_y;
  sf_mex_destroy(&c32_mxArrayInData);
}

static const mxArray *c32_c_sf_marshallOut(void *chartInstanceVoid, void
  *c32_inData)
{
  const mxArray *c32_mxArrayOutData = NULL;
  int32_T c32_i20;
  int32_T c32_i21;
  int32_T c32_i22;
  real_T c32_b_inData[9];
  int32_T c32_i23;
  int32_T c32_i24;
  int32_T c32_i25;
  real_T c32_u[9];
  const mxArray *c32_y = NULL;
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c32_mxArrayOutData = NULL;
  c32_i20 = 0;
  for (c32_i21 = 0; c32_i21 < 3; c32_i21++) {
    for (c32_i22 = 0; c32_i22 < 3; c32_i22++) {
      c32_b_inData[c32_i22 + c32_i20] = (*(real_T (*)[9])c32_inData)[c32_i22 +
        c32_i20];
    }

    c32_i20 += 3;
  }

  c32_i23 = 0;
  for (c32_i24 = 0; c32_i24 < 3; c32_i24++) {
    for (c32_i25 = 0; c32_i25 < 3; c32_i25++) {
      c32_u[c32_i25 + c32_i23] = c32_b_inData[c32_i25 + c32_i23];
    }

    c32_i23 += 3;
  }

  c32_y = NULL;
  sf_mex_assign(&c32_y, sf_mex_create("y", c32_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c32_mxArrayOutData, c32_y, false);
  return c32_mxArrayOutData;
}

static void c32_d_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId, real_T c32_y[9])
{
  real_T c32_dv7[9];
  int32_T c32_i26;
  (void)chartInstance;
  sf_mex_import(c32_parentId, sf_mex_dup(c32_u), c32_dv7, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c32_i26 = 0; c32_i26 < 9; c32_i26++) {
    c32_y[c32_i26] = c32_dv7[c32_i26];
  }

  sf_mex_destroy(&c32_u);
}

static void c32_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c32_mxArrayInData, const char_T *c32_varName, void *c32_outData)
{
  const mxArray *c32_R_inv;
  const char_T *c32_identifier;
  emlrtMsgIdentifier c32_thisId;
  real_T c32_y[9];
  int32_T c32_i27;
  int32_T c32_i28;
  int32_T c32_i29;
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c32_R_inv = sf_mex_dup(c32_mxArrayInData);
  c32_identifier = c32_varName;
  c32_thisId.fIdentifier = c32_identifier;
  c32_thisId.fParent = NULL;
  c32_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c32_R_inv), &c32_thisId,
    c32_y);
  sf_mex_destroy(&c32_R_inv);
  c32_i27 = 0;
  for (c32_i28 = 0; c32_i28 < 3; c32_i28++) {
    for (c32_i29 = 0; c32_i29 < 3; c32_i29++) {
      (*(real_T (*)[9])c32_outData)[c32_i29 + c32_i27] = c32_y[c32_i29 + c32_i27];
    }

    c32_i27 += 3;
  }

  sf_mex_destroy(&c32_mxArrayInData);
}

const mxArray *sf_c32_CSE1_DP_get_eml_resolved_functions_info(void)
{
  const mxArray *c32_nameCaptureInfo = NULL;
  c32_nameCaptureInfo = NULL;
  sf_mex_assign(&c32_nameCaptureInfo, sf_mex_createstruct("structure", 2, 17, 1),
                false);
  c32_info_helper(&c32_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c32_nameCaptureInfo);
  return c32_nameCaptureInfo;
}

static void c32_info_helper(const mxArray **c32_info)
{
  const mxArray *c32_rhs0 = NULL;
  const mxArray *c32_lhs0 = NULL;
  const mxArray *c32_rhs1 = NULL;
  const mxArray *c32_lhs1 = NULL;
  const mxArray *c32_rhs2 = NULL;
  const mxArray *c32_lhs2 = NULL;
  const mxArray *c32_rhs3 = NULL;
  const mxArray *c32_lhs3 = NULL;
  const mxArray *c32_rhs4 = NULL;
  const mxArray *c32_lhs4 = NULL;
  const mxArray *c32_rhs5 = NULL;
  const mxArray *c32_lhs5 = NULL;
  const mxArray *c32_rhs6 = NULL;
  const mxArray *c32_lhs6 = NULL;
  const mxArray *c32_rhs7 = NULL;
  const mxArray *c32_lhs7 = NULL;
  const mxArray *c32_rhs8 = NULL;
  const mxArray *c32_lhs8 = NULL;
  const mxArray *c32_rhs9 = NULL;
  const mxArray *c32_lhs9 = NULL;
  const mxArray *c32_rhs10 = NULL;
  const mxArray *c32_lhs10 = NULL;
  const mxArray *c32_rhs11 = NULL;
  const mxArray *c32_lhs11 = NULL;
  const mxArray *c32_rhs12 = NULL;
  const mxArray *c32_lhs12 = NULL;
  const mxArray *c32_rhs13 = NULL;
  const mxArray *c32_lhs13 = NULL;
  const mxArray *c32_rhs14 = NULL;
  const mxArray *c32_lhs14 = NULL;
  const mxArray *c32_rhs15 = NULL;
  const mxArray *c32_lhs15 = NULL;
  const mxArray *c32_rhs16 = NULL;
  const mxArray *c32_lhs16 = NULL;
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("cos"), "name", "name", 0);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c32_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 1);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c32_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("sin"), "name", "name", 2);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c32_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 3);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c32_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(""), "context", "context", 4);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 4);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c32_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 5);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 5);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c32_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 6);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 6);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c32_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 7);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 7);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c32_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 8);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c32_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 9);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  9);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c32_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 10);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c32_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 11);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c32_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 12);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c32_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 13);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "coder.internal.blas.threshold"), "name", "name", 13);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c32_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 14);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 14);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c32_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 15);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 15);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c32_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 16);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "coder.internal.refblas.xgemm"), "name", "name", 16);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c32_info, c32_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c32_info, c32_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c32_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c32_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c32_info, sf_mex_duplicatearraysafe(&c32_lhs16), "lhs", "lhs",
                  16);
  sf_mex_destroy(&c32_rhs0);
  sf_mex_destroy(&c32_lhs0);
  sf_mex_destroy(&c32_rhs1);
  sf_mex_destroy(&c32_lhs1);
  sf_mex_destroy(&c32_rhs2);
  sf_mex_destroy(&c32_lhs2);
  sf_mex_destroy(&c32_rhs3);
  sf_mex_destroy(&c32_lhs3);
  sf_mex_destroy(&c32_rhs4);
  sf_mex_destroy(&c32_lhs4);
  sf_mex_destroy(&c32_rhs5);
  sf_mex_destroy(&c32_lhs5);
  sf_mex_destroy(&c32_rhs6);
  sf_mex_destroy(&c32_lhs6);
  sf_mex_destroy(&c32_rhs7);
  sf_mex_destroy(&c32_lhs7);
  sf_mex_destroy(&c32_rhs8);
  sf_mex_destroy(&c32_lhs8);
  sf_mex_destroy(&c32_rhs9);
  sf_mex_destroy(&c32_lhs9);
  sf_mex_destroy(&c32_rhs10);
  sf_mex_destroy(&c32_lhs10);
  sf_mex_destroy(&c32_rhs11);
  sf_mex_destroy(&c32_lhs11);
  sf_mex_destroy(&c32_rhs12);
  sf_mex_destroy(&c32_lhs12);
  sf_mex_destroy(&c32_rhs13);
  sf_mex_destroy(&c32_lhs13);
  sf_mex_destroy(&c32_rhs14);
  sf_mex_destroy(&c32_lhs14);
  sf_mex_destroy(&c32_rhs15);
  sf_mex_destroy(&c32_lhs15);
  sf_mex_destroy(&c32_rhs16);
  sf_mex_destroy(&c32_lhs16);
}

static const mxArray *c32_emlrt_marshallOut(const char * c32_u)
{
  const mxArray *c32_y = NULL;
  c32_y = NULL;
  sf_mex_assign(&c32_y, sf_mex_create("y", c32_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c32_u)), false);
  return c32_y;
}

static const mxArray *c32_b_emlrt_marshallOut(const uint32_T c32_u)
{
  const mxArray *c32_y = NULL;
  c32_y = NULL;
  sf_mex_assign(&c32_y, sf_mex_create("y", &c32_u, 7, 0U, 0U, 0U, 0), false);
  return c32_y;
}

static void c32_eml_scalar_eg(SFc32_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c32_eml_xgemm(SFc32_CSE1_DPInstanceStruct *chartInstance, real_T
  c32_A[9], real_T c32_B[3], real_T c32_C[3], real_T c32_b_C[3])
{
  int32_T c32_i30;
  int32_T c32_i31;
  real_T c32_b_A[9];
  int32_T c32_i32;
  real_T c32_b_B[3];
  for (c32_i30 = 0; c32_i30 < 3; c32_i30++) {
    c32_b_C[c32_i30] = c32_C[c32_i30];
  }

  for (c32_i31 = 0; c32_i31 < 9; c32_i31++) {
    c32_b_A[c32_i31] = c32_A[c32_i31];
  }

  for (c32_i32 = 0; c32_i32 < 3; c32_i32++) {
    c32_b_B[c32_i32] = c32_B[c32_i32];
  }

  c32_b_eml_xgemm(chartInstance, c32_b_A, c32_b_B, c32_b_C);
}

static const mxArray *c32_d_sf_marshallOut(void *chartInstanceVoid, void
  *c32_inData)
{
  const mxArray *c32_mxArrayOutData = NULL;
  int32_T c32_u;
  const mxArray *c32_y = NULL;
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c32_mxArrayOutData = NULL;
  c32_u = *(int32_T *)c32_inData;
  c32_y = NULL;
  sf_mex_assign(&c32_y, sf_mex_create("y", &c32_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c32_mxArrayOutData, c32_y, false);
  return c32_mxArrayOutData;
}

static int32_T c32_e_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId)
{
  int32_T c32_y;
  int32_T c32_i33;
  (void)chartInstance;
  sf_mex_import(c32_parentId, sf_mex_dup(c32_u), &c32_i33, 1, 6, 0U, 0, 0U, 0);
  c32_y = c32_i33;
  sf_mex_destroy(&c32_u);
  return c32_y;
}

static void c32_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c32_mxArrayInData, const char_T *c32_varName, void *c32_outData)
{
  const mxArray *c32_b_sfEvent;
  const char_T *c32_identifier;
  emlrtMsgIdentifier c32_thisId;
  int32_T c32_y;
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c32_b_sfEvent = sf_mex_dup(c32_mxArrayInData);
  c32_identifier = c32_varName;
  c32_thisId.fIdentifier = c32_identifier;
  c32_thisId.fParent = NULL;
  c32_y = c32_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c32_b_sfEvent),
    &c32_thisId);
  sf_mex_destroy(&c32_b_sfEvent);
  *(int32_T *)c32_outData = c32_y;
  sf_mex_destroy(&c32_mxArrayInData);
}

static uint8_T c32_f_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_b_is_active_c32_CSE1_DP, const char_T *c32_identifier)
{
  uint8_T c32_y;
  emlrtMsgIdentifier c32_thisId;
  c32_thisId.fIdentifier = c32_identifier;
  c32_thisId.fParent = NULL;
  c32_y = c32_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c32_b_is_active_c32_CSE1_DP), &c32_thisId);
  sf_mex_destroy(&c32_b_is_active_c32_CSE1_DP);
  return c32_y;
}

static uint8_T c32_g_emlrt_marshallIn(SFc32_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c32_u, const emlrtMsgIdentifier *c32_parentId)
{
  uint8_T c32_y;
  uint8_T c32_u0;
  (void)chartInstance;
  sf_mex_import(c32_parentId, sf_mex_dup(c32_u), &c32_u0, 1, 3, 0U, 0, 0U, 0);
  c32_y = c32_u0;
  sf_mex_destroy(&c32_u);
  return c32_y;
}

static void c32_b_eml_xgemm(SFc32_CSE1_DPInstanceStruct *chartInstance, real_T
  c32_A[9], real_T c32_B[3], real_T c32_C[3])
{
  int32_T c32_i34;
  int32_T c32_i35;
  int32_T c32_i36;
  (void)chartInstance;
  for (c32_i34 = 0; c32_i34 < 3; c32_i34++) {
    c32_C[c32_i34] = 0.0;
    c32_i35 = 0;
    for (c32_i36 = 0; c32_i36 < 3; c32_i36++) {
      c32_C[c32_i34] += c32_A[c32_i35 + c32_i34] * c32_B[c32_i36];
      c32_i35 += 3;
    }
  }
}

static void init_dsm_address_info(SFc32_CSE1_DPInstanceStruct *chartInstance)
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

void sf_c32_CSE1_DP_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2145142411U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2122309350U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(490707251U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3827741092U);
}

mxArray *sf_c32_CSE1_DP_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("UmKAF1GE7xoIxSLZalYVt");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
      pr[0] = (double)(1);
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

mxArray *sf_c32_CSE1_DP_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c32_CSE1_DP_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c32_CSE1_DP(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"nu\",},{M[8],M[0],T\"is_active_c32_CSE1_DP\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c32_CSE1_DP_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc32_CSE1_DPInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc32_CSE1_DPInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_DPMachineNumber_,
           32,
           1,
           1,
           0,
           3,
           0,
           0,
           0,
           0,
           0,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"eta_dot");
          _SFD_SET_DATA_PROPS(1,2,0,1,"nu");
          _SFD_SET_DATA_PROPS(2,1,1,0,"psi");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,143);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c32_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c32_sf_marshallOut,(MexInFcnForType)
            c32_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c32_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c32_psi;
          real_T (*c32_eta_dot)[3];
          real_T (*c32_nu)[3];
          c32_psi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c32_nu = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c32_eta_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c32_eta_dot);
          _SFD_SET_DATA_VALUE_PTR(1U, *c32_nu);
          _SFD_SET_DATA_VALUE_PTR(2U, c32_psi);
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
  return "2WHkTcLHLrAwNcDo2iYm";
}

static void sf_opaque_initialize_c32_CSE1_DP(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar);
  initialize_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c32_CSE1_DP(void *chartInstanceVar)
{
  enable_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c32_CSE1_DP(void *chartInstanceVar)
{
  disable_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c32_CSE1_DP(void *chartInstanceVar)
{
  sf_gateway_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c32_CSE1_DP(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c32_CSE1_DP();/* state var info */
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

extern void sf_internal_set_sim_state_c32_CSE1_DP(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c32_CSE1_DP();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c32_CSE1_DP(SimStruct* S)
{
  return sf_internal_get_sim_state_c32_CSE1_DP(S);
}

static void sf_opaque_set_sim_state_c32_CSE1_DP(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c32_CSE1_DP(S, st);
}

static void sf_opaque_terminate_c32_CSE1_DP(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_DP_optimization_info();
    }

    finalize_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c32_CSE1_DP(SimStruct *S)
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
    initialize_params_c32_CSE1_DP((SFc32_CSE1_DPInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c32_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_DP_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      32);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,32,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,32,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,32);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,32,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,32,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,32);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2598544959U));
  ssSetChecksum1(S,(1017407891U));
  ssSetChecksum2(S,(2816383955U));
  ssSetChecksum3(S,(2007623478U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c32_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c32_CSE1_DP(SimStruct *S)
{
  SFc32_CSE1_DPInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc32_CSE1_DPInstanceStruct *)utMalloc(sizeof
    (SFc32_CSE1_DPInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc32_CSE1_DPInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c32_CSE1_DP;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c32_CSE1_DP;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c32_CSE1_DP;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c32_CSE1_DP;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c32_CSE1_DP;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c32_CSE1_DP;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c32_CSE1_DP;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c32_CSE1_DP;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c32_CSE1_DP;
  chartInstance->chartInfo.mdlStart = mdlStart_c32_CSE1_DP;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c32_CSE1_DP;
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

void c32_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c32_CSE1_DP(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c32_CSE1_DP(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c32_CSE1_DP(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c32_CSE1_DP_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
