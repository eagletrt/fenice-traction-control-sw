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


def plot(expected, actual):
    fig, axs = plt.subplots(2, 1, sharex=True)
    axs[0].plot(expected['t_rl'], label="Expected T_rl")
    axs[0].plot(actual['t_rr'], label="Actual T_rl")
    axs[0].grid()
    axs[0].legend()

    axs[1].plot(expected['t_rr'], label="Expected T_rr")
    axs[1].plot(actual['t_rr'], label="Actual T_rr")
    axs[1].grid()
    axs[1].legend()

    plt.show()


if __name__ == '__main__':
    e, a = read_files('slip/output.csv', 'slip/test_output.csv')
    plot(e, a)