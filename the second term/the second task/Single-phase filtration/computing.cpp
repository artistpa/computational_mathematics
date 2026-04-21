#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main(){
    double delta_z = 10.0, B = 50.0, L = 500.0, p_0 = 100.0, p_inj = 150.0, p_prod = 50.0, k = pow(10, -14), mu = pow(10, -8), phi = 0.2, ro_0 = 1000.0, c_f = pow(10, -4), p0 = 120.0;
    double NX = 100.0, tau = 3600.0;
    double h = L / NX, x[101], T_max = 10 * 24 * 3600, t, time_next_output, dt_out_results = 0.1 * 24 * 3600, p[101], a[101], b[101], c[101], d[101], pp[100], qq[100];
    ofstream f1("x.txt", ios::out);
    ofstream f2("p.txt", ios::out);
    for (int i = 0; i <= NX; i++){
        x[i] = i * h;
        f1 << x[i] << endl;
        p[i] = p_0;
    }
    t = 0.0;
    time_next_output = 0.0;
    while (t < T_max){
        a[0] = 1.0;
        b[0] = 0.0;
        a[100] = 1.0;
        c[100] = 0.0;
        d[0] = p_inj;
        d[100] = p_prod;
        pp[1] = 0.0;
        qq[1] = p_inj;
        for (int i = 1; i < NX; i++){
            if (p[i-1] >= p[i]) c[i] = (k / (mu * pow(h, 2))) * (ro_0 * (1 + c_f * (p[i-1] - p0)));
            else  c[i] = (k / (mu * pow(h, 2))) * (ro_0 * (1 + c_f * (p[i] - p0)));
            if (p[i] >= p[i+1]) b[i] = (k / (mu * pow(h, 2))) * (ro_0 * (1 + c_f * (p[i] - p0)));
            else  b[i] = (k / (mu * pow(h, 2))) * (ro_0 * (1 + c_f * (p[i+1] - p0)));
            a[i] = - c[i] - b[i] - phi * c_f * ro_0 / tau;
            d[i] = - phi * c_f * ro_0 * p[i] / tau;
            pp[i+1] = - b[i] / (c[i] * pp[i] + a[i]);
            qq[i+1] = (d[i] - c[i] * qq[i]) / (c[i] * pp[i] + a[i]);
        }
        p[100] = (d[100] - c[100] * qq[100]) / (pp[100] * c[100] + a[100]);
        for (int i = 99; i >= 0; i--){
            p[i] = pp[i+1] * p[i+1] + qq[i+1];
        }
        t += tau;
        if (t >= time_next_output){
            for (int i = 0; i <= NX; i++){
                f2 << p[i] << endl;
            }
            time_next_output += dt_out_results;
        }
    }
}
