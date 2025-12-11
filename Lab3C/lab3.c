#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
#include "queue.h"

void my_delete(void* d){
    free(d);
}

void get_file_string_size(FILE* file, size_t* c, size_t* r) {
    // Counting columns
    size_t columns = 0;
    int ch;
    for (ch = fgetc(file); ch != '\n' && ch != EOF; ch = fgetc(file)) {
        columns++;
    }
    rewind(file);

    // Counting rows
    size_t rows = 0;
    char* buf = malloc((columns+2)*sizeof(char));
    char* tmp = fgets(buf, columns+2, file);
    for (; tmp != NULL; tmp = fgets(buf, columns+2, file)) {
        rows++;
    }
    rewind(file);
    free(buf);

    *c = columns;
    *r = rows;
}

char** maze_read(FILE* file, int* start_x, int* start_y) {
    if(file == NULL) 
        return NULL;
    
    size_t cols = 0;
    size_t rows = 0;

    get_file_string_size(file, &cols, &rows);
    
    // Read maze and find E
    char** maze = malloc(rows * sizeof(char*));
    for (size_t i = 0; i < rows; i++) {
        maze[i] = (char*)malloc((cols+1)*sizeof(char));
        int c;
        for (size_t j = 0; j < cols; j++) {
            c = fgetc(file); 
            maze[i][j] = c;
            
            if (c == 'E'){
                *start_x = j;
                *start_y = i;                
            }
            
        }
        maze[i][cols] = '\0';
        c = fgetc(file);                // read remaining '\n'
    }
        
    return maze;
}


int** breadth_first_traversal(char** maze, int start_x, int stzrt_y) {
    Queue* q = queue_create(my_delete);

    queue_delete(q);
}

void Dijkstra_algorithm(int** graph) {

}

int Shortest_paths_counter(int** graph) {
    Dijkstra_algorithm(graph);
}

int main(int argc, char** argv) 
{
    // Reading maze from file with find E position 
    FILE* maze_file = fopen(argv[1], "r");
    int x,y;
    char** maze = maze_read(maze_file, &x, &y);

    // Making an adjacency list
    int** adjacency_list = breadth_first_traversal(maze, x, y);

    // Count number of shortest paths and print result
    size_t shortest_paths = Shortest_paths_counter(adjacency_list);
    printf("%lu", shortest_paths);

    fclose(maze_file);
    return 0;
}