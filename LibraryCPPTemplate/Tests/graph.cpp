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

    // Используем BFS для поиска кратчайших путей по количеству ребер
    std::vector<int> distance(getVertexCount(), -1);
    std::vector<std::vector<int>> predecessors(getVertexCount());
    std::queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Получаем всех соседей текущей вершины
        auto neighbors_iter = getNeighbors(current);
        while (neighbors_iter.hasNext()) {
            int neighbor = neighbors_iter.next();

            if (distance[neighbor] == -1) {
                // Первое посещение вершины
                distance[neighbor] = distance[current] + 1;
                predecessors[neighbor].push_back(current);
                q.push(neighbor);
            }
            else if (distance[neighbor] == distance[current] + 1) {
                // Альтернативный путь той же длины
                predecessors[neighbor].push_back(current);
            }
        }
    }

    // Если конечная вершина не достижима
    if (distance[end] == -1) {
        return {};
    }

    // Восстанавливаем все кратчайшие пути с помощью backtracking
    std::vector<std::vector<int>> all_paths;
    std::vector<int> current_path;

    std::function<void(int)> backtrack = [&](int node) {
        current_path.push_back(node);

        if (node == start) {
            // Найден полный путь
            std::vector<int> path = current_path;
            std::reverse(path.begin(), path.end());
            all_paths.push_back(path);
        }
        else {
            // Рекурсивно проходим по всем предшественникам
            for (int pred : predecessors[node]) {
                backtrack(pred);
            }
        }

        current_path.pop_back();
        };

    backtrack(end);

    // Сортируем пути для стабильного порядка вывода
    std::sort(all_paths.begin(), all_paths.end());

    return all_paths;
}

// Явные инстанцирования шаблонов
template class Graph<std::string, int>;
template class Graph<std::string, std::string>;
template class Graph<int, int>;

// Главная функция для TestGraphCPPTemplate
#ifdef TEST_GRAPH_STANDALONE
int main() {
    std::cout << "=== Testing Graph Library ===" << std::endl;

    Graph<std::string, int> graph(3);

    graph.setVertexLabel(0, "X");
    graph.setVertexLabel(1, "Y");
    graph.setVertexLabel(2, "Z");

    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 20);

    std::cout << "Vertex count: " << graph.getVertexCount() << std::endl;
    std::cout << "Has edge X->Y: " << graph.hasEdge(0, 1) << std::endl;
    std::cout << "Edge weight X->Y: " << graph.getEdgeLabel(0, 1) << std::endl;

    auto paths = graph.findAllShortestPaths(0, 2);
    std::cout << "Found " << paths.size() << " shortest path(s) from X to Z" << std::endl;

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

    std::cout << "TestGraphCPPTemplate completed successfully!" << std::endl;
    return 0;
}
#endif