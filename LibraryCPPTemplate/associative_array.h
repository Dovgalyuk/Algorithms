#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H
#include <string>
#include <queue>

template <typename Data>
class AssociativeArray {
    class Node {
        std::string key;
        Node* parent = nullptr;
        Node* right = nullptr;
        Node* left = nullptr;

        std::less<std::string> comp;
    public:
        Data data;

        Node(std::string key, Data data, Node* parent): key(key), data(data), parent(parent) {}

        bool isLess(std::string than) {
            return comp(key, than);
        }

        bool isMore(std::string than) {
            return comp(than, key);
        }

        std::string getKey() {
            return key;
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
            if (isLess(node->key)) {
                right = node;
            } else {
                left = node;
            }
        }

        Node* getMinimum() {
            Node* res = this;
            while (res->left) res = res->left;
            return res;
        }

        void replace(Node* newN) {
            if (parent) {
                if (parent->left == this) parent->left = newN;
                else parent->right = newN;
            }
            if (newN) newN->parent = parent;
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

    };

public:
    ~AssociativeArray() {
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

    Node* findNode(std::string key) {
        Node* node = root;
        while (node) {
            if (node->isLess(key)) {
                node = node->getRight();
            } else if (node->isMore(key)) {
                node = node->getLeft();
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
            if (newNode->isLess(key)) {
                newNode = newNode->getRight();
            } else {
                newNode = newNode->getLeft();
            }
        }
        newNode = new Node(key, data, parent);
        if (parent) {
            parent->insert(newNode);
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
        amountNodes--;
    }

protected:
    Node* root = nullptr;
    int amountNodes = 0;

};
#endif
