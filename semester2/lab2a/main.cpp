#include "structures.h"
#include "point.hpp"


#include <iostream>
#include <vector>
#include <string>
#include <chrono>


template<typename QueueType>
void demonstration(QueueType& queue){
    queue.push_back(Point(1.2,2.3,3.5));
    std::cout << queue << " :Add (1.2,2.3,3.5)" << std::endl;
    queue.erase(queue.begin());
    std::cout << queue << " :Dequeue" << std::endl;
    queue.push_back(Point(5,6,7));
    std::cout << queue << " :Add (5,6,7)"<< std::endl;
    queue.push_back(Point(13,12,5));
    std::cout << queue << " :Add (13,12,5)" << std::endl;
    queue.push_back(Point(1,2,3));
    std::cout << queue << " :Add (1,2,3)" << std::endl;
    queue.erase(queue.begin());
    std::cout << queue << " :Dequeue" << std::endl;
    queue.erase(queue.begin());
    std::cout << queue << " :Dequeue" << std::endl;

}


template<typename QueueType>
void interaction(QueueType& queue){
    std::string command = "No Command";
    while (command != "EXIT"){
        std::cout << "Choose command (ENQ, DEQ, EXIT): ";
        std::cin >> command;
        std::cout << std::endl;
    if (command == "ENQ"){
        std::cout << "Input element (point): ";
        Point X;
        std::cin >> X;
        std::cout << std::endl;
        queue.push_back(X);
        std::cout << queue;
        std::cout << std::endl;
    } else if (command == "DEQ"){
        queue.erase(queue.begin());
        std::cout << queue;
        std::cout << std::endl;
    }
}
}


template<typename QueueType>
void benchmark(QueueType& queue){
    int k = 2;
    double time = 0;
    while (time < 10) {
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for (int i = 1; i <= k; ++i){
            queue.push_back(Point(i-1,i,i+1));
        }
        for (int i = 1; i <= k; ++i){
            queue.push_back(Point(i+0.1,i,i-0.1));
            queue.erase(queue.begin());
        }
        while (queue.size() > 1) queue.erase(queue.begin());
        end = std::chrono::system_clock::now();
        double elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds>
                (end - start).count()) / 1000.;
        std::cout << "Elements: "  << k << " Time: " << elapsed_seconds << std::endl;
        time = elapsed_seconds;
        k *= 2;
    }
}


template<typename QueueType>
void operations(QueueType& queue){
    std::cout << "Choose interaction mode (USER,DEMONSTRATION,BENCHMARK): ";
    std::string int_mode;
    std::cin >> int_mode;
    std::cout << std::endl;

    if (int_mode == "USER"){
        interaction(queue);
    } else if (int_mode == "DEMONSTRATION"){
        demonstration(queue);
    } else if (int_mode == "BENCHMARK"){
        benchmark(queue);
    }
}

/*
int main() {

    std::string mode = "NO MODE";
    while (mode != "EXIT") {
        std::cout << "Choose mode (LIST, ARRAY, VECTOR, or EXIT to exit): ";
        std::cin >> mode;
        std::cout << std::endl;
        if (mode == "LIST") {
            ListQueue<Point> queue;

            operations(queue);

        } else if (mode == "ARRAY") {
            ArrayQueue<Point> queue;

            operations(queue);

        } else if (mode == "VECTOR") {
            std::vector<Point> queue;

            operations(queue);
        }
    }
    return 0;
}
*/