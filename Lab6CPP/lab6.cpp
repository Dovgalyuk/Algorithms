#include <iostream>
#include <string>
#include <vector>

#define max_ans(a, b) (((a).value > (b).value) ? (a) : (b))
#define min_ans(a, b) (((a).value < (b).value) ? (a) : (b))

struct Ans{
    bool is_number;
    std::string expression;
    int value;
};

Ans combine_answer(Ans a, Ans b, char op)
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

Ans min_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations);

Ans max_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations)
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

        if (k == l)
            ans = max_ans(max_ans(a1, a2), max_ans(a3, a4));
        else
            ans = max_ans(ans, max_ans(max_ans(a1, a2), max_ans(a3, a4)));
    }

    return ans;
}

Ans min_value(int l, int r, std::vector<int> &numbers, std::vector<char> &operations)
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

        if (k == l)
            ans = min_ans(min_ans(a1, a2), min_ans(a3, a4));
        else
            ans = min_ans(ans, min_ans(min_ans(a1, a2), min_ans(a3, a4)));
    }

    return ans;
}

Ans solve1(std::vector<int> &numbers, std::vector<char> &operations)
{
    return max_value(0, numbers.size() - 1, numbers, operations);
}

int main()
{
    std::string expression;
    std::vector<int> numbers;
    std::vector<char> operations;

    std::cout << "Enter expression: ";
    std::cin >> expression;

    int num = 0;
    for (char c: expression) {
        if (('0' <= c) and (c <= '9')) {
            num *= 10;
            num += c - '0';
        } else {
            numbers.push_back(num);
            operations.push_back(c);
            num = 0;
        }
    }
    numbers.push_back(num);

    Ans ans = solve1(numbers, operations);
    std::cout << ans.value << '\n' << ans.expression << std::endl;

    return 0;
}
