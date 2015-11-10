/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_sfun.h"
#include "c5_HIL_model.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HIL_model_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c5_debug_family_names[13] = { "deltaOverturn",
  "deltaRupture", "deltaSlippage", "overturn", "rupture", "slippage", "nargin",
  "nargout", "deltaIndex", "limits", "preDisconnect", "theTime", "disconnect" };

/* Function Declarations */
static void initialize_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance);
static void initialize_params_c5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance);
static void enable_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance);
static void disable_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance);
static void set_sim_state_c5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c5_st);
static void finalize_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance);
static void sf_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance);
static void initSimStructsc5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance);
static void registerMessagesc5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static real_T c5_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_disconnect, const char_T *c5_identifier);
static real_T c5_b_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_c_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_d_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_b_is_active_c5_HIL_model, const char_T *c5_identifier);
static uint8_T c5_e_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_HIL_modelInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance)
{
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c5_is_active_c5_HIL_model = 0U;
}

static void initialize_params_c5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void enable_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c5_update_debugger_state_c5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real_T c5_hoistedGlobal;
  real_T c5_u;
  const mxArray *c5_b_y = NULL;
  uint8_T c5_b_hoistedGlobal;
  uint8_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  real_T *c5_disconnect;
  c5_disconnect = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellarray(2), FALSE);
  c5_hoistedGlobal = *c5_disconnect;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = chartInstance->c5_is_active_c5_HIL_model;
  c5_b_u = c5_b_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  sf_mex_assign(&c5_st, c5_y, FALSE);
  return c5_st;
}

static void set_sim_state_c5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  real_T *c5_disconnect;
  c5_disconnect = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c5_doneDoubleBufferReInit = TRUE;
  c5_u = sf_mex_dup(c5_st);
  *c5_disconnect = c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 0)), "disconnect");
  chartInstance->c5_is_active_c5_HIL_model = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 1)), "is_active_c5_HIL_model");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_HIL_model(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance)
{
}

static void sf_c5_HIL_model(SFc5_HIL_modelInstanceStruct *chartInstance)
{
  int32_T c5_i0;
  int32_T c5_i1;
  real_T c5_hoistedGlobal;
  real_T c5_b_hoistedGlobal;
  int32_T c5_i2;
  real_T c5_deltaIndex[3];
  int32_T c5_i3;
  real_T c5_limits[3];
  real_T c5_preDisconnect;
  real_T c5_theTime;
  uint32_T c5_debug_family_var_map[13];
  real_T c5_deltaOverturn;
  real_T c5_deltaRupture;
  real_T c5_deltaSlippage;
  real_T c5_overturn;
  real_T c5_rupture;
  real_T c5_slippage;
  real_T c5_nargin = 4.0;
  real_T c5_nargout = 1.0;
  real_T c5_disconnect;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  int32_T c5_i4;
  static char_T c5_cv0[48] = { 'I', 'c', 'e', 'b', 'e', 'r', 'g', ' ', 'h', 'a',
    's', ' ', 'o', 'v', 'e', 'r', 't', 'u', 'r', 'n', 'e', 'd', ',', ' ', 't',
    'o', 'w', 'l', 'i', 'n', 'e', ' ', 'i', 's', ' ', 'd', 'i', 's', 'c', 'o',
    'n', 'n', 'e', 'c', 't', 'e', 'd', '.' };

  char_T c5_b_u[48];
  const mxArray *c5_b_y = NULL;
  real_T c5_c_u;
  const mxArray *c5_c_y = NULL;
  int32_T c5_i5;
  static char_T c5_cv1[42] = { 'T', 'o', 'w', 'l', 'i', 'n', 'e', ' ', 'h', 'a',
    's', ' ', 'r', 'u', 'p', 't', 'u', 'r', 'e', 'd', ',', ' ', 'a', 'n', 'd',
    ' ', 'i', 's', ' ', 'd', 'i', 's', 'c', 'o', 'n', 'n', 'e', 'c', 't', 'e',
    'd', '.' };

  char_T c5_d_u[42];
  const mxArray *c5_d_y = NULL;
  real_T c5_e_u;
  const mxArray *c5_e_y = NULL;
  int32_T c5_i6;
  static char_T c5_cv2[41] = { 'T', 'o', 'w', 'l', 'i', 'n', 'e', ' ', 'h', 'a',
    's', ' ', 's', 'l', 'i', 'p', 'p', 'e', 'd', ',', ' ', 'a', 'n', 'd', ' ',
    'i', 's', ' ', 'd', 'i', 's', 'c', 'o', 'n', 'n', 'e', 'c', 't', 'e', 'd',
    '.' };

  char_T c5_f_u[41];
  const mxArray *c5_f_y = NULL;
  real_T *c5_b_disconnect;
  real_T *c5_b_preDisconnect;
  real_T *c5_b_theTime;
  real_T (*c5_b_limits)[3];
  real_T (*c5_b_deltaIndex)[3];
  boolean_T guard1 = FALSE;
  c5_b_theTime = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c5_b_preDisconnect = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c5_b_limits = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c5_b_disconnect = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_b_deltaIndex = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  for (c5_i0 = 0; c5_i0 < 3; c5_i0++) {
    _SFD_DATA_RANGE_CHECK((*c5_b_deltaIndex)[c5_i0], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c5_b_disconnect, 1U);
  for (c5_i1 = 0; c5_i1 < 3; c5_i1++) {
    _SFD_DATA_RANGE_CHECK((*c5_b_limits)[c5_i1], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c5_b_preDisconnect, 3U);
  _SFD_DATA_RANGE_CHECK(*c5_b_theTime, 4U);
  chartInstance->c5_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  c5_hoistedGlobal = *c5_b_preDisconnect;
  c5_b_hoistedGlobal = *c5_b_theTime;
  for (c5_i2 = 0; c5_i2 < 3; c5_i2++) {
    c5_deltaIndex[c5_i2] = (*c5_b_deltaIndex)[c5_i2];
  }

  for (c5_i3 = 0; c5_i3 < 3; c5_i3++) {
    c5_limits[c5_i3] = (*c5_b_limits)[c5_i3];
  }

  c5_preDisconnect = c5_hoistedGlobal;
  c5_theTime = c5_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_deltaOverturn, 0U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_deltaRupture, 1U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_deltaSlippage, 2U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_overturn, 3U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_rupture, 4U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_slippage, 5U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 6U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 7U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_deltaIndex, 8U, c5_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_limits, 9U, c5_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_preDisconnect, 10U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_theTime, 11U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_disconnect, 12U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 4);
  c5_disconnect = c5_preDisconnect;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 6);
  guard1 = FALSE;
  if (CV_EML_COND(0, 1, 0, c5_preDisconnect == 0.0)) {
    if (CV_EML_COND(0, 1, 1, c5_theTime > 0.0)) {
      CV_EML_MCDC(0, 1, 0, TRUE);
      CV_EML_IF(0, 1, 0, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 8);
      c5_deltaOverturn = c5_deltaIndex[2];
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 9);
      c5_deltaRupture = c5_deltaIndex[0];
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 10);
      c5_deltaSlippage = c5_deltaIndex[1];
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 12);
      c5_overturn = c5_limits[0];
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 13);
      c5_rupture = c5_limits[1];
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 14);
      c5_slippage = c5_limits[2];
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 16);
      if (CV_EML_IF(0, 1, 1, c5_deltaOverturn < c5_overturn)) {
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 18);
        sf_mex_printf("%s =\\n", "theTime");
        c5_u = c5_theTime;
        c5_y = NULL;
        sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c5_y);
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 19);
        for (c5_i4 = 0; c5_i4 < 48; c5_i4++) {
          c5_b_u[c5_i4] = c5_cv0[c5_i4];
        }

        c5_b_y = NULL;
        sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_b_u, 10, 0U, 1U, 0U, 2, 1,
          48), FALSE);
        sf_mex_call_debug("disp", 0U, 1U, 14, c5_b_y);
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 20);
        c5_disconnect = 1.0;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 22);
        if (CV_EML_IF(0, 1, 2, c5_deltaRupture < c5_rupture)) {
          _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 24);
          sf_mex_printf("%s =\\n", "theTime");
          c5_c_u = c5_theTime;
          c5_c_y = NULL;
          sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_c_u, 0, 0U, 0U, 0U, 0),
                        FALSE);
          sf_mex_call_debug("disp", 0U, 1U, 14, c5_c_y);
          _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 25);
          for (c5_i5 = 0; c5_i5 < 42; c5_i5++) {
            c5_d_u[c5_i5] = c5_cv1[c5_i5];
          }

          c5_d_y = NULL;
          sf_mex_assign(&c5_d_y, sf_mex_create("y", c5_d_u, 10, 0U, 1U, 0U, 2, 1,
            42), FALSE);
          sf_mex_call_debug("disp", 0U, 1U, 14, c5_d_y);
          _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 26);
          c5_disconnect = 1.0;
        } else {
          _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 28);
          if (CV_EML_IF(0, 1, 3, c5_deltaSlippage < c5_slippage)) {
            _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 30);
            sf_mex_printf("%s =\\n", "theTime");
            c5_e_u = c5_theTime;
            c5_e_y = NULL;
            sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_e_u, 0, 0U, 0U, 0U, 0),
                          FALSE);
            sf_mex_call_debug("disp", 0U, 1U, 14, c5_e_y);
            _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 31);
            for (c5_i6 = 0; c5_i6 < 41; c5_i6++) {
              c5_f_u[c5_i6] = c5_cv2[c5_i6];
            }

            c5_f_y = NULL;
            sf_mex_assign(&c5_f_y, sf_mex_create("y", c5_f_u, 10, 0U, 1U, 0U, 2,
              1, 41), FALSE);
            sf_mex_call_debug("disp", 0U, 1U, 14, c5_f_y);
            _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 32);
            c5_disconnect = 1.0;
          }
        }
      }
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 0, FALSE);
    CV_EML_IF(0, 1, 0, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -32);
  _SFD_SYMBOL_SCOPE_POP();
  *c5_b_disconnect = c5_disconnect;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc5_HIL_model(SFc5_HIL_modelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber)
{
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc5_HIL_modelInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static real_T c5_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_disconnect, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_disconnect),
    &c5_thisId);
  sf_mex_destroy(&c5_disconnect);
  return c5_y;
}

static real_T c5_b_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_disconnect;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc5_HIL_modelInstanceStruct *)chartInstanceVoid;
  c5_disconnect = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_disconnect),
    &c5_thisId);
  sf_mex_destroy(&c5_disconnect);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i7;
  real_T c5_b_inData[3];
  int32_T c5_i8;
  real_T c5_u[3];
  const mxArray *c5_y = NULL;
  SFc5_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc5_HIL_modelInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i7 = 0; c5_i7 < 3; c5_i7++) {
    c5_b_inData[c5_i7] = (*(real_T (*)[3])c5_inData)[c5_i7];
  }

  for (c5_i8 = 0; c5_i8 < 3; c5_i8++) {
    c5_u[c5_i8] = c5_b_inData[c5_i8];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i9;
  real_T c5_b_inData[3];
  int32_T c5_i10;
  real_T c5_u[3];
  const mxArray *c5_y = NULL;
  SFc5_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc5_HIL_modelInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i9 = 0; c5_i9 < 3; c5_i9++) {
    c5_b_inData[c5_i9] = (*(real_T (*)[3])c5_inData)[c5_i9];
  }

  for (c5_i10 = 0; c5_i10 < 3; c5_i10++) {
    c5_u[c5_i10] = c5_b_inData[c5_i10];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

const mxArray *sf_c5_HIL_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo;
  c5_ResolvedFunctionInfo c5_info[1];
  c5_ResolvedFunctionInfo (*c5_b_info)[1];
  const mxArray *c5_m0 = NULL;
  int32_T c5_i11;
  c5_ResolvedFunctionInfo *c5_r0;
  c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  c5_b_info = (c5_ResolvedFunctionInfo (*)[1])c5_info;
  (*c5_b_info)[0].context = "";
  (*c5_b_info)[0].name = "disp";
  (*c5_b_info)[0].dominantType = "char";
  (*c5_b_info)[0].resolved = "[IXMB]$matlabroot$/toolbox/matlab/lang/disp";
  (*c5_b_info)[0].fileTimeLo = MAX_uint32_T;
  (*c5_b_info)[0].fileTimeHi = MAX_uint32_T;
  (*c5_b_info)[0].mFileTimeLo = MAX_uint32_T;
  (*c5_b_info)[0].mFileTimeHi = MAX_uint32_T;
  sf_mex_assign(&c5_m0, sf_mex_createstruct("nameCaptureInfo", 1, 1), FALSE);
  for (c5_i11 = 0; c5_i11 < 1; c5_i11++) {
    c5_r0 = &c5_info[c5_i11];
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c5_r0->context)), "context", "nameCaptureInfo",
                    c5_i11);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c5_r0->name)), "name", "nameCaptureInfo", c5_i11);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c5_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c5_i11);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c5_r0->resolved)), "resolved", "nameCaptureInfo",
                    c5_i11);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c5_i11);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c5_i11);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c5_i11);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c5_i11);
  }

  sf_mex_assign(&c5_nameCaptureInfo, c5_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c5_nameCaptureInfo);
  return c5_nameCaptureInfo;
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc5_HIL_modelInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static int32_T c5_c_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i12;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i12, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i12;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc5_HIL_modelInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static uint8_T c5_d_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_b_is_active_c5_HIL_model, const char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_is_active_c5_HIL_model), &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_HIL_model);
  return c5_y;
}

static uint8_T c5_e_emlrt_marshallIn(SFc5_HIL_modelInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_HIL_modelInstanceStruct *chartInstance)
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

void sf_c5_HIL_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3871986961U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1901429653U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3402338567U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1844923651U);
}

mxArray *sf_c5_HIL_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("mLUCAsKQO1Jrkerz4va37C");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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

mxArray *sf_c5_HIL_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c5_HIL_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"disconnect\",},{M[8],M[0],T\"is_active_c5_HIL_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_HIL_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_HIL_modelInstanceStruct *chartInstance;
    chartInstance = (SFc5_HIL_modelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_modelMachineNumber_,
           5,
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
          init_script_number_translation(_HIL_modelMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HIL_modelMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HIL_modelMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"deltaIndex");
          _SFD_SET_DATA_PROPS(1,2,0,1,"disconnect");
          _SFD_SET_DATA_PROPS(2,1,1,0,"limits");
          _SFD_SET_DATA_PROPS(3,1,1,0,"preDisconnect");
          _SFD_SET_DATA_PROPS(4,1,1,0,"theTime");
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
        _SFD_CV_INIT_EML(0,1,1,4,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,813);
        _SFD_CV_INIT_EML_IF(0,1,0,110,146,-1,808);
        _SFD_CV_INIT_EML_IF(0,1,1,343,370,491,520);
        _SFD_CV_INIT_EML_IF(0,1,2,491,520,643,799);
        _SFD_CV_INIT_EML_IF(0,1,3,643,674,-1,674);

        {
          static int condStart[] = { 113, 135 };

          static int condEnd[] = { 131, 146 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,113,146,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

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
            1.0,0,0,(MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c5_disconnect;
          real_T *c5_preDisconnect;
          real_T *c5_theTime;
          real_T (*c5_deltaIndex)[3];
          real_T (*c5_limits)[3];
          c5_theTime = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c5_preDisconnect = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c5_limits = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c5_disconnect = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c5_deltaIndex = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S,
            0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c5_deltaIndex);
          _SFD_SET_DATA_VALUE_PTR(1U, c5_disconnect);
          _SFD_SET_DATA_VALUE_PTR(2U, *c5_limits);
          _SFD_SET_DATA_VALUE_PTR(3U, c5_preDisconnect);
          _SFD_SET_DATA_VALUE_PTR(4U, c5_theTime);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HIL_modelMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "2mWZCGJzRtXjkDmrv5cJOB";
}

static void sf_opaque_initialize_c5_HIL_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_HIL_modelInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c5_HIL_model((SFc5_HIL_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c5_HIL_model((SFc5_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_HIL_model(void *chartInstanceVar)
{
  enable_c5_HIL_model((SFc5_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_HIL_model(void *chartInstanceVar)
{
  disable_c5_HIL_model((SFc5_HIL_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_HIL_model(void *chartInstanceVar)
{
  sf_c5_HIL_model((SFc5_HIL_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_HIL_model(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_HIL_model((SFc5_HIL_modelInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_HIL_model();/* state var info */
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

extern void sf_internal_set_sim_state_c5_HIL_model(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_HIL_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_HIL_model((SFc5_HIL_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_HIL_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_HIL_model(S);
}

static void sf_opaque_set_sim_state_c5_HIL_model(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c5_HIL_model(S, st);
}

static void sf_opaque_terminate_c5_HIL_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_HIL_modelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_optimization_info();
    }

    finalize_c5_HIL_model((SFc5_HIL_modelInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_HIL_model((SFc5_HIL_modelInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_HIL_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_HIL_model((SFc5_HIL_modelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_HIL_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,5,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4077711212U));
  ssSetChecksum1(S,(3054824821U));
  ssSetChecksum2(S,(2766824674U));
  ssSetChecksum3(S,(1075745747U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_HIL_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_HIL_model(SimStruct *S)
{
  SFc5_HIL_modelInstanceStruct *chartInstance;
  chartInstance = (SFc5_HIL_modelInstanceStruct *)utMalloc(sizeof
    (SFc5_HIL_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_HIL_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_HIL_model;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_HIL_model;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_HIL_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_HIL_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_HIL_model;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_HIL_model;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_HIL_model;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_HIL_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_HIL_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_HIL_model;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_HIL_model;
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

void c5_HIL_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_HIL_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_HIL_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_HIL_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_HIL_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
