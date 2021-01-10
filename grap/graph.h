#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "interface.h"

class Graph :public Interface {
private:
	vector <unsigned int> vertexList;			
	vector <List*> adjacencyList;				
	vector <unsigned int> labelVertex;			
	public:
	//Êîíñòðóêòîð
	Graph() {}
	//Äåñòðóêòîð
	virtual ~Graph() {}

	//Ôóíêöèè
	virtual unsigned int sizeGraph();
	virtual int posVertex(unsigned int vertex);																
	virtual unsigned int vertexGraph(unsigned int);	//Ðàçìåð ãðàôà
	virtual void printGraph();																
	virtual void addVertex(unsigned int vertex);													
	virtual void removeVertex(unsigned int vertex);											
	virtual void addEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge);		
	virtual void removeEdge(unsigned int firstVertex, unsigned int secondVertex);							
	virtual void existEdge(unsigned int firstVertex, unsigned int secondVertex);							
	virtual void addLabelVertex(unsigned int vertex, unsigned int valueVertex);								
	virtual unsigned int readLabelVertex(unsigned int vertex);									
	virtual void addLabelEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge);		
	virtual unsigned int readLabelEdge(unsigned int firstVertex, unsigned int secondVertex);
	virtual List<ListItem>::Iterator firstNeighborVertex(unsigned int vertex);
};

#endif
