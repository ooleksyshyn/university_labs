#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "structures.h"
#include "Search.h"

void User_Bin_File_Interaction(){

    std::string Command = "No command";
    while (Command != "EXIT"){
        std::cout << "Input command (ADD, PRINT, SEARCH, EXIT): ";
        std::cin >> Command;
        std::cout << std::endl;

        if (Command == "EXIT") return; else
        if (Command == "ADD") {
            Train NewTrain;
            GetTrain(std::cin,NewTrain);
            std::ofstream File("file", std::ios::binary | std::ios::app);
            binary_write_train(File, NewTrain);
        } else
        if (Command == "PRINT"){
            std::ifstream File("file", std::ios::binary | std::ios::in);
            while (!File.eof()) {
                Train train_to_print;
                binary_read_train(File,train_to_print);
                if (train_to_print.data_id() != 0)
                PrintTrain(std::cout, train_to_print);
                std::cout << std::endl;
            }
        } else
        if (Command == "SEARCH"){


            std::ifstream File("file", std::ios::in | std::ios::binary);

            std::cout << "Choose search criterion (NAME, NUMBER, POPULARITY, DATE): ";
            std::cin >> Command;
            std::cout << std::endl;
            if (Command == "NAME"){
                std::cout << "Enter name beginning: ";
                std::string beginning;
                std::cin >> beginning;
                std::cout << std::endl;
                Bin_File_Search(File, beginning, []
                               (const Train& train, const std::string& beginning){
                           std::string ending = beginning;
                           ++ending[ending.size()-1];
                           return (train.name() >= beginning && train.name() < ending);
                       }
                );
            } else
            if (Command == "NUMBER"){
                int number;
                std::cout << "Enter least train number: ";
                std::cin >> number;
                std::cout << std::endl;
                Bin_File_Search(File, number, [](const Train& train, int number){return train.number()>=number;});
            } else
            if (Command == "POPULARITY"){
                double popularity;
                std::cout << "Enter greatest train popularity: ";
                std::cin >> popularity;
                std::cout << std::endl;
                Bin_File_Search(File, popularity, [](const Train& train, double popularity)
                {return train.popularity_rate()<=popularity;});
            } else
            if (Command == "DATE"){
                Date least_arr, greatest_arr;
                Time least_arr_t, greatest_arr_t;

                std::cout << "Enter least train arrival date and time: ";
                std::cin >> least_arr >> least_arr_t;
                std::cout << std::endl;

                std::cout << "Enter greatest train arrival date and time: ";
                std::cin >> greatest_arr >> greatest_arr_t;
                std::cout << std::endl;

                Bin_File_Search(File, std::tie(least_arr,least_arr_t, greatest_arr, greatest_arr_t),
                       [](const Train& train, std::tuple<Date,Time, Date, Time> Period ){
                           if (train.arrival_date() == std::get<0>(Period) &&
                               train.arrival_date() == std::get<2>(Period))
                               return (train.arrival_time() >= std::get<1>(Period) &&
                                       std::get<3>(Period) >= train.arrival_time());

                           if (train.arrival_date() == std::get<0>(Period))
                               return train.arrival_time() >= std::get<1>(Period);

                           if (train.arrival_date() == std::get<2>(Period))
                               return std::get<3>(Period) >= train.arrival_time();

                           return (train.arrival_date() >= std::get<0>(Period) &&
                                   std::get<2>(Period) >= train.arrival_date());
                       });
            }
        }
    }
}