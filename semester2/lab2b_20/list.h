#pragma once

#include <iostream>

template <class P>
struct Node{
    P data;
    Node* next;
    bool empty;
};

template <typename P>
Node<P>* create_empty(P type){
    auto new_node = new Node<P>;
    new_node->next = nullptr;
    new_node->empty = true;
    return new_node;
}

template <class P>
Node<P>* create_list(const P data){
    auto new_node = new Node<P>;
    new_node->next = nullptr;
    new_node->data = data;
    new_node->empty = 0;
    return new_node;
}

template <class P>
void push_back(Node<P>* list, const P data){
    if (list->empty) {
        list->data = data;
        list->empty = false;
    } else if (!is_in_list(list, data)){
        Node<P> *FirstData = create_list(data);

        while (list->next != nullptr) {
            list = list->next;
        }

        list->next = FirstData;

    }
}

template <typename P>
void PrintList(Node<P>* list){
    std::cout << "{ ";
    if (list->empty) {
        std::cout << "empty }";
        return;
    }

    while(list->next != nullptr){
        std::cout << list->data << ", " ;
        list = list->next;
    }
    std::cout << list->data << " }";
}

template <typename P>
bool is_in_list(Node<P>* list, const P data){
    while (list->next != nullptr){
        if (list->data == data) return 1;
        list = list->next;
    }
    if (list->data == data) return 1;
    return 0;
}

template <typename P>
Node<P>* intersect(Node<P>* list_1, Node<P>* list_2){
    Node<P>* result = create_empty(P());

    while (list_1->next != nullptr){
        if (is_in_list(list_2, list_1->data)){
            push_back(result, list_1->data);
        }

        list_1 = list_1->next;
    }
    if (is_in_list(list_2, list_1->data)){
        push_back(result, list_1->data);
    }
    return result;
}

template <typename P>
Node<P>* unite(Node<P>* list_1, Node<P>* list_2){
    Node<P>* result = create_empty(P());
    while (list_1->next != nullptr){
        push_back(result, list_1->data);
        list_1 = list_1->next;
    }
    push_back(result, list_1->data);

    while (list_2->next != nullptr){
        if (!is_in_list(result, list_2->data)){
            push_back(result, list_2->data);
        }
        list_2 = list_2->next;
    }

    if (!is_in_list(result, list_2->data)) push_back(result, list_2->data);
    return result;
}

template <typename P>
Node<P>* complement(Node<P>* list_1, Node<P>* list_2){
    Node<P>* result = create_empty(P());

    while(list_2->next != nullptr){
        if (is_in_list(list_2, list_2->data) && !is_in_list(list_1, list_2->data)){
            push_back(result, list_2->data);
        }
        list_2 = list_2->next;
    }

    if (is_in_list(list_2, list_2->data) && !is_in_list(list_1, list_2->data)){
        push_back(result, list_2->data);
    }

    return result;
}