#include <iostream>
#include <string>

// Red-Bralck Tree Node color enumeration
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
    // Initialize Red-Black Tree
    Set() : root(nullptr) {}

    // Delete Red-Black Tree
    ~Set() { deleteTree(root); }

    // Insert a value into Red-Black Tree
    void insert(std::string key);

    // Find a Node with specified value
    const Node* find(std::string key);

    // Remove a value from Red-Black Tree
    void remove(std::string key);

private:
    Node* root; // Root of the Red-Black Tree

    // Utility function: Left Rotation
    void rotateLeft(Node*& node);

    // Utility function: Right Rotation
    void rotateRight(Node*& node);

    // Utility function: Fixing Insertion Violation
    void balanceAfterInsert(Node*& node);

    // Utility function: Fixing Deletion Violation
    void balanceAfterDelete(Node*& node);

    // Utility function: Find Node with Minimum Value
    Node* minValueNode(Node*& node);

    // Utility function: Transplant nodes in Red-Black Tree
    void transplant(Node*& root, Node*& u, Node*& v);

    // Utility function: Delete all nodes in the Red-Black Tree
    void deleteTree(Node* node);
};