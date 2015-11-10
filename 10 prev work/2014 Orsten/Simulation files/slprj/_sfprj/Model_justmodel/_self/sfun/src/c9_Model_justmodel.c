/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Model_justmodel_sfun.h"
#include "c9_Model_justmodel.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Model_justmodel_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c9_debug_family_names[6] = { "nu_s", "nargin", "nargout",
  "nu_ship", "alpha1", "z2" };

/* Function Declarations */
static void initialize_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance);
static void initialize_params_c9_Model_justmodel
  (SFc9_Model_justmodelInstanceStruct *chartInstance);
static void enable_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance);
static void disable_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance);
static void c9_update_debugger_state_c9_Model_justmodel
  (SFc9_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c9_Model_justmodel
  (SFc9_Model_justmodelInstanceStruct *chartInstance);
static void set_sim_state_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct *
  chartInstance, const mxArray *c9_st);
static void finalize_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance);
static void sf_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance);
static void initSimStructsc9_Model_justmodel(SFc9_Model_justmodelInstanceStruct *
  chartInstance);
static void registerMessagesc9_Model_justmodel
  (SFc9_Model_justmodelInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber);
static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData);
static void c9_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_z2, const char_T *c9_identifier, real_T
  c9_y[3]);
static void c9_b_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3]);
static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static real_T c9_c_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static int32_T c9_d_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static uint8_T c9_e_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_b_is_active_c9_Model_justmodel, const char_T
  *c9_identifier);
static uint8_T c9_f_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void init_dsm_address_info(SFc9_Model_justmodelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance)
{
  chartInstance->c9_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c9_is_active_c9_Model_justmodel = 0U;
}

static void initialize_params_c9_Model_justmodel
  (SFc9_Model_justmodelInstanceStruct *chartInstance)
{
}

static void enable_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c9_update_debugger_state_c9_Model_justmodel
  (SFc9_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c9_Model_justmodel
  (SFc9_Model_justmodelInstanceStruct *chartInstance)
{
  const mxArray *c9_st;
  const mxArray *c9_y = NULL;
  int32_T c9_i0;
  real_T c9_u[3];
  const mxArray *c9_b_y = NULL;
  uint8_T c9_hoistedGlobal;
  uint8_T c9_b_u;
  const mxArray *c9_c_y = NULL;
  real_T (*c9_z2)[3];
  c9_z2 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_st = NULL;
  c9_st = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_createcellarray(2), FALSE);
  for (c9_i0 = 0; c9_i0 < 3; c9_i0++) {
    c9_u[c9_i0] = (*c9_z2)[c9_i0];
  }

  c9_b_y = NULL;
  sf_mex_assign(&c9_b_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c9_y, 0, c9_b_y);
  c9_hoistedGlobal = chartInstance->c9_is_active_c9_Model_justmodel;
  c9_b_u = c9_hoistedGlobal;
  c9_c_y = NULL;
  sf_mex_assign(&c9_c_y, sf_mex_create("y", &c9_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 1, c9_c_y);
  sf_mex_assign(&c9_st, c9_y, FALSE);
  return c9_st;
}

static void set_sim_state_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct *
  chartInstance, const mxArray *c9_st)
{
  const mxArray *c9_u;
  real_T c9_dv0[3];
  int32_T c9_i1;
  real_T (*c9_z2)[3];
  c9_z2 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c9_doneDoubleBufferReInit = TRUE;
  c9_u = sf_mex_dup(c9_st);
  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 0)), "z2",
                      c9_dv0);
  for (c9_i1 = 0; c9_i1 < 3; c9_i1++) {
    (*c9_z2)[c9_i1] = c9_dv0[c9_i1];
  }

  chartInstance->c9_is_active_c9_Model_justmodel = c9_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 1)),
     "is_active_c9_Model_justmodel");
  sf_mex_destroy(&c9_u);
  c9_update_debugger_state_c9_Model_justmodel(chartInstance);
  sf_mex_destroy(&c9_st);
}

static void finalize_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance)
{
}

static void sf_c9_Model_justmodel(SFc9_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c9_i2;
  int32_T c9_i3;
  int32_T c9_i4;
  int32_T c9_i5;
  real_T c9_nu_ship[3];
  int32_T c9_i6;
  real_T c9_alpha1[3];
  uint32_T c9_debug_family_var_map[6];
  real_T c9_nu_s[3];
  real_T c9_nargin = 2.0;
  real_T c9_nargout = 1.0;
  real_T c9_z2[3];
  int32_T c9_i7;
  int32_T c9_i8;
  int32_T c9_i9;
  real_T (*c9_b_z2)[3];
  real_T (*c9_b_alpha1)[3];
  real_T (*c9_b_nu_ship)[3];
  c9_b_alpha1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c9_b_z2 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_b_nu_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  for (c9_i2 = 0; c9_i2 < 3; c9_i2++) {
    _SFD_DATA_RANGE_CHECK((*c9_b_nu_ship)[c9_i2], 0U);
  }

  for (c9_i3 = 0; c9_i3 < 3; c9_i3++) {
    _SFD_DATA_RANGE_CHECK((*c9_b_z2)[c9_i3], 1U);
  }

  for (c9_i4 = 0; c9_i4 < 3; c9_i4++) {
    _SFD_DATA_RANGE_CHECK((*c9_b_alpha1)[c9_i4], 2U);
  }

  chartInstance->c9_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  for (c9_i5 = 0; c9_i5 < 3; c9_i5++) {
    c9_nu_ship[c9_i5] = (*c9_b_nu_ship)[c9_i5];
  }

  for (c9_i6 = 0; c9_i6 < 3; c9_i6++) {
    c9_alpha1[c9_i6] = (*c9_b_alpha1)[c9_i6];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c9_debug_family_names,
    c9_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_nu_s, 0U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargin, 1U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargout, 2U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_nu_ship, 3U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_alpha1, 4U, c9_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_z2, 5U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 5);
  CV_EML_IF(0, 1, 0, TRUE);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 6);
  for (c9_i7 = 0; c9_i7 < 3; c9_i7++) {
    c9_nu_s[c9_i7] = c9_nu_ship[c9_i7];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 11);
  for (c9_i8 = 0; c9_i8 < 3; c9_i8++) {
    c9_z2[c9_i8] = c9_nu_s[c9_i8] - c9_alpha1[c9_i8];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, -11);
  _SFD_SYMBOL_SCOPE_POP();
  for (c9_i9 = 0; c9_i9 < 3; c9_i9++) {
    (*c9_b_z2)[c9_i9] = c9_z2[c9_i9];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Model_justmodelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc9_Model_justmodel(SFc9_Model_justmodelInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc9_Model_justmodel
  (SFc9_Model_justmodelInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber)
{
}

static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i10;
  real_T c9_b_inData[3];
  int32_T c9_i11;
  real_T c9_u[3];
  const mxArray *c9_y = NULL;
  SFc9_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc9_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i10 = 0; c9_i10 < 3; c9_i10++) {
    c9_b_inData[c9_i10] = (*(real_T (*)[3])c9_inData)[c9_i10];
  }

  for (c9_i11 = 0; c9_i11 < 3; c9_i11++) {
    c9_u[c9_i11] = c9_b_inData[c9_i11];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_z2, const char_T *c9_identifier, real_T
  c9_y[3])
{
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_z2), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_z2);
}

static void c9_b_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3])
{
  real_T c9_dv1[3];
  int32_T c9_i12;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c9_i12 = 0; c9_i12 < 3; c9_i12++) {
    c9_y[c9_i12] = c9_dv1[c9_i12];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_z2;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[3];
  int32_T c9_i13;
  SFc9_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc9_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c9_z2 = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_z2), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_z2);
  for (c9_i13 = 0; c9_i13 < 3; c9_i13++) {
    (*(real_T (*)[3])c9_outData)[c9_i13] = c9_y[c9_i13];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc9_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static real_T c9_c_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d0, 1, 0, 0U, 0, 0U, 0);
  c9_y = c9_d0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_nargout;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc9_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c9_nargout = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_nargout), &c9_thisId);
  sf_mex_destroy(&c9_nargout);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

const mxArray *sf_c9_Model_justmodel_get_eml_resolved_functions_info(void)
{
  const mxArray *c9_nameCaptureInfo;
  c9_ResolvedFunctionInfo c9_info[1];
  c9_ResolvedFunctionInfo (*c9_b_info)[1];
  const mxArray *c9_m0 = NULL;
  int32_T c9_i14;
  c9_ResolvedFunctionInfo *c9_r0;
  c9_nameCaptureInfo = NULL;
  c9_nameCaptureInfo = NULL;
  c9_b_info = (c9_ResolvedFunctionInfo (*)[1])c9_info;
  (*c9_b_info)[0].context = "";
  (*c9_b_info)[0].name = "length";
  (*c9_b_info)[0].dominantType = "double";
  (*c9_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  (*c9_b_info)[0].fileTimeLo = 1303146206U;
  (*c9_b_info)[0].fileTimeHi = 0U;
  (*c9_b_info)[0].mFileTimeLo = 0U;
  (*c9_b_info)[0].mFileTimeHi = 0U;
  sf_mex_assign(&c9_m0, sf_mex_createstruct("nameCaptureInfo", 1, 1), FALSE);
  for (c9_i14 = 0; c9_i14 < 1; c9_i14++) {
    c9_r0 = &c9_info[c9_i14];
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->context)), "context", "nameCaptureInfo",
                    c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c9_r0->name)), "name", "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c9_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->resolved)), "resolved", "nameCaptureInfo",
                    c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c9_i14);
  }

  sf_mex_assign(&c9_nameCaptureInfo, c9_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c9_nameCaptureInfo);
  return c9_nameCaptureInfo;
}

static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc9_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(int32_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static int32_T c9_d_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  int32_T c9_y;
  int32_T c9_i15;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_i15, 1, 6, 0U, 0, 0U, 0);
  c9_y = c9_i15;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_sfEvent;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y;
  SFc9_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc9_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c9_b_sfEvent = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_sfEvent),
    &c9_thisId);
  sf_mex_destroy(&c9_b_sfEvent);
  *(int32_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static uint8_T c9_e_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_b_is_active_c9_Model_justmodel, const char_T
  *c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c9_b_is_active_c9_Model_justmodel), &c9_thisId);
  sf_mex_destroy(&c9_b_is_active_c9_Model_justmodel);
  return c9_y;
}

static uint8_T c9_f_emlrt_marshallIn(SFc9_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  uint8_T c9_u0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_u0, 1, 3, 0U, 0, 0U, 0);
  c9_y = c9_u0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void init_dsm_address_info(SFc9_Model_justmodelInstanceStruct
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

void sf_c9_Model_justmodel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(418760340U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1376120814U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(179997232U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1808044482U);
}

mxArray *sf_c9_Model_justmodel_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("PScgNGCMFVfnekBdZR2I7C");
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

mxArray *sf_c9_Model_justmodel_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c9_Model_justmodel(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"z2\",},{M[8],M[0],T\"is_active_c9_Model_justmodel\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c9_Model_justmodel_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc9_Model_justmodelInstanceStruct *chartInstance;
    chartInstance = (SFc9_Model_justmodelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Model_justmodelMachineNumber_,
           9,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"nu_ship");
          _SFD_SET_DATA_PROPS(1,2,0,1,"z2");
          _SFD_SET_DATA_PROPS(2,1,1,0,"alpha1");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,139);
        _SFD_CV_INIT_EML_IF(0,1,0,47,69,90,118);
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
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c9_nu_ship)[3];
          real_T (*c9_z2)[3];
          real_T (*c9_alpha1)[3];
          c9_alpha1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c9_z2 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c9_nu_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c9_nu_ship);
          _SFD_SET_DATA_VALUE_PTR(1U, *c9_z2);
          _SFD_SET_DATA_VALUE_PTR(2U, *c9_alpha1);
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
  return "c10O9G8JXfEj3YBB8w0Yn";
}

static void sf_opaque_initialize_c9_Model_justmodel(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc9_Model_justmodelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*)
    chartInstanceVar);
  initialize_c9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c9_Model_justmodel(void *chartInstanceVar)
{
  enable_c9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c9_Model_justmodel(void *chartInstanceVar)
{
  disable_c9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c9_Model_justmodel(void *chartInstanceVar)
{
  sf_c9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c9_Model_justmodel(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c9_Model_justmodel
    ((SFc9_Model_justmodelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_Model_justmodel();/* state var info */
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

extern void sf_internal_set_sim_state_c9_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_Model_justmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c9_Model_justmodel(SimStruct* S)
{
  return sf_internal_get_sim_state_c9_Model_justmodel(S);
}

static void sf_opaque_set_sim_state_c9_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c9_Model_justmodel(S, st);
}

static void sf_opaque_terminate_c9_Model_justmodel(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc9_Model_justmodelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Model_justmodel_optimization_info();
    }

    finalize_c9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c9_Model_justmodel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c9_Model_justmodel((SFc9_Model_justmodelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c9_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Model_justmodel_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      9);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,9,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,9,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,9);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,9,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,9,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,9);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3095132736U));
  ssSetChecksum1(S,(2361543038U));
  ssSetChecksum2(S,(1907215156U));
  ssSetChecksum3(S,(2616287883U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c9_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c9_Model_justmodel(SimStruct *S)
{
  SFc9_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc9_Model_justmodelInstanceStruct *)utMalloc(sizeof
    (SFc9_Model_justmodelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc9_Model_justmodelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c9_Model_justmodel;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c9_Model_justmodel;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c9_Model_justmodel;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c9_Model_justmodel;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c9_Model_justmodel;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c9_Model_justmodel;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c9_Model_justmodel;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c9_Model_justmodel;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c9_Model_justmodel;
  chartInstance->chartInfo.mdlStart = mdlStart_c9_Model_justmodel;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c9_Model_justmodel;
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

void c9_Model_justmodel_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c9_Model_justmodel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c9_Model_justmodel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c9_Model_justmodel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c9_Model_justmodel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}