#include "multiplication.hpp"

matrix SimpleMatrixMultiplier::multiply(const matrix &left, const matrix &right) {
    if (left.empty() || right.empty()) return matrix();

    auto n = left.size();
    auto m = right[0].size();
    auto middle_dim = right.size();
    matrix result(n, std::vector<double>(m, 0));

    partial_multiply(result, left, right, 0, n);

    return result;
}

matrix MultiThreadMatrixMultiplier::multiply(const matrix &left, const matrix &right) {
    int n = left.size();
    int m = right[0].size();
    int middle_dim = right.size();

    matrix result(n, std::vector<double>(m, 0));
    std::array<std::future<void>, THREADS - 1> futures;

    for(int i = 0; i < THREADS - 1; ++i){
        futures[i] = std::async(std::launch::async, partial_multiply, std::ref(result), left, right, i * n/THREADS, (i + 1)*n/THREADS);
    }

    partial_multiply(result, left, right, (THREADS - 1) * n/THREADS, n);

    for(auto& future : futures){
        future.get();
    }

    return result;
}

void partial_multiply(matrix &result, const matrix &left, const matrix &right, int begin, int end) {
    int m = right[0].size();
    int middle_dim = right.size();

    for(int i = begin; i < end; ++i){
        for(int j = 0; j < m; ++j){
            for(int k = 0; k < middle_dim; ++k){
                result[i][j] += left[i][k] * right[k][j];
            }
        }
    }
}


matrix generate_random(int n, int m){
    matrix result(n, std::vector<double>(m, 0));

    std::random_device dev;
    std::default_random_engine rng(dev());
    std::uniform_real_distribution<double> dist6; // distribution in range [1, 6]

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            result[i][j] = dist6(rng);
        }
    }

    return result;
}
