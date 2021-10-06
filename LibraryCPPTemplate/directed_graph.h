#ifndef DIRECTED_GRAPH_TEMPLATE_H
#define DIRECTED_GRAPH_TEMPLATE_H

#include <vector>
#include "vector.h"

template <typename Data> class DirectedGraph {
public:
    struct Vertex {
        Data data;
        Vertex(Data data): data(data) {}
    };

    struct Edge {
        Vertex* first;
        Vertex* second;
        int weight;
        Edge(Vertex* first, Vertex* second, int weight): first(first), second(second), weight(weight) {}
    };

    struct Iterator {
        DirectedGraph* graph = nullptr;
        size_t index_next_item = 0;

        Iterator(DirectedGraph* graph): graph(graph) {}

        Vertex* operator *() {
            return index_next_item < graph->vertices->size() ? graph->get_vertex(index_next_item) : nullptr;
        }

        void operator ++(int i) {
            index_next_item++;
        }
    };

    size_t vertex_amount = 0;
    Vector<Vertex*>* vertices;

    ///\param vertex_amount - Количество вершин
    explicit DirectedGraph(size_t vertex_amount): vertex_amount(vertex_amount), matrix(new Vector<Edge*>), vertices(new Vector<Vertex*>) {
        matrix->resize(vertex_amount * vertex_amount);
        fill_matrix_with_null();
    }

    ~DirectedGraph() {
        delete matrix;
        delete vertices;
    }
    ///\param data - Данные, котрые надо добавить в новую вершину
    ///\return Вернёт индекс добавленной вершины, но если граф переполнен, то вернёт -1
    size_t add_vertex(Data data) {
        return add_vertex(new Vertex(data));
    }
    ///\param vertex - Добавляемая вершина
    ///\return Вернёт индекс добавленной вершины, но если граф переполнен, то вернёт -1
    size_t add_vertex(Vertex* vertex) {
        if (vertices->size() == vertex_amount) return -1;
        size_t index = vertices->size();
        vertices->resize(index + 1);
        vertices->set(index, vertex);
        return index;
    }
    /// \param index_first_vertex - Индекс вершины, из которой выходит добавляемого ребро
    /// \param index_second_vertex - Индекс вершины, в которую входит добавляемого ребро
    void add_edge(size_t index_first_vertex, size_t index_second_vertex, int weight) {
        Edge* edge = new Edge(get_vertex(index_first_vertex), get_vertex(index_second_vertex), weight);
        add_edge_to_matrix(index_first_vertex, index_second_vertex, edge);
    }
    /// \param index - Индекс удаляемой вершины
    void remove_vertex(size_t index) {
        if (index >= vertices->size()) return;
        int id = 0;
        for (int i = 0; i < vertices->size(); ++i) {
            if (i != index) {
                vertices->set(id++, vertices->get(i));
            }
        }
        vertices->resize(vertices->size() - 1);
    }
    /// \param index_first_vertex - Индекс вершины, из которой выходит удаляемого ребро
    /// \param index_second_vertex - Индекс вершины, в которую входит удаляемого ребро
    void remove_edge(size_t index_first_vertex, size_t index_second_vertex) {
        remove_edge_to_matrix(index_first_vertex, index_second_vertex);
    }
    /// \param index - Индекс вершины, которую хотите взять
    /// \return Возвращает найденную вершину
    Vertex* get_vertex(size_t index) {
        return vertices->get(index);
    }
    ///\param data - Данные, которые нужно добавить в новую вершину
    ///\param index - Индекс, под которым должна лежать вершина
    void set_vertex(size_t index, Data data) {
        set_vertex(index, new Vertex(data));
    }
    ///\param vertex - Вершина, которую хотим добавить
    ///\param index - Индекс, под которым должна лежать вершина
    void set_vertex(size_t index, Vertex* vertex) {
        if (index >= vertices->size()) return;
        vertices->set(index, vertex);
    }
    /// \param index_first_vertex - Индекс вершины, из которой выходит ребро
    /// \param index_second_vertex - Индекс вершины, в которую входит ребро
    /// \return Возвращает найденное ребро
    Edge* get_edge(size_t index_first_vertex, size_t index_second_vertex) {
        return get_edge_to_matrix(index_first_vertex, index_second_vertex);
    }
    /// \param index - Индекс вершины, в которой лежит Data
    /// \return Возвращает Data из найденной вершины
    Data get_vertex_data(size_t index) {
        return vertices->get(index)->data;
    }
    ///\param index - Индекс вершины, которой надо присвоить Data
    ///\param data - Присваиваемые данные
    void set_vertex_data(size_t index, Data data) {
        vertices->get(index)->data = data;
    }
    /// \param index_first_vertex - Индекс вершины, из которой выходит ребро
    /// \param index_second_vertex - Индекс вершины, в которую входит ребро
    /// \return Возвращает вес ребра
    int get_edge_weight(size_t index_first_vertex, size_t index_second_vertex) {
        return get_edge(index_first_vertex, index_second_vertex)->weight;
    }
    /// \param index_first_vertex - Индекс вершины, из которой выходит ребро
    /// \param index_second_vertex - Индекс вершины, в которую входит ребро
    ///\param weight - Присваиваемый вес
    void set_edge_weight(size_t index_first_vertex, size_t index_second_vertex, int weight) {
        get_edge(index_first_vertex, index_second_vertex)->weight = weight;
    }
    /// \param index_first_vertex - Индекс вершины, из которой выходит ребро
    /// \param index_second_vertex - Индекс вершины, в которую входит ребро
    /// \return Возвращает true, если ребро, с такими верщинами, существует
    bool contains_edge_between_vertices(size_t index_first_vertex, size_t index_second_vertex) {
        Edge* edge = get_edge_to_matrix(index_first_vertex, index_second_vertex);
        return edge != nullptr;
    }
    ///\param index - Индекс вершины, соседей которых надо найти
    std::vector<int> get_near_vertices(size_t index) {
        std::vector<int> result;
        for (int i = 0; i < vertex_amount; ++i) {
            if (contains_edge_between_vertices(index, i)) {
                result.push_back(i);
            }
        }
        return result;
    }
    /// \return Возвращает итератор-структуру
    Iterator get_iterator() {
        return Iterator(this);
    }
protected:
    Vector<Edge*>* matrix;

    void fill_matrix_with_null() {
        for (int i = 0; i < matrix->size(); ++i) {
            matrix->set(i, nullptr);
        }
    }

    size_t get_edge_index_in_matrix(size_t index_first_vertex, size_t index_second_vertex) {
        return index_first_vertex * vertex_amount + index_second_vertex;
    }

    void add_edge_to_matrix(size_t index_first_vertex, size_t index_second_vertex, Edge* edge) {
        matrix->set(get_edge_index_in_matrix(index_first_vertex, index_second_vertex), edge);
    }

    void remove_edge_to_matrix(size_t index_first_vertex, size_t index_second_vertex) {
        matrix->set(get_edge_index_in_matrix(index_first_vertex, index_second_vertex), nullptr);
    }

    Edge* get_edge_to_matrix(size_t index_first_vertex, size_t index_second_vertex) {
        return matrix->get(get_edge_index_in_matrix(index_first_vertex, index_second_vertex)) ;
    }
};
#endif