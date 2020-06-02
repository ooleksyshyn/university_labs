#pragma once


#include "datetime.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

enum file_node_type {folder, file};

template <class TREE>
TREE* GetByPath(TREE* tree, std::vector<int> path);


struct file_tree{

    file_node_type type;
    int size;
    Date_Time date_time;
    std::string name;
    file_tree* father;
    std::vector<file_tree*> children;
};


file_tree* create_file_tree(std::string name, int size, Date_Time time, file_node_type type){
    auto file = new file_tree;
    file->type = type;
    file->father = nullptr;
    file->name = name;
    file->size = size;
    file->date_time = time;
    return file;
}


std::vector<std::string> GetFilePath(file_tree* element, std::vector<std::string> CurrentPath){
    if (element == nullptr) return {};

    if (element->father == nullptr) return CurrentPath;

    file_tree* previous = element->father;


    CurrentPath.insert(CurrentPath.begin(), previous->name);
    return GetFilePath(previous, CurrentPath);

    return CurrentPath;
}


void add_to_file_tree(file_tree* father, std::string name, int size, Date_Time time, file_node_type type){
    file_tree* new_file = create_file_tree(name, size, time, type);
    if (father->type == file) {
        std::cout << "Can`t add file or folder into file\n";
    } else {
        father->children.push_back(new_file);
        new_file->father = father;
    }
}


void add_to_file_tree(file_tree* tree, std::string name, int size, Date_Time time,
        file_node_type type, std::vector<int> path){

    if (GetByPath(tree, path)){
        file_tree *previous = GetByPath(tree, move(path));
        if (previous->type == file) {
            std::cout << "Can`t add file or folder into file\n";
        } else {
            add_to_file_tree(previous, name, size, time, type);
        }
    }
}


void add_to_file_tree(file_tree* father, file_tree* child){
    if (father->type == file){
        std::cout << "Can`t add file or folder into file\n";
    } else {
        father->children.push_back(child);
        child->father = father;
    }
}


void print_node(file_tree* tree){
    std::cout << "~";
    for (auto& i : GetFilePath(tree, {})) {
        std::cout << "/" << i;
    }
    if (tree->type == folder) {
        std::cout << " -- folder ";
    } else std::cout << " -- file ";
    std::cout << tree->name << " " << tree->size << "KB " << tree->date_time << std::endl;
}


void print_file_tree(file_tree* tree){
    if (tree == nullptr) return;

    print_node(tree);


    for (auto i : tree->children){
        print_file_tree(i);
    }
}


int Size(file_tree* tree){
    int size = tree->size;
    for (file_tree* child : tree->children){
        size = size + Size(child);
    }

    return size;
}


std::pair<int, int> catalogs_files_amount(file_tree* tree){
    if (tree->children.empty()){
        if (tree->type == folder) return std::pair(1, 0);
        if (tree->type == file) return std::pair(0, 1);
    }

    int files = 0;
    int catalogs = 1;

    for (auto child : tree->children){
        auto child_catalogs_files = catalogs_files_amount(child);

        catalogs += child_catalogs_files.first;
        files += child_catalogs_files.second;
    }

    return std::make_pair(catalogs, files);
}


template <typename Function>
file_tree* filter(file_tree* tree, Function func){
    auto result = create_file_tree(tree->name, tree->size, tree->date_time, tree->type);

    for (auto child : tree->children){
        if (filter(child, func)){
            add_to_file_tree(result, child);
        }
    }

    if (tree->type == file && func(tree)) return result;

    if (tree->type == folder && result->children.empty()) return nullptr;

    if (tree->type == file && !func(tree)) return nullptr;

    return result;
}


file_tree* search_latest(file_tree* tree){
    file_tree* latest_change = tree;
    for (auto folder : tree->children){
        if (search_latest(folder)->date_time > latest_change->date_time){
            latest_change = search_latest(folder);
        }
    }
    return latest_change;
}


file_tree* search_first(file_tree* tree){
    file_tree* first_change = tree;
    for (auto folder : tree->children){
        if (first_change->date_time > search_first(folder)->date_time){
            first_change = search_first(folder);
        }
    }
    return first_change;
}