#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "vector.h"
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

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

    string operator*() const { return graph_->index_to_name_[current_]; }
  };

private:
  Vector<Vector<bool>> adjacency_matrix_;
  Vector<string> vertex_labels_;
  Vector<Vector<string>> edge_labels_;
  unordered_map<string, size_t> name_to_index_;
  Vector<string> index_to_name_;
  size_t vertex_count_;

  void expand(size_t new_size) {
    if (new_size <= vertex_count_)
      return;
    adjacency_matrix_.resize(new_size);
    vertex_labels_.resize(new_size, "");
    edge_labels_.resize(new_size);
    for (size_t i = 0; i < new_size; i++) {
      adjacency_matrix_[i].resize(new_size, false);
      edge_labels_[i].resize(new_size, "");
    }
    vertex_count_ = new_size;
  }

public:
  explicit Graph(size_t n = 0) : vertex_count_(0) { expand(n); }

  void addVertex(const string &name) {
    if (name_to_index_.find(name) != name_to_index_.end())
      return;
    name_to_index_[name] = vertex_count_;
    index_to_name_.push_back(name);
    expand(vertex_count_ + 1);
  }

  void addEdge(const string &from, const string &to) {
    if (name_to_index_.find(from) == name_to_index_.end() ||
        name_to_index_.find(to) == name_to_index_.end())
      return;
    size_t i = name_to_index_[from];
    size_t j = name_to_index_[to];
    adjacency_matrix_[i][j] = true;
  }

  void removeEdge(const string &from, const string &to) {
    if (name_to_index_.find(from) == name_to_index_.end() ||
        name_to_index_.find(to) == name_to_index_.end())
      return;
    size_t i = name_to_index_[from];
    size_t j = name_to_index_[to];
    adjacency_matrix_[i][j] = false;
  }

  bool hasEdge(const string &from, const string &to) const {
    if (name_to_index_.find(from) == name_to_index_.end() ||
        name_to_index_.find(to) == name_to_index_.end())
      return false;
    size_t i = name_to_index_.at(from);
    size_t j = name_to_index_.at(to);
    return adjacency_matrix_[i][j];
  }

  bool hasVertex(const string &name) const {
    return name_to_index_.find(name) != name_to_index_.end();
  }

  void setVertexLabel(const string &name, const string &label) {
    if (!hasVertex(name))
      return;
    vertex_labels_[name_to_index_[name]] = label;
  }

  string getVertexLabel(const string &name) const {
    if (!hasVertex(name))
      return "";
    return vertex_labels_[name_to_index_.at(name)];
  }

  void setEdgeLabel(const string &from, const string &to, const string &label) {
    if (!hasVertex(from) || !hasVertex(to))
      return;
    size_t i = name_to_index_[from];
    size_t j = name_to_index_[to];
    edge_labels_[i][j] = label;
  }

  string getEdgeLabel(const string &from, const string &to) const {
    if (!hasVertex(from) || !hasVertex(to))
      return "";
    size_t i = name_to_index_.at(from);
    size_t j = name_to_index_.at(to);
    return edge_labels_[i][j];
  }

  vector<string> getAllVertexLabels() const {
    vector<string> labels;
    for (size_t i = 0; i < vertex_count_; i++) {
      labels.push_back(vertex_labels_[i]);
    }
    return labels;
  }

  vector<string> getVertexNames() const {
    vector<string> names;
    for (size_t i = 0; i < index_to_name_.size(); i++) {
      names.push_back(index_to_name_[i]);
    }
    return names;
  }

  NeighborIterator beginNeighbors(const string &v) const {
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

  NeighborIterator endNeighbors(const string &v) const {
    return NeighborIterator(this, 0, vertex_count_);
  }

  size_t getVertexIndex(const string &name) const {
    return name_to_index_.at(name);
  }

  size_t vertexCount() const { return name_to_index_.size(); }
};

#endif
