import numpy as np
import math
import scipy.optimize as opt
import matplotlib.pyplot as plt

# Данные
x_a = [1910 + 10 * i for i in range(10)]
y_a = [92228496, 106021537, 123202624, 132164569, 151325798, 179323175, 203211926, 226545805, 248709873, 281421906]


# Функция для расчета разделенных разностей
def divided_differences(x, y):
    n = len(y)
    coef = np.copy(y).astype(float)

    for j in range(1, n):
        for i in range(n - 1, j - 1, -1):
            coef[i] = (coef[i] - coef[i - 1]) / (x[i] - x[i - j])

    return coef


# Функция для вычисления значения интерполяционного полинома в форме Ньютона
def newton_polynomial(x_data, coef, x):
    n = len(x_data)
    result = coef[-1]
    for i in range(n - 2, -1, -1):
        result = result * (x - x_data[i]) + coef[i]
    return result

# Вычисляем коэффициенты разделенных разностей
coef_a = divided_differences(x_a, y_a)

# Вычисляем f(5.25)
x_val = 2010
f_5_25 = newton_polynomial(x_a, coef_a, x_val)

# Табличное значение f(5.25)
true_value = 308745538
error = abs(true_value - f_5_25)

# Вывод результатов
print(f"Вычисленное значение f(2010) = {f_5_25}")
print(f"Табличное значение f(2010) = {true_value}")
print(f"Погрешность экстраполяции в данной точке = {error}")

# Построение графика интерполяции
x_plot = np.linspace(1900, 2010, 100)
y_plot = [newton_polynomial(x_a, coef_a, xi) for xi in x_plot]

plt.plot(x_plot, y_plot, label="Интерполяционный полином Ньютона")
plt.scatter(x_a, y_a, color='red', label="Узлы интерполяции")
plt.legend()
plt.xlabel("x")
plt.ylabel("f(x)")
plt.title("Интерполяция Ньютона")
plt.grid()
plt.show()