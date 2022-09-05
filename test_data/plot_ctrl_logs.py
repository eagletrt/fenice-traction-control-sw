import sys
import matplotlib.pyplot as plt

frames = open(sys.argv[1]).readlines()[1:]
frames = [l.strip().split(',') for l in frames]
id_to_label = ['dreq', 'steer', 'mode', 'yaw', 'omega_rr', 'omega_rl', 'omega_fr', 'omega_fl', 'ax_g', 'brake', 'tm_rr', 'tm_rl']
t_0 = int(frames[0][0])

params = {}
for f in frames:
    t = (int(f[0]) - t_0) / 1000
    p_id = int(f[1])
    p_val = float(f[2])
    p_name = id_to_label[p_id]

    if p_name not in params:
        params[p_name] = {'x': [], 'y': []}
    params[p_name]['x'].append(t)
    params[p_name]['y'].append(p_val)


if False:
    ''' Plot all params '''
    fig, axs = plt.subplots(len(params.keys()), sharex=True)

    for i, (p_name, data) in enumerate(params.items()):
        axs[i].plot(data['x'], data['y'], label=p_name)
        axs[i].legend()
        axs[i].grid()
            
    plt.xlabel('Time (ms)')
    plt.show()
else:
    fig, axs = plt.subplots(2, sharex=True)

    def plot_param(ax, p_name, col):
        tmp = params[p_name]
        return ax.plot(tmp['x'], tmp['y'], color=col, label=p_name, linewidth=1)

    def add_legend(ax, handles):
        ax.legend(handles, [l.get_label() for l in handles])


    y2 = axs[0].twinx()
    h1 = plot_param(axs[0], 'tm_rr', 'forestgreen')
    h2 = plot_param(axs[0], 'tm_rl', 'limegreen')
    h3 = plot_param(y2, 'dreq', 'cornflowerblue')
    add_legend(axs[0], h1+h2+h3)
    axs[0].set_ylabel('Torque [Nm]')
    y2.set_ylabel('[#]')

    y2 = axs[1].twinx()
    h1 = plot_param(axs[1], 'steer', 'orange')
    h2 = plot_param(y2, 'yaw', 'purple')
    add_legend(axs[1], h1+h2)
    axs[1].set_ylabel('Sex. Degrees [$^\circ$]')
    y2.set_ylabel('DPS [$^\circ$/s]')

    fig.tight_layout()
    plt.tight_layout()
    plt.show()



# plt.plot(params[4]['x'], params[4]['y'], label='Omega RR')
# plt.plot(params[5]['x'], list(-x for x in params[5]['y']), label='Omega RL')
# plt.plot(params[6]['x'], params[6]['y'], label='Omega FR')
# plt.plot(params[7]['x'], params[7]['y'], label='Omega FL')
