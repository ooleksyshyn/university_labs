#include "struct.hpp"
#include "hash.hpp"


#include <iostream>
#include <array>
#include <utility>


using namespace lab;

int main(){

    CPerfectHashTable<Company> table;

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


    std::vector<std::pair<std::string, Company>> data;

    data.reserve(companies.size());
    for (const auto& company : companies){
        data.emplace_back(company.name, company);
    }

    table.Calculate(data);

    std::cout <<*table.GetValue("Amazon") << " "
              << *table.GetValue("Google") << " "
              << *table.GetValue("Facebook");



    return 0;
}