#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

char* str_to_lower(const char* str) {
    size_t len = strlen(str);
    char* lower_str = malloc(len + 1);
    if (lower_str) {
        for (size_t i = 0; i < len; i++) {
            lower_str[i] = (char)tolower((unsigned char)str[i]);
        }
        lower_str[len] = '\0';
    }
    return lower_str;
}


bool is_matching_tag(const char* opening, const char* closing) {
    char* opening_lower = str_to_lower(opening);
    char* closing_lower = str_to_lower(closing);
    bool match = (strcmp(opening_lower + 1, closing_lower + 2) == 0);
    free(opening_lower);
    free(closing_lower);
    return match;
}

bool is_valid_html(FILE* input) {
    Stack* stack = stack_create(free);
    char line[256];

    while (fgets(line, sizeof(line), input)) {
        char* tag = strtok(line, "\n");
        if (tag == NULL) continue;

        if (tag[1] != '/') {
            char* tag_copy = strdup(tag);
            stack_push(stack, tag_copy);
        }
        else {
            if (stack_empty(stack) || !is_matching_tag(stack_get(stack), tag)) {
                stack_delete(stack);
                return false;
            }
            stack_pop(stack);
        }
    }

    bool result = stack_empty(stack);
    stack_delete(stack);
    return result;
}

int main(int argc, char* argv[]) {

    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");

    if (!input_file || !output_file) {
        return 1;
    }

    if (is_valid_html(input_file)) {
        fprintf(output_file, "YES\n");
    }
    else {
        fprintf(output_file, "NO\n");
    }

    fclose(input_file);
    fclose(output_file);


    return 0;
}
