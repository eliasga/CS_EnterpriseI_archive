/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_HIL_u_sfun.h"
#include "c5_CSE1_HIL_u.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "CSE1_HIL_u_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c5_debug_family_names[24] = { "a1", "b1", "c1", "a2", "b2",
  "c2", "a3", "b3", "c3", "a4", "b4", "c4", "a5", "b5", "c5", "a6", "b6", "c6",
  "nargin", "nargout", "alpha", "u_VST", "F_x", "F_y" };

/* Function Declarations */
static void initialize_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance);
static void initialize_params_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance);
static void enable_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct *chartInstance);
static void disable_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct *
  chartInstance);
static void set_sim_state_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance, const mxArray *c5_st);
static void finalize_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct *chartInstance);
static void sf_gateway_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance);
static void initSimStructsc5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static real_T c5_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct *chartInstance,
  const mxArray *c5_F_y, const char_T *c5_identifier);
static real_T c5_b_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_info_helper(const mxArray **c5_info);
static const mxArray *c5_emlrt_marshallOut(const char * c5_u);
static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_c_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_d_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_CSE1_HIL_u, const char_T
  *c5_identifier);
static uint8_T c5_e_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_CSE1_HIL_uInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance)
{
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_is_active_c5_CSE1_HIL_u = 0U;
}

static void initialize_params_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct *
  chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real_T c5_hoistedGlobal;
  real_T c5_u;
  const mxArray *c5_b_y = NULL;
  real_T c5_b_hoistedGlobal;
  real_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  uint8_T c5_c_hoistedGlobal;
  uint8_T c5_c_u;
  const mxArray *c5_d_y = NULL;
  real_T *c5_F_x;
  real_T *c5_F_y;
  c5_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_F_x = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(3, 1), false);
  c5_hoistedGlobal = *c5_F_x;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = *c5_F_y;
  c5_b_u = c5_b_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_c_hoistedGlobal = chartInstance->c5_is_active_c5_CSE1_HIL_u;
  c5_c_u = c5_c_hoistedGlobal;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 2, c5_d_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  real_T *c5_F_x;
  real_T *c5_F_y;
  c5_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_F_x = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  *c5_F_x = c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 0)),
    "F_x");
  *c5_F_y = c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 1)),
    "F_y");
  chartInstance->c5_is_active_c5_CSE1_HIL_u = c5_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 2)),
     "is_active_c5_CSE1_HIL_u");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_CSE1_HIL_u(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance)
{
  real_T c5_hoistedGlobal;
  real_T c5_b_hoistedGlobal;
  real_T c5_alpha;
  real_T c5_u_VST;
  uint32_T c5_debug_family_var_map[24];
  real_T c5_a1;
  real_T c5_b1;
  real_T c5_c1;
  real_T c5_a2;
  real_T c5_b2;
  real_T c5_c2;
  real_T c5_a3;
  real_T c5_b3;
  real_T c5_c3;
  real_T c5_a4;
  real_T c5_b4;
  real_T c5_c4;
  real_T c5_a5;
  real_T c5_b5;
  real_T c5_c5;
  real_T c5_a6;
  real_T c5_b6;
  real_T c5_c6;
  real_T c5_nargin = 2.0;
  real_T c5_nargout = 2.0;
  real_T c5_F_x;
  real_T c5_F_y;
  real_T c5_x;
  real_T c5_b_x;
  real_T c5_c_x;
  real_T c5_d_x;
  real_T c5_e_x;
  real_T c5_f_x;
  real_T c5_g_x;
  real_T c5_h_x;
  real_T c5_i_x;
  real_T c5_j_x;
  real_T c5_k_x;
  real_T c5_l_x;
  real_T c5_m_x;
  real_T c5_n_x;
  real_T c5_o_x;
  real_T c5_p_x;
  real_T c5_q_x;
  real_T c5_r_x;
  real_T c5_s_x;
  real_T c5_t_x;
  real_T c5_u_x;
  real_T c5_v_x;
  real_T c5_w_x;
  real_T c5_x_x;
  real_T *c5_b_alpha;
  real_T *c5_b_F_x;
  real_T *c5_b_u_VST;
  real_T *c5_b_F_y;
  c5_b_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_b_u_VST = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c5_b_F_x = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_b_alpha = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c5_b_alpha, 0U);
  chartInstance->c5_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  c5_hoistedGlobal = *c5_b_alpha;
  c5_b_hoistedGlobal = *c5_b_u_VST;
  c5_alpha = c5_hoistedGlobal;
  c5_u_VST = c5_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 24U, 24U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_a1, 0U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b1, 1U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c1, 2U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_a2, 3U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b2, 4U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c2, 5U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_a3, 6U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b3, 7U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c3, 8U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_a4, 9U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b4, 10U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c4, 11U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_a5, 12U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b5, 13U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c5, 14U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_a6, 15U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b6, 16U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c6, 17U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 18U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 19U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_alpha, 20U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_u_VST, 21U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_F_x, 22U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_F_y, 23U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 4);
  c5_a1 = 1.107;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 5);
  c5_b1 = 1.001;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 6);
  c5_c1 = 1.564;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 7);
  c5_a2 = 0.3471;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 8);
  c5_b2 = 0.1397;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 9);
  c5_c2 = -1.599;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 10);
  c5_a3 = 0.1558;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 11);
  c5_b3 = 1.993;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 12);
  c5_c3 = 1.886;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 13);
  c5_a4 = 0.1599;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 14);
  c5_b4 = 0.218;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 15);
  c5_c4 = 1.513;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 16);
  c5_a5 = 0.08237;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 17);
  c5_b5 = 2.986;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 18);
  c5_c5 = -1.601;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 19);
  c5_a6 = 0.04641;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 20);
  c5_b6 = 3.964;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 21);
  c5_c6 = 1.738;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 22);
  c5_x = 1.001 * c5_alpha + c5_c1;
  c5_b_x = c5_x;
  c5_b_x = muDoubleScalarSin(c5_b_x);
  c5_c_x = 0.1397 * c5_alpha + c5_c2;
  c5_d_x = c5_c_x;
  c5_d_x = muDoubleScalarSin(c5_d_x);
  c5_e_x = 1.993 * c5_alpha + c5_c3;
  c5_f_x = c5_e_x;
  c5_f_x = muDoubleScalarSin(c5_f_x);
  c5_g_x = 0.218 * c5_alpha + c5_c4;
  c5_h_x = c5_g_x;
  c5_h_x = muDoubleScalarSin(c5_h_x);
  c5_i_x = 2.986 * c5_alpha + c5_c5;
  c5_j_x = c5_i_x;
  c5_j_x = muDoubleScalarSin(c5_j_x);
  c5_k_x = 3.964 * c5_alpha + c5_c6;
  c5_l_x = c5_k_x;
  c5_l_x = muDoubleScalarSin(c5_l_x);
  c5_F_x = c5_u_VST * (((((1.107 * c5_b_x + 0.3471 * c5_d_x) + 0.1558 * c5_f_x)
    + 0.1599 * c5_h_x) + 0.08237 * c5_j_x) + 0.04641 * c5_l_x);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 29);
  c5_a1 = 0.7936;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 30);
  c5_b1 = 1.001;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 31);
  c5_c1 = 0.01605;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 32);
  c5_a2 = 0.2112;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 33);
  c5_b2 = 1.997;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 34);
  c5_c2 = 0.03229;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 35);
  c5_a3 = 0.07608;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 36);
  c5_b3 = 2.991;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 37);
  c5_c3 = 2.986;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 38);
  c5_a4 = 0.04817;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 39);
  c5_b4 = 3.999;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 40);
  c5_c4 = -0.8668;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 41);
  c5_a5 = 0.01757;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 42);
  c5_b5 = 4.904;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 43);
  c5_c5 = -2.622;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 44);
  c5_a6 = -0.02089;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 45);
  c5_b6 = 5.068;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 46);
  c5_c6 = 0.2548;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 47);
  c5_m_x = 1.001 * c5_alpha + c5_c1;
  c5_n_x = c5_m_x;
  c5_n_x = muDoubleScalarSin(c5_n_x);
  c5_o_x = 1.997 * c5_alpha + c5_c2;
  c5_p_x = c5_o_x;
  c5_p_x = muDoubleScalarSin(c5_p_x);
  c5_q_x = 2.991 * c5_alpha + c5_c3;
  c5_r_x = c5_q_x;
  c5_r_x = muDoubleScalarSin(c5_r_x);
  c5_s_x = 3.999 * c5_alpha + c5_c4;
  c5_t_x = c5_s_x;
  c5_t_x = muDoubleScalarSin(c5_t_x);
  c5_u_x = 4.904 * c5_alpha + c5_c5;
  c5_v_x = c5_u_x;
  c5_v_x = muDoubleScalarSin(c5_v_x);
  c5_w_x = 5.068 * c5_alpha + c5_c6;
  c5_x_x = c5_w_x;
  c5_x_x = muDoubleScalarSin(c5_x_x);
  c5_F_y = c5_u_VST * (((((0.7936 * c5_n_x + 0.2112 * c5_p_x) + 0.07608 * c5_r_x)
    + 0.04817 * c5_t_x) + 0.01757 * c5_v_x) + -0.02089 * c5_x_x);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -47);
  _SFD_SYMBOL_SCOPE_POP();
  *c5_b_F_x = c5_F_x;
  *c5_b_F_y = c5_F_y;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_HIL_uMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c5_b_F_x, 1U);
  _SFD_DATA_RANGE_CHECK(*c5_b_u_VST, 2U);
  _SFD_DATA_RANGE_CHECK(*c5_b_F_y, 3U);
}

static void initSimStructsc5_CSE1_HIL_u(SFc5_CSE1_HIL_uInstanceStruct
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
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_CSE1_HIL_uInstanceStruct *chartInstance;
  chartInstance = (SFc5_CSE1_HIL_uInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct *chartInstance,
  const mxArray *c5_F_y, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_F_y), &c5_thisId);
  sf_mex_destroy(&c5_F_y);
  return c5_y;
}

static real_T c5_b_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_F_y;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_CSE1_HIL_uInstanceStruct *chartInstance;
  chartInstance = (SFc5_CSE1_HIL_uInstanceStruct *)chartInstanceVoid;
  c5_F_y = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_F_y), &c5_thisId);
  sf_mex_destroy(&c5_F_y);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_CSE1_HIL_u_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_createstruct("structure", 2, 2, 1),
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
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("sin"), "name", "name", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
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
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
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
  sf_mex_destroy(&c5_rhs0);
  sf_mex_destroy(&c5_lhs0);
  sf_mex_destroy(&c5_rhs1);
  sf_mex_destroy(&c5_lhs1);
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

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_CSE1_HIL_uInstanceStruct *chartInstance;
  chartInstance = (SFc5_CSE1_HIL_uInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_c_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i0, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_CSE1_HIL_uInstanceStruct *chartInstance;
  chartInstance = (SFc5_CSE1_HIL_uInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static uint8_T c5_d_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_CSE1_HIL_u, const char_T
  *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_is_active_c5_CSE1_HIL_u), &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_CSE1_HIL_u);
  return c5_y;
}

static uint8_T c5_e_emlrt_marshallIn(SFc5_CSE1_HIL_uInstanceStruct
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

static void init_dsm_address_info(SFc5_CSE1_HIL_uInstanceStruct *chartInstance)
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

void sf_c5_CSE1_HIL_u_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3861847529U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4171984375U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3364069176U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1336699404U);
}

mxArray *sf_c5_CSE1_HIL_u_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ZxJonMXo0lEr8kq3DUBNmC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_CSE1_HIL_u_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_CSE1_HIL_u_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c5_CSE1_HIL_u(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"F_x\",},{M[1],M[7],T\"F_y\",},{M[8],M[0],T\"is_active_c5_CSE1_HIL_u\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_CSE1_HIL_u_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_CSE1_HIL_uInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_CSE1_HIL_uInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_HIL_uMachineNumber_,
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
        init_script_number_translation(_CSE1_HIL_uMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_CSE1_HIL_uMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _CSE1_HIL_uMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"alpha");
          _SFD_SET_DATA_PROPS(1,2,0,1,"F_x");
          _SFD_SET_DATA_PROPS(2,1,1,0,"u_VST");
          _SFD_SET_DATA_PROPS(3,2,0,1,"F_y");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1323);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);

        {
          real_T *c5_alpha;
          real_T *c5_F_x;
          real_T *c5_u_VST;
          real_T *c5_F_y;
          c5_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c5_u_VST = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c5_F_x = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c5_alpha = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c5_alpha);
          _SFD_SET_DATA_VALUE_PTR(1U, c5_F_x);
          _SFD_SET_DATA_VALUE_PTR(2U, c5_u_VST);
          _SFD_SET_DATA_VALUE_PTR(3U, c5_F_y);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _CSE1_HIL_uMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "NHJ7r9elp6jyZ6hMsRm63F";
}

static void sf_opaque_initialize_c5_CSE1_HIL_u(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_CSE1_HIL_uInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*)
    chartInstanceVar);
  initialize_c5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_CSE1_HIL_u(void *chartInstanceVar)
{
  enable_c5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_CSE1_HIL_u(void *chartInstanceVar)
{
  disable_c5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_CSE1_HIL_u(void *chartInstanceVar)
{
  sf_gateway_c5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_CSE1_HIL_u(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_CSE1_HIL_u
    ((SFc5_CSE1_HIL_uInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_CSE1_HIL_u();/* state var info */
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

extern void sf_internal_set_sim_state_c5_CSE1_HIL_u(SimStruct* S, const mxArray *
  st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c5_CSE1_HIL_u();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_CSE1_HIL_u(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_CSE1_HIL_u(S);
}

static void sf_opaque_set_sim_state_c5_CSE1_HIL_u(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c5_CSE1_HIL_u(S, st);
}

static void sf_opaque_terminate_c5_CSE1_HIL_u(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_CSE1_HIL_uInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_HIL_u_optimization_info();
    }

    finalize_c5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_CSE1_HIL_u(SimStruct *S)
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
    initialize_params_c5_CSE1_HIL_u((SFc5_CSE1_HIL_uInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_CSE1_HIL_u(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_HIL_u_optimization_info();
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2290629579U));
  ssSetChecksum1(S,(861332439U));
  ssSetChecksum2(S,(1207588318U));
  ssSetChecksum3(S,(4113372175U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_CSE1_HIL_u(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_CSE1_HIL_u(SimStruct *S)
{
  SFc5_CSE1_HIL_uInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc5_CSE1_HIL_uInstanceStruct *)utMalloc(sizeof
    (SFc5_CSE1_HIL_uInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_CSE1_HIL_uInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_CSE1_HIL_u;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_CSE1_HIL_u;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_CSE1_HIL_u;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_CSE1_HIL_u;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_CSE1_HIL_u;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_CSE1_HIL_u;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_CSE1_HIL_u;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_CSE1_HIL_u;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_CSE1_HIL_u;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_CSE1_HIL_u;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_CSE1_HIL_u;
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

void c5_CSE1_HIL_u_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_CSE1_HIL_u(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_CSE1_HIL_u(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_CSE1_HIL_u(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_CSE1_HIL_u_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
