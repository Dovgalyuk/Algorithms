#include <fstream>
#include <iostream>
#include <unordered_map>
#include "list.h"
#include "stack.h"


using namespace std;


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
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error reading the file" << endl;
        return;
    }
    
    string s;

    file >> s;

    file.close();

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

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Help: "<<argv[0]<<"\n -list <5> -- test list\n"
                                   " -stack <fileName> -- test stack"<<endl;
        
        return 1;
    }
    //TestStack("D:\\Программирование\\с++\\ALab\\Lab2CPP\\test.txt");
    
    string mode = argv[1];

    if (mode == "-list")
    {
        TestList(atoi(argv[2]));
    }
    else if (mode == "-stack")
    {
        TestStack(argv[2]);
    }
    else
    {
        return 1;
    }

    return 0;
}