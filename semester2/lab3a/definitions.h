
#ifndef LAB3A_DEFINITIONS_H
#define LAB3A_DEFINITIONS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <chrono>


void selection_sort(std::vector<int>&);

void selection_sort_with_printing(std::vector<int>&);

void quick_sort(std::vector<int>&, int, int);

void quick_sort_with_printing(std::vector<int>&, int, int);

void merge_sort(std::vector<int>&, int , int);

void merge_sort_with_printing(std::vector<int>&, int , int);

void demonstration();

void benchmark();

int RandomInt(int, int);

#endif
