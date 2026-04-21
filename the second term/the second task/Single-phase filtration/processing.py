import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation

x = []
p = []

with open('x.txt', 'r') as f:
    for line in f:
        x.append(float(line.strip()))
with open('p.txt', 'r') as f:
    for line in f:
        p.append(float(line.strip()))

p = np.array(p)
p = p.reshape(int(len(p) / 101), 101)
print(len(p))

fig, ax = plt.subplots()
artists = []
for i in range(len(p)):
    container = ax.plot(x, p[i], color="tab:blue")
    ax.set(xlabel='x, м', ylabel='p, атм')
    ax.set_title("Изменение распределения давления в пласте с шагом по времени 2.4 часа")
    ax.grid(True, which="major", axis="both", linestyle="--", color="gray", linewidth=0.5, alpha=0.7)
    artists.append(container)

ani = animation.ArtistAnimation(fig=fig, artists=artists, interval=1000)
writer = animation.PillowWriter(fps=1, metadata=dict(artist='Me'), bitrate=1800)
ani.save('p_x.gif', writer=writer)
plt.show()
