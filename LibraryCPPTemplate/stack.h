#ifndef STACK_H
#define STACK_H
#include "list.h"


template <typename Data> class Stack
{
public:
    // ������� ������ ����
    Stack()
    {
        list = new List<Data>;
    }

    // ������� ����
    ~Stack()
    {
        delete list;
    }

    // �������� ������ � ������� ����� �����
    // Should be O(1) on average
    void push(Data data)
    {
        list->insert(data);
    }

    // ��������� ��������� ������� �� �����
    Data get()
    {
       return list->first()->data();
    }

    // ������� ��������� ������� �� �����
    // Should be O(1)
    void pop()
    {
        if (!empty()){
            list->erase(list->first());
        }
    }

    // ���������� �������� true, ���� ���� ����
    bool empty()
    {
        return !list->first();
    }

private:
    // private data should be here
    List<Data> *list;
};

#endif