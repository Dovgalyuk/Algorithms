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
        size_t key;
        std::string str;
        size_t height;
        Node *left;
        Node *right;
        Node(size_t key, std::string str) {
            this->str = std::move(str);
            this->key = key;
            height = 1;
            left = nullptr;
            right = nullptr;
        }

        ~Node() {
            delete left;
            delete right;
        }
    };

    AVLTree();
    void addNode(std::string &str);
    Node *findNode(std::string &str);
    void removeNode(std::string &str);

    /// Test
    void addNode(size_t key);
    Node *findNode(size_t key);
    void removeNode(size_t key);

    void clear();

    static size_t hash(std::string &str);
private:
    Node *middle;

    int nodeHeight(Node *node);
    int balanceFactor(Node *node);
    void updateHeight(Node *node);
    Node *rotateLeft(Node *node);
    Node *rotateRight(Node *node);
    Node *balance(Node *node);
    Node *insert(Node *node, size_t key, std::string &str);
    Node *findMinimal(Node *node);
    Node *setMinimal(Node *node);
    Node *remove(Node *node, size_t key);

    Node *find(Node *node, size_t key);
};


#endif //ALGORITHMS_AVLTREE_H
