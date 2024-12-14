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
        // Сдвигаем элементы если достигли максимума в длинне вектора & при этом из масива удаляли элементы
        for (size_t idx = 0; idx < _back - _front; idx++) {
            _queue->set(idx, _queue->get(idx+_front));
        }
        _back -= _front;
        _front = 0;
    } else {
        _queue->insert(data);
        _back++;
    }
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
