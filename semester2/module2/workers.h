#pragma once

#include <vector>
#include <iostream>
#include <utility>
#include <cmath>
#include <string>
#include <random>
#include <algorithm>


const std::string Capital_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

int RandomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

std::string RandomString(int size){
    std::string s;
    for (int i = 0; i < size; ++i){
        if (i == 0) {
            s += Capital_alphabet[RandomInt(0, Capital_alphabet.size() - 1)];
        } else s += alphabet[RandomInt(0, alphabet.size() - 1)];
    }
    return s;
}


struct Worker{


    double compute_rate() const {
        double rate = 0;
        for (auto& pair : abilities){
            rate += pow(pair.first * persistence + pair.second * (1. - persistence), 2);
        }
        rate = pow(rate, 3 + persistence);
        return rate;
    }

    int height() const {
        int height = 1;
        for (auto child : employees){
            if (height < child->height()){
                height = child->height();
            }
        }
        return height;
    }

    int employees_amount() const{
        return employees.size();
    }


    int all_employees() const {
        int amount = 0;
        for (auto i : employees){
            amount += i->all_employees() + 1;
        }
        return amount;
    }


    double min_rate() const {
        double min = compute_rate();
        for (auto& employee : employees){
            if (employee->min_rate() < min){
                min = employee->min_rate();
            }
        }
        return min;
    }

    double max_rate() const {
        double max = compute_rate();
        for (auto& employee : employees){
            if (employee->max_rate() > max){
                max = employee->max_rate();
            }
        }
        return max;
    }


    double average_rate() const {
        if (employees.empty()) return compute_rate();

        double sum = compute_rate();
        double amount = 1;
        for (auto& empl : employees){
            sum += empl->average_rate() / (empl->all_employees() + 1.);
            amount += empl->all_employees() + 1.0;
        }

        return sum/amount;
    }
    

    Worker* father;

    std::string first_name;
    std::string last_name;
    double persistence;
    std::vector<Worker*> employees;
    std::vector<std::pair<int, int>> abilities; // (min, max)
};


Worker* create(){
    auto worker = new Worker;
    worker->first_name = RandomString(6);
    worker->last_name = RandomString(7);
    worker->persistence = RandomInt(1, 1'000)/1'000.; // I think its enough

    for (int i = 0; i < 11; ++i){
        int a = RandomInt(1, 1000);
        int b = RandomInt(1, 1000);
        worker->abilities.emplace_back(std::make_pair(std::min(a, b), std::max(a, b)));
    }

    worker->father = nullptr;
    return worker;
}



void add_child(Worker* workers_tree){
    int Random = RandomInt(1, 10);

    if (workers_tree->employees.empty() || Random > 8) { // Random compared with 8 for distributing workers
        Worker* new_child = create();
        workers_tree->employees.push_back(new_child);
        new_child->father = workers_tree;
        return;
    }

    int index = RandomInt(0, workers_tree->employees.size() - 1);

    add_child(workers_tree->employees[index]);
}


template <class TREE>
std::vector<int> GetPath(TREE* element, std::vector<int> CurrentPath){
    if (element == nullptr) return {};

    if (element->father == nullptr) return CurrentPath;

    TREE* previous = element->father;

    for (int i = 0; i < previous->employees.size(); ++i){
        if (previous->employees[i] == element){
            CurrentPath.insert(CurrentPath.begin(), i);
            return GetPath(previous, CurrentPath);
        }
    }
    return CurrentPath;
}


template <class TREE>
TREE* GetByPath(TREE* tree, std::vector<int> path){

    int counter = 0;
    while (counter < path.size()) {
        if (tree->employees.size() < path[counter] + 1){
            std::cout << "Invalid path\n";
            return nullptr;
        }

        tree = tree->employees[path[counter]];
        ++counter;
    }

    return tree;
}


void print_tree(Worker* worker){

    if (worker == nullptr) return;
    std::vector<int> path = GetPath(worker, {});

    std::cout << "path : {";
    for (int i = 0; i < path.size(); ++i){
        if (i == path.size() - 1) {
            std::cout << path[i];
        } else {
            std::cout << path[i] << ", ";
        }
    }


    std::cout << "} -- Name: " << worker->first_name << " "  << worker->last_name  << ", Rate: " << worker->compute_rate() << std::endl;

    for (auto child : worker->employees){
        print_tree(child);
    }
}


std::vector<Worker> workers(Worker* worker){
    if (worker == nullptr) return {};


    std::vector<Worker> result = {*worker};


    for (const auto& i : worker->employees){
        for (const auto& element : workers(i))
        result.push_back(element);
    }
    return result;
}


bool operator<(const Worker& lw, const Worker& rw){
    return lw.compute_rate() < rw.compute_rate();
}


double operator-(const Worker& lw, const Worker& rw){
    std::vector<std::pair<int, int>> left = lw.abilities;
    std::vector<std::pair<int, int>> right = rw.abilities;

    std::sort(left.rbegin(), left.rend());
    std::sort(right.rbegin(), right.rend());
    double result = 0.;
    for (int i = 0; i < left.size(); ++i){
        result += pow(left[i].second - right[i].second, 2);
    }
    result += 1;
    result = pow(result, std::min(lw.persistence, rw.persistence) - 2 * 3);

    return result;
}


bool operator<(const std::pair<Worker, Worker>& lp, const std::pair<Worker, Worker>& rp){
    return (lp.first - lp.second) < (rp.first - rp.second);
}


Worker* generate_workers(int n){
    Worker* resulting_workers_tree = create();

    for (int i = 0; i < n - 1; ++i){
        add_child(resulting_workers_tree);
    }

    return resulting_workers_tree;
}