#include "queue.h"

Queue::Queue() : atail(nullptr)
{
}

void Queue::copyqueue(const Queue& a)
{
	alist = a.alist;
	List::Item* curr = alist.first();
	while (curr != nullptr && curr->next() != nullptr) {
		curr = curr->next();
	}
	atail = curr;
}

Queue::Queue(const Queue& a) 
{
    copyqueue(a);
}

Queue& Queue::operator=(const Queue& a)
{
    if (this != &a) {
        copyqueue(a);
    }
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (empty()) {
        alist.insert(data);
        atail = alist.first();
    }
    else {
        atail = alist.insert_after(atail, data);
    }
}

Data Queue::get() const
{
    if (empty()) {
        return Data();
    }
    else {
        const List::Item* first = alist.first();
        return first->data();
    }
}

void Queue::remove()
{
    if (!empty()) {
        alist.erase_first();
        if (alist.first() == nullptr) {
            atail = nullptr;
        }
    }
}

bool Queue::empty() const
{
    return alist.first() == nullptr;
}