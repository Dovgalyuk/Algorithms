#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"

using namespace std;

const char WALL = '#';
const char EMPTY = '.';
const char START = 'X';
const char FINISH = 'Y';
const char PATH = 'x';

Vector* readMaze(const char* filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Error opening file: " << filename << endl;
		return nullptr;
	}

	Vector* maze = vector_create();
	char c;

	while (file.get(c)) {
		if (c == '\n') {
			vector_set(maze, vector_size(maze), ' ');
		}
		else {
			vector_set(maze, vector_size(maze), c);
		}
	}

	file.close();
	return maze;
}

void printMaze(const Vector* maze) {
	for (size_t i = 0; i < vector_size(maze); ++i) {
		char c = vector_get(maze, i);

		if (c == ' ') {
			cout << '\n';
		}
		else {
			cout << c;
		}
	}

	cout << endl;
}

bool findPath(Vector* maze) {
	Queue* queue = queue_create();

	size_t startX = 0, startY = 0;
	bool foundStart = false;

	for (size_t i = 0; i < vector_size(maze); ++i) {
		for (size_t j = 0; j < vector_size(maze); ++j) {
			char currentCell = vector_get(maze, i * vector_size(maze) + j);

			if (currentCell == START) {
				startX = i;
				startY = j;
				foundStart = true;
				break;
			}
		}

		if (foundStart) {
			break;
		}
	}

	if (!foundStart) {
		cout << "IMPOSSIBLE" << endl;
		queue_delete(queue);
		return false;
	}

	queue_insert(queue, static_cast<Data>(startX));
	queue_insert(queue, static_cast<Data>(startY));

	while (!queue_empty(queue)) {
		size_t currentX = static_cast<size_t>(queue_get(queue));
		queue_remove(queue);
		size_t currentY = static_cast<size_t>(queue_get(queue));
		queue_remove(queue);

		int dx[] = { -1, 1, 0, 0 };
		int dy[] = { 0, 0, -1, 1 };

		for (int i = 0; i < 4; ++i) {
			size_t newX = currentX + dx[i];
			size_t newY = currentY + dy[i];

			if (newX < vector_size(maze) && newY < vector_size(maze)) {
				char currentCell = vector_get(maze, newX * vector_size(maze) + newY);

				if (currentCell == EMPTY || currentCell == FINISH) {
					vector_set(maze, newX * vector_size(maze) + newY, PATH);

					queue_insert(queue, static_cast<Data>(newX));
					queue_insert(queue, static_cast<Data>(newY));
				}
			}
		}
	}


	bool wallFound = false;
	int emptyRowCount = 0;

	for (size_t i = 0; i < vector_size(maze); ++i) {
		char currentCell = vector_get(maze, i);

		if (currentCell == WALL) {
			wallFound = true;
			emptyRowCount = 0;  
		}
		else if (wallFound) {
			if (currentCell == ' ' || currentCell == '\n') {
				if (currentCell == '\n') {
					wallFound = false;
					emptyRowCount = 0;
				}
				else {
					++emptyRowCount;

					if (emptyRowCount >= 2) {
						queue_delete(queue);
						return false;
					}
				}
			}
			else {
				wallFound = false;
				emptyRowCount = 0;
			}
		}
	}
	for (size_t i = 0; i < vector_size(maze); ++i) {
		for (size_t j = 0; j < vector_size(maze); ++j) {
			if (vector_get(maze, i * vector_size(maze) + j) == EMPTY) {
				vector_set(maze, i * vector_size(maze) + j, 'x');
			}
		}
	}


	queue_delete(queue);
	return true;
}
int main() {
	const char* filename = "input.txt";
	Vector* maze = readMaze(filename);

	if (maze) {
		if (findPath(maze)) {
			printMaze(maze);
		}
		else {
			cout << "IMPOSSIBLE" << std::endl;
		}

		vector_delete(maze);
	}

	return 0;
}