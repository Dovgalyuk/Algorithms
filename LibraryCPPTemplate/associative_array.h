#ifndef DIRECTED_GRAPH_TEMPLATE_H
#define DIRECTED_GRAPH_TEMPLATE_H

template<typename Key, typename Value> class AssociativeArray {
public:

    struct Node {
        Key key;
        Value value;

        Node(Key key, Value value): key(key), value(value) {}

        bool isAVLTree() {
            return abs(getWeight()) <= 1 && (less || less->isAVLTree()) && (more || more->isAVLTree());
        }

        Node* remove() {
            Node* peak = nullptr;
            int weight = getWeight();
            if (weight < 0) {
                peak = less;
                if (more) {
                    peak = peak->insert(more);
                }
            } else {
                peak = more;
                if (less) {
                    peak = peak->insert(less);
                }
            }
            return peak;
        }

        Node* turnLeft() {
            Node* peak = more;
            more = peak->less;
            peak->less = this;
            return peak;
        }

        Node* turnRight() {
            Node* peak = less;
            less = peak->more;
            peak->more = this;
            return peak;
        }

        Node* balance() {
            int weight = getWeight();
            if (weight == -2) {
                if (less->getWeight() > 0) {
                    less = less->turnLeft();
                }
                return turnRight();
            } else if(weight == 2) {
                if (more->getWeight() < 0) {
                    more = more->turnRight();
                }
                return turnLeft();
            }
            return this;
        }

        Node* insert(Node* node) {
            if (node->key < key) {
                if (less) {
                    less = less->insert(node);
                } else {
                    less = node;
                }
            } else if (node->key > key) {
                if (more) {
                    more = more->insert(node);
                } else {
                    more = node;
                }
            }
            return balance();
        }

        int getWeight() {
            return getMoreLevelsCount() - getLessLevelsCount();
        }

        void write() {
            if (less || more) {
                std::cout << std::endl;
                if (less) {
                    printf("%d <<< ", less->key);
                }
                printf("%d", key);
                if (more) {
                    printf(" >>> %d", more->key);
                }
                std::cout << std::endl;
            }
            if (less) {
                less->write();
            }
            if (more) {
                more->write();
            }
        }

        Node* findNode(Key key) {
            Node* node = this;
            while (!node) {
                if (node->equalKey(key)) {
                    return node;
                } else {
                    if (node->isMoreThan(key)) {
                        node = node->less;
                    } else {
                        node = node->more;
                    }
                }
            }
            return nullptr;
        }

    private:
        Node* less = nullptr;
        Node* more = nullptr;

        int getMoreLevelsCount() {
            return !more ? 0 : more->getLevelsCount() + 1;
        }

        int getLessLevelsCount() {
            return !less ? 0 : less->getLevelsCount() + 1;
        }

        int getLevelsCount() {
            return std::max(getLessLevelsCount(), getMoreLevelsCount());
        }
    };

    AssociativeArray() {}

    ~AssociativeArray() {}

    void write() {
        main->write();
    }

    bool isCorrectAVLTree() {
        return main->isAVLTree();
    }

    ///\param key - Ключ, который нужно добавить
    ///\param value - Значение, которое надо добавить под указанным ключом
    void insert(Key key, Value value) {
        Node* node = new Node(key, value);
        if (!main) {
            main = node;
        } else {
            main = main->insert(node);
        }
    }

    ///\param key - Ключ, под которым лежит искомое значение
    ///\return Возвращает значение, лежащее под указанным ключом. Если ключ не найден, то вернётся NULL.
    Value find(Key key) {
        Node* node = main->findNode(key);
        return node ? NULL : node->value;
    }

    ///\param key - Ключ, который нужно удалить
    void remove(Key key) {
        if (key == main->key) {
            main = main->remove();
            return;
        }
        Node* parent = main;
        while (main->less )
        {
            
        }
        
    }

protected:
    Node* main = nullptr;

};
#endif