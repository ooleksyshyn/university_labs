#pragma once

#include "structures.h"
#include "userfileinteraction.h"
#include "filedemonstration.h"

void Use_File() {
    std::cout << "Type Test Mode (USER, DEMONSTRATION OR EXIT): ";
    std::string TestMode;
    std::cin >> TestMode;
    if(TestMode == "EXIT") return;
    if(TestMode == "USER") UserFileInteraction();  else
    if(TestMode == "DEMONSTRATION") FileDemonstration();
}