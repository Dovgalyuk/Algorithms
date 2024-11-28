#include <string>
#include <vector>
#include "solutions.h"

#define max_ans(a, b) (((a).value > (b).value) ? (a) : (b))
#define min_ans(a, b) (((a).value < (b).value) ? (a) : (b))

static Ans combine_answer(Ans a, Ans b, char op);
static Ans min_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations);
static Ans max_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations);
static Ans extremum_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations, bool is_maximum);

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

static Ans extremum_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations, bool is_maximum)
{
    Ans ans;

    if (l == r) {
        ans.expression = std::to_string(numbers[l]);
        ans.value = numbers[l];    
        ans.is_number = true;
        return ans;
    }

    for (int k = l; k < r; k++) {
        Ans a1, a2, a3, a4;
        Ans a, b;
        
        a = min_value(l, k, numbers, operations);
        b = min_value(k + 1, r, numbers, operations);
        a1 = combine_answer(a, b, operations[k]);

        a = min_value(l, k, numbers, operations);
        b = max_value(k + 1, r, numbers, operations);
        a2 = combine_answer(a, b, operations[k]);

        a = max_value(l, k, numbers, operations);
        b = min_value(k + 1, r, numbers, operations);
        a3 = combine_answer(a, b, operations[k]);

        a = max_value(l, k, numbers, operations);
        b = max_value(k + 1, r, numbers, operations);
        a4 = combine_answer(a, b, operations[k]);

        if (is_maximum) {
            if (k == l)
                ans = max_ans(max_ans(a1, a2), max_ans(a3, a4));
            else
                ans = max_ans(ans, max_ans(max_ans(a1, a2), max_ans(a3, a4)));
        } else {
            if (k == l)
                ans = min_ans(min_ans(a1, a2), min_ans(a3, a4));
            else
                ans = min_ans(ans, min_ans(min_ans(a1, a2), min_ans(a3, a4)));
        }
    }

    return ans;
}

static Ans min_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations)
{
    return extremum_value(l, r, numbers, operations, false);
}

static Ans max_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations)
{
    return extremum_value(l, r, numbers, operations, true);
}

Ans solve1(std::vector<int> &numbers, std::vector<char> &operations)
{
    return max_value(0, numbers.size() - 1, numbers, operations);
}
