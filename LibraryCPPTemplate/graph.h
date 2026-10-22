#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <limits>
#include <istream>
#include <stdexcept>
#include <memory>
#include "vector.h"

template <typename VertexLabel, typename EdgeLabel>
class Graph
{
public:
    explicit Graph(size_t count = 0)
    {
        if (count != 0 && count > std::numeric_limits<size_t>::max() / count) {
            throw std::length_error("graph is too big");
        }
        vertices.resize(count);
        edges.resize(count * count);
        if (vertices.size() != count || edges.size() != count * count) {
            throw std::length_error("graph is too big");
        }
    }
    size_t size() const{
    return vertices.size();
    }
    VertexLabel get_vertex(size_t index) const{
        if (index >= vertices.size()) {
        throw std::out_of_range("wrong vertex index");
        }
        return vertices.get(index);
    }

    void set_vertex(size_t index, const VertexLabel &label){
        if (index >= vertices.size()) {
            throw std::out_of_range("wrong vertex index");
        }
        vertices.set(index, label);
    }

    bool has_edge(size_t from, size_t to) const{
        if (from >= size() || to >= size()) {
            throw std::out_of_range("wrong vertex index");
        }
        return edges.at(from * size() + to).label != nullptr;
    }

    void add_edge(size_t from, size_t to, const EdgeLabel &label){
        if (from >= size() || to >= size()) {
            throw std::out_of_range("wrong vertex index");
        }
        edges.set(from * size() + to, Edge(label));
    }

    EdgeLabel get_edge(size_t from, size_t to) const{
        if (!has_edge(from, to)) {
            throw std::out_of_range("edge does not exist");
        }
        return *edges.at(from * size() + to).label;
    }

    void set_edge(size_t from, size_t to, const EdgeLabel &label){
        if (!has_edge(from, to)) {
            throw std::out_of_range("edge does not exist");
        }
        add_edge(from, to, label);
    }

    void remove_edge(size_t from, size_t to){
        if (from >= size() || to >= size()) {
            throw std::out_of_range("wrong vertex index");
        }
        edges.set(from * size() + to, Edge());
    }

    Vector<VertexLabel> get_vertices() const{
        return vertices;
    }

    size_t add_vertex(const VertexLabel &label){
        size_t oldsize = size();
        size_t maxsize = std::numeric_limits<size_t>::max();
        if (oldsize == maxsize) {
            throw std::length_error("graph is too big");
        }
        size_t newsize = oldsize + 1;
        if (newsize > maxsize / newsize) {
            throw std::length_error("graph is too big");
        }
        Vector<Edge> new_edges;
        new_edges.resize(newsize * newsize);
        if (new_edges.size() != newsize * newsize) {
            throw std::length_error("graph is too big");
        }
        for (size_t from = 0; from < oldsize; from++) {
            for (size_t to = 0; to < oldsize; to++) {
                Edge edge = edges.get(from * oldsize + to);
                new_edges.set(from * newsize + to, edge);
            }
        }
        Vector<VertexLabel> new_vertices = vertices;
        new_vertices.resize(newsize);
        if (new_vertices.size() != newsize) {
            throw std::length_error("graph is too big");
        }
        new_vertices.set(oldsize, label);
        vertices.swap(new_vertices);
        edges.swap(new_edges);
        return oldsize;
    }
    void remove_vertex(size_t index){
        size_t oldsize = size();
        if (index >= oldsize) {
            throw std::out_of_range("wrong vertex index");
        }
        size_t newsize = oldsize - 1;
        Vector<VertexLabel> new_vertices;
        Vector<Edge> new_edges;
        new_vertices.resize(newsize);
        new_edges.resize(newsize * newsize);
        if (new_vertices.size() != newsize || new_edges.size() != newsize * newsize) {
            throw std::length_error("graph is too big");
        }
        for (size_t from = 0; from < oldsize; from++) {
            if (from == index) continue;
            size_t new_from = from;
            if (from > index) new_from--;
            new_vertices.set(new_from, vertices.get(from));
            for (size_t to = 0; to < oldsize; to++) {
                if (to == index) continue;
                size_t new_to = to;
                if (to > index) new_to--;
                Edge edge = edges.get(from * oldsize + to);
                new_edges.set(new_from * newsize + new_to, edge);
            }
        }
        vertices.swap(new_vertices);
        edges.swap(new_edges);
    }

    size_t find_vertex(const VertexLabel &label) const{
        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices.get(i) == label)
                return i;
        }
        throw std::out_of_range("vertex not found");
    }

    void read(std::istream &input){
        long long vertex_input;
        long long edge_input;
        if (!(input >> vertex_input >> edge_input)) {
            throw std::runtime_error("cant read graph size");
        }
        if (vertex_input < 0 || edge_input < 0) {
            throw std::runtime_error("negative graph size");
        }

        if (static_cast<unsigned long long>(vertex_input) > std::numeric_limits<size_t>::max() ||
            static_cast<unsigned long long>(edge_input) > std::numeric_limits<size_t>::max()) {
            throw std::length_error("graph is too big");
        }
        size_t vertex_count = static_cast<size_t>(vertex_input);
        size_t edge_count = static_cast<size_t>(edge_input);
        Graph temp(vertex_count);
        for (size_t i = 0; i < vertex_count; i++) {
            VertexLabel label;
            if (!(input >> label)) {
                throw std::runtime_error("cant read vertex");
            }
            for (size_t j = 0; j < i; j++) {
                if (temp.get_vertex(j) == label) {
                    throw std::runtime_error("duplicate vertex name");
                }
            }
            temp.set_vertex(i, label);
        }
        for (size_t i = 0; i < edge_count; i++) {
            VertexLabel from;
            VertexLabel to;
            EdgeLabel label;
            if (!(input >> from >> to >> label)) {
                throw std::runtime_error("cant read edge");
            }
            size_t from_index = temp.find_vertex(from);
            size_t to_index = temp.find_vertex(to);
            if (temp.has_edge(from_index, to_index)) {
                throw std::runtime_error("duplicate edge");
            }
            temp.add_edge(from_index, to_index, label);
        }
        vertices.swap(temp.vertices);
        edges.swap(temp.edges);
    }

    struct NeighborIterator {
        const Graph *graph;
        size_t from;
        size_t to;

        NeighborIterator(const Graph *g, size_t vertex): graph(g), from(vertex), to(0){
            if (!graph || from >= graph->size()) {
                throw std::out_of_range("wrong vertex index");
            }
            skip();
        }

        void skip(){
            while (to < graph->size() && !graph->has_edge(from, to))
                to++;
        }

        bool valid() const{
            return to < graph->size();
        }

        size_t get() const{
            if (!valid()) {
                throw std::out_of_range("no more neighbors");
            }
            return to;
        }
        void next(){
            if (valid()) {
                to++;
                skip();
            }
        }
    };

    NeighborIterator neighbors(size_t from) const{
        return NeighborIterator(this, from);
    }
private:
    struct Edge {
        std::unique_ptr<EdgeLabel> label;

        Edge() = default;

        explicit Edge(const EdgeLabel &value): label(new EdgeLabel(value)){
        }

        Edge(const Edge &other){
            if (other.label) {
                label.reset(new EdgeLabel(*other.label));
            }
        }

        Edge &operator=(const Edge &other){
            if (this == &other) return *this;
            Edge temp(other);
            label.swap(temp.label);
            return *this;
        }
    };
    Vector<VertexLabel> vertices;
    Vector<Edge> edges;
};

#endif