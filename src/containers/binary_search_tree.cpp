#include <functional>
#include <iostream>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class BinaryTree {
    struct Node;

public:
    BinaryTree() {
        size_ = 0;
        root_ = nullptr;
    };

    BinaryTree(const BinaryTree& other) {
        // Copy using tree traversals
    }

    BinaryTree& operator=(BinaryTree other) {
        // Copy using tree traversals
    }

    bool Contains(const T& value) const {
        return GetNode(value) != nullptr;
    };

    bool Insert(const T& value) {
        // Handle duplicate insert
        if (Contains(value)) {
            return false;
        }

        if (root_ == nullptr) {
            Node* node = new Node;
            node->value = value;
            root_ = node;
        } else {
            Node* current_node = root_;
            bool is_right_subtree = false;
            while (true) {
                is_right_subtree = value > current_node->value;
                if (is_right_subtree) {
                    if (current_node->right == nullptr) {
                        break;
                    } else {
                        current_node = current_node->right;
                    }
                } else {
                    if (current_node->left == nullptr) {
                        break;
                    } else {
                        current_node = current_node->left;
                    }
                }
            }
            Node* new_node = new Node;
            new_node->value = value;
            new_node->parent = current_node;
            if (is_right_subtree) {
                current_node->right = new_node;
            } else {
                current_node->left = new_node;
            }
        }
        size_++;
        return true;
    }

    bool Erase(const T& value) {
        Node* node_to_delete = GetNode(value);

        if (node_to_delete == nullptr) {
            return false;
        }

        // Case 1: Deleting leaf node
        if (IsLeafNode(node_to_delete)) {
            if (node_to_delete != root_) {
                Node* parent = node_to_delete->parent;
                if (IsLeftChild(node_to_delete)) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
                delete node_to_delete;
            } else {
                delete node_to_delete;
                root_ = nullptr;
            }
            size_--;
            return true;
        }

        // Case 2: Has Left or Right child
        Node* successor = GetSuccessor(node_to_delete);
        // std::cout << "successor: " << successor->value << std::endl;
        bool is_node_to_delete_left = IsLeftChild(node_to_delete);

        Node* existing_parent_of_successor = successor->parent;

        // Part 1 : Managing successor's existing parent
        if (IsLeftChild(successor)) {
            // If left successor has a right child, the value of that right child must be lower than
            // the sucessor's parent, so linking it to left
            if (successor->right != nullptr) {
                existing_parent_of_successor->left = successor->right;
            } else {
                successor->parent->left = nullptr;
            }

        } else {
            // If the right successor has a left child, it means the value of that left child
            // must be higher than the success'r parent, so linking it to the right
            if (successor->left != nullptr) {
                existing_parent_of_successor->right = successor->left;
            } else {
                successor->parent->right = nullptr;
            }
        }

        // Part - 2 Linking successor's new parent

        if (node_to_delete != root_) {
            successor->parent = node_to_delete->parent;
            if (is_node_to_delete_left) {
                successor->parent->left = successor;
            } else {
                successor->parent->right = successor;
            }
        } else {
            successor->parent = nullptr;
            root_ = successor;
        }

        // Part - 3 Linking successor's new children
        if (node_to_delete->left != nullptr) {
            if (node_to_delete->left != successor) {  // avoiding node-cycling
                successor->left = node_to_delete->left;
                successor->left->parent = successor;
            }
        }
        if (node_to_delete->right != nullptr) {
            if (node_to_delete->right != successor) {
                successor->right = node_to_delete->right;
                successor->right->parent = successor;
            }
        }

        delete node_to_delete;
        size_--;
        return true;
    }

    Node* GetSuccessor(Node* node_to_delete) {
        Node* node_to_swap = nullptr;
        bool choosing_lst = node_to_delete->left != nullptr;
        if (choosing_lst) {
            // max lst
            node_to_swap = node_to_delete->left;
            while (node_to_swap->right != nullptr) {
                node_to_swap = node_to_swap->right;
            }
        } else {
            // min rst
            node_to_swap = node_to_delete->right;
            while (node_to_swap->left != nullptr) {
                node_to_swap = node_to_swap->left;
            }
        }
        return node_to_swap;
    }

    bool Empty() const {
        return (size_ == 0);
    };

    size_t Size() const {
        return size_;
    };

    void Clear() {
        ClearImpl(root_);
        size_ = 0;
        root_ = nullptr;
    }

    ~BinaryTree() {
        Clear();
    };

    // T GetInOrderSuccessor(const T& value) {
    //     std::vector<int> list;
    //     ConvertBstToVector(root_, list);
    //     if (value == list[list.size() - 1]) {
    //         return 0;
    //     }
    //     for (size_t i = 0; i < list.size(); i++) {
    //         if (list[i] == value) {
    //             return list[i + 1];
    //         }
    //     }
    //     return 0;
    // }

    T GetInOrderSuccessor(const T& value) {
        std::vector<int> list;
        ConvertBstToVector(root_, list);
        if (value == list[list.size() - 1]) {
            return 0;
        }
        Node* node = GetNode(value);
        if (node == nullptr) {
            return 0;
        }
        if (node->right != nullptr) {
            node = node->right;
            while (node->left != nullptr) {
                node = node->left;
            }
            return node->value;
        } else {
            Node* parent = root_;
            Node* successor = nullptr;
            while (parent != node) {
                if (node->value < parent->value) {
                    successor = parent;
                    parent = parent->left;
                } else {
                    parent = parent->right;
                }
            }
            return successor->value;
        }
        return 0;
    }

    T PthSmallest(size_t pth) {
        std::vector<int> list;
        ConvertBstToVector(root_, list);
        return list[pth - 1];
    }

    void ConvertBstToVector(Node* node, std::vector<int>& list,
                            std::string traversal = "in-order") {
        if (node != nullptr) {
            if (traversal == "in-order") {
                ConvertBstToVector(node->left, list);
                list.push_back(node->value);
                ConvertBstToVector(node->right, list);
            } else if (traversal == "post-order") {
                ConvertBstToVector(node->left, list, "post-order");
                ConvertBstToVector(node->right, list, "post-order");
                list.push_back(node->value);
            }
        }
    }

    void Prune(const T& left, const T& right) {
        std::vector<int> list;
        ConvertBstToVector(root_, list);
        Clear();
        for (size_t i = 0; i < list.size(); i++) {
            int element = list[i];
            bool range = element >= left && element <= right;
            if (!range) {
                Insert(element);
            }
        }
    }

    void PrintTree() {
        std::vector<int> list;
        ConvertBstToVector(root_, list);
        for (auto i : list) {
            std::cout << i << " ";
        }
    }


    /*
     * Finds the maximum value in the tree
     * Returns a reference to the maximum value.
     * If there is no the maximum value in the tree a std::runtime_error is thrown
     */
    T& GetMax() {
        Node* node = root_;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node->value;
    }

    // ** Additional functions and features **
    std::string GetTreeAsString() {
        if (!Empty()) {
            std::string str = "";
            PrintTreeImpl(root_, str);
            return str;
        } else {
            return "NIL";
        }
    }

    void Print() {
        std::cout << "root: " << root_->value << "|";
        std::cout << GetTreeAsString() << std::endl;
    }

    void PrintSuccessor(int val) {
        Node* node = GetNode(val);
        Node* successor = GetSuccessor(node);
        std::cout << successor->value << std::endl;
    }

    void NodeDetails(int val) {
        Node* node = GetNode(val);
        if (node == root_) {
            std::cout << "it is root" << std::endl;
        } else {
            std::cout << "Details p: " << node->parent->value << " l: " << node->left
                      << " r: " << node->right << "IsLeft: " << IsLeftChild(node) << std::endl;
        }
    }

private:
    size_t size_ = 0;
    Node* root_ = nullptr;
    struct Node {
        T value;

        Node* parent;
        Node* left;
        Node* right;

        Node() {
            value = 0;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
        }
    };

private:
    void ClearImpl(Node* node) {
        if (node != nullptr) {
            ClearImpl(node->left);
            ClearImpl(node->right);
            delete node;
        }
    }

    // Function to construct string from binary tree
    void PrintTreeImpl(Node* root, std::string& str) {
        if (root != nullptr) {
            PrintTreeImpl(root->left, str);
            str += std::to_string(root->value) + ",";
            PrintTreeImpl(root->right, str);
        }
    }

    Node* GetNode(const T& value) const {
        Node* node = nullptr;
        Node* current_node = root_;
        while (current_node != nullptr) {
            if (current_node->value == value) {
                node = current_node;
                break;
            }
            if (value > current_node->value) {
                current_node = current_node->right;
            } else {
                current_node = current_node->left;
            }
        }
        return node;
    }

    bool IsLeftChild(Node* node) {
        if (node == root_) {
            return false;
        }
        Node* parent = node->parent;
        return parent->left == node;
    }

    bool IsLeafNode(Node* node) {
        return node->left == nullptr && node->right == nullptr;
    }
};

void BinaryTreeInterfaceTester() {
    int n;
    std::cin >> n;
    BinaryTree<int> tree;
    for (int i = 0; i < n; i++) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Insert") {
            int val;
            std::cin >> val;
            std::cout << tree.Insert(val) << std::endl;
        } else if (cmd == "Delete") {
            int val;
            std::cin >> val;
            std::cout << tree.Erase(val) << std::endl;
        } else if (cmd == "Empty") {
            std::cout << tree.Empty() << std::endl;
        } else if (cmd == "Clear") {
            tree.Clear();
            std::cout << "Clear" << std::endl;
        } else if (cmd == "Size") {
            std::cout << tree.Size() << std::endl;
        } else if (cmd == "Find") {
            int val;
            std::cin >> val;
            std::cout << tree.Contains(val) << std::endl;
        } else if (cmd == "print") {
            tree.Print();
        } else if (cmd == "exit") {
            return;
        } else if (cmd == "snode") {
            int val;
            std::cin >> val;
            tree.PrintSuccessor(val);
        } else if (cmd == "node") {
            int val;
            std::cin >> val;
            tree.NodeDetails(val);
        } else if (cmd == "GetMax") {
            std::cout << tree.GetMax() << std::endl;
        }
    }
}

void ValidRange() {
    size_t n1;
    std::cin >> n1;
    BinaryTree<int> tree;
    for (size_t i = 0; i < n1; i++) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Insert") {
            int val;
            std::cin >> val;
            tree.Insert(val);
        } else if (cmd == "Delete") {
            int val;
            std::cin >> val;
            tree.Erase(val);
        }
    }
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "Prune") {
        size_t l;
        size_t r;
        std::cin >> l >> r;
        tree.Prune(l, r);
        tree.PrintTree();
    }
}

void GetInOrderSuccessor() {
    size_t n1;
    std::cin >> n1;
    size_t n2;
    std::cin >> n2;
    BinaryTree<int> tree;
    for (size_t i = 0; i < n1; i++) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Insert") {
            int val;
            std::cin >> val;
            tree.Insert(val);
        } else if (cmd == "Delete") {
            int val;
            std::cin >> val;
            tree.Erase(val);
        }
    }
    for (size_t i = 0; i < n2; i++) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "Successor") {
            size_t val;
            std::cin >> val;
            size_t res = tree.GetInOrderSuccessor(val);
            if (res == 0) {
                std::cout << "NOSUCCESSOR" << std::endl;
            } else {
                std::cout << res << std::endl;
            }
        }
    }
}