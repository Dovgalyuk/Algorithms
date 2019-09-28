#include <string>
#include <fstream>
#include "queue.h"

int main()
{
	std::ifstream input;
	input.open("input.txt");
	std::ofstream output;
	output.open("output.txt");


	std::string destination;
	size_t roadsAmount = 0;
	Queue* roads = queue_create();
	Queue* paths = queue_create();
	while (!input.eof()) {
		std::string origin;
		std::string ending;
		input >> origin >> ending;
		if (!input.eof()) {
			queue_insert(roads, origin);
			queue_insert(roads, ending);
			roadsAmount++;
		}
		else {
			queue_insert(paths, origin);
			queue_insert(paths, "");
			destination = ending;
		}
	}

	for (size_t i = 0; i < roadsAmount; i++) {
		while (queue_get(paths) != "") {
			Queue* buffer = queue_create();
			std::string last;
			for (size_t j = 0; j <= i; j++) {
				queue_insert(buffer, queue_get(paths));
				last = queue_get(paths);
				queue_remove(paths);
			}
			Queue* possibilities = queue_create();
			for (size_t j = 0; j < roadsAmount; j++) {
				std::string origin = queue_get(roads);
				queue_insert(roads, origin);
				queue_remove(roads);
				std::string ending = queue_get(roads);
				queue_insert(roads, ending);
				queue_remove(roads);
				if (origin == last) {
					if (ending == destination) {
						while (!queue_empty(buffer)) {
							output << queue_get(buffer) << " ";
							queue_remove(buffer);
						}
						output << destination;
						queue_delete(buffer);
						queue_delete(possibilities);
						queue_delete(roads);
						queue_delete(paths);
						return 0;
					}
					queue_insert(possibilities, ending);
				}
			}
			while (!queue_empty(possibilities)) {
				for (size_t j = 0; j <= i; j++) {
					queue_insert(paths, queue_get(buffer));
					queue_insert(buffer, queue_get(buffer));
					queue_remove(buffer);
				}
				queue_insert(paths, queue_get(possibilities));
				queue_remove(possibilities);
			}
			queue_delete(buffer);
			queue_delete(possibilities);
		}
		queue_remove(paths);
		queue_insert(paths, "");
	}
	queue_delete(roads);
	queue_delete(paths);
	output << "No way!";
}
