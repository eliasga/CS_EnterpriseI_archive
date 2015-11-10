/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_sfun.h"
#include "c25_HIL_model.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HIL_model_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c25_debug_family_names[13] = { "nWP", "xWP", "yWP", "x_ref",
  "y_ref", "psi_ref", "nargin", "nargout", "L", "WP", "alphaLOS_saved",
  "eta_ref_end", "nu_ref_end" };

/* Function Declarations */
static void initialize_c25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance);
static void initialize_params_c25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance);
static void enable_c25_HIL_model(SFc25_HIL_modelInstanceStruct *chartInstance);
static void disable_c25_HIL_model(SFc25_HIL_modelInstanceStruct *chartInstance);
static void c25_update_debugger_state_c25_HIL_model
  (SFc25_HIL_modelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c25_HIL_model(SFc25_HIL_modelInstanceStruct *
  chartInstance);
static void set_sim_state_c25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_st);
static void finalize_c25_HIL_model(SFc25_HIL_modelInstanceStruct *chartInstance);
static void sf_c25_HIL_model(SFc25_HIL_modelInstanceStruct *chartInstance);
static void initSimStructsc25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance);
static void registerMessagesc25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c25_machineNumber, uint32_T
  c25_chartNumber);
static const mxArray *c25_sf_marshallOut(void *chartInstanceVoid, void
  *c25_inData);
static void c25_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c25_nu_ref_end, const char_T *c25_identifier, real_T c25_y[3]);
static void c25_b_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c25_u, const emlrtMsgIdentifier *c25_parentId, real_T c25_y[3]);
static void c25_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c25_mxArrayInData, const char_T *c25_varName, void *c25_outData);
static const mxArray *c25_b_sf_marshallOut(void *chartInstanceVoid, void
  *c25_inData);
static const mxArray *c25_c_sf_marshallOut(void *chartInstanceVoid, void
  *c25_inData);
static real_T c25_c_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_u, const emlrtMsgIdentifier *c25_parentId);
static void c25_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c25_mxArrayInData, const char_T *c25_varName, void *c25_outData);
static const mxArray *c25_d_sf_marshallOut(void *chartInstanceVoid, void
  *c25_inData);
static int32_T c25_d_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_u, const emlrtMsgIdentifier *c25_parentId);
static void c25_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c25_mxArrayInData, const char_T *c25_varName, void *c25_outData);
static uint8_T c25_e_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_b_is_active_c25_HIL_model, const char_T
  *c25_identifier);
static uint8_T c25_f_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_u, const emlrtMsgIdentifier *c25_parentId);
static void init_dsm_address_info(SFc25_HIL_modelInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance)
{
  chartInstance->c25_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c25_is_active_c25_HIL_model = 0U;
}

static void initialize_params_c25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void enable_c25_HIL_model(SFc25_HIL_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c25_HIL_model(SFc25_HIL_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c25_update_debugger_state_c25_HIL_model
  (SFc25_HIL_modelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c25_HIL_model(SFc25_HIL_modelInstanceStruct *
  chartInstance)
{
  const mxArray *c25_st;
  const mxArray *c25_y = NULL;
  int32_T c25_i0;
  real_T c25_u[3];
  const mxArray *c25_b_y = NULL;
  int32_T c25_i1;
  real_T c25_b_u[3];
  const mxArray *c25_c_y = NULL;
  uint8_T c25_hoistedGlobal;
  uint8_T c25_c_u;
  const mxArray *c25_d_y = NULL;
  real_T (*c25_nu_ref_end)[3];
  real_T (*c25_eta_ref_end)[3];
  c25_nu_ref_end = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c25_eta_ref_end = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c25_st = NULL;
  c25_st = NULL;
  c25_y = NULL;
  sf_mex_assign(&c25_y, sf_mex_createcellarray(3), FALSE);
  for (c25_i0 = 0; c25_i0 < 3; c25_i0++) {
    c25_u[c25_i0] = (*c25_eta_ref_end)[c25_i0];
  }

  c25_b_y = NULL;
  sf_mex_assign(&c25_b_y, sf_mex_create("y", c25_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c25_y, 0, c25_b_y);
  for (c25_i1 = 0; c25_i1 < 3; c25_i1++) {
    c25_b_u[c25_i1] = (*c25_nu_ref_end)[c25_i1];
  }

  c25_c_y = NULL;
  sf_mex_assign(&c25_c_y, sf_mex_create("y", c25_b_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c25_y, 1, c25_c_y);
  c25_hoistedGlobal = chartInstance->c25_is_active_c25_HIL_model;
  c25_c_u = c25_hoistedGlobal;
  c25_d_y = NULL;
  sf_mex_assign(&c25_d_y, sf_mex_create("y", &c25_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c25_y, 2, c25_d_y);
  sf_mex_assign(&c25_st, c25_y, FALSE);
  return c25_st;
}

static void set_sim_state_c25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_st)
{
  const mxArray *c25_u;
  real_T c25_dv0[3];
  int32_T c25_i2;
  real_T c25_dv1[3];
  int32_T c25_i3;
  real_T (*c25_eta_ref_end)[3];
  real_T (*c25_nu_ref_end)[3];
  c25_nu_ref_end = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c25_eta_ref_end = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c25_doneDoubleBufferReInit = TRUE;
  c25_u = sf_mex_dup(c25_st);
  c25_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c25_u, 0)),
                       "eta_ref_end", c25_dv0);
  for (c25_i2 = 0; c25_i2 < 3; c25_i2++) {
    (*c25_eta_ref_end)[c25_i2] = c25_dv0[c25_i2];
  }

  c25_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c25_u, 1)),
                       "nu_ref_end", c25_dv1);
  for (c25_i3 = 0; c25_i3 < 3; c25_i3++) {
    (*c25_nu_ref_end)[c25_i3] = c25_dv1[c25_i3];
  }

  chartInstance->c25_is_active_c25_HIL_model = c25_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c25_u, 2)),
     "is_active_c25_HIL_model");
  sf_mex_destroy(&c25_u);
  c25_update_debugger_state_c25_HIL_model(chartInstance);
  sf_mex_destroy(&c25_st);
}

static void finalize_c25_HIL_model(SFc25_HIL_modelInstanceStruct *chartInstance)
{
}

static void sf_c25_HIL_model(SFc25_HIL_modelInstanceStruct *chartInstance)
{
  int32_T c25_i4;
  int32_T c25_i5;
  int32_T c25_i6;
  real_T c25_hoistedGlobal;
  real_T c25_b_hoistedGlobal;
  real_T c25_L;
  int32_T c25_i7;
  real_T c25_WP[4];
  real_T c25_alphaLOS_saved;
  uint32_T c25_debug_family_var_map[13];
  real_T c25_nWP;
  real_T c25_xWP;
  real_T c25_yWP;
  real_T c25_x_ref;
  real_T c25_y_ref;
  real_T c25_psi_ref;
  real_T c25_nargin = 3.0;
  real_T c25_nargout = 2.0;
  real_T c25_eta_ref_end[3];
  real_T c25_nu_ref_end[3];
  real_T c25_x;
  real_T c25_b_x;
  real_T c25_a;
  real_T c25_b;
  real_T c25_y;
  real_T c25_c_x;
  real_T c25_d_x;
  real_T c25_b_a;
  real_T c25_b_b;
  real_T c25_b_y;
  int32_T c25_i8;
  int32_T c25_i9;
  int32_T c25_i10;
  real_T *c25_b_L;
  real_T *c25_b_alphaLOS_saved;
  real_T (*c25_b_eta_ref_end)[3];
  real_T (*c25_b_nu_ref_end)[3];
  real_T (*c25_b_WP)[4];
  c25_b_nu_ref_end = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c25_b_eta_ref_end = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c25_b_alphaLOS_saved = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c25_b_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c25_b_L = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 17U, chartInstance->c25_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c25_b_L, 0U);
  for (c25_i4 = 0; c25_i4 < 4; c25_i4++) {
    _SFD_DATA_RANGE_CHECK((*c25_b_WP)[c25_i4], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c25_b_alphaLOS_saved, 2U);
  for (c25_i5 = 0; c25_i5 < 3; c25_i5++) {
    _SFD_DATA_RANGE_CHECK((*c25_b_eta_ref_end)[c25_i5], 3U);
  }

  for (c25_i6 = 0; c25_i6 < 3; c25_i6++) {
    _SFD_DATA_RANGE_CHECK((*c25_b_nu_ref_end)[c25_i6], 4U);
  }

  chartInstance->c25_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 17U, chartInstance->c25_sfEvent);
  c25_hoistedGlobal = *c25_b_L;
  c25_b_hoistedGlobal = *c25_b_alphaLOS_saved;
  c25_L = c25_hoistedGlobal;
  for (c25_i7 = 0; c25_i7 < 4; c25_i7++) {
    c25_WP[c25_i7] = (*c25_b_WP)[c25_i7];
  }

  c25_alphaLOS_saved = c25_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c25_debug_family_names,
    c25_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c25_nWP, 0U, c25_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c25_xWP, 1U, c25_b_sf_marshallOut,
    c25_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c25_yWP, 2U, c25_b_sf_marshallOut,
    c25_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c25_x_ref, 3U, c25_b_sf_marshallOut,
    c25_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c25_y_ref, 4U, c25_b_sf_marshallOut,
    c25_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c25_psi_ref, 5U, c25_b_sf_marshallOut,
    c25_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c25_nargin, 6U, c25_b_sf_marshallOut,
    c25_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c25_nargout, 7U, c25_b_sf_marshallOut,
    c25_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c25_L, 8U, c25_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c25_WP, 9U, c25_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c25_alphaLOS_saved, 10U, c25_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c25_eta_ref_end, 11U, c25_sf_marshallOut,
    c25_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c25_nu_ref_end, 12U, c25_sf_marshallOut,
    c25_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, 5);
  c25_nWP = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, 6);
  c25_xWP = c25_WP[1];
  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, 7);
  c25_yWP = c25_WP[3];
  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, 9);
  c25_x = c25_alphaLOS_saved;
  c25_b_x = c25_x;
  c25_b_x = muDoubleScalarCos(c25_b_x);
  c25_a = c25_L;
  c25_b = c25_b_x;
  c25_y = c25_a * c25_b;
  c25_x_ref = c25_xWP + c25_y;
  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, 10);
  c25_c_x = c25_alphaLOS_saved;
  c25_d_x = c25_c_x;
  c25_d_x = muDoubleScalarSin(c25_d_x);
  c25_b_a = c25_L;
  c25_b_b = c25_d_x;
  c25_b_y = c25_b_a * c25_b_b;
  c25_y_ref = c25_yWP + c25_b_y;
  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, 11);
  c25_psi_ref = c25_alphaLOS_saved;
  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, 13);
  c25_eta_ref_end[0] = c25_x_ref;
  c25_eta_ref_end[1] = c25_y_ref;
  c25_eta_ref_end[2] = c25_psi_ref;
  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, 16);
  for (c25_i8 = 0; c25_i8 < 3; c25_i8++) {
    c25_nu_ref_end[c25_i8] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c25_sfEvent, -16);
  _SFD_SYMBOL_SCOPE_POP();
  for (c25_i9 = 0; c25_i9 < 3; c25_i9++) {
    (*c25_b_eta_ref_end)[c25_i9] = c25_eta_ref_end[c25_i9];
  }

  for (c25_i10 = 0; c25_i10 < 3; c25_i10++) {
    (*c25_b_nu_ref_end)[c25_i10] = c25_nu_ref_end[c25_i10];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c25_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc25_HIL_model(SFc25_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c25_machineNumber, uint32_T
  c25_chartNumber)
{
}

static const mxArray *c25_sf_marshallOut(void *chartInstanceVoid, void
  *c25_inData)
{
  const mxArray *c25_mxArrayOutData = NULL;
  int32_T c25_i11;
  real_T c25_b_inData[3];
  int32_T c25_i12;
  real_T c25_u[3];
  const mxArray *c25_y = NULL;
  SFc25_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc25_HIL_modelInstanceStruct *)chartInstanceVoid;
  c25_mxArrayOutData = NULL;
  for (c25_i11 = 0; c25_i11 < 3; c25_i11++) {
    c25_b_inData[c25_i11] = (*(real_T (*)[3])c25_inData)[c25_i11];
  }

  for (c25_i12 = 0; c25_i12 < 3; c25_i12++) {
    c25_u[c25_i12] = c25_b_inData[c25_i12];
  }

  c25_y = NULL;
  sf_mex_assign(&c25_y, sf_mex_create("y", c25_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c25_mxArrayOutData, c25_y, FALSE);
  return c25_mxArrayOutData;
}

static void c25_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c25_nu_ref_end, const char_T *c25_identifier, real_T c25_y[3])
{
  emlrtMsgIdentifier c25_thisId;
  c25_thisId.fIdentifier = c25_identifier;
  c25_thisId.fParent = NULL;
  c25_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c25_nu_ref_end), &c25_thisId,
    c25_y);
  sf_mex_destroy(&c25_nu_ref_end);
}

static void c25_b_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c25_u, const emlrtMsgIdentifier *c25_parentId, real_T c25_y[3])
{
  real_T c25_dv2[3];
  int32_T c25_i13;
  sf_mex_import(c25_parentId, sf_mex_dup(c25_u), c25_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c25_i13 = 0; c25_i13 < 3; c25_i13++) {
    c25_y[c25_i13] = c25_dv2[c25_i13];
  }

  sf_mex_destroy(&c25_u);
}

static void c25_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c25_mxArrayInData, const char_T *c25_varName, void *c25_outData)
{
  const mxArray *c25_nu_ref_end;
  const char_T *c25_identifier;
  emlrtMsgIdentifier c25_thisId;
  real_T c25_y[3];
  int32_T c25_i14;
  SFc25_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc25_HIL_modelInstanceStruct *)chartInstanceVoid;
  c25_nu_ref_end = sf_mex_dup(c25_mxArrayInData);
  c25_identifier = c25_varName;
  c25_thisId.fIdentifier = c25_identifier;
  c25_thisId.fParent = NULL;
  c25_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c25_nu_ref_end), &c25_thisId,
    c25_y);
  sf_mex_destroy(&c25_nu_ref_end);
  for (c25_i14 = 0; c25_i14 < 3; c25_i14++) {
    (*(real_T (*)[3])c25_outData)[c25_i14] = c25_y[c25_i14];
  }

  sf_mex_destroy(&c25_mxArrayInData);
}

static const mxArray *c25_b_sf_marshallOut(void *chartInstanceVoid, void
  *c25_inData)
{
  const mxArray *c25_mxArrayOutData = NULL;
  real_T c25_u;
  const mxArray *c25_y = NULL;
  SFc25_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc25_HIL_modelInstanceStruct *)chartInstanceVoid;
  c25_mxArrayOutData = NULL;
  c25_u = *(real_T *)c25_inData;
  c25_y = NULL;
  sf_mex_assign(&c25_y, sf_mex_create("y", &c25_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c25_mxArrayOutData, c25_y, FALSE);
  return c25_mxArrayOutData;
}

static const mxArray *c25_c_sf_marshallOut(void *chartInstanceVoid, void
  *c25_inData)
{
  const mxArray *c25_mxArrayOutData = NULL;
  int32_T c25_i15;
  int32_T c25_i16;
  int32_T c25_i17;
  real_T c25_b_inData[4];
  int32_T c25_i18;
  int32_T c25_i19;
  int32_T c25_i20;
  real_T c25_u[4];
  const mxArray *c25_y = NULL;
  SFc25_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc25_HIL_modelInstanceStruct *)chartInstanceVoid;
  c25_mxArrayOutData = NULL;
  c25_i15 = 0;
  for (c25_i16 = 0; c25_i16 < 2; c25_i16++) {
    for (c25_i17 = 0; c25_i17 < 2; c25_i17++) {
      c25_b_inData[c25_i17 + c25_i15] = (*(real_T (*)[4])c25_inData)[c25_i17 +
        c25_i15];
    }

    c25_i15 += 2;
  }

  c25_i18 = 0;
  for (c25_i19 = 0; c25_i19 < 2; c25_i19++) {
    for (c25_i20 = 0; c25_i20 < 2; c25_i20++) {
      c25_u[c25_i20 + c25_i18] = c25_b_inData[c25_i20 + c25_i18];
    }

    c25_i18 += 2;
  }

  c25_y = NULL;
  sf_mex_assign(&c25_y, sf_mex_create("y", c25_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c25_mxArrayOutData, c25_y, FALSE);
  return c25_mxArrayOutData;
}

static real_T c25_c_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_u, const emlrtMsgIdentifier *c25_parentId)
{
  real_T c25_y;
  real_T c25_d0;
  sf_mex_import(c25_parentId, sf_mex_dup(c25_u), &c25_d0, 1, 0, 0U, 0, 0U, 0);
  c25_y = c25_d0;
  sf_mex_destroy(&c25_u);
  return c25_y;
}

static void c25_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c25_mxArrayInData, const char_T *c25_varName, void *c25_outData)
{
  const mxArray *c25_nargout;
  const char_T *c25_identifier;
  emlrtMsgIdentifier c25_thisId;
  real_T c25_y;
  SFc25_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc25_HIL_modelInstanceStruct *)chartInstanceVoid;
  c25_nargout = sf_mex_dup(c25_mxArrayInData);
  c25_identifier = c25_varName;
  c25_thisId.fIdentifier = c25_identifier;
  c25_thisId.fParent = NULL;
  c25_y = c25_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c25_nargout),
    &c25_thisId);
  sf_mex_destroy(&c25_nargout);
  *(real_T *)c25_outData = c25_y;
  sf_mex_destroy(&c25_mxArrayInData);
}

const mxArray *sf_c25_HIL_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c25_nameCaptureInfo;
  c25_ResolvedFunctionInfo c25_info[5];
  c25_ResolvedFunctionInfo (*c25_b_info)[5];
  const mxArray *c25_m0 = NULL;
  int32_T c25_i21;
  c25_ResolvedFunctionInfo *c25_r0;
  c25_nameCaptureInfo = NULL;
  c25_nameCaptureInfo = NULL;
  c25_b_info = (c25_ResolvedFunctionInfo (*)[5])c25_info;
  (*c25_b_info)[0].context = "";
  (*c25_b_info)[0].name = "cos";
  (*c25_b_info)[0].dominantType = "double";
  (*c25_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c25_b_info)[0].fileTimeLo = 1343830372U;
  (*c25_b_info)[0].fileTimeHi = 0U;
  (*c25_b_info)[0].mFileTimeLo = 0U;
  (*c25_b_info)[0].mFileTimeHi = 0U;
  (*c25_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c25_b_info)[1].name = "eml_scalar_cos";
  (*c25_b_info)[1].dominantType = "double";
  (*c25_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  (*c25_b_info)[1].fileTimeLo = 1286818722U;
  (*c25_b_info)[1].fileTimeHi = 0U;
  (*c25_b_info)[1].mFileTimeLo = 0U;
  (*c25_b_info)[1].mFileTimeHi = 0U;
  (*c25_b_info)[2].context = "";
  (*c25_b_info)[2].name = "mtimes";
  (*c25_b_info)[2].dominantType = "double";
  (*c25_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c25_b_info)[2].fileTimeLo = 1289519692U;
  (*c25_b_info)[2].fileTimeHi = 0U;
  (*c25_b_info)[2].mFileTimeLo = 0U;
  (*c25_b_info)[2].mFileTimeHi = 0U;
  (*c25_b_info)[3].context = "";
  (*c25_b_info)[3].name = "sin";
  (*c25_b_info)[3].dominantType = "double";
  (*c25_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c25_b_info)[3].fileTimeLo = 1343830386U;
  (*c25_b_info)[3].fileTimeHi = 0U;
  (*c25_b_info)[3].mFileTimeLo = 0U;
  (*c25_b_info)[3].mFileTimeHi = 0U;
  (*c25_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c25_b_info)[4].name = "eml_scalar_sin";
  (*c25_b_info)[4].dominantType = "double";
  (*c25_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  (*c25_b_info)[4].fileTimeLo = 1286818736U;
  (*c25_b_info)[4].fileTimeHi = 0U;
  (*c25_b_info)[4].mFileTimeLo = 0U;
  (*c25_b_info)[4].mFileTimeHi = 0U;
  sf_mex_assign(&c25_m0, sf_mex_createstruct("nameCaptureInfo", 1, 5), FALSE);
  for (c25_i21 = 0; c25_i21 < 5; c25_i21++) {
    c25_r0 = &c25_info[c25_i21];
    sf_mex_addfield(c25_m0, sf_mex_create("nameCaptureInfo", c25_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c25_r0->context)), "context", "nameCaptureInfo",
                    c25_i21);
    sf_mex_addfield(c25_m0, sf_mex_create("nameCaptureInfo", c25_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c25_r0->name)), "name", "nameCaptureInfo",
                    c25_i21);
    sf_mex_addfield(c25_m0, sf_mex_create("nameCaptureInfo",
      c25_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c25_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c25_i21);
    sf_mex_addfield(c25_m0, sf_mex_create("nameCaptureInfo", c25_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c25_r0->resolved)), "resolved",
                    "nameCaptureInfo", c25_i21);
    sf_mex_addfield(c25_m0, sf_mex_create("nameCaptureInfo", &c25_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c25_i21);
    sf_mex_addfield(c25_m0, sf_mex_create("nameCaptureInfo", &c25_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c25_i21);
    sf_mex_addfield(c25_m0, sf_mex_create("nameCaptureInfo",
      &c25_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c25_i21);
    sf_mex_addfield(c25_m0, sf_mex_create("nameCaptureInfo",
      &c25_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c25_i21);
  }

  sf_mex_assign(&c25_nameCaptureInfo, c25_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c25_nameCaptureInfo);
  return c25_nameCaptureInfo;
}

static const mxArray *c25_d_sf_marshallOut(void *chartInstanceVoid, void
  *c25_inData)
{
  const mxArray *c25_mxArrayOutData = NULL;
  int32_T c25_u;
  const mxArray *c25_y = NULL;
  SFc25_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc25_HIL_modelInstanceStruct *)chartInstanceVoid;
  c25_mxArrayOutData = NULL;
  c25_u = *(int32_T *)c25_inData;
  c25_y = NULL;
  sf_mex_assign(&c25_y, sf_mex_create("y", &c25_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c25_mxArrayOutData, c25_y, FALSE);
  return c25_mxArrayOutData;
}

static int32_T c25_d_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_u, const emlrtMsgIdentifier *c25_parentId)
{
  int32_T c25_y;
  int32_T c25_i22;
  sf_mex_import(c25_parentId, sf_mex_dup(c25_u), &c25_i22, 1, 6, 0U, 0, 0U, 0);
  c25_y = c25_i22;
  sf_mex_destroy(&c25_u);
  return c25_y;
}

static void c25_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c25_mxArrayInData, const char_T *c25_varName, void *c25_outData)
{
  const mxArray *c25_b_sfEvent;
  const char_T *c25_identifier;
  emlrtMsgIdentifier c25_thisId;
  int32_T c25_y;
  SFc25_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc25_HIL_modelInstanceStruct *)chartInstanceVoid;
  c25_b_sfEvent = sf_mex_dup(c25_mxArrayInData);
  c25_identifier = c25_varName;
  c25_thisId.fIdentifier = c25_identifier;
  c25_thisId.fParent = NULL;
  c25_y = c25_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c25_b_sfEvent),
    &c25_thisId);
  sf_mex_destroy(&c25_b_sfEvent);
  *(int32_T *)c25_outData = c25_y;
  sf_mex_destroy(&c25_mxArrayInData);
}

static uint8_T c25_e_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_b_is_active_c25_HIL_model, const char_T
  *c25_identifier)
{
  uint8_T c25_y;
  emlrtMsgIdentifier c25_thisId;
  c25_thisId.fIdentifier = c25_identifier;
  c25_thisId.fParent = NULL;
  c25_y = c25_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c25_b_is_active_c25_HIL_model), &c25_thisId);
  sf_mex_destroy(&c25_b_is_active_c25_HIL_model);
  return c25_y;
}

static uint8_T c25_f_emlrt_marshallIn(SFc25_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c25_u, const emlrtMsgIdentifier *c25_parentId)
{
  uint8_T c25_y;
  uint8_T c25_u0;
  sf_mex_import(c25_parentId, sf_mex_dup(c25_u), &c25_u0, 1, 3, 0U, 0, 0U, 0);
  c25_y = c25_u0;
  sf_mex_destroy(&c25_u);
  return c25_y;
}

static void init_dsm_address_info(SFc25_HIL_modelInstanceStruct *chartInstance)
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

void sf_c25_HIL_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1146835711U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1038677844U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1969767844U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4033073968U);
}

mxArray *sf_c25_HIL_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("uV0TFr6ZhSiO1vejw3TNqH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
      pr[0] = (double)(2);
      pr[1] = (double)(2);
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

mxArray *sf_c25_HIL_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c25_HIL_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[8],T\"eta_ref_end\",},{M[1],M[13],T\"nu_ref_end\",},{M[8],M[0],T\"is_active_c25_HIL_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c25_HIL_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc25_HIL_modelInstanceStruct *chartInstance;
    chartInstance = (SFc25_HIL_modelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_modelMachineNumber_,
           25,
           1,
           1,
           5,
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
          init_script_number_translation(_HIL_modelMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HIL_modelMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HIL_modelMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"L");
          _SFD_SET_DATA_PROPS(1,1,1,0,"WP");
          _SFD_SET_DATA_PROPS(2,1,1,0,"alphaLOS_saved");
          _SFD_SET_DATA_PROPS(3,2,0,1,"eta_ref_end");
          _SFD_SET_DATA_PROPS(4,2,0,1,"nu_ref_end");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,343);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c25_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c25_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c25_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c25_sf_marshallOut,(MexInFcnForType)
            c25_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c25_sf_marshallOut,(MexInFcnForType)
            c25_sf_marshallIn);
        }

        {
          real_T *c25_L;
          real_T *c25_alphaLOS_saved;
          real_T (*c25_WP)[4];
          real_T (*c25_eta_ref_end)[3];
          real_T (*c25_nu_ref_end)[3];
          c25_nu_ref_end = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            2);
          c25_eta_ref_end = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c25_alphaLOS_saved = (real_T *)ssGetInputPortSignal(chartInstance->S,
            2);
          c25_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
          c25_L = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c25_L);
          _SFD_SET_DATA_VALUE_PTR(1U, *c25_WP);
          _SFD_SET_DATA_VALUE_PTR(2U, c25_alphaLOS_saved);
          _SFD_SET_DATA_VALUE_PTR(3U, *c25_eta_ref_end);
          _SFD_SET_DATA_VALUE_PTR(4U, *c25_nu_ref_end);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HIL_modelMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "0zMw5LFa0bWy2VJ2QgwK1E";
}

static void sf_opaque_initialize_c25_HIL_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc25_HIL_modelInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c25_HIL_model((SFc25_HIL_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c25_HIL_model((SFc25_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c25_HIL_model(void *chartInstanceVar)
{
  enable_c25_HIL_model((SFc25_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c25_HIL_model(void *chartInstanceVar)
{
  disable_c25_HIL_model((SFc25_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c25_HIL_model(void *chartInstanceVar)
{
  sf_c25_HIL_model((SFc25_HIL_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c25_HIL_model(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c25_HIL_model
    ((SFc25_HIL_modelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c25_HIL_model();/* state var info */
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

extern void sf_internal_set_sim_state_c25_HIL_model(SimStruct* S, const mxArray *
  st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c25_HIL_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c25_HIL_model((SFc25_HIL_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c25_HIL_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c25_HIL_model(S);
}

static void sf_opaque_set_sim_state_c25_HIL_model(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c25_HIL_model(S, st);
}

static void sf_opaque_terminate_c25_HIL_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc25_HIL_modelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_optimization_info();
    }

    finalize_c25_HIL_model((SFc25_HIL_modelInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc25_HIL_model((SFc25_HIL_modelInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c25_HIL_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c25_HIL_model((SFc25_HIL_modelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c25_HIL_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      25);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,25,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,25,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,25);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,25,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,25,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,25);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2089394134U));
  ssSetChecksum1(S,(664676163U));
  ssSetChecksum2(S,(2630622601U));
  ssSetChecksum3(S,(2667023722U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c25_HIL_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c25_HIL_model(SimStruct *S)
{
  SFc25_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc25_HIL_modelInstanceStruct *)utMalloc(sizeof
    (SFc25_HIL_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc25_HIL_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c25_HIL_model;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c25_HIL_model;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c25_HIL_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c25_HIL_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c25_HIL_model;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c25_HIL_model;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c25_HIL_model;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c25_HIL_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c25_HIL_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c25_HIL_model;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c25_HIL_model;
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

void c25_HIL_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c25_HIL_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c25_HIL_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c25_HIL_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c25_HIL_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
