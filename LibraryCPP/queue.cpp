#include "queue.h"
#include "vector.h"
#include <cstddef>

struct Queue {
    Vector* buf;
    size_t head;
    size_t tail;
    size_t count;
};

static size_t q_capacity(const Queue* q) {
    return vector_size(q->buf);
}

static void q_grow(Queue* q) {
    size_t cap = q_capacity(q);
    size_t newcap = (cap == 0) ? 4 : cap * 2;

    Vector* nb = vector_create();
    vector_resize(nb, newcap);

    for (size_t i = 0; i < q->count; ++i) {
        Data x = vector_get(q->buf, (q->head + i) % cap);
        vector_set(nb, i, x);
    }

    vector_delete(q->buf);
    q->buf = nb;
    q->head = 0;
    q->tail = q->count;
}

Queue* queue_create() {
    Queue* q = new Queue;
    q->buf = vector_create();
    vector_resize(q->buf, 4);
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue* q) {
    if (!q)
        return;

    vector_delete(q->buf);
    delete q;
}

void queue_insert(Queue* q, Data data) {
    if (q->count == q_capacity(q))
        q_grow(q);

    size_t cap = q_capacity(q);
    vector_set(q->buf, q->tail, data);
    q->tail = (q->tail + 1) % cap;
    ++q->count;
}

Data queue_get(const Queue* q) {
    if (q->count == 0)
        return (Data)0;

    return vector_get(q->buf, q->head);
}

void queue_remove(Queue* q) {
    if (q->count == 0)
        return;

    size_t cap = q_capacity(q);
    q->head = (q->head + 1) % cap;
    --q->count;
}

bool queue_empty(const Queue* q) {
    return q->count == 0;
}