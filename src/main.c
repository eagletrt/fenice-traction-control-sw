#include <stdio.h>
#include "models_interface.h"


int main() {
    change_ctrl_mode(CTRL_NONE);
    change_ctrl_mode(CTRL_ALL);


    // Open UART
    // RX loop
    //   - If change model, unload DL + load DL
    //   - If param, record it (with timestamp?)
}