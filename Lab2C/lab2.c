#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "vector.h"

char filler = ' ';

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*')
        return 2;
    else
        return 0;
}

void parser(Stack* stack_ops, FILE* input, Vector* rpn_buf, Data filler)
{
    Vector* buffer = vector_create(NULL, filler);
    int c;
    while ((c = fgetc(input)) != EOF)
    {
        if (c == '\n')
            break;
        char *ptr = malloc(sizeof(char));
        *ptr = (char) c;
        vector_set(buffer, vector_size(buffer), ptr);
    } 
    for (size_t i = 0; i < vector_size(buffer); i++)
    {
        printf("%c",*(char*)vector_get(buffer, i));
    }
    printf("\n");
    size_t out_i = 0;
    for (size_t i = 0; i < vector_size(buffer); i++)
    {
        if (isdigit(*(char*)vector_get(buffer, i)))
        {
            while (isdigit(*(char*)vector_get(buffer, i)))
            {
                vector_set(rpn_buf, out_i++, vector_get(buffer, i));
                i++;
            }   
            vector_set(rpn_buf, out_i++, filler);
            i -= 1;
        }
        else if (*(char*)vector_get(buffer, i) == '(')
        {
            stack_push(stack_ops, vector_get(buffer, i));
        }
        else if (*(char*)vector_get(buffer, i) == ')')
        {
            free(vector_get(buffer, i));
            if (stack_empty(stack_ops))
                {   
                    printf("ERROR: except ')' before '(' \n");
                    break;
                }
            while (((char*)stack_get(stack_ops))[0] != '(')
            {
                vector_set(rpn_buf, out_i++, stack_get(stack_ops));
                vector_set(rpn_buf, out_i++, filler);
                stack_pop(stack_ops);
            }
            free(stack_get(stack_ops));
            stack_pop(stack_ops);
        }
        else if (*(char*)vector_get(buffer, i) == '+' || *(char*)vector_get(buffer, i) == '-' || *(char*)vector_get(buffer, i) == '*')
        {
            if (!stack_empty(stack_ops))
            {
                if (priority(*(char*)stack_get(stack_ops)) >= priority(*(char*)vector_get(buffer, i)))
                {
                    vector_set(rpn_buf, out_i++, stack_get(stack_ops));
                    vector_set(rpn_buf, out_i++, filler);
                    stack_pop(stack_ops);
                }
                else
                    stack_push(stack_ops, vector_get(buffer, i));
            }
            else
                stack_push(stack_ops, vector_get(buffer, i));
        }
        else
            free(vector_get(buffer, i));
    }
    while (!stack_empty(stack_ops))
    {
        vector_set(rpn_buf, out_i++, stack_get(stack_ops));
        vector_set(rpn_buf, out_i++, filler);
        stack_pop(stack_ops);
    }
    vector_delete(buffer);
    for (size_t i = 0; i < vector_size(rpn_buf); i++)
    {
        printf("%c",*(char*)vector_get(rpn_buf, i));
    }
    printf("\n");
    
}

void asm_commands(Vector* rpn_string)
{
    for (size_t i = 0; i < vector_size(rpn_string); i++)
    {
        if (isdigit(*(char*)vector_get(rpn_string, i)))
        {
            char token[20];
            size_t j = 0;
            while (*(char*)vector_get(rpn_string, i) != filler)
            {
                token[j++] = *(char*)vector_get(rpn_string, i++);
            }
            token[j+1] = '\0';
            printf("PUSH %s \n", token);
        }
        else if (*(char*)vector_get(rpn_string, i) == '+')
        {
            printf("POP A \n");
            printf("POP B \n");
            printf("ADD A, B \n");
            printf("PUSH A \n");
        }
        else if (*(char*)vector_get(rpn_string, i) == '-')
        {
            printf("POP A \n");
            printf("POP B \n");
            printf("SUB A, B \n");
            printf("PUSH A \n");
        }
        else if (*(char*)vector_get(rpn_string, i) == '*')
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
    Stack *stack = stack_create(NULL, &filler);
    FILE *input = fopen(argv[1], "r");
    Vector* rpn_string = vector_create(free, &filler);
    parser(stack, input, rpn_string, &filler);
    asm_commands(rpn_string);
    parser(stack, input, rpn_string, &filler);
    asm_commands(rpn_string);
    vector_delete(rpn_string);
    stack_delete(stack);
    fclose(input);
}
