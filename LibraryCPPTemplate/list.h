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
        

    protected:
        // internal data here
        Data data;
        Item *next;
        Item *prev;
        friend class List;
    };

    // Creates new list
    List() : head(nullptr), tail(nullptr) {}

    // copy constructor
    List(const List &original) : head(nullptr), tail(nullptr)
    {
        //Сделал
        if (original.head == nullptr)
        {
            return;
        }
        this->head = new Item(original.head->data);
        this->tail = this->head;

        Item *original_current = original.head->next;

        //Deep copy data
        while (original_current != original.head)
        {
            Item* new_item = new Item (original_current->data);
            new_item->prev = this->tail;
            this->tail->next = new_item;
            this->tail = new_item;


            original_current = original_current->next;
        }
        this->tail->next = this->head;
        this->head->prev = this->tail;
        
    }

    // assignment operator
    List &operator=(const List &original)
    {
        //Сделал
        if (this != &original)
        {
            //Очистка старого списка от старых данных для избежания утечки памяти и копирования новых данных
            while (this->head != nullptr)
            {
               erase_first();
            }

            if (original.head == nullptr)
            {
                return *this;
            }
            this->head = new Item(original.head->data);
            this->tail = this->head;

            Item *original_current = original.head->next;

            // Deep copy data
            while (original_current != original.head)
            {
                Item *new_item = new Item(original_current->data);
                new_item->prev = this->tail;
                this->tail->next = new_item;
                this->tail = new_item;

                original_current = original_current->next;
            }
            this->tail->next = this->head;
            this->head->prev = this->tail;
        }
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

    // Inserts new list item into the beginning
   
    Item *insert(Data data)
    { 
        // Сделал
        Item *new_item = new Item(data);

        if (this->head == nullptr) // Если список пуст
        {
            this->head = new_item;
            this->tail = new_item;
            this->head->prev = this->head; // Голова указывает на себя как на предыдущий
            this->head->next = this->head; // Голова указывает на себя как на следующий
        }
        else // Если список не пуст
        {
            Item * old_head=this->head; // Сохраняем старую голову
            Item * old_tail = this->tail; // Сохраняем старый хвост

            new_item->next = old_head; // Новый элемент указывает на старую голову
            new_item->prev = old_tail;  // Новый элемент указывает на хвост как на предыдущий

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

        if (this->tail == item)
        {
            this->tail = new_node;
        }
       

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

        if (this->head == this->tail) //Если список был из одного элемента
        {
            this->head = nullptr;
            this->tail = nullptr;
            delete delete_first;
            return nullptr;
        }
        this->head = this->head->next; // The next node is a head  | Может быть null или value
        // Если список не пустой после удаления
        this->head->prev = this->tail; // Новый head указывает на tail как
        this->tail->next = this->head; // tail указывает на новый head как на следующий
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
        
        if (delete_item == this->tail)
        {
            this->tail = item;
        }
        
        delete delete_item;
        return next_item;
    }

private:
    // private data should be here
    Item *head;
    Item *tail;
};

#endif
