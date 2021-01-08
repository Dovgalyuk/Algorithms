#ifndef INTERFACE_H
#define INTERFACE_H
-finput-charset=cp866 -fexec-charset=utf-8
#include <vector>
#include "list.h"

using namespace std;

//1. ÈÍÒÅÐÔÅÉÑ
class Interface {
private:
	vector <unsigned int> vertexList;				
	vector <List*> adjacencyList;					
	vector <unsigned int> labelVertex;			

public:
	Interface() {}								
	virtual ~Interface() {}						

	//Ôóíêöèè
	virtual unsigned int sizeGraph() = 0;
	virtual int posVertex(unsigned int vertex) = 0;	
	virtual unsigned int vertexGraph(unsigned int) = 0;	
	virtual void printGraph() {};										
	virtual void addVertex(unsigned int) = 0;;										
	virtual void removeVertex(unsigned int) = 0;;										
	virtual void addEdge(unsigned int, unsigned int, unsigned int) = 0;			
	virtual void removeEdge(unsigned int, unsigned int) = 0;									
	virtual void existEdge(unsigned int, unsigned int) = 0;										
	virtual void addLabelVertex() {};									
	virtual unsigned int readLabelVertex(unsigned int) = 0;				
	virtual void addLabelEdge() {};										
	virtual unsigned int readLabelEdge(unsigned int, unsigned int) = 0;	
	virtual ListItem* neighborsVertex(unsigned int, ListItem*) = 0;
};

#endif
