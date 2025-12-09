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

        size_t next() {
            if (!hasNext()) throw std::runtime_error("No more neighbors");

            try {
                Edge edge = edge_iter.next();

                if (edge.to_vertex >= graph->vertices.size()) {
                    std::cerr << "ERROR: Invalid neighbor index: " << edge.to_vertex
                        << " for vertex " << current_vertex
                        << " (total vertices: " << graph->vertices.size() << ")" << std::endl;
                    throw std::runtime_error("Invalid neighbor index in edge");
                }

                return edge.to_vertex;
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

                        Edge updated_edge(edge.to_vertex - 1, edge.label);
                        updated_edges.insert(updated_edge);
                    }
                    else if (edge.to_vertex < vertex) {

                        updated_edges.insert(edge);
                    }
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

    Vector<Vector<size_t>> findAllShortestPaths(size_t start, size_t end) const;

    ~Graph() = default;
};

template<typename VertexLabel, typename EdgeLabel>
Vector<Vector<size_t>> Graph<VertexLabel, EdgeLabel>::findAllShortestPaths(size_t start, size_t end) const {
    if (start >= getVertexCount()) {
        std::cerr << "ERROR: Invalid start vertex index: " << start
            << " (vertex count: " << getVertexCount() << ")" << std::endl;
        return Vector<Vector<size_t>>();
    }

    if (end >= getVertexCount()) {
        std::cerr << "ERROR: Invalid end vertex index: " << end
            << " (vertex count: " << getVertexCount() << ")" << std::endl;
        return Vector<Vector<size_t>>();
    }

    if (start == end) {
        Vector<Vector<size_t>> result;
        Vector<size_t> single_path;
        single_path.push_back(start);
        result.push_back(single_path);
        return result;
    }

    Vector<int> distance;
    distance.resize(getVertexCount());
    for (size_t i = 0; i < getVertexCount(); ++i) {
        distance.set(i, -1);
    }

    Vector<Vector<size_t>> predecessors;
    predecessors.resize(getVertexCount());

    std::queue<size_t> q;

    distance.set(start, 0);
    q.push(start);

    while (!q.empty()) {
        size_t current = q.front();
        q.pop();

        auto neighbors_iter = getNeighbors(current);

        while (neighbors_iter.hasNext()) {
            try {
                size_t neighbor = neighbors_iter.next();

                if (neighbor >= getVertexCount()) {
                    std::cerr << "WARNING: Invalid neighbor index returned: " << neighbor
                        << " for vertex " << current
                        << " (vertex count: " << getVertexCount() << ")" << std::endl;
                    continue;
                }

                int current_dist = distance.get(current);

                if (distance.get(neighbor) == -1) {
                    distance.set(neighbor, current_dist + 1);
                    predecessors[neighbor].push_back(current);
                    q.push(neighbor);
                }
                else if (distance.get(neighbor) == current_dist + 1) {
                    predecessors[neighbor].push_back(current);
                }
            }
            catch (const std::exception& e) {
                std::cerr << "ERROR processing neighbors of vertex " << current << ": "
                    << e.what() << std::endl;
            }
        }
    }

    if (distance.get(end) == -1) {
        return Vector<Vector<size_t>>();
    }

    Vector<Vector<size_t>> all_paths;
    Vector<size_t> current_path;

    std::function<void(size_t)> backtrack = [&](size_t node) {
        if (node >= getVertexCount()) {
            std::cerr << "ERROR: Invalid vertex index in backtrack: " << node << std::endl;
            return;
        }

        current_path.push_back(node);

        if (node == start) {

            Vector<size_t> path;
            for (int i = static_cast<int>(current_path.size()) - 1; i >= 0; --i) {
                path.push_back(current_path[i]);
            }
            all_paths.push_back(path);
        }
        else {
            const Vector<size_t>& preds = predecessors[node];
            for (size_t i = 0; i < preds.size(); ++i) {
                size_t pred = preds[i];
                if (pred >= getVertexCount()) {
                    std::cerr << "WARNING: Invalid predecessor index: " << pred
                        << " for vertex " << node << std::endl;
                    continue;
                }
                backtrack(pred);
            }
        }

        if (current_path.size() > 0) {
            current_path.erase(current_path.size() - 1);
        }
        };

    backtrack(end);

    if (all_paths.size() > 0) {
        std::vector<Vector<size_t>> temp_paths;
        for (size_t i = 0; i < all_paths.size(); ++i) {
            temp_paths.push_back(all_paths[i]);
        }

        std::sort(temp_paths.begin(), temp_paths.end(),
            [](const Vector<size_t>& a, const Vector<size_t>& b) {
                if (a.size() != b.size()) {
                    return a.size() < b.size();
                }
                for (size_t i = 0; i < a.size(); ++i) {
                    if (a[i] != b[i]) {
                        return a[i] < b[i];
                    }
                }
                return false;
            });

        all_paths.clear();
        for (const auto& path : temp_paths) {
            all_paths.push_back(path);
        }
    }

    return all_paths;
}

#endif