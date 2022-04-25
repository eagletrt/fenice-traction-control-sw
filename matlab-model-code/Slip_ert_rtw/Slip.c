/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Slip.c
 *
 * Code generated for Simulink model 'Slip'.
 *
 * Model version                  : 3.5
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sat Apr  2 09:26:59 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Slip.h"

/* Exported block parameters */
real_T lambda_ref = 0.097;             /* Variable: lambda_ref
                                        * Referenced by:
                                        *   '<S4>/lambda_rl_max [-]'
                                        *   '<S11>/lambda_rr_max [-]'
                                        */
static real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex);
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda);
static void IfActionSubsystem(real_T *rty_Out2);
static void IfActionSubsystem1(real_T *rty_Out2);
static real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  real_T yL_0d0;
  uint32_T bpIdx;
  uint32_T found;
  uint32_T iLeft;
  uint32_T iRght;

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
    yL_0d0 = table[bpIdx];
    y = (table[bpIdx + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

/*
 * Output and update for atomic system:
 *    '<S2>/Slip_est1'
 *    '<S3>/Slip_est1'
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

/*
 * Output and update for action system:
 *    '<S6>/If Action Subsystem'
 *    '<S13>/If Action Subsystem'
 */
static void IfActionSubsystem(real_T *rty_Out2)
{
  /* SignalConversion generated from: '<S9>/Out2' incorporates:
   *  Constant: '<S9>/Constant'
   */
  *rty_Out2 = 2.0;
}

/*
 * Output and update for action system:
 *    '<S6>/If Action Subsystem1'
 *    '<S13>/If Action Subsystem1'
 */
static void IfActionSubsystem1(real_T *rty_Out2)
{
  /* SignalConversion generated from: '<S10>/Out2' incorporates:
   *  Constant: '<S10>/Constant'
   */
  *rty_Out2 = 1.0;
}

/* Model step function */
void Slip_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T rtU_u_bar,
               real_T rtU_omega_rr, real_T rtU_omega_rl, real_T rtU_yaw_rate,
               real_T rtU_Brake, real_T *rtY_Tm_rr, real_T *rtY_Tm_rl)
{
  DW *rtDW = rtM->dwork;
  real_T DiscreteTimeIntegrator1;
  real_T DiscreteTimeIntegrator1_d;
  real_T rtb_Merge_d;
  real_T rtb_Product1;
  real_T rtb_Saturation_tmp;
  real_T rtb_Subtract;
  real_T rtb_Tm_req;
  real_T rtb_lambda;
  real_T rtb_vms;

  /* Gain: '<S1>/Max motor torque' incorporates:
   *  Inport: '<Root>/driver_request'
   */
  rtb_Tm_req = 55.0 * rtU_Driver_req;

  /* Sum: '<S3>/Add2' incorporates:
   *  Gain: '<S3>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = 0.605 * rtU_yaw_rate + rtU_u_bar;

  /* MATLAB Function: '<S3>/Slip_est1' incorporates:
   *  Constant: '<S3>/Constant'
   *  Gain: '<S3>/Rr'
   *  Inport: '<Root>/omega_rr'
   */
  Slip_est1(0.203 * rtU_omega_rr, rtb_vms, 1.0, &rtb_lambda);

  /* Sum: '<S11>/Add' incorporates:
   *  Constant: '<S11>/lambda_rr_max [-]'
   */
  rtb_lambda -= lambda_ref;

  /* Lookup_n-D: '<S3>/1-D Lookup Table1' incorporates:
   *  Sum: '<S3>/Add2'
   */
  rtb_Subtract = look1_pbinlcapw(rtb_vms, rtConstP.pooled3, rtConstP.pooled10,
    &rtDW->m_bpIndex, 13U);

  /* Product: '<S14>/Product1' */
  rtb_Product1 = rtb_lambda * rtb_Subtract;

  /* Saturate: '<S14>/Saturation' incorporates:
   *  Constant: '<S14>/Constant'
   *  Inport: '<Root>/Brake'
   *  Saturate: '<S7>/Saturation'
   *  Sum: '<S14>/Subtract'
   */
  rtb_Saturation_tmp = fmax(rtU_Brake - 0.1, 0.0);

  /* DiscreteIntegrator: '<S14>/Discrete-Time Integrator1' incorporates:
   *  Saturate: '<S14>/Saturation'
   */
  if ((rtb_Saturation_tmp != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevRes != 0))
  {
    rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* DiscreteIntegrator: '<S14>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = 0.0005 * rtb_Product1 +
    rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* If: '<S13>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtU_Brake >= 0.1) {
    /* Outputs for IfAction SubSystem: '<S13>/If Action Subsystem' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    IfActionSubsystem(&rtb_Subtract);

    /* End of Outputs for SubSystem: '<S13>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S13>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    IfActionSubsystem1(&rtb_Subtract);

    /* End of Outputs for SubSystem: '<S13>/If Action Subsystem1' */
  }

  /* End of If: '<S13>/If' */

  /* MultiPortSwitch: '<S3>/Multiport Switch' */
  if ((int32_T)rtb_Subtract == 1) {
    /* Lookup_n-D: '<S3>/1-D Lookup Table' incorporates:
     *  Sum: '<S3>/Add2'
     */
    rtb_vms = look1_pbinlcapw(rtb_vms, rtConstP.pooled3, rtConstP.pooled2,
      &rtDW->m_bpIndex_h, 13U);

    /* Sum: '<S3>/Add1' incorporates:
     *  Product: '<S15>/Product'
     *  Saturate: '<S11>/Saturation'
     *  Sum: '<S11>/Sum'
     */
    rtb_vms = rtb_Tm_req - fmax(rtb_lambda * rtb_vms + DiscreteTimeIntegrator1,
      0.0);

    /* Saturate: '<S3>/Trr_ctrl_sat' */
    if (rtb_vms > 55.0) {
      /* Outport: '<Root>/Tm_rr' */
      *rtY_Tm_rr = 55.0;
    } else if (rtb_vms < 0.0) {
      /* Outport: '<Root>/Tm_rr' */
      *rtY_Tm_rr = 0.0;
    } else {
      /* Outport: '<Root>/Tm_rr' */
      *rtY_Tm_rr = rtb_vms;
    }

    /* End of Saturate: '<S3>/Trr_ctrl_sat' */
  } else {
    /* Outport: '<Root>/Tm_rr' */
    *rtY_Tm_rr = rtb_Tm_req;
  }

  /* End of MultiPortSwitch: '<S3>/Multiport Switch' */

  /* Sum: '<S2>/Add5' incorporates:
   *  Gain: '<S2>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = rtU_u_bar - 0.605 * rtU_yaw_rate;

  /* MATLAB Function: '<S2>/Slip_est1' incorporates:
   *  Constant: '<S2>/Constant'
   *  Gain: '<S2>/Rl'
   *  Inport: '<Root>/omega_rl'
   */
  Slip_est1(0.203 * rtU_omega_rl, rtb_vms, 1.0, &rtb_lambda);

  /* Sum: '<S4>/Add' incorporates:
   *  Constant: '<S4>/lambda_rl_max [-]'
   */
  rtb_lambda -= lambda_ref;

  /* Lookup_n-D: '<S2>/1-D Lookup Table1' incorporates:
   *  Sum: '<S2>/Add5'
   */
  rtb_Subtract = look1_pbinlcapw(rtb_vms, rtConstP.pooled3, rtConstP.pooled10,
    &rtDW->m_bpIndex_i, 13U);

  /* Product: '<S7>/Product1' */
  rtb_Subtract *= rtb_lambda;

  /* DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  if ((rtb_Saturation_tmp != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevR_d != 0))
  {
    rtDW->DiscreteTimeIntegrator1_DSTAT_c = 0.0;
  }

  /* DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1_d = 0.0005 * rtb_Subtract +
    rtDW->DiscreteTimeIntegrator1_DSTAT_c;

  /* If: '<S6>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtU_Brake >= 0.1) {
    /* Outputs for IfAction SubSystem: '<S6>/If Action Subsystem' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    IfActionSubsystem(&rtb_Merge_d);

    /* End of Outputs for SubSystem: '<S6>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S6>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    IfActionSubsystem1(&rtb_Merge_d);

    /* End of Outputs for SubSystem: '<S6>/If Action Subsystem1' */
  }

  /* End of If: '<S6>/If' */

  /* MultiPortSwitch: '<S2>/Multiport Switch' */
  if ((int32_T)rtb_Merge_d == 1) {
    /* Lookup_n-D: '<S2>/1-D Lookup Table' incorporates:
     *  Sum: '<S2>/Add5'
     */
    rtb_vms = look1_pbinlcapw(rtb_vms, rtConstP.pooled3, rtConstP.pooled2,
      &rtDW->m_bpIndex_ig, 13U);

    /* Sum: '<S2>/Add1' incorporates:
     *  Product: '<S8>/Product'
     *  Saturate: '<S4>/Saturation'
     *  Sum: '<S4>/Sum'
     */
    rtb_vms = rtb_Tm_req - fmax(rtb_lambda * rtb_vms + DiscreteTimeIntegrator1_d,
      0.0);

    /* Saturate: '<S2>/Trl_ctrl_sat' */
    if (rtb_vms > 55.0) {
      /* Outport: '<Root>/Tm_rl' */
      *rtY_Tm_rl = 55.0;
    } else if (rtb_vms < 0.0) {
      /* Outport: '<Root>/Tm_rl' */
      *rtY_Tm_rl = 0.0;
    } else {
      /* Outport: '<Root>/Tm_rl' */
      *rtY_Tm_rl = rtb_vms;
    }

    /* End of Saturate: '<S2>/Trl_ctrl_sat' */
  } else {
    /* Outport: '<Root>/Tm_rl' */
    *rtY_Tm_rl = rtb_Tm_req;
  }

  /* End of MultiPortSwitch: '<S2>/Multiport Switch' */

  /* Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S7>/Discrete-Time Integrator1'
   *  Saturate: '<S14>/Saturation'
   */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0005 * rtb_Product1 +
    DiscreteTimeIntegrator1;
  if (rtb_Saturation_tmp > 0.0) {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 1;
    rtDW->DiscreteTimeIntegrator1_PrevR_d = 1;
  } else {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 0;
    rtDW->DiscreteTimeIntegrator1_PrevR_d = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_c = 0.0005 * rtb_Subtract +
    DiscreteTimeIntegrator1_d;
}

/* Model initialize function */
void Slip_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T
                     *rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl,
                     real_T *rtU_yaw_rate, real_T *rtU_Steeringangle, real_T
                     *rtU_Brake, real_T *rtY_Tm_rr, real_T *rtY_Tm_rl)
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

  /* external outputs */
  (*rtY_Tm_rr) = 0.0;
  (*rtY_Tm_rl) = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevRes = 0;

  /* InitializeConditions for DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevR_d = 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
