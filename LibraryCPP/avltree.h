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

    static void clear(Node* n);
    static int height(Node* n);
    static int balance(Node* n);
    static Node* rightRotate(Node* y);
    static Node* leftRotate(Node* x);
    static Node* add(Node* n, const std::string& k, const std::string& v);
    static Node* minNode(Node* n);
    static Node* del(Node* n, const std::string& k);
    static bool get(Node* n, const std::string& k, std::string& v);
};

#endif
