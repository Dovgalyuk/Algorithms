#ifndef DIRECTED_GRAPH_TEMPLATE_H
#define DIRECTED_GRAPH_TEMPLATE_H

#include <vector>
#include <cmath>
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

    struct VertexIterator {
        DirectedGraph* graph = nullptr;
        size_t index_next_item = 0;

        VertexIterator(DirectedGraph* graph): graph(graph) {}

        Vertex* operator *() {
            return index_next_item < graph->vertices->size() ? graph->get_vertex(index_next_item) : nullptr;
        }

        void operator ++(int i) {
            index_next_item++;
        }
    };

    struct NearVertexIterator {
        DirectedGraph* graph = nullptr;
        size_t root_vertex = 0;
        int last_index = -1;

        NearVertexIterator(DirectedGraph* graph, size_t root_vertex): graph(graph), root_vertex(root_vertex) { last_index = find_next_vertex();}

        int find_next_vertex() {
            for (int i = last_index + 1; i < graph->get_vertex_amount(); ++i) {
                if (graph->contains_edge_between_vertices(root_vertex, i)) {
                    return i;
                }
            }
            return -1;
        }

        Vertex* operator *() {
            return last_index != -1 ? graph->get_vertex(last_index) : nullptr;
        }

        void operator ++(int i) {
            last_index = find_next_vertex();
        }
    };

    Vector<Vertex*>* vertices;

    ///\param vertex_amount - Количество вершин
    DirectedGraph(size_t vertex_amount, Data default_value): matrix(new Vector<Edge*>) {
        vertices = new Vector<Vertex*>;
        vertices->resize(vertex_amount);
        for (int i = 0; i < vertex_amount; ++i) {
            vertices->set(i, new Vertex(default_value));
        }
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
        size_t index = vertices->size();
        vertices->resize(index + 1);
        vertices->set(index, vertex);
        add_vertex_to_matrix();
        return index;
    }
    /// \param first_vertex_index - Индекс вершины, из которой выходит добавляемого ребро
    /// \param second_vertex_index - Индекс вершины, в которую входит добавляемого ребро
    void add_edge(size_t first_vertex_index, size_t second_vertex_index, int weight) {
        Edge* edge = new Edge(get_vertex(first_vertex_index), get_vertex(second_vertex_index), weight);
        add_edge_to_matrix(first_vertex_index, second_vertex_index, edge);
    }
    /// \param index - Индекс удаляемой вершины
    void remove_vertex(size_t index) {
        if (index >= vertices->size()) return;
        for (int i = 0; i < vertices->size() - 1; ++i) {
            vertices->set(i, vertices->get(i + (i >= index)));
        }
        vertices->resize(vertices->size() - 1);
        remove_vertex_from_matrix(index);
    }
    /// \param first_vertex_index - Индекс вершины, из которой выходит удаляемого ребро
    /// \param second_vertex_index - Индекс вершины, в которую входит удаляемого ребро
    void remove_edge(size_t first_vertex_index, size_t second_vertex_index) {
        remove_edge_to_matrix(first_vertex_index, second_vertex_index);
    }
    /// \param index - Индекс вершины, которую хотите взять
    /// \return Возвращает найденную вершину
    Vertex* get_vertex(size_t index) {
        return vertices->get(index);
    }
    /// \param index - Индекс вершины, в которой лежит Data
    /// \return Возвращает Data из найденной вершины
    Data get_vertex_data(size_t index) {
        return vertices->get(index)->data;
    }
    ///\return Возвращает количество вершин
    size_t get_vertex_amount() {
        return vertices->size();
    }
    /// \param first_vertex_index - Индекс вершины, из которой выходит ребро
    /// \param second_vertex_index - Индекс вершины, в которую входит ребро
    /// \return Возвращает найденное ребро
    Edge* get_edge(size_t first_vertex_index, size_t second_vertex_index) {
        return get_edge_to_matrix(first_vertex_index, second_vertex_index);
    }
    /// \param first_vertex_index - Индекс вершины, из которой выходит ребро
    /// \param second_vertex_index - Индекс вершины, в которую входит ребро
    /// \return Возвращает вес ребра
    int get_edge_weight(size_t first_vertex_index, size_t second_vertex_index) {
        return get_edge(first_vertex_index, second_vertex_index)->weight;
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
    ///\param index - Индекс вершины, которой надо присвоить Data
    ///\param data - Присваиваемые данные
    void set_vertex_data(size_t index, Data data) {
        vertices->get(index)->data = data;
    }
    /// \param first_vertex_index - Индекс вершины, из которой выходит ребро
    /// \param second_vertex_index - Индекс вершины, в которую входит ребро
    ///\param weight - Присваиваемый вес
    void set_edge_weight(size_t first_vertex_index, size_t second_vertex_index, int weight) {
        get_edge(first_vertex_index, second_vertex_index)->weight = weight;
    }
    /// \param first_vertex_index - Индекс вершины, из которой выходит ребро
    /// \param second_vertex_index - Индекс вершины, в которую входит ребро
    /// \return Возвращает true, если ребро, с такими верщинами, существует
    bool contains_edge_between_vertices(size_t first_vertex_index, size_t second_vertex_index) {
        Edge* edge = get_edge_to_matrix(first_vertex_index, second_vertex_index);
        return edge != nullptr;
    }
    /// \return Возвращает итератор-структуру вершин
    VertexIterator get_vertex_iterator() {
        return VertexIterator(this);
    }
    ///\return Возвращает итератор соседей вершины с указанным индексом
    NearVertexIterator get_near_vertex_iterator(size_t root_index) {
        return NearVertexIterator(this, root_index);
    }
protected:
    Vector<Edge*>* matrix;

    void fill_matrix_with_null() {
        for (int i = 0; i < matrix->size(); ++i) {
            matrix->set(i, nullptr);
        }
    }

    void remove_vertex_from_matrix(size_t removed_vertex_index) {
        int vertex_amount = get_vertex_amount();
        Vector<Edge*>* new_matrix = new Vector<Edge*>;
        new_matrix->resize(vertex_amount * vertex_amount);
        int amount_vertex_in_old_matrix = sqrt(matrix->size());
        for (int i = 0; i < vertex_amount; ++i) {
            for (int j = 0; j < vertex_amount; ++j) {
                Edge* edge = matrix->get(((i + (i >= removed_vertex_index)) * amount_vertex_in_old_matrix) + (j + (j >= removed_vertex_index)));
                new_matrix->set((i * vertex_amount) + j, edge);
            }
        }
        delete matrix;
        matrix = new_matrix;
    }

    void add_vertex_to_matrix() {
        int vertex_amount = get_vertex_amount();
        Vector<Edge*>* new_matrix = new Vector<Edge*>;
        new_matrix->resize(vertex_amount * vertex_amount);
        int amount_vertex_in_old_matrix = sqrt(matrix->size());
        for (int i = 0; i < amount_vertex_in_old_matrix; ++i) {
            for (int j = 0; j < amount_vertex_in_old_matrix; ++j) {
                new_matrix->set((i * vertex_amount) + j, matrix->get(i * amount_vertex_in_old_matrix+ j));
            }
        }
        delete matrix;
        matrix = new_matrix;
    }

    size_t get_edge_index_in_matrix(size_t first_vertex_index, size_t second_vertex_index) {
        return first_vertex_index * get_vertex_amount() + second_vertex_index;
    }

    void add_edge_to_matrix(size_t first_vertex_index, size_t second_vertex_index, Edge* edge) {
        matrix->set(get_edge_index_in_matrix(first_vertex_index, second_vertex_index), edge);
    }

    void remove_edge_to_matrix(size_t first_vertex_index, size_t second_vertex_index) {
        matrix->set(get_edge_index_in_matrix(first_vertex_index, second_vertex_index), nullptr);
    }

    Edge* get_edge_to_matrix(size_t first_vertex_index, size_t second_vertex_index) {
        return matrix->get(get_edge_index_in_matrix(first_vertex_index, second_vertex_index)) ;
    }
};
#endif