
#include "RedBlackTree.hpp"

namespace lab {

    template<class T>
    RedBlackTree<T>::RedBlackTree(): root(nullptr) {}


    template<class T>
    RedBlackTree<T>::RedBlackTree(std::initializer_list<T> list) : root(nullptr){
        for (const auto& key : list){
            insert(key);
        }
    }


    template<class T>
    RedBlackTree<T>::RedBlackTreeNode::RedBlackTreeNode(
            const T& key,
            Colour colour,
            std::size_t size,
            RedBlackTreeNode *parent,
            RedBlackTreeNode *left,
            RedBlackTreeNode *right
                    ) : key(key), colour_(colour), size_(size), parent_(parent), left_(left), right_(right){}


    template<class T>
    std::size_t RedBlackTree<T>::RedBlackTreeNode::size(RedBlackTreeNode* node) {
        if (node == nullptr) return 0;

        return node->size_;
    }

    template<class T>
    Colour RedBlackTree<T>::RedBlackTreeNode::colour(RedBlackTreeNode* node) {
        if (node == nullptr) return Colour::Black;
        return node->colour_;
    }

    template<class T>
    auto RedBlackTree<T>::RedBlackTreeNode::parent(NodePtr node) -> NodePtr {
        if (node == nullptr) return nullptr;
        return node->parent_;
    }

    template<class T>
    auto RedBlackTree<T>::RedBlackTreeNode::left(NodePtr node) -> NodePtr {
        if (node == nullptr) return nullptr;
        return node->left_;
    }

    template<class T>
    auto RedBlackTree<T>::RedBlackTreeNode::right(NodePtr node) -> NodePtr {
        if (node == nullptr) return nullptr;
        return node->right_;
    }

    template<class T>
    auto RedBlackTree<T>::RedBlackTreeNode::successor(NodePtr node) -> NodePtr {
        if (node->right_){
            return node->right_;
        }

        while(true){
            if (node->parent_ == nullptr) return nullptr;

            if (node->parent_->right_ != node) return node->parent_;

            node = node->parent_;
        }
    }

    template<class T>
    auto RedBlackTree<T>::RedBlackTreeNode::predecessor(NodePtr node) -> NodePtr {
        if (node->left_) {
            return node->left_;
        }

        while(true){
            if (node->parent_ == nullptr) return nullptr;

            if (node->parent_->left_ != node) return node->parent_;

            node = node->parent_;
        }
    }


    template<class T>
    auto RedBlackTree<T>::operator[](std::size_t index) const -> CNodePtr{
        NodePtr node = root;

        while (true){
            std::size_t node_index = RedBlackTreeNode::size(root->left);

            if (node_index > index){
                node = node->left;
            } else if (node_index < index){
                node = node->right;
                index -= node_index + 1;
            } else{
                return node;
            }
        }
    }

    template<class T>
    template<class OStream>
    void RedBlackTree<T>::print_node(OStream &os, NodePtr node, int depth) {
        if (node == nullptr) return;

        std::string colour = (node->colour_ == Colour::Black) ? "B" : "R";

        RedBlackTree<T>::print_node(os, node->left_, depth + 1);

        os << std::string(2 * depth, ' ') << colour << " " << node->key << "\n";

        RedBlackTree<T>::print_node(os, node->right_, depth + 1);
    }

    template<class T>
    void RedBlackTree<T>::insert(const T &key) {
        NodePtr head = root;

        NodePtr predecessor = nullptr;

        while(head != nullptr){
            predecessor = head;

            if (head->key > key){
                head = head->left_;
            } else if (head->key < key){
                head = head->right_;
            } else {
                return;
            }
        }

        auto new_node = new Node(key, Colour::Red, 1, predecessor);

        if (predecessor){
            if (predecessor->key > key){
                predecessor->left_ = new_node;
            } else{
                predecessor->right_ = new_node;
            }
        } else{
            root = new_node;
        }

        insert_fix(new_node);
    }

    template<class T>
    void RedBlackTree<T>::insert_fix(NodePtr node) {

        while(Node::colour(Node::parent(node)) ==  Colour::Red){
            if (Node::parent(node) == Node::left(Node::parent(Node::parent(node)))){
                NodePtr uncle = Node::right(Node::parent(Node::parent(node)));
                if (Node::colour(uncle) == Colour::Red){
                    node->parent_->colour_ = Colour::Black;
                    uncle->colour_ = Colour::Black;
                    node->parent_->parent_->colour_ = Colour::Red;
                    node = node->parent_->parent_;
                } else {
                    if (node == Node::right(Node::parent(node))){
                        node = node->parent_;
                        left_rotate(node);
                    }

                    node->parent_->colour_ = Colour::Black;
                    node->parent_->parent_->colour_ = Colour::Red;
                    right_rotate(Node::parent(Node::parent(node)));
                }
            } else{
                NodePtr uncle = Node::left(Node::parent(Node::parent(node)));
                if (Node::colour(uncle) == Colour::Red){
                    node->parent_->colour_ = Colour::Black;
                    uncle->colour_ = Colour::Black;
                    node->parent_->parent_->colour_ = Colour::Red;
                    node = node->parent_->parent_;
                } else {
                    if (node == Node::left(Node::parent(node))){
                        node = node->parent_;
                        right_rotate(node);
                    }

                    node->parent_->colour_ = Colour::Black;
                    node->parent_->parent_->colour_ = Colour::Red;
                    left_rotate(Node::parent(Node::parent(node)));
                }
            }
        }

        root->colour_ = Colour::Black;
    }

    template<class T>
    void RedBlackTree<T>::left_rotate(NodePtr node) {
        NodePtr right = node->right_;

        NodePtr middle_subtree = right->left_;

        NodePtr parent = node->parent_;

        if (parent == nullptr){
            root = right;
        } else if (parent->right_ == node){
            parent->right_ = right;
        } else {
            parent->left_ = right;
        }

        right->parent_ = parent;

        right->left_ = node;
        node->parent_ = right;

        node->right_ = middle_subtree;
        if (middle_subtree){
            middle_subtree->parent_ = node;
        }
    }

    template<class T>
    void RedBlackTree<T>::right_rotate(NodePtr node) {
        NodePtr left = node->left_;

        NodePtr middle_subtree = left->right_;

        NodePtr parent = node->parent_;

        if (parent == nullptr){
            root = left;
        } else if (parent->right_ == node){
            parent->right_ = left;
        } else {
            parent->left_ = left;
        }

        left->parent_ = parent;

        left->right_ = node;
        node->parent_ = left;

        node->left_ = middle_subtree;
        if (middle_subtree){
            middle_subtree->parent_ = node;
        }
    }


    template<class T>
    auto RedBlackTree<T>::search(const T &key) const -> RedBlackTree::CNodePtr {
        NodePtr head = root;

        while(head){
            if (key > head->key){
                head = head->right_;
            } else if (key < head->key){
                head = head->left_;
            } else{
                return head;
            }
        }

        return nullptr;
    }

    template<class T>
    void RedBlackTree<T>::remove(const T &key) {
        NodePtr node = root; // node to delete

        while(node){
            if (key > node->key){
                node = node->right_;
            } else if (key < node->key){
                node = node->left_;
            } else{
                break;
            }
        }

        if (node == nullptr) return;

        if (node->left_ == nullptr || node->right_ == nullptr){

        }

    }

    template<class D, class OStream>
    OStream &operator<<(OStream &os, const RedBlackTree <D> &tree) {
        RedBlackTree<D>::print_node(os, tree.root, 0);;
    }
}