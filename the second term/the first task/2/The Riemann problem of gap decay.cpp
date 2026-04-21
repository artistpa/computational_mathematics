#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main(){
    double L = 10.0, gamma = 5.0 / 3.0, ul_0 = 0.0, rol_0 = 13.0, pl_0 = 1000000.0, ur_0 = 0.0, ror_0 = 1.3, pr_0 = 100000.0, T = 0.015, CFL_max = 0.01, h, tau, x[101];
    double t = 0.0, w[101][3], v[101][3], omegaT[101][3][3], omegaT_inv[101][3][3], abs_lambda[101][3][3], A[101][3][3], c[101], max_lambda, CFL, otil[101][3][3], otilot[101][3][3], P[101];
    int NX = 101;

    ofstream f1("x.txt", ios::out);
    ofstream f2("ro.txt", ios::out);
    ofstream f3("u.txt", ios::out);
    ofstream f4("e.txt", ios::out);
    ofstream f5("p.txt", ios::out);

    h = 2.0 * L / (NX - 1);
    for (int i = 0; i < NX; i++){
        x[i] = -10.0 + i * h;
        w[i][1] = 0;
        v[i][1] = 0;
        if (x[i] <= 0) {
            w[i][0] = rol_0;
            w[i][2] = pl_0 / (gamma - 1.0);
            v[i][0] = rol_0;
            v[i][2] = pl_0 / ((gamma - 1.0) * rol_0);
        }
        else {
            w[i][0] = ror_0;
            w[i][2] = pr_0 / (gamma - 1.0);
            v[i][0] = ror_0;
            v[i][2] = pr_0 / ((gamma - 1.0) * ror_0);
        }
    }

    while (t < T) {
        tau = 0.0000001;
        max_lambda = 0.0;
        for (int i = 0; i < NX; i++){
            c[i] = sqrt(gamma * (gamma - 1.0) * w[i][2] / w[i][0]);

            omegaT[i][0][0] = - c[i] * v[i][1];
            omegaT[i][0][1] = c[i];
            omegaT[i][0][2] = gamma - 1.0;
            omegaT[i][1][0] = - c[i] * c[i];
            omegaT[i][1][1] = 0.0;
            omegaT[i][1][2] = gamma - 1.0;
            omegaT[i][2][0] = c[i] * v[i][1];
            omegaT[i][2][1] = - c[i];
            omegaT[i][2][2] = gamma - 1.0;

            omegaT_inv[i][0][0] = 1.0 / (2.0 * c[i] * c[i]);
            omegaT_inv[i][0][1] = - 1.0 / (c[i] * c[i]);
            omegaT_inv[i][0][2] = 1.0 / (2.0 * c[i] * c[i]);
            omegaT_inv[i][1][0] = (v[i][1] + c[i]) / (2.0 * c[i] * c[i]);
            omegaT_inv[i][1][1] = - v[i][1] / (c[i] * c[i]);
            omegaT_inv[i][1][2] = (v[i][1] - c[i]) / (2.0 * c[i] * c[i]);
            omegaT_inv[i][2][0] = 1.0 / (2.0 * (gamma - 1.0));
            omegaT_inv[i][2][1] = 0.0;
            omegaT_inv[i][2][2] = 1.0 / (2.0 * (gamma - 1.0));

            abs_lambda[i][0][0] = fabs(v[i][1] + c[i]);
            if (max_lambda < abs_lambda[i][0][0]){
                max_lambda = abs_lambda[i][0][0];
            }
            abs_lambda[i][0][1] = 0.0;
            abs_lambda[i][0][2] = 0.0;
            abs_lambda[i][1][0] = 0.0;
            abs_lambda[i][1][1] = fabs(v[i][1]);
            if (max_lambda < abs_lambda[i][1][1]){
                max_lambda = abs_lambda[i][1][1];
            }
            abs_lambda[i][1][2] = 0.0;
            abs_lambda[i][2][0] = 0.0;
            abs_lambda[i][2][1] = 0.0;
            abs_lambda[i][2][2] = fabs(v[i][1] - c[i]);
            if (max_lambda < abs_lambda[i][2][2]){
                max_lambda = abs_lambda[i][2][2];
            }

            A[i][0][0] = 0.0;
            A[i][0][1] = 1.0;
            A[i][0][2] = 0.0;
            A[i][1][0] = - v[i][1] * v[i][1];
            A[i][1][1] = 2.0 * v[i][1];
            A[i][1][2] = gamma - 1.0;
            A[i][2][0] = - gamma * v[i][1] * v[i][2];
            A[i][2][1] = gamma * v[i][2];
            A[i][2][2] = v[i][1];

            for (int j = 0; j < 3; j++){
                for (int k = 0; k < 3; k++){
                    otil[i][j][k] = omegaT_inv[i][j][k] * abs_lambda[i][k][k];
                }
            }

            for (int j = 0; j < 3; j++){
                for (int k = 0; k < 3; k++){
                    otilot[i][j][k] = 0;
                    for (int m = 0; m < 3; m++){
                        otilot[i][j][k] += otil[i][j][m] * omegaT[i][m][k];
                    }
                }
            }

        }


        CFL = tau * max_lambda / h;

        while (CFL > CFL_max) {
            tau /= 2.0;
            CFL = tau * max_lambda / h;
        }

        for (int i = 1; i < NX - 1; i++){
            for (int j = 0; j < 3; j++){
                w[i][j] = w[i][j] - tau * (A[i][j][0] * (w[i+1][0] - w[i-1][0]) + A[i][j][1] * (w[i+1][1] - w[i-1][1]) + A[i][j][2] * (w[i+1][2] - w[i-1][2])) / (2.0 * h) + tau * (otilot[i][j][0] * (w[i+1][0] - 2 * w[i][0] + w[i-1][0]) + otilot[i][j][1] * (w[i+1][1] - 2 * w[i][1] + w[i-1][1]) + otilot[i][j][2] * (w[i+1][2] - 2 * w[i][2] + w[i-1][2])) / (2.0 * h);
            }
            v[i][0] = w[i][0];
            v[i][1] = w[i][1] / w[i][0];
            v[i][2] = w[i][2] / w[i][0];
        }

        for (int j = 0; j < 3; j++){
            v[0][j] = v[1][j];
            v[NX-1][j] = v[NX-2][j];
        }

        for (int i = 0; i < NX; i++){
            P[i] = (gamma - 1.0) * v[i][0] * v[i][2];
        }

        t += tau;
        cout << t << endl;
    }

    for (int i = 0; i < NX; i++){
        f1 << x[i] << endl;
        f2 << v[i][0] << endl;
        f3 << v[i][1] << endl;
        f4 << v[i][2] << endl;
        f5 << P[i] << endl;
    }
}
