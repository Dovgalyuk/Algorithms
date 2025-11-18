#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include "stack.h"

int getWordValue(const std::string& word) {
    int letter_scores[] = { 
        1, 3, 3, 2, 1, 4, 2,
        4, 1, 8, 5, 1, 3, 1,
        1, 3, 10, 1, 1, 1, 1,
        4, 4, 8, 4, 10
    };

    int sum = 0;
    for (char c : word) {
        if (isalpha(c)) {
            sum += letter_scores[toupper(c) - 'A'];
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

    Vector<int> scriptWords;
    int counter = 0;

    std::string word;
    while (scriptFile >> word) {
        if ((int)scriptWords.size() <= counter + 1) {
            scriptWords.resize(counter + 1);
        }
        scriptWords.set(counter, getWordValue(word));
        counter++;
    }

    for (size_t i = 0; i < scriptWords.size(); i++) {
        switch (scriptWords.get(i)) {
            case 5:
                if (i + 1 < scriptWords.size()) {
                    stack.push(scriptWords.get(++i));
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
                stack.push(inputFile.get());
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
                            int skip = scriptWords.get(i + 1);
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
                            int skip = scriptWords.get(i + 1);
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
                            int skip = scriptWords.get(i + 1);
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
                            int skip = scriptWords.get(i + 1);
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