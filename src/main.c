#include <stdio.h>
#include "models_interface.h"

CTRL_ModelInputTypeDef model_input = {};
CTRL_ModelOutputTypeDef model_output = {};

int main() {

    change_ctrl_mode(CTRL_NONE);
    model_output = step_model(model_input);
    printf("Out L: %4.2f  -  Out R: %4.2f\n", model_output.rtY_Tm_rl, model_output.rtY_Tm_rr);

    // Open UART
    // RX loop
    //   - If change model, unload DL + load DL
    //   - If param, record it (with timestamp?)
}