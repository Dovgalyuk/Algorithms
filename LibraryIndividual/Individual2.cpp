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

int main()
{
	fstream file;
	file.open("input.txt");
	size_t n;
	file >> n;
	Stack* stack = new Stack();
	int coord;
	bool wasPositive = false;
	Data* popped = new Data[n];
	for (int i = 0, j = 0; i < n; i++)
	{
		Quantum current;
		file >> current;
		if (current.mark == '-' && !stack->Empty() && wasPositive)
		{
			Data prevCoord = stack->Get();
			if (prevCoord < current.coord)
			{
				popped[j++] = prevCoord;
				popped[j++] = current.coord;
			}
		}
		else stack->Push(current.coord);

		wasPositive = current.mark == '+';
	}
	for (int i = 0; i < n; i++)
	{
		if (popped[i] > 0) cout << popped[i] << ' ';
	}
}