#include "queue.h"
#include "vector.h"
#include <algorithm>

Queue::Queue() : vector_(new Vector), head_(-1), rear_(-1) {
    vector_->resize(2);
}

Queue::Queue(const Queue& a) : vector_(new Vector(*(a.vector_))), head_(a.head_), rear_(a.rear_) {}

Queue& Queue::operator=(const Queue& a) {
    if (this != &a) {
        delete vector_;
        vector_ = new Vector(*(a.vector_));
        head_ = a.head_;
        rear_ = a.rear_;
    }
    return *this;
}

Queue::~Queue() { delete vector_; }

void Queue::insert(Data data) {
    size_t size = vector_->size();

    if (empty()) {
        rear_ = 0;
        head_ = 0;
    }
    else if (static_cast<size_t>(rear_) % size == static_cast<size_t>(head_)) {
        Vector* buff = new Vector;
        buff->resize(size * 2);

        int counter = 0;

        for (size_t i = head_; i < size; i++) {
            buff->set(counter, vector_->get(i));
            counter++;
        }
        for (int i = 0; i < rear_; i++) {
            buff->set(counter, vector_->get(i));
            counter++;
        }
        delete vector_;
        vector_ = buff;
        head_ = 0;
        rear_ = size;

        size = vector_->size();
    }

    auto rear = rear_ % size;

    vector_->set(rear, data);
    rear_ = rear + 1;
}

Data Queue::get() const {
    if (!empty()) {
        return vector_->get(head_);
    }
    return Data();
}

void Queue::remove() {
    size_t size = vector_->size();
    auto head = head_;

    if (!empty()) {
        head++;

        if (rear_ == head) {
            head_ = -1;
            rear_ = -1;
        }
        else {
            head_ = head % size;
        }
    }
}

bool Queue::empty() const { return (rear_ == -1 && head_ == -1); }
