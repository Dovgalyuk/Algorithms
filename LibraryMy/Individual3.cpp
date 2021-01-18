#include <iostream>
#include "queue.h"
using namespace std;

int main()
{
	string str;
	cin >> str;

	string result;
	Queue* queue = queue_create();
	for (int i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]))
		{
			queue_insert(queue, str[i]);
		}
		else if (isalpha(str[i]))
		{
			result += str[i];
		}
	}
	while (!queue_empty(queue))
	{
		result += queue_get(queue);
		queue_remove(queue);
	}
	cout << endl << result;
}