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


    RedBlackTree<Company> company_tree;

    for (auto company : companies){
        company_tree.insert(company);
    }

    for (int i = 0; i < company_tree.size(); ++i){
        std::cout << company_tree[i]->key << std::endl;
    }

    company_tree.remove(Company{"Google",
                                {Department{"technical",
                                            {Employee{"Oleksii"},
                                             Employee{"Ostap"},
                                             Employee{"Daniil"}
                                            }}
                                }}
                                );

    std::cout << company_tree << std::endl;



    // test on integers
    /*
    RedBlackTree<int> int_tree{10, 4, 5, 1, 3, 7, 9, 12, 2, -1, 0};

    std::cout << int_tree << std::endl << std::endl;

    int_tree.remove(9);

    std::cout << int_tree;

    for (int i = 0; i < int_tree.size(); ++i){
        std::cout << int_tree[i]->key << " ";
    }*/

    return 0;
}