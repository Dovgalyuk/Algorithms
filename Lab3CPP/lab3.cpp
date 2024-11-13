#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"
#include "list.h"

using namespace std;

void read_graph(ifstream& input_file, vector<vector<int>>& graph);
void bfs(int start_peak, int finish_peak, const vector<vector<int>>& graph, int count_peaks, ofstream& output_file);

void bfs(int start_peak, int finish_peak, const vector<vector<int>>& graph, int count_peaks, ofstream& output_file) {
    vector<int> distance(count_peaks + 1, -1);
    Queue* queue = queue_create();

    distance[start_peak] = 0;
    queue_insert(queue, start_peak);

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        for (int neighbor : graph[current]) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                queue_insert(queue, neighbor);
                if (neighbor == finish_peak) {
                    break;
                }
            }
        }
    }

    if (distance[finish_peak] != -1) {
        output_file << distance[finish_peak] << endl;
    }
    else {
        output_file << "IMPOSSIBLE" << endl;
    }

    queue_delete(queue);
}

void read_graph(ifstream& input_file, vector<vector<int>>& graph) {
    int x, y;
    while (input_file >> x >> y) {
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Error opening file " << argv[1] << endl;
        return 1;
    }

    ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        cerr << "Error opening file " << argv[2] << endl;
        return 1;
    }

    int count_peaks, start_peak, finish_peak;

    input_file >> count_peaks >> start_peak >> finish_peak;

    vector<vector<int>> graph(count_peaks + 1);

    read_graph(input_file, graph);

    bfs(start_peak, finish_peak, graph, count_peaks, output_file);

    input_file.close();
    output_file.close();

    return 0;
}





