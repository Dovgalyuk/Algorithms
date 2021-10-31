//
// Created by KirilliriK on 21.10.2021.
//

#ifndef ALGORITHMS_AVLTREE_H
#define ALGORITHMS_AVLTREE_H

#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <vector>


class AVLTree {
public:
    struct Node {
        std::string str;
        size_t height;
        Node *left;
        Node *right;
        Node(std::string str) {
            this->str = std::move(str);
            height = 1;
            left = nullptr;
            right = nullptr;
        }

        ~Node() {
            delete left;
            delete right;
        }

        void preDelete() {
            left = nullptr;
            right = nullptr;
        }
    };

    AVLTree();
    void addNode(const std::string &str);
    Node *findNode(const std::string &str);
    void removeNode(const std::string &str);

    bool isCorrectTree();

    void clear();
private:
    Node *middle;

    int nodeHeight(Node *node);
    int balanceFactor(Node *node);
    void updateHeight(Node *node);
    Node *rotateLeft(Node *node);
    Node *rotateRight(Node *node);
    Node *balance(Node *node);
    Node *insert(Node *node, const std::string &str);
    Node *findMinimal(Node *node);
    Node *setMinimal(Node *node);
    Node *remove(Node *node, const std::string &str);

    Node *find(Node *node, const std::string &str);

    bool isCorrectNode(Node *node);
};


#endif //ALGORITHMS_AVLTREE_H
