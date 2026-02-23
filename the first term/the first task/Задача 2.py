# Метод трапеций и метод Симпсона
import numpy as np

def f(x):
    return np.sin(100 * x) * np.exp(-(x ** 2)) * np.cos(2 * x)

x = np.linspace(0, 3, 1000001)
h = x[1] - x[0]
y = f(x)
integral = 0
for i in range(0, len(x) - 1):
    integral += h * (y[i] + y[i+1]) / 2
print("Искомый интеграл равен (методом трапеций):", integral)

x = np.linspace(0, 3, 1000001)
h = x[2] - x[0]
y = f(x)
integral = 0
for i in range(0, len(x) - 1, 2):
    integral += h * (y[i] + 4 * y[i+1] + y[i+2]) / 6
print("Искомый интеграл равен (методом Симпсона):", integral)


