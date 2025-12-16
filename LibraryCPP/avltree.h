#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
#include <memory>

class AVLTree {
private:
    struct Node {
        std::string key;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        int height;
        int count; // для хранения дубликатов

        Node(const std::string& k) : key(k), left(nullptr), right(nullptr), height(1), count(1) {}
    };

    std::shared_ptr<Node> root;
    size_t size_;

    // Вспомогательные методы
    int height(const std::shared_ptr<Node>& node) const;
    int balanceFactor(const std::shared_ptr<Node>& node) const;
    void updateHeight(std::shared_ptr<Node>& node);

    // Балансировка
    std::shared_ptr<Node> rotateRight(std::shared_ptr<Node>& y);
    std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node>& x);
    std::shared_ptr<Node> balance(std::shared_ptr<Node>& node);

    // Вставка, поиск, удаление
    std::shared_ptr<Node> insert(std::shared_ptr<Node>& node, const std::string& key);
    std::shared_ptr<Node> remove(std::shared_ptr<Node>& node, const std::string& key);
    bool contains(const std::shared_ptr<Node>& node, const std::string& key) const;

    // Вспомогательные для удаления
    std::shared_ptr<Node> findMin(std::shared_ptr<Node>& node);
    std::shared_ptr<Node> removeMin(std::shared_ptr<Node>& node);

    // Обход дерева
    void inOrderTraversal(const std::shared_ptr<Node>& node, std::vector<std::string>& result) const;
    void clear(std::shared_ptr<Node>& node);

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

private:
    // Рекурсивные проверки для тестирования
    bool isBalanced(const std::shared_ptr<Node>& node) const;
    bool isBST(const std::shared_ptr<Node>& node, const std::string& min, const std::string& max) const;
};

#endif