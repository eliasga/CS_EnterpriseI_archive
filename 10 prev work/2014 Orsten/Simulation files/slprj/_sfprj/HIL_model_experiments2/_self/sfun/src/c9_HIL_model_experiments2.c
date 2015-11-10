/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_experiments2_sfun.h"
#include "c9_HIL_model_experiments2.h"
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
static const char * c9_debug_family_names[17] = { "psi_d", "psi_s", "cd", "sd",
  "Rd", "cs", "ss", "Rs", "Rst", "nargin", "nargout", "Kp", "z1", "nu_d",
  "eta_s", "eta_d", "alpha_1" };

/* Function Declarations */
static void initialize_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void initialize_params_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void enable_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void disable_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void c9_update_debugger_state_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void set_sim_state_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance, const mxArray
   *c9_st);
static void finalize_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void sf_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void c9_chartstep_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void initSimStructsc9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void registerMessagesc9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber);
static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData);
static void c9_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_alpha_1, const char_T *c9_identifier, real_T
  c9_y[3]);
static void c9_b_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3]);
static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static real_T c9_c_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static void c9_d_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[9]);
static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[14]);
static void c9_eml_scalar_eg(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance);
static void c9_b_eml_scalar_eg(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance);
static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static int32_T c9_e_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static uint8_T c9_f_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_b_is_active_c9_HIL_model_experiments2, const
  char_T *c9_identifier);
static uint8_T c9_g_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void init_dsm_address_info(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
  chartInstance->c9_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c9_is_active_c9_HIL_model_experiments2 = 0U;
}

static void initialize_params_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void enable_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c9_update_debugger_state_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
  const mxArray *c9_st;
  const mxArray *c9_y = NULL;
  int32_T c9_i0;
  real_T c9_u[3];
  const mxArray *c9_b_y = NULL;
  uint8_T c9_hoistedGlobal;
  uint8_T c9_b_u;
  const mxArray *c9_c_y = NULL;
  real_T (*c9_alpha_1)[3];
  c9_alpha_1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_st = NULL;
  c9_st = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_createcellarray(2), FALSE);
  for (c9_i0 = 0; c9_i0 < 3; c9_i0++) {
    c9_u[c9_i0] = (*c9_alpha_1)[c9_i0];
  }

  c9_b_y = NULL;
  sf_mex_assign(&c9_b_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c9_y, 0, c9_b_y);
  c9_hoistedGlobal = chartInstance->c9_is_active_c9_HIL_model_experiments2;
  c9_b_u = c9_hoistedGlobal;
  c9_c_y = NULL;
  sf_mex_assign(&c9_c_y, sf_mex_create("y", &c9_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 1, c9_c_y);
  sf_mex_assign(&c9_st, c9_y, FALSE);
  return c9_st;
}

static void set_sim_state_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance, const mxArray
   *c9_st)
{
  const mxArray *c9_u;
  real_T c9_dv0[3];
  int32_T c9_i1;
  real_T (*c9_alpha_1)[3];
  c9_alpha_1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c9_doneDoubleBufferReInit = TRUE;
  c9_u = sf_mex_dup(c9_st);
  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 0)),
                      "alpha_1", c9_dv0);
  for (c9_i1 = 0; c9_i1 < 3; c9_i1++) {
    (*c9_alpha_1)[c9_i1] = c9_dv0[c9_i1];
  }

  chartInstance->c9_is_active_c9_HIL_model_experiments2 = c9_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 1)),
     "is_active_c9_HIL_model_experiments2");
  sf_mex_destroy(&c9_u);
  c9_update_debugger_state_c9_HIL_model_experiments2(chartInstance);
  sf_mex_destroy(&c9_st);
}

static void finalize_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void sf_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
  int32_T c9_i2;
  int32_T c9_i3;
  int32_T c9_i4;
  int32_T c9_i5;
  int32_T c9_i6;
  int32_T c9_i7;
  real_T (*c9_eta_d)[3];
  real_T (*c9_eta_s)[3];
  real_T (*c9_nu_d)[3];
  real_T (*c9_z1)[3];
  real_T (*c9_alpha_1)[3];
  real_T (*c9_Kp)[9];
  c9_eta_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c9_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c9_nu_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c9_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c9_alpha_1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_Kp = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  for (c9_i2 = 0; c9_i2 < 9; c9_i2++) {
    _SFD_DATA_RANGE_CHECK((*c9_Kp)[c9_i2], 0U);
  }

  for (c9_i3 = 0; c9_i3 < 3; c9_i3++) {
    _SFD_DATA_RANGE_CHECK((*c9_alpha_1)[c9_i3], 1U);
  }

  for (c9_i4 = 0; c9_i4 < 3; c9_i4++) {
    _SFD_DATA_RANGE_CHECK((*c9_z1)[c9_i4], 2U);
  }

  for (c9_i5 = 0; c9_i5 < 3; c9_i5++) {
    _SFD_DATA_RANGE_CHECK((*c9_nu_d)[c9_i5], 3U);
  }

  for (c9_i6 = 0; c9_i6 < 3; c9_i6++) {
    _SFD_DATA_RANGE_CHECK((*c9_eta_s)[c9_i6], 4U);
  }

  for (c9_i7 = 0; c9_i7 < 3; c9_i7++) {
    _SFD_DATA_RANGE_CHECK((*c9_eta_d)[c9_i7], 5U);
  }

  chartInstance->c9_sfEvent = CALL_EVENT;
  c9_chartstep_c9_HIL_model_experiments2(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_experiments2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c9_chartstep_c9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
  int32_T c9_i8;
  real_T c9_Kp[9];
  int32_T c9_i9;
  real_T c9_z1[3];
  int32_T c9_i10;
  real_T c9_nu_d[3];
  int32_T c9_i11;
  real_T c9_eta_s[3];
  int32_T c9_i12;
  real_T c9_eta_d[3];
  uint32_T c9_debug_family_var_map[17];
  real_T c9_psi_d;
  real_T c9_psi_s;
  real_T c9_cd;
  real_T c9_sd;
  real_T c9_Rd[9];
  real_T c9_cs;
  real_T c9_ss;
  real_T c9_Rs[9];
  real_T c9_Rst[9];
  real_T c9_nargin = 5.0;
  real_T c9_nargout = 1.0;
  real_T c9_alpha_1[3];
  real_T c9_x;
  real_T c9_b_x;
  real_T c9_c_x;
  real_T c9_d_x;
  int32_T c9_i13;
  int32_T c9_i14;
  static real_T c9_dv1[3] = { 0.0, 0.0, 1.0 };

  real_T c9_e_x;
  real_T c9_f_x;
  real_T c9_g_x;
  real_T c9_h_x;
  int32_T c9_i15;
  int32_T c9_i16;
  int32_T c9_i17;
  int32_T c9_i18;
  int32_T c9_i19;
  int32_T c9_i20;
  int32_T c9_i21;
  real_T c9_a[9];
  int32_T c9_i22;
  real_T c9_b[3];
  int32_T c9_i23;
  real_T c9_y[3];
  int32_T c9_i24;
  int32_T c9_i25;
  int32_T c9_i26;
  int32_T c9_i27;
  real_T c9_b_b[9];
  int32_T c9_i28;
  int32_T c9_i29;
  int32_T c9_i30;
  real_T c9_b_y[9];
  int32_T c9_i31;
  int32_T c9_i32;
  int32_T c9_i33;
  int32_T c9_i34;
  real_T c9_c_y[3];
  int32_T c9_i35;
  int32_T c9_i36;
  int32_T c9_i37;
  int32_T c9_i38;
  real_T (*c9_b_alpha_1)[3];
  real_T (*c9_b_eta_d)[3];
  real_T (*c9_b_eta_s)[3];
  real_T (*c9_b_nu_d)[3];
  real_T (*c9_b_z1)[3];
  real_T (*c9_b_Kp)[9];
  c9_b_eta_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c9_b_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c9_b_nu_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c9_b_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c9_b_alpha_1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_b_Kp = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  for (c9_i8 = 0; c9_i8 < 9; c9_i8++) {
    c9_Kp[c9_i8] = (*c9_b_Kp)[c9_i8];
  }

  for (c9_i9 = 0; c9_i9 < 3; c9_i9++) {
    c9_z1[c9_i9] = (*c9_b_z1)[c9_i9];
  }

  for (c9_i10 = 0; c9_i10 < 3; c9_i10++) {
    c9_nu_d[c9_i10] = (*c9_b_nu_d)[c9_i10];
  }

  for (c9_i11 = 0; c9_i11 < 3; c9_i11++) {
    c9_eta_s[c9_i11] = (*c9_b_eta_s)[c9_i11];
  }

  for (c9_i12 = 0; c9_i12 < 3; c9_i12++) {
    c9_eta_d[c9_i12] = (*c9_b_eta_d)[c9_i12];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 17U, 17U, c9_debug_family_names,
    c9_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_psi_d, 0U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_psi_s, 1U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_cd, 2U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_sd, 3U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_Rd, 4U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_cs, 5U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_ss, 6U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_Rs, 7U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_Rst, 8U, c9_b_sf_marshallOut,
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargin, 9U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargout, 10U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_Kp, 11U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_z1, 12U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_nu_d, 13U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_eta_s, 14U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_eta_d, 15U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_alpha_1, 16U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 5);
  CV_EML_IF(0, 1, 0, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 6);
  c9_psi_d = c9_eta_d[2];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 10);
  CV_EML_IF(0, 1, 1, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 11);
  c9_psi_s = c9_eta_s[2];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 16);
  c9_x = c9_psi_d;
  c9_cd = c9_x;
  c9_b_x = c9_cd;
  c9_cd = c9_b_x;
  c9_cd = muDoubleScalarCos(c9_cd);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 17);
  c9_c_x = c9_psi_d;
  c9_sd = c9_c_x;
  c9_d_x = c9_sd;
  c9_sd = c9_d_x;
  c9_sd = muDoubleScalarSin(c9_sd);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 18);
  c9_Rd[0] = c9_cd;
  c9_Rd[3] = -c9_sd;
  c9_Rd[6] = 0.0;
  c9_Rd[1] = c9_sd;
  c9_Rd[4] = c9_cd;
  c9_Rd[7] = 0.0;
  c9_i13 = 0;
  for (c9_i14 = 0; c9_i14 < 3; c9_i14++) {
    c9_Rd[c9_i13 + 2] = c9_dv1[c9_i14];
    c9_i13 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 22);
  c9_e_x = c9_psi_s;
  c9_cs = c9_e_x;
  c9_f_x = c9_cs;
  c9_cs = c9_f_x;
  c9_cs = muDoubleScalarCos(c9_cs);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 23);
  c9_g_x = c9_psi_s;
  c9_ss = c9_g_x;
  c9_h_x = c9_ss;
  c9_ss = c9_h_x;
  c9_ss = muDoubleScalarSin(c9_ss);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 24);
  c9_Rs[0] = c9_cs;
  c9_Rs[3] = -c9_ss;
  c9_Rs[6] = 0.0;
  c9_Rs[1] = c9_ss;
  c9_Rs[4] = c9_cs;
  c9_Rs[7] = 0.0;
  c9_i15 = 0;
  for (c9_i16 = 0; c9_i16 < 3; c9_i16++) {
    c9_Rs[c9_i15 + 2] = c9_dv1[c9_i16];
    c9_i15 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 27);
  c9_i17 = 0;
  for (c9_i18 = 0; c9_i18 < 3; c9_i18++) {
    c9_i19 = 0;
    for (c9_i20 = 0; c9_i20 < 3; c9_i20++) {
      c9_Rst[c9_i20 + c9_i17] = c9_Rs[c9_i19 + c9_i18];
      c9_i19 += 3;
    }

    c9_i17 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 29);
  for (c9_i21 = 0; c9_i21 < 9; c9_i21++) {
    c9_a[c9_i21] = -c9_Kp[c9_i21];
  }

  for (c9_i22 = 0; c9_i22 < 3; c9_i22++) {
    c9_b[c9_i22] = c9_z1[c9_i22];
  }

  c9_eml_scalar_eg(chartInstance);
  c9_eml_scalar_eg(chartInstance);
  for (c9_i23 = 0; c9_i23 < 3; c9_i23++) {
    c9_y[c9_i23] = 0.0;
    c9_i24 = 0;
    for (c9_i25 = 0; c9_i25 < 3; c9_i25++) {
      c9_y[c9_i23] += c9_a[c9_i24 + c9_i23] * c9_b[c9_i25];
      c9_i24 += 3;
    }
  }

  for (c9_i26 = 0; c9_i26 < 9; c9_i26++) {
    c9_a[c9_i26] = c9_Rst[c9_i26];
  }

  for (c9_i27 = 0; c9_i27 < 9; c9_i27++) {
    c9_b_b[c9_i27] = c9_Rd[c9_i27];
  }

  c9_b_eml_scalar_eg(chartInstance);
  c9_b_eml_scalar_eg(chartInstance);
  for (c9_i28 = 0; c9_i28 < 3; c9_i28++) {
    c9_i29 = 0;
    for (c9_i30 = 0; c9_i30 < 3; c9_i30++) {
      c9_b_y[c9_i29 + c9_i28] = 0.0;
      c9_i31 = 0;
      for (c9_i32 = 0; c9_i32 < 3; c9_i32++) {
        c9_b_y[c9_i29 + c9_i28] += c9_a[c9_i31 + c9_i28] * c9_b_b[c9_i32 +
          c9_i29];
        c9_i31 += 3;
      }

      c9_i29 += 3;
    }
  }

  for (c9_i33 = 0; c9_i33 < 3; c9_i33++) {
    c9_b[c9_i33] = c9_nu_d[c9_i33];
  }

  c9_eml_scalar_eg(chartInstance);
  c9_eml_scalar_eg(chartInstance);
  for (c9_i34 = 0; c9_i34 < 3; c9_i34++) {
    c9_c_y[c9_i34] = 0.0;
    c9_i35 = 0;
    for (c9_i36 = 0; c9_i36 < 3; c9_i36++) {
      c9_c_y[c9_i34] += c9_b_y[c9_i35 + c9_i34] * c9_b[c9_i36];
      c9_i35 += 3;
    }
  }

  for (c9_i37 = 0; c9_i37 < 3; c9_i37++) {
    c9_alpha_1[c9_i37] = c9_y[c9_i37] + c9_c_y[c9_i37];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, -29);
  _SFD_SYMBOL_SCOPE_POP();
  for (c9_i38 = 0; c9_i38 < 3; c9_i38++) {
    (*c9_b_alpha_1)[c9_i38] = c9_alpha_1[c9_i38];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
}

static void initSimStructsc9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void registerMessagesc9_HIL_model_experiments2
  (SFc9_HIL_model_experiments2InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber)
{
}

static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i39;
  real_T c9_b_inData[3];
  int32_T c9_i40;
  real_T c9_u[3];
  const mxArray *c9_y = NULL;
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i39 = 0; c9_i39 < 3; c9_i39++) {
    c9_b_inData[c9_i39] = (*(real_T (*)[3])c9_inData)[c9_i39];
  }

  for (c9_i40 = 0; c9_i40 < 3; c9_i40++) {
    c9_u[c9_i40] = c9_b_inData[c9_i40];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_alpha_1, const char_T *c9_identifier, real_T
  c9_y[3])
{
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_alpha_1), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_alpha_1);
}

static void c9_b_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3])
{
  real_T c9_dv2[3];
  int32_T c9_i41;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c9_i41 = 0; c9_i41 < 3; c9_i41++) {
    c9_y[c9_i41] = c9_dv2[c9_i41];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_alpha_1;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[3];
  int32_T c9_i42;
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c9_alpha_1 = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_alpha_1), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_alpha_1);
  for (c9_i42 = 0; c9_i42 < 3; c9_i42++) {
    (*(real_T (*)[3])c9_outData)[c9_i42] = c9_y[c9_i42];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i43;
  int32_T c9_i44;
  int32_T c9_i45;
  real_T c9_b_inData[9];
  int32_T c9_i46;
  int32_T c9_i47;
  int32_T c9_i48;
  real_T c9_u[9];
  const mxArray *c9_y = NULL;
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_i43 = 0;
  for (c9_i44 = 0; c9_i44 < 3; c9_i44++) {
    for (c9_i45 = 0; c9_i45 < 3; c9_i45++) {
      c9_b_inData[c9_i45 + c9_i43] = (*(real_T (*)[9])c9_inData)[c9_i45 + c9_i43];
    }

    c9_i43 += 3;
  }

  c9_i46 = 0;
  for (c9_i47 = 0; c9_i47 < 3; c9_i47++) {
    for (c9_i48 = 0; c9_i48 < 3; c9_i48++) {
      c9_u[c9_i48 + c9_i46] = c9_b_inData[c9_i48 + c9_i46];
    }

    c9_i46 += 3;
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static real_T c9_c_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d0, 1, 0, 0U, 0, 0U, 0);
  c9_y = c9_d0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_nargout;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c9_nargout = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_nargout), &c9_thisId);
  sf_mex_destroy(&c9_nargout);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static void c9_d_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[9])
{
  real_T c9_dv3[9];
  int32_T c9_i49;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv3, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c9_i49 = 0; c9_i49 < 9; c9_i49++) {
    c9_y[c9_i49] = c9_dv3[c9_i49];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_Rst;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[9];
  int32_T c9_i50;
  int32_T c9_i51;
  int32_T c9_i52;
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c9_Rst = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_Rst), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_Rst);
  c9_i50 = 0;
  for (c9_i51 = 0; c9_i51 < 3; c9_i51++) {
    for (c9_i52 = 0; c9_i52 < 3; c9_i52++) {
      (*(real_T (*)[9])c9_outData)[c9_i52 + c9_i50] = c9_y[c9_i52 + c9_i50];
    }

    c9_i50 += 3;
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

const mxArray *sf_c9_HIL_model_experiments2_get_eml_resolved_functions_info(void)
{
  const mxArray *c9_nameCaptureInfo;
  c9_ResolvedFunctionInfo c9_info[14];
  const mxArray *c9_m0 = NULL;
  int32_T c9_i53;
  c9_ResolvedFunctionInfo *c9_r0;
  c9_nameCaptureInfo = NULL;
  c9_nameCaptureInfo = NULL;
  c9_info_helper(c9_info);
  sf_mex_assign(&c9_m0, sf_mex_createstruct("nameCaptureInfo", 1, 14), FALSE);
  for (c9_i53 = 0; c9_i53 < 14; c9_i53++) {
    c9_r0 = &c9_info[c9_i53];
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->context)), "context", "nameCaptureInfo",
                    c9_i53);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c9_r0->name)), "name", "nameCaptureInfo", c9_i53);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c9_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c9_i53);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->resolved)), "resolved", "nameCaptureInfo",
                    c9_i53);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c9_i53);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c9_i53);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c9_i53);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c9_i53);
  }

  sf_mex_assign(&c9_nameCaptureInfo, c9_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c9_nameCaptureInfo);
  return c9_nameCaptureInfo;
}

static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[14])
{
  c9_info[0].context = "";
  c9_info[0].name = "length";
  c9_info[0].dominantType = "double";
  c9_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c9_info[0].fileTimeLo = 1303146206U;
  c9_info[0].fileTimeHi = 0U;
  c9_info[0].mFileTimeLo = 0U;
  c9_info[0].mFileTimeHi = 0U;
  c9_info[1].context = "";
  c9_info[1].name = "cos";
  c9_info[1].dominantType = "double";
  c9_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c9_info[1].fileTimeLo = 1343830372U;
  c9_info[1].fileTimeHi = 0U;
  c9_info[1].mFileTimeLo = 0U;
  c9_info[1].mFileTimeHi = 0U;
  c9_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c9_info[2].name = "eml_scalar_cos";
  c9_info[2].dominantType = "double";
  c9_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c9_info[2].fileTimeLo = 1286818722U;
  c9_info[2].fileTimeHi = 0U;
  c9_info[2].mFileTimeLo = 0U;
  c9_info[2].mFileTimeHi = 0U;
  c9_info[3].context = "";
  c9_info[3].name = "sin";
  c9_info[3].dominantType = "double";
  c9_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c9_info[3].fileTimeLo = 1343830386U;
  c9_info[3].fileTimeHi = 0U;
  c9_info[3].mFileTimeLo = 0U;
  c9_info[3].mFileTimeHi = 0U;
  c9_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c9_info[4].name = "eml_scalar_sin";
  c9_info[4].dominantType = "double";
  c9_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c9_info[4].fileTimeLo = 1286818736U;
  c9_info[4].fileTimeHi = 0U;
  c9_info[4].mFileTimeLo = 0U;
  c9_info[4].mFileTimeHi = 0U;
  c9_info[5].context = "";
  c9_info[5].name = "mtimes";
  c9_info[5].dominantType = "double";
  c9_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[5].fileTimeLo = 1289519692U;
  c9_info[5].fileTimeHi = 0U;
  c9_info[5].mFileTimeLo = 0U;
  c9_info[5].mFileTimeHi = 0U;
  c9_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[6].name = "eml_index_class";
  c9_info[6].dominantType = "";
  c9_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[6].fileTimeLo = 1323170578U;
  c9_info[6].fileTimeHi = 0U;
  c9_info[6].mFileTimeLo = 0U;
  c9_info[6].mFileTimeHi = 0U;
  c9_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[7].name = "eml_scalar_eg";
  c9_info[7].dominantType = "double";
  c9_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[7].fileTimeLo = 1286818796U;
  c9_info[7].fileTimeHi = 0U;
  c9_info[7].mFileTimeLo = 0U;
  c9_info[7].mFileTimeHi = 0U;
  c9_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[8].name = "eml_xgemm";
  c9_info[8].dominantType = "char";
  c9_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c9_info[8].fileTimeLo = 1299076772U;
  c9_info[8].fileTimeHi = 0U;
  c9_info[8].mFileTimeLo = 0U;
  c9_info[8].mFileTimeHi = 0U;
  c9_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c9_info[9].name = "eml_blas_inline";
  c9_info[9].dominantType = "";
  c9_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c9_info[9].fileTimeLo = 1299076768U;
  c9_info[9].fileTimeHi = 0U;
  c9_info[9].mFileTimeLo = 0U;
  c9_info[9].mFileTimeHi = 0U;
  c9_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c9_info[10].name = "mtimes";
  c9_info[10].dominantType = "double";
  c9_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[10].fileTimeLo = 1289519692U;
  c9_info[10].fileTimeHi = 0U;
  c9_info[10].mFileTimeLo = 0U;
  c9_info[10].mFileTimeHi = 0U;
  c9_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[11].name = "eml_index_class";
  c9_info[11].dominantType = "";
  c9_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[11].fileTimeLo = 1323170578U;
  c9_info[11].fileTimeHi = 0U;
  c9_info[11].mFileTimeLo = 0U;
  c9_info[11].mFileTimeHi = 0U;
  c9_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[12].name = "eml_scalar_eg";
  c9_info[12].dominantType = "double";
  c9_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[12].fileTimeLo = 1286818796U;
  c9_info[12].fileTimeHi = 0U;
  c9_info[12].mFileTimeLo = 0U;
  c9_info[12].mFileTimeHi = 0U;
  c9_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[13].name = "eml_refblas_xgemm";
  c9_info[13].dominantType = "char";
  c9_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[13].fileTimeLo = 1299076774U;
  c9_info[13].fileTimeHi = 0U;
  c9_info[13].mFileTimeLo = 0U;
  c9_info[13].mFileTimeHi = 0U;
}

static void c9_eml_scalar_eg(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance)
{
}

static void c9_b_eml_scalar_eg(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance)
{
}

static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(int32_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static int32_T c9_e_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  int32_T c9_y;
  int32_T c9_i54;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_i54, 1, 6, 0U, 0, 0U, 0);
  c9_y = c9_i54;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_sfEvent;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y;
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)chartInstanceVoid;
  c9_b_sfEvent = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_sfEvent),
    &c9_thisId);
  sf_mex_destroy(&c9_b_sfEvent);
  *(int32_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static uint8_T c9_f_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_b_is_active_c9_HIL_model_experiments2, const
  char_T *c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c9_b_is_active_c9_HIL_model_experiments2), &c9_thisId);
  sf_mex_destroy(&c9_b_is_active_c9_HIL_model_experiments2);
  return c9_y;
}

static uint8_T c9_g_emlrt_marshallIn(SFc9_HIL_model_experiments2InstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  uint8_T c9_u0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_u0, 1, 3, 0U, 0, 0U, 0);
  c9_y = c9_u0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void init_dsm_address_info(SFc9_HIL_model_experiments2InstanceStruct
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

void sf_c9_HIL_model_experiments2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3091581888U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1545513829U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2278389821U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1468613333U);
}

mxArray *sf_c9_HIL_model_experiments2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("s3Z21eWbdMKukxXIrWcsq");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
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

mxArray *sf_c9_HIL_model_experiments2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c9_HIL_model_experiments2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"alpha_1\",},{M[8],M[0],T\"is_active_c9_HIL_model_experiments2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c9_HIL_model_experiments2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
    chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_experiments2MachineNumber_,
           9,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"Kp");
          _SFD_SET_DATA_PROPS(1,2,0,1,"alpha_1");
          _SFD_SET_DATA_PROPS(2,1,1,0,"z1");
          _SFD_SET_DATA_PROPS(3,1,1,0,"nu_d");
          _SFD_SET_DATA_PROPS(4,1,1,0,"eta_s");
          _SFD_SET_DATA_PROPS(5,1,1,0,"eta_d");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,414);
        _SFD_CV_INIT_EML_IF(0,1,0,63,83,106,129);
        _SFD_CV_INIT_EML_IF(0,1,1,130,150,173,196);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c9_Kp)[9];
          real_T (*c9_alpha_1)[3];
          real_T (*c9_z1)[3];
          real_T (*c9_nu_d)[3];
          real_T (*c9_eta_s)[3];
          real_T (*c9_eta_d)[3];
          c9_eta_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c9_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c9_nu_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c9_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c9_alpha_1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c9_Kp = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c9_Kp);
          _SFD_SET_DATA_VALUE_PTR(1U, *c9_alpha_1);
          _SFD_SET_DATA_VALUE_PTR(2U, *c9_z1);
          _SFD_SET_DATA_VALUE_PTR(3U, *c9_nu_d);
          _SFD_SET_DATA_VALUE_PTR(4U, *c9_eta_s);
          _SFD_SET_DATA_VALUE_PTR(5U, *c9_eta_d);
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
  return "wLIU1FNcGVbOKxcd4UcwXB";
}

static void sf_opaque_initialize_c9_HIL_model_experiments2(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc9_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c9_HIL_model_experiments2
    ((SFc9_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
  initialize_c9_HIL_model_experiments2
    ((SFc9_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c9_HIL_model_experiments2(void *chartInstanceVar)
{
  enable_c9_HIL_model_experiments2((SFc9_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c9_HIL_model_experiments2(void *chartInstanceVar)
{
  disable_c9_HIL_model_experiments2((SFc9_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c9_HIL_model_experiments2(void *chartInstanceVar)
{
  sf_c9_HIL_model_experiments2((SFc9_HIL_model_experiments2InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c9_HIL_model_experiments2
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c9_HIL_model_experiments2
    ((SFc9_HIL_model_experiments2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_HIL_model_experiments2();/* state var info */
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

extern void sf_internal_set_sim_state_c9_HIL_model_experiments2(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_HIL_model_experiments2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c9_HIL_model_experiments2
    ((SFc9_HIL_model_experiments2InstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c9_HIL_model_experiments2
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c9_HIL_model_experiments2(S);
}

static void sf_opaque_set_sim_state_c9_HIL_model_experiments2(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c9_HIL_model_experiments2(S, st);
}

static void sf_opaque_terminate_c9_HIL_model_experiments2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc9_HIL_model_experiments2InstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_experiments2_optimization_info();
    }

    finalize_c9_HIL_model_experiments2
      ((SFc9_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc9_HIL_model_experiments2
    ((SFc9_HIL_model_experiments2InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c9_HIL_model_experiments2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c9_HIL_model_experiments2
      ((SFc9_HIL_model_experiments2InstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c9_HIL_model_experiments2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_experiments2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      9);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,9,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,9,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,9);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,9,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,9,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,9);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1015268603U));
  ssSetChecksum1(S,(3253929054U));
  ssSetChecksum2(S,(1933022004U));
  ssSetChecksum3(S,(974226328U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c9_HIL_model_experiments2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c9_HIL_model_experiments2(SimStruct *S)
{
  SFc9_HIL_model_experiments2InstanceStruct *chartInstance;
  chartInstance = (SFc9_HIL_model_experiments2InstanceStruct *)utMalloc(sizeof
    (SFc9_HIL_model_experiments2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc9_HIL_model_experiments2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c9_HIL_model_experiments2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c9_HIL_model_experiments2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c9_HIL_model_experiments2;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c9_HIL_model_experiments2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c9_HIL_model_experiments2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c9_HIL_model_experiments2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c9_HIL_model_experiments2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c9_HIL_model_experiments2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c9_HIL_model_experiments2;
  chartInstance->chartInfo.mdlStart = mdlStart_c9_HIL_model_experiments2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c9_HIL_model_experiments2;
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

void c9_HIL_model_experiments2_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c9_HIL_model_experiments2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c9_HIL_model_experiments2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c9_HIL_model_experiments2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c9_HIL_model_experiments2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
