#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include "list.h"

using namespace std;

//1. ÈÍÒÅÐÔÅÉÑ
class Interface {
private:
	vector <unsigned int> vertexList;				//Ñïèñîê âåðøèí ãðàôà
	vector <List*> adjacencyList;					//Ñïèñîê ñìåæíîñòè
	vector <unsigned int> labelVertex;				//Ìåòêà âåðøèí

public:
	Interface() {}									//Êîíñòðóêòîð
	virtual ~Interface() {}							//Äåñòðóêòîð 

	//Ôóíêöèè
	virtual unsigned int sizeGraph() = 0;
	virtual int posVertex(unsigned int vertex) = 0;	
	virtual unsigned int vertexGraph(unsigned int) = 0;	
	virtual void printGraph() {};										//Âûâîä ãðàôà
	virtual void addVertex() {};										//Äîáàâèòü âåðøèíó
	virtual void removeVertex() {};										//Óäàëèòü âåðøèíó
	virtual void addEdge() {};											//Äîáàâèòü ðåáðî
	virtual void removeEdge() {};										//Óäàëèòü ðåáðî
	virtual void existEdge() {};										//Ïðîâåðêà íà ñóùåñòâîâàíèå ðåáðà
	virtual void addLabelVertex() {};									//Çàäàòü ìåòêó âåðøèíå
	virtual unsigned int readLabelVertex(unsigned int) = 0;				//Ñ÷èòàòü ìåòêó âåðøèíû
	virtual void addLabelEdge() {};										//Çàäàòü ìåòêó ðåáðó
	virtual unsigned int readLabelEdge(unsigned int, unsigned int) = 0;	//Ñ÷èòàòü ìåòêó ðåáðà
	virtual ListItem* neighborsVertex(unsigned int, ListItem*) = 0;
};

#endif
