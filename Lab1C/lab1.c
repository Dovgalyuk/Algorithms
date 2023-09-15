#include <stdio.h>
#include "array.h"

void task1(Array* arr)
{
	int firstMax = -1, lastMax = -1;
	int max = -1;
	int length = array_size(arr);
	for (int i = 0;i < length;i++) {
		int x = array_get(arr, i);
		if (x == max) {
			lastMax = i;
		}
		else if (x > max) {
			max = x;
			firstMax = i;
			lastMax = -1;
		}
	}
	if (lastMax != -1) {
		printf("\nindex of first MaxSpeed Auto = %d , index of LastMax = %d\n", firstMax, lastMax);
	}
	else printf("\nindex of MaxSpeed Auto = %d \n", firstMax);
}

void task2(Array* arr)
{
	int length = array_size(arr);
	if (length >= 5) {
		int sum = 0;
		int i = 0, lastinfive;
		int maxfive;
		while (i < length) {
			if (i >= 5) {
				lastinfive = array_get(arr, i - 5);
				int next = array_get(arr, i);
				sum += next;
				sum -= lastinfive;
				if (sum > maxfive) maxfive = sum;
			}
			else {
				int next = array_get(arr, i);
				sum += next;
			}
			if (i == 4) {
				maxfive = sum;
			}
			i++;
		}
		printf("Max five of numbers %d\n", maxfive);
	}
	else
		printf("Count of numbers lower 5\n");
}

int main()
{
	Array* arr = NULL;
	int size = 0;
	printf("\nInput size of array\n");
	scanf_s("%d", &size);
	arr = array_create(size, NULL);
	for (int i = 0;i < size;i++) {
		array_set(arr, i, rand() % 50 + 50);
	}
	task1(arr);
	array_delete(arr);
	printf("\nInput size of array\n");
	scanf_s("%d", &size);
	arr = array_create(size, NULL);
	for (int i = 0;i < size;i++) {
		array_set(arr, i, rand() % 10);
	}
	task2(arr);
	array_delete(arr);
}