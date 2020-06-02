//
// Created by oleksii on 01.10.19.
//

#include "others.hpp"


#include <iostream>
#include <vector>
#include <random>


int random_int(int begin, int end) {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}


std::vector<int> random_vector(size_t size, int lowerBound, int upperBound){
    std::vector<int> result(size);

    for (auto& element : result){
        element = random_int(lowerBound, upperBound);
    }
    return result;
}