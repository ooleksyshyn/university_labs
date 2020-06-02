#include "matrix_graph.h"
#include "list_graph.h"
#include "graph_structure.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <iomanip>


/* functions:
 * connected
 * width go through
 * width go through, first least edge length
 * Floyd algorithm
 * topological sort -- Kann algorithm
 * spanning tree -- width do through
 * spanning tree -- width do through, first least edge
 * minimal spanning tree -- Kruskal algorithm*/

void demonstration();
void interaction();
void benchmark();
template <typename Graph>
void operate(Graph& g, std::string& operation){
    if (operation == "ADD_NODE"){
        std::vector<long long> empty = {};
        g.add_node(empty);
    }
    if (operation == "ADD_EDGE"){
        int i, j, weight = 1;
        std::cout << "INPUT TWO NODE NUMBERS (0 to n-1):";
        std::cin >> i >> j;
        if (g.is_weighted()){
            std::cout << "Input weight:";
            std::cin >> weight;
        }
        g.add_rib(i, j, weight);
    }
    if (operation == "PRINT"){
        g.print();
    }
    if (operation == "IS_CONNECTED"){
        if (g.is_oriented()) std::cout << "CAN`T CHECK ORIENTED GRAPH"; else {
            bool is_connected = g.connected();
            if (is_connected) std::cout << "GRAPH IS CONNECTED\n";
            else
                std::cout << "GRAPH IS NOT CONNECTED\n";
        }
    }
    if (operation == "GENERATE_RANDOM"){
        int k;
        int n = g.matrix().size();
        std::cout << "INPUT AMOUNT OF EDGES (NO MORE THAN " << (n*(n-1))/2 << "): ";
        std::cin >> k;
        g.generate_random(k);
    }
    if (operation == "BFS"){
        std::cout << "INPUT STARTING NODE:";
        int i;
        std::cin >> i;
        g.width_go_through(i, [](graph& g, long long j){std::cout << j << " ";});
    }
    if (operation == "BFS_FML"){
        std::cout << "INPUT STARTING NODE:";
        int i;
        std::cin >> i;
        g.width_go_through_first_min_weight(i, [](graph& g, long long j){std::cout << j << " ";});
    }
    if (operation == "FLOYD"){
        std::cout << "ALL DISTANCES:\n";
        auto matrix = g.floyd_algorithm();
        for (auto& row : matrix){
            for (auto element : row){
                std::cout << std::setw(5) << element;
            }
            std::cout << std::endl;
        }
    }
    if (operation == "TOP_SORT"){

        if (!g.is_oriented()){
            std::cout << "CAN`T SORT NOT ORIENTED GRAPH";
        } else {
            std::cout << "SORTED NODES:\n";
            auto sequence = g.top_sort();
            for (auto i : sequence){
                std::cout << i << " ";
            }
        }
    }
    if (operation == "SPANNING_TREE"){
        auto tree = g.build_tree(0);
        tree.print();
        std::cout << "TOTAL WEIGHT: " << tree.total_weight();
    }
    if (operation == "SPANNING_TREE_FML"){
        auto tree = g.build_tree_first_min_weight(0);
        tree.print();
        std::cout << "TOTAL WEIGHT: " << tree.total_weight();
    }

    if (operation == "MINIMAL_TREE"){
        auto tree = g.build_min_tree();
        tree.print();
        std::cout << "TOTAL WEIGHT: " << tree.total_weight();
    }
}

int main(){
    std::string command = std::string();
    while(command != "EXIT"){
        std::cout << "CHOOSE MODE (INTERACTION, BENCHMARK, DEMONSTRATION OR EXIT):";
        std::cin >> command;

        if (command == "BENCHMARK") benchmark();
        if (command == "INTERACTION") interaction();
        if (command == "DEMONSTRATION") demonstration();
    }
    return 0;
}


void demonstration(){

    std::cout << "Create a graph:\n";
    adjacency_matrix_graph g1(3, false, true);


    g1.add_rib(1, 2, 1);
    g1.add_rib(0, 1, 100);
    g1.add_node({std::make_pair(0, 4)});
    g1.add_node({std::make_pair(0, 5), std::make_pair(1, 4)});
    g1.add_rib(0, 2, 3);
    g1.print();
    std::cout << "Graph is connected: " << g1.connected() << std::endl;
    adjacency_list_graph g2(g1);
    std::cout << "Create adjacency list graph based on previous matrix graph";
    g2.print();
    std::cout << "Graph is connected: " << g2.connected() << std::endl;

    int k = 4;
    std::cout << "Width go through, matrix graph:\n";
    g1.width_go_through(k, [](graph& g, int i){std::cout << i << "->";});
    std::cout << std::endl;
    std::cout << "Width go through, first least edge length, matrix graph:\n";
    g1.width_go_through_first_min_weight(k, [](graph& g, int i){std::cout << i << "->";});
    std::cout << std::endl;
    std::cout << "Width go through, list graph:\n";
    g2.width_go_through(4, [](graph& g, int i){std::cout << i << "->";});
    std::cout << "Width go through, first least edge length, list graph:\n";
    g2.width_go_through_first_min_weight(4, [](graph& g, int i){std::cout << i << "->";});

    std::cout << "Build spanning tree, matrix graph:\n";
    adjacency_matrix_graph g3 = g1.build_tree(k);
    g3.print();
    std::cout << "Total weight: " << g3.total_weight() << std::endl;
    std::cout << "Build spanning tree, first least edge length, matrix graph:\n";
    adjacency_matrix_graph g4 = g1.build_tree_first_min_weight(k);
    g4.print();
    std::cout << "Total weight: " << g4.total_weight() << std::endl;
    std::cout << "Build spanning tree, list graph:\n";
    adjacency_list_graph g5 = g2.build_tree(k);
    g5.print();
    std::cout << "Total weight: " << g5.total_weight() << std::endl;
    std::cout << "Build spanning tree, first least edge length, list graph:\n";
    adjacency_list_graph g6 = g2.build_tree_first_min_weight(k);
    g6.print();
    std::cout << "Total weight: " << g4.total_weight() << std::endl;


    std::cout << "Build minimal spanning tree, matrix graph: \n";
    g1.build_min_tree().print();
    std::cout << "Total weight: " << g1.build_min_tree().total_weight() << std::endl;
    std::cout << "Build minimal spanning tree, list graph: \n";
    g2.build_min_tree().print();
    std::cout << "Total weight: " << g2.build_min_tree().total_weight() << std::endl;


    adjacency_matrix_graph g7(6, true);
    g7.add_rib(0, 1);
    g7.add_rib(0, 4);
    g7.add_rib(1, 2);
    g7.add_rib(3, 0);
    g7.add_rib(3, 5);
    g7.add_rib(4, 1);
    adjacency_list_graph g8(g7);
    std::cout << "Graph:\n";
    g7.print();
    std::cout << "\nTopological sort of this matrix graph:\n";
    for (auto i : g7.top_sort()){
        std::cout << i << " ";
    }
    std::cout << "\n\n\nGraph:\n";
    g8.print();
    std::cout << "\nTopological sort of this list graph:\n";
    for (auto i : g8.top_sort()){
        std::cout << i << " ";
    }

    std::cout << "\n\n\nFloyd algorithm for matrix graph:\n";
    for (auto& row : g1.floyd_algorithm()){
        for (auto element : row){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Floyd algorithm for list graph:\n";
    for (auto& row : g1.floyd_algorithm()){
        for (auto element : row){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

}


void benchmark(){

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : connected, adjacency matrix graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_matrix_graph g(n, false, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.connected();

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }
    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : connected, adjacency list graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_list_graph g(n, false, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.connected();

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : width go through, adjacency matrix graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_matrix_graph g(n, false, false);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.width_go_through(0, [](graph& g, long long i){ return;});

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : width go through, adjacency list graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_list_graph g(n, false, false);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.width_go_through(0, [](graph& g, long long i){ return;});

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : width go through, first least edge length, adjacency matrix graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_matrix_graph g(n, true, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.width_go_through_first_min_weight(0, [](graph& g, long long i){ return;});

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : width go through, first least edge length, adjacency list graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_list_graph g(n, true, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.width_go_through_first_min_weight(0, [](graph& g, long long i){ return;});

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : floyd algorithm, adjacency matrix graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_matrix_graph g(n, true, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.floyd_algorithm();

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : floyd algorithm, adjacency list graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_list_graph g(n, true, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.floyd_algorithm();

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 64;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : topological sort, adjacency matrix graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_matrix_graph g(n, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.top_sort();

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 64;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : topological sort, adjacency list graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_list_graph g(n, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            g = g.build_min_tree();
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.top_sort();

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }


    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : spanning tree, adjacency matrix graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_matrix_graph g(n, false, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.build_tree(0);

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : spanning tree, adjacency list graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_list_graph g(n, false, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.build_tree(0);

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : spanning tree, first least edge size, adjacency matrix graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_matrix_graph g(n, false, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.build_tree_first_min_weight(0);

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : spanning tree, first least edge size, adjacency list graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_list_graph g(n, false, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.build_tree_first_min_weight(0);

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : spanning tree, Kruskal algorithm, adjacency matrix graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_matrix_graph g(n, false, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.build_min_tree();

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }

    {
        long long n = 1;
        double elapsed_seconds = 0;
        std::cout << "Benchmark: function : spanning tree, Kruskal algorithm, adjacency list graph\n";
        while (elapsed_seconds < 0.1) {
            n *= 2;
            adjacency_list_graph g(n, false, true);
            long long amount_of_ribs = (n*(n-1))/6;
            g.generate_random(amount_of_ribs);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            g.build_min_tree();

            end = std::chrono::system_clock::now();


            elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            std::cout << "n = " << n << ", ribs: " << amount_of_ribs << ", time: " << elapsed_seconds << std::endl;
        }
    }
}


void interaction(){
    std::string command = std::string();
    std::cout << "FML = FIRST MINIMAL LENGTH\n";
    while (command != "EXIT") {
        std::cout << "CHOOSE GRAPH (MATRIX, LIST, or EXIT): ";
        std::cin >> command;
        std::cout << "INPUT AMOUNT OF NODES: ";
        int n;
        std::cin >> n;
        std::cout << "ORIENTED (0 - NO, 1 - YES): ";
        bool oriented;
        std::cin >> oriented;
        std::cout << "WEIGHTED (0 - NO, 1 - YES): ";
        bool weighted;
        std::cin >> weighted;
        if (command == "MATRIX") {

            adjacency_matrix_graph G(n, oriented, weighted);
            std::string operation = std::string();
            while (operation != "EXIT") {
                std::cout
                        << "CHOOSE OPERATION OUT OF (OR EXIT):\n* GENERATE_RANDOM\n* ADD_NODE\n* ADD_EDGE\n"
                           "* PRINT\n* IS_CONNECTED\n* BFS\n* BFS_FML\n* FLOYD\n"
                           "* TOP_SORT\n* SPANNING_TREE\n* SPANNING_TREE_FML\n* MINIMAL_TREE\n";

                std::cin >> operation;
                operate(G, operation);
            }
        }
        else if (command == "LIST"){
            adjacency_list_graph G(n, oriented, weighted);
            std::string operation = std::string();
            while (operation != "EXIT") {
                std::cout
                        << "CHOOSE OPERATION OUT OF (OR EXIT):\nGENERATE_RANDOM\nADD_NODE\nADD_EDGE\nPRINT\nIS_CONNECTED\nBFS\n"
                           "BFS_FML\nFLOYD\nTOP_SORT\nSPANNING_TREE\nSPANNING_TREE_FML\nMINIMAL_TREE\n";

                std::cin >> operation;
                operate(G, operation);
                std::cout << std::endl;
            }
        }
    }
}


int RandomInt(int begin, int end) {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}