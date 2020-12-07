#ifndef QUEUE_H
#define QUEUE_H

#include <stack>
using namespace std;

//Реализация очереди с помощью двух модулей stack
class queue {
private:
	stack<char> s1;	//Стек s1
	stack<char> s2;	//Стек s2

	//Метод перемещения элементов из одного стека в другую
	void moveBetweenStacks(stack<char> &st1, stack <char> &st2) {
		while (!st1.empty())	//Пока стек s1 не будет пустым...
		{
			st2.push(st1.top());	//...вставляем элемент из s1 в s2...
			st1.pop();				//...и удаляем данный элемент в s1
		}
	}
	
public:
	//Метод добавления элемента в очередь
	void push(int n)
	{
		s1.push(n);	//Вставляем новый элемент в s2
	}

	//Метод удаления первого элемента из очереди
	void pop()
	{
	if (s2.empty()) {				//Если s2 пустой, то
			moveBetweenStacks(s1, s2);	//Переносим все элементы во 2 стек
		}
		s2.pop();					//Удаляем первый элемент
	}

	//Получение значения первого элемента
	int front() {
		if (s2.empty()) {
			moveBetweenStacks(s1, s2);	//Переносим все элементы во 2 стек
		}
		return s2.top();	//Получаем значение первого элемента
	}

	//Обращение к последнему элементу
	int back() {
		return s1.top();	//Получаем значение последнего элемента
	}

	//Проверка очереди на пустоту
	bool empty() {
		if (s1.empty()&& s2.empty())
			return true;
		else
			return false;
	}
};

#endif
