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

    //vertices_q++;
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
    if (a >= vertices.size())
        return Vertex<V_type>();

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
    //vertices_q--;
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].number = i;
    }
    return temp;
}

template <typename V_type, typename E_type>
Edge<V_type, E_type> Graph<V_type, E_type>::add_edge(size_t a, size_t b, E_type edge_mark) {
    if (a >= vertices.size() && b >= vertices.size())
        return Edge<V_type, E_type>();

    edges.push(Edge<V_type, E_type>(&get_vertex_by_index(a), &get_vertex_by_index(b), edge_mark));
    matrix[a][b]++;
    return edges[edges.size() - 1];
}

template <typename V_type, typename E_type>
Edge<V_type, E_type> Graph<V_type, E_type>::delete_edge(size_t a, size_t b) {
    if ((a >= vertices.size() && b >= vertices.size()) || matrix[a][b] <= 0)
        return Edge<V_type, E_type>();

    matrix[a][b]--;
    return edges.erase(edge_index(a, b));
}

template <typename V_type, typename E_type>
Vertex<V_type> Graph<V_type, E_type>::set_mark(size_t a, V_type mark) {
    if (a < vertices.size())
        vertices[a].mark = mark;
    return vertices[a];
}

template <typename V_type, typename E_type>
Vertex<V_type>& Graph<V_type, E_type>::get_vertex_by_index(size_t index) {
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
bool Graph<V_type, E_type>::is_bounded(size_t a, size_t b) {
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
        : graph(graph), start_index(index), next_index(neib) {}

    Iterator& operator++() {
        Vector<unsigned int> v_neib = graph->get_matrix()[start_index];
        for (size_t i = next_index + 1; i < v_neib.size(); i++) {
            if (v_neib[i]) {
                next_index = i;
                return *this;
            }
        }
        next_index = v_neib.size();
        return *this;
    }

    bool operator!=(const Iterator iterator) {
        return next_index != iterator.next_index ? true : false;
    }

    const Vertex<V_type> operator*() {
        return graph->get_vertex_by_index(next_index);
    }

private:
    Graph<V_type, E_type>* graph;
    size_t start_index = 0;
    size_t next_index = 0;
};

template <typename V_type, typename E_type>
typename Graph<V_type, E_type>::Iterator Graph<V_type, E_type>::begin(size_t index) {
    size_t neib = matrix[index].size();
    for (size_t i = 0; i < matrix[index].size(); i++) {
        if (matrix[index][i] != 0) {
            neib = i;
            break;
        }
    }

    return Iterator(this, index, neib);
}

template <typename V_type, typename E_type>
typename Graph<V_type, E_type>::Iterator Graph<V_type, E_type>::end(size_t index) {
    return Iterator(this, index, matrix[index].size());
}

template <typename V_type, typename E_type>
std::ostream& operator<<(std::ostream& out, Graph<V_type, E_type> graph) {
    Vector<Vertex<V_type>> vertex = graph.get_vertices();
    Vector<Edge<V_type, E_type>> edges = graph.get_edges();
    Vector<Vector<unsigned int>> matrix = graph.get_matrix();

    for (size_t i = 0; i < vertex.size(); i++) {
        out << "Index: " << vertex[i].number << ", mark: " << vertex[i].mark << std::endl;
        int count = 0;
        for (size_t k = 0; k < matrix[i].size(); k++)
            matrix[i][k] != 0 ? count += matrix[i][k] : count;
        out << "\tEdges: " << count << "\n";
        auto it = graph.begin(vertex[i].number);
        if (it != graph.end(vertex[i].number)) {
            out << "\tNeighbours:\n";
            for (; it != graph.end(vertex[i].number); ++it) {
                out << "\t\tIndex: " << (*it).number << ", mark: " << (*it).mark << std::endl;
            }
        }
        out << std::endl;
    }

    return out;
}

#endif