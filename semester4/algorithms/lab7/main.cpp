#include "bheap.hpp"
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


    BinomialHeap heap = {companies[0], companies[1], companies[2]};


    for (int i = 0; i < 3; ++i) {
        std::cout << "Min element in heap : " << heap.front() << std::endl;
        std::cout << "Erasing min element...\n\n";
        heap.pop();
    }
    return 0;
}