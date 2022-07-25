/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Slip_data.c
 *
 * Code generated for Simulink model 'Slip'.
 *
 * Model version                  : 5.241
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sat May 21 16:03:14 2022
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
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S4>/1-D Lookup Table2'
   *   '<S5>/1-D Lookup Table2'
   */
  { 0.0, 1.0 },

  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S4>/1-D Lookup Table'
   *   '<S5>/1-D Lookup Table'
   */
  { 90.1086993951195, 97.706766136813, 97.779654209522, 97.7652517570111,
    97.0727083701121, 94.532403849043, 90.8074596427232, 90.0, 90.0, 90.0 },

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S4>/1-D Lookup Table'
   *   '<S4>/1-D Lookup Table1'
   *   '<S5>/1-D Lookup Table'
   *   '<S5>/1-D Lookup Table1'
   */
  { 0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0 },

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S4>/1-D Lookup Table1'
   *   '<S5>/1-D Lookup Table1'
   */
  { 20.0122411565707, 23.9799258614183, 24.0671225380504, 24.1427953562211,
    23.6765451970367, 21.6213330838734, 20.0460125761758, 20.0, 20.0, 20.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
