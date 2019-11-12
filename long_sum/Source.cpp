#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
	Queue* data = queue_create();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		queue_insert(data, temp);
	}
	int ost = 0;
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		int sum = ost + temp + queue_get(data);
		queue_remove(data);
		ost = sum / 10;
		sum = sum % 10;
		cout << sum << endl;
	}
	if (ost)
		cout << ost;
	queue_remove(data);
}