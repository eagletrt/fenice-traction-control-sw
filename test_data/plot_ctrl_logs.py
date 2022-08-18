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

    if p_id not in [1, 4, 5, 6, 7]: # [0, 1, 9, 10, 11]:
        continue

    if p_id not in params:
        params[p_id] = {'x': [], 'y': []}
    params[p_id]['x'].append(t)
    params[p_id]['y'].append(p_val)

steer_roll_y = []
roll_win = [0]*20
for y in params[1]['y']:
    roll_win.insert(0, y)
    roll_win.pop()
    tmp = sorted(roll_win)[1:-1]
    steer_roll_y.append(sum(tmp)/len(tmp))

fig, axs = plt.subplots(len(params.keys()), sharex=True)

for i, (p_id, data) in enumerate(params.items()):
    axs[i].plot(data['x'], data['y'], label=id_to_label[p_id])
    if p_id == 1:
        axs[i].plot(data['x'], steer_roll_y, label="Steer w/ roll. avg.")
    axs[i].legend()
    axs[i].grid()


# plt.plot(params[4]['x'], params[4]['y'], label='Omega RR')
# plt.plot(params[5]['x'], list(-x for x in params[5]['y']), label='Omega RL')
# plt.plot(params[6]['x'], params[6]['y'], label='Omega FR')
# plt.plot(params[7]['x'], params[7]['y'], label='Omega FL')

plt.xlabel('Time (ms)')
plt.legend()
plt.show()