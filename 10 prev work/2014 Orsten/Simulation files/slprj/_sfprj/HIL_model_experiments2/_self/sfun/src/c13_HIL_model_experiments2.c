/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_experiments2_sfun.h"
#include "c13_HIL_model_experiments2.h"
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
static const char * c13_debug_family_names[14] = { "psi", "r", "c", "s", "R_rev",
  "R_rev2", "nargin", "nargout", "eta_d_dot", "eta_d_dotdot", "eta_ship",
  "nu_ship", "nu_d", "nu_dot_d" };

/* Function Declarations */
static void initialize_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void initialize_params_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void enable_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void disable_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void c13_update_debugger_state_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void set_sim_state_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance, const mxArray
   *c13_st);
static void finalize_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void sf_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void c13_chartstep_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void initSimStructsc13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void registerMessagesc13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber);
static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_nu_dot_d, const char_T *c13_identifier,
  real_T c13_y[3]);
static void c13_b_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3]);
static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static real_T c13_c_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_d_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_d_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[9]);
static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static void c13_info_helper(c13_ResolvedFunctionInfo c13_info[13]);
static void c13_eml_scalar_eg(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance);
static const mxArray *c13_e_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static int32_T c13_e_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static uint8_T c13_f_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_b_is_active_c13_HIL_model_experiments2,
  const char_T *c13_identifier);
static uint8_T c13_g_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void init_dsm_address_info(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
  chartInstance->c13_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c13_is_active_c13_HIL_model_experiments2 = 0U;
}

static void initialize_params_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void enable_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c13_update_debugger_state_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
  const mxArray *c13_st;
  const mxArray *c13_y = NULL;
  int32_T c13_i0;
  real_T c13_u[3];
  const mxArray *c13_b_y = NULL;
  int32_T c13_i1;
  real_T c13_b_u[3];
  const mxArray *c13_c_y = NULL;
  uint8_T c13_hoistedGlobal;
  uint8_T c13_c_u;
  const mxArray *c13_d_y = NULL;
  real_T (*c13_nu_dot_d)[3];
  real_T (*c13_nu_d)[3];
  c13_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_st = NULL;
  c13_st = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_createcellarray(3), FALSE);
  for (c13_i0 = 0; c13_i0 < 3; c13_i0++) {
    c13_u[c13_i0] = (*c13_nu_d)[c13_i0];
  }

  c13_b_y = NULL;
  sf_mex_assign(&c13_b_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c13_y, 0, c13_b_y);
  for (c13_i1 = 0; c13_i1 < 3; c13_i1++) {
    c13_b_u[c13_i1] = (*c13_nu_dot_d)[c13_i1];
  }

  c13_c_y = NULL;
  sf_mex_assign(&c13_c_y, sf_mex_create("y", c13_b_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c13_y, 1, c13_c_y);
  c13_hoistedGlobal = chartInstance->c13_is_active_c13_HIL_model_experiments2;
  c13_c_u = c13_hoistedGlobal;
  c13_d_y = NULL;
  sf_mex_assign(&c13_d_y, sf_mex_create("y", &c13_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c13_y, 2, c13_d_y);
  sf_mex_assign(&c13_st, c13_y, FALSE);
  return c13_st;
}

static void set_sim_state_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance, const mxArray
   *c13_st)
{
  const mxArray *c13_u;
  real_T c13_dv0[3];
  int32_T c13_i2;
  real_T c13_dv1[3];
  int32_T c13_i3;
  real_T (*c13_nu_d)[3];
  real_T (*c13_nu_dot_d)[3];
  c13_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c13_doneDoubleBufferReInit = TRUE;
  c13_u = sf_mex_dup(c13_st);
  c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 0)),
                       "nu_d", c13_dv0);
  for (c13_i2 = 0; c13_i2 < 3; c13_i2++) {
    (*c13_nu_d)[c13_i2] = c13_dv0[c13_i2];
  }

  c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 1)),
                       "nu_dot_d", c13_dv1);
  for (c13_i3 = 0; c13_i3 < 3; c13_i3++) {
    (*c13_nu_dot_d)[c13_i3] = c13_dv1[c13_i3];
  }

  chartInstance->c13_is_active_c13_HIL_model_experiments2 =
    c13_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 2)),
    "is_active_c13_HIL_model_experiments2");
  sf_mex_destroy(&c13_u);
  c13_update_debugger_state_c13_HIL_model_experiments2(chartInstance);
  sf_mex_destroy(&c13_st);
}

static void finalize_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void sf_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
  int32_T c13_i4;
  int32_T c13_i5;
  int32_T c13_i6;
  int32_T c13_i7;
  int32_T c13_i8;
  int32_T c13_i9;
  real_T (*c13_nu_dot_d)[3];
  real_T (*c13_nu_ship)[3];
  real_T (*c13_eta_ship)[3];
  real_T (*c13_eta_d_dotdot)[3];
  real_T (*c13_nu_d)[3];
  real_T (*c13_eta_d_dot)[3];
  c13_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_nu_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c13_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c13_eta_d_dotdot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c13_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_eta_d_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  for (c13_i4 = 0; c13_i4 < 3; c13_i4++) {
    _SFD_DATA_RANGE_CHECK((*c13_eta_d_dot)[c13_i4], 0U);
  }

  for (c13_i5 = 0; c13_i5 < 3; c13_i5++) {
    _SFD_DATA_RANGE_CHECK((*c13_nu_d)[c13_i5], 1U);
  }

  for (c13_i6 = 0; c13_i6 < 3; c13_i6++) {
    _SFD_DATA_RANGE_CHECK((*c13_eta_d_dotdot)[c13_i6], 2U);
  }

  for (c13_i7 = 0; c13_i7 < 3; c13_i7++) {
    _SFD_DATA_RANGE_CHECK((*c13_eta_ship)[c13_i7], 3U);
  }

  for (c13_i8 = 0; c13_i8 < 3; c13_i8++) {
    _SFD_DATA_RANGE_CHECK((*c13_nu_ship)[c13_i8], 4U);
  }

  for (c13_i9 = 0; c13_i9 < 3; c13_i9++) {
    _SFD_DATA_RANGE_CHECK((*c13_nu_dot_d)[c13_i9], 5U);
  }

  chartInstance->c13_sfEvent = CALL_EVENT;
  c13_chartstep_c13_HIL_model_experiments2(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_experiments2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c13_chartstep_c13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
  int32_T c13_i10;
  real_T c13_eta_d_dot[3];
  int32_T c13_i11;
  real_T c13_eta_d_dotdot[3];
  int32_T c13_i12;
  real_T c13_eta_ship[3];
  int32_T c13_i13;
  real_T c13_nu_ship[3];
  uint32_T c13_debug_family_var_map[14];
  real_T c13_psi;
  real_T c13_r;
  real_T c13_c;
  real_T c13_s;
  real_T c13_R_rev[9];
  real_T c13_R_rev2[9];
  real_T c13_nargin = 4.0;
  real_T c13_nargout = 2.0;
  real_T c13_nu_d[3];
  real_T c13_nu_dot_d[3];
  real_T c13_x;
  real_T c13_b_x;
  real_T c13_c_x;
  real_T c13_d_x;
  int32_T c13_i14;
  int32_T c13_i15;
  static real_T c13_dv2[3] = { 0.0, 0.0, 1.0 };

  int32_T c13_i16;
  real_T c13_a[9];
  int32_T c13_i17;
  real_T c13_b[3];
  int32_T c13_i18;
  int32_T c13_i19;
  int32_T c13_i20;
  real_T c13_C[3];
  int32_T c13_i21;
  int32_T c13_i22;
  int32_T c13_i23;
  int32_T c13_i24;
  int32_T c13_i25;
  int32_T c13_i26;
  int32_T c13_i27;
  int32_T c13_i28;
  int32_T c13_i29;
  int32_T c13_i30;
  int32_T c13_i31;
  int32_T c13_i32;
  int32_T c13_i33;
  int32_T c13_i34;
  int32_T c13_i35;
  int32_T c13_i36;
  real_T c13_y[3];
  int32_T c13_i37;
  int32_T c13_i38;
  int32_T c13_i39;
  int32_T c13_i40;
  int32_T c13_i41;
  real_T (*c13_b_nu_d)[3];
  real_T (*c13_b_nu_dot_d)[3];
  real_T (*c13_b_nu_ship)[3];
  real_T (*c13_b_eta_ship)[3];
  real_T (*c13_b_eta_d_dotdot)[3];
  real_T (*c13_b_eta_d_dot)[3];
  c13_b_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_b_nu_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c13_b_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c13_b_eta_d_dotdot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c13_b_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_b_eta_d_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  for (c13_i10 = 0; c13_i10 < 3; c13_i10++) {
    c13_eta_d_dot[c13_i10] = (*c13_b_eta_d_dot)[c13_i10];
  }

  for (c13_i11 = 0; c13_i11 < 3; c13_i11++) {
    c13_eta_d_dotdot[c13_i11] = (*c13_b_eta_d_dotdot)[c13_i11];
  }

  for (c13_i12 = 0; c13_i12 < 3; c13_i12++) {
    c13_eta_ship[c13_i12] = (*c13_b_eta_ship)[c13_i12];
  }

  for (c13_i13 = 0; c13_i13 < 3; c13_i13++) {
    c13_nu_ship[c13_i13] = (*c13_b_nu_ship)[c13_i13];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 14U, 14U, c13_debug_family_names,
    c13_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_psi, 0U, c13_c_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_r, 1U, c13_c_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_c, 2U, c13_c_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_s, 3U, c13_c_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_R_rev, 4U, c13_d_sf_marshallOut,
    c13_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_R_rev2, 5U, c13_d_sf_marshallOut,
    c13_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargin, 6U, c13_c_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargout, 7U, c13_c_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_eta_d_dot, 8U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_eta_d_dotdot, 9U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_eta_ship, 10U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_nu_ship, 11U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_nu_d, 12U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_nu_dot_d, 13U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 4);
  c13_psi = c13_eta_ship[2];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 5);
  c13_r = c13_nu_ship[2];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 7);
  c13_x = c13_psi;
  c13_c = c13_x;
  c13_b_x = c13_c;
  c13_c = c13_b_x;
  c13_c = muDoubleScalarCos(c13_c);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 8);
  c13_c_x = c13_psi;
  c13_s = c13_c_x;
  c13_d_x = c13_s;
  c13_s = c13_d_x;
  c13_s = muDoubleScalarSin(c13_s);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 9);
  c13_R_rev[0] = c13_c;
  c13_R_rev[3] = c13_s;
  c13_R_rev[6] = 0.0;
  c13_R_rev[1] = -c13_s;
  c13_R_rev[4] = c13_c;
  c13_R_rev[7] = 0.0;
  c13_i14 = 0;
  for (c13_i15 = 0; c13_i15 < 3; c13_i15++) {
    c13_R_rev[c13_i14 + 2] = c13_dv2[c13_i15];
    c13_i14 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 13);
  for (c13_i16 = 0; c13_i16 < 9; c13_i16++) {
    c13_a[c13_i16] = c13_R_rev[c13_i16];
  }

  for (c13_i17 = 0; c13_i17 < 3; c13_i17++) {
    c13_b[c13_i17] = c13_eta_d_dot[c13_i17];
  }

  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i18 = 0; c13_i18 < 3; c13_i18++) {
    c13_nu_d[c13_i18] = 0.0;
  }

  for (c13_i19 = 0; c13_i19 < 3; c13_i19++) {
    c13_nu_d[c13_i19] = 0.0;
  }

  for (c13_i20 = 0; c13_i20 < 3; c13_i20++) {
    c13_C[c13_i20] = c13_nu_d[c13_i20];
  }

  for (c13_i21 = 0; c13_i21 < 3; c13_i21++) {
    c13_nu_d[c13_i21] = c13_C[c13_i21];
  }

  for (c13_i22 = 0; c13_i22 < 3; c13_i22++) {
    c13_C[c13_i22] = c13_nu_d[c13_i22];
  }

  for (c13_i23 = 0; c13_i23 < 3; c13_i23++) {
    c13_nu_d[c13_i23] = c13_C[c13_i23];
  }

  for (c13_i24 = 0; c13_i24 < 3; c13_i24++) {
    c13_nu_d[c13_i24] = 0.0;
    c13_i25 = 0;
    for (c13_i26 = 0; c13_i26 < 3; c13_i26++) {
      c13_nu_d[c13_i24] += c13_a[c13_i25 + c13_i24] * c13_b[c13_i26];
      c13_i25 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 15);
  c13_R_rev2[0] = 0.0;
  c13_R_rev2[3] = c13_r;
  c13_R_rev2[6] = 0.0;
  c13_R_rev2[1] = -c13_r;
  c13_R_rev2[4] = 0.0;
  c13_R_rev2[7] = 0.0;
  c13_i27 = 0;
  for (c13_i28 = 0; c13_i28 < 3; c13_i28++) {
    c13_R_rev2[c13_i27 + 2] = 0.0;
    c13_i27 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 17);
  for (c13_i29 = 0; c13_i29 < 9; c13_i29++) {
    c13_a[c13_i29] = c13_R_rev[c13_i29];
  }

  for (c13_i30 = 0; c13_i30 < 3; c13_i30++) {
    c13_b[c13_i30] = c13_eta_d_dotdot[c13_i30];
  }

  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i31 = 0; c13_i31 < 3; c13_i31++) {
    c13_C[c13_i31] = 0.0;
    c13_i32 = 0;
    for (c13_i33 = 0; c13_i33 < 3; c13_i33++) {
      c13_C[c13_i31] += c13_a[c13_i32 + c13_i31] * c13_b[c13_i33];
      c13_i32 += 3;
    }
  }

  for (c13_i34 = 0; c13_i34 < 9; c13_i34++) {
    c13_a[c13_i34] = c13_R_rev2[c13_i34];
  }

  for (c13_i35 = 0; c13_i35 < 3; c13_i35++) {
    c13_b[c13_i35] = c13_nu_d[c13_i35];
  }

  c13_eml_scalar_eg(chartInstance);
  c13_eml_scalar_eg(chartInstance);
  for (c13_i36 = 0; c13_i36 < 3; c13_i36++) {
    c13_y[c13_i36] = 0.0;
    c13_i37 = 0;
    for (c13_i38 = 0; c13_i38 < 3; c13_i38++) {
      c13_y[c13_i36] += c13_a[c13_i37 + c13_i36] * c13_b[c13_i38];
      c13_i37 += 3;
    }
  }

  for (c13_i39 = 0; c13_i39 < 3; c13_i39++) {
    c13_nu_dot_d[c13_i39] = c13_C[c13_i39] + c13_y[c13_i39];
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, -17);
  _SFD_SYMBOL_SCOPE_POP();
  for (c13_i40 = 0; c13_i40 < 3; c13_i40++) {
    (*c13_b_nu_d)[c13_i40] = c13_nu_d[c13_i40];
  }

  for (c13_i41 = 0; c13_i41 < 3; c13_i41++) {
    (*c13_b_nu_dot_d)[c13_i41] = c13_nu_dot_d[c13_i41];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
}

static void initSimStructsc13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void registerMessagesc13_HIL_model_experiments2
  (SFc13_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber)
{
}

static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i42;
  real_T c13_b_inData[3];
  int32_T c13_i43;
  real_T c13_u[3];
  const mxArray *c13_y = NULL;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i42 = 0; c13_i42 < 3; c13_i42++) {
    c13_b_inData[c13_i42] = (*(real_T (*)[3])c13_inData)[c13_i42];
  }

  for (c13_i43 = 0; c13_i43 < 3; c13_i43++) {
    c13_u[c13_i43] = c13_b_inData[c13_i43];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_nu_dot_d, const char_T *c13_identifier,
  real_T c13_y[3])
{
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_nu_dot_d), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_nu_dot_d);
}

static void c13_b_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3])
{
  real_T c13_dv3[3];
  int32_T c13_i44;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c13_i44 = 0; c13_i44 < 3; c13_i44++) {
    c13_y[c13_i44] = c13_dv3[c13_i44];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_nu_dot_d;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[3];
  int32_T c13_i45;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_nu_dot_d = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_nu_dot_d), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_nu_dot_d);
  for (c13_i45 = 0; c13_i45 < 3; c13_i45++) {
    (*(real_T (*)[3])c13_outData)[c13_i45] = c13_y[c13_i45];
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i46;
  real_T c13_b_inData[3];
  int32_T c13_i47;
  real_T c13_u[3];
  const mxArray *c13_y = NULL;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i46 = 0; c13_i46 < 3; c13_i46++) {
    c13_b_inData[c13_i46] = (*(real_T (*)[3])c13_inData)[c13_i46];
  }

  for (c13_i47 = 0; c13_i47 < 3; c13_i47++) {
    c13_u[c13_i47] = c13_b_inData[c13_i47];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  real_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(real_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static real_T c13_c_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  real_T c13_y;
  real_T c13_d0;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_d0, 1, 0, 0U, 0, 0U, 0);
  c13_y = c13_d0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_nargout;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_nargout = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_nargout),
    &c13_thisId);
  sf_mex_destroy(&c13_nargout);
  *(real_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_d_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i48;
  int32_T c13_i49;
  int32_T c13_i50;
  real_T c13_b_inData[9];
  int32_T c13_i51;
  int32_T c13_i52;
  int32_T c13_i53;
  real_T c13_u[9];
  const mxArray *c13_y = NULL;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_i48 = 0;
  for (c13_i49 = 0; c13_i49 < 3; c13_i49++) {
    for (c13_i50 = 0; c13_i50 < 3; c13_i50++) {
      c13_b_inData[c13_i50 + c13_i48] = (*(real_T (*)[9])c13_inData)[c13_i50 +
        c13_i48];
    }

    c13_i48 += 3;
  }

  c13_i51 = 0;
  for (c13_i52 = 0; c13_i52 < 3; c13_i52++) {
    for (c13_i53 = 0; c13_i53 < 3; c13_i53++) {
      c13_u[c13_i53 + c13_i51] = c13_b_inData[c13_i53 + c13_i51];
    }

    c13_i51 += 3;
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_d_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[9])
{
  real_T c13_dv4[9];
  int32_T c13_i54;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv4, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c13_i54 = 0; c13_i54 < 9; c13_i54++) {
    c13_y[c13_i54] = c13_dv4[c13_i54];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_R_rev2;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[9];
  int32_T c13_i55;
  int32_T c13_i56;
  int32_T c13_i57;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_R_rev2 = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_R_rev2), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_R_rev2);
  c13_i55 = 0;
  for (c13_i56 = 0; c13_i56 < 3; c13_i56++) {
    for (c13_i57 = 0; c13_i57 < 3; c13_i57++) {
      (*(real_T (*)[9])c13_outData)[c13_i57 + c13_i55] = c13_y[c13_i57 + c13_i55];
    }

    c13_i55 += 3;
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

const mxArray *sf_c13_HIL_model_experiments2_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c13_nameCaptureInfo;
  c13_ResolvedFunctionInfo c13_info[13];
  const mxArray *c13_m0 = NULL;
  int32_T c13_i58;
  c13_ResolvedFunctionInfo *c13_r0;
  c13_nameCaptureInfo = NULL;
  c13_nameCaptureInfo = NULL;
  c13_info_helper(c13_info);
  sf_mex_assign(&c13_m0, sf_mex_createstruct("nameCaptureInfo", 1, 13), FALSE);
  for (c13_i58 = 0; c13_i58 < 13; c13_i58++) {
    c13_r0 = &c13_info[c13_i58];
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c13_r0->context)), "context", "nameCaptureInfo",
                    c13_i58);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c13_r0->name)), "name", "nameCaptureInfo",
                    c13_i58);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      c13_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c13_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c13_i58);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c13_r0->resolved)), "resolved",
                    "nameCaptureInfo", c13_i58);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", &c13_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c13_i58);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", &c13_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c13_i58);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      &c13_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c13_i58);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      &c13_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c13_i58);
  }

  sf_mex_assign(&c13_nameCaptureInfo, c13_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c13_nameCaptureInfo);
  return c13_nameCaptureInfo;
}

static void c13_info_helper(c13_ResolvedFunctionInfo c13_info[13])
{
  c13_info[0].context = "";
  c13_info[0].name = "cos";
  c13_info[0].dominantType = "double";
  c13_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c13_info[0].fileTimeLo = 1343830372U;
  c13_info[0].fileTimeHi = 0U;
  c13_info[0].mFileTimeLo = 0U;
  c13_info[0].mFileTimeHi = 0U;
  c13_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c13_info[1].name = "eml_scalar_cos";
  c13_info[1].dominantType = "double";
  c13_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c13_info[1].fileTimeLo = 1286818722U;
  c13_info[1].fileTimeHi = 0U;
  c13_info[1].mFileTimeLo = 0U;
  c13_info[1].mFileTimeHi = 0U;
  c13_info[2].context = "";
  c13_info[2].name = "sin";
  c13_info[2].dominantType = "double";
  c13_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c13_info[2].fileTimeLo = 1343830386U;
  c13_info[2].fileTimeHi = 0U;
  c13_info[2].mFileTimeLo = 0U;
  c13_info[2].mFileTimeHi = 0U;
  c13_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c13_info[3].name = "eml_scalar_sin";
  c13_info[3].dominantType = "double";
  c13_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c13_info[3].fileTimeLo = 1286818736U;
  c13_info[3].fileTimeHi = 0U;
  c13_info[3].mFileTimeLo = 0U;
  c13_info[3].mFileTimeHi = 0U;
  c13_info[4].context = "";
  c13_info[4].name = "mtimes";
  c13_info[4].dominantType = "double";
  c13_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[4].fileTimeLo = 1289519692U;
  c13_info[4].fileTimeHi = 0U;
  c13_info[4].mFileTimeLo = 0U;
  c13_info[4].mFileTimeHi = 0U;
  c13_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[5].name = "eml_index_class";
  c13_info[5].dominantType = "";
  c13_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[5].fileTimeLo = 1323170578U;
  c13_info[5].fileTimeHi = 0U;
  c13_info[5].mFileTimeLo = 0U;
  c13_info[5].mFileTimeHi = 0U;
  c13_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[6].name = "eml_scalar_eg";
  c13_info[6].dominantType = "double";
  c13_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[6].fileTimeLo = 1286818796U;
  c13_info[6].fileTimeHi = 0U;
  c13_info[6].mFileTimeLo = 0U;
  c13_info[6].mFileTimeHi = 0U;
  c13_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[7].name = "eml_xgemm";
  c13_info[7].dominantType = "char";
  c13_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c13_info[7].fileTimeLo = 1299076772U;
  c13_info[7].fileTimeHi = 0U;
  c13_info[7].mFileTimeLo = 0U;
  c13_info[7].mFileTimeHi = 0U;
  c13_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c13_info[8].name = "eml_blas_inline";
  c13_info[8].dominantType = "";
  c13_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c13_info[8].fileTimeLo = 1299076768U;
  c13_info[8].fileTimeHi = 0U;
  c13_info[8].mFileTimeLo = 0U;
  c13_info[8].mFileTimeHi = 0U;
  c13_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c13_info[9].name = "mtimes";
  c13_info[9].dominantType = "double";
  c13_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[9].fileTimeLo = 1289519692U;
  c13_info[9].fileTimeHi = 0U;
  c13_info[9].mFileTimeLo = 0U;
  c13_info[9].mFileTimeHi = 0U;
  c13_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[10].name = "eml_index_class";
  c13_info[10].dominantType = "";
  c13_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[10].fileTimeLo = 1323170578U;
  c13_info[10].fileTimeHi = 0U;
  c13_info[10].mFileTimeLo = 0U;
  c13_info[10].mFileTimeHi = 0U;
  c13_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[11].name = "eml_scalar_eg";
  c13_info[11].dominantType = "double";
  c13_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[11].fileTimeLo = 1286818796U;
  c13_info[11].fileTimeHi = 0U;
  c13_info[11].mFileTimeLo = 0U;
  c13_info[11].mFileTimeHi = 0U;
  c13_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[12].name = "eml_refblas_xgemm";
  c13_info[12].dominantType = "char";
  c13_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[12].fileTimeLo = 1299076774U;
  c13_info[12].fileTimeHi = 0U;
  c13_info[12].mFileTimeLo = 0U;
  c13_info[12].mFileTimeHi = 0U;
}

static void c13_eml_scalar_eg(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance)
{
}

static const mxArray *c13_e_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(int32_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static int32_T c13_e_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  int32_T c13_y;
  int32_T c13_i59;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_i59, 1, 6, 0U, 0, 0U, 0);
  c13_y = c13_i59;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_b_sfEvent;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  int32_T c13_y;
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
    chartInstanceVoid;
  c13_b_sfEvent = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_b_sfEvent),
    &c13_thisId);
  sf_mex_destroy(&c13_b_sfEvent);
  *(int32_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static uint8_T c13_f_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_b_is_active_c13_HIL_model_experiments2,
  const char_T *c13_identifier)
{
  uint8_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_b_is_active_c13_HIL_model_experiments2), &c13_thisId);
  sf_mex_destroy(&c13_b_is_active_c13_HIL_model_experiments2);
  return c13_y;
}

static uint8_T c13_g_emlrt_marshallIn(SFc13_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  uint8_T c13_y;
  uint8_T c13_u0;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_u0, 1, 3, 0U, 0, 0U, 0);
  c13_y = c13_u0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void init_dsm_address_info(SFc13_HIL_model_experiments2InstanceStruct
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

void sf_c13_HIL_model_experiments2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(425175919U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2069451209U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(151386838U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3523368081U);
}

mxArray *sf_c13_HIL_model_experiments2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("EagqVUXLuWV3coqZnciokG");
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c13_HIL_model_experiments2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c13_HIL_model_experiments2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"nu_d\",},{M[1],M[9],T\"nu_dot_d\",},{M[8],M[0],T\"is_active_c13_HIL_model_experiments2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c13_HIL_model_experiments2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
    chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_experiments2MachineNumber_,
           13,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"eta_d_dot");
          _SFD_SET_DATA_PROPS(1,2,0,1,"nu_d");
          _SFD_SET_DATA_PROPS(2,1,1,0,"eta_d_dotdot");
          _SFD_SET_DATA_PROPS(3,1,1,0,"eta_ship");
          _SFD_SET_DATA_PROPS(4,1,1,0,"nu_ship");
          _SFD_SET_DATA_PROPS(5,2,0,1,"nu_dot_d");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,310);
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
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)
            c13_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)
            c13_sf_marshallIn);
        }

        {
          real_T (*c13_eta_d_dot)[3];
          real_T (*c13_nu_d)[3];
          real_T (*c13_eta_d_dotdot)[3];
          real_T (*c13_eta_ship)[3];
          real_T (*c13_nu_ship)[3];
          real_T (*c13_nu_dot_d)[3];
          c13_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            2);
          c13_nu_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c13_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c13_eta_d_dotdot = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 1);
          c13_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c13_eta_d_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S,
            0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c13_eta_d_dot);
          _SFD_SET_DATA_VALUE_PTR(1U, *c13_nu_d);
          _SFD_SET_DATA_VALUE_PTR(2U, *c13_eta_d_dotdot);
          _SFD_SET_DATA_VALUE_PTR(3U, *c13_eta_ship);
          _SFD_SET_DATA_VALUE_PTR(4U, *c13_nu_ship);
          _SFD_SET_DATA_VALUE_PTR(5U, *c13_nu_dot_d);
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
  return "L0iN3lNPQkmE6mwsvt6bED";
}

static void sf_opaque_initialize_c13_HIL_model_experiments2(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc13_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c13_HIL_model_experiments2
    ((SFc13_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
  initialize_c13_HIL_model_experiments2
    ((SFc13_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c13_HIL_model_experiments2(void *chartInstanceVar)
{
  enable_c13_HIL_model_experiments2((SFc13_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c13_HIL_model_experiments2(void *chartInstanceVar)
{
  disable_c13_HIL_model_experiments2((SFc13_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c13_HIL_model_experiments2(void *chartInstanceVar)
{
  sf_c13_HIL_model_experiments2((SFc13_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c13_HIL_model_experiments2
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c13_HIL_model_experiments2
    ((SFc13_HIL_model_experiments2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_HIL_model_experiments2();/* state var info */
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

extern void sf_internal_set_sim_state_c13_HIL_model_experiments2(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_HIL_model_experiments2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c13_HIL_model_experiments2
    ((SFc13_HIL_model_experiments2InstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c13_HIL_model_experiments2
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c13_HIL_model_experiments2(S);
}

static void sf_opaque_set_sim_state_c13_HIL_model_experiments2(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c13_HIL_model_experiments2(S, st);
}

static void sf_opaque_terminate_c13_HIL_model_experiments2(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc13_HIL_model_experiments2InstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_experiments2_optimization_info();
    }

    finalize_c13_HIL_model_experiments2
      ((SFc13_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc13_HIL_model_experiments2
    ((SFc13_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c13_HIL_model_experiments2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c13_HIL_model_experiments2
      ((SFc13_HIL_model_experiments2InstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c13_HIL_model_experiments2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_experiments2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      13);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,13,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,13,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,13);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,13,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,13,2);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,13);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(137575196U));
  ssSetChecksum1(S,(3049727474U));
  ssSetChecksum2(S,(3641868508U));
  ssSetChecksum3(S,(251121999U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c13_HIL_model_experiments2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c13_HIL_model_experiments2(SimStruct *S)
{
  SFc13_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc13_HIL_model_experiments2InstanceStruct *)utMalloc(sizeof
    (SFc13_HIL_model_experiments2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc13_HIL_model_experiments2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c13_HIL_model_experiments2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c13_HIL_model_experiments2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c13_HIL_model_experiments2;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c13_HIL_model_experiments2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c13_HIL_model_experiments2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c13_HIL_model_experiments2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c13_HIL_model_experiments2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c13_HIL_model_experiments2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c13_HIL_model_experiments2;
  chartInstance->chartInfo.mdlStart = mdlStart_c13_HIL_model_experiments2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c13_HIL_model_experiments2;
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

void c13_HIL_model_experiments2_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c13_HIL_model_experiments2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c13_HIL_model_experiments2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c13_HIL_model_experiments2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c13_HIL_model_experiments2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
