#include <iostream>
#include <string>
#include <fstream>
#include "queue.h"

using namespace std;

void addNumbers(Queue* first, Queue* second)
{
	ofstream fout;
	fout.open("..\\..\\..\\..\\Lab3CPP\\output.txt");
	bool carryOver = 0;
	int n;
	while (!queue_empty(first))
	{
		n = queue_get(first) + queue_get(second);
		cout << n % 10 + carryOver << '\n';
		fout << n % 10 + carryOver << '\n';
		carryOver = n / 10;
		queue_remove(first);
		queue_remove(second);
	}
	if (carryOver)
	{
		cout << carryOver << '\n';
		fout << carryOver << '\n';
	}
	fout.close();
}

int main()
{
	Queue* first = queue_create(), * second = queue_create();

	ifstream fin;
	fin.open("input.txt");
	string line;
	getline(fin, line);

	size_t len = line[0] - '0';
	for (size_t i = 0; i < len * 2; i++)
	{
		getline(fin, line);
		if (i < len)
			queue_insert(first, line[0] - '0');
		else
			queue_insert(second, line[0] - '0');
	}
	fin.close();

	addNumbers(first, second);

	queue_delete(first);
	queue_delete(second);
}
