#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

double u_y_0(double x){
    return 0;
}

double u_y_1(double x){
    return 0;
}

double u_x_0(double y){
    return 0;
}

double u_x_1(double y){
    return 0;
}

double f(double x, double y){
    return 2 * sin(M_PI * x) * sin(M_PI * y);
}

int main(){
    int N;
    double L = 1.0, h;
    vector<double> x(1001), y(1001), a(1001), b(1001), c(1001), d(1001), p(1001), q(1001);
    vector<vector<double>> u(1001, vector<double>(1001));

    ofstream f1("x.txt", ios::out);
    ofstream f2("y.txt", ios::out);
    ofstream f3("u.txt", ios::out);

    N = 1000;
    h = L / N;

    for (int i = 0; i <= N; i++){
        x[i] = i * h;
        y[i] = i * h;
        f1 << x[i] << endl;
        f2 << y[i] << endl;
    }

    // Полинейный метод Гаусса-Зейделя

    for (int i = 0; i <= N; i++){
        u[i][0] = u_y_0(x[i]);
        u[i][N] = u_y_1(x[i]);
        u[0][i] = u_x_0(y[i]);
        u[N][i] = u_x_1(y[i]);
    }

    for (int j = 1; j <= N; j++){
        a[0] = 1.0;
        b[0] = 0.0;
        a[N] = 1.0;
        c[N] = 0.0;
        d[0] = u_x_0(y[j]);
        d[N] = u_x_1(y[j]);
        p[1] = 0.0;
        q[1] = d[0] / a[0];
        for (int i = 1; i < N; i++){
            a[i] = pow(h, 2) - 4.0;
            b[i] = 1.0;
            c[i] = 1.0;
            d[i] = pow(h, 2) * f(x[i], y[j]) - 1.0 * (u[i][j-1] + u[i][j+1]);
            p[i+1] = - b[i] / (c[i] * p[i] + a[i]);
            q[i+1] = (d[i] - c[i] * q[i]) / (c[i] * p[i] + a[i]);
        }
        u[N][j] = (d[N] - c[N] * q[N]) / (p[N] * c[N] + a[N]);
        for (int i = N - 1; i >= 0; i--){
            u[i][j] = p[i+1] * u[i+1][j] + q[i+1];
        }
    }
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= N; j++){
            f3 << u[i][j] << endl;
        }
    }
}
