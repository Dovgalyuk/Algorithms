#ifndef ORGRAPH_H
#define ORGRAPH_H



struct Graph;
// создание пустого графа
Graph * graph_create();

Graph * graph_create(int key);

// удаление графа
void  graph_delete(Graph * graph);


// включение ребра в граф
void  graph_insert_reb(Graph * graph, int num1, int num2, int weight);


// удаление ребра из графа
void graph_remove_reb(Graph * graph, int num1, int num2);

// размер графа
int graph_size(Graph * graph);

//включение вершины в граф
void graph_insert_ver(Graph * graph, int data);

//удаление вершины из графа 
void graph_remove_ver(Graph *graph, int num);

//проверить, существует ли ребро между вершинами
bool graph_is_valid_rebro(Graph *graph, int ver1, int ver2);

//пометка для ребра 
void graph_pometka_ver(Graph *graph, int ver, int data);

// пометка для вершины
void graph_pometka_reb(Graph *graph, int rebx, int reby, int data);

int graph_get_ver(Graph *graph, int vernum);


int graph_get_reb(Graph *graph, int rebx, int reby);


void show_graph(Graph *graph);


#endif