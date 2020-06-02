#include <iostream>
#include <string>
#include <vector>
#include "list.h"

void demonstration();
void interaction();

int main() {

    std::string command = " ";
    while (command != "EXIT") {
        std::cout << "CHOOSE MODE (USER, DEMONSTRATION OR EXIT): ";
        std::cin >> command;

        if (command == "DEMONSTRATION"){
            demonstration();

        } else if (command == "USER"){
            interaction();
        }

    }
    return 0;
}

void demonstration(){
    Node<int>* L1 = create_empty(0);
    Node<int>* L2 = create_empty(0);
    Node<int>* L3 = create_empty(0);

    push_back(L1, 1);
    push_back(L1, 2);
    push_back(L1, 3);
    push_back(L1, 4);

    push_back(L2, 1);
    push_back(L2, 4);
    push_back(L2, 6);

    push_back(L3, 4);
    push_back(L3, 6);
    push_back(L3, 7);
    push_back(L3, 8);

    std::cout << "List 1: " ;
    PrintList(L1);
    std::cout << std::endl;

    std::cout << "List 2: " ;
    PrintList(L2);
    std::cout << std::endl;

    std::cout << "List 3: " ;
    PrintList(L3);
    std::cout << std::endl;

    std::cout << "Intersection of List 1 and List 2: ";
    PrintList(intersect(L1,L2));
    std::cout << std::endl;

    std::cout << "Union of List 2 and List 3: ";
    PrintList(unite(L2,L3));
    std::cout << std::endl;

    std::cout << "Complement of List 1 and List 3: ";
    PrintList(complement(L1,L3));
    std::cout << std::endl;

    std::cout << "Union of List 1 and ( intersection of List 2 and (complement of List 1 and List 3): ";
    PrintList(unite(L1,intersect(L2,complement(L1,L3))));
    std::cout << std::endl;
}


void interaction(){
    std::vector<Node<int>*> Lists;
    std::string command = " ";
    while (command != "EXIT") {
        std::cout << "Choose command from:\nADD_LIST\nINTERSECT_LISTS\nUNITE_LISTS\n" <<
                  "COMPLEMENT_LISTS\nPRINT_LIST\nPRINT_ALL_LISTS\nEXIT\n";
        std::cin >> command;
        std::cout << std::endl;

        if (command == "PRINT_ALL_LISTS"){
            if (Lists.empty()) {
                std::cout << "No lists created" << std::endl;
            }else {
                for (int i = 0; i < Lists.size(); ++i) {
                    std::cout << i+1 << " ";
                    PrintList(Lists[i]);
                    std::cout << std::endl;
                }
            }
        } else if (command == "PRINT_LIST"){
            int index;
            std::cout << "Which list to print: ";
            std::cin >> index;
            PrintList(Lists[index-1]);
            std::cout << std::endl;
        } else if (command == "COMPLEMENT_LISTS"){
            int index_1, index_2;
            std::cout << "Which lists to complement: ";
            std::cin >> index_1 >> index_2;
            std::cout << std::endl;
            PrintList(complement(Lists[index_1-1], Lists[index_2-1]));
            std::cout << std::endl;
        } else if (command == "UNITE_LISTS"){
            int index_1, index_2;
            std::cout << "Which lists to unite: ";
            std::cin >> index_1 >> index_2;
            std::cout << std::endl;
            PrintList(unite(Lists[index_1-1], Lists[index_2-1]));
            std::cout << std::endl;
        } else if (command == "INTERSECT_LISTS") {
            int index_1, index_2;
            std::cout << "Which lists to intersect: ";
            std::cin >> index_1 >> index_2;
            std::cout << std::endl;
            PrintList(intersect(Lists[index_1 - 1], Lists[index_2 - 1]));
            std::cout << std::endl;
        } else if (command == "ADD_LIST"){
            std::string add_method;
            std::cout << "How to add a list: \n" <<
                      "PRINT_NEW (only integers)\nINTERSECT_EXISTING\n" <<
                      "UNITE_EXISTING\nCOMPLEMENT_EXISTING\n";
            std::cin >> add_method;
            std::cout << std::endl;

            if (add_method == "INTERSECT_EXISTING"){
                int index_1, index_2;
                std::cout << "Which lists to intersect: ";
                std::cin >> index_1 >> index_2;
                std::cout << std::endl;
                Lists.push_back(intersect(Lists[index_1-1],Lists[index_2-1]));
            } else if (add_method == "UNITE_EXISTING"){
                int index_1, index_2;
                std::cout << "Which lists to unite: ";
                std::cin >> index_1 >> index_2;
                std::cout << std::endl;
                Lists.push_back(unite(Lists[index_1-1],Lists[index_2-1]));
            } else if (add_method == "COMPLEMENT_EXISTING"){
                    int index_1, index_2;
                    std::cout << "Which lists to complement: ";
                    std::cin >> index_1 >> index_2;
                    std::cout << std::endl;
                    Lists.push_back(complement(Lists[index_1-1],Lists[index_2-1]));
            } else if (add_method == "PRINT_NEW"){
                int amount;
                std::cout << "Print amount of elements: ";
                std::cin >> amount;
                std::cout << std::endl;

                Node<int>* new_list = create_empty(0);
                std::cout << "Print elements: ";
                for (int i = 0; i < amount; ++i){
                    int element;
                    std::cin >> element;
                    push_back(new_list, element);
                }
                Lists.push_back(new_list);
            }
        }
    }
}