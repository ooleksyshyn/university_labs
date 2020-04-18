namespace lab{
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
            node = node->right_;
            while(node->left_){
                node = node->left_;
            }
            return node;
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
            node = node->left_;

            while(node->right_){
                node = node->right_;
            }

            return node;
        }

        while(true){
            if (node->parent_ == nullptr) return nullptr;

            if (node->parent_->left_ != node) return node->parent_;

            node = node->parent_;
        }
    }


    template<class T>
    template<class OStream>
    void RedBlackTree<T>::Node::print_node(OStream &os, NodePtr node, int depth) {
        if (node == nullptr) return;

        std::string colour = (node->colour_ == Colour::Black) ? "B" : "R";

        Node::print_node(os, node->left_, depth + 1);

        os << std::string(2 * depth, ' ') << colour << " " << node->key << "\n";

        Node::print_node(os, node->right_, depth + 1);
    }
}