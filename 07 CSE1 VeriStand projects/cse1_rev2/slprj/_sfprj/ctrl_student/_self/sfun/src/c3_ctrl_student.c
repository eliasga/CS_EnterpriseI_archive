/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ctrl_student_sfun.h"
#include "c3_ctrl_student.h"
#include "mwmathutil.h"
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
static const char * c3_debug_family_names[80] = { "u", "v", "r", "m", "I_z",
  "x_g", "X_ud", "Y_vd", "N_vd", "Y_rd", "N_rd", "m_11", "m_22", "m_23", "m_32",
  "m_33", "M", "X_u", "X_v", "X_uu", "X_vv", "X_uuu", "X_vvv", "Y_v", "Y_r",
  "Y_vv", "Y_rr", "Y_vvv", "Y_rrr", "Y_rv", "Y_vr", "N_v", "N_r", "N_vv", "N_rr",
  "N_vvv", "N_rrr", "N_rv", "N_vr", "c_13", "c_23", "C", "d_11", "d_22", "d_33",
  "d_12", "d_23", "d_32", "D", "psi", "eta_1", "eta_2", "p", "nu_1", "nu_2",
  "ups", "R2", "S2", "py", "detM2", "cvv", "cvr", "bvv", "Av", "Bv", "h",
  "tau_ups", "nargin", "nargout", "nu", "eta", "pd", "pd_dot", "pd_ddot", "ly",
  "Kp", "Kd", "tau", "e1", "e2" };

/* Function Declarations */
static void initialize_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance);
static void initialize_params_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance);
static void enable_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance);
static void disable_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance);
static void c3_update_debugger_state_c3_ctrl_student
  (SFc3_ctrl_studentInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_ctrl_student
  (SFc3_ctrl_studentInstanceStruct *chartInstance);
static void set_sim_state_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance);
static void sf_gateway_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance);
static void c3_chartstep_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance);
static void initSimStructsc3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_e2, const char_T *c3_identifier, real_T c3_y[2]);
static void c3_b_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_c_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_tau, const char_T *c3_identifier, real_T c3_y[3]);
static void c3_d_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3]);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_e_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_f_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[4]);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_g_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[9]);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_info_helper(const mxArray **c3_info);
static const mxArray *c3_emlrt_marshallOut(const char * c3_u);
static const mxArray *c3_b_emlrt_marshallOut(const uint32_T c3_u);
static void c3_b_info_helper(const mxArray **c3_info);
static real_T c3_mpower(SFc3_ctrl_studentInstanceStruct *chartInstance, real_T
  c3_a);
static void c3_eml_scalar_eg(SFc3_ctrl_studentInstanceStruct *chartInstance);
static real_T c3_abs(SFc3_ctrl_studentInstanceStruct *chartInstance, real_T c3_x);
static void c3_b_eml_scalar_eg(SFc3_ctrl_studentInstanceStruct *chartInstance);
static void c3_threshold(SFc3_ctrl_studentInstanceStruct *chartInstance);
static void c3_c_eml_scalar_eg(SFc3_ctrl_studentInstanceStruct *chartInstance);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_h_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_i_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_ctrl_student, const char_T
  *c3_identifier);
static uint8_T c3_j_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_ctrl_studentInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_is_active_c3_ctrl_student = 0U;
}

static void initialize_params_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_ctrl_student
  (SFc3_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c3_ctrl_student
  (SFc3_ctrl_studentInstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i0;
  real_T c3_u[2];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i1;
  real_T c3_b_u[2];
  const mxArray *c3_c_y = NULL;
  int32_T c3_i2;
  real_T c3_c_u[3];
  const mxArray *c3_d_y = NULL;
  uint8_T c3_hoistedGlobal;
  uint8_T c3_d_u;
  const mxArray *c3_e_y = NULL;
  real_T (*c3_tau)[3];
  real_T (*c3_e2)[2];
  real_T (*c3_e1)[2];
  c3_e2 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_e1 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(4, 1), false);
  for (c3_i0 = 0; c3_i0 < 2; c3_i0++) {
    c3_u[c3_i0] = (*c3_e1)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i1 = 0; c3_i1 < 2; c3_i1++) {
    c3_b_u[c3_i1] = (*c3_e2)[c3_i1];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  for (c3_i2 = 0; c3_i2 < 3; c3_i2++) {
    c3_c_u[c3_i2] = (*c3_tau)[c3_i2];
  }

  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c3_y, 2, c3_d_y);
  c3_hoistedGlobal = chartInstance->c3_is_active_c3_ctrl_student;
  c3_d_u = c3_hoistedGlobal;
  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 3, c3_e_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[2];
  int32_T c3_i3;
  real_T c3_dv1[2];
  int32_T c3_i4;
  real_T c3_dv2[3];
  int32_T c3_i5;
  real_T (*c3_e1)[2];
  real_T (*c3_e2)[2];
  real_T (*c3_tau)[3];
  c3_e2 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_e1 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = true;
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)), "e1",
                      c3_dv0);
  for (c3_i3 = 0; c3_i3 < 2; c3_i3++) {
    (*c3_e1)[c3_i3] = c3_dv0[c3_i3];
  }

  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)), "e2",
                      c3_dv1);
  for (c3_i4 = 0; c3_i4 < 2; c3_i4++) {
    (*c3_e2)[c3_i4] = c3_dv1[c3_i4];
  }

  c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 2)),
                        "tau", c3_dv2);
  for (c3_i5 = 0; c3_i5 < 3; c3_i5++) {
    (*c3_tau)[c3_i5] = c3_dv2[c3_i5];
  }

  chartInstance->c3_is_active_c3_ctrl_student = c3_i_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 3)),
     "is_active_c3_ctrl_student");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_ctrl_student(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance)
{
  int32_T c3_i6;
  int32_T c3_i7;
  int32_T c3_i8;
  int32_T c3_i9;
  int32_T c3_i10;
  int32_T c3_i11;
  int32_T c3_i12;
  int32_T c3_i13;
  int32_T c3_i14;
  int32_T c3_i15;
  int32_T c3_i16;
  real_T (*c3_e2)[2];
  real_T (*c3_e1)[2];
  real_T (*c3_Kd)[4];
  real_T (*c3_Kp)[4];
  real_T (*c3_ly)[2];
  real_T (*c3_pd_ddot)[2];
  real_T (*c3_pd_dot)[2];
  real_T (*c3_pd)[2];
  real_T (*c3_eta)[3];
  real_T (*c3_tau)[3];
  real_T (*c3_nu)[3];
  c3_e2 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_e1 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_Kd = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 7);
  c3_Kp = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 6);
  c3_ly = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
  c3_pd_ddot = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
  c3_pd_dot = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
  c3_pd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
  c3_eta = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c3_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  for (c3_i6 = 0; c3_i6 < 3; c3_i6++) {
    _SFD_DATA_RANGE_CHECK((*c3_nu)[c3_i6], 0U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_ctrl_student(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ctrl_studentMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c3_i7 = 0; c3_i7 < 3; c3_i7++) {
    _SFD_DATA_RANGE_CHECK((*c3_tau)[c3_i7], 1U);
  }

  for (c3_i8 = 0; c3_i8 < 3; c3_i8++) {
    _SFD_DATA_RANGE_CHECK((*c3_eta)[c3_i8], 2U);
  }

  for (c3_i9 = 0; c3_i9 < 2; c3_i9++) {
    _SFD_DATA_RANGE_CHECK((*c3_pd)[c3_i9], 3U);
  }

  for (c3_i10 = 0; c3_i10 < 2; c3_i10++) {
    _SFD_DATA_RANGE_CHECK((*c3_pd_dot)[c3_i10], 4U);
  }

  for (c3_i11 = 0; c3_i11 < 2; c3_i11++) {
    _SFD_DATA_RANGE_CHECK((*c3_pd_ddot)[c3_i11], 5U);
  }

  for (c3_i12 = 0; c3_i12 < 2; c3_i12++) {
    _SFD_DATA_RANGE_CHECK((*c3_ly)[c3_i12], 6U);
  }

  for (c3_i13 = 0; c3_i13 < 4; c3_i13++) {
    _SFD_DATA_RANGE_CHECK((*c3_Kp)[c3_i13], 7U);
  }

  for (c3_i14 = 0; c3_i14 < 4; c3_i14++) {
    _SFD_DATA_RANGE_CHECK((*c3_Kd)[c3_i14], 8U);
  }

  for (c3_i15 = 0; c3_i15 < 2; c3_i15++) {
    _SFD_DATA_RANGE_CHECK((*c3_e1)[c3_i15], 9U);
  }

  for (c3_i16 = 0; c3_i16 < 2; c3_i16++) {
    _SFD_DATA_RANGE_CHECK((*c3_e2)[c3_i16], 10U);
  }
}

static void c3_chartstep_c3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance)
{
  int32_T c3_i17;
  real_T c3_nu[3];
  int32_T c3_i18;
  real_T c3_eta[3];
  int32_T c3_i19;
  real_T c3_pd[2];
  int32_T c3_i20;
  real_T c3_pd_dot[2];
  int32_T c3_i21;
  real_T c3_pd_ddot[2];
  int32_T c3_i22;
  real_T c3_ly[2];
  int32_T c3_i23;
  real_T c3_Kp[4];
  int32_T c3_i24;
  real_T c3_Kd[4];
  uint32_T c3_debug_family_var_map[80];
  real_T c3_u;
  real_T c3_v;
  real_T c3_r;
  real_T c3_m;
  real_T c3_I_z;
  real_T c3_x_g;
  real_T c3_X_ud;
  real_T c3_Y_vd;
  real_T c3_N_vd;
  real_T c3_Y_rd;
  real_T c3_N_rd;
  real_T c3_m_11;
  real_T c3_m_22;
  real_T c3_m_23;
  real_T c3_m_32;
  real_T c3_m_33;
  real_T c3_M[9];
  real_T c3_X_u;
  real_T c3_X_v;
  real_T c3_X_uu;
  real_T c3_X_vv;
  real_T c3_X_uuu;
  real_T c3_X_vvv;
  real_T c3_Y_v;
  real_T c3_Y_r;
  real_T c3_Y_vv;
  real_T c3_Y_rr;
  real_T c3_Y_vvv;
  real_T c3_Y_rrr;
  real_T c3_Y_rv;
  real_T c3_Y_vr;
  real_T c3_N_v;
  real_T c3_N_r;
  real_T c3_N_vv;
  real_T c3_N_rr;
  real_T c3_N_vvv;
  real_T c3_N_rrr;
  real_T c3_N_rv;
  real_T c3_N_vr;
  real_T c3_c_13;
  real_T c3_c_23;
  real_T c3_C[9];
  real_T c3_d_11;
  real_T c3_d_22;
  real_T c3_d_33;
  real_T c3_d_12;
  real_T c3_d_23;
  real_T c3_d_32;
  real_T c3_D[9];
  real_T c3_psi;
  real_T c3_eta_1;
  real_T c3_eta_2;
  real_T c3_p[2];
  real_T c3_nu_1;
  real_T c3_nu_2;
  real_T c3_ups[2];
  real_T c3_R2[4];
  real_T c3_S2[4];
  real_T c3_py[2];
  real_T c3_detM2;
  real_T c3_cvv;
  real_T c3_cvr;
  real_T c3_bvv;
  real_T c3_Av[4];
  real_T c3_Bv[4];
  real_T c3_h[2];
  real_T c3_tau_ups[2];
  real_T c3_nargin = 8.0;
  real_T c3_nargout = 3.0;
  real_T c3_tau[3];
  real_T c3_e1[2];
  real_T c3_e2[2];
  int32_T c3_i25;
  static real_T c3_dv3[9] = { 16.79, 0.0, 0.0, 0.0, 24.79, 0.55462499999999992,
    0.0, 0.55462499999999992, 2.76 };

  real_T c3_x;
  real_T c3_b_x;
  real_T c3_c_x;
  real_T c3_d_x;
  real_T c3_e_x;
  real_T c3_f_x;
  real_T c3_g_x;
  real_T c3_h_x;
  int32_T c3_i26;
  int32_T c3_i27;
  int32_T c3_i28;
  int32_T c3_i29;
  real_T c3_a[4];
  int32_T c3_i30;
  real_T c3_b[2];
  int32_T c3_i31;
  real_T c3_y[2];
  int32_T c3_i32;
  int32_T c3_i33;
  int32_T c3_i34;
  int32_T c3_i35;
  int32_T c3_i36;
  int32_T c3_i37;
  int32_T c3_i38;
  int32_T c3_i39;
  int32_T c3_i40;
  int32_T c3_i41;
  int32_T c3_i42;
  int32_T c3_i43;
  int32_T c3_i44;
  int32_T c3_i45;
  int32_T c3_i46;
  int32_T c3_i47;
  int32_T c3_i48;
  int32_T c3_i49;
  int32_T c3_i50;
  int32_T c3_i51;
  int32_T c3_i52;
  int32_T c3_i53;
  int32_T c3_i54;
  int32_T c3_i55;
  int32_T c3_i56;
  int32_T c3_i57;
  int32_T c3_i58;
  int32_T c3_i59;
  int32_T c3_i60;
  int32_T c3_i61;
  real_T c3_b_b[4];
  int32_T c3_i62;
  int32_T c3_i63;
  int32_T c3_i64;
  real_T c3_b_y[4];
  int32_T c3_i65;
  int32_T c3_i66;
  int32_T c3_i67;
  int32_T c3_i68;
  int32_T c3_i69;
  int32_T c3_i70;
  int32_T c3_i71;
  int32_T c3_i72;
  int32_T c3_i73;
  int32_T c3_i74;
  int32_T c3_i75;
  int32_T c3_i76;
  int32_T c3_i77;
  real_T c3_c_y[2];
  int32_T c3_i78;
  int32_T c3_i79;
  int32_T c3_i80;
  real_T c3_A;
  real_T c3_i_x;
  real_T c3_j_x;
  real_T c3_k_x;
  real_T c3_b_A;
  real_T c3_l_x;
  real_T c3_m_x;
  real_T c3_n_x;
  real_T c3_c_A;
  real_T c3_o_x;
  real_T c3_p_x;
  real_T c3_q_x;
  real_T c3_d_y;
  int32_T c3_i81;
  int32_T c3_i82;
  int32_T c3_i83;
  int32_T c3_i84;
  int32_T c3_i85;
  int32_T c3_i86;
  int32_T c3_i87;
  int32_T c3_i88;
  int32_T c3_i89;
  int32_T c3_i90;
  int32_T c3_i91;
  int32_T c3_i92;
  int32_T c3_i93;
  int32_T c3_i94;
  int32_T c3_i95;
  int32_T c3_i96;
  int32_T c3_i97;
  real_T (*c3_b_tau)[3];
  real_T (*c3_b_e1)[2];
  real_T (*c3_b_e2)[2];
  real_T (*c3_b_Kd)[4];
  real_T (*c3_b_Kp)[4];
  real_T (*c3_b_ly)[2];
  real_T (*c3_b_pd_ddot)[2];
  real_T (*c3_b_pd_dot)[2];
  real_T (*c3_b_pd)[2];
  real_T (*c3_b_eta)[3];
  real_T (*c3_b_nu)[3];
  c3_b_e2 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_b_e1 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_Kd = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 7);
  c3_b_Kp = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 6);
  c3_b_ly = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
  c3_b_pd_ddot = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
  c3_b_pd_dot = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
  c3_b_pd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
  c3_b_eta = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c3_b_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  for (c3_i17 = 0; c3_i17 < 3; c3_i17++) {
    c3_nu[c3_i17] = (*c3_b_nu)[c3_i17];
  }

  for (c3_i18 = 0; c3_i18 < 3; c3_i18++) {
    c3_eta[c3_i18] = (*c3_b_eta)[c3_i18];
  }

  for (c3_i19 = 0; c3_i19 < 2; c3_i19++) {
    c3_pd[c3_i19] = (*c3_b_pd)[c3_i19];
  }

  for (c3_i20 = 0; c3_i20 < 2; c3_i20++) {
    c3_pd_dot[c3_i20] = (*c3_b_pd_dot)[c3_i20];
  }

  for (c3_i21 = 0; c3_i21 < 2; c3_i21++) {
    c3_pd_ddot[c3_i21] = (*c3_b_pd_ddot)[c3_i21];
  }

  for (c3_i22 = 0; c3_i22 < 2; c3_i22++) {
    c3_ly[c3_i22] = (*c3_b_ly)[c3_i22];
  }

  for (c3_i23 = 0; c3_i23 < 4; c3_i23++) {
    c3_Kp[c3_i23] = (*c3_b_Kp)[c3_i23];
  }

  for (c3_i24 = 0; c3_i24 < 4; c3_i24++) {
    c3_Kd[c3_i24] = (*c3_b_Kd)[c3_i24];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 80U, 80U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_u, 0U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_v, 1U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_r, 2U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_m, 3U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_I_z, 4U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_x_g, 5U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_X_ud, 6U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_Y_vd, 7U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_N_vd, 8U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_Y_rd, 9U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_N_rd, 10U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_m_11, 11U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_m_22, 12U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_m_23, 13U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_m_32, 14U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_m_33, 15U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_M, 16U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_X_u, 17U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_X_v, 18U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_X_uu, 19U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_X_vv, 20U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_X_uuu, 21U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_X_vvv, 22U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_Y_v, 23U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_Y_r, 24U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_Y_vv, 25U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_Y_rr, 26U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_Y_vvv, 27U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_Y_rrr, 28U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_Y_rv, 29U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_Y_vr, 30U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_N_v, 31U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_N_r, 32U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_N_vv, 33U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_N_rr, 34U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_N_vvv, 35U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_N_rrr, 36U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_N_rv, 37U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_N_vr, 38U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_13, 39U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_23, 40U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_C, 41U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_11, 42U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_22, 43U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_33, 44U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_12, 45U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_23, 46U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_32, 47U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_D, 48U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_psi, 49U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_eta_1, 50U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_eta_2, 51U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_p, 52U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nu_1, 53U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nu_2, 54U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_ups, 55U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_R2, 56U, c3_c_sf_marshallOut,
    c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_S2, 57U, c3_c_sf_marshallOut,
    c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_py, 58U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_detM2, 59U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_cvv, 60U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_cvr, 61U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_bvv, 62U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_Av, 63U, c3_c_sf_marshallOut,
    c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_Bv, 64U, c3_c_sf_marshallOut,
    c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_h, 65U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_tau_ups, 66U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 67U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 68U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_nu, 69U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_eta, 70U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_pd, 71U, c3_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_pd_dot, 72U, c3_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_pd_ddot, 73U, c3_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_ly, 74U, c3_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_Kp, 75U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_Kd, 76U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_tau, 77U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_e1, 78U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_e2, 79U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 2);
  c3_u = c3_nu[0];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 3);
  c3_v = c3_nu[1];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 4);
  c3_r = c3_nu[2];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 7);
  c3_m = 14.79;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 7);
  c3_I_z = 1.76;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 7);
  c3_x_g = 0.0375;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 10);
  c3_X_ud = -2.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 11);
  c3_Y_vd = -10.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 11);
  c3_N_vd = -0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
  c3_Y_rd = -0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
  c3_N_rd = -1.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 15);
  c3_m_11 = 16.79;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 16);
  c3_m_22 = 24.79;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 17);
  c3_m_23 = 0.55462499999999992;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 18);
  c3_m_32 = 0.55462499999999992;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 19);
  c3_m_33 = 2.76;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 21);
  for (c3_i25 = 0; c3_i25 < 9; c3_i25++) {
    c3_M[c3_i25] = c3_dv3[c3_i25];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 27);
  c3_X_u = -0.6555;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 27);
  c3_X_v = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 28);
  c3_X_uu = 0.3545;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 28);
  c3_X_vv = -2.443;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
  c3_X_uuu = -3.787;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
  c3_X_vvv = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 31);
  c3_Y_v = -1.33;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 31);
  c3_Y_r = -7.25;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 32);
  c3_Y_vv = -2.776;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 32);
  c3_Y_rr = -3.45;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 33);
  c3_Y_vvv = -64.91;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 33);
  c3_Y_rrr = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 35);
  c3_Y_rv = -0.805;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 35);
  c3_Y_vr = -0.845;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 37);
  c3_N_v = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 37);
  c3_N_r = -1.9;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 38);
  c3_N_vv = -0.2088;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 38);
  c3_N_rr = -0.75;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 39);
  c3_N_vvv = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 39);
  c3_N_rrr = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 41);
  c3_N_rv = 0.13;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 41);
  c3_N_vr = 0.08;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 44);
  c3_c_13 = -24.79 * c3_v - 0.55462499999999992 * c3_r;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 45);
  c3_c_23 = 16.79 * c3_u;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 46);
  c3_C[0] = 0.0;
  c3_C[3] = 0.0;
  c3_C[6] = c3_c_13;
  c3_C[1] = 0.0;
  c3_C[4] = 0.0;
  c3_C[7] = c3_c_23;
  c3_C[2] = -c3_c_13;
  c3_C[5] = -c3_c_23;
  c3_C[8] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 51);
  c3_d_11 = (-c3_X_u - 0.3545 * c3_u) - -3.787 * c3_mpower(chartInstance, c3_u);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 52);
  c3_d_22 = ((-c3_Y_v - -2.776 * c3_v) - -64.91 * c3_mpower(chartInstance, c3_v))
    - -0.805 * c3_abs(chartInstance, c3_r);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 53);
  c3_d_33 = ((-c3_N_r - -0.75 * c3_abs(chartInstance, c3_r)) - 0.0 * c3_mpower
             (chartInstance, c3_r)) - 0.08 * c3_abs(chartInstance, c3_v);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 55);
  c3_d_12 = (-c3_X_v - -2.443 * c3_v) - 0.0 * c3_mpower(chartInstance, c3_v);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 56);
  c3_d_23 = ((-c3_Y_r - -3.45 * c3_abs(chartInstance, c3_r)) - 0.0 * c3_mpower
             (chartInstance, c3_r)) - -0.845 * c3_abs(chartInstance, c3_v);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 57);
  c3_d_32 = ((-c3_N_v - -0.2088 * c3_v) - 0.0 * c3_mpower(chartInstance, c3_v))
    - 0.13 * c3_abs(chartInstance, c3_r);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 59);
  c3_D[0] = c3_d_11;
  c3_D[3] = c3_d_12;
  c3_D[6] = 0.0;
  c3_D[1] = 0.0;
  c3_D[4] = c3_d_22;
  c3_D[7] = c3_d_23;
  c3_D[2] = 0.0;
  c3_D[5] = c3_d_32;
  c3_D[8] = c3_d_33;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 65);
  c3_d_11 = (-c3_X_u - 0.3545 * c3_u) - -3.787 * c3_mpower(chartInstance, c3_u);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 66);
  c3_d_22 = ((-c3_Y_v - -2.776 * c3_v) - -64.91 * c3_mpower(chartInstance, c3_v))
    - -0.805 * c3_abs(chartInstance, c3_r);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 67);
  c3_d_33 = ((-c3_N_r - -0.75 * c3_abs(chartInstance, c3_r)) - 0.0 * c3_mpower
             (chartInstance, c3_r)) - 0.08 * c3_abs(chartInstance, c3_v);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 69);
  c3_d_12 = (-c3_X_v - -2.443 * c3_v) - 0.0 * c3_mpower(chartInstance, c3_v);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 70);
  c3_d_23 = ((-c3_Y_r - -3.45 * c3_abs(chartInstance, c3_r)) - 0.0 * c3_mpower
             (chartInstance, c3_r)) - -0.845 * c3_abs(chartInstance, c3_v);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 71);
  c3_d_32 = ((-c3_N_v - -0.2088 * c3_v) - 0.0 * c3_mpower(chartInstance, c3_v))
    - 0.13 * c3_abs(chartInstance, c3_r);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 73);
  c3_D[0] = c3_d_11;
  c3_D[3] = c3_d_12;
  c3_D[6] = 0.0;
  c3_D[1] = 0.0;
  c3_D[4] = c3_d_22;
  c3_D[7] = c3_d_23;
  c3_D[2] = 0.0;
  c3_D[5] = c3_d_32;
  c3_D[8] = c3_d_33;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 81);
  c3_psi = c3_eta[2];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 82);
  c3_r = c3_nu[2];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 83);
  c3_eta_1 = c3_eta[0];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 84);
  c3_eta_2 = c3_eta[1];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 85);
  c3_p[0] = c3_eta_1;
  c3_p[1] = c3_eta_2;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 87);
  c3_nu_1 = c3_nu[0];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 88);
  c3_nu_2 = c3_nu[1];
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 89);
  c3_ups[0] = c3_nu_1;
  c3_ups[1] = c3_nu_2;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 92);
  c3_x = c3_psi;
  c3_b_x = c3_x;
  c3_b_x = muDoubleScalarCos(c3_b_x);
  c3_c_x = c3_psi;
  c3_d_x = c3_c_x;
  c3_d_x = muDoubleScalarSin(c3_d_x);
  c3_e_x = c3_psi;
  c3_f_x = c3_e_x;
  c3_f_x = muDoubleScalarSin(c3_f_x);
  c3_g_x = c3_psi;
  c3_h_x = c3_g_x;
  c3_h_x = muDoubleScalarCos(c3_h_x);
  c3_R2[0] = c3_b_x;
  c3_R2[2] = -c3_d_x;
  c3_R2[1] = c3_f_x;
  c3_R2[3] = c3_h_x;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 94);
  c3_S2[0] = 0.0;
  c3_S2[2] = -c3_r;
  c3_S2[1] = c3_r;
  c3_S2[3] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 97);
  c3_i26 = 0;
  for (c3_i27 = 0; c3_i27 < 2; c3_i27++) {
    c3_i28 = 0;
    for (c3_i29 = 0; c3_i29 < 2; c3_i29++) {
      c3_a[c3_i29 + c3_i26] = c3_R2[c3_i28 + c3_i27];
      c3_i28 += 2;
    }

    c3_i26 += 2;
  }

  for (c3_i30 = 0; c3_i30 < 2; c3_i30++) {
    c3_b[c3_i30] = c3_ly[c3_i30];
  }

  c3_b_eml_scalar_eg(chartInstance);
  c3_b_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i31 = 0; c3_i31 < 2; c3_i31++) {
    c3_y[c3_i31] = 0.0;
    c3_i32 = 0;
    for (c3_i33 = 0; c3_i33 < 2; c3_i33++) {
      c3_y[c3_i31] += c3_a[c3_i32 + c3_i31] * c3_b[c3_i33];
      c3_i32 += 2;
    }
  }

  for (c3_i34 = 0; c3_i34 < 2; c3_i34++) {
    c3_py[c3_i34] = c3_p[c3_i34] + c3_y[c3_i34];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 99);
  c3_i35 = 0;
  for (c3_i36 = 0; c3_i36 < 2; c3_i36++) {
    c3_i37 = 0;
    for (c3_i38 = 0; c3_i38 < 2; c3_i38++) {
      c3_a[c3_i38 + c3_i35] = c3_R2[c3_i37 + c3_i36];
      c3_i37 += 2;
    }

    c3_i35 += 2;
  }

  for (c3_i39 = 0; c3_i39 < 2; c3_i39++) {
    c3_b[c3_i39] = c3_py[c3_i39] - c3_pd[c3_i39];
  }

  c3_b_eml_scalar_eg(chartInstance);
  c3_b_eml_scalar_eg(chartInstance);
  for (c3_i40 = 0; c3_i40 < 2; c3_i40++) {
    c3_e1[c3_i40] = 0.0;
  }

  for (c3_i41 = 0; c3_i41 < 2; c3_i41++) {
    c3_e1[c3_i41] = 0.0;
  }

  for (c3_i42 = 0; c3_i42 < 2; c3_i42++) {
    c3_y[c3_i42] = c3_e1[c3_i42];
  }

  for (c3_i43 = 0; c3_i43 < 2; c3_i43++) {
    c3_e1[c3_i43] = c3_y[c3_i43];
  }

  c3_threshold(chartInstance);
  for (c3_i44 = 0; c3_i44 < 2; c3_i44++) {
    c3_y[c3_i44] = c3_e1[c3_i44];
  }

  for (c3_i45 = 0; c3_i45 < 2; c3_i45++) {
    c3_e1[c3_i45] = c3_y[c3_i45];
  }

  for (c3_i46 = 0; c3_i46 < 2; c3_i46++) {
    c3_e1[c3_i46] = 0.0;
    c3_i47 = 0;
    for (c3_i48 = 0; c3_i48 < 2; c3_i48++) {
      c3_e1[c3_i46] += c3_a[c3_i47 + c3_i46] * c3_b[c3_i48];
      c3_i47 += 2;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 100);
  c3_i49 = 0;
  for (c3_i50 = 0; c3_i50 < 2; c3_i50++) {
    c3_i51 = 0;
    for (c3_i52 = 0; c3_i52 < 2; c3_i52++) {
      c3_a[c3_i52 + c3_i49] = c3_R2[c3_i51 + c3_i50];
      c3_i51 += 2;
    }

    c3_i49 += 2;
  }

  for (c3_i53 = 0; c3_i53 < 2; c3_i53++) {
    c3_b[c3_i53] = c3_pd_dot[c3_i53];
  }

  c3_b_eml_scalar_eg(chartInstance);
  c3_b_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i54 = 0; c3_i54 < 2; c3_i54++) {
    c3_y[c3_i54] = 0.0;
    c3_i55 = 0;
    for (c3_i56 = 0; c3_i56 < 2; c3_i56++) {
      c3_y[c3_i54] += c3_a[c3_i55 + c3_i54] * c3_b[c3_i56];
      c3_i55 += 2;
    }
  }

  c3_i57 = 0;
  for (c3_i58 = 0; c3_i58 < 2; c3_i58++) {
    c3_i59 = 0;
    for (c3_i60 = 0; c3_i60 < 2; c3_i60++) {
      c3_a[c3_i60 + c3_i57] = c3_R2[c3_i59 + c3_i58];
      c3_i59 += 2;
    }

    c3_i57 += 2;
  }

  for (c3_i61 = 0; c3_i61 < 4; c3_i61++) {
    c3_b_b[c3_i61] = c3_S2[c3_i61];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i62 = 0; c3_i62 < 2; c3_i62++) {
    c3_i63 = 0;
    for (c3_i64 = 0; c3_i64 < 2; c3_i64++) {
      c3_b_y[c3_i63 + c3_i62] = 0.0;
      c3_i65 = 0;
      for (c3_i66 = 0; c3_i66 < 2; c3_i66++) {
        c3_b_y[c3_i63 + c3_i62] += c3_a[c3_i65 + c3_i62] * c3_b_b[c3_i66 +
          c3_i63];
        c3_i65 += 2;
      }

      c3_i63 += 2;
    }
  }

  c3_i67 = 0;
  for (c3_i68 = 0; c3_i68 < 2; c3_i68++) {
    c3_i69 = 0;
    for (c3_i70 = 0; c3_i70 < 2; c3_i70++) {
      c3_b_b[c3_i70 + c3_i67] = c3_R2[c3_i69 + c3_i68];
      c3_i69 += 2;
    }

    c3_i67 += 2;
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i71 = 0; c3_i71 < 2; c3_i71++) {
    c3_i72 = 0;
    for (c3_i73 = 0; c3_i73 < 2; c3_i73++) {
      c3_a[c3_i72 + c3_i71] = 0.0;
      c3_i74 = 0;
      for (c3_i75 = 0; c3_i75 < 2; c3_i75++) {
        c3_a[c3_i72 + c3_i71] += c3_b_y[c3_i74 + c3_i71] * c3_b_b[c3_i75 +
          c3_i72];
        c3_i74 += 2;
      }

      c3_i72 += 2;
    }
  }

  for (c3_i76 = 0; c3_i76 < 2; c3_i76++) {
    c3_b[c3_i76] = c3_ly[c3_i76];
  }

  c3_b_eml_scalar_eg(chartInstance);
  c3_b_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i77 = 0; c3_i77 < 2; c3_i77++) {
    c3_c_y[c3_i77] = 0.0;
    c3_i78 = 0;
    for (c3_i79 = 0; c3_i79 < 2; c3_i79++) {
      c3_c_y[c3_i77] += c3_a[c3_i78 + c3_i77] * c3_b[c3_i79];
      c3_i78 += 2;
    }
  }

  for (c3_i80 = 0; c3_i80 < 2; c3_i80++) {
    c3_e2[c3_i80] = (c3_ups[c3_i80] - c3_y[c3_i80]) - c3_c_y[c3_i80];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 102);
  c3_detM2 = 68.112791109374982;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 103);
  c3_A = -(c3_d_22 * 2.76 - c3_d_32 * 0.55462499999999992);
  c3_i_x = c3_A;
  c3_j_x = c3_i_x;
  c3_k_x = c3_j_x;
  c3_cvv = c3_k_x / 68.112791109374982;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 104);
  c3_b_A = -(c3_d_23 * 2.76 - c3_d_33 * 0.55462499999999992);
  c3_l_x = c3_b_A;
  c3_m_x = c3_l_x;
  c3_n_x = c3_m_x;
  c3_cvr = c3_n_x / 68.112791109374982;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 105);
  c3_bvv = 0.04052102336502425;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 107);
  c3_c_A = -c3_d_11;
  c3_o_x = c3_c_A;
  c3_p_x = c3_o_x;
  c3_q_x = c3_p_x;
  c3_d_y = c3_q_x / 16.79;
  c3_Av[0] = c3_d_y;
  c3_Av[2] = 0.0;
  c3_Av[1] = 0.0;
  c3_Av[3] = c3_cvv;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 109);
  c3_i81 = 0;
  for (c3_i82 = 0; c3_i82 < 2; c3_i82++) {
    c3_Bv[c3_i81] = 0.059559261465157838 + -0.059559261465157838 * (real_T)
      c3_i82;
    c3_i81 += 2;
  }

  c3_Bv[1] = 0.0;
  c3_Bv[3] = c3_bvv;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 111);
  c3_h[0] = 0.0;
  c3_h[1] = c3_cvr;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 131U);
  for (c3_i83 = 0; c3_i83 < 4; c3_i83++) {
    c3_a[c3_i83] = -c3_Kp[c3_i83];
  }

  for (c3_i84 = 0; c3_i84 < 2; c3_i84++) {
    c3_b[c3_i84] = c3_e1[c3_i84];
  }

  c3_b_eml_scalar_eg(chartInstance);
  c3_b_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i85 = 0; c3_i85 < 2; c3_i85++) {
    c3_y[c3_i85] = 0.0;
    c3_i86 = 0;
    for (c3_i87 = 0; c3_i87 < 2; c3_i87++) {
      c3_y[c3_i85] += c3_a[c3_i86 + c3_i85] * c3_b[c3_i87];
      c3_i86 += 2;
    }
  }

  for (c3_i88 = 0; c3_i88 < 4; c3_i88++) {
    c3_a[c3_i88] = c3_Kd[c3_i88];
  }

  for (c3_i89 = 0; c3_i89 < 2; c3_i89++) {
    c3_b[c3_i89] = c3_e2[c3_i89];
  }

  c3_b_eml_scalar_eg(chartInstance);
  c3_b_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i90 = 0; c3_i90 < 2; c3_i90++) {
    c3_c_y[c3_i90] = 0.0;
    c3_i91 = 0;
    for (c3_i92 = 0; c3_i92 < 2; c3_i92++) {
      c3_c_y[c3_i90] += c3_a[c3_i91 + c3_i90] * c3_b[c3_i92];
      c3_i91 += 2;
    }
  }

  for (c3_i93 = 0; c3_i93 < 2; c3_i93++) {
    c3_tau_ups[c3_i93] = c3_y[c3_i93] - c3_c_y[c3_i93];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 132U);
  for (c3_i94 = 0; c3_i94 < 2; c3_i94++) {
    c3_tau[c3_i94] = c3_tau_ups[c3_i94];
  }

  c3_tau[2] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -132);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i95 = 0; c3_i95 < 3; c3_i95++) {
    (*c3_b_tau)[c3_i95] = c3_tau[c3_i95];
  }

  for (c3_i96 = 0; c3_i96 < 2; c3_i96++) {
    (*c3_b_e1)[c3_i96] = c3_e1[c3_i96];
  }

  for (c3_i97 = 0; c3_i97 < 2; c3_i97++) {
    (*c3_b_e2)[c3_i97] = c3_e2[c3_i97];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_ctrl_student(SFc3_ctrl_studentInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)c3_machineNumber;
  (void)c3_chartNumber;
  (void)c3_instanceNumber;
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i98;
  real_T c3_b_inData[2];
  int32_T c3_i99;
  real_T c3_u[2];
  const mxArray *c3_y = NULL;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i98 = 0; c3_i98 < 2; c3_i98++) {
    c3_b_inData[c3_i98] = (*(real_T (*)[2])c3_inData)[c3_i98];
  }

  for (c3_i99 = 0; c3_i99 < 2; c3_i99++) {
    c3_u[c3_i99] = c3_b_inData[c3_i99];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_e2, const char_T *c3_identifier, real_T c3_y[2])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_e2), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_e2);
}

static void c3_b_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2])
{
  real_T c3_dv4[2];
  int32_T c3_i100;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv4, 1, 0, 0U, 1, 0U, 1, 2);
  for (c3_i100 = 0; c3_i100 < 2; c3_i100++) {
    c3_y[c3_i100] = c3_dv4[c3_i100];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_e2;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[2];
  int32_T c3_i101;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_e2 = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_e2), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_e2);
  for (c3_i101 = 0; c3_i101 < 2; c3_i101++) {
    (*(real_T (*)[2])c3_outData)[c3_i101] = c3_y[c3_i101];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i102;
  real_T c3_b_inData[3];
  int32_T c3_i103;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i102 = 0; c3_i102 < 3; c3_i102++) {
    c3_b_inData[c3_i102] = (*(real_T (*)[3])c3_inData)[c3_i102];
  }

  for (c3_i103 = 0; c3_i103 < 3; c3_i103++) {
    c3_u[c3_i103] = c3_b_inData[c3_i103];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_c_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_tau, const char_T *c3_identifier, real_T c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_tau), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_tau);
}

static void c3_d_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3])
{
  real_T c3_dv5[3];
  int32_T c3_i104;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv5, 1, 0, 0U, 1, 0U, 1, 3);
  for (c3_i104 = 0; c3_i104 < 3; c3_i104++) {
    c3_y[c3_i104] = c3_dv5[c3_i104];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_tau;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i105;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_tau = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_tau), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_tau);
  for (c3_i105 = 0; c3_i105 < 3; c3_i105++) {
    (*(real_T (*)[3])c3_outData)[c3_i105] = c3_y[c3_i105];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i106;
  int32_T c3_i107;
  int32_T c3_i108;
  real_T c3_b_inData[4];
  int32_T c3_i109;
  int32_T c3_i110;
  int32_T c3_i111;
  real_T c3_u[4];
  const mxArray *c3_y = NULL;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i106 = 0;
  for (c3_i107 = 0; c3_i107 < 2; c3_i107++) {
    for (c3_i108 = 0; c3_i108 < 2; c3_i108++) {
      c3_b_inData[c3_i108 + c3_i106] = (*(real_T (*)[4])c3_inData)[c3_i108 +
        c3_i106];
    }

    c3_i106 += 2;
  }

  c3_i109 = 0;
  for (c3_i110 = 0; c3_i110 < 2; c3_i110++) {
    for (c3_i111 = 0; c3_i111 < 2; c3_i111++) {
      c3_u[c3_i111 + c3_i109] = c3_b_inData[c3_i111 + c3_i109];
    }

    c3_i109 += 2;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 2, 2), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static real_T c3_e_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_f_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[4])
{
  real_T c3_dv6[4];
  int32_T c3_i112;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv6, 1, 0, 0U, 1, 0U, 2, 2, 2);
  for (c3_i112 = 0; c3_i112 < 4; c3_i112++) {
    c3_y[c3_i112] = c3_dv6[c3_i112];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_Bv;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[4];
  int32_T c3_i113;
  int32_T c3_i114;
  int32_T c3_i115;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_Bv = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_Bv), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_Bv);
  c3_i113 = 0;
  for (c3_i114 = 0; c3_i114 < 2; c3_i114++) {
    for (c3_i115 = 0; c3_i115 < 2; c3_i115++) {
      (*(real_T (*)[4])c3_outData)[c3_i115 + c3_i113] = c3_y[c3_i115 + c3_i113];
    }

    c3_i113 += 2;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i116;
  int32_T c3_i117;
  int32_T c3_i118;
  real_T c3_b_inData[9];
  int32_T c3_i119;
  int32_T c3_i120;
  int32_T c3_i121;
  real_T c3_u[9];
  const mxArray *c3_y = NULL;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i116 = 0;
  for (c3_i117 = 0; c3_i117 < 3; c3_i117++) {
    for (c3_i118 = 0; c3_i118 < 3; c3_i118++) {
      c3_b_inData[c3_i118 + c3_i116] = (*(real_T (*)[9])c3_inData)[c3_i118 +
        c3_i116];
    }

    c3_i116 += 3;
  }

  c3_i119 = 0;
  for (c3_i120 = 0; c3_i120 < 3; c3_i120++) {
    for (c3_i121 = 0; c3_i121 < 3; c3_i121++) {
      c3_u[c3_i121 + c3_i119] = c3_b_inData[c3_i121 + c3_i119];
    }

    c3_i119 += 3;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_g_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[9])
{
  real_T c3_dv7[9];
  int32_T c3_i122;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv7, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c3_i122 = 0; c3_i122 < 9; c3_i122++) {
    c3_y[c3_i122] = c3_dv7[c3_i122];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_D;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[9];
  int32_T c3_i123;
  int32_T c3_i124;
  int32_T c3_i125;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_D = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_D), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_D);
  c3_i123 = 0;
  for (c3_i124 = 0; c3_i124 < 3; c3_i124++) {
    for (c3_i125 = 0; c3_i125 < 3; c3_i125++) {
      (*(real_T (*)[9])c3_outData)[c3_i125 + c3_i123] = c3_y[c3_i125 + c3_i123];
    }

    c3_i123 += 3;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_ctrl_student_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_createstruct("structure", 2, 127, 1),
                false);
  c3_info_helper(&c3_nameCaptureInfo);
  c3_b_info_helper(&c3_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c3_nameCaptureInfo);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(const mxArray **c3_info)
{
  const mxArray *c3_rhs0 = NULL;
  const mxArray *c3_lhs0 = NULL;
  const mxArray *c3_rhs1 = NULL;
  const mxArray *c3_lhs1 = NULL;
  const mxArray *c3_rhs2 = NULL;
  const mxArray *c3_lhs2 = NULL;
  const mxArray *c3_rhs3 = NULL;
  const mxArray *c3_lhs3 = NULL;
  const mxArray *c3_rhs4 = NULL;
  const mxArray *c3_lhs4 = NULL;
  const mxArray *c3_rhs5 = NULL;
  const mxArray *c3_lhs5 = NULL;
  const mxArray *c3_rhs6 = NULL;
  const mxArray *c3_lhs6 = NULL;
  const mxArray *c3_rhs7 = NULL;
  const mxArray *c3_lhs7 = NULL;
  const mxArray *c3_rhs8 = NULL;
  const mxArray *c3_lhs8 = NULL;
  const mxArray *c3_rhs9 = NULL;
  const mxArray *c3_lhs9 = NULL;
  const mxArray *c3_rhs10 = NULL;
  const mxArray *c3_lhs10 = NULL;
  const mxArray *c3_rhs11 = NULL;
  const mxArray *c3_lhs11 = NULL;
  const mxArray *c3_rhs12 = NULL;
  const mxArray *c3_lhs12 = NULL;
  const mxArray *c3_rhs13 = NULL;
  const mxArray *c3_lhs13 = NULL;
  const mxArray *c3_rhs14 = NULL;
  const mxArray *c3_lhs14 = NULL;
  const mxArray *c3_rhs15 = NULL;
  const mxArray *c3_lhs15 = NULL;
  const mxArray *c3_rhs16 = NULL;
  const mxArray *c3_lhs16 = NULL;
  const mxArray *c3_rhs17 = NULL;
  const mxArray *c3_lhs17 = NULL;
  const mxArray *c3_rhs18 = NULL;
  const mxArray *c3_lhs18 = NULL;
  const mxArray *c3_rhs19 = NULL;
  const mxArray *c3_lhs19 = NULL;
  const mxArray *c3_rhs20 = NULL;
  const mxArray *c3_lhs20 = NULL;
  const mxArray *c3_rhs21 = NULL;
  const mxArray *c3_lhs21 = NULL;
  const mxArray *c3_rhs22 = NULL;
  const mxArray *c3_lhs22 = NULL;
  const mxArray *c3_rhs23 = NULL;
  const mxArray *c3_lhs23 = NULL;
  const mxArray *c3_rhs24 = NULL;
  const mxArray *c3_lhs24 = NULL;
  const mxArray *c3_rhs25 = NULL;
  const mxArray *c3_lhs25 = NULL;
  const mxArray *c3_rhs26 = NULL;
  const mxArray *c3_lhs26 = NULL;
  const mxArray *c3_rhs27 = NULL;
  const mxArray *c3_lhs27 = NULL;
  const mxArray *c3_rhs28 = NULL;
  const mxArray *c3_lhs28 = NULL;
  const mxArray *c3_rhs29 = NULL;
  const mxArray *c3_lhs29 = NULL;
  const mxArray *c3_rhs30 = NULL;
  const mxArray *c3_lhs30 = NULL;
  const mxArray *c3_rhs31 = NULL;
  const mxArray *c3_lhs31 = NULL;
  const mxArray *c3_rhs32 = NULL;
  const mxArray *c3_lhs32 = NULL;
  const mxArray *c3_rhs33 = NULL;
  const mxArray *c3_lhs33 = NULL;
  const mxArray *c3_rhs34 = NULL;
  const mxArray *c3_lhs34 = NULL;
  const mxArray *c3_rhs35 = NULL;
  const mxArray *c3_lhs35 = NULL;
  const mxArray *c3_rhs36 = NULL;
  const mxArray *c3_lhs36 = NULL;
  const mxArray *c3_rhs37 = NULL;
  const mxArray *c3_lhs37 = NULL;
  const mxArray *c3_rhs38 = NULL;
  const mxArray *c3_lhs38 = NULL;
  const mxArray *c3_rhs39 = NULL;
  const mxArray *c3_lhs39 = NULL;
  const mxArray *c3_rhs40 = NULL;
  const mxArray *c3_lhs40 = NULL;
  const mxArray *c3_rhs41 = NULL;
  const mxArray *c3_lhs41 = NULL;
  const mxArray *c3_rhs42 = NULL;
  const mxArray *c3_lhs42 = NULL;
  const mxArray *c3_rhs43 = NULL;
  const mxArray *c3_lhs43 = NULL;
  const mxArray *c3_rhs44 = NULL;
  const mxArray *c3_lhs44 = NULL;
  const mxArray *c3_rhs45 = NULL;
  const mxArray *c3_lhs45 = NULL;
  const mxArray *c3_rhs46 = NULL;
  const mxArray *c3_lhs46 = NULL;
  const mxArray *c3_rhs47 = NULL;
  const mxArray *c3_lhs47 = NULL;
  const mxArray *c3_rhs48 = NULL;
  const mxArray *c3_lhs48 = NULL;
  const mxArray *c3_rhs49 = NULL;
  const mxArray *c3_lhs49 = NULL;
  const mxArray *c3_rhs50 = NULL;
  const mxArray *c3_lhs50 = NULL;
  const mxArray *c3_rhs51 = NULL;
  const mxArray *c3_lhs51 = NULL;
  const mxArray *c3_rhs52 = NULL;
  const mxArray *c3_lhs52 = NULL;
  const mxArray *c3_rhs53 = NULL;
  const mxArray *c3_lhs53 = NULL;
  const mxArray *c3_rhs54 = NULL;
  const mxArray *c3_lhs54 = NULL;
  const mxArray *c3_rhs55 = NULL;
  const mxArray *c3_lhs55 = NULL;
  const mxArray *c3_rhs56 = NULL;
  const mxArray *c3_lhs56 = NULL;
  const mxArray *c3_rhs57 = NULL;
  const mxArray *c3_lhs57 = NULL;
  const mxArray *c3_rhs58 = NULL;
  const mxArray *c3_lhs58 = NULL;
  const mxArray *c3_rhs59 = NULL;
  const mxArray *c3_lhs59 = NULL;
  const mxArray *c3_rhs60 = NULL;
  const mxArray *c3_lhs60 = NULL;
  const mxArray *c3_rhs61 = NULL;
  const mxArray *c3_lhs61 = NULL;
  const mxArray *c3_rhs62 = NULL;
  const mxArray *c3_lhs62 = NULL;
  const mxArray *c3_rhs63 = NULL;
  const mxArray *c3_lhs63 = NULL;
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("mpower"), "name", "name", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c3_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c3_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("ismatrix"), "name", "name", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c3_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("power"), "name", "name", 3);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c3_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 4);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c3_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 5);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 5);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c3_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 6);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c3_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 7);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 7);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c3_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 8);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 8);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c3_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 9);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("floor"), "name", "name", 9);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c3_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 10);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c3_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 11);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c3_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 12);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 12);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c3_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 13);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("abs"), "name", "name", 13);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c3_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 14);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c3_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 15);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 15);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c3_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 16);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("cos"), "name", "name", 16);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c3_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 17);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c3_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 18);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("sin"), "name", "name", 18);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c3_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 19);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c3_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 20);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 20);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c3_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 21);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 21);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c3_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 22);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 22);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c3_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 23);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 23);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c3_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 24);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  24);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c3_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 25);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 25);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c3_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 26);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 26);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c3_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 27);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 27);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c3_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 28);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 28);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c3_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 29);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 29);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c3_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 30);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 30);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c3_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 31);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 31);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c3_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 32);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("det"), "name", "name", 32);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m"), "resolved",
                  "resolved", 32);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818822U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c3_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m"), "context",
                  "context", 33);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 33);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c3_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m"), "context",
                  "context", 34);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_xgetrf"), "name", "name",
                  34);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818806U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c3_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"),
                  "context", "context", 35);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_lapack_xgetrf"), "name",
                  "name", 35);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818810U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c3_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"),
                  "context", "context", 36);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_matlab_zgetrf"), "name",
                  "name", 36);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1302688994U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c3_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 37);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("realmin"), "name", "name", 37);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "resolved",
                  "resolved", 37);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1307651242U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c3_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "context",
                  "context", 38);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_realmin"), "name", "name",
                  38);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "resolved",
                  "resolved", 38);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1307651244U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c3_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "context",
                  "context", 39);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 39);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c3_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 40);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eps"), "name", "name", 40);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 40);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c3_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 41);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 41);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 41);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818782U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c3_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 42);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_eps"), "name", "name", 42);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "resolved",
                  "resolved", 42);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c3_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 43);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c3_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 44);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("min"), "name", "name", 44);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 44);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 44);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c3_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 45);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 45);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1378295984U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c3_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 46);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 46);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 46);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 46);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c3_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 47);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 47);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 47);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c3_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 48);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 48);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 48);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c3_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 49);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 49);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 49);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 49);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c3_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 50);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 50);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c3_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 51);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 51);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 51);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 51);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c3_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 52);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 52);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 52);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 52);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c3_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 53);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("colon"), "name", "name", 53);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 53);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1378295988U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c3_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 54);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("colon"), "name", "name", 54);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 54);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1378295988U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c3_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 55);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 55);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 55);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c3_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 56);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 56);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 56);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 56);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c3_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 57);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("floor"), "name", "name", 57);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 57);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c3_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 58);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("intmin"), "name", "name", 58);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 58);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c3_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 59);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 59);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 59);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c3_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 60);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("intmax"), "name", "name", 60);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 60);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c3_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 61);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 61);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 61);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c3_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 62);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("intmin"), "name", "name", 62);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 62);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 62);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c3_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 63);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("intmax"), "name", "name", 63);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 63);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c3_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c3_rhs0);
  sf_mex_destroy(&c3_lhs0);
  sf_mex_destroy(&c3_rhs1);
  sf_mex_destroy(&c3_lhs1);
  sf_mex_destroy(&c3_rhs2);
  sf_mex_destroy(&c3_lhs2);
  sf_mex_destroy(&c3_rhs3);
  sf_mex_destroy(&c3_lhs3);
  sf_mex_destroy(&c3_rhs4);
  sf_mex_destroy(&c3_lhs4);
  sf_mex_destroy(&c3_rhs5);
  sf_mex_destroy(&c3_lhs5);
  sf_mex_destroy(&c3_rhs6);
  sf_mex_destroy(&c3_lhs6);
  sf_mex_destroy(&c3_rhs7);
  sf_mex_destroy(&c3_lhs7);
  sf_mex_destroy(&c3_rhs8);
  sf_mex_destroy(&c3_lhs8);
  sf_mex_destroy(&c3_rhs9);
  sf_mex_destroy(&c3_lhs9);
  sf_mex_destroy(&c3_rhs10);
  sf_mex_destroy(&c3_lhs10);
  sf_mex_destroy(&c3_rhs11);
  sf_mex_destroy(&c3_lhs11);
  sf_mex_destroy(&c3_rhs12);
  sf_mex_destroy(&c3_lhs12);
  sf_mex_destroy(&c3_rhs13);
  sf_mex_destroy(&c3_lhs13);
  sf_mex_destroy(&c3_rhs14);
  sf_mex_destroy(&c3_lhs14);
  sf_mex_destroy(&c3_rhs15);
  sf_mex_destroy(&c3_lhs15);
  sf_mex_destroy(&c3_rhs16);
  sf_mex_destroy(&c3_lhs16);
  sf_mex_destroy(&c3_rhs17);
  sf_mex_destroy(&c3_lhs17);
  sf_mex_destroy(&c3_rhs18);
  sf_mex_destroy(&c3_lhs18);
  sf_mex_destroy(&c3_rhs19);
  sf_mex_destroy(&c3_lhs19);
  sf_mex_destroy(&c3_rhs20);
  sf_mex_destroy(&c3_lhs20);
  sf_mex_destroy(&c3_rhs21);
  sf_mex_destroy(&c3_lhs21);
  sf_mex_destroy(&c3_rhs22);
  sf_mex_destroy(&c3_lhs22);
  sf_mex_destroy(&c3_rhs23);
  sf_mex_destroy(&c3_lhs23);
  sf_mex_destroy(&c3_rhs24);
  sf_mex_destroy(&c3_lhs24);
  sf_mex_destroy(&c3_rhs25);
  sf_mex_destroy(&c3_lhs25);
  sf_mex_destroy(&c3_rhs26);
  sf_mex_destroy(&c3_lhs26);
  sf_mex_destroy(&c3_rhs27);
  sf_mex_destroy(&c3_lhs27);
  sf_mex_destroy(&c3_rhs28);
  sf_mex_destroy(&c3_lhs28);
  sf_mex_destroy(&c3_rhs29);
  sf_mex_destroy(&c3_lhs29);
  sf_mex_destroy(&c3_rhs30);
  sf_mex_destroy(&c3_lhs30);
  sf_mex_destroy(&c3_rhs31);
  sf_mex_destroy(&c3_lhs31);
  sf_mex_destroy(&c3_rhs32);
  sf_mex_destroy(&c3_lhs32);
  sf_mex_destroy(&c3_rhs33);
  sf_mex_destroy(&c3_lhs33);
  sf_mex_destroy(&c3_rhs34);
  sf_mex_destroy(&c3_lhs34);
  sf_mex_destroy(&c3_rhs35);
  sf_mex_destroy(&c3_lhs35);
  sf_mex_destroy(&c3_rhs36);
  sf_mex_destroy(&c3_lhs36);
  sf_mex_destroy(&c3_rhs37);
  sf_mex_destroy(&c3_lhs37);
  sf_mex_destroy(&c3_rhs38);
  sf_mex_destroy(&c3_lhs38);
  sf_mex_destroy(&c3_rhs39);
  sf_mex_destroy(&c3_lhs39);
  sf_mex_destroy(&c3_rhs40);
  sf_mex_destroy(&c3_lhs40);
  sf_mex_destroy(&c3_rhs41);
  sf_mex_destroy(&c3_lhs41);
  sf_mex_destroy(&c3_rhs42);
  sf_mex_destroy(&c3_lhs42);
  sf_mex_destroy(&c3_rhs43);
  sf_mex_destroy(&c3_lhs43);
  sf_mex_destroy(&c3_rhs44);
  sf_mex_destroy(&c3_lhs44);
  sf_mex_destroy(&c3_rhs45);
  sf_mex_destroy(&c3_lhs45);
  sf_mex_destroy(&c3_rhs46);
  sf_mex_destroy(&c3_lhs46);
  sf_mex_destroy(&c3_rhs47);
  sf_mex_destroy(&c3_lhs47);
  sf_mex_destroy(&c3_rhs48);
  sf_mex_destroy(&c3_lhs48);
  sf_mex_destroy(&c3_rhs49);
  sf_mex_destroy(&c3_lhs49);
  sf_mex_destroy(&c3_rhs50);
  sf_mex_destroy(&c3_lhs50);
  sf_mex_destroy(&c3_rhs51);
  sf_mex_destroy(&c3_lhs51);
  sf_mex_destroy(&c3_rhs52);
  sf_mex_destroy(&c3_lhs52);
  sf_mex_destroy(&c3_rhs53);
  sf_mex_destroy(&c3_lhs53);
  sf_mex_destroy(&c3_rhs54);
  sf_mex_destroy(&c3_lhs54);
  sf_mex_destroy(&c3_rhs55);
  sf_mex_destroy(&c3_lhs55);
  sf_mex_destroy(&c3_rhs56);
  sf_mex_destroy(&c3_lhs56);
  sf_mex_destroy(&c3_rhs57);
  sf_mex_destroy(&c3_lhs57);
  sf_mex_destroy(&c3_rhs58);
  sf_mex_destroy(&c3_lhs58);
  sf_mex_destroy(&c3_rhs59);
  sf_mex_destroy(&c3_lhs59);
  sf_mex_destroy(&c3_rhs60);
  sf_mex_destroy(&c3_lhs60);
  sf_mex_destroy(&c3_rhs61);
  sf_mex_destroy(&c3_lhs61);
  sf_mex_destroy(&c3_rhs62);
  sf_mex_destroy(&c3_lhs62);
  sf_mex_destroy(&c3_rhs63);
  sf_mex_destroy(&c3_lhs63);
}

static const mxArray *c3_emlrt_marshallOut(const char * c3_u)
{
  const mxArray *c3_y = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c3_u)), false);
  return c3_y;
}

static const mxArray *c3_b_emlrt_marshallOut(const uint32_T c3_u)
{
  const mxArray *c3_y = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 7, 0U, 0U, 0U, 0), false);
  return c3_y;
}

static void c3_b_info_helper(const mxArray **c3_info)
{
  const mxArray *c3_rhs64 = NULL;
  const mxArray *c3_lhs64 = NULL;
  const mxArray *c3_rhs65 = NULL;
  const mxArray *c3_lhs65 = NULL;
  const mxArray *c3_rhs66 = NULL;
  const mxArray *c3_lhs66 = NULL;
  const mxArray *c3_rhs67 = NULL;
  const mxArray *c3_lhs67 = NULL;
  const mxArray *c3_rhs68 = NULL;
  const mxArray *c3_lhs68 = NULL;
  const mxArray *c3_rhs69 = NULL;
  const mxArray *c3_lhs69 = NULL;
  const mxArray *c3_rhs70 = NULL;
  const mxArray *c3_lhs70 = NULL;
  const mxArray *c3_rhs71 = NULL;
  const mxArray *c3_lhs71 = NULL;
  const mxArray *c3_rhs72 = NULL;
  const mxArray *c3_lhs72 = NULL;
  const mxArray *c3_rhs73 = NULL;
  const mxArray *c3_lhs73 = NULL;
  const mxArray *c3_rhs74 = NULL;
  const mxArray *c3_lhs74 = NULL;
  const mxArray *c3_rhs75 = NULL;
  const mxArray *c3_lhs75 = NULL;
  const mxArray *c3_rhs76 = NULL;
  const mxArray *c3_lhs76 = NULL;
  const mxArray *c3_rhs77 = NULL;
  const mxArray *c3_lhs77 = NULL;
  const mxArray *c3_rhs78 = NULL;
  const mxArray *c3_lhs78 = NULL;
  const mxArray *c3_rhs79 = NULL;
  const mxArray *c3_lhs79 = NULL;
  const mxArray *c3_rhs80 = NULL;
  const mxArray *c3_lhs80 = NULL;
  const mxArray *c3_rhs81 = NULL;
  const mxArray *c3_lhs81 = NULL;
  const mxArray *c3_rhs82 = NULL;
  const mxArray *c3_lhs82 = NULL;
  const mxArray *c3_rhs83 = NULL;
  const mxArray *c3_lhs83 = NULL;
  const mxArray *c3_rhs84 = NULL;
  const mxArray *c3_lhs84 = NULL;
  const mxArray *c3_rhs85 = NULL;
  const mxArray *c3_lhs85 = NULL;
  const mxArray *c3_rhs86 = NULL;
  const mxArray *c3_lhs86 = NULL;
  const mxArray *c3_rhs87 = NULL;
  const mxArray *c3_lhs87 = NULL;
  const mxArray *c3_rhs88 = NULL;
  const mxArray *c3_lhs88 = NULL;
  const mxArray *c3_rhs89 = NULL;
  const mxArray *c3_lhs89 = NULL;
  const mxArray *c3_rhs90 = NULL;
  const mxArray *c3_lhs90 = NULL;
  const mxArray *c3_rhs91 = NULL;
  const mxArray *c3_lhs91 = NULL;
  const mxArray *c3_rhs92 = NULL;
  const mxArray *c3_lhs92 = NULL;
  const mxArray *c3_rhs93 = NULL;
  const mxArray *c3_lhs93 = NULL;
  const mxArray *c3_rhs94 = NULL;
  const mxArray *c3_lhs94 = NULL;
  const mxArray *c3_rhs95 = NULL;
  const mxArray *c3_lhs95 = NULL;
  const mxArray *c3_rhs96 = NULL;
  const mxArray *c3_lhs96 = NULL;
  const mxArray *c3_rhs97 = NULL;
  const mxArray *c3_lhs97 = NULL;
  const mxArray *c3_rhs98 = NULL;
  const mxArray *c3_lhs98 = NULL;
  const mxArray *c3_rhs99 = NULL;
  const mxArray *c3_lhs99 = NULL;
  const mxArray *c3_rhs100 = NULL;
  const mxArray *c3_lhs100 = NULL;
  const mxArray *c3_rhs101 = NULL;
  const mxArray *c3_lhs101 = NULL;
  const mxArray *c3_rhs102 = NULL;
  const mxArray *c3_lhs102 = NULL;
  const mxArray *c3_rhs103 = NULL;
  const mxArray *c3_lhs103 = NULL;
  const mxArray *c3_rhs104 = NULL;
  const mxArray *c3_lhs104 = NULL;
  const mxArray *c3_rhs105 = NULL;
  const mxArray *c3_lhs105 = NULL;
  const mxArray *c3_rhs106 = NULL;
  const mxArray *c3_lhs106 = NULL;
  const mxArray *c3_rhs107 = NULL;
  const mxArray *c3_lhs107 = NULL;
  const mxArray *c3_rhs108 = NULL;
  const mxArray *c3_lhs108 = NULL;
  const mxArray *c3_rhs109 = NULL;
  const mxArray *c3_lhs109 = NULL;
  const mxArray *c3_rhs110 = NULL;
  const mxArray *c3_lhs110 = NULL;
  const mxArray *c3_rhs111 = NULL;
  const mxArray *c3_lhs111 = NULL;
  const mxArray *c3_rhs112 = NULL;
  const mxArray *c3_lhs112 = NULL;
  const mxArray *c3_rhs113 = NULL;
  const mxArray *c3_lhs113 = NULL;
  const mxArray *c3_rhs114 = NULL;
  const mxArray *c3_lhs114 = NULL;
  const mxArray *c3_rhs115 = NULL;
  const mxArray *c3_lhs115 = NULL;
  const mxArray *c3_rhs116 = NULL;
  const mxArray *c3_lhs116 = NULL;
  const mxArray *c3_rhs117 = NULL;
  const mxArray *c3_lhs117 = NULL;
  const mxArray *c3_rhs118 = NULL;
  const mxArray *c3_lhs118 = NULL;
  const mxArray *c3_rhs119 = NULL;
  const mxArray *c3_lhs119 = NULL;
  const mxArray *c3_rhs120 = NULL;
  const mxArray *c3_lhs120 = NULL;
  const mxArray *c3_rhs121 = NULL;
  const mxArray *c3_lhs121 = NULL;
  const mxArray *c3_rhs122 = NULL;
  const mxArray *c3_lhs122 = NULL;
  const mxArray *c3_rhs123 = NULL;
  const mxArray *c3_lhs123 = NULL;
  const mxArray *c3_rhs124 = NULL;
  const mxArray *c3_lhs124 = NULL;
  const mxArray *c3_rhs125 = NULL;
  const mxArray *c3_lhs125 = NULL;
  const mxArray *c3_rhs126 = NULL;
  const mxArray *c3_lhs126 = NULL;
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 64);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  64);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 64);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 64);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c3_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "context",
                  "context", 65);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.isaUint"),
                  "name", "name", 65);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 65);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/isaUint.p"),
                  "resolved", "resolved", 65);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c3_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 66);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 66);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 66);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c3_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "context", "context", 67);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.unsignedClass"),
                  "name", "name", 67);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "resolved", "resolved", 67);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c3_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 68);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 68);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c3_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 69);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 69);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 69);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 69);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c3_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 70);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 70);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 70);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 70);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c3_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 71);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("intmax"), "name", "name", 71);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 71);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 71);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c3_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 72);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  72);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 72);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 72);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c3_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 73);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 73);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 73);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c3_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 74);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 74);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 74);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 74);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c3_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 75);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 75);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 75);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c3_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 76);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 76);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 76);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c3_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 77);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 77);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 77);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c3_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 78);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 78);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 78);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c3_rhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 79);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 79);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 79);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 79);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c3_rhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 80);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 80);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 80);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 80);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c3_rhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 81);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 81);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 81);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 81);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c3_rhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "context", "context", 82);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 82);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 82);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 82);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c3_rhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 83);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 83);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 83);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 83);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c3_rhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 84);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 84);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 84);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 84);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c3_rhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 85);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_ixamax"), "name", "name",
                  85);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "resolved", "resolved", 85);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c3_rhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "context", "context", 86);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 86);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 86);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c3_rhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "context", "context", 87);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.ixamax"),
                  "name", "name", 87);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 87);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "resolved", "resolved", 87);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c3_rhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "context", "context", 88);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 88);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 88);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c3_rhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p!below_threshold"),
                  "context", "context", 89);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 89);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c3_rhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "context", "context", 90);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.refblas.ixamax"),
                  "name", "name", 90);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "resolved", "resolved", 90);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c3_rhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 91);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.refblas.xcabs1"),
                  "name", "name", 91);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c3_rhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "context", "context", 92);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("abs"), "name", "name", 92);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 92);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c3_rhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 93);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 93);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 93);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 93);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c3_rhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 94);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_xswap"), "name", "name",
                  94);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 94);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"),
                  "resolved", "resolved", 94);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980692U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c3_rhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"), "context",
                  "context", 95);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 95);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 95);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 95);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c3_rhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"), "context",
                  "context", 96);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.xswap"),
                  "name", "name", 96);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 96);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "resolved", "resolved", 96);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c3_rhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "context", "context", 97);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 97);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 97);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 97);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c3_rhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p!below_threshold"),
                  "context", "context", 98);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 98);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 98);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c3_rhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "context", "context", 99);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.refblas.xswap"),
                  "name", "name", 99);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "resolved", "resolved", 99);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c3_rhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 100);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("abs"), "name", "name", 100);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 100);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 100);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c3_rhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 101);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 101);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 101);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c3_rhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 102);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 102);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 102);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c3_rhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 103);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 103);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 103);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c3_rhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 104);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("intmax"), "name", "name", 104);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 104);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 104);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c3_rhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 105);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 105);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 105);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 105);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c3_rhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 106);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_div"), "name", "name", 106);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 106);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 106);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c3_rhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 107);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 107);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 107);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 107);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c3_rhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 108);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_xgeru"), "name", "name",
                  108);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"),
                  "resolved", "resolved", 108);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c3_rhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"), "context",
                  "context", 109);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 109);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 109);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 109);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c3_rhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"), "context",
                  "context", 110);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.xgeru"),
                  "name", "name", 110);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgeru.p"),
                  "resolved", "resolved", 110);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c3_rhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgeru.p"),
                  "context", "context", 111);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.xger"),
                  "name", "name", 111);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "resolved", "resolved", 111);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c3_rhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 112);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 112);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 112);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c3_rhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 113);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 113);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 113);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 113);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c3_rhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 114);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.refblas.xger"),
                  "name", "name", 114);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "resolved", "resolved", 114);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c3_rhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "context", "context", 115);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.refblas.xgerx"),
                  "name", "name", 115);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "resolved", "resolved", 115);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c3_rhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 116);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("abs"), "name", "name", 116);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 116);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 116);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c3_rhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 117);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 117);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 117);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c3_rhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 118);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 118);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 118);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c3_rhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 119);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 119);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 119);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 119);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c3_rhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 120);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 120);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 120);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 120);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c3_rhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 121);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("mrdivide"), "name", "name",
                  121);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 121);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 121);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c3_rhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 122);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 122);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 122);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 122);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c3_rhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 123);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("rdivide"), "name", "name", 123);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 123);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c3_rhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 124);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 124);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 124);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c3_rhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 125);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 125);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 125);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c3_rhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 126);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_div"), "name", "name", 126);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 126);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 126);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c3_rhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs126), "lhs", "lhs",
                  126);
  sf_mex_destroy(&c3_rhs64);
  sf_mex_destroy(&c3_lhs64);
  sf_mex_destroy(&c3_rhs65);
  sf_mex_destroy(&c3_lhs65);
  sf_mex_destroy(&c3_rhs66);
  sf_mex_destroy(&c3_lhs66);
  sf_mex_destroy(&c3_rhs67);
  sf_mex_destroy(&c3_lhs67);
  sf_mex_destroy(&c3_rhs68);
  sf_mex_destroy(&c3_lhs68);
  sf_mex_destroy(&c3_rhs69);
  sf_mex_destroy(&c3_lhs69);
  sf_mex_destroy(&c3_rhs70);
  sf_mex_destroy(&c3_lhs70);
  sf_mex_destroy(&c3_rhs71);
  sf_mex_destroy(&c3_lhs71);
  sf_mex_destroy(&c3_rhs72);
  sf_mex_destroy(&c3_lhs72);
  sf_mex_destroy(&c3_rhs73);
  sf_mex_destroy(&c3_lhs73);
  sf_mex_destroy(&c3_rhs74);
  sf_mex_destroy(&c3_lhs74);
  sf_mex_destroy(&c3_rhs75);
  sf_mex_destroy(&c3_lhs75);
  sf_mex_destroy(&c3_rhs76);
  sf_mex_destroy(&c3_lhs76);
  sf_mex_destroy(&c3_rhs77);
  sf_mex_destroy(&c3_lhs77);
  sf_mex_destroy(&c3_rhs78);
  sf_mex_destroy(&c3_lhs78);
  sf_mex_destroy(&c3_rhs79);
  sf_mex_destroy(&c3_lhs79);
  sf_mex_destroy(&c3_rhs80);
  sf_mex_destroy(&c3_lhs80);
  sf_mex_destroy(&c3_rhs81);
  sf_mex_destroy(&c3_lhs81);
  sf_mex_destroy(&c3_rhs82);
  sf_mex_destroy(&c3_lhs82);
  sf_mex_destroy(&c3_rhs83);
  sf_mex_destroy(&c3_lhs83);
  sf_mex_destroy(&c3_rhs84);
  sf_mex_destroy(&c3_lhs84);
  sf_mex_destroy(&c3_rhs85);
  sf_mex_destroy(&c3_lhs85);
  sf_mex_destroy(&c3_rhs86);
  sf_mex_destroy(&c3_lhs86);
  sf_mex_destroy(&c3_rhs87);
  sf_mex_destroy(&c3_lhs87);
  sf_mex_destroy(&c3_rhs88);
  sf_mex_destroy(&c3_lhs88);
  sf_mex_destroy(&c3_rhs89);
  sf_mex_destroy(&c3_lhs89);
  sf_mex_destroy(&c3_rhs90);
  sf_mex_destroy(&c3_lhs90);
  sf_mex_destroy(&c3_rhs91);
  sf_mex_destroy(&c3_lhs91);
  sf_mex_destroy(&c3_rhs92);
  sf_mex_destroy(&c3_lhs92);
  sf_mex_destroy(&c3_rhs93);
  sf_mex_destroy(&c3_lhs93);
  sf_mex_destroy(&c3_rhs94);
  sf_mex_destroy(&c3_lhs94);
  sf_mex_destroy(&c3_rhs95);
  sf_mex_destroy(&c3_lhs95);
  sf_mex_destroy(&c3_rhs96);
  sf_mex_destroy(&c3_lhs96);
  sf_mex_destroy(&c3_rhs97);
  sf_mex_destroy(&c3_lhs97);
  sf_mex_destroy(&c3_rhs98);
  sf_mex_destroy(&c3_lhs98);
  sf_mex_destroy(&c3_rhs99);
  sf_mex_destroy(&c3_lhs99);
  sf_mex_destroy(&c3_rhs100);
  sf_mex_destroy(&c3_lhs100);
  sf_mex_destroy(&c3_rhs101);
  sf_mex_destroy(&c3_lhs101);
  sf_mex_destroy(&c3_rhs102);
  sf_mex_destroy(&c3_lhs102);
  sf_mex_destroy(&c3_rhs103);
  sf_mex_destroy(&c3_lhs103);
  sf_mex_destroy(&c3_rhs104);
  sf_mex_destroy(&c3_lhs104);
  sf_mex_destroy(&c3_rhs105);
  sf_mex_destroy(&c3_lhs105);
  sf_mex_destroy(&c3_rhs106);
  sf_mex_destroy(&c3_lhs106);
  sf_mex_destroy(&c3_rhs107);
  sf_mex_destroy(&c3_lhs107);
  sf_mex_destroy(&c3_rhs108);
  sf_mex_destroy(&c3_lhs108);
  sf_mex_destroy(&c3_rhs109);
  sf_mex_destroy(&c3_lhs109);
  sf_mex_destroy(&c3_rhs110);
  sf_mex_destroy(&c3_lhs110);
  sf_mex_destroy(&c3_rhs111);
  sf_mex_destroy(&c3_lhs111);
  sf_mex_destroy(&c3_rhs112);
  sf_mex_destroy(&c3_lhs112);
  sf_mex_destroy(&c3_rhs113);
  sf_mex_destroy(&c3_lhs113);
  sf_mex_destroy(&c3_rhs114);
  sf_mex_destroy(&c3_lhs114);
  sf_mex_destroy(&c3_rhs115);
  sf_mex_destroy(&c3_lhs115);
  sf_mex_destroy(&c3_rhs116);
  sf_mex_destroy(&c3_lhs116);
  sf_mex_destroy(&c3_rhs117);
  sf_mex_destroy(&c3_lhs117);
  sf_mex_destroy(&c3_rhs118);
  sf_mex_destroy(&c3_lhs118);
  sf_mex_destroy(&c3_rhs119);
  sf_mex_destroy(&c3_lhs119);
  sf_mex_destroy(&c3_rhs120);
  sf_mex_destroy(&c3_lhs120);
  sf_mex_destroy(&c3_rhs121);
  sf_mex_destroy(&c3_lhs121);
  sf_mex_destroy(&c3_rhs122);
  sf_mex_destroy(&c3_lhs122);
  sf_mex_destroy(&c3_rhs123);
  sf_mex_destroy(&c3_lhs123);
  sf_mex_destroy(&c3_rhs124);
  sf_mex_destroy(&c3_lhs124);
  sf_mex_destroy(&c3_rhs125);
  sf_mex_destroy(&c3_lhs125);
  sf_mex_destroy(&c3_rhs126);
  sf_mex_destroy(&c3_lhs126);
}

static real_T c3_mpower(SFc3_ctrl_studentInstanceStruct *chartInstance, real_T
  c3_a)
{
  real_T c3_b_a;
  real_T c3_c_a;
  real_T c3_ak;
  real_T c3_d_a;
  c3_b_a = c3_a;
  c3_c_a = c3_b_a;
  c3_eml_scalar_eg(chartInstance);
  c3_ak = c3_c_a;
  c3_d_a = c3_ak;
  c3_eml_scalar_eg(chartInstance);
  return c3_d_a * c3_d_a;
}

static void c3_eml_scalar_eg(SFc3_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real_T c3_abs(SFc3_ctrl_studentInstanceStruct *chartInstance, real_T c3_x)
{
  real_T c3_b_x;
  (void)chartInstance;
  c3_b_x = c3_x;
  return muDoubleScalarAbs(c3_b_x);
}

static void c3_b_eml_scalar_eg(SFc3_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_threshold(SFc3_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_c_eml_scalar_eg(SFc3_ctrl_studentInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_h_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i126;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i126, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i126;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_i_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_ctrl_student, const char_T
  *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_ctrl_student), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_ctrl_student);
  return c3_y;
}

static uint8_T c3_j_emlrt_marshallIn(SFc3_ctrl_studentInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_ctrl_studentInstanceStruct *chartInstance)
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

void sf_c3_ctrl_student_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(654943462U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2218326874U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(720764335U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(450578774U);
}

mxArray *sf_c3_ctrl_student_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("RBKWvAYPyF1ddZWhBeoTMG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

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
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
      pr[1] = (double)(2);
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
      pr[0] = (double)(2);
      pr[1] = (double)(2);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
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
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_ctrl_student_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_ctrl_student_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c3_ctrl_student(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[16],T\"e1\",},{M[1],M[17],T\"e2\",},{M[1],M[5],T\"tau\",},{M[8],M[0],T\"is_active_c3_ctrl_student\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_ctrl_student_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_ctrl_studentInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc3_ctrl_studentInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ctrl_studentMachineNumber_,
           3,
           1,
           1,
           0,
           11,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"nu");
          _SFD_SET_DATA_PROPS(1,2,0,1,"tau");
          _SFD_SET_DATA_PROPS(2,1,1,0,"eta");
          _SFD_SET_DATA_PROPS(3,1,1,0,"pd");
          _SFD_SET_DATA_PROPS(4,1,1,0,"pd_dot");
          _SFD_SET_DATA_PROPS(5,1,1,0,"pd_ddot");
          _SFD_SET_DATA_PROPS(6,1,1,0,"ly");
          _SFD_SET_DATA_PROPS(7,1,1,0,"Kp");
          _SFD_SET_DATA_PROPS(8,1,1,0,"Kd");
          _SFD_SET_DATA_PROPS(9,2,0,1,"e1");
          _SFD_SET_DATA_PROPS(10,2,0,1,"e2");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,3119);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)
            c3_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        {
          real_T (*c3_nu)[3];
          real_T (*c3_tau)[3];
          real_T (*c3_eta)[3];
          real_T (*c3_pd)[2];
          real_T (*c3_pd_dot)[2];
          real_T (*c3_pd_ddot)[2];
          real_T (*c3_ly)[2];
          real_T (*c3_Kp)[4];
          real_T (*c3_Kd)[4];
          real_T (*c3_e1)[2];
          real_T (*c3_e2)[2];
          c3_e2 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 3);
          c3_e1 = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 2);
          c3_Kd = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 7);
          c3_Kp = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 6);
          c3_ly = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
          c3_pd_ddot = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 4);
          c3_pd_dot = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 3);
          c3_pd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
          c3_eta = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c3_tau = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c3_nu = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_nu);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_tau);
          _SFD_SET_DATA_VALUE_PTR(2U, *c3_eta);
          _SFD_SET_DATA_VALUE_PTR(3U, *c3_pd);
          _SFD_SET_DATA_VALUE_PTR(4U, *c3_pd_dot);
          _SFD_SET_DATA_VALUE_PTR(5U, *c3_pd_ddot);
          _SFD_SET_DATA_VALUE_PTR(6U, *c3_ly);
          _SFD_SET_DATA_VALUE_PTR(7U, *c3_Kp);
          _SFD_SET_DATA_VALUE_PTR(8U, *c3_Kd);
          _SFD_SET_DATA_VALUE_PTR(9U, *c3_e1);
          _SFD_SET_DATA_VALUE_PTR(10U, *c3_e2);
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
  return "krxVy90t8127TPR1sqEDLE";
}

static void sf_opaque_initialize_c3_ctrl_student(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_ctrl_studentInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_ctrl_student((SFc3_ctrl_studentInstanceStruct*)
    chartInstanceVar);
  initialize_c3_ctrl_student((SFc3_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_ctrl_student(void *chartInstanceVar)
{
  enable_c3_ctrl_student((SFc3_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_ctrl_student(void *chartInstanceVar)
{
  disable_c3_ctrl_student((SFc3_ctrl_studentInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_ctrl_student(void *chartInstanceVar)
{
  sf_gateway_c3_ctrl_student((SFc3_ctrl_studentInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_ctrl_student(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_ctrl_student
    ((SFc3_ctrl_studentInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_ctrl_student();/* state var info */
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

extern void sf_internal_set_sim_state_c3_ctrl_student(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c3_ctrl_student();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_ctrl_student((SFc3_ctrl_studentInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_ctrl_student(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_ctrl_student(S);
}

static void sf_opaque_set_sim_state_c3_ctrl_student(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c3_ctrl_student(S, st);
}

static void sf_opaque_terminate_c3_ctrl_student(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_ctrl_studentInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ctrl_student_optimization_info();
    }

    finalize_c3_ctrl_student((SFc3_ctrl_studentInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_ctrl_student((SFc3_ctrl_studentInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_ctrl_student(SimStruct *S)
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
    initialize_params_c3_ctrl_student((SFc3_ctrl_studentInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ctrl_student_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1970360386U));
  ssSetChecksum1(S,(1422036783U));
  ssSetChecksum2(S,(255217610U));
  ssSetChecksum3(S,(1485831321U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_ctrl_student(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_ctrl_student(SimStruct *S)
{
  SFc3_ctrl_studentInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc3_ctrl_studentInstanceStruct *)utMalloc(sizeof
    (SFc3_ctrl_studentInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_ctrl_studentInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_ctrl_student;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_ctrl_student;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_ctrl_student;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_ctrl_student;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_ctrl_student;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_ctrl_student;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_ctrl_student;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_ctrl_student;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_ctrl_student;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_ctrl_student;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_ctrl_student;
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

void c3_ctrl_student_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_ctrl_student(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_ctrl_student(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_ctrl_student(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_ctrl_student_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
