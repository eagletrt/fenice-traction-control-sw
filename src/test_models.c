#include <stdlib.h>
#include <stdio.h>
#include "models_interface.h"
#include "velocity_estimation.h"


void test_velocity_estimation(char* in_fname, char* out_fname) {
    FILE *in_f = fopen(in_fname, "r");
    FILE *out_f = fopen(out_fname, "w");

    if (!in_f || !out_f) {
        printf("[vest] Error opening a file\n");
        return;
    }

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

void test_ctrl(char* in_fname, char* out_fname, CTRL_MODE ctrl_mode) {
    FILE *in_f = fopen(in_fname, "r");
    FILE *out_f = fopen(out_fname, "w");

    if (!in_f || !out_f) {
        printf("[ctrl] Error opening a file\n");
        return;
    }

    VES_DataInTypeDef vdata_in = { 0U };
    VES_DataOutTypeDef vdata_out = { 0U };
    CTRL_ModelInputTypeDef data_in = { 0U };
    CTRL_ModelOutputTypeDef data_out = { 0U };
    double ctrl_switch = 0.0f;

    CTRL_change_mode(ctrl_mode);

    while (!feof(in_f)) {
        fscanf(
            in_f,
            "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
            &(data_in.dreq),
            &(data_in.delta),
            &(ctrl_switch),
            &(vdata_in.omega_rl),
            &(vdata_in.omega_rr),
            &(vdata_in.omega_fr),
            &(vdata_in.omega_fl),
            &(vdata_in.ax_g),
            &(data_in.omega),
            &(vdata_in.torque_map),
            &(data_in.map_tv),
            &(data_in.map_sc),
            &(data_in.brake)
        );

        data_in.omega_rl = vdata_in.omega_rl;
        data_in.omega_rr = vdata_in.omega_rr;

        VES_step_model(&vdata_in, &vdata_out);
        data_in.bar = vdata_out.bar;
        data_in.tmax_rl = vdata_out.tmax_rl;
        data_in.tmax_rr = vdata_out.tmax_rr;

        CTRL_step_model(&data_in, &data_out);

        fprintf(out_f, "%lf,%lf\n", data_out.tm_rr, data_out.tm_rl);
    }
}


int main() {
    test_velocity_estimation("../test_data/vest/vel_input_prova2.csv", "../test_data/vest/vel_test_output2.csv");
    test_ctrl("../test_data/slip/input.csv", "../test_data/slip/test_output.csv", CTRL_SC);
    test_ctrl("../test_data/torque/input.csv", "../test_data/torque/test_output.csv", CTRL_TV);
    test_ctrl("../test_data/all/input.csv", "../test_data/all/test_output.csv", CTRL_ALL);
    return 1;
}