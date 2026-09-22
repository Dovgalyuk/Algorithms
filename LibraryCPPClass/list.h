#ifndef LIST_H
#define LIST_H

#include <cstddef>

typedef int Data;

class List
{
public:
    class Item
    {
    public:
        Item *next() {
            if (m_next == nullptr) return nullptr;
            return m_next->m_isBarrier ? nullptr : m_next;
        }
        Item *prev() {
            if (m_prev == nullptr) return nullptr;
            return m_prev->m_isBarrier ? nullptr : m_prev;
        }
        Data data() const { return m_data; }

        friend class List;
    private:
        Item *m_next = nullptr;
        Item *m_prev = nullptr;
        Data m_data = 0;
        bool m_isBarrier = false;
    };
    
    List();
    List(const List &a);
    List &operator=(const List &a);
    ~List();

    Item *first();
    Item *last();
    Item *insert(Data data);
    Item *insert_after(Item *item, Data data);
    Item *erase_first();
    Item *erase_next(Item *item);

private:
    Item *m_barrier;
    void clear();
};

#endif