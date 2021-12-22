#include <iostream>
#include "stack.h"
#include "fstream"
using namespace std;
typedef Stack<int> MyStack;

int main()
{
    ifstream  input("D:\\text.txt");
    if(input.is_open()){
        size_t size;
        input >> size;
        Stack<int> house;
        for (int i = 0; i < size; ++i) {
            int index;
            char sign;
            input >> index >> sign;
            if (sign == '-') {
                if (!house.empty()) {
                    std::cout << house.get() << " " << index << std::endl;
                    house.pop();
                }
            } else {
                house.push(index);
            }
        }
    }
    else{
        cout<<"file is not open"<<endl;
    }
    return 0;
}