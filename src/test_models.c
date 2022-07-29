#include <stdlib.h>
#include <stdio.h>
#include "models_interface.h"
#include "velocity_estimation.h"


void test_velocity_estimation(char* in_fname, char* out_fname) {
    FILE *in_f = fopen(in_fname, "r");
    FILE *out_f = fopen(out_fname, "w");
    VES_DataInTypeDef data_in = { 0U };
    VES_DataOutTypeDef data_out = { 0U };

    VES_init();

    while (!feof(in_f)) {
        fscanf(
            in_f,
            "%lf,%lf,%lf,%lf,%lf,%lf",
            &(data_in.omega_fl),
            &(data_in.omega_fr),
            &(data_in.omega_rl),
            &(data_in.omega_rr),
            &(data_in.ax_g),
            &(data_in.torque_map)
        );

        VES_step_model(&data_in, &data_out);

        fprintf(out_f, "%lf,%lf,%lf\n", data_out.bar, data_out.tmax_rr, data_out.tmax_rl);
    }
}



int main() {
    test_velocity_estimation("../vest_test_data/vel_input_prova2.csv", "../vest_test_data/vel_test_output2.csv");
    return 1;
}