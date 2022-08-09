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

    if p_id not in [0, 1, 9, 10, 11]:
        continue

    if p_id not in params:
        params[p_id] = {'x': [], 'y': []}
    params[p_id]['x'].append(t)
    params[p_id]['y'].append(p_val)

fig, axs = plt.subplots(len(params.keys()), sharex=True)

for i, (p_id, data) in enumerate(params.items()):
    axs[i].plot(data['x'], data['y'], label=id_to_label[p_id])
    axs[i].legend()
    axs[i].grid()

plt.xlabel('Time (ms)')
plt.show()