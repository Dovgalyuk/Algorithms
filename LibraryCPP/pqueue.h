#ifndef PQUEUE_H
#define PQUEUE_H

typedef int Data;

struct PriorityQueue;

PriorityQueue* pqueue_create();

void pqueue_set_dist(PriorityQueue* pq, const int* dist);

void pqueue_delete(PriorityQueue* pq);

bool pqueue_empty(const PriorityQueue* pq);

void pqueue_push(PriorityQueue* pq, int v);

int pqueue_pop(PriorityQueue* pq);

#endif