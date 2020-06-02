#pragma once

#include <cstdio>

void Bin_File_Demonstration(){


    std::ofstream file("file", std::ios::app | std::ios::binary);
    binary_write_train(file,Train(1,"Bukovyna",117,"Intercity", Date(26,12,2019), Time(19,56),Date(27,12,2019)
            ,Time(7,35),0.5));
    binary_write_train(file,Train(2,"Kyiv",118,"International", Date(26,12,2019), Time(10,15),Date(29,12,2019)
                 ,Time(23,56),0.7));
    binary_write_train(file,Train(3,"Kyivshchyna",236,"Local", Date(01,01,2020), Time(10,15),Date(02,01,2020)
                 ,Time(23,56),0.4));
    binary_write_train(file,Train(4,"Kharkiv",1,"International", Date(26,12,2019), Time(10,15),Date(29,12,2019)
                 ,Time(12,40),0.8));
    file.close();

    std::ifstream F("file", std::ios::in | std::ios::binary);
    while (!F.eof()) {
        Train train_to_print;
        binary_read_train(F,train_to_print);
        PrintTrain(std::cout, train_to_print);
        std::cout << std::endl;
    }
    F.close();

    std::ifstream File("file", std::ios::in | std::ios::binary);
    std::cout << "Search by beginning (K): " << std::endl;
    std::string beginning = "K";
    Bin_File_Search(File, beginning, []
            (const Train& train, const std::string& beginning){
        std::string ending = beginning;
        ++ending[ending.size()-1];
        return (train.name() >= beginning && train.name() < ending);
    });
    File.close();

    std::ifstream File1("file", std::ios::in | std::ios::binary);
    std::cout << "Search by beginning (Kyi): " << std::endl;
    beginning = "Kyi";
    Bin_File_Search(File1, beginning, []
            (const Train& train, const std::string& beginning){
        std::string ending = beginning;
        ++ending[ending.size()-1];
        return (train.name() >= beginning && train.name() < ending);
    });
    File1.close();

    std::ifstream File2("file", std::ios::in | std::ios::binary);
    int number = 118;
    std::cout << "Search by number (=>118): " << std::endl;
    Bin_File_Search(File2, number, [](const Train& train, int number){return train.number()>=number;});
    File2.close();


    std::ifstream File3("file", std::ios::in | std::ios::binary);
    std::cout << "Search by arrival time (26.12.2019 2:20 - 29.12.2019 13:30): " << std::endl;
    Date least_arr(26,12,2019), greatest_arr(29,12,2019);
    Time least_arr_t(2,20), greatest_arr_t(13,30);
    Bin_File_Search(File3, std::tie(least_arr,least_arr_t, greatest_arr, greatest_arr_t),
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
    File3.close();

    std::ifstream File4("file", std::ios::in | std::ios::binary);
    double popularity = 0.6;
    std::cout << "Search by popularity (<=0.6): " << std::endl;
    Bin_File_Search(File4, popularity, [](const Train& train, double popularity)
    {return train.popularity_rate()<=popularity;});
    File4.close();
};