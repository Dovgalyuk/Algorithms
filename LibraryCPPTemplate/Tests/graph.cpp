#include "graph.h"
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <iostream>
#include <climits>

template<typename VertexLabel, typename EdgeLabel>
std::vector<std::vector<int>> Graph<VertexLabel, EdgeLabel>::findAllShortestPaths(int start, int end) const {
    if (start < 0 || static_cast<size_t>(start) >= getVertexCount() ||
        end < 0 || static_cast<size_t>(end) >= getVertexCount()) {
        return {};
    }

    if (start == end) {
        return { {start} };
    }

    std::vector<int> distance(getVertexCount(), -1);
    std::vector<std::vector<int>> predecessors(getVertexCount());
    std::queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto neighbors_iter = getNeighbors(current);
        while (neighbors_iter.hasNext()) {
            int neighbor = neighbors_iter.next();

            if (neighbor < 0 || static_cast<size_t>(neighbor) >= getVertexCount()) {
                continue;
            }

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

    if (distance[end] == -1) {
        return {};
    }

    std::vector<std::vector<int>> all_paths;
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

    std::sort(all_paths.begin(), all_paths.end());

    return all_paths;
}

template class Graph<std::string, int>;
template class Graph<std::string, std::string>;
template class Graph<int, int>;

#ifdef TEST_GRAPH_STANDALONE
#include <vector>
#include <string>

void testGraphLibrary() {
    std::cout << "=== Testing Graph Library ===" << std::endl;

    Graph<std::string, int> graph(5);

    graph.setVertexLabel(0, "A");
    graph.setVertexLabel(1, "B");
    graph.setVertexLabel(2, "C");
    graph.setVertexLabel(3, "D");
    graph.setVertexLabel(4, "E");

    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 1);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 4, 6);

    std::cout << "Vertex count: " << graph.getVertexCount() << std::endl;
    std::cout << "Has edge A->B: " << graph.hasEdge(0, 1) << std::endl;
    std::cout << "Has edge B->A: " << graph.hasEdge(1, 0) << std::endl;

    auto labels = graph.getAllVertexLabels();
    std::cout << "Vertex labels: ";
    for (size_t i = 0; i < labels.size(); ++i) {
        std::cout << labels.get(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Neighbors of A: ";
    auto neighbors = graph.getNeighbors(0);
    while (neighbors.hasNext()) {
        int neighbor = neighbors.next();
        std::cout << graph.getVertexLabel(neighbor) << " ";
    }
    std::cout << std::endl;

    std::cout << "Edge A->B weight: " << graph.getEdgeLabel(0, 1) << std::endl;
    std::cout << "Edge C->D weight: " << graph.getEdgeLabel(2, 3) << std::endl;

    auto paths = graph.findAllShortestPaths(0, 4);
    std::cout << "\nFound " << paths.size() << " shortest path(s) from A to E" << std::endl;

    for (size_t i = 0; i < paths.size(); ++i) {
        std::cout << "Path " << i + 1 << ": ";
        for (size_t j = 0; j < paths[i].size(); ++j) {
            std::cout << graph.getVertexLabel(paths[i][j]);
            if (j < paths[i].size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << " (Length: " << paths[i].size() - 1 << ")" << std::endl;
    }
}

int main() {
    testGraphLibrary();
    return 0;
}
#endif