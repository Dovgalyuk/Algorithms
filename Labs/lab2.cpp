#include <iostream>
#include<fstream>
#include<sstream>
#include <string>
#include "stack.h"

using namespace std;
 int main() {
	 ifstream file("input.txt"); //C:\Users\user\Documents\Unreal Projects\GitSnake\Algorithms\out\build\x64-Debug\Labs - расположение файла
	 if (!file.is_open()) {
		 std::cout<<"Failed open!"<<endl;
		 return 0;
	 }
     Stack* stack = stack_create();
     int local_var[4] = { 0, 0, 0, 0 };
	 string line;
	 while (getline(file, line)) {
		 istringstream iss(line);
		 string function;
		 iss >> function;
         if (function == "bipush") {
             int value;
             if (iss >> value) {
                 stack_push(stack, value);
             }
         }
         else if (function == "pop") {
             stack_pop(stack);
         }
         else if (function == "imul") {
             int a = stack_get(stack);
             stack_pop(stack);
             int b = stack_get(stack);
             stack_pop(stack);
             stack_push(stack, a * b);
         }
         else if (function == "iand") {
             int a = stack_get(stack);
             stack_pop(stack);
             int b = stack_get(stack);
             stack_pop(stack);
             stack_push(stack, a & b);
         }
         else if (function == "ior") {
             int a = stack_get(stack);
             stack_pop(stack);
             int b = stack_get(stack);
             stack_pop(stack);
             stack_push(stack, a | b);
         }
         else if (function == "ixor") {
             int a = stack_get(stack);
             stack_pop(stack);
             int b = stack_get(stack);
             stack_pop(stack);
             stack_push(stack, a ^ b);
         }
         else if (function == "iadd") {
             int a = stack_get(stack);
             stack_pop(stack);
             int b = stack_get(stack);
             stack_pop(stack);
             stack_push(stack, a + b);
         }
         else if (function == "isub") {
             int a = stack_get(stack);
             stack_pop(stack);
             int b = stack_get(stack);
             stack_pop(stack);
             stack_push(stack, b - a);
         }
         else if (function == "iload_0") {
             stack_push(stack, local_var[0]);
         }
         else if (function == "iload_1") {
             stack_push(stack, local_var[1]);
         }
         else if (function == "iload_2") {
             stack_push(stack, local_var[2]);
         }
         else if (function == "iload_3") {
             stack_push(stack, local_var[3]);
         }
         else if (function == "istore_0") {
             local_var[0] = stack_get(stack);
             stack_pop(stack);
         }
         else if (function == "istore_1") {
             local_var[1] = stack_get(stack);
             stack_pop(stack);
         }
         else if (function == "istore_2") {
             local_var[2] = stack_get(stack);
             stack_pop(stack);
         }
         else if (function == "istore_3") {
             local_var[3] = stack_get(stack);
             stack_pop(stack);
         }
         else if (function == "swap") {
             int a = stack_get(stack);
             stack_pop(stack);
             int b = stack_get(stack);
             stack_pop(stack);
             stack_push(stack, a);
             stack_push(stack, b);
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
