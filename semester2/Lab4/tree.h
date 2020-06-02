#pragma once


#include <vector>
#include <iostream>
#include <string>


struct Tree{
    int data;


    Tree* father;


    std::vector<Tree*> children;
};


Tree* create(){
    Tree* tree = new Tree;

    tree->data = 0;
    tree->father = nullptr;
    return tree;


}


Tree* create(int Data){
    Tree* tree = new Tree;
    tree->data = Data;
    tree->father = nullptr;
    return tree;
}


void add_child(Tree* parent, int Data){
    Tree* new_child = create(Data);

    new_child->father = parent;

    parent->children.push_back(new_child);
}


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


template <class TREE>
TREE* GetByPath(TREE* tree, std::vector<int> path){

    int counter = 0;
    while (counter < path.size()) {
        if (tree->children.size() < path[counter] + 1){
            std::cout << "Invalid path\n";
            return nullptr;
        }

        tree = tree->children[path[counter]];
        ++counter;
    }

    return tree;
}


void add_child(Tree* tree, int Data, std::vector<int> path){

    if (GetByPath(tree, path)){
        Tree* previous = GetByPath(tree, path);
        add_child(previous, Data);
    }
}


template <class TREE>
int max_width(TREE* tree){
    if (tree == nullptr) return 0;
    int max = 0;
    for (auto i : tree->children){
        if (max_width(i) > max){
            max = max_width(i);
        }
    }

    if (std::to_string(tree->children.size()).size() > max){
        max = std::to_string(tree->children.size()).size();
    }
    return max;
}


template <class TREE>
void print_tree(TREE* tree, int max_width){

    if (tree == nullptr) return;
    std::cout << "{";
    std::vector<int> path = GetPath(tree, {});

    for (int i = 0; i < path.size(); ++i){
        if (i == path.size() - 1) {
            std::cout << std::string(max_width - std::to_string(path[i]).size(),' ');
            std::cout << path[i];
        } else {
            std::cout << std::string(max_width - std::to_string(path[i]).size(),' ') << path[i] << ", ";
        }
    }


    std::cout << "} -- " << tree->data << std::endl;

    for (auto child : tree->children){
        print_tree(child, max_width);
    }
}


template <class TREE>
TREE* delete_elements(TREE* element){
    if (element->father == nullptr){
        std::cout << "Can`t delete the root of the tree";
        return nullptr;
    }

    for (int i = 0; i < element->father->children.size(); ++i){
        if (element->father->children[i] == element){
            element->father->children.erase(element->father->children.begin() + i);
        }
    }
    return element;
}


template <class TREE>
TREE* delete_elements(TREE* tree, std::vector<int> path){
    if (GetByPath(tree, path)){
        return delete_elements(GetByPath(tree, path));
    } else {
        return nullptr;
    };
}


struct bin_tree{
    int data;

    bin_tree* father;
    std::vector<bin_tree*> children;
};


bin_tree* create_bin(){
    auto* tree = new bin_tree;

    tree->data = 0;
    tree->father = nullptr;
    tree->children.push_back(nullptr);
    tree->children.push_back(nullptr);
    return tree;
}


bin_tree* create_bin(int Data){
    auto tree = new bin_tree;
    tree->data = Data;
    tree->father = nullptr;
    return tree;
}


void add_data(bin_tree* tree, int data){
    if (tree->children.empty()){
        bin_tree* nulltree = create_bin();
        nulltree = nullptr;

        tree->children.push_back(nulltree);
        tree->children.push_back(nulltree);

        if (tree->data > data){
            tree->children[0] = create_bin(data);
            tree->children[0]->father = tree;
        } else{
            tree->children[1] = create_bin(data);
            tree->children[1]->father = tree;
        }
        return;
    }

    if (tree->data > data & tree->children[0] == nullptr){
        tree->children[0] = create_bin(data);
        tree->children[0]->father = tree;
        return;
    }

    if (tree->data <= data & tree->children[1] == nullptr){
        tree->children[1] = create_bin(data);
        tree->children[1]->father = tree;
        return;
    }

    if (tree->data > data){
        add_data(tree->children[0], data);
    } else{
        add_data(tree->children[1], data);
    }
}


std::vector<int> flatten(bin_tree* tree){
    if (tree == nullptr) return {};
    std::vector<int> presentation = {tree->data};

    if (tree->children.empty()){
        return presentation;
    }

    if (tree->children.size() == 1){
        for (auto i : flatten(tree->children[0])){
            presentation.push_back(i);
        }
        return presentation;
    }


    for (auto i : flatten(tree->children[0])){
        presentation.push_back(i);
    }

    for (auto i : flatten(tree->children[1])){
        presentation.push_back(i);
    }
    return presentation;
}