#include "train.h"
#include "multiplesort.h"


void radix_sort(std::vector<Train>&);


void sort_by_digit(std::vector<Train>&, int);


int nth_digit_of(int , int);


void counting_sort(std::vector<Train>&);


int main() {
    std::vector<Train> trains(5);
    trains[0] = Train(12, "noname", 117);
    trains[1] = Train(12, "chernivtsi", 117);
    trains[2] = Train(12, "chernivtsi", 118);
    trains[4] = Train(12, "noname", 117, Train_type::international);

    for (const auto& train : trains){
        std::cout << train << std::endl;
    }

    sort(trains);

    for (const auto& train : trains){
        std::cout << train << std::endl;
    }

    return 0;
}


void radix_sort(std::vector<Train>& Trains){
    for(int i = 1; i < 5; ++i){
        sort_by_digit(Trains, i);
    }
}


int nth_digit_of(int number, int digit_number){
    for (int i = 1; i < digit_number; ++i){
        number = number / 10;
    }
    return number - (number / 10) * 10;
}


void sort_by_digit(std::vector<Train>& Trains, int digit_number){
    std::vector<std::vector<Train>> digit_amounts(10);

    for (auto& train : Trains){
        digit_amounts[nth_digit_of(train.number(), digit_number)].push_back(train);
    }



    int index = 0;
    for (const auto& Trains_by_digit : digit_amounts){
        for (const auto& Train : Trains_by_digit){
            Trains[index] = Train;
            ++index;
        }
    }

}


void counting_sort(std::vector<Train>& Trains){
    std::vector<std::vector<Train>> trains_by_type(4);
    for (auto& train : Trains){
        trains_by_type[static_cast<int>(train.type())].push_back(train);
    }

    int index = 0;
    for (const auto& trains_type : trains_by_type){
        for (const auto& train : trains_type){
            Trains[index] = train;
            ++index;
        }
    }
}
