//
// Created by Alex on 14.01.2021.
//

#ifndef DOLBOYBLAB_LIST_H
#define DOLBOYBLAB_LIST_H
#include <cstdio>
#include <iostream>

template<typename T>
struct node
{
    T data;
    struct node *next;
    explicit node(T data, node<T> *next = nullptr) : data(data), next(next){}
    node() = default;
};

template<typename T>
class List {
private:
    node<T> *head,*tail;
public:
    List()
    {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(const T& n)
    {
        auto *tmp = new node<T>();
        tmp->data = n;
        tmp->next = nullptr;

        if(head == nullptr)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }

    void insert(const T& n){
        auto *tmp = new node<T>();
        tmp->data = n;
        tmp->next = nullptr;

        if(head == nullptr)
        {
            head = tmp;
            tail = tmp;
        } else {
            tmp->next = head;
            head = tmp;
        }
    }

    void insert_after(const node<T>* element, const T& value){
        node<T>* current = head;
        while(current != element){
            if (current->next == nullptr){
                throw std::invalid_argument("There is no element in list");
            }
            current = current->next;
        }
        auto* new_node = new node<T>();
        new_node->data = value;
        new_node->next = current->next;
        current->next = new_node;
        if (current == tail){
            tail = new_node;
        }
        new_node = nullptr;
    }

    const T& last(){
        return tail->data;
    }

    const T& first(){
        return head->data;
    }

    const node<T>* first_node(){
        return head;
    }

    void set(const size_t& index, const T& value) {
        node<T>* current = head;
        for (size_t i = 0; i != index; ++i) {
            if (current->next != nullptr){
                current = current->next;
            } else {
                throw std::invalid_argument("Index out of bounds");
            }
        }
        current->data = value;
    }

    T& next(const T& element){
        node<T>* current = head;
        while(current->data != element){
            if (current->next == nullptr){
                throw std::invalid_argument("There is no element in list");
            }
            current = current->next;
        }
        return current->next->data;
    }

    void drop_last(){
        if (tail != nullptr && head !=nullptr) {
            if (tail == head) {
                delete tail;
                delete head;
            } else {
                auto* current = head;
                while (current->next != tail) {
                    current = current->next;
                }
                current->next = nullptr;
                delete tail;
                tail = current;
            }
        }
    }

    void drop_first(){
        if (tail != nullptr && head !=nullptr) {
            if (tail == head) {
                delete tail;
                delete head;
                tail = nullptr;
                head = nullptr;
            } else {
                auto* current = head;
                head = head->next;
                delete current;
            }
        }
    }

    void erase_at(const size_t& index){
        if (index == 0) {
            drop_first();
        } else {
            node<T>* current = head;
            for (size_t i = 1; i < index; ++i) {
                if (current->next != nullptr){
                    current = current->next;
                } else {
                    throw std::invalid_argument("Index out of bounds");
                }
            }
            auto* next = current->next;
            if (next == tail){
                current->next = nullptr;
                tail = current;
                delete next;
            } else {
                current->next = next->next;
                delete next;
            }

        }
    }

    void erase(const T& value) {
        if (head->data == value){
            drop_first();
        } else {
            node<T>* current = head;
            while(current->next->data != value){
                if (current->next->next == nullptr){
                    throw std::invalid_argument("There is no element in list");
                }
                current = current->next;
            }
            auto* next = current->next;
            if (next == tail){
                current->next = nullptr;
                tail = current;
                delete next;
            } else {
                current->next = next->next;
                delete next;
            }
        }
    }

    void print(){
        std::cout << "[";
        node<T>* current = head;
        while (current != nullptr){
            std::cout << " " << current->data;
            if (current->next != nullptr) {
                std::cout << ",";
            }
            current = current->next;
        }
        std::cout << "]" << std::endl;
    }

    ~List(){
        auto* current = head;
        tail = nullptr;
        while (current != nullptr) {
            head = head->next;
            delete current;
            current = head;
        }
    }
};
#endif //DOLBOYBLAB_LIST_H
