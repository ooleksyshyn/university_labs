#include <iostream>
#include <vector>

using vector = std::vector<double>;
using matrix = std::vector<std::vector<double>>;

std::ostream& operator<<(std::ostream& os, const vector& v) {
    os << "{ ";
    for(const auto& i : v) {
        os << i << " ";
    }
    os << "}";

    return os;
}

std::ostream& operator<<(std::ostream& os, const matrix& m) {
    os << "{\n";
    for(const auto& vec : m) {
        os << vec << "\n";
    }
    os << "}\n";
    return os;
}

std::pair<vector, double> tridiagonal_algorithm(const matrix& m, const vector& f) {
    const int n = m.size() - 1;
    vector y(n + 1, 0);
    vector alpha(n + 1, 0);
    vector beta(n + 1, 0);
    // y[i] = alpha[i + 1] * y[i + 1] + beta[i]
    // a[i] = m[i][i - 1]
    // b[i] = m[i][i + 1]
    // c[i] = - m[i][i]
    // z[i] = c[i] - a[i] * alpha[i]

    double determinant = m[0][0];

    alpha[1] = m[0][1] / -m[0][0]; // b[0] / c[0]
    beta[1] = -f[0] / -m[0][0];     // f[0] / c[0]
    for(int i = 2; i <= n; ++i) {
        double z = -m[i - 1][i - 1] - alpha[i - 1] * m[i - 1][i - 2]; // z[i] = c[i - 1] - a[i - 1] * alpha[i - 1]
        alpha[i] = m[i - 1][i] / z; // b[i - 1] / z
        beta[i] = (-f[i - 1] + m[i - 1][i - 2] * beta[i - 1]) / z; // (f[i] + a[i] * beta[i]) / z
        determinant *= -z;
    }

    y[n] = (-f[n] + m[n][n - 1] * beta[n]) / (-m[n][n] - m[n][n - 1] * alpha[n]);
    for(int i = n - 1; i >= 0; --i) {
        y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1];
    }

    return std::make_pair(y, determinant);
}

int main() {
//    matrix m1 = {{1, 1, 0},
//                 {1, 3, 2},
//                 {0, 1, 2}};
//    vector f1 = {1, 1, 1};

    matrix m = {{2, 1, 0, 0},
                {1, 10, -5, 0},
                {0, 1, -5, 2},
                {0, 0, 1, 4}};
    vector f = {-5, -18, -40, -27};

    auto result = tridiagonal_algorithm(m, f);
    std::cout << result.first << std::endl << "determinant: " << result.second << std::endl;
    return 0;
}
