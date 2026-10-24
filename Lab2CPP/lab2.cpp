#include <stdio.h>
#include "stack.h"

int main(int argc, char** argv) {
    FILE* input = fopen(argv[1], "r");

    Stack* stack = stack_create();
    int ok = 1;
    int c;

    while ((c = fgetc(input)) != EOF) 
    {
        if (c == '(' || c == '[' || c == '{') 
            stack_push(stack, c);

        else if (c == ')' || c == ']' || c == '}') 
        {
            if (stack_empty(stack)) { ok = 0; break; }

            int top = stack_get(stack);
            stack_pop(stack);

            if (c == ')' && top != '(') { ok = 0; break; }
            if (c == ']' && top != '[') { ok = 0; break; }
            if (c == '}' && top != '{') { ok = 0; break; }
        }
    }

    if (!stack_empty(stack)) 
    ok = 0;

    if (ok) 
        printf("YES\n");
    else 
        printf("NO\n");
    
    stack_delete(stack);
    fclose(input);
    return 0;
}