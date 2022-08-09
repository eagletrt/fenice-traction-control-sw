#ifndef MODELS_INTERFACE_H
#define MODELS_INTERFACE_H

#include "ctrl-nwk-utils.h"


typedef struct {
    double dreq;
    double delta;
    double tmax_rl;
    double tmax_rr;
    double omega_rl;
    double omega_rr;
    double map_tv;
    double map_sc;
    double brake;
    double bar;
    double omega;
} CTRL_ModelInputTypeDef;

typedef struct {
    double tm_rl;
    double tm_rr;
} CTRL_ModelOutputTypeDef;


void CTRL_change_mode(CTRL_ModeTypeDef new_mode);
void CTRL_step_model(CTRL_ModelInputTypeDef *data_in, CTRL_ModelOutputTypeDef *data_out);

#endif