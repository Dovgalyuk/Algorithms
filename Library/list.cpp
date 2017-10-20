#include <stdlib.h>
#include "list.h"
#include <iostream>

struct ListItem
{
	int  data;
	
	ListItem* next;
	ListItem* prev;
	ListItem() 
	{
		data = NULL;
		next = nullptr;
		prev = nullptr;
	}
};

struct List
{
	ListItem * item;
	int count = 0;
	ListItem * last;
	
};




// создание списка
List *list_create()
{
	List *bufferlist = new List;
	
    return bufferlist;
}

// удаление списка
void list_delete(List *list)
{
	delete list;
}

// получить первый элемент списка
ListItem *list_first(List *list)
{
	if (list->count == 0)
		return 0;
	else
		return list->item;
}

// извлечь данные из элемента списка
int list_item_data(ListItem *item)
{
    return item->data;
}

// получить следующий элемент списка
ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

// получить предыдущий элемент списка
ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

// вставить данные в начало списка
ListItem *list_insert(List *list, int data)
{
	ListItem *buffer = new ListItem;
	buffer->data = data;
	if (list->count == 0) {
		buffer->next = 0;
		list->last = buffer;
		buffer->prev = 0;
	
	} else {
	buffer->next = list->item;
	list->item->prev = buffer;	
	}
	
	
	list->count++;
	list->item = buffer;
	return list->item;

}

// вставить данные после заданного элемента
ListItem *list_insert_after(List *list, ListItem *item, int data)
{
	if (item == list->last) 
	{
		ListItem * buffer = new ListItem;
		buffer->data = data;
		buffer->prev = list->item;
		buffer->next = 0;
		list->item->next = buffer;
		list->last = buffer;
		list->count++;
		return list->item;
	}
	else {
		while (list->item != item)
			list->item = list->item->next;



		ListItem * buffer = new ListItem;
		buffer->data = data;
		buffer->prev = item;
		buffer->next = item->next;
		item->next = buffer;
		item = buffer->next;
		item->prev = buffer;

		list->count++;
		return list->item;
	}
}

// удалить заданный элемент списка
ListItem *list_erase(List *list, ListItem *item)
{
	
	while (list->item != item)
		list->item = list->item->next;
	ListItem * buf = new ListItem;
	buf = list->item;
	if (list->item->prev != 0)
	{
		list->item = list->item->prev;
		list->item->next = buf->next;
		list->item = list->item->next;
		list->item->prev = buf->prev;
	}
	else 
	{
		if (list->item->next != 0)
		list->item = list->item->next;
		else {
			list->count = -1;
			list->item->data = 0;
		}
		list->item->prev = 0;
		
	}
		
	list->count--;
	
	return list->item;
}

// удалить элемент списка, следующий за заданным
ListItem *list_erase_next(List *list, ListItem *item)
{
	
	while (list->item != item)
	{
		list->item = list->item->next;
	}
	list->item = list->item->next;

	list->item->prev->next = list->item->next;
	list->item->next->prev = list->item->prev;
	list->count--;
	return list->item;
}

// получить последний элемент списка
ListItem *list_last(List *list) 
{
	
	return list->last;

}

/*

while (list->item->prev != 0)
list->item = list->item->prev;

*/