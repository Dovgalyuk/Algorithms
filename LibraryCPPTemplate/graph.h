#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Data>
class Graph {
public:
    Graph(size_t vertex_amount, Data vertex_data) {
        vertexes = new Vector<Vertex*>;
        // Заполнение вершинами
        vertexes->resize(vertex_amount);
        for (size_t i = 0; i < vertex_amount; i++) {
            vertexes->set(i, new Vertex(vertex_data));
        }
        // Создание матрицы смежности
        edgeMatrix = new Vector<Edge*>;
        edgeMatrix->resize(vertex_amount * vertex_amount);

        for (size_t i = 0; i < edgeMatrix->size(); i++) {
            edgeMatrix->set(i, nullptr);
        }

    }
    ~Graph() {
        for (size_t i = 0; i < vertexes->size(); i++) {
            delete vertexes->get(i);
        }
        for (size_t i = 0; i < edgeMatrix->size(); i++) {
            delete edgeMatrix->get(i);
        }
        delete vertexes;
        delete edgeMatrix;
    }
    Graph(const Graph& other) {
        vertexes = nullptr;
        edgeMatrix = nullptr;
        *this = other;
    }

    Graph& operator=(const Graph& other) {
        if (this == &other) {
            return *this;  // Проверка на самоприсваивание - важно для предотвращения удаления объекта самим собой
        }

        // Очистка памяти текущего графа перед копированием
        if (vertexes) {
            for (size_t i = 0; i < vertexes->size(); i++) {
                delete vertexes->get(i);  // Удаление каждой вершины вектора вершин
            }
            delete vertexes;  // Удаление вектора вершин
        }

        if (edgeMatrix) {
            for (size_t i = 0; i < edgeMatrix->size(); i++) {
                delete edgeMatrix->get(i);  // Удаление каждого ребра в матрице смежности
            }
            delete edgeMatrix;  // Удаление матрицы смежности
        }

        // Создание нового вектора вершин для глубокого копирования
        vertexes = new Vector<Vertex*>;
        vertexes->resize(other.vertexes->size());  // Ресайзинг вектора под размер вектора другого графа
        for (size_t i = 0; i < other.vertexes->size(); ++i) {
            vertexes->set(i, new Vertex(*(other.vertexes->get(i))));  // Копирование данных каждой вершины
        }

        // Создание новой матрицы смежности для глубокого копирования
        edgeMatrix = new Vector<Edge*>;
        edgeMatrix->resize(other.edgeMatrix->size());  // Ресайзинг матрицы под размер матрицы другого графа
        for (size_t i = 0; i < other.edgeMatrix->size(); ++i) {
            Edge* edge = other.edgeMatrix->get(i);
            if (edge) {
                edgeMatrix->set(i, new Edge(*(edge)));  // Копирование данных каждого ребра, если оно существует
            }
            else {
                edgeMatrix->set(i, nullptr);  // Установка nullptr, если ребра не существует
            }
        }

        return *this;  // Возврат ссылки на текущий объект для возможности цепочки присваиваний
    }
    struct Vertex {
    private:
        Data vertex_data;
    public:
        Vertex(Data vertex_data) {
            this->vertex_data = vertex_data;
        }
        void setVertexData(Data data) {
            this->vertex_data = data;
        }
        Data getVertexData() {
            return vertex_data;
        }
    };

    struct Edge {
    private:
        Data edge_data;
    public:
        Edge(Data data) {
            this->edge_data = data;
        }
        void setEdgeData(Data data) {
            this->edge_data = data;
        }
        Data getEdgeData() {
            return edge_data;
        }
    };

    size_t getVertexAmount() {
        return vertexes->size();
    }

    // Вложенная структура Iterator для обхода вершин графа, смежных с заданной начальной вершиной
    struct Iterator {
    private:
        Graph* graph;  // Указатель на граф, по которому будет производиться итерация
        size_t start;  // Индекс начальной вершины для итерации
        int end = -1;  // Индекс следующей смежной вершины. Инициализируется как -1, что означает конец итерации

        // Вспомогательный метод для поиска индекса ближайшей вершины, смежной с текущей
        int getNearVertexIndex() {
            // Итерация начинается с позиции следующей за последней найденной смежной вершиной
            for (size_t i = end + 1; i < graph->getVertexAmount(); i++) {
                // Если между начальной и проверяемой вершиной есть ребро, возвращаем её индекс
                if (graph->isEdgeExist(start, i)) {
                    return static_cast<int>(i);
                }
            }
            return -1;  // Если смежных вершин больше нет, возвращаем -1
        }
    public:
        // Конструктор итератора
        Iterator(Graph* graph, size_t start) {
            this->graph = graph;  // Установка указателя на граф
            this->start = start;  // Установка начальной вершины для итерации
            this->end = getNearVertexIndex();  // Поиск первой смежной вершины
        }

        // Оператор разыменования для получения текущей смежной вершины
        Vertex* operator *() {
            if (end != -1) {
                // Если индекс смежной вершины действителен, возвращаем указатель на эту вершину
                return graph->getVertex(end);
            }
            else {
                // Если смежных вершин нет, возвращаем nullptr
                return nullptr;
            }
        }

        // Префиксный оператор инкремента для перехода к следующей смежной вершине
        void operator ++() {
            end = getNearVertexIndex();  // Обновление индекса смежной вершины
        }

        // Метод для получения индекса текущей смежной вершины
        size_t getEnd() const {
            return end;
        }
    };

    Iterator getIterator(size_t start) {
        return Iterator(this, start);
    }
    size_t addVertex(Data vertex_data) {
        // Получение текущего количества вершин в графе для определения индекса новой вершины
        size_t index = vertexes->size();
        // Расширение вектора вершин для включения новой вершины
        vertexes->resize(index + 1);
        // Создание новой вершины с данными `vertex_data` и помещение её в вектор вершин на новый индекс
        vertexes->set(index, new Vertex(vertex_data));

        // Получение обновлённого количества вершин после добавления новой
        size_t vertex_amount = getVertexAmount();

        // Создание временной матрицы смежности для включения новой вершины
        Vector<Edge*>* buffMatrix = new Vector<Edge*>;
        // Установка размера новой матрицы смежности, исходя из нового количества вершин
        buffMatrix->resize(vertex_amount * vertex_amount);
        for (size_t i = 0; i < vertex_amount; i++) {
            for (size_t j = 0; j < vertex_amount; j++) {
                // Копирование существующих рёбер в новую матрицу смежности
                // Индекс для получения ребра из старой матрицы смежности обновляется для учёта новой вершины
                buffMatrix->set((i * vertex_amount) + j, edgeMatrix->get(i * index + j));
            }
        }
        // Удаление старых рёбер из исходной матрицы смежности
        for (size_t i = 0; i < edgeMatrix->size(); i++) {
            if (edgeMatrix->get(i)) {
                delete edgeMatrix->get(i);
            }
        }
        // Освобождение памяти, занимаемой старой матрицей смежности
        delete edgeMatrix;
        // Установка новой матрицы смежности в качестве текущей для графа
        edgeMatrix = buffMatrix;
        // Возвращение индекса, на который была добавлена новая вершина
        return index;
    }
    void removeVertex(size_t index) {
        // Получение текущего количества вершин в графе
        size_t _vertex_amount = getVertexAmount();

        // Если указанный индекс выходит за пределы количества вершин, выходим из функции
        if (index >= _vertex_amount) {
            return;
        }

        // Удаление вершины из вектора вершин
        Vertex* vertex = vertexes->get(index);
        delete vertex; // Освобождение памяти, занятой удалённой вершиной

        // Сдвиг вершин в векторе вершин на одну позицию назад
        // для заполнения "дыры" после удалённой вершины
        for (size_t i = index; i < _vertex_amount - 1; i++) {
            vertexes->set(i, vertexes->get(i + 1));
        }
        vertexes->resize(_vertex_amount - 1); // Уменьшение размера вектора вершин

        // Удаление всех рёбер, инцидентных удалённой вершине
        for (size_t i = 0; i < _vertex_amount; i++) {
            Edge* edge1 = edgeMatrix->get(index * _vertex_amount + i);
            Edge* edge2 = edgeMatrix->get(i * _vertex_amount + index);
            if (edge1) {
                delete edge1; // Удаление ребра, ведущего к удалённой вершине
            }
            if (edge2) {
                delete edge2; // Удаление ребра, исходящего из удалённой вершины
            }
        }

        // После удаления вершины обновляем количество вершин для новой матрицы смежности
        size_t vertex_amount = getVertexAmount();

        // Создание новой матрицы смежности для отражения изменённого размера графа
        Vector<Edge*>* buffMatrix = new Vector<Edge*>;
        buffMatrix->resize(vertex_amount * vertex_amount);
        for (size_t i = 0; i < vertex_amount; i++) {
            for (size_t j = 0; j < vertex_amount; j++) {
                // Копирование рёбер из старой матрицы смежности в новую,
                // исключая удалённые рёбра
                // Получение ребра из старой матрицы смежности с учётом смещения после удаления вершины.
                // Если текущие индексы строки (i) или столбца (j) больше или равны индексу удалённой вершины,
                // необходимо учесть смещение в старой матрице, чтобы скопировать соответствующие рёбра.
                Edge* edge = edgeMatrix->get(((i + (i >= index)) * _vertex_amount) + (j + (j >= index)));
                buffMatrix->set((i * vertex_amount) + j, edge);
            }
        }

        // Освобождение памяти, занятой старой матрицей смежности
        delete edgeMatrix;
        // Установка новой матрицы смежности как текущей матрицы графа
        edgeMatrix = buffMatrix;
    }
    Vertex* getVertex(size_t index) {
        return vertexes->get(index);
    }

    void addEdge(size_t start_vertex_index, size_t end_vertex_index, Data edge_data) {
        // Получение общего количества вершин в графе для расчета индексов в матрице смежности
        size_t vertex_amount = getVertexAmount();

        // Попытка получить существующее ребро из матрицы смежности по индексам начальной и конечной вершин
        Edge* existingEdge = edgeMatrix->get(start_vertex_index * vertex_amount + end_vertex_index);

        if (existingEdge) {
            // Если ребро между указанными вершинами уже существует,
            // обновляем его данные с новым значением `edge_data`
            existingEdge->setEdgeData(edge_data);
        }
        else {
            // Если ребро между вершинами отсутствует,
            // создаем новое ребро с данными `edge_data`
            Edge* newEdge = new Edge(edge_data);
            // Добавляем новое ребро в матрицу смежности на позицию, соответствующую индексам вершин
            edgeMatrix->set(start_vertex_index * vertex_amount + end_vertex_index, newEdge);
        }
    }

    void removeEdge(size_t start_vertex_index, size_t end_vertex_index) {
        size_t vertex_amount = getVertexAmount();
        Edge* edge = edgeMatrix->get(start_vertex_index * vertex_amount + end_vertex_index);
        delete edge;  // Освобождение памяти для ребра
        edgeMatrix->set(start_vertex_index * vertex_amount + end_vertex_index, nullptr);
    }

    Edge* getEdge(size_t start_vertex_index, size_t end_vertex_index) {
        size_t vertex_amount = getVertexAmount();
        return edgeMatrix->get(start_vertex_index * vertex_amount + end_vertex_index);
    }

    bool isEdgeExist(size_t start_vertex_index, size_t end_vertex_index) {
        return getEdge(start_vertex_index, end_vertex_index) != nullptr;
    }
private:
    Vector<Vertex*>* vertexes; //вершины
    Vector<Edge*>* edgeMatrix; //матрица смежности
};

#endif