#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"

using namespace std;

bool check(Stack* stack, string stroka)
{
   
    
    for (char i : stroka) {
        switch (i) {
        case '(': stack_push(stack, '(');  break;
        case '[': stack_push(stack, '[');  break;
        case '{': stack_push(stack, '{');  break;
        case '<': stack_push(stack, '<');  break;
        case ')':
            if (stack_empty(stack) || stack_get(stack) != '(')

        {
            return false;
        }
                stack_pop(stack);

                break;
        case ']':
            if (stack_empty(stack) || stack_get(stack) != '[')

        {
            return false;
        }
                stack_pop(stack);

                break;
        case '}':
            if (stack_empty(stack) || stack_get(stack) != '{')

        {
            return false;
        }
                stack_pop(stack);

                break;
        case '>':
            

            if (stack_empty(stack) || stack_get(stack) != '<')
        
            {
                return false;
            }
            stack_pop(stack);
            
            break;
        default: break;
        }
   }
    
   
    
    
}




int main() {


	Stack* stack = stack_create();
	string stroka;
   
	getline(cin, stroka);
    if (check(stack, stroka))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    stack_delete(stack);
    
   
	

}
