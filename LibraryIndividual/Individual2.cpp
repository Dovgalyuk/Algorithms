#include <iostream>
#include <fstream>
#include "..\..\..\..\..\..\Projects\Algorithms\LibraryCPP\stack.h"

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
	Stack* stack = new Stack();
	int coord;
	Quantum* q = new Quantum[n];
	for (int i = 0; i < n; i++)
	{
		file >> q[i];
	}
	for (int i = 0; i < n - 1; i++)
	{
		Quantum first = q[i];
		Quantum second = q[i + 1];
		if (first.coord < second.coord && (first.mark == '+' && second.mark == '-'
			|| first.coord > second.coord && (first.mark == '-' && second.mark == '+')))
		{
			stack->Push(first.coord);
			stack->Push(second.coord);
			i++;
		}
	}
	PrintReverse(*stack);
}