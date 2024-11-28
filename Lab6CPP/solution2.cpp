#include <string>
#include <vector>
#include <limits>
#include "solutions.h"

#define max_ans(a, b) (((a).value > (b).value) ? (a) : (b))
#define min_ans(a, b) (((a).value < (b).value) ? (a) : (b))

static Ans combine_answer(Ans a, Ans b, char op)
{
    Ans ans;

    if (a.is_number) {
        if (b.is_number) {
            ans.expression = a.expression + op + b.expression;
        } else {
            ans.expression = a.expression + op + '(' + b.expression + ')';
        }
    } else {
        if (b.is_number) {
            ans.expression = '(' + a.expression + ')' + op + b.expression;
        } else {
            ans.expression = '(' + a.expression + ')' + op + '(' + b.expression + ')';
        }
    }
    ans.is_number = false;

    switch (op) {
        case '+': {
            ans.value = a.value + b.value;
            break;
        }
        case '-': {
            ans.value = a.value - b.value;
            break;
        }
        case '*': {
            ans.value = a.value * b.value;
            break;  
        }
    }

    return ans;
}

Ans solve2(std::vector<int> &numbers, std::vector<char> &operations)
{
    std::vector<std::vector<Ans>> min_value, max_value;
    min_value.resize(numbers.size());
    max_value.resize(numbers.size());
    for (size_t ind = 0; ind < numbers.size(); ind++) {
        Ans item, min_item, max_item;
        item.value = numbers[ind];
        item.is_number = true;
        item.expression = std::to_string(numbers[ind]);
        max_item.value = std::numeric_limits<int>::max();
        min_item.value = std::numeric_limits<int>::min();

        min_value[ind].resize(numbers.size(), max_item);
        max_value[ind].resize(numbers.size(), min_item);
        min_value[ind][ind] = max_value[ind][ind] = item;
    }

    for (size_t d = 1; d < numbers.size(); d++) {
        for (size_t l = 0; (l + d) < numbers.size(); l++) {
            size_t r = l + d;
            for (size_t k = l; k < r; k++) {
                Ans a1, a2, a3, a4;
                Ans a, b;
                
                a = min_value[l][k];
                b = min_value[k+1][r];
                a1 = combine_answer(a, b, operations[k]);

                a = min_value[l][k];
                b = max_value[k+1][r];
                a2 = combine_answer(a, b, operations[k]);

                a = max_value[l][k];
                b = min_value[k+1][r];
                a3 = combine_answer(a, b, operations[k]);

                a = max_value[l][k];
                b = max_value[k+1][r];
                a4 = combine_answer(a, b, operations[k]);

                min_value[l][r] = min_ans(min_value[l][r], min_ans(min_ans(a1, a2), min_ans(a3, a4)));
                max_value[l][r] = max_ans(max_value[l][r], max_ans(max_ans(a1, a2), max_ans(a3, a4)));
            }
        }
    }

    return max_value[0][numbers.size() - 1];
}
