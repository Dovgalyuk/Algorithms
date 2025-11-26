#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <unordered_map>
#include "list.h"
#include "stack.h"
#include "array.h"


using namespace std;

string ReadStringFromFile(const string& fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error reading the file" << endl;
        return "";
    }
    
    string s;
    getline(file, s);

    file.close();

    return s;
}

Array ReadArrayFromFile(const string& fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error reading the file" << endl;
        return Array(0);
    }
    
    size_t n = 0;
    file >> n;
    if (n == 0)
    {
        return Array(0);
    }
    Array arr(n);
    for (size_t i = 0; i < n; i++)
    {
        Data val;
        file >> val;
        arr.set(i, val);
    }

    file.close();
    return arr;
}

string ReadNumber(size_t& scriptIndex, string& script)
{
    string number;
    while(scriptIndex < script.length() && isdigit(script[scriptIndex]))
    {
        number += script[scriptIndex];
        scriptIndex++;
    }
    scriptIndex--;
    return number;
}

void AnnoyingScriptInterpreter(const string& fileNameScript, const string& fileNameInput) //AS Interpreter
{
    
    string script = ReadStringFromFile(fileNameScript);
    Array input = ReadArrayFromFile(fileNameInput);
    Stack stack;

    size_t inputIndex = 0;
    size_t scriptIndex = 0;

    
    string tempValue;
    string output;

    unordered_map<int, std::string> variables;


    //генератор случайных чисел
    random_device rd;
    mt19937 gen(rd());


    bool halted = false;
    
    
    while (scriptIndex<script.length() && !halted)
    {
        char command = script[scriptIndex];

        switch (command)
        {
        case '+': //Adds a character or string to the top of the stack
        {
            scriptIndex++;

            if(scriptIndex >= script.length()) break;
            stack.push(string(1,script[scriptIndex]));
            break;
        }
        case '-': //Removes the bottom of the stack
        {
            if (!stack.empty())
            {
                stack.pop();
            }
            break;
        }
        case '~': //Returns the bottom of the stack
        {
            scriptIndex++;
            if (script[scriptIndex] == '\\')
            { 
                tempValue = "";
                break;
            }
            else
            {
                scriptIndex--;
            }
            if(!stack.empty())
            {
                tempValue = stack.get();
            } 
            break;
        }
        case '<': //reverses the stack
        {
            if(!stack.empty())
            {
                Stack temp = Stack();
                while (!stack.empty())
                {
                    temp.push(stack.get());
                    stack.pop();
                }

                stack = temp;
            }
            break;
        }
        case '>': //Outputs text to the console
        {
            scriptIndex++;
            
            if(script[scriptIndex] == '{')
            {
                scriptIndex++;
                while (scriptIndex < script.length() && script[scriptIndex] != '}')
                {
                    output += script[scriptIndex];
                    scriptIndex++;
                }
            }
            else if(script[scriptIndex] == '~')
            {
                 output += tempValue;
            }
            else if(script[scriptIndex] == '@')
            {
                scriptIndex++;
                string index = ReadNumber(scriptIndex, script);
                output += variables[stoi(index)];
            }
            else
            {
                output = script[scriptIndex];
            }
            break;
        }
        case '_': //Asks for the user input. Adds the input to the bottom of the stack
        {
            if (input.size() > 0)
            {
                if (inputIndex < input.size())
                {
                    
                    stack.push(input.get(inputIndex));
                    inputIndex++; 
                }
            }
            break;
        }
        case ':': //Combines the stack into one string
        {
            string str;

            while (!stack.empty())
            {
               str += stack.get();
               stack.pop();
            }

            stack.push(str);

            break;
        }
        case '#': //Halts the program.
        {
            halted = true;
            output = "Program Halted";
            break;
        }
        case '!': //Jumps to a certain index in the code
        {
            scriptIndex++;
            if(scriptIndex < script.length())
            {                
                size_t newIndex = stoi(ReadNumber(scriptIndex, script));

                if(newIndex < script.length())
                {
                    scriptIndex = newIndex;
                }
            }
            break;
        }
        case '?': //Checks if the ~ value is equal to the value, if so, it runs the code in the if
        {
            bool condition;
            size_t offsetCounter = 1;

            scriptIndex++;
            if (scriptIndex < script.length() && script[scriptIndex] == '!') 
            {
                scriptIndex++; // ?!
                condition = (tempValue != ReadNumber(scriptIndex, script));
            } 
            else
            {
                condition = (tempValue == ReadNumber(scriptIndex, script));
            }

            while (scriptIndex < script.length() && script[scriptIndex] != '|') {
                offsetCounter++;
                scriptIndex++;
            }
            
            if (condition)
            {
                scriptIndex = scriptIndex - offsetCounter;
            }
            break;
        }
        case '^': //Clears the output
        {
            output.clear();
            break;
        }
        case ';': //Waits the specified number of seconds
        {
            scriptIndex++;
            string seconds = ReadNumber(scriptIndex,script);
            if (!seconds.empty())
            {
                this_thread::sleep_for(chrono::seconds(stoi(seconds)));
            }
            break;
        }
        case '$': //Gets a random number between 1 and the specified number. Only whole numbers
        {
            scriptIndex++;
            string max = ReadNumber(scriptIndex, script);
            std::uniform_int_distribution<> dis(1, stoi(max));
            int randomNum = dis(gen);
            stack.push(randomNum);
            break;
        }
        case '=': //Creates a variable with the value of ~
        { 
            scriptIndex++;
            if (scriptIndex < script.length() && script[scriptIndex] == '(') //replaces the value of the variable with the specified number to the ~ value
            {
                scriptIndex++;
                string varNum = ReadNumber(scriptIndex, script);
                variables[stoi(varNum)] = tempValue;
            } 
            else if (scriptIndex < script.length() && script[scriptIndex] == ')') //deletes the variable with the specified number
            {
                scriptIndex++;
                string varNum = ReadNumber(scriptIndex, script);
                variables.erase(stoi(varNum));
            } 
            else
            {
                scriptIndex -= 2;
                if (script[scriptIndex] == '~')
                {
                    variables[(int)variables.size()+1] = tempValue;
                    scriptIndex++;
                }
                else 
                {
                    if (!tempValue.empty())
                    {
                        if (scriptIndex < script.length() && script[scriptIndex] == '@')
                        {
                            scriptIndex++;
                            string varNum = ReadNumber(scriptIndex, script);
                            variables[stoi(varNum)] = tempValue;
                        }
                    }
                }
            }
            break;
        }
        case '&': //Does math on the last to items on the bottom of the stack using the specified operator.
        { 
            scriptIndex++;
            if (scriptIndex < script.length()) {
                char op = script[scriptIndex];
                if (stack.Size() >= 2) {
                    std::string b = stack.get(); stack.pop();
                    std::string a = stack.get(); stack.pop();
                    
                    double numA = std::stod(a);
                    double numB = std::stod(b);
                    double result = 0;

                    if (op == '+') result = numA + numB;
                    else if (op == '-') result = numA - numB;
                    else if (op == '*') result = numA * numB;
                    else if (op == '/') result = numB != 0 ? numA / numB : 0;
                    
                    stack.push(std::to_string(result));
                }
            }
            break;
        }
        default:
            break;
        }

        scriptIndex++;
    }

    cout<<"Console output: "<<output<<endl;
    // Вывод состояния стека
    Stack temp;
    while (!stack.empty())
    {
        temp.push(stack.get());
        stack.pop();
    }

    
    while (!temp.empty())
    {
        cout << temp.get() << endl;
        temp.pop();
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Help: "<<argv[0]<<"\n -inter <scriptFile> <inputFile>"<<endl;
        return 1;
    }

    string mode = argv[1];


    //AnnoyingScriptInterpreter("D:\\Программирование\\с++\\ALab\\Lab2CPP\\Tests\\testscript19.txt", "D:\\Программирование\\с++\\ALab\\Lab2CPP\\Tests\\input1.txt");


    if (mode == "-inter")
    {
        AnnoyingScriptInterpreter(argv[2], argv[3]);
    }
    else
    {
        return 1;
    }

    return 0;
}