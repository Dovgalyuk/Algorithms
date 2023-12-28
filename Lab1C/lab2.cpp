#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <string>
#include "stack.h"
#include <fstream>

using namespace std;


int main()
{
    setlocale(LC_ALL, "ru");

    string filename = "C:\\Users\\PC\\Documents\\GitHub\\Algorithms\\Lab1C\\imput.txt";

	ifstream inputFile(filename);
    if (!inputFile) {
        printf("Не удалось открыть файл\n");
        return 0;
    }

    Stack* stack = stack_create(); 

	size_t size = 0;
    char ch;
	while (inputFile.get(ch)){
		while (ch != '*'){
			stack_push(stack, ch);
			size += 1;
		}
		if (!stack_empty(stack) && ((stack_get(stack) == ch) )) {
			stack_pop(stack);
			size -= 1;
		}
	}

	if (stack_empty(stack) && size == 0) { 
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}

	stack_delete(stack);


    return 0;
}
