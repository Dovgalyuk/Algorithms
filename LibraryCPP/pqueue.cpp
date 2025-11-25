#include "pqueue.h"
#include "vector.h"

struct PriorityQueue
{
    Vector* data;
};

PriorityQueue* pqueue_create()
{
    PriorityQueue* pq = new PriorityQueue;
    pq->data = vector_create();
    return pq;
}

static bool comp_dist(int a, int b, const int* dist)
{
    return dist[a] < dist[b];
}

void pqueue_delete(PriorityQueue* pq)
{
    vector_delete(pq->data);
    delete pq;
}

bool pqueue_empty(const PriorityQueue* pq)
{
    return vector_size(pq->data) == 0;
}

void pqueue_push(PriorityQueue* pq, int v, const int* dist)
{
    size_t n = vector_size(pq->data);
    vector_resize(pq->data, n + 1);
    vector_set(pq->data, n, v);

    size_t i = n;
    while (i > 0)
    {
        size_t parent = (i - 1) / 2;
        int vi = vector_get(pq->data, i);
        int vp = vector_get(pq->data, parent);

        if (!comp_dist(vi, vp, dist))
            break;

        vector_set(pq->data, i, vp);
        vector_set(pq->data, parent, vi);

        i = parent;
    }
}

int pqueue_pop(PriorityQueue* pq, const int* dist)
{
    size_t n = vector_size(pq->data);

    int root = vector_get(pq->data, 0);
    int last = vector_get(pq->data, n - 1);

    vector_set(pq->data, 0, last);
    vector_resize(pq->data, n - 1);
    n--;

    size_t i = 0;
    while (true)
    {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t best = i;

        if (left < n)
        {
            int vl = vector_get(pq->data, left);
            int vb = vector_get(pq->data, best);
            if (comp_dist(vl, vb, dist))
                best = left;
        }

        if (right < n)
        {
            int vr = vector_get(pq->data, right);
            int vb = vector_get(pq->data, best);
            if (comp_dist(vr, vb, dist))
                best = right;
        }

        if (best == i)
            break;

        int vi = vector_get(pq->data, i);
        int vb = vector_get(pq->data, best);

        vector_set(pq->data, i, vb);
        vector_set(pq->data, best, vi);

        i = best;
    }

    return root;
}