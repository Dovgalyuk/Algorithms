#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include "stack.h"
#include "vector.h"

int getWordValue(const std::string& word) {
    std::map<char,int> letter_scores = {
        {'A',1},{'B',3},{'C',3},{'D',2},{'E',1},{'F',4},{'G',2},
        {'H',4},{'I',1},{'J',8},{'K',5},{'L',1},{'M',3},{'N',1},
        {'O',1},{'P',3},{'Q',10},{'R',1},{'S',1},{'T',1},{'U',1},
        {'V',4},{'W',4},{'X',8},{'Y',4},{'Z',10}
    };

    int sum = 0;
    for (char c : word) {
        if (isalpha(c)) {
            sum += letter_scores[(char)toupper(c)];
        }
    }

    return sum;
}

int main(int argc, char** argv) {
    if (argc <= 2) {
        std::cerr << "Не хватает аргументов командной строки!" << std::endl;
        return 1;
    }

    std::ifstream scriptFile(argv[1]);
    std::ifstream inputFile(argv[2]);

    Stack<int> stack;

    int ch;

    Vector<std::string> scriptWords;
    int counter = 0;

    std::string word;
    while (scriptFile >> word) {
        if ((int)scriptWords.size() <= counter + 1) {
            scriptWords.resize(counter + 1);
        }
        scriptWords.set(counter, word);
        counter++;
    }

    for (size_t i = 0; i < scriptWords.size(); i++) {
        int value = getWordValue(scriptWords.get(i));
        switch (value) {
            case 5:
                if (i + 1 < scriptWords.size()) {
                    stack.push(getWordValue(scriptWords.get(++i)));
                }
                break;
            case 6:
                if (!stack.empty()) {
                    stack.pop();
                }
                break;
            case 7:
                if (!stack.empty()) {
                    int a = stack.get(); 
                    stack.pop();
                    int b = stack.get(); 
                    stack.pop();
                    stack.push(a + b);
                }
                break;
            case 8:
                ch = inputFile.get();
                stack.push(ch);
                break;
            case 9:
                if (!stack.empty()) {
                    char c = (char)stack.get();
                    stack.pop();
                    std::cout << c;
                }
                break;
            case 10:
                if (!stack.empty()) {
                    int a = stack.get(); 
                    stack.pop();
                    int b = stack.get(); 
                    stack.pop();
                    stack.push(b - a);
                }
                break;
            case 11:
                if (!stack.empty()) {
                    int a = stack.get(); 
                    stack.pop();
                    int b = stack.get(); 
                    stack.pop();
                    stack.push(a);
                    stack.push(b);
                }
                break;
            case 12:
                if (!stack.empty()) {
                    stack.push(stack.get());
                }
                break;
            case 13:
                if (!stack.empty()) {
                    int n = stack.get(); 
                    stack.pop();
                    if (n == 0) {
                        if (i + 1 < scriptWords.size()) {
                            int skip = getWordValue(scriptWords.get(i + 1));
                            i += skip + 1;
                            if (i >= scriptWords.size()) {
                                i = scriptWords.size() - 1;
                            }
                        }
                    }
                }
                break;
            case 14:
                if (!stack.empty()) {
                    int n = stack.get(); 
                    stack.pop();
                    if (n != 0) {
                        if (i + 1 < scriptWords.size()) {
                            int skip = getWordValue(scriptWords.get(i + 1));
                            i += skip + 1;
                            if (i >= scriptWords.size()) {
                                i = scriptWords.size() - 1;
                            }
                        }
                    }
                }
                break;
            case 15:
                if (!stack.empty()) {
                    int n = stack.get(); 
                    stack.pop();
                    if (n == 0) {
                        if (i + 1 < scriptWords.size()) {
                            int skip = getWordValue(scriptWords.get(i + 1));
                            if (skip > (int)i) {
                                i = 0;
                            } else {
                                i -= skip;
                            }
                            i--;
                        }
                    }
                }
                break;
            case 16:
                if (!stack.empty()) {
                    int n = stack.get(); 
                    stack.pop();
                    if (n != 0) {
                        if (i + 1 < scriptWords.size()) {
                            int skip = getWordValue(scriptWords.get(i + 1));
                            if (skip > (int)i) {
                                i = 0;
                            } else {
                                i -= skip;
                            }
                            i--;
                        }
                    }
                }
                break;
            case 17:
                return 0;
            default:
                break;
        }
    }

    return 0;
}