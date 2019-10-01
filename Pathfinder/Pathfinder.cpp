#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "queue.h"

int main()
{
	std::ifstream input;
	input.open("input.txt");
	std::ofstream output;
	output.open("output.txt");


	std::string destination;
	size_t roadsAmount = 0;
	std::map<std::string, std::vector<std::string>> roads;
	Queue* paths = queue_create();
	while (!input.eof()) {
		std::string origin;
		std::string ending;
		input >> origin >> ending;
		if (!input.eof()) {
			if (roads.count(origin) == 0) {
				roads.insert(std::pair<std::string, std::vector<std::string>>(origin, std::vector<std::string>()));
			}
			roads[origin].push_back(ending);
			roadsAmount++;
		}
		else {
			if (origin == ending) {
				output << origin;
				roads.clear();
				queue_delete(paths);
				return 0;
			}
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

			if (roads.count(last) == 1) {
				for (size_t h = 0; h < roads[last].size(); h++) {
					if (roads[last][h] == destination) {
						while (!queue_empty(buffer)) {
							output << queue_get(buffer) << " ";
							queue_remove(buffer);
						}
						output << destination;
						roads.clear();
						queue_delete(buffer);
						queue_delete(paths);
						return 0;
					}

					for (size_t j = 0; j <= i; j++) {
						queue_insert(paths, queue_get(buffer));
						queue_insert(buffer, queue_get(buffer));
						queue_remove(buffer);
					}
					queue_insert(paths, roads[last][h]);
				}
			}

			queue_delete(buffer);
		}
		queue_remove(paths);
		queue_insert(paths, "");
	}

	roads.clear();
	queue_delete(paths);
	output << "No way!";
}
