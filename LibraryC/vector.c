#include "vector.h"
#include <stdlib.h>

typedef struct Vector {
  Data *items;
  size_t size;
  size_t capacity;
  FFree *free_fn;
} Vector;

Vector *vector_create(FFree f) {
  Vector *v = malloc(sizeof(Vector));
  if (v == NULL) {
    return NULL;
  }

  v->items = NULL;
  v->size = 0;
  v->capacity = 0;
  v->free_fn = f;

  return v;
}

void vector_delete(Vector *vector) {
  if (vector == NULL) {
    return;
  }

  if (vector->items) {
    if (vector->free_fn != NULL) {
      for (size_t i = 0; i < vector->size; i++) {
        Data val = vector->items[i];
        if (val != (Data)0) {
          vector->free_fn((void *)val);
        }
      }
    }
    free(vector->items);
  }

  free(vector);
}

Data vector_get(const Vector *vector, size_t index) {
  if (!vector || index >= vector->size) {
    return (Data)0;
  }
  return vector->items[index];
}

void vector_set(Vector *vector, size_t index, Data value) {
  if (!vector || index >= vector->size) {
    return;
  }

  if (vector->free_fn != NULL) {
    Data old_value = vector->items[index];
    if (old_value != (Data)0) {
      vector->free_fn((void *)old_value);
    }
  }

  vector->items[index] = value;
}

size_t vector_size(const Vector *vector) {
  if (vector == NULL) {
    return 0;
  }
  return vector->size;
}

void vector_resize(Vector *vector, size_t size) {
  if (vector == NULL) {
    return;
  }

  if (size < vector->size) {
    if (vector->free_fn != NULL) {
      for (size_t i = size; i < vector->size; i++) {
        Data val = vector->items[i];
        if (val != (Data)0) {
          vector->free_fn((void *)val);
        }
      }
    }
  }

  if (size > vector->size) {
    if (size > vector->capacity) {
      size_t new_capacity = vector->capacity ? vector->capacity : 1;
      while (new_capacity < size) {
        new_capacity *= 2;
      }

      Data *new_items = realloc(vector->items, new_capacity * sizeof(Data));
      if (new_items == NULL) {
        return;
      }

      vector->items = new_items;
      vector->capacity = new_capacity;
    }

    for (size_t i = vector->size; i < size; i++) {
      vector->items[i] = (Data)0;
    }
  }

  vector->size = size;
}

void vector_swap(Vector *vector, size_t idx1, size_t idx2) {
  if (!vector || idx1 >= vector->size || idx2 >= vector->size) {
    return;
  }

  Data tmp = vector->items[idx1];
  vector->items[idx1] = vector->items[idx2];
  vector->items[idx2] = tmp;
}
