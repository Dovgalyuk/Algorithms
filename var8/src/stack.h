#ifndef STACK_H
#define STACK_H

// � ������ ������ � ����� �������� ������ ���� int,
// ������� ������� ������ �� ������ ��������� � ���������� 
// ������ ����� ����
struct Stack;

// �������� ������� �����
Stack *stack_create();

// �������� �����
void stack_delete(Stack *stack);

// ��������� �������� � ����
void stack_push(Stack *stack, int Data);

// ��������� ���������� �������� �����
int stack_get(Stack *stack);

// ������������ �������� �� �����
void stack_pop(Stack *stack);

// �������� ����� �� ������� ���������
bool stack_empty(Stack *stack);

#endif
