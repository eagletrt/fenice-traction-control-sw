#include <dlfcn.h>
#include <stdio.h>
#include "models_interface.h"


void *libsc_handle  = NULL;
void *libtv_handle  = NULL;
void *liball_handle = NULL;
void *libno_handle  = NULL;


void _unload_all_libs();


/**
 * @brief Change the traction control model being used by loading the appropriate dynamic library
 */
void change_ctrl_mode(CTRL_MODE new_mode) {
    char *lib_path;     /* Filesystem path of the DL to load */
    void **lib_handle;  /* Pointer to the variable that will contaian the DL handle */

    /* Ensure all other libs are unloaded to avoid namespace conflicts */
    _unload_all_libs();

    switch (new_mode) {
        case (CTRL_NONE):
            lib_path = "./libctrl-no.so";
            lib_handle = &libno_handle;
            break;
        case (CTRL_SC):
            lib_path = "./libctrl-sc.so";
            lib_handle = &libsc_handle;
            break;
        case (CTRL_TV):
            lib_path = "./libctrl-tv.so";
            lib_handle = &libtv_handle;
            break;
        case (CTRL_ALL):
            lib_path = "./libctrl-all.so";
            lib_handle = &liball_handle;
            break;
        default:
            printf("Error loading dynamic library - unknown CTRL_MODE: %d\n", new_mode);
            printf("Warning: reverting to CTRL_NONE mode as a failsafe.\n");
            lib_path = "./libctrl-no.so";
            lib_handle = &libno_handle;
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
 * @brief Make sure that all dynamic libraries are unloaded (e.g., before loading a new one)
 */
void _unload_all_libs() {
    if (libsc_handle)
        dlclose(libsc_handle);
    if (libtv_handle)
        dlclose(libtv_handle);
    if (liball_handle)
        dlclose(liball_handle);
    if (libno_handle)
        dlclose(libno_handle);
}