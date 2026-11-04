#include <iostream>
#include "t_stack.h"
#include <string>
using namespace std;


int priority(const  char& c){
    switch (c) {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    default: return -1;
    }
}


string RPN(string& input) {
    TStack<char> stack;
    string result;
    for (char ch : input) {
        if (isspace(ch)) continue;

        if (ch == '(') 
            stack.Push(ch);
        else if (ch == ')') {
            while (!stack.IsEmpty() && stack.Peek() != '(')
                result += stack.Pop();
            if (!stack.IsEmpty() && stack.Peek() == '(')
                stack.Pop();
        }
        else if (isdigit(ch))
            result += ch;
        else {
            while(!stack.IsEmpty() && priority(stack.Peek()) >= priority(ch)) 
                result += stack.Pop();
            stack.Push(ch);
        }
    }
    while (!stack.IsEmpty())
        result += stack.Pop();
    return result;
}

double answer(string& RpN) {
    TStack<double> sum;
    double value = 0.0;
    for (char c : RpN) {
        if (isdigit(c)) {
            sum.Push(c - '0');
        }
        else {
            double b = sum.Pop(); // Правый операнд
            double a = sum.Pop(); // Левый операнд
            switch (c) {
            case '+':
                value = (b+a);
                break;
            case '-':
                value = (a-b);

                break;
            case '*':
                value = (a * b);
 
                break;
            case '/':
                value = (a / b);
                break;
            default: return -1;
            }
            sum.Push(value);
        }
    }
    return sum.Pop();
}


int main() {
    setlocale(LC_ALL, "Russian");

    //TStack<int> stack;
    //cout << "Введите стек " << endl;
    //cin >> stack; 

    //cout << "\nстек: " << stack << endl; 

    //cout << "Размер: " << stack.size() << endl;
    //cout << "Верхний элемент: " << stack.Peek() << endl;

    //// Проверка копирования
    //TStack<int> stack2 = stack;
    //cout << "Копия: " << stack2 << endl;

    //// Проверка извлечения
    //cout << "Извлекаем: " << stack.Pop() << endl;
    //cout << "Стек после извлечения: " << stack << endl;
    string expression;
    cin >> expression;
    string to_RPN = RPN(expression); // перевод в ОПЗ
    cout << "Обратная польская запись: " << to_RPN << endl; // ОПЗ
    double an = answer(to_RPN); // Вычисление
    cout << "Ответ: " << an;
    return 0;
}