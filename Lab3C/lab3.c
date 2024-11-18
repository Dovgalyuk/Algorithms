#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

#define GOAL_STATE "123456780"

typedef struct Pair
{
    char child[10];
    struct Pair* parent;
} Pair;

void print_node(char* node);
void get_children(Pair* node, Queue* queue, List* visited);
void bfs(char* start_state,char* goal_state);
bool compare(char* state, char* goal_state);
bool find_state(List* visited, char* state);
void print_path(Pair* node);
void copy_node(char* buf, char* src);

int main(int argc, char **argv) {
    FILE *input = fopen(argv[1], "r");
    char start_state[10];
    fgets(start_state, 10, input);
    fclose(input);
    bfs(start_state, GOAL_STATE);
    return 0;
}

void print_node(char* node) {
    for (int i = 0; i < 9; i++) {
        printf("%c", (node[i]));
    }
    printf("\n");
}

void get_children(Pair* node, Queue* queue, List* visited) {
    int zero_index = 0;
    char children[10];
    while ((node->child)[zero_index] != '0') zero_index++;
    int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int new_zero_index;
    int x = zero_index % 3;
    int y = zero_index / 3;
    for (int i = 0; i < 4; i++) {
        int new_x = x + moves[i][0];
        int new_y = y + moves[i][1];
        if ((0 <= new_x && new_x < 3) && (0 <= new_y && new_y < 3)) {
            new_zero_index = new_y * 3 + new_x;
            copy_node(children, node->child);
            children[zero_index] = (node->child)[new_zero_index];
            children[new_zero_index] = '0';
            if (!find_state(visited, children)) {
                Pair* pair = malloc(sizeof(Pair));
                copy_node(pair->child, children);
                pair->parent = node;
                queue_insert(queue, pair);
                list_insert(visited, pair);
            }
        }
    }
}

void bfs(char* start_state,char* goal_state) {
    Queue* queue = queue_create(NULL);
    List* visited = list_create(free);
    Pair* pair = malloc(sizeof(Pair));
    copy_node(pair->child, start_state);
    pair->parent = NULL;
    list_insert(visited, pair);
    queue_insert(queue, pair);
    while (!queue_empty(queue)) {
        Pair* current_node = queue_get(queue);
        if (compare(current_node->child, goal_state)) {
            print_path(current_node);
            break;
        } else {
            get_children(current_node, queue, visited);
        }
        queue_remove(queue);
        if (queue_empty(queue)) {
            printf("EMPTY!\n");
        }
    }
    queue_delete(queue);
    list_delete(visited);
}

bool compare(char* state, char* goal_state) {
    bool result = true;
    for (int i = 0; i < 9; i++)
        if (state[i] != goal_state[i]) {
            result = false;
            i = 9;
        }
    return result;
}

bool find_state(List* visited, char* state) {
    bool result = false;
    ListItem* current = list_first(visited);
    ListItem* finish = current;
    do {
        if (compare(((Pair*)list_item_data(current))->child, state))
            result = true;
        else
            current = list_item_next(current);  
    } while (!result && current != finish);
    return result;
}

void print_path(Pair* node) {
    Stack* stack = stack_create(NULL, NULL);
    while (node) {
        stack_push(stack, node->child);
        node = node->parent;
    }
    while (!stack_empty(stack)) {
        print_node(stack_get(stack));
        stack_pop(stack);
    }
    stack_delete(stack);
}

void copy_node(char* buf, char* src) {
    for (int i = 0; i < 10; i++)
        buf[i] = src[i];
}
