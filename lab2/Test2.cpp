#include <iostream>
#include "stack.h"
#include "fstream"
using namespace std;
typedef Stack<int> MyStack;

int main()
{
    ifstream  input("C:\\Algorithms\\lab2\\input.txt");
    if(input.is_open()){
        size_t size;
        input >> size;
        Stack<int> plus;
        for (int i = 0; i < size; ++i) {
            int index;
            char sign;
            input >> index >> sign;
            if (sign == '-') {
                if (!plus.empty()) {
                    std::cout << plus.get() << " " << index << std::endl;
                    plus.pop();
                }
            } else {
                plus.push(index);
            }
        }
    }
    else{
        cout<<"file is not open"<<endl;
    }
    return 0;
}
