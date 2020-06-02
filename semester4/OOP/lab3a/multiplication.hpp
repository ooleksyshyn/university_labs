#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <array>
#include <future>
#include <random>


using matrix = std::vector<std::vector<double>>;


class MatrixMultiplier{
public:
    virtual matrix multiply(const matrix& left, const matrix& right) = 0;
};


class SimpleMatrixMultiplier : public MatrixMultiplier{
public:
    matrix multiply(const matrix& left, const matrix& right) override;
};


class MultiThreadMatrixMultiplier : public MatrixMultiplier{
public:
    matrix multiply(const matrix& left, const matrix& right) override;

private:
    static constexpr int THREADS = 4;
};

void partial_multiply(matrix& result, const matrix& left, const matrix& right, int begin, int end);


matrix generate_random(int n, int m);
