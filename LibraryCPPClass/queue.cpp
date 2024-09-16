#include "queue.h"
#include <queue>

Queue::Queue(){
}

Queue::Queue(const Queue &a){
    _queue = a._queue;
}

Queue &Queue::operator=(const Queue &a)
{
    return *this;
}

Queue::~Queue(){
    while (!_queue.empty()) {
        _queue.pop();
    }
}

void Queue::insert(Data data){
    _queue.push(data);
}

Data Queue::get() const {
    return _queue.front();
}

void Queue::remove(){
    _queue.pop();
}

bool Queue::empty() const {
    return _queue.empty();
}
