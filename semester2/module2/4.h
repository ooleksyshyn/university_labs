#pragma once

#include "workers.h"
#include <iostream>
#include <vector>
#include <utility>

struct bin_tree{
    std::pair<Worker, Worker> workers_couple;

    bin_tree* father;
    std::vector<bin_tree*> employees;
};


bin_tree* create_bin(){
    auto* tree = new bin_tree;

    tree->father = nullptr;
    tree->employees.push_back(nullptr);
    tree->employees.push_back(nullptr);
    return tree;
}


bin_tree* create_bin(std::pair<Worker, Worker>& couple){
    auto* tree = new bin_tree;

    tree->workers_couple = couple;
    tree->father = nullptr;
    tree->employees.push_back(nullptr);
    tree->employees.push_back(nullptr);
    return tree;
}


void add_data(bin_tree* tree, std::pair<Worker, Worker>& new_couple){
    if (tree->employees.empty()){
        bin_tree* nulltree = create_bin();
        nulltree = nullptr;

        tree->employees.push_back(nulltree);
        tree->employees.push_back(nulltree);

        if (tree->workers_couple.first - tree->workers_couple.second > new_couple.second - new_couple.first){
            tree->employees[0] = create_bin(new_couple);
            tree->employees[0]->father = tree;
        } else{
            tree->employees[1] = create_bin(new_couple);
            tree->employees[1]->father = tree;
        }
        return;
    }

    if (tree->workers_couple.first - tree->workers_couple.second > new_couple.second - new_couple.first
                        & tree->employees[0] == nullptr){
        tree->employees[0] = create_bin(new_couple);
        tree->employees[0]->father = tree;
        return;
    }

    if (tree->workers_couple.first - tree->workers_couple.second <= new_couple.second - new_couple.first
                        & tree->employees[1] == nullptr){
        tree->employees[1] = create_bin(new_couple);
        tree->employees[1]->father = tree;
        return;
    }

    if (tree->workers_couple.first - tree->workers_couple.second > new_couple.second - new_couple.first){
        add_data(tree->employees[0], new_couple);
    } else{
        add_data(tree->employees[1], new_couple);
    }
}


void print_tree(bin_tree* tree){

    if (tree == nullptr) return;
    std::cout << "{";
    std::vector<int> path = GetPath(tree, {});

    for (int i = 0; i < path.size(); ++i){
        if (i == path.size() - 1) {
            std::cout << path[i];
        } else {
            std::cout <<path[i] << ", ";
        }
    }


    std::cout << "} -- "
    << tree->workers_couple.first.first_name << " " << tree->workers_couple.first.last_name << " and "
    << tree->workers_couple.second.first_name << " " << tree->workers_couple.second.last_name << ", Distance: "
    << tree->workers_couple.first - tree->workers_couple.second << std::endl;

    for (auto child : tree->employees){
        print_tree(child);
    }
}


bin_tree* build_bin_tree(int amount){
    Worker* worker = generate_workers(amount);

    std::vector<Worker> workers_vector = workers(worker);
    std::vector<std::pair<Worker, Worker>> workers_pairs;


    for (int i = 0; i < workers_vector.size(); ++i){
        for (int j = i + 1; j < workers_vector.size(); ++j){
            workers_pairs.emplace_back(std::make_pair(workers_vector[i], workers_vector[j]));
        }
    }

    bin_tree* worker_pairs_tree = create_bin(workers_pairs[0]);
    for (int i = 1; i < workers_pairs.size(); ++i){
        add_data(worker_pairs_tree, workers_pairs[i]);
    }

    return worker_pairs_tree;
}


std::vector<std::pair<Worker, Worker>> search(bin_tree* worker_pairs_tree, double search_value, double accuracy){
    std::vector<std::pair<Worker, Worker>> result;
    if (worker_pairs_tree == nullptr) return {};

    if (worker_pairs_tree->workers_couple.first - worker_pairs_tree->workers_couple.second > search_value + accuracy){
        return search(worker_pairs_tree->employees[0], search_value, accuracy);
    }

    if (worker_pairs_tree->workers_couple.first - worker_pairs_tree->workers_couple.second < search_value - accuracy){
        return search(worker_pairs_tree->employees[1], search_value, accuracy);
    }

    for (const auto &i : search(worker_pairs_tree->employees[0], search_value, accuracy)){
        result.push_back(i);
    }

    result.push_back(worker_pairs_tree->workers_couple);

    for (const auto &i : search(worker_pairs_tree->employees[1], search_value, accuracy)){
        result.push_back(i);
    }

    return result;
}


void task_4(double search_value = 5 * std::pow(10, -35), double accuracy = 2 * std::pow(10, -35)){

    std::cout << "\n\n\nTask 4\n\n\n";

    bin_tree* worker_pairs_tree = build_bin_tree(8);

    print_tree(worker_pairs_tree);

    std::cout << "Searched pairs (search value: " << search_value << ", accuracy: " << accuracy << "): " << std::endl;
    bool found_data = false;
    for (auto& pair : search(worker_pairs_tree, search_value, accuracy)){
        found_data = true;

        std::cout << pair.first.first_name << " " << pair.first.last_name << " and "
                 << pair.second.first_name << " " << pair.second.last_name << " with difference: "
                 << pair.first - pair.second << std::endl;
    }

    if (!found_data) std::cout << "No such elements:(";
}