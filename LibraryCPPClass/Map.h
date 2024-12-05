#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

class AssociativeArray {
private:
    struct Node {
        std::string key;
        std::string value;
        Node* left;
        Node* right;
        int height;

        Node(const std::string& k, const std::string& v): key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* node);
    int balanceFactor(Node* node);
    void fixHeight(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* balance(Node* node);
    Node* insert(Node* node, const std::string& key, const std::string& value);
    Node* find(Node* node, const std::string& key) const;
    Node* remove(Node* node, const std::string& key);
    int countNodes(Node* node) const;
    void clear(Node* node);

public:
    AssociativeArray();
    ~AssociativeArray();
    void insert(const std::string& key, const std::string& value);
    std::string find(const std::string& key) const;
    void remove(const std::string& key);
    int countNodes() const;
};

#endif 

