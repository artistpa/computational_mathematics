import numpy as np

def f(x):
    return x * np.exp(-(x ** 2))

x_max = 0.5 ** (0.5) # x > 0
f_max = f(x_max)

def f1(x):
    return x * np.exp(-(x ** 2)) - f_max/2

def f1_diff(x):
    return (1 - 2 * (x ** 2)) * np.exp(-(x ** 2))

# Первый корень на [0,x_max]
#print(f1(1))
#print(f1(2))
# Второй корень на [1, 2]

# Ищем первый корень
# x = f_max * e^(x^2) / 2 = phi1(x)
#print(f_max * x_max * np.exp(x_max ** 2)) # < 1

def phi1(x):
    return f_max * np.exp((x**2)) / 2

i = 0.4
i = phi1(i)
while (f1(i) / f1_diff(i) > 0.001):
    i = phi1(i)
print(i)

#Ищем второй корень
# x = (-ln(f_max / (2x))) ** 0.5 = phi2(x)
#print(1 / (2 * 1 * (-np.log(f_max / 2 / 1))**0.5)) # < 1

def phi2(x):
    return (-np.log(f_max / (2 * x))) ** 0.5

j = 1.5
j = phi2(j)
while (f1(j) / f1_diff(j) > 0.001):
    j = phi2(j)
print(j)

print("Ширина функции на полувысоте =", j - i)


