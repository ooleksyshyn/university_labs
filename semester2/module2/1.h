#pragma once

#include "workers.h"
//
// 1st task functions
//


std::vector<std::pair<Worker, Worker>> sorted_interpretation(Worker* workers_tree){
    std::vector<Worker> workers_vector = workers(workers_tree);
    std::sort(workers_vector.begin(), workers_vector.end());

    std::cout << "Sorted workers rating: " << std::endl;
    int index = workers_vector.size();
    for (const auto& i : workers_vector){
        std::cout << index << ") ";
        --index;
        std::cout << i.first_name << " " << i.last_name << ", Rate: " << i.compute_rate() << std::endl;
    }

    std::vector<std::pair<Worker, Worker>> workers_pairs;


    for (int i = 0; i < workers_vector.size(); ++i){
        for (int j = i + 1; j < workers_vector.size(); ++j){
            workers_pairs.emplace_back(std::make_pair(workers_vector[i], workers_vector[j]));
        }
    }

    std::sort(workers_pairs.begin(), workers_pairs.end());

    return workers_pairs;
}


void print_some_data(std::vector<std::pair<Worker, Worker>> workers_pairs, int first, int last){
    std::cout << "Least workers distances: \n";
    for(int i = first; i < last; ++i){
        std::cout << i + 1 << ") "
                  << workers_pairs[i].first.first_name << " " << workers_pairs[i].first.last_name << " and "
                  << workers_pairs[i].second.first_name << " " << workers_pairs[i].second.last_name << " with difference: "
                  << workers_pairs[i].first - workers_pairs[i].second << "\n";
    }
}


void task_1(){

    std::cout << "Task 1 \n\n\n";

    Worker* workers_tree = generate_workers(132);

    std::cout << "Workers tree" << std::endl;
    print_tree(workers_tree);

    std::vector<std::pair<Worker, Worker>> workers_pairs = sorted_interpretation(workers_tree);

    print_some_data(workers_pairs, 0, 14);
    print_some_data(workers_pairs, workers_pairs.size() - 14, workers_pairs.size());
}