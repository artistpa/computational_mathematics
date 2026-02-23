#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<double> solve_finite_difference(int N = 1000) {
    double h = 10.0 / (N + 1);
    vector<double> x(N+2), y(N+2);

    for (int i = 0; i <= N+1; i++) {
        x[i] = i * h;
    }

    y[0] = 0.0;
    y[N+1] = 1.0;

    vector<double> a(N), b(N), c(N), d(N);

    for (int i = 1; i <= N; i++) {
        double xi = x[i];
        a[i-1] = 1.0/(h*h);                    // коэффициент при y_{i-1}
        b[i-1] = -2.0/(h*h) - (10.0 + xi*xi);  // коэффициент при y_i
        c[i-1] = 1.0/(h*h);                    // коэффициент при y_{i+1}
        d[i-1] = xi * exp(-xi);                // правая часть
    }

    d[0] -= a[0] * y[0];
    d[N-1] -= c[N-1] * y[N+1];

    vector<double> alpha(N), beta(N);

    alpha[0] = -c[0] / b[0];
    beta[0] = d[0] / b[0];

    for (int i = 1; i < N; i++) {
        double denom = b[i] + a[i] * alpha[i-1];
        alpha[i] = -c[i] / denom;
        beta[i] = (d[i] - a[i] * beta[i-1]) / denom;
    }

    y[N] = beta[N-1];
    for (int i = N-1; i >= 1; i--) {
        y[i] = alpha[i-1] * y[i+1] + beta[i-1];
    }

    return y;
}

int main() {
    int N = 1000;
    auto y = solve_finite_difference(N);

    double h = 10.0 / (N + 1);

    vector<double> points = {0.0, 3.0, 5.0, 8.0, 10.0};
    for (double x_point : points) {
        int idx = (int)(x_point / h + 0.5);
        if (idx >= 0 && idx <= N+1) {
            cout << "y(" << x_point << ") = " << y[idx] << endl;
        }
    }

    return 0;
}
