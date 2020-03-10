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

    RBtree<Company> obj;

    for (auto company : companies){
        obj.insert(company);
    }


    obj.disp();

    return 0;
}