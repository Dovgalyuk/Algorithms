#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "vector.h"

#define BOARD_SIZE 3
#define BOARD_CELLS (BOARD_SIZE * BOARD_SIZE)

typedef struct {
    int board[BOARD_CELLS];
    int zero_pos;
    int moves;
    char move_history[100];
} State;

void print_board(const int board[BOARD_CELLS]) {
    for (int i = 0; i < BOARD_CELLS; i++) {
        if (i % BOARD_SIZE == 0) printf("\n");
        printf("%d ", board[i]);
    }
    printf("\n");
}

int is_goal(const int board[BOARD_CELLS]) {
    for (int i = 0; i < BOARD_CELLS - 1; i++) {
        if (board[i] != i + 1) return 0;
    }
    return board[BOARD_CELLS - 1] == 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void generate_moves(Queue *queue, State *current) {
    int zero_pos = current -> zero_pos;
    int row = zero_pos / BOARD_SIZE;
    int col = zero_pos % BOARD_SIZE;

    if (row > 0) {
        State *next = (State *)malloc(sizeof(State));
        memcpy(next, current, sizeof(State));
        next -> zero_pos = zero_pos - BOARD_SIZE;
        swap(&next->board[zero_pos], &next -> board[next -> zero_pos]);
        next -> moves++;
        next -> move_history[next->moves - 1] = 'U';
        next -> move_history[next->moves] = '\0';
        queue_insert(queue, next);
    }

    if (row < BOARD_SIZE - 1) {
        State *next = (State *)malloc(sizeof(State));
        memcpy(next, current, sizeof(State));
        next -> zero_pos = zero_pos + BOARD_SIZE;
        swap(&next -> board[zero_pos], &next -> board[next -> zero_pos]);
        next -> moves++;
        next -> move_history[next -> moves - 1] = 'D';
        next -> move_history[next -> moves] = '\0';
        queue_insert(queue, next);
    }

    if (col > 0) {
        State *next = (State *)malloc(sizeof(State));
        memcpy(next, current, sizeof(State));
        next -> zero_pos = zero_pos - 1;
        swap(&next -> board[zero_pos], &next -> board[next -> zero_pos]);
        next -> moves++;
        next -> move_history[next -> moves - 1] = 'L';
        next -> move_history[next -> moves] = '\0';
        queue_insert(queue, next);
    }

    if (col < BOARD_SIZE - 1) {
        State *next = (State *)malloc(sizeof(State));
        memcpy(next, current, sizeof(State));
        next -> zero_pos = zero_pos + 1;
        swap(&next -> board[zero_pos], &next -> board[next -> zero_pos]);
        next -> moves++;
        next -> move_history[next -> moves - 1] = 'R';
        next -> move_history[next -> moves] = '\0';
        queue_insert(queue, next);
    }
}

void solve_puzzle(int initial_board[BOARD_CELLS]) {
    Queue *queue = queue_create(NULL);
    if (queue == NULL) {
        fprintf(stderr, "Не удалось создать очередь\n");
        return;
    }

    State *initial_state = (State *)malloc(sizeof(State));
    initial_state -> moves = 0;
    initial_state -> move_history[0] = '\0';
    memcpy(initial_state->board, initial_board, sizeof(initial_state -> board));
    for (int i = 0; i < BOARD_CELLS; i++) {
        if (initial_state -> board[i] == 0) {
            initial_state -> zero_pos = i;
            break;
        }
    }

    queue_insert(queue, initial_state);

    while (!queue_empty(queue)) {
        State *current = (State *)queue_get(queue);
        if (current == NULL) {
            fprintf(stderr, "Не удалось получить состояние из очереди\n");
            queue_delete(queue);
            return;
        }
        queue_remove(queue);

        if (is_goal(current -> board)) {
            printf("Решение найдено за %d ходов: %s\n", current -> moves, current -> move_history);
            print_board(current -> board);
            free(current);
            queue_delete(queue);
            return;
        }

        generate_moves(queue, current);
        free(current);
    }

    printf("Решение не найдено.\n");
    queue_delete(queue);
}

int read_board_from_file(const char *filename, int board[BOARD_CELLS]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Не удалось открыть файл");
        return 0;
    }

    for (int i = 0; i < BOARD_CELLS; i++) {
        if (fscanf(file, "%d", &board[i]) != 1) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <input_file>\n", argv[0]);
        return 1;
    }

    int initial_board[BOARD_CELLS];
    if (!read_board_from_file(argv[1], initial_board)) {
        fprintf(stderr, "Не удалось прочитать доску из файла %s\n", argv[1]);
        return 1;
    }

    solve_puzzle(initial_board);
    return 0;
}
