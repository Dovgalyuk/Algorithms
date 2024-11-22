#include <iostream>
#include "../Set.h"

int main() {
	std::cout << "SET TEST\n";
	Set set;
	set.insert("c");
	set.insert("a");
	set.insert("c");
	set.insert("b");
	std::cout << set.find("c") << '\n';
	std::cout << set.find("a") << '\n';
	std::cout << set.find("b") << '\n';
	return 0;
}