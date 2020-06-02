#pragma once

#include "point.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <set>


using Lambda = std::function<void(Point&)>;


std::set<Point>& operator+(std::set<Point>& left, const std::set<Point>& right){
    for (auto i : right){
        left.insert(i);
    }
    return left;
}


struct AVL{
    Point data;
    AVL* left;
    AVL* right;
    int height;
    bool empty;
    ~AVL(){
        delete left;
        delete right;
    }
};


AVL* create_empty(AVL*){
    AVL* tree = new AVL;
    tree->height = 1;
    tree->empty = true;
    tree->right = nullptr;
    tree->left = nullptr;
    return tree;
}


AVL* create(Point data, AVL*){
    AVL* tree = new AVL;
    tree->height = 1;
    tree->empty = false;
    tree->left = nullptr;
    tree->right = nullptr;
    tree->data = data;
    return tree;
}


void update_height(AVL* tree){
    if (tree->right == nullptr && tree->left == nullptr){
        tree->height = 1;
    }

    if (tree->left == nullptr && tree->right != nullptr){
        tree->height = tree->right->height + 1;
    }
    if (tree->left != nullptr && tree->right == nullptr){
        tree->height = tree->left->height + 1;
    }

    if (tree->left != nullptr && tree->right != nullptr){
        tree->height = std::max(tree->left->height, tree->right->height) + 1;
    }
}


int height(AVL* tree){
    if (tree == nullptr) return 0;
    return tree->height;
}


void print(AVL* tree, std::vector<int> path){
    if (tree->left != nullptr){
        path.push_back(0);
        print(tree->left, path);
        path.pop_back();
    }
    std::cout << "{ ";
    for (auto i : path){
        std::cout << i << " ";
    }
    std::cout << "} -- " << tree->data << std::endl;
    if (tree->right != nullptr){
        path.push_back(1);
        print(tree->right, path);
    }
}


void print(AVL* tree){
    if (tree->empty) {
        std::cout << "Tree is empty\n";
    }
    else print(tree, {});
}


void update_structure(AVL* tree){
    int dif = height(tree->left) - height(tree->right);

    if (abs(dif) < 2) return;

    if (dif > 1){
        if (height(tree->left->left) > height(tree->left->right)){ //small right turn
            Point a = tree->data;
            Point b = tree->left->data;
            tree->data = b;
            AVL* L = tree->left->left;
            AVL* C = tree->left->right;
            AVL* R = tree->right;
            tree->left->data = a;
            tree->right = tree->left;
            tree->left = L;
            tree->right->left = C;
            tree->right->right = R;
        } else { //big right turn
            Point a = tree->data;
            Point b = tree->left->data;
            Point c = tree->left->right->data;
            AVL* L = tree->left->left;
            AVL* M = tree->left->right->left;
            AVL* N = tree->left->right->right;
            AVL* R = tree->right;

            tree->data = c;
            tree->left->right->data = a;
            tree->right = tree->left->right;

            tree->left->left = L;
            tree->left->right = M;
            tree->right->left = N;
            tree->right->right = R;
        }
    }

    if (dif < 1){
        if (height(tree->right->right) > height(tree->right->left)){ //small left turn
            Point a = tree->data;
            Point b = tree->right->data;
            AVL* L = tree->left;
            AVL* C = tree->right->left;
            AVL* R = tree->right->right;
            tree->data = b;
            tree->right->data = a;
            tree->left = tree->right;
            tree->right = R;
            tree->left->right = C;
            tree->left->left = L;
        } else { //big left turn
            Point a = tree->data;
            Point b = tree->right->data;
            Point c = tree->right->left->data;
            AVL* L = tree->left;
            AVL* M = tree->right->left->left;
            AVL* N = tree->right->left->right;
            AVL* R = tree->right->right;

            tree->data = c;
            tree->right->left->data = a;
            tree->left = tree->right->left;

            tree->left->left = L;
            tree->left->right = M;
            tree->right->left = N;
            tree->right->right = R;
        }
    }
    update_height(tree);
}


void add(AVL* tree, Point data){
    if (tree->empty){
        tree->empty = false;
        tree->data = data;
        return;
    }

    if (tree->data < data){
        if (tree->right == nullptr){
            tree->right = create(data, tree);
        } else {
            add(tree->right, data);
        }
    } else {
        if (tree->left == nullptr){
            tree->left = create(data, tree);
        } else {
            add(tree->left, data);
        }
    }
    update_height(tree);
    update_structure(tree);
}


void access(AVL* tree, Lambda lambda){
    if (tree == nullptr) return;
    access(tree->left, lambda);
    lambda(tree->data);
    access(tree->right, lambda);
}


void add_random(AVL* tree, int n){
    for (int i = 0; i < n; ++i){
        add(tree, Point(0, 1000));
    }
}


std::set<Point> flatten(AVL* tree){
    if (tree == nullptr) return {};
    std::set<Point> result = flatten(tree->left);
    for (auto i : flatten(tree->right)){
        result.insert(i);
    }
    result.insert(tree->data);
    return result;
}


AVL* delete_data(AVL* tree, Point comparator){
    if (tree == nullptr) return nullptr;
    if (tree->data == comparator){
        return tree;
    }

    if (tree->data > comparator){
        AVL* previous = delete_data(tree->right, comparator);
        if (previous == tree->right){
            tree->right = nullptr;
        }
        return previous;
    }

    if (tree->data < comparator){
        AVL* previous = delete_data(tree->left, comparator);
        if (tree->left == previous){
            tree->left = nullptr;
        }
        return previous;
    }

    return nullptr;
}


void delete_(AVL* tree, Point comparator){
    AVL* deleted = delete_data(tree, comparator);
    if (tree->data == comparator){
        tree->empty = true;
        delete tree->left;
        delete tree->right;
        tree->left = nullptr;
        tree->right = nullptr;
    }

    access(deleted, [tree, comparator](Point p){if (p != comparator) add(tree, p);});
    delete deleted;
}


void search(AVL* tree, Point comparator, std::vector<int> path){
    if (tree == nullptr) return;

    if (tree->data == comparator) {
        path.push_back(0);
        search(tree->left, comparator, path);
        path.pop_back();
        std::cout << "{ ";
        for (auto i : path){
            std::cout << i << " ";
        }
        std::cout << "} -- " << tree->data << std::endl;
        path.push_back(1);
        search(tree->right, comparator, path);
        return;
    }

    if (tree->data > comparator){
        path.push_back(0);
        search(tree->left, comparator, path);
        return;
    }

    if (tree->data < comparator){
        path.push_back(1);
        search(tree->right, comparator, path);
        return;
    }

}


void search(AVL* tree, Point left_, Point right_, std::vector<int> path){
    if (tree == nullptr) return;


    if (tree->data <= right_ && tree->data >= left_){
        path.push_back(0);
        search(tree->left, left_, right_, path);
        path.pop_back();
        std::cout << "{ ";
        for (auto i : path){
            std::cout << i << " ";
        }
        std::cout << "} -- " << tree->data << std::endl;
        path.push_back(1);
        search(tree->right, left_, right_, path);
        return;
    }

    if (tree->data > right_){
        path.push_back(1);
        search(tree->left, left_, right_, path);
    }

    if (tree->data < left_){
        path.push_back(0);
        search(tree->right, left_, right_, path);
    }
}


void search(AVL* tree, Point comparator){
    search(tree, comparator, {});
}


void search(AVL* tree, Point left, Point right){
    search(tree, left, right, {});
}


void quick_search(AVL* tree, Point comparator){
    if (tree == nullptr) return;

    if (tree->data == comparator){
        quick_search(tree->left, comparator);
        std::cout << tree->data << std::endl;
        quick_search(tree->right, comparator);
    }

    if (tree->data > comparator){
        quick_search(tree->left, comparator);
    }
    if (tree->data < comparator){
        quick_search(tree->right, comparator);
    }
}