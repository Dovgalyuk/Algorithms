#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void add(const std::string& k, const std::string& v);
    bool get(const std::string& k, std::string& v);
    void del(const std::string& k);
    int count() const;

private:
    struct Node {
        std::string key;
        std::string val;
        Node* l;
        Node* r;
        int ht;

        Node(const std::string& k, const std::string& v)
            : key(k), val(v), l(nullptr), r(nullptr), ht(1) {
        }
    };

    Node* root;
    int cnt;

    void clear(Node* n);
    static int height(Node* n);
    static int balance(Node* n);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* add(Node* n, const std::string& k, const std::string& v);
    Node* minNode(Node* n);
    Node* del(Node* n, const std::string& k);
    bool get(Node* n, const std::string& k, std::string& v);
};

#endif
