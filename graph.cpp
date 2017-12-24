//
//  graph.cpp
//  Graph
//
//  Created by Marcos Vicente on 18.12.2017.
//  Copyright © 2017 Marcos Vicente. All rights reserved.
//

#include "graph.hpp"
#include <iostream>

using namespace std;

class vertex{
public:
    vertex *next; //ponteiro no vértice seguinte
    edge *adj; //ponteiro para o vértice "begin" da a aresta (Esta aresta vai servir como conexão entre dois vértices)
    int label; //nome do vértice
    
    friend class graph;
};

class edge{
public:
    edge *next; //ponteiro para a aresta seguinte
    vertex *adj; //ponteiro para o vértice "dest" da aresta
    int weight; //peso da aresta
    friend class graph;
};

void graph::createGraph()
{
    first = NULL;
    countEdges = 0;
}

bool graph::emptyGraph()
{
    if (first == NULL)
        return true;
    else
        return false;
}

int graph::sizeGraph()
{
    int cont = 0;
    vertex *aux;
    aux = first; //variável auxiliar funciona como um ponteiro para a lista de vértices (vai indicar cada vértice)
    
    while (aux != NULL){
        cont++;
        aux = aux->next; //o auxiliar percorre a lista de vértices até encontrar um cujo campo next seja NULL
    }
    return cont; //Mostra o tamanho do grafo
}

vertex *graph::getVertex(int label)
{
    vertex *aux;
    aux = first;
    
    while (aux != NULL)
    {
        if (aux->label == label)
            return aux;
        aux = aux->next;
    }
    return NULL;
}

bool graph::checkVertex(int label)
{
    vertex *aux;
    aux = first;
    
    while (aux != NULL)
    {
        if (aux->label == label)
        {
            cout << "\nСуществует вершину!\n" << endl;
            return true;
        }else{
            cout << "\nНе существует вершину!\n" << endl;
        }
        aux = aux->next;
        return false;
    }
    return false;
}

void graph::insertVertex(int label)
{
    vertex *newVertex = new vertex;
    newVertex->label = label;
    newVertex->next = NULL;
    newVertex->adj = NULL;
    
    if (emptyGraph())
    {
        first = newVertex;
    }else{
        vertex *aux;
        aux = first;
        
        while (aux->next != NULL) //funciona como um iterador, vai percorrer os vértices até chegar ao último (se já existir pelo menos um)
        {
            aux = aux->next;
        }
        aux->next = newVertex;
    }
}

bool graph::insertWeight(vertex *orig, vertex *dest, int weight)
{
    edge *actual;
    actual = orig->adj;
    
    if (actual->adj == dest)
    {
        actual->weight = weight;
        return true;
    }else{
        return false;
    }
}

void graph::insertEdge(vertex *orig, vertex *dest, int weight)
{
    edge *newEdge = new edge;
    newEdge->weight = weight;
    newEdge->next = NULL;
    newEdge->adj = NULL;
    countEdges = countEdges + 1;
    
    edge *aux;
    
    aux = orig->adj; // recebe o vértice origem
    
    if (aux == NULL) // Se o vértice estiver vazio
    {
        orig->adj = newEdge; //liga a aresta ao vértice origem
        newEdge->adj = dest; //liga a aresta ao vértice destino
    }else{
        while (aux->next != NULL) // funciona como um iterador, vai percorrer as arestas até chegar a última (se já existir pelo menos uma)
        {
            aux = aux->next;
        }
        aux->next = newEdge; //aqui adiciona a nova aresta conectando-a ao vértice begin (dentro da lista das arestas)
        newEdge->adj = dest; // aqui conecta a mesma aresta ao vértice destino
     }
}

void graph::adjList()
{
    vertex *vertAux;
    edge *edgeAux;
    
    vertAux = first; // posicionado no primeiro vértice
    
    while (vertAux != NULL) //percorre todos os outros vértices
    {
        cout << vertAux->label << " : "; //mostra o vértice que está a ser recorrido
        
        edgeAux = vertAux->adj; // posicionando o auxiliar das arestas no primeiro vértice
        while (edgeAux != NULL) // percorrendo as outras arestas desse vértice
        {
            cout << edgeAux->adj->label << " ->"; //mostra o nome do vértice origem que está a ser percorrido
            edgeAux = edgeAux->next;
        }
        vertAux = vertAux->next;
        cout << endl; //pulamos a linha
    }
    cout << "\n";
}

void graph::free()
{
    vertex *aux;
    
    while (first != NULL)
    {
        aux = first; //posiciona o aux no vértice actual (first)
        first = first->next; // first vai para o seguinte vértice
        delete (aux); // remove o vértice anterior onde estava o aux
    } // e assim  se repetirá até o grafo ficar vazio
}

//função adicionada por mim para verificar se existe ou não uma aresta entre os vértices
bool graph::checkEdge(vertex *orig, vertex *dest)
{
    edge *actual;
    actual = orig->adj;
    
    while (actual != NULL)
    {
        if (actual->adj == dest)
        {
            cout << "\nСуществует ребро между вершинами!" << endl;
            return true;
        }
        else
        {
            cout << "\nНе существует ребро между вершинами!" << endl;
        }
        actual = actual->next;
        return false;
    }
    return false;
}


int graph::getWeight(vertex *orig, vertex *dest)
{
    edge *actual;
    int w = 0;
    
    actual = orig->adj;
    
    while (actual != NULL)
    {
        if (actual->adj == dest)
        {
            w = actual->weight;
        }
        actual = actual->next;
    }
    return w;
}

void graph::removeEdge(vertex *orig, vertex *dest)
{
    int flag = 0;
    edge *actual, *prev = 0; //auxiliares
    
    actual = orig->adj; //posiciona o actual no vértice origem
    
    if (countEdges > 0)
        countEdges = countEdges - 1;
    
    if(actual == NULL)
    {
        cout << "\nNo edges in the origin vertex!\n" << endl;
    }else if(actual->adj == dest)
    {
        orig->adj = actual->next; //liga o vértice origem a aresta que está a seguir
        delete(actual); //elimina a aresta
    }else{
        while (actual != NULL)
        {
            if (actual->adj == dest)
            {
                flag = 1;
                prev->next = actual->next;
                delete (actual);
                break;
            }
            prev = actual;
            actual = actual->next;
        }
        if (flag == 0)
            cout << "\nЗаданные вершиные не связанны!" << endl;
    }
    countEdges = countEdges - 1;
}

void graph::removeVertex(vertex *insVertex)
{
    vertex *actual, *prev = 0;
    edge *aux;
    
    actual = first;
    
    while(actual != NULL)
    {
        aux = actual->adj;
        while (aux != NULL)
        {
            if (aux->adj == insVertex)
            {
                removeEdge(actual, aux->adj);
                break;
            }
            aux = aux->next;
        }
        actual = actual->next;
    }
    
    actual = first;
    if (first == insVertex)
    {
        first = first->next;
        delete (actual);
    }else{
        while (actual != insVertex)
        {
            prev = actual;
            actual = actual->next;
        }
        prev->next = actual->next;
        delete (actual);
    }
}
