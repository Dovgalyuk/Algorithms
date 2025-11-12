    #include <iostream>
    #include <fstream>
    #include <string>
    #include "vector.h"
    #include "stack.h"

    bool check(const std::string& line) {
        int round_brackets = 0;
        bool double_quotes = false;
        bool single_quotes = false;
        
        for (char c : line) {
            if (c == '(') {
                round_brackets++;
            }
            else if (c == ')') {
                if (round_brackets <= 0) {
                    return false;
                }
                round_brackets--;
            }
            else if (c == '\"') {
                double_quotes = !double_quotes;
            }
            else if (c == '\'') {
                single_quotes = !single_quotes;
            }
        }
        return (round_brackets == 0) && !double_quotes && !single_quotes;
    }

    int main(int argc, char **argv)
    { 
        std::ifstream input(argv[1]);
        std::string line;
        std::getline(input, line);
        if(check(line)){
            std::cout << "YES";
        }
        else
        {
            std::cout << "NO";
        }
        input.close();
        
    }