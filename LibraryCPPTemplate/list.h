#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return next_; }
        Item *prev() { return prev_; }
        Data& data() { return data_; }
        const Data& data() const { return data_; }

    private:
        // internal data here
        Item *next_ = nullptr;
		Item* prev_ = nullptr;
		Data data_;

		Item(Data d) : data_(d) {}

		friend class List<Data>;
    };

    // Creates new list
    List() : first_(nullptr), last_(nullptr)
    {
    }

    // copy constructor
    List(const List &a)
    {
        first_ = last_ = nullptr;
        Item* current = a.first_;
        Item* prevItem = nullptr;

        while (current) {
            Item* newItem = new Item(current->data_);

            if (!first_) {
                first_ = newItem;
            }

            newItem->prev_ = prevItem;

            if (prevItem) {
                prevItem->next_ = newItem;
            }

            prevItem = newItem;
            current = current->next_;
        }
        last_ = prevItem;

    }

    // assignment operator
    List& operator=(const List& a)
    {
        if (this != &a) {

            clear();
            Item* current = a.first_;
            Item* prevItem = nullptr;

            while (current) {

                Item* newItem = new Item(current->data_);

                if (!first_) {
                    first_ = newItem;
                }

                newItem->prev_ = prevItem;

                if (prevItem) {
                    prevItem->next_ = newItem;
                }

                prevItem = newItem;
                current = current->next_;

            }

            last_ = prevItem;
        }
		return *this;
        
    }

    // Destroys the list and frees the memory
    ~List()
    {
		clear();
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return first_;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
		Item* newItem = new Item(data);
		newItem->next_ = first_;

        if (first_) {
            first_->prev_ = newItem;
        } else {
            last_ = newItem;
        }

		first_ = newItem;
		return newItem;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr) {
			return insert(data);
        }

		Item* newItem = new Item(data);
		newItem->next_ = item->next_;
		newItem->prev_ = item;

		if (item->next_) {
			item->next_->prev_ = newItem;
		}
        else {
            last_ = newItem;
        }

		item->next_ = newItem;
		return newItem;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (first_ == nullptr) {
            return nullptr;
        }

		Item* next = first_->next_;
		delete first_;

		if (next) {
			next->prev_ = nullptr;
		}
		else {
			last_ = nullptr;
		}

		first_ = next;
		return next;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr) {
			return erase_first();
        }

		Item* toDelete = item->next_;

        if (!toDelete) {
			return nullptr;
        }

		Item* next = toDelete->next_;
		item->next_ = next;

		if (next) {
			next->prev_ = item;
            }
        else {
            last_ = item;
        }

		delete toDelete;
		return next;
    }
private:
    // private data should be here
	Item* first_;
	Item* last_;

	void clear() {
		Item* current = first_;

		while (current) {

			Item* next = current->next_;

			delete current;
			current = next;
		}

		first_ = last_ =  nullptr;
	}
};

#endif
