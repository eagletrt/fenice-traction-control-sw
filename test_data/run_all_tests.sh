#!/bin/bash

DATASETS_DIR="fenice-vehicle-model/Simulation_output/Exported_csv"

if [ ! -d $DATASETS_DIR ]
then
    echo "Directory not found: $DATASETS_DIR"
    exit -1
fi

for f in $(ls $DATASETS_DIR/*_input.csv)
do
    base_name=${f%_*} # Drop substring from last occurrence of '_' to the end
    in_f="${base_name}_input.csv"
    out_f="${base_name}_output.csv"
    echo -e "\n######   Running test with input maneuver: ${base_name##*/}" # Drop substring from start of string up to last occurrence of '/'
    echo "    In: ${in_f##*/}"
    echo "    Out: ${out_f##*/}"
    python test_data/plot_ctrl.py $in_f $out_f
done
