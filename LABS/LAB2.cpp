#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"

using namespace std;

bool check(Stack* stack, string stroka)
{
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    for (char i : stroka) {
        
        switch (i) {
        case '(': stack_push(stack, '('); count1++;  break;
        case '[': stack_push(stack, '['); count2++; break;
        case '{': stack_push(stack, '{'); count3++;  break;
        case '<': stack_push(stack, '<'); count4++;  break;
        case ')':
            count1--;
            if (stack_empty(stack) || stack_get(stack) != '(' || count1 ==1   )

        {
            return false;
        }
            
                stack_pop(stack); 

                break;
        case ']':
            count2--;
            if (stack_empty(stack) || stack_get(stack) != '[' || count2 == 1)

        {
            return false;
        }
                stack_pop(stack);

                break;
        case '}':
            count3--;
            if (stack_empty(stack) || stack_get(stack) != '{' || count3 == 1)

        {
            return false;
        }
                stack_pop(stack);

                break;
        case '>':
            count4--;

            if (stack_empty(stack) || stack_get(stack) != '<' || count4 == 1)
        
            {
                return false;
            }
            stack_pop(stack);
            
            break;
        default: break;
        }
       
        
        
       
   }
    if (stack_empty(stack))
        return true;
    else
        return false;
    
   
    
    
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
