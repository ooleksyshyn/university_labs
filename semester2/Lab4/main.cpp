#include "tree.h"
#include "filesystem.h"

// 2, 3, 11, 13, 18, 21, 26


void demonstration();
void interaction();


int main(){

    std::string command = std::string();
    while (command != "EXIT"){
        std::cout << "Choose mode(INTERACTION, DEMONSTRATION, EXIT): ";
        std::cin >> command;
        if (command == "INTERACTION"){
            interaction();
        }
        if (command == "DEMONSTRATION"){
            demonstration();
        }
    }
    return 0;
}


void demonstration() {

    std::cout << "Working with tree with multiple nodes:\n";
    Tree* tree = create(5);

    add_child(tree, 1);
    add_child(tree, 2);
    add_child(tree->children[0], 3);
    add_child(tree->children[1], 4);

    add_child(tree, 5, {1, 0});

    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});
    add_child(tree, 5, {1, 0});

    add_child(tree, 7, {1});

    add_child(tree, 8, {0});

    add_child(tree, 9, {0});

    add_child(tree, 6, {1, 1});



    print_tree(tree, max_width(tree));

    std::cout << "\n\n" << "Deleted part:";

    print_tree(delete_elements(tree->children[1]->children[0]), max_width(tree->children[1]->children[0]));

    std::cout << "\n\n" << "Rest after deleting node {1}";

    print_tree(tree, max_width(tree));

    std::cout << "\n\nWorking with binary tree:\n";
    bin_tree* binTree = create_bin(5);

    add_data(binTree, 8);
    add_data(binTree, 2);
    add_data(binTree, 4);
    add_data(binTree, 1);
    add_data(binTree, 3);
    add_data(binTree, 6);
    add_data(binTree, 7);

    print_tree(binTree, max_width(binTree));


    std::cout << "Interpretation based on direct order: ";
    for (auto i : flatten(binTree)){
        std::cout << i << " ";
    }
    std::cout << "\n\n\n";

    std::cout << "Files system interpretation using trees:" << std::endl;
    file_tree* fileTree = create_file_tree("oleksii", 3, Date_Time(12, 12, 3, 5, 2019), folder);
    add_to_file_tree(fileTree, "CLionProjects", 5, Date_Time(12, 13, 3, 5, 2019), folder);


    add_to_file_tree(fileTree, "lab4.cpp", 150, Date_Time(16,34,3,5,2019), file, {0});

    add_to_file_tree(fileTree, "lab3a.cpp", 165, Date_Time(13,00,3,5,2019), file, {0});


    add_to_file_tree(fileTree, "PyCharmProjects", 8, Date_Time(12,00,1,1,2019), folder, {});
    add_to_file_tree(fileTree, "hello.py", 200, Date_Time(12,00,15,03,2019), file, {1});
    add_to_file_tree(fileTree, "main.py", 255, Date_Time(11,05,15,03,2019), file, {1});

    print_file_tree(fileTree);

    std::cout << "Total size: " << Size(fileTree) << "KB" << std::endl;

    std::cout << "catalogs: "  << catalogs_files_amount(fileTree).first <<
    " files: " << catalogs_files_amount(fileTree).second;
    std::cout << std::endl << std::endl;

    std::cout << "\nSearching for size >= 150KB:\n";
    auto fileTree2 = new file_tree;
    fileTree2 = filter(fileTree, [](file_tree* fileTree1){return fileTree1->size >= 150;});
    if (fileTree2){
        print_file_tree(fileTree2);
    } else {
        std::cout << "No searched items";
    }


    std::cout << "\nSearching for changing time later than 15.3.2019, 11:30 :\n";
    fileTree2 = filter(fileTree, [](file_tree* fileTree1){return fileTree1->date_time > Date_Time(0,0,1,3,2019);});
    if (fileTree2){
        print_file_tree(fileTree2);
    } else {
        std::cout << "No searched items";
    }

    std::cout << "\nLast change:";
    print_node(search_latest(fileTree));

    std::cout << "\nFirst change:";
    print_node(search_first(fileTree));
}


void interaction(){
    std::string command = std::string();
    while (command != "EXIT") {
        std::cout << "Choose what to test (TREE, BINTREE, FILETREE or EXIT): ";
        std::cin >> command;
        if (command == "TREE"){
            std::cout << "Insert integer for tree initialization: ";
            int initial;
            std::cin >> initial;
            Tree* tree = create(initial);
            std::string operation = std::string();
            while (operation != "EXIT"){
                std::cout << "Choose operation (ADD, PRINT, DELETE or EXIT): ";
                std::cin >> operation;
                if (operation == "PRINT"){
                    print_tree(tree, max_width(tree));
                }
                if (operation == "ADD"){
                    std::cout << "Insert integer value to add: ";
                    int new_value;
                    int pathlength;
                    std::cin >> new_value;
                    std::cout << "Insert length of path to elements node: ";
                    std::cin >> pathlength;
                    if (pathlength) {
                        std::cout << "Insert " << pathlength << " integers - path to elements node: ";
                    }
                    std::vector<int> path(pathlength);
                    for (auto& i : path){
                        std::cin >> i;
                    }
                    add_child(tree, new_value, path);
                }
                if (operation == "DELETE"){
                    int pathlength;
                    std::cout << "Insert length of path to node which you want to delete: ";
                    std::cin >> pathlength;
                    if (pathlength){
                        std::cout << "Insert " << pathlength << " integers - path to node: ";
                    }
                    std::vector<int> path(pathlength);
                    for (auto& i : path){
                        std::cin >> i;
                    }
                    auto deleted = delete_elements(tree, path);
                    std::cout << "Deleted tree:\n";
                    print_tree(deleted, max_width(deleted));
                }
            }
        }

        if (command == "BINTREE"){
            std::cout << "Insert integer for tree initialization: ";
            int initial;
            std::cin >> initial;
            bin_tree* tree = create_bin(initial);
            std::string operation = std::string();
            while (operation != "EXIT"){
                std::cout << "Choose operation (ADD, PRINT or EXIT): ";
                std::cin >> operation;
                if (operation == "PRINT"){
                    print_tree(tree, max_width(tree));
                }
                if (operation == "ADD"){
                    std::cout << "Insert integer value to add: ";
                    int new_value;
                    std::cin >> new_value;

                    add_data(tree, new_value);
                }
            }
        }

        if (command == "FILETREE"){
            std::cout << "Insert name, changing date(hh,mn,dd,mm,yy), size and type (file or folder)"
                         " for tree initialization: ";
            std::string name;
            int mn, hh, dd, mm, yy, size;
            file_node_type type;
            std::string Type;
            std::cin >> name >> hh >> mn >> dd >> mm >> yy >> size >> Type;
            if (Type == "folder"){
                type = folder;
            } else type = file;
            file_tree* tree = create_file_tree(name, size, Date_Time(hh, mn, dd, mm, yy), type);
            std::string operation = std::string();
            while (operation != "EXIT"){
                std::cout << "Choose operation (ADD, PRINT, LASTCHANGE, FIRSTCHANGE, SEARCH, STATISTICS or EXIT): ";
                std::cin >> operation;
                if (operation == "PRINT"){
                    print_file_tree(tree);
                }
                if (operation == "ADD"){
                    std::cout << "Insert name, changing date(hh,mn,dd,mm,yy) "
                                 "and size and type (file or folder) to add: ";
                    file_node_type type;
                    std::string Type;
                    std::cin >> name >> hh >> mn >> dd >> mm >> yy >> size >> Type;
                    if (Type == "folder"){
                        type = folder;
                    } else type = file;

                    std::cout << "Insert lenght of path to folder: ";
                    int pathlength;
                    std::cin >> pathlength;
                    std::vector<int> path(pathlength);

                    if (pathlength) {
                        std::cout << "Insert " << pathlength << " steps of path to folder: ";
                    }
                    for (auto& i : path){
                        std::cin >> i;
                    }

                    add_to_file_tree(tree, name, size, Date_Time(hh, mn, dd, mm, yy), type, path);
                }
                if (operation == "LASTCHANGE"){
                    print_node(search_latest(tree));
                }
                if (operation == "FIRSTCHANGE"){
                    print_node(search_first(tree));
                }
                if (operation == "SEARCH"){
                    std::cout << "Choose search parameter (NAME, LASTCHANGE, SIZE): ";
                    std::string search_parameter;
                    std::cin >> search_parameter;
                    if (search_parameter == "SIZE"){
                        std::cout << "Insert file size: ";
                        std::cin >> size;
                        if (!filter(tree, [size](file_tree* fileTree){return (fileTree->size == size);})){
                            std::cout << "No searched files\n";
                        }
                    }
                    if (search_parameter == "NAME"){
                        std::cout << "Insert beginning of name: ";
                        std::string beginning;
                        std::cin >> beginning;
                        file_tree* filtered_tree = new file_tree;
                        filtered_tree = filter(tree, [beginning](file_tree* fileTree){
                            std::string ending = beginning;
                            ++ending[ending.size()-1];
                            return (fileTree->name >= beginning && fileTree->name < ending);
                        });
                        if (!filtered_tree){
                            std::cout << "No searched files\n";
                        } else {
                            print_file_tree(filtered_tree);
                        }
                    }
                    if (search_parameter == "LASTCHANGE"){
                        std::cout << "Insert last change date: ";
                        std::cin >> hh >> mn >> dd >> mm >> yy;
                        Date_Time dateTime = Date_Time(hh, mn, dd, mm, yy);
                        file_tree* filtered_tree = new file_tree;
                        filtered_tree = filter(tree, [dateTime](file_tree* fileTree){
                            return fileTree->date_time == dateTime;});
                        if (!filtered_tree){
                            std::cout << "No searched files\n";
                        } else {
                            print_file_tree(filtered_tree);
                        }
                    }
                }
                if (operation == "STATISTIC"){
                    std::pair<int, int> stats = catalogs_files_amount(tree);
                    std::cout << "Total size: " << Size(tree) << "\nFolders: " << stats.first
                              << "\nFiles: " << stats.second << std::endl;
                }
            }
        }
    }
}