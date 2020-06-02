#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>

#include "structures.h"

const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
const std::vector<std::string> Train_Types = {"Intercity", "International", "Regional", "Fast"};

int RandomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

std::string RandomString(int size){
    std::string s;
    for (int i = 0; i < size; ++i){
        s += alphabet[RandomInt(0, alphabet.size() - 1)];
    }
    return s;
}

Train RandomTrain(){
    int Data_ID = RandomInt(1,100000);
    std::string Name = RandomString(10);
    int Number = RandomInt(1,100000);
    std::string Type = Train_Types[RandomInt(0,3)];
    Date Departure_Date(RandomInt(1,31),RandomInt(1,23),RandomInt(1,2019));
    Time Departure_Time(RandomInt(0,23),RandomInt(0,59));
    Date Arrival_Date(RandomInt(1,31),RandomInt(1,12),RandomInt(1,2019));
    Time Arrival_Time(RandomInt(0,23),RandomInt(0,59));
    double Popularity_Rate = RandomInt(1,2000)/1000.;

    return Train(Data_ID,Name,Number,Type,Departure_Date,Departure_Time,Arrival_Date,Arrival_Time,Popularity_Rate);
}

void benchmark_vector(){
    int k = 2;
    double time = 0;

    while (time < 10) {
        int i = 1;

        std::vector<Train> trains;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        while (i <= k) {
            Train train = RandomTrain();
            trains.push_back(train);
            //std::cout << i << std::endl;
            ++i;
        }

        std::cout << "Search by beginning (k): " << std::endl;
        std::string beginning = "k";
        Search(trains, beginning, []
                (const Train &train, const std::string &beginning) {
            std::string ending = beginning;
            ++ending[ending.size() - 1];
            return (train.name() >= beginning && train.name() < ending);
        });
        end = std::chrono::system_clock::now();

        double elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds>
                (end - start).count()) / 1000.;

        std::cout << "Elements: "  << k << " Time: " << elapsed_seconds << std::endl;
        time = elapsed_seconds;
        k*=2;
    }
}

void benchmark_file(){
    int k = 2;
    double tm = 0;
    while (tm < 10){
        int i = 1;

        std::fstream File;

        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        File.open("file.txt", std::ios::app);

        while (i <= k) {

            Train train = RandomTrain();

            File << std::endl << train;
            //std::cout << i << std::endl;
            ++i;

        }
        File.close();


        std::cout << "Search by beginning (k): " << std::endl;
        std::string beginning = "k";
        Search(File, beginning, []
                (const Train &train, const std::string &beginning) {
            std::string ending = beginning;
            ++ending[ending.size() - 1];
            return (train.name() >= beginning && train.name() < ending);
        });

        end = std::chrono::system_clock::now();


        double elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds>
                (end - start).count()) / 1000.;

        std::cout << "Elements: " << k << " Time: " << elapsed_seconds << std::endl;
        tm = elapsed_seconds;
        k*=2;
    }

}

void benchmark_bin_file(){
    int k = 2;
    double time = 0;
    while (time < 10){
        int i = 1;


        std::ofstream osf("file", std::ios::trunc);
        osf.close();

        std::ofstream File("file", std::ios::app | std::ios::binary);
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        while (i <= k) {
            Train train = RandomTrain();
            binary_write_train(File, train);
            std::cout << i << std::endl;
            ++i;
        }
        File.close();

        std::ifstream F("file", std::ios::in | std::ios::binary);
        std::cout << "Search by beginning (k): " << std::endl;
        std::string beginning = "k";
        Bin_File_Search(F, beginning, []
                (const Train &train, const std::string &beginning) {
            std::string ending = beginning;
            ++ending[ending.size() - 1];
            return (train.name() >= beginning && train.name() < ending);
        });

        end = std::chrono::system_clock::now();

        double elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds>
                (end - start).count()) / 1000.;

        std::cout << "Elements: " << k << " Time: " << elapsed_seconds << std::endl;
        time = elapsed_seconds;
        k*=2;
    }
}