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
    ~Set() { deleteTree(root); }

    // Insert value to Red-Black Tree
    void insert(std::string key);

    // Find Node with specified value
    const Node* find(std::string key);

    // Remove value from Red-Black Tree
    void remove(std::string key);

private:
    Node* root; // Root of the Red-Black Tree

    // Left Rotate
    void rotateLeft(Node*& node);

    // Right Rotate
    void rotateRight(Node*& node);

    // Balance after insertion
    void balanceAfterInsert(Node*& node);

    // Balance after removing
    void balanceAfterDelete(Node*& node);

    // Find Node with min value
    Node* minValueNode(Node*& node);

    void transplant(Node*& root, Node*& u, Node*& v);

    // Remove all nodes from Red-Black Tree
    void deleteTree(Node* node);
};
