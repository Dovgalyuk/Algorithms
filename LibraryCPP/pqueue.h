#ifndef PQUEUE_H
#define PQUEUE_H

typedef int Data;

struct PriorityQueue;

PriorityQueue* pqueue_create();

void pqueue_delete(PriorityQueue* pq);

bool pqueue_empty(const PriorityQueue* pq);

void pqueue_push(PriorityQueue* pq, int v, const int* dist);

int pqueue_pop(PriorityQueue* pq, const int* dist);

#endif