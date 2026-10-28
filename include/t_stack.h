#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
class TStack {
private:
    T* pMem;          // Динамический массив
    int top;          // Индекс верхнего элемента
    size_t capacity;  // Вместимость массива

    void Resize() {
        // новая вместимость
        if (capacity == 0) {
            capacity = 1;     
        }
        else {
            capacity = capacity * 2; 
        }

        //выделение памяти и копирование
        T* newMem = new T[capacity];
        for (int i = 0; i <= top; i++) {
            newMem[i] = pMem[i];
        }
        delete[] pMem;
        pMem = newMem;
    }

public:

    
    TStack() : pMem(nullptr), top(-1), capacity(0) {}

    
    TStack(const TStack& other) : top(other.top), capacity(other.capacity) {
        if (capacity > 0) {
            pMem = new T[capacity];
            for (int i = 0; i <= top; i++) {
                pMem[i] = other.pMem[i];
            }
        }
        else {
            pMem = nullptr;
        }
    }

    // Конструктор перемещения
    TStack(TStack&& other) noexcept
        : pMem(other.pMem), top(other.top), capacity(other.capacity)
    {
        other.pMem = nullptr;
        other.top = -1;
        other.capacity = 0;
    }

    //  Оператор копирующего присваивания (классический)
    TStack& operator=(const TStack& other) {
        if (this == &other)
            return *this;
        T* newMem = nullptr;
        if (other.capacity > 0) {
            newMem = new T[other.capacity];
            for (int i = 0; i <= other.top; i++) 
                newMem[i] = other.pMem[i];          
        }
        delete[] pMem;
        pMem = newMem;
        top = other.top;
        capacity = other.capacity;
        return *this;
    }

    // Оператор перемещающего присваивания
    TStack& operator=(TStack&& other) noexcept {
        if (this != &other) {
            delete[] pMem;
            pMem = other.pMem;
            top = other.top;
            capacity = other.capacity;

            other.pMem = nullptr;
            other.top = -1;
            other.capacity = 0;
        }
        return *this;
    }

    ~TStack() {
        delete[] pMem;
    }

    // Размер стека
    size_t size() const { return top + 1; }

    // Проверка на пустоту
    bool IsEmpty() const { return top == -1; }

    // Добавление элемента
    void Push(const T& val) {
        if (static_cast<size_t>(top + 1) >= capacity) {
            Resize();
        }
        top++;
        pMem[top] = val;
    }

    // Извлечение элемента
    T Pop() {
        if (IsEmpty()) {
            throw out_of_range("Stack is empty");
        }
        T val = pMem[top];
        top--;
        return val;
    }

    // Просмотр верхнего элемента
    const T& Peek() const {
        if (IsEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return pMem[top];
    }

    // Ввод
    friend istream& operator>>(istream& istr, TStack& s) {
        s = TStack(); // Очищаем
        size_t count;
        cout << "Сколько элементов ввести? ";
        istr >> count;
        for (size_t i = 0; i < count; i++) {
            T val;
            istr >> val;
            s.Push(val);
        }
        return istr;
    }

    // Вывод
    friend ostream& operator<<(ostream& ostr, const TStack& s) {
        ostr << "Stack (top -> bottom): ";
        for (int i = s.top; i >= 0; i--) {
            ostr << s.pMem[i] << " ";
        }
        return ostr;
    }
};

#endif