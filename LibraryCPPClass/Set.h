#include <iostream>
#include <string>

// Red-Bralck Tree Node color enum
enum Color { RED, BLACK };

// Struct Red-Black Tree Node
struct Node {
    std::string data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(std::string value) : data(value), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

class Set {
public:
    // Init Red-Black Tree
    Set() : root(nullptr) {}

    // Delete Red-Black Tree
    ~Set() { delete_tree(root); }

    // Insert value to Red-Black Tree
    void insert(std::string key);

    // Find Node with specified value
    const Node* find(std::string key);

    // Remove value from Red-Black Tree
    void remove(std::string key);

private:
    Node* root; // Root of the Red-Black Tree

    // Left Rotate
    void rotate_left(Node*& node);

    // Right Rotate
    void rotate_right(Node*& node);

    // Balance after insertion
    void balance_after_insert(Node*& node);

    // Balance after removing
    void balance_after_delete(Node*& node);

    // Find Node with min value
    Node* min_node(Node*& node);

    void transplant(Node*& root, Node*& u, Node*& v);

    // Remove all nodes from Red-Black Tree
    void delete_tree(Node* node);
};
