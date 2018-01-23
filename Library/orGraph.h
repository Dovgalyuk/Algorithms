#ifndef ORGRAPH_H
#define ORGRAPH_H



struct Graph;
// �������� ������� �����
Graph * graph_create();

Graph * graph_create(int key);

// �������� �����
void  graph_delete(Graph * graph);


// ��������� ����� � ����
void  graph_insert_reb(Graph * graph, int num1, int num2, int weight);


// �������� ����� �� �����
void graph_remove_reb(Graph * graph, int num1, int num2);

// ������ �����
int graph_size(Graph * graph);

//��������� ������� � ����
void graph_insert_ver(Graph * graph, int data);

//�������� ������� �� ����� 
void graph_remove_ver(Graph *graph, int num);

//���������, ���������� �� ����� ����� ���������
bool graph_is_valid_rebro(Graph *graph, int ver1, int ver2);

//������� ��� ����� 
void graph_pometka_ver(Graph *graph, int ver, int data);

// ������� ��� �������
void graph_pometka_reb(Graph *graph, int rebx, int reby, int data);

int graph_get_ver(Graph *graph, int vernum);


int graph_get_reb(Graph *graph, int rebx, int reby);


void show_graph(Graph *graph);


#endif