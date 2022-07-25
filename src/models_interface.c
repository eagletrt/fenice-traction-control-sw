#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include "models_interface.h"
#include "matlab_shitty_datatypes.h"


Matlab_DW _CTRL_DW;
Matlab_RTM _CTRL_rtm = { NULL, &_CTRL_DW };

CTRL_MODE _CTRL_curr_mode = CTRL_NONE;
bool _CTRL_is_model_initialized = false;

void (*_CTRL_model_sc_init_fn) (Matlab_RTM*, double*, double*, double*, double*, double*, double*, double*, double*, double*);
void (*_CTRL_model_sc_step_fn) (Matlab_RTM*, double, double, double, double, double, double, double, double*, double*);
void *_CTRL_libsc_handle = NULL;

void (*_CTRL_model_tv_init_fn) (Matlab_RTM*, double*, double*, double*, double*, double*, double*, double*, double*, double*);
void (*_CTRL_model_tv_step_fn) (Matlab_RTM*, double, double, double, double, double, double, double, double*, double*);
void *_CTRL_libtv_handle = NULL;

void (*_CTRL_model_all_init_fn) (Matlab_RTM*, double*, double*, double*, double*, double*, double*, double*, double*, double*);
void (*_CTRL_model_all_step_fn) (Matlab_RTM*, double, double, double, double, double, double, double, double*, double*);
void *_CTRL_liball_handle = NULL;

void (*_CTRL_model_no_init_fn) (Matlab_RTM*, double*, double*, double*, double*, double*, double*, double*, double*, double*);
void (*_CTRL_model_no_step_fn) (Matlab_RTM*, double, double*, double*);
void *_CTRL_libno_handle = NULL;


void _unload_all_libs();
void _load_model_lib();
void _load_lib_syms();


CTRL_ModelOutputTypeDef CTRL_step_model(CTRL_ModelInputTypeDef data_in) {
    CTRL_ModelOutputTypeDef data_out;

    switch (_CTRL_curr_mode) {
        case (CTRL_NONE):
            if (!_CTRL_is_model_initialized)
                (*_CTRL_model_no_init_fn)(
                    &_CTRL_rtm,
                    &(data_in.rtU_Driver_req),
                    &(data_in.rtU_u_bar),
                    &(data_in.rtU_omega_rr),
                    &(data_in.rtU_omega_rl),
                    &(data_in.rtU_yaw_rate),
                    &(data_in.rtU_Steeringangle),
                    &(data_in.rtU_Brake),
                    &(data_out.rtY_Tm_rr),
                    &(data_out.rtY_Tm_rl)
                );
            else
                (*_CTRL_model_no_step_fn)(
                    &_CTRL_rtm,
                    data_in.rtU_Driver_req,
                    &(data_out.rtY_Tm_rr),
                    &(data_out.rtY_Tm_rl)
                );
            break;
        case (CTRL_SC):
            if (!_CTRL_is_model_initialized)
                (*_CTRL_model_sc_init_fn)(
                    &_CTRL_rtm,
                    &(data_in.rtU_Driver_req),
                    &(data_in.rtU_u_bar),
                    &(data_in.rtU_omega_rr),
                    &(data_in.rtU_omega_rl),
                    &(data_in.rtU_yaw_rate),
                    &(data_in.rtU_Steeringangle),
                    &(data_in.rtU_Brake),
                    &(data_out.rtY_Tm_rr),
                    &(data_out.rtY_Tm_rl)
                );
            else
                (*_CTRL_model_sc_step_fn)(
                    &_CTRL_rtm,
                    data_in.rtU_Driver_req,
                    data_in.rtU_u_bar,
                    data_in.rtU_omega_rr,
                    data_in.rtU_omega_rl,
                    data_in.rtU_yaw_rate,
                    data_in.rtU_Steeringangle,
                    data_in.rtU_Brake,
                    &(data_out.rtY_Tm_rr),
                    &(data_out.rtY_Tm_rl)
                );
            break;
        case (CTRL_TV):
            if (!_CTRL_is_model_initialized)
                (*_CTRL_model_tv_init_fn)(
                    &_CTRL_rtm,
                    &(data_in.rtU_Driver_req),
                    &(data_in.rtU_u_bar),
                    &(data_in.rtU_omega_rr),
                    &(data_in.rtU_omega_rl),
                    &(data_in.rtU_yaw_rate),
                    &(data_in.rtU_Steeringangle),
                    &(data_in.rtU_Brake),
                    &(data_out.rtY_Tm_rr),
                    &(data_out.rtY_Tm_rl)
                );
            else
                (*_CTRL_model_tv_step_fn)(
                    &_CTRL_rtm,
                    data_in.rtU_Driver_req,
                    data_in.rtU_u_bar,
                    data_in.rtU_omega_rr,
                    data_in.rtU_omega_rl,
                    data_in.rtU_yaw_rate,
                    data_in.rtU_Steeringangle,
                    data_in.rtU_Brake,
                    &(data_out.rtY_Tm_rr),
                    &(data_out.rtY_Tm_rl)
                );
            break;
        case (CTRL_ALL): 
            if (!_CTRL_is_model_initialized)
                (*_CTRL_model_all_init_fn)(
                    &_CTRL_rtm,
                    &(data_in.rtU_Driver_req),
                    &(data_in.rtU_u_bar),
                    &(data_in.rtU_omega_rr),
                    &(data_in.rtU_omega_rl),
                    &(data_in.rtU_yaw_rate),
                    &(data_in.rtU_Steeringangle),
                    &(data_in.rtU_Brake),
                    &(data_out.rtY_Tm_rr),
                    &(data_out.rtY_Tm_rl)
                );
            else
                (*_CTRL_model_all_step_fn)(
                    &_CTRL_rtm,
                    data_in.rtU_Driver_req,
                    data_in.rtU_u_bar,
                    data_in.rtU_omega_rr,
                    data_in.rtU_omega_rl,
                    data_in.rtU_yaw_rate,
                    data_in.rtU_Steeringangle,
                    data_in.rtU_Brake,
                    &(data_out.rtY_Tm_rr),
                    &(data_out.rtY_Tm_rl)
                );     
            break;
        default:
            printf("Error stepping model - unknown CTRL_MODE: %d\n", _CTRL_curr_mode);
            break;
    }

    _CTRL_is_model_initialized = true;
    return data_out;
}

/**
 * @brief Change the traction control model being used by loading the appropriate dynamic library
 */
void CTRL_change_mode(CTRL_MODE new_mode) {
    _CTRL_curr_mode = new_mode;
    _CTRL_is_model_initialized = false;

    /* Ensure all other libs are unloaded to avoid namespace conflicts */
    _unload_all_libs();

    /* Load current model library */
    _load_model_lib();

    /* Load current model's init and step functions */
    _load_lib_syms();
}

/**
 * @brief Make sure that all dynamic libraries are unloaded
 */
void _unload_all_libs() {
    if (_CTRL_libsc_handle)
        dlclose(_CTRL_libsc_handle);
    if (_CTRL_libtv_handle)
        dlclose(_CTRL_libtv_handle);
    if (_CTRL_liball_handle)
        dlclose(_CTRL_liball_handle);
    if (_CTRL_libno_handle)
        dlclose(_CTRL_libno_handle);
}

/**
 * @brief Dynamically load the shared library of the currently in-use model
 */
void _load_model_lib() {
    char *lib_path;     /* Filesystem path of the DL to load */
    void **lib_handle;  /* Pointer to the variable that will contaian the DL handle */

    switch (_CTRL_curr_mode) {
        case (CTRL_NONE):
            lib_path = "./libctrl-no.so";
            lib_handle = &_CTRL_libno_handle;
            break;
        case (CTRL_SC):
            lib_path = "./libctrl-sc.so";
            lib_handle = &_CTRL_libsc_handle;
            break;
        case (CTRL_TV):
            lib_path = "./libctrl-tv.so";
            lib_handle = &_CTRL_libtv_handle;
            break;
        case (CTRL_ALL):
            lib_path = "./libctrl-all.so";
            lib_handle = &_CTRL_liball_handle;
            break;
        default:
            printf("Error loading dynamic library - unknown CTRL_MODE: %d\n", _CTRL_curr_mode);
            printf("Warning: reverting to CTRL_NONE mode as a failsafe.\n");
            lib_path = "./libctrl-no.so";
            lib_handle = &_CTRL_libno_handle;
            break;
    }
    
    /* Attempt to load the dynamic library */
    (*lib_handle) = dlopen(lib_path, RTLD_NOW);

    if (*lib_handle)
        printf("Successfully switched control mode\n");
    else
        printf("Error loading dynamic library: %s\n", dlerror());
}

/**
 * @brief Load the function pointers to the init and step methods of the currently in-use model
 */
void _load_lib_syms() {
    switch (_CTRL_curr_mode) {
        case (CTRL_NONE):
            _CTRL_model_no_init_fn = dlsym(_CTRL_libno_handle, "No_initialize");
            _CTRL_model_no_step_fn = dlsym(_CTRL_libno_handle, "No_step");
            break;
        case (CTRL_SC):
            _CTRL_model_sc_init_fn = dlsym(_CTRL_libsc_handle, "Slip_initialize");
            _CTRL_model_sc_step_fn = dlsym(_CTRL_libsc_handle, "Slip_step");
            break;
        case (CTRL_TV):
            _CTRL_model_tv_init_fn = dlsym(_CTRL_libtv_handle, "Torque_initialize");
            _CTRL_model_tv_step_fn = dlsym(_CTRL_libtv_handle, "Torque_step");
            break;
        case (CTRL_ALL):
            _CTRL_model_all_init_fn = dlsym(_CTRL_liball_handle, "All0_initialize");
            _CTRL_model_all_step_fn = dlsym(_CTRL_liball_handle, "All0_step");       
            break;
        default:
            printf("Error loading dynamic library symbols - unknown CTRL_MODE: %d\n", _CTRL_curr_mode);
            break;
    }

    if (dlerror())
        printf("Error: %s\n", dlerror());
}