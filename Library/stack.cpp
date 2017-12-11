#include <stdlib.h>
#include "stack.h"
#include "vector.h"


struct Stack
{
	Vector * vector;
};

// �������� ������� �����
Stack *stack_create()
{
	Stack * stkak = new Stack;
	stkak->vector = vector_create();
	
	return stkak;
}

// �������� �����
void stack_delete(Stack *stack)
{
	delete stack;
}

// ��������� �������� � ����
void stack_push(Stack *stack, int  Data)
{
	vector_resize(stack->vector,(vector_size(stack->vector))+1);
	vector_set(stack->vector, vector_size(stack->vector)-1, Data);
}

// ��������� ���������� �������� �����
int stack_get(Stack *stack)
{
	
	
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

// ������������ �������� �� �����
void stack_pop(Stack *stack)
{
	vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

// �������� ����� �� ������� ���������
bool stack_empty(Stack *stack)
{
	if (!vector_size(stack->vector))
		return true;
	else
		return false;
}
