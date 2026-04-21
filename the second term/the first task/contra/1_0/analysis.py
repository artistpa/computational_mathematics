import matplotlib.pyplot as plt
import matplotlib.animation as animation

x = []
u0 = []
u1 = []
u2 = []
u3 = []
u4 = []
u5 = []
v0 = []
v1 = []
v2 = []
v3 = []
v4 = []
v5 = []

with open('x.txt', 'r') as f:
    for line in f:
        x.append(float(line.strip()))

with open('u_0_LW.txt', 'r') as f:
    for line in f:
        u0.append(float(line.strip()))

with open('u_2_LW.txt', 'r') as f:
    for line in f:
        u1.append(float(line.strip()))

with open('u_4_LW.txt', 'r') as f:
    for line in f:
        u2.append(float(line.strip()))

with open('u_6_LW.txt', 'r') as f:
    for line in f:
        u3.append(float(line.strip()))

with open('u_8_LW.txt', 'r') as f:
    for line in f:
        u4.append(float(line.strip()))

with open('u_10_LW.txt', 'r') as f:
    for line in f:
        u5.append(float(line.strip()))

with open('v_0_LW.txt', 'r') as f:
    for line in f:
        v0.append(float(line.strip()))

with open('v_2_LW.txt', 'r') as f:
    for line in f:
        v1.append(float(line.strip()))

with open('v_4_LW.txt', 'r') as f:
    for line in f:
        v2.append(float(line.strip()))

with open('v_6_LW.txt', 'r') as f:
    for line in f:
        v3.append(float(line.strip()))

with open('v_8_LW.txt', 'r') as f:
    for line in f:
        v4.append(float(line.strip()))

with open('v_10_LW.txt', 'r') as f:
    for line in f:
        v5.append(float(line.strip()))


fig, ax = plt.subplots()
data = [u0, u1, u2, u3, u4, u5]
artists = []
for i in range(6):
    container = ax.plot(x, data[i], color="tab:blue")
    ax.set(xlabel='x', ylabel='U(t,x)')
    ax.set_title("U(t,x)")
    artists.append(container)

ani = animation.ArtistAnimation(fig=fig, artists=artists, interval=1000)
writer = animation.PillowWriter(fps=1, metadata=dict(artist='Me'), bitrate=1800)
ani.save('U_f_g_1_0.gif', writer=writer)
plt.show()