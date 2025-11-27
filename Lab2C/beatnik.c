#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "stack.h"

static int letter_score(char c)
{
    c = (char)toupper((unsigned char)c);
    switch (c) {
        case 'A': case 'E': case 'I': case 'L': case 'N': case 'O': case 'R': case 'S': case 'T': case 'U': return 1;
        case 'D': case 'G': return 2;
        case 'B': case 'C': case 'M': case 'P': return 3;
        case 'F': case 'H': case 'V': case 'W': case 'Y': return 4;
        case 'K': return 5;
        case 'J': case 'X': return 8;
        case 'Q': case 'Z': return 10;
        default: return 0;
    }
}

static int word_score(const char *word)
{
    int sum = 0;
    for (const char *p = word; *p; ++p) {
        if (isalpha((unsigned char)*p)) sum += letter_score(*p);
    }
    return sum;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <script_file> <input_file>\n", argv[0]);
        return 1;
    }

    FILE *script = fopen(argv[1], "r");
    if (!script) { perror("script open"); return 1; }

    FILE *input = fopen(argv[2], "r");
    if (!input) { perror("input open"); fclose(script); return 1; }

    Stack *stack = stack_create(NULL);
    if (!stack) { fprintf(stderr, "Stack alloc failed\n"); fclose(script); fclose(input); return 1; }

    fseek(script, 0, SEEK_END);
    long len = ftell(script);

    fseek(script, 0, SEEK_SET);
    char *buf = malloc(len + 1);
    if (!buf) { fprintf(stderr, "Mem alloc failed\n"); stack_delete(stack); fclose(script); fclose(input); return 1; }
    fread(buf, 1, len, script);
    buf[len] = '\0';

    char word[256];
    size_t wi = 0;
    for (long i = 0; i <= len; ++i) {
        char c = buf[i];
        if (isalpha((unsigned char)c)) {
            if (wi < sizeof(word)-1) word[wi++] = c;
        } else {
            if (wi > 0) {
                word[wi] = '\0';
                int score = word_score(word);
                switch (score) {
                    case 6:
                        if (!stack_empty(stack)) {
                            stack_pop(stack);
                        }
                        break;
                    case 8:
                        stack_push(stack, (Data)(uintptr_t)(unsigned char)word[0]);
                        break;
                    case 10:
                        if (!stack_empty(stack)) {
                            unsigned char top = (unsigned char)(uintptr_t)stack_get(stack);
                            stack_push(stack, (Data)(uintptr_t)top);
                        }
                        break;
                    case 11:
                        if (!stack_empty(stack)) {
                            unsigned char a = (unsigned char)(uintptr_t)stack_get(stack);
                            stack_pop(stack);
                            if (!stack_empty(stack)) {
                                unsigned char b = (unsigned char)(uintptr_t)stack_get(stack);
                                stack_pop(stack);
                                stack_push(stack, (Data)(uintptr_t)a);
                                stack_push(stack, (Data)(uintptr_t)b);
                            } else {
                                stack_push(stack, (Data)(uintptr_t)a);
                            }
                        }
                        break;
                    case 5:
                        if (!stack_empty(stack)) {
                            const unsigned char ch = (unsigned char)(uintptr_t)stack_get(stack);
                            putchar(ch);
                            stack_pop(stack);
                        }
                        break;
                    case 7: {
                        int in = fgetc(input);
                        if (in != EOF) {
                            stack_push(stack, (Data)(uintptr_t)(unsigned char)in);
                        }
                        break; }
                    case 9:
                        i = len + 1;
                        break;
                    case 12:
                        if (!stack_empty(stack)) {
                            const unsigned char b = (unsigned char)(uintptr_t)stack_get(stack);
                            stack_pop(stack);
                            if (!stack_empty(stack)) {
                                const unsigned char a = (unsigned char)(uintptr_t)stack_get(stack);
                                stack_pop(stack);
                                stack_push(stack, (Data)(uintptr_t)(unsigned char)(a + b));
                            } else {
                                stack_push(stack, (Data)(uintptr_t)b);
                            }
                        }
                        break;
                    case 13: {
                        int num;
                        if (fscanf(input, "%d", &num) == 1) {
                            stack_push(stack, (Data)(uintptr_t)(unsigned char)num);
                        }
                        break; }
                    case 14:
                        if (!stack_empty(stack)) {
                            unsigned char b = (unsigned char)(uintptr_t)stack_get(stack);
                            stack_pop(stack);
                            if (!stack_empty(stack)) {
                                unsigned char a = (unsigned char)(uintptr_t)stack_get(stack);
                                stack_pop(stack);
                                stack_push(stack, (Data)(uintptr_t)(unsigned char)(a - b));
                            } else {
                                stack_push(stack, (Data)(uintptr_t)b);
                            }
                        }
                        break;
                    case 15:
                        if (!stack_empty(stack)) {
                            unsigned char b = (unsigned char)(uintptr_t)stack_get(stack);
                            stack_pop(stack);
                            if (!stack_empty(stack)) {
                                unsigned char a = (unsigned char)(uintptr_t)stack_get(stack);
                                stack_pop(stack);
                                if (b != 0) {
                                    stack_push(stack, (Data)(uintptr_t)(unsigned char)(a / b));
                                } else {
                                    stack_push(stack, (Data)(uintptr_t)a);
                                    stack_push(stack, (Data)(uintptr_t)b);
                                }
                            } else {
                                stack_push(stack, (Data)(uintptr_t)b);
                            }
                        }
                        break;
                    case 16:
                        if (!stack_empty(stack)) {
                            unsigned char b = (unsigned char)(uintptr_t)stack_get(stack);
                            stack_pop(stack);
                            if (!stack_empty(stack)) {
                                unsigned char a = (unsigned char)(uintptr_t)stack_get(stack);
                                stack_pop(stack);
                                stack_push(stack, (Data)(uintptr_t)(unsigned char)(a * b));
                            } else {
                                stack_push(stack, (Data)(uintptr_t)b);
                            }
                        }
                        break;
                    case 17:
                        if (!stack_empty(stack)) {
                            unsigned char b = (unsigned char)(uintptr_t)stack_get(stack);
                            stack_pop(stack);
                            if (!stack_empty(stack)) {
                                unsigned char a = (unsigned char)(uintptr_t)stack_get(stack);
                                stack_pop(stack);
                                if (b != 0) {
                                    stack_push(stack, (Data)(uintptr_t)(unsigned char)(a % b));
                                } else {
                                    stack_push(stack, (Data)(uintptr_t)a);
                                    stack_push(stack, (Data)(uintptr_t)b);
                                }
                            } else {
                                stack_push(stack, (Data)(uintptr_t)b);
                            }
                        }
                        break;
                    case 18: case 19: case 20: case 21: case 22:
                        if (!stack_empty(stack)) {
                            unsigned char top = (unsigned char)(uintptr_t)stack_get(stack);
                            if (top == 0) {
                                wi = 0;
                                while (i < len && (isalpha((unsigned char)buf[i]) ||
                                       (!isalpha((unsigned char)buf[i]) && wi == 0))) {
                                    if (isalpha((unsigned char)buf[i])) {
                                        wi = 1;
                                    } else if (wi > 0) {
                                        break;
                                    }
                                    i++;
                                }
                            }
                        }
                        break;
                    case 23:
                        if (!stack_empty(stack)) {
                            unsigned char num = (unsigned char)(uintptr_t)stack_get(stack);
                            printf("%d", (int)num);
                            stack_pop(stack);
                        }
                        break;
                    default:
                        break;
                }
                wi = 0;
            }
        }
    }

    free(buf);
    stack_delete(stack);
    fclose(script);
    fclose(input);
    return 0;
}
