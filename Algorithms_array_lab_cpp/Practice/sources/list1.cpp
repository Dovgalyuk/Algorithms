#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int *a = new int[n];
    for (int i = 0 ; i < n ; ++i)
    {
        int v;
        std::cin >> v;
        for (int j = i ; j > 0 ; --j)
            a[j] = a[j - 1];
        a[0] = v;
    }

    for (int i = 0 ; i < n ; ++i)
        std::cout << a[i] << ' ';
    std::cout << '\n';
    delete[] a;
}
