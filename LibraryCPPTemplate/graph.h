#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Data>
class Graph {
public:
	//���������
	//��������� ������
	struct Vertex {
	private:
		Data vertexData;
	public:
		Vertex(Data vertexData) {
			this->vertexData = vertexData;
		}
		void setVertexData(Data vertexData) {
			this->vertexData = vertexData;
		}
		Data getVertexData() {
			return this->vertexData;
		}
	};
	//��������� �����
	struct Edge {
	private:
		Data edgeData;
	public:
		Edge(Data data) {
			this->edgeData = data;
		}
		void setEdgeData(Data data) {
			this->edgeData = data;
		}
		Data getEdgeData() {
			return edgeData;
		}
	};
	//����������� �����
	Graph(size_t vertexAmount) {
		vertexes = new Vector<Vertex*>;
		vertexes->resize(vertexAmount);
		for (size_t i = 0; i < vertexAmount; i++) {
			vertexes->set(i, new Vertex(static_cast<int>(i)));
		}
		edgeMatrix = new Vector<Edge*>;
		edgeMatrix->resize(vertexAmount * vertexAmount);
		for (size_t i = 0; i < edgeMatrix->size(); i++) {
			edgeMatrix->set(i, nullptr);
		}
	}
	//����������
	~Graph() {
		//������� ������� ��� ��������� � �������
		for (size_t i = 0; i < vertexes->size(); i++) {
			delete vertexes->get(i);
		}
		delete vertexes;//������� ������

		for (size_t i = 0; i < edgeMatrix->size(); i++) {
			delete edgeMatrix->get(i);
		}
		delete edgeMatrix;
	}

	//����������� �����������
	Graph(const Graph& a) {
		vertexes = nullptr;
		edgeMatrix = nullptr;
		*this = a;
	}

	Graph& operator=(const Graph& a) {
		if (this != &a) {
			if (vertexes) {
				for (size_t i = 0; i < vertexes->size(); i++) {
					delete vertexes->get(i);
				}
				delete vertexes;//������� ������
			}
			if (edgeMatrix) {
				for (size_t i = 0; i < edgeMatrix->size(); i++) {
					delete edgeMatrix->get(i);
				}
				delete edgeMatrix;
			}

			vertexes = new Vector<Vertex*>;
			vertexes->resize(a.vertexes->size());
			for (size_t i = 0; i < vertexes->size(); i++) {
				vertexes->set(i, new Vertex(*(a.vertexes->get(i))));
			}

			edgeMatrix = new Vector<Edge*>;
			edgeMatrix->resize(a.edgeMatrix->size());
			for (size_t i = 0; i < edgeMatrix->size(); i++) {
				Edge* edge = a.edgeMatrix->get(i);
				edgeMatrix->set(i, new Edge(*(edge)));  // ����������� ������ ������� �����
			}
		}
		return *this;
	}

	size_t getVertexAmount() {
		return vertexes->size();
	}
	
	size_t addVertex(Data vertexData) {
		size_t index = vertexes->size();
		vertexes->resize(index + 1);
		vertexes->set(index, new Vertex(vertexData));

		size_t vertexAmount = getVertexAmount();
		// �������� ��������� ������� ��������� ��� ��������� ����� �������
		Vector<Edge*>* buffMatrix = new Vector<Edge*>;
		// ��������� ������� ����� ������� ���������, ������ �� ������ ���������� ������
		buffMatrix->resize(vertexAmount * vertexAmount);
		for (size_t i = 0; i < vertexAmount; i++) {
			for (size_t j = 0; j < vertexAmount; j++) {
				// ����������� ������������ ���� � ����� ������� ���������
				// ������ ��� ��������� ����� �� ������ ������� ��������� ����������� ��� ����� ����� �������
				buffMatrix->set((i * vertexAmount) + j, edgeMatrix->get(i * index + j));
			}
		}

		//�������� ������ ����� �� �������
		for (size_t i = 0; i < edgeMatrix->size(); i++) {
			if (edgeMatrix->get(i)) {
				delete edgeMatrix->get(i);
			}
		}
		// ������������ ������, ���������� ������ �������� ���������
		delete edgeMatrix;
		// ��������� ����� ������� ��������� � �������� ������� ��� �����
		edgeMatrix = buffMatrix;
		// ����������� �������, �� ������� ���� ��������� ����� �������
		return index;
	}

	void removeVertex(size_t index) {
		//��������� �������� ���-�� ������
		size_t _vertexAmount = getVertexAmount();

		//���� ��������� ������ ������� �� ������� ���-�� ������, ������� �� �������
		if (index >= _vertexAmount) {
			return;
		}

		//�������� ������� �� ������� ������
		Vertex* vertex = vertexes->get(index);
		delete vertex;

		//����� ������ � ������� ������ �� ���� ������� �����
		for (size_t i = index; i < _vertexAmount - 1; i++) {
			vertexes->set(i, vertexes->get(i + 1));
		}
		vertexes->resize(_vertexAmount - 1); //���������� ������� ������� ������

		//�������� ���� �����, �������������� ��������� �������
		for (size_t i = 0; i < _vertexAmount; i++) {
			Edge* edge = edgeMatrix->get(index * _vertexAmount + i);
			if (edge) {
				delete edge;
			}
			edge = edgeMatrix->get(i * _vertexAmount + index);
			if (edge) {
				delete edge;
			}
		}

		// ����� �������� ������� ��������� ���������� ������ ��� ����� ������� ���������
		size_t vertex_amount = getVertexAmount();
		
		Vector<Edge*>* buffMatrix = new Vector<Edge*>;
		buffMatrix->resize(vertex_amount * vertex_amount);
		for (size_t i = 0; i < vertex_amount; i++) {
			for (size_t j = 0; j < vertex_amount; j++) {
				Edge* edge = edgeMatrix->get(((i + (i >= index)) * _vertexAmount) + (j + (j >= index)));
				buffMatrix->set((i * vertex_amount) + j, edge);
			}
		}
		//�������� ������ �������
		delete edgeMatrix;
		//������������� ����� �������
		edgeMatrix = buffMatrix;
	}

	//��������� �������
	Vertex* getVertex(size_t index) {
		return vertexes->get(index);
	}

	Edge* getEdge(size_t startVertexIndex, size_t endVertexIndex) {
		size_t vertexAmount = getVertexAmount();
		return edgeMatrix->get(startVertexIndex * vertexAmount + endVertexIndex);
	}

	bool isEdgeExist(size_t startVertexIndex, size_t endVertexIndex) {
		return getEdge(startVertexIndex, endVertexIndex) != nullptr;
	}

	void addEdge(size_t startVertexIndex, size_t endVertexIndex, Data edgeData) {
		// ��������� ������ ���������� ������ � ����� ��� ������� �������� � ������� ���������
		size_t vertexAmount = getVertexAmount();

		//������� �������� ����� �� ������� ��������� �� �������� ������ � �����
		Edge* edge = edgeMatrix->get(startVertexIndex * vertexAmount + endVertexIndex);
		if (edge) {
			//���� ����� ���������� ������ ��������� ��� ��������
			edge->setEdgeData(edgeData);
		}
		else {
			//����� ������� ����� �����
			Edge* newEdge = new Edge(edgeData);
			edgeMatrix->set(startVertexIndex * vertexAmount + endVertexIndex, newEdge);
		}
	}

	void removeEdge(size_t startVertexIndex, size_t endVertexIndex) {
		size_t vertexAmount = getVertexAmount();
		Edge* edge = edgeMatrix->get(startVertexIndex * vertexAmount + endVertexIndex);
		delete edge; //������� ������ �����
		edgeMatrix->set(startVertexIndex * vertexAmount + endVertexIndex, nullptr);
	}

	struct Iterator {
	private:
		Graph* graph; // ��������� �� ����, �� �������� ����� ������������� ��������
		size_t start; // ������ ��������� ������� ��� ��������
		//end ��� int, ������ ��� size_t �� ����� ���� ������������� ������
		int end = -1; // ������ ��������� ������� �������. ���������������� ��� -1, ��� �������� ����� ��������
		
	
		//���������� ������� �������
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

		Vertex* operator *() {
			if (end != -1) {
				//���� ���� ������� �������, �� ���������� ������� �������
				return graph->getVertex(end);
			}
			else {
				//����� ������� ���
				return nullptr;
			}
		}
		
		//������� � ��������� ������� �������
		void operator ++() {
			end = getNearVertex(); // ���������� ������� ������� �������
		}

		//��������� ������� ������� ������� �������
		//const ��������, ��� ������ �������� ����������, ������� ���������� ���� �����
		size_t getIndex() const {
			return end;
		}

		int getStart() const {
			return start;
		}
	};

	Iterator getIterator(size_t start) {
		return Iterator(this, start);
	}

private:
	Vector<Vertex*>* vertexes; //�������
	Vector<Edge*>* edgeMatrix; //������� ���������
};

#endif