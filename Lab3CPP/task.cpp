#include <fstream>
#include <string>
#include "queue.h"
#include "vector.h"

using namespace std;

int nameIndex(string* cityNames, int& count, const string& city) {
    for (int i = 0; i < count; i++) {
        if (cityNames[i] == city) return i;
    }
    cityNames[count] = city;
    count++;
    return count - 1;
}

int BFS(Queue* queue, Vector** neighbors, Vector* dist, Vector* parent, Vector* dist2, int lvl) {
    int meet_city = -1;

    while (!queue_empty(queue) &&
           meet_city < 0 &&
           vector_get(dist, queue_get(queue)) == lvl)
    {
        int cur_city = queue_get(queue);
        queue_remove(queue);
        size_t neighbor_count = vector_size(neighbors[cur_city]);

        for (size_t i = 0; i < neighbor_count && meet_city < 0; i++) {
            int next_city = vector_get(neighbors[cur_city], i);

            if (vector_get(dist, next_city) != -1) continue;
            vector_set(dist, next_city, lvl + 1);
            vector_set(parent, next_city, cur_city);
            queue_insert(queue, next_city);

            if (vector_get(dist2, next_city) != -1) meet_city = next_city;
        }
    }
    return meet_city;
}


int main(int argc, char* argv[])
{
    if (argc < 3) return 1;
    ifstream fin(argv[1]);
    if (!fin.is_open()) return 1;
    ofstream fout(argv[2]);
    if (!fout.is_open()) return 1;

    int count_roads;
    fin >> count_roads;

    int* roadA = new int[count_roads];
    int* roadB = new int[count_roads];
    string* names = new string[count_roads * 2 + 2]; // + 2 для дорог старт и финиш

    int c_names = 0;

    for (int i = 0; i < count_roads; i++) {
        string a, b;
        fin >> a >> b;
        roadA[i] = nameIndex(names, c_names, a);
        roadB[i] = nameIndex(names, c_names, b);
    }

    string start_city, end_city;
    fin >> start_city >> end_city;

    int start = nameIndex(names, c_names, start_city);
    int finish = nameIndex(names, c_names, end_city);

    if (start == finish) {
        fout << start_city << '\n';
        delete[] roadA;
        delete[] roadB;
        delete[] names;
        return 0;
    }
    Vector** neighbors = new Vector*[c_names];
    for (int i = 0; i < c_names; i++) {
        neighbors[i] = vector_create();
    }
    for (int i = 0; i < count_roads; i++) {
        int a = roadA[i];
        int b = roadB[i];

        size_t c_neighbors = vector_size(neighbors[a]);
        vector_resize(neighbors[a], c_neighbors + 1);
        vector_set(neighbors[a], c_neighbors, b);

        c_neighbors = vector_size(neighbors[b]);
        vector_resize(neighbors[b], c_neighbors + 1);
        vector_set(neighbors[b], c_neighbors, a);
    }

    Vector* dist_forw = vector_create();
    Vector* dist_back = vector_create();
    Vector* p_forw = vector_create();
    Vector* p_back = vector_create();
    vector_resize(dist_forw, c_names);
    vector_resize(dist_back, c_names);
    vector_resize(p_forw, c_names);
    vector_resize(p_back, c_names);

    for (int i = 0; i < c_names; i++) {
        vector_set(dist_forw, i, -1);
        vector_set(dist_back, i, -1);
        vector_set(p_forw, i, -1);
        vector_set(p_back, i, -1);
    }
    Queue* q_forw = queue_create();
    Queue* q_back = queue_create();
    vector_set(dist_forw, start, 0);
    vector_set(dist_back, finish, 0);
    queue_insert(q_forw, start);
    queue_insert(q_back, finish);

    int meet_city = -1;

    while (!queue_empty(q_forw) && !queue_empty(q_back) && meet_city < 0) {
        int lvl = vector_get(dist_forw, queue_get(q_forw));
        meet_city = BFS(q_forw, neighbors, dist_forw, p_forw, dist_back, lvl);

        if (meet_city >= 0 || queue_empty(q_forw) || queue_empty(q_back)) break;

        lvl = vector_get(dist_back, queue_get(q_back));
        meet_city = BFS(q_back, neighbors, dist_back, p_back, dist_forw, lvl);
    }
    if (meet_city < 0) {
        fout << "No path" << '\n';
    } else {
        int* full_roads = new int[c_names];
        int full_size = 0;

        for (int current = meet_city; current != -1; current = vector_get(p_forw, current)) {
            full_roads[full_size] = current;
            full_size++;
            if (current == start) break;
        }

        for (int i = 0; i < full_size / 2; i++) {
            int temp = full_roads[i];
            full_roads[i] = full_roads[full_size - 1 - i];
            full_roads[full_size - 1 - i] = temp;
        }

        for (int current = meet_city; current != finish; ) {
            current = vector_get(p_back, current);
            full_roads[full_size] = current;
            full_size++;
        }

        for (int i = 0; i < full_size; i++) {
            fout << names[full_roads[i]] << '\n';
        }
        delete[] full_roads;
    }

    for (int i = 0; i < c_names; i++) {
        vector_delete(neighbors[i]);
    }
    
    delete[] neighbors;
    vector_delete(dist_forw);
    vector_delete(dist_back);
    vector_delete(p_forw);
    vector_delete(p_back);
    queue_delete(q_forw);
    queue_delete(q_back);
    delete[] roadA;
    delete[] roadB;
    delete[] names;
    return 0;
}