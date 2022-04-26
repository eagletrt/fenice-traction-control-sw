#ifndef MATLAB_SHIT_H
#define MATLAB_SHIT_H

#include <stdint.h>

/* "Observable states" ??? */
typedef struct {
  double DiscreteTimeIntegrator1_DSTATE;/* '<S14>/Discrete-Time Integrator1' */
  double DiscreteTimeIntegrator1_DSTAT_c;/* '<S7>/Discrete-Time Integrator1' */
  uint32_t m_bpIndex;                  /* '<S3>/1-D Lookup Table1' */
  uint32_t m_bpIndex_i;                /* '<S2>/1-D Lookup Table1' */
  uint32_t m_bpIndex_h;                /* '<S3>/1-D Lookup Table' */
  uint32_t m_bpIndex_ig;               /* '<S2>/1-D Lookup Table' */
  int8_t DiscreteTimeIntegrator1_PrevRes;/* '<S14>/Discrete-Time Integrator1' */
  int8_t DiscreteTimeIntegrator1_PrevR_d;/* '<S7>/Discrete-Time Integrator1' */
} Matlab_DW;

/* Real time model data struture */
typedef struct {
    char *errorStatus;
    Matlab_DW *dwork;
} Matlab_RTM;

#endif