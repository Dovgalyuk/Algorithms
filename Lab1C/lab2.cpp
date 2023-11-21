#include <iostream>
#include <fstream>
#include <string>
#include "list.h"
#include "stack.h"


bool check(const std::string& html) {
    Stack* stack = stack_create();

    for (std::size_t i = 0; i < html.size(); i+=6) {

        if(html[i + 5] != '>')
        {
            for (size_t g = i+6; g >= i; g--)
            {
                if (g == i + 1) {
                    g--;
                }
                if (std::tolower(html[g]) == stack_get(stack))
                {
                    stack_pop(stack);
                }
                else
                {
                    return 0;
                }
            }
            ++i;

        }
        else
        {
            for (size_t j = i; j < i+6; j++)
            {
                stack_push(stack, std::tolower(html[j]));
            }
        }
    }


    return 1;
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

