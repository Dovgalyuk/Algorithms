#include <iostream>
#include<fstream>
#include<sstream>
#include <string>
#include "stack.h"

using namespace std;
 int main() {
	 Stack* stack = stack_create();
	 int local_var[4] = { 0, 0, 0, 0 };

	 ifstream file("input.txt"); //C:\Users\user\Documents\Unreal Projects\GitSnake\Algorithms\out\build\x64-Debug\LibraryCPP - расположение файла
	 if (!file.is_open()) {
		 std::cout<<"Failed open!"<<endl;
		 return 0;
	 }

	 string line;
	 while (getline(file, line)) {
		 istringstream iss(line);
		 string function;
		 iss >> function;
		 if(function == "bipush") {
			 Data value;
			 iss >> value;
			 stack_push(stack, value);
		 }
	 }
	 file.close();

	 std::cout << "stack:" <<endl;
	 while (!stack_empty(stack)) {
		 std::cout << stack_get(stack) << endl;
		 stack_pop(stack);
	 }

	 std::cout << "vars:" <<endl;
	 for (int i = 0; i < 4; ++i) {
		 std::cout << local_var[i] <<endl;
	 }

	 stack_delete(stack);
	 return 0;
 }
