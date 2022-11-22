#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "models_interface.h"
#include "velocity_estimation.h"
#include "logger.h"


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

    while (true) {
        int bytes_read = fscanf(
            in_f,
            "%lf,%lf,%lf,%lf,%lf,%lf",
            &(data_in.omega_fl),
            &(data_in.omega_fr),
            &(data_in.omega_rl),
            &(data_in.omega_rr),
            &(data_in.ax_g),
            &(data_in.torque_map)
        );

        if (bytes_read == 0)
            break;

        VES_step_model(&data_in, &data_out);

        fprintf(out_f, "%lf,%lf,%lf\n", data_out.bar, data_out.tmax_rr, data_out.tmax_rl);
    }
}

void test_ctrl(char* in_fname, char* out_fname, CTRL_ModeTypeDef ctrl_mode) {
    LOG_write(LOGLEVEL_INFO, "[CTRL] Reading input data from: %s", in_fname);
    LOG_write(LOGLEVEL_INFO, "[CTRL] Writing output data to: %s", out_fname);
    
    FILE *in_f = fopen(in_fname, "r");
    FILE *out_f = fopen(out_fname, "w");

    if (!in_f || !out_f) {
        printf("[CTRL] Error opening a file\n");
        return;
    }

    VES_DataInTypeDef vdata_in = { 0U };
    VES_DataOutTypeDef vdata_out = { 0U };
    CTRL_ModelInputTypeDef data_in = { 0U };
    CTRL_ModelOutputTypeDef data_out = { 0U };
    double ctrl_switch = 0.0f;
    int line_cnt = 0;

    VES_init();
    CTRL_change_mode(ctrl_mode);

    while (true) {
        int bytes_read = fscanf(
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

        if (bytes_read == 0)
            break;

        data_in.omega_rl = vdata_in.omega_rl;
        data_in.omega_rr = vdata_in.omega_rr;

        VES_step_model(&vdata_in, &vdata_out);
        data_in.bar = vdata_out.bar;
        data_in.tmax_rl = vdata_out.tmax_rl;
        data_in.tmax_rr = vdata_out.tmax_rr;

        CTRL_step_model(&data_in, &data_out);

        fprintf(out_f, "%lf,%lf\n", data_out.tm_rr, data_out.tm_rl);
    }

    LOG_write(LOGLEVEL_INFO, "[CTRL] Test ended");
}

void print_usage() {
    printf("Usage:\n");
    printf("    ./test-models <type> <data_in> <data_out>\n");
    printf("Where:\n");
    printf("    <type>     is one of vest|slip|torque|all|none\n");
    printf("    <data_in>  is the CSV file with input data\n");
    printf("    <data_out> is the CSV file where to write the output\n");
}

int main(int argc, char **argv) {
    LOG_init(LOGLEVEL_INFO, false, true, false);
    LOG_write(LOGLEVEL_INFO, "[MAIN] Initializing test suite");

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_usage();
        return 0;
    } else if (argc != 4) {
        LOG_write(LOGLEVEL_ERR, "[MAIN] Argument error. Usage is: ./test-models <type> <data_in> <data_out>");
        return -1;
    }

    if (strcmp(argv[1], "vest") == 0) {
        LOG_write(LOGLEVEL_INFO, "[MAIN] Starting model simulation with type: Velocity Estimation");
        test_velocity_estimation(argv[2], argv[3]);
    } else if (strcmp(argv[1], "slip") == 0) {
        LOG_write(LOGLEVEL_INFO, "[MAIN] Starting model simulation with type: Slip Control");
        test_ctrl(argv[2], argv[3], CTRL_Mode_Slip);
    } else if (strcmp(argv[1], "torque") == 0) {
        LOG_write(LOGLEVEL_INFO, "[MAIN] Starting model simulation with type: Torque Vectoring");
        test_ctrl(argv[2], argv[3], CTRL_Mode_Torque);
    } else if (strcmp(argv[1], "all") == 0) {
        LOG_write(LOGLEVEL_INFO, "[MAIN] Starting model simulation with type: Complete");
        test_ctrl(argv[2], argv[3], CTRL_Mode_Complete);
    } else if (strcmp(argv[1], "none") == 0) {
        LOG_write(LOGLEVEL_INFO, "[MAIN] Starting model simulation with type: No Controls");
        test_ctrl(argv[2], argv[3], CTRL_Mode_None);
    } else {
        LOG_write(LOGLEVEL_ERR, "[MAIN] Argument error: unknown test type in first argument");
        return -1;
    }

    return 0;
}

void _LOG_write_raw(char *txt) {
    printf("%s\n", txt);
}