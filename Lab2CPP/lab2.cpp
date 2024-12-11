#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "stack.h"
using namespace std;

string lab_2(const string &inputstr){
    Stack * stack = stack_create();
    for (int i=0; i<(int)(inputstr.size());i++){
        if (inputstr[i] == '#'){
            stack_pop(stack);
        }
        else {
            stack_push(stack, inputstr[i]);
        }
    }
    stringstream ss;
    while (!stack_empty(stack)){
        ss << (char)(stack_get(stack));
        stack_pop(stack);
    }
    string temp = ss.str();
    reverse(temp.begin(), temp.end());
    stack_delete(stack);
    return temp;
}

int main()
{
    ifstream file;
    file.open("input.txt");
    string arr[4];
    file >> arr[0] >> arr[1] >> arr[2] >> arr[3];
    if (lab_2(arr[0]) != arr[1])
    {
        std::cout << "Invalid lab_2 test1 execution\n";
        return 1;
    } 
    if (lab_2(arr[2]) != arr[3])
    {
        std::cout << "Invalid lab_2 test2 execution\n";
        return 1;
    }
    return 0;
}



