#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

using namespace std;


typedef vector<vector<int>> Graph;

vector<int> bfs(const Graph& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, -1);
    vector<bool> visited(n, false);

    Queue* queue = queue_create();
    queue_insert(queue, start);
    distances[start] = 0;
    visited[start] = true;

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current][neighbor] == 1 && !visited[neighbor]) {
                distances[neighbor] = distances[current] + 1;
                visited[neighbor] = true;
                queue_insert(queue, neighbor);
            }
        }
    }

    queue_delete(queue);
    return distances;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }


    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error: Cannot open input file " << argv[1] << endl;
        return 1;
    }


    int n;
    input >> n;

   
    Graph graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            input >> graph[i][j];
        }
    }
    input.close();


    vector<int> distances = bfs(graph, 0);


    for (int i = 0; i < n; ++i) {
        cout << distances[i] << endl;
    }

    return 0;
}