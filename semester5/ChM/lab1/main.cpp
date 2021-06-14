#include <iostream>
#include <cmath>

const double epsilon = 0.0001;

bool same_sign(double left, double right) {
    return (left <= 0 && right <= 0) || (left >= 0 && right >= 0);
}

// sh(x) − 12*th(x)−0.311 = 0
double f(double x) {
    return std::sinh(x) - 12 * std::tanh(x) - 0.311;
}

double f_derivative(double x) {
    return std::cosh(x) - 12 / std::pow(std::cosh(x), 2);
}

double bisect(double a, double b) {
    double x_previous = std::numeric_limits<double>::infinity();
    double x = 0;
    double value;
    int i = 1;
    while (std::abs(x - x_previous) >= 2 * epsilon) {
        x_previous = x;
        x = (a + b) / 2;
        value = f(x);
        std::cout << "x" << i << " = " << x << ", f(x) = " << value << std::endl;
        if (same_sign(f(a), value)) {
            a = x;
        }
        if (same_sign(f(b), value)) {
            b = x;
        }
        ++i;
    }

    return x;
}

double newtons_modified() {
    double x0 = -3;
    double x_previous = std::numeric_limits<double>::infinity();
    double x = -3;
    double value;
    int i = 1;
    std::cout << "x0 = " << x0 << std::endl;
    while (std::abs(x - x_previous) >= 2 * epsilon) {
        x_previous = x;
        x = x - f(x)/f_derivative(x0);
        value = f(x);
        std::cout << "x" << i << " = " << x << ", f(x) = " << value << std::endl;
        ++i;
    }

    return x;
}

int main() {
    // Збіжність: n0(ε) = [log2((b−a)/ ε)] + 1 = 13 + 1 = 14
    double root_bisect = bisect(-4, -2);
    // Збіжність: n0(ε) = [log2 (ln(|x0−x∗|/ε)/ln(1/q)) + 1] + 1 = 6
    // q = M2 * |x0 - x*| / m1 = 0.71 < 1
    // M2 = max(|f''(x)|) = |f''(-3.5)| = 16.62
    // m1 = min(|f'(x)|) = f'(-2) = 3.49
    double root_newtons = newtons_modified();
    return 0;
}
