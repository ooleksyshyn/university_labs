//
// Created by oleksii on 01.10.19.
//

#ifndef LAB1_OTHERS_HPP
#define LAB1_OTHERS_HPP

#include <iostream>
#include <vector>
#include <random>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec){
    os << "{ ";
    for (auto& i : vec){
        os << i << " ";
    }
    os << "}";

    return os;
}


int random_int(int begin, int end);


std::vector<int> random_vector(size_t size, int = 0, int = 100);

#endif //LAB1_OTHERS_HPP
