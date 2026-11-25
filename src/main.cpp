#include <iostream>
#include "t_stack.h"
#include <string>
using namespace std;


int priority(const char& c) {
    switch (c) {
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    default: return -1;
    }
}


// Перевод в ОПЗ. Числа в результате разделены пробелами.
string RPN(string& input) {
    TStack<char> stack;
    string result;
    size_t i = 0;
    const size_t n = input.size();

    while (i < n) {
        char ch = input[i];

        if (isspace(ch)) { ++i; continue; }

        // --- число (одна или несколько цифр) ---
        if (isdigit(ch)) {
            // накапливаем всё число
            while (i < n && isdigit(input[i])) {
                result += input[i];
                ++i;
            }
            result += ' ';   // разделитель чисел в ОПЗ
            continue;        // i уже на следующем символе
        }

        // --- открывающая скобка ---
        if (ch == '(') {
            stack.Push(ch);
            ++i;
            continue;
        }

        // --- закрывающая скобка ---
        if (ch == ')') {
            while (!stack.IsEmpty() && stack.Peek() != '(')
                result += stack.Pop(), result += ' ';
            if (!stack.IsEmpty() && stack.Peek() == '(')
                stack.Pop();
            ++i;
            continue;
        }

        // --- оператор ---
        while (!stack.IsEmpty() && priority(stack.Peek()) >= priority(ch)) {
            result += stack.Pop();
            result += ' ';
        }
        stack.Push(ch);
        ++i;
    }

    while (!stack.IsEmpty()) {
        result += stack.Pop();
        result += ' ';
    }

    return result;
}


// Вычисление ОПЗ. Числа разделены пробелами.
double answer(string& RpN) {
    TStack<double> sum;
    size_t i = 0;
    const size_t n = RpN.size();

    while (i < n) {
        char c = RpN[i];

        if (isspace(c)) { ++i; continue; }

        // --- число ---
        if (isdigit(c)) {
            double num = 0.0;
            while (i < n && isdigit(RpN[i])) {
                num = num * 10 + (RpN[i] - '0');
                ++i;
            }
            sum.Push(num);
            continue;
        }

        // --- оператор ---
        double b = sum.Pop();   // правый операнд
        double a = sum.Pop();   // левый операнд
        double value = 0.0;

        switch (c) {
        case '+': value = a + b; break;
        case '-': value = a - b; break;
        case '*': value = a * b; break;
        case '/':
            if (b == 0.0) {
                cerr << "Ошибка: деление на ноль\n";
                return 0.0;
            }
            value = a / b;
            break;
        default:
            cerr << "Ошибка: неизвестный оператор '" << c << "'\n";
            return 0.0;
        }
        sum.Push(value);
        ++i;
    }

    return sum.Pop();
}


#ifndef RPN_TESTING
int main() {
    setlocale(LC_ALL, "Russian");

    string expression;
    getline(cin, expression);   // ← getline, чтобы читать пробелы

    string to_RPN = RPN(expression);
    cout << "Обратная польская запись: " << to_RPN << endl;

    double an = answer(to_RPN);
    cout << "Ответ: " << an << endl;
    return 0;
}
#endif