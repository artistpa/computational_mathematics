#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
    double CFL, h = 0.2, tau, T = 10.0, L = 2 * M_PI, u[100][50], v[100][50], z1[100][50], z2[100][50], x[100], f, g;
    int NX, NT;
    ofstream f1("x.txt", ios::out);
    ofstream f2("u_0_LW.txt", ios::out);
    ofstream f3("u_2_LW.txt", ios::out);
    ofstream f4("u_4_LW.txt", ios::out);
    ofstream f5("u_6_LW.txt", ios::out);
    ofstream f6("u_8_LW.txt", ios::out);
    ofstream f7("u_10_LW.txt", ios::out);
    ofstream f8("v_0_LW.txt", ios::out);
    ofstream f9("v_2_LW.txt", ios::out);
    ofstream f10("v_4_LW.txt", ios::out);
    ofstream f11("v_6_LW.txt", ios::out);
    ofstream f12("v_8_LW.txt", ios::out);
    ofstream f13("v_10_LW.txt", ios::out);
    CFL = 0.6;
    NX = int(1 + L / h);
    tau = CFL * h;
    f = 0.0;
    g = 0.0;
    NT = int(1 + T / tau);
    for (int m = 0; m < NX; m++) {
        x[m] = m * h;
        z1[0][m] = sin(x[m]) + cos(x[m]);
        z2[0][m] = sin(x[m]) - cos(x[m]);
        u[0][m] = sin(x[m]);
        v[0][m] = cos(x[m]);
    }
    for (int n = 0; n < NT - 1; n++){
        for (int m = 1; m < NX - 1; m++){
            z1[n+1][m] = z1[n][m] - CFL * (z1[n][m+1] - z1[n][m-1]) / 2.0 + pow(CFL, 2) * (z1[n][m-1] - 2 * z1[n][m] + z1[n][m+1]) / 2.0 + f + g;
            z2[n+1][m] = z2[n][m] + CFL * (z2[n][m+1] - z2[n][m-1]) / 2.0 + pow(CFL, 2) * (z2[n][m-1] - 2 * z2[n][m] + z2[n][m+1]) / 2.0 + f - g;
            u[n+1][m] = (z1[n+1][m] + z2[n+1][m]) / 2.0;
            v[n+1][m] = (z1[n+1][m] - z2[n+1][m]) / 2.0;
        }
        z1[n+1][0] = z1[n][0] - CFL * (z1[n][1] - z1[n][NX-2]) / 2.0 + pow(CFL, 2) * (z1[n][NX-2] - 2 * z1[n][0] + z1[n][1]) / 2.0;
        z1[n+1][NX-1] = z1[n+1][0];
        z2[n+1][0] = z2[n][0] + CFL * (z2[n][1] - z2[n][NX-2]) / 2.0 + pow(CFL, 2) * (z2[n][NX-2] - 2 * z2[n][0] + z2[n][1]) / 2.0;
        z2[n+1][NX-1] = z2[n+1][0];
        u[n+1][0] = (z1[n+1][0] + z2[n+1][0]) / 2.0;
        v[n+1][0] = (z1[n+1][0] - z2[n+1][0]) / 2.0;
        u[n+1][NX-1] = (z1[n+1][NX-1] + z2[n+1][NX-1]) / 2.0;
        v[n+1][NX-1] = (z1[n+1][NX-1] - z2[n+1][NX-1]) / 2.0;
//      y[n+1][NX-1] = y[n][NX-1] - CFL[i] * (y[n][0] - y[n][NX-2]) / 2.0 + pow(CFL[i], 2) * (y[n][NX-2] - 2 * y[n][NX-1] + y[n][0]) / 2.0;
    }
    for (int m = 0; m < NX; m++){
        f2 << u[0][m] << endl;
        f3 << u[int(2.0 / tau)][m] << endl;
        f4 << u[int(4.0 / tau)][m] << endl;
        f5 << u[int(6.0 / tau)][m] << endl;
        f6 << u[int(8.0 / tau)][m] << endl;
        f7 << u[int(10.0 / tau)][m] << endl;
        f8 << v[0][m] << endl;
        f9 << v[int(2.0 / tau)][m] << endl;
        f10 << v[int(4.0 / tau)][m] << endl;
        f11 << v[int(6.0 / tau)][m] << endl;
        f12 << v[int(8.0 / tau)][m] << endl;
        f13 << v[int(10.0 / tau)][m] << endl;
    }
    for (int m = 0; m < NX; m++){
        f1 << x[m] << endl;
    }
}
