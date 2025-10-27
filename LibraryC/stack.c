#include "stack.h"
#include "vector.h"
#include <stdlib.h>
#include <string.h> // Added for strlen and strcat

typedef struct Stack {
  Vector *vector;
} Stack;

Stack *stack_create(FFree f) {
  Stack *s = malloc(sizeof(Stack));
  if (s == NULL) {
    return NULL;
  }

  s->vector = vector_create(f);
  if (s->vector == NULL) {
    free(s);
    return NULL;
  }

  return s;
}

void stack_delete(Stack *stack) {
  if (stack == NULL) {
    return;
  }

  if (stack->vector) {
    vector_delete(stack->vector);
  }

  free(stack);
}

void stack_push(Stack *stack, Data data) {
  if (stack == NULL) {
    return;
  }

  vector_resize(stack->vector, vector_size(stack->vector) + 1);
  vector_set(stack->vector, vector_size(stack->vector) - 1, data);
}

Data stack_get(const Stack *stack) {
  if (stack == NULL || vector_size(stack->vector) == 0) {
    return (Data)0;
  }

  return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack *stack) {
  if (stack == NULL || vector_size(stack->vector) == 0) {
    return;
  }

  vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack *stack) {
  return (stack == NULL || vector_size(stack->vector) == 0);
}

void stack_reverse(Stack *stack) {
  if (stack == NULL) {
    return;
  }

  size_t n = vector_size(stack->vector);

  for (size_t i = 0; i < n / 2; i++) {
    vector_swap(stack->vector, i, n - i - 1);
  }
}

Data stack_get_bottom(Stack *stack) {
  if (stack == NULL || vector_size(stack->vector) == 0) {
    return (Data)0;
  }

  return vector_get(stack->vector, 0);
}

void stack_unshift(Stack *stack, Data data) {
  if (stack == NULL) {
    return;
  }

  size_t n = vector_size(stack->vector);

  vector_resize(stack->vector, n + 1);

  for (size_t i = n; i > 0; i--) {
    vector_set(stack->vector, i, vector_get(stack->vector, i - 1));
  }

  vector_set(stack->vector, 0, data);
}

Data stack_shift(Stack *stack) {
  if (stack == NULL || vector_size(stack->vector) == 0) {
    return (Data)0;
  }

  Data bottom = vector_get(stack->vector, 0);
  size_t n = vector_size(stack->vector);

  for (size_t i = 0; i < n - 1; i++) {
    vector_set(stack->vector, i, vector_get(stack->vector, i + 1));
  }

  vector_resize(stack->vector, n - 1);

  return bottom;
}

void stack_concat(Stack *stack) {
  if (stack == NULL || vector_size(stack->vector) == 0) {
    return;
  }

  size_t n = vector_size(stack->vector);

  size_t total_size = 1;
  for (size_t i = 0; i < n; i++) {
    char *elem = (char *)vector_get(stack->vector, i);
    if (elem) {
      total_size += strlen(elem);
    }
  }

  char *combined = malloc(total_size);
  if (!combined) {
    return;
  }
  combined[0] = '\0';

  for (size_t i = 0; i < n; i++) {
    char *elem = (char *)vector_get(stack->vector, i);
    if (elem) {
      strcat(combined, elem);
    }
  }

  vector_resize(stack->vector, 0);

  stack_push(stack, (Data)combined);
}
