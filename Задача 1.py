import numpy as np

def f(x, y):
    return np.array([x**2 + y**2 - 1, y - np.tan(x)])
def f_m(x, y):
    return np.array([x - (1/(2 * (x + y / (np.cos(x)**2)))) * (x**2 - y**2 - 1 + 2 * y * np.tan(x)), y - (1/(2 * (x + y / (np.cos(x)**2)))) * ((x**2 + y**2 - 1) / ((np.cos(x))**2) + 2 * y * x - 2 * x * np.tan(x))])

# Первый корень на [0.6, 0.8] * [0.6, 0.8]
# Второй корень на [-0.8, -0.6] * [-0.8, -0.6] (локализованы графически)

u_0 = np.array([0.7, 0.7])
u = f_m(u_0[0], u_0[1])
while (max(u - u_0) > 10 ** (-6)):
    u_0 = u
    u = f_m(u_0[0], u_0[1])
u_1 = u

u_0 = np.array([-0.7, -0.7])
u = f_m(u_0[0], u_0[1])
while (max(u - u_0) > 10 ** (-6)):
    u_0 = u
    u = f_m(u_0[0], u_0[1])
u_2 = u

print("Корни системы уравнений (x, y):")
print(*u_1)
print(*u_2)