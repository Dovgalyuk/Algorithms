#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "list.h"

template <typename Data>
class Graph
{
public:
    // Структура, представляющая ребро
    struct Edge 
    {
        int from;
        int to;// Вершина, куда ведет ребро
        Data weight;// Вес ребра

        Edge(int from, int to, Data weight) : from(from), to(to), weight(weight) {}
    };

    // Конструктор графа с указанием количества вершин
    Graph(int vertexCount) : vertexCount_(vertexCount) 
    {
        adjacencyList_ = new List<Edge>[vertexCount_];
        vertexData_ = new Data[vertexCount_]; // Инициализация массива данных вершин
    }

    // Конструктор копирования
    Graph(Graph& other) : vertexCount_(other.vertexCount_) 
    {
        adjacencyList_ = new List<Edge>[vertexCount_];
        for (int i = 0; i < vertexCount_; i++) 
        {
            adjacencyList_[i] = other.adjacencyList_[i];
        }
    }

    // Оператор присваивания
    Graph& operator=(Graph& other) 
    {
        if (this != &other) 
        {
            delete[] adjacencyList_;
            vertexCount_ = other.vertexCount_;
            adjacencyList_ = new List<Edge>[vertexCount_];
            for (int i = 0; i < vertexCount_; i++) 
            {
                adjacencyList_[i] = other.adjacencyList_[i];
            }
        }
        return *this;
    }

    // Деструктор
    ~Graph() 
    {
        delete[] adjacencyList_;
        delete[] vertexData_;
    }

    // Метод для получения списка смежности вершины
    List<Edge>& adjacencyList(int vertex) 
    {
        return adjacencyList_[vertex];
    }

    // Добавить новую вершину в граф
    void addVertex() 
    {
        List<Edge>* newAdjacencyList = new List<Edge>[vertexCount_ + 1];
        for (int i = 0; i < vertexCount_; i++) 
        {
            newAdjacencyList[i] = adjacencyList_[i];
        }
        delete[] adjacencyList_;
        adjacencyList_ = newAdjacencyList;
        vertexCount_++;
    }

    // Добавить ребро между вершинами
    void addEdge(int from, int to, Data weight) 
    {
        if (from >= 0 && from < vertexCount_ && to >= 0 && to < vertexCount_) 
        {
            adjacencyList_[from].insert(Edge(from, to, weight));
        }
    }

    // Удалить вершину из графа
    void removeVertex(int vertex)
    {
        if (vertex < 0 || vertex >= vertexCount_)
            return;

        List<Edge>* newAdjacencyList = new List<Edge>[vertexCount_ - 1];

        for (int i = 0, j = 0; i < vertexCount_; i++)
        {
            if (i != vertex)
            {
                newAdjacencyList[j] = adjacencyList_[i];

                // Удаляем все ребра, ведущие к удаляемой вершине
                auto item = newAdjacencyList[j].first();
                typename List<Edge>::Item* prevItem = nullptr;
                while (item != nullptr)
                {
                    if (item->data().to == vertex)
                    {
                        if (prevItem == nullptr)
                        {
                            item = newAdjacencyList[j].erase_first();
                        }
                        else
                        {
                            item = newAdjacencyList[j].erase_next(prevItem);
                        }
                    }
                    else
                    {
                        prevItem = item;
                        item = item->next();
                    }
                }

                j++;
            }
        }

        delete[] adjacencyList_;
        adjacencyList_ = newAdjacencyList;
        --vertexCount_;
    }


    // Удалить ребро из графа
    void removeEdge(int from, int to) {
        if (from < 0 || from >= vertexCount_) return;
        typename List<Edge>::Item* prevItem = nullptr;
        for (auto item = adjacencyList_[from].first(); item != nullptr; item = item->next()) {
            if (item->data().to == to) 
            {
                if (prevItem == nullptr) 
                {// Если удаляемый элемент первый в списке
                    adjacencyList_[from].erase_first();
                }
                else 
                {
                    adjacencyList_[from].erase_next(prevItem); // Удаляем элемент, следующий за prevItem
                }
                break;
            }
            prevItem = item;
        }
    }

    // Проверить существование ребра
    bool hasEdge(int from, int to)
    {
        if (from < 0 || from >= vertexCount_)
            return false;
        for (auto item = adjacencyList_[from].first(); item != nullptr; item = item->next()) 
        {
            if (item->data().to == to) 
            {
                return true;
            }
        }
        return false;
    }

    void setEdgeData(int from, int to, Data data) 
    {
        if (from < 0 || from >= vertexCount_)
            return;
        typename List<Edge>::Item* prev = nullptr;
        for (auto item = adjacencyList_[from].first(); item != nullptr; item = item->next())
        {
            if (item->data().to == to) 
            {
                if (prev == nullptr) 
                {
                    adjacencyList_[from].erase_first();
                }
                else 
                {
                    adjacencyList_[from].erase_next(prev);
                }
                adjacencyList_[from].insert_after(prev, Edge(from, to, data)); // Используйте конструктор Edge
                break;
            }
            prev = item;
        }
    }


    // Получить пометку ребра
    Data getEdgeData(int from, int to)
    {
        if (from < 0 || from >= vertexCount_) 
            return Data();
        for (auto item = adjacencyList_[from].first(); item != nullptr; item = item->next()) 
        {
            if (item->data().to == to) 
            {
                return item->data().weight;
            }
        }
        return Data(); // Возвращаем пустой Data, если ребро не найдено
    }

    // Задать пометку для вершины
    void setVertexData(int vertex, Data data) 
    {
        if (vertex >= 0 && vertex < vertexCount_) 
        {
            vertexData_[vertex] = data;
        }
    }

    // Получить пометку вершины
    Data getVertexData(int vertex)
    {
        if (vertex >= 0 && vertex < vertexCount_) 
        {
            return vertexData_[vertex];
        }
        return Data(); // Возвращаем пустой Data, если вершина не найдена
    }

    int vertexCount()
    {
        return vertexCount_;
    }
    
    // Класс итератора для перебора соседей вершины
    class NeighborIterator
    {
    public:
        // Конструктор
        NeighborIterator(Graph* graph, int vertex): graph_(graph), vertex_(vertex), currentItem_(nullptr) 
        {
            if (vertex >= 0 && vertex < graph->vertexCount_) 
            {
                currentItem_ = graph->adjacencyList_[vertex].head();
            }
        }

        // Перейти к следующему соседу
        void next() 
        {
            if (currentItem_ != nullptr) 
            {
                currentItem_ = currentItem_->next();
            }
        }

        // Проверить, есть ли следующий сосед
        bool hasNext() 
        {
            return currentItem_ != nullptr;
        }

        // Получить данные текущего соседа
        Data current() 
        {
            if (currentItem_ != nullptr) 
            {
                return currentItem_->data().weight;
            }
            return Data(); // Возвращаем пустой Data, если нет текущего элемента
        }

    private:
        // Указатель на граф
        Graph* graph_;

        // Текущая вершина
        int vertex_;

        // Текущий элемент списка соседей
        typename List<Edge>::Item* currentItem_;
    };

private:
    // Массив списков смежно сти для каждой вершины
    List<Edge>* adjacencyList_;
    int vertexCount_;
    Data* vertexData_;
    // Вспомогательные функции (если требуется)
};

#endif
