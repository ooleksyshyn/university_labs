#include "matrix_graph.h"
#include "list_graph.h"
#include <deque>
#include <algorithm>


adjacency_matrix_graph::adjacency_matrix_graph(const adjacency_list_graph& Graph) :
                                                graph(Graph.is_oriented(), Graph.is_weighted()){
    long long n = Graph.matrix().size();
    adjacency = std::vector<std::vector<int>>(n, std::vector<int>(n,0));

    for (long long i = 0; i < n; ++i){
        for (long long j = 0; j < Graph.matrix()[i].size(); ++j){
            adjacency[i][Graph.matrix()[i][j].first] = Graph.matrix()[i][j].second;
        }
    }
}


bool adjacency_matrix_graph::connected() const {
    long long n = adjacency.size();
    std::deque<long long> queue(1, 0);
    long long node_number = 0;
    std::vector<long long> visited(n);
    visited[0] = 1;
    while (!queue.empty()){
        node_number = queue[0];
        for (long long j = 0; j < n; ++j){
            if (adjacency[node_number][j] && !visited[j]){
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


void adjacency_matrix_graph::width_go_through(long long node_number, Lambda lambda){
    long long n = adjacency.size();
    bool all_visited = false;
    std::vector<long long> operated_nodes(n, 0);

    while (!all_visited) {

        std::deque<long long> queue(1, node_number);
        std::vector<long long> visited(n);
        visited[node_number] = 1;


        while (!queue.empty()) {
            node_number = queue[0];
            for (long long j = 0; j < n; ++j) {
                if (adjacency[node_number][j] && !visited[j]) {
                    queue.push_back(j);
                    visited[j] = 1;
                }
            }

            if (!operated_nodes[node_number]) lambda(*this, node_number);
            operated_nodes[node_number] = 1;

            queue.pop_front();
        }

        all_visited = true;
        for (long long i = 0; i < operated_nodes.size(); ++i){
            if (operated_nodes[i] == 0) {
                node_number = i;
                all_visited = false;
            }
        }
    }
}


void adjacency_matrix_graph::width_go_through_first_min_weight(long long node_number, Lambda lambda) {
    long long n = adjacency.size();
    bool all_visited = false;
    std::vector<long long> operated_nodes(n, 0);

    while (!all_visited) {

        std::deque<long long> queue(1, node_number);
        std::vector<long long> visited(n);
        visited[node_number] = 1;


        while (!queue.empty()) {
            node_number = queue[0];
            std::vector<std::pair<long long,long long>> sorted_nodes(n);
            for (long long i = 0; i < n; ++i){
                sorted_nodes[i] = std::make_pair(adjacency[node_number][i], i);

            }

            std::sort(sorted_nodes.begin(), sorted_nodes.end());

            for (long long j = 0; j < n; ++j) {
                if (sorted_nodes[j].first && !visited[sorted_nodes[j].second]) {
                    queue.push_back(sorted_nodes[j].second);
                    visited[sorted_nodes[j].second] = 1;
                }
            }

            if (!operated_nodes[node_number]) lambda(*this, node_number);
            operated_nodes[node_number] = 1;

            queue.pop_front();
        }

        all_visited = true;
        for (long long i = 0; i < operated_nodes.size(); ++i){
            if (operated_nodes[i] == 0) {
                node_number = i;
                all_visited = false;
            }
        }
    }
}


std::vector<std::vector<int>> adjacency_matrix_graph::floyd_algorithm() const {
    std::vector<std::vector<int>> result = matrix();
    long long n = result.size();
    for (long long i = 0; i < n; ++i){
        for (long long j = 0; j < n; ++j){
            if (result[i][j] == 0 && i != j) result[i][j] = 1'000'000'000; //very big number
        }
    }

    for (long long k = 0; k < n; ++k){
        for (long long i = 0; i < n; ++i){
            for (long long j = 0; j < n; ++j){

                result[i][j] = std::min(result[i][j], result[i][k] + result[k][j]);

            }
        }
    }

    for (auto& row : result){
        for (auto& element : row){
            if (element == 1'000'000'000){
                element = -1;
            }
        }
    }
    return result;
}


std::vector<long long> adjacency_matrix_graph::top_sort() const {
    long long n = adjacency.size();
    std::vector<std::vector<int>> current_matrix = adjacency;
    std::vector<long long> result_sequence{};
    std::vector<bool> visited(n, false);

    while (result_sequence.size() < n){

        for (long long i = 0; i < n; ++i) {
            if (!visited[i]) {
                bool found = true;
                for (long long j = 0; j < n; ++j) {
                    if (current_matrix[j][i] != 0) found = false;
                }
                if (i == n - 1 && !found) {
                    return {};
                }

                if (found) {
                    result_sequence.push_back(i);
                    for (long long j = 0; j < n; ++j) {
                        current_matrix[i][j] = 0;
                        current_matrix[j][i] = 0;
                    }
                    visited[i] = true;
                    break;
                }
            }
        }

    }

    return result_sequence;

}


adjacency_matrix_graph adjacency_matrix_graph::build_tree(long long node_number){
    adjacency_matrix_graph result_tree(adjacency.size(), oriented, weighted);

    long long n = adjacency.size();
    std::deque<long long> queue(1, node_number);
    std::vector<long long> visited(n);
    visited[node_number] = 1;
    while (!queue.empty()){
        node_number = queue[0];
        for (long long j = 0; j < n; ++j){
            if (adjacency[node_number][j] && !visited[j]){
                queue.push_back(j);
                visited[j] = 1;

                result_tree.add_rib(node_number, j, adjacency[node_number][j]);
            }
        }
        queue.pop_front();
    }

    return result_tree;
}


adjacency_matrix_graph adjacency_matrix_graph::build_tree_first_min_weight(long long node_number){
    adjacency_matrix_graph result_tree(adjacency.size(), oriented, weighted);


    long long n = adjacency.size();
    std::deque<long long> queue(1, node_number);
    std::vector<long long> visited(n);
    visited[node_number] = 1;
    while (!queue.empty()){
        node_number = queue[0];
        std::vector<std::pair<long long, long long>> sorted_nodes(n);
        for (long long i = 0; i < n; ++i){
            sorted_nodes[i] = std::make_pair(adjacency[node_number][i], i);
        }
        std::sort(sorted_nodes.begin(), sorted_nodes.end());


        for (long long j = 0; j < n; ++j) {
            if (sorted_nodes[j].first && !visited[sorted_nodes[j].second]) {
                queue.push_back(sorted_nodes[j].second);
                visited[sorted_nodes[j].second] = 1;

                result_tree.add_rib(node_number, sorted_nodes[j].second, sorted_nodes[j].first);
            }
        }
        queue.pop_front();
    }

    return result_tree;
}


long long adjacency_matrix_graph::total_weight() const {
    long long sum = 0;
    for (const auto& row : adjacency){
        for (const auto element : row){
            sum += element;
        }
    }
    if (!oriented) sum /= 2;
    return sum;
}


adjacency_matrix_graph adjacency_matrix_graph::build_min_tree(){
    if (!connected()) {
        std::cout << "Graph is not connected\n";
        return adjacency_matrix_graph(0);
    }
    long long n = adjacency.size();

    adjacency_matrix_graph result(n, oriented, weighted);

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
                if(min > adjacency[i][j] && added_nodes[i] != added_nodes[j] && adjacency[i][j] != 0){
                    min = adjacency[i][j];
                    first_node = i;
                    second_node = j;
                }


        if(added_nodes[first_node] != added_nodes[second_node]){
            result.add_rib(first_node, second_node, min);


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


void adjacency_matrix_graph::generate_random(long long amount_of_edges) {
    long long n = adjacency.size();
    long long added_edges = 0;

    while (added_edges < amount_of_edges){
        long long i = RandomInt(0, n - 1);
        long long j = RandomInt(0, n - 1);
        long long weight;
        if (weighted){weight = RandomInt(1, 999);} else weight = 1;
        if (adjacency[i][j] == 0 && i != j) {
            add_rib(i, j, weight);
            ++added_edges;
        }
    }
}