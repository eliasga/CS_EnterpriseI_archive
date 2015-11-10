/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Model_justmodel_sfun.h"
#include "c12_Model_justmodel.h"
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
static const char * c12_debug_family_names[12] = { "num", "nargin", "nargout",
  "err_percent", "eta_s_in", "eta_i_in", "error_previous", "eta_s_previous",
  "eta_i_previous", "error", "eta_s", "eta_i" };

/* Function Declarations */
static void initialize_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance);
static void initialize_params_c12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance);
static void enable_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance);
static void disable_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance);
static void c12_update_debugger_state_c12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance);
static void set_sim_state_c12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance, const mxArray *c12_st);
static void finalize_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance);
static void sf_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance);
static void initSimStructsc12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance);
static void registerMessagesc12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber);
static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_eta_i, const char_T *c12_identifier, real_T
  c12_y[2]);
static void c12_b_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[2]);
static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_c_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_eta_s, const char_T *c12_identifier, real_T
  c12_y[3]);
static void c12_d_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[3]);
static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static real_T c12_e_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_error, const char_T *c12_identifier);
static real_T c12_f_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static void c12_info_helper(c12_ResolvedFunctionInfo c12_info[27]);
static real_T c12_rand(SFc12_Model_justmodelInstanceStruct *chartInstance);
static void c12_eml_rand_mt19937ar(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_d_state[625]);
static void c12_twister_state_vector(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_mt[625], real_T c12_seed, uint32_T c12_b_mt[625]);
static void c12_b_eml_rand_mt19937ar(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_d_state[625], uint32_T c12_e_state[625], real_T
  *c12_r);
static void c12_eml_error(SFc12_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static int32_T c12_g_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static uint32_T c12_h_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_b_method, const char_T *c12_identifier);
static uint32_T c12_i_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static uint32_T c12_j_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_d_state, const char_T *c12_identifier);
static uint32_T c12_k_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_l_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_d_state, const char_T *c12_identifier,
  uint32_T c12_y[625]);
static void c12_m_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  uint32_T c12_y[625]);
static void c12_n_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_d_state, const char_T *c12_identifier,
  uint32_T c12_y[2]);
static void c12_o_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  uint32_T c12_y[2]);
static uint8_T c12_p_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_b_is_active_c12_Model_justmodel, const
  char_T *c12_identifier);
static uint8_T c12_q_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_b_twister_state_vector(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_mt[625], real_T c12_seed);
static real_T c12_c_eml_rand_mt19937ar(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_d_state[625]);
static void init_dsm_address_info(SFc12_Model_justmodelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance)
{
  chartInstance->c12_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c12_method_not_empty = FALSE;
  chartInstance->c12_state_not_empty = FALSE;
  chartInstance->c12_b_state_not_empty = FALSE;
  chartInstance->c12_c_state_not_empty = FALSE;
  chartInstance->c12_is_active_c12_Model_justmodel = 0U;
}

static void initialize_params_c12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance)
{
}

static void enable_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c12_update_debugger_state_c12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance)
{
  const mxArray *c12_st;
  const mxArray *c12_y = NULL;
  real_T c12_hoistedGlobal;
  real_T c12_u;
  const mxArray *c12_b_y = NULL;
  int32_T c12_i0;
  real_T c12_b_u[2];
  const mxArray *c12_c_y = NULL;
  int32_T c12_i1;
  real_T c12_c_u[3];
  const mxArray *c12_d_y = NULL;
  uint32_T c12_b_hoistedGlobal;
  uint32_T c12_d_u;
  const mxArray *c12_e_y = NULL;
  uint32_T c12_c_hoistedGlobal;
  uint32_T c12_e_u;
  const mxArray *c12_f_y = NULL;
  int32_T c12_i2;
  uint32_T c12_f_u[625];
  const mxArray *c12_g_y = NULL;
  int32_T c12_i3;
  uint32_T c12_g_u[2];
  const mxArray *c12_h_y = NULL;
  uint8_T c12_d_hoistedGlobal;
  uint8_T c12_h_u;
  const mxArray *c12_i_y = NULL;
  real_T *c12_error;
  real_T (*c12_eta_s)[3];
  real_T (*c12_eta_i)[2];
  c12_eta_i = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c12_eta_s = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c12_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c12_st = NULL;
  c12_st = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_createcellarray(8), FALSE);
  c12_hoistedGlobal = *c12_error;
  c12_u = c12_hoistedGlobal;
  c12_b_y = NULL;
  sf_mex_assign(&c12_b_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c12_y, 0, c12_b_y);
  for (c12_i0 = 0; c12_i0 < 2; c12_i0++) {
    c12_b_u[c12_i0] = (*c12_eta_i)[c12_i0];
  }

  c12_c_y = NULL;
  sf_mex_assign(&c12_c_y, sf_mex_create("y", c12_b_u, 0, 0U, 1U, 0U, 1, 2),
                FALSE);
  sf_mex_setcell(c12_y, 1, c12_c_y);
  for (c12_i1 = 0; c12_i1 < 3; c12_i1++) {
    c12_c_u[c12_i1] = (*c12_eta_s)[c12_i1];
  }

  c12_d_y = NULL;
  sf_mex_assign(&c12_d_y, sf_mex_create("y", c12_c_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c12_y, 2, c12_d_y);
  c12_b_hoistedGlobal = chartInstance->c12_method;
  c12_d_u = c12_b_hoistedGlobal;
  c12_e_y = NULL;
  if (!chartInstance->c12_method_not_empty) {
    sf_mex_assign(&c12_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_e_y, sf_mex_create("y", &c12_d_u, 7, 0U, 0U, 0U, 0),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 3, c12_e_y);
  c12_c_hoistedGlobal = chartInstance->c12_state;
  c12_e_u = c12_c_hoistedGlobal;
  c12_f_y = NULL;
  if (!chartInstance->c12_state_not_empty) {
    sf_mex_assign(&c12_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_f_y, sf_mex_create("y", &c12_e_u, 7, 0U, 0U, 0U, 0),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 4, c12_f_y);
  for (c12_i2 = 0; c12_i2 < 625; c12_i2++) {
    c12_f_u[c12_i2] = chartInstance->c12_c_state[c12_i2];
  }

  c12_g_y = NULL;
  if (!chartInstance->c12_c_state_not_empty) {
    sf_mex_assign(&c12_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_g_y, sf_mex_create("y", c12_f_u, 7, 0U, 1U, 0U, 1, 625),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 5, c12_g_y);
  for (c12_i3 = 0; c12_i3 < 2; c12_i3++) {
    c12_g_u[c12_i3] = chartInstance->c12_b_state[c12_i3];
  }

  c12_h_y = NULL;
  if (!chartInstance->c12_b_state_not_empty) {
    sf_mex_assign(&c12_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c12_h_y, sf_mex_create("y", c12_g_u, 7, 0U, 1U, 0U, 1, 2),
                  FALSE);
  }

  sf_mex_setcell(c12_y, 6, c12_h_y);
  c12_d_hoistedGlobal = chartInstance->c12_is_active_c12_Model_justmodel;
  c12_h_u = c12_d_hoistedGlobal;
  c12_i_y = NULL;
  sf_mex_assign(&c12_i_y, sf_mex_create("y", &c12_h_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c12_y, 7, c12_i_y);
  sf_mex_assign(&c12_st, c12_y, FALSE);
  return c12_st;
}

static void set_sim_state_c12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance, const mxArray *c12_st)
{
  const mxArray *c12_u;
  real_T c12_dv0[2];
  int32_T c12_i4;
  real_T c12_dv1[3];
  int32_T c12_i5;
  uint32_T c12_uv0[625];
  int32_T c12_i6;
  uint32_T c12_uv1[2];
  int32_T c12_i7;
  real_T *c12_error;
  real_T (*c12_eta_i)[2];
  real_T (*c12_eta_s)[3];
  c12_eta_i = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c12_eta_s = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c12_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c12_doneDoubleBufferReInit = TRUE;
  c12_u = sf_mex_dup(c12_st);
  *c12_error = c12_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c12_u, 0)), "error");
  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 1)),
                       "eta_i", c12_dv0);
  for (c12_i4 = 0; c12_i4 < 2; c12_i4++) {
    (*c12_eta_i)[c12_i4] = c12_dv0[c12_i4];
  }

  c12_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 2)),
    "eta_s", c12_dv1);
  for (c12_i5 = 0; c12_i5 < 3; c12_i5++) {
    (*c12_eta_s)[c12_i5] = c12_dv1[c12_i5];
  }

  chartInstance->c12_method = c12_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c12_u, 3)), "method");
  chartInstance->c12_state = c12_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c12_u, 4)), "state");
  c12_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 5)),
    "state", c12_uv0);
  for (c12_i6 = 0; c12_i6 < 625; c12_i6++) {
    chartInstance->c12_c_state[c12_i6] = c12_uv0[c12_i6];
  }

  c12_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 6)),
    "state", c12_uv1);
  for (c12_i7 = 0; c12_i7 < 2; c12_i7++) {
    chartInstance->c12_b_state[c12_i7] = c12_uv1[c12_i7];
  }

  chartInstance->c12_is_active_c12_Model_justmodel = c12_p_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 7)),
     "is_active_c12_Model_justmodel");
  sf_mex_destroy(&c12_u);
  c12_update_debugger_state_c12_Model_justmodel(chartInstance);
  sf_mex_destroy(&c12_st);
}

static void finalize_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance)
{
}

static void sf_c12_Model_justmodel(SFc12_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c12_i8;
  int32_T c12_i9;
  int32_T c12_i10;
  int32_T c12_i11;
  int32_T c12_i12;
  int32_T c12_i13;
  real_T c12_hoistedGlobal;
  real_T c12_b_hoistedGlobal;
  real_T c12_err_percent;
  int32_T c12_i14;
  real_T c12_eta_s_in[3];
  int32_T c12_i15;
  real_T c12_eta_i_in[2];
  real_T c12_error_previous;
  int32_T c12_i16;
  real_T c12_eta_s_previous[3];
  int32_T c12_i17;
  real_T c12_eta_i_previous[2];
  uint32_T c12_debug_family_var_map[12];
  real_T c12_num;
  real_T c12_nargin = 6.0;
  real_T c12_nargout = 3.0;
  real_T c12_error;
  real_T c12_eta_s[3];
  real_T c12_eta_i[2];
  real_T c12_b;
  int32_T c12_i18;
  int32_T c12_i19;
  int32_T c12_i20;
  int32_T c12_i21;
  int32_T c12_i22;
  int32_T c12_i23;
  real_T *c12_b_error;
  real_T *c12_b_err_percent;
  real_T *c12_b_error_previous;
  real_T (*c12_b_eta_s)[3];
  real_T (*c12_b_eta_i)[2];
  real_T (*c12_b_eta_i_previous)[2];
  real_T (*c12_b_eta_s_previous)[3];
  real_T (*c12_b_eta_i_in)[2];
  real_T (*c12_b_eta_s_in)[3];
  c12_b_eta_i = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c12_b_eta_i_previous = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
  c12_b_eta_s_previous = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c12_b_error_previous = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c12_b_eta_i_in = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
  c12_b_eta_s_in = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c12_b_eta_s = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c12_b_err_percent = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c12_b_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c12_b_error, 0U);
  _SFD_DATA_RANGE_CHECK(*c12_b_err_percent, 1U);
  for (c12_i8 = 0; c12_i8 < 3; c12_i8++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_eta_s)[c12_i8], 2U);
  }

  for (c12_i9 = 0; c12_i9 < 3; c12_i9++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_eta_s_in)[c12_i9], 3U);
  }

  for (c12_i10 = 0; c12_i10 < 2; c12_i10++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_eta_i_in)[c12_i10], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*c12_b_error_previous, 5U);
  for (c12_i11 = 0; c12_i11 < 3; c12_i11++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_eta_s_previous)[c12_i11], 6U);
  }

  for (c12_i12 = 0; c12_i12 < 2; c12_i12++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_eta_i_previous)[c12_i12], 7U);
  }

  for (c12_i13 = 0; c12_i13 < 2; c12_i13++) {
    _SFD_DATA_RANGE_CHECK((*c12_b_eta_i)[c12_i13], 8U);
  }

  chartInstance->c12_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  c12_hoistedGlobal = *c12_b_err_percent;
  c12_b_hoistedGlobal = *c12_b_error_previous;
  c12_err_percent = c12_hoistedGlobal;
  for (c12_i14 = 0; c12_i14 < 3; c12_i14++) {
    c12_eta_s_in[c12_i14] = (*c12_b_eta_s_in)[c12_i14];
  }

  for (c12_i15 = 0; c12_i15 < 2; c12_i15++) {
    c12_eta_i_in[c12_i15] = (*c12_b_eta_i_in)[c12_i15];
  }

  c12_error_previous = c12_b_hoistedGlobal;
  for (c12_i16 = 0; c12_i16 < 3; c12_i16++) {
    c12_eta_s_previous[c12_i16] = (*c12_b_eta_s_previous)[c12_i16];
  }

  for (c12_i17 = 0; c12_i17 < 2; c12_i17++) {
    c12_eta_i_previous[c12_i17] = (*c12_b_eta_i_previous)[c12_i17];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c12_debug_family_names,
    c12_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_num, 0U, c12_c_sf_marshallOut,
    c12_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargin, 1U, c12_c_sf_marshallOut,
    c12_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargout, 2U, c12_c_sf_marshallOut,
    c12_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_err_percent, 3U, c12_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_eta_s_in, 4U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_eta_i_in, 5U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_error_previous, 6U, c12_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_eta_s_previous, 7U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_eta_i_previous, 8U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_error, 9U, c12_c_sf_marshallOut,
    c12_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_eta_s, 10U, c12_b_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_eta_i, 11U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 6);
  c12_b = c12_rand(chartInstance);
  c12_num = 100.0 * c12_b;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 8);
  if (CV_EML_IF(0, 1, 0, c12_error_previous == 1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 9);
    c12_err_percent = 99.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 13);
  if (CV_EML_IF(0, 1, 1, c12_num < c12_err_percent)) {
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 14);
    c12_error = 1.0;
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 15);
    for (c12_i18 = 0; c12_i18 < 3; c12_i18++) {
      c12_eta_s[c12_i18] = c12_eta_s_previous[c12_i18];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 16);
    for (c12_i19 = 0; c12_i19 < 2; c12_i19++) {
      c12_eta_i[c12_i19] = c12_eta_i_previous[c12_i19];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 18);
    c12_error = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 19);
    for (c12_i20 = 0; c12_i20 < 3; c12_i20++) {
      c12_eta_s[c12_i20] = c12_eta_s_in[c12_i20];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 20);
    for (c12_i21 = 0; c12_i21 < 2; c12_i21++) {
      c12_eta_i[c12_i21] = c12_eta_i_in[c12_i21];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, -20);
  _SFD_SYMBOL_SCOPE_POP();
  *c12_b_error = c12_error;
  for (c12_i22 = 0; c12_i22 < 3; c12_i22++) {
    (*c12_b_eta_s)[c12_i22] = c12_eta_s[c12_i22];
  }

  for (c12_i23 = 0; c12_i23 < 2; c12_i23++) {
    (*c12_b_eta_i)[c12_i23] = c12_eta_i[c12_i23];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Model_justmodelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance)
{
}

static void registerMessagesc12_Model_justmodel
  (SFc12_Model_justmodelInstanceStruct *chartInstance)
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
  int32_T c12_i24;
  real_T c12_b_inData[2];
  int32_T c12_i25;
  real_T c12_u[2];
  const mxArray *c12_y = NULL;
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i24 = 0; c12_i24 < 2; c12_i24++) {
    c12_b_inData[c12_i24] = (*(real_T (*)[2])c12_inData)[c12_i24];
  }

  for (c12_i25 = 0; c12_i25 < 2; c12_i25++) {
    c12_u[c12_i25] = c12_b_inData[c12_i25];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_eta_i, const char_T *c12_identifier, real_T
  c12_y[2])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_eta_i), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_eta_i);
}

static void c12_b_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[2])
{
  real_T c12_dv2[2];
  int32_T c12_i26;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv2, 1, 0, 0U, 1, 0U, 1, 2);
  for (c12_i26 = 0; c12_i26 < 2; c12_i26++) {
    c12_y[c12_i26] = c12_dv2[c12_i26];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_eta_i;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[2];
  int32_T c12_i27;
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c12_eta_i = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_eta_i), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_eta_i);
  for (c12_i27 = 0; c12_i27 < 2; c12_i27++) {
    (*(real_T (*)[2])c12_outData)[c12_i27] = c12_y[c12_i27];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i28;
  real_T c12_b_inData[3];
  int32_T c12_i29;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i28 = 0; c12_i28 < 3; c12_i28++) {
    c12_b_inData[c12_i28] = (*(real_T (*)[3])c12_inData)[c12_i28];
  }

  for (c12_i29 = 0; c12_i29 < 3; c12_i29++) {
    c12_u[c12_i29] = c12_b_inData[c12_i29];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_c_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_eta_s, const char_T *c12_identifier, real_T
  c12_y[3])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_eta_s), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_eta_s);
}

static void c12_d_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[3])
{
  real_T c12_dv3[3];
  int32_T c12_i30;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c12_i30 = 0; c12_i30 < 3; c12_i30++) {
    c12_y[c12_i30] = c12_dv3[c12_i30];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_eta_s;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[3];
  int32_T c12_i31;
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c12_eta_s = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_eta_s), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_eta_s);
  for (c12_i31 = 0; c12_i31 < 3; c12_i31++) {
    (*(real_T (*)[3])c12_outData)[c12_i31] = c12_y[c12_i31];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  real_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(real_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static real_T c12_e_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_error, const char_T *c12_identifier)
{
  real_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_error),
    &c12_thisId);
  sf_mex_destroy(&c12_error);
  return c12_y;
}

static real_T c12_f_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  real_T c12_y;
  real_T c12_d0;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_d0, 1, 0, 0U, 0, 0U, 0);
  c12_y = c12_d0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_error;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y;
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c12_error = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_error),
    &c12_thisId);
  sf_mex_destroy(&c12_error);
  *(real_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

const mxArray *sf_c12_Model_justmodel_get_eml_resolved_functions_info(void)
{
  const mxArray *c12_nameCaptureInfo;
  c12_ResolvedFunctionInfo c12_info[27];
  const mxArray *c12_m0 = NULL;
  int32_T c12_i32;
  c12_ResolvedFunctionInfo *c12_r0;
  c12_nameCaptureInfo = NULL;
  c12_nameCaptureInfo = NULL;
  c12_info_helper(c12_info);
  sf_mex_assign(&c12_m0, sf_mex_createstruct("nameCaptureInfo", 1, 27), FALSE);
  for (c12_i32 = 0; c12_i32 < 27; c12_i32++) {
    c12_r0 = &c12_info[c12_i32];
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->context)), "context", "nameCaptureInfo",
                    c12_i32);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->name)), "name", "nameCaptureInfo",
                    c12_i32);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      c12_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c12_i32);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->resolved)), "resolved",
                    "nameCaptureInfo", c12_i32);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c12_i32);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c12_i32);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c12_i32);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c12_i32);
  }

  sf_mex_assign(&c12_nameCaptureInfo, c12_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c12_nameCaptureInfo);
  return c12_nameCaptureInfo;
}

static void c12_info_helper(c12_ResolvedFunctionInfo c12_info[27])
{
  c12_info[0].context = "";
  c12_info[0].name = "rand";
  c12_info[0].dominantType = "";
  c12_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/rand.m";
  c12_info[0].fileTimeLo = 1313347822U;
  c12_info[0].fileTimeHi = 0U;
  c12_info[0].mFileTimeLo = 0U;
  c12_info[0].mFileTimeHi = 0U;
  c12_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/rand.m";
  c12_info[1].name = "eml_is_rand_extrinsic";
  c12_info[1].dominantType = "";
  c12_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_is_rand_extrinsic.m";
  c12_info[1].fileTimeLo = 1334071490U;
  c12_info[1].fileTimeHi = 0U;
  c12_info[1].mFileTimeLo = 0U;
  c12_info[1].mFileTimeHi = 0U;
  c12_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/rand.m";
  c12_info[2].name = "eml_rand";
  c12_info[2].dominantType = "char";
  c12_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[2].fileTimeLo = 1313347820U;
  c12_info[2].fileTimeHi = 0U;
  c12_info[2].mFileTimeLo = 0U;
  c12_info[2].mFileTimeHi = 0U;
  c12_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[3].name = "eml_rand_str2id";
  c12_info[3].dominantType = "char";
  c12_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_str2id.m";
  c12_info[3].fileTimeLo = 1313347822U;
  c12_info[3].fileTimeHi = 0U;
  c12_info[3].mFileTimeLo = 0U;
  c12_info[3].mFileTimeHi = 0U;
  c12_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[4].name = "eml_rand_mcg16807_stateful";
  c12_info[4].dominantType = "char";
  c12_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c12_info[4].fileTimeLo = 1313347820U;
  c12_info[4].fileTimeHi = 0U;
  c12_info[4].mFileTimeLo = 0U;
  c12_info[4].mFileTimeHi = 0U;
  c12_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c12_info[5].name = "eml_rand_mcg16807";
  c12_info[5].dominantType = "char";
  c12_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m";
  c12_info[5].fileTimeLo = 1313347820U;
  c12_info[5].fileTimeHi = 0U;
  c12_info[5].mFileTimeLo = 0U;
  c12_info[5].mFileTimeHi = 0U;
  c12_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m";
  c12_info[6].name = "eml_rand_mcg16807";
  c12_info[6].dominantType = "uint32";
  c12_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m";
  c12_info[6].fileTimeLo = 1313347820U;
  c12_info[6].fileTimeHi = 0U;
  c12_info[6].mFileTimeLo = 0U;
  c12_info[6].mFileTimeHi = 0U;
  c12_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807.m!genrandu";
  c12_info[7].name = "mtimes";
  c12_info[7].dominantType = "double";
  c12_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[7].fileTimeLo = 1289519692U;
  c12_info[7].fileTimeHi = 0U;
  c12_info[7].mFileTimeLo = 0U;
  c12_info[7].mFileTimeHi = 0U;
  c12_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[8].name = "eml_rand_shr3cong_stateful";
  c12_info[8].dominantType = "char";
  c12_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c12_info[8].fileTimeLo = 1313347822U;
  c12_info[8].fileTimeHi = 0U;
  c12_info[8].mFileTimeLo = 0U;
  c12_info[8].mFileTimeHi = 0U;
  c12_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c12_info[9].name = "eml_rand_shr3cong";
  c12_info[9].dominantType = "char";
  c12_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m";
  c12_info[9].fileTimeLo = 1313347820U;
  c12_info[9].fileTimeHi = 0U;
  c12_info[9].mFileTimeLo = 0U;
  c12_info[9].mFileTimeHi = 0U;
  c12_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m";
  c12_info[10].name = "eml_rand_shr3cong";
  c12_info[10].dominantType = "uint32";
  c12_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m";
  c12_info[10].fileTimeLo = 1313347820U;
  c12_info[10].fileTimeHi = 0U;
  c12_info[10].mFileTimeLo = 0U;
  c12_info[10].mFileTimeHi = 0U;
  c12_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong.m!genrandu";
  c12_info[11].name = "mtimes";
  c12_info[11].dominantType = "double";
  c12_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[11].fileTimeLo = 1289519692U;
  c12_info[11].fileTimeHi = 0U;
  c12_info[11].mFileTimeLo = 0U;
  c12_info[11].mFileTimeHi = 0U;
  c12_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand.m";
  c12_info[12].name = "eml_rand_mt19937ar_stateful";
  c12_info[12].dominantType = "char";
  c12_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c12_info[12].fileTimeLo = 1313347820U;
  c12_info[12].fileTimeHi = 0U;
  c12_info[12].mFileTimeLo = 0U;
  c12_info[12].mFileTimeHi = 0U;
  c12_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c12_info[13].name = "eml_rand_mt19937ar";
  c12_info[13].dominantType = "char";
  c12_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m";
  c12_info[13].fileTimeLo = 1313347820U;
  c12_info[13].fileTimeHi = 0U;
  c12_info[13].mFileTimeLo = 0U;
  c12_info[13].mFileTimeHi = 0U;
  c12_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m";
  c12_info[14].name = "eml_rand_mt19937ar";
  c12_info[14].dominantType = "uint32";
  c12_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m";
  c12_info[14].fileTimeLo = 1313347820U;
  c12_info[14].fileTimeHi = 0U;
  c12_info[14].mFileTimeLo = 0U;
  c12_info[14].mFileTimeHi = 0U;
  c12_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c12_info[15].name = "eps";
  c12_info[15].dominantType = "";
  c12_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c12_info[15].fileTimeLo = 1326727996U;
  c12_info[15].fileTimeHi = 0U;
  c12_info[15].mFileTimeLo = 0U;
  c12_info[15].mFileTimeHi = 0U;
  c12_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c12_info[16].name = "eml_eps";
  c12_info[16].dominantType = "char";
  c12_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c12_info[16].fileTimeLo = 1326727996U;
  c12_info[16].fileTimeHi = 0U;
  c12_info[16].mFileTimeLo = 0U;
  c12_info[16].mFileTimeHi = 0U;
  c12_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c12_info[17].name = "eml_float_model";
  c12_info[17].dominantType = "char";
  c12_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c12_info[17].fileTimeLo = 1326727996U;
  c12_info[17].fileTimeHi = 0U;
  c12_info[17].mFileTimeLo = 0U;
  c12_info[17].mFileTimeHi = 0U;
  c12_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c12_info[18].name = "isequal";
  c12_info[18].dominantType = "double";
  c12_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c12_info[18].fileTimeLo = 1286818758U;
  c12_info[18].fileTimeHi = 0U;
  c12_info[18].mFileTimeLo = 0U;
  c12_info[18].mFileTimeHi = 0U;
  c12_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c12_info[19].name = "eml_isequal_core";
  c12_info[19].dominantType = "double";
  c12_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c12_info[19].fileTimeLo = 1286818786U;
  c12_info[19].fileTimeHi = 0U;
  c12_info[19].mFileTimeLo = 0U;
  c12_info[19].mFileTimeHi = 0U;
  c12_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c12_info[20].name = "isnan";
  c12_info[20].dominantType = "double";
  c12_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c12_info[20].fileTimeLo = 1286818760U;
  c12_info[20].fileTimeHi = 0U;
  c12_info[20].mFileTimeLo = 0U;
  c12_info[20].mFileTimeHi = 0U;
  c12_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c12_info[21].name = "mtimes";
  c12_info[21].dominantType = "double";
  c12_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[21].fileTimeLo = 1289519692U;
  c12_info[21].fileTimeHi = 0U;
  c12_info[21].mFileTimeLo = 0U;
  c12_info[21].mFileTimeHi = 0U;
  c12_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c12_info[22].name = "eml_index_class";
  c12_info[22].dominantType = "";
  c12_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[22].fileTimeLo = 1323170578U;
  c12_info[22].fileTimeHi = 0U;
  c12_info[22].mFileTimeLo = 0U;
  c12_info[22].mFileTimeHi = 0U;
  c12_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!is_valid_state";
  c12_info[23].name = "eml_index_plus";
  c12_info[23].dominantType = "double";
  c12_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c12_info[23].fileTimeLo = 1286818778U;
  c12_info[23].fileTimeHi = 0U;
  c12_info[23].mFileTimeLo = 0U;
  c12_info[23].mFileTimeHi = 0U;
  c12_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c12_info[24].name = "eml_index_class";
  c12_info[24].dominantType = "";
  c12_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c12_info[24].fileTimeLo = 1323170578U;
  c12_info[24].fileTimeHi = 0U;
  c12_info[24].mFileTimeLo = 0U;
  c12_info[24].mFileTimeHi = 0U;
  c12_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar.m!genrandu";
  c12_info[25].name = "eml_error";
  c12_info[25].dominantType = "char";
  c12_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c12_info[25].fileTimeLo = 1343830358U;
  c12_info[25].fileTimeHi = 0U;
  c12_info[25].mFileTimeLo = 0U;
  c12_info[25].mFileTimeHi = 0U;
  c12_info[26].context = "";
  c12_info[26].name = "mtimes";
  c12_info[26].dominantType = "double";
  c12_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c12_info[26].fileTimeLo = 1289519692U;
  c12_info[26].fileTimeHi = 0U;
  c12_info[26].mFileTimeLo = 0U;
  c12_info[26].mFileTimeHi = 0U;
}

static real_T c12_rand(SFc12_Model_justmodelInstanceStruct *chartInstance)
{
  real_T c12_r;
  uint32_T c12_hoistedGlobal;
  uint32_T c12_d_state;
  uint32_T c12_e_state;
  uint32_T c12_s;
  uint32_T c12_u0;
  uint32_T c12_hi;
  uint32_T c12_lo;
  uint32_T c12_test1;
  uint32_T c12_test2;
  uint32_T c12_f_state;
  real_T c12_a;
  real_T c12_b_r;
  real_T c12_d1;
  int32_T c12_i33;
  uint32_T c12_icng;
  uint32_T c12_jsr;
  uint32_T c12_u1;
  uint32_T c12_u2;
  uint32_T c12_ui;
  uint32_T c12_b_ui;
  real_T c12_b_a;
  real_T c12_c_r;
  real_T c12_d2;
  uint32_T c12_uv2[625];
  int32_T c12_i34;
  real_T c12_d3;
  if (!chartInstance->c12_method_not_empty) {
    chartInstance->c12_method = 7U;
    chartInstance->c12_method_not_empty = TRUE;
  }

  if (chartInstance->c12_method == 4U) {
    if (!chartInstance->c12_state_not_empty) {
      chartInstance->c12_state = 1144108930U;
      chartInstance->c12_state_not_empty = TRUE;
    }

    c12_hoistedGlobal = chartInstance->c12_state;
    c12_d_state = c12_hoistedGlobal;
    c12_e_state = c12_d_state;
    c12_s = c12_e_state;
    c12_u0 = 127773U;
    if (c12_u0 == 0) {
      c12_hi = MAX_uint32_T;
    } else {
      c12_hi = c12_s / c12_u0;
    }

    c12_lo = c12_s - c12_hi * 127773U;
    c12_test1 = 16807U * c12_lo;
    c12_test2 = 2836U * c12_hi;
    if (c12_test1 < c12_test2) {
      c12_f_state = (c12_test1 - c12_test2) + 2147483647U;
    } else {
      c12_f_state = c12_test1 - c12_test2;
    }

    c12_a = (real_T)c12_f_state;
    c12_b_r = c12_a * 4.6566128752457969E-10;
    c12_e_state = c12_f_state;
    c12_d1 = c12_b_r;
    chartInstance->c12_state = c12_e_state;
    c12_r = c12_d1;
  } else if (chartInstance->c12_method == 5U) {
    if (!chartInstance->c12_b_state_not_empty) {
      for (c12_i33 = 0; c12_i33 < 2; c12_i33++) {
        chartInstance->c12_b_state[c12_i33] = 362436069U + 158852560U *
          (uint32_T)c12_i33;
      }

      chartInstance->c12_b_state_not_empty = TRUE;
    }

    c12_icng = chartInstance->c12_b_state[0];
    c12_jsr = chartInstance->c12_b_state[1];
    c12_u1 = c12_jsr;
    c12_u2 = c12_icng;
    c12_u2 = 69069U * c12_u2 + 1234567U;
    c12_u1 ^= c12_u1 << 13U;
    c12_u1 ^= c12_u1 >> 17U;
    c12_u1 ^= c12_u1 << 5U;
    c12_ui = c12_u2 + c12_u1;
    chartInstance->c12_b_state[0] = c12_u2;
    chartInstance->c12_b_state[1] = c12_u1;
    c12_b_ui = c12_ui;
    c12_b_a = (real_T)c12_b_ui;
    c12_c_r = c12_b_a * 2.328306436538696E-10;
    c12_d2 = c12_c_r;
    c12_r = c12_d2;
  } else {
    if (!chartInstance->c12_c_state_not_empty) {
      c12_eml_rand_mt19937ar(chartInstance, c12_uv2);
      for (c12_i34 = 0; c12_i34 < 625; c12_i34++) {
        chartInstance->c12_c_state[c12_i34] = c12_uv2[c12_i34];
      }

      chartInstance->c12_c_state_not_empty = TRUE;
    }

    c12_d3 = c12_c_eml_rand_mt19937ar(chartInstance, chartInstance->c12_c_state);
    c12_r = c12_d3;
  }

  return c12_r;
}

static void c12_eml_rand_mt19937ar(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_d_state[625])
{
  real_T c12_d4;
  int32_T c12_i35;
  c12_d4 = 5489.0;
  for (c12_i35 = 0; c12_i35 < 625; c12_i35++) {
    c12_d_state[c12_i35] = 0U;
  }

  c12_b_twister_state_vector(chartInstance, c12_d_state, c12_d4);
}

static void c12_twister_state_vector(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_mt[625], real_T c12_seed, uint32_T c12_b_mt[625])
{
  int32_T c12_i36;
  for (c12_i36 = 0; c12_i36 < 625; c12_i36++) {
    c12_b_mt[c12_i36] = c12_mt[c12_i36];
  }

  c12_b_twister_state_vector(chartInstance, c12_b_mt, c12_seed);
}

static void c12_b_eml_rand_mt19937ar(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_d_state[625], uint32_T c12_e_state[625], real_T
  *c12_r)
{
  int32_T c12_i37;
  for (c12_i37 = 0; c12_i37 < 625; c12_i37++) {
    c12_e_state[c12_i37] = c12_d_state[c12_i37];
  }

  *c12_r = c12_c_eml_rand_mt19937ar(chartInstance, c12_e_state);
}

static void c12_eml_error(SFc12_Model_justmodelInstanceStruct *chartInstance)
{
  int32_T c12_i38;
  static char_T c12_cv0[37] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 'r', 'a', 'n', 'd', '_', 'i', 'n', 'v', 'a', 'l', 'i', 'd',
    'T', 'w', 'i', 's', 't', 'e', 'r', 'S', 't', 'a', 't', 'e' };

  char_T c12_u[37];
  const mxArray *c12_y = NULL;
  for (c12_i38 = 0; c12_i38 < 37; c12_i38++) {
    c12_u[c12_i38] = c12_cv0[c12_i38];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 10, 0U, 1U, 0U, 2, 1, 37),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c12_y));
}

static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(int32_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static int32_T c12_g_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  int32_T c12_y;
  int32_T c12_i39;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_i39, 1, 6, 0U, 0, 0U, 0);
  c12_y = c12_i39;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_b_sfEvent;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  int32_T c12_y;
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c12_b_sfEvent = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_b_sfEvent),
    &c12_thisId);
  sf_mex_destroy(&c12_b_sfEvent);
  *(int32_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static uint32_T c12_h_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_b_method, const char_T *c12_identifier)
{
  uint32_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_b_method),
    &c12_thisId);
  sf_mex_destroy(&c12_b_method);
  return c12_y;
}

static uint32_T c12_i_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint32_T c12_y;
  uint32_T c12_u3;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_method_not_empty = FALSE;
  } else {
    chartInstance->c12_method_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u3, 1, 7, 0U, 0, 0U, 0);
    c12_y = c12_u3;
  }

  sf_mex_destroy(&c12_u);
  return c12_y;
}

static uint32_T c12_j_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_d_state, const char_T *c12_identifier)
{
  uint32_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_d_state),
    &c12_thisId);
  sf_mex_destroy(&c12_d_state);
  return c12_y;
}

static uint32_T c12_k_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint32_T c12_y;
  uint32_T c12_u4;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_state_not_empty = FALSE;
  } else {
    chartInstance->c12_state_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u4, 1, 7, 0U, 0, 0U, 0);
    c12_y = c12_u4;
  }

  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_l_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_d_state, const char_T *c12_identifier,
  uint32_T c12_y[625])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_d_state), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_d_state);
}

static void c12_m_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  uint32_T c12_y[625])
{
  uint32_T c12_uv3[625];
  int32_T c12_i40;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_c_state_not_empty = FALSE;
  } else {
    chartInstance->c12_c_state_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_uv3, 1, 7, 0U, 1, 0U, 1,
                  625);
    for (c12_i40 = 0; c12_i40 < 625; c12_i40++) {
      c12_y[c12_i40] = c12_uv3[c12_i40];
    }
  }

  sf_mex_destroy(&c12_u);
}

static void c12_n_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_d_state, const char_T *c12_identifier,
  uint32_T c12_y[2])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_d_state), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_d_state);
}

static void c12_o_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  uint32_T c12_y[2])
{
  uint32_T c12_uv4[2];
  int32_T c12_i41;
  if (mxIsEmpty(c12_u)) {
    chartInstance->c12_b_state_not_empty = FALSE;
  } else {
    chartInstance->c12_b_state_not_empty = TRUE;
    sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_uv4, 1, 7, 0U, 1, 0U, 1,
                  2);
    for (c12_i41 = 0; c12_i41 < 2; c12_i41++) {
      c12_y[c12_i41] = c12_uv4[c12_i41];
    }
  }

  sf_mex_destroy(&c12_u);
}

static uint8_T c12_p_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_b_is_active_c12_Model_justmodel, const
  char_T *c12_identifier)
{
  uint8_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c12_b_is_active_c12_Model_justmodel), &c12_thisId);
  sf_mex_destroy(&c12_b_is_active_c12_Model_justmodel);
  return c12_y;
}

static uint8_T c12_q_emlrt_marshallIn(SFc12_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint8_T c12_y;
  uint8_T c12_u5;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u5, 1, 3, 0U, 0, 0U, 0);
  c12_y = c12_u5;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_b_twister_state_vector(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_mt[625], real_T c12_seed)
{
  real_T c12_d5;
  uint32_T c12_u6;
  uint32_T c12_r;
  int32_T c12_mti;
  real_T c12_b_mti;
  real_T c12_d6;
  uint32_T c12_u7;
  c12_d5 = c12_seed;
  if (c12_d5 < 4.294967296E+9) {
    if (c12_d5 >= 0.0) {
      c12_u6 = (uint32_T)c12_d5;
    } else {
      c12_u6 = 0U;
    }
  } else if (c12_d5 >= 4.294967296E+9) {
    c12_u6 = MAX_uint32_T;
  } else {
    c12_u6 = 0U;
  }

  c12_r = c12_u6;
  c12_mt[0] = c12_r;
  for (c12_mti = 0; c12_mti < 623; c12_mti++) {
    c12_b_mti = 2.0 + (real_T)c12_mti;
    c12_d6 = muDoubleScalarRound(c12_b_mti - 1.0);
    if (c12_d6 < 4.294967296E+9) {
      if (c12_d6 >= 0.0) {
        c12_u7 = (uint32_T)c12_d6;
      } else {
        c12_u7 = 0U;
      }
    } else if (c12_d6 >= 4.294967296E+9) {
      c12_u7 = MAX_uint32_T;
    } else {
      c12_u7 = 0U;
    }

    c12_r = (c12_r ^ c12_r >> 30U) * 1812433253U + c12_u7;
    c12_mt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", c12_b_mti), 1, 625, 1, 0) - 1] = c12_r;
  }

  c12_mt[624] = 624U;
}

static real_T c12_c_eml_rand_mt19937ar(SFc12_Model_justmodelInstanceStruct
  *chartInstance, uint32_T c12_d_state[625])
{
  int32_T c12_i42;
  uint32_T c12_u[2];
  int32_T c12_j;
  real_T c12_b_j;
  uint32_T c12_mti;
  int32_T c12_kk;
  real_T c12_b_kk;
  uint32_T c12_y;
  uint32_T c12_b_y;
  uint32_T c12_c_y;
  int32_T c12_c_kk;
  uint32_T c12_d_y;
  uint32_T c12_e_y;
  uint32_T c12_f_y;
  uint32_T c12_g_y;
  real_T c12_a;
  real_T c12_h_y;
  real_T c12_b;
  real_T c12_b_r;
  boolean_T c12_b0;
  boolean_T c12_isvalid;
  int32_T c12_k;
  int32_T c12_b_a;
  real_T c12_d7;
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
    for (c12_i42 = 0; c12_i42 < 2; c12_i42++) {
      c12_u[c12_i42] = 0U;
    }

    for (c12_j = 0; c12_j < 2; c12_j++) {
      c12_b_j = 1.0 + (real_T)c12_j;
      c12_mti = c12_d_state[624] + 1U;
      if ((real_T)c12_mti >= 625.0) {
        for (c12_kk = 0; c12_kk < 227; c12_kk++) {
          c12_b_kk = 1.0 + (real_T)c12_kk;
          c12_y = (c12_d_state[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
                    (int32_T)_SFD_INTEGER_CHECK("", c12_b_kk), 1, 625, 1, 0) - 1]
                   & 2147483648U) | (c12_d_state[(int32_T)(real_T)
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            c12_b_kk + 1.0), 1, 625, 1, 0) - 1] & 2147483647U);
          c12_b_y = c12_y;
          c12_c_y = c12_b_y;
          if ((real_T)(c12_c_y & 1U) == 0.0) {
            c12_c_y >>= 1U;
          } else {
            c12_c_y = c12_c_y >> 1U ^ 2567483615U;
          }

          c12_d_state[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c12_b_kk), 1, 625, 1, 0) - 1] = c12_d_state
            [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c12_b_kk + 397.0), 1, 625, 1, 0) - 1] ^
            c12_c_y;
        }

        for (c12_c_kk = 0; c12_c_kk < 396; c12_c_kk++) {
          c12_b_kk = 228.0 + (real_T)c12_c_kk;
          c12_y = (c12_d_state[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
                    (int32_T)_SFD_INTEGER_CHECK("", c12_b_kk), 1, 625, 1, 0) - 1]
                   & 2147483648U) | (c12_d_state[(int32_T)(real_T)
            _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            c12_b_kk + 1.0), 1, 625, 1, 0) - 1] & 2147483647U);
          c12_d_y = c12_y;
          c12_e_y = c12_d_y;
          if ((real_T)(c12_e_y & 1U) == 0.0) {
            c12_e_y >>= 1U;
          } else {
            c12_e_y = c12_e_y >> 1U ^ 2567483615U;
          }

          c12_d_state[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", c12_b_kk), 1, 625, 1, 0) - 1] = c12_d_state
            [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (c12_b_kk + 1.0) - 228.0), 1, 625, 1, 0) - 1]
            ^ c12_e_y;
        }

        c12_y = (c12_d_state[623] & 2147483648U) | (c12_d_state[0] & 2147483647U);
        c12_f_y = c12_y;
        c12_g_y = c12_f_y;
        if ((real_T)(c12_g_y & 1U) == 0.0) {
          c12_g_y >>= 1U;
        } else {
          c12_g_y = c12_g_y >> 1U ^ 2567483615U;
        }

        c12_d_state[623] = c12_d_state[396] ^ c12_g_y;
        c12_mti = 1U;
      }

      c12_y = c12_d_state[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)(uint32_T)_SFD_INTEGER_CHECK("", (real_T)c12_mti), 1, 625, 1, 0)
        - 1];
      c12_d_state[624] = c12_mti;
      c12_y ^= c12_y >> 11U;
      c12_y ^= c12_y << 7U & 2636928640U;
      c12_y ^= c12_y << 15U & 4022730752U;
      c12_y ^= c12_y >> 18U;
      c12_u[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c12_b_j), 1, 2, 1, 0) - 1] = c12_y;
    }

    c12_u[0] >>= 5U;
    c12_u[1] >>= 6U;
    c12_a = (real_T)c12_u[0];
    c12_h_y = c12_a * 6.7108864E+7;
    c12_b = c12_h_y + (real_T)c12_u[1];
    c12_b_r = 1.1102230246251565E-16 * c12_b;
    if (c12_b_r == 0.0) {
      guard1 = FALSE;
      if ((real_T)c12_d_state[624] >= 1.0) {
        if ((real_T)c12_d_state[624] < 625.0) {
          c12_b0 = TRUE;
        } else {
          guard1 = TRUE;
        }
      } else {
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        c12_b0 = FALSE;
      }

      c12_isvalid = c12_b0;
      if (c12_isvalid) {
        c12_isvalid = FALSE;
        c12_k = 1;
        exitg2 = FALSE;
        while ((exitg2 == FALSE) && (c12_k < 625)) {
          if ((real_T)c12_d_state[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
               _SFD_INTEGER_CHECK("", (real_T)c12_k), 1, 625, 1, 0) - 1] == 0.0)
          {
            c12_b_a = c12_k + 1;
            c12_k = c12_b_a;
          } else {
            c12_isvalid = TRUE;
            exitg2 = TRUE;
          }
        }
      }

      if (!c12_isvalid) {
        c12_eml_error(chartInstance);
        c12_d7 = 5489.0;
        c12_b_twister_state_vector(chartInstance, c12_d_state, c12_d7);
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return c12_b_r;
}

static void init_dsm_address_info(SFc12_Model_justmodelInstanceStruct
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

void sf_c12_Model_justmodel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(925340262U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(747127540U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3777176972U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1097445340U);
}

mxArray *sf_c12_Model_justmodel_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("xfSnGuNZBLRs5sdk0BCC1");
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

mxArray *sf_c12_Model_justmodel_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c12_Model_justmodel(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[11],T\"error\",},{M[1],M[10],T\"eta_i\",},{M[1],M[5],T\"eta_s\",},{M[4],M[0],T\"method\",S'l','i','p'{{M1x2[512 518],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[165 170],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_mcg16807_stateful.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[166 171],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_mt19937ar_stateful.m\"}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[165 170],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/randfun/eml_rand_shr3cong_stateful.m\"}}},{M[8],M[0],T\"is_active_c12_Model_justmodel\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c12_Model_justmodel_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc12_Model_justmodelInstanceStruct *chartInstance;
    chartInstance = (SFc12_Model_justmodelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Model_justmodelMachineNumber_,
           12,
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
          (MexFcnForType)c12_c_sf_marshallOut,(MexInFcnForType)
          c12_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c12_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)
            c12_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c12_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          real_T *c12_error;
          real_T *c12_err_percent;
          real_T *c12_error_previous;
          real_T (*c12_eta_s)[3];
          real_T (*c12_eta_s_in)[3];
          real_T (*c12_eta_i_in)[2];
          real_T (*c12_eta_s_previous)[3];
          real_T (*c12_eta_i_previous)[2];
          real_T (*c12_eta_i)[2];
          c12_eta_i = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
          c12_eta_i_previous = (real_T (*)[2])ssGetInputPortSignal
            (chartInstance->S, 5);
          c12_eta_s_previous = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 4);
          c12_error_previous = (real_T *)ssGetInputPortSignal(chartInstance->S,
            3);
          c12_eta_i_in = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
          c12_eta_s_in = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c12_eta_s = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c12_err_percent = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c12_error = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c12_error);
          _SFD_SET_DATA_VALUE_PTR(1U, c12_err_percent);
          _SFD_SET_DATA_VALUE_PTR(2U, *c12_eta_s);
          _SFD_SET_DATA_VALUE_PTR(3U, *c12_eta_s_in);
          _SFD_SET_DATA_VALUE_PTR(4U, *c12_eta_i_in);
          _SFD_SET_DATA_VALUE_PTR(5U, c12_error_previous);
          _SFD_SET_DATA_VALUE_PTR(6U, *c12_eta_s_previous);
          _SFD_SET_DATA_VALUE_PTR(7U, *c12_eta_i_previous);
          _SFD_SET_DATA_VALUE_PTR(8U, *c12_eta_i);
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
  return "fTlsYWM82OaAJSaTSEpkwF";
}

static void sf_opaque_initialize_c12_Model_justmodel(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc12_Model_justmodelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*)
    chartInstanceVar);
  initialize_c12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c12_Model_justmodel(void *chartInstanceVar)
{
  enable_c12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c12_Model_justmodel(void *chartInstanceVar)
{
  disable_c12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c12_Model_justmodel(void *chartInstanceVar)
{
  sf_c12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c12_Model_justmodel(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c12_Model_justmodel
    ((SFc12_Model_justmodelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_Model_justmodel();/* state var info */
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

extern void sf_internal_set_sim_state_c12_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_Model_justmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c12_Model_justmodel(SimStruct* S)
{
  return sf_internal_get_sim_state_c12_Model_justmodel(S);
}

static void sf_opaque_set_sim_state_c12_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c12_Model_justmodel(S, st);
}

static void sf_opaque_terminate_c12_Model_justmodel(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc12_Model_justmodelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Model_justmodel_optimization_info();
    }

    finalize_c12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c12_Model_justmodel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c12_Model_justmodel((SFc12_Model_justmodelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c12_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Model_justmodel_optimization_info();
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
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,12,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,12,3);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,12);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2311773148U));
  ssSetChecksum1(S,(3952334741U));
  ssSetChecksum2(S,(1340511017U));
  ssSetChecksum3(S,(3290551883U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c12_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c12_Model_justmodel(SimStruct *S)
{
  SFc12_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc12_Model_justmodelInstanceStruct *)utMalloc(sizeof
    (SFc12_Model_justmodelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc12_Model_justmodelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c12_Model_justmodel;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c12_Model_justmodel;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c12_Model_justmodel;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c12_Model_justmodel;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c12_Model_justmodel;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c12_Model_justmodel;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c12_Model_justmodel;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c12_Model_justmodel;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c12_Model_justmodel;
  chartInstance->chartInfo.mdlStart = mdlStart_c12_Model_justmodel;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c12_Model_justmodel;
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

void c12_Model_justmodel_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c12_Model_justmodel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c12_Model_justmodel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c12_Model_justmodel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c12_Model_justmodel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
