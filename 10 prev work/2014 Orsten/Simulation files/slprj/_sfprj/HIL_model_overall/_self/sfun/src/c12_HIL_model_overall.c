/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_overall_sfun.h"
#include "c12_HIL_model_overall.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HIL_model_overall_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c12_debug_family_names[18] = { "theSize", "u", "psi", "uMax",
  "vMax", "psiMax", "xVel", "yVel", "r", "surge", "sway", "yaw", "nargin",
  "nargout", "in", "velMax", "eta_ship", "y" };

/* Function Declarations */
static void initialize_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance);
static void initialize_params_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance);
static void enable_c12_HIL_model_overall(SFc12_HIL_model_overallInstanceStruct
  *chartInstance);
static void disable_c12_HIL_model_overall(SFc12_HIL_model_overallInstanceStruct *
  chartInstance);
static void c12_update_debugger_state_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance);
static void set_sim_state_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance, const mxArray *c12_st);
static void finalize_c12_HIL_model_overall(SFc12_HIL_model_overallInstanceStruct
  *chartInstance);
static void sf_c12_HIL_model_overall(SFc12_HIL_model_overallInstanceStruct
  *chartInstance);
static void initSimStructsc12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance);
static void registerMessagesc12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber);
static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_y, const char_T *c12_identifier, real_T
  c12_b_y[3]);
static void c12_b_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[3]);
static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static real_T c12_c_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static int32_T c12_d_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static uint8_T c12_e_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_b_is_active_c12_HIL_model_overall, const
  char_T *c12_identifier);
static uint8_T c12_f_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void init_dsm_address_info(SFc12_HIL_model_overallInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance)
{
  chartInstance->c12_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c12_is_active_c12_HIL_model_overall = 0U;
}

static void initialize_params_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void enable_c12_HIL_model_overall(SFc12_HIL_model_overallInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c12_HIL_model_overall(SFc12_HIL_model_overallInstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c12_update_debugger_state_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance)
{
  const mxArray *c12_st;
  const mxArray *c12_y = NULL;
  int32_T c12_i0;
  real_T c12_u[3];
  const mxArray *c12_b_y = NULL;
  uint8_T c12_hoistedGlobal;
  uint8_T c12_b_u;
  const mxArray *c12_c_y = NULL;
  real_T (*c12_d_y)[3];
  c12_d_y = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_st = NULL;
  c12_st = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_createcellarray(2), FALSE);
  for (c12_i0 = 0; c12_i0 < 3; c12_i0++) {
    c12_u[c12_i0] = (*c12_d_y)[c12_i0];
  }

  c12_b_y = NULL;
  sf_mex_assign(&c12_b_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c12_y, 0, c12_b_y);
  c12_hoistedGlobal = chartInstance->c12_is_active_c12_HIL_model_overall;
  c12_b_u = c12_hoistedGlobal;
  c12_c_y = NULL;
  sf_mex_assign(&c12_c_y, sf_mex_create("y", &c12_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c12_y, 1, c12_c_y);
  sf_mex_assign(&c12_st, c12_y, FALSE);
  return c12_st;
}

static void set_sim_state_c12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance, const mxArray *c12_st)
{
  const mxArray *c12_u;
  real_T c12_dv0[3];
  int32_T c12_i1;
  real_T (*c12_y)[3];
  c12_y = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c12_doneDoubleBufferReInit = TRUE;
  c12_u = sf_mex_dup(c12_st);
  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 0)), "y",
                       c12_dv0);
  for (c12_i1 = 0; c12_i1 < 3; c12_i1++) {
    (*c12_y)[c12_i1] = c12_dv0[c12_i1];
  }

  chartInstance->c12_is_active_c12_HIL_model_overall = c12_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 1)),
     "is_active_c12_HIL_model_overall");
  sf_mex_destroy(&c12_u);
  c12_update_debugger_state_c12_HIL_model_overall(chartInstance);
  sf_mex_destroy(&c12_st);
}

static void finalize_c12_HIL_model_overall(SFc12_HIL_model_overallInstanceStruct
  *chartInstance)
{
}

static void sf_c12_HIL_model_overall(SFc12_HIL_model_overallInstanceStruct
  *chartInstance)
{
  int32_T c12_i2;
  int32_T c12_i3;
  int32_T c12_i4;
  int32_T c12_i5;
  int32_T c12_i6;
  real_T c12_in[3];
  int32_T c12_i7;
  real_T c12_velMax[3];
  int32_T c12_i8;
  real_T c12_eta_ship[3];
  uint32_T c12_debug_family_var_map[18];
  real_T c12_theSize;
  real_T c12_u[3];
  real_T c12_psi;
  real_T c12_uMax;
  real_T c12_vMax;
  real_T c12_psiMax;
  real_T c12_xVel;
  real_T c12_yVel;
  real_T c12_r;
  real_T c12_surge;
  real_T c12_sway;
  real_T c12_yaw;
  real_T c12_nargin = 3.0;
  real_T c12_nargout = 1.0;
  real_T c12_y[3];
  int32_T c12_i9;
  real_T c12_x;
  real_T c12_b_x;
  real_T c12_a;
  real_T c12_b;
  real_T c12_b_y;
  real_T c12_c_x;
  real_T c12_d_x;
  real_T c12_b_a;
  real_T c12_b_b;
  real_T c12_c_y;
  real_T c12_e_x;
  real_T c12_f_x;
  real_T c12_c_a;
  real_T c12_c_b;
  real_T c12_d_y;
  real_T c12_g_x;
  real_T c12_h_x;
  real_T c12_d_a;
  real_T c12_d_b;
  real_T c12_e_y;
  real_T c12_i_x;
  real_T c12_j_x;
  real_T c12_f_y;
  real_T c12_k_x;
  real_T c12_l_x;
  real_T c12_e_a;
  real_T c12_e_b;
  real_T c12_m_x;
  real_T c12_n_x;
  real_T c12_g_y;
  real_T c12_o_x;
  real_T c12_p_x;
  real_T c12_f_a;
  real_T c12_f_b;
  real_T c12_q_x;
  real_T c12_r_x;
  real_T c12_h_y;
  real_T c12_s_x;
  real_T c12_t_x;
  real_T c12_g_a;
  real_T c12_g_b;
  int32_T c12_i10;
  real_T c12_u_x;
  real_T c12_v_x;
  real_T c12_h_a;
  real_T c12_h_b;
  real_T c12_i_y;
  real_T c12_w_x;
  real_T c12_x_x;
  real_T c12_i_a;
  real_T c12_i_b;
  real_T c12_j_y;
  real_T c12_y_x;
  real_T c12_ab_x;
  real_T c12_j_a;
  real_T c12_j_b;
  real_T c12_k_y;
  real_T c12_bb_x;
  real_T c12_cb_x;
  real_T c12_k_a;
  real_T c12_k_b;
  real_T c12_l_y;
  int32_T c12_i11;
  real_T (*c12_m_y)[3];
  real_T (*c12_b_eta_ship)[3];
  real_T (*c12_b_velMax)[3];
  real_T (*c12_b_in)[3];
  c12_b_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c12_m_y = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_b_velMax = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c12_b_in = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  for (c12_i2 = 0; c12_i2 < 3; c12_i2++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_in)[c12_i2], 0U);
  }

  for (c12_i3 = 0; c12_i3 < 3; c12_i3++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_velMax)[c12_i3], 1U);
  }

  for (c12_i4 = 0; c12_i4 < 3; c12_i4++) {
    _SFD_DATA_RANGE_CHECK((*c12_m_y)[c12_i4], 2U);
  }

  for (c12_i5 = 0; c12_i5 < 3; c12_i5++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_eta_ship)[c12_i5], 3U);
  }

  chartInstance->c12_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  for (c12_i6 = 0; c12_i6 < 3; c12_i6++) {
    c12_in[c12_i6] = (*c12_b_in)[c12_i6];
  }

  for (c12_i7 = 0; c12_i7 < 3; c12_i7++) {
    c12_velMax[c12_i7] = (*c12_b_velMax)[c12_i7];
  }

  for (c12_i8 = 0; c12_i8 < 3; c12_i8++) {
    c12_eta_ship[c12_i8] = (*c12_b_eta_ship)[c12_i8];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 18U, 18U, c12_debug_family_names,
    c12_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_theSize, 0U, c12_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_u, 1U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_psi, 2U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_uMax, 3U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_vMax, 4U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_psiMax, 5U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_xVel, 6U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_yVel, 7U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_r, 8U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_surge, 9U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_sway, 10U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_yaw, 11U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargin, 12U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargout, 13U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_in, 14U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_velMax, 15U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_eta_ship, 16U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_y, 17U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 5);
  c12_theSize = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 6);
  CV_EML_IF(0, 1, 0, c12_theSize < 3.0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 9);
  for (c12_i9 = 0; c12_i9 < 3; c12_i9++) {
    c12_u[c12_i9] = c12_in[c12_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 12);
  c12_psi = c12_eta_ship[2];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 13);
  c12_uMax = c12_velMax[0];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 14);
  c12_vMax = c12_velMax[1];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 15);
  c12_psiMax = c12_velMax[2];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 17);
  c12_xVel = c12_u[0];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 18);
  c12_yVel = c12_u[1];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 19);
  c12_r = c12_u[2];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 21);
  c12_x = c12_psi;
  c12_b_x = c12_x;
  c12_b_x = muDoubleScalarCos(c12_b_x);
  c12_a = c12_xVel;
  c12_b = c12_b_x;
  c12_b_y = c12_a * c12_b;
  c12_c_x = c12_psi;
  c12_d_x = c12_c_x;
  c12_d_x = muDoubleScalarSin(c12_d_x);
  c12_b_a = c12_yVel;
  c12_b_b = c12_d_x;
  c12_c_y = c12_b_a * c12_b_b;
  c12_surge = c12_b_y + c12_c_y;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 22);
  c12_e_x = c12_psi;
  c12_f_x = c12_e_x;
  c12_f_x = muDoubleScalarSin(c12_f_x);
  c12_c_a = -c12_xVel;
  c12_c_b = c12_f_x;
  c12_d_y = c12_c_a * c12_c_b;
  c12_g_x = c12_psi;
  c12_h_x = c12_g_x;
  c12_h_x = muDoubleScalarCos(c12_h_x);
  c12_d_a = c12_yVel;
  c12_d_b = c12_h_x;
  c12_e_y = c12_d_a * c12_d_b;
  c12_sway = c12_d_y + c12_e_y;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 23);
  c12_yaw = c12_r;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 25);
  c12_i_x = c12_surge;
  c12_j_x = c12_i_x;
  c12_f_y = muDoubleScalarAbs(c12_j_x);
  if (CV_EML_IF(0, 1, 1, c12_f_y > c12_uMax)) {
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 26);
    c12_k_x = c12_surge;
    c12_l_x = c12_k_x;
    c12_l_x = muDoubleScalarSign(c12_l_x);
    c12_e_a = c12_l_x;
    c12_e_b = c12_uMax;
    c12_surge = c12_e_a * c12_e_b;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 28);
  c12_m_x = c12_sway;
  c12_n_x = c12_m_x;
  c12_g_y = muDoubleScalarAbs(c12_n_x);
  if (CV_EML_IF(0, 1, 2, c12_g_y > c12_vMax)) {
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 29);
    c12_o_x = c12_sway;
    c12_p_x = c12_o_x;
    c12_p_x = muDoubleScalarSign(c12_p_x);
    c12_f_a = c12_p_x;
    c12_f_b = c12_vMax;
    c12_sway = c12_f_a * c12_f_b;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 31);
  c12_q_x = c12_yaw;
  c12_r_x = c12_q_x;
  c12_h_y = muDoubleScalarAbs(c12_r_x);
  if (CV_EML_IF(0, 1, 3, c12_h_y > c12_psiMax)) {
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 32);
    c12_s_x = c12_yaw;
    c12_t_x = c12_s_x;
    c12_t_x = muDoubleScalarSign(c12_t_x);
    c12_g_a = c12_t_x;
    c12_g_b = c12_psiMax;
    c12_yaw = c12_g_a * c12_g_b;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 35);
  for (c12_i10 = 0; c12_i10 < 3; c12_i10++) {
    c12_y[c12_i10] = c12_u[c12_i10];
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 36);
  c12_u_x = c12_psi;
  c12_v_x = c12_u_x;
  c12_v_x = muDoubleScalarCos(c12_v_x);
  c12_h_a = c12_v_x;
  c12_h_b = c12_surge;
  c12_i_y = c12_h_a * c12_h_b;
  c12_w_x = c12_psi;
  c12_x_x = c12_w_x;
  c12_x_x = muDoubleScalarSin(c12_x_x);
  c12_i_a = c12_x_x;
  c12_i_b = c12_sway;
  c12_j_y = c12_i_a * c12_i_b;
  c12_y[0] = c12_i_y - c12_j_y;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 37);
  c12_y_x = c12_psi;
  c12_ab_x = c12_y_x;
  c12_ab_x = muDoubleScalarSin(c12_ab_x);
  c12_j_a = c12_ab_x;
  c12_j_b = c12_surge;
  c12_k_y = c12_j_a * c12_j_b;
  c12_bb_x = c12_psi;
  c12_cb_x = c12_bb_x;
  c12_cb_x = muDoubleScalarCos(c12_cb_x);
  c12_k_a = c12_cb_x;
  c12_k_b = c12_sway;
  c12_l_y = c12_k_a * c12_k_b;
  c12_y[1] = c12_k_y + c12_l_y;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 38);
  c12_y[2] = c12_yaw;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, -38);
  _SFD_SYMBOL_SCOPE_POP();
  for (c12_i11 = 0; c12_i11 < 3; c12_i11++) {
    (*c12_m_y)[c12_i11] = c12_y[c12_i11];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_overallMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void registerMessagesc12_HIL_model_overall
  (SFc12_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber)
{
}

static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i12;
  real_T c12_b_inData[3];
  int32_T c12_i13;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc12_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i12 = 0; c12_i12 < 3; c12_i12++) {
    c12_b_inData[c12_i12] = (*(real_T (*)[3])c12_inData)[c12_i12];
  }

  for (c12_i13 = 0; c12_i13 < 3; c12_i13++) {
    c12_u[c12_i13] = c12_b_inData[c12_i13];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_y, const char_T *c12_identifier, real_T
  c12_b_y[3])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_y), &c12_thisId, c12_b_y);
  sf_mex_destroy(&c12_y);
}

static void c12_b_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[3])
{
  real_T c12_dv1[3];
  int32_T c12_i14;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c12_i14 = 0; c12_i14 < 3; c12_i14++) {
    c12_y[c12_i14] = c12_dv1[c12_i14];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_y;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_b_y[3];
  int32_T c12_i15;
  SFc12_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc12_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c12_y = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_y), &c12_thisId, c12_b_y);
  sf_mex_destroy(&c12_y);
  for (c12_i15 = 0; c12_i15 < 3; c12_i15++) {
    (*(real_T (*)[3])c12_outData)[c12_i15] = c12_b_y[c12_i15];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i16;
  real_T c12_b_inData[3];
  int32_T c12_i17;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc12_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i16 = 0; c12_i16 < 3; c12_i16++) {
    c12_b_inData[c12_i16] = (*(real_T (*)[3])c12_inData)[c12_i16];
  }

  for (c12_i17 = 0; c12_i17 < 3; c12_i17++) {
    c12_u[c12_i17] = c12_b_inData[c12_i17];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  real_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc12_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(real_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static real_T c12_c_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  real_T c12_y;
  real_T c12_d0;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_d0, 1, 0, 0U, 0, 0U, 0);
  c12_y = c12_d0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_nargout;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y;
  SFc12_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc12_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c12_nargout = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_nargout),
    &c12_thisId);
  sf_mex_destroy(&c12_nargout);
  *(real_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

const mxArray *sf_c12_HIL_model_overall_get_eml_resolved_functions_info(void)
{
  const mxArray *c12_nameCaptureInfo;
  c12_ResolvedFunctionInfo c12_info[10];
  c12_ResolvedFunctionInfo (*c12_b_info)[10];
  const mxArray *c12_m0 = NULL;
  int32_T c12_i18;
  c12_ResolvedFunctionInfo *c12_r0;
  c12_nameCaptureInfo = NULL;
  c12_nameCaptureInfo = NULL;
  c12_b_info = (c12_ResolvedFunctionInfo (*)[10])c12_info;
  (*c12_b_info)[0].context = "";
  (*c12_b_info)[0].name = "length";
  (*c12_b_info)[0].dominantType = "double";
  (*c12_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  (*c12_b_info)[0].fileTimeLo = 1303146206U;
  (*c12_b_info)[0].fileTimeHi = 0U;
  (*c12_b_info)[0].mFileTimeLo = 0U;
  (*c12_b_info)[0].mFileTimeHi = 0U;
  (*c12_b_info)[1].context = "";
  (*c12_b_info)[1].name = "cos";
  (*c12_b_info)[1].dominantType = "double";
  (*c12_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c12_b_info)[1].fileTimeLo = 1343830372U;
  (*c12_b_info)[1].fileTimeHi = 0U;
  (*c12_b_info)[1].mFileTimeLo = 0U;
  (*c12_b_info)[1].mFileTimeHi = 0U;
  (*c12_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c12_b_info)[2].name = "eml_scalar_cos";
  (*c12_b_info)[2].dominantType = "double";
  (*c12_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  (*c12_b_info)[2].fileTimeLo = 1286818722U;
  (*c12_b_info)[2].fileTimeHi = 0U;
  (*c12_b_info)[2].mFileTimeLo = 0U;
  (*c12_b_info)[2].mFileTimeHi = 0U;
  (*c12_b_info)[3].context = "";
  (*c12_b_info)[3].name = "mtimes";
  (*c12_b_info)[3].dominantType = "double";
  (*c12_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c12_b_info)[3].fileTimeLo = 1289519692U;
  (*c12_b_info)[3].fileTimeHi = 0U;
  (*c12_b_info)[3].mFileTimeLo = 0U;
  (*c12_b_info)[3].mFileTimeHi = 0U;
  (*c12_b_info)[4].context = "";
  (*c12_b_info)[4].name = "sin";
  (*c12_b_info)[4].dominantType = "double";
  (*c12_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c12_b_info)[4].fileTimeLo = 1343830386U;
  (*c12_b_info)[4].fileTimeHi = 0U;
  (*c12_b_info)[4].mFileTimeLo = 0U;
  (*c12_b_info)[4].mFileTimeHi = 0U;
  (*c12_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c12_b_info)[5].name = "eml_scalar_sin";
  (*c12_b_info)[5].dominantType = "double";
  (*c12_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  (*c12_b_info)[5].fileTimeLo = 1286818736U;
  (*c12_b_info)[5].fileTimeHi = 0U;
  (*c12_b_info)[5].mFileTimeLo = 0U;
  (*c12_b_info)[5].mFileTimeHi = 0U;
  (*c12_b_info)[6].context = "";
  (*c12_b_info)[6].name = "abs";
  (*c12_b_info)[6].dominantType = "double";
  (*c12_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  (*c12_b_info)[6].fileTimeLo = 1343830366U;
  (*c12_b_info)[6].fileTimeHi = 0U;
  (*c12_b_info)[6].mFileTimeLo = 0U;
  (*c12_b_info)[6].mFileTimeHi = 0U;
  (*c12_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  (*c12_b_info)[7].name = "eml_scalar_abs";
  (*c12_b_info)[7].dominantType = "double";
  (*c12_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  (*c12_b_info)[7].fileTimeLo = 1286818712U;
  (*c12_b_info)[7].fileTimeHi = 0U;
  (*c12_b_info)[7].mFileTimeLo = 0U;
  (*c12_b_info)[7].mFileTimeHi = 0U;
  (*c12_b_info)[8].context = "";
  (*c12_b_info)[8].name = "sign";
  (*c12_b_info)[8].dominantType = "double";
  (*c12_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  (*c12_b_info)[8].fileTimeLo = 1354368064U;
  (*c12_b_info)[8].fileTimeHi = 0U;
  (*c12_b_info)[8].mFileTimeLo = 0U;
  (*c12_b_info)[8].mFileTimeHi = 0U;
  (*c12_b_info)[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  (*c12_b_info)[9].name = "eml_scalar_sign";
  (*c12_b_info)[9].dominantType = "double";
  (*c12_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sign.m";
  (*c12_b_info)[9].fileTimeLo = 1354368064U;
  (*c12_b_info)[9].fileTimeHi = 0U;
  (*c12_b_info)[9].mFileTimeLo = 0U;
  (*c12_b_info)[9].mFileTimeHi = 0U;
  sf_mex_assign(&c12_m0, sf_mex_createstruct("nameCaptureInfo", 1, 10), FALSE);
  for (c12_i18 = 0; c12_i18 < 10; c12_i18++) {
    c12_r0 = &c12_info[c12_i18];
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->context)), "context", "nameCaptureInfo",
                    c12_i18);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->name)), "name", "nameCaptureInfo",
                    c12_i18);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      c12_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c12_i18);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->resolved)), "resolved",
                    "nameCaptureInfo", c12_i18);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c12_i18);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c12_i18);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c12_i18);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c12_i18);
  }

  sf_mex_assign(&c12_nameCaptureInfo, c12_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c12_nameCaptureInfo);
  return c12_nameCaptureInfo;
}

static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc12_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(int32_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static int32_T c12_d_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  int32_T c12_y;
  int32_T c12_i19;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_i19, 1, 6, 0U, 0, 0U, 0);
  c12_y = c12_i19;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_b_sfEvent;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  int32_T c12_y;
  SFc12_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc12_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c12_b_sfEvent = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_b_sfEvent),
    &c12_thisId);
  sf_mex_destroy(&c12_b_sfEvent);
  *(int32_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static uint8_T c12_e_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_b_is_active_c12_HIL_model_overall, const
  char_T *c12_identifier)
{
  uint8_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c12_b_is_active_c12_HIL_model_overall), &c12_thisId);
  sf_mex_destroy(&c12_b_is_active_c12_HIL_model_overall);
  return c12_y;
}

static uint8_T c12_f_emlrt_marshallIn(SFc12_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint8_T c12_y;
  uint8_T c12_u0;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u0, 1, 3, 0U, 0, 0U, 0);
  c12_y = c12_u0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void init_dsm_address_info(SFc12_HIL_model_overallInstanceStruct
  *chartInstance)
{
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

void sf_c12_HIL_model_overall_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(595520732U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1332140903U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(143591051U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2174478615U);
}

mxArray *sf_c12_HIL_model_overall_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ASu1O1s8cmc6pjtKKrL18F");
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

mxArray *sf_c12_HIL_model_overall_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c12_HIL_model_overall(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c12_HIL_model_overall\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c12_HIL_model_overall_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc12_HIL_model_overallInstanceStruct *chartInstance;
    chartInstance = (SFc12_HIL_model_overallInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_overallMachineNumber_,
           12,
           1,
           1,
           4,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_HIL_model_overallMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HIL_model_overallMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HIL_model_overallMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"in");
          _SFD_SET_DATA_PROPS(1,1,1,0,"velMax");
          _SFD_SET_DATA_PROPS(2,2,0,1,"y");
          _SFD_SET_DATA_PROPS(3,1,1,0,"eta_ship");
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
        _SFD_CV_INIT_EML(0,1,1,4,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,614);
        _SFD_CV_INIT_EML_IF(0,1,0,90,104,125,145);
        _SFD_CV_INIT_EML_IF(0,1,1,357,377,-1,411);
        _SFD_CV_INIT_EML_IF(0,1,2,412,431,-1,463);
        _SFD_CV_INIT_EML_IF(0,1,3,464,484,-1,516);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c12_in)[3];
          real_T (*c12_velMax)[3];
          real_T (*c12_y)[3];
          real_T (*c12_eta_ship)[3];
          c12_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c12_y = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c12_velMax = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c12_in = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c12_in);
          _SFD_SET_DATA_VALUE_PTR(1U, *c12_velMax);
          _SFD_SET_DATA_VALUE_PTR(2U, *c12_y);
          _SFD_SET_DATA_VALUE_PTR(3U, *c12_eta_ship);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HIL_model_overallMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "8FMnQhU6Uzl3cGuIyQtDkH";
}

static void sf_opaque_initialize_c12_HIL_model_overall(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc12_HIL_model_overallInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c12_HIL_model_overall((SFc12_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
  initialize_c12_HIL_model_overall((SFc12_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c12_HIL_model_overall(void *chartInstanceVar)
{
  enable_c12_HIL_model_overall((SFc12_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c12_HIL_model_overall(void *chartInstanceVar)
{
  disable_c12_HIL_model_overall((SFc12_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c12_HIL_model_overall(void *chartInstanceVar)
{
  sf_c12_HIL_model_overall((SFc12_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c12_HIL_model_overall(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c12_HIL_model_overall
    ((SFc12_HIL_model_overallInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_HIL_model_overall();/* state var info */
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

extern void sf_internal_set_sim_state_c12_HIL_model_overall(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_HIL_model_overall();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c12_HIL_model_overall((SFc12_HIL_model_overallInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c12_HIL_model_overall(SimStruct* S)
{
  return sf_internal_get_sim_state_c12_HIL_model_overall(S);
}

static void sf_opaque_set_sim_state_c12_HIL_model_overall(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c12_HIL_model_overall(S, st);
}

static void sf_opaque_terminate_c12_HIL_model_overall(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc12_HIL_model_overallInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_overall_optimization_info();
    }

    finalize_c12_HIL_model_overall((SFc12_HIL_model_overallInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc12_HIL_model_overall((SFc12_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c12_HIL_model_overall(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c12_HIL_model_overall
      ((SFc12_HIL_model_overallInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c12_HIL_model_overall(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_overall_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      12);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,12,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,12,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,12);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,12,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,12,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,12);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3317654908U));
  ssSetChecksum1(S,(1802814276U));
  ssSetChecksum2(S,(3371498805U));
  ssSetChecksum3(S,(1726282385U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c12_HIL_model_overall(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c12_HIL_model_overall(SimStruct *S)
{
  SFc12_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc12_HIL_model_overallInstanceStruct *)utMalloc(sizeof
    (SFc12_HIL_model_overallInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc12_HIL_model_overallInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c12_HIL_model_overall;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c12_HIL_model_overall;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c12_HIL_model_overall;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c12_HIL_model_overall;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c12_HIL_model_overall;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c12_HIL_model_overall;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c12_HIL_model_overall;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c12_HIL_model_overall;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c12_HIL_model_overall;
  chartInstance->chartInfo.mdlStart = mdlStart_c12_HIL_model_overall;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c12_HIL_model_overall;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c12_HIL_model_overall_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c12_HIL_model_overall(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c12_HIL_model_overall(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c12_HIL_model_overall(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c12_HIL_model_overall_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
