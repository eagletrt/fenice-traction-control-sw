#ifndef MODELS_INTERFACE_H
#define MODELS_INTERFACE_H


typedef enum {
    CTRL_NONE,
    CTRL_SC,
    CTRL_TV,
    CTRL_ALL
} CTRL_MODE;

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


void CTRL_change_mode(CTRL_MODE);
void CTRL_step_model(CTRL_ModelInputTypeDef*, CTRL_ModelOutputTypeDef*);

#endif