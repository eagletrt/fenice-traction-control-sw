/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: No.c
 *
 * Code generated for Simulink model 'No'.
 *
 * Model version                  : 5.241
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sat May 21 16:04:53 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "No.h"
#include "rtwtypes.h"

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

/* Model step function */
void No_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T rtU_Tm_rl,
             real_T rtU_Tm_rr, real_T *rtY_Tm_rr, real_T *rtY_Tm_rl)
{
  /* Outport: '<Root>/Tm_rr' incorporates:
   *  Inport: '<Root>/Tmax_rr'
   *  Inport: '<Root>/driver_request'
   *  Product: '<S1>/Product'
   */
  *rtY_Tm_rr = rtU_Driver_req * rtU_Tm_rr;

  /* Outport: '<Root>/Tm_rl' incorporates:
   *  Inport: '<Root>/Tmax_rl'
   *  Inport: '<Root>/driver_request'
   *  Product: '<S1>/Product1'
   */
  *rtY_Tm_rl = rtU_Tm_rl * rtU_Driver_req;
  UNUSED_PARAMETER(rtM);
}

/* Model initialize function */
void No_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T
                   *rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl,
                   real_T *rtU_yaw_rate, real_T *rtU_Steeringangle, real_T
                   *rtU_Brake, real_T *rtU_Tm_rl, real_T *rtU_Tm_rr, real_T
                   *rtU_map_tv, real_T *rtU_map_sc, real_T *rtY_Tm_rr, real_T
                   *rtY_Tm_rl)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(rtM, (NULL));

  /* external inputs */
  *rtU_Driver_req = 0.0;
  *rtU_u_bar = 0.0;
  *rtU_omega_rr = 0.0;
  *rtU_omega_rl = 0.0;
  *rtU_yaw_rate = 0.0;
  *rtU_Steeringangle = 0.0;
  *rtU_Brake = 0.0;
  *rtU_Tm_rl = 0.0;
  *rtU_Tm_rr = 0.0;
  *rtU_map_tv = 0.0;
  *rtU_map_sc = 0.0;

  /* external outputs */
  *rtY_Tm_rr = 0.0;
  *rtY_Tm_rl = 0.0;
  UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
