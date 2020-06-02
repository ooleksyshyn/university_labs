#include <iostream>
#include "struct.hpp"
#include "BplusTree.h"

using namespace lab;

int main() {
    BplusTree<Company> tree(1);
    std::initializer_list<Company> companies = {Company{"Google",
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

    for(auto i : companies){
        tree.insert(i);
    }

    tree.print();

    return 0;
}
