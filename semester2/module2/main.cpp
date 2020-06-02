//Author: Oleksyshyn Oleksii
// Variant : 3, subvariant : 4

#include "workers.h"
#include "1.h"
#include "2.h"
#include "3.h"
#include "4.h"
#include <iostream>

int main() {

    task_1(); // contains only those constants, which were described is task 1

    task_2(); // has default argument exchange depth: 2

    task_3(); // has default argument number of vertex for which minimal distances are calculated: 0
              // has default rib existence maximum value: 4 * 10^(-37),
              // you should insert between 10^(-27) and 10^(-38) to get something useful

    task_4(); // has default parameters: search_value = 5 * 10(-35), accuracy = 2 * 10^(35),
              // but you can also insert this search parameters as function parameters

    return 0;
}