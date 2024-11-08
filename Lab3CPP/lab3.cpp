#include "queue.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int bfs(vector<vector<int>> graph, int start, int end) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> distance(n, -1);
    Queue *q = queue_create();

    queue_insert(q, start);
    visited[start] = true;
    distance[start] = 0;

    while (!queue_empty(q)) {
        int current = queue_get(q);
        queue_remove(q);

        if (current == end) {
            queue_delete(q);
            return distance[current];
        }

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current][neighbor] == 1 && !visited[neighbor]) {
                queue_insert(q, neighbor);
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
            }
        }
    }
    queue_delete(q);
    return -1;
}
bool testTask(int res) {
    if (res == 2) {
        return true;
    }else
        return false;
}
int main(int argc, char **argv) {
    int n, start, end;
    ifstream input;
    input.open(argv[1]);
    if(!input.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    input >> n >> start >> end;
    start--;
    end--;

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            input >> graph[i][j];
        }
    }

    int result = bfs(graph, start, end);

    if (result == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        if (!testTask(result)) {
            return 1;
        }
        cout << result << endl;
    }

    return 0;
}
