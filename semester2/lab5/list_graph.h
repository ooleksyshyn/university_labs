#pragma once

#include "graph_structure.h"
#include "matrix_graph.h"
#include <utility>
#include <algorithm>
#include <cmath>

class adjacency_list_graph : public graph {
public:
    explicit adjacency_list_graph(long long n, bool is_oriented = false,
                                  bool is_weighted = false) : graph(is_oriented, is_weighted){
        adjacency = std::vector<std::vector<std::pair<long long, int>>>(n);
    }


    explicit adjacency_list_graph(const adjacency_matrix_graph& Graph);


    void print() const override {
        if (adjacency.empty()) std::cout << "Graph with no vertexes" << std::endl;
        long long row_number = 0;
        for (const auto& row : adjacency){
            std::cout << row_number << ": ";
            if (row.empty()) std::cout << "no connections";
            for (const auto& pair : row){
                if (weighted){
                    long long size = 4 + 2 + std::log(adjacency.size());
                    std::string s = std::to_string(pair.first) + " (" + std::to_string(pair.second) + ")";
                    while (s.size() < size){
                        s = " " + s;
                    }
                    std::cout << s;
                } else{
                    long long size = 2 + std::log(adjacency.size());
                    std::string s = std::to_string(pair.first);
                    while (s.size() < size){
                        s = " " + s;
                    }
                    std::cout << s;
                }
            }
            std::cout << std::endl;
            ++row_number;
        }
    }


    void add_node(std::vector<std::pair<long long, long long>> connections) override {
        long long n = adjacency.size() + 1;
        adjacency.emplace_back(std::vector<std::pair<long long,int>>());

        for (auto& pair : connections){
            adjacency[n - 1].push_back(pair);
            if (!oriented) adjacency[pair.first].push_back(std::make_pair(n - 1, pair.second));
        }
        for (auto& row : adjacency){
            std::sort(row.begin(), row.end());
        }
    }


    void add_node(std::vector<long long> connections) override {
        long long n = adjacency.size() + 1;
        adjacency.emplace_back(std::vector<std::pair<long long, int>>());

        for (auto& node : connections){
            adjacency[n - 1].push_back(std::make_pair(node, 1));
            if (!oriented) adjacency[node].push_back(std::make_pair(n - 1, 1));
        }
    }


    void add_rib(long long left, long long right, long long weight = 1) override {
        adjacency[left].push_back(std::make_pair(right, weight));
        std::sort(adjacency[left].begin(), adjacency[left].end());
        if (!oriented) {
            adjacency[right].push_back(std::make_pair(left, weight));
            std::sort(adjacency[right].begin(), adjacency[right].end());
        }
    }


    bool is_oriented() const override {
        return oriented;
    }

    bool is_weighted() const override {
        return weighted;
    }

    std::vector<std::vector<std::pair<long long, int>>> matrix() const{
        return adjacency;
    }


    bool connected()const override;


    void width_go_through(long long, Lambda) override;


    void width_go_through_first_min_weight(long long, Lambda) override;


    std::vector<std::vector<int>> floyd_algorithm() const override;


    std::vector<long long> top_sort() const override;


    long long total_weight()const override;


    void generate_random(long long)override;


    adjacency_list_graph build_tree(long long);


    adjacency_list_graph build_tree_first_min_weight(long long);


    adjacency_list_graph build_min_tree();
private:
    std::vector<std::vector<std::pair<long long, int>>> adjacency;
};