#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <stdbool.h>

static int tp = 0;
static int tf = 0;

void assert(bool expr, char* msg){
    if (expr) tp++;
    else tf++;
    printf(msg);
    printf("\n");
}

int main() {
    List *list = list_create(NULL);
    assert(list != NULL, "list created empty");
    assert(list_first(list) == NULL, "list created empty");
    assert(list_last(list) == NULL, "list created empty");
    list_delete(list);

    list = list_create(NULL);
    list_insert(list, (Data)10);
    list_insert(list, (Data)20);
    list_insert(list, (Data)30);
    assert(list_item_data(list_first(list)) == 30, "last insert puts at head");
    assert(list_item_data(list_last(list)) == 10, "first insert puts at tail");
    list_delete(list);

    list = list_create(NULL);
    list_insert(list, (Data)10);
    ListItem *first = list_first(list);
    list_insert_after(list, first, (Data)20);
    assert(list_item_data(list_last(list)) == 20, "insert_after works");
    list_delete(list);
    
    list = list_create(NULL);
    list_insert(list, (Data)10);
    list_insert(list, (Data)20);
    list_erase_first(list);
    assert(list_item_data(list_first(list)) == 10, "erase_first works");
    list_delete(list);
    
    list = list_create(NULL);
    list_insert(list, (Data)10);
    list_insert(list, (Data)20);
    list_insert(list, (Data)30);
    list_erase_next(list, list_first(list));
    assert(list_item_data(list_item_next(list_first(list))) == 10, "erase_next works");
    list_delete(list);
    
    assert(list_first(NULL) == NULL, "list_first(NULL) safe");
    assert(list_last(NULL) == NULL, "list_last(NULL) safe");
    assert(list_item_next(NULL) == NULL, "list_item_next(NULL) safe");
    assert(list_item_prev(NULL) == NULL, "list_item_prev(NULL) safe");
    
    list = list_create(NULL);
    list_insert(list, (Data)10);
    list_insert_after(list, NULL, (Data)20); 
    assert(list_item_data(list_first(list)) == 20, "insert_after(NULL) inserts first");
    list_delete(list);
    
    printf("\nResults: %d passed, %d failed\n", tp, tf);
    return tf > 0 ? 1 : 0;
}
