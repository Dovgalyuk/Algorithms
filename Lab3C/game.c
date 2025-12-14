#include "game.h"
#include "../LibraryC/queue.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

State *state_create(int *board, State *parent, char move) {
  State *s = malloc(sizeof(State));
  if (s == NULL)
    return NULL;
  memcpy(s->board, board, 9 * sizeof(int));
  s->parent = parent;
  s->last_move = move;
  return s;
}

void state_free(State *state) {
  if (state)
    free(state);
}

static bool state_is_goal(const int *board) {
  int goal[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  return memcmp(board, goal, 9 * sizeof(int)) == 0;
}

static int find_empty(const int *board) {
  for (int i = 0; i < 9; i++) {
    if (board[i] == 0)
      return i;
  }
  return -1;
}

typedef struct {
  State *states[181440];
  int count;
} VisitedSet;

static VisitedSet *visited_create(void) {
  VisitedSet *v = malloc(sizeof(VisitedSet));
  v->count = 0;
  return v;
}

static bool visited_contains(VisitedSet *v, const int *board) {
  for (int i = 0; i < v->count; i++) {
    if (memcmp(v->states[i]->board, board, 9 * sizeof(int)) == 0)
      return true;
  }
  return false;
}

static void visited_add(VisitedSet *v, State *state) {
  if (v->count < 181440)
    v->states[v->count++] = state;
}

static void visited_free(VisitedSet *v, State *solution) {
  if (v) {
    for (int i = 0; i < v->count; i++) {
      State *s = v->states[i];
      bool in_solution = false;
      for (State *c = solution; c != NULL; c = c->parent) {
        if (c == s) {
          in_solution = true;
          break;
        }
      }
      if (!in_solution)
        state_free(s);
    }
    free(v);
  }
}

static void generate_moves(State *current, Queue *q, VisitedSet *visited) {
  int empty = find_empty(current->board);

  int moves[4][2] = {
      {-3, 'U'}, // up
      {3, 'D'},  // down
      {-1, 'L'}, // left
      {1, 'R'}   // right
  };

  int valid[4] = {
      empty >= 3,     // up: not in top row
      empty <= 5,     // down: not in bottom row
      empty % 3 != 0, // left: not in left column
      empty % 3 != 2  // right: not in right column
  };

  for (int i = 0; i < 4; i++) {
    if (valid[i]) {
      int new_board[9];
      memcpy(new_board, current->board, 9 * sizeof(int));
      new_board[empty] = new_board[empty + moves[i][0]];
      new_board[empty + moves[i][0]] = 0;

      if (!visited_contains(visited, new_board)) {
        State *new_state = state_create(new_board, current, moves[i][1]);
        queue_insert(q, (Data)new_state);
        visited_add(visited, new_state);
      }
    }
  }
}

State *solve_puzzle(int *initial_board) {
  if (state_is_goal(initial_board))
    return state_create(initial_board, NULL, ' ');

  Queue *q = queue_create(NULL);
  VisitedSet *visited = visited_create();

  State *initial = state_create(initial_board, NULL, ' ');
  queue_insert(q, (Data)initial);
  visited_add(visited, initial);

  State *solution = NULL;
  while (!queue_empty(q)) {
    State *current = (State *)queue_get(q);
    queue_remove(q);

    if (state_is_goal(current->board)) {
      solution = current;
      while (!queue_empty(q))
        queue_remove(q);
      break;
    }

    generate_moves(current, q, visited);
  }

  visited_free(visited, solution);
  queue_delete(q);
  return solution;
}
