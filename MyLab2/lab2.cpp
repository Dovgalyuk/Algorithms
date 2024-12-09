#include <iostream>
#include <string>
#include <fstream>
#include "list.h"
#include "stack.h"


bool MyChecker(List<std::string> list) {
    Stack<std::string> stack;

    for (auto item = list.first(); item != nullptr; item = item->next())
    {
        std::string tag = item->data();

        // Opening tag
        if (tag.front() == '<' && tag[1] != '/')
        {
            stack.push(tag); 
        }
        // Closing tag
        else if (tag.front() == '<' && tag[1] == '/')
        {
            if (stack.empty())
            {
                return false;
            }

            std::string topTag = stack.get();
            stack.pop();

            // Converting opening tag to closing
            std::string expectedClosingTag = "</" + topTag.substr(1);

            if (expectedClosingTag != tag)
            {
                return false; 
            }
        }
    }

    return stack.empty();
}


int main(int argc, char **argv) {
    
    List<std::string> list;


    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file: " << argv[1] << "\n";
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file: " << argv[2] << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(input, line))
    {
        //Since the example is case insensitive
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] != '<' && line[i] != '/' && line[i] != '>') {
                line[i] = tolower(line[i]);
            }
        }
        list.insert_back(line);
    }

    input.close();

    bool check = MyChecker(list);
    if(check) {
        output << "YES\n";
    } else {
        output << "NO\n";
    }


    return 0;
}