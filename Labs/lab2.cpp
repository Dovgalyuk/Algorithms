#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>

using namespace std;

bool checkTags(ifstream& inputFile);

int main() {
	string inputNameFile, outputNameFile, html, line;

	/*cout << "inputFile: ", cin >> inputNameFile;
	cout << "outputFile: ", cin >> outputNameFile;*/
	inputNameFile = "input.txt";
	outputNameFile = "output.txt";
	
	ifstream inputFile(inputNameFile);
	if (!inputFile.is_open()) {
		cout << "n/a" << endl;
	}
	else {
		ofstream outputFile(outputNameFile);
		outputFile << (checkTags(inputFile) ? "YES" : "NO");
		inputFile.close();
		outputFile.close();
	}

	return 0;
}

bool checkTags(ifstream& inputFile) {
	Stack* stack = stack_create();
	string html;
	size_t i = 0;
	while (getline(inputFile, html)) {
		for (; i < html.size(); i++) {
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
		i=0;
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