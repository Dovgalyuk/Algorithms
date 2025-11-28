#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <memory>
#include <stdexcept>

template <typename Data>
class List
{
private:
    struct Node
    {
        Data data;
        std::unique_ptr<Node> next;

        Node(const Data& d) : data(d), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    size_t list_size;

public:
    class Item
    {
    private:
        Node* node;

    public:
        Item(Node* n = nullptr) : node(n) {}

        Item* next() {
            if (!node || !node->next) return nullptr;
            return new Item(node->next.get());
        }

        Data& data() {
            return node->data;
        }

        const Data& data() const {
            return node->data;
        }

        Node* getNode() const { return node; }

        static void deleteItem(Item* item) {
            delete item;
        }
    };

    List() : head(nullptr), list_size(0) {}

    List(const List& other) : head(nullptr), list_size(0) {
        Node* current = other.head.get();
        while (current) {
            insert(current->data);
            current = current->next.get();
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Node* current = other.head.get();
            while (current) {
                insert(current->data);
                current = current->next.get();
            }
        }
        return *this;
    }

    ~List() {
        clear();
    }

    void clear() {
        while (head) {
            head = std::move(head->next);
        }
        list_size = 0;
    }

    Item* first() {
        return head ? new Item(head.get()) : nullptr;
    }

    Item* first() const {
        return head ? new Item(head.get()) : nullptr;
    }

    void insert(Data data) {
        auto new_node = std::make_unique<Node>(data);
        new_node->next = std::move(head);
        head = std::move(new_node);
        list_size++;
    }

    void insert_after(Item* item, Data data) {
        if (!item || !item->getNode()) {
            insert(data);
            return;
        }

        auto new_node = std::make_unique<Node>(data);
        new_node->next = std::move(item->getNode()->next);
        item->getNode()->next = std::move(new_node);
        list_size++;
    }

    bool erase_first() {
        if (!head) return false;

        head = std::move(head->next);
        list_size--;
        return true;
    }

    bool erase_next(Item* item) {
        if (!item || !item->getNode() || !item->getNode()->next) {
            return erase_first();
        }

        item->getNode()->next = std::move(item->getNode()->next->next);
        list_size--;
        return true;
    }

    bool empty() const { return !head; }
    size_t size() const { return list_size; }

    bool contains(const Data& data) const {
        Node* current = head.get();
        while (current) {
            if (current->data == data) return true;
            current = current->next.get();
        }
        return false;
    }

    class Iterator {
    private:
        Item* current;

    public:
        Iterator(Item* start = nullptr) : current(start) {}
        ~Iterator() {
            if (current) {
                Item::deleteItem(current);
            }
        }

        bool hasNext() const { return current != nullptr; }

        Data& next() {
            if (!current) throw std::runtime_error("No more items");
            Data& result = current->data();
            Item* next_item = current->next();
            Item::deleteItem(current);
            current = next_item;
            return result;
        }

        Iterator(const Iterator&) = delete;
        Iterator& operator=(const Iterator&) = delete;

        Iterator(Iterator&& other) noexcept : current(other.current) {
            other.current = nullptr;
        }

        Iterator& operator=(Iterator&& other) noexcept {
            if (this != &other) {
                if (current) Item::deleteItem(current);
                current = other.current;
                other.current = nullptr;
            }
            return *this;
        }
    };

    Iterator getIterator() const {
        return Iterator(first());
    }

    Iterator getIterator() {
        return Iterator(first());
    }
};

#endif