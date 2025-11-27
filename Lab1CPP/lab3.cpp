#include<iostream>
#include<fstream>
#include"queue.h"
#include "list.h"
#include"myvector.h"
using namespace std;

int main(int argc, char** argv) {

    if (argc < 2) {
        cerr << "ispolzuem chasticy iz input.txt";
        return 1;
    }
    //проверка на открытие файла
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "ne otkryt input.txt";
        return 1;
    }

	int n, start, finish;
    while (input >> n >> start >> finish) {

        start--;
        finish--;

        Vector matrix;
        matrix.resize(n * n);

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                int x;
                input >> x;
                matrix.set(i * n + j, x);
            }
        }

        Vector dist;
        dist.resize(n);

        for (size_t i = 0; i < n; i++) {
            dist.set(i, -1);
        }

        Queue q;

        dist.set(start, 0);
        q.insert(start);

        while (!q.empty()) {
            int v = q.get();
            q.remove();

            for (size_t u = 0; u < n; u++) {
                if (matrix.get(v * n + u) != 0 && dist.get(u) == -1) {
                    dist.set(u, dist.get(v) + 1);
                    q.insert((Data)u);
                }
            }
        }
    if (dist.get(finish) == -1)
        cout << "IMPOSSIBLE"<< endl;
    else
        cout << dist.get(finish)<<endl;
    }


}