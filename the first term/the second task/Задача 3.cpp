// Метод пристрелки
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;

struct YP
    {
        double y;
        double p;
    };

double dydx(double v){
    return v;
}

double dvdx(double x, double y, double v){
    return 2 - 6 * x + 2 * pow(x, 3) + (pow(x, 2) - 3) * exp(x) * sin(x) * (1 + cos(x)) + cos(x) * (exp(x) + pow(x, 2) - 1 + pow(x, 4) - 3 * pow(x, 2)) - (pow(x, 2) - 3) * v - (pow(x, 2) - 3) * cos(x) * y;
}

double dpdx(double u){
    return u;
}

double dudx(double x, double p, double u){
    return - (pow(x, 2) - 3) * u - (pow(x, 2) - 3) * cos(x) * p;
}

YP MRK(double x0, double y0, double v0, double x, double h)
{
    int n = (int)((x - x0) / h);

    double k1[2], k2[2], k3[2], k4[2], k11[2], k22[2], k33[2], k44[2];

    double y = y0, v = v0, p = 0.0, u = 1.0;
    for (int i = 1; i <= n; i++)
    {
        k1[0] = dydx(v);
        k1[1] = dvdx(x0, y, v);
        k2[0] = dydx(v + 0.5 * h * k1[1]);
        k2[1] = dvdx(x0 + 0.5 * h, y + 0.5 * h * k1[0], v + 0.5 * h * k1[1]);
        k3[0] = dydx(v + 0.5 * h * k2[1]);
        k3[1] = dvdx(x0 + 0.5 * h, y + 0.5 * h * k2[0], v + 0.5 * h * k2[1]);
        k4[0] = dydx(v + h * k3[1]);
        k4[1] = dvdx(x0 + h, y + h * k3[0], v + h * k3[1]);

        y += h * (1.0 / 6.0)*(k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]);
        v += h * (1.0 / 6.0)*(k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1]);

        k11[0] = dpdx(u);
        k11[1] = dudx(x0, p, u);
        k22[0] = dpdx(u + 0.5 * h * k11[1]);
        k22[1] = dudx(x0 + 0.5 * h, p + 0.5 * h * k11[0], u + 0.5 * h * k11[1]);
        k33[0] = dpdx(u + 0.5 * h * k22[1]);
        k33[1] = dudx(x0 + 0.5 * h, p + 0.5 * h * k22[0], u + 0.5 * h * k22[1]);
        k44[0] = dpdx(u + h * k33[1]);
        k44[1] = dudx(x0 + h, p + h * k33[0], u + h * k33[1]);

        p += h * (1.0 / 6.0)*(k11[0] + 2.0 * k22[0] + 2.0 * k33[0] + k44[0]);
        u += h * (1.0 / 6.0)*(k11[1] + 2.0 * k22[1] + 2.0 * k33[1] + k44[1]);

        x0 += h;
    }

    YP yp;
    yp.y = y;
    yp.p = p;

    return yp;
}

int main() {
    const double x = PI, y_0 = 0.0, x_0 = 0.0, h = 0.001, y_1 = pow(PI, 2);
    double v_0;
    YP yp;
    v_0 = 0.0;
    yp = MRK(x_0, y_0, v_0, x, h);
    while (abs(yp.y - y_1) > 0.001){
        v_0 -= (yp.y - y_1) / yp.p;
        yp = MRK(x_0, y_0, v_0, x, h);
        //cout << yp.y << endl;
        //cout << y_1 << endl;
    }
    cout << "y(0.5) = " << MRK(x_0, y_0, v_0, 0.5, h).y << endl;
    cout << "y(1.0) = " << MRK(x_0, y_0, v_0, 1.0, h).y << endl;
    cout << "y(1.5) = " << MRK(x_0, y_0, v_0, 1.5, h).y << endl;
    cout << "y(2.0) = " << MRK(x_0, y_0, v_0, 2.0, h).y << endl;
    cout << "y(2.5) = " << MRK(x_0, y_0, v_0, 2.5, h).y << endl;
    cout << "y(3.0) = " << MRK(x_0, y_0, v_0, 3.0, h).y << endl;
}
