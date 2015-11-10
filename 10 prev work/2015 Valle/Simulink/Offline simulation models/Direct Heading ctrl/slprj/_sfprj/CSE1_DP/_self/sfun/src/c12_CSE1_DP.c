/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_DP_sfun.h"
#include "c12_CSE1_DP.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "CSE1_DP_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c12_debug_family_names[13] = { "L_VSP", "L_BT", "u", "T",
  "tau", "nargin", "nargout", "F_y_BT", "F_x_VSP", "F_y_VSP", "tau_u", "tau_v",
  "tau_r" };

/* Function Declarations */
static void initialize_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance);
static void initialize_params_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct
  *chartInstance);
static void enable_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance);
static void disable_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance);
static void c12_update_debugger_state_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct
  *chartInstance);
static void set_sim_state_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_st);
static void finalize_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance);
static void sf_gateway_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance);
static void initSimStructsc12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber, uint32_T c12_instanceNumber);
static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static real_T c12_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_tau_r, const char_T *c12_identifier);
static real_T c12_b_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_c_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[3]);
static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_info_helper(const mxArray **c12_info);
static const mxArray *c12_emlrt_marshallOut(const char * c12_u);
static const mxArray *c12_b_emlrt_marshallOut(const uint32_T c12_u);
static void c12_eml_scalar_eg(SFc12_CSE1_DPInstanceStruct *chartInstance);
static void c12_eml_xgemm(SFc12_CSE1_DPInstanceStruct *chartInstance, real_T
  c12_A[9], real_T c12_B[3], real_T c12_C[3], real_T c12_b_C[3]);
static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static int32_T c12_d_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static uint8_T c12_e_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_b_is_active_c12_CSE1_DP, const char_T *c12_identifier);
static uint8_T c12_f_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_b_eml_xgemm(SFc12_CSE1_DPInstanceStruct *chartInstance, real_T
  c12_A[9], real_T c12_B[3], real_T c12_C[3]);
static void init_dsm_address_info(SFc12_CSE1_DPInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance)
{
  chartInstance->c12_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c12_is_active_c12_CSE1_DP = 0U;
}

static void initialize_params_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c12_update_debugger_state_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct
  *chartInstance)
{
  const mxArray *c12_st;
  const mxArray *c12_y = NULL;
  real_T c12_hoistedGlobal;
  real_T c12_u;
  const mxArray *c12_b_y = NULL;
  real_T c12_b_hoistedGlobal;
  real_T c12_b_u;
  const mxArray *c12_c_y = NULL;
  real_T c12_c_hoistedGlobal;
  real_T c12_c_u;
  const mxArray *c12_d_y = NULL;
  uint8_T c12_d_hoistedGlobal;
  uint8_T c12_d_u;
  const mxArray *c12_e_y = NULL;
  real_T *c12_tau_r;
  real_T *c12_tau_u;
  real_T *c12_tau_v;
  c12_tau_r = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c12_tau_v = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c12_tau_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c12_st = NULL;
  c12_st = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_createcellmatrix(4, 1), false);
  c12_hoistedGlobal = *c12_tau_r;
  c12_u = c12_hoistedGlobal;
  c12_b_y = NULL;
  sf_mex_assign(&c12_b_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c12_y, 0, c12_b_y);
  c12_b_hoistedGlobal = *c12_tau_u;
  c12_b_u = c12_b_hoistedGlobal;
  c12_c_y = NULL;
  sf_mex_assign(&c12_c_y, sf_mex_create("y", &c12_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c12_y, 1, c12_c_y);
  c12_c_hoistedGlobal = *c12_tau_v;
  c12_c_u = c12_c_hoistedGlobal;
  c12_d_y = NULL;
  sf_mex_assign(&c12_d_y, sf_mex_create("y", &c12_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c12_y, 2, c12_d_y);
  c12_d_hoistedGlobal = chartInstance->c12_is_active_c12_CSE1_DP;
  c12_d_u = c12_d_hoistedGlobal;
  c12_e_y = NULL;
  sf_mex_assign(&c12_e_y, sf_mex_create("y", &c12_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c12_y, 3, c12_e_y);
  sf_mex_assign(&c12_st, c12_y, false);
  return c12_st;
}

static void set_sim_state_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_st)
{
  const mxArray *c12_u;
  real_T *c12_tau_r;
  real_T *c12_tau_u;
  real_T *c12_tau_v;
  c12_tau_r = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c12_tau_v = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c12_tau_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c12_doneDoubleBufferReInit = true;
  c12_u = sf_mex_dup(c12_st);
  *c12_tau_r = c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c12_u, 0)), "tau_r");
  *c12_tau_u = c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c12_u, 1)), "tau_u");
  *c12_tau_v = c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c12_u, 2)), "tau_v");
  chartInstance->c12_is_active_c12_CSE1_DP = c12_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 3)),
     "is_active_c12_CSE1_DP");
  sf_mex_destroy(&c12_u);
  c12_update_debugger_state_c12_CSE1_DP(chartInstance);
  sf_mex_destroy(&c12_st);
}

static void finalize_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance)
{
  real_T c12_hoistedGlobal;
  real_T c12_b_hoistedGlobal;
  real_T c12_c_hoistedGlobal;
  real_T c12_F_y_BT;
  real_T c12_F_x_VSP;
  real_T c12_F_y_VSP;
  uint32_T c12_debug_family_var_map[13];
  real_T c12_L_VSP;
  real_T c12_L_BT;
  real_T c12_u[3];
  real_T c12_T[9];
  real_T c12_tau[3];
  real_T c12_nargin = 3.0;
  real_T c12_nargout = 3.0;
  real_T c12_tau_u;
  real_T c12_tau_v;
  real_T c12_tau_r;
  int32_T c12_i0;
  static real_T c12_a[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, -0.4575, 0.0, 1.0, 0.3875
  };

  int32_T c12_i1;
  real_T c12_b[3];
  int32_T c12_i2;
  int32_T c12_i3;
  int32_T c12_i4;
  real_T c12_dv0[9];
  int32_T c12_i5;
  real_T c12_dv1[3];
  int32_T c12_i6;
  real_T c12_dv2[9];
  int32_T c12_i7;
  real_T c12_dv3[3];
  real_T *c12_b_tau_r;
  real_T *c12_b_tau_v;
  real_T *c12_b_tau_u;
  real_T *c12_b_F_y_VSP;
  real_T *c12_b_F_x_VSP;
  real_T *c12_b_F_y_BT;
  c12_b_tau_r = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c12_b_tau_v = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c12_b_F_y_VSP = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c12_b_F_x_VSP = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c12_b_tau_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c12_b_F_y_BT = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c12_b_F_y_BT, 0U);
  chartInstance->c12_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  c12_hoistedGlobal = *c12_b_F_y_BT;
  c12_b_hoistedGlobal = *c12_b_F_x_VSP;
  c12_c_hoistedGlobal = *c12_b_F_y_VSP;
  c12_F_y_BT = c12_hoistedGlobal;
  c12_F_x_VSP = c12_b_hoistedGlobal;
  c12_F_y_VSP = c12_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c12_debug_family_names,
    c12_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_L_VSP, 0U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_L_BT, 1U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_u, 2U, c12_b_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_T, 3U, c12_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_tau, 4U, c12_b_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargin, 5U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargout, 6U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_F_y_BT, 7U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_F_x_VSP, 8U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_F_y_VSP, 9U, c12_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_tau_u, 10U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_tau_v, 11U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_tau_r, 12U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 4);
  c12_L_VSP = -0.4575;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 5);
  c12_L_BT = 0.3875;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 7);
  c12_u[0] = c12_F_x_VSP;
  c12_u[1] = c12_F_y_VSP;
  c12_u[2] = c12_F_y_BT;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 9);
  for (c12_i0 = 0; c12_i0 < 9; c12_i0++) {
    c12_T[c12_i0] = c12_a[c12_i0];
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 13);
  for (c12_i1 = 0; c12_i1 < 3; c12_i1++) {
    c12_b[c12_i1] = c12_u[c12_i1];
  }

  c12_eml_scalar_eg(chartInstance);
  c12_eml_scalar_eg(chartInstance);
  for (c12_i2 = 0; c12_i2 < 3; c12_i2++) {
    c12_tau[c12_i2] = 0.0;
  }

  for (c12_i3 = 0; c12_i3 < 3; c12_i3++) {
    c12_tau[c12_i3] = 0.0;
  }

  for (c12_i4 = 0; c12_i4 < 9; c12_i4++) {
    c12_dv0[c12_i4] = c12_a[c12_i4];
  }

  for (c12_i5 = 0; c12_i5 < 3; c12_i5++) {
    c12_dv1[c12_i5] = c12_b[c12_i5];
  }

  for (c12_i6 = 0; c12_i6 < 9; c12_i6++) {
    c12_dv2[c12_i6] = c12_dv0[c12_i6];
  }

  for (c12_i7 = 0; c12_i7 < 3; c12_i7++) {
    c12_dv3[c12_i7] = c12_dv1[c12_i7];
  }

  c12_b_eml_xgemm(chartInstance, c12_dv2, c12_dv3, c12_tau);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 15);
  c12_tau_u = c12_tau[0];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 16);
  c12_tau_v = c12_tau[1];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 17);
  c12_tau_r = c12_tau[2];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, -17);
  _SFD_SYMBOL_SCOPE_POP();
  *c12_b_tau_u = c12_tau_u;
  *c12_b_tau_v = c12_tau_v;
  *c12_b_tau_r = c12_tau_r;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c12_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_DPMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c12_b_tau_u, 1U);
  _SFD_DATA_RANGE_CHECK(*c12_b_F_x_VSP, 2U);
  _SFD_DATA_RANGE_CHECK(*c12_b_F_y_VSP, 3U);
  _SFD_DATA_RANGE_CHECK(*c12_b_tau_v, 4U);
  _SFD_DATA_RANGE_CHECK(*c12_b_tau_r, 5U);
}

static void initSimStructsc12_CSE1_DP(SFc12_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber, uint32_T c12_instanceNumber)
{
  (void)c12_machineNumber;
  (void)c12_chartNumber;
  (void)c12_instanceNumber;
}

static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  real_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc12_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(real_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, false);
  return c12_mxArrayOutData;
}

static real_T c12_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_tau_r, const char_T *c12_identifier)
{
  real_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_tau_r),
    &c12_thisId);
  sf_mex_destroy(&c12_tau_r);
  return c12_y;
}

static real_T c12_b_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  real_T c12_y;
  real_T c12_d0;
  (void)chartInstance;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_d0, 1, 0, 0U, 0, 0U, 0);
  c12_y = c12_d0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_tau_r;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y;
  SFc12_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc12_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c12_tau_r = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_tau_r),
    &c12_thisId);
  sf_mex_destroy(&c12_tau_r);
  *(real_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i8;
  real_T c12_b_inData[3];
  int32_T c12_i9;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc12_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i8 = 0; c12_i8 < 3; c12_i8++) {
    c12_b_inData[c12_i8] = (*(real_T (*)[3])c12_inData)[c12_i8];
  }

  for (c12_i9 = 0; c12_i9 < 3; c12_i9++) {
    c12_u[c12_i9] = c12_b_inData[c12_i9];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, false);
  return c12_mxArrayOutData;
}

static void c12_c_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId, real_T c12_y[3])
{
  real_T c12_dv4[3];
  int32_T c12_i10;
  (void)chartInstance;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv4, 1, 0, 0U, 1, 0U, 1, 3);
  for (c12_i10 = 0; c12_i10 < 3; c12_i10++) {
    c12_y[c12_i10] = c12_dv4[c12_i10];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_tau;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[3];
  int32_T c12_i11;
  SFc12_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc12_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c12_tau = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_tau), &c12_thisId, c12_y);
  sf_mex_destroy(&c12_tau);
  for (c12_i11 = 0; c12_i11 < 3; c12_i11++) {
    (*(real_T (*)[3])c12_outData)[c12_i11] = c12_y[c12_i11];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i12;
  int32_T c12_i13;
  int32_T c12_i14;
  real_T c12_b_inData[9];
  int32_T c12_i15;
  int32_T c12_i16;
  int32_T c12_i17;
  real_T c12_u[9];
  const mxArray *c12_y = NULL;
  SFc12_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc12_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_i12 = 0;
  for (c12_i13 = 0; c12_i13 < 3; c12_i13++) {
    for (c12_i14 = 0; c12_i14 < 3; c12_i14++) {
      c12_b_inData[c12_i14 + c12_i12] = (*(real_T (*)[9])c12_inData)[c12_i14 +
        c12_i12];
    }

    c12_i12 += 3;
  }

  c12_i15 = 0;
  for (c12_i16 = 0; c12_i16 < 3; c12_i16++) {
    for (c12_i17 = 0; c12_i17 < 3; c12_i17++) {
      c12_u[c12_i17 + c12_i15] = c12_b_inData[c12_i17 + c12_i15];
    }

    c12_i15 += 3;
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, false);
  return c12_mxArrayOutData;
}

const mxArray *sf_c12_CSE1_DP_get_eml_resolved_functions_info(void)
{
  const mxArray *c12_nameCaptureInfo = NULL;
  c12_nameCaptureInfo = NULL;
  sf_mex_assign(&c12_nameCaptureInfo, sf_mex_createstruct("structure", 2, 13, 1),
                false);
  c12_info_helper(&c12_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c12_nameCaptureInfo);
  return c12_nameCaptureInfo;
}

static void c12_info_helper(const mxArray **c12_info)
{
  const mxArray *c12_rhs0 = NULL;
  const mxArray *c12_lhs0 = NULL;
  const mxArray *c12_rhs1 = NULL;
  const mxArray *c12_lhs1 = NULL;
  const mxArray *c12_rhs2 = NULL;
  const mxArray *c12_lhs2 = NULL;
  const mxArray *c12_rhs3 = NULL;
  const mxArray *c12_lhs3 = NULL;
  const mxArray *c12_rhs4 = NULL;
  const mxArray *c12_lhs4 = NULL;
  const mxArray *c12_rhs5 = NULL;
  const mxArray *c12_lhs5 = NULL;
  const mxArray *c12_rhs6 = NULL;
  const mxArray *c12_lhs6 = NULL;
  const mxArray *c12_rhs7 = NULL;
  const mxArray *c12_lhs7 = NULL;
  const mxArray *c12_rhs8 = NULL;
  const mxArray *c12_lhs8 = NULL;
  const mxArray *c12_rhs9 = NULL;
  const mxArray *c12_lhs9 = NULL;
  const mxArray *c12_rhs10 = NULL;
  const mxArray *c12_lhs10 = NULL;
  const mxArray *c12_rhs11 = NULL;
  const mxArray *c12_lhs11 = NULL;
  const mxArray *c12_rhs12 = NULL;
  const mxArray *c12_lhs12 = NULL;
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c12_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c12_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 2);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c12_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c12_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c12_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  5);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c12_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 6);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c12_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 7);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c12_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 8);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 8);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c12_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 9);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "coder.internal.blas.threshold"), "name", "name", 9);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c12_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 10);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 10);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c12_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 11);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c12_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "coder.internal.refblas.xgemm"), "name", "name", 12);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c12_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs12), "lhs", "lhs",
                  12);
  sf_mex_destroy(&c12_rhs0);
  sf_mex_destroy(&c12_lhs0);
  sf_mex_destroy(&c12_rhs1);
  sf_mex_destroy(&c12_lhs1);
  sf_mex_destroy(&c12_rhs2);
  sf_mex_destroy(&c12_lhs2);
  sf_mex_destroy(&c12_rhs3);
  sf_mex_destroy(&c12_lhs3);
  sf_mex_destroy(&c12_rhs4);
  sf_mex_destroy(&c12_lhs4);
  sf_mex_destroy(&c12_rhs5);
  sf_mex_destroy(&c12_lhs5);
  sf_mex_destroy(&c12_rhs6);
  sf_mex_destroy(&c12_lhs6);
  sf_mex_destroy(&c12_rhs7);
  sf_mex_destroy(&c12_lhs7);
  sf_mex_destroy(&c12_rhs8);
  sf_mex_destroy(&c12_lhs8);
  sf_mex_destroy(&c12_rhs9);
  sf_mex_destroy(&c12_lhs9);
  sf_mex_destroy(&c12_rhs10);
  sf_mex_destroy(&c12_lhs10);
  sf_mex_destroy(&c12_rhs11);
  sf_mex_destroy(&c12_lhs11);
  sf_mex_destroy(&c12_rhs12);
  sf_mex_destroy(&c12_lhs12);
}

static const mxArray *c12_emlrt_marshallOut(const char * c12_u)
{
  const mxArray *c12_y = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c12_u)), false);
  return c12_y;
}

static const mxArray *c12_b_emlrt_marshallOut(const uint32_T c12_u)
{
  const mxArray *c12_y = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 7, 0U, 0U, 0U, 0), false);
  return c12_y;
}

static void c12_eml_scalar_eg(SFc12_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c12_eml_xgemm(SFc12_CSE1_DPInstanceStruct *chartInstance, real_T
  c12_A[9], real_T c12_B[3], real_T c12_C[3], real_T c12_b_C[3])
{
  int32_T c12_i18;
  int32_T c12_i19;
  real_T c12_b_A[9];
  int32_T c12_i20;
  real_T c12_b_B[3];
  for (c12_i18 = 0; c12_i18 < 3; c12_i18++) {
    c12_b_C[c12_i18] = c12_C[c12_i18];
  }

  for (c12_i19 = 0; c12_i19 < 9; c12_i19++) {
    c12_b_A[c12_i19] = c12_A[c12_i19];
  }

  for (c12_i20 = 0; c12_i20 < 3; c12_i20++) {
    c12_b_B[c12_i20] = c12_B[c12_i20];
  }

  c12_b_eml_xgemm(chartInstance, c12_b_A, c12_b_B, c12_b_C);
}

static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc12_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(int32_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, false);
  return c12_mxArrayOutData;
}

static int32_T c12_d_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  int32_T c12_y;
  int32_T c12_i21;
  (void)chartInstance;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_i21, 1, 6, 0U, 0, 0U, 0);
  c12_y = c12_i21;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_b_sfEvent;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  int32_T c12_y;
  SFc12_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc12_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c12_b_sfEvent = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_b_sfEvent),
    &c12_thisId);
  sf_mex_destroy(&c12_b_sfEvent);
  *(int32_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static uint8_T c12_e_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_b_is_active_c12_CSE1_DP, const char_T *c12_identifier)
{
  uint8_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c12_b_is_active_c12_CSE1_DP), &c12_thisId);
  sf_mex_destroy(&c12_b_is_active_c12_CSE1_DP);
  return c12_y;
}

static uint8_T c12_f_emlrt_marshallIn(SFc12_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint8_T c12_y;
  uint8_T c12_u0;
  (void)chartInstance;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u0, 1, 3, 0U, 0, 0U, 0);
  c12_y = c12_u0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_b_eml_xgemm(SFc12_CSE1_DPInstanceStruct *chartInstance, real_T
  c12_A[9], real_T c12_B[3], real_T c12_C[3])
{
  int32_T c12_i22;
  int32_T c12_i23;
  int32_T c12_i24;
  (void)chartInstance;
  for (c12_i22 = 0; c12_i22 < 3; c12_i22++) {
    c12_C[c12_i22] = 0.0;
    c12_i23 = 0;
    for (c12_i24 = 0; c12_i24 < 3; c12_i24++) {
      c12_C[c12_i22] += c12_A[c12_i23 + c12_i22] * c12_B[c12_i24];
      c12_i23 += 3;
    }
  }
}

static void init_dsm_address_info(SFc12_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
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

void sf_c12_CSE1_DP_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3474120945U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(286852506U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3078481285U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3608223458U);
}

mxArray *sf_c12_CSE1_DP_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("K4XK4stm5HItb464S4fdKE");
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c12_CSE1_DP_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c12_CSE1_DP_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c12_CSE1_DP(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[9],T\"tau_r\",},{M[1],M[5],T\"tau_u\",},{M[1],M[8],T\"tau_v\",},{M[8],M[0],T\"is_active_c12_CSE1_DP\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c12_CSE1_DP_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc12_CSE1_DPInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc12_CSE1_DPInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_DPMachineNumber_,
           12,
           1,
           1,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_CSE1_DPMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_CSE1_DPMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _CSE1_DPMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"F_y_BT");
          _SFD_SET_DATA_PROPS(1,2,0,1,"tau_u");
          _SFD_SET_DATA_PROPS(2,1,1,0,"F_x_VSP");
          _SFD_SET_DATA_PROPS(3,1,1,0,"F_y_VSP");
          _SFD_SET_DATA_PROPS(4,2,0,1,"tau_v");
          _SFD_SET_DATA_PROPS(5,2,0,1,"tau_r");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,244);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)c12_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)c12_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)c12_sf_marshallIn);

        {
          real_T *c12_F_y_BT;
          real_T *c12_tau_u;
          real_T *c12_F_x_VSP;
          real_T *c12_F_y_VSP;
          real_T *c12_tau_v;
          real_T *c12_tau_r;
          c12_tau_r = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c12_tau_v = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c12_F_y_VSP = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c12_F_x_VSP = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c12_tau_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c12_F_y_BT = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c12_F_y_BT);
          _SFD_SET_DATA_VALUE_PTR(1U, c12_tau_u);
          _SFD_SET_DATA_VALUE_PTR(2U, c12_F_x_VSP);
          _SFD_SET_DATA_VALUE_PTR(3U, c12_F_y_VSP);
          _SFD_SET_DATA_VALUE_PTR(4U, c12_tau_v);
          _SFD_SET_DATA_VALUE_PTR(5U, c12_tau_r);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _CSE1_DPMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "hhO60cW3dFdG8jxKxZ0McE";
}

static void sf_opaque_initialize_c12_CSE1_DP(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar);
  initialize_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c12_CSE1_DP(void *chartInstanceVar)
{
  enable_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c12_CSE1_DP(void *chartInstanceVar)
{
  disable_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c12_CSE1_DP(void *chartInstanceVar)
{
  sf_gateway_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c12_CSE1_DP(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_CSE1_DP();/* state var info */
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

extern void sf_internal_set_sim_state_c12_CSE1_DP(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c12_CSE1_DP();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c12_CSE1_DP(SimStruct* S)
{
  return sf_internal_get_sim_state_c12_CSE1_DP(S);
}

static void sf_opaque_set_sim_state_c12_CSE1_DP(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c12_CSE1_DP(S, st);
}

static void sf_opaque_terminate_c12_CSE1_DP(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_DP_optimization_info();
    }

    finalize_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c12_CSE1_DP(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c12_CSE1_DP((SFc12_CSE1_DPInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c12_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_DP_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      12);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,12,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,12,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,12);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,12,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,12,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,12);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4025125190U));
  ssSetChecksum1(S,(1739357836U));
  ssSetChecksum2(S,(584562459U));
  ssSetChecksum3(S,(373661121U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c12_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c12_CSE1_DP(SimStruct *S)
{
  SFc12_CSE1_DPInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc12_CSE1_DPInstanceStruct *)utMalloc(sizeof
    (SFc12_CSE1_DPInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc12_CSE1_DPInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c12_CSE1_DP;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c12_CSE1_DP;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c12_CSE1_DP;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c12_CSE1_DP;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c12_CSE1_DP;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c12_CSE1_DP;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c12_CSE1_DP;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c12_CSE1_DP;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c12_CSE1_DP;
  chartInstance->chartInfo.mdlStart = mdlStart_c12_CSE1_DP;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c12_CSE1_DP;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c12_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c12_CSE1_DP(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c12_CSE1_DP(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c12_CSE1_DP(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c12_CSE1_DP_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
