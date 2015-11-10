/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_DP_sfun.h"
#include "c19_CSE1_DP.h"
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
static const char * c19_debug_family_names[24] = { "a1", "b1", "c1", "a2", "b2",
  "c2", "a3", "b3", "c3", "a4", "b4", "c4", "a5", "b5", "c5", "a6", "b6", "c6",
  "nargin", "nargout", "alpha", "u_VST", "F_x", "F_y" };

/* Function Declarations */
static void initialize_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance);
static void initialize_params_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct
  *chartInstance);
static void enable_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance);
static void disable_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance);
static void c19_update_debugger_state_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct
  *chartInstance);
static void set_sim_state_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_st);
static void finalize_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance);
static void sf_gateway_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance);
static void initSimStructsc19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c19_machineNumber, uint32_T
  c19_chartNumber, uint32_T c19_instanceNumber);
static const mxArray *c19_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static real_T c19_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_F_y, const char_T *c19_identifier);
static real_T c19_b_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId);
static void c19_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static void c19_info_helper(const mxArray **c19_info);
static const mxArray *c19_emlrt_marshallOut(const char * c19_u);
static const mxArray *c19_b_emlrt_marshallOut(const uint32_T c19_u);
static const mxArray *c19_b_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData);
static int32_T c19_c_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId);
static void c19_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData);
static uint8_T c19_d_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_b_is_active_c19_CSE1_DP, const char_T *c19_identifier);
static uint8_T c19_e_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId);
static void init_dsm_address_info(SFc19_CSE1_DPInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance)
{
  chartInstance->c19_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c19_is_active_c19_CSE1_DP = 0U;
}

static void initialize_params_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c19_update_debugger_state_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct
  *chartInstance)
{
  const mxArray *c19_st;
  const mxArray *c19_y = NULL;
  real_T c19_hoistedGlobal;
  real_T c19_u;
  const mxArray *c19_b_y = NULL;
  real_T c19_b_hoistedGlobal;
  real_T c19_b_u;
  const mxArray *c19_c_y = NULL;
  uint8_T c19_c_hoistedGlobal;
  uint8_T c19_c_u;
  const mxArray *c19_d_y = NULL;
  real_T *c19_F_x;
  real_T *c19_F_y;
  c19_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c19_F_x = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c19_st = NULL;
  c19_st = NULL;
  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_createcellmatrix(3, 1), false);
  c19_hoistedGlobal = *c19_F_x;
  c19_u = c19_hoistedGlobal;
  c19_b_y = NULL;
  sf_mex_assign(&c19_b_y, sf_mex_create("y", &c19_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c19_y, 0, c19_b_y);
  c19_b_hoistedGlobal = *c19_F_y;
  c19_b_u = c19_b_hoistedGlobal;
  c19_c_y = NULL;
  sf_mex_assign(&c19_c_y, sf_mex_create("y", &c19_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c19_y, 1, c19_c_y);
  c19_c_hoistedGlobal = chartInstance->c19_is_active_c19_CSE1_DP;
  c19_c_u = c19_c_hoistedGlobal;
  c19_d_y = NULL;
  sf_mex_assign(&c19_d_y, sf_mex_create("y", &c19_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c19_y, 2, c19_d_y);
  sf_mex_assign(&c19_st, c19_y, false);
  return c19_st;
}

static void set_sim_state_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_st)
{
  const mxArray *c19_u;
  real_T *c19_F_x;
  real_T *c19_F_y;
  c19_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c19_F_x = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c19_doneDoubleBufferReInit = true;
  c19_u = sf_mex_dup(c19_st);
  *c19_F_x = c19_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c19_u,
    0)), "F_x");
  *c19_F_y = c19_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c19_u,
    1)), "F_y");
  chartInstance->c19_is_active_c19_CSE1_DP = c19_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c19_u, 2)),
     "is_active_c19_CSE1_DP");
  sf_mex_destroy(&c19_u);
  c19_update_debugger_state_c19_CSE1_DP(chartInstance);
  sf_mex_destroy(&c19_st);
}

static void finalize_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance)
{
  real_T c19_hoistedGlobal;
  real_T c19_b_hoistedGlobal;
  real_T c19_alpha;
  real_T c19_u_VST;
  uint32_T c19_debug_family_var_map[24];
  real_T c19_a1;
  real_T c19_b1;
  real_T c19_c1;
  real_T c19_a2;
  real_T c19_b2;
  real_T c19_c2;
  real_T c19_a3;
  real_T c19_b3;
  real_T c19_c3;
  real_T c19_a4;
  real_T c19_b4;
  real_T c19_c4;
  real_T c19_a5;
  real_T c19_b5;
  real_T c19_c5;
  real_T c19_a6;
  real_T c19_b6;
  real_T c19_c6;
  real_T c19_nargin = 2.0;
  real_T c19_nargout = 2.0;
  real_T c19_F_x;
  real_T c19_F_y;
  real_T c19_x;
  real_T c19_b_x;
  real_T c19_c_x;
  real_T c19_d_x;
  real_T c19_e_x;
  real_T c19_f_x;
  real_T c19_g_x;
  real_T c19_h_x;
  real_T c19_i_x;
  real_T c19_j_x;
  real_T c19_k_x;
  real_T c19_l_x;
  real_T c19_m_x;
  real_T c19_n_x;
  real_T c19_o_x;
  real_T c19_p_x;
  real_T c19_q_x;
  real_T c19_r_x;
  real_T c19_s_x;
  real_T c19_t_x;
  real_T c19_u_x;
  real_T c19_v_x;
  real_T c19_w_x;
  real_T c19_x_x;
  real_T *c19_b_alpha;
  real_T *c19_b_F_x;
  real_T *c19_b_u_VST;
  real_T *c19_b_F_y;
  c19_b_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c19_b_u_VST = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c19_b_F_x = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c19_b_alpha = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 17U, chartInstance->c19_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c19_b_alpha, 0U);
  chartInstance->c19_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 17U, chartInstance->c19_sfEvent);
  c19_hoistedGlobal = *c19_b_alpha;
  c19_b_hoistedGlobal = *c19_b_u_VST;
  c19_alpha = c19_hoistedGlobal;
  c19_u_VST = c19_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 24U, 24U, c19_debug_family_names,
    c19_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_a1, 0U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_b1, 1U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_c1, 2U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_a2, 3U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_b2, 4U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_c2, 5U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_a3, 6U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_b3, 7U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_c3, 8U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_a4, 9U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_b4, 10U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_c4, 11U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_a5, 12U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_b5, 13U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_c5, 14U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_a6, 15U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_b6, 16U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_c6, 17U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_nargin, 18U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_nargout, 19U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_alpha, 20U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c19_u_VST, 21U, c19_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_F_x, 22U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c19_F_y, 23U, c19_sf_marshallOut,
    c19_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 4);
  c19_a1 = 1.107;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 5);
  c19_b1 = 1.001;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 6);
  c19_c1 = 1.564;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 7);
  c19_a2 = 0.3471;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 8);
  c19_b2 = 0.1397;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 9);
  c19_c2 = -1.599;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 10);
  c19_a3 = 0.1558;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 11);
  c19_b3 = 1.993;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 12);
  c19_c3 = 1.886;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 13);
  c19_a4 = 0.1599;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 14);
  c19_b4 = 0.218;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 15);
  c19_c4 = 1.513;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 16);
  c19_a5 = 0.08237;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 17);
  c19_b5 = 2.986;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 18);
  c19_c5 = -1.601;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 19);
  c19_a6 = 0.04641;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 20);
  c19_b6 = 3.964;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 21);
  c19_c6 = 1.738;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 22);
  c19_x = 1.001 * c19_alpha + c19_c1;
  c19_b_x = c19_x;
  c19_b_x = muDoubleScalarSin(c19_b_x);
  c19_c_x = 0.1397 * c19_alpha + c19_c2;
  c19_d_x = c19_c_x;
  c19_d_x = muDoubleScalarSin(c19_d_x);
  c19_e_x = 1.993 * c19_alpha + c19_c3;
  c19_f_x = c19_e_x;
  c19_f_x = muDoubleScalarSin(c19_f_x);
  c19_g_x = 0.218 * c19_alpha + c19_c4;
  c19_h_x = c19_g_x;
  c19_h_x = muDoubleScalarSin(c19_h_x);
  c19_i_x = 2.986 * c19_alpha + c19_c5;
  c19_j_x = c19_i_x;
  c19_j_x = muDoubleScalarSin(c19_j_x);
  c19_k_x = 3.964 * c19_alpha + c19_c6;
  c19_l_x = c19_k_x;
  c19_l_x = muDoubleScalarSin(c19_l_x);
  c19_F_x = c19_u_VST * (((((1.107 * c19_b_x + 0.3471 * c19_d_x) + 0.1558 *
    c19_f_x) + 0.1599 * c19_h_x) + 0.08237 * c19_j_x) + 0.04641 * c19_l_x);
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 29);
  c19_a1 = 0.7936;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 30);
  c19_b1 = 1.001;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 31);
  c19_c1 = 0.01605;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 32);
  c19_a2 = 0.2112;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 33);
  c19_b2 = 1.997;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 34);
  c19_c2 = 0.03229;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 35);
  c19_a3 = 0.07608;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 36);
  c19_b3 = 2.991;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 37);
  c19_c3 = 2.986;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 38);
  c19_a4 = 0.04817;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 39);
  c19_b4 = 3.999;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 40);
  c19_c4 = -0.8668;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 41);
  c19_a5 = 0.01757;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 42);
  c19_b5 = 4.904;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 43);
  c19_c5 = -2.622;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 44);
  c19_a6 = -0.02089;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 45);
  c19_b6 = 5.068;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 46);
  c19_c6 = 0.2548;
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, 47);
  c19_m_x = 1.001 * c19_alpha + c19_c1;
  c19_n_x = c19_m_x;
  c19_n_x = muDoubleScalarSin(c19_n_x);
  c19_o_x = 1.997 * c19_alpha + c19_c2;
  c19_p_x = c19_o_x;
  c19_p_x = muDoubleScalarSin(c19_p_x);
  c19_q_x = 2.991 * c19_alpha + c19_c3;
  c19_r_x = c19_q_x;
  c19_r_x = muDoubleScalarSin(c19_r_x);
  c19_s_x = 3.999 * c19_alpha + c19_c4;
  c19_t_x = c19_s_x;
  c19_t_x = muDoubleScalarSin(c19_t_x);
  c19_u_x = 4.904 * c19_alpha + c19_c5;
  c19_v_x = c19_u_x;
  c19_v_x = muDoubleScalarSin(c19_v_x);
  c19_w_x = 5.068 * c19_alpha + c19_c6;
  c19_x_x = c19_w_x;
  c19_x_x = muDoubleScalarSin(c19_x_x);
  c19_F_y = c19_u_VST * (((((0.7936 * c19_n_x + 0.2112 * c19_p_x) + 0.07608 *
    c19_r_x) + 0.04817 * c19_t_x) + 0.01757 * c19_v_x) + -0.02089 * c19_x_x);
  _SFD_EML_CALL(0U, chartInstance->c19_sfEvent, -47);
  _SFD_SYMBOL_SCOPE_POP();
  *c19_b_F_x = c19_F_x;
  *c19_b_F_y = c19_F_y;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c19_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_DPMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c19_b_F_x, 1U);
  _SFD_DATA_RANGE_CHECK(*c19_b_u_VST, 2U);
  _SFD_DATA_RANGE_CHECK(*c19_b_F_y, 3U);
}

static void initSimStructsc19_CSE1_DP(SFc19_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c19_machineNumber, uint32_T
  c19_chartNumber, uint32_T c19_instanceNumber)
{
  (void)c19_machineNumber;
  (void)c19_chartNumber;
  (void)c19_instanceNumber;
}

static const mxArray *c19_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  real_T c19_u;
  const mxArray *c19_y = NULL;
  SFc19_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc19_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  c19_u = *(real_T *)c19_inData;
  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", &c19_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, false);
  return c19_mxArrayOutData;
}

static real_T c19_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_F_y, const char_T *c19_identifier)
{
  real_T c19_y;
  emlrtMsgIdentifier c19_thisId;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_y = c19_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_F_y), &c19_thisId);
  sf_mex_destroy(&c19_F_y);
  return c19_y;
}

static real_T c19_b_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId)
{
  real_T c19_y;
  real_T c19_d0;
  (void)chartInstance;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), &c19_d0, 1, 0, 0U, 0, 0U, 0);
  c19_y = c19_d0;
  sf_mex_destroy(&c19_u);
  return c19_y;
}

static void c19_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_F_y;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  real_T c19_y;
  SFc19_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc19_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c19_F_y = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_y = c19_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_F_y), &c19_thisId);
  sf_mex_destroy(&c19_F_y);
  *(real_T *)c19_outData = c19_y;
  sf_mex_destroy(&c19_mxArrayInData);
}

const mxArray *sf_c19_CSE1_DP_get_eml_resolved_functions_info(void)
{
  const mxArray *c19_nameCaptureInfo = NULL;
  c19_nameCaptureInfo = NULL;
  sf_mex_assign(&c19_nameCaptureInfo, sf_mex_createstruct("structure", 2, 2, 1),
                false);
  c19_info_helper(&c19_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c19_nameCaptureInfo);
  return c19_nameCaptureInfo;
}

static void c19_info_helper(const mxArray **c19_info)
{
  const mxArray *c19_rhs0 = NULL;
  const mxArray *c19_lhs0 = NULL;
  const mxArray *c19_rhs1 = NULL;
  const mxArray *c19_lhs1 = NULL;
  sf_mex_addfield(*c19_info, c19_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c19_info, c19_emlrt_marshallOut("sin"), "name", "name", 0);
  sf_mex_addfield(*c19_info, c19_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c19_info, c19_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c19_info, c19_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c19_info, c19_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c19_info, c19_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c19_info, c19_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c19_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c19_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c19_info, sf_mex_duplicatearraysafe(&c19_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c19_info, sf_mex_duplicatearraysafe(&c19_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c19_info, c19_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c19_info, c19_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 1);
  sf_mex_addfield(*c19_info, c19_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c19_info, c19_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c19_info, c19_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c19_info, c19_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c19_info, c19_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c19_info, c19_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c19_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c19_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c19_info, sf_mex_duplicatearraysafe(&c19_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c19_info, sf_mex_duplicatearraysafe(&c19_lhs1), "lhs", "lhs",
                  1);
  sf_mex_destroy(&c19_rhs0);
  sf_mex_destroy(&c19_lhs0);
  sf_mex_destroy(&c19_rhs1);
  sf_mex_destroy(&c19_lhs1);
}

static const mxArray *c19_emlrt_marshallOut(const char * c19_u)
{
  const mxArray *c19_y = NULL;
  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", c19_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c19_u)), false);
  return c19_y;
}

static const mxArray *c19_b_emlrt_marshallOut(const uint32_T c19_u)
{
  const mxArray *c19_y = NULL;
  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", &c19_u, 7, 0U, 0U, 0U, 0), false);
  return c19_y;
}

static const mxArray *c19_b_sf_marshallOut(void *chartInstanceVoid, void
  *c19_inData)
{
  const mxArray *c19_mxArrayOutData = NULL;
  int32_T c19_u;
  const mxArray *c19_y = NULL;
  SFc19_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc19_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c19_mxArrayOutData = NULL;
  c19_u = *(int32_T *)c19_inData;
  c19_y = NULL;
  sf_mex_assign(&c19_y, sf_mex_create("y", &c19_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c19_mxArrayOutData, c19_y, false);
  return c19_mxArrayOutData;
}

static int32_T c19_c_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId)
{
  int32_T c19_y;
  int32_T c19_i0;
  (void)chartInstance;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), &c19_i0, 1, 6, 0U, 0, 0U, 0);
  c19_y = c19_i0;
  sf_mex_destroy(&c19_u);
  return c19_y;
}

static void c19_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c19_mxArrayInData, const char_T *c19_varName, void *c19_outData)
{
  const mxArray *c19_b_sfEvent;
  const char_T *c19_identifier;
  emlrtMsgIdentifier c19_thisId;
  int32_T c19_y;
  SFc19_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc19_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c19_b_sfEvent = sf_mex_dup(c19_mxArrayInData);
  c19_identifier = c19_varName;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_y = c19_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c19_b_sfEvent),
    &c19_thisId);
  sf_mex_destroy(&c19_b_sfEvent);
  *(int32_T *)c19_outData = c19_y;
  sf_mex_destroy(&c19_mxArrayInData);
}

static uint8_T c19_d_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_b_is_active_c19_CSE1_DP, const char_T *c19_identifier)
{
  uint8_T c19_y;
  emlrtMsgIdentifier c19_thisId;
  c19_thisId.fIdentifier = c19_identifier;
  c19_thisId.fParent = NULL;
  c19_y = c19_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c19_b_is_active_c19_CSE1_DP), &c19_thisId);
  sf_mex_destroy(&c19_b_is_active_c19_CSE1_DP);
  return c19_y;
}

static uint8_T c19_e_emlrt_marshallIn(SFc19_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c19_u, const emlrtMsgIdentifier *c19_parentId)
{
  uint8_T c19_y;
  uint8_T c19_u0;
  (void)chartInstance;
  sf_mex_import(c19_parentId, sf_mex_dup(c19_u), &c19_u0, 1, 3, 0U, 0, 0U, 0);
  c19_y = c19_u0;
  sf_mex_destroy(&c19_u);
  return c19_y;
}

static void init_dsm_address_info(SFc19_CSE1_DPInstanceStruct *chartInstance)
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

void sf_c19_CSE1_DP_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3861847529U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4171984375U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3364069176U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1336699404U);
}

mxArray *sf_c19_CSE1_DP_get_autoinheritance_info(void)
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

mxArray *sf_c19_CSE1_DP_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c19_CSE1_DP_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c19_CSE1_DP(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"F_x\",},{M[1],M[7],T\"F_y\",},{M[8],M[0],T\"is_active_c19_CSE1_DP\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c19_CSE1_DP_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc19_CSE1_DPInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc19_CSE1_DPInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_DPMachineNumber_,
           19,
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
          (MexFcnForType)c19_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c19_sf_marshallOut,(MexInFcnForType)c19_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c19_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c19_sf_marshallOut,(MexInFcnForType)c19_sf_marshallIn);

        {
          real_T *c19_alpha;
          real_T *c19_F_x;
          real_T *c19_u_VST;
          real_T *c19_F_y;
          c19_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c19_u_VST = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c19_F_x = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c19_alpha = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c19_alpha);
          _SFD_SET_DATA_VALUE_PTR(1U, c19_F_x);
          _SFD_SET_DATA_VALUE_PTR(2U, c19_u_VST);
          _SFD_SET_DATA_VALUE_PTR(3U, c19_F_y);
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
  return "NHJ7r9elp6jyZ6hMsRm63F";
}

static void sf_opaque_initialize_c19_CSE1_DP(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar);
  initialize_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c19_CSE1_DP(void *chartInstanceVar)
{
  enable_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c19_CSE1_DP(void *chartInstanceVar)
{
  disable_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c19_CSE1_DP(void *chartInstanceVar)
{
  sf_gateway_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c19_CSE1_DP(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c19_CSE1_DP();/* state var info */
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

extern void sf_internal_set_sim_state_c19_CSE1_DP(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c19_CSE1_DP();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c19_CSE1_DP(SimStruct* S)
{
  return sf_internal_get_sim_state_c19_CSE1_DP(S);
}

static void sf_opaque_set_sim_state_c19_CSE1_DP(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c19_CSE1_DP(S, st);
}

static void sf_opaque_terminate_c19_CSE1_DP(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_DP_optimization_info();
    }

    finalize_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c19_CSE1_DP(SimStruct *S)
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
    initialize_params_c19_CSE1_DP((SFc19_CSE1_DPInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c19_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_DP_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      19);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,19,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,19,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,19);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,19,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,19,2);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,19);
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

static void mdlRTW_c19_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c19_CSE1_DP(SimStruct *S)
{
  SFc19_CSE1_DPInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc19_CSE1_DPInstanceStruct *)utMalloc(sizeof
    (SFc19_CSE1_DPInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc19_CSE1_DPInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c19_CSE1_DP;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c19_CSE1_DP;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c19_CSE1_DP;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c19_CSE1_DP;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c19_CSE1_DP;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c19_CSE1_DP;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c19_CSE1_DP;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c19_CSE1_DP;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c19_CSE1_DP;
  chartInstance->chartInfo.mdlStart = mdlStart_c19_CSE1_DP;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c19_CSE1_DP;
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

void c19_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c19_CSE1_DP(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c19_CSE1_DP(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c19_CSE1_DP(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c19_CSE1_DP_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
