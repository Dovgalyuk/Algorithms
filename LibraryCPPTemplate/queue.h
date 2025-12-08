#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"
#include <stdexcept>

using namespace std;

template <typename T> class Queue {
private:
  Vector<T> data_;

public:
  void push(const T &item) { data_.push_back(item); }

  void pop() {
    if (empty())
      throw out_of_range("Queue is empty");
    for (size_t i = 1; i < data_.size(); i++)
      data_[i - 1] = data_[i];
    data_.pop_back();
  }

  T &front() {
    if (empty())
      throw out_of_range("Queue is empty");
    return data_[0];
  }

  const T &front() const {
    if (empty())
      throw out_of_range("Queue is empty");
    return data_[0];
  }

  bool empty() const { return data_.empty(); }

  size_t size() const { return data_.size(); }
};

#endif
