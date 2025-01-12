#include "queue.h"
#include <stdexcept>

Queue::Queue() {
    _front = 0;
    _size = 0;
    _queue = new Vector;
    _queue->resize(2);
}

Queue::Queue(const Queue &a) {
    _front = a._front;
    _size = a._size;
    _queue = a._queue;
}

Queue &Queue::operator=(const Queue &a) {
    if (this != &a) {
        delete _queue;
        _front = a._front;
        _size = a._size;
        _queue = a._queue;
    }
    return *this;
}

Queue::~Queue(){
    _front = 0;
    _size = 0;
    delete _queue;
}

void Queue::insert(Data data) {
    // Если достигли масимума по cap в vector
    if (_size == _queue->cap()) {
        // Делаем нормализацию для кольцего буфера, если буфер полностью заполнен
        for (size_t idx = 0; idx < (_queue->cap() / 2); idx++) {
            size_t idx_front = (_front + idx) % _queue->cap();

            Data bufData = _queue->get(idx);
            _queue->set(idx, _queue->get(idx_front));
            _queue->set(idx_front, bufData);
        }
        _front = 0;
    }

    _queue->resize(_queue->size()+1);
    _queue->set((_front + _size % (int) _queue->size()), data);
    _size++;
}


Data Queue::get() const {
    if (empty()) throw std::runtime_error("Queue is empty");
    return _queue->get(_front);
}

void Queue::remove(){
    if (empty()) throw std::runtime_error("Stack is empty");
    _front = (_front + 1) % (int) _queue->cap();
    _size--;
}

bool Queue::empty() const {
    return _size == 0;
}

size_t Queue::size() const {
    return _size;
}