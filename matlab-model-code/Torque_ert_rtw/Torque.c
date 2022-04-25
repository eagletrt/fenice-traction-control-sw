/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 3.3
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Mar 14 22:26:33 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Torque.h"

static real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
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

/* Model step function */
void Torque_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T rtU_u_bar,
                 real_T rtU_yaw_rate, real_T rtU_Steeringangle, real_T
                 *rtY_Tm_rr, real_T *rtY_Tm_rl)
{
  DW *rtDW = rtM->dwork;
  real_T T_rl_sat;
  real_T T_rr_sat;
  real_T rtb_IProdOut;
  real_T rtb_Saturation;
  real_T rtb_T_diff;
  real_T rtb_ZeroGain;
  real_T rtb_delta_F;

  /* MATLAB Function: '<S4>/SteeringModel' incorporates:
   *  Inport: '<Root>/delta'
   */
  rtb_IProdOut = pow(rtU_Steeringangle, 4.0);
  rtb_delta_F = pow(rtU_Steeringangle, 5.0) * 0.00057273150574059159;
  rtb_Saturation = pow(rtU_Steeringangle, 3.0) * 0.033763750817748066;
  rtb_T_diff = rtU_Steeringangle * rtU_Steeringangle;
  rtb_delta_F = (atan(tan(((((rtb_delta_F + rtb_IProdOut * 0.0033926772913763937)
    + rtb_Saturation) + rtb_T_diff * 0.002563827091551279) + rtU_Steeringangle *
    0.14012014788005878) + 0.025823733081163723) * 0.9932741359 - 0.01660869904)
                 + atan(tan(((((rtb_delta_F + rtb_IProdOut *
    -0.0033926772913763937) + rtb_Saturation) + rtb_T_diff *
    -0.002563827091551279) + rtU_Steeringangle * 0.14012014788005878) -
    0.025823733081163723) * 0.9932741359 + 0.01660869904)) / 2.0;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Constant: '<S7>/Constant'
   *  Inport: '<Root>/Omega'
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S7>/K_us_table'
   *  MATLAB Function: '<S7>/Yaw-Rate'
   */
  rtb_IProdOut = rtb_delta_F * rtU_u_bar / (rtU_u_bar * rtU_u_bar *
    look1_binlxpw(rtU_u_bar, rtConstP.K_us_table_bp01Data,
                  rtConstP.K_us_table_tableData, 9U) + 1.53) - rtU_yaw_rate;

  /* Product: '<S49>/PProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S8>/P_table'
   */
  rtb_Saturation = rtb_IProdOut * look1_binlxpw(rtU_u_bar, rtConstP.pooled1,
    rtConstP.P_table_tableData, 8U);

  /* Sum: '<S54>/Sum Fdbk' */
  rtb_T_diff = rtb_Saturation + rtDW->Integrator_DSTATE;

  /* DeadZone: '<S37>/DeadZone' */
  if (rtb_T_diff > 397.91416256157629) {
    rtb_T_diff -= 397.91416256157629;
  } else if (rtb_T_diff >= -397.91416256157629) {
    rtb_T_diff = 0.0;
  } else {
    rtb_T_diff -= -397.91416256157629;
  }

  /* End of DeadZone: '<S37>/DeadZone' */

  /* Product: '<S41>/IProd Out' incorporates:
   *  Inport: '<Root>/u_bar'
   *  Lookup_n-D: '<S8>/I_table'
   */
  rtb_IProdOut *= look1_binlxpw(rtU_u_bar, rtConstP.pooled1,
    rtConstP.I_table_tableData, 8U);

  /* Signum: '<S35>/SignPreSat' */
  if (rtb_T_diff < 0.0) {
    rtb_ZeroGain = -1.0;
  } else if (rtb_T_diff > 0.0) {
    rtb_ZeroGain = 1.0;
  } else {
    rtb_ZeroGain = rtb_T_diff;
  }

  /* End of Signum: '<S35>/SignPreSat' */

  /* DataTypeConversion: '<S35>/DataTypeConv1' */
  rtb_ZeroGain = fmod(rtb_ZeroGain, 256.0);

  /* Signum: '<S35>/SignPreIntegrator' */
  if (rtb_IProdOut < 0.0) {
    T_rr_sat = -1.0;
  } else if (rtb_IProdOut > 0.0) {
    T_rr_sat = 1.0;
  } else {
    T_rr_sat = rtb_IProdOut;
  }

  /* End of Signum: '<S35>/SignPreIntegrator' */

  /* DataTypeConversion: '<S35>/DataTypeConv2' */
  T_rr_sat = fmod(T_rr_sat, 256.0);

  /* Switch: '<S35>/Switch' incorporates:
   *  Constant: '<S35>/Constant1'
   *  DataTypeConversion: '<S35>/DataTypeConv1'
   *  DataTypeConversion: '<S35>/DataTypeConv2'
   *  Logic: '<S35>/AND3'
   *  RelationalOperator: '<S35>/Equal1'
   *  RelationalOperator: '<S35>/NotEqual'
   */
  if ((0.0 != rtb_T_diff) && ((rtb_ZeroGain < 0.0 ? (int32_T)(int8_T)-(int8_T)
        (uint8_T)-rtb_ZeroGain : (int32_T)(int8_T)(uint8_T)rtb_ZeroGain) ==
       (T_rr_sat < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-T_rr_sat : (int32_T)
        (int8_T)(uint8_T)T_rr_sat))) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S35>/Switch' */

  /* DiscreteIntegrator: '<S44>/Integrator' */
  rtb_ZeroGain = 0.0005 * rtb_IProdOut + rtDW->Integrator_DSTATE;

  /* Sum: '<S53>/Sum' */
  rtb_Saturation += rtb_ZeroGain;

  /* Saturate: '<S51>/Saturation' */
  if (rtb_Saturation > 397.91416256157629) {
    rtb_Saturation = 397.91416256157629;
  } else if (rtb_Saturation < -397.91416256157629) {
    rtb_Saturation = -397.91416256157629;
  }

  /* End of Saturate: '<S51>/Saturation' */

  /* Gain: '<S2>/Delta_T = 2*Nz*r // (Wr*tau_red*eff)1' incorporates:
   *  Constant: '<S5>/Constant'
   *  Product: '<S4>/Product2'
   *  RelationalOperator: '<S5>/Compare'
   */
  rtb_T_diff = (rtb_delta_F >= 0.05 ? rtb_Saturation : 0.0) * 0.0753931446090652;

  /* Gain: '<S2>/Max motor torque' incorporates:
   *  Inport: '<Root>/driver_request'
   */
  rtb_delta_F = 55.0 * rtU_Driver_req;

  /* Sum: '<S2>/Sum2' */
  rtb_Saturation = rtb_T_diff + rtb_delta_F;

  /* Sum: '<S2>/Sum3' */
  rtb_T_diff = rtb_delta_F - rtb_T_diff;

  /* MATLAB Function: '<S2>/Saturation block' incorporates:
   *  Constant: '<S2>/Constant'
   *  Inport: '<Root>/u_bar'
   */
  if (rtU_u_bar > 5.0) {
    if (rtb_Saturation > 55.0) {
      T_rr_sat = rtb_Saturation - 55.0;
    } else {
      T_rr_sat = fmin(rtb_Saturation, 0.0);
    }

    if (rtb_T_diff > 55.0) {
      T_rl_sat = rtb_T_diff - 55.0;
    } else if (rtb_Saturation < 0.0) {
      T_rl_sat = rtb_T_diff;
    } else {
      T_rl_sat = 0.0;
    }

    if (fabs(T_rr_sat) >= fabs(T_rl_sat)) {
      rtb_delta_F = rtb_Saturation - T_rr_sat;
      rtb_T_diff += T_rr_sat;
    } else {
      rtb_delta_F = rtb_Saturation + T_rl_sat;
      rtb_T_diff -= T_rl_sat;
    }
  } else {
    rtb_T_diff = rtb_delta_F;
  }

  /* End of MATLAB Function: '<S2>/Saturation block' */

  /* Saturate: '<S2>/Right_sat' */
  if (rtb_delta_F > 55.0) {
    /* Outport: '<Root>/Tm_rr' */
    *rtY_Tm_rr = 55.0;
  } else if (rtb_delta_F < 0.0) {
    /* Outport: '<Root>/Tm_rr' */
    *rtY_Tm_rr = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rr' */
    *rtY_Tm_rr = rtb_delta_F;
  }

  /* End of Saturate: '<S2>/Right_sat' */

  /* Saturate: '<S2>/Left_sat' */
  if (rtb_T_diff > 55.0) {
    /* Outport: '<Root>/Tm_rl' */
    *rtY_Tm_rl = 55.0;
  } else if (rtb_T_diff < 0.0) {
    /* Outport: '<Root>/Tm_rl' */
    *rtY_Tm_rl = 0.0;
  } else {
    /* Outport: '<Root>/Tm_rl' */
    *rtY_Tm_rl = rtb_T_diff;
  }

  /* End of Saturate: '<S2>/Left_sat' */

  /* Update for DiscreteIntegrator: '<S44>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0005 * rtb_IProdOut + rtb_ZeroGain;
}

/* Model initialize function */
void Torque_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T
  *rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl, real_T *rtU_yaw_rate,
  real_T *rtU_Steeringangle, real_T *rtU_Brake, real_T *rtY_Tm_rr, real_T
  *rtY_Tm_rl)
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

  /* InitializeConditions for DiscreteIntegrator: '<S44>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
