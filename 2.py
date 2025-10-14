# Метод трапеций и метод Симпсона
import numpy as np

def f(x):
    return np.log(x) / ((1 - x) ** 0.5)

x = np.linspace(0.0000001, 0.5, 10000001)
h = x[1] - x[0]
y = f(x)
integral1 = 0
for i in range(0, len(x) - 1):
    integral1 += h * (y[i])

x = np.linspace(0.5, 0.9999, 10000001)
h = x[1] - x[0]
y = f(x)
integral2 = 0
for i in range(0, len(x) - 1):
    integral2 += h * (y[i])
print("Искомый интеграл равен (методом левых прямоугольников):", integral1 + integral2)

