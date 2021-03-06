/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Model_justmodel2_sfun.h"
#include "c8_Model_justmodel2.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Model_justmodel2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c8_debug_family_names[16] = { "meanSum", "varSum",
  "startval", "Ndiv", "i", "variance", "nargin", "nargout", "theCount", "N",
  "input", "saved_in", "counter", "Mean", "StandardDev", "saved_out" };

/* Function Declarations */
static void initialize_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance);
static void initialize_params_c8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance);
static void enable_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance);
static void disable_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance);
static void c8_update_debugger_state_c8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance);
static void set_sim_state_c8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance, const mxArray *c8_st);
static void finalize_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance);
static void sf_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance);
static void c8_chartstep_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance);
static void initSimStructsc8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance);
static void registerMessagesc8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static void c8_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_saved_out, const char_T *c8_identifier,
  real_T c8_y[50]);
static void c8_b_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[50]);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_c_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_StandardDev, const char_T *c8_identifier);
static real_T c8_d_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[18]);
static void c8_eml_scalar_eg(SFc8_Model_justmodel2InstanceStruct *chartInstance);
static void c8_eml_error(SFc8_Model_justmodel2InstanceStruct *chartInstance);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_e_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_f_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_Model_justmodel2, const
  char_T *c8_identifier);
static uint8_T c8_g_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void init_dsm_address_info(SFc8_Model_justmodel2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c8_is_active_c8_Model_justmodel2 = 0U;
}

static void initialize_params_c8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance)
{
}

static void enable_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c8_update_debugger_state_c8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  real_T c8_hoistedGlobal;
  real_T c8_u;
  const mxArray *c8_b_y = NULL;
  real_T c8_b_hoistedGlobal;
  real_T c8_b_u;
  const mxArray *c8_c_y = NULL;
  real_T c8_c_hoistedGlobal;
  real_T c8_c_u;
  const mxArray *c8_d_y = NULL;
  int32_T c8_i0;
  real_T c8_d_u[50];
  const mxArray *c8_e_y = NULL;
  uint8_T c8_d_hoistedGlobal;
  uint8_T c8_e_u;
  const mxArray *c8_f_y = NULL;
  real_T *c8_Mean;
  real_T *c8_StandardDev;
  real_T *c8_counter;
  real_T (*c8_saved_out)[50];
  c8_saved_out = (real_T (*)[50])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_StandardDev = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c8_Mean = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_counter = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellarray(5), FALSE);
  c8_hoistedGlobal = *c8_Mean;
  c8_u = c8_hoistedGlobal;
  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_b_hoistedGlobal = *c8_StandardDev;
  c8_b_u = c8_b_hoistedGlobal;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  c8_c_hoistedGlobal = *c8_counter;
  c8_c_u = c8_c_hoistedGlobal;
  c8_d_y = NULL;
  sf_mex_assign(&c8_d_y, sf_mex_create("y", &c8_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 2, c8_d_y);
  for (c8_i0 = 0; c8_i0 < 50; c8_i0++) {
    c8_d_u[c8_i0] = (*c8_saved_out)[c8_i0];
  }

  c8_e_y = NULL;
  sf_mex_assign(&c8_e_y, sf_mex_create("y", c8_d_u, 0, 0U, 1U, 0U, 1, 50), FALSE);
  sf_mex_setcell(c8_y, 3, c8_e_y);
  c8_d_hoistedGlobal = chartInstance->c8_is_active_c8_Model_justmodel2;
  c8_e_u = c8_d_hoistedGlobal;
  c8_f_y = NULL;
  sf_mex_assign(&c8_f_y, sf_mex_create("y", &c8_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c8_y, 4, c8_f_y);
  sf_mex_assign(&c8_st, c8_y, FALSE);
  return c8_st;
}

static void set_sim_state_c8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance, const mxArray *c8_st)
{
  const mxArray *c8_u;
  real_T c8_dv0[50];
  int32_T c8_i1;
  real_T *c8_Mean;
  real_T *c8_StandardDev;
  real_T *c8_counter;
  real_T (*c8_saved_out)[50];
  c8_saved_out = (real_T (*)[50])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_StandardDev = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c8_Mean = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_counter = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = TRUE;
  c8_u = sf_mex_dup(c8_st);
  *c8_Mean = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u,
    0)), "Mean");
  *c8_StandardDev = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c8_u, 1)), "StandardDev");
  *c8_counter = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c8_u, 2)), "counter");
  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 3)),
                      "saved_out", c8_dv0);
  for (c8_i1 = 0; c8_i1 < 50; c8_i1++) {
    (*c8_saved_out)[c8_i1] = c8_dv0[c8_i1];
  }

  chartInstance->c8_is_active_c8_Model_justmodel2 = c8_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 4)),
     "is_active_c8_Model_justmodel2");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_Model_justmodel2(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance)
{
}

static void sf_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance)
{
  int32_T c8_i2;
  int32_T c8_i3;
  real_T *c8_counter;
  real_T *c8_theCount;
  real_T *c8_N;
  real_T *c8_Mean;
  real_T *c8_StandardDev;
  real_T *c8_input;
  real_T (*c8_saved_out)[50];
  real_T (*c8_saved_in)[50];
  c8_saved_out = (real_T (*)[50])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_saved_in = (real_T (*)[50])ssGetInputPortSignal(chartInstance->S, 3);
  c8_input = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c8_StandardDev = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c8_Mean = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_N = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c8_theCount = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c8_counter = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c8_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c8_counter, 0U);
  _SFD_DATA_RANGE_CHECK(*c8_theCount, 1U);
  _SFD_DATA_RANGE_CHECK(*c8_N, 2U);
  _SFD_DATA_RANGE_CHECK(*c8_Mean, 3U);
  _SFD_DATA_RANGE_CHECK(*c8_StandardDev, 4U);
  _SFD_DATA_RANGE_CHECK(*c8_input, 5U);
  for (c8_i2 = 0; c8_i2 < 50; c8_i2++) {
    _SFD_DATA_RANGE_CHECK((*c8_saved_in)[c8_i2], 6U);
  }

  for (c8_i3 = 0; c8_i3 < 50; c8_i3++) {
    _SFD_DATA_RANGE_CHECK((*c8_saved_out)[c8_i3], 7U);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  c8_chartstep_c8_Model_justmodel2(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Model_justmodel2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c8_chartstep_c8_Model_justmodel2(SFc8_Model_justmodel2InstanceStruct
  *chartInstance)
{
  real_T c8_hoistedGlobal;
  real_T c8_b_hoistedGlobal;
  real_T c8_c_hoistedGlobal;
  real_T c8_theCount;
  real_T c8_N;
  real_T c8_input;
  int32_T c8_i4;
  real_T c8_saved_in[50];
  uint32_T c8_debug_family_var_map[16];
  real_T c8_meanSum;
  real_T c8_varSum;
  real_T c8_startval;
  real_T c8_Ndiv;
  real_T c8_i;
  real_T c8_variance;
  real_T c8_nargin = 4.0;
  real_T c8_nargout = 4.0;
  real_T c8_counter;
  real_T c8_Mean;
  real_T c8_StandardDev;
  real_T c8_saved_out[50];
  real_T c8_x;
  real_T c8_b_x;
  int32_T c8_i5;
  real_T c8_b_startval;
  real_T c8_b_N;
  int32_T c8_i6;
  int32_T c8_b_i;
  real_T c8_B;
  real_T c8_y;
  real_T c8_b_y;
  real_T c8_c_y;
  real_T c8_a;
  real_T c8_b;
  real_T c8_d0;
  real_T c8_c_N;
  int32_T c8_i7;
  int32_T c8_c_i;
  real_T c8_b_a;
  real_T c8_c_a;
  real_T c8_d_a;
  real_T c8_ak;
  real_T c8_e_a;
  real_T c8_f_a;
  real_T c8_b_b;
  real_T c8_b_B;
  real_T c8_d_y;
  real_T c8_e_y;
  real_T c8_f_y;
  real_T c8_g_a;
  real_T c8_c_b;
  real_T c8_c_x;
  real_T c8_d_x;
  int32_T c8_i8;
  real_T *c8_b_StandardDev;
  real_T *c8_b_Mean;
  real_T *c8_b_counter;
  real_T *c8_b_input;
  real_T *c8_d_N;
  real_T *c8_b_theCount;
  real_T (*c8_b_saved_out)[50];
  real_T (*c8_b_saved_in)[50];
  c8_b_saved_out = (real_T (*)[50])ssGetOutputPortSignal(chartInstance->S, 4);
  c8_b_saved_in = (real_T (*)[50])ssGetInputPortSignal(chartInstance->S, 3);
  c8_b_input = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c8_b_StandardDev = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c8_b_Mean = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_d_N = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_theCount = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c8_b_counter = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c8_sfEvent);
  c8_hoistedGlobal = *c8_b_theCount;
  c8_b_hoistedGlobal = *c8_d_N;
  c8_c_hoistedGlobal = *c8_b_input;
  c8_theCount = c8_hoistedGlobal;
  c8_N = c8_b_hoistedGlobal;
  c8_input = c8_c_hoistedGlobal;
  for (c8_i4 = 0; c8_i4 < 50; c8_i4++) {
    c8_saved_in[c8_i4] = (*c8_b_saved_in)[c8_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 16U, 16U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_meanSum, 0U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_varSum, 1U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_startval, 2U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_Ndiv, 3U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_i, 4U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_variance, 5U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 6U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 7U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_theCount, 8U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_N, 9U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_input, 10U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_saved_in, 11U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_counter, 12U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_Mean, 13U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_StandardDev, 14U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_saved_out, 15U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 4);
  c8_meanSum = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 5);
  c8_varSum = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 7);
  c8_x = c8_N;
  c8_N = c8_x;
  c8_b_x = c8_N;
  c8_N = c8_b_x;
  c8_N = muDoubleScalarRound(c8_N);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 9);
  c8_startval = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 10);
  c8_Ndiv = c8_N;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 11);
  if (CV_EML_IF(0, 1, 0, c8_theCount < c8_N)) {
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 12);
    c8_startval = (c8_N + 1.0) - c8_theCount;
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 13);
    c8_Ndiv = c8_theCount;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 17);
  for (c8_i5 = 0; c8_i5 < 50; c8_i5++) {
    c8_saved_out[c8_i5] = c8_saved_in[c8_i5];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 18);
  c8_b_startval = c8_startval;
  c8_b_N = c8_N;
  c8_i6 = (int32_T)(c8_b_N + (1.0 - c8_b_startval));
  _SFD_FOR_LOOP_VECTOR_CHECK(c8_b_startval, 1.0, c8_b_N, mxDOUBLE_CLASS, c8_i6);
  c8_i = c8_b_startval;
  c8_b_i = 0;
  while (c8_b_i <= c8_i6 - 1) {
    c8_i = c8_b_startval + (real_T)c8_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 19);
    c8_saved_out[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("saved_out",
      (int32_T)_SFD_INTEGER_CHECK("i-1", c8_i - 1.0), 1, 50, 1, 0) - 1] =
      c8_saved_in[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("saved_in",
      (int32_T)_SFD_INTEGER_CHECK("i", c8_i), 1, 50, 1, 0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 20);
    c8_meanSum += c8_saved_in[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
      "saved_in", (int32_T)_SFD_INTEGER_CHECK("i", c8_i), 1, 50, 1, 0) - 1];
    c8_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 22);
  c8_saved_out[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("saved_out",
    (int32_T)_SFD_INTEGER_CHECK("N", c8_N), 1, 50, 1, 0) - 1] = c8_input;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 23);
  c8_meanSum += c8_input;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 25);
  c8_B = c8_Ndiv;
  c8_y = c8_B;
  c8_b_y = c8_y;
  c8_c_y = 1.0 / c8_b_y;
  c8_a = c8_c_y;
  c8_b = c8_meanSum;
  c8_Mean = c8_a * c8_b;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 29);
  c8_d0 = c8_startval - 1.0;
  c8_c_N = c8_N;
  c8_i7 = (int32_T)(c8_c_N + (1.0 - c8_d0));
  _SFD_FOR_LOOP_VECTOR_CHECK(c8_d0, 1.0, c8_c_N, mxDOUBLE_CLASS, c8_i7);
  c8_i = c8_d0;
  c8_c_i = 0;
  while (c8_c_i <= c8_i7 - 1) {
    c8_i = c8_d0 + (real_T)c8_c_i;
    CV_EML_FOR(0, 1, 1, 1);
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 30);
    c8_b_a = c8_saved_out[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
      "saved_out", (int32_T)_SFD_INTEGER_CHECK("i", c8_i), 1, 50, 1, 0) - 1] -
      c8_Mean;
    c8_c_a = c8_b_a;
    c8_d_a = c8_c_a;
    c8_eml_scalar_eg(chartInstance);
    c8_ak = c8_d_a;
    c8_e_a = c8_ak;
    c8_eml_scalar_eg(chartInstance);
    c8_f_a = c8_e_a;
    c8_b_b = c8_e_a;
    c8_varSum = c8_f_a * c8_b_b;
    c8_c_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 1, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 33);
  c8_b_B = c8_Ndiv;
  c8_d_y = c8_b_B;
  c8_e_y = c8_d_y;
  c8_f_y = 1.0 / c8_e_y;
  c8_g_a = c8_f_y;
  c8_c_b = c8_varSum;
  c8_variance = c8_g_a * c8_c_b;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 34);
  c8_c_x = c8_variance;
  c8_StandardDev = c8_c_x;
  if (c8_StandardDev < 0.0) {
    c8_eml_error(chartInstance);
  }

  c8_d_x = c8_StandardDev;
  c8_StandardDev = c8_d_x;
  c8_StandardDev = muDoubleScalarSqrt(c8_StandardDev);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 36);
  c8_counter = c8_theCount + 1.0;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -36);
  _SFD_SYMBOL_SCOPE_POP();
  *c8_b_counter = c8_counter;
  *c8_b_Mean = c8_Mean;
  *c8_b_StandardDev = c8_StandardDev;
  for (c8_i8 = 0; c8_i8 < 50; c8_i8++) {
    (*c8_b_saved_out)[c8_i8] = c8_saved_out[c8_i8];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c8_sfEvent);
}

static void initSimStructsc8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance)
{
}

static void registerMessagesc8_Model_justmodel2
  (SFc8_Model_justmodel2InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber)
{
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i9;
  real_T c8_b_inData[50];
  int32_T c8_i10;
  real_T c8_u[50];
  const mxArray *c8_y = NULL;
  SFc8_Model_justmodel2InstanceStruct *chartInstance;
  chartInstance = (SFc8_Model_justmodel2InstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i9 = 0; c8_i9 < 50; c8_i9++) {
    c8_b_inData[c8_i9] = (*(real_T (*)[50])c8_inData)[c8_i9];
  }

  for (c8_i10 = 0; c8_i10 < 50; c8_i10++) {
    c8_u[c8_i10] = c8_b_inData[c8_i10];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 50), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static void c8_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_saved_out, const char_T *c8_identifier,
  real_T c8_y[50])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_saved_out), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_saved_out);
}

static void c8_b_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[50])
{
  real_T c8_dv1[50];
  int32_T c8_i11;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv1, 1, 0, 0U, 1, 0U, 1, 50);
  for (c8_i11 = 0; c8_i11 < 50; c8_i11++) {
    c8_y[c8_i11] = c8_dv1[c8_i11];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_saved_out;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[50];
  int32_T c8_i12;
  SFc8_Model_justmodel2InstanceStruct *chartInstance;
  chartInstance = (SFc8_Model_justmodel2InstanceStruct *)chartInstanceVoid;
  c8_saved_out = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_saved_out), &c8_thisId,
                        c8_y);
  sf_mex_destroy(&c8_saved_out);
  for (c8_i12 = 0; c8_i12 < 50; c8_i12++) {
    (*(real_T (*)[50])c8_outData)[c8_i12] = c8_y[c8_i12];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_Model_justmodel2InstanceStruct *chartInstance;
  chartInstance = (SFc8_Model_justmodel2InstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static real_T c8_c_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_StandardDev, const char_T *c8_identifier)
{
  real_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_StandardDev),
    &c8_thisId);
  sf_mex_destroy(&c8_StandardDev);
  return c8_y;
}

static real_T c8_d_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d1;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d1, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d1;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_StandardDev;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_Model_justmodel2InstanceStruct *chartInstance;
  chartInstance = (SFc8_Model_justmodel2InstanceStruct *)chartInstanceVoid;
  c8_StandardDev = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_StandardDev),
    &c8_thisId);
  sf_mex_destroy(&c8_StandardDev);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

const mxArray *sf_c8_Model_justmodel2_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo;
  c8_ResolvedFunctionInfo c8_info[18];
  const mxArray *c8_m0 = NULL;
  int32_T c8_i13;
  c8_ResolvedFunctionInfo *c8_r0;
  c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  c8_info_helper(c8_info);
  sf_mex_assign(&c8_m0, sf_mex_createstruct("nameCaptureInfo", 1, 18), FALSE);
  for (c8_i13 = 0; c8_i13 < 18; c8_i13++) {
    c8_r0 = &c8_info[c8_i13];
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->context)), "context", "nameCaptureInfo",
                    c8_i13);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c8_r0->name)), "name", "nameCaptureInfo", c8_i13);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c8_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c8_i13);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", c8_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->resolved)), "resolved", "nameCaptureInfo",
                    c8_i13);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c8_i13);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c8_i13);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c8_i13);
    sf_mex_addfield(c8_m0, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c8_i13);
  }

  sf_mex_assign(&c8_nameCaptureInfo, c8_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c8_nameCaptureInfo);
  return c8_nameCaptureInfo;
}

static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[18])
{
  c8_info[0].context = "";
  c8_info[0].name = "round";
  c8_info[0].dominantType = "double";
  c8_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m";
  c8_info[0].fileTimeLo = 1343830384U;
  c8_info[0].fileTimeHi = 0U;
  c8_info[0].mFileTimeLo = 0U;
  c8_info[0].mFileTimeHi = 0U;
  c8_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m";
  c8_info[1].name = "eml_scalar_round";
  c8_info[1].dominantType = "double";
  c8_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m";
  c8_info[1].fileTimeLo = 1307651238U;
  c8_info[1].fileTimeHi = 0U;
  c8_info[1].mFileTimeLo = 0U;
  c8_info[1].mFileTimeHi = 0U;
  c8_info[2].context = "";
  c8_info[2].name = "mrdivide";
  c8_info[2].dominantType = "double";
  c8_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c8_info[2].fileTimeLo = 1357951548U;
  c8_info[2].fileTimeHi = 0U;
  c8_info[2].mFileTimeLo = 1319729966U;
  c8_info[2].mFileTimeHi = 0U;
  c8_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c8_info[3].name = "rdivide";
  c8_info[3].dominantType = "double";
  c8_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[3].fileTimeLo = 1346510388U;
  c8_info[3].fileTimeHi = 0U;
  c8_info[3].mFileTimeLo = 0U;
  c8_info[3].mFileTimeHi = 0U;
  c8_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[4].name = "eml_scalexp_compatible";
  c8_info[4].dominantType = "double";
  c8_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c8_info[4].fileTimeLo = 1286818796U;
  c8_info[4].fileTimeHi = 0U;
  c8_info[4].mFileTimeLo = 0U;
  c8_info[4].mFileTimeHi = 0U;
  c8_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c8_info[5].name = "eml_div";
  c8_info[5].dominantType = "double";
  c8_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c8_info[5].fileTimeLo = 1313347810U;
  c8_info[5].fileTimeHi = 0U;
  c8_info[5].mFileTimeLo = 0U;
  c8_info[5].mFileTimeHi = 0U;
  c8_info[6].context = "";
  c8_info[6].name = "mtimes";
  c8_info[6].dominantType = "double";
  c8_info[6].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[6].fileTimeLo = 1289519692U;
  c8_info[6].fileTimeHi = 0U;
  c8_info[6].mFileTimeLo = 0U;
  c8_info[6].mFileTimeHi = 0U;
  c8_info[7].context = "";
  c8_info[7].name = "mpower";
  c8_info[7].dominantType = "double";
  c8_info[7].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c8_info[7].fileTimeLo = 1286818842U;
  c8_info[7].fileTimeHi = 0U;
  c8_info[7].mFileTimeLo = 0U;
  c8_info[7].mFileTimeHi = 0U;
  c8_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c8_info[8].name = "power";
  c8_info[8].dominantType = "double";
  c8_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c8_info[8].fileTimeLo = 1348191930U;
  c8_info[8].fileTimeHi = 0U;
  c8_info[8].mFileTimeLo = 0U;
  c8_info[8].mFileTimeHi = 0U;
  c8_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c8_info[9].name = "eml_scalar_eg";
  c8_info[9].dominantType = "double";
  c8_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[9].fileTimeLo = 1286818796U;
  c8_info[9].fileTimeHi = 0U;
  c8_info[9].mFileTimeLo = 0U;
  c8_info[9].mFileTimeHi = 0U;
  c8_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c8_info[10].name = "eml_scalexp_alloc";
  c8_info[10].dominantType = "double";
  c8_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c8_info[10].fileTimeLo = 1352424860U;
  c8_info[10].fileTimeHi = 0U;
  c8_info[10].mFileTimeLo = 0U;
  c8_info[10].mFileTimeHi = 0U;
  c8_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c8_info[11].name = "floor";
  c8_info[11].dominantType = "double";
  c8_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c8_info[11].fileTimeLo = 1343830380U;
  c8_info[11].fileTimeHi = 0U;
  c8_info[11].mFileTimeLo = 0U;
  c8_info[11].mFileTimeHi = 0U;
  c8_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c8_info[12].name = "eml_scalar_floor";
  c8_info[12].dominantType = "double";
  c8_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c8_info[12].fileTimeLo = 1286818726U;
  c8_info[12].fileTimeHi = 0U;
  c8_info[12].mFileTimeLo = 0U;
  c8_info[12].mFileTimeHi = 0U;
  c8_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c8_info[13].name = "eml_scalar_eg";
  c8_info[13].dominantType = "double";
  c8_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c8_info[13].fileTimeLo = 1286818796U;
  c8_info[13].fileTimeHi = 0U;
  c8_info[13].mFileTimeLo = 0U;
  c8_info[13].mFileTimeHi = 0U;
  c8_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c8_info[14].name = "mtimes";
  c8_info[14].dominantType = "double";
  c8_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c8_info[14].fileTimeLo = 1289519692U;
  c8_info[14].fileTimeHi = 0U;
  c8_info[14].mFileTimeLo = 0U;
  c8_info[14].mFileTimeHi = 0U;
  c8_info[15].context = "";
  c8_info[15].name = "sqrt";
  c8_info[15].dominantType = "double";
  c8_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c8_info[15].fileTimeLo = 1343830386U;
  c8_info[15].fileTimeHi = 0U;
  c8_info[15].mFileTimeLo = 0U;
  c8_info[15].mFileTimeHi = 0U;
  c8_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c8_info[16].name = "eml_error";
  c8_info[16].dominantType = "char";
  c8_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c8_info[16].fileTimeLo = 1343830358U;
  c8_info[16].fileTimeHi = 0U;
  c8_info[16].mFileTimeLo = 0U;
  c8_info[16].mFileTimeHi = 0U;
  c8_info[17].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c8_info[17].name = "eml_scalar_sqrt";
  c8_info[17].dominantType = "double";
  c8_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c8_info[17].fileTimeLo = 1286818738U;
  c8_info[17].fileTimeHi = 0U;
  c8_info[17].mFileTimeLo = 0U;
  c8_info[17].mFileTimeHi = 0U;
}

static void c8_eml_scalar_eg(SFc8_Model_justmodel2InstanceStruct *chartInstance)
{
}

static void c8_eml_error(SFc8_Model_justmodel2InstanceStruct *chartInstance)
{
  int32_T c8_i14;
  static char_T c8_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c8_u[30];
  const mxArray *c8_y = NULL;
  int32_T c8_i15;
  static char_T c8_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c8_b_u[4];
  const mxArray *c8_b_y = NULL;
  for (c8_i14 = 0; c8_i14 < 30; c8_i14++) {
    c8_u[c8_i14] = c8_cv0[c8_i14];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  for (c8_i15 = 0; c8_i15 < 4; c8_i15++) {
    c8_b_u[c8_i15] = c8_cv1[c8_i15];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U, 14,
    c8_y, 14, c8_b_y));
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_Model_justmodel2InstanceStruct *chartInstance;
  chartInstance = (SFc8_Model_justmodel2InstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, FALSE);
  return c8_mxArrayOutData;
}

static int32_T c8_e_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i16;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i16, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i16;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_Model_justmodel2InstanceStruct *chartInstance;
  chartInstance = (SFc8_Model_justmodel2InstanceStruct *)chartInstanceVoid;
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

static uint8_T c8_f_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_Model_justmodel2, const
  char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_Model_justmodel2), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_Model_justmodel2);
  return c8_y;
}

static uint8_T c8_g_emlrt_marshallIn(SFc8_Model_justmodel2InstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void init_dsm_address_info(SFc8_Model_justmodel2InstanceStruct
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

void sf_c8_Model_justmodel2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2693999531U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2752981680U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3434808689U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(763146054U);
}

mxArray *sf_c8_Model_justmodel2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("iN2enFToX3SWwyCHGJEPiD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      pr[0] = (double)(50);
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

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      pr[0] = (double)(50);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c8_Model_justmodel2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c8_Model_justmodel2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"Mean\",},{M[1],M[11],T\"StandardDev\",},{M[1],M[10],T\"counter\",},{M[1],M[8],T\"saved_out\",},{M[8],M[0],T\"is_active_c8_Model_justmodel2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_Model_justmodel2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_Model_justmodel2InstanceStruct *chartInstance;
    chartInstance = (SFc8_Model_justmodel2InstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Model_justmodel2MachineNumber_,
           8,
           1,
           1,
           8,
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
          init_script_number_translation(_Model_justmodel2MachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_Model_justmodel2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Model_justmodel2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"counter");
          _SFD_SET_DATA_PROPS(1,1,1,0,"theCount");
          _SFD_SET_DATA_PROPS(2,1,1,0,"N");
          _SFD_SET_DATA_PROPS(3,2,0,1,"Mean");
          _SFD_SET_DATA_PROPS(4,2,0,1,"StandardDev");
          _SFD_SET_DATA_PROPS(5,1,1,0,"input");
          _SFD_SET_DATA_PROPS(6,1,1,0,"saved_in");
          _SFD_SET_DATA_PROPS(7,2,0,1,"saved_out");
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
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,2,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,627);
        _SFD_CV_INIT_EML_IF(0,1,0,161,176,-1,234);
        _SFD_CV_INIT_EML_FOR(0,1,0,288,305,379);
        _SFD_CV_INIT_EML_FOR(0,1,1,482,501,542);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)c8_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)c8_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)c8_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 50;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 50;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          real_T *c8_counter;
          real_T *c8_theCount;
          real_T *c8_N;
          real_T *c8_Mean;
          real_T *c8_StandardDev;
          real_T *c8_input;
          real_T (*c8_saved_in)[50];
          real_T (*c8_saved_out)[50];
          c8_saved_out = (real_T (*)[50])ssGetOutputPortSignal(chartInstance->S,
            4);
          c8_saved_in = (real_T (*)[50])ssGetInputPortSignal(chartInstance->S, 3);
          c8_input = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c8_StandardDev = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c8_Mean = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c8_N = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c8_theCount = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c8_counter = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c8_counter);
          _SFD_SET_DATA_VALUE_PTR(1U, c8_theCount);
          _SFD_SET_DATA_VALUE_PTR(2U, c8_N);
          _SFD_SET_DATA_VALUE_PTR(3U, c8_Mean);
          _SFD_SET_DATA_VALUE_PTR(4U, c8_StandardDev);
          _SFD_SET_DATA_VALUE_PTR(5U, c8_input);
          _SFD_SET_DATA_VALUE_PTR(6U, *c8_saved_in);
          _SFD_SET_DATA_VALUE_PTR(7U, *c8_saved_out);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Model_justmodel2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "NIIbpNADyF6w5W3Wbnw1T";
}

static void sf_opaque_initialize_c8_Model_justmodel2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_Model_justmodel2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*)
    chartInstanceVar);
  initialize_c8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c8_Model_justmodel2(void *chartInstanceVar)
{
  enable_c8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c8_Model_justmodel2(void *chartInstanceVar)
{
  disable_c8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c8_Model_justmodel2(void *chartInstanceVar)
{
  sf_c8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_Model_justmodel2(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_Model_justmodel2
    ((SFc8_Model_justmodel2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_Model_justmodel2();/* state var info */
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

extern void sf_internal_set_sim_state_c8_Model_justmodel2(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_Model_justmodel2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_Model_justmodel2(SimStruct* S)
{
  return sf_internal_get_sim_state_c8_Model_justmodel2(S);
}

static void sf_opaque_set_sim_state_c8_Model_justmodel2(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c8_Model_justmodel2(S, st);
}

static void sf_opaque_terminate_c8_Model_justmodel2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_Model_justmodel2InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Model_justmodel2_optimization_info();
    }

    finalize_c8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_Model_justmodel2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c8_Model_justmodel2((SFc8_Model_justmodel2InstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_Model_justmodel2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Model_justmodel2_optimization_info();
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3037781112U));
  ssSetChecksum1(S,(2352822062U));
  ssSetChecksum2(S,(1125829172U));
  ssSetChecksum3(S,(295639112U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c8_Model_justmodel2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_Model_justmodel2(SimStruct *S)
{
  SFc8_Model_justmodel2InstanceStruct *chartInstance;
  chartInstance = (SFc8_Model_justmodel2InstanceStruct *)utMalloc(sizeof
    (SFc8_Model_justmodel2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc8_Model_justmodel2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_Model_justmodel2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_Model_justmodel2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_Model_justmodel2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c8_Model_justmodel2;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c8_Model_justmodel2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_Model_justmodel2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_Model_justmodel2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_Model_justmodel2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_Model_justmodel2;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_Model_justmodel2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_Model_justmodel2;
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

void c8_Model_justmodel2_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_Model_justmodel2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_Model_justmodel2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_Model_justmodel2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_Model_justmodel2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
