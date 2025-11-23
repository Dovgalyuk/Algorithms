#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "stack.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_VARIABLES 1000

#define MAX_CONDITION_DEPTH 100

typedef struct Variable {
  Data value;
  bool exists;
} Variable;

typedef struct ConditionFrame {
  size_t start_ip;
} ConditionFrame;

typedef struct Interpreter {
  Stack *stack;

  Data tilde_value;

  FILE *input_file;

  const char *script;
  size_t script_length;
  size_t ip;
  bool halted;

  Variable variables[MAX_VARIABLES];
  size_t next_var_id;

  ConditionFrame cond_stack[MAX_CONDITION_DEPTH];
  size_t cond_depth;

  FFree *free_fn;
} Interpreter;

Interpreter *interpreter_create(FFree f, FILE *input_file);

void interpreter_delete(Interpreter *interp);

int interpreter_execute_script(Interpreter *interp, const char *script);

long data_to_number(Data d);

Data number_to_data(long num);

bool data_is_number(Data d);

#endif
