/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_experiments2_sfun.h"
#include "c1_HIL_model_experiments2.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HIL_model_experiments2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[12] = { "num", "nargin", "nargout",
  "err_percent", "eta_s_in", "eta_i_in", "error_previous", "eta_s_previous",
  "eta_i_previous", "error", "eta_s", "eta_i" };

/* Function Declarations */
static void initialize_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void initialize_params_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void enable_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void disable_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void set_sim_state_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance, const mxArray
   *c1_st);
static void finalize_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void sf_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void initSimStructsc1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void registerMessagesc1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_eta_i, const char_T *c1_identifier, real_T
  c1_y[2]);
static void c1_b_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[2]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_eta_s, const char_T *c1_identifier, real_T
  c1_y[3]);
static void c1_d_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_e_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_error, const char_T *c1_identifier);
static real_T c1_f_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[27]);
static real_T c1_rand(SFc1_HIL_model_experiments2InstanceStruct *chartInstance);
static void c1_eml_rand_mt19937ar(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, uint32_T c1_d_state[625]);
static void c1_twister_state_vector(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, uint32_T c1_mt[625], real_T c1_seed, uint32_T c1_b_mt[625]);
static void c1_b_eml_rand_mt19937ar(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, uint32_T c1_d_state[625], uint32_T c1_e_state[625], real_T
  *c1_r);
static void c1_eml_error(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_g_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint32_T c1_h_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c1_b_method, const char_T *c1_identifier);
static uint32_T c1_i_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static uint32_T c1_j_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c1_d_state, const char_T *c1_identifier);
static uint32_T c1_k_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_l_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_d_state, const char_T *c1_identifier,
  uint32_T c1_y[625]);
static void c1_m_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  uint32_T c1_y[625]);
static void c1_n_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_d_state, const char_T *c1_identifier,
  uint32_T c1_y[2]);
static void c1_o_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  uint32_T c1_y[2]);
static uint8_T c1_p_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_HIL_model_experiments2, const
  char_T *c1_identifier);
static uint8_T c1_q_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_twister_state_vector(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, uint32_T c1_mt[625], real_T c1_seed);
static real_T c1_c_eml_rand_mt19937ar(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, uint32_T c1_d_state[625]);
static void init_dsm_address_info(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_method_not_empty = FALSE;
  chartInstance->c1_state_not_empty = FALSE;
  chartInstance->c1_b_state_not_empty = FALSE;
  chartInstance->c1_c_state_not_empty = FALSE;
  chartInstance->c1_is_active_c1_HIL_model_experiments2 = 0U;
}

static void initialize_params_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void enable_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  int32_T c1_i0;
  real_T c1_b_u[2];
  const mxArray *c1_c_y = NULL;
  int32_T c1_i1;
  real_T c1_c_u[3];
  const mxArray *c1_d_y = NULL;
  uint32_T c1_b_hoistedGlobal;
  uint32_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  uint32_T c1_c_hoistedGlobal;
  uint32_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  int32_T c1_i2;
  uint32_T c1_f_u[625];
  const mxArray *c1_g_y = NULL;
  int32_T c1_i3;
  uint32_T c1_g_u[2];
  const mxArray *c1_h_y = NULL;
  uint8_T c1_d_hoistedGlobal;
  uint8_T c1_h_u;
  const mxArray *c1_i_y = NULL;
  real_T *c1_error;
  real_T (*c1_eta_s)[3];
  real_T (*c1_eta_i)[2];
  c1_eta_i = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_eta_s = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(8), FALSE);
  c1_hoistedGlobal = *c1_error;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  for (c1_i0 = 0; c1_i0 < 2; c1_i0++) {
    c1_b_u[c1_i0] = (*c1_eta_i)[c1_i0];
  }

  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
    c1_c_u[c1_i1] = (*c1_eta_s)[c1_i1];
  }

  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_b_hoistedGlobal = chartInstance->c1_method;
  c1_d_u = c1_b_hoistedGlobal;
  c1_e_y = NULL;
  if (!chartInstance->c1_method_not_empty) {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 7, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_c_hoistedGlobal = chartInstance->c1_state;
  c1_e_u = c1_c_hoistedGlobal;
  c1_f_y = NULL;
  if (!chartInstance->c1_state_not_empty) {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 7, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 4, c1_f_y);
  for (c1_i2 = 0; c1_i2 < 625; c1_i2++) {
    c1_f_u[c1_i2] = chartInstance->c1_c_state[c1_i2];
  }

  c1_g_y = NULL;
  if (!chartInstance->c1_c_state_not_empty) {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_f_u, 7, 0U, 1U, 0U, 1, 625),
                  FALSE);
  }

  sf_mex_setcell(c1_y, 5, c1_g_y);
  for (c1_i3 = 0; c1_i3 < 2; c1_i3++) {
    c1_g_u[c1_i3] = chartInstance->c1_b_state[c1_i3];
  }

  c1_h_y = NULL;
  if (!chartInstance->c1_b_state_not_empty) {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", c1_g_u, 7, 0U, 1U, 0U, 1, 2),
                  FALSE);
  }

  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_d_hoistedGlobal = chartInstance->c1_is_active_c1_HIL_model_experiments2;
  c1_h_u = c1_d_hoistedGlobal;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance, const mxArray
   *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[2];
  int32_T c1_i4;
  real_T c1_dv1[3];
  int32_T c1_i5;
  uint32_T c1_uv0[625];
  int32_T c1_i6;
  uint32_T c1_uv1[2];
  int32_T c1_i7;
  real_T *c1_error;
  real_T (*c1_eta_i)[2];
  real_T (*c1_eta_s)[3];
  c1_eta_i = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_eta_s = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_error = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 0)), "error");
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
                      "eta_i", c1_dv0);
  for (c1_i4 = 0; c1_i4 < 2; c1_i4++) {
    (*c1_eta_i)[c1_i4] = c1_dv0[c1_i4];
  }

  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)),
                        "eta_s", c1_dv1);
  for (c1_i5 = 0; c1_i5 < 3; c1_i5++) {
    (*c1_eta_s)[c1_i5] = c1_dv1[c1_i5];
  }

  chartInstance->c1_method = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 3)), "method");
  chartInstance->c1_state = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 4)), "state");
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 5)),
                        "state", c1_uv0);
  for (c1_i6 = 0; c1_i6 < 625; c1_i6++) {
    chartInstance->c1_c_state[c1_i6] = c1_uv0[c1_i6];
  }

  c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 6)),
                        "state", c1_uv1);
  for (c1_i7 = 0; c1_i7 < 2; c1_i7++) {
    chartInstance->c1_b_state[c1_i7] = c1_uv1[c1_i7];
  }

  chartInstance->c1_is_active_c1_HIL_model_experiments2 = c1_p_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 7)),
     "is_active_c1_HIL_model_experiments2");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_HIL_model_experiments2(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void sf_c1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
  int32_T c1_i8;
  int32_T c1_i9;
  int32_T c1_i10;
  int32_T c1_i11;
  int32_T c1_i12;
  int32_T c1_i13;
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_err_percent;
  int32_T c1_i14;
  real_T c1_eta_s_in[3];
  int32_T c1_i15;
  real_T c1_eta_i_in[2];
  real_T c1_error_previous;
  int32_T c1_i16;
  real_T c1_eta_s_previous[3];
  int32_T c1_i17;
  real_T c1_eta_i_previous[2];
  uint32_T c1_debug_family_var_map[12];
  real_T c1_num;
  real_T c1_nargin = 6.0;
  real_T c1_nargout = 3.0;
  real_T c1_error;
  real_T c1_eta_s[3];
  real_T c1_eta_i[2];
  real_T c1_b;
  int32_T c1_i18;
  int32_T c1_i19;
  int32_T c1_i20;
  int32_T c1_i21;
  int32_T c1_i22;
  int32_T c1_i23;
  real_T *c1_b_error;
  real_T *c1_b_err_percent;
  real_T *c1_b_error_previous;
  real_T (*c1_b_eta_s)[3];
  real_T (*c1_b_eta_i)[2];
  real_T (*c1_b_eta_i_previous)[2];
  real_T (*c1_b_eta_s_previous)[3];
  real_T (*c1_b_eta_i_in)[2];
  real_T (*c1_b_eta_s_in)[3];
  c1_b_eta_i = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_b_eta_i_previous = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
  c1_b_eta_s_previous = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c1_b_error_previous = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_eta_i_in = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_eta_s_in = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_eta_s = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_err_percent = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c1_b_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c1_b_error, 0U);
  _SFD_DATA_RANGE_CHECK(*c1_b_err_percent, 1U);
  for (c1_i8 = 0; c1_i8 < 3; c1_i8++) {
    _SFD_DATA_RANGE_CHECK((*c1_b_eta_s)[c1_i8], 2U);
  }

  for (c1_i9 = 0; c1_i9 < 3; c1_i9++) {
    _SFD_DATA_RANGE_CHECK((*c1_b_eta_s_in)[c1_i9], 3U);
  }

  for (c1_i10 = 0; c1_i10 < 2; c1_i10++) {
    _SFD_DATA_RANGE_CHECK((*c1_b_eta_i_in)[c1_i10], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_b_error_previous, 5U);
  for (c1_i11 = 0; c1_i11 < 3; c1_i11++) {
    _SFD_DATA_RANGE_CHECK((*c1_b_eta_s_previous)[c1_i11], 6U);
  }

  for (c1_i12 = 0; c1_i12 < 2; c1_i12++) {
    _SFD_DATA_RANGE_CHECK((*c1_b_eta_i_previous)[c1_i12], 7U);
  }

  for (c1_i13 = 0; c1_i13 < 2; c1_i13++) {
    _SFD_DATA_RANGE_CHECK((*c1_b_eta_i)[c1_i13], 8U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_err_percent;
  c1_b_hoistedGlobal = *c1_b_error_previous;
  c1_err_percent = c1_hoistedGlobal;
  for (c1_i14 = 0; c1_i14 < 3; c1_i14++) {
    c1_eta_s_in[c1_i14] = (*c1_b_eta_s_in)[c1_i14];
  }

  for (c1_i15 = 0; c1_i15 < 2; c1_i15++) {
    c1_eta_i_in[c1_i15] = (*c1_b_eta_i_in)[c1_i15];
  }

  c1_error_previous = c1_b_hoistedGlobal;
  for (c1_i16 = 0; c1_i16 < 3; c1_i16++) {
    c1_eta_s_previous[c1_i16] = (*c1_b_eta_s_previous)[c1_i16];
  }

  for (c1_i17 = 0; c1_i17 < 2; c1_i17++) {
    c1_eta_i_previous[c1_i17] = (*c1_b_eta_i_previous)[c1_i17];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_num, 0U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 1U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 2U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_err_percent, 3U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_eta_s_in, 4U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_eta_i_in, 5U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_error_previous, 6U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_eta_s_previous, 7U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_eta_i_previous, 8U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_error, 9U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_eta_s, 10U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_eta_i, 11U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  c1_b = c1_rand(chartInstance);
  c1_num = 100.0 * c1_b;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  if (CV_EML_IF(0, 1, 0, c1_error_previous == 1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
    c1_err_percent = 95.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  if (CV_EML_IF(0, 1, 1, c1_num < c1_err_percent)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
    c1_error = 1.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
    for (c1_i18 = 0; c1_i18 < 3; c1_i18++) {
      c1_eta_s[c1_i18] = c1_eta_s_previous[c1_i18];
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
    for (c1_i19 = 0; c1_i19 < 2; c1_i19++) {
      c1_eta_i[c1_i19] = c1_eta_i_previous[c1_i19];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
    c1_error = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
    for (c1_i20 = 0; c1_i20 < 3; c1_i20++) {
      c1_eta_s[c1_i20] = c1_eta_s_in[c1_i20];
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 20);
    for (c1_i21 = 0; c1_i21 < 2; c1_i21++) {
      c1_eta_i[c1_i21] = c1_eta_i_in[c1_i21];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -20);
  _SFD_SYMBOL_SCOPE_POP();
  *c1_b_error = c1_error;
  for (c1_i22 = 0; c1_i22 < 3; c1_i22++) {
    (*c1_b_eta_s)[c1_i22] = c1_eta_s[c1_i22];
  }

  for (c1_i23 = 0; c1_i23 < 2; c1_i23++) {
    (*c1_b_eta_i)[c1_i23] = c1_eta_i[c1_i23];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_experiments2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void registerMessagesc1_HIL_model_experiments2
  (SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i24;
  real_T c1_b_inData[2];
  int32_T c1_i25;
  real_T c1_u[2];
  const mxArray *c1_y = NULL;
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i24 = 0; c1_i24 < 2; c1_i24++) {
    c1_b_inData[c1_i24] = (*(real_T (*)[2])c1_inData)[c1_i24];
  }

  for (c1_i25 = 0; c1_i25 < 2; c1_i25++) {
    c1_u[c1_i25] = c1_b_inData[c1_i25];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_eta_i, const char_T *c1_identifier, real_T
  c1_y[2])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_eta_i), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_eta_i);
}

static void c1_b_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[2])
{
  real_T c1_dv2[2];
  int32_T c1_i26;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv2, 1, 0, 0U, 1, 0U, 1, 2);
  for (c1_i26 = 0; c1_i26 < 2; c1_i26++) {
    c1_y[c1_i26] = c1_dv2[c1_i26];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_eta_i;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[2];
  int32_T c1_i27;
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c1_eta_i = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_eta_i), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_eta_i);
  for (c1_i27 = 0; c1_i27 < 2; c1_i27++) {
    (*(real_T (*)[2])c1_outData)[c1_i27] = c1_y[c1_i27];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i28;
  real_T c1_b_inData[3];
  int32_T c1_i29;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i28 = 0; c1_i28 < 3; c1_i28++) {
    c1_b_inData[c1_i28] = (*(real_T (*)[3])c1_inData)[c1_i28];
  }

  for (c1_i29 = 0; c1_i29 < 3; c1_i29++) {
    c1_u[c1_i29] = c1_b_inData[c1_i29];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_eta_s, const char_T *c1_identifier, real_T
  c1_y[3])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_eta_s), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_eta_s);
}

static void c1_d_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3])
{
  real_T c1_dv3[3];
  int32_T c1_i30;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i30 = 0; c1_i30 < 3; c1_i30++) {
    c1_y[c1_i30] = c1_dv3[c1_i30];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_eta_s;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i31;
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c1_eta_s = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_eta_s), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_eta_s);
  for (c1_i31 = 0; c1_i31 < 3; c1_i31++) {
    (*(real_T (*)[3])c1_outData)[c1_i31] = c1_y[c1_i31];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_e_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_error, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_error), &c1_thisId);
  sf_mex_destroy(&c1_error);
  return c1_y;
}

static real_T c1_f_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_error;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c1_error = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_error), &c1_thisId);
  sf_mex_destroy(&c1_error);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_HIL_model_experiments2_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[27];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i32;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 27), FALSE);
  for (c1_i32 = 0; c1_i32 < 27; c1_i32++) {
    c1_r0 = &c1_info[c1_i32];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i32);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i32);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i32);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i32);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i32);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i32);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i32);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i32);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[27])
{
  c1_info[0].context = "";
  c1_info[0].name = "rand";
  c1_info[0].dominantType = "";
  c1_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/rand.m";
  c1_info[0].fileTimeLo = 1313347822U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/rand.m";
  c1_info[1].name = "eml_is_rand_extrinsic";
  c1_info[1].dominantType = "";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_is_rand_extrinsic.m";
  c1_info[1].fileTimeLo = 1334071490U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/rand.m";
  c1_info[2].name = "eml_rand";
  c1_info[2].dominantType = "char";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c1_info[2].fileTimeLo = 1313347820U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c1_info[3].name = "eml_rand_str2id";
  c1_info[3].dominantType = "char";
  c1_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_str2id.m";
  c1_info[3].fileTimeLo = 1313347822U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c1_info[4].name = "eml_rand_mcg16807_stateful";
  c1_info[4].dominantType = "char";
  c1_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c1_info[4].fileTimeLo = 1313347820U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c1_info[5].name = "eml_rand_mcg16807";
  c1_info[5].dominantType = "char";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m";
  c1_info[5].fileTimeLo = 1313347820U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c1_info[6].name = "eml_rand_mcg16807";
  c1_info[6].dominantType = "uint32";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m";
  c1_info[6].fileTimeLo = 1313347820U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m!genrandu";
  c1_info[7].name = "mtimes";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[7].fileTimeLo = 1289519692U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c1_info[8].name = "eml_rand_shr3cong_stateful";
  c1_info[8].dominantType = "char";
  c1_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c1_info[8].fileTimeLo = 1313347822U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c1_info[9].name = "eml_rand_shr3cong";
  c1_info[9].dominantType = "char";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m";
  c1_info[9].fileTimeLo = 1313347820U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c1_info[10].name = "eml_rand_shr3cong";
  c1_info[10].dominantType = "uint32";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m";
  c1_info[10].fileTimeLo = 1313347820U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m!genrandu";
  c1_info[11].name = "mtimes";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[11].fileTimeLo = 1289519692U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c1_info[12].name = "eml_rand_mt19937ar_stateful";
  c1_info[12].dominantType = "char";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c1_info[12].fileTimeLo = 1313347820U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c1_info[13].name = "eml_rand_mt19937ar";
  c1_info[13].dominantType = "char";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m";
  c1_info[13].fileTimeLo = 1313347820U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c1_info[14].name = "eml_rand_mt19937ar";
  c1_info[14].dominantType = "uint32";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m";
  c1_info[14].fileTimeLo = 1313347820U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c1_info[15].name = "eps";
  c1_info[15].dominantType = "";
  c1_info[15].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[15].fileTimeLo = 1326727996U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[16].name = "eml_eps";
  c1_info[16].dominantType = "char";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c1_info[16].fileTimeLo = 1326727996U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c1_info[17].name = "eml_float_model";
  c1_info[17].dominantType = "char";
  c1_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[17].fileTimeLo = 1326727996U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c1_info[18].name = "isequal";
  c1_info[18].dominantType = "double";
  c1_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c1_info[18].fileTimeLo = 1286818758U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c1_info[19].name = "eml_isequal_core";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c1_info[19].fileTimeLo = 1286818786U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c1_info[20].name = "isnan";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c1_info[20].fileTimeLo = 1286818760U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c1_info[21].name = "mtimes";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[21].fileTimeLo = 1289519692U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c1_info[22].name = "eml_index_class";
  c1_info[22].dominantType = "";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[22].fileTimeLo = 1323170578U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c1_info[23].name = "eml_index_plus";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[23].fileTimeLo = 1286818778U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[24].name = "eml_index_class";
  c1_info[24].dominantType = "";
  c1_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[24].fileTimeLo = 1323170578U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c1_info[25].name = "eml_error";
  c1_info[25].dominantType = "char";
  c1_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[25].fileTimeLo = 1343830358U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context = "";
  c1_info[26].name = "mtimes";
  c1_info[26].dominantType = "double";
  c1_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[26].fileTimeLo = 1289519692U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
}

static real_T c1_rand(SFc1_HIL_model_experiments2InstanceStruct *chartInstance)
{
  real_T c1_r;
  uint32_T c1_hoistedGlobal;
  uint32_T c1_d_state;
  uint32_T c1_e_state;
  uint32_T c1_s;
  uint32_T c1_u0;
  uint32_T c1_hi;
  uint32_T c1_lo;
  uint32_T c1_test1;
  uint32_T c1_test2;
  uint32_T c1_f_state;
  real_T c1_a;
  real_T c1_b_r;
  real_T c1_d1;
  int32_T c1_i33;
  uint32_T c1_icng;
  uint32_T c1_jsr;
  uint32_T c1_u1;
  uint32_T c1_u2;
  uint32_T c1_ui;
  uint32_T c1_b_ui;
  real_T c1_b_a;
  real_T c1_c_r;
  real_T c1_d2;
  uint32_T c1_uv2[625];
  int32_T c1_i34;
  real_T c1_d3;
  if (!chartInstance->c1_method_not_empty) {
    chartInstance->c1_method = 7U;
    chartInstance->c1_method_not_empty = TRUE;
  }

  if (chartInstance->c1_method == 4U) {
    if (!chartInstance->c1_state_not_empty) {
      chartInstance->c1_state = 1144108930U;
      chartInstance->c1_state_not_empty = TRUE;
    }

    c1_hoistedGlobal = chartInstance->c1_state;
    c1_d_state = c1_hoistedGlobal;
    c1_e_state = c1_d_state;
    c1_s = c1_e_state;
    c1_u0 = 127773U;
    if (c1_u0 == 0) {
      c1_hi = MAX_uint32_T;
    } else {
      c1_hi = c1_s / c1_u0;
    }

    c1_lo = c1_s - c1_hi * 127773U;
    c1_test1 = 16807U * c1_lo;
    c1_test2 = 2836U * c1_hi;
    if (c1_test1 < c1_test2) {
      c1_f_state = (c1_test1 - c1_test2) + 2147483647U;
    } else {
      c1_f_state = c1_test1 - c1_test2;
    }

    c1_a = (real_T)c1_f_state;
    c1_b_r = c1_a * 4.6566128752457969E-10;
    c1_e_state = c1_f_state;
    c1_d1 = c1_b_r;
    chartInstance->c1_state = c1_e_state;
    c1_r = c1_d1;
  } else if (chartInstance->c1_method == 5U) {
    if (!chartInstance->c1_b_state_not_empty) {
      for (c1_i33 = 0; c1_i33 < 2; c1_i33++) {
        chartInstance->c1_b_state[c1_i33] = 362436069U + 158852560U * (uint32_T)
          c1_i33;
      }

      chartInstance->c1_b_state_not_empty = TRUE;
    }

    c1_icng = chartInstance->c1_b_state[0];
    c1_jsr = chartInstance->c1_b_state[1];
    c1_u1 = c1_jsr;
    c1_u2 = c1_icng;
    c1_u2 = 69069U * c1_u2 + 1234567U;
    c1_u1 ^= c1_u1 << 13U;
    c1_u1 ^= c1_u1 >> 17U;
    c1_u1 ^= c1_u1 << 5U;
    c1_ui = c1_u2 + c1_u1;
    chartInstance->c1_b_state[0] = c1_u2;
    chartInstance->c1_b_state[1] = c1_u1;
    c1_b_ui = c1_ui;
    c1_b_a = (real_T)c1_b_ui;
    c1_c_r = c1_b_a * 2.328306436538696E-10;
    c1_d2 = c1_c_r;
    c1_r = c1_d2;
  } else {
    if (!chartInstance->c1_c_state_not_empty) {
      c1_eml_rand_mt19937ar(chartInstance, c1_uv2);
      for (c1_i34 = 0; c1_i34 < 625; c1_i34++) {
        chartInstance->c1_c_state[c1_i34] = c1_uv2[c1_i34];
      }

      chartInstance->c1_c_state_not_empty = TRUE;
    }

    c1_d3 = c1_c_eml_rand_mt19937ar(chartInstance, chartInstance->c1_c_state);
    c1_r = c1_d3;
  }

  return c1_r;
}

static void c1_eml_rand_mt19937ar(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, uint32_T c1_d_state[625])
{
  real_T c1_d4;
  int32_T c1_i35;
  c1_d4 = 5489.0;
  for (c1_i35 = 0; c1_i35 < 625; c1_i35++) {
    c1_d_state[c1_i35] = 0U;
  }

  c1_b_twister_state_vector(chartInstance, c1_d_state, c1_d4);
}

static void c1_twister_state_vector(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, uint32_T c1_mt[625], real_T c1_seed, uint32_T c1_b_mt[625])
{
  int32_T c1_i36;
  for (c1_i36 = 0; c1_i36 < 625; c1_i36++) {
    c1_b_mt[c1_i36] = c1_mt[c1_i36];
  }

  c1_b_twister_state_vector(chartInstance, c1_b_mt, c1_seed);
}

static void c1_b_eml_rand_mt19937ar(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, uint32_T c1_d_state[625], uint32_T c1_e_state[625], real_T
  *c1_r)
{
  int32_T c1_i37;
  for (c1_i37 = 0; c1_i37 < 625; c1_i37++) {
    c1_e_state[c1_i37] = c1_d_state[c1_i37];
  }

  *c1_r = c1_c_eml_rand_mt19937ar(chartInstance, c1_e_state);
}

static void c1_eml_error(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance)
{
  int32_T c1_i38;
  static char_T c1_cv0[37] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 'r', 'a', 'n', 'd', '_', 'i', 'n', 'v', 'a', 'l', 'i', 'd',
    'T', 'w', 'i', 's', 't', 'e', 'r', 'S', 't', 'a', 't', 'e' };

  char_T c1_u[37];
  const mxArray *c1_y = NULL;
  for (c1_i38 = 0; c1_i38 < 37; c1_i38++) {
    c1_u[c1_i38] = c1_cv0[c1_i38];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 37), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c1_y));
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_g_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i39;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i39, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i39;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint32_T c1_h_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c1_b_method, const char_T *c1_identifier)
{
  uint32_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_method),
    &c1_thisId);
  sf_mex_destroy(&c1_b_method);
  return c1_y;
}

static uint32_T c1_i_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint32_T c1_y;
  uint32_T c1_u3;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_method_not_empty = FALSE;
  } else {
    chartInstance->c1_method_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u3, 1, 7, 0U, 0, 0U, 0);
    c1_y = c1_u3;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static uint32_T c1_j_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c1_d_state, const char_T *c1_identifier)
{
  uint32_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d_state), &c1_thisId);
  sf_mex_destroy(&c1_d_state);
  return c1_y;
}

static uint32_T c1_k_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint32_T c1_y;
  uint32_T c1_u4;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_state_not_empty = FALSE;
  } else {
    chartInstance->c1_state_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u4, 1, 7, 0U, 0, 0U, 0);
    c1_y = c1_u4;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_l_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_d_state, const char_T *c1_identifier,
  uint32_T c1_y[625])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d_state), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_d_state);
}

static void c1_m_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  uint32_T c1_y[625])
{
  uint32_T c1_uv3[625];
  int32_T c1_i40;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_c_state_not_empty = FALSE;
  } else {
    chartInstance->c1_c_state_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv3, 1, 7, 0U, 1, 0U, 1, 625);
    for (c1_i40 = 0; c1_i40 < 625; c1_i40++) {
      c1_y[c1_i40] = c1_uv3[c1_i40];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_n_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_d_state, const char_T *c1_identifier,
  uint32_T c1_y[2])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d_state), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_d_state);
}

static void c1_o_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  uint32_T c1_y[2])
{
  uint32_T c1_uv4[2];
  int32_T c1_i41;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_b_state_not_empty = FALSE;
  } else {
    chartInstance->c1_b_state_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv4, 1, 7, 0U, 1, 0U, 1, 2);
    for (c1_i41 = 0; c1_i41 < 2; c1_i41++) {
      c1_y[c1_i41] = c1_uv4[c1_i41];
    }
  }

  sf_mex_destroy(&c1_u);
}

static uint8_T c1_p_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_HIL_model_experiments2, const
  char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_HIL_model_experiments2), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_HIL_model_experiments2);
  return c1_y;
}

static uint8_T c1_q_emlrt_marshallIn(SFc1_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u5;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u5, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u5;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_twister_state_vector(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, uint32_T c1_mt[625], real_T c1_seed)
{
  real_T c1_d5;
  uint32_T c1_u6;
  uint32_T c1_r;
  int32_T c1_mti;
  real_T c1_b_mti;
  real_T c1_d6;
  uint32_T c1_u7;
  c1_d5 = c1_seed;
  if (c1_d5 < 4.294967296E+9) {
    if (c1_d5 >= 0.0) {
      c1_u6 = (uint32_T)c1_d5;
    } else {
      c1_u6 = 0U;
    }
  } else if (c1_d5 >= 4.294967296E+9) {
    c1_u6 = MAX_uint32_T;
  } else {
    c1_u6 = 0U;
  }

  c1_r = c1_u6;
  c1_mt[0] = c1_r;
  for (c1_mti = 0; c1_mti < 623; c1_mti++) {
    c1_b_mti = 2.0 + (real_T)c1_mti;
    c1_d6 = muDoubleScalarRound(c1_b_mti - 1.0);
    if (c1_d6 < 4.294967296E+9) {
      if (c1_d6 >= 0.0) {
        c1_u7 = (uint32_T)c1_d6;
      } else {
        c1_u7 = 0U;
      }
    } else if (c1_d6 >= 4.294967296E+9) {
      c1_u7 = MAX_uint32_T;
    } else {
      c1_u7 = 0U;
    }

    c1_r = (c1_r ^ c1_r >> 30U) * 1812433253U + c1_u7;
    c1_mt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", c1_b_mti), 1, 625, 1, 0) - 1] = c1_r;
  }

  c1_mt[624] = 624U;
}

static real_T c1_c_eml_rand_mt19937ar(SFc1_HIL_model_experiments2InstanceStruct *
  chartInstance, uint32_T c1_d_state[625])
{
  int32_T c1_i42;
  uint32_T c1_u[2];
  int32_T c1_j;
  real_T c1_b_j;
  uint32_T c1_mti;
  int32_T c1_kk;
  real_T c1_b_kk;
  uint32_T c1_y;
  uint32_T c1_b_y;
  uint32_T c1_c_y;
  int32_T c1_c_kk;
  uint32_T c1_d_y;
  uint32_T c1_e_y;
  uint32_T c1_f_y;
  uint32_T c1_g_y;
  real_T c1_a;
  real_T c1_h_y;
  real_T c1_b;
  real_T c1_b_r;
  boolean_T c1_b0;
  boolean_T c1_isvalid;
  int32_T c1_k;
  int32_T c1_b_a;
  real_T c1_d7;
  boolean_T guard1 = FALSE;
  int32_T exitg1;
  boolean_T exitg2;

  /* <LEGAL>   This is a uniform (0,1) pseudorandom number generator based on: */
  /* <LEGAL> */
  /* <LEGAL>    A C-program for MT19937, with initialization improved 2002/1/26. */
  /* <LEGAL>    Coded by Takuji Nishimura and Makoto Matsumoto. */
  /* <LEGAL> */
  /* <LEGAL>    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura, */
  /* <LEGAL>    All rights reserved. */
  /* <LEGAL> */
  /* <LEGAL>    Redistribution and use in source and binary forms, with or without */
  /* <LEGAL>    modification, are permitted provided that the following conditions */
  /* <LEGAL>    are met: */
  /* <LEGAL> */
  /* <LEGAL>      1. Redistributions of source code must retain the above copyright */
  /* <LEGAL>         notice, this list of conditions and the following disclaimer. */
  /* <LEGAL> */
  /* <LEGAL>      2. Redistributions in binary form must reproduce the above copyright */
  /* <LEGAL>         notice, this list of conditions and the following disclaimer in the */
  /* <LEGAL>         documentation and/or other materials provided with the distribution. */
  /* <LEGAL> */
  /* <LEGAL>      3. The names of its contributors may not be used to endorse or promote */
  /* <LEGAL>         products derived from this software without specific prior written */
  /* <LEGAL>         permission. */
  /* <LEGAL> */
  /* <LEGAL>    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS */
  /* <LEGAL>    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT */
  /* <LEGAL>    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
  /* <LEGAL>    A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR */
  /* <LEGAL>    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, */
  /* <LEGAL>    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, */
  /* <LEGAL>    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR */
  /* <LEGAL>    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF */
  /* <LEGAL>    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING */
  /* <LEGAL>    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS */
  /* <LEGAL>    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
  do {
    exitg1 = 0;
    for (c1_i42 = 0; c1_i42 < 2; c1_i42++) {
      c1_u[c1_i42] = 0U;
    }

    for (c1_j = 0; c1_j < 2; c1_j++) {
      c1_b_j = 1.0 + (real_T)c1_j;
      c1_mti = c1_d_state[624] + 1U;
      if ((real_T)c1_mti >= 625.0) {
        for (c1_kk = 0; c1_kk < 227; c1_kk++) {
          c1_b_kk = 1.0 + (real_T)c1_kk;
          c1_y = (c1_d_state[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
                   (int32_T)_SFD_INTEGER_CHECK("", c1_b_kk), 1, 625, 1, 0) - 1]
                  & 2147483648U) | (c1_d_state[(int32_T)(real_T)
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            c1_b_kk + 1.0), 1, 625, 1, 0) - 1] & 2147483647U);
          c1_b_y = c1_y;
          c1_c_y = c1_b_y;
          if ((real_T)(c1_c_y & 1U) == 0.0) {
            c1_c_y >>= 1U;
          } else {
            c1_c_y = c1_c_y >> 1U ^ 2567483615U;
          }

          c1_d_state[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c1_b_kk), 1, 625, 1, 0) - 1] = c1_d_state
            [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c1_b_kk + 397.0), 1, 625, 1, 0) - 1] ^ c1_c_y;
        }

        for (c1_c_kk = 0; c1_c_kk < 396; c1_c_kk++) {
          c1_b_kk = 228.0 + (real_T)c1_c_kk;
          c1_y = (c1_d_state[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
                   (int32_T)_SFD_INTEGER_CHECK("", c1_b_kk), 1, 625, 1, 0) - 1]
                  & 2147483648U) | (c1_d_state[(int32_T)(real_T)
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            c1_b_kk + 1.0), 1, 625, 1, 0) - 1] & 2147483647U);
          c1_d_y = c1_y;
          c1_e_y = c1_d_y;
          if ((real_T)(c1_e_y & 1U) == 0.0) {
            c1_e_y >>= 1U;
          } else {
            c1_e_y = c1_e_y >> 1U ^ 2567483615U;
          }

          c1_d_state[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c1_b_kk), 1, 625, 1, 0) - 1] = c1_d_state
            [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (c1_b_kk + 1.0) - 228.0), 1, 625, 1, 0) - 1] ^
            c1_e_y;
        }

        c1_y = (c1_d_state[623] & 2147483648U) | (c1_d_state[0] & 2147483647U);
        c1_f_y = c1_y;
        c1_g_y = c1_f_y;
        if ((real_T)(c1_g_y & 1U) == 0.0) {
          c1_g_y >>= 1U;
        } else {
          c1_g_y = c1_g_y >> 1U ^ 2567483615U;
        }

        c1_d_state[623] = c1_d_state[396] ^ c1_g_y;
        c1_mti = 1U;
      }

      c1_y = c1_d_state[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c1_mti), 1, 625, 1, 0)
        - 1];
      c1_d_state[624] = c1_mti;
      c1_y ^= c1_y >> 11U;
      c1_y ^= c1_y << 7U & 2636928640U;
      c1_y ^= c1_y << 15U & 4022730752U;
      c1_y ^= c1_y >> 18U;
      c1_u[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c1_b_j), 1, 2, 1, 0) - 1] = c1_y;
    }

    c1_u[0] >>= 5U;
    c1_u[1] >>= 6U;
    c1_a = (real_T)c1_u[0];
    c1_h_y = c1_a * 6.7108864E+7;
    c1_b = c1_h_y + (real_T)c1_u[1];
    c1_b_r = 1.1102230246251565E-16 * c1_b;
    if (c1_b_r == 0.0) {
      guard1 = FALSE;
      if ((real_T)c1_d_state[624] >= 1.0) {
        if ((real_T)c1_d_state[624] < 625.0) {
          c1_b0 = TRUE;
        } else {
          guard1 = TRUE;
        }
      } else {
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        c1_b0 = FALSE;
      }

      c1_isvalid = c1_b0;
      if (c1_isvalid) {
        c1_isvalid = FALSE;
        c1_k = 1;
        exitg2 = FALSE;
        while ((exitg2 == FALSE) && (c1_k < 625)) {
          if ((real_T)c1_d_state[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
               _SFD_INTEGER_CHECK("", (real_T)c1_k), 1, 625, 1, 0) - 1] == 0.0)
          {
            c1_b_a = c1_k + 1;
            c1_k = c1_b_a;
          } else {
            c1_isvalid = TRUE;
            exitg2 = TRUE;
          }
        }
      }

      if (!c1_isvalid) {
        c1_eml_error(chartInstance);
        c1_d7 = 5489.0;
        c1_b_twister_state_vector(chartInstance, c1_d_state, c1_d7);
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return c1_b_r;
}

static void init_dsm_address_info(SFc1_HIL_model_experiments2InstanceStruct
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

void sf_c1_HIL_model_experiments2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1171325189U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1533711139U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1782811593U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3818559733U);
}

mxArray *sf_c1_HIL_model_experiments2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("26QjjNalRMX5fmoznzLGrB");
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
      pr[0] = (double)(3);
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
      pr[0] = (double)(2);
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

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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

mxArray *sf_c1_HIL_model_experiments2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c1_HIL_model_experiments2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[11],T\"error\",},{M[1],M[10],T\"eta_i\",},{M[1],M[5],T\"eta_s\",},{M[4],M[0],T\"method\",S'l','i','p'{{M1x2[512 518],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[165 170],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[166 171],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[165 170],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m\"}}},{M[8],M[0],T\"is_active_c1_HIL_model_experiments2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_HIL_model_experiments2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
    chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_experiments2MachineNumber_,
           1,
           1,
           1,
           9,
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
          init_script_number_translation(_HIL_model_experiments2MachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HIL_model_experiments2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HIL_model_experiments2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"error");
          _SFD_SET_DATA_PROPS(1,1,1,0,"err_percent");
          _SFD_SET_DATA_PROPS(2,2,0,1,"eta_s");
          _SFD_SET_DATA_PROPS(3,1,1,0,"eta_s_in");
          _SFD_SET_DATA_PROPS(4,1,1,0,"eta_i_in");
          _SFD_SET_DATA_PROPS(5,1,1,0,"error_previous");
          _SFD_SET_DATA_PROPS(6,1,1,0,"eta_s_previous");
          _SFD_SET_DATA_PROPS(7,1,1,0,"eta_i_previous");
          _SFD_SET_DATA_PROPS(8,2,0,1,"eta_i");
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
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,437);
        _SFD_CV_INIT_EML_IF(0,1,0,179,201,-1,227);
        _SFD_CV_INIT_EML_IF(0,1,1,278,298,370,437);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          real_T *c1_error;
          real_T *c1_err_percent;
          real_T *c1_error_previous;
          real_T (*c1_eta_s)[3];
          real_T (*c1_eta_s_in)[3];
          real_T (*c1_eta_i_in)[2];
          real_T (*c1_eta_s_previous)[3];
          real_T (*c1_eta_i_previous)[2];
          real_T (*c1_eta_i)[2];
          c1_eta_i = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
          c1_eta_i_previous = (real_T (*)[2])ssGetInputPortSignal
            (chartInstance->S, 5);
          c1_eta_s_previous = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 4);
          c1_error_previous = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c1_eta_i_in = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
          c1_eta_s_in = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c1_eta_s = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c1_err_percent = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c1_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_error);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_err_percent);
          _SFD_SET_DATA_VALUE_PTR(2U, *c1_eta_s);
          _SFD_SET_DATA_VALUE_PTR(3U, *c1_eta_s_in);
          _SFD_SET_DATA_VALUE_PTR(4U, *c1_eta_i_in);
          _SFD_SET_DATA_VALUE_PTR(5U, c1_error_previous);
          _SFD_SET_DATA_VALUE_PTR(6U, *c1_eta_s_previous);
          _SFD_SET_DATA_VALUE_PTR(7U, *c1_eta_i_previous);
          _SFD_SET_DATA_VALUE_PTR(8U, *c1_eta_i);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HIL_model_experiments2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "5d1d5sSeMbUSSINPhhruBG";
}

static void sf_opaque_initialize_c1_HIL_model_experiments2(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_HIL_model_experiments2
    ((SFc1_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
  initialize_c1_HIL_model_experiments2
    ((SFc1_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_HIL_model_experiments2(void *chartInstanceVar)
{
  enable_c1_HIL_model_experiments2((SFc1_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_HIL_model_experiments2(void *chartInstanceVar)
{
  disable_c1_HIL_model_experiments2((SFc1_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_HIL_model_experiments2(void *chartInstanceVar)
{
  sf_c1_HIL_model_experiments2((SFc1_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_HIL_model_experiments2
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_HIL_model_experiments2
    ((SFc1_HIL_model_experiments2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_HIL_model_experiments2();/* state var info */
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

extern void sf_internal_set_sim_state_c1_HIL_model_experiments2(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_HIL_model_experiments2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_HIL_model_experiments2
    ((SFc1_HIL_model_experiments2InstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_HIL_model_experiments2
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c1_HIL_model_experiments2(S);
}

static void sf_opaque_set_sim_state_c1_HIL_model_experiments2(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c1_HIL_model_experiments2(S, st);
}

static void sf_opaque_terminate_c1_HIL_model_experiments2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_HIL_model_experiments2InstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_experiments2_optimization_info();
    }

    finalize_c1_HIL_model_experiments2
      ((SFc1_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_HIL_model_experiments2
    ((SFc1_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_HIL_model_experiments2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_HIL_model_experiments2
      ((SFc1_HIL_model_experiments2InstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_HIL_model_experiments2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_experiments2_optimization_info();
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
        infoStruct,1,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
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
  ssSetChecksum0(S,(1567679518U));
  ssSetChecksum1(S,(3018153U));
  ssSetChecksum2(S,(1234625752U));
  ssSetChecksum3(S,(2840056860U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_HIL_model_experiments2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_HIL_model_experiments2(SimStruct *S)
{
  SFc1_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc1_HIL_model_experiments2InstanceStruct *)utMalloc(sizeof
    (SFc1_HIL_model_experiments2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_HIL_model_experiments2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_HIL_model_experiments2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_HIL_model_experiments2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_HIL_model_experiments2;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c1_HIL_model_experiments2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c1_HIL_model_experiments2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_HIL_model_experiments2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_HIL_model_experiments2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_HIL_model_experiments2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_HIL_model_experiments2;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_HIL_model_experiments2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_HIL_model_experiments2;
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

void c1_HIL_model_experiments2_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_HIL_model_experiments2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_HIL_model_experiments2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_HIL_model_experiments2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_HIL_model_experiments2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
