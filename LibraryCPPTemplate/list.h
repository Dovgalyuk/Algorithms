#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item(Data data) : previous_item(nullptr), next_item(nullptr), value(data) {}

        Item *next() { return next_item; }
        Item *prev() { return previous_item; }
        Data data() const { return value; }
    private:
        // internal data here
        Item *previous_item;
        Item *next_item;
        Data value;

        friend class List<Data>;
    };

    // Creates new list
    List();

    // copy constructor
    List(const List &a);

    // assignment operator
    List &operator=(const List &a);

    // Destroys the list and frees the memory
    ~List();

    // Retrieves the first item from the list
    Item *first();

    // Inserts new list item into the beginning
    Item *insert(Data data);

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data);

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first();

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item);

private:
    // private data should be here
    Item *first_item;
};

template <typename Data>
List<Data>::List() : first_item(nullptr)
{ }

template <typename Data>
List<Data>::List(const List &a)
{
    first_item = nullptr;
    *this = a;
}

template <typename Data>
List<Data> &List<Data>::operator=(const List &a)
{
    if (this != &a) {
        while (first_item) 
            erase_first();

        for (Item *current_item = a.first_item; current_item; current_item = current_item->next()) 
            insert(current_item->data());
    }

    return *this;
}

template <typename Data>
List<Data>::~List()
{
    while (first_item)
        erase_first();
}

template <typename Data>
typename List<Data>::Item *List<Data>::first()
{
    return first_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::insert(Data val)
{
    Item *new_item = new Item(val);
    new_item->next_item = first_item;
    if (first_item) first_item->previous_item = new_item;
    first_item = new_item;

    return new_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::insert_after(Item *item, Data val)
{
    if (!item)
        throw std::invalid_argument("The item pointer is nullptr");

    Item *new_item = new Item(val);
    new_item->previous_item = item;
    new_item->next_item = item->next_item;
    if (item->next_item) item->next_item->previous_item = new_item;
    item->next_item = new_item;


    return new_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::erase_first()
{
    if (first_item) {
        Item *temp_ptr = first_item->next_item;
        if (temp_ptr) temp_ptr->previous_item = nullptr;
        delete first_item;
        first_item = temp_ptr;
    }

    return first_item;
}

template <typename Data>
typename List<Data>::Item *List<Data>::erase_next(Item *item)
{
    if (!item) return nullptr;
    if (!(item->next_item)) return nullptr;

    Item *ans = item->next_item->next_item;
    delete item->next_item;
    item->next_item = ans;
    if (ans) ans->previous_item = item;

    return ans;
}

#endif
