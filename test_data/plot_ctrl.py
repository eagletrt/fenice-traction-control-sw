import matplotlib.pyplot as plt


def read_files(f_exp, f_act):
    expected = {
        't_rl': [],
        't_rr': []
    }

    actual = {
        't_rl': [],
        't_rr': []
    }

    for line in open(f_exp).readlines():
        r, l = map(float, line.strip().split(','))
        expected['t_rr'].append(r)
        expected['t_rl'].append(l)

    for line in open(f_act).readlines():
        r, l = map(float, line.strip().split(','))
        actual['t_rr'].append(r)
        actual['t_rl'].append(l)

    return expected, actual


def plot(expected, actual, t=None):
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
    '''
    e, a = read_files('slip/output.csv', 'slip/test_output.csv')
    plot(e, a)
    e, a = read_files('torque/output.csv', 'torque/test_output.csv')
    plot(e, a)
    e, a = read_files('all/output.csv', 'all/test_output.csv')
    plot(e, a)
    '''
    e, a = read_files('test_data/slip_4/control_output_m3c20.csv', 'test_data/slip_4/control_output_m3c20_test.csv')
    plot(e, a, "m3c20")
    e, a = read_files('test_data/slip_4/control_output_m3c21.csv', 'test_data/slip_4/control_output_m3c21_test.csv')
    plot(e, a, "m3c21")
    e, a = read_files('test_data/slip_4/control_output_m3c22.csv', 'test_data/slip_4/control_output_m3c22_test.csv')
    plot(e, a, "m3c22")
    e, a = read_files('test_data/slip_4/control_output_m3c23.csv', 'test_data/slip_4/control_output_m3c23_test.csv')
    plot(e, a, "m3c23")