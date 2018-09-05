#ifndef ORGRAPH_H_
#define ORGRAPH_H_


struct OrGraph;

OrGraph *create_orghraph(int vertices);
void delete_orgraph(OrGraph *orgraph);
int orgraph_add_vertex(OrGraph *orgraph);
void orgraph_del_vertex(OrGraph *orgraph, int index);
void orgraph_add_edge(OrGraph *orgraph, int indexFrom, int indexTo);
void orgraph_del_edge(OrGraph *orgraph, int indexFrom, int indexTo);
bool orgraph_edge_exist(OrGraph *orgraph, int indexFrom, int indexTo);
void orgraph_set_edge_weight(OrGraph *orgraph, int indexFrom, int indexTo,
		unsigned short weight);
int orgraph_get_edge_weight(OrGraph *orgraph, int indexFrom, int indexTo);
void orgraph_set_vertex_label(OrGraph *orgraph, int index, int label);
int orgraph_get_vertex_label(OrGraph *orgraph, int index);


#endif
