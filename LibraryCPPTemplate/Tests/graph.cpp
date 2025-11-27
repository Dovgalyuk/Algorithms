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
    std::cout << "Distance to end: " << distance[end] << std::endl;

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

template class Graph<std::string, int>;
template class Graph<std::string, std::string>;
template class Graph<int, int>;