#include <iostream>
#include <fstream>
#include <string>
#include "list.h"
#include "stack.h"


bool check(const std::string& html) {
    Stack* stack = stack_create();

    for (std::size_t i = 0; i < html.size(); ++i) {

        if (html[i] == '<')
        {
            if (html[i + 1] != '/')
            {
                ++i;
                for (; html[i] != '>'; ++i)
                {
                    stack_push(stack, std::tolower(html[i]));
                }
            }
            else
            {
                i += 2;
                int f = 0;
                for (; html[i] != '>'; ++i)
                {
                    f++;
                }
                i -= f;
                --f;
                for (; f!=-1; --f)
                {
                    if (std::tolower(html[i + f]) == stack_get(stack))
                    {
                        stack_pop(stack);
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }   
    }

    if (stack_empty(stack) == 1) 
    {
        stack_delete(stack);
        return 1;
    }
    else
    {
        stack_delete(stack);
        return 0;
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string html;
    std::string line;

    while (std::getline(inputFile, line)) {
        html += line;  
    }

    bool isCorrect = check(html);

    std::ofstream outputFile("output.txt");

    outputFile << (isCorrect ? "YES" : "NO");

    return 0;
}

