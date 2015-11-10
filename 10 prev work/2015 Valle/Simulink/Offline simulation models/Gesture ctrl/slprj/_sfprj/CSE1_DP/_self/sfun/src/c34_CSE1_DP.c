/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_DP_sfun.h"
#include "c34_CSE1_DP.h"
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
static const char * c34_debug_family_names[5] = { "nargin", "nargout", "w_d",
  "zeta", "y" };

/* Function Declarations */
static void initialize_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance);
static void initialize_params_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct
  *chartInstance);
static void enable_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance);
static void disable_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance);
static void c34_update_debugger_state_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct
  *chartInstance);
static void set_sim_state_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_st);
static void finalize_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance);
static void sf_gateway_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance);
static void initSimStructsc34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c34_machineNumber, uint32_T
  c34_chartNumber, uint32_T c34_instanceNumber);
static const mxArray *c34_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData);
static void c34_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_y, const char_T *c34_identifier, real_T c34_b_y[9]);
static void c34_b_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId, real_T c34_y[9]);
static void c34_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData);
static const mxArray *c34_b_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData);
static real_T c34_c_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId);
static void c34_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData);
static void c34_info_helper(const mxArray **c34_info);
static const mxArray *c34_emlrt_marshallOut(const char * c34_u);
static const mxArray *c34_b_emlrt_marshallOut(const uint32_T c34_u);
static void c34_eml_scalar_eg(SFc34_CSE1_DPInstanceStruct *chartInstance);
static void c34_eml_xgemm(SFc34_CSE1_DPInstanceStruct *chartInstance, real_T
  c34_A[9], real_T c34_B[9], real_T c34_C[9], real_T c34_b_C[9]);
static const mxArray *c34_c_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData);
static int32_T c34_d_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId);
static void c34_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData);
static uint8_T c34_e_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_b_is_active_c34_CSE1_DP, const char_T *c34_identifier);
static uint8_T c34_f_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId);
static void c34_b_eml_xgemm(SFc34_CSE1_DPInstanceStruct *chartInstance, real_T
  c34_A[9], real_T c34_B[9], real_T c34_C[9]);
static void init_dsm_address_info(SFc34_CSE1_DPInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance)
{
  chartInstance->c34_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c34_is_active_c34_CSE1_DP = 0U;
}

static void initialize_params_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c34_update_debugger_state_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct
  *chartInstance)
{
  const mxArray *c34_st;
  const mxArray *c34_y = NULL;
  int32_T c34_i0;
  real_T c34_u[9];
  const mxArray *c34_b_y = NULL;
  uint8_T c34_hoistedGlobal;
  uint8_T c34_b_u;
  const mxArray *c34_c_y = NULL;
  real_T (*c34_d_y)[9];
  c34_d_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c34_st = NULL;
  c34_st = NULL;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_createcellmatrix(2, 1), false);
  for (c34_i0 = 0; c34_i0 < 9; c34_i0++) {
    c34_u[c34_i0] = (*c34_d_y)[c34_i0];
  }

  c34_b_y = NULL;
  sf_mex_assign(&c34_b_y, sf_mex_create("y", c34_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_setcell(c34_y, 0, c34_b_y);
  c34_hoistedGlobal = chartInstance->c34_is_active_c34_CSE1_DP;
  c34_b_u = c34_hoistedGlobal;
  c34_c_y = NULL;
  sf_mex_assign(&c34_c_y, sf_mex_create("y", &c34_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c34_y, 1, c34_c_y);
  sf_mex_assign(&c34_st, c34_y, false);
  return c34_st;
}

static void set_sim_state_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_st)
{
  const mxArray *c34_u;
  real_T c34_dv0[9];
  int32_T c34_i1;
  real_T (*c34_y)[9];
  c34_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c34_doneDoubleBufferReInit = true;
  c34_u = sf_mex_dup(c34_st);
  c34_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c34_u, 0)), "y",
                       c34_dv0);
  for (c34_i1 = 0; c34_i1 < 9; c34_i1++) {
    (*c34_y)[c34_i1] = c34_dv0[c34_i1];
  }

  chartInstance->c34_is_active_c34_CSE1_DP = c34_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c34_u, 1)),
     "is_active_c34_CSE1_DP");
  sf_mex_destroy(&c34_u);
  c34_update_debugger_state_c34_CSE1_DP(chartInstance);
  sf_mex_destroy(&c34_st);
}

static void finalize_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance)
{
  int32_T c34_i2;
  int32_T c34_i3;
  real_T c34_w_d[9];
  int32_T c34_i4;
  real_T c34_zeta[9];
  uint32_T c34_debug_family_var_map[5];
  real_T c34_nargin = 2.0;
  real_T c34_nargout = 1.0;
  real_T c34_y[9];
  int32_T c34_i5;
  real_T c34_b[9];
  int32_T c34_i6;
  int32_T c34_i7;
  real_T c34_b_b[9];
  int32_T c34_i8;
  int32_T c34_i9;
  int32_T c34_i10;
  real_T c34_dv1[9];
  int32_T c34_i11;
  real_T c34_dv2[9];
  int32_T c34_i12;
  real_T c34_dv3[9];
  int32_T c34_i13;
  real_T c34_dv4[9];
  int32_T c34_i14;
  int32_T c34_i15;
  int32_T c34_i16;
  real_T (*c34_b_y)[9];
  real_T (*c34_b_zeta)[9];
  real_T (*c34_b_w_d)[9];
  c34_b_zeta = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 1);
  c34_b_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c34_b_w_d = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 31U, chartInstance->c34_sfEvent);
  for (c34_i2 = 0; c34_i2 < 9; c34_i2++) {
    _SFD_DATA_RANGE_CHECK((*c34_b_w_d)[c34_i2], 0U);
  }

  chartInstance->c34_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 31U, chartInstance->c34_sfEvent);
  for (c34_i3 = 0; c34_i3 < 9; c34_i3++) {
    c34_w_d[c34_i3] = (*c34_b_w_d)[c34_i3];
  }

  for (c34_i4 = 0; c34_i4 < 9; c34_i4++) {
    c34_zeta[c34_i4] = (*c34_b_zeta)[c34_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c34_debug_family_names,
    c34_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c34_nargin, 0U, c34_b_sf_marshallOut,
    c34_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c34_nargout, 1U, c34_b_sf_marshallOut,
    c34_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c34_w_d, 2U, c34_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c34_zeta, 3U, c34_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c34_y, 4U, c34_sf_marshallOut,
    c34_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c34_sfEvent, 4);
  for (c34_i5 = 0; c34_i5 < 9; c34_i5++) {
    c34_b[c34_i5] = c34_zeta[c34_i5];
  }

  for (c34_i6 = 0; c34_i6 < 9; c34_i6++) {
    c34_b[c34_i6] *= 2.0;
  }

  for (c34_i7 = 0; c34_i7 < 9; c34_i7++) {
    c34_b_b[c34_i7] = c34_w_d[c34_i7];
  }

  c34_eml_scalar_eg(chartInstance);
  c34_eml_scalar_eg(chartInstance);
  for (c34_i8 = 0; c34_i8 < 9; c34_i8++) {
    c34_y[c34_i8] = 0.0;
  }

  for (c34_i9 = 0; c34_i9 < 9; c34_i9++) {
    c34_y[c34_i9] = 0.0;
  }

  for (c34_i10 = 0; c34_i10 < 9; c34_i10++) {
    c34_dv1[c34_i10] = c34_b[c34_i10];
  }

  for (c34_i11 = 0; c34_i11 < 9; c34_i11++) {
    c34_dv2[c34_i11] = c34_b_b[c34_i11];
  }

  for (c34_i12 = 0; c34_i12 < 9; c34_i12++) {
    c34_dv3[c34_i12] = c34_dv1[c34_i12];
  }

  for (c34_i13 = 0; c34_i13 < 9; c34_i13++) {
    c34_dv4[c34_i13] = c34_dv2[c34_i13];
  }

  c34_b_eml_xgemm(chartInstance, c34_dv3, c34_dv4, c34_y);
  _SFD_EML_CALL(0U, chartInstance->c34_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c34_i14 = 0; c34_i14 < 9; c34_i14++) {
    (*c34_b_y)[c34_i14] = c34_y[c34_i14];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 31U, chartInstance->c34_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_DPMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c34_i15 = 0; c34_i15 < 9; c34_i15++) {
    _SFD_DATA_RANGE_CHECK((*c34_b_y)[c34_i15], 1U);
  }

  for (c34_i16 = 0; c34_i16 < 9; c34_i16++) {
    _SFD_DATA_RANGE_CHECK((*c34_b_zeta)[c34_i16], 2U);
  }
}

static void initSimStructsc34_CSE1_DP(SFc34_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c34_machineNumber, uint32_T
  c34_chartNumber, uint32_T c34_instanceNumber)
{
  (void)c34_machineNumber;
  (void)c34_chartNumber;
  (void)c34_instanceNumber;
}

static const mxArray *c34_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData)
{
  const mxArray *c34_mxArrayOutData = NULL;
  int32_T c34_i17;
  int32_T c34_i18;
  int32_T c34_i19;
  real_T c34_b_inData[9];
  int32_T c34_i20;
  int32_T c34_i21;
  int32_T c34_i22;
  real_T c34_u[9];
  const mxArray *c34_y = NULL;
  SFc34_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc34_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c34_mxArrayOutData = NULL;
  c34_i17 = 0;
  for (c34_i18 = 0; c34_i18 < 3; c34_i18++) {
    for (c34_i19 = 0; c34_i19 < 3; c34_i19++) {
      c34_b_inData[c34_i19 + c34_i17] = (*(real_T (*)[9])c34_inData)[c34_i19 +
        c34_i17];
    }

    c34_i17 += 3;
  }

  c34_i20 = 0;
  for (c34_i21 = 0; c34_i21 < 3; c34_i21++) {
    for (c34_i22 = 0; c34_i22 < 3; c34_i22++) {
      c34_u[c34_i22 + c34_i20] = c34_b_inData[c34_i22 + c34_i20];
    }

    c34_i20 += 3;
  }

  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", c34_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c34_mxArrayOutData, c34_y, false);
  return c34_mxArrayOutData;
}

static void c34_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_y, const char_T *c34_identifier, real_T c34_b_y[9])
{
  emlrtMsgIdentifier c34_thisId;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c34_y), &c34_thisId, c34_b_y);
  sf_mex_destroy(&c34_y);
}

static void c34_b_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId, real_T c34_y[9])
{
  real_T c34_dv5[9];
  int32_T c34_i23;
  (void)chartInstance;
  sf_mex_import(c34_parentId, sf_mex_dup(c34_u), c34_dv5, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c34_i23 = 0; c34_i23 < 9; c34_i23++) {
    c34_y[c34_i23] = c34_dv5[c34_i23];
  }

  sf_mex_destroy(&c34_u);
}

static void c34_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData)
{
  const mxArray *c34_y;
  const char_T *c34_identifier;
  emlrtMsgIdentifier c34_thisId;
  real_T c34_b_y[9];
  int32_T c34_i24;
  int32_T c34_i25;
  int32_T c34_i26;
  SFc34_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc34_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c34_y = sf_mex_dup(c34_mxArrayInData);
  c34_identifier = c34_varName;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c34_y), &c34_thisId, c34_b_y);
  sf_mex_destroy(&c34_y);
  c34_i24 = 0;
  for (c34_i25 = 0; c34_i25 < 3; c34_i25++) {
    for (c34_i26 = 0; c34_i26 < 3; c34_i26++) {
      (*(real_T (*)[9])c34_outData)[c34_i26 + c34_i24] = c34_b_y[c34_i26 +
        c34_i24];
    }

    c34_i24 += 3;
  }

  sf_mex_destroy(&c34_mxArrayInData);
}

static const mxArray *c34_b_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData)
{
  const mxArray *c34_mxArrayOutData = NULL;
  real_T c34_u;
  const mxArray *c34_y = NULL;
  SFc34_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc34_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c34_mxArrayOutData = NULL;
  c34_u = *(real_T *)c34_inData;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", &c34_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c34_mxArrayOutData, c34_y, false);
  return c34_mxArrayOutData;
}

static real_T c34_c_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId)
{
  real_T c34_y;
  real_T c34_d0;
  (void)chartInstance;
  sf_mex_import(c34_parentId, sf_mex_dup(c34_u), &c34_d0, 1, 0, 0U, 0, 0U, 0);
  c34_y = c34_d0;
  sf_mex_destroy(&c34_u);
  return c34_y;
}

static void c34_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData)
{
  const mxArray *c34_nargout;
  const char_T *c34_identifier;
  emlrtMsgIdentifier c34_thisId;
  real_T c34_y;
  SFc34_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc34_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c34_nargout = sf_mex_dup(c34_mxArrayInData);
  c34_identifier = c34_varName;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_y = c34_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c34_nargout),
    &c34_thisId);
  sf_mex_destroy(&c34_nargout);
  *(real_T *)c34_outData = c34_y;
  sf_mex_destroy(&c34_mxArrayInData);
}

const mxArray *sf_c34_CSE1_DP_get_eml_resolved_functions_info(void)
{
  const mxArray *c34_nameCaptureInfo = NULL;
  c34_nameCaptureInfo = NULL;
  sf_mex_assign(&c34_nameCaptureInfo, sf_mex_createstruct("structure", 2, 13, 1),
                false);
  c34_info_helper(&c34_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c34_nameCaptureInfo);
  return c34_nameCaptureInfo;
}

static void c34_info_helper(const mxArray **c34_info)
{
  const mxArray *c34_rhs0 = NULL;
  const mxArray *c34_lhs0 = NULL;
  const mxArray *c34_rhs1 = NULL;
  const mxArray *c34_lhs1 = NULL;
  const mxArray *c34_rhs2 = NULL;
  const mxArray *c34_lhs2 = NULL;
  const mxArray *c34_rhs3 = NULL;
  const mxArray *c34_lhs3 = NULL;
  const mxArray *c34_rhs4 = NULL;
  const mxArray *c34_lhs4 = NULL;
  const mxArray *c34_rhs5 = NULL;
  const mxArray *c34_lhs5 = NULL;
  const mxArray *c34_rhs6 = NULL;
  const mxArray *c34_lhs6 = NULL;
  const mxArray *c34_rhs7 = NULL;
  const mxArray *c34_lhs7 = NULL;
  const mxArray *c34_rhs8 = NULL;
  const mxArray *c34_lhs8 = NULL;
  const mxArray *c34_rhs9 = NULL;
  const mxArray *c34_lhs9 = NULL;
  const mxArray *c34_rhs10 = NULL;
  const mxArray *c34_lhs10 = NULL;
  const mxArray *c34_rhs11 = NULL;
  const mxArray *c34_lhs11 = NULL;
  const mxArray *c34_rhs12 = NULL;
  const mxArray *c34_lhs12 = NULL;
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c34_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c34_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 2);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c34_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c34_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c34_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  5);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c34_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 6);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c34_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 7);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c34_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 8);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 8);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c34_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 9);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "coder.internal.blas.threshold"), "name", "name", 9);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c34_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 10);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 10);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c34_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 11);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c34_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "coder.internal.refblas.xgemm"), "name", "name", 12);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c34_info, c34_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c34_info, c34_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c34_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c34_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c34_info, sf_mex_duplicatearraysafe(&c34_lhs12), "lhs", "lhs",
                  12);
  sf_mex_destroy(&c34_rhs0);
  sf_mex_destroy(&c34_lhs0);
  sf_mex_destroy(&c34_rhs1);
  sf_mex_destroy(&c34_lhs1);
  sf_mex_destroy(&c34_rhs2);
  sf_mex_destroy(&c34_lhs2);
  sf_mex_destroy(&c34_rhs3);
  sf_mex_destroy(&c34_lhs3);
  sf_mex_destroy(&c34_rhs4);
  sf_mex_destroy(&c34_lhs4);
  sf_mex_destroy(&c34_rhs5);
  sf_mex_destroy(&c34_lhs5);
  sf_mex_destroy(&c34_rhs6);
  sf_mex_destroy(&c34_lhs6);
  sf_mex_destroy(&c34_rhs7);
  sf_mex_destroy(&c34_lhs7);
  sf_mex_destroy(&c34_rhs8);
  sf_mex_destroy(&c34_lhs8);
  sf_mex_destroy(&c34_rhs9);
  sf_mex_destroy(&c34_lhs9);
  sf_mex_destroy(&c34_rhs10);
  sf_mex_destroy(&c34_lhs10);
  sf_mex_destroy(&c34_rhs11);
  sf_mex_destroy(&c34_lhs11);
  sf_mex_destroy(&c34_rhs12);
  sf_mex_destroy(&c34_lhs12);
}

static const mxArray *c34_emlrt_marshallOut(const char * c34_u)
{
  const mxArray *c34_y = NULL;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", c34_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c34_u)), false);
  return c34_y;
}

static const mxArray *c34_b_emlrt_marshallOut(const uint32_T c34_u)
{
  const mxArray *c34_y = NULL;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", &c34_u, 7, 0U, 0U, 0U, 0), false);
  return c34_y;
}

static void c34_eml_scalar_eg(SFc34_CSE1_DPInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c34_eml_xgemm(SFc34_CSE1_DPInstanceStruct *chartInstance, real_T
  c34_A[9], real_T c34_B[9], real_T c34_C[9], real_T c34_b_C[9])
{
  int32_T c34_i27;
  int32_T c34_i28;
  real_T c34_b_A[9];
  int32_T c34_i29;
  real_T c34_b_B[9];
  for (c34_i27 = 0; c34_i27 < 9; c34_i27++) {
    c34_b_C[c34_i27] = c34_C[c34_i27];
  }

  for (c34_i28 = 0; c34_i28 < 9; c34_i28++) {
    c34_b_A[c34_i28] = c34_A[c34_i28];
  }

  for (c34_i29 = 0; c34_i29 < 9; c34_i29++) {
    c34_b_B[c34_i29] = c34_B[c34_i29];
  }

  c34_b_eml_xgemm(chartInstance, c34_b_A, c34_b_B, c34_b_C);
}

static const mxArray *c34_c_sf_marshallOut(void *chartInstanceVoid, void
  *c34_inData)
{
  const mxArray *c34_mxArrayOutData = NULL;
  int32_T c34_u;
  const mxArray *c34_y = NULL;
  SFc34_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc34_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c34_mxArrayOutData = NULL;
  c34_u = *(int32_T *)c34_inData;
  c34_y = NULL;
  sf_mex_assign(&c34_y, sf_mex_create("y", &c34_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c34_mxArrayOutData, c34_y, false);
  return c34_mxArrayOutData;
}

static int32_T c34_d_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId)
{
  int32_T c34_y;
  int32_T c34_i30;
  (void)chartInstance;
  sf_mex_import(c34_parentId, sf_mex_dup(c34_u), &c34_i30, 1, 6, 0U, 0, 0U, 0);
  c34_y = c34_i30;
  sf_mex_destroy(&c34_u);
  return c34_y;
}

static void c34_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c34_mxArrayInData, const char_T *c34_varName, void *c34_outData)
{
  const mxArray *c34_b_sfEvent;
  const char_T *c34_identifier;
  emlrtMsgIdentifier c34_thisId;
  int32_T c34_y;
  SFc34_CSE1_DPInstanceStruct *chartInstance;
  chartInstance = (SFc34_CSE1_DPInstanceStruct *)chartInstanceVoid;
  c34_b_sfEvent = sf_mex_dup(c34_mxArrayInData);
  c34_identifier = c34_varName;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_y = c34_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c34_b_sfEvent),
    &c34_thisId);
  sf_mex_destroy(&c34_b_sfEvent);
  *(int32_T *)c34_outData = c34_y;
  sf_mex_destroy(&c34_mxArrayInData);
}

static uint8_T c34_e_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_b_is_active_c34_CSE1_DP, const char_T *c34_identifier)
{
  uint8_T c34_y;
  emlrtMsgIdentifier c34_thisId;
  c34_thisId.fIdentifier = c34_identifier;
  c34_thisId.fParent = NULL;
  c34_y = c34_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c34_b_is_active_c34_CSE1_DP), &c34_thisId);
  sf_mex_destroy(&c34_b_is_active_c34_CSE1_DP);
  return c34_y;
}

static uint8_T c34_f_emlrt_marshallIn(SFc34_CSE1_DPInstanceStruct *chartInstance,
  const mxArray *c34_u, const emlrtMsgIdentifier *c34_parentId)
{
  uint8_T c34_y;
  uint8_T c34_u0;
  (void)chartInstance;
  sf_mex_import(c34_parentId, sf_mex_dup(c34_u), &c34_u0, 1, 3, 0U, 0, 0U, 0);
  c34_y = c34_u0;
  sf_mex_destroy(&c34_u);
  return c34_y;
}

static void c34_b_eml_xgemm(SFc34_CSE1_DPInstanceStruct *chartInstance, real_T
  c34_A[9], real_T c34_B[9], real_T c34_C[9])
{
  int32_T c34_i31;
  int32_T c34_i32;
  int32_T c34_i33;
  int32_T c34_i34;
  int32_T c34_i35;
  (void)chartInstance;
  for (c34_i31 = 0; c34_i31 < 3; c34_i31++) {
    c34_i32 = 0;
    for (c34_i33 = 0; c34_i33 < 3; c34_i33++) {
      c34_C[c34_i32 + c34_i31] = 0.0;
      c34_i34 = 0;
      for (c34_i35 = 0; c34_i35 < 3; c34_i35++) {
        c34_C[c34_i32 + c34_i31] += c34_A[c34_i34 + c34_i31] * c34_B[c34_i35 +
          c34_i32];
        c34_i34 += 3;
      }

      c34_i32 += 3;
    }
  }
}

static void init_dsm_address_info(SFc34_CSE1_DPInstanceStruct *chartInstance)
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

void sf_c34_CSE1_DP_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4181106280U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2839422147U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2246211203U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4079734539U);
}

mxArray *sf_c34_CSE1_DP_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("mWs5kliPZZH7xQhqp3i5S");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c34_CSE1_DP_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c34_CSE1_DP_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c34_CSE1_DP(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c34_CSE1_DP\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c34_CSE1_DP_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc34_CSE1_DPInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc34_CSE1_DPInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_DPMachineNumber_,
           34,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"w_d");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
          _SFD_SET_DATA_PROPS(2,1,1,0,"zeta");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,53);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c34_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c34_sf_marshallOut,(MexInFcnForType)
            c34_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c34_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c34_w_d)[9];
          real_T (*c34_y)[9];
          real_T (*c34_zeta)[9];
          c34_zeta = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 1);
          c34_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          c34_w_d = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c34_w_d);
          _SFD_SET_DATA_VALUE_PTR(1U, *c34_y);
          _SFD_SET_DATA_VALUE_PTR(2U, *c34_zeta);
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
  return "MVO7e61n4UuIHiCH5iTcfB";
}

static void sf_opaque_initialize_c34_CSE1_DP(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar);
  initialize_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c34_CSE1_DP(void *chartInstanceVar)
{
  enable_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c34_CSE1_DP(void *chartInstanceVar)
{
  disable_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c34_CSE1_DP(void *chartInstanceVar)
{
  sf_gateway_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c34_CSE1_DP(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c34_CSE1_DP();/* state var info */
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

extern void sf_internal_set_sim_state_c34_CSE1_DP(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c34_CSE1_DP();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c34_CSE1_DP(SimStruct* S)
{
  return sf_internal_get_sim_state_c34_CSE1_DP(S);
}

static void sf_opaque_set_sim_state_c34_CSE1_DP(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c34_CSE1_DP(S, st);
}

static void sf_opaque_terminate_c34_CSE1_DP(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_DP_optimization_info();
    }

    finalize_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c34_CSE1_DP(SimStruct *S)
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
    initialize_params_c34_CSE1_DP((SFc34_CSE1_DPInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c34_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_DP_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      34);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,34,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,34,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,34);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,34,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,34,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,34);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3420843120U));
  ssSetChecksum1(S,(3401841517U));
  ssSetChecksum2(S,(2981406174U));
  ssSetChecksum3(S,(1676955676U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c34_CSE1_DP(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c34_CSE1_DP(SimStruct *S)
{
  SFc34_CSE1_DPInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc34_CSE1_DPInstanceStruct *)utMalloc(sizeof
    (SFc34_CSE1_DPInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc34_CSE1_DPInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c34_CSE1_DP;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c34_CSE1_DP;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c34_CSE1_DP;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c34_CSE1_DP;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c34_CSE1_DP;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c34_CSE1_DP;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c34_CSE1_DP;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c34_CSE1_DP;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c34_CSE1_DP;
  chartInstance->chartInfo.mdlStart = mdlStart_c34_CSE1_DP;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c34_CSE1_DP;
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

void c34_CSE1_DP_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c34_CSE1_DP(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c34_CSE1_DP(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c34_CSE1_DP(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c34_CSE1_DP_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
