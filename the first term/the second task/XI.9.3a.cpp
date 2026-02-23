#include <iostream>
#include <cmath>
using namespace std;


struct YP
    {
        double y;
        double p;
    };

double dydx(double v){
    return v;
}

double dvdx(double x, double y){
    return x * sqrt(y);
}

double dpdx(double u){
    return u;
}

double dudx(double x, double y, double p){
    return (x / (2.0 * sqrt(y))) * p ;
}

YP MRK(double x0, double y0, double v0, double x, double h)
{
    int n = (int)((x - x0) / h);

    double k1[2], k2[2], k3[2], k4[2], k11[2], k22[2], k33[2], k44[2];

    double y = y0, v = v0, p = 0.0, u = 1.0;
    for (int i = 1; i <= n; i++)
    {
        k1[0] = dydx(v);
        k1[1] = dvdx(x0, y);
        k2[0] = dydx(v + 0.5 * h * k1[1]);
        k2[1] = dvdx(x0 + 0.5 * h, y + 0.5 * h * k1[0]);
        k3[0] = dydx(v + 0.5 * h * k2[1]);
        k3[1] = dvdx(x0 + 0.5 * h, y + 0.5 * h * k2[0]);
        k4[0] = dydx(v + h * k3[1]);
        k4[1] = dvdx(x0 + h, y + h * k3[0]);

        y += h * (1.0 / 6.0) * (k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]);
        v += h * (1.0 / 6.0) * (k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1]);

        k11[0] = dpdx(u);
        k11[1] = dudx(x0, y, p);
        k22[0] = dpdx(u + 0.5 * h * k11[1]);
        k22[1] = dudx(x0 + 0.5 * h, y, p + 0.5 * h * k11[0]);
        k33[0] = dpdx(u + 0.5 * h * k22[1]);
        k33[1] = dudx(x0 + 0.5 * h, y, p + 0.5 * h * k22[0]);
        k44[0] = dpdx(u + h * k33[1]);
        k44[1] = dudx(x0 + h, y, p + h * k33[0]);

        p += h * (1.0 / 6.0) * (k11[0] + 2.0 * k22[0] + 2.0 * k33[0] + k44[0]);
        u += h * (1.0 / 6.0) * (k11[1] + 2.0 * k22[1] + 2.0 * k33[1] + k44[1]);

        x0 += h;
    }

    YP yp;
    yp.y = y;
    yp.p = p;

    return yp;
}

int main() {
    const double x = 1.0, y_0 = 0.0, x_0 = 0.0, h = 0.001, y_1 = 2.0;
    double v_0, x_chosen;
    YP yp;
    v_0 = 1.0;
    yp = MRK(x_0, y_0, v_0, x, h);
    while (abs(yp.y - y_1) > 0.001){
        v_0 -= (yp.y - y_1) / yp.p;
        yp = MRK(x_0, y_0, v_0, x, h);
    }
    //cout << yp.y - y_1 << endl;
    //cout << yp.y << endl;
    cin >> x_chosen;
    if (x_chosen >= 0.0 && x_chosen <= 1.0) cout << "y(" << x_chosen << ") = " << MRK(x_0, y_0, v_0, x_chosen, h).y << endl;
    else cout << "Error: x should be from zero to one.";
}
