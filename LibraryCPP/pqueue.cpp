#include "pqueue.h"
#include "vector.h"

struct PriorityQueue
{
    Vector* data;
    Vector* prio;
};

PriorityQueue* pqueue_create()
{
    PriorityQueue* pq = new PriorityQueue;
    pq->data = vector_create();
    pq->prio = vector_create();
    return pq;
}

void pqueue_delete(PriorityQueue* pq)
{
    vector_delete(pq->data);
    vector_delete(pq->prio);
    delete pq;
}

bool pqueue_empty(const PriorityQueue* pq)
{
    return vector_size(pq->data) == 0;
}

void pqueue_push(PriorityQueue* pq, int v, int priority)
{
    size_t n = vector_size(pq->data);

    vector_resize(pq->data, n + 1);
    vector_resize(pq->prio, n + 1);
    vector_set(pq->data, n, v);
    vector_set(pq->prio, n, priority);

    size_t i = n;
    while (i > 0)
    {
        size_t parent = (i - 1) / 2;
        int pr_i = vector_get(pq->prio, i);
        int pr_p = vector_get(pq->prio, parent);

        if (pr_p <= pr_i)
            break;

        int vi = vector_get(pq->data, i);
        int vp = vector_get(pq->data, parent);

        vector_set(pq->data, i, vp);
        vector_set(pq->data, parent, vi);

        vector_set(pq->prio, i, pr_p);
        vector_set(pq->prio, parent, pr_i);

        i = parent;
    }
}

int pqueue_pop(PriorityQueue* pq)
{
    size_t n = vector_size(pq->data);

    int root = vector_get(pq->data, 0);
    int last_v = vector_get(pq->data, n - 1);
    int last_p = vector_get(pq->prio, n - 1);

    vector_set(pq->data, 0, last_v);
    vector_set(pq->prio, 0, last_p);

    vector_resize(pq->data, n - 1);
    vector_resize(pq->prio, n - 1);
    n--;

    size_t i = 0;
    while (true)
    {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t best = i;

        if (left < n)
        {
            int pr_l = vector_get(pq->prio, left);
            int pr_b = vector_get(pq->prio, best);
            if (pr_l < pr_b)
                best = left;
        }

        if (right < n)
        {
            int pr_r = vector_get(pq->prio, right);
            int pr_b = vector_get(pq->prio, best);
            if (pr_r < pr_b)
                best = right;
        }

        if (best == i)
            break;

        int vi = vector_get(pq->data, i);
        int vb = vector_get(pq->data, best);
        vector_set(pq->data, i, vb);
        vector_set(pq->data, best, vi);

        int pr_i = vector_get(pq->prio, i);
        int pr_best = vector_get(pq->prio, best);
        vector_set(pq->prio, i, pr_best);
        vector_set(pq->prio, best, pr_i);

        i = best;
    }

    return root;
}