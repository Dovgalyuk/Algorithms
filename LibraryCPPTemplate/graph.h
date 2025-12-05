#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include "vector.h"
#include <string>
#include <stdexcept>
#include <functional>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>

template<typename VertexLabel, typename EdgeLabel>
class Graph {
private:
    struct Edge {
        size_t to_vertex;
        EdgeLabel label;
        Edge(size_t to, const EdgeLabel& lbl = EdgeLabel()) : to_vertex(to), label(lbl) {}

        bool operator==(const Edge& other) const {
            return to_vertex == other.to_vertex;
        }
    };

    struct VertexData {
        VertexLabel label;
        List<Edge> edges;

        VertexData() = default;
        VertexData(const VertexLabel& lbl) : label(lbl) {}
    };

    Vector<VertexData> vertices;

public:
    class NeighborIterator {
    private:
        const Graph* graph;
        size_t current_vertex;
        typename List<Edge>::SimpleIterator edge_iter;

    public:
        NeighborIterator(const Graph* g, size_t vertex) : graph(g), current_vertex(vertex) {
            if (vertex < graph->vertices.size()) {

                const VertexData& vertex_data = graph->vertices[vertex];
                edge_iter = vertex_data.edges.getSimpleIterator();
            }
        }

        bool hasNext() const {
            return edge_iter.hasNext();
        }

        int next() {
            if (!hasNext()) throw std::runtime_error("No more neighbors");

            try {
                Edge edge = edge_iter.next();

                if (edge.to_vertex >= graph->vertices.size()) {
                    std::cerr << "ERROR: Invalid neighbor index: " << edge.to_vertex
                        << " for vertex " << current_vertex
                        << " (total vertices: " << graph->vertices.size() << ")" << std::endl;
                    throw std::runtime_error("Invalid neighbor index in edge");
                }

                return static_cast<int>(edge.to_vertex);
            }
            catch (const std::exception& e) {
                std::cerr << "ERROR in NeighborIterator::next(): " << e.what() << std::endl;
                throw;
            }
        }

        EdgeLabel getEdgeLabel() const {
            throw std::runtime_error("Not implemented in this iterator version");
        }
    };

    Graph(size_t initial_vertices = 0) {
        for (size_t i = 0; i < initial_vertices; ++i) {
            vertices.push_back(VertexData());
        }
    }

    size_t addVertex() {
        vertices.push_back(VertexData());
        return vertices.size() - 1;
    }

    size_t addVertex(const VertexLabel& label) {
        vertices.push_back(VertexData(label));
        return vertices.size() - 1;
    }

    bool setVertexLabel(size_t vertex, const VertexLabel& label) {
        if (vertex >= vertices.size()) return false;
        vertices[vertex].label = label;
        return true;
    }

    VertexLabel getVertexLabel(size_t vertex) const {
        if (vertex >= vertices.size()) return VertexLabel();
        return vertices[vertex].label;
    }

    bool addEdge(size_t from, size_t to, const EdgeLabel& label = EdgeLabel()) {
        if (from >= vertices.size() || to >= vertices.size()) {
            std::cerr << "ERROR: Cannot add edge from " << from << " to " << to
                << " (vertices: " << vertices.size() << ")" << std::endl;
            return false;
        }

        VertexData& fromVertex = vertices[from];
        auto iter = fromVertex.edges.getSimpleIterator();
        while (iter.hasNext()) {
            Edge edge = iter.next();
            if (edge.to_vertex == to) {
                return false;
            }
        }

        vertices[from].edges.insert(Edge(to, label));
        return true;
    }

    bool removeEdge(size_t from, size_t to) {
        if (from >= vertices.size() || to >= vertices.size()) {
            return false;
        }

        VertexData& fromVertex = vertices[from];
        auto& edges = fromVertex.edges;

        List<Edge> new_edges;
        bool removed = false;
        auto iter = edges.getSimpleIterator();

        while (iter.hasNext()) {
            Edge edge = iter.next();
            if (edge.to_vertex != to) {
                new_edges.insert(edge);
            }
            else {
                removed = true;
            }
        }

        if (removed) {
            vertices[from].edges = std::move(new_edges);
        }

        return removed;
    }

    bool removeVertex(size_t vertex) {
        if (vertex >= vertices.size()) return false;

        for (size_t i = 0; i < vertices.size(); ++i) {
            if (i != vertex) {
                removeEdge(i, vertex);
            }
        }

        Vector<VertexData> new_vertices;
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (i != vertex) {

                VertexData data = vertices[i];
                List<Edge> updated_edges;
                auto iter = data.edges.getSimpleIterator();

                while (iter.hasNext()) {
                    Edge edge = iter.next();
                    if (edge.to_vertex > vertex) {
                        edge.to_vertex--;
                    }
                    updated_edges.insert(edge);
                }

                data.edges = std::move(updated_edges);
                new_vertices.push_back(data);
            }
        }

        vertices = std::move(new_vertices);
        return true;
    }

    bool hasEdge(size_t from, size_t to) const {
        if (from >= vertices.size() || to >= vertices.size()) {
            return false;
        }

        const VertexData& fromVertex = vertices[from];
        auto iter = fromVertex.edges.getSimpleIterator();
        while (iter.hasNext()) {
            Edge edge = iter.next();
            if (edge.to_vertex == to) {
                return true;
            }
        }
        return false;
    }

    bool setEdgeLabel(size_t from, size_t to, const EdgeLabel& label) {
        if (from >= vertices.size() || to >= vertices.size()) return false;

        if (removeEdge(from, to)) {
            return addEdge(from, to, label);
        }
        return false;
    }

    EdgeLabel getEdgeLabel(size_t from, size_t to) const {
        if (from >= vertices.size() || to >= vertices.size()) return EdgeLabel();

        const VertexData& fromVertex = vertices[from];
        auto iter = fromVertex.edges.getSimpleIterator();
        while (iter.hasNext()) {
            Edge edge = iter.next();
            if (edge.to_vertex == to) {
                return edge.label;
            }
        }
        return EdgeLabel();
    }

    Vector<VertexLabel> getAllVertexLabels() const {
        Vector<VertexLabel> labels;
        for (size_t i = 0; i < vertices.size(); ++i) {
            labels.push_back(vertices[i].label);
        }
        return labels;
    }

    NeighborIterator getNeighbors(size_t vertex) const {
        return NeighborIterator(this, vertex);
    }

    size_t getVertexCount() const { return vertices.size(); }

    std::vector<std::vector<int>> findAllShortestPaths(int start, int end) const;

    ~Graph() = default;
};

template<typename VertexLabel, typename EdgeLabel>
std::vector<std::vector<int>> Graph<VertexLabel, EdgeLabel>::findAllShortestPaths(int start, int end) const {

    if (start < 0 || static_cast<size_t>(start) >= getVertexCount()) {
        std::cerr << "ERROR: Invalid start vertex index: " << start
            << " (vertex count: " << getVertexCount() << ")" << std::endl;
        return {};
    }

    if (end < 0 || static_cast<size_t>(end) >= getVertexCount()) {
        std::cerr << "ERROR: Invalid end vertex index: " << end
            << " (vertex count: " << getVertexCount() << ")" << std::endl;
        return {};
    }

    if (start == end) {
        return { {start} };
    }

    std::vector<int> distance(getVertexCount(), -1);
    std::vector<std::vector<int>> predecessors(getVertexCount());
    std::queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto neighbors_iter = getNeighbors(current);
        int neighbor_count = 0;

        while (neighbors_iter.hasNext()) {
            neighbor_count++;
            try {
                int neighbor = neighbors_iter.next();

                if (neighbor < 0 || static_cast<size_t>(neighbor) >= getVertexCount()) {
                    std::cerr << "WARNING: Invalid neighbor index returned: " << neighbor
                        << " for vertex " << current
                        << " (vertex count: " << getVertexCount() << ")" << std::endl;
                    continue;
                }

                if (distance[neighbor] == -1) {

                    distance[neighbor] = distance[current] + 1;
                    predecessors[neighbor].push_back(current);
                    q.push(neighbor);
                }
                else if (distance[neighbor] == distance[current] + 1) {

                    predecessors[neighbor].push_back(current);
                }
            }
            catch (const std::exception& e) {
                std::cerr << "ERROR processing neighbors of vertex " << current << ": "
                    << e.what() << std::endl;
            }
        }

        if (neighbor_count == 0) {

        }
    }

    if (distance[end] == -1) {
        return {};
    }

    std::vector<std::vector<int>> all_paths;
    std::vector<int> current_path;

    std::function<void(int)> backtrack = [&](int node) {

        if (node < 0 || static_cast<size_t>(node) >= getVertexCount()) {
            std::cerr << "ERROR: Invalid vertex index in backtrack: " << node << std::endl;
            return;
        }

        current_path.push_back(node);

        if (node == start) {

            std::vector<int> path = current_path;
            std::reverse(path.begin(), path.end());
            all_paths.push_back(path);
        }
        else {

            for (int pred : predecessors[node]) {

                if (pred < 0 || static_cast<size_t>(pred) >= getVertexCount()) {
                    std::cerr << "WARNING: Invalid predecessor index: " << pred
                        << " for vertex " << node << std::endl;
                    continue;
                }
                backtrack(pred);
            }
        }

        current_path.pop_back();
        };

    backtrack(end);

    std::sort(all_paths.begin(), all_paths.end());

    return all_paths;
}

#endif