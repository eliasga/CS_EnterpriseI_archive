/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_experiments1_sfun.h"
#include "c4_HIL_model_experiments1.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HIL_model_experiments1_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c4_debug_family_names[25] = { "eta_s", "eta_i", "d",
  "Tlength", "K_tow", "x_s", "y_s", "psi_s", "x_i", "y_i", "x_r", "y_r", "dist",
  "angle", "deltaL", "Xtow", "Ytow", "nargin", "nargout", "eta_s_in", "eta_i_in",
  "TowLineParameters", "disconnected", "Tension", "T" };

/* Function Declarations */
static void initialize_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void initialize_params_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void enable_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void disable_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void set_sim_state_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance, const mxArray
   *c4_st);
static void finalize_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void sf_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void initSimStructsc4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void registerMessagesc4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static real_T c4_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_T, const char_T *c4_identifier);
static real_T c4_b_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_c_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_Tension, const char_T *c4_identifier, real_T
  c4_y[2]);
static void c4_d_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real_T c4_y[2]);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_e_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real_T c4_y[3]);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[21]);
static real_T c4_mpower(SFc4_HIL_model_experiments1InstanceStruct *chartInstance,
  real_T c4_a);
static void c4_eml_scalar_eg(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance);
static void c4_eml_error(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_f_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_g_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_HIL_model_experiments1, const
  char_T *c4_identifier);
static uint8_T c4_h_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_is_active_c4_HIL_model_experiments1 = 0U;
}

static void initialize_params_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
}

static void enable_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c4_update_debugger_state_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  real_T c4_hoistedGlobal;
  real_T c4_u;
  const mxArray *c4_b_y = NULL;
  int32_T c4_i0;
  real_T c4_b_u[2];
  const mxArray *c4_c_y = NULL;
  uint8_T c4_b_hoistedGlobal;
  uint8_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  real_T *c4_T;
  real_T (*c4_Tension)[2];
  c4_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_Tension = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(3), FALSE);
  c4_hoistedGlobal = *c4_T;
  c4_u = c4_hoistedGlobal;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  for (c4_i0 = 0; c4_i0 < 2; c4_i0++) {
    c4_b_u[c4_i0] = (*c4_Tension)[c4_i0];
  }

  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_b_hoistedGlobal = chartInstance->c4_is_active_c4_HIL_model_experiments1;
  c4_c_u = c4_b_hoistedGlobal;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  sf_mex_assign(&c4_st, c4_y, FALSE);
  return c4_st;
}

static void set_sim_state_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance, const mxArray
   *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv0[2];
  int32_T c4_i1;
  real_T *c4_T;
  real_T (*c4_Tension)[2];
  c4_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_Tension = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = TRUE;
  c4_u = sf_mex_dup(c4_st);
  *c4_T = c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)),
    "T");
  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
                        "Tension", c4_dv0);
  for (c4_i1 = 0; c4_i1 < 2; c4_i1++) {
    (*c4_Tension)[c4_i1] = c4_dv0[c4_i1];
  }

  chartInstance->c4_is_active_c4_HIL_model_experiments1 = c4_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 2)),
     "is_active_c4_HIL_model_experiments1");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_HIL_model_experiments1(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
}

static void sf_c4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
  int32_T c4_i2;
  int32_T c4_i3;
  int32_T c4_i4;
  int32_T c4_i5;
  real_T c4_hoistedGlobal;
  int32_T c4_i6;
  real_T c4_eta_s_in[3];
  int32_T c4_i7;
  real_T c4_eta_i_in[2];
  int32_T c4_i8;
  real_T c4_TowLineParameters[3];
  real_T c4_disconnected;
  uint32_T c4_debug_family_var_map[25];
  real_T c4_eta_s[3];
  real_T c4_eta_i[2];
  real_T c4_d;
  real_T c4_Tlength;
  real_T c4_K_tow;
  real_T c4_x_s;
  real_T c4_y_s;
  real_T c4_psi_s;
  real_T c4_x_i;
  real_T c4_y_i;
  real_T c4_x_r;
  real_T c4_y_r;
  real_T c4_dist;
  real_T c4_angle;
  real_T c4_deltaL;
  real_T c4_Xtow;
  real_T c4_Ytow;
  real_T c4_nargin = 4.0;
  real_T c4_nargout = 2.0;
  real_T c4_Tension[2];
  real_T c4_T;
  int32_T c4_i9;
  int32_T c4_i10;
  real_T c4_x;
  real_T c4_b_x;
  real_T c4_a;
  real_T c4_b;
  real_T c4_y;
  real_T c4_c_x;
  real_T c4_d_x;
  real_T c4_b_a;
  real_T c4_b_b;
  real_T c4_b_y;
  real_T c4_e_x;
  real_T c4_f_x;
  real_T c4_c_y;
  real_T c4_g_x;
  real_T c4_d_y;
  real_T c4_h_x;
  real_T c4_c_a;
  real_T c4_c_b;
  real_T c4_i_x;
  real_T c4_j_x;
  real_T c4_d_a;
  real_T c4_d_b;
  real_T c4_k_x;
  real_T c4_l_x;
  real_T c4_e_a;
  real_T c4_e_b;
  int32_T c4_i11;
  int32_T c4_i12;
  real_T *c4_b_T;
  real_T *c4_b_disconnected;
  real_T (*c4_b_Tension)[2];
  real_T (*c4_b_TowLineParameters)[3];
  real_T (*c4_b_eta_i_in)[2];
  real_T (*c4_b_eta_s_in)[3];
  c4_b_disconnected = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c4_b_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_b_TowLineParameters = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S,
    2);
  c4_b_eta_i_in = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c4_b_Tension = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_eta_s_in = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  for (c4_i2 = 0; c4_i2 < 3; c4_i2++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_eta_s_in)[c4_i2], 0U);
  }

  for (c4_i3 = 0; c4_i3 < 2; c4_i3++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_Tension)[c4_i3], 1U);
  }

  for (c4_i4 = 0; c4_i4 < 2; c4_i4++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_eta_i_in)[c4_i4], 2U);
  }

  for (c4_i5 = 0; c4_i5 < 3; c4_i5++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_TowLineParameters)[c4_i5], 3U);
  }

  _SFD_DATA_RANGE_CHECK(*c4_b_T, 4U);
  _SFD_DATA_RANGE_CHECK(*c4_b_disconnected, 5U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *c4_b_disconnected;
  for (c4_i6 = 0; c4_i6 < 3; c4_i6++) {
    c4_eta_s_in[c4_i6] = (*c4_b_eta_s_in)[c4_i6];
  }

  for (c4_i7 = 0; c4_i7 < 2; c4_i7++) {
    c4_eta_i_in[c4_i7] = (*c4_b_eta_i_in)[c4_i7];
  }

  for (c4_i8 = 0; c4_i8 < 3; c4_i8++) {
    c4_TowLineParameters[c4_i8] = (*c4_b_TowLineParameters)[c4_i8];
  }

  c4_disconnected = c4_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 25U, 25U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_eta_s, 0U, c4_d_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_eta_i, 1U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_d, 2U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_Tlength, 3U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_K_tow, 4U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_x_s, 5U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_y_s, 6U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_psi_s, 7U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_x_i, 8U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_y_i, 9U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_x_r, 10U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_y_r, 11U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_dist, 12U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_angle, 13U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_deltaL, 14U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_Xtow, 15U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_Ytow, 16U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 17U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 18U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_eta_s_in, 19U, c4_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_eta_i_in, 20U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_TowLineParameters, 21U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_disconnected, 22U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_Tension, 23U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_T, 24U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 4);
  CV_EML_IF(0, 1, 0, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 5);
  for (c4_i9 = 0; c4_i9 < 3; c4_i9++) {
    c4_eta_s[c4_i9] = c4_eta_s_in[c4_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 9);
  CV_EML_IF(0, 1, 1, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 10);
  for (c4_i10 = 0; c4_i10 < 2; c4_i10++) {
    c4_eta_i[c4_i10] = c4_eta_i_in[c4_i10];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 15);
  if (CV_EML_IF(0, 1, 2, c4_disconnected == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 17);
    c4_d = c4_TowLineParameters[0];
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 18);
    c4_Tlength = c4_TowLineParameters[1];
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 19);
    c4_K_tow = c4_TowLineParameters[2];
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 21);
    c4_x_s = c4_eta_s[0];
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 22);
    c4_y_s = c4_eta_s[1];
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 23);
    c4_psi_s = c4_eta_s[2];
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 25);
    c4_x_i = c4_eta_i[0];
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 26);
    c4_y_i = c4_eta_i[1];
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 29);
    c4_x = c4_psi_s;
    c4_b_x = c4_x;
    c4_b_x = muDoubleScalarCos(c4_b_x);
    c4_a = c4_d;
    c4_b = c4_b_x;
    c4_y = c4_a * c4_b;
    c4_x_r = c4_x_s - c4_y;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 30);
    c4_c_x = c4_psi_s;
    c4_d_x = c4_c_x;
    c4_d_x = muDoubleScalarSin(c4_d_x);
    c4_b_a = c4_d;
    c4_b_b = c4_d_x;
    c4_b_y = c4_b_a * c4_b_b;
    c4_y_r = c4_y_s - c4_b_y;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 33);
    c4_e_x = c4_mpower(chartInstance, c4_x_r - c4_x_i) + c4_mpower(chartInstance,
      c4_y_r - c4_y_i);
    c4_dist = c4_e_x;
    if (c4_dist < 0.0) {
      c4_eml_error(chartInstance);
    }

    c4_f_x = c4_dist;
    c4_dist = c4_f_x;
    c4_dist = muDoubleScalarSqrt(c4_dist);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 34);
    c4_c_y = c4_y_r - c4_y_i;
    c4_g_x = c4_x_r - c4_x_i;
    c4_eml_scalar_eg(chartInstance);
    c4_d_y = c4_c_y;
    c4_h_x = c4_g_x;
    c4_angle = muDoubleScalarAtan2(c4_d_y, c4_h_x);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 37);
    c4_T = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 38);
    if (CV_EML_IF(0, 1, 3, c4_dist >= c4_Tlength)) {
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 40);
      c4_deltaL = c4_dist - c4_Tlength;
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 41);
      c4_c_a = c4_K_tow;
      c4_c_b = c4_deltaL;
      c4_T = c4_c_a * c4_c_b;
    }

    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 46);
    c4_i_x = c4_angle;
    c4_j_x = c4_i_x;
    c4_j_x = muDoubleScalarCos(c4_j_x);
    c4_d_a = c4_T;
    c4_d_b = c4_j_x;
    c4_Xtow = c4_d_a * c4_d_b;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 47);
    c4_k_x = c4_angle;
    c4_l_x = c4_k_x;
    c4_l_x = muDoubleScalarSin(c4_l_x);
    c4_e_a = c4_T;
    c4_e_b = c4_l_x;
    c4_Ytow = c4_e_a * c4_e_b;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 49);
    c4_Tension[0] = c4_Xtow;
    c4_Tension[1] = c4_Ytow;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 53);
    c4_T = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 54);
    for (c4_i11 = 0; c4_i11 < 2; c4_i11++) {
      c4_Tension[c4_i11] = 0.0;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -54);
  _SFD_SYMBOL_SCOPE_POP();
  for (c4_i12 = 0; c4_i12 < 2; c4_i12++) {
    (*c4_b_Tension)[c4_i12] = c4_Tension[c4_i12];
  }

  *c4_b_T = c4_T;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_experiments1MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
}

static void registerMessagesc4_HIL_model_experiments1
  (SFc4_HIL_model_experiments1InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static real_T c4_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_T, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_T), &c4_thisId);
  sf_mex_destroy(&c4_T);
  return c4_y;
}

static real_T c4_b_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_T;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_T = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_T), &c4_thisId);
  sf_mex_destroy(&c4_T);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i13;
  real_T c4_b_inData[2];
  int32_T c4_i14;
  real_T c4_u[2];
  const mxArray *c4_y = NULL;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i13 = 0; c4_i13 < 2; c4_i13++) {
    c4_b_inData[c4_i13] = (*(real_T (*)[2])c4_inData)[c4_i13];
  }

  for (c4_i14 = 0; c4_i14 < 2; c4_i14++) {
    c4_u[c4_i14] = c4_b_inData[c4_i14];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static void c4_c_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_Tension, const char_T *c4_identifier, real_T
  c4_y[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_Tension), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_Tension);
}

static void c4_d_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real_T c4_y[2])
{
  real_T c4_dv1[2];
  int32_T c4_i15;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv1, 1, 0, 0U, 1, 0U, 1, 2);
  for (c4_i15 = 0; c4_i15 < 2; c4_i15++) {
    c4_y[c4_i15] = c4_dv1[c4_i15];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_Tension;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[2];
  int32_T c4_i16;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_Tension = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_Tension), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_Tension);
  for (c4_i16 = 0; c4_i16 < 2; c4_i16++) {
    (*(real_T (*)[2])c4_outData)[c4_i16] = c4_y[c4_i16];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i17;
  real_T c4_b_inData[3];
  int32_T c4_i18;
  real_T c4_u[3];
  const mxArray *c4_y = NULL;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i17 = 0; c4_i17 < 3; c4_i17++) {
    c4_b_inData[c4_i17] = (*(real_T (*)[3])c4_inData)[c4_i17];
  }

  for (c4_i18 = 0; c4_i18 < 3; c4_i18++) {
    c4_u[c4_i18] = c4_b_inData[c4_i18];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i19;
  real_T c4_b_inData[3];
  int32_T c4_i20;
  real_T c4_u[3];
  const mxArray *c4_y = NULL;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i19 = 0; c4_i19 < 3; c4_i19++) {
    c4_b_inData[c4_i19] = (*(real_T (*)[3])c4_inData)[c4_i19];
  }

  for (c4_i20 = 0; c4_i20 < 3; c4_i20++) {
    c4_u[c4_i20] = c4_b_inData[c4_i20];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static void c4_e_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real_T c4_y[3])
{
  real_T c4_dv2[3];
  int32_T c4_i21;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c4_i21 = 0; c4_i21 < 3; c4_i21++) {
    c4_y[c4_i21] = c4_dv2[c4_i21];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_eta_s;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[3];
  int32_T c4_i22;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_eta_s = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_eta_s), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_eta_s);
  for (c4_i22 = 0; c4_i22 < 3; c4_i22++) {
    (*(real_T (*)[3])c4_outData)[c4_i22] = c4_y[c4_i22];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_HIL_model_experiments1_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo;
  c4_ResolvedFunctionInfo c4_info[21];
  const mxArray *c4_m0 = NULL;
  int32_T c4_i23;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  c4_info_helper(c4_info);
  sf_mex_assign(&c4_m0, sf_mex_createstruct("nameCaptureInfo", 1, 21), FALSE);
  for (c4_i23 = 0; c4_i23 < 21; c4_i23++) {
    c4_r0 = &c4_info[c4_i23];
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context", "nameCaptureInfo",
                    c4_i23);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name", "nameCaptureInfo", c4_i23);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c4_i23);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved", "nameCaptureInfo",
                    c4_i23);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c4_i23);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c4_i23);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c4_i23);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c4_i23);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[21])
{
  c4_info[0].context = "";
  c4_info[0].name = "length";
  c4_info[0].dominantType = "double";
  c4_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c4_info[0].fileTimeLo = 1303146206U;
  c4_info[0].fileTimeHi = 0U;
  c4_info[0].mFileTimeLo = 0U;
  c4_info[0].mFileTimeHi = 0U;
  c4_info[1].context = "";
  c4_info[1].name = "cos";
  c4_info[1].dominantType = "double";
  c4_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c4_info[1].fileTimeLo = 1343830372U;
  c4_info[1].fileTimeHi = 0U;
  c4_info[1].mFileTimeLo = 0U;
  c4_info[1].mFileTimeHi = 0U;
  c4_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c4_info[2].name = "eml_scalar_cos";
  c4_info[2].dominantType = "double";
  c4_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c4_info[2].fileTimeLo = 1286818722U;
  c4_info[2].fileTimeHi = 0U;
  c4_info[2].mFileTimeLo = 0U;
  c4_info[2].mFileTimeHi = 0U;
  c4_info[3].context = "";
  c4_info[3].name = "mtimes";
  c4_info[3].dominantType = "double";
  c4_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[3].fileTimeLo = 1289519692U;
  c4_info[3].fileTimeHi = 0U;
  c4_info[3].mFileTimeLo = 0U;
  c4_info[3].mFileTimeHi = 0U;
  c4_info[4].context = "";
  c4_info[4].name = "sin";
  c4_info[4].dominantType = "double";
  c4_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c4_info[4].fileTimeLo = 1343830386U;
  c4_info[4].fileTimeHi = 0U;
  c4_info[4].mFileTimeLo = 0U;
  c4_info[4].mFileTimeHi = 0U;
  c4_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c4_info[5].name = "eml_scalar_sin";
  c4_info[5].dominantType = "double";
  c4_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c4_info[5].fileTimeLo = 1286818736U;
  c4_info[5].fileTimeHi = 0U;
  c4_info[5].mFileTimeLo = 0U;
  c4_info[5].mFileTimeHi = 0U;
  c4_info[6].context = "";
  c4_info[6].name = "mpower";
  c4_info[6].dominantType = "double";
  c4_info[6].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c4_info[6].fileTimeLo = 1286818842U;
  c4_info[6].fileTimeHi = 0U;
  c4_info[6].mFileTimeLo = 0U;
  c4_info[6].mFileTimeHi = 0U;
  c4_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c4_info[7].name = "power";
  c4_info[7].dominantType = "double";
  c4_info[7].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[7].fileTimeLo = 1348191930U;
  c4_info[7].fileTimeHi = 0U;
  c4_info[7].mFileTimeLo = 0U;
  c4_info[7].mFileTimeHi = 0U;
  c4_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c4_info[8].name = "eml_scalar_eg";
  c4_info[8].dominantType = "double";
  c4_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[8].fileTimeLo = 1286818796U;
  c4_info[8].fileTimeHi = 0U;
  c4_info[8].mFileTimeLo = 0U;
  c4_info[8].mFileTimeHi = 0U;
  c4_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c4_info[9].name = "eml_scalexp_alloc";
  c4_info[9].dominantType = "double";
  c4_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c4_info[9].fileTimeLo = 1352424860U;
  c4_info[9].fileTimeHi = 0U;
  c4_info[9].mFileTimeLo = 0U;
  c4_info[9].mFileTimeHi = 0U;
  c4_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c4_info[10].name = "floor";
  c4_info[10].dominantType = "double";
  c4_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c4_info[10].fileTimeLo = 1343830380U;
  c4_info[10].fileTimeHi = 0U;
  c4_info[10].mFileTimeLo = 0U;
  c4_info[10].mFileTimeHi = 0U;
  c4_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c4_info[11].name = "eml_scalar_floor";
  c4_info[11].dominantType = "double";
  c4_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c4_info[11].fileTimeLo = 1286818726U;
  c4_info[11].fileTimeHi = 0U;
  c4_info[11].mFileTimeLo = 0U;
  c4_info[11].mFileTimeHi = 0U;
  c4_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c4_info[12].name = "eml_scalar_eg";
  c4_info[12].dominantType = "double";
  c4_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[12].fileTimeLo = 1286818796U;
  c4_info[12].fileTimeHi = 0U;
  c4_info[12].mFileTimeLo = 0U;
  c4_info[12].mFileTimeHi = 0U;
  c4_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c4_info[13].name = "mtimes";
  c4_info[13].dominantType = "double";
  c4_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[13].fileTimeLo = 1289519692U;
  c4_info[13].fileTimeHi = 0U;
  c4_info[13].mFileTimeLo = 0U;
  c4_info[13].mFileTimeHi = 0U;
  c4_info[14].context = "";
  c4_info[14].name = "sqrt";
  c4_info[14].dominantType = "double";
  c4_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c4_info[14].fileTimeLo = 1343830386U;
  c4_info[14].fileTimeHi = 0U;
  c4_info[14].mFileTimeLo = 0U;
  c4_info[14].mFileTimeHi = 0U;
  c4_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c4_info[15].name = "eml_error";
  c4_info[15].dominantType = "char";
  c4_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c4_info[15].fileTimeLo = 1343830358U;
  c4_info[15].fileTimeHi = 0U;
  c4_info[15].mFileTimeLo = 0U;
  c4_info[15].mFileTimeHi = 0U;
  c4_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c4_info[16].name = "eml_scalar_sqrt";
  c4_info[16].dominantType = "double";
  c4_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c4_info[16].fileTimeLo = 1286818738U;
  c4_info[16].fileTimeHi = 0U;
  c4_info[16].mFileTimeLo = 0U;
  c4_info[16].mFileTimeHi = 0U;
  c4_info[17].context = "";
  c4_info[17].name = "atan2";
  c4_info[17].dominantType = "double";
  c4_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c4_info[17].fileTimeLo = 1343830372U;
  c4_info[17].fileTimeHi = 0U;
  c4_info[17].mFileTimeLo = 0U;
  c4_info[17].mFileTimeHi = 0U;
  c4_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c4_info[18].name = "eml_scalar_eg";
  c4_info[18].dominantType = "double";
  c4_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[18].fileTimeLo = 1286818796U;
  c4_info[18].fileTimeHi = 0U;
  c4_info[18].mFileTimeLo = 0U;
  c4_info[18].mFileTimeHi = 0U;
  c4_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c4_info[19].name = "eml_scalexp_alloc";
  c4_info[19].dominantType = "double";
  c4_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c4_info[19].fileTimeLo = 1352424860U;
  c4_info[19].fileTimeHi = 0U;
  c4_info[19].mFileTimeLo = 0U;
  c4_info[19].mFileTimeHi = 0U;
  c4_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c4_info[20].name = "eml_scalar_atan2";
  c4_info[20].dominantType = "double";
  c4_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m";
  c4_info[20].fileTimeLo = 1286818720U;
  c4_info[20].fileTimeHi = 0U;
  c4_info[20].mFileTimeLo = 0U;
  c4_info[20].mFileTimeHi = 0U;
}

static real_T c4_mpower(SFc4_HIL_model_experiments1InstanceStruct *chartInstance,
  real_T c4_a)
{
  real_T c4_b_a;
  real_T c4_c_a;
  real_T c4_ak;
  real_T c4_d_a;
  real_T c4_e_a;
  real_T c4_b;
  c4_b_a = c4_a;
  c4_c_a = c4_b_a;
  c4_eml_scalar_eg(chartInstance);
  c4_ak = c4_c_a;
  c4_d_a = c4_ak;
  c4_eml_scalar_eg(chartInstance);
  c4_e_a = c4_d_a;
  c4_b = c4_d_a;
  return c4_e_a * c4_b;
}

static void c4_eml_scalar_eg(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance)
{
}

static void c4_eml_error(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance)
{
  int32_T c4_i24;
  static char_T c4_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c4_u[30];
  const mxArray *c4_y = NULL;
  int32_T c4_i25;
  static char_T c4_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c4_b_u[4];
  const mxArray *c4_b_y = NULL;
  for (c4_i24 = 0; c4_i24 < 30; c4_i24++) {
    c4_u[c4_i24] = c4_cv0[c4_i24];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  for (c4_i25 = 0; c4_i25 < 4; c4_i25++) {
    c4_b_u[c4_i25] = c4_cv1[c4_i25];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U, 14,
    c4_y, 14, c4_b_y));
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static int32_T c4_f_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i26;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i26, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i26;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_g_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_HIL_model_experiments1, const
  char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_HIL_model_experiments1), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_HIL_model_experiments1);
  return c4_y;
}

static uint8_T c4_h_emlrt_marshallIn(SFc4_HIL_model_experiments1InstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_HIL_model_experiments1InstanceStruct
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

void sf_c4_HIL_model_experiments1_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(945345243U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(223758503U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2993445120U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(710725244U);
}

mxArray *sf_c4_HIL_model_experiments1_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("u8DodBcfg6Fycr1oCgSynD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      pr[0] = (double)(2);
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

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
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

mxArray *sf_c4_HIL_model_experiments1_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c4_HIL_model_experiments1(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[8],T\"T\",},{M[1],M[5],T\"Tension\",},{M[8],M[0],T\"is_active_c4_HIL_model_experiments1\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_HIL_model_experiments1_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
    chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_experiments1MachineNumber_,
           4,
           1,
           1,
           6,
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
          init_script_number_translation(_HIL_model_experiments1MachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HIL_model_experiments1MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HIL_model_experiments1MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"eta_s_in");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Tension");
          _SFD_SET_DATA_PROPS(2,1,1,0,"eta_i_in");
          _SFD_SET_DATA_PROPS(3,1,1,0,"TowLineParameters");
          _SFD_SET_DATA_PROPS(4,2,0,1,"T");
          _SFD_SET_DATA_PROPS(5,1,1,0,"disconnected");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1064);
        _SFD_CV_INIT_EML_IF(0,1,0,90,113,136,167);
        _SFD_CV_INIT_EML_IF(0,1,1,168,191,214,242);
        _SFD_CV_INIT_EML_IF(0,1,2,244,264,1012,1063);
        _SFD_CV_INIT_EML_IF(0,1,3,820,838,-1,905);
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
            1.0,0,0,(MexFcnForType)c4_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)
            c4_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c4_T;
          real_T *c4_disconnected;
          real_T (*c4_eta_s_in)[3];
          real_T (*c4_Tension)[2];
          real_T (*c4_eta_i_in)[2];
          real_T (*c4_TowLineParameters)[3];
          c4_disconnected = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c4_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c4_TowLineParameters = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 2);
          c4_eta_i_in = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
          c4_Tension = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
          c4_eta_s_in = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c4_eta_s_in);
          _SFD_SET_DATA_VALUE_PTR(1U, *c4_Tension);
          _SFD_SET_DATA_VALUE_PTR(2U, *c4_eta_i_in);
          _SFD_SET_DATA_VALUE_PTR(3U, *c4_TowLineParameters);
          _SFD_SET_DATA_VALUE_PTR(4U, c4_T);
          _SFD_SET_DATA_VALUE_PTR(5U, c4_disconnected);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HIL_model_experiments1MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "Yx149Zt7ofzbrArignrUN";
}

static void sf_opaque_initialize_c4_HIL_model_experiments1(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_HIL_model_experiments1InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c4_HIL_model_experiments1
    ((SFc4_HIL_model_experiments1InstanceStruct*) chartInstanceVar);
  initialize_c4_HIL_model_experiments1
    ((SFc4_HIL_model_experiments1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_HIL_model_experiments1(void *chartInstanceVar)
{
  enable_c4_HIL_model_experiments1((SFc4_HIL_model_experiments1InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c4_HIL_model_experiments1(void *chartInstanceVar)
{
  disable_c4_HIL_model_experiments1((SFc4_HIL_model_experiments1InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c4_HIL_model_experiments1(void *chartInstanceVar)
{
  sf_c4_HIL_model_experiments1((SFc4_HIL_model_experiments1InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_HIL_model_experiments1
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_HIL_model_experiments1
    ((SFc4_HIL_model_experiments1InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_HIL_model_experiments1();/* state var info */
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

extern void sf_internal_set_sim_state_c4_HIL_model_experiments1(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_HIL_model_experiments1();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_HIL_model_experiments1
    ((SFc4_HIL_model_experiments1InstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_HIL_model_experiments1
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c4_HIL_model_experiments1(S);
}

static void sf_opaque_set_sim_state_c4_HIL_model_experiments1(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c4_HIL_model_experiments1(S, st);
}

static void sf_opaque_terminate_c4_HIL_model_experiments1(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_HIL_model_experiments1InstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_experiments1_optimization_info();
    }

    finalize_c4_HIL_model_experiments1
      ((SFc4_HIL_model_experiments1InstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_HIL_model_experiments1
    ((SFc4_HIL_model_experiments1InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_HIL_model_experiments1(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_HIL_model_experiments1
      ((SFc4_HIL_model_experiments1InstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_HIL_model_experiments1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_experiments1_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,4,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2916884648U));
  ssSetChecksum1(S,(2335006339U));
  ssSetChecksum2(S,(3938495949U));
  ssSetChecksum3(S,(265401204U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_HIL_model_experiments1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_HIL_model_experiments1(SimStruct *S)
{
  SFc4_HIL_model_experiments1InstanceStruct *chartInstance;
  chartInstance = (SFc4_HIL_model_experiments1InstanceStruct *)utMalloc(sizeof
    (SFc4_HIL_model_experiments1InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_HIL_model_experiments1InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c4_HIL_model_experiments1;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_HIL_model_experiments1;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c4_HIL_model_experiments1;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c4_HIL_model_experiments1;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c4_HIL_model_experiments1;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c4_HIL_model_experiments1;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c4_HIL_model_experiments1;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_HIL_model_experiments1;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_HIL_model_experiments1;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_HIL_model_experiments1;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c4_HIL_model_experiments1;
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

void c4_HIL_model_experiments1_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_HIL_model_experiments1(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_HIL_model_experiments1(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_HIL_model_experiments1(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_HIL_model_experiments1_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
