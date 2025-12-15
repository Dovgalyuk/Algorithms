#ifndef CONTAINER_TEMPLATE_H
#define CONTAINER_TEMPLATE_H

#include <algorithm>

// Класс контейнера для хранения строк на основе АВЛ-дерева
template <typename KeyType>
class Container {
public:
    // Вложенный класс узла дерева
    class Node {
    public:
        const KeyType& key() const { return _key; }
        int height() const { return _height; }
        Node* left() const { return _left; }
        Node* right() const { return _right; }

    private:
        KeyType _key;
        Node* _left = nullptr;
        Node* _right = nullptr;
        int _height = 1;

        Node(const KeyType& k) : _key(k), _left(nullptr), _right(nullptr), _height(1) {}
        friend class Container;
    };

    Container() : _root(nullptr) {}
    Container(const Container& other) : _root(nullptr) {
        if (other._root) _root = copy_recursive(other._root);
    }
    Container& operator=(const Container& other) {
        if (this != &other) {
            clear();
            if (other._root) _root = copy_recursive(other._root);
        }
        return *this;
    }
    ~Container() {
        clear();
    }

    // Добавляет строку в контейнер
    void insert(const KeyType& value) {
        _root = insert_node(_root, value);
    }

    // Удаляет строку из контейнера
    // Возвращает true, если значение было найдено и удалено
    bool remove(const KeyType& value) {
        bool deleted = false;
        _root = remove_node(_root, value, deleted);
        return deleted;
    }

    // Проверяет наличие строки в контейнере
    bool find(const KeyType& value) const {
        Node* current = _root;
        while (current) {
            if (value == current->_key) return true;
            if (value < current->_key) current = current->_left;
            else current = current->_right;
        }

        return false;
    }

    // Возвращает корень дерева
    const Node* root() const {
        return _root;
    }

    // Очищает контейнер
    void clear() {
        clear_tree(_root);
        _root = nullptr;
    }

    // Возвращает текущую высоту дерева
    int get_height() const {
        return height(_root);
    }

private:
    Node* _root = nullptr;
    // Вспомогательные функции для АВЛ-дерева:

    // Возвращает высоту узла или 0, если узел nullptr
    int height(Node* n) const {
        return n ? n->_height : 0;
    }

    // Вычисляет разницу высот (левое - правое). >1 или <-1 требует балансировки
    int balance_factor(Node* n) const {
        return n ? height(n->_left) - height(n->_right) : 0;
    }

    // Пересчитывает высоту узла, беря максимум от детей + 1
    void update_height(Node* n) {
        if (n) {
            n->_height = 1 + std::max(height(n->_left), height(n->_right));
        }
    }

    // Малый правый поворот (для исправления перевеса слева)
    Node* rotate_right(Node* y) {
        Node* x = y->_left;
        Node* T2 = x->_right;

        x->_right = y;
        y->_left = T2;

        update_height(y);
        update_height(x);

        return x;
    }

    // Малый левый поворот (для исправления перевеса справа)
    Node* rotate_left(Node* x) {
        Node* y = x->_right;
        Node* T2 = y->_left;

        y->_left = x;
        x->_right = T2;

        update_height(x);
        update_height(y);

        return y;
    }

    // Проверяет баланс-фактор и при необходимости выполняет повороты (LL, LR, RR, RL)
    Node* balance(Node* n) {
        update_height(n);
        int bf = balance_factor(n);

        // Left Left случай
        if (bf > 1 && balance_factor(n->_left) >= 0)
            return rotate_right(n);

        // Left Right случай
        if (bf > 1 && balance_factor(n->_left) < 0) {
            n->_left = rotate_left(n->_left);
            return rotate_right(n);
        }

        // Right Right случай
        if (bf < -1 && balance_factor(n->_right) <= 0)
            return rotate_left(n);

        // Right Left случай
        if (bf < -1 && balance_factor(n->_right) > 0) {
            n->_right = rotate_right(n->_right);
            return rotate_left(n);
        }

        return n;
    }

    // Рекурсивно вставляет ключ и балансирует дерево при возврате (снизу вверх)
    Node* insert_node(Node* node, const KeyType& key) {
        if (!node) return new Node(key);

        if (key < node->_key)
            node->_left = insert_node(node->_left, key);
        else if (key > node->_key)
            node->_right = insert_node(node->_right, key);
        else
            return node;

        return balance(node);
    }

    // Ищет самый левый узел (минимум) в поддереве
    Node* find_min(Node* node) {
        Node* current = node;
        while (current->_left) current = current->_left;
        return current;
    }

    // Рекурсивно удаляет узел по ключу и перебалансирует дерево
    Node* remove_node(Node* node, const KeyType& key, bool& deleted) {
        if (!node) return nullptr;

        if (key < node->_key) {
            node->_left = remove_node(node->_left, key, deleted);
        }
        else if (key > node->_key) {
            node->_right = remove_node(node->_right, key, deleted);
        }
        else {
            // Удаление узла: если 2 ребенка, заменяем на минимум справа и удаляем его
            deleted = true;

            Node* left = node->_left;
            Node* right = node->_right;

            // Нет правого ребенка (или лист)
            if (!right) { delete node; return left; }

            // Нет левого ребенка
            if (!left) { delete node; return right; }

            // Есть оба ребенка -> находим минимум справа
            Node* min_right = find_min(right);
            // Копируем данные
            node->_key = min_right->_key;
            // Удаляем узел-преемник рекурсивно
            node->_right = remove_min_helper(node->_right);
        }

        return balance(node);
    }

    // Вспомогательная функция для удаления минимального узла справа (при удалении с двумя детьми)
    Node* remove_min_helper(Node* node) {
        if (!node->_left) {
            Node* right = node->_right;
            delete node;
            return right;
        }
        node->_left = remove_min_helper(node->_left);
        return balance(node);
    }

    // Рекурсивно удаляет все узлы (освобождает память)
    void clear_tree(Node* n) {
        if (n) {
            clear_tree(n->_left);
            clear_tree(n->_right);
            delete n;
        }
    }

    // Создает полную копию дерева
    Node* copy_recursive(Node* n) {
        if (!n) return nullptr;
        Node* new_node = new Node(n->_key);
        new_node->_height = n->_height;
        new_node->_left = copy_recursive(n->_left);
        new_node->_right = copy_recursive(n->_right);
        return new_node;
    }
};
#endif
