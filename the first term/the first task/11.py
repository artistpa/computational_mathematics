import numpy as np

def f1(x, a):
    return x + 0.5 * np.sin(x) + a

def phi1(x, a):
    return -0.5 * np.sin(x) - a

def f1_diff(x):
    return 1 + 0.5 * np.cos(x)

i = 1000
a = -3
while (abs(f1(i, a) / f1_diff(i)) > 0.001):
    i = phi1(i, a)
print(i)



