#ifndef MODELS_INTERFACE_H
#define MODELS_INTERFACE_H


typedef enum {
    CTRL_NONE,
    CTRL_SC,
    CTRL_TV,
    CTRL_ALL
} CTRL_MODE;

typedef struct {
    double rtU_Driver_req;
    double rtU_u_bar;
    double rtU_omega_rr;
    double rtU_omega_rl;
    double rtU_yaw_rate;
    double rtU_Steeringangle;
    double rtU_Brake;
} CTRL_ModelInputTypeDef;

typedef struct {
    double rtY_Tm_rr;
    double rtY_Tm_rl;
} CTRL_ModelOutputTypeDef;


void change_ctrl_mode(CTRL_MODE);
CTRL_ModelOutputTypeDef step_model(CTRL_ModelInputTypeDef);

#endif