#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;



int main(){
    ifstream input("C:\\Users\\veniamin\\Documents\\GitHub\\Algorithms\\Lab2CPP\\input.txt");
    if (input.is_open()){
        size_t size;
        input >> size;
        Stack *plus = stack_create();

        for ( int i = 0; i < size; i++){
            int index;
            char sign;
            input >> index >> sign;
            if (sign == '-'){
                if (!stack_empty(plus)){

                    cout << stack_get(plus) << " " << index << endl;

                    stack_pop(plus);
                }
            } else {
                stack_push(plus, index);
            }
        }
    } else {
        cerr << "Unable to open file";
    }
    int n;
    cin >> n;
    return 0;
    
}