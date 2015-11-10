/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CSE1_Oculus_gesture_sfun.h"
#include "c13_CSE1_Oculus_gesture.h"
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
static const char * c13_debug_family_names[7] = { "nargin", "nargout",
  "switch_signal", "ctrl_student", "ctrl_DP_basic", "ctrl_sixaxis2force",
  "ctrl_sixaxis2thruster" };

/* Function Declarations */
static void initialize_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void initialize_params_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void enable_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void disable_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void c13_update_debugger_state_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void set_sim_state_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance, const mxArray *c13_st);
static void finalize_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void sf_gateway_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void initSimStructsc13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber, uint32_T c13_instanceNumber);
static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static boolean_T c13_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_ctrl_sixaxis2thruster, const char_T
  *c13_identifier);
static boolean_T c13_b_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static real_T c13_c_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static int32_T c13_d_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static uint8_T c13_e_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_b_is_active_c13_CSE1_Oculus_gesture, const
  char_T *c13_identifier);
static uint8_T c13_f_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void init_dsm_address_info(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  chartInstance->c13_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c13_is_active_c13_CSE1_Oculus_gesture = 0U;
}

static void initialize_params_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c13_update_debugger_state_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  const mxArray *c13_st;
  const mxArray *c13_y = NULL;
  boolean_T c13_hoistedGlobal;
  boolean_T c13_u;
  const mxArray *c13_b_y = NULL;
  boolean_T c13_b_hoistedGlobal;
  boolean_T c13_b_u;
  const mxArray *c13_c_y = NULL;
  boolean_T c13_c_hoistedGlobal;
  boolean_T c13_c_u;
  const mxArray *c13_d_y = NULL;
  boolean_T c13_d_hoistedGlobal;
  boolean_T c13_d_u;
  const mxArray *c13_e_y = NULL;
  uint8_T c13_e_hoistedGlobal;
  uint8_T c13_e_u;
  const mxArray *c13_f_y = NULL;
  boolean_T *c13_ctrl_DP_basic;
  boolean_T *c13_ctrl_sixaxis2force;
  boolean_T *c13_ctrl_sixaxis2thruster;
  boolean_T *c13_ctrl_student;
  c13_ctrl_sixaxis2thruster = (boolean_T *)ssGetOutputPortSignal
    (chartInstance->S, 4);
  c13_ctrl_sixaxis2force = (boolean_T *)ssGetOutputPortSignal(chartInstance->S,
    3);
  c13_ctrl_DP_basic = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c13_ctrl_student = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c13_st = NULL;
  c13_st = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_createcellmatrix(5, 1), false);
  c13_hoistedGlobal = *c13_ctrl_DP_basic;
  c13_u = c13_hoistedGlobal;
  c13_b_y = NULL;
  sf_mex_assign(&c13_b_y, sf_mex_create("y", &c13_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c13_y, 0, c13_b_y);
  c13_b_hoistedGlobal = *c13_ctrl_sixaxis2force;
  c13_b_u = c13_b_hoistedGlobal;
  c13_c_y = NULL;
  sf_mex_assign(&c13_c_y, sf_mex_create("y", &c13_b_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c13_y, 1, c13_c_y);
  c13_c_hoistedGlobal = *c13_ctrl_sixaxis2thruster;
  c13_c_u = c13_c_hoistedGlobal;
  c13_d_y = NULL;
  sf_mex_assign(&c13_d_y, sf_mex_create("y", &c13_c_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c13_y, 2, c13_d_y);
  c13_d_hoistedGlobal = *c13_ctrl_student;
  c13_d_u = c13_d_hoistedGlobal;
  c13_e_y = NULL;
  sf_mex_assign(&c13_e_y, sf_mex_create("y", &c13_d_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c13_y, 3, c13_e_y);
  c13_e_hoistedGlobal = chartInstance->c13_is_active_c13_CSE1_Oculus_gesture;
  c13_e_u = c13_e_hoistedGlobal;
  c13_f_y = NULL;
  sf_mex_assign(&c13_f_y, sf_mex_create("y", &c13_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c13_y, 4, c13_f_y);
  sf_mex_assign(&c13_st, c13_y, false);
  return c13_st;
}

static void set_sim_state_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance, const mxArray *c13_st)
{
  const mxArray *c13_u;
  boolean_T *c13_ctrl_DP_basic;
  boolean_T *c13_ctrl_sixaxis2force;
  boolean_T *c13_ctrl_sixaxis2thruster;
  boolean_T *c13_ctrl_student;
  c13_ctrl_sixaxis2thruster = (boolean_T *)ssGetOutputPortSignal
    (chartInstance->S, 4);
  c13_ctrl_sixaxis2force = (boolean_T *)ssGetOutputPortSignal(chartInstance->S,
    3);
  c13_ctrl_DP_basic = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c13_ctrl_student = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c13_doneDoubleBufferReInit = true;
  c13_u = sf_mex_dup(c13_st);
  *c13_ctrl_DP_basic = c13_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c13_u, 0)), "ctrl_DP_basic");
  *c13_ctrl_sixaxis2force = c13_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c13_u, 1)), "ctrl_sixaxis2force");
  *c13_ctrl_sixaxis2thruster = c13_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c13_u, 2)), "ctrl_sixaxis2thruster");
  *c13_ctrl_student = c13_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c13_u, 3)), "ctrl_student");
  chartInstance->c13_is_active_c13_CSE1_Oculus_gesture = c13_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 4)),
     "is_active_c13_CSE1_Oculus_gesture");
  sf_mex_destroy(&c13_u);
  c13_update_debugger_state_c13_CSE1_Oculus_gesture(chartInstance);
  sf_mex_destroy(&c13_st);
}

static void finalize_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
{
  real_T c13_hoistedGlobal;
  real_T c13_switch_signal;
  uint32_T c13_debug_family_var_map[7];
  real_T c13_nargin = 1.0;
  real_T c13_nargout = 4.0;
  boolean_T c13_ctrl_student;
  boolean_T c13_ctrl_DP_basic;
  boolean_T c13_ctrl_sixaxis2force;
  boolean_T c13_ctrl_sixaxis2thruster;
  real_T *c13_b_switch_signal;
  boolean_T *c13_b_ctrl_student;
  boolean_T *c13_b_ctrl_DP_basic;
  boolean_T *c13_b_ctrl_sixaxis2force;
  boolean_T *c13_b_ctrl_sixaxis2thruster;
  c13_b_ctrl_sixaxis2thruster = (boolean_T *)ssGetOutputPortSignal
    (chartInstance->S, 4);
  c13_b_ctrl_sixaxis2force = (boolean_T *)ssGetOutputPortSignal(chartInstance->S,
    3);
  c13_b_ctrl_DP_basic = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c13_b_ctrl_student = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c13_b_switch_signal = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c13_b_switch_signal, 0U);
  chartInstance->c13_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  c13_hoistedGlobal = *c13_b_switch_signal;
  c13_switch_signal = c13_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c13_debug_family_names,
    c13_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargin, 0U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargout, 1U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_switch_signal, 2U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_ctrl_student, 3U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_ctrl_DP_basic, 4U,
    c13_sf_marshallOut, c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_ctrl_sixaxis2force, 5U,
    c13_sf_marshallOut, c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_ctrl_sixaxis2thruster, 6U,
    c13_sf_marshallOut, c13_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 3);
  c13_ctrl_sixaxis2thruster = false;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 4);
  c13_ctrl_sixaxis2force = false;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 5);
  c13_ctrl_DP_basic = false;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 6);
  c13_ctrl_student = false;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 8);
  if (CV_EML_IF(0, 1, 0, c13_switch_signal == 1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 9);
    c13_ctrl_student = true;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 10);
    if (CV_EML_IF(0, 1, 1, c13_switch_signal == 2.0)) {
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 11);
      c13_ctrl_sixaxis2force = true;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 12);
      if (CV_EML_IF(0, 1, 2, c13_switch_signal == 3.0)) {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 13);
        c13_ctrl_DP_basic = true;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 14);
        if (CV_EML_IF(0, 1, 3, c13_switch_signal == 4.0)) {
          _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 15);
          c13_ctrl_sixaxis2thruster = true;
        }
      }
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, -15);
  _SFD_SYMBOL_SCOPE_POP();
  *c13_b_ctrl_student = c13_ctrl_student;
  *c13_b_ctrl_DP_basic = c13_ctrl_DP_basic;
  *c13_b_ctrl_sixaxis2force = c13_ctrl_sixaxis2force;
  *c13_b_ctrl_sixaxis2thruster = c13_ctrl_sixaxis2thruster;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c13_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CSE1_Oculus_gestureMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK((real_T)*c13_b_ctrl_student, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c13_b_ctrl_DP_basic, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c13_b_ctrl_sixaxis2force, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*c13_b_ctrl_sixaxis2thruster, 4U);
}

static void initSimStructsc13_CSE1_Oculus_gesture
  (SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance)
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
  boolean_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(boolean_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, false);
  return c13_mxArrayOutData;
}

static boolean_T c13_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_ctrl_sixaxis2thruster, const char_T
  *c13_identifier)
{
  boolean_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_ctrl_sixaxis2thruster), &c13_thisId);
  sf_mex_destroy(&c13_ctrl_sixaxis2thruster);
  return c13_y;
}

static boolean_T c13_b_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct *
  chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  boolean_T c13_y;
  boolean_T c13_b0;
  (void)chartInstance;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_b0, 1, 11, 0U, 0, 0U, 0);
  c13_y = c13_b0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_ctrl_sixaxis2thruster;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  boolean_T c13_y;
  SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c13_ctrl_sixaxis2thruster = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_ctrl_sixaxis2thruster), &c13_thisId);
  sf_mex_destroy(&c13_ctrl_sixaxis2thruster);
  *(boolean_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  real_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(real_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, false);
  return c13_mxArrayOutData;
}

static real_T c13_c_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  real_T c13_y;
  real_T c13_d0;
  (void)chartInstance;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_d0, 1, 0, 0U, 0, 0U, 0);
  c13_y = c13_d0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_nargout;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y;
  SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c13_nargout = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_nargout),
    &c13_thisId);
  sf_mex_destroy(&c13_nargout);
  *(real_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

const mxArray *sf_c13_CSE1_Oculus_gesture_get_eml_resolved_functions_info(void)
{
  const mxArray *c13_nameCaptureInfo = NULL;
  c13_nameCaptureInfo = NULL;
  sf_mex_assign(&c13_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c13_nameCaptureInfo;
}

static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(int32_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, false);
  return c13_mxArrayOutData;
}

static int32_T c13_d_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  int32_T c13_y;
  int32_T c13_i0;
  (void)chartInstance;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_i0, 1, 6, 0U, 0, 0U, 0);
  c13_y = c13_i0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_b_sfEvent;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  int32_T c13_y;
  SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  chartInstance = (SFc13_CSE1_Oculus_gestureInstanceStruct *)chartInstanceVoid;
  c13_b_sfEvent = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_b_sfEvent),
    &c13_thisId);
  sf_mex_destroy(&c13_b_sfEvent);
  *(int32_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static uint8_T c13_e_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_b_is_active_c13_CSE1_Oculus_gesture, const
  char_T *c13_identifier)
{
  uint8_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_b_is_active_c13_CSE1_Oculus_gesture), &c13_thisId);
  sf_mex_destroy(&c13_b_is_active_c13_CSE1_Oculus_gesture);
  return c13_y;
}

static uint8_T c13_f_emlrt_marshallIn(SFc13_CSE1_Oculus_gestureInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  uint8_T c13_y;
  uint8_T c13_u0;
  (void)chartInstance;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_u0, 1, 3, 0U, 0, 0U, 0);
  c13_y = c13_u0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void init_dsm_address_info(SFc13_CSE1_Oculus_gestureInstanceStruct
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

void sf_c13_CSE1_Oculus_gesture_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3996351402U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3486839177U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1379718416U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3182576854U);
}

mxArray *sf_c13_CSE1_Oculus_gesture_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("163DM3nPJIkrqcuyUS9UNF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c13_CSE1_Oculus_gesture_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c13_CSE1_Oculus_gesture_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c13_CSE1_Oculus_gesture(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[6],T\"ctrl_DP_basic\",},{M[1],M[7],T\"ctrl_sixaxis2force\",},{M[1],M[8],T\"ctrl_sixaxis2thruster\",},{M[1],M[5],T\"ctrl_student\",},{M[8],M[0],T\"is_active_c13_CSE1_Oculus_gesture\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c13_CSE1_Oculus_gesture_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc13_CSE1_Oculus_gestureInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CSE1_Oculus_gestureMachineNumber_,
           13,
           1,
           1,
           0,
           5,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"switch_signal");
          _SFD_SET_DATA_PROPS(1,2,0,1,"ctrl_student");
          _SFD_SET_DATA_PROPS(2,2,0,1,"ctrl_DP_basic");
          _SFD_SET_DATA_PROPS(3,2,0,1,"ctrl_sixaxis2force");
          _SFD_SET_DATA_PROPS(4,2,0,1,"ctrl_sixaxis2thruster");
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
        _SFD_CV_INIT_EML(0,1,1,4,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,482);
        _SFD_CV_INIT_EML_IF(0,1,0,225,250,286,481);
        _SFD_CV_INIT_EML_IF(0,1,1,286,311,347,481);
        _SFD_CV_INIT_EML_IF(0,1,2,347,372,408,481);
        _SFD_CV_INIT_EML_IF(0,1,3,408,433,468,481);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)c13_sf_marshallIn);

        {
          real_T *c13_switch_signal;
          boolean_T *c13_ctrl_student;
          boolean_T *c13_ctrl_DP_basic;
          boolean_T *c13_ctrl_sixaxis2force;
          boolean_T *c13_ctrl_sixaxis2thruster;
          c13_ctrl_sixaxis2thruster = (boolean_T *)ssGetOutputPortSignal
            (chartInstance->S, 4);
          c13_ctrl_sixaxis2force = (boolean_T *)ssGetOutputPortSignal
            (chartInstance->S, 3);
          c13_ctrl_DP_basic = (boolean_T *)ssGetOutputPortSignal
            (chartInstance->S, 2);
          c13_ctrl_student = (boolean_T *)ssGetOutputPortSignal(chartInstance->S,
            1);
          c13_switch_signal = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c13_switch_signal);
          _SFD_SET_DATA_VALUE_PTR(1U, c13_ctrl_student);
          _SFD_SET_DATA_VALUE_PTR(2U, c13_ctrl_DP_basic);
          _SFD_SET_DATA_VALUE_PTR(3U, c13_ctrl_sixaxis2force);
          _SFD_SET_DATA_VALUE_PTR(4U, c13_ctrl_sixaxis2thruster);
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
  return "eF2g0FaS14oX9SjDf8B1DE";
}

static void sf_opaque_initialize_c13_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc13_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c13_CSE1_Oculus_gesture
    ((SFc13_CSE1_Oculus_gestureInstanceStruct*) chartInstanceVar);
  initialize_c13_CSE1_Oculus_gesture((SFc13_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c13_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  enable_c13_CSE1_Oculus_gesture((SFc13_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c13_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  disable_c13_CSE1_Oculus_gesture((SFc13_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c13_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  sf_gateway_c13_CSE1_Oculus_gesture((SFc13_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c13_CSE1_Oculus_gesture
  (SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c13_CSE1_Oculus_gesture
    ((SFc13_CSE1_Oculus_gestureInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_CSE1_Oculus_gesture();/* state var info */
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

extern void sf_internal_set_sim_state_c13_CSE1_Oculus_gesture(SimStruct* S,
  const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c13_CSE1_Oculus_gesture();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c13_CSE1_Oculus_gesture((SFc13_CSE1_Oculus_gestureInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c13_CSE1_Oculus_gesture(SimStruct*
  S)
{
  return sf_internal_get_sim_state_c13_CSE1_Oculus_gesture(S);
}

static void sf_opaque_set_sim_state_c13_CSE1_Oculus_gesture(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c13_CSE1_Oculus_gesture(S, st);
}

static void sf_opaque_terminate_c13_CSE1_Oculus_gesture(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc13_CSE1_Oculus_gestureInstanceStruct*) chartInstanceVar
      )->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CSE1_Oculus_gesture_optimization_info();
    }

    finalize_c13_CSE1_Oculus_gesture((SFc13_CSE1_Oculus_gestureInstanceStruct*)
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
  initSimStructsc13_CSE1_Oculus_gesture((SFc13_CSE1_Oculus_gestureInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c13_CSE1_Oculus_gesture(SimStruct *S)
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
    initialize_params_c13_CSE1_Oculus_gesture
      ((SFc13_CSE1_Oculus_gestureInstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c13_CSE1_Oculus_gesture(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CSE1_Oculus_gesture_optimization_info();
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,13,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,13,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,13);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(995678742U));
  ssSetChecksum1(S,(2434277172U));
  ssSetChecksum2(S,(527245971U));
  ssSetChecksum3(S,(3325611902U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c13_CSE1_Oculus_gesture(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c13_CSE1_Oculus_gesture(SimStruct *S)
{
  SFc13_CSE1_Oculus_gestureInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc13_CSE1_Oculus_gestureInstanceStruct *)utMalloc(sizeof
    (SFc13_CSE1_Oculus_gestureInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc13_CSE1_Oculus_gestureInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.mdlStart = mdlStart_c13_CSE1_Oculus_gesture;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c13_CSE1_Oculus_gesture;
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

void c13_CSE1_Oculus_gesture_method_dispatcher(SimStruct *S, int_T method, void *
  data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c13_CSE1_Oculus_gesture(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c13_CSE1_Oculus_gesture(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c13_CSE1_Oculus_gesture(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c13_CSE1_Oculus_gesture_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
