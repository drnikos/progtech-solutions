#include <iostream>
using namespace std;

template<typename T>
class stack {
public:
    stack(int size);
    stack(const stack &s);
    ~stack();
    const stack &operator=(const stack &s);
    bool empty() const;
    void push(const T &x);
    T pop();
    int size() const;
    template<typename U>
    friend ostream &operator<<(ostream &out, const stack<U> &s);

private:
    int stack_size;
    int c_index;
    T *li;
};

template<typename T>
stack<T>::stack(int size) {
    stack_size = size;
    c_index = 0;
    li = new T[stack_size];
}

template<typename T>
stack<T>::stack(const stack &s) {
    stack_size = s.stack_size;
    c_index = s.c_index;
    li = new T[stack_size];
    for (int i = 0; i < c_index; i++) {
        li[i] = s.li[i];
    }
}

template<typename T>
stack<T>::~stack() {
    delete[] li;
}

template<typename T>
const stack<T> &stack<T>::operator=(const stack &s) {
    if (this != &s) {
        delete[] li;
        stack_size = s.stack_size;
        c_index = s.c_index;
        li = new T[stack_size];
        for (int i = 0; i < c_index; i++) {
            li[i] = s.li[i];
        }
    }
    return *this;
}

template<typename T>
bool stack<T>::empty() const {
    return c_index == 0;
}

template<typename T>
void stack<T>::push(const T &x) {
        li[c_index++] = x;
}

template<typename T>
T stack<T>::pop() {
        return li[--c_index];
}

template<typename T>
int stack<T>::size() const {
    return c_index;
}

template<typename T>

ostream &operator<<(ostream &out, const stack<T> &s) {
    out << "[";
    for (int i = 0; i < s.c_index; i++) {
        out << s.li[i];
        if (i < s.c_index - 1)
            out << ", ";
    }
    out << "]";

    return out;
}

