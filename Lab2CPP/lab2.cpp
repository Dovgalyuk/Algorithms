#include "list.h"
#include <iostream>
#include "stack.h"
#include <string>

using namespace std;

    struct Computing{

        public:

            int vichislenie(string InputString, Stack *newstack)
            {

                for (int i = 0; i < InputString.size(); i++)
                {
                    
                    int operand1, operand2, result;
                    string tmpValue;
                    char LastSymb = InputString[InputString.size()-1];

                    if (isdigit(InputString[i]))
                    { 
                        tmpValue += InputString[i];
                    }
                    
                    else if (InputString[i] == ' ' && tmpValue != "")
                    {
                        stack_push(newstack, stoi(tmpValue));
                        tmpValue = "";
                    }
                    
                    else if(InputString[i] == '+' || InputString[i] == '-' || InputString[i] == '*' || InputString[i] == '/' && stack_empty(newstack) != true)
                    {
                        operand2 = stack_get(newstack);
                        stack_pop(newstack);
                        operand1 = stack_get(newstack);
                        stack_pop(newstack);
                        
                        if (InputString[i] == '+')
                        {
                            result = operand1 + operand2;
                            stack_push(newstack, result);
                        }
                        else if (InputString[i] == '-')
                        {
                            result = operand1 - operand2;
                            stack_push(newstack, result);
                        }
                        else if (InputString[i] == '*')
                        {
                            result = operand1 * operand2;
                            stack_push(newstack, result);
                        }
                        else if (InputString[i] == '/')
                        {
                            result = operand1 / operand2;
                            stack_push(newstack, result);
                        }  
                    
                    }
                    
                int answer = stack_get(newstack);
                return answer;
                    
                }

            }

    };


int main()
{
    string InputString;
    Computing *newSolution = new Computing;
    Stack* newstack = stack_create();
    int answer;

    cout << "Enter the expression in the Polish notation with spaces \nTo exit the program, type 'exit'" << endl;
    
    while (true)
    {
        getline(cin, InputString);

        if (InputString == "Exit" || InputString == "exit") break;
        
        else
        {
            answer = newSolution->vichislenie(InputString, newstack);
            cout << "The answer = " << answer << endl;
            cout << endl;
        }

    }

}