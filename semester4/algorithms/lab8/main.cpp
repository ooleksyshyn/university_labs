#include "fibbonaci.hpp"
#include "struct.hpp"


#include <iostream>
#include <array>


using namespace lab;

int main () {

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

    FibonacciHeap<Company> fibonacci_heap;

    for(auto i : companies) {
        fibonacci_heap.insert(i);
    }

    for(int i = 0; i < 3; ++i){
        std::cout << "Min: " << fibonacci_heap.getMinimum() << std::endl;

        fibonacci_heap.removeMinimum();
    }


    return 0;
}