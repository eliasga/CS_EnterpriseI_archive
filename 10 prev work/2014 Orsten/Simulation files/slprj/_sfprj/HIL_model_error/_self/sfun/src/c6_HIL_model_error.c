/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_error_sfun.h"
#include "c6_HIL_model_error.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HIL_model_error_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c6_debug_family_names[41] = { "Lpp", "n", "Rk", "maxWP", "x",
  "y", "deltaX", "deltaY", "distX", "distY", "fd", "fe", "ff", "fg", "a", "b",
  "c", "fact", "Xlos", "Ylos", "LosPos", "PosOld", "LosOld", "x_mark",
  "WP_angle", "y_star", "nargin", "nargout", "WPi", "alphaIce", "WP", "eta",
  "icebergData", "saved_alphaIce", "WPi_out", "deltaXlos", "deltaYlos",
  "WPnormal", "delta", "y_mark", "alphaIce_save" };

/* Function Declarations */
static void initialize_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance);
static void initialize_params_c6_HIL_model_error
  (SFc6_HIL_model_errorInstanceStruct *chartInstance);
static void enable_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance);
static void disable_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance);
static void c6_update_debugger_state_c6_HIL_model_error
  (SFc6_HIL_model_errorInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c6_HIL_model_error
  (SFc6_HIL_model_errorInstanceStruct *chartInstance);
static void set_sim_state_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct *
  chartInstance, const mxArray *c6_st);
static void finalize_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance);
static void sf_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance);
static void c6_chartstep_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance);
static void initSimStructsc6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct *
  chartInstance);
static void registerMessagesc6_HIL_model_error
  (SFc6_HIL_model_errorInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static real_T c6_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_alphaIce_save, const char_T *c6_identifier);
static real_T c6_b_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[30]);
static real_T c6_mpower(SFc6_HIL_model_errorInstanceStruct *chartInstance,
  real_T c6_a);
static void c6_eml_scalar_eg(SFc6_HIL_model_errorInstanceStruct *chartInstance);
static real_T c6_abs(SFc6_HIL_model_errorInstanceStruct *chartInstance, real_T
                     c6_x);
static void c6_eml_error(SFc6_HIL_model_errorInstanceStruct *chartInstance);
static real_T c6_atan2(SFc6_HIL_model_errorInstanceStruct *chartInstance, real_T
  c6_y, real_T c6_x);
static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_c_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint8_T c6_d_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_HIL_model_error, const char_T
  *c6_identifier);
static uint8_T c6_e_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_HIL_model_errorInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c6_is_active_c6_HIL_model_error = 0U;
}

static void initialize_params_c6_HIL_model_error
  (SFc6_HIL_model_errorInstanceStruct *chartInstance)
{
}

static void enable_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c6_update_debugger_state_c6_HIL_model_error
  (SFc6_HIL_model_errorInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c6_HIL_model_error
  (SFc6_HIL_model_errorInstanceStruct *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  real_T c6_hoistedGlobal;
  real_T c6_u;
  const mxArray *c6_b_y = NULL;
  real_T c6_b_hoistedGlobal;
  real_T c6_b_u;
  const mxArray *c6_c_y = NULL;
  real_T c6_c_hoistedGlobal;
  real_T c6_c_u;
  const mxArray *c6_d_y = NULL;
  real_T c6_d_hoistedGlobal;
  real_T c6_d_u;
  const mxArray *c6_e_y = NULL;
  real_T c6_e_hoistedGlobal;
  real_T c6_e_u;
  const mxArray *c6_f_y = NULL;
  real_T c6_f_hoistedGlobal;
  real_T c6_f_u;
  const mxArray *c6_g_y = NULL;
  real_T c6_g_hoistedGlobal;
  real_T c6_g_u;
  const mxArray *c6_h_y = NULL;
  uint8_T c6_h_hoistedGlobal;
  uint8_T c6_h_u;
  const mxArray *c6_i_y = NULL;
  real_T *c6_WPi_out;
  real_T *c6_WPnormal;
  real_T *c6_alphaIce_save;
  real_T *c6_delta;
  real_T *c6_deltaXlos;
  real_T *c6_deltaYlos;
  real_T *c6_y_mark;
  c6_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c6_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c6_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c6_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c6_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c6_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c6_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellarray(8), FALSE);
  c6_hoistedGlobal = *c6_WPi_out;
  c6_u = c6_hoistedGlobal;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_b_hoistedGlobal = *c6_WPnormal;
  c6_b_u = c6_b_hoistedGlobal;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  c6_c_hoistedGlobal = *c6_alphaIce_save;
  c6_c_u = c6_c_hoistedGlobal;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 2, c6_d_y);
  c6_d_hoistedGlobal = *c6_delta;
  c6_d_u = c6_d_hoistedGlobal;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 3, c6_e_y);
  c6_e_hoistedGlobal = *c6_deltaXlos;
  c6_e_u = c6_e_hoistedGlobal;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 4, c6_f_y);
  c6_f_hoistedGlobal = *c6_deltaYlos;
  c6_f_u = c6_f_hoistedGlobal;
  c6_g_y = NULL;
  sf_mex_assign(&c6_g_y, sf_mex_create("y", &c6_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 5, c6_g_y);
  c6_g_hoistedGlobal = *c6_y_mark;
  c6_g_u = c6_g_hoistedGlobal;
  c6_h_y = NULL;
  sf_mex_assign(&c6_h_y, sf_mex_create("y", &c6_g_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 6, c6_h_y);
  c6_h_hoistedGlobal = chartInstance->c6_is_active_c6_HIL_model_error;
  c6_h_u = c6_h_hoistedGlobal;
  c6_i_y = NULL;
  sf_mex_assign(&c6_i_y, sf_mex_create("y", &c6_h_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 7, c6_i_y);
  sf_mex_assign(&c6_st, c6_y, FALSE);
  return c6_st;
}

static void set_sim_state_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct *
  chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T *c6_WPi_out;
  real_T *c6_WPnormal;
  real_T *c6_alphaIce_save;
  real_T *c6_delta;
  real_T *c6_deltaXlos;
  real_T *c6_deltaYlos;
  real_T *c6_y_mark;
  c6_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c6_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c6_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c6_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c6_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c6_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c6_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c6_doneDoubleBufferReInit = TRUE;
  c6_u = sf_mex_dup(c6_st);
  *c6_WPi_out = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c6_u, 0)), "WPi_out");
  *c6_WPnormal = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c6_u, 1)), "WPnormal");
  *c6_alphaIce_save = c6_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 2)), "alphaIce_save");
  *c6_delta = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u,
    3)), "delta");
  *c6_deltaXlos = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c6_u, 4)), "deltaXlos");
  *c6_deltaYlos = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c6_u, 5)), "deltaYlos");
  *c6_y_mark = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u,
    6)), "y_mark");
  chartInstance->c6_is_active_c6_HIL_model_error = c6_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 7)),
     "is_active_c6_HIL_model_error");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_HIL_model_error(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance)
{
}

static void sf_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance)
{
  int32_T c6_i0;
  int32_T c6_i1;
  int32_T c6_i2;
  real_T *c6_WPi;
  real_T *c6_alphaIce;
  real_T *c6_WPi_out;
  real_T *c6_deltaXlos;
  real_T *c6_deltaYlos;
  real_T *c6_WPnormal;
  real_T *c6_delta;
  real_T *c6_y_mark;
  real_T *c6_saved_alphaIce;
  real_T *c6_alphaIce_save;
  real_T (*c6_icebergData)[2];
  real_T (*c6_eta)[2];
  real_T (*c6_WP)[4];
  c6_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c6_saved_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c6_icebergData = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
  c6_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c6_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c6_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c6_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c6_eta = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
  c6_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c6_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c6_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c6_WPi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c6_WPi, 0U);
  _SFD_DATA_RANGE_CHECK(*c6_alphaIce, 1U);
  for (c6_i0 = 0; c6_i0 < 4; c6_i0++) {
    _SFD_DATA_RANGE_CHECK((*c6_WP)[c6_i0], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c6_WPi_out, 3U);
  _SFD_DATA_RANGE_CHECK(*c6_deltaXlos, 4U);
  for (c6_i1 = 0; c6_i1 < 2; c6_i1++) {
    _SFD_DATA_RANGE_CHECK((*c6_eta)[c6_i1], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c6_deltaYlos, 6U);
  _SFD_DATA_RANGE_CHECK(*c6_WPnormal, 7U);
  _SFD_DATA_RANGE_CHECK(*c6_delta, 8U);
  _SFD_DATA_RANGE_CHECK(*c6_y_mark, 9U);
  for (c6_i2 = 0; c6_i2 < 2; c6_i2++) {
    _SFD_DATA_RANGE_CHECK((*c6_icebergData)[c6_i2], 10U);
  }

  _SFD_DATA_RANGE_CHECK(*c6_saved_alphaIce, 11U);
  _SFD_DATA_RANGE_CHECK(*c6_alphaIce_save, 12U);
  chartInstance->c6_sfEvent = CALL_EVENT;
  c6_chartstep_c6_HIL_model_error(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_errorMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c6_chartstep_c6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct
  *chartInstance)
{
  real_T c6_hoistedGlobal;
  real_T c6_b_hoistedGlobal;
  real_T c6_c_hoistedGlobal;
  real_T c6_WPi;
  real_T c6_alphaIce;
  int32_T c6_i3;
  real_T c6_WP[4];
  int32_T c6_i4;
  real_T c6_eta[2];
  int32_T c6_i5;
  real_T c6_icebergData[2];
  real_T c6_saved_alphaIce;
  uint32_T c6_debug_family_var_map[41];
  real_T c6_Lpp;
  real_T c6_n;
  real_T c6_Rk;
  real_T c6_maxWP;
  real_T c6_x;
  real_T c6_y;
  real_T c6_deltaX;
  real_T c6_deltaY;
  real_T c6_distX;
  real_T c6_distY;
  real_T c6_fd;
  real_T c6_fe;
  real_T c6_ff;
  real_T c6_fg;
  real_T c6_a;
  real_T c6_b;
  real_T c6_c;
  real_T c6_fact;
  real_T c6_Xlos;
  real_T c6_Ylos;
  real_T c6_LosPos;
  real_T c6_PosOld;
  real_T c6_LosOld;
  real_T c6_x_mark;
  real_T c6_WP_angle;
  real_T c6_y_star;
  real_T c6_nargin = 6.0;
  real_T c6_nargout = 7.0;
  real_T c6_WPi_out;
  real_T c6_deltaXlos;
  real_T c6_deltaYlos;
  real_T c6_WPnormal;
  real_T c6_delta;
  real_T c6_y_mark;
  real_T c6_alphaIce_save;
  real_T c6_b_b;
  real_T c6_b_x;
  real_T c6_c_x;
  real_T c6_u;
  const mxArray *c6_b_y = NULL;
  real_T c6_b_u;
  const mxArray *c6_c_y = NULL;
  real_T c6_A;
  real_T c6_B;
  real_T c6_d_x;
  real_T c6_d_y;
  real_T c6_e_x;
  real_T c6_e_y;
  real_T c6_b_a;
  real_T c6_c_b;
  real_T c6_f_y;
  real_T c6_c_a;
  real_T c6_d_b;
  real_T c6_g_y;
  real_T c6_d_a;
  real_T c6_e_b;
  real_T c6_h_y;
  real_T c6_f_b;
  real_T c6_g_b;
  real_T c6_i_y;
  real_T c6_h_b;
  real_T c6_j_y;
  real_T c6_e_a;
  real_T c6_i_b;
  real_T c6_k_y;
  real_T c6_j_b;
  real_T c6_l_y;
  real_T c6_f_a;
  real_T c6_k_b;
  real_T c6_m_y;
  real_T c6_g_a;
  real_T c6_l_b;
  real_T c6_n_y;
  real_T c6_m_b;
  real_T c6_o_y;
  real_T c6_h_a;
  real_T c6_n_b;
  real_T c6_p_y;
  real_T c6_o_b;
  real_T c6_q_y;
  real_T c6_i_a;
  real_T c6_p_b;
  real_T c6_r_y;
  real_T c6_f_x;
  real_T c6_g_x;
  real_T c6_j_a;
  real_T c6_q_b;
  real_T c6_s_y;
  real_T c6_r_b;
  real_T c6_t_y;
  real_T c6_b_A;
  real_T c6_b_B;
  real_T c6_h_x;
  real_T c6_u_y;
  real_T c6_i_x;
  real_T c6_v_y;
  real_T c6_k_a;
  real_T c6_s_b;
  real_T c6_w_y;
  real_T c6_l_a;
  real_T c6_x_y;
  real_T c6_m_a;
  real_T c6_t_b;
  real_T c6_y_y;
  real_T c6_j_x;
  real_T c6_k_x;
  real_T c6_l_x;
  real_T c6_m_x;
  real_T c6_n_x;
  real_T c6_o_x;
  real_T c6_u_b;
  real_T c6_ab_y;
  real_T c6_c_A;
  real_T c6_c_B;
  real_T c6_p_x;
  real_T c6_bb_y;
  real_T c6_q_x;
  real_T c6_cb_y;
  real_T c6_r_x;
  real_T c6_s_x;
  real_T c6_t_x;
  real_T c6_u_x;
  real_T c6_db_y;
  real_T c6_v_x;
  real_T c6_w_x;
  real_T c6_n_a;
  real_T c6_v_b;
  real_T c6_x_x;
  real_T c6_y_x;
  real_T c6_o_a;
  real_T c6_w_b;
  real_T c6_eb_y;
  real_T c6_ab_x;
  real_T c6_bb_x;
  real_T c6_p_a;
  real_T c6_x_b;
  real_T c6_fb_y;
  real_T c6_cb_x;
  real_T c6_db_x;
  real_T c6_q_a;
  real_T c6_y_b;
  real_T c6_gb_y;
  real_T c6_eb_x;
  real_T c6_fb_x;
  real_T c6_r_a;
  real_T c6_ab_b;
  real_T c6_hb_y;
  real_T c6_gb_x;
  real_T c6_hb_x;
  real_T c6_s_a;
  real_T c6_bb_b;
  real_T *c6_b_alphaIce_save;
  real_T *c6_b_y_mark;
  real_T *c6_b_delta;
  real_T *c6_b_WPnormal;
  real_T *c6_b_deltaYlos;
  real_T *c6_b_deltaXlos;
  real_T *c6_b_WPi_out;
  real_T *c6_b_saved_alphaIce;
  real_T *c6_b_alphaIce;
  real_T *c6_b_WPi;
  real_T (*c6_b_icebergData)[2];
  real_T (*c6_b_eta)[2];
  real_T (*c6_b_WP)[4];
  int32_T exitg1;
  c6_b_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c6_b_saved_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c6_b_icebergData = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
  c6_b_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c6_b_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c6_b_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c6_b_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c6_b_eta = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
  c6_b_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c6_b_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_b_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c6_b_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c6_b_WPi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  c6_hoistedGlobal = *c6_b_WPi;
  c6_b_hoistedGlobal = *c6_b_alphaIce;
  c6_c_hoistedGlobal = *c6_b_saved_alphaIce;
  c6_WPi = c6_hoistedGlobal;
  c6_alphaIce = c6_b_hoistedGlobal;
  for (c6_i3 = 0; c6_i3 < 4; c6_i3++) {
    c6_WP[c6_i3] = (*c6_b_WP)[c6_i3];
  }

  for (c6_i4 = 0; c6_i4 < 2; c6_i4++) {
    c6_eta[c6_i4] = (*c6_b_eta)[c6_i4];
  }

  for (c6_i5 = 0; c6_i5 < 2; c6_i5++) {
    c6_icebergData[c6_i5] = (*c6_b_icebergData)[c6_i5];
  }

  c6_saved_alphaIce = c6_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 41U, 41U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_Lpp, 0U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_n, 1U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_Rk, 2U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_maxWP, 3U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_x, 4U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_y, 5U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_deltaX, 6U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_deltaY, 7U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_distX, 8U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_distY, 9U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_fd, 10U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_fe, 11U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_ff, 12U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_fg, 13U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_a, 14U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b, 15U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c, 16U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_fact, 17U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_Xlos, 18U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_Ylos, 19U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_LosPos, 20U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_PosOld, 21U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_LosOld, 22U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_x_mark, 23U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_WP_angle, 24U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_y_star, 25U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 26U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 27U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_WPi, 28U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_alphaIce, 29U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_WP, 30U, c6_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_eta, 31U, c6_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_icebergData, 32U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_saved_alphaIce, 33U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_WPi_out, 34U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_deltaXlos, 35U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_deltaYlos, 36U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_WPnormal, 37U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_delta, 38U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_y_mark, 39U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_alphaIce_save, 40U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 3);
  c6_Lpp = c6_icebergData[0];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 4);
  c6_n = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_b_b = c6_Lpp;
  c6_Rk = 2.0 * c6_b_b;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 7);
  c6_b_x = c6_WPi;
  c6_WPi = c6_b_x;
  c6_c_x = c6_WPi;
  c6_WPi = c6_c_x;
  c6_WPi = muDoubleScalarRound(c6_WPi);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 8);
  c6_maxWP = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 10);
  c6_x = c6_eta[0];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 11);
  c6_y = c6_eta[1];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 14);
  if (CV_EML_IF(0, 1, 0, c6_WPi <= c6_maxWP)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 15);
    c6_deltaX = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP",
      (int32_T)_SFD_INTEGER_CHECK("WPi", c6_WPi), 1, 2, 1, 0) - 1] - c6_WP
      [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi - 1", c6_WPi - 1.0), 1, 2, 1, 0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 16);
    c6_deltaY = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP",
      (int32_T)_SFD_INTEGER_CHECK("WPi", c6_WPi), 1, 2, 1, 0) + 1] - c6_WP
      [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi - 1", c6_WPi - 1.0), 1, 2, 1, 0) + 1];
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 19);
    c6_distX = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi", c6_WPi), 1, 2, 1, 0) - 1] - c6_x;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 20);
    c6_distY = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi", c6_WPi), 1, 2, 1, 0) + 1] - c6_y;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 21);
    if (CV_EML_IF(0, 1, 1, c6_mpower(chartInstance, c6_distX) + c6_mpower
                  (chartInstance, c6_distY) <= c6_mpower(chartInstance, c6_Rk)))
    {
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 23);
      c6_WPi++;
      sf_mex_printf("%s =\\n", "WPi");
      c6_u = c6_WPi;
      c6_b_y = NULL;
      sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
      sf_mex_call_debug("disp", 0U, 1U, 14, c6_b_y);
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 24);
      if (CV_EML_IF(0, 1, 2, c6_WPi > c6_maxWP)) {
        _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 25);
        c6_saved_alphaIce = c6_alphaIce;
        sf_mex_printf("%s =\\n", "saved_alphaIce");
        c6_b_u = c6_saved_alphaIce;
        c6_c_y = NULL;
        sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c6_c_y);
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 30);
    c6_deltaX = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 31);
    c6_deltaY = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 32);
    c6_distX = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 33);
    c6_distY = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 38);
  if (CV_EML_IF(0, 1, 3, c6_WPi <= c6_maxWP)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 41);
    if (CV_EML_IF(0, 1, 4, c6_abs(chartInstance, c6_deltaX) > 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 43);
      c6_A = c6_deltaY;
      c6_B = c6_deltaX;
      c6_d_x = c6_A;
      c6_d_y = c6_B;
      c6_e_x = c6_d_x;
      c6_e_y = c6_d_y;
      c6_fd = c6_e_x / c6_e_y;
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 44);
      c6_fe = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
        _SFD_INTEGER_CHECK("WPi - 1", c6_WPi - 1.0), 1, 2, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 45);
      c6_ff = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
        _SFD_INTEGER_CHECK("WPi - 1", c6_WPi - 1.0), 1, 2, 1, 0) + 1];
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 46);
      c6_b_a = c6_fd;
      c6_c_b = c6_fe;
      c6_f_y = c6_b_a * c6_c_b;
      c6_fg = c6_ff - c6_f_y;
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 48);
      c6_a = 1.0 + c6_mpower(chartInstance, c6_fd);
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 49);
      c6_c_a = c6_fd;
      c6_d_b = c6_fg;
      c6_g_y = c6_c_a * c6_d_b;
      c6_d_a = c6_fd;
      c6_e_b = c6_y;
      c6_h_y = c6_d_a * c6_e_b;
      c6_f_b = (c6_g_y - c6_h_y) - c6_x;
      c6_b = 2.0 * c6_f_b;
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 50);
      c6_g_b = c6_Lpp;
      c6_i_y = 4.0 * c6_g_b;
      c6_h_b = c6_fg;
      c6_j_y = 2.0 * c6_h_b;
      c6_e_a = c6_j_y;
      c6_i_b = c6_y;
      c6_k_y = c6_e_a * c6_i_b;
      c6_c = (((c6_mpower(chartInstance, c6_x) + c6_mpower(chartInstance, c6_y))
               + c6_mpower(chartInstance, c6_fg)) - c6_mpower(chartInstance,
               c6_i_y)) - c6_k_y;
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 52);
      c6_fact = -1.0;
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 53);
      if (CV_EML_IF(0, 1, 5, c6_deltaX > 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 54);
        c6_fact = 1.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 57);
      do {
        exitg1 = 0;
        c6_j_b = c6_a;
        c6_l_y = 4.0 * c6_j_b;
        c6_f_a = c6_l_y;
        c6_k_b = c6_c;
        c6_m_y = c6_f_a * c6_k_b;
        if (CV_EML_WHILE(0, 1, 0, c6_mpower(chartInstance, c6_b) < c6_m_y)) {
          _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 58);
          c6_n++;
          _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 60);
          c6_g_a = c6_n;
          c6_l_b = c6_Lpp;
          c6_n_y = c6_g_a * c6_l_b;
          c6_m_b = c6_fg;
          c6_o_y = 2.0 * c6_m_b;
          c6_h_a = c6_o_y;
          c6_n_b = c6_y;
          c6_p_y = c6_h_a * c6_n_b;
          c6_c = (((c6_mpower(chartInstance, c6_x) + c6_mpower(chartInstance,
                     c6_y)) + c6_mpower(chartInstance, c6_fg)) - c6_mpower
                  (chartInstance, c6_n_y)) - c6_p_y;
          _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 57);
          _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 63);
      c6_o_b = c6_a;
      c6_q_y = 4.0 * c6_o_b;
      c6_i_a = c6_q_y;
      c6_p_b = c6_c;
      c6_r_y = c6_i_a * c6_p_b;
      c6_f_x = c6_mpower(chartInstance, c6_b) - c6_r_y;
      c6_g_x = c6_f_x;
      if (c6_g_x < 0.0) {
        c6_eml_error(chartInstance);
      }

      c6_g_x = muDoubleScalarSqrt(c6_g_x);
      c6_j_a = c6_fact;
      c6_q_b = c6_g_x;
      c6_s_y = c6_j_a * c6_q_b;
      c6_r_b = c6_a;
      c6_t_y = 2.0 * c6_r_b;
      c6_b_A = -c6_b + c6_s_y;
      c6_b_B = c6_t_y;
      c6_h_x = c6_b_A;
      c6_u_y = c6_b_B;
      c6_i_x = c6_h_x;
      c6_v_y = c6_u_y;
      c6_Xlos = c6_i_x / c6_v_y;
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 64);
      c6_k_a = c6_fd;
      c6_s_b = c6_Xlos - c6_fe;
      c6_w_y = c6_k_a * c6_s_b;
      c6_Ylos = c6_w_y + c6_ff;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 68);
      c6_fact = -1.0;
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 69);
      if (CV_EML_IF(0, 1, 6, c6_deltaY > 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 70);
        c6_fact = 1.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 73);
      c6_Xlos = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP",
        (int32_T)_SFD_INTEGER_CHECK("WPi - 1", c6_WPi - 1.0), 1, 2, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 74);
      c6_l_a = c6_fact;
      c6_x_y = c6_l_a * 4.0;
      c6_m_a = c6_x_y;
      c6_t_b = c6_Lpp;
      c6_y_y = c6_m_a * c6_t_b;
      c6_Ylos = c6_y + c6_y_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 79);
    c6_deltaXlos = c6_Xlos - c6_x;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 80);
    c6_deltaYlos = c6_Ylos - c6_y;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 83);
    c6_j_x = c6_mpower(chartInstance, c6_Xlos - c6_x) + c6_mpower(chartInstance,
      c6_Ylos - c6_y);
    c6_LosPos = c6_j_x;
    if (c6_LosPos < 0.0) {
      c6_eml_error(chartInstance);
    }

    c6_k_x = c6_LosPos;
    c6_LosPos = c6_k_x;
    c6_LosPos = muDoubleScalarSqrt(c6_LosPos);
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 84);
    c6_l_x = c6_mpower(chartInstance, c6_x - c6_WP[(int32_T)(real_T)
                       _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi-1", c6_WPi - 1.0), 1, 2, 1, 0) - 1]) + c6_mpower
      (chartInstance, c6_y - c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
        "WP", (int32_T)_SFD_INTEGER_CHECK("WPi-1", c6_WPi - 1.0), 1, 2, 1, 0) +
       1]);
    c6_PosOld = c6_l_x;
    if (c6_PosOld < 0.0) {
      c6_eml_error(chartInstance);
    }

    c6_m_x = c6_PosOld;
    c6_PosOld = c6_m_x;
    c6_PosOld = muDoubleScalarSqrt(c6_PosOld);
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 85);
    c6_n_x = c6_mpower(chartInstance, c6_Xlos - c6_WP[(int32_T)(real_T)
                       _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi-1", c6_WPi - 1.0), 1, 2, 1, 0) - 1]) + c6_mpower
      (chartInstance, c6_Ylos - c6_WP[(int32_T)(real_T)
       _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi-1",
         c6_WPi - 1.0), 1, 2, 1, 0) + 1]);
    c6_LosOld = c6_n_x;
    if (c6_LosOld < 0.0) {
      c6_eml_error(chartInstance);
    }

    c6_o_x = c6_LosOld;
    c6_LosOld = c6_o_x;
    c6_LosOld = muDoubleScalarSqrt(c6_LosOld);
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 87);
    if (CV_EML_IF(0, 1, 7, c6_LosOld == 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 88);
      c6_x_mark = 0.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 90);
      c6_u_b = c6_LosOld;
      c6_ab_y = 2.0 * c6_u_b;
      c6_c_A = (c6_mpower(chartInstance, c6_PosOld) + c6_mpower(chartInstance,
                 c6_LosOld)) - c6_mpower(chartInstance, c6_LosPos);
      c6_c_B = c6_ab_y;
      c6_p_x = c6_c_A;
      c6_bb_y = c6_c_B;
      c6_q_x = c6_p_x;
      c6_cb_y = c6_bb_y;
      c6_x_mark = c6_q_x / c6_cb_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 92);
    c6_r_x = c6_mpower(chartInstance, c6_PosOld) - c6_mpower(chartInstance,
      c6_x_mark);
    c6_s_x = c6_r_x;
    c6_s_x = muDoubleScalarSign(c6_s_x);
    c6_t_x = c6_mpower(chartInstance, c6_PosOld) - c6_mpower(chartInstance,
      c6_x_mark);
    c6_u_x = c6_t_x;
    c6_db_y = muDoubleScalarAbs(c6_u_x);
    c6_v_x = c6_db_y;
    c6_w_x = c6_v_x;
    if (c6_w_x < 0.0) {
      c6_eml_error(chartInstance);
    }

    c6_w_x = muDoubleScalarSqrt(c6_w_x);
    c6_n_a = c6_s_x;
    c6_v_b = c6_w_x;
    c6_y_mark = c6_n_a * c6_v_b;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 97);
    c6_WP_angle = c6_atan2(chartInstance, c6_deltaY, c6_deltaX);
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 98);
    c6_x_x = c6_WP_angle;
    c6_y_x = c6_x_x;
    c6_y_x = muDoubleScalarSin(c6_y_x);
    c6_o_a = -c6_x;
    c6_w_b = c6_y_x;
    c6_eb_y = c6_o_a * c6_w_b;
    c6_ab_x = c6_WP_angle;
    c6_bb_x = c6_ab_x;
    c6_bb_x = muDoubleScalarCos(c6_bb_x);
    c6_p_a = c6_y;
    c6_x_b = c6_bb_x;
    c6_fb_y = c6_p_a * c6_x_b;
    c6_cb_x = c6_WP_angle;
    c6_db_x = c6_cb_x;
    c6_db_x = muDoubleScalarSin(c6_db_x);
    c6_q_a = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi-1", c6_WPi - 1.0), 1, 2, 1, 0) - 1];
    c6_y_b = c6_db_x;
    c6_gb_y = c6_q_a * c6_y_b;
    c6_eb_x = c6_WP_angle;
    c6_fb_x = c6_eb_x;
    c6_fb_x = muDoubleScalarCos(c6_fb_x);
    c6_r_a = c6_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi-1", c6_WPi - 1.0), 1, 2, 1, 0) + 1];
    c6_ab_b = c6_fb_x;
    c6_hb_y = c6_r_a * c6_ab_b;
    c6_y_star = ((c6_eb_y + c6_fb_y) + c6_gb_y) - c6_hb_y;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 100);
    c6_gb_x = c6_y_star;
    c6_hb_x = c6_gb_x;
    c6_hb_x = muDoubleScalarSign(c6_hb_x);
    c6_s_a = -c6_hb_x;
    c6_bb_b = c6_y_mark;
    c6_y_mark = c6_s_a * c6_bb_b;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 104);
    c6_delta = c6_LosOld - c6_x_mark;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 106);
    c6_WPnormal = c6_atan2(chartInstance, c6_WP[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi",
      c6_WPi), 1, 2, 1, 0) + 1] - c6_WP[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi-1",
      c6_WPi - 1.0), 1, 2, 1, 0) + 1], c6_WP[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi",
      c6_WPi), 1, 2, 1, 0) - 1] - c6_WP[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi-1",
      c6_WPi - 1.0), 1, 2, 1, 0) - 1]) + 1.5707963267948966;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 110);
    c6_WPi_out = c6_WPi;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 114);
    c6_WPi_out = c6_WPi;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 115);
    c6_deltaXlos = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 116);
    c6_deltaYlos = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 117);
    c6_WPnormal = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 118);
    c6_delta = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 119);
    c6_y_mark = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 123);
  c6_alphaIce_save = c6_saved_alphaIce;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -123);
  _SFD_SYMBOL_SCOPE_POP();
  *c6_b_WPi_out = c6_WPi_out;
  *c6_b_deltaXlos = c6_deltaXlos;
  *c6_b_deltaYlos = c6_deltaYlos;
  *c6_b_WPnormal = c6_WPnormal;
  *c6_b_delta = c6_delta;
  *c6_b_y_mark = c6_y_mark;
  *c6_b_alphaIce_save = c6_alphaIce_save;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
}

static void initSimStructsc6_HIL_model_error(SFc6_HIL_model_errorInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc6_HIL_model_error
  (SFc6_HIL_model_errorInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber)
{
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_HIL_model_errorInstanceStruct *chartInstance;
  chartInstance = (SFc6_HIL_model_errorInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static real_T c6_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_alphaIce_save, const char_T *c6_identifier)
{
  real_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_alphaIce_save),
    &c6_thisId);
  sf_mex_destroy(&c6_alphaIce_save);
  return c6_y;
}

static real_T c6_b_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_alphaIce_save;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_HIL_model_errorInstanceStruct *chartInstance;
  chartInstance = (SFc6_HIL_model_errorInstanceStruct *)chartInstanceVoid;
  c6_alphaIce_save = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_alphaIce_save),
    &c6_thisId);
  sf_mex_destroy(&c6_alphaIce_save);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i6;
  real_T c6_b_inData[2];
  int32_T c6_i7;
  real_T c6_u[2];
  const mxArray *c6_y = NULL;
  SFc6_HIL_model_errorInstanceStruct *chartInstance;
  chartInstance = (SFc6_HIL_model_errorInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i6 = 0; c6_i6 < 2; c6_i6++) {
    c6_b_inData[c6_i6] = (*(real_T (*)[2])c6_inData)[c6_i6];
  }

  for (c6_i7 = 0; c6_i7 < 2; c6_i7++) {
    c6_u[c6_i7] = c6_b_inData[c6_i7];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 2, 1), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i8;
  real_T c6_b_inData[2];
  int32_T c6_i9;
  real_T c6_u[2];
  const mxArray *c6_y = NULL;
  SFc6_HIL_model_errorInstanceStruct *chartInstance;
  chartInstance = (SFc6_HIL_model_errorInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i8 = 0; c6_i8 < 2; c6_i8++) {
    c6_b_inData[c6_i8] = (*(real_T (*)[2])c6_inData)[c6_i8];
  }

  for (c6_i9 = 0; c6_i9 < 2; c6_i9++) {
    c6_u[c6_i9] = c6_b_inData[c6_i9];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i10;
  int32_T c6_i11;
  int32_T c6_i12;
  real_T c6_b_inData[4];
  int32_T c6_i13;
  int32_T c6_i14;
  int32_T c6_i15;
  real_T c6_u[4];
  const mxArray *c6_y = NULL;
  SFc6_HIL_model_errorInstanceStruct *chartInstance;
  chartInstance = (SFc6_HIL_model_errorInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_i10 = 0;
  for (c6_i11 = 0; c6_i11 < 2; c6_i11++) {
    for (c6_i12 = 0; c6_i12 < 2; c6_i12++) {
      c6_b_inData[c6_i12 + c6_i10] = (*(real_T (*)[4])c6_inData)[c6_i12 + c6_i10];
    }

    c6_i10 += 2;
  }

  c6_i13 = 0;
  for (c6_i14 = 0; c6_i14 < 2; c6_i14++) {
    for (c6_i15 = 0; c6_i15 < 2; c6_i15++) {
      c6_u[c6_i15 + c6_i13] = c6_b_inData[c6_i15 + c6_i13];
    }

    c6_i13 += 2;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

const mxArray *sf_c6_HIL_model_error_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo;
  c6_ResolvedFunctionInfo c6_info[30];
  const mxArray *c6_m0 = NULL;
  int32_T c6_i16;
  c6_ResolvedFunctionInfo *c6_r0;
  c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  c6_info_helper(c6_info);
  sf_mex_assign(&c6_m0, sf_mex_createstruct("nameCaptureInfo", 1, 30), FALSE);
  for (c6_i16 = 0; c6_i16 < 30; c6_i16++) {
    c6_r0 = &c6_info[c6_i16];
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->context)), "context", "nameCaptureInfo",
                    c6_i16);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c6_r0->name)), "name", "nameCaptureInfo", c6_i16);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c6_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c6_i16);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->resolved)), "resolved", "nameCaptureInfo",
                    c6_i16);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c6_i16);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c6_i16);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c6_i16);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c6_i16);
  }

  sf_mex_assign(&c6_nameCaptureInfo, c6_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c6_nameCaptureInfo);
  return c6_nameCaptureInfo;
}

static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[30])
{
  c6_info[0].context = "";
  c6_info[0].name = "mtimes";
  c6_info[0].dominantType = "double";
  c6_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[0].fileTimeLo = 1289519692U;
  c6_info[0].fileTimeHi = 0U;
  c6_info[0].mFileTimeLo = 0U;
  c6_info[0].mFileTimeHi = 0U;
  c6_info[1].context = "";
  c6_info[1].name = "round";
  c6_info[1].dominantType = "double";
  c6_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m";
  c6_info[1].fileTimeLo = 1343830384U;
  c6_info[1].fileTimeHi = 0U;
  c6_info[1].mFileTimeLo = 0U;
  c6_info[1].mFileTimeHi = 0U;
  c6_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m";
  c6_info[2].name = "eml_scalar_round";
  c6_info[2].dominantType = "double";
  c6_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m";
  c6_info[2].fileTimeLo = 1307651238U;
  c6_info[2].fileTimeHi = 0U;
  c6_info[2].mFileTimeLo = 0U;
  c6_info[2].mFileTimeHi = 0U;
  c6_info[3].context = "";
  c6_info[3].name = "mpower";
  c6_info[3].dominantType = "double";
  c6_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c6_info[3].fileTimeLo = 1286818842U;
  c6_info[3].fileTimeHi = 0U;
  c6_info[3].mFileTimeLo = 0U;
  c6_info[3].mFileTimeHi = 0U;
  c6_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c6_info[4].name = "power";
  c6_info[4].dominantType = "double";
  c6_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c6_info[4].fileTimeLo = 1348191930U;
  c6_info[4].fileTimeHi = 0U;
  c6_info[4].mFileTimeLo = 0U;
  c6_info[4].mFileTimeHi = 0U;
  c6_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c6_info[5].name = "eml_scalar_eg";
  c6_info[5].dominantType = "double";
  c6_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[5].fileTimeLo = 1286818796U;
  c6_info[5].fileTimeHi = 0U;
  c6_info[5].mFileTimeLo = 0U;
  c6_info[5].mFileTimeHi = 0U;
  c6_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c6_info[6].name = "eml_scalexp_alloc";
  c6_info[6].dominantType = "double";
  c6_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c6_info[6].fileTimeLo = 1352424860U;
  c6_info[6].fileTimeHi = 0U;
  c6_info[6].mFileTimeLo = 0U;
  c6_info[6].mFileTimeHi = 0U;
  c6_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c6_info[7].name = "floor";
  c6_info[7].dominantType = "double";
  c6_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c6_info[7].fileTimeLo = 1343830380U;
  c6_info[7].fileTimeHi = 0U;
  c6_info[7].mFileTimeLo = 0U;
  c6_info[7].mFileTimeHi = 0U;
  c6_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c6_info[8].name = "eml_scalar_floor";
  c6_info[8].dominantType = "double";
  c6_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c6_info[8].fileTimeLo = 1286818726U;
  c6_info[8].fileTimeHi = 0U;
  c6_info[8].mFileTimeLo = 0U;
  c6_info[8].mFileTimeHi = 0U;
  c6_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c6_info[9].name = "eml_scalar_eg";
  c6_info[9].dominantType = "double";
  c6_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[9].fileTimeLo = 1286818796U;
  c6_info[9].fileTimeHi = 0U;
  c6_info[9].mFileTimeLo = 0U;
  c6_info[9].mFileTimeHi = 0U;
  c6_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c6_info[10].name = "mtimes";
  c6_info[10].dominantType = "double";
  c6_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[10].fileTimeLo = 1289519692U;
  c6_info[10].fileTimeHi = 0U;
  c6_info[10].mFileTimeLo = 0U;
  c6_info[10].mFileTimeHi = 0U;
  c6_info[11].context = "";
  c6_info[11].name = "abs";
  c6_info[11].dominantType = "double";
  c6_info[11].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c6_info[11].fileTimeLo = 1343830366U;
  c6_info[11].fileTimeHi = 0U;
  c6_info[11].mFileTimeLo = 0U;
  c6_info[11].mFileTimeHi = 0U;
  c6_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c6_info[12].name = "eml_scalar_abs";
  c6_info[12].dominantType = "double";
  c6_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c6_info[12].fileTimeLo = 1286818712U;
  c6_info[12].fileTimeHi = 0U;
  c6_info[12].mFileTimeLo = 0U;
  c6_info[12].mFileTimeHi = 0U;
  c6_info[13].context = "";
  c6_info[13].name = "mrdivide";
  c6_info[13].dominantType = "double";
  c6_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c6_info[13].fileTimeLo = 1357951548U;
  c6_info[13].fileTimeHi = 0U;
  c6_info[13].mFileTimeLo = 1319729966U;
  c6_info[13].mFileTimeHi = 0U;
  c6_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c6_info[14].name = "rdivide";
  c6_info[14].dominantType = "double";
  c6_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[14].fileTimeLo = 1346510388U;
  c6_info[14].fileTimeHi = 0U;
  c6_info[14].mFileTimeLo = 0U;
  c6_info[14].mFileTimeHi = 0U;
  c6_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[15].name = "eml_scalexp_compatible";
  c6_info[15].dominantType = "double";
  c6_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c6_info[15].fileTimeLo = 1286818796U;
  c6_info[15].fileTimeHi = 0U;
  c6_info[15].mFileTimeLo = 0U;
  c6_info[15].mFileTimeHi = 0U;
  c6_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c6_info[16].name = "eml_div";
  c6_info[16].dominantType = "double";
  c6_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c6_info[16].fileTimeLo = 1313347810U;
  c6_info[16].fileTimeHi = 0U;
  c6_info[16].mFileTimeLo = 0U;
  c6_info[16].mFileTimeHi = 0U;
  c6_info[17].context = "";
  c6_info[17].name = "sqrt";
  c6_info[17].dominantType = "double";
  c6_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c6_info[17].fileTimeLo = 1343830386U;
  c6_info[17].fileTimeHi = 0U;
  c6_info[17].mFileTimeLo = 0U;
  c6_info[17].mFileTimeHi = 0U;
  c6_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c6_info[18].name = "eml_error";
  c6_info[18].dominantType = "char";
  c6_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c6_info[18].fileTimeLo = 1343830358U;
  c6_info[18].fileTimeHi = 0U;
  c6_info[18].mFileTimeLo = 0U;
  c6_info[18].mFileTimeHi = 0U;
  c6_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c6_info[19].name = "eml_scalar_sqrt";
  c6_info[19].dominantType = "double";
  c6_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c6_info[19].fileTimeLo = 1286818738U;
  c6_info[19].fileTimeHi = 0U;
  c6_info[19].mFileTimeLo = 0U;
  c6_info[19].mFileTimeHi = 0U;
  c6_info[20].context = "";
  c6_info[20].name = "sign";
  c6_info[20].dominantType = "double";
  c6_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c6_info[20].fileTimeLo = 1354368064U;
  c6_info[20].fileTimeHi = 0U;
  c6_info[20].mFileTimeLo = 0U;
  c6_info[20].mFileTimeHi = 0U;
  c6_info[21].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c6_info[21].name = "eml_scalar_sign";
  c6_info[21].dominantType = "double";
  c6_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sign.m";
  c6_info[21].fileTimeLo = 1354368064U;
  c6_info[21].fileTimeHi = 0U;
  c6_info[21].mFileTimeLo = 0U;
  c6_info[21].mFileTimeHi = 0U;
  c6_info[22].context = "";
  c6_info[22].name = "atan2";
  c6_info[22].dominantType = "double";
  c6_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c6_info[22].fileTimeLo = 1343830372U;
  c6_info[22].fileTimeHi = 0U;
  c6_info[22].mFileTimeLo = 0U;
  c6_info[22].mFileTimeHi = 0U;
  c6_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c6_info[23].name = "eml_scalar_eg";
  c6_info[23].dominantType = "double";
  c6_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[23].fileTimeLo = 1286818796U;
  c6_info[23].fileTimeHi = 0U;
  c6_info[23].mFileTimeLo = 0U;
  c6_info[23].mFileTimeHi = 0U;
  c6_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c6_info[24].name = "eml_scalexp_alloc";
  c6_info[24].dominantType = "double";
  c6_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c6_info[24].fileTimeLo = 1352424860U;
  c6_info[24].fileTimeHi = 0U;
  c6_info[24].mFileTimeLo = 0U;
  c6_info[24].mFileTimeHi = 0U;
  c6_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c6_info[25].name = "eml_scalar_atan2";
  c6_info[25].dominantType = "double";
  c6_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m";
  c6_info[25].fileTimeLo = 1286818720U;
  c6_info[25].fileTimeHi = 0U;
  c6_info[25].mFileTimeLo = 0U;
  c6_info[25].mFileTimeHi = 0U;
  c6_info[26].context = "";
  c6_info[26].name = "sin";
  c6_info[26].dominantType = "double";
  c6_info[26].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c6_info[26].fileTimeLo = 1343830386U;
  c6_info[26].fileTimeHi = 0U;
  c6_info[26].mFileTimeLo = 0U;
  c6_info[26].mFileTimeHi = 0U;
  c6_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c6_info[27].name = "eml_scalar_sin";
  c6_info[27].dominantType = "double";
  c6_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c6_info[27].fileTimeLo = 1286818736U;
  c6_info[27].fileTimeHi = 0U;
  c6_info[27].mFileTimeLo = 0U;
  c6_info[27].mFileTimeHi = 0U;
  c6_info[28].context = "";
  c6_info[28].name = "cos";
  c6_info[28].dominantType = "double";
  c6_info[28].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c6_info[28].fileTimeLo = 1343830372U;
  c6_info[28].fileTimeHi = 0U;
  c6_info[28].mFileTimeLo = 0U;
  c6_info[28].mFileTimeHi = 0U;
  c6_info[29].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c6_info[29].name = "eml_scalar_cos";
  c6_info[29].dominantType = "double";
  c6_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c6_info[29].fileTimeLo = 1286818722U;
  c6_info[29].fileTimeHi = 0U;
  c6_info[29].mFileTimeLo = 0U;
  c6_info[29].mFileTimeHi = 0U;
}

static real_T c6_mpower(SFc6_HIL_model_errorInstanceStruct *chartInstance,
  real_T c6_a)
{
  real_T c6_b_a;
  real_T c6_c_a;
  real_T c6_ak;
  real_T c6_d_a;
  real_T c6_e_a;
  real_T c6_b;
  c6_b_a = c6_a;
  c6_c_a = c6_b_a;
  c6_eml_scalar_eg(chartInstance);
  c6_ak = c6_c_a;
  c6_d_a = c6_ak;
  c6_eml_scalar_eg(chartInstance);
  c6_e_a = c6_d_a;
  c6_b = c6_d_a;
  return c6_e_a * c6_b;
}

static void c6_eml_scalar_eg(SFc6_HIL_model_errorInstanceStruct *chartInstance)
{
}

static real_T c6_abs(SFc6_HIL_model_errorInstanceStruct *chartInstance, real_T
                     c6_x)
{
  real_T c6_b_x;
  c6_b_x = c6_x;
  return muDoubleScalarAbs(c6_b_x);
}

static void c6_eml_error(SFc6_HIL_model_errorInstanceStruct *chartInstance)
{
  int32_T c6_i17;
  static char_T c6_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c6_u[30];
  const mxArray *c6_y = NULL;
  int32_T c6_i18;
  static char_T c6_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c6_b_u[4];
  const mxArray *c6_b_y = NULL;
  for (c6_i17 = 0; c6_i17 < 30; c6_i17++) {
    c6_u[c6_i17] = c6_cv0[c6_i17];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  for (c6_i18 = 0; c6_i18 < 4; c6_i18++) {
    c6_b_u[c6_i18] = c6_cv1[c6_i18];
  }

  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U, 14,
    c6_y, 14, c6_b_y));
}

static real_T c6_atan2(SFc6_HIL_model_errorInstanceStruct *chartInstance, real_T
  c6_y, real_T c6_x)
{
  real_T c6_b_y;
  real_T c6_b_x;
  c6_eml_scalar_eg(chartInstance);
  c6_b_y = c6_y;
  c6_b_x = c6_x;
  return muDoubleScalarAtan2(c6_b_y, c6_b_x);
}

static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_HIL_model_errorInstanceStruct *chartInstance;
  chartInstance = (SFc6_HIL_model_errorInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static int32_T c6_c_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i19;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i19, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i19;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_HIL_model_errorInstanceStruct *chartInstance;
  chartInstance = (SFc6_HIL_model_errorInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint8_T c6_d_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_HIL_model_error, const char_T
  *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_HIL_model_error), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_HIL_model_error);
  return c6_y;
}

static uint8_T c6_e_emlrt_marshallIn(SFc6_HIL_model_errorInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_HIL_model_errorInstanceStruct
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

void sf_c6_HIL_model_error_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1573056467U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3643127428U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(11765462U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2313913594U);
}

mxArray *sf_c6_HIL_model_error_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("t88tWvHfccsSlIYyLDrSIF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

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
      pr[0] = (double)(2);
      pr[1] = (double)(2);
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
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_HIL_model_error_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c6_HIL_model_error(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[12],T\"WPi_out\",},{M[1],M[22],T\"WPnormal\",},{M[1],M[30],T\"alphaIce_save\",},{M[1],M[23],T\"delta\",},{M[1],M[16],T\"deltaXlos\",},{M[1],M[21],T\"deltaYlos\",},{M[1],M[24],T\"y_mark\",},{M[8],M[0],T\"is_active_c6_HIL_model_error\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_HIL_model_error_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_HIL_model_errorInstanceStruct *chartInstance;
    chartInstance = (SFc6_HIL_model_errorInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_errorMachineNumber_,
           6,
           1,
           1,
           13,
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
          init_script_number_translation(_HIL_model_errorMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HIL_model_errorMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HIL_model_errorMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"WPi");
          _SFD_SET_DATA_PROPS(1,1,1,0,"alphaIce");
          _SFD_SET_DATA_PROPS(2,1,1,0,"WP");
          _SFD_SET_DATA_PROPS(3,2,0,1,"WPi_out");
          _SFD_SET_DATA_PROPS(4,2,0,1,"deltaXlos");
          _SFD_SET_DATA_PROPS(5,1,1,0,"eta");
          _SFD_SET_DATA_PROPS(6,2,0,1,"deltaYlos");
          _SFD_SET_DATA_PROPS(7,2,0,1,"WPnormal");
          _SFD_SET_DATA_PROPS(8,2,0,1,"delta");
          _SFD_SET_DATA_PROPS(9,2,0,1,"y_mark");
          _SFD_SET_DATA_PROPS(10,1,1,0,"icebergData");
          _SFD_SET_DATA_PROPS(11,1,1,0,"saved_alphaIce");
          _SFD_SET_DATA_PROPS(12,2,0,1,"alphaIce_save");
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
        _SFD_CV_INIT_EML(0,1,1,8,0,0,0,0,1,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2621);
        _SFD_CV_INIT_EML_IF(0,1,0,265,280,642,712);
        _SFD_CV_INIT_EML_IF(0,1,1,508,536,-1,641);
        _SFD_CV_INIT_EML_IF(0,1,2,568,582,-1,632);
        _SFD_CV_INIT_EML_IF(0,1,3,738,753,2457,2581);
        _SFD_CV_INIT_EML_IF(0,1,4,779,797,1346,1497);
        _SFD_CV_INIT_EML_IF(0,1,5,1068,1081,-1,1115);
        _SFD_CV_INIT_EML_IF(0,1,6,1379,1392,-1,1426);
        _SFD_CV_INIT_EML_IF(0,1,7,1784,1798,1823,1905);
        _SFD_CV_INIT_EML_WHILE(0,1,0,1125,1144,1251);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);

        {
          real_T *c6_WPi;
          real_T *c6_alphaIce;
          real_T *c6_WPi_out;
          real_T *c6_deltaXlos;
          real_T *c6_deltaYlos;
          real_T *c6_WPnormal;
          real_T *c6_delta;
          real_T *c6_y_mark;
          real_T *c6_saved_alphaIce;
          real_T *c6_alphaIce_save;
          real_T (*c6_WP)[4];
          real_T (*c6_eta)[2];
          real_T (*c6_icebergData)[2];
          c6_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
          c6_saved_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c6_icebergData = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S,
            4);
          c6_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
          c6_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
          c6_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c6_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c6_eta = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
          c6_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c6_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c6_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
          c6_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c6_WPi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c6_WPi);
          _SFD_SET_DATA_VALUE_PTR(1U, c6_alphaIce);
          _SFD_SET_DATA_VALUE_PTR(2U, *c6_WP);
          _SFD_SET_DATA_VALUE_PTR(3U, c6_WPi_out);
          _SFD_SET_DATA_VALUE_PTR(4U, c6_deltaXlos);
          _SFD_SET_DATA_VALUE_PTR(5U, *c6_eta);
          _SFD_SET_DATA_VALUE_PTR(6U, c6_deltaYlos);
          _SFD_SET_DATA_VALUE_PTR(7U, c6_WPnormal);
          _SFD_SET_DATA_VALUE_PTR(8U, c6_delta);
          _SFD_SET_DATA_VALUE_PTR(9U, c6_y_mark);
          _SFD_SET_DATA_VALUE_PTR(10U, *c6_icebergData);
          _SFD_SET_DATA_VALUE_PTR(11U, c6_saved_alphaIce);
          _SFD_SET_DATA_VALUE_PTR(12U, c6_alphaIce_save);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HIL_model_errorMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "vz6u7ezXroZWt3jjRgunP";
}

static void sf_opaque_initialize_c6_HIL_model_error(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_HIL_model_errorInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*)
    chartInstanceVar);
  initialize_c6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c6_HIL_model_error(void *chartInstanceVar)
{
  enable_c6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c6_HIL_model_error(void *chartInstanceVar)
{
  disable_c6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c6_HIL_model_error(void *chartInstanceVar)
{
  sf_c6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c6_HIL_model_error(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c6_HIL_model_error
    ((SFc6_HIL_model_errorInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_HIL_model_error();/* state var info */
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

extern void sf_internal_set_sim_state_c6_HIL_model_error(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_HIL_model_error();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c6_HIL_model_error(SimStruct* S)
{
  return sf_internal_get_sim_state_c6_HIL_model_error(S);
}

static void sf_opaque_set_sim_state_c6_HIL_model_error(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c6_HIL_model_error(S, st);
}

static void sf_opaque_terminate_c6_HIL_model_error(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_HIL_model_errorInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_error_optimization_info();
    }

    finalize_c6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_HIL_model_error(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_HIL_model_error((SFc6_HIL_model_errorInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_HIL_model_error(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_error_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,6,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,6,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,7);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=7; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 6; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2238320611U));
  ssSetChecksum1(S,(2329158339U));
  ssSetChecksum2(S,(3338299818U));
  ssSetChecksum3(S,(4249901072U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_HIL_model_error(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_HIL_model_error(SimStruct *S)
{
  SFc6_HIL_model_errorInstanceStruct *chartInstance;
  chartInstance = (SFc6_HIL_model_errorInstanceStruct *)utMalloc(sizeof
    (SFc6_HIL_model_errorInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_HIL_model_errorInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c6_HIL_model_error;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c6_HIL_model_error;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c6_HIL_model_error;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_HIL_model_error;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_HIL_model_error;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c6_HIL_model_error;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c6_HIL_model_error;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c6_HIL_model_error;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_HIL_model_error;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_HIL_model_error;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c6_HIL_model_error;
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

void c6_HIL_model_error_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_HIL_model_error(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_HIL_model_error(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_HIL_model_error(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_HIL_model_error_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
