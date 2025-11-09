#include "queue.h"

Queue::Queue() : atail(nullptr)
{
}

void Queue::copyqueue(const Queue& a)
{
    alist = a.alist;

    // ќбновл€ем указатель на хвост
    if (a.atail != nullptr) {
        // Ќаходим хвост в новом списке
        List::Item* curr = alist.first();
        while (curr != nullptr && curr->next() != nullptr) {
            curr = curr->next();
        }
        atail = curr;
    }
    else {
        atail = nullptr;
    }
}

Queue::Queue(const Queue& a) 
{
    // implement or disable this function
    
    copyqueue(a);
}

Queue& Queue::operator=(const Queue& a)
{
    // implement or disable this function
    if (this != &a) {
        copyqueue(a);
    }
    return *this;
}

Queue::~Queue()
{
    // ƒеструктор List автоматически очистит пам€ть
    // Ќе нужно €вно удал€ть atail, так как он €вл€етс€ частью alist

}

void Queue::insert(Data data)
{
    if (empty()) {
        // ≈сли очередь пуста, вставл€ем первый элемент
        alist.insert(data);
        atail = alist.first(); // хвост указывает на единственный элемент
    }
    else {
        // ¬ставл€ем после хвоста и обновл€ем хвост
        atail = alist.insert_after(atail, data);
    }
}

Data Queue::get() const
{
    if (empty()) {
        // ¬озвращаем значение по умолчанию, если очередь пуста
        return Data();
    }
    else {
        const List::Item* first = alist.first();
        return first->data();
    }
}

void Queue::remove()
{
    if (!empty()) {
        alist.erase_first();

        // ≈сли после удалени€ очередь стала пустой, обновл€ем atail
        if (alist.first() == nullptr) {
            atail = nullptr;
        }
    }
}

bool Queue::empty() const
{
    // »спользуем first() который возвращает const Item*
    return alist.first() == nullptr;
}