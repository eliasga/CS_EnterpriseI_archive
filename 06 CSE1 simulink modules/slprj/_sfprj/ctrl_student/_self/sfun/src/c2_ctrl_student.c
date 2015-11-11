/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ctrl_student_sfun.h"
#include "c2_ctrl_student.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ctrl_student_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[12] = { "u_BT", "u_VSP1", "u_VSP2",
  "alpha_VSP1", "alpha_VSP2", "omega_VSP1", "omega_VSP2", "OK", "nargin",
  "nargout", "u", "fault" };

/* Function Declarations */
static void initialize_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance);
static void initialize_params_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance);
static void enable_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance);
static void disable_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_ctrl_student
  (SFc2_ctrl_studentInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_ctrl_student
  (SFc2_ctrl_studentInstanceStruct *chartInstance);
static void set_sim_state_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance);
static void sf_gateway_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance);
static void initSimStructsc2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static boolean_T c2_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_fault, const char_T *c2_identifier);
static boolean_T c2_b_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_d_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_e_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_ctrl_student, const char_T
  *c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_ctrl_studentInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_ctrl_student = 0U;
}

static void initialize_params_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_ctrl_student
  (SFc2_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_ctrl_student
  (SFc2_ctrl_studentInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  boolean_T c2_hoistedGlobal;
  boolean_T c2_u;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  boolean_T *c2_fault;
  c2_fault = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  c2_hoistedGlobal = *c2_fault;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_active_c2_ctrl_student;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  boolean_T *c2_fault;
  c2_fault = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  *c2_fault = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u,
    0)), "fault");
  chartInstance->c2_is_active_c2_ctrl_student = c2_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_ctrl_student");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_ctrl_student(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance)
{
  int32_T c2_i0;
  int32_T c2_i1;
  real_T c2_u[7];
  uint32_T c2_debug_family_var_map[12];
  real_T c2_u_BT;
  real_T c2_u_VSP1;
  real_T c2_u_VSP2;
  real_T c2_alpha_VSP1;
  real_T c2_alpha_VSP2;
  real_T c2_omega_VSP1;
  real_T c2_omega_VSP2;
  boolean_T c2_OK;
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  boolean_T c2_fault;
  boolean_T c2_b0;
  boolean_T c2_b1;
  boolean_T c2_b2;
  boolean_T c2_b3;
  boolean_T c2_b4;
  boolean_T c2_b5;
  boolean_T c2_b6;
  boolean_T c2_b7;
  boolean_T c2_b8;
  boolean_T c2_b9;
  boolean_T c2_b10;
  boolean_T c2_b11;
  boolean_T c2_b12;
  boolean_T c2_b13;
  boolean_T c2_b14;
  boolean_T c2_b15;
  boolean_T c2_b16;
  boolean_T c2_b17;
  boolean_T c2_b18;
  boolean_T c2_b19;
  boolean_T c2_b20;
  boolean_T c2_b21;
  boolean_T c2_b22;
  boolean_T c2_b23;
  boolean_T c2_b24;
  boolean_T c2_b25;
  boolean_T *c2_b_fault;
  real_T (*c2_b_u)[7];
  c2_b_fault = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_u = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i0 = 0; c2_i0 < 7; c2_i0++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_u)[c2_i0], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i1 = 0; c2_i1 < 7; c2_i1++) {
    c2_u[c2_i1] = (*c2_b_u)[c2_i1];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_u_BT, 0U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_u_VSP1, 1U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_u_VSP2, 2U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_VSP1, 3U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_VSP2, 4U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_omega_VSP1, 5U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_omega_VSP2, 6U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_OK, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 8U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 9U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_u, 10U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_fault, 11U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 2);
  c2_u_BT = c2_u[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  c2_u_VSP1 = c2_u[1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_u_VSP2 = c2_u[2];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_alpha_VSP1 = c2_u[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_alpha_VSP2 = c2_u[4];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_omega_VSP1 = c2_u[5];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_omega_VSP2 = c2_u[6];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  c2_b0 = (-1.0 <= c2_u_BT);
  c2_b1 = (c2_u_BT <= 1.0);
  c2_b2 = (c2_b0 && c2_b1);
  c2_b3 = (0.0 <= c2_u_VSP1);
  c2_b4 = (c2_b2 && c2_b3);
  c2_b5 = (c2_u_VSP1 <= 1.0);
  c2_b6 = (c2_b4 && c2_b5);
  c2_b7 = (0.0 <= c2_u_VSP1);
  c2_b8 = (c2_b6 && c2_b7);
  c2_b9 = (c2_u_VSP1 <= 2.0);
  c2_b10 = (c2_b8 && c2_b9);
  c2_b11 = (-3.1415926535897931 <= c2_alpha_VSP1);
  c2_b12 = (c2_b10 && c2_b11);
  c2_b13 = (c2_alpha_VSP1 <= 3.1415926535897931);
  c2_b14 = (c2_b12 && c2_b13);
  c2_b15 = (-3.1415926535897931 <= c2_alpha_VSP2);
  c2_b16 = (c2_b14 && c2_b15);
  c2_b17 = (c2_alpha_VSP2 <= 3.1415926535897931);
  c2_b18 = (c2_b16 && c2_b17);
  c2_b19 = (-1.0 <= c2_omega_VSP1);
  c2_b20 = (c2_b18 && c2_b19);
  c2_b21 = (c2_omega_VSP1 <= 1.0);
  c2_b22 = (c2_b20 && c2_b21);
  c2_b23 = (-1.0 <= c2_omega_VSP2);
  c2_b24 = (c2_b22 && c2_b23);
  c2_b25 = (c2_omega_VSP2 <= 1.0);
  c2_OK = (c2_b24 && c2_b25);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
  c2_fault = !c2_OK;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -18);
  _SFD_SYMBOL_SCOPE_POP();
  *c2_b_fault = c2_fault;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ctrl_studentMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_b_fault, 1U);
}

static void initSimStructsc2_ctrl_student(SFc2_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  boolean_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc2_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(boolean_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static boolean_T c2_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_fault, const char_T *c2_identifier)
{
  boolean_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_fault), &c2_thisId);
  sf_mex_destroy(&c2_fault);
  return c2_y;
}

static boolean_T c2_b_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  boolean_T c2_y;
  boolean_T c2_b26;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b26, 1, 11, 0U, 0, 0U, 0);
  c2_y = c2_b26;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_fault;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  boolean_T c2_y;
  SFc2_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc2_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c2_fault = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_fault), &c2_thisId);
  sf_mex_destroy(&c2_fault);
  *(boolean_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i2;
  real_T c2_b_inData[7];
  int32_T c2_i3;
  real_T c2_u[7];
  const mxArray *c2_y = NULL;
  SFc2_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc2_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i2 = 0; c2_i2 < 7; c2_i2++) {
    c2_b_inData[c2_i2] = (*(real_T (*)[7])c2_inData)[c2_i2];
  }

  for (c2_i3 = 0; c2_i3 < 7; c2_i3++) {
    c2_u[c2_i3] = c2_b_inData[c2_i3];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 7), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc2_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc2_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_ctrl_student_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc2_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_d_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i4;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i4, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i4;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc2_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_ctrl_student, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_ctrl_student), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_ctrl_student);
  return c2_y;
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_ctrl_studentInstanceStruct *chartInstance)
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

void sf_c2_ctrl_student_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1672509844U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(168179353U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1559210883U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1854628246U);
}

mxArray *sf_c2_ctrl_student_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("twZ9xU73SDq5w5lBAf9Bv");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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

mxArray *sf_c2_ctrl_student_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_ctrl_student_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_ctrl_student(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"fault\",},{M[8],M[0],T\"is_active_c2_ctrl_student\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_ctrl_student_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_ctrl_studentInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_ctrl_studentInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ctrl_studentMachineNumber_,
           2,
           1,
           1,
           0,
           2,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_ctrl_studentMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ctrl_studentMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ctrl_studentMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"fault");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,503);

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);

        {
          boolean_T *c2_fault;
          real_T (*c2_u)[7];
          c2_fault = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c2_u = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_u);
          _SFD_SET_DATA_VALUE_PTR(1U, c2_fault);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ctrl_studentMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "q1j9ZtAb7K8XPjJwWLG9qG";
}

static void sf_opaque_initialize_c2_ctrl_student(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_ctrl_studentInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_ctrl_student((SFc2_ctrl_studentInstanceStruct*)
    chartInstanceVar);
  initialize_c2_ctrl_student((SFc2_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_ctrl_student(void *chartInstanceVar)
{
  enable_c2_ctrl_student((SFc2_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_ctrl_student(void *chartInstanceVar)
{
  disable_c2_ctrl_student((SFc2_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_ctrl_student(void *chartInstanceVar)
{
  sf_gateway_c2_ctrl_student((SFc2_ctrl_studentInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_ctrl_student(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_ctrl_student
    ((SFc2_ctrl_studentInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_ctrl_student();/* state var info */
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

extern void sf_internal_set_sim_state_c2_ctrl_student(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c2_ctrl_student();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_ctrl_student((SFc2_ctrl_studentInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_ctrl_student(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_ctrl_student(S);
}

static void sf_opaque_set_sim_state_c2_ctrl_student(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c2_ctrl_student(S, st);
}

static void sf_opaque_terminate_c2_ctrl_student(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_ctrl_studentInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ctrl_student_optimization_info();
    }

    finalize_c2_ctrl_student((SFc2_ctrl_studentInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_ctrl_student((SFc2_ctrl_studentInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_ctrl_student(SimStruct *S)
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
    initialize_params_c2_ctrl_student((SFc2_ctrl_studentInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ctrl_student_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(699299122U));
  ssSetChecksum1(S,(504358773U));
  ssSetChecksum2(S,(2261192820U));
  ssSetChecksum3(S,(3206535714U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_ctrl_student(SimStruct *S)
{
  SFc2_ctrl_studentInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_ctrl_studentInstanceStruct *)utMalloc(sizeof
    (SFc2_ctrl_studentInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_ctrl_studentInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_ctrl_student;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_ctrl_student;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_ctrl_student;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_ctrl_student;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_ctrl_student;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_ctrl_student;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_ctrl_student;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_ctrl_student;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_ctrl_student;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_ctrl_student;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_ctrl_student;
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

void c2_ctrl_student_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_ctrl_student(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_ctrl_student(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_ctrl_student(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_ctrl_student_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
