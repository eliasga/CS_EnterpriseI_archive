/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_DP_sfun.h"
#include "c11_CSE1_DP.h"
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
static const char * c11_debug_family_names[20] = { "tau", "l_VSP", "l_BT", "T",
  "F_max_VSP", "F_max_BT", "K", "u", "u_VSP_x", "u_VSP_y", "nargin", "nargout",
  "X", "Y", "N", "VSP_on", "u_BT", "u_VSP", "alpha_VSP", "omega_VSP" };

/* Function Declarations */
static void initialize_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance);
static void initialize_params_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct
  *chartInstance);
static void enable_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance);
static void disable_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance);
static void c11_update_debugger_state_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct
  *chartInstance);
static void set_sim_state_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_st);
static void finalize_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance);
static void sf_gateway_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance);
static void initSimStructsc11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber, uint32_T c11_instanceNumber);
static const mxArray *c11_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static real_T c11_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_omega_VSP, const char_T *c11_identifier);
static real_T c11_b_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_b_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static void c11_c_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId, real_T c11_y[3]);
static void c11_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_c_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static void c11_info_helper(const mxArray **c11_info);
static const mxArray *c11_emlrt_marshallOut(const char * c11_u);
static const mxArray *c11_b_emlrt_marshallOut(const uint32_T c11_u);
static void c11_mldivide(SFc11_CSE1_DPInstanceStruct *chartInstance, real_T
  c11_A[9], real_T c11_B[3], real_T c11_Y[3]);
static void c11_eml_warning(SFc11_CSE1_DPInstanceStruct *chartInstance);
static real_T c11_mpower(SFc11_CSE1_DPInstanceStruct *chartInstance, real_T
  c11_a);
static void c11_eml_scalar_eg(SFc11_CSE1_DPInstanceStruct *chartInstance);
static void c11_eml_error(SFc11_CSE1_DPInstanceStruct *chartInstance);
static const mxArray *c11_d_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static int32_T c11_d_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static uint8_T c11_e_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_b_is_active_c11_CSE1_DP, const char_T *c11_identifier);
static uint8_T c11_f_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void init_dsm_address_info(SFc11_CSE1_DPInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  chartInstance->c11_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c11_is_active_c11_CSE1_DP = 0U;
}

static void initialize_params_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c11_update_debugger_state_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct
  *chartInstance)
{
  const mxArray *c11_st;
  const mxArray *c11_y = NULL;
  real_T c11_hoistedGlobal;
  real_T c11_u;
  const mxArray *c11_b_y = NULL;
  real_T c11_b_hoistedGlobal;
  real_T c11_b_u;
  const mxArray *c11_c_y = NULL;
  real_T c11_c_hoistedGlobal;
  real_T c11_c_u;
  const mxArray *c11_d_y = NULL;
  real_T c11_d_hoistedGlobal;
  real_T c11_d_u;
  const mxArray *c11_e_y = NULL;
  uint8_T c11_e_hoistedGlobal;
  uint8_T c11_e_u;
  const mxArray *c11_f_y = NULL;
  real_T *c11_alpha_VSP;
  real_T *c11_omega_VSP;
  real_T *c11_u_BT;
  real_T *c11_u_VSP;
  c11_omega_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c11_alpha_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c11_u_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c11_u_BT = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c11_st = NULL;
  c11_st = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_createcellmatrix(5, 1), false);
  c11_hoistedGlobal = *c11_alpha_VSP;
  c11_u = c11_hoistedGlobal;
  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", &c11_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 0, c11_b_y);
  c11_b_hoistedGlobal = *c11_omega_VSP;
  c11_b_u = c11_b_hoistedGlobal;
  c11_c_y = NULL;
  sf_mex_assign(&c11_c_y, sf_mex_create("y", &c11_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 1, c11_c_y);
  c11_c_hoistedGlobal = *c11_u_BT;
  c11_c_u = c11_c_hoistedGlobal;
  c11_d_y = NULL;
  sf_mex_assign(&c11_d_y, sf_mex_create("y", &c11_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 2, c11_d_y);
  c11_d_hoistedGlobal = *c11_u_VSP;
  c11_d_u = c11_d_hoistedGlobal;
  c11_e_y = NULL;
  sf_mex_assign(&c11_e_y, sf_mex_create("y", &c11_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 3, c11_e_y);
  c11_e_hoistedGlobal = chartInstance->c11_is_active_c11_CSE1_DP;
  c11_e_u = c11_e_hoistedGlobal;
  c11_f_y = NULL;
  sf_mex_assign(&c11_f_y, sf_mex_create("y", &c11_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 4, c11_f_y);
  sf_mex_assign(&c11_st, c11_y, false);
  return c11_st;
}

static void set_sim_state_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_st)
{
  const mxArray *c11_u;
  real_T *c11_alpha_VSP;
  real_T *c11_omega_VSP;
  real_T *c11_u_BT;
  real_T *c11_u_VSP;
  c11_omega_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c11_alpha_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c11_u_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c11_u_BT = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c11_doneDoubleBufferReInit = true;
  c11_u = sf_mex_dup(c11_st);
  *c11_alpha_VSP = c11_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c11_u, 0)), "alpha_VSP");
  *c11_omega_VSP = c11_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c11_u, 1)), "omega_VSP");
  *c11_u_BT = c11_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c11_u, 2)), "u_BT");
  *c11_u_VSP = c11_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c11_u, 3)), "u_VSP");
  chartInstance->c11_is_active_c11_CSE1_DP = c11_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c11_u, 4)),
     "is_active_c11_CSE1_DP");
  sf_mex_destroy(&c11_u);
  c11_update_debugger_state_c11_CSE1_DP(chartInstance);
  sf_mex_destroy(&c11_st);
}

static void finalize_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  real_T c11_hoistedGlobal;
  real_T c11_b_hoistedGlobal;
  real_T c11_c_hoistedGlobal;
  real_T c11_d_hoistedGlobal;
  real_T c11_X;
  real_T c11_Y;
  real_T c11_N;
  real_T c11_VSP_on;
  uint32_T c11_debug_family_var_map[20];
  real_T c11_tau[3];
  real_T c11_l_VSP;
  real_T c11_l_BT;
  real_T c11_T[9];
  real_T c11_F_max_VSP;
  real_T c11_F_max_BT;
  real_T c11_K[9];
  real_T c11_u[3];
  real_T c11_u_VSP_x;
  real_T c11_u_VSP_y;
  real_T c11_nargin = 4.0;
  real_T c11_nargout = 4.0;
  real_T c11_u_BT;
  real_T c11_u_VSP;
  real_T c11_alpha_VSP;
  real_T c11_omega_VSP;
  int32_T c11_i0;
  static real_T c11_dv0[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, -0.4575, 0.0, 1.0,
    0.3875 };

  int32_T c11_i1;
  static real_T c11_dv1[9] = { 1.165, 0.0, 0.0, 0.0, 1.165, 0.0, 0.0, 0.0, 2.629
  };

  int32_T c11_i2;
  static real_T c11_dv2[9] = { 1.165, 0.0, 0.0, 0.0, 1.165, -0.53298750000000006,
    0.0, 2.629, 1.0187375 };

  real_T c11_dv3[9];
  int32_T c11_i3;
  real_T c11_b_tau[3];
  real_T c11_dv4[3];
  int32_T c11_i4;
  real_T c11_x;
  real_T c11_b_x;
  real_T c11_y;
  real_T c11_c_x;
  real_T c11_b_y;
  real_T c11_d_x;
  real_T *c11_b_X;
  real_T *c11_b_Y;
  real_T *c11_b_u_BT;
  real_T *c11_b_N;
  real_T *c11_b_u_VSP;
  real_T *c11_b_alpha_VSP;
  real_T *c11_b_VSP_on;
  real_T *c11_b_omega_VSP;
  c11_b_omega_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c11_b_VSP_on = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c11_b_alpha_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c11_b_u_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c11_b_N = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c11_b_u_BT = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c11_b_Y = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c11_b_X = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 10U, chartInstance->c11_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c11_b_X, 0U);
  _SFD_DATA_RANGE_CHECK(*c11_b_Y, 1U);
  chartInstance->c11_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 10U, chartInstance->c11_sfEvent);
  c11_hoistedGlobal = *c11_b_X;
  c11_b_hoistedGlobal = *c11_b_Y;
  c11_c_hoistedGlobal = *c11_b_N;
  c11_d_hoistedGlobal = *c11_b_VSP_on;
  c11_X = c11_hoistedGlobal;
  c11_Y = c11_b_hoistedGlobal;
  c11_N = c11_c_hoistedGlobal;
  c11_VSP_on = c11_d_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 20U, 20U, c11_debug_family_names,
    c11_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c11_tau, 0U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_l_VSP, 1U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_l_BT, 2U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_T, 3U, c11_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_F_max_VSP, 4U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_F_max_BT, 5U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_K, 6U, c11_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c11_u, 7U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_u_VSP_x, 8U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_u_VSP_y, 9U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_nargin, 10U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_nargout, 11U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_X, 12U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_Y, 13U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_N, 14U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_VSP_on, 15U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_u_BT, 16U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_u_VSP, 17U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_alpha_VSP, 18U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_omega_VSP, 19U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 4);
  c11_tau[0] = c11_X;
  c11_tau[1] = c11_Y;
  c11_tau[2] = c11_N;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 9);
  c11_l_VSP = -0.4575;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 10);
  c11_l_BT = 0.3875;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 11);
  for (c11_i0 = 0; c11_i0 < 9; c11_i0++) {
    c11_T[c11_i0] = c11_dv0[c11_i0];
  }

  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 16);
  c11_F_max_VSP = 1.165;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 17);
  c11_F_max_BT = 2.629;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 18);
  for (c11_i1 = 0; c11_i1 < 9; c11_i1++) {
    c11_K[c11_i1] = c11_dv1[c11_i1];
  }

  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 23);
  for (c11_i2 = 0; c11_i2 < 9; c11_i2++) {
    c11_dv3[c11_i2] = c11_dv2[c11_i2];
  }

  for (c11_i3 = 0; c11_i3 < 3; c11_i3++) {
    c11_b_tau[c11_i3] = c11_tau[c11_i3];
  }

  c11_mldivide(chartInstance, c11_dv3, c11_b_tau, c11_dv4);
  for (c11_i4 = 0; c11_i4 < 3; c11_i4++) {
    c11_u[c11_i4] = c11_dv4[c11_i4];
  }

  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 25);
  c11_u_BT = c11_u[2];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 27);
  c11_u_VSP_x = c11_u[0];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 28);
  c11_u_VSP_y = c11_u[1];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 29);
  c11_x = c11_mpower(chartInstance, c11_u_VSP_x) + c11_mpower(chartInstance,
    c11_u_VSP_y);
  c11_u_VSP = c11_x;
  if (c11_u_VSP < 0.0) {
    c11_eml_error(chartInstance);
  }

  c11_b_x = c11_u_VSP;
  c11_u_VSP = c11_b_x;
  c11_u_VSP = muDoubleScalarSqrt(c11_u_VSP);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 30);
  c11_y = c11_u_VSP_y;
  c11_c_x = c11_u_VSP_x;
  c11_eml_scalar_eg(chartInstance);
  c11_b_y = c11_y;
  c11_d_x = c11_c_x;
  c11_alpha_VSP = muDoubleScalarAtan2(c11_b_y, c11_d_x);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 32);
  if (CV_EML_IF(0, 1, 0, c11_VSP_on != 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 33);
    c11_omega_VSP = 0.3;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 35);
    c11_omega_VSP = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, -35);
  _SFD_SYMBOL_SCOPE_POP();
  *c11_b_u_BT = c11_u_BT;
  *c11_b_u_VSP = c11_u_VSP;
  *c11_b_alpha_VSP = c11_alpha_VSP;
  *c11_b_omega_VSP = c11_omega_VSP;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c11_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_DPMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c11_b_u_BT, 2U);
  _SFD_DATA_RANGE_CHECK(*c11_b_N, 3U);
  _SFD_DATA_RANGE_CHECK(*c11_b_u_VSP, 4U);
  _SFD_DATA_RANGE_CHECK(*c11_b_alpha_VSP, 5U);
  _SFD_DATA_RANGE_CHECK(*c11_b_VSP_on, 6U);
  _SFD_DATA_RANGE_CHECK(*c11_b_omega_VSP, 7U);
}

static void initSimStructsc11_CSE1_DP(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber, uint32_T c11_instanceNumber)
{
  (void)c11_machineNumber;
  (void)c11_chartNumber;
  (void)c11_instanceNumber;
}

static const mxArray *c11_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  real_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc11_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(real_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static real_T c11_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_omega_VSP, const char_T *c11_identifier)
{
  real_T c11_y;
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_omega_VSP),
    &c11_thisId);
  sf_mex_destroy(&c11_omega_VSP);
  return c11_y;
}

static real_T c11_b_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  real_T c11_y;
  real_T c11_d0;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_d0, 1, 0, 0U, 0, 0U, 0);
  c11_y = c11_d0;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_omega_VSP;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  real_T c11_y;
  SFc11_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc11_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c11_omega_VSP = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_omega_VSP),
    &c11_thisId);
  sf_mex_destroy(&c11_omega_VSP);
  *(real_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

static const mxArray *c11_b_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_i5;
  real_T c11_b_inData[3];
  int32_T c11_i6;
  real_T c11_u[3];
  const mxArray *c11_y = NULL;
  SFc11_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc11_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  for (c11_i5 = 0; c11_i5 < 3; c11_i5++) {
    c11_b_inData[c11_i5] = (*(real_T (*)[3])c11_inData)[c11_i5];
  }

  for (c11_i6 = 0; c11_i6 < 3; c11_i6++) {
    c11_u[c11_i6] = c11_b_inData[c11_i6];
  }

  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static void c11_c_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId, real_T c11_y[3])
{
  real_T c11_dv5[3];
  int32_T c11_i7;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), c11_dv5, 1, 0, 0U, 1, 0U, 1, 3);
  for (c11_i7 = 0; c11_i7 < 3; c11_i7++) {
    c11_y[c11_i7] = c11_dv5[c11_i7];
  }

  sf_mex_destroy(&c11_u);
}

static void c11_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_u;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  real_T c11_y[3];
  int32_T c11_i8;
  SFc11_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc11_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c11_u = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_u), &c11_thisId, c11_y);
  sf_mex_destroy(&c11_u);
  for (c11_i8 = 0; c11_i8 < 3; c11_i8++) {
    (*(real_T (*)[3])c11_outData)[c11_i8] = c11_y[c11_i8];
  }

  sf_mex_destroy(&c11_mxArrayInData);
}

static const mxArray *c11_c_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_i9;
  int32_T c11_i10;
  int32_T c11_i11;
  real_T c11_b_inData[9];
  int32_T c11_i12;
  int32_T c11_i13;
  int32_T c11_i14;
  real_T c11_u[9];
  const mxArray *c11_y = NULL;
  SFc11_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc11_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_i9 = 0;
  for (c11_i10 = 0; c11_i10 < 3; c11_i10++) {
    for (c11_i11 = 0; c11_i11 < 3; c11_i11++) {
      c11_b_inData[c11_i11 + c11_i9] = (*(real_T (*)[9])c11_inData)[c11_i11 +
        c11_i9];
    }

    c11_i9 += 3;
  }

  c11_i12 = 0;
  for (c11_i13 = 0; c11_i13 < 3; c11_i13++) {
    for (c11_i14 = 0; c11_i14 < 3; c11_i14++) {
      c11_u[c11_i14 + c11_i12] = c11_b_inData[c11_i14 + c11_i12];
    }

    c11_i12 += 3;
  }

  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

const mxArray *sf_c11_CSE1_DP_get_eml_resolved_functions_info(void)
{
  const mxArray *c11_nameCaptureInfo = NULL;
  c11_nameCaptureInfo = NULL;
  sf_mex_assign(&c11_nameCaptureInfo, sf_mex_createstruct("structure", 2, 46, 1),
                false);
  c11_info_helper(&c11_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c11_nameCaptureInfo);
  return c11_nameCaptureInfo;
}

static void c11_info_helper(const mxArray **c11_info)
{
  const mxArray *c11_rhs0 = NULL;
  const mxArray *c11_lhs0 = NULL;
  const mxArray *c11_rhs1 = NULL;
  const mxArray *c11_lhs1 = NULL;
  const mxArray *c11_rhs2 = NULL;
  const mxArray *c11_lhs2 = NULL;
  const mxArray *c11_rhs3 = NULL;
  const mxArray *c11_lhs3 = NULL;
  const mxArray *c11_rhs4 = NULL;
  const mxArray *c11_lhs4 = NULL;
  const mxArray *c11_rhs5 = NULL;
  const mxArray *c11_lhs5 = NULL;
  const mxArray *c11_rhs6 = NULL;
  const mxArray *c11_lhs6 = NULL;
  const mxArray *c11_rhs7 = NULL;
  const mxArray *c11_lhs7 = NULL;
  const mxArray *c11_rhs8 = NULL;
  const mxArray *c11_lhs8 = NULL;
  const mxArray *c11_rhs9 = NULL;
  const mxArray *c11_lhs9 = NULL;
  const mxArray *c11_rhs10 = NULL;
  const mxArray *c11_lhs10 = NULL;
  const mxArray *c11_rhs11 = NULL;
  const mxArray *c11_lhs11 = NULL;
  const mxArray *c11_rhs12 = NULL;
  const mxArray *c11_lhs12 = NULL;
  const mxArray *c11_rhs13 = NULL;
  const mxArray *c11_lhs13 = NULL;
  const mxArray *c11_rhs14 = NULL;
  const mxArray *c11_lhs14 = NULL;
  const mxArray *c11_rhs15 = NULL;
  const mxArray *c11_lhs15 = NULL;
  const mxArray *c11_rhs16 = NULL;
  const mxArray *c11_lhs16 = NULL;
  const mxArray *c11_rhs17 = NULL;
  const mxArray *c11_lhs17 = NULL;
  const mxArray *c11_rhs18 = NULL;
  const mxArray *c11_lhs18 = NULL;
  const mxArray *c11_rhs19 = NULL;
  const mxArray *c11_lhs19 = NULL;
  const mxArray *c11_rhs20 = NULL;
  const mxArray *c11_lhs20 = NULL;
  const mxArray *c11_rhs21 = NULL;
  const mxArray *c11_lhs21 = NULL;
  const mxArray *c11_rhs22 = NULL;
  const mxArray *c11_lhs22 = NULL;
  const mxArray *c11_rhs23 = NULL;
  const mxArray *c11_lhs23 = NULL;
  const mxArray *c11_rhs24 = NULL;
  const mxArray *c11_lhs24 = NULL;
  const mxArray *c11_rhs25 = NULL;
  const mxArray *c11_lhs25 = NULL;
  const mxArray *c11_rhs26 = NULL;
  const mxArray *c11_lhs26 = NULL;
  const mxArray *c11_rhs27 = NULL;
  const mxArray *c11_lhs27 = NULL;
  const mxArray *c11_rhs28 = NULL;
  const mxArray *c11_lhs28 = NULL;
  const mxArray *c11_rhs29 = NULL;
  const mxArray *c11_lhs29 = NULL;
  const mxArray *c11_rhs30 = NULL;
  const mxArray *c11_lhs30 = NULL;
  const mxArray *c11_rhs31 = NULL;
  const mxArray *c11_lhs31 = NULL;
  const mxArray *c11_rhs32 = NULL;
  const mxArray *c11_lhs32 = NULL;
  const mxArray *c11_rhs33 = NULL;
  const mxArray *c11_lhs33 = NULL;
  const mxArray *c11_rhs34 = NULL;
  const mxArray *c11_lhs34 = NULL;
  const mxArray *c11_rhs35 = NULL;
  const mxArray *c11_lhs35 = NULL;
  const mxArray *c11_rhs36 = NULL;
  const mxArray *c11_lhs36 = NULL;
  const mxArray *c11_rhs37 = NULL;
  const mxArray *c11_lhs37 = NULL;
  const mxArray *c11_rhs38 = NULL;
  const mxArray *c11_lhs38 = NULL;
  const mxArray *c11_rhs39 = NULL;
  const mxArray *c11_lhs39 = NULL;
  const mxArray *c11_rhs40 = NULL;
  const mxArray *c11_lhs40 = NULL;
  const mxArray *c11_rhs41 = NULL;
  const mxArray *c11_lhs41 = NULL;
  const mxArray *c11_rhs42 = NULL;
  const mxArray *c11_lhs42 = NULL;
  const mxArray *c11_rhs43 = NULL;
  const mxArray *c11_lhs43 = NULL;
  const mxArray *c11_rhs44 = NULL;
  const mxArray *c11_lhs44 = NULL;
  const mxArray *c11_rhs45 = NULL;
  const mxArray *c11_lhs45 = NULL;
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c11_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c11_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 2);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c11_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c11_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c11_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  5);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c11_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 6);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c11_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 7);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c11_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 8);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 8);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c11_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 9);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.blas.threshold"), "name", "name", 9);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c11_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 10);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 10);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c11_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 11);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c11_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.refblas.xgemm"), "name", "name", 12);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c11_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "context", "context", 13);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("mldivide"), "name", "name",
                  13);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1319729966U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c11_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "context",
                  "context", 14);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_lusolve"), "name",
                  "name", 14);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1370009886U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c11_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3"),
                  "context", "context", 15);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_xcabs1"), "name", "name",
                  15);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c11_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m"),
                  "context", "context", 16);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.refblas.xcabs1"), "name", "name", 16);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c11_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "context", "context", 17);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("abs"), "name", "name", 17);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c11_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 18);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c11_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 19);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c11_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3"),
                  "context", "context", 20);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("rdivide"), "name", "name",
                  20);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c11_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 21);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c11_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 22);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 22);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c11_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 23);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_div"), "name", "name",
                  23);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c11_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 24);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 24);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 24);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c11_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!warn_singular"),
                  "context", "context", 25);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_warning"), "name",
                  "name", 25);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m"), "resolved",
                  "resolved", 25);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1286818802U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c11_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3"),
                  "context", "context", 26);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 26);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 26);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c11_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "context", "context", 27);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("mpower"), "name", "name", 27);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 27);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c11_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 28);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c11_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("ismatrix"), "name", "name",
                  29);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 29);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c11_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 30);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("power"), "name", "name", 30);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 30);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c11_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 31);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 31);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c11_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 32);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 32);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 32);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c11_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 33);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 33);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c11_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 34);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c11_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 35);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("floor"), "name", "name", 35);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 35);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c11_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 36);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 36);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c11_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 37);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 37);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c11_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 38);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 38);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 38);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c11_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "context", "context", 39);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("sqrt"), "name", "name", 39);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 39);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c11_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 40);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_error"), "name", "name",
                  40);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 40);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c11_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 41);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_sqrt"), "name",
                  "name", 41);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m"),
                  "resolved", "resolved", 41);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1286818738U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c11_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "context", "context", 42);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("atan2"), "name", "name", 42);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "resolved",
                  "resolved", 42);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c11_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 43);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 43);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c11_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 44);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 44);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 44);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c11_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 45);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_atan2"), "name",
                  "name", 45);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1286818720U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c11_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs45), "lhs", "lhs",
                  45);
  sf_mex_destroy(&c11_rhs0);
  sf_mex_destroy(&c11_lhs0);
  sf_mex_destroy(&c11_rhs1);
  sf_mex_destroy(&c11_lhs1);
  sf_mex_destroy(&c11_rhs2);
  sf_mex_destroy(&c11_lhs2);
  sf_mex_destroy(&c11_rhs3);
  sf_mex_destroy(&c11_lhs3);
  sf_mex_destroy(&c11_rhs4);
  sf_mex_destroy(&c11_lhs4);
  sf_mex_destroy(&c11_rhs5);
  sf_mex_destroy(&c11_lhs5);
  sf_mex_destroy(&c11_rhs6);
  sf_mex_destroy(&c11_lhs6);
  sf_mex_destroy(&c11_rhs7);
  sf_mex_destroy(&c11_lhs7);
  sf_mex_destroy(&c11_rhs8);
  sf_mex_destroy(&c11_lhs8);
  sf_mex_destroy(&c11_rhs9);
  sf_mex_destroy(&c11_lhs9);
  sf_mex_destroy(&c11_rhs10);
  sf_mex_destroy(&c11_lhs10);
  sf_mex_destroy(&c11_rhs11);
  sf_mex_destroy(&c11_lhs11);
  sf_mex_destroy(&c11_rhs12);
  sf_mex_destroy(&c11_lhs12);
  sf_mex_destroy(&c11_rhs13);
  sf_mex_destroy(&c11_lhs13);
  sf_mex_destroy(&c11_rhs14);
  sf_mex_destroy(&c11_lhs14);
  sf_mex_destroy(&c11_rhs15);
  sf_mex_destroy(&c11_lhs15);
  sf_mex_destroy(&c11_rhs16);
  sf_mex_destroy(&c11_lhs16);
  sf_mex_destroy(&c11_rhs17);
  sf_mex_destroy(&c11_lhs17);
  sf_mex_destroy(&c11_rhs18);
  sf_mex_destroy(&c11_lhs18);
  sf_mex_destroy(&c11_rhs19);
  sf_mex_destroy(&c11_lhs19);
  sf_mex_destroy(&c11_rhs20);
  sf_mex_destroy(&c11_lhs20);
  sf_mex_destroy(&c11_rhs21);
  sf_mex_destroy(&c11_lhs21);
  sf_mex_destroy(&c11_rhs22);
  sf_mex_destroy(&c11_lhs22);
  sf_mex_destroy(&c11_rhs23);
  sf_mex_destroy(&c11_lhs23);
  sf_mex_destroy(&c11_rhs24);
  sf_mex_destroy(&c11_lhs24);
  sf_mex_destroy(&c11_rhs25);
  sf_mex_destroy(&c11_lhs25);
  sf_mex_destroy(&c11_rhs26);
  sf_mex_destroy(&c11_lhs26);
  sf_mex_destroy(&c11_rhs27);
  sf_mex_destroy(&c11_lhs27);
  sf_mex_destroy(&c11_rhs28);
  sf_mex_destroy(&c11_lhs28);
  sf_mex_destroy(&c11_rhs29);
  sf_mex_destroy(&c11_lhs29);
  sf_mex_destroy(&c11_rhs30);
  sf_mex_destroy(&c11_lhs30);
  sf_mex_destroy(&c11_rhs31);
  sf_mex_destroy(&c11_lhs31);
  sf_mex_destroy(&c11_rhs32);
  sf_mex_destroy(&c11_lhs32);
  sf_mex_destroy(&c11_rhs33);
  sf_mex_destroy(&c11_lhs33);
  sf_mex_destroy(&c11_rhs34);
  sf_mex_destroy(&c11_lhs34);
  sf_mex_destroy(&c11_rhs35);
  sf_mex_destroy(&c11_lhs35);
  sf_mex_destroy(&c11_rhs36);
  sf_mex_destroy(&c11_lhs36);
  sf_mex_destroy(&c11_rhs37);
  sf_mex_destroy(&c11_lhs37);
  sf_mex_destroy(&c11_rhs38);
  sf_mex_destroy(&c11_lhs38);
  sf_mex_destroy(&c11_rhs39);
  sf_mex_destroy(&c11_lhs39);
  sf_mex_destroy(&c11_rhs40);
  sf_mex_destroy(&c11_lhs40);
  sf_mex_destroy(&c11_rhs41);
  sf_mex_destroy(&c11_lhs41);
  sf_mex_destroy(&c11_rhs42);
  sf_mex_destroy(&c11_lhs42);
  sf_mex_destroy(&c11_rhs43);
  sf_mex_destroy(&c11_lhs43);
  sf_mex_destroy(&c11_rhs44);
  sf_mex_destroy(&c11_lhs44);
  sf_mex_destroy(&c11_rhs45);
  sf_mex_destroy(&c11_lhs45);
}

static const mxArray *c11_emlrt_marshallOut(const char * c11_u)
{
  const mxArray *c11_y = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c11_u)), false);
  return c11_y;
}

static const mxArray *c11_b_emlrt_marshallOut(const uint32_T c11_u)
{
  const mxArray *c11_y = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 7, 0U, 0U, 0U, 0), false);
  return c11_y;
}

static void c11_mldivide(SFc11_CSE1_DPInstanceStruct *chartInstance, real_T
  c11_A[9], real_T c11_B[3], real_T c11_Y[3])
{
  int32_T c11_i15;
  real_T c11_b_A[9];
  int32_T c11_r1;
  int32_T c11_r2;
  int32_T c11_r3;
  real_T c11_x;
  real_T c11_b_x;
  real_T c11_c_x;
  real_T c11_d_x;
  real_T c11_y;
  real_T c11_e_x;
  real_T c11_f_x;
  real_T c11_b_y;
  real_T c11_maxval;
  real_T c11_g_x;
  real_T c11_h_x;
  real_T c11_i_x;
  real_T c11_j_x;
  real_T c11_c_y;
  real_T c11_k_x;
  real_T c11_l_x;
  real_T c11_d_y;
  real_T c11_a21;
  real_T c11_m_x;
  real_T c11_n_x;
  real_T c11_o_x;
  real_T c11_p_x;
  real_T c11_e_y;
  real_T c11_q_x;
  real_T c11_r_x;
  real_T c11_f_y;
  real_T c11_d;
  real_T c11_s_x;
  real_T c11_g_y;
  real_T c11_t_x;
  real_T c11_h_y;
  real_T c11_u_x;
  real_T c11_i_y;
  real_T c11_z;
  real_T c11_v_x;
  real_T c11_j_y;
  real_T c11_w_x;
  real_T c11_k_y;
  real_T c11_x_x;
  real_T c11_l_y;
  real_T c11_b_z;
  real_T c11_y_x;
  real_T c11_ab_x;
  real_T c11_bb_x;
  real_T c11_cb_x;
  real_T c11_m_y;
  real_T c11_db_x;
  real_T c11_eb_x;
  real_T c11_n_y;
  real_T c11_b_d;
  real_T c11_fb_x;
  real_T c11_gb_x;
  real_T c11_hb_x;
  real_T c11_ib_x;
  real_T c11_o_y;
  real_T c11_jb_x;
  real_T c11_kb_x;
  real_T c11_p_y;
  real_T c11_c_d;
  int32_T c11_rtemp;
  real_T c11_lb_x;
  real_T c11_q_y;
  real_T c11_mb_x;
  real_T c11_r_y;
  real_T c11_nb_x;
  real_T c11_s_y;
  real_T c11_c_z;
  real_T c11_ob_x;
  real_T c11_t_y;
  real_T c11_pb_x;
  real_T c11_u_y;
  real_T c11_qb_x;
  real_T c11_v_y;
  real_T c11_d_z;
  real_T c11_rb_x;
  real_T c11_w_y;
  real_T c11_sb_x;
  real_T c11_x_y;
  real_T c11_tb_x;
  real_T c11_y_y;
  real_T c11_e_z;
  real_T c11_ub_x;
  real_T c11_ab_y;
  real_T c11_vb_x;
  real_T c11_bb_y;
  real_T c11_wb_x;
  real_T c11_cb_y;
  real_T c11_f_z;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  for (c11_i15 = 0; c11_i15 < 9; c11_i15++) {
    c11_b_A[c11_i15] = c11_A[c11_i15];
  }

  c11_r1 = 1;
  c11_r2 = 2;
  c11_r3 = 3;
  c11_x = c11_b_A[0];
  c11_b_x = c11_x;
  c11_c_x = c11_b_x;
  c11_d_x = c11_c_x;
  c11_y = muDoubleScalarAbs(c11_d_x);
  c11_e_x = 0.0;
  c11_f_x = c11_e_x;
  c11_b_y = muDoubleScalarAbs(c11_f_x);
  c11_maxval = c11_y + c11_b_y;
  c11_g_x = c11_b_A[1];
  c11_h_x = c11_g_x;
  c11_i_x = c11_h_x;
  c11_j_x = c11_i_x;
  c11_c_y = muDoubleScalarAbs(c11_j_x);
  c11_k_x = 0.0;
  c11_l_x = c11_k_x;
  c11_d_y = muDoubleScalarAbs(c11_l_x);
  c11_a21 = c11_c_y + c11_d_y;
  if (c11_a21 > c11_maxval) {
    c11_maxval = c11_a21;
    c11_r1 = 2;
    c11_r2 = 1;
  }

  c11_m_x = c11_b_A[2];
  c11_n_x = c11_m_x;
  c11_o_x = c11_n_x;
  c11_p_x = c11_o_x;
  c11_e_y = muDoubleScalarAbs(c11_p_x);
  c11_q_x = 0.0;
  c11_r_x = c11_q_x;
  c11_f_y = muDoubleScalarAbs(c11_r_x);
  c11_d = c11_e_y + c11_f_y;
  if (c11_d > c11_maxval) {
    c11_r1 = 3;
    c11_r2 = 2;
    c11_r3 = 1;
  }

  c11_s_x = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r2), 1, 3, 1, 0) - 1];
  c11_g_y = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r1), 1, 3, 1, 0) - 1];
  c11_t_x = c11_s_x;
  c11_h_y = c11_g_y;
  c11_u_x = c11_t_x;
  c11_i_y = c11_h_y;
  c11_z = c11_u_x / c11_i_y;
  c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r2), 1, 3, 1, 0) - 1] = c11_z;
  c11_v_x = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r3), 1, 3, 1, 0) - 1];
  c11_j_y = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r1), 1, 3, 1, 0) - 1];
  c11_w_x = c11_v_x;
  c11_k_y = c11_j_y;
  c11_x_x = c11_w_x;
  c11_l_y = c11_k_y;
  c11_b_z = c11_x_x / c11_l_y;
  c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) - 1] = c11_b_z;
  c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r2), 1, 3, 1, 0) + 2] = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r2), 1, 3, 1, 0) + 2] -
    c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r2), 1, 3, 1, 0) - 1] * c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r1), 1, 3, 1, 0) + 2];
  c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) + 2] = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r3), 1, 3, 1, 0) + 2] -
    c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) - 1] * c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r1), 1, 3, 1, 0) + 2];
  c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r2), 1, 3, 1, 0) + 5] = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r2), 1, 3, 1, 0) + 5] -
    c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r2), 1, 3, 1, 0) - 1] * c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r1), 1, 3, 1, 0) + 5];
  c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) + 5] = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r3), 1, 3, 1, 0) + 5] -
    c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) - 1] * c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r1), 1, 3, 1, 0) + 5];
  c11_y_x = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r3), 1, 3, 1, 0) + 2];
  c11_ab_x = c11_y_x;
  c11_bb_x = c11_ab_x;
  c11_cb_x = c11_bb_x;
  c11_m_y = muDoubleScalarAbs(c11_cb_x);
  c11_db_x = 0.0;
  c11_eb_x = c11_db_x;
  c11_n_y = muDoubleScalarAbs(c11_eb_x);
  c11_b_d = c11_m_y + c11_n_y;
  c11_fb_x = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
    ("", (real_T)c11_r2), 1, 3, 1, 0) + 2];
  c11_gb_x = c11_fb_x;
  c11_hb_x = c11_gb_x;
  c11_ib_x = c11_hb_x;
  c11_o_y = muDoubleScalarAbs(c11_ib_x);
  c11_jb_x = 0.0;
  c11_kb_x = c11_jb_x;
  c11_p_y = muDoubleScalarAbs(c11_kb_x);
  c11_c_d = c11_o_y + c11_p_y;
  if (c11_b_d > c11_c_d) {
    c11_rtemp = c11_r2;
    c11_r2 = c11_r3;
    c11_r3 = c11_rtemp;
  }

  c11_lb_x = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
    ("", (real_T)c11_r3), 1, 3, 1, 0) + 2];
  c11_q_y = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r2), 1, 3, 1, 0) + 2];
  c11_mb_x = c11_lb_x;
  c11_r_y = c11_q_y;
  c11_nb_x = c11_mb_x;
  c11_s_y = c11_r_y;
  c11_c_z = c11_nb_x / c11_s_y;
  c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) + 2] = c11_c_z;
  c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) + 5] = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r3), 1, 3, 1, 0) + 5] -
    c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) + 2] * c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c11_r2), 1, 3, 1, 0) + 5];
  guard1 = false;
  guard2 = false;
  if (c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c11_r1), 1, 3, 1, 0) - 1] == 0.0) {
    guard2 = true;
  } else if (c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
              ("", (real_T)c11_r2), 1, 3, 1, 0) + 2] == 0.0) {
    guard2 = true;
  } else {
    if (c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c11_r3), 1, 3, 1, 0) + 5] == 0.0) {
      guard1 = true;
    }
  }

  if (guard2 == true) {
    guard1 = true;
  }

  if (guard1 == true) {
    c11_eml_warning(chartInstance);
  }

  c11_Y[0] = c11_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r1), 1, 3, 1, 0) - 1];
  c11_Y[1] = c11_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r2), 1, 3, 1, 0) - 1] - c11_Y[0] *
    c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r2), 1, 3, 1, 0) - 1];
  c11_Y[2] = (c11_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r3), 1, 3, 1, 0) - 1] - c11_Y[0] *
              c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c11_r3), 1, 3, 1, 0) - 1]) - c11_Y[1] *
    c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
    (real_T)c11_r3), 1, 3, 1, 0) + 2];
  c11_ob_x = c11_Y[2];
  c11_t_y = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r3), 1, 3, 1, 0) + 5];
  c11_pb_x = c11_ob_x;
  c11_u_y = c11_t_y;
  c11_qb_x = c11_pb_x;
  c11_v_y = c11_u_y;
  c11_d_z = c11_qb_x / c11_v_y;
  c11_Y[2] = c11_d_z;
  c11_Y[0] -= c11_Y[2] * c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c11_r1), 1, 3, 1, 0) + 5];
  c11_Y[1] -= c11_Y[2] * c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c11_r2), 1, 3, 1, 0) + 5];
  c11_rb_x = c11_Y[1];
  c11_w_y = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
    "", (real_T)c11_r2), 1, 3, 1, 0) + 2];
  c11_sb_x = c11_rb_x;
  c11_x_y = c11_w_y;
  c11_tb_x = c11_sb_x;
  c11_y_y = c11_x_y;
  c11_e_z = c11_tb_x / c11_y_y;
  c11_Y[1] = c11_e_z;
  c11_Y[0] -= c11_Y[1] * c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
    _SFD_INTEGER_CHECK("", (real_T)c11_r1), 1, 3, 1, 0) + 2];
  c11_ub_x = c11_Y[0];
  c11_ab_y = c11_b_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
    ("", (real_T)c11_r1), 1, 3, 1, 0) - 1];
  c11_vb_x = c11_ub_x;
  c11_bb_y = c11_ab_y;
  c11_wb_x = c11_vb_x;
  c11_cb_y = c11_bb_y;
  c11_f_z = c11_wb_x / c11_cb_y;
  c11_Y[0] = c11_f_z;
}

static void c11_eml_warning(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  int32_T c11_i16;
  static char_T c11_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c11_u[27];
  const mxArray *c11_y = NULL;
  (void)chartInstance;
  for (c11_i16 = 0; c11_i16 < 27; c11_i16++) {
    c11_u[c11_i16] = c11_varargin_1[c11_i16];
  }

  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 10, 0U, 1U, 0U, 2, 1, 27),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c11_y));
}

static real_T c11_mpower(SFc11_CSE1_DPInstanceStruct *chartInstance, real_T
  c11_a)
{
  real_T c11_b_a;
  real_T c11_c_a;
  real_T c11_ak;
  real_T c11_d_a;
  c11_b_a = c11_a;
  c11_c_a = c11_b_a;
  c11_eml_scalar_eg(chartInstance);
  c11_ak = c11_c_a;
  c11_d_a = c11_ak;
  c11_eml_scalar_eg(chartInstance);
  return c11_d_a * c11_d_a;
}

static void c11_eml_scalar_eg(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c11_eml_error(SFc11_CSE1_DPInstanceStruct *chartInstance)
{
  int32_T c11_i17;
  static char_T c11_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c11_u[30];
  const mxArray *c11_y = NULL;
  int32_T c11_i18;
  static char_T c11_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c11_b_u[4];
  const mxArray *c11_b_y = NULL;
  (void)chartInstance;
  for (c11_i17 = 0; c11_i17 < 30; c11_i17++) {
    c11_u[c11_i17] = c11_cv0[c11_i17];
  }

  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 10, 0U, 1U, 0U, 2, 1, 30),
                false);
  for (c11_i18 = 0; c11_i18 < 4; c11_i18++) {
    c11_b_u[c11_i18] = c11_cv1[c11_i18];
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c11_y, 14, c11_b_y));
}

static const mxArray *c11_d_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc11_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(int32_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static int32_T c11_d_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  int32_T c11_y;
  int32_T c11_i19;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_i19, 1, 6, 0U, 0, 0U, 0);
  c11_y = c11_i19;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_b_sfEvent;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  int32_T c11_y;
  SFc11_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc11_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c11_b_sfEvent = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_sfEvent),
    &c11_thisId);
  sf_mex_destroy(&c11_b_sfEvent);
  *(int32_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

static uint8_T c11_e_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_b_is_active_c11_CSE1_DP, const char_T *c11_identifier)
{
  uint8_T c11_y;
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c11_b_is_active_c11_CSE1_DP), &c11_thisId);
  sf_mex_destroy(&c11_b_is_active_c11_CSE1_DP);
  return c11_y;
}

static uint8_T c11_f_emlrt_marshallIn(SFc11_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  uint8_T c11_y;
  uint8_T c11_u0;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_u0, 1, 3, 0U, 0, 0U, 0);
  c11_y = c11_u0;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void init_dsm_address_info(SFc11_CSE1_DPInstanceStruct *chartInstance)
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

void sf_c11_CSE1_DP_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3227770259U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3149228284U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1906233799U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2303917877U);
}

mxArray *sf_c11_CSE1_DP_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("2t7Wc0S7JKW5d7UKCRJoiD");
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

mxArray *sf_c11_CSE1_DP_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c11_CSE1_DP_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c11_CSE1_DP(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[9],T\"alpha_VSP\",},{M[1],M[11],T\"omega_VSP\",},{M[1],M[5],T\"u_BT\",},{M[1],M[8],T\"u_VSP\",},{M[8],M[0],T\"is_active_c11_CSE1_DP\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c11_CSE1_DP_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc11_CSE1_DPInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc11_CSE1_DPInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_DPMachineNumber_,
           11,
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
          (MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)c11_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)c11_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)c11_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)c11_sf_marshallIn);

        {
          real_T *c11_X;
          real_T *c11_Y;
          real_T *c11_u_BT;
          real_T *c11_N;
          real_T *c11_u_VSP;
          real_T *c11_alpha_VSP;
          real_T *c11_VSP_on;
          real_T *c11_omega_VSP;
          c11_omega_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c11_VSP_on = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c11_alpha_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c11_u_VSP = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c11_N = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c11_u_BT = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c11_Y = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c11_X = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c11_X);
          _SFD_SET_DATA_VALUE_PTR(1U, c11_Y);
          _SFD_SET_DATA_VALUE_PTR(2U, c11_u_BT);
          _SFD_SET_DATA_VALUE_PTR(3U, c11_N);
          _SFD_SET_DATA_VALUE_PTR(4U, c11_u_VSP);
          _SFD_SET_DATA_VALUE_PTR(5U, c11_alpha_VSP);
          _SFD_SET_DATA_VALUE_PTR(6U, c11_VSP_on);
          _SFD_SET_DATA_VALUE_PTR(7U, c11_omega_VSP);
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
  return "1ziAzsoSZ1VSNjS77W2i0F";
}

static void sf_opaque_initialize_c11_CSE1_DP(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar);
  initialize_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c11_CSE1_DP(void *chartInstanceVar)
{
  enable_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c11_CSE1_DP(void *chartInstanceVar)
{
  disable_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c11_CSE1_DP(void *chartInstanceVar)
{
  sf_gateway_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c11_CSE1_DP(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c11_CSE1_DP();/* state var info */
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

extern void sf_internal_set_sim_state_c11_CSE1_DP(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c11_CSE1_DP();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c11_CSE1_DP(SimStruct* S)
{
  return sf_internal_get_sim_state_c11_CSE1_DP(S);
}

static void sf_opaque_set_sim_state_c11_CSE1_DP(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c11_CSE1_DP(S, st);
}

static void sf_opaque_terminate_c11_CSE1_DP(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_DP_optimization_info();
    }

    finalize_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c11_CSE1_DP(SimStruct *S)
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
    initialize_params_c11_CSE1_DP((SFc11_CSE1_DPInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c11_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_DP_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      11);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,11,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,11,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,11);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,11,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,11,4);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,11);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(19971491U));
  ssSetChecksum1(S,(1704122644U));
  ssSetChecksum2(S,(1242413295U));
  ssSetChecksum3(S,(2137974769U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c11_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c11_CSE1_DP(SimStruct *S)
{
  SFc11_CSE1_DPInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc11_CSE1_DPInstanceStruct *)utMalloc(sizeof
    (SFc11_CSE1_DPInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc11_CSE1_DPInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c11_CSE1_DP;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c11_CSE1_DP;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c11_CSE1_DP;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c11_CSE1_DP;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c11_CSE1_DP;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c11_CSE1_DP;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c11_CSE1_DP;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c11_CSE1_DP;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c11_CSE1_DP;
  chartInstance->chartInfo.mdlStart = mdlStart_c11_CSE1_DP;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c11_CSE1_DP;
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

void c11_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c11_CSE1_DP(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c11_CSE1_DP(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c11_CSE1_DP(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c11_CSE1_DP_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
