#pragma once

#include "workers.h"

void print_with_additional_data(Worker* workers_tree){
    if (workers_tree == nullptr) return;
    std::vector<int> path = GetPath(workers_tree, {});

    std::cout << "path : {";
    for (int i = 0; i < path.size(); ++i){
        if (i == path.size() - 1) {
            std::cout << path[i];
        } else {
            std::cout << path[i] << ", ";
        }
    }


    std::cout << "} -- Name: " << workers_tree->first_name << " "  << workers_tree->last_name
    << ", Rate: " << workers_tree->compute_rate() << "\nheight: " << workers_tree->height()
    << "\nemployees in group: " << workers_tree->employees_amount() << "\nall employees: "
    << workers_tree->all_employees() << "\nminimal rate: " << workers_tree->min_rate()
    << "\nmaximal rate: " << workers_tree->max_rate() << "\naverage rate: " << workers_tree->average_rate()
    << std::endl << std::endl;

    for (auto child : workers_tree->employees){
        print_with_additional_data(child);
    }
}


void add_node(Worker* father, std::string first_name, std::string last_name,
        std::vector<std::pair<int, int>> abilities, double persistence){

    auto new_worker = new Worker;
    new_worker->first_name = first_name;
    new_worker->last_name = last_name;
    new_worker->persistence = persistence;
    new_worker->abilities = abilities;
    new_worker->father = father;
}


std::vector<Worker*> depth_n_level(Worker* worker, int n){
    if (n == 1) return {worker};

    std::vector<Worker*> result;
    for (auto child : worker->employees){
        for (auto j : depth_n_level(child, n - 1)){
            result.push_back(j);
        }
    }

    return result;
}


int get_index(Worker* worker){
    if (worker->father == nullptr) return -1;
    int result = -1;
    for (auto& employee : worker->father->employees){
        result +=1;
        if (employee == worker) return result;
    }
    return result;
}


void exchange(Worker* workers_tree, int depth){

    std::vector<Worker*> workers = depth_n_level(workers_tree, depth);
    if (workers.size() < 2) return;

    double minimal_maximal_rate = workers[0]->max_rate();
    Worker* minimal_maximal_rate_owner = workers[0];
    double maximal_minimal_rate = workers[0]->min_rate();
    Worker* maximal_minimal_rate_owner = workers[0];

    for (auto& worker : workers){
        if (worker->min_rate() > maximal_minimal_rate){
            maximal_minimal_rate = worker->min_rate();
            maximal_minimal_rate_owner = worker;
        }
        if (worker->max_rate() < minimal_maximal_rate){
            minimal_maximal_rate = worker->max_rate();
            minimal_maximal_rate_owner = worker;
        }
    }

    if (maximal_minimal_rate_owner == minimal_maximal_rate_owner) return;

    std::swap(maximal_minimal_rate_owner->abilities, minimal_maximal_rate_owner->abilities);
    std::swap(maximal_minimal_rate_owner->persistence, minimal_maximal_rate_owner->persistence);
    std::swap(maximal_minimal_rate_owner->employees, minimal_maximal_rate_owner->employees);
    std::swap(maximal_minimal_rate_owner->first_name, minimal_maximal_rate_owner->first_name);
    std::swap(maximal_minimal_rate_owner->last_name, minimal_maximal_rate_owner->last_name);
    std::swap(maximal_minimal_rate_owner->father, minimal_maximal_rate_owner->father);
}


void task_2(int exchange_depth = 2){

    std::cout << "\n\n\nTask 2\n\n\n";

    Worker* workers_tree = generate_workers(37);


    print_with_additional_data(workers_tree);


    exchange(workers_tree, exchange_depth);

    std::cout << "Changed tree: " << std::endl;

    print_tree(workers_tree);
}