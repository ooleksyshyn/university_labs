#pragma once


#include "workers.h"
#include <deque>

class graph {
public:
    explicit graph(int n){
        adjacency = std::vector<std::vector<double>>(n, std::vector<double>(n,0));
    }


    std::vector<std::vector<double>> matrix() const {
        return adjacency;
    }

    void print() const{
        for (const auto& row : adjacency){
            for (const auto& element : row){
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }

    void add_rib(int left, int right, double length) {
        adjacency[left][right] = length;
        adjacency[right][left] = length;
    }

    int width_go_through(int node_number = 0){
        int n = adjacency.size();
        bool all_visited = false;
        std::vector<int> operated_nodes(n, 0);
        int amount_of_parts = 0;

        while (!all_visited) {

            ++amount_of_parts;
            std::deque<int> queue(1, node_number);
            std::vector<int> visited(n);
            visited[node_number] = 1;


            while (!queue.empty()) {
                node_number = queue[0];
                for (int j = 0; j < n; ++j) {
                    if (adjacency[node_number][j] != 0 && !visited[j]) {
                        queue.push_back(j);
                        visited[j] = 1;
                    }
                }

                if (!operated_nodes[node_number]) {
                                                             //write here something !!!
                }
                operated_nodes[node_number] = 1;

                queue.pop_front();
            }

            all_visited = true;
            for (int i = 0; i < operated_nodes.size(); ++i){
                if (operated_nodes[i] == 0) {
                    node_number = i;
                    all_visited = false;
                }
            }
        }

        return amount_of_parts;
    }


    std::vector<std::vector<double>> floyd_algorithm() const {
        std::vector<std::vector<double>> result = matrix();
        int n = result.size();
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (result[i][j] == 0 && i != j) result[i][j] = 1'000'000'000; //very big number
            }
        }

        for (int k = 0; k < n; ++k){
            for (int i = 0; i < n; ++i){
                for (int j = 0; j < n; ++j){

                    result[i][j] = std::min(result[i][j], result[i][k] + result[k][j]);

                }
            }
        }

        return result;
    }

private:
    std::vector<std::vector<double>> adjacency;
};


std::vector<std::pair<int, double>> find_distances(graph& G, int node_number){

    std::vector<std::pair<int, double>> result;

    std::vector<std::vector<double>> adjacency = G.matrix();

    int n = adjacency.size();

    std::vector<std::vector<double>> shortest_ways = G.floyd_algorithm();
    for (int i = 0; i < shortest_ways.size(); ++i){
        if (shortest_ways[node_number][i] < 1'000'000) {
            result.emplace_back(std::make_pair(i, shortest_ways[node_number][i]));
        }
    }

    return result;
}


void task_3(int node_number = 0, double distance_comparator = 4 * std::pow(10, -37)){

    std::cout << "\n\n\nTask 3\n\n\n";

    Worker* workers_tree = generate_workers(37);

    std::cout << "Workers tree" << std::endl;
    print_tree(workers_tree);

    std::vector<Worker> workers_vector = workers(workers_tree);
    graph G(workers_vector.size());

    for (int i = 0; i < workers_vector.size(); ++i){
        for (int j = i + 1; j < workers_vector.size(); ++j){
            if (workers_vector[i] - workers_vector[j] < distance_comparator){
                G.add_rib(i, j, workers_vector[i] - workers_vector[j]);
            }
        }
    }

    G.print();
    std::cout << "Amount of parts: " << G.width_go_through() << std::endl;

    std::cout << "Distances from vertex " << node_number << " to others in its component:" << std::endl;

    bool very_strange_flag = false;
    bool one_more_very_strange_flag = false;
    for (auto& pair : find_distances(G, node_number)){
        if (!very_strange_flag) {
            very_strange_flag = true;
        } else {
            std::cout << "Distance to " << pair.first << " : " << pair.second << std::endl;
            one_more_very_strange_flag = true;
        }
    }

    if (!one_more_very_strange_flag) std::cout << "Vertex " << node_number << " has no connections";
}