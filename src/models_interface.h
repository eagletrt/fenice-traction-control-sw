#ifndef MODELS_INTERFACE_H
#define MODELS_INTERFACE_H

typedef enum {
    CTRL_NONE,
    CTRL_SC,
    CTRL_TV,
    CTRL_ALL
} CTRL_MODE;


void change_ctrl_mode(CTRL_MODE);

#endif