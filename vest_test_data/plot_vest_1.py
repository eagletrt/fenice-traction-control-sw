import matplotlib.pyplot as plt


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

for line in open('vel_output_prova2.csv').readlines():
    b, r, l = map(float, line.strip().split(','))
    expected['bar'].append(b)
    expected['tmax_rr'].append(r)
    expected['tmax_rl'].append(l)

for line in open('vel_test_output2.csv').readlines():
    b, r, l = map(float, line.strip().split(','))
    actual['bar'].append(b)
    actual['tmax_rr'].append(r)
    actual['tmax_rl'].append(l)


fig, axs = plt.subplots(3, 1)
axs[0].plot(expected['bar'], label="Expected uBar")
axs[0].plot(actual['bar'], label="Actual uBar")
axs[0].legend()

axs[1].plot(expected['tmax_rr'], label="Expected Tmax_rr")
axs[1].plot(actual['tmax_rr'], label="Actual Tmax_rr")
axs[1].legend()

axs[2].plot(expected['tmax_rl'], label="Expected Tmax_rl")
axs[2].plot(actual['tmax_rl'], label="Actual Tmax_rl")
axs[2].legend()

fig.suptitle("Velocity estimation test dataset #2")
plt.show()