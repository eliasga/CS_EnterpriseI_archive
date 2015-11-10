/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_overall_sfun.h"
#include "c16_HIL_model_overall.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HIL_model_overall_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c16_debug_family_names[17] = { "x1", "y1", "x2", "y2",
  "beta", "alpha", "L", "x", "y", "psi", "nargin", "nargout", "WP", "L_rope",
  "L_fast", "Offset_direction", "eta_ref" };

/* Function Declarations */
static void initialize_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance);
static void initialize_params_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance);
static void enable_c16_HIL_model_overall(SFc16_HIL_model_overallInstanceStruct
  *chartInstance);
static void disable_c16_HIL_model_overall(SFc16_HIL_model_overallInstanceStruct *
  chartInstance);
static void c16_update_debugger_state_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance);
static void set_sim_state_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance, const mxArray *c16_st);
static void finalize_c16_HIL_model_overall(SFc16_HIL_model_overallInstanceStruct
  *chartInstance);
static void sf_c16_HIL_model_overall(SFc16_HIL_model_overallInstanceStruct
  *chartInstance);
static void initSimStructsc16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance);
static void registerMessagesc16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c16_machineNumber, uint32_T
  c16_chartNumber);
static const mxArray *c16_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static void c16_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_eta_ref, const char_T *c16_identifier,
  real_T c16_y[3]);
static void c16_b_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId,
  real_T c16_y[3]);
static void c16_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData);
static const mxArray *c16_b_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static const mxArray *c16_c_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static real_T c16_c_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void c16_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData);
static void c16_info_helper(c16_ResolvedFunctionInfo c16_info[13]);
static const mxArray *c16_d_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static int32_T c16_d_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void c16_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData);
static uint8_T c16_e_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_b_is_active_c16_HIL_model_overall, const
  char_T *c16_identifier);
static uint8_T c16_f_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void init_dsm_address_info(SFc16_HIL_model_overallInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance)
{
  chartInstance->c16_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c16_is_active_c16_HIL_model_overall = 0U;
}

static void initialize_params_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void enable_c16_HIL_model_overall(SFc16_HIL_model_overallInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c16_HIL_model_overall(SFc16_HIL_model_overallInstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c16_update_debugger_state_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance)
{
  const mxArray *c16_st;
  const mxArray *c16_y = NULL;
  int32_T c16_i0;
  real_T c16_u[3];
  const mxArray *c16_b_y = NULL;
  uint8_T c16_hoistedGlobal;
  uint8_T c16_b_u;
  const mxArray *c16_c_y = NULL;
  real_T (*c16_eta_ref)[3];
  c16_eta_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c16_st = NULL;
  c16_st = NULL;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_createcellarray(2), FALSE);
  for (c16_i0 = 0; c16_i0 < 3; c16_i0++) {
    c16_u[c16_i0] = (*c16_eta_ref)[c16_i0];
  }

  c16_b_y = NULL;
  sf_mex_assign(&c16_b_y, sf_mex_create("y", c16_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c16_y, 0, c16_b_y);
  c16_hoistedGlobal = chartInstance->c16_is_active_c16_HIL_model_overall;
  c16_b_u = c16_hoistedGlobal;
  c16_c_y = NULL;
  sf_mex_assign(&c16_c_y, sf_mex_create("y", &c16_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c16_y, 1, c16_c_y);
  sf_mex_assign(&c16_st, c16_y, FALSE);
  return c16_st;
}

static void set_sim_state_c16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance, const mxArray *c16_st)
{
  const mxArray *c16_u;
  real_T c16_dv0[3];
  int32_T c16_i1;
  real_T (*c16_eta_ref)[3];
  c16_eta_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c16_doneDoubleBufferReInit = TRUE;
  c16_u = sf_mex_dup(c16_st);
  c16_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c16_u, 0)),
                       "eta_ref", c16_dv0);
  for (c16_i1 = 0; c16_i1 < 3; c16_i1++) {
    (*c16_eta_ref)[c16_i1] = c16_dv0[c16_i1];
  }

  chartInstance->c16_is_active_c16_HIL_model_overall = c16_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c16_u, 1)),
     "is_active_c16_HIL_model_overall");
  sf_mex_destroy(&c16_u);
  c16_update_debugger_state_c16_HIL_model_overall(chartInstance);
  sf_mex_destroy(&c16_st);
}

static void finalize_c16_HIL_model_overall(SFc16_HIL_model_overallInstanceStruct
  *chartInstance)
{
}

static void sf_c16_HIL_model_overall(SFc16_HIL_model_overallInstanceStruct
  *chartInstance)
{
  int32_T c16_i2;
  int32_T c16_i3;
  real_T c16_hoistedGlobal;
  real_T c16_b_hoistedGlobal;
  real_T c16_c_hoistedGlobal;
  int32_T c16_i4;
  real_T c16_WP[4];
  real_T c16_L_rope;
  real_T c16_L_fast;
  real_T c16_Offset_direction;
  uint32_T c16_debug_family_var_map[17];
  real_T c16_x1;
  real_T c16_y1;
  real_T c16_x2;
  real_T c16_y2;
  real_T c16_beta;
  real_T c16_alpha;
  real_T c16_L;
  real_T c16_x;
  real_T c16_y;
  real_T c16_psi;
  real_T c16_nargin = 4.0;
  real_T c16_nargout = 1.0;
  real_T c16_eta_ref[3];
  real_T c16_b_y;
  real_T c16_b_x;
  real_T c16_c_y;
  real_T c16_c_x;
  real_T c16_a;
  real_T c16_d_y;
  real_T c16_A;
  real_T c16_d_x;
  real_T c16_e_x;
  real_T c16_e_y;
  real_T c16_f_x;
  real_T c16_g_x;
  real_T c16_b_a;
  real_T c16_b;
  real_T c16_f_y;
  real_T c16_h_x;
  real_T c16_i_x;
  real_T c16_c_a;
  real_T c16_b_b;
  real_T c16_g_y;
  int32_T c16_i5;
  real_T *c16_b_Offset_direction;
  real_T *c16_b_L_fast;
  real_T *c16_b_L_rope;
  real_T (*c16_b_eta_ref)[3];
  real_T (*c16_b_WP)[4];
  c16_b_Offset_direction = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c16_b_L_fast = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c16_b_L_rope = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c16_b_eta_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c16_b_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 15U, chartInstance->c16_sfEvent);
  for (c16_i2 = 0; c16_i2 < 4; c16_i2++) {
    _SFD_DATA_RANGE_CHECK((*c16_b_WP)[c16_i2], 0U);
  }

  for (c16_i3 = 0; c16_i3 < 3; c16_i3++) {
    _SFD_DATA_RANGE_CHECK((*c16_b_eta_ref)[c16_i3], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c16_b_L_rope, 2U);
  _SFD_DATA_RANGE_CHECK(*c16_b_L_fast, 3U);
  _SFD_DATA_RANGE_CHECK(*c16_b_Offset_direction, 4U);
  chartInstance->c16_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 15U, chartInstance->c16_sfEvent);
  c16_hoistedGlobal = *c16_b_L_rope;
  c16_b_hoistedGlobal = *c16_b_L_fast;
  c16_c_hoistedGlobal = *c16_b_Offset_direction;
  for (c16_i4 = 0; c16_i4 < 4; c16_i4++) {
    c16_WP[c16_i4] = (*c16_b_WP)[c16_i4];
  }

  c16_L_rope = c16_hoistedGlobal;
  c16_L_fast = c16_b_hoistedGlobal;
  c16_Offset_direction = c16_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 17U, 17U, c16_debug_family_names,
    c16_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_x1, 0U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_y1, 1U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_x2, 2U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_y2, 3U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_beta, 4U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_alpha, 5U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_L, 6U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_x, 7U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_y, 8U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_psi, 9U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_nargin, 10U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_nargout, 11U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c16_WP, 12U, c16_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c16_L_rope, 13U, c16_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c16_L_fast, 14U, c16_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c16_Offset_direction, 15U, c16_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c16_eta_ref, 16U, c16_sf_marshallOut,
    c16_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 4);
  c16_x1 = c16_WP[0];
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 5);
  c16_y1 = c16_WP[2];
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 7);
  c16_x2 = c16_WP[1];
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 8);
  c16_y2 = c16_WP[3];
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 10);
  c16_b_y = c16_y2 - c16_y1;
  c16_b_x = c16_x2 - c16_x1;
  c16_c_y = c16_b_y;
  c16_c_x = c16_b_x;
  c16_beta = muDoubleScalarAtan2(c16_c_y, c16_c_x);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 11);
  c16_a = c16_Offset_direction;
  c16_d_y = c16_a * 3.1415926535897931;
  c16_A = c16_d_y;
  c16_d_x = c16_A;
  c16_e_x = c16_d_x;
  c16_e_y = c16_e_x / 10.0;
  c16_alpha = c16_beta + c16_e_y;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 13);
  c16_L = c16_L_rope + c16_L_fast;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 14);
  c16_f_x = c16_alpha;
  c16_g_x = c16_f_x;
  c16_g_x = muDoubleScalarCos(c16_g_x);
  c16_b_a = c16_L;
  c16_b = c16_g_x;
  c16_f_y = c16_b_a * c16_b;
  c16_x = c16_f_y + c16_x1;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 15);
  c16_h_x = c16_alpha;
  c16_i_x = c16_h_x;
  c16_i_x = muDoubleScalarSin(c16_i_x);
  c16_c_a = c16_L;
  c16_b_b = c16_i_x;
  c16_g_y = c16_c_a * c16_b_b;
  c16_y = c16_g_y + c16_y1;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 16);
  c16_psi = c16_alpha;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 18);
  c16_eta_ref[0] = c16_x;
  c16_eta_ref[1] = c16_y;
  c16_eta_ref[2] = c16_psi;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, -18);
  _SFD_SYMBOL_SCOPE_POP();
  for (c16_i5 = 0; c16_i5 < 3; c16_i5++) {
    (*c16_b_eta_ref)[c16_i5] = c16_eta_ref[c16_i5];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c16_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_overallMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void registerMessagesc16_HIL_model_overall
  (SFc16_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c16_machineNumber, uint32_T
  c16_chartNumber)
{
}

static const mxArray *c16_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_i6;
  real_T c16_b_inData[3];
  int32_T c16_i7;
  real_T c16_u[3];
  const mxArray *c16_y = NULL;
  SFc16_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc16_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  for (c16_i6 = 0; c16_i6 < 3; c16_i6++) {
    c16_b_inData[c16_i6] = (*(real_T (*)[3])c16_inData)[c16_i6];
  }

  for (c16_i7 = 0; c16_i7 < 3; c16_i7++) {
    c16_u[c16_i7] = c16_b_inData[c16_i7];
  }

  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", c16_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, FALSE);
  return c16_mxArrayOutData;
}

static void c16_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_eta_ref, const char_T *c16_identifier,
  real_T c16_y[3])
{
  emlrtMsgIdentifier c16_thisId;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_eta_ref), &c16_thisId,
    c16_y);
  sf_mex_destroy(&c16_eta_ref);
}

static void c16_b_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId,
  real_T c16_y[3])
{
  real_T c16_dv1[3];
  int32_T c16_i8;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), c16_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c16_i8 = 0; c16_i8 < 3; c16_i8++) {
    c16_y[c16_i8] = c16_dv1[c16_i8];
  }

  sf_mex_destroy(&c16_u);
}

static void c16_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData)
{
  const mxArray *c16_eta_ref;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  real_T c16_y[3];
  int32_T c16_i9;
  SFc16_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc16_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c16_eta_ref = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_eta_ref), &c16_thisId,
    c16_y);
  sf_mex_destroy(&c16_eta_ref);
  for (c16_i9 = 0; c16_i9 < 3; c16_i9++) {
    (*(real_T (*)[3])c16_outData)[c16_i9] = c16_y[c16_i9];
  }

  sf_mex_destroy(&c16_mxArrayInData);
}

static const mxArray *c16_b_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  real_T c16_u;
  const mxArray *c16_y = NULL;
  SFc16_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc16_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_u = *(real_T *)c16_inData;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", &c16_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, FALSE);
  return c16_mxArrayOutData;
}

static const mxArray *c16_c_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_i10;
  int32_T c16_i11;
  int32_T c16_i12;
  real_T c16_b_inData[4];
  int32_T c16_i13;
  int32_T c16_i14;
  int32_T c16_i15;
  real_T c16_u[4];
  const mxArray *c16_y = NULL;
  SFc16_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc16_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_i10 = 0;
  for (c16_i11 = 0; c16_i11 < 2; c16_i11++) {
    for (c16_i12 = 0; c16_i12 < 2; c16_i12++) {
      c16_b_inData[c16_i12 + c16_i10] = (*(real_T (*)[4])c16_inData)[c16_i12 +
        c16_i10];
    }

    c16_i10 += 2;
  }

  c16_i13 = 0;
  for (c16_i14 = 0; c16_i14 < 2; c16_i14++) {
    for (c16_i15 = 0; c16_i15 < 2; c16_i15++) {
      c16_u[c16_i15 + c16_i13] = c16_b_inData[c16_i15 + c16_i13];
    }

    c16_i13 += 2;
  }

  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", c16_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, FALSE);
  return c16_mxArrayOutData;
}

static real_T c16_c_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  real_T c16_y;
  real_T c16_d0;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_d0, 1, 0, 0U, 0, 0U, 0);
  c16_y = c16_d0;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void c16_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData)
{
  const mxArray *c16_nargout;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  real_T c16_y;
  SFc16_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc16_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c16_nargout = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_nargout),
    &c16_thisId);
  sf_mex_destroy(&c16_nargout);
  *(real_T *)c16_outData = c16_y;
  sf_mex_destroy(&c16_mxArrayInData);
}

const mxArray *sf_c16_HIL_model_overall_get_eml_resolved_functions_info(void)
{
  const mxArray *c16_nameCaptureInfo;
  c16_ResolvedFunctionInfo c16_info[13];
  const mxArray *c16_m0 = NULL;
  int32_T c16_i16;
  c16_ResolvedFunctionInfo *c16_r0;
  c16_nameCaptureInfo = NULL;
  c16_nameCaptureInfo = NULL;
  c16_info_helper(c16_info);
  sf_mex_assign(&c16_m0, sf_mex_createstruct("nameCaptureInfo", 1, 13), FALSE);
  for (c16_i16 = 0; c16_i16 < 13; c16_i16++) {
    c16_r0 = &c16_info[c16_i16];
    sf_mex_addfield(c16_m0, sf_mex_create("nameCaptureInfo", c16_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c16_r0->context)), "context", "nameCaptureInfo",
                    c16_i16);
    sf_mex_addfield(c16_m0, sf_mex_create("nameCaptureInfo", c16_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c16_r0->name)), "name", "nameCaptureInfo",
                    c16_i16);
    sf_mex_addfield(c16_m0, sf_mex_create("nameCaptureInfo",
      c16_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c16_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c16_i16);
    sf_mex_addfield(c16_m0, sf_mex_create("nameCaptureInfo", c16_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c16_r0->resolved)), "resolved",
                    "nameCaptureInfo", c16_i16);
    sf_mex_addfield(c16_m0, sf_mex_create("nameCaptureInfo", &c16_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c16_i16);
    sf_mex_addfield(c16_m0, sf_mex_create("nameCaptureInfo", &c16_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c16_i16);
    sf_mex_addfield(c16_m0, sf_mex_create("nameCaptureInfo",
      &c16_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c16_i16);
    sf_mex_addfield(c16_m0, sf_mex_create("nameCaptureInfo",
      &c16_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c16_i16);
  }

  sf_mex_assign(&c16_nameCaptureInfo, c16_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c16_nameCaptureInfo);
  return c16_nameCaptureInfo;
}

static void c16_info_helper(c16_ResolvedFunctionInfo c16_info[13])
{
  c16_info[0].context = "";
  c16_info[0].name = "atan2";
  c16_info[0].dominantType = "double";
  c16_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c16_info[0].fileTimeLo = 1343830372U;
  c16_info[0].fileTimeHi = 0U;
  c16_info[0].mFileTimeLo = 0U;
  c16_info[0].mFileTimeHi = 0U;
  c16_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c16_info[1].name = "eml_scalar_eg";
  c16_info[1].dominantType = "double";
  c16_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c16_info[1].fileTimeLo = 1286818796U;
  c16_info[1].fileTimeHi = 0U;
  c16_info[1].mFileTimeLo = 0U;
  c16_info[1].mFileTimeHi = 0U;
  c16_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c16_info[2].name = "eml_scalexp_alloc";
  c16_info[2].dominantType = "double";
  c16_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c16_info[2].fileTimeLo = 1352424860U;
  c16_info[2].fileTimeHi = 0U;
  c16_info[2].mFileTimeLo = 0U;
  c16_info[2].mFileTimeHi = 0U;
  c16_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c16_info[3].name = "eml_scalar_atan2";
  c16_info[3].dominantType = "double";
  c16_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m";
  c16_info[3].fileTimeLo = 1286818720U;
  c16_info[3].fileTimeHi = 0U;
  c16_info[3].mFileTimeLo = 0U;
  c16_info[3].mFileTimeHi = 0U;
  c16_info[4].context = "";
  c16_info[4].name = "mtimes";
  c16_info[4].dominantType = "double";
  c16_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c16_info[4].fileTimeLo = 1289519692U;
  c16_info[4].fileTimeHi = 0U;
  c16_info[4].mFileTimeLo = 0U;
  c16_info[4].mFileTimeHi = 0U;
  c16_info[5].context = "";
  c16_info[5].name = "mrdivide";
  c16_info[5].dominantType = "double";
  c16_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c16_info[5].fileTimeLo = 1357951548U;
  c16_info[5].fileTimeHi = 0U;
  c16_info[5].mFileTimeLo = 1319729966U;
  c16_info[5].mFileTimeHi = 0U;
  c16_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c16_info[6].name = "rdivide";
  c16_info[6].dominantType = "double";
  c16_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c16_info[6].fileTimeLo = 1346510388U;
  c16_info[6].fileTimeHi = 0U;
  c16_info[6].mFileTimeLo = 0U;
  c16_info[6].mFileTimeHi = 0U;
  c16_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c16_info[7].name = "eml_scalexp_compatible";
  c16_info[7].dominantType = "double";
  c16_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c16_info[7].fileTimeLo = 1286818796U;
  c16_info[7].fileTimeHi = 0U;
  c16_info[7].mFileTimeLo = 0U;
  c16_info[7].mFileTimeHi = 0U;
  c16_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c16_info[8].name = "eml_div";
  c16_info[8].dominantType = "double";
  c16_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c16_info[8].fileTimeLo = 1313347810U;
  c16_info[8].fileTimeHi = 0U;
  c16_info[8].mFileTimeLo = 0U;
  c16_info[8].mFileTimeHi = 0U;
  c16_info[9].context = "";
  c16_info[9].name = "cos";
  c16_info[9].dominantType = "double";
  c16_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c16_info[9].fileTimeLo = 1343830372U;
  c16_info[9].fileTimeHi = 0U;
  c16_info[9].mFileTimeLo = 0U;
  c16_info[9].mFileTimeHi = 0U;
  c16_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c16_info[10].name = "eml_scalar_cos";
  c16_info[10].dominantType = "double";
  c16_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c16_info[10].fileTimeLo = 1286818722U;
  c16_info[10].fileTimeHi = 0U;
  c16_info[10].mFileTimeLo = 0U;
  c16_info[10].mFileTimeHi = 0U;
  c16_info[11].context = "";
  c16_info[11].name = "sin";
  c16_info[11].dominantType = "double";
  c16_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c16_info[11].fileTimeLo = 1343830386U;
  c16_info[11].fileTimeHi = 0U;
  c16_info[11].mFileTimeLo = 0U;
  c16_info[11].mFileTimeHi = 0U;
  c16_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c16_info[12].name = "eml_scalar_sin";
  c16_info[12].dominantType = "double";
  c16_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c16_info[12].fileTimeLo = 1286818736U;
  c16_info[12].fileTimeHi = 0U;
  c16_info[12].mFileTimeLo = 0U;
  c16_info[12].mFileTimeHi = 0U;
}

static const mxArray *c16_d_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_u;
  const mxArray *c16_y = NULL;
  SFc16_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc16_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_u = *(int32_T *)c16_inData;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", &c16_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, FALSE);
  return c16_mxArrayOutData;
}

static int32_T c16_d_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  int32_T c16_y;
  int32_T c16_i17;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_i17, 1, 6, 0U, 0, 0U, 0);
  c16_y = c16_i17;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void c16_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData)
{
  const mxArray *c16_b_sfEvent;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  int32_T c16_y;
  SFc16_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc16_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c16_b_sfEvent = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_b_sfEvent),
    &c16_thisId);
  sf_mex_destroy(&c16_b_sfEvent);
  *(int32_T *)c16_outData = c16_y;
  sf_mex_destroy(&c16_mxArrayInData);
}

static uint8_T c16_e_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_b_is_active_c16_HIL_model_overall, const
  char_T *c16_identifier)
{
  uint8_T c16_y;
  emlrtMsgIdentifier c16_thisId;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c16_b_is_active_c16_HIL_model_overall), &c16_thisId);
  sf_mex_destroy(&c16_b_is_active_c16_HIL_model_overall);
  return c16_y;
}

static uint8_T c16_f_emlrt_marshallIn(SFc16_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  uint8_T c16_y;
  uint8_T c16_u0;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_u0, 1, 3, 0U, 0, 0U, 0);
  c16_y = c16_u0;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void init_dsm_address_info(SFc16_HIL_model_overallInstanceStruct
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

void sf_c16_HIL_model_overall_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2984638193U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2817324692U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1457416717U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2634252847U);
}

mxArray *sf_c16_HIL_model_overall_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("G64yU3zmbafFuwxSzxbspC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(2);
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

mxArray *sf_c16_HIL_model_overall_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c16_HIL_model_overall(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"eta_ref\",},{M[8],M[0],T\"is_active_c16_HIL_model_overall\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c16_HIL_model_overall_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc16_HIL_model_overallInstanceStruct *chartInstance;
    chartInstance = (SFc16_HIL_model_overallInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_overallMachineNumber_,
           16,
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
          init_script_number_translation(_HIL_model_overallMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HIL_model_overallMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HIL_model_overallMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"WP");
          _SFD_SET_DATA_PROPS(1,2,0,1,"eta_ref");
          _SFD_SET_DATA_PROPS(2,1,1,0,"L_rope");
          _SFD_SET_DATA_PROPS(3,1,1,0,"L_fast");
          _SFD_SET_DATA_PROPS(4,1,1,0,"Offset_direction");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,330);
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
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c16_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c16_sf_marshallOut,(MexInFcnForType)
            c16_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c16_L_rope;
          real_T *c16_L_fast;
          real_T *c16_Offset_direction;
          real_T (*c16_WP)[4];
          real_T (*c16_eta_ref)[3];
          c16_Offset_direction = (real_T *)ssGetInputPortSignal(chartInstance->S,
            3);
          c16_L_fast = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c16_L_rope = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c16_eta_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c16_WP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c16_WP);
          _SFD_SET_DATA_VALUE_PTR(1U, *c16_eta_ref);
          _SFD_SET_DATA_VALUE_PTR(2U, c16_L_rope);
          _SFD_SET_DATA_VALUE_PTR(3U, c16_L_fast);
          _SFD_SET_DATA_VALUE_PTR(4U, c16_Offset_direction);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HIL_model_overallMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "SLGExYOQbgHwOhnjPAxnnH";
}

static void sf_opaque_initialize_c16_HIL_model_overall(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc16_HIL_model_overallInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c16_HIL_model_overall((SFc16_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
  initialize_c16_HIL_model_overall((SFc16_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c16_HIL_model_overall(void *chartInstanceVar)
{
  enable_c16_HIL_model_overall((SFc16_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c16_HIL_model_overall(void *chartInstanceVar)
{
  disable_c16_HIL_model_overall((SFc16_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c16_HIL_model_overall(void *chartInstanceVar)
{
  sf_c16_HIL_model_overall((SFc16_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c16_HIL_model_overall(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c16_HIL_model_overall
    ((SFc16_HIL_model_overallInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c16_HIL_model_overall();/* state var info */
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

extern void sf_internal_set_sim_state_c16_HIL_model_overall(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c16_HIL_model_overall();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c16_HIL_model_overall((SFc16_HIL_model_overallInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c16_HIL_model_overall(SimStruct* S)
{
  return sf_internal_get_sim_state_c16_HIL_model_overall(S);
}

static void sf_opaque_set_sim_state_c16_HIL_model_overall(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c16_HIL_model_overall(S, st);
}

static void sf_opaque_terminate_c16_HIL_model_overall(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc16_HIL_model_overallInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_overall_optimization_info();
    }

    finalize_c16_HIL_model_overall((SFc16_HIL_model_overallInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc16_HIL_model_overall((SFc16_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c16_HIL_model_overall(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c16_HIL_model_overall
      ((SFc16_HIL_model_overallInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c16_HIL_model_overall(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_overall_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      16);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,16,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,16,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,16);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,16,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,16,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,16);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2179481285U));
  ssSetChecksum1(S,(1628351255U));
  ssSetChecksum2(S,(521812663U));
  ssSetChecksum3(S,(3310433740U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c16_HIL_model_overall(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c16_HIL_model_overall(SimStruct *S)
{
  SFc16_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc16_HIL_model_overallInstanceStruct *)utMalloc(sizeof
    (SFc16_HIL_model_overallInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc16_HIL_model_overallInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c16_HIL_model_overall;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c16_HIL_model_overall;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c16_HIL_model_overall;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c16_HIL_model_overall;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c16_HIL_model_overall;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c16_HIL_model_overall;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c16_HIL_model_overall;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c16_HIL_model_overall;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c16_HIL_model_overall;
  chartInstance->chartInfo.mdlStart = mdlStart_c16_HIL_model_overall;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c16_HIL_model_overall;
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

void c16_HIL_model_overall_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c16_HIL_model_overall(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c16_HIL_model_overall(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c16_HIL_model_overall(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c16_HIL_model_overall_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
