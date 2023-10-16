#include <iostream>
#include <queue>
#include <climits>
#include "../LibraryCPPTemplate/graph.h"

const int INF = INT_MAX;

template<typename Data>
int* dijkstra(const Graph<Data>& graph, size_t vertex_amount, size_t start_vertex) {
    // Создаем копию графа для обхода ограничения const
    Graph<Data> mutableGraph = graph;

    int* distances = new int[vertex_amount];
    for (size_t i = 0; i < vertex_amount; ++i)
        distances[i] = INF;
    distances[start_vertex] = 0;

    std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, std::greater<std::pair<int, size_t>>> minHeap;
    minHeap.push(std::make_pair(0, start_vertex));

    while (!minHeap.empty()) {
        int distance = minHeap.top().first;
        size_t current_vertex = minHeap.top().second;
        minHeap.pop();

        if (distance > distances[current_vertex])
            continue;

        for (size_t neighbor_index = 0; neighbor_index < vertex_amount; ++neighbor_index) {
            // Check if there is an edge between current_vertex and neighbor_index
            Graph<Data>::Edge* edge = mutableGraph.getEdge(current_vertex, neighbor_index);
            if (edge != nullptr) {
                int edge_weight = edge->getEdgeData();

                if (distances[current_vertex] + edge_weight < distances[neighbor_index]) {
                    distances[neighbor_index] = distances[current_vertex] + edge_weight;
                    minHeap.push(std::make_pair(distances[neighbor_index], neighbor_index));
                }
            }
        }
    }

    return distances;
}

int main() {
    size_t vertex_amount = 0;
    int N = 0;

    // Добавление рёбер
    std::cout << "Input vertex_amount> ";
    std::cin >> vertex_amount;
    Graph<int> graph(vertex_amount, 0);
    std::cout << "Input size read data> ";
    std::cin >> N;
    for (int i = 0; i < N;i++) {
        size_t start_vertex_index = 0;
        size_t end_vertex_index = 0;
        int edge_data = 0;
        std::cout << "input " << i << " data (size_t start_vertex_index, size_t end_vertex_index, Data edge_data)> ";
        std::cin >> start_vertex_index >> end_vertex_index >> edge_data;
        graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
    }
    //graph.addEdge(0, 1, 10);
    //graph.addEdge(0, 2, 5);
    //graph.addEdge(1, 2, 2);
    //graph.addEdge(1, 3, 1);
    //graph.addEdge(2, 1, 3);
    //graph.addEdge(2, 3, 9);
    //graph.addEdge(2, 4, 2);
    //graph.addEdge(3, 4, 4);

    // Вызов алгоритма Дейкстры для поиска кратчайших путей
    int start = 0;
    std::cin >> start;
    int* shortest_paths = dijkstra(graph, vertex_amount, start);

    // Вывод результатов
    for (size_t i = 0; i < vertex_amount; i++) {
        if(shortest_paths[i]!=INF)
            std::cout << "Shortest path from vertex "<<start<< " to vertex " << i << " is " << shortest_paths[i] << "\n";
        else
            std::cout << "Shortest path from vertex " << start << " to vertex " << i << " is NULL\n";
    }

    delete[] shortest_paths;  // освобождаем выделенную память

    return 0;
}