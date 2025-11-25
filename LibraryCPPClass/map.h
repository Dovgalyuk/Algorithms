#ifndef MAP_SPLAY_H
#define MAP_SPLAY_H

#include <string>

class Map {
private:
    struct Node {
        std::string key;
        std::string value;
        Node* left;
        Node* right;
        Node* parent;
        
        Node(const std::string& k, const std::string& v) 
            : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    Node* root;
    size_t sz;
    
    void rotate_left(Node* x);
    void rotate_right(Node* x);
    void splay(Node* x);
    Node* find_node(const std::string& key);
    void clear(Node* node);
    Node* cpy_tree(Node* node, Node* parent);
    
public:
    Map();
    Map(const Map& other);
    Map& operator=(const Map& other);
    ~Map();
    
    void insert(const std::string& key, const std::string& value);
    bool find(const std::string& key, std::string& value); 
    bool remove(const std::string& key);
    void clear();
    
    size_t size() const;
    bool empty() const;
    
    const Node* get_root() const { return root; }
};

#endif