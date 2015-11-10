/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Model_justmodel_sfun.h"
#include "c6_Model_justmodel.h"
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
static const char * c6_debug_family_names[25] = { "psi_s", "psi_d", "rs", "rd",
  "cs", "ss", "cd", "sd", "Rs", "Rst", "Rd", "eta_dot_d", "eta_dotdot_d",
  "nargin", "nargout", "Kp", "z2", "z1", "nu_s", "S", "eta_s", "eta_d", "nu_d",
  "nu_dot_d", "alpha_1_dot" };

/* Function Declarations */
static void initialize_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance);
static void initialize_params_c6_Model_justmodel
  (SFc6_Model_justmodelInstanceStruct *chartInstance);
static void enable_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance);
static void disable_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance);
static void c6_update_debugger_state_c6_Model_justmodel
  (SFc6_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c6_Model_justmodel
  (SFc6_Model_justmodelInstanceStruct *chartInstance);
static void set_sim_state_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct *
  chartInstance, const mxArray *c6_st);
static void finalize_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance);
static void sf_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance);
static void c6_chartstep_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance);
static void initSimStructsc6_Model_justmodel(SFc6_Model_justmodelInstanceStruct *
  chartInstance);
static void registerMessagesc6_Model_justmodel
  (SFc6_Model_justmodelInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static void c6_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_alpha_1_dot, const char_T *c6_identifier,
  real_T c6_y[3]);
static void c6_b_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId,
  real_T c6_y[3]);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real_T c6_c_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_d_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId,
  real_T c6_y[9]);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[14]);
static void c6_eml_scalar_eg(SFc6_Model_justmodelInstanceStruct *chartInstance);
static void c6_b_eml_scalar_eg(SFc6_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_e_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint8_T c6_f_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_Model_justmodel, const char_T
  *c6_identifier);
static uint8_T c6_g_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_Model_justmodelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c6_is_active_c6_Model_justmodel = 0U;
}

static void initialize_params_c6_Model_justmodel
  (SFc6_Model_justmodelInstanceStruct *chartInstance)
{
}

static void enable_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c6_update_debugger_state_c6_Model_justmodel
  (SFc6_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c6_Model_justmodel
  (SFc6_Model_justmodelInstanceStruct *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  int32_T c6_i0;
  real_T c6_u[3];
  const mxArray *c6_b_y = NULL;
  uint8_T c6_hoistedGlobal;
  uint8_T c6_b_u;
  const mxArray *c6_c_y = NULL;
  real_T (*c6_alpha_1_dot)[3];
  c6_alpha_1_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellarray(2), FALSE);
  for (c6_i0 = 0; c6_i0 < 3; c6_i0++) {
    c6_u[c6_i0] = (*c6_alpha_1_dot)[c6_i0];
  }

  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_hoistedGlobal = chartInstance->c6_is_active_c6_Model_justmodel;
  c6_b_u = c6_hoistedGlobal;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  sf_mex_assign(&c6_st, c6_y, FALSE);
  return c6_st;
}

static void set_sim_state_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct *
  chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T c6_dv0[3];
  int32_T c6_i1;
  real_T (*c6_alpha_1_dot)[3];
  c6_alpha_1_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c6_doneDoubleBufferReInit = TRUE;
  c6_u = sf_mex_dup(c6_st);
  c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 0)),
                      "alpha_1_dot", c6_dv0);
  for (c6_i1 = 0; c6_i1 < 3; c6_i1++) {
    (*c6_alpha_1_dot)[c6_i1] = c6_dv0[c6_i1];
  }

  chartInstance->c6_is_active_c6_Model_justmodel = c6_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 1)),
     "is_active_c6_Model_justmodel");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_Model_justmodel(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance)
{
}

static void sf_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c6_i2;
  int32_T c6_i3;
  int32_T c6_i4;
  int32_T c6_i5;
  int32_T c6_i6;
  int32_T c6_i7;
  int32_T c6_i8;
  int32_T c6_i9;
  int32_T c6_i10;
  int32_T c6_i11;
  real_T (*c6_nu_dot_d)[3];
  real_T (*c6_nu_d)[3];
  real_T (*c6_eta_d)[3];
  real_T (*c6_eta_s)[3];
  real_T (*c6_S)[9];
  real_T (*c6_nu_s)[3];
  real_T (*c6_z1)[3];
  real_T (*c6_alpha_1_dot)[3];
  real_T (*c6_z2)[3];
  real_T (*c6_Kp)[9];
  c6_nu_dot_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 8);
  c6_nu_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 7);
  c6_eta_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 6);
  c6_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c6_S = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 4);
  c6_nu_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c6_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c6_alpha_1_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_z2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c6_Kp = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  for (c6_i2 = 0; c6_i2 < 9; c6_i2++) {
    _SFD_DATA_RANGE_CHECK((*c6_Kp)[c6_i2], 0U);
  }

  for (c6_i3 = 0; c6_i3 < 3; c6_i3++) {
    _SFD_DATA_RANGE_CHECK((*c6_z2)[c6_i3], 1U);
  }

  for (c6_i4 = 0; c6_i4 < 3; c6_i4++) {
    _SFD_DATA_RANGE_CHECK((*c6_alpha_1_dot)[c6_i4], 2U);
  }

  for (c6_i5 = 0; c6_i5 < 3; c6_i5++) {
    _SFD_DATA_RANGE_CHECK((*c6_z1)[c6_i5], 3U);
  }

  for (c6_i6 = 0; c6_i6 < 3; c6_i6++) {
    _SFD_DATA_RANGE_CHECK((*c6_nu_s)[c6_i6], 4U);
  }

  for (c6_i7 = 0; c6_i7 < 9; c6_i7++) {
    _SFD_DATA_RANGE_CHECK((*c6_S)[c6_i7], 5U);
  }

  for (c6_i8 = 0; c6_i8 < 3; c6_i8++) {
    _SFD_DATA_RANGE_CHECK((*c6_eta_s)[c6_i8], 6U);
  }

  for (c6_i9 = 0; c6_i9 < 3; c6_i9++) {
    _SFD_DATA_RANGE_CHECK((*c6_eta_d)[c6_i9], 7U);
  }

  for (c6_i10 = 0; c6_i10 < 3; c6_i10++) {
    _SFD_DATA_RANGE_CHECK((*c6_nu_d)[c6_i10], 8U);
  }

  for (c6_i11 = 0; c6_i11 < 3; c6_i11++) {
    _SFD_DATA_RANGE_CHECK((*c6_nu_dot_d)[c6_i11], 9U);
  }

  chartInstance->c6_sfEvent = CALL_EVENT;
  c6_chartstep_c6_Model_justmodel(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Model_justmodelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c6_chartstep_c6_Model_justmodel(SFc6_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c6_i12;
  real_T c6_Kp[9];
  int32_T c6_i13;
  real_T c6_z2[3];
  int32_T c6_i14;
  real_T c6_z1[3];
  int32_T c6_i15;
  real_T c6_nu_s[3];
  int32_T c6_i16;
  real_T c6_S[9];
  int32_T c6_i17;
  real_T c6_eta_s[3];
  int32_T c6_i18;
  real_T c6_eta_d[3];
  int32_T c6_i19;
  real_T c6_nu_d[3];
  int32_T c6_i20;
  real_T c6_nu_dot_d[3];
  uint32_T c6_debug_family_var_map[25];
  real_T c6_psi_s;
  real_T c6_psi_d;
  real_T c6_rs;
  real_T c6_rd;
  real_T c6_cs;
  real_T c6_ss;
  real_T c6_cd;
  real_T c6_sd;
  real_T c6_Rs[9];
  real_T c6_Rst[9];
  real_T c6_Rd[9];
  real_T c6_eta_dot_d[3];
  real_T c6_eta_dotdot_d[3];
  real_T c6_nargin = 9.0;
  real_T c6_nargout = 1.0;
  real_T c6_alpha_1_dot[3];
  real_T c6_x;
  real_T c6_b_x;
  real_T c6_c_x;
  real_T c6_d_x;
  real_T c6_e_x;
  real_T c6_f_x;
  real_T c6_g_x;
  real_T c6_h_x;
  int32_T c6_i21;
  int32_T c6_i22;
  static real_T c6_dv1[3] = { 0.0, 0.0, 1.0 };

  int32_T c6_i23;
  int32_T c6_i24;
  int32_T c6_i25;
  int32_T c6_i26;
  int32_T c6_i27;
  int32_T c6_i28;
  int32_T c6_i29;
  real_T c6_a[9];
  int32_T c6_i30;
  real_T c6_b[3];
  int32_T c6_i31;
  int32_T c6_i32;
  int32_T c6_i33;
  real_T c6_C[3];
  int32_T c6_i34;
  int32_T c6_i35;
  int32_T c6_i36;
  int32_T c6_i37;
  int32_T c6_i38;
  int32_T c6_i39;
  int32_T c6_i40;
  int32_T c6_i41;
  real_T c6_b_b[9];
  int32_T c6_i42;
  int32_T c6_i43;
  int32_T c6_i44;
  real_T c6_y[9];
  int32_T c6_i45;
  int32_T c6_i46;
  int32_T c6_i47;
  int32_T c6_i48;
  int32_T c6_i49;
  int32_T c6_i50;
  int32_T c6_i51;
  int32_T c6_i52;
  int32_T c6_i53;
  real_T c6_b_y[3];
  int32_T c6_i54;
  int32_T c6_i55;
  int32_T c6_i56;
  int32_T c6_i57;
  int32_T c6_i58;
  int32_T c6_i59;
  int32_T c6_i60;
  int32_T c6_i61;
  int32_T c6_i62;
  int32_T c6_i63;
  int32_T c6_i64;
  int32_T c6_i65;
  int32_T c6_i66;
  int32_T c6_i67;
  int32_T c6_i68;
  int32_T c6_i69;
  int32_T c6_i70;
  int32_T c6_i71;
  int32_T c6_i72;
  int32_T c6_i73;
  int32_T c6_i74;
  int32_T c6_i75;
  int32_T c6_i76;
  int32_T c6_i77;
  int32_T c6_i78;
  int32_T c6_i79;
  int32_T c6_i80;
  int32_T c6_i81;
  int32_T c6_i82;
  int32_T c6_i83;
  int32_T c6_i84;
  int32_T c6_i85;
  real_T c6_c_y[3];
  int32_T c6_i86;
  int32_T c6_i87;
  int32_T c6_i88;
  int32_T c6_i89;
  real_T (*c6_b_alpha_1_dot)[3];
  real_T (*c6_b_nu_dot_d)[3];
  real_T (*c6_b_nu_d)[3];
  real_T (*c6_b_eta_d)[3];
  real_T (*c6_b_eta_s)[3];
  real_T (*c6_b_S)[9];
  real_T (*c6_b_nu_s)[3];
  real_T (*c6_b_z1)[3];
  real_T (*c6_b_z2)[3];
  real_T (*c6_b_Kp)[9];
  c6_b_nu_dot_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 8);
  c6_b_nu_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 7);
  c6_b_eta_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 6);
  c6_b_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c6_b_S = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 4);
  c6_b_nu_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c6_b_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c6_b_alpha_1_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_b_z2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c6_b_Kp = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  for (c6_i12 = 0; c6_i12 < 9; c6_i12++) {
    c6_Kp[c6_i12] = (*c6_b_Kp)[c6_i12];
  }

  for (c6_i13 = 0; c6_i13 < 3; c6_i13++) {
    c6_z2[c6_i13] = (*c6_b_z2)[c6_i13];
  }

  for (c6_i14 = 0; c6_i14 < 3; c6_i14++) {
    c6_z1[c6_i14] = (*c6_b_z1)[c6_i14];
  }

  for (c6_i15 = 0; c6_i15 < 3; c6_i15++) {
    c6_nu_s[c6_i15] = (*c6_b_nu_s)[c6_i15];
  }

  for (c6_i16 = 0; c6_i16 < 9; c6_i16++) {
    c6_S[c6_i16] = (*c6_b_S)[c6_i16];
  }

  for (c6_i17 = 0; c6_i17 < 3; c6_i17++) {
    c6_eta_s[c6_i17] = (*c6_b_eta_s)[c6_i17];
  }

  for (c6_i18 = 0; c6_i18 < 3; c6_i18++) {
    c6_eta_d[c6_i18] = (*c6_b_eta_d)[c6_i18];
  }

  for (c6_i19 = 0; c6_i19 < 3; c6_i19++) {
    c6_nu_d[c6_i19] = (*c6_b_nu_d)[c6_i19];
  }

  for (c6_i20 = 0; c6_i20 < 3; c6_i20++) {
    c6_nu_dot_d[c6_i20] = (*c6_b_nu_dot_d)[c6_i20];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 25U, 25U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_psi_s, 0U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_psi_d, 1U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_rs, 2U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_rd, 3U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_cs, 4U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_ss, 5U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_cd, 6U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_sd, 7U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_Rs, 8U, c6_b_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_Rst, 9U, c6_b_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_Rd, 10U, c6_b_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_eta_dot_d, 11U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_eta_dotdot_d, 12U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 13U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 14U, c6_c_sf_marshallOut,
    c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_Kp, 15U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_z2, 16U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_z1, 17U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_nu_s, 18U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_S, 19U, c6_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_eta_s, 20U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_eta_d, 21U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_nu_d, 22U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_nu_dot_d, 23U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_alpha_1_dot, 24U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  CV_EML_IF(0, 1, 0, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 6);
  c6_psi_s = c6_eta_s[2];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 10);
  CV_EML_IF(0, 1, 1, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 11);
  c6_psi_d = c6_eta_d[2];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 15);
  CV_EML_IF(0, 1, 2, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 16);
  c6_rs = c6_nu_s[2];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 20);
  CV_EML_IF(0, 1, 3, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 21);
  c6_rd = c6_nu_d[2];
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 26);
  c6_x = c6_psi_s;
  c6_cs = c6_x;
  c6_b_x = c6_cs;
  c6_cs = c6_b_x;
  c6_cs = muDoubleScalarCos(c6_cs);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 27);
  c6_c_x = c6_psi_s;
  c6_ss = c6_c_x;
  c6_d_x = c6_ss;
  c6_ss = c6_d_x;
  c6_ss = muDoubleScalarSin(c6_ss);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 28);
  c6_e_x = c6_psi_d;
  c6_cd = c6_e_x;
  c6_f_x = c6_cd;
  c6_cd = c6_f_x;
  c6_cd = muDoubleScalarCos(c6_cd);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 29);
  c6_g_x = c6_psi_d;
  c6_sd = c6_g_x;
  c6_h_x = c6_sd;
  c6_sd = c6_h_x;
  c6_sd = muDoubleScalarSin(c6_sd);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 31);
  c6_Rs[0] = c6_cs;
  c6_Rs[3] = -c6_ss;
  c6_Rs[6] = 0.0;
  c6_Rs[1] = c6_ss;
  c6_Rs[4] = c6_cs;
  c6_Rs[7] = 0.0;
  c6_i21 = 0;
  for (c6_i22 = 0; c6_i22 < 3; c6_i22++) {
    c6_Rs[c6_i21 + 2] = c6_dv1[c6_i22];
    c6_i21 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 34);
  c6_i23 = 0;
  for (c6_i24 = 0; c6_i24 < 3; c6_i24++) {
    c6_i25 = 0;
    for (c6_i26 = 0; c6_i26 < 3; c6_i26++) {
      c6_Rst[c6_i26 + c6_i23] = c6_Rs[c6_i25 + c6_i24];
      c6_i25 += 3;
    }

    c6_i23 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 35);
  c6_Rd[0] = c6_cd;
  c6_Rd[3] = -c6_sd;
  c6_Rd[6] = 0.0;
  c6_Rd[1] = c6_sd;
  c6_Rd[4] = c6_cd;
  c6_Rd[7] = 0.0;
  c6_i27 = 0;
  for (c6_i28 = 0; c6_i28 < 3; c6_i28++) {
    c6_Rd[c6_i27 + 2] = c6_dv1[c6_i28];
    c6_i27 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 40);
  for (c6_i29 = 0; c6_i29 < 9; c6_i29++) {
    c6_a[c6_i29] = c6_Rd[c6_i29];
  }

  for (c6_i30 = 0; c6_i30 < 3; c6_i30++) {
    c6_b[c6_i30] = c6_nu_d[c6_i30];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i31 = 0; c6_i31 < 3; c6_i31++) {
    c6_eta_dot_d[c6_i31] = 0.0;
  }

  for (c6_i32 = 0; c6_i32 < 3; c6_i32++) {
    c6_eta_dot_d[c6_i32] = 0.0;
  }

  for (c6_i33 = 0; c6_i33 < 3; c6_i33++) {
    c6_C[c6_i33] = c6_eta_dot_d[c6_i33];
  }

  for (c6_i34 = 0; c6_i34 < 3; c6_i34++) {
    c6_eta_dot_d[c6_i34] = c6_C[c6_i34];
  }

  for (c6_i35 = 0; c6_i35 < 3; c6_i35++) {
    c6_C[c6_i35] = c6_eta_dot_d[c6_i35];
  }

  for (c6_i36 = 0; c6_i36 < 3; c6_i36++) {
    c6_eta_dot_d[c6_i36] = c6_C[c6_i36];
  }

  for (c6_i37 = 0; c6_i37 < 3; c6_i37++) {
    c6_eta_dot_d[c6_i37] = 0.0;
    c6_i38 = 0;
    for (c6_i39 = 0; c6_i39 < 3; c6_i39++) {
      c6_eta_dot_d[c6_i37] += c6_a[c6_i38 + c6_i37] * c6_b[c6_i39];
      c6_i38 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 41);
  for (c6_i40 = 0; c6_i40 < 9; c6_i40++) {
    c6_a[c6_i40] = c6_rd * c6_Rd[c6_i40];
  }

  for (c6_i41 = 0; c6_i41 < 9; c6_i41++) {
    c6_b_b[c6_i41] = c6_S[c6_i41];
  }

  c6_b_eml_scalar_eg(chartInstance);
  c6_b_eml_scalar_eg(chartInstance);
  for (c6_i42 = 0; c6_i42 < 3; c6_i42++) {
    c6_i43 = 0;
    for (c6_i44 = 0; c6_i44 < 3; c6_i44++) {
      c6_y[c6_i43 + c6_i42] = 0.0;
      c6_i45 = 0;
      for (c6_i46 = 0; c6_i46 < 3; c6_i46++) {
        c6_y[c6_i43 + c6_i42] += c6_a[c6_i45 + c6_i42] * c6_b_b[c6_i46 + c6_i43];
        c6_i45 += 3;
      }

      c6_i43 += 3;
    }
  }

  for (c6_i47 = 0; c6_i47 < 3; c6_i47++) {
    c6_b[c6_i47] = c6_nu_d[c6_i47];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i48 = 0; c6_i48 < 3; c6_i48++) {
    c6_C[c6_i48] = 0.0;
    c6_i49 = 0;
    for (c6_i50 = 0; c6_i50 < 3; c6_i50++) {
      c6_C[c6_i48] += c6_y[c6_i49 + c6_i48] * c6_b[c6_i50];
      c6_i49 += 3;
    }
  }

  for (c6_i51 = 0; c6_i51 < 9; c6_i51++) {
    c6_a[c6_i51] = c6_Rd[c6_i51];
  }

  for (c6_i52 = 0; c6_i52 < 3; c6_i52++) {
    c6_b[c6_i52] = c6_nu_dot_d[c6_i52];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i53 = 0; c6_i53 < 3; c6_i53++) {
    c6_b_y[c6_i53] = 0.0;
    c6_i54 = 0;
    for (c6_i55 = 0; c6_i55 < 3; c6_i55++) {
      c6_b_y[c6_i53] += c6_a[c6_i54 + c6_i53] * c6_b[c6_i55];
      c6_i54 += 3;
    }
  }

  for (c6_i56 = 0; c6_i56 < 3; c6_i56++) {
    c6_eta_dotdot_d[c6_i56] = c6_C[c6_i56] + c6_b_y[c6_i56];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 42);
  for (c6_i57 = 0; c6_i57 < 9; c6_i57++) {
    c6_a[c6_i57] = c6_Kp[c6_i57];
  }

  for (c6_i58 = 0; c6_i58 < 3; c6_i58++) {
    c6_b[c6_i58] = c6_z1[c6_i58];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i59 = 0; c6_i59 < 3; c6_i59++) {
    c6_C[c6_i59] = 0.0;
    c6_i60 = 0;
    for (c6_i61 = 0; c6_i61 < 3; c6_i61++) {
      c6_C[c6_i59] += c6_a[c6_i60 + c6_i59] * c6_b[c6_i61];
      c6_i60 += 3;
    }
  }

  for (c6_i62 = 0; c6_i62 < 9; c6_i62++) {
    c6_a[c6_i62] = c6_rs * c6_S[c6_i62];
  }

  for (c6_i63 = 0; c6_i63 < 3; c6_i63++) {
    c6_b[c6_i63] = c6_z1[c6_i63];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i64 = 0; c6_i64 < 3; c6_i64++) {
    c6_b_y[c6_i64] = 0.0;
    c6_i65 = 0;
    for (c6_i66 = 0; c6_i66 < 3; c6_i66++) {
      c6_b_y[c6_i64] += c6_a[c6_i65 + c6_i64] * c6_b[c6_i66];
      c6_i65 += 3;
    }
  }

  for (c6_i67 = 0; c6_i67 < 9; c6_i67++) {
    c6_a[c6_i67] = -c6_Kp[c6_i67];
  }

  for (c6_i68 = 0; c6_i68 < 3; c6_i68++) {
    c6_C[c6_i68] = (c6_z2[c6_i68] - c6_C[c6_i68]) - c6_b_y[c6_i68];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i69 = 0; c6_i69 < 3; c6_i69++) {
    c6_b_y[c6_i69] = 0.0;
    c6_i70 = 0;
    for (c6_i71 = 0; c6_i71 < 3; c6_i71++) {
      c6_b_y[c6_i69] += c6_a[c6_i70 + c6_i69] * c6_C[c6_i71];
      c6_i70 += 3;
    }
  }

  for (c6_i72 = 0; c6_i72 < 9; c6_i72++) {
    c6_a[c6_i72] = c6_rs * c6_S[c6_i72];
  }

  for (c6_i73 = 0; c6_i73 < 9; c6_i73++) {
    c6_b_b[c6_i73] = c6_Rst[c6_i73];
  }

  c6_b_eml_scalar_eg(chartInstance);
  c6_b_eml_scalar_eg(chartInstance);
  for (c6_i74 = 0; c6_i74 < 3; c6_i74++) {
    c6_i75 = 0;
    for (c6_i76 = 0; c6_i76 < 3; c6_i76++) {
      c6_y[c6_i75 + c6_i74] = 0.0;
      c6_i77 = 0;
      for (c6_i78 = 0; c6_i78 < 3; c6_i78++) {
        c6_y[c6_i75 + c6_i74] += c6_a[c6_i77 + c6_i74] * c6_b_b[c6_i78 + c6_i75];
        c6_i77 += 3;
      }

      c6_i75 += 3;
    }
  }

  for (c6_i79 = 0; c6_i79 < 3; c6_i79++) {
    c6_b[c6_i79] = c6_eta_dot_d[c6_i79];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i80 = 0; c6_i80 < 3; c6_i80++) {
    c6_C[c6_i80] = 0.0;
    c6_i81 = 0;
    for (c6_i82 = 0; c6_i82 < 3; c6_i82++) {
      c6_C[c6_i80] += c6_y[c6_i81 + c6_i80] * c6_b[c6_i82];
      c6_i81 += 3;
    }
  }

  for (c6_i83 = 0; c6_i83 < 9; c6_i83++) {
    c6_a[c6_i83] = c6_Rst[c6_i83];
  }

  for (c6_i84 = 0; c6_i84 < 3; c6_i84++) {
    c6_b[c6_i84] = c6_eta_dotdot_d[c6_i84];
  }

  c6_eml_scalar_eg(chartInstance);
  c6_eml_scalar_eg(chartInstance);
  for (c6_i85 = 0; c6_i85 < 3; c6_i85++) {
    c6_c_y[c6_i85] = 0.0;
    c6_i86 = 0;
    for (c6_i87 = 0; c6_i87 < 3; c6_i87++) {
      c6_c_y[c6_i85] += c6_a[c6_i86 + c6_i85] * c6_b[c6_i87];
      c6_i86 += 3;
    }
  }

  for (c6_i88 = 0; c6_i88 < 3; c6_i88++) {
    c6_alpha_1_dot[c6_i88] = (c6_b_y[c6_i88] - c6_C[c6_i88]) + c6_c_y[c6_i88];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -42);
  _SFD_SYMBOL_SCOPE_POP();
  for (c6_i89 = 0; c6_i89 < 3; c6_i89++) {
    (*c6_b_alpha_1_dot)[c6_i89] = c6_alpha_1_dot[c6_i89];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
}

static void initSimStructsc6_Model_justmodel(SFc6_Model_justmodelInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc6_Model_justmodel
  (SFc6_Model_justmodelInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber)
{
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i90;
  real_T c6_b_inData[3];
  int32_T c6_i91;
  real_T c6_u[3];
  const mxArray *c6_y = NULL;
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i90 = 0; c6_i90 < 3; c6_i90++) {
    c6_b_inData[c6_i90] = (*(real_T (*)[3])c6_inData)[c6_i90];
  }

  for (c6_i91 = 0; c6_i91 < 3; c6_i91++) {
    c6_u[c6_i91] = c6_b_inData[c6_i91];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static void c6_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_alpha_1_dot, const char_T *c6_identifier,
  real_T c6_y[3])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_alpha_1_dot), &c6_thisId,
                        c6_y);
  sf_mex_destroy(&c6_alpha_1_dot);
}

static void c6_b_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId,
  real_T c6_y[3])
{
  real_T c6_dv2[3];
  int32_T c6_i92;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c6_i92 = 0; c6_i92 < 3; c6_i92++) {
    c6_y[c6_i92] = c6_dv2[c6_i92];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_alpha_1_dot;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[3];
  int32_T c6_i93;
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c6_alpha_1_dot = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_alpha_1_dot), &c6_thisId,
                        c6_y);
  sf_mex_destroy(&c6_alpha_1_dot);
  for (c6_i93 = 0; c6_i93 < 3; c6_i93++) {
    (*(real_T (*)[3])c6_outData)[c6_i93] = c6_y[c6_i93];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i94;
  int32_T c6_i95;
  int32_T c6_i96;
  real_T c6_b_inData[9];
  int32_T c6_i97;
  int32_T c6_i98;
  int32_T c6_i99;
  real_T c6_u[9];
  const mxArray *c6_y = NULL;
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_i94 = 0;
  for (c6_i95 = 0; c6_i95 < 3; c6_i95++) {
    for (c6_i96 = 0; c6_i96 < 3; c6_i96++) {
      c6_b_inData[c6_i96 + c6_i94] = (*(real_T (*)[9])c6_inData)[c6_i96 + c6_i94];
    }

    c6_i94 += 3;
  }

  c6_i97 = 0;
  for (c6_i98 = 0; c6_i98 < 3; c6_i98++) {
    for (c6_i99 = 0; c6_i99 < 3; c6_i99++) {
      c6_u[c6_i99 + c6_i97] = c6_b_inData[c6_i99 + c6_i97];
    }

    c6_i97 += 3;
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static real_T c6_c_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_nargout;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c6_nargout = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nargout), &c6_thisId);
  sf_mex_destroy(&c6_nargout);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static void c6_d_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId,
  real_T c6_y[9])
{
  real_T c6_dv3[9];
  int32_T c6_i100;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv3, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c6_i100 = 0; c6_i100 < 9; c6_i100++) {
    c6_y[c6_i100] = c6_dv3[c6_i100];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_Rd;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[9];
  int32_T c6_i101;
  int32_T c6_i102;
  int32_T c6_i103;
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c6_Rd = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_Rd), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_Rd);
  c6_i101 = 0;
  for (c6_i102 = 0; c6_i102 < 3; c6_i102++) {
    for (c6_i103 = 0; c6_i103 < 3; c6_i103++) {
      (*(real_T (*)[9])c6_outData)[c6_i103 + c6_i101] = c6_y[c6_i103 + c6_i101];
    }

    c6_i101 += 3;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

const mxArray *sf_c6_Model_justmodel_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo;
  c6_ResolvedFunctionInfo c6_info[14];
  const mxArray *c6_m0 = NULL;
  int32_T c6_i104;
  c6_ResolvedFunctionInfo *c6_r0;
  c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  c6_info_helper(c6_info);
  sf_mex_assign(&c6_m0, sf_mex_createstruct("nameCaptureInfo", 1, 14), FALSE);
  for (c6_i104 = 0; c6_i104 < 14; c6_i104++) {
    c6_r0 = &c6_info[c6_i104];
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->context)), "context", "nameCaptureInfo",
                    c6_i104);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c6_r0->name)), "name", "nameCaptureInfo", c6_i104);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c6_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c6_i104);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", c6_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->resolved)), "resolved", "nameCaptureInfo",
                    c6_i104);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c6_i104);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c6_i104);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c6_i104);
    sf_mex_addfield(c6_m0, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c6_i104);
  }

  sf_mex_assign(&c6_nameCaptureInfo, c6_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c6_nameCaptureInfo);
  return c6_nameCaptureInfo;
}

static void c6_info_helper(c6_ResolvedFunctionInfo c6_info[14])
{
  c6_info[0].context = "";
  c6_info[0].name = "length";
  c6_info[0].dominantType = "double";
  c6_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c6_info[0].fileTimeLo = 1303146206U;
  c6_info[0].fileTimeHi = 0U;
  c6_info[0].mFileTimeLo = 0U;
  c6_info[0].mFileTimeHi = 0U;
  c6_info[1].context = "";
  c6_info[1].name = "cos";
  c6_info[1].dominantType = "double";
  c6_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c6_info[1].fileTimeLo = 1343830372U;
  c6_info[1].fileTimeHi = 0U;
  c6_info[1].mFileTimeLo = 0U;
  c6_info[1].mFileTimeHi = 0U;
  c6_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c6_info[2].name = "eml_scalar_cos";
  c6_info[2].dominantType = "double";
  c6_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c6_info[2].fileTimeLo = 1286818722U;
  c6_info[2].fileTimeHi = 0U;
  c6_info[2].mFileTimeLo = 0U;
  c6_info[2].mFileTimeHi = 0U;
  c6_info[3].context = "";
  c6_info[3].name = "sin";
  c6_info[3].dominantType = "double";
  c6_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c6_info[3].fileTimeLo = 1343830386U;
  c6_info[3].fileTimeHi = 0U;
  c6_info[3].mFileTimeLo = 0U;
  c6_info[3].mFileTimeHi = 0U;
  c6_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c6_info[4].name = "eml_scalar_sin";
  c6_info[4].dominantType = "double";
  c6_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c6_info[4].fileTimeLo = 1286818736U;
  c6_info[4].fileTimeHi = 0U;
  c6_info[4].mFileTimeLo = 0U;
  c6_info[4].mFileTimeHi = 0U;
  c6_info[5].context = "";
  c6_info[5].name = "mtimes";
  c6_info[5].dominantType = "double";
  c6_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[5].fileTimeLo = 1289519692U;
  c6_info[5].fileTimeHi = 0U;
  c6_info[5].mFileTimeLo = 0U;
  c6_info[5].mFileTimeHi = 0U;
  c6_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[6].name = "eml_index_class";
  c6_info[6].dominantType = "";
  c6_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[6].fileTimeLo = 1323170578U;
  c6_info[6].fileTimeHi = 0U;
  c6_info[6].mFileTimeLo = 0U;
  c6_info[6].mFileTimeHi = 0U;
  c6_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[7].name = "eml_scalar_eg";
  c6_info[7].dominantType = "double";
  c6_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[7].fileTimeLo = 1286818796U;
  c6_info[7].fileTimeHi = 0U;
  c6_info[7].mFileTimeLo = 0U;
  c6_info[7].mFileTimeHi = 0U;
  c6_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[8].name = "eml_xgemm";
  c6_info[8].dominantType = "char";
  c6_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c6_info[8].fileTimeLo = 1299076772U;
  c6_info[8].fileTimeHi = 0U;
  c6_info[8].mFileTimeLo = 0U;
  c6_info[8].mFileTimeHi = 0U;
  c6_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c6_info[9].name = "eml_blas_inline";
  c6_info[9].dominantType = "";
  c6_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c6_info[9].fileTimeLo = 1299076768U;
  c6_info[9].fileTimeHi = 0U;
  c6_info[9].mFileTimeLo = 0U;
  c6_info[9].mFileTimeHi = 0U;
  c6_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c6_info[10].name = "mtimes";
  c6_info[10].dominantType = "double";
  c6_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c6_info[10].fileTimeLo = 1289519692U;
  c6_info[10].fileTimeHi = 0U;
  c6_info[10].mFileTimeLo = 0U;
  c6_info[10].mFileTimeHi = 0U;
  c6_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[11].name = "eml_index_class";
  c6_info[11].dominantType = "";
  c6_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c6_info[11].fileTimeLo = 1323170578U;
  c6_info[11].fileTimeHi = 0U;
  c6_info[11].mFileTimeLo = 0U;
  c6_info[11].mFileTimeHi = 0U;
  c6_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[12].name = "eml_scalar_eg";
  c6_info[12].dominantType = "double";
  c6_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c6_info[12].fileTimeLo = 1286818796U;
  c6_info[12].fileTimeHi = 0U;
  c6_info[12].mFileTimeLo = 0U;
  c6_info[12].mFileTimeHi = 0U;
  c6_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c6_info[13].name = "eml_refblas_xgemm";
  c6_info[13].dominantType = "char";
  c6_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c6_info[13].fileTimeLo = 1299076774U;
  c6_info[13].fileTimeHi = 0U;
  c6_info[13].mFileTimeLo = 0U;
  c6_info[13].mFileTimeHi = 0U;
}

static void c6_eml_scalar_eg(SFc6_Model_justmodelInstanceStruct *chartInstance)
{
}

static void c6_b_eml_scalar_eg(SFc6_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static int32_T c6_e_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i105;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i105, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i105;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint8_T c6_f_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_Model_justmodel, const char_T
  *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_Model_justmodel), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_Model_justmodel);
  return c6_y;
}

static uint8_T c6_g_emlrt_marshallIn(SFc6_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_Model_justmodelInstanceStruct
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

void sf_c6_Model_justmodel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2265239250U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(848372859U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(14645259U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3640935138U);
}

mxArray *sf_c6_Model_justmodel_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("VRXtcKU3IwjgHa6GKW3ipE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,9,3,dataFields);

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
      pr[1] = (double)(3);
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
      pr[1] = (double)(1);
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

mxArray *sf_c6_Model_justmodel_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c6_Model_justmodel(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"alpha_1_dot\",},{M[8],M[0],T\"is_active_c6_Model_justmodel\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_Model_justmodel_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_Model_justmodelInstanceStruct *chartInstance;
    chartInstance = (SFc6_Model_justmodelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Model_justmodelMachineNumber_,
           6,
           1,
           1,
           10,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"Kp");
          _SFD_SET_DATA_PROPS(1,1,1,0,"z2");
          _SFD_SET_DATA_PROPS(2,2,0,1,"alpha_1_dot");
          _SFD_SET_DATA_PROPS(3,1,1,0,"z1");
          _SFD_SET_DATA_PROPS(4,1,1,0,"nu_s");
          _SFD_SET_DATA_PROPS(5,1,1,0,"S");
          _SFD_SET_DATA_PROPS(6,1,1,0,"eta_s");
          _SFD_SET_DATA_PROPS(7,1,1,0,"eta_d");
          _SFD_SET_DATA_PROPS(8,1,1,0,"nu_d");
          _SFD_SET_DATA_PROPS(9,1,1,0,"nu_dot_d");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,677);
        _SFD_CV_INIT_EML_IF(0,1,0,90,110,133,156);
        _SFD_CV_INIT_EML_IF(0,1,1,157,177,200,223);
        _SFD_CV_INIT_EML_IF(0,1,2,224,243,262,282);
        _SFD_CV_INIT_EML_IF(0,1,3,283,302,321,341);
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
            1.0,0,0,(MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)
            c6_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c6_Kp)[9];
          real_T (*c6_z2)[3];
          real_T (*c6_alpha_1_dot)[3];
          real_T (*c6_z1)[3];
          real_T (*c6_nu_s)[3];
          real_T (*c6_S)[9];
          real_T (*c6_eta_s)[3];
          real_T (*c6_eta_d)[3];
          real_T (*c6_nu_d)[3];
          real_T (*c6_nu_dot_d)[3];
          c6_nu_dot_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 8);
          c6_nu_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 7);
          c6_eta_d = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 6);
          c6_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
          c6_S = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 4);
          c6_nu_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c6_z1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c6_alpha_1_dot = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            1);
          c6_z2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c6_Kp = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c6_Kp);
          _SFD_SET_DATA_VALUE_PTR(1U, *c6_z2);
          _SFD_SET_DATA_VALUE_PTR(2U, *c6_alpha_1_dot);
          _SFD_SET_DATA_VALUE_PTR(3U, *c6_z1);
          _SFD_SET_DATA_VALUE_PTR(4U, *c6_nu_s);
          _SFD_SET_DATA_VALUE_PTR(5U, *c6_S);
          _SFD_SET_DATA_VALUE_PTR(6U, *c6_eta_s);
          _SFD_SET_DATA_VALUE_PTR(7U, *c6_eta_d);
          _SFD_SET_DATA_VALUE_PTR(8U, *c6_nu_d);
          _SFD_SET_DATA_VALUE_PTR(9U, *c6_nu_dot_d);
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
  return "YiYKYViaUpsTRqcXREms9F";
}

static void sf_opaque_initialize_c6_Model_justmodel(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_Model_justmodelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*)
    chartInstanceVar);
  initialize_c6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c6_Model_justmodel(void *chartInstanceVar)
{
  enable_c6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c6_Model_justmodel(void *chartInstanceVar)
{
  disable_c6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c6_Model_justmodel(void *chartInstanceVar)
{
  sf_c6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c6_Model_justmodel(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c6_Model_justmodel
    ((SFc6_Model_justmodelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_Model_justmodel();/* state var info */
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

extern void sf_internal_set_sim_state_c6_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_Model_justmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c6_Model_justmodel(SimStruct* S)
{
  return sf_internal_get_sim_state_c6_Model_justmodel(S);
}

static void sf_opaque_set_sim_state_c6_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c6_Model_justmodel(S, st);
}

static void sf_opaque_terminate_c6_Model_justmodel(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_Model_justmodelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Model_justmodel_optimization_info();
    }

    finalize_c6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_Model_justmodel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_Model_justmodel((SFc6_Model_justmodelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Model_justmodel_optimization_info();
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
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,9);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 9; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(512227923U));
  ssSetChecksum1(S,(2617008737U));
  ssSetChecksum2(S,(2463148218U));
  ssSetChecksum3(S,(3707982247U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_Model_justmodel(SimStruct *S)
{
  SFc6_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc6_Model_justmodelInstanceStruct *)utMalloc(sizeof
    (SFc6_Model_justmodelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_Model_justmodelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c6_Model_justmodel;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c6_Model_justmodel;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c6_Model_justmodel;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_Model_justmodel;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_Model_justmodel;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c6_Model_justmodel;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c6_Model_justmodel;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c6_Model_justmodel;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_Model_justmodel;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_Model_justmodel;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c6_Model_justmodel;
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

void c6_Model_justmodel_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_Model_justmodel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_Model_justmodel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_Model_justmodel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_Model_justmodel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
