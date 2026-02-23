# Метод пристрелки

import math
import numpy as np
import matplotlib.pyplot as plt

class YP:
    def __init__(self, y=0.0, p=0.0):
        self.y = y
        self.p = p


def dydx(v):
    return v


def dvdx(x, v):
    return math.exp(x * x) * v + x


def dpdx(u):
    return u


def dudx(x, u):
    return math.exp(x * x) * u


def MRK(x0, y0, v0, x_end, h):
    n = int((x_end - x0) / h)

    k1 = [0.0, 0.0]
    k2 = [0.0, 0.0]
    k3 = [0.0, 0.0]
    k4 = [0.0, 0.0]
    k11 = [0.0, 0.0]
    k22 = [0.0, 0.0]
    k33 = [0.0, 0.0]
    k44 = [0.0, 0.0]

    y = y0
    v = v0
    p = 0.0
    u = 1.0

    for i in range(1, n + 1):
        # Основная система: y, v
        k1[0] = dydx(v)
        k1[1] = dvdx(x0, v)

        k2[0] = dydx(v + 0.5 * h * k1[1])
        k2[1] = dvdx(x0 + 0.5 * h, v + 0.5 * h * k1[1])

        k3[0] = dydx(v + 0.5 * h * k2[1])
        k3[1] = dvdx(x0 + 0.5 * h, v + 0.5 * h * k2[1])

        k4[0] = dydx(v + h * k3[1])
        k4[1] = dvdx(x0 + h, v + h * k3[1])

        y += h * (1.0 / 6.0) * (k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0])
        v += h * (1.0 / 6.0) * (k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1])

        # Вариационная система: p, u
        k11[0] = dpdx(u)
        k11[1] = dudx(x0, u)

        k22[0] = dpdx(u + 0.5 * h * k11[1])
        k22[1] = dudx(x0 + 0.5 * h, u + 0.5 * h * k11[1])

        k33[0] = dpdx(u + 0.5 * h * k22[1])
        k33[1] = dudx(x0 + 0.5 * h, u + 0.5 * h * k22[1])

        k44[0] = dpdx(u + h * k33[1])
        k44[1] = dudx(x0 + h, u + h * k33[1])

        p += h * (1.0 / 6.0) * (k11[0] + 2.0 * k22[0] + 2.0 * k33[0] + k44[0])
        u += h * (1.0 / 6.0) * (k11[1] + 2.0 * k22[1] + 2.0 * k33[1] + k44[1])

        x0 += h

    return YP(y, p)

x_end = 1.0
y_0 = 0.0
x_0 = 0.0
h = 0.001
y_1 = 2.0

v_0 = 0.0
yp = MRK(x_0, y_0, v_0, x_end, h)


while abs(yp.y - y_1) > 0.001:
    v_0 -= (yp.y - y_1) / yp.p
    yp = MRK(x_0, y_0, v_0, x_end, h)

try:
    print("Введите значение из отрезка [0,1]: ")
    x_chosen = float(input())
    if 0.0 <= x_chosen <= 1.0:
        result = MRK(x_0, y_0, v_0, x_chosen, h)
        print(f"y({x_chosen}) = {result.y}")
    else:
        print("Error: x should be from zero to one.")
except ValueError:
    print("Error: Please enter a valid number.")

x = np.linspace(0, 1, 1000)
y = [MRK(x_0, y_0, v_0, x[i], h).y for i in range(len(x))]
plt.plot(x, y)
plt.show()