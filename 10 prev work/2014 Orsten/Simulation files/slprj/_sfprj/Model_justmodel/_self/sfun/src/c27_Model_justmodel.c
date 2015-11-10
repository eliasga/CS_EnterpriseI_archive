/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Model_justmodel_sfun.h"
#include "c27_Model_justmodel.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Model_justmodel_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c27_debug_family_names[9] = { "psi", "gamma", "nargin",
  "nargout", "U", "eta_ship", "alpha_LOS", "surge", "sway" };

/* Function Declarations */
static void initialize_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance);
static void initialize_params_c27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance);
static void enable_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance);
static void disable_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance);
static void c27_update_debugger_state_c27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance);
static void set_sim_state_c27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance, const mxArray *c27_st);
static void finalize_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance);
static void sf_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance);
static void initSimStructsc27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance);
static void registerMessagesc27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c27_machineNumber, uint32_T
  c27_chartNumber);
static const mxArray *c27_sf_marshallOut(void *chartInstanceVoid, void
  *c27_inData);
static real_T c27_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_sway, const char_T *c27_identifier);
static real_T c27_b_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_u, const emlrtMsgIdentifier *c27_parentId);
static void c27_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c27_mxArrayInData, const char_T *c27_varName, void *c27_outData);
static const mxArray *c27_b_sf_marshallOut(void *chartInstanceVoid, void
  *c27_inData);
static const mxArray *c27_c_sf_marshallOut(void *chartInstanceVoid, void
  *c27_inData);
static int32_T c27_c_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_u, const emlrtMsgIdentifier *c27_parentId);
static void c27_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c27_mxArrayInData, const char_T *c27_varName, void *c27_outData);
static uint8_T c27_d_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_b_is_active_c27_Model_justmodel, const
  char_T *c27_identifier);
static uint8_T c27_e_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_u, const emlrtMsgIdentifier *c27_parentId);
static void init_dsm_address_info(SFc27_Model_justmodelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance)
{
  chartInstance->c27_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c27_is_active_c27_Model_justmodel = 0U;
}

static void initialize_params_c27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance)
{
}

static void enable_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c27_update_debugger_state_c27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance)
{
  const mxArray *c27_st;
  const mxArray *c27_y = NULL;
  real_T c27_hoistedGlobal;
  real_T c27_u;
  const mxArray *c27_b_y = NULL;
  real_T c27_b_hoistedGlobal;
  real_T c27_b_u;
  const mxArray *c27_c_y = NULL;
  uint8_T c27_c_hoistedGlobal;
  uint8_T c27_c_u;
  const mxArray *c27_d_y = NULL;
  real_T *c27_surge;
  real_T *c27_sway;
  c27_sway = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c27_surge = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c27_st = NULL;
  c27_st = NULL;
  c27_y = NULL;
  sf_mex_assign(&c27_y, sf_mex_createcellarray(3), FALSE);
  c27_hoistedGlobal = *c27_surge;
  c27_u = c27_hoistedGlobal;
  c27_b_y = NULL;
  sf_mex_assign(&c27_b_y, sf_mex_create("y", &c27_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c27_y, 0, c27_b_y);
  c27_b_hoistedGlobal = *c27_sway;
  c27_b_u = c27_b_hoistedGlobal;
  c27_c_y = NULL;
  sf_mex_assign(&c27_c_y, sf_mex_create("y", &c27_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c27_y, 1, c27_c_y);
  c27_c_hoistedGlobal = chartInstance->c27_is_active_c27_Model_justmodel;
  c27_c_u = c27_c_hoistedGlobal;
  c27_d_y = NULL;
  sf_mex_assign(&c27_d_y, sf_mex_create("y", &c27_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c27_y, 2, c27_d_y);
  sf_mex_assign(&c27_st, c27_y, FALSE);
  return c27_st;
}

static void set_sim_state_c27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance, const mxArray *c27_st)
{
  const mxArray *c27_u;
  real_T *c27_surge;
  real_T *c27_sway;
  c27_sway = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c27_surge = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c27_doneDoubleBufferReInit = TRUE;
  c27_u = sf_mex_dup(c27_st);
  *c27_surge = c27_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c27_u, 0)), "surge");
  *c27_sway = c27_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c27_u, 1)), "sway");
  chartInstance->c27_is_active_c27_Model_justmodel = c27_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c27_u, 2)),
     "is_active_c27_Model_justmodel");
  sf_mex_destroy(&c27_u);
  c27_update_debugger_state_c27_Model_justmodel(chartInstance);
  sf_mex_destroy(&c27_st);
}

static void finalize_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance)
{
}

static void sf_c27_Model_justmodel(SFc27_Model_justmodelInstanceStruct
  *chartInstance)
{
  int32_T c27_i0;
  real_T c27_hoistedGlobal;
  real_T c27_b_hoistedGlobal;
  real_T c27_U;
  int32_T c27_i1;
  real_T c27_eta_ship[3];
  real_T c27_alpha_LOS;
  uint32_T c27_debug_family_var_map[9];
  real_T c27_psi;
  real_T c27_gamma;
  real_T c27_nargin = 3.0;
  real_T c27_nargout = 2.0;
  real_T c27_surge;
  real_T c27_sway;
  real_T c27_x;
  real_T c27_b_x;
  real_T c27_a;
  real_T c27_b;
  real_T c27_c_x;
  real_T c27_d_x;
  real_T c27_b_a;
  real_T c27_b_b;
  real_T *c27_b_U;
  real_T *c27_b_surge;
  real_T *c27_b_alpha_LOS;
  real_T *c27_b_sway;
  real_T (*c27_b_eta_ship)[3];
  c27_b_sway = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c27_b_alpha_LOS = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c27_b_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c27_b_surge = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c27_b_U = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 17U, chartInstance->c27_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c27_b_U, 0U);
  _SFD_DATA_RANGE_CHECK(*c27_b_surge, 1U);
  for (c27_i0 = 0; c27_i0 < 3; c27_i0++) {
    _SFD_DATA_RANGE_CHECK((*c27_b_eta_ship)[c27_i0], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c27_b_alpha_LOS, 3U);
  _SFD_DATA_RANGE_CHECK(*c27_b_sway, 4U);
  chartInstance->c27_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 17U, chartInstance->c27_sfEvent);
  c27_hoistedGlobal = *c27_b_U;
  c27_b_hoistedGlobal = *c27_b_alpha_LOS;
  c27_U = c27_hoistedGlobal;
  for (c27_i1 = 0; c27_i1 < 3; c27_i1++) {
    c27_eta_ship[c27_i1] = (*c27_b_eta_ship)[c27_i1];
  }

  c27_alpha_LOS = c27_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c27_debug_family_names,
    c27_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c27_psi, 0U, c27_sf_marshallOut,
    c27_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c27_gamma, 1U, c27_sf_marshallOut,
    c27_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c27_nargin, 2U, c27_sf_marshallOut,
    c27_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c27_nargout, 3U, c27_sf_marshallOut,
    c27_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c27_U, 4U, c27_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c27_eta_ship, 5U, c27_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c27_alpha_LOS, 6U, c27_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c27_surge, 7U, c27_sf_marshallOut,
    c27_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c27_sway, 8U, c27_sf_marshallOut,
    c27_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c27_sfEvent, 3);
  c27_psi = c27_eta_ship[2];
  _SFD_EML_CALL(0U, chartInstance->c27_sfEvent, 4);
  c27_gamma = c27_alpha_LOS - c27_psi;
  _SFD_EML_CALL(0U, chartInstance->c27_sfEvent, 6);
  c27_x = c27_gamma;
  c27_b_x = c27_x;
  c27_b_x = muDoubleScalarCos(c27_b_x);
  c27_a = c27_U;
  c27_b = c27_b_x;
  c27_surge = c27_a * c27_b;
  _SFD_EML_CALL(0U, chartInstance->c27_sfEvent, 7);
  c27_c_x = c27_gamma;
  c27_d_x = c27_c_x;
  c27_d_x = muDoubleScalarSin(c27_d_x);
  c27_b_a = c27_U;
  c27_b_b = c27_d_x;
  c27_sway = c27_b_a * c27_b_b;
  _SFD_EML_CALL(0U, chartInstance->c27_sfEvent, -7);
  _SFD_SYMBOL_SCOPE_POP();
  *c27_b_surge = c27_surge;
  *c27_b_sway = c27_sway;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c27_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Model_justmodelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance)
{
}

static void registerMessagesc27_Model_justmodel
  (SFc27_Model_justmodelInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c27_machineNumber, uint32_T
  c27_chartNumber)
{
}

static const mxArray *c27_sf_marshallOut(void *chartInstanceVoid, void
  *c27_inData)
{
  const mxArray *c27_mxArrayOutData = NULL;
  real_T c27_u;
  const mxArray *c27_y = NULL;
  SFc27_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc27_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c27_mxArrayOutData = NULL;
  c27_u = *(real_T *)c27_inData;
  c27_y = NULL;
  sf_mex_assign(&c27_y, sf_mex_create("y", &c27_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c27_mxArrayOutData, c27_y, FALSE);
  return c27_mxArrayOutData;
}

static real_T c27_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_sway, const char_T *c27_identifier)
{
  real_T c27_y;
  emlrtMsgIdentifier c27_thisId;
  c27_thisId.fIdentifier = c27_identifier;
  c27_thisId.fParent = NULL;
  c27_y = c27_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c27_sway),
    &c27_thisId);
  sf_mex_destroy(&c27_sway);
  return c27_y;
}

static real_T c27_b_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_u, const emlrtMsgIdentifier *c27_parentId)
{
  real_T c27_y;
  real_T c27_d0;
  sf_mex_import(c27_parentId, sf_mex_dup(c27_u), &c27_d0, 1, 0, 0U, 0, 0U, 0);
  c27_y = c27_d0;
  sf_mex_destroy(&c27_u);
  return c27_y;
}

static void c27_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c27_mxArrayInData, const char_T *c27_varName, void *c27_outData)
{
  const mxArray *c27_sway;
  const char_T *c27_identifier;
  emlrtMsgIdentifier c27_thisId;
  real_T c27_y;
  SFc27_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc27_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c27_sway = sf_mex_dup(c27_mxArrayInData);
  c27_identifier = c27_varName;
  c27_thisId.fIdentifier = c27_identifier;
  c27_thisId.fParent = NULL;
  c27_y = c27_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c27_sway),
    &c27_thisId);
  sf_mex_destroy(&c27_sway);
  *(real_T *)c27_outData = c27_y;
  sf_mex_destroy(&c27_mxArrayInData);
}

static const mxArray *c27_b_sf_marshallOut(void *chartInstanceVoid, void
  *c27_inData)
{
  const mxArray *c27_mxArrayOutData = NULL;
  int32_T c27_i2;
  real_T c27_b_inData[3];
  int32_T c27_i3;
  real_T c27_u[3];
  const mxArray *c27_y = NULL;
  SFc27_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc27_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c27_mxArrayOutData = NULL;
  for (c27_i2 = 0; c27_i2 < 3; c27_i2++) {
    c27_b_inData[c27_i2] = (*(real_T (*)[3])c27_inData)[c27_i2];
  }

  for (c27_i3 = 0; c27_i3 < 3; c27_i3++) {
    c27_u[c27_i3] = c27_b_inData[c27_i3];
  }

  c27_y = NULL;
  sf_mex_assign(&c27_y, sf_mex_create("y", c27_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c27_mxArrayOutData, c27_y, FALSE);
  return c27_mxArrayOutData;
}

const mxArray *sf_c27_Model_justmodel_get_eml_resolved_functions_info(void)
{
  const mxArray *c27_nameCaptureInfo;
  c27_ResolvedFunctionInfo c27_info[5];
  c27_ResolvedFunctionInfo (*c27_b_info)[5];
  const mxArray *c27_m0 = NULL;
  int32_T c27_i4;
  c27_ResolvedFunctionInfo *c27_r0;
  c27_nameCaptureInfo = NULL;
  c27_nameCaptureInfo = NULL;
  c27_b_info = (c27_ResolvedFunctionInfo (*)[5])c27_info;
  (*c27_b_info)[0].context = "";
  (*c27_b_info)[0].name = "cos";
  (*c27_b_info)[0].dominantType = "double";
  (*c27_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c27_b_info)[0].fileTimeLo = 1343830372U;
  (*c27_b_info)[0].fileTimeHi = 0U;
  (*c27_b_info)[0].mFileTimeLo = 0U;
  (*c27_b_info)[0].mFileTimeHi = 0U;
  (*c27_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c27_b_info)[1].name = "eml_scalar_cos";
  (*c27_b_info)[1].dominantType = "double";
  (*c27_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  (*c27_b_info)[1].fileTimeLo = 1286818722U;
  (*c27_b_info)[1].fileTimeHi = 0U;
  (*c27_b_info)[1].mFileTimeLo = 0U;
  (*c27_b_info)[1].mFileTimeHi = 0U;
  (*c27_b_info)[2].context = "";
  (*c27_b_info)[2].name = "mtimes";
  (*c27_b_info)[2].dominantType = "double";
  (*c27_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c27_b_info)[2].fileTimeLo = 1289519692U;
  (*c27_b_info)[2].fileTimeHi = 0U;
  (*c27_b_info)[2].mFileTimeLo = 0U;
  (*c27_b_info)[2].mFileTimeHi = 0U;
  (*c27_b_info)[3].context = "";
  (*c27_b_info)[3].name = "sin";
  (*c27_b_info)[3].dominantType = "double";
  (*c27_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c27_b_info)[3].fileTimeLo = 1343830386U;
  (*c27_b_info)[3].fileTimeHi = 0U;
  (*c27_b_info)[3].mFileTimeLo = 0U;
  (*c27_b_info)[3].mFileTimeHi = 0U;
  (*c27_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c27_b_info)[4].name = "eml_scalar_sin";
  (*c27_b_info)[4].dominantType = "double";
  (*c27_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  (*c27_b_info)[4].fileTimeLo = 1286818736U;
  (*c27_b_info)[4].fileTimeHi = 0U;
  (*c27_b_info)[4].mFileTimeLo = 0U;
  (*c27_b_info)[4].mFileTimeHi = 0U;
  sf_mex_assign(&c27_m0, sf_mex_createstruct("nameCaptureInfo", 1, 5), FALSE);
  for (c27_i4 = 0; c27_i4 < 5; c27_i4++) {
    c27_r0 = &c27_info[c27_i4];
    sf_mex_addfield(c27_m0, sf_mex_create("nameCaptureInfo", c27_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c27_r0->context)), "context", "nameCaptureInfo",
                    c27_i4);
    sf_mex_addfield(c27_m0, sf_mex_create("nameCaptureInfo", c27_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c27_r0->name)), "name", "nameCaptureInfo", c27_i4);
    sf_mex_addfield(c27_m0, sf_mex_create("nameCaptureInfo",
      c27_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c27_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c27_i4);
    sf_mex_addfield(c27_m0, sf_mex_create("nameCaptureInfo", c27_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c27_r0->resolved)), "resolved",
                    "nameCaptureInfo", c27_i4);
    sf_mex_addfield(c27_m0, sf_mex_create("nameCaptureInfo", &c27_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c27_i4);
    sf_mex_addfield(c27_m0, sf_mex_create("nameCaptureInfo", &c27_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c27_i4);
    sf_mex_addfield(c27_m0, sf_mex_create("nameCaptureInfo",
      &c27_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c27_i4);
    sf_mex_addfield(c27_m0, sf_mex_create("nameCaptureInfo",
      &c27_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c27_i4);
  }

  sf_mex_assign(&c27_nameCaptureInfo, c27_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c27_nameCaptureInfo);
  return c27_nameCaptureInfo;
}

static const mxArray *c27_c_sf_marshallOut(void *chartInstanceVoid, void
  *c27_inData)
{
  const mxArray *c27_mxArrayOutData = NULL;
  int32_T c27_u;
  const mxArray *c27_y = NULL;
  SFc27_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc27_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c27_mxArrayOutData = NULL;
  c27_u = *(int32_T *)c27_inData;
  c27_y = NULL;
  sf_mex_assign(&c27_y, sf_mex_create("y", &c27_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c27_mxArrayOutData, c27_y, FALSE);
  return c27_mxArrayOutData;
}

static int32_T c27_c_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_u, const emlrtMsgIdentifier *c27_parentId)
{
  int32_T c27_y;
  int32_T c27_i5;
  sf_mex_import(c27_parentId, sf_mex_dup(c27_u), &c27_i5, 1, 6, 0U, 0, 0U, 0);
  c27_y = c27_i5;
  sf_mex_destroy(&c27_u);
  return c27_y;
}

static void c27_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c27_mxArrayInData, const char_T *c27_varName, void *c27_outData)
{
  const mxArray *c27_b_sfEvent;
  const char_T *c27_identifier;
  emlrtMsgIdentifier c27_thisId;
  int32_T c27_y;
  SFc27_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc27_Model_justmodelInstanceStruct *)chartInstanceVoid;
  c27_b_sfEvent = sf_mex_dup(c27_mxArrayInData);
  c27_identifier = c27_varName;
  c27_thisId.fIdentifier = c27_identifier;
  c27_thisId.fParent = NULL;
  c27_y = c27_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c27_b_sfEvent),
    &c27_thisId);
  sf_mex_destroy(&c27_b_sfEvent);
  *(int32_T *)c27_outData = c27_y;
  sf_mex_destroy(&c27_mxArrayInData);
}

static uint8_T c27_d_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_b_is_active_c27_Model_justmodel, const
  char_T *c27_identifier)
{
  uint8_T c27_y;
  emlrtMsgIdentifier c27_thisId;
  c27_thisId.fIdentifier = c27_identifier;
  c27_thisId.fParent = NULL;
  c27_y = c27_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c27_b_is_active_c27_Model_justmodel), &c27_thisId);
  sf_mex_destroy(&c27_b_is_active_c27_Model_justmodel);
  return c27_y;
}

static uint8_T c27_e_emlrt_marshallIn(SFc27_Model_justmodelInstanceStruct
  *chartInstance, const mxArray *c27_u, const emlrtMsgIdentifier *c27_parentId)
{
  uint8_T c27_y;
  uint8_T c27_u0;
  sf_mex_import(c27_parentId, sf_mex_dup(c27_u), &c27_u0, 1, 3, 0U, 0, 0U, 0);
  c27_y = c27_u0;
  sf_mex_destroy(&c27_u);
  return c27_y;
}

static void init_dsm_address_info(SFc27_Model_justmodelInstanceStruct
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

void sf_c27_Model_justmodel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1234325484U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2454043027U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2042974329U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(591919778U);
}

mxArray *sf_c27_Model_justmodel_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("22Y6r9N2L5gPKVN7ifxNPH");
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c27_Model_justmodel_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c27_Model_justmodel(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"surge\",},{M[1],M[8],T\"sway\",},{M[8],M[0],T\"is_active_c27_Model_justmodel\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c27_Model_justmodel_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc27_Model_justmodelInstanceStruct *chartInstance;
    chartInstance = (SFc27_Model_justmodelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Model_justmodelMachineNumber_,
           27,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"U");
          _SFD_SET_DATA_PROPS(1,2,0,1,"surge");
          _SFD_SET_DATA_PROPS(2,1,1,0,"eta_ship");
          _SFD_SET_DATA_PROPS(3,1,1,0,"alpha_LOS");
          _SFD_SET_DATA_PROPS(4,2,0,1,"sway");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,142);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c27_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c27_sf_marshallOut,(MexInFcnForType)c27_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c27_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c27_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c27_sf_marshallOut,(MexInFcnForType)c27_sf_marshallIn);

        {
          real_T *c27_U;
          real_T *c27_surge;
          real_T *c27_alpha_LOS;
          real_T *c27_sway;
          real_T (*c27_eta_ship)[3];
          c27_sway = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c27_alpha_LOS = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c27_eta_ship = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c27_surge = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c27_U = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c27_U);
          _SFD_SET_DATA_VALUE_PTR(1U, c27_surge);
          _SFD_SET_DATA_VALUE_PTR(2U, *c27_eta_ship);
          _SFD_SET_DATA_VALUE_PTR(3U, c27_alpha_LOS);
          _SFD_SET_DATA_VALUE_PTR(4U, c27_sway);
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
  return "EADHIkZDZp84G7FG02hUSF";
}

static void sf_opaque_initialize_c27_Model_justmodel(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc27_Model_justmodelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*)
    chartInstanceVar);
  initialize_c27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c27_Model_justmodel(void *chartInstanceVar)
{
  enable_c27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c27_Model_justmodel(void *chartInstanceVar)
{
  disable_c27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c27_Model_justmodel(void *chartInstanceVar)
{
  sf_c27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c27_Model_justmodel(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c27_Model_justmodel
    ((SFc27_Model_justmodelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c27_Model_justmodel();/* state var info */
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

extern void sf_internal_set_sim_state_c27_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c27_Model_justmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c27_Model_justmodel(SimStruct* S)
{
  return sf_internal_get_sim_state_c27_Model_justmodel(S);
}

static void sf_opaque_set_sim_state_c27_Model_justmodel(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c27_Model_justmodel(S, st);
}

static void sf_opaque_terminate_c27_Model_justmodel(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc27_Model_justmodelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Model_justmodel_optimization_info();
    }

    finalize_c27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c27_Model_justmodel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c27_Model_justmodel((SFc27_Model_justmodelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c27_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Model_justmodel_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      27);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,27,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,27,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,27);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,27,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,27,2);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,27);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3913897256U));
  ssSetChecksum1(S,(2118158802U));
  ssSetChecksum2(S,(4017571318U));
  ssSetChecksum3(S,(2882035714U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c27_Model_justmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c27_Model_justmodel(SimStruct *S)
{
  SFc27_Model_justmodelInstanceStruct *chartInstance;
  chartInstance = (SFc27_Model_justmodelInstanceStruct *)utMalloc(sizeof
    (SFc27_Model_justmodelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc27_Model_justmodelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c27_Model_justmodel;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c27_Model_justmodel;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c27_Model_justmodel;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c27_Model_justmodel;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c27_Model_justmodel;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c27_Model_justmodel;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c27_Model_justmodel;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c27_Model_justmodel;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c27_Model_justmodel;
  chartInstance->chartInfo.mdlStart = mdlStart_c27_Model_justmodel;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c27_Model_justmodel;
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

void c27_Model_justmodel_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c27_Model_justmodel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c27_Model_justmodel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c27_Model_justmodel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c27_Model_justmodel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
