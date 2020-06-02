//
// Created by oleksii on 19.09.19.
//

#include "object.h"
#include "exception"
#include "exceptions.h"
#include <vector>
#include <queue>
#include <iostream>

#ifndef LAB1SEM3_GRAPH_H
#define LAB1SEM3_GRAPH_H

template <typename T>
class Graph{
public:
    Graph() : connections({}), nodes({}){}
    explicit Graph(std::vector<T> values) :
    connections(std::vector<std::vector<int>>(values.size(), std::vector<int>(values.size()))),
    nodes(values){}


    [[nodiscard]] std::vector<std::vector<int>> matrix() const {
        return connections;
    };


    [[nodiscard ]]size_t size() const {
        return nodes.size();
    }


    void add_vertex(T node){
        nodes.emplace_back(node);
        connections.emplace_back(std::vector<int>(nodes.size() - 1));

        for (auto& row : connections){
            row.emplace_back(0);
        }
    }


    void add_vertex(T node, std::vector<std::pair<int, int>> connectedNodes){
        nodes.emplace_back(node);
        connections.emplace_back(std::vector<int>(nodes.size() - 1));

        for (auto& row : connections){
            row.emplace_back(0);
        }
        for (auto i : connectedNodes){
            connections[size() - 1][i.first] = i.second;
            connections[i.first][size() - 1] = i.second;
        }
    }


    void add_edge(int i, int j, int length = 1){
        connections[i][j] = length;
        connections[j][i] = length;
    }


    void remove_vertex(int index){
        nodes.erase(nodes.begin() + index);
        connections.erase(connections.begin() + index);
        for (auto& i : connections){
            i.erase(i.begin() + index);
        }
    }


    void remove_edge(int i, int j){
        connections[i][j] = 0;
        connections[j][i] = 0;
    }


    Graph build_min_tree(){
        if (!connected()) {
            throw ConnectedError("Graph is not connected, so there is no min tree");
        }
        long long n = size();

        Graph<T> result;

        for (auto i : nodes){
            result.add_vertex(i);
        }

        std::vector<long long> added_nodes(n); // позначає, чи належить дереву вершина

        for(long long i = 0; i < n; i++){
            added_nodes[i] = i;
        }

        long long first_node = 0;
        long long second_node = 0;
        long long current_size = 1;
        while(current_size < n){

            long long min = 1'000'000'000;
            for(long long i = 0; i < n; i++)
                for(long long j = 0; j < n; j++)
                    if(min > connections[i][j] && added_nodes[i] != added_nodes[j] && connections[i][j] != 0){
                        min = connections[i][j];
                        first_node = i;
                        second_node = j;
                    }


            if(added_nodes[first_node] != added_nodes[second_node]){
                result.add_edge(first_node, second_node, min);


                long long temp = added_nodes[second_node];
                added_nodes[second_node] = added_nodes[first_node];
                for(long long k = 0; k < n; k++)
                    if(added_nodes[k] == temp)
                        added_nodes[k] = added_nodes[first_node];

                current_size++;
            }
        }

        return result;
    }


    [[nodiscard]] bool connected() const{
        long long n = connections.size();
        std::deque<long long> queue(1, 0);
        long long node_number = 0;
        std::vector<long long> visited(n);
        visited[0] = 1;
        while (!queue.empty()){
            node_number = queue[0];
            for (long long j = 0; j < n; ++j){
                if (connections[node_number][j] && !visited[j]){
                    queue.push_back(j);
                    visited[j] = 1;
                }
            }
            queue.pop_front();
        }
        for (auto i : visited){
            if (i == 0) return false;
        }
        return true;
    }


    std::vector<T> data() const{
        return nodes;
    }


    T& operator[](size_t index){
        return nodes[index];
    }


    const T& operator[](size_t index) const{
        return nodes[index];
    }

private:
    std::vector<std::vector<int>> connections;
    std::vector<T> nodes;
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const Graph<T>& g){
    os << "Adjacency:\n";
    for (const auto& row : g.matrix()){
        for (const auto& i : row){
            os << i << " ";
        }
        os << "\n";
    }

    os << "Data: ";

    for (auto& i : g.data()){
        os << i << "\n";
    }

    return os;
}


template<typename T>
void print_data(const Graph<T*>& g){ //created this functions to print Shapes instead of their pointers
    std::cout << "Adjacency:\n";
    for (const auto& row : g.matrix()){
        for (const auto& i : row){
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Data: ";

    for (auto& i : g.data()){
        std::cout << *i << "\n";
    }
}


#endif //LAB1SEM3_GRAPH_H
