#pragma once

#define EMPTY_MATRIX_ROW Vector<Edge<E>*>(vertices.size(), nullptr)
#define TEMPLATE template <typename V, typename E>
#define GRAPH Graph<V, E>
#define MATRIX Vector<Vector<Edge<E>*>>

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
    // ������� �����������
    Graph() {}

    // ����������� �� ���������� ������
    Graph(int q) {
        for (size_t i = 0; i < q && q > 0; i++) {
            add_vertex();
        }
    }

    // ����������
    ~Graph() {
        vertices.clear();
        for (size_t i = 0; i < matrix.size(); i++) {
            for (auto it = begin(i); it != end(i); ++it) {
                delete (*it);
            }
        }
        matrix.clear();
    }

    // ���������� ������� ��� �������
    Vertex<V>& add_vertex();

    // ��������� ������� � ��������
    Vertex<V> add_vertex(V vertex_mark);

    // ������� �������
    Vertex<V> delete_vertex(size_t a);

    // ��������� ������� ������
    const Vector<Vertex<V>> get_vertices();

    // ��������� ������� �� �������
    Vertex<V>& get_vertex_by_index(size_t index);

    // ��������� ������� ������� ������
    Vector<V> get_vertices_marks();

    // ��������� ������� ��� �������
    Vertex<V> set_mark(size_t a, V mark);

    // ���������� �����
    Edge<E>* add_edge(size_t a, size_t b, E edge_mark);

    // �������� �����
    Edge<E>* delete_edge(size_t a, size_t b);

    // ��������� ������� ����� �� �������� ������
    E get_edge_mark(size_t a, size_t b);

    // �������� ����� ������
    bool is_bounded(size_t a, size_t b);

    // ��������� ������� ����� �� ��������� � �������� ������
    size_t edge_index(size_t a, size_t b, E mark);

    // ��������� ������� ���������
    const Vector<Vector<Edge<E>*>> get_matrix();

    // ����� ��������
    class Iterator;

    // ��������� ���������� ��������� ���������
    Iterator begin(size_t index);

    // ��������� ��������� ��������� ���������
    Iterator end(size_t index);
    
    // ����� ���������� � ����� (������� � �� ������)
    template <typename T1, typename T2>
    friend std::ostream& operator<<(std::ostream& out, GRAPH graph);

private:
    // ������ ������
    Vector<Vertex<V>> vertices;

    // ������� ���������
    MATRIX matrix;
};

TEMPLATE
Vertex<V> &GRAPH::add_vertex() {
    vertices.push({ vertices.size(), V() });

    matrix.push(EMPTY_MATRIX_ROW);

    for (size_t i = 0; i < matrix.size(); i++) {
        while (matrix[i].size() != vertices.size())
            matrix[i].push(nullptr);
    }

    return vertices[vertices.size() - 1];
}

TEMPLATE
Vertex<V> GRAPH::add_vertex(V vertex_mark) {
    vertices.push({ vertices.size(), vertex_mark });
    matrix.push(EMPTY_MATRIX_ROW);

    for (size_t i = 0; i < matrix.size(); i++) {
        while (matrix[i].size() != vertices.size()) {
            matrix[i].push(nullptr);
        }
    }

    return vertices[vertices.size() - 1];
}

TEMPLATE
Vertex<V> GRAPH::delete_vertex(size_t a) {
    if (a >= vertices.size()) {
        throw std::out_of_range("�������� ������ ��� �������� �������");
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
Edge<E>* GRAPH::add_edge(size_t a, size_t b, E edge_mark) {
    if (a >= vertices.size() || b >= vertices.size()) {
        throw std::out_of_range("�������� ������� ��� ���������� �����");
    }

    matrix[a][b] = new Edge<E>(edge_mark);
    return matrix[a][b];
}

TEMPLATE
Edge<E>* GRAPH::delete_edge(size_t a, size_t b) {
    if ((a >= vertices.size() || b >= vertices.size()) || matrix[a][b] == nullptr)
        throw std::out_of_range("�������� ������� ��� �������� ����� ��� ����� �� ����������");

    delete matrix[a][b];
    matrix[a][b] = nullptr;
    return nullptr;
}

TEMPLATE
Vertex<V> GRAPH::set_mark(size_t a, V mark) {
    if (a < vertices.size())
        vertices[a].mark = mark;
    else
        throw std::out_of_range("�������� ������ ��� ���������� ������� �������");
    return vertices[a];
}

TEMPLATE
Vertex<V>& GRAPH::get_vertex_by_index(size_t index) {
    if(index >= vertices.size()) {
        throw std::out_of_range("�������� ������ ��� ��������� �������");
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
E GRAPH::get_edge_mark(size_t a, size_t b) {
    if (a >= vertices.size() || b >= vertices.size()) {
        std::out_of_range("�������� ������� ��� ��������� ������� �����");
        return E();
    }
    if (!is_bounded(a, b)) {
        std::out_of_range("������� �� ������");
        return E();
    }
    return matrix[a][b]->mark;
}

TEMPLATE
bool GRAPH::is_bounded(size_t a, size_t b) {
    if (a >= vertices.size() || b >= vertices.size()) {
        throw std::out_of_range("�������� ������� ��� �������� �����������");
    }
    return matrix[a][b] == nullptr ? false : true;
}

TEMPLATE
const Vector<Vector<Edge<E>*>> GRAPH::get_matrix() {
    return matrix;
}

TEMPLATE
class GRAPH::Iterator {
public:
    Iterator(GRAPH* graph, size_t start_index, size_t col)
        : graph(graph), start_index(start_index), col(col) {}

    Iterator& operator++() {
        MATRIX matrix = graph->get_matrix();
        if (matrix[start_index][++col] == nullptr) {
            while (matrix[start_index][col] == nullptr && col < matrix.size()) {
                ++col;
            }
        }
        return *this;
    }

    bool operator!=(const Iterator iterator) {
        return col != iterator.col;
    }

    Edge<E>* operator*() {
        return graph->matrix[start_index][col];
    }

    size_t get_neib_index() {
        return col;
    }

private:
    GRAPH* graph;
    size_t start_index = std::numeric_limits<size_t>::max();
    size_t col = std::numeric_limits<size_t>::max();
};

TEMPLATE
typename GRAPH::Iterator GRAPH::begin(size_t index) {
    if (index >= vertices.size())
        std::out_of_range("�������� ������ ��� ������������� ���������");

    for (size_t j = 0; j < matrix[index].size(); j++) {
        if (matrix[index][j] != nullptr) {
            return Iterator(this, index, j);
        }
    }

    return Iterator(this, index, matrix[index].size());
}

TEMPLATE
typename GRAPH::Iterator GRAPH::end(size_t index) {
    if (index >= vertices.size())
        std::out_of_range("�������� ������ ��� ������������� ���������");

    return Iterator(this, index, matrix[index].size());
}