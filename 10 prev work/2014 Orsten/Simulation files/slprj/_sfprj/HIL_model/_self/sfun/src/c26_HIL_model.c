/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_sfun.h"
#include "c26_HIL_model.h"
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
static const char * c26_debug_family_names[10] = { "psi_ref", "nuRef", "c", "s",
  "R", "nargin", "nargout", "eta_ref", "nu_ref", "eta_dot_ref" };

/* Function Declarations */
static void initialize_c26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance);
static void initialize_params_c26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance);
static void enable_c26_HIL_model(SFc26_HIL_modelInstanceStruct *chartInstance);
static void disable_c26_HIL_model(SFc26_HIL_modelInstanceStruct *chartInstance);
static void c26_update_debugger_state_c26_HIL_model
  (SFc26_HIL_modelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c26_HIL_model(SFc26_HIL_modelInstanceStruct *
  chartInstance);
static void set_sim_state_c26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_st);
static void finalize_c26_HIL_model(SFc26_HIL_modelInstanceStruct *chartInstance);
static void sf_c26_HIL_model(SFc26_HIL_modelInstanceStruct *chartInstance);
static void c26_chartstep_c26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance);
static void initSimStructsc26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance);
static void registerMessagesc26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c26_machineNumber, uint32_T
  c26_chartNumber);
static const mxArray *c26_sf_marshallOut(void *chartInstanceVoid, void
  *c26_inData);
static void c26_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c26_eta_dot_ref, const char_T *c26_identifier, real_T c26_y[3]);
static void c26_b_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId, real_T c26_y[3]);
static void c26_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c26_mxArrayInData, const char_T *c26_varName, void *c26_outData);
static const mxArray *c26_b_sf_marshallOut(void *chartInstanceVoid, void
  *c26_inData);
static real_T c26_c_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId);
static void c26_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c26_mxArrayInData, const char_T *c26_varName, void *c26_outData);
static const mxArray *c26_c_sf_marshallOut(void *chartInstanceVoid, void
  *c26_inData);
static void c26_d_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId, real_T c26_y[9]);
static void c26_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c26_mxArrayInData, const char_T *c26_varName, void *c26_outData);
static void c26_info_helper(c26_ResolvedFunctionInfo c26_info[14]);
static void c26_eml_scalar_eg(SFc26_HIL_modelInstanceStruct *chartInstance);
static const mxArray *c26_d_sf_marshallOut(void *chartInstanceVoid, void
  *c26_inData);
static int32_T c26_e_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId);
static void c26_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c26_mxArrayInData, const char_T *c26_varName, void *c26_outData);
static uint8_T c26_f_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_b_is_active_c26_HIL_model, const char_T
  *c26_identifier);
static uint8_T c26_g_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId);
static void init_dsm_address_info(SFc26_HIL_modelInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance)
{
  chartInstance->c26_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c26_is_active_c26_HIL_model = 0U;
}

static void initialize_params_c26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void enable_c26_HIL_model(SFc26_HIL_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c26_HIL_model(SFc26_HIL_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c26_update_debugger_state_c26_HIL_model
  (SFc26_HIL_modelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c26_HIL_model(SFc26_HIL_modelInstanceStruct *
  chartInstance)
{
  const mxArray *c26_st;
  const mxArray *c26_y = NULL;
  int32_T c26_i0;
  real_T c26_u[3];
  const mxArray *c26_b_y = NULL;
  uint8_T c26_hoistedGlobal;
  uint8_T c26_b_u;
  const mxArray *c26_c_y = NULL;
  real_T (*c26_eta_dot_ref)[3];
  c26_eta_dot_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c26_st = NULL;
  c26_st = NULL;
  c26_y = NULL;
  sf_mex_assign(&c26_y, sf_mex_createcellarray(2), FALSE);
  for (c26_i0 = 0; c26_i0 < 3; c26_i0++) {
    c26_u[c26_i0] = (*c26_eta_dot_ref)[c26_i0];
  }

  c26_b_y = NULL;
  sf_mex_assign(&c26_b_y, sf_mex_create("y", c26_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c26_y, 0, c26_b_y);
  c26_hoistedGlobal = chartInstance->c26_is_active_c26_HIL_model;
  c26_b_u = c26_hoistedGlobal;
  c26_c_y = NULL;
  sf_mex_assign(&c26_c_y, sf_mex_create("y", &c26_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c26_y, 1, c26_c_y);
  sf_mex_assign(&c26_st, c26_y, FALSE);
  return c26_st;
}

static void set_sim_state_c26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_st)
{
  const mxArray *c26_u;
  real_T c26_dv0[3];
  int32_T c26_i1;
  real_T (*c26_eta_dot_ref)[3];
  c26_eta_dot_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c26_doneDoubleBufferReInit = TRUE;
  c26_u = sf_mex_dup(c26_st);
  c26_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c26_u, 0)),
                       "eta_dot_ref", c26_dv0);
  for (c26_i1 = 0; c26_i1 < 3; c26_i1++) {
    (*c26_eta_dot_ref)[c26_i1] = c26_dv0[c26_i1];
  }

  chartInstance->c26_is_active_c26_HIL_model = c26_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c26_u, 1)),
     "is_active_c26_HIL_model");
  sf_mex_destroy(&c26_u);
  c26_update_debugger_state_c26_HIL_model(chartInstance);
  sf_mex_destroy(&c26_st);
}

static void finalize_c26_HIL_model(SFc26_HIL_modelInstanceStruct *chartInstance)
{
}

static void sf_c26_HIL_model(SFc26_HIL_modelInstanceStruct *chartInstance)
{
  int32_T c26_i2;
  int32_T c26_i3;
  int32_T c26_i4;
  real_T (*c26_nu_ref)[3];
  real_T (*c26_eta_dot_ref)[3];
  real_T (*c26_eta_ref)[3];
  c26_nu_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c26_eta_dot_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c26_eta_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 18U, chartInstance->c26_sfEvent);
  for (c26_i2 = 0; c26_i2 < 3; c26_i2++) {
    _SFD_DATA_RANGE_CHECK((*c26_eta_ref)[c26_i2], 0U);
  }

  for (c26_i3 = 0; c26_i3 < 3; c26_i3++) {
    _SFD_DATA_RANGE_CHECK((*c26_eta_dot_ref)[c26_i3], 1U);
  }

  for (c26_i4 = 0; c26_i4 < 3; c26_i4++) {
    _SFD_DATA_RANGE_CHECK((*c26_nu_ref)[c26_i4], 2U);
  }

  chartInstance->c26_sfEvent = CALL_EVENT;
  c26_chartstep_c26_HIL_model(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c26_chartstep_c26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance)
{
  int32_T c26_i5;
  real_T c26_eta_ref[3];
  int32_T c26_i6;
  real_T c26_nu_ref[3];
  uint32_T c26_debug_family_var_map[10];
  real_T c26_psi_ref;
  real_T c26_nuRef[3];
  real_T c26_c;
  real_T c26_s;
  real_T c26_R[9];
  real_T c26_nargin = 2.0;
  real_T c26_nargout = 1.0;
  real_T c26_eta_dot_ref[3];
  int32_T c26_i7;
  real_T c26_x;
  real_T c26_b_x;
  real_T c26_c_x;
  real_T c26_d_x;
  int32_T c26_i8;
  int32_T c26_i9;
  static real_T c26_dv1[3] = { 0.0, 0.0, 1.0 };

  int32_T c26_i10;
  real_T c26_a[9];
  int32_T c26_i11;
  real_T c26_b[3];
  int32_T c26_i12;
  int32_T c26_i13;
  int32_T c26_i14;
  real_T c26_C[3];
  int32_T c26_i15;
  int32_T c26_i16;
  int32_T c26_i17;
  int32_T c26_i18;
  int32_T c26_i19;
  int32_T c26_i20;
  int32_T c26_i21;
  real_T (*c26_b_eta_dot_ref)[3];
  real_T (*c26_b_nu_ref)[3];
  real_T (*c26_b_eta_ref)[3];
  c26_b_nu_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c26_b_eta_dot_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c26_b_eta_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 18U, chartInstance->c26_sfEvent);
  for (c26_i5 = 0; c26_i5 < 3; c26_i5++) {
    c26_eta_ref[c26_i5] = (*c26_b_eta_ref)[c26_i5];
  }

  for (c26_i6 = 0; c26_i6 < 3; c26_i6++) {
    c26_nu_ref[c26_i6] = (*c26_b_nu_ref)[c26_i6];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c26_debug_family_names,
    c26_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c26_psi_ref, 0U, c26_b_sf_marshallOut,
    c26_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c26_nuRef, 1U, c26_sf_marshallOut,
    c26_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c26_c, 2U, c26_b_sf_marshallOut,
    c26_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c26_s, 3U, c26_b_sf_marshallOut,
    c26_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c26_R, 4U, c26_c_sf_marshallOut,
    c26_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c26_nargin, 5U, c26_b_sf_marshallOut,
    c26_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c26_nargout, 6U, c26_b_sf_marshallOut,
    c26_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c26_eta_ref, 7U, c26_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c26_nu_ref, 8U, c26_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c26_eta_dot_ref, 9U, c26_sf_marshallOut,
    c26_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, 3);
  CV_EML_IF(0, 1, 0, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, 4);
  c26_psi_ref = c26_eta_ref[2];
  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, 9);
  CV_EML_IF(0, 1, 1, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, 10);
  for (c26_i7 = 0; c26_i7 < 3; c26_i7++) {
    c26_nuRef[c26_i7] = c26_nu_ref[c26_i7];
  }

  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, 15);
  c26_x = c26_psi_ref;
  c26_c = c26_x;
  c26_b_x = c26_c;
  c26_c = c26_b_x;
  c26_c = muDoubleScalarCos(c26_c);
  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, 16);
  c26_c_x = c26_psi_ref;
  c26_s = c26_c_x;
  c26_d_x = c26_s;
  c26_s = c26_d_x;
  c26_s = muDoubleScalarSin(c26_s);
  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, 17);
  c26_R[0] = c26_c;
  c26_R[3] = -c26_s;
  c26_R[6] = 0.0;
  c26_R[1] = c26_s;
  c26_R[4] = c26_c;
  c26_R[7] = 0.0;
  c26_i8 = 0;
  for (c26_i9 = 0; c26_i9 < 3; c26_i9++) {
    c26_R[c26_i8 + 2] = c26_dv1[c26_i9];
    c26_i8 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, 21);
  for (c26_i10 = 0; c26_i10 < 9; c26_i10++) {
    c26_a[c26_i10] = c26_R[c26_i10];
  }

  for (c26_i11 = 0; c26_i11 < 3; c26_i11++) {
    c26_b[c26_i11] = c26_nuRef[c26_i11];
  }

  c26_eml_scalar_eg(chartInstance);
  c26_eml_scalar_eg(chartInstance);
  for (c26_i12 = 0; c26_i12 < 3; c26_i12++) {
    c26_eta_dot_ref[c26_i12] = 0.0;
  }

  for (c26_i13 = 0; c26_i13 < 3; c26_i13++) {
    c26_eta_dot_ref[c26_i13] = 0.0;
  }

  for (c26_i14 = 0; c26_i14 < 3; c26_i14++) {
    c26_C[c26_i14] = c26_eta_dot_ref[c26_i14];
  }

  for (c26_i15 = 0; c26_i15 < 3; c26_i15++) {
    c26_eta_dot_ref[c26_i15] = c26_C[c26_i15];
  }

  for (c26_i16 = 0; c26_i16 < 3; c26_i16++) {
    c26_C[c26_i16] = c26_eta_dot_ref[c26_i16];
  }

  for (c26_i17 = 0; c26_i17 < 3; c26_i17++) {
    c26_eta_dot_ref[c26_i17] = c26_C[c26_i17];
  }

  for (c26_i18 = 0; c26_i18 < 3; c26_i18++) {
    c26_eta_dot_ref[c26_i18] = 0.0;
    c26_i19 = 0;
    for (c26_i20 = 0; c26_i20 < 3; c26_i20++) {
      c26_eta_dot_ref[c26_i18] += c26_a[c26_i19 + c26_i18] * c26_b[c26_i20];
      c26_i19 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c26_sfEvent, -21);
  _SFD_SYMBOL_SCOPE_POP();
  for (c26_i21 = 0; c26_i21 < 3; c26_i21++) {
    (*c26_b_eta_dot_ref)[c26_i21] = c26_eta_dot_ref[c26_i21];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 18U, chartInstance->c26_sfEvent);
}

static void initSimStructsc26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc26_HIL_model(SFc26_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c26_machineNumber, uint32_T
  c26_chartNumber)
{
}

static const mxArray *c26_sf_marshallOut(void *chartInstanceVoid, void
  *c26_inData)
{
  const mxArray *c26_mxArrayOutData = NULL;
  int32_T c26_i22;
  real_T c26_b_inData[3];
  int32_T c26_i23;
  real_T c26_u[3];
  const mxArray *c26_y = NULL;
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)chartInstanceVoid;
  c26_mxArrayOutData = NULL;
  for (c26_i22 = 0; c26_i22 < 3; c26_i22++) {
    c26_b_inData[c26_i22] = (*(real_T (*)[3])c26_inData)[c26_i22];
  }

  for (c26_i23 = 0; c26_i23 < 3; c26_i23++) {
    c26_u[c26_i23] = c26_b_inData[c26_i23];
  }

  c26_y = NULL;
  sf_mex_assign(&c26_y, sf_mex_create("y", c26_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c26_mxArrayOutData, c26_y, FALSE);
  return c26_mxArrayOutData;
}

static void c26_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c26_eta_dot_ref, const char_T *c26_identifier, real_T c26_y[3])
{
  emlrtMsgIdentifier c26_thisId;
  c26_thisId.fIdentifier = c26_identifier;
  c26_thisId.fParent = NULL;
  c26_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c26_eta_dot_ref), &c26_thisId,
    c26_y);
  sf_mex_destroy(&c26_eta_dot_ref);
}

static void c26_b_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId, real_T c26_y[3])
{
  real_T c26_dv2[3];
  int32_T c26_i24;
  sf_mex_import(c26_parentId, sf_mex_dup(c26_u), c26_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c26_i24 = 0; c26_i24 < 3; c26_i24++) {
    c26_y[c26_i24] = c26_dv2[c26_i24];
  }

  sf_mex_destroy(&c26_u);
}

static void c26_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c26_mxArrayInData, const char_T *c26_varName, void *c26_outData)
{
  const mxArray *c26_eta_dot_ref;
  const char_T *c26_identifier;
  emlrtMsgIdentifier c26_thisId;
  real_T c26_y[3];
  int32_T c26_i25;
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)chartInstanceVoid;
  c26_eta_dot_ref = sf_mex_dup(c26_mxArrayInData);
  c26_identifier = c26_varName;
  c26_thisId.fIdentifier = c26_identifier;
  c26_thisId.fParent = NULL;
  c26_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c26_eta_dot_ref), &c26_thisId,
    c26_y);
  sf_mex_destroy(&c26_eta_dot_ref);
  for (c26_i25 = 0; c26_i25 < 3; c26_i25++) {
    (*(real_T (*)[3])c26_outData)[c26_i25] = c26_y[c26_i25];
  }

  sf_mex_destroy(&c26_mxArrayInData);
}

static const mxArray *c26_b_sf_marshallOut(void *chartInstanceVoid, void
  *c26_inData)
{
  const mxArray *c26_mxArrayOutData = NULL;
  real_T c26_u;
  const mxArray *c26_y = NULL;
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)chartInstanceVoid;
  c26_mxArrayOutData = NULL;
  c26_u = *(real_T *)c26_inData;
  c26_y = NULL;
  sf_mex_assign(&c26_y, sf_mex_create("y", &c26_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c26_mxArrayOutData, c26_y, FALSE);
  return c26_mxArrayOutData;
}

static real_T c26_c_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId)
{
  real_T c26_y;
  real_T c26_d0;
  sf_mex_import(c26_parentId, sf_mex_dup(c26_u), &c26_d0, 1, 0, 0U, 0, 0U, 0);
  c26_y = c26_d0;
  sf_mex_destroy(&c26_u);
  return c26_y;
}

static void c26_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c26_mxArrayInData, const char_T *c26_varName, void *c26_outData)
{
  const mxArray *c26_nargout;
  const char_T *c26_identifier;
  emlrtMsgIdentifier c26_thisId;
  real_T c26_y;
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)chartInstanceVoid;
  c26_nargout = sf_mex_dup(c26_mxArrayInData);
  c26_identifier = c26_varName;
  c26_thisId.fIdentifier = c26_identifier;
  c26_thisId.fParent = NULL;
  c26_y = c26_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c26_nargout),
    &c26_thisId);
  sf_mex_destroy(&c26_nargout);
  *(real_T *)c26_outData = c26_y;
  sf_mex_destroy(&c26_mxArrayInData);
}

static const mxArray *c26_c_sf_marshallOut(void *chartInstanceVoid, void
  *c26_inData)
{
  const mxArray *c26_mxArrayOutData = NULL;
  int32_T c26_i26;
  int32_T c26_i27;
  int32_T c26_i28;
  real_T c26_b_inData[9];
  int32_T c26_i29;
  int32_T c26_i30;
  int32_T c26_i31;
  real_T c26_u[9];
  const mxArray *c26_y = NULL;
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)chartInstanceVoid;
  c26_mxArrayOutData = NULL;
  c26_i26 = 0;
  for (c26_i27 = 0; c26_i27 < 3; c26_i27++) {
    for (c26_i28 = 0; c26_i28 < 3; c26_i28++) {
      c26_b_inData[c26_i28 + c26_i26] = (*(real_T (*)[9])c26_inData)[c26_i28 +
        c26_i26];
    }

    c26_i26 += 3;
  }

  c26_i29 = 0;
  for (c26_i30 = 0; c26_i30 < 3; c26_i30++) {
    for (c26_i31 = 0; c26_i31 < 3; c26_i31++) {
      c26_u[c26_i31 + c26_i29] = c26_b_inData[c26_i31 + c26_i29];
    }

    c26_i29 += 3;
  }

  c26_y = NULL;
  sf_mex_assign(&c26_y, sf_mex_create("y", c26_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c26_mxArrayOutData, c26_y, FALSE);
  return c26_mxArrayOutData;
}

static void c26_d_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId, real_T c26_y[9])
{
  real_T c26_dv3[9];
  int32_T c26_i32;
  sf_mex_import(c26_parentId, sf_mex_dup(c26_u), c26_dv3, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c26_i32 = 0; c26_i32 < 9; c26_i32++) {
    c26_y[c26_i32] = c26_dv3[c26_i32];
  }

  sf_mex_destroy(&c26_u);
}

static void c26_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c26_mxArrayInData, const char_T *c26_varName, void *c26_outData)
{
  const mxArray *c26_R;
  const char_T *c26_identifier;
  emlrtMsgIdentifier c26_thisId;
  real_T c26_y[9];
  int32_T c26_i33;
  int32_T c26_i34;
  int32_T c26_i35;
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)chartInstanceVoid;
  c26_R = sf_mex_dup(c26_mxArrayInData);
  c26_identifier = c26_varName;
  c26_thisId.fIdentifier = c26_identifier;
  c26_thisId.fParent = NULL;
  c26_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c26_R), &c26_thisId, c26_y);
  sf_mex_destroy(&c26_R);
  c26_i33 = 0;
  for (c26_i34 = 0; c26_i34 < 3; c26_i34++) {
    for (c26_i35 = 0; c26_i35 < 3; c26_i35++) {
      (*(real_T (*)[9])c26_outData)[c26_i35 + c26_i33] = c26_y[c26_i35 + c26_i33];
    }

    c26_i33 += 3;
  }

  sf_mex_destroy(&c26_mxArrayInData);
}

const mxArray *sf_c26_HIL_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c26_nameCaptureInfo;
  c26_ResolvedFunctionInfo c26_info[14];
  const mxArray *c26_m0 = NULL;
  int32_T c26_i36;
  c26_ResolvedFunctionInfo *c26_r0;
  c26_nameCaptureInfo = NULL;
  c26_nameCaptureInfo = NULL;
  c26_info_helper(c26_info);
  sf_mex_assign(&c26_m0, sf_mex_createstruct("nameCaptureInfo", 1, 14), FALSE);
  for (c26_i36 = 0; c26_i36 < 14; c26_i36++) {
    c26_r0 = &c26_info[c26_i36];
    sf_mex_addfield(c26_m0, sf_mex_create("nameCaptureInfo", c26_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c26_r0->context)), "context", "nameCaptureInfo",
                    c26_i36);
    sf_mex_addfield(c26_m0, sf_mex_create("nameCaptureInfo", c26_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c26_r0->name)), "name", "nameCaptureInfo",
                    c26_i36);
    sf_mex_addfield(c26_m0, sf_mex_create("nameCaptureInfo",
      c26_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c26_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c26_i36);
    sf_mex_addfield(c26_m0, sf_mex_create("nameCaptureInfo", c26_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c26_r0->resolved)), "resolved",
                    "nameCaptureInfo", c26_i36);
    sf_mex_addfield(c26_m0, sf_mex_create("nameCaptureInfo", &c26_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c26_i36);
    sf_mex_addfield(c26_m0, sf_mex_create("nameCaptureInfo", &c26_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c26_i36);
    sf_mex_addfield(c26_m0, sf_mex_create("nameCaptureInfo",
      &c26_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c26_i36);
    sf_mex_addfield(c26_m0, sf_mex_create("nameCaptureInfo",
      &c26_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c26_i36);
  }

  sf_mex_assign(&c26_nameCaptureInfo, c26_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c26_nameCaptureInfo);
  return c26_nameCaptureInfo;
}

static void c26_info_helper(c26_ResolvedFunctionInfo c26_info[14])
{
  c26_info[0].context = "";
  c26_info[0].name = "length";
  c26_info[0].dominantType = "double";
  c26_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c26_info[0].fileTimeLo = 1303146206U;
  c26_info[0].fileTimeHi = 0U;
  c26_info[0].mFileTimeLo = 0U;
  c26_info[0].mFileTimeHi = 0U;
  c26_info[1].context = "";
  c26_info[1].name = "cos";
  c26_info[1].dominantType = "double";
  c26_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c26_info[1].fileTimeLo = 1343830372U;
  c26_info[1].fileTimeHi = 0U;
  c26_info[1].mFileTimeLo = 0U;
  c26_info[1].mFileTimeHi = 0U;
  c26_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c26_info[2].name = "eml_scalar_cos";
  c26_info[2].dominantType = "double";
  c26_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c26_info[2].fileTimeLo = 1286818722U;
  c26_info[2].fileTimeHi = 0U;
  c26_info[2].mFileTimeLo = 0U;
  c26_info[2].mFileTimeHi = 0U;
  c26_info[3].context = "";
  c26_info[3].name = "sin";
  c26_info[3].dominantType = "double";
  c26_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c26_info[3].fileTimeLo = 1343830386U;
  c26_info[3].fileTimeHi = 0U;
  c26_info[3].mFileTimeLo = 0U;
  c26_info[3].mFileTimeHi = 0U;
  c26_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c26_info[4].name = "eml_scalar_sin";
  c26_info[4].dominantType = "double";
  c26_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c26_info[4].fileTimeLo = 1286818736U;
  c26_info[4].fileTimeHi = 0U;
  c26_info[4].mFileTimeLo = 0U;
  c26_info[4].mFileTimeHi = 0U;
  c26_info[5].context = "";
  c26_info[5].name = "mtimes";
  c26_info[5].dominantType = "double";
  c26_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c26_info[5].fileTimeLo = 1289519692U;
  c26_info[5].fileTimeHi = 0U;
  c26_info[5].mFileTimeLo = 0U;
  c26_info[5].mFileTimeHi = 0U;
  c26_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c26_info[6].name = "eml_index_class";
  c26_info[6].dominantType = "";
  c26_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c26_info[6].fileTimeLo = 1323170578U;
  c26_info[6].fileTimeHi = 0U;
  c26_info[6].mFileTimeLo = 0U;
  c26_info[6].mFileTimeHi = 0U;
  c26_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c26_info[7].name = "eml_scalar_eg";
  c26_info[7].dominantType = "double";
  c26_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c26_info[7].fileTimeLo = 1286818796U;
  c26_info[7].fileTimeHi = 0U;
  c26_info[7].mFileTimeLo = 0U;
  c26_info[7].mFileTimeHi = 0U;
  c26_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c26_info[8].name = "eml_xgemm";
  c26_info[8].dominantType = "char";
  c26_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c26_info[8].fileTimeLo = 1299076772U;
  c26_info[8].fileTimeHi = 0U;
  c26_info[8].mFileTimeLo = 0U;
  c26_info[8].mFileTimeHi = 0U;
  c26_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c26_info[9].name = "eml_blas_inline";
  c26_info[9].dominantType = "";
  c26_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c26_info[9].fileTimeLo = 1299076768U;
  c26_info[9].fileTimeHi = 0U;
  c26_info[9].mFileTimeLo = 0U;
  c26_info[9].mFileTimeHi = 0U;
  c26_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c26_info[10].name = "mtimes";
  c26_info[10].dominantType = "double";
  c26_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c26_info[10].fileTimeLo = 1289519692U;
  c26_info[10].fileTimeHi = 0U;
  c26_info[10].mFileTimeLo = 0U;
  c26_info[10].mFileTimeHi = 0U;
  c26_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c26_info[11].name = "eml_index_class";
  c26_info[11].dominantType = "";
  c26_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c26_info[11].fileTimeLo = 1323170578U;
  c26_info[11].fileTimeHi = 0U;
  c26_info[11].mFileTimeLo = 0U;
  c26_info[11].mFileTimeHi = 0U;
  c26_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c26_info[12].name = "eml_scalar_eg";
  c26_info[12].dominantType = "double";
  c26_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c26_info[12].fileTimeLo = 1286818796U;
  c26_info[12].fileTimeHi = 0U;
  c26_info[12].mFileTimeLo = 0U;
  c26_info[12].mFileTimeHi = 0U;
  c26_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c26_info[13].name = "eml_refblas_xgemm";
  c26_info[13].dominantType = "char";
  c26_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c26_info[13].fileTimeLo = 1299076774U;
  c26_info[13].fileTimeHi = 0U;
  c26_info[13].mFileTimeLo = 0U;
  c26_info[13].mFileTimeHi = 0U;
}

static void c26_eml_scalar_eg(SFc26_HIL_modelInstanceStruct *chartInstance)
{
}

static const mxArray *c26_d_sf_marshallOut(void *chartInstanceVoid, void
  *c26_inData)
{
  const mxArray *c26_mxArrayOutData = NULL;
  int32_T c26_u;
  const mxArray *c26_y = NULL;
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)chartInstanceVoid;
  c26_mxArrayOutData = NULL;
  c26_u = *(int32_T *)c26_inData;
  c26_y = NULL;
  sf_mex_assign(&c26_y, sf_mex_create("y", &c26_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c26_mxArrayOutData, c26_y, FALSE);
  return c26_mxArrayOutData;
}

static int32_T c26_e_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId)
{
  int32_T c26_y;
  int32_T c26_i37;
  sf_mex_import(c26_parentId, sf_mex_dup(c26_u), &c26_i37, 1, 6, 0U, 0, 0U, 0);
  c26_y = c26_i37;
  sf_mex_destroy(&c26_u);
  return c26_y;
}

static void c26_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c26_mxArrayInData, const char_T *c26_varName, void *c26_outData)
{
  const mxArray *c26_b_sfEvent;
  const char_T *c26_identifier;
  emlrtMsgIdentifier c26_thisId;
  int32_T c26_y;
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)chartInstanceVoid;
  c26_b_sfEvent = sf_mex_dup(c26_mxArrayInData);
  c26_identifier = c26_varName;
  c26_thisId.fIdentifier = c26_identifier;
  c26_thisId.fParent = NULL;
  c26_y = c26_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c26_b_sfEvent),
    &c26_thisId);
  sf_mex_destroy(&c26_b_sfEvent);
  *(int32_T *)c26_outData = c26_y;
  sf_mex_destroy(&c26_mxArrayInData);
}

static uint8_T c26_f_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_b_is_active_c26_HIL_model, const char_T
  *c26_identifier)
{
  uint8_T c26_y;
  emlrtMsgIdentifier c26_thisId;
  c26_thisId.fIdentifier = c26_identifier;
  c26_thisId.fParent = NULL;
  c26_y = c26_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c26_b_is_active_c26_HIL_model), &c26_thisId);
  sf_mex_destroy(&c26_b_is_active_c26_HIL_model);
  return c26_y;
}

static uint8_T c26_g_emlrt_marshallIn(SFc26_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c26_u, const emlrtMsgIdentifier *c26_parentId)
{
  uint8_T c26_y;
  uint8_T c26_u0;
  sf_mex_import(c26_parentId, sf_mex_dup(c26_u), &c26_u0, 1, 3, 0U, 0, 0U, 0);
  c26_y = c26_u0;
  sf_mex_destroy(&c26_u);
  return c26_y;
}

static void init_dsm_address_info(SFc26_HIL_modelInstanceStruct *chartInstance)
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

void sf_c26_HIL_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3156510384U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3949169897U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4175727034U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2295965943U);
}

mxArray *sf_c26_HIL_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("0ctf0Y5i7MK8fbaYTDLzOF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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

mxArray *sf_c26_HIL_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c26_HIL_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"eta_dot_ref\",},{M[8],M[0],T\"is_active_c26_HIL_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c26_HIL_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc26_HIL_modelInstanceStruct *chartInstance;
    chartInstance = (SFc26_HIL_modelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_modelMachineNumber_,
           26,
           1,
           1,
           3,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"eta_ref");
          _SFD_SET_DATA_PROPS(1,2,0,1,"eta_dot_ref");
          _SFD_SET_DATA_PROPS(2,1,1,0,"nu_ref");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,294);
        _SFD_CV_INIT_EML_IF(0,1,0,45,67,94,119);
        _SFD_CV_INIT_EML_IF(0,1,1,121,142,163,194);
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
            1.0,0,0,(MexFcnForType)c26_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c26_sf_marshallOut,(MexInFcnForType)
            c26_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c26_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c26_eta_ref)[3];
          real_T (*c26_eta_dot_ref)[3];
          real_T (*c26_nu_ref)[3];
          c26_nu_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c26_eta_dot_ref = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c26_eta_ref = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c26_eta_ref);
          _SFD_SET_DATA_VALUE_PTR(1U, *c26_eta_dot_ref);
          _SFD_SET_DATA_VALUE_PTR(2U, *c26_nu_ref);
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
  return "UALrpIdQJ4OdOD8IeOcDnD";
}

static void sf_opaque_initialize_c26_HIL_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc26_HIL_modelInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c26_HIL_model((SFc26_HIL_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c26_HIL_model((SFc26_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c26_HIL_model(void *chartInstanceVar)
{
  enable_c26_HIL_model((SFc26_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c26_HIL_model(void *chartInstanceVar)
{
  disable_c26_HIL_model((SFc26_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c26_HIL_model(void *chartInstanceVar)
{
  sf_c26_HIL_model((SFc26_HIL_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c26_HIL_model(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c26_HIL_model
    ((SFc26_HIL_modelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c26_HIL_model();/* state var info */
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

extern void sf_internal_set_sim_state_c26_HIL_model(SimStruct* S, const mxArray *
  st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c26_HIL_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c26_HIL_model((SFc26_HIL_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c26_HIL_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c26_HIL_model(S);
}

static void sf_opaque_set_sim_state_c26_HIL_model(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c26_HIL_model(S, st);
}

static void sf_opaque_terminate_c26_HIL_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc26_HIL_modelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_optimization_info();
    }

    finalize_c26_HIL_model((SFc26_HIL_modelInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc26_HIL_model((SFc26_HIL_modelInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c26_HIL_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c26_HIL_model((SFc26_HIL_modelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c26_HIL_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      26);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,26,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,26,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,26);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,26,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,26,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,26);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4139058722U));
  ssSetChecksum1(S,(1857962821U));
  ssSetChecksum2(S,(3466916789U));
  ssSetChecksum3(S,(1321566423U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c26_HIL_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c26_HIL_model(SimStruct *S)
{
  SFc26_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc26_HIL_modelInstanceStruct *)utMalloc(sizeof
    (SFc26_HIL_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc26_HIL_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c26_HIL_model;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c26_HIL_model;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c26_HIL_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c26_HIL_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c26_HIL_model;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c26_HIL_model;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c26_HIL_model;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c26_HIL_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c26_HIL_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c26_HIL_model;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c26_HIL_model;
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

void c26_HIL_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c26_HIL_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c26_HIL_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c26_HIL_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c26_HIL_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
