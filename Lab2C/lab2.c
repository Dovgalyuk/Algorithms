#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

char filler = ' ';
int int_filler = 0;

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*')
        return 2;
    else
        return 0;
}

void parser(Stack* stack_ops, FILE* input, char* rpn_buf)
{
    char buffer[20];
    fgets(buffer, 20, input);
    printf("%s \n",buffer);
    size_t out_i = 0;
    for (size_t i = 0; i < strlen(buffer); i++)
    {
        if (isdigit(buffer[i]))
        {
            while (isdigit(buffer[i]))
                rpn_buf[out_i++] = buffer[i++];
            rpn_buf[out_i++] = ' ';
            i -= 1;
        }
        else if (buffer[i] == '(')
        {
            char* data = malloc(sizeof(char));
            *data = buffer[i];
            stack_push(stack_ops, data);
        }
        else if (buffer[i] == ')')
        {
            if (stack_empty(stack_ops))
                {   
                    printf("ERROR: except ')' before '(' \n");
                    break;
                }
            while (((char*)stack_get(stack_ops))[0] != '(')
            {
                rpn_buf[out_i++] = *(char*)stack_get(stack_ops);
                rpn_buf[out_i++] = ' ';
                stack_pop(stack_ops);
            }
            stack_pop(stack_ops);
        }
        else if (buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '*')
        {
            if (!stack_empty(stack_ops))
            {
                if (priority(*(char*)stack_get(stack_ops)) >= priority(buffer[i]))
                {
                    rpn_buf[out_i++] = *(char*)stack_get(stack_ops);
                    rpn_buf[out_i++] = ' ';
                    stack_pop(stack_ops);
                }
                else
                {
                    char* data = malloc(sizeof(char));
                    *data = buffer[i];
                    stack_push(stack_ops, data);
                }
            }
            else
            {
                char* data = malloc(sizeof(char));
                *data = buffer[i];
                stack_push(stack_ops, data);
            }
        }
    }
    while (!stack_empty(stack_ops))
    {
        rpn_buf[out_i++] = *(char*) stack_get(stack_ops);
        rpn_buf[out_i++] = ' ';
        stack_pop(stack_ops);
    }
    rpn_buf[out_i-1] = '\0';
}

void asm_commands(Stack* stack_asm, char* rpn_string)
{
    long a, b;
    char* token = strtok(rpn_string, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            long* data = malloc(sizeof(long));
            *data = strtol(token, NULL, 10);
            stack_push(stack_asm, data);
            printf("PUSH %s \n", token);
        }
        else if (token[0] == '+')
        {
            b = *(long*) stack_get(stack_asm);
            printf("POP B \n");
            stack_pop(stack_asm);
            a = *(long*) stack_get(stack_asm);
            printf("POP A \n");
            stack_pop(stack_asm);
            a += b;
            printf("ADD A, B \n");
            long* data = malloc(sizeof(long));
            *data = a;
            stack_push(stack_asm, data);
            printf("PUSH A \n");
        }
        else if (token[0] == '-')
        {
            b = *(long*)stack_get(stack_asm);
            printf("POP B \n");
            stack_pop(stack_asm);
            a = *(long*)stack_get(stack_asm);
            printf("POP A \n");
            stack_pop(stack_asm);
            a -= b;
            printf("SUB A, B \n");
            long* data = malloc(sizeof(long));
            *data = a;
            stack_push(stack_asm, data);
            printf("PUSH A \n");
        }
        else if (token[0] == '*')
        {
            b = *(long*)stack_get(stack_asm);
            printf("POP B \n");
            stack_pop(stack_asm);
            a = *(long*)stack_get(stack_asm);
            printf("POP A \n");
            stack_pop(stack_asm);
            a *= b;
            printf("MUL A, B \n");
            long* data = malloc(sizeof(long));
            *data = a;
            stack_push(stack_asm, data);
            printf("PUSH A \n");
        }
        token = strtok(NULL, " ");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    Stack *stack = stack_create(free, &filler);
    Stack *stack_asm = stack_create(free, &int_filler);
    FILE *input = fopen(argv[1], "r");
    char rpn_string[20];
    parser(stack, input, rpn_string);
    asm_commands(stack_asm, rpn_string);
    while (!stack_empty(stack_asm))
    {
        stack_pop(stack_asm);
    }
    parser(stack, input, rpn_string);
    asm_commands(stack_asm, rpn_string);

    stack_delete(stack_asm);
    stack_delete(stack);
    fclose(input);
}
