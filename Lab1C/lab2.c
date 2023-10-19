#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "string.h"

void ErrorMessage(int err) {
	switch (err) {
	case 1:
		printf("\nZERO");
		break;
	case 2:
		printf("\nUNDERFLOW");
		break;
	case 3:
		printf("\nOVERFLOW");
		break;
	default:
		break;
	}
}

int main()
{
	char string[100];
	char op[] = "+-*/";
	char* number;
	int error = 0, x = 0, y = 0, answer = 0;
	Stack* stack = NULL;
	stack = stack_create(NULL);
	fgets(string, sizeof(string), stdin);
	string[strlen(string) - 1] = '\0';

	number = strtok(string, " ");

	while (number && error == 0) {
		if (strstr(op, number) == NULL) {
			int* c = (int*)malloc(sizeof(int));
			*c = atoi(number);

			stack_push(stack, c);
		}
		else {

			if (stack_get(stack) != NULL) {
				x = *((int*)stack_get(stack));
				stack_pop(stack);
			}
			else error = 2;


			if (stack_get(stack) != NULL) {
				y = *((int*)stack_get(stack));
				stack_pop(stack);
			}
			else error = 2;
			if (error == 0) {
				int* c = (int*)malloc(sizeof(int));

				if (strcmp(number, "+") == 0)
					*c = y + x;
				else if (strcmp(number, "-") == 0)
					*c = y - x;
				else if (strcmp(number, "*") == 0)
					*c = y * x;
				else if (strcmp(number, "/") == 0)
				{
					if (x == 0) error = 1;
					else
						*c = y / x;
				}
				stack_push(stack, c);
			}
		}
		number = strtok(NULL, " ");
	}
	if (!error) {
		answer = *((int*)stack_get(stack));
		stack_pop(stack);
		if (!stack_empty(stack)) error = 3;
	}
	if (error == 0)
		printf("\nOtvet: %d\n", answer);
	else
		ErrorMessage(error);

	stack_delete(stack);
}
