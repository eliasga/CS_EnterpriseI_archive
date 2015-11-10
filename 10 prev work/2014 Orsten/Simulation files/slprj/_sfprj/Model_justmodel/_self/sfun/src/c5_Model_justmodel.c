/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Model_justmodel_sfun.h"
#include "c5_Model_justmodel.h"
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
static const char * c5_debug_family_names[14] = { "psi", "r", "c", "s", "R_rev",
  "R_rev2", "nargin", "nargout", "eta_d_dot", "eta_d_dotdot", "eta_ship",
  "nu_ship", "nu_d", "nu_dot_d" };

/* Function Declarations */
static void initialize_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance);
static void initialize_params_c5_Model_justmodel
  (SFc5_Model_justmodelInstanceStruct *chartInstance);
static void enable_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance);
static void disable_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance);
static void c5_update_debugger_state_c5_Model_justmodel
  (SFc5_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_Model_justmodel
  (SFc5_Model_justmodelInstanceStruct *chartInstance);
static void set_sim_state_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct *
  chartInstance, const mxArray *c5_st);
static void finalize_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance);
static void sf_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance);
static void c5_chartstep_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance);
static void initSimStructsc5_Model_justmodel(SFc5_Model_justmodelInstanceStruct *
  chartInstance);
static void registerMessagesc5_Model_justmodel
  (SFc5_Model_justmodelInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static void c5_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_nu_dot_d, const char_T *c5_identifier,
  real_T c5_y[3]);
static void c5_b_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[3]);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_c_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_d_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[9]);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_info_helper(c5_ResolvedFunctionInfo c5_info[13]);
static void c5_eml_scalar_eg(SFc5_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_e_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_f_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_Model_justmodel, const char_T
  *c5_identifier);
static uint8_T c5_g_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_Model_justmodelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance)
{
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c5_is_active_c5_Model_justmodel = 0U;
}

static void initialize_params_c5_Model_justmodel
  (SFc5_Model_justmodelInstanceStruct *chartInstance)
{
}

static void enable_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c5_update_debugger_state_c5_Model_justmodel
  (SFc5_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c5_Model_justmodel
  (SFc5_Model_justmodelInstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  int32_T c5_i0;
  real_T c5_u[3];
  const mxArray *c5_b_y = NULL;
  int32_T c5_i1;
  real_T c5_b_u[3];
  const mxArray *c5_c_y = NULL;
  uint8_T c5_hoistedGlobal;
  uint8_T c5_c_u;
  const mxArray *c5_d_y = NULL;
  real_T (*c5_nu_dot_d)[3];
  real_T (*c5_nu_d)[3];
  c5_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c5_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellarray(3), FALSE);
  for (c5_i0 = 0; c5_i0 < 3; c5_i0++) {
    c5_u[c5_i0] = (*c5_nu_d)[c5_i0];
  }

  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  for (c5_i1 = 0; c5_i1 < 3; c5_i1++) {
    c5_b_u[c5_i1] = (*c5_nu_dot_d)[c5_i1];
  }

  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", c5_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_hoistedGlobal = chartInstance->c5_is_active_c5_Model_justmodel;
  c5_c_u = c5_hoistedGlobal;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c5_y, 2, c5_d_y);
  sf_mex_assign(&c5_st, c5_y, FALSE);
  return c5_st;
}

static void set_sim_state_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct *
  chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  real_T c5_dv0[3];
  int32_T c5_i2;
  real_T c5_dv1[3];
  int32_T c5_i3;
  real_T (*c5_nu_d)[3];
  real_T (*c5_nu_dot_d)[3];
  c5_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c5_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c5_doneDoubleBufferReInit = TRUE;
  c5_u = sf_mex_dup(c5_st);
  c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 0)), "nu_d",
                      c5_dv0);
  for (c5_i2 = 0; c5_i2 < 3; c5_i2++) {
    (*c5_nu_d)[c5_i2] = c5_dv0[c5_i2];
  }

  c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 1)),
                      "nu_dot_d", c5_dv1);
  for (c5_i3 = 0; c5_i3 < 3; c5_i3++) {
    (*c5_nu_dot_d)[c5_i3] = c5_dv1[c5_i3];
  }

  chartInstance->c5_is_active_c5_Model_justmodel = c5_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 2)),
     "is_active_c5_Model_justmodel");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_Model_justmodel(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance)
{
}

static void sf_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c5_i4;
  int32_T c5_i5;
  int32_T c5_i6;
  int32_T c5_i7;
  int32_T c5_i8;
  int32_T c5_i9;
  real_T (*c5_nu_dot_d)[3];
  real_T (*c5_nu_ship)[3];
  real_T (*c5_eta_ship)[3];
  real_T (*c5_eta_d_dotdot)[3];
  real_T (*c5_nu_d)[3];
  real_T (*c5_eta_d_dot)[3];
  c5_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c5_nu_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c5_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c5_eta_d_dotdot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c5_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_eta_d_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  for (c5_i4 = 0; c5_i4 < 3; c5_i4++) {
    _SFD_DATA_RANGE_CHECK((*c5_eta_d_dot)[c5_i4], 0U);
  }

  for (c5_i5 = 0; c5_i5 < 3; c5_i5++) {
    _SFD_DATA_RANGE_CHECK((*c5_nu_d)[c5_i5], 1U);
  }

  for (c5_i6 = 0; c5_i6 < 3; c5_i6++) {
    _SFD_DATA_RANGE_CHECK((*c5_eta_d_dotdot)[c5_i6], 2U);
  }

  for (c5_i7 = 0; c5_i7 < 3; c5_i7++) {
    _SFD_DATA_RANGE_CHECK((*c5_eta_ship)[c5_i7], 3U);
  }

  for (c5_i8 = 0; c5_i8 < 3; c5_i8++) {
    _SFD_DATA_RANGE_CHECK((*c5_nu_ship)[c5_i8], 4U);
  }

  for (c5_i9 = 0; c5_i9 < 3; c5_i9++) {
    _SFD_DATA_RANGE_CHECK((*c5_nu_dot_d)[c5_i9], 5U);
  }

  chartInstance->c5_sfEvent = CALL_EVENT;
  c5_chartstep_c5_Model_justmodel(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Model_justmodelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c5_chartstep_c5_Model_justmodel(SFc5_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c5_i10;
  real_T c5_eta_d_dot[3];
  int32_T c5_i11;
  real_T c5_eta_d_dotdot[3];
  int32_T c5_i12;
  real_T c5_eta_ship[3];
  int32_T c5_i13;
  real_T c5_nu_ship[3];
  uint32_T c5_debug_family_var_map[14];
  real_T c5_psi;
  real_T c5_r;
  real_T c5_c;
  real_T c5_s;
  real_T c5_R_rev[9];
  real_T c5_R_rev2[9];
  real_T c5_nargin = 4.0;
  real_T c5_nargout = 2.0;
  real_T c5_nu_d[3];
  real_T c5_nu_dot_d[3];
  real_T c5_x;
  real_T c5_b_x;
  real_T c5_c_x;
  real_T c5_d_x;
  int32_T c5_i14;
  int32_T c5_i15;
  static real_T c5_dv2[3] = { 0.0, 0.0, 1.0 };

  int32_T c5_i16;
  real_T c5_a[9];
  int32_T c5_i17;
  real_T c5_b[3];
  int32_T c5_i18;
  int32_T c5_i19;
  int32_T c5_i20;
  real_T c5_C[3];
  int32_T c5_i21;
  int32_T c5_i22;
  int32_T c5_i23;
  int32_T c5_i24;
  int32_T c5_i25;
  int32_T c5_i26;
  int32_T c5_i27;
  int32_T c5_i28;
  int32_T c5_i29;
  int32_T c5_i30;
  int32_T c5_i31;
  int32_T c5_i32;
  int32_T c5_i33;
  int32_T c5_i34;
  int32_T c5_i35;
  int32_T c5_i36;
  real_T c5_y[3];
  int32_T c5_i37;
  int32_T c5_i38;
  int32_T c5_i39;
  int32_T c5_i40;
  int32_T c5_i41;
  real_T (*c5_b_nu_d)[3];
  real_T (*c5_b_nu_dot_d)[3];
  real_T (*c5_b_nu_ship)[3];
  real_T (*c5_b_eta_ship)[3];
  real_T (*c5_b_eta_d_dotdot)[3];
  real_T (*c5_b_eta_d_dot)[3];
  c5_b_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c5_b_nu_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c5_b_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c5_b_eta_d_dotdot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c5_b_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_b_eta_d_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  for (c5_i10 = 0; c5_i10 < 3; c5_i10++) {
    c5_eta_d_dot[c5_i10] = (*c5_b_eta_d_dot)[c5_i10];
  }

  for (c5_i11 = 0; c5_i11 < 3; c5_i11++) {
    c5_eta_d_dotdot[c5_i11] = (*c5_b_eta_d_dotdot)[c5_i11];
  }

  for (c5_i12 = 0; c5_i12 < 3; c5_i12++) {
    c5_eta_ship[c5_i12] = (*c5_b_eta_ship)[c5_i12];
  }

  for (c5_i13 = 0; c5_i13 < 3; c5_i13++) {
    c5_nu_ship[c5_i13] = (*c5_b_nu_ship)[c5_i13];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 14U, 14U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_psi, 0U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_r, 1U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c, 2U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_s, 3U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_R_rev, 4U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_R_rev2, 5U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 6U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 7U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_eta_d_dot, 8U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_eta_d_dotdot, 9U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_eta_ship, 10U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_nu_ship, 11U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_nu_d, 12U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_nu_dot_d, 13U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 4);
  c5_psi = c5_eta_ship[2];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 5);
  c5_r = c5_nu_ship[2];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 7);
  c5_x = c5_psi;
  c5_c = c5_x;
  c5_b_x = c5_c;
  c5_c = c5_b_x;
  c5_c = muDoubleScalarCos(c5_c);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 8);
  c5_c_x = c5_psi;
  c5_s = c5_c_x;
  c5_d_x = c5_s;
  c5_s = c5_d_x;
  c5_s = muDoubleScalarSin(c5_s);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 9);
  c5_R_rev[0] = c5_c;
  c5_R_rev[3] = c5_s;
  c5_R_rev[6] = 0.0;
  c5_R_rev[1] = -c5_s;
  c5_R_rev[4] = c5_c;
  c5_R_rev[7] = 0.0;
  c5_i14 = 0;
  for (c5_i15 = 0; c5_i15 < 3; c5_i15++) {
    c5_R_rev[c5_i14 + 2] = c5_dv2[c5_i15];
    c5_i14 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 13);
  for (c5_i16 = 0; c5_i16 < 9; c5_i16++) {
    c5_a[c5_i16] = c5_R_rev[c5_i16];
  }

  for (c5_i17 = 0; c5_i17 < 3; c5_i17++) {
    c5_b[c5_i17] = c5_eta_d_dot[c5_i17];
  }

  c5_eml_scalar_eg(chartInstance);
  c5_eml_scalar_eg(chartInstance);
  for (c5_i18 = 0; c5_i18 < 3; c5_i18++) {
    c5_nu_d[c5_i18] = 0.0;
  }

  for (c5_i19 = 0; c5_i19 < 3; c5_i19++) {
    c5_nu_d[c5_i19] = 0.0;
  }

  for (c5_i20 = 0; c5_i20 < 3; c5_i20++) {
    c5_C[c5_i20] = c5_nu_d[c5_i20];
  }

  for (c5_i21 = 0; c5_i21 < 3; c5_i21++) {
    c5_nu_d[c5_i21] = c5_C[c5_i21];
  }

  for (c5_i22 = 0; c5_i22 < 3; c5_i22++) {
    c5_C[c5_i22] = c5_nu_d[c5_i22];
  }

  for (c5_i23 = 0; c5_i23 < 3; c5_i23++) {
    c5_nu_d[c5_i23] = c5_C[c5_i23];
  }

  for (c5_i24 = 0; c5_i24 < 3; c5_i24++) {
    c5_nu_d[c5_i24] = 0.0;
    c5_i25 = 0;
    for (c5_i26 = 0; c5_i26 < 3; c5_i26++) {
      c5_nu_d[c5_i24] += c5_a[c5_i25 + c5_i24] * c5_b[c5_i26];
      c5_i25 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 15);
  c5_R_rev2[0] = 0.0;
  c5_R_rev2[3] = c5_r;
  c5_R_rev2[6] = 0.0;
  c5_R_rev2[1] = -c5_r;
  c5_R_rev2[4] = 0.0;
  c5_R_rev2[7] = 0.0;
  c5_i27 = 0;
  for (c5_i28 = 0; c5_i28 < 3; c5_i28++) {
    c5_R_rev2[c5_i27 + 2] = 0.0;
    c5_i27 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 17);
  for (c5_i29 = 0; c5_i29 < 9; c5_i29++) {
    c5_a[c5_i29] = c5_R_rev[c5_i29];
  }

  for (c5_i30 = 0; c5_i30 < 3; c5_i30++) {
    c5_b[c5_i30] = c5_eta_d_dotdot[c5_i30];
  }

  c5_eml_scalar_eg(chartInstance);
  c5_eml_scalar_eg(chartInstance);
  for (c5_i31 = 0; c5_i31 < 3; c5_i31++) {
    c5_C[c5_i31] = 0.0;
    c5_i32 = 0;
    for (c5_i33 = 0; c5_i33 < 3; c5_i33++) {
      c5_C[c5_i31] += c5_a[c5_i32 + c5_i31] * c5_b[c5_i33];
      c5_i32 += 3;
    }
  }

  for (c5_i34 = 0; c5_i34 < 9; c5_i34++) {
    c5_a[c5_i34] = c5_R_rev2[c5_i34];
  }

  for (c5_i35 = 0; c5_i35 < 3; c5_i35++) {
    c5_b[c5_i35] = c5_nu_d[c5_i35];
  }

  c5_eml_scalar_eg(chartInstance);
  c5_eml_scalar_eg(chartInstance);
  for (c5_i36 = 0; c5_i36 < 3; c5_i36++) {
    c5_y[c5_i36] = 0.0;
    c5_i37 = 0;
    for (c5_i38 = 0; c5_i38 < 3; c5_i38++) {
      c5_y[c5_i36] += c5_a[c5_i37 + c5_i36] * c5_b[c5_i38];
      c5_i37 += 3;
    }
  }

  for (c5_i39 = 0; c5_i39 < 3; c5_i39++) {
    c5_nu_dot_d[c5_i39] = c5_C[c5_i39] + c5_y[c5_i39];
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -17);
  _SFD_SYMBOL_SCOPE_POP();
  for (c5_i40 = 0; c5_i40 < 3; c5_i40++) {
    (*c5_b_nu_d)[c5_i40] = c5_nu_d[c5_i40];
  }

  for (c5_i41 = 0; c5_i41 < 3; c5_i41++) {
    (*c5_b_nu_dot_d)[c5_i41] = c5_nu_dot_d[c5_i41];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
}

static void initSimStructsc5_Model_justmodel(SFc5_Model_justmodelInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc5_Model_justmodel
  (SFc5_Model_justmodelInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber)
{
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i42;
  real_T c5_b_inData[3];
  int32_T c5_i43;
  real_T c5_u[3];
  const mxArray *c5_y = NULL;
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i42 = 0; c5_i42 < 3; c5_i42++) {
    c5_b_inData[c5_i42] = (*(real_T (*)[3])c5_inData)[c5_i42];
  }

  for (c5_i43 = 0; c5_i43 < 3; c5_i43++) {
    c5_u[c5_i43] = c5_b_inData[c5_i43];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static void c5_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_nu_dot_d, const char_T *c5_identifier,
  real_T c5_y[3])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nu_dot_d), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_nu_dot_d);
}

static void c5_b_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[3])
{
  real_T c5_dv3[3];
  int32_T c5_i44;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c5_i44 = 0; c5_i44 < 3; c5_i44++) {
    c5_y[c5_i44] = c5_dv3[c5_i44];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nu_dot_d;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[3];
  int32_T c5_i45;
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c5_nu_dot_d = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nu_dot_d), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_nu_dot_d);
  for (c5_i45 = 0; c5_i45 < 3; c5_i45++) {
    (*(real_T (*)[3])c5_outData)[c5_i45] = c5_y[c5_i45];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static real_T c5_c_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nargout;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c5_nargout = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i46;
  int32_T c5_i47;
  int32_T c5_i48;
  real_T c5_b_inData[9];
  int32_T c5_i49;
  int32_T c5_i50;
  int32_T c5_i51;
  real_T c5_u[9];
  const mxArray *c5_y = NULL;
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_i46 = 0;
  for (c5_i47 = 0; c5_i47 < 3; c5_i47++) {
    for (c5_i48 = 0; c5_i48 < 3; c5_i48++) {
      c5_b_inData[c5_i48 + c5_i46] = (*(real_T (*)[9])c5_inData)[c5_i48 + c5_i46];
    }

    c5_i46 += 3;
  }

  c5_i49 = 0;
  for (c5_i50 = 0; c5_i50 < 3; c5_i50++) {
    for (c5_i51 = 0; c5_i51 < 3; c5_i51++) {
      c5_u[c5_i51 + c5_i49] = c5_b_inData[c5_i51 + c5_i49];
    }

    c5_i49 += 3;
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static void c5_d_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[9])
{
  real_T c5_dv4[9];
  int32_T c5_i52;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv4, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c5_i52 = 0; c5_i52 < 9; c5_i52++) {
    c5_y[c5_i52] = c5_dv4[c5_i52];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_R_rev2;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[9];
  int32_T c5_i53;
  int32_T c5_i54;
  int32_T c5_i55;
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c5_R_rev2 = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_R_rev2), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_R_rev2);
  c5_i53 = 0;
  for (c5_i54 = 0; c5_i54 < 3; c5_i54++) {
    for (c5_i55 = 0; c5_i55 < 3; c5_i55++) {
      (*(real_T (*)[9])c5_outData)[c5_i55 + c5_i53] = c5_y[c5_i55 + c5_i53];
    }

    c5_i53 += 3;
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_Model_justmodel_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo;
  c5_ResolvedFunctionInfo c5_info[13];
  const mxArray *c5_m0 = NULL;
  int32_T c5_i56;
  c5_ResolvedFunctionInfo *c5_r0;
  c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  c5_info_helper(c5_info);
  sf_mex_assign(&c5_m0, sf_mex_createstruct("nameCaptureInfo", 1, 13), FALSE);
  for (c5_i56 = 0; c5_i56 < 13; c5_i56++) {
    c5_r0 = &c5_info[c5_i56];
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c5_r0->context)), "context", "nameCaptureInfo",
                    c5_i56);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c5_r0->name)), "name", "nameCaptureInfo", c5_i56);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c5_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c5_i56);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c5_r0->resolved)), "resolved", "nameCaptureInfo",
                    c5_i56);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c5_i56);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c5_i56);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c5_i56);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c5_i56);
  }

  sf_mex_assign(&c5_nameCaptureInfo, c5_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c5_nameCaptureInfo);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(c5_ResolvedFunctionInfo c5_info[13])
{
  c5_info[0].context = "";
  c5_info[0].name = "cos";
  c5_info[0].dominantType = "double";
  c5_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c5_info[0].fileTimeLo = 1343830372U;
  c5_info[0].fileTimeHi = 0U;
  c5_info[0].mFileTimeLo = 0U;
  c5_info[0].mFileTimeHi = 0U;
  c5_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c5_info[1].name = "eml_scalar_cos";
  c5_info[1].dominantType = "double";
  c5_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c5_info[1].fileTimeLo = 1286818722U;
  c5_info[1].fileTimeHi = 0U;
  c5_info[1].mFileTimeLo = 0U;
  c5_info[1].mFileTimeHi = 0U;
  c5_info[2].context = "";
  c5_info[2].name = "sin";
  c5_info[2].dominantType = "double";
  c5_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c5_info[2].fileTimeLo = 1343830386U;
  c5_info[2].fileTimeHi = 0U;
  c5_info[2].mFileTimeLo = 0U;
  c5_info[2].mFileTimeHi = 0U;
  c5_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c5_info[3].name = "eml_scalar_sin";
  c5_info[3].dominantType = "double";
  c5_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c5_info[3].fileTimeLo = 1286818736U;
  c5_info[3].fileTimeHi = 0U;
  c5_info[3].mFileTimeLo = 0U;
  c5_info[3].mFileTimeHi = 0U;
  c5_info[4].context = "";
  c5_info[4].name = "mtimes";
  c5_info[4].dominantType = "double";
  c5_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c5_info[4].fileTimeLo = 1289519692U;
  c5_info[4].fileTimeHi = 0U;
  c5_info[4].mFileTimeLo = 0U;
  c5_info[4].mFileTimeHi = 0U;
  c5_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c5_info[5].name = "eml_index_class";
  c5_info[5].dominantType = "";
  c5_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c5_info[5].fileTimeLo = 1323170578U;
  c5_info[5].fileTimeHi = 0U;
  c5_info[5].mFileTimeLo = 0U;
  c5_info[5].mFileTimeHi = 0U;
  c5_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c5_info[6].name = "eml_scalar_eg";
  c5_info[6].dominantType = "double";
  c5_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c5_info[6].fileTimeLo = 1286818796U;
  c5_info[6].fileTimeHi = 0U;
  c5_info[6].mFileTimeLo = 0U;
  c5_info[6].mFileTimeHi = 0U;
  c5_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c5_info[7].name = "eml_xgemm";
  c5_info[7].dominantType = "char";
  c5_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c5_info[7].fileTimeLo = 1299076772U;
  c5_info[7].fileTimeHi = 0U;
  c5_info[7].mFileTimeLo = 0U;
  c5_info[7].mFileTimeHi = 0U;
  c5_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c5_info[8].name = "eml_blas_inline";
  c5_info[8].dominantType = "";
  c5_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c5_info[8].fileTimeLo = 1299076768U;
  c5_info[8].fileTimeHi = 0U;
  c5_info[8].mFileTimeLo = 0U;
  c5_info[8].mFileTimeHi = 0U;
  c5_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c5_info[9].name = "mtimes";
  c5_info[9].dominantType = "double";
  c5_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c5_info[9].fileTimeLo = 1289519692U;
  c5_info[9].fileTimeHi = 0U;
  c5_info[9].mFileTimeLo = 0U;
  c5_info[9].mFileTimeHi = 0U;
  c5_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c5_info[10].name = "eml_index_class";
  c5_info[10].dominantType = "";
  c5_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c5_info[10].fileTimeLo = 1323170578U;
  c5_info[10].fileTimeHi = 0U;
  c5_info[10].mFileTimeLo = 0U;
  c5_info[10].mFileTimeHi = 0U;
  c5_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c5_info[11].name = "eml_scalar_eg";
  c5_info[11].dominantType = "double";
  c5_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c5_info[11].fileTimeLo = 1286818796U;
  c5_info[11].fileTimeHi = 0U;
  c5_info[11].mFileTimeLo = 0U;
  c5_info[11].mFileTimeHi = 0U;
  c5_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c5_info[12].name = "eml_refblas_xgemm";
  c5_info[12].dominantType = "char";
  c5_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c5_info[12].fileTimeLo = 1299076774U;
  c5_info[12].fileTimeHi = 0U;
  c5_info[12].mFileTimeLo = 0U;
  c5_info[12].mFileTimeHi = 0U;
}

static void c5_eml_scalar_eg(SFc5_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static int32_T c5_e_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i57;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i57, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i57;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static uint8_T c5_f_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_Model_justmodel, const char_T
  *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_is_active_c5_Model_justmodel), &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_Model_justmodel);
  return c5_y;
}

static uint8_T c5_g_emlrt_marshallIn(SFc5_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_Model_justmodelInstanceStruct
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

void sf_c5_Model_justmodel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2699233759U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(848360892U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3126579503U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3821786023U);
}

mxArray *sf_c5_Model_justmodel_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("JaH9rLY29wusECyBipCU1B");
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

mxArray *sf_c5_Model_justmodel_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c5_Model_justmodel(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"nu_d\",},{M[1],M[9],T\"nu_dot_d\",},{M[8],M[0],T\"is_active_c5_Model_justmodel\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_Model_justmodel_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_Model_justmodelInstanceStruct *chartInstance;
    chartInstance = (SFc5_Model_justmodelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Model_justmodelMachineNumber_,
           5,
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
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)
            c5_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)
            c5_sf_marshallIn);
        }

        {
          real_T (*c5_eta_d_dot)[3];
          real_T (*c5_nu_d)[3];
          real_T (*c5_eta_d_dotdot)[3];
          real_T (*c5_eta_ship)[3];
          real_T (*c5_nu_ship)[3];
          real_T (*c5_nu_dot_d)[3];
          c5_nu_dot_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c5_nu_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c5_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c5_eta_d_dotdot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S,
            1);
          c5_nu_d = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c5_eta_d_dot = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c5_eta_d_dot);
          _SFD_SET_DATA_VALUE_PTR(1U, *c5_nu_d);
          _SFD_SET_DATA_VALUE_PTR(2U, *c5_eta_d_dotdot);
          _SFD_SET_DATA_VALUE_PTR(3U, *c5_eta_ship);
          _SFD_SET_DATA_VALUE_PTR(4U, *c5_nu_ship);
          _SFD_SET_DATA_VALUE_PTR(5U, *c5_nu_dot_d);
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
  return "Iaa4DHsWrE0ZGmOc9BvrfG";
}

static void sf_opaque_initialize_c5_Model_justmodel(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_Model_justmodelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*)
    chartInstanceVar);
  initialize_c5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c5_Model_justmodel(void *chartInstanceVar)
{
  enable_c5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c5_Model_justmodel(void *chartInstanceVar)
{
  disable_c5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c5_Model_justmodel(void *chartInstanceVar)
{
  sf_c5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_Model_justmodel(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_Model_justmodel
    ((SFc5_Model_justmodelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_Model_justmodel();/* state var info */
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

extern void sf_internal_set_sim_state_c5_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_Model_justmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_Model_justmodel(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_Model_justmodel(S);
}

static void sf_opaque_set_sim_state_c5_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c5_Model_justmodel(S, st);
}

static void sf_opaque_terminate_c5_Model_justmodel(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_Model_justmodelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Model_justmodel_optimization_info();
    }

    finalize_c5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_Model_justmodel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_Model_justmodel((SFc5_Model_justmodelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Model_justmodel_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,5,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2626424625U));
  ssSetChecksum1(S,(2866635470U));
  ssSetChecksum2(S,(784972941U));
  ssSetChecksum3(S,(273406740U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_Model_justmodel(SimStruct *S)
{
  SFc5_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc5_Model_justmodelInstanceStruct *)utMalloc(sizeof
    (SFc5_Model_justmodelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_Model_justmodelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c5_Model_justmodel;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c5_Model_justmodel;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c5_Model_justmodel;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_Model_justmodel;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_Model_justmodel;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c5_Model_justmodel;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c5_Model_justmodel;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c5_Model_justmodel;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_Model_justmodel;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_Model_justmodel;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c5_Model_justmodel;
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

void c5_Model_justmodel_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_Model_justmodel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_Model_justmodel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_Model_justmodel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_Model_justmodel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
