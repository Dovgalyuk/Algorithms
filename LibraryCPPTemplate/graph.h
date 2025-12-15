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

  void removeVertex(const VertexLabel &name) {
    if (!hasVertex(name))
      return;

    size_t vid = name_to_index_.at(name);
    size_t old_size = vertex_count_;
    size_t new_size = old_size - 1;

    if (new_size == 0) {
      adjacency_matrix_ = Vector<Vector<bool>>();
      edge_labels_ = Vector<Vector<EdgeLabel>>();
      vertex_labels_ = Vector<VertexLabel>();
      index_to_name_ = Vector<VertexLabel>();
      name_to_index_.clear();
      vertex_count_ = 0;
      return;
    }

    Vector<VertexLabel> new_index_to_name;
    new_index_to_name.resize(new_size);

    Vector<VertexLabel> new_vertex_labels;
    new_vertex_labels.resize(new_size);

    Vector<Vector<bool>> new_adj_matrix;
    new_adj_matrix.resize(new_size);
    for (size_t i = 0; i < new_size; i++) {
      new_adj_matrix[i].resize(new_size, false);
    }

    Vector<Vector<EdgeLabel>> new_edge_labels;
    new_edge_labels.resize(new_size);
    for (size_t i = 0; i < new_size; i++) {
      new_edge_labels[i].resize(new_size, EdgeLabel{});
    }

    size_t new_i = 0;
    for (size_t old_i = 0; old_i < old_size; old_i++) {
      if (old_i == vid)
        continue;

      new_index_to_name[new_i] = index_to_name_[old_i];
      new_vertex_labels[new_i] = vertex_labels_[old_i];
      name_to_index_[index_to_name_[old_i]] = new_i;

      size_t new_j = 0;
      for (size_t old_j = 0; old_j < old_size; old_j++) {
        if (old_j == vid)
          continue;
        new_adj_matrix[new_i][new_j] = adjacency_matrix_[old_i][old_j];
        new_edge_labels[new_i][new_j] = edge_labels_[old_i][old_j];
        new_j++;
      }
      new_i++;
    }

    name_to_index_.erase(name);

    index_to_name_ = new_index_to_name;
    vertex_labels_ = new_vertex_labels;
    adjacency_matrix_ = new_adj_matrix;
    edge_labels_ = new_edge_labels;
    vertex_count_ = new_size;
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

#endif
