
#ifndef 
#define 

#include <cstdio>
#include <iostream>

template<typename T>
struct node
{
    T data;
    struct node *next;
};

template<typename T>
class SinglyLinkedList {
private:
    node<T> *head,*tail;
public:
    SinglyLinkedList()
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

    void add(const T& n){
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

    const T& get(const size_t& index){
        node<T>* current = head;
        for (size_t i = 0; i != index; ++i) {
            if (current->next != nullptr){
                current = current->next;
            } else {
                throw std::invalid_argument("Index out of bounds");
            }
        }
        return current->data;
    }

    const T& last(){
        return tail->data;
    }

    const T& first(){
        return head->data;
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

    T& operator[](const size_t& index){
        node<T>* current = head;
        for (size_t i = 0; i != index; ++i) {
            if (current->next != nullptr){
                current = current->next;
            } else {
                throw std::invalid_argument("Index out of bounds");
            }
        }
        return current->data;
    }

    T& operator[](const size_t& index) const {
        node<T>* current = head;
        for (size_t i = 0; i != index; ++i) {
            if (current->next != nullptr){
                current = current->next;
            } else {
                throw std::invalid_argument("Index out of bounds");
            }
        }
        return current->data;
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

    ~SinglyLinkedList(){
        auto* current = head;
        tail = nullptr;
        while (current != nullptr) {
            head = head->next;
            delete current;
            current = head;
        }
    }
};



#endif
