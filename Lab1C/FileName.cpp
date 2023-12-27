#include <iostream>
#include <ctime>
#include "stack.h"
#include "vector.h"
#include "string"
using namespace std;


string checkbox(const string& sequence) {
    Stack* stack = stack_create();
    for (char c : sequence) {
        if (c == '(' || c == '[' || c == '{' || c == '\"' || c == '\'') {
            stack_push(stack, c);
        }
        else if (c == ')') {
            if (stack_empty(stack) || stack_get(stack) != '(') {
                return "NO";
            }
            stack_pop(stack);
        }
        else if (c == ']') {
            if (stack_empty(stack) || stack_get(stack) != '[') {
                return "NO";
            }
            stack_pop(stack);
        }
        else if (c == '}') {
            if (stack_empty(stack) || stack_get(stack) != '{') {
                return "NO";
            }
            stack_pop(stack);
        }
        else if (c == '\"' || c == '\'') 
        {
            if (stack_empty(stack) || stack_get(stack) != c)
            {

                stack_push(stack, c); // ≈сли кавычка открывающа€с€, то кладем ее в стек
            }
            else {
                stack_pop(stack); // ≈сли кавычка закрывающа€с€, то убираем ее из стека

                stack_push(stack, c);
            }
        }
    }
    string result = (stack_empty(stack)) ? "YES" : "NO";
    stack_delete(stack);
    return result;
}
int main()
{
	setlocale(LC_ALL, "Russian");

    string sequence = "{"; //vvod

	string result = checkbox(sequence);
	cout << result << endl;

	return 0;
}