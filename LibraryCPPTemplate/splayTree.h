#pragma once
#include <string>
#include <queue>

class SplayTree {
    class Node {
    public:
        Node(std::string str, Node* parent) {
            this->str = str;
            this->parent = parent;
        }

        std::string getString() {
            return str;
        }

        Node* getLeft() {
            return left;
        }

        Node* getRight() {
            return right;
        }
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
        void insert(Node* node) {
            if (this->str < node->str) {
                right = node;
            } else {
                left = node;
            }
        }

        Node* getMinimum() {
            Node* result = this;
            while (result->left) result = result->left;
            return result;
        }

        void replace(Node* newNode) {
            if (parent) {
                if (parent->left == this) parent->left = newNode;
                else parent->right = newNode;
            }
            if (newNode) newNode->parent = parent;
        }

        Node* replace() {
            Node* newRight = right->getMinimum();
            if (newRight->parent != this) {
                newRight->replace(newRight->right);
                newRight->right = right;
                newRight->right->parent = newRight;
            }
            replace(newRight);
            newRight->left = left;
            newRight->left->parent = newRight;
            return newRight;
        }
    private:
        std::string str;
        Node* parent = nullptr;
        Node* right = nullptr;
        Node* left = nullptr;
    };

public:
    SplayTree() {
        root = nullptr;
    }
    ~SplayTree() {
        std::queue<Node*> queue;
        while (!queue.empty()) {
            Node* node = queue.front();
            queue.pop();
            if(node->getLeft()) {
                queue.push(node->getLeft());
            }
            if(node->getRight()) {
                queue.push(node->getRight());
            }
            delete node;
        }
    }

    Node* findNode(std::string newstr) {
        Node* node = root;
        while (node) {
            if (node->getString() < newstr) {
                node = node->getRight();
            } else if (node->getString() > newstr) {
                node = node->getLeft();
            } else {
                return node;
            }
        }
        return nullptr;
    }

    void insert(std::string newstr) {
        Node* newNode = root;
        Node* parent = nullptr;
        while (newNode) {
            parent = newNode;
            if (newNode->getString() < newstr) {
                newNode = newNode->getRight();
            } else {
                newNode = newNode->getLeft();
            }
        }
        newNode = new Node(newstr, parent);
        if (parent) {
            parent->insert(newNode);
        }

        newNode->splay();
        root = newNode;
        amount++;
    }

    void remove(std::string str) {
        Node* node = findNode(str);
        if (!node) {
            return;
        }
        node->splay();

        if (!node->getLeft()) {
            node->replace(node->getRight());
        } else if (!node->getRight()) {
            node->replace(node->getLeft());
        } else if (node->getLeft() && node->getRight()) {
            root = node->replace();
        } else {
            root == nullptr;
        }

        delete node;
        amount--;
    }
    
    size_t size() {
        return amount;
    }

    bool empty() {
        return (amount < 1);
    }

private:
    Node* root = nullptr;
    int amount = 0;
};
