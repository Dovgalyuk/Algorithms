#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct QueueItem {
    int vertex;
    int distance;
    QueueItem* next;
};

struct PriorityQueue {
    QueueItem* front;
};

void pq_push(PriorityQueue* pq, int vertex, int distance) {
    QueueItem* new_item = new QueueItem;
    new_item->vertex = vertex;
    new_item->distance = distance;
    new_item->next = nullptr;

    if (pq->front == nullptr || pq->front->distance > distance) {
        new_item->next = pq->front;
        pq->front = new_item;
    }
    else {
        QueueItem* current = pq->front;
        while (current->next != nullptr && current->next->distance <= distance) {
            current = current->next;
        }
        new_item->next = current->next;
        current->next = new_item;
    }
}

int pq_pop(PriorityQueue* pq) {
    if (pq->front == nullptr) {
        return -1;
    }
    int vertex = pq->front->vertex;
    QueueItem* temp = pq->front;
    pq->front = pq->front->next;
    delete temp;
    return vertex;
}

bool pq_empty(PriorityQueue* pq) {
    return pq->front == nullptr;
}

void pq_delete(PriorityQueue* pq) {
    while (!pq_empty(pq)) {
        pq_pop(pq);
    }
    delete pq;
}

PriorityQueue* pq_create() {
    PriorityQueue* pq = new PriorityQueue;
    pq->front = nullptr;
    return pq;
}

size_t find_index(const string* names, size_t n, const string& name)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (names[i] == name)
            return i;
    }
    return static_cast<size_t>(-1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cout << "Cannot open file\n";
        return 1;
    }

    size_t vertex_count, edge_count;
    input >> vertex_count >> edge_count;

    Graph<string, int> graph(vertex_count);
    string* vertex_names = new string[vertex_count];

    for (size_t i = 0; i < vertex_count; ++i) {
        input >> vertex_names[i];
        graph.set_vertex_label(i, vertex_names[i]);
    }

    for (size_t i = 0; i < edge_count; ++i) {
        string from_name, to_name;
        int weight;
        input >> from_name >> to_name >> weight;

        size_t from_idx = find_index(vertex_names, vertex_count, from_name);
        size_t to_idx = find_index(vertex_names, vertex_count, to_name);

        if (from_idx != static_cast<size_t>(-1) && to_idx != static_cast<size_t>(-1)) {
            graph.add_edge(from_idx, to_idx, weight);
        }
    }

    string start_name, end_name;
    input >> start_name >> end_name;

    size_t start_idx = find_index(vertex_names, vertex_count, start_name);
    size_t end_idx = find_index(vertex_names, vertex_count, end_name);

    if (start_idx == static_cast<size_t>(-1) || end_idx == static_cast<size_t>(-1)) {
        cout << "Start or end vertex not found\n";
        delete[] vertex_names;
        return 1;
    }

    const int MAX_DIST = 1000000000;
    int* distances = new int[vertex_count];
    int* prev_vertex = new int[vertex_count];

    for (size_t i = 0; i < vertex_count; ++i) {
        distances[i] = MAX_DIST;
        prev_vertex[i] = -1;
    }
    distances[start_idx] = 0;

    PriorityQueue* pq = pq_create();
    pq_push(pq, static_cast<int>(start_idx), distances[start_idx]);

    while (!pq_empty(pq)) {
        int current = pq_pop(pq);

        auto it = graph.neighbors(static_cast<size_t>(current));
        while (it.valid()) {
            size_t neighbor = it.vertex_id();
            int edge_weight = it.edge_label();

            if (distances[current] + edge_weight < distances[neighbor]) {
                distances[neighbor] = distances[current] + edge_weight;
                prev_vertex[neighbor] = current;
                pq_push(pq, static_cast<int>(neighbor), distances[neighbor]);
            }

            it.next();
        }
    }

    if (distances[end_idx] == MAX_DIST) {
        cout << "No path\n";
    }
    else {
        cout << distances[end_idx] << "\n";

        size_t* path = new size_t[vertex_count];
        size_t path_len = 0;

        size_t current = end_idx;
        while (true) {
            path[path_len++] = current;
            if (current == start_idx) break;
            current = static_cast<size_t>(prev_vertex[current]);
        }

        for (size_t i = path_len; i > 0; --i) {
            cout << vertex_names[path[i - 1]];
            if (i > 1)
                cout << " ";
        }
        cout << "\n";

        delete[] path;
    }

    pq_delete(pq);
    delete[] distances;
    delete[] prev_vertex;
    delete[] vertex_names;

    return 0;
}