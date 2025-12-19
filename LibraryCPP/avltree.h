#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
#include <memory>

class AVLTree {
private:
    struct Node {
        std::string key;
        Node* left;
        Node* right;
        int height;

        Node(const std::string& k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    size_t size_;

    // Вспомогательные методы
    int height(const Node* node) const;
    int balanceFactor(const Node* node) const;
    void updateHeight(Node* node);

    // Балансировка
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);

    // Вставка, поиск, удаление
    Node* insert(Node* node, const std::string& key);
    Node* remove(Node* node, const std::string& key);
    bool contains(const Node* node, const std::string& key) const;

    // Вспомогательные для удаления
    Node* findMin(Node* node);
    Node* removeMin(Node* node);

    // Обход дерева
    void inOrderTraversal(const Node* node, std::vector<std::string>& result) const;
    void clear(Node* node);

    // Рекурсивные проверки для тестирования (должны быть в private секции)
    bool isBalancedRecursive(const Node* node) const;
    bool isBSTRecursive(const Node* node, const std::string& min, const std::string& max) const;

public:
    AVLTree();
    ~AVLTree();

    // Интерфейс контейнера
    bool insert(const std::string& key);
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    size_t size() const;
    bool empty() const;
    void clear();

    // Дополнительные методы
    std::vector<std::string> getAllElements() const;
    int getHeight() const;

    // Для тестирования
    bool isBalanced() const;
    bool isBST() const;
};

#endif