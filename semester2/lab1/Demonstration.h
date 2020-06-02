#pragma once

#include "vectormode.h"

void Demonstration(){
    std::vector<Train> DataBase;
    DataBase.push_back(Train(1,"Bukovyna",117,"Intercity", Date(26,12,2019), Time(19,56),Date(27,12,2019)
    ,Time(7,35),0.5));
    DataBase.push_back(Train(2,"Kyiv",118,"International", Date(26,12,2019), Time(10,15),Date(29,12,2019)
            ,Time(23,56),0.7));
    DataBase.push_back(Train(3,"Kyivshchyna",236,"Local", Date(01,01,2020), Time(10,15),Date(02,01,2020)
            ,Time(23,56),0.4));
    DataBase.push_back(Train(4,"Kharkiv",1,"International", Date(26,12,2019), Time(10,15),Date(29,12,2019)
            ,Time(12,40),0.8));

    for (const auto& train: DataBase) {
        PrintTrain(std::cout, train);
    }

    std::cout << "Search by beginning (K): " << std::endl;
    std::string beginning = "K";
    Search(DataBase, beginning, []
            (const Train& train, const std::string& beginning){
        std::string ending = beginning;
        ++ending[ending.size()-1];
        return (train.name() >= beginning && train.name() < ending);
    });

    std::cout << "Search by beginning (Kyi): " << std::endl;
    beginning = "Kyi";
    Search(DataBase, beginning, []
            (const Train& train, const std::string& beginning){
        std::string ending = beginning;
        ++ending[ending.size()-1];
        return (train.name() >= beginning && train.name() < ending);
    });

    int number = 118;
    std::cout << "Search by number (118): " << std::endl;
    Search(DataBase, number, [](const Train& train, int number){return train.number()>=number;});


    std::cout << "Search by arrival time (26.12.2019 2:20 - 29.12.2019 13:30): " << std::endl;
    Date least_arr(26,12,2019), greatest_arr(29,12,2019);
    Time least_arr_t(2,20), greatest_arr_t(13,30);
    Search(DataBase, std::tie(least_arr,least_arr_t, greatest_arr, greatest_arr_t),
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


    double popularity = 0.6;
    std::cout << "Search by popularity (0.6): " << std::endl;
    Search(DataBase, popularity, [](const Train& train, double popularity)
    {return train.popularity_rate()<=popularity;});
};