/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque.h
 *
 * Code generated for Simulink model 'Torque'.
 *
 * Model version                  : 3.3
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Mar 14 22:26:33 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Torque_h_
#define RTW_HEADER_Torque_h_
#include <math.h>
#include <string.h>
#ifndef Torque_COMMON_INCLUDES_
#define Torque_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Torque_COMMON_INCLUDES_ */

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

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S44>/Integrator' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: TV.KusT.K_us
   * Referenced by: '<S7>/K_us_table'
   */
  real_T K_us_table_tableData[10];

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S7>/K_us_table'
   */
  real_T K_us_table_bp01Data[10];

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S8>/P_table'
   */
  real_T P_table_tableData[9];

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S8>/I_table'
   *   '<S8>/P_table'
   */
  real_T pooled1[9];

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S8>/I_table'
   */
  real_T I_table_tableData[9];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Torque_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req,
  real_T *rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl, real_T
  *rtU_yaw_rate, real_T *rtU_Steeringangle, real_T *rtU_Brake, real_T *rtY_Tm_rr,
  real_T *rtY_Tm_rl);
extern void Torque_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T
  rtU_u_bar, real_T rtU_yaw_rate, real_T rtU_Steeringangle, real_T *rtY_Tm_rr,
  real_T *rtY_Tm_rl);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/deltaT' : Unused code path elimination
 * Block '<S4>/deltarad' : Unused code path elimination
 * Block '<S4>/errore' : Unused code path elimination
 * Block '<S4>/omega' : Unused code path elimination
 */

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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/Torque vectoring')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/Torque vectoring
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/Torque vectoring/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Saturation block'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Steering angle > 3deg'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/SteeringModel'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate estimator '
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate estimator /Yaw-Rate'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Anti-windup'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/D Gain'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Filter'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Filter ICs'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/I Gain'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Integrator'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Integrator ICs'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/N Copy'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/N Gain'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/P Copy'
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Parallel P Gain'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Reset Signal'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Saturation'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Saturation Fdbk'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Sum'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Sum Fdbk'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode Sum'
 * '<S31>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Integral'
 * '<S32>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Ngain'
 * '<S33>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/postSat Signal'
 * '<S34>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/preSat Signal'
 * '<S35>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S36>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S37>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S38>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/D Gain/Disabled'
 * '<S39>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Filter/Disabled'
 * '<S40>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Filter ICs/Disabled'
 * '<S41>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/I Gain/External Parameters'
 * '<S42>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S43>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S44>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Integrator/Discrete'
 * '<S45>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S46>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S47>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/N Gain/Disabled'
 * '<S48>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/P Copy/Disabled'
 * '<S49>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S50>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Reset Signal/Disabled'
 * '<S51>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Saturation/Enabled'
 * '<S52>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S53>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Sum/Sum_PI'
 * '<S54>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S55>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S56>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S57>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S58>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S59>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S60>'  : 'Fenice_VehicleModel/Vehicle Controller/Torque vectoring/PI Control/Yaw-Rate Controller/Yaw-Rate tracking/Discrete Varying PID/preSat Signal/Feedback_Path'
 */
#endif                                 /* RTW_HEADER_Torque_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
