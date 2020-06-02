#include "struct.hpp"

#include "PersistentSet.hpp"

#include <iostream>
#include <string>

using namespace lab;

int main(){
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

    PersistentSet<Company> persistent_set;

    for (auto i : companies){
        persistent_set.add(i);
    }

    for(auto i : persistent_set.get_roots()){
        std::cout << i << std::endl;
    }

    return 0;
}