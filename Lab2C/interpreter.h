#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "stack.h"
#include <stdint.h>
#include <stdio.h>

typedef struct Interpreter {
  Stack *stack;
  Data tilde_value;
  FILE *input_file;
} Interpreter;

Interpreter *interpreter_create(FFree f, FILE *input_file);

void interpreter_delete(Interpreter *interp);

int interpreter_execute_script(Interpreter *interp, const char *script);

#endif
