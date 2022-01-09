#ifndef LIST_H
#define LIST_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return nextItem; }
        void next(Item *newNextItem) {nextItem = newNextItem;} // присвоение след элемента

        Data data() const { return itemData; }

        Item() {
            nextItem = nullptr;
        }
        Item(Data newData, Item *nextItem) {
            itemData = newData;
            this->nextItem = nextItem;
        }
        Item *nextItem;
    private:
        Data itemData;

    };

    // Создает новый список
    List()
    {
        head = nullptr;
    }

    // Уничтожает список и освобождает память
    ~List()
    {
        while(head) {
            Item* temp = head->next();
            delete head;
            head = temp;
        }
    }

    // Извлекает первый элемент из списка
    Item *first()
    {
        return head;
    }

    // Вставляет новый элемент списка в начало
    Item *insert(Data data)
    {
        head = new Item(data, head); // каждый эл хранит ссылку на след элемент
        return head;
    }

    // Вставляет новый элемент списка после указанного элемента
    Item *insert_after(Item *item, Data data)
    {
        item->next(new Item(data, item->next()));
        return item->next();
    }

    // Удаляет указанный элемент списка.
    // Неприменимо для односвязных списков.
    // Должно быть О(1)
    Item *erase(Item *item)
    {
        if(item == head) {

            head = item->next(); // обн ссылки на нач эл

            delete item;
            return head;
        } else {
            Item *cur = head;
            while (cur->next() != item) { //поиск предка иск элемента
                cur = cur->next();
            }
            cur->next(cur->next()->next()); // присвоение след эл после удаленного
            delete item;
            return cur->next();
        }


    }

    // Удаляет элемент списка, следующий за указанным
    // Должно быть О(1)
    Item *erase_next(Item *item)
    {
        if (item->next()) {
            Item *mustBeDeleted = item->next();
            item->next(item->next()->next());
            delete mustBeDeleted;
        }
        return item->next();
    }
private:
    Item *head;
};

#endif
