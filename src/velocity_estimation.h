#ifndef VEL_EST_H
#define VEL_EST_H

#include "stdbool.h"


/* Path of the dynamic library */
#define VES_LIB_PATH "./libctrl-ve.so"


typedef struct {
    double omega_fl;
    double omega_fr;
    double omega_rl;
    double omega_rr;
    double ax_g;
    double torque_map;
} VES_DataInTypeDef;

typedef struct {
    double bar;
    double tmax_rr;
    double tmax_rl;
} VES_DataOutTypeDef;


bool VES_init();
void VES_step_model(VES_DataInTypeDef*, VES_DataOutTypeDef*);

#endif