#include <cstddef>
#include "list.h"

struct ListItem {
    Data data_;
    ListItem *next_;
    ListItem *prev_;
};

struct List {
    ListItem *head_;
};

List *list_create() {
    List *list = new List;
    list->head_ = nullptr;
    return list;
}

void list_delete(List *list) {
    while (list->head_ != nullptr) {
        list_erase(list, list->head_);
    }
    delete list;
}

ListItem *list_first(List *list) {
    return list->head_;
}

Data list_item_data(const ListItem *item) {
    return item->data_;
}

ListItem *list_item_next(ListItem *item) {
    return item->next_;
}

ListItem *list_item_prev(ListItem *item) {
    return item->prev_;
}

ListItem *list_insert(List *list, Data data) {
    ListItem *node = new ListItem;
    node->data_ = data;
    node->prev_ = nullptr;
    if (list->head_ == nullptr) {
        node->next_ = nullptr;
        list->head_ = node;
    } else {
        node->next_ = list->head_;
        list->head_->prev_ = node;
    }
    list->head_ = node;
    return node;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    ListItem *node = new ListItem;
    if (list->head_ == nullptr) {
        node = list_insert(list, data);
        return node;
    }
    node->data_ = data;
    node->prev_ = item;
    if (item->next_ == nullptr) {
        node->next_ = nullptr;
    } else {
        node->next_ = item->next_;
        item->next_->prev_ = node;
    }
    item->next_ = node;
    return node;
}

ListItem *list_erase(List *list, ListItem *item) {
    ListItem* prev_node = nullptr;

    if (list->head_ == nullptr)
        return prev_node;
    if (item->prev_ != nullptr){
        item->prev_->next_ = item->next_;
        prev_node = item->prev_;
    }
    else
        list->head_ = item->next_;
    if (item->next_ != nullptr){
        item->next_->prev_ = item->prev_;
        prev_node = item->prev_;
    }
    delete item;
    return prev_node;
}

ListItem *list_erase_next(List *list, ListItem *item) {
    if (item->next_ != nullptr)
        return list_erase(list, item->next_);
    return item;
}
