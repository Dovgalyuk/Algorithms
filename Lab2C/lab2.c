#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "vector.h"

int priority(long long op)
{
    if (op < 0)
        op *= -1;
    if (op == (long long)'+' || op == (long long)'-')
        return 1;
    else if (op == (long long)'*')
        return 2;
    else
        return 0;
}

void parser(FILE* input, Vector* rpn_buf)
{
    Stack *stack_ops = stack_create(NULL, NULL);
    int c;
    size_t out_i = 0;
    long long buf_num = 0;
    while ((c = fgetc(input)) != EOF)
    {
        printf("%c", c);
        if (isdigit(c))
        {
            buf_num *= 10;
            buf_num += ((long long)c - (long long)'0');  
        }
        if (!isdigit(c) && buf_num) {
            vector_set(rpn_buf, out_i++, (Data)(uintptr_t)buf_num);
            buf_num = 0;
        }
        if (c == '(')
        {
            stack_push(stack_ops, (Data)(uintptr_t)((long long)c * -1));
        }
        if (c == ')')
        {
            if (stack_empty(stack_ops))
                {   
                    printf("ERROR: received ')' before '(' \n");
                    return;
                }
            while (((long long)(uintptr_t)stack_get(stack_ops)) != ((long long)('(') * -1))
            {
                vector_set(rpn_buf, out_i++, stack_get(stack_ops));
                stack_pop(stack_ops);
            }
            stack_pop(stack_ops);
        }
        if (c == '+' || c == '-' || c == '*')
        {
            if (!stack_empty(stack_ops))
            {
                if (priority((long long)(uintptr_t)stack_get(stack_ops)) >= priority((long long)c))
                {
                    vector_set(rpn_buf, out_i++, stack_get(stack_ops));
                    stack_pop(stack_ops);
                }
                else
                    stack_push(stack_ops, (Data)(uintptr_t)((long long)c * -1));
            }
            else
                stack_push(stack_ops, (Data)(uintptr_t)((long long)c * -1));
        }
        if (c == '\n') {
            break;
        }
    }
    if (buf_num) {
            vector_set(rpn_buf, out_i++, (Data)(uintptr_t)buf_num);
            buf_num = 0;
            printf("\n");
        }
    while (!stack_empty(stack_ops))
    {
        vector_set(rpn_buf, out_i++, stack_get(stack_ops));
        stack_pop(stack_ops);
    }
    stack_delete(stack_ops);
}

void asm_commands(Vector* rpn_string)
{
    for (size_t i = 0; i < vector_size(rpn_string); i++)
    {
        if ((long long)(uintptr_t)vector_get(rpn_string, i) > 0)
        {
            printf("PUSH %lld \n", (long long)(uintptr_t)vector_get(rpn_string, i));
        }
        else if ((long long)(uintptr_t)vector_get(rpn_string, i) == ((long long)'+' * -1))
        {
            printf("POP A \n");
            printf("POP B \n");
            printf("ADD A, B \n");
            printf("PUSH A \n");
        }
        else if ((long long)(uintptr_t)vector_get(rpn_string, i) == ((long long)'-' * -1))
        {
            printf("POP A \n");
            printf("POP B \n");
            printf("SUB A, B \n");
            printf("PUSH A \n");
        }
        else if ((long long)(uintptr_t)vector_get(rpn_string, i) == ((long long)'*' * -1))
        {
            printf("POP A \n");
            printf("POP B \n");
            printf("MUL A, B \n");
            printf("PUSH A \n");
        }
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    FILE *input = fopen(argv[1], "r");
    Vector* rpn_string = vector_create(NULL, NULL);

    parser(input, rpn_string);
    asm_commands(rpn_string);

    vector_resize(rpn_string, 0);

    parser(input, rpn_string);
    fclose(input);
    asm_commands(rpn_string);
    
    vector_delete(rpn_string);
}
