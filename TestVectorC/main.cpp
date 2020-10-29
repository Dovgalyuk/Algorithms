#include <iostream>
#include "..\..\..\..\..\..\Projects\Algorithms\LibraryCPP\vector.h"

int main()
{
    Vector *vector = new Vector();

    vector->Resize(5);
    if (vector->GetSize() != 5)
        std::cout << "Invalid resize\n";

    for (size_t i = 0 ; i < vector->GetSize(); ++i)
        vector->Set(i, i);

    for (size_t i = 0 ; i < vector->GetSize() ; ++i)
        if (vector->GetValue(i) != i)
            std::cout << "Invalid vector element " << i << "\n";

    vector->Resize(10);
    if (vector->GetSize() != 10)
        std::cout << "Invalid resize\n";

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector->GetSize(); ++i)
        std::cout << vector->GetValue(i) << " ";
    std::cout << "\n";

    vector->Resize(3);
    if (vector->GetSize() != 3)
        std::cout << "Invalid resize\n";

    for (size_t i = 0 ; i < vector->GetSize(); ++i)
        if (vector->GetValue(i) != i)
            std::cout << "Invalid vector element " << i << "\n";

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector->GetSize(); ++i)
        std::cout << vector->GetValue(i) << " ";
    std::cout << "\n";

    // Performance test
    for (int i = 0; i < 10000000; ++i)
        vector->Resize(i);

    delete vector;
}
