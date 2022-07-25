#include "velocity_estimation.h"
#include <dlfcn.h>


/* Ridefinition of Matlab's data structure for the model */
typedef struct {
  double DiscreteFilter1_states;       /* '<S4>/Discrete Filter1' */
  double DiscreteFilter1_denStates;    /* '<S4>/Discrete Filter1' */
  double UnitDelay_DSTATE;             /* '<S4>/Unit Delay' */
  double DiscreteFilter2_states;       /* '<S4>/Discrete Filter2' */
  double DiscreteFilter2_denStates;    /* '<S4>/Discrete Filter2' */
} _VES_DW;

/* Ridefinition of Matlab's "handle" for the RealTimeModel*/
typedef struct {
  const char *errorStatus;
  _VES_DW *dwork;
} _VES_RTM;


/* Function pointers for the library symbols to be loaded */
void (*_VES_init_model)(_VES_RTM *, double*, double*, double*, double*, double*, double*, double*, double*, double*, double*);
void (*_VES_step_model)(_VES_RTM *,  double,  double,  double,  double,  double,  double, double*, double*, double*);
bool _VES_is_model_initialized = false;
_VES_RTM _VES_rt_model = {};


bool VES_init() {
    /* Load the Matlab model compiled as a dynamic library */
    void *lib_handle = dlopen(VES_LIB_PATH, RTLD_NOW);

    if (lib_handle == NULL) {
        printf("Error while loading the velocity estimation dynamic library: %s", dlerror());
        return false;
    }

    /* Load the necessary symbols from the library */
    _VES_init_model = dlsym(lib_handle, "Velocity_Estimation_initialize");
    _VES_step_model = dlsym(lib_handle, "Velocity_Estimation_step");

    if (_VES_init_model == NULL || _VES_step_model == NULL) {
        printf("Error while loading a velocity estimation library symbol: %s", dlerror());
        return false;
    }

    /* Mark the model as not initialized and return */
    _VES_is_model_initialized = false;
    return true;
}

void VES_step_model(VES_DataIn *data_in, VES_DataOut *data_out) {
    if (_VES_init_model == NULL || _VES_step_model == NULL) {
        printf("The velocity estimation library has not been loaded yet");
        return;
    }

    if (_VES_is_model_initialized) {
        _VES_step_model(
            &(_VES_rt_model),
            data_in->omega_fl, data_in->omega_fr, data_in->omega_rl, data_in->omega_rr,
            data_in->ax_g,
            data_in->torque_map,
            &(data_out->u),
            &(data_out->bar),
            &(data_out->tmax_rr),
            &(data_out->tmax_rl)
        );
    } else {
        _VES_init_model(
            &(_VES_rt_model),
            &(data_in->omega_fl), &(data_in->omega_fr), &(data_in->omega_rl), &(data_in->omega_rr),
            &(data_in->ax_g),
            &(data_in->torque_map),
            &(data_out->u),
            &(data_out->bar),
            &(data_out->tmax_rr),
            &(data_out->tmax_rl)
        );
        _VES_is_model_initialized = true;
    }
}