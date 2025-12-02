#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "queue.h"

using namespace std;
//псевдонимы типов контейнеров ключ значение 
typedef map<string, size_t> City_Id;// название города - его id
typedef map<size_t, string> Id_City;// id города - его название 
typedef map<size_t, vector<size_t>> Graph;// граф представленный в виде списка смежности
// (вершина - вектор соседних вершин )
City_Id city_id;
Id_City id_city;
size_t next_id = 0; // переменная для хранения следующего доступного id города
// функция получение id города по его названию
size_t Id_get_city(const string& name) {

	if (city_id.count(name) == 0) { // если города нет в мапе

		city_id[name] = next_id; // присваиваем новый id
		id_city[next_id] = name; // сохраняем соответствие id - название города
		next_id++;// обновляем id для следующего города
    }
	return city_id[name];// возвращаем id города
}
//функция поиска пути в графе с помощью поиска в ширину
vector<size_t> search_puti(Graph& graph, size_t start, size_t end) {
	vector<bool> visited(next_id, false); // вектор для отслеживания посещённых вершин
	vector<size_t> parent(next_id, next_id); // вектор для хранения предкав для восстановления пути

	Queue* queue = queue_create(); // создаём очередь для поиска в ширину
	queue_insert(queue, start); // добавляем стартовую вершину в очередь
	visited[start] = true; // отмечаем стартовую вершину как посещённую

	while (!queue_empty(queue)) { // пока очередь не пуста

		size_t vershin = queue_get(queue); // получаем вершину из головы очереди
		queue_remove(queue); // удаляем вершину из очереди

		if (vershin == end) // если достигли конечной вершины 
			break; // выходим из цикла

		for (size_t sosedi : graph[vershin]) { // проходим по соседним вершинам

			if (!visited[sosedi]) { // если соседняя вершина не посещена

				visited[sosedi] = true; // отмечаем её как посещённую
				parent[sosedi] = vershin; // сохраняем предка для восстановления пути
				queue_insert(queue, sosedi);// добавляем в очередь
            }
        }
    }

    queue_delete(queue);// освобождаем очередь 

	if (!visited[end]) { // если конечная вершина не была посещена
		return {}; // возвращаем пустой путь
    }

	vector<size_t> path; // вектор для хранения пути
	for (size_t i = end; i != next_id; i = parent[i]) { // начиная с конечной вершины
		path.push_back(i); // добавляем вершину в путь

		if (i == start) // если достигли стартовой вершины
            break; // выходим из цикла
    }
	reverse(path.begin(), path.end()); // переворачиваем путь чтобы он шёл от старта к концу

	return path; // возвращаем найденный путь
}

int main(int argc, char** argv) {
	(void)argc;

    ifstream file1(argv[1]); // открываем файл
    if (!file1.is_open()){ // проверка что он открыт 
        return 1;
    }

    Graph graph;
	string a, b;// переменные для хранения названий городов
	vector<pair<string, string>> Krai;// вектор для хранения пар городов (рёбра графа)

	while (file1 >> a >> b) {// чтение пар городов из файла
		Krai.push_back({ a, b }); // добавление пары в вектор
    }

    string start_name = Krai.back().first;
	// считываем последнюю пару городов для получения стартового и конечного города
    string end_name = Krai.back().second;
	Krai.pop_back(); // удаляем последнюю пару из вектора

	for (auto& x : Krai) { // проход по всем парам городов

		size_t id_a = Id_get_city(x.first); // получение id первого города в паре
		size_t id_b = Id_get_city(x.second); /// получение id второго города в паре

		graph[id_a].push_back(id_b); // добавление ребра в граф (список смежности)
		graph[id_b].push_back(id_a);
	}


	size_t start = Id_get_city(start_name); // получение id стартового и конечного города
	size_t end = Id_get_city(end_name);

	vector<size_t> path = search_puti(graph, start, end); // поиск пути в графе

	if (path.empty()) { // если путь не найден
        cout << "No path";
    }
    else {
		for (size_t i = 0; i < path.size(); i++) { // вывод найденного пути

            cout << id_city[path[i]];
            if (i + 1 < path.size())
                cout << " ";
        }
    }

	file1.close(); // закрываем файл
    return 0; // завершаем программу 
}
