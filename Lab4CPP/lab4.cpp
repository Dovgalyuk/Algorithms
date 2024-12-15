#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include "graph.h"

using namespace std;

template <typename V, typename E>
void dijkstra(Graph<V, E>& graph, size_t start_vertex) {
    size_t vertex_count = graph.get_vertex_count();
    vector<E> distances(vertex_count, numeric_limits<E>::max());
    vector<bool> visited(vertex_count, false);
    priority_queue<pair<E, size_t>, vector<pair<E, size_t>>, greater<pair<E, size_t>>> pq;

    distances[start_vertex] = 0;
    pq.push({ 0, start_vertex });

    while (!pq.empty()) {
        size_t current_vertex = pq.top().second;
        pq.pop();

        if (visited[current_vertex]) {
            continue;
        }
        visited[current_vertex] = true;

        for (auto item = graph.begin(current_vertex); item != graph.end(); ++item) {
            const typename Graph<V, E>::Vertex* neighbor = *item;
            E edge_weight = graph.get_edge_weight(current_vertex, neighbor->id_vertex);

            E new_distance = distances[current_vertex] + edge_weight;
            if (new_distance < distances[neighbor->id_vertex]) {
                distances[neighbor->id_vertex] = new_distance;
                pq.push({ new_distance, neighbor->id_vertex });
            }
        }
    }

    for (size_t i = 0; i < distances.size(); ++i) {
        if (distances[i] == numeric_limits<E>::max()) {
            cout << "Vertex " << graph.get_vertex_mark(i) << ": unreachable" << endl;
        }
        else {
            cout << "Vertex " << graph.get_vertex_mark(i) << ": " << distances[i] << endl;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    size_t vertex_count;
    input >> vertex_count;

    Graph<string, int> graph(vertex_count);

    for (size_t i = 0; i < vertex_count; ++i) {
        string mark;
        input >> mark;
        graph.add_vertex(mark);
    }

    size_t from, to, weight;
    while (input >> from >> to >> weight) {
        graph.add_edge(from, to, static_cast<int>(weight));
    }

    input.close();

    size_t start_vertex = 0;
    dijkstra(graph, start_vertex);

    return 0;
}