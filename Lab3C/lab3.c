#include "game.h"
#include <stdio.h>
#include <stdlib.h>

static void print_solution_path(State *solution) {
  int path_length = 0;
  State *current = solution;
  while (current != NULL) {
    path_length++;
    current = current->parent;
  }

  State **path = (State **)malloc(path_length * sizeof(State *));
  if (path == NULL)
    return;

  current = solution;
  for (int i = path_length - 1; i >= 0; i--) {
    path[i] = current;
    current = current->parent;
  }

  for (int i = 0; i < path_length; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%d", path[i]->board[j]);
    }
    printf("\n");
  }

  free(path);
}

int main(void) {
  int board[9];
  char input[10];

  if (scanf("%9s", input) != 1)
    return 1;

  for (int i = 0; i < 9; i++) {
    board[i] = input[i] - '0';
  }

  State *solution = solve_puzzle(board);

  if (solution == NULL) {
    return 1;
  }

  print_solution_path(solution);

  State *current = solution;
  while (current != NULL) {
    State *parent = current->parent;
    state_free(current);
    current = parent;
  }

  return 0;
}
