/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 5.254
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Jul 26 10:42:54 2022
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

/* Exported data definition */

/* Data with Exported storage */
real_T rtDriver_req;                   /* '<Root>/driver_request' */
real_T rtSteeringangle;                /* '<Root>/delta' */
real_T rtTm_rl;                        /* '<Root>/Tmax_rl' */
real_T rtTm_rl_a;                      /* '<Root>/Tm_rl' */
real_T rtTm_rr;                        /* '<Root>/Tmax_rr' */
real_T rtTm_rr_m;                      /* '<Root>/Tm_rr' */
real_T rtomega_rl;                     /* '<Root>/omega_rl' */
real_T rtomega_rr;                     /* '<Root>/omega_rr' */
real_T rtsignal11;                     /* '<Root>/map_tv' */
real_T rtsignal12;                     /* '<Root>/map_sc' */
real_T rtsignal13;                     /* '<Root>/Brake' */
real_T rtu_bar;                        /* '<Root>/u_bar' */
real_T rtyaw_rate;                     /* '<Root>/Omega' */
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
void Torque_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  real_T rtb_Gain;
  real_T rtb_IProdOut;
  real_T rtb_PProdOut;
  real_T rtb_SumFdbk;
  real_T rtb_Switch2_ou;
  real_T rtb_T_diff_k;
  real_T rtb_T_rr;
  real_T rtb_delta_F;
  real_T rtb_delta_F_tmp;
  int8_T rtb_IProdOut_0;
  int8_T rtb_T_diff_o;

  /* MATLAB Function: '<S2>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(rtSteeringangle, 10.0);
  rtb_SumFdbk = pow(rtSteeringangle, 9.0);
  rtb_T_diff_k = pow(rtSteeringangle, 8.0);
  rtb_delta_F = pow(rtSteeringangle, 7.0);
  rtb_T_rr = pow(rtSteeringangle, 6.0);
  rtb_Switch2_ou = pow(rtSteeringangle, 5.0);
  rtb_Gain = pow(rtSteeringangle, 4.0);
  rtb_PProdOut = pow(rtSteeringangle, 3.0);
  rtb_delta_F_tmp = rtSteeringangle * rtSteeringangle;
  rtb_delta_F = (((((((((((-2.511353952E-8 * rtb_IProdOut + 1.204729921E-7 *
    rtb_SumFdbk) - 2.613187764E-7 * rtb_T_diff_k) + 1.437082334E-6 * rtb_delta_F)
                        - 7.12221471E-6 * rtb_T_rr) + 4.68525841E-5 *
                       rtb_Switch2_ou) - 0.0001855092357 * rtb_Gain) +
                     0.001856824887 * rtb_PProdOut) - rtb_delta_F_tmp *
                    0.006374606899) + 0.2126142315 * rtSteeringangle) + 3.3E-9)
                 + ((((((((((2.5259036849999997E-8 * rtb_IProdOut +
    1.206067049E-7 * rtb_SumFdbk) + 2.599089767E-7 * rtb_T_diff_k) +
    1.435718737E-6 * rtb_delta_F) + 7.1264231E-6 * rtb_T_rr) + 4.685692282E-5 *
    rtb_Switch2_ou) + 0.0001855053075 * rtb_Gain) + 0.001856820364 *
                       rtb_PProdOut) + rtb_delta_F_tmp * 0.006374607119) +
                     0.2126142321 * rtSteeringangle) - 3.3E-9)) / 2.0;

  /* Lookup_n-D: '<S9>/1-D Lookup Table2' incorporates:
   *  Inport: '<Root>/map_tv'
   *  Lookup_n-D: '<S2>/1-D Lookup Table2'
   */
  rtb_T_rr = look1_binlxpw(rtsignal11, rtConstP.pooled1, rtConstP.pooled1, 1U);

  /* Product: '<S9>/Product' incorporates:
   *  Constant: '<S9>/Constant'
   *  Lookup_n-D: '<S9>/1-D Lookup Table2'
   */
  rtb_Switch2_ou = 729.50929802955659 * rtb_T_rr;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S8>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S8>/K_us_table'
   *  MATLAB Function: '<S8>/Yaw-Rate'
   */
  rtb_IProdOut = rtb_delta_F * rtu_bar / (rtu_bar * rtu_bar * look1_binlxpw
    (rtu_bar, rtConstP.K_us_table_bp01Data, rtConstP.K_us_table_tableData, 6U) +
    1.53) - rtyaw_rate;

  /* Product: '<S51>/PProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S9>/P_table'
   */
  rtb_PProdOut = rtb_IProdOut * look1_binlxpw(rtu_bar, rtConstP.pooled2,
    rtConstP.P_table_tableData, 7U);

  /* Sum: '<S57>/Sum Fdbk' */
  rtb_SumFdbk = rtb_PProdOut + rtDW->Integrator_DSTATE;

  /* Switch: '<S39>/Switch' incorporates:
   *  Gain: '<S9>/Gain'
   *  RelationalOperator: '<S39>/u_GTE_up'
   *  RelationalOperator: '<S39>/u_GT_lo'
   *  Switch: '<S39>/Switch1'
   */
  if (rtb_SumFdbk >= rtb_Switch2_ou) {
    rtb_T_diff_k = rtb_Switch2_ou;
  } else if (rtb_SumFdbk > -rtb_Switch2_ou) {
    /* Switch: '<S39>/Switch1' */
    rtb_T_diff_k = rtb_SumFdbk;
  } else {
    rtb_T_diff_k = -rtb_Switch2_ou;
  }

  /* End of Switch: '<S39>/Switch' */

  /* Sum: '<S39>/Diff' */
  rtb_T_diff_k = rtb_SumFdbk - rtb_T_diff_k;

  /* Product: '<S43>/IProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S9>/I_table'
   */
  rtb_IProdOut *= look1_binlxpw(rtu_bar, rtConstP.pooled2,
    rtConstP.I_table_tableData, 7U);

  /* Switch: '<S36>/Switch1' incorporates:
   *  Constant: '<S36>/Constant'
   *  Constant: '<S36>/Constant2'
   *  Constant: '<S36>/Constant5'
   *  RelationalOperator: '<S36>/fix for DT propagation issue'
   */
  if (rtb_T_diff_k > 0.0) {
    rtb_T_diff_o = 1;
  } else {
    rtb_T_diff_o = -1;
  }

  /* End of Switch: '<S36>/Switch1' */

  /* Switch: '<S36>/Switch2' incorporates:
   *  Constant: '<S36>/Constant3'
   *  Constant: '<S36>/Constant4'
   *  Constant: '<S36>/Constant5'
   *  RelationalOperator: '<S36>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > 0.0) {
    rtb_IProdOut_0 = 1;
  } else {
    rtb_IProdOut_0 = -1;
  }

  /* End of Switch: '<S36>/Switch2' */

  /* Switch: '<S36>/Switch' incorporates:
   *  Constant: '<S36>/Constant1'
   *  Constant: '<S36>/Constant5'
   *  Logic: '<S36>/AND3'
   *  RelationalOperator: '<S36>/Equal1'
   *  RelationalOperator: '<S36>/Relational Operator'
   */
  if ((rtb_T_diff_k != 0.0) && (rtb_T_diff_o == rtb_IProdOut_0)) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S36>/Switch' */

  /* DiscreteIntegrator: '<S46>/Integrator' */
  rtb_SumFdbk = 0.0005 * rtb_IProdOut + rtDW->Integrator_DSTATE;

  /* Sum: '<S56>/Sum' */
  rtb_T_diff_k = rtb_PProdOut + rtb_SumFdbk;

  /* Switch: '<S54>/Switch2' incorporates:
   *  RelationalOperator: '<S54>/LowerRelop1'
   */
  if (rtb_T_diff_k <= rtb_Switch2_ou) {
    /* Switch: '<S54>/Switch' incorporates:
     *  Gain: '<S9>/Gain'
     *  RelationalOperator: '<S54>/UpperRelop'
     */
    if (rtb_T_diff_k < -rtb_Switch2_ou) {
      rtb_Switch2_ou = -rtb_Switch2_ou;
    } else {
      rtb_Switch2_ou = rtb_T_diff_k;
    }

    /* End of Switch: '<S54>/Switch' */
  }

  /* End of Switch: '<S54>/Switch2' */

  /* Product: '<S2>/Product1' incorporates:
   *  Abs: '<S2>/Abs'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S2>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *  Product: '<S2>/Product2'
   *  RelationalOperator: '<S6>/Compare'
   */
  rtb_T_diff_k = (fabs(rtb_delta_F) >= 0.034906585039886591 ? rtb_Switch2_ou :
                  0.0) * 0.0753931446090652 * rtb_T_rr;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Sum: '<S1>/Add'
   */
  rtb_Switch2_ou = (rtTm_rl + rtTm_rr) * 0.5;

  /* Product: '<S1>/Product2' incorporates:
   *  Inport: '<Root>/driver_request'
   */
  rtb_delta_F = rtDriver_req * rtb_Switch2_ou;

  /* Sum: '<S1>/Sum2' */
  rtb_T_rr = rtb_T_diff_k + rtb_delta_F;

  /* Sum: '<S1>/Sum3' */
  rtb_T_diff_k = rtb_delta_F - rtb_T_diff_k;

  /* MATLAB Function: '<S1>/Saturation block' incorporates:
   *  Inport: '<Root>/u_bar'
   */
  if (rtu_bar > 5.0) {
    if (rtb_T_rr > rtb_Switch2_ou) {
      rtb_Gain = rtb_T_rr - rtb_Switch2_ou;
    } else {
      rtb_Gain = fmin(rtb_T_rr, 0.0);
    }

    if (rtb_T_diff_k > rtb_Switch2_ou) {
      rtb_Switch2_ou = rtb_T_diff_k - rtb_Switch2_ou;
    } else if (rtb_T_rr < 0.0) {
      rtb_Switch2_ou = rtb_T_diff_k;
    } else {
      rtb_Switch2_ou = 0.0;
    }

    if (fabs(rtb_Gain) >= fabs(rtb_Switch2_ou)) {
      rtb_delta_F = rtb_T_rr - rtb_Gain;
      rtb_T_diff_k -= rtb_Gain;
    } else {
      rtb_delta_F = rtb_T_rr - rtb_Switch2_ou;
      rtb_T_diff_k -= rtb_Switch2_ou;
    }
  } else {
    rtb_T_diff_k = rtb_delta_F;
  }

  /* End of MATLAB Function: '<S1>/Saturation block' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_delta_F > rtTm_rl) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m = rtTm_rl;
  } else if (rtb_delta_F < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant2'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S4>/Switch'
     */
    rtTm_rr_m = rtb_delta_F;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S3>/LowerRelop1'
   *  RelationalOperator: '<S3>/UpperRelop'
   *  Switch: '<S3>/Switch'
   */
  if (rtb_T_diff_k > rtTm_rr) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a = rtTm_rr;
  } else if (rtb_T_diff_k < 0.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S3>/Switch'
     */
    rtTm_rl_a = rtb_T_diff_k;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Update for DiscreteIntegrator: '<S46>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0005 * rtb_IProdOut + rtb_SumFdbk;
}

/* Model initialize function */
void Torque_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;

  /* Registration code */

  /* Storage classes */
  rtTm_rr_m = 0.0;
  rtTm_rl_a = 0.0;

  /* Storage classes */
  rtDriver_req = 0.0;
  rtu_bar = 0.0;
  rtomega_rr = 0.0;
  rtomega_rl = 0.0;
  rtyaw_rate = 0.0;
  rtSteeringangle = 0.0;
  rtsignal13 = 0.0;
  rtTm_rl = 0.0;
  rtTm_rr = 0.0;
  rtsignal11 = 0.0;
  rtsignal12 = 0.0;

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* InitializeConditions for DiscreteIntegrator: '<S46>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
