//#include <stdlib.h>
//#include "stack.h"
//
//
//template <typename T>
//MyStack<T>::MyStack()
//{
//    _array = new Array<T>(10);
//}
//
//template <typename T>
//MyStack<T>::~MyStack()
//{
//    delete _array;
//}
//
//template <typename T>
//void MyStack<T>::Push(T value)
//{
//    _topIndex++;
//    _array->set(_topIndex, value);
//}
//
//template <typename T>
//T MyStack<T>::Get()
//{
//    if (_topIndex < 0) return;
//    _array->get(_topIndex);
//}
//
//template <typename T>
//void MyStack<T>::Pop()
//{
//    _topIndex--;
//}
//
//template <typename T>
//bool MyStack<T>::Empty()
//{
//    return _topIndex;
//}
