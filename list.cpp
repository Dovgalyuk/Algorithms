#include <stdlib.h>
#include "list.h"

struct ListItem //Estrutura de n—s
{
	int item;
	ListItem *next;
	ListItem *prev;

};

struct List //Estrutura da nossa lista
{
	ListItem *head; // Ponteiro no ’n’cio da lista
	ListItem *tail; // Ponteiro no fim da lista
};

List* list_create()  // Cria um exemplar da lista
{
	List *tmp = new List;

	tmp->head = NULL;
	tmp->tail = NULL;
    return tmp;
}

void list_delete(List *list) // Limpa a lista
{
	ListItem *tmp = (list)->head;
	ListItem *next = NULL;
    
	while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(list);
}

// 
ListItem *list_first(List *list)
{
	return list->head;
}
 
int list_item_data(ListItem *item)
{
    return item->item;
}

// 
ListItem *list_item_next(ListItem *item)
{
    return item->next;
}


ListItem *list_item_prev(ListItem *item)
{
	return item->prev;
}
    
 
ListItem *list_insert(List *list, int data)
{
	ListItem *tmp = new ListItem ;
	
	if (tmp == NULL) {
		exit(1);
	}
	tmp->item = data;
	tmp->prev = NULL;
	tmp->next = list->head;
	if (list->head) {
		list->head->prev = tmp;
	}
	list->head = tmp;

	if (list->tail == NULL) {
		list->tail = tmp;
	}
	
    return tmp;
}


// 
ListItem *list_insert_after(List *list, ListItem *item, int data)
{
	ListItem *ins = new ListItem;
	if (item == NULL)
	{
		exit(5);
	}
	ins->item = data;
	ins->prev = item;
	ins->next = item->next;
	if (item->next)
	{
		item->next->prev = ins;
	}
	item->next = ins;
	
	
    return NULL;
}

// 
ListItem *list_erase(List *list, ListItem *item)
{
	if (item->next) {
		item->next->prev = item->prev;
	}

	if (!item->prev) {
		list->head =item->next;
		
    }
    
    free(item);
    return item;
}

// 
ListItem *list_erase_next(List *list, ListItem *item){
    return NULL;
}

