/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 5.241
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sat May 21 16:04:27 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Torque.h"
#include <math.h>
#include "rtwtypes.h"

static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/* Model step function */
void Torque_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T rtU_u_bar,
                 real_T rtU_yaw_rate, real_T rtU_Steeringangle, real_T rtU_Tm_rl,
                 real_T rtU_Tm_rr, real_T rtU_map_tv, real_T *rtY_Tm_rr, real_T *
                 rtY_Tm_rl)
{
  DW *rtDW = rtM->dwork;
  real_T rtb_Gain;
  real_T rtb_IProdOut;
  real_T rtb_PProdOut;
  real_T rtb_SumFdbk;
  real_T rtb_Switch2_k;
  real_T rtb_T_diff_p;
  real_T rtb_T_rr;
  real_T rtb_delta_F;
  real_T rtb_delta_F_tmp;
  int8_T rtb_IProdOut_0;
  int8_T rtb_T_diff_a;

  /* MATLAB Function: '<S6>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(rtU_Steeringangle, 10.0);
  rtb_SumFdbk = pow(rtU_Steeringangle, 9.0);
  rtb_T_diff_p = pow(rtU_Steeringangle, 8.0);
  rtb_delta_F = pow(rtU_Steeringangle, 7.0);
  rtb_T_rr = pow(rtU_Steeringangle, 6.0);
  rtb_Switch2_k = pow(rtU_Steeringangle, 5.0);
  rtb_Gain = pow(rtU_Steeringangle, 4.0);
  rtb_PProdOut = pow(rtU_Steeringangle, 3.0);
  rtb_delta_F_tmp = rtU_Steeringangle * rtU_Steeringangle;
  rtb_delta_F = (((((((((((-2.511353952E-8 * rtb_IProdOut + 1.204729921E-7 *
    rtb_SumFdbk) - 2.613187764E-7 * rtb_T_diff_p) + 1.437082334E-6 * rtb_delta_F)
                        - 7.12221471E-6 * rtb_T_rr) + 4.68525841E-5 *
                       rtb_Switch2_k) - 0.0001855092357 * rtb_Gain) +
                     0.001856824887 * rtb_PProdOut) - rtb_delta_F_tmp *
                    0.006374606899) + 0.2126142315 * rtU_Steeringangle) + 3.3E-9)
                 + ((((((((((2.5259036849999997E-8 * rtb_IProdOut +
    1.206067049E-7 * rtb_SumFdbk) + 2.599089767E-7 * rtb_T_diff_p) +
    1.435718737E-6 * rtb_delta_F) + 7.1264231E-6 * rtb_T_rr) + 4.685692282E-5 *
    rtb_Switch2_k) + 0.0001855053075 * rtb_Gain) + 0.001856820364 * rtb_PProdOut)
                      + rtb_delta_F_tmp * 0.006374607119) + 0.2126142321 *
                     rtU_Steeringangle) - 3.3E-9)) / 2.0;

  /* Lookup_n-D: '<S10>/1-D Lookup Table2' incorporates:
   *  Inport: '<Root>/map_tv'
   *  Lookup_n-D: '<S2>/1-D Lookup Table2'
   */
  rtb_T_rr = look1_binlxpw(rtU_map_tv, rtConstP.pooled1, rtConstP.pooled1, 1U);

  /* Product: '<S10>/Product' incorporates:
   *  Constant: '<S10>/Constant'
   *  Lookup_n-D: '<S10>/1-D Lookup Table2'
   */
  rtb_Switch2_k = 729.50929802955659 * rtb_T_rr;

  /* Sum: '<S6>/Sum1' incorporates:
   *  Constant: '<S9>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S9>/K_us_table'
   *  MATLAB Function: '<S9>/Yaw-Rate'
   */
  rtb_IProdOut = rtb_delta_F * rtU_u_bar / (rtU_u_bar * rtU_u_bar *
    look1_binlxpw(rtU_u_bar, rtConstP.K_us_table_bp01Data,
                  rtConstP.K_us_table_tableData, 9U) + 1.53) - rtU_yaw_rate;

  /* Product: '<S52>/PProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S10>/P_table'
   */
  rtb_PProdOut = rtb_IProdOut * look1_binlxpw(rtU_u_bar, rtConstP.pooled2,
    rtConstP.P_table_tableData, 7U);

  /* Sum: '<S58>/Sum Fdbk' */
  rtb_SumFdbk = rtb_PProdOut + rtDW->Integrator_DSTATE;

  /* Switch: '<S40>/Switch' incorporates:
   *  Gain: '<S10>/Gain'
   *  RelationalOperator: '<S40>/u_GTE_up'
   *  RelationalOperator: '<S40>/u_GT_lo'
   *  Switch: '<S40>/Switch1'
   */
  if (rtb_SumFdbk >= rtb_Switch2_k) {
    rtb_T_diff_p = rtb_Switch2_k;
  } else if (rtb_SumFdbk > -rtb_Switch2_k) {
    /* Switch: '<S40>/Switch1' */
    rtb_T_diff_p = rtb_SumFdbk;
  } else {
    rtb_T_diff_p = -rtb_Switch2_k;
  }

  /* End of Switch: '<S40>/Switch' */

  /* Sum: '<S40>/Diff' */
  rtb_T_diff_p = rtb_SumFdbk - rtb_T_diff_p;

  /* Product: '<S44>/IProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S10>/I_table'
   */
  rtb_IProdOut *= look1_binlxpw(rtU_u_bar, rtConstP.pooled2,
    rtConstP.I_table_tableData, 7U);

  /* Switch: '<S37>/Switch1' incorporates:
   *  Constant: '<S37>/Constant'
   *  Constant: '<S37>/Constant2'
   *  Constant: '<S37>/Constant5'
   *  RelationalOperator: '<S37>/fix for DT propagation issue'
   */
  if (rtb_T_diff_p > 0.0) {
    rtb_T_diff_a = 1;
  } else {
    rtb_T_diff_a = -1;
  }

  /* End of Switch: '<S37>/Switch1' */

  /* Switch: '<S37>/Switch2' incorporates:
   *  Constant: '<S37>/Constant3'
   *  Constant: '<S37>/Constant4'
   *  Constant: '<S37>/Constant5'
   *  RelationalOperator: '<S37>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > 0.0) {
    rtb_IProdOut_0 = 1;
  } else {
    rtb_IProdOut_0 = -1;
  }

  /* End of Switch: '<S37>/Switch2' */

  /* Switch: '<S37>/Switch' incorporates:
   *  Constant: '<S37>/Constant1'
   *  Constant: '<S37>/Constant5'
   *  Logic: '<S37>/AND3'
   *  RelationalOperator: '<S37>/Equal1'
   *  RelationalOperator: '<S37>/Relational Operator'
   */
  if ((rtb_T_diff_p != 0.0) && (rtb_T_diff_a == rtb_IProdOut_0)) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S37>/Switch' */

  /* DiscreteIntegrator: '<S47>/Integrator' */
  rtb_SumFdbk = 0.0005 * rtb_IProdOut + rtDW->Integrator_DSTATE;

  /* Sum: '<S57>/Sum' */
  rtb_T_diff_p = rtb_PProdOut + rtb_SumFdbk;

  /* Switch: '<S55>/Switch2' incorporates:
   *  RelationalOperator: '<S55>/LowerRelop1'
   */
  if (rtb_T_diff_p <= rtb_Switch2_k) {
    /* Switch: '<S55>/Switch' incorporates:
     *  Gain: '<S10>/Gain'
     *  RelationalOperator: '<S55>/UpperRelop'
     */
    if (rtb_T_diff_p < -rtb_Switch2_k) {
      rtb_Switch2_k = -rtb_Switch2_k;
    } else {
      rtb_Switch2_k = rtb_T_diff_p;
    }

    /* End of Switch: '<S55>/Switch' */
  }

  /* End of Switch: '<S55>/Switch2' */

  /* Product: '<S2>/Product2' incorporates:
   *  Constant: '<S7>/Constant'
   *  Gain: '<S2>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)1'
   *  Product: '<S6>/Product2'
   *  RelationalOperator: '<S7>/Compare'
   */
  rtb_T_diff_p = (rtb_delta_F >= 0.034906585039886591 ? rtb_Switch2_k : 0.0) *
    0.0753931446090652 * rtb_T_rr;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Sum: '<S1>/Add'
   */
  rtb_delta_F = (rtU_Tm_rl + rtU_Tm_rr) * 0.5 * rtU_Driver_req;

  /* Sum: '<S1>/Sum2' */
  rtb_T_rr = rtb_T_diff_p + rtb_delta_F;

  /* Sum: '<S1>/Sum3' */
  rtb_T_diff_p = rtb_delta_F - rtb_T_diff_p;

  /* MATLAB Function: '<S1>/Saturation block' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/u_bar'
   */
  if (rtU_u_bar > 5.0) {
    if (rtb_T_rr > rtU_Tm_rl) {
      rtb_Switch2_k = rtb_T_rr - rtU_Tm_rl;
    } else {
      rtb_Switch2_k = fmin(rtb_T_rr, 0.0);
    }

    if (rtb_T_diff_p > rtU_Tm_rl) {
      rtb_Gain = rtb_T_diff_p - rtU_Tm_rl;
    } else if (rtb_T_rr < 0.0) {
      rtb_Gain = rtb_T_diff_p;
    } else {
      rtb_Gain = 0.0;
    }

    if (fabs(rtb_Switch2_k) >= fabs(rtb_Gain)) {
      rtb_delta_F = rtb_T_rr - rtb_Switch2_k;
      rtb_T_diff_p += rtb_Switch2_k;
    } else {
      rtb_delta_F = rtb_T_rr + rtb_Gain;
      rtb_T_diff_p -= rtb_Gain;
    }
  } else {
    rtb_T_diff_p = rtb_delta_F;
  }

  /* End of MATLAB Function: '<S1>/Saturation block' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_delta_F > rtU_Tm_rl) {
    /* Outport: '<Root>/Tm_rr' */
    *rtY_Tm_rr = rtU_Tm_rl;
  } else if (rtb_delta_F < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    *rtY_Tm_rr = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S4>/Switch'
     */
    *rtY_Tm_rr = rtb_delta_F;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S3>/LowerRelop1'
   *  RelationalOperator: '<S3>/UpperRelop'
   *  Switch: '<S3>/Switch'
   */
  if (rtb_T_diff_p > rtU_Tm_rr) {
    /* Outport: '<Root>/Tm_rl' */
    *rtY_Tm_rl = rtU_Tm_rr;
  } else if (rtb_T_diff_p < 0.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    *rtY_Tm_rl = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S3>/Switch'
     */
    *rtY_Tm_rl = rtb_T_diff_p;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Update for DiscreteIntegrator: '<S47>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0005 * rtb_IProdOut + rtb_SumFdbk;
}

/* Model initialize function */
void Torque_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T
  *rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl, real_T *rtU_yaw_rate,
  real_T *rtU_Steeringangle, real_T *rtU_Brake, real_T *rtU_Tm_rl, real_T
  *rtU_Tm_rr, real_T *rtU_map_tv, real_T *rtU_map_sc, real_T *rtY_Tm_rr, real_T *
  rtY_Tm_rl)
{
  DW *rtDW = rtM->dwork;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  *rtU_Driver_req = 0.0;
  *rtU_u_bar = 0.0;
  *rtU_omega_rr = 0.0;
  *rtU_omega_rl = 0.0;
  *rtU_yaw_rate = 0.0;
  *rtU_Steeringangle = 0.0;
  *rtU_Brake = 0.0;
  *rtU_Tm_rl = 0.0;
  *rtU_Tm_rr = 0.0;
  *rtU_map_tv = 0.0;
  *rtU_map_sc = 0.0;

  /* external outputs */
  *rtY_Tm_rr = 0.0;
  *rtY_Tm_rl = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S47>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
