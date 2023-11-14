#pragma once

#include <iostream>
#include <string>
#include "array.h"
#include <utility> // ��� ������������� std::pair

// ����� HashTable ��� ���������� ���-�������
class HashTable {
public:
    // ���������� ��������� ��� �������� ��������� �������
    struct Element {
        std::string key;     // ����
        std::string value;   // ��������
        bool deleted;        // ���� ���������� ��������
        // ����������� �� ���������
        Element() : key(""), value(""), deleted(false) {}
        // ����������� � �����������
        Element(std::string key, std::string value, bool deleted = false) : key(key), value(value), deleted(deleted) {}
    };

private:
    Array<Element>* elements; // ������ ��������� ���-�������
    int capacity;             // ����������� �������
    int size;                 // ������� ���������� ���������
    int count_deleted = 0;    // ������� ��������� ���������

    // ������ ���-������� (������)
    static int FirstHashFunction(const std::string& key, int capa) {
        // ������������� ���������� hash, ������� ����� �������������� ��� ���������� ���-��������.
        int hash = 0;
        unsigned long long unique_value = 1;

        // ���� �������� �� ������� ������� � ������ key.
        for (size_t i = 0; key[i]; i++) {
            // ��� ������� ������� ����� ����������� ���-��������.
            // ������ ������ ������ �� �������� �������� ����,
            // ������� ����� ������� �� ������ ����������� ���-������� (capa),
            // ����� �������������, ��� ��� ����� � �������� ������� �������.
            hash = (hash * unique_value + key[i]) % capa;
        }
        return hash % capa;
    }

    // ������ ���-������� (������ � ������������ ����������� ����������� ��������)
    static int SecondHashFunction(const std::string& key, int capa) {
        // ������������� ���-�������� �����.
        int hash = 0;

        // ��������� ���������� �������� ��������� ����� 1. � ���� ������� ��� �������� �����,
        // ��������� ��� ���������� � ������ ��������, � ������� �� FirstHashFunction.
        unsigned long long unique_value = 1;

        // �������� �� ������� ������� �����.
        for (size_t i = 0; key[i]; i++) {
            // ��������� ���-��������, ���������� ������� ���, ASCII �������� �������
            // � ������� ���������� �������� ���������. �������� ������ �����������, ��� ��� ���������
            // � �������� ������� �������.
            hash = (hash * unique_value + key[i]) % capa;

            // ����� 27 ������� �� ��������, ������ ��� ������ ���� ������� ������,
            // ����� ������ ���������� ������� ������������� ���-��������.
            unique_value *= 27;
        }

        // ��������� ������������� ���-�������� �� ������ ����������� �������, ����� ���������, ��� ��� � �������� ���������� ������.
        int result = hash % capa;

        // ����� �������������, ��� ��� � ����� �������� ����������� �� ����� ���� � �� �������� ������� ������� �������,
        // ��� ����� ��� ����������� ������������ ���� ������ �������, ��������� ��������������, ����� ���� ��������.
        // ���� ��������� ������, ��������� 1, ����� ������� ��� ��������. ����� �������, ������ ���-������� ������� �� ������ ����
        // (��� ������� �� � ���������� �������� � ������������������ ������������) � ��������� ������ ������������� ����.
        if (result % 2 == 0) return result + 1;
        return result;
    }

    // �������� ������������� �������
    bool check_capacity() {
        return this->size + this->count_deleted >= this->capacity / 2;
    }

    //// �������� ��� ����������� ������� �������� � ���-�������
    //static int algorithm(const std::string& key, Array<Element>* in_elements, int capa, bool& not_found) {
    //    // ���������� ������ ���-������� ��� ����������� ���������� ������� ��������
    //    int first_hash = FirstHashFunction(key, capa);
    //    int final_hash = first_hash;

    //    // ���� ��������� ������� ������ � ������� �� ������� ��� ��������, ��������� �
    //    if (!in_elements->get(final_hash)->key.empty() && !in_elements->get(final_hash)->deleted) {
    //        // ���� �� ���� ������� � �� ������������ �� ����� �������, ���������� not_found � ���������� ������
    //        if (not_found && (key == in_elements->get(final_hash)->key)) {
    //            not_found = false;
    //            return final_hash;
    //        }

    //        // ������������ ������ � ������� ������ ���-������� ��� ���������� ��������
    //        int second_hash = SecondHashFunction(key, capa);

    //        // �������� ����������� ������� ��� ���������� ������ �������
    //        int iter = 1;

    //        // ��������� ������� ����������� ��� ���������� ���������� ������� ��� ������� � ������� ������
    //        final_hash = (first_hash + iter * second_hash) % capa;

    //        // ��������� �� ��� ���, ���� �� ����� ��������� ������ ��� ������ � ������
    //        while (!in_elements->get(final_hash)->key.empty() && !in_elements->get(final_hash)->deleted) {
    //            // ���� ����� ������ � ������� ������ � �� � ������ ������, ���������� not_found � ���������� ������
    //            if (not_found && key == in_elements->get(final_hash)->key) {
    //                not_found = false;
    //                return final_hash;
    //            }
    //            // ����������� �������� � ���� ��������� ������
    //            iter++;
    //            final_hash = (first_hash + iter * second_hash) % capa;
    //        }
    //    }
    //    // ���������� ������, ���� ����� ��������� ����� ������� ��� ��� ��������� ������� � ������� ������
    //    return final_hash;
    //}

    // �������� ��� ����������� ������� �������� � ���-�������
    static int algorithm(const std::string& key, Array<Element>* in_elements, int capa, bool& not_found) {
        // ��������� ��������� ������ � ������� ������ ���-�������
        int first_hash = FirstHashFunction(key, capa);
        // ��������� ��� ��� �������� ����������� � ������� ������ ���-�������
        int second_hash = SecondHashFunction(key, capa);

        // �������� ��� ������ ���-������� ��� ���������
        int iter = 0;
        // ������ ������� ������������ ���������� ��������, ��������������� -1 (���������� ������ ��������)
        int first_deleted_index = -1;

        // ����, ������� ������������ �� ���������� ����������� �������
        while (true) {
            // ��������� ������, ��������� ������� �����������
            int final_hash = (first_hash + iter * second_hash) % capa;
            // �������� ������� �� ������������ �������
            Element* elem = in_elements->get(final_hash);

            // ���� ������� ������ � �� ��� �� �������� ������ ���������� ��������
            if (elem->deleted && first_deleted_index == -1) {
                first_deleted_index = final_hash;
            }

            // ���� ����� ������ ������ ��� ������ � ������� ������
            if (elem->key.empty() || elem->key == key) {
                // ���� ���� �� ������ � ���� ������ ���������� ��������, ���������� ��� ������
                if (elem->key.empty() && first_deleted_index != -1 && not_found) {
                    return first_deleted_index;
                }

                // ������������� ���� not_found � ����������� �� ����, ������ �� ������
                not_found = elem->key.empty();
                return final_hash;
            }

            // ����������� �������� ��� ���������� ���� � ������������
            iter++;
        }
    }

    // ������� ���������� �������
    void resize() {
        // ��������� ������ ����������� �������.
        int old_capacity = this->capacity;

        // ����������� ����������� ������� � ������ ����.
        this->capacity *= 4;

        // ������� ����� ������ ��������� � ����� ������������.
        Array<Element>* new_elements = new Array<Element>(this->capacity);

        // ���������� �������� ������� �������.
        for (int i = 0; i < old_capacity; ++i) {
            // �������� ������� �� �������.
            Element* elem = this->elements->get(i);
            // ���� ������� �� ������ � �� ��� ������...
            if (!elem->key.empty() && !elem->deleted) {
                // ������������� ���� not_found � ������, ��� ��������� �� ��, ��� �� ��������� �������, � �� ���� ���.
                bool not_found = true;
                // ������� ����� ������ ��� �������� � ����� ������� � ������� ��������� �������� �����������.
                int index = algorithm(elem->key, new_elements, this->capacity, not_found);
                // ��������� ������� � ����� �������.
                new_elements->set(index, *elem);
            }
        }

        // ������� ������ ������ ���������.
        delete this->elements;
        // ��������� ����� ������ ��������� �������.
        this->elements = new_elements;
        // �������� ������� ��������� ���������, ��� ��� ��� �� ����������� � ����� �������.
        this->count_deleted = 0;
    }

    // ����� ������� �������� �� �����
    int find_index(const std::string& key) {
        // �������������� ����, ������� ����� ���������, ������ �� �������.
        bool not_found = true;

        // ��������� �������� �������� ����������� ��� ����������� ������� ��������.
        // ���� �������� ��������� ��������� �������� � ��������� ����� ������,
        // ��� ������ ���������� ������� � ������ ������, ���� �� ����������.
        int hash_index = algorithm(key, this->elements, this->capacity, not_found);

        // ���������, �� ��� �� ������� ������� ��� �� ��������� � ���������� ������ ���������.
        // ����� ���������, �� ��� �� ������� � ���� �������� ������� ��� ���������.
        // ���� ������� �� ������ ��� ������� ��� ���������, ���������� -1, ��� ��������� �� ���������� ��������.
        if (not_found || this->elements->get(hash_index)->deleted) return -1;

        // ���� ������� ������ � �� �� ������� ��� ���������, ���������� ��� ������.
        return hash_index;
    }

public:
    // ����������� �� ���������
    HashTable()
        : elements(new Array<Element>(16)), capacity(16), size(0), count_deleted(0) {}

    // ����������� �����������
    HashTable(const HashTable& other)
        : elements(new Array<Element>(other.capacity)), capacity(other.capacity), size(other.size), count_deleted(other.count_deleted) {
        // ����������� ���������
        for (int i = 0; i < capacity; ++i) {
            Element* elem = other.elements->get(i);
            if (!elem->key.empty()) {
                elements->set(i, *elem);
            }
        }
    }

    // �������� ������������
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

    // ����������
    ~HashTable() {
        delete elements;
    }

    // ���������� ��������
    void add(const std::string& key, const std::string& value) {
        // ����, ����������� �� ��, ��� ������� ��� ������� ��� �� �������.
        bool not_found = true;

        // ��������� ���-������� ��� ����� � ������� ��������� �������� �����������.
        int final_hash = algorithm(key, this->elements, this->capacity, not_found);

        // ��������� ����� ������� � ���������� ����� � ������ elements.
        // ������� ��������� �� ����� � �������������� ������������ Element.
        elements->set(final_hash, Element(key, value));

        // ����������� ������ ���-������� (���������� �������� ���������).
        this->size++;

        // ���������, �� ��������� �� ����� �������� ������� � ���������� ��������� ��������� �������� �����������.
        // ���� ��� ���, �� ���������� ��������� ������ ���-������� ��� ����������� ������������� ��������.
        if (check_capacity()) {
            // �������� ����� resize ��� ���������� ����������� ���-������� � ��������������� ���������.
            resize();
        }
    }

    // �������� ��������
    void del(const std::string& key) {
        // ���� ������ ��������, ������� ������������� �����.
        // find_index ���������� -1, ���� ������� �� ������.
        int index_to_delete = find_index(key);

        // ���� ������ �� ��� ������, �� �������� � ����� ������ ��� � �������,
        // � �� ������ ������� �� �������.
        if (index_to_delete == -1) return;

        // ���� ������� ������, �� ������������� ��� ������ ��� "���������".
        // ����� �� ���������� ���������� �������� �������� �� �������,
        // �� ���� �������� ��� ��� ���������, ������� ���� 'deleted' �� true.
        this->elements->get(index_to_delete)->deleted = true;

        // ����������� ������� ��������� ���������.
        // ��� �������� ������������ � ������� check_capacity ��� �����������,
        // ����� ����� ������������� ���������� �������.
        this->count_deleted++;
    }

    // ����� ��������
    std::pair<bool, std::string> find(const std::string& key) {
        // �������� ����� find_index ��� ��������� ������� �������� �� �����.
        int index = find_index(key);

        // ���� find_index ���������� -1, ������� � ����� ������ �� ������ ��� ������.
        // � ���� ������ ���������� ����, ������ ������� ������� - false, ������ - ������ ������.
        if (index == -1) return std::make_pair(false, "");

        // ���� ������� ������, ���������� ����, ��� ������ ������� - true,
        // � ������ - ��������, ��������� � ������.
        return std::make_pair(true, elements->get(index)->value);
    }
};