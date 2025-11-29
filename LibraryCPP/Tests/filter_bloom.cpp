#include <filter_bloom.h>
#include <iostream>

using namespace std;

int main() {

	FilterBloom* filter = f_create(1000, 3);

    if (!filter)
    {
        cout << "Filter creation error\n";
        return 1;
    }

	string value1 = "hello";
	string value2 = "world";
	string value3 = "bloom";

	f_insert(filter, value1);
	f_insert(filter, value2);

	if (!f_contains(filter, value1)) {
		cout << "f_insert or f_contains error for value1\n";
		return 1;
	}

	if (!f_contains(filter, value2)) {
		cout << "f_insert or f_contains error for value2\n";
		return 1;
	}

	if (f_contains(filter, value3)) {
		cout << "f_contains false positive for value3\n";
		return 1;
	}


	f_remove(filter, value1);

	if (f_contains(filter, value1)) {
		cout << "f_remove or f_contains error for value1\n";
		return 1;
	}

	if (!f_contains(filter, value2)) {
		cout << "f_contains error for value2 after removing value1\n";
		return 1;
	}

	f_delete(filter);

}