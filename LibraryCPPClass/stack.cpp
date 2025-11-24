#include "stack.h"


Stack::Stack() : list() {}

Stack::Stack(const Stack& a) : list(a.list) {}

Stack& Stack::operator=(const Stack& a)
{
    if (this != &a)
        list = a.list;
    return *this;
}

Stack::~Stack() {}

void Stack::push(Data data)
{
    list.insert(data);
}

Data Stack::get() const
{
    List::Item* f = list.first();
    return f ? f->data() : Data();
}

void Stack::pop()
{
    list.erase_first();
}

bool Stack::empty() const
{
    return list.first() == nullptr;
}

void Stack::remove_bottom()
{
    if (list.empty()) return;

    List::Item* first = list.first();
    List::Item* last = list.last();

    if (first == last)
    {
        list.erase_first();
        return;
    }

    List::Item* cur = first;
    while (cur && cur->next() != last)
        cur = cur->next();

    if (!cur) return;

    list.erase(last);
}

void Stack::reverse()
{

    List tmp;

    Stack helper;
    while (!empty())
    {
        helper.push(get());
        pop();
    }
    while (!helper.empty())
    {
        push(helper.get());
        helper.pop();
    }
}

std::string Stack::join_to_string() const
{

    std::string out;

    std::vector<char> v;
    for (List::Item* it = list.first(); it != nullptr; it = it->next())
    {
        v.push_back((char)it->data());
    }
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        out.push_back(*it);

    return out;
}