/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: All0.c
 *
 * Code generated for Simulink model 'All0'.
 *
 * Model version                  : 5.254
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Jul 26 10:41:27 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "All0.h"
#include "rtwtypes.h"
#include <math.h>

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
static real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex);
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda);
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

static real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T found;
    uint32_T iLeft;
    uint32_T iRght;

    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = ((bpIdx + iLeft) - 1U) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = ((bpIdx + iRght) + 1U) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex;
    frac = 0.0;
  }

  prevIndex[0U] = bpIdx;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  if (bpIdx == maxIndex) {
    y = table[bpIdx];
  } else {
    real_T yL_0d0;
    yL_0d0 = table[bpIdx];
    y = (table[bpIdx + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

/*
 * Output and update for atomic system:
 *    '<S65>/Slip_est1'
 *    '<S66>/Slip_est2'
 */
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda)
{
  real_T Vmax;
  Vmax = fmax(fabs(rtu_u_bar), fabs(rtu_omegaR));
  if (Vmax > rtu_Vlow) {
    *rty_lambda = fabs((rtu_u_bar - rtu_omegaR) / Vmax);
  } else {
    *rty_lambda = fabs((rtu_u_bar - rtu_omegaR) * 2.0 / (Vmax * Vmax / rtu_Vlow
      + rtu_Vlow));
  }
}

/* Model step function */
void All0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  real_T rtb_Add_g;
  real_T rtb_Gain;
  real_T rtb_IProdOut;
  real_T rtb_Product;
  real_T rtb_Subtract;
  real_T rtb_Sum;
  real_T rtb_SumFdbk;
  real_T rtb_Switch2_a;
  real_T rtb_T_rl;
  real_T rtb_delta_F;
  real_T rtb_lambda;
  real_T rtb_vms;
  real_T rtb_vms_n;
  int8_T rtb_IProdOut_0;
  int8_T rtb_Subtract_0;

  /* MATLAB Function: '<S2>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(rtSteeringangle, 10.0);
  rtb_SumFdbk = pow(rtSteeringangle, 9.0);
  rtb_delta_F = pow(rtSteeringangle, 8.0);
  rtb_T_rl = pow(rtSteeringangle, 7.0);
  rtb_Switch2_a = pow(rtSteeringangle, 6.0);
  rtb_Gain = pow(rtSteeringangle, 5.0);
  rtb_Sum = pow(rtSteeringangle, 4.0);
  rtb_Product = pow(rtSteeringangle, 3.0);
  rtb_lambda = rtSteeringangle * rtSteeringangle;
  rtb_delta_F = (((((((((((-2.511353952E-8 * rtb_IProdOut + 1.204729921E-7 *
    rtb_SumFdbk) - 2.613187764E-7 * rtb_delta_F) + 1.437082334E-6 * rtb_T_rl) -
                        7.12221471E-6 * rtb_Switch2_a) + 4.68525841E-5 *
                       rtb_Gain) - 0.0001855092357 * rtb_Sum) + 0.001856824887 *
                     rtb_Product) - rtb_lambda * 0.006374606899) + 0.2126142315 *
                   rtSteeringangle) + 3.3E-9) + ((((((((((2.5259036849999997E-8 *
    rtb_IProdOut + 1.206067049E-7 * rtb_SumFdbk) + 2.599089767E-7 * rtb_delta_F)
    + 1.435718737E-6 * rtb_T_rl) + 7.1264231E-6 * rtb_Switch2_a) +
    4.685692282E-5 * rtb_Gain) + 0.0001855053075 * rtb_Sum) + 0.001856820364 *
    rtb_Product) + rtb_lambda * 0.006374607119) + 0.2126142321 * rtSteeringangle)
    - 3.3E-9)) / 2.0;

  /* Lookup_n-D: '<S10>/1-D Lookup Table2' incorporates:
   *  Inport: '<Root>/map_tv'
   *  Lookup_n-D: '<S2>/1-D Lookup Table2'
   */
  rtb_T_rl = look1_binlxpw(rtsignal11, rtConstP.pooled2, rtConstP.pooled2, 1U);

  /* Product: '<S10>/Product' incorporates:
   *  Constant: '<S10>/Constant'
   *  Lookup_n-D: '<S10>/1-D Lookup Table2'
   */
  rtb_Switch2_a = 729.50929802955659 * rtb_T_rl;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S9>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S9>/K_us_table'
   *  MATLAB Function: '<S9>/Yaw-Rate'
   */
  rtb_IProdOut = rtb_delta_F * rtu_bar / (rtu_bar * rtu_bar * look1_binlxpw
    (rtu_bar, rtConstP.K_us_table_bp01Data, rtConstP.K_us_table_tableData, 6U) +
    1.53) - rtyaw_rate;

  /* Product: '<S52>/PProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S10>/P_table'
   */
  rtb_lambda = rtb_IProdOut * look1_binlxpw(rtu_bar, rtConstP.pooled9,
    rtConstP.P_table_tableData, 7U);

  /* Sum: '<S58>/Sum Fdbk' */
  rtb_SumFdbk = rtb_lambda + rtDW->Integrator_DSTATE;

  /* Switch: '<S40>/Switch' incorporates:
   *  Gain: '<S10>/Gain'
   *  RelationalOperator: '<S40>/u_GTE_up'
   *  RelationalOperator: '<S40>/u_GT_lo'
   *  Switch: '<S40>/Switch1'
   */
  if (rtb_SumFdbk >= rtb_Switch2_a) {
    rtb_Gain = rtb_Switch2_a;
  } else if (rtb_SumFdbk > -rtb_Switch2_a) {
    /* Switch: '<S40>/Switch1' */
    rtb_Gain = rtb_SumFdbk;
  } else {
    rtb_Gain = -rtb_Switch2_a;
  }

  /* End of Switch: '<S40>/Switch' */

  /* Sum: '<S40>/Diff' */
  rtb_Subtract = rtb_SumFdbk - rtb_Gain;

  /* Product: '<S44>/IProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S10>/I_table'
   */
  rtb_IProdOut *= look1_binlxpw(rtu_bar, rtConstP.pooled9,
    rtConstP.I_table_tableData, 7U);

  /* Switch: '<S37>/Switch1' incorporates:
   *  Constant: '<S37>/Constant'
   *  Constant: '<S37>/Constant2'
   *  Constant: '<S37>/Constant5'
   *  RelationalOperator: '<S37>/fix for DT propagation issue'
   */
  if (rtb_Subtract > 0.0) {
    rtb_Subtract_0 = 1;
  } else {
    rtb_Subtract_0 = -1;
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
  if ((rtb_Subtract != 0.0) && (rtb_Subtract_0 == rtb_IProdOut_0)) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S37>/Switch' */

  /* DiscreteIntegrator: '<S47>/Integrator' */
  rtb_SumFdbk = 0.0005 * rtb_IProdOut + rtDW->Integrator_DSTATE;

  /* Sum: '<S57>/Sum' */
  rtb_Sum = rtb_lambda + rtb_SumFdbk;

  /* Switch: '<S55>/Switch2' incorporates:
   *  RelationalOperator: '<S55>/LowerRelop1'
   */
  if (rtb_Sum <= rtb_Switch2_a) {
    /* Switch: '<S55>/Switch' incorporates:
     *  Gain: '<S10>/Gain'
     *  RelationalOperator: '<S55>/UpperRelop'
     */
    if (rtb_Sum < -rtb_Switch2_a) {
      rtb_Switch2_a = -rtb_Switch2_a;
    } else {
      rtb_Switch2_a = rtb_Sum;
    }

    /* End of Switch: '<S55>/Switch' */
  }

  /* End of Switch: '<S55>/Switch2' */

  /* Product: '<S2>/Product1' incorporates:
   *  Abs: '<S2>/Abs'
   *  Constant: '<S7>/Constant'
   *  Gain: '<S2>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)'
   *  Product: '<S2>/Product2'
   *  RelationalOperator: '<S7>/Compare'
   */
  rtb_Subtract = (fabs(rtb_delta_F) >= 0.034906585039886591 ? rtb_Switch2_a :
                  0.0) * 0.0753931446090652 * rtb_T_rl;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Sum: '<S1>/Add'
   */
  rtb_lambda = (rtTm_rr + rtTm_rl) * 0.5 * rtDriver_req;

  /* Sum: '<S1>/Sum3' */
  rtb_delta_F = rtb_Subtract + rtb_lambda;

  /* Sum: '<S1>/Sum4' */
  rtb_T_rl = rtb_lambda - rtb_Subtract;

  /* Product: '<S66>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   */
  rtb_Product = rtTm_rr * rtDriver_req;

  /* Sum: '<S66>/Add4' incorporates:
   *  Gain: '<S66>/Wr//1'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = 0.605 * rtyaw_rate + rtu_bar;

  /* MATLAB Function: '<S66>/Slip_est2' incorporates:
   *  Constant: '<S66>/Constant1'
   *  Gain: '<S66>/Rr1'
   *  Inport: '<Root>/omega_rr'
   */
  Slip_est1(0.203 * rtomega_rr, rtb_vms, 1.0, &rtb_lambda);

  /* Sum: '<S75>/Add' incorporates:
   *  Constant: '<S75>/lambda_rr_max [-]'
   */
  rtb_lambda -= 0.096;

  /* Lookup_n-D: '<S66>/1-D Lookup Table3' incorporates:
   *  Sum: '<S66>/Add4'
   */
  rtb_Subtract = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled13,
    &rtDW->m_bpIndex, 9U);

  /* Product: '<S79>/Product1' */
  rtb_Switch2_a = rtb_lambda * rtb_Subtract;

  /* Saturate: '<S79>/Saturation' incorporates:
   *  Constant: '<S79>/Constant'
   *  Inport: '<Root>/Brake'
   *  Saturate: '<S71>/Saturation'
   *  Sum: '<S79>/Subtract'
   */
  rtb_Gain = fmax(rtsignal13 - 0.1, 0.0);

  /* DiscreteIntegrator: '<S79>/Discrete-Time Integrator1' incorporates:
   *  Saturate: '<S79>/Saturation'
   */
  if ((rtb_Gain != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevRes != 0)) {
    rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* DiscreteIntegrator: '<S79>/Discrete-Time Integrator1' */
  rtb_Sum = 0.0005 * rtb_Switch2_a + rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* If: '<S78>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtsignal13 < 0.1) {
    /* Lookup_n-D: '<S66>/1-D Lookup Table2' incorporates:
     *  MultiPortSwitch: '<S66>/Multiport Switch1'
     *  Sum: '<S66>/Add4'
     */
    rtb_Subtract = look1_pbinlcapw(rtb_vms, rtConstP.pooled4, rtConstP.pooled3,
      &rtDW->m_bpIndex_f, 9U);

    /* Sum: '<S66>/Add3' incorporates:
     *  Inport: '<Root>/map_sc'
     *  Lookup_n-D: '<S66>/1-D Lookup Table1'
     *  MultiPortSwitch: '<S66>/Multiport Switch1'
     *  Product: '<S66>/Product2'
     *  Product: '<S80>/Product'
     *  Saturate: '<S75>/Saturation'
     *  Sum: '<S75>/Sum'
     */
    rtb_Product -= fmax(rtb_lambda * rtb_Subtract + rtb_Sum, 0.0) *
      look1_binlxpw(rtsignal12, rtConstP.pooled2, rtConstP.pooled2, 1U);

    /* Switch: '<S76>/Switch2' incorporates:
     *  Constant: '<S66>/Constant'
     *  Inport: '<Root>/Tmax_rr'
     *  MultiPortSwitch: '<S66>/Multiport Switch1'
     *  RelationalOperator: '<S76>/LowerRelop1'
     *  RelationalOperator: '<S76>/UpperRelop'
     *  Switch: '<S76>/Switch'
     */
    if (rtb_Product > rtTm_rr) {
      rtb_Product = rtTm_rr;
    } else if (rtb_Product < 0.0) {
      /* Switch: '<S76>/Switch' incorporates:
       *  Constant: '<S66>/Constant'
       */
      rtb_Product = 0.0;
    }

    /* End of Switch: '<S76>/Switch2' */
  }

  /* End of If: '<S78>/If' */

  /* Product: '<S65>/Product' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   */
  rtb_vms = rtTm_rl * rtDriver_req;

  /* Sum: '<S65>/Add5' incorporates:
   *  Gain: '<S65>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms_n = rtu_bar - 0.605 * rtyaw_rate;

  /* MATLAB Function: '<S65>/Slip_est1' incorporates:
   *  Constant: '<S65>/Constant'
   *  Gain: '<S65>/Rl'
   *  Inport: '<Root>/omega_rl'
   */
  Slip_est1(0.203 * rtomega_rl, rtb_vms_n, 1.0, &rtb_lambda);

  /* Sum: '<S67>/Add' incorporates:
   *  Constant: '<S67>/lambda_rl_max [-]'
   */
  rtb_Add_g = rtb_lambda - 0.096;

  /* Lookup_n-D: '<S65>/1-D Lookup Table1' incorporates:
   *  Sum: '<S65>/Add5'
   */
  rtb_Subtract = look1_pbinlcapw(rtb_vms_n, rtConstP.pooled4, rtConstP.pooled13,
    &rtDW->m_bpIndex_h, 9U);

  /* Product: '<S71>/Product1' incorporates:
   *  Constant: '<S67>/lambda_rl_max [-]'
   *  Sum: '<S67>/Add'
   */
  rtb_Subtract *= rtb_lambda - 0.096;

  /* DiscreteIntegrator: '<S71>/Discrete-Time Integrator1' */
  if ((rtb_Gain != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevR_o != 0)) {
    rtDW->DiscreteTimeIntegrator1_DSTAT_k = 0.0;
  }

  /* DiscreteIntegrator: '<S71>/Discrete-Time Integrator1' */
  rtb_lambda = 0.0005 * rtb_Subtract + rtDW->DiscreteTimeIntegrator1_DSTAT_k;

  /* If: '<S70>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtsignal13 < 0.1) {
    /* Lookup_n-D: '<S65>/1-D Lookup Table' incorporates:
     *  MultiPortSwitch: '<S65>/Multiport Switch'
     *  Sum: '<S65>/Add5'
     */
    rtb_vms_n = look1_pbinlcapw(rtb_vms_n, rtConstP.pooled4, rtConstP.pooled3,
      &rtDW->m_bpIndex_k, 9U);

    /* Sum: '<S65>/Add1' incorporates:
     *  Inport: '<Root>/map_sc'
     *  Lookup_n-D: '<S65>/1-D Lookup Table2'
     *  MultiPortSwitch: '<S65>/Multiport Switch'
     *  Product: '<S65>/Product2'
     *  Product: '<S72>/Product'
     *  Saturate: '<S67>/Saturation'
     *  Sum: '<S67>/Sum'
     */
    rtb_vms -= fmax(rtb_Add_g * rtb_vms_n + rtb_lambda, 0.0) * look1_binlxpw
      (rtsignal12, rtConstP.pooled2, rtConstP.pooled2, 1U);

    /* Switch: '<S68>/Switch2' incorporates:
     *  Constant: '<S65>/Constant1'
     *  Inport: '<Root>/Tmax_rl'
     *  MultiPortSwitch: '<S65>/Multiport Switch'
     *  RelationalOperator: '<S68>/LowerRelop1'
     *  RelationalOperator: '<S68>/UpperRelop'
     *  Switch: '<S68>/Switch'
     */
    if (rtb_vms > rtTm_rl) {
      rtb_vms = rtTm_rl;
    } else if (rtb_vms < 0.0) {
      /* Switch: '<S68>/Switch' incorporates:
       *  Constant: '<S65>/Constant1'
       */
      rtb_vms = 0.0;
    }

    /* End of Switch: '<S68>/Switch2' */
  }

  /* End of If: '<S70>/If' */

  /* MATLAB Function: '<S1>/Saturation block' incorporates:
   *  Inport: '<Root>/u_bar'
   */
  if (rtu_bar > 5.0) {
    if (rtb_delta_F > rtb_Product) {
      rtb_vms_n = rtb_delta_F - rtb_Product;
    } else {
      rtb_vms_n = fmin(rtb_delta_F, 0.0);
    }

    if (rtb_T_rl > rtb_vms) {
      rtb_vms = rtb_T_rl - rtb_vms;
    } else if (rtb_delta_F < 0.0) {
      rtb_vms = rtb_T_rl;
    } else {
      rtb_vms = 0.0;
    }

    if (fabs(rtb_vms_n) >= fabs(rtb_vms)) {
      rtb_Product = rtb_delta_F - rtb_vms_n;
      rtb_vms = rtb_T_rl - rtb_vms_n;
    } else {
      rtb_Product = rtb_delta_F - rtb_vms;
      rtb_vms = rtb_T_rl - rtb_vms;
    }
  }

  /* End of MATLAB Function: '<S1>/Saturation block' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Tmax_rr'
   *  RelationalOperator: '<S3>/LowerRelop1'
   *  RelationalOperator: '<S3>/UpperRelop'
   *  Switch: '<S3>/Switch'
   */
  if (rtb_Product > rtTm_rr) {
    /* Outport: '<Root>/Tm_rr' */
    rtTm_rr_m = rtTm_rr;
  } else if (rtb_Product < 0.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S1>/Constant'
     *  Outport: '<Root>/Tm_rr'
     */
    rtTm_rr_m = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' incorporates:
     *  Switch: '<S3>/Switch'
     */
    rtTm_rr_m = rtb_Product;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Inport: '<Root>/Tmax_rl'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_vms > rtTm_rl) {
    /* Outport: '<Root>/Tm_rl' */
    rtTm_rl_a = rtTm_rl;
  } else if (rtb_vms < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Outport: '<Root>/Tm_rl'
     */
    rtTm_rl_a = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' incorporates:
     *  Switch: '<S4>/Switch'
     */
    rtTm_rl_a = rtb_vms;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Update for DiscreteIntegrator: '<S47>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0005 * rtb_IProdOut + rtb_SumFdbk;

  /* Update for DiscreteIntegrator: '<S79>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S71>/Discrete-Time Integrator1'
   *  Saturate: '<S79>/Saturation'
   */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0005 * rtb_Switch2_a + rtb_Sum;
  if (rtb_Gain > 0.0) {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 1;
    rtDW->DiscreteTimeIntegrator1_PrevR_o = 1;
  } else {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 0;
    rtDW->DiscreteTimeIntegrator1_PrevR_o = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S79>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S71>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_k = 0.0005 * rtb_Subtract + rtb_lambda;
}

/* Model initialize function */
void All0_initialize(RT_MODEL *const rtM)
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

  /* InitializeConditions for DiscreteIntegrator: '<S47>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S79>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevRes = 0;

  /* InitializeConditions for DiscreteIntegrator: '<S71>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevR_o = 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
