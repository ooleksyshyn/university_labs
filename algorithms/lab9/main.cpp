#include <iostream>
#include <array>


#include "graph.hpp"
#include "struct.hpp"


using namespace lab;


int main(){
    std::array<Company, 3> companies = {Company{"Google",
                                                        {Department{"technical",
                                                                    {Employee{"Oleksii"},
                                                                     Employee{"Ostap"},
                                                                     Employee{"Daniil"}
                                                                    }}
                                                        }},
                                                Company{"Facebook",
                                                        {Department{"Technical",
                                                                    {Employee{"Maks"},
                                                                     Employee{"Den"}}},
                                                         Department{"media",
                                                                    {Employee{"Olenka"}}}
                                                        }},
                                                Company{"Amazon",
                                                        {Department{"lead"}}}
    };


    Graph<Company> graph{companies[0], companies[1], companies[2], companies[0]};

    graph.add_edge(0, 3);
    graph.add_edge(0, 2);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(3, 0);
    graph.add_edge(2, 0);
    graph.add_edge(1, 0);
    graph.add_edge(2, 1);

    const auto res = johnson_paths(graph);

    for (auto i = 0; i < res.size(); ++i) {
        std::cout << "Path from dir " << graph.vertices()[i] << " to :\n";
        for (auto j = 0; j < res[i].size(); ++j) {
            std::cout << "\t" << graph.vertices()[j] << " : " << res[i][j] << "\n";
        }
        std::cout << "\n";
    }
}