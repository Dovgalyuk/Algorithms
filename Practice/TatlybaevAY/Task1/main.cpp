#include <iostream>
#include "../../../LibraryCPPTemplate/array.h"

int main()
{
    int n;
    std::cin >> n;

    Array<int> osadki(n);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        osadki.set(i, x);
    }

    // делим на первую и вторую половину месяца с 1 по 15 и с 16 по 30
    int summa1 = 0, summa2 = 0;
    for (int i = 0; i < 15; i++)
        summa1 += osadki.get(i);
    for (int i = 15; i < n; i++)
        summa2 += osadki.get(i);

    if (summa1 > summa2)
        std::cout << "Больше осадков выпало в первой половине месяца\n";
    else if (summa2 > summa1)
        std::cout << "Больше осадков выпало во второй половине месяца\n";
    else
        std::cout << "Осадки в обеих половинах равны\n";

    // декаты 1- 10 11 - 20 21 - 30
    int dekada[3] = {0, 0, 0};
    for (int i = 0; i < n; i++)
        dekada[i / 10] += osadki.get(i);

    int maxDekada = 0;
    for (int i = 1; i < 3; i++)
        if (dekada[i] > dekada[maxDekada])
            maxDekada = i;

    std::cout << "Больше всего осадков выпало в " << (maxDekada + 1) << " декаде\n";

    return 0;
}