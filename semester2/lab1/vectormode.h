#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "structures.h"
#include "UserInteraction.h"
#include "Demonstration.h"


void Use_Vector(){
    std::cout << "Type Test Mode (USER, DEMONSTRATION OR EXIT): ";
    std::string TestMode;
    std::cin >> TestMode;
    if(TestMode == "EXIT") return;
    if(TestMode == "USER") UserInteraction(); else
    if(TestMode == "DEMONSTRATION") Demonstration();
}