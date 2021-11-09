#include <iostream>
#include "stack.h"
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace std;

const string input_name = "input.txt";
const string output_name = "output.txt";

int main() {
    Stack* stack = stack_create();

    ifstream input;
    input.open(input_name);
    if (!input.is_open()) {
        cout << input_name << " ne otkrilsya (((\n";
        system("pause");
        exit(0);
    }

    ofstream output;
    output.open(output_name);
    if (!output.is_open()) {
        cout << output_name << " ne otkrilsya (((\n";
        system("pause");
        exit(0);
    }

    string tag;
	bool result = true;

	while (input >> tag){
		transform(tag.begin(), tag.end(), tag.begin(), tolower);

		if (tag[1] == '/') {
			tag.erase(1, 1);
			if (!stack_empty(stack)) {
				if(stack_get(stack) == tag){ 
                    result = true;
                    stack_pop(stack);
                } 
                else {
                    result = false;
                    break;
                }
			}
			else {
				result = false;
				break;
			}
		}
		else {
			stack_push(stack, tag);
		}
	}

	if (!stack_empty(stack)) 
		result = false;

    result ? output << "YES" : output << "NO";

    input.close();
    output.close();
    stack_delete(stack);
    return 0;
}