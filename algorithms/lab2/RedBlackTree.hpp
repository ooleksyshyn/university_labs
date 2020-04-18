#pragma once

#include <iostream>

namespace lab {

    enum class Colour {
        Black, Red
    };


    template<class T>
    class RedBlackTree {
    public:
        struct RedBlackTreeNode {
            explicit RedBlackTreeNode(const T&,
                    Colour = Colour::Black,
                    std::size_t size = 1,
                    RedBlackTreeNode *parent = nullptr,
                    RedBlackTreeNode *left = nullptr,
                    RedBlackTreeNode *right = nullptr
                            );

            static std::size_t size(RedBlackTreeNode*);
            static Colour colour(RedBlackTreeNode*);
            static RedBlackTreeNode* parent(RedBlackTreeNode*);
            static RedBlackTreeNode* left(RedBlackTreeNode*);
            static RedBlackTreeNode* right(RedBlackTreeNode*);
            static RedBlackTreeNode* successor(RedBlackTreeNode*);
            static RedBlackTreeNode* predecessor(RedBlackTreeNode*);

            template<class OStream>
            static void print_node(OStream &, RedBlackTreeNode*, int depth);

            T key;
            Colour colour_;
            std::size_t size_;
            RedBlackTreeNode* parent_;
            RedBlackTreeNode* left_;
            RedBlackTreeNode* right_;
        };

        using NodePtr = RedBlackTreeNode *;
        using CNodePtr = const RedBlackTreeNode *;
        using Node = RedBlackTreeNode;


        RedBlackTree();

        RedBlackTree(std::initializer_list<T>);

        void insert(const T &key);
        void insert_fix(NodePtr);
        void left_rotate(NodePtr);
        void right_rotate(NodePtr);
        void remove(const T &key);
        void remove_fix(NodePtr);
        auto search(const T &key) const -> CNodePtr;
        auto operator[](std::size_t) const -> CNodePtr;

        template<class D, class OStream>
        friend OStream &operator<<(OStream &os, const RedBlackTree<D> &tree);

    private:
        NodePtr root;
    };
}

#include "RedBlackTreeNode.tpp"
#include "RedBlackTree.tpp"