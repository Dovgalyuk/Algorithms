#include <stdexcept>
#include "queue.h"

Queue::Queue() : list(list_create()) {}

Queue::~Queue() {
    list_delete(list);
}

void Queue::insert(Data data) {
    list_insert_after(list, list_last(list), data);
}

Data Queue::get() const {
    if (empty()) throw std::out_of_range("Queue is empty");
    return list_item_data(list_first(list));
}

void Queue::remove() {
    list_erase_first(list);
}

bool Queue::empty() const {
    return list_first(list) == nullptr;
}

Queue* queue_create() { return new Queue; }
void queue_delete(Queue* queue) { delete queue; }
void queue_insert(Queue* queue, Data data) { queue->insert(data); }
Data queue_get(const Queue* queue) { return queue->get(); }
void queue_remove(Queue* queue) { queue->remove(); }
bool queue_empty(const Queue* queue) { return queue->empty(); }
