#include "queue.h"

Queue::Queue()
{

}

Queue::Queue(const Queue &a)
{
    this->list = a.list;
}

Queue &Queue::operator=(const Queue &a)
{
    this->list = a.list;
    return *this;
}

Queue::~Queue()
{
    
}

void Queue::insert(Data data)
{
     if(this->empty()){
        this->list.insert(data);
     }
     else{
        //обеспечивает добавление одного элемента O(1) так как он добавляет его в конец
        this->list.insert_after(this->list.get_end_item() ,data);
     }

}

Data Queue::get() const
{
    return this->list.data_head();
}

void Queue::remove()
{
    this->list.erase_first();
}

Data Queue::take(){
    Data data = this->get();
    this->remove();
    return data;
}

bool Queue::empty() const
{
    return this->list.list_empty();
}
