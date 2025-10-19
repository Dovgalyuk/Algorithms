#include "stack.h"
#include <stdexcept>
Stack::Stack()
{
    //������ �������������� ������
}

Stack::Stack(const Stack &a):box(a.box)
{
    // implement or disable this function
  
}

Stack &Stack::operator=(const Stack &a)
{
    // implement or disable this function
    box = a.box;
    return *this;
}

Stack::~Stack()
{
    //������������� �� �����
    // ��� ��� vector ��������� � ������
}


//get �������� �������� � index
// 
//set ���������� �������� � index
// 
//size ������� ������ ������� 
// 
// resize �������� ����� ������ �������� ������ �������� 

//�������� � �����
void Stack::push(Data data)
{
    box.resize(box.size() + 1);
    box.set(box.size() - 1, data);
}


//�������� ������� �������
Data Stack::get() const
{
    if (box.size() == 0)
    {
        throw std::out_of_range("ERROR: index out of range");
    }
    return box.get(box.size() - 1);
}
//������� ��������� �������
void Stack::pop()
{
    if (box.size() == 0)
    {
        throw std::out_of_range("Cannot pop from empty stack");
    }
    box.resize(box.size() - 1);
}

bool Stack::empty() const
{
    if (box.size() != 0)
    {
        return false;
    }
    return true;
}
