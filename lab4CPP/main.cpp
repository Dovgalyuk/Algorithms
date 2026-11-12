#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <string>

// Подключаем граф из библиотеки
#include "graph.h" 

int main() {
    // В твоем графе порядок шаблонов: <Метка ребра, Метка вершины>
    Graph<int, std::string> g;
    
    // Считываем граф из потока ввода (файла)
    if (!g.read(std::cin)) {
        std::cerr << "Error reading graph!" << std::endl;
        return 1;
    }

    // Считываем стартовую вершину
    std::string start_label;
    if (!(std::cin >> start_label)) {
        std::cerr << "No start vertex provided!" << std::endl;
        return 1;
    }

    // Ищем индекс стартовой вершины
    size_t start_idx = g.size();
    for (size_t i = 0; i < g.size(); ++i) {
        if (g.vertex_label(i) == start_label) {
            start_idx = i;
            break;
        }
    }

    if (start_idx == g.size()) {
        std::cerr << "Start vertex not found in graph!" << std::endl;
        return 1;
    }

    // Инициализация алгоритма Дейкстры
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(g.size(), INF);
    dist[start_idx] = 0;

    // Очередь с приоритетом (расстояние, индекс_вершины)
    using pii = std::pair<int, size_t>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    
    pq.push({0, start_idx});

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        size_t u = pq.top().second;
        pq.pop();

        // Если достали устаревшее расстояние, пропускаем
        if (current_dist > dist[u]) continue;

        // Перебираем всех соседей вершины u
        for (auto it = g.begin(u); it != g.end(u); ++it) {
            size_t v = *it;
            
            // Важно: так как итератор проходит ребра в обе стороны, 
            // проверяем, что ребро идет ИМЕННО от u к v
            if (g.has_edge(u, v)) {
                int weight = g.edge_label(u, v);
                
                // Релаксация ребра
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // Вывод кратчайших расстояний
    std::cout << "Shortest paths from " << start_label << ":\n";
    for (size_t i = 0; i < g.size(); ++i) {
        std::cout << g.vertex_label(i) << ": ";
        if (dist[i] == INF) {
            std::cout << "INF\n";
        } else {
            std::cout << dist[i] << "\n";
        }
    }

    return 0;
}