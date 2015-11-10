/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Model_justmodel_sfun.h"
#include "c1_Model_justmodel.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Model_justmodel_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[41] = { "Lpp", "n", "Rk", "maxWP", "x",
  "y", "deltaX", "deltaY", "distX", "distY", "fd", "fe", "ff", "fg", "a", "b",
  "c", "fact", "Xlos", "Ylos", "LosPos", "PosOld", "LosOld", "x_mark",
  "WP_angle", "y_star", "nargin", "nargout", "WPi", "alphaIce", "WP", "eta",
  "icebergData", "saved_alphaIce", "WPi_out", "deltaXlos", "deltaYlos",
  "WPnormal", "delta", "y_mark", "alphaIce_save" };

/* Function Declarations */
static void initialize_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance);
static void initialize_params_c1_Model_justmodel
  (SFc1_Model_justmodelInstanceStruct *chartInstance);
static void enable_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance);
static void disable_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_Model_justmodel
  (SFc1_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_Model_justmodel
  (SFc1_Model_justmodelInstanceStruct *chartInstance);
static void set_sim_state_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct *
  chartInstance, const mxArray *c1_st);
static void finalize_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance);
static void sf_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance);
static void c1_chartstep_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance);
static void initSimStructsc1_Model_justmodel(SFc1_Model_justmodelInstanceStruct *
  chartInstance);
static void registerMessagesc1_Model_justmodel
  (SFc1_Model_justmodelInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_alphaIce_save, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[30]);
static real_T c1_mpower(SFc1_Model_justmodelInstanceStruct *chartInstance,
  real_T c1_a);
static void c1_eml_scalar_eg(SFc1_Model_justmodelInstanceStruct *chartInstance);
static real_T c1_abs(SFc1_Model_justmodelInstanceStruct *chartInstance, real_T
                     c1_x);
static void c1_eml_error(SFc1_Model_justmodelInstanceStruct *chartInstance);
static real_T c1_atan2(SFc1_Model_justmodelInstanceStruct *chartInstance, real_T
  c1_y, real_T c1_x);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_c_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_d_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_Model_justmodel, const char_T
  *c1_identifier);
static uint8_T c1_e_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_Model_justmodelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_Model_justmodel = 0U;
}

static void initialize_params_c1_Model_justmodel
  (SFc1_Model_justmodelInstanceStruct *chartInstance)
{
}

static void enable_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_Model_justmodel
  (SFc1_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c1_Model_justmodel
  (SFc1_Model_justmodelInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  real_T c1_f_hoistedGlobal;
  real_T c1_f_u;
  const mxArray *c1_g_y = NULL;
  real_T c1_g_hoistedGlobal;
  real_T c1_g_u;
  const mxArray *c1_h_y = NULL;
  uint8_T c1_h_hoistedGlobal;
  uint8_T c1_h_u;
  const mxArray *c1_i_y = NULL;
  real_T *c1_WPi_out;
  real_T *c1_WPnormal;
  real_T *c1_alphaIce_save;
  real_T *c1_delta;
  real_T *c1_deltaXlos;
  real_T *c1_deltaYlos;
  real_T *c1_y_mark;
  c1_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c1_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c1_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c1_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(8), FALSE);
  c1_hoistedGlobal = *c1_WPi_out;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_WPnormal;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *c1_alphaIce_save;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *c1_delta;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = *c1_deltaXlos;
  c1_e_u = c1_e_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_f_hoistedGlobal = *c1_deltaYlos;
  c1_f_u = c1_f_hoistedGlobal;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_g_hoistedGlobal = *c1_y_mark;
  c1_g_u = c1_g_hoistedGlobal;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_h_hoistedGlobal = chartInstance->c1_is_active_c1_Model_justmodel;
  c1_h_u = c1_h_hoistedGlobal;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct *
  chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_WPi_out;
  real_T *c1_WPnormal;
  real_T *c1_alphaIce_save;
  real_T *c1_delta;
  real_T *c1_deltaXlos;
  real_T *c1_deltaYlos;
  real_T *c1_y_mark;
  c1_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c1_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c1_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c1_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_WPi_out = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 0)), "WPi_out");
  *c1_WPnormal = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 1)), "WPnormal");
  *c1_alphaIce_save = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 2)), "alphaIce_save");
  *c1_delta = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    3)), "delta");
  *c1_deltaXlos = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 4)), "deltaXlos");
  *c1_deltaYlos = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 5)), "deltaYlos");
  *c1_y_mark = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    6)), "y_mark");
  chartInstance->c1_is_active_c1_Model_justmodel = c1_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 7)),
     "is_active_c1_Model_justmodel");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_Model_justmodel(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance)
{
}

static void sf_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c1_i0;
  int32_T c1_i1;
  int32_T c1_i2;
  real_T *c1_WPi;
  real_T *c1_alphaIce;
  real_T *c1_WPi_out;
  real_T *c1_deltaXlos;
  real_T *c1_deltaYlos;
  real_T *c1_WPnormal;
  real_T *c1_delta;
  real_T *c1_y_mark;
  real_T *c1_saved_alphaIce;
  real_T *c1_alphaIce_save;
  real_T (*c1_icebergData)[2];
  real_T (*c1_eta)[2];
  real_T (*c1_WP)[4];
  c1_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c1_saved_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_icebergData = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
  c1_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c1_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c1_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_eta = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
  c1_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c1_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_WPi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c1_WPi, 0U);
  _SFD_DATA_RANGE_CHECK(*c1_alphaIce, 1U);
  for (c1_i0 = 0; c1_i0 < 4; c1_i0++) {
    _SFD_DATA_RANGE_CHECK((*c1_WP)[c1_i0], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_WPi_out, 3U);
  _SFD_DATA_RANGE_CHECK(*c1_deltaXlos, 4U);
  for (c1_i1 = 0; c1_i1 < 2; c1_i1++) {
    _SFD_DATA_RANGE_CHECK((*c1_eta)[c1_i1], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_deltaYlos, 6U);
  _SFD_DATA_RANGE_CHECK(*c1_WPnormal, 7U);
  _SFD_DATA_RANGE_CHECK(*c1_delta, 8U);
  _SFD_DATA_RANGE_CHECK(*c1_y_mark, 9U);
  for (c1_i2 = 0; c1_i2 < 2; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*c1_icebergData)[c1_i2], 10U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_saved_alphaIce, 11U);
  _SFD_DATA_RANGE_CHECK(*c1_alphaIce_save, 12U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_Model_justmodel(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Model_justmodelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_Model_justmodel(SFc1_Model_justmodelInstanceStruct
  *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_WPi;
  real_T c1_alphaIce;
  int32_T c1_i3;
  real_T c1_WP[4];
  int32_T c1_i4;
  real_T c1_eta[2];
  int32_T c1_i5;
  real_T c1_icebergData[2];
  real_T c1_saved_alphaIce;
  uint32_T c1_debug_family_var_map[41];
  real_T c1_Lpp;
  real_T c1_n;
  real_T c1_Rk;
  real_T c1_maxWP;
  real_T c1_x;
  real_T c1_y;
  real_T c1_deltaX;
  real_T c1_deltaY;
  real_T c1_distX;
  real_T c1_distY;
  real_T c1_fd;
  real_T c1_fe;
  real_T c1_ff;
  real_T c1_fg;
  real_T c1_a;
  real_T c1_b;
  real_T c1_c;
  real_T c1_fact;
  real_T c1_Xlos;
  real_T c1_Ylos;
  real_T c1_LosPos;
  real_T c1_PosOld;
  real_T c1_LosOld;
  real_T c1_x_mark;
  real_T c1_WP_angle;
  real_T c1_y_star;
  real_T c1_nargin = 6.0;
  real_T c1_nargout = 7.0;
  real_T c1_WPi_out;
  real_T c1_deltaXlos;
  real_T c1_deltaYlos;
  real_T c1_WPnormal;
  real_T c1_delta;
  real_T c1_y_mark;
  real_T c1_alphaIce_save;
  real_T c1_b_b;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_A;
  real_T c1_B;
  real_T c1_d_x;
  real_T c1_d_y;
  real_T c1_e_x;
  real_T c1_e_y;
  real_T c1_b_a;
  real_T c1_c_b;
  real_T c1_f_y;
  real_T c1_c_a;
  real_T c1_d_b;
  real_T c1_g_y;
  real_T c1_d_a;
  real_T c1_e_b;
  real_T c1_h_y;
  real_T c1_f_b;
  real_T c1_g_b;
  real_T c1_i_y;
  real_T c1_h_b;
  real_T c1_j_y;
  real_T c1_e_a;
  real_T c1_i_b;
  real_T c1_k_y;
  real_T c1_j_b;
  real_T c1_l_y;
  real_T c1_f_a;
  real_T c1_k_b;
  real_T c1_m_y;
  real_T c1_g_a;
  real_T c1_l_b;
  real_T c1_n_y;
  real_T c1_m_b;
  real_T c1_o_y;
  real_T c1_h_a;
  real_T c1_n_b;
  real_T c1_p_y;
  real_T c1_o_b;
  real_T c1_q_y;
  real_T c1_i_a;
  real_T c1_p_b;
  real_T c1_r_y;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_j_a;
  real_T c1_q_b;
  real_T c1_s_y;
  real_T c1_r_b;
  real_T c1_t_y;
  real_T c1_b_A;
  real_T c1_b_B;
  real_T c1_h_x;
  real_T c1_u_y;
  real_T c1_i_x;
  real_T c1_v_y;
  real_T c1_k_a;
  real_T c1_s_b;
  real_T c1_w_y;
  real_T c1_l_a;
  real_T c1_x_y;
  real_T c1_m_a;
  real_T c1_t_b;
  real_T c1_y_y;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_l_x;
  real_T c1_m_x;
  real_T c1_n_x;
  real_T c1_o_x;
  real_T c1_u_b;
  real_T c1_ab_y;
  real_T c1_c_A;
  real_T c1_c_B;
  real_T c1_p_x;
  real_T c1_bb_y;
  real_T c1_q_x;
  real_T c1_cb_y;
  real_T c1_r_x;
  real_T c1_s_x;
  real_T c1_t_x;
  real_T c1_u_x;
  real_T c1_db_y;
  real_T c1_v_x;
  real_T c1_w_x;
  real_T c1_n_a;
  real_T c1_v_b;
  real_T c1_x_x;
  real_T c1_y_x;
  real_T c1_o_a;
  real_T c1_w_b;
  real_T c1_eb_y;
  real_T c1_ab_x;
  real_T c1_bb_x;
  real_T c1_p_a;
  real_T c1_x_b;
  real_T c1_fb_y;
  real_T c1_cb_x;
  real_T c1_db_x;
  real_T c1_q_a;
  real_T c1_y_b;
  real_T c1_gb_y;
  real_T c1_eb_x;
  real_T c1_fb_x;
  real_T c1_r_a;
  real_T c1_ab_b;
  real_T c1_hb_y;
  real_T c1_gb_x;
  real_T c1_hb_x;
  real_T c1_s_a;
  real_T c1_bb_b;
  real_T *c1_b_alphaIce_save;
  real_T *c1_b_y_mark;
  real_T *c1_b_delta;
  real_T *c1_b_WPnormal;
  real_T *c1_b_deltaYlos;
  real_T *c1_b_deltaXlos;
  real_T *c1_b_WPi_out;
  real_T *c1_b_saved_alphaIce;
  real_T *c1_b_alphaIce;
  real_T *c1_b_WPi;
  real_T (*c1_b_icebergData)[2];
  real_T (*c1_b_eta)[2];
  real_T (*c1_b_WP)[4];
  int32_T exitg1;
  c1_b_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c1_b_saved_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_b_icebergData = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
  c1_b_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c1_b_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c1_b_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_b_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_b_eta = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_WPi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_WPi;
  c1_b_hoistedGlobal = *c1_b_alphaIce;
  c1_c_hoistedGlobal = *c1_b_saved_alphaIce;
  c1_WPi = c1_hoistedGlobal;
  c1_alphaIce = c1_b_hoistedGlobal;
  for (c1_i3 = 0; c1_i3 < 4; c1_i3++) {
    c1_WP[c1_i3] = (*c1_b_WP)[c1_i3];
  }

  for (c1_i4 = 0; c1_i4 < 2; c1_i4++) {
    c1_eta[c1_i4] = (*c1_b_eta)[c1_i4];
  }

  for (c1_i5 = 0; c1_i5 < 2; c1_i5++) {
    c1_icebergData[c1_i5] = (*c1_b_icebergData)[c1_i5];
  }

  c1_saved_alphaIce = c1_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 41U, 41U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Lpp, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_n, 1U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Rk, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_maxWP, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_x, 4U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_y, 5U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_deltaX, 6U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_deltaY, 7U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_distX, 8U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_distY, 9U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_fd, 10U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_fe, 11U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ff, 12U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_fg, 13U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_a, 14U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b, 15U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c, 16U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_fact, 17U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Xlos, 18U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Ylos, 19U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_LosPos, 20U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_PosOld, 21U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_LosOld, 22U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_x_mark, 23U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_WP_angle, 24U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_y_star, 25U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 26U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 27U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_WPi, 28U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_alphaIce, 29U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_WP, 30U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_eta, 31U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_icebergData, 32U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_saved_alphaIce, 33U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_WPi_out, 34U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_deltaXlos, 35U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_deltaYlos, 36U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_WPnormal, 37U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_delta, 38U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_y_mark, 39U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_alphaIce_save, 40U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  c1_Lpp = c1_icebergData[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  c1_n = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  c1_b_b = c1_Lpp;
  c1_Rk = 2.0 * c1_b_b;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  c1_b_x = c1_WPi;
  c1_WPi = c1_b_x;
  c1_c_x = c1_WPi;
  c1_WPi = c1_c_x;
  c1_WPi = muDoubleScalarRound(c1_WPi);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  c1_maxWP = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_x = c1_eta[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  c1_y = c1_eta[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  if (CV_EML_IF(0, 1, 0, c1_WPi <= c1_maxWP)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
    c1_deltaX = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP",
      (int32_T)_SFD_INTEGER_CHECK("WPi", c1_WPi), 1, 2, 1, 0) - 1] - c1_WP
      [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi - 1", c1_WPi - 1.0), 1, 2, 1, 0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
    c1_deltaY = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP",
      (int32_T)_SFD_INTEGER_CHECK("WPi", c1_WPi), 1, 2, 1, 0) + 1] - c1_WP
      [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi - 1", c1_WPi - 1.0), 1, 2, 1, 0) + 1];
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
    c1_distX = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi", c1_WPi), 1, 2, 1, 0) - 1] - c1_x;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 20);
    c1_distY = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi", c1_WPi), 1, 2, 1, 0) + 1] - c1_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
    if (CV_EML_IF(0, 1, 1, c1_mpower(chartInstance, c1_distX) + c1_mpower
                  (chartInstance, c1_distY) <= c1_mpower(chartInstance, c1_Rk)))
    {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
      c1_WPi++;
      sf_mex_printf("%s =\\n", "WPi");
      c1_u = c1_WPi;
      c1_b_y = NULL;
      sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
      sf_mex_call_debug("disp", 0U, 1U, 14, c1_b_y);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
      if (CV_EML_IF(0, 1, 2, c1_WPi > c1_maxWP)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
        c1_saved_alphaIce = c1_alphaIce;
        sf_mex_printf("%s =\\n", "saved_alphaIce");
        c1_b_u = c1_saved_alphaIce;
        c1_c_y = NULL;
        sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0),
                      FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c1_c_y);
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 30);
    c1_deltaX = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 31);
    c1_deltaY = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
    c1_distX = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
    c1_distY = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
  if (CV_EML_IF(0, 1, 3, c1_WPi <= c1_maxWP)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 41);
    if (CV_EML_IF(0, 1, 4, c1_abs(chartInstance, c1_deltaX) > 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 43);
      c1_A = c1_deltaY;
      c1_B = c1_deltaX;
      c1_d_x = c1_A;
      c1_d_y = c1_B;
      c1_e_x = c1_d_x;
      c1_e_y = c1_d_y;
      c1_fd = c1_e_x / c1_e_y;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 44);
      c1_fe = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
        _SFD_INTEGER_CHECK("WPi - 1", c1_WPi - 1.0), 1, 2, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 45);
      c1_ff = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
        _SFD_INTEGER_CHECK("WPi - 1", c1_WPi - 1.0), 1, 2, 1, 0) + 1];
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 46);
      c1_b_a = c1_fd;
      c1_c_b = c1_fe;
      c1_f_y = c1_b_a * c1_c_b;
      c1_fg = c1_ff - c1_f_y;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 48);
      c1_a = 1.0 + c1_mpower(chartInstance, c1_fd);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 49);
      c1_c_a = c1_fd;
      c1_d_b = c1_fg;
      c1_g_y = c1_c_a * c1_d_b;
      c1_d_a = c1_fd;
      c1_e_b = c1_y;
      c1_h_y = c1_d_a * c1_e_b;
      c1_f_b = (c1_g_y - c1_h_y) - c1_x;
      c1_b = 2.0 * c1_f_b;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 50);
      c1_g_b = c1_Lpp;
      c1_i_y = 4.0 * c1_g_b;
      c1_h_b = c1_fg;
      c1_j_y = 2.0 * c1_h_b;
      c1_e_a = c1_j_y;
      c1_i_b = c1_y;
      c1_k_y = c1_e_a * c1_i_b;
      c1_c = (((c1_mpower(chartInstance, c1_x) + c1_mpower(chartInstance, c1_y))
               + c1_mpower(chartInstance, c1_fg)) - c1_mpower(chartInstance,
               c1_i_y)) - c1_k_y;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 52);
      c1_fact = -1.0;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 53);
      if (CV_EML_IF(0, 1, 5, c1_deltaX > 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 54);
        c1_fact = 1.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 57);
      do {
        exitg1 = 0;
        c1_j_b = c1_a;
        c1_l_y = 4.0 * c1_j_b;
        c1_f_a = c1_l_y;
        c1_k_b = c1_c;
        c1_m_y = c1_f_a * c1_k_b;
        if (CV_EML_WHILE(0, 1, 0, c1_mpower(chartInstance, c1_b) < c1_m_y)) {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 58);
          c1_n++;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 60);
          c1_g_a = c1_n;
          c1_l_b = c1_Lpp;
          c1_n_y = c1_g_a * c1_l_b;
          c1_m_b = c1_fg;
          c1_o_y = 2.0 * c1_m_b;
          c1_h_a = c1_o_y;
          c1_n_b = c1_y;
          c1_p_y = c1_h_a * c1_n_b;
          c1_c = (((c1_mpower(chartInstance, c1_x) + c1_mpower(chartInstance,
                     c1_y)) + c1_mpower(chartInstance, c1_fg)) - c1_mpower
                  (chartInstance, c1_n_y)) - c1_p_y;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 57);
          _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 63);
      c1_o_b = c1_a;
      c1_q_y = 4.0 * c1_o_b;
      c1_i_a = c1_q_y;
      c1_p_b = c1_c;
      c1_r_y = c1_i_a * c1_p_b;
      c1_f_x = c1_mpower(chartInstance, c1_b) - c1_r_y;
      c1_g_x = c1_f_x;
      if (c1_g_x < 0.0) {
        c1_eml_error(chartInstance);
      }

      c1_g_x = muDoubleScalarSqrt(c1_g_x);
      c1_j_a = c1_fact;
      c1_q_b = c1_g_x;
      c1_s_y = c1_j_a * c1_q_b;
      c1_r_b = c1_a;
      c1_t_y = 2.0 * c1_r_b;
      c1_b_A = -c1_b + c1_s_y;
      c1_b_B = c1_t_y;
      c1_h_x = c1_b_A;
      c1_u_y = c1_b_B;
      c1_i_x = c1_h_x;
      c1_v_y = c1_u_y;
      c1_Xlos = c1_i_x / c1_v_y;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 64);
      c1_k_a = c1_fd;
      c1_s_b = c1_Xlos - c1_fe;
      c1_w_y = c1_k_a * c1_s_b;
      c1_Ylos = c1_w_y + c1_ff;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 68);
      c1_fact = -1.0;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 69);
      if (CV_EML_IF(0, 1, 6, c1_deltaY > 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 70);
        c1_fact = 1.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 73);
      c1_Xlos = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP",
        (int32_T)_SFD_INTEGER_CHECK("WPi - 1", c1_WPi - 1.0), 1, 2, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 74);
      c1_l_a = c1_fact;
      c1_x_y = c1_l_a * 4.0;
      c1_m_a = c1_x_y;
      c1_t_b = c1_Lpp;
      c1_y_y = c1_m_a * c1_t_b;
      c1_Ylos = c1_y + c1_y_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 79);
    c1_deltaXlos = c1_Xlos - c1_x;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 80);
    c1_deltaYlos = c1_Ylos - c1_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 83);
    c1_j_x = c1_mpower(chartInstance, c1_Xlos - c1_x) + c1_mpower(chartInstance,
      c1_Ylos - c1_y);
    c1_LosPos = c1_j_x;
    if (c1_LosPos < 0.0) {
      c1_eml_error(chartInstance);
    }

    c1_k_x = c1_LosPos;
    c1_LosPos = c1_k_x;
    c1_LosPos = muDoubleScalarSqrt(c1_LosPos);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 84);
    c1_l_x = c1_mpower(chartInstance, c1_x - c1_WP[(int32_T)(real_T)
                       _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi-1", c1_WPi - 1.0), 1, 2, 1, 0) - 1]) + c1_mpower
      (chartInstance, c1_y - c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
        "WP", (int32_T)_SFD_INTEGER_CHECK("WPi-1", c1_WPi - 1.0), 1, 2, 1, 0) +
       1]);
    c1_PosOld = c1_l_x;
    if (c1_PosOld < 0.0) {
      c1_eml_error(chartInstance);
    }

    c1_m_x = c1_PosOld;
    c1_PosOld = c1_m_x;
    c1_PosOld = muDoubleScalarSqrt(c1_PosOld);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 85);
    c1_n_x = c1_mpower(chartInstance, c1_Xlos - c1_WP[(int32_T)(real_T)
                       _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi-1", c1_WPi - 1.0), 1, 2, 1, 0) - 1]) + c1_mpower
      (chartInstance, c1_Ylos - c1_WP[(int32_T)(real_T)
       _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi-1",
         c1_WPi - 1.0), 1, 2, 1, 0) + 1]);
    c1_LosOld = c1_n_x;
    if (c1_LosOld < 0.0) {
      c1_eml_error(chartInstance);
    }

    c1_o_x = c1_LosOld;
    c1_LosOld = c1_o_x;
    c1_LosOld = muDoubleScalarSqrt(c1_LosOld);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 87);
    if (CV_EML_IF(0, 1, 7, c1_LosOld == 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 88);
      c1_x_mark = 0.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 90);
      c1_u_b = c1_LosOld;
      c1_ab_y = 2.0 * c1_u_b;
      c1_c_A = (c1_mpower(chartInstance, c1_PosOld) + c1_mpower(chartInstance,
                 c1_LosOld)) - c1_mpower(chartInstance, c1_LosPos);
      c1_c_B = c1_ab_y;
      c1_p_x = c1_c_A;
      c1_bb_y = c1_c_B;
      c1_q_x = c1_p_x;
      c1_cb_y = c1_bb_y;
      c1_x_mark = c1_q_x / c1_cb_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 92);
    c1_r_x = c1_mpower(chartInstance, c1_PosOld) - c1_mpower(chartInstance,
      c1_x_mark);
    c1_s_x = c1_r_x;
    c1_s_x = muDoubleScalarSign(c1_s_x);
    c1_t_x = c1_mpower(chartInstance, c1_PosOld) - c1_mpower(chartInstance,
      c1_x_mark);
    c1_u_x = c1_t_x;
    c1_db_y = muDoubleScalarAbs(c1_u_x);
    c1_v_x = c1_db_y;
    c1_w_x = c1_v_x;
    if (c1_w_x < 0.0) {
      c1_eml_error(chartInstance);
    }

    c1_w_x = muDoubleScalarSqrt(c1_w_x);
    c1_n_a = c1_s_x;
    c1_v_b = c1_w_x;
    c1_y_mark = c1_n_a * c1_v_b;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 97);
    c1_WP_angle = c1_atan2(chartInstance, c1_deltaY, c1_deltaX);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 98);
    c1_x_x = c1_WP_angle;
    c1_y_x = c1_x_x;
    c1_y_x = muDoubleScalarSin(c1_y_x);
    c1_o_a = -c1_x;
    c1_w_b = c1_y_x;
    c1_eb_y = c1_o_a * c1_w_b;
    c1_ab_x = c1_WP_angle;
    c1_bb_x = c1_ab_x;
    c1_bb_x = muDoubleScalarCos(c1_bb_x);
    c1_p_a = c1_y;
    c1_x_b = c1_bb_x;
    c1_fb_y = c1_p_a * c1_x_b;
    c1_cb_x = c1_WP_angle;
    c1_db_x = c1_cb_x;
    c1_db_x = muDoubleScalarSin(c1_db_x);
    c1_q_a = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi-1", c1_WPi - 1.0), 1, 2, 1, 0) - 1];
    c1_y_b = c1_db_x;
    c1_gb_y = c1_q_a * c1_y_b;
    c1_eb_x = c1_WP_angle;
    c1_fb_x = c1_eb_x;
    c1_fb_x = muDoubleScalarCos(c1_fb_x);
    c1_r_a = c1_WP[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)
      _SFD_INTEGER_CHECK("WPi-1", c1_WPi - 1.0), 1, 2, 1, 0) + 1];
    c1_ab_b = c1_fb_x;
    c1_hb_y = c1_r_a * c1_ab_b;
    c1_y_star = ((c1_eb_y + c1_fb_y) + c1_gb_y) - c1_hb_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 100);
    c1_gb_x = c1_y_star;
    c1_hb_x = c1_gb_x;
    c1_hb_x = muDoubleScalarSign(c1_hb_x);
    c1_s_a = -c1_hb_x;
    c1_bb_b = c1_y_mark;
    c1_y_mark = c1_s_a * c1_bb_b;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 104);
    c1_delta = c1_LosOld - c1_x_mark;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 106);
    c1_WPnormal = c1_atan2(chartInstance, c1_WP[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi",
      c1_WPi), 1, 2, 1, 0) + 1] - c1_WP[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi-1",
      c1_WPi - 1.0), 1, 2, 1, 0) + 1], c1_WP[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi",
      c1_WPi), 1, 2, 1, 0) - 1] - c1_WP[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("WP", (int32_T)_SFD_INTEGER_CHECK("WPi-1",
      c1_WPi - 1.0), 1, 2, 1, 0) - 1]) + 1.5707963267948966;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 110);
    c1_WPi_out = c1_WPi;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 114);
    c1_WPi_out = c1_WPi;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 115);
    c1_deltaXlos = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 116);
    c1_deltaYlos = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 117);
    c1_WPnormal = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 118);
    c1_delta = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 119);
    c1_y_mark = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 123);
  c1_alphaIce_save = c1_saved_alphaIce;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -123);
  _SFD_SYMBOL_SCOPE_POP();
  *c1_b_WPi_out = c1_WPi_out;
  *c1_b_deltaXlos = c1_deltaXlos;
  *c1_b_deltaYlos = c1_deltaYlos;
  *c1_b_WPnormal = c1_WPnormal;
  *c1_b_delta = c1_delta;
  *c1_b_y_mark = c1_y_mark;
  *c1_b_alphaIce_save = c1_alphaIce_save;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_Model_justmodel(SFc1_Model_justmodelInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc1_Model_justmodel
  (SFc1_Model_justmodelInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_alphaIce_save, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_alphaIce_save),
    &c1_thisId);
  sf_mex_destroy(&c1_alphaIce_save);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_alphaIce_save;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c1_alphaIce_save = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_alphaIce_save),
    &c1_thisId);
  sf_mex_destroy(&c1_alphaIce_save);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i6;
  real_T c1_b_inData[2];
  int32_T c1_i7;
  real_T c1_u[2];
  const mxArray *c1_y = NULL;
  SFc1_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i6 = 0; c1_i6 < 2; c1_i6++) {
    c1_b_inData[c1_i6] = (*(real_T (*)[2])c1_inData)[c1_i6];
  }

  for (c1_i7 = 0; c1_i7 < 2; c1_i7++) {
    c1_u[c1_i7] = c1_b_inData[c1_i7];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 2, 1), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i8;
  real_T c1_b_inData[2];
  int32_T c1_i9;
  real_T c1_u[2];
  const mxArray *c1_y = NULL;
  SFc1_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i8 = 0; c1_i8 < 2; c1_i8++) {
    c1_b_inData[c1_i8] = (*(real_T (*)[2])c1_inData)[c1_i8];
  }

  for (c1_i9 = 0; c1_i9 < 2; c1_i9++) {
    c1_u[c1_i9] = c1_b_inData[c1_i9];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i10;
  int32_T c1_i11;
  int32_T c1_i12;
  real_T c1_b_inData[4];
  int32_T c1_i13;
  int32_T c1_i14;
  int32_T c1_i15;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i10 = 0;
  for (c1_i11 = 0; c1_i11 < 2; c1_i11++) {
    for (c1_i12 = 0; c1_i12 < 2; c1_i12++) {
      c1_b_inData[c1_i12 + c1_i10] = (*(real_T (*)[4])c1_inData)[c1_i12 + c1_i10];
    }

    c1_i10 += 2;
  }

  c1_i13 = 0;
  for (c1_i14 = 0; c1_i14 < 2; c1_i14++) {
    for (c1_i15 = 0; c1_i15 < 2; c1_i15++) {
      c1_u[c1_i15 + c1_i13] = c1_b_inData[c1_i15 + c1_i13];
    }

    c1_i13 += 2;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

const mxArray *sf_c1_Model_justmodel_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[30];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i16;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 30), FALSE);
  for (c1_i16 = 0; c1_i16 < 30; c1_i16++) {
    c1_r0 = &c1_info[c1_i16];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i16);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i16);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i16);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i16);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i16);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i16);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i16);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i16);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[30])
{
  c1_info[0].context = "";
  c1_info[0].name = "mtimes";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[0].fileTimeLo = 1289519692U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context = "";
  c1_info[1].name = "round";
  c1_info[1].dominantType = "double";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m";
  c1_info[1].fileTimeLo = 1343830384U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m";
  c1_info[2].name = "eml_scalar_round";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m";
  c1_info[2].fileTimeLo = 1307651238U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context = "";
  c1_info[3].name = "mpower";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[3].fileTimeLo = 1286818842U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[4].name = "power";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[4].fileTimeLo = 1348191930U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[5].name = "eml_scalar_eg";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[5].fileTimeLo = 1286818796U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[6].name = "eml_scalexp_alloc";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[6].fileTimeLo = 1352424860U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[7].name = "floor";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[7].fileTimeLo = 1343830380U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[8].name = "eml_scalar_floor";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[8].fileTimeLo = 1286818726U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c1_info[9].name = "eml_scalar_eg";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[9].fileTimeLo = 1286818796U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c1_info[10].name = "mtimes";
  c1_info[10].dominantType = "double";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[10].fileTimeLo = 1289519692U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context = "";
  c1_info[11].name = "abs";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[11].fileTimeLo = 1343830366U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[12].name = "eml_scalar_abs";
  c1_info[12].dominantType = "double";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[12].fileTimeLo = 1286818712U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context = "";
  c1_info[13].name = "mrdivide";
  c1_info[13].dominantType = "double";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[13].fileTimeLo = 1357951548U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 1319729966U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[14].name = "rdivide";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[14].fileTimeLo = 1346510388U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[15].name = "eml_scalexp_compatible";
  c1_info[15].dominantType = "double";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c1_info[15].fileTimeLo = 1286818796U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[16].name = "eml_div";
  c1_info[16].dominantType = "double";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[16].fileTimeLo = 1313347810U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context = "";
  c1_info[17].name = "sqrt";
  c1_info[17].dominantType = "double";
  c1_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[17].fileTimeLo = 1343830386U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[18].name = "eml_error";
  c1_info[18].dominantType = "char";
  c1_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[18].fileTimeLo = 1343830358U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[19].name = "eml_scalar_sqrt";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c1_info[19].fileTimeLo = 1286818738U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context = "";
  c1_info[20].name = "sign";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[20].fileTimeLo = 1354368064U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[21].name = "eml_scalar_sign";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sign.m";
  c1_info[21].fileTimeLo = 1354368064U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context = "";
  c1_info[22].name = "atan2";
  c1_info[22].dominantType = "double";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c1_info[22].fileTimeLo = 1343830372U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c1_info[23].name = "eml_scalar_eg";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[23].fileTimeLo = 1286818796U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c1_info[24].name = "eml_scalexp_alloc";
  c1_info[24].dominantType = "double";
  c1_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[24].fileTimeLo = 1352424860U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c1_info[25].name = "eml_scalar_atan2";
  c1_info[25].dominantType = "double";
  c1_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m";
  c1_info[25].fileTimeLo = 1286818720U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context = "";
  c1_info[26].name = "sin";
  c1_info[26].dominantType = "double";
  c1_info[26].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c1_info[26].fileTimeLo = 1343830386U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
  c1_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c1_info[27].name = "eml_scalar_sin";
  c1_info[27].dominantType = "double";
  c1_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c1_info[27].fileTimeLo = 1286818736U;
  c1_info[27].fileTimeHi = 0U;
  c1_info[27].mFileTimeLo = 0U;
  c1_info[27].mFileTimeHi = 0U;
  c1_info[28].context = "";
  c1_info[28].name = "cos";
  c1_info[28].dominantType = "double";
  c1_info[28].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c1_info[28].fileTimeLo = 1343830372U;
  c1_info[28].fileTimeHi = 0U;
  c1_info[28].mFileTimeLo = 0U;
  c1_info[28].mFileTimeHi = 0U;
  c1_info[29].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c1_info[29].name = "eml_scalar_cos";
  c1_info[29].dominantType = "double";
  c1_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c1_info[29].fileTimeLo = 1286818722U;
  c1_info[29].fileTimeHi = 0U;
  c1_info[29].mFileTimeLo = 0U;
  c1_info[29].mFileTimeHi = 0U;
}

static real_T c1_mpower(SFc1_Model_justmodelInstanceStruct *chartInstance,
  real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_ak;
  real_T c1_d_a;
  real_T c1_e_a;
  real_T c1_b;
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_c_a;
  c1_d_a = c1_ak;
  c1_eml_scalar_eg(chartInstance);
  c1_e_a = c1_d_a;
  c1_b = c1_d_a;
  return c1_e_a * c1_b;
}

static void c1_eml_scalar_eg(SFc1_Model_justmodelInstanceStruct *chartInstance)
{
}

static real_T c1_abs(SFc1_Model_justmodelInstanceStruct *chartInstance, real_T
                     c1_x)
{
  real_T c1_b_x;
  c1_b_x = c1_x;
  return muDoubleScalarAbs(c1_b_x);
}

static void c1_eml_error(SFc1_Model_justmodelInstanceStruct *chartInstance)
{
  int32_T c1_i17;
  static char_T c1_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c1_u[30];
  const mxArray *c1_y = NULL;
  int32_T c1_i18;
  static char_T c1_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c1_b_u[4];
  const mxArray *c1_b_y = NULL;
  for (c1_i17 = 0; c1_i17 < 30; c1_i17++) {
    c1_u[c1_i17] = c1_cv0[c1_i17];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  for (c1_i18 = 0; c1_i18 < 4; c1_i18++) {
    c1_b_u[c1_i18] = c1_cv1[c1_i18];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U, 14,
    c1_y, 14, c1_b_y));
}

static real_T c1_atan2(SFc1_Model_justmodelInstanceStruct *chartInstance, real_T
  c1_y, real_T c1_x)
{
  real_T c1_b_y;
  real_T c1_b_x;
  c1_eml_scalar_eg(chartInstance);
  c1_b_y = c1_y;
  c1_b_x = c1_x;
  return muDoubleScalarAtan2(c1_b_y, c1_b_x);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_c_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i19;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i19, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i19;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_d_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_Model_justmodel, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_Model_justmodel), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_Model_justmodel);
  return c1_y;
}

static uint8_T c1_e_emlrt_marshallIn(SFc1_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_Model_justmodelInstanceStruct
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

void sf_c1_Model_justmodel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1573056467U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3643127428U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(11765462U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2313913594U);
}

mxArray *sf_c1_Model_justmodel_get_autoinheritance_info(void)
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

mxArray *sf_c1_Model_justmodel_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c1_Model_justmodel(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[12],T\"WPi_out\",},{M[1],M[22],T\"WPnormal\",},{M[1],M[30],T\"alphaIce_save\",},{M[1],M[23],T\"delta\",},{M[1],M[16],T\"deltaXlos\",},{M[1],M[21],T\"deltaYlos\",},{M[1],M[24],T\"y_mark\",},{M[8],M[0],T\"is_active_c1_Model_justmodel\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_Model_justmodel_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_Model_justmodelInstanceStruct *chartInstance;
    chartInstance = (SFc1_Model_justmodelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Model_justmodelMachineNumber_,
           1,
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
          init_script_number_translation(_Model_justmodelMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_Model_justmodelMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Model_justmodelMachineNumber_,
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
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          real_T *c1_WPi;
          real_T *c1_alphaIce;
          real_T *c1_WPi_out;
          real_T *c1_deltaXlos;
          real_T *c1_deltaYlos;
          real_T *c1_WPnormal;
          real_T *c1_delta;
          real_T *c1_y_mark;
          real_T *c1_saved_alphaIce;
          real_T *c1_alphaIce_save;
          real_T (*c1_WP)[4];
          real_T (*c1_eta)[2];
          real_T (*c1_icebergData)[2];
          c1_alphaIce_save = (real_T *)ssGetOutputPortSignal(chartInstance->S, 7);
          c1_saved_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c1_icebergData = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S,
            4);
          c1_y_mark = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
          c1_delta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
          c1_WPnormal = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c1_deltaYlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c1_eta = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
          c1_deltaXlos = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_WPi_out = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
          c1_alphaIce = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_WPi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_WPi);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_alphaIce);
          _SFD_SET_DATA_VALUE_PTR(2U, *c1_WP);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_WPi_out);
          _SFD_SET_DATA_VALUE_PTR(4U, c1_deltaXlos);
          _SFD_SET_DATA_VALUE_PTR(5U, *c1_eta);
          _SFD_SET_DATA_VALUE_PTR(6U, c1_deltaYlos);
          _SFD_SET_DATA_VALUE_PTR(7U, c1_WPnormal);
          _SFD_SET_DATA_VALUE_PTR(8U, c1_delta);
          _SFD_SET_DATA_VALUE_PTR(9U, c1_y_mark);
          _SFD_SET_DATA_VALUE_PTR(10U, *c1_icebergData);
          _SFD_SET_DATA_VALUE_PTR(11U, c1_saved_alphaIce);
          _SFD_SET_DATA_VALUE_PTR(12U, c1_alphaIce_save);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Model_justmodelMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "vz6u7ezXroZWt3jjRgunP";
}

static void sf_opaque_initialize_c1_Model_justmodel(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_Model_justmodelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*)
    chartInstanceVar);
  initialize_c1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_Model_justmodel(void *chartInstanceVar)
{
  enable_c1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_Model_justmodel(void *chartInstanceVar)
{
  disable_c1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_Model_justmodel(void *chartInstanceVar)
{
  sf_c1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_Model_justmodel(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_Model_justmodel
    ((SFc1_Model_justmodelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_Model_justmodel();/* state var info */
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

extern void sf_internal_set_sim_state_c1_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_Model_justmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_Model_justmodel(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_Model_justmodel(S);
}

static void sf_opaque_set_sim_state_c1_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c1_Model_justmodel(S, st);
}

static void sf_opaque_terminate_c1_Model_justmodel(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_Model_justmodelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Model_justmodel_optimization_info();
    }

    finalize_c1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_Model_justmodel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_Model_justmodel((SFc1_Model_justmodelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Model_justmodel_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,7);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
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

static void mdlRTW_c1_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_Model_justmodel(SimStruct *S)
{
  SFc1_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Model_justmodelInstanceStruct *)utMalloc(sizeof
    (SFc1_Model_justmodelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_Model_justmodelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_Model_justmodel;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_Model_justmodel;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_Model_justmodel;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_Model_justmodel;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_Model_justmodel;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_Model_justmodel;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_Model_justmodel;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_Model_justmodel;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_Model_justmodel;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_Model_justmodel;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_Model_justmodel;
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

void c1_Model_justmodel_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_Model_justmodel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_Model_justmodel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_Model_justmodel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_Model_justmodel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
