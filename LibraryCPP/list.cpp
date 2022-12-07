#include <cstddef>
#include<iostream>
#include "list.h"

struct ListItem//������� ������
{
    Data data;//������
    ListItem* next, * prev;//��������� � ���������� �������

    ListItem(Data data = NULL, ListItem* next = nullptr, ListItem* prev = nullptr) {
        this->data = data;
        this->next = next;
        this->prev = prev;

    }
};

struct List//������
{
    ListItem* Head, * Tail;//"������" � "�����"

    List() {
        this->Head = nullptr;
        this->Tail = nullptr;
    }
};

List* list_create()//������� ������
{
    return new List;
}

void list_delete(List* list)//������� ������
{
    // TODO: free items
    delete list;
}

ListItem* list_first(List* list)//���������� ������ ������� �� ������
{
    return list->Head;
}

Data list_item_data(const ListItem* item)//���������� ������ �� �������� ������
{
    if (item != nullptr) return item->data;
    else return NULL;
}

ListItem* list_item_next(ListItem* item)// ���������� ������� ������, ��������� �� ���������
{
    return item->next;
}

ListItem* list_item_prev(ListItem* item)// ���������� ���������� ������� ��� ���������� ��������.
{
    return item->prev;
}

ListItem* list_insert(List* list, Data data)// ��������� ����� ������� ������ � ������
{
    if (list->Head == nullptr) {//���� ������ ������, �� � ������ ��������� �������,������� ����� � ������� � �������
        return list->Head = list->Tail = new ListItem(data);
    }
    else {
        ListItem* elem = new ListItem(data, list->Head);//������� ������� ������� ������
        list->Head->prev = elem;//�������� ������ ��������� �� ���������� �������, ������� �������
        list->Head = elem;//������ ��������� �������, ��� ������
        return list->Head;//���������� ������ ������� ������
    }
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)// ��������� ����� ������� ������ ����� ���������� ��������
{
    if (list->Head == nullptr) {//���� ������ ����
        std::cout << "error";
    }
    else {
        ListItem* elem = new ListItem(data, item->next, item);
        item->next = elem;

        if (item != list->Tail) {
            elem->next->prev = elem;
        }
        else {
            list->Tail = elem;
        }
        return elem;
    }
    
}


ListItem* list_erase(List* list, ListItem* item)
// ������� ��������� ������� ������. ���������� ��������� �������
{
    if (list->Head == nullptr)//���� ������ ����
    {
        std::cout << "������ ����";
    }

    else if (list->Head == item && list->Tail == item)//���� ��������� ������� - ��� � ������ � �����
    {
        delete item;
        return list->Head = list->Tail = nullptr;
    }

    else if (list->Head == item) //���� ��������� ������� - ��� ������ ������
    {
        list->Head = item->next;
        list->Head->prev = nullptr;
        delete item;
        return list->Head;
    }

    else if (list->Tail == item)//���� ��������� ������� - ��� ����� ������
    {
        list->Tail = item->prev;
        list->Tail->next = nullptr;
        delete item;
        return list->Tail;
    }
        
    else 
    {
        ListItem* elem = item->next;
        item->prev->next = elem;
        elem->prev = item->prev;
        delete item;
        return elem;
    }
}


ListItem* list_erase_next(List* list, ListItem* item)// ������� ������� ������, ��������� �� ���������.
// ���������� ��������� �� ������� ����� � ���������.
{

    if (list->Tail == item) //���� ������� ����� ������,�� ��������� ������� ������
    {
        std::cout << "������. ��������� ������� ������";
    }

    else if (list->Head == nullptr)//���� ������ ����
    {
        std::cout << "������.������ ����";
    }
   
    else {
        return list_erase(list, item->next);
    }
}
