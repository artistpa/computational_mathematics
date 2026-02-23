# Метод Ньютона
import numpy as np
import matplotlib.pyplot as plt

# Данные
x_a = [0, 1, 2, 3, 4, 5]
y_a = [0, 0.367879, 0.270671, 0.149361, 0.073263, 0.03369]


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

# Вычисляем f(0.5)
x_val = 0.5
f_05 = newton_polynomial(x_a, coef_a, x_val)


# Вывод результатов
print(f"Вычисленное значение (метод Ньютона) f(0.5) = {f_05}")

# Построение графика интерполяции (для проверки)
x_plot = np.linspace(0, 5, 100)
y_plot = [newton_polynomial(x_a, coef_a, xi) for xi in x_plot]

plt.plot(x_plot, y_plot, label="Интерполяционный полином Ньютона")
plt.scatter(x_a, y_a, color='red', label="Узлы интерполяции")
plt.legend()
plt.xlabel("x")
plt.ylabel("f(x)")
plt.title("Интерполяция Ньютона")
plt.grid()
plt.show()

