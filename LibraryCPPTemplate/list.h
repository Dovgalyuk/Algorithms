#ifndef LIST_H
#define LIST_H
#include <functional>

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return _next; } // Указатель на следующий элемент
        Item *prev() { return _prev; } // Указатель на предыдущий элемент
        Data data() const { return _data; }
        Item(Data data, Item* next = nullptr, Item* prev = nullptr): _data(data), _next(next), _prev(prev) {}
        void setPrev(Item* item) {_prev = item;} // Задает новый предыдущий элемент
        void setNext(Item* item) {_next = item;} // Задает новый следующий элемент
    private:
        // internal data here
        Item* _next;
        Item* _prev;
        Data _data;
    };

    // Создает новый список
    List()
    {
        elem = new Item(0); // Элементу присваивается значение 0
        elem->setNext(elem); // Задает следующим элементом самого себя
        elem->setPrev(elem); // Задает предыдущим элементом самого себя
    }

    // Уничтожает список и очищает память
    ~List()
    {
        Item *item = first();
        while (item) {
            if (item == elem)
                break;
            auto *deleted = item;
            item = item->next();
            delete deleted;
        }
        delete elem;
    }

    // Извлекает первый элемент из списка
    Item *first()
    {
        return elem->next();
    }

    // Вставляет новый элемент списка в начало
    Item *insert(Data data)
    {
        return insert_after(elem, data);
    }

    // Вставляет элемент в конец списка
    Item *insert_end(Data data)
    {
        return insert_after(elem->prev(), data); // Вставляем после последнего элемента
    }

    // Вставляет новый элемент списка после указанного элемента
    Item *insert_after(Item *item, Data data)
    {
        Item* newItem = new Item(data); // Создает новый элемент
        newItem->setNext(item->next()); // Новому элементу ставим следующим элементом, который следует после указанного item
        item->next()->setPrev(newItem); // Присваиваем предыдущим новый элемент, следующему после указанного
        newItem->setPrev(item); // Присваем предыдущим элементом указанного item'а новый элемент
        item->setNext(newItem); // Присваем следующий после указанного item'a новый элемент

        return newItem; // Возвращаем новый элемент
    }

    // Удаляет указанный элемент списка.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        item->next()->setPrev(item->prev()); // Присваивает следующему после указанного item предыдущий перед указанным
        item->prev()->setNext(item->next()); // Присваивает предыдущему перед указанным item следующий после указанного
        Item *buff_item = item->next();

        delete item; //Удаляет item
        return buff_item;
    }

    // Удаляет элемент списка, следующий за указанным
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return erase(item->next());
    }


    void showList() {
        Item *num = first();

        while (num != elem)
        {
            std::cout << num->data() << ' ';
            num = num->next();
        }
    }

    //
    bool empty()
    {
        return elem->next() == elem && elem->prev() == elem;
    }

private:
    // private data should be here
    Item* elem = nullptr;
};
#endif