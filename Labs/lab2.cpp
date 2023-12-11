#include <iostream>
#include<fstream>
#include <array.h>
#include<stack.cpp>
#include <cstdlib>

using namespace std;
 int main() {
	 Stack* stack = stack_create();
	 int local_var[4] = { 0, 0, 0, 0 };

	 ifstream file("input.txt"); //C:\Users\user\Documents\Unreal Projects\GitSnake\Algorithms\out\build\x64-Debug\LibraryCPP - расположение файла
	 if (!file.is_open()) {
		 cout<<"Failed open!"<<endl;
		 return 1;
	 }

	 string line;
	 while (getline(file, line)) {
		 istringstream iss(line);
		 string function;
		 iss >> function;
		 switch (function) {
			 case bipush:
				 Data value;
				 iss >> value;
				 stack_push(stack &, value);
		 }
	 }
	 file.close();

	 cout << "stack:" <<endl;
	 while (!stack_empty(stack)) {
		 cout << stack_getStack(stack) << endl;
		 stack_pop(stack);
	 }

	 cout << "vars:" <<endl;
	 for (int i = 0; i < 4; ++i) {
		 cout << local_var[i] <<endl;
	 }

	 stack_delete(stack);
	 return 0;
 }
}
