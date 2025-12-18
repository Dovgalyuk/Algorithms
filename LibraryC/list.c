#include "list.h"
#include <stdlib.h>

typedef struct ListItem {
  Data data;
  struct ListItem *next;
} ListItem;

typedef struct List {
  ListItem *head;
  ListItem *tail;
  FFree *free_fn;
} List;

List *list_create(FFree f) {
  List *list = malloc(sizeof(List));
  if (list == NULL) {
    return NULL;
  }
  list->head = NULL;
  list->tail = NULL;
  list->free_fn = f;
  return list;
}

void list_delete(List *list) {
  if (list == NULL) {
    return;
  }

  ListItem *current = list->head;
  while (current != NULL) {
    ListItem *next = current->next;

    if (list->free_fn != NULL) {
      list->free_fn((void *)current->data);
    }

    free(current);
    current = next;
  }

  free(list);
}

ListItem *list_first(List *list) {
  if (list == NULL) {
    return NULL;
  }
  return list->head;
}

ListItem *list_last(List *list) {
  if (list == NULL) {
    return NULL;
  }
  return list->tail;
}

Data list_item_data(const ListItem *item) {
  if (item == NULL) {
    return (Data)0;
  }
  return item->data;
}

ListItem *list_item_next(ListItem *item) {
  if (item == NULL) {
    return NULL;
  }
  return item->next;
}

ListItem *list_item_prev(ListItem *item) {
  (void)item;
  return NULL;
}

ListItem *list_insert(List *list, Data data) {
  if (list == NULL) {
    return NULL;
  }

  ListItem *new_item = malloc(sizeof(ListItem));
  if (new_item == NULL) {
    return NULL;
  }

  new_item->data = data;
  new_item->next = list->head;
  list->head = new_item;

  if (list->tail == NULL) {
    list->tail = new_item;
  }

  return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
  if (list == NULL) {
    return NULL;
  }

  if (item == NULL) {
    return list_insert(list, data);
  }

  ListItem *new_item = malloc(sizeof(ListItem));
  if (new_item == NULL) {
    return NULL;
  }

  new_item->data = data;
  new_item->next = item->next;
  item->next = new_item;

  if (item == list->tail) {
    list->tail = new_item;
  }

  return new_item;
}

ListItem *list_erase_first(List *list) {
  if (list == NULL || list->head == NULL) {
    return NULL;
  }

  ListItem *to_delete = list->head;
  ListItem *next = to_delete->next;

  if (list->free_fn != NULL) {
    list->free_fn((void *)to_delete->data);
  }

  free(to_delete);

  list->head = next;

  if (next == NULL) {
    list->tail = NULL;
  }

  return next;
}

ListItem *list_erase_next(List *list, ListItem *item) {
  if (list == NULL) {
    return NULL;
  }

  if (item == NULL) {
    return list_erase_first(list);
  }

  if (item->next == NULL) {
    return NULL;
  }

  ListItem *to_delete = item->next;
  ListItem *next = to_delete->next;

  if (list->free_fn != NULL) {
    list->free_fn((void *)to_delete->data);
  }

  free(to_delete);

  item->next = next;

  if (to_delete == list->tail) {
    list->tail = item;
  }

  return next;
}

ListItem *list_insert_tail(List *list, Data data) {
  if (list == NULL) {
    return NULL;
  }

  return list_insert_after(list, list->tail, data);
}
