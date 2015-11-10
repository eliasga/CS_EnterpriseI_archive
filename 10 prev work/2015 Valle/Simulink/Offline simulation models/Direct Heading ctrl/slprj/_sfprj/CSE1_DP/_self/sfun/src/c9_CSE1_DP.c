/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_DP_sfun.h"
#include "c9_CSE1_DP.h"
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
static const char * c9_debug_family_names[20] = { "tau", "l_VSP", "l_BT", "T",
  "F_max_VSP", "F_max_BT", "K", "u", "u_VSP_x", "u_VSP_y", "nargin", "nargout",
  "X", "Y", "N", "VSP_on", "u_BT", "u_VSP", "alpha_VSP", "omega_VSP" };

/* Function Declarations */
static void initialize_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance);
static void initialize_params_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct
  *chartInstance);
static void enable_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance);
static void disable_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance);
static void c9_update_debugger_state_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct
  *chartInstance);
static void set_sim_state_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_st);
static void finalize_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance);
static void sf_gateway_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance);
static void initSimStructsc9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber, uint32_T c9_instanceNumber);
static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData);
static real_T c9_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_omega_VSP, const char_T *c9_identifier);
static real_T c9_b_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static void c9_c_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId, real_T c9_y[3]);
static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static void c9_info_helper(const mxArray **c9_info);
static const mxArray *c9_emlrt_marshallOut(const char * c9_u);
static const mxArray *c9_b_emlrt_marshallOut(const uint32_T c9_u);
static void c9_mldivide(SFc9_CSE1_DPInstanceStruct *chartInstance, real_T c9_A[9],
  real_T c9_B[3], real_T c9_Y[3]);
static void c9_eml_warning(SFc9_CSE1_DPInstanceStruct *chartInstance);
static real_T c9_mpower(SFc9_CSE1_DPInstanceStruct *chartInstance, real_T c9_a);
static void c9_eml_scalar_eg(SFc9_CSE1_DPInstanceStruct *chartInstance);
static void c9_eml_error(SFc9_CSE1_DPInstanceStruct *chartInstance);
static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static int32_T c9_d_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static uint8_T c9_e_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_b_is_active_c9_CSE1_DP, const char_T *c9_identifier);
static uint8_T c9_f_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void init_dsm_address_info(SFc9_CSE1_DPInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  chartInstance->c9_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c9_is_active_c9_CSE1_DP = 0U;
}

static void initialize_params_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c9_update_debugger_state_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct
  *chartInstance)
{
  const mxArray *c9_st;
  const mxArray *c9_y = NULL;
  real_T c9_hoistedGlobal;
  real_T c9_u;
  const mxArray *c9_b_y = NULL;
  real_T c9_b_hoistedGlobal;
  real_T c9_b_u;
  const mxArray *c9_c_y = NULL;
  real_T c9_c_hoistedGlobal;
  real_T c9_c_u;
  const mxArray *c9_d_y = NULL;
  real_T c9_d_hoistedGlobal;
  real_T c9_d_u;
  const mxArray *c9_e_y = NULL;
  uint8_T c9_e_hoistedGlobal;
  uint8_T c9_e_u;
  const mxArray *c9_f_y = NULL;
  real_T *c9_alpha_VSP;
  real_T *c9_omega_VSP;
  real_T *c9_u_BT;
  real_T *c9_u_VSP;
  c9_omega_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c9_alpha_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_u_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c9_u_BT = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c9_st = NULL;
  c9_st = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_createcellmatrix(5, 1), false);
  c9_hoistedGlobal = *c9_alpha_VSP;
  c9_u = c9_hoistedGlobal;
  c9_b_y = NULL;
  sf_mex_assign(&c9_b_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c9_y, 0, c9_b_y);
  c9_b_hoistedGlobal = *c9_omega_VSP;
  c9_b_u = c9_b_hoistedGlobal;
  c9_c_y = NULL;
  sf_mex_assign(&c9_c_y, sf_mex_create("y", &c9_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c9_y, 1, c9_c_y);
  c9_c_hoistedGlobal = *c9_u_BT;
  c9_c_u = c9_c_hoistedGlobal;
  c9_d_y = NULL;
  sf_mex_assign(&c9_d_y, sf_mex_create("y", &c9_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c9_y, 2, c9_d_y);
  c9_d_hoistedGlobal = *c9_u_VSP;
  c9_d_u = c9_d_hoistedGlobal;
  c9_e_y = NULL;
  sf_mex_assign(&c9_e_y, sf_mex_create("y", &c9_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c9_y, 3, c9_e_y);
  c9_e_hoistedGlobal = chartInstance->c9_is_active_c9_CSE1_DP;
  c9_e_u = c9_e_hoistedGlobal;
  c9_f_y = NULL;
  sf_mex_assign(&c9_f_y, sf_mex_create("y", &c9_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c9_y, 4, c9_f_y);
  sf_mex_assign(&c9_st, c9_y, false);
  return c9_st;
}

static void set_sim_state_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_st)
{
  const mxArray *c9_u;
  real_T *c9_alpha_VSP;
  real_T *c9_omega_VSP;
  real_T *c9_u_BT;
  real_T *c9_u_VSP;
  c9_omega_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c9_alpha_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_u_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c9_u_BT = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c9_doneDoubleBufferReInit = true;
  c9_u = sf_mex_dup(c9_st);
  *c9_alpha_VSP = c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c9_u, 0)), "alpha_VSP");
  *c9_omega_VSP = c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c9_u, 1)), "omega_VSP");
  *c9_u_BT = c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u,
    2)), "u_BT");
  *c9_u_VSP = c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u,
    3)), "u_VSP");
  chartInstance->c9_is_active_c9_CSE1_DP = c9_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c9_u, 4)), "is_active_c9_CSE1_DP");
  sf_mex_destroy(&c9_u);
  c9_update_debugger_state_c9_CSE1_DP(chartInstance);
  sf_mex_destroy(&c9_st);
}

static void finalize_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  real_T c9_hoistedGlobal;
  real_T c9_b_hoistedGlobal;
  real_T c9_c_hoistedGlobal;
  real_T c9_d_hoistedGlobal;
  real_T c9_X;
  real_T c9_Y;
  real_T c9_N;
  real_T c9_VSP_on;
  uint32_T c9_debug_family_var_map[20];
  real_T c9_tau[3];
  real_T c9_l_VSP;
  real_T c9_l_BT;
  real_T c9_T[9];
  real_T c9_F_max_VSP;
  real_T c9_F_max_BT;
  real_T c9_K[9];
  real_T c9_u[3];
  real_T c9_u_VSP_x;
  real_T c9_u_VSP_y;
  real_T c9_nargin = 4.0;
  real_T c9_nargout = 4.0;
  real_T c9_u_BT;
  real_T c9_u_VSP;
  real_T c9_alpha_VSP;
  real_T c9_omega_VSP;
  int32_T c9_i0;
  static real_T c9_dv0[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, -0.4575, 0.0, 1.0, 0.3875
  };

  int32_T c9_i1;
  static real_T c9_dv1[9] = { 1.165, 0.0, 0.0, 0.0, 1.165, 0.0, 0.0, 0.0, 2.629
  };

  int32_T c9_i2;
  real_T c9_dv2[9];
  int32_T c9_i3;
  real_T c9_b_tau[3];
  real_T c9_dv3[3];
  int32_T c9_i4;
  real_T c9_dv4[9];
  int32_T c9_i5;
  real_T c9_dv5[3];
  real_T c9_dv6[3];
  int32_T c9_i6;
  real_T c9_x;
  real_T c9_b_x;
  real_T c9_y;
  real_T c9_c_x;
  real_T c9_b_y;
  real_T c9_d_x;
  real_T *c9_b_X;
  real_T *c9_b_Y;
  real_T *c9_b_u_BT;
  real_T *c9_b_N;
  real_T *c9_b_u_VSP;
  real_T *c9_b_alpha_VSP;
  real_T *c9_b_VSP_on;
  real_T *c9_b_omega_VSP;
  c9_b_omega_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c9_b_VSP_on = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c9_b_alpha_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_b_u_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c9_b_N = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c9_b_u_BT = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c9_b_Y = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c9_b_X = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c9_b_X, 0U);
  _SFD_DATA_RANGE_CHECK(*c9_b_Y, 1U);
  chartInstance->c9_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  c9_hoistedGlobal = *c9_b_X;
  c9_b_hoistedGlobal = *c9_b_Y;
  c9_c_hoistedGlobal = *c9_b_N;
  c9_d_hoistedGlobal = *c9_b_VSP_on;
  c9_X = c9_hoistedGlobal;
  c9_Y = c9_b_hoistedGlobal;
  c9_N = c9_c_hoistedGlobal;
  c9_VSP_on = c9_d_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 20U, 20U, c9_debug_family_names,
    c9_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_tau, 0U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_l_VSP, 1U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_l_BT, 2U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_T, 3U, c9_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_F_max_VSP, 4U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_F_max_BT, 5U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_K, 6U, c9_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_u, 7U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_u_VSP_x, 8U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_u_VSP_y, 9U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargin, 10U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargout, 11U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_X, 12U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_Y, 13U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_N, 14U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_VSP_on, 15U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_u_BT, 16U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_u_VSP, 17U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_alpha_VSP, 18U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_omega_VSP, 19U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 4);
  c9_tau[0] = c9_X;
  c9_tau[1] = c9_Y;
  c9_tau[2] = c9_N;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 9);
  c9_l_VSP = -0.4575;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 10);
  c9_l_BT = 0.3875;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 11);
  for (c9_i0 = 0; c9_i0 < 9; c9_i0++) {
    c9_T[c9_i0] = c9_dv0[c9_i0];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 16);
  c9_F_max_VSP = 1.165;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 17);
  c9_F_max_BT = 2.629;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 18);
  for (c9_i1 = 0; c9_i1 < 9; c9_i1++) {
    c9_K[c9_i1] = c9_dv1[c9_i1];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 23);
  for (c9_i2 = 0; c9_i2 < 9; c9_i2++) {
    c9_dv2[c9_i2] = c9_dv0[c9_i2];
  }

  for (c9_i3 = 0; c9_i3 < 3; c9_i3++) {
    c9_b_tau[c9_i3] = c9_tau[c9_i3];
  }

  c9_mldivide(chartInstance, c9_dv2, c9_b_tau, c9_dv3);
  for (c9_i4 = 0; c9_i4 < 9; c9_i4++) {
    c9_dv4[c9_i4] = c9_dv1[c9_i4];
  }

  for (c9_i5 = 0; c9_i5 < 3; c9_i5++) {
    c9_dv5[c9_i5] = c9_dv3[c9_i5];
  }

  c9_mldivide(chartInstance, c9_dv4, c9_dv5, c9_dv6);
  for (c9_i6 = 0; c9_i6 < 3; c9_i6++) {
    c9_u[c9_i6] = c9_dv6[c9_i6];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 25);
  c9_u_BT = c9_u[2];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 27);
  c9_u_VSP_x = c9_u[0];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 28);
  c9_u_VSP_y = c9_u[1];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 29);
  c9_x = c9_mpower(chartInstance, c9_u_VSP_x) + c9_mpower(chartInstance,
    c9_u_VSP_y);
  c9_u_VSP = c9_x;
  if (c9_u_VSP < 0.0) {
    c9_eml_error(chartInstance);
  }

  c9_b_x = c9_u_VSP;
  c9_u_VSP = c9_b_x;
  c9_u_VSP = muDoubleScalarSqrt(c9_u_VSP);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 30);
  c9_y = c9_u_VSP_y;
  c9_c_x = c9_u_VSP_x;
  c9_eml_scalar_eg(chartInstance);
  c9_b_y = c9_y;
  c9_d_x = c9_c_x;
  c9_alpha_VSP = muDoubleScalarAtan2(c9_b_y, c9_d_x);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 32);
  if (CV_EML_IF(0, 1, 0, c9_VSP_on != 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 33);
    c9_omega_VSP = 0.3;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 35);
    c9_omega_VSP = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, -35);
  _SFD_SYMBOL_SCOPE_POP();
  *c9_b_u_BT = c9_u_BT;
  *c9_b_u_VSP = c9_u_VSP;
  *c9_b_alpha_VSP = c9_alpha_VSP;
  *c9_b_omega_VSP = c9_omega_VSP;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_DPMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c9_b_u_BT, 2U);
  _SFD_DATA_RANGE_CHECK(*c9_b_N, 3U);
  _SFD_DATA_RANGE_CHECK(*c9_b_u_VSP, 4U);
  _SFD_DATA_RANGE_CHECK(*c9_b_alpha_VSP, 5U);
  _SFD_DATA_RANGE_CHECK(*c9_b_VSP_on, 6U);
  _SFD_DATA_RANGE_CHECK(*c9_b_omega_VSP, 7U);
}

static void initSimStructsc9_CSE1_DP(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber, uint32_T c9_instanceNumber)
{
  (void)c9_machineNumber;
  (void)c9_chartNumber;
  (void)c9_instanceNumber;
}

static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc9_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, false);
  return c9_mxArrayOutData;
}

static real_T c9_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_omega_VSP, const char_T *c9_identifier)
{
  real_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_omega_VSP),
    &c9_thisId);
  sf_mex_destroy(&c9_omega_VSP);
  return c9_y;
}

static real_T c9_b_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d0;
  (void)chartInstance;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d0, 1, 0, 0U, 0, 0U, 0);
  c9_y = c9_d0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_omega_VSP;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc9_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c9_omega_VSP = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_omega_VSP),
    &c9_thisId);
  sf_mex_destroy(&c9_omega_VSP);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i7;
  real_T c9_b_inData[3];
  int32_T c9_i8;
  real_T c9_u[3];
  const mxArray *c9_y = NULL;
  SFc9_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc9_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i7 = 0; c9_i7 < 3; c9_i7++) {
    c9_b_inData[c9_i7] = (*(real_T (*)[3])c9_inData)[c9_i7];
  }

  for (c9_i8 = 0; c9_i8 < 3; c9_i8++) {
    c9_u[c9_i8] = c9_b_inData[c9_i8];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, false);
  return c9_mxArrayOutData;
}

static void c9_c_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId, real_T c9_y[3])
{
  real_T c9_dv7[3];
  int32_T c9_i9;
  (void)chartInstance;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv7, 1, 0, 0U, 1, 0U, 1, 3);
  for (c9_i9 = 0; c9_i9 < 3; c9_i9++) {
    c9_y[c9_i9] = c9_dv7[c9_i9];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_u;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[3];
  int32_T c9_i10;
  SFc9_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc9_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c9_u = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_u), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_u);
  for (c9_i10 = 0; c9_i10 < 3; c9_i10++) {
    (*(real_T (*)[3])c9_outData)[c9_i10] = c9_y[c9_i10];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i11;
  int32_T c9_i12;
  int32_T c9_i13;
  real_T c9_b_inData[9];
  int32_T c9_i14;
  int32_T c9_i15;
  int32_T c9_i16;
  real_T c9_u[9];
  const mxArray *c9_y = NULL;
  SFc9_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc9_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_i11 = 0;
  for (c9_i12 = 0; c9_i12 < 3; c9_i12++) {
    for (c9_i13 = 0; c9_i13 < 3; c9_i13++) {
      c9_b_inData[c9_i13 + c9_i11] = (*(real_T (*)[9])c9_inData)[c9_i13 + c9_i11];
    }

    c9_i11 += 3;
  }

  c9_i14 = 0;
  for (c9_i15 = 0; c9_i15 < 3; c9_i15++) {
    for (c9_i16 = 0; c9_i16 < 3; c9_i16++) {
      c9_u[c9_i16 + c9_i14] = c9_b_inData[c9_i16 + c9_i14];
    }

    c9_i14 += 3;
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, false);
  return c9_mxArrayOutData;
}

const mxArray *sf_c9_CSE1_DP_get_eml_resolved_functions_info(void)
{
  const mxArray *c9_nameCaptureInfo = NULL;
  c9_nameCaptureInfo = NULL;
  sf_mex_assign(&c9_nameCaptureInfo, sf_mex_createstruct("structure", 2, 34, 1),
                false);
  c9_info_helper(&c9_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c9_nameCaptureInfo);
  return c9_nameCaptureInfo;
}

static void c9_info_helper(const mxArray **c9_info)
{
  const mxArray *c9_rhs0 = NULL;
  const mxArray *c9_lhs0 = NULL;
  const mxArray *c9_rhs1 = NULL;
  const mxArray *c9_lhs1 = NULL;
  const mxArray *c9_rhs2 = NULL;
  const mxArray *c9_lhs2 = NULL;
  const mxArray *c9_rhs3 = NULL;
  const mxArray *c9_lhs3 = NULL;
  const mxArray *c9_rhs4 = NULL;
  const mxArray *c9_lhs4 = NULL;
  const mxArray *c9_rhs5 = NULL;
  const mxArray *c9_lhs5 = NULL;
  const mxArray *c9_rhs6 = NULL;
  const mxArray *c9_lhs6 = NULL;
  const mxArray *c9_rhs7 = NULL;
  const mxArray *c9_lhs7 = NULL;
  const mxArray *c9_rhs8 = NULL;
  const mxArray *c9_lhs8 = NULL;
  const mxArray *c9_rhs9 = NULL;
  const mxArray *c9_lhs9 = NULL;
  const mxArray *c9_rhs10 = NULL;
  const mxArray *c9_lhs10 = NULL;
  const mxArray *c9_rhs11 = NULL;
  const mxArray *c9_lhs11 = NULL;
  const mxArray *c9_rhs12 = NULL;
  const mxArray *c9_lhs12 = NULL;
  const mxArray *c9_rhs13 = NULL;
  const mxArray *c9_lhs13 = NULL;
  const mxArray *c9_rhs14 = NULL;
  const mxArray *c9_lhs14 = NULL;
  const mxArray *c9_rhs15 = NULL;
  const mxArray *c9_lhs15 = NULL;
  const mxArray *c9_rhs16 = NULL;
  const mxArray *c9_lhs16 = NULL;
  const mxArray *c9_rhs17 = NULL;
  const mxArray *c9_lhs17 = NULL;
  const mxArray *c9_rhs18 = NULL;
  const mxArray *c9_lhs18 = NULL;
  const mxArray *c9_rhs19 = NULL;
  const mxArray *c9_lhs19 = NULL;
  const mxArray *c9_rhs20 = NULL;
  const mxArray *c9_lhs20 = NULL;
  const mxArray *c9_rhs21 = NULL;
  const mxArray *c9_lhs21 = NULL;
  const mxArray *c9_rhs22 = NULL;
  const mxArray *c9_lhs22 = NULL;
  const mxArray *c9_rhs23 = NULL;
  const mxArray *c9_lhs23 = NULL;
  const mxArray *c9_rhs24 = NULL;
  const mxArray *c9_lhs24 = NULL;
  const mxArray *c9_rhs25 = NULL;
  const mxArray *c9_lhs25 = NULL;
  const mxArray *c9_rhs26 = NULL;
  const mxArray *c9_lhs26 = NULL;
  const mxArray *c9_rhs27 = NULL;
  const mxArray *c9_lhs27 = NULL;
  const mxArray *c9_rhs28 = NULL;
  const mxArray *c9_lhs28 = NULL;
  const mxArray *c9_rhs29 = NULL;
  const mxArray *c9_lhs29 = NULL;
  const mxArray *c9_rhs30 = NULL;
  const mxArray *c9_lhs30 = NULL;
  const mxArray *c9_rhs31 = NULL;
  const mxArray *c9_lhs31 = NULL;
  const mxArray *c9_rhs32 = NULL;
  const mxArray *c9_lhs32 = NULL;
  const mxArray *c9_rhs33 = NULL;
  const mxArray *c9_lhs33 = NULL;
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("mldivide"), "name", "name", 0);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1319729966U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c9_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "context",
                  "context", 1);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_lusolve"), "name", "name",
                  1);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1370009886U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c9_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3"),
                  "context", "context", 2);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_xcabs1"), "name", "name",
                  2);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c9_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("coder.internal.refblas.xcabs1"),
                  "name", "name", 3);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c9_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "context", "context", 4);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("abs"), "name", "name", 4);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c9_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 5);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c9_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 6);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c9_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3"),
                  "context", "context", 7);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("rdivide"), "name", "name", 7);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c9_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 8);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c9_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 9);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c9_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_div"), "name", "name", 10);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c9_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 11);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 11);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c9_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!warn_singular"),
                  "context", "context", 12);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_warning"), "name", "name",
                  12);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1286818802U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c9_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3"),
                  "context", "context", 13);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 13);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c9_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 14);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c9_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(""), "context", "context", 15);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("mpower"), "name", "name", 15);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c9_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 16);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c9_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("ismatrix"), "name", "name", 17);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c9_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("power"), "name", "name", 18);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c9_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 19);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c9_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 20);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 20);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c9_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 21);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 21);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c9_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 22);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 22);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c9_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 23);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("floor"), "name", "name", 23);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c9_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 24);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 24);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c9_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 25);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 25);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c9_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 26);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 26);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 26);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c9_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(""), "context", "context", 27);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("sqrt"), "name", "name", 27);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 27);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c9_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_error"), "name", "name",
                  28);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 28);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c9_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalar_sqrt"), "name",
                  "name", 29);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1286818738U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c9_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(""), "context", "context", 30);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("atan2"), "name", "name", 30);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "resolved",
                  "resolved", 30);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c9_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 31);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 31);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 31);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c9_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 32);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 32);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c9_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 33);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("eml_scalar_atan2"), "name",
                  "name", 33);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c9_info, c9_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(1286818720U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c9_info, c9_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c9_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c9_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c9_info, sf_mex_duplicatearraysafe(&c9_lhs33), "lhs", "lhs",
                  33);
  sf_mex_destroy(&c9_rhs0);
  sf_mex_destroy(&c9_lhs0);
  sf_mex_destroy(&c9_rhs1);
  sf_mex_destroy(&c9_lhs1);
  sf_mex_destroy(&c9_rhs2);
  sf_mex_destroy(&c9_lhs2);
  sf_mex_destroy(&c9_rhs3);
  sf_mex_destroy(&c9_lhs3);
  sf_mex_destroy(&c9_rhs4);
  sf_mex_destroy(&c9_lhs4);
  sf_mex_destroy(&c9_rhs5);
  sf_mex_destroy(&c9_lhs5);
  sf_mex_destroy(&c9_rhs6);
  sf_mex_destroy(&c9_lhs6);
  sf_mex_destroy(&c9_rhs7);
  sf_mex_destroy(&c9_lhs7);
  sf_mex_destroy(&c9_rhs8);
  sf_mex_destroy(&c9_lhs8);
  sf_mex_destroy(&c9_rhs9);
  sf_mex_destroy(&c9_lhs9);
  sf_mex_destroy(&c9_rhs10);
  sf_mex_destroy(&c9_lhs10);
  sf_mex_destroy(&c9_rhs11);
  sf_mex_destroy(&c9_lhs11);
  sf_mex_destroy(&c9_rhs12);
  sf_mex_destroy(&c9_lhs12);
  sf_mex_destroy(&c9_rhs13);
  sf_mex_destroy(&c9_lhs13);
  sf_mex_destroy(&c9_rhs14);
  sf_mex_destroy(&c9_lhs14);
  sf_mex_destroy(&c9_rhs15);
  sf_mex_destroy(&c9_lhs15);
  sf_mex_destroy(&c9_rhs16);
  sf_mex_destroy(&c9_lhs16);
  sf_mex_destroy(&c9_rhs17);
  sf_mex_destroy(&c9_lhs17);
  sf_mex_destroy(&c9_rhs18);
  sf_mex_destroy(&c9_lhs18);
  sf_mex_destroy(&c9_rhs19);
  sf_mex_destroy(&c9_lhs19);
  sf_mex_destroy(&c9_rhs20);
  sf_mex_destroy(&c9_lhs20);
  sf_mex_destroy(&c9_rhs21);
  sf_mex_destroy(&c9_lhs21);
  sf_mex_destroy(&c9_rhs22);
  sf_mex_destroy(&c9_lhs22);
  sf_mex_destroy(&c9_rhs23);
  sf_mex_destroy(&c9_lhs23);
  sf_mex_destroy(&c9_rhs24);
  sf_mex_destroy(&c9_lhs24);
  sf_mex_destroy(&c9_rhs25);
  sf_mex_destroy(&c9_lhs25);
  sf_mex_destroy(&c9_rhs26);
  sf_mex_destroy(&c9_lhs26);
  sf_mex_destroy(&c9_rhs27);
  sf_mex_destroy(&c9_lhs27);
  sf_mex_destroy(&c9_rhs28);
  sf_mex_destroy(&c9_lhs28);
  sf_mex_destroy(&c9_rhs29);
  sf_mex_destroy(&c9_lhs29);
  sf_mex_destroy(&c9_rhs30);
  sf_mex_destroy(&c9_lhs30);
  sf_mex_destroy(&c9_rhs31);
  sf_mex_destroy(&c9_lhs31);
  sf_mex_destroy(&c9_rhs32);
  sf_mex_destroy(&c9_lhs32);
  sf_mex_destroy(&c9_rhs33);
  sf_mex_destroy(&c9_lhs33);
}

static const mxArray *c9_emlrt_marshallOut(const char * c9_u)
{
  const mxArray *c9_y = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c9_u)), false);
  return c9_y;
}

static const mxArray *c9_b_emlrt_marshallOut(const uint32_T c9_u)
{
  const mxArray *c9_y = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 7, 0U, 0U, 0U, 0), false);
  return c9_y;
}

static void c9_mldivide(SFc9_CSE1_DPInstanceStruct *chartInstance, real_T c9_A[9],
  real_T c9_B[3], real_T c9_Y[3])
{
  int32_T c9_i17;
  real_T c9_b_A[9];
  int32_T c9_r1;
  int32_T c9_r2;
  int32_T c9_r3;
  real_T c9_x;
  real_T c9_b_x;
  real_T c9_c_x;
  real_T c9_d_x;
  real_T c9_y;
  real_T c9_e_x;
  real_T c9_f_x;
  real_T c9_b_y;
  real_T c9_maxval;
  real_T c9_g_x;
  real_T c9_h_x;
  real_T c9_i_x;
  real_T c9_j_x;
  real_T c9_c_y;
  real_T c9_k_x;
  real_T c9_l_x;
  real_T c9_d_y;
  real_T c9_a21;
  real_T c9_m_x;
  real_T c9_n_x;
  real_T c9_o_x;
  real_T c9_p_x;
  real_T c9_e_y;
  real_T c9_q_x;
  real_T c9_r_x;
  real_T c9_f_y;
  real_T c9_d;
  real_T c9_s_x;
  real_T c9_g_y;
  real_T c9_t_x;
  real_T c9_h_y;
  real_T c9_u_x;
  real_T c9_i_y;
  real_T c9_z;
  real_T c9_v_x;
  real_T c9_j_y;
  real_T c9_w_x;
  real_T c9_k_y;
  real_T c9_x_x;
  real_T c9_l_y;
  real_T c9_b_z;
  real_T c9_y_x;
  real_T c9_ab_x;
  real_T c9_bb_x;
  real_T c9_cb_x;
  real_T c9_m_y;
  real_T c9_db_x;
  real_T c9_eb_x;
  real_T c9_n_y;
  real_T c9_b_d;
  real_T c9_fb_x;
  real_T c9_gb_x;
  real_T c9_hb_x;
  real_T c9_ib_x;
  real_T c9_o_y;
  real_T c9_jb_x;
  real_T c9_kb_x;
  real_T c9_p_y;
  real_T c9_c_d;
  int32_T c9_rtemp;
  real_T c9_lb_x;
  real_T c9_q_y;
  real_T c9_mb_x;
  real_T c9_r_y;
  real_T c9_nb_x;
  real_T c9_s_y;
  real_T c9_c_z;
  real_T c9_ob_x;
  real_T c9_t_y;
  real_T c9_pb_x;
  real_T c9_u_y;
  real_T c9_qb_x;
  real_T c9_v_y;
  real_T c9_d_z;
  real_T c9_rb_x;
  real_T c9_w_y;
  real_T c9_sb_x;
  real_T c9_x_y;
  real_T c9_tb_x;
  real_T c9_y_y;
  real_T c9_e_z;
  real_T c9_ub_x;
  real_T c9_ab_y;
  real_T c9_vb_x;
  real_T c9_bb_y;
  real_T c9_wb_x;
  real_T c9_cb_y;
  real_T c9_f_z;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  for (c9_i17 = 0; c9_i17 < 9; c9_i17++) {
    c9_b_A[c9_i17] = c9_A[c9_i17];
  }

  c9_r1 = 1;
  c9_r2 = 2;
  c9_r3 = 3;
  c9_x = c9_b_A[0];
  c9_b_x = c9_x;
  c9_c_x = c9_b_x;
  c9_d_x = c9_c_x;
  c9_y = muDoubleScalarAbs(c9_d_x);
  c9_e_x = 0.0;
  c9_f_x = c9_e_x;
  c9_b_y = muDoubleScalarAbs(c9_f_x);
  c9_maxval = c9_y + c9_b_y;
  c9_g_x = c9_b_A[1];
  c9_h_x = c9_g_x;
  c9_i_x = c9_h_x;
  c9_j_x = c9_i_x;
  c9_c_y = muDoubleScalarAbs(c9_j_x);
  c9_k_x = 0.0;
  c9_l_x = c9_k_x;
  c9_d_y = muDoubleScalarAbs(c9_l_x);
  c9_a21 = c9_c_y + c9_d_y;
  if (c9_a21 > c9_maxval) {
    c9_maxval = c9_a21;
    c9_r1 = 2;
    c9_r2 = 1;
  }

  c9_m_x = c9_b_A[2];
  c9_n_x = c9_m_x;
  c9_o_x = c9_n_x;
  c9_p_x = c9_o_x;
  c9_e_y = muDoubleScalarAbs(c9_p_x);
  c9_q_x = 0.0;
  c9_r_x = c9_q_x;
  c9_f_y = muDoubleScalarAbs(c9_r_x);
  c9_d = c9_e_y + c9_f_y;
  if (c9_d > c9_maxval) {
    c9_r1 = 3;
    c9_r2 = 2;
    c9_r3 = 1;
  }

  c9_s_x = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r2), 1, 3, 1, 0) - 1];
  c9_g_y = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r1), 1, 3, 1, 0) - 1];
  c9_t_x = c9_s_x;
  c9_h_y = c9_g_y;
  c9_u_x = c9_t_x;
  c9_i_y = c9_h_y;
  c9_z = c9_u_x / c9_i_y;
  c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c9_r2), 1, 3, 1, 0) - 1] = c9_z;
  c9_v_x = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r3), 1, 3, 1, 0) - 1];
  c9_j_y = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r1), 1, 3, 1, 0) - 1];
  c9_w_x = c9_v_x;
  c9_k_y = c9_j_y;
  c9_x_x = c9_w_x;
  c9_l_y = c9_k_y;
  c9_b_z = c9_x_x / c9_l_y;
  c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c9_r3), 1, 3, 1, 0) - 1] = c9_b_z;
  c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c9_r2), 1, 3, 1, 0) + 2] = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c9_r2), 1, 3, 1, 0) + 2] -
    c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r2), 1, 3, 1, 0) - 1] * c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c9_r1), 1, 3, 1, 0) + 2];
  c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c9_r3), 1, 3, 1, 0) + 2] = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c9_r3), 1, 3, 1, 0) + 2] -
    c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r3), 1, 3, 1, 0) - 1] * c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c9_r1), 1, 3, 1, 0) + 2];
  c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c9_r2), 1, 3, 1, 0) + 5] = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c9_r2), 1, 3, 1, 0) + 5] -
    c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r2), 1, 3, 1, 0) - 1] * c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c9_r1), 1, 3, 1, 0) + 5];
  c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c9_r3), 1, 3, 1, 0) + 5] = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c9_r3), 1, 3, 1, 0) + 5] -
    c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r3), 1, 3, 1, 0) - 1] * c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c9_r1), 1, 3, 1, 0) + 5];
  c9_y_x = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r3), 1, 3, 1, 0) + 2];
  c9_ab_x = c9_y_x;
  c9_bb_x = c9_ab_x;
  c9_cb_x = c9_bb_x;
  c9_m_y = muDoubleScalarAbs(c9_cb_x);
  c9_db_x = 0.0;
  c9_eb_x = c9_db_x;
  c9_n_y = muDoubleScalarAbs(c9_eb_x);
  c9_b_d = c9_m_y + c9_n_y;
  c9_fb_x = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c9_r2), 1, 3, 1, 0) + 2];
  c9_gb_x = c9_fb_x;
  c9_hb_x = c9_gb_x;
  c9_ib_x = c9_hb_x;
  c9_o_y = muDoubleScalarAbs(c9_ib_x);
  c9_jb_x = 0.0;
  c9_kb_x = c9_jb_x;
  c9_p_y = muDoubleScalarAbs(c9_kb_x);
  c9_c_d = c9_o_y + c9_p_y;
  if (c9_b_d > c9_c_d) {
    c9_rtemp = c9_r2;
    c9_r2 = c9_r3;
    c9_r3 = c9_rtemp;
  }

  c9_lb_x = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c9_r3), 1, 3, 1, 0) + 2];
  c9_q_y = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r2), 1, 3, 1, 0) + 2];
  c9_mb_x = c9_lb_x;
  c9_r_y = c9_q_y;
  c9_nb_x = c9_mb_x;
  c9_s_y = c9_r_y;
  c9_c_z = c9_nb_x / c9_s_y;
  c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c9_r3), 1, 3, 1, 0) + 2] = c9_c_z;
  c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c9_r3), 1, 3, 1, 0) + 5] = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c9_r3), 1, 3, 1, 0) + 5] -
    c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r3), 1, 3, 1, 0) + 2] * c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c9_r2), 1, 3, 1, 0) + 5];
  guard1 = false;
  guard2 = false;
  if (c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c9_r1), 1, 3, 1, 0) - 1] == 0.0) {
    guard2 = true;
  } else if (c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
               "", (real_T)c9_r2), 1, 3, 1, 0) + 2] == 0.0) {
    guard2 = true;
  } else {
    if (c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c9_r3), 1, 3, 1, 0) + 5] == 0.0) {
      guard1 = true;
    }
  }

  if (guard2 == true) {
    guard1 = true;
  }

  if (guard1 == true) {
    c9_eml_warning(chartInstance);
  }

  c9_Y[0] = c9_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r1), 1, 3, 1, 0) - 1];
  c9_Y[1] = c9_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r2), 1, 3, 1, 0) - 1] - c9_Y[0] *
    c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r2), 1, 3, 1, 0) - 1];
  c9_Y[2] = (c9_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
               (real_T)c9_r3), 1, 3, 1, 0) - 1] - c9_Y[0] *
             c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c9_r3), 1, 3, 1, 0) - 1]) - c9_Y[1] *
    c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r3), 1, 3, 1, 0) + 2];
  c9_ob_x = c9_Y[2];
  c9_t_y = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r3), 1, 3, 1, 0) + 5];
  c9_pb_x = c9_ob_x;
  c9_u_y = c9_t_y;
  c9_qb_x = c9_pb_x;
  c9_v_y = c9_u_y;
  c9_d_z = c9_qb_x / c9_v_y;
  c9_Y[2] = c9_d_z;
  c9_Y[0] -= c9_Y[2] * c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c9_r1), 1, 3, 1, 0) + 5];
  c9_Y[1] -= c9_Y[2] * c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c9_r2), 1, 3, 1, 0) + 5];
  c9_rb_x = c9_Y[1];
  c9_w_y = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c9_r2), 1, 3, 1, 0) + 2];
  c9_sb_x = c9_rb_x;
  c9_x_y = c9_w_y;
  c9_tb_x = c9_sb_x;
  c9_y_y = c9_x_y;
  c9_e_z = c9_tb_x / c9_y_y;
  c9_Y[1] = c9_e_z;
  c9_Y[0] -= c9_Y[1] * c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c9_r1), 1, 3, 1, 0) + 2];
  c9_ub_x = c9_Y[0];
  c9_ab_y = c9_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c9_r1), 1, 3, 1, 0) - 1];
  c9_vb_x = c9_ub_x;
  c9_bb_y = c9_ab_y;
  c9_wb_x = c9_vb_x;
  c9_cb_y = c9_bb_y;
  c9_f_z = c9_wb_x / c9_cb_y;
  c9_Y[0] = c9_f_z;
}

static void c9_eml_warning(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  int32_T c9_i18;
  static char_T c9_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c9_u[27];
  const mxArray *c9_y = NULL;
  (void)chartInstance;
  for (c9_i18 = 0; c9_i18 < 27; c9_i18++) {
    c9_u[c9_i18] = c9_varargin_1[c9_i18];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 10, 0U, 1U, 0U, 2, 1, 27), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c9_y));
}

static real_T c9_mpower(SFc9_CSE1_DPInstanceStruct *chartInstance, real_T c9_a)
{
  real_T c9_b_a;
  real_T c9_c_a;
  real_T c9_ak;
  real_T c9_d_a;
  c9_b_a = c9_a;
  c9_c_a = c9_b_a;
  c9_eml_scalar_eg(chartInstance);
  c9_ak = c9_c_a;
  c9_d_a = c9_ak;
  c9_eml_scalar_eg(chartInstance);
  return c9_d_a * c9_d_a;
}

static void c9_eml_scalar_eg(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c9_eml_error(SFc9_CSE1_DPInstanceStruct *chartInstance)
{
  int32_T c9_i19;
  static char_T c9_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c9_u[30];
  const mxArray *c9_y = NULL;
  int32_T c9_i20;
  static char_T c9_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c9_b_u[4];
  const mxArray *c9_b_y = NULL;
  (void)chartInstance;
  for (c9_i19 = 0; c9_i19 < 30; c9_i19++) {
    c9_u[c9_i19] = c9_cv0[c9_i19];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  for (c9_i20 = 0; c9_i20 < 4; c9_i20++) {
    c9_b_u[c9_i20] = c9_cv1[c9_i20];
  }

  c9_b_y = NULL;
  sf_mex_assign(&c9_b_y, sf_mex_create("y", c9_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c9_y, 14, c9_b_y));
}

static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc9_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(int32_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, false);
  return c9_mxArrayOutData;
}

static int32_T c9_d_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  int32_T c9_y;
  int32_T c9_i21;
  (void)chartInstance;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_i21, 1, 6, 0U, 0, 0U, 0);
  c9_y = c9_i21;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_sfEvent;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y;
  SFc9_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc9_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c9_b_sfEvent = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_sfEvent),
    &c9_thisId);
  sf_mex_destroy(&c9_b_sfEvent);
  *(int32_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static uint8_T c9_e_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_b_is_active_c9_CSE1_DP, const char_T *c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c9_b_is_active_c9_CSE1_DP), &c9_thisId);
  sf_mex_destroy(&c9_b_is_active_c9_CSE1_DP);
  return c9_y;
}

static uint8_T c9_f_emlrt_marshallIn(SFc9_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  uint8_T c9_u0;
  (void)chartInstance;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_u0, 1, 3, 0U, 0, 0U, 0);
  c9_y = c9_u0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void init_dsm_address_info(SFc9_CSE1_DPInstanceStruct *chartInstance)
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

void sf_c9_CSE1_DP_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3698834495U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(935120617U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3995777643U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1887230870U);
}

mxArray *sf_c9_CSE1_DP_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("eFSsiJ50SwdpowHvmmyyCD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c9_CSE1_DP_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c9_CSE1_DP_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c9_CSE1_DP(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[9],T\"alpha_VSP\",},{M[1],M[11],T\"omega_VSP\",},{M[1],M[5],T\"u_BT\",},{M[1],M[8],T\"u_VSP\",},{M[8],M[0],T\"is_active_c9_CSE1_DP\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c9_CSE1_DP_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc9_CSE1_DPInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc9_CSE1_DPInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_DPMachineNumber_,
           9,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"X");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Y");
          _SFD_SET_DATA_PROPS(2,2,0,1,"u_BT");
          _SFD_SET_DATA_PROPS(3,1,1,0,"N");
          _SFD_SET_DATA_PROPS(4,2,0,1,"u_VSP");
          _SFD_SET_DATA_PROPS(5,2,0,1,"alpha_VSP");
          _SFD_SET_DATA_PROPS(6,1,1,0,"VSP_on");
          _SFD_SET_DATA_PROPS(7,2,0,1,"omega_VSP");
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
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,639);
        _SFD_CV_INIT_EML_IF(0,1,0,581,590,612,639);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)c9_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)c9_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)c9_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)c9_sf_marshallIn);

        {
          real_T *c9_X;
          real_T *c9_Y;
          real_T *c9_u_BT;
          real_T *c9_N;
          real_T *c9_u_VSP;
          real_T *c9_alpha_VSP;
          real_T *c9_VSP_on;
          real_T *c9_omega_VSP;
          c9_omega_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c9_VSP_on = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c9_alpha_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c9_u_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c9_N = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c9_u_BT = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c9_Y = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c9_X = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c9_X);
          _SFD_SET_DATA_VALUE_PTR(1U, c9_Y);
          _SFD_SET_DATA_VALUE_PTR(2U, c9_u_BT);
          _SFD_SET_DATA_VALUE_PTR(3U, c9_N);
          _SFD_SET_DATA_VALUE_PTR(4U, c9_u_VSP);
          _SFD_SET_DATA_VALUE_PTR(5U, c9_alpha_VSP);
          _SFD_SET_DATA_VALUE_PTR(6U, c9_VSP_on);
          _SFD_SET_DATA_VALUE_PTR(7U, c9_omega_VSP);
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
  return "QYwTYRpCKeloDZt7PfG9cH";
}

static void sf_opaque_initialize_c9_CSE1_DP(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar);
  initialize_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c9_CSE1_DP(void *chartInstanceVar)
{
  enable_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c9_CSE1_DP(void *chartInstanceVar)
{
  disable_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c9_CSE1_DP(void *chartInstanceVar)
{
  sf_gateway_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c9_CSE1_DP(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_CSE1_DP();/* state var info */
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

extern void sf_internal_set_sim_state_c9_CSE1_DP(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c9_CSE1_DP();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c9_CSE1_DP(SimStruct* S)
{
  return sf_internal_get_sim_state_c9_CSE1_DP(S);
}

static void sf_opaque_set_sim_state_c9_CSE1_DP(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c9_CSE1_DP(S, st);
}

static void sf_opaque_terminate_c9_CSE1_DP(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_DP_optimization_info();
    }

    finalize_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c9_CSE1_DP(SimStruct *S)
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
    initialize_params_c9_CSE1_DP((SFc9_CSE1_DPInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c9_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_DP_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,9);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,9,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,9,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,9);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,9,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,9,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,9);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(550894419U));
  ssSetChecksum1(S,(2005775543U));
  ssSetChecksum2(S,(3404300522U));
  ssSetChecksum3(S,(2566869980U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c9_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c9_CSE1_DP(SimStruct *S)
{
  SFc9_CSE1_DPInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc9_CSE1_DPInstanceStruct *)utMalloc(sizeof
    (SFc9_CSE1_DPInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc9_CSE1_DPInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c9_CSE1_DP;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c9_CSE1_DP;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c9_CSE1_DP;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c9_CSE1_DP;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c9_CSE1_DP;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c9_CSE1_DP;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c9_CSE1_DP;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c9_CSE1_DP;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c9_CSE1_DP;
  chartInstance->chartInfo.mdlStart = mdlStart_c9_CSE1_DP;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c9_CSE1_DP;
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

void c9_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c9_CSE1_DP(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c9_CSE1_DP(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c9_CSE1_DP(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c9_CSE1_DP_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
