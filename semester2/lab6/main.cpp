#include "point.h"
#include "list.h"
#include "array.h"
#include "bin_tree.h"
#include "avl.h"
#include "two_three_tree.h"
#include "test_runner.h"
#include <iostream>

void two3nodeInteraction(){
    two3Tree tree1;

    int operation_index = -1;
    Point data;

    while (operation_index != 0)
    {

        std::cout << "\nChoose operation : ";
        std::cout << "\n1 - add \n2 - delete \n3 - search for point \n4 - search in point range\n"
                     "5 - print\n6 - generate random\n0 - exit\n\n";
        std::cout << "Enter number of an option: ";
        std::cin >> operation_index;

        if (operation_index == 1){
            std::cout << "\nEnter the point to be added: ";
            std::cin  >> data;

            tree1.add(data);
        }

        else if (operation_index == 2){
            std::cout << "\nEnter the point to be deleted: ";
            std::cin >> data;

            tree1.deleteNode(data);
        }

        else if (operation_index == 3){
            std::cout << "\nEnter the point element which you want to search: ";
            std::cin  >> data;

            tree1.searchFor(data);
        }

        else if (operation_index == 4){
            std::cout << "\nEnter the points range which you want to search:\n";
            std::cout << "Left boundary: ";
            Point left, right;
            std::cin >> left;
            std::cout << "\nRight boundary: ";
            std::cin >> right;

            tree1.searchForRange(left, right);
        }

        else if (operation_index == 5){
            tree1.printTree();
        }

        else if (operation_index == 6){
            std::cout << "\nEnter the amount of elements to be generated : ";
            int n;
            std::cin >> n;
            tree1.add_random(n);
        }
    }
}


template <typename T>
void interaction(T& list){
    int operation_index = -1;
    while (operation_index != 0){
        std::cout << "\nChoose operation:\n"
                     "1 - create empty\n"
                     "2 - create\n"
                     "3 - add\n"
                     "4 - print\n"
                     "5 - delete\n"
                     "6 - search point\n"
                     "7 - search point range\n"
                     "8 - generate random\n"
                     "0 - exit\n";

        std::cout << "Enter option number: ";

        std::cin >> operation_index;

        std::cout << std::endl;

        if (operation_index == 1) {  //create empty
            list = create_empty(list);
        }

        if (operation_index == 2) {  //create
            std::cout << "\nEnter point`s coordinates (3 real numbers): ";
            double x, y, z;
            std::cin >> x >> y >> z;
            list = create(Point(x, y, z), list);
        }

        if (operation_index == 3) {  //add
            std::cout << "\nEnter point to add(3 real numbers):";
            double x, y, z;
            std::cin >> x >> y >> z;
            add(list, Point(x, y, z));
        }

        if (operation_index == 4) {   //print
            print(list);
        }

        if (operation_index == 5) {   //delete
            std::cout << "\nEnter coordinates of point which you want to delete: ";
            double x, y, z;
            std::cin >> x >> y >> z;
            delete_(list, Point(x, y, z));
        }

        if (operation_index == 6) {   //search point
            std::cout << "\nEnter coordinates of point to search: ";
            double x, y, z;
            std::cin >> x >> y >> z;
            search(list, Point(x, y, z));
        }

        if (operation_index == 7) {
            std::cout << "\nEnter coordinates of points to search:\n"
                         "Left bounder: ";
            double x_l, y_l, z_l;
            std::cin >> x_l >> y_l >> z_l;
            std::cout << "\nRight bounder: ";
            double x_r, y_r, z_r;
            std::cin >> x_r >> y_r >> z_r;
            search(list, Point(x_l, y_l, z_l), Point(x_r, y_r, z_r));
        }

        if (operation_index == 8){
            std::cout << "\nEnter amount of data to add: ";
            int n;
            std::cin >> n;
            add_random(list, n);
        }
    }
}


void add_list(int n){
    Node* list1 = create_empty(list1);

    add_random(list1, n);
    delete list1;
}
void add_array(int n){
    Array list1 = create_empty(list1);

    add_random(list1, n);
}
void add_bin_tree(int n){
    bin_tree* list1 = create_empty(list1);

    add_random(list1, n);
}
void add_avl(int n){
    AVL* list1 = create_empty(list1);

    add_random(list1, n);
}
void add_23(int n){
    two3Tree tree;
    tree.add_random(n);
}

void generate_list(Node* list1, int n){
    int pow = log10(n);
    pow = std::pow(10, pow);
    add_random(list1, pow);
}
void delete_list(Node* list){
    delete_(list, Point(1000, 0, 0));
}
void search_list(Node* list){
    search(list, Point(1000, 0, 0));
}

void generate_array(Array list1, int n){
    int pow = log10(n);
    pow = std::pow(10, pow);
    add_random(list1, pow);
}
void delete_array(Array list){
    delete_(list, Point(1000, 0, 0));
}
void search_array(Array list){
    search(list, Point(1000, 0, 0));
}

void generate_bin_tree(bin_tree* list, int n){
    int pow = log10(n);
    pow = std::pow(10, pow);
    add_random(list, pow);
}
void delete_bin_tree(bin_tree* list){
    delete_(list, Point(1000, 0, 0));
}
void search_bin_tree(bin_tree* list){
    search(list, Point(1000, 0, 0));
}

void generate_avl(AVL* tree, int n){
    int pow = log10(n);
    pow = std::pow(10, pow);
    add_random(tree, n);
}
void delete_avl(AVL* tree){
    delete_(tree, Point(1000, 0, 0));
}
void search_avl(AVL* tree){
    quick_search(tree, Point(1000, 0, 0));
}

void generate_23(two3Tree tree, int n){
    int pow = log10(n);
    pow = std::pow(10, pow);
    tree.add_random(n);
}
void delete_23(two3Tree tree){
    tree.deleteNode(Point(1000, 0, 0));
}
void search_23(two3Tree tree){
    tree.searchFor(Point(1000, 0, 0));
}


void demonstration();
void benchmark();


int main() {

    std::cout << "For all choices enter the option number";
    int mode = -1;
    while(mode != 0){
        std::cout << "\nChoose mode:\n"
                     "1 - Interaction\n"
                     "2 - Demonstration\n"
                     "3 - Benchmark\n"
                     "0 - exit\n";
        std::cout << "Enter option number: ";
        std::cin >> mode;
        if (mode == 2) demonstration();
        if (mode == 3) benchmark();
        if (mode == 1) {
            int n = -1;
            while (n != 0) {
                std::cout << "Choose object type:\n";
                std::cout << "1 - Array\n2 - List\n3 - Binary tree\n4 - AVL tree\n5 - two-three tree\n0 - exit\n"
                             "Your choice: ";
                std::cin >> n;
                if (n == 1) {
                    Array a = create_empty(a);
                    print(a);
                    interaction(a);
                }
                if (n == 2) {
                    Node* a = create_empty(a);
                    interaction(a);
                }
                if (n == 3) {
                    bin_tree* a = create_empty(a);
                    interaction(a);
                }
                if (n == 4) {
                    AVL* a = create_empty(a);
                    interaction(a);
                }
                if (n == 5) {
                    two3nodeInteraction();
                }
            }
        }
    }
    return 0;
}


void demonstration(){
    Array list1 = create_empty(list1);
    Node* list2 = create_empty(list2);
    bin_tree* list3 = create_empty(list3);
    AVL* list4 = create_empty(list4);
    two3Tree list5;

    add_random(list1, 10);
    add_random(list2, 10);
    add_random(list3, 10);
    add_random(list4, 10);
    list5.add_random(10);

    add(list1, Point(1, 2, 3));
    add(list2, Point(1, 2, 3));
    add(list3, Point(1, 2, 3));
    add(list4, Point(1, 2, 3));
    list5.add(Point(1, 2, 3));

    std::cout << "Array list:\n";
    print(list1);
    std::cout << "\nList list:\n";
    print(list2);
    std::cout << "\nBinary tree list:\n";
    print(list3);
    std::cout << "\nAVL tree list:\n";
    print(list4);
    std::cout << "\nTwo-three tree list:\n";
    list5.printTree();

    std::cout << "\n\nSearch elements (Point(1, 2, 3)):\n\n";

    std::cout << "Array list:\n";
    search(list1, Point(1, 2, 3));

    std::cout << "\nList list:\n";
    search(list2, Point(1, 2, 3));

    std::cout << "\nBinary tree list:\n";
    search(list3, Point(1, 2, 3));

    std::cout << "\nAVL tree list:\n";
    search(list4, Point(1, 2, 3));

    std::cout << "\nTwo-three tree list:\n";
    list5.searchFor(Point(1, 2, 3));


    std::cout << "\n\nDelete elements (Point(1, 2, 3)):\n\n";

    std::cout << "Array list:\n";
    delete_(list1, Point(1, 2, 3));
    print(list1);
    std::cout << "\nList list:\n";
    delete_(list2, Point(1, 2, 3));
    print(list2);
    std::cout << "\nBinary tree list:\n";
    delete_(list3, Point(1, 2, 3));
    print(list3);
    std::cout << "\nAVL tree list:\n";
    delete_(list4, Point(1, 2, 3));
    print(list4);
    std::cout << "\nTwo-three tree list:\n";
    list5.deleteNode(Point(1, 2, 3));
    list5.printTree();

    std::cout << "\n\nSearch for range of elements (Point(0, 0, 0) -- Point(300, 0, 0):\n\n";

    std::cout << "Array list:\n";
    search(list1, Point(0, 0, 0), Point(300, 0, 0));

    std::cout << "\nList list:\n";
    search(list2, Point(0, 0, 0), Point(300, 0, 0));

    std::cout << "\nBinary tree list:\n";
    search(list3, Point(0, 0, 0), Point(300, 0, 0));

    std::cout << "\nAVL tree list:\n";
    search(list4, Point(0, 0, 0), Point(300, 0, 0));

    std::cout << "\nTwo-three tree list:\n";
    list5.searchForRange(Point(1, 2, 3), Point(300, 0, 0));


    std::cout << "\n\nAccess to elements (print first coordinate):\n\n";

    std::cout << "Array list:\n";
    access(list1, [](Point& p){std::cout << p.x << std::endl;});

    std::cout << "\nList list:\n";
    access(list2, [](Point& p){std::cout << p.x << std::endl;});

    std::cout << "\nBinary tree list:\n";
    access(list3, [](Point& p){std::cout << p.x << std::endl;});

    std::cout << "\nAVL tree list:\n";
    access(list4, [](Point& p){std::cout << p.x << std::endl;});

    std::cout << "\nTwo-three tree list:\n";
    list5.access([](Point& P){std::cout << P.x << std::endl;});

}
void benchmark(){

    TimeKeeper test_add(std::cout);
    TimeKeeper test_delete(std::cout);
    TimeKeeper test_search(std::cout);

    Node* list = create_empty(list);
    Array array = create_empty(array);
    bin_tree* binTree = create_empty(binTree);
    AVL* avl = create_empty(avl);
    two3Tree tree23;

    //TEST_COMPARISON(test_add, add_list, 10)
    //TEST_COMPARISON(test_add, add_array, 10)
    //TEST_COMPARISON(test_add, add_bin_tree, 10)
    //TEST_COMPARISON(test_add, add_avl, 10)
    //TEST_COMPARISON(test_add, add_23, 10)


    //TEST_COMPARISON_GENERATED(test_delete, delete_list, generate_list, list, 0.1)
    //TEST_COMPARISON_GENERATED(test_delete, delete_array, generate_array, array, 0.01)
    //TEST_COMPARISON_GENERATED(test_delete, delete_bin_tree, generate_bin_tree, binTree, 1)
    //TEST_COMPARISON_GENERATED(test_delete, delete_avl, generate_avl, avl, 1)
    //TEST_COMPARISON_GENERATED(test_delete, delete_23, generate_23, tree23, 1)

    Node* list1 = create_empty(list);
    Array array1 = create_empty(array);
    bin_tree* binTree1 = create_empty(binTree);
    AVL* avl1 = create_empty(avl);
    two3Tree tree23_1;

    //TEST_COMPARISON_GENERATED(test_search, search_list, generate_list, list1, 10)
    TEST_COMPARISON_GENERATED(test_search, search_array, generate_array, array1, 2)
    //TEST_COMPARISON_GENERATED(test_search, search_bin_tree, generate_bin_tree, binTree1, 2)
    //TEST_COMPARISON_GENERATED(test_search, search_avl, generate_avl, avl1, 2)
    //TEST_COMPARISON_GENERATED(test_search, search_23, generate_23, tree23_1, 2)
}