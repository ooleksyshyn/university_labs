#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "structures.h"
#include "UserInteraction.h"

template <class Func, typename P>
void Search(const std::vector<Train>& DataBase,  const P& criteria, Func func){
    for (const auto& train : DataBase ){
        if (func(train,criteria)) PrintTrain(std::cout, train);
    }
}

template <class Func, typename P>
void Search(std::fstream& File,  const P& criteria, Func func){
    File.open("file.txt",std::ios::in);
    while(!File.eof()) {
        Train train;
        File >> train;
        if (func(train, criteria)) PrintTrain(std::cout, train);
    }
    File.close();
}

template <typename Func, typename P>
void Bin_File_Search(std::ifstream& File, const P& criteria, Func func){
    while(!File.eof()){
        Train train;
        binary_read_train(File,train);
        if (train.data_id() == 0) return;
        if (func(train,criteria)) PrintTrain(std::cout, train);
    }
}