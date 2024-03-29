#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "string.h"
#include "models_interface.h"
#include "logger.h"


/* Ridefinition of Matlab's data structure for the model */
typedef struct {
  uint8_t dummy_memory[64];
} Matlab_DW;

/* Real time model data struture */
typedef struct {
    char *errorStatus;
    Matlab_DW *dwork;
} Matlab_RTM;

/* Pointers to the global variables in the velocity estimation library namespace */
double *_CTRL_dreq, *_CTRL_delta, *_CTRL_tmax_rl, *_CTRL_tmax_rr, *_CTRL_omega_rl, *_CTRL_omega_rr,
       *_CTRL_map_tv, *_CTRL_map_sc, *_CTRL_brake, *_CTRL_bar, *_CTRL_omega,
       *_CTRL_t_rl, *_CTRL_t_rr;


Matlab_DW _CTRL_DW = { 0U };
Matlab_RTM _CTRL_rt_model = { NULL, &_CTRL_DW };
void (*_CTRL_init_model_fn) (Matlab_RTM *);
void (*_CTRL_step_model_fn) (Matlab_RTM *);
void *_CTRL_lib_handle = NULL;
CTRL_ModeTypeDef _CTRL_curr_mode = CTRL_Mode_None;
bool _CTRL_initialization_ok = false;


bool _load_model_lib();
bool _load_lib_syms();


void CTRL_step_model(CTRL_ModelInputTypeDef *data_in, CTRL_ModelOutputTypeDef *data_out) {
    if (!_CTRL_initialization_ok) {
        LOG_write(LOGLEVEL_ERR, "[CTRL] Model not initialized");
        return;
    }

    /* Copy over the input data */
    *_CTRL_dreq     = data_in->dreq;
    *_CTRL_delta    = data_in->delta;
    *_CTRL_tmax_rl  = data_in->tmax_rl;
    *_CTRL_tmax_rr  = data_in->tmax_rr;
    *_CTRL_omega_rl = data_in->omega_rl;
    *_CTRL_omega_rr = data_in->omega_rr;
    *_CTRL_map_tv   = data_in->map_tv;
    *_CTRL_map_sc   = data_in->map_sc;
    *_CTRL_brake    = data_in->brake;
    *_CTRL_bar      = data_in->bar;
    *_CTRL_omega    = data_in->omega;

    /* Step the model */
    _CTRL_step_model_fn(&_CTRL_rt_model);

    /* Copy back the output data */
    data_out->tm_rl = *_CTRL_t_rl;
    data_out->tm_rr = *_CTRL_t_rr;
}

/**
 * @brief Change the traction control model being used by loading the appropriate dynamic library
 */
void CTRL_change_mode(CTRL_ModeTypeDef new_mode) {
    if (new_mode == _CTRL_curr_mode && _CTRL_initialization_ok)
        return;

    _CTRL_initialization_ok = false;
    _CTRL_curr_mode = new_mode;

    /* Reset model state */
    memset(&(_CTRL_DW.dummy_memory), sizeof(_CTRL_DW.dummy_memory[0]), sizeof(_CTRL_DW.dummy_memory));
    
    /* Load current model library and its symbols */
    if (_load_model_lib() && _load_lib_syms())
        _CTRL_initialization_ok = true;
    else
        LOG_write(LOGLEVEL_ERR, "[CTRL] Failed to intialize model");
}

/**
 * @brief Dynamically load the shared library of the currently in-use model
 */
bool _load_model_lib() {
    char *lib_path;     /* Filesystem path of the DL to load */

    switch (_CTRL_curr_mode) {
        case (CTRL_Mode_None):
            lib_path = "./libctrl-no.so";
            break;
        case (CTRL_Mode_Slip):
            lib_path = "./libctrl-sc.so";
            break;
        case (CTRL_Mode_Torque):
            lib_path = "./libctrl-tv.so";
            break;
        case (CTRL_Mode_Complete):
            lib_path = "./libctrl-all.so";
            break;
        default:
            LOG_write(LOGLEVEL_ERR, "[CTRL] Error loading dynamic library - unknown CTRL_ModeTypeDef: %d", _CTRL_curr_mode);
            return false;
    }

    /* Make sure no other model library is loaded */
    if (_CTRL_lib_handle)
        dlclose(_CTRL_lib_handle);
    
    /* Attempt to load the dynamic library */
    _CTRL_lib_handle = dlopen(lib_path, RTLD_NOW);

    if (!_CTRL_lib_handle) {
        LOG_write(LOGLEVEL_ERR, "[CTRL] Error loading dynamic library (%s): %s", lib_path, dlerror());
        return false;
    }
    
    LOG_write(LOGLEVEL_INFO, "[CTRL] Successfully loaded dynamic control model: %s", lib_path);
    return true;
}

/**
 * @brief Load the function pointers to the init and step methods of the currently in-use model
 */
bool _load_lib_syms() {
    char *i_fn_sym, *s_fn_sym;

    switch (_CTRL_curr_mode) {
        case (CTRL_Mode_None):
            i_fn_sym = "No_initialize";
            s_fn_sym = "No_step";
            break;
        case (CTRL_Mode_Slip):
            i_fn_sym = "Slip_initialize";
            s_fn_sym = "Slip_step";
            break;
        case (CTRL_Mode_Torque):
            i_fn_sym = "Torque_initialize";
            s_fn_sym = "Torque_step";
            break;
        case (CTRL_Mode_Complete):
            i_fn_sym = "All0_initialize";
            s_fn_sym = "All0_step";       
            break;
        default:
            LOG_write(LOGLEVEL_ERR, "[CTRL] Error loading dynamic library symbols - unknown CTRL_ModeTypeDef: %d", _CTRL_curr_mode);
            return false;
    }

    /* Load functions */
    _CTRL_init_model_fn = dlsym(_CTRL_lib_handle, i_fn_sym);
    _CTRL_step_model_fn = dlsym(_CTRL_lib_handle, s_fn_sym);

    if (_CTRL_init_model_fn == NULL || _CTRL_step_model_fn == NULL || dlerror()) {
        LOG_write(LOGLEVEL_ERR, "[CTRL] Error loading library functions: %s", dlerror());
        return false;
    }

    /* Load global variables */
    _CTRL_dreq     = dlsym(_CTRL_lib_handle, "rtDriver_req");
    _CTRL_delta    = dlsym(_CTRL_lib_handle, "rtSteeringangle");
    _CTRL_tmax_rl  = dlsym(_CTRL_lib_handle, "rtTm_rl");
    _CTRL_tmax_rr  = dlsym(_CTRL_lib_handle, "rtTm_rr");
    _CTRL_omega_rl = dlsym(_CTRL_lib_handle, "rtomega_rl");
    _CTRL_omega_rr = dlsym(_CTRL_lib_handle, "rtomega_rr");
    _CTRL_map_sc   = dlsym(_CTRL_lib_handle, "rtmap_sc");
    _CTRL_map_tv   = dlsym(_CTRL_lib_handle, "rtmap_tv");
    _CTRL_brake    = dlsym(_CTRL_lib_handle, "rtbrake");
    _CTRL_bar      = dlsym(_CTRL_lib_handle, "rtu_bar");
    _CTRL_omega    = dlsym(_CTRL_lib_handle, "rtyaw_rate");
    _CTRL_t_rl     = dlsym(_CTRL_lib_handle, "rtTm_rl_a");
    _CTRL_t_rr     = dlsym(_CTRL_lib_handle, "rtTm_rr_m");

    if (_CTRL_dreq && _CTRL_delta && _CTRL_tmax_rl && _CTRL_tmax_rr && _CTRL_omega_rl && _CTRL_omega_rr &&
    _CTRL_map_tv && _CTRL_map_sc && _CTRL_brake && _CTRL_bar && _CTRL_omega && _CTRL_t_rl && _CTRL_t_rr) {
        *_CTRL_dreq = 0.0;
        *_CTRL_delta = 0.0;
        *_CTRL_tmax_rl = 0.0;
        *_CTRL_tmax_rr = 0.0;
        *_CTRL_omega_rl = 0.0;
        *_CTRL_omega_rr = 0.0;
        *_CTRL_map_tv = 0.0;
        *_CTRL_map_sc = 0.0;
        *_CTRL_brake = 0.0;
        *_CTRL_bar = 0.0;
        *_CTRL_omega = 0.0;
        *_CTRL_t_rl = 0.0;
        *_CTRL_t_rr = 0.0;
    } else {
       LOG_write(LOGLEVEL_ERR, "Error loading global variables: %s", dlerror());
        return false;
    }

    _CTRL_init_model_fn(&_CTRL_rt_model);
    return true;
}