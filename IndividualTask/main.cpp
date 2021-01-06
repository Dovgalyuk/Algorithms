#include <iostream>
#include <map>
#include "stack.h"
#include <fstream>

using namespace std;

bool has_only_digits(const string& s){
    return s.find_first_not_of( "0123456789" ) == string::npos;
}

void push_into_stack(Stack<int>& stack, map<char, int>& map, const string& second_part, const size_t& str_num){
    if (second_part.length() == 1 && map.find(second_part[0]) != map.end()){
        stack.push(map[second_part[0]]);
    } else if(has_only_digits(second_part)) {
        char* end;
        stack.push(strtol(second_part.data(), &end, 10));
    } else {
        cout << "Unknown symbol at " << str_num <<" PUSH \"" + second_part + " \"" << endl;
    }
}

void pop_from_stack(Stack<int>& stack, map<char, int>& map, const string& second_part, const size_t& str_num){
    if (second_part.length() == 1 && map.find(second_part[0]) != map.end()){
        map[second_part[0]] = stack.top();
        stack.pop();
    } else {
        cout << "Unknown symbol at " << str_num <<" POP \"" + second_part + " \"" << endl;
    }
}

int main() {

    map<char, int> registers = map<char, int>{
            {'A', 0},
            {'B', 0},
            {'C', 0},
            {'D', 0}
    };
    Stack<int> processor_stack = Stack<int>();

    ifstream input_file_stream("input.txt");
    if (!input_file_stream){
        perror("File \"input.txt\" missing");
    }

    for (std::size_t i = 1; !input_file_stream.eof(); ++i){
        string buffer;
        getline(input_file_stream, buffer);
        int space_index = buffer.find(' ');
        string words[] = {
            buffer.substr(0, space_index),
            buffer.substr(space_index + 1, buffer.length() - 1)
        };

        if (words[0] == "PUSH"){
            push_into_stack(processor_stack, registers, words[1], i);
        } else if (words[0] == "POP"){
            pop_from_stack(processor_stack, registers, words[1], i);
        } else {
            cout << "Unknown symbol at " << i << " " << words[0] << " " <<  words[1] << endl;
        }
    }
    for (auto& s : registers)
    {
        cout << s.first << " = " << s.second << endl;
    }
    input_file_stream.close();
    system("pause");
    return 0;
}
