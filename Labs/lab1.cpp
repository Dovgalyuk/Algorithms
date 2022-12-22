#include <iostream>
#include "array.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	float summa = 0;
	float soprotivlenie = 0;
	int size = 0;
	cout << "Enter array size: ";
	cin >> size;
	Array* mass = array_create(size);

	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		array_set(mass, i, rand() % 10000 + 1);

	}

	if (size == 1) {
		soprotivlenie = array_get(mass, 0);
	}
	else {
		for (int i = 0; i < size; i++) {
			summa += (1. / array_get(mass, i));
		}
		soprotivlenie = (1. / summa);

	}

	cout << "obshee soprotivlenie = " << soprotivlenie;
	array_delete(mass);
	return 0;
}