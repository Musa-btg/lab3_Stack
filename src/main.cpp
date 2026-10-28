

#include <iostream>
#include "t_stack.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    TStack<int> stack;
    cout << "Введите стек " << endl;
    cin >> stack; 

    cout << "\nстек: " << stack << endl; 

    cout << "Размер: " << stack.size() << endl;
    cout << "Верхний элемент: " << stack.Peek() << endl;

    // Проверка копирования
    TStack<int> stack2 = stack;
    cout << "Копия: " << stack2 << endl;

    // Проверка извлечения
    cout << "Извлекаем: " << stack.Pop() << endl;
    cout << "Стек после извлечения: " << stack << endl;

    return 0;
}