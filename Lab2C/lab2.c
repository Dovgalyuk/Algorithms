#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

bool is_matching_tag(const char* opening, const char* closing) {
    return strcmp(opening + 1, closing + 2) == 0;
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

int main() {

    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

    if (!input_file || !output_file) {
        fprintf(stderr, "Error opening files.\n");
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
