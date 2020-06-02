#pragma once


#include "train.h"


void sort(std::vector<Train>&);
bool compare_trains_by_field(const Train&, const Train&, int);
bool equal_trains_by_field(const Train&, const Train&, int);
bool compare_two_trains(const Train&, const Train&, std::vector<int>&);
// function makes >= comparison for trains with given priorities
void merge_sort_for_trains(std::vector<Train>&, std::vector<int>&, int, int);





void sort(std::vector<Train>& Trains) {
    std::vector<int> priorities(9, 0); // default priority == 10 > 9 which is amount of fields
    std::cout << "    Insert number to set comparison priority:\n\n"
                 "    Train Data_ID -- 1\n"
                 "    Train Name -- 2\n"
                 "    Train Number -- 3\n"
                 "    Train Type -- 4\n"
                 "    Departure_Date -- 5\n"
                 "    Departure_Time -- 6\n"
                 "    Arrival_Date -- 7\n"
                 "    Arrival_Time -- 8\n"
                 "    Popularity_Rate -- 9\n"
                 "    or 0 if you ended inserting prioties\n\n" << std::endl;
    int field_number = 10;
    int priority = -1;
    while (field_number != 0) {
        ++priority;
        if (priority == 9) break;
        std::cout << "Print field number for comparison priority " << priority + 1 << " : ";
        std::cin >> field_number;

        if (field_number == 0) break;

        priorities[priority] = field_number; // counter is
    }



    merge_sort_for_trains(Trains, priorities, 0, Trains.size() - 1);
}


bool compare_trains_by_field(const Train &left, const Train &right, int field_number) {
    switch (field_number) {
        case 1 : return left.data_id() >= right.data_id();
        case 2 : return left.name() >= right.name();
        case 3 : return left.number() >= right.number();
        case 4 : return static_cast<int>(left.type()) >= static_cast<int>(right.type());
        case 5 : return left.arrival_date() >= right.departure_date();
        case 6 : return left.departure_time() >= right.departure_time();
        case 7 : return left.arrival_date() >= right.arrival_date();
        case 8 : return left.arrival_time() >= right.arrival_time();
        case 9 : return left.popularity_rate() >= right.popularity_rate();
    }
}


bool equal_trains_by_field(const Train &left, const Train &right, int field_number) {
    switch (field_number) {
        case 1 : return left.data_id() == right.data_id();
        case 2 : return left.name() == right.name();
        case 3 : return left.number() == right.number();
        case 4 : return static_cast<int>(left.type()) == static_cast<int>(right.type());
        case 5 : return left.arrival_date() == right.departure_date();
        case 6 : return left.departure_time() == right.departure_time();
        case 7 : return left.arrival_date() == right.arrival_date();
        case 8 : return left.arrival_time() == right.arrival_time();
        case 9 : return left.popularity_rate() == right.popularity_rate();
    }
}


bool compare_two_trains(const Train &left, const Train &right, std::vector<int> &priorities) {
    for (auto field : priorities){
        if (field == 0) return true;
        if (!equal_trains_by_field(left, right, field)) {
            return compare_trains_by_field(left, right, field);
        }
    }
    return true;
}


void
merge_sort_for_trains(std::vector<Train> &Trains, std::vector<int> &priorities, int left_position, int right_position) {

    if (right_position == left_position) return;

    int middle = (right_position + left_position)/2;

    merge_sort_for_trains(Trains, priorities, left_position, middle);
    merge_sort_for_trains(Trains, priorities, middle + 1, right_position);

    std::vector<Train> left_part, right_part;
    for (int i = left_position; i <= middle; ++i){
        left_part.push_back(Trains[i]);
    }
    for (int i = middle + 1; i <= right_position; ++i){
        right_part.push_back(Trains[i]);
    }

    int right_vector_index = 0, left_vector_index = 0;
    for (int i = left_position; i <= right_position; ++i){
        if (right_vector_index == right_part.size()){
            Trains[i] = left_part[left_vector_index];
            ++left_vector_index;
        } else if (left_vector_index == left_part.size()){
            Trains[i] = right_part[right_vector_index];
            ++right_vector_index;
        } else if (compare_two_trains(right_part[right_vector_index], left_part[left_vector_index], priorities)){
            Trains[i] = left_part[left_vector_index];
            ++left_vector_index;
        } else{
            Trains[i] = right_part[right_vector_index];
            ++right_vector_index;
        }
    }

}
