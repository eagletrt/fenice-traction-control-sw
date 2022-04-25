/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Slip.h
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

#ifndef RTW_HEADER_Slip_h_
#define RTW_HEADER_Slip_h_
#include <math.h>
#include <string.h>
#ifndef Slip_COMMON_INCLUDES_
#define Slip_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Slip_COMMON_INCLUDES_ */

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
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S14>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator1_DSTAT_c;/* '<S7>/Discrete-Time Integrator1' */
  uint32_T m_bpIndex;                  /* '<S3>/1-D Lookup Table1' */
  uint32_T m_bpIndex_i;                /* '<S2>/1-D Lookup Table1' */
  uint32_T m_bpIndex_h;                /* '<S3>/1-D Lookup Table' */
  uint32_T m_bpIndex_ig;               /* '<S2>/1-D Lookup Table' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S14>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_d;/* '<S7>/Discrete-Time Integrator1' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: sc_sched.Kp)
   * Referenced by:
   *   '<S2>/1-D Lookup Table'
   *   '<S3>/1-D Lookup Table'
   */
  real_T pooled2[14];

  /* Pooled Parameter (Expression: sc_sched.speed)
   * Referenced by:
   *   '<S2>/1-D Lookup Table'
   *   '<S2>/1-D Lookup Table1'
   *   '<S3>/1-D Lookup Table'
   *   '<S3>/1-D Lookup Table1'
   */
  real_T pooled3[14];

  /* Pooled Parameter (Expression: sc_sched.Ki)
   * Referenced by:
   *   '<S2>/1-D Lookup Table1'
   *   '<S3>/1-D Lookup Table1'
   */
  real_T pooled10[14];
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
                                        *   '<S4>/lambda_rl_max [-]'
                                        *   '<S11>/lambda_rr_max [-]'
                                        */

/* Model entry point functions */
extern void Slip_initialize(RT_MODEL *const rtM, real_T *rtU_Driver_req, real_T *
  rtU_u_bar, real_T *rtU_omega_rr, real_T *rtU_omega_rl, real_T *rtU_yaw_rate,
  real_T *rtU_Steeringangle, real_T *rtU_Brake, real_T *rtY_Tm_rr, real_T
  *rtY_Tm_rl);
extern void Slip_step(RT_MODEL *const rtM, real_T rtU_Driver_req, real_T
                      rtU_u_bar, real_T rtU_omega_rr, real_T rtU_omega_rl,
                      real_T rtU_yaw_rate, real_T rtU_Brake, real_T *rtY_Tm_rr,
                      real_T *rtY_Tm_rl);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S11>/Scope' : Unused code path elimination
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
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/Slip Control')    - opens subsystem Fenice_VehicleModel/Vehicle Controller/Slip Control
 * hilite_system('Fenice_VehicleModel/Vehicle Controller/Slip Control/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fenice_VehicleModel/Vehicle Controller'
 * '<S1>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control'
 * '<S2>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Left Wheel1'
 * '<S3>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Right Wheel1'
 * '<S4>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Left Wheel1/PI control'
 * '<S5>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Left Wheel1/Slip_est1'
 * '<S6>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Left Wheel1/control reset switch'
 * '<S7>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Left Wheel1/PI control/Integral Part'
 * '<S8>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Left Wheel1/PI control/Proportional Part'
 * '<S9>'   : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Left Wheel1/control reset switch/If Action Subsystem'
 * '<S10>'  : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Left Wheel1/control reset switch/If Action Subsystem1'
 * '<S11>'  : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Right Wheel1/PI control'
 * '<S12>'  : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Right Wheel1/Slip_est1'
 * '<S13>'  : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Right Wheel1/switching logic'
 * '<S14>'  : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Right Wheel1/PI control/Integral Part'
 * '<S15>'  : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Right Wheel1/PI control/Proportional Part'
 * '<S16>'  : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Right Wheel1/switching logic/If Action Subsystem'
 * '<S17>'  : 'Fenice_VehicleModel/Vehicle Controller/Slip Control/TCS Rear Right Wheel1/switching logic/If Action Subsystem1'
 */
#endif                                 /* RTW_HEADER_Slip_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
