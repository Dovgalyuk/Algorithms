#include <fstream>
#include <iostream>
#include <string>
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

void AnnoyingScriptInterpreter(const string& fileNameScript, const string& fileNameInput) //AS Interpreter
{
    string script = ReadStringFromFile(fileNameScript);
    Array input = ReadArrayFromFile(fileNameInput);

    size_t inputIndex = 0;
    Stack stack;
    string tempValue;
    for(size_t i = 0; i< script.length(); i++)
    {
        char command = script[i];

        switch (command)
        {
        case '+':
        {
            i++;
            
            if(i >= script.length()) break;
            stack.push(script[i]);
            break;
        }
        case '-':
        {
            if (!stack.empty())
            {
                stack.pop();
            }
            break;
        }
        case '~':
        {
            i++;
            if (script[i] == '\\')
            { 
                tempValue = "";
                break;
            }
            else
            {
                i--;
            }
            
                
            if(!stack.empty())
            {
                char ch = (char)stack.get();
                if (isprint(ch)) {
                    tempValue = ch;
                } else {
                    tempValue = to_string(ch);
                }
            } 
            break;
        }
        case '<':
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
        case '>':
        {
            i++;
            string str;
            if(script[i] == '{')
            {
                i++;
                while (i < script.length() && script[i] != '}')
                {
                    str += script[i];
                    i++;
                }
            }
            else if(script[i] == '~')
            {
                 str = tempValue;
            }
            else
            {
                str = script[i];
            }

            cout<<"Console output: "<<str;
            cout<<endl;
            i++;
            break;
        }
        case '_':
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
        default:
            break;
        }

    }


    // Вывод состояния стека
    Stack temp;
    while (!stack.empty())
    {
        temp.push(stack.get());
        stack.pop();
    }

    
    while (!temp.empty())
    {
        char ch = (char)temp.get();
        if (isprint(ch)) {
            cout << ch << endl;
        } else {
            cout << (int)ch << endl;
        }
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