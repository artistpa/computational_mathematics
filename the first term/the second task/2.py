import numpy as np
import matplotlib.pyplot as plt


def ddt(t, state, a):
    y, z = state
    dydt = z
    dzdt = -a * (y ** 2 - 1) * z - y
    return np.array([dydt, dzdt])


def MRK(f, t, y, h, a):
    k1 = h * f(t, y, a)
    k2 = h * f(t + h / 5, y + k1 / 5, a)
    k3 = h * f(t + 3 * h / 10, y + 3 * k1 / 40 + 9 * k2 / 40, a)
    k4 = h * f(t + 4 * h / 5, y + 44 * k1 / 45 - 56 * k2 / 15 + 32 * k3 / 9, a)
    k5 = h * f(t + 8 * h / 9, y + 19372 * k1 / 6561 - 25360 * k2 / 2187 + 64448 * k3 / 6561 - 212 * k4 / 729, a)
    k6 = h * f(t + h, y + 9017 * k1 / 3168 - 355 * k2 / 33 + 46732 * k3 / 5247 + 49 * k4 / 176 - 5103 * k5 / 18656, a)

    y5 = y + 35 * k1 / 384 + 500 * k3 / 1113 + 125 * k4 / 192 - 2187 * k5 / 6784 + 11 * k6 / 84
    k7 = h * f(t + h, y5, a)
    y4 = y + 5179 * k1 / 57600 + 7571 * k3 / 16695 + 393 * k4 / 640 - 92097 * k5 / 339200 + 187 * k6 / 2100 + k7 / 40

    error = np.linalg.norm(y5 - y4)
    return y5, error


def solve(a_values, t_span=(0, 50), y0=[2, 0], tol=1e-8, h_min=1e-6, h_max=0.1):
    fig, axes = plt.subplots(1, 2, figsize=(12, 10))

    for idx, a in enumerate(a_values):
        t = t_span[0]
        y = np.array(y0, dtype=float)
        h = 0.01

        t_values = [t]
        y_values = [y[0]]
        z_values = [y[1]]

        while t < t_span[1]:
            if t + h > t_span[1]:
                h = t_span[1] - t

            y_new, error = MRK(ddt, t, y, h, a)

            if error <= tol:
                t += h
                y = y_new
                t_values.append(t)
                y_values.append(y[0])
                z_values.append(y[1])

                if error < tol / 10:
                    h = min(h * 1.5, h_max)
            else:
                h = max(h * 0.5, h_min)

        t_values = np.array(t_values)
        y_values = np.array(y_values)
        z_values = np.array(z_values)

        ax2 = axes[idx]
        ax2.plot(t_values, y_values, 'r-', linewidth=1.5)
        ax2.set_xlabel('Время t')
        ax2.set_ylabel('y(t)')
        ax2.set_title(f'Решение y(t) (a = {a})')
        ax2.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.show()


def main():
    a_values = [0.02, 99]
    solve(a_values)


if __name__ == "__main__":
    main()
