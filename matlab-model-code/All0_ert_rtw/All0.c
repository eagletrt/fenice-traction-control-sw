/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: All0.c
 *
 * Code generated for Simulink model 'All0'.
 *
 * Model version                  : 3.3
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Mar 14 22:22:09 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "All0.h"

/* Exported block parameters */
real_T lambda_ref = 0.097;             /* Variable: lambda_ref
                                        * Referenced by:
                                        *   '<S6>/lambda_rl_max [-]'
                                        *   '<S13>/lambda_rr_max [-]'
                                        */
static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
static real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex);
static void Slip_est1(real_T rtu_omegaR, real_T rtu_u_bar, real_T rtu_Vlow,
                      real_T *rty_lambda);
static void IfActionSubsystem(real_T *rty_Out2);
static void IfActionSubsystem1(real_T *rty_Out2);
static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

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
 *    '<S3>/Slip_est1'
 *    '<S4>/Slip_est1'
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
 *    '<S8>/If Action Subsystem'
 *    '<S15>/If Action Subsystem'
 */
static void IfActionSubsystem(real_T *rty_Out2)
{
  /* SignalConversion generated from: '<S11>/Out2' incorporates:
   *  Constant: '<S11>/Constant'
   */
  *rty_Out2 = 2.0;
}

/*
 * Output and update for action system:
 *    '<S8>/If Action Subsystem1'
 *    '<S15>/If Action Subsystem1'
 */
static void IfActionSubsystem1(real_T *rty_Out2)
{
  /* SignalConversion generated from: '<S12>/Out2' incorporates:
   *  Constant: '<S12>/Constant'
   */
  *rty_Out2 = 1.0;
}

/* Model step function */
void All0_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T rtU_u_bar,
               real_T rtU_omega_rr, real_T rtU_omega_rl, real_T rtU_yaw_rate,
               real_T rtU_Steeringangle, real_T rtU_Brake, real_T *rtY_Tm_rr,
               real_T *rtY_Tm_rl)
{
  DW *rtDW = rtM->dwork;
  real_T DiscreteTimeIntegrator1;
  real_T rtb_Add;
  real_T rtb_IProdOut;
  real_T rtb_Merge;
  real_T rtb_Product1;
  real_T rtb_Saturation_tmp;
  real_T rtb_Subtract;
  real_T rtb_T_rl;
  real_T rtb_Tm_req;
  real_T rtb_ZeroGain;
  real_T rtb_delta_F;
  real_T rtb_lambda;
  real_T rtb_vms;
  real_T rtb_vms_h;

  /* MATLAB Function: '<S5>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(rtU_Steeringangle, 4.0);
  rtb_delta_F = pow(rtU_Steeringangle, 5.0) * 0.00057273150574059159;
  rtb_lambda = pow(rtU_Steeringangle, 3.0) * 0.033763750817748066;
  rtb_Subtract = rtU_Steeringangle * rtU_Steeringangle;
  rtb_delta_F = (atan(tan(((((rtb_delta_F + rtb_IProdOut * 0.0033926772913763937)
    + rtb_lambda) + rtb_Subtract * 0.002563827091551279) + rtU_Steeringangle *
    0.14012014788005878) + 0.025823733081163723) * 0.9932741359 - 0.01660869904)
                 + atan(tan(((((rtb_delta_F + rtb_IProdOut *
    -0.0033926772913763937) + rtb_lambda) + rtb_Subtract * -0.002563827091551279)
    + rtU_Steeringangle * 0.14012014788005878) - 0.025823733081163723) *
                        0.9932741359 + 0.01660869904)) / 2.0;

  /* Sum: '<S5>/Sum1' incorporates:
   *  Constant: '<S22>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S22>/K_us_table'
   *  MATLAB Function: '<S22>/Yaw-Rate'
   */
  rtb_IProdOut = rtb_delta_F * rtU_u_bar / (rtU_u_bar * rtU_u_bar *
    look1_binlxpw(rtU_u_bar, rtConstP.K_us_table_bp01Data,
                  rtConstP.K_us_table_tableData, 9U) + 1.53) - rtU_yaw_rate;

  /* Product: '<S64>/PProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S23>/P_table'
   */
  rtb_lambda = rtb_IProdOut * look1_binlxpw(rtU_u_bar, rtConstP.pooled8,
    rtConstP.P_table_tableData, 8U);

  /* Sum: '<S69>/Sum Fdbk' */
  rtb_Subtract = rtb_lambda + rtDW->Integrator_DSTATE;

  /* DeadZone: '<S52>/DeadZone' */
  if (rtb_Subtract > 397.91416256157629) {
    rtb_Subtract -= 397.91416256157629;
  } else if (rtb_Subtract >= -397.91416256157629) {
    rtb_Subtract = 0.0;
  } else {
    rtb_Subtract -= -397.91416256157629;
  }

  /* End of DeadZone: '<S52>/DeadZone' */

  /* Product: '<S56>/IProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S23>/I_table'
   */
  rtb_IProdOut *= look1_binlxpw(rtU_u_bar, rtConstP.pooled8,
    rtConstP.I_table_tableData, 8U);

  /* Signum: '<S50>/SignPreSat' */
  if (rtb_Subtract < 0.0) {
    rtb_ZeroGain = -1.0;
  } else if (rtb_Subtract > 0.0) {
    rtb_ZeroGain = 1.0;
  } else {
    rtb_ZeroGain = rtb_Subtract;
  }

  /* End of Signum: '<S50>/SignPreSat' */

  /* DataTypeConversion: '<S50>/DataTypeConv1' */
  rtb_ZeroGain = fmod(rtb_ZeroGain, 256.0);

  /* Signum: '<S50>/SignPreIntegrator' */
  if (rtb_IProdOut < 0.0) {
    rtb_Tm_req = -1.0;
  } else if (rtb_IProdOut > 0.0) {
    rtb_Tm_req = 1.0;
  } else {
    rtb_Tm_req = rtb_IProdOut;
  }

  /* End of Signum: '<S50>/SignPreIntegrator' */

  /* DataTypeConversion: '<S50>/DataTypeConv2' */
  rtb_Tm_req = fmod(rtb_Tm_req, 256.0);

  /* Switch: '<S50>/Switch' incorporates:
   *  Constant: '<S50>/Constant1'
   *  DataTypeConversion: '<S50>/DataTypeConv1'
   *  DataTypeConversion: '<S50>/DataTypeConv2'
   *  Logic: '<S50>/AND3'
   *  RelationalOperator: '<S50>/Equal1'
   *  RelationalOperator: '<S50>/NotEqual'
   */
  if ((0.0 != rtb_Subtract) && ((rtb_ZeroGain < 0.0 ? (int32_T)(int8_T)-(int8_T)
        (uint8_T)-rtb_ZeroGain : (int32_T)(int8_T)(uint8_T)rtb_ZeroGain) ==
       (rtb_Tm_req < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-rtb_Tm_req :
        (int32_T)(int8_T)(uint8_T)rtb_Tm_req))) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S50>/Switch' */

  /* DiscreteIntegrator: '<S59>/Integrator' */
  rtb_ZeroGain = 0.0005 * rtb_IProdOut + rtDW->Integrator_DSTATE;

  /* Sum: '<S68>/Sum' */
  rtb_lambda += rtb_ZeroGain;

  /* Saturate: '<S66>/Saturation' */
  if (rtb_lambda > 397.91416256157629) {
    rtb_lambda = 397.91416256157629;
  } else if (rtb_lambda < -397.91416256157629) {
    rtb_lambda = -397.91416256157629;
  }

  /* End of Saturate: '<S66>/Saturation' */

  /* Gain: '<S1>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)' incorporates:
   *  Constant: '<S20>/Constant'
   *  Product: '<S5>/Product2'
   *  RelationalOperator: '<S20>/Compare'
   */
  rtb_Subtract = (rtb_delta_F >= 0.05 ? rtb_lambda : 0.0) * 0.0753931446090652;

  /* Gain: '<S1>/Max motor torque' incorporates:
   *  Inport: '<Root>/driver_request'
   */
  rtb_Tm_req = 55.0 * rtU_Driver_req;

  /* Sum: '<S1>/Sum' */
  rtb_delta_F = rtb_Subtract + rtb_Tm_req;

  /* Sum: '<S1>/Sum1' */
  rtb_T_rl = rtb_Tm_req - rtb_Subtract;

  /* If: '<S15>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtU_Brake >= 0.1) {
    /* Outputs for IfAction SubSystem: '<S15>/If Action Subsystem' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    IfActionSubsystem(&rtb_Merge);

    /* End of Outputs for SubSystem: '<S15>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S15>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    IfActionSubsystem1(&rtb_Merge);

    /* End of Outputs for SubSystem: '<S15>/If Action Subsystem1' */
  }

  /* End of If: '<S15>/If' */

  /* Sum: '<S4>/Add2' incorporates:
   *  Gain: '<S4>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms = 0.605 * rtU_yaw_rate + rtU_u_bar;

  /* MATLAB Function: '<S4>/Slip_est1' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Rr'
   *  Inport: '<Root>/omega_rr'
   */
  Slip_est1(0.203 * rtU_omega_rr, rtb_vms, 1.0, &rtb_lambda);

  /* Sum: '<S13>/Add' incorporates:
   *  Constant: '<S13>/lambda_rr_max [-]'
   */
  rtb_lambda -= lambda_ref;

  /* Lookup_n-D: '<S4>/1-D Lookup Table1' incorporates:
   *  Sum: '<S4>/Add2'
   */
  rtb_Subtract = look1_pbinlcapw(rtb_vms, rtConstP.pooled3, rtConstP.pooled14,
    &rtDW->m_bpIndex, 13U);

  /* Product: '<S16>/Product1' */
  rtb_Product1 = rtb_lambda * rtb_Subtract;

  /* Saturate: '<S16>/Saturation' incorporates:
   *  Constant: '<S16>/Constant'
   *  Inport: '<Root>/Brake'
   *  Saturate: '<S9>/Saturation'
   *  Sum: '<S16>/Subtract'
   */
  rtb_Saturation_tmp = fmax(rtU_Brake - 0.1, 0.0);

  /* DiscreteIntegrator: '<S16>/Discrete-Time Integrator1' incorporates:
   *  Saturate: '<S16>/Saturation'
   */
  if ((rtb_Saturation_tmp != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevRes != 0))
  {
    rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* DiscreteIntegrator: '<S16>/Discrete-Time Integrator1' */
  DiscreteTimeIntegrator1 = 0.0005 * rtb_Product1 +
    rtDW->DiscreteTimeIntegrator1_DSTATE;

  /* MultiPortSwitch: '<S4>/Multiport Switch' */
  if ((int32_T)rtb_Merge == 1) {
    /* Lookup_n-D: '<S4>/1-D Lookup Table' incorporates:
     *  Sum: '<S4>/Add2'
     */
    rtb_Subtract = look1_pbinlcapw(rtb_vms, rtConstP.pooled3, rtConstP.pooled2,
      &rtDW->m_bpIndex_m, 13U);

    /* Sum: '<S4>/Add1' incorporates:
     *  Product: '<S17>/Product'
     *  Saturate: '<S13>/Saturation'
     *  Sum: '<S13>/Sum'
     */
    rtb_Merge = rtb_Tm_req - fmax(rtb_lambda * rtb_Subtract +
      DiscreteTimeIntegrator1, 0.0);

    /* Saturate: '<S4>/Trr_ctrl_sat' */
    if (rtb_Merge > 55.0) {
      rtb_Merge = 55.0;
    } else if (rtb_Merge < 0.0) {
      rtb_Merge = 0.0;
    }

    /* End of Saturate: '<S4>/Trr_ctrl_sat' */
  } else {
    rtb_Merge = rtb_Tm_req;
  }

  /* End of MultiPortSwitch: '<S4>/Multiport Switch' */

  /* If: '<S8>/If' incorporates:
   *  Inport: '<Root>/Brake'
   */
  if (rtU_Brake >= 0.1) {
    /* Outputs for IfAction SubSystem: '<S8>/If Action Subsystem' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    IfActionSubsystem(&rtb_vms);

    /* End of Outputs for SubSystem: '<S8>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S8>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S12>/Action Port'
     */
    IfActionSubsystem1(&rtb_vms);

    /* End of Outputs for SubSystem: '<S8>/If Action Subsystem1' */
  }

  /* End of If: '<S8>/If' */

  /* Sum: '<S3>/Add5' incorporates:
   *  Gain: '<S3>/Wr//2'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   */
  rtb_vms_h = rtU_u_bar - 0.605 * rtU_yaw_rate;

  /* MATLAB Function: '<S3>/Slip_est1' incorporates:
   *  Constant: '<S3>/Constant'
   *  Gain: '<S3>/Rl'
   *  Inport: '<Root>/omega_rl'
   */
  Slip_est1(0.203 * rtU_omega_rl, rtb_vms_h, 1.0, &rtb_lambda);

  /* Sum: '<S6>/Add' incorporates:
   *  Constant: '<S6>/lambda_rl_max [-]'
   */
  rtb_Add = rtb_lambda - lambda_ref;

  /* Lookup_n-D: '<S3>/1-D Lookup Table1' incorporates:
   *  Sum: '<S3>/Add5'
   */
  rtb_Subtract = look1_pbinlcapw(rtb_vms_h, rtConstP.pooled3, rtConstP.pooled14,
    &rtDW->m_bpIndex_h, 13U);

  /* Product: '<S9>/Product1' */
  rtb_Subtract *= rtb_Add;

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  if ((rtb_Saturation_tmp != 0.0) || (rtDW->DiscreteTimeIntegrator1_PrevR_n != 0))
  {
    rtDW->DiscreteTimeIntegrator1_DSTAT_a = 0.0;
  }

  /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtb_lambda = 0.0005 * rtb_Subtract + rtDW->DiscreteTimeIntegrator1_DSTAT_a;

  /* MultiPortSwitch: '<S3>/Multiport Switch' */
  if ((int32_T)rtb_vms == 1) {
    /* Lookup_n-D: '<S3>/1-D Lookup Table' incorporates:
     *  Sum: '<S3>/Add5'
     */
    rtb_vms = look1_pbinlcapw(rtb_vms_h, rtConstP.pooled3, rtConstP.pooled2,
      &rtDW->m_bpIndex_d, 13U);

    /* Sum: '<S3>/Add1' incorporates:
     *  Product: '<S10>/Product'
     *  Saturate: '<S6>/Saturation'
     *  Sum: '<S6>/Sum'
     */
    rtb_Tm_req -= fmax(rtb_Add * rtb_vms + rtb_lambda, 0.0);

    /* Saturate: '<S3>/Trl_ctrl_sat' */
    if (rtb_Tm_req > 55.0) {
      rtb_Tm_req = 55.0;
    } else if (rtb_Tm_req < 0.0) {
      rtb_Tm_req = 0.0;
    }

    /* End of Saturate: '<S3>/Trl_ctrl_sat' */
  }

  /* End of MultiPortSwitch: '<S3>/Multiport Switch' */

  /* MATLAB Function: '<S1>/Saturation block' incorporates:
   *  Inport: '<Root>/u_bar'
   */
  if (rtU_u_bar > 5.0) {
    if (rtb_delta_F > rtb_Merge) {
      rtb_vms = rtb_delta_F - rtb_Merge;
    } else {
      rtb_vms = fmin(rtb_delta_F, 0.0);
    }

    if (rtb_T_rl > rtb_Tm_req) {
      rtb_Tm_req = rtb_T_rl - rtb_Tm_req;
    } else if (rtb_delta_F < 0.0) {
      rtb_Tm_req = rtb_T_rl;
    } else {
      rtb_Tm_req = 0.0;
    }

    if (fabs(rtb_vms) >= fabs(rtb_Tm_req)) {
      rtb_Merge = rtb_delta_F - rtb_vms;
      rtb_Tm_req = rtb_T_rl - rtb_vms;
    } else {
      rtb_Merge = rtb_delta_F - rtb_Tm_req;
      rtb_Tm_req = rtb_T_rl - rtb_Tm_req;
    }
  }

  /* End of MATLAB Function: '<S1>/Saturation block' */

  /* Saturate: '<S1>/Right_sat_all' */
  if (rtb_Merge > 55.0) {
    /* Outport: '<Root>/Tm_rr' */
    *rtY_Tm_rr = 55.0;
  } else if (rtb_Merge < 0.0) {
    /* Outport: '<Root>/Tm_rr' */
    *rtY_Tm_rr = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' */
    *rtY_Tm_rr = rtb_Merge;
  }

  /* End of Saturate: '<S1>/Right_sat_all' */

  /* Saturate: '<S1>/Left_sat_all' */
  if (rtb_Tm_req > 55.0) {
    /* Outport: '<Root>/Tm_rl' */
    *rtY_Tm_rl = 55.0;
  } else if (rtb_Tm_req < 0.0) {
    /* Outport: '<Root>/Tm_rl' */
    *rtY_Tm_rl = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' */
    *rtY_Tm_rl = rtb_Tm_req;
  }

  /* End of Saturate: '<S1>/Left_sat_all' */

  /* Update for DiscreteIntegrator: '<S59>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0005 * rtb_IProdOut + rtb_ZeroGain;

  /* Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S9>/Discrete-Time Integrator1'
   *  Saturate: '<S16>/Saturation'
   */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0005 * rtb_Product1 +
    DiscreteTimeIntegrator1;
  if (rtb_Saturation_tmp > 0.0) {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 1;
    rtDW->DiscreteTimeIntegrator1_PrevR_n = 1;
  } else {
    rtDW->DiscreteTimeIntegrator1_PrevRes = 0;
    rtDW->DiscreteTimeIntegrator1_PrevR_n = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_a = 0.0005 * rtb_Subtract + rtb_lambda;
}

/* Model initialize function */
void All0_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T
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

  /* InitializeConditions for DiscreteIntegrator: '<S59>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S16>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevRes = 0;

  /* InitializeConditions for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_PrevR_n = 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
