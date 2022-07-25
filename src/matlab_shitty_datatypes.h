#ifndef MATLAB_SHIT_H
#define MATLAB_SHIT_H

#include <stdint.h>

/* "Observable states" ??? */
typedef struct {
  double Integrator_DSTATE;            /* '<S47>/Integrator' */
  double DiscreteTimeIntegrator1_DSTATE;/* '<S79>/Discrete-Time Integrator1' */
  double DiscreteTimeIntegrator1_DSTAT_k;/* '<S71>/Discrete-Time Integrator1' */
  uint32_t m_bpIndex;                  /* '<S66>/1-D Lookup Table3' */
  uint32_t m_bpIndex_h;                /* '<S65>/1-D Lookup Table1' */
  uint32_t m_bpIndex_f;                /* '<S66>/1-D Lookup Table2' */
  uint32_t m_bpIndex_k;                /* '<S65>/1-D Lookup Table' */
  int8_t DiscreteTimeIntegrator1_PrevRes;/* '<S79>/Discrete-Time Integrator1' */
  int8_t DiscreteTimeIntegrator1_PrevR_o;/* '<S71>/Discrete-Time Integrator1' */
} Matlab_DW;

/* Real time model data struture */
typedef struct {
    char *errorStatus;
    Matlab_DW *dwork;
} Matlab_RTM;

#endif