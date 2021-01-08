#ifndef INTERFACE_H
#define INTERFACE_H
-finput-charset=cp866 -fexec-charset=utf-8
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
	virtual void addVertex(unsigned int) = 0;;										//Äîáàâèòü âåðøèíó
	virtual void removeVertex(unsigned int) = 0;;										//Óäàëèòü âåðøèíó
	virtual void addEdge(unsigned int, unsigned int, unsigned int) = 0;											//Äîáàâèòü ðåáðî
	virtual void removeEdge(unsigned int, unsigned int) = 0;										//Óäàëèòü ðåáðî
	virtual void existEdge(unsigned int, unsigned int) = 0;										//Ïðîâåðêà íà ñóùåñòâîâàíèå ðåáðà
	virtual void addLabelVertex() {};									//Çàäàòü ìåòêó âåðøèíå
	virtual unsigned int readLabelVertex(unsigned int) = 0;				//Ñ÷èòàòü ìåòêó âåðøèíû
	virtual void addLabelEdge() {};										//Çàäàòü ìåòêó ðåáðó
	virtual unsigned int readLabelEdge(unsigned int, unsigned int) = 0;	//Ñ÷èòàòü ìåòêó ðåáðà
	virtual ListItem* neighborsVertex(unsigned int, ListItem*) = 0;
};

#endif
