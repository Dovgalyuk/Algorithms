#include <iostream>
#include "list.h"
#include "stack.h"

using namespace std;

struct Stack
{
    List* top;
};

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* begin;
    ListItem* end;
};

int MUL(int& tempA, int& tempB, int& MULData) {
    MULData = tempA * tempB;
    return MULData;
}

int ADD(int& tempA, int& tempB, int& ADDData) {
    ADDData = tempA + tempB;
    return ADDData;
}

int main()
{
    int tempData = 0; int tempA = 0, tempB = 0, MULData = 0, ADDData = 0, number;

    List* list = list_create();
    Stack* stack = stack_create();

    cout << "Select operation(write the number): \n\n" << "1) 1+2*3\n" << "2) (1+2)*3\n\n";
    cin >> number;
    if (number == 1) {

        cout << "\nPerforming an operation: 1+2*3\n";

        stack_push(stack, 1);
        stack_push(stack, 2);
        stack_push(stack, 3);

        stack_pop(stack, tempData); tempA = tempData;
        stack_pop(stack, tempData); tempB = tempData;

        MUL(tempA, tempB, MULData);

        stack_push(stack, MULData);

        stack_pop(stack, tempData); tempA = tempData;
        stack_pop(stack, tempData); tempB = tempData;

        ADD(tempA, tempB, ADDData);

        stack_push(stack, ADDData);
    }
    else if (number == 2) {

        cout << "\nPerforming an operation: (1+2)*3\n";

        stack_push(stack, 1);
        stack_push(stack, 2);

        stack_pop(stack, tempData); tempA = tempData;
        stack_pop(stack, tempData); tempB = tempData;

        ADD(tempA, tempB, ADDData);

        stack_push(stack, ADDData);
        stack_push(stack, 3);

        stack_pop(stack, tempData); tempA = tempData;
        stack_pop(stack, tempData); tempB = tempData;

        MUL(tempA, tempB, MULData);

        stack_push(stack, MULData);
    }
    else {
        cout << "Error";
    }

    ListItem* temp = stack->top->begin;

    // Проходим по списку, пока не достигнем конца
    while (temp != nullptr)
    {
        // Выводим данные текущего элемента
        cout << "\nThe final result after surgery = " << temp->data << endl;

        // Переходим к следующему элементу списка
        temp = temp->next;
    }

    stack_delete(stack);
    list_delete(list);

    return 0;
}
