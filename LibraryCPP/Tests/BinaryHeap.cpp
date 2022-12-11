#include <iostream>
#include "BinaryHeap.h"
using namespace std;

int main()
{
	Heap* BinH = new Heap;

	int count = 1000000;
	for (int i = 1; i <= count; ++i)
	{
		BinH->Insert(i);
	}
	if (BinH->GetMax() != 1000000)
	{
		cout << "The wrong maximum was detected!\a\n\n";
	}

	BinH->RemoveMax();
	if (BinH->GetMax() == 1000000)
	{
		cout << "The deletion was unsuccessful!\a\n\n";
	}

	while (!BinH->Empty())
	{
		BinH->RemoveMax();
	}
	if (!BinH->Empty())
	{
		cout << "The binary heap is not empty!\a\n\n";
	}

	delete BinH;
}


