/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Slip_data.c
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

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S2>/1-D Lookup Table'
   *   '<S3>/1-D Lookup Table'
   */
  { 121.25, 157.1875, 157.1875, 157.1875, 157.1875, 157.1875, 157.1875, 157.1875,
    157.1875, 157.1875, 100.0, 100.0, 110.0, 125.0 },

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S2>/1-D Lookup Table'
   *   '<S2>/1-D Lookup Table1'
   *   '<S3>/1-D Lookup Table'
   *   '<S3>/1-D Lookup Table1'
   */
  { 0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0,
    120.0, 130.0 },

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S2>/1-D Lookup Table1'
   *   '<S3>/1-D Lookup Table1'
   */
  { 37.5, 20.625, 20.625, 20.625, 20.625, 20.625, 20.625, 20.625, 20.625, 20.625,
    50.0, 50.0, 51.875, 45.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
