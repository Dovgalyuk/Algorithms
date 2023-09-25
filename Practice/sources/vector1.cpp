#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int *a = new int[n];
    for (int i = 0 ; i < n ; ++i)
        std::cin >> a[i];

    int k;
    std::cin >> k;
    int m = 0;
    for (int i = 0 ; i < n ; ++i)
        if (a[i] < k)
            ++m;

    int *b = new int[m];
    m = 0;
    for (int i = 0 ; i < n ; ++i)
        if (a[i] < k)
            b[m++] = a[i];

    delete[] a;
    for (int i = 0 ; i < m ; ++i)
        std::cout << b[i] << ' ';
    delete[] b;
}
