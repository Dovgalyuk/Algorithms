#include <cstddef>
#include "list.h"

void List::Item::setNextPtr(Item* next){
    this->next_ = next;
}

void List::Item::setPrevPtr(Item* prev){
    this->prev_ = prev;
}

List::List() : head_(NULL), tail_(NULL)
{
}

List::List(const List &a) : head_(NULL), tail_(NULL)
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

        if(a.head_ != NULL){
            Item* lastCopy = this->insert(a.head_->data());
            Item* current = a.head_->next();

            while(current != NULL){
                lastCopy = this->insert_after(lastCopy, current->data());
                current = current->next();
            }
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

    return newItem;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if(item == NULL){
        return insert(data);
    }

    Item *newItem = new Item(data);
    
    newItem->setNextPtr(item->next());
    newItem->setPrevPtr(item);
    
    if(item->next() != NULL){
        item->next()->setPrevPtr(newItem);
    }
    item->setNextPtr(newItem);
    
    if(this->tail_ == item){
        this->tail_ = newItem;
    }
    
    return newItem;
}

List::Item *List::erase_first()
{
    if(this->head_ == NULL){
        return NULL;
    }

    Item *toDelete = this->head_;
    this->head_ = this->head_->next();
    
    if(this->head_ != NULL){
        this->head_->setPrevPtr(NULL);
    }
    else {
        this->tail_ = NULL;
    }
    
    delete toDelete;
    
    return this->head_;
}

List::Item *List::erase_next(Item *item)
{
    if(item == NULL){
        return erase_first();
    }
    
    if(item->next() == NULL){
        return NULL;
    }
    
    Item *toDelete = item->next();
    Item *nextAfterDelete = toDelete->next();
    item->setNextPtr(nextAfterDelete);
    
    if(nextAfterDelete != NULL){
        nextAfterDelete->setPrevPtr(item);
    }
    else {
        this->tail_ = item;
    }
    
    delete toDelete;
    
    return nextAfterDelete;
}
// обеспечивает добавление одного элемента O(1) так как он добавляет его в конец (для очереди)
List::Item *List::get_end_item() const {
    return this->tail_;
}

Data List::data_head() const {
    if(this->head_ != NULL){
        return head_->data();
    }
    return Data();
}