#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>
#include "graph.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    size_t vertex_count;
    input >> vertex_count;

    Graph<std::string, int> graph(vertex_count);

    for (size_t i = 0; i < vertex_count; ++i) {
        std::string vertex_mark;
        input >> vertex_mark;
        graph.add_vertex_mark(vertex_mark);
    }

    size_t from, to;
    int weight;

    while (input >> from >> to >> weight) {
        try {
            graph.add_edge(from, to, weight);
        }
        catch (const std::exception& e) {
            std::cerr << "Error adding edge: " << e.what() << std::endl;
        }
    }

    input.close();

    size_t start_vertex = 0;
    std::vector<int> distances(graph.get_vertex_count(), INT_MAX);
    distances[start_vertex] = 0;

    using P = std::pair<int, size_t>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.emplace(0, start_vertex);

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        size_t current_vertex = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_vertex]) continue;

        typename List<Graph<std::string, int>::Edge*>::Item* edge_item = graph.get_vertex(current_vertex)->edges->first();
        while (edge_item) {
            Graph<std::string, int>::Edge* edge = edge_item->data();
            if (edge->mark < 0) {
                std::cerr << "Error: Negative edge weight detected!" << std::endl;
                return 1;
            }

            if (current_distance > INT_MAX - edge->mark) {
                std::cerr << "Error: Integer overflow detected!" << std::endl;
                return 1;
            }

            int new_distance = current_distance + edge->mark;

            if (new_distance < distances[edge->to->id_vertex]) {
                distances[edge->to->id_vertex] = new_distance;
                pq.emplace(new_distance, edge->to->id_vertex);
            }
            edge_item = edge_item->next();
        }
    }

    for (size_t i = 0; i < graph.get_vertex_count(); ++i) {
        std::cout << "To the vertex: " << i << " (" << graph.get_vertex_mark(i) << "): "
            << (distances[i] == INT_MAX ? "INF" : std::to_string(distances[i])) << "\n";
    }

    return 0;
}
