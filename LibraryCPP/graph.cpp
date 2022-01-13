#include <iostream>
#include "graph.h"

Graph::Vertex::Vertex(size_t id, int data) {
	this->id = id;
	this->data = data;
}

size_t Graph::Vertex::GetId() {
	return id;
}

int Graph::Vertex::GetData() {
	return data;
}

void Graph::Vertex::SetData(int data) {
	this->data = data;
};

int Graph::Edge::GetWeight() {
	return weight;
}


void Graph::Edge::SetWeight(int weight) {
	this->weight = weight;
}


Graph::Graph() :
	vertexCounter(0),
	vertices(),
	edges()
{};

Graph::Vertex* Graph::AddVertex(const int data) {
	auto vertex = std::make_unique<Vertex>(vertexCounter, data);
	vertexCounter++;
	auto* const rawPointer = vertex.get();
	vertices.emplace(rawPointer, std::move(vertex));
	return rawPointer;
};

void Graph::Edge::SetPointV(Vertex& v) {
	this->v->SetData(v.GetData());
}

void Graph::Edge::SetId(Vertex& v){
    this->id = v.GetId();
}

size_t Graph::Edge::GetId(){
    return id;
}

Graph::Vertex* Graph::Edge::GetPointV() {
	return v;
}

bool Graph::AddEdge(Vertex& u, Vertex& v, int weight) {
		
		Edge* edge = new Edge();
		edge->SetPointV(v);
        edge->SetId(v);
		edge->SetWeight(weight);
		
		auto& uSuccessors = edges[&u];
		
		if (uSuccessors.find(edge) == uSuccessors.end()) {
            uSuccessors.emplace(edge);
            return true;
		} else {
            return false;
		}
}

std::vector<Graph::Edge*> Graph::GetEdges(Graph::Vertex& u){
    std::vector<Graph::Edge*> uedges;
    uedges.reserve(3);
    auto& uEdges = edges[&u];
    for(auto& item: uEdges){
        uedges.push_back(item);
    }
    return uedges;
}


bool Graph::RemoveVertex(Vertex& u) {
	if (vertices.find(&u) != vertices.end()) {

		auto& uSuccessors = edges[&u];		

		vertices.erase(&u);

		edges.erase(&u);
		
		for (auto& pair : uSuccessors) {
			auto& successors = pair;
			uSuccessors.clear();
		}
		return true;
	} else {
		return false;
	}
}

bool Graph::RemoveEdge(Vertex& u, Vertex& v) {
	
	if (vertices.find(&u) != vertices.end() && vertices.find(&v) != vertices.end()) {
		auto& uSuccessors = edges[&u];
		for (auto& pair : uSuccessors) {
			auto& successors = pair;
			if(successors->GetId() == v.GetId()){
                uSuccessors.erase(successors);
                return true;
            }
		}
	} else {
		return false;
	}
}

bool Graph::IsEdge(Vertex& u, Vertex& v) {
	auto& uSuccessors = edges[&u];

	for (auto& pair : uSuccessors) {
		if (pair->GetId() == v.GetId()) {
			return true;
		}
	}
    return false;
}

std::vector<Graph::Vertex*> Graph::GetVertices() {
	std::vector<Vertex*> copy_vertices;
	copy_vertices.reserve(vertices.size());
	for (auto& pair : vertices) {
		copy_vertices.push_back(pair.first);
	}
	return copy_vertices;
};

std::vector<Graph::Vertex*> Graph::GetSuccessors(Vertex& u) {
	std::vector<Vertex*> suc;

	auto& uSuccessors = edges[&u];
	for (auto& pair : uSuccessors) {
		auto& successors = pair;
		suc.push_back(successors->GetPointV());
	}

	return suc;
}
