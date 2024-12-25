#include "lab3.h"

Vector bfs(Data start, Graph& graph) {
    unordered_set<Data> visited;
    Queue *q = queue_create();
    Vector result;

    queue_insert(q,start);
    visited.insert(start);

    while (!queue_empty(q)) {
        Data curr = queue_get(q);
        queue_remove(q);

        for (auto neighbor : graph[curr]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue_insert(q,neighbor);
                result.push_back(neighbor);
            }
        }
    }

    queue_delete(q);
    return result;
}

Vector task(ifstream& input, int reactions) {
    Data start;
    input >> start;

    Graph graph;
    Data curr, canGet;
    for(int i = 0; i < reactions; i++)
    {
        input >> curr >> canGet;
        graph[curr].push_back(canGet);
    }
    
    return bfs(start, graph);
}