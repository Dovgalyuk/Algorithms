#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

int main() {
    auto* stack = new Stack<string>();

    size_t size;
    int k = 0;
    cin >> size;
    cin.ignore();
    string buf;
    getline(cin,buf);

    while((buf.find("push ") == 0) || (buf.find("pop") == 0)){
        if  ((buf.find("push") == 0) && (buf.find_first_of("0123456789", 5) == 5)) {
            if (k != size) {
                string str = buf.substr (5);
                stack->push(str);
                k += 1; }
            else {
                cout << "BAD PUSH\n";
            }
        }
        if ((buf.find("pop") == 0)) {
            if(!stack->empty()) {
                cout << stack->get() << "\n";
                stack->pop();
                k -= 1; }
            else {
                cout << "BAD POP\n";
            }
        }
        getline(cin,buf);
    }

    buf = "";
    for (k; k > 0; k--){
        buf.insert(0, ("\n" + stack->get()));
        stack->pop();
    }
    cout << "STACK" << buf;
    return 0;
}