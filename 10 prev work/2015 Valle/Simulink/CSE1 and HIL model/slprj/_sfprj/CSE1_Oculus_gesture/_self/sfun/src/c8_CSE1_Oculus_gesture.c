/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_Oculus_gesture_sfun.h"
#include "c8_CSE1_Oculus_gesture.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "CSE1_Oculus_gesture_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c8_debug_family_names[5] = { "nargin", "nargout", "w_d",
  "zeta", "y" };

/* Function Declarations */
static void initialize_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void initialize_params_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void enable_c8_CSE1_Oculus_gesture(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance);
static void disable_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void c8_update_debugger_state_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void set_sim_state_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance, const mxArray *c8_st);
static void finalize_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void sf_gateway_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void initSimStructsc8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber, uint32_T c8_instanceNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static void c8_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_y, const char_T *c8_identifier, real_T
  c8_b_y[9]);
static void c8_b_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[9]);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_c_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void c8_info_helper(const mxArray **c8_info);
static const mxArray *c8_emlrt_marshallOut(const char * c8_u);
static const mxArray *c8_b_emlrt_marshallOut(const uint32_T c8_u);
static void c8_eml_scalar_eg(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance);
static void c8_eml_xgemm(SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance,
  real_T c8_A[9], real_T c8_B[9], real_T c8_C[9], real_T c8_b_C[9]);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_d_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_e_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_CSE1_Oculus_gesture, const
  char_T *c8_identifier);
static uint8_T c8_f_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_eml_xgemm(SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance,
  real_T c8_A[9], real_T c8_B[9], real_T c8_C[9]);
static void init_dsm_address_info(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c8_is_active_c8_CSE1_Oculus_gesture = 0U;
}

static void initialize_params_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c8_CSE1_Oculus_gesture(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c8_update_debugger_state_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  int32_T c8_i0;
  real_T c8_u[9];
  const mxArray *c8_b_y = NULL;
  uint8_T c8_hoistedGlobal;
  uint8_T c8_b_u;
  const mxArray *c8_c_y = NULL;
  real_T (*c8_d_y)[9];
  c8_d_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellmatrix(2, 1), false);
  for (c8_i0 = 0; c8_i0 < 9; c8_i0++) {
    c8_u[c8_i0] = (*c8_d_y)[c8_i0];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_hoistedGlobal = chartInstance->c8_is_active_c8_CSE1_Oculus_gesture;
  c8_b_u = c8_hoistedGlobal;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  sf_mex_assign(&c8_st, c8_y, false);
  return c8_st;
}

static void set_sim_state_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance, const mxArray *c8_st)
{
  const mxArray *c8_u;
  real_T c8_dv0[9];
  int32_T c8_i1;
  real_T (*c8_y)[9];
  c8_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = true;
  c8_u = sf_mex_dup(c8_st);
  c8_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 0)), "y",
                      c8_dv0);
  for (c8_i1 = 0; c8_i1 < 9; c8_i1++) {
    (*c8_y)[c8_i1] = c8_dv0[c8_i1];
  }

  chartInstance->c8_is_active_c8_CSE1_Oculus_gesture = c8_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 1)),
     "is_active_c8_CSE1_Oculus_gesture");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_CSE1_Oculus_gesture(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  int32_T c8_i2;
  int32_T c8_i3;
  real_T c8_w_d[9];
  int32_T c8_i4;
  real_T c8_zeta[9];
  uint32_T c8_debug_family_var_map[5];
  real_T c8_nargin = 2.0;
  real_T c8_nargout = 1.0;
  real_T c8_y[9];
  int32_T c8_i5;
  real_T c8_b[9];
  int32_T c8_i6;
  int32_T c8_i7;
  real_T c8_b_b[9];
  int32_T c8_i8;
  int32_T c8_i9;
  int32_T c8_i10;
  real_T c8_dv1[9];
  int32_T c8_i11;
  real_T c8_dv2[9];
  int32_T c8_i12;
  real_T c8_dv3[9];
  int32_T c8_i13;
  real_T c8_dv4[9];
  int32_T c8_i14;
  int32_T c8_i15;
  int32_T c8_i16;
  real_T (*c8_b_y)[9];
  real_T (*c8_b_zeta)[9];
  real_T (*c8_b_w_d)[9];
  c8_b_zeta = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_b_w_d = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  for (c8_i2 = 0; c8_i2 < 9; c8_i2++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_w_d)[c8_i2], 0U);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  for (c8_i3 = 0; c8_i3 < 9; c8_i3++) {
    c8_w_d[c8_i3] = (*c8_b_w_d)[c8_i3];
  }

  for (c8_i4 = 0; c8_i4 < 9; c8_i4++) {
    c8_zeta[c8_i4] = (*c8_b_zeta)[c8_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 0U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 1U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_w_d, 2U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_zeta, 3U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_y, 4U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 4);
  for (c8_i5 = 0; c8_i5 < 9; c8_i5++) {
    c8_b[c8_i5] = c8_zeta[c8_i5];
  }

  for (c8_i6 = 0; c8_i6 < 9; c8_i6++) {
    c8_b[c8_i6] *= 2.0;
  }

  for (c8_i7 = 0; c8_i7 < 9; c8_i7++) {
    c8_b_b[c8_i7] = c8_w_d[c8_i7];
  }

  c8_eml_scalar_eg(chartInstance);
  c8_eml_scalar_eg(chartInstance);
  for (c8_i8 = 0; c8_i8 < 9; c8_i8++) {
    c8_y[c8_i8] = 0.0;
  }

  for (c8_i9 = 0; c8_i9 < 9; c8_i9++) {
    c8_y[c8_i9] = 0.0;
  }

  for (c8_i10 = 0; c8_i10 < 9; c8_i10++) {
    c8_dv1[c8_i10] = c8_b[c8_i10];
  }

  for (c8_i11 = 0; c8_i11 < 9; c8_i11++) {
    c8_dv2[c8_i11] = c8_b_b[c8_i11];
  }

  for (c8_i12 = 0; c8_i12 < 9; c8_i12++) {
    c8_dv3[c8_i12] = c8_dv1[c8_i12];
  }

  for (c8_i13 = 0; c8_i13 < 9; c8_i13++) {
    c8_dv4[c8_i13] = c8_dv2[c8_i13];
  }

  c8_b_eml_xgemm(chartInstance, c8_dv3, c8_dv4, c8_y);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c8_i14 = 0; c8_i14 < 9; c8_i14++) {
    (*c8_b_y)[c8_i14] = c8_y[c8_i14];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_Oculus_gestureMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c8_i15 = 0; c8_i15 < 9; c8_i15++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_y)[c8_i15], 1U);
  }

  for (c8_i16 = 0; c8_i16 < 9; c8_i16++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_zeta)[c8_i16], 2U);
  }
}

static void initSimStructsc8_CSE1_Oculus_gesture
  (SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber, uint32_T c8_instanceNumber)
{
  (void)c8_machineNumber;
  (void)c8_chartNumber;
  (void)c8_instanceNumber;
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i17;
  int32_T c8_i18;
  int32_T c8_i19;
  real_T c8_b_inData[9];
  int32_T c8_i20;
  int32_T c8_i21;
  int32_T c8_i22;
  real_T c8_u[9];
  const mxArray *c8_y = NULL;
  SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc8_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i17 = 0;
  for (c8_i18 = 0; c8_i18 < 3; c8_i18++) {
    for (c8_i19 = 0; c8_i19 < 3; c8_i19++) {
      c8_b_inData[c8_i19 + c8_i17] = (*(real_T (*)[9])c8_inData)[c8_i19 + c8_i17];
    }

    c8_i17 += 3;
  }

  c8_i20 = 0;
  for (c8_i21 = 0; c8_i21 < 3; c8_i21++) {
    for (c8_i22 = 0; c8_i22 < 3; c8_i22++) {
      c8_u[c8_i22 + c8_i20] = c8_b_inData[c8_i22 + c8_i20];
    }

    c8_i20 += 3;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static void c8_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_y, const char_T *c8_identifier, real_T
  c8_b_y[9])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_y), &c8_thisId, c8_b_y);
  sf_mex_destroy(&c8_y);
}

static void c8_b_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[9])
{
  real_T c8_dv5[9];
  int32_T c8_i23;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv5, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c8_i23 = 0; c8_i23 < 9; c8_i23++) {
    c8_y[c8_i23] = c8_dv5[c8_i23];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_y;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_b_y[9];
  int32_T c8_i24;
  int32_T c8_i25;
  int32_T c8_i26;
  SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc8_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c8_y = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_y), &c8_thisId, c8_b_y);
  sf_mex_destroy(&c8_y);
  c8_i24 = 0;
  for (c8_i25 = 0; c8_i25 < 3; c8_i25++) {
    for (c8_i26 = 0; c8_i26 < 3; c8_i26++) {
      (*(real_T (*)[9])c8_outData)[c8_i26 + c8_i24] = c8_b_y[c8_i26 + c8_i24];
    }

    c8_i24 += 3;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc8_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static real_T c8_c_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_nargout;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc8_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c8_nargout = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_nargout), &c8_thisId);
  sf_mex_destroy(&c8_nargout);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

const mxArray *sf_c8_CSE1_Oculus_gesture_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  sf_mex_assign(&c8_nameCaptureInfo, sf_mex_createstruct("structure", 2, 13, 1),
                false);
  c8_info_helper(&c8_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c8_nameCaptureInfo);
  return c8_nameCaptureInfo;
}

static void c8_info_helper(const mxArray **c8_info)
{
  const mxArray *c8_rhs0 = NULL;
  const mxArray *c8_lhs0 = NULL;
  const mxArray *c8_rhs1 = NULL;
  const mxArray *c8_lhs1 = NULL;
  const mxArray *c8_rhs2 = NULL;
  const mxArray *c8_lhs2 = NULL;
  const mxArray *c8_rhs3 = NULL;
  const mxArray *c8_lhs3 = NULL;
  const mxArray *c8_rhs4 = NULL;
  const mxArray *c8_lhs4 = NULL;
  const mxArray *c8_rhs5 = NULL;
  const mxArray *c8_lhs5 = NULL;
  const mxArray *c8_rhs6 = NULL;
  const mxArray *c8_lhs6 = NULL;
  const mxArray *c8_rhs7 = NULL;
  const mxArray *c8_lhs7 = NULL;
  const mxArray *c8_rhs8 = NULL;
  const mxArray *c8_lhs8 = NULL;
  const mxArray *c8_rhs9 = NULL;
  const mxArray *c8_lhs9 = NULL;
  const mxArray *c8_rhs10 = NULL;
  const mxArray *c8_lhs10 = NULL;
  const mxArray *c8_rhs11 = NULL;
  const mxArray *c8_lhs11 = NULL;
  const mxArray *c8_rhs12 = NULL;
  const mxArray *c8_lhs12 = NULL;
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c8_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c8_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 2);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c8_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c8_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c8_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_xgemm"), "name", "name", 5);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c8_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 6);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c8_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 7);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c8_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 8);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 8);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c8_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 9);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 9);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c8_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 10);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 10);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c8_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 11);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c8_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 12);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c8_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs12), "lhs", "lhs",
                  12);
  sf_mex_destroy(&c8_rhs0);
  sf_mex_destroy(&c8_lhs0);
  sf_mex_destroy(&c8_rhs1);
  sf_mex_destroy(&c8_lhs1);
  sf_mex_destroy(&c8_rhs2);
  sf_mex_destroy(&c8_lhs2);
  sf_mex_destroy(&c8_rhs3);
  sf_mex_destroy(&c8_lhs3);
  sf_mex_destroy(&c8_rhs4);
  sf_mex_destroy(&c8_lhs4);
  sf_mex_destroy(&c8_rhs5);
  sf_mex_destroy(&c8_lhs5);
  sf_mex_destroy(&c8_rhs6);
  sf_mex_destroy(&c8_lhs6);
  sf_mex_destroy(&c8_rhs7);
  sf_mex_destroy(&c8_lhs7);
  sf_mex_destroy(&c8_rhs8);
  sf_mex_destroy(&c8_lhs8);
  sf_mex_destroy(&c8_rhs9);
  sf_mex_destroy(&c8_lhs9);
  sf_mex_destroy(&c8_rhs10);
  sf_mex_destroy(&c8_lhs10);
  sf_mex_destroy(&c8_rhs11);
  sf_mex_destroy(&c8_lhs11);
  sf_mex_destroy(&c8_rhs12);
  sf_mex_destroy(&c8_lhs12);
}

static const mxArray *c8_emlrt_marshallOut(const char * c8_u)
{
  const mxArray *c8_y = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c8_u)), false);
  return c8_y;
}

static const mxArray *c8_b_emlrt_marshallOut(const uint32_T c8_u)
{
  const mxArray *c8_y = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 7, 0U, 0U, 0U, 0), false);
  return c8_y;
}

static void c8_eml_scalar_eg(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c8_eml_xgemm(SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance,
  real_T c8_A[9], real_T c8_B[9], real_T c8_C[9], real_T c8_b_C[9])
{
  int32_T c8_i27;
  int32_T c8_i28;
  real_T c8_b_A[9];
  int32_T c8_i29;
  real_T c8_b_B[9];
  for (c8_i27 = 0; c8_i27 < 9; c8_i27++) {
    c8_b_C[c8_i27] = c8_C[c8_i27];
  }

  for (c8_i28 = 0; c8_i28 < 9; c8_i28++) {
    c8_b_A[c8_i28] = c8_A[c8_i28];
  }

  for (c8_i29 = 0; c8_i29 < 9; c8_i29++) {
    c8_b_B[c8_i29] = c8_B[c8_i29];
  }

  c8_b_eml_xgemm(chartInstance, c8_b_A, c8_b_B, c8_b_C);
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc8_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static int32_T c8_d_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i30;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i30, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i30;
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
  SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc8_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static uint8_T c8_e_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_CSE1_Oculus_gesture, const
  char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_CSE1_Oculus_gesture), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_CSE1_Oculus_gesture);
  return c8_y;
}

static uint8_T c8_f_emlrt_marshallIn(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_eml_xgemm(SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance,
  real_T c8_A[9], real_T c8_B[9], real_T c8_C[9])
{
  int32_T c8_i31;
  int32_T c8_i32;
  int32_T c8_i33;
  int32_T c8_i34;
  int32_T c8_i35;
  (void)chartInstance;
  for (c8_i31 = 0; c8_i31 < 3; c8_i31++) {
    c8_i32 = 0;
    for (c8_i33 = 0; c8_i33 < 3; c8_i33++) {
      c8_C[c8_i32 + c8_i31] = 0.0;
      c8_i34 = 0;
      for (c8_i35 = 0; c8_i35 < 3; c8_i35++) {
        c8_C[c8_i32 + c8_i31] += c8_A[c8_i34 + c8_i31] * c8_B[c8_i35 + c8_i32];
        c8_i34 += 3;
      }

      c8_i32 += 3;
    }
  }
}

static void init_dsm_address_info(SFc8_CSE1_Oculus_gestureInstanceStruct
  *chartInstance)
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

void sf_c8_CSE1_Oculus_gesture_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4181106280U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2839422147U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2246211203U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4079734539U);
}

mxArray *sf_c8_CSE1_Oculus_gesture_get_autoinheritance_info(void)
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

mxArray *sf_c8_CSE1_Oculus_gesture_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c8_CSE1_Oculus_gesture_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c8_CSE1_Oculus_gesture(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c8_CSE1_Oculus_gesture\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_CSE1_Oculus_gesture_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc8_CSE1_Oculus_gestureInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_Oculus_gestureMachineNumber_,
           8,
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
        init_script_number_translation(_CSE1_Oculus_gestureMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_CSE1_Oculus_gestureMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _CSE1_Oculus_gestureMachineNumber_,
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
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c8_w_d)[9];
          real_T (*c8_y)[9];
          real_T (*c8_zeta)[9];
          c8_zeta = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 1);
          c8_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          c8_w_d = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c8_w_d);
          _SFD_SET_DATA_VALUE_PTR(1U, *c8_y);
          _SFD_SET_DATA_VALUE_PTR(2U, *c8_zeta);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _CSE1_Oculus_gestureMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "MVO7e61n4UuIHiCH5iTcfB";
}

static void sf_opaque_initialize_c8_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c8_CSE1_Oculus_gesture
    ((SFc8_CSE1_Oculus_gestureInstanceStruct*) chartInstanceVar);
  initialize_c8_CSE1_Oculus_gesture((SFc8_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c8_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  enable_c8_CSE1_Oculus_gesture((SFc8_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c8_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  disable_c8_CSE1_Oculus_gesture((SFc8_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c8_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  sf_gateway_c8_CSE1_Oculus_gesture((SFc8_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_CSE1_Oculus_gesture(SimStruct*
  S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_CSE1_Oculus_gesture
    ((SFc8_CSE1_Oculus_gestureInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_CSE1_Oculus_gesture();/* state var info */
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

extern void sf_internal_set_sim_state_c8_CSE1_Oculus_gesture(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c8_CSE1_Oculus_gesture();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_CSE1_Oculus_gesture((SFc8_CSE1_Oculus_gestureInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_CSE1_Oculus_gesture(SimStruct*
  S)
{
  return sf_internal_get_sim_state_c8_CSE1_Oculus_gesture(S);
}

static void sf_opaque_set_sim_state_c8_CSE1_Oculus_gesture(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c8_CSE1_Oculus_gesture(S, st);
}

static void sf_opaque_terminate_c8_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_CSE1_Oculus_gestureInstanceStruct*) chartInstanceVar
      )->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_Oculus_gesture_optimization_info();
    }

    finalize_c8_CSE1_Oculus_gesture((SFc8_CSE1_Oculus_gestureInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_CSE1_Oculus_gesture((SFc8_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_CSE1_Oculus_gesture(SimStruct *S)
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
    initialize_params_c8_CSE1_Oculus_gesture
      ((SFc8_CSE1_Oculus_gestureInstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_CSE1_Oculus_gesture(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_Oculus_gesture_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,8,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,8,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,8);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
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

static void mdlRTW_c8_CSE1_Oculus_gesture(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_CSE1_Oculus_gesture(SimStruct *S)
{
  SFc8_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc8_CSE1_Oculus_gestureInstanceStruct *)utMalloc(sizeof
    (SFc8_CSE1_Oculus_gestureInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc8_CSE1_Oculus_gestureInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_CSE1_Oculus_gesture;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_CSE1_Oculus_gesture;
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

void c8_CSE1_Oculus_gesture_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_CSE1_Oculus_gesture(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_CSE1_Oculus_gesture(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_CSE1_Oculus_gesture(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_CSE1_Oculus_gesture_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
