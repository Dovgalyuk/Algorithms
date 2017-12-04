#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

void fillqueue(Queue *queue, ifstream &fin) {
	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		fin >> temp;
		queue_insert(queue, temp);
	}

}

int main() {
	ifstream fin("filte.txt", ios::in);
	freopen("output.txt","w",stdout);
	Queue *q[3];
	for (int i = 0; i < 3; i++) {
		q[i] = queue_create();
		fillqueue(q[i], fin);
	}
	fin.close();
	while (!(queue_empty(q[0]) && queue_empty(q[1]) && queue_empty(q[2]))) {
		int min = -1;
		int num;
		if (!queue_empty(q[0])) {
			min = queue_get(q[0]);
			num = 0;
		}
		if (!queue_empty(q[1])) {
			if (min == -1) {
				min = queue_get(q[1]);
				num = 1;
			} else {
				int temp = queue_get(q[1]);
				if (temp < min) {
					min = temp;
					num = 1;
				}
			}
		}
		if (!queue_empty(q[2])) {
			if (min == -1) {
				min = queue_get(q[2]);
				num = 2;
			} else {
				int temp = queue_get(q[2]);
				if (temp < min) {
					min = temp;
					num = 2;
				}
			}
		}
		queue_remove(q[num]);
		cout << num + 1 << " " << min << endl;
	}
	for (int i = 0; i < 3; i++) {
		queue_delete(q[i]);
	}
	return 0;
}
