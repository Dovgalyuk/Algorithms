#ifndef RBTREE_H
#define RBTREE_H

#include <string>

class RBTree {
public:
    RBTree();
    ~RBTree();

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
        Node* p;
        bool red;

        Node(const std::string& k, const std::string& v)
            : key(k), val(v), l(nullptr), r(nullptr), p(nullptr), red(true) {}
    };

    Node* root;
    int cnt;

    void clear(Node* n);
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void fixAdd(Node* k);
    void fixDel(Node* x);
    Node* minNode(Node* n);
    void replace(Node* u, Node* v);
    Node* find(const std::string& k);
};

#endif