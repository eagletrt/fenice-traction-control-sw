/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
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

#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "Torque.h"                    /* Model header file */

static RT_MODEL rtM_;
static RT_MODEL *const rtMPtr = &rtM_; /* Real-time model */
static DW rtDW;                        /* Observable states */

/* '<Root>/driver_request' */
static real_T rtU_Driver_req;

/* '<Root>/u_bar' */
static real_T rtU_u_bar;

/* '<Root>/omega_rr' */
static real_T rtU_omega_rr;

/* '<Root>/omega_rl' */
static real_T rtU_omega_rl;

/* '<Root>/Omega' */
static real_T rtU_yaw_rate;

/* '<Root>/delta' */
static real_T rtU_Steeringangle;

/* '<Root>/Brake' */
static real_T rtU_Brake;

/* '<Root>/Tmax_rl' */
static real_T rtU_Tm_rl;

/* '<Root>/Tmax_rr' */
static real_T rtU_Tm_rr;

/* '<Root>/map_tv' */
static real_T rtU_map_tv;

/* '<Root>/map_sc' */
static real_T rtU_map_sc;

/* '<Root>/Tm_rr' */
static real_T rtY_Tm_rr;

/* '<Root>/Tm_rl' */
static real_T rtY_Tm_rl;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL *const rtM);
void rt_OneStep(RT_MODEL *const rtM)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  Torque_step(rtM, rtU_Driver_req, rtU_u_bar, rtU_yaw_rate, rtU_Steeringangle,
              rtU_Tm_rl, rtU_Tm_rr, rtU_map_tv, &rtY_Tm_rr, &rtY_Tm_rl);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example main function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific. This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Pack model data into RTM */
  rtM->dwork = &rtDW;

  /* Initialize model */
  Torque_initialize(rtM, &rtU_Driver_req, &rtU_u_bar, &rtU_omega_rr,
                    &rtU_omega_rl, &rtU_yaw_rate, &rtU_Steeringangle, &rtU_Brake,
                    &rtU_Tm_rl, &rtU_Tm_rr, &rtU_map_tv, &rtU_map_sc, &rtY_Tm_rr,
                    &rtY_Tm_rl);

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.001 seconds (base rate of the model) here.
   * The call syntax for rt_OneStep is
   *
   *  rt_OneStep(rtM);
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(rtM) == (NULL)) {
    /*  Perform application tasks here */
  }

  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
