#include <iostream>
#include <string>
#include "myContainer.h"

using namespace std;

int main()
{
    int size = 1000000;
    auto spisok = new container(size);
    for (int i = 0; i < size; i++) {
        spisok->insert(to_string(i));
    }
    for (int i = 0; i < size; i++) {
        auto* strForChecking = spisok->findElement(to_string(i));
        if (!strForChecking) {
            cout << "Finding element in the spisok does not work correctly.";
            return 0;
        }
    }
    for (int i = 0; i < size; i++) {
        bool check = spisok->erase(to_string(i));
        if (!check) {
            cout << "Deleting element in the spisok does not work correctly.";
            return 0;
        }
    }
    spisok->~container();
    return 0;
}

