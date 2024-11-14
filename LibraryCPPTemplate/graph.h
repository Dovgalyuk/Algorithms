#pragma once

#define EMPTY_MATRIX_ROW Vector<Vector<Edge<E>>>(vertices.size(), Vector<Edge<E>>(0, Edge<E>()))
#define EMPTY_EDGE_VECTOR Vector<Edge<E>>()
#define TEMPLATE template <typename V, typename E>
#define GRAPH Graph<V, E>
#define MATRIX Vector<Vector<Vector<Edge<E>>>>

#include <iostream>
#include "vector.h"
#include <limits>

template <typename V>
struct Vertex {

    Vertex() {}
    Vertex(size_t number, V mark) : number(number), mark(mark) {}

    size_t number = std::numeric_limits<size_t>::max();
    V mark = V();
};

template <typename E>
struct Edge {

    Edge() {}
    Edge(E mark) : mark(mark) {}

    E mark = E();
};

TEMPLATE
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
        // edges.clear();
        matrix.clear();
    }

    // Добавление вершины без пометки
    Vertex<V>& add_vertex();

    // Добаление вершины с пометкой
    Vertex<V> add_vertex(V vertex_mark);

    // Удалние вершины
    Vertex<V> delete_vertex(size_t a);

    // Получение массива вершин
    const Vector<Vertex<V>> get_vertices();

    // Получение вершины по индексу
    Vertex<V>& get_vertex_by_index(size_t index);

    // Получение массива пометок вершин
    Vector<V> get_vertices_marks();

    // Установка пометки для вершины
    Vertex<V> set_mark(size_t a, V mark);

    // Добавление ребра
    Edge<E> &add_edge(size_t a, size_t b, E edge_mark);

    // Удаление ребра
    Edge<E> delete_edge(size_t a, size_t b, E mark);

    // Получение пометки ребра по индексам вершин
    E get_edge_mark(size_t a, size_t b, size_t edge_index);

    // Проверка связи вершин
    bool is_bounded(size_t a, size_t b);

    // Получение индекса ребра по начальной и конечной точкам
    size_t edge_index(size_t a, size_t b, E mark);

    // Получение матрицы смежности
    const Vector<Vector<Vector<Edge<E>>>> &get_matrix();

    // Класс итератор
    class Iterator;

    // Получение начального состояния итератора
    Iterator begin(size_t index);

    // Получение конечного состояния итератора
    Iterator end(size_t index);
    
    // Вывод информации и графе (вершина и ее соседи)
    template <typename T1, typename T2>
    friend std::ostream& operator<<(std::ostream& out, GRAPH graph);

private:
    // Массив вершин
    Vector<Vertex<V>> vertices;

    // Матрица смежности
    MATRIX matrix;
};

TEMPLATE
Vertex<V> &GRAPH::add_vertex() {
    vertices.push({ vertices.size(), V() });

    matrix.push(EMPTY_MATRIX_ROW);

    for (size_t i = 0; i < matrix.size(); i++) {
        while (matrix[i].size() != vertices.size())
            matrix[i].push(EMPTY_EDGE_VECTOR);
    }

    return vertices[vertices.size() - 1];
}

TEMPLATE
Vertex<V> GRAPH::add_vertex(V vertex_mark) {
    vertices.push({ vertices.size(), vertex_mark });
    matrix.push(EMPTY_MATRIX_ROW);

    for (size_t i = 0; i < matrix.size(); i++) {
        while (matrix[i].size() != vertices.size()) {
            matrix[i].push(EMPTY_EDGE_VECTOR);
        }
    }

    return vertices[vertices.size() - 1];
}

TEMPLATE
Vertex<V> GRAPH::delete_vertex(size_t a) {
    if (a >= vertices.size()) {
        throw std::out_of_range("Неверный индекс при удалении вершины");
        return Vertex<V>();
    }

    matrix.erase(a);
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[i].erase(a);
    }

    Vertex<V> temp = vertices.erase(a);
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].number = i;
    }
    return temp;
}

TEMPLATE
Edge<E> &GRAPH::add_edge(size_t a, size_t b, E edge_mark) {
    if (a >= vertices.size() || b >= vertices.size()) {
        throw std::out_of_range("Неверные индексы при добавлении ребра");
    }

    matrix[a][b].push(edge_mark);
    return matrix[a][b][matrix[a][b].size() - 1];
}

TEMPLATE
Edge<E> GRAPH::delete_edge(size_t a, size_t b, E mark) {
    if ((a >= vertices.size() || b >= vertices.size()) || matrix[a][b].size() <= 0) {
        throw std::out_of_range("Неверные индексы при удалении ребра или ребра не существует");
        return Edge<E>();
    }

    return matrix[a][b].erase(edge_index(a, b, mark));
}

TEMPLATE
Vertex<V> GRAPH::set_mark(size_t a, V mark) {
    if (a < vertices.size())
        vertices[a].mark = mark;
    else
        throw std::out_of_range("Неверный индекс при добавлении пометки вершины");
    return vertices[a];
}

TEMPLATE
Vertex<V>& GRAPH::get_vertex_by_index(size_t index) {
    if(index >= vertices.size()) {
        throw std::out_of_range("Неверный индекс при получении вершины");
    }
    return vertices[index];
}

TEMPLATE
Vector<V> GRAPH::get_vertices_marks() {
    Vector<V> marks;
    for (size_t i = 0; i < vertices.size(); i++) {
        marks.push(vertices[i].mark);
    }
    return marks;
}

TEMPLATE
const Vector<Vertex<V>> GRAPH::get_vertices() {
    return vertices;
}

TEMPLATE
E GRAPH::get_edge_mark(size_t a, size_t b, size_t edge_index) {
    if (a >= vertices.size() || b >= vertices.size()) {
        std::out_of_range("Неверные индексы при получении пометки ребра");
        return E();
    }
    if (!is_bounded(a, b)) {
        std::out_of_range("Вершины не связан");
        return E();
    }
    return matrix[a][b][edge_index].mark;
}

TEMPLATE
bool GRAPH::is_bounded(size_t a, size_t b) {
    if (a >= vertices.size() || b >= vertices.size()) {
        throw std::out_of_range("Неверные индексы при проверки связанности");
    }
    return matrix[a][b].size();
}
TEMPLATE
size_t GRAPH::edge_index(size_t a, size_t b, E mark) {
    if (a >= vertices.size() && b >= vertices.size())
        std::out_of_range("Неверные индесы при получении индекса ребра");

    for (size_t i = 0; i < matrix[a][b].size(); i++) {
        E e_mark = matrix[a][b][i].mark;
        if (matrix[a][b][i].mark == mark)
            return i;
    }

    return std::numeric_limits<size_t>::max();
}

TEMPLATE
const Vector<Vector<Vector<Edge<E>>>> &GRAPH::get_matrix() {
    return matrix;
}

TEMPLATE
class GRAPH::Iterator {
public:
    Iterator(GRAPH* graph, size_t start_index, size_t col, size_t index)
        : graph(graph), start_index(start_index), col(col), index(index) {}

    Iterator& operator++() {
        MATRIX matrix = graph->get_matrix();
        if (index + 1 == matrix[start_index][col].size()) {
            col++;
            while (matrix[start_index][col].size() == 0 && col < matrix[start_index].size()) {
                col++;
            }
            index = 0;
        }
        else {
            index++;
        }
        return *this;
    }

    bool operator!=(const Iterator iterator) {
        return col != iterator.col;
    }

    Edge<E> operator*() {
        return graph->matrix[start_index][col][index];
    }

    size_t get_neib_index() {
        return col;
    }

private:
    GRAPH* graph;
    size_t start_index = std::numeric_limits<size_t>::max();
    size_t col = std::numeric_limits<size_t>::max();
    size_t index = std::numeric_limits<size_t>::max();
};

TEMPLATE
typename GRAPH::Iterator GRAPH::begin(size_t index) {
    if (index >= vertices.size())
        std::out_of_range("Неверный индекс при инициализации итератора");

    for (size_t j = 0; j < matrix[index].size(); j++) {
        if (matrix[index][j].size() != 0) {
            return Iterator(this, index, j, 0);
        }
    }

    return Iterator(this, index, matrix[index].size(), 0);
}

TEMPLATE
typename GRAPH::Iterator GRAPH::end(size_t index) {
    if (index >= vertices.size())
        std::out_of_range("Неверный индекс при инициализации итератора");

    return Iterator(this, index, matrix[index].size(), 0);
}

//TEMPLATE
//std::ostream& operator<<(std::ostream& out, GRAPH graph) {
//    Vector<Vertex<V>> vertex = graph.get_vertices();
//    MATRIX matrix = graph.get_matrix();
//    out << "Adjacency matrix:\n\n";
//    for (size_t i = 0; i < matrix.size(); i++) {
//        for (size_t j = 0; j < matrix[i].size(); j++)
//            out << matrix[i][j].size() << " ";
//        out << std::endl;
//    }
//    out << std::endl;
//    for (size_t i = 0; i < vertex.size(); i++) {
//        out << "Index: " << vertex[i].number << ", mark: " << vertex[i].mark << std::endl;
//        int count = 0;
//        for (size_t k = 0; k < matrix[i].size(); k++)
//            matrix[i][k].size() != 0 ? count += matrix[i][k].size() : count;
//        if(count)
//            out << "   Edges: " << count << "\n";
//        for (size_t j = 0; j < edges.size(); j++) {
//            if (edges[j].start->number == i) {
//                out << "      " << edges[j].start->number << " (" << edges[j].start->mark << ") -> " << edges[j].destination->number << " (" << edges[j].destination->mark << "): " << edges[j].mark << '\n';
//            }
//        }
//        auto it = graph.begin(vertex[i].number);
//        if (it != graph.end(vertex[i].number)) {
//            out << "   Neighbours:\n";
//            for (; it != graph.end(vertex[i].number); ++it) {
//                out << "      Index: " << (*it).number << ", mark: " << (*it).mark << std::endl;
//            }
//            out << std::endl;
//        }
//    }
//    return out;
//}