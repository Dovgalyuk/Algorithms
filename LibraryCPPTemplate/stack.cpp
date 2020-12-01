#include <stdlib.h>
#include "../LibraryCPPTemplate/stack.h"

Stack::Stack()
{
    _vec = new Vector();
}

Stack::~Stack()
{
    delete _vec;
    delete this;
}

void Stack::Push(Data data)
{
    size_t newSize = _vec->GetSize() + 1;
    _vec->Resize(newSize);
    _vec->Set(newSize - 1, data);
}

Data Stack::Get()
{
    return _vec->GetValue(_vec->GetSize() - 1);
}

void Stack::Pop()
{
    _vec->Resize(_vec->GetSize() - 1);
}

bool Stack::Empty()
{
    if (_vec->GetSize() == 0) return true;
    return false;
}
