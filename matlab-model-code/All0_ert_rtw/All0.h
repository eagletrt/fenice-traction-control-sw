/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: All0.h
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

#ifndef RTW_HEADER_All0_h_
#define RTW_HEADER_All0_h_
#include <math.h>
#include <string.h>
#ifndef All0_COMMON_INCLUDES_
#define All0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* All0_COMMON_INCLUDES_ */

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
  real_T Integrator_DSTATE;            /* '<S59>/Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S16>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator1_DSTAT_a;/* '<S9>/Discrete-Time Integrator1' */
  uint32_T m_bpIndex;                  /* '<S4>/1-D Lookup Table1' */
  uint32_T m_bpIndex_h;                /* '<S3>/1-D Lookup Table1' */
  uint32_T m_bpIndex_m;                /* '<S4>/1-D Lookup Table' */
  uint32_T m_bpIndex_d;                /* '<S3>/1-D Lookup Table' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S16>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_n;/* '<S9>/Discrete-Time Integrator1' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S3>/1-D Lookup Table'
   *   '<S4>/1-D Lookup Table'
   */
  real_T pooled2[14];

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S3>/1-D Lookup Table'
   *   '<S3>/1-D Lookup Table1'
   *   '<S4>/1-D Lookup Table'
   *   '<S4>/1-D Lookup Table1'
   */
  real_T pooled3[14];

  /* Expression: TV.KusT.K_us
   * Referenced by: '<S22>/K_us_table'
   */
  real_T K_us_table_tableData[10];

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S22>/K_us_table'
   */
  real_T K_us_table_bp01Data[10];

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S23>/P_table'
   */
  real_T P_table_tableData[9];

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S23>/I_table'
   *   '<S23>/P_table'
   */
  real_T pooled8[9];

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S23>/I_table'
   */
  real_T I_table_tableData[9];

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S3>/1-D Lookup Table1'
   *   '<S4>/1-D Lookup Table1'
   */
  real_T pooled14[14];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T lambda_ref;              /* Variable: lambda_ref
                                        * Referenced by:
                                        *   '<S6>/lambda_rl_max [-]'
                                        *   '<S13>/lambda_rr_max [-]'
                                        */

/* Model entry point functions */
extern void All0_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T *
  rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl, real_T *rtU_yaw_rate,
  real_T *rtU_Steeringangle, real_T *rtU_Brake, real_T *rtY_Tm_rr, real_T
  *rtY_Tm_rl);
extern void All0_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T
                      rtU_u_bar, real_T rtU_omega_rr, real_T rtU_omega_rl,
                      real_T rtU_yaw_rate, real_T rtU_Steeringangle, real_T
                      rtU_Brake, real_T *rtY_Tm_rr, real_T *rtY_Tm_rl);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
 * Block '<S13>/Scope' : Unused code path elimination
 * Block '<S5>/deltaT' : Unused code path elimination
 * Block '<S5>/deltarad' : Unused code path elimination
 * Block '<S5>/errore' : Unused code path elimination
 * Block '<S5>/omega' : Unused code path elimination
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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/All Control Active')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/All Control Active
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/All Control Active/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Saturation block'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Left Wheel1'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Right Wheel1'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Left Wheel1/PI control'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Left Wheel1/Slip_est1'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Left Wheel1/control reset switch'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Left Wheel1/PI control/Integral Part'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Left Wheel1/PI control/Proportional Part'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Left Wheel1/control reset switch/If Action Subsystem'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Left Wheel1/control reset switch/If Action Subsystem1'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Right Wheel1/PI control'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Right Wheel1/Slip_est1'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Right Wheel1/switching logic'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Right Wheel1/PI control/Integral Part'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Right Wheel1/PI control/Proportional Part'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Right Wheel1/switching logic/If Action Subsystem'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/TCS Rear Right Wheel1/switching logic/If Action Subsystem1'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Steering angle > 3deg'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/SteeringModel'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate estimator '
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate estimator /Yaw-Rate'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Anti-windup'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/D Gain'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Filter'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Filter ICs'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/I Gain'
 * '<S31>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain'
 * '<S32>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S33>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Integrator'
 * '<S34>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Integrator ICs'
 * '<S35>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/N Copy'
 * '<S36>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/N Gain'
 * '<S37>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/P Copy'
 * '<S38>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Parallel P Gain'
 * '<S39>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Reset Signal'
 * '<S40>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Saturation'
 * '<S41>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Saturation Fdbk'
 * '<S42>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Sum'
 * '<S43>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Sum Fdbk'
 * '<S44>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode'
 * '<S45>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode Sum'
 * '<S46>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Integral'
 * '<S47>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Ngain'
 * '<S48>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/postSat Signal'
 * '<S49>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/preSat Signal'
 * '<S50>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S51>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S52>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S53>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/D Gain/Disabled'
 * '<S54>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Filter/Disabled'
 * '<S55>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Filter ICs/Disabled'
 * '<S56>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/I Gain/External Parameters'
 * '<S57>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S58>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S59>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Integrator/Discrete'
 * '<S60>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S61>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S62>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/N Gain/Disabled'
 * '<S63>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/P Copy/Disabled'
 * '<S64>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S65>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Reset Signal/Disabled'
 * '<S66>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Saturation/Enabled'
 * '<S67>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S68>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Sum/Sum_PI'
 * '<S69>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S70>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S71>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S72>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S73>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S74>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S75>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Yaw-Rate Controller (old)/Yaw-Rate tracking/Discrete Varying PID/preSat Signal/Feedback_Path'
 */
#endif                                 /* RTW_HEADER_All0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
