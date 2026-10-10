#include <stdio.h>
#include "stack.h"

int main(int argc, char** argv) {
    FILE* input = fopen(argv[1], "r");
    if (!input) return 1;

    Stack* stack = stack_create();
    bool ok = true;
    int c;

    while ((c = fgetc(input)) != EOF) 
    {
        if (c == '(' || c == '[' || c == '{') 
            stack_push(stack, c);

        else if (c == ')' || c == ']' || c == '}') 
        {
            if (stack_empty(stack)) { ok = false; break; }

            int top = stack_get(stack);
            stack_pop(stack);

            if (c == ')' && top != '(') { ok = false; break; }
            if (c == ']' && top != '[') { ok = false; break; }
            if (c == '}' && top != '{') { ok = false; break; }
        }
    }

    if (!stack_empty(stack)) 
        ok = false;

    if (ok) 
        printf("YES\n");
    else 
        printf("NO\n");
    
    stack_delete(stack);
    fclose(input);
    return 0;
}
