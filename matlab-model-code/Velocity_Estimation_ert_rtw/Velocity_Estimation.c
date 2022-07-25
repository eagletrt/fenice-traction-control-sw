/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Velocity_Estimation.c
 *
 * Code generated for Simulink model 'Velocity_Estimation'.
 *
 * Model version                  : 5.241
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sat May 21 16:02:01 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Velocity_Estimation.h"
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
void Velocity_Estimation_step(RT_MODEL *const rtM, real_T rtU_omega_fl, real_T
  rtU_omega_fr, real_T rtU_omega_rl, real_T rtU_omega_rr, real_T rtU_axG, real_T
  rtU_map_motor, real_T *rtY_u_bar, real_T *rtY_Tmax_rr, real_T *rtY_Tmax_rl)
{
  DW *rtDW = rtM->dwork;
  real_T rtb_DiscreteFilter1;
  real_T rtb_DiscreteFilter2;
  real_T w_mot;

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/map'
   *  Inport: '<Root>/omega_rr'
   *  Lookup_n-D: '<S1>/1-D Lookup Table2'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  rtb_DiscreteFilter1 = 55.0 * look1_binlxpw(rtU_map_motor,
    rtConstP.uDLookupTable2_bp01Data, rtConstP.uDLookupTable2_tableData, 5U);
  w_mot = rtU_omega_rr * 4.5 * 60.0 / 6.2831853071795862;
  if (w_mot <= 5000.0) {
    w_mot = rtb_DiscreteFilter1;
  } else {
    w_mot = rtb_DiscreteFilter1 / -1500.0 * (w_mot - 5000.0) +
      rtb_DiscreteFilter1;
  }

  if (rtb_DiscreteFilter1 > 55.0) {
    w_mot = 55.0;
  }

  if (w_mot < 0.0) {
    w_mot = 0.0;
  }

  /* End of MATLAB Function: '<S1>/MATLAB Function1' */

  /* Outport: '<Root>/Tmax_rr' */
  *rtY_Tmax_rr = w_mot;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/omega_rl'
   */
  w_mot = rtU_omega_rl * 4.5 * 60.0 / 6.2831853071795862;
  if (w_mot <= 5000.0) {
    w_mot = rtb_DiscreteFilter1;
  } else {
    w_mot = rtb_DiscreteFilter1 / -1500.0 * (w_mot - 5000.0) +
      rtb_DiscreteFilter1;
  }

  if (rtb_DiscreteFilter1 > 55.0) {
    w_mot = 55.0;
  }

  if (w_mot < 0.0) {
    w_mot = 0.0;
  }

  /* Outport: '<Root>/Tmax_rl' */
  *rtY_Tmax_rl = w_mot;

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant6'
   *  Inport: '<Root>/omega_fl'
   *  Inport: '<Root>/omega_fr'
   *  Product: '<S4>/Divide'
   *  Sum: '<S4>/Sum1'
   */
  w_mot = (rtU_omega_fl + rtU_omega_fr) / 2.0 * 0.203;

  /* DiscreteFilter: '<S4>/Discrete Filter1' */
  rtb_DiscreteFilter1 = (0.005 * w_mot + -0.005 * rtDW->DiscreteFilter1_states)
    - -0.99950012497916929 * rtDW->DiscreteFilter1_denStates;

  /* Outport: '<Root>/u_bar' incorporates:
   *  Sum: '<S4>/Sum'
   *  Sum: '<S4>/Sum2'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  *rtY_u_bar = (w_mot - rtb_DiscreteFilter1) + rtDW->UnitDelay_DSTATE;

  /* DiscreteFilter: '<S4>/Discrete Filter2' incorporates:
   *  Inport: '<Root>/a_x'
   */
  rtb_DiscreteFilter2 = (0.005 * rtU_axG + -0.005 * rtDW->DiscreteFilter2_states)
    - -0.99950012497916929 * rtDW->DiscreteFilter2_denStates;

  /* Update for DiscreteFilter: '<S4>/Discrete Filter1' */
  rtDW->DiscreteFilter1_states = w_mot;
  rtDW->DiscreteFilter1_denStates = rtb_DiscreteFilter1;

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  rtDW->UnitDelay_DSTATE = rtb_DiscreteFilter2;

  /* Update for DiscreteFilter: '<S4>/Discrete Filter2' incorporates:
   *  Inport: '<Root>/a_x'
   */
  rtDW->DiscreteFilter2_states = rtU_axG;
  rtDW->DiscreteFilter2_denStates = rtb_DiscreteFilter2;
}

/* Model initialize function */
void Velocity_Estimation_initialize(RT_MODEL *const rtM, real_T *rtU_omega_fl,
  real_T *rtU_omega_fr, real_T *rtU_omega_rl, real_T *rtU_omega_rr, real_T
  *rtU_axG, real_T *rtU_map_motor, real_T *rtU_u, real_T *rtY_u_bar, real_T
  *rtY_Tmax_rr, real_T *rtY_Tmax_rl)
{
  DW *rtDW = rtM->dwork;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  *rtU_omega_fl = 0.0;
  *rtU_omega_fr = 0.0;
  *rtU_omega_rl = 0.0;
  *rtU_omega_rr = 0.0;
  *rtU_axG = 0.0;
  *rtU_map_motor = 0.0;
  *rtU_u = 0.0;

  /* external outputs */
  *rtY_u_bar = 0.0;
  *rtY_Tmax_rr = 0.0;
  *rtY_Tmax_rl = 0.0;

  /* InitializeConditions for DiscreteFilter: '<S4>/Discrete Filter1' */
  rtDW->DiscreteFilter1_states = 0.0;
  rtDW->DiscreteFilter1_denStates = 0.0;

  /* InitializeConditions for DiscreteFilter: '<S4>/Discrete Filter2' */
  rtDW->DiscreteFilter2_states = 0.0;
  rtDW->DiscreteFilter2_denStates = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
