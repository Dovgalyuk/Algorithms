
#include "array.h" 
#include <iostream> 
#include <ctime>
#include <random>

//int generateRandomNumber(int min, int max) {
//	return min + rand() % (max - min + 1);
//}

int generateRandomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<int> distribution(min, max); 

	return distribution(gen);
}


// Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами. 
// Найти знакопеременную сумму элементов массива: a[0]-a[1]+a[2]-a[3]+a[4]-a[5]...
int znakomernaySumElements() {
	size_t size; 
	std::cout << "Enter size array: "; 
	std::cin >> size; 

	Array *newArray = array_create(size); 
	int resultSum = 0; 

	for (int i = 0; i != size; i++) {
		int randInt = generateRandomNumber(0, 10); 
		std::cout << randInt << " "; 
		array_set(newArray, i, randInt);
		i % 2 == 0 ? resultSum += randInt : resultSum -= randInt;
	}
	std::cout << std::endl;
	return resultSum; 
}

// Ввести целое число с клавиатуры, создать массив такой размерности и 
// заполнить его случайными числами. Найти в массиве те элементы, значение которых меньше среднего арифметического, 
// взятого от всех элементов массива.

void findElementsLessAverage() {
	size_t size; 
	std::cout << "Enter varieble: ";
	std::cin >> size; 

	Array* newArray = array_create(size);
	double average = 0; 

	for (int i = 0; i != size; i++) {
		int randInt = generateRandomNumber(0, 10); 
		array_set(newArray, i, randInt); 
		std::cout << randInt << " ";
		average += randInt; 
	}

	average = average / size; 
	std::cout << "Average: " << average << std::endl << "Number < Average: ";
	for (int i = 0; i != size; i++) {
		if (array_get(newArray, i) < average) {
			std::cout << array_get(newArray, i) << " ";
		}
	}
}

int main () { 
  
	// Знакомерные числа
	std::cout << "Result: " << znakomernaySumElements() << std::endl; 
	
	// Меньше среднего
	findElementsLessAverage();
}
			