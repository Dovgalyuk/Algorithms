#include <iostream>
#include <fstream>
#include "../LibraryCPPTemplate/stack.h"

using namespace std;

struct Quantum
{
	Data coord;
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
	Data* popped = new Data[n];
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		Quantum current;
		file >> current;
		if (current.mark == '-' && !stack->Empty())
		{
			Data prevCoord = stack->Get();

			popped[j++] = prevCoord;
			popped[j++] = current.coord;
		}
		else if (current.mark == '+') stack->Push(current.coord);
	}
	for (int i = 0; i < j; i++)
	{
		cout << popped[i] << ' ';
	}
}