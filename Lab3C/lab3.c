#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include "vector.h"
#include "queue.h"

#define INF 1e9

typedef struct {
    int x, y, value, paths_count;
} Point;

void my_delete(void* d){
    free((Point*)d);
}

void get_file_string_size(FILE* file, size_t* c, size_t* r) {
    size_t columns = 0;
    size_t rows = 0;
    size_t current_columns = 0;
    int ch;

    // Сounting characters
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            if (rows == 0) {
                columns = current_columns;
            }
            rows++;
            current_columns = 0;
        } else if (ch != '\r') { // Ignoring Windows migration
            current_columns++;
        }
    }

    // Processing last line if it doesn't end with \n
    if (current_columns > 0) {
        if (rows == 0) columns = current_columns;
        rows++;
    }

    rewind(file);
    *c = columns;
    *r = rows;
}

char** maze_read(FILE* file, int* start_y, int* start_x, size_t* len_y, size_t* len_x) {
    if (file == NULL) return NULL;
    
    size_t cols = 0;
    size_t rows = 0;

    // Получаем размеры (функция должна корректно делать rewind)
    get_file_string_size(file, &cols, &rows);
    
    // Выделяем память под массив указателей на строки
    char** maze = (char**)malloc(rows * sizeof(char*));
    if (maze == NULL) return NULL;

    for (size_t i = 0; i < rows; i++) {
        maze[i] = (char*)malloc((cols + 1) * sizeof(char));
        
        size_t j = 0;
        while (j < cols) {
            int c = fgetc(file);
            if (c == EOF) break;
            
            // Игнорируем символы переноса строки при чтении данных строки
            if (c == '\n' || c == '\r') continue;

            maze[i][j] = (char)c;
            
            if (c == 'Q') {
                *start_x = (int)j;
                *start_y = (int)i;                
            }
            j++;
        }
        maze[i][cols] = '\0'; // Завершаем строку
    }

    *len_x = cols;
    *len_y = rows;
        
    return maze;
}

size_t bfs_for_maze(char** maze, const Point start, const size_t len_y, const size_t len_x) {
    Vector* dist = vector_create(my_delete);
    if (dist == NULL)
        return 0;
    
    vector_resize(dist, len_y * len_x); 
    Queue* q = queue_create(NULL);      // Queue doen't clear memory, dist does it

    size_t min_steps_to_E = ULONG_MAX; 
    size_t shortest_paths_to_E = 0;

    // Start point initialization
    Point* start_node = (Point*)malloc(sizeof(Point));
    start_node->x = start.x;
    start_node->y = start.y;
    start_node->value = 0;
    start_node->paths_count = 1;
    vector_set(dist, start.y * len_x + start.x, start_node);
    queue_insert(q, start_node);

    while(!queue_empty(q)) {
        Point* current = (Point*)queue_get(q);
        queue_remove(q);

        // If path is shorter than current, skip
        if (current->value >= min_steps_to_E) continue;

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;

                // Stepping
                for (int step = 1; ; step++) {
                    int ny = current->y + dy * step;
                    int nx = current->x + dx * step;

                    // Checking boundaries
                    if (ny < 0 || ny >= (int)len_y || nx < 0 || nx >= (int)len_x) break;
                    
                    // Сhecking wall
                    if (maze[ny][nx] == '#') break;

                    size_t new_dist = current->value + 1;

                    // 'E' foundet
                    if (maze[ny][nx] == 'E') {
                        if (new_dist < min_steps_to_E) {
                            min_steps_to_E = new_dist;
                            shortest_paths_to_E = current->paths_count;
                        } else if (new_dist == min_steps_to_E) {
                            shortest_paths_to_E += current->paths_count;
                        }
                        // Not steppint any further
                        break; 
                    }

                    size_t idx = (size_t)ny * len_x + (size_t)nx;
                    // Next step
                    Data d = vector_get(dist, idx);

                    // Not visited
                    if (d == VECTOR_EMPTY) {
                        Point* next = (Point*)malloc(sizeof(Point));
                        next->x = nx;
                        next->y = ny;
                        next->value = new_dist;
                        next->paths_count = current->paths_count;
                        vector_set(dist, idx, next);
                        queue_insert(q, next);
                    }
                    
                    // Visited, update paths count
                    else {
                        Point* existing = (Point*)d;
                        if (existing->value == new_dist) {
                            existing->paths_count += current->paths_count;
                        }
                    }
                }
            }
        }
    }

    queue_delete(q);
    vector_delete(dist); 

    return shortest_paths_to_E;
}


int main(int argc, char** argv) 
{
    // Reading maze from file with find E position 
    FILE* maze_file = fopen(argv[1], "r");
    Point start;
    size_t len_y, len_x;
    size_t last_layer_size;
    char** maze = maze_read(maze_file, &start.y, &start.x, &len_y, &len_x);

    // Count number of shortest paths and print result
    size_t shortest_paths = bfs_for_maze(maze, start, len_y, len_x);
    printf("%lu", shortest_paths);
    if (shortest_paths == 0) {
        printf(", There are no paths.");
    }

    // Freeing memory
    for(size_t i = 0; i < len_y; i++) {
        free(maze[i]);
    }
    free(maze);
    fclose(maze_file);
    return 0;
}