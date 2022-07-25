/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: No.h
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

#ifndef RTW_HEADER_No_h_
#define RTW_HEADER_No_h_
#ifndef No_COMMON_INCLUDES_
#define No_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* No_COMMON_INCLUDES_ */

#include <stddef.h>

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Model entry point functions */
extern void No_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T
  *rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl, real_T *rtU_yaw_rate,
  real_T *rtU_Steeringangle, real_T *rtU_Brake, real_T *rtU_Tm_rl, real_T
  *rtU_Tm_rr, real_T *rtU_map_tv, real_T *rtU_map_sc, real_T *rtY_Tm_rr, real_T *
  rtY_Tm_rl);
extern void No_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T rtU_Tm_rl,
                    real_T rtU_Tm_rr, real_T *rtY_Tm_rr, real_T *rtY_Tm_rl);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/No Control')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/No Control
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/No Control/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/No Control'
 */
#endif                                 /* RTW_HEADER_No_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
