/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_overall_sfun.h"
#include "c20_HIL_model_overall.h"
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
static const char * c20_debug_family_names[10] = { "lowLim", "highLim", "b", "a",
  "maxRise", "nargin", "nargout", "pen", "prevPen", "newPen" };

/* Function Declarations */
static void initialize_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance);
static void initialize_params_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance);
static void enable_c20_HIL_model_overall(SFc20_HIL_model_overallInstanceStruct
  *chartInstance);
static void disable_c20_HIL_model_overall(SFc20_HIL_model_overallInstanceStruct *
  chartInstance);
static void c20_update_debugger_state_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance);
static void set_sim_state_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance, const mxArray *c20_st);
static void finalize_c20_HIL_model_overall(SFc20_HIL_model_overallInstanceStruct
  *chartInstance);
static void sf_c20_HIL_model_overall(SFc20_HIL_model_overallInstanceStruct
  *chartInstance);
static void initSimStructsc20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance);
static void registerMessagesc20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c20_machineNumber, uint32_T
  c20_chartNumber);
static const mxArray *c20_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData);
static real_T c20_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_newPen, const char_T *c20_identifier);
static real_T c20_b_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId);
static void c20_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData);
static void c20_eml_scalar_eg(SFc20_HIL_model_overallInstanceStruct
  *chartInstance);
static const mxArray *c20_b_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData);
static int32_T c20_c_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId);
static void c20_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData);
static uint8_T c20_d_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_b_is_active_c20_HIL_model_overall, const
  char_T *c20_identifier);
static uint8_T c20_e_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId);
static void init_dsm_address_info(SFc20_HIL_model_overallInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance)
{
  chartInstance->c20_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c20_is_active_c20_HIL_model_overall = 0U;
}

static void initialize_params_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void enable_c20_HIL_model_overall(SFc20_HIL_model_overallInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c20_HIL_model_overall(SFc20_HIL_model_overallInstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c20_update_debugger_state_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance)
{
  const mxArray *c20_st;
  const mxArray *c20_y = NULL;
  real_T c20_hoistedGlobal;
  real_T c20_u;
  const mxArray *c20_b_y = NULL;
  uint8_T c20_b_hoistedGlobal;
  uint8_T c20_b_u;
  const mxArray *c20_c_y = NULL;
  real_T *c20_newPen;
  c20_newPen = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c20_st = NULL;
  c20_st = NULL;
  c20_y = NULL;
  sf_mex_assign(&c20_y, sf_mex_createcellarray(2), FALSE);
  c20_hoistedGlobal = *c20_newPen;
  c20_u = c20_hoistedGlobal;
  c20_b_y = NULL;
  sf_mex_assign(&c20_b_y, sf_mex_create("y", &c20_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c20_y, 0, c20_b_y);
  c20_b_hoistedGlobal = chartInstance->c20_is_active_c20_HIL_model_overall;
  c20_b_u = c20_b_hoistedGlobal;
  c20_c_y = NULL;
  sf_mex_assign(&c20_c_y, sf_mex_create("y", &c20_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c20_y, 1, c20_c_y);
  sf_mex_assign(&c20_st, c20_y, FALSE);
  return c20_st;
}

static void set_sim_state_c20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance, const mxArray *c20_st)
{
  const mxArray *c20_u;
  real_T *c20_newPen;
  c20_newPen = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c20_doneDoubleBufferReInit = TRUE;
  c20_u = sf_mex_dup(c20_st);
  *c20_newPen = c20_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c20_u, 0)), "newPen");
  chartInstance->c20_is_active_c20_HIL_model_overall = c20_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c20_u, 1)),
     "is_active_c20_HIL_model_overall");
  sf_mex_destroy(&c20_u);
  c20_update_debugger_state_c20_HIL_model_overall(chartInstance);
  sf_mex_destroy(&c20_st);
}

static void finalize_c20_HIL_model_overall(SFc20_HIL_model_overallInstanceStruct
  *chartInstance)
{
}

static void sf_c20_HIL_model_overall(SFc20_HIL_model_overallInstanceStruct
  *chartInstance)
{
  real_T c20_hoistedGlobal;
  real_T c20_b_hoistedGlobal;
  real_T c20_pen;
  real_T c20_prevPen;
  uint32_T c20_debug_family_var_map[10];
  real_T c20_lowLim;
  real_T c20_highLim;
  real_T c20_b;
  real_T c20_a;
  real_T c20_maxRise;
  real_T c20_nargin = 2.0;
  real_T c20_nargout = 1.0;
  real_T c20_newPen;
  real_T c20_b_b;
  real_T c20_y;
  real_T c20_varargin_1;
  real_T c20_varargin_2;
  real_T c20_b_varargin_2;
  real_T c20_varargin_3;
  real_T c20_x;
  real_T c20_b_y;
  real_T c20_b_x;
  real_T c20_c_y;
  real_T c20_xk;
  real_T c20_yk;
  real_T c20_c_x;
  real_T c20_d_y;
  real_T *c20_b_pen;
  real_T *c20_b_newPen;
  real_T *c20_b_prevPen;
  c20_b_prevPen = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c20_b_newPen = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c20_b_pen = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 19U, chartInstance->c20_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c20_b_pen, 0U);
  _SFD_DATA_RANGE_CHECK(*c20_b_newPen, 1U);
  _SFD_DATA_RANGE_CHECK(*c20_b_prevPen, 2U);
  chartInstance->c20_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 19U, chartInstance->c20_sfEvent);
  c20_hoistedGlobal = *c20_b_pen;
  c20_b_hoistedGlobal = *c20_b_prevPen;
  c20_pen = c20_hoistedGlobal;
  c20_prevPen = c20_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c20_debug_family_names,
    c20_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_lowLim, 0U, c20_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_highLim, 1U, c20_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_b, 2U, c20_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_a, 3U, c20_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c20_maxRise, 4U, c20_sf_marshallOut,
    c20_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c20_nargin, 5U, c20_sf_marshallOut,
    c20_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c20_nargout, 6U, c20_sf_marshallOut,
    c20_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_pen, 7U, c20_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c20_prevPen, 8U, c20_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c20_newPen, 9U, c20_sf_marshallOut,
    c20_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 7);
  c20_lowLim = 1.6666666666666667E-6;
  _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 9);
  c20_highLim = 0.00016666666666666666;
  _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 12);
  if (CV_EML_IF(0, 1, 0, c20_pen < c20_prevPen)) {
    _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 13);
    c20_newPen = c20_pen;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 19);
    c20_lowLim = 1.6666666666666668E-7;
    _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 20);
    c20_highLim = 1.6666666666666667E-5;
    _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 22);
    c20_b = 1.6666666666666668E-7;
    _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 23);
    c20_a = 1.65E-5;
    _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 26);
    c20_b_b = c20_prevPen;
    c20_y = 1.65E-5 * c20_b_b;
    c20_maxRise = c20_y + c20_b;
    _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, 28);
    c20_varargin_1 = c20_prevPen + c20_maxRise;
    c20_varargin_2 = c20_pen;
    c20_b_varargin_2 = c20_varargin_1;
    c20_varargin_3 = c20_varargin_2;
    c20_x = c20_b_varargin_2;
    c20_b_y = c20_varargin_3;
    c20_b_x = c20_x;
    c20_c_y = c20_b_y;
    c20_eml_scalar_eg(chartInstance);
    c20_xk = c20_b_x;
    c20_yk = c20_c_y;
    c20_c_x = c20_xk;
    c20_d_y = c20_yk;
    c20_eml_scalar_eg(chartInstance);
    c20_newPen = muDoubleScalarMin(c20_c_x, c20_d_y);
  }

  _SFD_EML_CALL(0U, chartInstance->c20_sfEvent, -28);
  _SFD_SYMBOL_SCOPE_POP();
  *c20_b_newPen = c20_newPen;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c20_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_overallMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void registerMessagesc20_HIL_model_overall
  (SFc20_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c20_machineNumber, uint32_T
  c20_chartNumber)
{
}

static const mxArray *c20_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData)
{
  const mxArray *c20_mxArrayOutData = NULL;
  real_T c20_u;
  const mxArray *c20_y = NULL;
  SFc20_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc20_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c20_mxArrayOutData = NULL;
  c20_u = *(real_T *)c20_inData;
  c20_y = NULL;
  sf_mex_assign(&c20_y, sf_mex_create("y", &c20_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c20_mxArrayOutData, c20_y, FALSE);
  return c20_mxArrayOutData;
}

static real_T c20_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_newPen, const char_T *c20_identifier)
{
  real_T c20_y;
  emlrtMsgIdentifier c20_thisId;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_y = c20_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c20_newPen),
    &c20_thisId);
  sf_mex_destroy(&c20_newPen);
  return c20_y;
}

static real_T c20_b_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId)
{
  real_T c20_y;
  real_T c20_d0;
  sf_mex_import(c20_parentId, sf_mex_dup(c20_u), &c20_d0, 1, 0, 0U, 0, 0U, 0);
  c20_y = c20_d0;
  sf_mex_destroy(&c20_u);
  return c20_y;
}

static void c20_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData)
{
  const mxArray *c20_newPen;
  const char_T *c20_identifier;
  emlrtMsgIdentifier c20_thisId;
  real_T c20_y;
  SFc20_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc20_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c20_newPen = sf_mex_dup(c20_mxArrayInData);
  c20_identifier = c20_varName;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_y = c20_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c20_newPen),
    &c20_thisId);
  sf_mex_destroy(&c20_newPen);
  *(real_T *)c20_outData = c20_y;
  sf_mex_destroy(&c20_mxArrayInData);
}

const mxArray *sf_c20_HIL_model_overall_get_eml_resolved_functions_info(void)
{
  const mxArray *c20_nameCaptureInfo;
  c20_ResolvedFunctionInfo c20_info[11];
  c20_ResolvedFunctionInfo (*c20_b_info)[11];
  const mxArray *c20_m0 = NULL;
  int32_T c20_i0;
  c20_ResolvedFunctionInfo *c20_r0;
  c20_nameCaptureInfo = NULL;
  c20_nameCaptureInfo = NULL;
  c20_b_info = (c20_ResolvedFunctionInfo (*)[11])c20_info;
  (*c20_b_info)[0].context = "";
  (*c20_b_info)[0].name = "mrdivide";
  (*c20_b_info)[0].dominantType = "double";
  (*c20_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c20_b_info)[0].fileTimeLo = 1357951548U;
  (*c20_b_info)[0].fileTimeHi = 0U;
  (*c20_b_info)[0].mFileTimeLo = 1319729966U;
  (*c20_b_info)[0].mFileTimeHi = 0U;
  (*c20_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c20_b_info)[1].name = "rdivide";
  (*c20_b_info)[1].dominantType = "double";
  (*c20_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c20_b_info)[1].fileTimeLo = 1346510388U;
  (*c20_b_info)[1].fileTimeHi = 0U;
  (*c20_b_info)[1].mFileTimeLo = 0U;
  (*c20_b_info)[1].mFileTimeHi = 0U;
  (*c20_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c20_b_info)[2].name = "eml_scalexp_compatible";
  (*c20_b_info)[2].dominantType = "double";
  (*c20_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  (*c20_b_info)[2].fileTimeLo = 1286818796U;
  (*c20_b_info)[2].fileTimeHi = 0U;
  (*c20_b_info)[2].mFileTimeLo = 0U;
  (*c20_b_info)[2].mFileTimeHi = 0U;
  (*c20_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c20_b_info)[3].name = "eml_div";
  (*c20_b_info)[3].dominantType = "double";
  (*c20_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c20_b_info)[3].fileTimeLo = 1313347810U;
  (*c20_b_info)[3].fileTimeHi = 0U;
  (*c20_b_info)[3].mFileTimeLo = 0U;
  (*c20_b_info)[3].mFileTimeHi = 0U;
  (*c20_b_info)[4].context = "";
  (*c20_b_info)[4].name = "mtimes";
  (*c20_b_info)[4].dominantType = "double";
  (*c20_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c20_b_info)[4].fileTimeLo = 1289519692U;
  (*c20_b_info)[4].fileTimeHi = 0U;
  (*c20_b_info)[4].mFileTimeLo = 0U;
  (*c20_b_info)[4].mFileTimeHi = 0U;
  (*c20_b_info)[5].context = "";
  (*c20_b_info)[5].name = "min";
  (*c20_b_info)[5].dominantType = "double";
  (*c20_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  (*c20_b_info)[5].fileTimeLo = 1311255318U;
  (*c20_b_info)[5].fileTimeHi = 0U;
  (*c20_b_info)[5].mFileTimeLo = 0U;
  (*c20_b_info)[5].mFileTimeHi = 0U;
  (*c20_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  (*c20_b_info)[6].name = "eml_min_or_max";
  (*c20_b_info)[6].dominantType = "char";
  (*c20_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  (*c20_b_info)[6].fileTimeLo = 1334071490U;
  (*c20_b_info)[6].fileTimeHi = 0U;
  (*c20_b_info)[6].mFileTimeLo = 0U;
  (*c20_b_info)[6].mFileTimeHi = 0U;
  (*c20_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  (*c20_b_info)[7].name = "eml_scalar_eg";
  (*c20_b_info)[7].dominantType = "double";
  (*c20_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c20_b_info)[7].fileTimeLo = 1286818796U;
  (*c20_b_info)[7].fileTimeHi = 0U;
  (*c20_b_info)[7].mFileTimeLo = 0U;
  (*c20_b_info)[7].mFileTimeHi = 0U;
  (*c20_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  (*c20_b_info)[8].name = "eml_scalexp_alloc";
  (*c20_b_info)[8].dominantType = "double";
  (*c20_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  (*c20_b_info)[8].fileTimeLo = 1352424860U;
  (*c20_b_info)[8].fileTimeHi = 0U;
  (*c20_b_info)[8].mFileTimeLo = 0U;
  (*c20_b_info)[8].mFileTimeHi = 0U;
  (*c20_b_info)[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  (*c20_b_info)[9].name = "eml_index_class";
  (*c20_b_info)[9].dominantType = "";
  (*c20_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c20_b_info)[9].fileTimeLo = 1323170578U;
  (*c20_b_info)[9].fileTimeHi = 0U;
  (*c20_b_info)[9].mFileTimeLo = 0U;
  (*c20_b_info)[9].mFileTimeHi = 0U;
  (*c20_b_info)[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  (*c20_b_info)[10].name = "eml_scalar_eg";
  (*c20_b_info)[10].dominantType = "double";
  (*c20_b_info)[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c20_b_info)[10].fileTimeLo = 1286818796U;
  (*c20_b_info)[10].fileTimeHi = 0U;
  (*c20_b_info)[10].mFileTimeLo = 0U;
  (*c20_b_info)[10].mFileTimeHi = 0U;
  sf_mex_assign(&c20_m0, sf_mex_createstruct("nameCaptureInfo", 1, 11), FALSE);
  for (c20_i0 = 0; c20_i0 < 11; c20_i0++) {
    c20_r0 = &c20_info[c20_i0];
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", c20_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c20_r0->context)), "context", "nameCaptureInfo",
                    c20_i0);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", c20_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c20_r0->name)), "name", "nameCaptureInfo", c20_i0);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo",
      c20_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c20_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c20_i0);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", c20_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c20_r0->resolved)), "resolved",
                    "nameCaptureInfo", c20_i0);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", &c20_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c20_i0);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo", &c20_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c20_i0);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo",
      &c20_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c20_i0);
    sf_mex_addfield(c20_m0, sf_mex_create("nameCaptureInfo",
      &c20_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c20_i0);
  }

  sf_mex_assign(&c20_nameCaptureInfo, c20_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c20_nameCaptureInfo);
  return c20_nameCaptureInfo;
}

static void c20_eml_scalar_eg(SFc20_HIL_model_overallInstanceStruct
  *chartInstance)
{
}

static const mxArray *c20_b_sf_marshallOut(void *chartInstanceVoid, void
  *c20_inData)
{
  const mxArray *c20_mxArrayOutData = NULL;
  int32_T c20_u;
  const mxArray *c20_y = NULL;
  SFc20_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc20_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c20_mxArrayOutData = NULL;
  c20_u = *(int32_T *)c20_inData;
  c20_y = NULL;
  sf_mex_assign(&c20_y, sf_mex_create("y", &c20_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c20_mxArrayOutData, c20_y, FALSE);
  return c20_mxArrayOutData;
}

static int32_T c20_c_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId)
{
  int32_T c20_y;
  int32_T c20_i1;
  sf_mex_import(c20_parentId, sf_mex_dup(c20_u), &c20_i1, 1, 6, 0U, 0, 0U, 0);
  c20_y = c20_i1;
  sf_mex_destroy(&c20_u);
  return c20_y;
}

static void c20_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c20_mxArrayInData, const char_T *c20_varName, void *c20_outData)
{
  const mxArray *c20_b_sfEvent;
  const char_T *c20_identifier;
  emlrtMsgIdentifier c20_thisId;
  int32_T c20_y;
  SFc20_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc20_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c20_b_sfEvent = sf_mex_dup(c20_mxArrayInData);
  c20_identifier = c20_varName;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_y = c20_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c20_b_sfEvent),
    &c20_thisId);
  sf_mex_destroy(&c20_b_sfEvent);
  *(int32_T *)c20_outData = c20_y;
  sf_mex_destroy(&c20_mxArrayInData);
}

static uint8_T c20_d_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_b_is_active_c20_HIL_model_overall, const
  char_T *c20_identifier)
{
  uint8_T c20_y;
  emlrtMsgIdentifier c20_thisId;
  c20_thisId.fIdentifier = c20_identifier;
  c20_thisId.fParent = NULL;
  c20_y = c20_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c20_b_is_active_c20_HIL_model_overall), &c20_thisId);
  sf_mex_destroy(&c20_b_is_active_c20_HIL_model_overall);
  return c20_y;
}

static uint8_T c20_e_emlrt_marshallIn(SFc20_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c20_u, const emlrtMsgIdentifier *c20_parentId)
{
  uint8_T c20_y;
  uint8_T c20_u0;
  sf_mex_import(c20_parentId, sf_mex_dup(c20_u), &c20_u0, 1, 3, 0U, 0, 0U, 0);
  c20_y = c20_u0;
  sf_mex_destroy(&c20_u);
  return c20_y;
}

static void init_dsm_address_info(SFc20_HIL_model_overallInstanceStruct
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

void sf_c20_HIL_model_overall_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3199982810U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3289867667U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(486509135U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3754588209U);
}

mxArray *sf_c20_HIL_model_overall_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("XEp55aULV5ZbVPa7TrEXXD");
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

mxArray *sf_c20_HIL_model_overall_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c20_HIL_model_overall(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"newPen\",},{M[8],M[0],T\"is_active_c20_HIL_model_overall\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c20_HIL_model_overall_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc20_HIL_model_overallInstanceStruct *chartInstance;
    chartInstance = (SFc20_HIL_model_overallInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_overallMachineNumber_,
           20,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"pen");
          _SFD_SET_DATA_PROPS(1,2,0,1,"newPen");
          _SFD_SET_DATA_PROPS(2,1,1,0,"prevPen");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,758);
        _SFD_CV_INIT_EML_IF(0,1,0,333,349,368,758);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c20_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c20_sf_marshallOut,(MexInFcnForType)c20_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c20_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c20_pen;
          real_T *c20_newPen;
          real_T *c20_prevPen;
          c20_prevPen = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c20_newPen = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c20_pen = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c20_pen);
          _SFD_SET_DATA_VALUE_PTR(1U, c20_newPen);
          _SFD_SET_DATA_VALUE_PTR(2U, c20_prevPen);
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
  return "7358mV6jdBsEnCzMAfhPuC";
}

static void sf_opaque_initialize_c20_HIL_model_overall(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc20_HIL_model_overallInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c20_HIL_model_overall((SFc20_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
  initialize_c20_HIL_model_overall((SFc20_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c20_HIL_model_overall(void *chartInstanceVar)
{
  enable_c20_HIL_model_overall((SFc20_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c20_HIL_model_overall(void *chartInstanceVar)
{
  disable_c20_HIL_model_overall((SFc20_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c20_HIL_model_overall(void *chartInstanceVar)
{
  sf_c20_HIL_model_overall((SFc20_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c20_HIL_model_overall(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c20_HIL_model_overall
    ((SFc20_HIL_model_overallInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c20_HIL_model_overall();/* state var info */
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

extern void sf_internal_set_sim_state_c20_HIL_model_overall(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c20_HIL_model_overall();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c20_HIL_model_overall((SFc20_HIL_model_overallInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c20_HIL_model_overall(SimStruct* S)
{
  return sf_internal_get_sim_state_c20_HIL_model_overall(S);
}

static void sf_opaque_set_sim_state_c20_HIL_model_overall(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c20_HIL_model_overall(S, st);
}

static void sf_opaque_terminate_c20_HIL_model_overall(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc20_HIL_model_overallInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_overall_optimization_info();
    }

    finalize_c20_HIL_model_overall((SFc20_HIL_model_overallInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc20_HIL_model_overall((SFc20_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c20_HIL_model_overall(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c20_HIL_model_overall
      ((SFc20_HIL_model_overallInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c20_HIL_model_overall(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_overall_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      20);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,20,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,20,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,20);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,20,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,20,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,20);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(227695681U));
  ssSetChecksum1(S,(2568793074U));
  ssSetChecksum2(S,(508674035U));
  ssSetChecksum3(S,(3996586641U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c20_HIL_model_overall(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c20_HIL_model_overall(SimStruct *S)
{
  SFc20_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc20_HIL_model_overallInstanceStruct *)utMalloc(sizeof
    (SFc20_HIL_model_overallInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc20_HIL_model_overallInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c20_HIL_model_overall;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c20_HIL_model_overall;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c20_HIL_model_overall;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c20_HIL_model_overall;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c20_HIL_model_overall;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c20_HIL_model_overall;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c20_HIL_model_overall;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c20_HIL_model_overall;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c20_HIL_model_overall;
  chartInstance->chartInfo.mdlStart = mdlStart_c20_HIL_model_overall;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c20_HIL_model_overall;
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

void c20_HIL_model_overall_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c20_HIL_model_overall(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c20_HIL_model_overall(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c20_HIL_model_overall(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c20_HIL_model_overall_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
