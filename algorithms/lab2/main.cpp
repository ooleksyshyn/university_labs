#include "struct.hpp"
#include "RedBlackTree.hpp"

#include <iostream>
#include <string>
#include <array>

using namespace lab;

int main(){
    std::array companies = {Company{"Google",
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

    RedBlackTree<int> obj{10, 4, 5, 1, 3, 7, 9, 12, 2, -1, 0};

    std::cout << obj << std::endl << std::endl;

    obj.remove(9);

    std::cout << obj;

    return 0;
}