#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "list.h"

using namespace std;

template <typename Data> class Graph {
public:
	struct Edge {
		int start;
		int end;
		Data weight;
		size_t index = 0;
		Edge() {
			this->start = -1;
			this->end = -1;
			this->weight = -1;
		}
		Edge(int start, int end, Data weight, size_t index) {
			this->start = start;
			this->end = end;
			this->weight = weight;
			this->index = index;
		}
		Data getWeight() {
			return this->weight;
		}
	};

	Graph(size_t amountVertex) {
		vertexAmount = amountVertex;
		edgeAmount = 0;
		vertexes = new Data[vertexAmount];
		for (size_t i = 0; i < vertexAmount; i++) {
			vertexes[i] = static_cast<Data>(i);
		}
	}

	~Graph() {
		delete[] vertexes;
	}

	Graph(const Graph& a) {
		delete[] vertexes;
		vertexAmount = a.vertexAmount;
		vertexes = new Data[vertexAmount];
		for (size_t i = 0; i < vertexAmount; i++) {
			vertexes[i] = a.vertexes[i];
		}

		matrix = a.matrix;
		edgeAmount = a.edgeAmount;
	}

	Graph& operator=(const Graph& a) {
		if (this != &a) {
			delete[] vertexes;
			vertexes = new Data[a.vertexes.size()];
			for (size_t i = 0; i < a.vertexes.size(); i++) {
				vertexes[i] = a.vertexes[i];
			}

			List<Edge> newMatrix;
			for (size_t i = 0; i < edgeAmount; i++) {
				List<Graph<int>::Edge*>::Item* edgeItem = a.matrix[i];
				newMatrix.insert_after(newMatrix.last(), Edge(edgeItem->data()->start, edgeItem->data()->end, edgeItem->data()->weight, edgeItem->data()->index));
			}

			matrix = newMatrix;
		}
		return *this;
	}

	size_t getVertexAmount() {
		return vertexAmount;
	}

	void addVertex(Data vertexData) {
		Data* newVertexes = new Data[vertexAmount+1];
		for (size_t i = 0; i < vertexAmount; i++) {
			newVertexes[i] = vertexes[i];
		}
		newVertexes[vertexAmount] = vertexData;
		delete[] vertexes;
		vertexes = newVertexes;
		vertexAmount += 1;
	}

	void removeVertex(size_t index) {
		if (index >= vertexAmount) {
			return;
		}
		
		List<Edge> newMatrix;
		for (size_t i = 0; i < edgeAmount; i++) {
			newMatrix.insert_after(newMatrix.last(), Edge(matrix[i]->data().start, matrix[i]->data().end, matrix[i]->data().weight, matrix[i]->data().index));
		}
		for (size_t i = 0; i < edgeAmount; i++) {
			matrix.erase_first();
		}
		for (size_t i = 0; i < edgeAmount; i++) {
			typename List<Edge>::Item* edgeItem = newMatrix[i];
			if (edgeItem->data().start!=index || edgeItem->data().end != index) {
				typename List<Edge>::Item* edgeItem = newMatrix[i];
				matrix.insert_after(matrix.last(), Edge(edgeItem->data().start, edgeItem->data().end, edgeItem->data().weight, i));
			}
		}
		edgeAmount -= 1;
		Data* newVertexes = new Data[vertexAmount - 1];
		bool check = true;
		for (size_t i = 0; i < vertexAmount; i++) {
			if (i != index) {
				newVertexes[check == true ? i : i - 1] = vertexes[i];
			}
			else {
				check = false;
			}
		}
		delete[] vertexes;
		vertexAmount -= 1;
		vertexes = newVertexes;
	}

	Data getVertex(size_t index) {
		return vertexes[index];
	}

	Edge getEdge(size_t start, size_t end) {
		for (size_t i = 0; i < edgeAmount; i++) {
			typename List<Edge>::Item* edgeItem = matrix[i];
			if (edgeItem->data().start == start && edgeItem->data().end == end) {
				return Edge(edgeItem->data().start, edgeItem->data().end, edgeItem->data().weight, edgeItem->data().index);
			}
		}
		return Edge(-1,-1,-1,-1);
	}

	bool isEdgeExist(size_t start, size_t end) {
		Edge edge = getEdge(start, end);
		return edge.index !=-1;
	}

	void addEdge(size_t start, size_t end, Data edgeData) {
		if (!isEdgeExist(start, end)) {
			matrix.insert_after(matrix.last(), Edge(start, end, edgeData, edgeAmount));
			edgeAmount++;
		}
		else {
			Edge edge = getEdge(start, end);
			List<Edge> newMatrix;
			for (size_t i = 0; i < edgeAmount;i++) {
				newMatrix.insert_after(newMatrix.last(), Edge(matrix[i]->data().start, matrix[i]->data().end, matrix[i]->data().weight, matrix[i]->data().index));
			}
			for (size_t i = 0; i < edgeAmount; i++) {
				matrix.erase_first();
			}
			for (size_t i = 0; i < edgeAmount; i++) {
				if (i == edge.index) {
					matrix.insert_after(matrix.last(), Edge(start, end, edgeData, i));
				}
				else {
					typename List<Edge>::Item* edgeItem = newMatrix[i];
					matrix.insert_after(matrix.last(), Edge(edgeItem->data().start, edgeItem->data().end, edgeItem->data().weight, i));
				}
			}
		}
	}

	void removeEdge(size_t start, size_t end) {
		if (isEdgeExist(start, end)) {
			Edge edge = getEdge(start, end);
			List<Edge> newMatrix;
			for (size_t i = 0; i < edgeAmount; i++) {
				newMatrix.insert_after(newMatrix.last(), Edge(matrix[i]->data().start, matrix[i]->data().end, matrix[i]->data().weight, matrix[i]->data().index));
			}
			for (size_t i = 0; i < edgeAmount; i++) {
				matrix.erase_first();
			}
			for (size_t i = 0; i < edgeAmount; i++) {
				if (i!=edge.index){
					typename List<Edge>::Item* edgeItem = newMatrix[i];
					matrix.insert_after(matrix.last(), Edge(edgeItem->data().start, edgeItem->data().end, edgeItem->data().weight, i));
				}
			}
			edgeAmount -= 1;
		}
		else {
			return;
		}
	}

	struct Iterator {
	private:
		Graph* graph;
		size_t start;
		int end = -1;

		int getNearVertex() {
			for (size_t i = end + 1; i < graph->getVertexAmount(); i++) {
				if (graph->isEdgeExist(start, i)) {
					return static_cast<int>(i);
				}
			}
			return -1;
		}
	public:
		Iterator(Graph* graph, size_t start) {
			this->graph = graph;
			this->start = start;
			this->end = getNearVertex();
		}

		bool operator *() {
			if (end != -1) {
				return true;
			}
			else {
				return false;
			}
		}

		void operator ++() {
			end = getNearVertex();
		}

		size_t getEnd() const {
			return end;
		}

		size_t getStart() const {
			return start;
		}
	};

	Iterator getIterator(size_t start) {
		return Iterator(this, start);
	}
private:
	List<Edge> matrix;
	size_t edgeAmount;
	size_t vertexAmount;
	Data* vertexes;
};

#endif