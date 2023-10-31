#pragma once

#include <iostream>
#include <string>
#include "array.h"
#include <utility> // для std::pair


class HashTable {
public:
    struct Element {
        std::string key;
        std::string value;
        bool deleted;
        Element() : key(""), value(""), deleted(false) {}
        Element(std::string key, std::string value, bool deleted = false) : key(key), value(value), deleted(deleted) {}
    };

private:
    Array<Element>* elements;
    int capacity;
    int size;
    int count_deleted = 0;

    static int FirstHashFunction(const std::string& key, int capa) {
        int hash = 0;
        unsigned long long unique_value = 1;
        for (size_t i = 0; key[i]; i++) {
            hash = (hash * unique_value + key[i]) % capa;
        }
        return hash % capa;
    }

    static int SecondHashFunction(const std::string& key, int capa) {
        int hash = 0;
        unsigned long long unique_value = 1;
        for (size_t i = 0; key[i]; i++) {
            hash = (hash * unique_value + key[i]) % capa;
            unique_value *= 27;
        }
        int result = hash % capa;
        if (result % 2 == 0) return result + 1;
        return result;
    }

    bool check_capacity() {
        return this->size + this->count_deleted >= this->capacity / 2;
    }

    static int algorithm(const std::string& key, Array<Element>* in_elements, int capa, bool& founded) {
        int first_hash = FirstHashFunction(key, capa);
        int final_hash = first_hash;
        if (!in_elements->get(final_hash)->key.empty() && !in_elements->get(final_hash)->deleted) {
            if (founded && (key == in_elements->get(final_hash)->key)) { founded = false; return final_hash; }
            int second_hash = SecondHashFunction(key, capa);
            int iter = 1;
            final_hash = (first_hash + iter * second_hash) % capa;
            while (!in_elements->get(final_hash)->key.empty() && !in_elements->get(final_hash)->deleted) {
                if (founded && key == in_elements->get(final_hash)->key) { founded = false; return final_hash; }
                iter++;
                final_hash = (first_hash + iter * second_hash) % capa;
            }
        }
        return final_hash;
    }

    void resize() {
        int old_capacity = this->capacity;
        this->capacity *= 4;
        Array<Element>* new_elements = new Array<Element>(this->capacity);

        for (int i = 0; i < old_capacity; ++i) {
            Element* elem = this->elements->get(i);
            if (!elem->key.empty() && !elem->deleted) {
                bool not_found = true;
                int index = algorithm(elem->key, new_elements, this->capacity, not_found);
                new_elements->set(index, *elem);
            }
        }

        delete this->elements;
        this->elements = new_elements;
        this->count_deleted = 0;
    }

    int find_index(const std::string& key) {
        bool not_found = true;
        int hash_index = algorithm(key, this->elements, this->capacity, not_found);
        if (not_found || this->elements->get(hash_index)->deleted) return -1;
        return hash_index;
    }

public:
    HashTable()
        : elements(new Array<Element>(16)), capacity(16), size(0), count_deleted(0) {}

    HashTable(const HashTable& other)
        : elements(new Array<Element>(other.capacity)), capacity(other.capacity), size(other.size), count_deleted(other.count_deleted) {
        for (int i = 0; i < capacity; ++i) {
            Element* elem = other.elements->get(i);
            if (!elem->key.empty()) {
                elements->set(i, *elem);
            }
        }
    }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            delete elements;

            capacity = other.capacity;
            size = other.size;
            count_deleted = other.count_deleted;
            elements = new Array<Element>(capacity);

            for (int i = 0; i < capacity; ++i) {
                Element* elem = other.elements->get(i);
                if (!elem->key.empty()) {
                    elements->set(i, *elem);
                }
            }
        }
        return *this;
    }

    ~HashTable() {
        delete elements;
    }

    void add(const std::string& key, const std::string& value) {
        bool not_found = true;
        int final_hash = algorithm(key, this->elements, this->capacity, not_found);
        elements->set(final_hash, Element(key, value));
        this->size++;
        if (check_capacity()) resize();
    }

    void del(const std::string& key) {
        int index_to_delete = find_index(key);
        if (index_to_delete == -1) return;
        this->elements->get(index_to_delete)->deleted = true;
        this->count_deleted++;
    }

    std::pair<bool, std::string> find(const std::string& key) {
        int index = find_index(key);
        if (index == -1) return std::make_pair(false, "");
        return std::make_pair(true, elements->get(index)->value);
    }
};