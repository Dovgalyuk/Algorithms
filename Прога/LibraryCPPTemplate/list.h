#ifndef LIST_H
#define LIST_H

template<typename Data>
class List {
public:
    class Item {
    public:
        Item *next() { return next_; }

        Item *prev() { return prev_; }

        Data data() const { return data_; }

        void SetPrev(Item *item) { prev_ = item; }

        void SetNext(Item *item) { next_ = item; }

        void SetData(Data data) { data_ = data; }

    private:
        Item *next_;
        Item *prev_;
        Data data_;
    };

    // Creates new list
    List() : head_(nullptr) {}

    // Destroys the list and frees the memory
    ~List() {
        Item *curr = head_;
        while (curr != nullptr) {
            head_ = curr->next();
            delete curr;
            curr = head_;
        }
        delete head_;
    }

    // Retrieves the first item from the list
    Item *first() {
        return head_;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data) {
        if (head_ == nullptr) {
            head_ = new Item;
            head_->SetData(data);
            head_->SetNext(nullptr);
            head_->SetPrev(nullptr);
            return head_;
        }
        else{
            Item* new_node = new Item;
            new_node->SetData(data);
            new_node->SetNext(head_);
            new_node->SetPrev(nullptr);
            head_ = new_node;
            return head_;
        }
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data) {
        Item* new_node = new Item;
        new_node->SetData(data);
        if (item->next() != nullptr) {
            new_node->SetNext(item->next());
            item->next()->SetPrev(new_node);
        }
        new_node->SetPrev(item);
        item->SetNext(new_node);
        return new_node;
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item) {
        Item* temp_prev = item->prev();
        Item* temp_next = item->next();
        if (temp_prev != nullptr) {
            temp_prev->SetNext(item->next());
        } else {
            head_ = item->next();
        }
        if (temp_next != nullptr) {
            temp_next->SetPrev(item->prev());
        }
        delete item;
        return temp_next;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item) {
        if(item->next() == nullptr) {
            return nullptr;
        }
        auto *NextItem = item->next()->next();
        auto *DeletedItem = item->next();
        item->SetNext(NextItem);
        NextItem->SetPrev(item);
        delete DeletedItem;
        return NextItem;
    }

private:
    Item *head_;
};

#endif
