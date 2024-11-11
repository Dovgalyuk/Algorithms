#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "vector.h"
#include "Vertex.h"
#include "Edge.h"

template <typename V_type, typename E_type>
class Graph {
public:
    // Базовый конструктор
    Graph() {}

    // Конструктор по количеству вершин
    Graph(int q) {
        for (size_t i = 0; i < q && q > 0; i++) {
            add_vertex();
        }
    }

    // Деструктор
    ~Graph() {
        vertices.clear();
        edges.clear();
        matrix.clear();
    }

    // Добавление вершины без пометки
    Vertex<V_type> add_vertex();

    // Добаление вершины с пометкой
    Vertex<V_type> add_vertex(V_type vertex_mark);

    // Удалние вершины
    Vertex<V_type> delete_vertex(size_t a);

    // Получение массива вершин
    Vector<Vertex<V_type>> get_vertices();

    // Получение вершины по индексу
    Vertex<V_type>& get_vertex_by_index(size_t index);

    // Получение массива пометок вершин
    Vector<V_type> get_vertices_marks();

    // Установка пометки для вершины
    Vertex<V_type> set_mark(size_t a, V_type mark);

    // Добавление ребра
    Edge<V_type, E_type> add_edge(size_t a, size_t b, E_type edge_mark);

    // Удаление ребра
    Edge<V_type, E_type> delete_edge(size_t a, size_t b);

    // Получение массива ребер
    Vector<Edge<V_type, E_type>> get_edges();

    // Получение пометки ребра по индексам вершин
    E_type get_edge_mark(size_t a, size_t b);

    // Проверка связи вершин
    bool is_bounded(size_t a, size_t b);

    // Получение индекса ребра по начальной и конечной точкам
    int edge_index(size_t a, size_t b);

    // Получение матрицы смежности
    Vector<Vector<unsigned int>> get_matrix();

    // Класс итератор
    class Iterator;

    // Получение начального состояния итератора
    Iterator begin(size_t index);

    // Получение конечного состояния итератора
    Iterator end(size_t index);
    
    // Вывод информации и графе (вершина и ее соседи)
    template <typename T1, typename T2>
    friend std::ostream& operator<<(std::ostream& out, Graph<V_type, E_type> graph);

private:
    // Массив ребер
    Vector<Edge<V_type, E_type>> edges;

    // Массив вершин
    Vector<Vertex<V_type>> vertices;

    // Матрица смежности
    Vector<Vector<unsigned int>> matrix;
};

template <typename V_type, typename E_type>
Vertex<V_type> Graph<V_type, E_type>::add_vertex() {
    vertices.push({ vertices.size(), V_type() });

    //vertices_q++;
    matrix.push(Vector<unsigned int>(vertices.size(), 0));

    for (size_t i = 0; i < matrix.size(); i++) {
        while (matrix[i].size() != vertices.size())
            matrix[i].push(0);
    }

    return vertices[vertices.size() - 1];
}

template <typename V_type, typename E_type>
Vertex<V_type> Graph<V_type, E_type>::add_vertex(V_type vertex_mark) {
    vertices.push({ vertices.size(), vertex_mark });
    matrix.push(Vector<unsigned int>(vertices.size(), 0));

    for (size_t i = 0; i < matrix.size(); i++) {
        while (matrix[i].size() != vertices.size()) {
            matrix[i].push(0);
        }
    }

    return vertices[vertices.size() - 1];
}

template <typename V_type, typename E_type>
Vertex<V_type> Graph<V_type, E_type>::delete_vertex(size_t a) {
    if (a >= vertices.size()) {
        std::out_of_range("Неверный индекс при удалении вершины");
        return Vertex<V_type>();
    }

    matrix.erase(a);
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[i].erase(a);
    }

    for (size_t i = 0; i < edges.size(); i++) {
        if (edges[i].start->number == a || edges[i].destination->number == a) {
            edges.erase(i);
            i--;
        }
    }

    Vertex<V_type> temp = vertices.erase(a);
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].number = i;
    }
    return temp;
}

template <typename V_type, typename E_type>
Edge<V_type, E_type> Graph<V_type, E_type>::add_edge(size_t a, size_t b, E_type edge_mark) {
    if (a >= vertices.size() || b >= vertices.size()) {
        throw std::out_of_range("Неверные индексы при добавлении ребра");
        return Edge<V_type, E_type>();
    }

    edges.push(Edge<V_type, E_type>(&get_vertex_by_index(a), &get_vertex_by_index(b), edge_mark));
    matrix[a][b]++;
    return edges[edges.size() - 1];
}

template <typename V_type, typename E_type>
Edge<V_type, E_type> Graph<V_type, E_type>::delete_edge(size_t a, size_t b) {
    if ((a >= vertices.size() || b >= vertices.size()) || matrix[a][b] <= 0) {
        throw std::out_of_range("Неверные индексы при удалении ребра или ребра не существует");
        return Edge<V_type, E_type>();
    }

    matrix[a][b]--;
    return edges.erase(edge_index(a, b));
}

template <typename V_type, typename E_type>
Vertex<V_type> Graph<V_type, E_type>::set_mark(size_t a, V_type mark) {
    if (a < vertices.size())
        vertices[a].mark = mark;
    else
        throw std::out_of_range("Неверный индекс при добавлении пометки вершины");
    return vertices[a];
}

template <typename V_type, typename E_type>
Vertex<V_type>& Graph<V_type, E_type>::get_vertex_by_index(size_t index) {
    if(index >= vertices.size()) {
        throw std::out_of_range("Неверный индекс при получении вершины");
    }
    return vertices[index];
}

template <typename V_type, typename E_type>
Vector<V_type> Graph<V_type, E_type>::get_vertices_marks() {
    Vector<V_type> marks;
    for (size_t i = 0; i < vertices.size(); i++) {
        marks.push(vertices[i].mark);
    }
    return marks;
}

template <typename V_type, typename E_type>
Vector<Vertex<V_type>> Graph<V_type, E_type>::get_vertices() {
    return vertices;
}

template <typename V_type, typename E_type>
Vector<Edge<V_type, E_type>> Graph<V_type, E_type>::get_edges() {
    return edges;
}

template <typename V_type, typename E_type>
E_type Graph<V_type, E_type>::get_edge_mark(size_t a, size_t b) {
    if (a >= vertices.size() || b >= vertices.size()) {
        std::out_of_range("Неверные индексы при получении пометки ребра");
        return E_type();
    }
    if (!is_bounded(a, b)) {
        std::out_of_range("Вершины не связан");
        return E_type();
    }
    return edges[edge_index(a, b)].mark;
}

template <typename V_type, typename E_type>
bool Graph<V_type, E_type>::is_bounded(size_t a, size_t b) {
    if (a >= vertices.size() || b >= vertices.size()) {
        throw std::out_of_range("Неверные индексы при проверки связанности");
    }
    for (size_t i = 0; i < edges.size(); i++)
        if (edges[i].start->number == a && edges[i].destination->number == b)
            return true;
    return false;
}

template <typename V_type, typename E_type>
int Graph<V_type, E_type>::edge_index(size_t a, size_t b) {
    if (a < vertices.size() && b < vertices.size()) {
        for (size_t i = 0; i < edges.size(); i++) {
            if (edges[i].start->number == a && edges[i].destination->number == b)
                return i;
        }
    }
    else
        std::out_of_range("Неверные индесы при получении индекса ребра");
    return -1;
}

template <typename V_type, typename E_type>
Vector<Vector<unsigned int>> Graph<V_type, E_type>::get_matrix() {
    return matrix;
}

template <typename V_type, typename E_type>
class Graph<V_type, E_type>::Iterator {
public:
    Iterator(Graph<V_type, E_type>* graph, size_t index, size_t neib)
        : graph(graph), start_index(index), next_edge_index(neib) {}

    Iterator& operator++() {
        Vector<Edge<V_type, E_type>> edges = graph->get_edges();
        Vector<unsigned int> matrix = graph->get_matrix()[start_index];
        for (size_t i = next_edge_index + 1; i < edges.size(); i++) {
            if(edges[i].start->number == start_index) {
                next_edge_index = i;
                return *this;
            }
        }
        next_edge_index = edges.size();
        return *this;
    }

    bool operator!=(const Iterator iterator) {
        return next_edge_index != iterator.next_edge_index ? true : false;
    }

    Vertex<V_type> operator*() {
        return graph->get_vertex_by_index(graph->get_edges()[next_edge_index].destination->number);
    }

    size_t edge_index() {
        return next_edge_index;
    }
private:
    Graph<V_type, E_type>* graph;
    size_t start_index = std::numeric_limits<size_t>::max();
    size_t next_edge_index = std::numeric_limits<size_t>::max();
};

template <typename V_type, typename E_type>
typename Graph<V_type, E_type>::Iterator Graph<V_type, E_type>::begin(size_t index) {
    if (index >= vertices.size())
        std::out_of_range("Неверный индекс при инициализации итератора");

    for (size_t i = 0; i < edges.size(); i++) {
        if (edges[i].start->number == index) {
            return Iterator(this, index, i);
        }
    }

    return Iterator(this, index, edges.size());
}

template <typename V_type, typename E_type>
typename Graph<V_type, E_type>::Iterator Graph<V_type, E_type>::end(size_t index) {
    if (index >= vertices.size())
        std::out_of_range("Неверный индекс при инициализации итератора");

    return Iterator(this, index, edges.size());
}

template <typename V_type, typename E_type>
std::ostream& operator<<(std::ostream& out, Graph<V_type, E_type> graph) {
    Vector<Vertex<V_type>> vertex = graph.get_vertices();
    Vector<Edge<V_type, E_type>> edges = graph.get_edges();
    Vector<Vector<unsigned int>> matrix = graph.get_matrix();
    out << "Adjacency matrix:\n\n";
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++)
            out << matrix[i][j] << " ";
        out << std::endl;
    }
    out << std::endl;
    for (size_t i = 0; i < vertex.size(); i++) {
        out << "Index: " << vertex[i].number << ", mark: " << vertex[i].mark << std::endl;
        int count = 0;
        for (size_t k = 0; k < matrix[i].size(); k++)
            matrix[i][k] != 0 ? count += matrix[i][k] : count;
        if(count)
            out << "   Edges: " << count << "\n";
        for (size_t j = 0; j < edges.size(); j++) {
            if (edges[j].start->number == i) {
                out << "      " << edges[j].start->number << " (" << edges[j].start->mark << ") -> " << edges[j].destination->number << " (" << edges[j].destination->mark << "): " << edges[j].mark << '\n';
            }
        }
        auto it = graph.begin(vertex[i].number);
        if (it != graph.end(vertex[i].number)) {
            out << "   Neighbours:\n";
            for (; it != graph.end(vertex[i].number); ++it) {
                out << "      Index: " << (*it).number << ", mark: " << (*it).mark << std::endl;
            }
            out << std::endl;
        }
    }
    return out;
}

#endif