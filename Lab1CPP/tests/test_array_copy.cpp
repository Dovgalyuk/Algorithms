#include <iostream>
#include "array.h"

int main() 
{
    Array* arr = new Array(5);
    for (int i = 0; i < 5; i++)
        arr->set(i, i * 10);   // 0,10,20,30,40

    Array copy(*arr);

    for (int i = 0; i < 5; i++)
    {
        if (copy.get(i) != arr->get(i)) 
        {
            std::cout << "Invalid copied value " << i << "\n";
            delete arr;
            return 1;
        }
    }

    // ћен€ем исходник Ч копи€ не должна изменитьс€
    arr->set(2, 777);
    if (copy.get(2) != 20) 
    {
        std::cout << "Invalid deep copy (copy changed after source)\n";
        delete arr;
        return 1;
    }

    // ћен€ем копию Ч исходник не должен изменитьс€
    copy.set(1, 555);
    if (arr->get(1) != 10) 
    {
        std::cout << "Invalid deep copy (source changed after copy)\n";
        delete arr;
        return 1;
    }

    delete arr;
    return 0;
}
