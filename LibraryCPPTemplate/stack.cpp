#include <stdlib.h>
#include "stack.h"

Stack::Stack()
{
    _vec = new Vector();
}

Stack::~Stack()
{
    delete _vec;
    delete this;
}

void Stack::Push(Data data) const
{
    size_t newSize = _vec->GetSize() + 1;
    _vec->Resize(newSize);
    _vec->Set(newSize - 1, data);
}

Data Stack::Get() const
{
    return _vec->GetValue(_vec->GetSize() - 1);
}

void Stack::Pop() const
{
    _vec->Resize(_vec->GetSize() - 1);
}

bool Stack::Empty() const
{
    if (_vec->GetSize() == 0) return true;
    return false;
}
