#ifndef GRAPH_H
#define GRAPH_H

#pragma once

#include "list.h"
#include <cstdio>
#include <iostream>

using namespace std;

//typedef int Data;
template <typename Data>
class Graph {
public:
	
	Graph(size_t size, Data data = NULL) {
		for (int i = 0; i < size; i++)
		{
			this->addVertex(data);
		}
		this->sizeOfVertexes = size;
	}

	size_t getSize() {
		return this->sizeOfVertexes;
	}

	struct Edge;

	struct Vertex { //Структура вершины. Имеет данные, которые хранятся в вершине, список ребер и количество ребер.

		Vertex(Data data) {
			this->data = data;
			this->countOfEdges = 0;
		}

		~Vertex() {
			auto toDelete = listOfEdges.first();
			auto toDeleteNext = toDelete->getNext();
			while (toDelete) {
				delete toDelete;
				toDelete = toDeleteNext;
				if (toDelete->getNext() == nullptr) toDeleteNext = nullptr;
				else toDeleteNext = toDeleteNext->getNext();
			}
		}

		void setData(Data data) {
			this->data = data;
		}
		Data getData() {
			return this->data;
		}

		size_t getSize() {
			return this->countOfEdges;
		}

		Edge* getEdge(Vertex* toVertex) {
			if (isEdgeExist(toVertex)) {
				auto toFind = this->listOfEdges.first();
				while (toFind) {
					if (toFind->data.getDirection() == toVertex) {
						return &toFind->data;
					}
					toFind = toFind->getNext();
				}
			}
			else {
				cout << "Edge doesn't exist";
				return nullptr;
			}
		}

		void addEdge(Vertex* toVertex, size_t weight = NULL) {
			if (!this->listOfEdges.isListEmpty()) this->listOfEdges.insert_after(this->listOfEdges.last(), Edge(toVertex, weight));
			else this->listOfEdges.insert(Edge(toVertex, weight));
			this->countOfEdges++;
		}
		void deleteEdge(Vertex* toVertex) {
			auto toDelete = this->listOfEdges.first();
			while (toDelete) {
				if (toDelete->data.getDirection() == toVertex) {
					listOfEdges.erase(toDelete);
					this->countOfEdges--;
					break;
				}
				toDelete = toDelete->getNext();
			}
		}

		bool isEdgeExist(Vertex* toVertex) {
			auto toFind = this->listOfEdges.first();
			while (toFind) {
				if (toFind->data.getDirection() == toVertex) return true;
				toFind = toFind->getNext();
			}
			return false;
		}
		
		List <Edge> listOfEdges;
	private: 
		Data data;
		size_t countOfEdges;
		
	};

	struct Edge { //Структура ребра, имеет вес и направление.

		Edge(Vertex* vertex=nullptr, size_t weight = NULL) {
			this->direction = vertex;
			this->weight = weight;
		}

		void setWeight(size_t weight) {
			this->weight = weight;
		}
		size_t getWeight() {
			return this->weight;
		}

		Vertex* getDirection() {
			return this->direction;
		}

	private:
		size_t weight; //Вес ребра
		Vertex* direction; //Указатель на вершину, куда идет ребро
	};

	void addVertex(Data data) {
		if (this->isGraphEmpty()) listOfVertexes.insert(new Vertex(data));
		else listOfVertexes.insert_after(listOfVertexes.last(), new Vertex(data));
	}
	void deleteVertex(Vertex* toDelete) {
		if (!isGraphEmpty()) {
			auto toFind = listOfVertexes.first();
			while (toFind) {
				if (toFind->data->getData() == toDelete->getData()) {
					listOfVertexes.erase(toFind);
					this->sizeOfVertexes--;
					return;
				}
				toFind = toFind->getNext();
			}
			cout << "This vertex is missing here";
		}
		else cout << "Graph is empty!";
	}
	void setVertexData(Vertex* vertex, Data data) {
		vertex->setData(data);
	}
	Data getVertexData(Vertex* vertex) {
		return vertex->getData();
	}
	Vertex* getFirstElementOfList() {
		return this->listOfVertexes.first()->data;
	}

	void addEdgeBetween(Vertex* vertex, Vertex* toVertex, size_t weight=NULL) {
		if (vertex != nullptr && toVertex != nullptr) {
			vertex->addEdge(toVertex, weight);
		}
		else cout << "You have typed wrong vertexes";
	}
	void deleteEdgeBetween(Vertex* vertex, Vertex* toVertex) {
		if (isEdgeExistBetween(vertex, toVertex)) vertex->deleteEdge(toVertex);
		else cout << "Graph isn't have edge between " << vertex->getData() << " and " << toVertex->getData();
		
	}
	bool isEdgeExistBetween(Vertex* vertex, Vertex* toVertex) {
		if (!this->isGraphEmpty()) return vertex->isEdgeExist(toVertex);
		else {
			cout << "\n Graph is empty!";
			return false;
		}
	}
	void setEdgeWeight(Vertex* vertex, Vertex* toVertex, size_t weight) {
		if (isEdgeExistBetween(vertex, toVertex)) {
			vertex->getEdge(toVertex)->setWeight(weight);
		}
		else cout << "Edge doesn't exist";
	}
	size_t getEdgeWeight(Vertex* vertex, Vertex* toVertex) {
		if (isEdgeExistBetween(vertex, toVertex)) {
			return vertex->getEdge(toVertex)->getWeight();
		}
		else cout << "Edge doesn't exist";
	}

	bool isGraphEmpty() {
		if (this->sizeOfVertexes == 0) return true;
		else return false;
	}

	struct edgeIterator
	{
		typename List<Edge>::Item* edgeIter;

		edgeIterator(Vertex* vertex) {
			this->edgeIter = vertex->listOfEdges.first();
		}

		void operator++() {
			if (edgeIter) edgeIter = edgeIter->getNext();
		}

		void iteratorBegin(Vertex* vertex) {
			this->edgeIter = vertex->listOfEdges.first();
		}

		Edge* operator*() {
			if (edgeIter != nullptr) {
				return &edgeIter->data;
			}
			else return nullptr;
		}
	};

	struct vertexIterator
	{
		typename List<Vertex*>::Item* vertexIter;

		vertexIterator(Graph* graph) {
			this->vertexIter =  graph->listOfVertexes.first();
		}

		void operator++() {
			if (vertexIter) vertexIter = vertexIter->getNext();
		}

		void iteratorBegin(Graph* graph) {
			this->vertexIter = graph->listOfVertexes.first();
		}

		Vertex* operator*() {
			if (vertexIter !=nullptr) return &*vertexIter->data;
			else return nullptr;
		}
	};

private:
	List<Vertex*> listOfVertexes;
	size_t sizeOfVertexes;
};


#endif
