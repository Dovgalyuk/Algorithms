#include "interpreter.h"
#include "stack.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum { ARG_NONE, ARG_STRING, ARG_NUMBER } ArgType;

typedef struct Instruction {
  char symbol[3];
  ArgType arg_type;
  void (*handler)(Interpreter *interp, const char *arg);
} Instruction;

static void handle_push(Interpreter *interp, const char *arg);
static void handle_remove_bottom(Interpreter *interp, const char *arg);
static void handle_output(Interpreter *interp, const char *arg);
static void handle_tilde(Interpreter *interp, const char *arg);
static void handle_clear_tilde(Interpreter *interp, const char *arg);
static void handle_reverse(Interpreter *interp, const char *arg);
static void handle_concat(Interpreter *interp, const char *arg);
static void handle_jump(Interpreter *interp, const char *arg);
static void handle_if(Interpreter *interp, const char *arg);
static void handle_ifnot(Interpreter *interp, const char *arg);
static void handle_endif(Interpreter *interp, const char *arg);
static void handle_create_var(Interpreter *interp, const char *arg);
static void handle_tilde_get_var(Interpreter *interp, const char *arg);
static void handle_delete_var(Interpreter *interp, const char *arg);
static void handle_math(Interpreter *interp, const char *arg);
static void handle_get_var(Interpreter *interp, const char *arg);
static void handle_halt(Interpreter *interp, const char *arg);
static void handle_input(Interpreter *interp, const char *arg);
static void handle_random(Interpreter *interp, const char *arg);

static Instruction instructions[] = {
    {{'~', '\\'}, ARG_NONE, handle_clear_tilde},
    {{'~', '('}, ARG_NUMBER, handle_tilde_get_var},
    {{'=', ')'}, ARG_NUMBER, handle_delete_var},
    {{'?', '!'}, ARG_STRING, handle_ifnot},
    {{'+', '\0'}, ARG_STRING, handle_push},
    {{'-', '\0'}, ARG_NONE, handle_remove_bottom},
    {{'>', '\0'}, ARG_STRING, handle_output},
    {{'~', '\0'}, ARG_NONE, handle_tilde},
    {{'<', '\0'}, ARG_NONE, handle_reverse},
    {{':', '\0'}, ARG_NONE, handle_concat},
    {{'!', '\0'}, ARG_NUMBER, handle_jump},
    {{'?', '\0'}, ARG_STRING, handle_if},
    {{'|', '\0'}, ARG_NONE, handle_endif},
    {{'=', '\0'}, ARG_NONE, handle_create_var},
    {{'&', '\0'}, ARG_STRING, handle_math},
    {{'@', '\0'}, ARG_NUMBER, handle_get_var},
    {{'#', '\0'}, ARG_NONE, handle_halt},
    {{'_', '\0'}, ARG_NONE, handle_input},
    {{'$', '\0'}, ARG_NUMBER, handle_random},
    {{0, 0}, ARG_NONE, NULL}};

long data_to_number(Data d) {
  if (d == (Data)0) {
    return 0;
  }
  return atol((const char *)d);
}

Data number_to_data(long n) {
  char *str = malloc(32);
  if (!str) {
    return (Data)0;
  }
  snprintf(str, 32, "%ld", n);
  return (Data)str;
}

bool data_is_number(Data d) {
  if (d == (Data)0) {
    return false;
  }
  const char *str = (const char *)d;
  if (*str == '-' || *str == '+') {
    str++;
  }
  if (*str == '\0') {
    return false;
  }
  while (*str) {
    if (!isdigit(*str)) {
      return false;
    }
    str++;
  }
  return true;
}

static Instruction *find_instruction_at_ip(Interpreter *interp) {
  if (interp->ip >= interp->script_length) {
    return NULL;
  }

  char c1 = interp->script[interp->ip];
  char c2 = (interp->ip + 1 < interp->script_length)
                ? interp->script[interp->ip + 1]
                : '\0';

  for (int i = 0; instructions[i].handler != NULL; i++) {
    if (instructions[i].symbol[1] != '\0') {
      if (c1 == instructions[i].symbol[0] && c2 == instructions[i].symbol[1]) {
        return &instructions[i];
      }
    } else if (c1 == instructions[i].symbol[0]) {
      return &instructions[i];
    }
  }

  return NULL;
}

static char *parse_argument(Interpreter *interp, ArgType arg_type) {
  if (arg_type == ARG_NONE) {
    return NULL;
  }

  if (interp->ip >= interp->script_length) {
    return NULL;
  }

  char current = interp->script[interp->ip];

  if (current == '{') {
    interp->ip++;
    const char *start = &interp->script[interp->ip];
    size_t len = 0;

    while (interp->ip < interp->script_length &&
           interp->script[interp->ip] != '}') {
      interp->ip++;
      len++;
    }

    char *result = malloc(len + 1);
    if (result) {
      strncpy(result, start, len);
      result[len] = '\0';
    }

    if (interp->ip < interp->script_length &&
        interp->script[interp->ip] == '}') {
      interp->ip++;
    }

    return result;
  }

  if (arg_type == ARG_NUMBER) {
    const char *start = &interp->script[interp->ip];
    size_t len = 0;

    if (current == '-') {
      len++;
      interp->ip++;
    }

    while (interp->ip < interp->script_length &&
           interp->script[interp->ip] >= '0' &&
           interp->script[interp->ip] <= '9') {
      len++;
      interp->ip++;
    }

    if (len == 0) {
      return NULL;
    }

    char *result = malloc(len + 1);
    if (result) {
      strncpy(result, start, len);
      result[len] = '\0';
    }

    return result;
  }

  char *result = malloc(2);
  if (result) {
    result[0] = current;
    result[1] = '\0';
  }
  interp->ip++;

  return result;
}

static void handle_push(Interpreter *interp, const char *arg) {
  if (!arg) {
    return;
  }

  Data pushed = (Data)strdup(arg);
  stack_push(interp->stack, pushed);
}

static void handle_remove_bottom(Interpreter *interp, const char *arg) {
  (void)arg;

  if (interp->tilde_value != (Data)0 && !stack_empty(interp->stack)) {
    Data bottom = stack_get_bottom(interp->stack);
    if (bottom == interp->tilde_value) {
      bool tilde_in_vars = false;
      for (size_t i = 0; i < MAX_VARIABLES; i++) {
        if (interp->variables[i].exists &&
            interp->variables[i].value == interp->tilde_value) {
          tilde_in_vars = true;
          break;
        }
      }

      if (!tilde_in_vars) {
        interp->tilde_value = (Data)0;
      }
    }
  }

  stack_remove_bottom(interp->stack);
}

static void handle_output(Interpreter *interp, const char *arg) {
  if (arg) {
    if (strcmp(arg, "~") == 0) {
      if (interp->tilde_value != (Data)0) {
        printf("%s\n", (char *)interp->tilde_value);
      }
    } else {
      printf("%s\n", arg);
    }
  } else {
    if (!stack_empty(interp->stack)) {
      Data top = stack_get(interp->stack);
      if (top != (Data)0) {
        printf("%s\n", (char *)top);
      }
    }
  }
}

static void handle_tilde(Interpreter *interp, const char *arg) {
  (void)arg;
  if (!stack_empty(interp->stack)) {
    interp->tilde_value = stack_get_bottom(interp->stack);
  }
}

static void handle_clear_tilde(Interpreter *interp, const char *arg) {
  (void)arg;
  interp->tilde_value = (Data)0;
}

static void handle_reverse(Interpreter *interp, const char *arg) {
  (void)arg;
  stack_reverse(interp->stack);
}

static void handle_concat(Interpreter *interp, const char *arg) {
  (void)arg;

  if (interp->tilde_value != (Data)0) {
    bool tilde_in_vars = false;
    for (size_t i = 0; i < MAX_VARIABLES; i++) {
      if (interp->variables[i].exists &&
          interp->variables[i].value == interp->tilde_value) {
        tilde_in_vars = true;
        break;
      }
    }

    if (!tilde_in_vars) {
      interp->tilde_value = (Data)0;
    }
  }

  stack_concat(interp->stack);
}

static void handle_jump(Interpreter *interp, const char *arg) {
  if (!arg) {
    return;
  }

  long position = atol(arg);
  if (position < 0 || (size_t)position > interp->script_length) {
    return;
  }

  interp->ip = (size_t)position;
}

static void skip_to_matching_pipe(Interpreter *interp) {
  int depth = 1;

  while (interp->ip < interp->script_length && depth > 0) {
    char c = interp->script[interp->ip];

    if (c == '?') {
      depth++;
    } else if (c == '|') {
      depth--;
      if (depth == 0) {
        return;
      }
    }

    interp->ip++;
  }
}

static void handle_if(Interpreter *interp, const char *arg) {
  if (!arg) {
    skip_to_matching_pipe(interp);
    return;
  }

  if (interp->tilde_value == (Data)0) {
    skip_to_matching_pipe(interp);
    return;
  }

  const char *tilde_str = (const char *)interp->tilde_value;
  if (strcmp(tilde_str, arg) != 0) {
    skip_to_matching_pipe(interp);
  }
}

static void handle_ifnot(Interpreter *interp, const char *arg) {
  if (!arg) {
    return;
  }

  if (interp->tilde_value == (Data)0) {
    return;
  }

  const char *tilde_str = (const char *)interp->tilde_value;
  if (strcmp(tilde_str, arg) == 0) {
    skip_to_matching_pipe(interp);
  }
}

static void handle_endif(Interpreter *interp, const char *arg) { (void)arg; }

static void handle_create_var(Interpreter *interp, const char *arg) {
  (void)arg;

  if (interp->tilde_value == (Data)0) {
    return;
  }

  if (interp->next_var_id >= MAX_VARIABLES) {
    fprintf(stderr, "Error: Maximum number of variables (%d) exceeded\n",
            MAX_VARIABLES);
    return;
  }

  char *value_copy = strdup((const char *)interp->tilde_value);
  if (!value_copy) {
    return;
  }

  interp->variables[interp->next_var_id].value = (Data)value_copy;
  interp->variables[interp->next_var_id].exists = true;
  interp->next_var_id++;
}

static void handle_tilde_get_var(Interpreter *interp, const char *arg) {
  if (!arg) {
    return;
  }

  long var_id = atol(arg);
  if (var_id < 0 || (size_t)var_id >= MAX_VARIABLES) {
    fprintf(stderr, "Error: Variable ID %ld out of range\n", var_id);
    return;
  }

  if (!interp->variables[var_id].exists) {
    fprintf(stderr, "Error: Variable %ld doesn't exist\n", var_id);
    return;
  }

  interp->tilde_value = interp->variables[var_id].value;
}

static void handle_delete_var(Interpreter *interp, const char *arg) {
  if (!arg) {
    return;
  }

  long var_id = atol(arg);
  if (var_id < 0 || (size_t)var_id >= MAX_VARIABLES) {
    fprintf(stderr, "Error: Variable ID %ld out of range\n", var_id);
    return;
  }

  if (!interp->variables[var_id].exists) {
    return;
  }

  if (interp->tilde_value == interp->variables[var_id].value) {
    interp->tilde_value = (Data)0;
  }

  free((char *)interp->variables[var_id].value);
  interp->variables[var_id].value = (Data)0;
  interp->variables[var_id].exists = false;
}

static void handle_math(Interpreter *interp, const char *arg) {
  if (!arg || stack_empty(interp->stack)) {
    return;
  }

  Data first_data = stack_get_bottom(interp->stack);
  char *first_str = strdup((const char *)first_data);
  stack_remove_bottom(interp->stack);

  if (stack_empty(interp->stack)) {
    free(first_str);
    return;
  }

  Data second_data = stack_get_bottom(interp->stack);
  char *second_str = strdup((const char *)second_data);
  stack_remove_bottom(interp->stack);

  long first = atol(first_str);
  long second = atol(second_str);
  long result = 0;

  switch (arg[0]) {
  case '+':
    result = first + second;
    break;
  case '-':
    result = first - second;
    break;
  case '*':
    result = first * second;
    break;
  case '/':
    if (second != 0) {
      result = first / second;
    }
    break;
  case '%':
    if (second != 0) {
      result = first % second;
    }
    break;
  }

  Data result_data = number_to_data(result);
  stack_push(interp->stack, result_data);

  free(first_str);
  free(second_str);
}

static void handle_get_var(Interpreter *interp, const char *arg) {
  if (!arg) {
    return;
  }

  long var_id = atol(arg);
  if (var_id < 0 || (size_t)var_id >= MAX_VARIABLES) {
    fprintf(stderr, "Error: Variable ID %ld out of range\n", var_id);
    return;
  }

  if (!interp->variables[var_id].exists) {
    fprintf(stderr, "Error: Variable %ld doesn't exist\n", var_id);
    return;
  }

  char *value_copy = strdup((const char *)interp->variables[var_id].value);
  if (!value_copy) {
    return;
  }

  stack_push(interp->stack, (Data)value_copy);
}

static void handle_halt(Interpreter *interp, const char *arg) {
  (void)arg;
  interp->halted = true;
}

static void handle_input(Interpreter *interp, const char *arg) {
  (void)arg;

  if (!interp->input_file) {
    return;
  }

  char buffer[1024];
  if (!fgets(buffer, sizeof(buffer), interp->input_file)) {
    return;
  }

  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
    len--;
  }

  char *input_copy = strdup(buffer);
  if (!input_copy) {
    return;
  }

  stack_reverse(interp->stack);
  stack_push(interp->stack, (Data)input_copy);
  stack_reverse(interp->stack);
}

static void handle_random(Interpreter *interp, const char *arg) {
  if (!arg) {
    return;
  }

  long max = atol(arg);
  if (max <= 0) {
    return;
  }

  long random_num = (rand() % max) + 1;
  Data random_data = number_to_data(random_num);

  if (random_data != (Data)0) {
    stack_push(interp->stack, random_data);
  }
}

Interpreter *interpreter_create(FFree f, FILE *input_file) {
  srand((unsigned int)time(NULL));

  Interpreter *interp = malloc(sizeof(Interpreter));
  if (interp == NULL) {
    return NULL;
  }

  interp->stack = stack_create(f);
  if (interp->stack == NULL) {
    free(interp);
    return NULL;
  }

  interp->tilde_value = (Data)0;
  interp->input_file = input_file;
  interp->script = NULL;
  interp->script_length = 0;
  interp->ip = 0;
  interp->halted = false;

  for (size_t i = 0; i < MAX_VARIABLES; i++) {
    interp->variables[i].value = (Data)0;
    interp->variables[i].exists = false;
  }
  interp->next_var_id = 0;

  interp->cond_depth = 0;

  interp->free_fn = f;

  return interp;
}

void interpreter_delete(Interpreter *interp) {
  if (interp == NULL) {
    return;
  }

  if (interp->stack) {
    stack_delete(interp->stack);
  }

  if (interp->free_fn) {
    for (size_t i = 0; i < MAX_VARIABLES; i++) {
      if (interp->variables[i].exists &&
          interp->variables[i].value != (Data)0) {
        interp->free_fn((void *)interp->variables[i].value);
      }
    }
  }

  free(interp);
}

int interpreter_execute_script(Interpreter *interp, const char *script) {
  if (interp == NULL || script == NULL) {
    return -1;
  }

  interp->script = script;
  interp->script_length = strlen(script);
  interp->ip = 0;
  interp->halted = false;
  interp->cond_depth = 0;

  while (interp->ip < interp->script_length && !interp->halted) {
    while (interp->ip < interp->script_length &&
           (interp->script[interp->ip] == ' ' ||
            interp->script[interp->ip] == '\n' ||
            interp->script[interp->ip] == '\r' ||
            interp->script[interp->ip] == '\t')) {
      interp->ip++;
    }

    if (interp->ip >= interp->script_length) {
      break;
    }

    Instruction *ins = find_instruction_at_ip(interp);
    if (ins == NULL) {
      fprintf(stderr, "Error: Unknown instruction '%c' at position %zu\n",
              interp->script[interp->ip], interp->ip);
      return -1;
    }

    size_t symbol_len = (ins->symbol[1] != '\0') ? 2 : 1;
    interp->ip += symbol_len;

    char *arg = parse_argument(interp, ins->arg_type);

    ins->handler(interp, arg);

    if (arg) {
      free(arg);
    }
  }

  return 0;
}
