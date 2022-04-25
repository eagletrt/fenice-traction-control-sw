/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: All0_data.c
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

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S3>/1-D Lookup Table'
   *   '<S4>/1-D Lookup Table'
   */
  { 121.25, 157.1875, 157.1875, 157.1875, 157.1875, 157.1875, 157.1875, 157.1875,
    157.1875, 157.1875, 100.0, 100.0, 110.0, 125.0 },

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S3>/1-D Lookup Table'
   *   '<S3>/1-D Lookup Table1'
   *   '<S4>/1-D Lookup Table'
   *   '<S4>/1-D Lookup Table1'
   */
  { 0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0,
    120.0, 130.0 },

  /* Expression: TV.KusT.K_us
   * Referenced by: '<S22>/K_us_table'
   */
  { -5.6E-5, -0.00065, -0.000739, -0.000691, -0.000489, -0.000117, 0.0003,
    0.000657, 0.000908, 0.001289 },

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S22>/K_us_table'
   */
  { 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0 },

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S23>/P_table'
   */
  { 2001.687489, 3185.736082, 3712.084946, 4002.201574, 4185.729139, 4305.803753,
    4374.388334, 4396.305437, 4433.758076 },

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S23>/I_table'
   *   '<S23>/P_table'
   */
  { 5.555556, 8.333333, 11.111111, 13.888889, 16.666667, 19.444444, 22.222222,
    25.0, 27.777778 },

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S23>/I_table'
   */
  { 42277.068811, 31584.176095, 24190.556179, 19108.01705, 15596.686574,
    13229.730785, 11701.207242, 10600.614187, 8496.755918 },

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S3>/1-D Lookup Table1'
   *   '<S4>/1-D Lookup Table1'
   */
  { 37.5, 20.625, 20.625, 20.625, 20.625, 20.625, 20.625, 20.625, 20.625, 20.625,
    50.0, 50.0, 51.875, 45.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */