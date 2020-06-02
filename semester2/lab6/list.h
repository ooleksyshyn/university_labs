#pragma once

#include "point.h"
#include <iostream>
#include <functional>


using Lambda = std::function<void(Point&)>;
using SearchParameter = std::function<bool(Point&)>;


struct Node{

    Point data;
    Node* next;
    Node* previous;
    bool empty;
    ~Node(){
        delete next;
    }
};


Node* create_empty(Node*){
    auto new_node = new Node;
    new_node->next = nullptr;
    new_node->previous = nullptr;
    new_node->empty = true;
    return new_node;
}


Node* create(Point data, Node*){
    auto new_node = new Node;
    new_node->next = nullptr;
    new_node->previous = nullptr;
    new_node->data = data;
    new_node->empty = false;
    return new_node;
}


void add(Node* list, Point data){
    if (list->empty) {
        list->data = data;
        list->empty = false;
        list->previous = nullptr;
        list->next = nullptr;
        return;
    }
    while(list->previous != nullptr){
        list = list->previous;
    }

    if (list->data >= data){
        list->previous = create(data, list);
        list->previous->next = list;
        return;
    }

    while (list->next != nullptr){
        if (list->next->data >= data && list->data <= data){
            Node* next_node = list->next;
            list->next = create(data, list);
            list->next->previous = list;
            list->next->next = next_node;
            list->next->next->previous = list->next;
            return;
        }
        list = list->next;
    }


    list->next = create(data, list);
    list->next->previous = list;
}


void access(Node* list, Lambda lambda){
    if (list == nullptr) return;
    if (list->empty) return;
    while (list->previous != nullptr){
        list = list->previous;
    }
    while (list->next != nullptr) {
        lambda(list->data);
        list = list->next;
    }
    lambda(list->data);
}


void add_random(Node* list, int n){
    for (int i = 0; i < n; ++i) {
        add(list, Point(0, 1000));
    }
}


void search(Node* list, Point comparator){
    access(list, [comparator](Point& p){
        if (p == comparator) std::cout << p << std::endl;
    });
}


void search(Node* list, Point left, Point right){
    access(list, [left, right](Point& P){
        if (P <= right && P >= left) std::cout << P << std::endl;});
}


void print(Node* list){
    std::cout << "{ ";
    if (list->empty) std::cout << "empty";
    access(list, [](Point& P){std::cout << P << "\n";});
    std::cout << " }";
}


void delete_(Node* list, Point P){
    if (list->empty) return;

    while (list->previous != nullptr){
        list = list->previous;
    }

    while (list->data == P && !list->empty){
        if (list->next == nullptr){
            list->empty = true;
        } else{
            Node* node_to_delete = list;
            list->next->previous = nullptr;
            list = list->next;
            node_to_delete->next = nullptr;
            delete node_to_delete;
        }
    }

    while (list->next != nullptr){
        if (list->next->data == P){
            if (list->next->next == nullptr){
                Node* node_to_delete = list->next;
                list->next = nullptr;
                node_to_delete->next = nullptr;
                delete node_to_delete;
                return;
            } else {
                Node* node_to_delete = list->next;
                list->next = list->next->next;
                list->next->next->previous = list;
                node_to_delete->next = nullptr;
                delete node_to_delete;
            }
        }
        list = list->next;
    }
}