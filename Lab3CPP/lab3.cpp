#include "lab3.h"

vector<Data> bfs(Data start, unordered_map<Data, vector<Data>>& graph) {
    unordered_set<Data> visited;
    Queue *q = queue_create();
    vector<Data> result;

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

vector<Data> task(ifstream& input, int reactions) {
    Data start;
    input >> start;

    unordered_map<Data, vector<Data>> graph;
    Data curr, canGet;
    for(int i = 0; i < reactions; i++)
    {
        input >> curr >> canGet;
        graph[curr].push_back(canGet);
    }
    
    return bfs(start, graph);
}