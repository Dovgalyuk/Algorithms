#include "lab3.h"

vector<char> bfs(char start, unordered_map<char, vector<char>> graph) {
    unordered_set<char> visited;
    Queue *q = queue_create();
    vector<char> result;

    queue_insert(q,start);
    visited.insert(start);

    while (!queue_empty(q)) {
        char curr = queue_get(q);
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

vector<char> task(ifstream& input, int reactions) {
    char start;
    input >> start;

    unordered_map<char, vector<char>> graph;
    char curr, canGet;
    for(int i = 0; i < reactions; i++)
    {
        input >> curr >> canGet;
        graph[curr].push_back(canGet);
    }
    
    return bfs(start, graph);
}