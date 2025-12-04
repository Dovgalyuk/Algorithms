#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item(const Data &d = Data()) : data(d), next(nullptr), prev(nullptr) {}
        Item *f_next() { return next; }
        Item *f_prev() { return prev; }
        Data f_data() const { return data; }
        

    private:
        // internal data here
        Data data;
        Item *next;
        Item *prev;
        friend class List;
    };

    // Creates new list
    List() : head(nullptr) {}

    // copy constructor
    List(const List &original) : head(nullptr)
    {
        //Сделал
        if (original.head == nullptr)
        {
            return;
        }
        this->head = new Item(original.head->data);
        Item* new_node = nullptr;
        new_node = this->head;

        Item *original_current = original.head->next;

        //Deep copy data
        while (original_current != original.head)
        {
            Item* new_item = new Item (original_current->data);
            new_item->prev = new_node;
            new_node->next = new_item;
            new_node = new_item;


            original_current = original_current->next;
        }
        new_node->next = this->head;
        this->head->prev = new_node;
        
    }

    // assignment operator
    List &operator=(List original) noexcept
    {
        Item* current_head = this->head;
        this->head = original.head;
        original.head= current_head;
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        //Сделал
        
        while (head != nullptr)
        {
           erase_first();
        }
    }

    // Retrieves the first item from the list
   
    Item *first() const
    {
        return head;

    }
    Item *last () const 
    {
        if (head != nullptr)
        {
            return head->f_prev();
        }
        return nullptr;
    }

    // Inserts new list item into the beginning
   
    Item *insert(Data data)
    { 
        // Сделал
        Item *new_item = new Item(data);
        if (this->head == nullptr) // Если список пуст
        {
            this->head = new_item;
            this->head->prev = this->head; // Голова указывает на себя как на предыдущий
            this->head->next = this->head; // Голова указывает на себя как на следующий
        }
        else // Если список не пуст
        {
            Item * old_head=this->head; // Сохраняем старую голову
            Item* old_tail = old_head->prev;
            new_item->next = old_head; // Новый элемент указывает на старую голову
            new_item->prev = old_tail; // Новый элемент указывает на хвост как на предыдущий

            old_head->prev = new_item; // Старая голова указывает на новый элемент как на предыдущий
            old_tail->next = new_item; // Старый хвост указывает на новый элемент как на следующий

            this->head = new_item; // Теперь голова это новый элемент
            
        }
        return new_item;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    // Сделал
    {
       
        if (item == nullptr)
        {
            return insert(data);
        }
        Item *new_node = new Item(data);
        Item *save = item->next; //Сохраняем следующий элемент он будет указывать на head если 2ой элемент добавляется в список из одного элемента а если больше то на следующий
        new_node->prev = item; // Новый элемент указывает на текущий как на предыдущий
        new_node->next = save; // Новый элемент указывает на сохраненный как на следующий 
        item->next = new_node; // Текущий элемент указывает на новый как на следующий
        save->prev = new_node; // Сохраненный элемент указывает на новый как на предыдущий

        return new_node;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first() {
    // Сделал
        if (head == nullptr)
        {
            return nullptr;
        }

        Item *delete_first = this->head;
        Item* old_tail = delete_first->prev;
        if (this->head == old_tail) //Если список был из одного элемента
        {
            this->head = nullptr;
            delete delete_first;
            return nullptr;
        }
        this->head =delete_first->next; // The next node is a head  | Может быть null или value
        // Если список не пустой после удаления
        this->head->prev = old_tail; // tail указывает на новый head как на следующий
        old_tail->next = this->head;
        delete delete_first;
        
        return this->head;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        // Сделал
        if (item == nullptr ) //Если список из одного элемента
        { 
            return erase_first();
        }
        Item *delete_item = item->next;
        if (delete_item == item) //Если нет следующего элемента а список состоит из нескольких элементов
        {
            return erase_first();
        }
        //Если список из нескольких элементов и есть следующий элемент
        
        Item *next_item = delete_item->next;

        item->next = next_item;
        next_item->prev = item;
        
        if (delete_item == this->head->prev)
        {
            this->head->prev = item;
        }
        
        delete delete_item;
        return next_item;
    }

private:
    // private data should be here
    Item *head;
};

#endif
