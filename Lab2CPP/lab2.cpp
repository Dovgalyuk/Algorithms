#include <fstream>
#include <iostream>
#include <unordered_map>
#include "list.h"
#include "stack.h"
#include "array.h"


using namespace std;

string ReadStringFromFile(const string& fileName){
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error reading the file" << endl;
        return "";
    }
    
    string s;

    file >> s;

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
    
    size_t n;
    file >> n;
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

void TestList(int element_count)
{
    int start_value = 1;

    List list =  List();
        
        // Заполнение списка
    for (int i = 0; i < element_count; i++) {
        list.insert(start_value + i);
    }
    
    List::Item* next = list.first();

    while (next != nullptr)
    {
        cout << next->data() <<" ";
        next = next->next();
    }
    cout << endl;
}

void TestStack(const string& fileName)
{
    string s = ReadStringFromFile(fileName);

    Stack st; 
    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    

    bool isValid = true;

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') { //скобка открывающая
            st.push(c); //добавляем в стек
        } else if (c == ')' || c == ']' || c == '}') { //скобка закрывающая
            if (st.empty() || st.get() != pairs[c]) { //проверяем вершину стека
                isValid = false; //не совпадает
                break;
            }
            st.pop(); //удаляем вершину стека
        }
    }

    if (!st.empty()) { //проверяем что стек пуст
        isValid = false;
    } 
  
    //выводим ответ
    if (isValid){
        cout << "YES";
    } else{
        cout << "NO";
    }
}

void AnnoyingScriptInterpreter(const string& fileNameScript, const string& fileNameInput)
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
            if (script[i] == '/')
            { 
                tempValue = "";
                i++;
                break;
            }

            if(!stack.empty()) tempValue = (char)stack.get();
            break;
        }
        case '<':
        {
            if(!stack.empty())
            {
                //char top = stack.get();
                //stack.pop();
                Stack temp;
                while (!stack.empty())
                {
                    temp.push(stack.get());
                    stack.pop();
                }
               // stack.push(top);
                while (!temp.empty())
                {
                    stack.push(temp.get());
                    temp.pop();
                }
                
            }
            break;
        }
        case '>':
        {
            i++;
            if(script[i] == '{')
            {
                i++;
                while (i < script.length() && script[i] != '}')
                {
                    cout << script[i];
                    i++;
                }
            }
            else if(script[i] == '~')
            {
                cout << tempValue;
            }
            else
            {
                cout << script[i];
            }
            i++;
            break;
        }
        case '_':
        {
            stack.push(input.get(inputIndex));
            inputIndex++;
            break;
        }
        default:
            break;
        }
    }

    while (!stack.empty())
    {
        cout << (char)stack.get()<<endl;
        stack.pop();
    }
}

int main(int argc, char* argv[])//
{
    if (argc < 2)
    {
        cout << "Help: "<<argv[0]<<"\n -list <5> -- test list\n"
                                   " -stack <fileName> -- test stack\n"
                                   " -inter <scriptFile> <inputFile>"<<endl;
        
        return 1;
    }
    
    //AnnoyingScriptInterpreter("D:\\Программирование\\с++\\ALab\\Lab2CPP\\Tests\\testscript1.txt", "D:\\Программирование\\с++\\ALab\\Lab2CPP\\Tests\\emptyInput.txt");

    string mode = argv[1];

    if (mode == "-list")
    {
        TestList(atoi(argv[2]));
    }
    else if (mode == "-stack")
    {
        TestStack(argv[2]);
    }
    else if (mode == "-inter")
    {
        AnnoyingScriptInterpreter(argv[2], argv[3]);
    }
    else
    {
        return 1;
    }

    return 0;
}