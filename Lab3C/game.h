#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef struct State {
  int board[9];
  struct State *parent;
  char last_move;
} State;

State *state_create(int *board, State *parent, char move);
void state_free(State *state);
State *solve_puzzle(int *initial_board);

#endif
