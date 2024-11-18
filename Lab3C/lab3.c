#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

#define GOAL_STATE "123456780"

typedef struct Pair
{
    char* child;
    struct Pair* parent;
} Pair;

void pair_destructor(void* pair);
void print_node(char* node);
void get_children(Pair* node, Queue* queue, List* visited);
void bfs(char* start_state,char* goal_state);
bool compare(char* state, char* goal_state);
bool find_state(List* visited, char* state);
void print_path(Pair* node);

int main(int argc, char **argv) {
    FILE *input = fopen(argv[1], "r");
    char* start_state = malloc(10);
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
    while (node->child[zero_index] != '0') zero_index++;
    int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int new_zero_index;
    int x = zero_index % 3;
    int y = zero_index / 3;
    for (int i = 0; i < 4; i++) {
        int new_x = x + moves[i][0];
        int new_y = y + moves[i][1];
        if ((0 <= new_x && new_x < 3) && (0 <= new_y && new_y < 3)) {
            char* children = (char*)malloc(10);
            new_zero_index = new_y * 3 + new_x;
            for (int j = 0; j < 10; j++) 
                children[j] = (node->child)[j];
            children[zero_index] = (node->child)[new_zero_index];
            children[new_zero_index] = '0';
            if (!find_state(visited, children)) {
                Pair* pair = malloc(sizeof(Pair));
                pair->child = children;
                pair->parent = node;
                queue_insert(queue, pair);
                list_insert(visited, pair);
            } else free(children); 
        }
    }
}

void bfs(char* start_state,char* goal_state) {
    Queue* queue = queue_create(NULL);
    List* visited = list_create(pair_destructor);
    Pair* pair = malloc(sizeof(Pair));
    pair->child = start_state;
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
    while (current) {
        if (compare(((Pair*)list_item_data(current))->child, state)) {
            result = true;
            current = NULL;
        } else current = list_item_next(current);  
    }
    return result;
}

void pair_destructor(void* pair) {
    free(((Pair*)pair)->child);
    free(pair);
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
