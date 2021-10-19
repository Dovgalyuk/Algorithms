#ifndef DIRECTED_GRAPH_TEMPLATE_H
#define DIRECTED_GRAPH_TEMPLATE_H

template<typename Key, typename Value> class AssociativeArray {
public:

    struct Node {
        Key key;
        Value value;
        AssociativeArray<Key, Value>* array;

        Node(Key key, Value value, AssociativeArray<int, int> *array): key(key), value(value), array(array) {}

        bool isAVLTree() {
            return abs(getWeight()) <= 1 && lessNodeIsAVLTree() && moreNodeIsAVLTree();
        }

        bool lessNodeIsAVLTree() {
            return less == nullptr || less->isAVLTree();
        }

        bool moreNodeIsAVLTree() {
            return more == nullptr || more->isAVLTree();
        }

        void remove() {
            write();
            int weight = getWeight();
            Node* newPeak = nullptr;
            Node* inserted = nullptr;
            if (weight > 0) {
                newPeak = more;
                inserted = less;
            } else {
                newPeak = less;
                inserted = more;
            }
            if (parent == nullptr) {
                array->main = more;
            } else {
                if (parent->less != nullptr && parent->less->equalKey(key)) {
                    parent->less = newPeak;
                } else if (parent->more != nullptr && parent->more->equalKey(key)) {
                    parent->more = newPeak;
                }
            }
            if (newPeak != nullptr) {
                newPeak->parent = parent;
                if (inserted != nullptr) {
                    newPeak->insert(inserted);
                }
                std::cout << "\n\n\n";
                newPeak->write();
            }
        }

        void turnLeft() {
            Node* par = nullptr;
            if (parent == nullptr) {
                array->main = more;
            } else {
                par = parent;
                if (par->less != nullptr && par->less->equalKey(key)) {
                    par->less = more;
                } else if (par->more != nullptr && par->more->equalKey(key)) {
                    par->more = more;
                }
            }
            parent = more;
            more->parent = par;
            Node* moresLess = more->less;
            more->less = this;
            more = moresLess;
        }

        void turnRight() {
            Node* par = nullptr;
            if (parent == nullptr) {
                array->main = less;
            } else {
                par = parent;
                if (par->less != nullptr && par->less->equalKey(key)) {
                    par->less = less;
                } else if (par->more != nullptr && par->more->equalKey(key)) {
                    par->more = less;
                }
            }
            parent = less;
            less->parent = par;
            Node* lessMore = less->more;
            less->more = this;
            less = lessMore;
        }

        void sort() {
            if (!lessNodeIsAVLTree()) {
                less->sort();
            }
            if (!moreNodeIsAVLTree()) {
                more->sort();
            }
            if (!isAVLTree()) {
                int weight = getWeight() + (less == nullptr ? 0 : less->getWeight()) + (more == nullptr ? 0 : more->getWeight());
                if (abs(weight) == 3) {
                    if (weight > 0) {
                        turnLeft();
                    } else {
                        turnRight();
                    }
                } else if (abs(weight) == 1 || abs(weight) == 2) {
                    if (weight > 0) {
                        more->turnRight();
                        turnLeft();
                    } else {
                        less->turnLeft();
                        turnRight();
                    }
                }
            }
        }

        void insert(Node* node) {
            if (equalKey(node->key)) {
                value = node->value;
                return;
            }
            if (this->isMoreThan(node->key)) {
                if (less == nullptr) {
                    node->parent = this;
                    less = node;
                } else {
                    less->insert(node);
                }
            } else {
                if (more == nullptr) {
                    node->parent = this;
                    more = node;
                } else {
                    more->insert(node);
                }
            }
            if (!isAVLTree()) {
                sort();
            }
        }

        bool equalKey(Key key) {
            return this->key == key;
        }

        int isMoreThan(const Key key) {
            return this->key > key;
        }

        int getWeight() {
            return getMoreLevelsCount() - getLessLevelsCount();
        }

        void write() {
            if (less != nullptr || more != nullptr) {
                std::cout << std::endl;
                if (less != nullptr) {
                    printf("%d <<< ", less->key);
                }
                printf("%d", key);
                if (more != nullptr) {
                    printf(" >>> %d", more->key);
                }
                std::cout << std::endl;
            }
            if (less != nullptr) {
                less->write();
            }
            if (more != nullptr) {
                more->write();
            }
        }

        Node* findNode(Key key) {
        Node* node = this;
        while (node != nullptr) {
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
        Node* parent = nullptr;
        Node* less = nullptr;
        Node* more = nullptr;

        int getMoreLevelsCount() {
            return more == nullptr ? 0 : more->getLevelsCount() + 1;
        }

        int getLessLevelsCount() {
            return less == nullptr ? 0 : less->getLevelsCount() + 1;
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
        Node* node = new Node(key, value, this);
        if (main == nullptr) {
            main = node;
        } else {
            main->insert(node);
        }
    }

    ///\param key - Ключ, под которым лежит искомое значение
    ///\return Возвращает значение, лежащее под указанным ключом. Если ключ не найден, то вернётся NULL.
    Value find(Key key) {
        Node* node = main->findNode(key);
        return node == nullptr ? NULL : node->value;
    }

    ///\param key - Ключ, который нужно удалить
    void remove(Key key) {
        Node* node = main->findNode(key);
        if (node != nullptr) {
            node->remove();
        }
        if (!isCorrectAVLTree()) {
            main->sort();
        }
    }

protected:
    Node* main = nullptr;

};
#endif