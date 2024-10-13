#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "vector.h"

char filler = ' ';

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

void parser(FILE* input, Vector* rpn_buf, Data filler)
{
    Stack *stack_ops = stack_create(NULL, filler);
    Vector* buffer = vector_create(NULL, filler);
    int c;
    while ((c = fgetc(input)) != EOF)
    {
        if (c == '\n')
            break;
        vector_set(buffer, vector_size(buffer), (Data)(uintptr_t)c);
    } 
    for (size_t i = 0; i < vector_size(buffer); i++)
    {
        printf("%c",(char)(uintptr_t)vector_get(buffer, i));
    }
    printf("\n");
    size_t out_i = 0;
    long long buf_num;
    for (size_t i = 0; i < vector_size(buffer); i++)
    {
        if (isdigit((char)(uintptr_t)vector_get(buffer, i)))
        {
            buf_num = 0;
            while (isdigit((char)(uintptr_t)vector_get(buffer, i)))
            {
                buf_num *= 10;
                buf_num += ((long long)(uintptr_t)vector_get(buffer, i) - (long long)'0');
                i++;
            }   
            vector_set(rpn_buf, out_i++, (Data)(uintptr_t)buf_num);
            i -= 1;
        }
        else if ((char)(uintptr_t)vector_get(buffer, i) == '(')
        {
            stack_push(stack_ops, (Data)(uintptr_t)((long long)(uintptr_t)vector_get(buffer, i) * -1));
        }
        else if ((char)(uintptr_t)vector_get(buffer, i) == ')')
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
        else if ((char)(uintptr_t)vector_get(buffer, i) == '+' || (char)(uintptr_t)vector_get(buffer, i) == '-' || (char)(uintptr_t)vector_get(buffer, i) == '*')
        {
            if (!stack_empty(stack_ops))
            {
                if (priority((long long)(uintptr_t)stack_get(stack_ops)) >= priority((long long)(uintptr_t)vector_get(buffer, i)))
                {
                    vector_set(rpn_buf, out_i++, stack_get(stack_ops));
                    stack_pop(stack_ops);
                }
                else
                    stack_push(stack_ops, (Data)(uintptr_t)((long long)(uintptr_t)vector_get(buffer, i) * -1));
            }
            else
                stack_push(stack_ops, (Data)(uintptr_t)((long long)(uintptr_t)vector_get(buffer, i) * -1));
        }
    }
    while (!stack_empty(stack_ops))
    {
        vector_set(rpn_buf, out_i++, stack_get(stack_ops));
        stack_pop(stack_ops);
    }
    vector_delete(buffer);
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
    Vector* rpn_string = vector_create(NULL, (Data)(uintptr_t)filler);

    parser(input, rpn_string, (Data)(uintptr_t)filler);
    asm_commands(rpn_string);

    vector_resize(rpn_string, 0);

    parser(input, rpn_string, (Data)(uintptr_t)filler);
    fclose(input);
    asm_commands(rpn_string);
    
    vector_delete(rpn_string);
}
