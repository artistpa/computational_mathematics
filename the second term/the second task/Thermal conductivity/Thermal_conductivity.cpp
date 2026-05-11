#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double phi_t_0(double x, double y){
    return cos(M_PI * x) * sin(5 * M_PI * y);
}

double phi_y_0(double x, double t){
    return 0;
}

double phi_y_1(double x, double t){
    return 0;
}

double phi_x_0(double t, double y){
    return sin(5 * M_PI * y) * exp(-50 * pow(M_PI, 2) * pow(10, -4) * t);
}

double phi_x_1(double t, double y){
    return -sin(5 * M_PI * y) * exp(-50 * pow(M_PI, 2) * pow(10, -4) * t);
}

double phi_analytical(double t, double x, double y){
    return cos(M_PI * x) * sin(5 * M_PI * y) * exp(-50 * pow(M_PI, 2) * pow(10, -4) * t);
}

int main(){
    int N[7];
    double lambda = pow(10, -4), tau = 0.01, T_max = 1.0, t = 0.0, L = 1.0, h, sigma_x, sigma_y, delta_q[7];
    vector<double> x(1001), y(1001), a(1001), b(1001), c(1001), d(1001), p(1001), q(1001);
    vector<vector<double>> phi(1001, vector<double>(1001));

    N[0] = 10;
    N[1] = 20;
    N[2] = 50;
    N[3] = 100;
    N[4] = 200;
    N[5] = 500;
    N[6] = 1000;

    for (int s = 0; s < 7; s++){

        h = L / N[s];
        sigma_x = 25 * lambda * tau / pow(h, 2);
        sigma_y = lambda * tau / pow(h, 2);
        t = 0.0;

        for (int i = 0; i <= N[s]; i++){
            x[i] = i * h;
            y[i] = i * h;
        }

        for (int i = 0; i <= N[s]; i++){
            for (int j = 0; j <= N[s]; j++){
                phi[i][j] = phi_t_0(x[i], y[j]);
            }
        }

        while (t < T_max){
            for (int i = 0; i <= N[s]; i++){
                phi[i][0] = phi_y_0(x[i], t + tau);
                phi[i][N[s]] = phi_y_1(x[i], t + tau);
                phi[0][i] = phi_x_0(t + tau, y[i]);
                phi[N[s]][i] = phi_x_1(t + tau, y[i]);
            }
            for (int j = 1; j <= N[s]; j++){
                a[0] = 1.0;
                b[0] = 0.0;
                a[N[s]] = 1.0;
                c[N[s]] = 0.0;
                d[0] = phi_x_0(t + tau, y[j]);
                d[N[s]] = phi_x_1(t + tau, y[j]);
                p[1] = 0.0;
                q[1] = d[0] / a[0];
                for (int i = 1; i < N[s]; i++){
                    a[i] = 1 + 2 * (sigma_x + sigma_y);
                    b[i] = -sigma_x;
                    c[i] = -sigma_x;
                    d[i] = phi[i][j] + sigma_y * (phi[i][j-1] + phi[i][j+1]);
                    p[i+1] = - b[i] / (c[i] * p[i] + a[i]);
                    q[i+1] = (d[i] - c[i] * q[i]) / (c[i] * p[i] + a[i]);
                }
                phi[N[s]][j] = (d[N[s]] - c[N[s]] * q[N[s]]) / (p[N[s]] * c[N[s]] + a[N[s]]);
                for (int i = N[s] - 1; i >= 0; i--){
                    phi[i][j] = p[i+1] * phi[i+1][j] + q[i+1];
                }
            }
            t += tau;
        }
        delta_q[s] = 0.0;
        for (int i = 0; i <= N[s]; i++){
            for (int j = 0; j <= N[s]; j++){
                 if (abs(phi[i][j] - phi_analytical(t, x[i], y[j])) > delta_q[s])
                    delta_q[s] = abs(phi[i][j] - phi_analytical(t, x[i], y[j]));
            }
        }
        cout << delta_q[s] << endl;
    }
}
