#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void to_lowercase(string& text) {
    for (char& character : text) {
        if (character >= 'A' && character <= 'Z') {
            character += 32;
        }
    }
}

bool validate_tag_sequence(ifstream& file_input, Stack* tag_stack) {
    string tag_line;
    bool is_valid = true;
    
    while (getline(file_input, tag_line)) {
        if (tag_line.substr(0, 2) == "</") {
            string closing_tag = tag_line.substr(2, tag_line.length() - 3);
            
            if (stack_empty(tag_stack)) { 
                is_valid = false;
                break;
            }
            
            string opening_tag = stack_get(tag_stack).substr(1, stack_get(tag_stack).length() - 2); 
            to_lowercase(closing_tag);
            to_lowercase(opening_tag);
            
            if (closing_tag == opening_tag) {
                stack_pop(tag_stack); 
            } else {
                is_valid = false; 
                break;
            }
        } else {
            stack_push(tag_stack, tag_line); 
        }
    }

    if (!stack_empty(tag_stack)) {
        is_valid = false;
    }
    
    return is_valid;
}
