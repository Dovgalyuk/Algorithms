#ifndef RBTREE_H
#define RBTREE_H

#include <string>

using namespace std;

class RBTree {
private:
    struct Node {
        string key;
        string value;
        bool red;
        Node* left;
        Node* right;
        Node* parent;

        Node(const string& k, const string& v);
    };

    Node* root;
    int treeSize;

    void clear(Node* n);
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void fixAdd(Node* k);
    void fixDel(Node* x);
    Node* find(const string& k);
    Node* minNode(Node* n);
    void replace(Node* u, Node* v);

public:
    RBTree();
    ~RBTree();

    void insert(const string& k, const string& v);
    bool find(const string& k, string& v);
    void remove(const string& k);
    int size() const;
};

#endif