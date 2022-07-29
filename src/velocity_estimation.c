#include "velocity_estimation.h"
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>


/* Ridefinition of Matlab's data structure for the model */
typedef struct {
  double DiscreteFilter1_states;       /* '<S4>/Discrete Filter1' */
  double DiscreteFilter1_denStates;    /* '<S4>/Discrete Filter1' */
  double UnitDelay_DSTATE;             /* '<S4>/Unit Delay' */
  double DiscreteFilter2_states;       /* '<S4>/Discrete Filter2' */
  double DiscreteFilter2_denStates;    /* '<S4>/Discrete Filter2' */
} _VES_DW;

/* Ridefinition of Matlab's "handle" for the RealTimeModel */
typedef struct {
  const char *errorStatus;
  _VES_DW *dwork;
} _VES_RTM;

/* Pointers to the global variables in the velocity estimation library namespace */
double *_VES_axG, *_VES_omega_fl, *_VES_omega_fr, *_VES_omega_rl, *_VES_omega_rr, *_VES_map,
       *_VES_bar, *_VES_Tmax_rl, *_VES_Tmax_rr;


/* Function pointers for the library symbols to be loaded */
void (*_VES_init_model_fn)(_VES_RTM *);
void (*_VES_step_model_fn)(_VES_RTM *);
_VES_DW _VES_dw = { 0U };
_VES_RTM _VES_rt_model = { NULL, &_VES_dw };


bool VES_init() {
    /* Load the Matlab model compiled as a dynamic library */
    void *lib_handle = dlopen(VES_LIB_PATH, RTLD_NOW);

    if (lib_handle == NULL || dlerror()) {
        printf("Error while loading the velocity estimation dynamic library: %s", dlerror());
        return false;
    }

    /* Load the necessary symbols from the library */
    _VES_init_model_fn = dlsym(lib_handle, "Velocity_Estimation_initialize");
    _VES_step_model_fn = dlsym(lib_handle, "Velocity_Estimation_step");
    _VES_omega_fl = dlsym(lib_handle, "rtomega_fl");
    _VES_omega_fr = dlsym(lib_handle, "rtomega_fr");
    _VES_omega_rl = dlsym(lib_handle, "rtomega_rl");
    _VES_omega_rr = dlsym(lib_handle, "rtomega_rr");
    _VES_axG = dlsym(lib_handle, "rtaxG");
    _VES_map = dlsym(lib_handle, "rtsignal10");
    _VES_bar = dlsym(lib_handle, "rtu_bar");
    _VES_Tmax_rl = dlsym(lib_handle, "rtTmax_rl");
    _VES_Tmax_rr = dlsym(lib_handle, "rtTmax_rr");

    /* Check that variable pointers are not NULL and initiallize them to 0 */
    if (_VES_omega_fl && _VES_omega_fr && _VES_omega_rl && _VES_omega_rr && _VES_axG && _VES_map && \
    _VES_bar && _VES_Tmax_rl && _VES_Tmax_rr) {
        *_VES_omega_fl = 0.0;
        *_VES_omega_fr = 0.0;
        *_VES_omega_rl = 0.0;
        *_VES_omega_rr = 0.0;
        *_VES_axG = 0.0;
        *_VES_map = 0.0;
        *_VES_bar = 0.0;
        *_VES_Tmax_rl = 0.0;
        *_VES_Tmax_rr = 0.0;
    } else {
        printf("Error while loading a velocity estimation library variable: %s", dlerror());
        return false;
    }

    /* Check that function pointers are not NULL and initialize the model */
    if (_VES_init_model_fn && _VES_step_model_fn) {
        _VES_init_model_fn(&_VES_rt_model);
    } else {
        printf("Error while loading a velocity estimation library function: %s", dlerror());
        return false;
    }

    return true;
}

void VES_step_model(VES_DataInTypeDef *data_in, VES_DataOutTypeDef *data_out) {
    /* Copy over the input data */
    *_VES_omega_fl = data_in->omega_fl;
    *_VES_omega_fr = data_in->omega_fr;
    *_VES_omega_rl = data_in->omega_rl;
    *_VES_omega_rr = data_in->omega_rr;
    *_VES_axG = data_in->ax_g;
    *_VES_map = data_in->torque_map;

    /* Step the model */
    _VES_step_model_fn(&_VES_rt_model);

    /* Copy back the output data */
    data_out->bar = *_VES_bar;
    data_out->tmax_rl = *_VES_Tmax_rl;
    data_out->tmax_rr = *_VES_Tmax_rr;
}