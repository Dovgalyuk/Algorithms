#include <string>
#include <vector>

struct Ans{
    bool is_number;
    std::string expression;
    int value;
};

#ifdef COMBINE_ANSWER

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

    if (op == '+')
        ans.value = a.value + b.value;
    else if (op == '-')
        ans.value = a.value - b.value;
    else
        ans.value = a.value * b.value;

    return ans;
}

#endif

Ans solve1(std::vector<int> &numbers, std::vector<char> &operations);
Ans solve2(std::vector<int> &numbers, std::vector<char> &operations);