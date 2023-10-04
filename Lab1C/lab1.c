#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "array.h"
void task1(Array* arr)
{
	if (arr != NULL) {
		int firstMax = -1, lastMax = -1;
		int max = -1;
		size_t length = array_size(arr);
		for (size_t i = 0;i < length;i++) {
			int x = *((int*)array_get(arr, i));
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
	printf("\nmassive is empty\n");
}

void task2(Array* arr)
{
	size_t length = array_size(arr);
	if (length >= 5) {
		int sum = 0;
		size_t i = 0;
		int maxfive;
		while (i < length) {
			if (i >= 5) {
				sum += *((int*)array_get(arr, i));
				sum -= *((int*)array_get(arr, i - 5));
				if (sum > maxfive) maxfive = sum;
			}
			else {
				sum += *((int*)array_get(arr, i));
			}
			if (i == 4) {
				maxfive = sum;
			}
			i++;
		}
		printf("\nMax five of numbers %d\n", maxfive);
	}
	else
		printf("\nCount of numbers lower 5\n");
}

int main()
{
	Array* arr = NULL;
	size_t size = 0;
	printf("\nInput size of array\n");
	scanf("%zu", &size);
	arr = array_create(size, NULL);
	for (size_t i = 0;i < size;i++) {
		int* a = (int*)malloc(sizeof(int));
		*a = rand() % 50 + 70;
		array_set(arr, i, a);
		printf(" %d ", *a);
	}
	task1(arr);
	array_delete(arr);
	printf("\nInput size of array\n");
	scanf("%zu", &size);
	arr = array_create(size, NULL);
	for (size_t i = 0;i < size;i++) {
		int* a = (int*)malloc(sizeof(int));
		*a = rand() % 10;
		array_set(arr, i, a);
		printf(" %d ", *a);
	}
	task2(arr);
	array_delete(arr);
}
