#include "../LibraryC/queue.h"
#include "../LibraryC/vector.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 100
#define MAX_NAME_LENGTH 50

typedef struct {
  char name[MAX_NAME_LENGTH];
  Vector *neighbors;
  int visited;
  int parent;
} City;

void free_city(Data data) {
  City *city = (City *)data;
  if (city) {
    vector_delete(city->neighbors);
    free(city);
  }
}

int find_city(Vector *cities, const char *name) {
  for (size_t i = 0; i < vector_size(cities); i++) {
    City *city = (City *)vector_get(cities, i);
    if (strcmp(city->name, name) == 0) {
      return i;
    }
  }
  return -1;
}

int add_city(Vector *cities, const char *name) {
  int index = find_city(cities, name);
  if (index != -1)
    return index;

  City *new_city = malloc(sizeof(City));
  if (!new_city)
    return -1;

  strncpy(new_city->name, name, MAX_NAME_LENGTH - 1);
  new_city->name[MAX_NAME_LENGTH - 1] = '\0';
  new_city->neighbors = vector_create(NULL);
  new_city->visited = 0;
  new_city->parent = -1;

  vector_resize(cities, vector_size(cities) + 1);
  vector_set(cities, vector_size(cities) - 1, new_city);
  return vector_size(cities) - 1;
}

void add_edge(Vector *cities, int city1_idx, int city2_idx) {
  City *city1 = vector_get(cities, city1_idx);
  City *city2 = vector_get(cities, city2_idx);

  vector_resize(city1->neighbors, vector_size(city1->neighbors) + 1);
  vector_set(city1->neighbors, vector_size(city1->neighbors) - 1,
             (Data)(intptr_t)city2_idx);

  vector_resize(city2->neighbors, vector_size(city2->neighbors) + 1);
  vector_set(city2->neighbors, vector_size(city2->neighbors) - 1,
             (Data)(intptr_t)city1_idx);
}

void find_path(Vector *cities, int start_idx, int end_idx) {
  Queue *queue = queue_create(NULL);

  // Сброс состояния всех городов
  for (size_t i = 0; i < vector_size(cities); i++) {
    City *city = vector_get(cities, i);
    city->visited = 0;
    city->parent = -1;
  }

  City *start_city = vector_get(cities, start_idx);
  start_city->visited = 1;
  queue_insert(queue, (Data)(intptr_t)start_idx);

  while (!queue_empty(queue)) {
    int current_idx = (int)(intptr_t)queue_get(queue);
    queue_remove(queue);

    if (current_idx == end_idx)
      break;

    City *current_city = vector_get(cities, current_idx);
    for (size_t i = 0; i < vector_size(current_city->neighbors); i++) {
      int neighbor_idx = (int)(intptr_t)vector_get(current_city->neighbors, i);
      City *neighbor = vector_get(cities, neighbor_idx);

      if (!neighbor->visited) {
        neighbor->visited = 1;
        neighbor->parent = current_idx;
        queue_insert(queue, (Data)(intptr_t)neighbor_idx);
      }
    }
  }

  queue_delete(queue);
}

void print_path(Vector *cities, int end_idx) {
  int current_idx = end_idx;
  int path[MAX_CITIES];
  int path_length = 0;

  while (current_idx != -1) {
    path[path_length++] = current_idx;
    City *current_city = vector_get(cities, current_idx);
    current_idx = current_city->parent;
  }

  for (int i = path_length - 1; i >= 0; i--) {
    City *city = vector_get(cities, path[i]);
    printf("%s", city->name);
    if (i > 0)
      printf(" ");
  }
  printf("\n");
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Использование: %s <input_file>\n", argv[0]);
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (!input) {
    printf("Ошибка открытия файла %s\n", argv[1]);
    return 1;
  }

  Vector *cities = vector_create(free_city);
  char city1[MAX_NAME_LENGTH], city2[MAX_NAME_LENGTH];
  char start[MAX_NAME_LENGTH], end[MAX_NAME_LENGTH];

  int line_count = 0;
  char line[MAX_NAME_LENGTH * 2];
  while (fgets(line, sizeof(line), input)) {
    line_count++;
  }
  rewind(input);

  for (int i = 0; i < line_count - 1; i++) {
    if (fscanf(input, "%s %s", city1, city2) == 2) {
      int city1_idx = add_city(cities, city1);
      int city2_idx = add_city(cities, city2);

      if (city1_idx != -1 && city2_idx != -1) {
        add_edge(cities, city1_idx, city2_idx);
      }
    }
  }

  if (fscanf(input, "%s %s", start, end) != 2) {
    printf("Ошибка чтения начального и конечного городов\n");
    vector_delete(cities);
    fclose(input);
    return 1;
  }

  int start_idx = find_city(cities, start);
  int end_idx = find_city(cities, end);

  if (start_idx == -1 || end_idx == -1) {
    printf("Ошибка: начальный или конечный город не найден\n");
    vector_delete(cities);
    fclose(input);
    return 1;
  }

  find_path(cities, start_idx, end_idx);
  print_path(cities, end_idx);

  fclose(input);
  vector_delete(cities);
  return 0;
}
