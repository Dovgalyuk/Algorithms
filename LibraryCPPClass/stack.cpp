#include "stack.h"

Stack::Stack()
{
}

Stack::Stack(const Stack &a) : helper(a.helper)
{
}

Stack &Stack::operator=(const Stack &a)
{
    if (this != &a)
    {
        helper = a.helper;
    }
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    helper.push_back(data);
}

Data Stack::get() const
{
    if (helper.size() == 0)
    {
        throw std::out_of_range("Stack::get: stack is empty");
    }
    return helper.get(helper.size() - 1);
}

void Stack::pop()
{
    if (helper.size() == 0){
        throw std::out_of_range("Stack::pop: stack is empty");
    }
    helper.resize(helper.size() - 1);
}

bool Stack::empty() const
{
    return helper.size() == 0;
}

size_t Stack::size() const {
    return helper.size();
}

Data Stack::bottom() const {
    if (helper.size() == 0) {
        throw std::out_of_range("Stack::bottom: stack is empty");
    }
    return helper.get(0); // первый элемент вектора — это низ
}

void Stack::remove_bottom() {
    if (helper.size() == 0) {
        throw std::out_of_range("Stack::remove_bottom: stack is empty");
    }
    // Удаляем первый элемент вектора: сдвигаем все влево
    for (size_t i = 0; i + 1 < helper.size(); i++) {
        helper.set(i, helper.get(i + 1));
    }
    helper.resize(helper.size() - 1);
}

Data Stack::join_to_string() const {
    std::string combined;
    for (size_t i = helper.size(); i > 0; i--) {
        combined += helper.get(i - 1);
    }
    return combined;
}

void Stack::push_bottom(Data data) {
    helper.insert(0, data);
}
