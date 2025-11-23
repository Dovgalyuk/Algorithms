#include "interpreter.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(const char *filename, size_t *out_size) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  char *buffer = malloc(size + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, size, file);
  buffer[size] = '\0';
  fclose(file);

  if (out_size != NULL) {
    *out_size = size;
  }
  return buffer;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <script_file> <input_file>\n", argv[0]);
    return 1;
  }

  size_t script_size;
  char *script = read_file(argv[1], &script_size);
  if (script == NULL) {
    printf("Error: Failed to read script file '%s'\n", argv[1]);
    return 1;
  }

  FILE *input_file = fopen(argv[2], "r");
  if (input_file == NULL) {
    printf("Error: Failed to open input file '%s'\n", argv[2]);
    free(script);
    return 1;
  }

  Interpreter *interpreter = interpreter_create(free, input_file);
  if (interpreter == NULL) {
    printf("Error: Failed to create interpreter\n");
    free(script);
    fclose(input_file);
    return 1;
  }

  printf("=== Executing AnnoyingScript ===\n");
  int result = interpreter_execute_script(interpreter, script);

  if (result != 0) {
    printf("\n=== Execution failed ===\n");
  } else {
    printf("\n=== Execution completed ===\n");
  }

  printf("\n=== Final Stack State ===\n");
  while (!stack_empty(interpreter->stack)) {
    char *val = (char *)stack_get(interpreter->stack);
    if (val) {
      printf("%s\n", val);
    }
    stack_pop(interpreter->stack);
  }

  free(script);
  interpreter_delete(interpreter);
  fclose(input_file);

  return 0;
}
