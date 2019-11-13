#ifndef GRAPHS_H
#define GRAPHS_H
struct Graph;

Graph *graph_create(int num);

void graph_delete(Graph* graph);

void add_vertex(Graph* graph);

void add_edge(Graph* graph, int f_v, int s_v);

void delete_vertex(Graph* graph);

void delete_edge(Graph* graph, int f_v, int s_v);

bool check_edge(Graph* graph, int f_v, int s_v);

void add_mark_vertex(Graph* graph, int num, int mark);

int read_mark_vertex(Graph* graph, int num);

void add_mark_edge(Graph* graph, int f_v, int s_v, int mark);

int read_mark_edge(Graph* graph, int f_v, int s_v);

#endif