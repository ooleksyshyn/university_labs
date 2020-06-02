#pragma once

#include <iostream>
#include <fstream>
#include <tuple>

#include "structures.h"
#include "Search.h"

void UserFileInteraction(){

    std::string Command = "No command";
    while (Command != "EXIT"){
            std::cout << "Input command (ADD, PRINT, SEARCH, EXIT): ";
            std::cin >> Command;
            std::cout << std::endl;

            std::fstream File;

            if (Command == "EXIT") return; else
            if (Command == "ADD") {
                Train NewTrain;
                GetTrain(std::cin,NewTrain);
                File.open("file.txt", std::ios::app);

                File << std::endl << NewTrain;
                File.close();

            } else
            if (Command == "PRINT"){
                File.open("file.txt", std::ios::in);
                while (!File.eof()) {
                    Train train_to_print;
                    File >> train_to_print;
                    PrintTrain(std::cout, train_to_print);
                    std::cout << std::endl;
                }
                File.close();
            } else
            if (Command == "SEARCH"){



                std::cout << "Choose search criterion (NAME, NUMBER, POPULARITY, DATE): ";
                std::cin >> Command;
                std::cout << std::endl;
                if (Command == "NAME"){
                    std::cout << "Enter name beginning: ";
                    std::string beginning;
                    std::cin >> beginning;
                    std::cout << std::endl;
                    Search(File, beginning, []
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
                    Search(File, number, [](const Train& train, int number){return train.number()>=number;});
                } else
                if (Command == "POPULARITY"){
                    double popularity;
                    std::cout << "Enter greatest train popularity: ";
                    std::cin >> popularity;
                    std::cout << std::endl;
                    Search(File, popularity, [](const Train& train, double popularity)
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

                    Search(File, std::tie(least_arr,least_arr_t, greatest_arr, greatest_arr_t),
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