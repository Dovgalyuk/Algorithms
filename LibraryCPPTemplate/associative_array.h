#ifndef DIRECTED_GRAPH_TEMPLATE_H
#define DIRECTED_GRAPH_TEMPLATE_H
#include <iostream>
template<typename Key, typename Value> class AssociativeArray {
public:

    struct Node {
        Key key;
        Value value;
        Node* less = nullptr;
        Node* more = nullptr;

        Node(Key key, Value value): key(key), value(value) {}

        int lessHeight() {
            return less ? less->height : 0;
        }

        int moreHeight() {
            return more ? more->height : 0;
        }

        void updateHeight() {
            height = std::max(lessHeight(), moreHeight()) + 1;
        }

        int balanceValue() {
            return moreHeight() - lessHeight();
        }

    private:
        int height = 0;
    };

    Node* main = nullptr;

    AssociativeArray() {}

    ~AssociativeArray() {
        delete[] main;
    }

    bool isEmpty() {
        return !main;
    }

    bool isCorrectAVLTree() {
        return isAVLTree(main);
    }

    ///\param key - Ключ, который нужно добавить
    ///\param value - Значение, которое надо добавить под указанным ключом
    void insert(Key key, Value value) {
        Node* node = new Node(key, value);
        main = insert(main, node);
    }

    ///\param key - Ключ, под которым лежит искомое значение
    ///\return Возвращает значение, лежащее под указанным ключом. Если ключ не найден, то вернётся NULL.
    Value find(Key key) {
        Node* node = find(main, key);
        return node ? node->value : NULL;
    }

    ///\param key - Ключ, который нужно удалить
    void remove(Key key) {
        if (!main) return;
        main = remove(main, key);
    }

protected:

    bool isAVLTree(Node* src) {
        if (!src) return true;
        bool children = isAVLTree(src->less) && isAVLTree(src->more);
        src->updateHeight();
        return abs(src->balanceValue()) <= 1 && children;
    }

    Node* turnLeft(Node* src) {
        if (!src) return src;
        Node* peak = src->more;
        src->more = peak->less;
        peak->less = src;
        src->updateHeight();
        if (peak) peak->updateHeight();
        return peak;
    }

    Node* turnRight(Node* src) {
        if (!src) return src;
        Node* peak = src->less;
        src->less = peak->more;
        peak->more = src;
        src->updateHeight();
        if (peak) peak->updateHeight();
        return peak;
    }

    Node* balance(Node* src) {
        if (!src) return src;
        src->updateHeight();
        if (src->balanceValue() == -2) {
            if (src->less && src->less->balanceValue() > 0) {
                src->less = turnLeft(src->less);
            }
            return turnRight(src);
        } else if (src->balanceValue() == 2) {
            if (src->more && src->more->balanceValue() < 0) {
                src->more = turnRight(src->more);
            }
            return turnLeft(src);
        }
        return src;
    }

    Node* insert(Node* src, Node* newNode) {
        if (!src) return newNode;
        newNode->updateHeight();
        if (src->key < newNode->key) {
            src->more = insert(src->more, newNode);
            return balance(src);
        } else if (src->key > newNode->key) {
            src->less = insert(src->less, newNode);
            return balance(src);
        }
        src->value = newNode->value;
        return src;
    }

    Node* find(Node* src, Key key) {
        if (!src) return nullptr;
        if (src->key == key) return src;
        else if (src->key < key) return find(src->more, key);
        else return find(src->less, key);
    }

    Node* findLesserNode(Node* src) {
        return !src || !src->less ? src : findLesserNode(src->less) ;
    }

    Node* remove(Node* src, int key, bool deleteSrc = true) {
        if (!src) return src;
        if (src->key < key) {
            src->more = remove(src->more, key, deleteSrc);
        } else if (src->key > key) {
            src->less = remove(src->less, key, deleteSrc);
        } else {
            Node* less = src->less;
            Node* more = src->more;
            if (deleteSrc) delete src;
            if (!less) return more;
            else if (!more) return less;
            else {
                Node* lesser = findLesserNode(more);
                lesser->more = remove(more, lesser->key, false);
                lesser->less = less;
                return balance(lesser);
            }
        }
        return balance(src);
    }

};
#endif