#include <stdlib.h>
#include "list.h"

typedef struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
} ListItem;

typedef struct List {
    ListItem* head;
    ListItem* tail;
    FFree* free_func;
} List;

List *list_create(FFree f)
{
    List* new_list = (List*)malloc(sizeof(List));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->free_func = f;

    return new_list;
}

void list_delete(List *list)
{
   if(list == NULL) return;

   ListItem* current = list->head;

   while(current != NULL){
        ListItem* next = current->next;

        if(list->free_func != NULL)
            list->free_func((void*)current->data);
        
        free(current);

        current = next;
   }
   free(list);
}

ListItem *list_first(List *list)
{
    if (list == NULL) {
        return NULL;
    }
    
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    if (item == NULL) {
        return (Data)0;
    }
    
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if(item == NULL){
        return NULL;
    }
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if(item == NULL){
        return NULL;
    }
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    if (list == NULL) {
        return NULL;
    }
    
    ListItem* new_item = (ListItem*)malloc(sizeof(ListItem));  
    if(new_item == NULL){
        return NULL;
    }

    new_item->data = data;
    new_item->next = list->head;
    new_item->prev = NULL;

    if(list->head != NULL){
        list->head->prev = new_item;
    }
    else{
        list->tail = new_item;
    }
    
    list->head = new_item;  
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if(list==NULL){
        return NULL;
    }

    if(item==NULL){
        return list_insert(list,data);
    }
    
    ListItem* new_item = (ListItem*)malloc(sizeof(ListItem));
    if(new_item == NULL){
        return NULL;
    }

    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;

    item->next = new_item;

    if(new_item->next != NULL){
        new_item->next->prev = new_item;
    }
    else{
        list->tail = new_item;
    }
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if(list ==NULL || list->head == NULL){
        return NULL;
    }

    ListItem* to_delete = list->head;
    ListItem* new_first = list->head->next;

       if (list->free_func != NULL) {
        list->free_func((void*)to_delete->data);
    }
    
    // Обновляем связи
    if (new_first != NULL) {
        // Если есть второй элемент, он становится первым
        new_first->prev = NULL;
        list->head = new_first;
    } else {
        // Список стал пустым
        list->head = NULL;
        list->tail = NULL;
    }
    
    // Освобождаем память удаленного элемента
    free(to_delete);
    
    // Возвращаем новый первый элемент (может быть NULL)
    return new_first;
}


ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == NULL) {
        return NULL;
    }
    
   
    if (item == NULL) {
        return list_erase_first(list);
    }
    
    
    if (item->next == NULL) {
        return NULL;  
    }
    
    
    ListItem* to_delete = item->next;          
    ListItem* after_deleted = to_delete->next;  
    
    
    if (list->free_func != NULL) {
        list->free_func((void*)to_delete->data);
    }
    
    
    item->next = after_deleted;  
    
    if (after_deleted != NULL) {
        
        after_deleted->prev = item;
    } else {
        
        list->tail = item;
    }
    
    free(to_delete);
    
    
    return after_deleted;
}