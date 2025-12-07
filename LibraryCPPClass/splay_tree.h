#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <string>

class SplayTree {
public:
    SplayTree();
    virtual ~SplayTree();

    // Запрещаем копирование, чтобы избежать неявных тяжелых операций
    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    void insert(const std::string& key);
    bool contains(const std::string& key);
    void remove(const std::string& key);

private:
    struct Node {
        std::string key;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(const std::string& k) : key(k) {}
    };

    Node* root_;

    void rotate_right(Node*& node);
    void rotate_left(Node*& node);
    void splay(Node*& root, const std::string& key);
    void delete_tree(Node* node);
};

#endif
