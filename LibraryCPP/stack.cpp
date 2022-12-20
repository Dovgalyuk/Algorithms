//Стэк работает по принципу "Первый вошёл, последний вышел", поэтому последний элемент, который мы помещаемь в список, мы будем извлекать в первую очередь

#include "stack.h"
#include "list.h"

//Структура стэка
struct Stack
{
    //В стэкэ у нас содержится наш список
    List* list;
    //Конструктор
    Stack()
    {
        //Создаём список
        list = list_create();
        //Присваиваем первому элементу произвольное значение, мы не будет его использовать, он нужен, чтобы мы могли работать с первым элементов стекав
        list_insert(list, 'a');
    }
};

//Функция создаёт стэк
Stack* stack_create()
{
    return new Stack();
}

//Функция удаляет стэк
void stack_delete(Stack* stack)
{
     
    list_delete(stack->list);
    delete stack;
}

//Функция добавляет новый элемент в стэк
void stack_push(Stack* stack, Data data)
{
    //Добавляем новый элемент после первого элемента списка
    list_insert_after(stack->list, list_first(stack->list), data);
}

//Функция извлекает данные из стэка
Data stack_get(const Stack* stack)
{
    //Возвращаем данные элемента, который расположен после первого элемента списка
    return (list_item_data(list_item_next(list_first(stack->list))));
}

//Функция удаляет элемент из стэка
void stack_pop(Stack* stack)
{
    //Удаляем элемент, который расположен после первого элемента списка
    list_erase_next(stack->list, list_first(stack->list));
}

//Функция проверяет пуст список или нет
bool stack_empty(const Stack* stack)
{
    //Если первый элемент указывает на nullptr, значит в стэке нет элементов
    if (list_item_next(list_first(stack->list)) == nullptr)
        return true;
    else
        return false;
}
