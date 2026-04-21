import matplotlib.pyplot as plt
import matplotlib.animation as animation

x = []
ro = []
u = []
e = []
p = []


with open('x.txt', 'r') as f:
    for line in f:
        x.append(float(line.strip()))

with open('ro.txt', 'r') as f:
    for line in f:
        ro.append(float(line.strip()))

with open('u.txt', 'r') as f:
    for line in f:
        u.append(float(line.strip()))

with open('e.txt', 'r') as f:
    for line in f:
        e.append(float(line.strip()))

with open('p.txt', 'r') as f:
    for line in f:
        p.append(float(line.strip()))


plt.plot(x, ro, 'r', label = "Плотность")


plt.xlabel('x, м')
plt.ylabel('ρ, кг/м³')
plt.title("Зависимость плотности газа от координаты")
plt.grid(which='major', color='gray', linestyle='-')
plt.grid(which='minor', color='gray', linestyle='--', linewidth=0.5)
plt.minorticks_on()
plt.tight_layout()
plt.legend()
plt.show()


plt.plot(x, u, 'r', label = "Скорость")


plt.xlabel('x, м')
plt.ylabel('u, м/с')
plt.title("Зависимость скорости газа от координаты")
plt.grid(which='major', color='gray', linestyle='-')
plt.grid(which='minor', color='gray', linestyle='--', linewidth=0.5)
plt.minorticks_on()
plt.tight_layout()
plt.legend()
plt.show()

plt.plot(x, e, 'r', label = "Удельная энергия")


plt.xlabel('x, м')
plt.ylabel('е, Дж/кг')
plt.title("Зависимость удельной энергии газа от координаты")
plt.grid(which='major', color='gray', linestyle='-')
plt.grid(which='minor', color='gray', linestyle='--', linewidth=0.5)
plt.minorticks_on()
plt.tight_layout()
plt.legend()
plt.show()

plt.plot(x, p, 'r', label = "Давление")


plt.xlabel('x, м')
plt.ylabel('p, Па')
plt.title("Зависимость давления газа от координаты")
plt.grid(which='major', color='gray', linestyle='-')
plt.grid(which='minor', color='gray', linestyle='--', linewidth=0.5)
plt.minorticks_on()
plt.tight_layout()
plt.legend()
plt.show()
