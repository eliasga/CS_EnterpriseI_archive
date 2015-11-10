/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_experiments2_sfun.h"
#include "c8_HIL_model_experiments2.h"
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
static const char * c8_debug_family_names[23] = { "psi_s", "nu_ship", "cs", "ss",
  "Rs", "Rst", "nargin", "nargout", "z1", "Kd", "z2", "D", "nu_s", "eta_s",
  "b_s", "M", "alpha1_dot", "tau", "a", "b", "c", "d", "e" };

/* Function Declarations */
static void initialize_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void initialize_params_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void enable_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void disable_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void c8_update_debugger_state_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void set_sim_state_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance, const mxArray
   *c8_st);
static void finalize_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void sf_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void c8_chartstep_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void initSimStructsc8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void registerMessagesc8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static void c8_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_e, const char_T *c8_identifier, real_T c8_y
  [3]);
static void c8_b_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[3]);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_c_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void c8_d_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[9]);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[14]);
static void c8_eml_scalar_eg(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance);
static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_e_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_f_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_HIL_model_experiments2, const
  char_T *c8_identifier);
static uint8_T c8_g_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void init_dsm_address_info(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c8_is_active_c8_HIL_model_experiments2 = 0U;
}

static void initialize_params_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void enable_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c8_update_debugger_state_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  int32_T c8_i0;
  real_T c8_u[3];
  const mxArray *c8_b_y = NULL;
  int32_T c8_i1;
  real_T c8_b_u[3];
  const mxArray *c8_c_y = NULL;
  int32_T c8_i2;
  real_T c8_c_u[3];
  const mxArray *c8_d_y = NULL;
  int32_T c8_i3;
  real_T c8_d_u[3];
  const mxArray *c8_e_y = NULL;
  int32_T c8_i4;
  real_T c8_e_u[3];
  const mxArray *c8_f_y = NULL;
  int32_T c8_i5;
  real_T c8_f_u[3];
  const mxArray *c8_g_y = NULL;
  uint8_T c8_hoistedGlobal;
  uint8_T c8_g_u;
  const mxArray *c8_h_y = NULL;
  real_T (*c8_tau)[3];
  real_T (*c8_e)[3];
  real_T (*c8_d)[3];
  real_T (*c8_c)[3];
  real_T (*c8_b)[3];
  real_T (*c8_a)[3];
  c8_e = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 6);
  c8_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c8_c = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_b = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c8_a = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c8_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellarray(7), FALSE);
  for (c8_i0 = 0; c8_i0 < 3; c8_i0++) {
    c8_u[c8_i0] = (*c8_a)[c8_i0];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  for (c8_i1 = 0; c8_i1 < 3; c8_i1++) {
    c8_b_u[c8_i1] = (*c8_b)[c8_i1];
  }

  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", c8_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  for (c8_i2 = 0; c8_i2 < 3; c8_i2++) {
    c8_c_u[c8_i2] = (*c8_c)[c8_i2];
  }

  c8_d_y = NULL;
  sf_mex_assign(&c8_d_y, sf_mex_create("y", c8_c_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c8_y, 2, c8_d_y);
  for (c8_i3 = 0; c8_i3 < 3; c8_i3++) {
    c8_d_u[c8_i3] = (*c8_d)[c8_i3];
  }

  c8_e_y = NULL;
  sf_mex_assign(&c8_e_y, sf_mex_create("y", c8_d_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c8_y, 3, c8_e_y);
  for (c8_i4 = 0; c8_i4 < 3; c8_i4++) {
    c8_e_u[c8_i4] = (*c8_e)[c8_i4];
  }

  c8_f_y = NULL;
  sf_mex_assign(&c8_f_y, sf_mex_create("y", c8_e_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c8_y, 4, c8_f_y);
  for (c8_i5 = 0; c8_i5 < 3; c8_i5++) {
    c8_f_u[c8_i5] = (*c8_tau)[c8_i5];
  }

  c8_g_y = NULL;
  sf_mex_assign(&c8_g_y, sf_mex_create("y", c8_f_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c8_y, 5, c8_g_y);
  c8_hoistedGlobal = chartInstance->c8_is_active_c8_HIL_model_experiments2;
  c8_g_u = c8_hoistedGlobal;
  c8_h_y = NULL;
  sf_mex_assign(&c8_h_y, sf_mex_create("y", &c8_g_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 6, c8_h_y);
  sf_mex_assign(&c8_st, c8_y, FALSE);
  return c8_st;
}

static void set_sim_state_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance, const mxArray
   *c8_st)
{
  const mxArray *c8_u;
  real_T c8_dv0[3];
  int32_T c8_i6;
  real_T c8_dv1[3];
  int32_T c8_i7;
  real_T c8_dv2[3];
  int32_T c8_i8;
  real_T c8_dv3[3];
  int32_T c8_i9;
  real_T c8_dv4[3];
  int32_T c8_i10;
  real_T c8_dv5[3];
  int32_T c8_i11;
  real_T (*c8_a)[3];
  real_T (*c8_b)[3];
  real_T (*c8_c)[3];
  real_T (*c8_d)[3];
  real_T (*c8_e)[3];
  real_T (*c8_tau)[3];
  c8_e = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 6);
  c8_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c8_c = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_b = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c8_a = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c8_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = TRUE;
  c8_u = sf_mex_dup(c8_st);
  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 0)), "a",
                      c8_dv0);
  for (c8_i6 = 0; c8_i6 < 3; c8_i6++) {
    (*c8_a)[c8_i6] = c8_dv0[c8_i6];
  }

  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 1)), "b",
                      c8_dv1);
  for (c8_i7 = 0; c8_i7 < 3; c8_i7++) {
    (*c8_b)[c8_i7] = c8_dv1[c8_i7];
  }

  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 2)), "c",
                      c8_dv2);
  for (c8_i8 = 0; c8_i8 < 3; c8_i8++) {
    (*c8_c)[c8_i8] = c8_dv2[c8_i8];
  }

  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 3)), "d",
                      c8_dv3);
  for (c8_i9 = 0; c8_i9 < 3; c8_i9++) {
    (*c8_d)[c8_i9] = c8_dv3[c8_i9];
  }

  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 4)), "e",
                      c8_dv4);
  for (c8_i10 = 0; c8_i10 < 3; c8_i10++) {
    (*c8_e)[c8_i10] = c8_dv4[c8_i10];
  }

  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 5)), "tau",
                      c8_dv5);
  for (c8_i11 = 0; c8_i11 < 3; c8_i11++) {
    (*c8_tau)[c8_i11] = c8_dv5[c8_i11];
  }

  chartInstance->c8_is_active_c8_HIL_model_experiments2 = c8_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 6)),
     "is_active_c8_HIL_model_experiments2");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_HIL_model_experiments2(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void sf_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
  int32_T c8_i12;
  int32_T c8_i13;
  int32_T c8_i14;
  int32_T c8_i15;
  int32_T c8_i16;
  int32_T c8_i17;
  int32_T c8_i18;
  int32_T c8_i19;
  int32_T c8_i20;
  int32_T c8_i21;
  int32_T c8_i22;
  int32_T c8_i23;
  int32_T c8_i24;
  int32_T c8_i25;
  int32_T c8_i26;
  real_T (*c8_e)[3];
  real_T (*c8_d)[3];
  real_T (*c8_c)[3];
  real_T (*c8_b)[3];
  real_T (*c8_a)[3];
  real_T (*c8_alpha1_dot)[3];
  real_T (*c8_M)[9];
  real_T (*c8_b_s)[3];
  real_T (*c8_eta_s)[3];
  real_T (*c8_nu_s)[3];
  real_T (*c8_D)[9];
  real_T (*c8_tau)[3];
  real_T (*c8_z2)[3];
  real_T (*c8_Kd)[9];
  real_T (*c8_z1)[3];
  c8_e = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 6);
  c8_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c8_c = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_b = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c8_a = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c8_alpha1_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 8);
  c8_M = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 7);
  c8_b_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 6);
  c8_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c8_nu_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c8_D = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 3);
  c8_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_z2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c8_Kd = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 1);
  c8_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  for (c8_i12 = 0; c8_i12 < 3; c8_i12++) {
    _SFD_DATA_RANGE_CHECK((*c8_z1)[c8_i12], 0U);
  }

  for (c8_i13 = 0; c8_i13 < 9; c8_i13++) {
    _SFD_DATA_RANGE_CHECK((*c8_Kd)[c8_i13], 1U);
  }

  for (c8_i14 = 0; c8_i14 < 3; c8_i14++) {
    _SFD_DATA_RANGE_CHECK((*c8_z2)[c8_i14], 2U);
  }

  for (c8_i15 = 0; c8_i15 < 3; c8_i15++) {
    _SFD_DATA_RANGE_CHECK((*c8_tau)[c8_i15], 3U);
  }

  for (c8_i16 = 0; c8_i16 < 9; c8_i16++) {
    _SFD_DATA_RANGE_CHECK((*c8_D)[c8_i16], 4U);
  }

  for (c8_i17 = 0; c8_i17 < 3; c8_i17++) {
    _SFD_DATA_RANGE_CHECK((*c8_nu_s)[c8_i17], 5U);
  }

  for (c8_i18 = 0; c8_i18 < 3; c8_i18++) {
    _SFD_DATA_RANGE_CHECK((*c8_eta_s)[c8_i18], 6U);
  }

  for (c8_i19 = 0; c8_i19 < 3; c8_i19++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_s)[c8_i19], 7U);
  }

  for (c8_i20 = 0; c8_i20 < 9; c8_i20++) {
    _SFD_DATA_RANGE_CHECK((*c8_M)[c8_i20], 8U);
  }

  for (c8_i21 = 0; c8_i21 < 3; c8_i21++) {
    _SFD_DATA_RANGE_CHECK((*c8_alpha1_dot)[c8_i21], 9U);
  }

  for (c8_i22 = 0; c8_i22 < 3; c8_i22++) {
    _SFD_DATA_RANGE_CHECK((*c8_a)[c8_i22], 10U);
  }

  for (c8_i23 = 0; c8_i23 < 3; c8_i23++) {
    _SFD_DATA_RANGE_CHECK((*c8_b)[c8_i23], 11U);
  }

  for (c8_i24 = 0; c8_i24 < 3; c8_i24++) {
    _SFD_DATA_RANGE_CHECK((*c8_c)[c8_i24], 12U);
  }

  for (c8_i25 = 0; c8_i25 < 3; c8_i25++) {
    _SFD_DATA_RANGE_CHECK((*c8_d)[c8_i25], 13U);
  }

  for (c8_i26 = 0; c8_i26 < 3; c8_i26++) {
    _SFD_DATA_RANGE_CHECK((*c8_e)[c8_i26], 14U);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  c8_chartstep_c8_HIL_model_experiments2(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_experiments2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c8_chartstep_c8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
  int32_T c8_i27;
  real_T c8_z1[3];
  int32_T c8_i28;
  real_T c8_Kd[9];
  int32_T c8_i29;
  real_T c8_z2[3];
  int32_T c8_i30;
  real_T c8_D[9];
  int32_T c8_i31;
  real_T c8_nu_s[3];
  int32_T c8_i32;
  real_T c8_eta_s[3];
  int32_T c8_i33;
  real_T c8_b_s[3];
  int32_T c8_i34;
  real_T c8_M[9];
  int32_T c8_i35;
  real_T c8_alpha1_dot[3];
  uint32_T c8_debug_family_var_map[23];
  real_T c8_psi_s;
  real_T c8_nu_ship[3];
  real_T c8_cs;
  real_T c8_ss;
  real_T c8_Rs[9];
  real_T c8_Rst[9];
  real_T c8_nargin = 9.0;
  real_T c8_nargout = 6.0;
  real_T c8_tau[3];
  real_T c8_a[3];
  real_T c8_b[3];
  real_T c8_c[3];
  real_T c8_d[3];
  real_T c8_e[3];
  int32_T c8_i36;
  real_T c8_x;
  real_T c8_b_x;
  real_T c8_c_x;
  real_T c8_d_x;
  int32_T c8_i37;
  int32_T c8_i38;
  static real_T c8_dv6[3] = { 0.0, 0.0, 1.0 };

  int32_T c8_i39;
  int32_T c8_i40;
  int32_T c8_i41;
  int32_T c8_i42;
  int32_T c8_i43;
  int32_T c8_i44;
  real_T c8_b_a[9];
  int32_T c8_i45;
  real_T c8_b_b[3];
  int32_T c8_i46;
  int32_T c8_i47;
  int32_T c8_i48;
  real_T c8_C[3];
  int32_T c8_i49;
  int32_T c8_i50;
  int32_T c8_i51;
  int32_T c8_i52;
  int32_T c8_i53;
  int32_T c8_i54;
  int32_T c8_i55;
  int32_T c8_i56;
  int32_T c8_i57;
  int32_T c8_i58;
  int32_T c8_i59;
  int32_T c8_i60;
  int32_T c8_i61;
  int32_T c8_i62;
  int32_T c8_i63;
  int32_T c8_i64;
  int32_T c8_i65;
  int32_T c8_i66;
  int32_T c8_i67;
  int32_T c8_i68;
  int32_T c8_i69;
  int32_T c8_i70;
  int32_T c8_i71;
  int32_T c8_i72;
  int32_T c8_i73;
  int32_T c8_i74;
  int32_T c8_i75;
  int32_T c8_i76;
  int32_T c8_i77;
  int32_T c8_i78;
  int32_T c8_i79;
  int32_T c8_i80;
  int32_T c8_i81;
  int32_T c8_i82;
  int32_T c8_i83;
  int32_T c8_i84;
  int32_T c8_i85;
  int32_T c8_i86;
  int32_T c8_i87;
  int32_T c8_i88;
  int32_T c8_i89;
  int32_T c8_i90;
  int32_T c8_i91;
  int32_T c8_i92;
  int32_T c8_i93;
  real_T (*c8_b_tau)[3];
  real_T (*c8_c_a)[3];
  real_T (*c8_c_b)[3];
  real_T (*c8_b_c)[3];
  real_T (*c8_b_d)[3];
  real_T (*c8_b_e)[3];
  real_T (*c8_b_alpha1_dot)[3];
  real_T (*c8_b_M)[9];
  real_T (*c8_b_b_s)[3];
  real_T (*c8_b_eta_s)[3];
  real_T (*c8_b_nu_s)[3];
  real_T (*c8_b_D)[9];
  real_T (*c8_b_z2)[3];
  real_T (*c8_b_Kd)[9];
  real_T (*c8_b_z1)[3];
  c8_b_e = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 6);
  c8_b_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c8_b_c = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_c_b = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c8_c_a = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c8_b_alpha1_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 8);
  c8_b_M = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 7);
  c8_b_b_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 6);
  c8_b_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c8_b_nu_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c8_b_D = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 3);
  c8_b_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_b_z2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c8_b_Kd = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  for (c8_i27 = 0; c8_i27 < 3; c8_i27++) {
    c8_z1[c8_i27] = (*c8_b_z1)[c8_i27];
  }

  for (c8_i28 = 0; c8_i28 < 9; c8_i28++) {
    c8_Kd[c8_i28] = (*c8_b_Kd)[c8_i28];
  }

  for (c8_i29 = 0; c8_i29 < 3; c8_i29++) {
    c8_z2[c8_i29] = (*c8_b_z2)[c8_i29];
  }

  for (c8_i30 = 0; c8_i30 < 9; c8_i30++) {
    c8_D[c8_i30] = (*c8_b_D)[c8_i30];
  }

  for (c8_i31 = 0; c8_i31 < 3; c8_i31++) {
    c8_nu_s[c8_i31] = (*c8_b_nu_s)[c8_i31];
  }

  for (c8_i32 = 0; c8_i32 < 3; c8_i32++) {
    c8_eta_s[c8_i32] = (*c8_b_eta_s)[c8_i32];
  }

  for (c8_i33 = 0; c8_i33 < 3; c8_i33++) {
    c8_b_s[c8_i33] = (*c8_b_b_s)[c8_i33];
  }

  for (c8_i34 = 0; c8_i34 < 9; c8_i34++) {
    c8_M[c8_i34] = (*c8_b_M)[c8_i34];
  }

  for (c8_i35 = 0; c8_i35 < 3; c8_i35++) {
    c8_alpha1_dot[c8_i35] = (*c8_b_alpha1_dot)[c8_i35];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 23U, 23U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_psi_s, 0U, c8_d_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_nu_ship, 1U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_cs, 2U, c8_d_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_ss, 3U, c8_d_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_Rs, 4U, c8_b_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_Rst, 5U, c8_b_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 6U, c8_d_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 7U, c8_d_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_z1, 8U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_Kd, 9U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_z2, 10U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_D, 11U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_nu_s, 12U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_eta_s, 13U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_b_s, 14U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_M, 15U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_alpha1_dot, 16U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_tau, 17U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_a, 18U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_b, 19U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_c, 20U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_d, 21U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_e, 22U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 4);
  CV_EML_IF(0, 1, 0, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 5);
  c8_psi_s = c8_eta_s[2];
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 9);
  CV_EML_IF(0, 1, 1, FALSE);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 12);
  for (c8_i36 = 0; c8_i36 < 3; c8_i36++) {
    c8_nu_ship[c8_i36] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 15);
  c8_x = c8_psi_s;
  c8_cs = c8_x;
  c8_b_x = c8_cs;
  c8_cs = c8_b_x;
  c8_cs = muDoubleScalarCos(c8_cs);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 16);
  c8_c_x = c8_psi_s;
  c8_ss = c8_c_x;
  c8_d_x = c8_ss;
  c8_ss = c8_d_x;
  c8_ss = muDoubleScalarSin(c8_ss);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 18);
  c8_Rs[0] = c8_cs;
  c8_Rs[3] = -c8_ss;
  c8_Rs[6] = 0.0;
  c8_Rs[1] = c8_ss;
  c8_Rs[4] = c8_cs;
  c8_Rs[7] = 0.0;
  c8_i37 = 0;
  for (c8_i38 = 0; c8_i38 < 3; c8_i38++) {
    c8_Rs[c8_i37 + 2] = c8_dv6[c8_i38];
    c8_i37 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 21);
  c8_i39 = 0;
  for (c8_i40 = 0; c8_i40 < 3; c8_i40++) {
    c8_i41 = 0;
    for (c8_i42 = 0; c8_i42 < 3; c8_i42++) {
      c8_Rst[c8_i42 + c8_i39] = c8_Rs[c8_i41 + c8_i40];
      c8_i41 += 3;
    }

    c8_i39 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 23);
  for (c8_i43 = 0; c8_i43 < 3; c8_i43++) {
    c8_a[c8_i43] = c8_z1[c8_i43];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 24);
  for (c8_i44 = 0; c8_i44 < 9; c8_i44++) {
    c8_b_a[c8_i44] = c8_Kd[c8_i44];
  }

  for (c8_i45 = 0; c8_i45 < 3; c8_i45++) {
    c8_b_b[c8_i45] = c8_z2[c8_i45];
  }

  c8_eml_scalar_eg(chartInstance);
  c8_eml_scalar_eg(chartInstance);
  for (c8_i46 = 0; c8_i46 < 3; c8_i46++) {
    c8_b[c8_i46] = 0.0;
  }

  for (c8_i47 = 0; c8_i47 < 3; c8_i47++) {
    c8_b[c8_i47] = 0.0;
  }

  for (c8_i48 = 0; c8_i48 < 3; c8_i48++) {
    c8_C[c8_i48] = c8_b[c8_i48];
  }

  for (c8_i49 = 0; c8_i49 < 3; c8_i49++) {
    c8_b[c8_i49] = c8_C[c8_i49];
  }

  for (c8_i50 = 0; c8_i50 < 3; c8_i50++) {
    c8_C[c8_i50] = c8_b[c8_i50];
  }

  for (c8_i51 = 0; c8_i51 < 3; c8_i51++) {
    c8_b[c8_i51] = c8_C[c8_i51];
  }

  for (c8_i52 = 0; c8_i52 < 3; c8_i52++) {
    c8_b[c8_i52] = 0.0;
    c8_i53 = 0;
    for (c8_i54 = 0; c8_i54 < 3; c8_i54++) {
      c8_b[c8_i52] += c8_b_a[c8_i53 + c8_i52] * c8_b_b[c8_i54];
      c8_i53 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 25);
  for (c8_i55 = 0; c8_i55 < 9; c8_i55++) {
    c8_b_a[c8_i55] = c8_D[c8_i55];
  }

  c8_eml_scalar_eg(chartInstance);
  c8_eml_scalar_eg(chartInstance);
  for (c8_i56 = 0; c8_i56 < 3; c8_i56++) {
    c8_c[c8_i56] = 0.0;
  }

  for (c8_i57 = 0; c8_i57 < 3; c8_i57++) {
    c8_c[c8_i57] = 0.0;
  }

  for (c8_i58 = 0; c8_i58 < 3; c8_i58++) {
    c8_C[c8_i58] = c8_c[c8_i58];
  }

  for (c8_i59 = 0; c8_i59 < 3; c8_i59++) {
    c8_c[c8_i59] = c8_C[c8_i59];
  }

  for (c8_i60 = 0; c8_i60 < 3; c8_i60++) {
    c8_C[c8_i60] = c8_c[c8_i60];
  }

  for (c8_i61 = 0; c8_i61 < 3; c8_i61++) {
    c8_c[c8_i61] = c8_C[c8_i61];
  }

  for (c8_i62 = 0; c8_i62 < 3; c8_i62++) {
    c8_c[c8_i62] = 0.0;
    c8_i63 = 0;
    for (c8_i64 = 0; c8_i64 < 3; c8_i64++) {
      c8_c[c8_i62] += c8_b_a[c8_i63 + c8_i62] * 0.0;
      c8_i63 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 26);
  for (c8_i65 = 0; c8_i65 < 9; c8_i65++) {
    c8_b_a[c8_i65] = c8_Rst[c8_i65];
  }

  for (c8_i66 = 0; c8_i66 < 3; c8_i66++) {
    c8_b_b[c8_i66] = c8_b_s[c8_i66];
  }

  c8_eml_scalar_eg(chartInstance);
  c8_eml_scalar_eg(chartInstance);
  for (c8_i67 = 0; c8_i67 < 3; c8_i67++) {
    c8_d[c8_i67] = 0.0;
  }

  for (c8_i68 = 0; c8_i68 < 3; c8_i68++) {
    c8_d[c8_i68] = 0.0;
  }

  for (c8_i69 = 0; c8_i69 < 3; c8_i69++) {
    c8_C[c8_i69] = c8_d[c8_i69];
  }

  for (c8_i70 = 0; c8_i70 < 3; c8_i70++) {
    c8_d[c8_i70] = c8_C[c8_i70];
  }

  for (c8_i71 = 0; c8_i71 < 3; c8_i71++) {
    c8_C[c8_i71] = c8_d[c8_i71];
  }

  for (c8_i72 = 0; c8_i72 < 3; c8_i72++) {
    c8_d[c8_i72] = c8_C[c8_i72];
  }

  for (c8_i73 = 0; c8_i73 < 3; c8_i73++) {
    c8_d[c8_i73] = 0.0;
    c8_i74 = 0;
    for (c8_i75 = 0; c8_i75 < 3; c8_i75++) {
      c8_d[c8_i73] += c8_b_a[c8_i74 + c8_i73] * c8_b_b[c8_i75];
      c8_i74 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 27);
  for (c8_i76 = 0; c8_i76 < 9; c8_i76++) {
    c8_b_a[c8_i76] = c8_M[c8_i76];
  }

  for (c8_i77 = 0; c8_i77 < 3; c8_i77++) {
    c8_b_b[c8_i77] = c8_alpha1_dot[c8_i77];
  }

  c8_eml_scalar_eg(chartInstance);
  c8_eml_scalar_eg(chartInstance);
  for (c8_i78 = 0; c8_i78 < 3; c8_i78++) {
    c8_e[c8_i78] = 0.0;
  }

  for (c8_i79 = 0; c8_i79 < 3; c8_i79++) {
    c8_e[c8_i79] = 0.0;
  }

  for (c8_i80 = 0; c8_i80 < 3; c8_i80++) {
    c8_C[c8_i80] = c8_e[c8_i80];
  }

  for (c8_i81 = 0; c8_i81 < 3; c8_i81++) {
    c8_e[c8_i81] = c8_C[c8_i81];
  }

  for (c8_i82 = 0; c8_i82 < 3; c8_i82++) {
    c8_C[c8_i82] = c8_e[c8_i82];
  }

  for (c8_i83 = 0; c8_i83 < 3; c8_i83++) {
    c8_e[c8_i83] = c8_C[c8_i83];
  }

  for (c8_i84 = 0; c8_i84 < 3; c8_i84++) {
    c8_e[c8_i84] = 0.0;
    c8_i85 = 0;
    for (c8_i86 = 0; c8_i86 < 3; c8_i86++) {
      c8_e[c8_i84] += c8_b_a[c8_i85 + c8_i84] * c8_b_b[c8_i86];
      c8_i85 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 28);
  for (c8_i87 = 0; c8_i87 < 3; c8_i87++) {
    c8_tau[c8_i87] = (((-c8_a[c8_i87] - c8_b[c8_i87]) + c8_c[c8_i87]) +
                      c8_d[c8_i87]) + c8_e[c8_i87];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -28);
  _SFD_SYMBOL_SCOPE_POP();
  for (c8_i88 = 0; c8_i88 < 3; c8_i88++) {
    (*c8_b_tau)[c8_i88] = c8_tau[c8_i88];
  }

  for (c8_i89 = 0; c8_i89 < 3; c8_i89++) {
    (*c8_c_a)[c8_i89] = c8_a[c8_i89];
  }

  for (c8_i90 = 0; c8_i90 < 3; c8_i90++) {
    (*c8_c_b)[c8_i90] = c8_b[c8_i90];
  }

  for (c8_i91 = 0; c8_i91 < 3; c8_i91++) {
    (*c8_b_c)[c8_i91] = c8_c[c8_i91];
  }

  for (c8_i92 = 0; c8_i92 < 3; c8_i92++) {
    (*c8_b_d)[c8_i92] = c8_d[c8_i92];
  }

  for (c8_i93 = 0; c8_i93 < 3; c8_i93++) {
    (*c8_b_e)[c8_i93] = c8_e[c8_i93];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
}

static void initSimStructsc8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void registerMessagesc8_HIL_model_experiments2
  (SFc8_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber)
{
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i94;
  real_T c8_b_inData[3];
  int32_T c8_i95;
  real_T c8_u[3];
  const mxArray *c8_y = NULL;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i94 = 0; c8_i94 < 3; c8_i94++) {
    c8_b_inData[c8_i94] = (*(real_T (*)[3])c8_inData)[c8_i94];
  }

  for (c8_i95 = 0; c8_i95 < 3; c8_i95++) {
    c8_u[c8_i95] = c8_b_inData[c8_i95];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static void c8_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_e, const char_T *c8_identifier, real_T c8_y
  [3])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_e), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_e);
}

static void c8_b_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[3])
{
  real_T c8_dv7[3];
  int32_T c8_i96;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv7, 1, 0, 0U, 1, 0U, 1, 3);
  for (c8_i96 = 0; c8_i96 < 3; c8_i96++) {
    c8_y[c8_i96] = c8_dv7[c8_i96];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_e;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[3];
  int32_T c8_i97;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_e = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_e), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_e);
  for (c8_i97 = 0; c8_i97 < 3; c8_i97++) {
    (*(real_T (*)[3])c8_outData)[c8_i97] = c8_y[c8_i97];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i98;
  int32_T c8_i99;
  int32_T c8_i100;
  real_T c8_b_inData[9];
  int32_T c8_i101;
  int32_T c8_i102;
  int32_T c8_i103;
  real_T c8_u[9];
  const mxArray *c8_y = NULL;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i98 = 0;
  for (c8_i99 = 0; c8_i99 < 3; c8_i99++) {
    for (c8_i100 = 0; c8_i100 < 3; c8_i100++) {
      c8_b_inData[c8_i100 + c8_i98] = (*(real_T (*)[9])c8_inData)[c8_i100 +
        c8_i98];
    }

    c8_i98 += 3;
  }

  c8_i101 = 0;
  for (c8_i102 = 0; c8_i102 < 3; c8_i102++) {
    for (c8_i103 = 0; c8_i103 < 3; c8_i103++) {
      c8_u[c8_i103 + c8_i101] = c8_b_inData[c8_i103 + c8_i101];
    }

    c8_i101 += 3;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i104;
  real_T c8_b_inData[3];
  int32_T c8_i105;
  real_T c8_u[3];
  const mxArray *c8_y = NULL;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i104 = 0; c8_i104 < 3; c8_i104++) {
    c8_b_inData[c8_i104] = (*(real_T (*)[3])c8_inData)[c8_i104];
  }

  for (c8_i105 = 0; c8_i105 < 3; c8_i105++) {
    c8_u[c8_i105] = c8_b_inData[c8_i105];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static real_T c8_c_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_nargout;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_nargout = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_nargout), &c8_thisId);
  sf_mex_destroy(&c8_nargout);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static void c8_d_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[9])
{
  real_T c8_dv8[9];
  int32_T c8_i106;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv8, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c8_i106 = 0; c8_i106 < 9; c8_i106++) {
    c8_y[c8_i106] = c8_dv8[c8_i106];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_Rst;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[9];
  int32_T c8_i107;
  int32_T c8_i108;
  int32_T c8_i109;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_Rst = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_Rst), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_Rst);
  c8_i107 = 0;
  for (c8_i108 = 0; c8_i108 < 3; c8_i108++) {
    for (c8_i109 = 0; c8_i109 < 3; c8_i109++) {
      (*(real_T (*)[9])c8_outData)[c8_i109 + c8_i107] = c8_y[c8_i109 + c8_i107];
    }

    c8_i107 += 3;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

const mxArray *sf_c8_HIL_model_experiments2_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo;
  c8_ResolvedFunctionInfo c8_info[14];
  const mxArray *c8_m0 = NULL;
  int32_T c8_i110;
  c8_ResolvedFunctionInfo *c8_r0;
  c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  c8_info_helper(c8_info);
  sf_mex_assign(&c8_m0, sf_mex_createstruct("nameCaptureInfo", 1, 14), FALSE);
  for (c8_i110 = 0; c8_i110 < 14; c8_i110++) {
    c8_r0 = &c8_info[c8_i110];
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->context)), "context", "nameCaptureInfo",
                    c8_i110);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c8_r0->name)), "name", "nameCaptureInfo", c8_i110);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c8_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c8_i110);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->resolved)), "resolved", "nameCaptureInfo",
                    c8_i110);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c8_i110);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c8_i110);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c8_i110);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c8_i110);
  }

  sf_mex_assign(&c8_nameCaptureInfo, c8_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c8_nameCaptureInfo);
  return c8_nameCaptureInfo;
}

static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[14])
{
  c8_info[0].context = "";
  c8_info[0].name = "length";
  c8_info[0].dominantType = "double";
  c8_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c8_info[0].fileTimeLo = 1303146206U;
  c8_info[0].fileTimeHi = 0U;
  c8_info[0].mFileTimeLo = 0U;
  c8_info[0].mFileTimeHi = 0U;
  c8_info[1].context = "";
  c8_info[1].name = "cos";
  c8_info[1].dominantType = "double";
  c8_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c8_info[1].fileTimeLo = 1343830372U;
  c8_info[1].fileTimeHi = 0U;
  c8_info[1].mFileTimeLo = 0U;
  c8_info[1].mFileTimeHi = 0U;
  c8_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c8_info[2].name = "eml_scalar_cos";
  c8_info[2].dominantType = "double";
  c8_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c8_info[2].fileTimeLo = 1286818722U;
  c8_info[2].fileTimeHi = 0U;
  c8_info[2].mFileTimeLo = 0U;
  c8_info[2].mFileTimeHi = 0U;
  c8_info[3].context = "";
  c8_info[3].name = "sin";
  c8_info[3].dominantType = "double";
  c8_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c8_info[3].fileTimeLo = 1343830386U;
  c8_info[3].fileTimeHi = 0U;
  c8_info[3].mFileTimeLo = 0U;
  c8_info[3].mFileTimeHi = 0U;
  c8_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c8_info[4].name = "eml_scalar_sin";
  c8_info[4].dominantType = "double";
  c8_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c8_info[4].fileTimeLo = 1286818736U;
  c8_info[4].fileTimeHi = 0U;
  c8_info[4].mFileTimeLo = 0U;
  c8_info[4].mFileTimeHi = 0U;
  c8_info[5].context = "";
  c8_info[5].name = "mtimes";
  c8_info[5].dominantType = "double";
  c8_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[5].fileTimeLo = 1289519692U;
  c8_info[5].fileTimeHi = 0U;
  c8_info[5].mFileTimeLo = 0U;
  c8_info[5].mFileTimeHi = 0U;
  c8_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[6].name = "eml_index_class";
  c8_info[6].dominantType = "";
  c8_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[6].fileTimeLo = 1323170578U;
  c8_info[6].fileTimeHi = 0U;
  c8_info[6].mFileTimeLo = 0U;
  c8_info[6].mFileTimeHi = 0U;
  c8_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[7].name = "eml_scalar_eg";
  c8_info[7].dominantType = "double";
  c8_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[7].fileTimeLo = 1286818796U;
  c8_info[7].fileTimeHi = 0U;
  c8_info[7].mFileTimeLo = 0U;
  c8_info[7].mFileTimeHi = 0U;
  c8_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[8].name = "eml_xgemm";
  c8_info[8].dominantType = "char";
  c8_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c8_info[8].fileTimeLo = 1299076772U;
  c8_info[8].fileTimeHi = 0U;
  c8_info[8].mFileTimeLo = 0U;
  c8_info[8].mFileTimeHi = 0U;
  c8_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c8_info[9].name = "eml_blas_inline";
  c8_info[9].dominantType = "";
  c8_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c8_info[9].fileTimeLo = 1299076768U;
  c8_info[9].fileTimeHi = 0U;
  c8_info[9].mFileTimeLo = 0U;
  c8_info[9].mFileTimeHi = 0U;
  c8_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c8_info[10].name = "mtimes";
  c8_info[10].dominantType = "double";
  c8_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[10].fileTimeLo = 1289519692U;
  c8_info[10].fileTimeHi = 0U;
  c8_info[10].mFileTimeLo = 0U;
  c8_info[10].mFileTimeHi = 0U;
  c8_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[11].name = "eml_index_class";
  c8_info[11].dominantType = "";
  c8_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c8_info[11].fileTimeLo = 1323170578U;
  c8_info[11].fileTimeHi = 0U;
  c8_info[11].mFileTimeLo = 0U;
  c8_info[11].mFileTimeHi = 0U;
  c8_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[12].name = "eml_scalar_eg";
  c8_info[12].dominantType = "double";
  c8_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[12].fileTimeLo = 1286818796U;
  c8_info[12].fileTimeHi = 0U;
  c8_info[12].mFileTimeLo = 0U;
  c8_info[12].mFileTimeHi = 0U;
  c8_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c8_info[13].name = "eml_refblas_xgemm";
  c8_info[13].dominantType = "char";
  c8_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c8_info[13].fileTimeLo = 1299076774U;
  c8_info[13].fileTimeHi = 0U;
  c8_info[13].mFileTimeLo = 0U;
  c8_info[13].mFileTimeHi = 0U;
}

static void c8_eml_scalar_eg(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance)
{
}

static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static int32_T c8_e_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i111;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i111, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i111;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static uint8_T c8_f_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_HIL_model_experiments2, const
  char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_HIL_model_experiments2), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_HIL_model_experiments2);
  return c8_y;
}

static uint8_T c8_g_emlrt_marshallIn(SFc8_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void init_dsm_address_info(SFc8_HIL_model_experiments2InstanceStruct
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

void sf_c8_HIL_model_experiments2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(704805204U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(994112410U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2445049934U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2534483748U);
}

mxArray *sf_c8_HIL_model_experiments2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("7vTNpa8SAfEiBnpkxMaSRE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,9,3,dataFields);

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
      pr[1] = (double)(3);
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
      pr[1] = (double)(3);
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
      pr[0] = (double)(3);
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
      pr[0] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

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
      pr[0] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c8_HIL_model_experiments2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c8_HIL_model_experiments2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[18],T\"a\",},{M[1],M[19],T\"b\",},{M[1],M[20],T\"c\",},{M[1],M[21],T\"d\",},{M[1],M[22],T\"e\",},{M[1],M[5],T\"tau\",},{M[8],M[0],T\"is_active_c8_HIL_model_experiments2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_HIL_model_experiments2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
    chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_experiments2MachineNumber_,
           8,
           1,
           1,
           15,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"z1");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Kd");
          _SFD_SET_DATA_PROPS(2,1,1,0,"z2");
          _SFD_SET_DATA_PROPS(3,2,0,1,"tau");
          _SFD_SET_DATA_PROPS(4,1,1,0,"D");
          _SFD_SET_DATA_PROPS(5,1,1,0,"nu_s");
          _SFD_SET_DATA_PROPS(6,1,1,0,"eta_s");
          _SFD_SET_DATA_PROPS(7,1,1,0,"b_s");
          _SFD_SET_DATA_PROPS(8,1,1,0,"M");
          _SFD_SET_DATA_PROPS(9,1,1,0,"alpha1_dot");
          _SFD_SET_DATA_PROPS(10,2,0,1,"a");
          _SFD_SET_DATA_PROPS(11,2,0,1,"b");
          _SFD_SET_DATA_PROPS(12,2,0,1,"c");
          _SFD_SET_DATA_PROPS(13,2,0,1,"d");
          _SFD_SET_DATA_PROPS(14,2,0,1,"e");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,424);
        _SFD_CV_INIT_EML_IF(0,1,0,95,115,138,161);
        _SFD_CV_INIT_EML_IF(0,1,1,162,182,203,234);
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
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          real_T (*c8_z1)[3];
          real_T (*c8_Kd)[9];
          real_T (*c8_z2)[3];
          real_T (*c8_tau)[3];
          real_T (*c8_D)[9];
          real_T (*c8_nu_s)[3];
          real_T (*c8_eta_s)[3];
          real_T (*c8_b_s)[3];
          real_T (*c8_M)[9];
          real_T (*c8_alpha1_dot)[3];
          real_T (*c8_a)[3];
          real_T (*c8_b)[3];
          real_T (*c8_c)[3];
          real_T (*c8_d)[3];
          real_T (*c8_e)[3];
          c8_e = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 6);
          c8_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
          c8_c = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
          c8_b = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
          c8_a = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c8_alpha1_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S,
            8);
          c8_M = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 7);
          c8_b_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 6);
          c8_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
          c8_nu_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c8_D = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 3);
          c8_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c8_z2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c8_Kd = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 1);
          c8_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c8_z1);
          _SFD_SET_DATA_VALUE_PTR(1U, *c8_Kd);
          _SFD_SET_DATA_VALUE_PTR(2U, *c8_z2);
          _SFD_SET_DATA_VALUE_PTR(3U, *c8_tau);
          _SFD_SET_DATA_VALUE_PTR(4U, *c8_D);
          _SFD_SET_DATA_VALUE_PTR(5U, *c8_nu_s);
          _SFD_SET_DATA_VALUE_PTR(6U, *c8_eta_s);
          _SFD_SET_DATA_VALUE_PTR(7U, *c8_b_s);
          _SFD_SET_DATA_VALUE_PTR(8U, *c8_M);
          _SFD_SET_DATA_VALUE_PTR(9U, *c8_alpha1_dot);
          _SFD_SET_DATA_VALUE_PTR(10U, *c8_a);
          _SFD_SET_DATA_VALUE_PTR(11U, *c8_b);
          _SFD_SET_DATA_VALUE_PTR(12U, *c8_c);
          _SFD_SET_DATA_VALUE_PTR(13U, *c8_d);
          _SFD_SET_DATA_VALUE_PTR(14U, *c8_e);
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
  return "QchYsjLOOfUF8LFomlrrIB";
}

static void sf_opaque_initialize_c8_HIL_model_experiments2(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c8_HIL_model_experiments2
    ((SFc8_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
  initialize_c8_HIL_model_experiments2
    ((SFc8_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c8_HIL_model_experiments2(void *chartInstanceVar)
{
  enable_c8_HIL_model_experiments2((SFc8_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c8_HIL_model_experiments2(void *chartInstanceVar)
{
  disable_c8_HIL_model_experiments2((SFc8_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c8_HIL_model_experiments2(void *chartInstanceVar)
{
  sf_c8_HIL_model_experiments2((SFc8_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_HIL_model_experiments2
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_HIL_model_experiments2
    ((SFc8_HIL_model_experiments2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_HIL_model_experiments2();/* state var info */
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

extern void sf_internal_set_sim_state_c8_HIL_model_experiments2(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_HIL_model_experiments2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_HIL_model_experiments2
    ((SFc8_HIL_model_experiments2InstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_HIL_model_experiments2
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c8_HIL_model_experiments2(S);
}

static void sf_opaque_set_sim_state_c8_HIL_model_experiments2(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c8_HIL_model_experiments2(S, st);
}

static void sf_opaque_terminate_c8_HIL_model_experiments2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_HIL_model_experiments2InstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_experiments2_optimization_info();
    }

    finalize_c8_HIL_model_experiments2
      ((SFc8_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_HIL_model_experiments2
    ((SFc8_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_HIL_model_experiments2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c8_HIL_model_experiments2
      ((SFc8_HIL_model_experiments2InstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_HIL_model_experiments2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_experiments2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,8,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,8,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,8);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,9);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,6);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=6; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 9; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2864961794U));
  ssSetChecksum1(S,(2603574362U));
  ssSetChecksum2(S,(2556518416U));
  ssSetChecksum3(S,(659120070U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c8_HIL_model_experiments2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_HIL_model_experiments2(SimStruct *S)
{
  SFc8_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc8_HIL_model_experiments2InstanceStruct *)utMalloc(sizeof
    (SFc8_HIL_model_experiments2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc8_HIL_model_experiments2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_HIL_model_experiments2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_HIL_model_experiments2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_HIL_model_experiments2;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c8_HIL_model_experiments2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c8_HIL_model_experiments2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_HIL_model_experiments2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_HIL_model_experiments2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_HIL_model_experiments2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_HIL_model_experiments2;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_HIL_model_experiments2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_HIL_model_experiments2;
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

void c8_HIL_model_experiments2_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_HIL_model_experiments2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_HIL_model_experiments2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_HIL_model_experiments2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_HIL_model_experiments2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
