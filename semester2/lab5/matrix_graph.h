#pragma once

#include "graph_structure.h"
class adjacency_list_graph;

class adjacency_matrix_graph : public graph{
public:
    explicit adjacency_matrix_graph(long long n, bool is_oriented = false,
                                    bool is_weighted = false) : graph(is_oriented, is_weighted){
        adjacency = std::vector<std::vector<int>>(n, std::vector<int>(n,0));
    }


    explicit adjacency_matrix_graph(const adjacency_list_graph&);


    adjacency_matrix_graph& operator=(const adjacency_matrix_graph& G){
        adjacency = G.matrix();
        oriented = G.is_oriented();
        weighted = G.is_weighted();
        return *this;
    }


    std::vector<std::vector<int>> matrix() const {
        return adjacency;
    }


    bool is_oriented() const override{
        return oriented;
    }


    bool is_weighted() const override {
        return weighted;
    }


    void print() const override{
        if (adjacency.empty()) std::cout << "Graph with no vertexes" << std::endl;
        for (const auto& row : adjacency){
            for (const auto& element : row){
                std::string s = std::to_string(element);
                long long size = 4 - s.size();
                for (long long i = 0; i < size; ++i){
                    s = " " + s;
                }
                std::cout << s;
            }
            std::cout << std::endl;
        }
    }


    void add_node(std::vector<std::pair<long long, long long>> connections) override {
        long long n = adjacency.size() + 1;
        for (auto& row : adjacency){
            row.push_back(0);
        }
        adjacency.emplace_back(std::vector<int>(n));

        for (auto& node : connections){
            adjacency[n - 1][node.first] = node.second;
            if (!oriented) adjacency[node.first][n-1] = node.second;
        }
    }


    void add_node(std::vector<long long> connections) override {
        long long n = adjacency.size() + 1;
        for (auto& row : adjacency){
            row.push_back(0);
        }
        adjacency.emplace_back(std::vector<int>(n));

        for (auto& node : connections){
            adjacency[n - 1][node] = 1;
            if (!oriented) adjacency[node][n-1] = 1;
        }
    }


    void add_rib(long long left, long long right, long long weight = 1) override {
        if (!weighted) weight = 1;
        adjacency[left][right] = weight;
        if (!oriented) adjacency[right][left] = weight;
    }


    bool connected()const override;



    void width_go_through(long long, Lambda)override;


    void width_go_through_first_min_weight(long long, Lambda)override;


    std::vector<std::vector<int>> floyd_algorithm() const override;


    std::vector<long long> top_sort() const override;



    long long total_weight()const override;

    void generate_random(long long)override;


    adjacency_matrix_graph build_tree(long long node_number);


    adjacency_matrix_graph build_tree_first_min_weight(long long node_number);


    adjacency_matrix_graph build_min_tree();

private:
    std::vector<std::vector<int>> adjacency;
};