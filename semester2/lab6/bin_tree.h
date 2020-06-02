#pragma once


#include "point.h"
#include <vector>
#include <functional>


using Lambda = std::function<void(Point&)>;
using Fi = std::function<bool(Point)>;


template <class TREE>
std::vector<int> GetPath(TREE* element, std::vector<int> CurrentPath){
    if (element == nullptr) return {};

    if (element->father == nullptr) return CurrentPath;

    TREE* previous = element->father;

    for (int i = 0; i < previous->children.size(); ++i){
        if (previous->children[i] == element){
            CurrentPath.insert(CurrentPath.begin(), i);
            return GetPath(previous, CurrentPath);
        }
    }
    return CurrentPath;
}


struct bin_tree;


void delete_data(bin_tree* tree);


struct bin_tree{
    Point data;

    bin_tree* father;
    std::vector<bin_tree*> children;
    bool empty;

    ~bin_tree(){
        for (auto& i : children){
            delete i;
        }
    }
};


bin_tree* create_empty(bin_tree*){
    auto* tree = new bin_tree;


    tree->father = nullptr;
    tree->children.push_back(nullptr);
    tree->children.push_back(nullptr);
    tree->empty = true;
    return tree;
}


bin_tree* create(Point Data, bin_tree*){
    auto tree = new bin_tree;
    tree->data = Data;
    tree->father = nullptr;
    tree->empty = false;
    return tree;
}


void add(bin_tree* tree, Point data){
    if (tree->empty){
        tree->data = data;
        tree->empty = false;
        return;
    }
    if (tree->children.empty()){
        bin_tree* nulltree = nullptr;

        tree->children.push_back(nulltree);
        tree->children.push_back(nulltree);

        if (tree->data > data){
            tree->children[0] = create(data, tree);
            tree->children[0]->father = tree;
        } else{
            tree->children[1] = create(data, tree);
            tree->children[1]->father = tree;
        }
        return;
    }

    if (tree->data > data && tree->children[0] == nullptr){
        tree->children[0] = create(data, tree);
        tree->children[0]->father = tree;
        return;
    }

    if (tree->data <= data && tree->children[1] == nullptr){
        tree->children[1] = create(data, tree);
        tree->children[1]->father = tree;
        return;
    }

    if (tree->data > data){
        add(tree->children[0], data);
    } else{
        add(tree->children[1], data);
    }
}


void access(bin_tree* tree, Lambda lambda){
    if (tree->children.size() > 0) {
        if (tree->children[0] != nullptr) access(tree->children[0], lambda);
    }
    lambda(tree->data);
    if (tree->children.size() > 1) {
        if (tree->children[1] != nullptr) access(tree->children[1], lambda);
    }
}


void print_node(bin_tree* tree){
    std::cout << "{ ";
    for (auto i : GetPath(tree, {})){
        std::cout << i << " ";
    }
    std::cout << "} -- " << tree->data << std::endl;
}


void print(bin_tree* tree){
    if (tree == nullptr) return;
    if (tree->empty) {
        std::cout << "Tree is empty";
        return;
    }
    if (!tree->children.empty()) print(tree->children[0]);
    print_node(tree);
    if (tree->children.size() > 1) print(tree->children[1]);
}


void add(bin_tree* tree, bin_tree* deleted, Fi fi){
    if (deleted == nullptr) return;
    if (deleted->children.size() > 0){
        add(tree, deleted->children[0], fi);
    }
    if (fi(deleted->data)) {
        add(tree, deleted->data);
    }
    if (deleted->children.size() > 1){
        add(tree, deleted->children[1], fi);
    }
}


void delete_data(bin_tree* tree){
    if (tree->children.size() > 0){
        if (tree->children[0] != nullptr)
            delete tree->children[0];
    }

    if (tree->children.size() > 1){
        if (tree->children[1] != nullptr)
            delete tree->children[1];
    }

    delete tree;
}


void delete_(bin_tree* tree, Point comparator){
    if (tree->father == nullptr && tree->data == comparator){
        tree->empty = true;
        bin_tree* left = nullptr;
        bin_tree* right = nullptr;
        if (tree->children.size() > 0){
            left = tree->children[0];
        }
        if (tree->children.size() > 1){
            right = tree->children[1];
        }
        tree->children = std::vector<bin_tree*>(0);
        if (left != nullptr) {
            add(tree, left, [comparator](Point p){ return p != comparator;});
            delete_data(left);
        }
        if (right != nullptr) {
            add(tree, right, [comparator](Point p){ return p != comparator;});
            delete_data(right);
        }
    } else if (tree->data == comparator){
        bin_tree* left = nullptr;
        bin_tree* right = nullptr;
        if (tree->children.size() > 0){
            left = tree->children[0];
        }
        if (tree->children.size() > 1){
            right = tree->children[1];
        }
        tree->children = std::vector<bin_tree*>(0);
        for (auto& i : tree->father->children){
            if (i == tree){
                i = nullptr;
            }
        }
        if (left != nullptr) {
            add(tree->father, left, [comparator](Point p){ return p != comparator;});
            delete_data(left);
        }
        if (right != nullptr) {
            add(tree->father, right, [comparator](Point p){ return p != comparator;});
            delete_data(right);
        }
        delete tree;
    } else if (tree->data > comparator){
        if (tree->children.size() > 0){
            if (tree->children[0] != nullptr){
                delete_(tree->children[0], comparator);
            }
        }
    } else {
        if (tree->children.size() > 1){
            if (tree->children[1] != nullptr){
                delete_(tree->children[1], comparator);
            }
        }
    }
}


void search(bin_tree* tree, Point comparator){
    if (tree == nullptr) return;
    if (tree->children.empty()){
        if (tree->data == comparator) print_node(tree);
        return;
    }

    if (tree->children.size() == 1){
        if (tree->children[0] != nullptr){
            if (tree->children[0]->data > tree->data){
                if (tree->data == comparator) print_node(tree);
                if (tree->data <= comparator) search(tree->children[0], comparator);
                return;
            } else {
                if (tree->data >= comparator) search(tree->children[0], comparator);
                if (tree->data == comparator) print_node(tree);
                return;
            }
        }
    }

    if (tree->data >= comparator) search(tree->children[0], comparator);
    if (tree->data == comparator) print_node(tree);
    if (tree->data <= comparator) search(tree->children[1], comparator);

}


void search(bin_tree* tree, Point left, Point right){
    if (tree == nullptr) return;

    if (tree->children.empty()) {
        if (tree->data >= left && tree->data <= right) print_node(tree);
        return;
    }

    if (tree->children.size() == 1){
        if (tree->children[0] != nullptr){
            if (tree->children[0]->data > tree->data){
                if (tree->data >= left && tree->data <= right) {
                    print_node(tree);
                    search(tree->children[0], left, right);
                } else if (tree->data < right){
                    search(tree->children[0], left, right);
                }
                return;
            } else {
                if (tree->data >= left && tree->data <= right) {
                    search(tree->children[0], left, right);
                    print_node(tree);
                } else if (tree->data < left){
                    search(tree->children[0], left, right);
                }
                return;
            }
        }
    }

    if (tree->data >= left) search(tree->children[0], left, right);
    if (tree->data >= left && tree->data <= right) print_node(tree);
    if (tree->data <= right) search(tree->children[1], left, right);
}


void add_random(bin_tree* tree, int n){
    for (int i = 0; i < n; ++i){
        add(tree, Point(0, 1000));
    }
}