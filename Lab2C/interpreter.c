#include "interpreter.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum ArgType { ARG_NONE, ARG_STRING } ArgType;

typedef struct Instruction {
  char symbol[2];
  ArgType arg_type;
  void (*handler)(Interpreter *interpreter, const char *arg);
} Instruction;

static void handle_plus(Interpreter *interpreter, const char *arg) {
  if (!arg) {
    return;
  }

  Data pushed = (Data)strdup(arg);
  stack_push(interpreter->stack, pushed);
}

static void handle_reverse(Interpreter *interp, const char *arg) {
  stack_reverse(interp->stack);
}

static void handle_remove_bottom(Interpreter *interp, const char *arg) {
  stack_shift(interp->stack);
}

static void handle_output(Interpreter *interp, const char *arg) {
  if (arg) {
    if (strcmp(arg, "~") == 0) {
      if (interp->tilde_value) {
        printf("%s\n", (char *)interp->tilde_value);
      }
    } else {
      printf("%s\n", arg);
    }
  } else if (!stack_empty(interp->stack)) {
    printf("%s\n", (char *)stack_get(interp->stack));
  }
}

static void handle_tilde(Interpreter *interp, const char *arg) {
  if (!stack_empty(interp->stack)) {
    interp->tilde_value = stack_get_bottom(interp->stack);
  }
}

static void handle_clear_tilde(Interpreter *interp, const char *arg) {
  interp->tilde_value = (Data)0;
}

static void handle_user_input(Interpreter *interp, const char *arg) {
  if (interp->input_file == NULL) {
    fprintf(stderr, "Error: No input file available for _ command\n");
    return;
  }

  char buffer[1024];

  if (fgets(buffer, sizeof(buffer), interp->input_file) != NULL) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    }
    Data input_data = (Data)strdup(buffer);
    stack_unshift(interp->stack, input_data);
  }
}

static void handle_combine_stack(Interpreter *interp, const char *arg) {
  stack_concat(interp->stack);
}

static Instruction instructions[] = {
    // Two-character commands first
    {{'~', '\\'}, ARG_NONE, handle_clear_tilde},
    // Single-character commands
    {{'+', '\0'}, ARG_STRING, handle_plus},
    {{'<', '\0'}, ARG_NONE, handle_reverse},
    {{'-', '\0'}, ARG_NONE, handle_remove_bottom},
    {{'>', '\0'}, ARG_STRING, handle_output},
    {{'~', '\0'}, ARG_NONE, handle_tilde},
    {{':', '\0'}, ARG_NONE, handle_combine_stack},
    {{'_', '\0'}, ARG_NONE, handle_user_input},
    {{0, 0}, ARG_NONE, NULL},
};

Interpreter *interpreter_create(FFree f, FILE *input_file) {
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

  return interp;
}

void interpreter_delete(Interpreter *interp) {
  if (interp == NULL) {
    return;
  }

  if (interp->stack) {
    stack_delete(interp->stack);
  }

  free(interp);
}

int interpreter_execute_script(Interpreter *interp, const char *script) {
  if (interp == NULL || script == NULL) {
    return -1;
  }

  const char *p = script;

  while (*p) {
    Instruction *ins = NULL;
    int instruction_length = 1;

    for (int i = 0; instructions[i].symbol[0]; i++) {
      if (*p == instructions[i].symbol[0]) {
        if (instructions[i].symbol[1] != '\0') {
          if (*(p + 1) == instructions[i].symbol[1]) {
            ins = &instructions[i];
            instruction_length = 2;
            break;
          }
        } else {
          ins = &instructions[i];
          instruction_length = 1;
          break;
        }
      }
    }

    if (!ins) {
      fprintf(stderr, "Error: Unknown instruction: %c at position %ld\n", *p,
              p - script);
      break;
    }

    char *arg = NULL;

    if (ins->arg_type == ARG_STRING) {
      p += instruction_length;

      if (*p == '{') {
        const char *start = ++p;

        while (*p && *p != '}') {
          p++;
        }
        size_t arg_len = p - start;

        arg = malloc(arg_len + 1);

        strncpy(arg, start, arg_len);

        arg[arg_len] = '\0';

        if (*p == '}') {
          p++;
        }
      } else {
        arg = malloc(2);
        arg[0] = *p;
        arg[1] = '\0';
        p++;
      }
    } else {
      p += instruction_length;
    }

    ins->handler(interp, arg);
    if (arg) {
      free(arg);
    }
  }

  return 0;
}
