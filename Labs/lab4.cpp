#include <iostream>
#include <queue>
#include <climits>
#include "graph.h"
#include <cassert>

const int INF = INT_MAX;

// Шаблонная функция для алгоритма Дейкстры
template<typename Data>
Vector<int> dijkstra(const Graph<Data>& graph, size_t vertex_amount, size_t start_vertex) {
    // Создание немодифицируемой копии графа, чтобы обойти ограничения константности
    Graph<Data> mutableGraph = graph;

    // Установка всех расстояний до вершин в бесконечность, кроме начальной вершины
    for (size_t i = 0; i < vertex_amount; ++i) {
        mutableGraph.getVertex(i)->setVertexData(INF);
    }
    // Установка расстояния от начальной вершины до самой себя в 0
    mutableGraph.getVertex(start_vertex)->setVertexData(0);

    // Очередь с приоритетами для отслеживания вершин и их расстояний

    // 1. std::pair<int, size_t> - тип хранимых элементов: пары, включающие расстояние и индекс вершины
    // 2. std::vector<std::pair<int, size_t>> - контейнер, используемый внутри для хранения элементов
    // 3. std::greater<std::pair<int, size_t>> - функциональный объект для сравнения элементов
    std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, std::greater<std::pair<int, size_t>>> minHeap;
    // Добавление начальной вершины в очередь с приоритетами
    minHeap.push(std::make_pair(0, start_vertex));

    // Основной цикл алгоритма Дейкстры
    // Цикл продолжается до тех пор, пока есть вершины для обработки в приоритетной очереди
    while (!minHeap.empty()) {
        // Извлечение пары с наименьшим расстоянием и соответствующего индекса вершины из кучи
        int distance = minHeap.top().first; // Текущее кратчайшее известное расстояние до вершины
        size_t current_vertex = minHeap.top().second; // Индекс текущей вершины
        minHeap.pop(); // Удаление этой пары из кучи

        // Если расстояние в вершине уже меньше извлеченного расстояния, то мы уже нашли более короткий путь,
        // и текущую вершину можно пропустить
        if (distance > mutableGraph.getVertex(current_vertex)->getVertexData())
            continue;

        // Получаем итератор для обхода всех соседних вершин текущей вершины
        typename Graph<Data>::Iterator it = mutableGraph.getIterator(current_vertex);
        while (*it) { // Пока существуют соседние вершины
            size_t neighbor_index = it.getEnd(); // Индекс текущего соседа
            // Проверяем, есть ли ребро между текущей и соседней вершинами
            typename Graph<Data>::Edge* edge = mutableGraph.getEdge(current_vertex, neighbor_index);
            assert(edge != nullptr); // Утверждение, что такое ребро должно существовать
            int edge_weight = edge->getEdgeData(); // Вес ребра

            // Считаем потенциально новое расстояние до соседней вершины
            int current_vertex_data = mutableGraph.getVertex(current_vertex)->getVertexData();
            int neighbor_vertex_data = mutableGraph.getVertex(neighbor_index)->getVertexData();

            // Если сумма текущего расстояния и веса ребра меньше известного расстояния до соседа,
            // то обновляем значение расстояния в соседней вершине
            if (current_vertex_data + edge_weight < neighbor_vertex_data) {
                mutableGraph.getVertex(neighbor_index)->setVertexData(current_vertex_data + edge_weight);
                // Добавляем соседнюю вершину в кучу с обновленным расстоянием для дальнейшей обработки
                minHeap.push(std::make_pair(mutableGraph.getVertex(neighbor_index)->getVertexData(), neighbor_index));
            }

            ++it; // Переходим к следующему соседу
        }
    }

    // Подготовка вектора для хранения результатов алгоритма
    Vector<int> result;
    result.resize(vertex_amount);
    for (size_t i = 0; i < vertex_amount; ++i) {
        result.set(i, mutableGraph.getVertex(i)->getVertexData());
    }

    return result; // Возврат вектора с кратчайшими расстояниями от начальной вершины
}

int main() {
    size_t vertex_amount = 0; // Общее количество вершин
    int N = 0; // Количество рёбер для чтения

    // Ввод количества вершин
    std::cout << "Input vertex_amount> ";
    std::cin >> vertex_amount;
    // Создание графа с заданным количеством вершин и инициализацией нулями
    Graph<int> graph(vertex_amount, 0);

    // Ввод количества рёбер для считывания
    std::cout << "Input size read data> ";
    std::cin >> N;

    // Ввод данных рёбер и добавление их в граф
    for (int i = 0; i < N; i++) {
        size_t start_vertex_index, end_vertex_index;
        int edge_data;
        std::cout << "input " << i << " data (size_t start_vertex_index, size_t end_vertex_index, Data edge_data)> ";
        std::cin >> start_vertex_index >> end_vertex_index >> edge_data;
        graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
    }

    // Запуск алгоритма Дейкстры для поиска кратчайших путей от заданной начальной вершины
    int start = 0;
    std::cin >> start;
    Vector<int> shortest_paths = dijkstra(graph, vertex_amount, start);

    // Вывод результатов кратчайших путей от начальной вершины до всех остальных
    for (size_t i = 0; i < vertex_amount; i++) {
        if (shortest_paths.get(i) != INF)
            std::cout << "Shortest path from vertex " << start << " to vertex " << i << " is " << shortest_paths.get(i) << "\n";
        else
            std::cout << "Shortest path from vertex " << start << " to vertex " << i << " is NULL\n";
    }
    return 0;
}