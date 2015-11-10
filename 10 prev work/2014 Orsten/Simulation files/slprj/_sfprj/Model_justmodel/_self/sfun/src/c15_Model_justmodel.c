/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Model_justmodel_sfun.h"
#include "c15_Model_justmodel.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Model_justmodel_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c15_debug_family_names[7] = { "nargin", "nargout", "eta_s",
  "eta_s_obs", "QS_error", "eta_s_use", "eta_s_err" };

/* Function Declarations */
static void initialize_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance);
static void initialize_params_c15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance);
static void enable_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance);
static void disable_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance);
static void c15_update_debugger_state_c15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance);
static void set_sim_state_c15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance, const mxArray *c15_st);
static void finalize_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance);
static void sf_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance);
static void initSimStructsc15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance);
static void registerMessagesc15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c15_machineNumber, uint32_T
  c15_chartNumber);
static const mxArray *c15_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData);
static void c15_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_eta_s_err, const char_T *c15_identifier,
  real_T c15_y[3]);
static void c15_b_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId,
  real_T c15_y[3]);
static void c15_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData);
static const mxArray *c15_b_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData);
static real_T c15_c_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId);
static void c15_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData);
static const mxArray *c15_c_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData);
static int32_T c15_d_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId);
static void c15_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData);
static uint8_T c15_e_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_b_is_active_c15_Model_justmodel, const
  char_T *c15_identifier);
static uint8_T c15_f_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId);
static void init_dsm_address_info(SFc15_Model_justmodelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance)
{
  chartInstance->c15_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c15_is_active_c15_Model_justmodel = 0U;
}

static void initialize_params_c15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance)
{
}

static void enable_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c15_update_debugger_state_c15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance)
{
  const mxArray *c15_st;
  const mxArray *c15_y = NULL;
  int32_T c15_i0;
  real_T c15_u[3];
  const mxArray *c15_b_y = NULL;
  int32_T c15_i1;
  real_T c15_b_u[3];
  const mxArray *c15_c_y = NULL;
  uint8_T c15_hoistedGlobal;
  uint8_T c15_c_u;
  const mxArray *c15_d_y = NULL;
  real_T (*c15_eta_s_use)[3];
  real_T (*c15_eta_s_err)[3];
  c15_eta_s_err = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c15_eta_s_use = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c15_st = NULL;
  c15_st = NULL;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_createcellarray(3), FALSE);
  for (c15_i0 = 0; c15_i0 < 3; c15_i0++) {
    c15_u[c15_i0] = (*c15_eta_s_err)[c15_i0];
  }

  c15_b_y = NULL;
  sf_mex_assign(&c15_b_y, sf_mex_create("y", c15_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c15_y, 0, c15_b_y);
  for (c15_i1 = 0; c15_i1 < 3; c15_i1++) {
    c15_b_u[c15_i1] = (*c15_eta_s_use)[c15_i1];
  }

  c15_c_y = NULL;
  sf_mex_assign(&c15_c_y, sf_mex_create("y", c15_b_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c15_y, 1, c15_c_y);
  c15_hoistedGlobal = chartInstance->c15_is_active_c15_Model_justmodel;
  c15_c_u = c15_hoistedGlobal;
  c15_d_y = NULL;
  sf_mex_assign(&c15_d_y, sf_mex_create("y", &c15_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c15_y, 2, c15_d_y);
  sf_mex_assign(&c15_st, c15_y, FALSE);
  return c15_st;
}

static void set_sim_state_c15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance, const mxArray *c15_st)
{
  const mxArray *c15_u;
  real_T c15_dv0[3];
  int32_T c15_i2;
  real_T c15_dv1[3];
  int32_T c15_i3;
  real_T (*c15_eta_s_err)[3];
  real_T (*c15_eta_s_use)[3];
  c15_eta_s_err = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c15_eta_s_use = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c15_doneDoubleBufferReInit = TRUE;
  c15_u = sf_mex_dup(c15_st);
  c15_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c15_u, 0)),
                       "eta_s_err", c15_dv0);
  for (c15_i2 = 0; c15_i2 < 3; c15_i2++) {
    (*c15_eta_s_err)[c15_i2] = c15_dv0[c15_i2];
  }

  c15_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c15_u, 1)),
                       "eta_s_use", c15_dv1);
  for (c15_i3 = 0; c15_i3 < 3; c15_i3++) {
    (*c15_eta_s_use)[c15_i3] = c15_dv1[c15_i3];
  }

  chartInstance->c15_is_active_c15_Model_justmodel = c15_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c15_u, 2)),
     "is_active_c15_Model_justmodel");
  sf_mex_destroy(&c15_u);
  c15_update_debugger_state_c15_Model_justmodel(chartInstance);
  sf_mex_destroy(&c15_st);
}

static void finalize_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance)
{
}

static void sf_c15_Model_justmodel(SFc15_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c15_i4;
  int32_T c15_i5;
  int32_T c15_i6;
  int32_T c15_i7;
  real_T c15_hoistedGlobal;
  int32_T c15_i8;
  real_T c15_eta_s[3];
  int32_T c15_i9;
  real_T c15_eta_s_obs[3];
  real_T c15_QS_error;
  uint32_T c15_debug_family_var_map[7];
  real_T c15_nargin = 3.0;
  real_T c15_nargout = 2.0;
  real_T c15_eta_s_use[3];
  real_T c15_eta_s_err[3];
  int32_T c15_i10;
  int32_T c15_i11;
  int32_T c15_i12;
  int32_T c15_i13;
  int32_T c15_i14;
  int32_T c15_i15;
  real_T *c15_b_QS_error;
  real_T (*c15_b_eta_s_use)[3];
  real_T (*c15_b_eta_s_err)[3];
  real_T (*c15_b_eta_s_obs)[3];
  real_T (*c15_b_eta_s)[3];
  c15_b_eta_s_err = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c15_b_QS_error = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c15_b_eta_s_obs = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c15_b_eta_s_use = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c15_b_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 14U, chartInstance->c15_sfEvent);
  for (c15_i4 = 0; c15_i4 < 3; c15_i4++) {
    _SFD_DATA_RANGE_CHECK((*c15_b_eta_s)[c15_i4], 0U);
  }

  for (c15_i5 = 0; c15_i5 < 3; c15_i5++) {
    _SFD_DATA_RANGE_CHECK((*c15_b_eta_s_use)[c15_i5], 1U);
  }

  for (c15_i6 = 0; c15_i6 < 3; c15_i6++) {
    _SFD_DATA_RANGE_CHECK((*c15_b_eta_s_obs)[c15_i6], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c15_b_QS_error, 3U);
  for (c15_i7 = 0; c15_i7 < 3; c15_i7++) {
    _SFD_DATA_RANGE_CHECK((*c15_b_eta_s_err)[c15_i7], 4U);
  }

  chartInstance->c15_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 14U, chartInstance->c15_sfEvent);
  c15_hoistedGlobal = *c15_b_QS_error;
  for (c15_i8 = 0; c15_i8 < 3; c15_i8++) {
    c15_eta_s[c15_i8] = (*c15_b_eta_s)[c15_i8];
  }

  for (c15_i9 = 0; c15_i9 < 3; c15_i9++) {
    c15_eta_s_obs[c15_i9] = (*c15_b_eta_s_obs)[c15_i9];
  }

  c15_QS_error = c15_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c15_debug_family_names,
    c15_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_nargin, 0U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c15_nargout, 1U, c15_b_sf_marshallOut,
    c15_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c15_eta_s, 2U, c15_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c15_eta_s_obs, 3U, c15_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c15_QS_error, 4U, c15_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c15_eta_s_use, 5U, c15_sf_marshallOut,
    c15_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c15_eta_s_err, 6U, c15_sf_marshallOut,
    c15_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 4);
  if (CV_EML_IF(0, 1, 0, c15_QS_error == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 5);
    for (c15_i10 = 0; c15_i10 < 3; c15_i10++) {
      c15_eta_s_err[c15_i10] = c15_eta_s[c15_i10] - c15_eta_s_obs[c15_i10];
    }

    _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 6);
    for (c15_i11 = 0; c15_i11 < 3; c15_i11++) {
      c15_eta_s_use[c15_i11] = c15_eta_s[c15_i11];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 8);
    for (c15_i12 = 0; c15_i12 < 3; c15_i12++) {
      c15_eta_s_err[c15_i12] = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, 9);
    for (c15_i13 = 0; c15_i13 < 3; c15_i13++) {
      c15_eta_s_use[c15_i13] = c15_eta_s_obs[c15_i13];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c15_sfEvent, -9);
  _SFD_SYMBOL_SCOPE_POP();
  for (c15_i14 = 0; c15_i14 < 3; c15_i14++) {
    (*c15_b_eta_s_use)[c15_i14] = c15_eta_s_use[c15_i14];
  }

  for (c15_i15 = 0; c15_i15 < 3; c15_i15++) {
    (*c15_b_eta_s_err)[c15_i15] = c15_eta_s_err[c15_i15];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c15_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Model_justmodelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance)
{
}

static void registerMessagesc15_Model_justmodel
  (SFc15_Model_justmodelInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c15_machineNumber, uint32_T
  c15_chartNumber)
{
}

static const mxArray *c15_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData)
{
  const mxArray *c15_mxArrayOutData = NULL;
  int32_T c15_i16;
  real_T c15_b_inData[3];
  int32_T c15_i17;
  real_T c15_u[3];
  const mxArray *c15_y = NULL;
  SFc15_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc15_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c15_mxArrayOutData = NULL;
  for (c15_i16 = 0; c15_i16 < 3; c15_i16++) {
    c15_b_inData[c15_i16] = (*(real_T (*)[3])c15_inData)[c15_i16];
  }

  for (c15_i17 = 0; c15_i17 < 3; c15_i17++) {
    c15_u[c15_i17] = c15_b_inData[c15_i17];
  }

  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", c15_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c15_mxArrayOutData, c15_y, FALSE);
  return c15_mxArrayOutData;
}

static void c15_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_eta_s_err, const char_T *c15_identifier,
  real_T c15_y[3])
{
  emlrtMsgIdentifier c15_thisId;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_eta_s_err), &c15_thisId,
    c15_y);
  sf_mex_destroy(&c15_eta_s_err);
}

static void c15_b_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId,
  real_T c15_y[3])
{
  real_T c15_dv2[3];
  int32_T c15_i18;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), c15_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c15_i18 = 0; c15_i18 < 3; c15_i18++) {
    c15_y[c15_i18] = c15_dv2[c15_i18];
  }

  sf_mex_destroy(&c15_u);
}

static void c15_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData)
{
  const mxArray *c15_eta_s_err;
  const char_T *c15_identifier;
  emlrtMsgIdentifier c15_thisId;
  real_T c15_y[3];
  int32_T c15_i19;
  SFc15_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc15_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c15_eta_s_err = sf_mex_dup(c15_mxArrayInData);
  c15_identifier = c15_varName;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_eta_s_err), &c15_thisId,
    c15_y);
  sf_mex_destroy(&c15_eta_s_err);
  for (c15_i19 = 0; c15_i19 < 3; c15_i19++) {
    (*(real_T (*)[3])c15_outData)[c15_i19] = c15_y[c15_i19];
  }

  sf_mex_destroy(&c15_mxArrayInData);
}

static const mxArray *c15_b_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData)
{
  const mxArray *c15_mxArrayOutData = NULL;
  real_T c15_u;
  const mxArray *c15_y = NULL;
  SFc15_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc15_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c15_mxArrayOutData = NULL;
  c15_u = *(real_T *)c15_inData;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", &c15_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c15_mxArrayOutData, c15_y, FALSE);
  return c15_mxArrayOutData;
}

static real_T c15_c_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId)
{
  real_T c15_y;
  real_T c15_d0;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), &c15_d0, 1, 0, 0U, 0, 0U, 0);
  c15_y = c15_d0;
  sf_mex_destroy(&c15_u);
  return c15_y;
}

static void c15_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData)
{
  const mxArray *c15_nargout;
  const char_T *c15_identifier;
  emlrtMsgIdentifier c15_thisId;
  real_T c15_y;
  SFc15_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc15_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c15_nargout = sf_mex_dup(c15_mxArrayInData);
  c15_identifier = c15_varName;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_y = c15_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_nargout),
    &c15_thisId);
  sf_mex_destroy(&c15_nargout);
  *(real_T *)c15_outData = c15_y;
  sf_mex_destroy(&c15_mxArrayInData);
}

const mxArray *sf_c15_Model_justmodel_get_eml_resolved_functions_info(void)
{
  const mxArray *c15_nameCaptureInfo = NULL;
  c15_nameCaptureInfo = NULL;
  sf_mex_assign(&c15_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c15_nameCaptureInfo;
}

static const mxArray *c15_c_sf_marshallOut(void *chartInstanceVoid, void
  *c15_inData)
{
  const mxArray *c15_mxArrayOutData = NULL;
  int32_T c15_u;
  const mxArray *c15_y = NULL;
  SFc15_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc15_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c15_mxArrayOutData = NULL;
  c15_u = *(int32_T *)c15_inData;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", &c15_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c15_mxArrayOutData, c15_y, FALSE);
  return c15_mxArrayOutData;
}

static int32_T c15_d_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId)
{
  int32_T c15_y;
  int32_T c15_i20;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), &c15_i20, 1, 6, 0U, 0, 0U, 0);
  c15_y = c15_i20;
  sf_mex_destroy(&c15_u);
  return c15_y;
}

static void c15_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c15_mxArrayInData, const char_T *c15_varName, void *c15_outData)
{
  const mxArray *c15_b_sfEvent;
  const char_T *c15_identifier;
  emlrtMsgIdentifier c15_thisId;
  int32_T c15_y;
  SFc15_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc15_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c15_b_sfEvent = sf_mex_dup(c15_mxArrayInData);
  c15_identifier = c15_varName;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_y = c15_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_b_sfEvent),
    &c15_thisId);
  sf_mex_destroy(&c15_b_sfEvent);
  *(int32_T *)c15_outData = c15_y;
  sf_mex_destroy(&c15_mxArrayInData);
}

static uint8_T c15_e_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_b_is_active_c15_Model_justmodel, const
  char_T *c15_identifier)
{
  uint8_T c15_y;
  emlrtMsgIdentifier c15_thisId;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_y = c15_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c15_b_is_active_c15_Model_justmodel), &c15_thisId);
  sf_mex_destroy(&c15_b_is_active_c15_Model_justmodel);
  return c15_y;
}

static uint8_T c15_f_emlrt_marshallIn(SFc15_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId)
{
  uint8_T c15_y;
  uint8_T c15_u0;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), &c15_u0, 1, 3, 0U, 0, 0U, 0);
  c15_y = c15_u0;
  sf_mex_destroy(&c15_u);
  return c15_y;
}

static void init_dsm_address_info(SFc15_Model_justmodelInstanceStruct
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

void sf_c15_Model_justmodel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(273279496U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(730204876U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3170821917U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3327951455U);
}

mxArray *sf_c15_Model_justmodel_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("W1zcanKW732uWktz1OxkBC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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

mxArray *sf_c15_Model_justmodel_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c15_Model_justmodel(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[8],T\"eta_s_err\",},{M[1],M[5],T\"eta_s_use\",},{M[8],M[0],T\"is_active_c15_Model_justmodel\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c15_Model_justmodel_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc15_Model_justmodelInstanceStruct *chartInstance;
    chartInstance = (SFc15_Model_justmodelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Model_justmodelMachineNumber_,
           15,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"eta_s");
          _SFD_SET_DATA_PROPS(1,2,0,1,"eta_s_use");
          _SFD_SET_DATA_PROPS(2,1,1,0,"eta_s_obs");
          _SFD_SET_DATA_PROPS(3,1,1,0,"QS_error");
          _SFD_SET_DATA_PROPS(4,2,0,1,"eta_s_err");
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
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,205);
        _SFD_CV_INIT_EML_IF(0,1,0,68,84,143,205);
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
            1.0,0,0,(MexFcnForType)c15_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c15_sf_marshallOut,(MexInFcnForType)
            c15_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c15_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c15_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c15_sf_marshallOut,(MexInFcnForType)
            c15_sf_marshallIn);
        }

        {
          real_T *c15_QS_error;
          real_T (*c15_eta_s)[3];
          real_T (*c15_eta_s_use)[3];
          real_T (*c15_eta_s_obs)[3];
          real_T (*c15_eta_s_err)[3];
          c15_eta_s_err = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            2);
          c15_QS_error = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c15_eta_s_obs = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S,
            1);
          c15_eta_s_use = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            1);
          c15_eta_s = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c15_eta_s);
          _SFD_SET_DATA_VALUE_PTR(1U, *c15_eta_s_use);
          _SFD_SET_DATA_VALUE_PTR(2U, *c15_eta_s_obs);
          _SFD_SET_DATA_VALUE_PTR(3U, c15_QS_error);
          _SFD_SET_DATA_VALUE_PTR(4U, *c15_eta_s_err);
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
  return "o3yVXKn1Vks8genuOh7YJE";
}

static void sf_opaque_initialize_c15_Model_justmodel(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc15_Model_justmodelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*)
    chartInstanceVar);
  initialize_c15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c15_Model_justmodel(void *chartInstanceVar)
{
  enable_c15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c15_Model_justmodel(void *chartInstanceVar)
{
  disable_c15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c15_Model_justmodel(void *chartInstanceVar)
{
  sf_c15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c15_Model_justmodel(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c15_Model_justmodel
    ((SFc15_Model_justmodelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c15_Model_justmodel();/* state var info */
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

extern void sf_internal_set_sim_state_c15_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c15_Model_justmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c15_Model_justmodel(SimStruct* S)
{
  return sf_internal_get_sim_state_c15_Model_justmodel(S);
}

static void sf_opaque_set_sim_state_c15_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c15_Model_justmodel(S, st);
}

static void sf_opaque_terminate_c15_Model_justmodel(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc15_Model_justmodelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Model_justmodel_optimization_info();
    }

    finalize_c15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c15_Model_justmodel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c15_Model_justmodel((SFc15_Model_justmodelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c15_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Model_justmodel_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      15);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,15,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,15,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,15);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,15,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,15,2);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,15);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3228300485U));
  ssSetChecksum1(S,(3859136089U));
  ssSetChecksum2(S,(1927878112U));
  ssSetChecksum3(S,(756006418U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c15_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c15_Model_justmodel(SimStruct *S)
{
  SFc15_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc15_Model_justmodelInstanceStruct *)utMalloc(sizeof
    (SFc15_Model_justmodelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc15_Model_justmodelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c15_Model_justmodel;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c15_Model_justmodel;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c15_Model_justmodel;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c15_Model_justmodel;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c15_Model_justmodel;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c15_Model_justmodel;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c15_Model_justmodel;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c15_Model_justmodel;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c15_Model_justmodel;
  chartInstance->chartInfo.mdlStart = mdlStart_c15_Model_justmodel;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c15_Model_justmodel;
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

void c15_Model_justmodel_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c15_Model_justmodel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c15_Model_justmodel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c15_Model_justmodel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c15_Model_justmodel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
