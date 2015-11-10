/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HIL_model_overall_sfun.h"
#include "c28_HIL_model_overall.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HIL_model_overall_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c28_debug_family_names[17] = { "switchTime", "switchDur",
  "ini_gain", "reg_gain", "nargin", "nargout", "eta_ini", "nu_ini", "eta", "nu",
  "eta_end", "nu_end", "time", "WPi", "nWP", "eta_out", "nu_out" };

/* Function Declarations */
static void initialize_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance);
static void initialize_params_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance);
static void enable_c28_HIL_model_overall(SFc28_HIL_model_overallInstanceStruct
  *chartInstance);
static void disable_c28_HIL_model_overall(SFc28_HIL_model_overallInstanceStruct *
  chartInstance);
static void c28_update_debugger_state_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance);
static void set_sim_state_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance, const mxArray *c28_st);
static void finalize_c28_HIL_model_overall(SFc28_HIL_model_overallInstanceStruct
  *chartInstance);
static void sf_c28_HIL_model_overall(SFc28_HIL_model_overallInstanceStruct
  *chartInstance);
static void initSimStructsc28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance);
static void registerMessagesc28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c28_machineNumber, uint32_T
  c28_chartNumber);
static const mxArray *c28_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData);
static void c28_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_nu_out, const char_T *c28_identifier,
  real_T c28_y[3]);
static void c28_b_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId,
  real_T c28_y[3]);
static void c28_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData);
static const mxArray *c28_b_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData);
static real_T c28_c_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId);
static void c28_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData);
static const mxArray *c28_c_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData);
static int32_T c28_d_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId);
static void c28_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData);
static uint8_T c28_e_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_b_is_active_c28_HIL_model_overall, const
  char_T *c28_identifier);
static uint8_T c28_f_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId);
static void init_dsm_address_info(SFc28_HIL_model_overallInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance)
{
  chartInstance->c28_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c28_is_active_c28_HIL_model_overall = 0U;
}

static void initialize_params_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void enable_c28_HIL_model_overall(SFc28_HIL_model_overallInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c28_HIL_model_overall(SFc28_HIL_model_overallInstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c28_update_debugger_state_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance)
{
  const mxArray *c28_st;
  const mxArray *c28_y = NULL;
  int32_T c28_i0;
  real_T c28_u[3];
  const mxArray *c28_b_y = NULL;
  int32_T c28_i1;
  real_T c28_b_u[3];
  const mxArray *c28_c_y = NULL;
  uint8_T c28_hoistedGlobal;
  uint8_T c28_c_u;
  const mxArray *c28_d_y = NULL;
  real_T (*c28_nu_out)[3];
  real_T (*c28_eta_out)[3];
  c28_nu_out = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c28_eta_out = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c28_st = NULL;
  c28_st = NULL;
  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_createcellarray(3), FALSE);
  for (c28_i0 = 0; c28_i0 < 3; c28_i0++) {
    c28_u[c28_i0] = (*c28_eta_out)[c28_i0];
  }

  c28_b_y = NULL;
  sf_mex_assign(&c28_b_y, sf_mex_create("y", c28_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c28_y, 0, c28_b_y);
  for (c28_i1 = 0; c28_i1 < 3; c28_i1++) {
    c28_b_u[c28_i1] = (*c28_nu_out)[c28_i1];
  }

  c28_c_y = NULL;
  sf_mex_assign(&c28_c_y, sf_mex_create("y", c28_b_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c28_y, 1, c28_c_y);
  c28_hoistedGlobal = chartInstance->c28_is_active_c28_HIL_model_overall;
  c28_c_u = c28_hoistedGlobal;
  c28_d_y = NULL;
  sf_mex_assign(&c28_d_y, sf_mex_create("y", &c28_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c28_y, 2, c28_d_y);
  sf_mex_assign(&c28_st, c28_y, FALSE);
  return c28_st;
}

static void set_sim_state_c28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance, const mxArray *c28_st)
{
  const mxArray *c28_u;
  real_T c28_dv0[3];
  int32_T c28_i2;
  real_T c28_dv1[3];
  int32_T c28_i3;
  real_T (*c28_eta_out)[3];
  real_T (*c28_nu_out)[3];
  c28_nu_out = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c28_eta_out = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c28_doneDoubleBufferReInit = TRUE;
  c28_u = sf_mex_dup(c28_st);
  c28_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c28_u, 0)),
                       "eta_out", c28_dv0);
  for (c28_i2 = 0; c28_i2 < 3; c28_i2++) {
    (*c28_eta_out)[c28_i2] = c28_dv0[c28_i2];
  }

  c28_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c28_u, 1)),
                       "nu_out", c28_dv1);
  for (c28_i3 = 0; c28_i3 < 3; c28_i3++) {
    (*c28_nu_out)[c28_i3] = c28_dv1[c28_i3];
  }

  chartInstance->c28_is_active_c28_HIL_model_overall = c28_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c28_u, 2)),
     "is_active_c28_HIL_model_overall");
  sf_mex_destroy(&c28_u);
  c28_update_debugger_state_c28_HIL_model_overall(chartInstance);
  sf_mex_destroy(&c28_st);
}

static void finalize_c28_HIL_model_overall(SFc28_HIL_model_overallInstanceStruct
  *chartInstance)
{
}

static void sf_c28_HIL_model_overall(SFc28_HIL_model_overallInstanceStruct
  *chartInstance)
{
  int32_T c28_i4;
  int32_T c28_i5;
  int32_T c28_i6;
  int32_T c28_i7;
  int32_T c28_i8;
  int32_T c28_i9;
  int32_T c28_i10;
  int32_T c28_i11;
  real_T c28_hoistedGlobal;
  real_T c28_b_hoistedGlobal;
  real_T c28_c_hoistedGlobal;
  int32_T c28_i12;
  real_T c28_eta_ini[3];
  int32_T c28_i13;
  real_T c28_nu_ini[3];
  int32_T c28_i14;
  real_T c28_eta[3];
  int32_T c28_i15;
  real_T c28_nu[3];
  int32_T c28_i16;
  real_T c28_eta_end[3];
  int32_T c28_i17;
  real_T c28_nu_end[3];
  real_T c28_time;
  real_T c28_WPi;
  real_T c28_nWP;
  uint32_T c28_debug_family_var_map[17];
  real_T c28_switchTime;
  real_T c28_switchDur;
  real_T c28_ini_gain;
  real_T c28_reg_gain;
  real_T c28_nargin = 9.0;
  real_T c28_nargout = 2.0;
  real_T c28_eta_out[3];
  real_T c28_nu_out[3];
  int32_T c28_i18;
  int32_T c28_i19;
  int32_T c28_i20;
  int32_T c28_i21;
  real_T c28_b;
  real_T c28_y;
  real_T c28_b_b;
  real_T c28_a;
  int32_T c28_i22;
  real_T c28_c_b[3];
  int32_T c28_i23;
  real_T c28_b_a;
  int32_T c28_i24;
  real_T c28_d_b[3];
  int32_T c28_i25;
  int32_T c28_i26;
  real_T c28_c_a;
  int32_T c28_i27;
  int32_T c28_i28;
  real_T c28_d_a;
  int32_T c28_i29;
  int32_T c28_i30;
  int32_T c28_i31;
  int32_T c28_i32;
  int32_T c28_i33;
  int32_T c28_i34;
  int32_T c28_i35;
  real_T *c28_b_time;
  real_T *c28_b_WPi;
  real_T *c28_b_nWP;
  real_T (*c28_b_eta_out)[3];
  real_T (*c28_b_nu_out)[3];
  real_T (*c28_b_nu_end)[3];
  real_T (*c28_b_eta_end)[3];
  real_T (*c28_b_nu)[3];
  real_T (*c28_b_eta)[3];
  real_T (*c28_b_nu_ini)[3];
  real_T (*c28_b_eta_ini)[3];
  c28_b_nWP = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
  c28_b_WPi = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c28_b_nu_out = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c28_b_time = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c28_b_nu_end = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c28_b_eta_end = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c28_b_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c28_b_eta = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c28_b_nu_ini = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c28_b_eta_out = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c28_b_eta_ini = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 21U, chartInstance->c28_sfEvent);
  for (c28_i4 = 0; c28_i4 < 3; c28_i4++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_eta_ini)[c28_i4], 0U);
  }

  for (c28_i5 = 0; c28_i5 < 3; c28_i5++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_eta_out)[c28_i5], 1U);
  }

  for (c28_i6 = 0; c28_i6 < 3; c28_i6++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_nu_ini)[c28_i6], 2U);
  }

  for (c28_i7 = 0; c28_i7 < 3; c28_i7++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_eta)[c28_i7], 3U);
  }

  for (c28_i8 = 0; c28_i8 < 3; c28_i8++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_nu)[c28_i8], 4U);
  }

  for (c28_i9 = 0; c28_i9 < 3; c28_i9++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_eta_end)[c28_i9], 5U);
  }

  for (c28_i10 = 0; c28_i10 < 3; c28_i10++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_nu_end)[c28_i10], 6U);
  }

  _SFD_DATA_RANGE_CHECK(*c28_b_time, 7U);
  for (c28_i11 = 0; c28_i11 < 3; c28_i11++) {
    _SFD_DATA_RANGE_CHECK((*c28_b_nu_out)[c28_i11], 8U);
  }

  _SFD_DATA_RANGE_CHECK(*c28_b_WPi, 9U);
  _SFD_DATA_RANGE_CHECK(*c28_b_nWP, 10U);
  chartInstance->c28_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 21U, chartInstance->c28_sfEvent);
  c28_hoistedGlobal = *c28_b_time;
  c28_b_hoistedGlobal = *c28_b_WPi;
  c28_c_hoistedGlobal = *c28_b_nWP;
  for (c28_i12 = 0; c28_i12 < 3; c28_i12++) {
    c28_eta_ini[c28_i12] = (*c28_b_eta_ini)[c28_i12];
  }

  for (c28_i13 = 0; c28_i13 < 3; c28_i13++) {
    c28_nu_ini[c28_i13] = (*c28_b_nu_ini)[c28_i13];
  }

  for (c28_i14 = 0; c28_i14 < 3; c28_i14++) {
    c28_eta[c28_i14] = (*c28_b_eta)[c28_i14];
  }

  for (c28_i15 = 0; c28_i15 < 3; c28_i15++) {
    c28_nu[c28_i15] = (*c28_b_nu)[c28_i15];
  }

  for (c28_i16 = 0; c28_i16 < 3; c28_i16++) {
    c28_eta_end[c28_i16] = (*c28_b_eta_end)[c28_i16];
  }

  for (c28_i17 = 0; c28_i17 < 3; c28_i17++) {
    c28_nu_end[c28_i17] = (*c28_b_nu_end)[c28_i17];
  }

  c28_time = c28_hoistedGlobal;
  c28_WPi = c28_b_hoistedGlobal;
  c28_nWP = c28_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 17U, 17U, c28_debug_family_names,
    c28_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c28_switchTime, 0U, c28_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c28_switchDur, 1U, c28_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c28_ini_gain, 2U, c28_b_sf_marshallOut,
    c28_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c28_reg_gain, 3U, c28_b_sf_marshallOut,
    c28_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c28_nargin, 4U, c28_b_sf_marshallOut,
    c28_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c28_nargout, 5U, c28_b_sf_marshallOut,
    c28_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c28_eta_ini, 6U, c28_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c28_nu_ini, 7U, c28_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c28_eta, 8U, c28_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c28_nu, 9U, c28_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c28_eta_end, 10U, c28_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c28_nu_end, 11U, c28_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c28_time, 12U, c28_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c28_WPi, 13U, c28_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c28_nWP, 14U, c28_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c28_eta_out, 15U, c28_sf_marshallOut,
    c28_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c28_nu_out, 16U, c28_sf_marshallOut,
    c28_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 4);
  c28_switchTime = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 5);
  c28_switchDur = 5.0;
  _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 8);
  if (CV_EML_IF(0, 1, 0, c28_WPi <= c28_nWP)) {
    _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 10);
    if (CV_EML_IF(0, 1, 1, c28_time < c28_switchTime)) {
      _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 12);
      for (c28_i18 = 0; c28_i18 < 3; c28_i18++) {
        c28_eta_out[c28_i18] = c28_eta_ini[c28_i18];
      }

      _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 13);
      for (c28_i19 = 0; c28_i19 < 3; c28_i19++) {
        c28_nu_out[c28_i19] = c28_nu_ini[c28_i19];
      }
    } else {
      _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 15);
      if (CV_EML_COND(0, 1, 0, c28_time > c28_switchTime + c28_switchDur)) {
        CV_EML_MCDC(0, 1, 0, TRUE);
        CV_EML_IF(0, 1, 2, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 17);
        for (c28_i20 = 0; c28_i20 < 3; c28_i20++) {
          c28_eta_out[c28_i20] = c28_eta[c28_i20];
        }

        _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 18);
        for (c28_i21 = 0; c28_i21 < 3; c28_i21++) {
          c28_nu_out[c28_i21] = c28_nu[c28_i21];
        }
      } else {
        CV_EML_COND(0, 1, 1, c28_switchTime + c28_switchDur == 0.0);
        CV_EML_MCDC(0, 1, 0, FALSE);
        CV_EML_IF(0, 1, 2, FALSE);
        _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 22);
        c28_b = c28_time - c28_switchTime;
        c28_y = 0.2 * c28_b;
        c28_ini_gain = 1.0 - c28_y;
        _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 23);
        c28_b_b = c28_time - c28_switchTime;
        c28_reg_gain = 0.2 * c28_b_b;
        _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 25);
        c28_a = c28_ini_gain;
        for (c28_i22 = 0; c28_i22 < 3; c28_i22++) {
          c28_c_b[c28_i22] = c28_eta_ini[c28_i22];
        }

        for (c28_i23 = 0; c28_i23 < 3; c28_i23++) {
          c28_c_b[c28_i23] *= c28_a;
        }

        c28_b_a = c28_reg_gain;
        for (c28_i24 = 0; c28_i24 < 3; c28_i24++) {
          c28_d_b[c28_i24] = c28_eta[c28_i24];
        }

        for (c28_i25 = 0; c28_i25 < 3; c28_i25++) {
          c28_d_b[c28_i25] *= c28_b_a;
        }

        for (c28_i26 = 0; c28_i26 < 3; c28_i26++) {
          c28_eta_out[c28_i26] = c28_c_b[c28_i26] + c28_d_b[c28_i26];
        }

        _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 26);
        c28_c_a = c28_ini_gain;
        for (c28_i27 = 0; c28_i27 < 3; c28_i27++) {
          c28_c_b[c28_i27] = c28_nu_ini[c28_i27];
        }

        for (c28_i28 = 0; c28_i28 < 3; c28_i28++) {
          c28_c_b[c28_i28] *= c28_c_a;
        }

        c28_d_a = c28_reg_gain;
        for (c28_i29 = 0; c28_i29 < 3; c28_i29++) {
          c28_d_b[c28_i29] = c28_nu[c28_i29];
        }

        for (c28_i30 = 0; c28_i30 < 3; c28_i30++) {
          c28_d_b[c28_i30] *= c28_d_a;
        }

        for (c28_i31 = 0; c28_i31 < 3; c28_i31++) {
          c28_nu_out[c28_i31] = c28_c_b[c28_i31] + c28_d_b[c28_i31];
        }
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 32);
    for (c28_i32 = 0; c28_i32 < 3; c28_i32++) {
      c28_eta_out[c28_i32] = c28_eta_end[c28_i32];
    }

    _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, 33);
    for (c28_i33 = 0; c28_i33 < 3; c28_i33++) {
      c28_nu_out[c28_i33] = c28_nu_end[c28_i33];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c28_sfEvent, -33);
  _SFD_SYMBOL_SCOPE_POP();
  for (c28_i34 = 0; c28_i34 < 3; c28_i34++) {
    (*c28_b_eta_out)[c28_i34] = c28_eta_out[c28_i34];
  }

  for (c28_i35 = 0; c28_i35 < 3; c28_i35++) {
    (*c28_b_nu_out)[c28_i35] = c28_nu_out[c28_i35];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c28_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HIL_model_overallMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void registerMessagesc28_HIL_model_overall
  (SFc28_HIL_model_overallInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c28_machineNumber, uint32_T
  c28_chartNumber)
{
}

static const mxArray *c28_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData)
{
  const mxArray *c28_mxArrayOutData = NULL;
  int32_T c28_i36;
  real_T c28_b_inData[3];
  int32_T c28_i37;
  real_T c28_u[3];
  const mxArray *c28_y = NULL;
  SFc28_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc28_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c28_mxArrayOutData = NULL;
  for (c28_i36 = 0; c28_i36 < 3; c28_i36++) {
    c28_b_inData[c28_i36] = (*(real_T (*)[3])c28_inData)[c28_i36];
  }

  for (c28_i37 = 0; c28_i37 < 3; c28_i37++) {
    c28_u[c28_i37] = c28_b_inData[c28_i37];
  }

  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_create("y", c28_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c28_mxArrayOutData, c28_y, FALSE);
  return c28_mxArrayOutData;
}

static void c28_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_nu_out, const char_T *c28_identifier,
  real_T c28_y[3])
{
  emlrtMsgIdentifier c28_thisId;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c28_nu_out), &c28_thisId,
    c28_y);
  sf_mex_destroy(&c28_nu_out);
}

static void c28_b_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId,
  real_T c28_y[3])
{
  real_T c28_dv2[3];
  int32_T c28_i38;
  sf_mex_import(c28_parentId, sf_mex_dup(c28_u), c28_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c28_i38 = 0; c28_i38 < 3; c28_i38++) {
    c28_y[c28_i38] = c28_dv2[c28_i38];
  }

  sf_mex_destroy(&c28_u);
}

static void c28_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData)
{
  const mxArray *c28_nu_out;
  const char_T *c28_identifier;
  emlrtMsgIdentifier c28_thisId;
  real_T c28_y[3];
  int32_T c28_i39;
  SFc28_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc28_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c28_nu_out = sf_mex_dup(c28_mxArrayInData);
  c28_identifier = c28_varName;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c28_nu_out), &c28_thisId,
    c28_y);
  sf_mex_destroy(&c28_nu_out);
  for (c28_i39 = 0; c28_i39 < 3; c28_i39++) {
    (*(real_T (*)[3])c28_outData)[c28_i39] = c28_y[c28_i39];
  }

  sf_mex_destroy(&c28_mxArrayInData);
}

static const mxArray *c28_b_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData)
{
  const mxArray *c28_mxArrayOutData = NULL;
  real_T c28_u;
  const mxArray *c28_y = NULL;
  SFc28_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc28_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c28_mxArrayOutData = NULL;
  c28_u = *(real_T *)c28_inData;
  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_create("y", &c28_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c28_mxArrayOutData, c28_y, FALSE);
  return c28_mxArrayOutData;
}

static real_T c28_c_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId)
{
  real_T c28_y;
  real_T c28_d0;
  sf_mex_import(c28_parentId, sf_mex_dup(c28_u), &c28_d0, 1, 0, 0U, 0, 0U, 0);
  c28_y = c28_d0;
  sf_mex_destroy(&c28_u);
  return c28_y;
}

static void c28_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData)
{
  const mxArray *c28_nargout;
  const char_T *c28_identifier;
  emlrtMsgIdentifier c28_thisId;
  real_T c28_y;
  SFc28_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc28_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c28_nargout = sf_mex_dup(c28_mxArrayInData);
  c28_identifier = c28_varName;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_y = c28_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c28_nargout),
    &c28_thisId);
  sf_mex_destroy(&c28_nargout);
  *(real_T *)c28_outData = c28_y;
  sf_mex_destroy(&c28_mxArrayInData);
}

const mxArray *sf_c28_HIL_model_overall_get_eml_resolved_functions_info(void)
{
  const mxArray *c28_nameCaptureInfo;
  c28_ResolvedFunctionInfo c28_info[5];
  c28_ResolvedFunctionInfo (*c28_b_info)[5];
  const mxArray *c28_m0 = NULL;
  int32_T c28_i40;
  c28_ResolvedFunctionInfo *c28_r0;
  c28_nameCaptureInfo = NULL;
  c28_nameCaptureInfo = NULL;
  c28_b_info = (c28_ResolvedFunctionInfo (*)[5])c28_info;
  (*c28_b_info)[0].context = "";
  (*c28_b_info)[0].name = "mrdivide";
  (*c28_b_info)[0].dominantType = "double";
  (*c28_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c28_b_info)[0].fileTimeLo = 1357951548U;
  (*c28_b_info)[0].fileTimeHi = 0U;
  (*c28_b_info)[0].mFileTimeLo = 1319729966U;
  (*c28_b_info)[0].mFileTimeHi = 0U;
  (*c28_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c28_b_info)[1].name = "rdivide";
  (*c28_b_info)[1].dominantType = "double";
  (*c28_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c28_b_info)[1].fileTimeLo = 1346510388U;
  (*c28_b_info)[1].fileTimeHi = 0U;
  (*c28_b_info)[1].mFileTimeLo = 0U;
  (*c28_b_info)[1].mFileTimeHi = 0U;
  (*c28_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c28_b_info)[2].name = "eml_scalexp_compatible";
  (*c28_b_info)[2].dominantType = "double";
  (*c28_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  (*c28_b_info)[2].fileTimeLo = 1286818796U;
  (*c28_b_info)[2].fileTimeHi = 0U;
  (*c28_b_info)[2].mFileTimeLo = 0U;
  (*c28_b_info)[2].mFileTimeHi = 0U;
  (*c28_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c28_b_info)[3].name = "eml_div";
  (*c28_b_info)[3].dominantType = "double";
  (*c28_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c28_b_info)[3].fileTimeLo = 1313347810U;
  (*c28_b_info)[3].fileTimeHi = 0U;
  (*c28_b_info)[3].mFileTimeLo = 0U;
  (*c28_b_info)[3].mFileTimeHi = 0U;
  (*c28_b_info)[4].context = "";
  (*c28_b_info)[4].name = "mtimes";
  (*c28_b_info)[4].dominantType = "double";
  (*c28_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c28_b_info)[4].fileTimeLo = 1289519692U;
  (*c28_b_info)[4].fileTimeHi = 0U;
  (*c28_b_info)[4].mFileTimeLo = 0U;
  (*c28_b_info)[4].mFileTimeHi = 0U;
  sf_mex_assign(&c28_m0, sf_mex_createstruct("nameCaptureInfo", 1, 5), FALSE);
  for (c28_i40 = 0; c28_i40 < 5; c28_i40++) {
    c28_r0 = &c28_info[c28_i40];
    sf_mex_addfield(c28_m0, sf_mex_create("nameCaptureInfo", c28_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c28_r0->context)), "context", "nameCaptureInfo",
                    c28_i40);
    sf_mex_addfield(c28_m0, sf_mex_create("nameCaptureInfo", c28_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c28_r0->name)), "name", "nameCaptureInfo",
                    c28_i40);
    sf_mex_addfield(c28_m0, sf_mex_create("nameCaptureInfo",
      c28_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c28_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c28_i40);
    sf_mex_addfield(c28_m0, sf_mex_create("nameCaptureInfo", c28_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c28_r0->resolved)), "resolved",
                    "nameCaptureInfo", c28_i40);
    sf_mex_addfield(c28_m0, sf_mex_create("nameCaptureInfo", &c28_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c28_i40);
    sf_mex_addfield(c28_m0, sf_mex_create("nameCaptureInfo", &c28_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c28_i40);
    sf_mex_addfield(c28_m0, sf_mex_create("nameCaptureInfo",
      &c28_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c28_i40);
    sf_mex_addfield(c28_m0, sf_mex_create("nameCaptureInfo",
      &c28_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c28_i40);
  }

  sf_mex_assign(&c28_nameCaptureInfo, c28_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c28_nameCaptureInfo);
  return c28_nameCaptureInfo;
}

static const mxArray *c28_c_sf_marshallOut(void *chartInstanceVoid, void
  *c28_inData)
{
  const mxArray *c28_mxArrayOutData = NULL;
  int32_T c28_u;
  const mxArray *c28_y = NULL;
  SFc28_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc28_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c28_mxArrayOutData = NULL;
  c28_u = *(int32_T *)c28_inData;
  c28_y = NULL;
  sf_mex_assign(&c28_y, sf_mex_create("y", &c28_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c28_mxArrayOutData, c28_y, FALSE);
  return c28_mxArrayOutData;
}

static int32_T c28_d_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId)
{
  int32_T c28_y;
  int32_T c28_i41;
  sf_mex_import(c28_parentId, sf_mex_dup(c28_u), &c28_i41, 1, 6, 0U, 0, 0U, 0);
  c28_y = c28_i41;
  sf_mex_destroy(&c28_u);
  return c28_y;
}

static void c28_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c28_mxArrayInData, const char_T *c28_varName, void *c28_outData)
{
  const mxArray *c28_b_sfEvent;
  const char_T *c28_identifier;
  emlrtMsgIdentifier c28_thisId;
  int32_T c28_y;
  SFc28_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc28_HIL_model_overallInstanceStruct *)chartInstanceVoid;
  c28_b_sfEvent = sf_mex_dup(c28_mxArrayInData);
  c28_identifier = c28_varName;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_y = c28_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c28_b_sfEvent),
    &c28_thisId);
  sf_mex_destroy(&c28_b_sfEvent);
  *(int32_T *)c28_outData = c28_y;
  sf_mex_destroy(&c28_mxArrayInData);
}

static uint8_T c28_e_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_b_is_active_c28_HIL_model_overall, const
  char_T *c28_identifier)
{
  uint8_T c28_y;
  emlrtMsgIdentifier c28_thisId;
  c28_thisId.fIdentifier = c28_identifier;
  c28_thisId.fParent = NULL;
  c28_y = c28_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c28_b_is_active_c28_HIL_model_overall), &c28_thisId);
  sf_mex_destroy(&c28_b_is_active_c28_HIL_model_overall);
  return c28_y;
}

static uint8_T c28_f_emlrt_marshallIn(SFc28_HIL_model_overallInstanceStruct
  *chartInstance, const mxArray *c28_u, const emlrtMsgIdentifier *c28_parentId)
{
  uint8_T c28_y;
  uint8_T c28_u0;
  sf_mex_import(c28_parentId, sf_mex_dup(c28_u), &c28_u0, 1, 3, 0U, 0, 0U, 0);
  c28_y = c28_u0;
  sf_mex_destroy(&c28_u);
  return c28_y;
}

static void init_dsm_address_info(SFc28_HIL_model_overallInstanceStruct
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

void sf_c28_HIL_model_overall_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2589640527U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4049006658U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(91790886U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1534388908U);
}

mxArray *sf_c28_HIL_model_overall_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("SSTmexydsysmTRJLoEOgJG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,9,3,dataFields);

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
      pr[0] = (double)(3);
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
      pr[0] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));
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

mxArray *sf_c28_HIL_model_overall_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c28_HIL_model_overall(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"eta_out\",},{M[1],M[10],T\"nu_out\",},{M[8],M[0],T\"is_active_c28_HIL_model_overall\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c28_HIL_model_overall_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc28_HIL_model_overallInstanceStruct *chartInstance;
    chartInstance = (SFc28_HIL_model_overallInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HIL_model_overallMachineNumber_,
           28,
           1,
           1,
           11,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"eta_ini");
          _SFD_SET_DATA_PROPS(1,2,0,1,"eta_out");
          _SFD_SET_DATA_PROPS(2,1,1,0,"nu_ini");
          _SFD_SET_DATA_PROPS(3,1,1,0,"eta");
          _SFD_SET_DATA_PROPS(4,1,1,0,"nu");
          _SFD_SET_DATA_PROPS(5,1,1,0,"eta_end");
          _SFD_SET_DATA_PROPS(6,1,1,0,"nu_end");
          _SFD_SET_DATA_PROPS(7,1,1,0,"time");
          _SFD_SET_DATA_PROPS(8,2,0,1,"nu_out");
          _SFD_SET_DATA_PROPS(9,1,1,0,"WPi");
          _SFD_SET_DATA_PROPS(10,1,1,0,"nWP");
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
        _SFD_CV_INIT_EML(0,1,1,3,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,740);
        _SFD_CV_INIT_EML_IF(0,1,0,218,231,678,740);
        _SFD_CV_INIT_EML_IF(0,1,1,237,257,316,672);
        _SFD_CV_INIT_EML_IF(0,1,2,316,383,434,672);

        {
          static int condStart[] = { 323, 356 };

          static int condEnd[] = { 352, 383 };

          static int pfixExpr[] = { 0, 1, -2 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,323,383,2,0,&(condStart[0]),&(condEnd[0]),
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
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)
            c28_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c28_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c28_sf_marshallOut,(MexInFcnForType)
            c28_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c28_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c28_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c28_time;
          real_T *c28_WPi;
          real_T *c28_nWP;
          real_T (*c28_eta_ini)[3];
          real_T (*c28_eta_out)[3];
          real_T (*c28_nu_ini)[3];
          real_T (*c28_eta)[3];
          real_T (*c28_nu)[3];
          real_T (*c28_eta_end)[3];
          real_T (*c28_nu_end)[3];
          real_T (*c28_nu_out)[3];
          c28_nWP = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
          c28_WPi = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
          c28_nu_out = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c28_time = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c28_nu_end = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
          c28_eta_end = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c28_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c28_eta = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c28_nu_ini = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c28_eta_out = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c28_eta_ini = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c28_eta_ini);
          _SFD_SET_DATA_VALUE_PTR(1U, *c28_eta_out);
          _SFD_SET_DATA_VALUE_PTR(2U, *c28_nu_ini);
          _SFD_SET_DATA_VALUE_PTR(3U, *c28_eta);
          _SFD_SET_DATA_VALUE_PTR(4U, *c28_nu);
          _SFD_SET_DATA_VALUE_PTR(5U, *c28_eta_end);
          _SFD_SET_DATA_VALUE_PTR(6U, *c28_nu_end);
          _SFD_SET_DATA_VALUE_PTR(7U, c28_time);
          _SFD_SET_DATA_VALUE_PTR(8U, *c28_nu_out);
          _SFD_SET_DATA_VALUE_PTR(9U, c28_WPi);
          _SFD_SET_DATA_VALUE_PTR(10U, c28_nWP);
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
  return "je2Gmq1bf80hBBypf9zjpB";
}

static void sf_opaque_initialize_c28_HIL_model_overall(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc28_HIL_model_overallInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c28_HIL_model_overall((SFc28_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
  initialize_c28_HIL_model_overall((SFc28_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c28_HIL_model_overall(void *chartInstanceVar)
{
  enable_c28_HIL_model_overall((SFc28_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c28_HIL_model_overall(void *chartInstanceVar)
{
  disable_c28_HIL_model_overall((SFc28_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c28_HIL_model_overall(void *chartInstanceVar)
{
  sf_c28_HIL_model_overall((SFc28_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c28_HIL_model_overall(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c28_HIL_model_overall
    ((SFc28_HIL_model_overallInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c28_HIL_model_overall();/* state var info */
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

extern void sf_internal_set_sim_state_c28_HIL_model_overall(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c28_HIL_model_overall();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c28_HIL_model_overall((SFc28_HIL_model_overallInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c28_HIL_model_overall(SimStruct* S)
{
  return sf_internal_get_sim_state_c28_HIL_model_overall(S);
}

static void sf_opaque_set_sim_state_c28_HIL_model_overall(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c28_HIL_model_overall(S, st);
}

static void sf_opaque_terminate_c28_HIL_model_overall(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc28_HIL_model_overallInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HIL_model_overall_optimization_info();
    }

    finalize_c28_HIL_model_overall((SFc28_HIL_model_overallInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc28_HIL_model_overall((SFc28_HIL_model_overallInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c28_HIL_model_overall(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c28_HIL_model_overall
      ((SFc28_HIL_model_overallInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c28_HIL_model_overall(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HIL_model_overall_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      28);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,28,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,28,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,28);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,28,9);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,28,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 9; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,28);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2543783442U));
  ssSetChecksum1(S,(2324665440U));
  ssSetChecksum2(S,(441531230U));
  ssSetChecksum3(S,(2553681747U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c28_HIL_model_overall(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c28_HIL_model_overall(SimStruct *S)
{
  SFc28_HIL_model_overallInstanceStruct *chartInstance;
  chartInstance = (SFc28_HIL_model_overallInstanceStruct *)utMalloc(sizeof
    (SFc28_HIL_model_overallInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc28_HIL_model_overallInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c28_HIL_model_overall;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c28_HIL_model_overall;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c28_HIL_model_overall;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c28_HIL_model_overall;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c28_HIL_model_overall;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c28_HIL_model_overall;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c28_HIL_model_overall;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c28_HIL_model_overall;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c28_HIL_model_overall;
  chartInstance->chartInfo.mdlStart = mdlStart_c28_HIL_model_overall;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c28_HIL_model_overall;
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

void c28_HIL_model_overall_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c28_HIL_model_overall(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c28_HIL_model_overall(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c28_HIL_model_overall(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c28_HIL_model_overall_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
