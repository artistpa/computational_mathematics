#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

double dydx(double x,double y){
    return x * x + y * y;
}

int main() {
    const double T = 1, x_0 = 2.0, y_0 = 1.0;
    double y, tau;
    double k1, k2, k3, k4, k5, k6, k7, x0, y0, epsilon;
    int N;
    tau = 0.1;
    N = int(T / tau);
    x0 = x_0;
    y = y_0;
    //cin >> epsilon;
    for (int i = 1; i <= N; i++) {

        k1 = dydx(x0, y);

        k2 = dydx(x0 + 0.2 * tau, y + tau * (0.2 * k1));

        k3 = dydx(x0 + 0.3 * tau, y + tau * ((3.0 / 40.0) * k1 + (9.0 / 40.0) * k2));

        k4 = dydx(x0 + 0.8 * tau, y + tau * ((44.0 / 45.0) * k1 + (-56.0 / 15.0) * k2 + (32.0 / 9.0) * k3));

        k5 = dydx(x0 + (8.0 / 9.0) * tau, y + tau * ((19372.0 / 6561.0) * k1 + (-25360.0 / 2187.0) * k2 + (64448.0 / 6561.0) * k3 + (-212.0 / 729.0) * k4));

        k6 = dydx(x0 + tau, y + tau * ((9017.0 / 3168.0) * k1 + (-355.0 / 33.0) * k2 + (46732.0 / 5247.0) * k3 + (49.0 / 176.0) * k4 + (-5103.0 / 18656.0) * k5));

        k7 = dydx(x0 + tau, y + tau * ((35.0 / 384.0) * k1 + (500.0 / 1113.0) * k3 + (125.0 / 192.0) * k4 + (-2187.0 / 6784.0) * k5 + (11.0 / 84.0) * k6));

        y -= tau * ((35.0 / 384.0) * k1 + (500.0 / 1113.0) * k3 + (125.0 / 192.0) * k4 + (-2187.0 / 6784.0) * k5 + (11.0 / 84.0) * k6);
        //tau *= pow(epsilon * tau / (2 * abs((71.0 / 57600.0) * k1 - 71.0 * k3 / 16695.0 + 71.0 * k4 / 1920.0 - 17253.0 * k5 / 339200.0 + 22.0 * k6 / 525.0 - 1.0 * k7 / 40.0)), 0.2);
        x0 -= tau;
    }
    cout << fixed << setprecision(numeric_limits<double>::max_digits10) << y << endl;
}
