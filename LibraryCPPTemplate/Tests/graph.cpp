#include "graph.h"
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <iostream>

template<typename VertexLabel, typename EdgeLabel>
std::vector<std::vector<int>> Graph<VertexLabel, EdgeLabel>::findAllShortestPaths(int start, int end) const {
    if (start < 0 || static_cast<size_t>(start) >= vertex_count ||
        end < 0 || static_cast<size_t>(end) >= vertex_count) {
        return {};
    }

    if (start == end) {
        return { {start} };
    }

    std::vector<int> distance(vertex_count, -1);
    std::vector<std::vector<int>> predecessors(vertex_count);
    std::queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto neighbors_iter = getNeighbors(current);
        while (neighbors_iter.hasNext()) {
            int neighbor = neighbors_iter.next();

            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                predecessors[neighbor].push_back(current);
                q.push(neighbor);
            }
            else if (distance[neighbor] == distance[current] + 1) {
                predecessors[neighbor].push_back(current);
            }
        }
    }

    std::vector<std::vector<int>> all_paths;
    if (distance[end] == -1) {
        return all_paths;
    }

    std::vector<int> current_path;
    std::function<void(int)> backtrack = [&](int node) {
        current_path.push_back(node);
        if (node == start) {
            std::vector<int> path = current_path;
            std::reverse(path.begin(), path.end());
            all_paths.push_back(path);
        }
        else {
            for (int pred : predecessors[node]) {
                backtrack(pred);
            }
        }
        current_path.pop_back();
        };

    backtrack(end);
    return all_paths;
}

void testGraphFunctionality() {
    std::cout << "=== Testing Graph Functionality ===" << std::endl;

    Graph<std::string, int> graph(3);

    graph.setVertexLabel(0, "A");
    graph.setVertexLabel(1, "B");
    graph.setVertexLabel(2, "C");

    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, 3);
    graph.addEdge(0, 2, 7);

    std::cout << "Vertex count: " << graph.getVertexCount() << std::endl;
    std::cout << "Has edge A->B: " << graph.hasEdge(0, 1) << std::endl;
    std::cout << "Has edge B->A: " << graph.hasEdge(1, 0) << std::endl;
    std::cout << "Edge weight A->B: " << graph.getEdgeLabel(0, 1) << std::endl;

    auto neighbors = graph.getNeighbors(0);
    std::cout << "Neighbors of A: ";
    while (neighbors.hasNext()) {
        int neighbor = neighbors.next();
        std::cout << graph.getVertexLabel(neighbor) << " ";
    }
    std::cout << std::endl;

    auto paths = graph.findAllShortestPaths(0, 2);
    std::cout << "Found " << paths.size() << " shortest path(s) from A to C" << std::endl;

    for (size_t i = 0; i < paths.size(); ++i) {
        std::cout << "Path " << i + 1 << ": ";
        for (size_t j = 0; j < paths[i].size(); ++j) {
            std::cout << graph.getVertexLabel(paths[i][j]);
            if (j < paths[i].size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Graph functionality test completed!" << std::endl;
}

#ifdef TEST_GRAPH
int main() {
    testGraphFunctionality();
    return 0;
}
#endif

template class Graph<std::string, int>;
template class Graph<std::string, std::string>;
template class Graph<int, int>;