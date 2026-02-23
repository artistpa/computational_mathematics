import numpy as np

def f(x, y):
    return np.array([x * y - x ** 2 - 1.03, -2 * x**3 + y**2 - 1.98])
def f_m(x, y):
    return np.array([((y**2 - 1.98) / 2) ** (1/3), x + 1.03 / x])

u_0 = np.array([1, 2])
u = f_m(u_0[0], u_0[1])
delta = max(u - u_0)
i = 1
while (max(u - u_0) > ((delta) * 10**(-4))):
    u_0 = u
    u = f_m(u_0[0], u_0[1])
    i += 1
u_1 = u

print("Решение системы уравнений (x, y):")
print(*u_1)
print(i)