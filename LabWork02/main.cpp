// Write a program that uses a breadth-first search and displays a list of substances that can be obtained from the source.
// Example: Input: "A A->B B->C D->E" - Output: "B C"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "vector.h"
#include "queue.h"

using namespace std;

int main()
{
	ifstream fileIn("input.txt");
	ofstream fileOut("output.txt");

	Queue* queue = queue_create();
	string iData = "";
	char sourceElement = 0;
	char firstElement = 0;
	char secondElement = 0;
	char temp = 0;

	if (fileIn)
	{
		while (!fileIn.eof())
		{
			getline(fileIn, iData);
			transform(iData.begin(), iData.end(), iData.begin(), ::toupper);

			if (iData.size() == 1)
			{
				sourceElement = iData[0];
			}
			else
			{
				firstElement = iData[0];
				secondElement = iData[3];

				if (sourceElement == firstElement || temp == firstElement)
				{
					queue_insert(queue, secondElement);
					temp = secondElement;
				}				
			}
		}
	}
	else
	{
		cout << "Unable to open file!" << endl;
		system("pause");
		return 0;
	}
	while (!queue_empty(queue))
	{
		cout << queue_get(queue) << endl;
		fileOut << queue_get(queue) << endl;
		queue_remove(queue);
	}
	fileIn.close();
	fileOut.close();
	queue_delete(queue);
	return 0;
}