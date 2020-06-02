#pragma once

#include "structures.h"
#include "userbinfileinteraction.h"
#include "binfiledemonstration.h"

void Use_Bin_File(){
    std::cout << "Type Test Mode (USER, DEMONSTRATION OR EXIT): ";
    std::string TestMode;
    std::cin >> TestMode;
    if(TestMode == "EXIT") return;
    if(TestMode == "USER") User_Bin_File_Interaction();
    if(TestMode == "DEMONSTRATION") Bin_File_Demonstration();
}