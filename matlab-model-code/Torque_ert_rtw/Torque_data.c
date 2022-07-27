/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_data.c
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

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S2>/1-D Lookup Table2'
   *   '<S9>/1-D Lookup Table2'
   */
  { 0.0, 1.0 },

  /* Expression: TV.KusT.K_us
   * Referenced by: '<S8>/K_us_table'
   */
  { 0.182957, 0.081065, 0.045234, 0.028612, 0.019731, 0.01455, 0.011396 },

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S8>/K_us_table'
   */
  { 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0 },

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S9>/P_table'
   */
  { 1038.618629, 926.127599, 877.266978, 854.413214, 843.643018, 837.54139,
    831.38508, 822.261418 },

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S9>/I_table'
   *   '<S9>/P_table'
   */
  { 5.555556, 8.333333, 11.111111, 13.888889, 16.666667, 19.444444, 22.222222,
    25.0 },

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S9>/I_table'
   */
  { 62511.5719, 42200.197344, 31974.408367, 25689.352244, 21341.477686,
    18108.138404, 15588.628209, 13547.20095 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
