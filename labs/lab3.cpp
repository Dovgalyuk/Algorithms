#include <iostream>
#include "vector.h"
#include "queue.h"
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace std;

const string input_name = "input.txt";
const string output_name = "output.txt";

int main() {
    ifstream input;
    input.open(input_name);
    if (!input.is_open()) {
        cout << input_name << " ne otkrilsya (((\n";
        system("pause");
        exit(0);
    }

    ofstream output;
    output.open(output_name);
    if (!output.is_open()) {
        cout << output_name << " ne otkrilsya (((\n";
        system("pause");
        exit(0);
    }

    Queue* queue = queue_create();

    char ch;
    bool flag = true;
    while (input.get(ch)){
        if (ch == '\n') { flag = false; continue; }
        if (flag)
            queue_insert(queue, ch);
        else {
            while (ch != queue_get(queue)) {
                if (queue_empty(queue)) {
                    output << "NO";
                    input.close();
                    output.close();
                    return 0;
                }
                queue_remove(queue);
            }
            queue_remove(queue);
        }
    }
    if (!queue_empty(queue)) {
        output << "YES";
    }
    queue_delete(queue);
    input.close();
    output.close();
    return 0;
}