#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H
#include <string>
#include <queue>

template <typename Data>
class AssociativeArray {
    class Node {
    public:
        std::string key;
        Node* parent = nullptr;
        Node* right = nullptr;
        Node* left = nullptr;
        Data data;

        Node(std::string key, Data data): key(key), data(data) {}

        void setChild() {
            if (right) {
                right->parent = this;
            }
            if (left) {
                left->parent = this;
            }
        }

        void rotate() {
            if (!parent) {
                return;
            }

            Node* grandParent = parent->parent;
            if (grandParent) {
                if (grandParent->left == parent) {
                    grandParent->left = this;
                } else {
                    grandParent->right = this;
                }
            }

            if (parent->left == this) {
                parent->left = right;
                right = parent;
            } else {
                parent->right = left;
                left = parent;
            }

            setChild();
            parent->setChild();
            parent = grandParent;
        }

        void splay() {
            while (parent) {
                if (!parent->parent) {
                    rotate();
                } else {
                    if ((parent->parent->left == parent) == (parent->left == this)) {
                        parent->parent->rotate();
                        rotate();
                    } else {
                        rotate();
                        rotate();
                    }
                }
            }
        }

    };

public:
    ~AssociativeArray() {
        std::queue<Node*> queue;
        while (!queue.empty()) {
            Node* node = queue.front();
            queue.pop();
            if(node->left) {
                queue.push(node->left);
            }
            if(node->right) {
                queue.push(node->right);
            }
            delete node;
        }
    }

    Node* findNode(std::string key) {
        Node* node = root;
        while (node) {
            if (comp(node->key, key)) {
                node = node->right;
            } else if (comp(key, node->key)) {
                node = node->left;
            } else {
                return node;
            }
        }
        return nullptr;
    }

    void insert(std::string key, Data data) {
        Node* newNode = root;
        Node* parent = nullptr;
        while (newNode) {
            parent = newNode;
            if (comp(newNode->key, key)) {
                newNode = newNode->right;
            } else {
                newNode = newNode->left;
            }
        }
        newNode = new Node(key, data);
        newNode->parent = parent;
        if (parent) {
            if (comp(parent->key, key)) {
                parent->right = newNode;
            } else {
                parent->left = newNode;
            }
        }

        newNode->splay();
        root = newNode;
        amountNodes++;
    }

    void remove(std::string key) {
        Node* node = findNode(key);
        if (!node) {
            return;
        }
        node->splay();

        if (!node->left) {
            replace(node, node->right);
        } else if (!node->right) {
            replace(node, node->left);
        } else if (node->left && node->right) {
            Node* right = minimum(node->right);
            if (right->parent != node) {
                replace(right, right->right);
                right->right = node->right;
                right->right->parent = right;
            }
            replace(node, right);
            right->left = node->left;
            right->left->parent = right;
        } else {
            root == nullptr;
        }

        delete node;
        amountNodes--;
    }

private:
    std::less<std::string> comp;

    void replace(Node* oldN, Node* newN) {
        if (!oldN->parent) root = newN;
        else if (oldN == oldN->parent->left) oldN->parent->left = newN;
        else oldN->parent->right = newN;
        if (newN) newN->parent = oldN->parent;
    }
    Node* minimum(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

protected:
    Node* root = nullptr;
    int amountNodes = 0;

};
#endif
