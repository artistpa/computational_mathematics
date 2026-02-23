import numpy as np
import math
import scipy.optimize as opt

def u(t):
    return np.exp(t)
def sum(t, n):
    S = 0
    for i in range(n):
        S += u(0) * (t ** n) / math.factorial(n)
    return S

def Δt_exp(n, x1, x2):
    max_x = opt.fminbound(lambda x: -u(x), x1, x2)
    return u(max_x) * (x2 ** (n + 1)) / math.factorial(n+1)

def Δt_sin(n, x1, x2):
    max_x = opt.fminbound(lambda x: -u(x), x1, x2)
    return  (x2 ** (n + 1)) / math.factorial(n+1)

n = 0
a = Δt_exp(n, 0, 1)
while (a > 0.001):
    n += 1
    a = Δt_exp(n, 0, 1)

print("exp(x) на отрезке [0,1]:", n)
print("Погрешность:", a)

n = 0
a = Δt_exp(n, 10, 11)
while (a > 0.001):
    n += 1
    a = Δt_exp(n, 10, 11)

print("exp(x) на отрезке [10,11]:", n)
print("Погрешность:", a)

n = 0
a = Δt_sin(n, 0, 1)
while (a > 0.001):
    n += 1
    a = Δt_sin(n, 0, 1)

print("sin(x) на отрезке [0,1]:", n)
print("Погрешность:", a)

n = 0
a = Δt_sin(n, 10, 11)
while (a > 0.001):
    n += 1
    a = Δt_sin(n, 10, 11)

print("sin(x) на отрезке [10,11]:", n)
print("Погрешность:", a)

# Optimization (t = x + 10)

def u(t):
    return np.exp(t)

def Δt_exp(n):
    max_x = opt.fminbound(lambda x: -u(x), 0, 1)
    return u(10) * u(max_x) * (1 ** (n + 1)) / math.factorial(n+1)

def Δt_sin(n):
    return abs((np.sin(10) + np.cos(10)) * (1 ** (n + 1)) / math.factorial(n+1))

n = 0
a = Δt_exp(n)
while (a > 0.001):
    n += 1
    a = Δt_exp(n)

print("exp(x) на отрезке [10,11] (улучшенный алгоритм):", n)
print("Погрешность:", a)

n = 0
a = Δt_sin(n)
while (a > 0.001):
    n += 1
    a = Δt_sin(n)

print("sin(x) на отрезке [10,11] (улучшенный алгоритм):", n)
print("Погрешность:", a)
