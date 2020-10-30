#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

struct Quantum
{
	int coord;
	char mark;

	friend fstream& operator>>(fstream& in, Quantum& quantum)
	{
		in >> quantum.coord >> quantum.mark;
		return in;
	}
	friend fstream& operator<<(fstream& out, const Quantum& quantum)
	{
		out << quantum.coord << quantum.mark;
		return out;
	}
};

void PrintStack(Stack toPrint)
{
	while (!toPrint.Empty())
	{
		Data d = toPrint.Get();
		cout << d << ' ';
		toPrint.Pop();
	}
}

void PrintReverse(Stack toPrint)
{
	Stack* stack = new Stack();
	while (!toPrint.Empty())
	{
		stack->Push(toPrint.Get());
		toPrint.Pop();
	}
	while (!stack->Empty())
	{
		cout << stack->Get() << ' ';
		stack->Pop();
	}
}

int main()
{
	fstream file;
	file.open("input.txt");
	size_t n;
	file >> n;
	Stack* positive = new Stack();
	Stack* negative = new Stack();
	Stack* popped = new Stack();
	int coord;
	Quantum* q = new Quantum[n];
	for (int i = 0; i < n; i++)
	{
		file >> q[i];
	}
	for (int i = 0; i < n; i++)
	{
		Quantum current = q[i];

		if (current.mark == '+')
		{
			positive->Push(current.coord);
			if (!negative->Empty() && negative->Get() > current.coord)
			{
				popped->Push(positive->Get());
				popped->Push(negative->Get());
				positive->Pop();
				negative->Pop();
			}
		}
		else
		{
			negative->Push(current.coord);
			if (!positive->Empty() && positive->Get() < current.coord)
			{
				popped->Push(positive->Get());
				popped->Push(negative->Get());
				positive->Pop();
				negative->Pop();
			}
		}
	}
	PrintReverse(*popped);
}