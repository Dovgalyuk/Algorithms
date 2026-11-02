#include "Lab2CPP.h"
#include "stack.h"

static int priority(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

static bool SYA(Tokens& tokens)
{
    if (tokens.empty()) return false;

    Stack* stack = stack_create();
    Tokens aux;

    for (size_t i = 0; i < tokens.size(); i++) {
        const string& t = tokens[i];
        if (isdigit(static_cast<unsigned char>(t[0]))) {
            aux.push_back(t);
        }
        else if (t == "+" || t == "-" || t == "*" || t == "/") {
            while (!stack_empty(stack) && stack_get(stack) != "(" &&
                priority(stack_get(stack)) >= priority(t)) {
                aux.push_back(stack_get(stack));
                stack_pop(stack);
            }
            stack_push(stack, t);
        }
        else if (t == "(") {
            stack_push(stack, t);
        }
        else if (t == ")") {
            while (!stack_empty(stack) && stack_get(stack) != "(") {
                aux.push_back(stack_get(stack));
                stack_pop(stack);
            }
            if (stack_empty(stack)) {
                stack_delete(stack);
                return false;
            }
            stack_pop(stack);
        }
    }
    while (!stack_empty(stack)) {
        if (stack_get(stack) == "(") {
            stack_delete(stack);
            return false;
        }
        aux.push_back(stack_get(stack));
        stack_pop(stack);
    }
    tokens = std::move(aux);
    stack_delete(stack);
    return true;
}

void RPN(Tokens& tokens)
{
    if (!SYA(tokens)) {
        cerr << "Invalid expression\n";
        return;
    }
    Stack* stack = stack_create();
    for (size_t i = 0; i < tokens.size(); i++) {
        const string& t = tokens[i];
        if (isdigit(static_cast<unsigned char>(t[0]))) {
            stack_push(stack, t);
        }
        else if (t == "+") {
            long long ap1 = stoll(stack_get(stack));
            stack_pop(stack);
            long long ap2 = stoll(stack_get(stack));
            stack_pop(stack);
            stack_push(stack, to_string(ap2 + ap1));
        }
        else if (t == "-") {
            long long ap1 = stoll(stack_get(stack));
            stack_pop(stack);
            long long ap2 = stoll(stack_get(stack));
            stack_pop(stack);
            stack_push(stack, to_string(ap2 - ap1));
        }
        else if (t == "*") {
            long long ap1 = stoll(stack_get(stack));
            stack_pop(stack);
            long long ap2 = stoll(stack_get(stack));
            stack_pop(stack);
            stack_push(stack, to_string(ap2 * ap1));
        }
        else if (t == "/") {
            long long ap1 = stoll(stack_get(stack));
            stack_pop(stack);
            long long ap2 = stoll(stack_get(stack));
            stack_pop(stack);
            if (ap1) stack_push(stack, to_string(ap2 / ap1));
            else {
                cerr << "Division by zero\n";
                stack_delete(stack);
                return;
            }
        }
    }
    cout << stack_get(stack) << endl;
    stack_delete(stack);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        cerr << "При использовании файла: " << argv[0] << " произошла ошибка, Вы не указали входной файл" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Ошибка открытия файла" << endl;
        return 1;
    }

    Tokens* tokens = tokens_create_and_read(input);
    if (tokens == nullptr) {
        cerr << "Invalid expression\n";
        return 1;
    }

    RPN(*tokens);

    delete tokens;

    return 0;
}