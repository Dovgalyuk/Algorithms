#include <iostream>
#include "list.h"
#include "queue.h"

using namespace std;

bool check_list()
{
    List *list = list_create();
    bool valid = list_first(list) == nullptr && list_last(list) == nullptr;
    ListItem *next = list_erase_first(list);
    valid = valid && next == nullptr;

    ListItem *second = list_insert_after(list, nullptr, 2);
    valid = valid && list_first(list) == second && list_last(list) == second;
    valid = valid && list_item_next(second) == nullptr && list_item_prev(second) == nullptr;

    ListItem *first = list_insert(list, 1);
    ListItem *last = list_insert_after(list, second, 3);
    ListItem *middle = list_insert_after(list, first, 4);
    int expected[4] = {1, 4, 2, 3};

    ListItem *item = list_first(list);
    for (int i = 0; i < 4; ++i)
    {
        valid = valid && item != nullptr && list_item_data(item) == expected[i];
        item = list_item_next(item);
    }
    valid = valid && item == nullptr;

    item = list_last(list);
    for (int i = 3; i >= 0; --i)
    {
        valid = valid && item != nullptr && list_item_data(item) == expected[i];
        item = list_item_prev(item);
    }
    valid = valid && item == nullptr;

    next = list_erase_next(list, middle);
    valid = valid && next == last && list_item_prev(last) == middle;
    next = list_erase_next(list, last);
    valid = valid && next == nullptr && list_last(list) == last;
    next = list_erase_next(list, nullptr);
    valid = valid && next == middle && list_first(list) == middle;
    valid = valid && list_item_prev(middle) == nullptr;
    next = list_erase_next(list, middle);
    valid = valid && next == nullptr && list_first(list) == middle && list_last(list) == middle;
    valid = valid && list_item_next(middle) == nullptr;
    next = list_erase_first(list);
    valid = valid && next == nullptr && list_first(list) == nullptr && list_last(list) == nullptr;

    list_insert(list, 7);
    valid = valid && list_item_data(list_first(list)) == 7;
    list_insert(list, 8);
    list_delete(list);
    return valid;
}

bool check_queue()
{
    Queue *queue = queue_create();
    bool valid = queue_empty(queue) && queue_get(queue) == 0;
    queue_remove(queue);
    queue_insert(queue, 1);
    queue_insert(queue, 2);
    valid = valid && queue_get(queue) == 1;
    queue_remove(queue);
    queue_insert(queue, 3);
    valid = valid && queue_get(queue) == 2;
    queue_remove(queue);
    valid = valid && queue_get(queue) == 3;
    queue_remove(queue);
    valid = valid && queue_empty(queue);

    for (int i = 0; i < 10000; ++i)
        queue_insert(queue, i);

    for (int i = 0; i < 10000; ++i)
    {
        valid = valid && !queue_empty(queue) && queue_get(queue) == i;
        queue_remove(queue);
    }

    valid = valid && queue_empty(queue);
    queue_insert(queue, 7);
    valid = valid && queue_get(queue) == 7;
    queue_delete(queue);
    return valid;
}

int main()
{
    bool list_valid = check_list();
    bool queue_valid = check_queue();
    if (!list_valid || !queue_valid)
    {
        cerr << "Container test failed\n";
        return 1;
    }
    return 0;
}
