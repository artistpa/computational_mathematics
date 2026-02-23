#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
    double CFL[3], h = 0.5, tau, T = 18.0, L = 20.0, y[100][100], x[100];
    int NX, NT;
    ofstream f1("x.txt", ios::out);
    ofstream f2("y_CFL_0_0_corner.txt", ios::out);
    ofstream f3("y_CFL_0_5_corner.txt", ios::out);
    ofstream f4("y_CFL_0_10_corner.txt", ios::out);
    ofstream f5("y_CFL_0_15_corner.txt", ios::out);
    ofstream f6("y_CFL_0_18_corner.txt", ios::out);
    ofstream f7("y_CFL_1_0_corner.txt", ios::out);
    ofstream f8("y_CFL_1_5_corner.txt", ios::out);
    ofstream f9("y_CFL_1_10_corner.txt", ios::out);
    ofstream f10("y_CFL_1_15_corner.txt", ios::out);
    ofstream f11("y_CFL_1_18_corner.txt", ios::out);
    ofstream f12("y_CFL_2_0_corner.txt", ios::out);
    ofstream f13("y_CFL_2_5_corner.txt", ios::out);
    ofstream f14("y_CFL_2_10_corner.txt", ios::out);
    ofstream f15("y_CFL_2_15_corner.txt", ios::out);
    ofstream f16("y_CFL_2_18_corner.txt", ios::out);
    CFL[0] = 0.6;
    CFL[1] = 1.0;
    CFL[2] = 1.01;
    NX = int(1 + L / h);
    for (int i = 0; i < 3; i++) {
        tau = CFL[i] * h;
        NT = int(1 + T / tau);
        for (int m = 0; m < NX; m++) {
            x[m] = m * h;
            y[0][m] = sin(4 * M_PI * x[m] / L);
        }
        for (int n = 1; n < NT; n++){
            for (int m = 1; m < NX; m++){
                y[n][m] = y[n-1][m] - CFL[i] * (y[n-1][m] - y[n-1][m-1]);
            }
            y[n][0] = y[n][NX-1];
        }
        for (int m = 0; m < NX; m++){
            if (i == 0) {
                f2 << y[0][m] << endl;
                f3 << y[int(5.0 / tau)][m] << endl;
                f4 << y[int(10.0 / tau)][m] << endl;
                f5 << y[int(15.0 / tau)][m] << endl;
                f6 << y[int(18.0 / tau)][m] << endl;
            }
            if (i == 1) {
                f7 << y[0][m] << endl;
                f8 << y[int(5.0 / tau)][m] << endl;
                f9 << y[int(10.0 / tau)][m] << endl;
                f10 << y[int(15.0 / tau)][m] << endl;
                f11 << y[int(18.0 / tau)][m] << endl;
            }
            if (i == 2) {
                f12 << y[0][m] << endl;
                f13 << y[int(5.0 / tau)][m] << endl;
                f14 << y[int(10.0 / tau)][m] << endl;
                f15 << y[int(15.0 / tau)][m] << endl;
                f16 << y[int(18.0 / tau)][m] << endl;
            }
        }
    }
    for (int m = 0; m < NX; m++){
        f1 << x[m] << endl;
    }
}
