#include <cstddef>
#include "list.h"

void List::Item::setNextPtr(Item* next){
    this->next_ = next;
}

void List::Item::setPrevPtr(Item* prev){
    this->prev_ = prev;
}

List::List() : head_(NULL), tail_(NULL), size_(0)
{
}

List::List(const List &a) : head_(NULL), tail_(NULL), size_(0)
{
    if(a.head_ == NULL){
        return;
    }
    Item* lastCopy = this->insert(a.head_->data());

    Item* current = a.head_->next();

    while(current != NULL){
        lastCopy = this->insert_after(lastCopy, current->data());
        current = current->next();
    }
}

List &List::operator=(const List &a)
{
    if(this != &a){
        while(head_ != NULL){
            this->erase_first();
        }

        Item* lastCopy = this->insert(a.head_->data());

        Item* current = a.head_->next();

        while(current != NULL){
            lastCopy = this->insert_after(lastCopy, current->data());
            current = current->next();
        }
        
    }
    return *this;
}

List::~List()
{
    while (head_ != NULL) {
        erase_first();
    }
}

List::Item *List::first()
{
    return this->head_;
}

bool List::list_empty() const
{
    return this->head_ == NULL;
}

List::Item *List::insert(Data data)
{
    Item* newItem = new Item(data, this->head_, NULL);
    if(this->head_ != NULL){
        this->head_->setPrevPtr(newItem);
    }
    else {
        this->tail_ = newItem;
    }

    this->head_ = newItem;
    this->size_ ++;

    return newItem;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if(item == NULL){
        return insert(data);
    }

    

    Item *newItem = new Item(data, NULL, item);
    if(item->next() != NULL){
        Item *nextItem = item->next();
        newItem->setNextPtr(nextItem);
        nextItem->setPrevPtr(newItem);
    }

    if(newItem->next() == NULL){
        this->tail_ = newItem;
    }
    item->setNextPtr(newItem);
    this->size_++;
    return newItem;
}

List::Item *List::erase_first()
{
    if(this->head_ == NULL){
        return NULL;
    }

    if(this->head_->next() == NULL){
        this->head_ = NULL;
        this->tail_ = NULL;
        this->size_--;
        return NULL;
    }

    Item *newHead = this->head_->next();
    delete this->head_;
    this->head_ = newHead;
    this->head_->setPrevPtr(NULL);
    this->size_--;
    return this->head_;
}

List::Item *List::erase_next(Item *item)
{
    if(item == NULL){
        return NULL;
    }

    if(item->next() == NULL || item->prev() == NULL){
        delete item;
        this->head_ = NULL;
        this->tail_ = NULL;
        this->size_ --;
        return NULL;
    }

    Item *nextItem = item->next();
    item->setNextPtr(nextItem->next());
    delete nextItem;
    return item->next();
}
// обеспечивает добавление одного элемента O(1) так как он добавляет его в конец (для очереди)
List::Item *List::get_end_item() const {
    return this->tail_;
}

Data List::data_head() const {
    return head_->data();
}
