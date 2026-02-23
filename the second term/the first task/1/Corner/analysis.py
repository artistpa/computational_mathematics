import matplotlib.pyplot as plt
import matplotlib.animation as animation

x = []
y1 = []
y2 = []
y3 = []
y4 = []
y5 = []

with open('x.txt', 'r') as f:
    for line in f:
        x.append(float(line.strip()))

with open('y_CFL_0_0_corner.txt', 'r') as f:
    for line in f:
        y1.append(float(line.strip()))

with open('y_CFL_0_5_corner.txt', 'r') as f:
    for line in f:
        y2.append(float(line.strip()))

with open('y_CFL_0_10_corner.txt', 'r') as f:
    for line in f:
        y3.append(float(line.strip()))

with open('y_CFL_0_15_corner.txt', 'r') as f:
    for line in f:
        y4.append(float(line.strip()))

with open('y_CFL_0_18_corner.txt', 'r') as f:
    for line in f:
        y5.append(float(line.strip()))


fig, ax = plt.subplots()
data = [y1, y2, y3, y4, y5]
artists = []
for i in range(5):
    container = ax.plot(x, data[i], color="tab:blue")
    ax.set(xlabel='x', ylabel='U(t,x)')
    ax.set_title("U(t,x)")
    artists.append(container)

ani = animation.ArtistAnimation(fig=fig, artists=artists, interval=1000)
plt.show()
