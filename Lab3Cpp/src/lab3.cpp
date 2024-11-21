#include <iostream>
#include <vector>
#include <fstream>
#include "queue.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        cerr << "Unable to open input or output file!" << endl;
        return 1;
    }

    int n, start, finish;
    input >> n >> start >> finish;

    start--;
    finish--;

    vector<vector<int>> graph(n);

    int vertex1, vertex2;
    while (input >> vertex1 >> vertex2) {
        vertex1--;
        vertex2--;
        graph[vertex1].push_back(vertex2);
        graph[vertex2].push_back(vertex1);
    }

    vector<int> dist(n, -1);
    dist[start] = 0;

    Queue queue;  
    queue.insert(start);

    while (!queue.empty() && dist[finish] == -1) {
        int current = queue.get();
        queue.remove();

        for (int neighbor : graph[current]) {
            if (dist[neighbor] == -1) {  
                dist[neighbor] = dist[current] + 1;
                queue.insert(neighbor);
            }
        }
    }

    if (dist[finish] == -1) {
        output << "IMPOSSIBLE" << endl;
    }
    else {
        output << dist[finish] << endl;
    }

    return 0;
}