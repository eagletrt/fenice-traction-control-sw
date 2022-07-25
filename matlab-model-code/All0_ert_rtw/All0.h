/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: All0.h
 *
 * Code generated for Simulink model 'All0'.
 *
 * Model version                  : 5.241
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sat May 21 16:02:45 2022
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
#ifndef All0_COMMON_INCLUDES_
#define All0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* All0_COMMON_INCLUDES_ */

#include <string.h>

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
  real_T Integrator_DSTATE;            /* '<S47>/Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S79>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator1_DSTAT_k;/* '<S71>/Discrete-Time Integrator1' */
  uint32_T m_bpIndex;                  /* '<S66>/1-D Lookup Table3' */
  uint32_T m_bpIndex_h;                /* '<S65>/1-D Lookup Table1' */
  uint32_T m_bpIndex_f;                /* '<S66>/1-D Lookup Table2' */
  uint32_T m_bpIndex_k;                /* '<S65>/1-D Lookup Table' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S79>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_o;/* '<S71>/Discrete-Time Integrator1' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S2>/1-D Lookup Table2'
   *   '<S10>/1-D Lookup Table2'
   *   '<S65>/1-D Lookup Table2'
   *   '<S66>/1-D Lookup Table1'
   */
  real_T pooled2[2];

  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S65>/1-D Lookup Table'
   *   '<S66>/1-D Lookup Table2'
   */
  real_T pooled3[10];

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S65>/1-D Lookup Table'
   *   '<S65>/1-D Lookup Table1'
   *   '<S66>/1-D Lookup Table2'
   *   '<S66>/1-D Lookup Table3'
   */
  real_T pooled4[10];

  /* Expression: TV.KusT.K_us
   * Referenced by: '<S9>/K_us_table'
   */
  real_T K_us_table_tableData[10];

  /* Expression: TV.KusT.u_vals
   * Referenced by: '<S9>/K_us_table'
   */
  real_T K_us_table_bp01Data[10];

  /* Expression: TV.PID.Kp_vals
   * Referenced by: '<S10>/P_table'
   */
  real_T P_table_tableData[8];

  /* Pooled Parameter (Expression: TV.PID.u_vals)
   * Referenced by:
   *   '<S10>/I_table'
   *   '<S10>/P_table'
   */
  real_T pooled9[8];

  /* Expression: TV.PID.Ki_vals
   * Referenced by: '<S10>/I_table'
   */
  real_T I_table_tableData[8];

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S65>/1-D Lookup Table1'
   *   '<S66>/1-D Lookup Table3'
   */
  real_T pooled13[10];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void All0_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T *
  rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl, real_T *rtU_yaw_rate,
  real_T *rtU_Steeringangle, real_T *rtU_Brake, real_T *rtU_Tm_rl, real_T
  *rtU_Tm_rr, real_T *rtU_map_tv, real_T *rtU_map_sc, real_T *rtY_Tm_rr, real_T *
  rtY_Tm_rl);
extern void All0_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T
                      rtU_u_bar, real_T rtU_omega_rr, real_T rtU_omega_rl,
                      real_T rtU_yaw_rate, real_T rtU_Steeringangle, real_T
                      rtU_Brake, real_T rtU_Tm_rl, real_T rtU_Tm_rr, real_T
                      rtU_map_tv, real_T rtU_map_sc, real_T *rtY_Tm_rr, real_T
                      *rtY_Tm_rl);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S55>/Data Type Duplicate' : Unused code path elimination
 * Block '<S55>/Data Type Propagation' : Unused code path elimination
 * Block '<S2>/deltaT' : Unused code path elimination
 * Block '<S2>/deltarad' : Unused code path elimination
 * Block '<S2>/errore' : Unused code path elimination
 * Block '<S2>/omega' : Unused code path elimination
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S68>/Data Type Duplicate' : Unused code path elimination
 * Block '<S68>/Data Type Propagation' : Unused code path elimination
 * Block '<S75>/Scope' : Unused code path elimination
 * Block '<S76>/Data Type Duplicate' : Unused code path elimination
 * Block '<S76>/Data Type Propagation' : Unused code path elimination
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
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Saturation Dynamic'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Saturation Dynamic1'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Saturation block'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Steering angle > 2deg'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/SteeringModel'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate estimator '
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate estimator /Yaw-Rate'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/D Gain'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Filter'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Filter ICs'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/I Gain'
 * '<S18>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain'
 * '<S19>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain Fdbk'
 * '<S20>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Integrator'
 * '<S21>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Integrator ICs'
 * '<S22>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/N Copy'
 * '<S23>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/N Gain'
 * '<S24>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/P Copy'
 * '<S25>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Parallel P Gain'
 * '<S26>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Reset Signal'
 * '<S27>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation'
 * '<S28>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation Fdbk'
 * '<S29>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Sum'
 * '<S30>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Sum Fdbk'
 * '<S31>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode'
 * '<S32>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode Sum'
 * '<S33>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Integral'
 * '<S34>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Ngain'
 * '<S35>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/postSat Signal'
 * '<S36>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/preSat Signal'
 * '<S37>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel'
 * '<S38>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S39>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S40>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S41>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/D Gain/Disabled'
 * '<S42>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Filter/Disabled'
 * '<S43>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Filter ICs/Disabled'
 * '<S44>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/I Gain/External Parameters'
 * '<S45>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain/Passthrough'
 * '<S46>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Ideal P Gain Fdbk/Passthrough'
 * '<S47>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Integrator/Discrete'
 * '<S48>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Integrator ICs/Internal IC'
 * '<S49>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/N Copy/Disabled wSignal Specification'
 * '<S50>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/N Gain/Disabled'
 * '<S51>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/P Copy/Disabled'
 * '<S52>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Parallel P Gain/External Parameters'
 * '<S53>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Reset Signal/Disabled'
 * '<S54>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation/External'
 * '<S55>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation/External/Saturation Dynamic'
 * '<S56>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Saturation Fdbk/Passthrough'
 * '<S57>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Sum/Sum_PI'
 * '<S58>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Sum Fdbk/Enabled'
 * '<S59>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode/Disabled'
 * '<S60>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tracking Mode Sum/Passthrough'
 * '<S61>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Integral/Passthrough'
 * '<S62>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/Tsamp - Ngain/Passthrough'
 * '<S63>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/postSat Signal/Feedback_Path'
 * '<S64>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/PI Control/Yaw-Rate tracking/Discrete Varying PID/preSat Signal/Feedback_Path'
 * '<S65>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1'
 * '<S66>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1'
 * '<S67>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/PI control'
 * '<S68>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/Saturation Dynamic'
 * '<S69>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/Slip_est1'
 * '<S70>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/control reset switch'
 * '<S71>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/PI control/Integral Part'
 * '<S72>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/PI control/Proportional Part'
 * '<S73>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/control reset switch/If Action Subsystem'
 * '<S74>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Left Wheel1/control reset switch/If Action Subsystem1'
 * '<S75>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/PI control1'
 * '<S76>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/Saturation Dynamic'
 * '<S77>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/Slip_est2'
 * '<S78>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/switching logic1'
 * '<S79>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/PI control1/Integral Part'
 * '<S80>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/PI control1/Proportional Part'
 * '<S81>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/switching logic1/If Action Subsystem'
 * '<S82>'  : 'Fenice_VehicleModel/Vehicle Controller/All Control Active/Slip for simulation/TCS Rear Right Wheel1/switching logic1/If Action Subsystem1'
 */
#endif                                 /* RTW_HEADER_All0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
