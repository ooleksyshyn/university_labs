
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

        NodePtr node_to_delete;

        if (node->left_ == nullptr || node->right_ == nullptr){
            node_to_delete = node;
        } else{
            node_to_delete = Node::successor(node);
        }

        NodePtr node_to_fix;
        bool delete_node_to_fix = false;

        if (Node::left(node_to_delete) != nullptr){
            node_to_fix = Node::left(node_to_delete);
        } else if (Node::right(node_to_delete) != nullptr){
            node_to_fix = Node::right(node_to_delete);
        } else{
            node_to_fix = new Node(0, Colour::Black, 0);
            delete_node_to_fix = true;
            node_to_delete->right_ = node_to_fix;
        }


        node_to_fix->parent_ = node_to_delete->parent_;


        if (Node::parent(node_to_delete) == nullptr){
            root = node_to_fix;
        } else if (node_to_delete == node_to_delete->parent_->left_){
            node_to_delete->parent_->left_ = node_to_fix;
        } else{
            node_to_delete->parent_->right_ = node_to_fix;
        }

        if (node_to_delete != node){
            node->key = node_to_delete->key;
        }

        if (node_to_delete->colour_ == Colour::Black){
            remove_fix(node_to_fix);
        }

        delete node_to_delete;
        if (delete_node_to_fix){
            if (Node::right(Node::parent(node_to_fix)) == node_to_fix){
                node_to_fix->parent_->right_ = nullptr;
            } else if (Node::left(Node::parent(node_to_fix)) == node_to_fix){
                node_to_fix->parent_->left_ = nullptr;
            }

            delete node_to_fix;
        }
    }


    template<class T>
    void RedBlackTree<T>::remove_fix(NodePtr node) {
        while(node != root && node->colour_ == Colour::Black){
            if (node == node->parent_->left_){
                NodePtr sibling = node->parent_->right_;
                if (Node::colour(sibling) == Colour::Red){
                    sibling->colour_ = Colour::Black;
                    node->parent_->colour_ = Colour::Red;
                    left_rotate(node->parent_);
                    sibling = Node::right(node->parent_);
                }

                if (Node::colour(Node::left(sibling)) == Colour::Black && Node::colour(Node::right(sibling)) == Colour::Black){
                    sibling->colour_ = Colour::Red;
                    node = node->parent_;
                } else {
                    if (Node::colour(Node::right(sibling)) == Colour::Black){
                        sibling->left_->colour_ = Colour::Black;
                        sibling->colour_ = Colour::Red;
                        right_rotate(sibling);
                        sibling = node->parent_->right_;
                    }

                    sibling->colour_ = node->parent_->colour_;
                    node->parent_->colour_ = Colour::Black;
                    sibling->right_->colour_ = Colour::Black;
                    left_rotate(node->parent_);
                    node = root;
                }

            } else{
                NodePtr sibling = node->parent_->left_;
                if (Node::colour(sibling) == Colour::Red){
                    sibling->colour_ = Colour::Black;
                    node->parent_->colour_ = Colour::Red;
                    right_rotate(node->parent_);
                    sibling = Node::left(node->parent_);
                }

                if (Node::colour(Node::right(sibling)) == Colour::Black && Node::colour(Node::left(sibling)) == Colour::Black){
                    sibling->colour_ = Colour::Red;
                    node = node->parent_;
                } else {
                    if (Node::colour(Node::left(sibling)) == Colour::Black){
                        sibling->right_->colour_ = Colour::Black;
                        sibling->colour_ = Colour::Red;
                        left_rotate(sibling);
                        sibling = node->parent_->left_;
                    }

                    sibling->colour_ = node->parent_->colour_;
                    node->parent_->colour_ = Colour::Black;
                    sibling->left_->colour_ = Colour::Black;
                    right_rotate(node->parent_);
                    node = root;
                }
            }
        }

        node->colour_ = Colour::Black;
    }

    template<class D, class OStream>
    OStream &operator<<(OStream &os, const RedBlackTree <D> &tree) {
        RedBlackTree<D>::Node::print_node(os, tree.root, 0);

        return os;
    }
}