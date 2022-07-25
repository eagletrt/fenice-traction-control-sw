/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_data.c
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 5.241
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sat May 21 16:04:27 2022
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
   *   '<S10>/1-D Lookup Table2'
   */
  { 0.0, 1.0 },

  /* Expression: TV.KusT.K_us
   * Referenced by: '<S9>/K_us_table'
   */
  { -5.6E-5, -0.00065, -0.000739, -0.000691, -0.000489, -0.000117, 0.0003,
    0.000657, 0.000908, 0.001289 },

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S9>/K_us_table'
   */
  { 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0 },

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S10>/P_table'
   */
  { 725.778388, 714.991781, 717.127171, 725.372387, 735.915544, 745.859577,
    753.080441, 756.062299 },

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S10>/I_table'
   *   '<S10>/P_table'
   */
  { 5.555556, 8.333333, 11.111111, 13.888889, 16.666667, 19.444444, 22.222222,
    25.0 },

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S10>/I_table'
   */
  { 62510.227254, 42204.626597, 31989.404929, 25716.89812, 21375.905604,
    18122.799519, 15544.254837, 13367.430797 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
