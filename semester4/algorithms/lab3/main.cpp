#include "struct.hpp"
#include "SplayTree.hpp"

#include <iostream>
#include <array>

int main() {

    using namespace lab;
    SplayTree<Department> tree;

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

    std::cout << "Departments to insert: \n";

    for (const auto& company : companies) {
        for (const auto& department : company.departments) {
            std::cout << department.name << ' '
                      << "size: " << department.size() << std::endl;
            tree.insert(department);
        }
    }

    std::cout << "\n\nIterating in tree after insertion :\n";
    for (const auto& i : tree) {
        std::cout << i.name << ' '
                  << "size: " << i.size() << std::endl;
    }

    std::cout << "\n\nErasing file " << companies[0].departments[0].name << "\n";

    tree.erase(companies[0].departments[0]);

    std::cout << "\nIterating in tree after erasing :\n";
    for (const auto& i : tree) {
        std::cout << i.name << ' '
                  << "size: " << i.size() << std::endl;
    }
    return 0;
}