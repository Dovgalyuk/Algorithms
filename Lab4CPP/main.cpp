#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct HeapItem {
    int vertex;
    int distance;
};

struct PriorityQueue {
    Vector<HeapItem> heap;
};

PriorityQueue* pq_create() {
    PriorityQueue* pq = new PriorityQueue;
    return pq;
}

void pq_push(PriorityQueue* pq, int vertex, int distance) {
    HeapItem item;
    item.vertex = vertex;
    item.distance = distance;
    
    pq->heap.resize(pq->heap.size() + 1);
    size_t index = pq->heap.size() - 1;
    pq->heap.set(index, item);

    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (pq->heap.get(parent).distance > pq->heap.get(index).distance) {
            HeapItem temp = pq->heap.get(parent);
            pq->heap.set(parent, pq->heap.get(index));
            pq->heap.set(index, temp);
            index = parent;
        }
        else {
            break;
        }
    }
}

int pq_pop(PriorityQueue* pq) {
    if (pq->heap.size() == 0) {
        return -1;
    }
    int vertex = pq->heap.get(0).vertex;

    if (pq->heap.size() > 1) {
        pq->heap.set(0, pq->heap.get(pq->heap.size() - 1));
        pq->heap.resize(pq->heap.size() - 1);
        
        size_t index = 0;
        size_t heap_size = pq->heap.size();
        while (true) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t smallest = index;

            if (left < heap_size && pq->heap.get(left).distance < pq->heap.get(smallest).distance) {
                smallest = left;
            }
            if (right < heap_size && pq->heap.get(right).distance < pq->heap.get(smallest).distance) {
                smallest = right;
            }

            if (smallest != index) {
                HeapItem temp = pq->heap.get(index);
                pq->heap.set(index, pq->heap.get(smallest));
                pq->heap.set(smallest, temp);
                index = smallest;
            }
            else {
                break;
            }
        }
    }
    else {
        pq->heap.resize(0);
    }
    return vertex;
}

bool pq_empty(PriorityQueue* pq) {
    return pq->heap.size() == 0;
}

void pq_delete(PriorityQueue* pq) {
    delete pq;
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