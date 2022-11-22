import os, sys, subprocess
import matplotlib.pyplot as plt


def read_ctrl_files(f_exp, f_act):
    expected = {
        't_rl': [],
        't_rr': []
    }

    actual = {
        't_rl': [],
        't_rr': []
    }

    for line in open(f_exp).readlines()[1:]:
        r, l = map(float, line.strip().split(',')) # Exp
        expected['t_rr'].append(r)
        expected['t_rl'].append(l)

    for line in open(f_act).readlines():
        r, l = map(float, line.strip().split(',')) # Act
        actual['t_rr'].append(r)
        actual['t_rl'].append(l)

    return expected, actual

def read_vest_files(f_exp, f_act):
    expected = {
        'bar': [],
        'tmax_rl': [],
        'tmax_rr': []
    }

    actual = {
        'bar': [],
        'tmax_rl': [],
        'tmax_rr': []
    }

    for line in open(f_exp).readlines()[1:]:
        b, r, l = map(float, line.strip().split(','))
        expected['bar'].append(b)
        expected['tmax_rr'].append(r)
        expected['tmax_rl'].append(l)

    for line in open(f_act).readlines():
        b, r, l = map(float, line.strip().split(','))
        actual['bar'].append(b)
        actual['tmax_rr'].append(r)
        actual['tmax_rl'].append(l)

    return expected, actual


def plot_vest(expected, actual):
    fig, axs = plt.subplots(3, 1)
    axs[0].plot(expected['bar'], label="Expected uBar")
    axs[0].plot(actual['bar'], label="Actual uBar")
    axs[0].grid()
    axs[0].legend()

    axs[1].plot(expected['tmax_rr'], label="Expected Tmax_rr")
    axs[1].plot(actual['tmax_rr'], label="Actual Tmax_rr")
    axs[1].grid()
    axs[1].legend()

    axs[2].plot(expected['tmax_rl'], label="Expected Tmax_rl")
    axs[2].plot(actual['tmax_rl'], label="Actual Tmax_rl")
    axs[2].grid()
    axs[2].legend()

    plt.show()


def plot_ctrl(expected, actual, t=None):
    fig, axs = plt.subplots(2, 1, sharex=True)
    axs[0].plot(expected['t_rl'], label="Expected T_rl", alpha=0.8)
    axs[0].plot(actual['t_rl'], label="Actual T_rl", alpha=0.8)
    axs[0].grid()
    axs[0].legend()

    axs[1].plot(expected['t_rr'], label="Expected T_rr", alpha=0.8)
    axs[1].plot(actual['t_rr'], label="Actual T_rr", alpha=0.8)
    axs[1].grid()
    axs[1].legend()

    if t is not None:
        fig.suptitle(t)

    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Arg error. Usage: plot.py <data_in> <exp_output>")
        exit(-1)
    
    data_in_fn = sys.argv[1]
    exp_out_fn = sys.argv[2]
    tmp_out_data = "/tmp/test-models-tmp-data.csv"

    maneuver, test_type, _ = data_in_fn.split('/')[-1].split('_')
    maneuver_id = int(maneuver[-1])
    maneuver_str = ['slip', 'torque', 'all', 'none'][maneuver_id-1] if test_type == 'control' else 'vest'

    cmd_str = "./test-models %s %s %s" % (maneuver_str, '../' + data_in_fn, tmp_out_data)
    subprocess.Popen(cmd_str.split(' '), cwd='build')
    
    if test_type == 'vel':
        exp, act = read_vest_files(exp_out_fn, tmp_out_data)
        plot_vest(exp, act)
    else:
        exp, act = read_ctrl_files(exp_out_fn, tmp_out_data)
        plot_ctrl(exp, act, maneuver)
