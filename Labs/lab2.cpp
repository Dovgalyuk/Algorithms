#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>

using namespace std;

bool checkTags(const string& html);

int main() {
	string inputNameFile, outputNameFile, html, line;

	cout << "inputFile: ", cin >> inputNameFile;
	cout << "outputFile: ", cin >> outputNameFile;
	
	ifstream inputFile(inputNameFile);
	if (!inputFile.is_open()) {
		cout << "n/a" << endl;
	}
	else {
		while (getline(inputFile, line)) {
			html += line;
		}
		inputFile.close();
		ofstream outputFile(outputNameFile);
		outputFile << (checkTags(html) ? "YES" : "NO");
		outputFile.close();
	}

	return 0;
}

bool checkTags(const string& html) {
	Stack* stack = stack_create();
	for (size_t i = 0; i < html.size(); i++) {
		if (html[i] == '<') {
			if (html[i + 1] != '/') {
				i++;
				for (; html[i] != '>'; i++) {
					stack_push(stack, tolower(html[i]));
				}
			}
			else {
				i += 2;
				int j = 0;
				for (; html[i] != '>'; i++) {
					j++;
				}
				i -= j;
				j--;
				for (; j != -1; j--) {
					if (tolower(html[i + j]) == stack_get(stack)) {
						stack_pop(stack);
					}
					else {
						stack_delete(stack);
						return false;
					}
				}
			}
		}
	}
	if (stack_empty(stack))
	{
		stack_delete(stack);
		return true;
	}
	else
	{
		stack_delete(stack);
		return false;
	}
}