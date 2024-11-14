#include <iostream>
#include <fstream>
#include "queue.h"
#include <vector>

using namespace std;

int breadth_search(const vector<vector<int>>& graph, int start, int end);
bool test(int res);

int main(int argc, char **argv) {
    int n, start, end;
    ifstream input;
    input.open(argv[1]);
    if(!input.is_open()) {
        cerr << "ERROE OPEN FILE!" << endl;
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

    int result = breadth_search(graph, start, end);

    if (result == -1) {
        cout << "ERROR" << endl;
    } else {
        if (!test(result)) {
            return 1;
        }
        cout << result << endl;
    }

    return 0;
}


int breadth_search(const vector<vector<int>>& graph, int start, int end) {
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
bool test(int res) {
    if (res == 2) {
        return true;
    }
    else {
        return false;
    }
}

