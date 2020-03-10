#pragma once

#include <iostream>

enum class Colour{Black, Red};

template<class T>
struct Node{

    T key;
    Node *parent;
    Colour color;
    Node *left;
    Node *right;
};


template<class T>
class RBtree{
    Node<T> *root;
    Node<T> *q;
public:
    RBtree();

    void insert(T);
    void insertfix(Node<T> *);
    void leftrotate(Node<T> *);
    void rightrotate(Node<T> *);
    void del(T);
    auto successor(Node<T> *) -> Node<T>*;
    void delfix(Node<T> *);
    void disp();
    void display(Node<T> *);
    void search();
};


#include "RedBlackTree.tpp"