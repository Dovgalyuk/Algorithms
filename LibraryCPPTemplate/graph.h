#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "vector.h"
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename VertexLabel = string, typename EdgeLabel = string>
class Graph {
public:
  class NeighborIterator {
    const Graph *graph_;
    size_t vertex_id_;
    size_t current_;

  public:
    NeighborIterator(const Graph *g, size_t v, size_t start)
        : graph_(g), vertex_id_(v), current_(start) {}

    bool operator!=(const NeighborIterator &other) const {
      return current_ != other.current_;
    }

    void operator++() {
      current_++;
      while (current_ < graph_->vertex_count_ &&
             !graph_->adjacency_matrix_[vertex_id_][current_]) {
        current_++;
      }
    }

    VertexLabel operator*() const { return graph_->index_to_name_[current_]; }
  };

private:
  Vector<Vector<bool>> adjacency_matrix_;
  Vector<VertexLabel> vertex_labels_;
  Vector<Vector<EdgeLabel>> edge_labels_;
  unordered_map<VertexLabel, size_t> name_to_index_;
  Vector<VertexLabel> index_to_name_;
  size_t vertex_count_;

  void expand(size_t new_size) {
    if (new_size <= vertex_count_)
      return;
    adjacency_matrix_.resize(new_size);
    vertex_labels_.resize(new_size, VertexLabel{});
    edge_labels_.resize(new_size);
    for (size_t i = 0; i < new_size; i++) {
      adjacency_matrix_[i].resize(new_size, false);
      edge_labels_[i].resize(new_size, EdgeLabel{});
    }
    vertex_count_ = new_size;
  }

public:
  explicit Graph(size_t n = 0) : vertex_count_(0) { expand(n); }

  void addVertex(const VertexLabel &name) {
    if (name_to_index_.find(name) != name_to_index_.end())
      return;
    name_to_index_[name] = vertex_count_;
    index_to_name_.push_back(name);
    expand(vertex_count_ + 1);
  }

  void addEdge(const VertexLabel &from, const VertexLabel &to) {
    if (!hasVertex(from) || !hasVertex(to))
      return;
    size_t i = name_to_index_.at(from);
    size_t j = name_to_index_.at(to);
    adjacency_matrix_[i][j] = true;
  }

  void removeEdge(const VertexLabel &from, const VertexLabel &to) {
    if (!hasVertex(from) || !hasVertex(to))
      return;
    size_t i = name_to_index_.at(from);
    size_t j = name_to_index_.at(to);
    adjacency_matrix_[i][j] = false;
  }

  bool hasEdge(const VertexLabel &from, const VertexLabel &to) const {
    if (!hasVertex(from) || !hasVertex(to))
      return false;
    size_t i = name_to_index_.at(from);
    size_t j = name_to_index_.at(to);
    return adjacency_matrix_[i][j];
  }

  bool hasVertex(const VertexLabel &name) const {
    return name_to_index_.find(name) != name_to_index_.end();
  }

  void setVertexLabel(const VertexLabel &name, const VertexLabel &label) {
    if (!hasVertex(name))
      return;
    vertex_labels_[name_to_index_.at(name)] = label;
  }

  VertexLabel getVertexLabel(const VertexLabel &name) const {
    if (!hasVertex(name))
      return VertexLabel{};
    return vertex_labels_[name_to_index_.at(name)];
  }

  void setEdgeLabel(const VertexLabel &from, const VertexLabel &to,
                    const EdgeLabel &label) {
    if (!hasVertex(from) || !hasVertex(to))
      return;
    size_t i = name_to_index_.at(from);
    size_t j = name_to_index_.at(to);
    edge_labels_[i][j] = label;
  }

  EdgeLabel getEdgeLabel(const VertexLabel &from, const VertexLabel &to) const {
    if (!hasVertex(from) || !hasVertex(to))
      return EdgeLabel{};
    size_t i = name_to_index_.at(from);
    size_t j = name_to_index_.at(to);
    return edge_labels_[i][j];
  }

  vector<VertexLabel> getAllVertexLabels() const {
    vector<VertexLabel> labels;
    for (size_t i = 0; i < vertex_count_; i++) {
      labels.push_back(vertex_labels_[i]);
    }
    return labels;
  }

  vector<VertexLabel> getVertexNames() const {
    vector<VertexLabel> names;
    for (size_t i = 0; i < index_to_name_.size(); i++) {
      names.push_back(index_to_name_[i]);
    }
    return names;
  }

  NeighborIterator beginNeighbors(const VertexLabel &v) const {
    if (!hasVertex(v)) {
      return NeighborIterator(this, 0, vertex_count_);
    }
    size_t vid = name_to_index_.at(v);
    size_t start = 0;
    while (start < vertex_count_ && !adjacency_matrix_[vid][start]) {
      start++;
    }
    return NeighborIterator(this, vid, start);
  }

  NeighborIterator endNeighbors(const VertexLabel &v) const {
    size_t vid = hasVertex(v) ? name_to_index_.at(v) : 0;
    return NeighborIterator(this, vid, vertex_count_);
  }

  size_t getVertexIndex(const VertexLabel &name) const {
    return name_to_index_.at(name);
  }

  size_t vertexCount() const { return name_to_index_.size(); }
};

#endif // GRAPH_TEMPLATE_H
