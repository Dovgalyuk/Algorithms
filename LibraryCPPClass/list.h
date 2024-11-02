// list.h

#ifndef LIST_H
#define LIST_H

using Data = int;

class List {
public:
    class Item {
    public:
        Item(Data data, Item* next = nullptr) : data_(data), next_(next) {}
        
        Data data() const { return data_; }
        Item* next() const { return next_; }
        
        void set_next(Item* next) { next_ = next; }
        
    private:
        Data data_;
        Item* next_;
    };

    // Конструктор по умолчанию
    List() : head_(nullptr) {}

    // Конструктор копирования
    List(const List& a);

    // Оператор присваивания
    List& operator=(const List& a);

    // Деструктор
    ~List();

    // Вставка элемента в начало списка
    Item* insert(Data data);

    // Вставка элемента после заданного элемента
    Item* insert_after(Item* item, Data data);

    // Удаление первого элемента списка
    Item* erase_first();

    // Удаление элемента, следующего за данным
    Item* erase_next(Item* item);

    // Возвращает первый элемент списка
    Item* first() const { return head_; }

private:
    Item* head_;

    // Вспомогательный метод для добавления элемента в конец
    void append(Data data);
};

#endif // LIST_H
