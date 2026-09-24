#include <iostream>
#include "array.h"

int main()
{
    int n;
    std::cin >> n;

    Array<int> nums(n);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        nums.set(i, x);
    }

    // счетчик
    Array<int> count(1001);
    for (int i = 0; i <= 1000; i++)
        count.set(i, 0);

    for (int i = 0; i < n; i++)
        count.set(nums.get(i), count.get(nums.get(i)) + 1);

    // искат макс
    int maxVal = 0;
    for (int i = 1; i <= 1000; i++)
        if (count.get(i) > count.get(maxVal))
            maxVal = i;

    std::cout << maxVal << "\n";

    return 0;
}