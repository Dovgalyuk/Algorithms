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
	vertices()
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
		
		auto uSuccessors = u.getEdges();

        if(uSuccessors.first() == nullptr){
            u.getEdges().insert(edge);
            return true;
        }

        for(auto item = uSuccessors.first(); item != nullptr; item = item->getNext()){
            if(item->getData() == edge){
                return false;
            }else{
                u.getEdges().insert(item->getData());
                return true;
            }
        }
		return false;
}


List<Graph::Edge*> Graph::GetEdges(Graph::Vertex& u){
    return u.getEdges();
}


bool Graph::RemoveVertex(Vertex& u) {
	if (vertices.find(&u) != vertices.end()) {

		vertices.erase(&u);

		for(auto item = u.getEdges().first(); item!=nullptr; item = item->getNext()){
               u.getEdges().erase(item);
        }
		return true;
	}

    return false;

}

bool Graph::RemoveEdge(Vertex& u, Vertex& v) {
	
	for(auto item = u.getEdges().first(); item != nullptr; item = item->getNext()){
        if(item->getData()->GetPointV() == &v){
            u.getEdges().erase(item);
            return true;
        }
    }

    return false;

}

bool Graph::IsEdge(Vertex& u, Vertex& v) {

    for(auto item = u.getEdges().first(); item != nullptr; item = item->getNext()){
        if(item->getData()->GetPointV() == &v){
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

Graph::Vertex* Graph::getVertex(int index){
    return this->GetVertices().at(index);
}

List<Graph::Edge*> Graph::Vertex::getEdges(){
    return edges;
}

std::vector<Graph::Vertex*> Graph::GetSuccessors(Vertex& u) {
	std::vector<Vertex*> suc;

    for(auto item = u.getEdges().first(); item != nullptr; item = item->getNext()){
        suc.push_back(item->getData()->GetPointV());
    }

	return suc;
}
