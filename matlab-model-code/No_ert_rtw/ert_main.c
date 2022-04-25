/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'No'.
 *
 * Model version                  : 3.3
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Mar 14 22:27:51 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "No.h"                        /* Model's header file */
#include "rtwtypes.h"

static RT_MODEL rtM_;
static RT_MODEL *const rtMPtr = &rtM_; /* Real-time model */

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
  No_step(rtM, rtU_Driver_req, &rtY_Tm_rr, &rtY_Tm_rl);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Pack model data into RTM */

  /* Initialize model */
  No_initialize(rtM, &rtU_Driver_req, &rtU_u_bar, &rtU_omega_rr, &rtU_omega_rl,
                &rtU_yaw_rate, &rtU_Steeringangle, &rtU_Brake, &rtY_Tm_rr,
                &rtY_Tm_rl);

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.001 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep(rtM);
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(rtM) == (NULL)) {
    /*  Perform other application tasks here */
  }

  /* Disable rt_OneStep() here */
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
