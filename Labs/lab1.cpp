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
	int* mass = new int[size];

	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		mass[i] = 1 + rand() % 10000; 

	}

	if (size == 1) {
		soprotivlenie = mass[0];

	}
	else {
		for (int i = 0; i < size; i++) {
			summa += (1. / mass[i]);
		}
		soprotivlenie = (1. / summa);

	}

	cout << "obshee soprotivlenie = " << soprotivlenie;
	delete[] mass;
	return 0;
}