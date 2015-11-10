/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_DP_sfun.h"
#include "c13_CSE1_DP.h"
#include "mwmathutil.h"
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
static const char * c13_debug_family_names[15] = { "u", "a", "b", "c", "d", "y0",
  "a0", "a1", "b1", "c1", "nargin", "nargout", "u_BT", "nu", "F_y" };

/* Function Declarations */
static void initialize_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance);
static void initialize_params_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct
  *chartInstance);
static void enable_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance);
static void disable_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance);
static void c13_update_debugger_state_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct
  *chartInstance);
static void set_sim_state_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_st);
static void finalize_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance);
static void sf_gateway_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance);
static void initSimStructsc13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber, uint32_T c13_instanceNumber);
static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static real_T c13_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_F_y, const char_T *c13_identifier);
static real_T c13_b_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_info_helper(const mxArray **c13_info);
static const mxArray *c13_emlrt_marshallOut(const char * c13_u);
static const mxArray *c13_b_emlrt_marshallOut(const uint32_T c13_u);
static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static int32_T c13_c_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static uint8_T c13_d_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_b_is_active_c13_CSE1_DP, const char_T *c13_identifier);
static uint8_T c13_e_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void init_dsm_address_info(SFc13_CSE1_DPInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance)
{
  chartInstance->c13_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c13_is_active_c13_CSE1_DP = 0U;
}

static void initialize_params_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c13_update_debugger_state_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct
  *chartInstance)
{
  const mxArray *c13_st;
  const mxArray *c13_y = NULL;
  real_T c13_hoistedGlobal;
  real_T c13_u;
  const mxArray *c13_b_y = NULL;
  uint8_T c13_b_hoistedGlobal;
  uint8_T c13_b_u;
  const mxArray *c13_c_y = NULL;
  real_T *c13_F_y;
  c13_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c13_st = NULL;
  c13_st = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_createcellmatrix(2, 1), false);
  c13_hoistedGlobal = *c13_F_y;
  c13_u = c13_hoistedGlobal;
  c13_b_y = NULL;
  sf_mex_assign(&c13_b_y, sf_mex_create("y", &c13_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c13_y, 0, c13_b_y);
  c13_b_hoistedGlobal = chartInstance->c13_is_active_c13_CSE1_DP;
  c13_b_u = c13_b_hoistedGlobal;
  c13_c_y = NULL;
  sf_mex_assign(&c13_c_y, sf_mex_create("y", &c13_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c13_y, 1, c13_c_y);
  sf_mex_assign(&c13_st, c13_y, false);
  return c13_st;
}

static void set_sim_state_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_st)
{
  const mxArray *c13_u;
  real_T *c13_F_y;
  c13_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c13_doneDoubleBufferReInit = true;
  c13_u = sf_mex_dup(c13_st);
  *c13_F_y = c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u,
    0)), "F_y");
  chartInstance->c13_is_active_c13_CSE1_DP = c13_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 1)),
     "is_active_c13_CSE1_DP");
  sf_mex_destroy(&c13_u);
  c13_update_debugger_state_c13_CSE1_DP(chartInstance);
  sf_mex_destroy(&c13_st);
}

static void finalize_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance)
{
  real_T c13_hoistedGlobal;
  real_T c13_u_BT;
  int32_T c13_i0;
  real_T c13_nu[3];
  uint32_T c13_debug_family_var_map[15];
  real_T c13_u;
  real_T c13_a;
  real_T c13_b;
  real_T c13_c;
  real_T c13_d;
  real_T c13_y0;
  real_T c13_a0;
  real_T c13_a1;
  real_T c13_b1;
  real_T c13_c1;
  real_T c13_nargin = 2.0;
  real_T c13_nargout = 1.0;
  real_T c13_F_y;
  real_T c13_x;
  real_T c13_b_x;
  real_T c13_c_x;
  real_T c13_d_x;
  real_T c13_e_x;
  real_T c13_f_x;
  real_T c13_g_x;
  real_T c13_h_x;
  real_T c13_i_x;
  real_T c13_j_x;
  real_T c13_A;
  real_T c13_k_x;
  real_T c13_l_x;
  real_T c13_m_x;
  int32_T c13_i1;
  real_T *c13_b_u_BT;
  real_T *c13_b_F_y;
  real_T (*c13_b_nu)[3];
  c13_b_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c13_b_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c13_b_u_BT = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c13_b_u_BT, 0U);
  chartInstance->c13_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  c13_hoistedGlobal = *c13_b_u_BT;
  c13_u_BT = c13_hoistedGlobal;
  for (c13_i0 = 0; c13_i0 < 3; c13_i0++) {
    c13_nu[c13_i0] = (*c13_b_nu)[c13_i0];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 15U, 15U, c13_debug_family_names,
    c13_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_u, 0U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_a, 1U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_b, 2U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_c, 3U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_d, 4U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_y0, 5U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_a0, 6U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_a1, 7U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_b1, 8U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_c1, 9U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargin, 10U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargout, 11U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_u_BT, 12U, c13_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_nu, 13U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_F_y, 14U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 3);
  c13_u = c13_nu[0];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 5);
  if (CV_EML_IF(0, 1, 0, c13_u_BT > 0.0879)) {
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 6);
    c13_a = 2.515;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 7);
    c13_b = 0.1174;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 8);
    c13_c = -2.807;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 9);
    c13_d = -1.131;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 10);
    c13_x = 0.1174 * c13_u_BT;
    c13_b_x = c13_x;
    c13_b_x = muDoubleScalarExp(c13_b_x);
    c13_c_x = -1.131 * c13_u_BT;
    c13_d_x = c13_c_x;
    c13_d_x = muDoubleScalarExp(c13_d_x);
    c13_y0 = 2.515 * c13_b_x + -2.807 * c13_d_x;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 11);
    if (CV_EML_IF(0, 1, 1, c13_u_BT < -0.059)) {
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 12);
      c13_a = -548.0;
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 13);
      c13_b = 0.193;
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 14);
      c13_c = 548.2;
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 15);
      c13_d = 0.1992;
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 16);
      c13_e_x = 0.193 * c13_u_BT;
      c13_f_x = c13_e_x;
      c13_f_x = muDoubleScalarExp(c13_f_x);
      c13_g_x = 0.1992 * c13_u_BT;
      c13_h_x = c13_g_x;
      c13_h_x = muDoubleScalarExp(c13_h_x);
      c13_y0 = -548.0 * c13_f_x + 548.2 * c13_h_x;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 18);
      c13_y0 = 0.0;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 21);
  c13_a0 = 0.7561;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 22);
  c13_a1 = 0.3075;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 23);
  c13_b1 = -10.22;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 24);
  c13_c1 = 2.947;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 25);
  c13_i_x = -10.22 * c13_u + c13_c1;
  c13_j_x = c13_i_x;
  c13_j_x = muDoubleScalarAtan(c13_j_x);
  c13_A = c13_y0 * (c13_a0 + 0.3075 * c13_j_x);
  c13_k_x = c13_A;
  c13_l_x = c13_k_x;
  c13_m_x = c13_l_x;
  c13_F_y = c13_m_x / 1.1385;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, -25);
  _SFD_SYMBOL_SCOPE_POP();
  *c13_b_F_y = c13_F_y;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_DPMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c13_b_F_y, 1U);
  for (c13_i1 = 0; c13_i1 < 3; c13_i1++) {
    _SFD_DATA_RANGE_CHECK((*c13_b_nu)[c13_i1], 2U);
  }
}

static void initSimStructsc13_CSE1_DP(SFc13_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber, uint32_T c13_instanceNumber)
{
  (void)c13_machineNumber;
  (void)c13_chartNumber;
  (void)c13_instanceNumber;
}

static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  real_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(real_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, false);
  return c13_mxArrayOutData;
}

static real_T c13_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_F_y, const char_T *c13_identifier)
{
  real_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_F_y), &c13_thisId);
  sf_mex_destroy(&c13_F_y);
  return c13_y;
}

static real_T c13_b_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  real_T c13_y;
  real_T c13_d0;
  (void)chartInstance;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_d0, 1, 0, 0U, 0, 0U, 0);
  c13_y = c13_d0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_F_y;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y;
  SFc13_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c13_F_y = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_F_y), &c13_thisId);
  sf_mex_destroy(&c13_F_y);
  *(real_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i2;
  real_T c13_b_inData[3];
  int32_T c13_i3;
  real_T c13_u[3];
  const mxArray *c13_y = NULL;
  SFc13_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i2 = 0; c13_i2 < 3; c13_i2++) {
    c13_b_inData[c13_i2] = (*(real_T (*)[3])c13_inData)[c13_i2];
  }

  for (c13_i3 = 0; c13_i3 < 3; c13_i3++) {
    c13_u[c13_i3] = c13_b_inData[c13_i3];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, false);
  return c13_mxArrayOutData;
}

const mxArray *sf_c13_CSE1_DP_get_eml_resolved_functions_info(void)
{
  const mxArray *c13_nameCaptureInfo = NULL;
  c13_nameCaptureInfo = NULL;
  sf_mex_assign(&c13_nameCaptureInfo, sf_mex_createstruct("structure", 2, 11, 1),
                false);
  c13_info_helper(&c13_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c13_nameCaptureInfo);
  return c13_nameCaptureInfo;
}

static void c13_info_helper(const mxArray **c13_info)
{
  const mxArray *c13_rhs0 = NULL;
  const mxArray *c13_lhs0 = NULL;
  const mxArray *c13_rhs1 = NULL;
  const mxArray *c13_lhs1 = NULL;
  const mxArray *c13_rhs2 = NULL;
  const mxArray *c13_lhs2 = NULL;
  const mxArray *c13_rhs3 = NULL;
  const mxArray *c13_lhs3 = NULL;
  const mxArray *c13_rhs4 = NULL;
  const mxArray *c13_lhs4 = NULL;
  const mxArray *c13_rhs5 = NULL;
  const mxArray *c13_lhs5 = NULL;
  const mxArray *c13_rhs6 = NULL;
  const mxArray *c13_lhs6 = NULL;
  const mxArray *c13_rhs7 = NULL;
  const mxArray *c13_lhs7 = NULL;
  const mxArray *c13_rhs8 = NULL;
  const mxArray *c13_lhs8 = NULL;
  const mxArray *c13_rhs9 = NULL;
  const mxArray *c13_lhs9 = NULL;
  const mxArray *c13_rhs10 = NULL;
  const mxArray *c13_lhs10 = NULL;
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("exp"), "name", "name", 0);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/exp.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1343830380U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c13_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/exp.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalar_exp"), "name",
                  "name", 1);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_exp.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1301328464U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c13_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("atan"), "name", "name", 2);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c13_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalar_atan"), "name",
                  "name", 3);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286818718U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c13_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(""), "context", "context", 4);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("mrdivide"), "name", "name",
                  4);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c13_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 5);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 5);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c13_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 6);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("rdivide"), "name", "name", 6);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c13_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 7);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c13_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 8);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c13_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("eml_div"), "name", "name", 9);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c13_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 10);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c13_info, c13_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c13_info, c13_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c13_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c13_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c13_info, sf_mex_duplicatearraysafe(&c13_lhs10), "lhs", "lhs",
                  10);
  sf_mex_destroy(&c13_rhs0);
  sf_mex_destroy(&c13_lhs0);
  sf_mex_destroy(&c13_rhs1);
  sf_mex_destroy(&c13_lhs1);
  sf_mex_destroy(&c13_rhs2);
  sf_mex_destroy(&c13_lhs2);
  sf_mex_destroy(&c13_rhs3);
  sf_mex_destroy(&c13_lhs3);
  sf_mex_destroy(&c13_rhs4);
  sf_mex_destroy(&c13_lhs4);
  sf_mex_destroy(&c13_rhs5);
  sf_mex_destroy(&c13_lhs5);
  sf_mex_destroy(&c13_rhs6);
  sf_mex_destroy(&c13_lhs6);
  sf_mex_destroy(&c13_rhs7);
  sf_mex_destroy(&c13_lhs7);
  sf_mex_destroy(&c13_rhs8);
  sf_mex_destroy(&c13_lhs8);
  sf_mex_destroy(&c13_rhs9);
  sf_mex_destroy(&c13_lhs9);
  sf_mex_destroy(&c13_rhs10);
  sf_mex_destroy(&c13_lhs10);
}

static const mxArray *c13_emlrt_marshallOut(const char * c13_u)
{
  const mxArray *c13_y = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c13_u)), false);
  return c13_y;
}

static const mxArray *c13_b_emlrt_marshallOut(const uint32_T c13_u)
{
  const mxArray *c13_y = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 7, 0U, 0U, 0U, 0), false);
  return c13_y;
}

static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(int32_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, false);
  return c13_mxArrayOutData;
}

static int32_T c13_c_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  int32_T c13_y;
  int32_T c13_i4;
  (void)chartInstance;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_i4, 1, 6, 0U, 0, 0U, 0);
  c13_y = c13_i4;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_b_sfEvent;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  int32_T c13_y;
  SFc13_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c13_b_sfEvent = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_b_sfEvent),
    &c13_thisId);
  sf_mex_destroy(&c13_b_sfEvent);
  *(int32_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static uint8_T c13_d_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_b_is_active_c13_CSE1_DP, const char_T *c13_identifier)
{
  uint8_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_b_is_active_c13_CSE1_DP), &c13_thisId);
  sf_mex_destroy(&c13_b_is_active_c13_CSE1_DP);
  return c13_y;
}

static uint8_T c13_e_emlrt_marshallIn(SFc13_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  uint8_T c13_y;
  uint8_T c13_u0;
  (void)chartInstance;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_u0, 1, 3, 0U, 0, 0U, 0);
  c13_y = c13_u0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void init_dsm_address_info(SFc13_CSE1_DPInstanceStruct *chartInstance)
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

void sf_c13_CSE1_DP_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4100083572U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1549670936U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(687264034U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4185728238U);
}

mxArray *sf_c13_CSE1_DP_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("HcHb7KfjZDcI8Ssh66im5");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c13_CSE1_DP_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c13_CSE1_DP_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c13_CSE1_DP(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"F_y\",},{M[8],M[0],T\"is_active_c13_CSE1_DP\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c13_CSE1_DP_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc13_CSE1_DPInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc13_CSE1_DPInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_DPMachineNumber_,
           13,
           1,
           1,
           0,
           3,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"u_BT");
          _SFD_SET_DATA_PROPS(1,2,0,1,"F_y");
          _SFD_SET_DATA_PROPS(2,1,1,0,"nu");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,535);
        _SFD_CV_INIT_EML_IF(0,1,0,76,92,217,382);
        _SFD_CV_INIT_EML_IF(0,1,1,217,237,362,382);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T *c13_u_BT;
          real_T *c13_F_y;
          real_T (*c13_nu)[3];
          c13_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c13_F_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c13_u_BT = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c13_u_BT);
          _SFD_SET_DATA_VALUE_PTR(1U, c13_F_y);
          _SFD_SET_DATA_VALUE_PTR(2U, *c13_nu);
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
  return "TFjENdXaDE0vhjgNr3hyEF";
}

static void sf_opaque_initialize_c13_CSE1_DP(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar);
  initialize_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c13_CSE1_DP(void *chartInstanceVar)
{
  enable_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c13_CSE1_DP(void *chartInstanceVar)
{
  disable_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c13_CSE1_DP(void *chartInstanceVar)
{
  sf_gateway_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c13_CSE1_DP(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_CSE1_DP();/* state var info */
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

extern void sf_internal_set_sim_state_c13_CSE1_DP(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c13_CSE1_DP();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c13_CSE1_DP(SimStruct* S)
{
  return sf_internal_get_sim_state_c13_CSE1_DP(S);
}

static void sf_opaque_set_sim_state_c13_CSE1_DP(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c13_CSE1_DP(S, st);
}

static void sf_opaque_terminate_c13_CSE1_DP(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_DP_optimization_info();
    }

    finalize_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c13_CSE1_DP(SimStruct *S)
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
    initialize_params_c13_CSE1_DP((SFc13_CSE1_DPInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c13_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_DP_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      13);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,13,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,13,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,13);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,13,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,13,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,13);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1202996399U));
  ssSetChecksum1(S,(1922040777U));
  ssSetChecksum2(S,(2113676709U));
  ssSetChecksum3(S,(773354843U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c13_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c13_CSE1_DP(SimStruct *S)
{
  SFc13_CSE1_DPInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc13_CSE1_DPInstanceStruct *)utMalloc(sizeof
    (SFc13_CSE1_DPInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc13_CSE1_DPInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c13_CSE1_DP;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c13_CSE1_DP;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c13_CSE1_DP;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c13_CSE1_DP;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c13_CSE1_DP;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c13_CSE1_DP;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c13_CSE1_DP;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c13_CSE1_DP;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c13_CSE1_DP;
  chartInstance->chartInfo.mdlStart = mdlStart_c13_CSE1_DP;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c13_CSE1_DP;
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

void c13_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c13_CSE1_DP(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c13_CSE1_DP(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c13_CSE1_DP(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c13_CSE1_DP_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
