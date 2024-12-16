#include "queue.h"
#include <stdexcept>

Queue::Queue() : _front(0), _back(0), _queue(new Vector) {
}

Queue::Queue(const Queue &a) {
    _queue = a._queue;
}

Queue &Queue::operator=(const Queue &a) {
    return *this;
}

Queue::~Queue(){
    _front = 0;
    _back = 0;
    delete _queue;
}

void Queue::insert(Data data) {
    if (_back == _queue->cap() && _front != 0) {
        // Сдвигаем элементы в начало, освобождая место
        for (size_t idx = 0; idx < _back - _front; idx++) {
            _queue->set(idx, _queue->get(idx + _front));
        }
        _queue->resize(_back - _front);
        _back -= _front;
        _front = 0;
    }
    if (_back == _queue->cap()) {
        _queue->resize(_queue->cap() * 2);
    }

    _queue->resize(_back + 1);
    _queue->set(_back, data);
    _back++;
}

Data Queue::get() const {
    if (empty()) throw std::runtime_error("Queue is empty");
    return _queue->get(_front);
}

void Queue::remove(){
    if (empty()) throw std::runtime_error("Stack is empty");
    _front++;
}

bool Queue::empty() const {
    return _back - _front == 0;
}

int Queue::size() const {
    return (int) (_back - _front);
}

void Queue::safeSwap(int n) {
    // Normalize swapN
    int swapN = ((-1 * n) % size() + size()) % size();

    if (swapN == 0) return;

    Vector* buf = new Vector;
    buf->resize(size());
    for (int idx = 0; idx < (int) buf->size(); idx++) {
        buf->set(idx, _queue->get(_front + ((idx + swapN) % size())));
    }
    for (int idx = 0; idx < size(); idx++) {
        _queue->set(_front + idx, buf->get(idx));
    }
    delete buf;
}