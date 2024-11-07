
#include "list.h"

// Конструктор копирования
List::List(const List& a) {
    head_ = nullptr;

    if (!a.head_) return;

    // Создаём первый элемент
    head_ = new Item(a.head_->data());
    Item* current = head_;
    Item* a_current = a.head_->next(); 

    // Копируем оставшиеся элементы
    while (a_current) {
        current->set_next(new Item(a_current->data()));
        current = current->next();
        a_current = a_current->next();
    }
}


// Оператор присваивания
List& List::operator=(const List& a) {
    if (this != &a) {
        while (head_) {
            erase_first();
        }
        // Копируем элементы из списка
        for (Item* item = a.first(); item != nullptr; item = item->next()) {
            append(item->data()); // Добавляем элементы в конец
        }
    }
    return *this;
}

// Деструктор
List::~List() {
    while (head_) {
        erase_first();
    }
}

// Вставка элемента в начало списка
List::Item* List::insert(Data data) {
    head_ = new Item(data, head_);
    return head_;
}

// Вставка элемента после заданного элемента
List::Item* List::insert_after(Item* item, Data data) {
    if (!item) return nullptr;
    item->set_next(new Item(data, item->next()));
    return item->next();
}

// Удаление первого элемента списка
List::Item* List::erase_first() {
    if (!head_) return nullptr;
    Item* temp = head_;
    head_ = head_->next();
    delete temp;
    return head_;
}

// Удаление элемента, следующего за данным
List::Item* List::erase_next(Item* item) {
    if (!item || !item->next()) return nullptr;
    Item* temp = item->next();
    item->set_next(temp->next());
    delete temp;
    return item->next();
}

// Вспомогательный метод для добавления элемента в конец списка
void List::append(Data data) {
    if (!head_) {
        head_ = new Item(data);
    } else {
        Item* current = head_;
        while (current->next()) {
            current = current->next();
        }
        current->set_next(new Item(data));
    }
}
