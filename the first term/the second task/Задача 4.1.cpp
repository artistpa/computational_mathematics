//Метод квазилинеаризации
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double y_0(double x){
    return x * log(x);
}

int main() {
    const double v0 = 0, vN = 0, h = 0.001, x0 = exp(1), xN = exp(2);
    double x[5000], y0[5000], dy0[5000], d2y0[5000], v[5000], y1[5000];
    int N;
    N = int((xN - x0) / h);

    for (int i = 0; i <= N; i++){
        x[i] = x0 + i * h;
    }

    for (int i = 0; i <= N; i++){
        y0[i] = y_0(x[i]);
        y1[i] = 0;
    }

    while (abs(y0[int(N/2)] - y1[int(N/2)]) > 0.000000001){
        dy0[0] = (y0[1] - y0[0]) / h;
        for (int i = 1; i < N; i++) {
            dy0[i] = (y0[i+1] - y0[i-1]) / (2.0 * h);
        }
        dy0[N] = (y0[N] - y0[N-1]) / h;

        d2y0[0] = (dy0[1] - dy0[0]) / h;
        for (int i = 1; i < N; i++) {
            d2y0[i] = (y0[i+1] - 2 * y0[i] + y0[i-1]) / (h * h);
        }
        d2y0[N] = (dy0[N] - dy0[N-1]) / h;

        v[0] = 0;
        v[N] = 0;

        double a[5000], b[5000], c[5000], d[5000];

        b[0] = 1;
        a[0] = 0;
        c[0] = 0;
        d[0] = 0;

        for (int i = 1; i < N; i++) {
            double xi = x[i];
            a[i] = 1 + h * exp(dy0[i]) * y0[i] / 2.0;
            b[i] = -2.0 + h * h * (exp(dy0[i]) - exp(1) * 2 * y0[i] / log(x[i]));
            c[i] = 1.0 - h * exp(dy0[i]) * y0[i] / 2.0;
            d[i] = h * h * (-d2y0[i] * d2y0[i] - y0[i] * exp(dy0[i]) + exp(1) * y0[i] * y0[i] / log(x[i]) + 1 / (x[i] * x[i]));
        }

        a[N] = 0;
        b[N] = 1;
        c[N] = 0;
        d[N] = 0;

        double p[5000], q[5000];

        p[0] = -a[0] / b[0];
        q[0] = d[0] / b[0];

        for (int i = 0; i < (N - 1); i++) {
            double denom = b[i+1] + c[i+1] * p[i];
            p[i+1] = -a[i+1] / denom;
            q[i+1] = (d[i+1] - c[i+1] * q[i]) / denom;
        }

        v[N] = (d[N] - c[N] * q[N-1]) / (b[N] + c[N] * p[N-1]);
        for (int i = N-1; i >= 0; i--) {
            v[i] = p[i] * v[i+1] + q[i];
        }

        for (int i = 0; i <= N; i++){
            y1[i] = y0[i];
            y0[i] += v[i];
        }
        }
    cout << "y(3.0) = " << y0[int((3.0 - x0) / h)] << endl;
    cout << "y(3.5) = " << y0[int((3.5 - x0) / h)] << endl;
    cout << "y(4.0) = " << y0[int((4.0 - x0) / h)] << endl;
    cout << "y(4.5) = " << y0[int((4.5 - x0) / h)] << endl;
    cout << "y(5.0) = " << y0[int((5.0 - x0) / h)] << endl;
}
