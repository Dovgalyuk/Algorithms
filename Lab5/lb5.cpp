#include "associative_array.h"
#include <iostream>

int main()
{
	string one = "Ivan";
	string second = "Filippov";
	AssociativeArray lol(one, second);
	lol.add(second, one);
	lol.add("PEPA", "FAFA");
	lol.add("PEPAf", "FAFAq");
	lol.remove("PEPA");
	string itog = lol.search("PEPAf");
	cout << itog;
}
